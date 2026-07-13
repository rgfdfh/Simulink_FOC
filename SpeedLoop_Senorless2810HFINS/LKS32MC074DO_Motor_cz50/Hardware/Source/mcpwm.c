#include "mcpwm.h"

void HAL_MCPWM_Init(void)
{
	PWMOutputs(DISABLE);
  MCPWM_InitTypeDef MCPWM_InitStruct;
  MCPWM_StructInit(&MCPWM_InitStruct);

  MCPWM_InitStruct.CLK_DIV = 0;            /* MCPWM时钟分频设置 */
  MCPWM_InitStruct.MCLK_EN = ENABLE;       /* 模块时钟开启 */
  MCPWM_InitStruct.IO_CMP_FLT_CLKDIV = 3; /* 急停事件(来自IO口信号)数字滤波器时间设置 */

  MCPWM_InitStruct.AUEN = MCPWM0_TH0_AUPDATE; /*自动加载使能*/

  /* MCPWM0_CNT0	 第一组PWM设置*/

  MCPWM_InitStruct.BASE_CNT0_EN = ENABLE;                   /* 主计数器开始计数使能开关 */
  MCPWM_InitStruct.TH0 = (uint16_t)(PWM_FRQ / FOC_FRQ / 2); /* 计数周期设置即MCPWM输出周期，这个芯片是从-th计数到th的，因此这个属于整个周期的一半，除以2就是计算这个的*/
                                                            /*计算方法：96Mhz/想要的foc频率/2*/

  MCPWM_InitStruct.TH00 = (uint16_t)(-0); /*芯片计数到这个值后高脚置1，计到正的置0，因此可以知道这个值越大，占空比越大，和PWM模式1相同*/
  MCPWM_InitStruct.TH01 = (0);
  MCPWM_InitStruct.TH10 = (uint16_t)(-0);
  MCPWM_InitStruct.TH11 = (0);
  MCPWM_InitStruct.TH20 = (uint16_t)(-0);
  MCPWM_InitStruct.TH21 = (0);

  MCPWM_InitStruct.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
  MCPWM_InitStruct.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
  MCPWM_InitStruct.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;

  MCPWM_InitStruct.DeadTimeCH012N = (uint16_t)(DEAD_TIME_CNT); /* 死区时间设置 */
  MCPWM_InitStruct.DeadTimeCH012P = (uint16_t)(DEAD_TIME_CNT); /*死区时间计算类似，可以理解成这个PWM发生器的计数+1等于多少时间，像这里频率96Mhz那么+1就是1e-8s*/

  MCPWM_InitStruct.CMP_CTRL_CNT0 = DISABLE; /* CMP控制CNT0计数使能位 */
  MCPWM_InitStruct.EVT_CNT0_EN = DISABLE;   /* MCPWM_CNT1外部触发使能位 */
  MCPWM_InitStruct.EVT0 = DISABLE;          /* 外部触发 */

  MCPWM_InitStruct.TR0_UP_INTV = DISABLE;
  MCPWM_InitStruct.TR0_T0_UpdateEN = ENABLE; /*T0时刻更新使能*/
  MCPWM_InitStruct.TR0_T1_UpdateEN = DISABLE;
  MCPWM_InitStruct.TR0_AEC = DISABLE; /*自动清除MCPWM0_EIF标志位*/

  MCPWM_InitStruct.TMR0 = (uint16_t)((int16_T)(PWM_FRQ / FOC_FRQ / 2 - DEAD_TIME_CNT)); /* MCPWM_TMR0  设置采样点，一般在低脚导通中点采样，因此是±ARR附近 */
  MCPWM_InitStruct.TMR1 = 0;                                                            /* MCPWM_TMR1 设置，不采第二次所以不管 */

  MCPWM_InitStruct.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 正常输出或取反输出*/
  MCPWM_InitStruct.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
  MCPWM_InitStruct.CH1N_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH1P_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH2N_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH2P_Polarity_INV = DISABLE;

  MCPWM_InitStruct.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
  MCPWM_InitStruct.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
  MCPWM_InitStruct.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

  /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                   通道交换和极性控制的影响，直接控制通道输出 */
  MCPWM_InitStruct.CH0P_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH0N_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH1P_default_output = MCPWM0_LOW_LEVEL; /* CH1P对应引脚在空闲状态输出低电平 */
  MCPWM_InitStruct.CH1N_default_output = MCPWM0_LOW_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
  MCPWM_InitStruct.CH2P_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH2N_default_output = MCPWM0_LOW_LEVEL;

  MCPWM_InitStruct.T0_Update0_INT_EN = DISABLE; /* T0更新事件 中断使能位 */
  MCPWM_InitStruct.T1_Update0_INT_EN = DISABLE; /* T1更新事件 中断使能位*/
  MCPWM_InitStruct.Update0_INT_EN = DISABLE;    /* CNT0 更新事件 中断使能  双电阻不使用PWM中断  */

  MCPWM_InitStruct.CH0N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH0P_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH1N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH1P_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH2N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH2P_FAIL_EN = ENABLE;

  MCPWM_InitStruct.FAIL0_INPUT_EN = DISABLE; // FAIL_0CAP
  MCPWM_InitStruct.FAIL0_INT_EN = DISABLE;
  MCPWM_InitStruct.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
  MCPWM_InitStruct.FAIL0_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

  MCPWM_InitStruct.FAIL1_INPUT_EN = DISABLE;               // FAIL_1CAP，打开CAP1
  MCPWM_InitStruct.FAIL1_INT_EN = DISABLE;                 // fail中断
  MCPWM_InitStruct.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
  MCPWM_InitStruct.FAIL1_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

  MCPWM_InitStruct.HALT_PRT0 = DISABLE; /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                         还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
  MCPWM_InitStruct.FAIL_0CAP = ENABLE;  // FAIL01事件发生时 将MCPWM0_CNT0值存入MCPWM0_FCNT 使能

  PWM_SWAP = 0x67;
  MCPWM_Init(&MCPWM_InitStruct);

  /*PWM引脚初始化*/
  PWMOutputs(DISABLE);
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIO1, &GPIO_InitStruct);
}

void Self_Check(int16_T step, float pwm_frq, float duty)
{
  PWMOutputs(DISABLE);
  /*GPIO结构体初始化*/
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct);
  /*PWM结构体初始化*/
  MCPWM_InitTypeDef MCPWM_InitStruct;
  MCPWM_StructInit(&MCPWM_InitStruct);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIO1, &GPIO_InitStruct);

  float ccr = (float)(PWM_FRQ / (pwm_frq) / 2) * duty;
  switch (step)
  {
  case 1: /*AHCL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_4, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_5, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_6, Bit_SET);            /*CL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM); /*AH*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_8, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_9, Bit_RESET);

    MCPWM_InitStruct.TH00 = (uint16_T)(-ccr); /*芯片计数到这个值后高脚置1，计到正的置0，因此可以知道这个值越大，占空比越大，和PWM模式1相同*/
    MCPWM_InitStruct.TH01 = (ccr);
    MCPWM_InitStruct.TH10 = (uint16_T)(-0);
    MCPWM_InitStruct.TH11 = (0);
    MCPWM_InitStruct.TH20 = (uint16_T)(-0);
    MCPWM_InitStruct.TH21 = (0);
    break;

  case 2: /*BHCL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_4, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_5, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_6, Bit_SET); /*CL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_7, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM); /*BH*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_9, Bit_RESET);

    MCPWM_InitStruct.TH00 = (uint16_T)(-0); /*芯片计数到这个值后高脚置1，计到正的置0，因此可以知道这个值越大，占空比越大，和PWM模式1相同*/
    MCPWM_InitStruct.TH01 = (0);
    MCPWM_InitStruct.TH10 = (uint16_T)(-ccr);
    MCPWM_InitStruct.TH11 = (ccr);
    MCPWM_InitStruct.TH20 = (uint16_T)(-0);
    MCPWM_InitStruct.TH21 = (0);
    break;

  case 3: /*BHAL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_4, Bit_SET); /*AL*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_5, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_6, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_7, Bit_RESET);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM); /*BH*/
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF0_GPIO);
    GPIO_WriteBit(GPIO1, GPIO_Pin_9, Bit_RESET);

    MCPWM_InitStruct.TH00 = (uint16_T)(-0); /*芯片计数到这个值后高脚置1，计到正的置0，因此可以知道这个值越大，占空比越大，和PWM模式1相同*/
    MCPWM_InitStruct.TH01 = (0);
    MCPWM_InitStruct.TH10 = (uint16_T)(-ccr);
    MCPWM_InitStruct.TH11 = (ccr);
    MCPWM_InitStruct.TH20 = (uint16_T)(-0);
    MCPWM_InitStruct.TH21 = (0);
    break;
  }

  MCPWM_InitStruct.CLK_DIV = 0;            /* MCPWM时钟分频设置 */
  MCPWM_InitStruct.MCLK_EN = ENABLE;       /* 模块时钟开启 */
  MCPWM_InitStruct.IO_CMP_FLT_CLKDIV = 12; /* 急停事件(来自IO口信号)数字滤波器时间设置 */

  MCPWM_InitStruct.AUEN = MCPWM0_TH0_AUPDATE; /*自动加载使能*/

  /* MCPWM0_CNT0	 第一组PWM设置*/

  MCPWM_InitStruct.BASE_CNT0_EN = ENABLE;                   /* 主计数器开始计数使能开关 */
  MCPWM_InitStruct.TH0 = (uint16_T)(PWM_FRQ / pwm_frq / 2); /* 计数周期设置即MCPWM输出周期，这个芯片是从-th计数到th的，因此这个属于整个周期的一半，除以2就是计算这个的*/

  MCPWM_InitStruct.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
  MCPWM_InitStruct.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
  MCPWM_InitStruct.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;

  MCPWM_InitStruct.DeadTimeCH012N = (uint16_T)(DEAD_TIME_CNT); /* 死区时间设置 */
  MCPWM_InitStruct.DeadTimeCH012P = (uint16_T)(DEAD_TIME_CNT); /*死区时间计算类似，可以理解成这个PWM发生器的计数+1等于多少时间，像这里频率96Mhz那么+1就是1e-8s*/

  MCPWM_InitStruct.CMP_CTRL_CNT0 = DISABLE; /* CMP控制CNT0计数使能位 */
  MCPWM_InitStruct.EVT_CNT0_EN = DISABLE;   /* MCPWM_CNT1外部触发使能位 */
  MCPWM_InitStruct.EVT0 = DISABLE;          /* 外部触发 */

  MCPWM_InitStruct.TR0_UP_INTV = DISABLE;
  MCPWM_InitStruct.TR0_T0_UpdateEN = ENABLE; /*T0时刻更新使能*/
  MCPWM_InitStruct.TR0_T1_UpdateEN = DISABLE;
  MCPWM_InitStruct.TR0_AEC = DISABLE; /*自动清除MCPWM0_EIF标志位*/

  MCPWM_InitStruct.TMR0 = (uint16_T)(0); /* MCPWM_TMR0  设置采样点，一般在低脚导通中点采样，因此是±ARR附近 */
  MCPWM_InitStruct.TMR1 = 0;             /* MCPWM_TMR1 设置，不采第二次所以不管 */

  MCPWM_InitStruct.CH0N_Polarity_INV = DISABLE; /* CH0N通道输出极性设置 | 正常输出或取反输出*/
  MCPWM_InitStruct.CH0P_Polarity_INV = DISABLE; /* CH0P通道输出极性设置 | 正常输出或取反输出 */
  MCPWM_InitStruct.CH1N_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH1P_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH2N_Polarity_INV = DISABLE;
  MCPWM_InitStruct.CH2P_Polarity_INV = DISABLE;

  MCPWM_InitStruct.Switch_CH0N_CH0P = DISABLE; /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
  MCPWM_InitStruct.Switch_CH1N_CH1P = DISABLE; /* 通道交换选择设置 */
  MCPWM_InitStruct.Switch_CH2N_CH2P = DISABLE; /* 通道交换选择设置 */

  /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                   通道交换和极性控制的影响，直接控制通道输出 */
  MCPWM_InitStruct.CH0P_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH0N_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH1P_default_output = MCPWM0_LOW_LEVEL; /* CH1P对应引脚在空闲状态输出低电平 */
  MCPWM_InitStruct.CH1N_default_output = MCPWM0_LOW_LEVEL; /* CH1N对应引脚在空闲状态输出高电平 */
  MCPWM_InitStruct.CH2P_default_output = MCPWM0_LOW_LEVEL;
  MCPWM_InitStruct.CH2N_default_output = MCPWM0_LOW_LEVEL;

  MCPWM_InitStruct.T0_Update0_INT_EN = DISABLE; /* T0更新事件 中断使能位 */
  MCPWM_InitStruct.T1_Update0_INT_EN = DISABLE; /* T1更新事件 中断使能位*/
  MCPWM_InitStruct.Update0_INT_EN = DISABLE;    /* CNT0 更新事件 中断使能  双电阻不使用PWM中断  */

  MCPWM_InitStruct.CH0N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH0P_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH1N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH1P_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH2N_FAIL_EN = ENABLE;
  MCPWM_InitStruct.CH2P_FAIL_EN = ENABLE;

  MCPWM_InitStruct.FAIL0_INPUT_EN = DISABLE; // FAIL_0CAP
  MCPWM_InitStruct.FAIL0_INT_EN = DISABLE;
  MCPWM_InitStruct.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
  MCPWM_InitStruct.FAIL0_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

  MCPWM_InitStruct.FAIL1_INPUT_EN = DISABLE;               // FAIL_1CAP，打开CAP1
  MCPWM_InitStruct.FAIL1_INT_EN = DISABLE;                 // fail中断
  MCPWM_InitStruct.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP; // FAIL_0CAP
  MCPWM_InitStruct.FAIL1_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;

  MCPWM_InitStruct.HALT_PRT0 = ENABLE; /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                         还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
  MCPWM_InitStruct.FAIL_0CAP = ENABLE;  // FAIL01事件发生时 将MCPWM0_CNT0值存入MCPWM0_FCNT 使能
  PWM_SWAP = 0x67;
  MCPWM_Init(&MCPWM_InitStruct);

  PWMOutputs(ENABLE);
}