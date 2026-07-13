// header file: hardware_init.h
#ifndef _HARDWAREINIT_H
#define _HARDWAREINIT_H

#include "basic.h"
#include "lks32mc07x_lib.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

void Common_GPIOInit(void);
void UART0_GPIOInit(void);
void UTIMER3_GPIOInit(void);
void MCPWM0_GPIOInit(void);
void ADC0_GPIOInit(void);
void ADC1_GPIOInit(void);
void OPA0_GPIOInit(void);
void OPA2_GPIOInit(void);
/* USER CODE BEGIN GPIOs */

/* USER CODE END GPIOs */
//////////////////////////////////////////////////////////////////////////

void Clock_Init(void);
void UART0_ModuleInit(void);
void UTIMER3_ModuleInit(void);
void MCPWM0_ModuleInit(void);
void ADC0_ModuleInit(void);
void ADC1_ModuleInit(void);
void OPA0_ModuleInit(void);
void OPA2_ModuleInit(void);
/* USER CODE BEGIN Periphs */
void SendData_4(int16_t Data_1,int16_t Data_2,int16_t Data_3,int16_t Data_4);
void SendData_12(int16_t Data_1,int16_t Data_2,int16_t Data_3,int16_t Data_4,
								int16_t Data_5,int16_t Data_6,int16_t Data_7,int16_t Data_8,
								int16_t Data_9,int16_t Data_10,int16_t Data_11,int16_t Data_12);
/* USER CODE END Periphs */
void SoftDelay(u32 cnt);

#endif

/*************** (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE**************/

