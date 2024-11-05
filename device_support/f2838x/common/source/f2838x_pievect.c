//###########################################################################
//
// FILE:   f2838x_pievect.c
//
// TITLE:  f2838x Device PIE Vector Initialization Functions
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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

//
// Included Files
//
#include "f2838x_device.h"       // f2838x Header File Include File
#include "f2838x_examples.h"     // f2838x Examples Include File

//
// Globals
//
const struct PIE_VECT_TABLE PieVectTableInit = {
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
    TIMER1_ISR,                     // CPU Timer 1 Interrupt
    TIMER2_ISR,                     // CPU Timer 2 Interrupt
    DATALOG_ISR,                    // Datalogging Interrupt
    RTOS_ISR,                       // RTOS Interrupt
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
    ADCA1_ISR,                      // 1.1 - ADCA Interrupt 1
    ADCB1_ISR,                      // 1.2 - ADCB Interrupt 1
    ADCC1_ISR,                      // 1.3 - ADCC Interrupt 1
    XINT1_ISR,                      // 1.4 - XINT1 Interrupt
    XINT2_ISR,                      // 1.5 - XINT2 Interrupt
    ADCD1_ISR,                      // 1.6 - ADCD Interrupt 1
    TIMER0_ISR,                     // 1.7 - Timer 0 Interrupt
    WAKE_ISR,                       // 1.8 - Standby and Halt Wakeup Interrupt
    EPWM1_TZ_ISR,                   // 2.1 - ePWM1 Trip Zone Interrupt
    EPWM2_TZ_ISR,                   // 2.2 - ePWM2 Trip Zone Interrupt
    EPWM3_TZ_ISR,                   // 2.3 - ePWM3 Trip Zone Interrupt
    EPWM4_TZ_ISR,                   // 2.4 - ePWM4 Trip Zone Interrupt
    EPWM5_TZ_ISR,                   // 2.5 - ePWM5 Trip Zone Interrupt
    EPWM6_TZ_ISR,                   // 2.6 - ePWM6 Trip Zone Interrupt
    EPWM7_TZ_ISR,                   // 2.7 - ePWM7 Trip Zone Interrupt
    EPWM8_TZ_ISR,                   // 2.8 - ePWM8 Trip Zone Interrupt
    EPWM1_ISR,                      // 3.1 - ePWM1 Interrupt
    EPWM2_ISR,                      // 3.2 - ePWM2 Interrupt
    EPWM3_ISR,                      // 3.3 - ePWM3 Interrupt
    EPWM4_ISR,                      // 3.4 - ePWM4 Interrupt
    EPWM5_ISR,                      // 3.5 - ePWM5 Interrupt
    EPWM6_ISR,                      // 3.6 - ePWM6 Interrupt
    EPWM7_ISR,                      // 3.7 - ePWM7 Interrupt
    EPWM8_ISR,                      // 3.8 - ePWM8 Interrupt
    ECAP1_ISR,                      // 4.1 - eCAP1 Interrupt
    ECAP2_ISR,                      // 4.2 - eCAP2 Interrupt
    ECAP3_ISR,                      // 4.3 - eCAP3 Interrupt
    ECAP4_ISR,                      // 4.4 - eCAP4 Interrupt
    ECAP5_ISR,                      // 4.5 - eCAP5 Interrupt
    ECAP6_ISR,                      // 4.6 - eCAP6 Interrupt
    ECAP7_ISR,                      // 4.7 - eCAP7 Interrupt
    PIE_RESERVED_ISR,               // 4.8 - Reserved
    EQEP1_ISR,                      // 5.1 - eQEP1 Interrupt
    EQEP2_ISR,                      // 5.2 - eQEP2 Interrupt
    EQEP3_ISR,                      // 5.3 - eQEP3 Interrupt
    PIE_RESERVED_ISR,               // 5.4 - Reserved
    CLB1_ISR,                       // 5.5 - CLB1 (Reconfigurable Logic) Interrupt
    CLB2_ISR,                       // 5.6 - CLB2 (Reconfigurable Logic) Interrupt
    CLB3_ISR,                       // 5.7 - CLB3 (Reconfigurable Logic) Interrupt
    CLB4_ISR,                       // 5.8 - CLB4 (Reconfigurable Logic) Interrupt
    SPIA_RX_ISR,                    // 6.1 - SPIA Receive Interrupt
    SPIA_TX_ISR,                    // 6.2 - SPIA Transmit Interrupt
    SPIB_RX_ISR,                    // 6.3 - SPIB Receive Interrupt
    SPIB_TX_ISR,                    // 6.4 - SPIB Transmit Interrupt
    MCBSPA_RX_ISR,                  // 6.5 - McBSPA Receive Interrupt
    MCBSPA_TX_ISR,                  // 6.6 - McBSPA Transmit Interrupt
    MCBSPB_RX_ISR,                  // 6.7 - McBSPB Receive Interrupt
    MCBSPB_TX_ISR,                  // 6.8 - McBSPB Transmit Interrupt
    DMA_CH1_ISR,                    // 7.1 - DMA Channel 1 Interrupt
    DMA_CH2_ISR,                    // 7.2 - DMA Channel 2 Interrupt
    DMA_CH3_ISR,                    // 7.3 - DMA Channel 3 Interrupt
    DMA_CH4_ISR,                    // 7.4 - DMA Channel 4 Interrupt
    DMA_CH5_ISR,                    // 7.5 - DMA Channel 5 Interrupt
    DMA_CH6_ISR,                    // 7.6 - DMA Channel 6 Interrupt
    PIE_RESERVED_ISR,               // 7.7 - Reserved
    PIE_RESERVED_ISR,               // 7.8 - Reserved
    I2CA_ISR,                       // 8.1 - I2CA Interrupt 1
    I2CA_FIFO_ISR,                  // 8.2 - I2CA Interrupt 2
    I2CB_ISR,                       // 8.3 - I2CB Interrupt 1
    I2CB_FIFO_ISR,                  // 8.4 - I2CB Interrupt 2
    SCIC_RX_ISR,                    // 8.5 - SCIC Receive Interrupt
    SCIC_TX_ISR,                    // 8.6 - SCIC Transmit Interrupt
    SCID_RX_ISR,                    // 8.7 - SCID Receive Interrupt
    SCID_TX_ISR,                    // 8.8 - SCID Transmit Interrupt
    SCIA_RX_ISR,                    // 9.1 - SCIA Receive Interrupt
    SCIA_TX_ISR,                    // 9.2 - SCIA Transmit Interrupt
    SCIB_RX_ISR,                    // 9.3 - SCIB Receive Interrupt
    SCIB_TX_ISR,                    // 9.4 - SCIB Transmit Interrupt
    CANA0_ISR,                      // 9.5 - CANA Interrupt 0
    CANA1_ISR,                      // 9.6 - CANA Interrupt 1
    CANB0_ISR,                      // 9.7 - CANB Interrupt 0
    CANB1_ISR,                      // 9.8 - CANB Interrupt 1
    ADCA_EVT_ISR,                   // 10.1 - ADCA Event Interrupt
    ADCA2_ISR,                      // 10.2 - ADCA Interrupt 2
    ADCA3_ISR,                      // 10.3 - ADCA Interrupt 3
    ADCA4_ISR,                      // 10.4 - ADCA Interrupt 4
    ADCB_EVT_ISR,                   // 10.5 - ADCB Event Interrupt
    ADCB2_ISR,                      // 10.6 - ADCB Interrupt 2
    ADCB3_ISR,                      // 10.7 - ADCB Interrupt 3
    ADCB4_ISR,                      // 10.8 - ADCB Interrupt 4
    CLA1_1_ISR,                     // 11.1 - CLA1 Interrupt 1
    CLA1_2_ISR,                     // 11.2 - CLA1 Interrupt 2
    CLA1_3_ISR,                     // 11.3 - CLA1 Interrupt 3
    CLA1_4_ISR,                     // 11.4 - CLA1 Interrupt 4
    CLA1_5_ISR,                     // 11.5 - CLA1 Interrupt 5
    CLA1_6_ISR,                     // 11.6 - CLA1 Interrupt 6
    CLA1_7_ISR,                     // 11.7 - CLA1 Interrupt 7
    CLA1_8_ISR,                     // 11.8 - CLA1 Interrupt 8
    XINT3_ISR,                      // 12.1 - XINT3 Interrupt
    XINT4_ISR,                      // 12.2 - XINT4 Interrupt
    XINT5_ISR,                      // 12.3 - XINT5 Interrupt
    MPOST_ISR,                      // 12.4 - MPOST Interrupt
    FMC_ISR,                        // 12.5 - Flash Wrapper Operation Done Interrupt
    PIE_RESERVED_ISR,               // 12.6 - Reserved
    FPU_OFLOW_ISR,                  // 12.7 - FPU Overflow Interrupt
    FPU_UFLOW_ISR,                  // 12.8 - FPU Underflow Interrupt
    I2CA_HIGH_ISR,                  // 1.9 - I2CA Interrupt high priority
    SYS_ERR_ISR,                    // 1.10 - System error interrupt
    ECATSYNC0_ISR,                  // 1.11 - ETHERCAT SYNC0 interrupt
    ECAT_ISR,                       // 1.12 - ETHERCAT main interrupt
    CIPC0_ISR,                      // 1.13 - C28x CPU IPC interrupt 1
    CIPC1_ISR,                      // 1.14 - C28x CPU IPC interrupt 2
    CIPC2_ISR,                      // 1.15 - C28x CPU IPC interrupt 3
    CIPC3_ISR,                      // 1.16 - C28x CPU IPC interrupt 4
    EPWM9_TZ_ISR,                   // 2.9 -  ePWM9 Trip Zone Interrupt
    EPWM10_TZ_ISR,                  // 2.10 - ePWM10 Trip Zone Interrupt
    EPWM11_TZ_ISR,                  // 2.11 - ePWM11 Trip Zone Interrupt
    EPWM12_TZ_ISR,                  // 2.12 - ePWM12 Trip Zone Interrupt
    EPWM13_TZ_ISR,                  // 2.13 - ePWM13 Trip Zone Interrupt
    EPWM14_TZ_ISR,                  // 2.14 - ePWM14 Trip Zone Interrupt
    EPWM15_TZ_ISR,                  // 2.15 - ePWM15 Trip Zone Interrupt
    EPWM16_TZ_ISR,                  // 2.16 - ePWM16 Trip Zone Interrupt
    EPWM9_ISR,                      // 3.9 - ePWM9 Interrupt
    EPWM10_ISR,                     // 3.10 - ePWM10 Interrupt
    EPWM11_ISR,                     // 3.11 - ePWM11 Interrupt
    EPWM12_ISR,                     // 3.12 - ePWM12 Interrupt
    EPWM13_ISR,                     // 3.13 - ePWM13 Interrupt
    EPWM14_ISR,                     // 3.14 - ePWM14 Interrupt
    EPWM15_ISR,                     // 3.15 - ePWM15 Interrupt
    EPWM16_ISR,                     // 3.16 - ePWM16 Interrupt
    FSITXA1_ISR,                    // 4.9 - FSIA Transmit interrupt 1
    FSITXA2_ISR,                    // 4.10 - FSIA Transmit interrupt 2
    FSITXB1_ISR,                    // 4.11 - FSIB Transmit interrupt 1
    FSITXB2_ISR,                    // 4.12 - FSIB Transmit interrupt 2
    FSIRXA1_ISR,                    // 4.13 - FSIA Receive interrupt 1
    FSIRXA2_ISR,                    // 4.14 - FSIA Receive interrupt 2
    FSIRXB1_ISR,                    // 4.15 - FSIB Receive interrupt 1
    FSIRXB2_ISR,                    // 4.16 - FSIB Receive interrupt 2
    SDFM1_ISR,                      // 5.9 - Sigma Delta Filter Module1  Interrupt
    SDFM2_ISR,                      // 5.10 - Sigma Delta Filter Module2 Interrupt
    ECATRST_ISR,                    // 5.11 - ETHERCAT Resetout Interrupt
    ECATSYNC1_ISR,                  // 5.12 - ETHERCAT SYNC1 interrupt
    SDFM1DR1_ISR,                   // 5.13 - Sigma Delta Filter Module1  Filter 1 Interrupt
    SDFM1DR2_ISR,                   // 5.14 - Sigma Delta Filter Module1  Filter 2 Interrupt
    SDFM1DR3_ISR,                   // 5.15 - Sigma Delta Filter Module1  Filter 3 Interrupt
    SDFM1DR4_ISR,                   // 5.16 - Sigma Delta Filter Module1  Filter 4 Interrupt
    SPIC_RX_ISR,                    // 6.9 - SPIC Receive Interrupt
    SPIC_TX_ISR,                    // 6.10 - SPIC Transmit Interrupt
    SPID_RX_ISR,                    // 6.11 - SPID Receive Interrupt
    SPID_TX_ISR,                    // 6.12 - SPID Transmit Interrupt
    SDFM2DR1_ISR,                   // 6.13 - Sigma Delta Filter Module2  Filter 1 Interrupt
    SDFM2DR2_ISR,                   // 6.14 - Sigma Delta Filter Module2  Filter 2 Interrupt
    SDFM2DR3_ISR,                   // 6.15 - Sigma Delta Filter Module2  Filter 3 Interrupt
    SDFM2DR4_ISR,                   // 6.16 - Sigma Delta Filter Module2  Filter 4 Interrupt
    FSIRXC1_ISR,                    // 7.9 - FSIC Receive interrupt 1
    FSIRXC2_ISR,                    // 7.10 - FSIC Receive interrupt 2
    FSIRXD1_ISR,                    // 7.11 - FSID Receive interrupt 1
    FSIRXD2_ISR,                    // 7.12 - FSID Receive interrupt 2
    FSIRXE1_ISR,                    // 7.13 - FSIE Receive interrupt 1
    FSIRXE2_ISR,                    // 7.14 - FSIE Receive interrupt 2
    FSIRXF1_ISR,                    // 7.15 - FSIF Receive interrupt 1
    FSIRXF2_ISR,                    // 7.16 - FSIF Receive interrupt 2
    FSIRXG1_ISR,                    // 8.9 - FSIG Receive interrupt 1
    FSIRXG2_ISR,                    // 8.10 - FSIG Receive interrupt 2
    FSIRXH1_ISR,                    // 8.11 - FSIH Receive interrupt 1
    FSIRXH2_ISR,                    // 8.12 - FSIH Receive interrupt 2
    CLB5_ISR,                       // 8.13 - CLB5 Interrupt
    CLB6_ISR,                       // 8.14 - CLB6 Interrupt
    CLB7_ISR,                       // 8.15 - CLB7 Interrupt
    CLB8_ISR,                       // 8.16 - CLB8 Interrupt
    MCANA_0_ISR,                    // 9.9 - MCAN Sub-System Interrupt 0
    MCANA_1_ISR,                    // 9.10 - MCAN Sub-System Interrupt 1
    MCANA_ECC_ISR,                  // 9.11 - MCAN Sub-System ECC error Interrupt
    MCANA_WAKE_ISR,                 // 9.12 - MCAN Sub-System wakeup Interrupt
    PMBUSA_ISR,                     // 9.13 - PMBUSA Interrupt
    CM_STATUS_ISR,                  // 9.14 - CM Reset Status Interrupt
    USBA_ISR,                       // 9.15 - USBA Interrupt
    PIE_RESERVED_ISR,               // 9.16 - Reserved
    ADCC_EVT_ISR,                   // 10.9 - ADCC Event Interrupt
    ADCC2_ISR,                      // 10.10 - ADCC Interrupt 2
    ADCC3_ISR,                      // 10.11 - ADCC Interrupt 3
    ADCC4_ISR,                      // 10.12 - ADCC Interrupt 4
    ADCD_EVT_ISR,                   // 10.13 - ADCD Event Interrupt
    ADCD2_ISR,                      // 10.14 - ADCD Interrupt 2
    ADCD3_ISR,                      // 10.15 - ADCD Interrupt 3
    ADCD4_ISR,                      // 10.16 - ADCD Interrupt 4
    CMTOCPUXIPC0_ISR,               // 11.9 - CM to CPU IPC Interrupt 0
    CMTOCPUXIPC1_ISR,               // 11.10 - CM to CPU IPC Interrupt 1
    CMTOCPUXIPC2_ISR,               // 11.11 - CM to CPU IPC Interrupt 2
    CMTOCPUXIPC3_ISR,               // 11.12 - CM to CPU IPC Interrupt 3
    CMTOCPUXIPC4_ISR,               // 11.13 - CM to CPU IPC Interrupt 4
    CMTOCPUXIPC5_ISR,               // 11.14 - CM to CPU IPC Interrupt 5
    CMTOCPUXIPC6_ISR,               // 11.15 - CM to CPU IPC Interrupt 6
    CMTOCPUXIPC7_ISR,               // 11.16 - CM to CPU IPC Interrupt 7
    PIE_RESERVED_ISR,               // 12.9 - Reserved
    ECAP6_2_ISR,                    // 12.10 - eCAP6 Interrupt 2
    ECAP7_2_ISR,                    // 12.11 - eCAP7 Interrupt 2
    PIE_RESERVED_ISR,               // 12.12 - Reserved
    CPUCRC_ISR,                     // 12.13 - CPU BGCRC module interrupt
    CLA1CRC_ISR,                    // 12.14 - CLA1 BGCRC module interrupt
    CLA_OVERFLOW_ISR,               // 12.15 - CLA Overflow Interrupt
    CLA_UNDERFLOW_ISR,              // 12.16 - CLA Underflow Interrupt
};

//
// InitPieVectTable - This function initializes the PIE vector table to a
//                    known state and must be executed after boot time.
//
void InitPieVectTable(void)
{
    Uint16 i;
    Uint32 *Source = (void *) &PieVectTableInit;
    Uint32 *Dest = (void *) &PieVectTable;

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

    //
    // Enable the PIE Vector Table
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
}

//
// End of file
//
