//###########################################################################
//
// FILE:    f280013x_adc.c
//
// TITLE:   F28002x ADC Support Functions.
//
//###########################################################################
//
//
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

//
// Included Files
//
#include "f280013x_device.h"      // Header File Include File
#include "f280013x_examples.h"    // Examples Include File

//
// SetVREF - Set Vref mode. Function to select reference mode and offset trim.
// Offset trim for Internal VREF 3.3 is unique.  All other modes use the same
// offset trim. Also note that when the mode parameter is ADC_EXTERNAL, the
// ref parameter has no effect.
//
// In this device, the bandgaps are common for all the ADC instances,
// hence common Vref configuration needs to be done for all the ADCs. This
// API configures same Vref configuration for all the supported ADCs in the
// device.
//
void SetVREF(int module, int mode, int ref)
{
    Uint16 *offset, offsetShiftVal;

    if((mode == ADC_INTERNAL) && (ref == ADC_VREF3P3))
    {
        offsetShiftVal = 8U;         // Internal / 1.65v mode offset
    }
    else
    {
        offsetShiftVal = 0U;        // All other modes
    }

    uint32_t *offsetKey;

    //
    // Set up pointer to offset trim in OTP for ADCA.
    //

    //
    // Check if MP3 trim key matches with 0x5A5A5A5A
    // If not, check for MP1 trim key.
    //
    offsetKey = (uint32_t *)0x71114UL;
    if(*offsetKey == 0x5A5A5A5AUL)
    {
        offset = (Uint16 *)((Uint32)0x71116U);
    }
    else
    {
        offsetKey = (uint32_t *)0x7103CUL;
        if(*offsetKey == 0x5A5A5A5AUL)
        {
            offset = (Uint16 *)((Uint32)0x7103EU);
        }
        else
        {
            offset = 0U;
        }
    }

    EALLOW;

    //
    // Get offset trim from OTP and write it to the register for ADCA.
    //
    AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset >> offsetShiftVal) & 0xFFU;

    //
    // Set up pointer to offset trim in OTP for ADCC.
    //

    //
    // Check if MP3 trim key matches with 0x5A5A5A5A
    // If not, check for MP1 trim key.
    //
    offsetKey = (uint32_t *)0x71114UL;
    if(*offsetKey == 0x5A5A5A5AUL)
    {
        offset = (Uint16 *)((Uint32)0x71117U);
    }
    else
    {
        offsetKey = (uint32_t *)0x7103CUL;
        if(*offsetKey == 0x5A5A5A5AUL)
        {
            offset = (Uint16 *)((Uint32)0x7103FU);
        }
        else
        {
            offset = 0U;
        }
    }

    //
    // Get offset trim from OTP and write it to the register for ADCC.
    //
    AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset >> offsetShiftVal) & 0xFFU;

    //
    // Configure the reference mode for all ADCs (internal or external).
    //
    AnalogSubsysRegs.ANAREFCTL.bit.ANAREFSEL = mode;

    //
    // Configure the reference voltage for all ADCs (3.3V or 2.5V).
    //
    AnalogSubsysRegs.ANAREFCTL.bit.ANAREF2P5SEL = ref;

    EDIS;
}

//
// End of File
//
