/*
 * @日期: 2025.10.10
 * @作者: lzm
 * @版本号:1.0
 */

#include "basic.h"
#include "lks32mc07x_sys.h"
#include "rtt_debug.h"
/***********************************/
#include "system.h"
#include "gpio.h"
#include "timer.h"
#include "mcpwm.h"
#include "adc.h"
#include "opa.h"
#include "dshot.h"
/***********************************/
#include "FOC_PointModel.h"
Rtt_HandleTypeDef Rtt_Handle;
int32_T check_data[3];
int16_T rtt_buffer[256];
int16_T zero_cnt;
int32_T iwzero, iuzero, vdczero;
boolean_T Led_State = 0; // 按钮用
boolean_T Motor_State = 0, Slow_State = 0;
int main(void)
{
	__disable_irq(); // 关闭中断 中断总开关
	SYS_WR_PROTECT = 0x7a83;
	Clock_Init();	// 没用，但是有所以我写了
	IWDG_DISABLE(); // 关狗

	/*硬件初始化*/
	HAL_GPIO_Init();
//	HAL_Timer_Init();
	HAL_MCPWM_Init();
	HAL_ADC_Init();
	HAL_OPA_Init();
	SoftDelay(100); // 等待硬件初始化完毕

	for (int16_T i = 0; i < 64; i++)
	{
		iuzero += ADC_GetConversionValue(ADC0, DAT0); // A
		iwzero += ADC_GetConversionValue(ADC0, DAT1); // C
	}

	iuzero = (iuzero >> 6);
	iwzero = (iwzero >> 6);

	Self_Check(1, CHECK_FRQ1, CHECK_DUTY); /*AHCL*/
	delay_ms(150);
	check_data[0] = ADC_GetConversionValue(ADC0, DAT1) - (int16_T)iwzero;

	Self_Check(2, CHECK_FRQ1, CHECK_DUTY); /*BHCL*/
	delay_ms(150);
	check_data[1] = ADC_GetConversionValue(ADC0, DAT1) - (int16_T)iwzero;

	Self_Check(3, CHECK_FRQ1, CHECK_DUTY); /*BHAL*/
	delay_ms(150);
	check_data[2] = ADC_GetConversionValue(ADC0, DAT0) - (int16_T)iuzero;

	PWMOutputs(DISABLE);
	for (int8_T i = 0; i < 3; i++)
	{
		if (check_data[i] < 0)
		{
			delay_ms(400);
//			while (1)
//			{
//				Self_Check(1, CHECK_C, CHECK_DUTY1); /*AHCL*/
//				delay_ms(300);
//				PWMOutputs(DISABLE);delay_ms(100);
//				Self_Check(2, CHECK_C, CHECK_DUTY1); /*BHCL*/
//				delay_ms(300);
//				PWMOutputs(DISABLE);delay_ms(100);
//				Self_Check(3, CHECK_C, CHECK_DUTY1); /*BHAL*/
//				delay_ms(300);
//				PWMOutputs(DISABLE);delay_ms(800);
//			}
		}
	}
	delay_ms(200);
	Self_Check(1, CHECK_FRQ2, CHECK_DUTY);
	delay_ms(400);
	Self_Check(3, CHECK_FRQ3, CHECK_DUTY);
	delay_ms(400);
	HAL_MCPWM_Init(); // 重新初始化
//	HAL_SysTick_Init(16384);
	SoftDelay(100);	  // 等待硬件初始化完毕
	vdczero = 0;
	iwzero = 0;
	iuzero = 0;					 // 个人认为需要在进入等待后再次真正采集64次飘零，这里是使用ADC中断中进行采集，可以保证64次每次都是新的值。
	Read_Flash_Data(&Dshot_Handle.Direction); // 读取方向
	PWMOutputs(DISABLE);

//	NVIC_SetPriority(SysTick_IRQn, 2); // SysTick中断优先级
	NVIC_SetPriority(ADC0_IRQn, 1);	   // ADC中断优先级
	NVIC_SetPriority(GPIO_IRQn, 0);

//	NVIC_EnableIRQ(SysTick_IRQn); // 使能SysTick中断
	NVIC_EnableIRQ(ADC0_IRQn);	  // 使能ADC中断
	NVIC_EnableIRQ(GPIO_IRQn); // 外部gpio中断

	__enable_irq();					   // 开启总中断
	PWMOutputs(DISABLE);			   // 关闭PWM
	rtU.Motor_OnOff = 0;			   // 关闭FOC代码
	rtU.Slow_OnOff = 0;				   // 关闭慢速
	Dshot_Handle.Dshot_Check_Cnt = 0; //重置通信超时计数
	GPIO_ResetBits(GPIO0, GPIO_Pin_7); // 关闭代码指示灯
	while (1)
	{
//		if(Dshot_Handle.Dshot_Check_Cnt >= Dshot_Handle.Dshot_Check_Frq)
//		{
//			NVIC_DisableIRQ(ADC0_IRQn);
//			Self_Check(1, CHECK_C, CHECK_DUTY1);SoftDelay(960000*3);
//			PWMOutputs(DISABLE);SoftDelay(960000*5);
//			Self_Check(2, CHECK_C, CHECK_DUTY1*2);SoftDelay(960000*3);
//			PWMOutputs(DISABLE);SoftDelay(960000*5);
//			Self_Check(3, CHECK_C, CHECK_DUTY1);SoftDelay(960000*3);
//			PWMOutputs(DISABLE);SoftDelay(960000*5);
//			Dshot_Handle.Dshot_Check_Cnt = 0;
//			HAL_MCPWM_Init(); // 重新初始化
//			SoftDelay(100);
//			NVIC_EnableIRQ(ADC0_IRQn);	  // 使能ADC中断
//		}
//		Dshot_Decode(&Dshot_Handle, &Motor_State, &Slow_State, &rtU.Spd_Ref);
	}
}
/**
 * @description: ADC0中断函数,处理绝大部分任务，主要是FOC计算、ADC数据采集后转换
 * @return {*}
 */
int32_T iw, iu, iv, vdc;
uint16_T tcmpW, tcmpV, tcmpU;
int32_T time,tmp;
void ADC0_IRQHandler(void)
{
	if (ADC_GetIRQFlag(ADC0, ADC_SF1_IF))
	{
		GPIO_SetBits(GPIO0, GPIO_Pin_5); // 进入adc中断指示
		if (zero_cnt < 64)// 采集飘零值
		{
			PWMOutputs(DISABLE);
			vdczero += ADC_GetConversionValue(ADC1, DAT0);
			iuzero += ADC_GetConversionValue(ADC0, DAT0);
			iwzero += ADC_GetConversionValue(ADC0, DAT1);
			zero_cnt++;
		}
		else if (zero_cnt == 64)//飘零平均值、初始化FOC
		{
			vdczero = (vdczero >> 6);
			iuzero = (iuzero >> 6);
			iwzero = (iwzero >> 6);
			zero_cnt++;
			FOC_PointModel_initialize();
		}
		if (zero_cnt > 64)
		{
			vdc = (int32_T)ADC_GetConversionValue(ADC1, DAT0);
			iu = (int32_T)ADC_GetConversionValue(ADC0, DAT0) - iuzero; // 哪个相对应哪个adc的DAT在adcgpio初始化中确定
			iw = (int32_T)ADC_GetConversionValue(ADC0, DAT1) - iwzero; // 返回值是s16，有符号的
			iw = ((iw > 32767) ? 32767 : (iw < -32767) ? -32767
													   : iw);
			iu = ((iu > 32767) ? 32767 : (iu < -32767) ? -32767
													   : iu);
			iv = -(iw + iu);
//			 time++; // 这里会自动变转速
//			 if (time > 25000 * 3)
//			 {
//			 	rtU.Spd_Ref = 5000;
//			 }
//			 if (time > 25000 * 6)
//			 {
//			 	rtU.Spd_Ref = 5000;
//			 }
//			 if (time > 25000 * 9)
//			 {
//			 	time = 0;
//			 }
			if (Dshot_Handle.Direction) // 1正转，0反转
			{
				rtU.ia = (int32_T)iu;
				rtU.ib = (int32_T)iv;
				rtU.ic = (int32_T)iw;
				rtU.v_bus = (int32_T)vdc;
			}
			else
			{
				rtU.ia = (int32_T)iw;
				rtU.ib = (int32_T)iv;
				rtU.ic = (int32_T)iu;
				rtU.v_bus = (int32_T)vdc;
			}
			time++; // 这里会自动变转速，和上面的dshot二选一
			if (time > 2500 * 2)
			{
			rtU.Spd_Ref = 7000;
			}
			if (time > 2500 * 4)
			{
			rtU.Spd_Ref = 5000;
//			time--;
			}
			if (time > 2500 * 6)
			{
			time = 0;
			}
//			rtU.Spd_Ref = 7000;
			SysTick->LOAD=9600;
			SysTick->CTRL=0X05;
			SysTick->VAL=0;
			FOC_PointModel_step();
			tmp=9600-SysTick->VAL;
			SysTick->CTRL=0;    //关闭计数器
			SysTick->VAL=0;     //清空计数器
			if (rtY.Reset == 1) // 过流保护
			{
				PWMOutputs(DISABLE);						 // 开关PWM
				rtU.Motor_OnOff = Led_State;						 // FOC代码开关
				GPIO_WriteBit(GPIO0, GPIO_Pin_7, Bit_RESET); // 指示灯开关
			}
			else
			{
				 PWMOutputs(Led_State);						 // 开关PWM
				 GPIO_WriteBit(GPIO0, GPIO_Pin_7, Led_State); // 指示灯开关
				 rtU.Motor_OnOff = Led_State;				 // FOC代码开关
				/***********************下面的是dshot时用的，上面是按钮用的**************************** */
//				PWMOutputs(Motor_State || Slow_State); // 开关PWM
//				rtU.Motor_OnOff = Motor_State;		   // FOC代码开关
//				rtU.Slow_OnOff = Slow_State;		   // 慢速开关
			}
			if (Dshot_Handle.Direction)//1正转，0反转
			{
				tcmpU = rtY.tABC[0];
				tcmpV = rtY.tABC[1];
				tcmpW = rtY.tABC[2];
			}
			else
			{
				
				tcmpU = rtY.tABC[2];
				tcmpV = rtY.tABC[1];
				tcmpW = rtY.tABC[0];
			}
			MCPWM0_TH00 = (uint16_T)(-tcmpU);
			MCPWM0_TH01 = (tcmpU);
			MCPWM0_TH10 = (uint16_T)(-tcmpV);
			MCPWM0_TH11 = (tcmpV);
			MCPWM0_TH20 = (uint16_T)(-tcmpW);
			MCPWM0_TH21 = (tcmpW);
		}
		ADC_ClearIRQFlag(ADC0, ADC_SF1_IF);
		GPIO_ResetBits(GPIO0, GPIO_Pin_5); // 退出adc中断指示
	}
}

/**
 * @description: SysTick中断函数,用于定时任务
 * @return {*}
 */
void SysTick_Handler(void)
{
	Dshot_Check(&Dshot_Handle, &Motor_State, &Slow_State, &rtU.Spd_Ref); // 检测dshot信号
//	Dshot_Decode(&Dshot_Handle, &Motor_State, &Slow_State, &rtU.Spd_Ref);
	SysTick->CTRL &= ~(1 << 16); // 清除计数标志位
}

/**
 * @description: GPIO中断函数
 * @return {*}
 */
void GPIO_IRQHandler(void)
{
	if (EXTI_GetIRQFlag(GPIO0, GPIO_PinSource_14))
	{
		if (zero_cnt > 64)
		{
			Led_State = !Led_State;						 // 状态反转
			PWMOutputs(Led_State);						 // 开关PWM
			rtU.Motor_OnOff = Led_State;				 // FOC代码开关
			GPIO_WriteBit(GPIO0, GPIO_Pin_7, Led_State); // 指示灯开关
		}

		EXTI_ClearIRQFlag(GPIO0, GPIO_PinSource_14);
	}
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
