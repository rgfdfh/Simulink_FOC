/*
 * @日期: 
 * @作者: 
 * @版本号: 
 */
#ifndef __MCPWM_H
#define __MCPWM_H 

/*引入系统头文件*/
#include "system.h"

#define DEAD_TIME (150e-9F) //硬件死区时间，单位s
#define DEAD_TIME_CNT (uint16_T)(DEAD_TIME*PWM_FRQ + 1) //可以理解成这个PWM发生器的计数+1等于多少时间，像这里频率96Mhz那么+1就是1e-8s
#define CHECK_FRQ1 587 * 11 / 4 //自检PWM频率
#define CHECK_FRQ2 700 * 11 / 4
#define CHECK_FRQ3 900 * 11 / 4
#define CHECK_C 587  * 11 / 4
#define CHECK_D 659  * 11 / 4
#define CHECK_E 740  * 11 / 4
#define CHECK_F 784  * 11 / 4
#define CHECK_G 880  * 11 / 4
#define CHECK_A 987  * 11 / 4
#define CHECK_B 1107 * 11 / 4

#define CHECK_DUTY 0.01 //自检PWM占空比,音量
#define CHECK_DUTY1 0.01


void HAL_MCPWM_Init(void);
void Self_Check(int16_T step, float pwm_frq, float duty);

#endif