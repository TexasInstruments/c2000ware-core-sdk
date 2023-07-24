//###########################################################################
//
// FILE:    f28p65x_adc.h
//
// TITLE:   Definitions for the ADC registers.
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

#ifndef F28P65X_ADC_H
#define F28P65X_ADC_H

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
    Uint16 EXTMUXPRESELECTEN:1;         // 14 External Mux Preselect Enable
    Uint16 TDMAEN:1;                    // 15 Enable Alternate DMA Timings
};

union ADCCTL1_REG {
    Uint16  all;
    struct  ADCCTL1_BITS  bit;
};

struct ADCCTL2_BITS {                   // bits description
    Uint16 PRESCALE:4;                  // 3:0 ADC Clock Prescaler
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 RESOLUTION:1;                // 6 SOC Conversion Resolution
    Uint16 SIGNALMODE:1;                // 7 SOC Signaling Mode
    Uint16 OFFTRIMMODE:1;               // 8 Offset Trim Mode
    Uint16 rsvd2:4;                     // 12:9 Reserved
    Uint16 rsvd3:3;                     // 15:13 Reserved
};

union ADCCTL2_REG {
    Uint16  all;
    struct  ADCCTL2_BITS  bit;
};

struct ADCBURSTCTL_BITS {               // bits description
    Uint16 BURSTTRIGSEL:7;              // 6:0 SOC Burst Trigger Source Select
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 BURSTSIZE:4;                 // 11:8 SOC Burst Size Select
    Uint16 rsvd2:3;                     // 14:12 Reserved
    Uint16 BURSTEN:1;                   // 15 SOC Burst Mode Enable
};

union ADCBURSTCTL_REG {
    Uint16  all;
    struct  ADCBURSTCTL_BITS  bit;
};

struct ADCINTFLG_BITS {                 // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Flag
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Flag
    Uint16 ADCINT3:1;                   // 2 ADC Interrupt 3 Flag
    Uint16 ADCINT4:1;                   // 3 ADC Interrupt 4 Flag
    Uint16 ADCINT1RESULT:1;             // 4 ADC Interrupt 1 Results Ready
    Uint16 ADCINT2RESULT:1;             // 5 ADC Interrupt 2 Results Ready
    Uint16 ADCINT3RESULT:1;             // 6 ADC Interrupt 3 Results Ready
    Uint16 ADCINT4RESULT:1;             // 7 ADC Interrupt 4 Results Ready
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union ADCINTFLG_REG {
    Uint16  all;
    struct  ADCINTFLG_BITS  bit;
};

struct ADCINTFLGCLR_BITS {              // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Flag Clear
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Flag Clear
    Uint16 ADCINT3:1;                   // 2 ADC Interrupt 3 Flag Clear
    Uint16 ADCINT4:1;                   // 3 ADC Interrupt 4 Flag Clear
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union ADCINTFLGCLR_REG {
    Uint16  all;
    struct  ADCINTFLGCLR_BITS  bit;
};

struct ADCINTOVF_BITS {                 // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Overflow Flags
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Overflow Flags
    Uint16 ADCINT3:1;                   // 2 ADC Interrupt 3 Overflow Flags
    Uint16 ADCINT4:1;                   // 3 ADC Interrupt 4 Overflow Flags
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union ADCINTOVF_REG {
    Uint16  all;
    struct  ADCINTOVF_BITS  bit;
};

struct ADCINTOVFCLR_BITS {              // bits description
    Uint16 ADCINT1:1;                   // 0 ADC Interrupt 1 Overflow Clear Bits
    Uint16 ADCINT2:1;                   // 1 ADC Interrupt 2 Overflow Clear Bits
    Uint16 ADCINT3:1;                   // 2 ADC Interrupt 3 Overflow Clear Bits
    Uint16 ADCINT4:1;                   // 3 ADC Interrupt 4 Overflow Clear Bits
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union ADCINTOVFCLR_REG {
    Uint16  all;
    struct  ADCINTOVFCLR_BITS  bit;
};

struct ADCINTSEL1N2_BITS {              // bits description
    Uint16 INT1SEL:5;                   // 4:0 ADCINT1 EOC Source Select
    Uint16 INT1E:1;                     // 5 ADCINT1 Interrupt Enable
    Uint16 INT1CONT:1;                  // 6 ADCINT1 Continue to Interrupt Mode
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 INT2SEL:5;                   // 12:8 ADCINT2 EOC Source Select
    Uint16 INT2E:1;                     // 13 ADCINT2 Interrupt Enable
    Uint16 INT2CONT:1;                  // 14 ADCINT2 Continue to Interrupt Mode
    Uint16 rsvd2:1;                     // 15 Reserved
};

union ADCINTSEL1N2_REG {
    Uint16  all;
    struct  ADCINTSEL1N2_BITS  bit;
};

struct ADCINTSEL3N4_BITS {              // bits description
    Uint16 INT3SEL:5;                   // 4:0 ADCINT3 EOC Source Select
    Uint16 INT3E:1;                     // 5 ADCINT3 Interrupt Enable
    Uint16 INT3CONT:1;                  // 6 ADCINT3 Continue to Interrupt Mode
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 INT4SEL:5;                   // 12:8 ADCINT4 EOC Source Select
    Uint16 INT4E:1;                     // 13 ADCINT4 Interrupt Enable
    Uint16 INT4CONT:1;                  // 14 ADCINT4 Continue to Interrupt Mode
    Uint16 rsvd2:1;                     // 15 Reserved
};

union ADCINTSEL3N4_REG {
    Uint16  all;
    struct  ADCINTSEL3N4_BITS  bit;
};

struct ADCSOCPRICTL_BITS {              // bits description
    Uint16 SOCPRIORITY:5;               // 4:0 SOC Priority
    Uint16 RRPOINTER:5;                 // 9:5 Round Robin Pointer
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCSOCPRICTL_REG {
    Uint16  all;
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
};

union ADCINTSOCSEL1_REG {
    Uint16  all;
    struct  ADCINTSOCSEL1_BITS  bit;
};

struct ADCINTSOCSEL2_BITS {             // bits description
    Uint16 SOC8:2;                      // 1:0 SOC8 ADC Interrupt Trigger Select
    Uint16 SOC9:2;                      // 3:2 SOC9 ADC Interrupt Trigger Select
    Uint16 SOC10:2;                     // 5:4 SOC10 ADC Interrupt Trigger Select
    Uint16 SOC11:2;                     // 7:6 SOC11 ADC Interrupt Trigger Select
    Uint16 SOC12:2;                     // 9:8 SOC12 ADC Interrupt Trigger Select
    Uint16 SOC13:2;                     // 11:10 SOC13 ADC Interrupt Trigger Select
    Uint16 SOC14:2;                     // 13:12 SOC14 ADC Interrupt Trigger Select
    Uint16 SOC15:2;                     // 15:14 SOC15 ADC Interrupt Trigger Select
};

union ADCINTSOCSEL2_REG {
    Uint16  all;
    struct  ADCINTSOCSEL2_BITS  bit;
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
};

union ADCSOCFLG1_REG {
    Uint16  all;
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
};

union ADCSOCFRC1_REG {
    Uint16  all;
    struct  ADCSOCFRC1_BITS  bit;
};

struct ADCSOCOVF1_BITS {                // bits description
    Uint16 SOC0:1;                      // 0 SOC0 Start of Conversion Overflow Flag
    Uint16 SOC1:1;                      // 1 SOC1 Start of Conversion Overflow Flag
    Uint16 SOC2:1;                      // 2 SOC2 Start of Conversion Overflow Flag
    Uint16 SOC3:1;                      // 3 SOC3 Start of Conversion Overflow Flag
    Uint16 SOC4:1;                      // 4 SOC4 Start of Conversion Overflow Flag
    Uint16 SOC5:1;                      // 5 SOC5 Start of Conversion Overflow Flag
    Uint16 SOC6:1;                      // 6 SOC6 Start of Conversion Overflow Flag
    Uint16 SOC7:1;                      // 7 SOC7 Start of Conversion Overflow Flag
    Uint16 SOC8:1;                      // 8 SOC8 Start of Conversion Overflow Flag
    Uint16 SOC9:1;                      // 9 SOC9 Start of Conversion Overflow Flag
    Uint16 SOC10:1;                     // 10 SOC10 Start of Conversion Overflow Flag
    Uint16 SOC11:1;                     // 11 SOC11 Start of Conversion Overflow Flag
    Uint16 SOC12:1;                     // 12 SOC12 Start of Conversion Overflow Flag
    Uint16 SOC13:1;                     // 13 SOC13 Start of Conversion Overflow Flag
    Uint16 SOC14:1;                     // 14 SOC14 Start of Conversion Overflow Flag
    Uint16 SOC15:1;                     // 15 SOC15 Start of Conversion Overflow Flag
};

union ADCSOCOVF1_REG {
    Uint16  all;
    struct  ADCSOCOVF1_BITS  bit;
};

struct ADCSOCOVFCLR1_BITS {             // bits description
    Uint16 SOC0:1;                      // 0 SOC0 Clear Start of Conversion Overflow Bit
    Uint16 SOC1:1;                      // 1 SOC1 Clear Start of Conversion Overflow Bit
    Uint16 SOC2:1;                      // 2 SOC2 Clear Start of Conversion Overflow Bit
    Uint16 SOC3:1;                      // 3 SOC3 Clear Start of Conversion Overflow Bit
    Uint16 SOC4:1;                      // 4 SOC4 Clear Start of Conversion Overflow Bit
    Uint16 SOC5:1;                      // 5 SOC5 Clear Start of Conversion Overflow Bit
    Uint16 SOC6:1;                      // 6 SOC6 Clear Start of Conversion Overflow Bit
    Uint16 SOC7:1;                      // 7 SOC7 Clear Start of Conversion Overflow Bit
    Uint16 SOC8:1;                      // 8 SOC8 Clear Start of Conversion Overflow Bit
    Uint16 SOC9:1;                      // 9 SOC9 Clear Start of Conversion Overflow Bit
    Uint16 SOC10:1;                     // 10 SOC10 Clear Start of Conversion Overflow Bit
    Uint16 SOC11:1;                     // 11 SOC11 Clear Start of Conversion Overflow Bit
    Uint16 SOC12:1;                     // 12 SOC12 Clear Start of Conversion Overflow Bit
    Uint16 SOC13:1;                     // 13 SOC13 Clear Start of Conversion Overflow Bit
    Uint16 SOC14:1;                     // 14 SOC14 Clear Start of Conversion Overflow Bit
    Uint16 SOC15:1;                     // 15 SOC15 Clear Start of Conversion Overflow Bit
};

union ADCSOCOVFCLR1_REG {
    Uint16  all;
    struct  ADCSOCOVFCLR1_BITS  bit;
};

struct ADCSOC0CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC0 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC0 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC0 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC0 External Channel Mux Select
};

union ADCSOC0CTL_REG {
    Uint32  all;
    struct  ADCSOC0CTL_BITS  bit;
};

struct ADCSOC1CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC1 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC1 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC1 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC1 External Channel Mux Select
};

union ADCSOC1CTL_REG {
    Uint32  all;
    struct  ADCSOC1CTL_BITS  bit;
};

struct ADCSOC2CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC2 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC2 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC2 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC2 External Channel Mux Select
};

union ADCSOC2CTL_REG {
    Uint32  all;
    struct  ADCSOC2CTL_BITS  bit;
};

struct ADCSOC3CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC3 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC3 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC3 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC3 External Channel Mux Select
};

union ADCSOC3CTL_REG {
    Uint32  all;
    struct  ADCSOC3CTL_BITS  bit;
};

struct ADCSOC4CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC4 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC4 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC4 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC4 External Channel Mux Select
};

union ADCSOC4CTL_REG {
    Uint32  all;
    struct  ADCSOC4CTL_BITS  bit;
};

struct ADCSOC5CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC5 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC5 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC5 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC5 External Channel Mux Select
};

union ADCSOC5CTL_REG {
    Uint32  all;
    struct  ADCSOC5CTL_BITS  bit;
};

struct ADCSOC6CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC6 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC6 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC6 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC6 External Channel Mux Select
};

union ADCSOC6CTL_REG {
    Uint32  all;
    struct  ADCSOC6CTL_BITS  bit;
};

struct ADCSOC7CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC7 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC7 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC7 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC7 External Channel Mux Select
};

union ADCSOC7CTL_REG {
    Uint32  all;
    struct  ADCSOC7CTL_BITS  bit;
};

struct ADCSOC8CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC8 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC8 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC8 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC8 External Channel Mux Select
};

union ADCSOC8CTL_REG {
    Uint32  all;
    struct  ADCSOC8CTL_BITS  bit;
};

struct ADCSOC9CTL_BITS {                // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC9 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC9 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC9 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC9 External Channel Mux Select
};

union ADCSOC9CTL_REG {
    Uint32  all;
    struct  ADCSOC9CTL_BITS  bit;
};

struct ADCSOC10CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC10 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC10 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC10 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC10 External Channel Mux Select
};

union ADCSOC10CTL_REG {
    Uint32  all;
    struct  ADCSOC10CTL_BITS  bit;
};

struct ADCSOC11CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC11 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC11 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC11 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC11 External Channel Mux Select
};

union ADCSOC11CTL_REG {
    Uint32  all;
    struct  ADCSOC11CTL_BITS  bit;
};

struct ADCSOC12CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC12 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC12 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC12 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC12 External Channel Mux Select
};

union ADCSOC12CTL_REG {
    Uint32  all;
    struct  ADCSOC12CTL_BITS  bit;
};

struct ADCSOC13CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC13 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC13 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC13 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC13 External Channel Mux Select
};

union ADCSOC13CTL_REG {
    Uint32  all;
    struct  ADCSOC13CTL_BITS  bit;
};

struct ADCSOC14CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC14 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC14 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC14 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC14 External Channel Mux Select
};

union ADCSOC14CTL_REG {
    Uint32  all;
    struct  ADCSOC14CTL_BITS  bit;
};

struct ADCSOC15CTL_BITS {               // bits description
    Uint16 ACQPS:9;                     // 8:0 SOC15 Acquisition Prescale
    Uint16 rsvd1:1;                     // 9 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint32 CHSEL:5;                     // 19:15 SOC15 Channel Select
    Uint16 TRIGSEL:7;                   // 26:20 SOC15 Trigger Source Select
    Uint16 rsvd4:1;                     // 27 Reserved
    Uint16 EXTCHSEL:4;                  // 31:28 SOC15 External Channel Mux Select
};

union ADCSOC15CTL_REG {
    Uint32  all;
    struct  ADCSOC15CTL_BITS  bit;
};

struct ADCEVTSTAT_BITS {                // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Flag
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Flag
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Flag
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Flag
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Flag
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Flag
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Flag
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Flag
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Flag
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 PPB4TRIPHI:1;                // 12 Post Processing Block 4 Trip High Flag
    Uint16 PPB4TRIPLO:1;                // 13 Post Processing Block 4 Trip Low Flag
    Uint16 PPB4ZERO:1;                  // 14 Post Processing Block 4 Zero Crossing Flag
    Uint16 rsvd4:1;                     // 15 Reserved
};

union ADCEVTSTAT_REG {
    Uint16  all;
    struct  ADCEVTSTAT_BITS  bit;
};

struct ADCEVTCLR_BITS {                 // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Clear
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Clear
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Clear
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Clear
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Clear
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Clear
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Clear
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Clear
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Clear
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 PPB4TRIPHI:1;                // 12 Post Processing Block 4 Trip High Clear
    Uint16 PPB4TRIPLO:1;                // 13 Post Processing Block 4 Trip Low Clear
    Uint16 PPB4ZERO:1;                  // 14 Post Processing Block 4 Zero Crossing Clear
    Uint16 rsvd4:1;                     // 15 Reserved
};

union ADCEVTCLR_REG {
    Uint16  all;
    struct  ADCEVTCLR_BITS  bit;
};

struct ADCEVTSEL_BITS {                 // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Event Enable
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Event Enable
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Event Enable
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Event Enable
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Event Enable
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Event Enable
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Event Enable
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Event Enable
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Event Enable
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 PPB4TRIPHI:1;                // 12 Post Processing Block 4 Trip High Event Enable
    Uint16 PPB4TRIPLO:1;                // 13 Post Processing Block 4 Trip Low Event Enable
    Uint16 PPB4ZERO:1;                  // 14 Post Processing Block 4 Zero Crossing Event Enable
    Uint16 rsvd4:1;                     // 15 Reserved
};

union ADCEVTSEL_REG {
    Uint16  all;
    struct  ADCEVTSEL_BITS  bit;
};

struct ADCEVTINTSEL_BITS {              // bits description
    Uint16 PPB1TRIPHI:1;                // 0 Post Processing Block 1 Trip High Interrupt Enable
    Uint16 PPB1TRIPLO:1;                // 1 Post Processing Block 1 Trip Low Interrupt Enable
    Uint16 PPB1ZERO:1;                  // 2 Post Processing Block 1 Zero Crossing Interrupt Enable
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PPB2TRIPHI:1;                // 4 Post Processing Block 2 Trip High Interrupt Enable
    Uint16 PPB2TRIPLO:1;                // 5 Post Processing Block 2 Trip Low Interrupt Enable
    Uint16 PPB2ZERO:1;                  // 6 Post Processing Block 2 Zero Crossing Interrupt Enable
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 PPB3TRIPHI:1;                // 8 Post Processing Block 3 Trip High Interrupt Enable
    Uint16 PPB3TRIPLO:1;                // 9 Post Processing Block 3 Trip Low Interrupt Enable
    Uint16 PPB3ZERO:1;                  // 10 Post Processing Block 3 Zero Crossing Interrupt Enable
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 PPB4TRIPHI:1;                // 12 Post Processing Block 4 Trip High Interrupt Enable
    Uint16 PPB4TRIPLO:1;                // 13 Post Processing Block 4 Trip Low Interrupt Enable
    Uint16 PPB4ZERO:1;                  // 14 Post Processing Block 4 Zero Crossing Interrupt Enable
    Uint16 rsvd4:1;                     // 15 Reserved
};

union ADCEVTINTSEL_REG {
    Uint16  all;
    struct  ADCEVTINTSEL_BITS  bit;
};

struct ADCOSDETECT_BITS {               // bits description
    Uint16 DETECTCFG:3;                 // 2:0 ADC Opens and Shorts Detect Configuration
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union ADCOSDETECT_REG {
    Uint16  all;
    struct  ADCOSDETECT_BITS  bit;
};

struct ADCCOUNTER_BITS {                // bits description
    Uint16 FREECOUNT:12;                // 11:0 ADC Free Running Counter Value
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCCOUNTER_REG {
    Uint16  all;
    struct  ADCCOUNTER_BITS  bit;
};

struct ADCREV_BITS {                    // bits description
    Uint16 TYPE:8;                      // 7:0 ADC Type
    Uint16 REV:8;                       // 15:8 ADC Revision
};

union ADCREV_REG {
    Uint16  all;
    struct  ADCREV_BITS  bit;
};

struct ADCOFFTRIM_BITS {                // bits description
    Uint16 OFFTRIM:8;                   // 7:0 ADC Offset Trim 12B SE Even
    Uint16 OFFTRIM12BSEODD:8;           // 15:8 ADC Offset Trim 12B SE Odd
};

union ADCOFFTRIM_REG {
    Uint16  all;
    struct  ADCOFFTRIM_BITS  bit;
};

struct ADCOFFTRIM2_BITS {               // bits description
    Uint16 OFFTRIM16BSEEVEN:8;          // 7:0 ADC Offset Trim 16B SE Even
    Uint16 OFFTRIM16BSEODD:8;           // 15:8 ADC Offset Trim 16B SE Odd
};

union ADCOFFTRIM2_REG {
    Uint16  all;
    struct  ADCOFFTRIM2_BITS  bit;
};

struct ADCOFFTRIM3_BITS {               // bits description
    Uint16 OFFTRIM12BDE:8;              // 7:0 ADC Offset Trim 12B DE
    Uint16 OFFTRIM16BDE:8;              // 15:8 ADC Offset Trim 16B DE
};

union ADCOFFTRIM3_REG {
    Uint16  all;
    struct  ADCOFFTRIM3_BITS  bit;
};

struct ADCPPB1CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block 1 Configuration
    Uint16 TWOSCOMPEN:1;                // 4 ADC Post Processing Block 1 Two's Complement Enable
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 ABSEN:1;                     // 6 ADC Post Processing Block 1 Absolute Enable
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union ADCPPB1CONFIG_REG {
    Uint16  all;
    struct  ADCPPB1CONFIG_BITS  bit;
};

struct ADCPPB1STAMP_BITS {              // bits description
    Uint16 DLYSTAMP:12;                 // 11:0 ADC Post Processing Block 1 Delay Time Stamp
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCPPB1STAMP_REG {
    Uint16  all;
    struct  ADCPPB1STAMP_BITS  bit;
};

struct ADCPPB1OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:10;                   // 9:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1OFFCAL_REG {
    Uint16  all;
    struct  ADCPPB1OFFCAL_BITS  bit;
};

struct ADCPPB1TRIPHI_BITS {             // bits description
    Uint32 LIMITHI:24;                  // 23:0 ADC Post Processing Block 1 Trip High Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB1TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB1TRIPHI_BITS  bit;
};

struct ADCPPB1TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 1 Trip Low Limit
    Uint16 LSIGN:1;                     // 16 Low Limit Sign Bit
    Uint16 rsvd1:2;                     // 18:17 Reserved
    Uint16 LIMITLO2EN:1;                // 19 Extended Low Limit 2 Enable
    Uint16 REQSTAMP:12;                 // 31:20 ADC Post Processing Block 1 Request Time Stamp
};

union ADCPPB1TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB1TRIPLO_BITS  bit;
};

struct ADCPPB2CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block 2 Configuration
    Uint16 TWOSCOMPEN:1;                // 4 ADC Post Processing Block 2 Two's Complement Enable
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 ABSEN:1;                     // 6 ADC Post Processing Block 2 Absolute Enable
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union ADCPPB2CONFIG_REG {
    Uint16  all;
    struct  ADCPPB2CONFIG_BITS  bit;
};

struct ADCPPB2STAMP_BITS {              // bits description
    Uint16 DLYSTAMP:12;                 // 11:0 ADC Post Processing Block 2 Delay Time Stamp
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCPPB2STAMP_REG {
    Uint16  all;
    struct  ADCPPB2STAMP_BITS  bit;
};

struct ADCPPB2OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:10;                   // 9:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2OFFCAL_REG {
    Uint16  all;
    struct  ADCPPB2OFFCAL_BITS  bit;
};

struct ADCPPB2TRIPHI_BITS {             // bits description
    Uint32 LIMITHI:24;                  // 23:0 ADC Post Processing Block 2 Trip High Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB2TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB2TRIPHI_BITS  bit;
};

struct ADCPPB2TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 2 Trip Low Limit
    Uint16 LSIGN:1;                     // 16 Low Limit Sign Bit
    Uint16 rsvd1:2;                     // 18:17 Reserved
    Uint16 LIMITLO2EN:1;                // 19 Extended Low Limit 2 Enable
    Uint16 REQSTAMP:12;                 // 31:20 ADC Post Processing Block 2 Request Time Stamp
};

union ADCPPB2TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB2TRIPLO_BITS  bit;
};

struct ADCPPB3CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block 3 Configuration
    Uint16 TWOSCOMPEN:1;                // 4 ADC Post Processing Block 3 Two's Complement Enable
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 ABSEN:1;                     // 6 ADC Post Processing Block 3 Absolute Enable
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union ADCPPB3CONFIG_REG {
    Uint16  all;
    struct  ADCPPB3CONFIG_BITS  bit;
};

struct ADCPPB3STAMP_BITS {              // bits description
    Uint16 DLYSTAMP:12;                 // 11:0 ADC Post Processing Block 3 Delay Time Stamp
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCPPB3STAMP_REG {
    Uint16  all;
    struct  ADCPPB3STAMP_BITS  bit;
};

struct ADCPPB3OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:10;                   // 9:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3OFFCAL_REG {
    Uint16  all;
    struct  ADCPPB3OFFCAL_BITS  bit;
};

struct ADCPPB3TRIPHI_BITS {             // bits description
    Uint32 LIMITHI:24;                  // 23:0 ADC Post Processing Block 3 Trip High Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB3TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB3TRIPHI_BITS  bit;
};

struct ADCPPB3TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 3 Trip Low Limit
    Uint16 LSIGN:1;                     // 16 Low Limit Sign Bit
    Uint16 rsvd1:2;                     // 18:17 Reserved
    Uint16 LIMITLO2EN:1;                // 19 Extended Low Limit 2 Enable
    Uint16 REQSTAMP:12;                 // 31:20 ADC Post Processing Block 3 Request Time Stamp
};

union ADCPPB3TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB3TRIPLO_BITS  bit;
};

struct ADCPPB4CONFIG_BITS {             // bits description
    Uint16 CONFIG:4;                    // 3:0 ADC Post Processing Block 4 Configuration
    Uint16 TWOSCOMPEN:1;                // 4 ADC Post Processing Block 4 Two's Complement Enable
    Uint16 CBCEN:1;                     // 5 Cycle By Cycle Enable
    Uint16 ABSEN:1;                     // 6 ADC Post Processing Block 4 Absolute Enable
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union ADCPPB4CONFIG_REG {
    Uint16  all;
    struct  ADCPPB4CONFIG_BITS  bit;
};

struct ADCPPB4STAMP_BITS {              // bits description
    Uint16 DLYSTAMP:12;                 // 11:0 ADC Post Processing Block 4 Delay Time Stamp
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ADCPPB4STAMP_REG {
    Uint16  all;
    struct  ADCPPB4STAMP_BITS  bit;
};

struct ADCPPB4OFFCAL_BITS {             // bits description
    Uint16 OFFCAL:10;                   // 9:0 ADC Post Processing Block Offset Correction
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4OFFCAL_REG {
    Uint16  all;
    struct  ADCPPB4OFFCAL_BITS  bit;
};

struct ADCPPB4TRIPHI_BITS {             // bits description
    Uint32 LIMITHI:24;                  // 23:0 ADC Post Processing Block 4 Trip High Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB4TRIPHI_REG {
    Uint32  all;
    struct  ADCPPB4TRIPHI_BITS  bit;
};

struct ADCPPB4TRIPLO_BITS {             // bits description
    Uint16 LIMITLO:16;                  // 15:0 ADC Post Processing Block 4 Trip Low Limit
    Uint16 LSIGN:1;                     // 16 Low Limit Sign Bit
    Uint16 rsvd1:2;                     // 18:17 Reserved
    Uint16 LIMITLO2EN:1;                // 19 Extended Low Limit 2 Enable
    Uint16 REQSTAMP:12;                 // 31:20 ADC Post Processing Block 4 Request Time Stamp
};

union ADCPPB4TRIPLO_REG {
    Uint32  all;
    struct  ADCPPB4TRIPLO_BITS  bit;
};

struct ADCSAFECHECKRESEN_BITS {         // bits description
    Uint16 SOC0CHKEN:2;                 // 1:0 ADC SOC0 Safety Checker Result Enable
    Uint16 SOC1CHKEN:2;                 // 3:2 ADC SOC1 Safety Checker Result Enable
    Uint16 SOC2CHKEN:2;                 // 5:4 ADC SOC2 Safety Checker Result Enable
    Uint16 SOC3CHKEN:2;                 // 7:6 ADC SOC3 Safety Checker Result Enable
    Uint16 SOC4CHKEN:2;                 // 9:8 ADC SOC4 Safety Checker Result Enable
    Uint16 SOC5CHKEN:2;                 // 11:10 ADC SOC5 Safety Checker Result Enable
    Uint16 SOC6CHKEN:2;                 // 13:12 ADC SOC6 Safety Checker Result Enable
    Uint16 SOC7CHKEN:2;                 // 15:14 ADC SOC7 Safety Checker Result Enable
    Uint16 SOC8CHKEN:2;                 // 17:16 ADC SOC8 Safety Checker Result Enable
    Uint16 SOC9CHKEN:2;                 // 19:18 ADC SOC9 Safety Checker Result Enable
    Uint16 SOC10CHKEN:2;                // 21:20 ADC SOC10 Safety Checker Result Enable
    Uint16 SOC11CHKEN:2;                // 23:22 ADC SOC11 Safety Checker Result Enable
    Uint16 SOC12CHKEN:2;                // 25:24 ADC SOC12 Safety Checker Result Enable
    Uint16 SOC13CHKEN:2;                // 27:26 ADC SOC13 Safety Checker Result Enable
    Uint16 SOC14CHKEN:2;                // 29:28 ADC SOC14 Safety Checker Result Enable
    Uint16 SOC15CHKEN:2;                // 31:30 ADC SOC15 Safety Checker Result Enable
};

union ADCSAFECHECKRESEN_REG {
    Uint32  all;
    struct  ADCSAFECHECKRESEN_BITS  bit;
};

struct ADCREV2_BITS {                   // bits description
    Uint16 WRAPPERTYPE:8;               // 7:0 ADC Wrapper Type
    Uint16 WRAPPERREV:8;                // 15:8 ADC Wrapper Revision
};

union ADCREV2_REG {
    Uint16  all;
    struct  ADCREV2_BITS  bit;
};

struct REP1CTL_BITS {                   // bits description
    Uint16 MODE:1;                      // 0 ADC Trigger Repeater 1 Mode Select
    Uint16 ACTIVEMODE:1;                // 1 ADC Trigger Repeater 1 Active Mode
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 MODULEBUSY:1;                // 3 ADC Trigger Repeater 1 Module Busy
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 PHASEOVF:1;                  // 6 ADC Trigger Repeater 1 Phase Delay Overflow
    Uint16 TRIGGEROVF:1;                // 7 ADC Trigger Repeater 1 Oversampled Trigger Overflow
    Uint16 TRIGGER:7;                   // 14:8 ADC Trigger Repeater 1 Trigger Select
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 SYNCINSEL:5;                 // 20:16 ADC Trigger Repeater 1 Sync. In Select
    Uint16 rsvd5:2;                     // 22:21 Reserved
    Uint16 SWSYNC:1;                    // 23 ADC Trigger Repeater 1 Software Sync.
    Uint16 rsvd6:8;                     // 31:24 Reserved
};

union REP1CTL_REG {
    Uint32  all;
    struct  REP1CTL_BITS  bit;
};

struct REP1N_BITS {                     // bits description
    Uint16 NSEL:7;                      // 6:0 ADC Trigger Repeater 1 Trigger Number Selection
    Uint16 rsvd1:9;                     // 15:7 Reserved
    Uint16 NCOUNT:7;                    // 22:16 ADC Trigger Repeater 1 Trigger Counter
    Uint16 rsvd2:9;                     // 31:23 Reserved
};

union REP1N_REG {
    Uint32  all;
    struct  REP1N_BITS  bit;
};

struct REP1PHASE_BITS {                 // bits description
    Uint16 PHASE:16;                    // 15:0 ADC Trigger Repeater 1 Phase Delay Configuration
    Uint16 PHASECOUNT:16;               // 31:16 ADC Trigger Repeater 1 Phase Delay Status
};

union REP1PHASE_REG {
    Uint32  all;
    struct  REP1PHASE_BITS  bit;
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
};

union REP1FRC_REG {
    Uint16  all;
    struct  REP1FRC_BITS  bit;
};

struct REP2CTL_BITS {                   // bits description
    Uint16 MODE:1;                      // 0 ADC Trigger Repeater 2 Mode Select
    Uint16 ACTIVEMODE:1;                // 1 ADC Trigger Repeater 2 Active Mode
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 MODULEBUSY:1;                // 3 ADC Trigger Repeater 2 Module Busy
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 PHASEOVF:1;                  // 6 ADC Trigger Repeater 2 Phase Delay Overflow
    Uint16 TRIGGEROVF:1;                // 7 ADC Trigger Repeater 2 Oversampled Trigger Overflow
    Uint16 TRIGGER:7;                   // 14:8 ADC Trigger Repeater 2 Trigger Select
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 SYNCINSEL:5;                 // 20:16 ADC Trigger Repeater 2 Sync. In Select
    Uint16 rsvd5:2;                     // 22:21 Reserved
    Uint16 SWSYNC:1;                    // 23 ADC Trigger Repeater 2 Software Sync.
    Uint16 rsvd6:8;                     // 31:24 Reserved
};

union REP2CTL_REG {
    Uint32  all;
    struct  REP2CTL_BITS  bit;
};

struct REP2N_BITS {                     // bits description
    Uint16 NSEL:7;                      // 6:0 ADC Trigger Repeater 2 Trigger Number Selection
    Uint16 rsvd1:9;                     // 15:7 Reserved
    Uint16 NCOUNT:7;                    // 22:16 ADC Trigger Repeater 2 Trigger Counter
    Uint16 rsvd2:9;                     // 31:23 Reserved
};

union REP2N_REG {
    Uint32  all;
    struct  REP2N_BITS  bit;
};

struct REP2PHASE_BITS {                 // bits description
    Uint16 PHASE:16;                    // 15:0 ADC Trigger Repeater 2 Phase Delay Configuration
    Uint16 PHASECOUNT:16;               // 31:16 ADC Trigger Repeater 2 Phase Delay Status
};

union REP2PHASE_REG {
    Uint32  all;
    struct  REP2PHASE_BITS  bit;
};

struct REP2SPREAD_BITS {                // bits description
    Uint16 SPREAD:16;                   // 15:0 ADC Trigger Repeater 2 Spread Delay Configuration
    Uint16 SPREADCOUNT:16;              // 31:16 ADC Trigger Repeater 2 Spread Delay Status
};

union REP2SPREAD_REG {
    Uint32  all;
    struct  REP2SPREAD_BITS  bit;
};

struct REP2FRC_BITS {                   // bits description
    Uint16 SWFRC:1;                     // 0 ADC Trigger Repeater 2 Software Force
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union REP2FRC_REG {
    Uint16  all;
    struct  REP2FRC_BITS  bit;
};

struct ADCPPB1LIMIT_BITS {              // bits description
    Uint16 LIMIT:10;                    // 9:0 Post Processing Block 1 Limit
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1LIMIT_REG {
    Uint16  all;
    struct  ADCPPB1LIMIT_BITS  bit;
};

struct ADCPPBP1PCOUNT_BITS {            // bits description
    Uint16 PCOUNT:10;                   // 9:0 Post Processing Block 1 Partial Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPBP1PCOUNT_REG {
    Uint16  all;
    struct  ADCPPBP1PCOUNT_BITS  bit;
};

struct ADCPPB1CONFIG2_BITS {            // bits description
    Uint16 SHIFT:4;                     // 3:0 Post Processing Block 1 Right Shift
    Uint16 SYNCINSEL:5;                 // 8:4 Post Processing Block 1 Sync. Input Select
    Uint16 rsvd1:2;                     // 10:9 Reserved
    Uint16 SWSYNC:1;                    // 11 Post Processing Block 1 Software Force Sync.
    Uint16 OSINTSEL:1;                  // 12 Post Processing Block 1 Interrupt Source Select
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 COMPSEL:2;                   // 15:14 Post Processing Block 1 Compare Source Select
};

union ADCPPB1CONFIG2_REG {
    Uint16  all;
    struct  ADCPPB1CONFIG2_BITS  bit;
};

struct ADCPPB1PSUM_BITS {               // bits description
    Uint32 PSUM:24;                     // 23:0 Post Processing Block 1 Oversampling Partial Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB1PSUM_REG {
    Uint32  all;
    struct  ADCPPB1PSUM_BITS  bit;
};

struct ADCPPB1PMAX_BITS {               // bits description
    Uint32 PMAX:17;                     // 16:0 Post Processing Block 1 Oversampling Partial Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB1PMAX_REG {
    Uint32  all;
    struct  ADCPPB1PMAX_BITS  bit;
};

struct ADCPPB1PMAXI_BITS {              // bits description
    Uint16 PMAXI:10;                    // 9:0 Post Processing Block 1 Oversampling Partial Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1PMAXI_REG {
    Uint16  all;
    struct  ADCPPB1PMAXI_BITS  bit;
};

struct ADCPPB1PMIN_BITS {               // bits description
    Uint32 PMIN:17;                     // 16:0 Post Processing Block 1 Oversampling Partial Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB1PMIN_REG {
    Uint32  all;
    struct  ADCPPB1PMIN_BITS  bit;
};

struct ADCPPB1PMINI_BITS {              // bits description
    Uint16 PMINI:10;                    // 9:0 Post Processing Block 1 Oversampling Partial Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1PMINI_REG {
    Uint16  all;
    struct  ADCPPB1PMINI_BITS  bit;
};

struct ADCPPB1TRIPLO2_BITS {            // bits description
    Uint32 LIMITLO:24;                  // 23:0 ADC Post Processing Block 1 Trip Low Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB1TRIPLO2_REG {
    Uint32  all;
    struct  ADCPPB1TRIPLO2_BITS  bit;
};

struct ADCPPB2LIMIT_BITS {              // bits description
    Uint16 LIMIT:10;                    // 9:0 Post Processing Block 2 Limit
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2LIMIT_REG {
    Uint16  all;
    struct  ADCPPB2LIMIT_BITS  bit;
};

struct ADCPPBP2PCOUNT_BITS {            // bits description
    Uint16 PCOUNT:10;                   // 9:0 Post Processing Block 2 Partial Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPBP2PCOUNT_REG {
    Uint16  all;
    struct  ADCPPBP2PCOUNT_BITS  bit;
};

struct ADCPPB2CONFIG2_BITS {            // bits description
    Uint16 SHIFT:4;                     // 3:0 Post Processing Block 2 Right Shift
    Uint16 SYNCINSEL:5;                 // 8:4 Post Processing Block 2 Sync. Input Select
    Uint16 rsvd1:2;                     // 10:9 Reserved
    Uint16 SWSYNC:1;                    // 11 Post Processing Block 2 Software Force Sync.
    Uint16 OSINTSEL:1;                  // 12 Post Processing Block 2 Interrupt Source Select
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 COMPSEL:2;                   // 15:14 Post Processing Block 2 Compare Source Select
};

union ADCPPB2CONFIG2_REG {
    Uint16  all;
    struct  ADCPPB2CONFIG2_BITS  bit;
};

struct ADCPPB2PSUM_BITS {               // bits description
    Uint32 PSUM:24;                     // 23:0 Post Processing Block 2 Oversampling Partial Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB2PSUM_REG {
    Uint32  all;
    struct  ADCPPB2PSUM_BITS  bit;
};

struct ADCPPB2PMAX_BITS {               // bits description
    Uint32 PMAX:17;                     // 16:0 Post Processing Block 2 Oversampling Partial Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB2PMAX_REG {
    Uint32  all;
    struct  ADCPPB2PMAX_BITS  bit;
};

struct ADCPPB2PMAXI_BITS {              // bits description
    Uint16 PMAXI:10;                    // 9:0 Post Processing Block 2 Oversampling Partial Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2PMAXI_REG {
    Uint16  all;
    struct  ADCPPB2PMAXI_BITS  bit;
};

struct ADCPPB2PMIN_BITS {               // bits description
    Uint32 PMIN:17;                     // 16:0 Post Processing Block 2 Oversampling Partial Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB2PMIN_REG {
    Uint32  all;
    struct  ADCPPB2PMIN_BITS  bit;
};

struct ADCPPB2PMINI_BITS {              // bits description
    Uint16 PMINI:10;                    // 9:0 Post Processing Block 2 Oversampling Partial Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2PMINI_REG {
    Uint16  all;
    struct  ADCPPB2PMINI_BITS  bit;
};

struct ADCPPB2TRIPLO2_BITS {            // bits description
    Uint32 LIMITLO:24;                  // 23:0 ADC Post Processing Block 2 Trip Low Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB2TRIPLO2_REG {
    Uint32  all;
    struct  ADCPPB2TRIPLO2_BITS  bit;
};

struct ADCPPB3LIMIT_BITS {              // bits description
    Uint16 LIMIT:10;                    // 9:0 Post Processing Block 3 Limit
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3LIMIT_REG {
    Uint16  all;
    struct  ADCPPB3LIMIT_BITS  bit;
};

struct ADCPPBP3PCOUNT_BITS {            // bits description
    Uint16 PCOUNT:10;                   // 9:0 Post Processing Block 3 Partial Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPBP3PCOUNT_REG {
    Uint16  all;
    struct  ADCPPBP3PCOUNT_BITS  bit;
};

struct ADCPPB3CONFIG2_BITS {            // bits description
    Uint16 SHIFT:4;                     // 3:0 Post Processing Block 3 Right Shift
    Uint16 SYNCINSEL:5;                 // 8:4 Post Processing Block 3 Sync. Input Select
    Uint16 rsvd1:2;                     // 10:9 Reserved
    Uint16 SWSYNC:1;                    // 11 Post Processing Block 3 Software Force Sync.
    Uint16 OSINTSEL:1;                  // 12 Post Processing Block 3 Interrupt Source Select
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 COMPSEL:2;                   // 15:14 Post Processing Block 3 Compare Source Select
};

union ADCPPB3CONFIG2_REG {
    Uint16  all;
    struct  ADCPPB3CONFIG2_BITS  bit;
};

struct ADCPPB3PSUM_BITS {               // bits description
    Uint32 PSUM:24;                     // 23:0 Post Processing Block 3 Oversampling Partial Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB3PSUM_REG {
    Uint32  all;
    struct  ADCPPB3PSUM_BITS  bit;
};

struct ADCPPB3PMAX_BITS {               // bits description
    Uint32 PMAX:17;                     // 16:0 Post Processing Block 3 Oversampling Partial Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB3PMAX_REG {
    Uint32  all;
    struct  ADCPPB3PMAX_BITS  bit;
};

struct ADCPPB3PMAXI_BITS {              // bits description
    Uint16 PMAXI:10;                    // 9:0 Post Processing Block 3 Oversampling Partial Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3PMAXI_REG {
    Uint16  all;
    struct  ADCPPB3PMAXI_BITS  bit;
};

struct ADCPPB3PMIN_BITS {               // bits description
    Uint32 PMIN:17;                     // 16:0 Post Processing Block 3 Oversampling Partial Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB3PMIN_REG {
    Uint32  all;
    struct  ADCPPB3PMIN_BITS  bit;
};

struct ADCPPB3PMINI_BITS {              // bits description
    Uint16 PMINI:10;                    // 9:0 Post Processing Block 3 Oversampling Partial Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3PMINI_REG {
    Uint16  all;
    struct  ADCPPB3PMINI_BITS  bit;
};

struct ADCPPB3TRIPLO2_BITS {            // bits description
    Uint32 LIMITLO:24;                  // 23:0 ADC Post Processing Block 3 Trip Low Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB3TRIPLO2_REG {
    Uint32  all;
    struct  ADCPPB3TRIPLO2_BITS  bit;
};

struct ADCPPB4LIMIT_BITS {              // bits description
    Uint16 LIMIT:10;                    // 9:0 Post Processing Block 4 Limit
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4LIMIT_REG {
    Uint16  all;
    struct  ADCPPB4LIMIT_BITS  bit;
};

struct ADCPPBP4PCOUNT_BITS {            // bits description
    Uint16 PCOUNT:10;                   // 9:0 Post Processing Block 4 Partial Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPBP4PCOUNT_REG {
    Uint16  all;
    struct  ADCPPBP4PCOUNT_BITS  bit;
};

struct ADCPPB4CONFIG2_BITS {            // bits description
    Uint16 SHIFT:4;                     // 3:0 Post Processing Block 4 Right Shift
    Uint16 SYNCINSEL:5;                 // 8:4 Post Processing Block 4 Sync. Input Select
    Uint16 rsvd1:2;                     // 10:9 Reserved
    Uint16 SWSYNC:1;                    // 11 Post Processing Block 4 Software Force Sync.
    Uint16 OSINTSEL:1;                  // 12 Post Processing Block 4 Interrupt Source Select
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 COMPSEL:2;                   // 15:14 Post Processing Block 4 Compare Source Select
};

union ADCPPB4CONFIG2_REG {
    Uint16  all;
    struct  ADCPPB4CONFIG2_BITS  bit;
};

struct ADCPPB4PSUM_BITS {               // bits description
    Uint32 PSUM:24;                     // 23:0 Post Processing Block 4 Oversampling Partial Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB4PSUM_REG {
    Uint32  all;
    struct  ADCPPB4PSUM_BITS  bit;
};

struct ADCPPB4PMAX_BITS {               // bits description
    Uint32 PMAX:17;                     // 16:0 Post Processing Block 4 Oversampling Partial Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB4PMAX_REG {
    Uint32  all;
    struct  ADCPPB4PMAX_BITS  bit;
};

struct ADCPPB4PMAXI_BITS {              // bits description
    Uint16 PMAXI:10;                    // 9:0 Post Processing Block 4 Oversampling Partial Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4PMAXI_REG {
    Uint16  all;
    struct  ADCPPB4PMAXI_BITS  bit;
};

struct ADCPPB4PMIN_BITS {               // bits description
    Uint32 PMIN:17;                     // 16:0 Post Processing Block 4 Oversampling Partial Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB4PMIN_REG {
    Uint32  all;
    struct  ADCPPB4PMIN_BITS  bit;
};

struct ADCPPB4PMINI_BITS {              // bits description
    Uint16 PMINI:10;                    // 9:0 Post Processing Block 4 Oversampling Partial Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4PMINI_REG {
    Uint16  all;
    struct  ADCPPB4PMINI_BITS  bit;
};

struct ADCPPB4TRIPLO2_BITS {            // bits description
    Uint32 LIMITLO:24;                  // 23:0 ADC Post Processing Block 4 Trip Low Limit
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union ADCPPB4TRIPLO2_REG {
    Uint32  all;
    struct  ADCPPB4TRIPLO2_BITS  bit;
};

struct ADC_REGS {
    union   ADCCTL1_REG                      ADCCTL1;                      // ADC Control 1 Register
    union   ADCCTL2_REG                      ADCCTL2;                      // ADC Control 2 Register
    union   ADCBURSTCTL_REG                  ADCBURSTCTL;                  // ADC Burst Control Register
    union   ADCINTFLG_REG                    ADCINTFLG;                    // ADC Interrupt Flag Register
    union   ADCINTFLGCLR_REG                 ADCINTFLGCLR;                 // ADC Interrupt Flag Clear Register
    union   ADCINTOVF_REG                    ADCINTOVF;                    // ADC Interrupt Overflow Register
    union   ADCINTOVFCLR_REG                 ADCINTOVFCLR;                 // ADC Interrupt Overflow Clear Register
    union   ADCINTSEL1N2_REG                 ADCINTSEL1N2;                 // ADC Interrupt 1 and 2 Selection Register
    union   ADCINTSEL3N4_REG                 ADCINTSEL3N4;                 // ADC Interrupt 3 and 4 Selection Register
    union   ADCSOCPRICTL_REG                 ADCSOCPRICTL;                 // ADC SOC Priority Control Register
    union   ADCINTSOCSEL1_REG                ADCINTSOCSEL1;                // ADC Interrupt SOC Selection 1 Register
    union   ADCINTSOCSEL2_REG                ADCINTSOCSEL2;                // ADC Interrupt SOC Selection 2 Register
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
    union   ADCEVTSTAT_REG                   ADCEVTSTAT;                   // ADC Event Status Register
    Uint16                                   rsvd1;                        // Reserved
    union   ADCEVTCLR_REG                    ADCEVTCLR;                    // ADC Event Clear Register
    Uint16                                   rsvd2;                        // Reserved
    union   ADCEVTSEL_REG                    ADCEVTSEL;                    // ADC Event Selection Register
    Uint16                                   rsvd3;                        // Reserved
    union   ADCEVTINTSEL_REG                 ADCEVTINTSEL;                 // ADC Event Interrupt Selection Register
    Uint16                                   rsvd4;                        // Reserved
    union   ADCOSDETECT_REG                  ADCOSDETECT;                  // ADC Open and Shorts Detect Register
    union   ADCCOUNTER_REG                   ADCCOUNTER;                   // ADC Counter Register
    union   ADCREV_REG                       ADCREV;                       // ADC Revision Register
    union   ADCOFFTRIM_REG                   ADCOFFTRIM;                   // ADC Offset Trim Register
    union   ADCOFFTRIM2_REG                  ADCOFFTRIM2;                  // ADC Offset Trim Register
    union   ADCOFFTRIM3_REG                  ADCOFFTRIM3;                  // ADC Offset Trim Register
    Uint16                                   rsvd5[2];                     // Reserved
    union   ADCPPB1CONFIG_REG                ADCPPB1CONFIG;                // ADC PPB1 Config Register
    union   ADCPPB1STAMP_REG                 ADCPPB1STAMP;                 // ADC PPB1 Sample Delay Time Stamp Register
    union   ADCPPB1OFFCAL_REG                ADCPPB1OFFCAL;                // ADC PPB1 Offset Calibration Register
    Uint16                                   ADCPPB1OFFREF;                // ADC PPB1 Offset Reference Register
    union   ADCPPB1TRIPHI_REG                ADCPPB1TRIPHI;                // ADC PPB1 Trip High Register
    union   ADCPPB1TRIPLO_REG                ADCPPB1TRIPLO;                // ADC PPB1 Trip Low/Trigger Time Stamp Register
    union   ADCPPB2CONFIG_REG                ADCPPB2CONFIG;                // ADC PPB2 Config Register
    union   ADCPPB2STAMP_REG                 ADCPPB2STAMP;                 // ADC PPB2 Sample Delay Time Stamp Register
    union   ADCPPB2OFFCAL_REG                ADCPPB2OFFCAL;                // ADC PPB2 Offset Calibration Register
    Uint16                                   ADCPPB2OFFREF;                // ADC PPB2 Offset Reference Register
    union   ADCPPB2TRIPHI_REG                ADCPPB2TRIPHI;                // ADC PPB2 Trip High Register
    union   ADCPPB2TRIPLO_REG                ADCPPB2TRIPLO;                // ADC PPB2 Trip Low/Trigger Time Stamp Register
    union   ADCPPB3CONFIG_REG                ADCPPB3CONFIG;                // ADC PPB3 Config Register
    union   ADCPPB3STAMP_REG                 ADCPPB3STAMP;                 // ADC PPB3 Sample Delay Time Stamp Register
    union   ADCPPB3OFFCAL_REG                ADCPPB3OFFCAL;                // ADC PPB3 Offset Calibration Register
    Uint16                                   ADCPPB3OFFREF;                // ADC PPB3 Offset Reference Register
    union   ADCPPB3TRIPHI_REG                ADCPPB3TRIPHI;                // ADC PPB3 Trip High Register
    union   ADCPPB3TRIPLO_REG                ADCPPB3TRIPLO;                // ADC PPB3 Trip Low/Trigger Time Stamp Register
    union   ADCPPB4CONFIG_REG                ADCPPB4CONFIG;                // ADC PPB4 Config Register
    union   ADCPPB4STAMP_REG                 ADCPPB4STAMP;                 // ADC PPB4 Sample Delay Time Stamp Register
    union   ADCPPB4OFFCAL_REG                ADCPPB4OFFCAL;                // ADC PPB4 Offset Calibration Register
    Uint16                                   ADCPPB4OFFREF;                // ADC PPB4 Offset Reference Register
    union   ADCPPB4TRIPHI_REG                ADCPPB4TRIPHI;                // ADC PPB4 Trip High Register
    union   ADCPPB4TRIPLO_REG                ADCPPB4TRIPLO;                // ADC PPB4 Trip Low/Trigger Time Stamp Register
    union   ADCSAFECHECKRESEN_REG            ADCSAFECHECKRESEN;            // ADC Safe Check Result Enable Register
    Uint16                                   rsvd6[13];                    // Reserved
    Uint16                                   ADCINTCYCLE;                  // ADC Early Interrupt Generation Cycle
    Uint32                                   ADCINLTRIM1;                  // ADC Linearity Trim 1 Register
    Uint32                                   ADCINLTRIM2;                  // ADC Linearity Trim 2 Register
    Uint32                                   ADCINLTRIM3;                  // ADC Linearity Trim 3 Register
    Uint32                                   ADCINLTRIM4;                  // ADC Linearity Trim 4 Register
    Uint32                                   ADCINLTRIM5;                  // ADC Linearity Trim 5 Register
    Uint32                                   ADCINLTRIM6;                  // ADC Linearity Trim 6 Register
    Uint16                                   rsvd7;                        // Reserved
    union   ADCREV2_REG                      ADCREV2;                      // ADC Wrapper Revision Register
    Uint16                                   rsvd8[2];                     // Reserved
    union   REP1CTL_REG                      REP1CTL;                      // ADC Trigger Repeater 1 Control Register
    union   REP1N_REG                        REP1N;                        // ADC Trigger Repeater 1 N Select Register
    union   REP1PHASE_REG                    REP1PHASE;                    // ADC Trigger Repeater 1 Phase Select Register
    union   REP1SPREAD_REG                   REP1SPREAD;                   // ADC Trigger Repeater 1 Spread Select Register
    union   REP1FRC_REG                      REP1FRC;                      // ADC Trigger Repeater 1 Software Force Register
    Uint16                                   rsvd9[7];                     // Reserved
    union   REP2CTL_REG                      REP2CTL;                      // ADC Trigger Repeater 2 Control Register
    union   REP2N_REG                        REP2N;                        // ADC Trigger Repeater 2 N Select Register
    union   REP2PHASE_REG                    REP2PHASE;                    // ADC Trigger Repeater 2 Phase Select Register
    union   REP2SPREAD_REG                   REP2SPREAD;                   // ADC Trigger Repeater 2 Spread Select Register
    union   REP2FRC_REG                      REP2FRC;                      // ADC Trigger Repeater 2 Software Force Register
    Uint16                                   rsvd10[7];                    // Reserved
    union   ADCPPB1LIMIT_REG                 ADCPPB1LIMIT;                 // ADC PPB1Conversion Count Limit Register
    Uint16                                   rsvd11;                       // Reserved
    union   ADCPPBP1PCOUNT_REG               ADCPPBP1PCOUNT;               // ADC PPB1 Partial Conversion Count Register
    Uint16                                   rsvd12;                       // Reserved
    union   ADCPPB1CONFIG2_REG               ADCPPB1CONFIG2;               // ADC PPB1 Sum Shift Register
    Uint16                                   rsvd13;                       // Reserved
    union   ADCPPB1PSUM_REG                  ADCPPB1PSUM;                  // ADC PPB1 Partial Sum Register
    union   ADCPPB1PMAX_REG                  ADCPPB1PMAX;                  // ADC PPB1 Partial Max Register
    union   ADCPPB1PMAXI_REG                 ADCPPB1PMAXI;                 // ADC PPB1 Partial Max Index Register
    Uint16                                   rsvd14;                       // Reserved
    union   ADCPPB1PMIN_REG                  ADCPPB1PMIN;                  // ADC PPB1 Partial MIN Register
    union   ADCPPB1PMINI_REG                 ADCPPB1PMINI;                 // ADC PPB1 Partial Min Index Register
    Uint16                                   rsvd15;                       // Reserved
    union   ADCPPB1TRIPLO2_REG               ADCPPB1TRIPLO2;               // ADC PPB1 Extended Trip Low Register
    Uint16                                   rsvd16[8];                    // Reserved
    union   ADCPPB2LIMIT_REG                 ADCPPB2LIMIT;                 // ADC PPB2Conversion Count Limit Register
    Uint16                                   rsvd17;                       // Reserved
    union   ADCPPBP2PCOUNT_REG               ADCPPBP2PCOUNT;               // ADC PPB2 Partial Conversion Count Register
    Uint16                                   rsvd18;                       // Reserved
    union   ADCPPB2CONFIG2_REG               ADCPPB2CONFIG2;               // ADC PPB2 Sum Shift Register
    Uint16                                   rsvd19;                       // Reserved
    union   ADCPPB2PSUM_REG                  ADCPPB2PSUM;                  // ADC PPB2 Partial Sum Register
    union   ADCPPB2PMAX_REG                  ADCPPB2PMAX;                  // ADC PPB2 Partial Max Register
    union   ADCPPB2PMAXI_REG                 ADCPPB2PMAXI;                 // ADC PPB2 Partial Max Index Register
    Uint16                                   rsvd20;                       // Reserved
    union   ADCPPB2PMIN_REG                  ADCPPB2PMIN;                  // ADC PPB2 Partial MIN Register
    union   ADCPPB2PMINI_REG                 ADCPPB2PMINI;                 // ADC PPB2 Partial Min Index Register
    Uint16                                   rsvd21;                       // Reserved
    union   ADCPPB2TRIPLO2_REG               ADCPPB2TRIPLO2;               // ADC PPB2 Extended Trip Low Register
    Uint16                                   rsvd22[8];                    // Reserved
    union   ADCPPB3LIMIT_REG                 ADCPPB3LIMIT;                 // ADC PPB3Conversion Count Limit Register
    Uint16                                   rsvd23;                       // Reserved
    union   ADCPPBP3PCOUNT_REG               ADCPPBP3PCOUNT;               // ADC PPB3 Partial Conversion Count Register
    Uint16                                   rsvd24;                       // Reserved
    union   ADCPPB3CONFIG2_REG               ADCPPB3CONFIG2;               // ADC PPB3 Sum Shift Register
    Uint16                                   rsvd25;                       // Reserved
    union   ADCPPB3PSUM_REG                  ADCPPB3PSUM;                  // ADC PPB3 Partial Sum Register
    union   ADCPPB3PMAX_REG                  ADCPPB3PMAX;                  // ADC PPB3 Partial Max Register
    union   ADCPPB3PMAXI_REG                 ADCPPB3PMAXI;                 // ADC PPB3 Partial Max Index Register
    Uint16                                   rsvd26;                       // Reserved
    union   ADCPPB3PMIN_REG                  ADCPPB3PMIN;                  // ADC PPB3 Partial MIN Register
    union   ADCPPB3PMINI_REG                 ADCPPB3PMINI;                 // ADC PPB3 Partial Min Index Register
    Uint16                                   rsvd27;                       // Reserved
    union   ADCPPB3TRIPLO2_REG               ADCPPB3TRIPLO2;               // ADC PPB3 Extended Trip Low Register
    Uint16                                   rsvd28[8];                    // Reserved
    union   ADCPPB4LIMIT_REG                 ADCPPB4LIMIT;                 // ADC PPB4Conversion Count Limit Register
    Uint16                                   rsvd29;                       // Reserved
    union   ADCPPBP4PCOUNT_REG               ADCPPBP4PCOUNT;               // ADC PPB4 Partial Conversion Count Register
    Uint16                                   rsvd30;                       // Reserved
    union   ADCPPB4CONFIG2_REG               ADCPPB4CONFIG2;               // ADC PPB4 Sum Shift Register
    Uint16                                   rsvd31;                       // Reserved
    union   ADCPPB4PSUM_REG                  ADCPPB4PSUM;                  // ADC PPB4 Partial Sum Register
    union   ADCPPB4PMAX_REG                  ADCPPB4PMAX;                  // ADC PPB4 Partial Max Register
    union   ADCPPB4PMAXI_REG                 ADCPPB4PMAXI;                 // ADC PPB4 Partial Max Index Register
    Uint16                                   rsvd32;                       // Reserved
    union   ADCPPB4PMIN_REG                  ADCPPB4PMIN;                  // ADC PPB4 Partial MIN Register
    union   ADCPPB4PMINI_REG                 ADCPPB4PMINI;                 // ADC PPB4 Partial Min Index Register
    Uint16                                   rsvd33;                       // Reserved
    union   ADCPPB4TRIPLO2_REG               ADCPPB4TRIPLO2;               // ADC PPB4 Extended Trip Low Register
};

struct ADCPPB1RESULT_BITS {             // bits description
    Uint16 PPBRESULT:16;                // 15:0 ADC Post Processing Block Result
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB1RESULT_REG {
    Uint32  all;
    struct  ADCPPB1RESULT_BITS  bit;
};

struct ADCPPB2RESULT_BITS {             // bits description
    Uint16 PPBRESULT:16;                // 15:0 ADC Post Processing Block Result
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB2RESULT_REG {
    Uint32  all;
    struct  ADCPPB2RESULT_BITS  bit;
};

struct ADCPPB3RESULT_BITS {             // bits description
    Uint16 PPBRESULT:16;                // 15:0 ADC Post Processing Block Result
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB3RESULT_REG {
    Uint32  all;
    struct  ADCPPB3RESULT_BITS  bit;
};

struct ADCPPB4RESULT_BITS {             // bits description
    Uint16 PPBRESULT:16;                // 15:0 ADC Post Processing Block Result
    Uint16 SIGN:16;                     // 31:16 Sign Extended Bits
};

union ADCPPB4RESULT_REG {
    Uint32  all;
    struct  ADCPPB4RESULT_BITS  bit;
};

struct ADCPPB1SUM_BITS {                // bits description
    Uint32 SUM:24;                      // 23:0 Post Processing Block 1 Oversampling Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB1SUM_REG {
    Uint32  all;
    struct  ADCPPB1SUM_BITS  bit;
};

struct ADCPPB1COUNT_BITS {              // bits description
    Uint16 COUNT:10;                    // 9:0 Post Processing Block 1 Final Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1COUNT_REG {
    Uint16  all;
    struct  ADCPPB1COUNT_BITS  bit;
};

struct ADCPPB2SUM_BITS {                // bits description
    Uint32 SUM:24;                      // 23:0 Post Processing Block 2 Oversampling Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB2SUM_REG {
    Uint32  all;
    struct  ADCPPB2SUM_BITS  bit;
};

struct ADCPPB2COUNT_BITS {              // bits description
    Uint16 COUNT:10;                    // 9:0 Post Processing Block 2 Final Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2COUNT_REG {
    Uint16  all;
    struct  ADCPPB2COUNT_BITS  bit;
};

struct ADCPPB3SUM_BITS {                // bits description
    Uint32 SUM:24;                      // 23:0 Post Processing Block 3 Oversampling Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB3SUM_REG {
    Uint32  all;
    struct  ADCPPB3SUM_BITS  bit;
};

struct ADCPPB3COUNT_BITS {              // bits description
    Uint16 COUNT:10;                    // 9:0 Post Processing Block 3 Final Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3COUNT_REG {
    Uint16  all;
    struct  ADCPPB3COUNT_BITS  bit;
};

struct ADCPPB4SUM_BITS {                // bits description
    Uint32 SUM:24;                      // 23:0 Post Processing Block 4 Oversampling Sum
    Uint16 SIGN:8;                      // 31:24 Sign Extended Bits
};

union ADCPPB4SUM_REG {
    Uint32  all;
    struct  ADCPPB4SUM_BITS  bit;
};

struct ADCPPB4COUNT_BITS {              // bits description
    Uint16 COUNT:10;                    // 9:0 Post Processing Block 4 Final Count
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4COUNT_REG {
    Uint16  all;
    struct  ADCPPB4COUNT_BITS  bit;
};

struct ADCPPB1MAX_BITS {                // bits description
    Uint32 MAX:17;                      // 16:0 Post Processing Block 1 Oversampling Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB1MAX_REG {
    Uint32  all;
    struct  ADCPPB1MAX_BITS  bit;
};

struct ADCPPB1MAXI_BITS {               // bits description
    Uint16 MAXI:10;                     // 9:0 Post Processing Block 1 Oversampling Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1MAXI_REG {
    Uint16  all;
    struct  ADCPPB1MAXI_BITS  bit;
};

struct ADCPPB1MIN_BITS {                // bits description
    Uint32 MIN:17;                      // 16:0 Post Processing Block 1 Oversampling Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB1MIN_REG {
    Uint32  all;
    struct  ADCPPB1MIN_BITS  bit;
};

struct ADCPPB1MINI_BITS {               // bits description
    Uint16 MINI:10;                     // 9:0 Post Processing Block 1 Oversampling Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB1MINI_REG {
    Uint16  all;
    struct  ADCPPB1MINI_BITS  bit;
};

struct ADCPPB2MAX_BITS {                // bits description
    Uint32 MAX:17;                      // 16:0 Post Processing Block 2 Oversampling Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB2MAX_REG {
    Uint32  all;
    struct  ADCPPB2MAX_BITS  bit;
};

struct ADCPPB2MAXI_BITS {               // bits description
    Uint16 MAXI:10;                     // 9:0 Post Processing Block 2 Oversampling Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2MAXI_REG {
    Uint16  all;
    struct  ADCPPB2MAXI_BITS  bit;
};

struct ADCPPB2MIN_BITS {                // bits description
    Uint32 MIN:17;                      // 16:0 Post Processing Block 2 Oversampling Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB2MIN_REG {
    Uint32  all;
    struct  ADCPPB2MIN_BITS  bit;
};

struct ADCPPB2MINI_BITS {               // bits description
    Uint16 MINI:10;                     // 9:0 Post Processing Block 2 Oversampling Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB2MINI_REG {
    Uint16  all;
    struct  ADCPPB2MINI_BITS  bit;
};

struct ADCPPB3MAX_BITS {                // bits description
    Uint32 MAX:17;                      // 16:0 Post Processing Block 3 Oversampling Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB3MAX_REG {
    Uint32  all;
    struct  ADCPPB3MAX_BITS  bit;
};

struct ADCPPB3MAXI_BITS {               // bits description
    Uint16 MAXI:10;                     // 9:0 Post Processing Block 3 Oversampling Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3MAXI_REG {
    Uint16  all;
    struct  ADCPPB3MAXI_BITS  bit;
};

struct ADCPPB3MIN_BITS {                // bits description
    Uint32 MIN:17;                      // 16:0 Post Processing Block 3 Oversampling Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB3MIN_REG {
    Uint32  all;
    struct  ADCPPB3MIN_BITS  bit;
};

struct ADCPPB3MINI_BITS {               // bits description
    Uint16 MINI:10;                     // 9:0 Post Processing Block 3 Oversampling Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB3MINI_REG {
    Uint16  all;
    struct  ADCPPB3MINI_BITS  bit;
};

struct ADCPPB4MAX_BITS {                // bits description
    Uint32 MAX:17;                      // 16:0 Post Processing Block 4 Oversampling Max
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB4MAX_REG {
    Uint32  all;
    struct  ADCPPB4MAX_BITS  bit;
};

struct ADCPPB4MAXI_BITS {               // bits description
    Uint16 MAXI:10;                     // 9:0 Post Processing Block 4 Oversampling Index of Max
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4MAXI_REG {
    Uint16  all;
    struct  ADCPPB4MAXI_BITS  bit;
};

struct ADCPPB4MIN_BITS {                // bits description
    Uint32 MIN:17;                      // 16:0 Post Processing Block 4 Oversampling Min
    Uint16 SIGN:15;                     // 31:17 Sign Extended Bits
};

union ADCPPB4MIN_REG {
    Uint32  all;
    struct  ADCPPB4MIN_BITS  bit;
};

struct ADCPPB4MINI_BITS {               // bits description
    Uint16 MINI:10;                     // 9:0 Post Processing Block 4 Oversampling Index of Min
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ADCPPB4MINI_REG {
    Uint16  all;
    struct  ADCPPB4MINI_BITS  bit;
};

struct ADC_RESULT_REGS {
    Uint16                                   ADCRESULT0;                   // ADC Result 0 Register
    Uint16                                   ADCRESULT1;                   // ADC Result 1 Register
    Uint16                                   ADCRESULT2;                   // ADC Result 2 Register
    Uint16                                   ADCRESULT3;                   // ADC Result 3 Register
    Uint16                                   ADCRESULT4;                   // ADC Result 4 Register
    Uint16                                   ADCRESULT5;                   // ADC Result 5 Register
    Uint16                                   ADCRESULT6;                   // ADC Result 6 Register
    Uint16                                   ADCRESULT7;                   // ADC Result 7 Register
    Uint16                                   ADCRESULT8;                   // ADC Result 8 Register
    Uint16                                   ADCRESULT9;                   // ADC Result 9 Register
    Uint16                                   ADCRESULT10;                  // ADC Result 10 Register
    Uint16                                   ADCRESULT11;                  // ADC Result 11 Register
    Uint16                                   ADCRESULT12;                  // ADC Result 12 Register
    Uint16                                   ADCRESULT13;                  // ADC Result 13 Register
    Uint16                                   ADCRESULT14;                  // ADC Result 14 Register
    Uint16                                   ADCRESULT15;                  // ADC Result 15 Register
    union   ADCPPB1RESULT_REG                ADCPPB1RESULT;                // ADC Post Processing Block 1 Result Register
    union   ADCPPB2RESULT_REG                ADCPPB2RESULT;                // ADC Post Processing Block 2 Result Register
    union   ADCPPB3RESULT_REG                ADCPPB3RESULT;                // ADC Post Processing Block 3 Result Register
    union   ADCPPB4RESULT_REG                ADCPPB4RESULT;                // ADC Post Processing Block 4 Result Register
    union   ADCPPB1SUM_REG                   ADCPPB1SUM;                   // ADC PPB 1 Final Sum Result Register
    union   ADCPPB1COUNT_REG                 ADCPPB1COUNT;                 // ADC PPB1 Final Conversion Count Register
    Uint16                                   rsvd1;                        // Reserved
    union   ADCPPB2SUM_REG                   ADCPPB2SUM;                   // ADC PPB 2 Final Sum Result Register
    union   ADCPPB2COUNT_REG                 ADCPPB2COUNT;                 // ADC PPB2 Final Conversion Count Register
    Uint16                                   rsvd2;                        // Reserved
    union   ADCPPB3SUM_REG                   ADCPPB3SUM;                   // ADC PPB 3 Final Sum Result Register
    union   ADCPPB3COUNT_REG                 ADCPPB3COUNT;                 // ADC PPB3 Final Conversion Count Register
    Uint16                                   rsvd3;                        // Reserved
    union   ADCPPB4SUM_REG                   ADCPPB4SUM;                   // ADC PPB 4 Final Sum Result Register
    union   ADCPPB4COUNT_REG                 ADCPPB4COUNT;                 // ADC PPB4 Final Conversion Count Register
    Uint16                                   rsvd4;                        // Reserved
    union   ADCPPB1MAX_REG                   ADCPPB1MAX;                   // ADC PPB 1 Final Max Result Register
    union   ADCPPB1MAXI_REG                  ADCPPB1MAXI;                  // ADC PPB 1 Final Max Index Result Register
    Uint16                                   rsvd5;                        // Reserved
    union   ADCPPB1MIN_REG                   ADCPPB1MIN;                   // ADC PPB 1 Final Min Result Register
    union   ADCPPB1MINI_REG                  ADCPPB1MINI;                  // ADC PPB 1 Final Min Index Result Register
    Uint16                                   rsvd6;                        // Reserved
    union   ADCPPB2MAX_REG                   ADCPPB2MAX;                   // ADC PPB 2 Final Max Result Register
    union   ADCPPB2MAXI_REG                  ADCPPB2MAXI;                  // ADC PPB 2 Final Max Index Result Register
    Uint16                                   rsvd7;                        // Reserved
    union   ADCPPB2MIN_REG                   ADCPPB2MIN;                   // ADC PPB 2 Final Min Result Register
    union   ADCPPB2MINI_REG                  ADCPPB2MINI;                  // ADC PPB 2 Final Min Index Result Register
    Uint16                                   rsvd8;                        // Reserved
    union   ADCPPB3MAX_REG                   ADCPPB3MAX;                   // ADC PPB 3 Final Max Result Register
    union   ADCPPB3MAXI_REG                  ADCPPB3MAXI;                  // ADC PPB 3 Final Max Index Result Register
    Uint16                                   rsvd9;                        // Reserved
    union   ADCPPB3MIN_REG                   ADCPPB3MIN;                   // ADC PPB 3 Final Min Result Register
    union   ADCPPB3MINI_REG                  ADCPPB3MINI;                  // ADC PPB 3 Final Min Index Result Register
    Uint16                                   rsvd10;                       // Reserved
    union   ADCPPB4MAX_REG                   ADCPPB4MAX;                   // ADC PPB 4 Final Max Result Register
    union   ADCPPB4MAXI_REG                  ADCPPB4MAXI;                  // ADC PPB 4 Final Max Index Result Register
    Uint16                                   rsvd11;                       // Reserved
    union   ADCPPB4MIN_REG                   ADCPPB4MIN;                   // ADC PPB 4 Final Min Result Register
    union   ADCPPB4MINI_REG                  ADCPPB4MINI;                  // ADC PPB 4 Final Min Index Result Register
};

struct CHECKCONFIG_BITS {               // bits description
    Uint16 rsvd1:5;                     // 4:0 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 SWSYNC:1;                    // 6 Result Safe Check SW Force Sync.
    Uint16 rsvd3:8;                     // 14:7 Reserved
    Uint16 CHKEN:1;                     // 15 Result Safe Check Module Enable
};

union CHECKCONFIG_REG {
    Uint16  all;
    struct  CHECKCONFIG_BITS  bit;
};

struct CHECKSTATUS_BITS {               // bits description
    Uint16 RES1READY:1;                 // 0 Result Safe Check Result 1 Arrived
    Uint16 RES2READY:1;                 // 1 Result Safe Check Result 2 Arrived
    Uint16 OOT:1;                       // 2 Safe Check OOT Flag
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union CHECKSTATUS_REG {
    Uint16  all;
    struct  CHECKSTATUS_BITS  bit;
};

struct ADCRESSEL1_BITS {                // bits description
    Uint16 ADCSEL:3;                    // 2:0 Result Safe Check ADC Select 1
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 ADCRESULTSEL:6;              // 9:4 Result Safe Check Result Select 1
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union ADCRESSEL1_REG {
    Uint16  all;
    struct  ADCRESSEL1_BITS  bit;
};

struct ADCRESSEL2_BITS {                // bits description
    Uint16 ADCSEL:3;                    // 2:0 Result Safe Check ADC Select 2
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 ADCRESULTSEL:6;              // 9:4 Result Safe Check Result Select 2
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union ADCRESSEL2_REG {
    Uint16  all;
    struct  ADCRESSEL2_BITS  bit;
};

struct TOLERANCE_BITS {                 // bits description
    Uint32 TOLERANCE:24;                // 23:0 Result Safe Check Tolerance
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union TOLERANCE_REG {
    Uint32  all;
    struct  TOLERANCE_BITS  bit;
};

struct CHECKRESULT1_BITS {              // bits description
    Uint32 RESULT:24;                   // 23:0 Result Safe Check Captured Result
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union CHECKRESULT1_REG {
    Uint32  all;
    struct  CHECKRESULT1_BITS  bit;
};

struct CHECKRESULT2_BITS {              // bits description
    Uint32 RESULT:24;                   // 23:0 Result Safe Check Captured Result
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union CHECKRESULT2_REG {
    Uint32  all;
    struct  CHECKRESULT2_BITS  bit;
};

struct ADC_SAFECHECK_REGS {
    union   CHECKCONFIG_REG                  CHECKCONFIG;                  // ADC Check Configuration Register
    Uint16                                   rsvd1;                        // Reserved
    union   CHECKSTATUS_REG                  CHECKSTATUS;                  // ADC Check Status Register
    Uint16                                   rsvd2;                        // Reserved
    union   ADCRESSEL1_REG                   ADCRESSEL1;                   // ADC Check 1 Select Register
    Uint16                                   rsvd3;                        // Reserved
    union   ADCRESSEL2_REG                   ADCRESSEL2;                   // ADC Check 2 Select Register
    Uint16                                   rsvd4;                        // Reserved
    union   TOLERANCE_REG                    TOLERANCE;                    // ADC Check Tolerance Register
    Uint16                                   rsvd5[2];                     // Reserved
    union   CHECKRESULT1_REG                 CHECKRESULT1;                 // ADC Check Captured Result 1
    union   CHECKRESULT2_REG                 CHECKRESULT2;                 // ADC Check Captured Result 2
};

struct OOTFLG_BITS {                    // bits description
    Uint16 OOT1:1;                      // 0 Checker 1 Out-of-Tolerance Flag
    Uint16 OOT2:1;                      // 1 Checker 2 Out-of-Tolerance Flag
    Uint16 OOT3:1;                      // 2 Checker 3 Out-of-Tolerance Flag
    Uint16 OOT4:1;                      // 3 Checker 4 Out-of-Tolerance Flag
    Uint16 OOT5:1;                      // 4 Checker 5 Out-of-Tolerance Flag
    Uint16 OOT6:1;                      // 5 Checker 6 Out-of-Tolerance Flag
    Uint16 OOT7:1;                      // 6 Checker 7 Out-of-Tolerance Flag
    Uint16 OOT8:1;                      // 7 Checker 8 Out-of-Tolerance Flag
    Uint16 OOT9:1;                      // 8 Checker 9 Out-of-Tolerance Flag
    Uint16 OOT10:1;                     // 9 Checker 10 Out-of-Tolerance Flag
    Uint16 OOT11:1;                     // 10 Checker 11 Out-of-Tolerance Flag
    Uint16 OOT12:1;                     // 11 Checker 12 Out-of-Tolerance Flag
    Uint16 OOT13:1;                     // 12 Checker 13 Out-of-Tolerance Flag
    Uint16 OOT14:1;                     // 13 Checker 14 Out-of-Tolerance Flag
    Uint16 OOT15:1;                     // 14 Checker 15 Out-of-Tolerance Flag
    Uint16 OOT16:1;                     // 15 Checker 16 Out-of-Tolerance Flag
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union OOTFLG_REG {
    Uint32  all;
    struct  OOTFLG_BITS  bit;
};

struct OOTFLGCLR_BITS {                 // bits description
    Uint16 OOT1:1;                      // 0 Checker 1 OOT Flag Clear
    Uint16 OOT2:1;                      // 1 Checker 2 OOT Flag Clear
    Uint16 OOT3:1;                      // 2 Checker 3 OOT Flag Clear
    Uint16 OOT4:1;                      // 3 Checker 4 OOT Flag Clear
    Uint16 OOT5:1;                      // 4 Checker 5 OOT Flag Clear
    Uint16 OOT6:1;                      // 5 Checker 6 OOT Flag Clear
    Uint16 OOT7:1;                      // 6 Checker 7 OOT Flag Clear
    Uint16 OOT8:1;                      // 7 Checker 8 OOT Flag Clear
    Uint16 OOT9:1;                      // 8 Checker 9 OOT Flag Clear
    Uint16 OOT10:1;                     // 9 Checker 10 OOT Flag Clear
    Uint16 OOT11:1;                     // 10 Checker 11 OOT Flag Clear
    Uint16 OOT12:1;                     // 11 Checker 12 OOT Flag Clear
    Uint16 OOT13:1;                     // 12 Checker 13 OOT Flag Clear
    Uint16 OOT14:1;                     // 13 Checker 14 OOT Flag Clear
    Uint16 OOT15:1;                     // 14 Checker 15 OOT Flag Clear
    Uint16 OOT16:1;                     // 15 Checker 16 OOT Flag Clear
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union OOTFLGCLR_REG {
    Uint32  all;
    struct  OOTFLGCLR_BITS  bit;
};

struct RES1OVF_BITS {                   // bits description
    Uint16 RES1OVF1:1;                  // 0 Checker 1 Result 1 Overflow Flag
    Uint16 RES1OVF2:1;                  // 1 Checker 2 Result 1 Overflow Flag
    Uint16 RES1OVF3:1;                  // 2 Checker 3 Result 1 Overflow Flag
    Uint16 RES1OVF4:1;                  // 3 Checker 4 Result 1 Overflow Flag
    Uint16 RES1OVF5:1;                  // 4 Checker 5 Result 5 Overflow Flag
    Uint16 RES1OVF6:1;                  // 5 Checker 6 Result 1 Overflow Flag
    Uint16 RES1OVF7:1;                  // 6 Checker 7 Result 1 Overflow Flag
    Uint16 RES1OVF8:1;                  // 7 Checker 8 Result 1 Overflow Flag
    Uint16 RES1OVF9:1;                  // 8 Checker 9 Result 1 Overflow Flag
    Uint16 RES1OVF10:1;                 // 9 Checker 10 Result 1 Overflow Flag
    Uint16 RES1OVF11:1;                 // 10 Checker 11 Result 1 Overflow Flag
    Uint16 RES1OVF12:1;                 // 11 Checker 12 Result 1 Overflow Flag
    Uint16 RES1OVF13:1;                 // 12 Checker 13 Result 5 Overflow Flag
    Uint16 RES1OVF14:1;                 // 13 Checker 14 Result 1 Overflow Flag
    Uint16 RES1OVF15:1;                 // 14 Checker 15 Result 1 Overflow Flag
    Uint16 RES1OVF16:1;                 // 15 Checker 16 Result 1 Overflow Flag
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RES1OVF_REG {
    Uint32  all;
    struct  RES1OVF_BITS  bit;
};

struct RES1OVFCLR_BITS {                // bits description
    Uint16 RES1OVF1:1;                  // 0 Checker 1 Result 1  OVF Flag Clear
    Uint16 RES1OVF2:1;                  // 1 Checker 2 Result 1 OVF Flag Clear
    Uint16 RES1OVF3:1;                  // 2 Checker 3 Result 1 OVF Flag Clear
    Uint16 RES1OVF4:1;                  // 3 Checker 4 Result 1 OVF Flag Clear
    Uint16 RES1OVF5:1;                  // 4 Checker 5 Result 1  OVF Flag Clear
    Uint16 RES1OVF6:1;                  // 5 Checker 6 Result 1 OVF Flag Clear
    Uint16 RES1OVF7:1;                  // 6 Checker 7 Result 1 OVF Flag Clear
    Uint16 RES1OVF8:1;                  // 7 Checker 8 Result 1 OVF Flag Clear
    Uint16 RES1OVF9:1;                  // 8 Checker 9 Result 1  OVF Flag Clear
    Uint16 RES1OVF10:1;                 // 9 Checker 10 Result 1 OVF Flag Clear
    Uint16 RES1OVF11:1;                 // 10 Checker 11 Result 1 OVF Flag Clear
    Uint16 RES1OVF12:1;                 // 11 Checker 12 Result 1 OVF Flag Clear
    Uint16 RES1OVF13:1;                 // 12 Checker 13 Result 1  OVF Flag Clear
    Uint16 RES1OVF14:1;                 // 13 Checker 14 Result 1 OVF Flag Clear
    Uint16 RES1OVF15:1;                 // 14 Checker 15 Result 1 OVF Flag Clear
    Uint16 RES1OVF16:1;                 // 15 Checker 16 Result 1 OVF Flag Clear
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RES1OVFCLR_REG {
    Uint32  all;
    struct  RES1OVFCLR_BITS  bit;
};

struct RES2OVF_BITS {                   // bits description
    Uint16 RES2OVF1:1;                  // 0 Checker 1 Result 2 Overflow Flag
    Uint16 RES2OVF2:1;                  // 1 Checker 2 Result 2 Overflow Flag
    Uint16 RES2OVF3:1;                  // 2 Checker 3 Result 2 Overflow Flag
    Uint16 RES2OVF4:1;                  // 3 Checker 4 Result 2 Overflow Flag
    Uint16 RES2OVF5:1;                  // 4 Checker 5 Result 2 Overflow Flag
    Uint16 RES2OVF6:1;                  // 5 Checker 6 Result 2 Overflow Flag
    Uint16 RES2OVF7:1;                  // 6 Checker 7 Result 2 Overflow Flag
    Uint16 RES2OVF8:1;                  // 7 Checker 8 Result 2 Overflow Flag
    Uint16 RES2OVF9:1;                  // 8 Checker 9 Result 2 Overflow Flag
    Uint16 RES2OVF10:1;                 // 9 Checker 10 Result 2 Overflow Flag
    Uint16 RES2OVF11:1;                 // 10 Checker 11 Result 2 Overflow Flag
    Uint16 RES2OVF12:1;                 // 11 Checker 12 Result 2 Overflow Flag
    Uint16 RES2OVF13:1;                 // 12 Checker 13 Result 2 Overflow Flag
    Uint16 RES2OVF14:1;                 // 13 Checker 14 Result 2 Overflow Flag
    Uint16 RES2OVF15:1;                 // 14 Checker 15 Result 2 Overflow Flag
    Uint16 RES2OVF16:1;                 // 15 Checker 16 Result 2 Overflow Flag
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RES2OVF_REG {
    Uint32  all;
    struct  RES2OVF_BITS  bit;
};

struct RES2OVFCLR_BITS {                // bits description
    Uint16 RES2OVF1:1;                  // 0 Checker 1 Result 2  OVF Flag Clear
    Uint16 RES2OVF2:1;                  // 1 Checker 2 Result 2 OVF Flag Clear
    Uint16 RES2OVF3:1;                  // 2 Checker 3 Result 2 OVF Flag Clear
    Uint16 RES2OVF4:1;                  // 3 Checker 4 Result 2 OVF Flag Clear
    Uint16 RES2OVF5:1;                  // 4 Checker 5 Result 2  OVF Flag Clear
    Uint16 RES2OVF6:1;                  // 5 Checker 6 Result 2 OVF Flag Clear
    Uint16 RES2OVF7:1;                  // 6 Checker 7 Result 2 OVF Flag Clear
    Uint16 RES2OVF8:1;                  // 7 Checker 8 Result 2 OVF Flag Clear
    Uint16 RES2OVF9:1;                  // 8 Checker 9 Result 2  OVF Flag Clear
    Uint16 RES2OVF10:1;                 // 9 Checker 10 Result 2 OVF Flag Clear
    Uint16 RES2OVF11:1;                 // 10 Checker 11 Result 2 OVF Flag Clear
    Uint16 RES2OVF12:1;                 // 11 Checker 12 Result 2 OVF Flag Clear
    Uint16 RES2OVF13:1;                 // 12 Checker 13 Result 2  OVF Flag Clear
    Uint16 RES2OVF14:1;                 // 13 Checker 14 Result 2 OVF Flag Clear
    Uint16 RES2OVF15:1;                 // 14 Checker 15 Result 2 OVF Flag Clear
    Uint16 RES2OVF16:1;                 // 15 Checker 16 Result 2 OVF Flag Clear
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RES2OVFCLR_REG {
    Uint32  all;
    struct  RES2OVFCLR_BITS  bit;
};

struct CHECKINTFLG_BITS {               // bits description
    Uint16 CHECKINT:1;                  // 0 ADC Safety Checker Subsystem Interrupt Flag
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union CHECKINTFLG_REG {
    Uint16  all;
    struct  CHECKINTFLG_BITS  bit;
};

struct CHECKINTFLGCLR_BITS {            // bits description
    Uint16 CHECKINTCLR:1;               // 0 ADC Safety Checker Subsystem Interrupt Flag Clear
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union CHECKINTFLGCLR_REG {
    Uint16  all;
    struct  CHECKINTFLGCLR_BITS  bit;
};

struct CHECKINTSEL1_BITS {              // bits description
    Uint16 RES1OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 1
    Uint16 RES1OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 1
    Uint16 RES1OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 1
    Uint16 RES1OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 1
    Uint16 RES1OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 1
    Uint16 RES1OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 1
    Uint16 RES1OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 1
    Uint16 RES1OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 1
    Uint16 RES1OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 1
    Uint16 RES1OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 1
    Uint16 RES1OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 1
    Uint16 RES1OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 1
    Uint16 RES1OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 1
    Uint16 RES1OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 1
    Uint16 RES1OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 1
    Uint16 RES1OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 1
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKINTSEL1_REG {
    Uint32  all;
    struct  CHECKINTSEL1_BITS  bit;
};

struct CHECKINTSEL2_BITS {              // bits description
    Uint16 RES2OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 2
    Uint16 RES2OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 2
    Uint16 RES2OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 2
    Uint16 RES2OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 2
    Uint16 RES2OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 2
    Uint16 RES2OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 2
    Uint16 RES2OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 2
    Uint16 RES2OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 2
    Uint16 RES2OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 2
    Uint16 RES2OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 2
    Uint16 RES2OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 2
    Uint16 RES2OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 2
    Uint16 RES2OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 2
    Uint16 RES2OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 2
    Uint16 RES2OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 2
    Uint16 RES2OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKINTSEL2_REG {
    Uint32  all;
    struct  CHECKINTSEL2_BITS  bit;
};

struct CHECKINTSEL3_BITS {              // bits description
    Uint16 OOT1EN:1;                    // 0 Out-of-Tolerance Enable from Checker 1
    Uint16 OOT2EN:1;                    // 1 Out-of-Tolerance Enable from Checker 2
    Uint16 OOT3EN:1;                    // 2 Out-of-Tolerance Enable from Checker 3
    Uint16 OOT4EN:1;                    // 3 Out-of-Tolerance Enable from Checker 4
    Uint16 OOT5EN:1;                    // 4 Out-of-Tolerance Enable from Checker 5
    Uint16 OOT6EN:1;                    // 5 Out-of-Tolerance Enable from Checker 6
    Uint16 OOT7EN:1;                    // 6 Out-of-Tolerance Enable from Checker 7
    Uint16 OOT8EN:1;                    // 7 Out-of-Tolerance Enable from Checker 8
    Uint16 OOT9EN:1;                    // 8 Out-of-Tolerance Enable from Checker 9
    Uint16 OOT10EN:1;                   // 9 Out-of-Tolerance Enable from Checker 10
    Uint16 OOT11EN:1;                   // 10 Out-of-Tolerance Enable from Checker 11
    Uint16 OOT12EN:1;                   // 11 Out-of-Tolerance Enable from Checker 12
    Uint16 OOT13EN:1;                   // 12 Out-of-Tolerance Enable from Checker 13
    Uint16 OOT14EN:1;                   // 13 Out-of-Tolerance Enable from Checker 14
    Uint16 OOT15EN:1;                   // 14 Out-of-Tolerance Enable from Checker 15
    Uint16 OOT16EN:1;                   // 15 Out-of-Tolerance Enable from Checker 16
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKINTSEL3_REG {
    Uint32  all;
    struct  CHECKINTSEL3_BITS  bit;
};

struct CHECKEVT1SEL1_BITS {             // bits description
    Uint16 RES1OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 1
    Uint16 RES1OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 1
    Uint16 RES1OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 1
    Uint16 RES1OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 1
    Uint16 RES1OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 1
    Uint16 RES1OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 1
    Uint16 RES1OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 1
    Uint16 RES1OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 1
    Uint16 RES1OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 1
    Uint16 RES1OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 1
    Uint16 RES1OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 1
    Uint16 RES1OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 1
    Uint16 RES1OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 1
    Uint16 RES1OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 1
    Uint16 RES1OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 1
    Uint16 RES1OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 1
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT1SEL1_REG {
    Uint32  all;
    struct  CHECKEVT1SEL1_BITS  bit;
};

struct CHECKEVT1SEL2_BITS {             // bits description
    Uint16 RES2OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 2
    Uint16 RES2OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 2
    Uint16 RES2OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 2
    Uint16 RES2OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 2
    Uint16 RES2OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 2
    Uint16 RES2OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 2
    Uint16 RES2OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 2
    Uint16 RES2OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 2
    Uint16 RES2OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 2
    Uint16 RES2OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 2
    Uint16 RES2OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 2
    Uint16 RES2OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 2
    Uint16 RES2OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 2
    Uint16 RES2OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 2
    Uint16 RES2OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 2
    Uint16 RES2OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT1SEL2_REG {
    Uint32  all;
    struct  CHECKEVT1SEL2_BITS  bit;
};

struct CHECKEVT1SEL3_BITS {             // bits description
    Uint16 OOT1EN:1;                    // 0 Out-of-Tolerance Enable from Checker 1
    Uint16 OOT2EN:1;                    // 1 Out-of-Tolerance Enable from Checker 2
    Uint16 OOT3EN:1;                    // 2 Out-of-Tolerance Enable from Checker 3
    Uint16 OOT4EN:1;                    // 3 Out-of-Tolerance Enable from Checker 4
    Uint16 OOT5EN:1;                    // 4 Out-of-Tolerance Enable from Checker 5
    Uint16 OOT6EN:1;                    // 5 Out-of-Tolerance Enable from Checker 6
    Uint16 OOT7EN:1;                    // 6 Out-of-Tolerance Enable from Checker 7
    Uint16 OOT8EN:1;                    // 7 Out-of-Tolerance Enable from Checker 8
    Uint16 OOT9EN:1;                    // 8 Out-of-Tolerance Enable from Checker 9
    Uint16 OOT10EN:1;                   // 9 Out-of-Tolerance Enable from Checker 10
    Uint16 OOT11EN:1;                   // 10 Out-of-Tolerance Enable from Checker 11
    Uint16 OOT12EN:1;                   // 11 Out-of-Tolerance Enable from Checker 12
    Uint16 OOT13EN:1;                   // 12 Out-of-Tolerance Enable from Checker 13
    Uint16 OOT14EN:1;                   // 13 Out-of-Tolerance Enable from Checker 14
    Uint16 OOT15EN:1;                   // 14 Out-of-Tolerance Enable from Checker 15
    Uint16 OOT16EN:1;                   // 15 Out-of-Tolerance Enable from Checker 16
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT1SEL3_REG {
    Uint32  all;
    struct  CHECKEVT1SEL3_BITS  bit;
};

struct CHECKEVT2SEL1_BITS {             // bits description
    Uint16 RES1OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 1
    Uint16 RES1OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 1
    Uint16 RES1OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 1
    Uint16 RES1OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 1
    Uint16 RES1OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 1
    Uint16 RES1OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 1
    Uint16 RES1OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 1
    Uint16 RES1OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 1
    Uint16 RES1OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 1
    Uint16 RES1OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 1
    Uint16 RES1OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 1
    Uint16 RES1OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 1
    Uint16 RES1OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 1
    Uint16 RES1OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 1
    Uint16 RES1OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 1
    Uint16 RES1OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 1
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT2SEL1_REG {
    Uint32  all;
    struct  CHECKEVT2SEL1_BITS  bit;
};

struct CHECKEVT2SEL2_BITS {             // bits description
    Uint16 RES2OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 2
    Uint16 RES2OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 2
    Uint16 RES2OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 2
    Uint16 RES2OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 2
    Uint16 RES2OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 2
    Uint16 RES2OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 2
    Uint16 RES2OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 2
    Uint16 RES2OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 2
    Uint16 RES2OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 2
    Uint16 RES2OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 2
    Uint16 RES2OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 2
    Uint16 RES2OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 2
    Uint16 RES2OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 2
    Uint16 RES2OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 2
    Uint16 RES2OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 2
    Uint16 RES2OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT2SEL2_REG {
    Uint32  all;
    struct  CHECKEVT2SEL2_BITS  bit;
};

struct CHECKEVT2SEL3_BITS {             // bits description
    Uint16 OOT1EN:1;                    // 0 Out-of-Tolerance Enable from Checker 1
    Uint16 OOT2EN:1;                    // 1 Out-of-Tolerance Enable from Checker 2
    Uint16 OOT3EN:1;                    // 2 Out-of-Tolerance Enable from Checker 3
    Uint16 OOT4EN:1;                    // 3 Out-of-Tolerance Enable from Checker 4
    Uint16 OOT5EN:1;                    // 4 Out-of-Tolerance Enable from Checker 5
    Uint16 OOT6EN:1;                    // 5 Out-of-Tolerance Enable from Checker 6
    Uint16 OOT7EN:1;                    // 6 Out-of-Tolerance Enable from Checker 7
    Uint16 OOT8EN:1;                    // 7 Out-of-Tolerance Enable from Checker 8
    Uint16 OOT9EN:1;                    // 8 Out-of-Tolerance Enable from Checker 9
    Uint16 OOT10EN:1;                   // 9 Out-of-Tolerance Enable from Checker 10
    Uint16 OOT11EN:1;                   // 10 Out-of-Tolerance Enable from Checker 11
    Uint16 OOT12EN:1;                   // 11 Out-of-Tolerance Enable from Checker 12
    Uint16 OOT13EN:1;                   // 12 Out-of-Tolerance Enable from Checker 13
    Uint16 OOT14EN:1;                   // 13 Out-of-Tolerance Enable from Checker 14
    Uint16 OOT15EN:1;                   // 14 Out-of-Tolerance Enable from Checker 15
    Uint16 OOT16EN:1;                   // 15 Out-of-Tolerance Enable from Checker 16
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT2SEL3_REG {
    Uint32  all;
    struct  CHECKEVT2SEL3_BITS  bit;
};

struct CHECKEVT3SEL1_BITS {             // bits description
    Uint16 RES1OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 1
    Uint16 RES1OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 1
    Uint16 RES1OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 1
    Uint16 RES1OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 1
    Uint16 RES1OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 1
    Uint16 RES1OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 1
    Uint16 RES1OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 1
    Uint16 RES1OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 1
    Uint16 RES1OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 1
    Uint16 RES1OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 1
    Uint16 RES1OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 1
    Uint16 RES1OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 1
    Uint16 RES1OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 1
    Uint16 RES1OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 1
    Uint16 RES1OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 1
    Uint16 RES1OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 1
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT3SEL1_REG {
    Uint32  all;
    struct  CHECKEVT3SEL1_BITS  bit;
};

struct CHECKEVT3SEL2_BITS {             // bits description
    Uint16 RES2OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 2
    Uint16 RES2OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 2
    Uint16 RES2OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 2
    Uint16 RES2OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 2
    Uint16 RES2OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 2
    Uint16 RES2OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 2
    Uint16 RES2OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 2
    Uint16 RES2OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 2
    Uint16 RES2OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 2
    Uint16 RES2OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 2
    Uint16 RES2OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 2
    Uint16 RES2OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 2
    Uint16 RES2OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 2
    Uint16 RES2OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 2
    Uint16 RES2OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 2
    Uint16 RES2OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT3SEL2_REG {
    Uint32  all;
    struct  CHECKEVT3SEL2_BITS  bit;
};

struct CHECKEVT3SEL3_BITS {             // bits description
    Uint16 OOT1EN:1;                    // 0 Out-of-Tolerance Enable from Checker 1
    Uint16 OOT2EN:1;                    // 1 Out-of-Tolerance Enable from Checker 2
    Uint16 OOT3EN:1;                    // 2 Out-of-Tolerance Enable from Checker 3
    Uint16 OOT4EN:1;                    // 3 Out-of-Tolerance Enable from Checker 4
    Uint16 OOT5EN:1;                    // 4 Out-of-Tolerance Enable from Checker 5
    Uint16 OOT6EN:1;                    // 5 Out-of-Tolerance Enable from Checker 6
    Uint16 OOT7EN:1;                    // 6 Out-of-Tolerance Enable from Checker 7
    Uint16 OOT8EN:1;                    // 7 Out-of-Tolerance Enable from Checker 8
    Uint16 OOT9EN:1;                    // 8 Out-of-Tolerance Enable from Checker 9
    Uint16 OOT10EN:1;                   // 9 Out-of-Tolerance Enable from Checker 10
    Uint16 OOT11EN:1;                   // 10 Out-of-Tolerance Enable from Checker 11
    Uint16 OOT12EN:1;                   // 11 Out-of-Tolerance Enable from Checker 12
    Uint16 OOT13EN:1;                   // 12 Out-of-Tolerance Enable from Checker 13
    Uint16 OOT14EN:1;                   // 13 Out-of-Tolerance Enable from Checker 14
    Uint16 OOT15EN:1;                   // 14 Out-of-Tolerance Enable from Checker 15
    Uint16 OOT16EN:1;                   // 15 Out-of-Tolerance Enable from Checker 16
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT3SEL3_REG {
    Uint32  all;
    struct  CHECKEVT3SEL3_BITS  bit;
};

struct CHECKEVT4SEL1_BITS {             // bits description
    Uint16 RES1OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 1
    Uint16 RES1OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 1
    Uint16 RES1OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 1
    Uint16 RES1OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 1
    Uint16 RES1OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 1
    Uint16 RES1OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 1
    Uint16 RES1OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 1
    Uint16 RES1OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 1
    Uint16 RES1OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 1
    Uint16 RES1OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 1
    Uint16 RES1OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 1
    Uint16 RES1OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 1
    Uint16 RES1OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 1
    Uint16 RES1OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 1
    Uint16 RES1OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 1
    Uint16 RES1OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 1
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT4SEL1_REG {
    Uint32  all;
    struct  CHECKEVT4SEL1_BITS  bit;
};

struct CHECKEVT4SEL2_BITS {             // bits description
    Uint16 RES2OVF1EN:1;                // 0 Overflow Enable from Checker 1 Result 2
    Uint16 RES2OVF2EN:1;                // 1 Overflow Enable from Checker 2 Result 2
    Uint16 RES2OVF3EN:1;                // 2 Overflow Enable from Checker 3 Result 2
    Uint16 RES2OVF4EN:1;                // 3 Overflow Enable from Checker 4 Result 2
    Uint16 RES2OVF5EN:1;                // 4 Overflow Enable from Checker 5 Result 2
    Uint16 RES2OVF6EN:1;                // 5 Overflow Enable from Checker 6 Result 2
    Uint16 RES2OVF7EN:1;                // 6 Overflow Enable from Checker 7 Result 2
    Uint16 RES2OVF8EN:1;                // 7 Overflow Enable from Checker 8 Result 2
    Uint16 RES2OVF9EN:1;                // 8 Overflow Enable from Checker 9 Result 2
    Uint16 RES2OVF10EN:1;               // 9 Overflow Enable from Checker 10 Result 2
    Uint16 RES2OVF11EN:1;               // 10 Overflow Enable from Checker 11 Result 2
    Uint16 RES2OVF12EN:1;               // 11 Overflow Enable from Checker 12 Result 2
    Uint16 RES2OVF13EN:1;               // 12 Overflow Enable from Checker 13 Result 2
    Uint16 RES2OVF14EN:1;               // 13 Overflow Enable from Checker 14 Result 2
    Uint16 RES2OVF15EN:1;               // 14 Overflow Enable from Checker 15 Result 2
    Uint16 RES2OVF16EN:1;               // 15 Overflow Enable from Checker 16 Result 2
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT4SEL2_REG {
    Uint32  all;
    struct  CHECKEVT4SEL2_BITS  bit;
};

struct CHECKEVT4SEL3_BITS {             // bits description
    Uint16 OOT1EN:1;                    // 0 Out-of-Tolerance Enable from Checker 1
    Uint16 OOT2EN:1;                    // 1 Out-of-Tolerance Enable from Checker 2
    Uint16 OOT3EN:1;                    // 2 Out-of-Tolerance Enable from Checker 3
    Uint16 OOT4EN:1;                    // 3 Out-of-Tolerance Enable from Checker 4
    Uint16 OOT5EN:1;                    // 4 Out-of-Tolerance Enable from Checker 5
    Uint16 OOT6EN:1;                    // 5 Out-of-Tolerance Enable from Checker 6
    Uint16 OOT7EN:1;                    // 6 Out-of-Tolerance Enable from Checker 7
    Uint16 OOT8EN:1;                    // 7 Out-of-Tolerance Enable from Checker 8
    Uint16 OOT9EN:1;                    // 8 Out-of-Tolerance Enable from Checker 9
    Uint16 OOT10EN:1;                   // 9 Out-of-Tolerance Enable from Checker 10
    Uint16 OOT11EN:1;                   // 10 Out-of-Tolerance Enable from Checker 11
    Uint16 OOT12EN:1;                   // 11 Out-of-Tolerance Enable from Checker 12
    Uint16 OOT13EN:1;                   // 12 Out-of-Tolerance Enable from Checker 13
    Uint16 OOT14EN:1;                   // 13 Out-of-Tolerance Enable from Checker 14
    Uint16 OOT15EN:1;                   // 14 Out-of-Tolerance Enable from Checker 15
    Uint16 OOT16EN:1;                   // 15 Out-of-Tolerance Enable from Checker 16
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CHECKEVT4SEL3_REG {
    Uint32  all;
    struct  CHECKEVT4SEL3_BITS  bit;
};

struct ADC_SAFECHECK_INTEVT_REGS {
    union   OOTFLG_REG                       OOTFLG;                       // Checker Out-of-Tolerance Flag Register
    union   OOTFLGCLR_REG                    OOTFLGCLR;                    // Checker Out-of-Tolerance Flag Clear Register
    union   RES1OVF_REG                      RES1OVF;                      // Checker Overflow Result 1 Flag Register
    union   RES1OVFCLR_REG                   RES1OVFCLR;                   // Checker Overflow Result 1 Flag Clear Register
    union   RES2OVF_REG                      RES2OVF;                      // Checker Overflow Result 2 Flag Register
    union   RES2OVFCLR_REG                   RES2OVFCLR;                   // Checker Overflow Result 2 Flag Clear Register
    union   CHECKINTFLG_REG                  CHECKINTFLG;                  // Checker Interrupt Flag Register
    Uint16                                   rsvd1;                        // Reserved
    union   CHECKINTFLGCLR_REG               CHECKINTFLGCLR;               // Checker Interrupt Flag Clear Register
    Uint16                                   rsvd2;                        // Reserved
    union   CHECKINTSEL1_REG                 CHECKINTSEL1;                 // Checker Interrupt Source Select Register 1
    union   CHECKINTSEL2_REG                 CHECKINTSEL2;                 // Checker Interrupt Source Select Register 2
    union   CHECKINTSEL3_REG                 CHECKINTSEL3;                 // Checker Interrupt Source Select Register 3
    Uint16                                   rsvd3[2];                     // Reserved
    union   CHECKEVT1SEL1_REG                CHECKEVT1SEL1;                // Checker X-Bar EVT1 Source Select Register 1
    union   CHECKEVT1SEL2_REG                CHECKEVT1SEL2;                // Checker X-Bar EVT1 Source Select Register 2
    union   CHECKEVT1SEL3_REG                CHECKEVT1SEL3;                // Checker X-Bar EVT1 Source Select Register 3
    Uint16                                   rsvd4[2];                     // Reserved
    union   CHECKEVT2SEL1_REG                CHECKEVT2SEL1;                // Checker X-Bar EVT2 Source Select Register 1
    union   CHECKEVT2SEL2_REG                CHECKEVT2SEL2;                // Checker X-Bar EVT2 Source Select Register 2
    union   CHECKEVT2SEL3_REG                CHECKEVT2SEL3;                // Checker X-Bar EVT2 Source Select Register 3
    Uint16                                   rsvd5[2];                     // Reserved
    union   CHECKEVT3SEL1_REG                CHECKEVT3SEL1;                // Checker X-Bar EVT3 Source Select Register 1
    union   CHECKEVT3SEL2_REG                CHECKEVT3SEL2;                // Checker X-Bar EVT3 Source Select Register 2
    union   CHECKEVT3SEL3_REG                CHECKEVT3SEL3;                // Checker X-Bar EVT3 Source Select Register 3
    Uint16                                   rsvd6[2];                     // Reserved
    union   CHECKEVT4SEL1_REG                CHECKEVT4SEL1;                // Checker X-Bar EVT4 Source Select Register 1
    union   CHECKEVT4SEL2_REG                CHECKEVT4SEL2;                // Checker X-Bar EVT4 Source Select Register 2
    union   CHECKEVT4SEL3_REG                CHECKEVT4SEL3;                // Checker X-Bar EVT4 Source Select Register 3
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ADC_RESULT_REGS AdcaResultRegs;
extern volatile struct ADC_RESULT_REGS AdcbResultRegs;
extern volatile struct ADC_RESULT_REGS AdccResultRegs;
extern volatile struct ADC_REGS AdcaRegs;
extern volatile struct ADC_REGS AdcbRegs;
extern volatile struct ADC_REGS AdccRegs;
extern volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyIntEvtAgg1Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk1Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk2Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk3Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk4Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk5Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk6Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk7Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk8Regs;
#endif
#ifdef CPU2
extern volatile struct ADC_RESULT_REGS AdcaResultRegs;
extern volatile struct ADC_RESULT_REGS AdcbResultRegs;
extern volatile struct ADC_RESULT_REGS AdccResultRegs;
extern volatile struct ADC_REGS AdcaRegs;
extern volatile struct ADC_REGS AdcbRegs;
extern volatile struct ADC_REGS AdccRegs;
extern volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyIntEvtAgg2Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk1Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk2Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk3Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk4Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk5Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk6Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk7Regs;
extern volatile struct ADC_SAFECHECK_REGS ADCSafetyChk8Regs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
