//#############################################################################
//
// FILE:   epwm_ex2_updown_aq.c
//
// TITLE:  ePWM Action Qualifier Module - Using up/down count.
//
//! \addtogroup driver_example_list
//! <h1> ePWM Up Down Count Action Qualifier</h1>
//!
//! This example configures ePWM1, ePWM2, ePWM3 to produce a waveform with
//! independent modulation on ePWMxA and ePWMxB.
//!
//! The compare values CMPA and CMPB are modified within the ePWM's ISR.
//!
//! The TB counter is in up/down count mode for this example.
//!
//! View the ePWM1A/B(GPIO0 & GPIO1), ePWM2A/B(GPIO2 &GPIO3)
//! and ePWM3A/B(GPIO4 & GPIO5) waveforms on oscilloscope.
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD  2000U
#define EPWM1_MAX_CMPA     1950U
#define EPWM1_MIN_CMPA       50U
#define EPWM1_MAX_CMPB     1950U
#define EPWM1_MIN_CMPB       50U

#define EPWM2_TIMER_TBPRD  2000U
#define EPWM2_MAX_CMPA     1950U
#define EPWM2_MIN_CMPA       50U
#define EPWM2_MAX_CMPB     1950U
#define EPWM2_MIN_CMPB       50U

#define EPWM3_TIMER_TBPRD  2000U
#define EPWM3_MAX_CMPA      950U
#define EPWM3_MIN_CMPA       50U
#define EPWM3_MAX_CMPB     1950U
#define EPWM3_MIN_CMPB     1050U

#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U

//
// Globals
//
typedef struct
{
    uint32_t epwmModule;
    uint16_t epwmCompADirection;
    uint16_t epwmCompBDirection;
    uint16_t epwmTimerIntCount;
    uint16_t epwmMaxCompA;
    uint16_t epwmMinCompA;
    uint16_t epwmMaxCompB;
    uint16_t epwmMinCompB;
}epwmInformation;

//
// Globals to hold the ePWM information used in this example
//
epwmInformation epwm1Info;
epwmInformation epwm2Info;
epwmInformation epwm3Info;

//
// Function Prototypes
//
void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);
__interrupt void epwm1ISR(void);
__interrupt void epwm2ISR(void);
__interrupt void epwm3ISR(void);
void updateCompare(epwmInformation *epwmInfo);

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
    // Disable pin locks and enable internal pull ups.
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
    // Assign the interrupt service routines to ePWM interrupts
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);
    Interrupt_register(INT_EPWM2, &epwm2ISR);
    Interrupt_register(INT_EPWM3, &epwm3ISR);


    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    // Configure EPWM Modules
    //
    Board_init();

    initEPWM1();
    initEPWM2();
    initEPWM3();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_EPWM2);
    Interrupt_enable(INT_EPWM3);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}

//
// epwm1ISR - ePWM 1 ISR
//
__interrupt void epwm1ISR(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&epwm1Info);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// epwm2ISR - ePWM 2 ISR
//
__interrupt void epwm2ISR(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&epwm2Info);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM2_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// epwm3ISR - ePWM 3 ISR
//
__interrupt void epwm3ISR(void)
{
    //
    // Update the CMPA and CMPB values
    //
    updateCompare(&epwm3Info);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// initEPWM1 - Configure ePWM1
//
void initEPWM1()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm1Info.epwmCompADirection = EPWM_CMP_UP;
    epwm1Info.epwmCompBDirection = EPWM_CMP_DOWN;
    epwm1Info.epwmTimerIntCount = 0U;
    epwm1Info.epwmModule = myEPWM1_BASE;
    epwm1Info.epwmMaxCompA = EPWM1_MAX_CMPA;
    epwm1Info.epwmMinCompA = EPWM1_MIN_CMPA;
    epwm1Info.epwmMaxCompB = EPWM1_MAX_CMPB;
    epwm1Info.epwmMinCompB = EPWM1_MIN_CMPB;
}

//
// initEPWM2 - Configure ePWM2
//
void initEPWM2()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm2Info.epwmCompADirection = EPWM_CMP_UP;
    epwm2Info.epwmCompBDirection = EPWM_CMP_UP;
    epwm2Info.epwmTimerIntCount = 0U;
    epwm2Info.epwmModule = myEPWM2_BASE;
    epwm2Info.epwmMaxCompA = EPWM2_MAX_CMPA;
    epwm2Info.epwmMinCompA = EPWM2_MIN_CMPA;
    epwm2Info.epwmMaxCompB = EPWM2_MAX_CMPB;
    epwm2Info.epwmMinCompB = EPWM2_MIN_CMPB;
}

//
// initEPWM3 - Configure ePWM3
//
void initEPWM3(void)
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm3Info.epwmCompADirection = EPWM_CMP_UP;
    epwm3Info.epwmCompBDirection = EPWM_CMP_DOWN;
    epwm3Info.epwmTimerIntCount = 0U;
    epwm3Info.epwmModule = myEPWM3_BASE;
    epwm3Info.epwmMaxCompA = EPWM3_MAX_CMPA;
    epwm3Info.epwmMinCompA = EPWM3_MIN_CMPA;
    epwm3Info.epwmMaxCompB = EPWM3_MAX_CMPB;
    epwm3Info.epwmMinCompB = EPWM3_MIN_CMPB;
}

//
// updateCompare - Function to update the frequency
//
void updateCompare(epwmInformation *epwmInfo)
{
    uint16_t compAValue;
    uint16_t compBValue;

    compAValue = EPWM_getCounterCompareValue(epwmInfo->epwmModule,
                                             EPWM_COUNTER_COMPARE_A);

    compBValue = EPWM_getCounterCompareValue(epwmInfo->epwmModule,
                                             EPWM_COUNTER_COMPARE_B);

    //
    //  Change the CMPA/CMPB values every 10th interrupt.
    //
    if(epwmInfo->epwmTimerIntCount == 10U)
    {
        epwmInfo->epwmTimerIntCount = 0U;

        //
        // If we were increasing CMPA, check to see if we reached the max
        // value. If not, increase CMPA else, change directions and decrease
        // CMPA
        //
        if(epwmInfo->epwmCompADirection == EPWM_CMP_UP)
        {
            if(compAValue < (epwmInfo->epwmMaxCompA))
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            ++compAValue);
            }
            else
            {
                epwmInfo->epwmCompADirection = EPWM_CMP_DOWN;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            --compAValue);
            }
        }
        //
        // If we were decreasing CMPA, check to see if we reached the min
        // value. If not, decrease CMPA else, change directions and increase
        // CMPA
        //
        else
        {
            if( compAValue == (epwmInfo->epwmMinCompA))
            {
                epwmInfo->epwmCompADirection = EPWM_CMP_UP;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            ++compAValue);
            }
            else
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_A,
                                            --compAValue);
            }
        }

        //
        // If we were increasing CMPB, check to see if we reached the max
        // value. If not, increase CMPB else, change directions and decrease
        // CMPB
        //
        if(epwmInfo->epwmCompBDirection == EPWM_CMP_UP)
        {
            if(compBValue < (epwmInfo->epwmMaxCompB))
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                epwmInfo->epwmCompBDirection = EPWM_CMP_DOWN;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
        //
        // If we were decreasing CMPB, check to see if we reached the min
        // value. If not, decrease CMPB else, change directions and increase
        // CMPB
        //
        else
        {
            if(compBValue == (epwmInfo->epwmMinCompB))
            {
                epwmInfo->epwmCompBDirection = EPWM_CMP_UP;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
    }
    else
    {
        epwmInfo->epwmTimerIntCount++;
    }
}
