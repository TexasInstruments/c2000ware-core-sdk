//#############################################################################
//
// FILE:   clb_ex5_event_window.c
//
// TITLE:  CLB Event Window.
//
//! \addtogroup driver_example_list
//! <h1>CLB Event Window</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! This example uses the counter, FSM, and HLC sub-modules of the CLB to implement 
//! an event timing feature which detects whether an interrupt service routine 
//! takes too long to respond to an interrupt. The example configures four PWM 
//! modules to operate in up-count mode and generate a low-to-high edge on a timer 
//! zero match event. The zero match event also triggers a PWM ISR which, for the 
//! purposes of this example, contains a dummy payload of variable length. At the 
//! end of the ISR, a write operation takes place to a CLB GP register to indicate 
//! the ISR has ended.
//!
//
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.05.00.00
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



#include "driverlib.h"
#include "device.h"
#include "clb_config.h"
#include "clb.h"
#include "board.h"

#define EPWM1_TIMER_TBPRD  20000U
#define EPWM1_CMPA          1933U
#define EPWM1_CMPB          1933U

#define EPWM2_TIMER_TBPRD  25000U
#define EPWM2_CMPA          1933U
#define EPWM2_CMPB          1933U

#define EPWM3_TIMER_TBPRD  30000U
#define EPWM3_CMPA          1933U
#define EPWM3_CMPB          1933U

#define EPWM4_TIMER_TBPRD  35000U
#define EPWM4_CMPA          1933U
#define EPWM4_CMPB          1933U

// default interrupt payloads
#define ISR1_PAYLOAD         60U
#define ISR2_PAYLOAD         60U
#define ISR3_PAYLOAD         60U
#define ISR4_PAYLOAD         60U

void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);
void initEPWM4(void);

__interrupt void epwm1ISR(void);
__interrupt void epwm2ISR(void);
__interrupt void epwm3ISR(void);
__interrupt void epwm4ISR(void);
__interrupt void clb1ISR(void);
__interrupt void clb2ISR(void);
__interrupt void clb3ISR(void);
__interrupt void clb4ISR(void);

// GPREG settings:
// bit 2 = enable
// bit 1 = ISR end flag
// bit 0 not used
uint32_t gpreg1 = 4;
uint32_t gpreg2 = 4;
uint32_t gpreg3 = 4;
uint32_t gpreg4 = 4;

uint32_t payload_1 = ISR1_PAYLOAD;
uint32_t payload_2 = ISR2_PAYLOAD;
uint32_t payload_3 = ISR3_PAYLOAD;
uint32_t payload_4 = ISR4_PAYLOAD;

volatile uint16_t i = 0;
bool first_trip_1 = false;
bool first_trip_2 = false;
bool first_trip_3 = false;
bool first_trip_4 = false;


void main(void)
{
    Device_init();
    Device_initGPIO();

    // map interrupts
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_EPWM1, &epwm1ISR);
    Interrupt_register(INT_EPWM2, &epwm2ISR);
    Interrupt_register(INT_EPWM3, &epwm3ISR);
    Interrupt_register(INT_EPWM4, &epwm4ISR);
    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_register(INT_CLB2, &clb2ISR);
    Interrupt_register(INT_CLB3, &clb3ISR);
    Interrupt_register(INT_CLB4, &clb4ISR);

    Board_init();
    // initialize PWMs
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);   
    initEPWM1();
    initEPWM2();
    initEPWM3();
    initEPWM4();

    // initialize CLB tiles

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB3);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB4);

    initTILE1(myTILE1_BASE);
    initTILE2(myTILE2_BASE);
    initTILE3(myTILE3_BASE);
    initTILE4(myTILE4_BASE);

    // enable interrupts
    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_EPWM2);
    Interrupt_enable(INT_EPWM3);
    Interrupt_enable(INT_EPWM4);

    Interrupt_enable(INT_CLB1);
    Interrupt_enable(INT_CLB2);
    Interrupt_enable(INT_CLB3);
    Interrupt_enable(INT_CLB4);

    EINT;

    // enable CLB counters
    HWREG(0x3100) = 0x6;
    HWREG(0x3500) = 0x6;
    HWREG(0x3900) = 0x6;
    HWREG(0x3D00) = 0x6;
    
    CLB_setGPREG(myTILE1_BASE, gpreg1);
    CLB_setGPREG(myTILE2_BASE, gpreg2);
    CLB_setGPREG(myTILE3_BASE, gpreg3);
    CLB_setGPREG(myTILE4_BASE, gpreg4);

    // start PWMs
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    while(1)
    {
        asm(" NOP");
    }
}


//--- PWM initialization ---

void initEPWM1()
{
    EPWM_setTimeBasePeriod(myEPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);

    EPWM_enableSyncOutPulseSource(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);

    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_CMPA);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM1_CMPB);

    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(myEPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(myEPWM1_BASE);
    EPWM_setInterruptEventCount(myEPWM1_BASE, 1U);
}


void initEPWM2()
{
    EPWM_setTimeBasePeriod(myEPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM2_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0U);

    EPWM_disablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_setPhaseShift(myEPWM2_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM2_CMPA);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM2_CMPB);

    EPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(myEPWM2_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(myEPWM2_BASE);
    EPWM_setInterruptEventCount(myEPWM2_BASE, 1U);
}

void initEPWM3()
{
    EPWM_setTimeBasePeriod(myEPWM3_BASE, EPWM3_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM3_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM3_BASE, 0U);

    EPWM_disablePhaseShiftLoad(myEPWM3_BASE);
    EPWM_setPhaseShift(myEPWM3_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM3_CMPA);
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM3_CMPB);

    EPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(myEPWM3_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(myEPWM3_BASE);
    EPWM_setInterruptEventCount(myEPWM3_BASE, 1U);
}

void initEPWM4()
{
    EPWM_setTimeBasePeriod(myEPWM4_BASE, EPWM4_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM4_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM4_BASE, 0U);

    EPWM_disablePhaseShiftLoad(myEPWM4_BASE);
    EPWM_setPhaseShift(myEPWM4_BASE, 0U);

    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM4_CMPA);
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM4_CMPB);

    EPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(myEPWM4_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(myEPWM4_BASE);
    EPWM_setInterruptEventCount(myEPWM4_BASE, 1U);
}

//--- interrupt service routines ---

__interrupt void epwm1ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

   // ISR payload
    for (i=0; i<payload_1; i++)
    {
        asm(" NOP");
    }

    // pulse GPREG bit 2 to indicate ISR finished
    CLB_setGPREG(myTILE1_BASE, gpreg1 | 0x00000002);
    asm(" NOP");
    CLB_setGPREG(myTILE1_BASE, gpreg1);
}

__interrupt void epwm2ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM2_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

    // ISR payload
    for (i=0; i<payload_2; i++)
    {
        asm(" NOP");
    }

    // pulse GPREG bit 2 to indicate ISR finished
    CLB_setGPREG(myTILE2_BASE, gpreg2 | 0x00000002);
    asm(" NOP");
    CLB_setGPREG(myTILE2_BASE, gpreg2);
}

__interrupt void epwm3ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

    // ISR payload
    for (i=0; i<payload_3; i++)
    {
        asm(" NOP");
    }

    // pulse GPREG bit 2 to indicate ISR finished
    CLB_setGPREG(myTILE3_BASE, gpreg3 | 0x00000002);
    asm(" NOP");
    CLB_setGPREG(myTILE3_BASE, gpreg3);
}

__interrupt void epwm4ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM4_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

    // ISR payload
    for (i=0; i<payload_4; i++)
    {
        asm(" NOP");
    }

    // pulse GPREG bit 2 to indicate ISR finished
    CLB_setGPREG(myTILE4_BASE, gpreg4 | 0x00000002);
    asm(" NOP");
    CLB_setGPREG(myTILE4_BASE, gpreg4);
}

__interrupt void clb1ISR(void)
{
    if (!first_trip_1)
    {
        first_trip_1 = true;
    }
    else
    {
        asm(" ESTOP0");
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb2ISR(void)
{
    if (!first_trip_2)
    {
        first_trip_2 = true;
    }
    else
    {
        asm(" ESTOP0");
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb3ISR(void)
{
    if (!first_trip_3)
    {
        first_trip_3 = true;
    }
    else
    {
        asm(" ESTOP0");
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb4ISR(void)
{
    if (!first_trip_4)
    {
        first_trip_4 = true;
    }
    else
    {
        asm(" ESTOP0");
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

/* end of file */
