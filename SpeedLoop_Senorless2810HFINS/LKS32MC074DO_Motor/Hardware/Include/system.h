/*
 * @日期:2025.10.28 
 * @作者: lzm
 * @版本号: 1.0
 */
#ifndef __System_H
#define __System_H


/*引入标准头文件*/
#include "basic.h"
#include "lks32mc07x_sys.h"
/*引入参数头文件*/
#include "FOC_PointModel.h"

typedef struct {
    int16_T data0;
    int16_T data1;
    int16_T data2;
}Rtt_HandleTypeDef;

extern Rtt_HandleTypeDef Rtt_Handle;

void SystemInit(void);
void Clock_Init(void);
void delay_ms(u32 i);
void delay_us(u32 i);
void SoftDelay(u32 cnt);

#endif