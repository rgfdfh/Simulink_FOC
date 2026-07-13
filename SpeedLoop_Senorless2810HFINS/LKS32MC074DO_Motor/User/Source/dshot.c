/*
 * @日期: 2025.10.10
 * @作者: lzm
 * @版本号: 1.3
 */
#include "dshot.h"
#include "timer.h"

Dshot_HandleTypeDef Dshot_Handle={0}; // 定义Dshot结构体
uint16_T Dshot_Data[DSHOT_SIZE]; // Dshot数据

/**
 * @函数名称: dshot数据辨识
 * @功能描述: 根据占空比大小返回0/1，错误则为2
 * @param {uint16_T} dshot_data
 */
uint8_T Dshot_Bit_Read(uint16_T dshot_data)
{
    uint8_T result = 2; // 默认错误
    if (dshot_data >= DSHOT_0_MIN && dshot_data <= DSHOT_0_MAX)
        result = 0;
    if (dshot_data >= DSHOT_1_MIN && dshot_data <= DSHOT_1_MAX)
        result = 1;
    return result;
}

/**
 * @函数名称:
 * @功能描述: 将DMA数据进行解码
 */
uint16_T Dshot_Get_Data(Dshot_HandleTypeDef *hdshot, uint16_T begin_count, uint8_T *flag)
{
    uint16_T result = 0;
		*flag = 1;
    for (uint8_T i = begin_count; i < hdshot->DMA_Count; i++)
    {
        uint8_T bit = Dshot_Bit_Read(Dshot_Data[i]);
        if (bit == 2)
        {
            result = 0;
            *flag = 0;
            break;
        }
        else
        {
            result = (result << 1) | (bit & 0x01);
        }
    }
    return result;
}

/**
 * @函数名称:
 * @功能描述: 检测是否有数据传过来
 */
void Dshot_Check(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD)
{
    hdshot->Dshot_Check_Cnt++;
    if (hdshot->Dshot_Check_Cnt > hdshot->Dshot_Check_Frq) // 1秒无命令则认为关机
    {
        hdshot->Dshot_Check_Cnt = hdshot->Dshot_Check_Frq;
        *state = 0;
        *slow = 0;
        *SPD = 0;
    }

    if (hdshot->DMA_Count == DSHOT_SIZE - DMA_CHN0->CTMS)
    {
        hdshot->DMA_Stop_Flag++; // 搬运结束
				if(hdshot->DMA_Stop_Flag > 250)
				{
					hdshot->DMA_Stop_Flag = 250;
				}
    }
    else
    {
        hdshot->DMA_Stop_Flag = 0;
    }

    hdshot->DMA_Count = DSHOT_SIZE - DMA_CHN0->CTMS; // 记录个数

    if (DSHOT_SIZE - DMA_CHN0->CTMS >= 0 && hdshot->DMA_Stop_Flag > 1) // 发生搬运且搬运结束
    {
        hdshot->Dshot_Decode_Flag = 1;
				DMA_CHN0->CCR &= ~BIT0;      // 关闭DMA
        DMA_CHN0->CTMS = DSHOT_SIZE; // 重置搬运个数
    }
}

/**
 * @函数名称:
 * @功能描述: dshot数据获取
 */
void Dshot_Decode(Dshot_HandleTypeDef *hdshot, boolean_T *state, boolean_T *slow, int32_T *SPD)
{
    uint8_T Data_Correct_Flag = 0; // 数据正确标志
    uint16_T result = 0;           // 解码结果
    uint8_T CRC = 0;               // CRC校验
    if (hdshot->Dshot_Decode_Flag == 1)
    {
        if (hdshot->DMA_Count >= 16) // 至少16个数据才进行解码
        {
            result = Dshot_Get_Data(hdshot, hdshot->DMA_Count - 16, &Data_Correct_Flag);
        }

        if (Data_Correct_Flag == 1) // 数据正确才往下
        {
            CRC = result & 0x0F;
            result = result >> 4;
            if (CRC == (((result ^ (result >> 4) ^ (result >> 8)) & 0x0F))) // CRC校验
            {
								hdshot->Dshot_Check_Cnt = 0;               // 有命令，计数清零
                hdshot->Throttle = (result >> 1) & 0x07FF; // 11位油门值
                hdshot->Telemetry = (result) & 0x01;       // 请求

								if (hdshot->Throttle > 47 && hdshot->Throttle < 2048) // 48~2047为油门值，并映射到转速
                {
                    *state = 1;
                    *slow = 0;
                    *SPD = SPD_MIN + ((hdshot->Throttle - 47) * ((SPD_MAX - SPD_MIN) / 2000));
                }
								
								if (hdshot->Throttle == hdshot->Throttle_Last)
                {
                    hdshot->Repeat_Cnt++; // 重复命令计数
                    if (hdshot->Repeat_Cnt > 60000U)
                        hdshot->Repeat_Cnt = 60000U;
                }
                else
                {
                    hdshot->Repeat_Cnt = 0;
                }
								hdshot->Throttle_Last = hdshot->Throttle; // 记录上次油门值
								
                if (hdshot->Throttle < 37 && *state == 0 && hdshot->Repeat_Cnt > 6)
                {
                    switch (hdshot->Throttle)
                    {
                    case 7: // 永久方向0
                        hdshot->Direction = 0;
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 8: // 永久方向1
                        hdshot->Direction = 1;
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 12: // 写入
                        Save_Flash_Data(hdshot->Direction);
                        break;
                    case 15: // 慢转
                        *state = 0;
												*slow = 1;
												*SPD = 0;
                        break;
                    case 20: // 临时方向0
                        hdshot->Direction = 0;
                        break;
                    case 21: // 临时方向1
                        hdshot->Direction = 1;
                        break;
                    }
                }
								if (hdshot->Throttle == 0) // 0油门认为关机
                {
                    *state = 0;
                    *slow = 0;
                    *SPD = 0;
                }
            }
        }
				//memset(Dshot_Data, 0, sizeof(Dshot_Data));
        hdshot->Dshot_Decode_Flag = 0; // 清除标志
        DMA_CHN0->CCR |= BIT0; // 重新开启DMA
    }
}

/**********************************************FLASH相关******************************************************************* */
void Save_Flash_Data(uint8_T dir)
{
    erase_flag = 0x9A0D361F;             // c擦除解锁
    EraseSector(0x0, Flash_NVR);         // 擦除flash的NVR区域即独立的1KB用户存储区
    erase_flag = 0;                      // 擦除上锁
    progm_flag = 0x9AFDA40C;             // 编程解锁
    ProgramPage(0x0, 1, &dir, Flash_NVR); // 编程flash的NVR区域即独立的1KB用户存储区
    progm_flag = 0;                      // 编程上锁
}

void Read_Flash_Data(uint8_T *dir)
{
    Read_More_Flash(0x0, 1, (uint32_T *)(dir), Flash_NVR); // 读取NVR区域数据
}
