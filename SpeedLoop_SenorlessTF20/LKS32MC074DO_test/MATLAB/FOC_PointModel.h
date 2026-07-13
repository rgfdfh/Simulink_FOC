/*
 * File: FOC_PointModel.h
 *
 * Code generated for Simulink model 'FOC_PointModel'.
 *
 * Model version                  : 4.212
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Sep  3 15:37:54 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_PointModel_h_
#define RTW_HEADER_FOC_PointModel_h_
#ifndef FOC_PointModel_COMMON_INCLUDES_
#define FOC_PointModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_PointModel_COMMON_INCLUDES_ */

#include "zero_crossing_types.h"

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
#define AMP_GAIN                       6.4F                      /* Referenced by: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 运算放大器倍数，单位：无 */
#define CURR_LIMIT                     0.8F              /* Referenced by: '<S14>/Constant34' *//* 电流环PI限幅，32768*n */
#define CURR_POINT_GAIN                7                         /* Referenced by:
                                                                  * '<S1>/电流采集适当放大系数2^n'
                                                                  * '<S14>/电流采集定点化适当放大2^n'
                                                                  *//* 相电流采集后采样值与定点值换算系数做适当放大，此处为2^n */
#define CURR_STEP                      6                         /* Referenced by:
                                                                  * '<S12>/Constant2'
                                                                  * '<S12>/Constant3'
                                                                  *//* 电流环每周期步进值 */
#define CURR_WIDTH                     400.0F                    /* Referenced by:
                                                                  * '<S14>/Constant11'
                                                                  * '<S14>/Constant9'
                                                                  *//* 电流环带宽，可使用此计算电流环kpki，在仿真模型的初始化模块中进行选择 */
#define DIVSQRT3                       18917                     /* Referenced by: '<S4>/Gain2' *//* 1/sqrt(3)*32767的值 */
#define FOC_FRQ                        25000.0                   /* Referenced by:
                                                                  * '<S14>/Constant18'
                                                                  * '<S14>/Constant21'
                                                                  * '<S14>/Constant22'
                                                                  * '<S14>/Constant30'
                                                                  * '<S14>/Constant8'
                                                                  *//* FOC触发频率 */
#define IMAX                           10.0F                     /* Referenced by:
                                                                  * '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  * '<S14>/Constant13'
                                                                  * '<S14>/Constant2'
                                                                  * '<S14>/Constant4'
                                                                  *//* 电流最大值，单位：A */
#define LPF_FRQ                        1500.0F                   /* Referenced by:
                                                                  * '<S14>/Constant19'
                                                                  * '<S14>/Constant28'
                                                                  * '<S14>/Constant31'
                                                                  *//* 观测器中低通滤波器截止频率，单位：Hz PS:这个也可以是最大转速的频率，用来计算滑模K */
#define MOTOR_FLUX                     0.00474F                  /* Referenced by: '<S14>/Constant29' *//* 电机磁链 */
#define MOTOR_LS                       4.0E-5F                   /* Referenced by:
                                                                  * '<S14>/Constant10'
                                                                  * '<S14>/Constant20'
                                                                  *//* 相电感 */
#define MOTOR_PN                       7.0F                      /* Referenced by: '<S14>/Gain2' *//* 电机极对数 */
#define MOTOR_RS                       0.38F                     /* Referenced by:
                                                                  * '<S14>/Constant12'
                                                                  * '<S14>/Constant15'
                                                                  *//* 相电阻 */
#define OPEN_IQ                        3276                      /* Referenced by:
                                                                  * '<S15>/Constant'
                                                                  * '<S16>/Constant'
                                                                  * '<S16>/Constant5'
                                                                  *//* 开环加速IQ */
#define OPEN_IQ_MIN                    327                       /* Referenced by: '<S16>/Constant6' *//* 切闭环降力矩降到这个数 */
#define OPEN_SPD                       1000.0F                   /* Referenced by: '<S14>/Constant5' *//* 开环最终速度,单位：RPM */
#define OPEN_TIME                      1.0F                      /* Referenced by:
                                                                  * '<S1>/Chart'
                                                                  * '<S14>/Constant14'
                                                                  *//* 开环加速时间，单位：s */
#define PLL_LIMIT                      0.95F                     /* Referenced by: '<S14>/Constant32' *//* 锁相环PI限幅，32768*n */
#define PLL_LPF_LEVEL                  8                         /* Referenced by:
                                                                  * '<S22>/Constant1'
                                                                  * '<S23>/Constant1'
                                                                  *//* PLL速度滤波器等级，范围0~15，越高滤波性越强 */
#define PLL_WIDTH                      200.0F                    /* Referenced by:
                                                                  * '<S14>/Constant25'
                                                                  * '<S14>/Constant26'
                                                                  *//* 锁相环带宽 */
#define PWM_FRQ                        9.6E+7F                   /* Referenced by: '<S14>/Constant7' *//* PWM计数器频率 */
#define RS_HUNT                        0.005F                    /* Referenced by: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 采样电阻，单位：欧 */
#define THETA_ERR_LIMIT                1200                      /* Referenced by: '<S1>/Chart' *//* 开环切闭环。开环角度与观测器角度误差小于这个才能切过去 */
#define TS_POINT_GAIN                  10                        /* Referenced by:
                                                                  * '<S14>/周期定点化适当放大2^n'
                                                                  * '<S26>/周期定点化适当放大2^n'
                                                                  * '<S44>/周期定点化适当放大2^n'
                                                                  * '<S50>/周期定点化适当放大2^n'
                                                                  * '<S59>/周期定点化适当放大2^n'
                                                                  * '<S60>/周期定点化适当放大2^n'
                                                                  * '<S67>/周期定点化适当放大2^n'
                                                                  * '<S28>/周期定点化适当放大2^n'
                                                                  *//* FOC频率的倒数适当放大,具体多少应该观察init模块中放大2^15后是多少，此处为2^n */
#define UDC_GAIN                       41.0F                     /* Referenced by: '<S14>/ADC量程*母线电压分压倍数//定义的最大电压值' *//* 母线电压分压倍数，单位：无 */
#define UDC_POINT_GAIN                 10                        /* Referenced by: '<S14>/电压采集定点化适当放大2' *//* 母线电压采集后采样值与定点值换算系数做适当放大,此处为2^n */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S19>/PLL_LPF1' */
typedef struct {
  int32_T UnitDelay9_DSTATE;           /* '<S22>/Unit Delay9' */
} DW_PLL_LPF1;

/* Block signals and states (default storage) for system '<S20>/SMO_LPF1' */
typedef struct {
  int32_T UnitDelay9_DSTATE;           /* '<S35>/Unit Delay9' */
} DW_SMO_LPF1;

/* Block signals and states (default storage) for system '<S58>/积分器//上升沿初始化' */
typedef struct {
  int32_T UnitDelay_DSTATE;            /* '<S59>/Unit Delay' */
  int32_T tmp;                         /* '<S59>/Data Store Memory' */
} DW_u;

/* Zero-crossing (trigger) state for system '<S58>/积分器//上升沿初始化' */
typedef struct {
  ZCSigState Reset_Block_Trig_ZCE_ju;  /* '<S59>/Reset_Block' */
} ZCE_u;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_u u_ae;                           /* '<S58>/积分器//上升沿初始化1' */
  DW_u u_k;                            /* '<S58>/积分器//上升沿初始化' */
  DW_SMO_LPF1 SMO_LPF2;                /* '<S20>/SMO_LPF2' */
  DW_SMO_LPF1 SMO_LPF1_f;              /* '<S20>/SMO_LPF1' */
  DW_PLL_LPF1 PLL_LPF2;                /* '<S19>/PLL_LPF2' */
  DW_PLL_LPF1 PLL_LPF1_f;              /* '<S19>/PLL_LPF1' */
  int32_T UnitDelay_DSTATE;            /* '<S50>/Unit Delay' */
  int32_T UnitDelay_DSTATE_n;          /* '<S44>/Unit Delay' */
  int32_T UnitDelay_DSTATE_j;          /* '<S67>/Unit Delay' */
  int32_T UnitDelay2_DSTATE;           /* '<S20>/Unit Delay2' */
  int32_T UnitDelay3_DSTATE;           /* '<S20>/Unit Delay3' */
  int32_T UnitDelay4_DSTATE;           /* '<S20>/Unit Delay4' */
  int32_T UnitDelay6_DSTATE;           /* '<S20>/Unit Delay6' */
  int32_T UnitDelay_DSTATE_l;          /* '<S26>/Unit Delay' */
  int32_T UnitDelay7_DSTATE;           /* '<S19>/Unit Delay7' */
  int32_T UnitDelay3_DSTATE_p;         /* '<S19>/Unit Delay3' */
  int32_T UnitDelay2_DSTATE_h;         /* '<S19>/Unit Delay2' */
  int32_T UnitDelay_DSTATE_f;          /* '<S28>/Unit Delay' */
  int32_T DIV_LPF_FRQ;                 /* '<S1>/1//LPF_FRQ' */
  int32_T Curr_Ki_Point;               /* '<S1>/电流环Ki' */
  int32_T Curr_Kp_Point;               /* '<S1>/电流环Kp' */
  int32_T Curr_Limit;                  /* '<S1>/电流环PI限幅' */
  int32_T PLL_Ki;                      /* '<S1>/锁相环Ki' */
  int32_T PLL_Limit;                   /* '<S1>/锁相环PI限幅' */
  uint32_T temporalCounter_i1;         /* '<S1>/Chart' */
  uint32_T temporalCounter_i2;         /* '<S1>/Chart' */
  int16_T sin512[512];                 /* '<S1>/Sin2_512' */
  int16_T sin512_h[512];               /* '<S19>/Sin2_1' */
  int16_T Merge2;                      /* '<S1>/Merge2' */
  int16_T Merge1;                      /* '<S1>/Merge1' */
  int16_T UnitDelay4_DSTATE_j;         /* '<S12>/Unit Delay4' */
  int16_T UnitDelay3_DSTATE_g;         /* '<S12>/Unit Delay3' */
  int16_T UnitDelay1_DSTATE;           /* '<S16>/Unit Delay1' */
  int16_T FOC_FRQ_Point;               /* '<S1>/FOC整数类型频率' */
  int16_T PWM_TH;                      /* '<S1>/PWM周期值' */
  int16_T Ts_Point;                    /* '<S1>/PWM周期时间' */
  int16_T SMO_K;                       /* '<S1>/SMO增益K' */
  int16_T LPF_FRQ_Point;               /* '<S1>/SMO里低通滤波器频率' */
  int16_T Open_Acceleration;           /* '<S1>/开环加速度' */
  int16_T Open_Hz;                     /* '<S1>/开环最终转速' */
  int16_T Curr_Conversion;             /* '<S1>/电流采集定点化换算系数' */
  int16_T Obs_VtoI;                    /* '<S1>/观测器电流转电压衡量系数' */
  int16_T PLL_Kp;                      /* '<S1>/锁相环Kp' */
  uint16_T atan256[256];               /* '<S19>/atan_1' */
  uint16_T Merge;                      /* '<S1>/Merge' */
  uint16_T UnitDelay7_DSTATE_p;        /* '<S1>/Unit Delay7' */
  uint16_T UnitDelay6_DSTATE_a;        /* '<S1>/Unit Delay6' */
  uint16_T UnitDelay4_DSTATE_g;        /* '<S1>/Unit Delay4' */
  uint16_T UnitDelay1_DSTATE_b;        /* '<S1>/Unit Delay1' */
  uint16_T UnitDelay5_DSTATE;          /* '<S1>/Unit Delay5' */
  uint16_T SMO_Gain1;                  /* '<S1>/1-Ts(Rs//Ls)' */
  uint16_T SMO_Gain2;                  /* '<S1>/Ts//Ls' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
  uint8_T Motor_state;                 /* '<S1>/Chart' */
  uint8_T Angles_Reset_Signal;         /* '<S1>/Chart' */
  uint8_T Curr_Reset_Sinal;            /* '<S1>/Chart' */
  uint8_T is_active_c2_FOC_PointModel; /* '<S1>/Chart' */
  uint8_T is_c2_FOC_PointModel;        /* '<S1>/Chart' */
} DW;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Reset_Block_Trig_ZCE;     /* '<S50>/Reset_Block' */
  ZCSigState Reset_Block_Trig_ZCE_j;   /* '<S44>/Reset_Block' */
  ZCSigState Reset_Block_Trig_ZCE_e;   /* '<S67>/Reset_Block' */
  ZCE_u u_ae;                          /* '<S58>/积分器//上升沿初始化1' */
  ZCE_u u_k;                           /* '<S58>/积分器//上升沿初始化' */
  ZCSigState Reset_Block_Trig_ZCE_h;   /* '<S26>/Reset_Block' */
  ZCSigState Reset_Block_Trig_ZCE_m;   /* '<S28>/Reset_Block' */
} PrevZCX;

/* Invariant block signals for system '<S19>/PLL_LPF1' */
typedef struct {
  const int16_T ShiftArithmetic1;      /* '<S22>/Shift Arithmetic1' */
} ConstB_PLL_LPF1;

/* Invariant block signals for system '<S20>/SMO_LPF1' */
typedef struct {
  const int16_T ShiftArithmetic1;      /* '<S35>/Shift Arithmetic1' */
} ConstB_SMO_LPF1;

/* Invariant block signals (default storage) */
typedef struct {
  ConstB_SMO_LPF1 SMO_LPF2;            /* '<S20>/SMO_LPF2' */
  ConstB_SMO_LPF1 SMO_LPF1_f;          /* '<S20>/SMO_LPF1' */
  ConstB_PLL_LPF1 PLL_LPF2;            /* '<S19>/PLL_LPF2' */
  ConstB_PLL_LPF1 PLL_LPF1_f;          /* '<S19>/PLL_LPF1' */
} ConstB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int16_T ia;                          /* '<Root>/ia' */
  int16_T ib;                          /* '<Root>/ib' */
  int16_T ic;                          /* '<Root>/ic' */
  int16_T v_bus;                       /* '<Root>/v_bus' */
  int16_T Motor_OnOff;                 /* '<Root>/Motor_OnOff' */
  real_T Theta;                        /* '<Root>/Theta' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint16_T tABC[3];                    /* '<Root>/tABC' */
  uint16_T Obs_Theta;                  /* '<Root>/Obs_Theta' */
  int16_T Obs_Spd;                     /* '<Root>/Obs_Spd' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Zero-crossing (trigger) state */
extern PrevZCX rtPrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern int16_T Udc;                    /* Variable: Udc
                                        * Referenced by:
                                        *   '<S14>/Constant'
                                        *   '<S14>/Constant16'
                                        * 仿真使用的假设输入母线电压，实际由ADC采样获取。注意，在实际使用时应当在初始化部分重新读一次母线电压，用作初始化变量，不然默认使用字典值，单位：V
                                        */

/* Model entry point functions */
extern void FOC_PointModel_initialize(void);
extern void FOC_PointModel_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Conversion1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion7' : Unused code path elimination
 * Block '<S1>/Data Type Conversion8' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S21>/Scope' : Unused code path elimination
 * Block '<S28>/Scope' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S19>/Scope1' : Unused code path elimination
 * Block '<S19>/Scope2' : Unused code path elimination
 * Block '<S19>/Scope7' : Unused code path elimination
 * Block '<S20>/Constant1' : Unused code path elimination
 * Block '<S20>/Display' : Unused code path elimination
 * Block '<S20>/Scope' : Unused code path elimination
 * Block '<S20>/Scope1' : Unused code path elimination
 * Block '<S20>/Scope2' : Unused code path elimination
 * Block '<S20>/Scope3' : Unused code path elimination
 * Block '<S20>/Scope5' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S10>/Scope' : Unused code path elimination
 * Block '<S10>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope12' : Unused code path elimination
 * Block '<S1>/Scope13' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 * Block '<S1>/Scope5' : Unused code path elimination
 * Block '<S1>/Scope6' : Unused code path elimination
 * Block '<S1>/Scope7' : Unused code path elimination
 * Block '<S1>/Scope8' : Unused code path elimination
 * Block '<S1>/Scope9' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Unit Delay2' : Unused code path elimination
 * Block '<S1>/Unit Delay3' : Unused code path elimination
 * Block '<S41>/Scope' : Unused code path elimination
 * Block '<S42>/Scope' : Unused code path elimination
 * Block '<S50>/Scope' : Unused code path elimination
 * Block '<S12>/Scope1' : Unused code path elimination
 * Block '<S12>/Scope2' : Unused code path elimination
 * Block '<S12>/Scope3' : Unused code path elimination
 * Block '<S12>/Scope4' : Unused code path elimination
 * Block '<S12>/Scope5' : Unused code path elimination
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
 * Block '<S14>/Display3' : Unused code path elimination
 * Block '<S14>/Display4' : Unused code path elimination
 * Block '<S14>/Display5' : Unused code path elimination
 * Block '<S14>/Display6' : Unused code path elimination
 * Block '<S14>/Display7' : Unused code path elimination
 * Block '<S14>/Display8' : Unused code path elimination
 * Block '<S14>/Display9' : Unused code path elimination
 * Block '<S59>/Scope' : Unused code path elimination
 * Block '<S60>/Scope' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S65>/Scope1' : Unused code path elimination
 * Block '<S65>/Scope3' : Unused code path elimination
 * Block '<S67>/Scope' : Unused code path elimination
 * Block '<S16>/Scope2' : Unused code path elimination
 * Block '<S17>/Constant1' : Unused code path elimination
 * Block '<S17>/Constant4' : Unused code path elimination
 * Block '<S17>/Constant5' : Unused code path elimination
 * Block '<S17>/Saturation2' : Unused code path elimination
 * Block '<S17>/Sum1' : Unused code path elimination
 * Block '<S17>/Sum2' : Unused code path elimination
 * Block '<S17>/Sum3' : Unused code path elimination
 * Block '<S17>/Unit Delay2' : Unused code path elimination
 * Block '<S1>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S19>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S19>/Shift Arithmetic2' : Eliminated trivial shift
 * Block '<S26>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S14>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S14>/Gain3' : Eliminated nontunable gain of 1
 * Block '<S59>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S60>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S58>/这个是缩小积分增益的' : Eliminated trivial shift
 * Block '<S65>/这个是缩小积分增益的' : Eliminated trivial shift
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
 * '<S5>'   : 'Senorless/FOC_PointModel/MATLAB Function'
 * '<S6>'   : 'Senorless/FOC_PointModel/MATLAB Function1'
 * '<S7>'   : 'Senorless/FOC_PointModel/MATLAB Function2'
 * '<S8>'   : 'Senorless/FOC_PointModel/Observers'
 * '<S9>'   : 'Senorless/FOC_PointModel/Park'
 * '<S10>'  : 'Senorless/FOC_PointModel/SVPWM'
 * '<S11>'  : 'Senorless/FOC_PointModel/Sin2_512'
 * '<S12>'  : 'Senorless/FOC_PointModel/idq_Controller'
 * '<S13>'  : 'Senorless/FOC_PointModel/停止等待'
 * '<S14>'  : 'Senorless/FOC_PointModel/初始化模块'
 * '<S15>'  : 'Senorless/FOC_PointModel/加速强拖'
 * '<S16>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖'
 * '<S17>'  : 'Senorless/FOC_PointModel/观测器闭环'
 * '<S18>'  : 'Senorless/FOC_PointModel/预定位'
 * '<S19>'  : 'Senorless/FOC_PointModel/Observers/PLL'
 * '<S20>'  : 'Senorless/FOC_PointModel/Observers/SMO'
 * '<S21>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller'
 * '<S22>'  : 'Senorless/FOC_PointModel/Observers/PLL/PLL_LPF1'
 * '<S23>'  : 'Senorless/FOC_PointModel/Observers/PLL/PLL_LPF2'
 * '<S24>'  : 'Senorless/FOC_PointModel/Observers/PLL/Sin2_1'
 * '<S25>'  : 'Senorless/FOC_PointModel/Observers/PLL/atan_1'
 * '<S26>'  : 'Senorless/FOC_PointModel/Observers/PLL/积分器//上升沿初始化'
 * '<S27>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/MATLAB Function'
 * '<S28>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器//上升沿初始化'
 * '<S29>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器//上升沿初始化/MATLAB Function'
 * '<S30>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器//上升沿初始化/MATLAB Function1'
 * '<S31>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器//上升沿初始化/MATLAB Function2'
 * '<S32>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller/积分器//上升沿初始化/Reset_Block'
 * '<S33>'  : 'Senorless/FOC_PointModel/Observers/PLL/积分器//上升沿初始化/MATLAB Function2'
 * '<S34>'  : 'Senorless/FOC_PointModel/Observers/PLL/积分器//上升沿初始化/Reset_Block'
 * '<S35>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF1'
 * '<S36>'  : 'Senorless/FOC_PointModel/Observers/SMO/SMO_LPF2'
 * '<S37>'  : 'Senorless/FOC_PointModel/SVPWM/AntiClark'
 * '<S38>'  : 'Senorless/FOC_PointModel/SVPWM/ei_t'
 * '<S39>'  : 'Senorless/FOC_PointModel/idq_Controller/MATLAB Function1'
 * '<S40>'  : 'Senorless/FOC_PointModel/idq_Controller/MATLAB Function2'
 * '<S41>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller'
 * '<S42>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1'
 * '<S43>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/MATLAB Function'
 * '<S44>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器//双边沿初始化'
 * '<S45>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器//双边沿初始化/MATLAB Function'
 * '<S46>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器//双边沿初始化/MATLAB Function1'
 * '<S47>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器//双边沿初始化/MATLAB Function2'
 * '<S48>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器//双边沿初始化/Reset_Block'
 * '<S49>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/MATLAB Function'
 * '<S50>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器//双边沿初始化'
 * '<S51>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器//双边沿初始化/MATLAB Function'
 * '<S52>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器//双边沿初始化/MATLAB Function1'
 * '<S53>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器//双边沿初始化/MATLAB Function2'
 * '<S54>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器//双边沿初始化/Reset_Block'
 * '<S55>'  : 'Senorless/FOC_PointModel/初始化模块/MATLAB Function'
 * '<S56>'  : 'Senorless/FOC_PointModel/初始化模块/MATLAB Function1'
 * '<S57>'  : 'Senorless/FOC_PointModel/初始化模块/MATLAB Function2'
 * '<S58>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point'
 * '<S59>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化'
 * '<S60>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化1'
 * '<S61>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化/MATLAB Function'
 * '<S62>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化/Reset_Block'
 * '<S63>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化1/MATLAB Function'
 * '<S64>'  : 'Senorless/FOC_PointModel/加速强拖/FreqGenerator_point/积分器//上升沿初始化1/Reset_Block'
 * '<S65>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/FreqGenerator_point'
 * '<S66>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/MATLAB Function1'
 * '<S67>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/FreqGenerator_point/积分器//下降沿初始化'
 * '<S68>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/FreqGenerator_point/积分器//下降沿初始化/MATLAB Function'
 * '<S69>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/FreqGenerator_point/积分器//下降沿初始化/Reset_Block'
 */
#endif                                 /* RTW_HEADER_FOC_PointModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
