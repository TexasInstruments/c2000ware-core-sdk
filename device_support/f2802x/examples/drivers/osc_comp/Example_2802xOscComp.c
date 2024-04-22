//#############################################################################
//
//  File:   Example_F2802xOscComp.c
//
//  Title:  Example Internal Oscillator Compensation
//
//! \addtogroup example_list
//!  <h1>Internal Oscillator Compensation</h1>
//!
//!   This program shows how to use the internal oscillator compensation
//!   functions in osc.c or F2802x_OscComp.c. The temperature sensor is sampled
//!   and the raw temp sensor value is passed to the oscillator compensation
//!   function, which uses this parameter to compensate for
//!   frequency drift of the internal oscillator over temperature.
//!
//!   Watch Variables:
//!   - temp
//!   - SysCtrlRegs.INTOSC1TRIM
//!   - SysCtrlRegs.INTOSC2TRIM
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
#include "DSP28x_Project.h"     // DSP28x Headerfile

#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/osc.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/wdog.h"

//
// Globals
//
int16_t temp;   //Temperature sensor reading

ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

//
// Main
//
void main(void)
{
    CPU_Handle myCpu;
    OSC_Handle myOsc;
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
    myOsc = OSC_init((void *)OSC_BASE_ADDR, sizeof(OSC_Obj));
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

    //
    // Set the flash OTP wait-states to minimum. This is important
    // for the performance of the compensation function.
    //
    FLASH_setup(myFlash);
#endif

    //
    // Initialize GPIO
    // Enable XCLOCKOUT to allow monitoring of oscillator 1
    //
    GPIO_setMode(myGpio, GPIO_Number_18, GPIO_18_Mode_XCLKOUT);
    CLK_setClkOutPreScaler(myClk, CLK_ClkOutPreScaler_SysClkOut_by_1);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Initialize the ADC
    //
    ADC_enableBandGap(myAdc);
    ADC_enableRefBuffers(myAdc);
    ADC_powerUp(myAdc);
    ADC_enable(myAdc);
    ADC_setVoltRefSrc(myAdc, ADC_VoltageRefSrc_Int);

    //
    // Connect channel A5 internally to the temperature sensor
    //
    ADC_enableTempSensor(myAdc);            
    
    //
    // Set SOC0 channel select to ADCINA5
    //
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_0, ADC_SocChanNumber_A5);
    
    //
    // Set SOC1 channel select to ADCINA5
    //
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_1, ADC_SocChanNumber_A5);
    
    //
    // Set SOC0 acquisition period to 37 ADCCLK
    //
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_0, 
                           ADC_SocSampleWindow_37_cycles);
    //
    // Set SOC1 acquisition period to 37 ADCCLK
    //
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_1, 
                           ADC_SocSampleWindow_37_cycles);
    
    //
    // Connect ADCINT1 to EOC1
    //
    ADC_setIntSrc(myAdc, ADC_IntNumber_1, ADC_IntSrc_EOC1);
    ADC_enableInt(myAdc, ADC_IntNumber_1);                // Enable ADCINT1

    //
    // Note: two channels have been connected to the temp sensor
    // so that the first sample can be discarded to avoid the
    // ADC first sample issue.  See the device errata.
    //
    for(;;)
    {
        //
        // Sample temperature sensor. Note: the end application will
        // be responsible for deciding how and when to sample the
        // temperature sensor so that the value can be passed to the
        // compensation function
        //

        //
        // Force start of conversion on SOC0 and SOC1
        //
        ADC_forceConversion(myAdc, ADC_SocNumber_0);
        ADC_forceConversion(myAdc, ADC_SocNumber_1);

        //
        // Wait for end of conversion
        //
        while(ADC_getIntStatus(myAdc, ADC_IntNumber_1) == 0)
        {
            
        }

        //
        // Clear ADCINT1
        //
        ADC_clearIntFlag(myAdc, ADC_IntNumber_1);

        //
        // Get temp sensor sample result from SOC1
        //
        temp = ADC_readResult(myAdc, ADC_ResultNumber_1);

        //
        // Use temp sensor measurement to perform oscillator compensation even
        // as temperature changes.
        //
        OSC_runCompensation(myOsc, OSC_Number_1, temp);
        OSC_runCompensation(myOsc, OSC_Number_2, temp);

        //
        // Add other application tasks here
        //
    }
}

//
// End of File
//

