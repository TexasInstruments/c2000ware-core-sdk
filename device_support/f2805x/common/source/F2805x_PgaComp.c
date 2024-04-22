//###########################################################################
//
// FILE:   F2805x_PgaComp.c
//
// TITLE:  F2805x PGA compensation functions
//
// This file contains the functions which adjust the oscillator trim and
// compensate for frequency drift based on the current temperature sensor
// reading.
//
// This program makes use of variables stored in OTP during factory
// test.  These OTP locations on pre-TMS devices may not be populated.
// Ensure that the following memory locations in TI OTP are populated
// (not 0xFFFF) before use:
//
// 0x3D7E61 to 0x3D7E8A
//
// Note that these functions pull data from the OTP by calling functions which
// reside in OTP.  Therefore the OTP wait-states (controlled by
// FlashRegs.FOTPWAIT.bit.OTPWAIT) will significantly affect the time required
// to execute these functions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F2805x_Device.h"     // F2805x Headerfile Include File
#include "F2805x_Examples.h"   // F2805x Examples Include File

//
// Defines
//
#define Q14_SHIFT        14
#define PGA_COMP_LOC     0x3D7E61
#define PGA_GAIN_INDEX   14
#define PGA_CHAN_INDEX    2

//
// PgaComp - This function takes a conversion result from an ADC channel with
// an amplifier and compensates for non-ideal behavior.
//
Uint16
PgaComp(Uint16 pga_ch, Uint16 pga_gain, Uint16 adc_conv)
{
    Uint16 offset_comp = *(Uint16*)(PGA_COMP_LOC + (PGA_GAIN_INDEX*pga_gain) +
                           (PGA_CHAN_INDEX*pga_ch));
    Uint16 gain_comp = *(Uint16*)(PGA_COMP_LOC + (PGA_GAIN_INDEX*pga_gain) +
                         (PGA_CHAN_INDEX*pga_ch) + 1);

    return ((((int32)adc_conv * gain_comp) -
             ((int32)offset_comp << Q14_SHIFT)) >> Q14_SHIFT);
}

//
// End of File
//

