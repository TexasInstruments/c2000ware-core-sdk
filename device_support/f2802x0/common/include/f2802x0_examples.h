//###########################################################################
//
// FILE:   F2802x0_Examples.h
//
// TITLE:  F2802x0 Device Definitions.
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

#ifndef F2802x0_EXAMPLES_H
#define F2802x0_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
//
//#define DSP28_DIVSEL   0 // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1 // Disable /4 for SYSCKOUT
#define DSP28_DIVSEL   2 // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL   3 // Enable /1 for SYSCLKOUT

//
// Uncomment for 50 Mhz devices [50 Mhz = (10MHz * 10)/2]
//
#define DSP28_PLLCR   10

//#define DSP28_PLLCR    9

//
// Uncomment for 40 MHz devices [40 MHz = (10MHz * 8)/2]
//
//#define DSP28_PLLCR    8

//#define DSP28_PLLCR    7
//#define DSP28_PLLCR    6
//#define DSP28_PLLCR    5
//#define DSP28_PLLCR    4
//#define DSP28_PLLCR    3
//#define DSP28_PLLCR    2
//#define DSP28_PLLCR    1
//#define DSP28_PLLCR    0  // PLL is bypassed in this mode

//
//      Specify the clock rate of the CPU (SYSCLKOUT) in nS.
//
//      Take into account the input clock frequency and the PLL multiplier
//      selected in step 1.
//
//      Use one of the values provided, or define your own.
//      The trailing L is required tells the compiler to treat
//      the number as a 64-bit value.
//
//      Only one statement should be uncommented.
//
//      Example 1: 40 MHz devices:
//                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator
//
//                 In step 1 the user specified PLLCR = 0x8 for a
//                 40 MHz CPU clock (SYSCLKOUT = 40 MHz).
//
//                 In this case, the CPU_RATE will be 25.000L
//                 Uncomment the line: #define CPU_RATE 25.000L
//
//      Example 1: 50 MHz devices:
//                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator
//
//                 In step 1 the user specified PLLCR = 0xA for a
//                 50 MHz CPU clock (SYSCLKOUT = 50 MHz).
//
//                 In this case, the CPU_RATE will be 20.000L
//                 Uncomment the line: #define CPU_RATE 20.000L
//
#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   25.000L   // for a 40MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//
// Target device (in F2802x0_Device.h) determines CPU frequency
//  (for examples) - either 50 MHz (for 28026 and 28027) or 40 MHz 
//  (for 280230 and 280220). User does not have to change anything here.
//

//
// 280260||280270 devices only
//
#if (DSP28_280260PT||DSP28_280260DA||DSP28_280270PT||DSP28_280270DA)
    #define CPU_FRQ_50MHZ    1     //50 Mhz CPU Freq (10 MHz input clock)
    #define CPU_FRQ_40MHZ    0

//
// 280230||280220 devices
//
#elif (DSP28_280230PT||DSP28_280230DA||DSP28_280220PT||DSP28_280220DA)
    #define CPU_FRQ_50MHZ    0     // 40 MHz CPU Freq (10 MHz input clock)
    #define CPU_FRQ_40MHZ    1

//
// Unknown devices
//    
#else                           
    #define CPU_FRQ_50MHZ    0
    #define CPU_FRQ_40MHZ    1     // 40 MHz CPU Freq (10 MHz input clock)
#endif

//
// The following pointer to a function call calibrates the ADC and 
// internal oscillators
//
#define Device_cal (void   (*)(void))0x3D7C80

//
// Include Example Header Files
//

//
// Prototypes for global functions within the .c files.
//
#include "f2802x0_globalprototypes.h"
#include "f2802x0_epwm_defines.h"     // Macros used for PWM examples.
#include "f2802x0_i2c_defines.h"      // Macros used for I2C examples.

#define PARTNO_280270PT  0x0F
#define PARTNO_280270DA  0x0E
#define PARTNO_280260PT  0x07
#define PARTNO_280260DA  0x06
#define PARTNO_280230PT  0x0D
#define PARTNO_280230DA  0x0C
#define PARTNO_280220PT  0x05
#define PARTNO_280220DA  0x04

//
// Include files not used with DSP/BIOS
//
#ifndef DSP28_BIOS
#include "f2802x0_defaultisr.h"
#endif

//
// DO NOT MODIFY THIS LINE.
//
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / \
                                    (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x0_EXAMPLES_H definition

//
// End of file
//

