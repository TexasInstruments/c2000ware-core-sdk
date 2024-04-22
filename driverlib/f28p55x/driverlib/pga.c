//###########################################################################
//
// FILE:   pga.c
//
// TITLE:  C28x PGA driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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


#include "pga.h"

//
// All the API functions are in-lined in pga.h
//


//
// This macro calculates the PGA offset trim location in OTP memory required
// to calibrate PGA offset. Use this in the PGA_setOffsetTrimNMOS() and
// PGA_setOffsetTrimPMOS() function only.
//
#define PGA_getOffsetTrimNOTPLoc(offset)     ((uint16_t *)(0x72094U + offset))
#define PGA_getOffsetTrimPOTPLoc(offset)     ((uint16_t *)(0x72095U + offset))
//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY                          (0x5A5AU)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY                      (HWREGH(0x72092UL))


//*****************************************************************************
//
// ADC_setOffsetTrim
//
//*****************************************************************************
void
PGA_setOffsetTrimNMOS(uint32_t base)
{
    uint16_t offsetIndex = 0U, offsetTrim = 0U;

    ASSERT(PGA_isBaseValid(base));

    //
    // Get the offset index for the PGA base
    //
    switch(base)
    {
        case PGA1_BASE:
            offsetIndex = (uint16_t)(0U);
            break;
        case PGA2_BASE:
            offsetIndex = (uint16_t)(3U);
            break;
        case PGA3_BASE:
            offsetIndex = (uint16_t)(6U);
            break;
        default:
            //
            // Invalid base address!
            //
            offsetIndex = (uint16_t)(0U);
            break;
    }

    if(TI_OTP_DEV_PRG_KEY == TI_OTP_DEV_KEY)
    {
        offsetTrim = (*(uint16_t *)(PGA_getOffsetTrimNOTPLoc(offsetIndex)));
        offsetTrim = (offsetTrim & PGA_OFFSETTRIM_PGA_OFFSETTRIMN_M);
    }
    else
    {
        offsetTrim = 0U;
    }

    //
    // Configure the offset trim, offset trim is not updated here in case of
    // untrimmed devices.
    //
    if(offsetTrim > 0x0U)
    {
        EALLOW;
        HWREG(base + PGA_O_OFFSETTRIM) |= offsetTrim;
        EDIS;
    }
}

void
PGA_setOffsetTrimPMOS(uint32_t base)
{
    uint16_t offsetIndex = 0U;
    uint32_t offsetTrim = 0U;

    ASSERT(PGA_isBaseValid(base));

    //
    // Get the offset index for the PGA base
    //
    switch(base)
    {
        case PGA1_BASE:
            offsetIndex = (uint16_t)(0U);
            break;
        case PGA2_BASE:
            offsetIndex = (uint16_t)(3U);
            break;
        case PGA3_BASE:
            offsetIndex = (uint16_t)(6U);
            break;
        default:
            //
            // Invalid base address!
            //
            offsetIndex = (uint16_t)(0U);
            break;
    }

    if(TI_OTP_DEV_PRG_KEY == TI_OTP_DEV_KEY)
    {
        offsetTrim = (*(uint16_t *)(PGA_getOffsetTrimPOTPLoc(offsetIndex)));
        offsetTrim = (offsetTrim << PGA_OFFSETTRIM_PGA_OFFSETTRIMP_S);
    }
    else
    {
        offsetTrim = 0U;
    }

    //
    // Configure the offset trim, offset trim is not updated here in case of
    // untrimmed devices.
    //
    if(offsetTrim > 0x0U)
    {
        EALLOW;
        HWREG(base + PGA_O_OFFSETTRIM) |= offsetTrim;
        EDIS;
    }
}
