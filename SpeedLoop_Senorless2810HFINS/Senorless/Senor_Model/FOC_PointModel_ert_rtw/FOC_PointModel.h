/*
 * File: FOC_PointModel.h
 *
 * Code generated for Simulink model 'FOC_PointModel'.
 *
 * Model version                  : 4.357
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Mon Jun 29 14:16:30 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
 *    3. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_PointModel_h_
#define RTW_HEADER_FOC_PointModel_h_
#ifndef FOC_PointModel_COMMON_INCLUDES_
#define FOC_PointModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_PointModel_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define ADC_REF                        3.6F                      /* Referenced by:
                                                                  * '<S15>/ADC量程*母线电压分压倍数//定义的最大电压值'
                                                                  * '<S15>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  *//* ADC采样最大电压幅值，也应该为处理飘零后的范围，也应该会是总量程的一半。因为有部分ADC不能采负值所以会整体抬高一半，此时就得总量程/2=这里的数值 */
#define AMP_GAIN                       32.0F                     /* Referenced by: '<S15>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 运算放大器倍数，是放大器中R1/(R1+R2)单位：无 */
#define CURR_LIMIT                     1.1F                      /* Referenced by: '<S15>/Constant34' *//* 电流环PI限幅，32767*n */
#define CURR_OVER                      34.0F                     /* Referenced by: '<S15>/Constant50' *//* 过流保护值，应注意不能大于IMAX。单位：A */
#define CURR_POINT_GAIN                7                         /* Referenced by:
                                                                  * '<S1>/电流采集适当放大系数2^n'
                                                                  * '<S15>/电流采集定点化适当放大2^n'
                                                                  *//* 相电流采集后采样值与定点值换算系数做适当放大，此处为2^n */
#define CURR_STEP                      32760                     /* Referenced by:
                                                                  * '<S12>/Constant1'
                                                                  * '<S12>/Constant2'
                                                                  * '<S12>/Constant3'
                                                                  * '<S12>/Constant8'
                                                                  *//* 电流环每周期步进值 */
#define CURR_UNDER                     0.03F                     /* Referenced by: '<S15>/Constant58' *//* 欠流值，为了处理出现堵住但观测器发散、实际电机电流很小的情况。单位：A
                                                                      */
#define CURR_WIDTH                     250.0F                    /* Referenced by:
                                                                  * '<S15>/Constant11'
                                                                  * '<S15>/Constant9'
                                                                  *//* 电流环带宽，可使用此计算电流环kpki，在仿真模型的初始化模块中进行选择。单位：Hz */
#define FOC_FRQ                        36000.0                   /* Referenced by:
                                                                  * '<S15>/Constant18'
                                                                  * '<S15>/Constant21'
                                                                  * '<S15>/Constant22'
                                                                  * '<S15>/Constant30'
                                                                  * '<S15>/Constant8'
                                                                  *//* FOC触发频率，不能在生成代码后更改，只能在字典改。 */
#define HFI_ID                         2.125F                    /* Referenced by: '<S15>/Constant5' *//* 低速时辅助高频注入的直流偏置。单位：A */
#define IMAX                           34.0F                     /* Referenced by:
                                                                  * '<S15>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  * '<S15>/Constant13'
                                                                  * '<S15>/Constant2'
                                                                  * '<S15>/Constant4'
                                                                  * '<S15>/Constant43'
                                                                  * '<S15>/Constant6'
                                                                  * '<S15>/Constant60'
                                                                  * '<S15>/Gain5'
                                                                  * '<S15>/Gain7'
                                                                  * '<S15>/Saturation'
                                                                  * '<S15>/Saturation2'
                                                                  * '<S15>/Saturation4'
                                                                  *//* 电流最大值，单位：A */
#define LPF_FRQ                        300.0F                    /* Referenced by:
                                                                  * '<S15>/Constant19'
                                                                  * '<S15>/Constant31'
                                                                  *//* 观测器中低通滤波器截止频率，单位：Hz */
#define MOTOR_FLUX                     0.00127131119F            /* Referenced by:
                                                                  * '<S15>/Constant29'
                                                                  * '<S15>/Constant42'
                                                                  * '<S15>/Constant62'
                                                                  * '<S15>/Constant63'
                                                                  * '<S15>/Constant65'
                                                                  *//* 电机磁链。单位：Wb */
#define MOTOR_INERTIA                  1.02E-6F                  /* Referenced by:
                                                                  * '<S15>/Constant40'
                                                                  * '<S15>/Constant45'
                                                                  *//* 电机转动惯量，单位：kgm^2 */
#define MOTOR_LS                       1.8E-5F                   /* Referenced by:
                                                                  * '<S15>/Constant10'
                                                                  * '<S15>/Constant20'
                                                                  * '<S15>/Constant61'
                                                                  *//* 相电感。DQ轴电感。单位：H */
#define MOTOR_PN                       7.0F                      /* Referenced by:
                                                                  * '<S15>/Constant41'
                                                                  * '<S15>/Constant49'
                                                                  *//* 电机极对数 */
#define MOTOR_RS                       0.065F                    /* Referenced by:
                                                                  * '<S15>/Constant12'
                                                                  * '<S15>/Constant15'
                                                                  * '<S15>/Constant59'
                                                                  *//* 相电阻。单位：Ω */
#define NS_COMP_UD                     0.531F                    /* Referenced by: '<S15>/Constant14' *//* 极性辨识的电压值流偏置，注意，他是在电流环PI后的，所以要用[-0.5Udc,0.5udc]的电压范围来考量，也就是最多只能到一半单位：V */
#define OBS_SPD                        500                       /* Referenced by:
                                                                  * '<S6>/Chart'
                                                                  * '<S9>/obs_chart'
                                                                  *//* 观测器滞环切换速度,单位：RPM */
#define PLL_LIMIT                      0.95F                     /* Referenced by: '<S15>/Constant32' *//* 锁相环PI限幅，32767*n */
#define PLL_WIDTH                      500.0F                    /* Referenced by:
                                                                  * '<S15>/Constant25'
                                                                  * '<S15>/Constant26'
                                                                  *//* 锁相环带宽。单位：Hz */
#define PWM_FRQ                        9.6E+7F                   /* Referenced by: '<S15>/Constant7' *//* PWM计数器频率。也可以认为是MCU时钟频率。单位：Hz */
#define RS_HUNT                        0.002F                    /* Referenced by: '<S15>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 采样电阻，单位：Ω */
#define SMOK_FRQ                       1200.0F                   /* Referenced by: '<S15>/Constant28' *//* 滑模增益K，公式电角速度*磁链，即反电动势峰值。单位：Hz */
#define SPD_LIMIT                      0.8F                      /* Referenced by: '<S15>/Constant47' *//* 速度环PI限幅，32767*n */
#define SPD_MAX                        8100                      /* Referenced by: '<S17>/Constant6' *//* 最大转速，这个为实际使用时使用标准电压正常工作所会达到的最大值，用于降压时限制最大转速。单位：RPM */
#define SPD_MIN                        -8100                     /* Referenced by:
                                                                  * '<S17>/Constant7'
                                                                  * '<S18>/速度缓冲1'
                                                                  *//* 进入闭环后最低目标转速，单位：RPM */
#define SPD_REDUCE                     380                       /* Referenced by: '<S17>/Constant1' *//* 每降1V少多少转速，我认为是kv值。单位：RPM */
#define SPD_STEP                       3                         /* Referenced by:
                                                                  * '<S18>/Constant5'
                                                                  * '<S18>/Constant8'
                                                                  *//* 速度环步进值 */
#define SPD_WIDTH                      10.0F                     /* Referenced by:
                                                                  * '<S15>/Constant39'
                                                                  * '<S15>/Constant44'
                                                                  * '<S15>/Constant46'
                                                                  *//* 速度环带宽.单位：Hz */
#define TS_POINT_GAIN                  10                        /* Referenced by:
                                                                  * '<S15>/周期定点化适当放大2^n'
                                                                  * '<S37>/周期定点化适当放大2^n'
                                                                  * '<S44>/周期定点化适当放大2^n'
                                                                  * '<S45>/周期定点化适当放大2^n'
                                                                  * '<S47>/周期定点化适当放大2^n'
                                                                  * '<S48>/周期定点化适当放大2^n'
                                                                  * '<S57>/周期定点化适当放大2^n'
                                                                  * '<S60>/周期定点化适当放大2^n'
                                                                  * '<S70>/周期定点化适当放大2^n'
                                                                  * '<S70>/周期定点化适当放大2^n1'
                                                                  * '<S70>/周期定点化适当放大2^n2'
                                                                  * '<S39>/周期定点化适当放大2^n'
                                                                  *//* FOC频率的倒数适当放大,具体多少应该观察init模块中放大2^15后是多少，此处为2^n */
#define UDC                            17.0F                     /* Referenced by:
                                                                  * '<S15>/Constant'
                                                                  * '<S15>/Constant16'
                                                                  * '<S15>/Constant17'
                                                                  * '<S15>/Constant69'
                                                                  * '<S15>/Constant71'
                                                                  * '<S15>/Constant72'
                                                                  * '<S15>/Saturation1'
                                                                  *//* 基准母线电压，电压比这个低的时候会有些处理。单位：V */
#define UDC_GAIN                       21.0F                     /* Referenced by: '<S15>/ADC量程*母线电压分压倍数//定义的最大电压值' *//* 母线电压分压倍数，单位：无 */
#define UDC_POINT_GAIN                 10                        /* Referenced by:
                                                                  * '<S1>/Constant33'
                                                                  * '<S15>/电压采集定点化适当放大2^n'
                                                                  *//* 母线电压采集后采样值与定点值换算系数做适当放大,此处为2^n */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S8>/max' */
typedef struct {
  int32_T UnitDelay_DSTATE;            /* '<S25>/Unit Delay' */
  boolean_T max_MODE;                  /* '<S8>/max' */
} DW_max;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_max min;                          /* '<S8>/min' */
  DW_max max_f;                        /* '<S8>/max' */
  int64_T Delay_DSTATE;                /* '<S70>/Delay' */
  int32_T Delay4_DSTATE[4];            /* '<S33>/Delay4' */
  int32_T Ud;                          /* '<S12>/Shift Arithmetic4' */
  int32_T Uq;                          /* '<S12>/Shift Arithmetic5' */
  int32_T Sum;                         /* '<S8>/Sum' */
  int32_T output;                      /* '<S8>/正负偏置' */
  int32_T Sum_f;                       /* '<S26>/Sum' */
  int32_T Sum_e;                       /* '<S25>/Sum' */
  int32_T UnitDelay_DSTATE;            /* '<S6>/Unit Delay' */
  int32_T UnitDelay_DSTATE_k;          /* '<S46>/Unit Delay' */
  int32_T UnitDelay_DSTATE_i;          /* '<S48>/Unit Delay' */
  int32_T UnitDelay3_DSTATE;           /* '<S1>/Unit Delay3' */
  int32_T UnitDelay2_DSTATE;           /* '<S1>/Unit Delay2' */
  int32_T Delay3_DSTATE;               /* '<S10>/Delay3' */
  int32_T Delay2_DSTATE;               /* '<S10>/Delay2' */
  int32_T UnitDelay_DSTATE_f;          /* '<S47>/Unit Delay' */
  int32_T UnitDelay_DSTATE_n;          /* '<S57>/Unit Delay' */
  int32_T UnitDelay_DSTATE_d;          /* '<S60>/Unit Delay' */
  int32_T Delay1_DSTATE;               /* '<S18>/Delay1' */
  int32_T Delay2_DSTATE_h;             /* '<S8>/Delay2' */
  int32_T UnitDelay_DSTATE_j;          /* '<S9>/Unit Delay' */
  int32_T UnitDelay_DSTATE_dt;         /* '<S34>/Unit Delay' */
  int32_T UnitDelay_DSTATE_e;          /* '<S45>/Unit Delay' */
  int32_T UnitDelay_DSTATE_g;          /* '<S44>/Unit Delay' */
  int32_T UnitDelay9_DSTATE;           /* '<S43>/Unit Delay9' */
  int32_T UnitDelay2_DSTATE_i;         /* '<S31>/Unit Delay2' */
  int32_T UnitDelay3_DSTATE_l;         /* '<S31>/Unit Delay3' */
  int32_T UnitDelay1_DSTATE;           /* '<S41>/Unit Delay1' */
  int32_T UnitDelay6_DSTATE;           /* '<S31>/Unit Delay6' */
  int32_T UnitDelay4_DSTATE;           /* '<S31>/Unit Delay4' */
  int32_T UnitDelay1_DSTATE_m;         /* '<S42>/Unit Delay1' */
  int32_T UnitDelay_DSTATE_p;          /* '<S39>/Unit Delay' */
  int32_T UnitDelay_DSTATE_m;          /* '<S37>/Unit Delay' */
  int32_T Delay_DSTATE_g;              /* '<S29>/Delay' */
  int32_T Delay1_DSTATE_e;             /* '<S29>/Delay1' */
  int32_T UnitDelay2_DSTATE_a;         /* '<S22>/Unit Delay2' */
  int32_T UnitDelay9_DSTATE_j;         /* '<S20>/Unit Delay9' */
  int32_T clockTickCounter;            /* '<S6>/Pulse Generator1' */
  int32_T SMO_Gain1;                   /* '<S1>/1-Ts(Rs//Ls)' */
  int32_T FOC_FRQ_Point;               /* '<S1>/FOC整数类型频率' */
  int32_T SMO_Gain2;                   /* '<S1>/Ts//Ls' */
  int32_T NScomp_Ud_Point;             /* '<S1>/极性辨识偏置电压' */
  int32_T NS_Flag;                     /* '<S1>/极性辨识标志位' */
  int32_T Curr_Under;                  /* '<S1>/欠流保护值' */
  int32_T Curr_Ki_Point;               /* '<S1>/电流环Ki' */
  int32_T Curr_Kp_Point;               /* '<S1>/电流环Kp' */
  int32_T Curr_Limit;                  /* '<S1>/电流环PI限幅' */
  int32_T Hz_RPM;                      /* '<S1>/电赫兹换算机械转速' */
  int32_T Curr_Over;                   /* '<S1>/过流保护值' */
  int32_T Speed_Ki_Point;              /* '<S1>/速度环Ki' */
  int32_T Speed_Kp_Point;              /* '<S1>/速度环Kp' */
  int32_T Speed_Limit;                 /* '<S1>/速度环限幅' */
  int32_T PLL_Ki;                      /* '<S1>/锁相环Ki' */
  int32_T PLL_Limit;                   /* '<S1>/锁相环PI限幅' */
  int16_T Merge2;                      /* '<S1>/Merge2' */
  int16_T Merge1;                      /* '<S1>/Merge1' */
  int16_T UnitDelay4_DSTATE_j;         /* '<S12>/Unit Delay4' */
  int16_T UnitDelay5_DSTATE;           /* '<S55>/Unit Delay5' */
  int16_T UnitDelay3_DSTATE_d;         /* '<S12>/Unit Delay3' */
  int16_T Delay2_DSTATE_a;             /* '<S18>/Delay2' */
  int16_T PWM_TH;                      /* '<S1>/PWM周期值' */
  int16_T Ts_Point;                    /* '<S1>/PWM周期时间' */
  int16_T SMO_K;                       /* '<S1>/SMO增益K' */
  int16_T LPF_FRQ_Point;               /* '<S1>/SMO里低通滤波器频率' */
  int16_T Uout_Max;                    /* '<S1>/UDQ最大输出限幅' */
  int16_T Voltage_Conversion;          /* '<S1>/母线电压采集定点化转换系数' */
  int16_T Curr_Conversion;             /* '<S1>/电流采集定点化换算系数' */
  int16_T Obs_VtoI;                    /* '<S1>/观测器电流转电压衡量系数' */
  int16_T PLL_Kp;                      /* '<S1>/锁相环Kp' */
  int16_T HFI_Id_Point;                /* '<S1>/高频注入偏置电流' */
  uint16_T Merge;                      /* '<S1>/Merge' */
  uint16_T UnitDelay6_DSTATE_b;        /* '<S1>/Unit Delay6' */
  uint16_T UnitDelay4_DSTATE_f;        /* '<S1>/Unit Delay4' */
  uint16_T UnitDelay1_DSTATE_b;        /* '<S1>/Unit Delay1' */
  uint16_T UnitDelay_DSTATE_l;         /* '<S30>/Unit Delay' */
  uint16_T temporalCounter_i1;         /* '<S18>/速度缓冲1' */
  uint16_T temporalCounter_i1_e;       /* '<S8>/正负偏置' */
  uint16_T temporalCounter_i1_h;       /* '<S9>/obs_chart' */
  uint16_T temporalCounter_i1_d;       /* '<S6>/Chart' */
  uint16_T temporalCounter_i1_c;       /* '<S1>/Chart' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
  int8_T If1_ActiveSubsystem;          /* '<S21>/If1' */
  uint8_T Motor_State;                 /* '<S1>/Chart' */
  uint8_T is_active_c9_FOC_PointModel; /* '<S18>/速度缓冲1' */
  uint8_T is_c9_FOC_PointModel;        /* '<S18>/速度缓冲1' */
  uint8_T is_active_c12_FOC_PointModel;/* '<S8>/正负偏置' */
  uint8_T is_c12_FOC_PointModel;       /* '<S8>/正负偏置' */
  uint8_T is_active_c3_FOC_PointModel; /* '<S9>/obs_chart' */
  uint8_T is_c3_FOC_PointModel;        /* '<S9>/obs_chart' */
  uint8_T is_active_c7_FOC_PointModel; /* '<S6>/Chart' */
  uint8_T is_c7_FOC_PointModel;        /* '<S6>/Chart' */
  uint8_T is_active_c2_FOC_PointModel; /* '<S1>/Chart' */
  uint8_T is_c2_FOC_PointModel;        /* '<S1>/Chart' */
  boolean_T OR1;                       /* '<S21>/OR1' */
  boolean_T icLoad;                    /* '<S18>/Delay1' */
  boolean_T icLoad_c;                  /* '<S70>/Delay' */
  boolean_T icLoad_f;                  /* '<S18>/Delay2' */
  boolean_T Relay_Mode;                /* '<S18>/Relay' */
  boolean_T idq_Controller_MODE;       /* '<S1>/idq_Controller' */
  boolean_T Observers_MODE;            /* '<S1>/Observers' */
  boolean_T _MODE;                     /* '<S5>/闭环错误判断' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: int16(32767*sin(linspace(0,2*pi,4096))))
   * Referenced by:
   *   '<S13>/Sin'
   *   '<S13>/Sin1'
   *   '<S27>/Sin'
   *   '<S27>/Sin1'
   *   '<S36>/Sin'
   *   '<S36>/Sin1'
   */
  int16_T pooled13[4096];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int32_T ia;                          /* '<Root>/ia' */
  int32_T ib;                          /* '<Root>/ib' */
  int32_T ic;                          /* '<Root>/ic' */
  int32_T v_bus;                       /* '<Root>/v_bus' */
  int16_T Motor_OnOff;                 /* '<Root>/Motor_OnOff' */
  int32_T Spd_Ref;                     /* '<Root>/Spd_Ref' */
  real_T Theta;                        /* '<Root>/Theta' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int16_T Reset;                       /* '<Root>/Reset' */
  uint16_T tABC[3];                    /* '<Root>/tABC' */
  int32_T Obs_Spd;                     /* '<Root>/Obs_Spd' */
  uint16_T Obs_Theta;                  /* '<Root>/Obs_Theta' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void FOC_PointModel_initialize(void);

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  extern void FOC_PointModel_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Constant2' : Unused code path elimination
 * Block '<S1>/Data Type Conversion1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion5' : Unused code path elimination
 * Block '<S1>/Data Type Conversion6' : Unused code path elimination
 * Block '<S1>/Data Type Conversion7' : Unused code path elimination
 * Block '<S1>/Data Type Conversion8' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S21>/Constant1' : Unused code path elimination
 * Block '<S21>/Relational Operator2' : Unused code path elimination
 * Block '<S21>/Scope' : Unused code path elimination
 * Block '<S21>/Scope1' : Unused code path elimination
 * Block '<S21>/Scope2' : Unused code path elimination
 * Block '<S21>/Unit Delay' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S7>/Constant1' : Unused code path elimination
 * Block '<S7>/Constant5' : Unused code path elimination
 * Block '<S7>/Product10' : Unused code path elimination
 * Block '<S7>/Product11' : Unused code path elimination
 * Block '<S7>/Saturation' : Unused code path elimination
 * Block '<S7>/Shift Arithmetic1' : Unused code path elimination
 * Block '<S7>/Shift Arithmetic9' : Unused code path elimination
 * Block '<S7>/Sum10' : Unused code path elimination
 * Block '<S7>/Sum11' : Unused code path elimination
 * Block '<S7>/Unit Delay9' : Unused code path elimination
 * Block '<S29>/Product1' : Unused code path elimination
 * Block '<S29>/Product2' : Unused code path elimination
 * Block '<S29>/Scope1' : Unused code path elimination
 * Block '<S29>/Scope10' : Unused code path elimination
 * Block '<S29>/Scope14' : Unused code path elimination
 * Block '<S30>/Bias' : Unused code path elimination
 * Block '<S38>/Data Type Duplicate' : Unused code path elimination
 * Block '<S38>/Data Type Propagation' : Unused code path elimination
 * Block '<S35>/Scope' : Unused code path elimination
 * Block '<S39>/Constant' : Unused code path elimination
 * Block '<S40>/Data Type Duplicate' : Unused code path elimination
 * Block '<S40>/Data Type Propagation' : Unused code path elimination
 * Block '<S39>/Sum2' : Unused code path elimination
 * Block '<S30>/Product2' : Unused code path elimination
 * Block '<S30>/Scope' : Unused code path elimination
 * Block '<S30>/Scope1' : Unused code path elimination
 * Block '<S30>/Scope3' : Unused code path elimination
 * Block '<S30>/Shift Arithmetic1' : Unused code path elimination
 * Block '<S30>/Shift Arithmetic10' : Unused code path elimination
 * Block '<S30>/Shift Arithmetic15' : Unused code path elimination
 * Block '<S30>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S30>/Unit Delay2' : Unused code path elimination
 * Block '<S30>/atan256' : Unused code path elimination
 * Block '<S31>/Display' : Unused code path elimination
 * Block '<S41>/Constant5' : Unused code path elimination
 * Block '<S41>/Product10' : Unused code path elimination
 * Block '<S41>/Product11' : Unused code path elimination
 * Block '<S41>/Shift Arithmetic2' : Unused code path elimination
 * Block '<S41>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S41>/Sum10' : Unused code path elimination
 * Block '<S41>/Sum11' : Unused code path elimination
 * Block '<S41>/Unit Delay9' : Unused code path elimination
 * Block '<S42>/Constant5' : Unused code path elimination
 * Block '<S42>/Product10' : Unused code path elimination
 * Block '<S42>/Product11' : Unused code path elimination
 * Block '<S42>/Shift Arithmetic2' : Unused code path elimination
 * Block '<S42>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S42>/Sum10' : Unused code path elimination
 * Block '<S42>/Sum11' : Unused code path elimination
 * Block '<S42>/Unit Delay9' : Unused code path elimination
 * Block '<S31>/Saturation1' : Unused code path elimination
 * Block '<S31>/Scope' : Unused code path elimination
 * Block '<S31>/Scope1' : Unused code path elimination
 * Block '<S31>/Scope2' : Unused code path elimination
 * Block '<S31>/Scope4' : Unused code path elimination
 * Block '<S31>/Scope5' : Unused code path elimination
 * Block '<S31>/Scope6' : Unused code path elimination
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S9>/Scope2' : Unused code path elimination
 * Block '<S34>/Scope' : Unused code path elimination
 * Block '<S46>/Scope' : Unused code path elimination
 * Block '<S11>/Gain1' : Unused code path elimination
 * Block '<S11>/Scope' : Unused code path elimination
 * Block '<S11>/Sign' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope10' : Unused code path elimination
 * Block '<S1>/Scope11' : Unused code path elimination
 * Block '<S1>/Scope13' : Unused code path elimination
 * Block '<S1>/Scope14' : Unused code path elimination
 * Block '<S1>/Scope18' : Unused code path elimination
 * Block '<S1>/Scope19' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope20' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 * Block '<S1>/Scope5' : Unused code path elimination
 * Block '<S1>/Scope6' : Unused code path elimination
 * Block '<S1>/Scope7' : Unused code path elimination
 * Block '<S1>/Scope8' : Unused code path elimination
 * Block '<S1>/Scope9' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Sum10' : Unused code path elimination
 * Block '<S1>/Unit Delay5' : Unused code path elimination
 * Block '<S56>/Data Type Duplicate' : Unused code path elimination
 * Block '<S56>/Data Type Propagation' : Unused code path elimination
 * Block '<S51>/Scope' : Unused code path elimination
 * Block '<S57>/Constant' : Unused code path elimination
 * Block '<S58>/Data Type Duplicate' : Unused code path elimination
 * Block '<S58>/Data Type Propagation' : Unused code path elimination
 * Block '<S57>/Sum2' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Propagation' : Unused code path elimination
 * Block '<S52>/Scope' : Unused code path elimination
 * Block '<S60>/Constant' : Unused code path elimination
 * Block '<S61>/Data Type Duplicate' : Unused code path elimination
 * Block '<S61>/Data Type Propagation' : Unused code path elimination
 * Block '<S60>/Scope' : Unused code path elimination
 * Block '<S60>/Sum2' : Unused code path elimination
 * Block '<S53>/Data Type Duplicate' : Unused code path elimination
 * Block '<S53>/Data Type Propagation' : Unused code path elimination
 * Block '<S54>/Data Type Duplicate' : Unused code path elimination
 * Block '<S54>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Scope3' : Unused code path elimination
 * Block '<S12>/Scope4' : Unused code path elimination
 * Block '<S55>/Scope' : Unused code path elimination
 * Block '<S62>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S15>/Constant23' : Unused code path elimination
 * Block '<S15>/Constant3' : Unused code path elimination
 * Block '<S15>/Display1' : Unused code path elimination
 * Block '<S15>/Display10' : Unused code path elimination
 * Block '<S15>/Display11' : Unused code path elimination
 * Block '<S15>/Display12' : Unused code path elimination
 * Block '<S15>/Display13' : Unused code path elimination
 * Block '<S15>/Display14' : Unused code path elimination
 * Block '<S15>/Display15' : Unused code path elimination
 * Block '<S15>/Display16' : Unused code path elimination
 * Block '<S15>/Display17' : Unused code path elimination
 * Block '<S15>/Display18' : Unused code path elimination
 * Block '<S15>/Display19' : Unused code path elimination
 * Block '<S15>/Display2' : Unused code path elimination
 * Block '<S15>/Display20' : Unused code path elimination
 * Block '<S15>/Display21' : Unused code path elimination
 * Block '<S15>/Display22' : Unused code path elimination
 * Block '<S15>/Display23' : Unused code path elimination
 * Block '<S15>/Display24' : Unused code path elimination
 * Block '<S15>/Display25' : Unused code path elimination
 * Block '<S15>/Display26' : Unused code path elimination
 * Block '<S15>/Display27' : Unused code path elimination
 * Block '<S15>/Display28' : Unused code path elimination
 * Block '<S15>/Display29' : Unused code path elimination
 * Block '<S15>/Display3' : Unused code path elimination
 * Block '<S15>/Display30' : Unused code path elimination
 * Block '<S15>/Display31' : Unused code path elimination
 * Block '<S15>/Display32' : Unused code path elimination
 * Block '<S15>/Display33' : Unused code path elimination
 * Block '<S15>/Display34' : Unused code path elimination
 * Block '<S15>/Display35' : Unused code path elimination
 * Block '<S15>/Display36' : Unused code path elimination
 * Block '<S15>/Display37' : Unused code path elimination
 * Block '<S15>/Display38' : Unused code path elimination
 * Block '<S15>/Display39' : Unused code path elimination
 * Block '<S15>/Display4' : Unused code path elimination
 * Block '<S15>/Display40' : Unused code path elimination
 * Block '<S15>/Display43' : Unused code path elimination
 * Block '<S15>/Display44' : Unused code path elimination
 * Block '<S15>/Display45' : Unused code path elimination
 * Block '<S15>/Display46' : Unused code path elimination
 * Block '<S15>/Display47' : Unused code path elimination
 * Block '<S15>/Display48' : Unused code path elimination
 * Block '<S15>/Display5' : Unused code path elimination
 * Block '<S15>/Display50' : Unused code path elimination
 * Block '<S15>/Display51' : Unused code path elimination
 * Block '<S15>/Display6' : Unused code path elimination
 * Block '<S15>/Display7' : Unused code path elimination
 * Block '<S15>/Display8' : Unused code path elimination
 * Block '<S15>/Display9' : Unused code path elimination
 * Block '<S16>/Constant1' : Unused code path elimination
 * Block '<S16>/Display' : Unused code path elimination
 * Block '<S63>/Data Type Duplicate' : Unused code path elimination
 * Block '<S63>/Data Type Propagation' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Constant1' : Unused code path elimination
 * Block '<S18>/Constant15' : Unused code path elimination
 * Block '<S18>/Constant2' : Unused code path elimination
 * Block '<S18>/Constant3' : Unused code path elimination
 * Block '<S18>/Constant4' : Unused code path elimination
 * Block '<S18>/Constant6' : Unused code path elimination
 * Block '<S18>/Constant7' : Unused code path elimination
 * Block '<S69>/Data Type Duplicate' : Unused code path elimination
 * Block '<S69>/Data Type Propagation' : Unused code path elimination
 * Block '<S65>/Scope' : Unused code path elimination
 * Block '<S65>/Scope1' : Unused code path elimination
 * Block '<S65>/Scope2' : Unused code path elimination
 * Block '<S70>/Constant' : Unused code path elimination
 * Block '<S70>/Constant1' : Unused code path elimination
 * Block '<S71>/Data Type Duplicate' : Unused code path elimination
 * Block '<S71>/Data Type Propagation' : Unused code path elimination
 * Block '<S70>/Scope' : Unused code path elimination
 * Block '<S70>/Sum1' : Unused code path elimination
 * Block '<S70>/Unit Delay' : Unused code path elimination
 * Block '<S18>/Relay1' : Unused code path elimination
 * Block '<S66>/Data Type Duplicate' : Unused code path elimination
 * Block '<S66>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Scope' : Unused code path elimination
 * Block '<S18>/Scope1' : Unused code path elimination
 * Block '<S18>/Scope2' : Unused code path elimination
 * Block '<S18>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S18>/Shift Arithmetic4' : Unused code path elimination
 * Block '<S18>/Switch1' : Unused code path elimination
 * Block '<S18>/Switch2' : Unused code path elimination
 * Block '<S67>/Constant' : Unused code path elimination
 * Block '<S67>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S67>/FixPt Switch' : Unused code path elimination
 * Block '<S1>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S55>/Shift Arithmetic7' : Eliminated trivial shift
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Senorless/FOC_PointModel')    - opens subsystem Senorless/FOC_PointModel
 * hilite_system('Senorless/FOC_PointModel/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Senorless'
 * '<S1>'   : 'Senorless/FOC_PointModel'
 * '<S2>'   : 'Senorless/FOC_PointModel/AntiPark'
 * '<S3>'   : 'Senorless/FOC_PointModel/Chart'
 * '<S4>'   : 'Senorless/FOC_PointModel/Clark'
 * '<S5>'   : 'Senorless/FOC_PointModel/Err'
 * '<S6>'   : 'Senorless/FOC_PointModel/HF_Generator'
 * '<S7>'   : 'Senorless/FOC_PointModel/LPF'
 * '<S8>'   : 'Senorless/FOC_PointModel/NS辨识'
 * '<S9>'   : 'Senorless/FOC_PointModel/Observers'
 * '<S10>'  : 'Senorless/FOC_PointModel/Park'
 * '<S11>'  : 'Senorless/FOC_PointModel/SVPWM'
 * '<S12>'  : 'Senorless/FOC_PointModel/idq_Controller'
 * '<S13>'  : 'Senorless/FOC_PointModel/sincos_4096'
 * '<S14>'  : 'Senorless/FOC_PointModel/停止等待'
 * '<S15>'  : 'Senorless/FOC_PointModel/初始化模块'
 * '<S16>'  : 'Senorless/FOC_PointModel/标志位'
 * '<S17>'  : 'Senorless/FOC_PointModel/电压限转速'
 * '<S18>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环'
 * '<S19>'  : 'Senorless/FOC_PointModel/识别初始位置'
 * '<S20>'  : 'Senorless/FOC_PointModel/Err/PLL_LPF1'
 * '<S21>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断'
 * '<S22>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/SUM'
 * '<S23>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/ZERO'
 * '<S24>'  : 'Senorless/FOC_PointModel/HF_Generator/Chart'
 * '<S25>'  : 'Senorless/FOC_PointModel/NS辨识/max'
 * '<S26>'  : 'Senorless/FOC_PointModel/NS辨识/min'
 * '<S27>'  : 'Senorless/FOC_PointModel/NS辨识/sincos_4096'
 * '<S28>'  : 'Senorless/FOC_PointModel/NS辨识/正负偏置'
 * '<S29>'  : 'Senorless/FOC_PointModel/Observers/HFI'
 * '<S30>'  : 'Senorless/FOC_PointModel/Observers/PLL'
 * '<S31>'  : 'Senorless/FOC_PointModel/Observers/SMO'
 * '<S32>'  : 'Senorless/FOC_PointModel/Observers/obs_chart'
 * '<S33>'  : 'Senorless/FOC_PointModel/Observers/提取波'
 * '<S34>'  : 'Senorless/FOC_PointModel/Observers/滤波器'
 * '<S35>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller'
 * '<S36>'  : 'Senorless/FOC_PointModel/Observers/PLL/sincos_4096'
 * '<S37>'  : 'Senorless/FOC_PointModel/Observers/PLL/积分器'
 * '<S38>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/Saturation Dynamic2'
 * '<S39>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器'
 * '<S40>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器/Saturation Dynamic2'
 * '<S41>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF1'
 * '<S42>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF2'
 * '<S43>'  : 'Senorless/FOC_PointModel/Observers/滤波器/LPF'
 * '<S44>'  : 'Senorless/FOC_PointModel/Observers/滤波器/积分器4'
 * '<S45>'  : 'Senorless/FOC_PointModel/Observers/滤波器/积分器5'
 * '<S46>'  : 'Senorless/FOC_PointModel/Park/滤波器'
 * '<S47>'  : 'Senorless/FOC_PointModel/Park/滤波器/积分器4'
 * '<S48>'  : 'Senorless/FOC_PointModel/Park/滤波器/积分器5'
 * '<S49>'  : 'Senorless/FOC_PointModel/SVPWM/AntiClark'
 * '<S50>'  : 'Senorless/FOC_PointModel/SVPWM/ei_t'
 * '<S51>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller'
 * '<S52>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1'
 * '<S53>'  : 'Senorless/FOC_PointModel/idq_Controller/Saturation Dynamic1'
 * '<S54>'  : 'Senorless/FOC_PointModel/idq_Controller/Saturation Dynamic2'
 * '<S55>'  : 'Senorless/FOC_PointModel/idq_Controller/Subsystem'
 * '<S56>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/Saturation Dynamic2'
 * '<S57>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器'
 * '<S58>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器/Saturation Dynamic2'
 * '<S59>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/Saturation Dynamic2'
 * '<S60>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器'
 * '<S61>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器/Saturation Dynamic2'
 * '<S62>'  : 'Senorless/FOC_PointModel/idq_Controller/Subsystem/Wrap To Zero1'
 * '<S63>'  : 'Senorless/FOC_PointModel/电压限转速/Saturation Dynamic1'
 * '<S64>'  : 'Senorless/FOC_PointModel/电压限转速/Saturation Dynamic2'
 * '<S65>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller'
 * '<S66>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Saturation Dynamic2'
 * '<S67>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero2'
 * '<S68>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/速度缓冲1'
 * '<S69>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/Saturation Dynamic2'
 * '<S70>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/积分器1'
 * '<S71>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/积分器1/Saturation Dynamic2'
 */
#endif                                 /* RTW_HEADER_FOC_PointModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
