//###########################################################################
//
// FILE:    F2802x0_DefaultIsr.h
//
// TITLE:   F2802x0 Devices Default Interrupt Service Routines Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2802x0_DEFAULT_ISR_H
#define F2802x0_DEFAULT_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes
//

//
// Default Interrupt Service Routine Declarations -  The following function 
// prototypes are for the default ISR routines used with the default PIE vector
// table. This default vector table is found in the F2802x0_PieVect.h
// file.
//

//
// For compatibility with header files V1.00 and earlier
//
#define TINT1_ISR INT13_ISR
#define TINT2_ISR INT14_ISR

//
// Non-Peripheral Interrupts
//
interrupt void INT13_ISR(void);     // INT13 or CPU-Timer 1
interrupt void INT14_ISR(void);     // INT14 or CPU-Timer 2
interrupt void DATALOG_ISR(void);   // Datalogging interrupt
interrupt void RTOSINT_ISR(void);   // RTOS interrupt
interrupt void EMUINT_ISR(void);    // Emulation interrupt
interrupt void NMI_ISR(void);       // Non-maskable interrupt
interrupt void ILLEGAL_ISR(void);   // Illegal operation TRAP
interrupt void USER1_ISR(void);     // User Defined trap 1
interrupt void USER2_ISR(void);     // User Defined trap 2
interrupt void USER3_ISR(void);     // User Defined trap 3
interrupt void USER4_ISR(void);     // User Defined trap 4
interrupt void USER5_ISR(void);     // User Defined trap 5
interrupt void USER6_ISR(void);     // User Defined trap 6
interrupt void USER7_ISR(void);     // User Defined trap 7
interrupt void USER8_ISR(void);     // User Defined trap 8
interrupt void USER9_ISR(void);     // User Defined trap 9
interrupt void USER10_ISR(void);    // User Defined trap 10
interrupt void USER11_ISR(void);    // User Defined trap 11
interrupt void USER12_ISR(void);    // User Defined trap 12

//
// Group 1 PIE Interrupt Service Routines
//
interrupt void  ADCINT1_ISR(void);   // ADC INT1 ISR - 1.1 OR 10.1
interrupt void  ADCINT2_ISR(void);   // ADC INT2 ISR - 1.2 OR 10.2
interrupt void  XINT1_ISR(void);     // External interrupt 1
interrupt void  XINT2_ISR(void);     // External interrupt 2
interrupt void  ADCINT9_ISR(void);   // ADC INT9 ISR
interrupt void  TINT0_ISR(void);     // Timer 0
interrupt void  WAKEINT_ISR(void);   // WD

//
// Group 2 PIE Interrupt Service Routines
//
interrupt void EPWM1_TZINT_ISR(void);    // EPWM-1
interrupt void EPWM2_TZINT_ISR(void);    // EPWM-2
interrupt void EPWM3_TZINT_ISR(void);    // EPWM-3
interrupt void EPWM4_TZINT_ISR(void);    // EPWM-4

//
// Group 3 PIE Interrupt Service Routines
//
interrupt void EPWM1_INT_ISR(void);    // EPWM-1
interrupt void EPWM2_INT_ISR(void);    // EPWM-2
interrupt void EPWM3_INT_ISR(void);    // EPWM-3
interrupt void EPWM4_INT_ISR(void);    // EPWM-4

//
// Group 4 PIE Interrupt Service Routines
//
interrupt void ECAP1_INT_ISR(void);    // ECAP-1

//
// Group 5 PIE Interrupt Service Routines
//

//
// Group 6 PIE Interrupt Service Routines
//
interrupt void SPIRXINTA_ISR(void);   // SPI-A
interrupt void SPITXINTA_ISR(void);   // SPI-A

//
// Group 7 PIE Interrupt Service Routines
//

//
// Group 8 PIE Interrupt Service Routines
//
interrupt void I2CINT1A_ISR(void);     // I2C-A
interrupt void I2CINT2A_ISR(void);     // I2C-A

//
// Group 9 PIE Interrupt Service Routines
//
interrupt void SCIRXINTA_ISR(void); // SCI-A
interrupt void SCITXINTA_ISR(void); // SCI-A

//
// Group 10 PIE Interrupt Service Routines
//

//
// ADC INT1 ISR - 1.1 or 10.1
//

//
// ADC INT2 ISR - 1.2 or 10.2
//
interrupt void ADCINT3_ISR(void);  // ADC INT3 ISR
interrupt void ADCINT4_ISR(void);  // ADC INT4 ISR
interrupt void ADCINT5_ISR(void);  // ADC INT5 ISR
interrupt void ADCINT6_ISR(void);  // ADC INT6 ISR
interrupt void ADCINT7_ISR(void);  // ADC INT7 ISR
interrupt void ADCINT8_ISR(void);  // ADC INT8 ISR

//
// Group 11 PIE Interrupt Service Routines
//

//
// Group 12 PIE Interrupt Service Routines
//
interrupt void XINT3_ISR (void); // External interrupt 3

//
// Catch-all for Reserved Locations For testing purposes
//
interrupt void PIE_RESERVED(void);       // Reserved for test
interrupt void rsvd_ISR(void);           // for test
interrupt void INT_NOTUSED_ISR(void);    // for unused interrupts

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif    // end of F2802x0_DEFAULT_ISR_H definition

//
// End of file
//

