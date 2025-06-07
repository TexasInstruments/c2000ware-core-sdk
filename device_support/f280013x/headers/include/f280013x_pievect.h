//###########################################################################
//
// FILE:   f280013x_pievect.h
//
// TITLE:   Definitions for the PIE Vector Table.
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

#ifndef F280013X_PIEVECT_H
#define F280013X_PIEVECT_H
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
    PINT RTOS_INT;                  // RTOS Interrupt from ERAD
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
    PINT ADCC1_INT;                 // 1.2 - ADCC Interrupt 1
    PINT PIE14_RESERVED_INT;        // 1.3 - Reserved
    PINT XINT1_INT;                 // 1.4 - XINT1 Interrupt
    PINT XINT2_INT;                 // 1.5 - XINT2 Interrupt
    PINT SYS_ERR_INT;               // 1.6 - SYS_ERR Interrupt
    PINT TIMER0_INT;                // 1.7 - Timer 0 Interrupt
    PINT WAKE_INT;                  // 1.8 - Standby and Halt Wakeup Interrupt
    PINT EPWM1_TZ_INT;              // 2.1 - ePWM1 Trip Zone Interrupt
    PINT EPWM2_TZ_INT;              // 2.2 - ePWM2 Trip Zone Interrupt
    PINT EPWM3_TZ_INT;              // 2.3 - ePWM3 Trip Zone Interrupt
    PINT EPWM4_TZ_INT;              // 2.4 - ePWM4 Trip Zone Interrupt
    PINT EPWM5_TZ_INT;              // 2.5 - ePWM5 Trip Zone Interrupt
    PINT EPWM6_TZ_INT;              // 2.6 - ePWM6 Trip Zone Interrupt
    PINT EPWM7_TZ_INT;              // 2.7 - ePWM7 Trip Zone Interrupt
    PINT PIE15_RESERVED_INT;        // 2.8 - Reserved
    PINT EPWM1_INT;                 // 3.1 - ePWM1 Interrupt
    PINT EPWM2_INT;                 // 3.2 - ePWM2 Interrupt
    PINT EPWM3_INT;                 // 3.3 - ePWM3 Interrupt
    PINT EPWM4_INT;                 // 3.4 - ePWM4 Interrupt
    PINT EPWM5_INT;                 // 3.5 - ePWM5 Interrupt
    PINT EPWM6_INT;                 // 3.6 - ePWM6 Interrupt
    PINT EPWM7_INT;                 // 3.7 - ePWM7 Interrupt
    PINT PIE16_RESERVED_INT;        // 3.8 - Reserved
    PINT ECAP1_INT;                 // 4.1 - eCAP1 Interrupt
    PINT ECAP2_INT;                 // 4.2 - eCAP2 Interrupt
    PINT PIE17_RESERVED_INT;        // 4.3 - Reserved
    PINT PIE18_RESERVED_INT;        // 4.4 - Reserved
    PINT PIE19_RESERVED_INT;        // 4.5 - Reserved
    PINT PIE20_RESERVED_INT;        // 4.6 - Reserved
    PINT PIE21_RESERVED_INT;        // 4.7 - Reserved
    PINT PIE22_RESERVED_INT;        // 4.8 - Reserved
    PINT EQEP1_INT;                 // 5.1 - eQEP1 Interrupt
    PINT PIE23_RESERVED_INT;        // 5.2 - Reserved
    PINT PIE24_RESERVED_INT;        // 5.3 - Reserved
    PINT PIE25_RESERVED_INT;        // 5.4 - Reserved
    PINT PIE26_RESERVED_INT;        // 5.5 - Reserved
    PINT PIE27_RESERVED_INT;        // 5.6 - Reserved
    PINT PIE28_RESERVED_INT;        // 5.7 - Reserved
    PINT PIE29_RESERVED_INT;        // 5.8 - Reserved
    PINT SPIA_RX_INT;               // 6.1 - SPIA Receive Interrupt
    PINT SPIA_TX_INT;               // 6.2 - SPIA Transmit Interrupt
    PINT PIE30_RESERVED_INT;        // 6.3 - Reserved
    PINT PIE31_RESERVED_INT;        // 6.4 - Reserved
    PINT PIE32_RESERVED_INT;        // 6.5 - Reserved
    PINT PIE33_RESERVED_INT;        // 6.6 - Reserved
    PINT DCC0_INT;                  // 6.7 - DCC0 Interrupt
    PINT PIE34_RESERVED_INT;        // 6.8 - Reserved
    PINT PIE35_RESERVED_INT;        // 7.1 - Reserved
    PINT PIE36_RESERVED_INT;        // 7.2 - Reserved
    PINT PIE37_RESERVED_INT;        // 7.3 - Reserved
    PINT PIE38_RESERVED_INT;        // 7.4 - Reserved
    PINT PIE39_RESERVED_INT;        // 7.5 - Reserved
    PINT PIE40_RESERVED_INT;        // 7.6 - Reserved
    PINT PIE41_RESERVED_INT;        // 7.7 - Reserved
    PINT PIE42_RESERVED_INT;        // 7.8 - Reserved
    PINT I2CA_INT;                  // 8.1 - I2CA Interrupt 1
    PINT I2CA_FIFO_INT;             // 8.2 - I2CA Interrupt 2
    PINT I2CB_INT;                  // 8.3 - I2CB Interrupt 1
    PINT I2CB_FIFO_INT;             // 8.4 - I2CB Interrupt 2
    PINT SCIC_RX_INT;               // 8.5 - SCIC Receive Interrupt
    PINT SCIC_TX_INT;               // 8.6 - SCIC Transmit Interrupt
    PINT PIE43_RESERVED_INT;        // 8.7 - Reserved
    PINT PIE44_RESERVED_INT;        // 8.8 - Reserved
    PINT SCIA_RX_INT;               // 9.1 - SCIA Receive Interrupt
    PINT SCIA_TX_INT;               // 9.2 - SCIA Transmit Interrupt
    PINT SCIB_RX_INT;               // 9.3 - SCIB Receive Interrupt
    PINT SCIB_TX_INT;               // 9.4 - SCIB Transmit Interrupt
    PINT CANA0_INT;                 // 9.5 - CANA Interrupt 0
    PINT CANA1_INT;                 // 9.6 - CANA Interrupt 1
    PINT PIE45_RESERVED_INT;        // 9.7 - Reserved
    PINT PIE46_RESERVED_INT;        // 9.8 - Reserved
    PINT ADCA_EVT_INT;              // 10.1 - ADCA Event Interrupt
    PINT ADCA2_INT;                 // 10.2 - ADCA Interrupt 2
    PINT ADCA3_INT;                 // 10.3 - ADCA Interrupt 3
    PINT ADCA4_INT;                 // 10.4 - ADCA Interrupt 4
    PINT ADCC_EVT_INT;              // 10.5 - ADCC Event Interrupt
    PINT ADCC2_INT;                 // 10.6 - ADCC Interrupt 2
    PINT ADCC3_INT;                 // 10.7 - ADCC Interrupt 3
    PINT ADCC4_INT;                 // 10.8 - ADCC Interrupt 4
    PINT PIE47_RESERVED_INT;        // 11.1 - Reserved
    PINT PIE48_RESERVED_INT;        // 11.2 - Reserved
    PINT PIE49_RESERVED_INT;        // 11.3 - Reserved
    PINT PIE50_RESERVED_INT;        // 11.4 - Reserved
    PINT PIE51_RESERVED_INT;        // 11.5 - Reserved
    PINT PIE52_RESERVED_INT;        // 11.6 - Reserved
    PINT PIE53_RESERVED_INT;        // 11.7 - Reserved
    PINT PIE54_RESERVED_INT;        // 11.8 - Reserved
    PINT XINT3_INT;                 // 12.1 - XINT3 Interrupt
    PINT XINT4_INT;                 // 12.2 - XINT4 Interrupt
    PINT XINT5_INT;                 // 12.3 - XINT5 Interrupt
    PINT PIE55_RESERVED_INT;        // 12.4 - Reserved
    PINT FLSS_INT;                  // 12.5 - Interrupt from flash sub-system
    PINT PIE56_RESERVED_INT;        // 12.6 - Reserved
    PINT PIE57_RESERVED_INT;        // 12.7 - Reserved
    PINT PIE58_RESERVED_INT;        // 12.8 - Reserved
};

//---------------------------------------------------------------------------
// PieVect External References & Function Declarations:
//

extern volatile struct PIE_VECT_TABLE PieVectTable;

#ifdef __cplusplus
}
#endif                                               /* extern "C" */


#endif                                               // end of F280013X_PIEVECT_H definition
//===========================================================================
// End of file.
//===========================================================================
