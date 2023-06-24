//#############################################################################
//
// FILE:   fsi_delay_tap_measurement.c
//
// TITLE:  FSI Receive Skew Compensation Block Element Delays
//
//! \addtogroup driver_example_list
//! <h1>FSI Receive Skew Compensation Block Element Delays</h1>
//!
//! In order to understand this example better and visualize the results
//! please refer to: [Fast Serial Interface (FSI) Skew 
//! Compensation](http://www.ti.com/lit/an/spracj9/spracj9.pdf)
//! This example uses the HRCAP module to measure the FSI RX delay elements. The
//! measure delays can be graphed using the FSI Skew Compensation Utility.
//!
//! The FSI receiver module has a programmable delay line on each of the
//! external signal inputs: RXCLK, RXD0, and RXD1. The delay elements
//! introduce delays on the respective lines. This is to facilitate
//! adjustment for signal delays introduced by system level components
//! such as signal buffers, ferrite beads, isolators, and so on, or board
//! delays such as uneven trace lengths, long cable length, and so on. The
//! length of the delay is controlled by setting the RX_DLY_LINE_CTRL register
//! values for each line. There are 32 delay elements available for each of
//! the external signal input. These delay elements must be activated accordingly,
//! in order to ensure that the FSI RX module will meet the requirements for the
//! setup time and hold time. The amount of delay introduced by each delay
//! element can be measure using the high-resolution capture (HRCAP) module.
//! An example project is available with the name of fsi_delay_tap_measurement
//! which measure the delay elements on RXD1 in nano-seconds.
//!
//!\b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b delays  Value of delays, in nanoseconds
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "device.h"
#include <stdint.h>
#include <fsi.h>
#include <hrcap.h>

//
// Defines
//
#define HRCALCAL_STATUS_DONE_ISR    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT )

#define HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR                               \
                                    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT |      \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCALCAL_CALIBRATION_FLAGS  (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCAPCAL_OVERFLOW           4294967295.0f
#define HRCAPCAL_INV_OVERFLOW       (float32_t)(1.0f / HRCAPCAL_OVERFLOW)

//
// Typedefs
//
typedef struct
{
    uint32_t hrclkCount;    // High resolution clock count
    uint32_t sysclkcount;   // System clock count
    float32_t scaleFactor;  // Scale factor
    bool calDone;           // Calibration done flag
} HRCAPCAL_CalResultObj;


#define NUMBER_OF_SAMPLES   10
#define OR_SIGNAL           0
#define AND_SIGNAL          1

// CAP1 and CAP2 values of the ORed and ANDed signal. 10 Samples of each pair.
float32_t cap2cap1DifferenceNanoSecond[2][NUMBER_OF_SAMPLES] = {0};

// Delay value in ns for each FSI RX Tap (32 taps). 10 Samples of each delay tap.
// In order to understand this example better and visualize the results
// please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
float32_t delays[32][NUMBER_OF_SAMPLES] = {0};

// Raw value of CAP1
volatile uint32_t cap1Count;

// Value of CAP1 converted to nano-seconds
volatile float32_t cap1NanoSecond;

// Raw value of CAP2
volatile uint32_t cap2Count;

// Value of CAP2 converted to nano-seconds
volatile float32_t cap2NanoSecond;

// Not Used
volatile uint32_t cap3Count;

// Not Used
volatile uint32_t cap4Count;

// Number of HRCAP interrupts occurred
volatile uint16_t hrcapIntCount = 0;

// Variable to check whether ECAP interrupt has occurred
volatile uint16_t ecapIntCalCount = 0;

// HRCAP Calibration Status
volatile uint16_t calStatus = 0;

// The HRCAP Calibration Result Object
HRCAPCAL_CalResultObj hrcapCalResult;

volatile float32_t signalLenght = 0;
volatile uint32_t tap = 0;
volatile uint32_t hrcapMuxSel = 0;
volatile uint32_t sample = 0;


//
// Function Prototypes
//
void initFSI(void);
void configECAP(void);
__interrupt void hrcap6CalISR(void);
__interrupt void ecap6ISR(void);
void
FSI_configRxDelayLine_fix(uint32_t base, FSI_RxDelayTapType delayTapType,
                uint16_t tapValue);
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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ECAP6, &ecap6ISR);
    Interrupt_register(INT_ECAP6_2, &hrcap6CalISR);

    // Initialize FSI
    initFSI();

    //Configuration of ECAP(HRCAP) begins here
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure eCAP
    //
    configECAP();

    //
    // Configure HRCAL
    //
    HRCAP_enableHighResolutionClock(HRCAP6_BASE);

    //
    // Add small delay for HRCLK to start
    //
    __asm(" RPT #25 || NOP");

    HRCAP_enableHighResolution(HRCAP6_BASE);
    HRCAP_setCalibrationPeriod(HRCAP6_BASE, DEVICE_SYSCLK_FREQ);
    HRCAP_setCalibrationMode(HRCAP6_BASE);

    HRCAP_enableCalibrationInterrupt(HRCAP6_BASE, HRCAP_CALIBRATION_DONE);
    HRCAP_enableCalibrationInterrupt(HRCAP6_BASE,
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW);

    HRCAP_startCalibration(HRCAP6_BASE);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_ECAP6);
    Interrupt_enable(INT_ECAP6_2);

    //
    // Initialize counters
    //
    cap1Count = 0U;
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    // Wait for the first scale factor to become available
    while(hrcapCalResult.scaleFactor == 0);

    // Loop through all 32 delay taps on FSI RX. Sample each 10 times.
    for (tap = 0 ; tap < 32; tap++)
    {
        // Loop through the 2 different HRCAP MUX Sel sources (ANDed and ORed Signal)
        // The two values of the HRCAP MUX Sel Sources can be used to measure the delay
        // introduced by the delay tap.
        for (hrcapMuxSel = 0; hrcapMuxSel < 2; hrcapMuxSel++)
        {
            // Configure the HRCAP MUX Select
            ECAP_selectECAPInput(ECAP6_BASE, (ECAP_InputCaptureSignals)(49 + hrcapMuxSel));
            // Configure the FSI Delay Line
            FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_CLK, tap);
            FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_D0, tap);
            FSI_configRxDelayLine_fix(FSIRXA_BASE, FSI_RX_DELAY_D1, tap);

            // Acquire 10 samples
            for (sample = 0; sample < NUMBER_OF_SAMPLES; sample++)
            {
                ecapIntCalCount = 0;
                // Send FSI TX flush sequence to capture the delayed signal on FSI RX
                FSI_executeTxFlushSequence(FSITXA_BASE, 40U);
                DEVICE_DELAY_US(1);

                while(1)
                {
                    //
                    // Wait for a value to be captured by the HRCAP
                    //
                    if (ecapIntCalCount != 0)
                    {
                        // Measure the difference between cap2 and ca1 in nano-seconds
                        signalLenght = HRCAP_convertEventTimeStampNanoseconds((cap2Count - cap1Count),
                                                                       hrcapCalResult.scaleFactor);
                        // Log the result
                        cap2cap1DifferenceNanoSecond[hrcapMuxSel][sample] = signalLenght;
                        break;
                    }
                }
            }
        }

        //Measure the actual delay introduce by the tap for all 10 samples
        for (sample = 0; sample < NUMBER_OF_SAMPLES; sample++)
        {
            // Delay value in ns for each FSI RX Tap (32 taps). 10 Samples of each delay tap.
            // In order to understand this example better and visualize the results
            // please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
            delays[tap][sample] =
                    (cap2cap1DifferenceNanoSecond[AND_SIGNAL][sample] -
                            cap2cap1DifferenceNanoSecond[OR_SIGNAL][sample])/2;
        }

    }
    // Delay elements are calculated.
    // Delay value in ns for each FSI RX Tap (32 taps). 10 Samples of each delay tap.
    // In order to understand this example better and visualize the results
    // please refer to: http://www.ti.com/lit/an/spracj9/spracj9.pdf
    ESTOP0;
    while(1);
}

void initFSI()
{
    FSI_performTxInitialization(FSITXA_BASE, 40U);
    FSI_performRxInitialization(FSIRXA_BASE);

    //
    // Set internalLoopback mode
    //
    FSI_enableRxInternalLoopback(FSIRXA_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, 40U);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, 40U);
}

void
FSI_configRxDelayLine_fix(uint32_t base, FSI_RxDelayTapType delayTapType,
                uint16_t tapValue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));
    ASSERT(tapValue <= FSI_RX_MAX_DELAY_LINE_VAL);

    EALLOW;
    switch(delayTapType)
    {
        case FSI_RX_DELAY_CLK:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                   (~FSI_RX_DLYLINE_CTRL_RXCLK_DLY_M)) |
                                                   (tapValue <<
                                                   FSI_RX_DLYLINE_CTRL_RXCLK_DLY_S);
            break;

        case FSI_RX_DELAY_D0:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                   (~FSI_RX_DLYLINE_CTRL_RXD0_DLY_M)) |
                                                   (tapValue <<
                                                   FSI_RX_DLYLINE_CTRL_RXD0_DLY_S);
            break;

        case FSI_RX_DELAY_D1:
            HWREGH(base + FSI_O_RX_DLYLINE_CTRL) = (HWREGH(base + FSI_O_RX_DLYLINE_CTRL) &
                                                    (~FSI_RX_DLYLINE_CTRL_RXD1_DLY_M)) |
                                                    (tapValue <<
                                                    FSI_RX_DLYLINE_CTRL_RXD1_DLY_S);
            break;

        default:
            //
            // Invalid tap selection input
            //
            ASSERT(false);
            break;
    }
    EDIS;
}


//
// configECAP - Configure eCAP 6
//
void configECAP()
{
    //
    // Disable, clear all capture flags and interrupts
    //
    ECAP_disableInterrupt(ECAP6_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP6_BASE,
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
    ECAP_disableTimeStampCapture(ECAP6_BASE);

    //
    // Make sure the counter is stopped
    //
    ECAP_stopCounter(ECAP6_BASE);

    //
    // Capture mode
    //
    ECAP_enableCaptureMode(ECAP6_BASE);

    //
    // One - shot mode, stop at 2 events
    //
    ECAP_setCaptureMode(ECAP6_BASE,
                        ECAP_ONE_SHOT_CAPTURE_MODE,
                        ECAP_EVENT_2);

    ECAP_setEventPolarity(ECAP6_BASE,
                          ECAP_EVENT_1,
                          ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP6_BASE,
                          ECAP_EVENT_2,
                          ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(ECAP6_BASE,
                          ECAP_EVENT_3,
                          ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP6_BASE,
                          ECAP_EVENT_4,
                          ECAP_EVNT_RISING_EDGE);

    ECAP_disableCounterResetOnEvent(ECAP6_BASE, ECAP_EVENT_1);
    ECAP_disableCounterResetOnEvent(ECAP6_BASE, ECAP_EVENT_2);
    ECAP_disableCounterResetOnEvent(ECAP6_BASE, ECAP_EVENT_3);
    ECAP_disableCounterResetOnEvent(ECAP6_BASE, ECAP_EVENT_4);

    //
    // Select input
    //
    ECAP_selectECAPInput(ECAP6_BASE, (ECAP_InputCaptureSignals)49);

    ECAP_enableLoadCounter(ECAP6_BASE);

    //
    // Set SYNCO
    //
    ECAP_setSyncOutMode(ECAP6_BASE, ECAP_SYNC_OUT_SYNCI);

    //
    // Enable capture units
    //
    ECAP_enableTimeStampCapture(ECAP6_BASE);

    //
    // Start counter
    //
    ECAP_startCounter(ECAP6_BASE);

    //
    // Reset counters
    //
    ECAP_resetCounters(ECAP6_BASE);
    ECAP_reArm(ECAP6_BASE);

    //
    // Enable CAP1-CAP2 register loads
    //
    ECAP_enableTimeStampCapture(ECAP6_BASE);

    //
    // 2 events = 1 interrupt
    //
    ECAP_enableInterrupt(ECAP6_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_2);
}

//
// ecap6ISR -  eCAP 6 ISR
//
__interrupt void ecap6ISR(void)
{
    ecapIntCalCount++;

    //
    // Get the raw time stamps
    //
    cap1Count = ECAP_getEventTimeStamp(ECAP6_BASE, ECAP_EVENT_1);
    cap2Count = ECAP_getEventTimeStamp(ECAP6_BASE, ECAP_EVENT_2);

    ECAP_clearInterrupt(ECAP6_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(ECAP6_BASE);
    ECAP_reArm(ECAP6_BASE);
    ECAP_resetCounters(ECAP6_BASE);

    //
    // Acknowledge the PIE interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// hrcap6CalISR -  eCAP 6 Calibration ISR
//
__interrupt void hrcap6CalISR(void)
{
    hrcapIntCount++;

    //
    // Get calibration interrupt sources
    //
    calStatus = HRCAP_getCalibrationFlags(HRCAP6_BASE);

    //
    // Get calibration clock counts
    //
    hrcapCalResult.hrclkCount = HRCAP_getCalibrationClockPeriod(HRCAP6_BASE,
                                            HRCAP_CALIBRATION_CLOCK_HRCLK);
    hrcapCalResult.sysclkcount = HRCAP_getCalibrationClockPeriod(HRCAP6_BASE,
                                            HRCAP_CALIBRATION_CLOCK_SYSCLK);

    //
    // The following options are possible
    //   - HRCALCAL_STATUS_DONE_ISR
    //   - HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR
    //   - Software forced generated interrupt
    //
    if(HRCALCAL_STATUS_DONE_ISR == calStatus)
    {
        //
        // Calculate scale factor
        //
        hrcapCalResult.scaleFactor = HRCAP_getScaleFactor(HRCAP6_BASE);
    }
    else if (HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR == calStatus)
    {
        //
        // Calibration done with an overflow. Determine which counter has
        // overflowed
        //
        if(hrcapCalResult.hrclkCount > hrcapCalResult.sysclkcount)
        {
            //
            // HRCLK has overflowed
            //
            hrcapCalResult.scaleFactor = hrcapCalResult.sysclkcount *
                                         HRCAPCAL_INV_OVERFLOW;
        }
        else if(hrcapCalResult.hrclkCount < hrcapCalResult.sysclkcount)
        {
            //
            // SYSCLK has overflowed
            //
            hrcapCalResult.scaleFactor = HRCAPCAL_OVERFLOW /
                                         hrcapCalResult.hrclkCount;
        }
        else
        {
            //
            // Both SYSCLK and HRCLK have overflowed
            //
            hrcapCalResult.scaleFactor = 1.0f;
        }
    }
    else
    {
        //
        // Software generated interrupt
        //
    }

    //
    // Clear the interrupts
    //
    HRCAP_clearCalibrationFlags(HRCAP6_BASE, calStatus);

    //
    // Acknowledge the PIE interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}
