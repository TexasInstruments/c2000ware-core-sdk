//###########################################################################
//
// FILE:   F2802x0_TempSensorConv.c
//
// TITLE:  F2802x0 ADC Temperature Sensor Conversion Functions
//
// This file contains functions necessary to convert the temperature sensor
// reading into degrees C or K.
//
// This program makes use of variables stored in OTP during factory
// test on 2802x0 TMS devices only.
// These OTP locations on pre-TMS devices may not be populated.
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
//###########################################################################

//
// Included Files
//
#include "F2802x0_Device.h"   // F2802x0 Headers Include File
#include "f2802x0_examples.h" // F2802x0 Examples Include File

//
// Defines
//

#define FP_SCALE 32768       // Scale factor for Q15 fixed point numbers (2^15)

//
// Added to Q15 numbers before converting to integer to round the number
//
#define FP_ROUND FP_SCALE/2

//
// Amount to add to Q15 fixed point numbers to shift from Celsius to Kelvin
// (Converting guarantees number is positive, which makes rounding more 
// efficient)
//
#define KELVIN 273
#define KELVIN_OFF FP_SCALE*KELVIN

//
// The following pointers to function calls are:
//

//
// Slope of temperature sensor (deg. C / ADC code). 
// Stored in fixed point Q15 format.
//
#define getTempSlope() (*(int (*)(void))0x3D7E80)()

//
// ADC code corresponding to temperature sensor output at 0 deg. C
//
#define getTempOffset() (*(int (*)(void))0x3D7E83)()

//
// GetTemperatureC - This function uses the reference data stored in OTP to 
// convert the raw temperature sensor reading into degrees C
//
int16_t
GetTemperatureC(int16_t sensorSample)
{
    return ((sensorSample - getTempOffset())*(int32_t)getTempSlope() + FP_ROUND
            + KELVIN_OFF)/FP_SCALE - KELVIN;
}

//
// GetTemperatureK - This function uses the reference data stored in OTP to 
// convert the raw temperature sensor reading into degrees K
//
int16_t
GetTemperatureK(int16_t sensorSample)
{
    return ((sensorSample - getTempOffset())*(int32_t)getTempSlope() + FP_ROUND
            + KELVIN_OFF)/FP_SCALE;
}

//
// End of File
//

