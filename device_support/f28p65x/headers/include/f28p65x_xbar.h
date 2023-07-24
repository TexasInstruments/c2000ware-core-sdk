//###########################################################################
//
// FILE:    f28p65x_xbar.h
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

#ifndef F28P65X_XBAR_H
#define F28P65X_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// XBAR Individual Register Bit Definitions:

struct XBARFLG1_BITS {                  // bits description
    Uint16 CMPSS1_CTRIPL:1;             // 0 Input Flag for CMPSS1.CTRIPL Signal
    Uint16 CMPSS1_CTRIPH:1;             // 1 Input Flag for CMPSS1.CTRIPH Signal
    Uint16 CMPSS2_CTRIPL:1;             // 2 Input Flag for CMPSS2.CTRIPL Signal
    Uint16 CMPSS2_CTRIPH:1;             // 3 Input Flag for CMPSS2.CTRIPH Signal
    Uint16 CMPSS3_CTRIPL:1;             // 4 Input Flag for CMPSS3.CTRIPL Signal
    Uint16 CMPSS3_CTRIPH:1;             // 5 Input Flag for CMPSS3.CTRIPH Signal
    Uint16 CMPSS4_CTRIPL:1;             // 6 Input Flag for CMPSS4.CTRIPL Signal
    Uint16 CMPSS4_CTRIPH:1;             // 7 Input Flag for CMPSS4.CTRIPH Signal
    Uint16 CMPSS5_CTRIPL:1;             // 8 Input Flag for CMPSS5.CTRIPL Signal
    Uint16 CMPSS5_CTRIPH:1;             // 9 Input Flag for CMPSS5.CTRIPH Signal
    Uint16 CMPSS6_CTRIPL:1;             // 10 Input Flag for CMPSS6.CTRIPL Signal
    Uint16 CMPSS6_CTRIPH:1;             // 11 Input Flag for CMPSS6.CTRIPH Signal
    Uint16 CMPSS7_CTRIPL:1;             // 12 Input Flag for CMPSS7.CTRIPL Signal
    Uint16 CMPSS7_CTRIPH:1;             // 13 Input Flag for CMPSS7.CTRIPH Signal
    Uint16 CMPSS8_CTRIPL:1;             // 14 Input Flag for CMPSS8.CTRIPL Signal
    Uint16 CMPSS8_CTRIPH:1;             // 15 Input Flag for CMPSS8.CTRIPH Signal
    Uint16 CMPSS1_CTRIPOUTL:1;          // 16 Input Flag for CMPSS1.CTRIPOUTL Signal
    Uint16 CMPSS1_CTRIPOUTH:1;          // 17 Input Flag for CMPSS1.CTRIPOUTH Signal
    Uint16 CMPSS2_CTRIPOUTL:1;          // 18 Input Flag for CMPSS2.CTRIPOUTL Signal
    Uint16 CMPSS2_CTRIPOUTH:1;          // 19 Input Flag for CMPSS2.CTRIPOUTH Signal
    Uint16 CMPSS3_CTRIPOUTL:1;          // 20 Input Flag for CMPSS3.CTRIPOUTL Signal
    Uint16 CMPSS3_CTRIPOUTH:1;          // 21 Input Flag for CMPSS3.CTRIPOUTH Signal
    Uint16 CMPSS4_CTRIPOUTL:1;          // 22 Input Flag for CMPSS4.CTRIPOUTL Signal
    Uint16 CMPSS4_CTRIPOUTH:1;          // 23 Input Flag for CMPSS4.CTRIPOUTH Signal
    Uint16 CMPSS5_CTRIPOUTL:1;          // 24 Input Flag for CMPSS5.CTRIPOUTL Signal
    Uint16 CMPSS5_CTRIPOUTH:1;          // 25 Input Flag for CMPSS5.CTRIPOUTH Signal
    Uint16 CMPSS6_CTRIPOUTL:1;          // 26 Input Flag for CMPSS6.CTRIPOUTL Signal
    Uint16 CMPSS6_CTRIPOUTH:1;          // 27 Input Flag for CMPSS6.CTRIPOUTH Signal
    Uint16 CMPSS7_CTRIPOUTL:1;          // 28 Input Flag for CMPSS7.CTRIPOUTL Signal
    Uint16 CMPSS7_CTRIPOUTH:1;          // 29 Input Flag for CMPSS7.CTRIPOUTH Signal
    Uint16 CMPSS8_CTRIPOUTL:1;          // 30 Input Flag for CMPSS8.CTRIPOUTL Signal
    Uint16 CMPSS8_CTRIPOUTH:1;          // 31 Input Flag for CMPSS8.CTRIPOUTH Signal
};

union XBARFLG1_REG {
    Uint32  all;
    struct  XBARFLG1_BITS  bit;
};

struct XBARFLG2_BITS {                  // bits description
    Uint16 INPUT1:1;                    // 0 Input Flag for INPUT1 Signal
    Uint16 INPUT2:1;                    // 1 Input Flag for INPUT2 Signal
    Uint16 INPUT3:1;                    // 2 Input Flag for INPUT3 Signal
    Uint16 INPUT4:1;                    // 3 Input Flag for INPUT4 Signal
    Uint16 INPUT5:1;                    // 4 Input Flag for INPUT5 Signal
    Uint16 INPUT6:1;                    // 5 Input Flag for INPUT6 Signal
    Uint16 ADCSOCA:1;                   // 6 Input Flag for ADCSOCA Signal
    Uint16 ADCSOCB:1;                   // 7 Input Flag for ADCSOCB Signal
    Uint16 INPUT7:1;                    // 8 Input Flag for INPUT7 Signal
    Uint16 INPUT8:1;                    // 9 Input Flag for INPUT8 Signal
    Uint16 INPUT9:1;                    // 10 Input Flag for INPUT9 Signal
    Uint16 INPUT10:1;                   // 11 Input Flag for INPUT10\ Signal
    Uint16 INPUT11:1;                   // 12 Input Flag for INPUT11 Signal
    Uint16 INPUT12:1;                   // 13 Input Flag for INPUT12 Signal
    Uint16 INPUT13:1;                   // 14 Input Flag for INPUT13 Signal
    Uint16 INPUT14:1;                   // 15 Input Flag for INPUT14 Signal
    Uint16 ECAP1_OUT:1;                 // 16 Input Flag for ECAP1.OUT Signal
    Uint16 ECAP2_OUT:1;                 // 17 Input Flag for ECAP2.OUT Signal
    Uint16 ECAP3_OUT:1;                 // 18 Input Flag for ECAP3.OUT Signal
    Uint16 ECAP4_OUT:1;                 // 19 Input Flag for ECAP4.OUT Signal
    Uint16 ECAP5_OUT:1;                 // 20 Input Flag for ECAP5.OUT Signal
    Uint16 ECAP6_OUT:1;                 // 21 Input Flag for ECAP6.OUT Signal
    Uint16 EXTSYNCOUT:1;                // 22 Input Flag for EXTSYNCOUT Signal
    Uint16 ADCAEVT1:1;                  // 23 Input Flag for ADCAEVT1 Signal
    Uint16 ADCAEVT2:1;                  // 24 Input Flag for ADCAEVT2 Signal
    Uint16 ADCAEVT3:1;                  // 25 Input Flag for ADCAEVT3 Signal
    Uint16 ADCAEVT4:1;                  // 26 Input Flag for ADCAEVT4 Signal
    Uint16 ADCBEVT1:1;                  // 27 Input Flag for ADCBEVT1 Signal
    Uint16 ADCBEVT2:1;                  // 28 Input Flag for ADCBEVT2 Signal
    Uint16 ADCBEVT3:1;                  // 29 Input Flag for ADCBEVT3 Signal
    Uint16 ADCBEVT4:1;                  // 30 Input Flag for ADCBEVT4 Signal
    Uint16 ADCCEVT1:1;                  // 31 Input Flag for ADCCEVT1 Signal
};

union XBARFLG2_REG {
    Uint32  all;
    struct  XBARFLG2_BITS  bit;
};

struct XBARFLG3_BITS {                  // bits description
    Uint16 ADCCEVT2:1;                  // 0 Input Flag for ADCCEVT2 Signal
    Uint16 ADCCEVT3:1;                  // 1 Input Flag for ADCCEVT3 Signal
    Uint16 ADCCEVT4:1;                  // 2 Input Flag for ADCCEVT4 Signal
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:1;                     // 6 Reserved
    Uint16 SD1FLT1_COMPL:1;             // 7 Input Flag for SD1FLT1.COMPL Signal
    Uint16 SD1FLT1_COMPH:1;             // 8 Input Flag for SD1FLT1.COMPH Signal
    Uint16 SD1FLT2_COMPL:1;             // 9 Input Flag for SD1FLT2.COMPL Signal
    Uint16 SD1FLT2_COMPH:1;             // 10 Input Flag for SD1FLT2.COMPH Signal
    Uint16 SD1FLT3_COMPL:1;             // 11 Input Flag for SD1FLT3.COMPL Signal
    Uint16 SD1FLT3_COMPH:1;             // 12 Input Flag for SD1FLT3.COMPH Signal
    Uint16 SD1FLT4_COMPL:1;             // 13 Input Flag for SD1FLT4.COMPL Signal
    Uint16 SD1FLT4_COMPH:1;             // 14 Input Flag for SD1FLT4.COMPH Signal
    Uint16 SD2FLT1_COMPL:1;             // 15 Input Flag for SD2FLT1.COMPL Signal
    Uint16 SD2FLT1_COMPH:1;             // 16 Input Flag for SD2FLT1.COMPH Signal
    Uint16 SD2FLT2_COMPL:1;             // 17 Input Flag for SD2FLT2.COMPL Signal
    Uint16 SD2FLT2_COMPH:1;             // 18 Input Flag for SD2FLT2.COMPH Signal
    Uint16 SD2FLT3_COMPL:1;             // 19 Input Flag for SD2FLT3.COMPL Signal
    Uint16 SD2FLT3_COMPH:1;             // 20 Input Flag for SD2FLT3.COMPH Signal
    Uint16 SD2FLT4_COMPL:1;             // 21 Input Flag for SD2FLT4.COMPL Signal
    Uint16 SD2FLT4_COMPH:1;             // 22 Input Flag for SD2FLT4.COMPH Signal
    Uint16 ECAP7_OUT:1;                 // 23 Input Flag for ECAP7.OUT Signal
    Uint16 rsvd5:1;                     // 24 Reserved
    Uint16 rsvd6:1;                     // 25 Reserved
    Uint16 rsvd7:1;                     // 26 Reserved
    Uint16 rsvd8:1;                     // 27 Reserved
    Uint16 rsvd9:1;                     // 28 Reserved
    Uint16 rsvd10:1;                    // 29 Reserved
    Uint16 rsvd11:1;                    // 30 Reserved
    Uint16 rsvd12:1;                    // 31 Reserved
};

union XBARFLG3_REG {
    Uint32  all;
    struct  XBARFLG3_BITS  bit;
};

struct XBARFLG4_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 rsvd7:1;                     // 6 Reserved
    Uint16 rsvd8:1;                     // 7 Reserved
    Uint16 rsvd9:1;                     // 8 Reserved
    Uint16 MCANA_FEVT0:1;               // 9 Input Flag for MCANA_FEVT0 Signal
    Uint16 MCANA_FEVT1:1;               // 10 Input Flag for MCANA_FEVT1 Signal
    Uint16 MCANA_FEVT2:1;               // 11 Input Flag for MCANA_FEVT2 Signal
    Uint16 rsvd10:1;                    // 12 Reserved
    Uint16 rsvd11:1;                    // 13 Reserved
    Uint16 rsvd12:1;                    // 14 Reserved
    Uint16 rsvd13:1;                    // 15 Reserved
    Uint16 CLB1_OUT4:1;                 // 16 Input Flag for CLB1_4.1 Signal
    Uint16 CLB1_OUT5:1;                 // 17 Input Flag for CLB1_5.1 Signal
    Uint16 CLB2_OUT4:1;                 // 18 Input Flag for CLB2_4.1 Signal
    Uint16 CLB2_OUT5:1;                 // 19 Input Flag for CLB2_5.1 Signal
    Uint16 CLB3_OUT4:1;                 // 20 Input Flag for CLB3_4.1 Signal
    Uint16 CLB3_OUT5:1;                 // 21 Input Flag for CLB3_5.1 Signal
    Uint16 CLB4_OUT4:1;                 // 22 Input Flag for CLB4_4.1 Signal
    Uint16 CLB4_OUT5:1;                 // 23 Input Flag for CLB4_5.1 Signal
    Uint16 CLB5_OUT4:1;                 // 24 Input Latch for CLB5_OUT4 Signal
    Uint16 CLB5_OUT5:1;                 // 25 Input Latch for CLB5_OUT5 Signal
    Uint16 CLB6_OUT4:1;                 // 26 Input Latch for CLB6_OUT4 Signal
    Uint16 CLB6_OUT5:1;                 // 27 Input Latch for CLB6_OUT5 Signal
    Uint16 ERRORSTS_ERROR:1;            // 28 Input Latch for ERRORSTS_ERROR Signal
    Uint16 ECATSYNC0:1;                 // 29 Input Latch for ECATSYNC0 Signal
    Uint16 ECATSYNC1:1;                 // 30 Input Latch for ECATSYNC1 Signal
    Uint16 CLAHALT:1;                   // 31 Input Latch for CLAHALT Signal
};

union XBARFLG4_REG {
    Uint32  all;
    struct  XBARFLG4_BITS  bit;
};

struct XBARFLG5_BITS {                  // bits description
    Uint16 EPWM1_TRIPOUT:1;             // 0 Input Flag for EPWM1_TRIPOUT Signal
    Uint16 EPWM2_TRIPOUT:1;             // 1 Input Flag for EPWM2_TRIPOUT Signal
    Uint16 EPWM3_TRIPOUT:1;             // 2 Input Flag for EPWM3_TRIPOUT Signal
    Uint16 EPWM4_TRIPOUT:1;             // 3 Input Flag for EPWM4_TRIPOUT Signal
    Uint16 EPWM5_TRIPOUT:1;             // 4 Input Flag for EPWM5_TRIPOUT Signal
    Uint16 EPWM6_TRIPOUT:1;             // 5 Input Flag for EPWM6_TRIPOUT Signal
    Uint16 EPWM7_TRIPOUT:1;             // 6 Input Flag for EPWM7_TRIPOUT Signal
    Uint16 EPWM8_TRIPOUT:1;             // 7 Input Flag for EPWM8_TRIPOUT Signal
    Uint16 EPWM9_TRIPOUT:1;             // 8 Input Flag for EPWM9_TRIPOUT Signal
    Uint16 EPWM10_TRIPOUT:1;            // 9 Input Flag for EPWM10_TRIPOUT Signal
    Uint16 EPWM11_TRIPOUT:1;            // 10 Input Flag for EPWM11_TRIPOUT Signal
    Uint16 EPWM12_TRIPOUT:1;            // 11 Input Flag for EPWM12_TRIPOUT Signal
    Uint16 EPWM13_TRIPOUT:1;            // 12 Input Flag for EPWM13_TRIPOUT Signal
    Uint16 EPWM14_TRIPOUT:1;            // 13 Input Flag for EPWM14_TRIPOUT Signal
    Uint16 EPWM15_TRIPOUT:1;            // 14 Input Flag for EPWM15_TRIPOUT Signal
    Uint16 EPWM16_TRIPOUT:1;            // 15 Input Flag for EPWM16_TRIPOUT Signal
    Uint16 EPWM17_TRIPOUT:1;            // 16 Input Flag for EPWM17_TRIPOUT Signal
    Uint16 EPWM18_TRIPOUT:1;            // 17 Input Flag for EPWM18_TRIPOUT Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARFLG5_REG {
    Uint32  all;
    struct  XBARFLG5_BITS  bit;
};

struct XBARFLG6_BITS {                  // bits description
    Uint16 EPWM1_DEL_TRIP:1;            // 0 Input Flag for EPWM1_DEL_TRIP Signal
    Uint16 EPWM2_DEL_TRIP:1;            // 1 Input Flag for EPWM2_DEL_TRIP Signal
    Uint16 EPWM3_DEL_TRIP:1;            // 2 Input Flag for EPWM3_DEL_TRIP Signal
    Uint16 EPWM4_DEL_TRIP:1;            // 3 Input Flag for EPWM4_DEL_TRIP Signal
    Uint16 EPWM5_DEL_TRIP:1;            // 4 Input Flag for EPWM5_DEL_TRIP Signal
    Uint16 EPWM6_DEL_TRIP:1;            // 5 Input Flag for EPWM6_DEL_TRIP Signal
    Uint16 EPWM7_DEL_TRIP:1;            // 6 Input Flag for EPWM7_DEL_TRIP Signal
    Uint16 EPWM8_DEL_TRIP:1;            // 7 Input Flag for EPWM8_DEL_TRIP Signal
    Uint16 EPWM9_DEL_TRIP:1;            // 8 Input Flag for EPWM9_DEL_TRIP Signal
    Uint16 EPWM10_DEL_TRIP:1;           // 9 Input Flag for EPWM10_DEL_TRIP Signal
    Uint16 EPWM11_DEL_TRIP:1;           // 10 Input Flag for EPWM11_DEL_TRIP Signal
    Uint16 EPWM12_DEL_TRIP:1;           // 11 Input Flag for EPWM12_DEL_TRIP Signal
    Uint16 EPWM13_DEL_TRIP:1;           // 12 Input Flag for EPWM13_DEL_TRIP Signal
    Uint16 EPWM14_DEL_TRIP:1;           // 13 Input Flag for EPWM14_DEL_TRIP Signal
    Uint16 EPWM15_DEL_TRIP:1;           // 14 Input Flag for EPWM15_DEL_TRIP Signal
    Uint16 EPWM16_DEL_TRIP:1;           // 15 Input Flag for EPWM16_DEL_TRIP Signal
    Uint16 EPWM17_DEL_TRIP:1;           // 16 Input Flag for EPWM17_DEL_TRIP Signal
    Uint16 EPWM18_DEL_TRIP:1;           // 17 Input Flag for EPWM18_DEL_TRIP Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARFLG6_REG {
    Uint32  all;
    struct  XBARFLG6_BITS  bit;
};

struct XBARFLG7_BITS {                  // bits description
    Uint16 EPWM1_DEL_ACTIVE:1;          // 0 Input Flag for EPWM1_DEL_ACTIVE Signal
    Uint16 EPWM2_DEL_ACTIVE:1;          // 1 Input Flag for EPWM2_DEL_ACTIVE Signal
    Uint16 EPWM3_DEL_ACTIVE:1;          // 2 Input Flag for EPWM3_DEL_ACTIVE Signal
    Uint16 EPWM4_DEL_ACTIVE:1;          // 3 Input Flag for EPWM4_DEL_ACTIVE Signal
    Uint16 EPWM5_DEL_ACTIVE:1;          // 4 Input Flag for EPWM5_DEL_ACTIVE Signal
    Uint16 EPWM6_DEL_ACTIVE:1;          // 5 Input Flag for EPWM6_DEL_ACTIVE Signal
    Uint16 EPWM7_DEL_ACTIVE:1;          // 6 Input Flag for EPWM7_DEL_ACTIVE Signal
    Uint16 EPWM8_DEL_ACTIVE:1;          // 7 Input Flag for EPWM8_DEL_ACTIVE Signal
    Uint16 EPWM9_DEL_ACTIVE:1;          // 8 Input Flag for EPWM9_DEL_ACTIVE Signal
    Uint16 EPWM10_DEL_ACTIVE:1;         // 9 Input Flag for EPWM10_DEL_ACTIVE Signal
    Uint16 EPWM11_DEL_ACTIVE:1;         // 10 Input Flag for EPWM11_DEL_ACTIVE Signal
    Uint16 EPWM12_DEL_ACTIVE:1;         // 11 Input Flag for EPWM12_DEL_ACTIVE Signal
    Uint16 EPWM13_DEL_ACTIVE:1;         // 12 Input Flag for EPWM13_DEL_ACTIVE Signal
    Uint16 EPWM14_DEL_ACTIVE:1;         // 13 Input Flag for EPWM14_DEL_ACTIVE Signal
    Uint16 EPWM15_DEL_ACTIVE:1;         // 14 Input Flag for EPWM15_DEL_ACTIVE Signal
    Uint16 EPWM16_DEL_ACTIVE:1;         // 15 Input Flag for EPWM16_DEL_ACTIVE Signal
    Uint16 EPWM17_DEL_ACTIVE:1;         // 16 Input Flag for EPWM17_DEL_ACTIVE Signal
    Uint16 EPWM18_DEL_ACTIVE:1;         // 17 Input Flag for EPWM18_DEL_ACTIVE Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARFLG7_REG {
    Uint32  all;
    struct  XBARFLG7_BITS  bit;
};

struct XBARFLG8_BITS {                  // bits description
    Uint16 ETPWM1_A0_sclk:1;            // 0 Input Flag for ETPWM1_A0_sclk Signal
    Uint16 ETPWM1_B0_sclk:1;            // 1 Input Flag for ETPWM1_B0_sclk Signal
    Uint16 ETPWM2_A0_sclk:1;            // 2 Input Flag for ETPWM2_A0_sclk Signal
    Uint16 ETPWM2_B0_sclk:1;            // 3 Input Flag for ETPWM2_B0_sclk Signal
    Uint16 ETPWM3_A0_sclk:1;            // 4 Input Flag for ETPWM3_A0_sclk Signal
    Uint16 ETPWM3_B0_sclk:1;            // 5 Input Flag for ETPWM3_B0_sclk Signal
    Uint16 ETPWM4_A0_sclk:1;            // 6 Input Flag for ETPWM4_A0_sclk Signal
    Uint16 ETPWM4_B0_sclk:1;            // 7 Input Flag for ETPWM4_B0_sclk Signal
    Uint16 ETPWM5_A0_sclk:1;            // 8 Input Flag for ETPWM5_A0_sclk Signal
    Uint16 ETPWM5_B0_sclk:1;            // 9 Input Flag for ETPWM5_B0_sclk Signal
    Uint16 ETPWM6_A0_sclk:1;            // 10 Input Flag for ETPWM6_A0_sclk Signal
    Uint16 ETPWM6_B0_sclk:1;            // 11 Input Flag for ETPWM6_B0_sclk Signal
    Uint16 ETPWM7_A0_sclk:1;            // 12 Input Flag for ETPWM7_A0_sclk Signal
    Uint16 ETPWM7_B0_sclk:1;            // 13 Input Flag for ETPWM7_B0_sclk Signal
    Uint16 ETPWM8_A0_sclk:1;            // 14 Input Flag for ETPWM8_A0_sclk Signal
    Uint16 ETPWM8_B0_sclk:1;            // 15 Input Flag for ETPWM8_B0_sclk Signal
    Uint16 ETPWM9_A0_sclk:1;            // 16 Input Flag for ETPWM9_A0_sclk Signal
    Uint16 ETPWM9_B0_sclk:1;            // 17 Input Flag for ETPWM9_B0_sclk Signal
    Uint16 ETPWM10_A0_sclk:1;           // 18 Input Flag for ETPWM10_A0_sclk Signal
    Uint16 ETPWM10_B0_sclk:1;           // 19 Input Flag for ETPWM10_B0_sclk Signal
    Uint16 ETPWM11_A0_sclk:1;           // 20 Input Flag for ETPWM11_A0_sclk Signal
    Uint16 ETPWM11_B0_sclk:1;           // 21 Input Flag for ETPWM11_B0_sclk Signal
    Uint16 ETPWM12_A0_sclk:1;           // 22 Input Flag for ETPWM12_A0_sclk Signal
    Uint16 ETPWM12_B0_sclk:1;           // 23 Input Flag for ETPWM12_B0_sclk Signal
    Uint16 ETPWM13_A0_sclk:1;           // 24 Input Flag for ETPWM13_A0_sclk Signal
    Uint16 ETPWM13_B0_sclk:1;           // 25 Input Flag for ETPWM13_B0_sclk Signal
    Uint16 ETPWM14_A0_sclk:1;           // 26 Input Flag for ETPWM14_A0_sclk Signal
    Uint16 ETPWM14_B0_sclk:1;           // 27 Input Flag for ETPWM14_B0_sclk Signal
    Uint16 ETPWM15_A0_sclk:1;           // 28 Input Flag for ETPWM15_A0_sclk Signal
    Uint16 ETPWM15_B0_sclk:1;           // 29 Input Flag for ETPWM15_B0_sclk Signal
    Uint16 ETPWM16_A0_sclk:1;           // 30 Input Flag for ETPWM16_A0_sclk Signal
    Uint16 ETPWM16_B0_sclk:1;           // 31 Input Flag for ETPWM16_B0_sclk Signal
};

union XBARFLG8_REG {
    Uint32  all;
    struct  XBARFLG8_BITS  bit;
};

struct XBARFLG9_BITS {                  // bits description
    Uint16 ETPWM17_A0_sclk:1;           // 0 Input Flag for ETPWM17_A0_sclk Signal
    Uint16 ETPWM17_B0_sclk:1;           // 1 Input Flag for ETPWM17_B0_sclk Signal
    Uint16 ETPWM18_A0_sclk:1;           // 2 Input Flag for ETPWM18_A0_sclk Signal
    Uint16 ETPWM18_B0_sclk:1;           // 3 Input Flag for ETPWM18_B0_sclk Signal
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:1;                     // 8 Reserved
    Uint16 rsvd6:1;                     // 9 Reserved
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:1;                     // 11 Reserved
    Uint16 rsvd9:1;                     // 12 Reserved
    Uint16 rsvd10:1;                    // 13 Reserved
    Uint16 rsvd11:1;                    // 14 Reserved
    Uint16 rsvd12:1;                    // 15 Reserved
    Uint16 rsvd13:1;                    // 16 Reserved
    Uint16 rsvd14:1;                    // 17 Reserved
    Uint16 rsvd15:1;                    // 18 Reserved
    Uint16 rsvd16:1;                    // 19 Reserved
    Uint16 rsvd17:1;                    // 20 Reserved
    Uint16 rsvd18:1;                    // 21 Reserved
    Uint16 rsvd19:1;                    // 22 Reserved
    Uint16 rsvd20:1;                    // 23 Reserved
    Uint16 rsvd21:1;                    // 24 Reserved
    Uint16 rsvd22:1;                    // 25 Reserved
    Uint16 rsvd23:1;                    // 26 Reserved
    Uint16 rsvd24:1;                    // 27 Reserved
    Uint16 rsvd25:1;                    // 28 Reserved
    Uint16 rsvd26:1;                    // 29 Reserved
    Uint16 rsvd27:1;                    // 30 Reserved
    Uint16 rsvd28:1;                    // 31 Reserved
};

union XBARFLG9_REG {
    Uint32  all;
    struct  XBARFLG9_BITS  bit;
};

struct XBARFLG10_BITS {                 // bits description
    Uint16 MDL1_OUTA:1;                 // 0 Input Flag for MDL1_OUTA Signal
    Uint16 MDL1_OUTB:1;                 // 1 Input Flag for MDL1_OUTB Signal
    Uint16 MDL2_OUTA:1;                 // 2 Input Flag for MDL2_OUTA Signal
    Uint16 MDL2_OUTB:1;                 // 3 Input Flag for MDL2_OUTB Signal
    Uint16 MDL3_OUTA:1;                 // 4 Input Flag for MDL3_OUTA Signal
    Uint16 MDL3_OUTB:1;                 // 5 Input Flag for MDL3_OUTB Signal
    Uint16 MDL4_OUTA:1;                 // 6 Input Flag for MDL4_OUTA Signal
    Uint16 MDL4_OUTB:1;                 // 7 Input Flag for MDL4_OUTB Signal
    Uint16 MDL5_OUTA:1;                 // 8 Input Flag for MDL5_OUTA Signal
    Uint16 MDL5_OUTB:1;                 // 9 Input Flag for MDL5_OUTB Signal
    Uint16 MDL6_OUTA:1;                 // 10 Input Flag for MDL6_OUTA Signal
    Uint16 MDL6_OUTB:1;                 // 11 Input Flag for MDL6_OUTB Signal
    Uint16 MDL7_OUTA:1;                 // 12 Input Flag for MDL7_OUTA Signal
    Uint16 MDL7_OUTB:1;                 // 13 Input Flag for MDL7_OUTB Signal
    Uint16 MDL8_OUTA:1;                 // 14 Input Flag for MDL8_OUTA Signal
    Uint16 MDL8_OUTB:1;                 // 15 Input Flag for MDL8_OUTB Signal
    Uint16 MDL9_OUTA:1;                 // 16 Input Flag for MDL9_OUTA Signal
    Uint16 MDL9_OUTB:1;                 // 17 Input Flag for MDL9_OUTB Signal
    Uint16 MDL10_OUTA:1;                // 18 Input Flag for MDL10_OUTA Signal
    Uint16 MDL10_OUTB:1;                // 19 Input Flag for MDL10_OUTB Signal
    Uint16 MDL11_OUTA:1;                // 20 Input Flag for MDL11_OUTA Signal
    Uint16 MDL11_OUTB:1;                // 21 Input Flag for MDL11_OUTB Signal
    Uint16 MDL12_OUTA:1;                // 22 Input Flag for MDL12_OUTA Signal
    Uint16 MDL12_OUTB:1;                // 23 Input Flag for MDL12_OUTB Signal
    Uint16 MDL13_OUTA:1;                // 24 Input Flag for MDL13_OUTA Signal
    Uint16 MDL13_OUTB:1;                // 25 Input Flag for MDL13_OUTB Signal
    Uint16 MDL14_OUTA:1;                // 26 Input Flag for MDL14_OUTA Signal
    Uint16 MDL14_OUTB:1;                // 27 Input Flag for MDL14_OUTB Signal
    Uint16 MDL15_OUTA:1;                // 28 Input Flag for MDL15_OUTA Signal
    Uint16 MDL15_OUTB:1;                // 29 Input Flag for MDL15_OUTB Signal
    Uint16 MDL16_OUTA:1;                // 30 Input Flag for MDL16_OUTA Signal
    Uint16 MDL16_OUTB:1;                // 31 Input Flag for MDL16_OUTB Signal
};

union XBARFLG10_REG {
    Uint32  all;
    struct  XBARFLG10_BITS  bit;
};

struct XBARFLG11_BITS {                 // bits description
    Uint16 MDL17_OUTA:1;                // 0 Input Flag for MDL17_OUTA Signal
    Uint16 MDL17_OUTB:1;                // 1 Input Flag for MDL17_OUTB Signal
    Uint16 MDL18_OUTA:1;                // 2 Input Flag for MDL18_OUTA Signal
    Uint16 MDL18_OUTB:1;                // 3 Input Flag for MDL18_OUTB Signal
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:1;                     // 8 Reserved
    Uint16 rsvd6:1;                     // 9 Reserved
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:1;                     // 11 Reserved
    Uint16 rsvd9:1;                     // 12 Reserved
    Uint16 rsvd10:1;                    // 13 Reserved
    Uint16 rsvd11:1;                    // 14 Reserved
    Uint16 rsvd12:1;                    // 15 Reserved
    Uint16 rsvd13:1;                    // 16 Reserved
    Uint16 rsvd14:1;                    // 17 Reserved
    Uint16 rsvd15:1;                    // 18 Reserved
    Uint16 rsvd16:1;                    // 19 Reserved
    Uint16 rsvd17:1;                    // 20 Reserved
    Uint16 rsvd18:1;                    // 21 Reserved
    Uint16 rsvd19:1;                    // 22 Reserved
    Uint16 rsvd20:1;                    // 23 Reserved
    Uint16 rsvd21:1;                    // 24 Reserved
    Uint16 rsvd22:1;                    // 25 Reserved
    Uint16 rsvd23:1;                    // 26 Reserved
    Uint16 rsvd24:1;                    // 27 Reserved
    Uint16 rsvd25:1;                    // 28 Reserved
    Uint16 rsvd26:1;                    // 29 Reserved
    Uint16 rsvd27:1;                    // 30 Reserved
    Uint16 rsvd28:1;                    // 31 Reserved
};

union XBARFLG11_REG {
    Uint32  all;
    struct  XBARFLG11_BITS  bit;
};

struct XBARFLG12_BITS {                 // bits description
    Uint16 CLB1_OUT0:1;                 // 0 Input Flag for CLB1_OUT0 Signal
    Uint16 CLB1_OUT1:1;                 // 1 Input Flag for CLB1_OUT1 Signal
    Uint16 CLB1_OUT2:1;                 // 2 Input Flag for CLB1_OUT2 Signal
    Uint16 CLB1_OUT3:1;                 // 3 Input Flag for CLB1_OUT3 Signal
    Uint16 CLB1_OUT6:1;                 // 4 Input Flag for CLB1_OUT6 Signal
    Uint16 CLB1_OUT7:1;                 // 5 Input Flag for CLB1_OUT7 Signal
    Uint16 CLB2_OUT0:1;                 // 6 Input Flag for CLB2_OUT0 Signal
    Uint16 CLB2_OUT1:1;                 // 7 Input Flag for CLB2_OUT1 Signal
    Uint16 CLB2_OUT2:1;                 // 8 Input Flag for CLB2_OUT2 Signal
    Uint16 CLB2_OUT3:1;                 // 9 Input Flag for CLB2_OUT3 Signal
    Uint16 CLB2_OUT6:1;                 // 10 Input Flag for CLB2_OUT6 Signal
    Uint16 CLB2_OUT7:1;                 // 11 Input Flag for CLB2_OUT7 Signal
    Uint16 CLB3_OUT0:1;                 // 12 Input Flag for CLB3_OUT0 Signal
    Uint16 CLB3_OUT1:1;                 // 13 Input Flag for CLB3_OUT1 Signal
    Uint16 CLB3_OUT2:1;                 // 14 Input Flag for CLB3_OUT2 Signal
    Uint16 CLB3_OUT3:1;                 // 15 Input Flag for CLB3_OUT3 Signal
    Uint16 CLB3_OUT6:1;                 // 16 Input Flag for CLB3_OUT6 Signal
    Uint16 CLB3_OUT7:1;                 // 17 Input Flag for CLB3_OUT7 Signal
    Uint16 CLB4_OUT0:1;                 // 18 Input Flag for CLB4_OUT0 Signal
    Uint16 CLB4_OUT1:1;                 // 19 Input Flag for CLB4_OUT1 Signal
    Uint16 CLB4_OUT2:1;                 // 20 Input Flag for CLB4_OUT2 Signal
    Uint16 CLB4_OUT3:1;                 // 21 Input Flag for CLB4_OUT3 Signal
    Uint16 CLB4_OUT6:1;                 // 22 Input Flag for CLB4_OUT6 Signal
    Uint16 CLB4_OUT7:1;                 // 23 Input Flag for CLB4_OUT7 Signal
    Uint16 CLB5_OUT0:1;                 // 24 Input Flag for CLB5_OUT0 Signal
    Uint16 CLB5_OUT1:1;                 // 25 Input Flag for CLB5_OUT1 Signal
    Uint16 CLB5_OUT2:1;                 // 26 Input Flag for CLB5_OUT2 Signal
    Uint16 CLB5_OUT3:1;                 // 27 Input Flag for CLB5_OUT3 Signal
    Uint16 CLB5_OUT6:1;                 // 28 Input Flag for CLB5_OUT6 Signal
    Uint16 CLB5_OUT7:1;                 // 29 Input Flag for CLB5_OUT7 Signal
    Uint16 CLB6_OUT0:1;                 // 30 Input Flag for CLB6_OUT0 Signal
    Uint16 CLB6_OUT1:1;                 // 31 Input Flag for CLB6_OUT1 Signal
};

union XBARFLG12_REG {
    Uint32  all;
    struct  XBARFLG12_BITS  bit;
};

struct XBARFLG13_BITS {                 // bits description
    Uint16 CLB6_OUT2:1;                 // 0 Input Flag for CLB6_OUT2 Signal
    Uint16 CLB6_OUT3:1;                 // 1 Input Flag for CLB6_OUT3 Signal
    Uint16 CLB6_OUT6:1;                 // 2 Input Flag for CLB6_OUT6 Signal
    Uint16 CLB6_OUT7:1;                 // 3 Input Flag for CLB6_OUT7 Signal
    Uint16 XTRIPOUT1:1;                 // 4 Input Flag for XTRIPOUT1 Signal
    Uint16 XTRIPOUT2:1;                 // 5 Input Flag for XTRIPOUT2 Signal
    Uint16 XTRIPOUT3:1;                 // 6 Input Flag for XTRIPOUT3 Signal
    Uint16 XTRIPOUT4:1;                 // 7 Input Flag for XTRIPOUT4 Signal
    Uint16 XTRIPOUT5:1;                 // 8 Input Flag for XTRIPOUT5 Signal
    Uint16 XTRIPOUT6:1;                 // 9 Input Flag for XTRIPOUT6 Signal
    Uint16 XTRIPOUT7:1;                 // 10 Input Flag for XTRIPOUT7 Signal
    Uint16 XTRIPOUT8:1;                 // 11 Input Flag for XTRIPOUT8 Signal
    Uint16 ADCA_EXTMUXSEL0:1;           // 12 Input Flag for ADCA_EXTMUXSEL0 Signal
    Uint16 ADCA_EXTMUXSEL1:1;           // 13 Input Flag for ADCA_EXTMUXSEL1 Signal
    Uint16 ADCA_EXTMUXSEL2:1;           // 14 Input Flag for ADCA_EXTMUXSEL2 Signal
    Uint16 ADCA_EXTMUXSEL3:1;           // 15 Input Flag for ADCA_EXTMUXSEL3 Signal
    Uint16 ADCB_EXTMUXSEL0:1;           // 16 Input Flag for ADCB_EXTMUXSEL0 Signal
    Uint16 ADCB_EXTMUXSEL1:1;           // 17 Input Flag for ADCB_EXTMUXSEL1 Signal
    Uint16 ADCB_EXTMUXSEL2:1;           // 18 Input Flag for ADCB_EXTMUXSEL2 Signal
    Uint16 ADCB_EXTMUXSEL3:1;           // 19 Input Flag for ADCB_EXTMUXSEL3 Signal
    Uint16 ADCC_EXTMUXSEL0:1;           // 20 Input Flag for ADCC_EXTMUXSEL0 Signal
    Uint16 ADCC_EXTMUXSEL1:1;           // 21 Input Flag for ADCC_EXTMUXSEL1 Signal
    Uint16 ADCC_EXTMUXSEL2:1;           // 22 Input Flag for ADCC_EXTMUXSEL2 Signal
    Uint16 ADCC_EXTMUXSEL3:1;           // 23 Input Flag for ADCC_EXTMUXSEL3 Signal
    Uint16 rsvd1:1;                     // 24 Reserved
    Uint16 rsvd2:1;                     // 25 Reserved
    Uint16 PIEERR:1;                    // 26 Input Flag for PIEERR Signal
    Uint16 ECCERR:1;                    // 27 Input Flag for ECCERR Signal
    Uint16 EPG1_EPGOUT0:1;              // 28 Input Flag for EPG1_EPGOUT0 Signal
    Uint16 EPG1_EPGOUT1:1;              // 29 Input Flag for EPG1_EPGOUT1 Signal
    Uint16 EPG1_EPGOUT2:1;              // 30 Input Flag for EPG1_EPGOUT2 Signal
    Uint16 EPG1_EPGOUT3:1;              // 31 Input Flag for EPG1_EPGOUT3 Signal
};

union XBARFLG13_REG {
    Uint32  all;
    struct  XBARFLG13_BITS  bit;
};

struct XBARFLG14_BITS {                 // bits description
    Uint16 SD3FLT1_COMPH:1;             // 0 Input Flag for SD3FLT1_COMPH Signal
    Uint16 SD3FLT1_COMPL:1;             // 1 Input Flag for SD3FLT1_COMPL Signal
    Uint16 SD3FLT2_COMPH:1;             // 2 Input Flag for SD3FLT2_COMPH Signal
    Uint16 SD3FLT2_COMPL:1;             // 3 Input Flag for SD3FLT2_COMPL Signal
    Uint16 SD3FLT3_COMPH:1;             // 4 Input Flag for SD3FLT3_COMPH Signal
    Uint16 SD3FLT3_COMPL:1;             // 5 Input Flag for SD3FLT3_COMPL Signal
    Uint16 SD3FLT4_COMPH:1;             // 6 Input Flag for SD3FLT4_COMPH Signal
    Uint16 SD3FLT4_COMPL:1;             // 7 Input Flag for SD3FLT4_COMPL Signal
    Uint16 SD4FLT1_COMPH:1;             // 8 Input Flag for SD4FLT1_COMPH Signal
    Uint16 SD4FLT1_COMPL:1;             // 9 Input Flag for SD4FLT1_COMPL Signal
    Uint16 SD4FLT2_COMPH:1;             // 10 Input Flag for SD4FLT2_COMPH Signal
    Uint16 SD4FLT2_COMPL:1;             // 11 Input Flag for SD4FLT2_COMPL Signal
    Uint16 SD4FLT3_COMPH:1;             // 12 Input Flag for SD4FLT3_COMPH Signal
    Uint16 SD4FLT3_COMPL:1;             // 13 Input Flag for SD4FLT3_COMPL Signal
    Uint16 SD4FLT4_COMPH:1;             // 14 Input Flag for SD4FLT4_COMPH Signal
    Uint16 SD4FLT4_COMPL:1;             // 15 Input Flag for SD4FLT4_COMPL Signal
    Uint16 rsvd1:1;                     // 16 Reserved
    Uint16 INPUTXBAR2_INPUT10:1;        // 17 Input Flag for INPUTXBAR2_INPUT10 Signal
    Uint16 INPUTXBAR2_INPUT11:1;        // 18 Input Flag for INPUTXBAR2_INPUT11 Signal
    Uint16 INPUTXBAR2_INPUT12:1;        // 19 Input Flag for INPUTXBAR2_INPUT12 Signal
    Uint16 INPUTXBAR2_INPUT13:1;        // 20 Input Flag for INPUTXBAR2_INPUT13 Signal
    Uint16 INPUTXBAR2_INPUT14:1;        // 21 Input Flag for INPUTXBAR2_INPUT14 Signal
    Uint16 INPUTXBAR2_INPUT7:1;         // 22 Input Flag for INPUTXBAR2_INPUT7 Signal
    Uint16 INPUTXBAR2_INPUT8:1;         // 23 Input Flag for INPUTXBAR2_INPUT8 Signal
    Uint16 INPUTXBAR2_INPUT9:1;         // 24 Input Flag for INPUTXBAR2_INPUT9 Signal
    Uint16 MCANB_FEVT0:1;               // 25 Input Flag for MCANB_FEVT0 Signal
    Uint16 MCANB_FEVT1:1;               // 26 Input Flag for MCANB_FEVT1 Signal
    Uint16 MCANB_FEVT2:1;               // 27 Input Flag for MCANB_FEVT2 Signal
    Uint16 FSIA_RX_TRIG1:1;             // 28 Input Flag for FSIA_RX_TRIG1 Signal
    Uint16 FSIB_RX_TRIG1:1;             // 29 Input Flag for FSIB_RX_TRIG1 Signal
    Uint16 FSIC_RX_TRIG1:1;             // 30 Input Flag for FSIC_RX_TRIG1 Signal
    Uint16 FSID_RX_TRIG1:1;             // 31 Input Flag for FSID_RX_TRIG1 Signal
};

union XBARFLG14_REG {
    Uint32  all;
    struct  XBARFLG14_BITS  bit;
};

struct XBARFLG15_BITS {                 // bits description
    Uint16 FSIRXA_TRIG_2:1;             // 0 Input Flag for FSIRXA_TRIG_2 Signal
    Uint16 FSIRXA_TRIG_3:1;             // 1 Input Flag for FSIRXA_TRIG_3 Signal
    Uint16 FSIRXB_TRIG_2:1;             // 2 Input Flag for FSIRXB_TRIG_2 Signal
    Uint16 FSIRXB_TRIG_3:1;             // 3 Input Flag for FSIRXB_TRIG_3 Signal
    Uint16 FSIRXC_TRIG_2:1;             // 4 Input Flag for FSIRXC_TRIG_2 Signal
    Uint16 FSIRXC_TRIG_3:1;             // 5 Input Flag for FSIRXC_TRIG_3 Signal
    Uint16 FSIRXD_TRIG_2:1;             // 6 Input Flag for FSIRXD_TRIG_2 Signal
    Uint16 FSIRXD_TRIG_3:1;             // 7 Input Flag for FSIRXD_TRIG_3 Signal
    Uint16 ECAP1_TRIPOUT:1;             // 8 Input Flag for ECAP1_TRIPOUT Signal
    Uint16 ECAP2_TRIPOUT:1;             // 9 Input Flag for ECAP2_TRIPOUT Signal
    Uint16 ECAP3_TRIPOUT:1;             // 10 Input Flag for ECAP3_TRIPOUT Signal
    Uint16 ECAP4_TRIPOUT:1;             // 11 Input Flag for ECAP4_TRIPOUT Signal
    Uint16 ECAP5_TRIPOUT:1;             // 12 Input Flag for ECAP5_TRIPOUT Signal
    Uint16 ECAP6_TRIPOUT:1;             // 13 Input Flag for ECAP6_TRIPOUT Signal
    Uint16 CPU1ERADEVT10:1;             // 14 Input Flag for CPU1ERADEVT10 Signal
    Uint16 CPU1ERADEVT11:1;             // 15 Input Flag for CPU1ERADEVT11 Signal
    Uint16 CPU1ERADEVT8:1;              // 16 Input Flag for CPU1ERADEVT8 Signal
    Uint16 CPU1ERADEVT9:1;              // 17 Input Flag for CPU1ERADEVT9 Signal
    Uint16 CPU1_ADCCHECKEVT1:1;         // 18 Input Flag for CPU1_ADCCHECKEVT1 Signal
    Uint16 CPU1_ADCCHECKEVT2:1;         // 19 Input Flag for CPU1_ADCCHECKEVT2 Signal
    Uint16 CPU1_ADCCHECKEVT3:1;         // 20 Input Flag for CPU1_ADCCHECKEVT3 Signal
    Uint16 CPU1_ADCCHECKEVT4:1;         // 21 Input Flag for CPU1_ADCCHECKEVT4 Signal
    Uint16 CPU2ERADEVT10:1;             // 22 Input Flag for CPU2ERADEVT10 Signal
    Uint16 CPU2ERADEVT11:1;             // 23 Input Flag for CPU2ERADEVT11 Signal
    Uint16 CPU2ERADEVT8:1;              // 24 Input Flag for CPU2ERADEVT8 Signal
    Uint16 CPU2ERADEVT9:1;              // 25 Input Flag for CPU2ERADEVT9 Signal
    Uint16 CPU2_ADCCHECKEVT1:1;         // 26 Input Flag for CPU2_ADCCHECKEVT1 Signal
    Uint16 CPU2_ADCCHECKEVT2:1;         // 27 Input Flag for CPU2_ADCCHECKEVT2 Signal
    Uint16 CPU2_ADCCHECKEVT3:1;         // 28 Input Flag for CPU2_ADCCHECKEVT3 Signal
    Uint16 CPU2_ADCCHECKEVT4:1;         // 29 Input Flag for CPU2_ADCCHECKEVT4 Signal
    Uint16 rsvd1:1;                     // 30 Reserved
    Uint16 rsvd2:1;                     // 31 Reserved
};

union XBARFLG15_REG {
    Uint32  all;
    struct  XBARFLG15_BITS  bit;
};

struct XBARFLG16_BITS {                 // bits description
    Uint16 CMPSS9_CTRIPH:1;             // 0 Input Flag for CMPSS9_CTRIPH Signal
    Uint16 CMPSS9_CTRIPL:1;             // 1 Input Flag for CMPSS9_CTRIPL Signal
    Uint16 CMPSS9_CTRIPOUTH:1;          // 2 Input Flag for CMPSS9_CTRIPOUTH Signal
    Uint16 CMPSS9_CTRIPOUTL:1;          // 3 Input Flag for CMPSS9_CTRIPOUTL Signal
    Uint16 CMPSS10_CTRIPH:1;            // 4 Input Flag for CMPSS10_CTRIPH Signal
    Uint16 CMPSS10_CTRIPL:1;            // 5 Input Flag for CMPSS10_CTRIPL Signal
    Uint16 CMPSS10_CTRIPOUTH:1;         // 6 Input Flag for CMPSS10_CTRIPOUTH Signal
    Uint16 CMPSS10_CTRIPOUTL:1;         // 7 Input Flag for CMPSS10_CTRIPOUTL Signal
    Uint16 CMPSS11_CTRIPH:1;            // 8 Input Flag for CMPSS11_CTRIPH Signal
    Uint16 CMPSS11_CTRIPL:1;            // 9 Input Flag for CMPSS11_CTRIPL Signal
    Uint16 CMPSS11_CTRIPOUTH:1;         // 10 Input Flag for CMPSS11_CTRIPOUTH Signal
    Uint16 CMPSS11_CTRIPOUTL:1;         // 11 Input Flag for CMPSS11_CTRIPOUTL Signal
    Uint16 CMPSS12_CTRIPH:1;            // 12 Input Flag for CMPSS12_CTRIPH Signal
    Uint16 CMPSS12_CTRIPL:1;            // 13 Input Flag for CMPSS12_CTRIPL Signal
    Uint16 CMPSS12_CTRIPOUTH:1;         // 14 Input Flag for CMPSS12_CTRIPOUTH Signal
    Uint16 CMPSS12_CTRIPOUTL:1;         // 15 Input Flag for CMPSS12_CTRIPOUTL Signal
    Uint16 rsvd1:1;                     // 16 Reserved
    Uint16 rsvd2:1;                     // 17 Reserved
    Uint16 rsvd3:1;                     // 18 Reserved
    Uint16 rsvd4:1;                     // 19 Reserved
    Uint16 rsvd5:1;                     // 20 Reserved
    Uint16 rsvd6:1;                     // 21 Reserved
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 XCLKOUT:1;                   // 31 Input Flag for XCLKOUT Signal
};

union XBARFLG16_REG {
    Uint32  all;
    struct  XBARFLG16_BITS  bit;
};

struct XBARCLR1_BITS {                  // bits description
    Uint16 CMPSS1_CTRIPL:1;             // 0 Input Flag Clear for CMPSS1.CTRIPL Signal
    Uint16 CMPSS1_CTRIPH:1;             // 1 Input Flag Clear for CMPSS1.CTRIPH Signal
    Uint16 CMPSS2_CTRIPL:1;             // 2 Input Flag Clear for CMPSS2.CTRIPL Signal
    Uint16 CMPSS2_CTRIPH:1;             // 3 Input Flag Clear for CMPSS2.CTRIPH Signal
    Uint16 CMPSS3_CTRIPL:1;             // 4 Input Flag Clear for CMPSS3.CTRIPL Signal
    Uint16 CMPSS3_CTRIPH:1;             // 5 Input Flag Clear for CMPSS3.CTRIPH Signal
    Uint16 CMPSS4_CTRIPL:1;             // 6 Input Flag Clear for CMPSS4.CTRIPL Signal
    Uint16 CMPSS4_CTRIPH:1;             // 7 Input Flag Clear for CMPSS4.CTRIPH Signal
    Uint16 CMPSS5_CTRIPL:1;             // 8 Input Flag Clear for CMPSS5.CTRIPL Signal
    Uint16 CMPSS5_CTRIPH:1;             // 9 Input Flag Clear for CMPSS5.CTRIPH Signal
    Uint16 CMPSS6_CTRIPL:1;             // 10 Input Flag Clear for CMPSS6.CTRIPL Signal
    Uint16 CMPSS6_CTRIPH:1;             // 11 Input Flag Clear for CMPSS6.CTRIPH Signal
    Uint16 CMPSS7_CTRIPL:1;             // 12 Input Flag Clear for CMPSS7.CTRIPL Signal
    Uint16 CMPSS7_CTRIPH:1;             // 13 Input Flag Clear for CMPSS7.CTRIPH Signal
    Uint16 CMPSS8_CTRIPL:1;             // 14 Input Flag Clear for CMPSS8.CTRIPL Signal
    Uint16 CMPSS8_CTRIPH:1;             // 15 Input Flag Clear for CMPSS8.CTRIPH Signal
    Uint16 CMPSS1_CTRIPOUTL:1;          // 16 Input Flag Clear for CMPSS1.CTRIPOUTL Signal
    Uint16 CMPSS1_CTRIPOUTH:1;          // 17 Input Flag Clear for CMPSS1.CTRIPOUTH Signal
    Uint16 CMPSS2_CTRIPOUTL:1;          // 18 Input Flag Clear for CMPSS2.CTRIPOUTL Signal
    Uint16 CMPSS2_CTRIPOUTH:1;          // 19 Input Flag Clear for CMPSS2.CTRIPOUTH Signal
    Uint16 CMPSS3_CTRIPOUTL:1;          // 20 Input Flag Clear for CMPSS3.CTRIPOUTL Signal
    Uint16 CMPSS3_CTRIPOUTH:1;          // 21 Input Flag Clear for CMPSS3.CTRIPOUTH Signal
    Uint16 CMPSS4_CTRIPOUTL:1;          // 22 Input Flag Clear for CMPSS4.CTRIPOUTL Signal
    Uint16 CMPSS4_CTRIPOUTH:1;          // 23 Input Flag Clear for CMPSS4.CTRIPOUTH Signal
    Uint16 CMPSS5_CTRIPOUTL:1;          // 24 Input Flag Clear for CMPSS5.CTRIPOUTL Signal
    Uint16 CMPSS5_CTRIPOUTH:1;          // 25 Input Flag Clear for CMPSS5.CTRIPOUTH Signal
    Uint16 CMPSS6_CTRIPOUTL:1;          // 26 Input Flag Clear for CMPSS6.CTRIPOUTL Signal
    Uint16 CMPSS6_CTRIPOUTH:1;          // 27 Input Flag Clear for CMPSS6.CTRIPOUTH Signal
    Uint16 CMPSS7_CTRIPOUTL:1;          // 28 Input Flag Clear for CMPSS7.CTRIPOUTL Signal
    Uint16 CMPSS7_CTRIPOUTH:1;          // 29 Input Flag Clear for CMPSS7.CTRIPOUTH Signal
    Uint16 CMPSS8_CTRIPOUTL:1;          // 30 Input Flag Clear for CMPSS8.CTRIPOUTL Signal
    Uint16 CMPSS8_CTRIPOUTH:1;          // 31 Input Flag Clear for CMPSS8.CTRIPOUTH Signal
};

union XBARCLR1_REG {
    Uint32  all;
    struct  XBARCLR1_BITS  bit;
};

struct XBARCLR2_BITS {                  // bits description
    Uint16 INPUT1:1;                    // 0 Input Flag Clear for INPUT1 Signal
    Uint16 INPUT2:1;                    // 1 Input Flag Clear for INPUT2 Signal
    Uint16 INPUT3:1;                    // 2 Input Flag Clear for INPUT3 Signal
    Uint16 INPUT4:1;                    // 3 Input Flag Clear for INPUT4 Signal
    Uint16 INPUT5:1;                    // 4 Input Flag Clear for INPUT5 Signal
    Uint16 INPUT6:1;                    // 5 Input Flag Clear for INPUT6 Signal
    Uint16 ADCSOCA:1;                   // 6 Input Flag Clear for ADCSOCA Signal
    Uint16 ADCSOCB:1;                   // 7 Input Flag Clear for ADCSOCB Signal
    Uint16 INPUT7:1;                    // 8 Input Flag Clear for INPUT7 Signal
    Uint16 INPUT8:1;                    // 9 Input Flag Clear for INPUT8 Signal
    Uint16 INPUT9:1;                    // 10 Input Flag Clear for INPUT9 Signal
    Uint16 INPUT10:1;                   // 11 Input Flag Clear for INPUT10 Signal
    Uint16 INPUT11:1;                   // 12 Input Flag Clear for INPUT11 Signal
    Uint16 INPUT12:1;                   // 13 Input Flag Clear for INPUT12 Signal
    Uint16 INPUT13:1;                   // 14 Input Flag Clear for INPUT13 Signal
    Uint16 INPUT14:1;                   // 15 Input Flag Clear for INPUT14 Signal
    Uint16 ECAP1_OUT:1;                 // 16 Input Flag Clear for ECAP1.OUT Signal
    Uint16 ECAP2_OUT:1;                 // 17 Input Flag Clear for ECAP2.OUT Signal
    Uint16 ECAP3_OUT:1;                 // 18 Input Flag Clear for ECAP3.OUT Signal
    Uint16 ECAP4_OUT:1;                 // 19 Input Flag Clear for ECAP4.OUT Signal
    Uint16 ECAP5_OUT:1;                 // 20 Input Flag Clear for ECAP5.OUT Signal
    Uint16 ECAP6_OUT:1;                 // 21 Input Flag Clear for ECAP6.OUT Signal
    Uint16 EXTSYNCOUT:1;                // 22 Input Flag Clear for EXTSYNCOUT Signal
    Uint16 ADCAEVT1:1;                  // 23 Input Flag Clear for ADCAEVT1 Signal
    Uint16 ADCAEVT2:1;                  // 24 Input Flag Clear for ADCAEVT2 Signal
    Uint16 ADCAEVT3:1;                  // 25 Input Flag Clear for ADCAEVT3 Signal
    Uint16 ADCAEVT4:1;                  // 26 Input Flag Clear for ADCAEVT4 Signal
    Uint16 ADCBEVT1:1;                  // 27 Input Flag Clear for ADCBEVT1 Signal
    Uint16 ADCBEVT2:1;                  // 28 Input Flag Clear for ADCBEVT2 Signal
    Uint16 ADCBEVT3:1;                  // 29 Input Flag Clear for ADCBEVT3 Signal
    Uint16 ADCBEVT4:1;                  // 30 Input Flag Clear for ADCBEVT4 Signal
    Uint16 ADCCEVT1:1;                  // 31 Input Flag Clear for ADCCEVT1 Signal
};

union XBARCLR2_REG {
    Uint32  all;
    struct  XBARCLR2_BITS  bit;
};

struct XBARCLR3_BITS {                  // bits description
    Uint16 ADCCEVT2:1;                  // 0 Input Flag Clear for ADCCEVT2 Signal
    Uint16 ADCCEVT3:1;                  // 1 Input Flag Clear for ADCCEVT3 Signal
    Uint16 ADCCEVT4:1;                  // 2 Input Flag Clear for ADCCEVT4 Signal
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:1;                     // 6 Reserved
    Uint16 SD1FLT1_COMPL:1;             // 7 Input Flag Clear for SD1FLT1.COMPL Signal
    Uint16 SD1FLT1_COMPH:1;             // 8 Input Flag Clear for SD1FLT1.COMPH Signal
    Uint16 SD1FLT2_COMPL:1;             // 9 Input Flag Clear for SD1FLT2.COMPL Signal
    Uint16 SD1FLT2_COMPH:1;             // 10 Input Flag Clear for SD1FLT2.COMPH Signal
    Uint16 SD1FLT3_COMPL:1;             // 11 Input Flag Clear for SD1FLT3.COMPL Signal
    Uint16 SD1FLT3_COMPH:1;             // 12 Input Flag Clear for SD1FLT3.COMPH Signal
    Uint16 SD1FLT4_COMPL:1;             // 13 Input Flag Clear for SD1FLT4.COMPL Signal
    Uint16 SD1FLT4_COMPH:1;             // 14 Input Flag Clear for SD1FLT4.COMPH Signal
    Uint16 SD2FLT1_COMPL:1;             // 15 Input Flag Clear for SD2FLT1.COMPL Signal
    Uint16 SD2FLT1_COMPH:1;             // 16 Input Flag Clear for SD2FLT1.COMPH Signal
    Uint16 SD2FLT2_COMPL:1;             // 17 Input Flag Clear for SD2FLT2.COMPL Signal
    Uint16 SD2FLT2_COMPH:1;             // 18 Input Flag Clear for SD2FLT2.COMPH Signal
    Uint16 SD2FLT3_COMPL:1;             // 19 Input Flag Clear for SD2FLT3.COMPL Signal
    Uint16 SD2FLT3_COMPH:1;             // 20 Input Flag Clear for SD2FLT3.COMPH Signal
    Uint16 SD2FLT4_COMPL:1;             // 21 Input Flag Clear for SD2FLT4.COMPL Signal
    Uint16 SD2FLT4_COMPH:1;             // 22 Input Flag Clear for SD2FLT4.COMPH Signal
    Uint16 ECAP7_OUT:1;                 // 23 Input Flag clear for ECAP7.OUT Signal
    Uint16 rsvd5:1;                     // 24 Reserved
    Uint16 rsvd6:1;                     // 25 Reserved
    Uint16 rsvd7:1;                     // 26 Reserved
    Uint16 rsvd8:1;                     // 27 Reserved
    Uint16 rsvd9:1;                     // 28 Reserved
    Uint16 rsvd10:1;                    // 29 Reserved
    Uint16 rsvd11:1;                    // 30 Reserved
    Uint16 rsvd12:1;                    // 31 Reserved
};

union XBARCLR3_REG {
    Uint32  all;
    struct  XBARCLR3_BITS  bit;
};

struct XBARCLR4_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 rsvd7:1;                     // 6 Reserved
    Uint16 rsvd8:1;                     // 7 Reserved
    Uint16 rsvd9:1;                     // 8 Reserved
    Uint16 MCANA_FEVT0:1;               // 9 Input Flag clear for MCANA_FEVT0 Signal
    Uint16 MCANA_FEVT1:1;               // 10 Input Flag clear for MCANA_FEVT1 Signal
    Uint16 MCANA_FEVT2:1;               // 11 Input Flag clear for MCANA_FEVT2 Signal
    Uint16 rsvd10:1;                    // 12 Reserved
    Uint16 rsvd11:1;                    // 13 Reserved
    Uint16 rsvd12:1;                    // 14 Reserved
    Uint16 rsvd13:1;                    // 15 Reserved
    Uint16 CLB1_OUT4:1;                 // 16 Input Flag clear for CLB1_4.1 Signal
    Uint16 CLB1_OUT5:1;                 // 17 Input Flag clear for CLB1_5.1 Signal
    Uint16 CLB2_OUT4:1;                 // 18 Input Flag clear for CLB2_4.1 Signal
    Uint16 CLB2_OUT5:1;                 // 19 Input Flag clear for CLB2_5.1 Signal
    Uint16 CLB3_OUT4:1;                 // 20 Input Flag clear for CLB3_4.1 Signal
    Uint16 CLB3_OUT5:1;                 // 21 Input Flag clear for CLB3_5.1 Signal
    Uint16 CLB4_OUT4:1;                 // 22 Input Flag clear for CLB4_4.1 Signal
    Uint16 CLB4_OUT5:1;                 // 23 Input Flag clear for CLB4_5.1 Signal
    Uint16 CLB5_OUT4:1;                 // 24 Input Latch clear for CLB5_OUT4 Signal
    Uint16 CLB5_OUT5:1;                 // 25 Input Latch clear for CLB5_OUT5 Signal
    Uint16 CLB6_OUT4:1;                 // 26 Input Latch clear for CLB6_OUT4 Signal
    Uint16 CLB6_OUT5:1;                 // 27 Input Latch clear for CLB6_OUT5 Signal
    Uint16 ERRORSTS_ERROR:1;            // 28 Input Latch clear for ERRORSTS_ERROR Signal
    Uint16 ECATSYNC0:1;                 // 29 Input Latch clear for ECATSYNC0 Signal
    Uint16 ECATSYNC1:1;                 // 30 Input Latch clear for ECATSYNC1 Signal
    Uint16 CLAHALT:1;                   // 31 Input Flag clear for CLAHALT Signal
};

union XBARCLR4_REG {
    Uint32  all;
    struct  XBARCLR4_BITS  bit;
};

struct XBARCLR5_BITS {                  // bits description
    Uint16 EPWM1_TRIPOUT:1;             // 0 Input Flag clear for EPWM1_TRIPOUT Signal
    Uint16 EPWM2_TRIPOUT:1;             // 1 Input Flag clear for EPWM2_TRIPOUT Signal
    Uint16 EPWM3_TRIPOUT:1;             // 2 Input Flag clear for EPWM3_TRIPOUT Signal
    Uint16 EPWM4_TRIPOUT:1;             // 3 Input Flag clear for EPWM4_TRIPOUT Signal
    Uint16 EPWM5_TRIPOUT:1;             // 4 Input Flag clear for EPWM5_TRIPOUT Signal
    Uint16 EPWM6_TRIPOUT:1;             // 5 Input Flag clear for EPWM6_TRIPOUT Signal
    Uint16 EPWM7_TRIPOUT:1;             // 6 Input Flag clear for EPWM7_TRIPOUT Signal
    Uint16 EPWM8_TRIPOUT:1;             // 7 Input Flag clear for EPWM8_TRIPOUT Signal
    Uint16 EPWM9_TRIPOUT:1;             // 8 Input Flag clear for EPWM9_TRIPOUT Signal
    Uint16 EPWM10_TRIPOUT:1;            // 9 Input Flag clear for EPWM10_TRIPOUT Signal
    Uint16 EPWM11_TRIPOUT:1;            // 10 Input Flag clear for EPWM11_TRIPOUT Signal
    Uint16 EPWM12_TRIPOUT:1;            // 11 Input Flag clear for EPWM12_TRIPOUT Signal
    Uint16 EPWM13_TRIPOUT:1;            // 12 Input Flag clear for EPWM13_TRIPOUT Signal
    Uint16 EPWM14_TRIPOUT:1;            // 13 Input Flag clear for EPWM14_TRIPOUT Signal
    Uint16 EPWM15_TRIPOUT:1;            // 14 Input Flag clear for EPWM15_TRIPOUT Signal
    Uint16 EPWM16_TRIPOUT:1;            // 15 Input Flag clear for EPWM16_TRIPOUT Signal
    Uint16 EPWM17_TRIPOUT:1;            // 16 Input Flag clear for EPWM17_TRIPOUT Signal
    Uint16 EPWM18_TRIPOUT:1;            // 17 Input Flag clear for EPWM18_TRIPOUT Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARCLR5_REG {
    Uint32  all;
    struct  XBARCLR5_BITS  bit;
};

struct XBARCLR6_BITS {                  // bits description
    Uint16 EPWM1_DEL_TRIP:1;            // 0 Input Flag clear for EPWM1_DEL_TRIP Signal
    Uint16 EPWM2_DEL_TRIP:1;            // 1 Input Flag clear for EPWM2_DEL_TRIP Signal
    Uint16 EPWM3_DEL_TRIP:1;            // 2 Input Flag clear for EPWM3_DEL_TRIP Signal
    Uint16 EPWM4_DEL_TRIP:1;            // 3 Input Flag clear for EPWM4_DEL_TRIP Signal
    Uint16 EPWM5_DEL_TRIP:1;            // 4 Input Flag clear for EPWM5_DEL_TRIP Signal
    Uint16 EPWM6_DEL_TRIP:1;            // 5 Input Flag clear for EPWM6_DEL_TRIP Signal
    Uint16 EPWM7_DEL_TRIP:1;            // 6 Input Flag clear for EPWM7_DEL_TRIP Signal
    Uint16 EPWM8_DEL_TRIP:1;            // 7 Input Flag clear for EPWM8_DEL_TRIP Signal
    Uint16 EPWM9_DEL_TRIP:1;            // 8 Input Flag clear for EPWM9_DEL_TRIP Signal
    Uint16 EPWM10_DEL_TRIP:1;           // 9 Input Flag clear for EPWM10_DEL_TRIP Signal
    Uint16 EPWM11_DEL_TRIP:1;           // 10 Input Flag clear for EPWM11_DEL_TRIP Signal
    Uint16 EPWM12_DEL_TRIP:1;           // 11 Input Flag clear for EPWM12_DEL_TRIP Signal
    Uint16 EPWM13_DEL_TRIP:1;           // 12 Input Flag clear for EPWM13_DEL_TRIP Signal
    Uint16 EPWM14_DEL_TRIP:1;           // 13 Input Flag clear for EPWM14_DEL_TRIP Signal
    Uint16 EPWM15_DEL_TRIP:1;           // 14 Input Flag clear for EPWM15_DEL_TRIP Signal
    Uint16 EPWM16_DEL_TRIP:1;           // 15 Input Flag clear for EPWM16_DEL_TRIP Signal
    Uint16 EPWM17_DEL_TRIP:1;           // 16 Input Flag clear for EPWM17_DEL_TRIP Signal
    Uint16 EPWM18_DEL_TRIP:1;           // 17 Input Flag clear for EPWM18_DEL_TRIP Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARCLR6_REG {
    Uint32  all;
    struct  XBARCLR6_BITS  bit;
};

struct XBARCLR7_BITS {                  // bits description
    Uint16 EPWM1_DEL_ACTIVE:1;          // 0 Input Flag clear for EPWM1_DEL_ACTIVE Signal
    Uint16 EPWM2_DEL_ACTIVE:1;          // 1 Input Flag clear for EPWM2_DEL_ACTIVE Signal
    Uint16 EPWM3_DEL_ACTIVE:1;          // 2 Input Flag clear for EPWM3_DEL_ACTIVE Signal
    Uint16 EPWM4_DEL_ACTIVE:1;          // 3 Input Flag clear for EPWM4_DEL_ACTIVE Signal
    Uint16 EPWM5_DEL_ACTIVE:1;          // 4 Input Flag clear for EPWM5_DEL_ACTIVE Signal
    Uint16 EPWM6_DEL_ACTIVE:1;          // 5 Input Flag clear for EPWM6_DEL_ACTIVE Signal
    Uint16 EPWM7_DEL_ACTIVE:1;          // 6 Input Flag clear for EPWM7_DEL_ACTIVE Signal
    Uint16 EPWM8_DEL_ACTIVE:1;          // 7 Input Flag clear for EPWM8_DEL_ACTIVE Signal
    Uint16 EPWM9_DEL_ACTIVE:1;          // 8 Input Flag clear for EPWM9_DEL_ACTIVE Signal
    Uint16 EPWM10_DEL_ACTIVE:1;         // 9 Input Flag clear for EPWM10_DEL_ACTIVE Signal
    Uint16 EPWM11_DEL_ACTIVE:1;         // 10 Input Flag clear for EPWM11_DEL_ACTIVE Signal
    Uint16 EPWM12_DEL_ACTIVE:1;         // 11 Input Flag clear for EPWM12_DEL_ACTIVE Signal
    Uint16 EPWM13_DEL_ACTIVE:1;         // 12 Input Flag clear for EPWM13_DEL_ACTIVE Signal
    Uint16 EPWM14_DEL_ACTIVE:1;         // 13 Input Flag clear for EPWM14_DEL_ACTIVE Signal
    Uint16 EPWM15_DEL_ACTIVE:1;         // 14 Input Flag clear for EPWM15_DEL_ACTIVE Signal
    Uint16 EPWM16_DEL_ACTIVE:1;         // 15 Input Flag clear for EPWM16_DEL_ACTIVE Signal
    Uint16 EPWM17_DEL_ACTIVE:1;         // 16 Input Flag clear for EPWM17_DEL_ACTIVE Signal
    Uint16 EPWM18_DEL_ACTIVE:1;         // 17 Input Flag clear for EPWM18_DEL_ACTIVE Signal
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union XBARCLR7_REG {
    Uint32  all;
    struct  XBARCLR7_BITS  bit;
};

struct XBARCLR8_BITS {                  // bits description
    Uint16 ETPWM1_A0_sclk:1;            // 0 Input Flag clear for ETPWM1_A0_sclk Signal
    Uint16 ETPWM1_B0_sclk:1;            // 1 Input Flag clear for ETPWM1_B0_sclk Signal
    Uint16 ETPWM2_A0_sclk:1;            // 2 Input Flag clear for ETPWM2_A0_sclk Signal
    Uint16 ETPWM2_B0_sclk:1;            // 3 Input Flag clear for ETPWM2_B0_sclk Signal
    Uint16 ETPWM3_A0_sclk:1;            // 4 Input Flag clear for ETPWM3_A0_sclk Signal
    Uint16 ETPWM3_B0_sclk:1;            // 5 Input Flag clear for ETPWM3_B0_sclk Signal
    Uint16 ETPWM4_A0_sclk:1;            // 6 Input Flag clear for ETPWM4_A0_sclk Signal
    Uint16 ETPWM4_B0_sclk:1;            // 7 Input Flag clear for ETPWM4_B0_sclk Signal
    Uint16 ETPWM5_A0_sclk:1;            // 8 Input Flag clear for ETPWM5_A0_sclk Signal
    Uint16 ETPWM5_B0_sclk:1;            // 9 Input Flag clear for ETPWM5_B0_sclk Signal
    Uint16 ETPWM6_A0_sclk:1;            // 10 Input Flag clear for ETPWM6_A0_sclk Signal
    Uint16 ETPWM6_B0_sclk:1;            // 11 Input Flag clear for ETPWM6_B0_sclk Signal
    Uint16 ETPWM7_A0_sclk:1;            // 12 Input Flag clear for ETPWM7_A0_sclk Signal
    Uint16 ETPWM7_B0_sclk:1;            // 13 Input Flag clear for ETPWM7_B0_sclk Signal
    Uint16 ETPWM8_A0_sclk:1;            // 14 Input Flag clear for ETPWM8_A0_sclk Signal
    Uint16 ETPWM8_B0_sclk:1;            // 15 Input Flag clear for ETPWM8_B0_sclk Signal
    Uint16 ETPWM9_A0_sclk:1;            // 16 Input Flag clear for ETPWM9_A0_sclk Signal
    Uint16 ETPWM9_B0_sclk:1;            // 17 Input Flag clear for ETPWM9_B0_sclk Signal
    Uint16 ETPWM10_A0_sclk:1;           // 18 Input Flag clear for ETPWM10_A0_sclk Signal
    Uint16 ETPWM10_B0_sclk:1;           // 19 Input Flag clear for ETPWM10_B0_sclk Signal
    Uint16 ETPWM11_A0_sclk:1;           // 20 Input Flag clear for ETPWM11_A0_sclk Signal
    Uint16 ETPWM11_B0_sclk:1;           // 21 Input Flag clear for ETPWM11_B0_sclk Signal
    Uint16 ETPWM12_A0_sclk:1;           // 22 Input Flag clear for ETPWM12_A0_sclk Signal
    Uint16 ETPWM12_B0_sclk:1;           // 23 Input Flag clear for ETPWM12_B0_sclk Signal
    Uint16 ETPWM13_A0_sclk:1;           // 24 Input Flag clear for ETPWM13_A0_sclk Signal
    Uint16 ETPWM13_B0_sclk:1;           // 25 Input Flag clear for ETPWM13_B0_sclk Signal
    Uint16 ETPWM14_A0_sclk:1;           // 26 Input Flag clear for ETPWM14_A0_sclk Signal
    Uint16 ETPWM14_B0_sclk:1;           // 27 Input Flag clear for ETPWM14_B0_sclk Signal
    Uint16 ETPWM15_A0_sclk:1;           // 28 Input Flag clear for ETPWM15_A0_sclk Signal
    Uint16 ETPWM15_B0_sclk:1;           // 29 Input Flag clear for ETPWM15_B0_sclk Signal
    Uint16 ETPWM16_A0_sclk:1;           // 30 Input Flag clear for ETPWM16_A0_sclk Signal
    Uint16 ETPWM16_B0_sclk:1;           // 31 Input Flag clear for ETPWM16_B0_sclk Signal
};

union XBARCLR8_REG {
    Uint32  all;
    struct  XBARCLR8_BITS  bit;
};

struct XBARCLR9_BITS {                  // bits description
    Uint16 ETPWM17_A0_sclk:1;           // 0 Input Flag clear for ETPWM17_A0_sclk Signal
    Uint16 ETPWM17_B0_sclk:1;           // 1 Input Flag clear for ETPWM17_B0_sclk Signal
    Uint16 ETPWM18_A0_sclk:1;           // 2 Input Flag clear for ETPWM18_A0_sclk Signal
    Uint16 ETPWM18_B0_sclk:1;           // 3 Input Flag clear for ETPWM18_B0_sclk Signal
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:1;                     // 8 Reserved
    Uint16 rsvd6:1;                     // 9 Reserved
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:1;                     // 11 Reserved
    Uint16 rsvd9:1;                     // 12 Reserved
    Uint16 rsvd10:1;                    // 13 Reserved
    Uint16 rsvd11:1;                    // 14 Reserved
    Uint16 rsvd12:1;                    // 15 Reserved
    Uint16 rsvd13:1;                    // 16 Reserved
    Uint16 rsvd14:1;                    // 17 Reserved
    Uint16 rsvd15:1;                    // 18 Reserved
    Uint16 rsvd16:1;                    // 19 Reserved
    Uint16 rsvd17:1;                    // 20 Reserved
    Uint16 rsvd18:1;                    // 21 Reserved
    Uint16 rsvd19:1;                    // 22 Reserved
    Uint16 rsvd20:1;                    // 23 Reserved
    Uint16 rsvd21:1;                    // 24 Reserved
    Uint16 rsvd22:1;                    // 25 Reserved
    Uint16 rsvd23:1;                    // 26 Reserved
    Uint16 rsvd24:1;                    // 27 Reserved
    Uint16 rsvd25:1;                    // 28 Reserved
    Uint16 rsvd26:1;                    // 29 Reserved
    Uint16 rsvd27:1;                    // 30 Reserved
    Uint16 rsvd28:1;                    // 31 Reserved
};

union XBARCLR9_REG {
    Uint32  all;
    struct  XBARCLR9_BITS  bit;
};

struct XBARCLR10_BITS {                 // bits description
    Uint16 MDL1_OUTA:1;                 // 0 Input Flag clear for MDL1_OUTA Signal
    Uint16 MDL1_OUTB:1;                 // 1 Input Flag clear for MDL1_OUTB Signal
    Uint16 MDL2_OUTA:1;                 // 2 Input Flag clear for MDL2_OUTA Signal
    Uint16 MDL2_OUTB:1;                 // 3 Input Flag clear for MDL2_OUTB Signal
    Uint16 MDL3_OUTA:1;                 // 4 Input Flag clear for MDL3_OUTA Signal
    Uint16 MDL3_OUTB:1;                 // 5 Input Flag clear for MDL3_OUTB Signal
    Uint16 MDL4_OUTA:1;                 // 6 Input Flag clear for MDL4_OUTA Signal
    Uint16 MDL4_OUTB:1;                 // 7 Input Flag clear for MDL4_OUTB Signal
    Uint16 MDL5_OUTA:1;                 // 8 Input Flag clear for MDL5_OUTA Signal
    Uint16 MDL5_OUTB:1;                 // 9 Input Flag clear for MDL5_OUTB Signal
    Uint16 MDL6_OUTA:1;                 // 10 Input Flag clear for MDL6_OUTA Signal
    Uint16 MDL6_OUTB:1;                 // 11 Input Flag clear for MDL6_OUTB Signal
    Uint16 MDL7_OUTA:1;                 // 12 Input Flag clear for MDL7_OUTA Signal
    Uint16 MDL7_OUTB:1;                 // 13 Input Flag clear for MDL7_OUTB Signal
    Uint16 MDL8_OUTA:1;                 // 14 Input Flag clear for MDL8_OUTA Signal
    Uint16 MDL8_OUTB:1;                 // 15 Input Flag clear for MDL8_OUTB Signal
    Uint16 MDL9_OUTA:1;                 // 16 Input Flag clear for MDL9_OUTA Signal
    Uint16 MDL9_OUTB:1;                 // 17 Input Flag clear for MDL9_OUTB Signal
    Uint16 MDL10_OUTA:1;                // 18 Input Flag clear for MDL10_OUTA Signal
    Uint16 MDL10_OUTB:1;                // 19 Input Flag clear for MDL10_OUTB Signal
    Uint16 MDL11_OUTA:1;                // 20 Input Flag clear for MDL11_OUTA Signal
    Uint16 MDL11_OUTB:1;                // 21 Input Flag clear for MDL11_OUTB Signal
    Uint16 MDL12_OUTA:1;                // 22 Input Flag clear for MDL12_OUTA Signal
    Uint16 MDL12_OUTB:1;                // 23 Input Flag clear for MDL12_OUTB Signal
    Uint16 MDL13_OUTA:1;                // 24 Input Flag clear for MDL13_OUTA Signal
    Uint16 MDL13_OUTB:1;                // 25 Input Flag clear for MDL13_OUTB Signal
    Uint16 MDL14_OUTA:1;                // 26 Input Flag clear for MDL14_OUTA Signal
    Uint16 MDL14_OUTB:1;                // 27 Input Flag clear for MDL14_OUTB Signal
    Uint16 MDL15_OUTA:1;                // 28 Input Flag clear for MDL15_OUTA Signal
    Uint16 MDL15_OUTB:1;                // 29 Input Flag clear for MDL15_OUTB Signal
    Uint16 MDL16_OUTA:1;                // 30 Input Flag clear for MDL16_OUTA Signal
    Uint16 MDL16_OUTB:1;                // 31 Input Flag clear for MDL16_OUTB Signal
};

union XBARCLR10_REG {
    Uint32  all;
    struct  XBARCLR10_BITS  bit;
};

struct XBARCLR11_BITS {                 // bits description
    Uint16 MDL17_OUTA:1;                // 0 Input Flag clear for MDL17_OUTA Signal
    Uint16 MDL17_OUTB:1;                // 1 Input Flag clear for MDL17_OUTB Signal
    Uint16 MDL18_OUTA:1;                // 2 Input Flag clear for MDL18_OUTA Signal
    Uint16 MDL18_OUTB:1;                // 3 Input Flag clear for MDL18_OUTB Signal
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:1;                     // 8 Reserved
    Uint16 rsvd6:1;                     // 9 Reserved
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:1;                     // 11 Reserved
    Uint16 rsvd9:1;                     // 12 Reserved
    Uint16 rsvd10:1;                    // 13 Reserved
    Uint16 rsvd11:1;                    // 14 Reserved
    Uint16 rsvd12:1;                    // 15 Reserved
    Uint16 rsvd13:1;                    // 16 Reserved
    Uint16 rsvd14:1;                    // 17 Reserved
    Uint16 rsvd15:1;                    // 18 Reserved
    Uint16 rsvd16:1;                    // 19 Reserved
    Uint16 rsvd17:1;                    // 20 Reserved
    Uint16 rsvd18:1;                    // 21 Reserved
    Uint16 rsvd19:1;                    // 22 Reserved
    Uint16 rsvd20:1;                    // 23 Reserved
    Uint16 rsvd21:1;                    // 24 Reserved
    Uint16 rsvd22:1;                    // 25 Reserved
    Uint16 rsvd23:1;                    // 26 Reserved
    Uint16 rsvd24:1;                    // 27 Reserved
    Uint16 rsvd25:1;                    // 28 Reserved
    Uint16 rsvd26:1;                    // 29 Reserved
    Uint16 rsvd27:1;                    // 30 Reserved
    Uint16 rsvd28:1;                    // 31 Reserved
};

union XBARCLR11_REG {
    Uint32  all;
    struct  XBARCLR11_BITS  bit;
};

struct XBARCLR12_BITS {                 // bits description
    Uint16 CLB1_OUT0:1;                 // 0 Input Flag clear for CLB1_OUT0 Signal
    Uint16 CLB1_OUT1:1;                 // 1 Input Flag clear for CLB1_OUT1 Signal
    Uint16 CLB1_OUT2:1;                 // 2 Input Flag clear for CLB1_OUT2 Signal
    Uint16 CLB1_OUT3:1;                 // 3 Input Flag clear for CLB1_OUT3 Signal
    Uint16 CLB1_OUT6:1;                 // 4 Input Flag clear for CLB1_OUT6 Signal
    Uint16 CLB1_OUT7:1;                 // 5 Input Flag clear for CLB1_OUT7 Signal
    Uint16 CLB2_OUT0:1;                 // 6 Input Flag clear for CLB2_OUT0 Signal
    Uint16 CLB2_OUT1:1;                 // 7 Input Flag clear for CLB2_OUT1 Signal
    Uint16 CLB2_OUT2:1;                 // 8 Input Flag clear for CLB2_OUT2 Signal
    Uint16 CLB2_OUT3:1;                 // 9 Input Flag clear for CLB2_OUT3 Signal
    Uint16 CLB2_OUT6:1;                 // 10 Input Flag clear for CLB2_OUT6 Signal
    Uint16 CLB2_OUT7:1;                 // 11 Input Flag clear for CLB2_OUT7 Signal
    Uint16 CLB3_OUT0:1;                 // 12 Input Flag clear for CLB3_OUT0 Signal
    Uint16 CLB3_OUT1:1;                 // 13 Input Flag clear for CLB3_OUT1 Signal
    Uint16 CLB3_OUT2:1;                 // 14 Input Flag clear for CLB3_OUT2 Signal
    Uint16 CLB3_OUT3:1;                 // 15 Input Flag clear for CLB3_OUT3 Signal
    Uint16 CLB3_OUT6:1;                 // 16 Input Flag clear for CLB3_OUT6 Signal
    Uint16 CLB3_OUT7:1;                 // 17 Input Flag clear for CLB3_OUT7 Signal
    Uint16 CLB4_OUT0:1;                 // 18 Input Flag clear for CLB4_OUT0 Signal
    Uint16 CLB4_OUT1:1;                 // 19 Input Flag clear for CLB4_OUT1 Signal
    Uint16 CLB4_OUT2:1;                 // 20 Input Flag clear for CLB4_OUT2 Signal
    Uint16 CLB4_OUT3:1;                 // 21 Input Flag clear for CLB4_OUT3 Signal
    Uint16 CLB4_OUT6:1;                 // 22 Input Flag clear for CLB4_OUT6 Signal
    Uint16 CLB4_OUT7:1;                 // 23 Input Flag clear for CLB4_OUT7 Signal
    Uint16 CLB5_OUT0:1;                 // 24 Input Flag clear for CLB5_OUT0 Signal
    Uint16 CLB5_OUT1:1;                 // 25 Input Flag clear for CLB5_OUT1 Signal
    Uint16 CLB5_OUT2:1;                 // 26 Input Flag clear for CLB5_OUT2 Signal
    Uint16 CLB5_OUT3:1;                 // 27 Input Flag clear for CLB5_OUT3 Signal
    Uint16 CLB5_OUT6:1;                 // 28 Input Flag clear for CLB5_OUT6 Signal
    Uint16 CLB5_OUT7:1;                 // 29 Input Flag clear for CLB5_OUT7 Signal
    Uint16 CLB6_OUT0:1;                 // 30 Input Flag clear for CLB6_OUT0 Signal
    Uint16 CLB6_OUT1:1;                 // 31 Input Flag clear for CLB6_OUT1 Signal
};

union XBARCLR12_REG {
    Uint32  all;
    struct  XBARCLR12_BITS  bit;
};

struct XBARCLR13_BITS {                 // bits description
    Uint16 CLB6_OUT2:1;                 // 0 Input Flag clear for CLB6_OUT2 Signal
    Uint16 CLB6_OUT3:1;                 // 1 Input Flag clear for CLB6_OUT3 Signal
    Uint16 CLB6_OUT6:1;                 // 2 Input Flag clear for CLB6_OUT6 Signal
    Uint16 CLB6_OUT7:1;                 // 3 Input Flag clear for CLB6_OUT7 Signal
    Uint16 XTRIPOUT1:1;                 // 4 Input Flag clear for XTRIPOUT1 Signal
    Uint16 XTRIPOUT2:1;                 // 5 Input Flag clear for XTRIPOUT2 Signal
    Uint16 XTRIPOUT3:1;                 // 6 Input Flag clear for XTRIPOUT3 Signal
    Uint16 XTRIPOUT4:1;                 // 7 Input Flag clear for XTRIPOUT4 Signal
    Uint16 XTRIPOUT5:1;                 // 8 Input Flag clear for XTRIPOUT5 Signal
    Uint16 XTRIPOUT6:1;                 // 9 Input Flag clear for XTRIPOUT6 Signal
    Uint16 XTRIPOUT7:1;                 // 10 Input Flag clear for XTRIPOUT7 Signal
    Uint16 XTRIPOUT8:1;                 // 11 Input Flag clear for XTRIPOUT8 Signal
    Uint16 ADCA_EXTMUXSEL0:1;           // 12 Input Flag clear for ADCA_EXTMUXSEL0 Signal
    Uint16 ADCA_EXTMUXSEL1:1;           // 13 Input Flag clear for ADCA_EXTMUXSEL1 Signal
    Uint16 ADCA_EXTMUXSEL2:1;           // 14 Input Flag clear for ADCA_EXTMUXSEL2 Signal
    Uint16 ADCA_EXTMUXSEL3:1;           // 15 Input Flag clear for ADCA_EXTMUXSEL3 Signal
    Uint16 ADCB_EXTMUXSEL0:1;           // 16 Input Flag clear for ADCB_EXTMUXSEL0 Signal
    Uint16 ADCB_EXTMUXSEL1:1;           // 17 Input Flag clear for ADCB_EXTMUXSEL1 Signal
    Uint16 ADCB_EXTMUXSEL2:1;           // 18 Input Flag clear for ADCB_EXTMUXSEL2 Signal
    Uint16 ADCB_EXTMUXSEL3:1;           // 19 Input Flag clear for ADCB_EXTMUXSEL3 Signal
    Uint16 ADCC_EXTMUXSEL0:1;           // 20 Input Flag clear for ADCC_EXTMUXSEL0 Signal
    Uint16 ADCC_EXTMUXSEL1:1;           // 21 Input Flag clear for ADCC_EXTMUXSEL1 Signal
    Uint16 ADCC_EXTMUXSEL2:1;           // 22 Input Flag clear for ADCC_EXTMUXSEL2 Signal
    Uint16 ADCC_EXTMUXSEL3:1;           // 23 Input Flag clear for ADCC_EXTMUXSEL3 Signal
    Uint16 rsvd1:1;                     // 24 Reserved
    Uint16 rsvd2:1;                     // 25 Reserved
    Uint16 PIEERR:1;                    // 26 Input Flag clear for PIEERR Signal
    Uint16 ECCERR:1;                    // 27 Input Flag clear for ECCERR Signal
    Uint16 EPG1_EPGOUT0:1;              // 28 Input Flag clear for EPG1_EPGOUT0 Signal
    Uint16 EPG1_EPGOUT1:1;              // 29 Input Flag clear for EPG1_EPGOUT1 Signal
    Uint16 EPG1_EPGOUT2:1;              // 30 Input Flag clear for EPG1_EPGOUT2 Signal
    Uint16 EPG1_EPGOUT3:1;              // 31 Input Flag clear for EPG1_EPGOUT3 Signal
};

union XBARCLR13_REG {
    Uint32  all;
    struct  XBARCLR13_BITS  bit;
};

struct XBARCLR14_BITS {                 // bits description
    Uint16 SD3FLT1_COMPH:1;             // 0 Input Flag clear for SD3FLT1_COMPH Signal
    Uint16 SD3FLT1_COMPL:1;             // 1 Input Flag clear for SD3FLT1_COMPL Signal
    Uint16 SD3FLT2_COMPH:1;             // 2 Input Flag clear for SD3FLT2_COMPH Signal
    Uint16 SD3FLT2_COMPL:1;             // 3 Input Flag clear for SD3FLT2_COMPL Signal
    Uint16 SD3FLT3_COMPH:1;             // 4 Input Flag clear for SD3FLT3_COMPH Signal
    Uint16 SD3FLT3_COMPL:1;             // 5 Input Flag clear for SD3FLT3_COMPL Signal
    Uint16 SD3FLT4_COMPH:1;             // 6 Input Flag clear for SD3FLT4_COMPH Signal
    Uint16 SD3FLT4_COMPL:1;             // 7 Input Flag clear for SD3FLT4_COMPL Signal
    Uint16 SD4FLT1_COMPH:1;             // 8 Input Flag clear for SD4FLT1_COMPH Signal
    Uint16 SD4FLT1_COMPL:1;             // 9 Input Flag clear for SD4FLT1_COMPL Signal
    Uint16 SD4FLT2_COMPH:1;             // 10 Input Flag clear for SD4FLT2_COMPH Signal
    Uint16 SD4FLT2_COMPL:1;             // 11 Input Flag clear for SD4FLT2_COMPL Signal
    Uint16 SD4FLT3_COMPH:1;             // 12 Input Flag clear for SD4FLT3_COMPH Signal
    Uint16 SD4FLT3_COMPL:1;             // 13 Input Flag clear for SD4FLT3_COMPL Signal
    Uint16 SD4FLT4_COMPH:1;             // 14 Input Flag clear for SD4FLT4_COMPH Signal
    Uint16 SD4FLT4_COMPL:1;             // 15 Input Flag clear for SD4FLT4_COMPL Signal
    Uint16 rsvd1:1;                     // 16 Reserved
    Uint16 INPUTXBAR2_INPUT10:1;        // 17 Input Flag clear for INPUTXBAR2_INPUT10 Signal
    Uint16 INPUTXBAR2_INPUT11:1;        // 18 Input Flag clear for INPUTXBAR2_INPUT11 Signal
    Uint16 INPUTXBAR2_INPUT12:1;        // 19 Input Flag clear for INPUTXBAR2_INPUT12 Signal
    Uint16 INPUTXBAR2_INPUT13:1;        // 20 Input Flag clear for INPUTXBAR2_INPUT13 Signal
    Uint16 INPUTXBAR2_INPUT14:1;        // 21 Input Flag clear for INPUTXBAR2_INPUT14 Signal
    Uint16 INPUTXBAR2_INPUT7:1;         // 22 Input Flag clear for INPUTXBAR2_INPUT7 Signal
    Uint16 INPUTXBAR2_INPUT8:1;         // 23 Input Flag clear for INPUTXBAR2_INPUT8 Signal
    Uint16 INPUTXBAR2_INPUT9:1;         // 24 Input Flag clear for INPUTXBAR2_INPUT9 Signal
    Uint16 MCANB_FEVT0:1;               // 25 Input Flag clear for MCANB_FEVT0 Signal
    Uint16 MCANB_FEVT1:1;               // 26 Input Flag clear for MCANB_FEVT1 Signal
    Uint16 MCANB_FEVT2:1;               // 27 Input Flag clear for MCANB_FEVT2 Signal
    Uint16 FSIA_RX_TRIG1:1;             // 28 Input Flag clear for FSIA_RX_TRIG1 Signal
    Uint16 FSIB_RX_TRIG1:1;             // 29 Input Flag clear for FSIB_RX_TRIG1 Signal
    Uint16 FSIC_RX_TRIG1:1;             // 30 Input Flag clear for FSIC_RX_TRIG1 Signal
    Uint16 FSID_RX_TRIG1:1;             // 31 Input Flag clear for FSID_RX_TRIG1 Signal
};

union XBARCLR14_REG {
    Uint32  all;
    struct  XBARCLR14_BITS  bit;
};

struct XBARCLR15_BITS {                 // bits description
    Uint16 FSIRXA_TRIG_2:1;             // 0 Input Flag clear for FSIRXA_TRIG_2 Signal
    Uint16 FSIRXA_TRIG_3:1;             // 1 Input Flag clear for FSIRXA_TRIG_3 Signal
    Uint16 FSIRXB_TRIG_2:1;             // 2 Input Flag clear for FSIRXB_TRIG_2 Signal
    Uint16 FSIRXB_TRIG_3:1;             // 3 Input Flag clear for FSIRXB_TRIG_3 Signal
    Uint16 FSIRXC_TRIG_2:1;             // 4 Input Flag clear for FSIRXC_TRIG_2 Signal
    Uint16 FSIRXC_TRIG_3:1;             // 5 Input Flag clear for FSIRXC_TRIG_3 Signal
    Uint16 FSIRXD_TRIG_2:1;             // 6 Input Flag clear for FSIRXD_TRIG_2 Signal
    Uint16 FSIRXD_TRIG_3:1;             // 7 Input Flag clear for FSIRXD_TRIG_3 Signal
    Uint16 ECAP1_TRIPOUT:1;             // 8 Input Flag clear for ECAP1_TRIPOUT Signal
    Uint16 ECAP2_TRIPOUT:1;             // 9 Input Flag clear for ECAP2_TRIPOUT Signal
    Uint16 ECAP3_TRIPOUT:1;             // 10 Input Flag clear for ECAP3_TRIPOUT Signal
    Uint16 ECAP4_TRIPOUT:1;             // 11 Input Flag clear for ECAP4_TRIPOUT Signal
    Uint16 ECAP5_TRIPOUT:1;             // 12 Input Flag clear for ECAP5_TRIPOUT Signal
    Uint16 ECAP6_TRIPOUT:1;             // 13 Input Flag clear for ECAP6_TRIPOUT Signal
    Uint16 CPU1ERADEVT10:1;             // 14 Input Flag clear for CPU1ERADEVT10 Signal
    Uint16 CPU1ERADEVT11:1;             // 15 Input Flag clear for CPU1ERADEVT11 Signal
    Uint16 CPU1ERADEVT8:1;              // 16 Input Flag clear for CPU1ERADEVT8 Signal
    Uint16 CPU1ERADEVT9:1;              // 17 Input Flag clear for CPU1ERADEVT9 Signal
    Uint16 CPU1_ADCCHECKEVT1:1;         // 18 Input Flag clear for CPU1_ADCCHECKEVT1 Signal
    Uint16 CPU1_ADCCHECKEVT2:1;         // 19 Input Flag clear for CPU1_ADCCHECKEVT2 Signal
    Uint16 CPU1_ADCCHECKEVT3:1;         // 20 Input Flag clear for CPU1_ADCCHECKEVT3 Signal
    Uint16 CPU1_ADCCHECKEVT4:1;         // 21 Input Flag clear for CPU1_ADCCHECKEVT4 Signal
    Uint16 CPU2ERADEVT10:1;             // 22 Input Flag clear for CPU2ERADEVT10 Signal
    Uint16 CPU2ERADEVT11:1;             // 23 Input Flag clear for CPU2ERADEVT11 Signal
    Uint16 CPU2ERADEVT8:1;              // 24 Input Flag clear for CPU2ERADEVT8 Signal
    Uint16 CPU2ERADEVT9:1;              // 25 Input Flag clear for CPU2ERADEVT9 Signal
    Uint16 CPU2_ADCCHECKEVT1:1;         // 26 Input Flag clear for CPU2_ADCCHECKEVT1 Signal
    Uint16 CPU2_ADCCHECKEVT2:1;         // 27 Input Flag clear for CPU2_ADCCHECKEVT2 Signal
    Uint16 CPU2_ADCCHECKEVT3:1;         // 28 Input Flag clear for CPU2_ADCCHECKEVT3 Signal
    Uint16 CPU2_ADCCHECKEVT4:1;         // 29 Input Flag clear for CPU2_ADCCHECKEVT4 Signal
    Uint16 rsvd1:1;                     // 30 Reserved
    Uint16 rsvd2:1;                     // 31 Reserved
};

union XBARCLR15_REG {
    Uint32  all;
    struct  XBARCLR15_BITS  bit;
};

struct XBARCLR16_BITS {                 // bits description
    Uint16 CMPSS9_CTRIPH:1;             // 0 Input Flag clear for CMPSS9_CTRIPH Signal
    Uint16 CMPSS9_CTRIPL:1;             // 1 Input Flag clear for CMPSS9_CTRIPL Signal
    Uint16 CMPSS9_CTRIPOUTH:1;          // 2 Input Flag clear for CMPSS9_CTRIPOUTH Signal
    Uint16 CMPSS9_CTRIPOUTL:1;          // 3 Input Flag clear for CMPSS9_CTRIPOUTL Signal
    Uint16 CMPSS10_CTRIPH:1;            // 4 Input Flag clear for CMPSS10_CTRIPH Signal
    Uint16 CMPSS10_CTRIPL:1;            // 5 Input Flag clear for CMPSS10_CTRIPL Signal
    Uint16 CMPSS10_CTRIPOUTH:1;         // 6 Input Flag clear for CMPSS10_CTRIPOUTH Signal
    Uint16 CMPSS10_CTRIPOUTL:1;         // 7 Input Flag clear for CMPSS10_CTRIPOUTL Signal
    Uint16 CMPSS11_CTRIPH:1;            // 8 Input Flag clear for CMPSS11_CTRIPH Signal
    Uint16 CMPSS11_CTRIPL:1;            // 9 Input Flag clear for CMPSS11_CTRIPL Signal
    Uint16 CMPSS11_CTRIPOUTH:1;         // 10 Input Flag clear for CMPSS11_CTRIPOUTH Signal
    Uint16 CMPSS11_CTRIPOUTL:1;         // 11 Input Flag clear for CMPSS11_CTRIPOUTL Signal
    Uint16 CMPSS12_CTRIPH:1;            // 12 Input Flag clear for CMPSS12_CTRIPH Signal
    Uint16 CMPSS12_CTRIPL:1;            // 13 Input Flag clear for CMPSS12_CTRIPL Signal
    Uint16 CMPSS12_CTRIPOUTH:1;         // 14 Input Flag clear for CMPSS12_CTRIPOUTH Signal
    Uint16 CMPSS12_CTRIPOUTL:1;         // 15 Input Flag clear for CMPSS12_CTRIPOUTL Signal
    Uint16 rsvd1:1;                     // 16 Reserved
    Uint16 rsvd2:1;                     // 17 Reserved
    Uint16 rsvd3:1;                     // 18 Reserved
    Uint16 rsvd4:1;                     // 19 Reserved
    Uint16 rsvd5:1;                     // 20 Reserved
    Uint16 rsvd6:1;                     // 21 Reserved
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 CLB5_4_1:1;                  // 27 Input Flag clear for CLB5_4_1  Signal
    Uint16 CLB5_5_1:1;                  // 28 Input Flag clear for CLB5_5_1 Signal
    Uint16 CLB6_4_1:1;                  // 29 Input Flag clear for CLB6_4_1 Signal
    Uint16 CLB6_5_1:1;                  // 30 Input Flag clear for CLB6_5_1 Signal
    Uint16 XCLKOUT:1;                   // 31 Input Flag clear for XCLKOUT Signal
};

union XBARCLR16_REG {
    Uint32  all;
    struct  XBARCLR16_BITS  bit;
};

struct XBAR_REGS {
    union   XBARFLG1_REG                     XBARFLG1;                     // X-Bar Input Flag Register 1
    union   XBARFLG2_REG                     XBARFLG2;                     // X-Bar Input Flag Register 2
    union   XBARFLG3_REG                     XBARFLG3;                     // X-Bar Input Flag Register 3
    union   XBARFLG4_REG                     XBARFLG4;                     // X-Bar Input Flag Register 4
    union   XBARFLG5_REG                     XBARFLG5;                     // X-Bar Input Flag Register 5
    union   XBARFLG6_REG                     XBARFLG6;                     // X-Bar Input Flag Register 6
    union   XBARFLG7_REG                     XBARFLG7;                     // X-Bar Input Flag Register 7
    union   XBARFLG8_REG                     XBARFLG8;                     // X-Bar Input Flag Register 8
    union   XBARFLG9_REG                     XBARFLG9;                     // X-Bar Input Flag Register 9
    union   XBARFLG10_REG                    XBARFLG10;                    // X-Bar Input Flag Register 10
    union   XBARFLG11_REG                    XBARFLG11;                    // X-Bar Input Flag Register 11
    union   XBARFLG12_REG                    XBARFLG12;                    // X-Bar Input Flag Register 12
    union   XBARFLG13_REG                    XBARFLG13;                    // X-Bar Input Flag Register 13
    union   XBARFLG14_REG                    XBARFLG14;                    // X-Bar Input Flag Register 14
    union   XBARFLG15_REG                    XBARFLG15;                    // X-Bar Input Flag Register 15
    union   XBARFLG16_REG                    XBARFLG16;                    // X-Bar Input Flag Register 16
    union   XBARCLR1_REG                     XBARCLR1;                     // X-Bar Input Flag Clear Register 1
    union   XBARCLR2_REG                     XBARCLR2;                     // X-Bar Input Flag Clear Register 2
    union   XBARCLR3_REG                     XBARCLR3;                     // X-Bar Input Flag Clear Register 3
    union   XBARCLR4_REG                     XBARCLR4;                     // X-Bar Input Flag Clear Register 4
    union   XBARCLR5_REG                     XBARCLR5;                     // X-Bar Input Flag Clear Register 5
    union   XBARCLR6_REG                     XBARCLR6;                     // X-Bar Input Flag Clear Register 6
    union   XBARCLR7_REG                     XBARCLR7;                     // X-Bar Input Flag Clear Register 7
    union   XBARCLR8_REG                     XBARCLR8;                     // X-Bar Input Flag Clear Register 8
    union   XBARCLR9_REG                     XBARCLR9;                     // X-Bar Input Flag Clear Register 9
    union   XBARCLR10_REG                    XBARCLR10;                    // X-Bar Input Flag Clear Register 10
    union   XBARCLR11_REG                    XBARCLR11;                    // X-Bar Input Flag Clear Register 11
    union   XBARCLR12_REG                    XBARCLR12;                    // X-Bar Input Flag Clear Register 12
    union   XBARCLR13_REG                    XBARCLR13;                    // X-Bar Input Flag Clear Register 13
    union   XBARCLR14_REG                    XBARCLR14;                    // X-Bar Input Flag Clear Register 14
    union   XBARCLR15_REG                    XBARCLR15;                    // X-Bar Input Flag Clear Register 15
    union   XBARCLR16_REG                    XBARCLR16;                    // X-Bar Input Flag Clear Register 16
};

//---------------------------------------------------------------------------
// XBAR External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct XBAR_REGS XbarRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
