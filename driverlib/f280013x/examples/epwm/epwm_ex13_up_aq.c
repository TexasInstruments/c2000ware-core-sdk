//###########################################################################
//
// FILE:   epwm_ex13_up_aq.c
//
// TITLE:  Action Qualifier Module - Using up count.
//
//! \addtogroup driver_example_list
//! <h1> EPWM Action Qualifier (epwm_up_aq)</h1>
//!
//! This example configures ePWM1, ePWM2, ePWM3 to produce an
//! waveform with independent modulation on EPWMxA and
//! EPWMxB.
//!
//! The compare values CMPA and CMPB are modified within the ePWM's ISR.
//!
//! The TB counter is in up count mode for this example.
//!
//! View the EPWM1A/B(GPIO0 & GPIO1), EPWM2A/B(GPIO2 & GPIO3)
//! and EPWM3A/B(GPIO4 & GPIO5) waveforms via an oscilloscope.
//!
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD  2000  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

#define EPWM2_TIMER_TBPRD  2000  // Period register
#define EPWM2_MAX_CMPA     1950
#define EPWM2_MIN_CMPA       50
#define EPWM2_MAX_CMPB     1950
#define EPWM2_MIN_CMPB       50

#define EPWM3_TIMER_TBPRD  2000  // Period register
#define EPWM3_MAX_CMPA      950
#define EPWM3_MIN_CMPA       50
#define EPWM3_MAX_CMPB     1950
#define EPWM3_MIN_CMPB     1050

#define EPWM_CMP_UP           1
#define EPWM_CMP_DOWN         0

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
} epwmInfo;

epwmInfo epwm1Info;
epwmInfo epwm2Info;
epwmInfo epwm3Info;

volatile uint16_t compAVal, compBVal;

//
//  Function Prototypes
//
void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);
__interrupt void epwm1ISR(void);
__interrupt void epwm2ISR(void);
__interrupt void epwm3ISR(void);
void updateCompare(epwmInfo*);

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
    // Disable pin locks and enable internal pull-ups.
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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);
    Interrupt_register(INT_EPWM2, &epwm2ISR);
    Interrupt_register(INT_EPWM3, &epwm3ISR);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure GPIO pins and EPWM Modules
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
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_EPWM2);
    Interrupt_enable(INT_EPWM3);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        asm ("  NOP");
    }
}

//
// epwm1ISR - EPWM1 ISR to update compare values
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
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// epwm2ISR - EPWM2 ISR to update compare values
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
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// epwm3ISR - EPWM3 ISR to update compare values
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
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// initEPWM1 Information
//
void initEPWM1()
{
   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct ePWM registers
   //

    // Start by increasing CMPA & CMPB
    epwm1Info.epwmCompADirection = EPWM_CMP_UP;
    epwm1Info.epwmCompBDirection = EPWM_CMP_UP;

    // Clear interrupt counter
    epwm1Info.epwmTimerIntCount = 0;

    // Set base as ePWM1
    epwm1Info.epwmModule = myEPWM1_BASE;

    // Setup min/max CMPA/CMP values
    epwm1Info.epwmMaxCompA = EPWM1_MAX_CMPA;
    epwm1Info.epwmMinCompA = EPWM1_MIN_CMPA;
    epwm1Info.epwmMaxCompB = EPWM1_MAX_CMPB;
    epwm1Info.epwmMinCompB = EPWM1_MIN_CMPB;
}

//
// initEPWM2 Information
//
void initEPWM2()
{
    //
    // Information this example uses to keep track
    // of the direction the CMPA/CMPB values are
    // moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //

    // Start by increasing CMPA & decreasing CMPB
    epwm2Info.epwmCompADirection = EPWM_CMP_UP;
    epwm2Info.epwmCompBDirection = EPWM_CMP_DOWN;

    // Clear interrupt counter
    epwm2Info.epwmTimerIntCount = 0;

    // Set base as ePWM2
    epwm2Info.epwmModule = myEPWM2_BASE;

    // Setup min/max CMPA/CMP values
    epwm2Info.epwmMaxCompA = EPWM2_MAX_CMPA;
    epwm2Info.epwmMinCompA = EPWM2_MIN_CMPA;
    epwm2Info.epwmMaxCompB = EPWM2_MAX_CMPB;
    epwm2Info.epwmMinCompB = EPWM2_MIN_CMPB;
}

//
// initEPWM3 Information
//
void initEPWM3(void)
{
   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct ePWM registers
   //

    // Start by increasing CMPA & decreasing CMPB
    epwm3Info.epwmCompADirection = EPWM_CMP_UP;
    epwm3Info.epwmCompBDirection = EPWM_CMP_DOWN;

    // Start the count at 0
    epwm3Info.epwmTimerIntCount = 0;

    // Set base as ePWM3
    epwm3Info.epwmModule = myEPWM3_BASE;

    // Setup min/max CMPA/CMP values
    epwm3Info.epwmMaxCompA = EPWM3_MAX_CMPA;
    epwm3Info.epwmMinCompA = EPWM3_MIN_CMPA;
    epwm3Info.epwmMaxCompB = EPWM3_MAX_CMPB;
    epwm3Info.epwmMinCompB = EPWM3_MIN_CMPB;
}

//
// updateCompare - Update the compare values for the specified EPWM
//
void updateCompare(epwmInfo *epwm_info)
{
   //
   // Every 10'th interrupt, change the CMPA/CMPB values
   //
   if(epwm_info->epwmTimerIntCount == 10)
   {
       epwm_info->epwmTimerIntCount = 0;
       compAVal = EPWM_getCounterCompareValue(epwm_info->epwmModule,
                                              EPWM_COUNTER_COMPARE_A);
       compBVal = EPWM_getCounterCompareValue(epwm_info->epwmModule,
                                              EPWM_COUNTER_COMPARE_B);

       //
       // If we were increasing CMPA, check to see if
       // we reached the max value.  If not, increase CMPA
       // else, change directions and decrease CMPA
       //
       if(epwm_info->epwmCompADirection == EPWM_CMP_UP)
       {
           if(compAVal < epwm_info->epwmMaxCompA)
           {
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_A, ++compAVal);
           }
           else
           {
               epwm_info->epwmCompADirection = EPWM_CMP_DOWN;
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_A, --compAVal);
           }
       }

       //
       // If we were decreasing CMPA, check to see if
       // we reached the min value.  If not, decrease CMPA
       // else, change directions and increase CMPA
       //
       else
       {
           if(compAVal == epwm_info->epwmMinCompA)
           {
               epwm_info->epwmCompADirection = EPWM_CMP_UP;
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_A, ++compAVal);

           }
           else
           {
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_A, --compAVal);
           }
       }

       //
       // If we were increasing CMPB, check to see if
       // we reached the max value.  If not, increase CMPB
       // else, change directions and decrease CMPB
       //
       if(epwm_info->epwmCompBDirection == EPWM_CMP_UP)
       {
           if(compBVal < epwm_info->epwmMaxCompB)
           {
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_B, ++compBVal);
           }
           else
           {
               epwm_info->epwmCompBDirection = EPWM_CMP_DOWN;
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_B, --compBVal);

           }
       }

       //
       // If we were decreasing CMPB, check to see if
       // we reached the min value.  If not, decrease CMPB
       // else, change directions and increase CMPB
       //
       else
       {
           if(compBVal == epwm_info->epwmMinCompB)
           {
               epwm_info->epwmCompBDirection = EPWM_CMP_UP;
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_B, ++compBVal);
           }
           else
           {
               EPWM_setCounterCompareValue(epwm_info->epwmModule,
                                           EPWM_COUNTER_COMPARE_B, --compBVal);
           }
       }
   }

   //
   // Increment interrupt count if < 10
   //
   else
   {
      epwm_info->epwmTimerIntCount++;
   }
   return;
}
//
// End of file
//
