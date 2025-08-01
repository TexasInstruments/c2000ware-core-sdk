//#############################################################################
//
// FILE:   adc_ex17_safety_checker.c
//
// TITLE:  ADC Safety Checker
//
//! \addtogroup driver_example_list
//! <h1>ADC Safety Checker</h1>
//!
//! This example compares the absolute value of the two ADC conversion results
//! with the set tolerance value.
//!
//! The ADCA is used with A0 and A1 to compare the two ADC conversions. If
//! the difference between two conversion results exceeds the value configured
//! as tolerance then the ADC result safety checker tile generates an interrupt
//! signal from out-of-tolerance.
//!
//! \b External \b Connections \n
//!  - A0 and A1 should be connected to signals to convert.
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result0 - Digital representation of the voltage on pin A0
//! - \b myADC0Result1 - Digital representation of the voltage on pin A1
//! - \b tolerance - Set digital tolerance limit for ADC safety checker
//! - \b count - number of times the OOT flag is generated
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t myADC0Result0;
uint16_t myADC0Result1;
uint32_t count;
uint32_t getsafecheckStatus;
volatile uint16_t tolerance;

void myADCSafetyChecker0_init();

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set up ADCs, initializing the SOCs to be triggered by software
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    myADCSafetyChecker0_init();
    Board_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Convert, wait for completion, and store results
        //
        ADC_forceMultipleSOC(myADC0_BASE, (ADC_FORCE_SOC0 | ADC_FORCE_SOC1));

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0Result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

        //
        // Get the safety checker result and generate flag if the difference exceeds the tolerance value
        //
        getsafecheckStatus = ADC_getSafetyCheckStatus(ADCSAFETYINTEVTAGG1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_OOT_FLG);
        if(getsafecheckStatus)
        {
            //
            // Indicate that the OOT flag is generated
            //
            count++;

            //
            // Software breakpoint. At this point, conversion results (myADC0Result0, myADC0Result1)
            // are compared with each other, generated safety checker out-of-tolerance flag and incremented count
            //
            // Hit run again to get updated conversions.
            //
            ESTOP0;
        }
        ADC_clearSafetyCheckStatus(ADCSAFETYINTEVTAGG1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_OOT_FLG);
    }
}


void myADCSafetyChecker0_init(void){

    //
    // Enable the safety checker event.
    //
    ADC_enableSafetyCheckEvt(ADCSAFETYINTEVTAGG1_BASE, ADC_SAFETY_CHECKER1, ADC_SAFETY_CHECK_EVENT1, ADC_SAFETY_CHECK_OOT);
    //
    // Configures the safety checker result for a selected SOC.
    //
    ADC_configSOCSafetyCheckerInput(myADC0_BASE,ADC_SOC_NUMBER0,ADC_SAFETY_CHECKER_INPUT_SOCx);

    //
    // Configures the safety checker module.
    //
    ADC_configureSafetyChecker(ADCSAFETYCHK1_BASE, ADC_SAFETY_CHECK1,ADC_A,ADC_RESULT0);

    //
    // Configures the safety checker result for a selected SOC.
    //
    ADC_configSOCSafetyCheckerInput(myADC0_BASE,ADC_SOC_NUMBER1,ADC_SAFETY_CHECKER_INPUT_SOCx);
    
    //
    // Configures the safety checker module.
    //
    ADC_configureSafetyChecker(ADCSAFETYCHK1_BASE, ADC_SAFETY_CHECK2,ADC_A,ADC_RESULT1);

    //
    // Configures the tolerance allowed between safety check results.
    //
    ADC_setSafetyCheckerTolerance(ADCSAFETYCHK1_BASE,tolerance);

    //
    // Enables the ADC result safety checker module.
    //
    ADC_enableSafetyChecker(ADCSAFETYCHK1_BASE);
}
