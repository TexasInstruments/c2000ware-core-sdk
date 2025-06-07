// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:38 $
//###########################################################################
//
// FILE:	DSP2833x_PieVect.c
//
// TITLE:	DSP2833x Devices PIE Vector Table Initialization Functions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
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
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

const struct PIE_VECT_TABLE PieVectTableInit = 
{
    PIE_RESERVED,  // 0  Reserved space
    PIE_RESERVED,  // 1  Reserved space 
    PIE_RESERVED,  // 2  Reserved space 
    PIE_RESERVED,  // 3  Reserved space 
    PIE_RESERVED,  // 4  Reserved space 
    PIE_RESERVED,  // 5  Reserved space 
    PIE_RESERVED,  // 6  Reserved space 
    PIE_RESERVED,  // 7  Reserved space 
    PIE_RESERVED,  // 8  Reserved space 
    PIE_RESERVED,  // 9  Reserved space 
    PIE_RESERVED,  // 10 Reserved space 
    PIE_RESERVED,  // 11 Reserved space 
    PIE_RESERVED,  // 12 Reserved space 

    //
    // Non-Peripheral Interrupts
    //
    INT13_ISR,     // XINT13 or CPU-Timer 1
    INT14_ISR,     // CPU-Timer2
    DATALOG_ISR,   // Datalogging interrupt
    RTOSINT_ISR,   // RTOS interrupt
    EMUINT_ISR,    // Emulation interrupt
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
    SEQ1INT_ISR,     // 1.1 ADC  
    SEQ2INT_ISR,     // 1.2 ADC  
    rsvd_ISR,        // 1.3
    XINT1_ISR,       // 1.4     
    XINT2_ISR,       // 1.5
    ADCINT_ISR,      // 1.6 ADC
    TINT0_ISR,       // 1.7 Timer 0
    WAKEINT_ISR,     // 1.8 WD, Low Power

    //
    // Group 2 PIE Vectors
    //
    EPWM1_TZINT_ISR, // 2.1 EPWM-1 Trip Zone
    EPWM2_TZINT_ISR, // 2.2 EPWM-2 Trip Zone
    EPWM3_TZINT_ISR, // 2.3 EPWM-3 Trip Zone
    EPWM4_TZINT_ISR, // 2.4 EPWM-4 Trip Zone
    EPWM5_TZINT_ISR, // 2.5 EPWM-5 Trip Zone
    EPWM6_TZINT_ISR, // 2.6 EPWM-6 Trip Zone                        
    rsvd_ISR,        // 2.7
    rsvd_ISR,        // 2.8

    //
    // Group 3 PIE Vectors
    //
    EPWM1_INT_ISR,   // 3.1 EPWM-1 Interrupt
    EPWM2_INT_ISR,   // 3.2 EPWM-2 Interrupt
    EPWM3_INT_ISR,   // 3.3 EPWM-3 Interrupt
    EPWM4_INT_ISR,   // 3.4 EPWM-4 Interrupt
    EPWM5_INT_ISR,   // 3.5 EPWM-5 Interrupt
    EPWM6_INT_ISR,   // 3.6 EPWM-6 Interrupt                        
    rsvd_ISR,        // 3.7
    rsvd_ISR,        // 3.8

    //
    // Group 4 PIE Vectors
    //
    ECAP1_INT_ISR,   // 4.1 ECAP-1
    ECAP2_INT_ISR,   // 4.2 ECAP-2
    ECAP3_INT_ISR,   // 4.3 ECAP-3
    ECAP4_INT_ISR,   // 4.4 ECAP-4            
    ECAP5_INT_ISR,   // 4.5 ECAP-5     
    ECAP6_INT_ISR,   // 4.6 ECAP-6          
    rsvd_ISR,        // 4.7      
    rsvd_ISR,        // 4.8      

    //
    // Group 5 PIE Vectors
    //
    EQEP1_INT_ISR,   // 5.1 EQEP-1
    EQEP2_INT_ISR,   // 5.2 EQEP-2
    rsvd_ISR,        // 5.3      
    rsvd_ISR,        // 5.4           
    rsvd_ISR,        // 5.5      
    rsvd_ISR,        // 5.6      
    rsvd_ISR,        // 5.7      
    rsvd_ISR,        // 5.8   

    //
    // Group 6 PIE Vectors
    //
    SPIRXINTA_ISR,   // 6.1 SPI-A
    SPITXINTA_ISR,   // 6.2 SPI-A
    MRINTA_ISR,      // 6.3 McBSP-A
    MXINTA_ISR,      // 6.4 McBSP-A
    MRINTB_ISR,      // 6.5 McBSP-B
    MXINTB_ISR,      // 6.6 McBSP-B
    rsvd_ISR,        // 6.7 
    rsvd_ISR,        // 6.8                  

    //
    // Group 7 PIE Vectors
    //
    DINTCH1_ISR,     // 7.1  DMA channel 1    
    DINTCH2_ISR,     // 7.2  DMA channel 2
    DINTCH3_ISR,     // 7.3  DMA channel 3      
    DINTCH4_ISR,     // 7.4  DMA channel 4           
    DINTCH5_ISR,     // 7.5  DMA channel 5      
    DINTCH6_ISR,     // 7.6  DMA channel 6      
    rsvd_ISR,        // 7.7      
    rsvd_ISR,        // 7.8   

    //
    // Group 8 PIE Vectors
    //
    I2CINT1A_ISR,    // 8.1  I2C    
    I2CINT2A_ISR,    // 8.2  I2C
    rsvd_ISR,        // 8.3      
    rsvd_ISR,        // 8.4           
    SCIRXINTC_ISR,   // 8.5  SCI-C
    SCITXINTC_ISR,   // 8.6  SCI-C      
    rsvd_ISR,        // 8.7      
    rsvd_ISR,        // 8.8    

    //
    // Group 9 PIE Vectors
    //
    SCIRXINTA_ISR,   // 9.1 SCI-A
    SCITXINTA_ISR,   // 9.2 SCI-A
    SCIRXINTB_ISR,   // 9.3 SCI-B
    SCITXINTB_ISR,   // 9.4 SCI-B
    ECAN0INTA_ISR,   // 9.5 eCAN-A
    ECAN1INTA_ISR,   // 9.6 eCAN-A
    ECAN0INTB_ISR,   // 9.7 eCAN-B
    ECAN1INTB_ISR,   // 9.8 eCAN-B

    //
    // Group 10 PIE Vectors
    //
    rsvd_ISR,        // 10.1      
    rsvd_ISR,        // 10.2
    rsvd_ISR,        // 10.3      
    rsvd_ISR,        // 10.4           
    rsvd_ISR,        // 10.5      
    rsvd_ISR,        // 10.6      
    rsvd_ISR,        // 10.7      
    rsvd_ISR,        // 10.8    

    //
    // Group 11 PIE Vectors
    //
    rsvd_ISR,        // 11.1      
    rsvd_ISR,        // 11.2
    rsvd_ISR,        // 11.3      
    rsvd_ISR,        // 11.4           
    rsvd_ISR,        // 11.5      
    rsvd_ISR,        // 11.6      
    rsvd_ISR,        // 11.7      
    rsvd_ISR,        // 11.8

    //
    // Group 12 PIE Vectors
    //
    XINT3_ISR,       // 12.1      
    XINT4_ISR,       // 12.2
    XINT5_ISR,       // 12.3      
    XINT6_ISR,       // 12.4           
    XINT7_ISR,       // 12.5      
    rsvd_ISR,        // 12.6      
    LVF_ISR,         // 12.7      
    LUF_ISR,         // 12.8   
};

//
// InitPieVectTable - This function initializes the PIE vector table to a known
// state. This function must be executed after boot time.
//
void 
InitPieVectTable(void)
{
    int16	i;
    Uint32 *Source = (void *) &PieVectTableInit;
    volatile Uint32 *Dest = (void *) &PieVectTable;
        
    EALLOW;	
    for(i=0; i < 128; i++)
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

