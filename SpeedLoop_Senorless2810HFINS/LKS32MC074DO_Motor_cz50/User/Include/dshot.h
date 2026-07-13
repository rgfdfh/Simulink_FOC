/*
 * @日期: 2025.10.10
 * @作者: lzm
 * @版本号: 
 */
#pragma once
#ifndef __DSHOT_H
#define __DSHOT_H

/*引入系统头文件*/
#include "system.h"
#include "timer.h"

#define DSHOT_SIZE (32) //Dshot缓冲数组长度
#define DSHOT_TYPE (300) //Dshot类型
#define DSHOT_TH (TIMER_FRQ/(DSHOT_TYPE*1000)) //对应dshot类型下一个数据的周期，用于计算占空比
#define DSHOT_0 ((uint16_T)(0.375F*DSHOT_TH)) //标准Dshot0占空比
#define DSHOT_1 ((uint16_T)(0.750F*DSHOT_TH)) //标准Dshot1占空比
#define DSHOT_Err (0.25F) //允许的误差百分比
#define DSHOT_0_MIN (DSHOT_0 - (uint16_T)(DSHOT_0*(DSHOT_Err))) //Dshot0最小值
#define DSHOT_0_MAX (DSHOT_0 + (uint16_T)(DSHOT_0*(DSHOT_Err))) //Dshot0最大值
#define DSHOT_1_MIN (DSHOT_1 - (uint16_T)(DSHOT_1*(DSHOT_Err))) //Dshot1最小值
#define DSHOT_1_MAX (DSHOT_1 + (uint16_T)(DSHOT_1*(DSHOT_Err))) //Dshot1最大值

/* Dshot结构体 */
typedef struct {
		uint32_T Dshot_Check_Cnt; // 无命令计数
    uint32_T Dshot_Check_Frq; // 检测频率
    uint16_T Throttle_Last; // 上次油门值（用于检测重复命令）
    uint16_T Repeat_Cnt; // 重复命令计数
    uint16_T Telemetry; // 请求
    uint16_T DMA_Count; // DMA搬运数据个数
    uint8_T DMA_Stop_Flag; // DMA搬运停止标志
    uint8_T Dshot_Decode_Flag; // 解码标志
		uint8_T Data_Receive_Flag; //回传标志
    uint8_T Direction; // 方向
    uint8_T Telem_Tx_Busy; // 遥测发送状态：1=发送中，0=空闲
    uint8_T Decode_Lock; // 解码过程锁，1=解码中
} Dshot_HandleTypeDef;

extern Dshot_HandleTypeDef Dshot_Handle;
extern uint16_T Dshot_Data[DSHOT_SIZE]; // Dshot数据
extern int16_T DMAtmp;

uint8_T Dshot_Bit_Read(uint16_T dshot_data);
uint16_T Dshot_Get_Data(Dshot_HandleTypeDef *hdshot, uint16_T begin_count, uint8_T *flag);
void Dshot_Check(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD);
void Dshot_Decode(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD);
void Save_Flash_Data(uint8_T dir);
void Read_Flash_Data(uint8_T *dir);



#endif
