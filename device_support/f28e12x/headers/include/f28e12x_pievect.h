//###########################################################################
//
// FILE:   f28e12x_pievect.h
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

#ifndef F28E12X_PIEVECT_H
#define F28E12X_PIEVECT_H
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
    PINT PIE14_RESERVED_INT;        // 1.2 - Reserved
    PINT XINT1_INT;                 // 1.3 - XINT1 Interrupt
    PINT XINT2_INT;                 // 1.4 - XINT2 Interrupt
    PINT SYS_ERR_INT;               // 2.1 - SYS_ERR Interrupt
    PINT TIMER0_INT;                // 2.2 - Timer 0 Interrupt
    PINT WAKE_INT;                  // 2.3 - Standby and Halt Wakeup Interrupt
    PINT MCPWM1_INT;                // 2.4 - MCPWM1 Interrupt
    PINT PIE15_RESERVED_INT;        // 3.1 - Reserved
    PINT MCPWM3_INT;                // 3.2 - MCPWM3 Interrupt
    PINT PIE16_RESERVED_INT;        // 3.3 - Reserved
    PINT PIE17_RESERVED_INT;        // 3.4 - Reserved
    PINT PIE18_RESERVED_INT;        // 4.1 - Reserved
    PINT PIE19_RESERVED_INT;        // 4.2 - Reserved
    PINT ECAP1_INT;                 // 4.3 - eCAP1 Interrupt
    PINT PIE20_RESERVED_INT;        // 4.4 - Reserved
    PINT EQEP1_INT;                 // 5.1 - eQEP1 Interrupt
    PINT SPIA_RX_INT;               // 5.2 - SPIA Receive Interrupt
    PINT SPIA_TX_INT;               // 5.3 - SPIA Transmit Interrupt
    PINT PIE21_RESERVED_INT;        // 5.4 - Reserved
    PINT PIE22_RESERVED_INT;        // 6.1 - Reserved
    PINT DCC0_INT;                  // 6.2 - DCC0 Interrupt
    PINT DMA_CH1_INT;               // 6.3 - DMA Channel 1 Interrupt
    PINT DMA_CH2_INT;               // 6.4 - DMA Channel 2 Interrupt
    PINT PIE23_RESERVED_INT;        // 7.1 - Reserved
    PINT I2CA_INT;                  // 7.2 - I2CA Interrupt 1
    PINT I2CA_FIFO_INT;             // 7.3 - I2CA Interrupt 2
    PINT SCIA_RX_INT;               // 7.4 - SCIA Receive Interrupt
    PINT SCIA_TX_INT;               // 8.1 - SCIA Transmit Interrupt
    PINT SCIB_RX_INT;               // 8.2 - SCIB Receive Interrupt
    PINT SCIB_TX_INT;               // 8.3 - SCIB Transmit Interrupt
    PINT PIE24_RESERVED_INT;        // 8.4 - Reserved
    PINT PIE25_RESERVED_INT;        // 9.1 - Reserved
    PINT UARTA_INT;                 // 9.2 - UARTA Interrupt
    PINT ADCA_EVT_INT;              // 9.3 - ADCA Event Interrupt
    PINT ADCA2_INT;                 // 9.4 - ADCA Interrupt 2
    PINT PIE26_RESERVED_INT;        // 10.1 - Reserved
    PINT PIE27_RESERVED_INT;        // 10.2 - Reserved
    PINT XINT3_INT;                 // 10.3 - XINT3 Interrupt
    PINT XINT4_INT;                 // 10.4 - XINT4 Interrupt
    PINT XINT5_INT;                 // 11.1 - XINT5 Interrupt
    PINT FLSS_INT;                  // 11.2 - Interrupt from flash sub-system
    PINT PIE28_RESERVED_INT;        // 11.3 - Reserved
    PINT PIE29_RESERVED_INT;        // 11.4 - Reserved
    PINT PIE30_RESERVED_INT;        // 12.1 - Reserved
    PINT PIE31_RESERVED_INT;        // 12.2 - Reserved
    PINT PIE32_RESERVED_INT;        // 12.3 - Reserved
    PINT PIE33_RESERVED_INT;        // 12.4 - Reserved
};

//---------------------------------------------------------------------------
// PieVect External References & Function Declarations:
//

extern volatile struct PIE_VECT_TABLE PieVectTable;

#ifdef __cplusplus
}
#endif                                               /* extern "C" */


#endif                                               // end of F28E12X_PIEVECT_H definition
//===========================================================================
// End of file.
//===========================================================================
