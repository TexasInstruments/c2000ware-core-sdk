//###########################################################################
//
// FILE:    f28004x_sw_prioritized_defaultisr.c
//
// TITLE:   Default Software Prioritized Interrupt Service Routines.
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"
#include "f28004x_sw_prioritized_isr_levels.h"

//
// Globals
//
extern uint16_t ISRTrace[50];
extern uint16_t ISRTraceIndex;
uint16_t i; // Used for ISR delays

//
// Connected to INT13 of CPU (use MINT13 mask):
//
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
#if (INT13PL != 0)
__interrupt void TIMER1_ISR(void)
{
     IER &= MINT13;                 // Set "global" priority
     EINT;

    //
    // Insert ISR Code here
    //

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
    ESTOP0;
     for(;;);
}
#endif

//
// Connected to INT14 of CPU (use MINT14 mask):
//
#if (INT14PL != 0)
__interrupt void TIMER2_ISR(void)
{
    IER &= MINT14;                  // Set "global" priority
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    ESTOP0;
    for(;;);
}
#endif

//
// Connected to INT15 of CPU (use MINT15 mask):
//
#if (INT15PL != 0)
__interrupt void DATALOG_ISR(void)
{
    IER &= MINT15;                 // Set "global" priority
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}
#endif

//
// Connected to INT16 of CPU (use MINT16 mask):
//
#if (INT16PL != 0)
__interrupt void RTOS_ISR(void)
{
    IER &= MINT16;                 // Set "global" priority
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}
#endif

//
// Connected to EMUINT of CPU (non-maskable):
//
__interrupt void EMU_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to NMI of CPU (non-maskable):
//
__interrupt void NMI_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to ITRAP of CPU (non-maskable):
//
__interrupt void ILLEGAL_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER1 of CPU (non-maskable):
//
__interrupt void USER1_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER2 of CPU (non-maskable):
//
__interrupt void USER2_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER3 of CPU (non-maskable):
//
__interrupt void USER3_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER4 of CPU (non-maskable):
//
__interrupt void USER4_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER5 of CPU (non-maskable):
//
__interrupt void USER5_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER6 of CPU (non-maskable):
//
__interrupt void USER6_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER7 of CPU (non-maskable):
//
__interrupt void USER7_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER8 of CPU (non-maskable):
//
__interrupt void USER8_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER9 of CPU (non-maskable):
//
__interrupt void USER9_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER10 of CPU (non-maskable):
//
__interrupt void USER10_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER11 of CPU (non-maskable):
//
__interrupt void USER11_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

//
// Connected to USER12 of CPU (non-maskable):
//
__interrupt void USER12_ISR(void)
{
    EINT;

    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   ESTOP0;
    for(;;);
}

// -----------------------------------------------------------
// PIE Group 1 - MUXed into CPU INT1
// -----------------------------------------------------------
//
// Connected to PIEIER1_1 (use MINT1 and MG1_1 masks):
//
#if (G1_1PL != 0)
__interrupt void ADCA1_ISR(void)     // ADC
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0011;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER1_2 (use MINT1 and MG1_2 masks):
//
#if (G1_2PL != 0)
__interrupt void ADCB1_ISR(void)    // ADC
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0012;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER1_3 (use MINT1 and MG1_3 masks):
//
#if (G1_3PL != 0)
__interrupt void ADCC1_ISR(void)    // ADC
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0013;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER1_4 (use MINT1 and MG1_4 masks):
//
#if (G1_4PL != 0)
__interrupt void XINT1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //

     __asm("      NOP");

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0014;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_5 (use MINT1 and MG15 masks):
//
#if (G1_5PL != 0)
__interrupt void XINT2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0015;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_7 (use MINT1 and MG1_7 masks):
//
#if (G1_7PL != 0)
__interrupt void TIMER0_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0017;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_8 (use MINT1 and MG1_8 masks):
//
#if (G1_8PL != 0)
__interrupt void WAKE_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0018;
    ISRTraceIndex++;
}
#endif

// -----------------------------------------------------------
// PIE Group 2 - MUXed into CPU INT2
// -----------------------------------------------------------

//
// Connected to PIEIER2_1 (use MINT2 and MG2_1 masks):
//
#if (G2_1PL != 0)
__interrupt void EPWM1_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //Add ISR to Trace
    ISRTrace[ISRTraceIndex] = 0x0021;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER2_2 (use MINT2 and MG2_2 masks):
//
#if (G2_2PL != 0)
__interrupt void EPWM2_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0022;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_3 (use MINT2 and MG2_3 masks):
//
#if (G2_3PL != 0)
__interrupt void EPWM3_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0023;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_4 (use MINT2 and MG2_4 masks):
//
#if (G2_4PL != 0)
__interrupt void EPWM4_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_4;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0024;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_5 (use MINT2 and MG2_5 masks):
//
#if (G2_5PL != 0)
__interrupt void EPWM5_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_5;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0025;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_6 (use MINT2 and MG2_6 masks):
//
#if (G2_6PL != 0)
__interrupt void EPWM6_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_6;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0026;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_7 (use MINT2 and MG2_7 masks):
//
#if (G2_7PL != 0)
__interrupt void EPWM7_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_7;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0027;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_8 (use MINT2 and MG2_8 masks):
//
#if (G2_8PL != 0)
__interrupt void EPWM8_TZ_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_8;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0028;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 3 - MUXed into CPU INT3
// -----------------------------------------------------------

//
// Connected to PIEIER3_1 (use MINT3 and MG3_1 masks):
//
#if (G3_1PL != 0)
__interrupt void EPWM1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0031;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER3_2 (use MINT3 and MG3_2 masks):
//
#if (G3_2PL != 0)
__interrupt void EPWM2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0032;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_3 (use MINT3 and MG3_3 masks):
//
#if (G3_3PL != 0)
__interrupt void EPWM3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                          // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0033;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_4 (use MINT3 and MG3_4 masks):
//
#if (G3_4PL != 0)
__interrupt void EPWM4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0034;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_5 (use MINT3 and MG3_5 masks):
//
#if (G3_5PL != 0)
__interrupt void EPWM5_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0035;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_6 (use MINT3 and MG3_6 masks):
//
#if (G3_6PL != 0)
__interrupt void EPWM6_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0036;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_7 (use MINT3 and MG3_7 masks):
//
#if (G3_7PL != 0)
__interrupt void EPWM7_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0037;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_8 (use MINT3 and MG3_8 masks):
//
#if (G3_8PL != 0)
__interrupt void EPWM8_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0038;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 4 - MUXed into CPU INT4
// -----------------------------------------------------------

//
// Connected to PIEIER4_1 (use MINT4 and MG4_1 masks):
//
#if (G4_1PL != 0)
__interrupt void ECAP1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0041;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_2 (use MINT4 and MG4_2 masks):
//
#if (G4_2PL != 0)
__interrupt void ECAP2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0042;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_3 (use MINT4 and MG4_3 masks):
//
#if (G4_3PL != 0)
__interrupt void ECAP3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0043;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_4 (use MINT4 and MG4_4 masks):
//
#if (G4_4PL != 0)
__interrupt void ECAP4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0044;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_5 (use MINT4 and MG4_5 masks):
//
#if (G4_5PL != 0)
__interrupt void ECAP5_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0045;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_6 (use MINT4 and MG4_6 masks):
//
#if (G4_6PL != 0)
__interrupt void ECAP6_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0046;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_7 (use MINT4 and MG4_7 masks):
//
#if (G4_7PL != 0)
__interrupt void ECAP7_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0047;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_14 (use MINT4 and MG4_14 masks):
//
#if (G4_14PL != 0)
__interrupt void ECAP6_2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x004E;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER4_15 (use MINT4 and MG4_15 masks):
//
#if (G4_14PL != 0)
__interrupt void ECAP7_2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x004F;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 5 - MUXed into CPU INT5
// -----------------------------------------------------------

//
// Connected to PIEIER5_1 (use MINT5 and MG5_1 masks):
//
#if (G5_1PL != 0)
__interrupt void EQEP1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0051;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_2 (use MINT5 and MG5_2 masks):
//
#if (G5_2PL != 0)
__interrupt void EQEP2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0052;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_9 (use MINT5 and MG5_9 masks):
//
#if (G5_9PL != 0)
__interrupt void SD1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0059;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_13 (use MINT5 and MG5_13 masks):
//
#if (G5_13PL != 0)
__interrupt void SD1DR1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_13;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x005D;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_14 (use MINT5 and MG5_14 masks):
//
#if (G5_14PL != 0)
__interrupt void SD1DR2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x005E;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_15 (use MINT5 and MG5_15 masks):
//
#if (G5_15PL != 0)
__interrupt void SD1DR3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x005F;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_16 (use MINT5 and MG5_16 masks):
//
#if (G5_16PL != 0)
__interrupt void SD1DR4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_16;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0060;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 6 - MUXed into CPU INT6
// -----------------------------------------------------------

//
// Connected to PIEIER6_1 (use MINT6 and MG6_1 masks):
//
#if (G6_1PL != 0)
__interrupt void SPIA_RX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0061;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_2 (use MINT6 and MG6_2 masks):
//
#if (G6_2PL != 0)
__interrupt void SPIA_TX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0062;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_3 (use MINT6 and MG6_3 masks):
//
#if (G6_3PL != 0)
__interrupt void SPIB_RX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0063;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_4 (use MINT6 and MG6_4 masks):
//
#if (G6_4PL != 0)
__interrupt void SPIB_TX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0064;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 7 - MUXed into CPU INT7
// -----------------------------------------------------------

//
// Connected to PIEIER7_1 (use MINT7 and MG7_1 masks):
//
#if (G7_1PL != 0)
__interrupt void DMA_CH1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0071;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_2 (use MINT7 and MG7_2 masks):
//
#if (G7_2PL != 0)
__interrupt void DMA_CH2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0072;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_3 (use MINT7 and MG7_3 masks):
//
#if (G7_3PL != 0)
__interrupt void DMA_CH3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0073;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_4 (use MINT7 and MG7_4 masks):
//
#if (G7_4PL != 0)
__interrupt void DMA_CH4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0074;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_5 (use MINT7 and MG7_5 masks):
//
#if (G7_5PL != 0)
__interrupt void DMA_CH5_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0075;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_6 (use MINT7 and MG7_6 masks):
//
#if (G7_6PL != 0)
__interrupt void DMA_CH6_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0076;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_11 (use MINT7 and MG7_11 masks):
//
#if (G7_11PL != 0)
__interrupt void FSITXA1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x007B;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_12 (use MINT7 and MG7_12 masks):
//
#if (G7_12PL != 0)
__interrupt void FSITXA2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x007C;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_13 (use MINT7 and MG7_13 masks):
//
#if (G7_13PL != 0)
__interrupt void FSIRXA1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_13;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x007D;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_14 (use MINT7 and MG7_14 masks):
//
#if (G7_14PL != 0)
__interrupt void FSIRXA2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x007E;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER7_15 (use MINT7 and MG7_15 masks):
//
#if (G7_15PL != 0)
__interrupt void CLA1PROMCRC_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x007F;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 8 - MUXed into CPU INT8
// -----------------------------------------------------------

//
// Connected to PIEIER8_1 (use MINT8 and MG8_1 masks):
//
#if (G8_1PL != 0)
__interrupt void I2CA_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0081;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_2 (use MINT8 and MG8_2 masks):
//
#if (G8_2PL != 0)
__interrupt void I2CA_FIFO_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0082;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_9 (use MINT8 and MG8_9 masks):
//
#if (G8_9PL != 0)
__interrupt void LINA_0_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0089;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_10 (use MINT8 and MG8_10 masks):
//
#if (G8_10PL != 0)
__interrupt void LINA_1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_10;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x008A;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_13 (use MINT8 and MG8_13 masks):
//
#if (G8_13PL != 0)
__interrupt void PMBUSA_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_13;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x008D;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 9 - MUXed into CPU INT9
// -----------------------------------------------------------

//
// Connected to PIEIER9_1 (use MINT9 and MG9_1 masks):
//
#if (G9_1PL != 0)
__interrupt void SCIA_RX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                          // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0091;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_2 (use MINT9 and MG9_2 masks):
//
#if (G9_2PL != 0)
__interrupt void SCIA_TX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0092;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_3 (use MINT9 and MG9_3 masks):
//
#if (G9_3PL != 0)
__interrupt void SCIB_RX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0093;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_4 (use MINT9 and MG9_4 masks):
//
#if (G9_4PL != 0)
__interrupt void SCIB_TX_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0094;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_5 (use MINT9 and MG9_5 masks):
//
#if (G9_5PL != 0)
__interrupt void CANA0_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0095;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_6 (use MINT9 and MG9_6 masks):
//
#if (G9_6PL != 0)
__interrupt void CANA1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0096;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_7 (use MINT9 and MG9_7 masks):
//
#if (G9_7PL != 0)
__interrupt void CANB0_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0097;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER9_8 (use MINT9 and MG9_8 masks):
//
#if (G9_8PL != 0)
__interrupt void CANB1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0098;
    ISRTraceIndex++;

}
#endif

// -----------------------------------------------------------
// PIE Group 10 - MUXed into CPU INT10
// -----------------------------------------------------------
/* Uncomment the below if ADCA_EVT_ISR and ADCA1_ISR in the 10.1 and 10.2
   PIE interrupt spaces are enabled. Then comment out the equivalent
   1.1 and 1.2 interrupt service routines. */

//
// Connected to PIEIER10_1 (use MINT10 and MG10_1 masks):
//
#if (G10_1PL != 0)
__interrupt void ADCA_EVT_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0101;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER10_2 (use MINT10 and MG10_2 masks):
//
#if (G10_2PL != 0)
__interrupt void ADCA2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_2; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0102;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER10_3 (use MINT10 and MG10_3 masks):
//
#if (G10_3PL != 0)
__interrupt void ADCA3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_3; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //

     __asm("      NOP");

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0103;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_4 (use MINT10 and MG10_4 masks):
//
#if (G10_4PL != 0)
__interrupt void ADCA4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                           // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //

     __asm("      NOP");

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0104;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_5 (use MINT10 and MG10_5 masks):
//
#if (G10_5PL != 0)
__interrupt void ADCB_EVT_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0105;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_6 (use MINT10 and MG10_6 masks):
//
#if (G10_6PL != 0)
__interrupt void ADCB2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_6; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
   for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0106;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER10_7 (use MINT10 and MG10_7 masks):
//
#if (G10_7PL != 0)
__interrupt void ADCB3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_7; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0107;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_8 (use MINT10 and MG10_8 masks):
//
#if (G10_8PL != 0)
__interrupt void ADCB4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0108;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_9 (use MINT10 and MG10_9 masks):
//
#if (G10_9PL != 0)
interrupt void ADCC_EVT_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0109;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_10 (use MINT10 and MG10_10 masks):
//
#if (G10_10PL != 0)
interrupt void ADCC2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_10;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x010A;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_11 (use MINT10 and MG10_11 masks):
//
#if (G10_11PL != 0)
interrupt void ADCC3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x010B;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_12 (use MINT10 and MG10_12 masks):
//
#if (G10_12PL != 0)
interrupt void ADCC4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x010C;
    ISRTraceIndex++;
}
#endif

// -----------------------------------------------------------
// PIE Group 11 - MUXed into CPU INT11
// -----------------------------------------------------------

//
// Connected to PIEIER11_1 (use MINT11 and MG11_1 masks):
//
#if (G11_1PL != 0)
__interrupt void CLA1_1_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_1; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0111;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER11_2 (use MINT11 and MG11_2 masks):
//
#if (G11_2PL != 0)
__interrupt void CLA1_2_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_2; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0112;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER11_3 (use MINT11 and MG11_3 masks):
//
#if (G11_3PL != 0)
__interrupt void CLA1_3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_3; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //

     __asm("      NOP");

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0113;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER11_4 (use MINT11 and MG11_4 masks):
//
#if (G11_4PL != 0)
__interrupt void CLA1_4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                           // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //

     __asm("      NOP");

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0114;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER11_5 (use MINT11 and MG11_5 masks):
//
#if (G11_5PL != 0)
__interrupt void CLA1_5_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_5; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0115;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER11_6 (use MINT11 and MG11_6 masks):
//
#if (G11_6PL != 0)
__interrupt void CLA1_6_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_6; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
   for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0116;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER11_7 (use MINT11 and MG11_7 masks):
//
#if (G11_7PL != 0)
__interrupt void CLA1_7_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_7; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0117;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER11_8 (use MINT11 and MG11_8 masks):
//
#if (G11_8PL != 0)
__interrupt void CLA1_8_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0118;
    ISRTraceIndex++;
}
#endif

// -----------------------------------------------------------
// PIE Group 12 - MUXed into CPU INT12
// -----------------------------------------------------------

//
// Connected to PIEIER12_1 (use MINT12 and MG12_1 masks):
//
#if (G12_1PL != 0)
__interrupt void XINT3_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0121;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_2 (use MINT12 and MG12_2 masks):
//
#if (G12_2PL != 0)
__interrupt void XINT4_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0122;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_3 (use MINT12 and MG12_3 masks):
//
#if (G12_3PL != 0)
__interrupt void XINT5_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0123;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_7 (use MINT12 and MG12_7 masks):
//
#if (G12_7PL != 0)
__interrupt void FPU_OVERFLOW_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_7;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0127;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_8 (use MINT12 and MG12_8 masks):
//
#if (G12_8PL != 0)
__interrupt void FPU_UNDERFLOW_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_8;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0128;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_10 (use MINT12 and MG12_10 masks):
//
#if (G12_10PL != 0)
__interrupt void RAM_CORRECTABLE_ERROR_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_10;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x012A;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_11 (use MINT12 and MG12_11 masks):
//
#if (G12_11PL != 0)
__interrupt void FLASH_CORRECTABLE_ERROR_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_11;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x012B;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_12 (use MINT12 and MG12_12 masks):
//
#if (G12_12PL != 0)
__interrupt void RAM_ACCESS_VIOLATION_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_12;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x012C;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_13 (use MINT12 and MG12_13 masks):
//
#if (G12_13PL != 0)
__interrupt void SYS_PLL_SLIP_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_13;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x012D;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_15 (use MINT12 and MG12_15 masks):
//
#if (G12_15PL != 0)
__interrupt void CLA_OVERFLOW_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_15;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x012F;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_16 (use MINT12 and MG12_16 masks):
//
#if (G12_16PL != 0)
__interrupt void CLA_UNDERFLOW_ISR(void)
{
    // Set interrupt priority:
    volatile uint16_t TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_16;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    //  Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0130;
    ISRTraceIndex++;

}
#endif

//
// Catch All Default ISRs:
//

//
// PIE_RESERVED_ISR - Reserved PIE ISR
//
__interrupt void PIE_RESERVED_ISR(void)
{
    ESTOP0;
    for(;;);
}

//
// NOTUSED_ISR - Unused ISR
//
__interrupt void NOTUSED_ISR(void)
{
    ESTOP0;
    for(;;);
}

//
// End of file
//
