//###########################################################################
//
// FILE:   f280013x_tempsensorconv.c
//
// TITLE:  F280013x Temperature Sensor Conversion Functions
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "f280013x_device.h"
#include "f280013x_examples.h"

//
// Defines
//

#define ADC_EXT_REF_TSSLOPE  (*(int16_t *)((uintptr_t)0x701C8)) //Slope of temperature sensor
#define ADC_EXT_REF_TSOFFSET (*(int16_t *)((uintptr_t)0x701C9)) //Temperature offset

#define ADC_INT_REF_TSSLOPE  (*(int16_t *)((uintptr_t)0x701CA))
#define ADC_INT_REF_TSOFFSET (*(int16_t *)((uintptr_t)0x701CB))


//
// Globals
//
int16_t tempSensor_tempSlope;
int16_t tempSensor_tempOffset;
float32_t tempSensor_scaleFactor;

//
// InitTempSensor - Initialize the temperature sensor by powering up the
//                  sensor, loading the calibration values from OTP to RAM,
//                  and recording the intended VREFHI voltage.
//                  Note: This function doesn't support VREFLO != 0.0V,
//                  but this could be implemented if desired.
//
void InitTempSensor(float vrefhi_voltage)
{
    EALLOW;

    //
    //power up the the temperature sensor
    //
    AnalogSubsysRegs.TSNSCTL.bit.ENABLE = 1;

    //
    //delay to allow the sensor to power up
    //
    DELAY_US(1000);


    //
    //need to remember VREFHI voltage so that sensor readings can be scaled
    //to match 2.5V values used for calibration data.
    //
    tempSensor_scaleFactor = vrefhi_voltage;

    EDIS;
}

//
// GetTemperatureC - This function uses the reference data stored in OTP to
//                   convert the raw temperature sensor reading into degrees C
//
int16_t GetTemperatureC(uint16_t sensorSample)
{
    float32_t temp;
    temp = (float32_t)((tempSensor_scaleFactor / 2.5F) * sensorSample);

    //
    //Read the Slope and Offset from OTP
    //
    tempSensor_tempSlope = ADC_EXT_REF_TSSLOPE;
    tempSensor_tempOffset = ADC_EXT_REF_TSOFFSET;

    return((int16_t)((((int32_t)temp - tempSensor_tempOffset) * 4096) /
            tempSensor_tempSlope));

}

//
// GetTemperatureK - This function uses the reference data stored in OTP to
//                   convert the raw temperature sensor reading into degrees K
//
int16_t GetTemperatureK(uint16_t sensorSample)
{
    float32_t temp;

   //
   // Read temp sensor slope and offset locations from OTP and convert
   //
    tempSensor_tempSlope = ADC_EXT_REF_TSSLOPE;
    tempSensor_tempOffset = ADC_EXT_REF_TSOFFSET;
   temp = (float32_t)sensorSample * (tempSensor_scaleFactor / 2.5F);
   return((int16_t)(((((int32_t)temp - tempSensor_tempOffset) * 4096) /
           tempSensor_tempSlope) + 273));
}

//
// End of file
//
