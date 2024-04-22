//###########################################################################
//
// FILE:  F2806x_OscComp.c
//
// TITLE:  F2806x oscillator compensation functions
//
// This file contains the functions which adjust the oscillator trim and compensate
// for frequency drift based on the current temperature sensor reading.
//
// This program makes use of variables stored in OTP during factory
// test.  These OTP locations on pre-TMS devices may not be populated.
// Ensure that the following memory locations in TI OTP are populated
// (not 0xFFFF) before use:
//
// 0x3D7E90 to 0x3D7EA4
//
// Note that these functions pull data from the OTP by calling functions which
// reside in OTP.  Therefore the OTP wait-states (controlled by
// FlashRegs.FOTPWAIT.bit.OTPWAIT) will significantly affect the time required
// to execute these functions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
//###########################################################################

//
// Included Files
//
#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

//
// Defines
//
#define FP_SCALE 32768       // Scale factor for Q15 fixed point numbers (2^15)
//
// Quantity added to Q15 numbers before converting to integer to round the 
// number
//
#define FP_ROUND FP_SCALE/2 

//
// Amount to add to Q16.15 fixed point number to shift from a fine trim range 
// of (-31 to 31) to (1 to 63).  This guarantees that the trim is positive and 
// can therefore be efficiently rounded
//
#define OSC_POSTRIM 32
#define OSC_POSTRIM_OFF FP_SCALE*OSC_POSTRIM

//
// The following functions return reference values stored in OTP.
//

//
// Slope used to compensate oscillator 1 (fine trim steps / ADC code). Stored
// in fixed point Q15 format.
//
#define getOsc1FineTrimSlope() (*(int16 (*)(void))0x3D7E90)()

//
// Oscillator 1 fine trim at high temp
//
#define getOsc1FineTrimOffset() (*(int16 (*)(void))0x3D7E93)()

//
// Oscillator 1 coarse trim
//
#define getOsc1CoarseTrim() (*(int16 (*)(void))0x3D7E96)()

//
// Slope used to compensate oscillator 2 (fine trim steps / ADC code). Stored
// in fixed point Q15 format.
//
#define getOsc2FineTrimSlope() (*(int16 (*)(void))0x3D7E99)()

//
// Oscillator 2 fine trim at high temp
//
#define getOsc2FineTrimOffset() (*(int16 (*)(void))0x3D7E9C)()

//
// Oscillator 2 coarse trim
//
#define getOsc2CoarseTrim() (*(int16 (*)(void))0x3D7E9F)()

//
// ADC reading of temperature sensor at reference temperature for compensation
//
#define getRefTempOffset() (*(int16 (*)(void))0x3D7EA2)()

//
// Function Prototypes
//
Uint16 GetOscTrimValue(int Coarse, int Fine);

//
// Osc1Comp - This function uses the temperature sensor sample reading to 
// perform internal oscillator 1 compensation with reference values stored in 
// OTP.
//
void
Osc1Comp(int16 sensorSample)
{
    int16 compOscFineTrim;

    EALLOW;
    compOscFineTrim = ((sensorSample - 
                        getRefTempOffset())*(int32)getOsc1FineTrimSlope() + 
                        OSC_POSTRIM_OFF + FP_ROUND )/FP_SCALE + 
                        getOsc1FineTrimOffset() - OSC_POSTRIM;
    if(compOscFineTrim > 31)
    {
		compOscFineTrim = 31;
	}
	else if(compOscFineTrim < -31)
    {
		compOscFineTrim = -31;
	} 
    SysCtrlRegs.INTOSC1TRIM.all = GetOscTrimValue(getOsc1CoarseTrim(), 
                                                  compOscFineTrim);
    EDIS;
}

//
// Osc2Comp - This function uses the temperature sensor sample reading to 
// perform internal oscillator 2 compensation with reference values stored in 
// OTP.
//
void
Osc2Comp(int16 sensorSample)
{
    int16 compOscFineTrim;

    EALLOW;
    compOscFineTrim = ((sensorSample - 
                        getRefTempOffset())*(int32)getOsc2FineTrimSlope() +
                        OSC_POSTRIM_OFF + FP_ROUND )/FP_SCALE + 
                        getOsc2FineTrimOffset() - OSC_POSTRIM;
    
    if(compOscFineTrim > 31)
    {
		compOscFineTrim = 31;
	}
	else if(compOscFineTrim < -31)
    {
		compOscFineTrim = -31;
	}
    
    SysCtrlRegs.INTOSC2TRIM.all = GetOscTrimValue(getOsc2CoarseTrim(), 
                                                  compOscFineTrim);
    EDIS;
}

//
// GetOscTrimValue - This function packs the coarse and fine trim into the 
// format of the oscillator trim register
//
Uint16
GetOscTrimValue(int Coarse, int Fine)
{
    Uint16 regValue = 0;

    if(Fine < 0)
    {
        regValue = ((-Fine) | 0x20) << 9;
    }
    else
    {
        regValue = Fine << 9;
    }
    if(Coarse < 0)
    {
        regValue |= ((-Coarse) | 0x80);
    }
    else
    {
        regValue |= Coarse;
    }
    return regValue;
}

//
// End of File
//

