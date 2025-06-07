//###########################################################################
//
// FILE:    F2837xD_clb.h
//
// TITLE:   Definitions for the CLB registers.
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2025 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef F2837xD_CLB_H
#define F2837xD_CLB_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CLB Individual Register Bit Definitions:

struct CLB_COUNT_RESET_BITS {           // bits description
    Uint16 SEL_0:5;                     // 4:0 Count Reset Select 0
    Uint16 SEL_1:5;                     // 9:5 Count Reset Select 1
    Uint16 SEL_2:5;                     // 14:10 Count Reset Select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_COUNT_RESET_REG {
    Uint32  all;
    struct  CLB_COUNT_RESET_BITS  bit;
};

struct CLB_COUNT_MODE_1_BITS {          // bits description
    Uint16 SEL_0:5;                     // 4:0 Counter mode 1 select 0
    Uint16 SEL_1:5;                     // 9:5 Counter mode 1 select 1
    Uint16 SEL_2:5;                     // 14:10 Counter mode 1 select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_COUNT_MODE_1_REG {
    Uint32  all;
    struct  CLB_COUNT_MODE_1_BITS  bit;
};

struct CLB_COUNT_MODE_0_BITS {          // bits description
    Uint16 SEL_0:5;                     // 4:0 Counter mode 0 select 0
    Uint16 SEL_1:5;                     // 9:5 Counter mode 0 select 1
    Uint16 SEL_2:5;                     // 14:10 Counter mode 0 select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_COUNT_MODE_0_REG {
    Uint32  all;
    struct  CLB_COUNT_MODE_0_BITS  bit;
};

struct CLB_COUNT_EVENT_BITS {           // bits description
    Uint16 SEL_0:5;                     // 4:0 Counter event select 0
    Uint16 SEL_1:5;                     // 9:5 Counter event select 1
    Uint16 SEL_2:5;                     // 14:10 Counter event select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_COUNT_EVENT_REG {
    Uint32  all;
    struct  CLB_COUNT_EVENT_BITS  bit;
};

struct CLB_FSM_EXTRA_IN0_BITS {         // bits description
    Uint16 SEL_0:5;                     // 4:0 FSM extra ext input select 0
    Uint16 SEL_1:5;                     // 9:5 FSM extra ext input select 1
    Uint16 SEL_2:5;                     // 14:10 FSM extra ext input select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_FSM_EXTRA_IN0_REG {
    Uint32  all;
    struct  CLB_FSM_EXTRA_IN0_BITS  bit;
};

struct CLB_FSM_EXTERNAL_IN0_BITS {      // bits description
    Uint16 SEL_0:5;                     // 4:0 FSM EXT_IN0 select input for unit 0
    Uint16 SEL_1:5;                     // 9:5 FSM EXT_IN0 select input for unit 1
    Uint16 SEL_2:5;                     // 14:10 FSM EXT_IN0 select input for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_FSM_EXTERNAL_IN0_REG {
    Uint32  all;
    struct  CLB_FSM_EXTERNAL_IN0_BITS  bit;
};

struct CLB_FSM_EXTERNAL_IN1_BITS {      // bits description
    Uint16 SEL_0:5;                     // 4:0 FSM EXT_IN1 select input for unit 0
    Uint16 SEL_1:5;                     // 9:5 FSM EXT_IN1 select input for unit 1
    Uint16 SEL_2:5;                     // 14:10 FSM EXT_IN1 select input for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_FSM_EXTERNAL_IN1_REG {
    Uint32  all;
    struct  CLB_FSM_EXTERNAL_IN1_BITS  bit;
};

struct CLB_FSM_EXTRA_IN1_BITS {         // bits description
    Uint16 SEL_0:5;                     // 4:0 FSM extra ext input select 0
    Uint16 SEL_1:5;                     // 9:5 FSM extra ext input select 1
    Uint16 SEL_2:5;                     // 14:10 FSM extra ext input select 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_FSM_EXTRA_IN1_REG {
    Uint32  all;
    struct  CLB_FSM_EXTRA_IN1_BITS  bit;
};

struct CLB_LUT4_IN0_BITS {              // bits description
    Uint16 SEL_0:5;                     // 4:0 Select inputs for unit 0
    Uint16 SEL_1:5;                     // 9:5 Select inputs for unit 1
    Uint16 SEL_2:5;                     // 14:10 Select inputs for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_LUT4_IN0_REG {
    Uint32  all;
    struct  CLB_LUT4_IN0_BITS  bit;
};

struct CLB_LUT4_IN1_BITS {              // bits description
    Uint16 SEL_0:5;                     // 4:0 Select inputs for unit 0
    Uint16 SEL_1:5;                     // 9:5 Select inputs for unit 1
    Uint16 SEL_2:5;                     // 14:10 Select inputs for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_LUT4_IN1_REG {
    Uint32  all;
    struct  CLB_LUT4_IN1_BITS  bit;
};

struct CLB_LUT4_IN2_BITS {              // bits description
    Uint16 SEL_0:5;                     // 4:0 Select inputs for unit 0
    Uint16 SEL_1:5;                     // 9:5 Select inputs for unit 1
    Uint16 SEL_2:5;                     // 14:10 Select inputs for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_LUT4_IN2_REG {
    Uint32  all;
    struct  CLB_LUT4_IN2_BITS  bit;
};

struct CLB_LUT4_IN3_BITS {              // bits description
    Uint16 SEL_0:5;                     // 4:0 Select inputs for unit 0
    Uint16 SEL_1:5;                     // 9:5 Select inputs for unit 1
    Uint16 SEL_2:5;                     // 14:10 Select inputs for unit 2
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_LUT4_IN3_REG {
    Uint32  all;
    struct  CLB_LUT4_IN3_BITS  bit;
};

struct CLB_FSM_LUT_FN1_0_BITS {         // bits description
    Uint16 FN0:16;                      // 15:0 FSM LUT output function for unit 0
    Uint16 FN1:16;                      // 31:16 FSM LUT output function for unit 1
};

union CLB_FSM_LUT_FN1_0_REG {
    Uint32  all;
    struct  CLB_FSM_LUT_FN1_0_BITS  bit;
};

struct CLB_FSM_LUT_FN2_BITS {           // bits description
    Uint16 FN1:16;                      // 15:0 FSM LUT output function for unit 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CLB_FSM_LUT_FN2_REG {
    Uint32  all;
    struct  CLB_FSM_LUT_FN2_BITS  bit;
};

struct CLB_LUT4_FN1_0_BITS {            // bits description
    Uint16 FN0:16;                      // 15:0 LUT4 output function for unit 0
    Uint16 FN1:16;                      // 31:16 LUT4 output function for unit 1
};

union CLB_LUT4_FN1_0_REG {
    Uint32  all;
    struct  CLB_LUT4_FN1_0_BITS  bit;
};

struct CLB_LUT4_FN2_BITS {              // bits description
    Uint16 FN1:16;                      // 15:0 LUT4 output function for unit 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CLB_LUT4_FN2_REG {
    Uint32  all;
    struct  CLB_LUT4_FN2_BITS  bit;
};

struct CLB_FSM_NEXT_STATE_0_BITS {      // bits description
    Uint16 S0:16;                       // 15:0 FSM next state function for S0
    Uint16 S1:16;                       // 31:16 FSM next state function for S1
};

union CLB_FSM_NEXT_STATE_0_REG {
    Uint32  all;
    struct  CLB_FSM_NEXT_STATE_0_BITS  bit;
};

struct CLB_FSM_NEXT_STATE_1_BITS {      // bits description
    Uint16 S0:16;                       // 15:0 FSM next state function for S0
    Uint16 S1:16;                       // 31:16 FSM next state function for S1
};

union CLB_FSM_NEXT_STATE_1_REG {
    Uint32  all;
    struct  CLB_FSM_NEXT_STATE_1_BITS  bit;
};

struct CLB_FSM_NEXT_STATE_2_BITS {      // bits description
    Uint16 S0:16;                       // 15:0 FSM next state function for S0
    Uint16 S1:16;                       // 31:16 FSM next state function for S1
};

union CLB_FSM_NEXT_STATE_2_REG {
    Uint32  all;
    struct  CLB_FSM_NEXT_STATE_2_BITS  bit;
};

struct CLB_MISC_CONTROL_BITS {          // bits description
    Uint16 COUNT_ADD_SHIFT_0:1;         // 0 Add/Shift for counter 0
    Uint16 COUNT_DIR_0:1;               // 1 Direction for counter 0
    Uint16 COUNT_EVENT_CTRL_0:1;        // 2 Event control for counter 0
    Uint16 COUNT_ADD_SHIFT_1:1;         // 3 Add/Shift for counter 1
    Uint16 COUNT_DIR_1:1;               // 4 Direction for counter 1
    Uint16 COUNT_EVENT_CTRL_1:1;        // 5 Event control for counter 1
    Uint16 COUNT_ADD_SHIFT_2:1;         // 6 Add/Shift for counter 2
    Uint16 COUNT_DIR_2:1;               // 7 Direction for counter 2
    Uint16 COUNT_EVENT_CTRL_2:1;        // 8 Event control for counter 2
    Uint16 COUNT_SERIALIZER_0:1;        // 9 Serializer enable 0
    Uint16 COUNT_SERIALIZER_1:1;        // 10 Serializer enable 1
    Uint16 COUNT_SERIALIZER_2:1;        // 11 Serializer enable 2
    Uint16 FSM_EXTRA_SEL0_0:1;          // 12 FSM extra_sel0 for 0
    Uint16 FSM_EXTRA_SEL1_0:1;          // 13 FSM extra_sel1 for 0
    Uint16 FSM_EXTRA_SEL0_1:1;          // 14 FSM extra_sel0 for 1
    Uint16 FSM_EXTRA_SEL1_1:1;          // 15 FSM extra_sel1 for 1
    Uint16 FSM_EXTRA_SEL0_2:1;          // 16 FSM extra_sel0 for 2
    Uint16 FSM_EXTRA_SEL1_2:1;          // 17 FSM extra_sel1 for 2
    Uint16 rsvd1:14;                    // 31:18 Reserved
};

union CLB_MISC_CONTROL_REG {
    Uint32  all;
    struct  CLB_MISC_CONTROL_BITS  bit;
};

struct CLB_OUTPUT_LUT_0_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_0_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_0_BITS  bit;
};

struct CLB_OUTPUT_LUT_1_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_1_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_1_BITS  bit;
};

struct CLB_OUTPUT_LUT_2_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_2_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_2_BITS  bit;
};

struct CLB_OUTPUT_LUT_3_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_3_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_3_BITS  bit;
};

struct CLB_OUTPUT_LUT_4_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_4_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_4_BITS  bit;
};

struct CLB_OUTPUT_LUT_5_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_5_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_5_BITS  bit;
};

struct CLB_OUTPUT_LUT_6_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_6_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_6_BITS  bit;
};

struct CLB_OUTPUT_LUT_7_BITS {          // bits description
    Uint16 IN0:5;                       // 4:0 Select value for IN0 of output LUT
    Uint16 IN1:5;                       // 9:5 Select value for IN1 of output LUT
    Uint16 IN2:5;                       // 14:10 Select value for IN2 of output LUT
    Uint32 FN:8;                        // 22:15 Output function for output LUT
    Uint16 rsvd1:9;                     // 31:23 Reserved
};

union CLB_OUTPUT_LUT_7_REG {
    Uint32  all;
    struct  CLB_OUTPUT_LUT_7_BITS  bit;
};

struct CLB_HLC_EVENT_SEL_BITS {         // bits description
    Uint16 EVENT0_SEL:5;                // 4:0 Event Select 0
    Uint16 EVENT1_SEL:5;                // 9:5 Event Select 1
    Uint16 EVENT2_SEL:5;                // 14:10 Event Select 2
    Uint32 EVENT3_SEL:5;                // 19:15 Event Select 3
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union CLB_HLC_EVENT_SEL_REG {
    Uint32  all;
    struct  CLB_HLC_EVENT_SEL_BITS  bit;
};

struct CLB_LOGIC_CONFIG_REGS {
    Uint16                                   rsvd1[2];                     // Reserved
    union   CLB_COUNT_RESET_REG              CLB_COUNT_RESET;              // Counter Block RESET
    union   CLB_COUNT_MODE_1_REG             CLB_COUNT_MODE_1;             // Counter Block MODE_1
    union   CLB_COUNT_MODE_0_REG             CLB_COUNT_MODE_0;             // Counter Block MODE_0
    union   CLB_COUNT_EVENT_REG              CLB_COUNT_EVENT;              // Counter Block EVENT
    union   CLB_FSM_EXTRA_IN0_REG            CLB_FSM_EXTRA_IN0;            // FSM Extra EXT_IN0
    union   CLB_FSM_EXTERNAL_IN0_REG         CLB_FSM_EXTERNAL_IN0;         // FSM EXT_IN0
    union   CLB_FSM_EXTERNAL_IN1_REG         CLB_FSM_EXTERNAL_IN1;         // FSM_EXT_IN1
    union   CLB_FSM_EXTRA_IN1_REG            CLB_FSM_EXTRA_IN1;            // FSM Extra_EXT_IN1
    union   CLB_LUT4_IN0_REG                 CLB_LUT4_IN0;                 // LUT4_0/1/2 IN0 input source
    union   CLB_LUT4_IN1_REG                 CLB_LUT4_IN1;                 // LUT4_0/1/2 IN1 input source
    union   CLB_LUT4_IN2_REG                 CLB_LUT4_IN2;                 // LUT4_0/1/2 IN2 input source
    union   CLB_LUT4_IN3_REG                 CLB_LUT4_IN3;                 // LUT4_0/1/2 IN3 input source
    Uint16                                   rsvd2[2];                     // Reserved
    union   CLB_FSM_LUT_FN1_0_REG            CLB_FSM_LUT_FN1_0;            // LUT function for FSM Unit 1 and Unit 0
    union   CLB_FSM_LUT_FN2_REG              CLB_FSM_LUT_FN2;              // LUT function for FSM Unit 2
    union   CLB_LUT4_FN1_0_REG               CLB_LUT4_FN1_0;               // LUT function for LUT4 block of Unit 1 and 0
    union   CLB_LUT4_FN2_REG                 CLB_LUT4_FN2;                 // LUT function for LUT4 block of Unit 2
    union   CLB_FSM_NEXT_STATE_0_REG         CLB_FSM_NEXT_STATE_0;         // FSM Next state equations for Unit 0
    union   CLB_FSM_NEXT_STATE_1_REG         CLB_FSM_NEXT_STATE_1;         // FSM Next state equations for Unit 1
    union   CLB_FSM_NEXT_STATE_2_REG         CLB_FSM_NEXT_STATE_2;         // FSM Next state equations for Unit 2
    union   CLB_MISC_CONTROL_REG             CLB_MISC_CONTROL;             // Static controls for Ctr,FSM
    union   CLB_OUTPUT_LUT_0_REG             CLB_OUTPUT_LUT_0;             // Inp Sel, LUT fns for Out0
    union   CLB_OUTPUT_LUT_1_REG             CLB_OUTPUT_LUT_1;             // Inp Sel, LUT fns for Out1
    union   CLB_OUTPUT_LUT_2_REG             CLB_OUTPUT_LUT_2;             // Inp Sel, LUT fns for Out2
    union   CLB_OUTPUT_LUT_3_REG             CLB_OUTPUT_LUT_3;             // Inp Sel, LUT fns for Out3
    union   CLB_OUTPUT_LUT_4_REG             CLB_OUTPUT_LUT_4;             // Inp Sel, LUT fns for Out4
    union   CLB_OUTPUT_LUT_5_REG             CLB_OUTPUT_LUT_5;             // Inp Sel, LUT fns for Out5
    union   CLB_OUTPUT_LUT_6_REG             CLB_OUTPUT_LUT_6;             // Inp Sel, LUT fns for Out6
    union   CLB_OUTPUT_LUT_7_REG             CLB_OUTPUT_LUT_7;             // Inp Sel, LUT fns for Out7
    union   CLB_HLC_EVENT_SEL_REG            CLB_HLC_EVENT_SEL;            // Event Selector register for the High Level controller
};

struct CLB_LOAD_EN_BITS {               // bits description
    Uint16 LOAD_EN:1;                   // 0 Load Enable
    Uint16 GLOBAL_EN:1;                 // 1 Global Enable
    Uint16 STOP:1;                      // 2 Debug stop control
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union CLB_LOAD_EN_REG {
    Uint16  all;
    struct  CLB_LOAD_EN_BITS  bit;
};

struct CLB_LOAD_ADDR_BITS {             // bits description
    Uint16 ADDR:6;                      // 5:0 Indirect Address
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_LOAD_ADDR_REG {
    Uint32  all;
    struct  CLB_LOAD_ADDR_BITS  bit;
};

struct CLB_INPUT_FILTER_BITS {          // bits description
    Uint16 FIN0:2;                      // 1:0 Input filter control 0
    Uint16 FIN1:2;                      // 3:2 Input filter control 1
    Uint16 FIN2:2;                      // 5:4 Input filter control 2
    Uint16 FIN3:2;                      // 7:6 Input filter control 3
    Uint16 FIN4:2;                      // 9:8 Input filter control 4
    Uint16 FIN5:2;                      // 11:10 Input filter control 5
    Uint16 FIN6:2;                      // 13:12 Input filter control 6
    Uint16 FIN7:2;                      // 15:14 Input filter control 7
    Uint16 SYNC0:1;                     // 16 Synchronizer control 0
    Uint16 SYNC1:1;                     // 17 Synchronizer control 1
    Uint16 SYNC2:1;                     // 18 Synchronizer control 2
    Uint16 SYNC3:1;                     // 19 Synchronizer control 3
    Uint16 SYNC4:1;                     // 20 Synchronizer control 4
    Uint16 SYNC5:1;                     // 21 Synchronizer control 5
    Uint16 SYNC6:1;                     // 22 Synchronizer control 6
    Uint16 SYNC7:1;                     // 23 Synchronizer control 7
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union CLB_INPUT_FILTER_REG {
    Uint32  all;
    struct  CLB_INPUT_FILTER_BITS  bit;
};

struct CLB_IN_MUX_SEL_0_BITS {          // bits description
    Uint16 SEL_GP_IN_0:1;               // 0 Select GP register 0
    Uint16 SEL_GP_IN_1:1;               // 1 Select GP register 1
    Uint16 SEL_GP_IN_2:1;               // 2 Select GP register 2
    Uint16 SEL_GP_IN_3:1;               // 3 Select GP register 3
    Uint16 SEL_GP_IN_4:1;               // 4 Select GP register 4
    Uint16 SEL_GP_IN_5:1;               // 5 Select GP register 5
    Uint16 SEL_GP_IN_6:1;               // 6 Select GP register 6
    Uint16 SEL_GP_IN_7:1;               // 7 Select GP register 7
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_IN_MUX_SEL_0_REG {
    Uint32  all;
    struct  CLB_IN_MUX_SEL_0_BITS  bit;
};

struct CLB_LCL_MUX_SEL_1_BITS {         // bits description
    Uint16 LCL_MUX_SEL_IN_0:5;          // 4:0 Local Mux select 0
    Uint16 LCL_MUX_SEL_IN_1:5;          // 9:5 Local Mux select 1
    Uint16 LCL_MUX_SEL_IN_2:5;          // 14:10 Local Mux select 2
    Uint32 LCL_MUX_SEL_IN_3:5;          // 19:15 Local Mux select 3
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union CLB_LCL_MUX_SEL_1_REG {
    Uint32  all;
    struct  CLB_LCL_MUX_SEL_1_BITS  bit;
};

struct CLB_LCL_MUX_SEL_2_BITS {         // bits description
    Uint16 LCL_MUX_SEL_IN_4:5;          // 4:0 Local Mux select 4
    Uint16 LCL_MUX_SEL_IN_5:5;          // 9:5 Local Mux select 5
    Uint16 LCL_MUX_SEL_IN_6:5;          // 14:10 Local Mux select 6
    Uint32 LCL_MUX_SEL_IN_7:5;          // 19:15 Local Mux select 7
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union CLB_LCL_MUX_SEL_2_REG {
    Uint32  all;
    struct  CLB_LCL_MUX_SEL_2_BITS  bit;
};

struct CLB_BUF_PTR_BITS {               // bits description
    Uint16 PULL:8;                      // 7:0 Data pointer for pull
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 PUSH:8;                      // 23:16 Data pointer for pull
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union CLB_BUF_PTR_REG {
    Uint32  all;
    struct  CLB_BUF_PTR_BITS  bit;
};

struct CLB_GP_REG_BITS {                // bits description
    Uint16 REG:8;                       // 7:0 General Purpose bit register
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLB_GP_REG_REG {
    Uint32  all;
    struct  CLB_GP_REG_BITS  bit;
};

struct CLB_GLBL_MUX_SEL_1_BITS {        // bits description
    Uint16 GLBL_MUX_SEL_IN_0:7;         // 6:0 Global Mux select 0
    Uint16 GLBL_MUX_SEL_IN_1:7;         // 13:7 Global Mux select 1
    Uint32 GLBL_MUX_SEL_IN_2:7;         // 20:14 Global Mux select 2
    Uint16 GLBL_MUX_SEL_IN_3:7;         // 27:21 Global Mux select 3
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union CLB_GLBL_MUX_SEL_1_REG {
    Uint32  all;
    struct  CLB_GLBL_MUX_SEL_1_BITS  bit;
};

struct CLB_GLBL_MUX_SEL_2_BITS {        // bits description
    Uint16 GLBL_MUX_SEL_IN_4:7;         // 6:0 Global Mux select 4
    Uint16 GLBL_MUX_SEL_IN_5:7;         // 13:7 Global Mux select 5
    Uint32 GLBL_MUX_SEL_IN_6:7;         // 20:14 Global Mux select 6
    Uint16 GLBL_MUX_SEL_IN_7:7;         // 27:21 Global Mux select 7
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union CLB_GLBL_MUX_SEL_2_REG {
    Uint32  all;
    struct  CLB_GLBL_MUX_SEL_2_BITS  bit;
};

struct CLB_INTR_TAG_REG_BITS {          // bits description
    Uint16 TAG:6;                       // 5:0 Interrupt tag
    Uint16 rsvd1:10;                    // 15:6 Reserved
};

union CLB_INTR_TAG_REG_REG {
    Uint16  all;
    struct  CLB_INTR_TAG_REG_BITS  bit;
};

struct CLB_LOCK_BITS {                  // bits description
    Uint16 LOCK:1;                      // 0 LOCK enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Key for enabling write
};

union CLB_LOCK_REG {
    Uint32  all;
    struct  CLB_LOCK_BITS  bit;
};

struct CLB_DBG_OUT_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 COUNT0_MATCH2:1;             // 1 COUNT_MATCH2 UNIT 0
    Uint16 COUNT0_ZERO:1;               // 2 COUNT_ZERO UNIT 0
    Uint16 COUNT0_MATCH1:1;             // 3 COUNT_MATCH1 UNIT 0
    Uint16 FSM0_S0:1;                   // 4 FSM_S0 UNIT 0
    Uint16 FSM0_S1:1;                   // 5 FSM_S1 UNIT 0
    Uint16 FSM0_LUTOUT:1;               // 6 FSM_LUT_OUT UNIT 0
    Uint16 LUT40_OUT:1;                 // 7 LUT4_OUT UNIT 0
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 COUNT1_MATCH2:1;             // 9 COUNT_MATCH2 UNIT 1
    Uint16 COUNT1_ZERO:1;               // 10 COUNT_ZERO UNIT 1
    Uint16 COUNT1_MATCH1:1;             // 11 COUNT_MATCH1 UNIT 1
    Uint16 FSM1_S0:1;                   // 12 FSM_S0 UNIT 1
    Uint16 FSM1_S1:1;                   // 13 FSM_S1 UNIT 1
    Uint16 FSM1_LUTOUT:1;               // 14 FSM_LUT_OUT UNIT 1
    Uint16 LUT41_OUT:1;                 // 15 LUT4_OUT UNIT 1
    Uint16 rsvd3:1;                     // 16 Reserved
    Uint16 COUNT2_MATCH2:1;             // 17 COUNT_MATCH2 UNIT 2
    Uint16 COUNT2_ZERO:1;               // 18 COUNT_ZERO UNIT 2
    Uint16 COUNT2_MATCH1:1;             // 19 COUNT_MATCH1 UNIT 2
    Uint16 FSM2_S0:1;                   // 20 FSM_S0 UNIT 2
    Uint16 FSM2_S1:1;                   // 21 FSM_S1 UNIT 2
    Uint16 FSM2_LUTOUT:1;               // 22 FSM_LUT_OUT UNIT 2
    Uint16 LUT42_OUT:1;                 // 23 LUT4_OUT UNIT 2
    Uint16 OUT0:1;                      // 24 CELL Output 0
    Uint16 OUT1:1;                      // 25 CELL Output 1
    Uint16 OUT2:1;                      // 26 CELL Output 2
    Uint16 OUT3:1;                      // 27 CELL Output 3
    Uint16 OUT4:1;                      // 28 CELL Output 4
    Uint16 OUT5:1;                      // 29 CELL Output 5
    Uint16 OUT6:1;                      // 30 CELL Output 6
    Uint16 OUT7:1;                      // 31 CELL Output 7
};

union CLB_DBG_OUT_REG {
    Uint32  all;
    struct  CLB_DBG_OUT_BITS  bit;
};

struct CLB_LOGIC_CONTROL_REGS {
    union   CLB_LOAD_EN_REG                  CLB_LOAD_EN;                  // Global enable & indirect load enable control
    Uint16                                   rsvd1;                        // Reserved
    union   CLB_LOAD_ADDR_REG                CLB_LOAD_ADDR;                // Indirect address
    Uint32                                   CLB_LOAD_DATA;                // Data for indirect loads
    union   CLB_INPUT_FILTER_REG             CLB_INPUT_FILTER;             // Input filter selection for both edge detection and synchronizers
    union   CLB_IN_MUX_SEL_0_REG             CLB_IN_MUX_SEL_0;             // Input selection to decide between Signals and GP register
    union   CLB_LCL_MUX_SEL_1_REG            CLB_LCL_MUX_SEL_1;            // Input Mux selection for local mux
    union   CLB_LCL_MUX_SEL_2_REG            CLB_LCL_MUX_SEL_2;            // Input Mux selection for local mux
    union   CLB_BUF_PTR_REG                  CLB_BUF_PTR;                  // PUSH and PULL pointers
    union   CLB_GP_REG_REG                   CLB_GP_REG;                   // General purpose register for CELL inputs
    Uint32                                   CLB_OUT_EN;                   // CELL output enable register
    union   CLB_GLBL_MUX_SEL_1_REG           CLB_GLBL_MUX_SEL_1;           // Global Mux select for CELL inputs
    union   CLB_GLBL_MUX_SEL_2_REG           CLB_GLBL_MUX_SEL_2;           // Global Mux select for CELL inputs
    Uint16                                   rsvd2[8];                     // Reserved
    union   CLB_INTR_TAG_REG_REG             CLB_INTR_TAG_REG;             // Interrupt Tag register
    Uint16                                   rsvd3;                        // Reserved
    union   CLB_LOCK_REG                     CLB_LOCK;                     // Lock control register
    Uint16                                   rsvd4[12];                    // Reserved
    Uint32                                   CLB_DBG_R0;                   // R0 of High level Controller
    Uint32                                   CLB_DBG_R1;                   // R1 of High level Controller
    Uint32                                   CLB_DBG_R2;                   // R2 of High level Controller
    Uint32                                   CLB_DBG_R3;                   // R3 of High level Controller
    Uint32                                   CLB_DBG_C0;                   // Count of Unit 0
    Uint32                                   CLB_DBG_C1;                   // Count of Unit 1
    Uint32                                   CLB_DBG_C2;                   // Count of Unit 2
    union   CLB_DBG_OUT_REG                  CLB_DBG_OUT;                  // Outputs of various units in the Cell
};

struct CLB_DATA_EXCHANGE_REGS {
    Uint32                                   CLB_PUSH[4];                  // CLB_PUSH FIFO Registers (from HLC)
    Uint16                                   rsvd1[248];                   // Reserved
    Uint32                                   CLB_PULL[4];                  // CLB_PULL FIFO Registers (TO HLC)
};

//---------------------------------------------------------------------------
// CLB External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb1DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb2DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb3DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb4DataExchRegs;
#endif
#ifdef CPU2
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb1DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb2DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb3DataExchRegs;
extern volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicCfgRegs;
extern volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicCtrlRegs;
extern volatile struct CLB_DATA_EXCHANGE_REGS Clb4DataExchRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
