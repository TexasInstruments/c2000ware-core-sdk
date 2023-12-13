//###########################################################################
//
// FILE:   Example_2805xAdcTempSensorConv.c
//
// TITLE:  ADC Temperature Sensor Conversion
//
//! \addtogroup f2805x_example_list
//! <h1> ADC Temperature Sensor Conversion</h1>
//!
//! This example shows how to convert a raw ADC temperature sensor reading
//! into degrees C and degrees K. Internal temperature is sampled continuously
//! through ADCINA5. The coefficients required to compensate for temperature
//! offset are read from TI OTP.
//!
//! \note
//! THIS EXAMPLE USES VARIABLES STORED IN OTP DURING FACTORY TEST. THESE OTP
//! LOCATIONS, 0x3D7E90 to 0x3D7EA4, MAY NOT BE POPULATED. ENSURE THAT THESE
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
// Copyright (C) 2012-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#define CONV_WAIT 1L //Micro-seconds to wait for ADC conversion.

int16 temp; //raw temperature sensor reading
int16 degC; //temperature in deg. C
int16 degK; //temperature in deg. K

void main()
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2805x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // Enable XCLOCKOUT to allow monitoring of oscillator 1
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3; //enable XCLOCKOUT through GPIO mux
    SysCtrlRegs.XCLK.bit.XCLKOUTDIV = 2; //XCLOCKOUT = SYSCLK

    //
    // Step 3. Clear all __interrupts and initialize PIE vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE __interrupts disabled and flags
    // are cleared.
    // This function is found in the F2805x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU __interrupts and clear all CPU __interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the __interrupt
    // is not used in this example. This is useful for debug purposes.
    // The shell ISR routines are found in F2805x_DefaultIsr.c.
    // This function is found in F2805x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //
    // Configure the ADC:
    // Initialize the ADC
    //
    InitAdc();
    AdcOffsetSelfCal();

    EALLOW;
    AdcRegs.ADCCTL1.bit.TEMPCONV  = 1;  //Connect A5 internally to temp sensor
    AdcRegs.ADCSOC0CTL.bit.CHSEL  = 5;  //Set SOC0 channel select to ADCINA5
    AdcRegs.ADCSOC1CTL.bit.CHSEL  = 5;  //Set SOC1 channel select to ADCINA5
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = 36; //Set SOC0 acq. period to 37 ADCCLK
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = 36; //Set SOC1 acq. period to 37 ADCCLK
    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;  //Connect ADCINT1 to EOC1
    AdcRegs.INTSEL1N2.bit.INT1E  =  1;  //Enable ADCINT1

    //
    // Note: two channels have been connected to the temp sensor
    // so that the first sample can be discarded to avoid the
    // ADC first sample issue.  See the device errata.
    //
    // Set the flash OTP wait-states to minimum. This is important
    // for the performance of the temperature conversion function.
    //
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 1;

    //
    //Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        //Sample the temp sensor...
        //
        //Force start of conversion on SOC0 and SOC1
        //
        AdcRegs.ADCSOCFRC1.all = 0x03;

        //
        //Wait for end of conversion.
        //
        while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
        {

        }  //Wait for ADCINT1
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        //Clear ADCINT1

        //
        //Get temp sensor sample result from SOC1
        //
        temp = AdcResult.ADCRESULT1;

        //
        //Convert the raw temperature sensor measurement into temperature
        //
        degC = GetTemperatureC(temp);
        degK = GetTemperatureK(temp);
    }
}



