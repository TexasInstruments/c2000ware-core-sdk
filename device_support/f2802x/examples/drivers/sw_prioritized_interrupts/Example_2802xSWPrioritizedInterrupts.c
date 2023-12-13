//#############################################################################
//
//  File:   Example_F2802xSWPrioritizedInterrupts.c
//
//  Title:  F2802x Software Prioritized Interrupt Example.
//
//! \addtogroup example_list
//!  <h1>Software Prioritized Interrupts</h1>
//!
//!   For most applications, the hardware prioritization of the
//!   the PIE module is sufficient.  For applications that need custom
//!   prioritization, this example illustrates an example of
//!   how this can be done through software.
//!
//!   For more information on F2802x interrupt priorities, refer to the
//!   Software ISR Priorities section of the firmware examples guide document
//!   included with the F2802x/doc directory.
//!
//!   This program simulates interrupt conflicts by writing to the
//!   PIEIFR registers.  This will simulate multiple interrupts coming into
//!   the PIE block at the same time.
//!
//!   The interrupt service routine routines are software prioritized
//!   by the table found in the F2802x_SWPrioritizedIsrLevels.h file.
//!
//!   -# Before compiling you must set the Global and Group interrupt 
//!         priorities in the F2802x_SWPrioritizedIsrLevels.h file.
//!   -# Set the #define CASE directive at the top of the code in this file
//!         to determine which test case to run
//!   -# Compile the code, load, and run
//!   -# At the end of each test there is a hard coded breakpoint (ESTOP0).  
//!         When code stops at the breakpoint, examine the ISRTrace buffer to 
//!         see the order in which the ISR's completed. All PIE interrupts will 
//!         add to the ISRTrace. \n
//!   -# If desired, set a new set of Global and Group interrupt priorities
//!         and repeat the test to see the change.
//!
//!   Watch Variables:
//!   - ISRTrace[50] - Trace of ISR's in the order they complete
//!                    After each test, examine this buffer
//!                    to determine if the ISR's completed in
//!                    the order desired. The ISRTrace will consist of a list 
//!                    of hex values as shown: \n
//!      0x00wx    <- PIE Group w interrupt x finished first \n
//!      0x00yz    <- PIE Group y interrupt z finished next
//
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "common/include/f2802x_swprioritizedisrlevels.h"

#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/cpu.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/wdog.h"

//
// Defines
//
#define CASE 1

//
// Defines for the interrupts used in the PIE for each group
//
#define ISRS_GROUP1  (M_INT1|M_INT2|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP2  (M_INT1|M_INT2|M_INT3|M_INT4)
#define ISRS_GROUP3  (M_INT1|M_INT2|M_INT3|M_INT4)
#define ISRS_GROUP4  (M_INT1)
#define ISRS_GROUP6  (M_INT1|M_INT2)
#define ISRS_GROUP8  (M_INT1|M_INT2)
#define ISRS_GROUP9  (M_INT1|M_INT2)

//
// If M_INT1,M_INT2 are available in Group 10, delete them in Group 1
//
#define ISRS_GROUP10 (M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)

#define ISRS_GROUP12 (M_INT1)

//
// This array will be used as a trace to check the order that the
// interrupts were serviced
//
uint16_t  ISRTrace[50];
uint16_t  ISRTraceIndex;       // used to update an element in the trace buffer

ADC_Handle myAdc;
CLK_Handle myClk;
CPU_Handle myCpu;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

//
// Main
//
void main(void)
{
    uint16_t i;

    PLL_Handle myPll;
    WDOG_Handle myWDog;

    //
    // Initialize all the handles needed for this application
    //
    myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    //
    // Perform basic system initialization    
    //
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();

    //
    // Select the internal oscillator 1 as the clock source
    //
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);

    //
    // Setup the PLL for x10 /2 which will yield 50Mhz = 10Mhz * 10 / 2
    //
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);

    //
    // Disable the PIE and all interrupts
    //
    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // If running from flash copy RAM only functions to RAM
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif   

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);

    //
    // CASE 1:
    //
#if (CASE==1)
    //
    // Force all group 1 interrupts at once by writing to the PIEIFR1 register
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 1 interrupt 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 1 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);

    //
    // Enable CPU INT1
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);

    //
    // Force all valid interrupts for Group 1
    //
    PIE_forceInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_ADCINT_1_1 | 
                 PIE_InterruptSource_ADCINT_1_2 | PIE_InterruptSource_XINT_1 | 
                 PIE_InterruptSource_XINT_2 | PIE_InterruptSource_ADCINT_9 | 
                 PIE_InterruptSource_TIMER_0 | PIE_InterruptSource_WAKE));

    //
    // Enable global Interrupts CPU level
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all Group 1 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_1) != 0x0000)
    {
        
    }

    //
    // Stop here and check the ISRTrace to determine which order the
    // ISR Routines completed.  The order is dependant on the priority
    // assigned in the F2802x_SWPrioritizedIsrLevels.h file
    //
    // The ISRTrace will contain a list of values corresponding to the
    // interrupts serviced in the order they were serviced.
    // For example if the ISRTrace looks like this
    //        0x0014     ISR Group 1 interrupt 4
    //        0x0017     ISR Group 1 interrupt 7
    //        0x0016     ISR Group 1 interrupt 6
    //        0x0015     ISR Group 1 interrupt 5
    //        0x0018     ISR Group 1 interrupt 8
    //        0x0012     ISR Group 1 interrupt 2
    //        0x0011     ISR Group 1 interrupt 1
    //        0x0000     end of trace
    //
    __asm("        ESTOP0");

    //
    // CASE 2
    //
#elif (CASE==2)
    //
    // Force all group 2 interrupts at once by writing to the PIEIFR2 register
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++) ISRTrace[i] = 0;
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 2 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) 0x00FF);

    //
    // Enable CPU INT2
    //
    CPU_enableInt(myCpu, CPU_IntNumber_2);

    //
    // Make sure PIEACK for group 2 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_2);

    //
    // Force all valid interrupts for Group 2
    //
    PIE_forceInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_TZ1 | PIE_InterruptSource_TZ2 | 
                 PIE_InterruptSource_TZ3));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 2 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_2) != 0x0000)
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");


    //
    // CASE 3:
    //
#elif (CASE==3)
    //
    // Force all group 3 interrupts at once by writing to the PIEIFR3 register
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 3 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 3 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_3);

    //
    // Enable CPU INT3
    //
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    //
    // Force all valid interrupts for Group 3
    //
    PIE_forceInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_EPWM1 | PIE_InterruptSource_EPWM2 | 
                 PIE_InterruptSource_EPWM3));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 3 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_3) != 0x0000)
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 4
    //
#elif (CASE==4)
    //
    // Force all group 4 interrupts at once by writing to the PIEIFR4 register
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 4 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 3 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_4);

    //
    // Enable CPU INT4
    //
    CPU_enableInt(myCpu, CPU_IntNumber_4);

    //
    // Force all valid interrupts for Group 4
    //
    PIE_forceInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e) 
                 PIE_InterruptSource_ECAP1);

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 4 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_4) != 0x0000)
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 5
    //
#elif (CASE==5)
    //
    // Force all group 6 interrupts at once by writing to the PIEIFR6 register
    //

    //
    // Prepare for the test
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 6 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 6 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_6);

    //
    // Enable CPU INT6
    //
    CPU_enableInt(myCpu, CPU_IntNumber_6);

    //
    // Force all valid interrupts for Group 6
    //
    PIE_forceInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_SPIARX | PIE_InterruptSource_SPIATX));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 6 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_6) != 0x0000)
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 6
    //
#elif (CASE==6)
    //
    // Force all group 9 interrupts at once by writing to the PIEIFR4 register
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 9 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 9 is clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_9);

    //
    // Enable CPU INT9
    //
    CPU_enableInt(myCpu, CPU_IntNumber_9);

    //
    // Force all valid interrupts for Group 9
    //
    PIE_forceInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_SCIARX | PIE_InterruptSource_SCIATX));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 9 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_9) != 0x0000)
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 7
    //
#elif (CASE==7)
    //
    // Force all group 1 and group 2 interrupts at once
    //

    //
    // Setup next test - fire interrupts from Group 1 and Group 2
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 1 and group 2 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 1 & 2 are clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
    PIE_clearInt(myPie, PIE_GroupNumber_2);

    //
    // Enable CPU INT1 and INT2
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    
    //
    // Force all valid interrupts for Group 1 and from Group 2
    //
    PIE_forceInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_ADCINT_1_1 | 
                 PIE_InterruptSource_ADCINT_1_2 | PIE_InterruptSource_XINT_1 | 
                 PIE_InterruptSource_XINT_2 | PIE_InterruptSource_ADCINT_9 | 
                 PIE_InterruptSource_TIMER_0 | PIE_InterruptSource_WAKE));
    PIE_forceInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_TZ1 | PIE_InterruptSource_TZ2 | 
                 PIE_InterruptSource_TZ3));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 1 and group 2 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_1) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_2) != 0x0000)
    {
        
    }

    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");

    //
    // CASE 8
    //
#elif (CASE==8)
    //
    // Force all group 1 and group 2 and group 3 interrupts at once
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable PIE group 1, 2 and 3 interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 1, 2 & 3 are clear (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
    PIE_clearInt(myPie, PIE_GroupNumber_2);
    PIE_clearInt(myPie, PIE_GroupNumber_3);

    //
    // Enable CPU INT1, INT2 & INT3
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    //
    // Force all valid interrupts for Group1, 2 and 3
    //
    PIE_forceInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_ADCINT_1_1 | 
                 PIE_InterruptSource_ADCINT_1_2 | PIE_InterruptSource_XINT_1 | 
                 PIE_InterruptSource_XINT_2 | PIE_InterruptSource_ADCINT_9 | 
                 PIE_InterruptSource_TIMER_0 | PIE_InterruptSource_WAKE));
    PIE_forceInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_TZ1 | PIE_InterruptSource_TZ2 | 
                 PIE_InterruptSource_TZ3));
    PIE_forceInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_EPWM1 | PIE_InterruptSource_EPWM2 | 
                 PIE_InterruptSource_EPWM3));

    //
    // Enable Global interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group 1 and group 2 and group 3 interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_1) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_2) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_3) != 0x0000)
    {
        
    }

    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");

    //
    // CASE 9
    //
#elif (CASE==9)
    //
    // Force all used PIE interrupts at once
    //

    //
    // Prepare for the test:
    // Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
    //
    CPU_disableGlobalInts(myCpu);
    for(i = 0; i < 50; i++)
    {
        ISRTrace[i] = 0;
    }
    ISRTraceIndex = 0;
    PIE_clearAllFlags(myPie);
    PIE_clearAllFlags(myPie);
    CPU_disableInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // Enable the PIE block
    //
    PIE_enable(myPie);

    //
    // Enable all PIE group interrupts 1-8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) 0x00FF);
    PIE_enableInt(myPie, PIE_GroupNumber_12, (PIE_InterruptSource_e) 0x00FF);

    //
    // Make sure PIEACK for group 1, 2, 3, 4, 6, 8, 9, 10, and 12 are clear 
    // (default after reset)
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
    PIE_clearInt(myPie, PIE_GroupNumber_2);
    PIE_clearInt(myPie, PIE_GroupNumber_3);
    PIE_clearInt(myPie, PIE_GroupNumber_4);
    PIE_clearInt(myPie, PIE_GroupNumber_6);
    PIE_clearInt(myPie, PIE_GroupNumber_8);
    PIE_clearInt(myPie, PIE_GroupNumber_9);
    PIE_clearInt(myPie, PIE_GroupNumber_10);
    PIE_clearInt(myPie, PIE_GroupNumber_12);

    //
    // Enable CPU INT1, INT2, INT3, INT4, INT6, INT8, INT9, INT10, and INT12
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_2);
    CPU_enableInt(myCpu, CPU_IntNumber_3);
    CPU_enableInt(myCpu, CPU_IntNumber_4);
    CPU_enableInt(myCpu, CPU_IntNumber_6);
    CPU_enableInt(myCpu, CPU_IntNumber_8);
    CPU_enableInt(myCpu, CPU_IntNumber_9);
    CPU_enableInt(myCpu, CPU_IntNumber_10);
    CPU_enableInt(myCpu, CPU_IntNumber_12);

    //
    // Force all valid interrupts for all PIE groups
    //
    PIE_forceInt(myPie, PIE_GroupNumber_1, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_ADCINT_1_1 | 
                 PIE_InterruptSource_ADCINT_1_2 | PIE_InterruptSource_XINT_1 | 
                 PIE_InterruptSource_XINT_2 | PIE_InterruptSource_ADCINT_9 | 
                 PIE_InterruptSource_TIMER_0 | PIE_InterruptSource_WAKE));
    PIE_forceInt(myPie, PIE_GroupNumber_2, (PIE_InterruptSource_e)
                 (PIE_InterruptSource_TZ1 | PIE_InterruptSource_TZ2 | 
                 PIE_InterruptSource_TZ3));
    PIE_forceInt(myPie, PIE_GroupNumber_3, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_EPWM1 | PIE_InterruptSource_EPWM2 | 
                 PIE_InterruptSource_EPWM3));
    PIE_forceInt(myPie, PIE_GroupNumber_4, (PIE_InterruptSource_e) 
                 PIE_InterruptSource_ECAP1);
    PIE_forceInt(myPie, PIE_GroupNumber_6, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_SPIARX | PIE_InterruptSource_SPIATX));
    PIE_forceInt(myPie, PIE_GroupNumber_8, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_I2CA1 | PIE_InterruptSource_I2CA2));
    PIE_forceInt(myPie, PIE_GroupNumber_9, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_SCIARX | PIE_InterruptSource_SCIATX));
    PIE_forceInt(myPie, PIE_GroupNumber_10, (PIE_InterruptSource_e) 
                 (PIE_InterruptSource_ADCINT_3 | PIE_InterruptSource_ADCINT_4 |
                 PIE_InterruptSource_ADCINT_5 | PIE_InterruptSource_ADCINT_6 | 
                 PIE_InterruptSource_ADCINT_7 | PIE_InterruptSource_ADCINT_8));
    PIE_forceInt(myPie, PIE_GroupNumber_12, (PIE_InterruptSource_e) 
                 PIE_InterruptSource_XINT_3);

    //
    // Enable Global interrupts - CPU level
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Wait for all group interrupts to be serviced
    //
    while(PIE_getIntFlags(myPie, PIE_GroupNumber_1) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_2) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_3) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_4) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_5) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_8) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_9) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_10) != 0x0000 || 
          PIE_getIntFlags(myPie, PIE_GroupNumber_12) != 0x0000)
    {
        
    }

    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");
    #endif
}

//
// End of File
//

