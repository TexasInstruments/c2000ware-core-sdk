//###########################################################################
//
// FILE:    f28p55x_analogsubsys.h
//
// TITLE:   Definitions for the ANALOGSUBSYS registers.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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

#ifndef F28P55X_ANALOGSUBSYS_H
#define F28P55X_ANALOGSUBSYS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct ADCOSDETECT_BITS {               // bits description
    Uint16 rsvd1:4;                     // 3:0 Reserved
    Uint16 OSDETECT_EN:1;               // 4 Enable OS Detect Logic
    Uint16 DETECTCFG:3;                 // 7:5 OS detect config bits
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union ADCOSDETECT_REG {
    Uint16  all;
    struct  ADCOSDETECT_BITS  bit;
};

struct REFCONFIGB_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:2;                     // 4:3 Reserved
    Uint16 ADC_ATB_ENA:2;               // 6:5 ADC testmux enable
    Uint16 ADC_ATB_ENB:2;               // 8:7 ADC testmux enable
    Uint16 ADC_ATB_ENC:2;               // 10:9 ADC testmux enable
    Uint16 ADC_ATB_END:2;               // 12:11 ADC testmux enable
    Uint16 ADC_ATB_ENE:2;               // 14:13 ADC testmux enable
    Uint16 rsvd5:1;                     // 15 Reserved
    Uint16 rsvd6:2;                     // 17:16 Reserved
    Uint16 rsvd7:2;                     // 19:18 Reserved
    Uint16 rsvd8:12;                    // 31:20 Reserved
};

union REFCONFIGB_REG {
    Uint32  all;
    struct  REFCONFIGB_BITS  bit;
};

struct INTERNALTESTCTL_BITS {           // bits description
    Uint16 TESTSEL:6;                   // 5:0 Test Select
    Uint16 rsvd1:3;                     // 8:6 Reserved
    Uint16 rsvd2:7;                     // 15:9 Reserved
    Uint16 KEY:16;                      // 31:16 Key to Enable writes
};

union INTERNALTESTCTL_REG {
    Uint32  all;
    struct  INTERNALTESTCTL_BITS  bit;
};

struct CONFIGLOCK_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 AGPIOCTRL:1;                 // 3 Locks all AGPIOCTRL Register
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 GPIOINENACTRL:1;             // 6 Locks all GPIOINENACTRL Register
    Uint16 rsvd6:9;                     // 15:7 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
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

struct ANAREFPCTL_BITS {                // bits description
    Uint16 REFPMUXSELA:2;               // 1:0 Analog Reference Select ADCA
    Uint16 REFPMUXSELB:2;               // 3:2 Analog Reference Select ADCB
    Uint16 REFPMUXSELC:2;               // 5:4 Analog Reference Select ADCC
    Uint16 REFPMUXSELD:2;               // 7:6 Analog Reference Select ADCD
    Uint16 REFPMUXSELE:2;               // 9:8 Analog Reference Select ADCE
    Uint16 ANAREFA1P65SEL:1;            // 10 1.65v Reference Select ADCA
    Uint16 ANAREFB1P65SEL:1;            // 11 1.65v Reference Select ADCB
    Uint16 ANAREFC1P65SEL:1;            // 12 1.65v Reference Select ADCC
    Uint16 ANAREFD1P65SEL:1;            // 13 1.65v Reference Select ADCD
    Uint16 ANAREFE1P65SEL:1;            // 14 1.65v Reference Select ADCE
    Uint16 rsvd1:1;                     // 15 Reserved
};

union ANAREFPCTL_REG {
    Uint16  all;
    struct  ANAREFPCTL_BITS  bit;
};

struct ANAREFNCTL_BITS {                // bits description
    Uint16 REFNMUXSELA:2;               // 1:0 Analog Reference Select ADCA
    Uint16 REFNMUXSELB:2;               // 3:2 Analog Reference Select ADCB
    Uint16 REFNMUXSELC:2;               // 5:4 Analog Reference Select ADCC
    Uint16 REFNMUXSELD:2;               // 7:6 Analog Reference Select ADCD
    Uint16 REFNMUXSELE:2;               // 9:8 Analog Reference Select ADCE
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union ANAREFNCTL_REG {
    Uint16  all;
    struct  ANAREFNCTL_BITS  bit;
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
    Uint16 rsvd1:3;                     // 14:12 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 rsvd3:3;                     // 18:16 Reserved
    Uint16 rsvd4:3;                     // 21:19 Reserved
    Uint16 rsvd5:10;                    // 31:22 Reserved
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
    Uint16 rsvd1:3;                     // 14:12 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 rsvd3:3;                     // 18:16 Reserved
    Uint16 rsvd4:3;                     // 21:19 Reserved
    Uint16 rsvd5:10;                    // 31:22 Reserved
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
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:9;                     // 15:7 Reserved
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
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:9;                     // 15:7 Reserved
};

union CMPLNMXSEL_REG {
    Uint16  all;
    struct  CMPLNMXSEL_BITS  bit;
};

struct ADCDACLOOPBACK_BITS {            // bits description
    Uint16 ENLB2ADCA:1;                 // 0 Enable DACA loopback to ADCA
    Uint16 ENLB2ADCB:1;                 // 1 Enable DACA loopback to ADCB
    Uint16 ENLB2ADCC:1;                 // 2 Enable DACA loopback to ADCC
    Uint16 ENLB2ADCD:1;                 // 3 Enable DACA loopback to ADCD
    Uint16 ENLB2ADCE:1;                 // 4 Enable DACA loopback to ADCE
    Uint16 rsvd1:11;                    // 15:5 Reserved
    Uint16 KEY:16;                      // 31:16 Key to enable writes
};

union ADCDACLOOPBACK_REG {
    Uint32  all;
    struct  ADCDACLOOPBACK_BITS  bit;
};

struct CMPSSCTL_BITS {                  // bits description
    Uint16 CMP1LDACOUTEN:1;             // 0 Enable general purpose DAC functionality for CMPSS1.COMPDACL
    Uint16 rsvd1:14;                    // 14:1 Reserved
    Uint16 CMPSSCTLEN:1;                // 15 Enable the CMPSSCTL Register
};

union CMPSSCTL_REG {
    Uint16  all;
    struct  CMPSSCTL_BITS  bit;
};

struct CMPSSDACBUFCONFIG_BITS {         // bits description
    Uint16 CMPSSADACL:8;                // 7:0 Configuration bits for CMPSS DACA
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:8;                     // 23:16 Reserved
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union CMPSSDACBUFCONFIG_REG {
    Uint32  all;
    struct  CMPSSDACBUFCONFIG_BITS  bit;
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
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union LOCK_REG {
    Uint32  all;
    struct  LOCK_BITS  bit;
};

struct AGPIOCTRLA_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 rsvd7:1;                     // 6 Reserved
    Uint16 rsvd8:1;                     // 7 Reserved
    Uint16 rsvd9:1;                     // 8 Reserved
    Uint16 rsvd10:1;                    // 9 Reserved
    Uint16 rsvd11:1;                    // 10 Reserved
    Uint16 GPIO11:1;                    // 11 AGPIOCTRL for GPIO11
    Uint16 GPIO12:1;                    // 12 AGPIOCTRL for GPIO12
    Uint16 GPIO13:1;                    // 13 AGPIOCTRL for GPIO13
    Uint16 rsvd12:1;                    // 14 Reserved
    Uint16 rsvd13:1;                    // 15 Reserved
    Uint16 GPIO16:1;                    // 16 AGPIOCTRL for GPIO16
    Uint16 GPIO17:1;                    // 17 AGPIOCTRL for GPIO17
    Uint16 rsvd14:1;                    // 18 Reserved
    Uint16 rsvd15:1;                    // 19 Reserved
    Uint16 GPIO20:1;                    // 20 AGPIOCTRL for GPIO20
    Uint16 GPIO21:1;                    // 21 AGPIOCTRL for GPIO21
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 GPIO24:1;                    // 24 AGPIOCTRL for GPIO24
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 GPIO28:1;                    // 28 AGPIOCTRL for GPIO28
    Uint16 rsvd21:1;                    // 29 Reserved
    Uint16 rsvd22:1;                    // 30 Reserved
    Uint16 rsvd23:1;                    // 31 Reserved
};

union AGPIOCTRLA_REG {
    Uint32  all;
    struct  AGPIOCTRLA_BITS  bit;
};

struct AGPIOCTRLB_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 GPIO33:1;                    // 1 AGPIOCTRL for GPIO33
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:1;                     // 6 Reserved
    Uint16 rsvd7:1;                     // 7 Reserved
    Uint16 rsvd8:1;                     // 8 Reserved
    Uint16 rsvd9:1;                     // 9 Reserved
    Uint16 rsvd10:1;                    // 10 Reserved
    Uint16 rsvd11:1;                    // 11 Reserved
    Uint16 rsvd12:1;                    // 12 Reserved
    Uint16 rsvd13:1;                    // 13 Reserved
    Uint16 rsvd14:1;                    // 14 Reserved
    Uint16 rsvd15:1;                    // 15 Reserved
    Uint16 rsvd16:1;                    // 16 Reserved
    Uint16 rsvd17:1;                    // 17 Reserved
    Uint16 rsvd18:1;                    // 18 Reserved
    Uint16 rsvd19:1;                    // 19 Reserved
    Uint16 rsvd20:1;                    // 20 Reserved
    Uint16 rsvd21:1;                    // 21 Reserved
    Uint16 rsvd22:1;                    // 22 Reserved
    Uint16 rsvd23:1;                    // 23 Reserved
    Uint16 rsvd24:1;                    // 24 Reserved
    Uint16 rsvd25:1;                    // 25 Reserved
    Uint16 rsvd26:1;                    // 26 Reserved
    Uint16 rsvd27:1;                    // 27 Reserved
    Uint16 rsvd28:1;                    // 28 Reserved
    Uint16 rsvd29:1;                    // 29 Reserved
    Uint16 rsvd30:1;                    // 30 Reserved
    Uint16 rsvd31:1;                    // 31 Reserved
};

union AGPIOCTRLB_REG {
    Uint32  all;
    struct  AGPIOCTRLB_BITS  bit;
};

struct AGPIOCTRLG_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 rsvd7:1;                     // 6 Reserved
    Uint16 rsvd8:1;                     // 7 Reserved
    Uint16 rsvd9:1;                     // 8 Reserved
    Uint16 rsvd10:1;                    // 9 Reserved
    Uint16 rsvd11:1;                    // 10 Reserved
    Uint16 rsvd12:1;                    // 11 Reserved
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 rsvd17:1;                    // 16 Reserved
    Uint16 rsvd18:1;                    // 17 Reserved
    Uint16 rsvd19:1;                    // 18 Reserved
    Uint16 GPIO211:1;                   // 19 AGPIOCTRL for GPIO211
    Uint16 GPIO212:1;                   // 20 AGPIOCTRL for GPIO212
    Uint16 GPIO213:1;                   // 21 AGPIOCTRL for GPIO213
    Uint16 GPIO214:1;                   // 22 AGPIOCTRL for GPIO214
    Uint16 GPIO215:1;                   // 23 AGPIOCTRL for GPIO215
    Uint16 rsvd20:1;                    // 24 Reserved
    Uint16 rsvd21:1;                    // 25 Reserved
    Uint16 rsvd22:1;                    // 26 Reserved
    Uint16 rsvd23:1;                    // 27 Reserved
    Uint16 rsvd24:1;                    // 28 Reserved
    Uint16 rsvd25:1;                    // 29 Reserved
    Uint16 rsvd26:1;                    // 30 Reserved
    Uint16 rsvd27:1;                    // 31 Reserved
};

union AGPIOCTRLG_REG {
    Uint32  all;
    struct  AGPIOCTRLG_BITS  bit;
};

struct AGPIOCTRLH_BITS {                // bits description
    Uint16 GPIO224:1;                   // 0 AGPIOCTRL for GPIO224
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 AGPIOCTRL for GPIO226
    Uint16 GPIO227:1;                   // 3 AGPIOCTRL for GPIO227
    Uint16 GPIO228:1;                   // 4 AGPIOCTRL for GPIO228
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 AGPIOCTRL for GPIO230
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 GPIO236:1;                   // 12 AGPIOCTRL for GPIO236
    Uint16 rsvd8:1;                     // 13 Reserved
    Uint16 rsvd9:1;                     // 14 Reserved
    Uint16 rsvd10:1;                    // 15 Reserved
    Uint16 rsvd11:1;                    // 16 Reserved
    Uint16 rsvd12:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 AGPIOCTRL for GPIO242
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 GPIO247:1;                   // 23 AGPIOCTRL for GPIO247
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 GPIO253:1;                   // 29 AGPIOCTRL for GPIO253
    Uint16 rsvd22:1;                    // 30 Reserved
    Uint16 rsvd23:1;                    // 31 Reserved
};

union AGPIOCTRLH_REG {
    Uint32  all;
    struct  AGPIOCTRLH_BITS  bit;
};

struct GPIOINENACTRL_BITS {             // bits description
    Uint16 GPIO20:1;                    // 0 Input Buffer Control for GPIO20
    Uint16 GPIO21:1;                    // 1 Input Buffer Control for GPIO21
    Uint16 GPIO62:1;                    // 2 Input Buffer Control for GPIO62
    Uint16 GPIO63:1;                    // 3 Input Buffer Control for GPIO63
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union GPIOINENACTRL_REG {
    Uint32  all;
    struct  GPIOINENACTRL_BITS  bit;
};

struct IO_DRVSEL_BITS {                 // bits description
    Uint16 DRVSEL_GPIO2:1;              // 0 Drive select for GPIO 2
    Uint16 DRVSEL_GPIO3:1;              // 1 Drive select for GPIO 3
    Uint16 DRVSEL_GPIO9:1;              // 2 Drive select for GPIO 9
    Uint16 DRVSEL_GPIO32:1;             // 3 Drive select for GPIO 32
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union IO_DRVSEL_REG {
    Uint16  all;
    struct  IO_DRVSEL_BITS  bit;
};

struct IO_MODESEL_BITS {                // bits description
    Uint16 MODESEL_GPIO2:1;             // 0 Mode select for GPIO 2
    Uint16 MODESEL_GPIO3:1;             // 1 Mode select for GPIO 3
    Uint16 MODESEL_GPIO9:1;             // 2 Mode select for GPIO 9
    Uint16 MODESEL_GPIO32:1;            // 3 Mode select for GPIO 32
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union IO_MODESEL_REG {
    Uint16  all;
    struct  IO_MODESEL_BITS  bit;
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
    Uint16 ADCD:1;                      // 3 Generate synchronous SW trigger for ADCD
    Uint16 ADCE:1;                      // 4 Generate synchronous SW trigger for ADCE
    Uint16 rsvd1:11;                    // 15:5 Reserved
};

union ADCSOCFRCGBSEL_REG {
    Uint16  all;
    struct  ADCSOCFRCGBSEL_BITS  bit;
};

struct ANALOG_SUBSYS_REGS {
    Uint16                                   rsvd1[38];                    // Reserved
    union   ADCOSDETECT_REG                  ADCOSDETECT;                  // I2V Logic Control
    Uint16                                   rsvd2[15];                    // Reserved
    union   REFCONFIGB_REG                   REFCONFIGB;                   // Config register for analog reference B.
    Uint16                                   rsvd3[18];                    // Reserved
    union   INTERNALTESTCTL_REG              INTERNALTESTCTL;              // INTERNALTEST Node Control Register
    Uint16                                   rsvd4[18];                    // Reserved
    union   CONFIGLOCK_REG                   CONFIGLOCK;                   // Lock Register for all the config registers.
    union   TSNSCTL_REG                      TSNSCTL;                      // Temperature Sensor Control Register
    Uint16                                   rsvd5[7];                     // Reserved
    union   ANAREFPCTL_REG                   ANAREFPCTL;                   // Analog Reference Control Register for VREFHI
    union   ANAREFNCTL_REG                   ANAREFNCTL;                   // Analog Reference Control Register for VREFLO
    Uint16                                   rsvd6[6];                     // Reserved
    union   VMONCTL_REG                      VMONCTL;                      // Voltage Monitor Control Register
    Uint16                                   rsvd7[17];                    // Reserved
    union   CMPHPMXSEL_REG                   CMPHPMXSEL;                   // Bits to select one of the many sources on CompHP inputs. Refer to Pimux diagram for details.
    union   CMPLPMXSEL_REG                   CMPLPMXSEL;                   // Bits to select one of the many sources on CompLP inputs. Refer to Pimux diagram for details.
    union   CMPHNMXSEL_REG                   CMPHNMXSEL;                   // Bits to select one of the many sources on CompHN inputs. Refer to Pimux diagram for details.
    union   CMPLNMXSEL_REG                   CMPLNMXSEL;                   // Bits to select one of the many sources on CompLN inputs. Refer to Pimux diagram for details.
    union   ADCDACLOOPBACK_REG               ADCDACLOOPBACK;               // Enabble loopback from DAC to ADCs
    Uint16                                   rsvd8;                        // Reserved
    union   CMPSSCTL_REG                     CMPSSCTL;                     // CMPSS Control Register
    union   CMPSSDACBUFCONFIG_REG            CMPSSDACBUFCONFIG;            // Config bits for CMPSS DAC buffer
    union   LOCK_REG                         LOCK;                         // Lock Register
    Uint16                                   rsvd9[122];                   // Reserved
    union   AGPIOCTRLA_REG                   AGPIOCTRLA;                   // AGPIO Control Register
    union   AGPIOCTRLB_REG                   AGPIOCTRLB;                   // AGPIO Control Register
    Uint16                                   rsvd10[8];                    // Reserved
    union   AGPIOCTRLG_REG                   AGPIOCTRLG;                   // AGPIO Control Register
    union   AGPIOCTRLH_REG                   AGPIOCTRLH;                   // AGPIO Control Register
    Uint16                                   rsvd11[24];                   // Reserved
    union   GPIOINENACTRL_REG                GPIOINENACTRL;                // GPIOINENACTRL Control Register
    union   IO_DRVSEL_REG                    IO_DRVSEL;                    // IO Drive strength select register
    union   IO_MODESEL_REG                   IO_MODESEL;                   // IO Mode select register
    union   ADCSOCFRCGB_REG                  ADCSOCFRCGB;                  // ADC Global SOC Force
    union   ADCSOCFRCGBSEL_REG               ADCSOCFRCGBSEL;               // ADC Global SOC Force Select
};

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
