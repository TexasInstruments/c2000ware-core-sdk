// TI File $Revision: /main/5 $
// Checkin $Date: January 14, 2008   11:28:12 $
//###########################################################################
//
// FILE:    DSP2823x_SWPrioritizedDefaultIsr.c
//
// TITLE:   DSP2823x Device Default Software Prioritized Interrupt 
//          Service Routines.
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

//
// INT13_ISR - Connected to INT13 of CPU (use MINT13 mask):
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
#if (INT13PL != 0)
interrupt void 
INT13_ISR(void)     // INT13 or CPU-Timer1
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
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// INT14_ISR - Connected to INT14 of CPU (use MINT14 mask):
//
#if (INT14PL != 0)
interrupt void 
INT14_ISR(void)     // CPU-Timer2
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
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DATALOG_ISR - Connected to INT15 of CPU (use MINT15 mask):
//
#if (INT15PL != 0)
interrupt void 
DATALOG_ISR(void)   // Datalogging interrupt
{
    IER |= MINT15;                 // Set "global" priority
    EINT;

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
#endif

//
// RTOSINT_ISR - Connected to INT16 of CPU (use MINT16 mask):
//
#if (INT16PL != 0)
interrupt void 
RTOSINT_ISR(void)   // RTOS interrupt
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
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EMUINT_ISR - Emulation interrupt is connected to EMUINT of CPU(non-maskable)
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-maskable interrupt is connected to NMI of CPU (non-maskable):
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);;
}

//
// ILLEGAL_ISR - Illegal operation TRAP
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined trap 1
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined trap 2
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined trap 3
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined trap 4
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined trap 5
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined trap 6
//
interrupt void
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined trap 7
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined trap 8
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined trap 9
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined trap 10
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined trap 11
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined trap 12
//
interrupt void 
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
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 1 - MUXed into CPU INT1
//

//
// SEQ1INT_ISR - Connected to PIEIER1_1 (use MINT1 and MG11 masks):
//
#if (G11PL != 0)
interrupt void 
SEQ1INT_ISR( void )     // ADC
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SEQ2INT_ISR - Connected to PIEIER1_2 (use MINT1 and MG12 masks):
//
#if (G12PL != 0)
interrupt void 
SEQ2INT_ISR( void )    // ADC
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT1_ISR - Connected to PIEIER1_4 (use MINT1 and MG14 masks):
//
#if (G14PL != 0)
interrupt void  
XINT1_ISR(void)
{
    //
    // Set interrupt priority:
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT2_ISR - Connected to PIEIER1_5 (use MINT1 and MG15 masks):
//
#if (G15PL != 0)
interrupt void  
XINT2_ISR(void)
{
    //
    // Set interrupt priority:
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here
    //
    
    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ADCINT_ISR - Connected to PIEIER1_6 (use MINT1 and MG16 masks):
//
#if (G16PL != 0)
interrupt void  
ADCINT_ISR(void)     // ADC
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// TINT0_ISR - Connected to PIEIER1_7 (use MINT1 and MG17 masks):
//
#if (G17PL != 0)
interrupt void  
TINT0_ISR(void)      // CPU-Timer 0
{
    //
	// Set interrupt priority:
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

    //
  	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// WAKEINT_ISR - Connected to PIEIER1_8 (use MINT1 and MG18 masks):
//
#if (G18PL != 0)
interrupt void  
WAKEINT_ISR(void)      // WD/LPM
{
    //
	// Set interrupt priority:
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

    //
    // Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER1.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 2 - MUXed into CPU INT2
//

//
// EPWM1_TZINT_ISR - Connected to PIEIER2_1 (use MINT2 and MG21 masks):
//
#if (G21PL != 0)
interrupt void 
EPWM1_TZINT_ISR(void)    // ePWM1 Trip Zone
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM2_TZINT_ISR - Connected to PIEIER2_2 (use MINT2 and MG22 masks):
//
#if (G22PL != 0)
interrupt void 
EPWM2_TZINT_ISR(void)    // ePWM2 Trip Zone
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM3_TZINT_ISR - Connected to PIEIER2_3 (use MINT2 and MG23 masks):
//
#if (G23PL != 0)
interrupt void 
EPWM3_TZINT_ISR(void)    // ePWM3 Trip Zone
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM4_TZINT_ISR - Connected to PIEIER2_4 (use MINT2 and MG24 masks):
//
#if (G24PL != 0)
interrupt void 
EPWM4_TZINT_ISR(void)    // ePWM4 Trip Zone
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM5_TZINT_ISR - Connected to PIEIER2_5 (use MINT2 and MG25 masks)
//
#if (G25PL != 0)
interrupt void 
EPWM5_TZINT_ISR(void)    // ePWM5 Trip Zone
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM6_TZINT_ISR - Connected to PIEIER2_6 (use MINT2 and MG26 masks)
//
#if (G26PL != 0)
interrupt void 
EPWM6_TZINT_ISR(void)    // ePWM6 Trip Zone
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER2.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - Connected to PIEIER3_1 (use MINT3 and MG31 masks)
//
#if (G31PL != 0)
interrupt void 
EPWM1_INT_ISR(void)     // ePWM1 Interrupt
{
    //
    // Set interrupt priority:
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

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM2_INT_ISR - Connected to PIEIER3_2 (use MINT3 and MG32 masks)
//
#if (G32PL != 0)
interrupt void 
EPWM2_INT_ISR(void)     // ePWM2 Interrupt
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM3_INT_ISR - Connected to PIEIER3_3 (use MINT3 and MG33 masks)
//
#if (G33PL != 0)
interrupt void 
EPWM3_INT_ISR(void)     // ePWM3 Interrupt
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// Connected to PIEIER3_4 (use MINT3 and MG34 masks)
//
#if (G34PL != 0)
interrupt void 
EPWM4_INT_ISR(void)     // ePWM4 Interrupt
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM5_INT_ISR - Connected to PIEIER3_5 (use MINT3 and MG35 masks)
//
#if (G35PL != 0)
interrupt void 
EPWM5_INT_ISR(void)     // ePWM5 Interrupt
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EPWM6_INT_ISR - Connected to PIEIER3_6 (use MINT3 and MG36 masks)
//
#if (G36PL != 0)
interrupt void 
EPWM6_INT_ISR(void)     // ePWM6 Interrupt
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

    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER3.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

// 
// PIE Group 4 - MUXed into CPU INT4
// 

//
// ECAP1_INT_ISR - Connected to PIEIER4_1 (use MINT4 and MG41 masks)
//
#if (G41PL != 0)
interrupt void 
ECAP1_INT_ISR(void)     // eCAP1 Interrupt
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// Connected to PIEIER4_2 (use MINT4 and MG42 masks):
//
#if (G42PL != 0)
interrupt void 
ECAP2_INT_ISR(void)     // eCAP2 Interrupt
{
    //
	// Set interrupt priority:
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
	IER |= M_INT4;
	IER	&= MINT4;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER4.all &= MG42;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAP3_INT_ISR - Connected to PIEIER4_3 (use MINT4 and MG43 masks)
//
#if (G43PL != 0)
interrupt void 
ECAP3_INT_ISR(void)     // eCAP3 Interrupt
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAP4_INT_ISR - Connected to PIEIER4_4 (use MINT4 and MG44 masks)
//
#if (G44PL != 0)
interrupt void 
ECAP4_INT_ISR(void)     // eCAP4 Interrupt
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
  	// Insert ISR Code here.
    //

    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAP5_INT_ISR - Connected to PIEIER4_5 (use MINT4 and MG45 masks):
//
#if (G45PL != 0)
interrupt void 
ECAP5_INT_ISR(void)     // eCAP5 Interrupt
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAP6_INT_ISR - Connected to PIEIER4_6 (use MINT4 and MG46 masks):
//
#if (G46PL != 0)
interrupt void 
ECAP6_INT_ISR(void)     // eCAP6 Interrupt
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER4.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 5 - MUXed into CPU INT5
//

//
// Connected to PIEIER5_1 (use MINT5 and MG51 masks)
//
#if (G51PL != 0)
interrupt void 
EQEP1_INT_ISR(void)     // eQEP1 Interrupt
{
    //
    // Set interrupt priority:
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER	&= MINT5;	  	               // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG51;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
    __asm("  NOP");
    EINT;

    // Insert ISR Code here.......

    //
    // Restore registers saved:
    //
    DINT;
    PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// EQEP2_INT_ISR - Connected to PIEIER5_2 (use MINT5 and MG52 masks)
//
#if (G52PL != 0)
interrupt void 
EQEP2_INT_ISR(void)     // eQEP2 Interrupt
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
	IER |= M_INT5;
	IER	&= MINT5;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER5.all &= MG52;    // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER5.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 6 - MUXed into CPU INT6
//

//
// SPIRXINTA_ISR - Connected to PIEIER6_1 (use MINT6 and MG61 masks)
//
#if (G61PL != 0)
interrupt void 
SPIRXINTA_ISR(void)    // SPI-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SPITXINTA_ISR - Connected to PIEIER6_2 (use MINT6 and MG62 masks)
//
#if (G62PL != 0)
interrupt void 
SPITXINTA_ISR(void)     // SPI-A
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// MRINTB_ISR - Connected to PIEIER6_3 (use MINT6 and MG63 masks)
//
#if (G63PL != 0)
interrupt void 
MRINTB_ISR(void)    // McBSP-B
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// MXINTB_ISR - Connected to PIEIER6_4 (use MINT6 and MG64 masks)
//
#if (G64PL != 0)
interrupt void 
MXINTB_ISR(void)     // McBSP-B
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// MRINTA_ISR - Connected to PIEIER6_5 (use MINT6 and MG65 masks)
//
#if (G65PL != 0)
interrupt void 
MRINTA_ISR(void)     // McBSP-A
{
    //
	// Set interrupt priority:
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// MXINTA_ISR - Connected to PIEIER6_6 (use MINT6 and MG66 masks)
//
#if (G66PL != 0)
interrupt void 
MXINTA_ISR(void)     // McBSP-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER6.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 7 - MUXed into CPU INT7
//

//
// DINTCH1_ISR - Connected to PIEIER7_1 (use MINT7 and MG71 masks)
//
#if (G71PL != 0)
interrupt void 
DINTCH1_ISR(void)    // DMA
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DINTCH2_ISR - Connected to PIEIER7_2 (use MINT7 and MG72 masks)
//
#if (G72PL != 0)
interrupt void 
DINTCH2_ISR(void)       // DMA
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
    
    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DINTCH3_ISR - Connected to PIEIER7_3 (use MINT7 and MG73 masks)
//
#if (G73PL != 0)
interrupt void 
DINTCH3_ISR(void)       // DMA
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DINTCH4_ISR - Connected to PIEIER7_4 (use MINT7 and MG74 masks)
//
#if (G74PL != 0)
interrupt void 
DINTCH4_ISR(void)       // DMA
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

    //
	// Restore registers saved:
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DINTCH5_ISR - Connected to PIEIER7_5 (use MINT7 and MG75 masks):
//
#if (G75PL != 0)
interrupt void 
DINTCH5_ISR(void)        // DMA
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// DINTCH6_ISR - Connected to PIEIER7_6 (use MINT7 and MG76 masks)
//
#if (G76PL != 0)
interrupt void 
DINTCH6_ISR(void)        // DMA
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER7.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - Connected to PIEIER8_1 (use MINT8 and MG81 masks)
//
#if (G81PL != 0)
interrupt void 
I2CINT1A_ISR(void)    // I2C-A
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG81;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// I2CINT2A_ISR - Connected to PIEIER8_2 (use MINT8 and MG82 masks)
//
#if (G82PL != 0)
interrupt void 
I2CINT2A_ISR(void)     // I2C-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SCIRXINTC_ISR - Connected to PIEIER8_5 (use MINT8 and MG85 masks)
//
#if (G85PL != 0)
interrupt void 
SCIRXINTC_ISR(void)    // SCI-C
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
	IER |= M_INT8;
	IER	&= MINT8;	  	               // Set "global" priority
	PieCtrlRegs.PIEIER6.all &= MG85;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SCITXINTC_ISR - Connected to PIEIER8_6 (use MINT8 and MG86 masks)
//
#if (G82PL != 0)
interrupt void 
SCITXINTC_ISR(void)     // SCI-C
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER8.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

// 
// PIE Group 9 - MUXed into CPU INT9
// 

//
// SCIRXINTA_ISR - Connected to PIEIER9_1 (use MINT9 and MG91 masks)
//
#if (G91PL != 0)
interrupt void 
SCIRXINTA_ISR(void)     // SCI-A
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
	IER |= M_INT9;
	IER	&= MINT9;	  	                // Set "global" priority
	PieCtrlRegs.PIEIER9.all &= MG91;    // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SCITXINTA_ISR - Connected to PIEIER9_2 (use MINT9 and MG92 masks)
//
#if (G92PL != 0)
interrupt void 
SCITXINTA_ISR(void)     // SCI-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SCIRXINTB_ISR - Connected to PIEIER9_3 (use MINT9 and MG93 masks)
//
#if (G93PL != 0)
interrupt void 
SCIRXINTB_ISR(void)     // SCI-B
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// SCITXINTB_ISR - Connected to PIEIER9_4 (use MINT9 and MG94 masks)
//
#if (G94PL != 0)
interrupt void 
SCITXINTB_ISR(void)     // SCI-B
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAN0INTA_ISR - Connected to PIEIER9_5 (use MINT9 and MG95 masks)
//
#if (G95PL != 0)
interrupt void 
ECAN0INTA_ISR(void)    // eCAN-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAN1INTA_ISR - Connected to PIEIER9_6 (use MINT9 and MG96 masks)
//
#if (G96PL != 0)
interrupt void 
ECAN1INTA_ISR(void)     // eCAN-A
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAN0INTB_ISR - Connected to PIEIER9_7 (use MINT9 and MG97 masks)
//
#if (G97PL != 0)
interrupt void 
ECAN0INTB_ISR(void)    // eCAN-B
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// ECAN1INTB_ISR - Connected to PIEIER9_8 (use MINT9 and MG98 masks)
//
#if (G98PL != 0)
interrupt void 
ECAN1INTB_ISR(void)     // eCAN-B
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

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER9.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 10 - MUXed into CPU INT10
//

//
// PIE Group 11 - MUXed into CPU INT11
//

//
// PIE Group 12 - MUXed into CPU INT12
//

//
// XINT3_ISR - Connected to PIEIER9_1 (use MINT12 and MG121 masks)
//
#if (G121PL != 0)
interrupt void 
XINT3_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                 // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG121;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT4_ISR - Connected to PIEIER12_2 (use MINT12 and MG122 masks)
//
#if (G122PL != 0)
interrupt void 
XINT4_ISR(void)
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                 // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG122;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT5_ISR - Connected to PIEIER12_3 (use MINT12 and MG123 masks)
//
#if (G123PL != 0)
interrupt void 
XINT5_ISR(void)     // SCI-B
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                 // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG123;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT6_ISR - Connected to PIEIER12_4 (use MINT12 and MG124 masks)
//
#if (G124PL != 0)
interrupt void 
XINT6_ISR(void)     // SCI-B
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                 // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG124;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// XINT7_ISR - Connected to PIEIER12_5 (use MINT12 and MG125 masks)
//
#if (G125PL != 0)
interrupt void 
XINT7_ISR(void)    // eCAN-A
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                 // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG125;   // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;     // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// LVF_ISR - Connected to PIEIER12_7 (use MINT12 and MG127 masks)
//
#if (G127PL != 0)
interrupt void 
LVF_ISR(void)    // FPU
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                    // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG127;      // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;        // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// LUF_ISR - Connected to PIEIER12_8 (use MINT12 and MG128 masks)
//
#if (G128PL != 0)
interrupt void 
LUF_ISR(void)     // FPU
{
    //
	// Set interrupt priority
    //
	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
	IER |= M_INT12;
	IER	&= MINT12;	  	                    // Set "global" priority
	PieCtrlRegs.PIEIER12.all &= MG128;      // Set "group"  priority
	PieCtrlRegs.PIEACK.all = 0xFFFF;        // Enable PIE interrupts
	__asm("  NOP");
	EINT;

    //
  	// Insert ISR Code here
    //

    //
	// Restore registers saved
    //
	DINT;
	PieCtrlRegs.PIEIER12.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// Catch All Default ISRs
//

//
// PIE_RESERVED - Reserved space.  For test.
//
interrupt void 
PIE_RESERVED(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// INT_NOTUSED_ISR - Reserved space.  For test.
//
interrupt void 
INT_NOTUSED_ISR(void)  
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
// End of File
//

