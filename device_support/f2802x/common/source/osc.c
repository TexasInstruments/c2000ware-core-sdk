//#############################################################################
//
//! \file   f2802x/common/source/osc.c
//!
//! \brief  Contains the various functions related to the oscillator object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "osc.h"

//
// OSC_init -
//
OSC_Handle
OSC_init(void *pMemory, const size_t numBytes)
{
    OSC_Handle oscHandle;

    if(numBytes < sizeof(OSC_Obj))
    {
        return((OSC_Handle)NULL);
    }

    //
    // assign the handle
    //
    oscHandle = (OSC_Handle)pMemory;

    return(oscHandle);
}

//
// OSC_runCompensation -
//
void
OSC_runCompensation(OSC_Handle oscHandle, const OSC_Number_e oscNumber, 
                    int16_t sample)
{
    int16_t compOscFineTrim;
    int16_t compOscCourseTrim;

    compOscFineTrim = (sample - OSC_getRefTempOffset(oscHandle));

    if(oscNumber == OSC_Number_1)
    {
        compOscFineTrim = ((sample - OSC_getRefTempOffset(oscHandle))*
                           (int32_t)OSC_getFineTrimSlope1(oscHandle) + 
                           OSC_POSTRIM_OFF + FP_ROUND )/FP_SCALE + 
                           OSC_getFineTrimOffset1(oscHandle) - OSC_POSTRIM;
        compOscCourseTrim = OSC_getCourseTrim1(oscHandle);
    }
    else
    {
        compOscFineTrim = ((sample - OSC_getRefTempOffset(oscHandle))*
                           (int32_t)OSC_getFineTrimSlope2(oscHandle) + 
                           OSC_POSTRIM_OFF + FP_ROUND )/FP_SCALE + 
                           OSC_getFineTrimOffset2(oscHandle) - OSC_POSTRIM;
        compOscCourseTrim = OSC_getCourseTrim2(oscHandle);
    }

    if(compOscFineTrim > 31)
    {
        compOscFineTrim = 31;
    }
    else if(compOscFineTrim < -31)
    {
        compOscFineTrim = -31;
    } 

    if(compOscFineTrim < 0)
    {
        compOscFineTrim = (-compOscFineTrim) | 0x20;
    }
    if(compOscCourseTrim < 0)
    {
        compOscCourseTrim = (-compOscCourseTrim) | 0x80;
    }

    OSC_setCoarseTrim(oscHandle, oscNumber, (uint8_t)compOscCourseTrim);
    OSC_setFineTrim(oscHandle, oscNumber, (uint8_t)compOscFineTrim);
}

//
// OSC_setCoarseTrim -
//
void
OSC_setCoarseTrim(OSC_Handle oscHandle, const OSC_Number_e oscNumber, 
                  const uint8_t trimValue)
{
    OSC_Obj *osc = (OSC_Obj *)oscHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    if(oscNumber == OSC_Number_1)
    {
        //
        // clear the bits
        //
        osc->INTOSC1TRIM &= (~OSC_INTOSCnTRIM_COARSE_BITS);

        //
        // set the bits
        //
        osc->INTOSC1TRIM |= trimValue;
    }
    else
    {
        //
        // clear the bits
        //
        osc->INTOSC2TRIM &= (~OSC_INTOSCnTRIM_COARSE_BITS);

        //
        // set the bits
        //
        osc->INTOSC2TRIM |= trimValue;
    }
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// OSC_setFineTrim -
//
void
OSC_setFineTrim(OSC_Handle oscHandle, const OSC_Number_e oscNumber, 
                const uint8_t trimValue)
{
    OSC_Obj *osc = (OSC_Obj *)oscHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    if(oscNumber == OSC_Number_1)
    {
        //
        // clear the bits
        //
        osc->INTOSC1TRIM &= (~OSC_INTOSCnTRIM_FINE_BITS);

        //
        // set the bits
        //
        osc->INTOSC1TRIM |= trimValue << 9;
    }
    else
    {
        //
        // clear the bits
        //
        osc->INTOSC2TRIM &= (~OSC_INTOSCnTRIM_FINE_BITS);

        //
        // set the bits
        //
        osc->INTOSC2TRIM |= trimValue << 9;
    }
    
    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// End of file
//

