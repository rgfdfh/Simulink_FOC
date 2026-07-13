/*
 * File: FOC_PointModel.h
 *
 * Code generated for Simulink model 'FOC_PointModel'.
 *
 * Model version                  : 4.303
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Fri Jan 16 14:35:17 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
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
                                                                  * '<S14>/ADC量程*母线电压分压倍数//定义的最大电压值'
                                                                  * '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  *//* ADC采样最大电压幅值，也应该为处理飘零后的范围，也应该会是总量程的一半。因为有部分ADC不能采负值所以会整体抬高一半，此时就得总量程/2=这里的数值 */
#define AMP_GAIN                       16.0F                     /* Referenced by: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 运算放大器倍数，是放大器中R1/(R1+R2)单位：无 */
#define CURR_LIMIT                     1.1F                      /* Referenced by: '<S14>/Constant34' *//* 电流环PI限幅，32768*n */
#define CURR_OVER                      22.0F                     /* Referenced by: '<S14>/Constant50' *//* 过流保护值，应注意不能大于IMAX。单位：A */
#define CURR_POINT_GAIN                7                         /* Referenced by:
                                                                  * '<S1>/电流采集适当放大系数2^n'
                                                                  * '<S14>/电流采集定点化适当放大2^n'
                                                                  *//* 相电流采集后采样值与定点值换算系数做适当放大，此处为2^n */
#define CURR_STEP                      32760                     /* Referenced by:
                                                                  * '<S10>/Constant1'
                                                                  * '<S10>/Constant2'
                                                                  * '<S10>/Constant3'
                                                                  * '<S10>/Constant8'
                                                                  *//* 电流环每周期步进值 */
#define CURR_UNDER                     0.03F                     /* Referenced by: '<S14>/Constant58' *//* 欠流值，为了处理出现堵住但观测器发散、实际电机电流很小的情况。单位：A
                                                                      */
#define CURR_WIDTH                     2048.0F                   /* Referenced by:
                                                                  * '<S14>/Constant11'
                                                                  * '<S14>/Constant9'
                                                                  *//* 电流环带宽，可使用此计算电流环kpki，在仿真模型的初始化模块中进行选择 */
#define FOC_FRQ                        25000.0                   /* Referenced by:
                                                                  * '<S14>/Constant18'
                                                                  * '<S14>/Constant21'
                                                                  * '<S14>/Constant22'
                                                                  * '<S14>/Constant30'
                                                                  * '<S14>/Constant8'
                                                                  *//* FOC触发频率，不能在生成代码后更改，只能在字典改。 */
#define IMAX                           48.0F                     /* Referenced by:
                                                                  * '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  * '<S14>/Constant13'
                                                                  * '<S14>/Constant2'
                                                                  * '<S14>/Constant4'
                                                                  * '<S14>/Constant43'
                                                                  * '<S14>/Constant53'
                                                                  * '<S14>/Constant55'
                                                                  * '<S14>/Constant56'
                                                                  * '<S14>/Constant60'
                                                                  * '<S14>/Gain5'
                                                                  * '<S14>/Gain7'
                                                                  * '<S14>/Saturation'
                                                                  * '<S14>/Saturation1'
                                                                  * '<S14>/Saturation2'
                                                                  * '<S14>/Saturation3'
                                                                  * '<S14>/Saturation4'
                                                                  *//* 电流最大值，单位：A */
#define LPF_FRQ                        3000.0F                   /* Referenced by:
                                                                  * '<S14>/Constant19'
                                                                  * '<S14>/Constant31'
                                                                  *//* 观测器中低通滤波器截止频率，单位：Hz */
#define MOTOR_FLUX                     0.00218F                  /* Referenced by:
                                                                  * '<S14>/Constant29'
                                                                  * '<S14>/Constant42'
                                                                  * '<S14>/Constant62'
                                                                  * '<S14>/Constant63'
                                                                  * '<S14>/Constant65'
                                                                  *//* 电机磁链 */
#define MOTOR_INERTIA                  1.58E-6F                  /* Referenced by:
                                                                  * '<S14>/Constant40'
                                                                  * '<S14>/Constant45'
                                                                  *//* 电机转动惯量，单位：kgm^2 */
#define MOTOR_LS                       6.5E-5F                   /* Referenced by:
                                                                  * '<S14>/Constant10'
                                                                  * '<S14>/Constant20'
                                                                  * '<S14>/Constant61'
                                                                  *//* 相电感 */
#define MOTOR_PN                       7.0F                      /* Referenced by:
                                                                  * '<S14>/Constant41'
                                                                  * '<S14>/Constant49'
                                                                  * '<S14>/Gain2'
                                                                  * '<S14>/Gain6'
                                                                  *//* 电机极对数 */
#define MOTOR_RS                       0.135F                    /* Referenced by:
                                                                  * '<S14>/Constant12'
                                                                  * '<S14>/Constant15'
                                                                  * '<S14>/Constant59'
                                                                  *//* 相电阻 */
#define OPEN_IQ                        5.0F                      /* Referenced by: '<S14>/Constant52' *//* 开环加速IQ。单位：A */
#define OPEN_IQ_MIN                    2.0F                      /* Referenced by: '<S14>/Constant54' *//* 切闭环降力矩降到这个数.单位：A */
#define OPEN_IQ_SLOW                   0.1F                      /* Referenced by: '<S14>/Constant6' *//* 慢速强拖IQ，单位：A */
#define OPEN_SPD                       500                       /* Referenced by:
                                                                  * '<S14>/Constant5'
                                                                  * '<S14>/Constant70'
                                                                  * '<S19>/Constant12'
                                                                  * '<S19>/Unit Delay3'
                                                                  *//* 开环最终速度,单位：RPM */
#define OPEN_SPD_SLOW                  180.0F                    /* Referenced by: '<S14>/Constant57' *//* 慢速强拖转速，单位：RPM */
#define OPEN_TIME                      0.5F                      /* Referenced by:
                                                                  * '<S1>/Chart'
                                                                  * '<S14>/Constant14'
                                                                  *//* 开环加速时间，单位：s */
#define OPEN_TIME_NFO                  0.5F                      /* Referenced by: '<S14>/Constant67' *//* 不同于开环强拖，这个是使用非线性磁链直接闭环后防止打桨将加速强拖那段加进来的缓冲时间 */
#define PLL_LIMIT                      0.95F                     /* Referenced by: '<S14>/Constant32' *//* 锁相环PI限幅，32768*n */
#define PLL_WIDTH                      1024.0F                   /* Referenced by:
                                                                  * '<S14>/Constant25'
                                                                  * '<S14>/Constant26'
                                                                  *//* 锁相环带宽 */
#define PWM_FRQ                        9.6E+7F                   /* Referenced by: '<S14>/Constant7' *//* PWM计数器频率 */
#define RS_HUNT                        0.002F                    /* Referenced by: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 采样电阻，单位：欧 */
#define SMOK_FRQ                       300.0F                    /* Referenced by: '<S14>/Constant28' *//* 滑模增益K，公式电角速度*磁链，即反电动势峰值。单位：Hz */
#define SPD_LIMIT                      0.99F                     /* Referenced by: '<S14>/Constant47' *//* 速度环PI限幅，32768*n */
#define SPD_LPF_LEVEL                  15                        /* Referenced by: '<S6>/Constant1' *//* PLL速度滤波器等级，范围0~15，越高滤波性越强 */
#define SPD_MAX                        8500                      /* Referenced by: '<S18>/Constant6' *//* 最大转速，这个为实际使用时使用标准电压正常工作所会达到的最大值，用于降压时限制最大转速。单位：RPM */
#define SPD_MIN                        1000                      /* Referenced by: '<S18>/Constant7' *//* 进入闭环后最低目标转速，单位：RPM */
#define SPD_REDUCE                     380                       /* Referenced by: '<S18>/Constant1' *//* 每降1V少多少转速，我认为是kv值。单位：RPM */
#define SPD_STEP                       8                         /* Referenced by:
                                                                  * '<S19>/Constant5'
                                                                  * '<S19>/Constant8'
                                                                  *//* 速度环步进值 */
#define SPD_WIDTH                      15.0F                     /* Referenced by:
                                                                  * '<S14>/Constant39'
                                                                  * '<S14>/Constant44'
                                                                  * '<S14>/Constant46'
                                                                  *//* 速度环带宽 */
#define THETA_ERR_LIMIT                8192                      /* Referenced by: '<S1>/Chart' *//* 开环切闭环。开环角度与观测器角度误差小于这个才能切过去 */
#define TS_POINT_GAIN                  10                        /* Referenced by:
                                                                  * '<S14>/周期定点化适当放大2^n'
                                                                  * '<S53>/周期定点化适当放大2^n'
                                                                  * '<S54>/周期定点化适当放大2^n'
                                                                  * '<S29>/周期定点化适当放大2^n'
                                                                  * '<S43>/周期定点化适当放大2^n'
                                                                  * '<S46>/周期定点化适当放大2^n'
                                                                  * '<S50>/周期定点化适当放大2^n'
                                                                  * '<S51>/周期定点化适当放大2^n'
                                                                  * '<S63>/周期定点化适当放大2^n'
                                                                  * '<S31>/周期定点化适当放大2^n'
                                                                  *//* FOC频率的倒数适当放大,具体多少应该观察init模块中放大2^15后是多少，此处为2^n */
#define UDC                            24                        /* Referenced by:
                                                                  * '<S14>/Constant'
                                                                  * '<S14>/Constant16'
                                                                  * '<S14>/Constant69'
                                                                  * '<S14>/Constant71'
                                                                  * '<S14>/Constant72'
                                                                  * '<S18>/Constant4'
                                                                  * '<S18>/Constant5'
                                                                  * '<S18>/Saturation'
                                                                  *//* 基准母线电压，电压比这个低的时候会有些处理。 */
#define UDC_GAIN                       41.0F                     /* Referenced by: '<S14>/ADC量程*母线电压分压倍数//定义的最大电压值' *//* 母线电压分压倍数，单位：无 */
#define UDC_POINT_GAIN                 10                        /* Referenced by:
                                                                  * '<S1>/Constant33'
                                                                  * '<S14>/电压采集定点化适当放大2^n'
                                                                  *//* 母线电压采集后采样值与定点值换算系数做适当放大,此处为2^n */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  int32_T Ud;                          /* '<S10>/Shift Arithmetic4' */
  int32_T Uq;                          /* '<S10>/Shift Arithmetic5' */
  int32_T SPD_Ref;                     /* '<S19>/速度缓冲' */
  int32_T ShiftArithmetic13;           /* '<S25>/Shift Arithmetic13' */
  int32_T UnitDelay_DSTATE;            /* '<S43>/Unit Delay' */
  int32_T UnitDelay_DSTATE_f;          /* '<S46>/Unit Delay' */
  int32_T UnitDelay_DSTATE_h;          /* '<S54>/Unit Delay' */
  int32_T UnitDelay3_DSTATE_m;         /* '<S19>/Unit Delay3' */
  int32_T UnitDelay_DSTATE_g;          /* '<S63>/Unit Delay' */
  int32_T Delay_DSTATE;                /* '<S53>/Delay' */
  int32_T UnitDelay_DSTATE_b;          /* '<S51>/Unit Delay' */
  int32_T UnitDelay_DSTATE_d;          /* '<S50>/Unit Delay' */
  int32_T UnitDelay4_DSTATE;           /* '<S26>/Unit Delay4' */
  int32_T UnitDelay6_DSTATE;           /* '<S26>/Unit Delay6' */
  int32_T UnitDelay1_DSTATE;           /* '<S33>/Unit Delay1' */
  int32_T UnitDelay2_DSTATE;           /* '<S26>/Unit Delay2' */
  int32_T UnitDelay3_DSTATE_l;         /* '<S26>/Unit Delay3' */
  int32_T UnitDelay1_DSTATE_m;         /* '<S34>/Unit Delay1' */
  int32_T UnitDelay1_DSTATE_p;         /* '<S25>/Unit Delay1' */
  int32_T UnitDelay_DSTATE_p;          /* '<S31>/Unit Delay' */
  int32_T UnitDelay_DSTATE_m;          /* '<S29>/Unit Delay' */
  int32_T UnitDelay9_DSTATE;           /* '<S6>/Unit Delay9' */
  int32_T UnitDelay_DSTATE_k;          /* '<S22>/Unit Delay' */
  int32_T UnitDelay2_DSTATE_a;         /* '<S23>/Unit Delay2' */
  int32_T UnitDelay9_DSTATE_j;         /* '<S21>/Unit Delay9' */
  int32_T DIV_LPF_FRQ;                 /* '<S1>/1//LPF_FRQ' */
  int32_T FOC_FRQ_Point;               /* '<S1>/FOC整数类型频率' */
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
  uint32_T temporalCounter_i1;         /* '<S1>/Chart' */
  int16_T Merge2;                      /* '<S1>/Merge2' */
  int16_T Merge1;                      /* '<S1>/Merge1' */
  int16_T UnitDelay4_DSTATE_j;         /* '<S10>/Unit Delay4' */
  int16_T UnitDelay5_DSTATE;           /* '<S41>/Unit Delay5' */
  int16_T UnitDelay3_DSTATE_d;         /* '<S10>/Unit Delay3' */
  int16_T Delay_DSTATE_h;              /* '<S19>/Delay' */
  int16_T Delay1_DSTATE;               /* '<S19>/Delay1' */
  int16_T UnitDelay1_DSTATE_g;         /* '<S16>/Unit Delay1' */
  int16_T PWM_TH;                      /* '<S1>/PWM周期值' */
  int16_T Ts_Point;                    /* '<S1>/PWM周期时间' */
  int16_T SMO_K;                       /* '<S1>/SMO增益K' */
  int16_T LPF_FRQ_Point;               /* '<S1>/SMO里低通滤波器频率' */
  int16_T Open_Acceleration;           /* '<S1>/开环加速度' */
  int16_T Open_Hz;                     /* '<S1>/开环最终转速' */
  int16_T Open_Iq_Point;               /* '<S1>/开环阶段Iq' */
  int16_T Open_IqMin_Point;            /* '<S1>/开环阶段Iq最终值' */
  int16_T Open_Iq_Slow;                /* '<S1>/慢速强拖Iq' */
  int16_T Open_Slow;                   /* '<S1>/慢速强拖转速' */
  int16_T Voltage_Conversion;          /* '<S1>/母线电压采集定点化转换系数' */
  int16_T Curr_Conversion;             /* '<S1>/电流采集定点化换算系数' */
  int16_T Obs_VtoI;                    /* '<S1>/观测器电流转电压衡量系数' */
  int16_T PLL_Kp;                      /* '<S1>/锁相环Kp' */
  uint16_T Merge;                      /* '<S1>/Merge' */
  uint16_T UnitDelay1_DSTATE_b;        /* '<S1>/Unit Delay1' */
  uint16_T UnitDelay7_DSTATE;          /* '<S13>/Unit Delay7' */
  uint16_T UnitDelay6_DSTATE_a;        /* '<S13>/Unit Delay6' */
  uint16_T UnitDelay5_DSTATE_i;        /* '<S13>/Unit Delay5' */
  uint16_T SMO_Gain1;                  /* '<S1>/1-Ts(Rs//Ls)' */
  uint16_T SMO_Gain2;                  /* '<S1>/Ts//Ls' */
  uint16_T temporalCounter_i1_m;       /* '<S19>/速度缓冲' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
  int8_T If1_ActiveSubsystem;          /* '<S22>/If1' */
  uint8_T Motor_State;                 /* '<S1>/Chart' */
  uint8_T is_active_c48_FOC_PointModel;/* '<S19>/速度缓冲' */
  uint8_T is_c48_FOC_PointModel;       /* '<S19>/速度缓冲' */
  uint8_T is_active_c2_FOC_PointModel; /* '<S1>/Chart' */
  uint8_T is_c2_FOC_PointModel;        /* '<S1>/Chart' */
  boolean_T OR1;                       /* '<S22>/OR1' */
  boolean_T icLoad;                    /* '<S19>/Delay' */
  boolean_T icLoad_l;                  /* '<S19>/Delay1' */
  boolean_T icLoad_d;                  /* '<S53>/Delay' */
  boolean_T _MODE;                     /* '<S1>/切闭环角度差' */
  boolean_T idq_Controller_MODE;       /* '<S1>/idq_Controller' */
  boolean_T Observers_MODE;            /* '<S1>/Observers' */
  boolean_T _MODE_p;                   /* '<S5>/闭环错误判断' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: int16(32767*sin(linspace(0,2*pi,512))))
   * Referenced by:
   *   '<S11>/Sin'
   *   '<S11>/Sin1'
   *   '<S28>/Sin'
   *   '<S28>/Sin1'
   */
  int16_T pooled16[512];

  /* Expression: uint16(16384*atan(linspace(0,1,256)))
   * Referenced by: '<S25>/atan256'
   */
  uint16_T atan256_tableData[256];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int32_T ia;                          /* '<Root>/ia' */
  int32_T ib;                          /* '<Root>/ib' */
  int32_T ic;                          /* '<Root>/ic' */
  int32_T v_bus;                       /* '<Root>/v_bus' */
  int16_T Motor_OnOff;                 /* '<Root>/Motor_OnOff' */
  int16_T Slow_OnOff;                  /* '<Root>/Slow_OnOff' */
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
extern void FOC_PointModel_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Constant' : Unused code path elimination
 * Block '<S1>/Constant1' : Unused code path elimination
 * Block '<S1>/Constant2' : Unused code path elimination
 * Block '<S1>/Data Type Conversion1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion5' : Unused code path elimination
 * Block '<S1>/Data Type Conversion6' : Unused code path elimination
 * Block '<S1>/Data Type Conversion7' : Unused code path elimination
 * Block '<S1>/Data Type Conversion8' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S22>/Scope' : Unused code path elimination
 * Block '<S22>/Scope1' : Unused code path elimination
 * Block '<S22>/Scope2' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Scope' : Unused code path elimination
 * Block '<S31>/Constant' : Unused code path elimination
 * Block '<S32>/Data Type Duplicate' : Unused code path elimination
 * Block '<S32>/Data Type Propagation' : Unused code path elimination
 * Block '<S31>/Sum2' : Unused code path elimination
 * Block '<S25>/Scope' : Unused code path elimination
 * Block '<S25>/Scope1' : Unused code path elimination
 * Block '<S25>/Scope3' : Unused code path elimination
 * Block '<S25>/Scope8' : Unused code path elimination
 * Block '<S25>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S28>/Sin2' : Unused code path elimination
 * Block '<S28>/Sin3' : Unused code path elimination
 * Block '<S26>/Display' : Unused code path elimination
 * Block '<S26>/Display1' : Unused code path elimination
 * Block '<S33>/Constant5' : Unused code path elimination
 * Block '<S33>/Product10' : Unused code path elimination
 * Block '<S33>/Product11' : Unused code path elimination
 * Block '<S33>/Shift Arithmetic2' : Unused code path elimination
 * Block '<S33>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S33>/Sum10' : Unused code path elimination
 * Block '<S33>/Sum11' : Unused code path elimination
 * Block '<S33>/Unit Delay9' : Unused code path elimination
 * Block '<S34>/Constant5' : Unused code path elimination
 * Block '<S34>/Product10' : Unused code path elimination
 * Block '<S34>/Product11' : Unused code path elimination
 * Block '<S34>/Shift Arithmetic2' : Unused code path elimination
 * Block '<S34>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S34>/Sum10' : Unused code path elimination
 * Block '<S34>/Sum11' : Unused code path elimination
 * Block '<S34>/Unit Delay9' : Unused code path elimination
 * Block '<S26>/Scope' : Unused code path elimination
 * Block '<S26>/Scope1' : Unused code path elimination
 * Block '<S26>/Scope2' : Unused code path elimination
 * Block '<S26>/Scope3' : Unused code path elimination
 * Block '<S26>/Scope4' : Unused code path elimination
 * Block '<S26>/Scope5' : Unused code path elimination
 * Block '<S26>/Scope6' : Unused code path elimination
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S9>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope10' : Unused code path elimination
 * Block '<S1>/Scope11' : Unused code path elimination
 * Block '<S1>/Scope12' : Unused code path elimination
 * Block '<S1>/Scope13' : Unused code path elimination
 * Block '<S1>/Scope16' : Unused code path elimination
 * Block '<S1>/Scope18' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
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
 * Block '<S42>/Data Type Duplicate' : Unused code path elimination
 * Block '<S42>/Data Type Propagation' : Unused code path elimination
 * Block '<S37>/Scope' : Unused code path elimination
 * Block '<S43>/Constant' : Unused code path elimination
 * Block '<S44>/Data Type Duplicate' : Unused code path elimination
 * Block '<S44>/Data Type Propagation' : Unused code path elimination
 * Block '<S43>/Sum2' : Unused code path elimination
 * Block '<S45>/Data Type Duplicate' : Unused code path elimination
 * Block '<S45>/Data Type Propagation' : Unused code path elimination
 * Block '<S38>/Scope' : Unused code path elimination
 * Block '<S46>/Constant' : Unused code path elimination
 * Block '<S47>/Data Type Duplicate' : Unused code path elimination
 * Block '<S47>/Data Type Propagation' : Unused code path elimination
 * Block '<S46>/Scope' : Unused code path elimination
 * Block '<S46>/Sum2' : Unused code path elimination
 * Block '<S39>/Data Type Duplicate' : Unused code path elimination
 * Block '<S39>/Data Type Propagation' : Unused code path elimination
 * Block '<S40>/Data Type Duplicate' : Unused code path elimination
 * Block '<S40>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/Scope2' : Unused code path elimination
 * Block '<S10>/Scope3' : Unused code path elimination
 * Block '<S10>/Scope4' : Unused code path elimination
 * Block '<S48>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S14>/Constant23' : Unused code path elimination
 * Block '<S14>/Constant3' : Unused code path elimination
 * Block '<S14>/Display1' : Unused code path elimination
 * Block '<S14>/Display10' : Unused code path elimination
 * Block '<S14>/Display11' : Unused code path elimination
 * Block '<S14>/Display12' : Unused code path elimination
 * Block '<S14>/Display13' : Unused code path elimination
 * Block '<S14>/Display14' : Unused code path elimination
 * Block '<S14>/Display15' : Unused code path elimination
 * Block '<S14>/Display16' : Unused code path elimination
 * Block '<S14>/Display17' : Unused code path elimination
 * Block '<S14>/Display18' : Unused code path elimination
 * Block '<S14>/Display19' : Unused code path elimination
 * Block '<S14>/Display2' : Unused code path elimination
 * Block '<S14>/Display20' : Unused code path elimination
 * Block '<S14>/Display21' : Unused code path elimination
 * Block '<S14>/Display22' : Unused code path elimination
 * Block '<S14>/Display23' : Unused code path elimination
 * Block '<S14>/Display24' : Unused code path elimination
 * Block '<S14>/Display25' : Unused code path elimination
 * Block '<S14>/Display26' : Unused code path elimination
 * Block '<S14>/Display27' : Unused code path elimination
 * Block '<S14>/Display28' : Unused code path elimination
 * Block '<S14>/Display29' : Unused code path elimination
 * Block '<S14>/Display3' : Unused code path elimination
 * Block '<S14>/Display30' : Unused code path elimination
 * Block '<S14>/Display31' : Unused code path elimination
 * Block '<S14>/Display32' : Unused code path elimination
 * Block '<S14>/Display33' : Unused code path elimination
 * Block '<S14>/Display34' : Unused code path elimination
 * Block '<S14>/Display35' : Unused code path elimination
 * Block '<S14>/Display36' : Unused code path elimination
 * Block '<S14>/Display37' : Unused code path elimination
 * Block '<S14>/Display38' : Unused code path elimination
 * Block '<S14>/Display39' : Unused code path elimination
 * Block '<S14>/Display4' : Unused code path elimination
 * Block '<S14>/Display40' : Unused code path elimination
 * Block '<S14>/Display41' : Unused code path elimination
 * Block '<S14>/Display42' : Unused code path elimination
 * Block '<S14>/Display43' : Unused code path elimination
 * Block '<S14>/Display44' : Unused code path elimination
 * Block '<S14>/Display45' : Unused code path elimination
 * Block '<S14>/Display46' : Unused code path elimination
 * Block '<S14>/Display47' : Unused code path elimination
 * Block '<S14>/Display48' : Unused code path elimination
 * Block '<S14>/Display49' : Unused code path elimination
 * Block '<S14>/Display5' : Unused code path elimination
 * Block '<S14>/Display6' : Unused code path elimination
 * Block '<S14>/Display7' : Unused code path elimination
 * Block '<S14>/Display8' : Unused code path elimination
 * Block '<S14>/Display9' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S16>/Constant8' : Unused code path elimination
 * Block '<S52>/Data Type Duplicate' : Unused code path elimination
 * Block '<S52>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/Scope1' : Unused code path elimination
 * Block '<S17>/Scope1' : Unused code path elimination
 * Block '<S18>/Constant2' : Unused code path elimination
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Constant1' : Unused code path elimination
 * Block '<S19>/Constant2' : Unused code path elimination
 * Block '<S19>/Constant3' : Unused code path elimination
 * Block '<S19>/Constant4' : Unused code path elimination
 * Block '<S19>/Constant6' : Unused code path elimination
 * Block '<S19>/Constant7' : Unused code path elimination
 * Block '<S62>/Data Type Duplicate' : Unused code path elimination
 * Block '<S62>/Data Type Propagation' : Unused code path elimination
 * Block '<S56>/Scope' : Unused code path elimination
 * Block '<S56>/Scope1' : Unused code path elimination
 * Block '<S63>/Constant1' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Propagation' : Unused code path elimination
 * Block '<S63>/Sum1' : Unused code path elimination
 * Block '<S57>/Data Type Duplicate' : Unused code path elimination
 * Block '<S57>/Data Type Propagation' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S58>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S59>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S60>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S25>/Shift Arithmetic1' : Eliminated trivial shift
 * Block '<S41>/Shift Arithmetic7' : Eliminated trivial shift
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
 * '<S6>'   : 'Senorless/FOC_PointModel/LPF'
 * '<S7>'   : 'Senorless/FOC_PointModel/Observers'
 * '<S8>'   : 'Senorless/FOC_PointModel/Park'
 * '<S9>'   : 'Senorless/FOC_PointModel/SVPWM'
 * '<S10>'  : 'Senorless/FOC_PointModel/idq_Controller'
 * '<S11>'  : 'Senorless/FOC_PointModel/sincos_512'
 * '<S12>'  : 'Senorless/FOC_PointModel/停止等待'
 * '<S13>'  : 'Senorless/FOC_PointModel/切闭环角度差'
 * '<S14>'  : 'Senorless/FOC_PointModel/初始化模块'
 * '<S15>'  : 'Senorless/FOC_PointModel/加速强拖'
 * '<S16>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖'
 * '<S17>'  : 'Senorless/FOC_PointModel/慢速开环'
 * '<S18>'  : 'Senorless/FOC_PointModel/电压限转速'
 * '<S19>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环'
 * '<S20>'  : 'Senorless/FOC_PointModel/预定位'
 * '<S21>'  : 'Senorless/FOC_PointModel/Err/PLL_LPF1'
 * '<S22>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断'
 * '<S23>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/SUM'
 * '<S24>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/ZERO'
 * '<S25>'  : 'Senorless/FOC_PointModel/Observers/PLL'
 * '<S26>'  : 'Senorless/FOC_PointModel/Observers/SMO'
 * '<S27>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller'
 * '<S28>'  : 'Senorless/FOC_PointModel/Observers/PLL/sincos_1'
 * '<S29>'  : 'Senorless/FOC_PointModel/Observers/PLL/积分器'
 * '<S30>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/Saturation Dynamic2'
 * '<S31>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器'
 * '<S32>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器/Saturation Dynamic2'
 * '<S33>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF1'
 * '<S34>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF2'
 * '<S35>'  : 'Senorless/FOC_PointModel/SVPWM/AntiClark'
 * '<S36>'  : 'Senorless/FOC_PointModel/SVPWM/ei_t'
 * '<S37>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller'
 * '<S38>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1'
 * '<S39>'  : 'Senorless/FOC_PointModel/idq_Controller/Saturation Dynamic1'
 * '<S40>'  : 'Senorless/FOC_PointModel/idq_Controller/Saturation Dynamic2'
 * '<S41>'  : 'Senorless/FOC_PointModel/idq_Controller/Subsystem'
 * '<S42>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/Saturation Dynamic2'
 * '<S43>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器'
 * '<S44>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器/Saturation Dynamic2'
 * '<S45>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/Saturation Dynamic2'
 * '<S46>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器'
 * '<S47>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器/Saturation Dynamic2'
 * '<S48>'  : 'Senorless/FOC_PointModel/idq_Controller/Subsystem/Wrap To Zero1'
 * '<S49>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度'
 * '<S50>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度/积分器3'
 * '<S51>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度/积分器4'
 * '<S52>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/Saturation Dynamic2'
 * '<S53>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/积分器'
 * '<S54>'  : 'Senorless/FOC_PointModel/慢速开环/积分器'
 * '<S55>'  : 'Senorless/FOC_PointModel/电压限转速/Saturation Dynamic2'
 * '<S56>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller'
 * '<S57>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Saturation Dynamic2'
 * '<S58>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero'
 * '<S59>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero1'
 * '<S60>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero2'
 * '<S61>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/速度缓冲'
 * '<S62>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/Saturation Dynamic2'
 * '<S63>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/积分器1'
 * '<S64>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/积分器1/Saturation Dynamic2'
 */
#endif                                 /* RTW_HEADER_FOC_PointModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
