//###########################################################################
//
// FILE:   lcm.c
//
// TITLE:  C28x LCM driver.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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
//###########################################################################

#include <stdbool.h>
#include <stdint.h>
#include "lcm.h"

//*****************************************************************************
//
// LCM_runSelfTest
//
//*****************************************************************************
LCM_Status LCM_runSelfTest(uint32_t base)
{
    LCM_Status ret;
    uint16_t count = 0;

    ASSERT(LCM_isBaseValid(base));

    //
    // Check if Lockstep feature is disabled.
    // Check for any pending functional failure or test failure
    //
    if(!LCM_isLockStepEnabled(base)                       ||
       (LCM_getLockStepCompareStatus(base)   == LCM_FAIL) ||
       (LCM_getSelfTestStatus(base)          == LCM_FAIL) ||
       (LCM_getComp1ErrForceTestStatus(base) == LCM_FAIL) ||
       (LCM_getComp2ErrForceTestStatus(base) == LCM_FAIL))
    {
        ret = LCM_NOT_RUN;
    }
    else
    {
        //
        // Enable self test and wait for completion.
        // Use timeout for the wait
        //
        HWREG_BP(base + LCM_O_CONTROL) |= LCM_CONTROL_STEN;
        while(((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_STDONE) == 0U) || 
              (count == 20U))
        {
            count++;
        };

        if((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_STPASS) == 0U)
        {
            ret = LCM_FAIL;
        }
        else
        {
            ret = LCM_PASS;
        }

        //
        // Clear the flags
        //
        HWREG_BP(base + LCM_O_STATUS_CLEAR) = LCM_STATUS_CLEAR_STDONE |
                                              LCM_STATUS_CLEAR_STPASS;
    }

    return(ret);
}


//*****************************************************************************
//
// LCM_runComp1ErrorForceTest
//
//*****************************************************************************
LCM_Status LCM_runComp1ErrorForceTest(uint32_t base)
{
    LCM_Status ret;
    uint16_t count = 0;

    ASSERT(LCM_isBaseValid(base));

    //
    // Check if Lockstep feature is disabled.
    // Check for any pending functional failure or test failure
    //
    if(!LCM_isLockStepEnabled(base)                       ||
       (LCM_getLockStepCompareStatus(base)   == LCM_FAIL) ||
       (LCM_getSelfTestStatus(base)          == LCM_FAIL) ||
       (LCM_getComp1ErrForceTestStatus(base) == LCM_FAIL) ||
       (LCM_getComp2ErrForceTestStatus(base) == LCM_FAIL))
    {
        ret = LCM_NOT_RUN;
    }
    else
    {
        //
        // Force comparator-1 lockstep compare error and wait for completion
        // Use timeout for the wait
        //
        HWREG_BP(base + LCM_O_CONTROL) |= LCM_CONTROL_CMP1_ERR_FORCE;
        while(((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_CMP1_ERR_FORCE_DONE)
                == 0U) || (count == 20U))
        {
            count++;
        }

        if((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_CMP1_ERR_FORCE_PASS) == 0U)
        {
            ret = LCM_FAIL;
        }
        else
        {
            ret = LCM_PASS;
        }

        //
        // Clear the flags
        //
        HWREG_BP(base + LCM_O_STATUS_CLEAR) = LCM_STATUS_CMP1_ERR_FORCE_DONE |
                                              LCM_STATUS_CMP1_ERR_FORCE_PASS;
    }

    return(ret);
}

//*****************************************************************************
//
// LCM_runComp2ErrorForceTest
//
//*****************************************************************************
LCM_Status LCM_runComp2ErrorForceTest(uint32_t base)
{
    LCM_Status ret;
    uint16_t count = 0;

    ASSERT(LCM_isBaseValid(base));

    //
    // Check if Lockstep feature is disabled.
    // Check for any pending functional failure or test failure
    //
    if(!LCM_isLockStepEnabled(base)                       ||
       (LCM_getLockStepCompareStatus(base)   == LCM_FAIL) ||
       (LCM_getSelfTestStatus(base)          == LCM_FAIL) ||
       (LCM_getComp1ErrForceTestStatus(base) == LCM_FAIL) ||
       (LCM_getComp2ErrForceTestStatus(base) == LCM_FAIL))
    {
        ret = LCM_NOT_RUN;
    }
    else
    {
        //
        // Force comparator-1 lockstep compare error and wait for completion
        // Use timeout for the wait
        //
        HWREG_BP(base + LCM_O_CONTROL) |= LCM_CONTROL_CMP2_ERR_FORCE;
        while(((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_CMP2_ERR_FORCE_DONE)
                == 0U) || (count == 20U))
        {
            count++;
        }

        if((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_CMP2_ERR_FORCE_PASS) == 0U)
        {
            ret = LCM_FAIL;
        }
        else
        {
            ret = LCM_PASS;
        }

        //
        // Clear the flags
        //
        HWREG_BP(base + LCM_O_STATUS_CLEAR) = LCM_STATUS_CMP2_ERR_FORCE_DONE |
                                              LCM_STATUS_CMP2_ERR_FORCE_PASS;
    }

    return(ret);
}
