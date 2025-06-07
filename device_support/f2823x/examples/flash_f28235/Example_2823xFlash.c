//###########################################################################
//
// FILE:	Example_2823xFlash.c
//
// TITLE:	ePWM Timer Interrupt From Flash Example
//
//! \addtogroup f2823x_example_list
//! <h1>ePWM Timer Interrupt From Flash (flash_f28235)</h1>
//!
//! This example runs the ePWM interrupt example from flash. ePwm1 Interrupt
//! will run from RAM and puts the flash into sleep mode. ePwm2 Interrupt
//! will run from RAM and puts the flash into standby mode. ePWM3 Interrupt
//! will run from FLASH. All timers have the same period. The timers are
//! started sync'ed. An interrupt is taken on a zero event for each ePWM
//! timer.GPIO32 is toggled while in the background loop.\n
//! \b Note:
//!   - ePWM1: takes an interrupt every event
//!   - ePWM2: takes an interrupt every 2nd event
//!   - ePWM3: takes an interrupt every 3rd event
//!
//! Thus the Interrupt count for ePWM1, ePWM4-ePWM6 should be equal
//! The interrupt count for ePWM2 should be about half that of ePWM1
//! and the interrupt count for ePWM3 should be about 1/3 that of ePWM1
//!
//! Follow these steps to run the program.
//!   - Build the project
//!   - Flash the .out file into the device.
//!   - Set the hardware jumpers to boot to Flash
//!   - Use the included GEL file to load the project, symbols
//!     defined within the project and the variables into the watch
//!     window.
//!
//! Steps that were taken to convert the ePWM example from RAM
//! to Flash execution:
//! - Change the linker cmd file to reflect the flash memory map.
//! - Make sure any initialized sections are mapped to Flash.
//! In SDFlash utility this can be checked by the View->Coff/Hex
//! status utility. Any section marked as "load" should be
//! allocated to Flash.
//! - Make sure there is a branch instruction from the entry to Flash
//! at 0x33FFF6 to the beginning of code execution. This example
//! uses the DSP2823x_CodeStartBranch.__asm file to accomplish this.
//! - Set boot mode Jumpers to "boot to Flash"
//! - For best performance from the flash, modify the waitstates
//! and enable the flash pipeline as shown in this example.
//! Note: any code that manipulates the flash waitstate and pipeline
//! control must be run from RAM. Thus these functions are located
//! in their own memory section called ramfuncs.
//!
//! \b Watch \b Variables \n
//!  - EPwm1TimerIntCount
//!  - EPwm2TimerIntCount
//!  - EPwm3TimerIntCount
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
#include <string.h>

//
// Defines that configure which ePWM timer interrupts are enabled at 
// the PIE level: 1 = enabled,  0 = disabled
//
#define PWM1_INT_ENABLE  1
#define PWM2_INT_ENABLE  1
#define PWM3_INT_ENABLE  1

//
// Defines for the period for each timer
//
#define PWM1_TIMER_TBPRD   0x1FFF
#define PWM2_TIMER_TBPRD   0x1FFF
#define PWM3_TIMER_TBPRD   0x1FFF

//
// Make this long enough so that we can see an LED toggle
//
#define DELAY 1000000L

//
// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped using
// the linker cmd file.
//
#pragma CODE_SECTION(epwm1_timer_isr, "ramfuncs");
#pragma CODE_SECTION(epwm2_timer_isr, "ramfuncs");

//
// Function Prototypes
//
__interrupt void epwm1_timer_isr(void);
__interrupt void epwm2_timer_isr(void);
__interrupt void epwm3_timer_isr(void);
void InitEPwmTimer(void);

//
// Globals
//
Uint32  EPwm1TimerIntCount;
Uint32  EPwm2TimerIntCount;
Uint32  EPwm3TimerIntCount;
Uint32  LoopCount;

//
// These are defined by the linker (see F28235.cmd)
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadSize;

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2823x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2823x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2823x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2823x_DefaultIsr.c.
    // This function is found in DSP2823x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;          // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    PieVectTable.EPWM2_INT = &epwm2_timer_isr;
    PieVectTable.EPWM3_INT = &epwm3_timer_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2823x_InitPeripherals.c
    //
    //InitPeripherals();  // Not required for this example
    InitEPwmTimer();    // For this example, only initialize the ePWM Timers

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Copy time critical code and Flash setup code to RAM
    // This includes the following ISR functions: epwm1_timer_isr(), 
    // epwm2_timer_isr(), epwm3_timer_isr and and InitFlash();
    // The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the F28235.cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    InitFlash();

    //
    // Initialize counters
    //
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;
    LoopCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT
    //
    IER |= M_INT3;

    //
    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
    //
    PieCtrlRegs.PIEIER3.bit.INTx1 = PWM1_INT_ENABLE;
    PieCtrlRegs.PIEIER3.bit.INTx2 = PWM2_INT_ENABLE;
    PieCtrlRegs.PIEIER3.bit.INTx3 = PWM3_INT_ENABLE;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
    EDIS;

    for(;;)
    {
        //
        // This loop will be interrupted, so the overall
        // delay between pin toggles will be longer.
        //
        DELAY_US(DELAY);
        LoopCount++;
        GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;
    }
}

//
// InitEPwmTimer -
//
void 
InitEPwmTimer()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    //
    // Setup Sync
    //
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through

    //
    // Allow each timer to be sync'ed
    //
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;

    EPwm1Regs.TBPHS.half.TBPHS = 100;
    EPwm2Regs.TBPHS.half.TBPHS = 200;
    EPwm3Regs.TBPHS.half.TBPHS = 300;

    EPwm1Regs.TBPRD = PWM1_TIMER_TBPRD;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = PWM1_INT_ENABLE;  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event


    EPwm2Regs.TBPRD = PWM2_TIMER_TBPRD;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = PWM2_INT_ENABLE;   // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_2ND;            // Generate INT on 2nd event


    EPwm3Regs.TBPRD = PWM3_TIMER_TBPRD;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Enable INT on Zero event
    EPwm3Regs.ETSEL.bit.INTEN = PWM3_INT_ENABLE;  // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;       // Start all the timers synced
    EDIS;
}

//
// epwm1_timer_isr -This ISR MUST be executed from RAM as it will put the Flash
// into Sleep Interrupt routines uses in this example
//
__interrupt void 
epwm1_timer_isr(void)
{
    //
    // Put the Flash to sleep
    //
    EALLOW;
    FlashRegs.FPWR.bit.PWR = FLASH_SLEEP;
    EDIS;
    EPwm1TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm2_timer_isr - This ISR MUST be executed from RAM as it will put the 
// Flash into Standby
//
__interrupt void 
epwm2_timer_isr(void)
{
    EPwm2TimerIntCount++;

    //
    // Put the Flash into standby
    //
    EALLOW;
    FlashRegs.FPWR.bit.PWR = FLASH_STANDBY;
    EDIS;
    
    //
    // Clear INT flag for this timer
    //
    EPwm2Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm3_timer_isr -
//
__interrupt void 
epwm3_timer_isr(void)
{
    Uint16 i;

    EPwm3TimerIntCount++;

    //
    // Short Delay to simulate some ISR Code
    //
    for(i = 1; i < 0x01FF; i++)
    {
        
    }

    //
    // Clear INT flag for this timer
    //
    EPwm3Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// End of File
//

