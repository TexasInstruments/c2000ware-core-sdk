//###########################################################################
//
// FILE:   F2805x_Analogsubsys.h
//
// TITLE:  F2805x Device ANALOGSUBSYS Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_ANALOGSUBSYS_H
#define F2805x_ANALOGSUBSYS_H

#ifdef __cplusplus
extern "C" {
#endif


//
// ANALOGSUBSYS Individual Register Bit Definitions:
//
struct DACCTL_BITS {                                   // bits description
    Uint16  DACVAL:6;                                  // 5:0 DAC Output
    Uint16  rsvd1:10;                                  // 15:6 Reserved
};

union DACCTL_REG {
    Uint16  all;
    struct  DACCTL_BITS  bit;
};

struct VREFOUTCTL_BITS {                               // bits description
    Uint16  DACVAL:6;                                  // 5:0 DAC Output
    Uint16  rsvd1:10;                                  // 15:6 Reserved
};

union VREFOUTCTL_REG {
    Uint16  all;
    struct  VREFOUTCTL_BITS  bit;
};

struct DACEN_BITS {                                    // bits description
    Uint16  DAC1EN:1;                                  // 0 DAC 1 Enable
    Uint16  DAC2EN:1;                                  // 1 DAC 2 Enable
    Uint16  DAC3EN:1;                                  // 2 DAC 3 Enable
    Uint16  DAC4EN:1;                                  // 3 DAC 4 Enable
    Uint16  DAC5EN:1;                                  // 4 DAC 5 Enable
    Uint16  rsvd1:11;                                  // 15:5 Reserved
};

union DACEN_REG {
    Uint16  all;
    struct  DACEN_BITS  bit;
};

struct VREFOUTEN_BITS {                   // bits description
    Uint16  DACVREFOUTEN:1;               // 0 DACVREFOUT (DAC6) Output Enable
    Uint16  rsvd1:15;                     // 15:1 Reserved
};

union VREFOUTEN_REG {
    Uint16  all;
    struct  VREFOUTEN_BITS  bit;
};

struct PGAEN_BITS {                    // bits description
    Uint16  AMPA1EN:1;                 // 0 Motor 1- Amp2 (on ADC A1) Enable
    Uint16  AMPA3EN:1;                 // 1 Motor 1- Amp3 (on ADC A3) Enable
    Uint16  AMPB1EN:1;                 // 2 Motor 1- Amp4 (on ADC B1) Enable
    Uint16  AMPA6EN:1;                 // 3 Motor 2- Amp5 (on ADC A6) Enable
    Uint16  AMPB4EN:1;                 // 4 Motor 2- Amp6 (on ADC B4) Enable
    Uint16  AMPB6EN:1;                 // 5 Motor 2- Amp7 (on ADC B6) Enable
    Uint16  AMPB7EN:1;                 // 6 PFC- Amp1 (on ADC B7) Enable
    Uint16  rsvd1:9;                   // 15:7 Reserved
};

union PGAEN_REG {
    Uint16  all;
    struct  PGAEN_BITS  bit;
};

struct COMPEN_BITS {                        // bits description
    Uint16  COMPB7EN:1;                     // 0 Comparator COMPB7 Enable
    Uint16  rsvd1:1;                        // 1 Reserved
    Uint16  COMPA1EN:1;                     // 2 "Comparator COMPA1H,L Enable"
    Uint16  rsvd2:1;                        // 3 Reserved
    Uint16  COMPA3EN:1;                     // 4 "Comparator COMPA3H,L Enable"
    Uint16  rsvd3:1;                        // 5 Reserved
    Uint16  COMPB1EN:1;                     // 6 "Comparator COMPB1H,L Enable"
    Uint16  rsvd4:1;                        // 7 Reserved
    Uint16  COMPA6EN:1;                     // 8 "Comparator COMPA6H,L Enable"
    Uint16  rsvd5:1;                        // 9 Reserved
    Uint16  COMPB4EN:1;                     // 10 "Comparator COMPB4H,L Enable"
    Uint16  rsvd6:1;                        // 11 Reserved
    Uint16  COMPB6EN:1;                     // 12 "Comparator COMPB6H,L Enable"
    Uint16  rsvd7:3;                        // 15:13 Reserved
};

union COMPEN_REG {
    Uint16  all;
    struct  COMPEN_BITS  bit;
};

struct AMPM1_GAIN_BITS {                               // bits description
    Uint16  AMPA1GAIN:2;                               // 1:0 AMP A1 Gain
    Uint16  rsvd1:2;                                   // 3:2 Reserved
    Uint16  AMPA3GAIN:2;                               // 5:4 AMP A3 Gain
    Uint16  rsvd2:2;                                   // 7:6 Reserved
    Uint16  AMPB1GAIN:2;                               // 9:8 AMP B1 Gain
    Uint16  rsvd3:6;                                   // 15:10 Reserved
};

union AMPM1_GAIN_REG {
    Uint16  all;
    struct  AMPM1_GAIN_BITS  bit;
};

struct AMPM2_GAIN_BITS {                               // bits description
    Uint16  AMPA6GAIN:2;                               // 1:0 AMP A6 Gain
    Uint16  rsvd1:2;                                   // 3:2 Reserved
    Uint16  AMPB4GAIN:2;                               // 5:4 AMP B4 Gain
    Uint16  rsvd2:2;                                   // 7:6 Reserved
    Uint16  AMPB6GAIN:2;                               // 9:8 AMP B6 Gain
    Uint16  rsvd3:6;                                   // 15:10 Reserved
};

union AMPM2_GAIN_REG {
    Uint16  all;
    struct  AMPM2_GAIN_BITS  bit;
};

struct AMPPFC_GAIN_BITS {                              // bits description
    Uint16  AMPB7GAIN:2;                               // 1:0 AMP B0 Gain
    Uint16  rsvd1:14;                                  // 15:2 Reserved
};

union AMPPFC_GAIN_REG {
    Uint16  all;
    struct  AMPPFC_GAIN_BITS  bit;
};

struct ADCINSWITCH_BITS {                              // bits description
    Uint16  ADCINA1SEL:1;                              // 0 ADC A1 input select
    Uint16  ADCINB1SEL:1;                              // 1 ADC B1 input select
    Uint16  ADCINA6SEL:1;                              // 2 ADC A6 input select
    Uint16  ADCINB6SEL:1;                              // 3 ADC B6 input select
    Uint16  rsvd1:12;                                  // 15:4 Reserved
};

union ADCINSWITCH_REG {
    Uint16  all;
    struct  ADCINSWITCH_BITS  bit;
};

struct COMPHYSTCTL_BITS {          //bits description
    Uint16  COMPA1_HYST_DISABLE:1; //0 Comparator-A1 High/Low hysteresis en/dis
    Uint16  COMPA3_HYST_DISABLE:1; //1 Comparator-A3 High/Low hysteresis en/dis
    Uint16  COMPA6_HYST_DISABLE:1; //2 Comparator-A6 High/Low hysteresis en/dis
    Uint16  COMPB1_HYST_DISABLE:1; //3 Comparator-B1 High/Low hysteresis en/dis
    Uint16  COMPB4_HYST_DISABLE:1; //4 Comparator-B4 High/Low hysteresis en/dis
    Uint16  COMPB6_HYST_DISABLE:1; //5 Comparator-B6 High/Low hysteresis en/dis
    Uint16  COMPB7_HYST_DISABLE:1; //6 Comparator-B7 High/Low hysteresis en/dis
    Uint16  rsvd1:9;               //15:7 Reserved
};

union COMPHYSTCTL_REG {
    Uint16  all;
    struct  COMPHYSTCTL_BITS  bit;
};

struct CTRIPICTL_BITS {                     // bits description
    Uint16  COMPHPOL:1;                     // 0 COMPH Polarity Control
    Uint16  COMPLPOL:1;                     // 1 COMPL Polarity Control
    Uint16  COMPHINPEN:1;                   // 2 COMPH Input Enable for CTRIPn
    Uint16  COMPLINPEN:1;                   // 3 COMPL Input Enable for CTRIPn
    Uint16  rsvd1:7;                        // 10:4 Reserved
    Uint16  CTRIPBYP:1;                     // 11 CTRIPn Filter Bypass
    Uint16  CTRIPOUTBYP:1;                  // 12 CTRIPnOUT Filter Bypass
    Uint16  rsvd2:3;                        // 15:13 Reserved
};

union CTRIPICTL_REG {
    Uint16  all;
    struct  CTRIPICTL_BITS  bit;
};

struct CTRIPB7ICTL_BITS {                   // bits description
    Uint16  COMPPOL:1;                      // 0 COMP Polarity Control
    Uint16  rsvd1:1;                        // 1 Reserved
    Uint16  COMPINPEN:1;                    // 2 COMP Input Enable for CTRIPn
    Uint16  rsvd2:1;                        // 3 Reserved
    Uint16  rsvd3:7;                        // 10:4 Reserved
    Uint16  CTRIPBYP:1;                     // 11 CTRIPn Filter Bypass
    Uint16  CTRIPOUTBYP:1;                  // 12 CTRIPnOUT Filter Bypass
    Uint16  rsvd4:3;                        // 15:13 Reserved
};

union CTRIPB7ICTL_REG {
    Uint16  all;
    struct  CTRIPB7ICTL_BITS  bit;
};

struct CTRIPFILCTL_BITS {        // bits description
    Uint16  rsvd1:4;             // 3:0 Reserved
    Uint16  SAMPWIN:5;  // 8:4 Sample Window Size for Digital Filter on CTRIPn
    Uint16  THRESH:5;   // 13:9 Majority Voting Threshold
    Uint16  rsvd2:1;    // 14 Reserved
    Uint16  FILINIT:1;  // 15 CTRIPn Filter Initialization
};

union CTRIPFILCTL_REG {
    Uint16  all;
    struct  CTRIPFILCTL_BITS  bit;
};

struct CTRIPFILCLKCTL_BITS {     // bits description
    Uint16  CLKPRESCALE:8;       // 7:0 Sample Clock Prescale value for CTRIPn
    Uint16  rsvd1:8;             // 15:8 Reserved
};

union CTRIPFILCLKCTL_REG {
    Uint16  all;
    struct  CTRIPFILCLKCTL_BITS  bit;
};

struct CTRIPM1OCTL_BITS {        // bits description
    Uint16  CTRIPA1EN:1;         // 0 CTRIPA1 Input Enable for CTRIPM1
    Uint16  CTRIPA3EN:1;         // 1 CTRIPA3 Input Enable for CTRIPM1
    Uint16  CTRIPB1EN:1;         // 2 CTRIPB1 Input Enable for CTRIPM1
    Uint16  rsvd1:5;             // 7:3 Reserved
    Uint16  CTRIPA1OUTEN:1;      // 8 CTRIPA1 Input Enable for CTRIPOUTM1
    Uint16  CTRIPA3OUTEN:1;      // 9 CTRIPA3 Input Enable for CTRIPOUTM1
    Uint16  CTRIPB1OUTEN:1;      // 10 CTRIPB1 Input Enable for CTRIPOUTM1
    Uint16  rsvd2:3;             // 13:11 Reserved
    Uint16  CTRIPOUTPOL:1;       // 14 CTRIPM1OUT Polarity
    Uint16  CTRIPOUTLATEN:1;     // 15 CTRIPM1OUT latch enable
};

union CTRIPM1OCTL_REG {
    Uint16  all;
    struct  CTRIPM1OCTL_BITS  bit;
};

struct CTRIPM1STS_BITS {         // bits description
    Uint16  CTRIPA1STS:1;        // 0 CTRIPA1 Output Status
    Uint16  CTRIPA3STS:1;        // 1 CTRIPA3 Output Status
    Uint16  CTRIPB1STS:1;        // 2 CTRIPB1 Output Status
    Uint16  rsvd1:4;             // 6:3 Reserved
    Uint16  CTRIPOUTM1STS:1;     // 7 CTRIPOUTM1 Output Status
    Uint16  CTRIPA1FLG:1;        // 8 CTRIPA1 Latched Output Flag for CTRIPM1
    Uint16  CTRIPA3FLG:1;        // 9 CTRIPA3 Latched Output Flag for CTRIPM1
    Uint16  CTRIPB1FLG:1;        // 10 CTRIPB1 Latched Output Flag for CTRIPM1
    Uint16  rsvd2:4;             // 14:11 Reserved
    Uint16  CTRIPOUTM1FLG:1;     // 15 CTRIPOUTM1 Latched Output Flag
};

union CTRIPM1STS_REG {
    Uint16  all;
    struct  CTRIPM1STS_BITS  bit;
};

struct CTRIPM1FLGCLR_BITS {      // bits description
    Uint16  rsvd1:8;             // 7:0 Reserved
    Uint16  CTRIPA1FLGCLR:1;     // 8 CTRIPA1 Output Flag Clear for CTRIPM1
    Uint16  CTRIPA3FLGCLR:1;     // 9 CTRIPA3 Output Flag Clear for CTRIPM1
    Uint16  CTRIPB1FLGCLR:1;     // 10 CTRIPB1 Output Flag Clear for CTRIPM1
    Uint16  rsvd2:4;             // 14:11 Reserved
    Uint16  CTRIPOUTM1FLGCLR:1;  // 15 CTRIPOUTM1FLG Flag Clear
};

union CTRIPM1FLGCLR_REG {
    Uint16  all;
    struct  CTRIPM1FLGCLR_BITS  bit;
};

struct CTRIPM2OCTL_BITS {        // bits description
    Uint16  CTRIPA6EN:1;         // 0 CTRIPA6 Input Enable for CTRIPM2
    Uint16  CTRIPB4EN:1;         // 1 CTRIPB4 Input Enable for CTRIPM2
    Uint16  CTRIPB6EN:1;         // 2 CTRIPB6 Input Enable for CTRIPM2
    Uint16  rsvd1:5;             // 7:3 Reserved
    Uint16  CTRIPA6OUTEN:1;      // 8 CTRIPA6 Input Enable for CTRIPOUTM2
    Uint16  CTRIPB4OUTEN:1;      // 9 CTRIPB4 Input Enable for CTRIPOUTM2
    Uint16  CTRIPB6OUTEN:1;      // 10 CTRIPB6 Input Enable for CTRIPOUTM2
    Uint16  rsvd2:3;             // 13:11 Reserved
    Uint16  CTRIPOUTPOL:1;       // 14 CTRIPM2OUT Polarity
    Uint16  CTRIPOUTLATEN:1;     // 15 CTRIPM2OUT latch enable
};

union CTRIPM2OCTL_REG {
    Uint16  all;
    struct  CTRIPM2OCTL_BITS  bit;
};

struct CTRIPM2STS_BITS {         // bits description
    Uint16  CTRIPA6STS:1;        // 0 CTRIPA6 Output Status
    Uint16  CTRIPB4STS:1;        // 1 CTRIPB4 Output Status
    Uint16  CTRIPB6STS:1;        // 2 CTRIPB6 Output Status
    Uint16  rsvd1:4;             // 6:3 Reserved
    Uint16  CTRIPOUTM2STS:1;     // 7 CTRIPOUTM2 Output Status
    Uint16  CTRIPA6FLG:1;        // 8 CTRIPA6 Latched Output Flag for CTRIPM2
    Uint16  CTRIPB4FLG:1;        // 9 CTRIPB4 Latched Output Flag for CTRIPM2
    Uint16  CTRIPB6FLG:1;        // 10 CTRIPB6 Latched Output Flag for CTRIPM2
    Uint16  rsvd2:4;             // 14:11 Reserved
    Uint16  CTRIPOUTM2FLG:1;     // 15 CTRIPOUTM2FLG Flag
};

union CTRIPM2STS_REG {
    Uint16  all;
    struct  CTRIPM2STS_BITS  bit;
};

struct CTRIPM2FLGCLR_BITS {      // bits description
    Uint16  rsvd1:8;             // 7:0 Reserved
    Uint16  CTRIPA6FLGCLR:1;     // 8 CTRIPA6 Output Flag Clear for CTRIPM2
    Uint16  CTRIPB4FLGCLR:1;     // 9 CTRIPB4 Output Flag Clear for CTRIPM2
    Uint16  CTRIPB6FLGCLR:1;     // 10 CTRIPB6 Output Flag Clear for CTRIPM2
    Uint16  rsvd2:4;             // 14:11 Reserved
    Uint16  CTRIPOUTM2FLGCLR:1;  // 15 CTRIPOUTM2FLG Flag Clear
};

union CTRIPM2FLGCLR_REG {
    Uint16  all;
    struct  CTRIPM2FLGCLR_BITS  bit;
};

struct CTRIPPFCOCTL_BITS {            // bits description
    Uint16  CTRIPB7EN:1;              // 0 CTRIPB7 Input Enable for CTRIPPFC
    Uint16  rsvd1:7;                  // 7:1 Reserved
    Uint16  CTRIPB7OUTEN:1;           // 8 CTRIPB7 Input Enable for CTRIPOUTPFC
    Uint16  rsvd2:5;                  // 13:9 Reserved
    Uint16  CTRIPOUTPOL:1;            // 14 CTRIPPFCOUT Polarity
    Uint16  CTRIPOUTLATEN:1;          // 15 CTRIPPFCOUT latch enable
};

union CTRIPPFCOCTL_REG {
    Uint16  all;
    struct  CTRIPPFCOCTL_BITS  bit;
};

struct CTRIPPFCSTS_BITS {         // bits description
    Uint16  CTRIPB7STS:1;         // 0 CTRIPB7 Output Status
    Uint16  rsvd1:6;              // 6:1 Reserved
    Uint16  CTRIPOUTPFCSTS:1;     // 7 CTRIPOUTPFC Output Status
    Uint16  CTRIPB7FLG:1;         // 8 CTRIPB7 Latched Output Flag for CTRIPPFC
    Uint16  rsvd2:6;              // 14:9 Reserved
    Uint16  CTRIPOUTPFCFLG:1;     // 15 CTRIPOUTPFCFLG Output Flag
};

union CTRIPPFCSTS_REG {
    Uint16  all;
    struct  CTRIPPFCSTS_BITS  bit;
};

struct CTRIPPFCFLGCLR_BITS {        // bits description
    Uint16  rsvd1:8;                // 7:0 Reserved
    Uint16  CTRIPB7FLGCLR:1;        // 8 CTRIPB7 Output Flag Clear for CTRIPPFC
    Uint16  rsvd2:6;                // 14:9 Reserved
    Uint16  CTRIPOUTPFCFLGCLR:1;    // 15 CTRIPOUTPFCFLG Output Flag Clear
};

union CTRIPPFCFLGCLR_REG {
    Uint16  all;
    struct  CTRIPPFCFLGCLR_BITS  bit;
};

struct LOCKCTRIP_BITS {      // bits description
    Uint16  CTRIPM1LOCK:1;   // 0 CTRIPM1 Configuration and Filter Control Lock
    Uint16  CTRIPM2LOCK:1;   // 1 CTRIPM2 Configuration and Filter Control Lock
    Uint16  CTRIPPFCLOCK:1;  // 2 CTRIPPFC Configuration & Filter Control Lock
    Uint16  rsvd1:13;        // 15:3 Reserved
};

union LOCKCTRIP_REG {
    Uint16  all;
    struct  LOCKCTRIP_BITS  bit;
};

struct LOCKDAC_BITS {                        // bits description
    Uint16  DAC1LOCK:1;                      // 0 DAC1CTL Register Lock
    Uint16  DAC2LOCK:1;                      // 1 DAC2CTL Register Lock
    Uint16  DAC3LOCK:1;                      // 2 DAC3CTL Register Lock
    Uint16  DAC4LOCK:1;                      // 3 DAC4CTL Register Lock
    Uint16  DAC5LOCK:1;                      // 4 DAC5CTL Register Lock
    Uint16  DACENLOCK:1;                     // 5 DACEN Register lock
    Uint16  DACVREFLOCK:1;                   // 6 VREFOUTCTL Register Lock
    Uint16  VREFOUTENLOCK:1;                 // 7 VREFOUTEN Register Lock
    Uint16  rsvd1:8;                         // 15:8 Reserved
};

union LOCKDAC_REG {
    Uint16  all;
    struct  LOCKDAC_BITS  bit;
};

struct LOCKAMPCOMP_BITS {        // bits description
    Uint16  PGAENLOCK:1;         // 0 PGAEN Register Lock
    Uint16  COMPENLOCK:1;        // 1 COMPEN Register Lock
    Uint16  AMP_M1_LOCK:1;       // 2 "AMP's A1, A3, B1 Gain Control Lock"
    Uint16  AMP_M2_LOCK:1;       // 3 "AMP's A6, B4, B6 Gain Control Lock"
    Uint16  AMP_PFC_LOCK:1;      // 4 PFC AMP Gain Control Lock
    Uint16  rsvd1:11;            // 15:5 Reserved
};

union LOCKAMPCOMP_REG {
    Uint16  all;
    struct  LOCKAMPCOMP_BITS  bit;
};

struct LOCKSWITCH_BITS {         // bits description
    Uint16  AMPOUTSWLOCK:1;      // 0 AMP Output Switch Control Lock
    Uint16  ADCINSWLOCK:1;       // 1 ADCINSWITCH Register Lock
    Uint16  COMPHYSLOCK:1;       // 2 COMPHYS Register Lock
    Uint16  rsvd1:1;             // 3 Reserved
    Uint16  rsvd2:12;            // 15:4 Reserved
};

union LOCKSWITCH_REG {
    Uint16  all;
    struct  LOCKSWITCH_BITS  bit;
};

struct ANALOG_SUBSYS_REGS {
    union DACCTL_REG         DAC1CTL;          //DAC1 control
    union DACCTL_REG         DAC2CTL;          //DAC2 control
    union DACCTL_REG         DAC3CTL;          //DAC3 control
    union DACCTL_REG         DAC4CTL;          //DAC4 control
    union DACCTL_REG         DAC5CTL;          //DAC5 control
    union VREFOUTCTL_REG     VREFOUTCTL;       //VREFOUT (DAC6) control
    Uint16                   rsvd1[10];        //Reserved
    union DACEN_REG          DACEN;            //DAC Enables
    union VREFOUTEN_REG      VREFOUTEN;        //VREFOUT Enable
    union PGAEN_REG          PGAEN;            //Programmable Gain Amp Enable
    union COMPEN_REG         COMPEN;           //Comparator Enable
    union AMPM1_GAIN_REG     AMPM1_GAIN;       //Motor Unit 1 PGA Gain control
    union AMPM2_GAIN_REG     AMPM2_GAIN;       //Motor Unit 2 PGA Gain control
    union AMPPFC_GAIN_REG    AMPPFC_GAIN;      //PFC PGA Gain controls
    Uint16                   rsvd2[9];         //Reserved
    Uint16                   rsvd3;            //Reserved
    union ADCINSWITCH_REG    ADCINSWITCH;      //ADC input-select switch ctrl
    Uint16                   rsvd4[2];         //Reserved
    Uint16                   rsvd5;            //Reserved
    Uint16                   rsvd6;            //Reserved
    Uint16                   rsvd7;            //Reserved
    Uint16                   rsvd8;            //Reserved
    Uint16                   rsvd9;            //Reserved
    union COMPHYSTCTL_REG    COMPHYSTCTL;      //Comp. Hi/Lo hysteresis en/dis
    Uint16                   rsvd10[6];        //Reserved
    union CTRIPICTL_REG      CTRIPA1ICTL;      //CTRIPA1 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPA1FILCTL;    //CTRIPA1 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPA1FILCLKCTL; //CTRIPA1 Filter Sample Clk Ctrl
    Uint16                   rsvd11;           //Reserved
    union CTRIPICTL_REG      CTRIPA3ICTL;      //CTRIPA3 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPA3FILCTL;    //CTRIPA3 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPA3FILCLKCTL; //CTRIPA3 Filter Sample Clk Ctrl
    Uint16                   rsvd12;           //Reserved
    union CTRIPICTL_REG      CTRIPB1ICTL;      //CTRIPB1 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPB1FILCTL;    //CTRIPB1 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPB1FILCLKCTL; //CTRIPB1 Filter Sample Clk Ctrl
    Uint16                   rsvd13;           //Reserved
    Uint16                   rsvd14;           //Reserved
    union CTRIPM1OCTL_REG    CTRIPM1OCTL;      //CTRIPM1 CTRIP Filter Out Ctrl
    union CTRIPM1STS_REG     CTRIPM1STS;       //CTRIPM1 CTRIPx outputs status
    union CTRIPM1FLGCLR_REG  CTRIPM1FLGCLR;    //CTRIPM1 CTRIPx flag clear
    Uint16                   rsvd15[16];       //Reserved
    union CTRIPICTL_REG      CTRIPA6ICTL;      //CTRIPA6 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPA6FILCTL;    //CTRIPA6 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPA6FILCLKCTL; //CTRIPA6 Filter Sample Clk Ctrl
    Uint16                   rsvd16;           //Reserved
    union CTRIPICTL_REG      CTRIPB4ICTL;      //CTRIPB4 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPB4FILCTL;    //CTRIPB4 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPB4FILCLKCTL; //CTRIPB4 Filter Sample Clk Ctrl
    Uint16                   rsvd17;           //Reserved
    union CTRIPICTL_REG      CTRIPB6ICTL;      //CTRIPB6 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPB6FILCTL;    //CTRIPB6 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPB6FILCLKCTL; //CTRIPB6 Filter Sample Clk Ctrl
    Uint16                   rsvd18;           //Reserved
    Uint16                   rsvd19;           //Reserved
    union CTRIPM2OCTL_REG    CTRIPM2OCTL;      //CTRIPM2 CTRIP Filter Out Ctrl
    union CTRIPM2STS_REG     CTRIPM2STS;       //CTRIPM2 CTRIPx outputs status
    union CTRIPM2FLGCLR_REG  CTRIPM2FLGCLR;    //CTRIPM2 CTRIPx flag clear
    Uint16                   rsvd20[16];       //Reserved
    union CTRIPB7ICTL_REG    CTRIPB7ICTL;      //CTRIPB7 Filter Input/Fxn Ctrl
    union CTRIPFILCTL_REG    CTRIPB7FILCTL;    //CTRIPB7 Filter parameters
    union CTRIPFILCLKCTL_REG CTRIPB7FILCLKCTL; //CTRIPB7 Filter Sample Clk Ctrl
    Uint16                   rsvd21[9];        //Reserved
    Uint16                   rsvd22;           //Reserved
    union CTRIPPFCOCTL_REG   CTRIPPFCOCTL;     //CTRIPPFC CTRIPx outputs status
    union CTRIPPFCSTS_REG    CTRIPPFCSTS;      //CTRIPPFC CTRIPx flag clear
    union CTRIPPFCFLGCLR_REG CTRIPPFCFLGCLR;   //CTRIPPFC COMP Test Control
    Uint16                   rsvd23[112];      //Reserved
    union LOCKCTRIP_REG      LOCKCTRIP;        //Lock Register for CTRIP Filter
    Uint16                   rsvd24;           //Reserved
    union LOCKDAC_REG        LOCKDAC;          //Lock Register for DACs
    Uint16                   rsvd25;           //Reserved
    union LOCKAMPCOMP_REG    LOCKAMPCOMP;      //Lock Register for Amp/Comp
    Uint16                   rsvd26;           //Reserved
    union LOCKSWITCH_REG     LOCKSWITCH;       //Lock Register for Switches
    Uint16                   rsvd27[9];        //Reserved
};

//
// Analogsubsys External References & Function Declarations:
//
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

#ifdef __cplusplus
}
#endif                    /* extern "C" */


#endif                    // end of F2805x_ANALOGSUBSYS_H definition
//
// End of file
//
