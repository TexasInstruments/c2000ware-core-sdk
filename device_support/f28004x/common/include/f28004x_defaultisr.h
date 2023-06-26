//###########################################################################
//
// FILE:   f28004x_defaultisr.h
//
// TITLE:  f28004x Device Default Interrupt Service Routines Definitions
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28004x_DEFAULT_ISR_H
#define F28004x_DEFAULT_ISR_H
#ifdef __cplusplus
extern "C" {
#endif

//
// Default Interrupt Service Routine Declarations:
// The following function prototypes are for the
// default ISR routines used with the default PIE vector table.
// This default vector table is found in the f28004x_pievect.h
// file.
//
__interrupt void TIMER1_ISR(void);            // CPU Timer 1 Interrupt
__interrupt void TIMER2_ISR(void);            // CPU Timer 2 Interrupt
__interrupt void DATALOG_ISR(void);           // Datalogging Interrupt
__interrupt void RTOS_ISR(void);              // RTOS Interrupt
__interrupt void EMU_ISR(void);               // Emulation Interrupt
__interrupt void NMI_ISR(void);               // Non-Maskable Interrupt
__interrupt void ILLEGAL_ISR(void);           // Illegal Operation Trap
__interrupt void USER1_ISR(void);             // User Defined Trap 1
__interrupt void USER2_ISR(void);             // User Defined Trap 2
__interrupt void USER3_ISR(void);             // User Defined Trap 3
__interrupt void USER4_ISR(void);             // User Defined Trap 4
__interrupt void USER5_ISR(void);             // User Defined Trap 5
__interrupt void USER6_ISR(void);             // User Defined Trap 6
__interrupt void USER7_ISR(void);             // User Defined Trap 7
__interrupt void USER8_ISR(void);             // User Defined Trap 8
__interrupt void USER9_ISR(void);             // User Defined Trap 9
__interrupt void USER10_ISR(void);            // User Defined Trap 10
__interrupt void USER11_ISR(void);            // User Defined Trap 11
__interrupt void USER12_ISR(void);            // User Defined Trap 12
__interrupt void ADCA1_ISR(void);             // 1.1 - ADCA Interrupt 1
__interrupt void ADCB1_ISR(void);             // 1.2 - ADCB Interrupt 1
__interrupt void ADCC1_ISR(void);             // 1.3 - ADCC Interrupt 1
__interrupt void XINT1_ISR(void);             // 1.4 - XINT1 Interrupt
__interrupt void XINT2_ISR(void);             // 1.5 - XINT2 Interrupt
__interrupt void TIMER0_ISR(void);            // 1.7 - Timer 0 Interrupt
__interrupt void WAKE_ISR(void);              // 1.8 - Halt Wakeup Interrupt
__interrupt void EPWM1_TZ_ISR(void);          // 2.1 - ePWM1 Trip Zone Interrupt
__interrupt void EPWM2_TZ_ISR(void);          // 2.2 - ePWM2 Trip Zone Interrupt
__interrupt void EPWM3_TZ_ISR(void);          // 2.3 - ePWM3 Trip Zone Interrupt
__interrupt void EPWM4_TZ_ISR(void);          // 2.4 - ePWM4 Trip Zone Interrupt
__interrupt void EPWM5_TZ_ISR(void);          // 2.5 - ePWM5 Trip Zone Interrupt
__interrupt void EPWM6_TZ_ISR(void);          // 2.6 - ePWM6 Trip Zone Interrupt
__interrupt void EPWM7_TZ_ISR(void);          // 2.7 - ePWM7 Trip Zone Interrupt
__interrupt void EPWM8_TZ_ISR(void);          // 2.8 - ePWM8 Trip Zone Interrupt
__interrupt void EPWM1_ISR(void);             // 3.1 - ePWM1 Interrupt
__interrupt void EPWM2_ISR(void);             // 3.2 - ePWM2 Interrupt
__interrupt void EPWM3_ISR(void);             // 3.3 - ePWM3 Interrupt
__interrupt void EPWM4_ISR(void);             // 3.4 - ePWM4 Interrupt
__interrupt void EPWM5_ISR(void);             // 3.5 - ePWM5 Interrupt
__interrupt void EPWM6_ISR(void);             // 3.6 - ePWM6 Interrupt
__interrupt void EPWM7_ISR(void);             // 3.7 - ePWM7 Interrupt
__interrupt void EPWM8_ISR(void);             // 3.8 - ePWM8 Interrupt
__interrupt void ECAP1_ISR(void);             // 4.1 - eCAP1 Interrupt
__interrupt void ECAP2_ISR(void);             // 4.2 - eCAP2 Interrupt
__interrupt void ECAP3_ISR(void);             // 4.3 - eCAP3 Interrupt
__interrupt void ECAP4_ISR(void);             // 4.4 - eCAP4 Interrupt
__interrupt void ECAP5_ISR(void);             // 4.5 - eCAP5 Interrupt
__interrupt void ECAP6_ISR(void);             // 4.6 - eCAP6 Interrupt
__interrupt void ECAP7_ISR(void);             // 4.7 - eCAP7 Interrupt
__interrupt void EQEP1_ISR(void);             // 5.1 - eQEP1 Interrupt
__interrupt void EQEP2_ISR(void);             // 5.2 - eQEP2 Interrupt
__interrupt void SPIA_RX_ISR(void);           // 6.1 - SPIA Receive Interrupt
__interrupt void SPIA_TX_ISR(void);           // 6.2 - SPIA Transmit Interrupt
__interrupt void SPIB_RX_ISR(void);           // 6.3 - SPIB Receive Interrupt
__interrupt void SPIB_TX_ISR(void);           // 6.4 - SPIB Transmit Interrupt
__interrupt void DMA_CH1_ISR(void);           // 7.1 - DMA Channel 1 Interrupt
__interrupt void DMA_CH2_ISR(void);           // 7.2 - DMA Channel 2 Interrupt
__interrupt void DMA_CH3_ISR(void);           // 7.3 - DMA Channel 3 Interrupt
__interrupt void DMA_CH4_ISR(void);           // 7.4 - DMA Channel 4 Interrupt
__interrupt void DMA_CH5_ISR(void);           // 7.5 - DMA Channel 5 Interrupt
__interrupt void DMA_CH6_ISR(void);           // 7.6 - DMA Channel 6 Interrupt
__interrupt void I2CA_ISR(void);              // 8.1 - I2CA Interrupt 1
__interrupt void I2CA_FIFO_ISR(void);         // 8.2 - I2CA Interrupt 2
__interrupt void SCIA_RX_ISR(void);           // 9.1 - SCIA Receive Interrupt
__interrupt void SCIA_TX_ISR(void);           // 9.2 - SCIA Transmit Interrupt
__interrupt void SCIB_RX_ISR(void);           // 9.3 - SCIB Receive Interrupt
__interrupt void SCIB_TX_ISR(void);           // 9.4 - SCIB Transmit Interrupt
__interrupt void CANA0_ISR(void);             // 9.5 - CANA Interrupt 0
__interrupt void CANA1_ISR(void);             // 9.6 - CANA Interrupt 1
__interrupt void CANB0_ISR(void);             // 9.7 - CANB Interrupt 0
__interrupt void CANB1_ISR(void);             // 9.8 - CANB Interrupt 1
__interrupt void ADCA_EVT_ISR(void);          // 10.1 - ADCA Event Interrupt
__interrupt void ADCA2_ISR(void);             // 10.2 - ADCA Interrupt 2
__interrupt void ADCA3_ISR(void);             // 10.3 - ADCA Interrupt 3
__interrupt void ADCA4_ISR(void);             // 10.4 - ADCA Interrupt 4
__interrupt void ADCB_EVT_ISR(void);          // 10.5 - ADCB Event Interrupt
__interrupt void ADCB2_ISR(void);             // 10.6 - ADCB Interrupt 2
__interrupt void ADCB3_ISR(void);             // 10.7 - ADCB Interrupt 3
__interrupt void ADCB4_ISR(void);             // 10.8 - ADCB Interrupt 4
__interrupt void CLA1_1_ISR(void);            // 11.1 - CLA1 Interrupt 1
__interrupt void CLA1_2_ISR(void);            // 11.2 - CLA1 Interrupt 2
__interrupt void CLA1_3_ISR(void);            // 11.3 - CLA1 Interrupt 3
__interrupt void CLA1_4_ISR(void);            // 11.4 - CLA1 Interrupt 4
__interrupt void CLA1_5_ISR(void);            // 11.5 - CLA1 Interrupt 5
__interrupt void CLA1_6_ISR(void);            // 11.6 - CLA1 Interrupt 6
__interrupt void CLA1_7_ISR(void);            // 11.7 - CLA1 Interrupt 7
__interrupt void CLA1_8_ISR(void);            // 11.8 - CLA1 Interrupt 8
__interrupt void XINT3_ISR(void);             // 12.1 - XINT3 Interrupt
__interrupt void XINT4_ISR(void);             // 12.2 - XINT4 Interrupt
__interrupt void XINT5_ISR(void);             // 12.3 - XINT5 Interrupt
__interrupt void FPU_OVERFLOW_ISR(void);      // 12.7 - FPU Overflow Interrupt
__interrupt void FPU_UNDERFLOW_ISR(void);     // 12.8 - FPU Underflow Interrupt
__interrupt void ECAP6_2_ISR(void);     // 4.14 - eCAP6 HR Calibration Interrupt
__interrupt void ECAP7_2_ISR(void);      // 4.15 - eCAP6 HR Calibration Interrupt
__interrupt void SD1_ISR(void);          // 5.9 - SD1 Interrupt
__interrupt void SD1DR1_ISR(void);       // 5.13 - SDFM1 DR Interrupt 1
__interrupt void SD1DR2_ISR(void);       // 5.14 - SDFM1 DR Interrupt 2
__interrupt void SD1DR3_ISR(void);       // 5.15 - SDFM1 DR Interrupt 3
__interrupt void SD1DR4_ISR(void);       // 5.16 - SDFM1 DR Interrupt 4
__interrupt void FSITXA1_ISR(void);      // 7.11 - FSITXA1 Interrupt
__interrupt void FSITXA2_ISR(void);      // 7.12 - FSITXA2 Interrupt
__interrupt void FSIRXA1_ISR(void);      // 7.13 - FSIRXA1 Interrupt
__interrupt void FSIRXA2_ISR(void);      // 7.14 - FSIRXA2 Interrupt
__interrupt void CLA1PROMCRC_ISR(void);  // 7.15 - CLAP1ROMCRC Interrupt
__interrupt void LINA_0_ISR(void);       // 8.9 - LINA Interrupt 0
__interrupt void LINA_1_ISR(void);       // 8.10 - LINA Interrupt 1
__interrupt void PMBUSA_ISR(void);       // 8.13 - PMBUSA Interrupt
__interrupt void ADCC_EVT_ISR(void);     // 10.9 - ADCC Event Interrupt
__interrupt void ADCC2_ISR(void);        // 10.10 - ADCC Interrupt 2
__interrupt void ADCC3_ISR(void);        // 10.11 - ADCC Interrupt 3
__interrupt void ADCC4_ISR(void);        // 10.12 - ADCC Interrupt 4
//
// 12.10 - RAM Correctable Error Interrupt
//
__interrupt void RAM_CORRECTABLE_ERROR_ISR(void);

//
// 12.11 - Flash Correctable Error Interrupt
//
__interrupt void FLASH_CORRECTABLE_ERROR_ISR(void);

//
// 12.12 - RAM Access Violation Interrupt
//
__interrupt void RAM_ACCESS_VIOLATION_ISR(void);

__interrupt void SYS_PLL_SLIP_ISR(void);  // 12.13 - System PLL Slip Interrupt
__interrupt void CLA_OVERFLOW_ISR(void);  // 12.15 - CLA Overflow Interrupt
__interrupt void CLA_UNDERFLOW_ISR(void); // 12.16 - CLA Underflow Interrupt

//
// Catch-all for PIE Reserved Locations for testing purposes:
//
__interrupt void PIE_RESERVED_ISR(void);                // Reserved ISR
__interrupt void EMPTY_ISR(void);                       // Only does a return
__interrupt void NOTUSED_ISR(void);                     // Unused ISR
#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                               // end of F28004x_PIEVECT_H definition
//
// End of file.
//


