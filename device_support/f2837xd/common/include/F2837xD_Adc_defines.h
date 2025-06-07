//###########################################################################
//
// FILE:   F2837xD_Adc_defines.h
//
// TITLE:  #defines used in ADC examples
//
//###########################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2013-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2837xD_ADC_DEFINES_H
#define F2837xD_ADC_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define ADC_CHANNEL_0        0
#define ADC_CHANNEL_1        1
#define ADC_CHANNEL_2        2
#define ADC_CHANNEL_3        3
#define ADC_CHANNEL_4        4
#define ADC_CHANNEL_5        5
#define ADC_CHANNEL_6        6
#define ADC_CHANNEL_7        7

#define ADC_CHANNEL_8        8
#define ADC_CHANNEL_9        9
#define ADC_CHANNEL_10       10
#define ADC_CHANNEL_11       11
#define ADC_CHANNEL_12       12
#define ADC_CHANNEL_13       13
#define ADC_CHANNEL_14       14
#define ADC_CHANNEL_15       15

//
//definitions for specifying an ADC
//
#define ADC_ADCA 0
#define ADC_ADCB 1
#define ADC_ADCC 2
#define ADC_ADCD 3

//
//definitions for selecting ADC resolution
//
#ifndef _DUAL_HEADERS
#define ADC_RESOLUTION_12BIT 0
#define ADC_RESOLUTION_16BIT 1
#else
#define ADC_BITRESOLUTION_12BIT 0
#define ADC_BITRESOLUTION_16BIT 1
#endif
//
//definitions for selecting ADC signal mode
//(single-ended mode is only a valid mode for 12-bit resolution)
//
#define ADC_SIGNALMODE_SINGLE 0
#define ADC_SIGNALMODE_DIFFERENTIAL 1

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_ADC_DEFINES_H

//
// End of file
//
