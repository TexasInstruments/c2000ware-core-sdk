//###########################################################################
//
// FILE:    f28p65x_analogsubsys.h
//
// TITLE:   Definitions for the ANALOGSUBSYS registers.
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

#ifndef F28P65X_ANALOGSUBSYS_H
#define F28P65X_ANALOGSUBSYS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct INTERNALTESTCTL_BITS {           // bits description
    Uint16 TESTSEL:6;                   // 5:0 Test Select
    Uint16 rsvd1:3;                     // 8:6 Reserved
    Uint16 rsvd2:3;                     // 11:9 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 KEY:16;                      // 31:16 Key to Enable writes
};

union INTERNALTESTCTL_REG {
    Uint32  all;
    struct  INTERNALTESTCTL_BITS  bit;
};

struct CONFIGLOCK_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 AGPIOFILTER:1;               // 1 Locks AGPIOFILTER Register
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 AGPIOCTRL:1;                 // 3 Locks all AGPIOCTRL Register
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 GPIOINENACTRL:1;             // 6 Locks all GPIOINENACTRL Register
    Uint16 rsvd5:9;                     // 15:7 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union CONFIGLOCK_REG {
    Uint32  all;
    struct  CONFIGLOCK_BITS  bit;
};

struct TSNSCTL_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 Temperature Sensor Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union TSNSCTL_REG {
    Uint16  all;
    struct  TSNSCTL_BITS  bit;
};

struct ANAREFCTL_BITS {                 // bits description
    Uint16 ANAREFASEL:1;                // 0 Analog Reference Select
    Uint16 ANAREFBSEL:1;                // 1 Analog Reference B Select
    Uint16 ANAREFCSEL:1;                // 2 Analog Reference C Select
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 ANAREFA2P5SEL:1;             // 8 Analog Reference Select
    Uint16 ANAREFB2P5SEL:1;             // 9 Analog Reference B Select
    Uint16 ANAREFC2P5SEL:1;             // 10 Analog Reference C Select
    Uint16 rsvd2:4;                     // 14:11 Reserved
    Uint16 rsvd3:1;                     // 15 Reserved
};

union ANAREFCTL_REG {
    Uint16  all;
    struct  ANAREFCTL_BITS  bit;
};

struct VMONCTL_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:6;                     // 7:2 Reserved
    Uint16 BORLVMONDIS:1;               // 8 Disable BORL(ow) feature on VDDIO
    Uint16 rsvd4:7;                     // 15:9 Reserved
};

union VMONCTL_REG {
    Uint16  all;
    struct  VMONCTL_BITS  bit;
};

struct CMPHPMXSEL_BITS {                // bits description
    Uint16 CMP1HPMXSEL:3;               // 2:0 CMP1HPMXSEL bits
    Uint16 CMP2HPMXSEL:3;               // 5:3 CMP2HPMXSEL bits
    Uint16 CMP3HPMXSEL:3;               // 8:6 CMP3HPMXSEL bits
    Uint16 CMP4HPMXSEL:3;               // 11:9 CMP4HPMXSEL bits
    Uint16 CMP5HPMXSEL:3;               // 14:12 CMP5HPMXSEL bits
    Uint32 CMP6HPMXSEL:3;               // 17:15 CMP6HPMXSEL bits
    Uint16 CMP7HPMXSEL:3;               // 20:18 CMP7HPMXSEL bits
    Uint16 CMP8HPMXSEL:3;               // 23:21 CMP8HPMXSEL bits
    Uint16 CMP9HPMXSEL:3;               // 26:24 CMP9HPMXSEL bits
    Uint16 CMP10HPMXSEL:3;              // 29:27 CMP10HPMXSEL bits
    Uint16 rsvd1:2;                     // 31:30 Reserved
};

union CMPHPMXSEL_REG {
    Uint32  all;
    struct  CMPHPMXSEL_BITS  bit;
};

struct CMPLPMXSEL_BITS {                // bits description
    Uint16 CMP1LPMXSEL:3;               // 2:0 CMP1LPMXSEL bits
    Uint16 CMP2LPMXSEL:3;               // 5:3 CMP2LPMXSEL bits
    Uint16 CMP3LPMXSEL:3;               // 8:6 CMP3LPMXSEL bits
    Uint16 CMP4LPMXSEL:3;               // 11:9 CMP4LPMXSEL bits
    Uint16 CMP5LPMXSEL:3;               // 14:12 CMP5LPMXSEL bits
    Uint32 CMP6LPMXSEL:3;               // 17:15 CMP6LPMXSEL bits
    Uint16 CMP7LPMXSEL:3;               // 20:18 CMP7LPMXSEL bits
    Uint16 CMP8LPMXSEL:3;               // 23:21 CMP8LPMXSEL bits
    Uint16 CMP9LPMXSEL:3;               // 26:24 CMP9LPMXSEL bits
    Uint16 CMP10LPMXSEL:3;              // 29:27 CMP10LPMXSEL bits
    Uint16 rsvd1:2;                     // 31:30 Reserved
};

union CMPLPMXSEL_REG {
    Uint32  all;
    struct  CMPLPMXSEL_BITS  bit;
};

struct CMPHNMXSEL_BITS {                // bits description
    Uint16 CMP1HNMXSEL:1;               // 0 CMP1HNMXSEL bits
    Uint16 CMP2HNMXSEL:1;               // 1 CMP2HNMXSEL bits
    Uint16 CMP3HNMXSEL:1;               // 2 CMP3HNMXSEL bits
    Uint16 CMP4HNMXSEL:1;               // 3 CMP4HNMXSEL bits
    Uint16 CMP5HNMXSEL:1;               // 4 CMP5HNMXSEL bits
    Uint16 CMP6HNMXSEL:1;               // 5 CMP6HNMXSEL bits
    Uint16 CMP7HNMXSEL:1;               // 6 CMP7HNMXSEL bits
    Uint16 CMP8HNMXSEL:1;               // 7 CMP8HNMXSEL bits
    Uint16 CMP9HNMXSEL:1;               // 8 CMP9HNMXSEL bits
    Uint16 CMP10HNMXSEL:1;              // 9 CMP10HNMXSEL bits
    Uint16 CMP11HNMXSEL:1;              // 10 CMP11HNMXSEL bits
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union CMPHNMXSEL_REG {
    Uint16  all;
    struct  CMPHNMXSEL_BITS  bit;
};

struct CMPLNMXSEL_BITS {                // bits description
    Uint16 CMP1LNMXSEL:1;               // 0 CMP1LNMXSEL bits
    Uint16 CMP2LNMXSEL:1;               // 1 CMP2LNMXSEL bits
    Uint16 CMP3LNMXSEL:1;               // 2 CMP3LNMXSEL bits
    Uint16 CMP4LNMXSEL:1;               // 3 CMP4LNMXSEL bits
    Uint16 CMP5LNMXSEL:1;               // 4 CMP5LNMXSEL bits
    Uint16 CMP6LNMXSEL:1;               // 5 CMP6LNMXSEL bits
    Uint16 CMP7LNMXSEL:1;               // 6 CMP7LNMXSEL bits
    Uint16 CMP8LNMXSEL:1;               // 7 CMP8LNMXSEL bits
    Uint16 CMP9LNMXSEL:1;               // 8 CMP9LNMXSEL bits
    Uint16 CMP10LNMXSEL:1;              // 9 CMP10LNMXSEL bits
    Uint16 CMP11LNMXSEL:1;              // 10 CMP11LNMXSEL bits
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union CMPLNMXSEL_REG {
    Uint16  all;
    struct  CMPLNMXSEL_BITS  bit;
};

struct ADCDACLOOPBACK_BITS {            // bits description
    Uint16 ENLB2ADCA:1;                 // 0 Enable COMPDACA loopback to ADCA
    Uint16 ENLB2ADCB:1;                 // 1 Enable COMPDACA loopback to ADCB
    Uint16 ENLB2ADCC:1;                 // 2 Enable COMPDACA loopback to ADCC
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 KEY:16;                      // 31:16 Key to enable writes
};

union ADCDACLOOPBACK_REG {
    Uint32  all;
    struct  ADCDACLOOPBACK_BITS  bit;
};

struct LOCK_BITS {                      // bits description
    Uint16 TSNSCTL:1;                   // 0 TSNSCTL Register lock bit
    Uint16 ANAREFCTL:1;                 // 1 ANAREFCTL Register lock bit
    Uint16 VMONCTL:1;                   // 2 VMONCTL Register lock bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 CMPHPMXSEL:1;                // 5 CMPHPMXSEL Register lock bit
    Uint16 CMPLPMXSEL:1;                // 6 CMPLPMXSEL Register lock bit
    Uint16 CMPHNMXSEL:1;                // 7 CMPHNMXSEL Register lock bit
    Uint16 CMPLNMXSEL:1;                // 8 CMPLNMXSEL Register lock bit
    Uint16 VREGCTL:1;                   // 9 VREGCTL Register lock bit
    Uint16 CMPSSCTL:1;                  // 10 CMPSSCTL Register lock bit
    Uint16 CMPHPMXSEL1:1;               // 11 CMPHPMXSEL1 Register lock bit
    Uint16 CMPLPMXSEL1:1;               // 12 CMPLPMXSEL1 Register lock bit
    Uint16 rsvd3:3;                     // 15:13 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union LOCK_REG {
    Uint32  all;
    struct  LOCK_BITS  bit;
};

struct CMPHPMXSEL1_BITS {               // bits description
    Uint16 CMP11HPMXSEL:3;              // 2:0 CMP15HPMXSEL bits
    Uint16 rsvd1:3;                     // 5:3 Reserved
    Uint16 rsvd2:3;                     // 8:6 Reserved
    Uint16 rsvd3:3;                     // 11:9 Reserved
    Uint16 rsvd4:3;                     // 14:12 Reserved
    Uint16 rsvd5:1;                     // 15 Reserved
    Uint16 rsvd6:2;                     // 17:16 Reserved
    Uint16 rsvd7:3;                     // 20:18 Reserved
    Uint16 rsvd8:3;                     // 23:21 Reserved
    Uint16 rsvd9:3;                     // 26:24 Reserved
    Uint16 rsvd10:3;                    // 29:27 Reserved
    Uint16 rsvd11:2;                    // 31:30 Reserved
};

union CMPHPMXSEL1_REG {
    Uint32  all;
    struct  CMPHPMXSEL1_BITS  bit;
};

struct CMPLPMXSEL1_BITS {               // bits description
    Uint16 CMP11LPMXSEL:3;              // 2:0 CMP15LPMXSEL bits
    Uint16 rsvd1:3;                     // 5:3 Reserved
    Uint16 rsvd2:3;                     // 8:6 Reserved
    Uint16 rsvd3:3;                     // 11:9 Reserved
    Uint16 rsvd4:3;                     // 14:12 Reserved
    Uint16 rsvd5:1;                     // 15 Reserved
    Uint16 rsvd6:2;                     // 17:16 Reserved
    Uint16 rsvd7:3;                     // 20:18 Reserved
    Uint16 rsvd8:3;                     // 23:21 Reserved
    Uint16 rsvd9:3;                     // 26:24 Reserved
    Uint16 rsvd10:3;                    // 29:27 Reserved
    Uint16 rsvd11:2;                    // 31:30 Reserved
};

union CMPLPMXSEL1_REG {
    Uint32  all;
    struct  CMPLPMXSEL1_BITS  bit;
};

struct ADCSOCFRCGB_BITS {               // bits description
    Uint16 SOC0:1;                      // 0 Generate synchronous SW trigger for SOC0
    Uint16 SOC1:1;                      // 1 Generate synchronous SW trigger for SOC1
    Uint16 SOC2:1;                      // 2 Generate synchronous SW trigger for SOC2
    Uint16 SOC3:1;                      // 3 Generate synchronous SW trigger for SOC3
    Uint16 SOC4:1;                      // 4 Generate synchronous SW trigger for SOC4
    Uint16 SOC5:1;                      // 5 Generate synchronous SW trigger for SOC5
    Uint16 SOC6:1;                      // 6 Generate synchronous SW trigger for SOC6
    Uint16 SOC7:1;                      // 7 Generate synchronous SW trigger for SOC7
    Uint16 SOC8:1;                      // 8 Generate synchronous SW trigger for SOC8
    Uint16 SOC9:1;                      // 9 Generate synchronous SW trigger for SOC9
    Uint16 SOC10:1;                     // 10 Generate synchronous SW trigger for SOC10
    Uint16 SOC11:1;                     // 11 Generate synchronous SW trigger for SOC11
    Uint16 SOC12:1;                     // 12 Generate synchronous SW trigger for SOC12
    Uint16 SOC13:1;                     // 13 Generate synchronous SW trigger for SOC13
    Uint16 SOC14:1;                     // 14 Generate synchronous SW trigger for SOC14
    Uint16 SOC15:1;                     // 15 Generate synchronous SW trigger for SOC15
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ADCSOCFRCGB_REG {
    Uint32  all;
    struct  ADCSOCFRCGB_BITS  bit;
};

struct ADCSOCFRCGBSEL_BITS {            // bits description
    Uint16 ADCA:1;                      // 0 Generate synchronous SW trigger for ADCA
    Uint16 ADCB:1;                      // 1 Generate synchronous SW trigger for ADCB
    Uint16 ADCC:1;                      // 2 Generate synchronous SW trigger for ADCC
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ADCSOCFRCGBSEL_REG {
    Uint16  all;
    struct  ADCSOCFRCGBSEL_BITS  bit;
};

struct AGPIOFILTER_BITS {               // bits description
    Uint16 RIGHT:2;                     // 1:0 AGPIOFILTER Control for right side pins
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 BOTTOM:2;                    // 9:8 AGPIOFILTER Control for bottom side pins
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union AGPIOFILTER_REG {
    Uint16  all;
    struct  AGPIOFILTER_BITS  bit;
};

struct AGPIOCTRLG_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 GPIO198:1;                   // 6 AGPIOCTRL for GPIO198
    Uint16 GPIO199:1;                   // 7 AGPIOCTRL for GPIO199
    Uint16 GPIO200:1;                   // 8 AGPIOCTRL for GPIO200
    Uint16 GPIO201:1;                   // 9 AGPIOCTRL for GPIO201
    Uint16 GPIO202:1;                   // 10 AGPIOCTRL for GPIO202
    Uint16 GPIO203:1;                   // 11 AGPIOCTRL for GPIO203
    Uint16 GPIO204:1;                   // 12 AGPIOCTRL for GPIO204
    Uint16 GPIO205:1;                   // 13 AGPIOCTRL for GPIO205
    Uint16 GPIO206:1;                   // 14 AGPIOCTRL for GPIO206
    Uint16 GPIO207:1;                   // 15 AGPIOCTRL for GPIO207
    Uint16 GPIO208:1;                   // 16 AGPIOCTRL for GPIO208
    Uint16 GPIO209:1;                   // 17 AGPIOCTRL for GPIO209
    Uint16 GPIO210:1;                   // 18 AGPIOCTRL for GPIO210
    Uint16 GPIO211:1;                   // 19 AGPIOCTRL for GPIO211
    Uint16 GPIO212:1;                   // 20 AGPIOCTRL for GPIO212
    Uint16 GPIO213:1;                   // 21 AGPIOCTRL for GPIO213
    Uint16 GPIO214:1;                   // 22 AGPIOCTRL for GPIO214
    Uint16 GPIO215:1;                   // 23 AGPIOCTRL for GPIO215
    Uint16 GPIO216:1;                   // 24 AGPIOCTRL for GPIO216
    Uint16 GPIO217:1;                   // 25 AGPIOCTRL for GPIO217
    Uint16 GPIO218:1;                   // 26 AGPIOCTRL for GPIO218
    Uint16 GPIO219:1;                   // 27 AGPIOCTRL for GPIO219
    Uint16 rsvd7:1;                     // 28 Reserved
    Uint16 rsvd8:1;                     // 29 Reserved
    Uint16 rsvd9:1;                     // 30 Reserved
    Uint16 rsvd10:1;                    // 31 Reserved
};

union AGPIOCTRLG_REG {
    Uint32  all;
    struct  AGPIOCTRLG_BITS  bit;
};

struct AGPIOCTRLH_BITS {                // bits description
    Uint16 GPIO224:1;                   // 0 AGPIOCTRL for GPIO224
    Uint16 GPIO225:1;                   // 1 AGPIOCTRL for GPIO225
    Uint16 GPIO226:1;                   // 2 AGPIOCTRL for GPIO226
    Uint16 GPIO227:1;                   // 3 AGPIOCTRL for GPIO227
    Uint16 GPIO228:1;                   // 4 AGPIOCTRL for GPIO228
    Uint16 GPIO229:1;                   // 5 AGPIOCTRL for GPIO229
    Uint16 GPIO230:1;                   // 6 AGPIOCTRL for GPIO230
    Uint16 GPIO231:1;                   // 7 AGPIOCTRL for GPIO231
    Uint16 GPIO232:1;                   // 8 AGPIOCTRL for GPIO232
    Uint16 GPIO233:1;                   // 9 AGPIOCTRL for GPIO233
    Uint16 GPIO234:1;                   // 10 AGPIOCTRL for GPIO234
    Uint16 GPIO235:1;                   // 11 AGPIOCTRL for GPIO235
    Uint16 GPIO236:1;                   // 12 AGPIOCTRL for GPIO236
    Uint16 GPIO237:1;                   // 13 AGPIOCTRL for GPIO237
    Uint16 GPIO238:1;                   // 14 AGPIOCTRL for GPIO238
    Uint16 GPIO239:1;                   // 15 AGPIOCTRL for GPIO239
    Uint16 GPIO240:1;                   // 16 AGPIOCTRL for GPIO240
    Uint16 GPIO241:1;                   // 17 AGPIOCTRL for GPIO241
    Uint16 GPIO242:1;                   // 18 AGPIOCTRL for GPIO242
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 rsvd2:1;                     // 20 Reserved
    Uint16 rsvd3:1;                     // 21 Reserved
    Uint16 rsvd4:1;                     // 22 Reserved
    Uint16 rsvd5:1;                     // 23 Reserved
    Uint16 rsvd6:1;                     // 24 Reserved
    Uint16 rsvd7:1;                     // 25 Reserved
    Uint16 rsvd8:1;                     // 26 Reserved
    Uint16 rsvd9:1;                     // 27 Reserved
    Uint16 rsvd10:1;                    // 28 Reserved
    Uint16 rsvd11:1;                    // 29 Reserved
    Uint16 rsvd12:1;                    // 30 Reserved
    Uint16 rsvd13:1;                    // 31 Reserved
};

union AGPIOCTRLH_REG {
    Uint32  all;
    struct  AGPIOCTRLH_BITS  bit;
};

struct GPIOINENACTRL_BITS {             // bits description
    Uint16 GPIO0:1;                     // 0 Input Buffer Control for GPIO0
    Uint16 GPIO23:1;                    // 1 Input Buffer Control for GPIO23
    Uint16 GPIO25:1;                    // 2 Input Buffer Control for GPIO25
    Uint16 GPIO31:1;                    // 3 Input Buffer Control for GPIO31
    Uint16 GPIO46:1;                    // 4 Input Buffer Control for GPIO46
    Uint16 GPIO103:1;                   // 5 Input Buffer Control for GPIO103
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union GPIOINENACTRL_REG {
    Uint32  all;
    struct  GPIOINENACTRL_BITS  bit;
};

struct ANALOG_SUBSYS_REGS {
    Uint16                                   rsvd1[74];                    // Reserved
    union   INTERNALTESTCTL_REG              INTERNALTESTCTL;              // INTERNALTEST Node Control Register
    Uint16                                   rsvd2[18];                    // Reserved
    union   CONFIGLOCK_REG                   CONFIGLOCK;                   // Lock Register for all the config registers.
    union   TSNSCTL_REG                      TSNSCTL;                      // Temperature Sensor Control Register
    Uint16                                   rsvd3[7];                     // Reserved
    union   ANAREFCTL_REG                    ANAREFCTL;                    // Analog Reference Control Register.
    Uint16                                   rsvd4[7];                     // Reserved
    union   VMONCTL_REG                      VMONCTL;                      // Voltage Monitor Control Register
    Uint16                                   rsvd5[17];                    // Reserved
    union   CMPHPMXSEL_REG                   CMPHPMXSEL;                   // Bits to select one of the many sources on CopmHP inputs. Refer to Pimux diagram for details.
    union   CMPLPMXSEL_REG                   CMPLPMXSEL;                   // Bits to select one of the many sources on CopmLP inputs. Refer to Pimux diagram for details.
    union   CMPHNMXSEL_REG                   CMPHNMXSEL;                   // Bits to select one of the many sources on CopmHN inputs. Refer to Pimux diagram for details.
    union   CMPLNMXSEL_REG                   CMPLNMXSEL;                   // Bits to select one of the many sources on CopmLN inputs. Refer to Pimux diagram for details.
    union   ADCDACLOOPBACK_REG               ADCDACLOOPBACK;               // Enabble loopback from DAC to ADCs
    Uint16                                   rsvd6[4];                     // Reserved
    union   LOCK_REG                         LOCK;                         // Lock Register
    union   CMPHPMXSEL1_REG                  CMPHPMXSEL1;                  // Bits to select one of the many sources on CopmHP inputs. Refer to Pimux diagram for details.
    union   CMPLPMXSEL1_REG                  CMPLPMXSEL1;                  // Bits to select one of the many sources on CopmLP inputs. Refer to Pimux diagram for details.
    Uint16                                   rsvd7[122];                   // Reserved
    union   ADCSOCFRCGB_REG                  ADCSOCFRCGB;                  // ADC Global SOC Force
    union   ADCSOCFRCGBSEL_REG               ADCSOCFRCGBSEL;               // ADC Global SOC Force Select
    union   AGPIOFILTER_REG                  AGPIOFILTER;                  // AGPIO Filter Control Register
    Uint16                                   rsvd8[14];                    // Reserved
    union   AGPIOCTRLG_REG                   AGPIOCTRLG;                   // AGPIO Control Register
    union   AGPIOCTRLH_REG                   AGPIOCTRLH;                   // AGPIO Control Register
    Uint16                                   rsvd9[16];                    // Reserved
    union   GPIOINENACTRL_REG                GPIOINENACTRL;                // GPIOINENACTRL Control Register
};

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
