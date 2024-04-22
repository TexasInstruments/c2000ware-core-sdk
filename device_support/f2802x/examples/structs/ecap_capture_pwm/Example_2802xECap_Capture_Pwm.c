//###########################################################################
//
// FILE:    Example_2802xECap_Capture_Pwm.c
//
// TITLE:   Capture EPwm3.
//
// ASSUMPTIONS:
//
//    This program requires the f2802x header files.
//
//    Make the following external connection:
//    EPWM3 on GPIO4 should be connected to ECAP1 on GPIO5.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait		 !=0x55AA        X
//      I/O		     0x55AA	         0x0000
//      SCI		     0x55AA	         0x0001
//      Wait 	     0x55AA	         0x0002
//      Get_Mode	 0x55AA	         0x0003
//      SPI		     0x55AA	         0x0004
//      I2C		     0x55AA	         0x0005
//      OTP		     0x55AA	         0x0006
//      Wait		 0x55AA	         0x0007
//      Wait		 0x55AA	         0x0008
//      SARAM		 0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash		 0x55AA	         0x000B
//	    Wait		 0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//
//
// DESCRIPTION:
//
//    This example configures EPWM3A for:
//    - Up count
//    - Period starts at 2 and goes up to 1000
//    - Toggle output on PRD
//
//    eCAP1 is configured to capture the time between rising
//    and falling edge of the PWM3A output.
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines that configure the start/end period for the timer
//
#define PWM3_TIMER_MIN     10
#define PWM3_TIMER_MAX     8000

//
// Function Prototypes
//
__interrupt void ecap1_isr(void);
void InitECapture(void);
void InitEPwmTimer(void);
void Fail(void);

//
// Globals
//
uint32_t  ECap1IntCount;
uint32_t  ECap1PassCount;
uint32_t  EPwm3TimerDirection;

//
// Defines that keep track of which way the timer value is moving
//
#define EPwm_TIMER_UP   1
#define EPwm_TIMER_DOWN 0

//
// Main
//
void main(void)
{
    //
    // WARNING: Always ensure you call memcpy before running any functions from
    // RAM InitSysCtrl includes a call to a RAM based function and without a 
    // call to memcpy first, the processor will go "into the weeds"
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example
    InitEPwm3Gpio();
    InitECap1Gpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
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
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;            // This is needed to write to EALLOW protected registers
    PieVectTable.ECAP1_INT = &ecap1_isr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals
    //
    InitEPwmTimer();       // For this example, only initialize the EPwm Timers
    InitECapture();

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Initialize counters
    //
    ECap1IntCount = 0;
    ECap1PassCount = 0;

    //
    // Enable CPU INT4 which is connected to ECAP1-4 INT
    //
    IER |= M_INT4;

    //
    // Enable eCAP INTn in the PIE: Group 3 interrupt 1-6
    //
    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;               // Enable Global interrupt INTM
    ERTM;               // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;)
    {
        __asm("          NOP");
    }
}

//
// InitEPwmTimer - 
//
void
InitEPwmTimer()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;  // Count up
    EPwm3Regs.TBPRD = PWM3_TIMER_MIN;
    EPwm3Regs.TBPHS.all = 0x00000000;
    EPwm3Regs.AQCTLA.bit.PRD = AQ_TOGGLE;       // Toggle on PRD

    //
    // TBCLK = SYSCLKOUT
    //
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;
    EPwm3Regs.TBCTL.bit.CLKDIV = 0;

    EPwm3TimerDirection = EPwm_TIMER_UP;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

//
// InitECapture - 
//
void
InitECapture()
{
    ECap1Regs.ECEINT.all = 0x0000;        // Disable all capture interrupts
    ECap1Regs.ECCLR.all = 0xFFFF;         // Clear all CAP interrupt flags
    ECap1Regs.ECCTL1.bit.CAPLDEN = 0;     // Disable CAP1-CAP4 register loads
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;   // Make sure the counter is stopped

    //
    // Configure peripheral registers
    //
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;    // One-shot
    ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;      // Stop at 4 events
    ECap1Regs.ECCTL1.bit.CAP1POL = 1;        // Falling edge
    ECap1Regs.ECCTL1.bit.CAP2POL = 0;        // Rising edge
    ECap1Regs.ECCTL1.bit.CAP3POL = 1;        // Falling edge
    ECap1Regs.ECCTL1.bit.CAP4POL = 0;        // Rising edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = 1;        // Difference operation
    ECap1Regs.ECCTL1.bit.CTRRST2 = 1;        // Difference operation
    ECap1Regs.ECCTL1.bit.CTRRST3 = 1;        // Difference operation
    ECap1Regs.ECCTL1.bit.CTRRST4 = 1;        // Difference operation
    ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;       // Enable sync in
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;      // Pass through
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;        // Enable capture units

    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;      // Start Counter
    ECap1Regs.ECCTL2.bit.REARM = 1;          // arm one-shot
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;        // Enable CAP1-CAP4 register loads
    ECap1Regs.ECEINT.bit.CEVT4 = 1;          // 4 events = interrupt
}

//
// ecap1_isr -
//
__interrupt void
ecap1_isr(void)
{
    //
    // Cap input is syc'ed to SYSCLKOUT so there may be
    // a +/- 1 cycle variation
    //
    if(ECap1Regs.CAP2 > EPwm3Regs.TBPRD*2+1 ||
       ECap1Regs.CAP2 < EPwm3Regs.TBPRD*2-1)
    {
        Fail();
    }

    if(ECap1Regs.CAP3 > EPwm3Regs.TBPRD*2+1 ||
       ECap1Regs.CAP3 < EPwm3Regs.TBPRD*2-1)
    {
        Fail();
    }

    if(ECap1Regs.CAP4 > EPwm3Regs.TBPRD*2+1 ||
       ECap1Regs.CAP4 < EPwm3Regs.TBPRD*2-1)
    {
        Fail();
    }

    ECap1IntCount++;

    if(EPwm3TimerDirection == EPwm_TIMER_UP)
    {
        if(EPwm3Regs.TBPRD < PWM3_TIMER_MAX)
        {
            EPwm3Regs.TBPRD++;
        }
        else
        {
            EPwm3TimerDirection = EPwm_TIMER_DOWN;
            EPwm3Regs.TBPRD--;
        }
    }
    else
    {
        if(EPwm3Regs.TBPRD > PWM3_TIMER_MIN)
        {
            EPwm3Regs.TBPRD--;
        }
        else
        {
            EPwm3TimerDirection = EPwm_TIMER_UP;
            EPwm3Regs.TBPRD++;
        }
    }

    ECap1PassCount++;

    ECap1Regs.ECCLR.bit.CEVT4 = 1;
    ECap1Regs.ECCLR.bit.INT = 1;
    ECap1Regs.ECCTL2.bit.REARM = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 4
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

//
// Fail - 
//
void
Fail()
{
    __asm("   ESTOP0");
}

//
// End of File
//

