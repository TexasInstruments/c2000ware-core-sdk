//###########################################################################
//
// FILE:   F2802x_Examples.h
//
// TITLE:  F2802x Device Definitions.
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

#ifndef F2802x_EXAMPLES_H
#define F2802x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines that specify the PLL control register (PLLCR) and divide select 
// (DIVSEL) value.
//
//#define DSP28_DIVSEL   0 // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1 // Disable /4 for SYSCKOUT
#define DSP28_DIVSEL   2 // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL   3 // Enable /1 for SYSCLKOUT

//
// Uncomment for 60 MHz devices [60 MHz = (10MHz * 12)/2]
//
#define DSP28_PLLCR   12

//#define DSP28_PLLCR   11

//
// Uncomment for 50 Mhz devices [50 Mhz = (10MHz * 10)/2]
//
//#define DSP28_PLLCR   10

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
//
//      Example 2: 60 MHz devices:
//                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator
//
//                 In step 1 the user specified PLLCR = 0xC for a
//                 60 MHz CPU clock (SYSCLKOUT = 60 MHz).
//
//                 In this case, the CPU_RATE will be 16.667L
//                 Uncomment the line: #define CPU_RATE 16.667L
//

#define CPU_RATE   16.667L   // for a 60MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   25.000L   // for a 40MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//
// Target device (in F2802x_Device.h) determines CPU frequency
// (for examples) - either 60 MHz (for 28026 and 28027), 50 MHz
// (for 28023 and 28023, or 40 MHz (for 28021, 28020, and 280200).
// User does not have to change anything here.
//

//
// 28026||28027 devices only
//
#if (DSP28_28026PT||DSP28_28026DA||DSP28_28027PT||DSP28_28027DA)
  #define CPU_FRQ_60MHZ    1     // 60 Mhz CPU Freq (10 MHz input clock)
  #define CPU_FRQ_50MHZ    0
  #define CPU_FRQ_40MHZ    0

//
// 28023||28023 devices
//  
#elif (DSP28_28023PT||DSP28_28023DA||DSP28_28022PT||DSP28_28022DA)
  #define CPU_FRQ_60MHZ    0
  #define CPU_FRQ_50MHZ    1     // 50 MHz CPU Freq (10 MHz input clock)
  #define CPU_FRQ_40MHZ    0
  
//
// 28021||28020||280200 devices
//
#else
  #define CPU_FRQ_60MHZ    0
  #define CPU_FRQ_50MHZ    0
  #define CPU_FRQ_40MHZ    1     // 40 MHz CPU Freq (10 MHz input clock)
#endif

//
// The following pointer to a function call calibrates the ADC and internal
// oscillators
//
#define Device_cal (void   (*)(void))0x3D7C80

//
// Includes Files
//

//
// Prototypes for global functions within the .c files.
//
#include "f2802x_globalprototypes.h"
#include "f2802x_epwm_defines.h"             // Macros used for PWM examples.
#include "f2802x_i2c_defines.h"              // Macros used for I2C examples.

#define PARTNO_28027PT  0xCF
#define PARTNO_28027DA  0xCE
#define PARTNO_28026PT  0xC7
#define PARTNO_28026DA  0xC6
#define PARTNO_28023PT  0xCD
#define PARTNO_28023DA  0xCC
#define PARTNO_28022PT  0xC5
#define PARTNO_28022DA  0xC4
#define PARTNO_28021PT  0xCB
#define PARTNO_28021DA  0xCA
#define PARTNO_28020PT  0xC3
#define PARTNO_28020DA  0xC2
#define PARTNO_280200PT 0xC1
#define PARTNO_280200DA 0xC0

//
// Include files not used with DSP/BIOS
//
#ifndef DSP28_BIOS
#include "f2802x_defaultisr.h"
#endif

//
// DO NOT MODIFY THIS LINE.
//
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / \
                                    (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x_EXAMPLES_H definition

//
// End of file
//

