/*
 * @日期: 
 * @作者: 
 * @版本号: 
 */
#include "adc.h"

void HAL_ADC_Init(void)
{
    HAL_ADC0_Init();
    HAL_ADC1_Init();
}

void HAL_ADC0_Init(void)
{
    ADC_InitTypeDef ADC_InitStruct;

    ADC_StructInit(&ADC_InitStruct);
    ADC_InitStruct.IE = ADC_SF1_IE;           // 第一段常规采样完成中断
    ADC_InitStruct.RE = DISABLE;              // DMA不使能
    ADC_InitStruct.NSMP = DISABLE;            // 一段采样
    ADC_InitStruct.DATA_ALIGN = DISABLE;      // 不右对齐
    ADC_InitStruct.CSMP = DISABLE;            // 不连续采样
    ADC_InitStruct.TCNT = 0;                  // 触发ADC采样事件数
    ADC_InitStruct.TROVS = DISABLE;           // 是否手动触发
    ADC_InitStruct.OVSR = 0;                  // 无过采样
    ADC_InitStruct.TRIG = ADC_TRIG_MCPWM0_T0; // ADC触发时机
    ADC_InitStruct.S1 = 2;                    // 第一段采样次数
    ADC_InitStruct.S2 = 0;                    // 第二段采样次数

    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);
    ADC_Init(ADC0, &ADC_InitStruct);

    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC_CHANNEL_3, ADC_GAIN3V6); // CH3是OPA0, W相A，用PWM1组
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC_CHANNEL_2, ADC_GAIN3V6); // CH2是OPA2, U相C，用PWM3组
		//ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC_CHANNEL_8, ADC_GAIN3V6);  //母线电压
}

void HAL_ADC1_Init()
{
    ADC_InitTypeDef ADC_InitStruct;

    ADC_StructInit(&ADC_InitStruct);     // ADC1暂留用作软键触发采母线电压
    //ADC_InitStruct.IE = ADC_SF1_IE;      // 第一段常规采样完成中断
    ADC_InitStruct.RE = DISABLE;         // DMA不使能
    ADC_InitStruct.NSMP = DISABLE;       // 一段采样
    ADC_InitStruct.DATA_ALIGN = DISABLE; // 不右对齐
    ADC_InitStruct.CSMP = DISABLE;       // 不连续采样
    ADC_InitStruct.TCNT = 0;             // 触发ADC采样事件数
    ADC_InitStruct.TROVS = DISABLE;       // 是否手动触发
    ADC_InitStruct.OVSR = 0;             // 无过采样
    ADC_InitStruct.TRIG = ADC_TRIG_MCPWM0_T0;     // ADC触发时机
    ADC_InitStruct.S1 = 1;               // 第一段采样次数
    ADC_InitStruct.S2 = 0;               // 第二段采样次数

	  ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);
    ADC_Init(ADC1, &ADC_InitStruct);
	
    ADC_CHN_GAIN_CFG(ADC1, CHN0, ADC_CHANNEL_12, ADC_GAIN3V6); // CH12是母线电压值，采样次数中多次采样顺序对应CHNx、DATx
    // ADC_SoftTrgEN(ADC0,ENABLE);//软件触发一次ADC采样
}