//#############################################################################
//
//! \file   f2802x/common/source/comp.c
//!
//! \brief  Contains the various functions related to the comparator 
//!         (COMP) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "comp.h"

//
// Assembly files
//
extern void usDelay(unsigned long Count);

//
// COMP_disable - 
//
void
COMP_disable(COMP_Handle compHandle)
{
    COMP_Obj *comp = (COMP_Obj *)compHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    comp->COMPCTL &= ~COMP_COMPCTL_COMPDACE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// COMP_disableDac - 
//
void
COMP_disableDac(COMP_Handle compHandle)
{
    COMP_Obj *comp = (COMP_Obj *)compHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    comp->COMPCTL |= COMP_COMPCTL_COMPSOURCE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// COMP_enable - 
//
void
COMP_enable(COMP_Handle compHandle)
{
    COMP_Obj *comp = (COMP_Obj *)compHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    comp->COMPCTL |= COMP_COMPCTL_COMPDACE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// COMP_enableDac - 
//
void
COMP_enableDac(COMP_Handle compHandle)
{
    COMP_Obj *comp = (COMP_Obj *)compHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    comp->COMPCTL &= ~COMP_COMPCTL_COMPSOURCE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// COMP_init - 
//
COMP_Handle
COMP_init(void *pMemory, const size_t numBytes)
{
    COMP_Handle compHandle;

    if(numBytes < sizeof(COMP_Obj))
    {
        return((COMP_Handle)NULL);
    }

    //
    // assign the handle
    //
    compHandle = (COMP_Handle)pMemory;

    return(compHandle);
}

//
// End of file
//

