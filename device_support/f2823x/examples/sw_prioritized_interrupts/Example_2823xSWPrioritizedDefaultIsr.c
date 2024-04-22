//###########################################################################
//
// FILE:    Example_2823xSWPrioritizedDefaultIsr.c
//
// TITLE:   DSP2823x Device Default Software Prioritized Interrupt 
//          Service Routines.
//          This file is based on the standard 
//          DSP2823x_SWPrioritizedDefaultIsr.c. The ISR routines have been 
//          modified slightly to provide a trace mechanism used for this 
//          example
//
//###########################################################################
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2823x_SWPrioritizedIsrLevels.h"

//
// Defined in the Example_28xSWPrioritizedInterrupts.c file
// for this example only
//
extern Uint16 ISRTrace[50];
extern Uint16 ISRTraceIndex;

//
// Global used for ISR delays
//
Uint16 i;

//
// INT13_ISR - INT13 or CPU-Timer1 is connected to INT13 of CPU 
// (use MINT13 mask): Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
#if (INT13PL != 0)
__interrupt void 
INT13_ISR(void)
{
    IER |= MINT13;                 // Set "global" priority
    EINT;

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
#endif

//
// INT14_ISR - CPU-Timer2 is connected to INT14 of CPU (use MINT14 mask)
//
#if (INT14PL != 0)
__interrupt void 
INT14_ISR(void)
{
    IER |= MINT14;                  // Set "global" priority
    EINT;

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
#endif

//
// DATALOG_ISR - Datalogging interrupt is connected to int15 of CPU
// (use MINT15 mask)
//
#if (INT15PL != 0)
__interrupt void 
DATALOG_ISR(void)
{
	IER |= MINT15;                 // Set "global" priority
	EINT;

  	// Insert ISR Code here.......

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    __asm ("      ESTOP0");
    for(;;);
}
#endif

//
// RTOSINT_ISR - RTOS interrupt is connected to int16 of CPU (use MINT16 mask)
//
#if (INT16PL != 0)
__interrupt void 
RTOSINT_ISR(void)
{
    IER |= MINT16;                 // Set "global" priority
    EINT;

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
#endif

//
// EMUINT_ISR - Emulation interrupt is connected to EMUINT of CPU 
// (non-maskable)
//
__interrupt void
EMUINT_ISR(void)
{
    EINT;

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
// NMI_ISR - Non-maskable interrupt is connected to NMI of CPU (non-maskable)
//
__interrupt void
NMI_ISR(void)
{
    EINT;

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
// ILLEGAL_ISR - Illegal operation TRAP is connected to ITRAP of CPU 
// (non-maskable)
//
__interrupt void
ILLEGAL_ISR(void)
{
    EINT;

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
// USER1_ISR - User Defined trap 1 is connected to USER1 of CPU (non-maskable)
//
__interrupt void
USER1_ISR(void)
{
    EINT;

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
// USER2_ISR - User Defined trap 2 is connected to USER2 of CPU (non-maskable)
//
__interrupt void
USER2_ISR(void)
{
    EINT;

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
// USER3_ISR - User Defined trap 3 is connected to USER3 of CPU (non-maskable)
//
__interrupt void
USER3_ISR(void)
{
    EINT;

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
// USER4_ISR - User Defined trap 4 is connected to USER4 of CPU (non-maskable)
//
__interrupt void
USER4_ISR(void)
{
    EINT;

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
// USER5_ISR - User Defined trap 5 is connected to USER5 of CPU (non-maskable)
//
__interrupt void
USER5_ISR(void)
{
    EINT;

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
// USER6_ISR - User Defined trap 6 is connected to USER6 of CPU (non-maskable)
//
__interrupt void
USER6_ISR(void)
{
    EINT;

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
// USER7_ISR - User Defined trap 7 is connected to USER7 of CPU (non-maskable)
//
__interrupt void 
USER7_ISR(void)
{
    EINT;

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
// USER8_ISR - User Defined trap 8 is connected to USER8 of CPU (non-maskable)
//
__interrupt void
USER8_ISR(void)
{
    EINT;

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
// USER9_ISR - User Defined trap 9 is connected to USER9 of CPU (non-maskable)
//
__interrupt void
USER9_ISR(void)
{
    EINT;

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
// USER10_ISR - User Defined trap 10 is connected to USER10 of 
// CPU (non-maskable)
//
__interrupt void 
USER10_ISR(void)
{
    EINT;

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
// USER11_ISR - User Defined trap 11 is connected to USER11 of
// CPU (non-maskable)
//
__interrupt void 
USER11_ISR(void)
{
    EINT;

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
// USER12_ISR - User Defined trap 12 is connected to USER12 of 
// CPU (non-maskable)
//
__interrupt void 
USER12_ISR(void)
{
    EINT;

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
// SEQ1INT_ISR - ADC is connected to PIEIER1_1 (use MINT1 and MG11 masks)
//
#if (G11PL != 0)
__interrupt void 
SEQ1INT_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER	&= MINT1;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0011;
    ISRTraceIndex++;
}
#endif

//
// SEQ2INT_ISR - ADC is connected to PIEIER1_2 (use MINT1 and MG12 masks)
//
#if (G12PL != 0)
__interrupt void 
SEQ2INT_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER	&= MINT1;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0012;
    ISRTraceIndex++;
}
#endif

//
// XINT1_ISR - connected to PIEIER1_4 (use MINT1 and MG14 masks)
//
#if (G14PL != 0)
__interrupt void
XINT1_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG14;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    __asm("      NOP");

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0014;
    ISRTraceIndex++;
}
#endif

//
// XINT2_ISR - Connected to PIEIER1_5 (use MINT1 and MG15 masks)
//
#if (G15PL != 0)
__interrupt void
XINT2_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER	&= MINT1;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0015;
    ISRTraceIndex++;
}
#endif

//
// ADCINT_ISR - ADC is connected to PIEIER1_6 (use MINT1 and MG16 masks)
//
#if (G16PL != 0)
__interrupt void
ADCINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER	&= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG16;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {

    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0016;
    ISRTraceIndex++;
}
#endif

//
// TINT0_ISR - CPU-Timer 0 is connected to PIEIER1_7 (use MINT1 and MG17 masks)
//
#if (G17PL != 0)
__interrupt void
TINT0_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
	IER |= M_INT1;
	IER	&= MINT1;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER1.all &= MG17;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0017;
    ISRTraceIndex++;
}
#endif

//
// WAKEINT_ISR - WD/LPM is connected to PIEIER1_8 (use MINT1 and MG18 masks)
//
#if (G18PL != 0)
__interrupt void
WAKEINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER	&= MINT1;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG18;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }
    
    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0018;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 2 - MUXed into CPU INT2
//

//
// EPWM1_TZINT_ISR - ePWM1 Trip Zone is connected to PIEIER2_1 
// (use MINT2 and MG21 masks)
//
#if (G21PL != 0)
__interrupt void
EPWM1_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER	&= MINT2;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG21;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0021;
    ISRTraceIndex++;
}
#endif

//
// EPWM2_TZINT_ISR - ePWM2 Trip Zone is connected to PIEIER2_2 
// (use MINT2 and MG22 masks)
//
#if (G22PL != 0)
__interrupt void
EPWM2_TZINT_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
	IER |= M_INT2;
	IER	&= MINT2;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER2.all &= MG22;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0022;
    ISRTraceIndex++;
}
#endif

//
// EPWM3_TZINT_ISR - ePWM3 Trip Zone is connected to PIEIER2_3 
// (use MINT2 and MG23 masks)
//
#if (G23PL != 0)
__interrupt void
EPWM3_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER	&= MINT2;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG23;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0023;
    ISRTraceIndex++;
}
#endif

//
// EPWM4_TZINT_ISR - ePWM4 Trip Zone is connected to PIEIER2_4
// (use MINT2 and MG24 masks)
//
#if (G24PL != 0)
__interrupt void
EPWM4_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER	&= MINT2;	  	                // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG24;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0024;
    ISRTraceIndex++;
}
#endif

//
// EPWM5_TZINT_ISR - ePWM5 Trip Zone is connected to PIEIER2_5
// (use MINT2 and MG25 masks)
//
#if (G25PL != 0)
__interrupt void
EPWM5_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER	&= MINT2;	  	                // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG25;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0025;
    ISRTraceIndex++;
}
#endif

//
// EPWM6_TZINT_ISR - ePWM6 Trip Zone is connected to PIEIER2_6
// (use MINT2 and MG26 masks)
//
#if (G26PL != 0)
__interrupt void
EPWM6_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER	&= MINT2;	  	                // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG26;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0026;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - ePWM1 Interrupt is connected to PIEIER3_1
// (use MINT3 and MG31 masks)
//
#if (G31PL != 0)
__interrupt void
EPWM1_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG31;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0031;
    ISRTraceIndex++;
}
#endif

//
// EPWM2_INT_ISR - ePWM2 Interrupt is connected to PIEIER3_2
// (use MINT3 and MG32 masks)
//
#if (G32PL != 0)
__interrupt void
EPWM2_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG32;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0032;
    ISRTraceIndex++;
}
#endif

//
// EPWM3_INT_ISR - ePWM3 Interrupt is connected to PIEIER3_3
// (use MINT3 and MG33 masks)
//
#if (G33PL != 0)
__interrupt void
EPWM3_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	                // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG33;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }
    
    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0033;
    ISRTraceIndex++;
}
#endif

//
// EPWM4_INT_ISR - ePWM4 Interrupt is connected to PIEIER3_4
// (use MINT3 and MG34 masks)
//
#if (G34PL != 0)
__interrupt void
EPWM4_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG34;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0034;
    ISRTraceIndex++;
}
#endif

//
// EPWM5_INT_ISR - ePWM5 Interrupt is connected to PIEIER3_5
// (use MINT3 and MG35 masks)
//
#if (G35PL != 0)
__interrupt void
EPWM5_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG35;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0035;
    ISRTraceIndex++;
}
#endif

//
// EPWM6_INT_ISR - ePWM6 Interrupt is connected to PIEIER3_6
// (use MINT3 and MG36 masks)
//
#if (G36PL != 0)
__interrupt void
EPWM6_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER	&= MINT3;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG36;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0036;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 4 - MUXed into CPU INT4
//

//
// ECAP1_INT_ISR - eCAP1 Interrupt is connected to PIEIER4_1
// (use MINT4 and MG41 masks)
//
#if (G41PL != 0)
__interrupt void
ECAP1_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG41;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0041;
    ISRTraceIndex++;
}
#endif

//
// ECAP2_INT_ISR - eCAP2 Interrupt is connected to PIEIER4_2
// (use MINT4 and MG42 masks)
//
#if (G42PL != 0)
__interrupt void
ECAP2_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG42;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0042;
    ISRTraceIndex++;

}
#endif

//
// ECAP3_INT_ISR - eCAP3 Interrupt is connected to PIEIER4_3 
// (use MINT4 and MG43 masks)
//
#if (G43PL != 0)
__interrupt void
ECAP3_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG43;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0043;
    ISRTraceIndex++;

}
#endif

//
// ECAP4_INT_ISR - eCAP4 Interrupt is connected to PIEIER4_4
// (use MINT4 and MG44 masks)
//
#if (G44PL != 0)
__interrupt void
ECAP4_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG44;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0044;
    ISRTraceIndex++;
}
#endif

//
// ECAP5_INT_ISR - eCAP5 Interrupt is connected to PIEIER4_5
// (use MINT4 and MG45 masks)
//
#if (G44PL != 0)
__interrupt void
ECAP5_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG45;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0045;
    ISRTraceIndex++;
}
#endif

//
// ECAP6_INT_ISR - eCAP6 Interrupt is connected to PIEIER4_6
// (use MINT4 and MG46 masks)
//
#if (G44PL != 0)
__interrupt void
ECAP6_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER	&= MINT4;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG46;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0046;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 5 - MUXed into CPU INT5
//

//
// EQEP1_INT_ISR - eQEP1 Interrupt is connected to PIEIER5_1
// (use MINT5 and MG51 masks)
//
#if (G51PL != 0)
__interrupt void
EQEP1_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER	&= MINT5;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG51;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0051;
    ISRTraceIndex++;
}
#endif

//
// EQEP2_INT_ISR - eQEP2 Interrupt is connected to PIEIER5_2
// (use MINT5 and MG52 masks)
//
#if (G52PL != 0)
__interrupt void
EQEP2_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER	&= MINT5;	  	                // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG52;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++) {}

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0052;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 6 - MUXed into CPU INT6
//

//
// SPIRXINTA_ISR - SPI-A is connected to PIEIER6_1 (use MINT6 and MG61 masks)
//
#if (G61PL != 0)
__interrupt void
SPIRXINTA_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG61;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0061;
    ISRTraceIndex++;
}
#endif

//
// SPITXINTA_ISR - SPI-A is connected to PIEIER6_2 (use MINT6 and MG62 masks)
//
#if (G62PL != 0)
__interrupt void
SPITXINTA_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG62;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0062;
    ISRTraceIndex++;
}
#endif

//
// MRINTB_ISR - McBSP-B is connected to PIEIER6_3 (use MINT6 and MG63 masks)
//
#if (G63PL != 0)
__interrupt void
MRINTB_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG63;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0063;
    ISRTraceIndex++;
}
#endif

//
// MXINTB_ISR - McBSP-B is connected to PIEIER6_4 (use MINT6 and MG64 masks)
//
#if (G64PL != 0)
__interrupt void
MXINTB_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG64;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0064;
    ISRTraceIndex++;
}
#endif

//
// MRINTA_ISR - McBSP-A is connected to PIEIER6_5 (use MINT6 and MG65 masks)
//
#if (G65PL != 0)
__interrupt void
MRINTA_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG65;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0065;
    ISRTraceIndex++;
}
#endif

//
// MXINTA_ISR - McBSP-A is connected to PIEIER6_6 (use MINT6 and MG66 masks)
//
#if (G66PL != 0)
__interrupt void
MXINTA_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER	&= MINT6;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG66;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0066;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 7 - MUXed into CPU INT7
//

//
// DINTCH1_ISR - DMA-Channel 1 is connected to PIEIER7_1
// (use MINT7 and MG71 masks)
//
#if (G71PL != 0)
__interrupt void
DINTCH1_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER	&= MINT7;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG71;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0071;
    ISRTraceIndex++;
}
#endif

//
// DINTCH2_ISR - DMA-Channel 2 is connected to PIEIER7_2
// (use MINT7 and MG72 masks)
//
#if (G72PL != 0)
__interrupt void
DINTCH2_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
	IER |= M_INT7;
	IER	&= MINT7;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER7.all &= MG72;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0072;
    ISRTraceIndex++;
}
#endif

//
// DINTCH3_ISR - DMA-Channel 3 is connected to PIEIER7_3
// (use MINT7 and MG73 masks)
//
#if (G73PL != 0)
__interrupt void
DINTCH3_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER	&= MINT7;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG73;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0073;
    ISRTraceIndex++;
}
#endif

//
// DINTCH4_ISR - DMA-Channel 4 is connected to PIEIER7_4
// (use MINT7 and MG74 masks)
//
#if (G74PL != 0)
__interrupt void
DINTCH4_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER	&= MINT7;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG74;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0074;
    ISRTraceIndex++;
}
#endif

//
// DINTCH5_ISR - DMA-Channel 5 is connected to PIEIER7_5
// (use MINT7 and MG75 masks)
//
#if (G75PL != 0)
__interrupt void
DINTCH5_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
	IER |= M_INT7;
	IER	&= MINT7;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER7.all &= MG75;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0075;
    ISRTraceIndex++;
}
#endif

//
// DINTCH6_ISR - DMA-Channel 6 is connected to PIEIER7_6
// (use MINT7 and MG76 masks)
//
#if (G76PL != 0)
__interrupt void
DINTCH6_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER7.all;
    IER |= M_INT7;
    IER	&= MINT7;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER7.all &= MG76;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0076;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - I2C-A is connected to PIEIER8_1
// (use MINT8 and MG81 masks)
//
#if (G81PL != 0)
__interrupt void
I2CINT1A_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER	&= MINT8;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG81;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here.
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0081;
    ISRTraceIndex++;
}
#endif

//
// I2CINT2A_ISR - I2C-A is connected to PIEIER8_2 (use MINT8 and MG82 masks)
//
#if (G82PL != 0)
__interrupt void
I2CINT2A_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER8.all &= MG82;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0082;
    ISRTraceIndex++;
}
#endif

//
// SCIRXINTC_ISR - SCI-C is connected to PIEIER8_5 (use MINT8 and MG85 masks)
//
#if (G85PL != 0)
__interrupt void
SCIRXINTC_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER8.all &= MG85;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0085;
    ISRTraceIndex++;
}
#endif

//
// SCITXINTC_ISR - SCI-C is connected to PIEIER8_6 (use MINT8 and MG86 masks)
//
#if (G86PL != 0)
__interrupt void
SCITXINTC_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER	&= MINT8;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG86;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0086;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 9 - MUXed into CPU INT9
//

//
// SCIRXINTA_ISR - SCI-A is connected to PIEIER9_1 (use MINT9 and MG91 masks)
//
#if (G91PL != 0)
__interrupt void
SCIRXINTA_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG91;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0091;
    ISRTraceIndex++;
}
#endif

//
// SCITXINTA_ISR - SCI-A is connected to PIEIER9_2 (use MINT9 and MG92 masks)
//
#if (G92PL != 0)
__interrupt void
SCITXINTA_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG92;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0092;
    ISRTraceIndex++;
}
#endif

//
// SCIRXINTB_ISR - SCI-B is connected to PIEIER9_3 (use MINT9 and MG93 masks)
//
#if (G93PL != 0)
__interrupt void
SCIRXINTB_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG93;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
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
// SCITXINTB_ISR - SCI-B is connected to PIEIER9_4 (use MINT9 and MG94 masks)
//
#if (G94PL != 0)
__interrupt void
SCITXINTB_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER	&= MINT9;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG94;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0094;
    ISRTraceIndex++;
}
#endif

//
// ECAN0INTA_ISR - eCAN-A is connected to PIEIER9_5 (use MINT9 and MG95 masks)
//
#if (G95PL != 0)
__interrupt void
ECAN0INTA_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG95;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0095;
    ISRTraceIndex++;
}
#endif

//
// ECAN1INTA_ISR - eCAN-A is connected to PIEIER9_6 (use MINT9 and MG96 masks)
//
#if (G96PL != 0)
__interrupt void
ECAN1INTA_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG96;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0096;
    ISRTraceIndex++;
}
#endif

//
// ECAN0INTB_ISR - eCAN-B is connected to PIEIER9_7 (use MINT9 and MG97 masks)
//
#if (G97PL != 0)
__interrupt void
ECAN0INTB_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG97;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0097;
    ISRTraceIndex++;
}
#endif

//
// ECAN1INTB_ISR - eCAN-B is connected to PIEIER9_8 (use MINT9 and MG98 masks)
//
#if (G98PL != 0)
__interrupt void 
ECAN1INTB_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG98;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;
    
    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0098;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 10 - MUXed into CPU int10
//

//
// PIE Group 11 - MUXed into CPU int11
//

//
// PIE Group 12 - MUXed into CPU int12
//

//
// XINT3_ISR - External Interrupt is connected to PIEIER12_1
// (use MINT12 and MG121 masks)
//
#if (G121PL != 0)
__interrupt void
XINT3_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG121; // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0121;
    ISRTraceIndex++;
}
#endif

//
// XINT4_ISR - External Interrupt is connected to PIEIER12_2
// (use MINT12 and MG122 masks)
//
#if (G122PL != 0)
__interrupt void
XINT4_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG122; // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0122;
    ISRTraceIndex++;
}
#endif

//
// XINT5_ISR - External Interrupt is connected to PIEIER12_3
// (use MINT12 and MG123 masks)
//
#if (G123PL != 0)
__interrupt void
XINT5_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG123; // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0123;
    ISRTraceIndex++;
}
#endif

//
// XINT6_ISR - External Interrupt is connected to PIEIER12_4
// (use MINT12 and MG124 masks)
//
#if (G124PL != 0)
__interrupt void
XINT6_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG124; // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0124;
    ISRTraceIndex++;
}
#endif

//
// XINT7_ISR - External Interrupt is connected to PIEIER12_5 
// (use MINT12 and MG125 masks)
//
#if (G125PL != 0)
__interrupt void
XINT7_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER	&= MINT12;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG125; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0125;
    ISRTraceIndex++;
}
#endif

//
// LVF_ISR - FPA32 is connected to PIEIER12_7 (use MINT12 and MG127 masks)
//
#if (G127PL != 0)
__interrupt void
LVF_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER	&= MINT12;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG127; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0127;
    ISRTraceIndex++;
}
#endif

//
// LUF_ISR - FPA32 is connected to PIEIER12_8 (use MINT12 and MG128 masks)
//
#if (G128PL != 0)
__interrupt void
LUF_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER	&= MINT12;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG128; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0128;
    ISRTraceIndex++;
}
#endif

//
// Catch All Default ISRs
//

//
// PIE_RESERVED - 
//
__interrupt void
PIE_RESERVED(void)
{
    __asm ("      ESTOP0");
    for(;;);
}

//
// INT_NOTUSED_ISR - 
//
__interrupt void 
INT_NOTUSED_ISR(void)
{
    __asm ("      ESTOP0");
    for(;;);
}

//
// rsvd_ISR - 
//
__interrupt void
rsvd_ISR(void)
{
    __asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

