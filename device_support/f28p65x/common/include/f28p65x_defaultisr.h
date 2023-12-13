//###########################################################################
//
// FILE:   f28p65x_defaultisr.h
//
// TITLE:  f28p65x Device Default Interrupt Service Routines Definitions
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef F28P65X_DEFAULTISR_H
#define F28P65X_DEFAULTISR_H
#ifdef __cplusplus
extern "C" {
#endif

//
// Default Interrupt Service Routine Declarations:
// The following function prototypes are for the
// default ISR routines used with the default PIE vector table.
// This default vector table is found in the f28p65x_pievect.h
// file.
//
interrupt void TIMER1_ISR(void);
interrupt void TIMER2_ISR(void);
interrupt void DATALOG_ISR(void);
interrupt void RTOS_ISR(void);
interrupt void EMU_ISR(void);
interrupt void NMI_ISR(void);
interrupt void ILLEGAL_ISR(void);
interrupt void USER1_ISR(void);
interrupt void USER2_ISR(void);
interrupt void USER3_ISR(void);
interrupt void USER4_ISR(void);
interrupt void USER5_ISR(void);
interrupt void USER6_ISR(void);
interrupt void USER7_ISR(void);
interrupt void USER8_ISR(void);
interrupt void USER9_ISR(void);
interrupt void USER10_ISR(void);
interrupt void USER11_ISR(void);
interrupt void USER12_ISR(void);
interrupt void ADCA1_ISR(void);
interrupt void ADCB1_ISR(void);
interrupt void ADCC1_ISR(void);
interrupt void XINT1_ISR(void);
interrupt void XINT2_ISR(void);
interrupt void TIMER0_ISR(void);
interrupt void WAKE_ISR(void);
interrupt void EPWM1_TZ_ISR(void);
interrupt void EPWM2_TZ_ISR(void);
interrupt void EPWM3_TZ_ISR(void);
interrupt void EPWM4_TZ_ISR(void);
interrupt void EPWM5_TZ_ISR(void);
interrupt void EPWM6_TZ_ISR(void);
interrupt void EPWM7_TZ_ISR(void);
interrupt void EPWM8_TZ_ISR(void);
interrupt void EPWM1_ISR(void);
interrupt void EPWM2_ISR(void);
interrupt void EPWM3_ISR(void);
interrupt void EPWM4_ISR(void);
interrupt void EPWM5_ISR(void);
interrupt void EPWM6_ISR(void);
interrupt void EPWM7_ISR(void);
interrupt void EPWM8_ISR(void);
interrupt void ECAP1_ISR(void);
interrupt void ECAP2_ISR(void);
interrupt void ECAP3_ISR(void);
interrupt void ECAP4_ISR(void);
interrupt void ECAP5_ISR(void);
interrupt void ECAP6_ISR(void);
interrupt void ECAP7_ISR(void);
interrupt void EQEP1_ISR(void);
interrupt void EQEP2_ISR(void);
interrupt void EQEP3_ISR(void);
interrupt void EQEP4_ISR(void);
interrupt void CLB1_ISR(void);
interrupt void CLB2_ISR(void);
interrupt void CLB3_ISR(void);
interrupt void CLB4_ISR(void);
interrupt void SPIA_RX_ISR(void);
interrupt void SPIA_TX_ISR(void);
interrupt void SPIB_RX_ISR(void);
interrupt void SPIB_TX_ISR(void);
interrupt void LINA_0_ISR(void);
interrupt void LINA_1_ISR(void);
interrupt void LINB_0_ISR(void);
interrupt void LINB_1_ISR(void);
interrupt void DMA_CH1_ISR(void);
interrupt void DMA_CH2_ISR(void);
interrupt void DMA_CH3_ISR(void);
interrupt void DMA_CH4_ISR(void);
interrupt void DMA_CH5_ISR(void);
interrupt void DMA_CH6_ISR(void);
interrupt void EQEP5_ISR(void);
interrupt void EQEP6_ISR(void);
interrupt void I2CA_ISR(void);
interrupt void I2CA_FIFO_ISR(void);
interrupt void I2CB_ISR(void);
interrupt void I2CB_FIFO_ISR(void);
interrupt void UARTA_ISR(void);
interrupt void UARTB_ISR(void);
interrupt void EPWM17_TZ_ISR(void);
interrupt void EPWM18_TZ_ISR(void);
interrupt void SCIA_RX_ISR(void);
interrupt void SCIA_TX_ISR(void);
interrupt void SCIB_RX_ISR(void);
interrupt void SCIB_TX_ISR(void);
interrupt void CANA0_ISR(void);
interrupt void CANA1_ISR(void);
interrupt void EPWM17_ISR(void);
interrupt void EPWM18_ISR(void);
interrupt void ADCA_EVT_ISR(void);
interrupt void ADCA2_ISR(void);
interrupt void ADCA3_ISR(void);
interrupt void ADCA4_ISR(void);
interrupt void ADCB_EVT_ISR(void);
interrupt void ADCB2_ISR(void);
interrupt void ADCB3_ISR(void);
interrupt void ADCB4_ISR(void);
interrupt void CLA1_1_ISR(void);
interrupt void CLA1_2_ISR(void);
interrupt void CLA1_3_ISR(void);
interrupt void CLA1_4_ISR(void);
interrupt void CLA1_5_ISR(void);
interrupt void CLA1_6_ISR(void);
interrupt void CLA1_7_ISR(void);
interrupt void CLA1_8_ISR(void);
interrupt void XINT3_ISR(void);
interrupt void XINT4_ISR(void);
interrupt void XINT5_ISR(void);
interrupt void MPOST_ISR(void);
interrupt void FLSS_ISR(void);
interrupt void FPU_OVERFLOW_ISR(void);
interrupt void FPU_UNDERFLOW_ISR(void);
interrupt void I2CA_HIGH_ISR(void);
interrupt void SYS_ERR_ISR(void);
interrupt void ECATSYNC0_ISR(void);
interrupt void ECAT_ISR(void);
interrupt void CIPC0_ISR(void);
interrupt void CIPC1_ISR(void);
interrupt void CIPC2_ISR(void);
interrupt void CIPC3_ISR(void);
interrupt void EPWM9_TZ_ISR(void);
interrupt void EPWM10_TZ_ISR(void);
interrupt void EPWM11_TZ_ISR(void);
interrupt void EPWM12_TZ_ISR(void);
interrupt void EPWM13_TZ_ISR(void);
interrupt void EPWM14_TZ_ISR(void);
interrupt void EPWM15_TZ_ISR(void);
interrupt void EPWM16_TZ_ISR(void);
interrupt void EPWM9_ISR(void);
interrupt void EPWM10_ISR(void);
interrupt void EPWM11_ISR(void);
interrupt void EPWM12_ISR(void);
interrupt void EPWM13_ISR(void);
interrupt void EPWM14_ISR(void);
interrupt void EPWM15_ISR(void);
interrupt void EPWM16_ISR(void);
interrupt void FSITXA1_ISR(void);
interrupt void FSITXA2_ISR(void);
interrupt void FSITXB1_ISR(void);
interrupt void FSITXB2_ISR(void);
interrupt void FSIRXA1_ISR(void);
interrupt void FSIRXA2_ISR(void);
interrupt void FSIRXB1_ISR(void);
interrupt void FSIRXB2_ISR(void);
interrupt void SDFM1_ISR(void);
interrupt void SDFM2_ISR(void);
interrupt void ECATRST_ISR(void);
interrupt void ECATSYNC1_ISR(void);
interrupt void SDFM1DR1_ISR(void);
interrupt void SDFM1DR2_ISR(void);
interrupt void SDFM1DR3_ISR(void);
interrupt void SDFM1DR4_ISR(void);
interrupt void SPIC_RX_ISR(void);
interrupt void SPIC_TX_ISR(void);
interrupt void SPID_RX_ISR(void);
interrupt void SPID_TX_ISR(void);
interrupt void SDFM2DR1_ISR(void);
interrupt void SDFM2DR2_ISR(void);
interrupt void SDFM2DR3_ISR(void);
interrupt void SDFM2DR4_ISR(void);
interrupt void FSIRXC1_ISR(void);
interrupt void FSIRXC2_ISR(void);
interrupt void FSIRXD1_ISR(void);
interrupt void FSIRXD2_ISR(void);
interrupt void SDFM3DR1_ISR(void);
interrupt void SDFM3DR2_ISR(void);
interrupt void SDFM3DR3_ISR(void);
interrupt void SDFM3DR4_ISR(void);
interrupt void SDFM3_ISR(void);
interrupt void SDFM4_ISR(void);
interrupt void CLB5_ISR(void);
interrupt void CLB6_ISR(void);
interrupt void MCANA_0_ISR(void);
interrupt void MCANA_1_ISR(void);
interrupt void MCANA_ECC_ISR(void);
interrupt void MCANA_WAKE_ISR(void);
interrupt void PMBUSA_ISR(void);
interrupt void AES_SINTREQUEST_ISR(void);
interrupt void USBA_ISR(void);
interrupt void ADCC_EVT_ISR(void);
interrupt void ADCC2_ISR(void);
interrupt void ADCC3_ISR(void);
interrupt void ADCC4_ISR(void);
interrupt void ADCCHECKINT_ISR(void);
interrupt void MCANB_0_ISR(void);
interrupt void MCANB_1_ISR(void);
interrupt void MCANB_ECC_ISR(void);
interrupt void MCANB_WAKE_ISR(void);
interrupt void SDFM4DR1_ISR(void);
interrupt void SDFM4DR2_ISR(void);
interrupt void SDFM4DR3_ISR(void);
interrupt void SDFM4DR4_ISR(void);
interrupt void ECAP6_2_ISR(void);
interrupt void ECAP7_2_ISR(void);
interrupt void CPUCRC_ISR(void);
interrupt void CLA1CRC_ISR(void);
interrupt void CLA_OVERFLOW_ISR(void);
interrupt void CLA_UNDERFLOW_ISR(void);
//
// Catch-all for PIE Reserved Locations for testing purposes:
//
interrupt void PIE_RESERVED_ISR(void);              // Reserved ISR
interrupt void EMPTY_ISR(void);                     // Only does a return
interrupt void NOTUSED_ISR(void);
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif   // end of f28p65x_PIEVECT_H definition

//
// End of file
//

