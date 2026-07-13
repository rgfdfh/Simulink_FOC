/*
 * File: FOC_PointModel.h
 *
 * Code generated for Simulink model 'FOC_PointModel'.
 *
 * Model version                  : 4.287
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Tue Dec 30 15:51:59 2025
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
                                                                  * '<S13>/ADC量程*母线电压分压倍数//定义的最大电压值'
                                                                  * '<S13>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  *//* ADC采样最大电压幅值，也应该为处理飘零后的范围，也应该会是总量程的一半。因为有部分ADC不能采负值所以会整体抬高一半，此时就得总量程/2=这里的数值 */
#define AMP_GAIN                       16.0F                     /* Referenced by: '<S13>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 运算放大器倍数，单位：无 */
#define CURR_LIMIT                     0.95F                     /* Referenced by: '<S13>/Constant34' *//* 电流环PI限幅，32768*n */
#define CURR_OVER                      6.0F                      /* Referenced by: '<S13>/Constant50' *//* 过流保护值，应注意不能大于IMAX。单位：A */
#define CURR_POINT_GAIN                7                         /* Referenced by:
                                                                  * '<S1>/电流采集适当放大系数2^n'
                                                                  * '<S13>/电流采集定点化适当放大2^n'
                                                                  *//* 相电流采集后采样值与定点值换算系数做适当放大，此处为2^n */
#define CURR_STEP                      32760                     /* Referenced by:
                                                                  * '<S9>/Constant1'
                                                                  * '<S9>/Constant2'
                                                                  * '<S9>/Constant3'
                                                                  * '<S9>/Constant8'
                                                                  *//* 电流环每周期步进值 */
#define CURR_UNDER                     0.03F                     /* Referenced by: '<S13>/Constant58' *//* 欠流值，为了处理出现堵住但观测器发散、实际电机电流很小的情况。单位：A
                                                                      */
#define CURR_WIDTH                     6552.0F                   /* Referenced by:
                                                                  * '<S13>/Constant11'
                                                                  * '<S13>/Constant9'
                                                                  *//* 电流环带宽，可使用此计算电流环kpki，在仿真模型的初始化模块中进行选择 */
#define FOC_FRQ                        25000.0                   /* Referenced by:
                                                                  * '<S13>/Constant18'
                                                                  * '<S13>/Constant21'
                                                                  * '<S13>/Constant22'
                                                                  * '<S13>/Constant30'
                                                                  * '<S13>/Constant8'
                                                                  *//* FOC触发频率，不能在生成代码后更改，只能在字典改。 */
#define IMAX                           10.0F                     /* Referenced by:
                                                                  * '<S13>/ADC量程//放大器倍数//定义的最大电流//采样电流'
                                                                  * '<S13>/Constant13'
                                                                  * '<S13>/Constant2'
                                                                  * '<S13>/Constant4'
                                                                  * '<S13>/Constant43'
                                                                  * '<S13>/Constant53'
                                                                  * '<S13>/Constant55'
                                                                  * '<S13>/Constant56'
                                                                  * '<S13>/Constant60'
                                                                  * '<S13>/Gain5'
                                                                  * '<S13>/Gain7'
                                                                  * '<S13>/Saturation'
                                                                  * '<S13>/Saturation1'
                                                                  * '<S13>/Saturation2'
                                                                  * '<S13>/Saturation3'
                                                                  * '<S13>/Saturation4'
                                                                  *//* 电流最大值，单位：A */
#define LPF_FRQ                        2000.0F                   /* Referenced by:
                                                                  * '<S13>/Constant19'
                                                                  * '<S13>/Constant31'
                                                                  *//* 观测器中低通滤波器截止频率，单位：Hz */
#define MOTOR_FLUX                     0.00212352F               /* Referenced by:
                                                                  * '<S13>/Constant29'
                                                                  * '<S13>/Constant42'
                                                                  * '<S13>/Constant62'
                                                                  * '<S13>/Constant63'
                                                                  * '<S13>/Constant65'
                                                                  *//* 电机磁链 */
#define MOTOR_INERTIA                  4.0E-7F                   /* Referenced by:
                                                                  * '<S13>/Constant40'
                                                                  * '<S13>/Constant45'
                                                                  *//* 电机转动惯量，单位：kgm^2 */
#define MOTOR_LS                       0.000536F                 /* Referenced by:
                                                                  * '<S13>/Constant10'
                                                                  * '<S13>/Constant20'
                                                                  * '<S13>/Constant61'
                                                                  *//* 相电感 */
#define MOTOR_PN                       7.0F                      /* Referenced by:
                                                                  * '<S13>/Constant41'
                                                                  * '<S13>/Constant49'
                                                                  * '<S13>/Gain2'
                                                                  * '<S13>/Gain6'
                                                                  *//* 电机极对数 */
#define MOTOR_RS                       4.0F                      /* Referenced by:
                                                                  * '<S13>/Constant12'
                                                                  * '<S13>/Constant15'
                                                                  * '<S13>/Constant59'
                                                                  *//* 相电阻 */
#define OPEN_IQ                        0.28F                     /* Referenced by: '<S13>/Constant52' *//* 开环加速IQ。单位：A */
#define OPEN_IQ_MIN                    0.05F                     /* Referenced by: '<S13>/Constant54' *//* 切闭环降力矩降到这个数.单位：A */
#define OPEN_IQ_SLOW                   0.1F                      /* Referenced by: '<S13>/Constant6' *//* 慢速强拖IQ，单位：A */
#define OPEN_SPD                       1000                      /* Referenced by:
                                                                  * '<S13>/Constant5'
                                                                  * '<S13>/Constant70'
                                                                  * '<S18>/Constant12'
                                                                  * '<S18>/Unit Delay3'
                                                                  *//* 开环最终速度,单位：RPM */
#define OPEN_SPD_SLOW                  180.0F                    /* Referenced by: '<S13>/Constant57' *//* 慢速强拖转速，单位：RPM */
#define OPEN_TIME                      0.5F                      /* Referenced by:
                                                                  * '<S1>/Chart'
                                                                  * '<S13>/Constant14'
                                                                  *//* 开环加速时间，单位：s */
#define OPEN_TIME_NFO                  0.5F                      /* Referenced by: '<S13>/Constant67' *//* 不同于开环强拖，这个是使用非线性磁链直接闭环后防止打桨将加速强拖那段加进来的缓冲时间 */
#define PLL_LIMIT                      0.9F                      /* Referenced by: '<S13>/Constant32' *//* 锁相环PI限幅，32768*n */
#define PLL_WIDTH                      800.0F                    /* Referenced by:
                                                                  * '<S13>/Constant25'
                                                                  * '<S13>/Constant26'
                                                                  *//* 锁相环带宽 */
#define PWM_FRQ                        9.6E+7F                   /* Referenced by: '<S13>/Constant7' *//* PWM计数器频率 */
#define RS_HUNT                        0.02F                     /* Referenced by: '<S13>/ADC量程//放大器倍数//定义的最大电流//采样电流' *//* 采样电阻，单位：欧 */
#define SMOK_FRQ                       600.0F                    /* Referenced by: '<S13>/Constant28' *//* 滑模增益K，公式电角速度*磁链，即反电动势峰值。单位：Hz */
#define SPD_LIMIT                      0.9F                      /* Referenced by: '<S13>/Constant47' *//* 速度环PI限幅，32768*n */
#define SPD_LPF_LEVEL                  0                         /* Referenced by: '<S26>/Constant1' *//* PLL速度滤波器等级，范围0~15，越高滤波性越强 */
#define SPD_MAX                        12000                     /* Referenced by: '<S17>/Constant6' *//* 最大转速，这个为实际使用时使用标准电压正常工作所会达到的最大值，用于降压时限制最大转速。单位：RPM */
#define SPD_MIN                        4000                      /* Referenced by: '<S17>/Constant7' *//* 进入闭环后最低目标转速，单位：RPM */
#define SPD_REDUCE                     380                       /* Referenced by: '<S17>/Constant1' *//* 每降1V少多少转速，我认为是kv值。单位：RPM */
#define SPD_STEP                       6                         /* Referenced by:
                                                                  * '<S18>/Constant5'
                                                                  * '<S18>/Constant8'
                                                                  *//* 速度环步进值 */
#define SPD_WIDTH                      20.0F                     /* Referenced by:
                                                                  * '<S13>/Constant39'
                                                                  * '<S13>/Constant44'
                                                                  * '<S13>/Constant46'
                                                                  *//* 速度环带宽 */
#define THETA_ERR_LIMIT                8192                      /* Referenced by: '<S1>/Chart' *//* 开环切闭环。开环角度与观测器角度误差小于这个才能切过去 */
#define TS_POINT_GAIN                  10                        /* Referenced by:
                                                                  * '<S13>/周期定点化适当放大2^n'
                                                                  * '<S51>/周期定点化适当放大2^n'
                                                                  * '<S52>/周期定点化适当放大2^n'
                                                                  * '<S29>/周期定点化适当放大2^n'
                                                                  * '<S42>/周期定点化适当放大2^n'
                                                                  * '<S45>/周期定点化适当放大2^n'
                                                                  * '<S48>/周期定点化适当放大2^n'
                                                                  * '<S49>/周期定点化适当放大2^n'
                                                                  * '<S31>/周期定点化适当放大2^n'
                                                                  *//* FOC频率的倒数适当放大,具体多少应该观察init模块中放大2^15后是多少，此处为2^n */
#define UDC                            48                        /* Referenced by:
                                                                  * '<S13>/Constant'
                                                                  * '<S13>/Constant16'
                                                                  * '<S13>/Constant69'
                                                                  * '<S13>/Constant71'
                                                                  * '<S13>/Constant72'
                                                                  * '<S17>/Constant4'
                                                                  * '<S17>/Constant5'
                                                                  * '<S17>/Saturation'
                                                                  *//* 基准母线电压，电压比这个低的时候会有些处理。 */
#define UDC_GAIN                       21.0F                     /* Referenced by: '<S13>/ADC量程*母线电压分压倍数//定义的最大电压值' *//* 母线电压分压倍数，单位：无 */
#define UDC_POINT_GAIN                 10                        /* Referenced by:
                                                                  * '<S1>/Constant33'
                                                                  * '<S13>/电压采集定点化适当放大2^n'
                                                                  *//* 母线电压采集后采样值与定点值换算系数做适当放大,此处为2^n */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  int32_T Ud;                          /* '<S9>/Shift Arithmetic4' */
  int32_T Uq;                          /* '<S9>/Shift Arithmetic5' */
  int32_T SPD_Ref;                     /* '<S18>/速度缓冲' */
  int32_T UnitDelay_DSTATE;            /* '<S42>/Unit Delay' */
  int32_T UnitDelay_DSTATE_f;          /* '<S45>/Unit Delay' */
  int32_T UnitDelay_DSTATE_h;          /* '<S52>/Unit Delay' */
  int32_T UnitDelay3_DSTATE_m;         /* '<S18>/Unit Delay3' */
  int32_T Delay_DSTATE;                /* '<S51>/Delay' */
  int32_T UnitDelay_DSTATE_b;          /* '<S49>/Unit Delay' */
  int32_T UnitDelay_DSTATE_d;          /* '<S48>/Unit Delay' */
  int32_T UnitDelay4_DSTATE;           /* '<S25>/Unit Delay4' */
  int32_T UnitDelay6_DSTATE;           /* '<S25>/Unit Delay6' */
  int32_T UnitDelay1_DSTATE;           /* '<S33>/Unit Delay1' */
  int32_T UnitDelay2_DSTATE;           /* '<S25>/Unit Delay2' */
  int32_T UnitDelay3_DSTATE_l;         /* '<S25>/Unit Delay3' */
  int32_T UnitDelay1_DSTATE_m;         /* '<S34>/Unit Delay1' */
  int32_T UnitDelay_DSTATE_p;          /* '<S31>/Unit Delay' */
  int32_T UnitDelay_DSTATE_m;          /* '<S29>/Unit Delay' */
  int32_T UnitDelay1_DSTATE_p;         /* '<S24>/Unit Delay1' */
  int32_T UnitDelay_DSTATE_k;          /* '<S21>/Unit Delay' */
  int32_T UnitDelay2_DSTATE_a;         /* '<S22>/Unit Delay2' */
  int32_T UnitDelay9_DSTATE_j;         /* '<S20>/Unit Delay9' */
  int32_T DIV_LPF_FRQ;                 /* '<S1>/1//LPF_FRQ' */
  int32_T FOC_FRQ_Point;               /* '<S1>/FOC整数类型频率' */
  int32_T Curr_Under;                  /* '<S1>/欠流保护值' */
  int32_T Curr_Ki_Point;               /* '<S1>/电流环Ki' */
  int32_T Curr_Kp_Point;               /* '<S1>/电流环Kp' */
  int32_T Curr_Limit;                  /* '<S1>/电流环PI限幅' */
  int32_T Curr_Over;                   /* '<S1>/过流保护值' */
  int32_T Speed_Kp_Point;              /* '<S1>/速度环Kp' */
  int32_T Speed_Limit;                 /* '<S1>/速度环限幅' */
  int32_T PLL_Ki;                      /* '<S1>/锁相环Ki' */
  int32_T PLL_Limit;                   /* '<S1>/锁相环PI限幅' */
  uint32_T temporalCounter_i1;         /* '<S1>/Chart' */
  int16_T Merge2;                      /* '<S1>/Merge2' */
  int16_T Merge1;                      /* '<S1>/Merge1' */
  int16_T Abs;                         /* '<S12>/Abs' */
  int16_T UnitDelay4_DSTATE_j;         /* '<S9>/Unit Delay4' */
  int16_T UnitDelay3_DSTATE_d;         /* '<S9>/Unit Delay3' */
  int16_T Delay_DSTATE_h;              /* '<S18>/Delay' */
  int16_T Delay1_DSTATE;               /* '<S18>/Delay1' */
  int16_T UnitDelay1_DSTATE_g;         /* '<S15>/Unit Delay1' */
  int16_T UnitDelay4_DSTATE_d;         /* '<S19>/Unit Delay4' */
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
  int16_T Hz_RPM;                      /* '<S1>/电赫兹换算机械转速' */
  int16_T Obs_VtoI;                    /* '<S1>/观测器电流转电压衡量系数' */
  int16_T PLL_Kp;                      /* '<S1>/锁相环Kp' */
  uint16_T Merge;                      /* '<S1>/Merge' */
  uint16_T UnitDelay1_DSTATE_b;        /* '<S1>/Unit Delay1' */
  uint16_T UnitDelay7_DSTATE;          /* '<S12>/Unit Delay7' */
  uint16_T UnitDelay6_DSTATE_a;        /* '<S12>/Unit Delay6' */
  uint16_T UnitDelay5_DSTATE;          /* '<S12>/Unit Delay5' */
  uint16_T SMO_Gain1;                  /* '<S1>/1-Ts(Rs//Ls)' */
  uint16_T SMO_Gain2;                  /* '<S1>/Ts//Ls' */
  uint16_T temporalCounter_i1_m;       /* '<S18>/速度缓冲' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S1>/Switch Case' */
  int8_T If1_ActiveSubsystem;          /* '<S21>/If1' */
  uint8_T Motor_State;                 /* '<S1>/Chart' */
  uint8_T is_active_c48_FOC_PointModel;/* '<S18>/速度缓冲' */
  uint8_T is_c48_FOC_PointModel;       /* '<S18>/速度缓冲' */
  uint8_T is_active_c2_FOC_PointModel; /* '<S1>/Chart' */
  uint8_T is_c2_FOC_PointModel;        /* '<S1>/Chart' */
  boolean_T OR1;                       /* '<S21>/OR1' */
  boolean_T icLoad;                    /* '<S18>/Delay' */
  boolean_T icLoad_l;                  /* '<S18>/Delay1' */
  boolean_T icLoad_d;                  /* '<S51>/Delay' */
  boolean_T _MODE;                     /* '<S1>/切闭环角度差' */
  boolean_T idq_Controller_MODE;       /* '<S1>/idq_Controller' */
  boolean_T Observers_MODE;            /* '<S1>/Observers' */
  boolean_T _MODE_p;                   /* '<S5>/闭环错误判断' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: int16(32767*sin(linspace(0,2*pi,512))))
   * Referenced by:
   *   '<S10>/Sin'
   *   '<S10>/Sin1'
   *   '<S28>/Sin'
   *   '<S28>/Sin1'
   */
  int16_T pooled14[512];

  /* Expression: uint16(16384*atan(linspace(0,1,256)))
   * Referenced by: '<S24>/atan256'
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
 * Block '<S1>/Data Type Conversion7' : Unused code path elimination
 * Block '<S1>/Data Type Conversion8' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S21>/Scope' : Unused code path elimination
 * Block '<S21>/Scope1' : Unused code path elimination
 * Block '<S21>/Scope2' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Scope' : Unused code path elimination
 * Block '<S31>/Constant' : Unused code path elimination
 * Block '<S32>/Data Type Duplicate' : Unused code path elimination
 * Block '<S32>/Data Type Propagation' : Unused code path elimination
 * Block '<S31>/Sum2' : Unused code path elimination
 * Block '<S24>/Scope' : Unused code path elimination
 * Block '<S24>/Scope1' : Unused code path elimination
 * Block '<S24>/Scope8' : Unused code path elimination
 * Block '<S24>/Shift Arithmetic3' : Unused code path elimination
 * Block '<S25>/Display' : Unused code path elimination
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
 * Block '<S25>/Scope' : Unused code path elimination
 * Block '<S25>/Scope1' : Unused code path elimination
 * Block '<S25>/Scope2' : Unused code path elimination
 * Block '<S25>/Scope4' : Unused code path elimination
 * Block '<S25>/Scope5' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S8>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope11' : Unused code path elimination
 * Block '<S1>/Scope12' : Unused code path elimination
 * Block '<S1>/Scope13' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 * Block '<S1>/Scope4' : Unused code path elimination
 * Block '<S1>/Scope5' : Unused code path elimination
 * Block '<S1>/Scope6' : Unused code path elimination
 * Block '<S1>/Scope7' : Unused code path elimination
 * Block '<S1>/Scope8' : Unused code path elimination
 * Block '<S1>/Scope9' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<S1>/Unit Delay5' : Unused code path elimination
 * Block '<S41>/Data Type Duplicate' : Unused code path elimination
 * Block '<S41>/Data Type Propagation' : Unused code path elimination
 * Block '<S37>/Scope' : Unused code path elimination
 * Block '<S42>/Constant' : Unused code path elimination
 * Block '<S43>/Data Type Duplicate' : Unused code path elimination
 * Block '<S43>/Data Type Propagation' : Unused code path elimination
 * Block '<S42>/Sum2' : Unused code path elimination
 * Block '<S44>/Data Type Duplicate' : Unused code path elimination
 * Block '<S44>/Data Type Propagation' : Unused code path elimination
 * Block '<S38>/Scope' : Unused code path elimination
 * Block '<S45>/Constant' : Unused code path elimination
 * Block '<S46>/Data Type Duplicate' : Unused code path elimination
 * Block '<S46>/Data Type Propagation' : Unused code path elimination
 * Block '<S45>/Sum2' : Unused code path elimination
 * Block '<S39>/Data Type Duplicate' : Unused code path elimination
 * Block '<S39>/Data Type Propagation' : Unused code path elimination
 * Block '<S40>/Data Type Duplicate' : Unused code path elimination
 * Block '<S40>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/Scope3' : Unused code path elimination
 * Block '<S13>/Constant23' : Unused code path elimination
 * Block '<S13>/Constant3' : Unused code path elimination
 * Block '<S13>/Display1' : Unused code path elimination
 * Block '<S13>/Display10' : Unused code path elimination
 * Block '<S13>/Display11' : Unused code path elimination
 * Block '<S13>/Display12' : Unused code path elimination
 * Block '<S13>/Display13' : Unused code path elimination
 * Block '<S13>/Display14' : Unused code path elimination
 * Block '<S13>/Display15' : Unused code path elimination
 * Block '<S13>/Display16' : Unused code path elimination
 * Block '<S13>/Display17' : Unused code path elimination
 * Block '<S13>/Display18' : Unused code path elimination
 * Block '<S13>/Display19' : Unused code path elimination
 * Block '<S13>/Display2' : Unused code path elimination
 * Block '<S13>/Display20' : Unused code path elimination
 * Block '<S13>/Display21' : Unused code path elimination
 * Block '<S13>/Display22' : Unused code path elimination
 * Block '<S13>/Display23' : Unused code path elimination
 * Block '<S13>/Display24' : Unused code path elimination
 * Block '<S13>/Display25' : Unused code path elimination
 * Block '<S13>/Display26' : Unused code path elimination
 * Block '<S13>/Display27' : Unused code path elimination
 * Block '<S13>/Display28' : Unused code path elimination
 * Block '<S13>/Display29' : Unused code path elimination
 * Block '<S13>/Display3' : Unused code path elimination
 * Block '<S13>/Display30' : Unused code path elimination
 * Block '<S13>/Display31' : Unused code path elimination
 * Block '<S13>/Display32' : Unused code path elimination
 * Block '<S13>/Display33' : Unused code path elimination
 * Block '<S13>/Display34' : Unused code path elimination
 * Block '<S13>/Display35' : Unused code path elimination
 * Block '<S13>/Display36' : Unused code path elimination
 * Block '<S13>/Display37' : Unused code path elimination
 * Block '<S13>/Display38' : Unused code path elimination
 * Block '<S13>/Display39' : Unused code path elimination
 * Block '<S13>/Display4' : Unused code path elimination
 * Block '<S13>/Display40' : Unused code path elimination
 * Block '<S13>/Display41' : Unused code path elimination
 * Block '<S13>/Display42' : Unused code path elimination
 * Block '<S13>/Display43' : Unused code path elimination
 * Block '<S13>/Display44' : Unused code path elimination
 * Block '<S13>/Display45' : Unused code path elimination
 * Block '<S13>/Display46' : Unused code path elimination
 * Block '<S13>/Display47' : Unused code path elimination
 * Block '<S13>/Display48' : Unused code path elimination
 * Block '<S13>/Display49' : Unused code path elimination
 * Block '<S13>/Display5' : Unused code path elimination
 * Block '<S13>/Display6' : Unused code path elimination
 * Block '<S13>/Display7' : Unused code path elimination
 * Block '<S13>/Display8' : Unused code path elimination
 * Block '<S13>/Display9' : Unused code path elimination
 * Block '<S15>/Constant8' : Unused code path elimination
 * Block '<S50>/Data Type Duplicate' : Unused code path elimination
 * Block '<S50>/Data Type Propagation' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S16>/Scope1' : Unused code path elimination
 * Block '<S17>/Constant2' : Unused code path elimination
 * Block '<S53>/Data Type Duplicate' : Unused code path elimination
 * Block '<S53>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Constant' : Unused code path elimination
 * Block '<S18>/Constant1' : Unused code path elimination
 * Block '<S18>/Constant2' : Unused code path elimination
 * Block '<S18>/Constant3' : Unused code path elimination
 * Block '<S18>/Constant4' : Unused code path elimination
 * Block '<S18>/Constant6' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Propagation' : Unused code path elimination
 * Block '<S54>/Scope' : Unused code path elimination
 * Block '<S54>/Scope1' : Unused code path elimination
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S55>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Scope' : Unused code path elimination
 * Block '<S56>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S57>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S1>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S24>/Shift Arithmetic1' : Eliminated trivial shift
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
 * '<S6>'   : 'Senorless/FOC_PointModel/Observers'
 * '<S7>'   : 'Senorless/FOC_PointModel/Park'
 * '<S8>'   : 'Senorless/FOC_PointModel/SVPWM'
 * '<S9>'   : 'Senorless/FOC_PointModel/idq_Controller'
 * '<S10>'  : 'Senorless/FOC_PointModel/sincos_512'
 * '<S11>'  : 'Senorless/FOC_PointModel/停止等待'
 * '<S12>'  : 'Senorless/FOC_PointModel/切闭环角度差'
 * '<S13>'  : 'Senorless/FOC_PointModel/初始化模块'
 * '<S14>'  : 'Senorless/FOC_PointModel/加速强拖'
 * '<S15>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖'
 * '<S16>'  : 'Senorless/FOC_PointModel/慢速开环'
 * '<S17>'  : 'Senorless/FOC_PointModel/电压限转速'
 * '<S18>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环'
 * '<S19>'  : 'Senorless/FOC_PointModel/预定位'
 * '<S20>'  : 'Senorless/FOC_PointModel/Err/PLL_LPF1'
 * '<S21>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断'
 * '<S22>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/SUM'
 * '<S23>'  : 'Senorless/FOC_PointModel/Err/闭环错误判断/SUM1'
 * '<S24>'  : 'Senorless/FOC_PointModel/Observers/PLL'
 * '<S25>'  : 'Senorless/FOC_PointModel/Observers/SMO'
 * '<S26>'  : 'Senorless/FOC_PointModel/Observers/PLL/LPF'
 * '<S27>'  : 'Senorless/FOC_PointModel/Observers/PLL/PI Controller'
 * '<S28>'  : 'Senorless/FOC_PointModel/Observers/PLL/sincos_512'
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
 * '<S41>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/Saturation Dynamic2'
 * '<S42>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器'
 * '<S43>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller/积分器/Saturation Dynamic2'
 * '<S44>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/Saturation Dynamic2'
 * '<S45>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器'
 * '<S46>'  : 'Senorless/FOC_PointModel/idq_Controller/PI Controller1/积分器/Saturation Dynamic2'
 * '<S47>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度'
 * '<S48>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度/积分器3'
 * '<S49>'  : 'Senorless/FOC_PointModel/加速强拖/加速积分角度/积分器4'
 * '<S50>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/Saturation Dynamic2'
 * '<S51>'  : 'Senorless/FOC_PointModel/恒速降力矩强拖/积分器'
 * '<S52>'  : 'Senorless/FOC_PointModel/慢速开环/积分器'
 * '<S53>'  : 'Senorless/FOC_PointModel/电压限转速/Saturation Dynamic2'
 * '<S54>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller'
 * '<S55>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Saturation Dynamic2'
 * '<S56>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero'
 * '<S57>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/Wrap To Zero1'
 * '<S58>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/速度缓冲'
 * '<S59>'  : 'Senorless/FOC_PointModel/观测器闭环//速度环/PI Controller/Saturation Dynamic2'
 * '<S60>'  : 'Senorless/FOC_PointModel/预定位/Saturation Dynamic2'
 */
#endif                                 /* RTW_HEADER_FOC_PointModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
