//###########################################################################
//
// FILE:    F2805x_SWPrioritizedDefaultIsr.c
//
// TITLE:   F2805x Devices Default SW Prioritized Interrupt Service Routines.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File
#include "F2805x_SWPrioritizedIsrLevels.h"

#if (INT13PL != 0)
//
// INT13_ISR - INT13 or CPU-Timer1
// Connected to INT13 of CPU (use MINT13 mask):
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
__interrupt void
INT13_ISR(void)
{
    //
    // Set "global" priority
    //
    IER |= MINT13;
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

#if (INT14PL != 0)
//
// INT14_ISR - INT14 or CPU-Timer2
// Connected to INT14 of CPU (use MINT14 mask)
//
__interrupt void
INT14_ISR(void)
{
    //
    // Set "global" priority
    //
    IER |= MINT14;
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

#if (INT15PL != 0)
//
// DATALOG_ISR - Datalogging interrupt
// Connected to INT15 of CPU (use MINT15 mask):
//
__interrupt void
DATALOG_ISR(void)
{
    //
    // Set "global" priority
    //
    IER |= MINT15;
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

#if (INT16PL != 0)
//
// RTOSINT_ISR - RTOS interrupt
// Connected to INT16 of CPU (use MINT16 mask)
//
__interrupt void
RTOSINT_ISR(void)
{
    //
    // Set "global" priority
    //
    IER |= MINT16;
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
// EMUINT_ISR - Emulation interrupt
// Connected to EMUINT of CPU (non-maskable)
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
    asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-maskable __interrupt
// Connected to NMI of CPU (non-maskable)
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
    asm ("      ESTOP0");
    for(;;);
}

//
// ILLEGAL_ISR -  Illegal operation TRAP
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined trap 1
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined trap 2
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined trap 3
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined trap 4
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined trap 5
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined trap 6
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined trap 7
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined trap 8
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined trap 9
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined trap 10
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined trap 11
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
    asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined trap 12
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
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 1 - MUXed into CPU INT1
//
#if (G11PL != 0)
//
// ADCINT1_ISR - ADC  Interrupt 1
// Connected to PIEIER1_1 (use MINT1 and MG11 masks)
//
__interrupt void
ADCINT1_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG11;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G12PL != 0)
//
// ADCINT2_ISR - ADC Interrupt 2
// Connected to PIEIER1_2 (use MINT1 and MG12 masks)
//
__interrupt void
ADCINT2_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG12;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G14PL != 0)
//
// XINT1_ISR - XINT1 Interrupt
// Connected to PIEIER1_4 (use MINT1 and MG14 masks)
//
__interrupt void
XINT1_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG14;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
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

#if (G15PL != 0)
//
// XINT2_ISR - XINT2 Interrupt
// Connected to PIEIER1_5 (use MINT1 and MG15 masks)
//
__interrupt void
XINT2_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG15;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G16PL != 0)
//
// ADCINT9_ISR - ADC Interrupt 9
// Connected to PIEIER1_6 (use MINT1 and MG16 masks)
//
__interrupt void
ADCINT9_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG16;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G17PL != 0)
//
// TINT0_ISR - CPU-Timer 0 Interrupt
// Connected to PIEIER1_7 (use MINT1 and MG17 masks):
//
__interrupt void
TINT0_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG17;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G18PL != 0)
//
// WAKEINT_ISR - WD/LPM
// Connected to PIEIER1_8 (use MINT1 and MG18 masks)
//
__interrupt void
WAKEINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER &= MINT1;                      // Set "global" priority
    PieCtrlRegs.PIEIER1.all &= MG18;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G21PL != 0)
//
// EPWM1_TZINT_ISR - ePWM1 Trip Zone
// Connected to PIEIER2_1 (use MINT2 and MG21 masks):
//
__interrupt void
EPWM1_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                      // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG21;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G22PL != 0)
//
// EPWM2_TZINT_ISR - ePWM2 Trip Zone
// Connected to PIEIER2_2 (use MINT2 and MG22 masks):
//
__interrupt void
EPWM2_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                      // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG22;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G23PL != 0)
//
// EPWM3_TZINT_ISR - ePWM3 Trip Zone
// Connected to PIEIER2_3 (use MINT2 and MG23 masks):
//
__interrupt void
EPWM3_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                      // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG23;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G24PL != 0)
//
// EPWM4_TZINT_ISR - ePWM4 Trip Zone
// Connected to PIEIER2_4 (use MINT2 and MG24 masks):
//
__interrupt void
EPWM4_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                       // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG24;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G25PL != 0)
//
// EPWM5_TZINT_ISR - ePWM5 Trip Zone
// Connected to PIEIER2_5 (use MINT2 and MG25 masks):
//
__interrupt void
EPWM5_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                       // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG25;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G24PL != 0)
//
// EPWM6_TZINT_ISR - ePWM6 Trip Zone
// Connected to PIEIER2_6 (use MINT2 and MG26 masks):
//
__interrupt void
EPWM6_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                       // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG26;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G27PL != 0)
//
// EPWM7_TZINT_ISR - ePWM7 Trip Zone
// Connected to PIEIER2_7 (use MINT2 and MG27 masks)
//
__interrupt void
EPWM7_TZINT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT2;
    IER &= MINT2;                       // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG27;    // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G31PL != 0)
//
// EPWM1_INT_ISR - ePWM1 Interrupt
// Connected to PIEIER3_1 (use MINT3 and MG31 masks)
//
__interrupt void
EPWM1_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG31;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G32PL != 0)
//
// EPWM2_INT_ISR - ePWM2 Interrupt
// Connected to PIEIER3_2 (use MINT3 and MG32 masks)
//
__interrupt void
EPWM2_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG32;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G33PL != 0)
//
// EPWM3_INT_ISR -  ePWM3 Interrupt
// Connected to PIEIER3_3 (use MINT3 and MG33 masks)
//
__interrupt void
EPWM3_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                       // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG33;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G34PL != 0)
//
// EPWM4_INT_ISR - ePWM4 Interrupt
// Connected to PIEIER3_4 (use MINT3 and MG34 masks)
//
__interrupt void
EPWM4_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG34;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G34PL != 0)
//
// EPWM5_INT_ISR - ePWM5 Interrupt
// Connected to PIEIER3_5 (use MINT3 and MG35 masks)
//
__interrupt void
EPWM5_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG35;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G36PL != 0)
//
// EPWM6_INT_ISR - ePWM6 Interrupt
// Connected to PIEIER3_6 (use MINT3 and MG36 masks)
//
__interrupt void
EPWM6_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG36;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G37PL != 0)
//
// EPWM7_INT_ISR - ePWM4 Interrupt
// Connected to PIEIER3_7 (use MINT3 and MG37 masks):
//
__interrupt void
EPWM7_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;
    IER |= M_INT3;
    IER &= MINT3;                      // Set "global" priority
    PieCtrlRegs.PIEIER3.all &= MG37;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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
// PIE Group 4 - MUXed into CPU INT4
//

#if (G41PL != 0)
//
// ECAP1_INT_ISR - eCAP1 Interrupt
// Connected to PIEIER4_1 (use MINT4 and MG41 masks):
//
__interrupt void
ECAP1_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER4.all;
    IER |= M_INT4;
    IER &= MINT4;                      // Set "global" priority
    PieCtrlRegs.PIEIER4.all &= MG41;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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
// PIE Group 5 - MUXed into CPU INT5
//

#if (G51PL != 0)
//
// EQEP1_INT_ISR - eQEP1 Interrupt
// Connected to PIEIER5_1 (use MINT5 and MG51 masks):
//
__interrupt void
EQEP1_INT_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER5.all;
    IER |= M_INT5;
    IER &= MINT5;                      // Set "global" priority
    PieCtrlRegs.PIEIER5.all &= MG51;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
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

#if (G61PL != 0)
//
// SPIRXINTA_ISR - SPI-A
// Connected to PIEIER6_1 (use MINT6 and MG61 masks)
//
__interrupt void
SPIRXINTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER &= MINT6;                      // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG61;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G62PL != 0)
//
// SPITXINTA_ISR - SPI-A
// Connected to PIEIER6_2 (use MINT6 and MG62 masks):
//
__interrupt void
SPITXINTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER6.all;
    IER |= M_INT6;
    IER &= MINT6;                      // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG62;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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
// PIE Group 8 - MUXed into CPU INT8
//

#if (G81PL != 0)
//
// I2CINT1A_ISR - I2C-A
// Connected to PIEIER8_1 (use MINT8 and MG81 masks)
//
__interrupt void
I2CINT1A_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER &= MINT8;                      // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG81;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G82PL != 0)
//
// I2CINT2A_ISR - I2C-A
// Connected to PIEIER8_2 (use MINT8 and MG82 masks)
//
__interrupt void
I2CINT2A_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER &= MINT8;                      // Set "global" priority
    PieCtrlRegs.PIEIER6.all &= MG82;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G85PL != 0)
//
// SCIRXINTC_ISR - SCI-C
// Connected to PIEIER8_5 (use MINT8 and MG85 masks)
//
__interrupt void
SCIRXINTC_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER &= MINT8;                      // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG85;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G86PL != 0)
//
// SCITXINTC_ISR - SCI-C
// Connected to PIEIER8_6 (use MINT8 and MG86 masks):
//
__interrupt void
SCITXINTC_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER8.all;
    IER |= M_INT8;
    IER &= MINT8;                      // Set "global" priority
    PieCtrlRegs.PIEIER8.all &= MG86;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G91PL != 0)
//
// SCIRXINTA_ISR - SCI-A3
// Connected to PIEIER9_1 (use MINT9 and MG91 masks)
//
__interrupt void
SCIRXINTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                       // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG91;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G92PL != 0)
//
// SCITXINTA_ISR - SCI-A
// Connected to PIEIER9_2 (use MINT9 and MG92 masks)
//
__interrupt void
SCITXINTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                      // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG92;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G93PL != 0)
//
// SCIRXINTB_ISR - SCI-B
// Connected to PIEIER9_3 (use MINT9 and MG93 masks)
//
__interrupt void
SCIRXINTB_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                      // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG93;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G94PL != 0)
//
// SCITXINTB_ISR - SCI-B
// Connected to PIEIER9_4 (use MINT9 and MG94 masks):
//
__interrupt void
SCITXINTB_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                      // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG94;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G95PL != 0)
//
// ECAN0INTA_ISR - eCAN-A
// Connected to PIEIER9_5 (use MINT9 and MG95 masks)
//
__interrupt void
ECAN0INTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                      // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG95;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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

#if (G96PL != 0)
//
// ECAN1INTA_ISR - eCAN-A
// Connected to PIEIER9_6 (use MINT9 and MG96 masks)
//
__interrupt void
ECAN1INTA_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER9.all;
    IER |= M_INT9;
    IER &= MINT9;                      // Set "global" priority
    PieCtrlRegs.PIEIER9.all &= MG96;   // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
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
// Uncomment the below if ADCINT1 and ADCINT2 in the 10.1 and 10.2
// PIE interrupt spaces are enabled. Then comment out the equivalent
// 1.1 and 1.2 interrupt service routines.
//

/*
#if (G101PL != 0)
//
// ADCINT1_ISR -  ADC
// Connected to PIEIER10_1 (use MINT10 and MG101 masks)
//
__interrupt void
ADCINT1_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG101; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G102PL != 0)
//
// ADCINT2_ISR - ADC
// Connected to PIEIER10_2 (use MINT10 and MG102 masks)
//
__interrupt void
ADCINT2_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG102; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

*/

#if (G103PL != 0)
//
// ADCINT3_ISR - ADC
// Connected to PIEIER10_3 (use MINT10 and MG103 masks)
//
__interrupt void
ADCINT3_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG103; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G104PL != 0)
//
// ADCINT4_ISR - ADC
// Connected to PIEIER10_4 (use MINT10 and MG104 masks):
//
__interrupt void
ADCINT4_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG104; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G105PL != 0)
//
// ADCINT5_ISR - ADC
// Connected to PIEIER10_5 (use MINT10 and MG105 masks):
//
__interrupt void
ADCINT5_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG105; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G106PL != 0)
//
// ADCINT6_ISR - ADC
// Connected to PIEIER10_6 (use MINT10 and MG106 masks)
//
__interrupt void
ADCINT6_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER &= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG106; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G107PL != 0)
//
// ADCINT7_ISR - ADC
// Connected to PIEIER10_7 (use MINT10 and MG107 masks):
//
__interrupt void
ADCINT7_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER &= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG107; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G108PL != 0)
//
// ADCINT8_ISR - ADC
// Connected to PIEIER10_8 (use MINT10 and MG108 masks)
//
__interrupt void
ADCINT8_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER10.all;
    IER |= M_INT10;
    IER &= MINT10;                     // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG108; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER10.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif


//
// PIE Group 11 - MUXed into CPU INT11
//

#if (G111PL != 0)
//
// CLA1_INT1_ISR - CLA1
// Connected to PIEIER11_1 (use MINT11 and MG111 masks)
//
__interrupt void
CLA1_INT1_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG111; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G112PL != 0)
//
// CLA1_INT2_ISR - CLA1
// Connected to PIEIER11_2 (use MINT11 and MG112 masks):
//
__interrupt void
CLA1_INT2_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG112; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G113PL != 0)
//
// CLA1_INT3_ISR - CLA1
// Connected to PIEIER11_3 (use MINT11 and MG113 masks)
//
__interrupt void
CLA1_INT3_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG113; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G114PL != 0)
//
// CLA1_INT4_ISR - CLA1
// Connected to PIEIER11_4 (use MINT11 and MG114 masks):
//
__interrupt void
CLA1_INT4_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG114; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G115PL != 0)
//
// CLA1_INT5_ISR - CLA1
// Connected to PIEIER11_5 (use MINT11 and MG115 masks)
//
__interrupt void
CLA1_INT5_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG115; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G116PL != 0)
//
// CLA1_INT6_ISR - CLA1
// Connected to PIEIER11_6 (use MINT11 and MG116 masks):
//
__interrupt void
CLA1_INT6_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER &= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG116; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G117PL != 0)
//
// CLA1_INT7_ISR - CLA1
// Connected to PIEIER11_7 (use MINT11 and MG117 masks)
//
__interrupt void
CLA1_INT7_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER &= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG117; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

#if (G118PL != 0)
//
// CLA1_INT8_ISR - CLA1
// Connected to PIEIER11_8 (use MINT11 and MG118 masks):
//
__interrupt void
CLA1_INT8_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER11.all;
    IER |= M_INT11;
    IER &= MINT11;                     // Set "global" priority
    PieCtrlRegs.PIEIER11.all &= MG118; // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;   // Enable PIE __interrupts
    EINT;

    //
    // Insert ISR Code here
    //

    //
    // Restore registers saved
    //
    DINT;
    PieCtrlRegs.PIEIER11.all = TempPIEIER;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}
#endif

//
// PIE Group 12 - MUXed into CPU INT12
//

#if (G121PL != 0)
//
// XINT3_ISR - External interrupt
// Connected to PIEIER12_1 (use MINT12 and MG121 masks)
//
__interrupt void
XINT3_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER &= MINT12;                      // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG121;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G127PL != 0)
//
// LVF_ISR - CLA1
// Connected to PIEIER12_7 (use MINT12 and MG127 masks)
//
__interrupt void
LVF_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER &= MINT12;                      // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG127;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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

#if (G128PL != 0)
//
// LUF_ISR - CLA1
// Connected to PIEIER12_8 (use MINT12 and MG128 masks)
//
__interrupt void
LUF_ISR(void)
{
    //
    // Set __interrupt priority
    //
    volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER12.all;
    IER |= M_INT12;
    IER &= MINT12;                      // Set "global" priority
    PieCtrlRegs.PIEIER12.all &= MG128;  // Set "group"  priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;    // Enable PIE __interrupts
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
__interrupt void
PIE_RESERVED(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// INT_NOTUSED_ISR - Reserved space.  For test.
//
__interrupt void
INT_NOTUSED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

__interrupt void
rsvd_ISR(void)      // For test
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of file.
//

