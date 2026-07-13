#include "gpio.h"

void HAL_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;//gpio0.5为led灯引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	
	  GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//gpio0.7为led灯引脚
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_PODEna = DISABLE;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
	
		GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStruct.GPIO_PFLT = ENABLE;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		EXTI_Trigger_Config(GPIO0,GPIO_PinSource_14,EXTI_Trigger_Negedge);//gpio0.14为外部中断脚，下降沿触发
}