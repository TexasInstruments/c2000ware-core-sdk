//###########################################################################
//
// FILE:    F2802x_DefaultIsr.c
//
// TITLE:    F2802x Device Default Interrupt Service Routines.
//
// This file contains shell ISR routines for the 2802x PIE vector table.
// Typically these shell ISR routines can be used to populate the entire PIE
// vector table during device debug.  In this manner if an interrupt is taken
// during firmware development, there will always be an ISR to catch it.
//
// As development progresses, these ISR routines can be eliminated and replaced
// with the user's own ISR routines for each interrupt.  Since these shell ISRs
// include infinite loops they will typically not be included as-is in the 
// final production firmware.
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

//
// INT13_ISR - INT13 or CPU-Timer1 is connected to INT13 of CPU 
// (use MINT13 mask)
//
interrupt void
INT13_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT14_ISR - INT14 or CPU-Timer2
//
interrupt void
INT14_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);;
}

//
// DATALOG_ISR - Datalogging interrupt 
//
interrupt void
DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RTOSINT_ISR - RTOS interrupt
//
interrupt void
RTOSINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EMUINT_ISR - Emulation interrupt
//
interrupt void
EMUINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-maskable interrupt
//
interrupt void
NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ILLEGAL_ISR - Illegal operation TRAP
//
interrupt void
ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined trap 1
//
interrupt void
USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined trap 2
//
interrupt void
USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined trap 3 
//
interrupt void
USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined trap 4
//
interrupt void
USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined trap 5
//
interrupt void
USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined trap 6
//
interrupt void
USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined trap 7
//
interrupt void
USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined trap 8
//
interrupt void
USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined trap 9
//
interrupt void
USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined trap 10
//
interrupt void
USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined trap 11
//
interrupt void
USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined trap 12
//
interrupt void
USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 1 - MUXed into CPU INT1
//

//
// ADCINT1_ISR - INT1.1 is ADC  (Can also be ISR for INT10.1 when enabled)
//
interrupt void
ADCINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT2_ISR - INT1.2 is ADC  (Can also be ISR for INT10.2 when enabled)
//
interrupt void
ADCINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT1.3 - Reserved
//

//
// XINT1_ISR - INT1.4
//
interrupt void
XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT2_ISR - INT1.5
//
interrupt void
XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT9_ISR - INT1.6 ADC
//
interrupt void
ADCINT9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// TINT0_ISR - INT1.7 is CPU-Timer 0
//
interrupt void
TINT0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// WAKEINT_ISR - INT1.8 is WD, LOW Power
//
interrupt void
WAKEINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 2 - MUXed into CPU INT2
//

//
// EPWM1_TZINT_ISR - INT2.1
//
interrupt void
EPWM1_TZINT_ISR(void)    // EPWM-1
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_TZINT_ISR - INT2.2 is EPWM-2
//
interrupt void
EPWM2_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_TZINT_ISR - INT2.3 is EPWM-3
//
interrupt void
EPWM3_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_TZINT_ISR - INT2.4 is EPWM-4
//
interrupt void
EPWM4_TZINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT2.5 - Reserved
//

//
// INT2.6 - Reserved
//

//
// INT2.7 - Reserved
//

//
// INT2.8 - Reserved
//

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - INT 3.1 is EPWM-1
//
interrupt void
EPWM1_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_INT_ISR - INT3.2 is EPWM-2
//
interrupt void
EPWM2_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_INT_ISR - INT3.3 is EPWM-3
//
interrupt void
EPWM3_INT_ISR(void)    
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_INT_ISR - INT3.4 is EPWM-4
//
interrupt void
EPWM4_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT3.5 - Reserved
//

//
// INT3.6 - Reserved
//

//
// INT3.7 - Reserved
//

//
// INT3.8 - Reserved
//

//
// PIE Group 4 - MUXed into CPU INT4
//

//
// ECAP1_INT_ISR - INT 4.1 is ECAP-1
//
interrupt void
ECAP1_INT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT4.2 - Reserved
//

//
// INT4.3 - Reserved
//

//
// INT4.4 - Reserved
//

//
// INT4.5 - Reserved
//

//
// INT4.6 - Reserved
//

//
// INT4.7 - Reserved
//

//
// INT4.8 - Reserved
//

//
// PIE Group 5 - MUXed into CPU INT5
//

//
// INT5.1 - Reserved
//

//
// INT5.2 - Reserved
//

//
// INT5.3 - Reserved
//

//
// INT5.4 - Reserved
//

//
// INT5.5 - Reserved
//

//
// INT5.6 - Reserved
//

//
// INT5.7 - Reserved
//

//
// INT5.8 - Reserved
//

//
// PIE Group 6 - MUXed into CPU INT6
//

//
// SPIRXINTA_ISR - INT6.1 is SPI-A
//
interrupt void
SPIRXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPITXINTA_ISR - INT6.2 is SPI-A
//
interrupt void
SPITXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT6.3 - Reserved
//

//
// INT6.4 - Reserved
//

//
// INT6.5 - Reserved
//

//
// INT6.6 - Reserved
//

//
// INT6.7 - Reserved
//

//
// INT6.8 - Reserved
//

//
// PIE Group 7 - MUXed into CPU INT7
//

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - INT8.1 is I2C-A
//
interrupt void
I2CINT1A_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// I2CINT2A_ISR - INT8.2 is I2C-A
//
interrupt void
I2CINT2A_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT8.3 - Reserved
//

//
// INT8.4 - Reserved
//

//
// INT8.5 - Reserved
//

//
// INT8.6 - Reserved
//

//
// INT8.7 - Reserved
//

//
// INT8.8 - Reserved
//

//
// PIE Group 9 - MUXed into CPU INT9
//

//
// SCIRXINTA_ISR - INT9.1 is SCI-A
//
interrupt void
SCIRXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCITXINTA_ISR - INT9.2 is SCI-A
//
interrupt void
SCITXINTA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT9.3 - Reserved
//

//
// INT9.4 - Reserved
//

//
// INT9.5 - Reserved
//

//
// INT9.6 - Reserved
//

//
// INT9.7 - Reserved
//

//
// INT9.8 - Reserved
//

//
// PIE Group 10 - MUXed into CPU INT10
//

//
// ADCINT3_ISR - INT10.3 is ADC
//
interrupt void
ADCINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT4_ISR - INT10.4 is ADC
//
interrupt void
ADCINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT5_ISR - INT10.5 is ADC
//
interrupt void
ADCINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT6_ISR - INT10.6 is ADC
//
interrupt void
ADCINT6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT7_ISR - INT10.7 is ADC
//
interrupt void
ADCINT7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT8_ISR - INT10.8 is ADC
//
interrupt void
ADCINT8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 11 - MUXed into CPU INT11
//

//
// PIE Group 12 - MUXed into CPU INT12
//

//
// XINT3_ISR - INT12.1 is External interrupt 3
//
interrupt void
XINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT12.2 - Reserved
//

//
// INT12.3 - Reserved
//

//
// INT12.4 - Reserved
//

//
// INT12.5 - Reserved
//

//
// INT12.6 - Reserved
//

//
// INT12.7 - Reserved
//

//
// INT12.8 - Reserved
//

//
// Catch All Default ISRs:
//

//
// EMPTY_ISR - only does a return
//
interrupt void
EMPTY_ISR(void)
{

}

//
// PIE_RESERVED -  Reserved space.
//
interrupt void
PIE_RESERVED(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// rsvd_ISR - For test
//
interrupt void
rsvd_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of file
//

