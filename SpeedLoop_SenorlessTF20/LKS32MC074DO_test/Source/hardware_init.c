// src file: hardware_init.c
#include "hardware_init.h"
#include "lks32mc07x_gpio.h"
/* USER CODE BEGIN Includes */
#include "FOC_PointModel.h"
#define CH_NUM 	12	//???????4??12
#define DIV			7	//?????
typedef struct
{
		int16_t front;
    int16_t buff[CH_NUM];
}TYPE_BUFF;
TYPE_BUFF send_buff;
uint8_t flag_div;
uint8_t flag_ptr;
uint16_t flag[4] = {0x7800, 0x0400, 0x3f00, 0x5a00};
/* USER CODE END Includes */


void Clock_Init(void)
{
    SYS_InitTypeDef SYS_InitStruct;

    SYS_StructInit (&SYS_InitStruct);
    SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;
    SYS_InitStruct.Clk_Sel = CLK_SEL_PLL;
    SYS_InitStruct.PLL_DivSel = BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
    SYS_InitStruct.Clk_DivSPI = SYS_Clk_SPIDiv1;
    SYS_InitStruct.Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct.Clk_FEN = 0;
    SYS_InitStruct.WDT_Ena = DISABLE;
    SYS_InitStruct.PORFilter_Ena = DISABLE;
    /* USER CODE BEGIN Clock_Init */

    /* USER CODE END Clock_Init */
    SYS_Init(&SYS_InitStruct);
}

void Common_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* USER CODE BEGIN Common_GPIOInit */

    /* USER CODE END Common_GPIOInit */
}

void UART0_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);
    /* USER CODE BEGIN UART0_GPIOInit */

    /* USER CODE END UART0_GPIOInit */
}

void UTIMER3_GPIOInit(void)
{
    /* USER CODE BEGIN UTIMER3_GPIOInit */
    
    /* USER CODE END UTIMER3_GPIOInit */
}

void MCPWM0_GPIOInit(void)
{
    /* USER CODE BEGIN MCPWM0_GPIOInit */
		PWMOutputs(DISABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    /* USER CODE END MCPWM0_GPIOInit */
}

void ADC0_GPIOInit(void)
{
    /* USER CODE BEGIN ADC0_GPIOInit */
		ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC_CHANNEL_8, ADC_GAIN3V6); // CH8 will be ADC0 DAT0. Continuous sample will lots of DATx
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC_CHANNEL_0, ADC_GAIN3V6); // CH0 is OPA0, W Phase HO1 CP
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC_CHANNEL_2, ADC_GAIN3V6); // CH2 is OPA2, U Phase HO3 AP
    /* USER CODE END ADC0_GPIOInit */
}

void ADC1_GPIOInit(void)
{
    /* USER CODE BEGIN ADC1_GPIOInit */

    /* USER CODE END ADC1_GPIOInit */
}

void OPA0_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO3, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_5, AF0_GPIO);
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_7, AF0_GPIO);
    /* USER CODE BEGIN OPA0_GPIOInit */
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0,ENABLE);
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2,ENABLE);
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA3,ENABLE);
	
    /* USER CODE END OPA0_GPIOInit */
}

void OPA2_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO3, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_10, AF0_GPIO);
    GPIO_PinAFConfig(GPIO3, GPIO_PinSource_11, AF0_GPIO);
    /* USER CODE BEGIN OPA2_GPIOInit */
    /* USER CODE END OPA2_GPIOInit */
}
//////////////////////////////////////////////////////////////////////////

void UART0_ModuleInit(void)
{
    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 9600;
    UART_InitStruct.WordLength = 0;
    UART_InitStruct.StopBits = 1;
    UART_InitStruct.FirstSend = 0;
    UART_InitStruct.ParityMode = 0;
    UART_InitStruct.MultiDropEna = 0;
    UART_InitStruct.Bit9Value = 0;
    UART_InitStruct.DUPLEX = 0;
    UART_InitStruct.Match485Addr = 0;
    UART_InitStruct.IRQEna = 1;
    UART_InitStruct.DMARE = 1;
    UART_InitStruct.RXD_INV = 0;
    UART_InitStruct.TXD_INV = 0;
    /* USER CODE BEGIN UART0_ModuleInit */
		DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.IRQ_EN = DISABLE;									/* 中断不使能 */
    DMA_InitStruct.CIRC = DISABLE;										/* 使用循环模式 */
    DMA_InitStruct.SINC = ENABLE;											/* 源地址自增 */
    DMA_InitStruct.DINC = DISABLE;										/* 目标地址不自增 */
    DMA_InitStruct.SBTW = DMA_BYTE_TRANS;							/* 源地址访问位宽：字节 */
    DMA_InitStruct.DBTW = DMA_BYTE_TRANS;							/* 目的地址访问位宽：字节 */
    DMA_InitStruct.REN.B.UART0_TX_EN = ENABLE;				/* DAM搬运使能源：UART0_TX */
    DMA_InitStruct.TMS = 2*CH_NUM+1;									/* 数据搬运的次数 */
    DMA_InitStruct.RMODE = ENABLE;										/* 多轮传输使能 */
    DMA_InitStruct.SADR = (u32)((uint8_t *)&send_buff + 1);		/* 源地址 */
    DMA_InitStruct.DADR = (u32)&UART0_BUFF;						/* 目标地址 */
    DMA_InitStruct.EN = ENABLE;												/* 使能通道 */
    DMA_Init(DMA_CHN3, &DMA_InitStruct);							/* DMA通道3用来搬运 */
    /* USER CODE END UART0_ModuleInit */
    UART_Init(UART0, &UART_InitStruct);
}

void UTIMER3_ModuleInit(void)
{
    TIM_TimerInitTypeDef UTIMER_InitStruct;

    TIM_TimerStrutInit(&UTIMER_InitStruct);
    UTIMER_InitStruct.Timer_EN = 1;
    UTIMER_InitStruct.Timer_CAP1_CLR_EN = 0;
    UTIMER_InitStruct.Timer_CAP0_CLR_EN = 0;
    UTIMER_InitStruct.Timer_ONE_TRIG = 0;
    UTIMER_InitStruct.Timer_CENTER = 0;
    UTIMER_InitStruct.Timer_DIR = 0;
    UTIMER_InitStruct.Timer_XCLK_EN = 0;
    UTIMER_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV32;
    UTIMER_InitStruct.Timer_ETON = 0;
    UTIMER_InitStruct.Timer_GATE_EN = 0;
    UTIMER_InitStruct.Timer_RL_EN = 1;
    UTIMER_InitStruct.Timer_CH1Output = 0;
    UTIMER_InitStruct.Timer_CH1_WorkMode = 0;
    UTIMER_InitStruct.Timer_CH1_FE_CAP_EN = 0;
    UTIMER_InitStruct.Timer_CH1_RE_CAP_EN = 0;
    UTIMER_InitStruct.Timer_TH = 96000000;
    UTIMER_InitStruct.Timer_CNT = 0;
    UTIMER_InitStruct.Timer_EVT = 0;
    UTIMER_InitStruct.Timer_FLT = 0;
    UTIMER_InitStruct.Timer_IRQEna = 0;
    /* USER CODE BEGIN UTIMER3_ModuleInit */
    
    /* USER CODE END UTIMER3_ModuleInit */
    TIM_TimerInit(UTIMER3, &UTIMER_InitStruct);
}

void MCPWM0_ModuleInit(void)
{
    MCPWM_InitTypeDef MCPWM_InitStruct;

    MCPWM_StructInit(&MCPWM_InitStruct);
    MCPWM_InitStruct.TH0 = 3000;
    MCPWM_InitStruct.TH1 = 0;
    MCPWM_InitStruct.TH00 = -1500;
    MCPWM_InitStruct.TH01 = 1500;
    MCPWM_InitStruct.TH10 = -1500;
    MCPWM_InitStruct.TH11 = 1500;
    MCPWM_InitStruct.TH20 = -1500;
    MCPWM_InitStruct.TH21 = 1500;
    MCPWM_InitStruct.TH30 = 0;
    MCPWM_InitStruct.TH31 = 0;
    MCPWM_InitStruct.TH40 = 0;
    MCPWM_InitStruct.TH41 = 0;
    MCPWM_InitStruct.TH50 = 0;
    MCPWM_InitStruct.TH51 = 0;
    MCPWM_InitStruct.CMP_CTRL_CNT1 = 0;
    MCPWM_InitStruct.CMP_CTRL_CNT0 = 0;
    MCPWM_InitStruct.BASE_CNT1_EN = 0;
    MCPWM_InitStruct.BASE_CNT0_EN = 1;
    MCPWM_InitStruct.EVT_CNT1_EN = 0;
    MCPWM_InitStruct.EVT_CNT0_EN = 0;
    MCPWM_InitStruct.TMR3_TB = 0;
    MCPWM_InitStruct.TMR2_TB = 0;
    MCPWM_InitStruct.ZCS_EN = 0;
    MCPWM_InitStruct.MCLK_EN = 1;
    MCPWM_InitStruct.CLK_DIV = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH0 = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH1 = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH2 = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH3 = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH4 = 0;
    MCPWM_InitStruct.MCPWM_WorkModeCH5 = 0;
    MCPWM_InitStruct.TMR0 = -2999;
    MCPWM_InitStruct.TMR1 = 0;
    MCPWM_InitStruct.TMR2 = 0;
    MCPWM_InitStruct.TMR3 = 0;
    MCPWM_InitStruct.DeadTimeCH012N = 115;
    MCPWM_InitStruct.DeadTimeCH012P = 115;
    MCPWM_InitStruct.DeadTimeCH345N = 0;
    MCPWM_InitStruct.DeadTimeCH345P = 0;
    MCPWM_InitStruct.EVT0 = 0;
    MCPWM_InitStruct.EVT1 = 0;
    MCPWM_InitStruct.CH0N_Polarity_INV = 0;
    MCPWM_InitStruct.CH0P_Polarity_INV = 0;
    MCPWM_InitStruct.CH1N_Polarity_INV = 0;
    MCPWM_InitStruct.CH1P_Polarity_INV = 0;
    MCPWM_InitStruct.CH2N_Polarity_INV = 0;
    MCPWM_InitStruct.CH2P_Polarity_INV = 0;
    MCPWM_InitStruct.CH3N_Polarity_INV = 0;
    MCPWM_InitStruct.CH3P_Polarity_INV = 0;
    MCPWM_InitStruct.CH4N_Polarity_INV = 0;
    MCPWM_InitStruct.CH4P_Polarity_INV = 0;
    MCPWM_InitStruct.CH5N_Polarity_INV = 0;
    MCPWM_InitStruct.CH5P_Polarity_INV = 0;
    MCPWM_InitStruct.CH0P_SCTRLP = 0;
    MCPWM_InitStruct.CH0N_SCTRLN = 0;
    MCPWM_InitStruct.CH1P_SCTRLP = 0;
    MCPWM_InitStruct.CH1N_SCTRLN = 0;
    MCPWM_InitStruct.CH2P_SCTRLP = 0;
    MCPWM_InitStruct.CH2N_SCTRLN = 0;
    MCPWM_InitStruct.CH3P_SCTRLP = 0;
    MCPWM_InitStruct.CH3N_SCTRLN = 0;
    MCPWM_InitStruct.CH4P_SCTRLP = 0;
    MCPWM_InitStruct.CH4N_SCTRLN = 0;
    MCPWM_InitStruct.CH5P_SCTRLP = 0;
    MCPWM_InitStruct.CH5N_SCTRLN = 0;
    MCPWM_InitStruct.CH0_PS = 0;
    MCPWM_InitStruct.CH0_NS = 0;
    MCPWM_InitStruct.CH1_PS = 0;
    MCPWM_InitStruct.CH1_NS = 0;
    MCPWM_InitStruct.CH2_PS = 0;
    MCPWM_InitStruct.CH2_NS = 0;
    MCPWM_InitStruct.CH3_PS = 0;
    MCPWM_InitStruct.CH3_NS = 0;
    MCPWM_InitStruct.CH4_PS = 0;
    MCPWM_InitStruct.CH4_NS = 0;
    MCPWM_InitStruct.CH5_PS = 0;
    MCPWM_InitStruct.CH5_NS = 0;
    MCPWM_InitStruct.Switch_CH0N_CH0P = 0;
    MCPWM_InitStruct.Switch_CH1N_CH1P = 0;
    MCPWM_InitStruct.Switch_CH2N_CH2P = 0;
    MCPWM_InitStruct.Switch_CH3N_CH3P = 0;
    MCPWM_InitStruct.Switch_CH4N_CH4P = 0;
    MCPWM_InitStruct.Switch_CH5N_CH5P = 0;
    MCPWM_InitStruct.TR0_UP_INTV = 0;
    MCPWM_InitStruct.TR0_T0_UpdateEN = 0;
    MCPWM_InitStruct.TR0_T1_UpdateEN = 0;
    MCPWM_InitStruct.TR0_AEC = 0;
    MCPWM_InitStruct.TR1_UP_INTV = 0;
    MCPWM_InitStruct.TR1_T0_UpdateEN = 0;
    MCPWM_InitStruct.TR1_T1_UpdateEN = 0;
    MCPWM_InitStruct.TR1_AEC = 0;
    MCPWM_InitStruct.FAIL0_INPUT_EN = 0;
    MCPWM_InitStruct.FAIL1_INPUT_EN = 0;
    MCPWM_InitStruct.FAIL_0CAP = 0;
    MCPWM_InitStruct.FAIL0_Signal_Sel = 0;
    MCPWM_InitStruct.FAIL1_Signal_Sel = 0;
    MCPWM_InitStruct.FAIL0_Polarity = 0;
    MCPWM_InitStruct.FAIL1_Polarity = 0;
    MCPWM_InitStruct.HALT_PRT0 = 0;
    MCPWM_InitStruct.FAIL2_INPUT_EN = 0;
    MCPWM_InitStruct.FAIL3_INPUT_EN = 0;
    MCPWM_InitStruct.FAIL_1CAP = 0;
    MCPWM_InitStruct.FAIL2_Signal_Sel = 0;
    MCPWM_InitStruct.FAIL3_Signal_Sel = 0;
    MCPWM_InitStruct.FAIL2_Polarity = 0;
    MCPWM_InitStruct.FAIL3_Polarity = 0;
    MCPWM_InitStruct.HALT_PRT1 = 0;
    MCPWM_InitStruct.CH0P_default_output = 0;
    MCPWM_InitStruct.CH0N_default_output = 0;
    MCPWM_InitStruct.CH1P_default_output = 0;
    MCPWM_InitStruct.CH1N_default_output = 0;
    MCPWM_InitStruct.CH2P_default_output = 0;
    MCPWM_InitStruct.CH2N_default_output = 0;
    MCPWM_InitStruct.CH3P_default_output = 0;
    MCPWM_InitStruct.CH3N_default_output = 0;
    MCPWM_InitStruct.CH4P_default_output = 0;
    MCPWM_InitStruct.CH4N_default_output = 0;
    MCPWM_InitStruct.CH5P_default_output = 0;
    MCPWM_InitStruct.CH5N_default_output = 0;
    MCPWM_InitStruct.CH0N_FAIL_EN = 1;
    MCPWM_InitStruct.CH0P_FAIL_EN = 1;
    MCPWM_InitStruct.CH1N_FAIL_EN = 1;
    MCPWM_InitStruct.CH1P_FAIL_EN = 1;
    MCPWM_InitStruct.CH2N_FAIL_EN = 1;
    MCPWM_InitStruct.CH2P_FAIL_EN = 1;
    MCPWM_InitStruct.CH3N_FAIL_EN = 0;
    MCPWM_InitStruct.CH3P_FAIL_EN = 0;
    MCPWM_InitStruct.CH4N_FAIL_EN = 0;
    MCPWM_InitStruct.CH4P_FAIL_EN = 0;
    MCPWM_InitStruct.CH5N_FAIL_EN = 0;
    MCPWM_InitStruct.CH5P_FAIL_EN = 0;
    MCPWM_InitStruct.T0_Update0_INT_EN = 0;
    MCPWM_InitStruct.T1_Update0_INT_EN = 0;
    MCPWM_InitStruct.TMR0_Match0_INT_EN = 0;
    MCPWM_InitStruct.TMR1_Match0_INT_EN = 0;
    MCPWM_InitStruct.TMR2_Match0_INT_EN = 0;
    MCPWM_InitStruct.TMR3_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH00_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH01_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH10_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH11_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH20_Match0_INT_EN = 0;
    MCPWM_InitStruct.TH21_Match0_INT_EN = 0;
    MCPWM_InitStruct.Update0_INT_EN = 0;
    MCPWM_InitStruct.T0_Update1_INT_EN = 0;
    MCPWM_InitStruct.T1_Update1_INT_EN = 0;
    MCPWM_InitStruct.TMR0_Match1_INT_EN = 0;
    MCPWM_InitStruct.TMR1_Match1_INT_EN = 0;
    MCPWM_InitStruct.TMR2_Match1_INT_EN = 0;
    MCPWM_InitStruct.TMR3_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH00_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH01_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH10_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH11_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH20_Match1_INT_EN = 0;
    MCPWM_InitStruct.TH21_Match1_INT_EN = 0;
    MCPWM_InitStruct.Update1_INT_EN = 0;
    MCPWM_InitStruct.FAIL0_INT_EN = 0;
    MCPWM_InitStruct.FAIL1_INT_EN = 0;
    MCPWM_InitStruct.FAIL2_INT_EN = 0;
    MCPWM_InitStruct.FAIL3_INT_EN = 0;
    MCPWM_InitStruct.IO_CMP_FLT_CLKDIV = 12;
    MCPWM_InitStruct.ZCS0_INT_EN = 0;
    MCPWM_InitStruct.ZCS1_INT_EN = 0;
    MCPWM_InitStruct.IO0_PPE = 0;
    MCPWM_InitStruct.IO1_PPE = 0;
    MCPWM_InitStruct.IO2_PPE = 0;
    MCPWM_InitStruct.IO3_PPE = 0;
    MCPWM_InitStruct.IO4_PPE = 0;
    MCPWM_InitStruct.IO5_PPE = 0;
    MCPWM_InitStruct.TR1_T1_RE1 = 0;
    MCPWM_InitStruct.TR1_T0_RE1 = 0;
    MCPWM_InitStruct.TR0_T1_RE1 = 0;
    MCPWM_InitStruct.TR0_T0_RE1 = 0;
    MCPWM_InitStruct.TMR3_RE1 = 0;
    MCPWM_InitStruct.TMR2_RE1 = 0;
    MCPWM_InitStruct.TMR1_RE1 = 0;
    MCPWM_InitStruct.TMR0_RE1 = 0;
    MCPWM_InitStruct.TR1_T1_RE0 = 0;
    MCPWM_InitStruct.TR1_T0_RE0 = 0;
    MCPWM_InitStruct.TR0_T1_RE0 = 0;
    MCPWM_InitStruct.TR0_T0_RE0 = 0;
    MCPWM_InitStruct.TMR3_RE0 = 0;
    MCPWM_InitStruct.TMR2_RE0 = 0;
    MCPWM_InitStruct.TMR1_RE0 = 0;
    MCPWM_InitStruct.TMR0_RE0 = 0;
    MCPWM_InitStruct.STT_HYST = 0;
    MCPWM_InitStruct.ZCS_DELAY = 0;
    MCPWM_InitStruct.AUEN = 1;
    /* USER CODE BEGIN MCPWM0_ModuleInit */
		
		/*上面是生成的代码，不能用*/
    MCPWM_InitTypeDef MCPWM_InitStructure;
    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;            /* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;       /* 模块时钟开启 */
    MCPWM_InitStructure.IO_CMP_FLT_CLKDIV = 12; /* 急停事件(来自IO口信号)数字滤波器时间设置 */

    MCPWM_InitStructure.AUEN = MCPWM0_TH0_AUPDATE; /*自动加载使能*/

    /* MCPWM0_CNT0	 第一组PWM设置*/

    MCPWM_InitStructure.BASE_CNT0_EN = ENABLE; /* 主计数器开始计数使能开关 */
    MCPWM_InitStructure.TH0 = (u16)(PWM_FRQ/FOC_FRQ/2);            /* 计数周期设置即MCPWM输出周期，这个芯片是从-th计数到th的，因此这个属于整个周期的一半，除以2就是计算这个的*/
																											/*计算方法：96Mhz/想要的foc频率/2.像这里就是96M/10k/2=4800*/
		
    MCPWM_InitStructure.TH00 = (u16)(-0);/*芯片计数到这个值后高脚置1，计到正的置0，因此可以知道这个值越大，占空比越大，和PWM模式1相同*/
    MCPWM_InitStructure.TH01 = (0);
    MCPWM_InitStructure.TH10 = (u16)(-0);
    MCPWM_InitStructure.TH11 = (0);
    MCPWM_InitStructure.TH20 = (u16)(-0);
    MCPWM_InitStructure.TH21 = (0);

    MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
		
    MCPWM_InitStructure.DeadTimeCH012N = (u16)(96); /* 死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH012P = (u16)(96);/*死区时间计算类似，可以理解成这个PWM发生器的计数+1等于多少时间，像这里频率96Mhz那么+1就是0.096ns，想要1000ns那就是96*/

    MCPWM_InitStructure.CMP_CTRL_CNT0 = DISABLE; /* CMP控制CNT0计数使能位 */
    MCPWM_InitStructure.EVT_CNT0_EN = DISABLE;   /* MCPWM_CNT1外部触发使能位 */
    MCPWM_InitStructure.EVT0 = DISABLE;          /* 外部触发 */

    MCPWM_InitStructure.TR0_UP_INTV = DISABLE;
    MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE; /*T0时刻更新使能*/
    MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE;
    MCPWM_InitStructure.TR0_AEC = DISABLE; /*自动清除MCPWM0_EIF标志位*/

    MCPWM_InitStructure.TMR0 = (uint16_t)((int16_T)(PWM_FRQ/FOC_FRQ/2-96)); /* MCPWM_TMR0  设置采样点，一般在低脚导通中点采样，因此是±ARR附近 */
    MCPWM_InitStructure.TMR1 = 0;                /* MCPWM_TMR1 设置，不采第二次所以不管 */

    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
		MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;

    MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE; /* T0更新事件 中断使能位 */
    MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE; /* T1更新事件 中断使能位*/
    MCPWM_InitStructure.Update0_INT_EN = DISABLE;    /* CNT0 更新事件 中断使能  双电阻不使用PWM中断  */

    MCPWM_InitStructure.CH0N_FAIL_EN = ENABLE;
    MCPWM_InitStructure.CH0P_FAIL_EN = ENABLE;
    MCPWM_InitStructure.CH1N_FAIL_EN = ENABLE;
    MCPWM_InitStructure.CH1P_FAIL_EN = ENABLE;
    MCPWM_InitStructure.CH2N_FAIL_EN = ENABLE;
    MCPWM_InitStructure.CH2P_FAIL_EN = ENABLE;

    MCPWM_InitStructure.FAIL0_INPUT_EN = ENABLE; // FAIL_0CAP
    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;
    MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
    MCPWM_InitStructure.FAIL0_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

    MCPWM_InitStructure.FAIL1_INPUT_EN = DISABLE;               // FAIL_1CAP，打开CAP1
    MCPWM_InitStructure.FAIL1_INT_EN = DISABLE;                 // fail中断
    MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
    MCPWM_InitStructure.FAIL1_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

    MCPWM_InitStructure.HALT_PRT0 = ENABLE; /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                           还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
    MCPWM_InitStructure.FAIL_0CAP = ENABLE; // FAIL01事件发生时 将MCPWM0_CNT0值存入MCPWM0_FCNT 使能
		
		PWM_SWAP = 0x67;
    /* USER CODE END MCPWM0_ModuleInit */
    MCPWM_Init(&MCPWM_InitStructure);
}

void ADC0_ModuleInit(void)
{
    ADC_InitTypeDef ADC_InitStruct;

    ADC_StructInit(&ADC_InitStruct);
    ADC_InitStruct.IE = ADC_SF1_IE;//第一次采样完成中断
    ADC_InitStruct.RE = DISABLE;
    ADC_InitStruct.NSMP = DISABLE;
    ADC_InitStruct.DATA_ALIGN = DISABLE;
    ADC_InitStruct.CSMP = DISABLE;
    ADC_InitStruct.TCNT = 0;
    ADC_InitStruct.TROVS = DISABLE;
    ADC_InitStruct.OVSR = 0;
    ADC_InitStruct.TRIG = ADC_TRIG_MCPWM0_T0;
    ADC_InitStruct.S1 = 3;
    ADC_InitStruct.S2 = 0;
    /* USER CODE BEGIN ADC0_ModuleInit */
		ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);
    /* USER CODE END ADC0_ModuleInit */
    ADC_Init(ADC0, &ADC_InitStruct);
}

void ADC1_ModuleInit(void)
{
    ADC_InitTypeDef ADC_InitStruct;

    ADC_StructInit(&ADC_InitStruct);
    ADC_InitStruct.IE = DISABLE;
    ADC_InitStruct.RE = DISABLE;
    ADC_InitStruct.NSMP = DISABLE;
    ADC_InitStruct.DATA_ALIGN = DISABLE;
    ADC_InitStruct.CSMP = DISABLE;
    ADC_InitStruct.TCNT = 0;
    ADC_InitStruct.TROVS = ENABLE;
    ADC_InitStruct.OVSR = 0;
    ADC_InitStruct.TRIG = 0;
    ADC_InitStruct.S1 = 1;
    ADC_InitStruct.S2 = 0;
    ADC_InitStruct.IS1 = 0;
    ADC_InitStruct.GAIN = DISABLE;
    ADC_InitStruct.LTH = 0;
    ADC_InitStruct.HTH = 0;
    ADC_InitStruct.GEN = DISABLE;
    /* USER CODE BEGIN ADC1_ModuleInit */
	
    /* USER CODE END ADC1_ModuleInit */
    ADC_Init(ADC1, &ADC_InitStruct);
}

void OPA0_ModuleInit(void)
{
    OPA_InitTypeDef OPA_InitStruct;
	/*例程里面没有这个函数*/
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0,ENABLE);
		SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2,ENABLE);
	
    OPA_StructInit(&OPA_InitStruct);
	
    OPA_InitStruct.OPA_Gain = PGA_GAIN_32;
    OPA_InitStruct.OPA_CLEna = ENABLE;
    /* USER CODE BEGIN OPA0_ModuleInit */
	OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; /*opa????????????*/
    /* USER CODE END OPA0_ModuleInit */
    OPA_Init(OPA0, &OPA_InitStruct);
    OPA_OUT(OPA0, ENABLE);
}

void OPA2_ModuleInit(void)
{
    OPA_InitTypeDef OPA_InitStruct;

    OPA_StructInit(&OPA_InitStruct);
    OPA_InitStruct.OPA_Gain = PGA_GAIN_32;
    OPA_InitStruct.OPA_CLEna = ENABLE;
    /* USER CODE BEGIN OPA2_ModuleInit */
	OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; /*opa????????????*/
    /* USER CODE END OPA2_ModuleInit */
    OPA_Init(OPA2, &OPA_InitStruct);
    OPA_OUT(OPA2, ENABLE);
}

void SystemInit(void)
{
    Clock_Init();
}

void SoftDelay(u32 cnt)
{
    for(u32 i = 0; i < cnt; i++)
    {
    }
}


/*************** (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE**************/

