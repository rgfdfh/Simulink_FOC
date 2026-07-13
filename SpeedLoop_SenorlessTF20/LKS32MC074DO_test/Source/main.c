// src file: main.c
#include "basic.h"
#include "hardware_init.h"
#include "hardware_config.h"
#include "lks32mc07x.h"
#include "rtt_debug.h"
#include "delay.h"

/* USER CODE BEGIN Includes */
#include "FOC_PointModel.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Defines */


/* USER CODE END Defines */


int main()
{
    __disable_irq();
    Clock_Init();
    /* USER CODE BEGIN Main */
		IWDG_DISABLE();//นุนท

    /* USER CODE END Main */

    Common_GPIOInit();
    UART0_GPIOInit();
    UTIMER3_GPIOInit();
    MCPWM0_GPIOInit();
    ADC0_GPIOInit();
    ADC1_GPIOInit();
    OPA0_GPIOInit();
    OPA2_GPIOInit();

    UART0_ModuleInit();
    UTIMER3_ModuleInit();
    MCPWM0_ModuleInit();
    ADC0_ModuleInit();
    ADC1_ModuleInit();
    OPA0_ModuleInit();
    OPA2_ModuleInit();
    delay_init(MAIN_CLOCK);

		NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_EnableIRQ(TIMER3_IRQn);
    NVIC_EnableIRQ(MCPWM0_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC1_IRQn);
    __enable_irq();

    while(1)
    {
        /* USER CODE BEGIN MainWhile */
        //ADC_SoftTrgEN(ADC0, ENABLE);
				//ADC_SoftTrgEN(ADC1, ENABLE);//software trigger
        delay_ms(100);
        // UART_SendData(UART0,f);
        /* USER CODE END MainWhile */
    }
}


/*************** (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE**************/

