//###########################################################################
//
// FILE:    hw_xbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#define XBAR_O_FLG1   0x0U   // X-Bar Input Flag Register 1
#define XBAR_O_FLG2   0x2U   // X-Bar Input Flag Register 2
#define XBAR_O_FLG3   0x4U   // X-Bar Input Flag Register 3
#define XBAR_O_CLR1   0x8U   // X-Bar Input Flag Clear Register 1
#define XBAR_O_CLR2   0xAU   // X-Bar Input Flag Clear Register 2
#define XBAR_O_CLR3   0xCU   // X-Bar Input Flag Clear Register 3


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
#define XBAR_FLG2_ADCSOCAO     0x40U         // Input Flag for ADCSOCAO Signal
#define XBAR_FLG2_ADCSOCBO     0x80U         // Input Flag for ADCSOCBO Signal
#define XBAR_FLG2_CLB1_OUT4    0x100U        // Input Flag for CLB1_OUT4 Signal
#define XBAR_FLG2_CLB1_OUT5    0x200U        // Input Flag for CLB1_OUT5 Signal
#define XBAR_FLG2_CLB2_OUT4    0x400U        // Input Flag for CLB2_OUT4 Signal
#define XBAR_FLG2_CLB2_OUT5    0x800U        // Input Flag for CLB2_OUT5 Signal
#define XBAR_FLG2_CLB3_OUT4    0x1000U       // Input Flag for CLB3_OUT4 Signal
#define XBAR_FLG2_CLB3_OUT5    0x2000U       // Input Flag for CLB3_OUT5 Signal
#define XBAR_FLG2_CLB4_OUT4    0x4000U       // Input Flag for CLB4_OUT4 Signal
#define XBAR_FLG2_CLB4_OUT5    0x8000U       // Input Flag for CLB4_OUT5 Signal
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
#define XBAR_FLG3_ADCDEVT1        0x8U        // Input Flag for ADCDEVT1 Signal
#define XBAR_FLG3_ADCDEVT2        0x10U       // Input Flag for ADCDEVT2 Signal
#define XBAR_FLG3_ADCDEVT3        0x20U       // Input Flag for ADCDEVT3 Signal
#define XBAR_FLG3_ADCDEVT4        0x40U       // Input Flag for ADCDEVT4 Signal
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
#define XBAR_CLR2_INPUT7       0x20U         // Input Flag Clear for INPUT7 Signal
#define XBAR_CLR2_ADCSOCAO     0x40U         // Input Flag Clear for ADCSOCAO Signal
#define XBAR_CLR2_ADCSOCBO     0x80U         // Input Flag Clear for ADCSOCBO Signal
#define XBAR_CLR2_CLB1_OUT4    0x100U        // Input Flag Clear for CLB1_OUT4 Signal
#define XBAR_CLR2_CLB1_OUT5    0x200U        // Input Flag Clear for CLB1_OUT5 Signal
#define XBAR_CLR2_CLB2_OUT4    0x400U        // Input Flag Clear for CLB2_OUT4 Signal
#define XBAR_CLR2_CLB2_OUT5    0x800U        // Input Flag Clear for CLB2_OUT5 Signal
#define XBAR_CLR2_CLB3_OUT4    0x1000U       // Input Flag Clear for CLB3_OUT4 Signal
#define XBAR_CLR2_CLB3_OUT5    0x2000U       // Input Flag Clear for CLB3_OUT5 Signal
#define XBAR_CLR2_CLB4_OUT4    0x4000U       // Input Flag Clear for CLB4_OUT4 Signal
#define XBAR_CLR2_CLB4_OUT5    0x8000U       // Input Flag Clear for CLB4_OUT5 Signal
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
#define XBAR_CLR3_ADCDEVT1        0x8U        // Input Flag Clear for ADCDEVT1 Signal
#define XBAR_CLR3_ADCDEVT2        0x10U       // Input Flag Clear for ADCDEVT2 Signal
#define XBAR_CLR3_ADCDEVT3        0x20U       // Input Flag Clear for ADCDEVT3 Signal
#define XBAR_CLR3_ADCDEVT4        0x40U       // Input Flag Clear for ADCDEVT4 Signal
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



#endif
