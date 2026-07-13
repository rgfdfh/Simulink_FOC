/*
 * File: FOC_PointModel.c
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

#include "FOC_PointModel.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "zero_crossing_types.h"

/* Named constants for Chart: '<S1>/Chart' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_OpenStage                   ((uint8_T)3U)
#define IN_RunStage                    ((uint8_T)4U)
#define IN_SpeedupStage                ((uint8_T)5U)
#define IN_StopStage                   ((uint8_T)6U)
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Exported block parameters */
int16_T Udc = 48;                      /* Variable: Udc
                                        * Referenced by:
                                        *   '<S14>/Constant'
                                        *   '<S14>/Constant16'
                                        * 仿真使用的假设输入母线电压，实际由ADC采样获取。注意，在实际使用时应当在初始化部分重新读一次母线电压，用作初始化变量，不然默认使用字典值，单位：V
                                        */

/* Block signals and states (default storage) */
DW rtDW;

/* Previous zero-crossings (trigger) states */
PrevZCX rtPrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void AntiPark(int16_T rtu_Ud, int16_T rtu_Uq, int32_T rtu_Theta_Sin,
                     int32_T rtu_Theta_Cos, int16_T *rty_ualpha, int16_T
                     *rty_ubeta);
static void MATLABFunction(int32_T rtu_in, int16_T rtu_n, int32_T *rty_out);
static void MATLABFunction_j(int32_T rtu_in, int32_T rtu_up, int32_T rtu_low,
  int32_T *rty_out);
static int32_T PLL_LPF1(int32_T rtu_input, DW_PLL_LPF1 *localDW);
static int32_T SMO_LPF1(int32_T rtu_input, const int16_T *rtd_LPF_FRQ_Point,
  DW_SMO_LPF1 *localDW);
static void u_Init(ZCE_u *localZCE);
static void u_Reset(DW_u *localDW, ZCE_u *localZCE);
static int32_T u(int16_T rtu_Ki, int32_T rtu_input, int32_T rtu_Xo, uint8_T
                 rtu_Reset, const int16_T *rtd_Ts_Point, DW_u *localDW, ZCE_u
                 *localZCE);
static void MATLABFunction1(int16_T rtu_in, int16_T rtu_up, int16_T rtu_low,
  int16_T *rty_out);
static void SVPWM(int16_T rtu_Ualpha, int16_T rtu_Ubeta, uint16_T rty_tABC[3],
                  const int16_T *rtd_PWM_TH);

/* Output and update for atomic system: '<S1>/AntiPark' */
static void AntiPark(int16_T rtu_Ud, int16_T rtu_Uq, int32_T rtu_Theta_Sin,
                     int32_T rtu_Theta_Cos, int16_T *rty_ualpha, int16_T
                     *rty_ubeta)
{
  /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Add'
   */
  *rty_ualpha = (int16_T)((rtu_Ud * rtu_Theta_Cos - rtu_Uq * rtu_Theta_Sin) >>
    15);

  /* DataTypeConversion: '<S2>/Data Type Conversion1' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S2>/Add1'
   */
  *rty_ubeta = (int16_T)((rtu_Ud * rtu_Theta_Sin + rtu_Uq * rtu_Theta_Cos) >> 15);
}

/*
 * Output and update for atomic system:
 *    '<S1>/MATLAB Function'
 *    '<S1>/MATLAB Function1'
 *    '<S1>/MATLAB Function2'
 *    '<S28>/MATLAB Function2'
 *    '<S26>/MATLAB Function2'
 *    '<S59>/MATLAB Function'
 *    '<S60>/MATLAB Function'
 *    '<S67>/MATLAB Function'
 *    '<S44>/MATLAB Function2'
 *    '<S50>/MATLAB Function2'
 */
static void MATLABFunction(int32_T rtu_in, int16_T rtu_n, int32_T *rty_out)
{
  int32_T tmp;
  tmp = -rtu_n;
  if (-rtu_n > 32767) {
    tmp = 32767;
  }

  if ((int16_T)tmp >= 0) {
    if ((int16_T)tmp <= 31) {
      *rty_out = rtu_in << (int16_T)tmp;
    } else {
      *rty_out = 0;
    }
  } else if ((int16_T)tmp >= -31) {
    *rty_out = rtu_in >> -(int16_T)tmp;
  } else if (rtu_in < 0) {
    *rty_out = -1;
  } else {
    *rty_out = 0;
  }
}

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function'
 *    '<S28>/MATLAB Function'
 *    '<S28>/MATLAB Function1'
 *    '<S41>/MATLAB Function'
 *    '<S44>/MATLAB Function'
 *    '<S44>/MATLAB Function1'
 *    '<S42>/MATLAB Function'
 *    '<S50>/MATLAB Function'
 *    '<S50>/MATLAB Function1'
 */
static void MATLABFunction_j(int32_T rtu_in, int32_T rtu_up, int32_T rtu_low,
  int32_T *rty_out)
{
  int32_T in;
  in = rtu_in;
  if (rtu_in >= rtu_up) {
    in = rtu_up;
  }

  if (in <= rtu_low) {
    in = rtu_low;
  }

  *rty_out = in;
}

/*
 * Output and update for atomic system:
 *    '<S19>/PLL_LPF1'
 *    '<S19>/PLL_LPF2'
 */
static int32_T PLL_LPF1(int32_T rtu_input, DW_PLL_LPF1 *localDW)
{
  int32_T rty_output_0;

  /* ArithShift: '<S22>/Shift Arithmetic9' incorporates:
   *  Constant: '<S22>/Constant1'
   *  Product: '<S22>/Product10'
   *  Product: '<S22>/Product11'
   *  Sum: '<S22>/Sum10'
   *  Sum: '<S22>/Sum11'
   *  UnitDelay: '<S22>/Unit Delay9'
   */
  rty_output_0 = ((int16_T)(16 - ((int16_T)PLL_LPF_LEVEL)) * rtu_input +
                  localDW->UnitDelay9_DSTATE * ((int16_T)PLL_LPF_LEVEL)) >> 4;

  /* Update for UnitDelay: '<S22>/Unit Delay9' */
  localDW->UnitDelay9_DSTATE = rty_output_0;
  return rty_output_0;
}

/*
 * Output and update for atomic system:
 *    '<S20>/SMO_LPF1'
 *    '<S20>/SMO_LPF2'
 */
static int32_T SMO_LPF1(int32_T rtu_input, const int16_T *rtd_LPF_FRQ_Point,
  DW_SMO_LPF1 *localDW)
{
  int32_T rty_output_0;

  /* ArithShift: '<S35>/Shift Arithmetic9' incorporates:
   *  DataStoreRead: '<S35>/Data Store Read7'
   *  Product: '<S35>/Product10'
   *  Product: '<S35>/Product11'
   *  Sum: '<S35>/Sum10'
   *  Sum: '<S35>/Sum11'
   *  UnitDelay: '<S35>/Unit Delay9'
   */
  rty_output_0 = ((int16_T)(16 - *rtd_LPF_FRQ_Point) *
                  localDW->UnitDelay9_DSTATE + rtu_input * *rtd_LPF_FRQ_Point) >>
    4;

  /* Update for UnitDelay: '<S35>/Unit Delay9' */
  localDW->UnitDelay9_DSTATE = rty_output_0;
  return rty_output_0;
}

/*
 * System initialize for atomic system:
 *    '<S58>/积分器//上升沿初始化'
 *    '<S58>/积分器//上升沿初始化1'
 */
static void u_Init(ZCE_u *localZCE)
{
  /* SystemInitialize for Triggered SubSystem: '<S59>/Reset_Block' */
  localZCE->Reset_Block_Trig_ZCE_ju = ZERO_ZCSIG;

  /* End of SystemInitialize for SubSystem: '<S59>/Reset_Block' */
}

/*
 * System reset for atomic system:
 *    '<S58>/积分器//上升沿初始化'
 *    '<S58>/积分器//上升沿初始化1'
 */
static void u_Reset(DW_u *localDW, ZCE_u *localZCE)
{
  /* InitializeConditions for UnitDelay: '<S59>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0;

  /* SystemReset for Triggered SubSystem: '<S59>/Reset_Block' */
  localZCE->Reset_Block_Trig_ZCE_ju = ZERO_ZCSIG;

  /* End of SystemReset for SubSystem: '<S59>/Reset_Block' */
}

/*
 * Output and update for atomic system:
 *    '<S58>/积分器//上升沿初始化'
 *    '<S58>/积分器//上升沿初始化1'
 */
static int32_T u(int16_T rtu_Ki, int32_T rtu_input, int32_T rtu_Xo, uint8_T
                 rtu_Reset, const int16_T *rtd_Ts_Point, DW_u *localDW, ZCE_u
                 *localZCE)
{
  int32_T rty_output_0;
  int32_T rtb_Product1_c;

  /* UnitDelay: '<S59>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S59>/Data Store Write'
   */
  localDW->tmp = localDW->UnitDelay_DSTATE;

  /* MATLAB Function: '<S59>/MATLAB Function' incorporates:
   *  Constant: '<S59>/周期定点化适当放大2^n'
   */
  MATLABFunction(rtu_input, ((int16_T)TS_POINT_GAIN), &rtb_Product1_c);

  /* Product: '<S59>/Product1' incorporates:
   *  ArithShift: '<S59>/这个是缩小周期增益的'
   *  DataStoreRead: '<S59>/Data Store Read1'
   *  Product: '<S59>/Product2'
   */
  rtb_Product1_c = ((*rtd_Ts_Point * rtb_Product1_c) >> 15) * rtu_Ki;

  /* Outputs for Triggered SubSystem: '<S59>/Reset_Block' incorporates:
   *  TriggerPort: '<S62>/Trigger'
   */
  if ((rtu_Reset > 0) && (localZCE->Reset_Block_Trig_ZCE_ju != POS_ZCSIG)) {
    /* DataStoreWrite: '<S62>/Data Store Write1' incorporates:
     *  Sum: '<S59>/Sum1'
     */
    localDW->tmp = rtu_Xo - rtb_Product1_c;
  }

  localZCE->Reset_Block_Trig_ZCE_ju = (ZCSigState)(rtu_Reset > 0);

  /* End of Outputs for SubSystem: '<S59>/Reset_Block' */

  /* Sum: '<S59>/Sum' incorporates:
   *  DataStoreRead: '<S59>/Data Store Read'
   */
  rty_output_0 = rtb_Product1_c + localDW->tmp;

  /* Update for UnitDelay: '<S59>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rty_output_0;
  return rty_output_0;
}

/*
 * Output and update for atomic system:
 *    '<S16>/MATLAB Function1'
 *    '<S12>/MATLAB Function1'
 *    '<S12>/MATLAB Function2'
 */
static void MATLABFunction1(int16_T rtu_in, int16_T rtu_up, int16_T rtu_low,
  int16_T *rty_out)
{
  int16_T in;
  in = rtu_in;
  if (rtu_in >= rtu_up) {
    in = rtu_up;
  }

  if (in <= rtu_low) {
    in = rtu_low;
  }

  *rty_out = in;
}

/* Output and update for atomic system: '<S1>/SVPWM' */
static void SVPWM(int16_T rtu_Ualpha, int16_T rtu_Ubeta, uint16_T rty_tABC[3],
                  const int16_T *rtd_PWM_TH)
{
  int32_T tmp;
  int16_T rtb_Gain_gq;
  int16_T rtb_ShiftArithmetic_j;
  int16_T rtb_Sum_f;
  int16_T rtb_Sum_mf;
  int16_T y;

  /* DataTypeConversion: '<S37>/Data Type Conversion' incorporates:
   *  ArithShift: '<S37>/Shift Arithmetic'
   *  Gain: '<S37>/Gain1'
   */
  rtb_Gain_gq = (int16_T)((28378 * rtu_Ubeta) >> 15);

  /* Gain: '<S37>/Gain' */
  rtb_Sum_mf = (int16_T)(-rtu_Ualpha >> 1);

  /* Sum: '<S37>/Sum' */
  rtb_Sum_f = (int16_T)(rtb_Sum_mf + rtb_Gain_gq);

  /* Sum: '<S37>/Sum1' */
  rtb_Sum_mf -= rtb_Gain_gq;

  /* ArithShift: '<S10>/Shift Arithmetic' incorporates:
   *  DataStoreRead: '<S10>/Data Store Read3'
   */
  rtb_ShiftArithmetic_j = (int16_T)(*rtd_PWM_TH >> 1);

  /* MinMax: '<S38>/Min' */
  if (rtu_Ualpha <= rtb_Sum_f) {
    rtb_Gain_gq = rtu_Ualpha;
  } else {
    rtb_Gain_gq = rtb_Sum_f;
  }

  /* MinMax: '<S38>/Min1' */
  if (rtu_Ualpha >= rtb_Sum_f) {
    y = rtu_Ualpha;
  } else {
    y = rtb_Sum_f;
  }

  /* MinMax: '<S38>/Min' */
  if (rtb_Gain_gq > rtb_Sum_mf) {
    rtb_Gain_gq = rtb_Sum_mf;
  }

  /* MinMax: '<S38>/Min1' */
  if (y < rtb_Sum_mf) {
    y = rtb_Sum_mf;
  }

  /* Gain: '<S38>/Gain' incorporates:
   *  MinMax: '<S38>/Min'
   *  MinMax: '<S38>/Min1'
   *  Sum: '<S38>/Sum'
   */
  tmp = -(int16_T)(rtb_Gain_gq + y);
  rtb_Gain_gq = (int16_T)(((tmp < 0) + tmp) >> 1);

  /* Sum: '<S10>/Sum' incorporates:
   *  SignalConversion generated from: '<S10>/Sum'
   */
  y = (int16_T)(rtu_Ualpha + rtb_Gain_gq);

  /* Saturate: '<S10>/Saturation' */
  if (y > 16384) {
    y = 16384;
  } else if (y < -16384) {
    y = -16384;
  }

  /* DataTypeConversion: '<S10>/Data Type Conversion' incorporates:
   *  ArithShift: '<S10>/默认除以32768'
   *  DataStoreRead: '<S10>/Data Store Read2'
   *  Product: '<S10>/Product'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/Sum1'
   */
  rty_tABC[0] = (uint16_T)(rtb_ShiftArithmetic_j - ((y * *rtd_PWM_TH) >> 15));

  /* Sum: '<S10>/Sum' incorporates:
   *  SignalConversion generated from: '<S10>/Sum'
   */
  y = (int16_T)(rtb_Sum_f + rtb_Gain_gq);

  /* Saturate: '<S10>/Saturation' */
  if (y > 16384) {
    y = 16384;
  } else if (y < -16384) {
    y = -16384;
  }

  /* DataTypeConversion: '<S10>/Data Type Conversion' incorporates:
   *  ArithShift: '<S10>/默认除以32768'
   *  DataStoreRead: '<S10>/Data Store Read2'
   *  Product: '<S10>/Product'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/Sum1'
   */
  rty_tABC[1] = (uint16_T)(rtb_ShiftArithmetic_j - ((y * *rtd_PWM_TH) >> 15));

  /* Sum: '<S10>/Sum' incorporates:
   *  SignalConversion generated from: '<S10>/Sum'
   */
  y = (int16_T)(rtb_Sum_mf + rtb_Gain_gq);

  /* Saturate: '<S10>/Saturation' */
  if (y > 16384) {
    y = 16384;
  } else if (y < -16384) {
    y = -16384;
  }

  /* DataTypeConversion: '<S10>/Data Type Conversion' incorporates:
   *  ArithShift: '<S10>/默认除以32768'
   *  DataStoreRead: '<S10>/Data Store Read2'
   *  Product: '<S10>/Product'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/Sum1'
   */
  rty_tABC[2] = (uint16_T)(rtb_ShiftArithmetic_j - ((y * *rtd_PWM_TH) >> 15));
}

/* Model step function */
void FOC_PointModel_step(void)
{
  int32_T rtb_Product1_jr;
  int32_T rtb_ShiftArithmetic9_a;
  int32_T rtb_Sum2_pz;
  int32_T rtb_Sum_b;
  int32_T rtb_out_bj;
  int32_T tmp;
  uint32_T tmp_0;
  uint32_T tmp_1;
  int16_T rtb_DataTypeConversion1_hr;
  int16_T rtb_DataTypeConversion1_l;
  int16_T rtb_DataTypeConversion_n;
  int16_T rtb_Sum1_a;
  int16_T rtb_Sum8;
  int16_T rtb_out_n;
  uint16_T b_index;
  int8_T rtAction;
  int8_T rtPrevAction;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_PointModel' */
  /* Chart: '<S1>/Chart' incorporates:
   *  Abs: '<S1>/Abs'
   *  DataTypeConversion: '<S1>/Data Type Conversion3'
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i2 < MAX_uint32_T) {
    rtDW.temporalCounter_i2++;
  }

  if (rtDW.temporalCounter_i1 < MAX_uint32_T) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c2_FOC_PointModel == 0U) {
    rtDW.is_active_c2_FOC_PointModel = 1U;
    rtDW.is_c2_FOC_PointModel = IN_IDLE;
  } else {
    switch (rtDW.is_c2_FOC_PointModel) {
     case IN_AlignStage:
      if (rtDW.temporalCounter_i2 >= 250U) {
        rtDW.is_c2_FOC_PointModel = IN_SpeedupStage;
        rtDW.temporalCounter_i2 = 0U;
      } else if ((uint8_T)rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
      } else {
        rtDW.Motor_state = 2U;
      }
      break;

     case IN_IDLE:
      if ((uint8_T)rtU.Motor_OnOff == 1) {
        rtDW.is_c2_FOC_PointModel = IN_AlignStage;
        rtDW.temporalCounter_i2 = 0U;
        rtDW.Angles_Reset_Signal = 1U;
        rtDW.Curr_Reset_Sinal = 1U;
      } else {
        rtDW.Motor_state = 1U;
        rtDW.Angles_Reset_Signal = 0U;
        rtDW.Curr_Reset_Sinal = 0U;
      }
      break;

     case IN_OpenStage:
      if (rtDW.temporalCounter_i2 >= 12500U) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i2 = 0U;
        rtDW.Angles_Reset_Signal = 0U;
        rtDW.Curr_Reset_Sinal = 0U;
      } else {
        /* Sum: '<S1>/Sum4' incorporates:
         *  UnitDelay: '<S1>/Unit Delay6'
         *  UnitDelay: '<S1>/Unit Delay7'
         */
        rtb_out_n = (int16_T)((int16_T)rtDW.UnitDelay7_DSTATE_p - (int16_T)
                              rtDW.UnitDelay6_DSTATE_a);

        /* Abs: '<S1>/Abs' */
        if (rtb_out_n < 0) {
          rtb_out_n = (int16_T)-rtb_out_n;
        }

        if ((rtDW.temporalCounter_i1 >= 6552U) && (rtb_out_n < ((int16_T)
              THETA_ERR_LIMIT))) {
          rtDW.Angles_Reset_Signal = 1U;
          rtDW.is_c2_FOC_PointModel = IN_RunStage;
        } else if ((uint8_T)rtU.Motor_OnOff == 0) {
          rtDW.Angles_Reset_Signal = 1U;
          rtDW.is_c2_FOC_PointModel = IN_IDLE;
        } else {
          rtDW.Motor_state = 4U;
        }
      }
      break;

     case IN_RunStage:
      if ((uint8_T)rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
      } else {
        rtDW.Motor_state = 5U;
      }
      break;

     case IN_SpeedupStage:
      if ((uint8_T)rtU.Motor_OnOff == 0) {
        rtDW.Angles_Reset_Signal = 0U;
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
      } else if (rtDW.temporalCounter_i2 >= (uint32_T)ceil(OPEN_TIME / 4.0E-5 -
                  4.0000000000000006E-13)) {
        rtDW.is_c2_FOC_PointModel = IN_OpenStage;
        rtDW.temporalCounter_i2 = 0U;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.Angles_Reset_Signal = 0U;
      } else {
        rtDW.Motor_state = 3U;
      }
      break;

     default:
      /* case IN_StopStage: */
      if (rtDW.temporalCounter_i2 >= 12500U) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
      } else {
        rtDW.Motor_state = 1U;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  ArithShift: '<S58>/Shift Arithmetic'
   *  Constant: '<S58>/初始值'
   *  Constant: '<S58>/初始值2'
   *  Constant: '<S58>/积分增益2'
   *  Constant: '<S58>/积分增益3'
   *  Sum: '<S60>/Sum'
   */
  rtPrevAction = rtDW.SwitchCase_ActiveSubsystem;
  rtAction = -1;
  switch (rtDW.Motor_state) {
   case 1:
    rtAction = 0;
    break;

   case 2:
    rtAction = 1;
    break;

   case 3:
    rtAction = 2;
    break;

   case 4:
    rtAction = 3;
    break;

   case 5:
    rtAction = 4;
    break;
  }

  rtDW.SwitchCase_ActiveSubsystem = rtAction;
  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S1>/停止等待' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S13>/Constant2'
     *  SignalConversion generated from: '<S13>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S13>/Constant1'
     *  SignalConversion generated from: '<S13>/Id'
     */
    rtDW.Merge2 = 0;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S13>/Constant1'
     *  SignalConversion generated from: '<S13>/Iq'
     */
    rtDW.Merge1 = 0;

    /* End of Outputs for SubSystem: '<S1>/停止等待' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/预定位' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S18>/Constant3'
     *  SignalConversion generated from: '<S18>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S18>/Constant1'
     *  SignalConversion generated from: '<S18>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S18>/Constant2'
     *  SignalConversion generated from: '<S18>/Id'
     */
    rtDW.Merge2 = 6552;

    /* End of Outputs for SubSystem: '<S1>/预定位' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* SystemReset for IfAction SubSystem: '<S1>/加速强拖' incorporates:
       *  ActionPort: '<S15>/Action Port'
       */
      /* SystemReset for Atomic SubSystem: '<S58>/积分器//上升沿初始化' */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' */
      u_Reset(&rtDW.u_k, &rtPrevZCX.u_k);

      /* End of SystemReset for SubSystem: '<S58>/积分器//上升沿初始化' */

      /* SystemReset for Atomic SubSystem: '<S58>/积分器//上升沿初始化1' */
      u_Reset(&rtDW.u_ae, &rtPrevZCX.u_ae);

      /* End of SystemReset for SubSystem: '<S58>/积分器//上升沿初始化1' */
      /* End of SystemReset for SubSystem: '<S1>/加速强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/加速强拖' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* DataTypeConversion: '<S58>/Data Type Conversion3' incorporates:
     *  DataStoreRead: '<S1>/Data Store Read1'
     */
    rtb_Sum_b = rtDW.Open_Acceleration;

    /* Outputs for Atomic SubSystem: '<S58>/积分器//上升沿初始化' */
    rtb_Sum_b = u(1, rtb_Sum_b << 16, 0, rtDW.Angles_Reset_Signal,
                  &rtDW.Ts_Point, &rtDW.u_k, &rtPrevZCX.u_k);

    /* End of Outputs for SubSystem: '<S58>/积分器//上升沿初始化' */

    /* Outputs for Atomic SubSystem: '<S58>/积分器//上升沿初始化1' */
    rtb_Sum_b = u(1, rtb_Sum_b, 0, rtDW.Angles_Reset_Signal, &rtDW.Ts_Point,
                  &rtDW.u_ae, &rtPrevZCX.u_ae);

    /* End of Outputs for SubSystem: '<S58>/积分器//上升沿初始化1' */

    /* Merge: '<S1>/Merge' incorporates:
     *  ArithShift: '<S58>/Shift Arithmetic'
     *  Constant: '<S58>/初始值'
     *  Constant: '<S58>/初始值2'
     *  Constant: '<S58>/积分增益2'
     *  Constant: '<S58>/积分增益3'
     *  DataTypeConversion: '<S58>/Data Type Conversion2'
     *  SignalConversion generated from: '<S15>/Theta'
     *  Sum: '<S60>/Sum'
     */
    rtDW.Merge = (uint16_T)rtb_Sum_b;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S15>/Constant'
     *  SignalConversion generated from: '<S15>/Iq'
     */
    rtDW.Merge1 = ((int16_T)OPEN_IQ);

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S15>/Constant1'
     *  SignalConversion generated from: '<S15>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/加速强拖' */
    break;

   case 3:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
       *  ActionPort: '<S16>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S16>/Unit Delay1'
       */
      rtDW.UnitDelay1_DSTATE = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/恒速降力矩强拖' */

      /* SystemReset for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
       *  ActionPort: '<S16>/Action Port'
       */
      /* SystemReset for Atomic SubSystem: '<S65>/积分器//下降沿初始化' */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S67>/Unit Delay'
       */
      rtDW.UnitDelay_DSTATE_j = 0;

      /* SystemReset for Triggered SubSystem: '<S67>/Reset_Block' */
      rtPrevZCX.Reset_Block_Trig_ZCE_e = POS_ZCSIG;

      /* End of SystemReset for SubSystem: '<S67>/Reset_Block' */
      /* End of SystemReset for SubSystem: '<S65>/积分器//下降沿初始化' */
      /* End of SystemReset for SubSystem: '<S1>/恒速降力矩强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* Outputs for Atomic SubSystem: '<S65>/积分器//下降沿初始化' */
    /* UnitDelay: '<S67>/Unit Delay' incorporates:
     *  DataStoreWrite: '<S67>/Data Store Write'
     */
    rtb_Sum_b = rtDW.UnitDelay_DSTATE_j;

    /* MATLAB Function: '<S67>/MATLAB Function' incorporates:
     *  ArithShift: '<S65>/Shift Arithmetic'
     *  Constant: '<S67>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read'
     *  DataTypeConversion: '<S65>/Data Type Conversion2'
     */
    MATLABFunction(rtDW.Open_Hz << 16, ((int16_T)TS_POINT_GAIN),
                   &rtb_Product1_jr);

    /* Product: '<S67>/Product1' incorporates:
     *  ArithShift: '<S67>/这个是缩小周期增益的'
     *  DataStoreRead: '<S67>/Data Store Read1'
     *  Product: '<S67>/Product2'
     */
    rtb_Product1_jr = (rtDW.Ts_Point * rtb_Product1_jr) >> 15;

    /* Outputs for Triggered SubSystem: '<S67>/Reset_Block' incorporates:
     *  TriggerPort: '<S69>/Trigger'
     */
    if ((rtDW.Angles_Reset_Signal == 0) && (rtPrevZCX.Reset_Block_Trig_ZCE_e !=
         ZERO_ZCSIG)) {
      /* DataStoreWrite: '<S69>/Data Store Write1' incorporates:
       *  Sum: '<S67>/Sum1'
       *  UnitDelay: '<S1>/Unit Delay1'
       */
      rtb_Sum_b = rtDW.UnitDelay1_DSTATE_b - rtb_Product1_jr;
    }

    rtPrevZCX.Reset_Block_Trig_ZCE_e = (ZCSigState)(rtDW.Angles_Reset_Signal > 0);

    /* End of Outputs for SubSystem: '<S67>/Reset_Block' */

    /* Sum: '<S67>/Sum' incorporates:
     *  DataStoreRead: '<S67>/Data Store Read'
     */
    rtb_Sum_b += rtb_Product1_jr;

    /* Update for UnitDelay: '<S67>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_j = rtb_Sum_b;

    /* End of Outputs for SubSystem: '<S65>/积分器//下降沿初始化' */

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S65>/Data Type Conversion'
     *  SignalConversion generated from: '<S16>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_Sum_b;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Gain: '<S16>/Gain'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    rtDW.Merge2 = (int16_T)-rtDW.UnitDelay1_DSTATE;

    /* MATLAB Function: '<S16>/MATLAB Function1' incorporates:
     *  Constant: '<S16>/Constant4'
     *  Constant: '<S16>/Constant5'
     *  Constant: '<S16>/Constant6'
     *  Constant: '<S16>/Constant7'
     *  Sum: '<S16>/Sum'
     *  Sum: '<S16>/Sum2'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    MATLABFunction1((int16_T)(rtDW.UnitDelay1_DSTATE - 1), 0, (int16_T)
                    (((int16_T)OPEN_IQ_MIN) - ((int16_T)OPEN_IQ)), &rtb_out_n);

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S16>/Constant'
     *  Sum: '<S16>/Sum1'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    rtDW.Merge1 = (int16_T)(((int16_T)OPEN_IQ) + rtDW.UnitDelay1_DSTATE);

    /* Update for UnitDelay: '<S16>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE = rtb_out_n;

    /* End of Outputs for SubSystem: '<S1>/恒速降力矩强拖' */
    break;

   case 4:
    /* Outputs for IfAction SubSystem: '<S1>/观测器闭环' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S17>/Obs_Theta'
     *  UnitDelay: '<S1>/Unit Delay4'
     */
    rtDW.Merge = rtDW.UnitDelay4_DSTATE_g;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S17>/Constant2'
     *  SignalConversion generated from: '<S17>/Iq'
     */
    rtDW.Merge1 = MAX_int16_T;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S17>/Constant3'
     *  SignalConversion generated from: '<S17>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/观测器闭环' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* MATLAB Function: '<S12>/MATLAB Function1' incorporates:
   *  Constant: '<S12>/Constant2'
   *  Gain: '<S12>/Gain'
   *  Sum: '<S12>/Sum5'
   *  UnitDelay: '<S12>/Unit Delay4'
   */
  MATLABFunction1((int16_T)(rtDW.Merge2 - rtDW.UnitDelay4_DSTATE_j), ((int16_T)
    CURR_STEP), (int16_T)-((int16_T)CURR_STEP), &rtb_out_n);

  /* Sum: '<S12>/Sum6' incorporates:
   *  UnitDelay: '<S12>/Unit Delay4'
   */
  rtb_out_n += rtDW.UnitDelay4_DSTATE_j;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ia'
   *  Product: '<S1>/Product'
   */
  MATLABFunction(rtU.ia * rtDW.Curr_Conversion, ((int16_T)CURR_POINT_GAIN),
                 &rtb_out_bj);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Gain: '<S1>/Gain4'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ic'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Sum'
   */
  MATLABFunction(-(rtU.ia + rtU.ic) * rtDW.Curr_Conversion, ((int16_T)
    CURR_POINT_GAIN), &rtb_ShiftArithmetic9_a);

  /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ic'
   *  Product: '<S1>/Product2'
   */
  MATLABFunction(rtU.ic * rtDW.Curr_Conversion, ((int16_T)CURR_POINT_GAIN),
                 &rtb_Sum_b);

  /* Outputs for Atomic SubSystem: '<S1>/Clark' */
  /* DataTypeConversion: '<S4>/Data Type Conversion1' */
  rtb_DataTypeConversion1_hr = (int16_T)rtb_out_bj;

  /* ArithShift: '<S4>/Shift Arithmetic' incorporates:
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S4>/Add2'
   */
  rtb_Sum_b = ((rtb_ShiftArithmetic9_a - rtb_Sum_b) * ((int16_T)DIVSQRT3)) >> 15;

  /* DataTypeConversion: '<S4>/Data Type Conversion' */
  rtb_DataTypeConversion_n = (int16_T)rtb_Sum_b;

  /* End of Outputs for SubSystem: '<S1>/Clark' */

  /* MATLAB Function: '<S1>/Sin2_512' */
  b_index = (uint16_T)((uint32_T)rtDW.Merge >> 7);
  tmp_0 = (b_index - (((b_index + 128U) >> 9) << 9)) + 128U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  tmp_1 = tmp_0 + 1U;
  if (tmp_0 + 1U > 65535U) {
    tmp_1 = 65535U;
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion5' incorporates:
   *  MATLAB Function: '<S1>/Sin2_512'
   */
  rtb_Sum_b = rtDW.sin512[(int32_T)tmp_1 - 1];

  /* DataTypeConversion: '<S1>/Data Type Conversion2' incorporates:
   *  MATLAB Function: '<S1>/Sin2_512'
   */
  rtb_Product1_jr = rtDW.sin512[b_index];

  /* Outputs for Atomic SubSystem: '<S1>/Clark' */
  /* Sum: '<S12>/Sum1' incorporates:
   *  ArithShift: '<S9>/Shift Arithmetic'
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Product: '<S9>/Product'
   *  Product: '<S9>/Product1'
   *  Sum: '<S9>/Add'
   */
  tmp = rtb_out_n - (int16_T)(((int16_T)rtb_out_bj * rtb_Sum_b +
    rtb_DataTypeConversion_n * rtb_Product1_jr) >> 15);

  /* End of Outputs for SubSystem: '<S1>/Clark' */
  if (tmp > 32767) {
    tmp = 32767;
  } else if (tmp < -32768) {
    tmp = -32768;
  }

  rtb_Sum1_a = (int16_T)tmp;

  /* Outputs for Atomic SubSystem: '<S12>/PI Controller' */
  /* UnitDelay: '<S44>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S44>/Data Store Write'
   */
  rtb_out_bj = rtDW.UnitDelay_DSTATE_n;

  /* MATLAB Function: '<S44>/MATLAB Function2' incorporates:
   *  Constant: '<S44>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S12>/Data Store Read5'
   */
  MATLABFunction(rtDW.Curr_Ki_Point, ((int16_T)TS_POINT_GAIN),
                 &rtb_ShiftArithmetic9_a);

  /* MATLAB Function: '<S44>/MATLAB Function1' incorporates:
   *  ArithShift: '<S44>/这个是缩小周期增益的'
   *  Constant: '<S44>/Constant'
   *  DataStoreRead: '<S44>/Data Store Read1'
   *  DataStoreRead: '<S44>/Data Store Read3'
   *  DataTypeConversion: '<S44>/Data Type Conversion'
   *  Gain: '<S44>/Gain1'
   *  Product: '<S44>/Product1'
   *  Product: '<S44>/Product2'
   *  Sum: '<S12>/Sum1'
   *  Sum: '<S44>/Sum2'
   */
  MATLABFunction_j((int16_T)rtb_ShiftArithmetic9_a * ((rtDW.Ts_Point * (int16_T)
    tmp) >> 15), 1073741824 - rtDW.Curr_Limit, rtDW.Curr_Limit - 1073741824,
                   &rtb_ShiftArithmetic9_a);

  /* Outputs for Triggered SubSystem: '<S44>/Reset_Block' incorporates:
   *  TriggerPort: '<S48>/Trigger'
   */
  if (((rtDW.Curr_Reset_Sinal > 0) != (rtPrevZCX.Reset_Block_Trig_ZCE_j ==
        POS_ZCSIG)) && (rtPrevZCX.Reset_Block_Trig_ZCE_j != UNINITIALIZED_ZCSIG))
  {
    /* DataStoreWrite: '<S48>/Data Store Write1' incorporates:
     *  Sum: '<S44>/Sum1'
     */
    rtb_out_bj = -rtb_ShiftArithmetic9_a;
  }

  rtPrevZCX.Reset_Block_Trig_ZCE_j = (ZCSigState)(rtDW.Curr_Reset_Sinal > 0);

  /* End of Outputs for SubSystem: '<S44>/Reset_Block' */

  /* MATLAB Function: '<S44>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S44>/Data Store Read'
   *  DataStoreRead: '<S44>/Data Store Read3'
   *  Gain: '<S44>/Gain'
   *  Sum: '<S44>/Sum'
   */
  MATLABFunction_j(rtb_ShiftArithmetic9_a + rtb_out_bj, rtDW.Curr_Limit,
                   -rtDW.Curr_Limit, &rtb_ShiftArithmetic9_a);

  /* MATLAB Function: '<S41>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S12>/Data Store Read2'
   *  DataStoreRead: '<S41>/Data Store Read3'
   *  Gain: '<S41>/Gain'
   *  Product: '<S41>/Product2'
   *  Sum: '<S12>/Sum1'
   *  Sum: '<S41>/Sum'
   */
  MATLABFunction_j((int16_T)tmp * rtDW.Curr_Kp_Point + rtb_ShiftArithmetic9_a,
                   rtDW.Curr_Limit, -rtDW.Curr_Limit, &rtb_out_bj);

  /* Update for UnitDelay: '<S44>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_n = rtb_ShiftArithmetic9_a;

  /* End of Outputs for SubSystem: '<S12>/PI Controller' */

  /* MATLAB Function: '<S12>/MATLAB Function2' incorporates:
   *  Constant: '<S12>/Constant3'
   *  Gain: '<S12>/Gain1'
   *  Sum: '<S12>/Sum9'
   *  UnitDelay: '<S12>/Unit Delay3'
   */
  MATLABFunction1((int16_T)(rtDW.Merge1 - rtDW.UnitDelay3_DSTATE_g), ((int16_T)
    CURR_STEP), (int16_T)-((int16_T)CURR_STEP), &rtb_Sum1_a);

  /* Sum: '<S12>/Sum10' incorporates:
   *  UnitDelay: '<S12>/Unit Delay3'
   */
  rtb_Sum1_a += rtDW.UnitDelay3_DSTATE_g;

  /* ArithShift: '<S9>/Shift Arithmetic1' incorporates:
   *  Product: '<S9>/Product2'
   *  Product: '<S9>/Product3'
   *  Sum: '<S9>/Add1'
   */
  rtb_Sum2_pz = (rtb_DataTypeConversion_n * rtb_Sum_b -
                 rtb_DataTypeConversion1_hr * rtb_Product1_jr) >> 15;

  /* Sum: '<S12>/Sum8' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion1'
   */
  tmp = rtb_Sum1_a - (int16_T)rtb_Sum2_pz;
  if (tmp > 32767) {
    tmp = 32767;
  } else if (tmp < -32768) {
    tmp = -32768;
  }

  rtb_Sum8 = (int16_T)tmp;

  /* Outputs for Atomic SubSystem: '<S12>/PI Controller1' */
  /* UnitDelay: '<S50>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S50>/Data Store Write'
   */
  rtb_ShiftArithmetic9_a = rtDW.UnitDelay_DSTATE;

  /* MATLAB Function: '<S50>/MATLAB Function2' incorporates:
   *  Constant: '<S50>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S12>/Data Store Read7'
   */
  MATLABFunction(rtDW.Curr_Ki_Point, ((int16_T)TS_POINT_GAIN), &rtb_Sum2_pz);

  /* MATLAB Function: '<S50>/MATLAB Function1' incorporates:
   *  ArithShift: '<S50>/这个是缩小周期增益的'
   *  Constant: '<S50>/Constant'
   *  DataStoreRead: '<S50>/Data Store Read1'
   *  DataStoreRead: '<S50>/Data Store Read3'
   *  DataTypeConversion: '<S50>/Data Type Conversion'
   *  Gain: '<S50>/Gain1'
   *  Product: '<S50>/Product1'
   *  Product: '<S50>/Product2'
   *  Sum: '<S12>/Sum8'
   *  Sum: '<S50>/Sum2'
   */
  MATLABFunction_j((int16_T)rtb_Sum2_pz * ((rtDW.Ts_Point * (int16_T)tmp) >> 15),
                   1073741824 - rtDW.Curr_Limit, rtDW.Curr_Limit - 1073741824,
                   &rtb_Sum2_pz);

  /* Outputs for Triggered SubSystem: '<S50>/Reset_Block' incorporates:
   *  TriggerPort: '<S54>/Trigger'
   */
  if (((rtDW.Curr_Reset_Sinal > 0) != (rtPrevZCX.Reset_Block_Trig_ZCE ==
        POS_ZCSIG)) && (rtPrevZCX.Reset_Block_Trig_ZCE != UNINITIALIZED_ZCSIG))
  {
    /* DataStoreWrite: '<S54>/Data Store Write1' incorporates:
     *  Sum: '<S50>/Sum1'
     */
    rtb_ShiftArithmetic9_a = -rtb_Sum2_pz;
  }

  rtPrevZCX.Reset_Block_Trig_ZCE = (ZCSigState)(rtDW.Curr_Reset_Sinal > 0);

  /* End of Outputs for SubSystem: '<S50>/Reset_Block' */

  /* MATLAB Function: '<S50>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S50>/Data Store Read'
   *  DataStoreRead: '<S50>/Data Store Read3'
   *  Gain: '<S50>/Gain'
   *  Sum: '<S50>/Sum'
   */
  MATLABFunction_j(rtb_Sum2_pz + rtb_ShiftArithmetic9_a, rtDW.Curr_Limit,
                   -rtDW.Curr_Limit, &rtb_Sum2_pz);

  /* MATLAB Function: '<S42>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S12>/Data Store Read6'
   *  DataStoreRead: '<S42>/Data Store Read3'
   *  Gain: '<S42>/Gain'
   *  Product: '<S42>/Product2'
   *  Sum: '<S12>/Sum8'
   *  Sum: '<S42>/Sum'
   */
  MATLABFunction_j((int16_T)tmp * rtDW.Curr_Kp_Point + rtb_Sum2_pz,
                   rtDW.Curr_Limit, -rtDW.Curr_Limit, &rtb_ShiftArithmetic9_a);

  /* Update for UnitDelay: '<S50>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Sum2_pz;

  /* End of Outputs for SubSystem: '<S12>/PI Controller1' */

  /* Outputs for Atomic SubSystem: '<S1>/AntiPark' */
  /* DataTypeConversion: '<S12>/Data Type Conversion4' incorporates:
   *  ArithShift: '<S12>/Shift Arithmetic2'
   *  ArithShift: '<S12>/Shift Arithmetic3'
   *  ArithShift: '<S19>/Shift Arithmetic10'
   *  DataTypeConversion: '<S12>/Data Type Conversion5'
   *  UnitDelay: '<S19>/Unit Delay2'
   */
  AntiPark((int16_T)(rtb_out_bj >> 15), (int16_T)(rtb_ShiftArithmetic9_a >> 15),
           rtb_Product1_jr, rtb_Sum_b, &rtb_Sum8, &rtb_DataTypeConversion1_l);

  /* End of Outputs for SubSystem: '<S1>/AntiPark' */

  /* Outputs for Atomic SubSystem: '<S8>/SMO' */
  /* Switch: '<S20>/清零选择1' incorporates:
   *  ArithShift: '<S20>/Shift Arithmetic3'
   *  ArithShift: '<S20>/Shift Arithmetic4'
   *  ArithShift: '<S20>/Shift Arithmetic5'
   *  ArithShift: '<S20>/Shift Arithmetic6'
   *  Constant: '<S20>/Constant'
   *  Constant: '<S20>/Constant2'
   *  DataStoreRead: '<S20>/Data Store Read11'
   *  DataStoreRead: '<S20>/Data Store Read13'
   *  DataStoreRead: '<S20>/Data Store Read15'
   *  DataStoreRead: '<S20>/Data Store Read16'
   *  DataStoreRead: '<S20>/Data Store Read7'
   *  DataStoreRead: '<S20>/Data Store Read8'
   *  Product: '<S20>/Product10'
   *  Product: '<S20>/Product11'
   *  Product: '<S20>/Product12'
   *  Product: '<S20>/Product5'
   *  Product: '<S20>/Product6'
   *  Product: '<S20>/Product8'
   *  Sum: '<S20>/Sum2'
   *  Sum: '<S20>/Sum3'
   *  Sum: '<S20>/Sum4'
   *  Sum: '<S20>/Sum7'
   *  Switch: '<S20>/清零选择4'
   *  UnitDelay: '<S20>/Unit Delay2'
   *  UnitDelay: '<S20>/Unit Delay3'
   *  UnitDelay: '<S20>/Unit Delay4'
   *  UnitDelay: '<S20>/Unit Delay6'
   */
  if (rtDW.Curr_Reset_Sinal != 0) {
    rtb_Product1_jr = (((rtb_DataTypeConversion1_l * rtDW.Obs_VtoI -
                         rtDW.UnitDelay2_DSTATE) * rtDW.SMO_Gain2) >> 8) +
      ((rtDW.UnitDelay3_DSTATE * rtDW.SMO_Gain1) >> 8);
    rtb_out_bj = (((rtb_Sum8 * rtDW.Obs_VtoI - rtDW.UnitDelay4_DSTATE) *
                   rtDW.SMO_Gain2) >> 8) + ((rtDW.UnitDelay6_DSTATE *
      rtDW.SMO_Gain1) >> 8);
  } else {
    rtb_Product1_jr = 0;
    rtb_out_bj = 0;
  }

  /* End of Switch: '<S20>/清零选择1' */

  /* Outputs for Atomic SubSystem: '<S20>/SMO_LPF1' */
  /* Product: '<S20>/Product9' incorporates:
   *  DataStoreRead: '<S20>/Data Store Read14'
   *  Sum: '<S20>/Sum5'
   */
  rtb_Sum_b = SMO_LPF1((rtb_out_bj - rtb_DataTypeConversion1_hr) * rtDW.SMO_K,
                       &rtDW.LPF_FRQ_Point, &rtDW.SMO_LPF1_f);

  /* End of Outputs for SubSystem: '<S20>/SMO_LPF1' */

  /* Outputs for Atomic SubSystem: '<S20>/SMO_LPF2' */
  /* Product: '<S20>/Product13' incorporates:
   *  DataStoreRead: '<S20>/Data Store Read12'
   *  Sum: '<S20>/Sum8'
   */
  rtb_ShiftArithmetic9_a = SMO_LPF1((rtb_Product1_jr - rtb_DataTypeConversion_n)
    * rtDW.SMO_K, &rtDW.LPF_FRQ_Point, &rtDW.SMO_LPF2);

  /* End of Outputs for SubSystem: '<S20>/SMO_LPF2' */

  /* Update for UnitDelay: '<S20>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE = rtb_ShiftArithmetic9_a;

  /* Update for UnitDelay: '<S20>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE = rtb_Product1_jr;

  /* Update for UnitDelay: '<S20>/Unit Delay4' */
  rtDW.UnitDelay4_DSTATE = rtb_Sum_b;

  /* Update for UnitDelay: '<S20>/Unit Delay6' */
  rtDW.UnitDelay6_DSTATE = rtb_out_bj;

  /* End of Outputs for SubSystem: '<S8>/SMO' */

  /* Outputs for Atomic SubSystem: '<S8>/PLL' */
  /* UnitDelay: '<S26>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S26>/Data Store Write'
   */
  rtb_Product1_jr = rtDW.UnitDelay_DSTATE_l;

  /* MATLAB Function: '<S19>/Sin2_1' incorporates:
   *  DataTypeConversion: '<S19>/Data Type Conversion7'
   *  UnitDelay: '<S19>/Unit Delay7'
   */
  b_index = (uint16_T)((uint32_T)(uint16_T)rtDW.UnitDelay7_DSTATE >> 7);
  tmp_0 = (b_index - (((b_index + 128U) >> 9) << 9)) + 128U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  tmp_1 = tmp_0 + 1U;
  if (tmp_0 + 1U > 65535U) {
    tmp_1 = 65535U;
  }

  /* DataTypeConversion: '<S19>/Data Type Conversion9' incorporates:
   *  ArithShift: '<S19>/Shift Arithmetic7'
   *  ArithShift: '<S19>/Shift Arithmetic8'
   *  MATLAB Function: '<S19>/Sin2_1'
   *  Product: '<S19>/Product3'
   *  Product: '<S19>/Product4'
   *  Sum: '<S19>/Sum4'
   */
  rtb_DataTypeConversion1_hr = (int16_T)(-((rtDW.sin512_h[(int32_T)tmp_1 - 1] *
    rtb_Sum_b) >> 15) - ((rtDW.sin512_h[b_index] * rtb_ShiftArithmetic9_a) >> 15));

  /* Outputs for Atomic SubSystem: '<S19>/PI Controller' */
  /* UnitDelay: '<S28>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S28>/Data Store Write'
   */
  rtb_ShiftArithmetic9_a = rtDW.UnitDelay_DSTATE_f;

  /* MATLAB Function: '<S28>/MATLAB Function2' incorporates:
   *  Constant: '<S28>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S19>/Data Store Read8'
   */
  MATLABFunction(rtDW.PLL_Ki, ((int16_T)TS_POINT_GAIN), &rtb_Sum_b);

  /* Sum: '<S28>/Sum2' incorporates:
   *  Constant: '<S28>/Constant'
   *  DataStoreRead: '<S28>/Data Store Read3'
   */
  rtb_out_bj = 1073741824 - rtDW.PLL_Limit;

  /* MATLAB Function: '<S28>/MATLAB Function1' incorporates:
   *  ArithShift: '<S28>/这个是缩小周期增益的'
   *  Constant: '<S28>/Constant'
   *  DataStoreRead: '<S28>/Data Store Read1'
   *  DataStoreRead: '<S28>/Data Store Read3'
   *  DataTypeConversion: '<S28>/Data Type Conversion'
   *  Gain: '<S28>/Gain1'
   *  Product: '<S28>/Product1'
   *  Product: '<S28>/Product2'
   *  Sum: '<S28>/Sum2'
   */
  MATLABFunction_j((int16_T)rtb_Sum_b * ((rtDW.Ts_Point
    * rtb_DataTypeConversion1_hr) >> 15), 1073741824 - rtDW.PLL_Limit,
                   rtDW.PLL_Limit - 1073741824, &rtb_Sum_b);

  /* Outputs for Triggered SubSystem: '<S28>/Reset_Block' incorporates:
   *  TriggerPort: '<S32>/Trigger'
   */
  if ((rtDW.Curr_Reset_Sinal > 0) && (rtPrevZCX.Reset_Block_Trig_ZCE_m !=
       POS_ZCSIG)) {
    /* DataStoreWrite: '<S32>/Data Store Write1' incorporates:
     *  Sum: '<S28>/Sum1'
     */
    rtb_ShiftArithmetic9_a = -rtb_Sum_b;
  }

  rtPrevZCX.Reset_Block_Trig_ZCE_m = (ZCSigState)(rtDW.Curr_Reset_Sinal > 0);

  /* End of Outputs for SubSystem: '<S28>/Reset_Block' */

  /* MATLAB Function: '<S28>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S28>/Data Store Read'
   *  DataStoreRead: '<S28>/Data Store Read3'
   *  Gain: '<S28>/Gain'
   *  Sum: '<S28>/Sum'
   */
  MATLABFunction_j(rtb_Sum_b + rtb_ShiftArithmetic9_a, rtDW.PLL_Limit,
                   -rtDW.PLL_Limit, &rtb_Sum_b);

  /* MATLAB Function: '<S21>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S19>/Data Store Read7'
   *  DataStoreRead: '<S21>/Data Store Read3'
   *  Gain: '<S21>/Gain'
   *  Product: '<S21>/Product2'
   *  Sum: '<S21>/Sum'
   */
  MATLABFunction_j(rtb_DataTypeConversion1_hr * rtDW.PLL_Kp + rtb_Sum_b,
                   rtDW.PLL_Limit, -rtDW.PLL_Limit, &rtb_ShiftArithmetic9_a);

  /* Update for UnitDelay: '<S28>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_f = rtb_Sum_b;

  /* End of Outputs for SubSystem: '<S19>/PI Controller' */

  /* MATLAB Function: '<S26>/MATLAB Function2' incorporates:
   *  ArithShift: '<S23>/Shift Arithmetic9'
   *  ArithShift: '<S26>/这个是缩小周期增益的'
   *  Constant: '<S26>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S26>/Data Store Read1'
   *  Product: '<S26>/Product2'
   */
  MATLABFunction(rtDW.Ts_Point * (rtb_ShiftArithmetic9_a >> 15), ((int16_T)
    TS_POINT_GAIN), &rtb_out_bj);

  /* Outputs for Triggered SubSystem: '<S26>/Reset_Block' incorporates:
   *  TriggerPort: '<S34>/Trigger'
   */
  if ((rtDW.Curr_Reset_Sinal > 0) && (rtPrevZCX.Reset_Block_Trig_ZCE_h !=
       POS_ZCSIG)) {
    /* DataStoreWrite: '<S34>/Data Store Write1' incorporates:
     *  Sum: '<S26>/Sum1'
     */
    rtb_Product1_jr = -rtb_out_bj;
  }

  rtPrevZCX.Reset_Block_Trig_ZCE_h = (ZCSigState)(rtDW.Curr_Reset_Sinal > 0);

  /* End of Outputs for SubSystem: '<S26>/Reset_Block' */

  /* Sum: '<S26>/Sum' incorporates:
   *  DataStoreRead: '<S26>/Data Store Read'
   */
  rtb_Product1_jr += rtb_out_bj;

  /* Outputs for Atomic SubSystem: '<S19>/PLL_LPF1' */
  /* ArithShift: '<S19>/Shift Arithmetic6' incorporates:
   *  DataStoreRead: '<S19>/Data Store Read5'
   *  Product: '<S19>/Product6'
   *  Sum: '<S19>/Sum2'
   *  UnitDelay: '<S19>/Unit Delay3'
   */
  rtb_Sum_b = PLL_LPF1(((int16_T)((int16_T)rtb_Product1_jr - (int16_T)
    rtDW.UnitDelay3_DSTATE_p) * rtDW.FOC_FRQ_Point) >> 16, &rtDW.PLL_LPF1_f);

  /* End of Outputs for SubSystem: '<S19>/PLL_LPF1' */

  /* Outputs for Atomic SubSystem: '<S19>/PLL_LPF2' */
  /* ArithShift: '<S19>/Shift Arithmetic13' incorporates:
   *  ArithShift: '<S23>/Shift Arithmetic9'
   */
  rtb_ShiftArithmetic9_a = PLL_LPF1(rtb_ShiftArithmetic9_a >> 16, &rtDW.PLL_LPF2);

  /* End of Outputs for SubSystem: '<S19>/PLL_LPF2' */

  /* ArithShift: '<S19>/Shift Arithmetic15' incorporates:
   *  ArithShift: '<S19>/Shift Arithmetic10'
   *  DataStoreRead: '<S19>/Data Store Read6'
   *  Product: '<S19>/Product2'
   *  UnitDelay: '<S19>/Unit Delay2'
   */
  rtb_out_bj = ((rtDW.DIV_LPF_FRQ << 8) * rtDW.UnitDelay2_DSTATE_h) >> 15;

  /* MATLAB Function: '<S19>/atan_1' */
  if (rtb_out_bj < 0) {
    rtb_out_bj = -rtb_out_bj;
  }

  if (rtb_out_bj > 255) {
    rtb_out_bj = 255;
  }

  /* Sum: '<S19>/Sum3' incorporates:
   *  ArithShift: '<S19>/Shift Arithmetic1'
   *  DataTypeConversion: '<S19>/Data Type Conversion8'
   *  MATLAB Function: '<S19>/atan_1'
   */
  b_index = (uint16_T)(((uint32_T)rtDW.atan256[rtb_out_bj] >> 2) + (uint16_T)
                       rtb_Product1_jr);

  /* Update for UnitDelay: '<S26>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_l = rtb_Product1_jr;

  /* Update for UnitDelay: '<S19>/Unit Delay7' */
  rtDW.UnitDelay7_DSTATE = rtb_Product1_jr;

  /* Update for UnitDelay: '<S19>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE_p = rtb_Product1_jr;

  /* Update for UnitDelay: '<S19>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE_h = rtb_ShiftArithmetic9_a;

  /* End of Outputs for SubSystem: '<S8>/PLL' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtU.Motor_OnOff > 0) {
    /* Outputs for Atomic SubSystem: '<S1>/SVPWM' */
    /* Outport: '<Root>/tABC' */
    SVPWM(rtb_Sum8, rtb_DataTypeConversion1_l, rtY.tABC, &rtDW.PWM_TH);

    /* End of Outputs for SubSystem: '<S1>/SVPWM' */
  } else {
    /* Outport: '<Root>/tABC' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtY.tABC[0] = 0U;
    rtY.tABC[1] = 0U;
    rtY.tABC[2] = 0U;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Update for UnitDelay: '<S1>/Unit Delay7' incorporates:
   *  UnitDelay: '<S1>/Unit Delay5'
   */
  rtDW.UnitDelay7_DSTATE_p = rtDW.UnitDelay5_DSTATE;

  /* Update for UnitDelay: '<S1>/Unit Delay6' */
  rtDW.UnitDelay6_DSTATE_a = rtDW.Merge;

  /* Update for UnitDelay: '<S12>/Unit Delay4' */
  rtDW.UnitDelay4_DSTATE_j = rtb_out_n;

  /* Update for UnitDelay: '<S1>/Unit Delay4' */
  rtDW.UnitDelay4_DSTATE_g = b_index;

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_b = rtDW.Merge;

  /* Update for UnitDelay: '<S12>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE_g = rtb_Sum1_a;

  /* Update for UnitDelay: '<S1>/Unit Delay5' */
  rtDW.UnitDelay5_DSTATE = b_index;

  /* End of Outputs for SubSystem: '<Root>/FOC_PointModel' */

  /* Outport: '<Root>/Obs_Theta' */
  rtY.Obs_Theta = b_index;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_PointModel' */
  /* Outputs for Atomic SubSystem: '<S8>/PLL' */
  /* Outport: '<Root>/Obs_Spd' incorporates:
   *  DataTypeConversion: '<S19>/Data Type Conversion11'
   */
  rtY.Obs_Spd = (int16_T)rtb_Sum_b;

  /* End of Outputs for SubSystem: '<S8>/PLL' */
  /* End of Outputs for SubSystem: '<Root>/FOC_PointModel' */
}

/* Model initialize function */
void FOC_PointModel_initialize(void)
{
  {
    real_T rtb_Product4;
    real_T u_0;
    real_T v;
    int32_T i;
    real32_T rtb_Product9;
    real32_T u_tmp;
    real32_T v_0;
    static const int16_T tmp[512] = { 0, 402, 804, 1207, 1609, 2011, 2412, 2814,
      3214, 3615, 4015, 4414, 4812, 5210, 5607, 6003, 6398, 6793, 7186, 7578,
      7969, 8359, 8747, 9135, 9521, 9905, 10288, 10669, 11049, 11427, 11804,
      12178, 12551, 12922, 13291, 13658, 14022, 14385, 14746, 15104, 15460,
      15814, 16165, 16514, 16860, 17204, 17546, 17884, 18220, 18553, 18884,
      19211, 19536, 19857, 20176, 20492, 20804, 21114, 21420, 21723, 22023,
      22319, 22612, 22902, 23188, 23470, 23750, 24025, 24297, 24565, 24830,
      25090, 25347, 25601, 25850, 26095, 26337, 26574, 26808, 27037, 27263,
      27484, 27701, 27914, 28123, 28327, 28527, 28723, 28915, 29102, 29285,
      29463, 29637, 29806, 29971, 30132, 30288, 30439, 30586, 30728, 30865,
      30998, 31126, 31250, 31368, 31482, 31592, 31696, 31796, 31891, 31981,
      32066, 32146, 32222, 32293, 32359, 32419, 32476, 32527, 32573, 32614,
      32651, 32682, 32709, 32730, 32747, 32759, 32766, MAX_int16_T, 32764, 32756,
      32743, 32725, 32703, 32675, 32642, 32604, 32562, 32514, 32462, 32405,
      32343, 32275, 32204, 32127, 32045, 31959, 31867, 31771, 31670, 31565,
      31454, 31339, 31219, 31095, 30965, 30831, 30693, 30549, 30402, 30249,
      30092, 29930, 29764, 29594, 29419, 29239, 29055, 28867, 28674, 28478,
      28276, 28071, 27861, 27647, 27429, 27207, 26980, 26750, 26515, 26277,
      26034, 25788, 25538, 25284, 25026, 24764, 24498, 24229, 23956, 23680,
      23400, 23117, 22830, 22539, 22245, 21948, 21647, 21344, 21037, 20726,
      20413, 20097, 19777, 19455, 19130, 18801, 18470, 18136, 17800, 17461,
      17119, 16774, 16427, 16078, 15726, 15371, 15015, 14656, 14295, 13931,
      13566, 13199, 12829, 12458, 12085, 11710, 11333, 10954, 10574, 10192, 9809,
      9424, 9038, 8650, 8262, 7871, 7480, 7088, 6694, 6300, 5904, 5508, 5111,
      4713, 4314, 3915, 3515, 3114, 2713, 2312, 1910, 1508, 1106, 704, 301, -100,
      -503, -905, -1307, -1709, -2111, -2513, -2914, -3315, -3715, -4114, -4513,
      -4912, -5309, -5706, -6102, -6497, -6891, -7284, -7676, -8067, -8456,
      -8844, -9231, -9617, -10001, -10383, -10764, -11144, -11521, -11897,
      -12271, -12644, -13014, -13383, -13749, -14113, -14475, -14835, -15193,
      -15549, -15902, -16253, -16601, -16947, -17290, -17630, -17968, -18304,
      -18636, -18966, -19293, -19616, -19937, -20255, -20570, -20882, -21191,
      -21496, -21798, -22097, -22393, -22685, -22973, -23259, -23541, -23819,
      -24093, -24364, -24632, -24895, -25155, -25411, -25663, -25912, -26156,
      -26397, -26633, -26866, -27094, -27318, -27538, -27755, -27966, -28174,
      -28377, -28577, -28771, -28962, -29148, -29330, -29507, -29680, -29848,
      -30012, -30171, -30326, -30476, -30622, -30763, -30899, -31031, -31157,
      -31280, -31397, -31510, -31618, -31721, -31820, -31914, -32003, -32087,
      -32166, -32240, -32310, -32374, -32434, -32489, -32539, -32584, -32624,
      -32659, -32689, -32715, -32735, -32750, -32761, -32767, -32767, -32763,
      -32754, -32739, -32720, -32696, -32667, -32633, -32594, -32550, -32502,
      -32448, -32390, -32326, -32258, -32185, -32107, -32024, -31936, -31844,
      -31747, -31644, -31538, -31426, -31310, -31189, -31063, -30932, -30797,
      -30657, -30513, -30364, -30210, -30052, -29889, -29722, -29550, -29374,
      -29194, -29009, -28819, -28626, -28428, -28225, -28019, -27808, -27593,
      -27374, -27150, -26923, -26692, -26456, -26217, -25973, -25726, -25475,
      -25219, -24961, -24698, -24432, -24161, -23888, -23610, -23330, -23045,
      -22757, -22466, -22171, -21873, -21572, -21267, -20959, -20648, -20334,
      -20017, -19697, -19374, -19048, -18719, -18387, -18052, -17715, -17375,
      -17033, -16688, -16340, -15990, -15637, -15282, -14925, -14566, -14204,
      -13840, -13474, -13106, -12737, -12365, -11991, -11616, -11238, -10859,
      -10479, -10097, -9713, -9328, -8941, -8553, -8164, -7774, -7382, -6989,
      -6596, -6201, -5805, -5409, -5011, -4613, -4214, -3815, -3415, -3014,
      -2613, -2212, -1810, -1408, -1006, -603, -201 };

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_PointModel' */
    /* Start for SwitchCase: '<S1>/Switch Case' */
    rtDW.SwitchCase_ActiveSubsystem = -1;

    /* SystemInitialize for IfAction SubSystem: '<S1>/加速强拖' */
    /* SystemInitialize for Atomic SubSystem: '<S58>/积分器//上升沿初始化' */
    u_Init(&rtPrevZCX.u_k);

    /* End of SystemInitialize for SubSystem: '<S58>/积分器//上升沿初始化' */

    /* SystemInitialize for Atomic SubSystem: '<S58>/积分器//上升沿初始化1' */
    u_Init(&rtPrevZCX.u_ae);

    /* End of SystemInitialize for SubSystem: '<S58>/积分器//上升沿初始化1' */
    /* End of SystemInitialize for SubSystem: '<S1>/加速强拖' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/恒速降力矩强拖' */
    /* SystemInitialize for Atomic SubSystem: '<S65>/积分器//下降沿初始化' */
    /* SystemInitialize for Triggered SubSystem: '<S67>/Reset_Block' */
    rtPrevZCX.Reset_Block_Trig_ZCE_e = POS_ZCSIG;

    /* End of SystemInitialize for SubSystem: '<S67>/Reset_Block' */
    /* End of SystemInitialize for SubSystem: '<S65>/积分器//下降沿初始化' */
    /* End of SystemInitialize for SubSystem: '<S1>/恒速降力矩强拖' */

    /* SystemInitialize for Atomic SubSystem: '<S12>/PI Controller' */
    /* SystemInitialize for Triggered SubSystem: '<S44>/Reset_Block' */
    rtPrevZCX.Reset_Block_Trig_ZCE_j = ZERO_ZCSIG;

    /* End of SystemInitialize for SubSystem: '<S44>/Reset_Block' */
    /* End of SystemInitialize for SubSystem: '<S12>/PI Controller' */

    /* SystemInitialize for Atomic SubSystem: '<S12>/PI Controller1' */
    /* SystemInitialize for Triggered SubSystem: '<S50>/Reset_Block' */
    rtPrevZCX.Reset_Block_Trig_ZCE = ZERO_ZCSIG;

    /* End of SystemInitialize for SubSystem: '<S50>/Reset_Block' */
    /* End of SystemInitialize for SubSystem: '<S12>/PI Controller1' */

    /* SystemInitialize for MATLAB Function: '<S1>/Sin2_512' */
    memcpy(&rtDW.sin512[0], &tmp[0], sizeof(int16_T) << 9U);

    /* SystemInitialize for Atomic SubSystem: '<S8>/PLL' */
    /* SystemInitialize for MATLAB Function: '<S19>/Sin2_1' */
    memcpy(&rtDW.sin512_h[0], &tmp[0], sizeof(int16_T) << 9U);

    /* SystemInitialize for Atomic SubSystem: '<S19>/PI Controller' */
    /* SystemInitialize for Triggered SubSystem: '<S28>/Reset_Block' */
    rtPrevZCX.Reset_Block_Trig_ZCE_m = ZERO_ZCSIG;

    /* End of SystemInitialize for SubSystem: '<S28>/Reset_Block' */
    /* End of SystemInitialize for SubSystem: '<S19>/PI Controller' */

    /* SystemInitialize for Triggered SubSystem: '<S26>/Reset_Block' */
    rtPrevZCX.Reset_Block_Trig_ZCE_h = ZERO_ZCSIG;

    /* End of SystemInitialize for SubSystem: '<S26>/Reset_Block' */

    /* SystemInitialize for MATLAB Function: '<S19>/atan_1' */
    for (i = 0; i < 256; i++) {
      rtDW.atan256[i] = (uint16_T)(i << 6);
    }

    /* End of SystemInitialize for MATLAB Function: '<S19>/atan_1' */
    /* End of SystemInitialize for SubSystem: '<S8>/PLL' */

    /* Outputs for Atomic SubSystem: '<S1>/初始化模块' */
    /* MATLAB Function: '<S14>/MATLAB Function2' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic'
     *  Constant: '<S14>/Constant18'
     *  Constant: '<S14>/周期定点化适当放大2^n'
     */
    i = -(int16_T)-((int16_T)TS_POINT_GAIN);
    if (-(int16_T)-((int16_T)TS_POINT_GAIN) > 32767) {
      i = 32767;
    }

    if ((int16_T)i >= 0) {
      if ((int16_T)i <= 63) {
        u_0 = (real_T)(1ULL << (int16_T)i);
      } else {
        u_0 = 0.0;
      }
    } else if ((int16_T)i >= -63) {
      u_0 = (real_T)(1ULL >> (int16_T)-(int16_T)i);
    } else {
      u_0 = 0.0;
    }

    u_0 *= ldexp(1.0 / FOC_FRQ, 15);

    /* End of MATLAB Function: '<S14>/MATLAB Function2' */

    /* DataTypeConversion: '<S14>/Data Type Conversion6' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write7'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.Ts_Point = (int16_T)floor(u_0 + 0.5);
      } else {
        rtDW.Ts_Point = 0;
      }
    } else {
      rtDW.Ts_Point = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion6' */

    /* MATLAB Function: '<S14>/MATLAB Function' incorporates:
     *  Constant: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流'
     *  Constant: '<S14>/电流采集定点化适当放大2^n'
     */
    i = -(int16_T)-((int16_T)CURR_POINT_GAIN);
    if (-(int16_T)-((int16_T)CURR_POINT_GAIN) > 32767) {
      i = 32767;
    }

    if ((int16_T)i >= 0) {
      if ((int16_T)i <= 63) {
        u_0 = (real_T)(1ULL << (int16_T)i);
      } else {
        u_0 = 0.0;
      }
    } else if ((int16_T)i >= -63) {
      u_0 = (real_T)(1ULL >> (int16_T)-(int16_T)i);
    } else {
      u_0 = 0.0;
    }

    rtb_Product9 = ADC_REF / AMP_GAIN / IMAX / RS_HUNT * (real32_T)u_0;

    /* End of MATLAB Function: '<S14>/MATLAB Function' */

    /* DataTypeConversion: '<S14>/Data Type Conversion4' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write5'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Conversion = (int16_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Curr_Conversion = 0;
      }
    } else {
      rtDW.Curr_Conversion = (int16_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion4' */

    /* Product: '<S14>/Divide7' incorporates:
     *  Constant: '<S14>/Constant20'
     *  Constant: '<S14>/Constant21'
     */
    rtb_Product4 = 1.0 / FOC_FRQ / MOTOR_LS;

    /* ArithShift: '<S14>/Shift Arithmetic3' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant15'
     *  Product: '<S14>/Product5'
     *  Sum: '<S14>/Sum'
     */
    u_0 = ldexp(1.0 - MOTOR_RS * rtb_Product4, 8);

    /* DataTypeConversion: '<S14>/Data Type Conversion9' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write10'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain1 = (uint16_T)floor(u_0 + 0.5);
      } else {
        rtDW.SMO_Gain1 = 0U;
      }
    } else {
      rtDW.SMO_Gain1 = (uint16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion9' */

    /* ArithShift: '<S14>/Shift Arithmetic4' incorporates:
     *  Product: '<S14>/Product4'
     */
    u_0 = ldexp(rtb_Product4, 8);

    /* DataTypeConversion: '<S14>/Data Type Conversion10' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write11'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain2 = (uint16_T)floor(u_0 + 0.5);
      } else {
        rtDW.SMO_Gain2 = 0U;
      }
    } else {
      rtDW.SMO_Gain2 = (uint16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion10' */

    /* Product: '<S14>/Divide' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S14>/Constant2'
     *  DataStoreWrite: '<S14>/Data Store Write1'
     *  Product: '<S14>/Divide1'
     */
    u_tmp = IMAX / (real32_T)Udc;

    /* ArithShift: '<S14>/Shift Arithmetic1' incorporates:
     *  Constant: '<S14>/Constant10'
     *  Constant: '<S14>/Constant9'
     *  Product: '<S14>/Divide'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product2'
     */
    rtb_Product9 = ldexpf(CURR_WIDTH * MOTOR_LS * u_tmp, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion11' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Kp_Point = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Curr_Kp_Point = 0;
      }
    } else {
      rtDW.Curr_Kp_Point = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion11' */

    /* ArithShift: '<S14>/Shift Arithmetic2' incorporates:
     *  Constant: '<S14>/Constant11'
     *  Constant: '<S14>/Constant12'
     *  Product: '<S14>/Product1'
     *  Product: '<S14>/Product3'
     */
    rtb_Product9 = ldexpf(CURR_WIDTH * MOTOR_RS * u_tmp, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion1' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write2'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Ki_Point = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Curr_Ki_Point = 0;
      }
    } else {
      rtDW.Curr_Ki_Point = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion1' */

    /* Product: '<S14>/Divide5' incorporates:
     *  Constant: '<S14>/Constant'
     *  Constant: '<S14>/Constant13'
     *  DataStoreWrite: '<S14>/Data Store Write1'
     */
    rtb_Product9 = (real32_T)Udc / IMAX;

    /* DataTypeConversion: '<S14>/Data Type Conversion8' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write9'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Obs_VtoI = (int16_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Obs_VtoI = 0;
      }
    } else {
      rtDW.Obs_VtoI = (int16_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion8' */

    /* Gain: '<S14>/Gain2' incorporates:
     *  Constant: '<S14>/Constant5'
     */
    rtb_Product9 = MOTOR_PN / 60.0F * OPEN_SPD;

    /* DataTypeConversion: '<S14>/Data Type Conversion2' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write12'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Hz = (int16_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Open_Hz = 0;
      }
    } else {
      rtDW.Open_Hz = (int16_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion2' */

    /* Product: '<S14>/Product4' incorporates:
     *  Constant: '<S14>/Constant14'
     *  Constant: '<S14>/Constant17'
     *  Product: '<S14>/Divide4'
     */
    u_0 = 1.0 / OPEN_TIME * rtb_Product9;

    /* DataTypeConversion: '<S14>/Data Type Conversion7' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write13'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.Open_Acceleration = (int16_T)floor(u_0 + 0.5);
      } else {
        rtDW.Open_Acceleration = 0;
      }
    } else {
      rtDW.Open_Acceleration = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion7' */

    /* Product: '<S14>/Product6' incorporates:
     *  Constant: '<S14>/Constant19'
     *  Constant: '<S14>/Constant22'
     */
    rtb_Product4 = 1.0 / FOC_FRQ * LPF_FRQ;

    /* DataTypeConversion: '<S14>/Data Type Conversion12' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic5'
     *  Constant: '<S14>/Constant24'
     *  DataStoreWrite: '<S14>/Data Store Write3'
     *  Product: '<S14>/Divide6'
     *  Sum: '<S14>/Sum1'
     */
    rtDW.LPF_FRQ_Point = (int16_T)ceil(ldexp(rtb_Product4 / (rtb_Product4 + 1.0),
      4));

    /* Product: '<S14>/Product8' incorporates:
     *  Constant: '<S14>/Constant25'
     *  Constant: '<S14>/Constant26'
     */
    rtb_Product9 = PLL_WIDTH * PLL_WIDTH;

    /* DataTypeConversion: '<S14>/Data Type Conversion14' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write14'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Ki = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.PLL_Ki = 0;
      }
    } else {
      rtDW.PLL_Ki = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion14' */

    /* Product: '<S14>/Product7' incorporates:
     *  Constant: '<S14>/Constant25'
     *  Constant: '<S14>/Constant27'
     */
    u_0 = 1.414 * PLL_WIDTH;

    /* DataTypeConversion: '<S14>/Data Type Conversion13' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write8'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.PLL_Kp = (int16_T)floor(u_0 + 0.5);
      } else {
        rtDW.PLL_Kp = 0;
      }
    } else {
      rtDW.PLL_Kp = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion13' */

    /* DataTypeConversion: '<S14>/Data Type Conversion15' incorporates:
     *  Constant: '<S14>/Constant28'
     *  Constant: '<S14>/Constant29'
     *  DataStoreRead: '<S14>/Data Store Read3'
     *  DataStoreWrite: '<S14>/Data Store Write15'
     *  Product: '<S14>/Divide8'
     *  Product: '<S14>/Product9'
     */
    rtDW.SMO_K = (int16_T)ceilf(LPF_FRQ * MOTOR_FLUX / (real32_T)rtDW.Obs_VtoI);

    /* DataTypeConversion: '<S14>/Data Type Conversion16' incorporates:
     *  Constant: '<S14>/Constant30'
     *  DataStoreWrite: '<S14>/Data Store Write16'
     */
    v = fabs(FOC_FRQ);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.FOC_FRQ_Point = (int16_T)floor(FOC_FRQ + 0.5);
      } else {
        rtDW.FOC_FRQ_Point = 0;
      }
    } else {
      rtDW.FOC_FRQ_Point = (int16_T)FOC_FRQ;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion16' */

    /* ArithShift: '<S14>/Shift Arithmetic6' incorporates:
     *  Constant: '<S14>/Constant31'
     */
    rtb_Product9 = ldexpf(1.0F / LPF_FRQ, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion17' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write17'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.DIV_LPF_FRQ = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.DIV_LPF_FRQ = 0;
      }
    } else {
      rtDW.DIV_LPF_FRQ = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion17' */

    /* Product: '<S14>/Product10' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic7'
     *  Constant: '<S14>/Constant32'
     */
    rtb_Product9 = PLL_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S14>/Data Type Conversion18' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write18'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Limit = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.PLL_Limit = 0;
      }
    } else {
      rtDW.PLL_Limit = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion18' */

    /* Product: '<S14>/Product11' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic8'
     *  Constant: '<S14>/Constant34'
     */
    rtb_Product9 = CURR_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S14>/Data Type Conversion19' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write19'
     */
    v_0 = fabsf(rtb_Product9);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Limit = (int32_T)floorf(rtb_Product9 + 0.5F);
      } else {
        rtDW.Curr_Limit = 0;
      }
    } else {
      rtDW.Curr_Limit = (int32_T)rtb_Product9;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion19' */

    /* Product: '<S14>/Divide2' incorporates:
     *  Constant: '<S14>/Constant7'
     *  Constant: '<S14>/Constant8'
     */
    u_0 = PWM_FRQ / (FOC_FRQ * 2.0);

    /* DataTypeConversion: '<S14>/Data Type Conversion3' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write4'
     */
    v = fabs(u_0);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.PWM_TH = (int16_T)floor(u_0 + 0.5);
      } else {
        rtDW.PWM_TH = 0;
      }
    } else {
      rtDW.PWM_TH = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S14>/Data Type Conversion3' */
    /* End of Outputs for SubSystem: '<S1>/初始化模块' */
    /* End of SystemInitialize for SubSystem: '<Root>/FOC_PointModel' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
