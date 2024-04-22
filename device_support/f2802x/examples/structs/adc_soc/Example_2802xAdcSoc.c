//###########################################################################
//
// FILE:   Example_2802xAdcSoc.c
//
// TITLE:  f2802x ADC Start-Of-Conversion (SOC) Example Program.
//
// ASSUMPTIONS:
//
//   This program requires the f2802x header files.
//
//   Make sure the CPU clock speed is properly defined in
//   f2802x_Examples.h before compiling this example.
//
//   Connect signals to be converted to A2 and A3.
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
// DESCRIPTION:
//
//   This example sets up the PLL in x12/2 mode.
//
//   For 60 MHz devices (default)
//   (assuming a 10Mhz input clock).
//
//   Interrupts are enabled and the ePWM1 is setup to generate a periodic
//   ADC SOC - ADCINT1. Two channels are converted, ADCINA4 and ADCINA2.
//
//   Watch Variables:
//
//         Voltage1[10]     Last 10 ADCRESULT0 values
//         Voltage2[10]     Last 10 ADCRESULT1 values
//         ConversionCount  Current result number 0-9
//         LoopCount        Idle loop counter
//
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
__interrupt void adc_isr(void);
void Adc_Config(void);

//
// Globals
//
uint16_t LoopCount;
uint16_t ConversionCount;
uint16_t Voltage1[10];
uint16_t Voltage2[10];

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
    EALLOW;             // This is needed to write to EALLOW protected register
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals
    //
    InitAdc();  // For this example, init the ADC
    AdcOffsetSelfCal();

    //
    // Step 5. User specific code, enable interrupts:
    // Enable ADCINT1 in PIE
    //
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE
    IER |= M_INT1; 					   // Enable CPU Interrupt 1
    EINT;          					   // Enable Global interrupt INTM
    ERTM;          					   // Enable Global realtime interrupt DBGM

    LoopCount = 0;
    ConversionCount = 0;

    //
    // Configure ADC
    // Note: Channel ADCINA4  will be double sampled to workaround the ADC 1st 
    // sample issue for rev0 silicon errata
    //
    EALLOW;
    
    //
    // ADCINT1 trips after AdcResults latch
    //
    AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;
    
    AdcRegs.INTSEL1N2.bit.INT1E     = 1;    // Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;    // Disable ADCINT1 Continuous mode
    
    //
    // setup EOC2 to trigger ADCINT1 to fire
    //
    AdcRegs.INTSEL1N2.bit.INT1SEL	= 2;
    
    //
    // set SOC0 channel select to ADCINA4
    //
    AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 4;
    
    //
    // set SOC1 channel select to ADCINA4
    //
    AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 4;
    
    //
    // set SOC1 channel select to ADCINA2
    //
    AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 2;
    
    //
    // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first
    // then SOC1
    //
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5;
    
    //
    // set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first
    // then SOC1
    //
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 5;
    
    //
    // set SOC2 start trigger on EPWM1A, due to round-robin SOC0 converts first
    // then SOC1, then SOC2
    //
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 5;
    
    //
    // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;
    
    //
    // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;
    
    //
    // set SOC2 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 6;	
    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EPwm1Regs.ETSEL.bit.SOCAEN	= 1;		// Enable SOC on A group
    
    //
    // Select SOC from from CPMA on upcount
    //
    EPwm1Regs.ETSEL.bit.SOCASEL	= 4;
    
    EPwm1Regs.ETPS.bit.SOCAPRD 	= 1;		    // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA 	= 0x0080;	    // Set compare A value
    EPwm1Regs.TBPRD 				= 0xFFFF;	// Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE 	= 0;		// count up and start

    //
    // Wait for ADC interrupt
    //
    for(;;)
    {
        LoopCount++;
    }
}

//
// adc_isr -
//
__interrupt void
adc_isr(void)
{
    //
    // discard ADCRESULT0 as part of the workaround to the 1st sample errata
    // for rev0
    //
    Voltage1[ConversionCount] = AdcResult.ADCRESULT1;
    Voltage2[ConversionCount] = AdcResult.ADCRESULT2;

    //
    // If 20 conversions have been logged, start over
    //
    if(ConversionCount == 9)
    {
        ConversionCount = 0;
    }
    else
    {
        ConversionCount++;
    }

    //
    // Clear ADCINT1 flag reinitialize for next SOC
    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    
    //
    // Acknowledge interrupt to PIE
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    return;
}

//
// End of File
//

