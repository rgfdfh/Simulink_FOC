/*
 * @日期:
 * @作者: lzm
 * @版本号:1.0
 */
#include "timer.h"
#include "dshot.h"

void HAL_Timer_Init()
{
	HAL_Timer3_Init();
}

void HAL_Timer3_Init()
{
	TIM_TimerInitTypeDef TIM_InitStruct;

	TIM_TimerStrutInit(&TIM_InitStruct);				  /* Timer结构体初始化*/
	TIM_InitStruct.Timer_SRC0 = CAP_SRC_TCH1;			  /* 定时器3通道0捕获定时器3通道1的输入信号，此处前通道0指寄存器，后通道1指IO脚，不是一个意思*/
	TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CAP; /* 设置Timer CH0为捕获模式 */
	TIM_InitStruct.Timer_CAP0_CLR_EN = ENABLE;			  /* 当发生CAP0捕获事件时，清零Timer计数器*/
	TIM_InitStruct.Timer_CH0_RE_CAP_EN = ENABLE;		  /* 使能Timer通道0上升沿捕获*/
	TIM_InitStruct.Timer_CH0_FE_CAP_EN = DISABLE;		  /* 关闭Timer通道0下降沿捕获*/

	TIM_InitStruct.Timer_SRC1 = CAP_SRC_TCH1;			  /* 定时器3通道1捕获定时器3通道1的输入信号*/
	TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CAP; /* 设置Timer CH1为捕获模式 */
	TIM_InitStruct.Timer_CAP1_CLR_EN = DISABLE;			  /* disable当发生CAP1捕获事件时，清零Timer计数器*/
	TIM_InitStruct.Timer_CH1_RE_CAP_EN = DISABLE;		  /* 关闭Timer通道1上升沿捕获*/
	TIM_InitStruct.Timer_CH1_FE_CAP_EN = ENABLE;		  /* 使能Timer通道1下降沿捕获*/

	TIM_InitStruct.Timer_TH = 960;					   /* 定时器计数门限初始值960*/
	TIM_InitStruct.Timer_FLT = 3;					   /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
	TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;	   /* 设置Timer模块时钟1分频系数 */
	TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_CH1_RE; /*通道1捕获/DMA请求使能，值寄存器通道1。这里是下降沿触发*/
	TIM_InitStruct.Timer_EVT = TIMER3_EVT_CH1;		   /*外部事件选择，通道1高电平开始计数，指的IO口*/
	TIM_InitStruct.Timer_GATE_EN = ENABLE;			   /*外部信号高电平则计数*/

	TIM_TimerInit(UTIMER3, &TIM_InitStruct);
	TIM_TimerCmd(UTIMER3, ENABLE); /* Timer3 模块使能 */

	// 配置P1.3 UTIMER3_CH1
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);		  // 初始化结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; // GPIO输入模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	// GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIO1, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_3, AF8_TIMER23); // P3.1复用为timer3的输出模式

	/*******************************************DMA初始化*********************************************** */
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.IRQ_EN = DISABLE;			   /* 中断不使能 */
	DMA_InitStruct.CIRC = DISABLE;				   /* 使用循环模式 */
	DMA_InitStruct.SINC = DISABLE;				   /* 源地址不自增 */
	DMA_InitStruct.DINC = ENABLE;				   /* 目标地址自增 */
	DMA_InitStruct.SBTW = DMA_HALFWORD_TRANS;	   /* 源地址访问位宽：字节 */
	DMA_InitStruct.DBTW = DMA_HALFWORD_TRANS;	   /* 目的地址访问位宽：字节 */
	DMA_InitStruct.REN.B.TIMER3_EN = ENABLE;	   /* DAM搬运使能源：TIMER3_EN */
	DMA_InitStruct.TMS = DSHOT_SIZE;			   /* 数据搬运的次数 */
	DMA_InitStruct.RMODE = ENABLE;				   /* 多轮传输使能 */
	DMA_InitStruct.DADR = (uint32_T)(Dshot_Data);  /* 目标地址 */
	DMA_InitStruct.SADR = (uint32_T)&UTIMER3_CMP1; /* 源地址 */
	DMA_InitStruct.EN = ENABLE;					   /* 使能通道 */
	DMA_Init(DMA_CHN0, &DMA_InitStruct);		   /* DMA通道0用来搬运 */
}

void HAL_SysTick_Init(uint32_T frq)
{
	Dshot_Handle.Dshot_Check_Frq = frq;				   // 确定检测频率
	
	if ((uint32_T)MCU_CLK / frq > 0xFFFFFF)
		return; // 24位计数器

	SysTick->LOAD = (uint32_T)MCU_CLK / frq - 1; // 计数到0，共ticks个时钟周期
	SysTick->VAL = 0;							   // 清零当前值
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |   // 使用处理器时钟
					SysTick_CTRL_TICKINT_Msk |	   // 使能中断
					SysTick_CTRL_ENABLE_Msk;	   // 使能SysTick
}