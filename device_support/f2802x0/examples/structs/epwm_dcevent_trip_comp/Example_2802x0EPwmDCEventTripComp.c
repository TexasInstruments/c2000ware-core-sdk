//###########################################################################
//
// FILE:    Example_2802x0EpwmTripZoneComp.c
//
// TITLE:   Check PWM Trip Zone Test with Comparator Inputs
//
// ASSUMPTIONS:
//
//    This program requires the f2802x0 header files.
//
//    Initially make voltage on pin COMP1A greater than COMP1B if using dual
//    pin compare; else make internal DAC output lower than V on COMP1A
//
//    During the test, monitor ePWM1 outputs on a scope
//    increase voltage on inverting side of comparator (either through COMP1B
//    pin or internal DAC setting) to trigger
//    a DCAEVT1, and DCBEVT1 .
//
//       EPWM1A is on GPIO0
//       EPWM1B is on GPIO1
//
//   DCAEVT1, DCBEVT1 a are all defined as
//   true when COMP1OUT is low
//
//    ePWM1 will react to DCAEVT1 and DCBEVT1 as a 1 shot trip
//          DCAEVT1 will pull EPWM1A high
//          DCBEVT1 will pull EPWM1B low
//
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x0 Boot Mode table is shown below.
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
// DESCRIPTION:
//
//    This example configures ePWM1
//
//    2 Examples are included:
//    * ePWM1 has DCAEVT1 and DCBEVT1 as one shot trip sources
////
//    View the EPWM1A/B waveforms
//    via an oscilloscope to see the effect of the events
//    change the state of COMP1OUT create the events
//
//    DCAEVT1, DCBEVT1  are all defined as
//    true when COMP1OUT is low
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
// Function Prototypes
//
void InitEPwm1Example(void);
__interrupt void epwm1_tzint_isr(void);

//
// Global variables used in this example
//
uint32_t  EPwm1TZIntCount;
uint32_t  EPwm2TZIntCount;

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
    // This example function is found in the f2802x0_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x0_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, and TZ pins
    //
    InitEPwm1Gpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x0_PieCtrl.c file.
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
    // The shell ISR routines are found in f2802x0_DefaultIsr.c.
    // This function is found in f2802x0_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;            // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_TZINT = &epwm1_tzint_isr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;     // Enable Clock to the ADC
    
    //
    // Comparator shares the internal BG reference of the ADC, must be powered
    // even if ADC is unused
    //
    AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;
    
    DELAY_US(1000L);         // Delay to allow BG reference to settle

    //
    // Enable clock to the Comparator 1 block
    //
    SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;
    
    Comp1Regs.COMPCTL.bit.COMPDACEN = 1;      // Power up Comparator 1 locally
    
    //
    // Connect the inverting input to pin COMP1B
    //
    Comp1Regs.COMPCTL.bit.COMPSOURCE = 1;

    //
    // Uncomment following 2 lines to use DAC instead of pin COMP1B
    // Connect the inverting input to the internal DAC
    //
    //Comp1Regs.COMPCTL.bit.COMPSOURCE = 0;
    //
    // Set DAC output to midpoint
    //
    //Comp1Regs.DACVAL.bit.DACVAL = 512;
    
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Step 5. User specific code, enable interrupts
    // Initialize counters
    //
    EPwm1TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT
    //
    IER |= M_INT2;

    //
    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;)
    {
    __asm("          NOP");
    }
}

//
// epwm1_tzint_isr - 
//
__interrupt void
epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    //
    // Leave these flags set so we only take this interrupt once
    //
    //EALLOW;
    //EPwm1Regs.TZCLR.bit.OST = 1;
    //EPwm1Regs.TZCLR.bit.INT = 1;
    //EDIS;

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

//
// InitEPwm1Example -
//
void
InitEPwm1Example()
{
    EALLOW;
    EPwm1Regs.TBPRD = 6000;                         // Set timer period
    EPwm1Regs.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA = 3000;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Define an event (DCAEVT1) based on TZ1 and TZ2
    //
    
    //
    // DCAH = Comparator 1 output
    //
    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;
    
    EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
    
    //
    // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
    //
    EPwm1Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAH_LOW;
    
    //
    // DCAEVT1 = DCAEVT1 (not filtered)
    //
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;    // Take async path

    //
    // Define an event (DCBEVT1) based on TZ1 and TZ2
    //
    
    //
    // DCBH = Comparator 1 output
    //
    EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP1OUT;
    
    EPwm1Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;     // DCAL = TZ2
    
    //
    // DCBEVT1 =  (will become active as Comparator output goes low)
    //
    EPwm1Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCBH_LOW;
    
    //
    // DCBEVT1 = DCBEVT1 (not filtered)
    //
    EPwm1Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm1Regs.DCBCTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;   // Take async path

    //
    // Enable DCAEVT1 and DCBEVT1 are one shot trip sources
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    //
    EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;
    EPwm1Regs.TZSEL.bit.DCBEVT1 = 1;

    //
    // DCAEVTx events can force EPWMxA
    // DCBEVTx events can force EPWMxB
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;           // EPWM1A will go high
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPWM1B will go low

    //
    // Enable TZ interrupt
    //
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;
}

//
// End of File
//

