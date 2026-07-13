/*
 * @日期:2026.1.29
 * @作者:lzm
 * @版本号:V0.1
 */
#pragma once
#ifndef __DSHOT_BIDIR_H
#define __DSHOT_BIDIR_H

/*引入系统头文件*/
#include "system.h"
#include "dshot.h" // 引入DSHOT_TH，用于双向速率宏

// 双向DShot 5/4速率下的周期（更快：5/4倍频率 → 周期按5/4放大）
#define DSHOT_TH_5_4 ((uint16_T)((DSHOT_TH * 4) / 5))

/* DShot 类型 */
typedef enum {
	DSHOT_TYPE_UNKNOWN = 0,
	DSHOT_TYPE_NORMAL = 1,   // 普通 DShot（空闲低电平）
	DSHOT_TYPE_BIDIR = 2     // 双向 DShot（空闲高电平，反相）
} Dshot_Type_e;

/* 存储检测到的 DShot 类型，用于定时器初始化和后续解码分支选择 */
extern Dshot_Type_e Dshot_Type;

/* 根据 GPIO 电平统计检测 DShot 类型
 * 固定时间采样，统计高/低电平占比，无法确定时默认普通 DShot
 * 返回检测到的 DShot 类型，调用方需存储到全局变量 Dshot_Type
 */
Dshot_Type_e Dshot_Detect_Type_By_Level(void);

/* 根据全局变量中存储的类型初始化定时器与 DMA */
void Dshot_Init_Capture_By_Type(Dshot_Type_e detect_type);

/* 双向DShot遥测数据帧结构（21位） */
typedef struct {
	uint8_T bit_count;  // 0=写入中，20=写入完成
} Dshot_Bidir_Frame_t;

/* 全局遥测帧实例，用于存储编码后的双向DShot遥测数据 */
extern Dshot_Bidir_Frame_t Dshot_Bidir_Frame;

/* 将转速值编码为双向DShot遥测帧（电调端发送）
 * 输入：rpm - 电机转速（单位：rpm）
 *       pole_pair_num - 电机极对数
 * 输出：frame - 编码后的21位遥测帧，可用于GPIO/PWM发送
 * 返回：0=成功，-1=失败
 * 
 * 内部流程：
 * 1. 计算eRPM = rpm × pole_pair_num × 2（电气转速）
 * 2. 编码为16位遥测数据：3位指数 + 9位周期基数 + 4位CRC
 * 3. GCR编码+变换为21位帧
 */
int Dshot_Bidir_Encode_Telemetry(uint32_T rpm, uint8_T pole_pair_num, Dshot_Bidir_Frame_t *frame);

/* 切换到发送模式：关闭接收DMA_CHN0，启用发送DMA_CHN1
 * 功能：
 *   1. 关闭DMA_CHN0（接收模式）
 *   2. 切换Timer_CH0为比较输出模式
 *   3. 启用DMA_CHN1（发送模式）
 *   4. 启动Timer计数
 * 发送速率：DShot 5/4 @ 96MHz = 375kHz（每bit=256个时钟周期）
 */
void Dshot_Init_Transmit_By_Frame(void);


/* 发送完成后切换回接收模式
 * 功能：
 *   1. 停止Timer计数
 *   2. 关闭DMA_CHN1（发送模式）
 *   3. 切换Timer_CH0回到捕获模式
 *   4. 启用DMA_CHN0（接收模式）
 *   5. 重启Timer计数进行接收
 */
void Dshot_Exit_Transmit_Mode(void);

#endif /* __DSHOT_BIDIR_H */
