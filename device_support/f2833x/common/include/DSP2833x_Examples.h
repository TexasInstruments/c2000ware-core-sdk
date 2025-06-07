// TI File $Revision: /main/9 $
// Checkin $Date: July 2, 2008   14:31:12 $
//###########################################################################
//
// FILE:   DSP2833x_Examples.h
//
// TITLE:  DSP2833x Device Definitions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DSP2833x_EXAMPLES_H
#define DSP2833x_EXAMPLES_H


#ifdef __cplusplus
extern "C" {
#endif

//
// Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
//
//#define DSP28_DIVSEL   0   // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1 // Enable /4 for SYSCKOUT
#define DSP28_DIVSEL     2 // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL     3 // Enable /1 for SYSCLKOUT

#define DSP28_PLLCR   10
//#define DSP28_PLLCR    9
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
// Specify the clock rate of the CPU (SYSCLKOUT) in nS.
//
//  Take into account the input clock frequency and the PLL multiplier
//	      selected in step 1.
//
//      Use one of the values provided, or define your own.
//      The trailing L is required tells the compiler to treat
//      the number as a 64-bit value.
//
//      Only one statement should be uncommented.
//
//      Example 1:150 MHz devices:
//                CLKIN is a 30MHz crystal.
//
//                In step 1 the user specified PLLCR = 0xA for a
//                150Mhz CPU clock (SYSCLKOUT = 150MHz).
//
//                In this case, the CPU_RATE will be 6.667L
//                Uncomment the line:  #define CPU_RATE  6.667L
//
//      Example 2:  100 MHz devices:
//                  CLKIN is a 20MHz crystal.
//
//	              In step 1 the user specified PLLCR = 0xA for a
//	              100Mhz CPU clock (SYSCLKOUT = 100MHz).
//
//	              In this case, the CPU_RATE will be 10.000L
//                  Uncomment the line:  #define CPU_RATE  10.000L
//
#define CPU_RATE    6.667L   // for a 150MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    7.143L   // for a 140MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    8.333L   // for a 120MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   10.000L   // for a 100MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   13.330L   // for a 75MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//
// Target device (in DSP2833x_Device.h) determines CPU frequency
// (for examples) - either 150 MHz (for 28335 and 28334) or 100 MHz
// (for 28332 and 28333). User does not have to change anything here.
//
#if DSP28_28332 || DSP28_28333  // 28332 and 28333 devices only
  #define CPU_FRQ_100MHZ  1     // 100 Mhz CPU Freq (20 MHz input freq)
  #define CPU_FRQ_150MHZ  0
#else
  #define CPU_FRQ_100MHZ  0  // DSP28_28335||DSP28_28334
  #define CPU_FRQ_150MHZ  1  // 150 MHz CPU Freq (30 MHz input freq) by DEFAULT
#endif

//
// Include Example Header Files
//

//
// Prototypes for global functions within the .c files.
//
#include "DSP2833x_GlobalPrototypes.h"                                              
#include "DSP2833x_EPwm_defines.h"       // Macros used for PWM examples.
#include "DSP2833x_Dma_defines.h"        // Macros used for DMA examples.
#include "DSP2833x_I2c_defines.h"        // Macros used for I2C examples.

#define PARTNO_28335  0xEF
#define PARTNO_28334  0xEE
#define PARTNO_28333  0xEA
#define PARTNO_28332  0xED

//
// Include files not used with DSP/BIOS
//
#ifndef DSP28_BIOS
#include "DSP2833x_DefaultIsr.h"
#endif

//
// DO NOT MODIFY THIS LINE.
//
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / \
        (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_EXAMPLES_H definition

//
// End of file
//

