//#############################################################################
//
//! \file   f2802x0/common/source/flash.c
//!
//! \brief  Contains the various functions related to the flash object
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
#include "flash.h"

//
// FLASH_clear3VStatus -
//
void
FLASH_clear3VStatus(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // set the bits
    //
    flash->FSTATUS |= FLASH_FSTATUS_3VSTAT_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_disablePipelineMode, "ramfuncs");
//
// FLASH_disablePipelineMode - 
//
void
FLASH_disablePipelineMode(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    flash->FOPT &= (~FLASH_FOPT_ENPIPE_BITS);

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_enablePipelineMode, "ramfuncs");
//
// FLASH_enablePipelineMode - 
//
void
FLASH_enablePipelineMode(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;
    
    //
    // set the bits
    //
    flash->FOPT |= FLASH_FOPT_ENPIPE_BITS;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

//
// FLASH_get3VStatus - 
//
FLASH_3VStatus_e
FLASH_get3VStatus(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the status
    //
    FLASH_3VStatus_e status = (FLASH_3VStatus_e)(flash->FSTATUS & 
                               FLASH_FSTATUS_3VSTAT_BITS);

    return(status);
}

//
// FLASH_getActiveWaitCount -
//
uint16_t
FLASH_getActiveWaitCount(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the status
    //
    uint16_t count = (flash->FACTIVEWAIT & FLASH_FACTIVEWAIT_ACTIVEWAIT_BITS);

    return(count);
}

//
// FLASH_getActiveWaitStatus -
//
FLASH_CounterStatus_e
FLASH_getActiveWaitStatus(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the status
    //
    FLASH_CounterStatus_e status = (FLASH_CounterStatus_e)((flash->FSTATUS & 
                                    FLASH_FSTATUS_ACTIVEWAITS_BITS) >> 3);

    return(status);
}

//
// FLASH_getPowerMode -
//
FLASH_PowerMode_e
FLASH_getPowerMode(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the bits
    //
    FLASH_PowerMode_e mode = (FLASH_PowerMode_e)(flash->FSTATUS & 
                              FLASH_FSTATUS_PWRS_BITS);

    return(mode);
}

//
// FLASH_getStandbyWaitCount -
//
uint16_t
FLASH_getStandbyWaitCount(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the status
    //
    uint16_t count = (flash->FSTDBYWAIT & FLASH_FSTDBYWAIT_STDBYWAIT_BITS);

    return(count);
}

//
// FLASH_getStandbyWaitStatus -
//
FLASH_CounterStatus_e
FLASH_getStandbyWaitStatus(FLASH_Handle flashHandle)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    //
    // get the status
    //
    FLASH_CounterStatus_e status = (FLASH_CounterStatus_e)((flash->FSTATUS & 
                                    FLASH_FSTATUS_STDBYWAITS_BITS) >> 2);

    return(status);
}

//
// FLASH_init -
//
FLASH_Handle
FLASH_init(void *pMemory, const size_t numBytes)
{
    FLASH_Handle flashHandle;

    if(numBytes < sizeof(FLASH_Obj))
    {
        return((FLASH_Handle)NULL);
    }

    //
    // assign the handle
    //
    flashHandle = (FLASH_Handle)pMemory;

    return(flashHandle);
}

#pragma CODE_SECTION(FLASH_setActiveWaitCount, "ramfuncs");
//
// FLASH_setActiveWaitCount -
//
void
FLASH_setActiveWaitCount(FLASH_Handle flashHandle, const uint16_t count)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    flash->FACTIVEWAIT = count;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setNumPagedReadWaitStates, "ramfuncs");
//
// FLASH_setNumPagedReadWaitStates - 
//
void
FLASH_setNumPagedReadWaitStates(FLASH_Handle flashHandle, 
                                const FLASH_NumPagedWaitStates_e numStates)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    flash->FBANKWAIT &= (~FLASH_FBANKWAIT_PAGEWAIT_BITS);

    //
    // set the bits
    //
    flash->FBANKWAIT |= numStates;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setNumRandomReadWaitStates, "ramfuncs");
//
// FLASH_setNumRandomReadWaitStates - 
//
void
FLASH_setNumRandomReadWaitStates(FLASH_Handle flashHandle, 
                                 const FLASH_NumRandomWaitStates_e numStates)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    flash->FBANKWAIT &= (~FLASH_FBANKWAIT_RANDWAIT_BITS);

    //
    // set the bits
    //
    flash->FBANKWAIT |= numStates;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setOtpWaitStates, "ramfuncs");
//
// FLASH_setOtpWaitStates -
//
void
FLASH_setOtpWaitStates(FLASH_Handle flashHandle, 
                       const FLASH_NumOtpWaitStates_e numStates)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    flash->FOTPWAIT &= (~FLASH_FOTPWAIT_OTPWAIT_BITS);

    //
    // set the bits
    //
    flash->FOTPWAIT |= numStates;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setPowerMode, "ramfuncs");
//
// FLASH_setPowerMode - 
//
void
FLASH_setPowerMode(FLASH_Handle flashHandle, const FLASH_PowerMode_e mode)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    //
    // clear the bits
    //
    flash->FPWR &= (~FLASH_FPWR_PWR_BITS);

    //
    // set the bits
    //
    flash->FPWR |= mode;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setStandbyWaitCount, "ramfuncs");
//
// FLASH_setStandbyWaitCount - 
//
void
FLASH_setStandbyWaitCount(FLASH_Handle flashHandle, const uint16_t count)
{
    FLASH_Obj *flash = (FLASH_Obj *)flashHandle;

    ENABLE_PROTECTED_REGISTER_WRITE_MODE;

    flash->FSTDBYWAIT = count;

    DISABLE_PROTECTED_REGISTER_WRITE_MODE;

    return;
}

#pragma CODE_SECTION(FLASH_setup, "ramfuncs");
//
// FLASH_setup - 
//
void
FLASH_setup(FLASH_Handle flashHandle)
{
    //
    // Enable Flash Pipeline mode to improve performance of code executed from
    // Flash.
    //
    FLASH_enablePipelineMode(flashHandle);
    //FlashRegs.FOPT.bit.ENPIPE = 1;

    //
    //                CAUTION
    // Minimum waitstates required for the flash operating
    // at a given CPU rate must be characterized by TI.
    // Refer to the datasheet for the latest information.
    //

    #if (CPU_FRQ_50MHZ)
    //
    // Set the Paged Waitstate for the Flash
    //
    FLASH_setNumPagedReadWaitStates(flashHandle, FLASH_NumPagedWaitStates_2);
    //   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 2;

    //
    // Set the Random Waitstate for the Flash
    //
    FLASH_setNumRandomReadWaitStates(flashHandle, FLASH_NumRandomWaitStates_2);
    //FlashRegs.FBANKWAIT.bit.RANDWAIT = 2;

    //
    // Set the Waitstate for the OTP
    //
    FLASH_setOtpWaitStates(flashHandle, FLASH_NumOtpWaitStates_2);
    //FlashRegs.FOTPWAIT.bit.OTPWAIT = 2;

    #elif (CPU_FRQ_40MHZ)
    //
    // Set the Paged Waitstate for the Flash
    //
    FLASH_setNumPagedReadWaitStates(flashHandle, FLASH_NumPagedWaitStates_1);
    //FlashRegs.FBANKWAIT.bit.PAGEWAIT = 1;

    //
    // Set the Random Waitstate for the Flash
    //
    FLASH_setNumRandomReadWaitStates(flashHandle, FLASH_NumRandomWaitStates_1);
    //FlashRegs.FBANKWAIT.bit.RANDWAIT = 1;

    //
    // Set the Waitstate for the OTP
    //
    FLASH_setOtpWaitStates(flashHandle, FLASH_NumOtpWaitStates_1);
    //FlashRegs.FOTPWAIT.bit.OTPWAIT = 1;
    #endif
    
    //
    // CAUTION: ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
    //
    //FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
    FLASH_setStandbyWaitCount(flashHandle, 0x01FF);
    //FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
    FLASH_setActiveWaitCount(flashHandle, 0x01FF);

    //
    // Force a pipeline flush to ensure that the write to the last register 
    // configured occurs before returning.
    //
    asm(" RPT #7 || NOP");
}

//
// End of file
//

