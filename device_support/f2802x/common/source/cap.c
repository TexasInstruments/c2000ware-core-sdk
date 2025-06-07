//#############################################################################
//
//! \file   f2802x/common/source/cap.c
//!
//! \brief  Contains the various functions related to the serial 
//!         communications interface (CAP) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
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
#include "cap.h"

//
// CAP_init - 
//
CAP_Handle
CAP_init(void *pMemory, const size_t numBytes)
{
    CAP_Handle capHandle;

    if(numBytes < sizeof(CAP_Obj))
    {
        return((CAP_Handle)NULL);
    }

    //
    // assign the handle
    //
    capHandle = (CAP_Handle)pMemory;

    return(capHandle);
}

//
// CAP_disableCaptureLoad - 
//
void
CAP_disableCaptureLoad(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL1 &= ~CAP_ECCTL1_CAPLDEN_BITS;

    return;
}

//
// CAP_disableSyncIn -
//
void
CAP_disableSyncIn(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // set the bit
    //
    cap->ECCTL2 &= ~CAP_ECCTL2_SYNCIEN_BITS;

    return;
}

//
// CAP_disableInt - 
//
void
CAP_disableInt(CAP_Handle capHandle, const CAP_Int_Type_e intType)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECEINT &= ~intType;

    return;
}

//
// CAP_disableTimestampCounter -
//
void
CAP_disableTimestampCounter(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;
    
    //
    // clear the bits
    //
    cap->ECCTL2 &= ~CAP_ECCTL2_TSCTRSTOP_BITS;

    return;
}

//
// CAP_enableCaptureLoad - 
//
void
CAP_enableCaptureLoad(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;
    
    //
    // clear the bits
    //
    cap->ECCTL1 |= CAP_ECCTL1_CAPLDEN_BITS;

    return;
}

//
// CAP_enableInt - 
//
void
CAP_enableInt(CAP_Handle capHandle, const CAP_Int_Type_e intType)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECEINT |= intType;

    return;
}

//
// CAP_enableSyncIn - 
//
void
CAP_enableSyncIn(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // set the bit
    //
    cap->ECCTL2 |= CAP_ECCTL2_SYNCIEN_BITS;

    return;
}

//
// CAP_enableTimestampCounter - 
//
void
CAP_enableTimestampCounter(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 |= CAP_ECCTL2_TSCTRSTOP_BITS;

    return;
}

//
// CAP_setCapEvtPolarity -
//
void
CAP_setCapEvtPolarity(CAP_Handle capHandle, const CAP_Event_e event, 
                      const CAP_Polarity_e polarity)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL1 &= ~(1 << (2 * event));

    //
    // Set the new value
    //
    cap->ECCTL1 |= (polarity << (2 * event));

    return;
}

//
// CAP_setCapEvtReset - 
//
void
CAP_setCapEvtReset(CAP_Handle capHandle, const CAP_Event_e event, 
                   const CAP_Reset_e reset)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL1 &= ~(1 << (1 + (2 * event)));

    //
    // Set the new value
    //
    cap->ECCTL1 |= (reset << (1 + (2 * event)));

    return;
}

//
// CAP_setCapContinuous -
//
void
CAP_setCapContinuous(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 &= (~CAP_ECCTL2_CONTONESHOT_BITS);

    return;
}

//
// CAP_setCapOneShot -
//
void
CAP_setCapOneShot(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;
    
    //
    // clear the bits
    //
    cap->ECCTL2 |= CAP_ECCTL2_CONTONESHOT_BITS;

    return;
}

//
// CAP_setModeCap - 
//
void
CAP_setModeCap(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 &= (~CAP_ECCTL2_CAPAPWM_BITS);

    return;
}

//
// CAP_setModeApwm -
//
void
CAP_setModeApwm(CAP_Handle capHandle)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 |= CAP_ECCTL2_CAPAPWM_BITS;

    return;
}

//
// CAP_setStopWrap -
//
void
CAP_setStopWrap(CAP_Handle capHandle, const CAP_Stop_Wrap_e stopWrap)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 &= (~CAP_ECCTL2_STOP_WRAP_BITS);

    //
    // Set the new value
    //
    cap->ECCTL2 |= stopWrap;

    return;
}

//
// CAP_setSyncOut -
//
void
CAP_setSyncOut(CAP_Handle capHandle, const CAP_SyncOut_e syncOut)
{
    CAP_Obj *cap = (CAP_Obj *)capHandle;

    //
    // clear the bits
    //
    cap->ECCTL2 &= (~CAP_ECCTL2_SYNCOSEL_BITS);
    
    //
    // Set the new value
    //
    cap->ECCTL2 |= syncOut;

    return;
}

//
// End of file
//

