//#############################################################################
//
//  File:   Example_F2802xCpuTimer.c
//
//  Title:  F2802x CPU Timer Example
//
//! \addtogroup example_list
//!  <h1>CPU Timer</h1>
//!
//!   This example configures CPU Timer0, 1, & 2 and increments
//!   a counter each time the timer asserts an interrupt.
//!
//!   Watch Variables:
//!   - timer0IntCount
//!   - timer1IntCount
//!   - timer2IntCount
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/timer.h"
#include "common/include/wdog.h"

//
// Function Prototypes
//
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

//
// Globals
//
unsigned long timer0IntCount;
unsigned long timer1IntCount;
unsigned long timer2IntCount;

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
TIMER_Handle myTimer0, myTimer1, myTimer2;

//
// Main
//
void main(void)
{
    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;

    //
    // Initialize all the handles needed for this application
    //
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myTimer0 = TIMER_init((void *)TIMER0_BASE_ADDR, sizeof(TIMER_Obj));
    myTimer1 = TIMER_init((void *)TIMER1_BASE_ADDR, sizeof(TIMER_Obj));
    myTimer2 = TIMER_init((void *)TIMER2_BASE_ADDR, sizeof(TIMER_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    timer0IntCount = 0;
    timer1IntCount = 0;
    timer2IntCount = 0;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    //InitSysCtrl();

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
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    //DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
    //
    //InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    //IER = 0x0000;
    //IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    //InitPieVectTable();
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;            // This is needed to write to EALLOW protected registers

    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_7, 
                              (intVec_t)&cpu_timer0_isr);
    PIE_registerSystemIntHandler(myPie, PIE_SystemInterrupts_TINT1, 
                                 (intVec_t)&cpu_timer1_isr);
    PIE_registerSystemIntHandler(myPie, PIE_SystemInterrupts_TINT2, 
                                 (intVec_t)&cpu_timer2_isr);

    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize the Device Peripheral. This function can be
    // found in f2802x_CpuTimers.c
    //
    //InitCpuTimers();   // For this example, only initialize the Cpu Timers
    TIMER_stop(myTimer0);
    TIMER_stop(myTimer1);
    TIMER_stop(myTimer2);

#if (CPU_FRQ_50MHZ)
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 50MHz CPU Freq, 1 second Period (in uSeconds)
    //
    //ConfigCpuTimer(&CpuTimer0, 50, 1000000);
    TIMER_setPeriod(myTimer0, 50 * 1000000);
    //ConfigCpuTimer(&CpuTimer1, 50, 1000000);
    TIMER_setPeriod(myTimer1, 50 * 1000000);
    //ConfigCpuTimer(&CpuTimer2, 50, 1000000);
    TIMER_setPeriod(myTimer2, 50 * 1000000);
#endif
#if (CPU_FRQ_40MHZ)
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 40MHz CPU Freq, 1 second Period (in uSeconds)
    //
    //ConfigCpuTimer(&CpuTimer0, 40, 1000000);
    TIMER_setPeriod(myTimer0, 40 * 1000000);
    //ConfigCpuTimer(&CpuTimer1, 40, 1000000);
    TIMER_setPeriod(myTimer1, 40 * 1000000);
    //ConfigCpuTimer(&CpuTimer2, 40, 1000000);
    TIMER_setPeriod(myTimer2, 40 * 1000000);
#endif

    TIMER_setPreScaler(myTimer0, 0);
    TIMER_reload(myTimer0);
    TIMER_setEmulationMode(myTimer0, 
                           TIMER_EmulationMode_StopAfterNextDecrement);
    TIMER_enableInt(myTimer0);

    TIMER_setPreScaler(myTimer1, 0);
    TIMER_reload(myTimer1);
    TIMER_setEmulationMode(myTimer1, 
                           TIMER_EmulationMode_StopAfterNextDecrement);
    TIMER_enableInt(myTimer1);

    TIMER_setPreScaler(myTimer2, 0);
    TIMER_reload(myTimer2);
    TIMER_setEmulationMode(myTimer2, 
                           TIMER_EmulationMode_StopAfterNextDecrement);
    TIMER_enableInt(myTimer2);

    //
    // To ensure precise timing, use write-only instructions to write to the 
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers (in f2802x_CpuTimers.h), the
    // below settings must also be updated.
    //
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    //CpuTimer0Regs.TCR.all = 0x4001;
    TIMER_start(myTimer0);
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    //CpuTimer1Regs.TCR.all = 0x4001;
    TIMER_start(myTimer1);
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    //CpuTimer2Regs.TCR.all = 0x4001;
    TIMER_start(myTimer2);

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int 14, which is connected
    // to CPU-Timer 2
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_enableInt(myCpu, CPU_IntNumber_13);
    CPU_enableInt(myCpu, CPU_IntNumber_14);

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PIE_enableTimer0Int(myPie);

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    CPU_enableGlobalInts(myCpu);       // Enable Global interrupt INTM
    CPU_enableDebugInt(myCpu);         // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;);
}

//
// cpu_timer0_isr - 
//
__interrupt void
cpu_timer0_isr(void)
{
    timer0IntCount++;

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

//
// cpu_timer1_isr - 
//
__interrupt void
cpu_timer1_isr(void)
{
    timer1IntCount++;
}

//
// cpu_timer2_isr - 
//
__interrupt void
cpu_timer2_isr(void)
{
    timer2IntCount++;
}

//
// End of File
//

