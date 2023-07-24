//###########################################################################
//
// FILE:    hw_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
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

#ifndef HW_XBAR_H
#define HW_XBAR_H

//*************************************************************************************************
//
// The following are defines for the XBAR register offsets
//
//*************************************************************************************************
#define XBAR_O_FLG1    0x0U    // X-Bar Input Flag Register 1
#define XBAR_O_FLG2    0x2U    // X-Bar Input Flag Register 2
#define XBAR_O_FLG3    0x4U    // X-Bar Input Flag Register 3
#define XBAR_O_FLG4    0x6U    // X-Bar Input Flag Register 4
#define XBAR_O_FLG5    0x8U    // X-Bar Input Flag Register 5
#define XBAR_O_FLG6    0xAU    // X-Bar Input Flag Register 6
#define XBAR_O_FLG7    0xCU    // X-Bar Input Flag Register 7
#define XBAR_O_FLG8    0xEU    // X-Bar Input Flag Register 8
#define XBAR_O_FLG9    0x10U   // X-Bar Input Flag Register 9
#define XBAR_O_FLG10   0x12U   // X-Bar Input Flag Register 10
#define XBAR_O_FLG11   0x14U   // X-Bar Input Flag Register 11
#define XBAR_O_FLG12   0x16U   // X-Bar Input Flag Register 12
#define XBAR_O_FLG13   0x18U   // X-Bar Input Flag Register 13
#define XBAR_O_FLG14   0x1AU   // X-Bar Input Flag Register 14
#define XBAR_O_FLG15   0x1CU   // X-Bar Input Flag Register 15
#define XBAR_O_FLG16   0x1EU   // X-Bar Input Flag Register 16
#define XBAR_O_CLR1    0x20U   // X-Bar Input Flag Clear Register 1
#define XBAR_O_CLR2    0x22U   // X-Bar Input Flag Clear Register 2
#define XBAR_O_CLR3    0x24U   // X-Bar Input Flag Clear Register 3
#define XBAR_O_CLR4    0x26U   // X-Bar Input Flag Clear Register 4
#define XBAR_O_CLR5    0x28U   // X-Bar Input Flag Clear Register 5
#define XBAR_O_CLR6    0x2AU   // X-Bar Input Flag Clear Register 6
#define XBAR_O_CLR7    0x2CU   // X-Bar Input Flag Clear Register 7
#define XBAR_O_CLR8    0x2EU   // X-Bar Input Flag Clear Register 8
#define XBAR_O_CLR9    0x30U   // X-Bar Input Flag Clear Register 9
#define XBAR_O_CLR10   0x32U   // X-Bar Input Flag Clear Register 10
#define XBAR_O_CLR11   0x34U   // X-Bar Input Flag Clear Register 11
#define XBAR_O_CLR12   0x36U   // X-Bar Input Flag Clear Register 12
#define XBAR_O_CLR13   0x38U   // X-Bar Input Flag Clear Register 13
#define XBAR_O_CLR14   0x3AU   // X-Bar Input Flag Clear Register 14
#define XBAR_O_CLR15   0x3CU   // X-Bar Input Flag Clear Register 15
#define XBAR_O_CLR16   0x3EU   // X-Bar Input Flag Clear Register 16


//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG1 register
//
//*************************************************************************************************
#define XBAR_FLG1_CMPSS1_CTRIPL      0x1U          // Input Flag for CMPSS1.CTRIPL Signal
#define XBAR_FLG1_CMPSS1_CTRIPH      0x2U          // Input Flag for CMPSS1.CTRIPH Signal
#define XBAR_FLG1_CMPSS2_CTRIPL      0x4U          // Input Flag for CMPSS2.CTRIPL Signal
#define XBAR_FLG1_CMPSS2_CTRIPH      0x8U          // Input Flag for CMPSS2.CTRIPH Signal
#define XBAR_FLG1_CMPSS3_CTRIPL      0x10U         // Input Flag for CMPSS3.CTRIPL Signal
#define XBAR_FLG1_CMPSS3_CTRIPH      0x20U         // Input Flag for CMPSS3.CTRIPH Signal
#define XBAR_FLG1_CMPSS4_CTRIPL      0x40U         // Input Flag for CMPSS4.CTRIPL Signal
#define XBAR_FLG1_CMPSS4_CTRIPH      0x80U         // Input Flag for CMPSS4.CTRIPH Signal
#define XBAR_FLG1_CMPSS5_CTRIPL      0x100U        // Input Flag for CMPSS5.CTRIPL Signal
#define XBAR_FLG1_CMPSS5_CTRIPH      0x200U        // Input Flag for CMPSS5.CTRIPH Signal
#define XBAR_FLG1_CMPSS6_CTRIPL      0x400U        // Input Flag for CMPSS6.CTRIPL Signal
#define XBAR_FLG1_CMPSS6_CTRIPH      0x800U        // Input Flag for CMPSS6.CTRIPH Signal
#define XBAR_FLG1_CMPSS7_CTRIPL      0x1000U       // Input Flag for CMPSS7.CTRIPL Signal
#define XBAR_FLG1_CMPSS7_CTRIPH      0x2000U       // Input Flag for CMPSS7.CTRIPH Signal
#define XBAR_FLG1_CMPSS8_CTRIPL      0x4000U       // Input Flag for CMPSS8.CTRIPL Signal
#define XBAR_FLG1_CMPSS8_CTRIPH      0x8000U       // Input Flag for CMPSS8.CTRIPH Signal
#define XBAR_FLG1_CMPSS1_CTRIPOUTL   0x10000U      // Input Flag for CMPSS1.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS1_CTRIPOUTH   0x20000U      // Input Flag for CMPSS1.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS2_CTRIPOUTL   0x40000U      // Input Flag for CMPSS2.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS2_CTRIPOUTH   0x80000U      // Input Flag for CMPSS2.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS3_CTRIPOUTL   0x100000U     // Input Flag for CMPSS3.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS3_CTRIPOUTH   0x200000U     // Input Flag for CMPSS3.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS4_CTRIPOUTL   0x400000U     // Input Flag for CMPSS4.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS4_CTRIPOUTH   0x800000U     // Input Flag for CMPSS4.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS5_CTRIPOUTL   0x1000000U    // Input Flag for CMPSS5.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS5_CTRIPOUTH   0x2000000U    // Input Flag for CMPSS5.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS6_CTRIPOUTL   0x4000000U    // Input Flag for CMPSS6.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS6_CTRIPOUTH   0x8000000U    // Input Flag for CMPSS6.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS7_CTRIPOUTL   0x10000000U   // Input Flag for CMPSS7.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS7_CTRIPOUTH   0x20000000U   // Input Flag for CMPSS7.CTRIPOUTH Signal
#define XBAR_FLG1_CMPSS8_CTRIPOUTL   0x40000000U   // Input Flag for CMPSS8.CTRIPOUTL Signal
#define XBAR_FLG1_CMPSS8_CTRIPOUTH   0x80000000U   // Input Flag for CMPSS8.CTRIPOUTH Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG2 register
//
//*************************************************************************************************
#define XBAR_FLG2_INPUT1       0x1U          // Input Flag for INPUT1 Signal
#define XBAR_FLG2_INPUT2       0x2U          // Input Flag for INPUT2 Signal
#define XBAR_FLG2_INPUT3       0x4U          // Input Flag for INPUT3 Signal
#define XBAR_FLG2_INPUT4       0x8U          // Input Flag for INPUT4 Signal
#define XBAR_FLG2_INPUT5       0x10U         // Input Flag for INPUT5 Signal
#define XBAR_FLG2_INPUT6       0x20U         // Input Flag for INPUT6 Signal
#define XBAR_FLG2_ADCSOCA      0x40U         // Input Flag for ADCSOCA Signal
#define XBAR_FLG2_ADCSOCB      0x80U         // Input Flag for ADCSOCB Signal
#define XBAR_FLG2_INPUT7       0x100U        // Input Flag for INPUT7 Signal
#define XBAR_FLG2_INPUT8       0x200U        // Input Flag for INPUT8 Signal
#define XBAR_FLG2_INPUT9       0x400U        // Input Flag for INPUT9 Signal
#define XBAR_FLG2_INPUT10      0x800U        // Input Flag for INPUT10\ Signal
#define XBAR_FLG2_INPUT11      0x1000U       // Input Flag for INPUT11 Signal
#define XBAR_FLG2_INPUT12      0x2000U       // Input Flag for INPUT12 Signal
#define XBAR_FLG2_INPUT13      0x4000U       // Input Flag for INPUT13 Signal
#define XBAR_FLG2_INPUT14      0x8000U       // Input Flag for INPUT14 Signal
#define XBAR_FLG2_ECAP1_OUT    0x10000U      // Input Flag for ECAP1.OUT Signal
#define XBAR_FLG2_ECAP2_OUT    0x20000U      // Input Flag for ECAP2.OUT Signal
#define XBAR_FLG2_ECAP3_OUT    0x40000U      // Input Flag for ECAP3.OUT Signal
#define XBAR_FLG2_ECAP4_OUT    0x80000U      // Input Flag for ECAP4.OUT Signal
#define XBAR_FLG2_ECAP5_OUT    0x100000U     // Input Flag for ECAP5.OUT Signal
#define XBAR_FLG2_ECAP6_OUT    0x200000U     // Input Flag for ECAP6.OUT Signal
#define XBAR_FLG2_EXTSYNCOUT   0x400000U     // Input Flag for EXTSYNCOUT Signal
#define XBAR_FLG2_ADCAEVT1     0x800000U     // Input Flag for ADCAEVT1 Signal
#define XBAR_FLG2_ADCAEVT2     0x1000000U    // Input Flag for ADCAEVT2 Signal
#define XBAR_FLG2_ADCAEVT3     0x2000000U    // Input Flag for ADCAEVT3 Signal
#define XBAR_FLG2_ADCAEVT4     0x4000000U    // Input Flag for ADCAEVT4 Signal
#define XBAR_FLG2_ADCBEVT1     0x8000000U    // Input Flag for ADCBEVT1 Signal
#define XBAR_FLG2_ADCBEVT2     0x10000000U   // Input Flag for ADCBEVT2 Signal
#define XBAR_FLG2_ADCBEVT3     0x20000000U   // Input Flag for ADCBEVT3 Signal
#define XBAR_FLG2_ADCBEVT4     0x40000000U   // Input Flag for ADCBEVT4 Signal
#define XBAR_FLG2_ADCCEVT1     0x80000000U   // Input Flag for ADCCEVT1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG3 register
//
//*************************************************************************************************
#define XBAR_FLG3_ADCCEVT2        0x1U        // Input Flag for ADCCEVT2 Signal
#define XBAR_FLG3_ADCCEVT3        0x2U        // Input Flag for ADCCEVT3 Signal
#define XBAR_FLG3_ADCCEVT4        0x4U        // Input Flag for ADCCEVT4 Signal
#define XBAR_FLG3_SD1FLT1_COMPL   0x80U       // Input Flag for SD1FLT1.COMPL Signal
#define XBAR_FLG3_SD1FLT1_COMPH   0x100U      // Input Flag for SD1FLT1.COMPH Signal
#define XBAR_FLG3_SD1FLT2_COMPL   0x200U      // Input Flag for SD1FLT2.COMPL Signal
#define XBAR_FLG3_SD1FLT2_COMPH   0x400U      // Input Flag for SD1FLT2.COMPH Signal
#define XBAR_FLG3_SD1FLT3_COMPL   0x800U      // Input Flag for SD1FLT3.COMPL Signal
#define XBAR_FLG3_SD1FLT3_COMPH   0x1000U     // Input Flag for SD1FLT3.COMPH Signal
#define XBAR_FLG3_SD1FLT4_COMPL   0x2000U     // Input Flag for SD1FLT4.COMPL Signal
#define XBAR_FLG3_SD1FLT4_COMPH   0x4000U     // Input Flag for SD1FLT4.COMPH Signal
#define XBAR_FLG3_SD2FLT1_COMPL   0x8000U     // Input Flag for SD2FLT1.COMPL Signal
#define XBAR_FLG3_SD2FLT1_COMPH   0x10000U    // Input Flag for SD2FLT1.COMPH Signal
#define XBAR_FLG3_SD2FLT2_COMPL   0x20000U    // Input Flag for SD2FLT2.COMPL Signal
#define XBAR_FLG3_SD2FLT2_COMPH   0x40000U    // Input Flag for SD2FLT2.COMPH Signal
#define XBAR_FLG3_SD2FLT3_COMPL   0x80000U    // Input Flag for SD2FLT3.COMPL Signal
#define XBAR_FLG3_SD2FLT3_COMPH   0x100000U   // Input Flag for SD2FLT3.COMPH Signal
#define XBAR_FLG3_SD2FLT4_COMPL   0x200000U   // Input Flag for SD2FLT4.COMPL Signal
#define XBAR_FLG3_SD2FLT4_COMPH   0x400000U   // Input Flag for SD2FLT4.COMPH Signal
#define XBAR_FLG3_ECAP7_OUT       0x800000U   // Input Flag for ECAP7.OUT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG4 register
//
//*************************************************************************************************
#define XBAR_FLG4_MCANA_FEVT0      0x200U        // Input Flag for MCANA_FEVT0 Signal
#define XBAR_FLG4_MCANA_FEVT1      0x400U        // Input Flag for MCANA_FEVT1 Signal
#define XBAR_FLG4_MCANA_FEVT2      0x800U        // Input Flag for MCANA_FEVT2 Signal
#define XBAR_FLG4_CLB1_OUT4        0x10000U      // Input Flag for CLB1_4.1 Signal
#define XBAR_FLG4_CLB1_OUT5        0x20000U      // Input Flag for CLB1_5.1 Signal
#define XBAR_FLG4_CLB2_OUT4        0x40000U      // Input Flag for CLB2_4.1 Signal
#define XBAR_FLG4_CLB2_OUT5        0x80000U      // Input Flag for CLB2_5.1 Signal
#define XBAR_FLG4_CLB3_OUT4        0x100000U     // Input Flag for CLB3_4.1 Signal
#define XBAR_FLG4_CLB3_OUT5        0x200000U     // Input Flag for CLB3_5.1 Signal
#define XBAR_FLG4_CLB4_OUT4        0x400000U     // Input Flag for CLB4_4.1 Signal
#define XBAR_FLG4_CLB4_OUT5        0x800000U     // Input Flag for CLB4_5.1 Signal
#define XBAR_FLG4_CLB5_OUT4        0x1000000U    // Input Latch for CLB5_OUT4 Signal
#define XBAR_FLG4_CLB5_OUT5        0x2000000U    // Input Latch for CLB5_OUT5 Signal
#define XBAR_FLG4_CLB6_OUT4        0x4000000U    // Input Latch for CLB6_OUT4 Signal
#define XBAR_FLG4_CLB6_OUT5        0x8000000U    // Input Latch for CLB6_OUT5 Signal
#define XBAR_FLG4_ERRORSTS_ERROR   0x10000000U   // Input Latch for ERRORSTS_ERROR Signal
#define XBAR_FLG4_ECATSYNC0        0x20000000U   // Input Latch for ECATSYNC0 Signal
#define XBAR_FLG4_ECATSYNC1        0x40000000U   // Input Latch for ECATSYNC1 Signal
#define XBAR_FLG4_CLAHALT          0x80000000U   // Input Latch for CLAHALT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG5 register
//
//*************************************************************************************************
#define XBAR_FLG5_EPWM1_TRIPOUT    0x1U       // Input Flag for EPWM1_TRIPOUT Signal
#define XBAR_FLG5_EPWM2_TRIPOUT    0x2U       // Input Flag for EPWM2_TRIPOUT Signal
#define XBAR_FLG5_EPWM3_TRIPOUT    0x4U       // Input Flag for EPWM3_TRIPOUT Signal
#define XBAR_FLG5_EPWM4_TRIPOUT    0x8U       // Input Flag for EPWM4_TRIPOUT Signal
#define XBAR_FLG5_EPWM5_TRIPOUT    0x10U      // Input Flag for EPWM5_TRIPOUT Signal
#define XBAR_FLG5_EPWM6_TRIPOUT    0x20U      // Input Flag for EPWM6_TRIPOUT Signal
#define XBAR_FLG5_EPWM7_TRIPOUT    0x40U      // Input Flag for EPWM7_TRIPOUT Signal
#define XBAR_FLG5_EPWM8_TRIPOUT    0x80U      // Input Flag for EPWM8_TRIPOUT Signal
#define XBAR_FLG5_EPWM9_TRIPOUT    0x100U     // Input Flag for EPWM9_TRIPOUT Signal
#define XBAR_FLG5_EPWM10_TRIPOUT   0x200U     // Input Flag for EPWM10_TRIPOUT Signal
#define XBAR_FLG5_EPWM11_TRIPOUT   0x400U     // Input Flag for EPWM11_TRIPOUT Signal
#define XBAR_FLG5_EPWM12_TRIPOUT   0x800U     // Input Flag for EPWM12_TRIPOUT Signal
#define XBAR_FLG5_EPWM13_TRIPOUT   0x1000U    // Input Flag for EPWM13_TRIPOUT Signal
#define XBAR_FLG5_EPWM14_TRIPOUT   0x2000U    // Input Flag for EPWM14_TRIPOUT Signal
#define XBAR_FLG5_EPWM15_TRIPOUT   0x4000U    // Input Flag for EPWM15_TRIPOUT Signal
#define XBAR_FLG5_EPWM16_TRIPOUT   0x8000U    // Input Flag for EPWM16_TRIPOUT Signal
#define XBAR_FLG5_EPWM17_TRIPOUT   0x10000U   // Input Flag for EPWM17_TRIPOUT Signal
#define XBAR_FLG5_EPWM18_TRIPOUT   0x20000U   // Input Flag for EPWM18_TRIPOUT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG6 register
//
//*************************************************************************************************
#define XBAR_FLG6_EPWM1_DEL_TRIP    0x1U       // Input Flag for EPWM1_DEL_TRIP Signal
#define XBAR_FLG6_EPWM2_DEL_TRIP    0x2U       // Input Flag for EPWM2_DEL_TRIP Signal
#define XBAR_FLG6_EPWM3_DEL_TRIP    0x4U       // Input Flag for EPWM3_DEL_TRIP Signal
#define XBAR_FLG6_EPWM4_DEL_TRIP    0x8U       // Input Flag for EPWM4_DEL_TRIP Signal
#define XBAR_FLG6_EPWM5_DEL_TRIP    0x10U      // Input Flag for EPWM5_DEL_TRIP Signal
#define XBAR_FLG6_EPWM6_DEL_TRIP    0x20U      // Input Flag for EPWM6_DEL_TRIP Signal
#define XBAR_FLG6_EPWM7_DEL_TRIP    0x40U      // Input Flag for EPWM7_DEL_TRIP Signal
#define XBAR_FLG6_EPWM8_DEL_TRIP    0x80U      // Input Flag for EPWM8_DEL_TRIP Signal
#define XBAR_FLG6_EPWM9_DEL_TRIP    0x100U     // Input Flag for EPWM9_DEL_TRIP Signal
#define XBAR_FLG6_EPWM10_DEL_TRIP   0x200U     // Input Flag for EPWM10_DEL_TRIP Signal
#define XBAR_FLG6_EPWM11_DEL_TRIP   0x400U     // Input Flag for EPWM11_DEL_TRIP Signal
#define XBAR_FLG6_EPWM12_DEL_TRIP   0x800U     // Input Flag for EPWM12_DEL_TRIP Signal
#define XBAR_FLG6_EPWM13_DEL_TRIP   0x1000U    // Input Flag for EPWM13_DEL_TRIP Signal
#define XBAR_FLG6_EPWM14_DEL_TRIP   0x2000U    // Input Flag for EPWM14_DEL_TRIP Signal
#define XBAR_FLG6_EPWM15_DEL_TRIP   0x4000U    // Input Flag for EPWM15_DEL_TRIP Signal
#define XBAR_FLG6_EPWM16_DEL_TRIP   0x8000U    // Input Flag for EPWM16_DEL_TRIP Signal
#define XBAR_FLG6_EPWM17_DEL_TRIP   0x10000U   // Input Flag for EPWM17_DEL_TRIP Signal
#define XBAR_FLG6_EPWM18_DEL_TRIP   0x20000U   // Input Flag for EPWM18_DEL_TRIP Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG7 register
//
//*************************************************************************************************
#define XBAR_FLG7_EPWM1_DEL_ACTIVE    0x1U       // Input Flag for EPWM1_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM2_DEL_ACTIVE    0x2U       // Input Flag for EPWM2_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM3_DEL_ACTIVE    0x4U       // Input Flag for EPWM3_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM4_DEL_ACTIVE    0x8U       // Input Flag for EPWM4_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM5_DEL_ACTIVE    0x10U      // Input Flag for EPWM5_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM6_DEL_ACTIVE    0x20U      // Input Flag for EPWM6_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM7_DEL_ACTIVE    0x40U      // Input Flag for EPWM7_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM8_DEL_ACTIVE    0x80U      // Input Flag for EPWM8_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM9_DEL_ACTIVE    0x100U     // Input Flag for EPWM9_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM10_DEL_ACTIVE   0x200U     // Input Flag for EPWM10_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM11_DEL_ACTIVE   0x400U     // Input Flag for EPWM11_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM12_DEL_ACTIVE   0x800U     // Input Flag for EPWM12_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM13_DEL_ACTIVE   0x1000U    // Input Flag for EPWM13_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM14_DEL_ACTIVE   0x2000U    // Input Flag for EPWM14_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM15_DEL_ACTIVE   0x4000U    // Input Flag for EPWM15_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM16_DEL_ACTIVE   0x8000U    // Input Flag for EPWM16_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM17_DEL_ACTIVE   0x10000U   // Input Flag for EPWM17_DEL_ACTIVE Signal
#define XBAR_FLG7_EPWM18_DEL_ACTIVE   0x20000U   // Input Flag for EPWM18_DEL_ACTIVE Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG8 register
//
//*************************************************************************************************
#define XBAR_FLG8_ETPWM1_A0_SCLK    0x1U          // Input Flag for ETPWM1_A0_sclk Signal
#define XBAR_FLG8_ETPWM1_B0_SCLK    0x2U          // Input Flag for ETPWM1_B0_sclk Signal
#define XBAR_FLG8_ETPWM2_A0_SCLK    0x4U          // Input Flag for ETPWM2_A0_sclk Signal
#define XBAR_FLG8_ETPWM2_B0_SCLK    0x8U          // Input Flag for ETPWM2_B0_sclk Signal
#define XBAR_FLG8_ETPWM3_A0_SCLK    0x10U         // Input Flag for ETPWM3_A0_sclk Signal
#define XBAR_FLG8_ETPWM3_B0_SCLK    0x20U         // Input Flag for ETPWM3_B0_sclk Signal
#define XBAR_FLG8_ETPWM4_A0_SCLK    0x40U         // Input Flag for ETPWM4_A0_sclk Signal
#define XBAR_FLG8_ETPWM4_B0_SCLK    0x80U         // Input Flag for ETPWM4_B0_sclk Signal
#define XBAR_FLG8_ETPWM5_A0_SCLK    0x100U        // Input Flag for ETPWM5_A0_sclk Signal
#define XBAR_FLG8_ETPWM5_B0_SCLK    0x200U        // Input Flag for ETPWM5_B0_sclk Signal
#define XBAR_FLG8_ETPWM6_A0_SCLK    0x400U        // Input Flag for ETPWM6_A0_sclk Signal
#define XBAR_FLG8_ETPWM6_B0_SCLK    0x800U        // Input Flag for ETPWM6_B0_sclk Signal
#define XBAR_FLG8_ETPWM7_A0_SCLK    0x1000U       // Input Flag for ETPWM7_A0_sclk Signal
#define XBAR_FLG8_ETPWM7_B0_SCLK    0x2000U       // Input Flag for ETPWM7_B0_sclk Signal
#define XBAR_FLG8_ETPWM8_A0_SCLK    0x4000U       // Input Flag for ETPWM8_A0_sclk Signal
#define XBAR_FLG8_ETPWM8_B0_SCLK    0x8000U       // Input Flag for ETPWM8_B0_sclk Signal
#define XBAR_FLG8_ETPWM9_A0_SCLK    0x10000U      // Input Flag for ETPWM9_A0_sclk Signal
#define XBAR_FLG8_ETPWM9_B0_SCLK    0x20000U      // Input Flag for ETPWM9_B0_sclk Signal
#define XBAR_FLG8_ETPWM10_A0_SCLK   0x40000U      // Input Flag for ETPWM10_A0_sclk Signal
#define XBAR_FLG8_ETPWM10_B0_SCLK   0x80000U      // Input Flag for ETPWM10_B0_sclk Signal
#define XBAR_FLG8_ETPWM11_A0_SCLK   0x100000U     // Input Flag for ETPWM11_A0_sclk Signal
#define XBAR_FLG8_ETPWM11_B0_SCLK   0x200000U     // Input Flag for ETPWM11_B0_sclk Signal
#define XBAR_FLG8_ETPWM12_A0_SCLK   0x400000U     // Input Flag for ETPWM12_A0_sclk Signal
#define XBAR_FLG8_ETPWM12_B0_SCLK   0x800000U     // Input Flag for ETPWM12_B0_sclk Signal
#define XBAR_FLG8_ETPWM13_A0_SCLK   0x1000000U    // Input Flag for ETPWM13_A0_sclk Signal
#define XBAR_FLG8_ETPWM13_B0_SCLK   0x2000000U    // Input Flag for ETPWM13_B0_sclk Signal
#define XBAR_FLG8_ETPWM14_A0_SCLK   0x4000000U    // Input Flag for ETPWM14_A0_sclk Signal
#define XBAR_FLG8_ETPWM14_B0_SCLK   0x8000000U    // Input Flag for ETPWM14_B0_sclk Signal
#define XBAR_FLG8_ETPWM15_A0_SCLK   0x10000000U   // Input Flag for ETPWM15_A0_sclk Signal
#define XBAR_FLG8_ETPWM15_B0_SCLK   0x20000000U   // Input Flag for ETPWM15_B0_sclk Signal
#define XBAR_FLG8_ETPWM16_A0_SCLK   0x40000000U   // Input Flag for ETPWM16_A0_sclk Signal
#define XBAR_FLG8_ETPWM16_B0_SCLK   0x80000000U   // Input Flag for ETPWM16_B0_sclk Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG9 register
//
//*************************************************************************************************
#define XBAR_FLG9_ETPWM17_A0_SCLK   0x1U   // Input Flag for ETPWM17_A0_sclk Signal
#define XBAR_FLG9_ETPWM17_B0_SCLK   0x2U   // Input Flag for ETPWM17_B0_sclk Signal
#define XBAR_FLG9_ETPWM18_A0_SCLK   0x4U   // Input Flag for ETPWM18_A0_sclk Signal
#define XBAR_FLG9_ETPWM18_B0_SCLK   0x8U   // Input Flag for ETPWM18_B0_sclk Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG10 register
//
//*************************************************************************************************
#define XBAR_FLG10_MDL1_OUTA    0x1U          // Input Flag for MDL1_OUTA Signal
#define XBAR_FLG10_MDL1_OUTB    0x2U          // Input Flag for MDL1_OUTB Signal
#define XBAR_FLG10_MDL2_OUTA    0x4U          // Input Flag for MDL2_OUTA Signal
#define XBAR_FLG10_MDL2_OUTB    0x8U          // Input Flag for MDL2_OUTB Signal
#define XBAR_FLG10_MDL3_OUTA    0x10U         // Input Flag for MDL3_OUTA Signal
#define XBAR_FLG10_MDL3_OUTB    0x20U         // Input Flag for MDL3_OUTB Signal
#define XBAR_FLG10_MDL4_OUTA    0x40U         // Input Flag for MDL4_OUTA Signal
#define XBAR_FLG10_MDL4_OUTB    0x80U         // Input Flag for MDL4_OUTB Signal
#define XBAR_FLG10_MDL5_OUTA    0x100U        // Input Flag for MDL5_OUTA Signal
#define XBAR_FLG10_MDL5_OUTB    0x200U        // Input Flag for MDL5_OUTB Signal
#define XBAR_FLG10_MDL6_OUTA    0x400U        // Input Flag for MDL6_OUTA Signal
#define XBAR_FLG10_MDL6_OUTB    0x800U        // Input Flag for MDL6_OUTB Signal
#define XBAR_FLG10_MDL7_OUTA    0x1000U       // Input Flag for MDL7_OUTA Signal
#define XBAR_FLG10_MDL7_OUTB    0x2000U       // Input Flag for MDL7_OUTB Signal
#define XBAR_FLG10_MDL8_OUTA    0x4000U       // Input Flag for MDL8_OUTA Signal
#define XBAR_FLG10_MDL8_OUTB    0x8000U       // Input Flag for MDL8_OUTB Signal
#define XBAR_FLG10_MDL9_OUTA    0x10000U      // Input Flag for MDL9_OUTA Signal
#define XBAR_FLG10_MDL9_OUTB    0x20000U      // Input Flag for MDL9_OUTB Signal
#define XBAR_FLG10_MDL10_OUTA   0x40000U      // Input Flag for MDL10_OUTA Signal
#define XBAR_FLG10_MDL10_OUTB   0x80000U      // Input Flag for MDL10_OUTB Signal
#define XBAR_FLG10_MDL11_OUTA   0x100000U     // Input Flag for MDL11_OUTA Signal
#define XBAR_FLG10_MDL11_OUTB   0x200000U     // Input Flag for MDL11_OUTB Signal
#define XBAR_FLG10_MDL12_OUTA   0x400000U     // Input Flag for MDL12_OUTA Signal
#define XBAR_FLG10_MDL12_OUTB   0x800000U     // Input Flag for MDL12_OUTB Signal
#define XBAR_FLG10_MDL13_OUTA   0x1000000U    // Input Flag for MDL13_OUTA Signal
#define XBAR_FLG10_MDL13_OUTB   0x2000000U    // Input Flag for MDL13_OUTB Signal
#define XBAR_FLG10_MDL14_OUTA   0x4000000U    // Input Flag for MDL14_OUTA Signal
#define XBAR_FLG10_MDL14_OUTB   0x8000000U    // Input Flag for MDL14_OUTB Signal
#define XBAR_FLG10_MDL15_OUTA   0x10000000U   // Input Flag for MDL15_OUTA Signal
#define XBAR_FLG10_MDL15_OUTB   0x20000000U   // Input Flag for MDL15_OUTB Signal
#define XBAR_FLG10_MDL16_OUTA   0x40000000U   // Input Flag for MDL16_OUTA Signal
#define XBAR_FLG10_MDL16_OUTB   0x80000000U   // Input Flag for MDL16_OUTB Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG11 register
//
//*************************************************************************************************
#define XBAR_FLG11_MDL17_OUTA   0x1U   // Input Flag for MDL17_OUTA Signal
#define XBAR_FLG11_MDL17_OUTB   0x2U   // Input Flag for MDL17_OUTB Signal
#define XBAR_FLG11_MDL18_OUTA   0x4U   // Input Flag for MDL18_OUTA Signal
#define XBAR_FLG11_MDL18_OUTB   0x8U   // Input Flag for MDL18_OUTB Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG12 register
//
//*************************************************************************************************
#define XBAR_FLG12_CLB1_OUT0   0x1U          // Input Flag for CLB1_OUT0 Signal
#define XBAR_FLG12_CLB1_OUT1   0x2U          // Input Flag for CLB1_OUT1 Signal
#define XBAR_FLG12_CLB1_OUT2   0x4U          // Input Flag for CLB1_OUT2 Signal
#define XBAR_FLG12_CLB1_OUT3   0x8U          // Input Flag for CLB1_OUT3 Signal
#define XBAR_FLG12_CLB1_OUT6   0x10U         // Input Flag for CLB1_OUT6 Signal
#define XBAR_FLG12_CLB1_OUT7   0x20U         // Input Flag for CLB1_OUT7 Signal
#define XBAR_FLG12_CLB2_OUT0   0x40U         // Input Flag for CLB2_OUT0 Signal
#define XBAR_FLG12_CLB2_OUT1   0x80U         // Input Flag for CLB2_OUT1 Signal
#define XBAR_FLG12_CLB2_OUT2   0x100U        // Input Flag for CLB2_OUT2 Signal
#define XBAR_FLG12_CLB2_OUT3   0x200U        // Input Flag for CLB2_OUT3 Signal
#define XBAR_FLG12_CLB2_OUT6   0x400U        // Input Flag for CLB2_OUT6 Signal
#define XBAR_FLG12_CLB2_OUT7   0x800U        // Input Flag for CLB2_OUT7 Signal
#define XBAR_FLG12_CLB3_OUT0   0x1000U       // Input Flag for CLB3_OUT0 Signal
#define XBAR_FLG12_CLB3_OUT1   0x2000U       // Input Flag for CLB3_OUT1 Signal
#define XBAR_FLG12_CLB3_OUT2   0x4000U       // Input Flag for CLB3_OUT2 Signal
#define XBAR_FLG12_CLB3_OUT3   0x8000U       // Input Flag for CLB3_OUT3 Signal
#define XBAR_FLG12_CLB3_OUT6   0x10000U      // Input Flag for CLB3_OUT6 Signal
#define XBAR_FLG12_CLB3_OUT7   0x20000U      // Input Flag for CLB3_OUT7 Signal
#define XBAR_FLG12_CLB4_OUT0   0x40000U      // Input Flag for CLB4_OUT0 Signal
#define XBAR_FLG12_CLB4_OUT1   0x80000U      // Input Flag for CLB4_OUT1 Signal
#define XBAR_FLG12_CLB4_OUT2   0x100000U     // Input Flag for CLB4_OUT2 Signal
#define XBAR_FLG12_CLB4_OUT3   0x200000U     // Input Flag for CLB4_OUT3 Signal
#define XBAR_FLG12_CLB4_OUT6   0x400000U     // Input Flag for CLB4_OUT6 Signal
#define XBAR_FLG12_CLB4_OUT7   0x800000U     // Input Flag for CLB4_OUT7 Signal
#define XBAR_FLG12_CLB5_OUT0   0x1000000U    // Input Flag for CLB5_OUT0 Signal
#define XBAR_FLG12_CLB5_OUT1   0x2000000U    // Input Flag for CLB5_OUT1 Signal
#define XBAR_FLG12_CLB5_OUT2   0x4000000U    // Input Flag for CLB5_OUT2 Signal
#define XBAR_FLG12_CLB5_OUT3   0x8000000U    // Input Flag for CLB5_OUT3 Signal
#define XBAR_FLG12_CLB5_OUT6   0x10000000U   // Input Flag for CLB5_OUT6 Signal
#define XBAR_FLG12_CLB5_OUT7   0x20000000U   // Input Flag for CLB5_OUT7 Signal
#define XBAR_FLG12_CLB6_OUT0   0x40000000U   // Input Flag for CLB6_OUT0 Signal
#define XBAR_FLG12_CLB6_OUT1   0x80000000U   // Input Flag for CLB6_OUT1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG13 register
//
//*************************************************************************************************
#define XBAR_FLG13_CLB6_OUT2         0x1U          // Input Flag for CLB6_OUT2 Signal
#define XBAR_FLG13_CLB6_OUT3         0x2U          // Input Flag for CLB6_OUT3 Signal
#define XBAR_FLG13_CLB6_OUT6         0x4U          // Input Flag for CLB6_OUT6 Signal
#define XBAR_FLG13_CLB6_OUT7         0x8U          // Input Flag for CLB6_OUT7 Signal
#define XBAR_FLG13_XTRIPOUT1         0x10U         // Input Flag for XTRIPOUT1 Signal
#define XBAR_FLG13_XTRIPOUT2         0x20U         // Input Flag for XTRIPOUT2 Signal
#define XBAR_FLG13_XTRIPOUT3         0x40U         // Input Flag for XTRIPOUT3 Signal
#define XBAR_FLG13_XTRIPOUT4         0x80U         // Input Flag for XTRIPOUT4 Signal
#define XBAR_FLG13_XTRIPOUT5         0x100U        // Input Flag for XTRIPOUT5 Signal
#define XBAR_FLG13_XTRIPOUT6         0x200U        // Input Flag for XTRIPOUT6 Signal
#define XBAR_FLG13_XTRIPOUT7         0x400U        // Input Flag for XTRIPOUT7 Signal
#define XBAR_FLG13_XTRIPOUT8         0x800U        // Input Flag for XTRIPOUT8 Signal
#define XBAR_FLG13_ADCA_EXTMUXSEL0   0x1000U       // Input Flag for ADCA_EXTMUXSEL0 Signal
#define XBAR_FLG13_ADCA_EXTMUXSEL1   0x2000U       // Input Flag for ADCA_EXTMUXSEL1 Signal
#define XBAR_FLG13_ADCA_EXTMUXSEL2   0x4000U       // Input Flag for ADCA_EXTMUXSEL2 Signal
#define XBAR_FLG13_ADCA_EXTMUXSEL3   0x8000U       // Input Flag for ADCA_EXTMUXSEL3 Signal
#define XBAR_FLG13_ADCB_EXTMUXSEL0   0x10000U      // Input Flag for ADCB_EXTMUXSEL0 Signal
#define XBAR_FLG13_ADCB_EXTMUXSEL1   0x20000U      // Input Flag for ADCB_EXTMUXSEL1 Signal
#define XBAR_FLG13_ADCB_EXTMUXSEL2   0x40000U      // Input Flag for ADCB_EXTMUXSEL2 Signal
#define XBAR_FLG13_ADCB_EXTMUXSEL3   0x80000U      // Input Flag for ADCB_EXTMUXSEL3 Signal
#define XBAR_FLG13_ADCC_EXTMUXSEL0   0x100000U     // Input Flag for ADCC_EXTMUXSEL0 Signal
#define XBAR_FLG13_ADCC_EXTMUXSEL1   0x200000U     // Input Flag for ADCC_EXTMUXSEL1 Signal
#define XBAR_FLG13_ADCC_EXTMUXSEL2   0x400000U     // Input Flag for ADCC_EXTMUXSEL2 Signal
#define XBAR_FLG13_ADCC_EXTMUXSEL3   0x800000U     // Input Flag for ADCC_EXTMUXSEL3 Signal
#define XBAR_FLG13_PIEERR            0x4000000U    // Input Flag for PIEERR Signal
#define XBAR_FLG13_ECCERR            0x8000000U    // Input Flag for ECCERR Signal
#define XBAR_FLG13_EPG1_EPGOUT0      0x10000000U   // Input Flag for EPG1_EPGOUT0 Signal
#define XBAR_FLG13_EPG1_EPGOUT1      0x20000000U   // Input Flag for EPG1_EPGOUT1 Signal
#define XBAR_FLG13_EPG1_EPGOUT2      0x40000000U   // Input Flag for EPG1_EPGOUT2 Signal
#define XBAR_FLG13_EPG1_EPGOUT3      0x80000000U   // Input Flag for EPG1_EPGOUT3 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG14 register
//
//*************************************************************************************************
#define XBAR_FLG14_SD3FLT1_COMPH        0x1U          // Input Flag for SD3FLT1_COMPH Signal
#define XBAR_FLG14_SD3FLT1_COMPL        0x2U          // Input Flag for SD3FLT1_COMPL Signal
#define XBAR_FLG14_SD3FLT2_COMPH        0x4U          // Input Flag for SD3FLT2_COMPH Signal
#define XBAR_FLG14_SD3FLT2_COMPL        0x8U          // Input Flag for SD3FLT2_COMPL Signal
#define XBAR_FLG14_SD3FLT3_COMPH        0x10U         // Input Flag for SD3FLT3_COMPH Signal
#define XBAR_FLG14_SD3FLT3_COMPL        0x20U         // Input Flag for SD3FLT3_COMPL Signal
#define XBAR_FLG14_SD3FLT4_COMPH        0x40U         // Input Flag for SD3FLT4_COMPH Signal
#define XBAR_FLG14_SD3FLT4_COMPL        0x80U         // Input Flag for SD3FLT4_COMPL Signal
#define XBAR_FLG14_SD4FLT1_COMPH        0x100U        // Input Flag for SD4FLT1_COMPH Signal
#define XBAR_FLG14_SD4FLT1_COMPL        0x200U        // Input Flag for SD4FLT1_COMPL Signal
#define XBAR_FLG14_SD4FLT2_COMPH        0x400U        // Input Flag for SD4FLT2_COMPH Signal
#define XBAR_FLG14_SD4FLT2_COMPL        0x800U        // Input Flag for SD4FLT2_COMPL Signal
#define XBAR_FLG14_SD4FLT3_COMPH        0x1000U       // Input Flag for SD4FLT3_COMPH Signal
#define XBAR_FLG14_SD4FLT3_COMPL        0x2000U       // Input Flag for SD4FLT3_COMPL Signal
#define XBAR_FLG14_SD4FLT4_COMPH        0x4000U       // Input Flag for SD4FLT4_COMPH Signal
#define XBAR_FLG14_SD4FLT4_COMPL        0x8000U       // Input Flag for SD4FLT4_COMPL Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT10   0x20000U      // Input Flag for INPUTXBAR2_INPUT10 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT11   0x40000U      // Input Flag for INPUTXBAR2_INPUT11 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT12   0x80000U      // Input Flag for INPUTXBAR2_INPUT12 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT13   0x100000U     // Input Flag for INPUTXBAR2_INPUT13 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT14   0x200000U     // Input Flag for INPUTXBAR2_INPUT14 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT7    0x400000U     // Input Flag for INPUTXBAR2_INPUT7 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT8    0x800000U     // Input Flag for INPUTXBAR2_INPUT8 Signal
#define XBAR_FLG14_INPUTXBAR2_INPUT9    0x1000000U    // Input Flag for INPUTXBAR2_INPUT9 Signal
#define XBAR_FLG14_MCANB_FEVT0          0x2000000U    // Input Flag for MCANB_FEVT0 Signal
#define XBAR_FLG14_MCANB_FEVT1          0x4000000U    // Input Flag for MCANB_FEVT1 Signal
#define XBAR_FLG14_MCANB_FEVT2          0x8000000U    // Input Flag for MCANB_FEVT2 Signal
#define XBAR_FLG14_FSIA_RX_TRIG1        0x10000000U   // Input Flag for FSIA_RX_TRIG1 Signal
#define XBAR_FLG14_FSIB_RX_TRIG1        0x20000000U   // Input Flag for FSIB_RX_TRIG1 Signal
#define XBAR_FLG14_FSIC_RX_TRIG1        0x40000000U   // Input Flag for FSIC_RX_TRIG1 Signal
#define XBAR_FLG14_FSID_RX_TRIG1        0x80000000U   // Input Flag for FSID_RX_TRIG1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG15 register
//
//*************************************************************************************************
#define XBAR_FLG15_FSIRXA_TRIG_2       0x1U          // Input Flag for FSIRXA_TRIG_2 Signal
#define XBAR_FLG15_FSIRXA_TRIG_3       0x2U          // Input Flag for FSIRXA_TRIG_3 Signal
#define XBAR_FLG15_FSIRXB_TRIG_2       0x4U          // Input Flag for FSIRXB_TRIG_2 Signal
#define XBAR_FLG15_FSIRXB_TRIG_3       0x8U          // Input Flag for FSIRXB_TRIG_3 Signal
#define XBAR_FLG15_FSIRXC_TRIG_2       0x10U         // Input Flag for FSIRXC_TRIG_2 Signal
#define XBAR_FLG15_FSIRXC_TRIG_3       0x20U         // Input Flag for FSIRXC_TRIG_3 Signal
#define XBAR_FLG15_FSIRXD_TRIG_2       0x40U         // Input Flag for FSIRXD_TRIG_2 Signal
#define XBAR_FLG15_FSIRXD_TRIG_3       0x80U         // Input Flag for FSIRXD_TRIG_3 Signal
#define XBAR_FLG15_ECAP1_TRIPOUT       0x100U        // Input Flag for ECAP1_TRIPOUT Signal
#define XBAR_FLG15_ECAP2_TRIPOUT       0x200U        // Input Flag for ECAP2_TRIPOUT Signal
#define XBAR_FLG15_ECAP3_TRIPOUT       0x400U        // Input Flag for ECAP3_TRIPOUT Signal
#define XBAR_FLG15_ECAP4_TRIPOUT       0x800U        // Input Flag for ECAP4_TRIPOUT Signal
#define XBAR_FLG15_ECAP5_TRIPOUT       0x1000U       // Input Flag for ECAP5_TRIPOUT Signal
#define XBAR_FLG15_ECAP6_TRIPOUT       0x2000U       // Input Flag for ECAP6_TRIPOUT Signal
#define XBAR_FLG15_CPU1ERADEVT10       0x4000U       // Input Flag for CPU1ERADEVT10 Signal
#define XBAR_FLG15_CPU1ERADEVT11       0x8000U       // Input Flag for CPU1ERADEVT11 Signal
#define XBAR_FLG15_CPU1ERADEVT8        0x10000U      // Input Flag for CPU1ERADEVT8 Signal
#define XBAR_FLG15_CPU1ERADEVT9        0x20000U      // Input Flag for CPU1ERADEVT9 Signal
#define XBAR_FLG15_CPU1_ADCCHECKEVT1   0x40000U      // Input Flag for CPU1_ADCCHECKEVT1 Signal
#define XBAR_FLG15_CPU1_ADCCHECKEVT2   0x80000U      // Input Flag for CPU1_ADCCHECKEVT2 Signal
#define XBAR_FLG15_CPU1_ADCCHECKEVT3   0x100000U     // Input Flag for CPU1_ADCCHECKEVT3 Signal
#define XBAR_FLG15_CPU1_ADCCHECKEVT4   0x200000U     // Input Flag for CPU1_ADCCHECKEVT4 Signal
#define XBAR_FLG15_CPU2ERADEVT10       0x400000U     // Input Flag for CPU2ERADEVT10 Signal
#define XBAR_FLG15_CPU2ERADEVT11       0x800000U     // Input Flag for CPU2ERADEVT11 Signal
#define XBAR_FLG15_CPU2ERADEVT8        0x1000000U    // Input Flag for CPU2ERADEVT8 Signal
#define XBAR_FLG15_CPU2ERADEVT9        0x2000000U    // Input Flag for CPU2ERADEVT9 Signal
#define XBAR_FLG15_CPU2_ADCCHECKEVT1   0x4000000U    // Input Flag for CPU2_ADCCHECKEVT1 Signal
#define XBAR_FLG15_CPU2_ADCCHECKEVT2   0x8000000U    // Input Flag for CPU2_ADCCHECKEVT2 Signal
#define XBAR_FLG15_CPU2_ADCCHECKEVT3   0x10000000U   // Input Flag for CPU2_ADCCHECKEVT3 Signal
#define XBAR_FLG15_CPU2_ADCCHECKEVT4   0x20000000U   // Input Flag for CPU2_ADCCHECKEVT4 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARFLG16 register
//
//*************************************************************************************************
#define XBAR_FLG16_CMPSS9_CTRIPH       0x1U          // Input Flag for CMPSS9_CTRIPH Signal
#define XBAR_FLG16_CMPSS9_CTRIPL       0x2U          // Input Flag for CMPSS9_CTRIPL Signal
#define XBAR_FLG16_CMPSS9_CTRIPOUTH    0x4U          // Input Flag for CMPSS9_CTRIPOUTH Signal
#define XBAR_FLG16_CMPSS9_CTRIPOUTL    0x8U          // Input Flag for CMPSS9_CTRIPOUTL Signal
#define XBAR_FLG16_CMPSS10_CTRIPH      0x10U         // Input Flag for CMPSS10_CTRIPH Signal
#define XBAR_FLG16_CMPSS10_CTRIPL      0x20U         // Input Flag for CMPSS10_CTRIPL Signal
#define XBAR_FLG16_CMPSS10_CTRIPOUTH   0x40U         // Input Flag for CMPSS10_CTRIPOUTH Signal
#define XBAR_FLG16_CMPSS10_CTRIPOUTL   0x80U         // Input Flag for CMPSS10_CTRIPOUTL Signal
#define XBAR_FLG16_CMPSS11_CTRIPH      0x100U        // Input Flag for CMPSS11_CTRIPH Signal
#define XBAR_FLG16_CMPSS11_CTRIPL      0x200U        // Input Flag for CMPSS11_CTRIPL Signal
#define XBAR_FLG16_CMPSS11_CTRIPOUTH   0x400U        // Input Flag for CMPSS11_CTRIPOUTH Signal
#define XBAR_FLG16_CMPSS11_CTRIPOUTL   0x800U        // Input Flag for CMPSS11_CTRIPOUTL Signal
#define XBAR_FLG16_CMPSS12_CTRIPH      0x1000U       // Input Flag for CMPSS12_CTRIPH Signal
#define XBAR_FLG16_CMPSS12_CTRIPL      0x2000U       // Input Flag for CMPSS12_CTRIPL Signal
#define XBAR_FLG16_CMPSS12_CTRIPOUTH   0x4000U       // Input Flag for CMPSS12_CTRIPOUTH Signal
#define XBAR_FLG16_CMPSS12_CTRIPOUTL   0x8000U       // Input Flag for CMPSS12_CTRIPOUTL Signal
#define XBAR_FLG16_XCLKOUT             0x80000000U   // Input Flag for XCLKOUT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR1 register
//
//*************************************************************************************************
#define XBAR_CLR1_CMPSS1_CTRIPL      0x1U          // Input Flag Clear for CMPSS1.CTRIPL Signal
#define XBAR_CLR1_CMPSS1_CTRIPH      0x2U          // Input Flag Clear for CMPSS1.CTRIPH Signal
#define XBAR_CLR1_CMPSS2_CTRIPL      0x4U          // Input Flag Clear for CMPSS2.CTRIPL Signal
#define XBAR_CLR1_CMPSS2_CTRIPH      0x8U          // Input Flag Clear for CMPSS2.CTRIPH Signal
#define XBAR_CLR1_CMPSS3_CTRIPL      0x10U         // Input Flag Clear for CMPSS3.CTRIPL Signal
#define XBAR_CLR1_CMPSS3_CTRIPH      0x20U         // Input Flag Clear for CMPSS3.CTRIPH Signal
#define XBAR_CLR1_CMPSS4_CTRIPL      0x40U         // Input Flag Clear for CMPSS4.CTRIPL Signal
#define XBAR_CLR1_CMPSS4_CTRIPH      0x80U         // Input Flag Clear for CMPSS4.CTRIPH Signal
#define XBAR_CLR1_CMPSS5_CTRIPL      0x100U        // Input Flag Clear for CMPSS5.CTRIPL Signal
#define XBAR_CLR1_CMPSS5_CTRIPH      0x200U        // Input Flag Clear for CMPSS5.CTRIPH Signal
#define XBAR_CLR1_CMPSS6_CTRIPL      0x400U        // Input Flag Clear for CMPSS6.CTRIPL Signal
#define XBAR_CLR1_CMPSS6_CTRIPH      0x800U        // Input Flag Clear for CMPSS6.CTRIPH Signal
#define XBAR_CLR1_CMPSS7_CTRIPL      0x1000U       // Input Flag Clear for CMPSS7.CTRIPL Signal
#define XBAR_CLR1_CMPSS7_CTRIPH      0x2000U       // Input Flag Clear for CMPSS7.CTRIPH Signal
#define XBAR_CLR1_CMPSS8_CTRIPL      0x4000U       // Input Flag Clear for CMPSS8.CTRIPL Signal
#define XBAR_CLR1_CMPSS8_CTRIPH      0x8000U       // Input Flag Clear for CMPSS8.CTRIPH Signal
#define XBAR_CLR1_CMPSS1_CTRIPOUTL   0x10000U      // Input Flag Clear for CMPSS1.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS1_CTRIPOUTH   0x20000U      // Input Flag Clear for CMPSS1.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS2_CTRIPOUTL   0x40000U      // Input Flag Clear for CMPSS2.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS2_CTRIPOUTH   0x80000U      // Input Flag Clear for CMPSS2.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS3_CTRIPOUTL   0x100000U     // Input Flag Clear for CMPSS3.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS3_CTRIPOUTH   0x200000U     // Input Flag Clear for CMPSS3.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS4_CTRIPOUTL   0x400000U     // Input Flag Clear for CMPSS4.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS4_CTRIPOUTH   0x800000U     // Input Flag Clear for CMPSS4.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS5_CTRIPOUTL   0x1000000U    // Input Flag Clear for CMPSS5.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS5_CTRIPOUTH   0x2000000U    // Input Flag Clear for CMPSS5.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS6_CTRIPOUTL   0x4000000U    // Input Flag Clear for CMPSS6.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS6_CTRIPOUTH   0x8000000U    // Input Flag Clear for CMPSS6.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS7_CTRIPOUTL   0x10000000U   // Input Flag Clear for CMPSS7.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS7_CTRIPOUTH   0x20000000U   // Input Flag Clear for CMPSS7.CTRIPOUTH Signal
#define XBAR_CLR1_CMPSS8_CTRIPOUTL   0x40000000U   // Input Flag Clear for CMPSS8.CTRIPOUTL Signal
#define XBAR_CLR1_CMPSS8_CTRIPOUTH   0x80000000U   // Input Flag Clear for CMPSS8.CTRIPOUTH Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR2 register
//
//*************************************************************************************************
#define XBAR_CLR2_INPUT1       0x1U          // Input Flag Clear for INPUT1 Signal
#define XBAR_CLR2_INPUT2       0x2U          // Input Flag Clear for INPUT2 Signal
#define XBAR_CLR2_INPUT3       0x4U          // Input Flag Clear for INPUT3 Signal
#define XBAR_CLR2_INPUT4       0x8U          // Input Flag Clear for INPUT4 Signal
#define XBAR_CLR2_INPUT5       0x10U         // Input Flag Clear for INPUT5 Signal
#define XBAR_CLR2_INPUT6       0x20U         // Input Flag Clear for INPUT6 Signal
#define XBAR_CLR2_ADCSOCA      0x40U         // Input Flag Clear for ADCSOCA Signal
#define XBAR_CLR2_ADCSOCB      0x80U         // Input Flag Clear for ADCSOCB Signal
#define XBAR_CLR2_INPUT7       0x100U        // Input Flag Clear for INPUT7 Signal
#define XBAR_CLR2_INPUT8       0x200U        // Input Flag Clear for INPUT8 Signal
#define XBAR_CLR2_INPUT9       0x400U        // Input Flag Clear for INPUT9 Signal
#define XBAR_CLR2_INPUT10      0x800U        // Input Flag Clear for INPUT10 Signal
#define XBAR_CLR2_INPUT11      0x1000U       // Input Flag Clear for INPUT11 Signal
#define XBAR_CLR2_INPUT12      0x2000U       // Input Flag Clear for INPUT12 Signal
#define XBAR_CLR2_INPUT13      0x4000U       // Input Flag Clear for INPUT13 Signal
#define XBAR_CLR2_INPUT14      0x8000U       // Input Flag Clear for INPUT14 Signal
#define XBAR_CLR2_ECAP1_OUT    0x10000U      // Input Flag Clear for ECAP1.OUT Signal
#define XBAR_CLR2_ECAP2_OUT    0x20000U      // Input Flag Clear for ECAP2.OUT Signal
#define XBAR_CLR2_ECAP3_OUT    0x40000U      // Input Flag Clear for ECAP3.OUT Signal
#define XBAR_CLR2_ECAP4_OUT    0x80000U      // Input Flag Clear for ECAP4.OUT Signal
#define XBAR_CLR2_ECAP5_OUT    0x100000U     // Input Flag Clear for ECAP5.OUT Signal
#define XBAR_CLR2_ECAP6_OUT    0x200000U     // Input Flag Clear for ECAP6.OUT Signal
#define XBAR_CLR2_EXTSYNCOUT   0x400000U     // Input Flag Clear for EXTSYNCOUT Signal
#define XBAR_CLR2_ADCAEVT1     0x800000U     // Input Flag Clear for ADCAEVT1 Signal
#define XBAR_CLR2_ADCAEVT2     0x1000000U    // Input Flag Clear for ADCAEVT2 Signal
#define XBAR_CLR2_ADCAEVT3     0x2000000U    // Input Flag Clear for ADCAEVT3 Signal
#define XBAR_CLR2_ADCAEVT4     0x4000000U    // Input Flag Clear for ADCAEVT4 Signal
#define XBAR_CLR2_ADCBEVT1     0x8000000U    // Input Flag Clear for ADCBEVT1 Signal
#define XBAR_CLR2_ADCBEVT2     0x10000000U   // Input Flag Clear for ADCBEVT2 Signal
#define XBAR_CLR2_ADCBEVT3     0x20000000U   // Input Flag Clear for ADCBEVT3 Signal
#define XBAR_CLR2_ADCBEVT4     0x40000000U   // Input Flag Clear for ADCBEVT4 Signal
#define XBAR_CLR2_ADCCEVT1     0x80000000U   // Input Flag Clear for ADCCEVT1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR3 register
//
//*************************************************************************************************
#define XBAR_CLR3_ADCCEVT2        0x1U        // Input Flag Clear for ADCCEVT2 Signal
#define XBAR_CLR3_ADCCEVT3        0x2U        // Input Flag Clear for ADCCEVT3 Signal
#define XBAR_CLR3_ADCCEVT4        0x4U        // Input Flag Clear for ADCCEVT4 Signal
#define XBAR_CLR3_SD1FLT1_COMPL   0x80U       // Input Flag Clear for SD1FLT1.COMPL Signal
#define XBAR_CLR3_SD1FLT1_COMPH   0x100U      // Input Flag Clear for SD1FLT1.COMPH Signal
#define XBAR_CLR3_SD1FLT2_COMPL   0x200U      // Input Flag Clear for SD1FLT2.COMPL Signal
#define XBAR_CLR3_SD1FLT2_COMPH   0x400U      // Input Flag Clear for SD1FLT2.COMPH Signal
#define XBAR_CLR3_SD1FLT3_COMPL   0x800U      // Input Flag Clear for SD1FLT3.COMPL Signal
#define XBAR_CLR3_SD1FLT3_COMPH   0x1000U     // Input Flag Clear for SD1FLT3.COMPH Signal
#define XBAR_CLR3_SD1FLT4_COMPL   0x2000U     // Input Flag Clear for SD1FLT4.COMPL Signal
#define XBAR_CLR3_SD1FLT4_COMPH   0x4000U     // Input Flag Clear for SD1FLT4.COMPH Signal
#define XBAR_CLR3_SD2FLT1_COMPL   0x8000U     // Input Flag Clear for SD2FLT1.COMPL Signal
#define XBAR_CLR3_SD2FLT1_COMPH   0x10000U    // Input Flag Clear for SD2FLT1.COMPH Signal
#define XBAR_CLR3_SD2FLT2_COMPL   0x20000U    // Input Flag Clear for SD2FLT2.COMPL Signal
#define XBAR_CLR3_SD2FLT2_COMPH   0x40000U    // Input Flag Clear for SD2FLT2.COMPH Signal
#define XBAR_CLR3_SD2FLT3_COMPL   0x80000U    // Input Flag Clear for SD2FLT3.COMPL Signal
#define XBAR_CLR3_SD2FLT3_COMPH   0x100000U   // Input Flag Clear for SD2FLT3.COMPH Signal
#define XBAR_CLR3_SD2FLT4_COMPL   0x200000U   // Input Flag Clear for SD2FLT4.COMPL Signal
#define XBAR_CLR3_SD2FLT4_COMPH   0x400000U   // Input Flag Clear for SD2FLT4.COMPH Signal
#define XBAR_CLR3_ECAP7_OUT       0x800000U   // Input Flag clear for ECAP7.OUT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR4 register
//
//*************************************************************************************************
#define XBAR_CLR4_MCANA_FEVT0      0x200U        // Input Flag clear for MCANA_FEVT0 Signal
#define XBAR_CLR4_MCANA_FEVT1      0x400U        // Input Flag clear for MCANA_FEVT1 Signal
#define XBAR_CLR4_MCANA_FEVT2      0x800U        // Input Flag clear for MCANA_FEVT2 Signal
#define XBAR_CLR4_CLB1_OUT4        0x10000U      // Input Flag clear for CLB1_4.1 Signal
#define XBAR_CLR4_CLB1_OUT5        0x20000U      // Input Flag clear for CLB1_5.1 Signal
#define XBAR_CLR4_CLB2_OUT4        0x40000U      // Input Flag clear for CLB2_4.1 Signal
#define XBAR_CLR4_CLB2_OUT5        0x80000U      // Input Flag clear for CLB2_5.1 Signal
#define XBAR_CLR4_CLB3_OUT4        0x100000U     // Input Flag clear for CLB3_4.1 Signal
#define XBAR_CLR4_CLB3_OUT5        0x200000U     // Input Flag clear for CLB3_5.1 Signal
#define XBAR_CLR4_CLB4_OUT4        0x400000U     // Input Flag clear for CLB4_4.1 Signal
#define XBAR_CLR4_CLB4_OUT5        0x800000U     // Input Flag clear for CLB4_5.1 Signal
#define XBAR_CLR4_CLB5_OUT4        0x1000000U    // Input Latch clear for CLB5_OUT4 Signal
#define XBAR_CLR4_CLB5_OUT5        0x2000000U    // Input Latch clear for CLB5_OUT5 Signal
#define XBAR_CLR4_CLB6_OUT4        0x4000000U    // Input Latch clear for CLB6_OUT4 Signal
#define XBAR_CLR4_CLB6_OUT5        0x8000000U    // Input Latch clear for CLB6_OUT5 Signal
#define XBAR_CLR4_ERRORSTS_ERROR   0x10000000U   // Input Latch clear for ERRORSTS_ERROR Signal
#define XBAR_CLR4_ECATSYNC0        0x20000000U   // Input Latch clear for ECATSYNC0 Signal
#define XBAR_CLR4_ECATSYNC1        0x40000000U   // Input Latch clear for ECATSYNC1 Signal
#define XBAR_CLR4_CLAHALT          0x80000000U   // Input Flag clear for CLAHALT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR5 register
//
//*************************************************************************************************
#define XBAR_CLR5_EPWM1_TRIPOUT    0x1U       // Input Flag clear for EPWM1_TRIPOUT Signal
#define XBAR_CLR5_EPWM2_TRIPOUT    0x2U       // Input Flag clear for EPWM2_TRIPOUT Signal
#define XBAR_CLR5_EPWM3_TRIPOUT    0x4U       // Input Flag clear for EPWM3_TRIPOUT Signal
#define XBAR_CLR5_EPWM4_TRIPOUT    0x8U       // Input Flag clear for EPWM4_TRIPOUT Signal
#define XBAR_CLR5_EPWM5_TRIPOUT    0x10U      // Input Flag clear for EPWM5_TRIPOUT Signal
#define XBAR_CLR5_EPWM6_TRIPOUT    0x20U      // Input Flag clear for EPWM6_TRIPOUT Signal
#define XBAR_CLR5_EPWM7_TRIPOUT    0x40U      // Input Flag clear for EPWM7_TRIPOUT Signal
#define XBAR_CLR5_EPWM8_TRIPOUT    0x80U      // Input Flag clear for EPWM8_TRIPOUT Signal
#define XBAR_CLR5_EPWM9_TRIPOUT    0x100U     // Input Flag clear for EPWM9_TRIPOUT Signal
#define XBAR_CLR5_EPWM10_TRIPOUT   0x200U     // Input Flag clear for EPWM10_TRIPOUT Signal
#define XBAR_CLR5_EPWM11_TRIPOUT   0x400U     // Input Flag clear for EPWM11_TRIPOUT Signal
#define XBAR_CLR5_EPWM12_TRIPOUT   0x800U     // Input Flag clear for EPWM12_TRIPOUT Signal
#define XBAR_CLR5_EPWM13_TRIPOUT   0x1000U    // Input Flag clear for EPWM13_TRIPOUT Signal
#define XBAR_CLR5_EPWM14_TRIPOUT   0x2000U    // Input Flag clear for EPWM14_TRIPOUT Signal
#define XBAR_CLR5_EPWM15_TRIPOUT   0x4000U    // Input Flag clear for EPWM15_TRIPOUT Signal
#define XBAR_CLR5_EPWM16_TRIPOUT   0x8000U    // Input Flag clear for EPWM16_TRIPOUT Signal
#define XBAR_CLR5_EPWM17_TRIPOUT   0x10000U   // Input Flag clear for EPWM17_TRIPOUT Signal
#define XBAR_CLR5_EPWM18_TRIPOUT   0x20000U   // Input Flag clear for EPWM18_TRIPOUT Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR6 register
//
//*************************************************************************************************
#define XBAR_CLR6_EPWM1_DEL_TRIP    0x1U       // Input Flag clear for EPWM1_DEL_TRIP Signal
#define XBAR_CLR6_EPWM2_DEL_TRIP    0x2U       // Input Flag clear for EPWM2_DEL_TRIP Signal
#define XBAR_CLR6_EPWM3_DEL_TRIP    0x4U       // Input Flag clear for EPWM3_DEL_TRIP Signal
#define XBAR_CLR6_EPWM4_DEL_TRIP    0x8U       // Input Flag clear for EPWM4_DEL_TRIP Signal
#define XBAR_CLR6_EPWM5_DEL_TRIP    0x10U      // Input Flag clear for EPWM5_DEL_TRIP Signal
#define XBAR_CLR6_EPWM6_DEL_TRIP    0x20U      // Input Flag clear for EPWM6_DEL_TRIP Signal
#define XBAR_CLR6_EPWM7_DEL_TRIP    0x40U      // Input Flag clear for EPWM7_DEL_TRIP Signal
#define XBAR_CLR6_EPWM8_DEL_TRIP    0x80U      // Input Flag clear for EPWM8_DEL_TRIP Signal
#define XBAR_CLR6_EPWM9_DEL_TRIP    0x100U     // Input Flag clear for EPWM9_DEL_TRIP Signal
#define XBAR_CLR6_EPWM10_DEL_TRIP   0x200U     // Input Flag clear for EPWM10_DEL_TRIP Signal
#define XBAR_CLR6_EPWM11_DEL_TRIP   0x400U     // Input Flag clear for EPWM11_DEL_TRIP Signal
#define XBAR_CLR6_EPWM12_DEL_TRIP   0x800U     // Input Flag clear for EPWM12_DEL_TRIP Signal
#define XBAR_CLR6_EPWM13_DEL_TRIP   0x1000U    // Input Flag clear for EPWM13_DEL_TRIP Signal
#define XBAR_CLR6_EPWM14_DEL_TRIP   0x2000U    // Input Flag clear for EPWM14_DEL_TRIP Signal
#define XBAR_CLR6_EPWM15_DEL_TRIP   0x4000U    // Input Flag clear for EPWM15_DEL_TRIP Signal
#define XBAR_CLR6_EPWM16_DEL_TRIP   0x8000U    // Input Flag clear for EPWM16_DEL_TRIP Signal
#define XBAR_CLR6_EPWM17_DEL_TRIP   0x10000U   // Input Flag clear for EPWM17_DEL_TRIP Signal
#define XBAR_CLR6_EPWM18_DEL_TRIP   0x20000U   // Input Flag clear for EPWM18_DEL_TRIP Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR7 register
//
//*************************************************************************************************
#define XBAR_CLR7_EPWM1_DEL_ACTIVE    0x1U       // Input Flag clear for EPWM1_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM2_DEL_ACTIVE    0x2U       // Input Flag clear for EPWM2_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM3_DEL_ACTIVE    0x4U       // Input Flag clear for EPWM3_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM4_DEL_ACTIVE    0x8U       // Input Flag clear for EPWM4_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM5_DEL_ACTIVE    0x10U      // Input Flag clear for EPWM5_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM6_DEL_ACTIVE    0x20U      // Input Flag clear for EPWM6_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM7_DEL_ACTIVE    0x40U      // Input Flag clear for EPWM7_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM8_DEL_ACTIVE    0x80U      // Input Flag clear for EPWM8_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM9_DEL_ACTIVE    0x100U     // Input Flag clear for EPWM9_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM10_DEL_ACTIVE   0x200U     // Input Flag clear for EPWM10_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM11_DEL_ACTIVE   0x400U     // Input Flag clear for EPWM11_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM12_DEL_ACTIVE   0x800U     // Input Flag clear for EPWM12_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM13_DEL_ACTIVE   0x1000U    // Input Flag clear for EPWM13_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM14_DEL_ACTIVE   0x2000U    // Input Flag clear for EPWM14_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM15_DEL_ACTIVE   0x4000U    // Input Flag clear for EPWM15_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM16_DEL_ACTIVE   0x8000U    // Input Flag clear for EPWM16_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM17_DEL_ACTIVE   0x10000U   // Input Flag clear for EPWM17_DEL_ACTIVE Signal
#define XBAR_CLR7_EPWM18_DEL_ACTIVE   0x20000U   // Input Flag clear for EPWM18_DEL_ACTIVE Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR8 register
//
//*************************************************************************************************
#define XBAR_CLR8_ETPWM1_A0_SCLK    0x1U          // Input Flag clear for ETPWM1_A0_sclk Signal
#define XBAR_CLR8_ETPWM1_B0_SCLK    0x2U          // Input Flag clear for ETPWM1_B0_sclk Signal
#define XBAR_CLR8_ETPWM2_A0_SCLK    0x4U          // Input Flag clear for ETPWM2_A0_sclk Signal
#define XBAR_CLR8_ETPWM2_B0_SCLK    0x8U          // Input Flag clear for ETPWM2_B0_sclk Signal
#define XBAR_CLR8_ETPWM3_A0_SCLK    0x10U         // Input Flag clear for ETPWM3_A0_sclk Signal
#define XBAR_CLR8_ETPWM3_B0_SCLK    0x20U         // Input Flag clear for ETPWM3_B0_sclk Signal
#define XBAR_CLR8_ETPWM4_A0_SCLK    0x40U         // Input Flag clear for ETPWM4_A0_sclk Signal
#define XBAR_CLR8_ETPWM4_B0_SCLK    0x80U         // Input Flag clear for ETPWM4_B0_sclk Signal
#define XBAR_CLR8_ETPWM5_A0_SCLK    0x100U        // Input Flag clear for ETPWM5_A0_sclk Signal
#define XBAR_CLR8_ETPWM5_B0_SCLK    0x200U        // Input Flag clear for ETPWM5_B0_sclk Signal
#define XBAR_CLR8_ETPWM6_A0_SCLK    0x400U        // Input Flag clear for ETPWM6_A0_sclk Signal
#define XBAR_CLR8_ETPWM6_B0_SCLK    0x800U        // Input Flag clear for ETPWM6_B0_sclk Signal
#define XBAR_CLR8_ETPWM7_A0_SCLK    0x1000U       // Input Flag clear for ETPWM7_A0_sclk Signal
#define XBAR_CLR8_ETPWM7_B0_SCLK    0x2000U       // Input Flag clear for ETPWM7_B0_sclk Signal
#define XBAR_CLR8_ETPWM8_A0_SCLK    0x4000U       // Input Flag clear for ETPWM8_A0_sclk Signal
#define XBAR_CLR8_ETPWM8_B0_SCLK    0x8000U       // Input Flag clear for ETPWM8_B0_sclk Signal
#define XBAR_CLR8_ETPWM9_A0_SCLK    0x10000U      // Input Flag clear for ETPWM9_A0_sclk Signal
#define XBAR_CLR8_ETPWM9_B0_SCLK    0x20000U      // Input Flag clear for ETPWM9_B0_sclk Signal
#define XBAR_CLR8_ETPWM10_A0_SCLK   0x40000U      // Input Flag clear for ETPWM10_A0_sclk Signal
#define XBAR_CLR8_ETPWM10_B0_SCLK   0x80000U      // Input Flag clear for ETPWM10_B0_sclk Signal
#define XBAR_CLR8_ETPWM11_A0_SCLK   0x100000U     // Input Flag clear for ETPWM11_A0_sclk Signal
#define XBAR_CLR8_ETPWM11_B0_SCLK   0x200000U     // Input Flag clear for ETPWM11_B0_sclk Signal
#define XBAR_CLR8_ETPWM12_A0_SCLK   0x400000U     // Input Flag clear for ETPWM12_A0_sclk Signal
#define XBAR_CLR8_ETPWM12_B0_SCLK   0x800000U     // Input Flag clear for ETPWM12_B0_sclk Signal
#define XBAR_CLR8_ETPWM13_A0_SCLK   0x1000000U    // Input Flag clear for ETPWM13_A0_sclk Signal
#define XBAR_CLR8_ETPWM13_B0_SCLK   0x2000000U    // Input Flag clear for ETPWM13_B0_sclk Signal
#define XBAR_CLR8_ETPWM14_A0_SCLK   0x4000000U    // Input Flag clear for ETPWM14_A0_sclk Signal
#define XBAR_CLR8_ETPWM14_B0_SCLK   0x8000000U    // Input Flag clear for ETPWM14_B0_sclk Signal
#define XBAR_CLR8_ETPWM15_A0_SCLK   0x10000000U   // Input Flag clear for ETPWM15_A0_sclk Signal
#define XBAR_CLR8_ETPWM15_B0_SCLK   0x20000000U   // Input Flag clear for ETPWM15_B0_sclk Signal
#define XBAR_CLR8_ETPWM16_A0_SCLK   0x40000000U   // Input Flag clear for ETPWM16_A0_sclk Signal
#define XBAR_CLR8_ETPWM16_B0_SCLK   0x80000000U   // Input Flag clear for ETPWM16_B0_sclk Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR9 register
//
//*************************************************************************************************
#define XBAR_CLR9_ETPWM17_A0_SCLK   0x1U   // Input Flag clear for ETPWM17_A0_sclk Signal
#define XBAR_CLR9_ETPWM17_B0_SCLK   0x2U   // Input Flag clear for ETPWM17_B0_sclk Signal
#define XBAR_CLR9_ETPWM18_A0_SCLK   0x4U   // Input Flag clear for ETPWM18_A0_sclk Signal
#define XBAR_CLR9_ETPWM18_B0_SCLK   0x8U   // Input Flag clear for ETPWM18_B0_sclk Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR10 register
//
//*************************************************************************************************
#define XBAR_CLR10_MDL1_OUTA    0x1U          // Input Flag clear for MDL1_OUTA Signal
#define XBAR_CLR10_MDL1_OUTB    0x2U          // Input Flag clear for MDL1_OUTB Signal
#define XBAR_CLR10_MDL2_OUTA    0x4U          // Input Flag clear for MDL2_OUTA Signal
#define XBAR_CLR10_MDL2_OUTB    0x8U          // Input Flag clear for MDL2_OUTB Signal
#define XBAR_CLR10_MDL3_OUTA    0x10U         // Input Flag clear for MDL3_OUTA Signal
#define XBAR_CLR10_MDL3_OUTB    0x20U         // Input Flag clear for MDL3_OUTB Signal
#define XBAR_CLR10_MDL4_OUTA    0x40U         // Input Flag clear for MDL4_OUTA Signal
#define XBAR_CLR10_MDL4_OUTB    0x80U         // Input Flag clear for MDL4_OUTB Signal
#define XBAR_CLR10_MDL5_OUTA    0x100U        // Input Flag clear for MDL5_OUTA Signal
#define XBAR_CLR10_MDL5_OUTB    0x200U        // Input Flag clear for MDL5_OUTB Signal
#define XBAR_CLR10_MDL6_OUTA    0x400U        // Input Flag clear for MDL6_OUTA Signal
#define XBAR_CLR10_MDL6_OUTB    0x800U        // Input Flag clear for MDL6_OUTB Signal
#define XBAR_CLR10_MDL7_OUTA    0x1000U       // Input Flag clear for MDL7_OUTA Signal
#define XBAR_CLR10_MDL7_OUTB    0x2000U       // Input Flag clear for MDL7_OUTB Signal
#define XBAR_CLR10_MDL8_OUTA    0x4000U       // Input Flag clear for MDL8_OUTA Signal
#define XBAR_CLR10_MDL8_OUTB    0x8000U       // Input Flag clear for MDL8_OUTB Signal
#define XBAR_CLR10_MDL9_OUTA    0x10000U      // Input Flag clear for MDL9_OUTA Signal
#define XBAR_CLR10_MDL9_OUTB    0x20000U      // Input Flag clear for MDL9_OUTB Signal
#define XBAR_CLR10_MDL10_OUTA   0x40000U      // Input Flag clear for MDL10_OUTA Signal
#define XBAR_CLR10_MDL10_OUTB   0x80000U      // Input Flag clear for MDL10_OUTB Signal
#define XBAR_CLR10_MDL11_OUTA   0x100000U     // Input Flag clear for MDL11_OUTA Signal
#define XBAR_CLR10_MDL11_OUTB   0x200000U     // Input Flag clear for MDL11_OUTB Signal
#define XBAR_CLR10_MDL12_OUTA   0x400000U     // Input Flag clear for MDL12_OUTA Signal
#define XBAR_CLR10_MDL12_OUTB   0x800000U     // Input Flag clear for MDL12_OUTB Signal
#define XBAR_CLR10_MDL13_OUTA   0x1000000U    // Input Flag clear for MDL13_OUTA Signal
#define XBAR_CLR10_MDL13_OUTB   0x2000000U    // Input Flag clear for MDL13_OUTB Signal
#define XBAR_CLR10_MDL14_OUTA   0x4000000U    // Input Flag clear for MDL14_OUTA Signal
#define XBAR_CLR10_MDL14_OUTB   0x8000000U    // Input Flag clear for MDL14_OUTB Signal
#define XBAR_CLR10_MDL15_OUTA   0x10000000U   // Input Flag clear for MDL15_OUTA Signal
#define XBAR_CLR10_MDL15_OUTB   0x20000000U   // Input Flag clear for MDL15_OUTB Signal
#define XBAR_CLR10_MDL16_OUTA   0x40000000U   // Input Flag clear for MDL16_OUTA Signal
#define XBAR_CLR10_MDL16_OUTB   0x80000000U   // Input Flag clear for MDL16_OUTB Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR11 register
//
//*************************************************************************************************
#define XBAR_CLR11_MDL17_OUTA   0x1U   // Input Flag clear for MDL17_OUTA Signal
#define XBAR_CLR11_MDL17_OUTB   0x2U   // Input Flag clear for MDL17_OUTB Signal
#define XBAR_CLR11_MDL18_OUTA   0x4U   // Input Flag clear for MDL18_OUTA Signal
#define XBAR_CLR11_MDL18_OUTB   0x8U   // Input Flag clear for MDL18_OUTB Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR12 register
//
//*************************************************************************************************
#define XBAR_CLR12_CLB1_OUT0   0x1U          // Input Flag clear for CLB1_OUT0 Signal
#define XBAR_CLR12_CLB1_OUT1   0x2U          // Input Flag clear for CLB1_OUT1 Signal
#define XBAR_CLR12_CLB1_OUT2   0x4U          // Input Flag clear for CLB1_OUT2 Signal
#define XBAR_CLR12_CLB1_OUT3   0x8U          // Input Flag clear for CLB1_OUT3 Signal
#define XBAR_CLR12_CLB1_OUT6   0x10U         // Input Flag clear for CLB1_OUT6 Signal
#define XBAR_CLR12_CLB1_OUT7   0x20U         // Input Flag clear for CLB1_OUT7 Signal
#define XBAR_CLR12_CLB2_OUT0   0x40U         // Input Flag clear for CLB2_OUT0 Signal
#define XBAR_CLR12_CLB2_OUT1   0x80U         // Input Flag clear for CLB2_OUT1 Signal
#define XBAR_CLR12_CLB2_OUT2   0x100U        // Input Flag clear for CLB2_OUT2 Signal
#define XBAR_CLR12_CLB2_OUT3   0x200U        // Input Flag clear for CLB2_OUT3 Signal
#define XBAR_CLR12_CLB2_OUT6   0x400U        // Input Flag clear for CLB2_OUT6 Signal
#define XBAR_CLR12_CLB2_OUT7   0x800U        // Input Flag clear for CLB2_OUT7 Signal
#define XBAR_CLR12_CLB3_OUT0   0x1000U       // Input Flag clear for CLB3_OUT0 Signal
#define XBAR_CLR12_CLB3_OUT1   0x2000U       // Input Flag clear for CLB3_OUT1 Signal
#define XBAR_CLR12_CLB3_OUT2   0x4000U       // Input Flag clear for CLB3_OUT2 Signal
#define XBAR_CLR12_CLB3_OUT3   0x8000U       // Input Flag clear for CLB3_OUT3 Signal
#define XBAR_CLR12_CLB3_OUT6   0x10000U      // Input Flag clear for CLB3_OUT6 Signal
#define XBAR_CLR12_CLB3_OUT7   0x20000U      // Input Flag clear for CLB3_OUT7 Signal
#define XBAR_CLR12_CLB4_OUT0   0x40000U      // Input Flag clear for CLB4_OUT0 Signal
#define XBAR_CLR12_CLB4_OUT1   0x80000U      // Input Flag clear for CLB4_OUT1 Signal
#define XBAR_CLR12_CLB4_OUT2   0x100000U     // Input Flag clear for CLB4_OUT2 Signal
#define XBAR_CLR12_CLB4_OUT3   0x200000U     // Input Flag clear for CLB4_OUT3 Signal
#define XBAR_CLR12_CLB4_OUT6   0x400000U     // Input Flag clear for CLB4_OUT6 Signal
#define XBAR_CLR12_CLB4_OUT7   0x800000U     // Input Flag clear for CLB4_OUT7 Signal
#define XBAR_CLR12_CLB5_OUT0   0x1000000U    // Input Flag clear for CLB5_OUT0 Signal
#define XBAR_CLR12_CLB5_OUT1   0x2000000U    // Input Flag clear for CLB5_OUT1 Signal
#define XBAR_CLR12_CLB5_OUT2   0x4000000U    // Input Flag clear for CLB5_OUT2 Signal
#define XBAR_CLR12_CLB5_OUT3   0x8000000U    // Input Flag clear for CLB5_OUT3 Signal
#define XBAR_CLR12_CLB5_OUT6   0x10000000U   // Input Flag clear for CLB5_OUT6 Signal
#define XBAR_CLR12_CLB5_OUT7   0x20000000U   // Input Flag clear for CLB5_OUT7 Signal
#define XBAR_CLR12_CLB6_OUT0   0x40000000U   // Input Flag clear for CLB6_OUT0 Signal
#define XBAR_CLR12_CLB6_OUT1   0x80000000U   // Input Flag clear for CLB6_OUT1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR13 register
//
//*************************************************************************************************
#define XBAR_CLR13_CLB6_OUT2         0x1U          // Input Flag clear for CLB6_OUT2 Signal
#define XBAR_CLR13_CLB6_OUT3         0x2U          // Input Flag clear for CLB6_OUT3 Signal
#define XBAR_CLR13_CLB6_OUT6         0x4U          // Input Flag clear for CLB6_OUT6 Signal
#define XBAR_CLR13_CLB6_OUT7         0x8U          // Input Flag clear for CLB6_OUT7 Signal
#define XBAR_CLR13_XTRIPOUT1         0x10U         // Input Flag clear for XTRIPOUT1 Signal
#define XBAR_CLR13_XTRIPOUT2         0x20U         // Input Flag clear for XTRIPOUT2 Signal
#define XBAR_CLR13_XTRIPOUT3         0x40U         // Input Flag clear for XTRIPOUT3 Signal
#define XBAR_CLR13_XTRIPOUT4         0x80U         // Input Flag clear for XTRIPOUT4 Signal
#define XBAR_CLR13_XTRIPOUT5         0x100U        // Input Flag clear for XTRIPOUT5 Signal
#define XBAR_CLR13_XTRIPOUT6         0x200U        // Input Flag clear for XTRIPOUT6 Signal
#define XBAR_CLR13_XTRIPOUT7         0x400U        // Input Flag clear for XTRIPOUT7 Signal
#define XBAR_CLR13_XTRIPOUT8         0x800U        // Input Flag clear for XTRIPOUT8 Signal
#define XBAR_CLR13_ADCA_EXTMUXSEL0   0x1000U       // Input Flag clear for ADCA_EXTMUXSEL0 Signal
#define XBAR_CLR13_ADCA_EXTMUXSEL1   0x2000U       // Input Flag clear for ADCA_EXTMUXSEL1 Signal
#define XBAR_CLR13_ADCA_EXTMUXSEL2   0x4000U       // Input Flag clear for ADCA_EXTMUXSEL2 Signal
#define XBAR_CLR13_ADCA_EXTMUXSEL3   0x8000U       // Input Flag clear for ADCA_EXTMUXSEL3 Signal
#define XBAR_CLR13_ADCB_EXTMUXSEL0   0x10000U      // Input Flag clear for ADCB_EXTMUXSEL0 Signal
#define XBAR_CLR13_ADCB_EXTMUXSEL1   0x20000U      // Input Flag clear for ADCB_EXTMUXSEL1 Signal
#define XBAR_CLR13_ADCB_EXTMUXSEL2   0x40000U      // Input Flag clear for ADCB_EXTMUXSEL2 Signal
#define XBAR_CLR13_ADCB_EXTMUXSEL3   0x80000U      // Input Flag clear for ADCB_EXTMUXSEL3 Signal
#define XBAR_CLR13_ADCC_EXTMUXSEL0   0x100000U     // Input Flag clear for ADCC_EXTMUXSEL0 Signal
#define XBAR_CLR13_ADCC_EXTMUXSEL1   0x200000U     // Input Flag clear for ADCC_EXTMUXSEL1 Signal
#define XBAR_CLR13_ADCC_EXTMUXSEL2   0x400000U     // Input Flag clear for ADCC_EXTMUXSEL2 Signal
#define XBAR_CLR13_ADCC_EXTMUXSEL3   0x800000U     // Input Flag clear for ADCC_EXTMUXSEL3 Signal
#define XBAR_CLR13_PIEERR            0x4000000U    // Input Flag clear for PIEERR Signal
#define XBAR_CLR13_ECCERR            0x8000000U    // Input Flag clear for ECCERR Signal
#define XBAR_CLR13_EPG1_EPGOUT0      0x10000000U   // Input Flag clear for EPG1_EPGOUT0 Signal
#define XBAR_CLR13_EPG1_EPGOUT1      0x20000000U   // Input Flag clear for EPG1_EPGOUT1 Signal
#define XBAR_CLR13_EPG1_EPGOUT2      0x40000000U   // Input Flag clear for EPG1_EPGOUT2 Signal
#define XBAR_CLR13_EPG1_EPGOUT3      0x80000000U   // Input Flag clear for EPG1_EPGOUT3 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR14 register
//
//*************************************************************************************************
#define XBAR_CLR14_SD3FLT1_COMPH        0x1U          // Input Flag clear for SD3FLT1_COMPH Signal
#define XBAR_CLR14_SD3FLT1_COMPL        0x2U          // Input Flag clear for SD3FLT1_COMPL Signal
#define XBAR_CLR14_SD3FLT2_COMPH        0x4U          // Input Flag clear for SD3FLT2_COMPH Signal
#define XBAR_CLR14_SD3FLT2_COMPL        0x8U          // Input Flag clear for SD3FLT2_COMPL Signal
#define XBAR_CLR14_SD3FLT3_COMPH        0x10U         // Input Flag clear for SD3FLT3_COMPH Signal
#define XBAR_CLR14_SD3FLT3_COMPL        0x20U         // Input Flag clear for SD3FLT3_COMPL Signal
#define XBAR_CLR14_SD3FLT4_COMPH        0x40U         // Input Flag clear for SD3FLT4_COMPH Signal
#define XBAR_CLR14_SD3FLT4_COMPL        0x80U         // Input Flag clear for SD3FLT4_COMPL Signal
#define XBAR_CLR14_SD4FLT1_COMPH        0x100U        // Input Flag clear for SD4FLT1_COMPH Signal
#define XBAR_CLR14_SD4FLT1_COMPL        0x200U        // Input Flag clear for SD4FLT1_COMPL Signal
#define XBAR_CLR14_SD4FLT2_COMPH        0x400U        // Input Flag clear for SD4FLT2_COMPH Signal
#define XBAR_CLR14_SD4FLT2_COMPL        0x800U        // Input Flag clear for SD4FLT2_COMPL Signal
#define XBAR_CLR14_SD4FLT3_COMPH        0x1000U       // Input Flag clear for SD4FLT3_COMPH Signal
#define XBAR_CLR14_SD4FLT3_COMPL        0x2000U       // Input Flag clear for SD4FLT3_COMPL Signal
#define XBAR_CLR14_SD4FLT4_COMPH        0x4000U       // Input Flag clear for SD4FLT4_COMPH Signal
#define XBAR_CLR14_SD4FLT4_COMPL        0x8000U       // Input Flag clear for SD4FLT4_COMPL Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT10   0x20000U      // Input Flag clear for INPUTXBAR2_INPUT10
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT11   0x40000U      // Input Flag clear for INPUTXBAR2_INPUT11
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT12   0x80000U      // Input Flag clear for INPUTXBAR2_INPUT12
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT13   0x100000U     // Input Flag clear for INPUTXBAR2_INPUT13
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT14   0x200000U     // Input Flag clear for INPUTXBAR2_INPUT14
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT7    0x400000U     // Input Flag clear for INPUTXBAR2_INPUT7
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT8    0x800000U     // Input Flag clear for INPUTXBAR2_INPUT8
                                                      // Signal
#define XBAR_CLR14_INPUTXBAR2_INPUT9    0x1000000U    // Input Flag clear for INPUTXBAR2_INPUT9
                                                      // Signal
#define XBAR_CLR14_MCANB_FEVT0          0x2000000U    // Input Flag clear for MCANB_FEVT0 Signal
#define XBAR_CLR14_MCANB_FEVT1          0x4000000U    // Input Flag clear for MCANB_FEVT1 Signal
#define XBAR_CLR14_MCANB_FEVT2          0x8000000U    // Input Flag clear for MCANB_FEVT2 Signal
#define XBAR_CLR14_FSIA_RX_TRIG1        0x10000000U   // Input Flag clear for FSIA_RX_TRIG1 Signal
#define XBAR_CLR14_FSIB_RX_TRIG1        0x20000000U   // Input Flag clear for FSIB_RX_TRIG1 Signal
#define XBAR_CLR14_FSIC_RX_TRIG1        0x40000000U   // Input Flag clear for FSIC_RX_TRIG1 Signal
#define XBAR_CLR14_FSID_RX_TRIG1        0x80000000U   // Input Flag clear for FSID_RX_TRIG1 Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR15 register
//
//*************************************************************************************************
#define XBAR_CLR15_FSIRXA_TRIG_2       0x1U          // Input Flag clear for FSIRXA_TRIG_2 Signal
#define XBAR_CLR15_FSIRXA_TRIG_3       0x2U          // Input Flag clear for FSIRXA_TRIG_3 Signal
#define XBAR_CLR15_FSIRXB_TRIG_2       0x4U          // Input Flag clear for FSIRXB_TRIG_2 Signal
#define XBAR_CLR15_FSIRXB_TRIG_3       0x8U          // Input Flag clear for FSIRXB_TRIG_3 Signal
#define XBAR_CLR15_FSIRXC_TRIG_2       0x10U         // Input Flag clear for FSIRXC_TRIG_2 Signal
#define XBAR_CLR15_FSIRXC_TRIG_3       0x20U         // Input Flag clear for FSIRXC_TRIG_3 Signal
#define XBAR_CLR15_FSIRXD_TRIG_2       0x40U         // Input Flag clear for FSIRXD_TRIG_2 Signal
#define XBAR_CLR15_FSIRXD_TRIG_3       0x80U         // Input Flag clear for FSIRXD_TRIG_3 Signal
#define XBAR_CLR15_ECAP1_TRIPOUT       0x100U        // Input Flag clear for ECAP1_TRIPOUT Signal
#define XBAR_CLR15_ECAP2_TRIPOUT       0x200U        // Input Flag clear for ECAP2_TRIPOUT Signal
#define XBAR_CLR15_ECAP3_TRIPOUT       0x400U        // Input Flag clear for ECAP3_TRIPOUT Signal
#define XBAR_CLR15_ECAP4_TRIPOUT       0x800U        // Input Flag clear for ECAP4_TRIPOUT Signal
#define XBAR_CLR15_ECAP5_TRIPOUT       0x1000U       // Input Flag clear for ECAP5_TRIPOUT Signal
#define XBAR_CLR15_ECAP6_TRIPOUT       0x2000U       // Input Flag clear for ECAP6_TRIPOUT Signal
#define XBAR_CLR15_CPU1ERADEVT10       0x4000U       // Input Flag clear for CPU1ERADEVT10 Signal
#define XBAR_CLR15_CPU1ERADEVT11       0x8000U       // Input Flag clear for CPU1ERADEVT11 Signal
#define XBAR_CLR15_CPU1ERADEVT8        0x10000U      // Input Flag clear for CPU1ERADEVT8 Signal
#define XBAR_CLR15_CPU1ERADEVT9        0x20000U      // Input Flag clear for CPU1ERADEVT9 Signal
#define XBAR_CLR15_CPU1_ADCCHECKEVT1   0x40000U      // Input Flag clear for CPU1_ADCCHECKEVT1
                                                     // Signal
#define XBAR_CLR15_CPU1_ADCCHECKEVT2   0x80000U      // Input Flag clear for CPU1_ADCCHECKEVT2
                                                     // Signal
#define XBAR_CLR15_CPU1_ADCCHECKEVT3   0x100000U     // Input Flag clear for CPU1_ADCCHECKEVT3
                                                     // Signal
#define XBAR_CLR15_CPU1_ADCCHECKEVT4   0x200000U     // Input Flag clear for CPU1_ADCCHECKEVT4
                                                     // Signal
#define XBAR_CLR15_CPU2ERADEVT10       0x400000U     // Input Flag clear for CPU2ERADEVT10 Signal
#define XBAR_CLR15_CPU2ERADEVT11       0x800000U     // Input Flag clear for CPU2ERADEVT11 Signal
#define XBAR_CLR15_CPU2ERADEVT8        0x1000000U    // Input Flag clear for CPU2ERADEVT8 Signal
#define XBAR_CLR15_CPU2ERADEVT9        0x2000000U    // Input Flag clear for CPU2ERADEVT9 Signal
#define XBAR_CLR15_CPU2_ADCCHECKEVT1   0x4000000U    // Input Flag clear for CPU2_ADCCHECKEVT1
                                                     // Signal
#define XBAR_CLR15_CPU2_ADCCHECKEVT2   0x8000000U    // Input Flag clear for CPU2_ADCCHECKEVT2
                                                     // Signal
#define XBAR_CLR15_CPU2_ADCCHECKEVT3   0x10000000U   // Input Flag clear for CPU2_ADCCHECKEVT3
                                                     // Signal
#define XBAR_CLR15_CPU2_ADCCHECKEVT4   0x20000000U   // Input Flag clear for CPU2_ADCCHECKEVT4
                                                     // Signal

//*************************************************************************************************
//
// The following are defines for the bit fields in the XBARCLR16 register
//
//*************************************************************************************************
#define XBAR_CLR16_CMPSS9_CTRIPH       0x1U          // Input Flag clear for CMPSS9_CTRIPH Signal
#define XBAR_CLR16_CMPSS9_CTRIPL       0x2U          // Input Flag clear for CMPSS9_CTRIPL Signal
#define XBAR_CLR16_CMPSS9_CTRIPOUTH    0x4U          // Input Flag clear for CMPSS9_CTRIPOUTH
                                                     // Signal
#define XBAR_CLR16_CMPSS9_CTRIPOUTL    0x8U          // Input Flag clear for CMPSS9_CTRIPOUTL
                                                     // Signal
#define XBAR_CLR16_CMPSS10_CTRIPH      0x10U         // Input Flag clear for CMPSS10_CTRIPH Signal
#define XBAR_CLR16_CMPSS10_CTRIPL      0x20U         // Input Flag clear for CMPSS10_CTRIPL Signal
#define XBAR_CLR16_CMPSS10_CTRIPOUTH   0x40U         // Input Flag clear for CMPSS10_CTRIPOUTH
                                                     // Signal
#define XBAR_CLR16_CMPSS10_CTRIPOUTL   0x80U         // Input Flag clear for CMPSS10_CTRIPOUTL
                                                     // Signal
#define XBAR_CLR16_CMPSS11_CTRIPH      0x100U        // Input Flag clear for CMPSS11_CTRIPH Signal
#define XBAR_CLR16_CMPSS11_CTRIPL      0x200U        // Input Flag clear for CMPSS11_CTRIPL Signal
#define XBAR_CLR16_CMPSS11_CTRIPOUTH   0x400U        // Input Flag clear for CMPSS11_CTRIPOUTH
                                                     // Signal
#define XBAR_CLR16_CMPSS11_CTRIPOUTL   0x800U        // Input Flag clear for CMPSS11_CTRIPOUTL
                                                     // Signal
#define XBAR_CLR16_CMPSS12_CTRIPH      0x1000U       // Input Flag clear for CMPSS12_CTRIPH Signal
#define XBAR_CLR16_CMPSS12_CTRIPL      0x2000U       // Input Flag clear for CMPSS12_CTRIPL Signal
#define XBAR_CLR16_CMPSS12_CTRIPOUTH   0x4000U       // Input Flag clear for CMPSS12_CTRIPOUTH
                                                     // Signal
#define XBAR_CLR16_CMPSS12_CTRIPOUTL   0x8000U       // Input Flag clear for CMPSS12_CTRIPOUTL
                                                     // Signal
#define XBAR_CLR16_CLB5_4_1            0x8000000U    // Input Flag clear for CLB5_4_1  Signal
#define XBAR_CLR16_CLB5_5_1            0x10000000U   // Input Flag clear for CLB5_5_1 Signal
#define XBAR_CLR16_CLB6_4_1            0x20000000U   // Input Flag clear for CLB6_4_1 Signal
#define XBAR_CLR16_CLB6_5_1            0x40000000U   // Input Flag clear for CLB6_5_1 Signal
#define XBAR_CLR16_XCLKOUT             0x80000000U   // Input Flag clear for XCLKOUT Signal



#endif
