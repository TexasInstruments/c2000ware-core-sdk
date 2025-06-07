//###########################################################################
//
// FILE:   f280013x_examples.h
//
// TITLE:  f280013x Device Definitions.
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

#ifndef f280013x_EXAMPLES_H
#define f280013x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// The following are values that can be passed to the
// InitSysPll() & InitAuxPll() to select SYSPLL/AUXPLL integer multiplier
//
#define   IMULT_0         0 //PLLBYPASS
#define   IMULT_1         1
#define   IMULT_2         2
#define   IMULT_3         3
#define   IMULT_4         4
#define   IMULT_5         5
#define   IMULT_6         6
#define   IMULT_7         7
#define   IMULT_8         8
#define   IMULT_9         9
#define   IMULT_10        10
#define   IMULT_11        11
#define   IMULT_12        12
#define   IMULT_13        13
#define   IMULT_14        14
#define   IMULT_15        15
#define   IMULT_16        16
#define   IMULT_17        17
#define   IMULT_18        18
#define   IMULT_19        19
#define   IMULT_20        20
#define   IMULT_21        21
#define   IMULT_22        22
#define   IMULT_23        23
#define   IMULT_24        24
#define   IMULT_25        25
#define   IMULT_26        26
#define   IMULT_27        27
#define   IMULT_28        28
#define   IMULT_29        29
#define   IMULT_30        30
#define   IMULT_31        31
#define   IMULT_32        32
#define   IMULT_33        33
#define   IMULT_34        34
#define   IMULT_35        35
#define   IMULT_36        36
#define   IMULT_37        37
#define   IMULT_38        38
#define   IMULT_39        39
#define   IMULT_40        40
#define   IMULT_41        41
#define   IMULT_42        42
#define   IMULT_43        43
#define   IMULT_44        44
#define   IMULT_45        45
#define   IMULT_46        46
#define   IMULT_47        47
#define   IMULT_48        48
#define   IMULT_49        49
#define   IMULT_50        50
#define   IMULT_51        51
#define   IMULT_52        52
#define   IMULT_53        53
#define   IMULT_54        54
#define   IMULT_55        55
#define   IMULT_56        56
#define   IMULT_57        57
#define   IMULT_58        58
#define   IMULT_59        59
#define   IMULT_60        60
#define   IMULT_61        61
#define   IMULT_62        62
#define   IMULT_63        63
#define   IMULT_64        64
#define   IMULT_65        65
#define   IMULT_66        66
#define   IMULT_67        67
#define   IMULT_68        68
#define   IMULT_69        69
#define   IMULT_70        70
#define   IMULT_71        71
#define   IMULT_72        72
#define   IMULT_73        73
#define   IMULT_74        74
#define   IMULT_75        75
#define   IMULT_76        76
#define   IMULT_77        77
#define   IMULT_78        78
#define   IMULT_79        79
#define   IMULT_80        80
#define   IMULT_81        81
#define   IMULT_82        82
#define   IMULT_83        83
#define   IMULT_84        84
#define   IMULT_85        85
#define   IMULT_86        86
#define   IMULT_87        87
#define   IMULT_88        88
#define   IMULT_89        89
#define   IMULT_90        90
#define   IMULT_91        91
#define   IMULT_92        92
#define   IMULT_93        93
#define   IMULT_94        94
#define   IMULT_95        95
#define   IMULT_96        96
#define   IMULT_97        97
#define   IMULT_98        98
#define   IMULT_99        99
#define   IMULT_100       100
#define   IMULT_101       101
#define   IMULT_102       102
#define   IMULT_103       103
#define   IMULT_104       104
#define   IMULT_105       105
#define   IMULT_106       106
#define   IMULT_107       107
#define   IMULT_108       108
#define   IMULT_109       109
#define   IMULT_110       110
#define   IMULT_111       111
#define   IMULT_112       112
#define   IMULT_113       113
#define   IMULT_114       114
#define   IMULT_115       115
#define   IMULT_116       116
#define   IMULT_117       117
#define   IMULT_118       118
#define   IMULT_119       119
#define   IMULT_120       120
#define   IMULT_121       121
#define   IMULT_122       122
#define   IMULT_123       123
#define   IMULT_124       124
#define   IMULT_125       125
#define   IMULT_126       126
#define   IMULT_127       127

//
// The following are values that can be passed to the
// InitSysPll() & InitAuxPll() to select SYSPLL/AUXPLL Reference
// clock dividers
//
#define   REFDIV_1         0
#define   REFDIV_2         1
#define   REFDIV_3         2
#define   REFDIV_4         3
#define   REFDIV_5         4
#define   REFDIV_6         5
#define   REFDIV_7         6
#define   REFDIV_8         7
#define   REFDIV_9         8
#define   REFDIV_10        9
#define   REFDIV_11        10
#define   REFDIV_12        11
#define   REFDIV_13        12
#define   REFDIV_14        13
#define   REFDIV_15        14
#define   REFDIV_16        15
#define   REFDIV_17        16
#define   REFDIV_18        17
#define   REFDIV_19        18
#define   REFDIV_20        19
#define   REFDIV_21        20
#define   REFDIV_22        21
#define   REFDIV_23        22
#define   REFDIV_24        23
#define   REFDIV_25        24
#define   REFDIV_26        25
#define   REFDIV_27        26
#define   REFDIV_28        27
#define   REFDIV_29        28
#define   REFDIV_30        29
#define   REFDIV_31        30
#define   REFDIV_32        31

//
// The following are values that can be passed to the
// InitSysPll() & InitAuxPll() to select SYSPLL/AUXPLL Output
// clock dividers
//

#define   ODIV_1         0
#define   ODIV_2         1
#define   ODIV_3         2
#define   ODIV_4         3
#define   ODIV_5         4
#define   ODIV_6         5
#define   ODIV_7         6
#define   ODIV_8         7
#define   ODIV_9         8
#define   ODIV_10        9
#define   ODIV_11        10
#define   ODIV_12        11
#define   ODIV_13        12
#define   ODIV_14        13
#define   ODIV_15        14
#define   ODIV_16        15
#define   ODIV_17        16
#define   ODIV_18        17
#define   ODIV_19        18
#define   ODIV_20        19
#define   ODIV_21        20
#define   ODIV_22        21
#define   ODIV_23        22
#define   ODIV_24        23
#define   ODIV_25        24
#define   ODIV_26        25
#define   ODIV_27        26
#define   ODIV_28        27
#define   ODIV_29        28
#define   ODIV_30        29
#define   ODIV_31        30
#define   ODIV_32        31

//
// The following are values that can be passed to the
// InitSysPll() to select divsel for SYSPLL
//
#define   PLLCLK_BY_1      0
#define   PLLCLK_BY_2      1
#define   PLLCLK_BY_4      2
#define   PLLCLK_BY_6      3
#define   PLLCLK_BY_8      4
#define   PLLCLK_BY_10     5
#define   PLLCLK_BY_12     6
#define   PLLCLK_BY_14     7
#define   PLLCLK_BY_16     8
#define   PLLCLK_BY_18     9
#define   PLLCLK_BY_20     10
#define   PLLCLK_BY_22     11
#define   PLLCLK_BY_24     12
#define   PLLCLK_BY_26     13
#define   PLLCLK_BY_28     14
#define   PLLCLK_BY_30     15
#define   PLLCLK_BY_32     16
#define   PLLCLK_BY_34     17
#define   PLLCLK_BY_36     18
#define   PLLCLK_BY_38     19
#define   PLLCLK_BY_40     20
#define   PLLCLK_BY_42     21
#define   PLLCLK_BY_44     22
#define   PLLCLK_BY_46     23
#define   PLLCLK_BY_48     24
#define   PLLCLK_BY_50     25
#define   PLLCLK_BY_52     26
#define   PLLCLK_BY_54     27
#define   PLLCLK_BY_56     28
#define   PLLCLK_BY_58     29
#define   PLLCLK_BY_60     30
#define   PLLCLK_BY_62     31
#define   PLLCLK_BY_64     32
#define   PLLCLK_BY_66     33
#define   PLLCLK_BY_68     34
#define   PLLCLK_BY_70     35
#define   PLLCLK_BY_72     36
#define   PLLCLK_BY_74     37
#define   PLLCLK_BY_76     38
#define   PLLCLK_BY_78     39
#define   PLLCLK_BY_80     40
#define   PLLCLK_BY_82     41
#define   PLLCLK_BY_84     42
#define   PLLCLK_BY_86     43
#define   PLLCLK_BY_88     44
#define   PLLCLK_BY_90     45
#define   PLLCLK_BY_92     46
#define   PLLCLK_BY_94     47
#define   PLLCLK_BY_96     48
#define   PLLCLK_BY_98     49
#define   PLLCLK_BY_100    50
#define   PLLCLK_BY_102    51
#define   PLLCLK_BY_104    52
#define   PLLCLK_BY_106    53
#define   PLLCLK_BY_108    54
#define   PLLCLK_BY_110    55
#define   PLLCLK_BY_112    56
#define   PLLCLK_BY_114    57
#define   PLLCLK_BY_116    58
#define   PLLCLK_BY_118    59
#define   PLLCLK_BY_120    60
#define   PLLCLK_BY_122    61
#define   PLLCLK_BY_124    62
#define   PLLCLK_BY_126    63

//
// The following are values that can be passed to the
// IntOsc2Sel() , XtalOscSel() to select system PLL (or) AUX PLL
//
#define   SYSTEM_PLL    (Uint16) 0

//
// The following are values that can be passed to the
// InitSysPll() , InitAuxPll() & IsPLLValid() to select clock source
//
#define   INT_OSC2     0
#define   XTAL_OSC     1
#define   INT_OSC1     2
#define   XTAL_OSC_SE    5  // External oscillator, single-ended mode
#define   INT_PLL_SYSPLL    0

//
// The following are values that can be passed to the
// IsPLLValid() to select DCC for PLL validation
//
#define   SYSCTL_DCC_BASE0              0

/*-----------------------------------------------------------------------------
    Specify the clock rate of the CPU (SYSCLKOUT) in nS.

    Take into account the input clock frequency and the PLL multiplier
    selected in step 1.

    Use one of the values provided, or define your own.
    The trailing L is required tells the compiler to treat
    the number as a 64-bit value.

    Only one statement should be uncommented.

    Example:   100 MHz devices:
             CLKIN is a 10 MHz crystal or internal 10 MHz oscillator

             In step 1 the user specified the PLL multiplier = 0x20 for a
             100 MHz CPU clock (SYSCLKOUT = 100 MHz).

             In this case, the CPU_RATE will be 10.00L
             Uncomment the line: #define CPU_RATE 10.00L

-----------------------------------------------------------------------------*/

#define CPU_RATE   8.33L     // for a 120MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   10.00L    // for a 100MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   11.111L   // for a 90MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   12.500L   // for a 80MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   16.667L   // for a 60MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   25.000L   // for a 40MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//
// The following pointer to a function call calibrates the ADC reference,
// DAC offset, and internal oscillators
//
#define Device_cal ((void (*)(void))((uintptr_t)0x003fcb5e))


//
// Includes
//
#include "f280013x_globalprototypes.h"       // Prototypes for global functions
                                           // within the .c files.
#include "f280013x_adc_defines.h"
#include "f280013x_cputimervars.h"
#include "f280013x_gpio_defines.h"           // Macros used for GPIO support code
#include "f280013x_pie_defines.h"            // Macros used for PIE examples.
#include "f280013x_sysctrl_defines.h"        // Macros used for LPM support code
#include "f280013x_epwm_defines.h"           // Macros used for PWM examples.

//
// To use CPU frequency as 100MHZ, uncomment #define CPU_FRQ_100MHZ,
// and comment the #define CPU_FRQ_120MHZ
//
//#define CPU_FRQ_100MHZ 1
#define CPU_FRQ_120MHZ 1

//
// Include files not used with F/BIOS
//
#ifndef F28_BIOS
#include "f280013x_defaultisr.h"
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

#endif  // end of f280013x_EXAMPLES_H definition

//
// End of file
//
