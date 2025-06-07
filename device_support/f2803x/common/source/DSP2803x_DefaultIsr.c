//###########################################################################
//
// FILE:	DSP2803x_DefaultIsr.c
//
// TITLE:	DSP2803x Device Default Interrupt Service Routines.
//
// This file contains shell ISR routines for the 2803x PIE vector table.
// Typically these shell ISR routines can be used to populate the entire PIE
// vector table during device debug.  In this manner if an interrupt is taken
// during firmware development, there will always be an ISR to catch it.
//
// As develpment progresses, these ISR rotuines can be eliminated and replaced
// with the user's own ISR routines for each interrupt.  Since these shell ISRs
// include infinite loops they will typically not be included as-is in the 
// final production firmware.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

//
// INT13_ISR - Connected to INT13 of CPU (use MINT13 mask):
// ISR can be used by the user.
// INT13 or CPU-Timer1
//
__interrupt void 
INT13_ISR(void)     
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// INT14_ISR - INT14 or CPU-Timer2
//
__interrupt void 
INT14_ISR(void) 
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// DATALOG_ISR - Datalogging Interrupt
//
__interrupt void 
DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// RTOSINT_ISR - RTOS Interrupt
//
__interrupt void 
RTOSINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EMUINT_ISR - Emulation Interrupt
//
__interrupt void 
EMUINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-Maskable Interrupt
//
__interrupt void 
NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ILLEGAL_ISR - Illegal Operation Trap
//
__interrupt void
ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined Trap 1
//
__interrupt void
USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined Trap 2
//
__interrupt void 
USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined Trap 3
//
__interrupt void 
USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined Trap 4
//
__interrupt void 
USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined Trap 5
//
__interrupt void 
USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined Trap 6
//
__interrupt void 
USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined Trap 7
//
__interrupt void 
USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined Trap 8
//
__interrupt void 
USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined Trap 9
//
__interrupt void 
USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined Trap 10
//
__interrupt void 
USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined Trap 11
//
__interrupt void 
USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined Trap 12
//
__interrupt void 
USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 1 - MUXed into CPU INT1
//

//
// ADCINT1_ISR - INT1.1 ADC  (Can also be ISR for INT10.1 when enabled)
//
__interrupt void 
ADCINT1_ISR(void)   
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT2_ISR - INT1.2 ADC  (Can also be ISR for INT10.2 when enabled)
//
__interrupt void 
ADCINT2_ISR(void)  
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// XINT1_ISR - INT1.4
//
__interrupt void  
XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// XINT2_ISR - INT1.5
//
__interrupt void  
XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT9_ISR - INT1.6
//
__interrupt void  
ADCINT9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// TINT0_ISR - INT1.7 CPU-Timer 0
//
__interrupt void  
TINT0_ISR(void)      
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// WAKEINT_ISR - INT1.8  WD, LOW Power
//
__interrupt void  
WAKEINT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 2 - MUXed into CPU INT2
//

//
// EPWM1_TZINT_ISR - INT2.1 EPWM-1
//
__interrupt void 
EPWM1_TZINT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_TZINT_ISR - INT2.2 EPWM-2
//
__interrupt void 
EPWM2_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_TZINT_ISR - INT2.3 EPWM-3
//
__interrupt void 
EPWM3_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_TZINT_ISR - INT2.4 EPWM-4
//
__interrupt void 
EPWM4_TZINT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_TZINT_ISR - INT2.5  EPWM-5
//
__interrupt void 
EPWM5_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_TZINT_ISR - INT2.6 EPWM-6
//
__interrupt void 
EPWM6_TZINT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM7_TZINT_ISR - INT2.7 EPWM-7
//
__interrupt void 
EPWM7_TZINT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, 
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - INT 3.1  EPWM-1
//
__interrupt void 
EPWM1_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_INT_ISR - INT3.2  EPWM-2
//
__interrupt void 
EPWM2_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_INT_ISR - INT3.3 EPWM-3
//
__interrupt void 
EPWM3_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_INT_ISR - INT3.4 EPWM-4
//
__interrupt void 
EPWM4_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_INT_ISR - INT3.5 EPWM-5
//
__interrupt void 
EPWM5_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_INT_ISR - INT3.5 EPWM-6
//
__interrupt void 
EPWM6_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// EPWM7_INT_ISR - INT3.5 EPWM-7
//
__interrupt void 
EPWM7_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 4 - MUXed into CPU INT4
//

// 
// ECAP1_INT_ISR - INT 4.1 ECAP-1
//
__interrupt void 
ECAP1_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// HRCAP1_INT_ISR - INT 4.7 HRCAP-1
//
__interrupt void 
HRCAP1_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// HRCAP2_INT_ISR -  HRCAP-2 - INT 4.8
//
__interrupt void 
HRCAP2_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 5 - MUXed into CPU INT5
//

//
// EQEP1_INT_ISR - INT 5.1 EQEP-1
//
__interrupt void 
EQEP1_INT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 6 - MUXed into CPU INT6
//

//
// SPIRXINTA_ISR - INT6.1 SPI-A
//
__interrupt void 
SPIRXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// SPITXINTA_ISR - INT6.2 SPI-A
//
__interrupt void 
SPITXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// SPIRXINTB_ISR - INT6.3 SPI-B
//
__interrupt void 
SPIRXINTB_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}
//
// SPITXINTB_ISR - INT6.4 SPI-B
//
__interrupt void 
SPITXINTB_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

// 
// PIE Group 7 - MUXed into CPU INT7
// 

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - INT8.1 I2C-A
//
__interrupt void 
I2CINT1A_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,  
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// I2CINT2A_ISR - INT8.2 I2C-A
//
__interrupt void 
I2CINT2A_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,  
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 9 - MUXed into CPU INT9
//

//
// SCIRXINTA_ISR - INT9.1 SCI-A
//
__interrupt void 
SCIRXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// SCITXINTA_ISR - INT9.2 SCI-A
//
__interrupt void 
SCITXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// LIN0INTA_ISR - INT9.3 LIN-A
__interrupt void 
LIN0INTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// LIN1INTA_ISR - INT9.4 LIN-A
//
__interrupt void 
LIN1INTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ECAN0INTA_ISR - INT9.5 eCAN-A
//
__interrupt void 
ECAN0INTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ECAN1INTA_ISR - INT9.6 eCAN-A
//
__interrupt void 
ECAN1INTA_ISR(void)  
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 10 - MUXed into CPU INT10
//

//
// INT10.1 - Reserved or ADCINT1_ISR
// INT10.2 - Reserved or ADCINT2_ISRk
//

//
// ADCINT3_ISR - INT10.3 ADC
//
__interrupt void 
ADCINT3_ISR(void)    
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT4_ISR - INT10.4 ADC
//
__interrupt void 
ADCINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT5_ISR - INT10.5 ADC
//
__interrupt void 
ADCINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT6_ISR - INT10.6 ADC
//
__interrupt void 
ADCINT6_ISR(void)
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT7_ISR - INT10.7 ADC
//
__interrupt void 
ADCINT7_ISR(void)
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT8_ISR - INT10.8 ADC
//
__interrupt void 
ADCINT8_ISR(void)
{
    //
    // Insert ISR Code here
    //
    
    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 11 - MUXed into CPU INT11
//

//
// CLA1_INT1_ISR - INT11.1 MCLA
//
__interrupt void 
CLA1_INT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT2_ISR - INT11.2 MCLA
//
__interrupt void 
CLA1_INT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT3_ISR - INT11.3 MCLA
//
__interrupt void 
CLA1_INT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT4_ISR - INT11.4 MCLA
//
__interrupt void 
CLA1_INT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT5_ISR - INT11.5 MCLA
//
__interrupt void 
CLA1_INT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT6_ISR - INT11.6 MCLA
//
__interrupt void 
CLA1_INT6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT7_ISR - INT11.7 MCLA
//
__interrupt void 
CLA1_INT7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_INT8_ISR - INT11.8 MCLA
//
__interrupt void 
CLA1_INT8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 12 - MUXed into CPU INT12
//

//
// XINT3_ISR - INT12.1 External interrupt 3
//
__interrupt void 
XINT3_ISR(void)  
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// LVF_ISR - INT12.7 CLA1 - overflow
//
__interrupt void 
LVF_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// LUF_ISR - INT12.8 CLA1 - underflow
//
__interrupt void 
LUF_ISR(void)  
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// Catch All Default ISRs
//

//
// EMPTY_ISR - Empty ISR (only does a return.)
//
__interrupt void 
EMPTY_ISR(void)
{

}

//
// PIE_RESERVED - Reserved space.  For test.
//
__interrupt void 
PIE_RESERVED(void)
{
    __asm ("      ESTOP0");
    for(;;);
}

//
// rsvd_ISR - for test
//
__interrupt void 
rsvd_ISR(void)
{
    __asm ("      ESTOP0");
    for(;;);
}

//
// End of file
//

