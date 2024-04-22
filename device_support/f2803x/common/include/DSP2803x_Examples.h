//###########################################################################
//
// FILE:   DSP2803x_Examples.h
//
// TITLE:  DSP2803x Device Definitions.
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

#ifndef DSP2803x_EXAMPLES_H
#define DSP2803x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
//

//
// Defines
//
//#define DSP28_DIVSEL   0      // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1      // Disable /4 for SYSCKOUT
#define DSP28_DIVSEL   2      // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL   3      // Enable /1 for SYSCLKOUT

#define DSP28_PLLCR   12    //Uncomment for 60 MHz devs [60 MHz=(10MHz * 12)/2]
//#define DSP28_PLLCR   11
//#define DSP28_PLLCR   10
//#define DSP28_PLLCR    9
//#define DSP28_PLLCR    8  //Uncomment for 40 MHz devs [40 MHz=(10MHz * 8)/2]
//#define DSP28_PLLCR    7
//#define DSP28_PLLCR    6
//#define DSP28_PLLCR    5
//#define DSP28_PLLCR    4
//#define DSP28_PLLCR    3
//#define DSP28_PLLCR    2
//#define DSP28_PLLCR    1
//#define DSP28_PLLCR    0  // PLL is bypassed in this mode
//

//
//    Specify the clock rate of the CPU (SYSCLKOUT) in nS.
//
//    Take into account the input clock frequency and the PLL multiplier
//    selected in step 1.
//
//    Use one of the values provided, or define your own.
//    The trailing L is required tells the compiler to treat
//    the number as a 64-bit value.
//
//    Only one statement should be uncommented.
//
//    Example:   60 MHz devices:
//             CLKIN is a 10 MHz crystal or internal 10 MHz oscillator
//
//             In step 1 the user specified PLLCR = 0xC for a
//             60 MHz CPU clock (SYSCLKOUT = 60 MHz).
//
//             In this case, the CPU_RATE will be 16.667L
//             Uncomment the line: #define CPU_RATE 16.667L
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
// The following pointer to a function call calibrates the ADC
// and internal oscillators
//
#define Device_cal (void   (*)(void))0x3D7C80

//
// Included Files
//
#include "DSP2803x_GlobalPrototypes.h"  // Prototypes for global functions 
                                        // within the .c files.
#include "DSP2803x_EPwm_defines.h"      // Macros used for PWM examples.
#include "DSP2803x_I2c_defines.h"       // Macros used for I2C examples.
#include "DSP2803x_Cla_defines.h"       // Macros used for CLA examples.

#define   PARTNO_28030PAG   0xAA
#define   PARTNO_28030PN    0xAB

#define   PARTNO_28031PAG   0xAE
#define   PARTNO_28031PN    0xAF

#define   PARTNO_28032PAG   0xB2
#define   PARTNO_28032PN    0xB3

#define   PARTNO_28033PAG   0xB6
#define   PARTNO_28033PN    0xB7

#define   PARTNO_28034PAG   0xBA
#define   PARTNO_28034PN    0xBB

#define   PARTNO_28035PAG   0xBE
#define   PARTNO_28035PN    0xBF

//
// Include files not used with DSP/BIOS
//
#ifndef DSP28_BIOS
    #include "DSP2803x_DefaultISR.h"
#endif

//
// DO NOT MODIFY THIS LINE
//
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / \
                    (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_EXAMPLES_H definition

//
// End of file
//

