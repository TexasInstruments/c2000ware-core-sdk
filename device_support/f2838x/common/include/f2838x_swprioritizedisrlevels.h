//###########################################################################
//
// FILE:    f2838x_swprioritizedisrlevels.h
//
// TITLE:   F28 Devices Software Prioritized Interrupt Service Routine
//          Level definitions.
//
//###########################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef F2838x_SW_PRIORITZIED_ISR_H
#define F2838x_SW_PRIORITZIED_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Interrupt Enable Register Allocation For F2838x Devices:
//
// Interrupts can be enabled/disabled using the CPU interrupt enable register
// (IER) and the PIE interrupt enable registers (PIEIER1 to PIEIER12).
//
//
// Set "Global" Interrupt Priority Level (IER register):
//
// The user must set the appropriate priority level for each of the CPU
// interrupts. This is termed as the "global" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used. This
// will also reduce code size by not including ISR's that are not used.
//
// Note: The priority levels below are used to calculate the IER register
//       interrupt masks MINT1 to MINT16.
//
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
#define	INT1PL      2        // Group1 Interrupts (PIEIER1)
#define	INT2PL      1        // Group2 Interrupts (PIEIER2)
#define	INT3PL      4        // Group3 Interrupts (PIEIER3)
#define	INT4PL      2        // Group4 Interrupts (PIEIER4)
#define	INT5PL      2        // Group5 Interrupts (PIEIER5)
#define	INT6PL      3        // Group6 Interrupts (PIEIER6)
#define	INT7PL      5        // Group7 Interrupts (PIEIER6)
#define	INT8PL      5        // Group8 Interrupts (PIEIER6)
#define	INT9PL      3        // Group9 Interrupts (PIEIER9)
#define	INT10PL     6        // Group10 Interrupts (PIEIER6)
#define	INT11PL     6        // Group11 Interrupts (PIEIER6)
#define	INT12PL     8        // Group12 Interrupts (PIEIER6)
#define	INT13PL     4        // INT13 (TINT1)
#define	INT14PL     4        // INT14 (TINT2)
#define	INT15PL     4        // DATALOG
#define	INT16PL     4        // RTOSINT

//
// Set "Group" Interrupt Priority Level (PIEIER1 to PIEIER12 registers):
//
// The user must set the appropriate priority level for each of the PIE
// interrupts. This is termed as the "group" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used. This
// will also reduce code size by not including ISR's that are not used:
//
// Note: The priority levels below are used to calculate the following
//       PIEIER register interrupt masks:
//                           MG1_1 to MG1_16
//                           MG2_1 to MG2_16
//                           MG3_1 to MG3_16
//                           MG4_1 to MG4_16
//                           MG5_1 to MG5_16
//                           MG6_1 to MG6_16
//                           MG7_1 to MG7_16
//                           MG8_1 to MG8_16
//                           MG9_1 to MG9_16
//                           MG10_1 to MG10_16
//                           MG11_1 to MG11_16
//                           MG12_1 to MG12_16
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
#define G1_1PL		5		// ADCA1_INT
#define G1_2PL		3		// ADCB1_INT
#define G1_3PL		1		// ADCC1_INT
#define G1_4PL		4		// XINT1_INT
#define G1_5PL		4		// XINT2_INT
#define G1_6PL		1		// ADCD1_INT
#define G1_7PL		12		// TIMER0_INT
#define G1_8PL		5		// WAKE_INT
#define G1_9PL		16   	// I2CA_HIGH_INT
#define G1_10PL		16   	// SYS_ERROR_INT
#define G1_11PL		16   	// ECATSYNC0_INT
#define G1_12PL		16   	// ECAT_INT
#define G1_13PL		8		// IPC0_INT
#define G1_14PL		13		// IPC1_INT
#define G1_15PL		15		// IPC2_INT
#define G1_16PL		9		// IPC3_INT

#define G2_1PL		13		// EPWM1_TZ_INT
#define G2_2PL		1		// EPWM2_TZ_INT
#define G2_3PL		1		// EPWM3_TZ_INT
#define G2_4PL		9		// EPWM4_TZ_INT
#define G2_5PL      3		// EPWM5_TZ_INT
#define G2_6PL		13		// EPWM6_TZ_INT
#define G2_7PL		9		// EPWM7_TZ_INT
#define G2_8PL		13		// EPWM8_TZ_INT
#define G2_9PL		15		// EPWM9_TZ_INT
#define G2_10PL		11		// EPWM10_TZ_INT
#define G2_11PL		7		// EPWM11_TZ_INT
#define G2_12PL		10		// EPWM12_TZ_INT
#define G2_13PL		16   	// EPWM13_TZ_INT
#define G2_14PL		16   	// EPWM14_TZ_INT
#define G2_15PL		16   	// EPWM15_TZ_INT
#define G2_16PL		16   	// EPWM16_TZ_INT

#define G3_1PL		5		// EPWM1_INT
#define G3_2PL		9		// EPWM2_INT
#define G3_3PL		5		// EPWM3_INT
#define G3_4PL		2		// EPWM4_INT
#define G3_5PL		12		// EPWM5_INT
#define G3_6PL		4		// EPWM6_INT
#define G3_7PL		2		// EPWM7_INT
#define G3_8PL		13		// EPWM8_INT
#define G3_9PL		4		// EPWM9_INT
#define G3_10PL		12		// EPWM10_INT
#define G3_11PL		4		// EPWM11_INT
#define G3_12PL		14		// EPWM12_INT
#define G3_13PL		16		// EPWM13_INT
#define G3_14PL		16		// EPWM14_INT
#define G3_15PL		16		// EPWM15_INT
#define G3_16PL		16		// EPWM16_INT

#define G4_1PL		3		// ECAP1_INT
#define G4_2PL		3		// ECAP2_INT
#define G4_3PL		3		// ECAP3_INT
#define G4_4PL		6		// ECAP4_INT
#define G4_5PL		7		// ECAP5_INT
#define G4_6PL		7       // ECAP6_INT
#define G4_7PL		7   	// ECAP7_INT
#define G4_8PL		0   	// Reserved
#define G4_9PL		16   	// FSITXA1_INT
#define G4_10PL		16   	// FSITXA2_INT
#define G4_11PL		16      // FSITXB1_INT
#define G4_12PL		16      // FSITXB2_INT
#define G4_13PL		16      // FSIRXA1_INT
#define G4_14PL		16   	// FSIRXA2_INT
#define G4_15PL		16   	// FSIRXB1_INT
#define G4_16PL		16      // FSIRXB2_INT

#define G5_1PL		6		// EQEP1_INT
#define G5_2PL		5		// EQEP2_INT
#define G5_3PL		5		// EQEP3_INT
#define G5_4PL		1		// Reserved
#define G5_5PL		9		// CLB1_INT
#define G5_6PL		10		// CLB2_INT
#define G5_7PL		15		// CLB3_INT
#define G5_8PL		13		// CLB4_INT
#define G5_9PL		12		// SD1_INT
#define G5_10PL		9		// SD2_INT
#define G5_11PL		16   	// ECATRST_INT
#define G5_12PL		16   	// ECATSYNC1_INT
#define G5_13PL		16   	// SDFM1DR1_INT
#define G5_14PL		16   	// SDFM1DR2_INT
#define G5_15PL		16   	// SDFM1DR3_INT
#define G5_16PL		16   	// SDFM1DR4_INT

#define G6_1PL		1		// SPIA_RX_INT
#define G6_2PL		7		// SPIA_TX_INT
#define G6_3PL		3		// SPIB_RX_INT
#define G6_4PL		3		// SPIB_TX_INT
#define G6_5PL		10		// MCBSPA_RX_INT
#define G6_6PL		7		// MCBSPA_TX_INT
#define G6_7PL		6		// MCBSPB_RX_INT
#define G6_8PL		13		// MCBSPB_TX_INT
#define G6_9PL		14		// SPIC_RX_INT
#define G6_10PL		3		// SPIC_TX_INT
#define G6_11PL		16	    // SPID_RX_INT
#define G6_12PL		16	    // SPID_TX_INT
#define G6_13PL		16		// SDFM2DR1_INT
#define G6_14PL		16		// SDFM2DR2_INT
#define G6_15PL		16		// SDFM2DR3_INT
#define G6_16PL		16		// SDFM2DR4_INT

#define G7_1PL		1		// DMA_CH1_INT
#define G7_2PL		11		// DMA_CH2_INT
#define G7_3PL		14		// DMA_CH3_INT
#define G7_4PL		3		// DMA_CH4_INT
#define G7_5PL		13		// DMA_CH5_INT
#define G7_6PL		14		// DMA_CH6_INT
#define G7_7PL		0   	// Reserved
#define G7_8PL		0   	// Reserved
#define G7_9PL		0   	// FSIRXC1_INT
#define G7_10PL		16   	// FSIRXC2_INT
#define G7_11PL		16   	// FSIRXD1_INT
#define G7_12PL		16   	// FSIRXD2_INT
#define G7_13PL		16   	// FSIRXE1_INT
#define G7_14PL		16   	// FSIRXE2_INT
#define G7_15PL		16   	// FSIRXF1_INT
#define G7_16PL		16   	// FSIRXF2_INT

#define G8_1PL		14		// I2CA_INT
#define G8_2PL		10		// I2CA_FIFO_INT
#define G8_3PL		11		// I2CB_INT
#define G8_4PL		9		// I2CB_FIFO_INT
#define G8_5PL		12		// SCIC_RX_INT
#define G8_6PL		2		// SCIC_TX_INT
#define G8_7PL		8		// SCID_RX_INT
#define G8_8PL		7		// SCID_TX_INT
#define G8_9PL		16		// FSIRXG1_INT
#define G8_10PL		16		// FSIRXG2_INT
#define G8_11PL		16		// FSIRXH1_INT
#define G8_12PL		16		// FSIRXH2_INT
#define G8_13PL		16		// Reserved
#define G8_14PL		16		// Reserved
#define G8_15PL		16		// Reserved
#define G8_16PL		16		// Reserved

#define G9_1PL		12		// SCIA_RX_INT
#define G9_2PL		14		// SCIA_TX_INT
#define G9_3PL		11		// SCIB_RX_INT
#define G9_4PL		6		// SCIB_TX_INT
#define G9_5PL		14		// CANA0_INT
#define G9_6PL		10		// CANA1_INT
#define G9_7PL		10		// CANB0_INT
#define G9_8PL		5		// CANB1_INT
#define G9_9PL		16		// MCAN0_INT
#define G9_10PL		16		// MCAN1_INT
#define G9_11PL		16		// Reserved
#define G9_12PL		16		// Reserved
#define G9_13PL		16		// PMBUSA_INT
#define G9_14PL		16		// CM_STATUS_INT
#define G9_15PL		12		// USBA_INT
#define G9_16PL		0		// Reserved

#define G10_1PL		14		// ADCA_EVT_INT
#define G10_2PL		3		// ADCA2_INT
#define G10_3PL		1		// ADCA3_INT
#define G10_4PL		12		// ADCA4_INT
#define G10_5PL		5		// ADCB_EVT_INT
#define G10_6PL		11		// ADCB2_INT
#define G10_7PL		12		// ADCB3_INT
#define G10_8PL		13		// ADCB4_INT
#define G10_9PL		7		// ADCC_EVT_INT
#define G10_10PL	8		// ADCC2_INT
#define G10_11PL	4		// ADCC3_INT
#define G10_12PL	9		// ADCC4_INT
#define G10_13PL	2		// ADCD_EVT_INT
#define G10_14PL	10		// ADCD2_INT
#define G10_15PL	11		// ADCD3_INT
#define G10_16PL	5		// ADCD4_INT

#define G11_1PL		9		// CLA1_1_INT
#define G11_2PL		6		// CLA1_2_INT
#define G11_3PL		9		// CLA1_3_INT
#define G11_4PL		9		// CLA1_4_INT
#define G11_5PL		6		// CLA1_5_INT
#define G11_6PL		13		// CLA1_6_INT
#define G11_7PL		10		// CLA1_7_INT
#define G11_8PL		15		// CLA1_8_INT
#define G11_9PL		16		// CMTOCPUXIPC0_INT
#define G11_10PL	16	    // CMTOCPUXIPC1_INT
#define G11_11PL	16	    // CMTOCPUXIPC2_INT
#define G11_12PL	16	    // CMTOCPUXIPC3_INT
#define G11_13PL	16	    // CMTOCPUXIPC4_INT
#define G11_14PL	16      // CMTOCPUXIPC5_INT
#define G11_15PL	16	    // CMTOCPUXIPC6_INT
#define G11_16PL	16	    // CMTOCPUXIPC7_INT

#define G12_1PL		3		// XINT3_INT
#define G12_2PL		6		// XINT4_INT
#define G12_3PL		10		// XINT5_INT
#define G12_4PL		5		// Reserved
#define G12_5PL		2		// FMC_INT
#define G12_6PL		11		// Reserved
#define G12_7PL		14		// FPU_OVERFLOW_ISR
#define G12_8PL		14  	// FPU_UNDERFLOW_ISR
#define G12_9PL		6   	// Reserved
#define G12_10PL	5   	// ECAP6_2_INT
#define G12_11PL	4   	// ECAP7_2_INT
#define G12_12PL	12		// Reserved
#define G12_13PL	8		// CPUCRC_INT 
#define G12_14PL	2		// CLA1CRC_INT
#define G12_15PL	12		// CLA_OVERFLOW_INT
#define G12_16PL	2		// CLA_UNDERFLOW_INT

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
