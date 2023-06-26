//###########################################################################
//
// FILE:   f2838x_tempsensorconv.c
//
// TITLE:  F2838x Temperature Sensor Conversion Functions
//
//###########################################################################
//
//
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

//
// Included Files
//
#include "f2838x_device.h"
#include "f2838x_examples.h"

//
// Defines
//

//
// Value to be added to shift from Celsius to Kelvin
//
#define KELVIN              273

#define ADC_VREFHI_SAMPLE   4096.0

//
// Slope of temperature sensor
//
#define TEMPSENSOR_SLOPE_OTP_ADDR   ((float32 *)0x701C8)

//
// Offset of temperature sensor which is ADC code
// corresponding to sensor output at 0 deg. C
//
#define TEMPSENSOR_OFFSET_OTP_ADDR  ((float32 *)0x701CA)

//
// Globals
//
float32 tempSensor_tempSlope;
float32 tempSensor_tempOffset;
float32 tempSensor_scaleFactor;

//
// InitTempSensor - Initialize the temperature sensor by powering up the
//                  sensor, loading the calibration values from OTP to RAM,
//                  and recording the intended VREFHI voltage.
//                  Note: This function doesn't support VREFLO != 0.0V,
//                  but this could be implemented if desired.
//
#ifdef CPU1
void InitTempSensor(float32 vrefhi_voltage)
{
    EALLOW;

    //
    // Power up the temperature sensor
    //
    AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 1;

    //
    // Delay to allow the sensor to power up
    //
    DELAY_US(1000);

    EDIS;

    //
    // Need to remember VREFHI voltage so that sensor readings can be scaled
    // to match 2.5V values used for calibration data.
    //
    tempSensor_scaleFactor = vrefhi_voltage;

    //
    // Pull the slope and offset from OTP
    //
    tempSensor_tempSlope = *(TEMPSENSOR_SLOPE_OTP_ADDR);
    tempSensor_tempOffset = *(TEMPSENSOR_OFFSET_OTP_ADDR);
}
#endif
//
// GetTemperatureC - This function uses the reference data stored in OTP to
//                   convert the raw temperature sensor reading into degrees C
//
int16_t GetTemperatureC(int16 sensorSample)
{
    return((int16_t)((((float32)sensorSample * tempSensor_scaleFactor /
                       ADC_VREFHI_SAMPLE) - tempSensor_tempOffset)    /
                     tempSensor_tempSlope));
}

//
// GetTemperatureK - This function uses the reference data stored in OTP to
//                   convert the raw temperature sensor reading into degrees K
//
int16_t GetTemperatureK(int16 sensorSample)
{
    return((int16_t)(((((float32)sensorSample * tempSensor_scaleFactor /
                        ADC_VREFHI_SAMPLE) - tempSensor_tempOffset)    /
                     tempSensor_tempSlope) + KELVIN));
}

//
// End of file
//
