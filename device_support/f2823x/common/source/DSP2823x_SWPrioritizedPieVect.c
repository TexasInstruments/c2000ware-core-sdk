// TI File $Revision: /main/2 $
// Checkin $Date: April 4, 2007   14:25:31 $
//###########################################################################
//
// FILE:   DSP2823x_SWPiroritizedPieVect.c
//
// TITLE:  DSP2823x Devices SW Prioritized PIE Vector Table Initialization.
//
//###########################################################################
// $TI Release: 2823x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
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

//
// Included Files
//
#include "DSP2823x_Device.h"     // DSP2823x Headerfile Include File
#include "DSP2823x_Examples.h"   // DSP2823x Examples Include File
#include "DSP2823x_SWPrioritizedIsrLevels.h" 

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
    // Non-Peripheral Interrupts:
    //
    #if (INT13PL != 0)
    INT13_ISR,    // XINT13
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (INT14PL != 0)
    INT14_ISR,     // CPU-Timer2
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
    // Group 1 PIE Vectors:
    //
    #if (G11PL != 0)
    SEQ1INT_ISR,   // ADC
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G12PL != 0)
    SEQ2INT_ISR,   // ADC 
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
    ADCINT_ISR,    // ADC
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
    // Group 2 PIE Vectors:
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

    #if (G25PL != 0)
    EPWM5_TZINT_ISR,   // ePWM5 Trip Zone
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G26PL != 0)
    EPWM6_TZINT_ISR,   // ePWM6 Trip Zone
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 3 PIE Vectors:
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

    #if (G35PL != 0)
    EPWM5_INT_ISR,     // ePWM5 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G36PL != 0)
    EPWM6_INT_ISR,     // ePWM6 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 4 PIE Vectors:
    //
    #if (G41PL != 0)
    ECAP1_INT_ISR,     // eCAP1 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G42PL != 0)
    ECAP2_INT_ISR,     // eCAP2 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G43PL != 0)
    ECAP3_INT_ISR,     // eCAP3 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G44PL != 0)
    ECAP4_INT_ISR,     // eCAP4 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G45PL != 0)
    ECAP5_INT_ISR,     // eCAP5 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G46PL != 0)
    ECAP6_INT_ISR,     // eCAP6 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,          

    //
    // Group 5 PIE Vectors:
    //
    #if (G51PL != 0)
    EQEP1_INT_ISR,     // eQEP1 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G52PL != 0)
    EQEP2_INT_ISR,     // eQEP2 Interrupt
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
    // Group 6 PIE Vectors:
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

    #if (G63PL != 0)
    MRINTB_ISR,     // McBSP-B
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G64PL != 0)
    MXINTB_ISR,     // McBSP-B
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G65PL != 0)
    MRINTA_ISR,     // McBSP-A
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G66PL != 0)
    MXINTA_ISR,     // McBSP-A
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 7 PIE Vectors:
    //
    #if (G71PL != 0)
    DINTCH1_ISR,     // DMA-Channel 1 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G72PL != 0)
    DINTCH2_ISR,     // DMA-Channel 2 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G73PL != 0)
    DINTCH3_ISR,     // DMA-Channel 3 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G74PL != 0)
    DINTCH4_ISR,     // DMA-Channel 4 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G75PL != 0)
    DINTCH5_ISR,     // DMA-Channel 5 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G76PL != 0)
    DINTCH6_ISR,     // DMA-Channel 6 Interrupt
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,         

    //
    // Group 8 PIE Vectors:
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
     
    #if (G85PL != 0)
    SCIRXINTC_ISR,    // SCI-C
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G86PL != 0)
    SCITXINTC_ISR,    // SCI-C
    #else
    INT_NOTUSED_ISR,
    #endif
      
    rsvd_ISR,     
    rsvd_ISR,     

    //
    // Group 9 PIE Vectors:
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

    #if (G93PL != 0)
    SCIRXINTB_ISR,    // SCI-B
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G94PL != 0)
    SCITXINTB_ISR,    // SCI-B
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G95PL != 0)
    ECAN0INTA_ISR,    // eCAN-A
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G96PL != 0)
    ECAN1INTA_ISR,   // eCAN-A
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G97PL != 0)
    ECAN0INTB_ISR,   // eCAN-B
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G98PL != 0)
    ECAN1INTB_ISR,   // eCAN-B
    #else
    INT_NOTUSED_ISR,
    #endif

    //
    // Group 10 PIE Vectors
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
    XINT3_ISR,       // External interrupt 3
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G122PL != 0)
    XINT4_ISR,       // External interrupt 4
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G123PL != 0)
    XINT5_ISR,       // External interrupt 5
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G124PL != 0)
    XINT6_ISR,       // External interrupt 6
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G125PL != 0)
    XINT7_ISR,       // External interrupt 7
    #else
    INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,

    #if (G127PL != 0)
    LVF_ISR,         // Latched overflow flag  
    #else
    INT_NOTUSED_ISR,
    #endif

    #if (G128PL != 0)
    LUF_ISR,         // Latched underflow flag
    #else
    INT_NOTUSED_ISR,
    #endif   
};

//
// InitPieVectTable - This function initializes the PIE vector table to a known
// state. This function must be executed after boot time.
//
void 
InitPieVectTable(void)
{
    int16 i;
    Uint32 *Source = (void *) &PieVectTableInit;
    Uint32 *Dest = (void *) &PieVectTable;

    EALLOW;
    for(i=0; i < 128; i++) 
    {
        *Dest++ = *Source++;
    }
    EDIS;
}

//
// End of File
//

