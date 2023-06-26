//###########################################################################
//
// FILE:   f28004x_sw_prioritized_pievect.c
//
// TITLE:  SW Prioritized PIE Vector Table Initialization.
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

//
// Included Files
//
#include "f28004x_device.h"
#include "f28004x_examples.h"
#include "f28004x_sw_prioritized_isr_levels.h"

const struct PIE_VECT_TABLE PieVectTableInit =
{
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved
    PIE_RESERVED_ISR,               // Reserved

    //
    // Non-Peripheral Interrupts:
    //
    #if (INT13PL != 0)
    TIMER1_ISR,                     // CPU Timer 1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (INT14PL != 0)
    TIMER2_ISR,                     // CPU Timer 2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (INT15PL != 0)
    DATALOG_ISR,                    // Datalogging interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (INT16PL != 0)
    RTOS_ISR,                       // RTOS Interrupt
    #else
    NOTUSED_ISR,
    #endif

    EMU_ISR,                        // Emulation Interrupt
    NMI_ISR,                        // Non-Maskable Interrupt
    ILLEGAL_ISR,                    // Illegal Operation Trap
    USER1_ISR,                      // User Defined Trap 1
    USER2_ISR,                      // User Defined Trap 2
    USER3_ISR,                      // User Defined Trap 3
    USER4_ISR,                      // User Defined Trap 4
    USER5_ISR,                      // User Defined Trap 5
    USER6_ISR,                      // User Defined Trap 6
    USER7_ISR,                      // User Defined Trap 7
    USER8_ISR,                      // User Defined Trap 8
    USER9_ISR,                      // User Defined Trap 9
    USER10_ISR,                     // User Defined Trap 10
    USER11_ISR,                     // User Defined Trap 11
    USER12_ISR,                     // User Defined Trap 12

    //
    // Group 1 PIE Vectors:
    //
    #if (G1_1PL != 0)
    ADCA1_ISR,                      // 1.1 - ADCA Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G1_2PL != 0)
    ADCB1_ISR,                      // 1.2 - ADCB Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G1_3PL != 0)
    ADCC1_ISR,                      // 1.3 - ADCC Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G1_4PL != 0)
    XINT1_ISR,                      // 1.4 - XINT1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G1_5PL != 0)
    XINT2_ISR,                      // 1.5 - XINT2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 1.6 - Reserved

    #if (G1_7PL != 0)
    TIMER0_ISR,                     // 1.7 - Timer 0 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G1_8PL != 0)
    WAKE_ISR,                       // 1.8 - Halt Wakeup Interrupt
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 2 PIE Vectors:
    //
    #if (G2_1PL != 0)
    EPWM1_TZ_ISR,                   // 2.1 - ePWM1 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_2PL != 0)
    EPWM2_TZ_ISR,                   // 2.2 - ePWM2 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_3PL != 0)
    EPWM3_TZ_ISR,                   // 2.3 - ePWM3 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_4PL != 0)
    EPWM4_TZ_ISR,                   // 2.4 - ePWM4 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_5PL != 0)
    EPWM5_TZ_ISR,                   // 2.5 - ePWM5 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_6PL != 0)
    EPWM6_TZ_ISR,                   // 2.6 - ePWM6 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_7PL != 0)
    EPWM7_TZ_ISR,                   // 2.7 - ePWM7 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G2_8PL != 0)
    EPWM8_TZ_ISR,                   // 2.8 - ePWM8 Trip Zone Interrupt
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 3 PIE Vectors:
    //
    #if (G3_1PL != 0)
    EPWM1_ISR,                      // 3.1 - ePWM1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_2PL != 0)
    EPWM2_ISR,                      // 3.2 - ePWM2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_3PL != 0)
    EPWM3_ISR,                      // 3.3 - ePWM3 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_4PL != 0)
    EPWM4_ISR,                      // 3.4 - ePWM4 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_5PL != 0)
    EPWM5_ISR,                      // 3.5 - ePWM5 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_6PL != 0)
    EPWM6_ISR,                      // 3.6 - ePWM6 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_7PL != 0)
    EPWM7_ISR,                      // 3.7 - ePWM7 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G3_8PL != 0)
    EPWM8_ISR,                      // 3.8 - ePWM8 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 4 PIE Vectors:
    //
    #if (G4_1PL != 0)
    ECAP1_ISR,                      // 4.1 - eCAP1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_2PL != 0)
    ECAP2_ISR,                      // 4.2 - eCAP2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_3PL != 0)
    ECAP3_ISR,                      // 4.3 - eCAP3 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_4PL != 0)
    ECAP4_ISR,                      // 4.4 - eCAP4 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_5PL != 0)
    ECAP5_ISR,                      // 4.5 - eCAP5 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_6PL != 0)
    ECAP6_ISR,                      // 4.6 - eCAP6 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_7PL != 0)
    ECAP7_ISR,                      // 4.7 - eCAP7 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 4.8 - Reserved

    //
    // Group 5 PIE Vectors:
    //
    #if (G5_1PL != 0)
    EQEP1_ISR,                      // 5.1 - eQEP1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G5_2PL != 0)
    EQEP2_ISR,                      // 5.2 - eQEP2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 5.3 - Reserved
    PIE_RESERVED_ISR,               // 5.4 - Reserved
    PIE_RESERVED_ISR,               // 5.5 - Reserved
    PIE_RESERVED_ISR,               // 5.6 - Reserved
    PIE_RESERVED_ISR,               // 5.7 - Reserved
    PIE_RESERVED_ISR,               // 5.8 - Reserved

    //
    // Group 6 PIE Vectors:
    //
    #if (G6_1PL != 0)
    SPIA_RX_ISR,                    // 6.1 - SPIA Receive Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G6_2PL != 0)
    SPIA_TX_ISR,                    // 6.2 - SPIA Transmit Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G6_3PL != 0)
    SPIB_RX_ISR,                    // 6.3 - SPIB Receive Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G6_4PL != 0)
    SPIB_TX_ISR,                    // 6.4 - SPIB Transmit Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 6.5 - Reserved
    PIE_RESERVED_ISR,               // 6.6 - Reserved
    PIE_RESERVED_ISR,               // 6.7 - Reserved
    PIE_RESERVED_ISR,               // 6.8 - Reserved

    //
    // Group 7 PIE Vectors:
    //
    #if (G7_1PL != 0)
    DMA_CH1_ISR,                    // 7.1 - DMA Channel 1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_2PL != 0)
    DMA_CH2_ISR,                    // 7.2 - DMA Channel 2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_3PL != 0)
    DMA_CH3_ISR,                    // 7.3 - DMA Channel 3 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_4PL != 0)
    DMA_CH4_ISR,                    // 7.4 - DMA Channel 4 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_5PL != 0)
    DMA_CH5_ISR,                    // 7.5 - DMA Channel 5 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_6PL != 0)
    DMA_CH6_ISR,                    // 7.6 - DMA Channel 6 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 7.7 - Reserved
    PIE_RESERVED_ISR,               // 7.8 - Reserved

    //
    // Group 8 PIE Vectors:
    //
    #if (G8_1PL != 0)
    I2CA_ISR,                       // 8.1 - I2CA Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G8_2PL != 0)
    I2CA_FIFO_ISR,                  // 8.2 - I2CA Interrupt 2
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 8.3 - Reserved
    PIE_RESERVED_ISR,               // 8.4 - Reserved
    PIE_RESERVED_ISR,               // 8.5 - Reserved
    PIE_RESERVED_ISR,               // 8.6 - Reserved
    PIE_RESERVED_ISR,               // 8.7 - Reserved
    PIE_RESERVED_ISR,               // 8.8 - Reserved

    //
    // Group 9 PIE Vectors:
    //
    #if (G9_1PL != 0)
    SCIA_RX_ISR,                    // 9.1 - SCIA Receive Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_2PL != 0)
    SCIA_TX_ISR,                    // 9.2 - SCIA Transmit Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_3PL != 0)
    SCIB_RX_ISR,                    // 9.3 - SCIB Receive Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_4PL != 0)
    SCIB_TX_ISR,                    // 9.4 - SCIB Transmit Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_5PL != 0)
    CANA0_ISR,                      // 9.5 - CANA Interrupt 0
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_6PL != 0)
    CANA1_ISR,                      // 9.6 - CANA Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_7PL != 0)
    CANB0_ISR,                      // 9.7 - CANB Interrupt 0
    #else
    NOTUSED_ISR,
    #endif

    #if (G9_8PL != 0)
    CANB1_ISR,                      // 9.8 - CANB Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 10 PIE Vectors
    //
    #if (G10_1PL != 0)
    ADCA_EVT_ISR,                   // 10.1 - ADCA Event Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_2PL != 0)
    ADCA2_ISR,                      // 10.2 - ADCA Interrupt 2
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_3PL != 0)
    ADCA3_ISR,                      // 10.3 - ADCA Interrupt 3
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_4PL != 0)
    ADCA4_ISR,                      // 10.4 - ADCA Interrupt 4
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_5PL != 0)
    ADCB_EVT_ISR,                   // 10.5 - ADCB Event Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_6PL != 0)
    ADCB2_ISR,                      // 10.6 - ADCB Interrupt 2
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_7PL != 0)
    ADCB3_ISR,                      // 10.7 - ADCB Interrupt 3
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_8PL != 0)
    ADCB4_ISR,                      // 10.8 - ADCB Interrupt 4
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 11 PIE Vectors
    //
    #if (G11_1PL != 0)
    CLA1_1_ISR,                     // 11.1 - CLA1 Interrupt 1
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_2PL != 0)
    CLA1_2_ISR,                     // 11.2 - CLA1 Interrupt 2
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_3PL != 0)
    CLA1_3_ISR,                     // 11.3 - CLA1 Interrupt 3
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_4PL != 0)
    CLA1_4_ISR,                     // 11.4 - CLA1 Interrupt 4
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_5PL != 0)
    CLA1_5_ISR,                     // 11.5 - CLA1 Interrupt 5
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_6PL != 0)
    CLA1_6_ISR,                     // 11.6 - CLA1 Interrupt 6
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_7PL != 0)
    CLA1_7_ISR,                     // 11.7 - CLA1 Interrupt 7
    #else
    NOTUSED_ISR,
    #endif

    #if (G11_8PL != 0)
    CLA1_8_ISR,                     // 11.8 - CLA1 Interrupt 8
    #else
    NOTUSED_ISR,
    #endif

    //
    // Group 12 PIE Vectors
    //
    #if (G12_1PL != 0)
    XINT3_ISR,                      // 12.1 - XINT3 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_2PL != 0)
    XINT4_ISR,                      // 12.2 - XINT4 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_3PL != 0)
    XINT5_ISR,                      // 12.3 - XINT5 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 12.4 - Reserved
    PIE_RESERVED_ISR,               // 12.5 - Reserved
    PIE_RESERVED_ISR,               // 12.6 - Reserved

    #if (G12_7PL != 0)
    FPU_OVERFLOW_ISR,               // 12.7 - FPU Overflow Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_8PL != 0)
    FPU_UNDERFLOW_ISR,              // 12.8 - FPU Underflow Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 1.9 - Reserved
    PIE_RESERVED_ISR,               // 1.10 - Reserved
    PIE_RESERVED_ISR,               // 1.11 - Reserved
    PIE_RESERVED_ISR,               // 1.12 - Reserved
    PIE_RESERVED_ISR,               // 1.13 - Reserved
    PIE_RESERVED_ISR,               // 1.14 - Reserved
    PIE_RESERVED_ISR,               // 1.15 - Reserved
    PIE_RESERVED_ISR,               // 1.16 - Reserved
    PIE_RESERVED_ISR,               // 2.9 - Reserved
    PIE_RESERVED_ISR,               // 2.10 - Reserved
    PIE_RESERVED_ISR,               // 2.11 - Reserved
    PIE_RESERVED_ISR,               // 2.12 - Reserved
    PIE_RESERVED_ISR,               // 2.13 - Reserved
    PIE_RESERVED_ISR,               // 2.14 - Reserved
    PIE_RESERVED_ISR,               // 2.15 - Reserved
    PIE_RESERVED_ISR,               // 2.16 - Reserved
    PIE_RESERVED_ISR,               // 3.9 - Reserved
    PIE_RESERVED_ISR,               // 3.10 - Reserved
    PIE_RESERVED_ISR,               // 3.11 - Reserved
    PIE_RESERVED_ISR,               // 3.12 - Reserved
    PIE_RESERVED_ISR,               // 3.13 - Reserved
    PIE_RESERVED_ISR,               // 3.14 - Reserved
    PIE_RESERVED_ISR,               // 3.15 - Reserved
    PIE_RESERVED_ISR,               // 3.16 - Reserved
    PIE_RESERVED_ISR,               // 4.9 - Reserved
    PIE_RESERVED_ISR,               // 4.10 - Reserved
    PIE_RESERVED_ISR,               // 4.11 - Reserved
    PIE_RESERVED_ISR,               // 4.12 - Reserved
    PIE_RESERVED_ISR,               // 4.13 - Reserved

    #if (G4_14PL != 0)
    ECAP6_2_ISR,                    // 4.14 - eCAP6_2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G4_15PL != 0)
    ECAP7_2_ISR,                    // 4.15 - eCAP7_2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 4.16 - Reserved

    #if (G5_9PL != 0)
    SD1_ISR,                        // 5.9 - SD1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 5.10 - Reserved
    PIE_RESERVED_ISR,               // 5.11 - Reserved
    PIE_RESERVED_ISR,               // 5.12 - Reserved

    #if (G5_13PL != 0)
    SD1DR1_ISR,                     // 5.13 - SD1DR1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G5_14PL != 0)
    SD1DR2_ISR,                     // 5.14 - SD1DR2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G5_15PL != 0)
    SD1DR3_ISR,                     // 5.15 - SD1DR3 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G5_16PL != 0)
    SD1DR4_ISR,                     // 5.16 - SD1DR4 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 6.9 - Reserved
    PIE_RESERVED_ISR,               // 6.10 - Reserved
    PIE_RESERVED_ISR,               // 6.11 - Reserved
    PIE_RESERVED_ISR,               // 6.12 - Reserved
    PIE_RESERVED_ISR,               // 6.13 - Reserved
    PIE_RESERVED_ISR,               // 6.14 - Reserved
    PIE_RESERVED_ISR,               // 6.15 - Reserved
    PIE_RESERVED_ISR,               // 6.16 - Reserved
    PIE_RESERVED_ISR,               // 7.9 - Reserved
    PIE_RESERVED_ISR,               // 7.10 - Reserved

    #if (G7_11PL != 0)
    FSITXA1_ISR,                    // 7.11 - FSITXA1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_12PL != 0)
    FSITXA2_ISR,                    // 7.12 - FSITXA2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_13PL != 0)
    FSIRXA1_ISR,                    // 7.13 - FSIRXA1 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_14PL != 0)
    FSIRXA2_ISR,                    // 7.14 - FSIRXA2 Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G7_15PL != 0)
    CLA1PROMCRC_ISR,                // 7.15 - CLA1PROMCRC Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 7.16 - Reserved

    #if (G8_9PL != 0)
    LINA_0_ISR,                     // 8.9 - LINA Interrupt0
    #else
    NOTUSED_ISR,
    #endif

    #if (G8_10PL != 0)
    LINA_1_ISR,                     // 8.10 - LINA Interrupt1
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 8.11 - Reserved
    PIE_RESERVED_ISR,               // 8.12 - Reserved

    #if (G8_13PL != 0)
    PMBUSA_ISR,                     // 8.13 - PMBUSA Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 8.14 - Reserved
    PIE_RESERVED_ISR,               // 8.15 - Reserved
    PIE_RESERVED_ISR,               // 8.16 - Reserved
    PIE_RESERVED_ISR,               // 9.9 - Reserved
    PIE_RESERVED_ISR,               // 9.10 - Reserved
    PIE_RESERVED_ISR,               // 9.11 - Reserved
    PIE_RESERVED_ISR,               // 9.12 - Reserved
    PIE_RESERVED_ISR,               // 9.13 - Reserved
    PIE_RESERVED_ISR,               // 9.14 - Reserved
    PIE_RESERVED_ISR,               // 9.15 - Reserved
    PIE_RESERVED_ISR,               // 9.16 - Reserved

    #if (G10_9PL != 0)
    ADCC_EVT_ISR,                   // 10.9 - ADCC Event Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_10PL != 0)
    ADCC2_ISR,                      // 10.10 - ADCC Interrupt 2
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_11PL != 0)
    ADCC3_ISR,                      // 10.11 - ADCC Interrupt 3
    #else
    NOTUSED_ISR,
    #endif

    #if (G10_12PL != 0)
    ADCC4_ISR,                      // 10.12 - ADCC Interrupt 4
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 10.13 - Reserved
    PIE_RESERVED_ISR,               // 10.14 - Reserved
    PIE_RESERVED_ISR,               // 10.15 - Reserved
    PIE_RESERVED_ISR,               // 10.16 - Reserved
    PIE_RESERVED_ISR,               // 11.9 - Reserved
    PIE_RESERVED_ISR,               // 11.10 - Reserved
    PIE_RESERVED_ISR,               // 11.11 - Reserved
    PIE_RESERVED_ISR,               // 11.12 - Reserved
    PIE_RESERVED_ISR,               // 11.13 - Reserved
    PIE_RESERVED_ISR,               // 11.14 - Reserved
    PIE_RESERVED_ISR,               // 11.15 - Reserved
    PIE_RESERVED_ISR,               // 11.16 - Reserved
    PIE_RESERVED_ISR,               // 12.9 - Reserved

    #if (G12_10PL != 0)
    RAM_CORRECTABLE_ERROR_ISR,      // 12.10 - RAM Correctable Error Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_11PL != 0)
    FLASH_CORRECTABLE_ERROR_ISR,    // 12.11 - Flash Correctable Error Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_12PL != 0)
    RAM_ACCESS_VIOLATION_ISR,       // 12.12 - RAM Access Violation Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_13PL != 0)
    SYS_PLL_SLIP_ISR,               // 12.13 - System PLL Slip Interrupt
    #else
    NOTUSED_ISR,
    #endif

    PIE_RESERVED_ISR,               // 12.14 - Reserved

    #if (G12_15PL != 0)
    CLA_OVERFLOW_ISR,               // 12.15 - CLA Overflow Interrupt
    #else
    NOTUSED_ISR,
    #endif

    #if (G12_16PL != 0)
    CLA_UNDERFLOW_ISR               // 12.16 - CLA Underflow Interrupt
    #else
    NOTUSED_ISR,
    #endif

};

//
// InitPieVectTable - This function initializes the PIE vector table to a known
// state. This function must be executed after boot time.
//
void
InitPieVectTable(void)
{
    uint16_t i;
    uint32_t *Source = (void *) &PieVectTableInit;
    uint32_t *Dest   = (void *) &PieVectTable;

    //
    // Do not write over first 3 32-bit locations (these locations are
    // initialized by Boot ROM with boot variables)
    //
    Source = Source + 3;
    Dest = Dest + 3;

    EALLOW;

    for(i = 0; i < 221; i++)
    {
        *Dest++ = *Source++;
    }

    EDIS;
}

//
// End of File
//
