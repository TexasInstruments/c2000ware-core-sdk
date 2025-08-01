//###########################################################################
//
// FILE:   flash.c
//
// TITLE:  C28x Flash driver.
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

#include "flash.h"

#ifndef __cplusplus
#pragma CODE_SECTION(Flash_initModule, ".TI.ramfunc");
#endif

//*****************************************************************************
//
// Flash_initModule
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
void
Flash_initModule(uint32_t ctrlBase, uint32_t eccBase, uint16_t waitstates)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));
    ASSERT(Flash_isECCBaseValid(eccBase));
    ASSERT(waitstates <= 0xFU);


    //
    // Disable cache and prefetch mechanism before changing wait states
    //
    Flash_disableCache(ctrlBase);
    Flash_disablePrefetch(ctrlBase);

    //
    // Set waitstates according to frequency.
    //
    Flash_setWaitstates(ctrlBase, waitstates);

    //
    // Commit Flash Trims
    //

    //
    // Configure TRIMCTL.ENABLE to be valid
    //
    Flash_writeTrims(FLASH_O_TRIMCTL, FLASH_TRIMCTL_ENABLE_M, 
               FLASH_TRIMCTL_ENABLE_S, 1);

    //
    // Configure TRIMLOCKOTHER and TRIMLOCKREAD in TRIMLOCK register
    //
    Flash_writeTrims(FLASH_O_TRIMLOCK, FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_M, 
               FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_S, 3);

    //
    // Configure TRIMCOMMITREAD and TRIMCOMMITOTHER in TRIMCOMMIT register
    //
    Flash_writeTrims(FLASH_O_TRIMCOMMIT, 
               FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_M, 
               FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_S, 3);


    //
    // Enable cache and prefetch mechanism to improve performance of code
    // executed from flash.
    //
    Flash_enableCache(ctrlBase);
    Flash_enablePrefetch(ctrlBase);

    //
    // At reset, ECC is enabled.  If it is disabled by application software and
    // if application again wants to enable ECC.
    //
    Flash_enableECC(eccBase);

    //
    // Force a pipeline flush to ensure that the write to the last register
    // configured occurs before returning.
    //

    FLASH_DELAY_CONFIG;
}

