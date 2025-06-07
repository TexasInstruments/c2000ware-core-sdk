//###########################################################################
//
// FILE:   f280013x_defaultisr.h
//
// TITLE:  f280013x Device Default Interrupt Service Routines Definitions
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

#ifndef F280013X_DEFAULTISR_H
#define F280013X_DEFAULTISR_H
#ifdef __cplusplus
extern "C" {
#endif

//
// Default Interrupt Service Routine Declarations:
// The following function prototypes are for the
// default ISR routines used with the default PIE vector table.
// This default vector table is found in the f280013x_pievect.h
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
interrupt void ADCC1_ISR(void);
interrupt void XINT1_ISR(void);
interrupt void XINT2_ISR(void);
interrupt void SYS_ERR_ISR(void);
interrupt void TIMER0_ISR(void);
interrupt void WAKE_ISR(void);
interrupt void EPWM1_TZ_ISR(void);
interrupt void EPWM2_TZ_ISR(void);
interrupt void EPWM3_TZ_ISR(void);
interrupt void EPWM4_TZ_ISR(void);
interrupt void EPWM5_TZ_ISR(void);
interrupt void EPWM6_TZ_ISR(void);
interrupt void EPWM7_TZ_ISR(void);
interrupt void EPWM1_ISR(void);
interrupt void EPWM2_ISR(void);
interrupt void EPWM3_ISR(void);
interrupt void EPWM4_ISR(void);
interrupt void EPWM5_ISR(void);
interrupt void EPWM6_ISR(void);
interrupt void EPWM7_ISR(void);
interrupt void ECAP1_ISR(void);
interrupt void ECAP2_ISR(void);
interrupt void EQEP1_ISR(void);
interrupt void SPIA_RX_ISR(void);
interrupt void SPIA_TX_ISR(void);
interrupt void DCC0_ISR(void);
interrupt void I2CA_ISR(void);
interrupt void I2CA_FIFO_ISR(void);
interrupt void I2CB_ISR(void);
interrupt void I2CB_FIFO_ISR(void);
interrupt void SCIC_RX_ISR(void);
interrupt void SCIC_TX_ISR(void);
interrupt void SCIA_RX_ISR(void);
interrupt void SCIA_TX_ISR(void);
interrupt void SCIB_RX_ISR(void);
interrupt void SCIB_TX_ISR(void);
interrupt void CANA0_ISR(void);
interrupt void CANA1_ISR(void);
interrupt void ADCA_EVT_ISR(void);
interrupt void ADCA2_ISR(void);
interrupt void ADCA3_ISR(void);
interrupt void ADCA4_ISR(void);
interrupt void ADCC_EVT_ISR(void);
interrupt void ADCC2_ISR(void);
interrupt void ADCC3_ISR(void);
interrupt void ADCC4_ISR(void);
interrupt void XINT3_ISR(void);
interrupt void XINT4_ISR(void);
interrupt void XINT5_ISR(void);
interrupt void FLSS_ISR(void);
//
// Catch-all for PIE Reserved Locations for testing purposes:
//
interrupt void PIE_RESERVED_ISR(void);              // Reserved ISR
interrupt void EMPTY_ISR(void);                     // Only does a return
interrupt void NOTUSED_ISR(void);
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif   // end of f280013x_PIEVECT_H definition

//
// End of file
//

