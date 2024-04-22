//###########################################################################
//
// FILE:    SWPrioritizedDefaultIsr.c
//
// TITLE:   F2837xD Device Default Software Prioritized Interrupt Service
//          Routines.
//
//          This file is based on the standard SWPrioritizedDefaultIsr.c
//          The ISR routines have been modified slightly to provide a trace
//          mechanism used for this example
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F2837xD_SWPrioritizedIsrLevels.h"

//
// Globals
//
extern Uint16 ISRTrace[50];
extern Uint16 ISRTraceIndex;
Uint16 i; // Used for ISR delays

//
// Connected to INT13 of CPU (use MINT13 mask):
//
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
#if (INT13PL != 0)
__interrupt void TIMER1_ISR(void)     // INT13 or CPU-Timer1
{
     IER &= MINT13;                 // Set "global" priority
     EINT;

    //
    // Insert ISR Code here.......
    //

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
    __asm ("      ESTOP0");
     for(;;);
}
#endif

//
// Connected to INT14 of CPU (use MINT14 mask):
//
#if (INT14PL != 0)
__interrupt void TIMER2_ISR(void)     // CPU-Timer2
{
   IER &= MINT14;                  // Set "global" priority
   EINT;

    //
    // Insert ISR Code here.......
    //

   // Next two lines for debug only to halt the processor here
   // Remove after inserting ISR Code
  __asm ("      ESTOP0");
   for(;;);
}
#endif

//
// Connected to INT15 of CPU (use MINT15 mask):
//
#if (INT15PL != 0)
__interrupt void DATALOG_ISR(void)   // Datalogging interrupt
{
    IER &= MINT15;                 // Set "global" priority
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}
#endif

//
// Connected to INT16 of CPU (use MINT16 mask):
//
#if (INT16PL != 0)
__interrupt void RTOS_ISR(void)   // RTOS interrupt
{
    IER &= MINT16;                 // Set "global" priority
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}
#endif

//
// Connected to EMUINT of CPU (non-maskable):
//
__interrupt void EMU_ISR(void)    // Emulation interrupt
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to NMI of CPU (non-maskable):
//
__interrupt void NMI_ISR(void)      // Non-maskable interrupt
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to ITRAP of CPU (non-maskable):
//
__interrupt void ILLEGAL_ISR(void)   // Illegal operation TRAP
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER1 of CPU (non-maskable):
//
__interrupt void USER1_ISR(void)     // User Defined trap 1
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER2 of CPU (non-maskable):
//
__interrupt void USER2_ISR(void)     // User Defined trap 2
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER3 of CPU (non-maskable):
//
__interrupt void USER3_ISR(void)     // User Defined trap 3
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER4 of CPU (non-maskable):
//
__interrupt void USER4_ISR(void)     // User Defined trap 4
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER5 of CPU (non-maskable):
//
__interrupt void USER5_ISR(void)     // User Defined trap 5
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER6 of CPU (non-maskable):
//
__interrupt void USER6_ISR(void)     // User Defined trap 6
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER7 of CPU (non-maskable):
//
__interrupt void USER7_ISR(void)     // User Defined trap 7
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER8 of CPU (non-maskable):
//
__interrupt void USER8_ISR(void)     // User Defined trap 8
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER9 of CPU (non-maskable):
//
__interrupt void USER9_ISR(void)     // User Defined trap 9
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER10 of CPU (non-maskable):
//
__interrupt void USER10_ISR(void)    // User Defined trap 10
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER11 of CPU (non-maskable):
//
__interrupt void USER11_ISR(void)    // User Defined trap 11
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

//
// Connected to USER12 of CPU (non-maskable):
//
__interrupt void USER12_ISR(void)     // User Defined trap 12
{
    EINT;

    //
    // Insert ISR Code here.......
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
   __asm ("      ESTOP0");
    for(;;);
}

// -----------------------------------------------------------
// PIE Group 1 - MUXed into CPU INT1
// -----------------------------------------------------------
//
// Connected to PIEIER1_1 (use MINT1 and MG1_1 masks):
//
#if (G1_1PL != 0)
__interrupt void ADCA1_ISR( void )     // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ADCB1_ISR( void )    // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ADCC1_ISR( void )    // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  XINT1_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  XINT2_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER1_6 (use MINT1 and MG1_6 masks):
//
#if (G1_6PL != 0)
__interrupt void  ADCD1_ISR(void)     // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0016;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER1_7 (use MINT1 and MG1_7 masks):
//
#if (G1_7PL != 0)
__interrupt void  TIMER0_ISR(void)      // CPU-Timer 0
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  WAKE_ISR(void)      // WD/LPM
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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

//
// Connected to PIEIER1_13 (use MINT1 and MG1_13 masks):
//
#if (G1_13PL != 0)
__interrupt void  IPC0_ISR(void)      // IPC0
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_13;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x001D;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_14 (use MINT1 and MG1_14 masks):
//
#if (G1_14PL != 0)
__interrupt void  IPC1_ISR(void)      // IPC1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x001E;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_15 (use MINT1 and MG1_15 masks):
//
#if (G1_15PL != 0)
__interrupt void  IPC2_ISR(void)      // IPC2
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x001F;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER1_16 (use MINT1 and MG1_16 masks):
//
#if (G1_16PL != 0)
__interrupt void  IPC3_ISR(void)      // IPC3
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;                         // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG1_16;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0020;
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
__interrupt void EPWM1_TZ_ISR(void)    // ePWM1 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM2_TZ_ISR(void)    // ePWM2 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM3_TZ_ISR(void)    // ePWM3 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM4_TZ_ISR(void)    // ePWM4 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_4;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM5_TZ_ISR(void)    // ePWM5 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_5;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM6_TZ_ISR(void)    // ePWM6 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_6;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM7_TZ_ISR(void)    // ePWM7 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_7;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM8_TZ_ISR(void)    // ePWM8 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_8;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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

//
// Connected to PIEIER2_9 (use MINT2 and MG2_9 masks):
//
#if (G2_9PL != 0)
__interrupt void EPWM9_TZ_ISR(void)    // ePWM9 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_9;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0029;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_10 (use MINT2 and MG2_10 masks):
//
#if (G2_10PL != 0)
__interrupt void EPWM10_TZ_ISR(void)    // ePWM10 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_10;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x002A;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_11 (use MINT2 and MG2_11 masks):
//
#if (G2_11PL != 0)
__interrupt void EPWM11_TZ_ISR(void)    // ePWM11 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_11;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x002B;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER2_12 (use MINT2 and MG2_12 masks):
//
#if (G2_12PL != 0)
__interrupt void EPWM12_TZ_ISR(void)    // ePWM12 Trip Zone
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER    &= MINT2;                          // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG2_12;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x002C;
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
__interrupt void EPWM1_ISR(void)     // ePWM1 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM2_ISR(void)     // ePWM2 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM3_ISR(void)     // ePWM3 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                          // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM4_ISR(void)     // ePWM4 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM5_ISR(void)     // ePWM5 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM6_ISR(void)     // ePWM6 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM7_ISR(void)     // ePWM7 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EPWM8_ISR(void)     // ePWM8 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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

//
// Connected to PIEIER3_9 (use MINT3 and MG3_9 masks):
//
#if (G3_9PL != 0)
__interrupt void EPWM9_ISR(void)     // ePWM9 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0039;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_10 (use MINT3 and MG3_10 masks):
//
#if (G3_10PL != 0)
__interrupt void EPWM10_ISR(void)     // ePWM10 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_10;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x003A;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_11 (use MINT3 and MG3_11 masks):
//
#if (G3_11PL != 0)
__interrupt void EPWM11_ISR(void)     // ePWM11 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x003B;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER3_12 (use MINT3 and MG3_12 masks):
//
#if (G3_12PL != 0)
__interrupt void EPWM12_ISR(void)     // ePWM12 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER    &= MINT3;                         // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG3_12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x003C;
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
__interrupt void ECAP1_ISR(void)     // eCAP1 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ECAP2_ISR(void)     // eCAP2 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ECAP3_ISR(void)     // eCAP3 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ECAP4_ISR(void)     // eCAP4 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ECAP5_ISR(void)     // eCAP5 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ECAP6_ISR(void)     // eCAP6 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER    &= MINT4;                         // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG4_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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

// -----------------------------------------------------------
// PIE Group 5 - MUXed into CPU INT5
// -----------------------------------------------------------

//
// Connected to PIEIER5_1 (use MINT5 and MG5_1 masks):
//
#if (G5_1PL != 0)
__interrupt void EQEP1_ISR(void)     // eQEP1 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void EQEP2_ISR(void)     // eQEP2 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER5_3 (use MINT5 and MG5_3 masks):
//
#if (G5_3PL != 0)
__interrupt void EQEP3_ISR(void)     // eQEP3 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0053;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_5 (use MINT5 and MG5_5 masks):
//
#if (G5_5PL != 0)
__interrupt void CLB1_ISR(void)     // CLB1 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0055;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_6 (use MINT5 and MG5_6 masks):
//
#if (G5_6PL != 0)
__interrupt void CLB2_ISR(void)     // CLB2 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0056;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_7 (use MINT5 and MG5_7 masks):
//
#if (G5_7PL != 0)
__interrupt void CLB3_ISR(void)     // CLB3 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0057;
    ISRTraceIndex++;

}
#endif


//
// Connected to PIEIER5_8 (use MINT5 and MG5_8 masks):
//
#if (G5_8PL != 0)
__interrupt void CLB4_ISR(void)     // CLB4 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0058;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER5_9 (use MINT5 and MG5_9 masks):
//
#if (G5_9PL != 0)
__interrupt void SD1_ISR(void)     // SD1 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER5_10 (use MINT5 and MG5_10 masks):
//
#if (G5_10PL != 0)
__interrupt void SD2_ISR(void)     // SD2 Interrupt
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER    &= MINT5;                         // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG5_10;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x005A;
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
__interrupt void SPIA_RX_ISR(void)    // SPI-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void SPIA_TX_ISR(void)     // SPI-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void SPIB_RX_ISR(void)    // SPI-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void SPIB_TX_ISR(void)     // SPI-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
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

//
// Connected to PIEIER6_5 (use MINT6 and MG6_5 masks):
//
#if (G6_5PL != 0)
__interrupt void MCBSPA_RX_ISR(void)     // McBSP-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_5;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x0065;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_6 (use MINT6 and MG6_6 masks):
//
#if (G6_6PL != 0)
__interrupt void MCBSPA_TX_ISR(void)     // McBSP-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_6;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x0066;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_7 (use MINT6 and MG6_7 masks):
//
#if (G6_7PL != 0)
__interrupt void MCBSPB_RX_ISR(void)     // McBSP-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_7;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x0067;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_8 (use MINT6 and MG6_8 masks):
//
#if (G6_8PL != 0)
__interrupt void MCBSPB_TX_ISR(void)     // McBSP-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_8;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x0068;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_9 (use MINT6 and MG6_9 masks):
//
#if (G6_9PL != 0)
__interrupt void SPIC_RX_ISR(void)     // SPIC_RX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_9;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x0069;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER6_10 (use MINT6 and MG6_10 masks):
//
#if (G6_10PL != 0)
__interrupt void SPIC_TX_ISR(void)     // SPIC_TX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER    &= MINT6;                         // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG6_10;   // Set "group"  priority
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
    ISRTrace[ISRTraceIndex] = 0x006A;
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
__interrupt void DMA_CH1_ISR(void)    // DMA Channel 1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void DMA_CH2_ISR(void)    // DMA Channel 2
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void DMA_CH3_ISR(void)    // DMA Channel 3
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void DMA_CH4_ISR(void)    // DMA Channel 4
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void DMA_CH5_ISR(void)    // DMA Channel 5
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void DMA_CH6_ISR(void)    // DMA Channel 6
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER    &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG7_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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


// -----------------------------------------------------------
// PIE Group 8 - MUXed into CPU INT8
// -----------------------------------------------------------

//
// Connected to PIEIER8_1 (use MINT8 and MG8_1 masks):
//
#if (G8_1PL != 0)
__interrupt void I2CA_ISR(void)    // I2C-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void I2CA_FIFO_ISR(void)     // I2C-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER8_3 (use MINT8 and MG8_3 masks):
//
#if (G8_3PL != 0)
__interrupt void I2CB_ISR(void)    // I2C-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0083;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_4 (use MINT8 and MG8_4 masks):
//
#if (G8_4PL != 0)
__interrupt void I2CB_FIFO_ISR(void)     // I2C-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0084;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_5 (use MINT8 and MG8_5 masks):
//
#if (G8_5PL != 0)
__interrupt void SCIC_RX_ISR(void)    // SCI-C RX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0085;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_6 (use MINT8 and MG8_6 masks):
//
#if (G8_6PL != 0)
__interrupt void SCIC_TX_ISR(void)     // SCI-C TX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0086;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_7 (use MINT8 and MG8_7 masks):
//
#if (G8_7PL != 0)
__interrupt void SCID_RX_ISR(void)    // SCI-D RX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0087;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER8_8 (use MINT8 and MG8_8 masks):
//
#if (G8_8PL != 0)
__interrupt void SCID_TX_ISR(void)     // SCI-D TX
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0088;
    ISRTraceIndex++;

}
#endif

#ifdef CPU1
//
// Connected to PIEIER8_15 (use MINT8 and MG8_15 masks):
//
#if (G8_15PL != 0)
__interrupt void UPPA_ISR(void)     // uPP-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER    &= MINT8;                         // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG8_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x008F;
    ISRTraceIndex++;

}
#endif
#endif // CPU1
// -----------------------------------------------------------
// PIE Group 9 - MUXed into CPU INT9
// -----------------------------------------------------------

//
// Connected to PIEIER9_1 (use MINT9 and MG9_1 masks):
//
#if (G9_1PL != 0)
__interrupt void SCIA_RX_ISR(void)     // SCI-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                          // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void SCIA_TX_ISR(void)     // SCI-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  SCIB_RX_ISR(void)     // SCI - B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  SCIB_TX_ISR(void)     // SCI - B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CANA0_ISR(void)    // CAN-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CANA1_ISR(void)     // CAN-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CANB0_ISR(void)    // CAN-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_7;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CANB1_ISR(void)     // CAN-B
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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


#ifdef CPU1
//
// Connected to PIEIER9_15 (use MINT9 and MG9_15 masks):
//
#if (G9_15PL != 0)
__interrupt void USBA_ISR(void)     // USB-A
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER    &= MINT9;                         // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG9_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x009F;
    ISRTraceIndex++;

}
#endif
#endif // CPU1
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
__interrupt void ADCA_EVT_ISR( void )     // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void ADCA2_ISR( void )    // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_2; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCA3_ISR(void)  // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_3; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCA4_ISR(void)  // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                           // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCB_EVT_ISR(void)  // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_5;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCB2_ISR(void)     // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_6; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCB3_ISR(void)      // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_7; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  ADCB4_ISR(void)      // ADC
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_9;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_10;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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

//
// Connected to PIEIER10_13 (use MINT10 and MG10_13 masks):
//
#if (G10_13PL != 0)
interrupt void ADCD_EVT_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_13;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x010D;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_14 (use MINT10 and MG10_14 masks):
//
#if (G10_14PL != 0)
interrupt void ADCD2_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x010E;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_15 (use MINT10 and MG10_15 masks):
//
#if (G10_15PL != 0)
interrupt void ADCD3_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x010F;
    ISRTraceIndex++;
}
#endif

//
// Connected to PIEIER10_16 (use MINT10 and MG10_16 masks):
//
#if (G10_16PL != 0)
interrupt void ADCD4_ISR(void)
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER    &= MINT10;                         // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG10_16;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0110;
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
__interrupt void CLA1_1_ISR( void )     // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_1; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CLA1_2_ISR( void )    // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_2; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_3_ISR(void)  // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_3; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_4_ISR(void)  // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                           // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_4;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_5_ISR(void)  // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_5; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_6_ISR(void)     // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_6; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_7_ISR(void)      // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_7; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void  CLA1_8_ISR(void)      // CLA1
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER    &= MINT11;                         // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG11_8;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void XINT3_ISR(void)     // XINT3
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_1;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void XINT4_ISR(void)     // XINT4
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_2;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void XINT5_ISR(void)     // XINT5
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_3;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER12_6 (use MINT12 and MG12_6 masks):
//
#if (G12_6PL != 0)
__interrupt void VCU_ISR(void)     // VCU
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_6;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0126;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_7 (use MINT12 and MG12_7 masks):
//
#if (G12_7PL != 0)
__interrupt void FPU_OVERFLOW_ISR(void)     // CLA1 - Overflow
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_7;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void FPU_UNDERFLOW_ISR(void)     // CLA1 - Underflow
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_8;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER12_9 (use MINT12 and MG12_9 masks):
//
#if (G12_9PL != 0)
__interrupt void EMIF_ERROR_ISR(void)     // EMIF_ERROR
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_9;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x0129;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_10 (use MINT12 and MG12_10 masks):
//
#if (G12_10PL != 0)
__interrupt void RAM_CORRECTABLE_ERROR_ISR(void)     // RAM_CORRECTABLE_ERROR
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_10;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void FLASH_CORRECTABLE_ERROR_ISR(void)     // FLASH_CORRECTABLE_ERROR
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_11;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void RAM_ACCESS_VIOLATION_ISR(void)     // RAM_ACCESS_VIOLATION
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_12;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void SYS_PLL_SLIP_ISR(void)     // SYS_PLL_SLIP
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_13;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
// Connected to PIEIER12_14 (use MINT12 and MG12_14 masks):
//
#if (G12_14PL != 0)
__interrupt void AUX_PLL_SLIP_ISR(void)     // AUX_PLL_SLIP
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_14;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
    ISRTrace[ISRTraceIndex] = 0x012E;
    ISRTraceIndex++;

}
#endif

//
// Connected to PIEIER12_15 (use MINT12 and MG12_15 masks):
//
#if (G12_15PL != 0)
__interrupt void CLA_OVERFLOW_ISR(void)     // CLA_OVERFLOW
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_15;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void CLA_UNDERFLOW_ISR(void)     // CLA_UNDERFLOW
{
    // Set interrupt priority:
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER    &= MINT12;                          // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG12_16;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.......
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
__interrupt void PIE_RESERVED_ISR(void)  // Reserved space.  For test.
{
 __asm ("      ESTOP0");
  for(;;);
}

//
// INT_NOTUSED_ISR - Unused ISR
//
__interrupt void INT_NOTUSED_ISR(void)  // Reserved space.  For test.
{
 __asm ("      ESTOP0");
  for(;;);
}

//
// rsvd_ISR - Reserved ISR
//
__interrupt void rsvd_ISR(void)      // For test
{
 __asm ("      ESTOP0");
  for(;;);
}

//
// End of file
//
