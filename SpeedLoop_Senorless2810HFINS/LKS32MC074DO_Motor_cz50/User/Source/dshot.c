/*
 * @日期:
 * @作者:
 * @版本号:
 */
/*
 * @日期: 2025.10.10
 * @作者: lzm
 * @版本号: 1.3
 */
#include "dshot.h"
#include "dshot_bidir.h"
#include "timer.h"

#define SPD_SCALE (SPD_MAX - SPD_MIN) / 2000U
Dshot_HandleTypeDef Dshot_Handle = {0}; // 定义Dshot结构体（含 Telem_Tx_Busy 初始化为0）
uint16_T Dshot_Data[DSHOT_SIZE];//={240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 119, 119, 119, 119, 119, 119, 119, 119}; // Dshot数据

/**
 * @函数名称: dshot数据辨识
 * @功能描述: 根据占空比大小返回0/1，错误则为2
 * @param {uint16_T} dshot_data
 */
uint8_T Dshot_Bit_Read(uint16_T dshot_data)
{
    uint8_T result = 2; // 默认错误
    if (dshot_data >= DSHOT_0_MIN && dshot_data <= DSHOT_0_MAX)
        result = 0;
    if (dshot_data >= DSHOT_1_MIN && dshot_data <= DSHOT_1_MAX)
        result = 1;
    return result;
}

/**
 * @函数名称:
 * @功能描述: 将DMA数据进行解码（高性能版：循环展开 + 指针遍历）
 */
uint16_T Dshot_Get_Data(Dshot_HandleTypeDef *hdshot, uint16_T begin_count, uint8_T *flag)
{
    uint16_T result = 0;
    *flag = 1;

    // 缓存边界和指针，避免重复访问
    uint16_T end_count = hdshot->DMA_Count;
    uint16_T *pData = &Dshot_Data[begin_count];
    uint8_T loop_count = end_count - begin_count;

    // 快速路径：16位固定长度（最常见情况）- 完全展开
    if (loop_count == 16)
    {
// 宏定义：保留完整的范围检查逻辑
#define DECODE_BIT(idx)                                      \
    {                                                        \
        uint16_T data = pData[idx];                          \
        if (data >= DSHOT_0_MIN && data <= DSHOT_0_MAX)      \
        {                                                    \
            result = (result << 1);                          \
        }                                                    \
        else if (data >= DSHOT_1_MIN && data <= DSHOT_1_MAX) \
        {                                                    \
            result = (result << 1) | 1;                      \
        }                                                    \
        else                                                 \
        {                                                    \
            *flag = 0;                                       \
            return 0;                                        \
        }                                                    \
    }

        DECODE_BIT(0);
        DECODE_BIT(1);
        DECODE_BIT(2);
        DECODE_BIT(3);
        DECODE_BIT(4);
        DECODE_BIT(5);
        DECODE_BIT(6);
        DECODE_BIT(7);
        DECODE_BIT(8);
        DECODE_BIT(9);
        DECODE_BIT(10);
        DECODE_BIT(11);
        DECODE_BIT(12);
        DECODE_BIT(13);
        DECODE_BIT(14);
        DECODE_BIT(15);

#undef DECODE_BIT
        return result;
    }

    // 慢速路径：非16位长度 - 指针遍历
    for (uint8_T i = 0; i < loop_count; i++)
    {
        uint16_T dshot_data = *pData++;

        if (dshot_data >= DSHOT_0_MIN && dshot_data <= DSHOT_0_MAX)
        {
            result = (result << 1);
        }
        else if (dshot_data >= DSHOT_1_MIN && dshot_data <= DSHOT_1_MAX)
        {
            result = (result << 1) | 1;
        }
        else
        {
            result = 0;
            *flag = 0;
            break;
        }
    }

    return result;
}

/**
 * @函数名称:
 * @功能描述: 检测是否有数据传过来
 */
void Dshot_Check(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD)
{
    hdshot->Dshot_Check_Cnt++;
    if (hdshot->Dshot_Check_Cnt > hdshot->Dshot_Check_Frq) // 1秒无命令则认为关机
    {
        hdshot->Dshot_Check_Cnt = hdshot->Dshot_Check_Frq;
        *state = 0;
        *slow = 0;
        *SPD = 0;
    }

//    if (hdshot->DMA_Count == DSHOT_SIZE - DMA_CHN0->CTMS)
//    {
//        hdshot->DMA_Stop_Flag++; // 搬运结束
//        if (hdshot->DMA_Stop_Flag > 250)
//        {
//            hdshot->DMA_Stop_Flag = 250;
//        }
//    }
//    else
//    {
//        hdshot->DMA_Stop_Flag = 0;
//    }

    hdshot->DMA_Count = DSHOT_SIZE - DMA_CHN0->CTMS; // 记录个数
		
		if (hdshot->DMA_Count > 0) // 发生搬运
    {
      hdshot->Dshot_Decode_Flag = 1;
			
    }
		if(hdshot->DMA_Count > 15)
		{
			hdshot->Data_Receive_Flag = 1;
		}

}

/**
 * @函数名称:
 * @功能描述: dshot数据获取
 */
int16_T DMAtmp;
void Dshot_Decode(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD)
{
    uint16_T result = 0;           // 解码结果
		uint8_T Data_Correct_Flag = 0; // 数据正确标志
    uint8_T CRC = 0;               // CRC校验
    uint16_T throttle_val;         // 缓存油门值，减少load指令依赖

    if (hdshot->Dshot_Decode_Flag == 1)
    {
//        DMA_CHN0->CCR &= ~BIT0;      // 关闭DMA
        if (hdshot->DMA_Count >= 16) // 至少16个数据才进行解码
        {
            result = Dshot_Get_Data(hdshot, hdshot->DMA_Count - 16, &Data_Correct_Flag);
        }

        if (Data_Correct_Flag == 1) // 数据正确才往下
        	{	
            CRC = result & 0x0F;
            if (Dshot_Type == DSHOT_TYPE_BIDIR)
            {
                // 双向 DShot 反相处理
                CRC = (~CRC) & 0x0F;
            }
            result = result >> 4;
            if (CRC == (((result ^ (result >> 4) ^ (result >> 8)) & 0x0F))) // CRC校验
            {
                hdshot->Dshot_Check_Cnt = 0;           // 有命令，计数清零
                throttle_val = (result >> 1) & 0x07FF; // 缓存油门值到本地变量
                hdshot->Telemetry = (result) & 0x01;   // 请求标志

                if (throttle_val > 47 && throttle_val < 2048) // 48~2047为油门值，并映射到转速
                {
                    *state = 1;
                    *slow = 0;
                    *SPD = SPD_MIN + ((throttle_val - 47) * SPD_SCALE);
                }

                if (throttle_val == hdshot->Throttle_Last)
                {
                    hdshot->Repeat_Cnt++; // 重复命令计数
                    if (hdshot->Repeat_Cnt > 60000U)
                        hdshot->Repeat_Cnt = 60000U;
                }
                else
                {
                    hdshot->Repeat_Cnt = 0;
                }
                hdshot->Throttle_Last = throttle_val; // 记录上次油门值

                if (throttle_val < 37 && *state == 0 && hdshot->Repeat_Cnt > 6)
                {
                    switch (throttle_val)
                    {
                    case 7: // 永久方向0
                        hdshot->Direction = 0;
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 8: // 永久方向1
                        hdshot->Direction = 1;
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 12: // 写入
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 15: // 慢转
                        *state = 0;
                        *slow = 1;
                        *SPD = 0;
                        break;
                    case 20: // 临时方向0
                        hdshot->Direction = 0;
                        break;
                    case 21: // 临时方向1
                        hdshot->Direction = 1;
                        break;
                    }
                }
                if (throttle_val == 0) // 0油门认为关机
                {
                    *state = 0;
                    *slow = 0;
                    *SPD = 0;
                }
            }
				}

//        memset(Dshot_Data, 0, sizeof(Dshot_Data));
        
        if (Dshot_Type == DSHOT_TYPE_NORMAL && hdshot->DMA_Count >= 16)  // DSHOT_TYPE_BIDIR  DSHOT_TYPE_NORMAL
        {
						DMA_CHN0->CCR &= ~BIT0;      // 关闭DMA
            DMA_CHN0->CTMS = DSHOT_SIZE; // 重置DMA搬运次数
            DMA_CHN0->CCR |= BIT0; // 启动DMA_CHN0
        }
        hdshot->Dshot_Decode_Flag = 0; // 清除标志
    }
}

/******************************************Flash相关*************************************/
void Save_Flash_Data(uint8_T dir)
{
    erase_flag = 0x9A0D361F;              // c擦除解锁
    EraseSector(0x0, Flash_NVR);          // 擦除flash的NVR区域即独立的1KB用户存储区
    erase_flag = 0;                       // 擦除上锁
    progm_flag = 0x9AFDA40C;              // 编程解锁
    ProgramPage(0x0, 1, &dir, Flash_NVR); // 编程flash的NVR区域即独立的1KB用户存储区
    progm_flag = 0;                       // 编程上锁
}

void Read_Flash_Data(uint8_T *dir)
{
    uint32_T tmp = 0;
    Read_More_Flash(0x0, 1, &tmp, Flash_NVR); // 读取1个单位（底层实现按字/字节由库决定）
    *dir = (uint8_T)(tmp & 0xFFU);
}
