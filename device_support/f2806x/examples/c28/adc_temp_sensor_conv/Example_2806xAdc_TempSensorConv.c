//###########################################################################
//
// FILE:   Example_2806xAdcTempSensorConv.c
//
// TITLE:  ADC Temperature Sensor Conversion Example
//
//! \addtogroup f2806x_example_list
//! <h1> ADC Temperature Sensor Conversion (adc_temp_sensor_conv)</h1>
//!
//! This example shows how to convert a raw ADC temperature sensor reading 
//! into deg. C and deg. K. Internal temperature is sampled continuously 
//! through ADCINA5. The coefficients required to compensate for temperature
//! offset are read from TI OTP.
//!
//! \note
//! THIS EXAMPLE USES VARIABLES STORED IN OTP DURING FACTORY TEST. THESE OTP
//! LOCATIONS ,0x3D7E90 to 0x3D7EA4, MAY NOT BE POPULATED. ENSURE THAT THESE 
//! MEMORY LOCATIONS IN TI OTP ARE POPULATED WITH VALUES DIFFERENT FROM
//! 0XFFFF
//!
//! \b Watch \b Variables \n
//!  - temp
//!  - degC
//!  - degK
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
#include "DSP28x_Project.h"     // DSP28x Headerfile

//
// Defines
//

//
// Micro-seconds to wait for ADC conversion. Longer than necessary.
//
#define CONV_WAIT 1L

//
// Globals
//
int16 temp; //raw temperature sensor reading
int16 degC; //temperature in deg. C
int16 degK; //temperature in deg. K

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // Enable XCLOCKOUT to allow monitoring of oscillator 1
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;  // enable XCLOCKOUT through GPIO mux
    SysCtrlRegs.XCLK.bit.XCLKOUTDIV = 2;  // XCLOCKOUT = SYSCLK

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Configure the ADC: Initialize the ADC
    //
    InitAdc();
    AdcOffsetSelfCal();

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;	// Enable non-overlap mode
    
    //
    // Connect channel A5 internally to the temperature sensor
    //
    AdcRegs.ADCCTL1.bit.TEMPCONV  = 1; 		
    
    AdcRegs.ADCSOC0CTL.bit.CHSEL  = 5; 	// Set SOC0 channel select to ADCINA5
    
    //
    // Set SOC0 acquisition period to 26 ADCCLK
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = 25;
    
    AdcRegs.INTSEL1N2.bit.INT1SEL = 0; 	// Connect ADCINT1 to EOC0
    AdcRegs.INTSEL1N2.bit.INT1E   = 1; 	// Enable ADCINT1

    //
    // Set the flash OTP wait-states to minimum. This is important
    // for the performance of the temperature conversion function.
    //
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 1;

    //
    // Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        // Sample the temp sensor...
        //

        //
        // Force start of conversion on SOC0
        //
        AdcRegs.ADCSOCFRC1.all = 0x01;

        //
        // Wait for end of conversion.
        //
        while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
        {
            //
            // Wait for ADCINT1
            //
        }
        
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        // Clear ADCINT1

        //
        // Get temp sensor sample result from SOC0
        //
        temp = AdcResult.ADCRESULT0;

        //
        // Convert the raw temperature sensor measurement into temperature
        //
        degC = GetTemperatureC(temp);
        degK = GetTemperatureK(temp);
    }
}

//
// End of File
//

