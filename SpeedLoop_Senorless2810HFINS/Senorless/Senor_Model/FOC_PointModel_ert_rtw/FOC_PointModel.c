/*
 * File: FOC_PointModel.c
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

#include "FOC_PointModel.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S1>/Chart' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_CompStage                   ((uint8_T)2U)
#define IN_EndStage                    ((uint8_T)3U)
#define IN_IDLE                        ((uint8_T)4U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_NSStage                     ((uint8_T)5U)
#define IN_RunStage                    ((uint8_T)6U)
#define IN_StopStage                   ((uint8_T)7U)

/* Named constants for Chart: '<S6>/Chart' */
#define IN_DISABLE                     ((uint8_T)1U)
#define IN_ENABLE                      ((uint8_T)2U)
#define IN_ENABLE1                     ((uint8_T)3U)

/* Named constants for Chart: '<S9>/obs_chart' */
#define IN_Begin                       ((uint8_T)1U)
#define IN_HFI                         ((uint8_T)2U)
#define IN_HFI_SMO1                    ((uint8_T)3U)
#define IN_HFI_SMO2                    ((uint8_T)4U)
#define IN_SMO                         ((uint8_T)5U)

/* Named constants for Chart: '<S8>/正负偏置' */
#define IN_Down                        ((uint8_T)1U)
#define IN_Up                          ((uint8_T)2U)
#define IN_Zero                        ((uint8_T)3U)
#define IN_Zero1                       ((uint8_T)4U)

/* Named constants for Chart: '<S18>/速度缓冲1' */
#define IN_Open_Loop                   ((uint8_T)1U)
#define IN_SPD_Loop                    ((uint8_T)2U)

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern int16_T rt_sqrt_Us32_Ys16_Is32__s(int32_T u);
static uint32_T plook_u32u16_even0ckag(uint16_T u, uint16_T bp0);
static void max_Reset(DW_max *localDW);

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  static void max_Disable(DW_max *localDW);

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  static void max(int32_T rtu_Enable, int32_T rtu_input, int32_T *rty_output,
                  DW_max *localDW);
static uint32_T plook_u32u16_even0ckag(uint16_T u, uint16_T bp0)
{
  /* Prelookup - Index only
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'on'
   */
  return (uint16_T)((uint32_T)u - bp0);
}

/*
 * System reset for enable system:
 *    '<S8>/max'
 *    '<S8>/min'
 */
static void max_Reset(DW_max *localDW)
{
  /* InitializeConditions for UnitDelay: '<S25>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0;
}

/*
 * Disable for enable system:
 *    '<S8>/max'
 *    '<S8>/min'
 */

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  static void max_Disable(DW_max *localDW)
{
  localDW->max_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S8>/max'
 *    '<S8>/min'
 */

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  static void max(int32_T rtu_Enable, int32_T rtu_input, int32_T *rty_output,
                  DW_max *localDW)
{
  /* Outputs for Enabled SubSystem: '<S8>/max' incorporates:
   *  EnablePort: '<S25>/Enable'
   */
  if (rtu_Enable > 0) {
    if (!localDW->max_MODE) {
      max_Reset(localDW);
      localDW->max_MODE = true;
    }

    /* Sum: '<S25>/Sum' incorporates:
     *  UnitDelay: '<S25>/Unit Delay'
     */
    *rty_output = rtu_input + localDW->UnitDelay_DSTATE;

    /* Update for UnitDelay: '<S25>/Unit Delay' */
    localDW->UnitDelay_DSTATE = *rty_output;
  } else if (localDW->max_MODE) {
    max_Disable(localDW);
  }

  /* End of Outputs for SubSystem: '<S8>/max' */
}

int16_T rt_sqrt_Us32_Ys16_Is32__s(int32_T u)
{
  int32_T iBit;
  int16_T shiftMask;
  int16_T y;

  /* Fixed-Point Sqrt Computation by the bisection method. */
  y = 0;
  shiftMask = 16384;
  for (iBit = 0; iBit < 15; iBit++) {
    int16_T tmp01_y;
    tmp01_y = (int16_T)(y | shiftMask);
    if (tmp01_y * tmp01_y <= u) {
      y = tmp01_y;
    }

    shiftMask = (int16_T)((uint32_T)shiftMask >> 1U);
  }

  return y;
}

/* Model step function */

/*Add __attribute__((section(".ramfunc"))) to Function*/
__attribute__((section(".ramfunc")))
  void FOC_PointModel_step(void)
{
  int64_T rtb_ShiftArithmetic1;
  int64_T rtb_Sum;
  int32_T rtb_Gain_k;
  int32_T rtb_Min1;
  int32_T rtb_ShiftArithmetic3_m;
  int32_T rtb_ShiftArithmetic9_e1;
  int32_T rtb_ShiftArithmetic_f;
  int32_T rtb_ShiftArithmetic_lo;
  int32_T rtb_Sign_a;
  int32_T rtb_Sign_h;
  int32_T rtb_Sum1_o;
  int32_T rtb_Sum2_e;
  int32_T rtb_Sum2_pv;
  int32_T rtb_Sum4_p;
  int32_T rtb_Sum7;
  int32_T rtb_Sum_aj;
  int32_T rtb_UnitDelay3;
  int32_T rtb_Uq;
  int16_T rtb_PulseGenerator1;
  int16_T rtb_Sin1;
  int16_T rtb_Sum10_i;
  int16_T rtb_Sum12;
  int16_T rtb_Sum5_f;
  int16_T rtb_Sum_pv;
  uint16_T rtb_UnitDelay6;
  int8_T rtAction;
  int8_T rtPrevAction;
  boolean_T rtb_LogicalOperator_d;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_output;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_PointModel' */
  /* DiscretePulseGenerator: '<S6>/Pulse Generator1' incorporates:
   *  Constant: '<S6>/Constant5'
   *  Sum: '<S6>/Sum2'
   *  Switch: '<S6>/Switch'
   */
  rtb_PulseGenerator1 = (int16_T)(((rtDW.clockTickCounter < 1) &&
    (rtDW.clockTickCounter >= 0) ? 2 : 0) - 1);
  if (rtDW.clockTickCounter >= 1) {
    rtDW.clockTickCounter = 0;
  } else {
    rtDW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S6>/Pulse Generator1' */

  /* Chart: '<S6>/Chart' incorporates:
   *  UnitDelay: '<S6>/Unit Delay'
   */
  if (rtDW.temporalCounter_i1_d < 2047U) {
    rtDW.temporalCounter_i1_d++;
  }

  if (rtDW.is_active_c7_FOC_PointModel == 0U) {
    rtDW.is_active_c7_FOC_PointModel = 1U;
    rtDW.is_c7_FOC_PointModel = IN_ENABLE;
    rtb_output = true;
  } else {
    switch (rtDW.is_c7_FOC_PointModel) {
     case IN_DISABLE:
      if (OBS_SPD > 1073741823) {
        rtb_Sum_aj = MAX_int32_T;
      } else if (OBS_SPD <= -1073741824) {
        rtb_Sum_aj = MIN_int32_T;
      } else {
        rtb_Sum_aj = OBS_SPD << 1;
      }

      if (rtDW.UnitDelay_DSTATE < rtb_Sum_aj) {
        rtDW.is_c7_FOC_PointModel = IN_ENABLE;
        rtb_output = true;
      } else {
        rtb_output = false;
      }
      break;

     case IN_ENABLE:
      if (OBS_SPD > 1073741823) {
        rtb_ShiftArithmetic_f = MAX_int32_T;
      } else if (OBS_SPD <= -1073741824) {
        rtb_ShiftArithmetic_f = MIN_int32_T;
      } else {
        rtb_ShiftArithmetic_f = OBS_SPD << 1;
      }

      if ((rtb_ShiftArithmetic_f < 0) && (OBS_SPD < MIN_int32_T
           - rtb_ShiftArithmetic_f)) {
        rtb_Sum_aj = MIN_int32_T;
      } else if ((rtb_ShiftArithmetic_f > 0) && (OBS_SPD > MAX_int32_T
                  - rtb_ShiftArithmetic_f)) {
        rtb_Sum_aj = MAX_int32_T;
      } else {
        rtb_Sum_aj = rtb_ShiftArithmetic_f + OBS_SPD;
      }

      if (rtDW.UnitDelay_DSTATE > rtb_Sum_aj) {
        rtDW.is_c7_FOC_PointModel = IN_ENABLE1;
        rtDW.temporalCounter_i1_d = 0U;
        rtb_output = true;
      } else {
        rtb_output = true;
      }
      break;

     default:
      /* case IN_ENABLE1: */
      if (rtDW.temporalCounter_i1_d >= 1800U) {
        rtDW.is_c7_FOC_PointModel = IN_DISABLE;
        rtb_output = false;
      } else {
        rtb_output = true;
      }
      break;
    }
  }

  /* End of Chart: '<S6>/Chart' */

  /* ArithShift: '<S1>/Shift Arithmetic' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ia'
   *  Product: '<S1>/Product'
   */
  rtb_ShiftArithmetic_f = (rtU.ia * rtDW.Curr_Conversion) >> ((int16_T)
    CURR_POINT_GAIN);

  /* ArithShift: '<S1>/Shift Arithmetic1' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ib'
   *  Product: '<S1>/Product1'
   */
  rtb_Uq = (rtU.ib * rtDW.Curr_Conversion) >> ((int16_T)CURR_POINT_GAIN);

  /* ArithShift: '<S1>/Shift Arithmetic2' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ic'
   *  Product: '<S1>/Product2'
   */
  rtb_Min1 = (rtU.ic * rtDW.Curr_Conversion) >> ((int16_T)CURR_POINT_GAIN);

  /* Abs: '<S5>/Abs1' */
  if (rtb_ShiftArithmetic_f < 0) {
    rtb_ShiftArithmetic3_m = -rtb_ShiftArithmetic_f;
  } else {
    rtb_ShiftArithmetic3_m = rtb_ShiftArithmetic_f;
  }

  /* End of Abs: '<S5>/Abs1' */

  /* Abs: '<S5>/Abs2' */
  if (rtb_Uq < 0) {
    rtb_ShiftArithmetic9_e1 = -rtb_Uq;
  } else {
    rtb_ShiftArithmetic9_e1 = rtb_Uq;
  }

  /* End of Abs: '<S5>/Abs2' */

  /* MinMax: '<S5>/Max' */
  if (rtb_ShiftArithmetic3_m >= rtb_ShiftArithmetic9_e1) {
    rtb_ShiftArithmetic9_e1 = rtb_ShiftArithmetic3_m;
  }

  /* Abs: '<S5>/Abs3' */
  if (rtb_Min1 < 0) {
    rtb_ShiftArithmetic3_m = -rtb_Min1;
  } else {
    rtb_ShiftArithmetic3_m = rtb_Min1;
  }

  /* End of Abs: '<S5>/Abs3' */

  /* MinMax: '<S5>/Max' */
  if (rtb_ShiftArithmetic9_e1 >= rtb_ShiftArithmetic3_m) {
    rtb_ShiftArithmetic3_m = rtb_ShiftArithmetic9_e1;
  }

  /* Outputs for Atomic SubSystem: '<S5>/PLL_LPF1' */
  /* ArithShift: '<S20>/Shift Arithmetic9' incorporates:
   *  Constant: '<S20>/Constant1'
   *  MinMax: '<S5>/Max'
   *  Product: '<S20>/Product11'
   *  Sum: '<S20>/Sum11'
   *  UnitDelay: '<S20>/Unit Delay9'
   */
  rtb_ShiftArithmetic9_e1 = (rtDW.UnitDelay9_DSTATE_j * 15 +
    rtb_ShiftArithmetic3_m) >> 4;

  /* Update for UnitDelay: '<S20>/Unit Delay9' */
  rtDW.UnitDelay9_DSTATE_j = rtb_ShiftArithmetic9_e1;

  /* End of Outputs for SubSystem: '<S5>/PLL_LPF1' */

  /* RelationalOperator: '<S5>/Relational Operator' incorporates:
   *  DataStoreRead: '<S5>/Data Store Read3'
   */
  rtb_RelationalOperator = (rtDW.Curr_Over < rtb_ShiftArithmetic9_e1);

  /* ArithShift: '<S1>/Shift Arithmetic3' incorporates:
   *  Constant: '<S1>/Constant33'
   *  DataStoreRead: '<S1>/Data Store Read'
   *  Inport: '<Root>/v_bus'
   *  Product: '<S1>/Product3'
   */
  rtb_ShiftArithmetic3_m = (rtU.v_bus * rtDW.Voltage_Conversion) >> ((int16_T)
    UDC_POINT_GAIN);

  /* Outputs for Enabled SubSystem: '<S5>/闭环错误判断' incorporates:
   *  EnablePort: '<S21>/Enable'
   */
  /* RelationalOperator: '<S5>/Relational Operator1' incorporates:
   *  Constant: '<S5>/闭环是4'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  if (rtDW.Motor_State == 4) {
    rtDW._MODE = true;

    /* Logic: '<S21>/Logical Operator' incorporates:
     *  Constant: '<S21>/Constant'
     *  DataStoreRead: '<S21>/Data Store Read7'
     *  RelationalOperator: '<S21>/Relational Operator1'
     *  RelationalOperator: '<S21>/Relational Operator4'
     */
    rtb_LogicalOperator_d = ((rtb_ShiftArithmetic3_m < 16384) ||
      (rtb_ShiftArithmetic9_e1 < rtDW.Curr_Under));

    /* If: '<S21>/If1' incorporates:
     *  DataTypeConversion: '<S21>/Data Type Conversion13'
     */
    rtPrevAction = rtDW.If1_ActiveSubsystem;
    rtAction = (int8_T)!rtb_LogicalOperator_d;
    rtDW.If1_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (rtPrevAction != 0) {
        /* InitializeConditions for IfAction SubSystem: '<S21>/SUM' incorporates:
         *  ActionPort: '<S22>/Action Port'
         */
        /* InitializeConditions for If: '<S21>/If1' incorporates:
         *  UnitDelay: '<S22>/Unit Delay2'
         */
        rtDW.UnitDelay2_DSTATE_a = 0;

        /* End of InitializeConditions for SubSystem: '<S21>/SUM' */
      }

      /* Outputs for IfAction SubSystem: '<S21>/SUM' incorporates:
       *  ActionPort: '<S22>/Action Port'
       */
      /* SignalConversion generated from: '<S22>/out' incorporates:
       *  UnitDelay: '<S22>/Unit Delay2'
       */
      rtb_ShiftArithmetic9_e1 = rtDW.UnitDelay2_DSTATE_a;

      /* Update for UnitDelay: '<S22>/Unit Delay2' incorporates:
       *  DataTypeConversion: '<S21>/Data Type Conversion12'
       *  Sum: '<S22>/Sum'
       */
      rtDW.UnitDelay2_DSTATE_a += rtb_LogicalOperator_d;

      /* End of Outputs for SubSystem: '<S21>/SUM' */
    } else {
      /* Outputs for IfAction SubSystem: '<S21>/ZERO' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
      /* SignalConversion generated from: '<S23>/out' incorporates:
       *  Constant: '<S23>/Constant'
       */
      rtb_ShiftArithmetic9_e1 = 0;

      /* End of Outputs for SubSystem: '<S21>/ZERO' */
    }

    /* End of If: '<S21>/If1' */

    /* Logic: '<S21>/OR1' incorporates:
     *  ArithShift: '<S21>/半秒的意思'
     *  DataStoreRead: '<S21>/Data Store Read'
     *  RelationalOperator: '<S21>/Relational Operator3'
     */
    rtDW.OR1 = (rtb_RelationalOperator || (rtb_ShiftArithmetic9_e1 >=
      (rtDW.FOC_FRQ_Point >> 1)));
  } else if (rtDW._MODE) {
    /* Disable for If: '<S21>/If1' */
    rtDW.If1_ActiveSubsystem = -1;
    rtDW._MODE = false;
  }

  /* End of RelationalOperator: '<S5>/Relational Operator1' */
  /* End of Outputs for SubSystem: '<S5>/闭环错误判断' */

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i1_c < 32767U) {
    rtDW.temporalCounter_i1_c++;
  }

  if (rtDW.is_active_c2_FOC_PointModel == 0U) {
    rtDW.is_active_c2_FOC_PointModel = 1U;
    rtDW.is_c2_FOC_PointModel = IN_IDLE;
    rtDW.temporalCounter_i1_c = 0U;
  } else {
    switch (rtDW.is_c2_FOC_PointModel) {
     case IN_AlignStage:
      if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1_c = 0U;
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtDW.temporalCounter_i1_c >= 1800U) {
        rtDW.is_c2_FOC_PointModel = IN_NSStage;
        rtDW.temporalCounter_i1_c = 0U;
        rtDW.Motor_State = 2U;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else {
        rtDW.Motor_State = 1U;
      }
      break;

     case IN_CompStage:
      if ((rtDW.temporalCounter_i1_c >= 18000U) || rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1_c = 0U;
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else if (rtDW.temporalCounter_i1_c >= 1800U) {
        rtDW.is_c2_FOC_PointModel = IN_RunStage;
        rtDW.Motor_State = 4U;
      } else {
        rtDW.Motor_State = 3U;
      }
      break;

     case IN_EndStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else {
        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;

     case IN_IDLE:
      if ((rtU.Motor_OnOff == 1) && (rtDW.temporalCounter_i1_c >= 360U)) {
        rtDW.is_c2_FOC_PointModel = IN_AlignStage;
        rtDW.temporalCounter_i1_c = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 0;
        rtDW.Motor_State = 1U;
      } else {
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;

     case IN_NSStage:
      if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1_c = 0U;
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else if (rtDW.temporalCounter_i1_c >= 1800U) {
        rtDW.is_c2_FOC_PointModel = IN_CompStage;
        rtDW.temporalCounter_i1_c = 0U;
        rtDW.Motor_State = 3U;
      } else {
        rtDW.Motor_State = 2U;
      }
      break;

     case IN_RunStage:
      if (rtDW.OR1) {
        rtDW.is_c2_FOC_PointModel = IN_EndStage;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else {
        rtDW.Motor_State = 4U;
      }
      break;

     default:
      /* case IN_StopStage: */
      if (rtDW.temporalCounter_i1_c >= 7200U) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1_c = 0U;
      } else {
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* RelationalOperator: '<S1>/Relational Operator' incorporates:
   *  Constant: '<S1>/Constant3'
   */
  rtb_RelationalOperator = (rtDW.Motor_State > 0);

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S6>/Constant6'
   *  Logic: '<S6>/Logical Operator'
   */
  if ((!rtb_output) || (!rtb_RelationalOperator)) {
    rtb_PulseGenerator1 = 0;
  }

  /* Sum: '<S48>/Sum' incorporates:
   *  ArithShift: '<S48>/Shift Arithmetic'
   *  Constant: '<S46>/Constant13'
   *  Constant: '<S48>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S48>/Data Store Read1'
   *  Product: '<S46>/Product1'
   *  Product: '<S48>/Product2'
   *  UnitDelay: '<S46>/Unit Delay'
   *  UnitDelay: '<S48>/Unit Delay'
   */
  rtb_ShiftArithmetic9_e1 = ((1571 * rtDW.UnitDelay_DSTATE_k) >> ((int16_T)
    TS_POINT_GAIN)) * rtDW.Ts_Point + rtDW.UnitDelay_DSTATE_i;

  /* ArithShift: '<S48>/这个是缩小周期增益的' incorporates:
   *  Sum: '<S48>/Sum'
   */
  rtb_Sum1_o = rtb_ShiftArithmetic9_e1 >> 15;

  /* UnitDelay: '<S1>/Unit Delay6' */
  rtb_UnitDelay6 = rtDW.UnitDelay6_DSTATE_b;

  /* Sum: '<S17>/Sum' incorporates:
   *  ArithShift: '<S17>/Shift Arithmetic'
   *  Constant: '<S17>/Constant2'
   *  DataStoreRead: '<S17>/Data Store Read1'
   *  DataStoreRead: '<S17>/Data Store Read3'
   *  Product: '<S17>/Product4'
   *  Sum: '<S17>/Sum1'
   */
  rtb_Sum_pv = (int16_T)((int16_T)(rtDW.Uout_Max - (int16_T)((rtDW.Uout_Max *
    rtb_ShiftArithmetic3_m) >> 15)) - 2);

  /* Switch: '<S63>/Switch2' incorporates:
   *  Constant: '<S17>/Constant3'
   *  DataStoreRead: '<S17>/Data Store Read2'
   *  RelationalOperator: '<S63>/LowerRelop1'
   *  RelationalOperator: '<S63>/UpperRelop'
   *  Switch: '<S63>/Switch'
   */
  if (rtb_Sum_pv > rtDW.Uout_Max) {
    rtb_Sum_pv = rtDW.Uout_Max;
  } else if (rtb_Sum_pv < 0) {
    /* Switch: '<S63>/Switch' incorporates:
     *  Constant: '<S17>/Constant3'
     */
    rtb_Sum_pv = 0;
  }

  /* End of Switch: '<S63>/Switch2' */

  /* Sum: '<S17>/Sum2' incorporates:
   *  Constant: '<S17>/Constant1'
   *  Constant: '<S17>/Constant6'
   *  Product: '<S17>/Product'
   */
  rtb_ShiftArithmetic_lo = SPD_MAX - ((int16_T)SPD_REDUCE) * rtb_Sum_pv;

  /* Switch: '<S64>/Switch2' incorporates:
   *  Inport: '<Root>/Spd_Ref'
   *  RelationalOperator: '<S64>/LowerRelop1'
   */
  if (rtU.Spd_Ref <= rtb_ShiftArithmetic_lo) {
    /* Switch: '<S64>/Switch' incorporates:
     *  Constant: '<S17>/Constant7'
     *  RelationalOperator: '<S64>/UpperRelop'
     */
    if (rtU.Spd_Ref < SPD_MIN) {
      rtb_ShiftArithmetic_lo = SPD_MIN;
    } else {
      rtb_ShiftArithmetic_lo = rtU.Spd_Ref;
    }

    /* End of Switch: '<S64>/Switch' */
  }

  /* End of Switch: '<S64>/Switch2' */

  /* UnitDelay: '<S1>/Unit Delay3' */
  rtb_UnitDelay3 = rtDW.UnitDelay3_DSTATE;

  /* ArithShift: '<S4>/Shift Arithmetic' incorporates:
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S4>/Add2'
   */
  rtb_ShiftArithmetic3_m = ((rtb_Uq - rtb_Min1) * 18918) >> 15;

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  UnaryMinus: '<S8>/Unary Minus'
   */
  rtPrevAction = rtDW.SwitchCase_ActiveSubsystem;
  rtAction = -1;
  switch (rtDW.Motor_State) {
   case 0:
    rtAction = 0;
    break;

   case 1:
    rtAction = 1;
    break;

   case 2:
    rtAction = 2;
    break;

   case 3:
    rtAction = 3;
    break;

   case 4:
    rtAction = 4;
    break;
  }

  rtDW.SwitchCase_ActiveSubsystem = rtAction;
  if ((rtPrevAction != rtAction) && (rtPrevAction == 2)) {
    /* Disable for Enabled SubSystem: '<S8>/max' */
    if (rtDW.max_f.max_MODE) {
      max_Disable(&rtDW.max_f);
    }

    /* End of Disable for SubSystem: '<S8>/max' */

    /* Disable for Enabled SubSystem: '<S8>/min' */
    if (rtDW.min.max_MODE) {
      max_Disable(&rtDW.min);
    }

    /* End of Disable for SubSystem: '<S8>/min' */
  }

  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S1>/停止等待' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* DataStoreWrite: '<S14>/Data Store Write' incorporates:
     *  Constant: '<S14>/Constant4'
     */
    rtDW.NS_Flag = 1;

    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S14>/Constant2'
     *  SignalConversion generated from: '<S14>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S14>/Constant1'
     *  SignalConversion generated from: '<S14>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S14>/Constant3'
     *  SignalConversion generated from: '<S14>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/停止等待' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/识别初始位置' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S19>/Obs_Theta'
     */
    rtDW.Merge = rtb_UnitDelay6;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S19>/Constant1'
     *  SignalConversion generated from: '<S19>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S19>/Constant2'
     *  SignalConversion generated from: '<S19>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/识别初始位置' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/NS辨识' incorporates:
       *  ActionPort: '<S8>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S8>/Delay2'
       */
      rtDW.Delay2_DSTATE_h = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/NS辨识' */

      /* SystemReset for IfAction SubSystem: '<S1>/NS辨识' incorporates:
       *  ActionPort: '<S8>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Chart: '<S8>/正负偏置'
       */
      rtDW.temporalCounter_i1_e = 0U;
      rtDW.is_active_c12_FOC_PointModel = 0U;
      rtDW.is_c12_FOC_PointModel = IN_NO_ACTIVE_CHILD;

      /* End of SystemReset for SubSystem: '<S1>/NS辨识' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/NS辨识' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* ArithShift: '<S8>/Shift Arithmetic4' incorporates:
     *  ArithShift: '<S27>/Shift Arithmetic'
     *  ArithShift: '<S27>/Shift Arithmetic1'
     *  Constant: '<S27>/Constant1'
     *  Constant: '<S27>/Constant3'
     *  Lookup_n-D: '<S27>/Sin'
     *  Lookup_n-D: '<S27>/Sin1'
     *  Product: '<S8>/Product4'
     *  Product: '<S8>/Product5'
     *  SignalConversion generated from: '<S8>/Obs_Theta'
     *  Sum: '<S27>/Sum1'
     *  Sum: '<S27>/Sum2'
     *  Sum: '<S8>/Add2'
     */
    rtb_UnitDelay3 = (rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)
      ((uint32_T)(uint16_T)(rtb_UnitDelay6 + 16512U) >> 4), 1U)] *
                      rtb_ShiftArithmetic_f +
                      rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)
      ((uint32_T)(uint16_T)(rtb_UnitDelay6 + 128U) >> 4), 1U)] *
                      rtb_ShiftArithmetic3_m) >> 15;

    /* Sum: '<S8>/Sum2' incorporates:
     *  Delay: '<S8>/Delay2'
     */
    rtb_ShiftArithmetic_lo = rtb_UnitDelay3 - rtDW.Delay2_DSTATE_h;

    /* Abs: '<S8>/Abs' */
    if (rtb_ShiftArithmetic_lo < 0) {
      rtb_ShiftArithmetic_lo = -rtb_ShiftArithmetic_lo;
    }

    /* End of Abs: '<S8>/Abs' */

    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S8>/Obs_Theta'
     *  SignalConversion generated from: '<S8>/Theta'
     */
    rtDW.Merge = rtb_UnitDelay6;

    /* Chart: '<S8>/正负偏置' incorporates:
     *  DataStoreRead: '<S8>/Data Store Read'
     */
    if (rtDW.temporalCounter_i1_e < 1023U) {
      rtDW.temporalCounter_i1_e++;
    }

    if (rtDW.is_active_c12_FOC_PointModel == 0U) {
      rtDW.is_active_c12_FOC_PointModel = 1U;
      rtDW.is_c12_FOC_PointModel = IN_Down;
      rtDW.temporalCounter_i1_e = 0U;
      if (rtDW.NScomp_Ud_Point <= MIN_int32_T) {
        rtDW.output = MAX_int32_T;
      } else {
        rtDW.output = -rtDW.NScomp_Ud_Point;
      }
    } else {
      switch (rtDW.is_c12_FOC_PointModel) {
       case IN_Down:
        if (rtDW.temporalCounter_i1_e >= 540U) {
          rtDW.is_c12_FOC_PointModel = IN_Zero;
          rtDW.temporalCounter_i1_e = 0U;
          rtDW.output = 0;
        } else if (rtDW.NScomp_Ud_Point <= MIN_int32_T) {
          rtDW.output = MAX_int32_T;
        } else {
          rtDW.output = -rtDW.NScomp_Ud_Point;
        }
        break;

       case IN_Up:
        if (rtDW.temporalCounter_i1_e >= 540U) {
          rtDW.is_c12_FOC_PointModel = IN_Zero1;
          rtDW.output = 0;
        } else {
          rtDW.output = rtDW.NScomp_Ud_Point;
        }
        break;

       case IN_Zero:
        if (rtDW.temporalCounter_i1_e >= 360U) {
          rtDW.is_c12_FOC_PointModel = IN_Up;
          rtDW.temporalCounter_i1_e = 0U;
          rtDW.output = rtDW.NScomp_Ud_Point;
        } else {
          rtDW.output = 0;
        }
        break;

       default:
        /* case IN_Zero1: */
        rtDW.output = 0;
        break;
      }
    }

    /* End of Chart: '<S8>/正负偏置' */

    /* Signum: '<S8>/Sign' */
    if (rtDW.output < 0) {
      rtb_Sign_a = -1;
    } else {
      rtb_Sign_a = (rtDW.output > 0);
    }

    /* End of Signum: '<S8>/Sign' */

    /* Outputs for Enabled SubSystem: '<S8>/max' */
    max(rtb_Sign_a, rtb_ShiftArithmetic_lo, &rtDW.Sum_e, &rtDW.max_f);

    /* End of Outputs for SubSystem: '<S8>/max' */

    /* Outputs for Enabled SubSystem: '<S8>/min' */
    max(-rtb_Sign_a, rtb_ShiftArithmetic_lo, &rtDW.Sum_f, &rtDW.min);

    /* End of Outputs for SubSystem: '<S8>/min' */

    /* Sum: '<S8>/Sum' incorporates:
     *  UnaryMinus: '<S8>/Unary Minus'
     */
    rtDW.Sum = rtDW.Sum_e - rtDW.Sum_f;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S8>/Constant1'
     *  SignalConversion generated from: '<S8>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Update for Delay: '<S8>/Delay2' */
    rtDW.Delay2_DSTATE_h = rtb_UnitDelay3;

    /* End of Outputs for SubSystem: '<S1>/NS辨识' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S1>/标志位' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* Signum: '<S16>/Sign' */
    if (rtDW.Sum < 0) {
      rtDW.NS_Flag = -1;
    } else {
      rtDW.NS_Flag = (rtDW.Sum > 0);
    }

    /* End of Signum: '<S16>/Sign' */

    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S16>/Obs_Theta'
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    rtDW.Merge = rtDW.UnitDelay1_DSTATE_b;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S16>/Constant8'
     *  SignalConversion generated from: '<S16>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S16>/Constant4'
     *  SignalConversion generated from: '<S16>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/标志位' */
    break;

   case 4:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S18>/Delay1'
       *  Delay: '<S18>/Delay2'
       *  Delay: '<S70>/Delay'
       */
      rtDW.icLoad = true;
      rtDW.icLoad_c = true;
      rtDW.icLoad_f = true;

      /* End of InitializeConditions for SubSystem: '<S1>/观测器闭环//速度环' */

      /* SystemReset for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Chart: '<S18>/速度缓冲1'
       */
      rtDW.temporalCounter_i1 = 0U;
      rtDW.is_active_c9_FOC_PointModel = 0U;
      rtDW.is_c9_FOC_PointModel = IN_NO_ACTIVE_CHILD;

      /* End of SystemReset for SubSystem: '<S1>/观测器闭环//速度环' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S18>/Obs_Theta'
     *  UnitDelay: '<S1>/Unit Delay4'
     */
    rtDW.Merge = rtDW.UnitDelay4_DSTATE_f;

    /* Delay: '<S18>/Delay1' */
    if (rtDW.icLoad) {
      rtDW.Delay1_DSTATE = rtb_UnitDelay3;
    }

    /* Sum: '<S18>/Sum9' incorporates:
     *  Delay: '<S18>/Delay1'
     */
    rtb_ShiftArithmetic_lo -= rtDW.Delay1_DSTATE;

    /* Switch: '<S66>/Switch2' incorporates:
     *  Constant: '<S18>/Constant5'
     *  Constant: '<S18>/Constant8'
     *  RelationalOperator: '<S66>/LowerRelop1'
     *  RelationalOperator: '<S66>/UpperRelop'
     *  Switch: '<S66>/Switch'
     */
    if (rtb_ShiftArithmetic_lo > SPD_STEP) {
      rtb_ShiftArithmetic_lo = SPD_STEP;
    } else if (rtb_ShiftArithmetic_lo < -SPD_STEP) {
      /* Switch: '<S66>/Switch' incorporates:
       *  Constant: '<S18>/Constant5'
       */
      rtb_ShiftArithmetic_lo = -SPD_STEP;
    }

    /* Sum: '<S18>/Sum10' incorporates:
     *  Delay: '<S18>/Delay1'
     *  Switch: '<S66>/Switch2'
     */
    rtb_ShiftArithmetic_lo += rtDW.Delay1_DSTATE;

    /* Sum: '<S18>/Sum2' */
    rtb_Sum_pv = (int16_T)((int16_T)rtb_ShiftArithmetic_lo - (int16_T)
      rtb_UnitDelay3);

    /* ArithShift: '<S70>/Shift Arithmetic1' incorporates:
     *  ArithShift: '<S70>/Shift Arithmetic2'
     *  Constant: '<S70>/周期定点化适当放大2^n1'
     *  DataStoreRead: '<S70>/Data Store Read2'
     *  DataTypeConversion: '<S70>/Data Type Conversion'
     */
    rtb_ShiftArithmetic1 = ((int64_T)rtDW.Speed_Limit << 15) << ((int16_T)
      TS_POINT_GAIN);

    /* Delay: '<S70>/Delay' incorporates:
     *  ArithShift: '<S70>/Shift Arithmetic3'
     *  ArithShift: '<S70>/这个是缩小周期增益的1'
     *  Constant: '<S70>/周期定点化适当放大2^n2'
     *  DataTypeConversion: '<S70>/Data Type Conversion2'
     *  UnitDelay: '<S1>/Unit Delay2'
     */
    if (rtDW.icLoad_c) {
      rtDW.Delay_DSTATE = ((int64_T)rtDW.UnitDelay2_DSTATE << ((int16_T)
        TS_POINT_GAIN)) << 15;
    }

    /* Sum: '<S70>/Sum' incorporates:
     *  DataStoreRead: '<S18>/Data Store Read4'
     *  DataStoreRead: '<S70>/Data Store Read1'
     *  Delay: '<S70>/Delay'
     *  Product: '<S70>/Product1'
     *  Product: '<S70>/Product2'
     */
    rtb_Sum = rtDW.Ts_Point * rtb_Sum_pv * rtDW.Speed_Ki_Point
      + rtDW.Delay_DSTATE;

    /* Switch: '<S71>/Switch2' incorporates:
     *  ArithShift: '<S70>/Shift Arithmetic1'
     *  RelationalOperator: '<S71>/LowerRelop1'
     *  Sum: '<S70>/Sum'
     */
    if (rtb_Sum <= rtb_ShiftArithmetic1) {
      /* Gain: '<S70>/Gain' */
      rtb_ShiftArithmetic1 = -rtb_ShiftArithmetic1;

      /* Switch: '<S71>/Switch' incorporates:
       *  Gain: '<S70>/Gain'
       *  RelationalOperator: '<S71>/UpperRelop'
       *  Switch: '<S71>/Switch2'
       */
      if (rtb_Sum >= rtb_ShiftArithmetic1) {
        rtb_ShiftArithmetic1 = rtb_Sum;
      }

      /* End of Switch: '<S71>/Switch' */
    }

    /* End of Switch: '<S71>/Switch2' */

    /* Sum: '<S65>/Sum' incorporates:
     *  ArithShift: '<S70>/Shift Arithmetic'
     *  ArithShift: '<S70>/这个是缩小周期增益的'
     *  Constant: '<S70>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S18>/Data Store Read3'
     *  DataTypeConversion: '<S70>/Data Type Conversion1'
     *  Product: '<S65>/Product2'
     *  Switch: '<S71>/Switch2'
     */
    rtb_Sign_a = (int32_T)((rtb_ShiftArithmetic1 >> 15) >> ((int16_T)
      TS_POINT_GAIN)) + rtb_Sum_pv * rtDW.Speed_Kp_Point;

    /* Switch: '<S69>/Switch2' incorporates:
     *  DataStoreRead: '<S65>/Data Store Read3'
     *  Gain: '<S65>/Gain'
     *  RelationalOperator: '<S69>/LowerRelop1'
     *  RelationalOperator: '<S69>/UpperRelop'
     *  Switch: '<S69>/Switch'
     */
    if (rtb_Sign_a > rtDW.Speed_Limit) {
      rtb_Sign_a = rtDW.Speed_Limit;
    } else if (rtb_Sign_a < -rtDW.Speed_Limit) {
      /* Switch: '<S69>/Switch' incorporates:
       *  Gain: '<S65>/Gain'
       */
      rtb_Sign_a = -rtDW.Speed_Limit;
    }

    /* End of Switch: '<S69>/Switch2' */

    /* Delay: '<S18>/Delay2' incorporates:
     *  DataStoreRead: '<S18>/Data Store Read1'
     */
    if (rtDW.icLoad_f) {
      rtDW.Delay2_DSTATE_a = rtDW.HFI_Id_Point;
    }

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataTypeConversion: '<S18>/Data Type Conversion'
     *  SignalConversion generated from: '<S18>/Iq'
     *  Sum: '<S18>/Sum'
     */
    rtDW.Merge1 = (int16_T)rtb_Sign_a;

    /* Relay: '<S18>/Relay' */
    rtDW.Relay_Mode = ((rtb_UnitDelay3 >= 1700) || ((rtb_UnitDelay3 > 1300) &&
      rtDW.Relay_Mode));

    /* Switch: '<S18>/Switch' incorporates:
     *  Constant: '<S18>/Constant10'
     *  DataStoreRead: '<S18>/Data Store Read2'
     *  Relay: '<S18>/Relay'
     */
    if (rtDW.Relay_Mode) {
      rtb_Sum_pv = 0;
    } else {
      rtb_Sum_pv = rtDW.HFI_Id_Point;
    }

    /* Sum: '<S18>/Sum4' incorporates:
     *  Delay: '<S18>/Delay2'
     *  Switch: '<S18>/Switch'
     */
    rtb_Sum_pv -= rtDW.Delay2_DSTATE_a;

    /* Saturate: '<S18>/Saturation' */
    if (rtb_Sum_pv > 16384) {
      rtb_Sum_pv = 16384;
    } else if (rtb_Sum_pv < -1) {
      rtb_Sum_pv = -1;
    }

    /* Sum: '<S18>/Sum3' incorporates:
     *  Delay: '<S18>/Delay2'
     *  Saturate: '<S18>/Saturation'
     */
    rtb_Sum_pv += rtDW.Delay2_DSTATE_a;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Sum: '<S18>/Sum6'
     */
    rtDW.Merge2 = rtb_Sum_pv;

    /* Chart: '<S18>/速度缓冲1' */
    if (rtDW.temporalCounter_i1 < 4095U) {
      rtDW.temporalCounter_i1++;
    }

    if (rtDW.is_active_c9_FOC_PointModel == 0U) {
      rtDW.is_active_c9_FOC_PointModel = 1U;
      rtDW.is_c9_FOC_PointModel = IN_Open_Loop;
      rtDW.temporalCounter_i1 = 0U;
    } else if ((rtDW.is_c9_FOC_PointModel == IN_Open_Loop) &&
               (rtDW.temporalCounter_i1 >= 3600U)) {
      rtDW.is_c9_FOC_PointModel = IN_SPD_Loop;
    } else {
      /* case IN_SPD_Loop: */
    }

    /* End of Chart: '<S18>/速度缓冲1' */

    /* Update for Delay: '<S18>/Delay1' */
    rtDW.icLoad = false;
    rtDW.Delay1_DSTATE = rtb_ShiftArithmetic_lo;

    /* Update for Delay: '<S70>/Delay' incorporates:
     *  Switch: '<S71>/Switch2'
     */
    rtDW.icLoad_c = false;
    rtDW.Delay_DSTATE = rtb_ShiftArithmetic1;

    /* Update for Delay: '<S18>/Delay2' */
    rtDW.icLoad_f = false;
    rtDW.Delay2_DSTATE_a = rtb_Sum_pv;

    /* End of Outputs for SubSystem: '<S1>/观测器闭环//速度环' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* Lookup_n-D: '<S13>/Sin' incorporates:
   *  ArithShift: '<S13>/Shift Arithmetic1'
   *  Constant: '<S13>/Constant1'
   *  Sum: '<S13>/Sum1'
   */
  rtb_Sum_pv = rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    (uint16_T)(rtDW.Merge + 128U) >> 4), 1U)];

  /* Lookup_n-D: '<S13>/Sin1' incorporates:
   *  ArithShift: '<S13>/Shift Arithmetic'
   *  Constant: '<S13>/Constant3'
   *  Sum: '<S13>/Sum2'
   */
  rtb_Sin1 = rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    (uint16_T)(rtDW.Merge + 16512U) >> 4), 1U)];

  /* ArithShift: '<S10>/Shift Arithmetic1' incorporates:
   *  Lookup_n-D: '<S13>/Sin'
   *  Lookup_n-D: '<S13>/Sin1'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Sum: '<S10>/Add1'
   */
  rtb_UnitDelay3 = (rtb_ShiftArithmetic3_m * rtb_Sin1 - rtb_ShiftArithmetic_f *
                    rtb_Sum_pv) >> 15;

  /* ArithShift: '<S10>/Shift Arithmetic4' incorporates:
   *  Delay: '<S10>/Delay3'
   *  Sum: '<S10>/Sum3'
   */
  rtb_ShiftArithmetic_lo = (rtb_UnitDelay3 + rtDW.Delay3_DSTATE) >> 1;

  /* Outputs for Enabled SubSystem: '<S1>/idq_Controller' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* RelationalOperator: '<S1>/Relational Operator2' incorporates:
   *  Constant: '<S1>/Constant1'
   */
  if (rtDW.Motor_State > 3) {
    if (!rtDW.idq_Controller_MODE) {
      /* InitializeConditions for UnitDelay: '<S12>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE_j = 0;

      /* InitializeConditions for UnitDelay: '<S55>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S57>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_n = 0;

      /* InitializeConditions for UnitDelay: '<S12>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_d = 0;

      /* InitializeConditions for UnitDelay: '<S60>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_d = 0;
      rtDW.idq_Controller_MODE = true;
    }

    /* Sum: '<S12>/Sum5' incorporates:
     *  Sum: '<S12>/Sum13'
     *  UnitDelay: '<S12>/Unit Delay4'
     *  UnitDelay: '<S55>/Unit Delay5'
     */
    rtb_Sum5_f = (int16_T)((int16_T)(rtDW.UnitDelay5_DSTATE + rtDW.Merge2) -
      rtDW.UnitDelay4_DSTATE_j);

    /* Switch: '<S54>/Switch2' incorporates:
     *  Constant: '<S12>/Constant1'
     *  Constant: '<S12>/Constant2'
     *  RelationalOperator: '<S54>/LowerRelop1'
     *  RelationalOperator: '<S54>/UpperRelop'
     *  Switch: '<S54>/Switch'
     */
    if (rtb_Sum5_f > ((int16_T)CURR_STEP)) {
      rtb_Sum5_f = ((int16_T)CURR_STEP);
    } else if (rtb_Sum5_f < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S54>/Switch' incorporates:
       *  Constant: '<S12>/Constant1'
       */
      rtb_Sum5_f = (int16_T)-((int16_T)CURR_STEP);
    }

    /* Sum: '<S12>/Sum6' incorporates:
     *  Switch: '<S54>/Switch2'
     *  UnitDelay: '<S12>/Unit Delay4'
     */
    rtb_Sum5_f += rtDW.UnitDelay4_DSTATE_j;

    /* Sum: '<S12>/Sum1' incorporates:
     *  ArithShift: '<S46>/Shift Arithmetic1'
     *  Gain: '<S46>/Gain1'
     */
    rtb_Min1 = rtb_Sum5_f - ((23166 * rtb_Sum1_o) >> 15);

    /* ArithShift: '<S57>/Shift Arithmetic' incorporates:
     *  ArithShift: '<S60>/Shift Arithmetic'
     *  Constant: '<S57>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S12>/Data Store Read5'
     */
    rtb_Sum_aj = rtDW.Curr_Ki_Point >> ((int16_T)TS_POINT_GAIN);

    /* Sum: '<S57>/Sum' incorporates:
     *  ArithShift: '<S57>/Shift Arithmetic'
     *  ArithShift: '<S57>/这个是缩小周期增益的'
     *  DataStoreRead: '<S57>/Data Store Read1'
     *  Product: '<S57>/Product1'
     *  Product: '<S57>/Product2'
     *  UnitDelay: '<S57>/Unit Delay'
     */
    rtb_Sign_a = ((rtDW.Ts_Point * rtb_Min1) >> 15) * rtb_Sum_aj +
      rtDW.UnitDelay_DSTATE_n;

    /* Switch: '<S58>/Switch2' incorporates:
     *  DataStoreRead: '<S57>/Data Store Read3'
     *  Gain: '<S57>/Gain'
     *  RelationalOperator: '<S58>/LowerRelop1'
     *  RelationalOperator: '<S58>/UpperRelop'
     *  Switch: '<S58>/Switch'
     */
    if (rtb_Sign_a > rtDW.Curr_Limit) {
      rtb_Sign_a = rtDW.Curr_Limit;
    } else if (rtb_Sign_a < -rtDW.Curr_Limit) {
      /* Switch: '<S58>/Switch' incorporates:
       *  Gain: '<S57>/Gain'
       */
      rtb_Sign_a = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S58>/Switch2' */

    /* Sum: '<S51>/Sum' incorporates:
     *  DataStoreRead: '<S12>/Data Store Read2'
     *  Product: '<S51>/Product2'
     */
    rtb_Min1 = rtb_Min1 * rtDW.Curr_Kp_Point + rtb_Sign_a;

    /* Switch: '<S56>/Switch2' incorporates:
     *  DataStoreRead: '<S51>/Data Store Read3'
     *  RelationalOperator: '<S56>/LowerRelop1'
     */
    if (rtb_Min1 > rtDW.Curr_Limit) {
      rtb_Uq = rtDW.Curr_Limit;
    } else {
      /* Gain: '<S51>/Gain' */
      rtb_Uq = -rtDW.Curr_Limit;

      /* Switch: '<S56>/Switch' incorporates:
       *  Gain: '<S51>/Gain'
       *  RelationalOperator: '<S56>/UpperRelop'
       */
      if (rtb_Min1 >= -rtDW.Curr_Limit) {
        rtb_Uq = rtb_Min1;
      }

      /* End of Switch: '<S56>/Switch' */
    }

    /* End of Switch: '<S56>/Switch2' */

    /* Sum: '<S12>/Sum9' incorporates:
     *  Sum: '<S12>/Sum14'
     *  UnitDelay: '<S12>/Unit Delay3'
     */
    rtb_Sum12 = (int16_T)(rtDW.Merge1 - rtDW.UnitDelay3_DSTATE_d);

    /* Switch: '<S53>/Switch2' incorporates:
     *  Constant: '<S12>/Constant3'
     *  Constant: '<S12>/Constant8'
     *  RelationalOperator: '<S53>/LowerRelop1'
     *  RelationalOperator: '<S53>/UpperRelop'
     *  Switch: '<S53>/Switch'
     */
    if (rtb_Sum12 > ((int16_T)CURR_STEP)) {
      rtb_Sum12 = ((int16_T)CURR_STEP);
    } else if (rtb_Sum12 < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S53>/Switch' incorporates:
       *  Constant: '<S12>/Constant3'
       */
      rtb_Sum12 = (int16_T)-((int16_T)CURR_STEP);
    }

    /* End of Switch: '<S53>/Switch2' */

    /* Sum: '<S12>/Sum10' incorporates:
     *  UnitDelay: '<S12>/Unit Delay3'
     */
    rtb_Sum10_i = (int16_T)(rtb_Sum12 + rtDW.UnitDelay3_DSTATE_d);

    /* Sum: '<S12>/Sum8' */
    rtb_Min1 = rtb_Sum10_i - rtb_ShiftArithmetic_lo;

    /* Sum: '<S60>/Sum' incorporates:
     *  ArithShift: '<S60>/这个是缩小周期增益的'
     *  DataStoreRead: '<S60>/Data Store Read1'
     *  Product: '<S60>/Product1'
     *  Product: '<S60>/Product2'
     *  UnitDelay: '<S60>/Unit Delay'
     */
    rtb_Sum_aj = ((rtDW.Ts_Point * rtb_Min1) >> 15) * rtb_Sum_aj +
      rtDW.UnitDelay_DSTATE_d;

    /* Switch: '<S61>/Switch2' incorporates:
     *  DataStoreRead: '<S60>/Data Store Read3'
     *  RelationalOperator: '<S61>/LowerRelop1'
     */
    if (rtb_Sum_aj > rtDW.Curr_Limit) {
      rtb_Gain_k = rtDW.Curr_Limit;
    } else {
      /* Gain: '<S60>/Gain' */
      rtb_Gain_k = -rtDW.Curr_Limit;

      /* Switch: '<S61>/Switch' incorporates:
       *  Gain: '<S60>/Gain'
       *  RelationalOperator: '<S61>/UpperRelop'
       */
      if (rtb_Sum_aj >= -rtDW.Curr_Limit) {
        rtb_Gain_k = rtb_Sum_aj;
      }

      /* End of Switch: '<S61>/Switch' */
    }

    /* End of Switch: '<S61>/Switch2' */

    /* Sum: '<S52>/Sum' incorporates:
     *  DataStoreRead: '<S12>/Data Store Read6'
     *  Product: '<S52>/Product2'
     */
    rtb_Min1 = rtb_Min1 * rtDW.Curr_Kp_Point + rtb_Gain_k;

    /* Switch: '<S59>/Switch2' incorporates:
     *  DataStoreRead: '<S52>/Data Store Read3'
     *  RelationalOperator: '<S59>/LowerRelop1'
     */
    if (rtb_Min1 > rtDW.Curr_Limit) {
      rtb_Sum_aj = rtDW.Curr_Limit;
    } else {
      /* Gain: '<S52>/Gain' */
      rtb_Sum_aj = -rtDW.Curr_Limit;

      /* Switch: '<S59>/Switch' incorporates:
       *  Gain: '<S52>/Gain'
       *  RelationalOperator: '<S59>/UpperRelop'
       */
      if (rtb_Min1 >= -rtDW.Curr_Limit) {
        rtb_Sum_aj = rtb_Min1;
      }

      /* End of Switch: '<S59>/Switch' */
    }

    /* End of Switch: '<S59>/Switch2' */

    /* ArithShift: '<S12>/Shift Arithmetic4' incorporates:
     *  ArithShift: '<S12>/Shift Arithmetic2'
     *  Product: '<S34>/Product'
     */
    rtDW.Ud = rtb_Uq >> 16;

    /* ArithShift: '<S12>/Shift Arithmetic5' incorporates:
     *  ArithShift: '<S12>/Shift Arithmetic3'
     *  Sum: '<S34>/Sum8'
     */
    rtDW.Uq = rtb_Sum_aj >> 16;

    /* Sum: '<S55>/Sum12' incorporates:
     *  Constant: '<S55>/Constant'
     *  DataTypeConversion: '<S55>/Data Type Conversion5'
     *  DataTypeConversion: '<S55>/Data Type Conversion6'
     *  Math: '<S55>/Square2'
     *  Math: '<S55>/Square3'
     *  Sqrt: '<S55>/Sqrt1'
     *  Sum: '<S55>/Sum11'
     */
    rtb_Sum12 = (int16_T)(14746 - rt_sqrt_Us32_Ys16_Is32__s((int16_T)rtDW.Ud *
      (int16_T)rtDW.Ud + (int16_T)rtDW.Uq * (int16_T)rtDW.Uq));

    /* Update for UnitDelay: '<S12>/Unit Delay4' */
    rtDW.UnitDelay4_DSTATE_j = rtb_Sum5_f;

    /* Switch: '<S62>/FixPt Switch' */
    if (rtb_Sum12 > 0) {
      /* Update for UnitDelay: '<S55>/Unit Delay5' incorporates:
       *  Constant: '<S62>/Constant'
       */
      rtDW.UnitDelay5_DSTATE = 0;
    } else {
      /* Update for UnitDelay: '<S55>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE = rtb_Sum12;
    }

    /* End of Switch: '<S62>/FixPt Switch' */

    /* Update for UnitDelay: '<S57>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_n = rtb_Sign_a;

    /* Update for UnitDelay: '<S12>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_d = rtb_Sum10_i;

    /* Update for UnitDelay: '<S60>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_d = rtb_Gain_k;
  } else if (rtDW.idq_Controller_MODE) {
    /* Disable for ArithShift: '<S12>/Shift Arithmetic4' incorporates:
     *  Outport: '<S12>/Ud'
     */
    rtDW.Ud = 0;

    /* Disable for ArithShift: '<S12>/Shift Arithmetic5' incorporates:
     *  Outport: '<S12>/Uq'
     */
    rtDW.Uq = 0;
    rtDW.idq_Controller_MODE = false;
  }

  /* End of RelationalOperator: '<S1>/Relational Operator2' */
  /* End of Outputs for SubSystem: '<S1>/idq_Controller' */

  /* Sum: '<S1>/Sum5' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  rtb_Min1 = ((rtb_PulseGenerator1 << 10) + rtDW.Ud) + rtDW.output;

  /* ArithShift: '<S2>/Shift Arithmetic' incorporates:
   *  Lookup_n-D: '<S13>/Sin'
   *  Lookup_n-D: '<S13>/Sin1'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add'
   */
  rtb_Sign_a = (rtb_Min1 * rtb_Sin1 - rtDW.Uq * rtb_Sum_pv) >> 15;

  /* ArithShift: '<S2>/Shift Arithmetic1' incorporates:
   *  Lookup_n-D: '<S13>/Sin'
   *  Lookup_n-D: '<S13>/Sin1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add1'
   */
  rtb_Min1 = (rtb_Min1 * rtb_Sum_pv + rtDW.Uq * rtb_Sin1) >> 15;

  /* Outputs for Enabled SubSystem: '<S1>/Observers' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtb_RelationalOperator) {
    if (!rtDW.Observers_MODE) {
      /* InitializeConditions for UnitDelay: '<S9>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_j = 0;

      /* InitializeConditions for Delay: '<S33>/Delay4' */
      rtDW.Delay4_DSTATE[0] = 0;
      rtDW.Delay4_DSTATE[1] = 0;
      rtDW.Delay4_DSTATE[2] = 0;
      rtDW.Delay4_DSTATE[3] = 0;

      /* InitializeConditions for UnitDelay: '<S34>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_dt = 0;

      /* InitializeConditions for UnitDelay: '<S45>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_e = 0;

      /* InitializeConditions for UnitDelay: '<S44>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_g = 0;

      /* SystemReset for Atomic SubSystem: '<S9>/HFI' */
      /* InitializeConditions for Delay: '<S29>/Delay' */
      rtDW.Delay_DSTATE_g = 0;

      /* InitializeConditions for Delay: '<S29>/Delay1' */
      rtDW.Delay1_DSTATE_e = 0;

      /* End of SystemReset for SubSystem: '<S9>/HFI' */

      /* SystemReset for Atomic SubSystem: '<S9>/SMO' */
      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay2' */
      rtDW.UnitDelay2_DSTATE_i = 0;

      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_l = 0;

      /* InitializeConditions for UnitDelay: '<S41>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay6' */
      rtDW.UnitDelay6_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S42>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE_m = 0;

      /* End of SystemReset for SubSystem: '<S9>/SMO' */

      /* SystemReset for Chart: '<S9>/obs_chart' */
      rtDW.temporalCounter_i1_h = 0U;
      rtDW.is_active_c3_FOC_PointModel = 0U;
      rtDW.is_c3_FOC_PointModel = IN_NO_ACTIVE_CHILD;

      /* SystemReset for Atomic SubSystem: '<S9>/PLL' */
      /* InitializeConditions for UnitDelay: '<S30>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_l = 0U;

      /* InitializeConditions for UnitDelay: '<S39>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_p = 0;

      /* InitializeConditions for UnitDelay: '<S37>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_m = 0;

      /* End of SystemReset for SubSystem: '<S9>/PLL' */

      /* SystemReset for Atomic SubSystem: '<S34>/LPF' */
      /* InitializeConditions for UnitDelay: '<S43>/Unit Delay9' */
      rtDW.UnitDelay9_DSTATE = 0;

      /* End of SystemReset for SubSystem: '<S34>/LPF' */
      rtDW.Observers_MODE = true;
    }

    /* Abs: '<S9>/Abs' incorporates:
     *  UnitDelay: '<S9>/Unit Delay'
     */
    if (rtDW.UnitDelay_DSTATE_j < 0) {
      rtb_Uq = -rtDW.UnitDelay_DSTATE_j;
    } else {
      rtb_Uq = rtDW.UnitDelay_DSTATE_j;
    }

    /* End of Abs: '<S9>/Abs' */

    /* Outputs for Atomic SubSystem: '<S9>/HFI' */
    /* ArithShift: '<S29>/Shift Arithmetic5' incorporates:
     *  Delay: '<S29>/Delay1'
     *  Sum: '<S29>/Sum3'
     */
    rtb_Sum_aj = (rtb_ShiftArithmetic_f - rtDW.Delay1_DSTATE_e) >> 1;

    /* ArithShift: '<S29>/Shift Arithmetic4' incorporates:
     *  Delay: '<S29>/Delay'
     *  Sum: '<S29>/Sum2'
     */
    rtb_Gain_k = (rtb_ShiftArithmetic3_m - rtDW.Delay_DSTATE_g) >> 1;

    /* Update for Delay: '<S29>/Delay' */
    rtDW.Delay_DSTATE_g = rtb_ShiftArithmetic3_m;

    /* Update for Delay: '<S29>/Delay1' */
    rtDW.Delay1_DSTATE_e = rtb_ShiftArithmetic_f;

    /* End of Outputs for SubSystem: '<S9>/HFI' */

    /* Signum: '<S9>/Sign' incorporates:
     *  UnitDelay: '<S9>/Unit Delay'
     */
    if (rtDW.UnitDelay_DSTATE_j < 0) {
      rtb_Sign_h = -1;
    } else {
      rtb_Sign_h = (rtDW.UnitDelay_DSTATE_j > 0);
    }

    /* End of Signum: '<S9>/Sign' */

    /* Outputs for Atomic SubSystem: '<S9>/SMO' */
    /* Sum: '<S31>/Sum7' incorporates:
     *  ArithShift: '<S31>/Shift Arithmetic4'
     *  ArithShift: '<S31>/Shift Arithmetic6'
     *  ArithShift: '<S31>/Shift Arithmetic9'
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  DataStoreRead: '<S31>/Data Store Read13'
     *  DataStoreRead: '<S31>/Data Store Read15'
     *  DataStoreRead: '<S31>/Data Store Read16'
     *  Delay: '<S33>/Delay4'
     *  Product: '<S31>/Product10'
     *  Product: '<S31>/Product11'
     *  Product: '<S31>/Product12'
     *  SignalConversion generated from: '<S33>/Delay4'
     *  Sum: '<S31>/Sum2'
     *  Sum: '<S33>/Sum4'
     *  UnitDelay: '<S31>/Unit Delay2'
     *  UnitDelay: '<S31>/Unit Delay3'
     */
    rtb_Sum7 = (((((((rtb_Min1 + rtDW.Delay4_DSTATE[2]) >> 1) * rtDW.Obs_VtoI) >>
                   8) - rtDW.UnitDelay2_DSTATE_i) * rtDW.SMO_Gain2) >> 15) +
      ((rtDW.SMO_Gain1 * rtDW.UnitDelay3_DSTATE_l) >> 15);

    /* Sum: '<S31>/Sum4' incorporates:
     *  ArithShift: '<S31>/Shift Arithmetic3'
     *  ArithShift: '<S31>/Shift Arithmetic5'
     *  ArithShift: '<S31>/Shift Arithmetic8'
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  DataStoreRead: '<S31>/Data Store Read11'
     *  DataStoreRead: '<S31>/Data Store Read7'
     *  DataStoreRead: '<S31>/Data Store Read8'
     *  Delay: '<S33>/Delay4'
     *  Product: '<S31>/Product5'
     *  Product: '<S31>/Product6'
     *  Product: '<S31>/Product8'
     *  SignalConversion generated from: '<S33>/Delay4'
     *  Sum: '<S31>/Sum3'
     *  Sum: '<S33>/Sum4'
     *  UnitDelay: '<S31>/Unit Delay4'
     *  UnitDelay: '<S31>/Unit Delay6'
     */
    rtb_Sum4_p = (((((((rtb_Sign_a + rtDW.Delay4_DSTATE[0]) >> 1) *
                      rtDW.Obs_VtoI) >> 8) - rtDW.UnitDelay4_DSTATE) *
                   rtDW.SMO_Gain2) >> 15) + ((rtDW.UnitDelay6_DSTATE *
      rtDW.SMO_Gain1) >> 15);

    /* Sum: '<S41>/Sum2' incorporates:
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  ArithShift: '<S41>/Shift Arithmetic4'
     *  DataStoreRead: '<S31>/Data Store Read14'
     *  DataStoreRead: '<S41>/Data Store Read1'
     *  Delay: '<S33>/Delay4'
     *  Product: '<S31>/Product9'
     *  Product: '<S41>/Product1'
     *  SignalConversion generated from: '<S33>/Delay4'
     *  Sum: '<S31>/Sum5'
     *  Sum: '<S33>/Sum4'
     *  Sum: '<S41>/Sum1'
     *  UnitDelay: '<S41>/Unit Delay1'
     */
    rtb_Sum2_e = ((((rtb_Sum4_p - ((rtb_ShiftArithmetic_f + rtDW.Delay4_DSTATE[1])
      >> 1)) * rtDW.SMO_K - rtDW.UnitDelay1_DSTATE) * rtDW.LPF_FRQ_Point) >> 4)
      + rtDW.UnitDelay1_DSTATE;

    /* Sum: '<S42>/Sum2' incorporates:
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  ArithShift: '<S42>/Shift Arithmetic4'
     *  DataStoreRead: '<S31>/Data Store Read12'
     *  DataStoreRead: '<S42>/Data Store Read1'
     *  Delay: '<S33>/Delay4'
     *  Product: '<S31>/Product13'
     *  Product: '<S42>/Product1'
     *  SignalConversion generated from: '<S33>/Delay4'
     *  Sum: '<S31>/Sum8'
     *  Sum: '<S33>/Sum4'
     *  Sum: '<S42>/Sum1'
     *  UnitDelay: '<S42>/Unit Delay1'
     */
    rtb_Sum2_pv = ((((rtb_Sum7 - ((rtb_ShiftArithmetic3_m + rtDW.Delay4_DSTATE[3])
      >> 1)) * rtDW.SMO_K - rtDW.UnitDelay1_DSTATE_m) * rtDW.LPF_FRQ_Point) >> 4)
      + rtDW.UnitDelay1_DSTATE_m;

    /* Update for UnitDelay: '<S31>/Unit Delay2' incorporates:
     *  Sum: '<S31>/Sum'
     */
    rtDW.UnitDelay2_DSTATE_i = rtb_Sum2_pv;

    /* Update for UnitDelay: '<S31>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_l = rtb_Sum7;

    /* Update for UnitDelay: '<S41>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE = rtb_Sum2_e;

    /* Update for UnitDelay: '<S31>/Unit Delay6' */
    rtDW.UnitDelay6_DSTATE = rtb_Sum4_p;

    /* Update for UnitDelay: '<S31>/Unit Delay4' incorporates:
     *  Sum: '<S31>/Sum9'
     */
    rtDW.UnitDelay4_DSTATE = rtb_Sum2_e;

    /* Update for UnitDelay: '<S42>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m = rtb_Sum2_pv;

    /* SignalConversion generated from: '<S32>/ SFunction ' incorporates:
     *  Chart: '<S9>/obs_chart'
     *  Product: '<S31>/Product25'
     *  Product: '<S31>/Product26'
     */
    rtb_Sum7 = rtb_Sum2_e * rtb_Sign_h;
    rtb_Sign_h *= rtb_Sum2_pv;

    /* End of Outputs for SubSystem: '<S9>/SMO' */

    /* Outputs for Atomic SubSystem: '<S9>/HFI' */
    /* SignalConversion generated from: '<S32>/ SFunction ' incorporates:
     *  Chart: '<S9>/obs_chart'
     *  Product: '<S29>/Product4'
     *  Product: '<S29>/Product5'
     */
    rtb_Gain_k *= rtb_PulseGenerator1;
    rtb_Sum2_pv = rtb_PulseGenerator1 * rtb_Sum_aj;

    /* End of Outputs for SubSystem: '<S9>/HFI' */

    /* Chart: '<S9>/obs_chart' */
    if (rtDW.temporalCounter_i1_h < 511U) {
      rtDW.temporalCounter_i1_h++;
    }

    if (rtDW.is_active_c3_FOC_PointModel == 0U) {
      rtDW.is_active_c3_FOC_PointModel = 1U;
      rtDW.is_c3_FOC_PointModel = IN_Begin;
      rtDW.temporalCounter_i1_h = 0U;
      rtb_Gain_k >>= 1;
      rtb_Sum7 >>= 1;
      rtb_Sum2_pv >>= 1;
      rtb_Sign_h >>= 1;
    } else {
      switch (rtDW.is_c3_FOC_PointModel) {
       case IN_Begin:
        if ((rtDW.temporalCounter_i1_h >= 360U) && (rtb_Uq < OBS_SPD)) {
          rtDW.is_c3_FOC_PointModel = IN_HFI;
          rtb_Sum7 = 0;
          rtb_Sign_h = 0;
        } else {
          if (OBS_SPD > 1073741823) {
            rtb_Sum_aj = MAX_int32_T;
          } else if (OBS_SPD <= -1073741824) {
            rtb_Sum_aj = MIN_int32_T;
          } else {
            rtb_Sum_aj = OBS_SPD << 1;
          }

          if ((rtDW.temporalCounter_i1_h >= 360U) && (rtb_Uq > rtb_Sum_aj)) {
            rtDW.is_c3_FOC_PointModel = IN_SMO;
            rtb_Gain_k = 0;
            rtb_Sum2_pv = 0;
          } else {
            rtb_Gain_k >>= 1;
            rtb_Sum7 >>= 1;
            rtb_Sum2_pv >>= 1;
            rtb_Sign_h >>= 1;
          }
        }
        break;

       case IN_HFI:
        if (OBS_SPD > 1073741823) {
          rtb_Sum_aj = MAX_int32_T;
        } else if (OBS_SPD <= -1073741824) {
          rtb_Sum_aj = MIN_int32_T;
        } else {
          rtb_Sum_aj = OBS_SPD << 1;
        }

        if (rtb_Uq > rtb_Sum_aj) {
          rtDW.is_c3_FOC_PointModel = IN_HFI_SMO2;
          rtDW.temporalCounter_i1_h = 0U;
          rtb_Gain_k >>= 1;
          rtb_Sum2_pv >>= 1;
        } else {
          rtb_Sum7 = 0;
          rtb_Sign_h = 0;
        }
        break;

       case IN_HFI_SMO1:
        if (rtDW.temporalCounter_i1_h >= 360U) {
          rtDW.is_c3_FOC_PointModel = IN_HFI;
          rtb_Sum7 = 0;
          rtb_Sign_h = 0;
        } else {
          rtb_Sum7 >>= 1;
          rtb_Sign_h >>= 1;
        }
        break;

       case IN_HFI_SMO2:
        if (rtDW.temporalCounter_i1_h >= 360U) {
          rtDW.is_c3_FOC_PointModel = IN_SMO;
          rtb_Gain_k = 0;
          rtb_Sum2_pv = 0;
        } else {
          rtb_Gain_k >>= 1;
          rtb_Sum2_pv >>= 1;
        }
        break;

       default:
        /* case IN_SMO: */
        if (rtb_Uq < OBS_SPD) {
          rtDW.is_c3_FOC_PointModel = IN_HFI_SMO1;
          rtDW.temporalCounter_i1_h = 0U;
          rtb_Sum7 >>= 1;
          rtb_Sign_h >>= 1;
        } else {
          rtb_Gain_k = 0;
          rtb_Sum2_pv = 0;
        }
        break;
      }
    }

    /* Outputs for Atomic SubSystem: '<S9>/PLL' */
    /* Sum: '<S30>/Sum4' incorporates:
     *  ArithShift: '<S30>/Shift Arithmetic7'
     *  ArithShift: '<S30>/Shift Arithmetic8'
     *  ArithShift: '<S36>/Shift Arithmetic'
     *  ArithShift: '<S36>/Shift Arithmetic1'
     *  Constant: '<S36>/Constant1'
     *  Constant: '<S36>/Constant3'
     *  Lookup_n-D: '<S36>/Sin'
     *  Lookup_n-D: '<S36>/Sin1'
     *  Product: '<S30>/Product3'
     *  Product: '<S30>/Product4'
     *  Sum: '<S36>/Sum1'
     *  Sum: '<S36>/Sum2'
     *  Sum: '<S9>/Sum'
     *  Sum: '<S9>/Sum2'
     *  UnitDelay: '<S30>/Unit Delay'
     */
    rtb_Sum_aj = ((rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)((uint32_T)
      (uint16_T)(rtDW.UnitDelay_DSTATE_l + 16512U) >> 4), 1U)] * (rtb_Gain_k -
      rtb_Sum7)) >> 15) - ((rtConstP.pooled13[plook_u32u16_even0ckag((uint16_T)
      ((uint32_T)(uint16_T)(rtDW.UnitDelay_DSTATE_l + 128U) >> 4), 1U)] *
      (rtb_Sign_h + rtb_Sum2_pv)) >> 15);

    /* Sum: '<S39>/Sum' incorporates:
     *  ArithShift: '<S39>/Shift Arithmetic'
     *  ArithShift: '<S39>/这个是缩小周期增益的'
     *  Constant: '<S39>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S30>/Data Store Read8'
     *  DataStoreRead: '<S39>/Data Store Read1'
     *  Product: '<S39>/Product1'
     *  Product: '<S39>/Product2'
     *  UnitDelay: '<S39>/Unit Delay'
     */
    rtb_Uq = ((rtDW.Ts_Point * rtb_Sum_aj) >> 15) * (rtDW.PLL_Ki >> ((int16_T)
      TS_POINT_GAIN)) + rtDW.UnitDelay_DSTATE_p;

    /* Switch: '<S40>/Switch2' incorporates:
     *  DataStoreRead: '<S39>/Data Store Read3'
     *  RelationalOperator: '<S40>/LowerRelop1'
     */
    if (rtb_Uq > rtDW.PLL_Limit) {
      rtb_Gain_k = rtDW.PLL_Limit;
    } else {
      /* Gain: '<S39>/Gain' */
      rtb_Gain_k = -rtDW.PLL_Limit;

      /* Switch: '<S40>/Switch' incorporates:
       *  Gain: '<S39>/Gain'
       *  RelationalOperator: '<S40>/UpperRelop'
       */
      if (rtb_Uq >= -rtDW.PLL_Limit) {
        rtb_Gain_k = rtb_Uq;
      }

      /* End of Switch: '<S40>/Switch' */
    }

    /* End of Switch: '<S40>/Switch2' */

    /* Sum: '<S35>/Sum' incorporates:
     *  DataStoreRead: '<S30>/Data Store Read7'
     *  Product: '<S35>/Product2'
     */
    rtb_Uq = rtb_Sum_aj * rtDW.PLL_Kp + rtb_Gain_k;

    /* Switch: '<S38>/Switch2' incorporates:
     *  DataStoreRead: '<S35>/Data Store Read3'
     *  RelationalOperator: '<S38>/LowerRelop1'
     */
    if (rtb_Uq > rtDW.PLL_Limit) {
      rtb_Sum_aj = rtDW.PLL_Limit;
    } else {
      /* Gain: '<S35>/Gain' */
      rtb_Sum_aj = -rtDW.PLL_Limit;

      /* Switch: '<S38>/Switch' incorporates:
       *  Gain: '<S35>/Gain'
       *  RelationalOperator: '<S38>/UpperRelop'
       */
      if (rtb_Uq >= -rtDW.PLL_Limit) {
        rtb_Sum_aj = rtb_Uq;
      }

      /* End of Switch: '<S38>/Switch' */
    }

    /* End of Switch: '<S38>/Switch2' */

    /* ArithShift: '<S37>/这个是缩小周期增益的' incorporates:
     *  ArithShift: '<S37>/Shift Arithmetic'
     *  Constant: '<S37>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S37>/Data Store Read1'
     *  Product: '<S37>/Product2'
     *  Sum: '<S34>/Sum8'
     */
    rtb_Uq = ((rtb_Sum_aj >> ((int16_T)TS_POINT_GAIN)) * rtDW.Ts_Point) >> 15;

    /* Sum: '<S37>/Sum' incorporates:
     *  Product: '<S37>/Product1'
     *  UnitDelay: '<S37>/Unit Delay'
     */
    rtb_Sign_h = rtb_Uq + rtDW.UnitDelay_DSTATE_m;

    /* Switch: '<S30>/Switch' incorporates:
     *  Constant: '<S30>/Constant'
     *  Constant: '<S30>/Constant1'
     *  DataStoreRead: '<S30>/Data Store Read1'
     */
    if (rtDW.NS_Flag >= 0) {
      rtb_UnitDelay6 = 0U;
    } else {
      rtb_UnitDelay6 = 32767U;
    }

    /* Outport: '<Root>/Obs_Theta' incorporates:
     *  DataTypeConversion: '<S30>/Data Type Conversion8'
     *  Sum: '<S30>/Sum1'
     *  Sum: '<S37>/Sum1'
     *  Switch: '<S30>/Switch'
     */
    rtY.Obs_Theta = (uint16_T)((uint32_T)(uint16_T)(rtb_Sign_h + rtb_Uq) -
      rtb_UnitDelay6);

    /* Update for UnitDelay: '<S30>/Unit Delay' incorporates:
     *  Outport: '<Root>/Obs_Theta'
     */
    rtDW.UnitDelay_DSTATE_l = rtY.Obs_Theta;

    /* Update for UnitDelay: '<S39>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_p = rtb_Gain_k;

    /* Update for UnitDelay: '<S37>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_m = rtb_Sign_h;

    /* End of Outputs for SubSystem: '<S9>/PLL' */

    /* Sum: '<S45>/Sum' incorporates:
     *  ArithShift: '<S45>/Shift Arithmetic'
     *  Constant: '<S34>/Constant13'
     *  Constant: '<S45>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S45>/Data Store Read1'
     *  Product: '<S34>/Product1'
     *  Product: '<S45>/Product2'
     *  UnitDelay: '<S34>/Unit Delay'
     *  UnitDelay: '<S45>/Unit Delay'
     */
    rtb_Uq = ((942 * rtDW.UnitDelay_DSTATE_dt) >> ((int16_T)TS_POINT_GAIN)) *
      rtDW.Ts_Point + rtDW.UnitDelay_DSTATE_e;

    /* ArithShift: '<S45>/这个是缩小周期增益的' incorporates:
     *  Sum: '<S45>/Sum'
     */
    rtb_Gain_k = rtb_Uq >> 15;

    /* Outputs for Atomic SubSystem: '<S34>/LPF' */
    /* Outport: '<Root>/Obs_Spd' incorporates:
     *  ArithShift: '<S43>/Shift Arithmetic9'
     *  Product: '<S43>/Product10'
     *  Product: '<S43>/Product11'
     *  Sum: '<S43>/Sum11'
     *  UnitDelay: '<S43>/Unit Delay9'
     */
    rtY.Obs_Spd = ((rtDW.UnitDelay9_DSTATE << 3) + (rtb_Gain_k << 3)) >> 4;

    /* Update for UnitDelay: '<S43>/Unit Delay9' incorporates:
     *  Outport: '<Root>/Obs_Spd'
     */
    rtDW.UnitDelay9_DSTATE = rtY.Obs_Spd;

    /* End of Outputs for SubSystem: '<S34>/LPF' */

    /* Outputs for Atomic SubSystem: '<S9>/PLL' */
    /* Sum: '<S44>/Sum' incorporates:
     *  ArithShift: '<S30>/Shift Arithmetic13'
     *  ArithShift: '<S44>/Shift Arithmetic'
     *  ArithShift: '<S9>/Shift Arithmetic4'
     *  Constant: '<S34>/Constant13'
     *  Constant: '<S44>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S44>/Data Store Read1'
     *  DataStoreRead: '<S9>/Data Store Read1'
     *  Product: '<S34>/Product'
     *  Product: '<S44>/Product2'
     *  Product: '<S9>/Product4'
     *  Sum: '<S34>/Sum5'
     *  Sum: '<S34>/Sum8'
     *  UnitDelay: '<S34>/Unit Delay'
     *  UnitDelay: '<S44>/Unit Delay'
     */
    rtb_Sum_aj = (((((((rtb_Sum_aj >> 16) * rtDW.Hz_RPM) >> 8) -
                     rtDW.UnitDelay_DSTATE_dt) - rtb_Gain_k) * 942) >> ((int16_T)
      TS_POINT_GAIN)) * rtDW.Ts_Point + rtDW.UnitDelay_DSTATE_g;

    /* End of Outputs for SubSystem: '<S9>/PLL' */

    /* Update for UnitDelay: '<S9>/Unit Delay' incorporates:
     *  Outport: '<Root>/Obs_Spd'
     */
    rtDW.UnitDelay_DSTATE_j = rtY.Obs_Spd;

    /* Update for Delay: '<S33>/Delay4' incorporates:
     *  SignalConversion generated from: '<S33>/Delay4'
     */
    rtDW.Delay4_DSTATE[0] = rtb_Sign_a;
    rtDW.Delay4_DSTATE[1] = rtb_ShiftArithmetic_f;
    rtDW.Delay4_DSTATE[2] = rtb_Min1;
    rtDW.Delay4_DSTATE[3] = rtb_ShiftArithmetic3_m;

    /* Update for UnitDelay: '<S34>/Unit Delay' incorporates:
     *  ArithShift: '<S44>/这个是缩小周期增益的'
     *  Sum: '<S44>/Sum'
     */
    rtDW.UnitDelay_DSTATE_dt = rtb_Sum_aj >> 15;

    /* Update for UnitDelay: '<S45>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_e = rtb_Uq;

    /* Update for UnitDelay: '<S44>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_g = rtb_Sum_aj;
  } else if (rtDW.Observers_MODE) {
    /* Disable for Outport: '<Root>/Obs_Spd' incorporates:
     *  Outport: '<S9>/Obs_Spd'
     */
    rtY.Obs_Spd = 0;

    /* Disable for Outport: '<Root>/Obs_Theta' incorporates:
     *  Outport: '<S9>/Obs_Theta'
     */
    rtY.Obs_Theta = 0U;
    rtDW.Observers_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/Observers' */

  /* ArithShift: '<S10>/Shift Arithmetic' incorporates:
   *  Lookup_n-D: '<S13>/Sin'
   *  Lookup_n-D: '<S13>/Sin1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Sum: '<S10>/Add2'
   */
  rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic_f * rtb_Sin1 +
    rtb_ShiftArithmetic3_m * rtb_Sum_pv) >> 15;

  /* Sum: '<S47>/Sum' incorporates:
   *  ArithShift: '<S10>/Shift Arithmetic3'
   *  ArithShift: '<S46>/Shift Arithmetic'
   *  ArithShift: '<S47>/Shift Arithmetic'
   *  Constant: '<S46>/Constant13'
   *  Constant: '<S47>/周期定点化适当放大2^n'
   *  DataStoreRead: '<S47>/Data Store Read1'
   *  Delay: '<S10>/Delay2'
   *  Gain: '<S46>/Gain'
   *  Product: '<S46>/Product'
   *  Product: '<S47>/Product2'
   *  Sum: '<S10>/Sum2'
   *  Sum: '<S46>/Sum5'
   *  Sum: '<S46>/Sum8'
   *  UnitDelay: '<S46>/Unit Delay'
   *  UnitDelay: '<S47>/Unit Delay'
   */
  rtb_Sum1_o = ((((((((rtb_ShiftArithmetic_f + rtDW.Delay2_DSTATE) >> 1) -
                     rtDW.UnitDelay_DSTATE_k) * 46333) >> 15) - rtb_Sum1_o) *
                 1571) >> ((int16_T)TS_POINT_GAIN)) * rtDW.Ts_Point
    + rtDW.UnitDelay_DSTATE_f;

  /* ArithShift: '<S49>/Shift Arithmetic' incorporates:
   *  Gain: '<S49>/Gain1'
   */
  rtb_ShiftArithmetic3_m = (28377 * rtb_Min1) >> 15;

  /* ArithShift: '<S49>/Shift Arithmetic1' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic'
   */
  rtb_Min1 = rtb_Sign_a >> 1;

  /* ArithShift: '<S11>/Shift Arithmetic' incorporates:
   *  DataStoreRead: '<S11>/Data Store Read3'
   */
  rtb_PulseGenerator1 = (int16_T)(rtDW.PWM_TH >> 1);

  /* SignalConversion generated from: '<S11>/Sum' incorporates:
   *  Sum: '<S49>/Sum'
   *  Sum: '<S49>/Sum1'
   */
  rtb_Uq = rtb_ShiftArithmetic3_m - rtb_Min1;
  rtb_Sum_aj = -rtb_ShiftArithmetic3_m - rtb_Min1;

  /* MinMax: '<S50>/Min' incorporates:
   *  SignalConversion generated from: '<S11>/Sum'
   */
  if (rtb_Sign_a <= rtb_Uq) {
    rtb_ShiftArithmetic3_m = rtb_Sign_a;
  } else {
    rtb_ShiftArithmetic3_m = rtb_Uq;
  }

  /* MinMax: '<S50>/Min1' incorporates:
   *  MinMax: '<S50>/Min'
   *  SignalConversion generated from: '<S11>/Sum'
   */
  if (rtb_Sign_a >= rtb_Uq) {
    rtb_Min1 = rtb_Sign_a;
  } else {
    rtb_Min1 = rtb_Uq;
  }

  /* MinMax: '<S50>/Min' */
  if (rtb_ShiftArithmetic3_m > rtb_Sum_aj) {
    rtb_ShiftArithmetic3_m = rtb_Sum_aj;
  }

  /* MinMax: '<S50>/Min1' incorporates:
   *  MinMax: '<S50>/Min'
   */
  if (rtb_Min1 < rtb_Sum_aj) {
    rtb_Min1 = rtb_Sum_aj;
  }

  /* UnaryMinus: '<S50>/Unary Minus' incorporates:
   *  ArithShift: '<S50>/Shift Arithmetic'
   *  MinMax: '<S50>/Min'
   *  MinMax: '<S50>/Min1'
   *  Sum: '<S50>/Sum'
   */
  rtb_ShiftArithmetic3_m = -((rtb_ShiftArithmetic3_m + rtb_Min1) >> 1);

  /* Abs: '<S1>/Abs' incorporates:
   *  Outport: '<Root>/Obs_Spd'
   */
  if (rtY.Obs_Spd < 0) {
    /* Update for UnitDelay: '<S6>/Unit Delay' */
    rtDW.UnitDelay_DSTATE = -rtY.Obs_Spd;
  } else {
    /* Update for UnitDelay: '<S6>/Unit Delay' */
    rtDW.UnitDelay_DSTATE = rtY.Obs_Spd;
  }

  /* End of Abs: '<S1>/Abs' */

  /* Update for UnitDelay: '<S46>/Unit Delay' incorporates:
   *  ArithShift: '<S47>/这个是缩小周期增益的'
   *  Sum: '<S47>/Sum'
   */
  rtDW.UnitDelay_DSTATE_k = rtb_Sum1_o >> 15;

  /* Update for UnitDelay: '<S48>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_i = rtb_ShiftArithmetic9_e1;

  /* Update for UnitDelay: '<S1>/Unit Delay6' incorporates:
   *  Outport: '<Root>/Obs_Theta'
   */
  rtDW.UnitDelay6_DSTATE_b = rtY.Obs_Theta;

  /* Update for UnitDelay: '<S1>/Unit Delay4' incorporates:
   *  Outport: '<Root>/Obs_Theta'
   */
  rtDW.UnitDelay4_DSTATE_f = rtY.Obs_Theta;

  /* Update for UnitDelay: '<S1>/Unit Delay3' incorporates:
   *  Outport: '<Root>/Obs_Spd'
   */
  rtDW.UnitDelay3_DSTATE = rtY.Obs_Spd;

  /* Update for UnitDelay: '<S1>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE = rtb_ShiftArithmetic_lo;

  /* Update for UnitDelay: '<S1>/Unit Delay1' incorporates:
   *  Outport: '<Root>/Obs_Theta'
   */
  rtDW.UnitDelay1_DSTATE_b = rtY.Obs_Theta;

  /* Update for Delay: '<S10>/Delay3' */
  rtDW.Delay3_DSTATE = rtb_UnitDelay3;

  /* Update for Delay: '<S10>/Delay2' */
  rtDW.Delay2_DSTATE = rtb_ShiftArithmetic_f;

  /* Update for UnitDelay: '<S47>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_f = rtb_Sum1_o;

  /* Sum: '<S11>/Sum' incorporates:
   *  SignalConversion generated from: '<S11>/Sum'
   */
  rtb_ShiftArithmetic_f = rtb_Sign_a + rtb_ShiftArithmetic3_m;

  /* Saturate: '<S11>/Saturation' */
  if (rtb_ShiftArithmetic_f > 16384) {
    rtb_ShiftArithmetic_f = 16384;
  } else if (rtb_ShiftArithmetic_f < -16384) {
    rtb_ShiftArithmetic_f = -16384;
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S11>/默认除以32767电压'
   *  DataStoreRead: '<S11>/Data Store Read4'
   *  DataTypeConversion: '<S11>/Data Type Conversion'
   *  Product: '<S11>/Product'
   *  Saturate: '<S11>/Saturation'
   *  Sum: '<S11>/Sum1'
   */
  rtY.tABC[0] = (uint16_T)(rtb_PulseGenerator1 - ((rtb_ShiftArithmetic_f *
    rtDW.PWM_TH) >> 15));

  /* Sum: '<S11>/Sum' */
  rtb_ShiftArithmetic_f = rtb_Uq + rtb_ShiftArithmetic3_m;

  /* Saturate: '<S11>/Saturation' */
  if (rtb_ShiftArithmetic_f > 16384) {
    rtb_ShiftArithmetic_f = 16384;
  } else if (rtb_ShiftArithmetic_f < -16384) {
    rtb_ShiftArithmetic_f = -16384;
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S11>/默认除以32767电压'
   *  DataStoreRead: '<S11>/Data Store Read4'
   *  DataTypeConversion: '<S11>/Data Type Conversion'
   *  Product: '<S11>/Product'
   *  Saturate: '<S11>/Saturation'
   *  Sum: '<S11>/Sum1'
   */
  rtY.tABC[1] = (uint16_T)(rtb_PulseGenerator1 - ((rtb_ShiftArithmetic_f *
    rtDW.PWM_TH) >> 15));

  /* Sum: '<S11>/Sum' */
  rtb_ShiftArithmetic_f = rtb_Sum_aj + rtb_ShiftArithmetic3_m;

  /* Saturate: '<S11>/Saturation' */
  if (rtb_ShiftArithmetic_f > 16384) {
    rtb_ShiftArithmetic_f = 16384;
  } else if (rtb_ShiftArithmetic_f < -16384) {
    rtb_ShiftArithmetic_f = -16384;
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S11>/默认除以32767电压'
   *  DataStoreRead: '<S11>/Data Store Read4'
   *  DataTypeConversion: '<S11>/Data Type Conversion'
   *  Product: '<S11>/Product'
   *  Saturate: '<S11>/Saturation'
   *  Sum: '<S11>/Sum1'
   */
  rtY.tABC[2] = (uint16_T)(rtb_PulseGenerator1 - ((rtb_ShiftArithmetic_f *
    rtDW.PWM_TH) >> 15));

  /* End of Outputs for SubSystem: '<Root>/FOC_PointModel' */
}

/* Model initialize function */
void FOC_PointModel_initialize(void)
{
  {
    real_T rtb_ShiftArithmetic4;
    real_T u;
    real_T v;
    real32_T rtb_ShiftArithmetic9;
    real32_T u_0;
    real32_T v_0;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_PointModel' */
    /* Start for SwitchCase: '<S1>/Switch Case' */
    rtDW.SwitchCase_ActiveSubsystem = -1;

    /* SystemInitialize for Enabled SubSystem: '<S5>/闭环错误判断' */
    /* Start for If: '<S21>/If1' */
    rtDW.If1_ActiveSubsystem = -1;

    /* End of SystemInitialize for SubSystem: '<S5>/闭环错误判断' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/观测器闭环//速度环' */
    /* InitializeConditions for Delay: '<S18>/Delay1' */
    rtDW.icLoad = true;

    /* InitializeConditions for Delay: '<S70>/Delay' */
    rtDW.icLoad_c = true;

    /* InitializeConditions for Delay: '<S18>/Delay2' */
    rtDW.icLoad_f = true;

    /* End of SystemInitialize for SubSystem: '<S1>/观测器闭环//速度环' */

    /* Outputs for Atomic SubSystem: '<S1>/初始化模块' */
    /* ArithShift: '<S15>/Shift Arithmetic26' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic'
     *  Constant: '<S15>/Constant18'
     *  Constant: '<S15>/周期定点化适当放大2^n'
     */
    u = ldexp(ldexp(1.0 / FOC_FRQ, 15), ((int16_T)TS_POINT_GAIN));

    /* DataTypeConversion: '<S15>/Data Type Conversion6' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write7'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.Ts_Point = (int16_T)floor(u + 0.5);
      } else {
        rtDW.Ts_Point = 0;
      }
    } else {
      rtDW.Ts_Point = (int16_T)u;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion6' */

    /* ArithShift: '<S15>/Shift Arithmetic25' incorporates:
     *  Constant: '<S15>/ADC量程*母线电压分压倍数//定义的最大电压值'
     *  Constant: '<S15>/Constant16'
     *  Constant: '<S15>/电压采集定点化适当放大2^n'
     *  Product: '<S15>/Divide3'
     */
    u_0 = ldexpf(ADC_REF * UDC_GAIN / UDC, ((int16_T)UDC_POINT_GAIN));

    /* DataTypeConversion: '<S15>/Data Type Conversion5' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write6'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Voltage_Conversion = (int16_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Voltage_Conversion = 0;
      }
    } else {
      rtDW.Voltage_Conversion = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion5' */

    /* ArithShift: '<S15>/Shift Arithmetic24' incorporates:
     *  Constant: '<S15>/ADC量程//放大器倍数//定义的最大电流//采样电流'
     *  Constant: '<S15>/电流采集定点化适当放大2^n'
     */
    u_0 = ldexpf(ADC_REF / AMP_GAIN / IMAX / RS_HUNT, ((int16_T)CURR_POINT_GAIN));

    /* DataTypeConversion: '<S15>/Data Type Conversion4' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write5'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Conversion = (int16_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Conversion = 0;
      }
    } else {
      rtDW.Curr_Conversion = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion4' */

    /* DataTypeConversion: '<S15>/Data Type Conversion35' incorporates:
     *  Constant: '<S15>/Constant'
     *  DataStoreWrite: '<S15>/Data Store Write1'
     */
    v_0 = fabsf(UDC);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Uout_Max = (int16_T)floorf(UDC + 0.5F);
      } else {
        rtDW.Uout_Max = 0;
      }
    } else {
      rtDW.Uout_Max = (int16_T)UDC;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion35' */

    /* Product: '<S15>/Divide7' incorporates:
     *  Constant: '<S15>/Constant20'
     *  Constant: '<S15>/Constant21'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ / MOTOR_LS;

    /* ArithShift: '<S15>/Shift Arithmetic3' incorporates:
     *  Constant: '<S15>/Constant1'
     *  Constant: '<S15>/Constant15'
     *  Product: '<S15>/Product5'
     *  Sum: '<S15>/Sum'
     */
    u = ldexp(1.0 - MOTOR_RS * rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion9' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write10'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain1 = (int32_T)floor(u + 0.5);
      } else {
        rtDW.SMO_Gain1 = 0;
      }
    } else {
      rtDW.SMO_Gain1 = (int32_T)u;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion9' */

    /* ArithShift: '<S15>/Shift Arithmetic4' */
    u = ldexp(rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion10' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write11'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain2 = (int32_T)floor(u + 0.5);
      } else {
        rtDW.SMO_Gain2 = 0;
      }
    } else {
      rtDW.SMO_Gain2 = (int32_T)u;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion10' */

    /* Product: '<S15>/Divide' incorporates:
     *  Constant: '<S15>/Constant2'
     *  Constant: '<S15>/Constant71'
     *  Product: '<S15>/Divide1'
     */
    rtb_ShiftArithmetic9 = IMAX / UDC;

    /* ArithShift: '<S15>/Shift Arithmetic1' incorporates:
     *  Constant: '<S15>/Constant10'
     *  Constant: '<S15>/Constant9'
     *  Gain: '<S15>/Gain4'
     *  Product: '<S15>/Divide'
     *  Product: '<S15>/Product'
     *  Product: '<S15>/Product2'
     */
    u_0 = ldexpf(6.28318548F * CURR_WIDTH * MOTOR_LS * rtb_ShiftArithmetic9, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion11' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Kp_Point = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Kp_Point = 0;
      }
    } else {
      rtDW.Curr_Kp_Point = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion11' */

    /* ArithShift: '<S15>/Shift Arithmetic2' incorporates:
     *  Constant: '<S15>/Constant11'
     *  Constant: '<S15>/Constant12'
     *  Gain: '<S15>/Gain11'
     *  Product: '<S15>/Product1'
     *  Product: '<S15>/Product3'
     */
    u_0 = ldexpf(6.28318548F * CURR_WIDTH * MOTOR_RS * rtb_ShiftArithmetic9, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion1' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write2'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Ki_Point = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Ki_Point = 0;
      }
    } else {
      rtDW.Curr_Ki_Point = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion1' */

    /* ArithShift: '<S15>/Shift Arithmetic20' incorporates:
     *  Constant: '<S15>/Constant13'
     *  Constant: '<S15>/Constant69'
     *  Product: '<S15>/Divide5'
     */
    u_0 = ldexpf(UDC / IMAX, 8);

    /* DataTypeConversion: '<S15>/Data Type Conversion8' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write9'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Obs_VtoI = (int16_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Obs_VtoI = 0;
      }
    } else {
      rtDW.Obs_VtoI = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion8' */

    /* Saturate: '<S15>/Saturation1' incorporates:
     *  Constant: '<S15>/Constant14'
     */
    u_0 = -UDC / 2.0F;
    v_0 = UDC / 2.0F;
    if (NS_COMP_UD > v_0) {
      u_0 = v_0;
    } else if (NS_COMP_UD >= u_0) {
      u_0 = NS_COMP_UD;
    }

    /* DataTypeConversion: '<S15>/Data Type Conversion7' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic14'
     *  Constant: '<S15>/Constant17'
     *  DataStoreWrite: '<S15>/Data Store Write13'
     *  Product: '<S15>/Divide8'
     *  Saturate: '<S15>/Saturation1'
     */
    rtDW.NScomp_Ud_Point = (int32_T)ceilf(ldexpf(u_0 / UDC, 15));

    /* Product: '<S15>/Product6' incorporates:
     *  Constant: '<S15>/Constant19'
     *  Constant: '<S15>/Constant22'
     *  Gain: '<S15>/Gain1'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ * (6.28318548F * LPF_FRQ);

    /* DataTypeConversion: '<S15>/Data Type Conversion12' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic5'
     *  Constant: '<S15>/Constant24'
     *  DataStoreWrite: '<S15>/Data Store Write3'
     *  Product: '<S15>/Divide6'
     *  Sum: '<S15>/Sum1'
     */
    rtDW.LPF_FRQ_Point = (int16_T)ceil(ldexp(rtb_ShiftArithmetic4 /
      (rtb_ShiftArithmetic4 + 1.0), 4));

    /* Gain: '<S15>/Gain12' incorporates:
     *  Constant: '<S15>/Constant25'
     */
    rtb_ShiftArithmetic9 = 6.28318548F * PLL_WIDTH;

    /* Product: '<S15>/Product8' incorporates:
     *  Constant: '<S15>/Constant26'
     *  Gain: '<S15>/Gain13'
     */
    u_0 = 6.28318548F * PLL_WIDTH * rtb_ShiftArithmetic9;

    /* DataTypeConversion: '<S15>/Data Type Conversion14' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write14'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Ki = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.PLL_Ki = 0;
      }
    } else {
      rtDW.PLL_Ki = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion14' */

    /* Product: '<S15>/Product7' incorporates:
     *  Constant: '<S15>/Constant27'
     */
    u_0 = 2.0F * rtb_ShiftArithmetic9;

    /* DataTypeConversion: '<S15>/Data Type Conversion13' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write8'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Kp = (int16_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.PLL_Kp = 0;
      }
    } else {
      rtDW.PLL_Kp = (int16_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion13' */

    /* DataTypeConversion: '<S15>/Data Type Conversion15' incorporates:
     *  Constant: '<S15>/Constant28'
     *  Constant: '<S15>/Constant29'
     *  DataStoreWrite: '<S15>/Data Store Write15'
     *  Gain: '<S15>/Gain'
     *  Product: '<S15>/Product9'
     */
    rtDW.SMO_K = (int16_T)ceilf(SMOK_FRQ * MOTOR_FLUX * 6.28318548F);

    /* DataTypeConversion: '<S15>/Data Type Conversion16' incorporates:
     *  Constant: '<S15>/Constant30'
     *  DataStoreWrite: '<S15>/Data Store Write16'
     */
    v = fabs(FOC_FRQ);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.FOC_FRQ_Point = (int32_T)floor(FOC_FRQ + 0.5);
      } else {
        rtDW.FOC_FRQ_Point = 0;
      }
    } else {
      rtDW.FOC_FRQ_Point = (int32_T)FOC_FRQ;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion16' */

    /* Product: '<S15>/Product10' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic7'
     *  Constant: '<S15>/Constant32'
     */
    u_0 = PLL_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S15>/Data Type Conversion18' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write18'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Limit = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.PLL_Limit = 0;
      }
    } else {
      rtDW.PLL_Limit = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion18' */

    /* Product: '<S15>/Product11' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic8'
     *  Constant: '<S15>/Constant34'
     */
    u_0 = CURR_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S15>/Data Type Conversion19' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write19'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Limit = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Limit = 0;
      }
    } else {
      rtDW.Curr_Limit = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion19' */

    /* DataTypeConversion: '<S15>/Data Type Conversion23' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic12'
     *  Constant: '<S15>/Constant38'
     *  Constant: '<S15>/Constant49'
     *  DataStoreWrite: '<S15>/Data Store Write23'
     *  Product: '<S15>/Divide11'
     */
    rtDW.Hz_RPM = (int32_T)ceilf(ldexpf(60.0F / MOTOR_PN, 8));

    /* Product: '<S15>/Product13' incorporates:
     *  Constant: '<S15>/Constant41'
     *  Constant: '<S15>/Constant42'
     *  Constant: '<S15>/Constant43'
     */
    rtb_ShiftArithmetic9 = MOTOR_PN * MOTOR_FLUX * (1.5F * IMAX);

    /* DataTypeConversion: '<S15>/Data Type Conversion21' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic9'
     *  Constant: '<S15>/Constant39'
     *  Constant: '<S15>/Constant40'
     *  DataStoreWrite: '<S15>/Data Store Write20'
     *  Gain: '<S15>/Gain10'
     *  Product: '<S15>/Divide9'
     *  Product: '<S15>/Product12'
     */
    rtDW.Speed_Kp_Point = (int32_T)ceilf(ldexpf(6.28318548F * SPD_WIDTH *
      MOTOR_INERTIA / rtb_ShiftArithmetic9, 15));

    /* DataTypeConversion: '<S15>/Data Type Conversion20' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic21'
     *  Constant: '<S15>/Constant44'
     *  Constant: '<S15>/Constant45'
     *  Constant: '<S15>/Constant46'
     *  DataStoreWrite: '<S15>/Data Store Write21'
     *  Gain: '<S15>/Gain3'
     *  Gain: '<S15>/Gain9'
     *  Product: '<S15>/Divide10'
     *  Product: '<S15>/Product14'
     */
    rtDW.Speed_Ki_Point = (int32_T)ceilf(ldexpf(6.28318548F * SPD_WIDTH *
      (6.28318548F * SPD_WIDTH) * MOTOR_INERTIA * (1.0F / rtb_ShiftArithmetic9),
      15));

    /* Product: '<S15>/Product15' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic11'
     *  Constant: '<S15>/Constant47'
     *  Constant: '<S15>/Constant48'
     */
    u_0 = SPD_LIMIT * 32768.0F;

    /* DataTypeConversion: '<S15>/Data Type Conversion22' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write22'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Speed_Limit = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Speed_Limit = 0;
      }
    } else {
      rtDW.Speed_Limit = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion22' */

    /* Saturate: '<S15>/Saturation' incorporates:
     *  Constant: '<S15>/Constant5'
     */
    if (HFI_ID > IMAX) {
      u_0 = IMAX;
    } else if (HFI_ID < -IMAX) {
      u_0 = -IMAX;
    } else {
      u_0 = HFI_ID;
    }

    /* DataTypeConversion: '<S15>/Data Type Conversion2' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic10'
     *  Constant: '<S15>/Constant6'
     *  DataStoreWrite: '<S15>/Data Store Write12'
     *  Product: '<S15>/Divide4'
     *  Saturate: '<S15>/Saturation'
     */
    rtDW.HFI_Id_Point = (int16_T)ceilf(ldexpf(u_0 / IMAX, 15));

    /* Saturate: '<S15>/Saturation2' incorporates:
     *  Constant: '<S15>/Constant50'
     */
    if (CURR_OVER > IMAX) {
      u_0 = IMAX;
    } else if (CURR_OVER < -IMAX) {
      u_0 = -IMAX;
    } else {
      u_0 = CURR_OVER;
    }

    /* ArithShift: '<S15>/Shift Arithmetic13' incorporates:
     *  Gain: '<S15>/Gain5'
     *  Saturate: '<S15>/Saturation2'
     */
    u_0 = ldexpf(1.0F / IMAX * u_0, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion24' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write24'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Over = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Over = 0;
      }
    } else {
      rtDW.Curr_Over = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion24' */

    /* Saturate: '<S15>/Saturation4' incorporates:
     *  Constant: '<S15>/Constant58'
     */
    if (CURR_UNDER > IMAX) {
      u_0 = IMAX;
    } else if (CURR_UNDER < -IMAX) {
      u_0 = -IMAX;
    } else {
      u_0 = CURR_UNDER;
    }

    /* ArithShift: '<S15>/Shift Arithmetic17' incorporates:
     *  Gain: '<S15>/Gain7'
     *  Saturate: '<S15>/Saturation4'
     */
    u_0 = ldexpf(1.0F / IMAX * u_0, 15);

    /* DataTypeConversion: '<S15>/Data Type Conversion29' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write29'
     */
    v_0 = fabsf(u_0);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Under = (int32_T)floorf(u_0 + 0.5F);
      } else {
        rtDW.Curr_Under = 0;
      }
    } else {
      rtDW.Curr_Under = (int32_T)u_0;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion29' */

    /* Product: '<S15>/Divide2' incorporates:
     *  Constant: '<S15>/Constant7'
     *  Constant: '<S15>/Constant8'
     */
    u = PWM_FRQ / (FOC_FRQ * 2.0);

    /* DataTypeConversion: '<S15>/Data Type Conversion3' incorporates:
     *  DataStoreWrite: '<S15>/Data Store Write4'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.PWM_TH = (int16_T)floor(u + 0.5);
      } else {
        rtDW.PWM_TH = 0;
      }
    } else {
      rtDW.PWM_TH = (int16_T)u;
    }

    /* End of DataTypeConversion: '<S15>/Data Type Conversion3' */
    /* End of Outputs for SubSystem: '<S1>/初始化模块' */
    /* End of SystemInitialize for SubSystem: '<Root>/FOC_PointModel' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
