//###########################################################################
//
// FILE:   f28e12x_pievect.c
//
// TITLE:  f28e12x Device PIE Vector Initialization Functions
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

//
// Included Files
//
#include "f28e12x_device.h"       // f28e12x Header File Include File
#include "f28e12x_examples.h"     // f28e12x Examples Include File

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
    RTOS_ISR,                       // RTOS Interrupt from ERAD
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
    PIE_RESERVED_ISR,               // 1.2 - Reserved
    XINT1_ISR,                      // 1.3 - XINT1 Interrupt
    XINT2_ISR,                      // 1.4 - XINT2 Interrupt
    SYS_ERR_ISR,                    // 2.1 - SYS_ERR Interrupt
    TIMER0_ISR,                     // 2.2 - Timer 0 Interrupt
    WAKE_ISR,                       // 2.3 - Standby and Halt Wakeup Interrupt
    MCPWM1_ISR,                     // 2.4 - MCPWM1 Interrupt
    PIE_RESERVED_ISR,               // 3.1 - Reserved
    MCPWM3_ISR,                     // 3.2 - MCPWM3 Interrupt
    PIE_RESERVED_ISR,               // 3.3 - Reserved
    PIE_RESERVED_ISR,               // 3.4 - Reserved
    PIE_RESERVED_ISR,               // 4.1 - Reserved
    PIE_RESERVED_ISR,               // 4.2 - Reserved
    ECAP1_ISR,                      // 4.3 - eCAP1 Interrupt
    PIE_RESERVED_ISR,               // 4.4 - Reserved
    EQEP1_ISR,                      // 5.1 - eQEP1 Interrupt
    SPIA_RX_ISR,                    // 5.2 - SPIA Receive Interrupt
    SPIA_TX_ISR,                    // 5.3 - SPIA Transmit Interrupt
    PIE_RESERVED_ISR,               // 5.4 - Reserved
    PIE_RESERVED_ISR,               // 6.1 - Reserved
    DCC0_ISR,                       // 6.2 - DCC0 Interrupt
    DMA_CH1_ISR,                    // 6.3 - DMA Channel 1 Interrupt
    DMA_CH2_ISR,                    // 6.4 - DMA Channel 2 Interrupt
    PIE_RESERVED_ISR,               // 7.1 - Reserved
    I2CA_ISR,                       // 7.2 - I2CA Interrupt 1
    I2CA_FIFO_ISR,                  // 7.3 - I2CA Interrupt 2
    SCIA_RX_ISR,                    // 7.4 - SCIA Receive Interrupt
    SCIA_TX_ISR,                    // 8.1 - SCIA Transmit Interrupt
    SCIB_RX_ISR,                    // 8.2 - SCIB Receive Interrupt
    SCIB_TX_ISR,                    // 8.3 - SCIB Transmit Interrupt
    PIE_RESERVED_ISR,               // 8.4 - Reserved
    PIE_RESERVED_ISR,               // 9.1 - Reserved
    UARTA_ISR,                      // 9.2 - UARTA Interrupt
    ADCA_EVT_ISR,                   // 9.3 - ADCA Event Interrupt
    ADCA2_ISR,                      // 9.4 - ADCA Interrupt 2
    PIE_RESERVED_ISR,               // 10.1 - Reserved
    PIE_RESERVED_ISR,               // 10.2 - Reserved
    XINT3_ISR,                      // 10.3 - XINT3 Interrupt
    XINT4_ISR,                      // 10.4 - XINT4 Interrupt
    XINT5_ISR,                      // 11.1 - XINT5 Interrupt
    FLSS_ISR,                       // 11.2 - Interrupt from flash sub-system
    PIE_RESERVED_ISR,               // 11.3 - Reserved
    PIE_RESERVED_ISR,               // 11.4 - Reserved
    PIE_RESERVED_ISR,               // 12.1 - Reserved
    PIE_RESERVED_ISR,               // 12.2 - Reserved
    PIE_RESERVED_ISR,               // 12.3 - Reserved
    PIE_RESERVED_ISR,               // 12.4 - Reserved
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
    for(i = 0; i < 77; i++)
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
