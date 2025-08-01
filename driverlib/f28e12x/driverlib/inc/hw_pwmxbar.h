//###########################################################################
//
// FILE:    hw_pwmxbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef HW_PWMXBAR_H
#define HW_PWMXBAR_H

//*************************************************************************************************
//
// The following are defines for the XBAR register offsets
//
//*************************************************************************************************
#define XBAR_O_TRIP1MUX0TO15CFG    0x0U    // PWM XBAR Mux Configuration for Output1
#define XBAR_O_TRIP1MUX16TO31CFG   0x2U    // PWM XBAR Mux Configuration for Output1
#define XBAR_O_TRIP2MUX0TO15CFG    0x4U    // PWM XBAR Mux Configuration for Output2
#define XBAR_O_TRIP2MUX16TO31CFG   0x6U    // PWM XBAR Mux Configuration for Output2
#define XBAR_O_TRIP3MUX0TO15CFG    0x8U    // PWM XBAR Mux Configuration for Output3
#define XBAR_O_TRIP3MUX16TO31CFG   0xAU    // PWM XBAR Mux Configuration for Output3
#define XBAR_O_TRIP4MUX0TO15CFG    0xCU    // PWM XBAR Mux Configuration for Output4
#define XBAR_O_TRIP4MUX16TO31CFG   0xEU    // PWM XBAR Mux Configuration for Output4
#define XBAR_O_TRIP5MUX0TO15CFG    0x10U   // PWM XBAR Mux Configuration for Output5
#define XBAR_O_TRIP5MUX16TO31CFG   0x12U   // PWM XBAR Mux Configuration for Output5
#define XBAR_O_TRIP6MUX0TO15CFG    0x14U   // PWM XBAR Mux Configuration for Output6
#define XBAR_O_TRIP6MUX16TO31CFG   0x16U   // PWM XBAR Mux Configuration for Output6
#define XBAR_O_TRIP7MUX0TO15CFG    0x18U   // PWM XBAR Mux Configuration for Output7
#define XBAR_O_TRIP7MUX16TO31CFG   0x1AU   // PWM XBAR Mux Configuration for Output7
#define XBAR_O_TRIP8MUX0TO15CFG    0x1CU   // PWM XBAR Mux Configuration for Output8
#define XBAR_O_TRIP8MUX16TO31CFG   0x1EU   // PWM XBAR Mux Configuration for Output8
#define XBAR_O_TRIP1MUXENABLE      0x20U   // PWM XBAR Mux Enable for Output1
#define XBAR_O_TRIP2MUXENABLE      0x22U   // PWM XBAR Mux Enable for Output2
#define XBAR_O_TRIP3MUXENABLE      0x24U   // PWM XBAR Mux Enable for Output3
#define XBAR_O_TRIP4MUXENABLE      0x26U   // PWM XBAR Mux Enable for Output4
#define XBAR_O_TRIP5MUXENABLE      0x28U   // PWM XBAR Mux Enable for Output5
#define XBAR_O_TRIP6MUXENABLE      0x2AU   // PWM XBAR Mux Enable for Output6
#define XBAR_O_TRIP7MUXENABLE      0x2CU   // PWM XBAR Mux Enable for Output7
#define XBAR_O_TRIP8MUXENABLE      0x2EU   // PWM XBAR Mux Enable for Output8
#define XBAR_O_TRIPOUTINV          0x38U   // PWM XBAR Output Inversion Register
#define XBAR_O_TRIPLOCK            0x3EU   // PWM XBAR Configuration Lock register


//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP1MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP1MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP1MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP1MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP1MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP1MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP1MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP1MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP1MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP1MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP1MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP1MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP1MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP1MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP1MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP1MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP1MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP1MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT1 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP1MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP1MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP1MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT1 of PWM-XBAR
#define XBAR_TRIP1MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP1MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT1 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP2MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP2MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP2MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP2MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP2MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP2MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP2MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP2MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP2MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP2MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP2MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP2MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP2MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP2MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP2MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP2MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP2MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP2MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT2 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP2MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP2MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP2MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT2 of PWM-XBAR
#define XBAR_TRIP2MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP2MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT2 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP3MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP3MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP3MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP3MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP3MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP3MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP3MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP3MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP3MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP3MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP3MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP3MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP3MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP3MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP3MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP3MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP3MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP3MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT3 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP3MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP3MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP3MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT3 of PWM-XBAR
#define XBAR_TRIP3MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP3MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT3 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP4MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP4MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP4MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP4MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP4MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP4MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP4MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP4MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP4MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP4MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP4MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP4MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP4MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP4MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP4MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP4MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP4MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP4MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT4 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP4MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP4MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP4MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT4 of PWM-XBAR
#define XBAR_TRIP4MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP4MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT4 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP5MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP5MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP5MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP5MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP5MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP5MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP5MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP5MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP5MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP5MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP5MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP5MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP5MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP5MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP5MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP5MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP5MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP5MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT5 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP5MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP5MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP5MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT5 of PWM-XBAR
#define XBAR_TRIP5MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP5MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT5 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP6MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP6MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP6MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP6MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP6MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP6MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP6MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP6MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP6MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP6MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP6MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP6MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP6MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP6MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP6MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP6MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP6MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP6MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT6 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP6MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP6MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP6MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT6 of PWM-XBAR
#define XBAR_TRIP6MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP6MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT6 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP7MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP7MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP7MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP7MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP7MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP7MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP7MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP7MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP7MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP7MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP7MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP7MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP7MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP7MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP7MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP7MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP7MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP7MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT7 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP7MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP7MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP7MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT7 of PWM-XBAR
#define XBAR_TRIP7MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP7MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT7 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP8MUX0TO15CFG register
//
//*************************************************************************************************
#define XBAR_TRIP8MUX0TO15CFG_MUX0_S    0U
#define XBAR_TRIP8MUX0TO15CFG_MUX0_M    0x3U          // MUX0 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX1_S    2U
#define XBAR_TRIP8MUX0TO15CFG_MUX1_M    0xCU          // MUX1 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX2_S    4U
#define XBAR_TRIP8MUX0TO15CFG_MUX2_M    0x30U         // MUX2 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX3_S    6U
#define XBAR_TRIP8MUX0TO15CFG_MUX3_M    0xC0U         // MUX3 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX4_S    8U
#define XBAR_TRIP8MUX0TO15CFG_MUX4_M    0x300U        // MUX4 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX5_S    10U
#define XBAR_TRIP8MUX0TO15CFG_MUX5_M    0xC00U        // MUX5 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX6_S    12U
#define XBAR_TRIP8MUX0TO15CFG_MUX6_M    0x3000U       // MUX6 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX7_S    14U
#define XBAR_TRIP8MUX0TO15CFG_MUX7_M    0xC000U       // MUX7 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX8_S    16U
#define XBAR_TRIP8MUX0TO15CFG_MUX8_M    0x30000U      // MUX8 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX9_S    18U
#define XBAR_TRIP8MUX0TO15CFG_MUX9_M    0xC0000U      // MUX9 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX10_S   20U
#define XBAR_TRIP8MUX0TO15CFG_MUX10_M   0x300000U     // MUX10 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX11_S   22U
#define XBAR_TRIP8MUX0TO15CFG_MUX11_M   0xC00000U     // MUX11 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX12_S   24U
#define XBAR_TRIP8MUX0TO15CFG_MUX12_M   0x3000000U    // MUX12 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX13_S   26U
#define XBAR_TRIP8MUX0TO15CFG_MUX13_M   0xC000000U    // MUX13 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX14_S   28U
#define XBAR_TRIP8MUX0TO15CFG_MUX14_M   0x30000000U   // MUX14 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX0TO15CFG_MUX15_S   30U
#define XBAR_TRIP8MUX0TO15CFG_MUX15_M   0xC0000000U   // MUX15 Configuration for OUT8 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP8MUX16TO31CFG register
//
//*************************************************************************************************
#define XBAR_TRIP8MUX16TO31CFG_MUX16_S   0U
#define XBAR_TRIP8MUX16TO31CFG_MUX16_M   0x3U   // MUX16 Configuration for OUT8 of PWM-XBAR
#define XBAR_TRIP8MUX16TO31CFG_MUX17_S   2U
#define XBAR_TRIP8MUX16TO31CFG_MUX17_M   0xCU   // MUX17 Configuration for OUT8 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP1MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP1MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT1 of PWM-XBAR
#define XBAR_TRIP1MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT1 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP2MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP2MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT2 of PWM-XBAR
#define XBAR_TRIP2MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT2 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP3MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP3MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT3 of PWM-XBAR
#define XBAR_TRIP3MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT3 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP4MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP4MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT4 of PWM-XBAR
#define XBAR_TRIP4MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT4 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP5MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP5MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT5 of PWM-XBAR
#define XBAR_TRIP5MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT5 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP6MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP6MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT6 of PWM-XBAR
#define XBAR_TRIP6MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT6 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP7MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP7MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT7 of PWM-XBAR
#define XBAR_TRIP7MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT7 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIP8MUXENABLE register
//
//*************************************************************************************************
#define XBAR_TRIP8MUXENABLE_MUX0    0x1U       // MUX0 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX1    0x2U       // MUX1 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX2    0x4U       // MUX2 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX3    0x8U       // MUX3 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX4    0x10U      // MUX4 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX5    0x20U      // MUX5 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX6    0x40U      // MUX6 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX7    0x80U      // MUX7 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX8    0x100U     // MUX8 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX9    0x200U     // MUX9 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX10   0x400U     // MUX10 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX11   0x800U     // MUX11 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX12   0x1000U    // MUX12 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX13   0x2000U    // MUX13 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX14   0x4000U    // MUX14 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX15   0x8000U    // MUX15 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX16   0x10000U   // MUX16 to drive OUT8 of PWM-XBAR
#define XBAR_TRIP8MUXENABLE_MUX17   0x20000U   // MUX17 to drive OUT8 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIPOUTINV register
//
//*************************************************************************************************
#define XBAR_TRIPOUTINV_OUT1   0x1U    // Selects polarity for OUT1 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT2   0x2U    // Selects polarity for OUT2 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT3   0x4U    // Selects polarity for OUT3 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT4   0x8U    // Selects polarity for OUT4 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT5   0x10U   // Selects polarity for OUT5 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT6   0x20U   // Selects polarity for OUT6 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT7   0x40U   // Selects polarity for OUT7 of PWM-XBAR
#define XBAR_TRIPOUTINV_OUT8   0x80U   // Selects polarity for OUT8 of PWM-XBAR

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIPLOCK register
//
//*************************************************************************************************
#define XBAR_TRIPLOCK_LOCK    0x1U          // Locks the configuration for PWM-XBAR
#define XBAR_TRIPLOCK_KEY_S   16U
#define XBAR_TRIPLOCK_KEY_M   0xFFFF0000U   // Write protection KEY



#endif
