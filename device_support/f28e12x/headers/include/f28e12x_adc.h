//###########################################################################
//
// FILE:    f28e12x_adc.h
//
// TITLE:   Definitions for the ADC registers.
//
//###########################################################################
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

#ifndef F28E12X_ADC_H
#define F28E12X_ADC_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ADC Individual Register Bit Definitions:

struct ADCCTL1_BITS {                   // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 INTPULSEPOS:1;               // 2 ADC Interrupt Pulse Position
    Uint16 rsvd2:4;                     // 6:3 Reserved
    Uint16 ADCPWDNZ:1;                  // 7 ADC Power Down
    Uint16 ADCBSYCHN:4;                 // 11:8 ADC Busy Channel
    Uint16 rsvd3:1;                     // 12 Reserved
    Uint16 ADCBSY:1;                    // 13 ADC Busy
    Uint16 rsvd4:2;                     // 15:14 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ADCCTL1_REG {
    Uint32  all;
    struct  ADCCTL1_BITS  bit;
};

struct ADCCTL2_BITS {                   // bits description
    Uint16 PRESCALE:4;                  // 3:0 ADC Clock Prescaler
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:4;                     // 12:9 Reserved
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union ADCCTL2_REG {
    Uint32  all;
    struct  ADCCTL2_BITS  bit;
};

struct ADCINTSEL_BITS {                 // bits description
    Uint16 INT1SEL:6;                   // 5:0 ADCINT1 EOC Source Select
    Uint16 INT1CONT:1;                  // 6 ADCINT1 Continue to Interrupt Mode
    Uint16 INT1E:1;                     // 7 ADCINT1 Interrupt Enable
    Uint16 INT2SEL:6;                   // 13:8 ADCINT2 EOC Source Select
    Uint16 INT2CONT:1;                  // 14 ADCINT2 Continue to Interrupt Mode
    Uint16 INT2E:1;                     // 15 ADCINT2 Interrupt Enable
    Uint16 rsvd1:6;                     // 21:16 Reserved
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 rsvd3:1;                     // 23 Reserved
    Uint16 rsvd4:6;                     // 29:24 Reserved
    Uint16 rsvd5:1;                     // 30 Reserved
    Uint16 rsvd6:1;                     // 31 Reserved
};

union ADCINTSEL_REG {
    Uint32  all;
    struct  ADCINTSEL_BITS  bit;
};

struct ADCDMAINTSEL_BITS {              // bits description
    Uint16 DMAINT1SEL:6;                // 5:0 ADCDMAINT1 EOC Source Select
    Uint16 DMAINT1CONT:1;               // 6 ADCDMAINT1 Continue to Interrupt Mode
    Uint16 DMAINT1E:1;                  // 7 ADCDMAINT1 Interrupt Enable
    Uint16 DMAINT2SEL:6;                // 13:8 ADCDMAINT2 EOC Source Select
    Uint16 DMAINT2CONT:1;               // 14 ADCDMAINT2 Continue to Interrupt Mode
    Uint16 DMAINT2E:1;                  // 15 ADCDMAINT2 Interrupt Enable
    Uint16 rsvd1:6;                     // 21:16 Reserved
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 rsvd3:1;                     // 23 Reserved
    Uint16 rsvd4:6;                     // 29:24 Reserved
    Uint16 rsvd5:1;                     // 30 Reserved
    Uint16 rsvd6:1;                     // 31 Reserved
};

union ADCDMAINTSEL_REG {
    Uint32  all;
    struct  ADCDMAINTSEL_BITS  bit;
};

struct ADCRAWINTFLG_BITS {              // bits description
    Uint16 ADCRAWINT1:1;                // 0 ADC Raw Interrupt 1 Flag
    Uint16 ADCRAWINT2:1;                // 1 ADC Raw Interrupt 2 Flag
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 ADCDMARAWINT1:1;             // 16 ADC DMA Raw Interrupt 1 Flag
    Uint16 ADCDMARAWINT2:1;             // 17 ADC DMA Raw Interrupt 2 Flag
    Uint16 rsvd4:1;                     // 18 Reserved
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 rsvd6:12;                    // 31:20 Reserved
};

union ADCRAWINTFLG_REG {
    Uint32  all;
    struct  ADCRAWINTFLG_BITS  bit;
};

struct ADCINTFLG_BITS {                 // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Flag
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Flag
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:4;                     // 7:4 Reserved
    Uint16 ADCINT1RESULT:1;             // 8 ADC Interrupt 1 Results Ready
    Uint16 ADCINT2RESULT:1;             // 9 ADC Interrupt 2 Results Ready
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:4;                     // 15:12 Reserved
    Uint16 ADCDMAINT1:1;                // 16 ADC DMA Interrupt 1 Flag
    Uint16 ADCDMAINT2:1;                // 17 ADC DMA Interrupt 2 Flag
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:12;                    // 31:20 Reserved
};

union ADCINTFLG_REG {
    Uint32  all;
    struct  ADCINTFLG_BITS  bit;
};

struct ADCINTFLGFRC_BITS {              // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Flag Force
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Flag Force
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 ADCDMAINT1:1;                // 16 ADC DMA Interrupt 1 Flag Force
    Uint16 ADCDMAINT2:1;                // 17 ADC DMA Interrupt 2 Flag Force
    Uint16 rsvd4:1;                     // 18 Reserved
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 rsvd6:12;                    // 31:20 Reserved
};

union ADCINTFLGFRC_REG {
    Uint32  all;
    struct  ADCINTFLGFRC_BITS  bit;
};

struct ADCINTFLGCLR_BITS {              // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Flag Clear
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Flag Clear
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 ADCDMAINT1:1;                // 16 ADC DMA Interrupt 1 Flag Clear
    Uint16 ADCDMAINT2:1;                // 17 ADC DMA Interrupt 2 Flag Clear
    Uint16 rsvd4:1;                     // 18 Reserved
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 rsvd6:12;                    // 31:20 Reserved
};

union ADCINTFLGCLR_REG {
    Uint32  all;
    struct  ADCINTFLGCLR_BITS  bit;
};

struct ADCINTOVF_BITS {                 // bits description
    Uint16 ADCINT1OVF:1;                // 0 ADC Interrupt 1 Overflow Flags
    Uint16 ADCINT2OVF:1;                // 1 ADC Interrupt 2 Overflow Flags
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 ADCDMAINT1OVF:1;             // 16 ADC DMA Interrupt 1 Overflow Flags
    Uint16 ADCDMAINT2OVF:1;             // 17 ADC DMA Interrupt 2 Overflow Flags
    Uint16 rsvd4:1;                     // 18 Reserved
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 rsvd6:12;                    // 31:20 Reserved
};

union ADCINTOVF_REG {
    Uint32  all;
    struct  ADCINTOVF_BITS  bit;
};

struct ADCINTOVFCLR_BITS {              // bits description
    Uint16 ADCINT1OVF:1;                // 0 ADC Interrupt 1 Overflow Clear Bits
    Uint16 ADCINT2OVF:1;                // 1 ADC Interrupt 2 Overflow Clear Bits
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 ADCDMAINT1OVF:1;             // 16 ADC DMA Interrupt 1 Overflow Clear Bits
    Uint16 ADCDMAINT2OVF:1;             // 17 ADC DMA Interrupt 2 Overflow Clear Bits
    Uint16 rsvd4:1;                     // 18 Reserved
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 rsvd6:12;                    // 31:20 Reserved
};

union ADCINTOVFCLR_REG {
    Uint32  all;
    struct  ADCINTOVFCLR_BITS  bit;
};

struct ADCSOCPRICTL_BITS {              // bits description
    Uint16 SOCPRIORITY:2;               // 1:0 SOC Priority
    Uint16 rsvd1:4;                     // 5:2 Reserved
    Uint16 RRPOINTER:5;                 // 10:6 Round Robin Pointer
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ADCSOCPRICTL_REG {
    Uint32  all;
    struct  ADCSOCPRICTL_BITS  bit;
};

struct ADCINTSOCSEL1_BITS {             // bits description
    Uint16 SOC0:2;                      // 1:0 SOC0 ADC Interrupt Trigger Select
    Uint16 SOC1:2;                      // 3:2 SOC1 ADC Interrupt Trigger Select
    Uint16 SOC2:2;                      // 5:4 SOC2 ADC Interrupt Trigger Select
    Uint16 SOC3:2;                      // 7:6 SOC3 ADC Interrupt Trigger Select
    Uint16 SOC4:2;                      // 9:8 SOC4 ADC Interrupt Trigger Select
    Uint16 SOC5:2;                      // 11:10 SOC5 ADC Interrupt Trigger Select
    Uint16 SOC6:2;                      // 13:12 SOC6 ADC Interrupt Trigger Select
    Uint16 SOC7:2;                      // 15:14 SOC7 ADC Interrupt Trigger Select
    Uint16 SOC8:2;                      // 17:16 SOC8 ADC Interrupt Trigger Select
    Uint16 SOC9:2;                      // 19:18 SOC9 ADC Interrupt Trigger Select
    Uint16 SOC10:2;                     // 21:20 SOC10 ADC Interrupt Trigger Select
    Uint16 SOC11:2;                     // 23:22 SOC11 ADC Interrupt Trigger Select
    Uint16 SOC12:2;                     // 25:24 SOC12 ADC Interrupt Trigger Select
    Uint16 SOC13:2;                     // 27:26 SOC13 ADC Interrupt Trigger Select
    Uint16 SOC14:2;                     // 29:28 SOC14 ADC Interrupt Trigger Select
    Uint16 SOC15:2;                     // 31:30 SOC15 ADC Interrupt Trigger Select
};

union ADCINTSOCSEL1_REG {
    Uint32  all;
    struct  ADCINTSOCSEL1_BITS  bit;
};

struct ADCSOCFLG1_BITS {                // bits description
    Uint16 SOC0:1;                      // 0 SOC0 Start of Conversion Flag
    Uint16 SOC1:1;                      // 1 SOC1 Start of Conversion Flag
    Uint16 SOC2:1;                      // 2 SOC2 Start of Conversion Flag
    Uint16 SOC3:1;                      // 3 SOC3 Start of Conversion Flag
    Uint16 SOC4:1;                      // 4 SOC4 Start of Conversion Flag
    Uint16 SOC5:1;                      // 5 SOC5 Start of Conversion Flag
    Uint16 SOC6:1;                      // 6 SOC6 Start of Conversion Flag
    Uint16 SOC7:1;                      // 7 SOC7 Start of Conversion Flag
    Uint16 SOC8:1;                      // 8 SOC8 Start of Conversion Flag
    Uint16 SOC9:1;                      // 9 SOC9 Start of Conversion Flag
    Uint16 SOC10:1;                     // 10 SOC10 Start of Conversion Flag
    Uint16 SOC11:1;                     // 11 SOC11 Start of Conversion Flag
    Uint16 SOC12:1;                     // 12 SOC12 Start of Conversion Flag
    Uint16 SOC13:1;                     // 13 SOC13 Start of Conversion Flag
    Uint16 SOC14:1;                     // 14 SOC14 Start of Conversion Flag
    Uint16 SOC15:1;                     // 15 SOC15 Start of Conversion Flag
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCSOCFLG1_REG {
    Uint32  all;
    struct  ADCSOCFLG1_BITS  bit;
};

struct ADCSOCFRC1_BITS {                // bits description
    Uint16 SOC0:1;                      // 0 SOC0 Force Start of Conversion Bit
    Uint16 SOC1:1;                      // 1 SOC1 Force Start of Conversion Bit
    Uint16 SOC2:1;                      // 2 SOC2 Force Start of Conversion Bit
    Uint16 SOC3:1;                      // 3 SOC3 Force Start of Conversion Bit
    Uint16 SOC4:1;                      // 4 SOC4 Force Start of Conversion Bit
    Uint16 SOC5:1;                      // 5 SOC5 Force Start of Conversion Bit
    Uint16 SOC6:1;                      // 6 SOC6 Force Start of Conversion Bit
    Uint16 SOC7:1;                      // 7 SOC7 Force Start of Conversion Bit
    Uint16 SOC8:1;                      // 8 SOC8 Force Start of Conversion Bit
    Uint16 SOC9:1;                      // 9 SOC9 Force Start of Conversion Bit
    Uint16 SOC10:1;                     // 10 SOC10 Force Start of Conversion Bit
    Uint16 SOC11:1;                     // 11 SOC11 Force Start of Conversion Bit
    Uint16 SOC12:1;                     // 12 SOC12 Force Start of Conversion Bit
    Uint16 SOC13:1;                     // 13 SOC13 Force Start of Conversion Bit
    Uint16 SOC14:1;                     // 14 SOC14 Force Start of Conversion Bit
    Uint16 SOC15:1;                     // 15 SOC15 Force Start of Conversion Bit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCSOCFRC1_REG {
    Uint32  all;
    struct  ADCSOCFRC1_BITS  bit;
};

struct ADCSOCOVF1_BITS {                // bits description
    Uint16 SOC0OVF:1;                   // 0 SOC0 Start of Conversion Overflow Flag
    Uint16 SOC1OVF:1;                   // 1 SOC1 Start of Conversion Overflow Flag
    Uint16 SOC2OVF:1;                   // 2 SOC2 Start of Conversion Overflow Flag
    Uint16 SOC3OVF:1;                   // 3 SOC3 Start of Conversion Overflow Flag
    Uint16 SOC4OVF:1;                   // 4 SOC4 Start of Conversion Overflow Flag
    Uint16 SOC5OVF:1;                   // 5 SOC5 Start of Conversion Overflow Flag
    Uint16 SOC6OVF:1;                   // 6 SOC6 Start of Conversion Overflow Flag
    Uint16 SOC7OVF:1;                   // 7 SOC7 Start of Conversion Overflow Flag
    Uint16 SOC8OVF:1;                   // 8 SOC8 Start of Conversion Overflow Flag
    Uint16 SOC9OVF:1;                   // 9 SOC9 Start of Conversion Overflow Flag
    Uint16 SOC10OVF:1;                  // 10 SOC10 Start of Conversion Overflow Flag
    Uint16 SOC11OVF:1;                  // 11 SOC11 Start of Conversion Overflow Flag
    Uint16 SOC12OVF:1;                  // 12 SOC12 Start of Conversion Overflow Flag
    Uint16 SOC13OVF:1;                  // 13 SOC13 Start of Conversion Overflow Flag
    Uint16 SOC14OVF:1;                  // 14 SOC14 Start of Conversion Overflow Flag
    Uint16 SOC15OVF:1;                  // 15 SOC15 Start of Conversion Overflow Flag
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCSOCOVF1_REG {
    Uint32  all;
    struct  ADCSOCOVF1_BITS  bit;
};

struct ADCSOCOVFCLR1_BITS {             // bits description
    Uint16 SOC0OVF:1;                   // 0 SOC0 Clear Start of Conversion Overflow Bit
    Uint16 SOC1OVF:1;                   // 1 SOC1 Clear Start of Conversion Overflow Bit
    Uint16 SOC2OVF:1;                   // 2 SOC2 Clear Start of Conversion Overflow Bit
    Uint16 SOC3OVF:1;                   // 3 SOC3 Clear Start of Conversion Overflow Bit
    Uint16 SOC4OVF:1;                   // 4 SOC4 Clear Start of Conversion Overflow Bit
    Uint16 SOC5OVF:1;                   // 5 SOC5 Clear Start of Conversion Overflow Bit
    Uint16 SOC6OVF:1;                   // 6 SOC6 Clear Start of Conversion Overflow Bit
    Uint16 SOC7OVF:1;                   // 7 SOC7 Clear Start of Conversion Overflow Bit
    Uint16 SOC8OVF:1;                   // 8 SOC8 Clear Start of Conversion Overflow Bit
    Uint16 SOC9OVF:1;                   // 9 SOC9 Clear Start of Conversion Overflow Bit
    Uint16 SOC10OVF:1;                  // 10 SOC10 Clear Start of Conversion Overflow Bit
    Uint16 SOC11OVF:1;                  // 11 SOC11 Clear Start of Conversion Overflow Bit
    Uint16 SOC12OVF:1;                  // 12 SOC12 Clear Start of Conversion Overflow Bit
    Uint16 SOC13OVF:1;                  // 13 SOC13 Clear Start of Conversion Overflow Bit
    Uint16 SOC14OVF:1;                  // 14 SOC14 Clear Start of Conversion Overflow Bit
    Uint16 SOC15OVF:1;                  // 15 SOC15 Clear Start of Conversion Overflow Bit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCSOCOVFCLR1_REG {
    Uint32  all;
    struct  ADCSOCOVFCLR1_BITS  bit;
};

struct ADCSOC0CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC0 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC0 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC0 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC0 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC0 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC0CTL_REG {
    Uint32  all;
    struct  ADCSOC0CTL_BITS  bit;
};

struct ADCSOC1CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC1 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC1 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC1 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC1 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC1 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC1CTL_REG {
    Uint32  all;
    struct  ADCSOC1CTL_BITS  bit;
};

struct ADCSOC2CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC2 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC2 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC2 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC2 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC2 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC2CTL_REG {
    Uint32  all;
    struct  ADCSOC2CTL_BITS  bit;
};

struct ADCSOC3CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC3 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC3 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC3 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC3 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC3 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC3CTL_REG {
    Uint32  all;
    struct  ADCSOC3CTL_BITS  bit;
};

struct ADCSOC4CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC4 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC4 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC4 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC4 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC4 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC4CTL_REG {
    Uint32  all;
    struct  ADCSOC4CTL_BITS  bit;
};

struct ADCSOC5CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC5 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC5 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC5 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC5 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC5 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC5CTL_REG {
    Uint32  all;
    struct  ADCSOC5CTL_BITS  bit;
};

struct ADCSOC6CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC6 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC6 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC6 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC6 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC6 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC6CTL_REG {
    Uint32  all;
    struct  ADCSOC6CTL_BITS  bit;
};

struct ADCSOC7CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC7 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC7 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC7 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC7 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC7 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC7CTL_REG {
    Uint32  all;
    struct  ADCSOC7CTL_BITS  bit;
};

struct ADCSOC8CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC8 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC8 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC8 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC8 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC8 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC8CTL_REG {
    Uint32  all;
    struct  ADCSOC8CTL_BITS  bit;
};

struct ADCSOC9CTL_BITS {                // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC9 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC9 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC9 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC9 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC9 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC9CTL_REG {
    Uint32  all;
    struct  ADCSOC9CTL_BITS  bit;
};

struct ADCSOC10CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC10 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC10 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC10 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC10 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC10 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC10CTL_REG {
    Uint32  all;
    struct  ADCSOC10CTL_BITS  bit;
};

struct ADCSOC11CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC11 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC11 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC11 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC11 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC11 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC11CTL_REG {
    Uint32  all;
    struct  ADCSOC11CTL_BITS  bit;
};

struct ADCSOC12CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC12 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC12 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC12 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC12 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC12 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC12CTL_REG {
    Uint32  all;
    struct  ADCSOC12CTL_BITS  bit;
};

struct ADCSOC13CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC13 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC13 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC13 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC13 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC13 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC13CTL_REG {
    Uint32  all;
    struct  ADCSOC13CTL_BITS  bit;
};

struct ADCSOC14CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC14 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC14 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC14 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC14 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC14 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC14CTL_REG {
    Uint32  all;
    struct  ADCSOC14CTL_BITS  bit;
};

struct ADCSOC15CTL_BITS {               // bits description
    Uint16 ACQPS:8;                     // 7:0 SOC15 Acquisition Prescale
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 SAMPCAPRESETDISABLE:1;       // 9 SOC15 Sample Cap Reset Enable
    Uint16 SAMPCAPRESETSEL:1;           // 10 SOC15 Sample Cap Reset Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC15 Channel Select
    Uint16 TRIGSEL:5;                   // 24:20 SOC15 Trigger Source Select
    Uint16 rsvd3:7;                     // 31:25 Reserved
};

union ADCSOC15CTL_REG {
    Uint32  all;
    struct  ADCSOC15CTL_BITS  bit;
};

struct ADCEVTSTAT_BITS {                // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Flag
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Flag
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Flag
    Uint16 PPB1INLIMIT:1;               // 3 Post Processing Block 1 Within trip limit Flag
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Flag
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Flag
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Flag
    Uint16 PPB2INLIMIT:1;               // 7 Post Processing Block 2 Within trip limit Flag
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Flag
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Flag
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Flag
    Uint16 PPB3INLIMIT:1;               // 11 Post Processing Block 3 Within trip limit Flag
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ADCEVTSTAT_REG {
    Uint32  all;
    struct  ADCEVTSTAT_BITS  bit;
};

struct ADCEVTCLR_BITS {                 // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Clear
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Clear
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Clear
    Uint16 PPB1INLIMIT:1;               // 3 Post Processing Block 1 Within trip limit flag Clear
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Clear
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Clear
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Clear
    Uint16 PPB2INLIMIT:1;               // 7 Post Processing Block 2 Within trip limit flag Clear
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Clear
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Clear
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Clear
    Uint16 PPB3INLIMIT:1;               // 11 Post Processing Block 3 Within trip limit flag Clear
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ADCEVTCLR_REG {
    Uint32  all;
    struct  ADCEVTCLR_BITS  bit;
};

struct ADCEVTSEL_BITS {                 // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Event Enable
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Event Enable
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Event Enable
    Uint16 PPB1INLIMIT:1;               // 3 Post Processing Block 1 Within trip limit event enable
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Event Enable
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Event Enable
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Event Enable
    Uint16 PPB2INLIMIT:1;               // 7 Post Processing Block 2 Within trip limit event enable
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Event Enable
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Event Enable
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Event Enable
    Uint16 PPB3INLIMIT:1;               // 11 Post Processing Block 3 Within trip limit event enable
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ADCEVTSEL_REG {
    Uint32  all;
    struct  ADCEVTSEL_BITS  bit;
};

struct ADCEVTINTSEL_BITS {              // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Interrupt Enable
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Interrupt Enable
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Interrupt Enable
    Uint16 PPB1INLIMIT:1;               // 3 Post Processing Block 1 Within trip limit interrupt enable
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Interrupt Enable
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Interrupt Enable
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Interrupt Enable
    Uint16 PPB2INLIMIT:1;               // 7 Post Processing Block 2 Within trip limit interrupt enable
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Interrupt Enable
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Interrupt Enable
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Interrupt Enable
    Uint16 PPB3INLIMIT:1;               // 11 Post Processing Block 3 Within trip limit interrupt enable
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ADCEVTINTSEL_REG {
    Uint32  all;
    struct  ADCEVTINTSEL_BITS  bit;
};

struct ADCREV_BITS {                    // bits description
    Uint16 TYPE:8;                      // 7:0 ADC Type
    Uint32 REV:24;                      // 31:8 ADC Revision
};

union ADCREV_REG {
    Uint32  all;
    struct  ADCREV_BITS  bit;
};

struct ADCOFFTRIM_BITS {                // bits description
    Uint16 OFFTRIM:8;                   // 7:0 ADC Offset Trim
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCOFFTRIM_REG {
    Uint32  all;
    struct  ADCOFFTRIM_BITS  bit;
};

struct ADCPPB1CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block {#} Configuration
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 TWOSCOMPEN:1;                // 7 ADC Post Processing Block {#} Two's Complement Enable
    Uint16 rsvd3:8;                     // 15:8 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union ADCPPB1CONFIG_REG {
    Uint32  all;
    struct  ADCPPB1CONFIG_BITS  bit;
};

struct ADCPPB1OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:6;                    // 5:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB1OFFCAL_REG {
    Uint32  all;
    struct  ADCPPB1OFFCAL_BITS  bit;
};

struct ADCPPB1OFFREF_BITS {             // bits description
    Uint16 OFFREF:12;                   // 11:0 ADC Post Processing Block 1 Offset Reference
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB1OFFREF_REG {
    Uint32  all;
    struct  ADCPPB1OFFREF_BITS  bit;
};

struct ADCPPB1TRIPHI_BITS {             // bits description
    Uint16 LIMITHI:16;                  // 15:0 ADC Post Processing Block 1 Trip High Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB1TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB1TRIPHI_BITS  bit;
};

struct ADCPPB1TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 1 Trip Low Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB1TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB1TRIPLO_BITS  bit;
};

struct ADCPPB2CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block {#} Configuration
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 TWOSCOMPEN:1;                // 7 ADC Post Processing Block {#} Two's Complement Enable
    Uint16 rsvd3:8;                     // 15:8 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union ADCPPB2CONFIG_REG {
    Uint32  all;
    struct  ADCPPB2CONFIG_BITS  bit;
};

struct ADCPPB2OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:6;                    // 5:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB2OFFCAL_REG {
    Uint32  all;
    struct  ADCPPB2OFFCAL_BITS  bit;
};

struct ADCPPB2OFFREF_BITS {             // bits description
    Uint16 OFFREF:12;                   // 11:0 ADC Post Processing Block 2 Offset Reference
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB2OFFREF_REG {
    Uint32  all;
    struct  ADCPPB2OFFREF_BITS  bit;
};

struct ADCPPB2TRIPHI_BITS {             // bits description
    Uint16 LIMITHI:16;                  // 15:0 ADC Post Processing Block 2 Trip High Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB2TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB2TRIPHI_BITS  bit;
};

struct ADCPPB2TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 2 Trip Low Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB2TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB2TRIPLO_BITS  bit;
};

struct ADCPPB3CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block {#} Configuration
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 TWOSCOMPEN:1;                // 7 ADC Post Processing Block {#} Two's Complement Enable
    Uint16 rsvd3:8;                     // 15:8 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union ADCPPB3CONFIG_REG {
    Uint32  all;
    struct  ADCPPB3CONFIG_BITS  bit;
};

struct ADCPPB3OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:6;                    // 5:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB3OFFCAL_REG {
    Uint32  all;
    struct  ADCPPB3OFFCAL_BITS  bit;
};

struct ADCPPB3OFFREF_BITS {             // bits description
    Uint16 OFFREF:12;                   // 11:0 ADC Post Processing Block 3 Offset Reference
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB3OFFREF_REG {
    Uint32  all;
    struct  ADCPPB3OFFREF_BITS  bit;
};

struct ADCPPB3TRIPHI_BITS {             // bits description
    Uint16 LIMITHI:16;                  // 15:0 ADC Post Processing Block 3 Trip High Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB3TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB3TRIPHI_BITS  bit;
};

struct ADCPPB3TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 3 Trip Low Limit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCPPB3TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB3TRIPLO_BITS  bit;
};

struct ADCINTCYCLE_BITS {               // bits description
    Uint16 DELAY:6;                     // 5:0 Delay from ADCSOC fall edge to early interrupt generation.
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCINTCYCLE_REG {
    Uint32  all;
    struct  ADCINTCYCLE_BITS  bit;
};

struct ADCREV2_BITS {                   // bits description
    Uint16 WRAPPERTYPE:8;               // 7:0 ADC Wrapper Type
    Uint32 WRAPPERREV:24;               // 31:8 ADC Wrapper Revision
};

union ADCREV2_REG {
    Uint32  all;
    struct  ADCREV2_BITS  bit;
};

struct REP1CTL_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 MODULEBUSY:1;                // 3 ADC Trigger Repeater 1 Module Busy
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:1;                     // 6 Reserved
    Uint16 TRIGGEROVF:1;                // 7 ADC Trigger Repeater 1 Oversampled Trigger Overflow
    Uint16 TRIGGER:5;                   // 12:8 ADC Trigger Repeater 1 Trigger Select
    Uint16 rsvd7:3;                     // 15:13 Reserved
    Uint16 SYNCINSEL:3;                 // 18:16 ADC Trigger Repeater 1 Sync. In Select
    Uint16 rsvd8:4;                     // 22:19 Reserved
    Uint16 SWSYNC:1;                    // 23 ADC Trigger Repeater 1 Software Sync.
    Uint16 rsvd9:8;                     // 31:24 Reserved
};

union REP1CTL_REG {
    Uint32  all;
    struct  REP1CTL_BITS  bit;
};

struct REP1N_BITS {                     // bits description
    Uint16 NSEL:2;                      // 1:0 ADC Trigger Repeater 1 Trigger Number Selection
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 NCOUNT:3;                    // 18:16 ADC Trigger Repeater 1 Trigger Counter
    Uint16 rsvd2:13;                    // 31:19 Reserved
};

union REP1N_REG {
    Uint32  all;
    struct  REP1N_BITS  bit;
};

struct REP1SPREAD_BITS {                // bits description
    Uint16 SPREAD:16;                   // 15:0 ADC Trigger Repeater 1 Spread Delay Configuration
    Uint16 SPREADCOUNT:16;              // 31:16 ADC Trigger Repeater 1 Spread Delay Status
};

union REP1SPREAD_REG {
    Uint32  all;
    struct  REP1SPREAD_BITS  bit;
};

struct REP1FRC_BITS {                   // bits description
    Uint16 SWFRC:1;                     // 0 ADC Trigger Repeater 1 Software Force
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union REP1FRC_REG {
    Uint32  all;
    struct  REP1FRC_BITS  bit;
};

struct ADCPPB1LIMIT_BITS {              // bits description
    Uint16 LIMIT:2;                     // 1:0 Post Processing Block 1 Limit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPB1LIMIT_REG {
    Uint32  all;
    struct  ADCPPB1LIMIT_BITS  bit;
};

struct ADCPPBP1PCOUNT_BITS {            // bits description
    Uint16 PCOUNT:3;                    // 2:0 Post Processing Block 1 Partial Count
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCPPBP1PCOUNT_REG {
    Uint32  all;
    struct  ADCPPBP1PCOUNT_BITS  bit;
};

struct ADCPPB1CONFIG2_BITS {            // bits description
    Uint16 SHIFT:3;                     // 2:0 Post Processing Block 1 Right Shift
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 SYNCINSEL:3;                 // 6:4 Post Processing Block 1 Sync. Input Select
    Uint16 rsvd2:4;                     // 10:7 Reserved
    Uint16 SWSYNC:1;                    // 11 Post Processing Block 1 Software Force Sync.
    Uint16 OSINTSEL:1;                  // 12 Post Processing Block 1 Interrupt Source Select
    Uint16 rsvd3:2;                     // 14:13 Reserved
    Uint16 COMPSEL:1;                   // 15 Post Processing Block 1 Compare Source Select
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union ADCPPB1CONFIG2_REG {
    Uint32  all;
    struct  ADCPPB1CONFIG2_BITS  bit;
};

struct ADCPPB1PSUM_BITS {               // bits description
    Uint16 PSUM:16;                     // 15:0 Post Processing Block 1 Oversampling Partial Sum
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB1PSUM_REG {
    Uint32  all;
    struct  ADCPPB1PSUM_BITS  bit;
};

struct ADC_LITE_REGS {
    union   ADCCTL1_REG                      ADCCTL1;                      // ADC Control 1 Register
    union   ADCCTL2_REG                      ADCCTL2;                      // ADC Control 2 Register
    Uint16                                   rsvd1[4];                     // Reserved
    union   ADCINTSEL_REG                    ADCINTSEL;                    // ADC Interrupt 1, 2, 3 and 4 Selection Register
    union   ADCDMAINTSEL_REG                 ADCDMAINTSEL;                 // ADC DMA Interrupt 1, 2, 3 and 4 Selection Register
    union   ADCRAWINTFLG_REG                 ADCRAWINTFLG;                 // ADC Raw Interrupt Flag Register
    union   ADCINTFLG_REG                    ADCINTFLG;                    // ADC Interrupt Flag Register
    union   ADCINTFLGFRC_REG                 ADCINTFLGFRC;                 // ADC Interrupt Flag Force Register
    union   ADCINTFLGCLR_REG                 ADCINTFLGCLR;                 // ADC Interrupt Flag Clear Register
    union   ADCINTOVF_REG                    ADCINTOVF;                    // ADC Interrupt Overflow Register
    union   ADCINTOVFCLR_REG                 ADCINTOVFCLR;                 // ADC Interrupt Overflow Clear Register
    union   ADCSOCPRICTL_REG                 ADCSOCPRICTL;                 // ADC SOC Priority Control Register
    union   ADCINTSOCSEL1_REG                ADCINTSOCSEL1;                // ADC Interrupt SOC Selection 1 Register
    Uint16                                   rsvd2[2];                     // Reserved
    union   ADCSOCFLG1_REG                   ADCSOCFLG1;                   // ADC SOC Flag 1 Register
    union   ADCSOCFRC1_REG                   ADCSOCFRC1;                   // ADC SOC Force 1 Register
    union   ADCSOCOVF1_REG                   ADCSOCOVF1;                   // ADC SOC Overflow 1 Register
    union   ADCSOCOVFCLR1_REG                ADCSOCOVFCLR1;                // ADC SOC Overflow Clear 1 Register
    union   ADCSOC0CTL_REG                   ADCSOC0CTL;                   // ADC SOC0 Control Register
    union   ADCSOC1CTL_REG                   ADCSOC1CTL;                   // ADC SOC1 Control Register
    union   ADCSOC2CTL_REG                   ADCSOC2CTL;                   // ADC SOC2 Control Register
    union   ADCSOC3CTL_REG                   ADCSOC3CTL;                   // ADC SOC3 Control Register
    union   ADCSOC4CTL_REG                   ADCSOC4CTL;                   // ADC SOC4 Control Register
    union   ADCSOC5CTL_REG                   ADCSOC5CTL;                   // ADC SOC5 Control Register
    union   ADCSOC6CTL_REG                   ADCSOC6CTL;                   // ADC SOC6 Control Register
    union   ADCSOC7CTL_REG                   ADCSOC7CTL;                   // ADC SOC7 Control Register
    union   ADCSOC8CTL_REG                   ADCSOC8CTL;                   // ADC SOC8 Control Register
    union   ADCSOC9CTL_REG                   ADCSOC9CTL;                   // ADC SOC9 Control Register
    union   ADCSOC10CTL_REG                  ADCSOC10CTL;                  // ADC SOC10 Control Register
    union   ADCSOC11CTL_REG                  ADCSOC11CTL;                  // ADC SOC11 Control Register
    union   ADCSOC12CTL_REG                  ADCSOC12CTL;                  // ADC SOC12 Control Register
    union   ADCSOC13CTL_REG                  ADCSOC13CTL;                  // ADC SOC13 Control Register
    union   ADCSOC14CTL_REG                  ADCSOC14CTL;                  // ADC SOC14 Control Register
    union   ADCSOC15CTL_REG                  ADCSOC15CTL;                  // ADC SOC15 Control Register
    Uint16                                   rsvd3[32];                    // Reserved
    union   ADCEVTSTAT_REG                   ADCEVTSTAT;                   // ADC Event Status Register
    union   ADCEVTCLR_REG                    ADCEVTCLR;                    // ADC Event Clear Register
    union   ADCEVTSEL_REG                    ADCEVTSEL;                    // ADC Event Selection Register
    union   ADCEVTINTSEL_REG                 ADCEVTINTSEL;                 // ADC Event Interrupt Selection Register
    Uint16                                   rsvd4[4];                     // Reserved
    union   ADCREV_REG                       ADCREV;                       // ADC Revision Register
    union   ADCOFFTRIM_REG                   ADCOFFTRIM;                   // ADC Offset Trim Register 1
    Uint16                                   rsvd5[10];                    // Reserved
    union   ADCPPB1CONFIG_REG                ADCPPB1CONFIG;                // ADC PPB{#} Config Register
    Uint16                                   rsvd6[2];                     // Reserved
    union   ADCPPB1OFFCAL_REG                ADCPPB1OFFCAL;                // ADC PPB1 Offset Calibration Register
    union   ADCPPB1OFFREF_REG                ADCPPB1OFFREF;                // ADC PPB1 Offset Reference Register
    union   ADCPPB1TRIPHI_REG                ADCPPB1TRIPHI;                // ADC PPB1 Trip High Register
    union   ADCPPB1TRIPLO_REG                ADCPPB1TRIPLO;                // ADC PPB1 Trip Low/Trigger Time Stamp Register
    Uint16                                   rsvd7[4];                     // Reserved
    union   ADCPPB2CONFIG_REG                ADCPPB2CONFIG;                // ADC PPB{#} Config Register
    Uint16                                   rsvd8[2];                     // Reserved
    union   ADCPPB2OFFCAL_REG                ADCPPB2OFFCAL;                // ADC PPB2 Offset Calibration Register
    union   ADCPPB2OFFREF_REG                ADCPPB2OFFREF;                // ADC PPB2 Offset Reference Register
    union   ADCPPB2TRIPHI_REG                ADCPPB2TRIPHI;                // ADC PPB2 Trip High Register
    union   ADCPPB2TRIPLO_REG                ADCPPB2TRIPLO;                // ADC PPB2 Trip Low/Trigger Time Stamp Register
    Uint16                                   rsvd9[4];                     // Reserved
    union   ADCPPB3CONFIG_REG                ADCPPB3CONFIG;                // ADC PPB{#} Config Register
    Uint16                                   rsvd10[2];                    // Reserved
    union   ADCPPB3OFFCAL_REG                ADCPPB3OFFCAL;                // ADC PPB3 Offset Calibration Register
    union   ADCPPB3OFFREF_REG                ADCPPB3OFFREF;                // ADC PPB3 Offset Reference Register
    union   ADCPPB3TRIPHI_REG                ADCPPB3TRIPHI;                // ADC PPB3 Trip High Register
    union   ADCPPB3TRIPLO_REG                ADCPPB3TRIPLO;                // ADC PPB3 Trip Low/Trigger Time Stamp Register
    Uint16                                   rsvd11[20];                   // Reserved
    union   ADCINTCYCLE_REG                  ADCINTCYCLE;                  // ADC Early Interrupt Generation Cycle
    Uint32                                   ADCINLTRIM1;                  // ADC Linearity Trim 1 Register
    Uint32                                   ADCINLTRIM2;                  // ADC Linearity Trim 2 Register
    Uint16                                   rsvd12[8];                    // Reserved
    union   ADCREV2_REG                      ADCREV2;                      // ADC Wrapper Revision Register
    Uint16                                   rsvd13[16];                   // Reserved
    union   REP1CTL_REG                      REP1CTL;                      // ADC Trigger Repeater 1 Control Register
    union   REP1N_REG                        REP1N;                        // ADC Trigger Repeater 1 N Select Register
    Uint16                                   rsvd14[2];                    // Reserved
    union   REP1SPREAD_REG                   REP1SPREAD;                   // ADC Trigger Repeater 1 Spread Select Register
    union   REP1FRC_REG                      REP1FRC;                      // ADC Trigger Repeater 1 Software Force Register
    Uint16                                   rsvd15[22];                   // Reserved
    union   ADCPPB1LIMIT_REG                 ADCPPB1LIMIT;                 // ADC PPB1Conversion Count Limit Register
    union   ADCPPBP1PCOUNT_REG               ADCPPBP1PCOUNT;               // ADC PPB1 Partial Conversion Count Register
    union   ADCPPB1CONFIG2_REG               ADCPPB1CONFIG2;               // ADC PPB1 Sum Shift Register
    union   ADCPPB1PSUM_REG                  ADCPPB1PSUM;                  // ADC PPB1 Partial Sum Register
};

struct ADCRESULT0_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT0_REG {
    Uint16  all;
    struct  ADCRESULT0_BITS  bit;
};

struct ADCRESULT1_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT1_REG {
    Uint16  all;
    struct  ADCRESULT1_BITS  bit;
};

struct ADCRESULT2_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT2_REG {
    Uint16  all;
    struct  ADCRESULT2_BITS  bit;
};

struct ADCRESULT3_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT3_REG {
    Uint16  all;
    struct  ADCRESULT3_BITS  bit;
};

struct ADCRESULT4_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT4_REG {
    Uint16  all;
    struct  ADCRESULT4_BITS  bit;
};

struct ADCRESULT5_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT5_REG {
    Uint16  all;
    struct  ADCRESULT5_BITS  bit;
};

struct ADCRESULT6_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT6_REG {
    Uint16  all;
    struct  ADCRESULT6_BITS  bit;
};

struct ADCRESULT7_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT7_REG {
    Uint16  all;
    struct  ADCRESULT7_BITS  bit;
};

struct ADCRESULT8_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT8_REG {
    Uint16  all;
    struct  ADCRESULT8_BITS  bit;
};

struct ADCRESULT9_BITS {                // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT9_REG {
    Uint16  all;
    struct  ADCRESULT9_BITS  bit;
};

struct ADCRESULT10_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT10_REG {
    Uint16  all;
    struct  ADCRESULT10_BITS  bit;
};

struct ADCRESULT11_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT11_REG {
    Uint16  all;
    struct  ADCRESULT11_BITS  bit;
};

struct ADCRESULT12_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT12_REG {
    Uint16  all;
    struct  ADCRESULT12_BITS  bit;
};

struct ADCRESULT13_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT13_REG {
    Uint16  all;
    struct  ADCRESULT13_BITS  bit;
};

struct ADCRESULT14_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT14_REG {
    Uint16  all;
    struct  ADCRESULT14_BITS  bit;
};

struct ADCRESULT15_BITS {               // bits description
    Uint16 RESULT:12;                   // 11:0 ADC Result
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCRESULT15_REG {
    Uint16  all;
    struct  ADCRESULT15_BITS  bit;
};

struct ADCPPB1RESULT_BITS {             // bits description
    Uint16 PPBRESULT:13;                // 12:0 ADC Post Processing Block Result
    Uint32 SIGN:19;                     // 31:13 Sign Extended Bits
};

union ADCPPB1RESULT_REG {
    Uint32  all;
    struct  ADCPPB1RESULT_BITS  bit;
};

struct ADCPPB2RESULT_BITS {             // bits description
    Uint16 PPBRESULT:13;                // 12:0 ADC Post Processing Block Result
    Uint32 SIGN:19;                     // 31:13 Sign Extended Bits
};

union ADCPPB2RESULT_REG {
    Uint32  all;
    struct  ADCPPB2RESULT_BITS  bit;
};

struct ADCPPB3RESULT_BITS {             // bits description
    Uint16 PPBRESULT:13;                // 12:0 ADC Post Processing Block Result
    Uint32 SIGN:19;                     // 31:13 Sign Extended Bits
};

union ADCPPB3RESULT_REG {
    Uint32  all;
    struct  ADCPPB3RESULT_BITS  bit;
};

struct ADCPPB1SUM_BITS {                // bits description
    Uint16 SUM:16;                      // 15:0 Post Processing Block 1 Oversampling Sum
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB1SUM_REG {
    Uint32  all;
    struct  ADCPPB1SUM_BITS  bit;
};

struct ADCPPB1COUNT_BITS {              // bits description
    Uint16 COUNT:4;                     // 3:0 Post Processing Block 1 Final Count
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union ADCPPB1COUNT_REG {
    Uint16  all;
    struct  ADCPPB1COUNT_BITS  bit;
};

struct ADC_LITE_RESULT_REGS {
    union   ADCRESULT0_REG                   ADCRESULT0;                   // ADC Result 0 Register
    union   ADCRESULT1_REG                   ADCRESULT1;                   // ADC Result 1 Register
    union   ADCRESULT2_REG                   ADCRESULT2;                   // ADC Result 2 Register
    union   ADCRESULT3_REG                   ADCRESULT3;                   // ADC Result 3 Register
    union   ADCRESULT4_REG                   ADCRESULT4;                   // ADC Result 4 Register
    union   ADCRESULT5_REG                   ADCRESULT5;                   // ADC Result 5 Register
    union   ADCRESULT6_REG                   ADCRESULT6;                   // ADC Result 6 Register
    union   ADCRESULT7_REG                   ADCRESULT7;                   // ADC Result 7 Register
    union   ADCRESULT8_REG                   ADCRESULT8;                   // ADC Result 8 Register
    union   ADCRESULT9_REG                   ADCRESULT9;                   // ADC Result 9 Register
    union   ADCRESULT10_REG                  ADCRESULT10;                  // ADC Result 10 Register
    union   ADCRESULT11_REG                  ADCRESULT11;                  // ADC Result 11 Register
    union   ADCRESULT12_REG                  ADCRESULT12;                  // ADC Result 12 Register
    union   ADCRESULT13_REG                  ADCRESULT13;                  // ADC Result 13 Register
    union   ADCRESULT14_REG                  ADCRESULT14;                  // ADC Result 14 Register
    union   ADCRESULT15_REG                  ADCRESULT15;                  // ADC Result 15 Register
    Uint16                                   rsvd1[16];                    // Reserved
    union   ADCPPB1RESULT_REG                ADCPPB1RESULT;                // ADC Post Processing Block 1 Result Register
    union   ADCPPB2RESULT_REG                ADCPPB2RESULT;                // ADC Post Processing Block 2 Result Register
    union   ADCPPB3RESULT_REG                ADCPPB3RESULT;                // ADC Post Processing Block 3 Result Register
    Uint16                                   rsvd2[2];                     // Reserved
    union   ADCPPB1SUM_REG                   ADCPPB1SUM;                   // ADC PPB 1 Final Sum Result Register
    union   ADCPPB1COUNT_REG                 ADCPPB1COUNT;                 // ADC PPB1 Final Conversion Count Register
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//
extern volatile struct ADC_LITE_RESULT_REGS AdcaResultRegs;
extern volatile struct ADC_LITE_REGS AdcaRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
