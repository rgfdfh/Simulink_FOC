/*
 * File: FOC_PointModel.c
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

#include "FOC_PointModel.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S1>/Chart' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_EndStage                    ((uint8_T)2U)
#define IN_IDLE                        ((uint8_T)3U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_OpenStage                   ((uint8_T)4U)
#define IN_RunStage                    ((uint8_T)5U)
#define IN_SlowOpen                    ((uint8_T)6U)
#define IN_SpeedupStage                ((uint8_T)7U)
#define IN_StopStage                   ((uint8_T)8U)

/* Named constants for Chart: '<S18>/速度缓冲' */
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
static uint32_T plook_u32u16_even0ckag(uint16_T u, uint16_T bp0);
static uint32_T plook_u32s32_even0ckag(int32_T u, int32_T bp0);
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

static uint32_T plook_u32s32_even0ckag(int32_T u, int32_T bp0)
{
  /* Prelookup - Index only
     Index Search method: 'even'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'on'
   */
  return (uint32_T)u - (uint32_T)bp0;
}

/* Model step function */
void FOC_PointModel_step(void)
{
  int32_T rtb_Gain;
  int32_T rtb_Gain_av;
  int32_T rtb_Gain_f;
  int32_T rtb_ShiftArithmetic1_o;
  int32_T rtb_ShiftArithmetic2;
  int32_T rtb_ShiftArithmetic3;
  int32_T rtb_ShiftArithmetic9_f;
  int32_T rtb_ShiftArithmetic_f;
  int32_T rtb_Sum2;
  int32_T rtb_Sum7;
  int16_T rtb_Bias_a;
  int16_T rtb_Saturation;
  int16_T rtb_Sum5_f;
  int16_T rtb_Sum_ix;
  int8_T rtAction;
  int8_T rtPrevAction;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_RelationalOperator;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_PointModel' */
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
  rtb_ShiftArithmetic1_o = (rtU.ib * rtDW.Curr_Conversion) >> ((int16_T)
    CURR_POINT_GAIN);

  /* ArithShift: '<S1>/Shift Arithmetic2' incorporates:
   *  Constant: '<S1>/电流采集适当放大系数2^n'
   *  DataStoreRead: '<S1>/电流采集定点化换算系数1'
   *  Inport: '<Root>/ic'
   *  Product: '<S1>/Product2'
   */
  rtb_ShiftArithmetic2 = (rtU.ic * rtDW.Curr_Conversion) >> ((int16_T)
    CURR_POINT_GAIN);

  /* Abs: '<S5>/Abs1' */
  if (rtb_ShiftArithmetic_f < 0) {
    rtb_Gain_f = -rtb_ShiftArithmetic_f;
  } else {
    rtb_Gain_f = rtb_ShiftArithmetic_f;
  }

  /* End of Abs: '<S5>/Abs1' */

  /* Abs: '<S5>/Abs2' */
  if (rtb_ShiftArithmetic1_o < 0) {
    rtb_Gain = -rtb_ShiftArithmetic1_o;
  } else {
    rtb_Gain = rtb_ShiftArithmetic1_o;
  }

  /* End of Abs: '<S5>/Abs2' */

  /* MinMax: '<S5>/Max' */
  if (rtb_Gain_f >= rtb_Gain) {
    rtb_Gain = rtb_Gain_f;
  }

  /* Abs: '<S5>/Abs3' */
  if (rtb_ShiftArithmetic2 < 0) {
    rtb_Gain_f = -rtb_ShiftArithmetic2;
  } else {
    rtb_Gain_f = rtb_ShiftArithmetic2;
  }

  /* End of Abs: '<S5>/Abs3' */

  /* MinMax: '<S5>/Max' */
  if (rtb_Gain >= rtb_Gain_f) {
    rtb_Gain_f = rtb_Gain;
  }

  /* Outputs for Atomic SubSystem: '<S5>/PLL_LPF1' */
  /* ArithShift: '<S20>/Shift Arithmetic9' incorporates:
   *  Constant: '<S20>/Constant1'
   *  MinMax: '<S5>/Max'
   *  Product: '<S20>/Product11'
   *  Sum: '<S20>/Sum11'
   *  UnitDelay: '<S20>/Unit Delay9'
   */
  rtb_ShiftArithmetic9_f = (rtDW.UnitDelay9_DSTATE_j * 15 + rtb_Gain_f) >> 4;

  /* Update for UnitDelay: '<S20>/Unit Delay9' */
  rtDW.UnitDelay9_DSTATE_j = rtb_ShiftArithmetic9_f;

  /* End of Outputs for SubSystem: '<S5>/PLL_LPF1' */

  /* RelationalOperator: '<S5>/Relational Operator' incorporates:
   *  DataStoreRead: '<S5>/Data Store Read3'
   */
  rtb_RelationalOperator = (rtDW.Curr_Over < rtb_ShiftArithmetic9_f);

  /* ArithShift: '<S1>/Shift Arithmetic3' incorporates:
   *  Constant: '<S1>/Constant33'
   *  DataStoreRead: '<S1>/Data Store Read'
   *  Inport: '<Root>/v_bus'
   *  Product: '<S1>/Product3'
   */
  rtb_ShiftArithmetic3 = (rtU.v_bus * rtDW.Voltage_Conversion) >> ((int16_T)
    UDC_POINT_GAIN);

  /* Outputs for Enabled SubSystem: '<S5>/闭环错误判断' incorporates:
   *  EnablePort: '<S21>/Enable'
   */
  /* RelationalOperator: '<S5>/Relational Operator1' incorporates:
   *  Constant: '<S5>/闭环是4'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  if (rtDW.Motor_State == 4) {
    if (!rtDW._MODE_p) {
      /* InitializeConditions for UnitDelay: '<S21>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_k = 0;
      rtDW._MODE_p = true;
    }

    /* Logic: '<S21>/Logical Operator' incorporates:
     *  ArithShift: '<S21>/Shift Arithmetic3'
     *  Constant: '<S21>/Constant'
     *  DataStoreRead: '<S21>/Data Store Read4'
     *  DataStoreRead: '<S21>/Data Store Read7'
     *  RelationalOperator: '<S21>/Relational Operator1'
     *  RelationalOperator: '<S21>/Relational Operator2'
     *  RelationalOperator: '<S21>/Relational Operator4'
     *  UnitDelay: '<S21>/Unit Delay'
     */
    rtb_LogicalOperator = ((rtb_ShiftArithmetic3 < 16384) ||
      (rtb_ShiftArithmetic9_f < rtDW.Curr_Under) || (rtDW.UnitDelay_DSTATE_k <
      (rtDW.Open_Hz >> 1)));

    /* If: '<S21>/If1' incorporates:
     *  DataTypeConversion: '<S21>/Data Type Conversion13'
     */
    rtPrevAction = rtDW.If1_ActiveSubsystem;
    rtAction = (int8_T)!rtb_LogicalOperator;
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
      rtb_ShiftArithmetic9_f = rtDW.UnitDelay2_DSTATE_a;

      /* Update for UnitDelay: '<S22>/Unit Delay2' incorporates:
       *  DataTypeConversion: '<S21>/Data Type Conversion12'
       *  Sum: '<S22>/Sum'
       */
      rtDW.UnitDelay2_DSTATE_a += rtb_LogicalOperator;

      /* End of Outputs for SubSystem: '<S21>/SUM' */
    } else {
      /* Outputs for IfAction SubSystem: '<S21>/SUM1' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
      /* SignalConversion generated from: '<S23>/out' incorporates:
       *  Constant: '<S23>/Constant'
       */
      rtb_ShiftArithmetic9_f = 0;

      /* End of Outputs for SubSystem: '<S21>/SUM1' */
    }

    /* End of If: '<S21>/If1' */

    /* Logic: '<S21>/OR1' incorporates:
     *  ArithShift: '<S21>/Shift Arithmetic1'
     *  DataStoreRead: '<S21>/Data Store Read'
     *  RelationalOperator: '<S21>/Relational Operator3'
     */
    rtDW.OR1 = (rtb_RelationalOperator || (rtb_ShiftArithmetic9_f >=
      (rtDW.FOC_FRQ_Point >> 1)));
  } else if (rtDW._MODE_p) {
    /* Disable for If: '<S21>/If1' */
    rtDW.If1_ActiveSubsystem = -1;
    rtDW._MODE_p = false;
  }

  /* End of RelationalOperator: '<S5>/Relational Operator1' */
  /* End of Outputs for SubSystem: '<S5>/闭环错误判断' */

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   *  Inport: '<Root>/Slow_OnOff'
   *  UnitDelay: '<S1>/Unit Delay2'
   */
  if (rtDW.temporalCounter_i1 < MAX_uint32_T) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c2_FOC_PointModel == 0U) {
    rtDW.is_active_c2_FOC_PointModel = 1U;
    rtDW.is_c2_FOC_PointModel = IN_IDLE;
    rtDW.temporalCounter_i1 = 0U;
  } else {
    switch (rtDW.is_c2_FOC_PointModel) {
     case IN_AlignStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtDW.temporalCounter_i1 >= 250U) {
        rtDW.is_c2_FOC_PointModel = IN_SpeedupStage;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        rtDW.Motor_State = 1U;
      }
      break;

     case IN_EndStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;

     case IN_IDLE:
      if ((rtU.Motor_OnOff == 1) && (rtDW.temporalCounter_i1 >= 250U)) {
        rtDW.is_c2_FOC_PointModel = IN_AlignStage;
        rtDW.temporalCounter_i1 = 0U;
      } else if ((rtU.Slow_OnOff == 1) && (rtDW.temporalCounter_i1 >= 250U)) {
        rtDW.is_c2_FOC_PointModel = IN_SlowOpen;
      } else {
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 0;
      }
      break;

     case IN_OpenStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else if ((rtDW.temporalCounter_i1 >= 6250U) && (rtDW.Abs < ((int16_T)
                   THETA_ERR_LIMIT))) {
        rtDW.is_c2_FOC_PointModel = IN_RunStage;
      } else if (rtb_RelationalOperator || (rtDW.temporalCounter_i1 >= 12500U))
      {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        rtDW.Motor_State = 3U;
      }
      break;

     case IN_RunStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtDW.OR1) {
        rtDW.is_c2_FOC_PointModel = IN_EndStage;
      } else {
        rtDW.Motor_State = 4U;
      }
      break;

     case IN_SlowOpen:
      if (rtU.Slow_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        rtDW.Motor_State = 5U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 0;
      }
      break;

     case IN_SpeedupStage:
      if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtDW.temporalCounter_i1 >= (uint32_T)ceil(OPEN_TIME / 4.0E-5 -
                  4.0000000000000006E-13)) {
        rtDW.is_c2_FOC_PointModel = IN_OpenStage;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        rtDW.Motor_State = 2U;
      }
      break;

     default:
      /* case IN_StopStage: */
      if (rtDW.temporalCounter_i1 >= 5000U) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* Sum: '<S17>/Sum' incorporates:
   *  ArithShift: '<S17>/Shift Arithmetic'
   *  Constant: '<S17>/Constant4'
   *  Constant: '<S17>/Constant5'
   *  Product: '<S17>/Product4'
   */
  rtb_Bias_a = (int16_T)((int16_T)(((int16_T)UDC) - 6) - (int16_T)((((int16_T)
    UDC) * rtb_ShiftArithmetic3) >> 15));

  /* Saturate: '<S17>/Saturation' */
  if (rtb_Bias_a > ((int16_T)UDC)) {
    rtb_Bias_a = ((int16_T)UDC);
  } else if (rtb_Bias_a < 0) {
    rtb_Bias_a = 0;
  }

  /* Sum: '<S17>/Sum2' incorporates:
   *  Constant: '<S17>/Constant1'
   *  Constant: '<S17>/Constant6'
   *  Product: '<S17>/Product'
   *  Saturate: '<S17>/Saturation'
   */
  rtb_ShiftArithmetic3 = SPD_MAX - ((int16_T)SPD_REDUCE) * rtb_Bias_a;

  /* Switch: '<S53>/Switch2' incorporates:
   *  Inport: '<Root>/Spd_Ref'
   *  RelationalOperator: '<S53>/LowerRelop1'
   */
  if (rtU.Spd_Ref <= rtb_ShiftArithmetic3) {
    /* Switch: '<S53>/Switch' incorporates:
     *  Constant: '<S17>/Constant7'
     *  RelationalOperator: '<S53>/UpperRelop'
     */
    if (rtU.Spd_Ref < SPD_MIN) {
      rtb_ShiftArithmetic3 = SPD_MIN;
    } else {
      rtb_ShiftArithmetic3 = rtU.Spd_Ref;
    }

    /* End of Switch: '<S53>/Switch' */
  }

  /* End of Switch: '<S53>/Switch2' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Constant: '<S18>/Constant8'
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

   case 5:
    rtAction = 5;
    break;
  }

  rtDW.SwitchCase_ActiveSubsystem = rtAction;
  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S1>/停止等待' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S11>/Constant2'
     *  SignalConversion generated from: '<S11>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S11>/Constant1'
     *  SignalConversion generated from: '<S11>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S11>/Constant3'
     *  SignalConversion generated from: '<S11>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/停止等待' */
    break;

   case 1:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/预定位' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S19>/Unit Delay4'
       */
      rtDW.UnitDelay4_DSTATE_d = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/预定位' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/预定位' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S19>/Constant3'
     *  SignalConversion generated from: '<S19>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S19>/Constant1'
     *  SignalConversion generated from: '<S19>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Bias: '<S19>/Bias' incorporates:
     *  UnitDelay: '<S19>/Unit Delay4'
     */
    rtb_Bias_a = (int16_T)(rtDW.UnitDelay4_DSTATE_d + 5);

    /* Switch: '<S60>/Switch2' incorporates:
     *  Bias: '<S19>/Bias'
     *  Constant: '<S19>/Constant2'
     *  DataStoreRead: '<S19>/Data Store Read3'
     *  RelationalOperator: '<S60>/LowerRelop1'
     *  RelationalOperator: '<S60>/UpperRelop'
     *  Switch: '<S60>/Switch'
     *  UnitDelay: '<S19>/Unit Delay4'
     */
    if ((int16_T)(rtDW.UnitDelay4_DSTATE_d + 5) > rtDW.Open_Iq_Point) {
      rtb_Bias_a = rtDW.Open_Iq_Point;
    } else if ((int16_T)(rtDW.UnitDelay4_DSTATE_d + 5) < 1) {
      /* Switch: '<S60>/Switch' incorporates:
       *  Constant: '<S19>/Constant2'
       */
      rtb_Bias_a = 1;
    }

    /* End of Switch: '<S60>/Switch2' */

    /* Merge: '<S1>/Merge2' incorporates:
     *  SignalConversion generated from: '<S19>/Id'
     */
    rtDW.Merge2 = rtb_Bias_a;

    /* Update for UnitDelay: '<S19>/Unit Delay4' */
    rtDW.UnitDelay4_DSTATE_d = rtb_Bias_a;

    /* End of Outputs for SubSystem: '<S1>/预定位' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/加速强拖' incorporates:
       *  ActionPort: '<S14>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S48>/Unit Delay'
       *  UnitDelay: '<S49>/Unit Delay'
       */
      rtDW.UnitDelay_DSTATE_b = 0;
      rtDW.UnitDelay_DSTATE_d = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/加速强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/加速强拖' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* Sum: '<S48>/Sum' incorporates:
     *  ArithShift: '<S47>/Shift Arithmetic'
     *  ArithShift: '<S48>/Shift Arithmetic'
     *  ArithShift: '<S48>/这个是缩小周期增益的'
     *  Constant: '<S48>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read1'
     *  DataStoreRead: '<S48>/Data Store Read1'
     *  DataTypeConversion: '<S47>/Data Type Conversion3'
     *  Product: '<S48>/Product2'
     *  UnitDelay: '<S48>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Acceleration << 16) >> ((int16_T)
      TS_POINT_GAIN)) * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_d;

    /* Sum: '<S49>/Sum' incorporates:
     *  ArithShift: '<S49>/Shift Arithmetic'
     *  ArithShift: '<S49>/这个是缩小周期增益的'
     *  Constant: '<S49>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S49>/Data Store Read1'
     *  Product: '<S49>/Product2'
     *  Sum: '<S48>/Sum'
     *  UnitDelay: '<S49>/Unit Delay'
     */
    rtb_ShiftArithmetic9_f = (((rtb_ShiftArithmetic3 >> ((int16_T)TS_POINT_GAIN))
      * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_b;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S47>/Data Type Conversion2'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic9_f;

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S14>/Data Store Read3'
     */
    rtDW.Merge1 = rtDW.Open_Iq_Point;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S14>/Constant1'
     *  SignalConversion generated from: '<S14>/Id'
     */
    rtDW.Merge2 = 0;

    /* Update for UnitDelay: '<S49>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_b = rtb_ShiftArithmetic9_f;

    /* Update for UnitDelay: '<S48>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_d = rtb_ShiftArithmetic3;

    /* End of Outputs for SubSystem: '<S1>/加速强拖' */
    break;

   case 3:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
       *  ActionPort: '<S15>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S51>/Delay'
       *  UnitDelay: '<S15>/Unit Delay1'
       */
      rtDW.icLoad_d = true;
      rtDW.UnitDelay1_DSTATE_g = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/恒速降力矩强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* Delay: '<S51>/Delay' incorporates:
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    if (rtDW.icLoad_d) {
      rtDW.Delay_DSTATE = rtDW.UnitDelay1_DSTATE_b;
    }

    /* Sum: '<S51>/Sum' incorporates:
     *  ArithShift: '<S15>/Shift Arithmetic'
     *  ArithShift: '<S51>/Shift Arithmetic'
     *  ArithShift: '<S51>/这个是缩小周期增益的'
     *  Constant: '<S51>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read6'
     *  DataStoreRead: '<S51>/Data Store Read1'
     *  DataTypeConversion: '<S15>/Data Type Conversion2'
     *  Delay: '<S51>/Delay'
     *  Product: '<S51>/Product2'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Hz << 16) >> ((int16_T)TS_POINT_GAIN)) *
      rtDW.Ts_Point) >> 15) + rtDW.Delay_DSTATE;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S15>/Data Type Conversion'
     *  SignalConversion generated from: '<S15>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic3;

    /* Merge: '<S1>/Merge2' incorporates:
     *  SignalConversion generated from: '<S15>/Id'
     *  UnitDelay: '<S15>/Unit Delay1'
     */
    rtDW.Merge2 = rtDW.UnitDelay1_DSTATE_g;

    /* Sum: '<S15>/Sum' incorporates:
     *  DataStoreRead: '<S15>/Data Store Read1'
     *  DataStoreRead: '<S15>/Data Store Read3'
     */
    rtb_Sum_ix = (int16_T)(rtDW.Open_Iq_Point - rtDW.Open_IqMin_Point);

    /* Switch: '<S50>/Switch2' incorporates:
     *  Bias: '<S15>/Bias'
     *  RelationalOperator: '<S50>/LowerRelop1'
     *  UnitDelay: '<S15>/Unit Delay1'
     */
    if ((int16_T)(rtDW.UnitDelay1_DSTATE_g + 1) <= rtb_Sum_ix) {
      /* Switch: '<S50>/Switch' incorporates:
       *  Constant: '<S15>/Constant7'
       *  RelationalOperator: '<S50>/UpperRelop'
       */
      if ((int16_T)(rtDW.UnitDelay1_DSTATE_g + 1) < 0) {
        rtb_Sum_ix = 0;
      } else {
        rtb_Sum_ix = (int16_T)(rtDW.UnitDelay1_DSTATE_g + 1);
      }

      /* End of Switch: '<S50>/Switch' */
    }

    /* End of Switch: '<S50>/Switch2' */

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S15>/Data Store Read2'
     *  Sum: '<S15>/Sum1'
     *  UnitDelay: '<S15>/Unit Delay1'
     */
    rtDW.Merge1 = (int16_T)(rtDW.Open_Iq_Point - rtDW.UnitDelay1_DSTATE_g);

    /* Update for Delay: '<S51>/Delay' */
    rtDW.icLoad_d = false;
    rtDW.Delay_DSTATE = rtb_ShiftArithmetic3;

    /* Update for UnitDelay: '<S15>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_g = rtb_Sum_ix;

    /* End of Outputs for SubSystem: '<S1>/恒速降力矩强拖' */
    break;

   case 4:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S18>/Delay'
       *  Delay: '<S18>/Delay1'
       *  UnitDelay: '<S18>/Unit Delay3'
       */
      rtDW.icLoad = true;
      rtDW.UnitDelay3_DSTATE_m = OPEN_SPD;
      rtDW.icLoad_l = true;

      /* End of InitializeConditions for SubSystem: '<S1>/观测器闭环//速度环' */

      /* SystemReset for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Chart: '<S18>/速度缓冲'
       */
      rtDW.temporalCounter_i1_m = 0U;
      rtDW.is_active_c48_FOC_PointModel = 0U;
      rtDW.is_c48_FOC_PointModel = IN_NO_ACTIVE_CHILD;
      rtDW.SPD_Ref = 0;

      /* End of SystemReset for SubSystem: '<S1>/观测器闭环//速度环' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S18>/Obs_Theta'
     *  UnitDelay: '<S1>/Unit Delay4'
     */
    rtDW.Merge = rtY.Obs_Theta;

    /* Delay: '<S18>/Delay' incorporates:
     *  DataStoreRead: '<S18>/Data Store Read8'
     *  UnaryMinus: '<S18>/Unary Minus1'
     */
    if (rtDW.icLoad) {
      rtDW.Delay_DSTATE_h = (int16_T)-rtDW.Open_IqMin_Point;
    }

    /* Switch: '<S56>/FixPt Switch' incorporates:
     *  Constant: '<S56>/Constant'
     *  Delay: '<S18>/Delay'
     */
    if (rtDW.Delay_DSTATE_h > 0) {
      rtb_Bias_a = 0;
    } else {
      rtb_Bias_a = rtDW.Delay_DSTATE_h;
    }

    /* End of Switch: '<S56>/FixPt Switch' */
    rtb_ShiftArithmetic9_f = ((int16_T)SPD_STEP);

    /* Chart: '<S18>/速度缓冲' incorporates:
     *  Constant: '<S18>/Constant12'
     *  Constant: '<S18>/Constant8'
     */
    if (rtDW.temporalCounter_i1_m < 2047U) {
      rtDW.temporalCounter_i1_m++;
    }

    if (rtDW.is_active_c48_FOC_PointModel == 0U) {
      rtDW.is_active_c48_FOC_PointModel = 1U;
      rtDW.is_c48_FOC_PointModel = IN_Open_Loop;
      rtDW.temporalCounter_i1_m = 0U;
    } else if (rtDW.is_c48_FOC_PointModel == IN_Open_Loop) {
      if (rtDW.temporalCounter_i1_m >= 1250U) {
        rtDW.is_c48_FOC_PointModel = IN_SPD_Loop;
      } else {
        rtDW.SPD_Ref = OPEN_SPD << 1;
      }
    } else {
      /* case IN_SPD_Loop: */
      rtDW.SPD_Ref = rtb_ShiftArithmetic3;
    }

    /* End of Chart: '<S18>/速度缓冲' */

    /* Sum: '<S18>/Sum9' incorporates:
     *  UnitDelay: '<S18>/Unit Delay3'
     */
    rtb_ShiftArithmetic3 = (int16_T)((int16_T)rtDW.SPD_Ref - (int16_T)
      rtDW.UnitDelay3_DSTATE_m);

    /* Switch: '<S55>/Switch2' incorporates:
     *  Constant: '<S18>/Constant8'
     *  RelationalOperator: '<S55>/LowerRelop1'
     */
    if (rtb_ShiftArithmetic3 <= ((int16_T)SPD_STEP)) {
      /* UnaryMinus: '<S18>/Unary Minus' incorporates:
       *  Constant: '<S18>/Constant5'
       */
      rtb_ShiftArithmetic9_f = -((int16_T)SPD_STEP);

      /* Switch: '<S55>/Switch' incorporates:
       *  Constant: '<S18>/Constant5'
       *  RelationalOperator: '<S55>/UpperRelop'
       *  UnaryMinus: '<S18>/Unary Minus'
       */
      if (rtb_ShiftArithmetic3 >= -((int16_T)SPD_STEP)) {
        rtb_ShiftArithmetic9_f = rtb_ShiftArithmetic3;
      }

      /* End of Switch: '<S55>/Switch' */
    }

    /* End of Switch: '<S55>/Switch2' */

    /* Sum: '<S18>/Sum10' incorporates:
     *  UnitDelay: '<S18>/Unit Delay3'
     */
    rtb_ShiftArithmetic3 = rtDW.UnitDelay3_DSTATE_m + rtb_ShiftArithmetic9_f;

    /* Sum: '<S18>/Sum2' incorporates:
     *  ArithShift: '<S18>/Shift Arithmetic'
     *  DataStoreRead: '<S18>/Data Store Read1'
     *  Product: '<S18>/Product'
     *  UnitDelay: '<S1>/Unit Delay3'
     */
    rtb_ShiftArithmetic9_f = (rtDW.Hz_RPM * rtY.Obs_Spd) >> 4;
    if ((rtb_ShiftArithmetic3 >= 0) && (rtb_ShiftArithmetic9_f <
         rtb_ShiftArithmetic3 - MAX_int32_T)) {
      rtb_ShiftArithmetic9_f = MAX_int32_T;
    } else if ((rtb_ShiftArithmetic3 < 0) && (rtb_ShiftArithmetic9_f >
                rtb_ShiftArithmetic3 - MIN_int32_T)) {
      rtb_ShiftArithmetic9_f = MIN_int32_T;
    } else {
      rtb_ShiftArithmetic9_f = rtb_ShiftArithmetic3 - rtb_ShiftArithmetic9_f;
    }

    if (rtb_ShiftArithmetic9_f > 32767) {
      rtb_ShiftArithmetic9_f = 32767;
    } else if (rtb_ShiftArithmetic9_f < -32768) {
      rtb_ShiftArithmetic9_f = -32768;
    }

    /* Sum: '<S54>/Sum' incorporates:
     *  DataStoreRead: '<S18>/Data Store Read3'
     *  Product: '<S54>/Product2'
     *  Sum: '<S18>/Sum2'
     */
    rtb_ShiftArithmetic9_f *= rtDW.Speed_Kp_Point;

    /* Switch: '<S59>/Switch2' incorporates:
     *  DataStoreRead: '<S54>/Data Store Read3'
     *  Gain: '<S54>/Gain'
     *  RelationalOperator: '<S59>/LowerRelop1'
     *  RelationalOperator: '<S59>/UpperRelop'
     *  Switch: '<S59>/Switch'
     */
    if (rtb_ShiftArithmetic9_f > rtDW.Speed_Limit) {
      rtb_ShiftArithmetic9_f = rtDW.Speed_Limit;
    } else if (rtb_ShiftArithmetic9_f < -rtDW.Speed_Limit) {
      /* Switch: '<S59>/Switch' incorporates:
       *  Gain: '<S54>/Gain'
       */
      rtb_ShiftArithmetic9_f = -rtDW.Speed_Limit;
    }

    /* End of Switch: '<S59>/Switch2' */

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataTypeConversion: '<S18>/Data Type Conversion2'
     *  SignalConversion generated from: '<S18>/Iq'
     *  Sum: '<S18>/Sum'
     */
    rtDW.Merge1 = (int16_T)(rtb_ShiftArithmetic9_f - rtb_Bias_a);

    /* Delay: '<S18>/Delay1' incorporates:
     *  DataStoreRead: '<S18>/Data Store Read5'
     *  DataStoreRead: '<S18>/Data Store Read7'
     *  Sum: '<S18>/Sum4'
     *  UnaryMinus: '<S18>/Unary Minus2'
     */
    if (rtDW.icLoad_l) {
      rtDW.Delay1_DSTATE = (int16_T)(rtDW.Open_IqMin_Point - rtDW.Open_Iq_Point);
    }

    /* Switch: '<S57>/FixPt Switch' incorporates:
     *  Constant: '<S57>/Constant'
     *  Delay: '<S18>/Delay1'
     */
    if (rtDW.Delay1_DSTATE > 0) {
      rtb_Sum_ix = 0;
    } else {
      rtb_Sum_ix = rtDW.Delay1_DSTATE;
    }

    /* End of Switch: '<S57>/FixPt Switch' */

    /* Merge: '<S1>/Merge2' incorporates:
     *  Sum: '<S18>/Sum6'
     */
    rtDW.Merge2 = (int16_T)-rtb_Sum_ix;

    /* Update for Delay: '<S18>/Delay' incorporates:
     *  Bias: '<S18>/Bias'
     */
    rtDW.icLoad = false;
    rtDW.Delay_DSTATE_h = (int16_T)(rtb_Bias_a + 1);

    /* Update for UnitDelay: '<S18>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_m = rtb_ShiftArithmetic3;

    /* Update for Delay: '<S18>/Delay1' incorporates:
     *  Bias: '<S18>/Bias1'
     */
    rtDW.icLoad_l = false;
    rtDW.Delay1_DSTATE = (int16_T)(rtb_Sum_ix + 1);

    /* End of Outputs for SubSystem: '<S1>/观测器闭环//速度环' */
    break;

   case 5:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/慢速开环' incorporates:
       *  ActionPort: '<S16>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S52>/Unit Delay'
       */
      rtDW.UnitDelay_DSTATE_h = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/慢速开环' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/慢速开环' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* Sum: '<S52>/Sum' incorporates:
     *  ArithShift: '<S16>/Shift Arithmetic'
     *  ArithShift: '<S52>/Shift Arithmetic'
     *  ArithShift: '<S52>/这个是缩小周期增益的'
     *  Constant: '<S52>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read2'
     *  DataStoreRead: '<S52>/Data Store Read1'
     *  DataTypeConversion: '<S16>/Data Type Conversion2'
     *  Product: '<S52>/Product2'
     *  UnitDelay: '<S52>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Slow << 16) >> ((int16_T)TS_POINT_GAIN))
      * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_h;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S16>/Data Type Conversion'
     *  SignalConversion generated from: '<S16>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic3;

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S16>/Data Store Read6'
     */
    rtDW.Merge1 = rtDW.Open_Iq_Slow;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S16>/Constant8'
     *  SignalConversion generated from: '<S16>/Id'
     */
    rtDW.Merge2 = 0;

    /* Update for UnitDelay: '<S52>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_h = rtb_ShiftArithmetic3;

    /* End of Outputs for SubSystem: '<S1>/慢速开环' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* Lookup_n-D: '<S10>/Sin1' incorporates:
   *  ArithShift: '<S10>/Shift Arithmetic'
   *  Constant: '<S10>/Constant3'
   *  Sum: '<S10>/Sum2'
   */
  rtb_Bias_a = rtConstP.pooled14[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    (uint16_T)(rtDW.Merge + 16384U) >> 7), 1U)];

  /* ArithShift: '<S4>/Shift Arithmetic' incorporates:
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S4>/Add2'
   */
  rtb_ShiftArithmetic9_f = ((rtb_ShiftArithmetic1_o - rtb_ShiftArithmetic2) *
    18918) >> 15;

  /* Lookup_n-D: '<S10>/Sin' incorporates:
   *  ArithShift: '<S10>/Shift Arithmetic1'
   *  Merge: '<S1>/Merge'
   *  Sum: '<S12>/Sum4'
   */
  rtb_Sum_ix = rtConstP.pooled14[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    rtDW.Merge >> 7), 1U)];

  /* RelationalOperator: '<S1>/Relational Operator' incorporates:
   *  Constant: '<S1>/Constant3'
   */
  rtb_RelationalOperator = (rtDW.Motor_State > 0);

  /* Outputs for Enabled SubSystem: '<S1>/idq_Controller' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtb_RelationalOperator) {
    if (!rtDW.idq_Controller_MODE) {
      /* InitializeConditions for UnitDelay: '<S9>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE_j = 0;

      /* InitializeConditions for UnitDelay: '<S42>/Unit Delay' */
      rtDW.UnitDelay_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S9>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_d = 0;

      /* InitializeConditions for UnitDelay: '<S45>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_f = 0;
      rtDW.idq_Controller_MODE = true;
    }

    /* Sum: '<S9>/Sum5' incorporates:
     *  UnitDelay: '<S9>/Unit Delay4'
     */
    rtb_Sum5_f = (int16_T)(rtDW.Merge2 - rtDW.UnitDelay4_DSTATE_j);

    /* Switch: '<S40>/Switch2' incorporates:
     *  Constant: '<S9>/Constant1'
     *  Constant: '<S9>/Constant2'
     *  RelationalOperator: '<S40>/LowerRelop1'
     *  RelationalOperator: '<S40>/UpperRelop'
     *  Switch: '<S40>/Switch'
     */
    if (rtb_Sum5_f > ((int16_T)CURR_STEP)) {
      rtb_Sum5_f = ((int16_T)CURR_STEP);
    } else if (rtb_Sum5_f < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S40>/Switch' incorporates:
       *  Constant: '<S9>/Constant1'
       */
      rtb_Sum5_f = (int16_T)-((int16_T)CURR_STEP);
    }

    /* Sum: '<S9>/Sum6' incorporates:
     *  Switch: '<S40>/Switch2'
     *  UnitDelay: '<S9>/Unit Delay4'
     */
    rtb_Sum5_f += rtDW.UnitDelay4_DSTATE_j;

    /* Sum: '<S9>/Sum1' incorporates:
     *  ArithShift: '<S7>/Shift Arithmetic'
     *  Lookup_n-D: '<S10>/Sin1'
     *  Product: '<S7>/Product'
     *  Product: '<S7>/Product1'
     *  Sum: '<S12>/Sum4'
     *  Sum: '<S7>/Add2'
     */
    rtb_ShiftArithmetic3 = rtb_Sum5_f - ((rtb_ShiftArithmetic_f * rtb_Bias_a +
      rtb_ShiftArithmetic9_f * rtb_Sum_ix) >> 15);

    /* ArithShift: '<S42>/Shift Arithmetic' incorporates:
     *  ArithShift: '<S45>/Shift Arithmetic'
     *  Constant: '<S42>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S9>/Data Store Read5'
     */
    rtb_Gain_f = rtDW.Curr_Ki_Point >> ((int16_T)TS_POINT_GAIN);

    /* Sum: '<S42>/Sum' incorporates:
     *  ArithShift: '<S42>/Shift Arithmetic'
     *  ArithShift: '<S42>/这个是缩小周期增益的'
     *  DataStoreRead: '<S42>/Data Store Read1'
     *  Product: '<S42>/Product1'
     *  Product: '<S42>/Product2'
     *  UnitDelay: '<S42>/Unit Delay'
     */
    rtb_Gain_av = ((rtDW.Ts_Point * rtb_ShiftArithmetic3) >> 15) * rtb_Gain_f +
      rtDW.UnitDelay_DSTATE;

    /* Switch: '<S43>/Switch2' incorporates:
     *  DataStoreRead: '<S42>/Data Store Read3'
     *  Gain: '<S42>/Gain'
     *  RelationalOperator: '<S43>/LowerRelop1'
     *  RelationalOperator: '<S43>/UpperRelop'
     *  Switch: '<S43>/Switch'
     */
    if (rtb_Gain_av > rtDW.Curr_Limit) {
      rtb_Gain_av = rtDW.Curr_Limit;
    } else if (rtb_Gain_av < -rtDW.Curr_Limit) {
      /* Switch: '<S43>/Switch' incorporates:
       *  Gain: '<S42>/Gain'
       */
      rtb_Gain_av = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S43>/Switch2' */

    /* Sum: '<S37>/Sum' incorporates:
     *  DataStoreRead: '<S9>/Data Store Read2'
     *  Product: '<S37>/Product2'
     */
    rtb_ShiftArithmetic3 = rtb_ShiftArithmetic3 * rtDW.Curr_Kp_Point
      + rtb_Gain_av;

    /* Switch: '<S41>/Switch2' incorporates:
     *  DataStoreRead: '<S37>/Data Store Read3'
     *  Gain: '<S37>/Gain'
     *  RelationalOperator: '<S41>/LowerRelop1'
     *  RelationalOperator: '<S41>/UpperRelop'
     *  Switch: '<S41>/Switch'
     */
    if (rtb_ShiftArithmetic3 > rtDW.Curr_Limit) {
      rtb_ShiftArithmetic3 = rtDW.Curr_Limit;
    } else if (rtb_ShiftArithmetic3 < -rtDW.Curr_Limit) {
      /* Switch: '<S41>/Switch' incorporates:
       *  Gain: '<S37>/Gain'
       */
      rtb_ShiftArithmetic3 = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S41>/Switch2' */

    /* ArithShift: '<S9>/Shift Arithmetic4' incorporates:
     *  ArithShift: '<S9>/Shift Arithmetic2'
     *  Sum: '<S35>/Sum1'
     */
    rtDW.Ud = rtb_ShiftArithmetic3 >> 16;

    /* Sum: '<S9>/Sum9' incorporates:
     *  UnitDelay: '<S9>/Unit Delay3'
     */
    rtb_Saturation = (int16_T)(rtDW.Merge1 - rtDW.UnitDelay3_DSTATE_d);

    /* Switch: '<S39>/Switch2' incorporates:
     *  Constant: '<S9>/Constant3'
     *  Constant: '<S9>/Constant8'
     *  RelationalOperator: '<S39>/LowerRelop1'
     *  RelationalOperator: '<S39>/UpperRelop'
     *  Switch: '<S39>/Switch'
     */
    if (rtb_Saturation > ((int16_T)CURR_STEP)) {
      rtb_Saturation = ((int16_T)CURR_STEP);
    } else if (rtb_Saturation < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S39>/Switch' incorporates:
       *  Constant: '<S9>/Constant3'
       */
      rtb_Saturation = (int16_T)-((int16_T)CURR_STEP);
    }

    /* End of Switch: '<S39>/Switch2' */

    /* Sum: '<S9>/Sum10' incorporates:
     *  UnitDelay: '<S9>/Unit Delay3'
     */
    rtb_Saturation += rtDW.UnitDelay3_DSTATE_d;

    /* Sum: '<S9>/Sum8' incorporates:
     *  ArithShift: '<S7>/Shift Arithmetic1'
     *  Lookup_n-D: '<S10>/Sin1'
     *  Product: '<S7>/Product2'
     *  Product: '<S7>/Product3'
     *  Sum: '<S12>/Sum4'
     *  Sum: '<S7>/Add1'
     */
    rtb_ShiftArithmetic3 = rtb_Saturation - ((rtb_ShiftArithmetic9_f *
      rtb_Bias_a - rtb_ShiftArithmetic_f * rtb_Sum_ix) >> 15);

    /* Sum: '<S45>/Sum' incorporates:
     *  ArithShift: '<S45>/这个是缩小周期增益的'
     *  DataStoreRead: '<S45>/Data Store Read1'
     *  Product: '<S45>/Product1'
     *  Product: '<S45>/Product2'
     *  UnitDelay: '<S45>/Unit Delay'
     */
    rtb_Gain_f = ((rtDW.Ts_Point * rtb_ShiftArithmetic3) >> 15) * rtb_Gain_f +
      rtDW.UnitDelay_DSTATE_f;

    /* Switch: '<S46>/Switch2' incorporates:
     *  DataStoreRead: '<S45>/Data Store Read3'
     *  Gain: '<S45>/Gain'
     *  RelationalOperator: '<S46>/LowerRelop1'
     *  RelationalOperator: '<S46>/UpperRelop'
     *  Switch: '<S46>/Switch'
     */
    if (rtb_Gain_f > rtDW.Curr_Limit) {
      rtb_Gain_f = rtDW.Curr_Limit;
    } else if (rtb_Gain_f < -rtDW.Curr_Limit) {
      /* Switch: '<S46>/Switch' incorporates:
       *  Gain: '<S45>/Gain'
       */
      rtb_Gain_f = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S46>/Switch2' */

    /* Sum: '<S38>/Sum' incorporates:
     *  DataStoreRead: '<S9>/Data Store Read6'
     *  Product: '<S38>/Product2'
     */
    rtb_ShiftArithmetic3 = rtb_ShiftArithmetic3 * rtDW.Curr_Kp_Point
      + rtb_Gain_f;

    /* Switch: '<S44>/Switch2' incorporates:
     *  DataStoreRead: '<S38>/Data Store Read3'
     *  Gain: '<S38>/Gain'
     *  RelationalOperator: '<S44>/LowerRelop1'
     *  RelationalOperator: '<S44>/UpperRelop'
     *  Switch: '<S44>/Switch'
     */
    if (rtb_ShiftArithmetic3 > rtDW.Curr_Limit) {
      rtb_ShiftArithmetic3 = rtDW.Curr_Limit;
    } else if (rtb_ShiftArithmetic3 < -rtDW.Curr_Limit) {
      /* Switch: '<S44>/Switch' incorporates:
       *  Gain: '<S38>/Gain'
       */
      rtb_ShiftArithmetic3 = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S44>/Switch2' */

    /* ArithShift: '<S9>/Shift Arithmetic5' incorporates:
     *  ArithShift: '<S9>/Shift Arithmetic3'
     *  Sum: '<S35>/Sum1'
     */
    rtDW.Uq = rtb_ShiftArithmetic3 >> 16;

    /* Update for UnitDelay: '<S9>/Unit Delay4' */
    rtDW.UnitDelay4_DSTATE_j = rtb_Sum5_f;

    /* Update for UnitDelay: '<S42>/Unit Delay' */
    rtDW.UnitDelay_DSTATE = rtb_Gain_av;

    /* Update for UnitDelay: '<S9>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_d = rtb_Saturation;

    /* Update for UnitDelay: '<S45>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_f = rtb_Gain_f;
  } else {
    rtDW.idq_Controller_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/idq_Controller' */

  /* ArithShift: '<S2>/Shift Arithmetic' incorporates:
   *  Lookup_n-D: '<S10>/Sin1'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S12>/Sum4'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add'
   */
  rtb_Gain_av = (rtDW.Ud * rtb_Bias_a - rtDW.Uq * rtb_Sum_ix) >> 15;

  /* ArithShift: '<S2>/Shift Arithmetic1' incorporates:
   *  Lookup_n-D: '<S10>/Sin1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S12>/Sum4'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add1'
   */
  rtb_Gain_f = (rtDW.Ud * rtb_Sum_ix + rtDW.Uq * rtb_Bias_a) >> 15;

  /* Outputs for Enabled SubSystem: '<S1>/Observers' incorporates:
   *  EnablePort: '<S6>/Enable'
   */
  if (rtb_RelationalOperator) {
    if (!rtDW.Observers_MODE) {
      /* SystemReset for Atomic SubSystem: '<S6>/SMO' */
      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay6' */
      rtDW.UnitDelay6_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S33>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay2' */
      rtDW.UnitDelay2_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_l = 0;

      /* InitializeConditions for UnitDelay: '<S34>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE_m = 0;

      /* End of SystemReset for SubSystem: '<S6>/SMO' */

      /* SystemReset for Atomic SubSystem: '<S6>/PLL' */
      /* InitializeConditions for UnitDelay: '<S24>/Unit Delay' */
      rtY.Obs_Theta = 0U;

      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_p = 0;

      /* InitializeConditions for UnitDelay: '<S29>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_m = 0;

      /* InitializeConditions for UnitDelay: '<S24>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE_p = 0;

      /* SystemReset for Atomic SubSystem: '<S24>/LPF' */
      /* InitializeConditions for UnitDelay: '<S26>/Unit Delay9' */
      rtY.Obs_Spd = 0;

      /* End of SystemReset for SubSystem: '<S24>/LPF' */
      /* End of SystemReset for SubSystem: '<S6>/PLL' */
      rtDW.Observers_MODE = true;
    }

    /* Outputs for Atomic SubSystem: '<S6>/SMO' */
    /* Sum: '<S25>/Sum4' incorporates:
     *  ArithShift: '<S25>/Shift Arithmetic3'
     *  ArithShift: '<S25>/Shift Arithmetic5'
     *  DataStoreRead: '<S25>/Data Store Read11'
     *  DataStoreRead: '<S25>/Data Store Read7'
     *  DataStoreRead: '<S25>/Data Store Read8'
     *  Product: '<S25>/Product5'
     *  Product: '<S25>/Product6'
     *  Product: '<S25>/Product8'
     *  Sum: '<S25>/Sum3'
     *  UnitDelay: '<S25>/Unit Delay4'
     *  UnitDelay: '<S25>/Unit Delay6'
     */
    rtb_Gain = (((rtDW.Obs_VtoI * rtb_Gain_av - rtDW.UnitDelay4_DSTATE) *
                 rtDW.SMO_Gain2) >> 15) + ((rtDW.UnitDelay6_DSTATE *
      rtDW.SMO_Gain1) >> 15);

    /* Product: '<S25>/Product9' incorporates:
     *  DataStoreRead: '<S25>/Data Store Read14'
     *  Sum: '<S25>/Sum5'
     */
    rtb_ShiftArithmetic3 = (rtb_Gain - rtb_ShiftArithmetic_f) * rtDW.SMO_K;

    /* Saturate: '<S25>/Saturation1' */
    if (rtb_ShiftArithmetic3 > 32767) {
      rtb_ShiftArithmetic3 = 32767;
    } else if (rtb_ShiftArithmetic3 < -32767) {
      rtb_ShiftArithmetic3 = -32767;
    }

    /* End of Saturate: '<S25>/Saturation1' */

    /* Sum: '<S33>/Sum2' incorporates:
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  DataStoreRead: '<S33>/Data Store Read1'
     *  Product: '<S33>/Product1'
     *  Sum: '<S33>/Sum1'
     *  UnitDelay: '<S33>/Unit Delay1'
     */
    rtb_Sum2 = (((rtb_ShiftArithmetic3 - rtDW.UnitDelay1_DSTATE) *
                 rtDW.LPF_FRQ_Point) >> 15) + rtDW.UnitDelay1_DSTATE;

    /* Update for UnitDelay: '<S25>/Unit Delay4' incorporates:
     *  Sum: '<S25>/Sum9'
     */
    rtDW.UnitDelay4_DSTATE = rtb_ShiftArithmetic3 + rtb_Sum2;

    /* Sum: '<S25>/Sum7' incorporates:
     *  ArithShift: '<S25>/Shift Arithmetic4'
     *  ArithShift: '<S25>/Shift Arithmetic6'
     *  DataStoreRead: '<S25>/Data Store Read13'
     *  DataStoreRead: '<S25>/Data Store Read15'
     *  DataStoreRead: '<S25>/Data Store Read16'
     *  Product: '<S25>/Product10'
     *  Product: '<S25>/Product11'
     *  Product: '<S25>/Product12'
     *  Sum: '<S25>/Sum2'
     *  UnitDelay: '<S25>/Unit Delay2'
     *  UnitDelay: '<S25>/Unit Delay3'
     */
    rtb_Sum7 = (((rtb_Gain_f * rtDW.Obs_VtoI - rtDW.UnitDelay2_DSTATE) *
                 rtDW.SMO_Gain2) >> 15) + ((rtDW.SMO_Gain1 *
      rtDW.UnitDelay3_DSTATE_l) >> 15);

    /* Product: '<S25>/Product13' incorporates:
     *  DataStoreRead: '<S25>/Data Store Read12'
     *  Sum: '<S25>/Sum8'
     */
    rtb_ShiftArithmetic3 = (rtb_Sum7 - rtb_ShiftArithmetic9_f) * rtDW.SMO_K;

    /* Saturate: '<S25>/Saturation2' */
    if (rtb_ShiftArithmetic3 > 32767) {
      rtb_ShiftArithmetic3 = 32767;
    } else if (rtb_ShiftArithmetic3 < -32767) {
      rtb_ShiftArithmetic3 = -32767;
    }

    /* End of Saturate: '<S25>/Saturation2' */

    /* Sum: '<S34>/Sum2' incorporates:
     *  ArithShift: '<S34>/Shift Arithmetic4'
     *  DataStoreRead: '<S34>/Data Store Read1'
     *  Product: '<S34>/Product1'
     *  Sum: '<S34>/Sum1'
     *  UnitDelay: '<S34>/Unit Delay1'
     */
    rtb_ShiftArithmetic9_f = (((rtb_ShiftArithmetic3 - rtDW.UnitDelay1_DSTATE_m)
      * rtDW.LPF_FRQ_Point) >> 15) + rtDW.UnitDelay1_DSTATE_m;

    /* Update for UnitDelay: '<S25>/Unit Delay6' */
    rtDW.UnitDelay6_DSTATE = rtb_Gain;

    /* Update for UnitDelay: '<S33>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE = rtb_Sum2;

    /* Update for UnitDelay: '<S25>/Unit Delay2' incorporates:
     *  Sum: '<S25>/Sum'
     */
    rtDW.UnitDelay2_DSTATE = rtb_ShiftArithmetic9_f + rtb_ShiftArithmetic3;

    /* Update for UnitDelay: '<S25>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_l = rtb_Sum7;

    /* Update for UnitDelay: '<S34>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m = rtb_ShiftArithmetic9_f;

    /* End of Outputs for SubSystem: '<S6>/SMO' */

    /* Outputs for Atomic SubSystem: '<S6>/PLL' */
    /* Sum: '<S24>/Sum4' incorporates:
     *  ArithShift: '<S24>/Shift Arithmetic7'
     *  ArithShift: '<S24>/Shift Arithmetic8'
     *  ArithShift: '<S28>/Shift Arithmetic'
     *  ArithShift: '<S28>/Shift Arithmetic1'
     *  Constant: '<S28>/Constant3'
     *  Lookup_n-D: '<S28>/Sin'
     *  Lookup_n-D: '<S28>/Sin1'
     *  Product: '<S24>/Product3'
     *  Product: '<S24>/Product4'
     *  Sum: '<S28>/Sum2'
     *  UnitDelay: '<S24>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = -((rtConstP.pooled14[plook_u32u16_even0ckag((uint16_T)
      ((uint32_T)(uint16_T)(rtY.Obs_Theta + 16384U) >> 7), 1U)] * rtb_Sum2) >>
      15) - ((rtConstP.pooled14[plook_u32u16_even0ckag((uint16_T)((uint32_T)
                rtY.Obs_Theta >> 7), 1U)] * rtb_ShiftArithmetic9_f) >> 15);

    /* Sum: '<S31>/Sum' incorporates:
     *  ArithShift: '<S31>/Shift Arithmetic'
     *  ArithShift: '<S31>/这个是缩小周期增益的'
     *  Constant: '<S31>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S24>/Data Store Read8'
     *  DataStoreRead: '<S31>/Data Store Read1'
     *  Product: '<S31>/Product1'
     *  Product: '<S31>/Product2'
     *  UnitDelay: '<S31>/Unit Delay'
     */
    rtb_ShiftArithmetic9_f = ((rtDW.Ts_Point * rtb_ShiftArithmetic3) >> 15) *
      (rtDW.PLL_Ki >> ((int16_T)TS_POINT_GAIN)) + rtDW.UnitDelay_DSTATE_p;

    /* Switch: '<S32>/Switch2' incorporates:
     *  DataStoreRead: '<S31>/Data Store Read3'
     *  Gain: '<S31>/Gain'
     *  RelationalOperator: '<S32>/LowerRelop1'
     *  RelationalOperator: '<S32>/UpperRelop'
     *  Switch: '<S32>/Switch'
     */
    if (rtb_ShiftArithmetic9_f > rtDW.PLL_Limit) {
      rtb_ShiftArithmetic9_f = rtDW.PLL_Limit;
    } else if (rtb_ShiftArithmetic9_f < -rtDW.PLL_Limit) {
      /* Switch: '<S32>/Switch' incorporates:
       *  Gain: '<S31>/Gain'
       */
      rtb_ShiftArithmetic9_f = -rtDW.PLL_Limit;
    }

    /* End of Switch: '<S32>/Switch2' */

    /* Sum: '<S27>/Sum' incorporates:
     *  DataStoreRead: '<S24>/Data Store Read7'
     *  Product: '<S27>/Product2'
     */
    rtb_ShiftArithmetic3 = rtb_ShiftArithmetic3 * rtDW.PLL_Kp +
      rtb_ShiftArithmetic9_f;

    /* Switch: '<S30>/Switch2' incorporates:
     *  DataStoreRead: '<S27>/Data Store Read3'
     *  Gain: '<S27>/Gain'
     *  RelationalOperator: '<S30>/LowerRelop1'
     *  RelationalOperator: '<S30>/UpperRelop'
     *  Switch: '<S30>/Switch'
     */
    if (rtb_ShiftArithmetic3 > rtDW.PLL_Limit) {
      rtb_ShiftArithmetic3 = rtDW.PLL_Limit;
    } else if (rtb_ShiftArithmetic3 < -rtDW.PLL_Limit) {
      /* Switch: '<S30>/Switch' incorporates:
       *  Gain: '<S27>/Gain'
       */
      rtb_ShiftArithmetic3 = -rtDW.PLL_Limit;
    }

    /* End of Switch: '<S30>/Switch2' */

    /* Sum: '<S29>/Sum' incorporates:
     *  ArithShift: '<S29>/Shift Arithmetic'
     *  ArithShift: '<S29>/这个是缩小周期增益的'
     *  Constant: '<S29>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S29>/Data Store Read1'
     *  Product: '<S29>/Product2'
     *  Sum: '<S35>/Sum1'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    rtb_Gain = (((rtb_ShiftArithmetic3 >> ((int16_T)TS_POINT_GAIN)) *
                 rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_m;

    /* Outputs for Atomic SubSystem: '<S24>/LPF' */
    /* Saturate: '<S26>/Saturation' incorporates:
     *  Constant: '<S26>/Constant1'
     */
    if (((int16_T)SPD_LPF_LEVEL) > 15) {
      rtb_Saturation = 15;
    } else if (((int16_T)SPD_LPF_LEVEL) < 0) {
      rtb_Saturation = 0;
    } else {
      rtb_Saturation = ((int16_T)SPD_LPF_LEVEL);
    }

    /* End of Saturate: '<S26>/Saturation' */

    /* Outport: '<Root>/Obs_Spd' incorporates:
     *  ArithShift: '<S24>/Shift Arithmetic13'
     *  ArithShift: '<S26>/Shift Arithmetic9'
     *  Product: '<S26>/Product10'
     *  Product: '<S26>/Product11'
     *  Sum: '<S26>/Sum10'
     *  Sum: '<S26>/Sum11'
     *  Sum: '<S35>/Sum1'
     *  UnitDelay: '<S26>/Unit Delay9'
     */
    rtY.Obs_Spd = ((16 - rtb_Saturation) * (rtb_ShiftArithmetic3 >> 16) +
                   rtY.Obs_Spd * rtb_Saturation) >> 4;

    /* End of Outputs for SubSystem: '<S24>/LPF' */

    /* Outport: '<Root>/Obs_Theta' incorporates:
     *  ArithShift: '<S24>/Shift Arithmetic10'
     *  ArithShift: '<S24>/Shift Arithmetic15'
     *  DataStoreRead: '<S24>/Data Store Read6'
     *  DataTypeConversion: '<S24>/Data Type Conversion8'
     *  Lookup_n-D: '<S24>/atan256'
     *  Product: '<S24>/Product2'
     *  Sum: '<S24>/Sum1'
     *  Sum: '<S24>/Sum3'
     *  UnitDelay: '<S24>/Unit Delay1'
     */
    rtY.Obs_Theta = (uint16_T)((uint32_T)
      rtConstP.atan256_tableData[plook_u32s32_even0ckag(((rtDW.DIV_LPF_FRQ << 8)
      * rtDW.UnitDelay1_DSTATE_p) >> 15, 1)] + (uint16_T)rtb_Gain);

    /* Update for UnitDelay: '<S31>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_p = rtb_ShiftArithmetic9_f;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_m = rtb_Gain;

    /* Update for UnitDelay: '<S24>/Unit Delay1' incorporates:
     *  Outport: '<Root>/Obs_Spd'
     */
    rtDW.UnitDelay1_DSTATE_p = rtY.Obs_Spd;

    /* End of Outputs for SubSystem: '<S6>/PLL' */
  } else {
    rtDW.Observers_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/Observers' */

  /* ArithShift: '<S35>/Shift Arithmetic' incorporates:
   *  Gain: '<S35>/Gain1'
   */
  rtb_ShiftArithmetic3 = (28377 * rtb_Gain_f) >> 15;

  /* ArithShift: '<S35>/Shift Arithmetic1' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic'
   */
  rtb_Gain_f = rtb_Gain_av >> 1;

  /* Sum: '<S35>/Sum' */
  rtb_ShiftArithmetic9_f = rtb_ShiftArithmetic3 - rtb_Gain_f;

  /* Sum: '<S35>/Sum1' */
  rtb_ShiftArithmetic3 = -rtb_ShiftArithmetic3 - rtb_Gain_f;

  /* ArithShift: '<S8>/Shift Arithmetic' incorporates:
   *  DataStoreRead: '<S8>/Data Store Read3'
   */
  rtb_Bias_a = (int16_T)(rtDW.PWM_TH >> 1);

  /* MinMax: '<S36>/Min' */
  if (rtb_Gain_av <= rtb_ShiftArithmetic9_f) {
    rtb_Gain_f = rtb_Gain_av;
  } else {
    rtb_Gain_f = rtb_ShiftArithmetic9_f;
  }

  /* MinMax: '<S36>/Min1' */
  if (rtb_Gain_av >= rtb_ShiftArithmetic9_f) {
    rtb_Gain = rtb_Gain_av;
  } else {
    rtb_Gain = rtb_ShiftArithmetic9_f;
  }

  /* MinMax: '<S36>/Min' */
  if (rtb_Gain_f > rtb_ShiftArithmetic3) {
    rtb_Gain_f = rtb_ShiftArithmetic3;
  }

  /* MinMax: '<S36>/Min1' */
  if (rtb_Gain < rtb_ShiftArithmetic3) {
    rtb_Gain = rtb_ShiftArithmetic3;
  }

  /* UnaryMinus: '<S36>/Unary Minus' incorporates:
   *  ArithShift: '<S36>/Shift Arithmetic'
   *  MinMax: '<S36>/Min'
   *  MinMax: '<S36>/Min1'
   *  Sum: '<S36>/Sum'
   */
  rtb_Gain_f = -((rtb_Gain_f + rtb_Gain) >> 1);

  /* Outputs for Enabled SubSystem: '<S1>/切闭环角度差' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* RelationalOperator: '<S1>/Relational Operator1' incorporates:
   *  Constant: '<S1>/闭环是4'
   */
  if (rtDW.Motor_State < 4) {
    if (!rtDW._MODE) {
      /* InitializeConditions for UnitDelay: '<S12>/Unit Delay7' */
      rtDW.UnitDelay7_DSTATE = 0U;

      /* InitializeConditions for UnitDelay: '<S12>/Unit Delay6' */
      rtDW.UnitDelay6_DSTATE_a = 0U;

      /* InitializeConditions for UnitDelay: '<S12>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE = 0U;
      rtDW._MODE = true;
    }

    /* Sum: '<S12>/Sum4' incorporates:
     *  UnitDelay: '<S12>/Unit Delay6'
     *  UnitDelay: '<S12>/Unit Delay7'
     */
    rtb_Sum_ix = (int16_T)((int16_T)rtDW.UnitDelay7_DSTATE - (int16_T)
      rtDW.UnitDelay6_DSTATE_a);

    /* Abs: '<S12>/Abs' */
    if (rtb_Sum_ix < 0) {
      /* Abs: '<S12>/Abs' */
      rtDW.Abs = (int16_T)-rtb_Sum_ix;
    } else {
      /* Abs: '<S12>/Abs' */
      rtDW.Abs = rtb_Sum_ix;
    }

    /* End of Abs: '<S12>/Abs' */

    /* Update for UnitDelay: '<S12>/Unit Delay7' incorporates:
     *  UnitDelay: '<S12>/Unit Delay5'
     */
    rtDW.UnitDelay7_DSTATE = rtDW.UnitDelay5_DSTATE;

    /* Update for UnitDelay: '<S12>/Unit Delay6' */
    rtDW.UnitDelay6_DSTATE_a = rtDW.Merge;

    /* Update for UnitDelay: '<S12>/Unit Delay5' incorporates:
     *  Outport: '<Root>/Obs_Theta'
     */
    rtDW.UnitDelay5_DSTATE = rtY.Obs_Theta;
  } else {
    rtDW._MODE = false;
  }

  /* End of RelationalOperator: '<S1>/Relational Operator1' */
  /* End of Outputs for SubSystem: '<S1>/切闭环角度差' */

  /* Update for Enabled SubSystem: '<S5>/闭环错误判断' incorporates:
   *  EnablePort: '<S21>/Enable'
   */
  if (rtDW._MODE_p) {
    /* Update for UnitDelay: '<S21>/Unit Delay' incorporates:
     *  Outport: '<Root>/Obs_Spd'
     */
    rtDW.UnitDelay_DSTATE_k = rtY.Obs_Spd;
  }

  /* End of Update for SubSystem: '<S5>/闭环错误判断' */

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_b = rtDW.Merge;

  /* Signum: '<S8>/Sign' */
  if (rtb_ShiftArithmetic_f < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic_f > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S8>/默认除以32767'
   *  DataStoreRead: '<S8>/Data Store Read4'
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   *  Gain: '<S8>/Gain1'
   *  Product: '<S8>/Product'
   *  SignalConversion generated from: '<S8>/Sum'
   *  Signum: '<S8>/Sign'
   *  Sum: '<S8>/Sum'
   *  Sum: '<S8>/Sum1'
   *  UnaryMinus: '<S8>/Unary Minus'
   */
  rtY.tABC[0] = (uint16_T)((int16_T)-((((rtb_Gain_av + rtb_Gain_f) - -85 *
    rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_a);

  /* Signum: '<S8>/Sign' */
  if (rtb_ShiftArithmetic1_o < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic1_o > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S8>/默认除以32767'
   *  DataStoreRead: '<S8>/Data Store Read4'
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   *  Gain: '<S8>/Gain1'
   *  Product: '<S8>/Product'
   *  SignalConversion generated from: '<S8>/Sum'
   *  Signum: '<S8>/Sign'
   *  Sum: '<S8>/Sum'
   *  Sum: '<S8>/Sum1'
   *  UnaryMinus: '<S8>/Unary Minus'
   */
  rtY.tABC[1] = (uint16_T)((int16_T)-((((rtb_ShiftArithmetic9_f + rtb_Gain_f) -
    -85 * rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_a);

  /* Signum: '<S8>/Sign' */
  if (rtb_ShiftArithmetic2 < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic2 > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S8>/默认除以32767'
   *  DataStoreRead: '<S8>/Data Store Read4'
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   *  Gain: '<S8>/Gain1'
   *  Product: '<S8>/Product'
   *  SignalConversion generated from: '<S8>/Sum'
   *  Signum: '<S8>/Sign'
   *  Sum: '<S8>/Sum'
   *  Sum: '<S8>/Sum1'
   *  UnaryMinus: '<S8>/Unary Minus'
   */
  rtY.tABC[2] = (uint16_T)((int16_T)-((((rtb_ShiftArithmetic3 + rtb_Gain_f) -
    -85 * rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_a);

  /* End of Outputs for SubSystem: '<Root>/FOC_PointModel' */
}

/* Model initialize function */
void FOC_PointModel_initialize(void)
{
  {
    real_T rtb_ShiftArithmetic4;
    real_T u;
    real_T v;
    real32_T rtb_Product18;
    real32_T u_tmp;
    real32_T v_0;

    /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_PointModel' */
    /* Start for SwitchCase: '<S1>/Switch Case' */
    rtDW.SwitchCase_ActiveSubsystem = -1;

    /* SystemInitialize for Enabled SubSystem: '<S5>/闭环错误判断' */
    /* Start for If: '<S21>/If1' */
    rtDW.If1_ActiveSubsystem = -1;

    /* End of SystemInitialize for SubSystem: '<S5>/闭环错误判断' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/恒速降力矩强拖' */
    /* InitializeConditions for Delay: '<S51>/Delay' */
    rtDW.icLoad_d = true;

    /* End of SystemInitialize for SubSystem: '<S1>/恒速降力矩强拖' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/观测器闭环//速度环' */
    /* InitializeConditions for Delay: '<S18>/Delay' */
    rtDW.icLoad = true;

    /* InitializeConditions for UnitDelay: '<S18>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_m = OPEN_SPD;

    /* InitializeConditions for Delay: '<S18>/Delay1' */
    rtDW.icLoad_l = true;

    /* End of SystemInitialize for SubSystem: '<S1>/观测器闭环//速度环' */

    /* Outputs for Atomic SubSystem: '<S1>/初始化模块' */
    /* ArithShift: '<S13>/Shift Arithmetic26' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic'
     *  Constant: '<S13>/Constant18'
     *  Constant: '<S13>/周期定点化适当放大2^n'
     */
    u = ldexp(ldexp(1.0 / FOC_FRQ, 15), ((int16_T)TS_POINT_GAIN));

    /* DataTypeConversion: '<S13>/Data Type Conversion6' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write7'
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

    /* End of DataTypeConversion: '<S13>/Data Type Conversion6' */

    /* ArithShift: '<S13>/Shift Arithmetic25' incorporates:
     *  Constant: '<S13>/ADC量程*母线电压分压倍数//定义的最大电压值'
     *  Constant: '<S13>/Constant16'
     *  Constant: '<S13>/电压采集定点化适当放大2^n'
     *  Product: '<S13>/Divide3'
     */
    rtb_Product18 = ldexpf(ADC_REF * UDC_GAIN / (real32_T)((int16_T)UDC),
      ((int16_T)UDC_POINT_GAIN));

    /* DataTypeConversion: '<S13>/Data Type Conversion5' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write6'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Voltage_Conversion = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Voltage_Conversion = 0;
      }
    } else {
      rtDW.Voltage_Conversion = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion5' */

    /* ArithShift: '<S13>/Shift Arithmetic24' incorporates:
     *  Constant: '<S13>/ADC量程//放大器倍数//定义的最大电流//采样电流'
     *  Constant: '<S13>/电流采集定点化适当放大2^n'
     */
    rtb_Product18 = ldexpf(ADC_REF / AMP_GAIN / IMAX / RS_HUNT, ((int16_T)
      CURR_POINT_GAIN));

    /* DataTypeConversion: '<S13>/Data Type Conversion4' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write5'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Conversion = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Conversion = 0;
      }
    } else {
      rtDW.Curr_Conversion = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion4' */

    /* Product: '<S13>/Divide7' incorporates:
     *  Constant: '<S13>/Constant20'
     *  Constant: '<S13>/Constant21'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ / MOTOR_LS;

    /* ArithShift: '<S13>/Shift Arithmetic3' incorporates:
     *  Constant: '<S13>/Constant1'
     *  Constant: '<S13>/Constant15'
     *  Product: '<S13>/Product5'
     *  Sum: '<S13>/Sum'
     */
    u = ldexp(1.0 - MOTOR_RS * rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion9' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write10'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain1 = (uint16_T)floor(u + 0.5);
      } else {
        rtDW.SMO_Gain1 = 0U;
      }
    } else {
      rtDW.SMO_Gain1 = (uint16_T)u;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion9' */

    /* ArithShift: '<S13>/Shift Arithmetic4' */
    u = ldexp(rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion10' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write11'
     */
    v = fabs(u);
    if (v < 4.503599627370496E+15) {
      if (v >= 0.5) {
        rtDW.SMO_Gain2 = (uint16_T)floor(u + 0.5);
      } else {
        rtDW.SMO_Gain2 = 0U;
      }
    } else {
      rtDW.SMO_Gain2 = (uint16_T)u;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion10' */

    /* Product: '<S13>/Divide' incorporates:
     *  Constant: '<S13>/Constant2'
     *  Constant: '<S13>/Constant71'
     *  Product: '<S13>/Divide1'
     */
    u_tmp = IMAX / (real32_T)((int16_T)UDC);

    /* ArithShift: '<S13>/Shift Arithmetic1' incorporates:
     *  Constant: '<S13>/Constant10'
     *  Constant: '<S13>/Constant9'
     *  Product: '<S13>/Divide'
     *  Product: '<S13>/Product'
     *  Product: '<S13>/Product2'
     */
    rtb_Product18 = ldexpf(CURR_WIDTH * MOTOR_LS * u_tmp, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion11' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Kp_Point = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Kp_Point = 0;
      }
    } else {
      rtDW.Curr_Kp_Point = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion11' */

    /* ArithShift: '<S13>/Shift Arithmetic2' incorporates:
     *  Constant: '<S13>/Constant11'
     *  Constant: '<S13>/Constant12'
     *  Product: '<S13>/Product1'
     *  Product: '<S13>/Product3'
     */
    rtb_Product18 = ldexpf(CURR_WIDTH * MOTOR_RS * u_tmp, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion1' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write2'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Ki_Point = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Ki_Point = 0;
      }
    } else {
      rtDW.Curr_Ki_Point = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion1' */

    /* Product: '<S13>/Divide5' incorporates:
     *  Constant: '<S13>/Constant13'
     *  Constant: '<S13>/Constant69'
     */
    rtb_Product18 = (real32_T)((int16_T)UDC) / IMAX;

    /* DataTypeConversion: '<S13>/Data Type Conversion8' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write9'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Obs_VtoI = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Obs_VtoI = 0;
      }
    } else {
      rtDW.Obs_VtoI = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion8' */

    /* Gain: '<S13>/Gain2' incorporates:
     *  Constant: '<S13>/Constant5'
     */
    rtb_Product18 = MOTOR_PN / 60.0F * (real32_T)OPEN_SPD;

    /* DataTypeConversion: '<S13>/Data Type Conversion2' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write12'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Hz = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_Hz = 0;
      }
    } else {
      rtDW.Open_Hz = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion2' */

    /* Product: '<S13>/Product4' incorporates:
     *  Constant: '<S13>/Constant14'
     *  Constant: '<S13>/Constant17'
     *  Product: '<S13>/Divide4'
     */
    rtb_Product18 *= 1.0F / OPEN_TIME;

    /* DataTypeConversion: '<S13>/Data Type Conversion7' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write13'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Acceleration = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_Acceleration = 0;
      }
    } else {
      rtDW.Open_Acceleration = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion7' */

    /* Gain: '<S13>/Gain4' incorporates:
     *  Constant: '<S13>/Constant19'
     *  Constant: '<S13>/Constant22'
     *  Product: '<S13>/Product6'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ * LPF_FRQ * 6.2831853071795862;

    /* DataTypeConversion: '<S13>/Data Type Conversion12' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic5'
     *  Constant: '<S13>/Constant24'
     *  DataStoreWrite: '<S13>/Data Store Write3'
     *  Product: '<S13>/Divide6'
     *  Sum: '<S13>/Sum1'
     */
    rtDW.LPF_FRQ_Point = (int16_T)ceil(ldexp(rtb_ShiftArithmetic4 /
      (rtb_ShiftArithmetic4 + 1.0), 15));

    /* Product: '<S13>/Product8' incorporates:
     *  Constant: '<S13>/Constant25'
     *  Constant: '<S13>/Constant26'
     */
    rtb_Product18 = PLL_WIDTH * PLL_WIDTH;

    /* DataTypeConversion: '<S13>/Data Type Conversion14' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write14'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Ki = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.PLL_Ki = 0;
      }
    } else {
      rtDW.PLL_Ki = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion14' */

    /* Product: '<S13>/Product7' incorporates:
     *  Constant: '<S13>/Constant25'
     *  Constant: '<S13>/Constant27'
     */
    rtb_Product18 = 2.0F * PLL_WIDTH;

    /* DataTypeConversion: '<S13>/Data Type Conversion13' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write8'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Kp = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.PLL_Kp = 0;
      }
    } else {
      rtDW.PLL_Kp = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion13' */

    /* DataTypeConversion: '<S13>/Data Type Conversion15' incorporates:
     *  Constant: '<S13>/Constant28'
     *  Constant: '<S13>/Constant29'
     *  DataStoreWrite: '<S13>/Data Store Write15'
     *  Gain: '<S13>/Gain'
     *  Product: '<S13>/Product9'
     */
    rtDW.SMO_K = (int16_T)ceilf(SMOK_FRQ * MOTOR_FLUX * 6.28318548F);

    /* DataTypeConversion: '<S13>/Data Type Conversion16' incorporates:
     *  Constant: '<S13>/Constant30'
     *  DataStoreWrite: '<S13>/Data Store Write16'
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

    /* End of DataTypeConversion: '<S13>/Data Type Conversion16' */

    /* ArithShift: '<S13>/Shift Arithmetic6' incorporates:
     *  Constant: '<S13>/Constant31'
     */
    rtb_Product18 = ldexpf(1.0F / LPF_FRQ, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion17' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write17'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.DIV_LPF_FRQ = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.DIV_LPF_FRQ = 0;
      }
    } else {
      rtDW.DIV_LPF_FRQ = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion17' */

    /* Product: '<S13>/Product10' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic7'
     *  Constant: '<S13>/Constant32'
     */
    rtb_Product18 = PLL_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S13>/Data Type Conversion18' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write18'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.PLL_Limit = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.PLL_Limit = 0;
      }
    } else {
      rtDW.PLL_Limit = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion18' */

    /* Product: '<S13>/Product11' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic8'
     *  Constant: '<S13>/Constant34'
     */
    rtb_Product18 = CURR_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S13>/Data Type Conversion19' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write19'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Limit = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Limit = 0;
      }
    } else {
      rtDW.Curr_Limit = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion19' */

    /* DataTypeConversion: '<S13>/Data Type Conversion23' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic12'
     *  Constant: '<S13>/Constant38'
     *  Constant: '<S13>/Constant49'
     *  DataStoreWrite: '<S13>/Data Store Write23'
     *  Product: '<S13>/Divide11'
     */
    rtDW.Hz_RPM = (int16_T)ceilf(ldexpf(60.0F / MOTOR_PN, 4));

    /* DataTypeConversion: '<S13>/Data Type Conversion21' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic9'
     *  Constant: '<S13>/Constant39'
     *  Constant: '<S13>/Constant40'
     *  Constant: '<S13>/Constant41'
     *  Constant: '<S13>/Constant42'
     *  Constant: '<S13>/Constant43'
     *  DataStoreWrite: '<S13>/Data Store Write20'
     *  Product: '<S13>/Divide9'
     *  Product: '<S13>/Product12'
     *  Product: '<S13>/Product13'
     */
    rtDW.Speed_Kp_Point = (int32_T)ceilf(ldexpf(SPD_WIDTH * MOTOR_INERTIA /
      (MOTOR_PN * MOTOR_FLUX * (1.5F * IMAX)), 15));

    /* Product: '<S13>/Product15' incorporates:
     *  ArithShift: '<S13>/Shift Arithmetic11'
     *  Constant: '<S13>/Constant47'
     *  Constant: '<S13>/Constant48'
     */
    rtb_Product18 = SPD_LIMIT * 32768.0F;

    /* DataTypeConversion: '<S13>/Data Type Conversion22' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write22'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Speed_Limit = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Speed_Limit = 0;
      }
    } else {
      rtDW.Speed_Limit = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion22' */

    /* Saturate: '<S13>/Saturation2' incorporates:
     *  Constant: '<S13>/Constant50'
     */
    if (CURR_OVER > IMAX) {
      v_0 = IMAX;
    } else if (CURR_OVER < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = CURR_OVER;
    }

    /* ArithShift: '<S13>/Shift Arithmetic13' incorporates:
     *  Gain: '<S13>/Gain5'
     *  Saturate: '<S13>/Saturation2'
     */
    rtb_Product18 = ldexpf(1.0F / IMAX * v_0, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion24' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write24'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Over = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Over = 0;
      }
    } else {
      rtDW.Curr_Over = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion24' */

    /* Saturate: '<S13>/Saturation' incorporates:
     *  Constant: '<S13>/Constant52'
     */
    if (OPEN_IQ > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ;
    }

    /* ArithShift: '<S13>/Shift Arithmetic14' incorporates:
     *  Constant: '<S13>/Constant53'
     *  Product: '<S13>/Divide12'
     *  Saturate: '<S13>/Saturation'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion25' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write25'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Iq_Point = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_Iq_Point = 0;
      }
    } else {
      rtDW.Open_Iq_Point = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion25' */

    /* Saturate: '<S13>/Saturation1' incorporates:
     *  Constant: '<S13>/Constant54'
     */
    if (OPEN_IQ_MIN > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ_MIN < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ_MIN;
    }

    /* ArithShift: '<S13>/Shift Arithmetic15' incorporates:
     *  Constant: '<S13>/Constant55'
     *  Product: '<S13>/Divide13'
     *  Saturate: '<S13>/Saturation1'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion26' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write26'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_IqMin_Point = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_IqMin_Point = 0;
      }
    } else {
      rtDW.Open_IqMin_Point = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion26' */

    /* Saturate: '<S13>/Saturation3' incorporates:
     *  Constant: '<S13>/Constant6'
     */
    if (OPEN_IQ_SLOW > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ_SLOW < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ_SLOW;
    }

    /* ArithShift: '<S13>/Shift Arithmetic16' incorporates:
     *  Constant: '<S13>/Constant56'
     *  Product: '<S13>/Divide14'
     *  Saturate: '<S13>/Saturation3'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion27' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write28'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Iq_Slow = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_Iq_Slow = 0;
      }
    } else {
      rtDW.Open_Iq_Slow = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion27' */

    /* Gain: '<S13>/Gain6' incorporates:
     *  Constant: '<S13>/Constant57'
     */
    rtb_Product18 = MOTOR_PN / 60.0F * OPEN_SPD_SLOW;

    /* DataTypeConversion: '<S13>/Data Type Conversion28' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write27'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Open_Slow = (int16_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Open_Slow = 0;
      }
    } else {
      rtDW.Open_Slow = (int16_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion28' */

    /* Saturate: '<S13>/Saturation4' incorporates:
     *  Constant: '<S13>/Constant58'
     */
    if (CURR_UNDER > IMAX) {
      v_0 = IMAX;
    } else if (CURR_UNDER < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = CURR_UNDER;
    }

    /* ArithShift: '<S13>/Shift Arithmetic17' incorporates:
     *  Gain: '<S13>/Gain7'
     *  Saturate: '<S13>/Saturation4'
     */
    rtb_Product18 = ldexpf(1.0F / IMAX * v_0, 15);

    /* DataTypeConversion: '<S13>/Data Type Conversion29' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write29'
     */
    v_0 = fabsf(rtb_Product18);
    if (v_0 < 8.388608E+6F) {
      if (v_0 >= 0.5F) {
        rtDW.Curr_Under = (int32_T)floorf(rtb_Product18 + 0.5F);
      } else {
        rtDW.Curr_Under = 0;
      }
    } else {
      rtDW.Curr_Under = (int32_T)rtb_Product18;
    }

    /* End of DataTypeConversion: '<S13>/Data Type Conversion29' */

    /* Product: '<S13>/Divide2' incorporates:
     *  Constant: '<S13>/Constant7'
     *  Constant: '<S13>/Constant8'
     */
    u = PWM_FRQ / (FOC_FRQ * 2.0);

    /* DataTypeConversion: '<S13>/Data Type Conversion3' incorporates:
     *  DataStoreWrite: '<S13>/Data Store Write4'
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

    /* End of DataTypeConversion: '<S13>/Data Type Conversion3' */
    /* End of Outputs for SubSystem: '<S1>/初始化模块' */
    /* End of SystemInitialize for SubSystem: '<Root>/FOC_PointModel' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
