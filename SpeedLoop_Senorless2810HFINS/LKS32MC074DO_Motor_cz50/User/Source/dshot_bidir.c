/*
 * @日期: 2026.1.22
 * @作者: lzm
 * @版本号: 0.1
 */
#include "dshot_bidir.h"
#include "dshot.h"
#include "lks32mc07x_dma.h"
#include "timer.h"

/* 存储检测到的 DShot 类型 */
Dshot_Type_e Dshot_Type = DSHOT_TYPE_NORMAL; // 默认为普通 DShot

/* 全局遥测帧实例，存储编码后的双向DShot遥测数据 */
Dshot_Bidir_Frame_t Dshot_Bidir_Frame;

/* 双缓冲CMP值（发送模式用）*/
uint16_T Dshot_Telemetry_CMP_Buf[2][21];
static volatile uint8_T Dshot_Telemetry_Active = 0;
static volatile uint8_T Dshot_Telemetry_Pending = 0;
static volatile uint8_T Dshot_Telemetry_Pending_Valid = 0;

// 获取当前非活动缓冲区指针
static inline uint16_T *Dshot_Telemetry_GetInactiveBuf(void)
{
    return Dshot_Telemetry_CMP_Buf[Dshot_Telemetry_Active ^ 1U];
}

// 应用挂起的遥测数据（如果有）
static inline void Dshot_Telemetry_ApplyPending(void)
{
    if (Dshot_Telemetry_Pending_Valid)
    {
        Dshot_Telemetry_Active = Dshot_Telemetry_Pending;
        Dshot_Telemetry_Pending_Valid = 0;
    }
}

// 根据 GPIO 电平统计检测 DShot 类型（固定时间采样法）
// 在固定的 50ms 时间窗口内采样 GPIO，统计高/低电平出现次数
// 占比更高的电平为空闲电平。
// 返回检测到的 DShot 类型
Dshot_Type_e Dshot_Detect_Type_By_Level(void)
{
    // GPIO 初始化
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);        // 初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; // GPIO 输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // 高阻态
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    // 使用固定时间采样：50ms 内尽快采样 GPIO
    // 50ms 可覆盖约 500~4000 个 DShot 帧（取决于速率），避免数据溢出
    uint32_T count_high = 0, count_low = 0;
    uint32_T sample_start = 0; // 记录采样开始

    // 标记采样开始并进行 50ms 固定时间采样
    for (sample_start = 0; sample_start < 50; ++sample_start)
    {
        // 每 1ms 内尽快采样多次
        for (volatile uint16_T loop = 0; loop < 1000; ++loop)
        {
            uint8_T level = GPIO_ReadInputDataBit(GPIO1, GPIO_Pin_3);
            if (level)
            {
                count_high++;
            }
            else
            {
                count_low++;
            }
        }
        delay_ms(1); // 延迟 1ms，确保整个采样窗口为 50ms
    }

    uint32_T total = count_high + count_low;
    if (total == 0)
    {
        return DSHOT_TYPE_NORMAL; // 无法统计，保守默认单向 DShot
    }

    // 判断占比 >70%：count_high / total > 0.7 等价于 count_high * 10 > total * 7
    // 要求另一电平至少出现10次，避免空连接时的偶然扰动误判
    if (count_high * 10 > total * 7 && count_low >= 10)
    {
        // 高电平占 >70% 且低电平 >=10次 -> 空闲为高 -> 双向 DShot（反相）
        return DSHOT_TYPE_BIDIR;
    }
    else if (count_low * 10 > total * 7 && count_high >= 10)
    {
        // 低电平占 >70% 且高电平 >=10次 -> 空闲为低 -> 普通 DShot
        return DSHOT_TYPE_NORMAL;
    }
    else
    {
        // 无法确定或无有效信号，保守默认单向 DShot
        return DSHOT_TYPE_NORMAL;
    }
}

// 初始化定时器和 DMA（根据传入的类型配置）
void Dshot_Init_Capture_By_Type(Dshot_Type_e detect_type)
{
    TIM_TimerInitTypeDef TIM_InitStruct;
    TIM_TimerStrutInit(&TIM_InitStruct);
    TIM_TimerCmd(UTIMER3, DISABLE);
    // 通道0：捕获同一输入的另一沿，并在该沿清零计数器
    TIM_InitStruct.Timer_SRC0 = CAP_SRC_TCH1;             // CH0 捕获 TCH1 输入
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP; // CH0 捕获模式
    TIM_InitStruct.Timer_CAP0_CLR_EN = ENABLE;            // CH0 捕获事件清零计数器
    // 通道1：在另一沿进行捕获，不清零，用于DMA搬运脉宽值
    TIM_InitStruct.Timer_SRC1 = CAP_SRC_TCH1;             // CH1 捕获 TCH1 输入
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP; // CH1 捕获模式
    TIM_InitStruct.Timer_CAP1_CLR_EN = DISABLE;           // CH1 不清零（由CH0清零实现脉宽测量）

    // 根据传入的类型中选择边沿组合
    if (detect_type == DSHOT_TYPE_BIDIR)
    {
        // 双向DShot（反相）：测低脉宽
        // CH0 在下降沿清零；CH1 在上升沿捕获并触发DMA
        TIM_InitStruct.Timer_CH0_RE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH0_FE_CAP_EN = ENABLE; // 下降沿清零
        TIM_InitStruct.Timer_CH1_RE_CAP_EN = ENABLE;
        TIM_InitStruct.Timer_CH1_FE_CAP_EN = DISABLE; // 上升沿捕获
        // DMA请求选择CH1的对应沿（工程中使用 Timer_IRQEna_CH1_RE）
        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1_RE; // 这里为上升沿触发
    }
    else
    {
        // 普通DShot：测高脉宽
        // CH0 在上升沿清零；CH1 在下降沿捕获并触发DMA
        TIM_InitStruct.Timer_CH0_RE_CAP_EN = ENABLE; // 上升沿清零
        TIM_InitStruct.Timer_CH0_FE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH1_RE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH1_FE_CAP_EN = ENABLE; // 下降沿捕获
        // DMA请求选择CH1的对应沿（工程中使用 Timer_IRQEna_CH1_RE）
        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1_RE; // 这里为下降沿触发（与工程保持一致）
    }

    TIM_InitStruct.Timer_TH = 960;                  // 门限
    TIM_InitStruct.Timer_FLT = 3;                   // 数字滤波
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1; // 时钟分频
    TIM_InitStruct.Timer_EVT = TIMER3_EVT_CH1;      // 外部事件选择：通道1
    TIM_InitStruct.Timer_GATE_EN = DISABLE;         // 统一关闭门控，计数在高/低电平都进行

    TIM_TimerInit(UTIMER3, &TIM_InitStruct);
    UTIMER3->IF = 0xFFFFFFFF; // 清除Timer3中断/请求标志

    // 配置 P1.3 UTIMER3_CH1
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);        // 初始化结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; // GPIO 输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, AF8_TIMER23); // P1.3 复用为 TIMER3

    // ========== DMA_CHN0 初始化：接收模式（默认启用） ==========
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.IRQ_EN = DISABLE;          // 关闭中断
    DMA_InitStruct.CIRC = DISABLE;            // 循环模式
    DMA_InitStruct.SINC = DISABLE;            // 源地址固定：捕获寄存器
    DMA_InitStruct.DINC = ENABLE;             // 目标地址递增
    DMA_InitStruct.SBTW = DMA_HALFWORD_TRANS; // 源地址半字传输（16位）
    DMA_InitStruct.DBTW = DMA_HALFWORD_TRANS; // 目标地址半字传输（16位）
    DMA_InitStruct.REN.B.TIMER3_EN = ENABLE;
    DMA_InitStruct.TMS = DSHOT_SIZE;               // 最多32个脉宽值
    DMA_InitStruct.RMODE = ENABLE;                 // 单轮传输，意思是一个触发源来一次搬一次
    DMA_InitStruct.EN = ENABLE;                    // 使能DMA
    DMA_InitStruct.DADR = (uint32_T)(Dshot_Data);  /* 目标地址 */
    DMA_InitStruct.SADR = (uint32_T)&UTIMER3_CMP1; /* 源地址 */
    DMA_Init(DMA_CHN0, &DMA_InitStruct);

    TIM_TimerCmd(UTIMER3, ENABLE);
}

/******************************************************************************
 * 双向DShot遥测数据编码（电调端：转速->16位数据->GCR编码 + 变换）
 *****************************************************************************/

// GCR编码表：4位数据 -> 5位GCR码（标准双向DShot映射）
// 索引为4位数据值（0~15），值为对应的5位GCR编码（保证无连续3个0）
static const uint8_T GCR_Encode_Table[16] = {
    0x19, // 0x0 -> 0b11001
    0x1B, // 0x1 -> 0b11011
    0x12, // 0x2 -> 0b10010
    0x13, // 0x3 -> 0b10011
    0x1D, // 0x4 -> 0b11101
    0x15, // 0x5 -> 0b10101
    0x16, // 0x6 -> 0b10110
    0x17, // 0x7 -> 0b10111
    0x1A, // 0x8 -> 0b11010
    0x09, // 0x9 -> 0b01001
    0x0A, // 0xA -> 0b01010
    0x0B, // 0xB -> 0b01011
    0x1E, // 0xC -> 0b11110
    0x0D, // 0xD -> 0b01101
    0x0E, // 0xE -> 0b01110
    0x0F  // 0xF -> 0b01111
};

// GCR编码：4位 -> 5位
static inline uint8_T Dshot_GCR_Encode(uint8_T nibble)
{
    return GCR_Encode_Table[nibble & 0x0F];
}

// 计算4位CRC（双向DShot遥测使用的CRC算法）
// 输入：data_12bit - 12位数据（与命令帧相同的CRC算法）
static uint8_T Dshot_Bidir_CalcCRC(uint16_T data_12bit)
{
    uint8_T crc = 0;
    crc = (data_12bit ^ (data_12bit >> 4) ^ (data_12bit >> 8)) & 0x0F;
    return crc;
}

// 编码双向DShot遥测帧
int Dshot_Bidir_Encode_Telemetry(uint32_T rpm, uint8_T pole_pair_num, Dshot_Bidir_Frame_t *frame)
{
    if (frame == NULL || pole_pair_num == 0)
    {
        return -1;
    }
    // 步骤1：计算eRPM（电气转速）
    // eRPM = 转速(rpm) × 极对数 × 2
    uint32_T erpm = rpm * pole_pair_num * 2;

    if (erpm == 0)
    {
        erpm = 1;
    }

    // 步骤2：计算周期（单位：us）
    uint32_T period_us = DSP0_div(60000000, erpm); // 60,000,000 = 60秒 * 1,000,000微秒

    // 步骤3：指数编码
    uint8_T exp = 0;
    uint16_T period_base = period_us;

    while (period_base > 511 && exp < 7) // 9位有效数据，最大511, 3位指数
    {
        period_base >>= 1;
        exp++;
    }

    if (period_base > 511)
    {
        period_base = 511;
    }
    if (period_base == 0)
    {
        period_base = 1;
    }

    // 步骤4：组装12位数据
    uint16_T data_12bit = ((exp & 0x07) << 9) | (period_base & 0x1FF);

    // 步骤5：计算CRC
    uint8_T crc = Dshot_Bidir_CalcCRC(data_12bit);

    // 步骤6：分解为4个nibble
    uint8_T nibbles[4];
    nibbles[0] = (data_12bit >> 8) & 0x0F;
    nibbles[1] = (data_12bit >> 4) & 0x0F;
    nibbles[2] = data_12bit & 0x0F;
    nibbles[3] = crc & 0x0F;

    // 步骤7&8：合并 GCR 位展开 + RLL 变换 + CMP生成（仅输出CMP，不再存储bit数组）
    // If the current bit in GCR data is a 1: The current new bit is the inversion of the last new bit
    // If the current bit in GCR data is a 0: The current new bit is the same as the last new bit
    // 大概就是1的话反转电平，0保持电平，使用5/4 DShot的TH值来生成CMP值

    frame->bit_count = 0; // 标记写入中
    uint16_T *cmp_buf = Dshot_Telemetry_GetInactiveBuf();
    uint8_T last_bit = 0;
    uint8_T idx = 0; // 已生成位计数（不含起始位）,在PWM初始化就写入了
    for (int i = 0; i < 4; i++)
    {
        uint8_T gcr_value = Dshot_GCR_Encode(nibbles[i]);
        for (int bit = 4; bit >= 0; bit--)
        {
            last_bit ^= (gcr_value >> bit) & 0x01; // 1→翻转，0→保持
            cmp_buf[idx] = last_bit ? 0 : DSHOT_TH_5_4;
            idx++;
        }
    }
    cmp_buf[20] = DSHOT_TH_5_4;                                       // 默认最后拉低，可以改
    Dshot_Telemetry_Pending = (uint8_T)(Dshot_Telemetry_Active ^ 1U); // 切换缓冲区
    Dshot_Telemetry_Pending_Valid = 1;                                // 也算切换缓冲区标志
    frame->bit_count = 20;                                            // 写入完成
    return 0;
}

/******************************************************************************
 * 双向DShot发送模式初始化（Timer + DMA_CHN1）
 *****************************************************************************/

// 初始化Timer用于发送双向DShot遥测帧
// 工作模式：比较输出（OC），21位RLL编码数据通过DMA加载到CMP0
// 速率：5/4 DShot速率 = 375kHz @ 96MHz（每bit=256个时钟周期）
void Dshot_Init_Transmit_By_Frame(void)
{
    Dshot_Telemetry_ApplyPending();
    // 步骤1：关闭DMA_CHN0
    DMA_CHN0->CCR &= ~BIT0;
    // 确保定时器在重新配置前处于关闭状态，避免残留触发
    TIM_TimerCmd(UTIMER3, DISABLE);

    // 步骤2：配置Timer为比较输出模式

    // 通道0：比较输出模式，输出RLL编码后的PWM
    TIM_TimerInitTypeDef TIM_InitStruct;
    TIM_TimerStrutInit(&TIM_InitStruct);
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; // CH0 比较输出模式（标准库宏）
    TIM_InitStruct.Timer_CMP0 = DSHOT_TH_5_4;
    TIM_InitStruct.Timer_CH0Output = 0; // 计数器回零时，比较模式输出极性控制

    // 通道1：比较输出模式，输出RLL编码后的PWM
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; // CH1 比较输出模式（标准库宏）
    TIM_InitStruct.Timer_CMP1 = DSHOT_TH_5_4;
    TIM_InitStruct.Timer_CH1Output = 0; // 计数器回零时，比较模式输出极性控制

    // 改变中断触发源为计数器过0事件（用于DMA_CHN0每bit时间触发一次）
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC_RE; // 使用计数器过0 DMA请求触发DMA_CHN0

    TIM_InitStruct.Timer_TH = DSHOT_TH_5_4 - 1;     // 5/4速率对应的周期
    TIM_InitStruct.Timer_FLT = 0;                   // 数字滤波
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1; // 时钟分频
    TIM_InitStruct.Timer_GATE_EN = DISABLE;         // 关闭门控

    TIM_TimerInit(UTIMER3, &TIM_InitStruct);
    TIM_TimerCmd(UTIMER3, DISABLE);
    UTIMER3->CNT = 0;
    UTIMER3->IF = 0xFFFFFFFF; // 清除Timer3中断/请求标志

    // 步骤3：配置GPIO为比较输出模式（UTIMER3 CH0 → P1.3，AF复用）
    GPIO1->POE |= GPIO_Pin_3;
    GPIO1->PIE &= ~GPIO_Pin_3; // 设置为输出模式

    // 步骤5：重新配置 DMA_CHN0 为发送模式
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.DADR = (uint32_T)&UTIMER3_CMP1;                                   // 目标：Timer比较寄存器
    DMA_InitStruct.SADR = (uint32_T)Dshot_Telemetry_CMP_Buf[Dshot_Telemetry_Active]; // 源：活动CMP缓冲
    DMA_InitStruct.TMS = 20;                                                         // 传输20个值
    DMA_InitStruct.SINC = ENABLE;                                                    // 源地址递增
    DMA_InitStruct.DINC = DISABLE;                                                   // 目标地址固定
    DMA_InitStruct.SBTW = DMA_HALFWORD_TRANS;                                        // 源宽度：16位
    DMA_InitStruct.DBTW = DMA_HALFWORD_TRANS;                                        // 目标宽度：16位
    DMA_InitStruct.REN.B.TIMER3_EN = ENABLE;                                         // Timer3触发DMA
    DMA_InitStruct.RMODE = ENABLE;                                                   // 单轮传输
    DMA_InitStruct.CIRC = DISABLE;                                                   // 非循环
    DMA_InitStruct.IRQ_EN = DISABLE;                                                 // 无中断
    DMA_InitStruct.EN = ENABLE;
    DMA_Init(DMA_CHN0, &DMA_InitStruct);

    TIM_TimerCmd(UTIMER3, ENABLE); // 最后启动定时器
}

// 发送完成后切换回接收模式
void Dshot_Exit_Transmit_Mode(void)
{
    // 步骤1：关闭DMA_CHN0
    DMA_CHN0->CCR &= ~BIT0;

    // 步骤2：关闭DMA_CHN0（发送模式）并重置CTMS
    TIM_TimerCmd(UTIMER3, DISABLE);

    // 步骤3：配置Timer回到捕获模式，恢复CH1边沿DMA触发
    TIM_TimerInitTypeDef TIM_InitStruct;
    TIM_TimerStrutInit(&TIM_InitStruct);

    // 通道0：捕获模式，清零计数器
    TIM_InitStruct.Timer_SRC0 = CAP_SRC_TCH1;             // CH0 捕获 TCH1 输入
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP; // CH0 捕获模式
    TIM_InitStruct.Timer_CAP0_CLR_EN = ENABLE;            // CH0 捕获事件清零计数器

    // 通道1：捕获模式，不清零
    TIM_InitStruct.Timer_SRC1 = CAP_SRC_TCH1;             // CH1 捕获 TCH1 输入
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP; // CH1 捕获模式
    TIM_InitStruct.Timer_CAP1_CLR_EN = DISABLE;           // CH1 不清零

    // 根据DShot类型配置边沿（恢复接收模式的配置）
    if (Dshot_Type == DSHOT_TYPE_BIDIR)
    {
        TIM_InitStruct.Timer_CH0_RE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH0_FE_CAP_EN = ENABLE; // 下降沿清零
        TIM_InitStruct.Timer_CH1_RE_CAP_EN = ENABLE; // 上升沿捕获
        TIM_InitStruct.Timer_CH1_FE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1_RE; // 上升沿触发DMA
    }
    else
    {
        TIM_InitStruct.Timer_CH0_RE_CAP_EN = ENABLE; // 上升沿清零
        TIM_InitStruct.Timer_CH0_FE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH1_RE_CAP_EN = DISABLE;
        TIM_InitStruct.Timer_CH1_FE_CAP_EN = ENABLE;       // 下降沿捕获
        TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1_RE; // 下降沿触发DMA
    }

    TIM_InitStruct.Timer_TH = 960;   // 恢复原有门限
    TIM_InitStruct.Timer_CMP0 = 960; // 预防更改定时器一瞬间，GPIO还是输出模式导致出现一个小高电平
    TIM_InitStruct.Timer_CMP1 = 960;
    TIM_InitStruct.Timer_FLT = 3;                   // 数字滤波
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1; // 时钟分频
    TIM_InitStruct.Timer_EVT = TIMER3_EVT_CH1;      // 外部事件选择：通道1
    TIM_InitStruct.Timer_GATE_EN = DISABLE;         // 关闭门控

    TIM_TimerInit(UTIMER3, &TIM_InitStruct); // 就这里
    UTIMER3->IF = 0xFFFFFFFF;                // 清除Timer3中断/请求标志

    // 步骤4：恢复GPIO为输入模式（UTIMER3 CH1 → P1.3 捕获输入）
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; // 输入模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;    // P1.3 捕获输入
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    //    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, AF8_TIMER23);

    // 步骤5：重新配置 DMA_CHN0 为接收模式并启动
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.IRQ_EN = DISABLE; // 关闭中断
    DMA_InitStruct.CIRC = DISABLE;
    DMA_InitStruct.SINC = DISABLE; // 源地址固定：捕获寄存器
    DMA_InitStruct.DINC = ENABLE;  // 目标地址递增
    DMA_InitStruct.SBTW = DMA_HALFWORD_TRANS;
    DMA_InitStruct.DBTW = DMA_HALFWORD_TRANS;
    DMA_InitStruct.REN.B.TIMER3_EN = ENABLE;
    DMA_InitStruct.TMS = DSHOT_SIZE; // 最多32个脉宽值
    DMA_InitStruct.RMODE = ENABLE;   // 单轮传输
    DMA_InitStruct.EN = ENABLE;
    DMA_InitStruct.DADR = (uint32_T)(Dshot_Data);  /* 目标地址 */
    DMA_InitStruct.SADR = (uint32_T)&UTIMER3_CMP1; /* 源地址 */
    DMA_Init(DMA_CHN0, &DMA_InitStruct);

    // 最后启动定时器
    TIM_TimerCmd(UTIMER3, ENABLE); // 最后启动定时器
}
