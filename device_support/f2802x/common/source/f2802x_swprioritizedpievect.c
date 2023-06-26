//###########################################################################
//
// FILE:   F2802x_SWPrioritizedPieVect.c
//
// TITLE:  F2802x Devices SW Prioritized PIE Vector Table Initialization.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F2802x_Device.h"     // Headerfile Include File
#include "f2802x_examples.h"   // Examples Include File
#include "f2802x_swprioritizedisrlevels.h"

const struct PIE_VECT_TABLE PieVectTableInit = 
{
    PIE_RESERVED,       // Reserved space
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved
    PIE_RESERVED,       // reserved

    //
    // Non-Peripheral Interrupts
    //
#if (INT13PL != 0)
    INT13_ISR,     // INT13 or CPU-Timer1
#else
    INT_NOTUSED_ISR,
#endif

#if (INT14PL != 0)
    INT14_ISR,     // INT14 or CPU-Timer2
#else
    INT_NOTUSED_ISR,
#endif

#if (INT15PL != 0)
    DATALOG_ISR,   // Datalogging interrupt
#else
    INT_NOTUSED_ISR,
#endif

#if (INT16PL != 0)
    RTOSINT_ISR,   // RTOS interrupt
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,      // reserved interrupt
    NMI_ISR,       // Non-maskable interrupt
    ILLEGAL_ISR,   // Illegal operation TRAP
    USER1_ISR,     // User Defined trap 1
    USER2_ISR,     // User Defined trap 2
    USER3_ISR,     // User Defined trap 3
    USER4_ISR,     // User Defined trap 4
    USER5_ISR,     // User Defined trap 5
    USER6_ISR,     // User Defined trap 6
    USER7_ISR,     // User Defined trap 7
    USER8_ISR,     // User Defined trap 8
    USER9_ISR,     // User Defined trap 9
    USER10_ISR,    // User Defined trap 10
    USER11_ISR,    // User Defined trap 11
    USER12_ISR,    // User Defined trap 12

    //
    // Group 1 PIE Vectors
    //
#if (G11PL != 0)
    ADCINT1_ISR,   // ADC    or change to rsvd_ISR if 10.1 is ADCINT1
#else
    INT_NOTUSED_ISR,
#endif

#if (G12PL != 0)
    ADCINT2_ISR,   // ADC    or change to rsvd_ISR if 10.2 is ADCINT2
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,

#if (G14PL != 0)
    XINT1_ISR,     // External
#else
    INT_NOTUSED_ISR,
#endif

#if (G15PL != 0)
    XINT2_ISR,     // External
#else
    INT_NOTUSED_ISR,
#endif

#if (G16PL != 0)
    ADCINT9_ISR,    // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G17PL != 0)
    TINT0_ISR,     // Timer 0
#else
    INT_NOTUSED_ISR,
#endif

#if (G18PL != 0)
    WAKEINT_ISR,   // WD & Low Power
#else
    INT_NOTUSED_ISR,
#endif

    //
    // Group 2 PIE Vectors
    //
#if (G21PL != 0)
    EPWM1_TZINT_ISR,   // ePWM1 Trip Zone
#else
    INT_NOTUSED_ISR,
#endif

#if (G22PL != 0)
    EPWM2_TZINT_ISR,   // ePWM2 Trip Zone
#else
    INT_NOTUSED_ISR,
#endif

#if (G23PL != 0)
    EPWM3_TZINT_ISR,   // ePWM3 Trip Zone
#else
    INT_NOTUSED_ISR,
#endif

#if (G24PL != 0)
    EPWM4_TZINT_ISR,   // ePWM4 Trip Zone
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 3 PIE Vectors
    //
#if (G31PL != 0)
    EPWM1_INT_ISR,     // ePWM1 Interrupt
#else
    INT_NOTUSED_ISR,
#endif

#if (G32PL != 0)
    EPWM2_INT_ISR,     // ePWM2 Interrupt
#else
    INT_NOTUSED_ISR,
#endif

#if (G33PL != 0)
    EPWM3_INT_ISR,     // ePWM3 Interrupt
#else
    INT_NOTUSED_ISR,
#endif

#if (G34PL != 0)
    EPWM4_INT_ISR,     // ePWM4 Interrupt
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 4 PIE Vectors
    //
#if (G41PL != 0)
    ECAP1_INT_ISR,     // eCAP1 Interrupt
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 5 PIE Vectors
    //
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 6 PIE Vectors
    //
#if (G61PL != 0)
    SPIRXINTA_ISR,  // SPI-A
#else
    INT_NOTUSED_ISR,
#endif

#if (G62PL != 0)
    SPITXINTA_ISR,  // SPI-A
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 7 PIE Vectors
    //
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 8 PIE Vectors
    //
#if (G81PL != 0)
    I2CINT1A_ISR,    // I2C-A
#else
    INT_NOTUSED_ISR,
#endif

#if (G82PL != 0)
    I2CINT2A_ISR,    // I2C-A
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 9 PIE Vectors
    //
#if (G91PL != 0)
    SCIRXINTA_ISR,    // SCI-A
#else
    INT_NOTUSED_ISR,
#endif

#if (G92PL != 0)
    SCITXINTA_ISR,    // SCI-A
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 10 PIE Vectors
    //
    rsvd_ISR,          // or change to ADCINT1_ISR if ADCINT1 is 10.1 in G101PL
    rsvd_ISR,          // or change to ADCINT2_ISR if ADCINT2 is 10.2 in G102PL

#if (G103PL != 0)
    ADCINT3_ISR,     // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G104PL != 0)
    ADCINT4_ISR,     // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G105PL != 0)
    ADCINT5_ISR,     // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G106PL != 0)
    ADCINT6_ISR,     // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G107PL != 0)
    ADCINT7_ISR,     // ADC
#else
    INT_NOTUSED_ISR,
#endif

#if (G108PL != 0)
    ADCINT8_ISR,    // ADC
#else
    INT_NOTUSED_ISR,
#endif

    //
    // Group 11 PIE Vectors
    //
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 12 PIE Vectors
    //
#if (G121PL != 0)
    XINT3_ISR,    // External interrupt
#else
    INT_NOTUSED_ISR,
#endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
};

//
// InitPieVectTable -  This function initializes the PIE vector table to a 
// known state. This function must be executed after boot time.
//
void
InitPieVectTable(void)
{
    int16    i;
    Uint32 *Source = (void *) &PieVectTableInit;
    Uint32 *Dest = (void *) &PieVectTable;

    //
    // Do not write over first 3 32-bit locations (these locations are
    // initialized by Boot ROM with boot variables)
    //
    Source = Source + 3;
    Dest = Dest + 3;

    EALLOW;
    for(i=0; i < 125; i++)
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
// End of File
//

