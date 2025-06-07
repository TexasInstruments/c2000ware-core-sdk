//###########################################################################
//
// FILE:    Example_F2802x0SWPrioritizedDefaultIsr.c
//
// TITLE:   F2802x0 Device Default Software Prioritized Interrupt Service 
//          Routines.
//
//          This file is based on the standard 
//          F2802x0_SWPrioritizedDefaultIsr.c. The ISR routines have been 
//          modified slightly to provide a trace mechanism used for 
//          this example
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "common/include/f2802x0_swprioritizedisrlevels.h"

#include "common/include/cpu.h"
#include "common/include/pie.h"

//
// Defined in the Example_28xSWPrioritizedInterrupts.c file
// for this example only
//
extern uint16_t ISRTrace[50];
extern uint16_t ISRTraceIndex;
extern CPU_Handle myCpu;
extern PIE_Handle myPie;

//
// Global used for ISR delays
//
uint16_t i;

//
// INT13_ISR - INT13 or CPU-Timer1 is connected to INT13/TINT1 of CPU 
// (use MINT13 mask)
//
#if (INT13PL != 0)
__interrupt void
INT13_ISR(void)
{
    IER |= MINT13;                 // Set "global" priority
    CPU_enableGlobalInts(myCpu);

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
// INT14_ISR - CPU-Timer2 is connected to INT14/TINT2 of CPU (use MINT14 mask)
//
#if (INT14PL != 0)
__interrupt void
INT14_ISR(void)
{
    IER |= MINT14;                 // Set "global" priority
    CPU_enableGlobalInts(myCpu);

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
// DATALOG_ISR - Datalogging interrupt is connected to INT15 of CPU 
// (use MINT15 mask)
//
#if (INT15PL != 0)
__interrupt void
DATALOG_ISR(void)
{
    IER |= MINT15;                 // Set "global" priority
    CPU_enableGlobalInts(myCpu);

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
// RTOSINT_ISR - RTOS interrupt is connected to INT16 of CPU (use MINT16 mask)
//
#if (INT16PL != 0)
__interrupt void
RTOSINT_ISR(void)
{
    IER |= MINT16;                 // Set "global" priority
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
// ILLEGAL_ISR - Illegal operation TRAP is connected to ITRAP of 
// CPU (non-maskable)
//
__interrupt void
ILLEGAL_ISR(void)
{
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
    CPU_enableGlobalInts(myCpu);

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
// ADCINT1_ISR - ADC is connected to PIEIER1_1 (use MINT1 and MG11 masks)
//
#if (G11PL != 0)
__interrupt void
ADCINT1_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG11);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0011;
    ISRTraceIndex++;
}
#endif

//
// ADCINT2_ISR - ADC is connected to PIEIER1_2 (use MINT1 and MG12 masks)
//
#if (G12PL != 0)
__interrupt void
ADCINT2_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG12);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority

    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG14);

    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    __asm("      NOP");

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG15);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0015;
    ISRTraceIndex++;
}
#endif

//
// ADCINT9_ISR - ADC is connected to PIEIER1_6 (use MINT1 and MG16 masks)
//
#if (G16PL != 0)
__interrupt void
ADCINT9_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG16);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG17);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT1);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) ~MG18);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)TempPIEIER);

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
// EPWM1_TZINT_ISR - EPwm1 Trip Zone is connected to PIEIER2_1 
// (use MINT2 and MG21 masks)
//
#if (G21PL != 0)
__interrupt void
EPWM1_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT2); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) ~MG21);
    
    PIE_clearAllInts(myPie);             // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0021;
    ISRTraceIndex++;
}
#endif

//
// EPWM2_TZINT_ISR - EPwm2 Trip Zone is connected to PIEIER2_2
// (use MINT2 and MG22 masks)
//
#if (G22PL != 0)
__interrupt void
EPWM2_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT2);   // Set "global" priority

    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) ~MG22);

    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0022;
    ISRTraceIndex++;
}
#endif

//
// EPWM3_TZINT_ISR - EPwm3 Trip Zone is connected to PIEIER2_3
// (use MINT2 and MG23 masks)
//
#if (G23PL != 0)
__interrupt void
EPWM3_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT2);   // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) ~MG23);
    
    PIE_clearAllInts(myPie);                    // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0023;
    ISRTraceIndex++;
}
#endif

//
// EPWM4_TZINT_ISR - EPwm4 Trip Zone is connected to PIEIER2_4 
// (use MINT2 and MG24 masks)
//
#if (G24PL != 0)
__interrupt void
EPWM4_TZINT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT2);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) ~MG24);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0024;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - EPwm1 Interrupt is connected to PIEIER3_1
// (use MINT3 and MG31 masks)
//
#if (G31PL != 0)
__interrupt void
EPWM1_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_3);
    CPU_enableInt(myCpu, CPU_IntNumber_3);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT3);  // Set "global" priority

    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) ~MG31);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0031;
    ISRTraceIndex++;
}
#endif

//
// EPWM2_INT_ISR - EPwm2 Interrupt is connected to PIEIER3_2
// (use MINT3 and MG32 masks)
//
#if (G32PL != 0)
__interrupt void
EPWM2_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_3);
    CPU_enableInt(myCpu, CPU_IntNumber_3);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT3);   // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) ~MG32);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0032;
    ISRTraceIndex++;
}
#endif

//
// EPWM3_INT_ISR - EPwm3 Interrupt is connected to PIEIER3_3
// (use MINT3 and MG33 masks)
//
#if (G33PL != 0)
__interrupt void
EPWM3_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_3);
    CPU_enableInt(myCpu, CPU_IntNumber_3);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT3);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) ~MG33);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0033;
    ISRTraceIndex++;
}
#endif

//
// EPWM4_INT_ISR - EPwm4 Interrupt is connected to PIEIER3_4
// (use MINT3 and MG34 masks)
//
#if (G34PL != 0)
__interrupt void
EPWM4_INT_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_3);
    CPU_enableInt(myCpu, CPU_IntNumber_3);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT3);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) ~MG34);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0034;
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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_4);
    CPU_enableInt(myCpu, CPU_IntNumber_4);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT4);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e) ~MG41);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0041;
    ISRTraceIndex++;
}
#endif

// 
// PIE Group 5 - MUXed into CPU INT5
// 

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_6);
    CPU_enableInt(myCpu, CPU_IntNumber_6);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT6);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) ~MG61);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_6);
    CPU_enableInt(myCpu, CPU_IntNumber_6);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT6);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) ~MG62);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0062;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 7 - MUXed into CPU INT7
//

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - I2C-A is connected to PIEIER8_1 (use MINT8 and MG81 masks)
//
#if (G81PL != 0)
__interrupt void
I2CINT1A_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_8);
    CPU_enableInt(myCpu, CPU_IntNumber_8);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT8);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e) ~MG81);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_8);
    CPU_enableInt(myCpu, CPU_IntNumber_8);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT8);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e) ~MG82);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0082;
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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_9);
    CPU_enableInt(myCpu, CPU_IntNumber_9);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT9);  // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) ~MG91);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e)TempPIEIER);

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
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_9);
    CPU_enableInt(myCpu, CPU_IntNumber_9);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT9); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) ~MG92);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0092;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 10 - MUXed into CPU INT10
//

//
// Uncomment the below ADCINT1_ISR, and ADCINT2_ISR if the
// high priority equivalents in Group 1     are not used.
// Comment out the Group 1 equivalents in this case
//

/*
//
// ADCINT1_ISR - ADC is connected to PIEIER10_1 (use MINT10 and MG101 masks)
//
#if (G101PL != 0)
__interrupt void
ADCINT1_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority

    //
    // Set "group"  priority
    //
    PieCtrlRegs.PIEIER10.all &= MG101;

    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {

    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0101;
    ISRTraceIndex++;
}
#endif

//
// ADCINT2_ISR - ADC is connected to PIEIER10_2 (use MINT10 and MG102 masks)
//
#if (G102PL != 0)
__interrupt void
ADCINT2_ISR( void )
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    PieCtrlRegs.PIEIER10.all &= MG102;      // Set "group" priority
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0102;
    ISRTraceIndex++;
}
#endif
*/

//
// ADCINT3_ISR - ADC is connected to PIEIER10_3 (use MINT10 and MG103 masks)
//
#if (G103PL != 0)
__interrupt void
ADCINT3_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG103);
    
    PIE_clearAllInts(myPie);              // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //

    __asm("      NOP");

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0103;
    ISRTraceIndex++;
}
#endif

//
// ADCINT4_ISR - ADC is connected to PIEIER10_4 (use MINT10 and MG104 masks)
//
#if (G104PL != 0)
__interrupt void
ADCINT4_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG104);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //

    __asm("      NOP");

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0104;
    ISRTraceIndex++;
}
#endif

//
// ADCINT5_ISR - ADC is connected to PIEIER10_5 (use MINT10 and MG105 masks)
//
#if (G105PL != 0)
__interrupt void
ADCINT5_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group" priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG105);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0105;
    ISRTraceIndex++;
}
#endif

//
// ADCINT6_ISR - ADC is connected to PIEIER10_6 (use MINT10 and MG106 masks)
//
#if (G106PL != 0)
__interrupt void
ADCINT6_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG106);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0106;
    ISRTraceIndex++;
}
#endif

//
// ADCINT7_ISR - ADC is connected to PIEIER10_7 (use MINT10 and MG107 masks)
//
#if (G107PL != 0)
__interrupt void
ADCINT7_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group" priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG107);
    
    PIE_clearAllInts(myPie);            // Enable PIE interrupts
	__asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0107;
    ISRTraceIndex++;
}
#endif

//
// ADCINT8_ISR - ADC is connected to PIEIER10_8 (use MINT10 and MG108 masks)
//
#if (G108PL != 0)
__interrupt void
ADCINT8_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, PIE_GroupNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT10); // Set "global" priority
    
    //
    // Set "group"  priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) ~MG108);
    
    PIE_clearAllInts(myPie);               // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_10, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0108;
    ISRTraceIndex++;
}
#endif

//
// PIE Group 11 - MUXed into CPU INT11
//

//
// PIE Group 12 - MUXed into CPU INT12
//

//
// XINT3_ISR - XINT3 is connected to PIEIER12_1 (use MINT12 and MG121 masks)
//
#if (G121PL != 0)
__interrupt void
XINT3_ISR(void)
{
    //
    // Set interrupt priority
    //
    volatile uint16_t TempPIEIER = PIE_getIntEnables(myPie, 
                                                     PIE_GroupNumber_12);
    CPU_enableInt(myCpu, CPU_IntNumber_12);
    CPU_disableInt(myCpu, (CPU_IntNumber_e) ~MINT12);  // Set "global" priority
    
    //
    // Set "group" priority
    //
    PIE_disableInt(myPie, PIE_GroupNumber_12, (PIE_InterruptSource_e) ~MG121);
    
    PIE_clearAllInts(myPie);                // Enable PIE interrupts
    __asm("  NOP");
    CPU_enableGlobalInts(myCpu);

    //
    // Insert ISR Code here
    //
    for(i = 1; i <= 10; i++)
    {
        
    }

    //
    // Restore registers saved
    //
    CPU_disableGlobalInts(myCpu);
    PIE_enableInt(myPie, PIE_GroupNumber_12, 
                  (PIE_InterruptSource_e)TempPIEIER);

    //
    // Add ISR to Trace
    //
    ISRTrace[ISRTraceIndex] = 0x0121;
    ISRTraceIndex++;
}
#endif

//
// Catch All Default ISRs
//

//
// EMPTY_ISR - Empty ISR - only does a return.
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
// rsvd_ISR - For test
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

