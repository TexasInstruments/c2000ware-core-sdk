//#############################################################################
//
// FILE:    baud_tune_via_uart.c
//
// TITLE:   Tune Baud Rate Via UART.
//
//! \addtogroup driver_example_list
//! <h1>Tune Baud Rate via UART Example</h1>
//!
//! This example demonstrates the process of tuning the UART/SCI baud rate of
//! a C2000 device based on the UART input from another device. As UART does
//! not have a clock signal, reliable communication requires baud rates to
//! be reasonably matched. This example addresses cases where  a clock
//! mismatch between devices is greater than is acceptable for communications,
//! requiring baud compensation between boards. As reliable communication
//! only requires matching the EFFECTIVE baud rate, it does not matter which
//! of the two boards executes the tuning (the board with the less-accurate
//! clock source does not need to be the one to tune; as long as one of the
//! two devices tunes to the other, then proper communication can
//! be established).
//!
//! To tune the baud rate of this device, SCI data (of the desired baud rate)
//! must be sent to this device. The input SCI baud rate must be within the
//! +/- MARGINPERCENT of the TARGETBAUD chosen below. These two variables are
//! defined below, and should be chosen based on the application requirements.
//! Higher MARGINPERCENT will allow more data to be considered "correct" in
//! noisy conditions, and  may decrease accuracy. The TARGETBAUD is what was
//! expected to be the baud rate, but due to clock differences, needs to be
//! tuned for better communication robustness with the other device.
//!
//! For LaunchPad and custom devices, there may be need to configure
//! different GPIO for the SCI_RX and SCI_TX pins if GPIO9 and GPIO8 are not
//! available for these devices. This can be configured using the included
//! .syscfg file. Open the SCI peripheral, open the
//! "PinMux" / "Peripheral and Pin Configuration" configuration section
//! and choose GPIOs that are available on the given board. Update
//! GPIO_SCIRX_NUMBER below to match the RX choice. Please refer to the
//! LaunchPad user guide for list of available GPIO.
//!
//! There may also be a need to add a global define to choose the LaunchPad.
//! For example, in device.h, some devices require choosing a LaunchPad
//! configuration, such as writing #define _LAUNCHXL_F2####. Please ensure
//! these are defined if used.
//!
//! NOTE: Lower baud rates have more granularity in register options,
//! and therefore tuning is more affective at these speeds.
//!
//! \b External \b Connections for Control Card \n
//! - SCIA_RX/eCAP1 is on GPIO9, connect to incoming SCI communications
//! - SCIA_TX is on GPIO8, for observation externally
//!
//! \b Watch \b Variables \n
//! - \b avgBaud - Baud rate that was detected and set after tuning
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
// must replace with the GPIO number of the SCIRX pin chosen in .syscfg
#define GPIO_SCIRX_NUMBER   9

//
// choose baud rate being received from target baud rate device
// closest baud rate to 9600 that can be set in register is 9601
//
#define TARGETBAUD          9601

//
// number of samples in the array (higher = better averaging, lower = faster)
//
#define NUMSAMPLES          32

//
// margin for what is considered a "good" pulse width:
// set this higher to allow more samples to be considered "good" data,
// if losing too much data set this lower to prevent "bad" samples to
// be discarded more strictly
//
#define MARGINPERCENT       0.05

//
// at least this percentage of the samples array must be "good"
// to not flag an error
//
#define MINSAMPLEPERCENT    0.50

//
// Globals
//
volatile uint32_t capCountArr[4];
volatile int capCountIter = 0;
volatile float sampleArr[NUMSAMPLES];
volatile uint16_t sampleArrIter = 0;
volatile uint16_t stopCaptures = 0;

//
// Function Prototypes
//
void initECAP(void);
__interrupt void ecap1ISR(void);
uint16_t arrTo1PulseWidth(volatile float arr[], int size, float targetWidth);
float computeAvgWidth(volatile float arr[], int size);
uint32_t getAverageBaud(volatile float arr[], int size, float targetBaudRate);


//
// Main
//
void main(void)
{
    stopCaptures = 0;

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
    // Board Initialization
    //
    Board_init();

    //
    // Configure SCIRX pin's GPIO location as eCAP input
    // Fill this GPIO number in based on SCIRX from .syscfg file
    //
    XBAR_setInputPin(XBAR_INPUT7, GPIO_SCIRX_NUMBER);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ECAP1, &ecap1ISR);

    //
    // Initialize basic settings for eCAP monitoring of SCI RX
    //
    initECAP();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_ECAP1);

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for(;;)
    {
        //
        // Array is filled, begin tuning
        //
        if(stopCaptures==1)
        {
            //
            // Get an average baud rate from the array of samples
            //
            uint32_t avgBaud = getAverageBaud(sampleArr,NUMSAMPLES,TARGETBAUD);

            //
            // if the baud function returns the error code '0', then flag an
            // error
            //
            if(avgBaud==0)
            {
                ESTOP0;
            }

            //
            // Update the device's baud rate to match the measured baud rate
            //
            SCI_setBaud(mySCI0_BASE, DEVICE_LSPCLK_FREQ, avgBaud);

            //
            // Wait for user to view the results in "Expressions" window
            //
            ESTOP0;

            //
            // (OPTIONAL) Continuously send data to SCITX once tuning
            // is complete for external observation (by logic analyzer or
            // scope)
            //
            //unsigned char *msg;
            //while(1)
            //{
            //    msg = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\0";
            //    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 51);
            //}

            //
            // If continuing, reset the array iterator and unlock the ISR for
            // new captures
            //
            sampleArrIter=0;
            stopCaptures=0;
        }
    }
}

void initECAP()
{
    //
    // Disable ,clear all capture flags and interrupts
    //
    ECAP_disableInterrupt(ECAP1_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP1_BASE,
                        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE));

    //
    // Disable CAP1-CAP4 register loads
    //
    ECAP_disableTimeStampCapture(ECAP1_BASE);

    //
    // Configure eCAP
    //    Enable capture mode.
    //    One shot mode, stop capture at event 4.
    //    Set polarity of the events to rising, falling, rising, falling edge.
    //    Set capture in time difference mode.
    //    Select input from XBAR7.
    //    Enable eCAP module.
    //    Enable interrupt.
    //
    ECAP_stopCounter(ECAP1_BASE);
    ECAP_enableCaptureMode(ECAP1_BASE);

    ECAP_setCaptureMode(ECAP1_BASE, ECAP_ONE_SHOT_CAPTURE_MODE, ECAP_EVENT_4);

    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_RISING_EDGE);

    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);

    XBAR_setInputPin(XBAR_INPUT7, GPIO_SCIRX_NUMBER);

    ECAP_enableLoadCounter(ECAP1_BASE);
    ECAP_setSyncOutMode(ECAP1_BASE, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_enableTimeStampCapture(ECAP1_BASE);
    ECAP_reArm(ECAP1_BASE);

    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
}


__interrupt void ecap1ISR(void)
{
    if(stopCaptures==0)
    {
        //
        // Get the capture counts, interrupt every 4. Can be 1-bit or more
        // wide. Add one to account for partial eCAP counts at higher baud
        // rates (for example: count = 40, but if had higher resolution, this
        // would be 40.5)
        capCountArr[0] = 1+ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);
        capCountArr[1] = 1+ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_2);
        capCountArr[2] = 1+ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_3);
        capCountArr[3] = 1+ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_4);

        //
        // Add samples to a buffer. Get average baud and tune if buffer filled.
        //
        capCountIter = 0;
        for(capCountIter=0;capCountIter<4;capCountIter++)
        {
            //
            // if we still have samples left to capture, add it to the
            // samples array
            //
            if(sampleArrIter<NUMSAMPLES)
            {
                sampleArr[sampleArrIter] = capCountArr[capCountIter];
                sampleArrIter++;
            }

            //
            // else, all samples were received, break to begin tuning
            //
            else
            {
                stopCaptures=1;
                break;
            }
        }
    }

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(ECAP1_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(ECAP1_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(ECAP1_BASE);

    //
    // Acknowledge the group interrupt for more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// FUNCTION:    getAverageBaud
// PURPOSE:     get the average baud rate of the array
// INPUTS:      array of pulse widths (in number eCAP counts),
//              size of array, and target baud rate
// RETURNS:     average baud rate
//
uint32_t getAverageBaud(volatile float arr[], int size, float targetBaudRate)
{
    //
    // clean up variable width array to single-bit-width array
    //
    float calcTargetWidth = (float)DEVICE_SYSCLK_FREQ/targetBaudRate;
    uint16_t pass = arrTo1PulseWidth(arr, size, calcTargetWidth);

    //
    // pass only if enough good samples provided
    //
    if(pass == 0)
    {
        return(0);
    }

    //
    // convert 2-bit width, 3-bit width, and so on to 1-bit width values by
    // dividing, and average these values. skip unrelated values
    //
    float averageBitWidth = computeAvgWidth(arr, size);

    //
    // get the rounded baud rate from the average number of clocks and the
    // sysclk frequency
    //
    return((uint32_t)(((float)DEVICE_SYSCLK_FREQ/(float)averageBitWidth)+0.5));
}

//
// FUNCTION:    arrTo1PulseWidth
// PURPOSE:     convert 2-bit and higher widths to 1-bit equivalent,
//              set "bad" values to zero
// INPUTS:      array of pulse widths in number eCAP counts, size of array,
//              and target pulse-width (in number of eCAP counts)
// RETURNS:     pass if enough "good" data received,
//              fail if not enough "good" data
//
uint16_t arrTo1PulseWidth(volatile float arr[], int size, float targetWidth)
{
    int iterator = 0, numBitWidths=0;
    uint16_t goodDataCount = 0, pass = 0;
    for(iterator=0;iterator<size;iterator++)
    {

        //
        // if the item is less than 10 times the bit width,
        //
        if(arr[iterator] < targetWidth*10)
        {

            //
            // if the item is not within +/-MARGINPERCENT% of the targetWidth,
            // then it is a multiple of 1-bit
            //
            bool belowBound = arr[iterator] < targetWidth*(1.0-MARGINPERCENT);
            bool aboveBound = arr[iterator] > targetWidth*(1.0+MARGINPERCENT);
            if(belowBound || aboveBound)
            {

                //
                // estimate how many bit-widths this is
                //
                numBitWidths = (int)((arr[iterator]/targetWidth)+0.5);

                //
                // multiply the multi-bit baudrate value by the estimated
                // number of bits to make this a 1-bit baud estimate
                //
                arr[iterator] = arr[iterator]/numBitWidths;

                //
                // find if this new value is within the bounds
                //
                belowBound = arr[iterator] < targetWidth*(1.0-MARGINPERCENT);
                aboveBound = arr[iterator] > targetWidth*(1.0+MARGINPERCENT);
                if(belowBound || aboveBound)
                {
                    arr[iterator] = 0; // discard if not within margins
                }
                else
                {
                    goodDataCount++; // iterate good data counter
                }
            }
            else
            {

                //
                // this is a 1-bit value so increment the counter for it
                //
                goodDataCount++;
            }
        }
        else
        {
            arr[iterator] = 0;
        }
    }

    //
    // if at least MINSAMPLEPERCENT% of the sampled values
    // are "good" samples, then return a pass
    //
    if((float)goodDataCount/(float)size > MINSAMPLEPERCENT)
    {
        pass=1;
    }
    return(pass); //return if the array had enough good samples or not
}

//
// FUNCTION:    computeAvgWidth
// PURPOSE:     average all non-zero items in the array
// INPUTS:      array of 1-bit pulse widths in number eCAP counts,
//              and size of array
// RETURNS:     average width
//
float computeAvgWidth(volatile float arr[], int size)
{
    int iterator = 0, totSamples = 0;
    float total = 0;
    for(iterator=0;iterator<size;iterator++)
    {
        //
        // if the item has not been removed
        //
        if(arr[iterator] != 0)
        {
            //
            // iterate the number of samples that are included in the total
            //
            totSamples++;
            //
            //add it to the moving average
            //
            total+=arr[iterator];
        }
    }
    return(total/totSamples); //return the average
}
