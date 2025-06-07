//#############################################################################
//
//! \file   f2802x0/common/source/timer.c
//!
//! \brief  Contains the various functions related to the timer (TIMER) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x0
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"
#include "timer.h"

//
// TIMER_clearFlag - 
//
void
TIMER_clearFlag(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->TCR |= (uint32_t)TIMER_TCR_TIF_BITS;

    return;
}

//
// TIMER_disableInt - 
//
void
TIMER_disableInt(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // clear the bits
    //
    timer->TCR &= (~(uint32_t)TIMER_TCR_TIE_BITS);

    return;
}

//
// TIMER_enableInt - 
//
void
TIMER_enableInt(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->TCR |= (uint32_t)TIMER_TCR_TIE_BITS;

    return;
}

//
// TIMER_getStatus - 
//
TIMER_Status_e
TIMER_getStatus(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // get the status
    //
    TIMER_Status_e status = (TIMER_Status_e)
                            (timer->TCR & (uint32_t)TIMER_TCR_TIF_BITS);

    return(status);
}

//
// TIMER_init -
//
TIMER_Handle
TIMER_init(void *pMemory, const size_t numBytes)
{
    TIMER_Handle timerHandle;

    if(numBytes < sizeof(TIMER_Obj))
    {
        return((TIMER_Handle)NULL);
    }

    //
    // assign the handle
    //
    timerHandle = (TIMER_Handle)pMemory;

    return(timerHandle);
}

//
// TIMER_reload - 
//
void
TIMER_reload(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // clear the bits
    //
    timer->TCR |= TIMER_TCR_TRB_BITS;

    return;
}

//
// TIMER_setDecimationFactor - 
//
void
TIMER_setDecimationFactor(TIMER_Handle timerHandle, const uint16_t decFactor)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->TPR |= ((uint32_t)(decFactor & 0xFF00) << 8) | 
                  (uint32_t)(decFactor & 0x00FF);

    return;
}

//
// TIMER_setEmulationMode - 
//
void
TIMER_setEmulationMode(TIMER_Handle timerHandle, 
                       const TIMER_EmulationMode_e mode)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // clear the bits
    //
    timer->TCR &= (~(uint32_t)TIMER_TCR_FREESOFT_BITS);

    //
    // set the bits
    //
    timer->TCR |= (uint32_t)mode;

    return;
}

//
// TIMER_setPeriod - 
//
void
TIMER_setPeriod(TIMER_Handle timerHandle, const uint32_t period)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->PRD = period;

    return;
}

//
// TIMER_setPreScaler - 
//
void
TIMER_setPreScaler(TIMER_Handle timerHandle, const uint16_t preScaler)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->TPR |= ((uint32_t)(preScaler & 0xFF00) << 8) |
                   ((uint32_t)(preScaler & 0x00FF) << 0);

    return;
}

//
// TIMER_start - 
//
void
TIMER_start(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // clear the bits
    //
    timer->TCR &= (~(uint32_t)TIMER_TCR_TSS_BITS);

    return;
}

//
// TIMER_stop - 
//
void
TIMER_stop(TIMER_Handle timerHandle)
{
    TIMER_Obj *timer = (TIMER_Obj *)timerHandle;

    //
    // set the bits
    //
    timer->TCR |= (uint32_t)TIMER_TCR_TSS_BITS;

    return;
}

//
// End of file
//

