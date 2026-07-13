#ifndef __TIMER_H
#define __TIMER_H

/*引入系统头文件*/
#include "system.h"


#define MCU_CLK 9.6E+7F //芯片主频
#define TIMER_FRQ 9.6E+7F //定时器工作频率

void HAL_Timer_Init();
void HAL_Timer3_Init();
void HAL_SysTick_Init(uint32_T frq);
#endif


