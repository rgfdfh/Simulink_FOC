/*
 * File: FOC_PointModel.c
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

/* Named constants for Chart: '<S19>/速度缓冲' */
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
void FOC_PointModel_step(void)
{
  int32_T rtb_Gain;
  int32_T rtb_Min;
  int32_T rtb_ShiftArithmetic1_o;
  int32_T rtb_ShiftArithmetic2;
  int32_T rtb_ShiftArithmetic3;
  int32_T rtb_ShiftArithmetic9_e1;
  int32_T rtb_ShiftArithmetic_f;
  int32_T rtb_Sum_a;
  int32_T rtb_Sum_bk;
  int32_T y;
  int16_T rtb_Bias_o;
  int16_T rtb_FixPtSwitch_j;
  int16_T rtb_Sum10_i;
  int16_T rtb_Sum12;
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
    rtb_Min = -rtb_ShiftArithmetic_f;
  } else {
    rtb_Min = rtb_ShiftArithmetic_f;
  }

  /* End of Abs: '<S5>/Abs1' */

  /* Abs: '<S5>/Abs2' */
  if (rtb_ShiftArithmetic1_o < 0) {
    y = -rtb_ShiftArithmetic1_o;
  } else {
    y = rtb_ShiftArithmetic1_o;
  }

  /* End of Abs: '<S5>/Abs2' */

  /* MinMax: '<S5>/Max' */
  if (rtb_Min >= y) {
    y = rtb_Min;
  }

  /* Abs: '<S5>/Abs3' */
  if (rtb_ShiftArithmetic2 < 0) {
    rtb_Min = -rtb_ShiftArithmetic2;
  } else {
    rtb_Min = rtb_ShiftArithmetic2;
  }

  /* End of Abs: '<S5>/Abs3' */

  /* MinMax: '<S5>/Max' */
  if (y >= rtb_Min) {
    rtb_Min = y;
  }

  /* Outputs for Atomic SubSystem: '<S5>/PLL_LPF1' */
  /* ArithShift: '<S21>/Shift Arithmetic9' incorporates:
   *  Constant: '<S21>/Constant1'
   *  MinMax: '<S5>/Max'
   *  Product: '<S21>/Product11'
   *  Sum: '<S21>/Sum11'
   *  UnitDelay: '<S21>/Unit Delay9'
   */
  rtb_ShiftArithmetic9_e1 = (rtDW.UnitDelay9_DSTATE_j * 15 + rtb_Min) >> 4;

  /* Update for UnitDelay: '<S21>/Unit Delay9' */
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
  rtb_ShiftArithmetic3 = (rtU.v_bus * rtDW.Voltage_Conversion) >> ((int16_T)
    UDC_POINT_GAIN);

  /* Outputs for Enabled SubSystem: '<S5>/闭环错误判断' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  /* RelationalOperator: '<S5>/Relational Operator1' incorporates:
   *  Constant: '<S5>/闭环是4'
   *  UnitDelay: '<S5>/Unit Delay'
   */
  if (rtDW.Motor_State == 4) {
    if (!rtDW._MODE_p) {
      /* InitializeConditions for UnitDelay: '<S22>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_k = 0;
      rtDW._MODE_p = true;
    }

    /* Logic: '<S22>/Logical Operator' incorporates:
     *  ArithShift: '<S22>/Shift Arithmetic3'
     *  Constant: '<S22>/Constant'
     *  DataStoreRead: '<S22>/Data Store Read4'
     *  DataStoreRead: '<S22>/Data Store Read7'
     *  RelationalOperator: '<S22>/Relational Operator1'
     *  RelationalOperator: '<S22>/Relational Operator2'
     *  RelationalOperator: '<S22>/Relational Operator4'
     *  UnitDelay: '<S22>/Unit Delay'
     */
    rtb_LogicalOperator = ((rtb_ShiftArithmetic3 < 16384) ||
      (rtb_ShiftArithmetic9_e1 < rtDW.Curr_Under) || (rtDW.UnitDelay_DSTATE_k <
      (rtDW.Open_Hz >> 1)));

    /* If: '<S22>/If1' incorporates:
     *  DataTypeConversion: '<S22>/Data Type Conversion13'
     */
    rtPrevAction = rtDW.If1_ActiveSubsystem;
    rtAction = (int8_T)!rtb_LogicalOperator;
    rtDW.If1_ActiveSubsystem = rtAction;
    if (rtAction == 0) {
      if (rtPrevAction != 0) {
        /* InitializeConditions for IfAction SubSystem: '<S22>/SUM' incorporates:
         *  ActionPort: '<S23>/Action Port'
         */
        /* InitializeConditions for If: '<S22>/If1' incorporates:
         *  UnitDelay: '<S23>/Unit Delay2'
         */
        rtDW.UnitDelay2_DSTATE_a = 0;

        /* End of InitializeConditions for SubSystem: '<S22>/SUM' */
      }

      /* Outputs for IfAction SubSystem: '<S22>/SUM' incorporates:
       *  ActionPort: '<S23>/Action Port'
       */
      /* SignalConversion generated from: '<S23>/out' incorporates:
       *  UnitDelay: '<S23>/Unit Delay2'
       */
      rtb_ShiftArithmetic9_e1 = rtDW.UnitDelay2_DSTATE_a;

      /* Update for UnitDelay: '<S23>/Unit Delay2' incorporates:
       *  DataTypeConversion: '<S22>/Data Type Conversion12'
       *  Sum: '<S23>/Sum'
       */
      rtDW.UnitDelay2_DSTATE_a += rtb_LogicalOperator;

      /* End of Outputs for SubSystem: '<S22>/SUM' */
    } else {
      /* Outputs for IfAction SubSystem: '<S22>/ZERO' incorporates:
       *  ActionPort: '<S24>/Action Port'
       */
      /* SignalConversion generated from: '<S24>/out' incorporates:
       *  Constant: '<S24>/Constant'
       */
      rtb_ShiftArithmetic9_e1 = 0;

      /* End of Outputs for SubSystem: '<S22>/ZERO' */
    }

    /* End of If: '<S22>/If1' */

    /* Logic: '<S22>/OR1' incorporates:
     *  ArithShift: '<S22>/Shift Arithmetic1'
     *  DataStoreRead: '<S22>/Data Store Read'
     *  RelationalOperator: '<S22>/Relational Operator3'
     */
    rtDW.OR1 = (rtb_RelationalOperator || (rtb_ShiftArithmetic9_e1 >=
      (rtDW.FOC_FRQ_Point >> 1)));
  } else if (rtDW._MODE_p) {
    /* Disable for If: '<S22>/If1' */
    rtDW.If1_ActiveSubsystem = -1;
    rtDW._MODE_p = false;
  }

  /* End of RelationalOperator: '<S5>/Relational Operator1' */
  /* End of Outputs for SubSystem: '<S5>/闭环错误判断' */

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   *  Inport: '<Root>/Slow_OnOff'
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
      if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtDW.temporalCounter_i1 >= 250U) {
        rtDW.is_c2_FOC_PointModel = IN_SpeedupStage;
        rtDW.temporalCounter_i1 = 0U;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
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
      if ((rtU.Slow_OnOff == 1) && (rtDW.temporalCounter_i1 >= 250U)) {
        rtDW.is_c2_FOC_PointModel = IN_SlowOpen;
      } else if ((rtU.Motor_OnOff == 1) && (rtDW.temporalCounter_i1 >= 250U)) {
        rtDW.is_c2_FOC_PointModel = IN_AlignStage;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.Motor_State = 1U;
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
      } else {
        rtDW.Motor_State = 3U;
      }
      break;

     case IN_RunStage:
      if (rtDW.OR1) {
        rtDW.is_c2_FOC_PointModel = IN_EndStage;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
        rtDW.temporalCounter_i1 = 0U;
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
      if (rtb_RelationalOperator) {
        rtDW.is_c2_FOC_PointModel = IN_StopStage;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      } else if (rtDW.temporalCounter_i1 >= (uint32_T)ceil(OPEN_TIME / 4.0E-5 -
                  4.0000000000000006E-13)) {
        rtDW.is_c2_FOC_PointModel = IN_OpenStage;
      } else if (rtU.Motor_OnOff == 0) {
        rtDW.is_c2_FOC_PointModel = IN_IDLE;
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
        rtDW.Motor_State = 0U;

        /* Outport: '<Root>/Reset' */
        rtY.Reset = 1;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* Sum: '<S18>/Sum' incorporates:
   *  ArithShift: '<S18>/Shift Arithmetic'
   *  Constant: '<S18>/Constant4'
   *  Constant: '<S18>/Constant5'
   *  Product: '<S18>/Product4'
   */
  rtb_Bias_o = (int16_T)((int16_T)(((int16_T)UDC) - 6) - (int16_T)((((int16_T)
    UDC) * rtb_ShiftArithmetic3) >> 15));

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Bias_o > ((int16_T)UDC)) {
    rtb_Bias_o = ((int16_T)UDC);
  } else if (rtb_Bias_o < 0) {
    rtb_Bias_o = 0;
  }

  /* Sum: '<S18>/Sum2' incorporates:
   *  Constant: '<S18>/Constant1'
   *  Constant: '<S18>/Constant6'
   *  Product: '<S18>/Product'
   *  Saturate: '<S18>/Saturation'
   */
  rtb_Min = SPD_MAX - ((int16_T)SPD_REDUCE) * rtb_Bias_o;

  /* Switch: '<S55>/Switch2' incorporates:
   *  Inport: '<Root>/Spd_Ref'
   *  RelationalOperator: '<S55>/LowerRelop1'
   */
  if (rtU.Spd_Ref <= rtb_Min) {
    /* Switch: '<S55>/Switch' incorporates:
     *  Constant: '<S18>/Constant7'
     *  RelationalOperator: '<S55>/UpperRelop'
     */
    if (rtU.Spd_Ref < SPD_MIN) {
      rtb_Min = SPD_MIN;
    } else {
      rtb_Min = rtU.Spd_Ref;
    }

    /* End of Switch: '<S55>/Switch' */
  }

  /* End of Switch: '<S55>/Switch2' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Constant: '<S19>/Constant8'
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
     *  ActionPort: '<S12>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S12>/Constant2'
     *  SignalConversion generated from: '<S12>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S12>/Constant1'
     *  SignalConversion generated from: '<S12>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S12>/Constant3'
     *  SignalConversion generated from: '<S12>/Id'
     */
    rtDW.Merge2 = 0;

    /* End of Outputs for SubSystem: '<S1>/停止等待' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/预定位' incorporates:
     *  ActionPort: '<S20>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S20>/Constant3'
     *  SignalConversion generated from: '<S20>/Theta'
     */
    rtDW.Merge = 0U;

    /* Merge: '<S1>/Merge1' incorporates:
     *  Constant: '<S20>/Constant1'
     *  SignalConversion generated from: '<S20>/Iq'
     */
    rtDW.Merge1 = 0;

    /* Merge: '<S1>/Merge2' incorporates:
     *  DataStoreRead: '<S20>/Data Store Read3'
     *  Gain: '<S20>/Gain'
     */
    rtDW.Merge2 = (int16_T)(rtDW.Open_Iq_Point << 1);

    /* End of Outputs for SubSystem: '<S1>/预定位' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/加速强拖' incorporates:
       *  ActionPort: '<S15>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S50>/Unit Delay'
       *  UnitDelay: '<S51>/Unit Delay'
       */
      rtDW.UnitDelay_DSTATE_b = 0;
      rtDW.UnitDelay_DSTATE_d = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/加速强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/加速强拖' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    /* Sum: '<S50>/Sum' incorporates:
     *  ArithShift: '<S49>/Shift Arithmetic'
     *  ArithShift: '<S50>/Shift Arithmetic'
     *  ArithShift: '<S50>/这个是缩小周期增益的'
     *  Constant: '<S50>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read1'
     *  DataStoreRead: '<S50>/Data Store Read1'
     *  DataTypeConversion: '<S49>/Data Type Conversion3'
     *  Product: '<S50>/Product2'
     *  UnitDelay: '<S50>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Acceleration << 16) >> ((int16_T)
      TS_POINT_GAIN)) * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_d;

    /* Sum: '<S51>/Sum' incorporates:
     *  ArithShift: '<S51>/Shift Arithmetic'
     *  ArithShift: '<S51>/这个是缩小周期增益的'
     *  Constant: '<S51>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S51>/Data Store Read1'
     *  Product: '<S51>/Product2'
     *  Sum: '<S50>/Sum'
     *  UnitDelay: '<S51>/Unit Delay'
     */
    rtb_ShiftArithmetic9_e1 = (((rtb_ShiftArithmetic3 >> ((int16_T)TS_POINT_GAIN))
      * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_b;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S49>/Data Type Conversion2'
     *  SignalConversion generated from: '<S15>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic9_e1;

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S15>/Data Store Read3'
     */
    rtDW.Merge1 = rtDW.Open_Iq_Point;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S15>/Constant1'
     *  SignalConversion generated from: '<S15>/Id'
     */
    rtDW.Merge2 = 0;

    /* Update for UnitDelay: '<S51>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_b = rtb_ShiftArithmetic9_e1;

    /* Update for UnitDelay: '<S50>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_d = rtb_ShiftArithmetic3;

    /* End of Outputs for SubSystem: '<S1>/加速强拖' */
    break;

   case 3:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
       *  ActionPort: '<S16>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S53>/Delay'
       *  UnitDelay: '<S16>/Unit Delay1'
       */
      rtDW.icLoad_d = true;
      rtDW.UnitDelay1_DSTATE_g = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/恒速降力矩强拖' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/恒速降力矩强拖' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    /* Delay: '<S53>/Delay' incorporates:
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    if (rtDW.icLoad_d) {
      rtDW.Delay_DSTATE = rtDW.UnitDelay1_DSTATE_b;
    }

    /* Sum: '<S53>/Sum' incorporates:
     *  ArithShift: '<S16>/Shift Arithmetic'
     *  ArithShift: '<S53>/Shift Arithmetic'
     *  ArithShift: '<S53>/这个是缩小周期增益的'
     *  Constant: '<S53>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read6'
     *  DataStoreRead: '<S53>/Data Store Read1'
     *  DataTypeConversion: '<S16>/Data Type Conversion2'
     *  Delay: '<S53>/Delay'
     *  Product: '<S53>/Product2'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Hz << 16) >> ((int16_T)TS_POINT_GAIN)) *
      rtDW.Ts_Point) >> 15) + rtDW.Delay_DSTATE;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S16>/Data Type Conversion'
     *  SignalConversion generated from: '<S16>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic3;

    /* Merge: '<S1>/Merge2' incorporates:
     *  SignalConversion generated from: '<S16>/Id'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    rtDW.Merge2 = rtDW.UnitDelay1_DSTATE_g;

    /* Sum: '<S16>/Sum' incorporates:
     *  DataStoreRead: '<S16>/Data Store Read1'
     *  DataStoreRead: '<S16>/Data Store Read3'
     */
    rtb_Sum_ix = (int16_T)(rtDW.Open_Iq_Point - rtDW.Open_IqMin_Point);

    /* Switch: '<S52>/Switch2' incorporates:
     *  Bias: '<S16>/Bias'
     *  RelationalOperator: '<S52>/LowerRelop1'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    if ((int16_T)(rtDW.UnitDelay1_DSTATE_g + 1) <= rtb_Sum_ix) {
      /* Switch: '<S52>/Switch' incorporates:
       *  Constant: '<S16>/Constant7'
       *  RelationalOperator: '<S52>/UpperRelop'
       */
      if ((int16_T)(rtDW.UnitDelay1_DSTATE_g + 1) < 0) {
        rtb_Sum_ix = 0;
      } else {
        rtb_Sum_ix = (int16_T)(rtDW.UnitDelay1_DSTATE_g + 1);
      }

      /* End of Switch: '<S52>/Switch' */
    }

    /* End of Switch: '<S52>/Switch2' */

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S16>/Data Store Read2'
     *  Sum: '<S16>/Sum1'
     *  UnitDelay: '<S16>/Unit Delay1'
     */
    rtDW.Merge1 = (int16_T)(rtDW.Open_Iq_Point - rtDW.UnitDelay1_DSTATE_g);

    /* Update for Delay: '<S53>/Delay' */
    rtDW.icLoad_d = false;
    rtDW.Delay_DSTATE = rtb_ShiftArithmetic3;

    /* Update for UnitDelay: '<S16>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_g = rtb_Sum_ix;

    /* End of Outputs for SubSystem: '<S1>/恒速降力矩强拖' */
    break;

   case 4:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Delay: '<S19>/Delay'
       *  Delay: '<S19>/Delay1'
       *  UnitDelay: '<S19>/Unit Delay3'
       *  UnitDelay: '<S63>/Unit Delay'
       */
      rtDW.icLoad = true;
      rtDW.icLoad_l = true;
      rtDW.UnitDelay3_DSTATE_m = OPEN_SPD;
      rtDW.UnitDelay_DSTATE_g = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/观测器闭环//速度环' */

      /* SystemReset for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S1>/Switch Case' incorporates:
       *  Chart: '<S19>/速度缓冲'
       */
      rtDW.temporalCounter_i1_m = 0U;
      rtDW.is_active_c48_FOC_PointModel = 0U;
      rtDW.is_c48_FOC_PointModel = IN_NO_ACTIVE_CHILD;
      rtDW.SPD_Ref = 0;

      /* End of SystemReset for SubSystem: '<S1>/观测器闭环//速度环' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/观测器闭环//速度环' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  SignalConversion generated from: '<S19>/Obs_Theta'
     *  UnitDelay: '<S1>/Unit Delay4'
     */
    rtDW.Merge = rtY.Obs_Theta;

    /* Delay: '<S19>/Delay' incorporates:
     *  DataStoreRead: '<S19>/Data Store Read8'
     *  UnaryMinus: '<S19>/Unary Minus1'
     */
    if (rtDW.icLoad) {
      rtDW.Delay_DSTATE_h = (int16_T)-rtDW.Open_IqMin_Point;
    }

    /* Switch: '<S58>/FixPt Switch' incorporates:
     *  Constant: '<S58>/Constant'
     *  Delay: '<S19>/Delay'
     */
    if (rtDW.Delay_DSTATE_h > 0) {
      rtb_Bias_o = 0;
    } else {
      rtb_Bias_o = rtDW.Delay_DSTATE_h;
    }

    /* End of Switch: '<S58>/FixPt Switch' */

    /* Delay: '<S19>/Delay1' incorporates:
     *  DataStoreRead: '<S19>/Data Store Read5'
     *  DataStoreRead: '<S19>/Data Store Read7'
     *  Sum: '<S19>/Sum4'
     *  UnaryMinus: '<S19>/Unary Minus2'
     */
    if (rtDW.icLoad_l) {
      rtDW.Delay1_DSTATE = (int16_T)(rtDW.Open_IqMin_Point - rtDW.Open_Iq_Point);
    }

    /* Switch: '<S59>/FixPt Switch' incorporates:
     *  Constant: '<S59>/Constant'
     *  Delay: '<S19>/Delay1'
     */
    if (rtDW.Delay1_DSTATE > 0) {
      rtb_Sum_ix = 0;
    } else {
      rtb_Sum_ix = rtDW.Delay1_DSTATE;
    }

    rtb_ShiftArithmetic3 = ((int16_T)SPD_STEP);

    /* Chart: '<S19>/速度缓冲' incorporates:
     *  Constant: '<S19>/Constant12'
     *  Constant: '<S19>/Constant8'
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
      rtDW.SPD_Ref = rtb_Min;
    }

    /* End of Chart: '<S19>/速度缓冲' */

    /* Sum: '<S19>/Sum9' incorporates:
     *  UnitDelay: '<S19>/Unit Delay3'
     */
    rtb_ShiftArithmetic9_e1 = (int16_T)((int16_T)rtDW.SPD_Ref - (int16_T)
      rtDW.UnitDelay3_DSTATE_m);

    /* Switch: '<S57>/Switch2' incorporates:
     *  Constant: '<S19>/Constant8'
     *  RelationalOperator: '<S57>/LowerRelop1'
     */
    if (rtb_ShiftArithmetic9_e1 <= ((int16_T)SPD_STEP)) {
      /* UnaryMinus: '<S19>/Unary Minus' incorporates:
       *  Constant: '<S19>/Constant5'
       */
      rtb_ShiftArithmetic3 = -((int16_T)SPD_STEP);

      /* Switch: '<S57>/Switch' incorporates:
       *  Constant: '<S19>/Constant5'
       *  RelationalOperator: '<S57>/UpperRelop'
       *  UnaryMinus: '<S19>/Unary Minus'
       */
      if (rtb_ShiftArithmetic9_e1 >= -((int16_T)SPD_STEP)) {
        rtb_ShiftArithmetic3 = rtb_ShiftArithmetic9_e1;
      }

      /* End of Switch: '<S57>/Switch' */
    }

    /* End of Switch: '<S57>/Switch2' */

    /* Sum: '<S19>/Sum10' incorporates:
     *  UnitDelay: '<S19>/Unit Delay3'
     */
    rtb_ShiftArithmetic3 += rtDW.UnitDelay3_DSTATE_m;

    /* Sum: '<S19>/Sum2' incorporates:
     *  ArithShift: '<S19>/Shift Arithmetic'
     *  DataStoreRead: '<S19>/Data Store Read1'
     *  Product: '<S19>/Product'
     *  UnitDelay: '<S1>/Unit Delay3'
     */
    rtb_ShiftArithmetic9_e1 = (rtDW.Hz_RPM * rtDW.ShiftArithmetic13) >> 8;
    if ((rtb_ShiftArithmetic3 >= 0) && (rtb_ShiftArithmetic9_e1 <
         rtb_ShiftArithmetic3 - MAX_int32_T)) {
      rtb_Sum_a = MAX_int32_T;
    } else if ((rtb_ShiftArithmetic3 < 0) && (rtb_ShiftArithmetic9_e1 >
                rtb_ShiftArithmetic3 - MIN_int32_T)) {
      rtb_Sum_a = MIN_int32_T;
    } else {
      rtb_Sum_a = rtb_ShiftArithmetic3 - rtb_ShiftArithmetic9_e1;
    }

    if (rtb_Sum_a > 32767) {
      rtb_Sum_a = 32767;
    } else if (rtb_Sum_a < -32768) {
      rtb_Sum_a = -32768;
    }

    /* Sum: '<S63>/Sum' incorporates:
     *  ArithShift: '<S63>/Shift Arithmetic'
     *  ArithShift: '<S63>/这个是缩小周期增益的'
     *  Constant: '<S63>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S19>/Data Store Read4'
     *  DataStoreRead: '<S63>/Data Store Read1'
     *  Product: '<S63>/Product1'
     *  Product: '<S63>/Product2'
     *  Sum: '<S19>/Sum2'
     *  UnitDelay: '<S63>/Unit Delay'
     */
    rtb_ShiftArithmetic9_e1 = ((((rtDW.Ts_Point * (int16_T)rtb_Sum_a) >> 15) *
      rtDW.Speed_Ki_Point) >> ((int16_T)TS_POINT_GAIN)) +
      rtDW.UnitDelay_DSTATE_g;

    /* Switch: '<S64>/Switch2' incorporates:
     *  DataStoreRead: '<S63>/Data Store Read2'
     *  RelationalOperator: '<S64>/LowerRelop1'
     *  RelationalOperator: '<S64>/UpperRelop'
     *  Switch: '<S64>/Switch'
     */
    if (rtb_ShiftArithmetic9_e1 > rtDW.Speed_Limit) {
      rtb_ShiftArithmetic9_e1 = rtDW.Speed_Limit;
    } else if (rtb_ShiftArithmetic9_e1 < -1) {
      /* Switch: '<S64>/Switch' */
      rtb_ShiftArithmetic9_e1 = -1;
    }

    /* End of Switch: '<S64>/Switch2' */

    /* Sum: '<S56>/Sum' incorporates:
     *  DataStoreRead: '<S19>/Data Store Read3'
     *  Product: '<S56>/Product2'
     *  Sum: '<S19>/Sum2'
     */
    rtb_Sum_a = (int16_T)rtb_Sum_a * rtDW.Speed_Kp_Point
      + rtb_ShiftArithmetic9_e1;

    /* Switch: '<S62>/Switch2' incorporates:
     *  DataStoreRead: '<S56>/Data Store Read3'
     *  Gain: '<S56>/Gain'
     *  RelationalOperator: '<S62>/LowerRelop1'
     *  RelationalOperator: '<S62>/UpperRelop'
     *  Switch: '<S62>/Switch'
     */
    if (rtb_Sum_a > rtDW.Speed_Limit) {
      rtb_Sum_a = rtDW.Speed_Limit;
    } else if (rtb_Sum_a < -rtDW.Speed_Limit) {
      /* Switch: '<S62>/Switch' incorporates:
       *  Gain: '<S56>/Gain'
       */
      rtb_Sum_a = -rtDW.Speed_Limit;
    }

    /* End of Switch: '<S62>/Switch2' */

    /* DataTypeConversion: '<S19>/Data Type Conversion2' incorporates:
     *  Sum: '<S19>/Sum'
     */
    rtb_FixPtSwitch_j = (int16_T)(rtb_Sum_a - rtb_Bias_o);

    /* Merge: '<S1>/Merge1' incorporates:
     *  SignalConversion generated from: '<S19>/Iq'
     */
    rtDW.Merge1 = rtb_FixPtSwitch_j;

    /* Switch: '<S60>/FixPt Switch' incorporates:
     *  Constant: '<S60>/Constant'
     */
    if (rtb_FixPtSwitch_j > 0) {
      rtb_FixPtSwitch_j = 0;
    }

    /* Merge: '<S1>/Merge2' incorporates:
     *  Bias: '<S19>/Bias1'
     *  Constant: '<S19>/Constant9'
     *  Sum: '<S19>/Sum6'
     *  Switch: '<S59>/FixPt Switch'
     *  Switch: '<S60>/FixPt Switch'
     */
    rtDW.Merge2 = (int16_T)((int16_T)-rtb_FixPtSwitch_j - (int16_T)(rtb_Sum_ix -
      327));

    /* Update for Delay: '<S19>/Delay' incorporates:
     *  Bias: '<S19>/Bias'
     */
    rtDW.icLoad = false;
    rtDW.Delay_DSTATE_h = (int16_T)(rtb_Bias_o + 1);

    /* Update for Delay: '<S19>/Delay1' incorporates:
     *  Bias: '<S19>/Bias1'
     *  Constant: '<S19>/Constant9'
     *  Sum: '<S19>/Sum6'
     *  Switch: '<S59>/FixPt Switch'
     */
    rtDW.icLoad_l = false;
    rtDW.Delay1_DSTATE = (int16_T)((int16_T)(rtb_Sum_ix - 327) + 328);

    /* Update for UnitDelay: '<S19>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_m = rtb_ShiftArithmetic3;

    /* Update for UnitDelay: '<S63>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_g = rtb_ShiftArithmetic9_e1;

    /* End of Outputs for SubSystem: '<S1>/观测器闭环//速度环' */
    break;

   case 5:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S1>/慢速开环' incorporates:
       *  ActionPort: '<S17>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S1>/Switch Case' incorporates:
       *  UnitDelay: '<S54>/Unit Delay'
       */
      rtDW.UnitDelay_DSTATE_h = 0;

      /* End of InitializeConditions for SubSystem: '<S1>/慢速开环' */
    }

    /* Outputs for IfAction SubSystem: '<S1>/慢速开环' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    /* Sum: '<S54>/Sum' incorporates:
     *  ArithShift: '<S17>/Shift Arithmetic'
     *  ArithShift: '<S54>/Shift Arithmetic'
     *  ArithShift: '<S54>/这个是缩小周期增益的'
     *  Constant: '<S54>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S1>/Data Store Read2'
     *  DataStoreRead: '<S54>/Data Store Read1'
     *  DataTypeConversion: '<S17>/Data Type Conversion2'
     *  Product: '<S54>/Product2'
     *  UnitDelay: '<S54>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = ((((rtDW.Open_Slow << 16) >> ((int16_T)TS_POINT_GAIN))
      * rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_h;

    /* Merge: '<S1>/Merge' incorporates:
     *  DataTypeConversion: '<S17>/Data Type Conversion'
     *  SignalConversion generated from: '<S17>/Theta'
     */
    rtDW.Merge = (uint16_T)rtb_ShiftArithmetic3;

    /* Merge: '<S1>/Merge1' incorporates:
     *  DataStoreRead: '<S17>/Data Store Read6'
     */
    rtDW.Merge1 = rtDW.Open_Iq_Slow;

    /* Merge: '<S1>/Merge2' incorporates:
     *  Constant: '<S17>/Constant8'
     *  SignalConversion generated from: '<S17>/Id'
     */
    rtDW.Merge2 = 0;

    /* Update for UnitDelay: '<S54>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_h = rtb_ShiftArithmetic3;

    /* End of Outputs for SubSystem: '<S1>/慢速开环' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* Lookup_n-D: '<S11>/Sin1' incorporates:
   *  ArithShift: '<S11>/Shift Arithmetic'
   *  Constant: '<S11>/Constant3'
   *  Sum: '<S11>/Sum2'
   */
  rtb_Bias_o = rtConstP.pooled16[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    (uint16_T)(rtDW.Merge + 16512U) >> 7), 1U)];

  /* ArithShift: '<S4>/Shift Arithmetic' incorporates:
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S4>/Add2'
   */
  rtb_ShiftArithmetic9_e1 = ((rtb_ShiftArithmetic1_o - rtb_ShiftArithmetic2) *
    18918) >> 15;

  /* Lookup_n-D: '<S11>/Sin' incorporates:
   *  ArithShift: '<S11>/Shift Arithmetic1'
   *  Constant: '<S11>/Constant1'
   *  Sum: '<S11>/Sum1'
   *  Sum: '<S13>/Sum4'
   */
  rtb_Sum_ix = rtConstP.pooled16[plook_u32u16_even0ckag((uint16_T)((uint32_T)
    (uint16_T)(rtDW.Merge + 128U) >> 7), 1U)];

  /* RelationalOperator: '<S1>/Relational Operator' incorporates:
   *  Constant: '<S1>/Constant3'
   */
  rtb_RelationalOperator = (rtDW.Motor_State > 0);

  /* Outputs for Enabled SubSystem: '<S1>/idq_Controller' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (rtb_RelationalOperator) {
    if (!rtDW.idq_Controller_MODE) {
      /* InitializeConditions for UnitDelay: '<S10>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE_j = 0;

      /* InitializeConditions for UnitDelay: '<S41>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S43>/Unit Delay' */
      rtDW.UnitDelay_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S10>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_d = 0;

      /* InitializeConditions for UnitDelay: '<S46>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_f = 0;
      rtDW.idq_Controller_MODE = true;
    }

    /* Sum: '<S10>/Sum5' incorporates:
     *  Sum: '<S10>/Sum13'
     *  UnitDelay: '<S10>/Unit Delay4'
     *  UnitDelay: '<S41>/Unit Delay5'
     */
    rtb_FixPtSwitch_j = (int16_T)((int16_T)(rtDW.UnitDelay5_DSTATE + rtDW.Merge2)
      - rtDW.UnitDelay4_DSTATE_j);

    /* Switch: '<S40>/Switch2' incorporates:
     *  Constant: '<S10>/Constant1'
     *  Constant: '<S10>/Constant2'
     *  RelationalOperator: '<S40>/LowerRelop1'
     *  RelationalOperator: '<S40>/UpperRelop'
     *  Switch: '<S40>/Switch'
     */
    if (rtb_FixPtSwitch_j > ((int16_T)CURR_STEP)) {
      rtb_FixPtSwitch_j = ((int16_T)CURR_STEP);
    } else if (rtb_FixPtSwitch_j < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S40>/Switch' incorporates:
       *  Constant: '<S10>/Constant1'
       */
      rtb_FixPtSwitch_j = (int16_T)-((int16_T)CURR_STEP);
    }

    /* Sum: '<S10>/Sum6' incorporates:
     *  Switch: '<S40>/Switch2'
     *  UnitDelay: '<S10>/Unit Delay4'
     */
    rtb_FixPtSwitch_j += rtDW.UnitDelay4_DSTATE_j;

    /* Sum: '<S10>/Sum1' incorporates:
     *  ArithShift: '<S8>/Shift Arithmetic'
     *  Lookup_n-D: '<S11>/Sin1'
     *  Product: '<S8>/Product'
     *  Product: '<S8>/Product1'
     *  Sum: '<S13>/Sum4'
     *  Sum: '<S8>/Add2'
     */
    rtb_ShiftArithmetic3 = rtb_FixPtSwitch_j - ((rtb_ShiftArithmetic_f *
      rtb_Bias_o + rtb_ShiftArithmetic9_e1 * rtb_Sum_ix) >> 15);

    /* ArithShift: '<S43>/Shift Arithmetic' incorporates:
     *  ArithShift: '<S46>/Shift Arithmetic'
     *  Constant: '<S43>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S10>/Data Store Read5'
     */
    rtb_Sum_bk = rtDW.Curr_Ki_Point >> ((int16_T)TS_POINT_GAIN);

    /* Sum: '<S43>/Sum' incorporates:
     *  ArithShift: '<S43>/Shift Arithmetic'
     *  ArithShift: '<S43>/这个是缩小周期增益的'
     *  DataStoreRead: '<S43>/Data Store Read1'
     *  Product: '<S43>/Product1'
     *  Product: '<S43>/Product2'
     *  UnitDelay: '<S43>/Unit Delay'
     */
    rtb_Sum_a = ((rtDW.Ts_Point * rtb_ShiftArithmetic3) >> 15) * rtb_Sum_bk +
      rtDW.UnitDelay_DSTATE;

    /* Switch: '<S44>/Switch2' incorporates:
     *  DataStoreRead: '<S43>/Data Store Read3'
     *  Gain: '<S43>/Gain'
     *  RelationalOperator: '<S44>/LowerRelop1'
     *  RelationalOperator: '<S44>/UpperRelop'
     *  Switch: '<S44>/Switch'
     */
    if (rtb_Sum_a > rtDW.Curr_Limit) {
      rtb_Sum_a = rtDW.Curr_Limit;
    } else if (rtb_Sum_a < -rtDW.Curr_Limit) {
      /* Switch: '<S44>/Switch' incorporates:
       *  Gain: '<S43>/Gain'
       */
      rtb_Sum_a = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S44>/Switch2' */

    /* Sum: '<S37>/Sum' incorporates:
     *  DataStoreRead: '<S10>/Data Store Read2'
     *  Product: '<S37>/Product2'
     */
    rtb_ShiftArithmetic3 = rtb_ShiftArithmetic3 * rtDW.Curr_Kp_Point + rtb_Sum_a;

    /* Switch: '<S42>/Switch2' incorporates:
     *  DataStoreRead: '<S37>/Data Store Read3'
     *  Gain: '<S37>/Gain'
     *  RelationalOperator: '<S42>/LowerRelop1'
     *  RelationalOperator: '<S42>/UpperRelop'
     *  Switch: '<S42>/Switch'
     */
    if (rtb_ShiftArithmetic3 > rtDW.Curr_Limit) {
      rtb_ShiftArithmetic3 = rtDW.Curr_Limit;
    } else if (rtb_ShiftArithmetic3 < -rtDW.Curr_Limit) {
      /* Switch: '<S42>/Switch' incorporates:
       *  Gain: '<S37>/Gain'
       */
      rtb_ShiftArithmetic3 = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S42>/Switch2' */

    /* Sum: '<S10>/Sum9' incorporates:
     *  Sum: '<S10>/Sum14'
     *  UnitDelay: '<S10>/Unit Delay3'
     */
    rtb_Sum12 = (int16_T)(rtDW.Merge1 - rtDW.UnitDelay3_DSTATE_d);

    /* Switch: '<S39>/Switch2' incorporates:
     *  Constant: '<S10>/Constant3'
     *  Constant: '<S10>/Constant8'
     *  RelationalOperator: '<S39>/LowerRelop1'
     *  RelationalOperator: '<S39>/UpperRelop'
     *  Switch: '<S39>/Switch'
     */
    if (rtb_Sum12 > ((int16_T)CURR_STEP)) {
      rtb_Sum12 = ((int16_T)CURR_STEP);
    } else if (rtb_Sum12 < (int16_T)-((int16_T)CURR_STEP)) {
      /* Switch: '<S39>/Switch' incorporates:
       *  Constant: '<S10>/Constant3'
       */
      rtb_Sum12 = (int16_T)-((int16_T)CURR_STEP);
    }

    /* End of Switch: '<S39>/Switch2' */

    /* Sum: '<S10>/Sum10' incorporates:
     *  UnitDelay: '<S10>/Unit Delay3'
     */
    rtb_Sum10_i = (int16_T)(rtb_Sum12 + rtDW.UnitDelay3_DSTATE_d);

    /* Sum: '<S10>/Sum8' incorporates:
     *  ArithShift: '<S8>/Shift Arithmetic1'
     *  Lookup_n-D: '<S11>/Sin1'
     *  Product: '<S8>/Product2'
     *  Product: '<S8>/Product3'
     *  Sum: '<S13>/Sum4'
     *  Sum: '<S8>/Add1'
     */
    rtb_Min = rtb_Sum10_i - ((rtb_ShiftArithmetic9_e1 * rtb_Bias_o -
      rtb_ShiftArithmetic_f * rtb_Sum_ix) >> 15);

    /* Sum: '<S46>/Sum' incorporates:
     *  ArithShift: '<S46>/这个是缩小周期增益的'
     *  DataStoreRead: '<S46>/Data Store Read1'
     *  Product: '<S46>/Product1'
     *  Product: '<S46>/Product2'
     *  UnitDelay: '<S46>/Unit Delay'
     */
    rtb_Sum_bk = ((rtDW.Ts_Point * rtb_Min) >> 15) * rtb_Sum_bk +
      rtDW.UnitDelay_DSTATE_f;

    /* Switch: '<S47>/Switch2' incorporates:
     *  DataStoreRead: '<S46>/Data Store Read3'
     *  Gain: '<S46>/Gain'
     *  RelationalOperator: '<S47>/LowerRelop1'
     *  RelationalOperator: '<S47>/UpperRelop'
     *  Switch: '<S47>/Switch'
     */
    if (rtb_Sum_bk > rtDW.Curr_Limit) {
      rtb_Sum_bk = rtDW.Curr_Limit;
    } else if (rtb_Sum_bk < -rtDW.Curr_Limit) {
      /* Switch: '<S47>/Switch' incorporates:
       *  Gain: '<S46>/Gain'
       */
      rtb_Sum_bk = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S47>/Switch2' */

    /* Sum: '<S38>/Sum' incorporates:
     *  DataStoreRead: '<S10>/Data Store Read6'
     *  Product: '<S38>/Product2'
     */
    rtb_Min = rtb_Min * rtDW.Curr_Kp_Point + rtb_Sum_bk;

    /* Switch: '<S45>/Switch2' incorporates:
     *  DataStoreRead: '<S38>/Data Store Read3'
     *  Gain: '<S38>/Gain'
     *  RelationalOperator: '<S45>/LowerRelop1'
     *  RelationalOperator: '<S45>/UpperRelop'
     *  Switch: '<S45>/Switch'
     */
    if (rtb_Min > rtDW.Curr_Limit) {
      rtb_Min = rtDW.Curr_Limit;
    } else if (rtb_Min < -rtDW.Curr_Limit) {
      /* Switch: '<S45>/Switch' incorporates:
       *  Gain: '<S38>/Gain'
       */
      rtb_Min = -rtDW.Curr_Limit;
    }

    /* End of Switch: '<S45>/Switch2' */

    /* ArithShift: '<S10>/Shift Arithmetic4' incorporates:
     *  ArithShift: '<S10>/Shift Arithmetic2'
     *  Sum: '<S35>/Sum1'
     */
    rtDW.Ud = rtb_ShiftArithmetic3 >> 16;

    /* ArithShift: '<S10>/Shift Arithmetic5' incorporates:
     *  ArithShift: '<S10>/Shift Arithmetic3'
     *  UnitDelay: '<S6>/Unit Delay9'
     */
    rtDW.Uq = rtb_Min >> 16;

    /* Sum: '<S41>/Sum12' incorporates:
     *  Constant: '<S41>/Constant'
     *  DataTypeConversion: '<S41>/Data Type Conversion5'
     *  DataTypeConversion: '<S41>/Data Type Conversion6'
     *  Math: '<S41>/Square2'
     *  Math: '<S41>/Square3'
     *  Sqrt: '<S41>/Sqrt1'
     *  Sum: '<S41>/Sum11'
     */
    rtb_Sum12 = (int16_T)(14746 - rt_sqrt_Us32_Ys16_Is32__s((int16_T)rtDW.Ud *
      (int16_T)rtDW.Ud + (int16_T)rtDW.Uq * (int16_T)rtDW.Uq));

    /* Update for UnitDelay: '<S10>/Unit Delay4' */
    rtDW.UnitDelay4_DSTATE_j = rtb_FixPtSwitch_j;

    /* Switch: '<S48>/FixPt Switch' */
    if (rtb_Sum12 > 0) {
      /* Update for UnitDelay: '<S41>/Unit Delay5' incorporates:
       *  Constant: '<S48>/Constant'
       */
      rtDW.UnitDelay5_DSTATE = 0;
    } else {
      /* Update for UnitDelay: '<S41>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE = rtb_Sum12;
    }

    /* End of Switch: '<S48>/FixPt Switch' */

    /* Update for UnitDelay: '<S43>/Unit Delay' */
    rtDW.UnitDelay_DSTATE = rtb_Sum_a;

    /* Update for UnitDelay: '<S10>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_d = rtb_Sum10_i;

    /* Update for UnitDelay: '<S46>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_f = rtb_Sum_bk;
  } else {
    rtDW.idq_Controller_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/idq_Controller' */

  /* ArithShift: '<S2>/Shift Arithmetic' incorporates:
   *  Lookup_n-D: '<S11>/Sin1'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S13>/Sum4'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add'
   */
  rtb_Sum_a = (rtDW.Ud * rtb_Bias_o - rtDW.Uq * rtb_Sum_ix) >> 15;

  /* ArithShift: '<S2>/Shift Arithmetic1' incorporates:
   *  Lookup_n-D: '<S11>/Sin1'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S13>/Sum4'
   *  Sum: '<S1>/Sum5'
   *  Sum: '<S1>/Sum6'
   *  Sum: '<S2>/Add1'
   */
  rtb_Min = (rtDW.Ud * rtb_Sum_ix + rtDW.Uq * rtb_Bias_o) >> 15;

  /* Outputs for Enabled SubSystem: '<S1>/Observers' incorporates:
   *  EnablePort: '<S7>/Enable'
   */
  if (rtb_RelationalOperator) {
    if (!rtDW.Observers_MODE) {
      /* SystemReset for Atomic SubSystem: '<S7>/SMO' */
      /* InitializeConditions for UnitDelay: '<S26>/Unit Delay4' */
      rtDW.UnitDelay4_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S26>/Unit Delay6' */
      rtDW.UnitDelay6_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S33>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S26>/Unit Delay2' */
      rtDW.UnitDelay2_DSTATE = 0;

      /* InitializeConditions for UnitDelay: '<S26>/Unit Delay3' */
      rtDW.UnitDelay3_DSTATE_l = 0;

      /* InitializeConditions for UnitDelay: '<S34>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE_m = 0;

      /* End of SystemReset for SubSystem: '<S7>/SMO' */

      /* SystemReset for Atomic SubSystem: '<S7>/PLL' */
      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE_p = 0;

      /* InitializeConditions for UnitDelay: '<S25>/Unit Delay' */
      rtY.Obs_Theta = 0U;

      /* InitializeConditions for UnitDelay: '<S31>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_p = 0;

      /* InitializeConditions for UnitDelay: '<S29>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_m = 0;

      /* End of SystemReset for SubSystem: '<S7>/PLL' */
      rtDW.Observers_MODE = true;
    }

    /* Outputs for Atomic SubSystem: '<S7>/SMO' */
    /* Sum: '<S26>/Sum4' incorporates:
     *  ArithShift: '<S26>/Shift Arithmetic3'
     *  ArithShift: '<S26>/Shift Arithmetic5'
     *  ArithShift: '<S26>/Shift Arithmetic8'
     *  DataStoreRead: '<S26>/Data Store Read11'
     *  DataStoreRead: '<S26>/Data Store Read7'
     *  DataStoreRead: '<S26>/Data Store Read8'
     *  Product: '<S26>/Product5'
     *  Product: '<S26>/Product6'
     *  Product: '<S26>/Product8'
     *  Sum: '<S26>/Sum3'
     *  UnitDelay: '<S26>/Unit Delay4'
     *  UnitDelay: '<S26>/Unit Delay6'
     */
    rtb_ShiftArithmetic3 = (((((rtDW.Obs_VtoI * rtb_Sum_a) >> 1) -
      rtDW.UnitDelay4_DSTATE) * rtDW.SMO_Gain2) >> 15) +
      ((rtDW.UnitDelay6_DSTATE * rtDW.SMO_Gain1) >> 15);

    /* Sum: '<S26>/Sum5' */
    y = rtb_ShiftArithmetic3 - rtb_ShiftArithmetic_f;

    /* Saturate: '<S26>/Saturation1' */
    if (y > 32767) {
      y = 32767;
    } else if (y < -32767) {
      y = -32767;
    }

    /* Sum: '<S33>/Sum2' incorporates:
     *  ArithShift: '<S33>/Shift Arithmetic4'
     *  DataStoreRead: '<S26>/Data Store Read14'
     *  DataStoreRead: '<S33>/Data Store Read1'
     *  Product: '<S26>/Product9'
     *  Product: '<S33>/Product1'
     *  Saturate: '<S26>/Saturation1'
     *  Sum: '<S33>/Sum1'
     *  UnitDelay: '<S33>/Unit Delay1'
     */
    rtb_Sum_bk = (((rtDW.SMO_K * y - rtDW.UnitDelay1_DSTATE) *
                   rtDW.LPF_FRQ_Point) >> 4) + rtDW.UnitDelay1_DSTATE;

    /* Sum: '<S26>/Sum7' incorporates:
     *  ArithShift: '<S26>/Shift Arithmetic4'
     *  ArithShift: '<S26>/Shift Arithmetic6'
     *  ArithShift: '<S26>/Shift Arithmetic9'
     *  DataStoreRead: '<S26>/Data Store Read13'
     *  DataStoreRead: '<S26>/Data Store Read15'
     *  DataStoreRead: '<S26>/Data Store Read16'
     *  Product: '<S26>/Product10'
     *  Product: '<S26>/Product11'
     *  Product: '<S26>/Product12'
     *  Sum: '<S26>/Sum2'
     *  UnitDelay: '<S26>/Unit Delay2'
     *  UnitDelay: '<S26>/Unit Delay3'
     */
    rtb_Gain = (((((rtb_Min * rtDW.Obs_VtoI) >> 1) - rtDW.UnitDelay2_DSTATE) *
                 rtDW.SMO_Gain2) >> 15) + ((rtDW.SMO_Gain1 *
      rtDW.UnitDelay3_DSTATE_l) >> 15);

    /* Sum: '<S26>/Sum8' */
    y = rtb_Gain - rtb_ShiftArithmetic9_e1;

    /* Saturate: '<S26>/Saturation2' */
    if (y > 32767) {
      y = 32767;
    } else if (y < -32767) {
      y = -32767;
    }

    /* Sum: '<S34>/Sum2' incorporates:
     *  ArithShift: '<S34>/Shift Arithmetic4'
     *  DataStoreRead: '<S26>/Data Store Read12'
     *  DataStoreRead: '<S34>/Data Store Read1'
     *  Product: '<S26>/Product13'
     *  Product: '<S34>/Product1'
     *  Saturate: '<S26>/Saturation2'
     *  Sum: '<S34>/Sum1'
     *  UnitDelay: '<S34>/Unit Delay1'
     */
    rtb_ShiftArithmetic9_e1 = (((y * rtDW.SMO_K - rtDW.UnitDelay1_DSTATE_m) *
      rtDW.LPF_FRQ_Point) >> 4) + rtDW.UnitDelay1_DSTATE_m;

    /* Update for UnitDelay: '<S26>/Unit Delay4' incorporates:
     *  Sum: '<S26>/Sum9'
     */
    rtDW.UnitDelay4_DSTATE = rtb_Sum_bk;

    /* Update for UnitDelay: '<S26>/Unit Delay6' */
    rtDW.UnitDelay6_DSTATE = rtb_ShiftArithmetic3;

    /* Update for UnitDelay: '<S33>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE = rtb_Sum_bk;

    /* Update for UnitDelay: '<S26>/Unit Delay2' incorporates:
     *  Sum: '<S26>/Sum'
     */
    rtDW.UnitDelay2_DSTATE = rtb_ShiftArithmetic9_e1;

    /* Update for UnitDelay: '<S26>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_l = rtb_Gain;

    /* Update for UnitDelay: '<S34>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_m = rtb_ShiftArithmetic9_e1;

    /* End of Outputs for SubSystem: '<S7>/SMO' */

    /* Outputs for Atomic SubSystem: '<S7>/PLL' */
    /* Sum: '<S25>/Sum4' incorporates:
     *  ArithShift: '<S25>/Shift Arithmetic7'
     *  ArithShift: '<S25>/Shift Arithmetic8'
     *  ArithShift: '<S28>/Shift Arithmetic'
     *  ArithShift: '<S28>/Shift Arithmetic1'
     *  Constant: '<S28>/Constant1'
     *  Constant: '<S28>/Constant3'
     *  Lookup_n-D: '<S28>/Sin'
     *  Lookup_n-D: '<S28>/Sin1'
     *  Product: '<S25>/Product3'
     *  Product: '<S25>/Product4'
     *  Sum: '<S28>/Sum1'
     *  Sum: '<S28>/Sum2'
     *  UnitDelay: '<S25>/Unit Delay'
     */
    rtb_ShiftArithmetic3 = -((rtConstP.pooled16[plook_u32u16_even0ckag((uint16_T)
      ((uint32_T)(uint16_T)(rtY.Obs_Theta + 16512U) >> 7), 1U)] * rtb_Sum_bk) >>
      15) - ((rtConstP.pooled16[plook_u32u16_even0ckag((uint16_T)((uint32_T)
                (uint16_T)(rtY.Obs_Theta + 128U) >> 7), 1U)] *
              rtb_ShiftArithmetic9_e1) >> 15);

    /* Sum: '<S31>/Sum' incorporates:
     *  ArithShift: '<S31>/Shift Arithmetic'
     *  ArithShift: '<S31>/这个是缩小周期增益的'
     *  Constant: '<S31>/周期定点化适当放大2^n'
     *  DataStoreRead: '<S25>/Data Store Read8'
     *  DataStoreRead: '<S31>/Data Store Read1'
     *  Product: '<S31>/Product1'
     *  Product: '<S31>/Product2'
     *  UnitDelay: '<S31>/Unit Delay'
     */
    rtb_ShiftArithmetic9_e1 = ((rtDW.Ts_Point * rtb_ShiftArithmetic3) >> 15) *
      (rtDW.PLL_Ki >> ((int16_T)TS_POINT_GAIN)) + rtDW.UnitDelay_DSTATE_p;

    /* Switch: '<S32>/Switch2' incorporates:
     *  DataStoreRead: '<S31>/Data Store Read3'
     *  Gain: '<S31>/Gain'
     *  RelationalOperator: '<S32>/LowerRelop1'
     *  RelationalOperator: '<S32>/UpperRelop'
     *  Switch: '<S32>/Switch'
     */
    if (rtb_ShiftArithmetic9_e1 > rtDW.PLL_Limit) {
      rtb_ShiftArithmetic9_e1 = rtDW.PLL_Limit;
    } else if (rtb_ShiftArithmetic9_e1 < -rtDW.PLL_Limit) {
      /* Switch: '<S32>/Switch' incorporates:
       *  Gain: '<S31>/Gain'
       */
      rtb_ShiftArithmetic9_e1 = -rtDW.PLL_Limit;
    }

    /* End of Switch: '<S32>/Switch2' */

    /* Sum: '<S27>/Sum' incorporates:
     *  DataStoreRead: '<S25>/Data Store Read7'
     *  Product: '<S27>/Product2'
     */
    rtb_ShiftArithmetic3 = rtb_ShiftArithmetic3 * rtDW.PLL_Kp +
      rtb_ShiftArithmetic9_e1;

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
    rtb_Sum_bk = (((rtb_ShiftArithmetic3 >> ((int16_T)TS_POINT_GAIN)) *
                   rtDW.Ts_Point) >> 15) + rtDW.UnitDelay_DSTATE_m;

    /* ArithShift: '<S25>/Shift Arithmetic13' incorporates:
     *  Sum: '<S35>/Sum1'
     */
    rtDW.ShiftArithmetic13 = rtb_ShiftArithmetic3 >> 16;

    /* Outport: '<Root>/Obs_Theta' incorporates:
     *  ArithShift: '<S25>/Shift Arithmetic10'
     *  ArithShift: '<S25>/Shift Arithmetic15'
     *  Bias: '<S25>/Bias'
     *  DataStoreRead: '<S25>/Data Store Read6'
     *  DataTypeConversion: '<S25>/Data Type Conversion8'
     *  Lookup_n-D: '<S25>/atan256'
     *  Product: '<S25>/Product2'
     *  Sum: '<S25>/Sum1'
     *  Sum: '<S25>/Sum3'
     *  UnitDelay: '<S25>/Unit Delay1'
     */
    rtY.Obs_Theta = (uint16_T)((uint32_T)
      rtConstP.atan256_tableData[plook_u32s32_even0ckag((((rtDW.DIV_LPF_FRQ << 8)
      * rtDW.UnitDelay1_DSTATE_p) >> 15) + 1, 1)] + (uint16_T)rtb_Sum_bk);

    /* Update for UnitDelay: '<S25>/Unit Delay1' */
    rtDW.UnitDelay1_DSTATE_p = rtDW.ShiftArithmetic13;

    /* Update for UnitDelay: '<S31>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_p = rtb_ShiftArithmetic9_e1;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_m = rtb_Sum_bk;

    /* End of Outputs for SubSystem: '<S7>/PLL' */
  } else {
    rtDW.Observers_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S1>/Observers' */

  /* Outputs for Atomic SubSystem: '<S1>/LPF' */
  /* Saturate: '<S6>/Saturation' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  if (((int16_T)SPD_LPF_LEVEL) > 15) {
    rtb_Bias_o = 15;
  } else if (((int16_T)SPD_LPF_LEVEL) < 0) {
    rtb_Bias_o = 0;
  } else {
    rtb_Bias_o = ((int16_T)SPD_LPF_LEVEL);
  }

  /* End of Saturate: '<S6>/Saturation' */

  /* ArithShift: '<S6>/Shift Arithmetic9' incorporates:
   *  DataStoreRead: '<S1>/Data Store Read3'
   *  Product: '<S1>/Product4'
   *  Product: '<S6>/Product10'
   *  Product: '<S6>/Product11'
   *  Sum: '<S6>/Sum10'
   *  Sum: '<S6>/Sum11'
   *  UnitDelay: '<S6>/Unit Delay9'
   */
  rtb_ShiftArithmetic9_e1 = ((16 - rtb_Bias_o) * (rtDW.ShiftArithmetic13 *
    rtDW.Hz_RPM) + rtDW.UnitDelay9_DSTATE * rtb_Bias_o) >> 4;

  /* Update for UnitDelay: '<S6>/Unit Delay9' */
  rtDW.UnitDelay9_DSTATE = rtb_ShiftArithmetic9_e1;

  /* End of Outputs for SubSystem: '<S1>/LPF' */

  /* ArithShift: '<S35>/Shift Arithmetic' incorporates:
   *  Gain: '<S35>/Gain1'
   */
  rtb_Min = (28377 * rtb_Min) >> 15;

  /* ArithShift: '<S35>/Shift Arithmetic1' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic'
   */
  rtb_ShiftArithmetic3 = rtb_Sum_a >> 1;

  /* Sum: '<S35>/Sum' */
  rtb_Sum_bk = rtb_Min - rtb_ShiftArithmetic3;

  /* Sum: '<S35>/Sum1' */
  rtb_ShiftArithmetic3 = -rtb_Min - rtb_ShiftArithmetic3;

  /* ArithShift: '<S9>/Shift Arithmetic' incorporates:
   *  DataStoreRead: '<S9>/Data Store Read3'
   */
  rtb_Bias_o = (int16_T)(rtDW.PWM_TH >> 1);

  /* MinMax: '<S36>/Min' */
  if (rtb_Sum_a <= rtb_Sum_bk) {
    rtb_Min = rtb_Sum_a;
  } else {
    rtb_Min = rtb_Sum_bk;
  }

  /* MinMax: '<S36>/Min1' */
  if (rtb_Sum_a >= rtb_Sum_bk) {
    y = rtb_Sum_a;
  } else {
    y = rtb_Sum_bk;
  }

  /* MinMax: '<S36>/Min' */
  if (rtb_Min > rtb_ShiftArithmetic3) {
    rtb_Min = rtb_ShiftArithmetic3;
  }

  /* MinMax: '<S36>/Min1' */
  if (y < rtb_ShiftArithmetic3) {
    y = rtb_ShiftArithmetic3;
  }

  /* UnaryMinus: '<S36>/Unary Minus' incorporates:
   *  ArithShift: '<S36>/Shift Arithmetic'
   *  MinMax: '<S36>/Min'
   *  MinMax: '<S36>/Min1'
   *  Sum: '<S36>/Sum'
   */
  rtb_Min = -((rtb_Min + y) >> 1);

  /* Outputs for Enabled SubSystem: '<S1>/切闭环角度差' incorporates:
   *  EnablePort: '<S13>/Enable'
   */
  /* RelationalOperator: '<S1>/Relational Operator1' incorporates:
   *  Constant: '<S1>/闭环是4'
   */
  if (rtDW.Motor_State < 4) {
    if (!rtDW._MODE) {
      /* InitializeConditions for UnitDelay: '<S13>/Unit Delay5' */
      rtDW.UnitDelay5_DSTATE_i = 0U;
      rtDW._MODE = true;
    }

    /* Update for UnitDelay: '<S13>/Unit Delay7' incorporates:
     *  UnitDelay: '<S13>/Unit Delay5'
     */
    rtDW.UnitDelay7_DSTATE = rtDW.UnitDelay5_DSTATE_i;

    /* Update for UnitDelay: '<S13>/Unit Delay6' */
    rtDW.UnitDelay6_DSTATE_a = rtDW.Merge;

    /* Update for UnitDelay: '<S13>/Unit Delay5' incorporates:
     *  Outport: '<Root>/Obs_Theta'
     */
    rtDW.UnitDelay5_DSTATE_i = rtY.Obs_Theta;
  } else {
    rtDW._MODE = false;
  }

  /* End of RelationalOperator: '<S1>/Relational Operator1' */
  /* End of Outputs for SubSystem: '<S1>/切闭环角度差' */

  /* Update for Enabled SubSystem: '<S5>/闭环错误判断' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  if (rtDW._MODE_p) {
    /* Update for UnitDelay: '<S22>/Unit Delay' */
    rtDW.UnitDelay_DSTATE_k = rtDW.ShiftArithmetic13;
  }

  /* End of Update for SubSystem: '<S5>/闭环错误判断' */

  /* Update for UnitDelay: '<S1>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_b = rtDW.Merge;

  /* Signum: '<S9>/Sign' */
  if (rtb_ShiftArithmetic_f < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic_f > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S9>/默认除以32767'
   *  DataStoreRead: '<S9>/Data Store Read4'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Gain: '<S9>/Gain1'
   *  Product: '<S9>/Product'
   *  SignalConversion generated from: '<S9>/Sum'
   *  Signum: '<S9>/Sign'
   *  Sum: '<S9>/Sum'
   *  Sum: '<S9>/Sum1'
   *  UnaryMinus: '<S9>/Unary Minus'
   */
  rtY.tABC[0] = (uint16_T)((int16_T)-((((rtb_Sum_a + rtb_Min) - 51 *
    rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_o);

  /* Signum: '<S9>/Sign' */
  if (rtb_ShiftArithmetic1_o < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic1_o > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S9>/默认除以32767'
   *  DataStoreRead: '<S9>/Data Store Read4'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Gain: '<S9>/Gain1'
   *  Product: '<S9>/Product'
   *  SignalConversion generated from: '<S9>/Sum'
   *  Signum: '<S9>/Sign'
   *  Sum: '<S9>/Sum'
   *  Sum: '<S9>/Sum1'
   *  UnaryMinus: '<S9>/Unary Minus'
   */
  rtY.tABC[1] = (uint16_T)((int16_T)-((((rtb_Sum_bk + rtb_Min) - 51 *
    rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_o);

  /* Signum: '<S9>/Sign' */
  if (rtb_ShiftArithmetic2 < 0) {
    rtb_ShiftArithmetic_f = -1;
  } else {
    rtb_ShiftArithmetic_f = (rtb_ShiftArithmetic2 > 0);
  }

  /* Outport: '<Root>/tABC' incorporates:
   *  ArithShift: '<S9>/默认除以32767'
   *  DataStoreRead: '<S9>/Data Store Read4'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Gain: '<S9>/Gain1'
   *  Product: '<S9>/Product'
   *  SignalConversion generated from: '<S9>/Sum'
   *  Signum: '<S9>/Sign'
   *  Sum: '<S9>/Sum'
   *  Sum: '<S9>/Sum1'
   *  UnaryMinus: '<S9>/Unary Minus'
   */
  rtY.tABC[2] = (uint16_T)((int16_T)-((((rtb_ShiftArithmetic3 + rtb_Min) - 51 *
    rtb_ShiftArithmetic_f) * rtDW.PWM_TH) >> 15) + rtb_Bias_o);

  /* Outport: '<Root>/Obs_Spd' incorporates:
   *  ArithShift: '<S1>/Shift Arithmetic4'
   *  ArithShift: '<S6>/Shift Arithmetic9'
   */
  rtY.Obs_Spd = rtb_ShiftArithmetic9_e1 >> 8;

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
    /* Start for If: '<S22>/If1' */
    rtDW.If1_ActiveSubsystem = -1;

    /* End of SystemInitialize for SubSystem: '<S5>/闭环错误判断' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/恒速降力矩强拖' */
    /* InitializeConditions for Delay: '<S53>/Delay' */
    rtDW.icLoad_d = true;

    /* End of SystemInitialize for SubSystem: '<S1>/恒速降力矩强拖' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/观测器闭环//速度环' */
    /* InitializeConditions for Delay: '<S19>/Delay' */
    rtDW.icLoad = true;

    /* InitializeConditions for Delay: '<S19>/Delay1' */
    rtDW.icLoad_l = true;

    /* InitializeConditions for UnitDelay: '<S19>/Unit Delay3' */
    rtDW.UnitDelay3_DSTATE_m = OPEN_SPD;

    /* End of SystemInitialize for SubSystem: '<S1>/观测器闭环//速度环' */

    /* Outputs for Atomic SubSystem: '<S1>/初始化模块' */
    /* ArithShift: '<S14>/Shift Arithmetic26' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic'
     *  Constant: '<S14>/Constant18'
     *  Constant: '<S14>/周期定点化适当放大2^n'
     */
    u = ldexp(ldexp(1.0 / FOC_FRQ, 15), ((int16_T)TS_POINT_GAIN));

    /* DataTypeConversion: '<S14>/Data Type Conversion6' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write7'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion6' */

    /* ArithShift: '<S14>/Shift Arithmetic25' incorporates:
     *  Constant: '<S14>/ADC量程*母线电压分压倍数//定义的最大电压值'
     *  Constant: '<S14>/Constant16'
     *  Constant: '<S14>/电压采集定点化适当放大2^n'
     *  Product: '<S14>/Divide3'
     */
    rtb_Product18 = ldexpf(ADC_REF * UDC_GAIN / (real32_T)((int16_T)UDC),
      ((int16_T)UDC_POINT_GAIN));

    /* DataTypeConversion: '<S14>/Data Type Conversion5' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write6'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion5' */

    /* ArithShift: '<S14>/Shift Arithmetic24' incorporates:
     *  Constant: '<S14>/ADC量程//放大器倍数//定义的最大电流//采样电流'
     *  Constant: '<S14>/电流采集定点化适当放大2^n'
     */
    rtb_Product18 = ldexpf(ADC_REF / AMP_GAIN / IMAX / RS_HUNT, ((int16_T)
      CURR_POINT_GAIN));

    /* DataTypeConversion: '<S14>/Data Type Conversion4' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write5'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion4' */

    /* Product: '<S14>/Divide7' incorporates:
     *  Constant: '<S14>/Constant20'
     *  Constant: '<S14>/Constant21'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ / MOTOR_LS;

    /* ArithShift: '<S14>/Shift Arithmetic3' incorporates:
     *  Constant: '<S14>/Constant1'
     *  Constant: '<S14>/Constant15'
     *  Product: '<S14>/Product5'
     *  Sum: '<S14>/Sum'
     */
    u = ldexp(1.0 - MOTOR_RS * rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion9' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write10'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion9' */

    /* ArithShift: '<S14>/Shift Arithmetic4' */
    u = ldexp(rtb_ShiftArithmetic4, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion10' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write11'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion10' */

    /* Product: '<S14>/Divide' incorporates:
     *  Constant: '<S14>/Constant2'
     *  Constant: '<S14>/Constant71'
     *  Product: '<S14>/Divide1'
     */
    u_tmp = IMAX / (real32_T)((int16_T)UDC);

    /* ArithShift: '<S14>/Shift Arithmetic1' incorporates:
     *  Constant: '<S14>/Constant10'
     *  Constant: '<S14>/Constant9'
     *  Product: '<S14>/Divide'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product2'
     */
    rtb_Product18 = ldexpf(CURR_WIDTH * MOTOR_LS * u_tmp, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion11' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion11' */

    /* ArithShift: '<S14>/Shift Arithmetic2' incorporates:
     *  Constant: '<S14>/Constant11'
     *  Constant: '<S14>/Constant12'
     *  Product: '<S14>/Product1'
     *  Product: '<S14>/Product3'
     */
    rtb_Product18 = ldexpf(CURR_WIDTH * MOTOR_RS * u_tmp, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion1' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write2'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion1' */

    /* ArithShift: '<S14>/Shift Arithmetic20' incorporates:
     *  Constant: '<S14>/Constant13'
     *  Constant: '<S14>/Constant69'
     *  Product: '<S14>/Divide5'
     */
    rtb_Product18 = ldexpf((real32_T)((int16_T)UDC) / IMAX, 1);

    /* DataTypeConversion: '<S14>/Data Type Conversion8' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write9'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion8' */

    /* Gain: '<S14>/Gain2' incorporates:
     *  Constant: '<S14>/Constant5'
     */
    rtb_Product18 = MOTOR_PN / 60.0F * (real32_T)OPEN_SPD;

    /* DataTypeConversion: '<S14>/Data Type Conversion2' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write12'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion2' */

    /* Product: '<S14>/Product4' incorporates:
     *  Constant: '<S14>/Constant14'
     *  Constant: '<S14>/Constant17'
     *  Product: '<S14>/Divide4'
     */
    rtb_Product18 *= 1.0F / OPEN_TIME;

    /* DataTypeConversion: '<S14>/Data Type Conversion7' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write13'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion7' */

    /* Product: '<S14>/Product6' incorporates:
     *  Constant: '<S14>/Constant19'
     *  Constant: '<S14>/Constant22'
     */
    rtb_ShiftArithmetic4 = 1.0 / FOC_FRQ * LPF_FRQ;

    /* DataTypeConversion: '<S14>/Data Type Conversion12' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic5'
     *  Constant: '<S14>/Constant24'
     *  DataStoreWrite: '<S14>/Data Store Write3'
     *  Product: '<S14>/Divide6'
     *  Sum: '<S14>/Sum1'
     */
    rtDW.LPF_FRQ_Point = (int16_T)ceil(ldexp(rtb_ShiftArithmetic4 /
      (rtb_ShiftArithmetic4 + 1.0), 4));

    /* Product: '<S14>/Product8' incorporates:
     *  Constant: '<S14>/Constant25'
     *  Constant: '<S14>/Constant26'
     */
    rtb_Product18 = PLL_WIDTH * PLL_WIDTH;

    /* DataTypeConversion: '<S14>/Data Type Conversion14' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write14'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion14' */

    /* Product: '<S14>/Product7' incorporates:
     *  Constant: '<S14>/Constant25'
     *  Constant: '<S14>/Constant27'
     */
    rtb_Product18 = 1.414F * PLL_WIDTH;

    /* DataTypeConversion: '<S14>/Data Type Conversion13' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write8'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion13' */

    /* DataTypeConversion: '<S14>/Data Type Conversion15' incorporates:
     *  Constant: '<S14>/Constant28'
     *  Constant: '<S14>/Constant29'
     *  DataStoreWrite: '<S14>/Data Store Write15'
     *  Gain: '<S14>/Gain'
     *  Product: '<S14>/Product9'
     */
    rtDW.SMO_K = (int16_T)ceilf(SMOK_FRQ * MOTOR_FLUX * 6.28318548F);

    /* DataTypeConversion: '<S14>/Data Type Conversion16' incorporates:
     *  Constant: '<S14>/Constant30'
     *  DataStoreWrite: '<S14>/Data Store Write16'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion16' */

    /* ArithShift: '<S14>/Shift Arithmetic6' incorporates:
     *  Constant: '<S14>/Constant31'
     */
    rtb_Product18 = ldexpf(1.0F / LPF_FRQ, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion17' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write17'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion17' */

    /* Product: '<S14>/Product10' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic7'
     *  Constant: '<S14>/Constant32'
     */
    rtb_Product18 = PLL_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S14>/Data Type Conversion18' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write18'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion18' */

    /* Product: '<S14>/Product11' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic8'
     *  Constant: '<S14>/Constant34'
     */
    rtb_Product18 = CURR_LIMIT * 1.07374182E+9F;

    /* DataTypeConversion: '<S14>/Data Type Conversion19' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write19'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion19' */

    /* DataTypeConversion: '<S14>/Data Type Conversion23' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic12'
     *  Constant: '<S14>/Constant38'
     *  Constant: '<S14>/Constant49'
     *  DataStoreWrite: '<S14>/Data Store Write23'
     *  Product: '<S14>/Divide11'
     */
    rtDW.Hz_RPM = (int32_T)ceilf(ldexpf(60.0F / MOTOR_PN, 8));

    /* Product: '<S14>/Product13' incorporates:
     *  Constant: '<S14>/Constant41'
     *  Constant: '<S14>/Constant42'
     *  Constant: '<S14>/Constant43'
     */
    rtb_Product18 = MOTOR_PN * MOTOR_FLUX * (1.5F * IMAX);

    /* DataTypeConversion: '<S14>/Data Type Conversion21' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic9'
     *  Constant: '<S14>/Constant39'
     *  Constant: '<S14>/Constant40'
     *  DataStoreWrite: '<S14>/Data Store Write20'
     *  Product: '<S14>/Divide9'
     *  Product: '<S14>/Product12'
     */
    rtDW.Speed_Kp_Point = (int32_T)ceilf(ldexpf(SPD_WIDTH * MOTOR_INERTIA /
      rtb_Product18, 15));

    /* DataTypeConversion: '<S14>/Data Type Conversion20' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic10'
     *  Constant: '<S14>/Constant44'
     *  Constant: '<S14>/Constant45'
     *  Constant: '<S14>/Constant46'
     *  DataStoreWrite: '<S14>/Data Store Write21'
     *  Product: '<S14>/Divide10'
     *  Product: '<S14>/Product14'
     */
    rtDW.Speed_Ki_Point = (int32_T)ceilf(ldexpf(SPD_WIDTH * SPD_WIDTH *
      MOTOR_INERTIA * (1.0F / rtb_Product18), 15));

    /* Product: '<S14>/Product15' incorporates:
     *  ArithShift: '<S14>/Shift Arithmetic11'
     *  Constant: '<S14>/Constant47'
     *  Constant: '<S14>/Constant48'
     */
    rtb_Product18 = SPD_LIMIT * 32768.0F;

    /* DataTypeConversion: '<S14>/Data Type Conversion22' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write22'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion22' */

    /* Saturate: '<S14>/Saturation2' incorporates:
     *  Constant: '<S14>/Constant50'
     */
    if (CURR_OVER > IMAX) {
      v_0 = IMAX;
    } else if (CURR_OVER < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = CURR_OVER;
    }

    /* ArithShift: '<S14>/Shift Arithmetic13' incorporates:
     *  Gain: '<S14>/Gain5'
     *  Saturate: '<S14>/Saturation2'
     */
    rtb_Product18 = ldexpf(1.0F / IMAX * v_0, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion24' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write24'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion24' */

    /* Saturate: '<S14>/Saturation' incorporates:
     *  Constant: '<S14>/Constant52'
     */
    if (OPEN_IQ > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ;
    }

    /* ArithShift: '<S14>/Shift Arithmetic14' incorporates:
     *  Constant: '<S14>/Constant53'
     *  Product: '<S14>/Divide12'
     *  Saturate: '<S14>/Saturation'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion25' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write25'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion25' */

    /* Saturate: '<S14>/Saturation1' incorporates:
     *  Constant: '<S14>/Constant54'
     */
    if (OPEN_IQ_MIN > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ_MIN < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ_MIN;
    }

    /* ArithShift: '<S14>/Shift Arithmetic15' incorporates:
     *  Constant: '<S14>/Constant55'
     *  Product: '<S14>/Divide13'
     *  Saturate: '<S14>/Saturation1'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion26' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write26'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion26' */

    /* Saturate: '<S14>/Saturation3' incorporates:
     *  Constant: '<S14>/Constant6'
     */
    if (OPEN_IQ_SLOW > IMAX) {
      v_0 = IMAX;
    } else if (OPEN_IQ_SLOW < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = OPEN_IQ_SLOW;
    }

    /* ArithShift: '<S14>/Shift Arithmetic16' incorporates:
     *  Constant: '<S14>/Constant56'
     *  Product: '<S14>/Divide14'
     *  Saturate: '<S14>/Saturation3'
     */
    rtb_Product18 = ldexpf(v_0 / IMAX, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion27' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write28'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion27' */

    /* Gain: '<S14>/Gain6' incorporates:
     *  Constant: '<S14>/Constant57'
     */
    rtb_Product18 = MOTOR_PN / 60.0F * OPEN_SPD_SLOW;

    /* DataTypeConversion: '<S14>/Data Type Conversion28' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write27'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion28' */

    /* Saturate: '<S14>/Saturation4' incorporates:
     *  Constant: '<S14>/Constant58'
     */
    if (CURR_UNDER > IMAX) {
      v_0 = IMAX;
    } else if (CURR_UNDER < -IMAX) {
      v_0 = -IMAX;
    } else {
      v_0 = CURR_UNDER;
    }

    /* ArithShift: '<S14>/Shift Arithmetic17' incorporates:
     *  Gain: '<S14>/Gain7'
     *  Saturate: '<S14>/Saturation4'
     */
    rtb_Product18 = ldexpf(1.0F / IMAX * v_0, 15);

    /* DataTypeConversion: '<S14>/Data Type Conversion29' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write29'
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

    /* End of DataTypeConversion: '<S14>/Data Type Conversion29' */

    /* Product: '<S14>/Divide2' incorporates:
     *  Constant: '<S14>/Constant7'
     *  Constant: '<S14>/Constant8'
     */
    u = PWM_FRQ / (FOC_FRQ * 2.0);

    /* DataTypeConversion: '<S14>/Data Type Conversion3' incorporates:
     *  DataStoreWrite: '<S14>/Data Store Write4'
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
