#include "opa.h"

void HAL_OPA_Init(void)
{
    HAL_OPA0_Init();
    HAL_OPA2_Init();
		HAL_OPA3_Init();
}

void HAL_OPA0_Init(void)//A
{
    OPA_InitTypeDef OPA_InitStruct;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA0, ENABLE);

    OPA_StructInit(&OPA_InitStruct);
    OPA_InitStruct.OPA_Gain = PGA_GAIN_32;
    OPA_InitStruct.OPA_CLEna = ENABLE;
    OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; // opa偏置电流
    OPA_Init(OPA0, &OPA_InitStruct);
}

void HAL_OPA2_Init(void)//C
{
    OPA_InitTypeDef OPA_InitStruct;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA2, ENABLE);

    OPA_StructInit(&OPA_InitStruct);
    OPA_InitStruct.OPA_Gain = PGA_GAIN_32;
    OPA_InitStruct.OPA_CLEna = ENABLE;
    OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; // opa偏置电流
    OPA_Init(OPA2, &OPA_InitStruct);
}

void HAL_OPA3_Init(void)
{
    OPA_InitTypeDef OPA_InitStruct;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA3, ENABLE);

    OPA_StructInit(&OPA_InitStruct);
    OPA_InitStruct.OPA_Gain = PGA_GAIN_32;
    OPA_InitStruct.OPA_CLEna = ENABLE;
    OPA_InitStruct.OPA_IT = PGA_IT_DISABLE; // opa偏置电流
    OPA_Init(OPA3, &OPA_InitStruct);
}


