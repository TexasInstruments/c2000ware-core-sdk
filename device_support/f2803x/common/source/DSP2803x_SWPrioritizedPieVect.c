//###########################################################################
//
// FILE:   DSP2803x_SWPiroritizedPieVect.c
//
// TITLE:  DSP2803x Devices SW Prioritized PIE Vector Table Initialization.
//
//###########################################################################
//
// Original Source by A.T.
//
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "DSP2803x_SWPrioritizedIsrLevels.h"

//
// Define PIE Vector Table
//
const struct PIE_VECT_TABLE PieVectTableInit = {
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
    
    //
    // CPU-Timer1
    //
    #if (INT13PL != 0)
        INT13_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CPU-Timer2
    //
    #if (INT14PL != 0)
        INT14_ISR,
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // Datalogging interrupt
    //
    #if (INT15PL != 0)
        DATALOG_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // RTOS interrupt
    // 
    #if (INT16PL != 0)
        RTOSINT_ISR,
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,       // reserved interrupt
    NMI_ISR,        // Non-maskable interrupt
    ILLEGAL_ISR,    // Illegal operation TRAP
    USER1_ISR,      // User Defined trap 1
    USER2_ISR,      // User Defined trap 2
    USER3_ISR,      // User Defined trap 3
    USER4_ISR,      // User Defined trap 4
    USER5_ISR,      // User Defined trap 5
    USER6_ISR,      // User Defined trap 6
    USER7_ISR,      // User Defined trap 7
    USER8_ISR,      // User Defined trap 8
    USER9_ISR,      // User Defined trap 9
    USER10_ISR,     // User Defined trap 10
    USER11_ISR,     // User Defined trap 11
    USER12_ISR,     // User Defined trap 12

    //
    // Group 1 PIE Vectors:
    //
    
    //
    // ADC or change to rsvd_ISR if 10.1 is ADCINT1
    //
    #if (G11PL != 0)
        ADCINT1_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC	or change to rsvd_ISR if 10.2 is ADCINT2
    //
    #if (G12PL != 0)
        ADCINT2_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,

    //
    // External
    //
    #if (G14PL != 0)
        XINT1_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // External
    //
    #if (G15PL != 0)
        XINT2_ISR,
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G16PL != 0)
        ADCINT9_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // Timer 0
    //
    #if (G17PL != 0)
        TINT0_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // WD & Low Power
    //
    #if (G18PL != 0)
        WAKEINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // Group 2 PIE Vectors:
    //
    
    //
    // ePWM1 Trip Zone
    //
    #if (G21PL != 0)
        EPWM1_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM2 Trip Zone
    //
    #if (G22PL != 0)
        EPWM2_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM3 Trip Zone
    //
    #if (G23PL != 0)
        EPWM3_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM4 Trip Zone
    //
    #if (G24PL != 0)
        EPWM4_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM5 Trip Zone
    //
    #if (G25PL != 0)
        EPWM5_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM6 Trip Zone
    //
    #if (G26PL != 0)
        EPWM6_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM7 Trip Zone
    //
    #if (G27PL != 0)
        EPWM7_TZINT_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,

    //
    // Group 3 PIE Vectors:
    //
    
    //
    // ePWM1 Interrupt
    //
    #if (G31PL != 0)
        EPWM1_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM2 Interrupt
    //
    #if (G32PL != 0)
        EPWM2_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM3 Interrupt
    //
    #if (G33PL != 0)
        EPWM3_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM4 Interrupt
    //
    #if (G34PL != 0)
        EPWM4_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM5 Interrupt
    //
    #if (G35PL != 0)
        EPWM5_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM6 Interrupt
    //
    #if (G36PL != 0)
        EPWM6_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ePWM7 Interrupt
    //
    #if (G37PL != 0)
        EPWM7_INT_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,

    //
    // Group 4 PIE Vectors:
    //
    
    //
    // eCAP1 Interrupt
    //
    #if (G41PL != 0)
        ECAP1_INT_ISR,     
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
    // Group 5 PIE Vectors:
    //

    //
    // eQEP1 Interrupt
    //
    #if (G51PL != 0)
        EQEP1_INT_ISR,     
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
    // Group 6 PIE Vectors:
    //
    
    //
    // SPI-A
    //
    #if (G61PL != 0)
        SPIRXINTA_ISR,  
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // SPI-A
    //
    #if (G62PL != 0)
        SPITXINTA_ISR,  
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
    // Group 7 PIE Vectors:
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
    // Group 8 PIE Vectors:
    //
    
    //
    // I2C-A
    //
    #if (G81PL != 0)
        I2CINT1A_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // I2C-A
    //
    #if (G82PL != 0)
        I2CINT2A_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // SCI-C
    //
    #if (G85PL != 0)
        SCIRXINTC_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // SCI-C
    //
    #if (G86PL != 0)
        SCITXINTC_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 9 PIE Vectors:
    //
    
    //
    // SCI-A
    //
    #if (G91PL != 0)
        SCIRXINTA_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // SCI-A
    //
    #if (G92PL != 0)
        SCITXINTA_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // LIN0-A
    //
    #if (G93PL != 0)
        LIN0INTA_ISR,
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // LIN1-A
    //
    #if (G94PL != 0)
        LIN1INTA_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // eCAN-A
    //
    #if (G95PL != 0)
        ECAN0INTA_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // eCAN-A
    //
    #if (G96PL != 0)
        ECAN1INTA_ISR,   
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,

    //
    // Group 10 PIE Vectors
    //

    rsvd_ISR,	      // or change to ADCINT1_ISR if ADCINT1 is 10.1 in G101PL
    rsvd_ISR,		  // or change to ADCINT2_ISR if ADCINT2 is 10.2 in G102PL

    //
    // ADC
    //
    #if (G103PL != 0)
        ADCINT3_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G104PL != 0)
        ADCINT4_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G105PL != 0)
        ADCINT5_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G106PL != 0)
        ADCINT6_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G107PL != 0)
        ADCINT7_ISR,
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // ADC
    //
    #if (G108PL != 0)
        ADCINT8_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // Group 11 PIE Vectors
    //

    //
    // CLA1_INT1
    //
    #if (G111PL != 0)
        CLA1_INT1_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT2
    //
    #if (G112PL != 0)
        CLA1_INT2_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT3
    //
    #if (G113PL != 0)
        CLA1_INT3_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT4
    //
    #if (G114PL != 0)
        CLA1_INT4_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT5
    //
    #if (G115PL != 0)
        CLA1_INT5_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT6
    //
    #if (G116PL != 0)
        CLA1_INT6_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT7
    //
    #if (G117PL != 0)
        CLA1_INT7_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1_INT8
    //
    #if (G118PL != 0)
        CLA1_INT8_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // Group 12 PIE Vectors
    //
    
    //
    // External interrupt
    //
    #if (G121PL != 0)
        XINT3_ISR,    
    #else
        INT_NOTUSED_ISR,
    #endif

    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,
    rsvd_ISR,

    //
    // CLA1 Overflow
    //
    #if (G127PL != 0)
        LVF_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif

    //
    // CLA1 Underflow
    //
    #if (G128PL != 0)
        LUF_ISR,     
    #else
        INT_NOTUSED_ISR,
    #endif
};

//
// InitPieVectTable - This function initializes the PIE vector table
// to a known state. This function must be executed after boot time.
//
void 
InitPieVectTable(void)
{
	int16	i;
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

