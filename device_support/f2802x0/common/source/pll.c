//#############################################################################
//
//! \file   f2802x0/common/source/pll.c
//!
//! \brief  Contains the various functions related to the phase-locked loop
//!         (PLL) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x0
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
#include "pll.h"

//
// PLL_disable -
//
void
PLL_disable(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLSTS |= PLL_PLLSTS_PLLOFF_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_disableClkDetect -
//
void
PLL_disableClkDetect(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLSTS |= PLL_PLLSTS_MCLKOFF_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_disableNormRdy -
//
void
PLL_disableNormRdy(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pll->PLLSTS &= (~PLL_PLLSTS_NORMRDYE_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_disableOsc -
//
void
PLL_disableOsc(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLSTS |= PLL_PLLSTS_OSCOFF_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_enable -
//
void
PLL_enable(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pll->PLLSTS &= (~PLL_PLLSTS_PLLOFF_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_enableClkDetect - 
//
void
PLL_enableClkDetect(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pll->PLLSTS &= (~PLL_PLLSTS_MCLKOFF_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_enableNormRdy - 
//
void
PLL_enableNormRdy(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLSTS |= (uint16_t)PLL_PLLSTS_NORMRDYE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_enableOsc-
//
void
PLL_enableOsc(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pll->PLLSTS &= (~PLL_PLLSTS_OSCOFF_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_getMultiplier -
//
PLL_Multiplier_e
PLL_getMultiplier(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    //
    // get the clock rate
    //
    PLL_Multiplier_e clkMult = (PLL_Multiplier_e)
                               (pll->PLLCR & PLL_PLLCR_DIV_BITS);

    return(clkMult);
}

//
// PLL_getClkStatus -
//
PLL_ClkStatus_e
PLL_getClkStatus(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    //
    // mask the bits
    //
    PLL_ClkStatus_e status = (PLL_ClkStatus_e)
                             (pll->PLLSTS & PLL_PLLSTS_MCLKSTS_BITS);

    return(status);
}

//
// PLL_getDivider -
//
PLL_DivideSelect_e
PLL_getDivider(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    //
    // mask the bits
    //
    PLL_DivideSelect_e divSelect = (PLL_DivideSelect_e)
                                   (pll->PLLSTS & PLL_PLLSTS_DIVSEL_BITS);

    return(divSelect);
}

//
// PLL_getLockStatus - 
//
PLL_LockStatus_e
PLL_getLockStatus(PLL_Handle pllHandle)
{
    volatile PLL_Obj *pll = (PLL_Obj *)pllHandle;

    //
    // mask the bits
    //
    PLL_LockStatus_e status = (PLL_LockStatus_e)
                              (pll->PLLSTS & PLL_PLLSTS_PLLLOCKS_BITS);

    return(status);
}

//
// PLL_init - 
//
PLL_Handle
PLL_init(void *pMemory, const size_t numBytes)
{
    PLL_Handle pllHandle;

    if(numBytes < sizeof(PLL_Obj))
    {
        return((PLL_Handle)NULL);
    }

    //
    // assign the handle
    //
    pllHandle = (PLL_Handle)pMemory;

    return(pllHandle);
}

//
// PLL_resetClkDetect - 
//
void
PLL_resetClkDetect(PLL_Handle pllHandle)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLSTS |= PLL_PLLSTS_MCLKCLR_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_setMultiplier - 
//
void
PLL_setMultiplier(PLL_Handle pllHandle, const PLL_Multiplier_e clkMult)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLCR = clkMult;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_setDivider - 
//
void
PLL_setDivider(PLL_Handle pllHandle, const PLL_DivideSelect_e divSelect)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    pll->PLLSTS &= (~PLL_PLLSTS_DIVSEL_BITS);

    //
    // set the bits
    //
    pll->PLLSTS |= divSelect;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// PLL_setup -
//
void
PLL_setup(PLL_Handle pllHandle, const PLL_Multiplier_e clkMult, 
          const PLL_DivideSelect_e divSelect)
{
    if(PLL_getClkStatus(pllHandle) == PLL_ClkStatus_Missing)
    {
        //
        // The clock is missing so we cannot setup the PLL correctly
        //
        asm(" ESTOP0");
    }
    
    //
    // Set divider to max value (/4) for safety
    //
    PLL_setDivider(pllHandle, PLL_DivideSelect_ClkIn_by_4);
    
    //
    // Set the desired multiplier
    //
    PLL_setMultiplier(pllHandle, clkMult);
    
    while(PLL_getLockStatus(pllHandle) != PLL_LockStatus_Done)
    {
        
    }
    
    //
    // Set the desired divider
    //
    PLL_setDivider(pllHandle, divSelect);
    
}

//
// PLL_setLockPeriod -
//
void
PLL_setLockPeriod(PLL_Handle pllHandle, const uint16_t lockPeriod)
{
    PLL_Obj *pll = (PLL_Obj *)pllHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // set the bits
    //
    pll->PLLLOCKPRD = lockPeriod;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// End of file
//

