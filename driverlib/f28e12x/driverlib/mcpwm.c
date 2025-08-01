//###########################################################################
//
// FILE:   mcpwm.c
//
// TITLE:  C28x MCPWM driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#include "mcpwm.h"

//*****************************************************************************
//
// MCPWM_setEmulationMode
//
//*****************************************************************************
void MCPWM_setEmulationMode(uint32_t base, MCPWM_EmulationMode emulationMode)
{
    //
    // Check the arguments.
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to FREE_SOFT bits
    //
    HWREG(base + MCPWM_O_TBCTL) =
           ((HWREGH(base + MCPWM_O_TBCTL) & (~MCPWM_TBCTL_FREE_SOFT_M)) |
            ((uint32_t)emulationMode << MCPWM_TBCTL_FREE_SOFT_S));
}

//*****************************************************************************
//
// MCPWM_configureSignal
//
//*****************************************************************************
void MCPWM_configureSignal(uint32_t base, const MCPWM_SignalParams *signalParams)
{
    float32_t tbClkInHz = 0.0F;
    uint16_t tbPrdVal = 0U;
    uint16_t cmp1AVal = 0U, cmp1BVal = 0U;
    uint16_t cmp2AVal = 0U, cmp2BVal = 0U;
    uint16_t cmp3AVal = 0U, cmp3BVal = 0U;

    //
    // Check the arguments.
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Valid values in the function for TBCTR Mode are UP, DOWN
    // and UP-DOWN count.
    //
    ASSERT((uint16_t)signalParams->tbCtrMode < 2U);

    //
    // Configure Time Base counter Clock
    //
    MCPWM_setClockPrescaler(base, signalParams->tbClkDiv);

    //
    // Configure Time Base Counter Mode
    //
    MCPWM_setTimeBaseCounterMode(base, signalParams->tbCtrMode);

    //
    // Calculate TBCLK, TBPRD and CMPx values to be configured for
    // achieving desired signal
    //
    tbClkInHz = ((float32_t)signalParams->sysClkInHz /
                 (float32_t)(1U << ((uint16_t)signalParams->tbClkDiv)));

    if(signalParams->tbCtrMode == MCPWM_COUNTER_MODE_UP)
    {
        tbPrdVal = (uint16_t)((tbClkInHz / signalParams->freqInHz) - 1.0f);
        cmp1AVal = (uint16_t)(signalParams->dutyVal1A *
                             (float32_t)(tbPrdVal + 1U));
        cmp1BVal = (uint16_t)(signalParams->dutyVal1B *
                             (float32_t)(tbPrdVal + 1U));

        cmp2AVal = (uint16_t)(signalParams->dutyVal2A *
                             (float32_t)(tbPrdVal + 1U));
        cmp2BVal = (uint16_t)(signalParams->dutyVal2B *
                             (float32_t)(tbPrdVal + 1U));
                     
        cmp3AVal = (uint16_t)(signalParams->dutyVal3A *
                             (float32_t)(tbPrdVal + 1U));
        cmp3BVal = (uint16_t)(signalParams->dutyVal3B *
                             (float32_t)(tbPrdVal + 1U));
    }
    else
    {
        tbPrdVal = (uint16_t)(tbClkInHz / (2.0f * signalParams->freqInHz));
        cmp1AVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal1A *
                              (float32_t)tbPrdVal))) + 0.5f);
        cmp1BVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal1B *
                              (float32_t)tbPrdVal))) + 0.5f);
        cmp2AVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal2A *
                              (float32_t)tbPrdVal))) + 0.5f);
        cmp2BVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal2B *
                              (float32_t)tbPrdVal))) + 0.5f);
        cmp3AVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal3A *
                              (float32_t)tbPrdVal))) + 0.5f);
        cmp3BVal = (uint16_t)(((float32_t)tbPrdVal -
                             ((signalParams->dutyVal3B *
                              (float32_t)tbPrdVal))) + 0.5f);

    }

    //
    // Configure TBPRD value
    //
    MCPWM_setTimeBasePeriodShadow(base, tbPrdVal);

    //
    // Default Configurations.
    //
    MCPWM_disablePhaseShiftLoad(base);
    MCPWM_setPhaseShift(base, 0U);
    MCPWM_setTimeBaseCounter(base, 0U);

    //
    // Setup shadow register load on ZERO
    //
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_1A,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_1B,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_2A,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_2B,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_3A,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    MCPWM_setCounterCompareShadowLoadMode(base,
                                         MCPWM_COUNTER_COMPARE_3B,
                                         MCPWM_COMP_LOAD_ON_CNTR_ZERO);
    //
    // Set Compare values
    //
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_1A,
                                cmp1AVal);
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_1B,
                                cmp1BVal);
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_2A,
                                cmp2AVal);
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_2B,
                                cmp2BVal);
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_3A,
                                cmp3AVal);
    MCPWM_setCounterCompareShadowValue(base, MCPWM_COUNTER_COMPARE_3B,
                                cmp3BVal);

    //
    // Set actions for mcpwmxA & mcpwmxB
    //
    if(signalParams->tbCtrMode == MCPWM_COUNTER_MODE_UP)
    {
        //
        // Set on Zero, clear on CMPA 
        //
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPA);
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPA);
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPA);

        if(signalParams->invertSignal1B == (bool) true)
        {
            //
            // Clear PWMxB on Zero and set on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
            
        }
        else
        {
            //
            // Set PWMxB on Zero and clear on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }
        if(signalParams->invertSignal2B == (bool) true)
        {
            //
            // Clear PWMxB on Zero and set on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
            
        }
        else
        {
            //
            // Set PWMxB on Zero and clear on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }
        if(signalParams->invertSignal3B == (bool) true)
        {
            //
            // Clear PWMxB on Zero and set on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
            
        }
        else
        {
            //
            // Set PWMxB on Zero and clear on CMPB 
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }
    }
    else
    {
        //
        // Clear PWMxA on Zero set on CMPA up, and clear on CMPA down
        //
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPA | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA);
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPA | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA);
        MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3A,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPA | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA);

        if(signalParams->invertSignal1B == (bool) true)
        {
            //
            // Set PWMxB on Zero, clear on CMPA up and Set on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
        }
        else
        {
            //
            // clear PWMxB on Zero, Set on CMPA up and clear on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_1B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }
        if(signalParams->invertSignal2B == (bool) true)
        {
            //
            // Set PWMxB on Zero, clear on CMPA up and Set on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
        }
        else
        {
            //
            // clear PWMxB on Zero, Set on CMPA up and clear on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_2B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }
        if(signalParams->invertSignal3B == (bool) true)
        {
            //
            // Set PWMxB on Zero, clear on CMPA up and Set on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB);
        }
        else
        {
            //
            // clear PWMxB on Zero, Set on CMPA up and clear on CMPB down
            //
            MCPWM_setActionQualifierActionCompleteShadow(base, MCPWM_AQ_OUTPUT_3B,
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_ZERO | 
                                 (uint16_t)MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
                                 (uint16_t)MCPWM_AQ_OUTPUT_LOW_UP_CMPB);
        }

    }
}


