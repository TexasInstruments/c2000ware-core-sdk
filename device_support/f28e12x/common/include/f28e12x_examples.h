//###########################################################################
//
// FILE:   f28e12x_examples.h
//
// TITLE:  F28E12x Device Definitions.
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28E12x_EXAMPLES_H
#define F28E12x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// The following are values that can be passed to the
// InitSysPll() to select SYSPLL integer multiplier
//
#define   PLLMULT_2         1
#define   PLLMULT_3         2
#define   PLLMULT_4         3
#define   PLLMULT_5         4
#define   PLLMULT_6         5
#define   PLLMULT_7         6
#define   PLLMULT_8         7
#define   PLLMULT_9         8
#define   PLLMULT_10        9
#define   PLLMULT_11        10
#define   PLLMULT_12        11
#define   PLLMULT_13        12
#define   PLLMULT_14        13
#define   PLLMULT_15        14
#define   PLLMULT_16        15
#define   PLLMULT_17        16
#define   PLLMULT_18        17
#define   PLLMULT_19        18
#define   PLLMULT_20        19
#define   PLLMULT_21        20
#define   PLLMULT_22        21
#define   PLLMULT_23        22
#define   PLLMULT_24        23
#define   PLLMULT_25        24
#define   PLLMULT_26        25
#define   PLLMULT_27        26
#define   PLLMULT_28        27
#define   PLLMULT_29        28
#define   PLLMULT_30        29
#define   PLLMULT_31        30
#define   PLLMULT_32        31
#define   PLLMULT_33        32
#define   PLLMULT_34        33
#define   PLLMULT_35        34
#define   PLLMULT_36        35
#define   PLLMULT_37        36
#define   PLLMULT_38        37
#define   PLLMULT_39        38
#define   PLLMULT_40        39
#define   PLLMULT_41        40
#define   PLLMULT_42        41
#define   PLLMULT_43        42
#define   PLLMULT_44        43
#define   PLLMULT_45        44
#define   PLLMULT_46        45
#define   PLLMULT_47        46
#define   PLLMULT_48        47
#define   PLLMULT_49        48
#define   PLLMULT_50        49
#define   PLLMULT_51        50
#define   PLLMULT_52        51
#define   PLLMULT_53        52
#define   PLLMULT_54        53
#define   PLLMULT_55        54
#define   PLLMULT_56        55
#define   PLLMULT_57        56
#define   PLLMULT_58        57
#define   PLLMULT_59        58
#define   PLLMULT_60        59
#define   PLLMULT_61        60
#define   PLLMULT_62        61
#define   PLLMULT_63        62
#define   PLLMULT_64        63
#define   PLLMULT_65        64
#define   PLLMULT_66        65
#define   PLLMULT_67        66
#define   PLLMULT_68        67
#define   PLLMULT_69        68
#define   PLLMULT_70        69
#define   PLLMULT_71        70
#define   PLLMULT_72        71
#define   PLLMULT_73        72
#define   PLLMULT_74        73
#define   PLLMULT_75        74
#define   PLLMULT_76        75
#define   PLLMULT_77        76
#define   PLLMULT_78        77
#define   PLLMULT_79        78
#define   PLLMULT_80        79
#define   PLLMULT_81        80
#define   PLLMULT_82        81
#define   PLLMULT_83        82
#define   PLLMULT_84        83
#define   PLLMULT_85        84
#define   PLLMULT_86        85
#define   PLLMULT_87        86
#define   PLLMULT_88        87
#define   PLLMULT_89        88
#define   PLLMULT_90        89
#define   PLLMULT_91        90
#define   PLLMULT_92        91
#define   PLLMULT_93        92
#define   PLLMULT_94        93
#define   PLLMULT_95        94
#define   PLLMULT_96        95
#define   PLLMULT_97        96
#define   PLLMULT_98        97
#define   PLLMULT_99        98
#define   PLLMULT_100       99
#define   PLLMULT_101       100
#define   PLLMULT_102       101
#define   PLLMULT_103       102
#define   PLLMULT_104       103
#define   PLLMULT_105       104
#define   PLLMULT_106       105
#define   PLLMULT_107       106
#define   PLLMULT_108       107
#define   PLLMULT_109       108
#define   PLLMULT_110       109
#define   PLLMULT_111       110
#define   PLLMULT_112       111
#define   PLLMULT_113       112
#define   PLLMULT_114       113
#define   PLLMULT_115       114
#define   PLLMULT_116       115
#define   PLLMULT_117       116
#define   PLLMULT_118       117
#define   PLLMULT_119       118
#define   PLLMULT_120       119
#define   PLLMULT_121       120
#define   PLLMULT_122       121
#define   PLLMULT_123       122
#define   PLLMULT_124       123
#define   PLLMULT_125       124
#define   PLLMULT_126       125
#define   PLLMULT_127       126
#define   PLLMULT_128       127

//
// The following are values that can be passed to the
// InitSysPll() to select SYSPLL Reference
// clock dividers
//
#define   PDIV_1         0
#define   PDIV_2         1
#define   PDIV_4         2
#define   PDIV_8         3

//
// The following are values that can be passed to the
// InitSysPll() to select SYSPLL Output
// clock dividers
//


#define   RDIVCLK0_2         0
#define   RDIVCLK0_4         1
#define   RDIVCLK0_6         2
#define   RDIVCLK0_8         3
#define   RDIVCLK0_10        4
#define   RDIVCLK0_12        5
#define   RDIVCLK0_14        6
#define   RDIVCLK0_16        7
#define   RDIVCLK0_18        8
#define   RDIVCLK0_20        9
#define   RDIVCLK0_22        10
#define   RDIVCLK0_24        11
#define   RDIVCLK0_26        12
#define   RDIVCLK0_28        13
#define   RDIVCLK0_30        14
#define   RDIVCLK0_32        15

//
// The following are values that can be passed to the
// InitSysPll() to select divsel for SYSPLL
//
#define   PLLCLK_BY_1        0
#define   PLLCLK_BY_2        1
#define   PLLCLK_BY_3        2
#define   PLLCLK_BY_4        3
#define   PLLCLK_BY_5        4
#define   PLLCLK_BY_6        5
#define   PLLCLK_BY_7        6
#define   PLLCLK_BY_8        7
#define   PLLCLK_BY_9        8
#define   PLLCLK_BY_10       9
#define   PLLCLK_BY_11      10
#define   PLLCLK_BY_12      11
#define   PLLCLK_BY_13      12
#define   PLLCLK_BY_14      13
#define   PLLCLK_BY_15      14
#define   PLLCLK_BY_16      15
#define   PLLCLK_BY_17      16
#define   PLLCLK_BY_18      17
#define   PLLCLK_BY_19      18
#define   PLLCLK_BY_20      19
#define   PLLCLK_BY_21      20
#define   PLLCLK_BY_22      21
#define   PLLCLK_BY_23      22
#define   PLLCLK_BY_24      23
#define   PLLCLK_BY_25      24
#define   PLLCLK_BY_26      25
#define   PLLCLK_BY_27      26
#define   PLLCLK_BY_28      27
#define   PLLCLK_BY_29      28
#define   PLLCLK_BY_30      29
#define   PLLCLK_BY_31      30
#define   PLLCLK_BY_32      31
#define   PLLCLK_BY_33      32
#define   PLLCLK_BY_34      33
#define   PLLCLK_BY_35      34
#define   PLLCLK_BY_36      35
#define   PLLCLK_BY_37      36
#define   PLLCLK_BY_38      37
#define   PLLCLK_BY_39      38
#define   PLLCLK_BY_40      39
#define   PLLCLK_BY_41      40
#define   PLLCLK_BY_42      41
#define   PLLCLK_BY_43      42
#define   PLLCLK_BY_44      43
#define   PLLCLK_BY_45      44
#define   PLLCLK_BY_46      45
#define   PLLCLK_BY_47      46
#define   PLLCLK_BY_48      47
#define   PLLCLK_BY_49      48
#define   PLLCLK_BY_50      49
#define   PLLCLK_BY_51      50
#define   PLLCLK_BY_52      51
#define   PLLCLK_BY_53      52
#define   PLLCLK_BY_54      53
#define   PLLCLK_BY_55      54
#define   PLLCLK_BY_56      55
#define   PLLCLK_BY_57      56
#define   PLLCLK_BY_58      57
#define   PLLCLK_BY_59      58
#define   PLLCLK_BY_60      59
#define   PLLCLK_BY_61      60
#define   PLLCLK_BY_62      61
#define   PLLCLK_BY_63      62
#define   PLLCLK_BY_64      63

//
// The following are values that can be passed to the
// SysOscdiv4Sel() , XtalOscSel() to select system PLL
//
#define   SYSTEM_PLL    (Uint16) 0

//
// The following are values that can be passed to the
// InitSysPll() , InitAuxPll() & IsPLLValid() to select clock source
//
#define   INT_SYSOSCDIV4    0
#define   XTAL_OSC          1
#define   INT_WROSCDIV8     2
#define   XTAL_OSC_SE       5  // External oscillator, single-ended mode
#define   INT_PLL_SYSPLL    0

//
// The following are values that can be passed to the
// IsPLLValid() to select DCC for PLL validation
//
#define   SYSCTL_DCC_BASE0              0

//
//  Specify the clock rate of the CPU (SYSCLKOUT) in nS.
//
//  Take into account the input clock frequency and the PLL multiplier
//  selected in step 1.
//
//  Use one of the values provided, or define your own.
//  The trailing L is required tells the compiler to treat
//  the number as a 64-bit value.
//
//  Only one statement should be uncommented.
//
//  Example:   200 MHz devices:
//             CLKIN is a 10 MHz crystal or internal 10 MHz oscillator
//
//             In step 1 the user specified the PLL multiplier = 40 for a
//             200 MHz CPU clock (SYSCLKOUT = 200 MHz).
//
//             In this case, the CPU_RATE will be 5.000L
//             Uncomment the line: #define CPU_RATE 5.000L
//

//#define CPU_RATE   5.00L   // for a 200MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   5.263L   // for a 190MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   5.556L   // for a 180MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   5.882L   // for a 170MHz CPU clock speed  (SYSCLKOUT)
#define CPU_RATE   6.250L   // for a 160MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   6.667L   // for a 150MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   7.143L   // for a 140MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   7.692L   // for a 130MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   8.333L   // for a 120MHz CPU clock speed  (SYSCLKOUT)

//
// The following pointer to a function call calibrates the ADC reference,
// DAC offset, and internal oscillators
//

#define Device_cal ((void (*)(void))((uintptr_t)0x003fc3f4))

//
// The following macro define the OTP locations where ADC INL trim values
// are stored. Use this in the AdcSetMode(...) function only
//
#define GetAdcINLTrimOTPLoc(adc) ((Uint32 *)(0x72070U + (0x6 * adc)))

//
// The following pointer to a function call looks up the ADC offset trim for a
// given condition. Use this in the AdcSetMode(...) function only.
//
#define GetAdcOffsetTrimOTPLoc(adc)                              \
                                ((Uint16 *)(0x72064U + adc))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY_BF                          (0x5A5A)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY_BF                      (*((Uint16 *)(0x72062UL)))

//
// Includes
//
#include "f28e12x_globalprototypes.h"       // Prototypes for global functions                                            
                                            // within the .c files.
#include "f28e12x_adc_defines.h"            // Macros used for ADC support code
#include "f28e12x_cputimervars.h"
#include "f28e12x_mcpwm_defines.h"           // Macros used for PWM examples.
#include "f28e12x_gpio_defines.h"           // Macros used for GPIO support code
#include "f28e12x_pie_defines.h"            // Macros used for PIE examples.
#include "f28e12x_dma_defines.h"            // Macros used for DMA examples.
#include "f28e12x_sysctrl_defines.h"        // Macros used for LPM support code


#define CPU_FRQ_200MHZ 0
#define CPU_FRQ_160MHZ 1
#define CPU_FRQ_120MHZ 0

//
// Include files not used with F/BIOS
//
#ifndef F28_BIOS
#include "f28e12x_defaultisr.h"
#endif

extern void F28x_usDelay(long LoopCount);

//
// DO NOT MODIFY THIS LINE.
//
#define DELAY_US(A)  F28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

//
// Timer Operations:
//

//
// Start Timer:
//
#define StartCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadCpuTimer0() CpuTimer0Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadCpuTimer0Counter() CpuTimer0Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadCpuTimer0Period() CpuTimer0Regs.PRD.all

//
// Start Timer:
//
#define StartCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 0
#define StartCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 0

//
// Stop Timer:
//
#define StopCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 1
#define StopCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value:
//
#define ReloadCpuTimer1() CpuTimer1Regs.TCR.bit.TRB = 1
#define ReloadCpuTimer2() CpuTimer2Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value:
//
#define ReadCpuTimer1Counter() CpuTimer1Regs.TIM.all
#define ReadCpuTimer2Counter() CpuTimer2Regs.TIM.all

//
// Read 32-Bit Period Value:
//
#define ReadCpuTimer1Period() CpuTimer1Regs.PRD.all
#define ReadCpuTimer2Period() CpuTimer2Regs.PRD.all

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F28E12x_EXAMPLES_H definition

//
// End of file
//
