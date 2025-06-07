//###########################################################################
//
// FILE:   f2838x_pievect.h
//
// TITLE:   Definitions for the PIE Vector Table.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
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

#ifndef F2838X_PIEVECT_H
#define F2838X_PIEVECT_H
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PIE Interrupt Vector Table Definition:
// Create a user type called PINT (pointer to interrupt):

typedef __interrupt void (*PINT)(void);

// Define Vector Table:
struct PIE_VECT_TABLE {
    PINT PIE1_RESERVED_INT;         // Reserved
    PINT PIE2_RESERVED_INT;         // Reserved
    PINT PIE3_RESERVED_INT;         // Reserved
    PINT PIE4_RESERVED_INT;         // Reserved
    PINT PIE5_RESERVED_INT;         // Reserved
    PINT PIE6_RESERVED_INT;         // Reserved
    PINT PIE7_RESERVED_INT;         // Reserved
    PINT PIE8_RESERVED_INT;         // Reserved
    PINT PIE9_RESERVED_INT;         // Reserved
    PINT PIE10_RESERVED_INT;        // Reserved
    PINT PIE11_RESERVED_INT;        // Reserved
    PINT PIE12_RESERVED_INT;        // Reserved
    PINT PIE13_RESERVED_INT;        // Reserved
    PINT TIMER1_INT;                // CPU Timer 1 Interrupt
    PINT TIMER2_INT;                // CPU Timer 2 Interrupt
    PINT DATALOG_INT;               // Datalogging Interrupt
    PINT RTOS_INT;                  // RTOS Interrupt
    PINT EMU_INT;                   // Emulation Interrupt
    PINT NMI_INT;                   // Non-Maskable Interrupt
    PINT ILLEGAL_INT;               // Illegal Operation Trap
    PINT USER1_INT;                 // User Defined Trap 1
    PINT USER2_INT;                 // User Defined Trap 2
    PINT USER3_INT;                 // User Defined Trap 3
    PINT USER4_INT;                 // User Defined Trap 4
    PINT USER5_INT;                 // User Defined Trap 5
    PINT USER6_INT;                 // User Defined Trap 6
    PINT USER7_INT;                 // User Defined Trap 7
    PINT USER8_INT;                 // User Defined Trap 8
    PINT USER9_INT;                 // User Defined Trap 9
    PINT USER10_INT;                // User Defined Trap 10
    PINT USER11_INT;                // User Defined Trap 11
    PINT USER12_INT;                // User Defined Trap 12
    PINT ADCA1_INT;                 // 1.1 - ADCA Interrupt 1
    PINT ADCB1_INT;                 // 1.2 - ADCB Interrupt 1
    PINT ADCC1_INT;                 // 1.3 - ADCC Interrupt 1
    PINT XINT1_INT;                 // 1.4 - XINT1 Interrupt
    PINT XINT2_INT;                 // 1.5 - XINT2 Interrupt
    PINT ADCD1_INT;                 // 1.6 - ADCD Interrupt 1
    PINT TIMER0_INT;                // 1.7 - Timer 0 Interrupt
    PINT WAKE_INT;                  // 1.8 - Standby and Halt Wakeup Interrupt
    PINT EPWM1_TZ_INT;              // 2.1 - ePWM1 Trip Zone Interrupt
    PINT EPWM2_TZ_INT;              // 2.2 - ePWM2 Trip Zone Interrupt
    PINT EPWM3_TZ_INT;              // 2.3 - ePWM3 Trip Zone Interrupt
    PINT EPWM4_TZ_INT;              // 2.4 - ePWM4 Trip Zone Interrupt
    PINT EPWM5_TZ_INT;              // 2.5 - ePWM5 Trip Zone Interrupt
    PINT EPWM6_TZ_INT;              // 2.6 - ePWM6 Trip Zone Interrupt
    PINT EPWM7_TZ_INT;              // 2.7 - ePWM7 Trip Zone Interrupt
    PINT EPWM8_TZ_INT;              // 2.8 - ePWM8 Trip Zone Interrupt
    PINT EPWM1_INT;                 // 3.1 - ePWM1 Interrupt
    PINT EPWM2_INT;                 // 3.2 - ePWM2 Interrupt
    PINT EPWM3_INT;                 // 3.3 - ePWM3 Interrupt
    PINT EPWM4_INT;                 // 3.4 - ePWM4 Interrupt
    PINT EPWM5_INT;                 // 3.5 - ePWM5 Interrupt
    PINT EPWM6_INT;                 // 3.6 - ePWM6 Interrupt
    PINT EPWM7_INT;                 // 3.7 - ePWM7 Interrupt
    PINT EPWM8_INT;                 // 3.8 - ePWM8 Interrupt
    PINT ECAP1_INT;                 // 4.1 - eCAP1 Interrupt
    PINT ECAP2_INT;                 // 4.2 - eCAP2 Interrupt
    PINT ECAP3_INT;                 // 4.3 - eCAP3 Interrupt
    PINT ECAP4_INT;                 // 4.4 - eCAP4 Interrupt
    PINT ECAP5_INT;                 // 4.5 - eCAP5 Interrupt
    PINT ECAP6_INT;                 // 4.6 - eCAP6 Interrupt
    PINT ECAP7_INT;                 // 4.7 - eCAP7 Interrupt
    PINT PIE14_RESERVED_INT;        // 4.8 - Reserved
    PINT EQEP1_INT;                 // 5.1 - eQEP1 Interrupt
    PINT EQEP2_INT;                 // 5.2 - eQEP2 Interrupt
    PINT EQEP3_INT;                 // 5.3 - eQEP3 Interrupt
    PINT PIE15_RESERVED_INT;        // 5.4 - Reserved
    PINT CLB1_INT;                  // 5.5 - CLB1 (Reconfigurable Logic) Interrupt
    PINT CLB2_INT;                  // 5.6 - CLB2 (Reconfigurable Logic) Interrupt
    PINT CLB3_INT;                  // 5.7 - CLB3 (Reconfigurable Logic) Interrupt
    PINT CLB4_INT;                  // 5.8 - CLB4 (Reconfigurable Logic) Interrupt
    PINT SPIA_RX_INT;               // 6.1 - SPIA Receive Interrupt
    PINT SPIA_TX_INT;               // 6.2 - SPIA Transmit Interrupt
    PINT SPIB_RX_INT;               // 6.3 - SPIB Receive Interrupt
    PINT SPIB_TX_INT;               // 6.4 - SPIB Transmit Interrupt
    PINT MCBSPA_RX_INT;             // 6.5 - McBSPA Receive Interrupt
    PINT MCBSPA_TX_INT;             // 6.6 - McBSPA Transmit Interrupt
    PINT MCBSPB_RX_INT;             // 6.7 - McBSPB Receive Interrupt
    PINT MCBSPB_TX_INT;             // 6.8 - McBSPB Transmit Interrupt
    PINT DMA_CH1_INT;               // 7.1 - DMA Channel 1 Interrupt
    PINT DMA_CH2_INT;               // 7.2 - DMA Channel 2 Interrupt
    PINT DMA_CH3_INT;               // 7.3 - DMA Channel 3 Interrupt
    PINT DMA_CH4_INT;               // 7.4 - DMA Channel 4 Interrupt
    PINT DMA_CH5_INT;               // 7.5 - DMA Channel 5 Interrupt
    PINT DMA_CH6_INT;               // 7.6 - DMA Channel 6 Interrupt
    PINT PIE16_RESERVED_INT;        // 7.7 - Reserved
    PINT PIE17_RESERVED_INT;        // 7.8 - Reserved
    PINT I2CA_INT;                  // 8.1 - I2CA Interrupt 1
    PINT I2CA_FIFO_INT;             // 8.2 - I2CA Interrupt 2
    PINT I2CB_INT;                  // 8.3 - I2CB Interrupt 1
    PINT I2CB_FIFO_INT;             // 8.4 - I2CB Interrupt 2
    PINT SCIC_RX_INT;               // 8.5 - SCIC Receive Interrupt
    PINT SCIC_TX_INT;               // 8.6 - SCIC Transmit Interrupt
    PINT SCID_RX_INT;               // 8.7 - SCID Receive Interrupt
    PINT SCID_TX_INT;               // 8.8 - SCID Transmit Interrupt
    PINT SCIA_RX_INT;               // 9.1 - SCIA Receive Interrupt
    PINT SCIA_TX_INT;               // 9.2 - SCIA Transmit Interrupt
    PINT SCIB_RX_INT;               // 9.3 - SCIB Receive Interrupt
    PINT SCIB_TX_INT;               // 9.4 - SCIB Transmit Interrupt
    PINT CANA0_INT;                 // 9.5 - CANA Interrupt 0
    PINT CANA1_INT;                 // 9.6 - CANA Interrupt 1
    PINT CANB0_INT;                 // 9.7 - CANB Interrupt 0
    PINT CANB1_INT;                 // 9.8 - CANB Interrupt 1
    PINT ADCA_EVT_INT;              // 10.1 - ADCA Event Interrupt
    PINT ADCA2_INT;                 // 10.2 - ADCA Interrupt 2
    PINT ADCA3_INT;                 // 10.3 - ADCA Interrupt 3
    PINT ADCA4_INT;                 // 10.4 - ADCA Interrupt 4
    PINT ADCB_EVT_INT;              // 10.5 - ADCB Event Interrupt
    PINT ADCB2_INT;                 // 10.6 - ADCB Interrupt 2
    PINT ADCB3_INT;                 // 10.7 - ADCB Interrupt 3
    PINT ADCB4_INT;                 // 10.8 - ADCB Interrupt 4
    PINT CLA1_1_INT;                // 11.1 - CLA1 Interrupt 1
    PINT CLA1_2_INT;                // 11.2 - CLA1 Interrupt 2
    PINT CLA1_3_INT;                // 11.3 - CLA1 Interrupt 3
    PINT CLA1_4_INT;                // 11.4 - CLA1 Interrupt 4
    PINT CLA1_5_INT;                // 11.5 - CLA1 Interrupt 5
    PINT CLA1_6_INT;                // 11.6 - CLA1 Interrupt 6
    PINT CLA1_7_INT;                // 11.7 - CLA1 Interrupt 7
    PINT CLA1_8_INT;                // 11.8 - CLA1 Interrupt 8
    PINT XINT3_INT;                 // 12.1 - XINT3 Interrupt
    PINT XINT4_INT;                 // 12.2 - XINT4 Interrupt
    PINT XINT5_INT;                 // 12.3 - XINT5 Interrupt
    PINT MPOST_INT;                 // 12.4 - MPOST Interrupt
    PINT FMC_INT;                   // 12.5 - Flash Wrapper Operation Done Interrupt
    PINT PIE18_RESERVED_INT;        // 12.6 - Reserved
    PINT FPU_OFLOW_INT;             // 12.7 - FPU Overflow Interrupt
    PINT FPU_UFLOW_INT;             // 12.8 - FPU Underflow Interrupt
    PINT I2CA_HIGH_INT;             // 1.9 - I2CA Interrupt high priority
    PINT SYS_ERR_INT;               // 1.10 - System error interrupt
    PINT ECATSYNC0_INT;             // 1.11 - ETHERCAT SYNC0 interrupt
    PINT ECAT_INT;                  // 1.12 - ETHERCAT main interrupt
    PINT CIPC0_INT;                 // 1.13 - C28x CPU IPC interrupt 1
    PINT CIPC1_INT;                 // 1.14 - C28x CPU IPC interrupt 2
    PINT CIPC2_INT;                 // 1.15 - C28x CPU IPC interrupt 3
    PINT CIPC3_INT;                 // 1.16 - C28x CPU IPC interrupt 4
    PINT EPWM9_TZ_INT;              // 2.9 -  ePWM9 Trip Zone Interrupt
    PINT EPWM10_TZ_INT;             // 2.10 - ePWM10 Trip Zone Interrupt
    PINT EPWM11_TZ_INT;             // 2.11 - ePWM11 Trip Zone Interrupt
    PINT EPWM12_TZ_INT;             // 2.12 - ePWM12 Trip Zone Interrupt
    PINT EPWM13_TZ_INT;             // 2.13 - ePWM13 Trip Zone Interrupt
    PINT EPWM14_TZ_INT;             // 2.14 - ePWM14 Trip Zone Interrupt
    PINT EPWM15_TZ_INT;             // 2.15 - ePWM15 Trip Zone Interrupt
    PINT EPWM16_TZ_INT;             // 2.16 - ePWM16 Trip Zone Interrupt
    PINT EPWM9_INT;                 // 3.9 - ePWM9 Interrupt
    PINT EPWM10_INT;                // 3.10 - ePWM10 Interrupt
    PINT EPWM11_INT;                // 3.11 - ePWM11 Interrupt
    PINT EPWM12_INT;                // 3.12 - ePWM12 Interrupt
    PINT EPWM13_INT;                // 3.13 - ePWM13 Interrupt
    PINT EPWM14_INT;                // 3.14 - ePWM14 Interrupt
    PINT EPWM15_INT;                // 3.15 - ePWM15 Interrupt
    PINT EPWM16_INT;                // 3.16 - ePWM16 Interrupt
    PINT FSITXA1_INT;               // 4.9 - FSIA Transmit interrupt 1
    PINT FSITXA2_INT;               // 4.10 - FSIA Transmit interrupt 2
    PINT FSITXB1_INT;               // 4.11 - FSIB Transmit interrupt 1
    PINT FSITXB2_INT;               // 4.12 - FSIB Transmit interrupt 2
    PINT FSIRXA1_INT;               // 4.13 - FSIA Receive interrupt 1
    PINT FSIRXA2_INT;               // 4.14 - FSIA Receive interrupt 2
    PINT FSIRXB1_INT;               // 4.15 - FSIB Receive interrupt 1
    PINT FSIRXB2_INT;               // 4.16 - FSIB Receive interrupt 2
    PINT SDFM1_INT;                 // 5.9 - Sigma Delta Filter Module1  Interrupt
    PINT SDFM2_INT;                 // 5.10 - Sigma Delta Filter Module2 Interrupt
    PINT ECATRST_INT;               // 5.11 - ETHERCAT Resetout Interrupt
    PINT ECATSYNC1_INT;             // 5.12 - ETHERCAT SYNC1 interrupt
    PINT SDFM1DR1_INT;              // 5.13 - Sigma Delta Filter Module1  Filter 1 Interrupt
    PINT SDFM1DR2_INT;              // 5.14 - Sigma Delta Filter Module1  Filter 2 Interrupt
    PINT SDFM1DR3_INT;              // 5.15 - Sigma Delta Filter Module1  Filter 3 Interrupt
    PINT SDFM1DR4_INT;              // 5.16 - Sigma Delta Filter Module1  Filter 4 Interrupt
    PINT SPIC_RX_INT;               // 6.9 - SPIC Receive Interrupt
    PINT SPIC_TX_INT;               // 6.10 - SPIC Transmit Interrupt
    PINT SPID_RX_INT;               // 6.11 - SPID Receive Interrupt
    PINT SPID_TX_INT;               // 6.12 - SPID Transmit Interrupt
    PINT SDFM2DR1_INT;              // 6.13 - Sigma Delta Filter Module2  Filter 1 Interrupt
    PINT SDFM2DR2_INT;              // 6.14 - Sigma Delta Filter Module2  Filter 2 Interrupt
    PINT SDFM2DR3_INT;              // 6.15 - Sigma Delta Filter Module2  Filter 3 Interrupt
    PINT SDFM2DR4_INT;              // 6.16 - Sigma Delta Filter Module2  Filter 4 Interrupt
    PINT FSIRXC1_INT;               // 7.9 - FSIC Receive interrupt 1
    PINT FSIRXC2_INT;               // 7.10 - FSIC Receive interrupt 2
    PINT FSIRXD1_INT;               // 7.11 - FSID Receive interrupt 1
    PINT FSIRXD2_INT;               // 7.12 - FSID Receive interrupt 2
    PINT FSIRXE1_INT;               // 7.13 - FSIE Receive interrupt 1
    PINT FSIRXE2_INT;               // 7.14 - FSIE Receive interrupt 2
    PINT FSIRXF1_INT;               // 7.15 - FSIF Receive interrupt 1
    PINT FSIRXF2_INT;               // 7.16 - FSIF Receive interrupt 2
    PINT FSIRXG1_INT;               // 8.9 - FSIG Receive interrupt 1
    PINT FSIRXG2_INT;               // 8.10 - FSIG Receive interrupt 2
    PINT FSIRXH1_INT;               // 8.11 - FSIH Receive interrupt 1
    PINT FSIRXH2_INT;               // 8.12 - FSIH Receive interrupt 2
    PINT CLB5_INT;                  // 8.13 - CLB5 Interrupt
    PINT CLB6_INT;                  // 8.14 - CLB6 Interrupt
    PINT CLB7_INT;                  // 8.15 - CLB7 Interrupt
    PINT CLB8_INT;                  // 8.16 - CLB8 Interrupt
    PINT MCANA_0_INT;               // 9.9 - MCAN Sub-System Interrupt 0
    PINT MCANA_1_INT;               // 9.10 - MCAN Sub-System Interrupt 1
    PINT MCANA_ECC_INT;             // 9.11 - MCAN Sub-System ECC error Interrupt
    PINT MCANA_WAKE_INT;            // 9.12 - MCAN Sub-System wakeup Interrupt
    PINT PMBUSA_INT;                // 9.13 - PMBUSA Interrupt
    PINT CM_STATUS_INT;             // 9.14 - CM Reset Status Interrupt
    PINT USBA_INT;                  // 9.15 - USBA Interrupt
    PINT PIE19_RESERVED_INT;        // 9.16 - Reserved
    PINT ADCC_EVT_INT;              // 10.9 - ADCC Event Interrupt
    PINT ADCC2_INT;                 // 10.10 - ADCC Interrupt 2
    PINT ADCC3_INT;                 // 10.11 - ADCC Interrupt 3
    PINT ADCC4_INT;                 // 10.12 - ADCC Interrupt 4
    PINT ADCD_EVT_INT;              // 10.13 - ADCD Event Interrupt
    PINT ADCD2_INT;                 // 10.14 - ADCD Interrupt 2
    PINT ADCD3_INT;                 // 10.15 - ADCD Interrupt 3
    PINT ADCD4_INT;                 // 10.16 - ADCD Interrupt 4
    PINT CMTOCPUXIPC0_INT;          // 11.9 - CM to CPU IPC Interrupt 0
    PINT CMTOCPUXIPC1_INT;          // 11.10 - CM to CPU IPC Interrupt 1
    PINT CMTOCPUXIPC2_INT;          // 11.11 - CM to CPU IPC Interrupt 2
    PINT CMTOCPUXIPC3_INT;          // 11.12 - CM to CPU IPC Interrupt 3
    PINT CMTOCPUXIPC4_INT;          // 11.13 - CM to CPU IPC Interrupt 4
    PINT CMTOCPUXIPC5_INT;          // 11.14 - CM to CPU IPC Interrupt 5
    PINT CMTOCPUXIPC6_INT;          // 11.15 - CM to CPU IPC Interrupt 6
    PINT CMTOCPUXIPC7_INT;          // 11.16 - CM to CPU IPC Interrupt 7
    PINT PIE20_RESERVED_INT;        // 12.9 - Reserved
    PINT ECAP6_2_INT;               // 12.10 - eCAP6 Interrupt 2
    PINT ECAP7_2_INT;               // 12.11 - eCAP7 Interrupt 2
    PINT PIE21_RESERVED_INT;        // 12.12 - Reserved
    PINT CPUCRC_INT;                // 12.13 - CPU BGCRC module interrupt
    PINT CLA1CRC_INT;               // 12.14 - CLA1 BGCRC module interrupt
    PINT CLA_OVERFLOW_INT;          // 12.15 - CLA Overflow Interrupt
    PINT CLA_UNDERFLOW_INT;         // 12.16 - CLA Underflow Interrupt
};

//---------------------------------------------------------------------------
// PieVect External References & Function Declarations:
//

extern volatile struct PIE_VECT_TABLE PieVectTable;

#ifdef __cplusplus
}
#endif                                               /* extern "C" */


#endif                                               // end of F2838X_PIEVECT_H definition
//===========================================================================
// End of file.
//===========================================================================
