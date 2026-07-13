#include "system.h"


/*系统时钟初始化函数，在main开始前自动执行*/
void SystemInit(void)
{
    /* 时钟初始化 */
	  SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_AFE_REG5 = BIT15;      /* BIT15:PLLPDN 开PLL */
    SoftDelay(100);            /* 延时100us, 等待PLL稳定 21.4.17*/
    SYS_CLK_CFG = 0x000001ff;  /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
    SYS_WR_PROTECT = 0;        /* 关闭系统寄存器写操作*/
		
		//Clock_Init();
}

void Clock_Init(void)
{
		SYS_InitTypeDef SYS_InitStruct;

		SYS_StructInit (&SYS_InitStruct);
		SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;
		SYS_InitStruct.Clk_Sel = CLK_SEL_PLL;
		SYS_InitStruct.PLL_DivSel = BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
		SYS_InitStruct.Clk_DivSPI = SYS_Clk_SPIDiv1;
		SYS_InitStruct.Clk_DivUART = SYS_Clk_UARTDiv1;
		SYS_InitStruct.Clk_FEN = 0;
		SYS_InitStruct.WDT_Ena = DISABLE;
		SYS_InitStruct.PORFilter_Ena = DISABLE;
		SYS_Init(&SYS_InitStruct);
}

/*寄存器清零函数*/
void Reg_Clr(u32 addr, u8 nSize)
{
   while(nSize --)
   {
      REG32(addr) = 0;
      addr += 4;
   }
}

/*软件延时函数*/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/*硬件延时函数*/
void delay_us(u32 i)
{
    u32 temp;
		for(uint16_t cnt=0;cnt<i;cnt++)
		{
			SysTick->LOAD=96;       	 //设置重装数值, 96MHZ
			SysTick->CTRL=0X05;        //使能，减到零是无动作，采用外部时钟源
			SysTick->VAL=0;            //清零计数器
			do
			{
					temp=SysTick->CTRL;       //读取当前倒计数值
			}
			while((temp&0x01)&&(!(temp&(1<<16))));    //等待时间到达
			SysTick->CTRL=0;    //关闭计数器
			SysTick->VAL=0;     //清空计数器
		}
}
/*硬件延时函数*/
void delay_ms(u32 i)
{
    u32 temp;
		for(uint16_t cnt=0;cnt<i;cnt++)
		{
			SysTick->LOAD=96000;       //设置重装数值, 96MHZ
			SysTick->CTRL=0X05;        //使能，减到零是无动作，采用外部时钟源
			SysTick->VAL=0;            //清零计数器
			do
			{
					temp=SysTick->CTRL;       //读取当前倒计数值
			}
			while((temp&0x01)&&(!(temp&(1<<16))));    //等待时间到达
			SysTick->CTRL=0;    //关闭计数器
			SysTick->VAL=0;     //清空计数器
		}
}