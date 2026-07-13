/*
 * 
 *    ┏┓　　　┏┓
 *  ┏┛┻━━━┛┻┓
 *  ┃　　　　　　　┃
 *  ┃　　　━　　　┃
 *  ┃　＞　　　＜　┃
 *  ┃　　　　　　　┃
 *  ┃...　⌒　...　┃
 *  ┃　　　　　　　┃
 *  ┗━┓　　　┏━┛
 *      ┃　　　┃　
 *      ┃　　　┃
 *      ┃　　　┃
 *      ┃　　　┃  神兽保佑
 *      ┃　　　┃  代码无bug　　
 *      ┃　　　┃
 *      ┃　　　┗━━━┓
 *      ┃　　　　　　　┣┓
 *      ┃　　　　　　　┏┛
 *      ┗┓┓┏━┳┓┏┛
 *        ┃┫┫　┃┫┫
 *        ┗┻┛　┗┻┛
 */

/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_wake.c\n
 * 文件标识： 无 \n
 * 内容摘要： wake外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年02月23日 <td>1.0    <td>HuangMG    <td>创建
 * </table>
 */

#include "lks32mc07x_wake.h"
#include "lks32mc07x.h"


/**
 * @brief 低功耗初始化结构体定义
 * 
 */
WAKE_InitTypeDef WAKE_InitStruct;

/**
 *@brief @b 函数名称:   static void SoftDelay(u32 cnt)
 *@brief @b 功能描述:   延时函数
 *@see被调用函数：      无
 *@param输入参数：      cnt：延时cnt的空指令_NOP()
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       改函数只在此文件使用，主要用在Switch2PLL函数内      
 *@warning             无
 *@par 示例代码：
 *@code    
           SoftDelay(0xff);//延时255个_NOP()时间1个_NOP大约按一个系统时钟周期计算
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/**
 *@brief @b 函数名称:   void Switch2PLL(void)
 *@brief @b 功能描述:   休眠唤醒后，系统时钟切换到PLL时钟函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗唤醒使用  
 *@warning             无 
 *@par 示例代码：
 *@code    
           Switch2PLL();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2PLL(void)
{
	  SYS_WR_PROTECT = 0x7a83;                        /*开启寄存器写使能*/
    SYS_AFE_REG5 = WAKE_InitStruct.AFE_REG5_RECORD; /*开启 PLL,BGP*/
    SoftDelay(200);
    SYS_CLK_CFG = WAKE_InitStruct.CLK_CFG_RECORD;   /*将主时钟切换到PLL时钟*/
	  SoftDelay(200);
	  SYS_WR_PROTECT = 0x0; 	  
}

/**
 *@brief @b 函数名称:   void Switch2HRC(void)
 *@brief @b 功能描述:   休眠唤醒前一时刻，关闭高速时钟与BGP和掉电检测电路函数
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       系统低功耗休眠使用   
 *@warning             无
 *@par 示例代码：
 *@code    
           Switch2HRC();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void Switch2HRC(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    WAKE_InitStruct.AFE_REG5_RECORD = SYS_AFE_REG5;
	  WAKE_InitStruct.CLK_CFG_RECORD = SYS_CLK_CFG;
	  SYS_CLK_CFG &= 0x0;         /* 切换到HRC时钟*/
	  SYS_AFE_REG5 = 0x0500;    /* 准备关闭 PLL,BGP,即其它模拟电路使能*/  
	  SYS_WR_PROTECT = 0x0; 
}

/**
 *@brief @b 函数名称:    void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
 *@brief @b 功能描述:    设置休眠唤醒IO
 *@see唤醒电平选择枚举：  enumWakeTrigLevel 
 *@param输入参数：                           
 * <table>              <tr><td>
                                wakeIO = BIT11: CLUOUT3_EN  CLUOUT3 作为唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT10: CLUOUT2_EN  CLUOUT2 作为唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT9:  CLUOUT1_EN  CLUOUT1 作为唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT8:  CLUOUT0_EN  CLUOUT0 作为唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT7:  GPIO 2[15] / P2[4]  外部唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT6:  GPIO 2[7]  / P2[4]  外部唤醒使能。1：使能；0：禁用。 \n
                                wakeIO = BIT5:  GPIO 2[4]  / P2[4]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT4:  GPIO 0[14] / P0[14] 外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT3:  GPIO 0[11] / P0[11] 外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT2:  GPIO 0[6]  / P0[6]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT1:  GPIO 0[2]  / P0[2]  外部唤醒使能。1：使能；0：禁用。 \n
 *                              wakeIO = BIT0:  GPIO 0[0]  / P0[0]  外部唤醒使能。1：使能；0：禁用。
 *                      <tr><td>enumWakeTrigLevel : \n
 *                              唤醒电平选择： \n 
 *                              0:低电平唤醒 \n
 *                              1:高电平唤醒 
 *                      <tr><td>flt: \n
 *                              ENABLE： 开启IO滤波 \n
 *                              DISABLE：关闭IO滤波 
 *                      <tr><td>ena: \n
 *                              ENABLE： 开启IO唤醒 \n
 *                              DISABLE：关闭IO唤醒 
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       低功耗IO可以使用多个，但所有IO唤醒信号使用同一个极性选择。    
 *@warning             无 
 *@par 示例代码：
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//系统休眠时,使能P0.0作为低功耗唤醒IO，
           低电平唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
{
	if(ena == ENABLE)
	{
		AON_IO_WAKE_EN |= wakeIO;
	}
	else
	{
		AON_IO_WAKE_EN &= ~wakeIO;
	}
	
	if (trigLevel == WAKETRIG_HIGH)
	{
		AON_IO_WAKE_POL = 0x01;
	}
	else
	{
		AON_IO_WAKE_POL = 0x00;
	}
	
	if(flt == IOWK_FLT_EN)
	{
	  AON_PWR_CFG = BIT1;
	}else{
		AON_PWR_CFG = 0;
	}
}

/**
 *@brief @b 函数名称:   void SYS_FallSleep(void)
 *@brief @b 功能描述:   触发系统进入休眠状态
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无 
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_FallSleep();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_FallSleep(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn); /*关闭TIMER0中断*/
	NVIC_DisableIRQ(TIMER1_IRQn); /*关闭TIMER1中断*/
	NVIC_DisableIRQ(TIMER2_IRQn); /*关闭TIMER2中断*/
	NVIC_DisableIRQ(TIMER3_IRQn); /*关闭TIMER3中断*/
	NVIC_DisableIRQ(QEP0_IRQn); /*关闭QEP0中断*/
	NVIC_DisableIRQ(QEP1_IRQn); /*关闭QEP1中断*/
	NVIC_DisableIRQ(I2C0_IRQn); /*关闭I2C0中断*/
	NVIC_DisableIRQ(SPI0_IRQn); /*关闭SPI0中断*/
	NVIC_DisableIRQ(GPIO_IRQn); /*关闭GPIO中断*/
	NVIC_DisableIRQ(HALL0_IRQn); /*关闭HALL0中断*/
	NVIC_DisableIRQ(UART0_IRQn); /*关闭UART0中断*/
	NVIC_DisableIRQ(UART1_IRQn); /*关闭UART1中断*/
	NVIC_DisableIRQ(DSP0_IRQn); /*关闭DSP0中断*/
	NVIC_DisableIRQ(CMP_IRQn); /*关闭CMP中断*/
	NVIC_DisableIRQ(ADC0_IRQn); /*关闭ADC0中断*/
	NVIC_DisableIRQ(ADC1_IRQn); /*关闭ADC1中断*/
	NVIC_DisableIRQ(MCPWM0_IRQn); /*关闭MCPWM0中断*/
	NVIC_DisableIRQ(MCPWM1_IRQn); /*关闭MCPWM1中断*/
	NVIC_DisableIRQ(DMA0_IRQn); /*关闭DMA0中断*/
	NVIC_DisableIRQ(CAN0_IRQn); /*关闭CAN0中断*/
	NVIC_DisableIRQ(SIF0_IRQn); /*关闭SIF0中断*/
	NVIC_DisableIRQ(SW_IRQn); /*关闭SW中断*/
	NVIC_DisableIRQ(PWRDN_IRQn); /*关闭PWRDN中断*/
	NVIC_DisableIRQ(CL0_IRQn); /*关闭CL0中断*/

	IWDG_PSW = 0xA6B4;
	IWDG_CLR = 0x798D;
	SCB->SCR |= (1UL << 2);
	 __WFI();	  /*PC指针停止运行，等待中断*/
}

/**
 *@brief @b 函数名称:   void SYS_EVTCLRSleep(void)
 *@brief @b 功能描述:   清除休眠全部事件记录
 *@see被调用函数：      无
 *@param输入参数：      无
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无 
 *@warning             无
 *@par 示例代码：
 *@code    
           SYS_EVTCLRSleep();
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_EVTCLRSleep(void)
{
	 AON_EVT_RCD = PSW_EVT_CLR;/* 清除全部事件记录*/
}

/**
 *@brief @b 函数名称:    void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
 *@brief @b 功能描述:    设置休眠唤醒周期
 *@see被调用函数：  无
 *@param输入参数：                           
 * <table>
 *                     <tr><th>rth <td>看门狗超时复位门限值，也是重新装载值(最大值0x1FF000)
 *                     <tr><th>wth <td>看门狗定时唤醒门限值(最大值小于rth)
 *                     <tr><th>ena <td>ENABLE：开启定时唤醒  DISABLE：关闭定时唤醒  
 * </table>
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       
 *               唤醒时间计算公式：
 *               WakeupIWDG = tLRC * (rth - Iwth) 
 *               tLRC 为 LRC时钟周期，1/32kHz=31.25uS
 *</table>
 *               <tr><th>rth - wth  * （tLRC） =  <td>唤醒时间
 *               <tr><th>   8000    * 31.25uS  =  <td>0.25S
 *               <tr><th>   16000   * 31.25uS  =  <td>0.5S
 *               <tr><th>   32000   * 31.25uS  =  <td>1S
 *               <tr><th>   64000   * 31.25uS  =  <td>2S
 *               <tr><th>   128000  * 31.25uS  =  <td>4S  
 *</table> 
 *@warning             无 
 *@par 示例代码：
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//系统休眠时,使能P0.0作为低功耗唤醒IO，
           低电平唤醒
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2023年02月22日 <td>1.0     <td>HuangMG      <td>创建
 * </table>
 */
void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
{ 
	 if(ena == ENABLE)
	 { 
	   IWDG_CFG |= 0x01 << 4; /*深度休眠定时唤醒使能*/
	 }else{
		 IWDG_CFG &= ~(0x01 << 4); /*关闭深度休眠定时唤醒*/
	 }
	  IWDG_PSW = 0xA6B4;     /*使能看门狗部分寄存器写操作*/
	  IWDG_RTH = rth;
	  IWDG_WTH = wth;
}







