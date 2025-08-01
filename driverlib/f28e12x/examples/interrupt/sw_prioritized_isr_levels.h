//###########################################################################
//
// FILE:    sw_prioritized_isr_levels.h
//
// TITLE:   Software Prioritized Interrupt Service Routine Level
//          definitions.
//
//#############################################################################
//
//
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
//#############################################################################
#ifndef SW_PRIORITZIED_ISR_LEVELS_H
#define SW_PRIORITZIED_ISR_LEVELS_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Mask for interrupt groups
//
#define M_INT1      0x0001  // INT1 Mask
#define M_INT2      0x0002  // INT2 Mask
#define M_INT3      0x0004  // INT3 Mask
#define M_INT4      0x0008  // INT4 Mask
#define M_INT5      0x0010  // INT5 Mask
#define M_INT6      0x0020  // INT6 Mask
#define M_INT7      0x0040  // INT7 Mask
#define M_INT8      0x0080  // INT8 Mask
#define M_INT9      0x0100  // INT9 Mask
#define M_INT10     0x0200  // INT10 Mask
#define M_INT11     0x0400  // INT11 Mask
#define M_INT12     0x0800  // INT12 Mask
#define M_INT13     0x1000  // INT13 Mask
#define M_INT14     0x2000  // INT14 Mask
#define M_DLOG      0x4000  // DLOGINT Mask
#define M_RTOS      0x8000  // RTOSINT Mask

//
// Interrupt Enable Register Allocation:
// Interrupts can be enabled/disabled using the CPU interrupt enable register
// (IER) and the PIE interrupt enable registers (PIEIER1 to PIEIER12).
//

//
// Set "Global" Interrupt Priority Level (IER register):
//
// The user must set the appropriate priority level for each of the CPU
// interrupts. This is termed as the "global" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used.
//
// Note: The priority levels below are used to calculate the IER register
//       interrupt masks MINT1 to MINT16.
//
// Note: The priority levels shown here may not make sense in a
//       real application.  This is for demonstration purposes only!!!
//
//       The user should change these to values that make sense for
//       their application.
//
// 0  = not used
// 1  = highest priority
// ...
// 16 = lowest priority
//
#define INT1PL      16       // Global Priority for Group1 Interrupts
#define INT2PL      0        // Global Priority for Group2 Interrupts
#define INT3PL      0        // Global Priority for Group3 Interrupts
#define INT4PL      0        // Global Priority for Group4 Interrupts
#define INT5PL      0        // Global Priority for Group5 Interrupts
#define INT6PL      0        // Global Priority for Group6 Interrupts
#define INT7PL      0        // Global Priority for Group7 Interrupts
#define INT8PL      0        // Global Priority for Group8 Interrupts
#define INT9PL      0        // Global Priority for Group9 Interrupts
#define INT10PL     0        // Global Priority for Group10 Interrupts
#define INT11PL     0        // Global Priority for Group11 Interrupts
#define INT12PL     0        // Global Priority for Group12 Interrupts
#define INT13PL     7        // Global Priority for INT13 (TINT1)
#define INT14PL     1        // Global Priority for INT14 (TINT2)
#define INT15PL     0        // Global Priority for DATALOG
#define INT16PL     0        // Global Priority for RTOSINT

//
// Set "Group" Interrupt Priority Level (PIEIER1 to PIEIER12 registers):
//
// The user must set the appropriate priority level for each of the PIE
// interrupts. This is termed as the "group" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used.
//
// Note: The priority levels below are used to calculate the following
//       PIEIER register interrupt masks:
//       MG1_1 to MG1_4
//       MG2_1 to MG2_4
//       MG3_1 to MG3_16
//       MG4_1 to MG4_16
//       MG5_1 to MG5_16
//       MG6_1 to MG6_16
//       MG7_1 to MG7_16
//       MG8_1 to MG8_16
//       MG9_1 to MG9_16
//       MG10_1 to MG10_16
//       MG11_1 to MG11_16
//       MG12_1 to MG12_16
//
// Note: The priority levels shown here may not make sense in a
//       real application.  This is for demonstration purposes only!!!
//
//       The user should change these to values that make sense for
//       their application.
//
// 0  = not used
// 1  = highest priority
// ...
// 16  = lowest priority
//
#define G1_1PL      0       // ADCA1_INT
#define G1_2PL      0       // Reserved
#define G1_3PL      0       // XINT1_INT
#define G1_4PL      0       // XINT2_INT

#define G2_1PL      0       // SYS_ERR_INT
#define G2_2PL      4       // TIMER0_INT
#define G2_3PL      0       // WAKE_INT
#define G2_4PL      0       // MCPWM1_INT

#define G3_1PL      0       // Reserved
#define G3_2PL      0       // MCPWM3_INT
#define G3_3PL      0       // Reserved
#define G3_4PL      0       // Reserved

#define G4_1PL      0       // Reserved
#define G4_2PL      0       // Reserved
#define G4_3PL      0       // ECAP1_INT
#define G4_4PL      0       // Reserved

#define G5_1PL      0       // EQEP1_INT
#define G5_2PL      0       // SPIA_RX_INT
#define G5_3PL      0       // SPIA_TX_INT
#define G5_4PL      0       // Reserved

#define G6_1PL      0       // Reserved
#define G6_2PL      0       // DCC0_INT
#define G6_3PL      0       // DMA_CH1_INT
#define G6_4PL      0       // DMA_CH2_INT

#define G7_1PL      0       // Reserved
#define G7_2PL      0       // I2CA_INT
#define G7_3PL      0       // I2CB_INT
#define G7_4PL      0       // SCIA_RX_INT

#define G8_1PL      0       // SCIA_TX_INT
#define G8_2PL      4       // SCIB_RX_INT
#define G8_3PL      0       // SCIB_TX_INT
#define G8_4PL      0       // Reserved

#define G9_1PL      0       // Reserved
#define G9_2PL      0       // UART0_INT
#define G9_3PL      0       // ADCA_EVT_INT
#define G9_4PL      0       // ADCA2_INT

#define G10_1PL      0       // Reserved
#define G10_2PL      0       // Reserved
#define G10_3PL      0       // XINT3_INT
#define G10_4PL      0       // XINT4_INT

#define G11_1PL      0       // XINT5_INT
#define G11_2PL      0       // FLSS_INT
#define G11_3PL      0       // Reserved
#define G11_4PL      0       // Reserved

#define G12_1PL      0       // Reserved
#define G12_2PL      0       // Reserved
#define G12_3PL      0       // Reserved
#define G12_4PL      0       // Reserved

//
// Include the header file with software interrupt prioritization logic
//
#include "sw_interrupt_prioritization_logic.h"

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // eof

//
// End of file
//
