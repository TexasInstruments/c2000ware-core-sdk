//###########################################################################
//
// FILE:    F2805x_DefaultIsr.c
//
// TITLE:   F2805x Device Default Interrupt Service Routines.
//
// DESCRIPTION:
//
// This file contains shell ISR routines for the 2805x PIE vector table.
// Typically these shell ISR routines can be used to populate the entire PIE
// vector table during device debug.  In this manner if an __interrupt is taken
// during firmware development, there will always be an ISR to catch it.
//
// As development progresses, these ISR routines can be eliminated and replaced
// with the user's own ISR routines for each __interrupt.  Since these shell
// ISRs include infinite loops they will typically not be included as-is in the
// final production firmware.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File

// Connected to INT13 of CPU (use MINT13 mask):
// ISR can be used by the user.
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void INT14_ISR(void)     // INT14 or CPU-Timer2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void DATALOG_ISR(void)   // Datalogging __interrupt
{
   // Insert ISR Code here

   // Next two lines for debug only to halt the processor here
   // Remove after inserting ISR Code
  asm ("      ESTOP0");
   for(;;);
}

__interrupt void RTOSINT_ISR(void)   // RTOS __interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void EMUINT_ISR(void)    // Emulation __interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void NMI_ISR(void)       // Non-maskable __interrupt
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void ILLEGAL_ISR(void)   // Illegal operation TRAP
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm("          ESTOP0");
  for(;;);

}

__interrupt void USER1_ISR(void)     // User Defined trap 1
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);

}

__interrupt void USER2_ISR(void)     // User Defined trap 2
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);

}

__interrupt void USER3_ISR(void)     // User Defined trap 3
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER4_ISR(void)     // User Defined trap 4
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER5_ISR(void)     // User Defined trap 5
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER6_ISR(void)     // User Defined trap 6
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER7_ISR(void)     // User Defined trap 7
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER8_ISR(void)     // User Defined trap 8
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER9_ISR(void)     // User Defined trap 9
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER10_ISR(void)    // User Defined trap 10
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER11_ISR(void)    // User Defined trap 11
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void USER12_ISR(void)     // User Defined trap 12
{
 // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
 asm ("      ESTOP0");
  for(;;);

}

// -----------------------------------------------------------
// PIE Group 1 - MUXed into CPU INT1
// -----------------------------------------------------------
// INT1.1
// ADC  (Can also be ISR for INT10.1 when enabled)
__interrupt void ADCINT1_ISR(void)
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code

    asm ("      ESTOP0");
    for(;;);

}

// INT1.2
// ADC (Can also be ISR for INT10.2 when enabled)
__interrupt void ADCINT2_ISR(void)
{

    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code

    asm("    ESTOP0");
    for(;;);

}

// INT1.3 - Reserved

// INT1.4
__interrupt void  XINT1_ISR(void)
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}

// INT1.5
__interrupt void  XINT2_ISR(void)
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);

}

// INT1.6
__interrupt void  ADCINT9_ISR(void)     // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT1.7
__interrupt void  TINT0_ISR(void)      // CPU-Timer 0
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT1.8
__interrupt void  WAKEINT_ISR(void)    // WD, LOW Power
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// -----------------------------------------------------------
// PIE Group 2 - MUXed into CPU INT2
// -----------------------------------------------------------

// INT2.1
__interrupt void EPWM1_TZINT_ISR(void)    // EPWM-1
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.2
__interrupt void EPWM2_TZINT_ISR(void)    // EPWM-2
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.3
__interrupt void EPWM3_TZINT_ISR(void)    // EPWM-3
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.4
__interrupt void EPWM4_TZINT_ISR(void)    // EPWM-4
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.5
__interrupt void EPWM5_TZINT_ISR(void)    // EPWM-5
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.6
__interrupt void EPWM6_TZINT_ISR(void)    // EPWM-6
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.7
__interrupt void EPWM7_TZINT_ISR(void)    // EPWM-7
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT2.8 - Reserved

// -----------------------------------------------------------
// PIE Group 3 - MUXed into CPU INT3
// -----------------------------------------------------------

// INT 3.1
__interrupt void EPWM1_INT_ISR(void)     // EPWM-1
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.2
__interrupt void EPWM2_INT_ISR(void)     // EPWM-2
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.3
__interrupt void EPWM3_INT_ISR(void)    // EPWM-3
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.4
__interrupt void EPWM4_INT_ISR(void)    // EPWM-4
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.5
__interrupt void EPWM5_INT_ISR(void)    // EPWM-5
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.5
__interrupt void EPWM6_INT_ISR(void)    // EPWM-6
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.5
__interrupt void EPWM7_INT_ISR(void)    // EPWM-7
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT3.8 - Reserved

// -----------------------------------------------------------
// PIE Group 4 - MUXed into CPU INT4
// -----------------------------------------------------------

// INT 4.1
__interrupt void ECAP1_INT_ISR(void)    // ECAP-1
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT4.2 - Reserved
// INT4.3 - Reserved
// INT4.4 - Reserved
// INT4.5 - Reserved
// INT4.6 - Reserved
// INT4.7 - Reserved
// INT4.8 - Reserved

// -----------------------------------------------------------
// PIE Group 5 - MUXed into CPU INT5
// -----------------------------------------------------------

// INT 5.1
__interrupt void EQEP1_INT_ISR(void)    // EQEP-1
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT5.2 - Reserved
// INT5.3 - Reserved
// INT5.4 - Reserved
// INT5.5 - Reserved
// INT5.6 - Reserved
// INT5.7 - Reserved
// INT5.8 - Reserved

// -----------------------------------------------------------
// PIE Group 6 - MUXed into CPU INT6
// -----------------------------------------------------------

// INT6.1
__interrupt void SPIRXINTA_ISR(void)    // SPI-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT6.2
__interrupt void SPITXINTA_ISR(void)     // SPI-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT6.3 - Reserved
// INT6.4 - Reserved
// INT6.5 - Reserved
// INT6.6 - Reserved
// INT6.7 - Reserved
// INT6.8 - Reserved

// -----------------------------------------------------------
// PIE Group 7 - MUXed into CPU INT7
// -----------------------------------------------------------

// -----------------------------------------------------------
// PIE Group 8 - MUXed into CPU INT8
// -----------------------------------------------------------

// INT8.1
__interrupt void I2CINT1A_ISR(void)     // I2C-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT8.2
__interrupt void I2CINT2A_ISR(void)     // I2C-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT8.3 - Reserved
// INT8.4 - Reserved

// INT8.5
__interrupt void SCIRXINTC_ISR(void)     // SCI-C
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT8.6
__interrupt void SCITXINTC_ISR(void)     // SCI-C
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT8.7 - Reserved
// INT8.8 - Reserved

// -----------------------------------------------------------
// PIE Group 9 - MUXed into CPU INT9
// -----------------------------------------------------------

// INT9.1
__interrupt void SCIRXINTA_ISR(void)     // SCI-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.2
__interrupt void SCITXINTA_ISR(void)     // SCI-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.3
__interrupt void SCIRXINTB_ISR(void)     // SCI-B
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.4
__interrupt void SCITXINTB_ISR(void)     // SCI-B
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.5
__interrupt void ECAN0INTA_ISR(void)  // eCAN-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.6
__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT9.7 - Reserved
// INT9.8 - Reserved

// -----------------------------------------------------------
// PIE Group 10 - MUXed into CPU INT10
// -----------------------------------------------------------

// INT10.1 - Reserved or ADCINT1_ISR
// INT10.2 - Reserved or ADCINT2_ISR

// INT10.3
__interrupt void ADCINT3_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT10.4
__interrupt void ADCINT4_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT10.5
__interrupt void ADCINT5_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT10.6
__interrupt void ADCINT6_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT10.7
__interrupt void ADCINT7_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT10.8
__interrupt void ADCINT8_ISR(void)    // ADC
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}


// -----------------------------------------------------------
// PIE Group 11 - MUXed into CPU INT11
// -----------------------------------------------------------

// INT11.1
__interrupt void CLA1_INT1_ISR(void)   // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code

    asm ("      ESTOP0");
    for(;;);
}

// INT11.2
__interrupt void CLA1_INT2_ISR(void)  // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code

    asm("    ESTOP0");
    for(;;);
}

// INT11.3
__interrupt void CLA1_INT3_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT11.4
__interrupt void CLA1_INT4_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT11.5
__interrupt void CLA1_INT5_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT11.6
__interrupt void CLA1_INT6_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT11.7
__interrupt void CLA1_INT7_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT11.8
__interrupt void CLA1_INT8_ISR(void)    // MCLA
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// -----------------------------------------------------------
// PIE Group 12 - MUXed into CPU INT12
// -----------------------------------------------------------

// INT12.1
__interrupt void XINT3_ISR(void)  // External __interrupt 3
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}
// INT12.2 - Reserved
// INT12.3 - Reserved
// INT12.4 - Reserved
// INT12.5 - Reserved
// INT12.6 - Reserved

// INT12.7
__interrupt void LVF_ISR(void)  // CLA1 - overflow
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

// INT12.8
__interrupt void LUF_ISR(void)  // CLA1 - underflow
{
    // Insert ISR Code here

    // To receive more __interrupts from this PIE group, acknowledge this
    // __interrupt PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm ("      ESTOP0");
    for(;;);
}

//---------------------------------------------------------------------------
// Catch All Default ISRs:
//

__interrupt void EMPTY_ISR(void)  // Empty ISR - only does a return.
{

}

__interrupt void PIE_RESERVED(void)  // Reserved space.  For test.
{
 asm ("      ESTOP0");
  for(;;);
}

__interrupt void rsvd_ISR(void)      // For test
{
 asm ("      ESTOP0");
  for(;;);
}

//
// End of file.
//

