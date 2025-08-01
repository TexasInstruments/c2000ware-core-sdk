//###########################################################################
//
// FILE:    f28e12x_mcpwm.h
//
// TITLE:   Definitions for the MCPWM registers.
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

#ifndef F28E12X_MCPWM_H
#define F28E12X_MCPWM_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MCPWM Individual Register Bit Definitions:

struct REVISION_BITS {                  // bits description
    Uint16 PWM2_PRESENT:1;              // 0 PWM2 Present
    Uint16 PWM3_PRESENT:1;              // 1 PWM3 Present
    Uint16 CMPCD_PRESENT:1;             // 2 Compare C and D Present
    Uint16 CAP_PRESENT:1;               // 3 Capture mode Present
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union REVISION_REG {
    Uint32  all;
    struct  REVISION_BITS  bit;
};

struct TBCTL_BITS {                     // bits description
    Uint16 CTRMODE:2;                   // 1:0 Counter Mode
    Uint16 CLKDIV:4;                    // 5:2 Time Base Clock Pre-scaler
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 PRDLD:1;                     // 8 Shadow to active load of TBPRD
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 PHSEN:1;                     // 10 Phase Load Enable
    Uint16 PHSDIR:1;                    // 11 Phase Direction Bit
    Uint16 rsvd3:3;                     // 14:12 Reserved
    Uint16 SWSYNC:1;                    // 15 Software Force Sync Pulse
    Uint16 SYNCOSEL:3;                  // 18:16 Sync Output Select
    Uint16 rsvd4:1;                     // 19 Reserved
    Uint16 FREE_SOFT:2;                 // 21:20 Emulation Mode Bits
    Uint16 SYNCPERSEL:3;                // 24:22 Sync peripheral Select
    Uint16 SYNCISEL:5;                  // 29:25 Sync Input Select
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union TBCTL_REG {
    Uint32  all;
    struct  TBCTL_BITS  bit;
};

struct TBPRD_BITS {                     // bits description
    Uint16 TBPRD:16;                    // 15:0 Time base period register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union TBPRD_REG {
    Uint32  all;
    struct  TBPRD_BITS  bit;
};

struct TBPRDS_BITS {                    // bits description
    Uint16 TBPRDS:16;                   // 15:0 Time base period shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union TBPRDS_REG {
    Uint32  all;
    struct  TBPRDS_BITS  bit;
};

struct TBPHS_BITS {                     // bits description
    Uint16 TBPHS:16;                    // 15:0 Phase Offset Register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union TBPHS_REG {
    Uint32  all;
    struct  TBPHS_BITS  bit;
};

struct TBSTS_BITS {                     // bits description
    Uint16 CTRDIR:1;                    // 0 Counter Direction Status
    Uint16 SYNCI:1;                     // 1 External Input Sync Status
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union TBSTS_REG {
    Uint32  all;
    struct  TBSTS_BITS  bit;
};

struct TBSTSCLR_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 SYNCI:1;                     // 1 External Input Sync Status clear
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union TBSTSCLR_REG {
    Uint32  all;
    struct  TBSTSCLR_BITS  bit;
};

struct TBCTR_BITS {                     // bits description
    Uint16 TBCTR:16;                    // 15:0 Counter Value
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union TBCTR_REG {
    Uint32  all;
    struct  TBCTR_BITS  bit;
};

struct CMPCTL_BITS {                    // bits description
    Uint16 PWM1_LOADAMODE:2;            // 1:0 Shadow to active load of PWM1_CMPA
    Uint16 PWM1_LOADBMODE:2;            // 3:2 Shadow to active load of PWM1_CMPB
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 PWM2_LOADAMODE:2;            // 9:8 Shadow to active load of PWM2_CMPA
    Uint16 PWM2_LOADBMODE:2;            // 11:10 Shadow to active load of PWM2_CMPB
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 PWM3_LOADAMODE:2;            // 17:16 Shadow to active load of PWM3_CMPA
    Uint16 PWM3_LOADBMODE:2;            // 19:18 Shadow to active load of PWM3_CMPB
    Uint16 rsvd3:4;                     // 23:20 Reserved
    Uint16 LOADCMODE:2;                 // 25:24 Shadow to active load of CMPC
    Uint16 LOADDMODE:2;                 // 27:26 Shadow to active load of CMPD
    Uint16 rsvd4:4;                     // 31:28 Reserved
};

union CMPCTL_REG {
    Uint32  all;
    struct  CMPCTL_BITS  bit;
};

struct CMPC_BITS {                      // bits description
    Uint16 CMPC:16;                     // 15:0 Compare C register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CMPC_REG {
    Uint32  all;
    struct  CMPC_BITS  bit;
};

struct CMPD_BITS {                      // bits description
    Uint16 CMPD:16;                     // 15:0 Compare D register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CMPD_REG {
    Uint32  all;
    struct  CMPD_BITS  bit;
};

struct CMPCS_BITS {                     // bits description
    Uint16 CMPCS:16;                    // 15:0 Compare C shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CMPCS_REG {
    Uint32  all;
    struct  CMPCS_BITS  bit;
};

struct CMPDS_BITS {                     // bits description
    Uint16 CMPDS:16;                    // 15:0 Compare D shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CMPDS_REG {
    Uint32  all;
    struct  CMPDS_BITS  bit;
};

struct AQCTL_BITS {                     // bits description
    Uint16 PWM1_LDAQAMODE:2;            // 1:0 Shadow to active load of PWM1_AQCTLA
    Uint16 PWM1_LDAQBMODE:2;            // 3:2 Shadow to active load of PWM1_AQCTLB
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 PWM2_LDAQAMODE:2;            // 9:8 Shadow to active load of PWM2_AQCTLA
    Uint16 PWM2_LDAQBMODE:2;            // 11:10 Shadow to active load of PWM2_AQCTLB
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 PWM3_LDAQAMODE:2;            // 17:16 Shadow to active load of PWM3_AQCTLA
    Uint16 PWM3_LDAQBMODE:2;            // 19:18 Shadow to active load of PWM3_AQCTLB
    Uint16 rsvd3:12;                    // 31:20 Reserved
};

union AQCTL_REG {
    Uint32  all;
    struct  AQCTL_BITS  bit;
};

struct SOCEN_BITS {                     // bits description
    Uint16 SOCA_ENABLE:1;               // 0 Start of conversion (SOC) A enable
    Uint16 SOCB_ENABLE:1;               // 1 Start of conversion (SOC) B enable
    Uint16 SOCC_ENABLE:1;               // 2 Start of conversion (SOC) C enable
    Uint16 SOCD_ENABLE:1;               // 3 Start of conversion (SOC) D enable
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOCEN_REG {
    Uint32  all;
    struct  SOCEN_BITS  bit;
};

struct SOCSEL_BITS {                    // bits description
    Uint16 SOCA_SEL:5;                  // 4:0 Start of conversion (SOC) A select
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 SOCB_SEL:5;                  // 12:8 Start of conversion (SOC) B select
    Uint16 rsvd2:3;                     // 15:13 Reserved
    Uint16 SOCC_SEL:5;                  // 20:16 Start of conversion (SOC) C select
    Uint16 rsvd3:3;                     // 23:21 Reserved
    Uint16 SOCD_SEL:5;                  // 28:24 Start of conversion (SOC) D select
    Uint16 rsvd4:3;                     // 31:29 Reserved
};

union SOCSEL_REG {
    Uint32  all;
    struct  SOCSEL_BITS  bit;
};

struct SOCPERIOD_BITS {                 // bits description
    Uint16 SOCA_PERIOD:3;               // 2:0 Start of conversion (SOC) A PERIOD
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 SOCB_PERIOD:3;               // 10:8 Start of conversion (SOC) B PERIOD
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 SOCC_PERIOD:3;               // 18:16 Start of conversion (SOC) C PERIOD
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 SOCD_PERIOD:3;               // 26:24 Start of conversion (SOC) D PERIOD
    Uint16 rsvd4:5;                     // 31:27 Reserved
};

union SOCPERIOD_REG {
    Uint32  all;
    struct  SOCPERIOD_BITS  bit;
};

struct SOCCNT_BITS {                    // bits description
    Uint16 SOCA_CNT:3;                  // 2:0 Start of conversion (SOC) A COUNT
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 SOCB_CNT:3;                  // 10:8 Start of conversion (SOC) B COUNT
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 SOCC_CNT:3;                  // 18:16 Start of conversion (SOC) C COUNT
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 SOCD_CNT:3;                  // 26:24 Start of conversion (SOC) D COUNT
    Uint16 rsvd4:5;                     // 31:27 Reserved
};

union SOCCNT_REG {
    Uint32  all;
    struct  SOCCNT_BITS  bit;
};

struct SOCFLAG_BITS {                   // bits description
    Uint16 SOCA:1;                      // 0 SOCA Flag
    Uint16 SOCB:1;                      // 1 SOCB Flag
    Uint16 SOCC:1;                      // 2 SOCC Flag
    Uint16 SOCD:1;                      // 3 SOCD Flag
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOCFLAG_REG {
    Uint32  all;
    struct  SOCFLAG_BITS  bit;
};

struct SOCCLR_BITS {                    // bits description
    Uint16 SOCA:1;                      // 0 SOCA Clear
    Uint16 SOCB:1;                      // 1 SOCB Clear
    Uint16 SOCC:1;                      // 2 SOCC Clear
    Uint16 SOCD:1;                      // 3 SOCD Clear
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOCCLR_REG {
    Uint32  all;
    struct  SOCCLR_BITS  bit;
};

struct ETSEL_BITS {                     // bits description
    Uint16 ET1_SEL:5;                   // 4:0 Event trigger1 selection
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 ET2_SEL:5;                   // 12:8 Event trigger2 selection
    Uint16 rsvd2:3;                     // 15:13 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ETSEL_REG {
    Uint32  all;
    struct  ETSEL_BITS  bit;
};

struct ETPERIOD_BITS {                  // bits description
    Uint16 ET1_PERIOD:3;                // 2:0 Event trigger1 PERIOD
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 ET2_PERIOD:3;                // 10:8 Event trigger2 PERIOD
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ETPERIOD_REG {
    Uint32  all;
    struct  ETPERIOD_BITS  bit;
};

struct ETCNT_BITS {                     // bits description
    Uint16 ET1_CNT:3;                   // 2:0 Event trigger1 COUNT
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 ET2_CNT:3;                   // 10:8 Event trigger2 COUNT
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ETCNT_REG {
    Uint32  all;
    struct  ETCNT_BITS  bit;
};

struct INTEN_BITS {                     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Enable CBC interrupt
    Uint16 OST:1;                       // 2 Enable OST interrupt
    Uint16 ET1:1;                       // 3 Enable ET1 interrupt
    Uint16 ET2:1;                       // 4 Enable ET2 interrupt
    Uint16 CNT_OVF:1;                   // 5 Counter overflow interrupt
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union INTEN_REG {
    Uint32  all;
    struct  INTEN_BITS  bit;
};

struct INTFLAG_BITS {                   // bits description
    Uint16 INT:1;                       // 0 Global Flag
    Uint16 CBC:1;                       // 1 CBC interrupt flag
    Uint16 OST:1;                       // 2 OST interrupt flag
    Uint16 ET1:1;                       // 3 ET1 interrupt flag
    Uint16 ET2:1;                       // 4 ET2 interrupt flag
    Uint16 CNT_OVF:1;                   // 5 Counter overflow flag
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union INTFLAG_REG {
    Uint32  all;
    struct  INTFLAG_BITS  bit;
};

struct INTCLR_BITS {                    // bits description
    Uint16 INT:1;                       // 0 Clear Global Flag
    Uint16 CBC:1;                       // 1 Clear CBC interrupt flag
    Uint16 OST:1;                       // 2 Clear OST interrupt flag
    Uint16 ET1:1;                       // 3 Clear ET1 interrupt flag
    Uint16 ET2:1;                       // 4 Clear ET2 interrupt flag
    Uint16 CNT_OVF:1;                   // 5 Counter overflow flag
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union INTCLR_REG {
    Uint32  all;
    struct  INTCLR_BITS  bit;
};

struct INTFRC_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Force CBC interrupt flag
    Uint16 OST:1;                       // 2 Force OST interrupt flag
    Uint16 ET1:1;                       // 3 Force ET1 interrupt flag
    Uint16 ET2:1;                       // 4 Force ET2 interrupt flag
    Uint16 CNT_OVF:1;                   // 5 Counter overflow flag
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union INTFRC_REG {
    Uint32  all;
    struct  INTFRC_BITS  bit;
};

struct TZSEL_BITS {                     // bits description
    Uint16 CBC1:1;                      // 0 CBC TZ1 select
    Uint16 CBC2:1;                      // 1 CBC TZ2 select
    Uint16 CBC3:1;                      // 2 CBC TZ3 select
    Uint16 CBC4:1;                      // 3 CBC TZ4  select
    Uint16 CBC5:1;                      // 4 CBC TZ5 select
    Uint16 CBC6:1;                      // 5 CBC TZ6 select
    Uint16 CBC7:1;                      // 6 CBC TZ7 select
    Uint16 CBC8:1;                      // 7 CBC TZ8 select
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 OST1:1;                      // 16 OST TZ1 select
    Uint16 OST2:1;                      // 17 OST TZ2 select
    Uint16 OST3:1;                      // 18 OST TZ3 select
    Uint16 OST4:1;                      // 19 OST TZ4  select
    Uint16 OST5:1;                      // 20 OST TZ5 select
    Uint16 OST6:1;                      // 21 OST TZ6 select
    Uint16 OST7:1;                      // 22 OST TZ7 select
    Uint16 OST8:1;                      // 23 OST TZ8 select
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union TZSEL_REG {
    Uint32  all;
    struct  TZSEL_BITS  bit;
};

struct TZCTL_BITS {                     // bits description
    Uint16 TZA:2;                       // 1:0 TZ1 to TZ8 Trip Action on PWMA
    Uint16 TZB:2;                       // 3:2 TZ1 to TZ8 Trip Action on PWMB
    Uint16 CBCPULSE:2;                  // 5:4 Clear Pulse for CBC Trip Latch
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union TZCTL_REG {
    Uint32  all;
    struct  TZCTL_BITS  bit;
};

struct TZCBCOSTFLAG_BITS {              // bits description
    Uint16 CBC1:1;                      // 0 CBC TZ1 Flag
    Uint16 CBC2:1;                      // 1 CBC TZ2 Flag
    Uint16 CBC3:1;                      // 2 CBC TZ3 Flag
    Uint16 CBC4:1;                      // 3 CBC TZ4 Flag
    Uint16 CBC5:1;                      // 4 CBC TZ5 Flag
    Uint16 CBC6:1;                      // 5 CBC TZ6 Flag
    Uint16 CBC7:1;                      // 6 CBC TZ7 Flag
    Uint16 CBC8:1;                      // 7 OST TZ8 Flag
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 OST1:1;                      // 16 OST TZ1 Flag
    Uint16 OST2:1;                      // 17 OST TZ2 Flag
    Uint16 OST3:1;                      // 18 OST TZ3 Flag
    Uint16 OST4:1;                      // 19 OST TZ4 Flag
    Uint16 OST5:1;                      // 20 OST TZ5 Flag
    Uint16 OST6:1;                      // 21 OST TZ6 Flag
    Uint16 OST7:1;                      // 22 OST TZ7 Flag
    Uint16 OST8:1;                      // 23 OST TZ8 Flag
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union TZCBCOSTFLAG_REG {
    Uint32  all;
    struct  TZCBCOSTFLAG_BITS  bit;
};

struct TZCBCOSTCLR_BITS {               // bits description
    Uint16 CBC1:1;                      // 0 CBC TZ1 Clear
    Uint16 CBC2:1;                      // 1 CBC TZ2 Clear
    Uint16 CBC3:1;                      // 2 CBC TZ3 Clear
    Uint16 CBC4:1;                      // 3 CBC TZ4 Clear
    Uint16 CBC5:1;                      // 4 CBC TZ5 Clear
    Uint16 CBC6:1;                      // 5 CBC TZ6 Clear
    Uint16 CBC7:1;                      // 6 CBC TZ7 Clear
    Uint16 CBC8:1;                      // 7 OST TZ8 Clear
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 OST1:1;                      // 16 OST TZ1 Clear
    Uint16 OST2:1;                      // 17 OST TZ2 Clear
    Uint16 OST3:1;                      // 18 OST TZ3 Clear
    Uint16 OST4:1;                      // 19 OST TZ4 Clear
    Uint16 OST5:1;                      // 20 OST TZ5 Clear
    Uint16 OST6:1;                      // 21 OST TZ6 Clear
    Uint16 OST7:1;                      // 22 OST TZ7 Clear
    Uint16 OST8:1;                      // 23 OST TZ8 Clear
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union TZCBCOSTCLR_REG {
    Uint32  all;
    struct  TZCBCOSTCLR_BITS  bit;
};

struct DBCTL_BITS {                     // bits description
    Uint16 OUT_MODE:2;                  // 1:0 Dead Band Output Mode Control
    Uint16 POLSEL:2;                    // 3:2 Polarity Select Control
    Uint16 IN_MODE:2;                   // 5:4 Dead Band Input Select Mode Control
    Uint16 OUTSWAP:2;                   // 7:6 Dead Band Output Swap Control
    Uint16 DEDB_MODE:1;                 // 8 Dead Band Dual-Edge B Mode Control
    Uint16 rsvd1:7;                     // 15:9 Reserved
    Uint16 LOADFEDMODE:2;               // 17:16 Shadow to active load of DBFED
    Uint16 LOADREDMODE:2;               // 19:18 Shadow to active load of DBRED
    Uint16 rsvd2:12;                    // 31:20 Reserved
};

union DBCTL_REG {
    Uint32  all;
    struct  DBCTL_BITS  bit;
};

struct DBFED_BITS {                     // bits description
    Uint16 DBFED:14;                    // 13:0 Falling edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DBFED_REG {
    Uint32  all;
    struct  DBFED_BITS  bit;
};

struct DBRED_BITS {                     // bits description
    Uint16 DBRED:14;                    // 13:0 Rising edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DBRED_REG {
    Uint32  all;
    struct  DBRED_BITS  bit;
};

struct DBFEDS_BITS {                    // bits description
    Uint16 DBFEDS:14;                   // 13:0 Falling edge delay shadow register
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DBFEDS_REG {
    Uint32  all;
    struct  DBFEDS_BITS  bit;
};

struct DBREDS_BITS {                    // bits description
    Uint16 DBREDS:14;                   // 13:0 Rising edge delay shadow register
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DBREDS_REG {
    Uint32  all;
    struct  DBREDS_BITS  bit;
};

struct GLDCTL_BITS {                    // bits description
    Uint16 GLD:1;                       // 0 Global load enable
    Uint16 OSHTMODE:1;                  // 1 Global load one-shot enable
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 GLDMODE:2;                   // 5:4 Select global load event
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GLDCTL_REG {
    Uint32  all;
    struct  GLDCTL_BITS  bit;
};

struct GLDOSHTCTL_BITS {                // bits description
    Uint16 OSHTLD:1;                    // 0 Enable Reload Event in One Shot Mode
    Uint16 OSHTCLR:1;                   // 1 Enable Reload Event in One Shot Mode
    Uint16 GFRCLD:1;                    // 2 Force load event in one shot mode
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union GLDOSHTCTL_REG {
    Uint32  all;
    struct  GLDOSHTCTL_BITS  bit;
};

struct GLDOSHTSTS_BITS {                // bits description
    Uint16 OSHTLATCH:1;                 // 0 One shot latch output
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union GLDOSHTSTS_REG {
    Uint32  all;
    struct  GLDOSHTSTS_BITS  bit;
};

struct PWM1_CMPA_BITS {                 // bits description
    Uint16 PWM1_CMPA:16;                // 15:0 PWM1 Compare A register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM1_CMPA_REG {
    Uint32  all;
    struct  PWM1_CMPA_BITS  bit;
};

struct PWM1_CMPAS_BITS {                // bits description
    Uint16 PWM1_CMPAS:16;               // 15:0 PWM1 Compare A shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM1_CMPAS_REG {
    Uint32  all;
    struct  PWM1_CMPAS_BITS  bit;
};

struct PWM1_CMPB_BITS {                 // bits description
    Uint16 PWM1_CMPB:16;                // 15:0 PWM1 Compare B register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM1_CMPB_REG {
    Uint32  all;
    struct  PWM1_CMPB_BITS  bit;
};

struct PWM1_CMPBS_BITS {                // bits description
    Uint16 PWM1_CMPBS:16;               // 15:0 PWM1 Compare B shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM1_CMPBS_REG {
    Uint32  all;
    struct  PWM1_CMPBS_BITS  bit;
};

struct PWM1_AQCTLA_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM1_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM1_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM1_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM1_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM1_AQCTLA_REG {
    Uint32  all;
    struct  PWM1_AQCTLA_BITS  bit;
};

struct PWM1_AQCTLAS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM1_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM1_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM1_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM1_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM1_AQCTLAS_REG {
    Uint32  all;
    struct  PWM1_AQCTLAS_BITS  bit;
};

struct PWM1_AQCTLB_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM1_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM1_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM1_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM1_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM1_AQCTLB_REG {
    Uint32  all;
    struct  PWM1_AQCTLB_BITS  bit;
};

struct PWM1_AQCTLBS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM1_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM1_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM1_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM1_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM1_AQCTLBS_REG {
    Uint32  all;
    struct  PWM1_AQCTLBS_BITS  bit;
};

struct PWM1_AQSFRC_BITS {               // bits description
    Uint16 PWMA:3;                      // 2:0 Action qualifier software force on PWMA
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMB:3;                      // 6:4 Action qualifier software force on PWMB
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM1_AQSFRC_REG {
    Uint32  all;
    struct  PWM1_AQSFRC_BITS  bit;
};

struct PWM1_AQOTSFRC_BITS {             // bits description
    Uint16 PWMA:1;                      // 0 Action qualifier one time software force on PWMA
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 PWMB:1;                      // 4 Action qualifier software force on PWMB
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM1_AQOTSFRC_REG {
    Uint32  all;
    struct  PWM1_AQOTSFRC_BITS  bit;
};

struct PWM2_CMPA_BITS {                 // bits description
    Uint16 PWM2_CMPA:16;                // 15:0 PWM2 Compare A register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM2_CMPA_REG {
    Uint32  all;
    struct  PWM2_CMPA_BITS  bit;
};

struct PWM2_CMPAS_BITS {                // bits description
    Uint16 PWM2_CMPAS:16;               // 15:0 PWM2 Compare A shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM2_CMPAS_REG {
    Uint32  all;
    struct  PWM2_CMPAS_BITS  bit;
};

struct PWM2_CMPB_BITS {                 // bits description
    Uint16 PWM2_CMPB:16;                // 15:0 PWM2 Compare B register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM2_CMPB_REG {
    Uint32  all;
    struct  PWM2_CMPB_BITS  bit;
};

struct PWM2_CMPBS_BITS {                // bits description
    Uint16 PWM2_CMPBS:16;               // 15:0 PWM2 Compare B shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM2_CMPBS_REG {
    Uint32  all;
    struct  PWM2_CMPBS_BITS  bit;
};

struct PWM2_AQCTLA_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM2_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM2_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM2_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM2_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM2_AQCTLA_REG {
    Uint32  all;
    struct  PWM2_AQCTLA_BITS  bit;
};

struct PWM2_AQCTLAS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM2_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM2_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM2_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM2_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM2_AQCTLAS_REG {
    Uint32  all;
    struct  PWM2_AQCTLAS_BITS  bit;
};

struct PWM2_AQCTLB_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM2_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM2_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM2_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM2_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM2_AQCTLB_REG {
    Uint32  all;
    struct  PWM2_AQCTLB_BITS  bit;
};

struct PWM2_AQCTLBS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM2_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM2_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM2_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM2_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM2_AQCTLBS_REG {
    Uint32  all;
    struct  PWM2_AQCTLBS_BITS  bit;
};

struct PWM2_AQSFRC_BITS {               // bits description
    Uint16 PWMA:3;                      // 2:0 Action qualifier software force on PWMA
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMB:3;                      // 6:4 Action qualifier software force on PWMB
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM2_AQSFRC_REG {
    Uint32  all;
    struct  PWM2_AQSFRC_BITS  bit;
};

struct PWM2_AQOTSFRC_BITS {             // bits description
    Uint16 PWMA:1;                      // 0 Action qualifier one time software force on PWMA
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 PWMB:1;                      // 4 Action qualifier software force on PWMB
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM2_AQOTSFRC_REG {
    Uint32  all;
    struct  PWM2_AQOTSFRC_BITS  bit;
};

struct PWM3_CMPA_BITS {                 // bits description
    Uint16 PWM3_CMPA:16;                // 15:0 PWM3 Compare A register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM3_CMPA_REG {
    Uint32  all;
    struct  PWM3_CMPA_BITS  bit;
};

struct PWM3_CMPAS_BITS {                // bits description
    Uint16 PWM3_CMPAS:16;               // 15:0 PWM3 Compare A shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM3_CMPAS_REG {
    Uint32  all;
    struct  PWM3_CMPAS_BITS  bit;
};

struct PWM3_CMPB_BITS {                 // bits description
    Uint16 PWM3_CMPB:16;                // 15:0 PWM3 Compare B register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM3_CMPB_REG {
    Uint32  all;
    struct  PWM3_CMPB_BITS  bit;
};

struct PWM3_CMPBS_BITS {                // bits description
    Uint16 PWM3_CMPBS:16;               // 15:0 PWM3 Compare B shadow register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PWM3_CMPBS_REG {
    Uint32  all;
    struct  PWM3_CMPBS_BITS  bit;
};

struct PWM3_AQCTLA_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM3_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM3_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM3_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM3_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM3_AQCTLA_REG {
    Uint32  all;
    struct  PWM3_AQCTLA_BITS  bit;
};

struct PWM3_AQCTLAS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM3_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM3_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM3_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM3_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM3_AQCTLAS_REG {
    Uint32  all;
    struct  PWM3_AQCTLAS_BITS  bit;
};

struct PWM3_AQCTLB_BITS {               // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM3_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM3_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM3_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM3_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM3_AQCTLB_REG {
    Uint32  all;
    struct  PWM3_AQCTLB_BITS  bit;
};

struct PWM3_AQCTLBS_BITS {              // bits description
    Uint16 ZRO:2;                       // 1:0 Action When TBCTR = 0
    Uint16 PRD:2;                       // 3:2 Action When TBCTR = TBPRD
    Uint16 CAU:2;                       // 5:4 Action When TBCTR = PWM3_CMPA on Up Count
    Uint16 CAD:2;                       // 7:6 Action When TBCTR = PWM3_CMPA on Down Count
    Uint16 CBU:2;                       // 9:8 Action When TBCTR = PWM3_CMPB on Up Count
    Uint16 CBD:2;                       // 11:10 Action When TBCTR = PWM3_CMPB on Down Count
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PWM3_AQCTLBS_REG {
    Uint32  all;
    struct  PWM3_AQCTLBS_BITS  bit;
};

struct PWM3_AQSFRC_BITS {               // bits description
    Uint16 PWMA:3;                      // 2:0 Action qualifier software force on PWMA
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMB:3;                      // 6:4 Action qualifier software force on PWMB
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM3_AQSFRC_REG {
    Uint32  all;
    struct  PWM3_AQSFRC_BITS  bit;
};

struct PWM3_AQOTSFRC_BITS {             // bits description
    Uint16 PWMA:1;                      // 0 Action qualifier one time software force on PWMA
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 PWMB:1;                      // 4 Action qualifier software force on PWMB
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PWM3_AQOTSFRC_REG {
    Uint32  all;
    struct  PWM3_AQOTSFRC_BITS  bit;
};

struct MCPWM_6CH_REGS {
    union   REVISION_REG                     REVISION;                     // IP revision id register
    Uint16                                   rsvd1[6];                     // Reserved
    union   TBCTL_REG                        TBCTL;                        // Time base control register
    union   TBPRD_REG                        TBPRD;                        // Time base period register
    union   TBPRDS_REG                       TBPRDS;                       // Time base period shadow register
    union   TBPHS_REG                        TBPHS;                        // Time base phase offset register
    union   TBSTS_REG                        TBSTS;                        // Time base status register
    union   TBSTSCLR_REG                     TBSTSCLR;                     // Time base status clear register
    union   TBCTR_REG                        TBCTR;                        // Time base counter register
    Uint16                                   rsvd2[2];                     // Reserved
    union   CMPCTL_REG                       CMPCTL;                       // Counter compare control register
    Uint16                                   rsvd3[6];                     // Reserved
    union   CMPC_REG                         CMPC;                         // Counter compare C register
    union   CMPD_REG                         CMPD;                         // Counter compare D register
    union   CMPCS_REG                        CMPCS;                        // Counter compare C shadow register
    union   CMPDS_REG                        CMPDS;                        // Counter compare D shadow register
    union   AQCTL_REG                        AQCTL;                        // Action qualifier control register
    Uint16                                   rsvd4[6];                     // Reserved
    union   SOCEN_REG                        SOCEN;                        // Start of conversion enable
    union   SOCSEL_REG                       SOCSEL;                       // Start of conversion selection
    union   SOCPERIOD_REG                    SOCPERIOD;                    // Start of conversion period
    union   SOCCNT_REG                       SOCCNT;                       // Start of conversion count
    union   SOCFLAG_REG                      SOCFLAG;                      // Start of conversion flag
    union   SOCCLR_REG                       SOCCLR;                       // Start of conversion clear
    Uint16                                   rsvd5[4];                     // Reserved
    union   ETSEL_REG                        ETSEL;                        // Event trigger selection
    union   ETPERIOD_REG                     ETPERIOD;                     // Event trigger period
    union   ETCNT_REG                        ETCNT;                        // Event trigger count
    Uint16                                   rsvd6[2];                     // Reserved
    union   INTEN_REG                        INTEN;                        // Interrupt enable
    union   INTFLAG_REG                      INTFLAG;                      // Interrupt flag
    union   INTCLR_REG                       INTCLR;                       // Interrupt clear
    union   INTFRC_REG                       INTFRC;                       // Interrupt force
    union   TZSEL_REG                        TZSEL;                        // Trip Zone selection
    Uint16                                   rsvd7[4];                     // Reserved
    union   TZCTL_REG                        TZCTL;                        // Trip Zone control
    union   TZCBCOSTFLAG_REG                 TZCBCOSTFLAG;                 // Trip zone CBCOST flag
    union   TZCBCOSTCLR_REG                  TZCBCOSTCLR;                  // Trip zone CBCOST flag clear
    Uint16                                   rsvd8[4];                     // Reserved
    union   DBCTL_REG                        DBCTL;                        // Dead band control register
    Uint16                                   rsvd9[6];                     // Reserved
    union   DBFED_REG                        DBFED;                        // Dead band fall edge delay
    union   DBRED_REG                        DBRED;                        // Dead band rise edge delay
    union   DBFEDS_REG                       DBFEDS;                       // Dead band fall edge delay shadow register
    union   DBREDS_REG                       DBREDS;                       // Dead band rise edge delay shadow register
    Uint16                                   rsvd10[8];                    // Reserved
    union   GLDCTL_REG                       GLDCTL;                       // Global load control register
    union   GLDOSHTCTL_REG                   GLDOSHTCTL;                   // Global load one shot control register
    union   GLDOSHTSTS_REG                   GLDOSHTSTS;                   // Global load one shot status register
    Uint16                                   rsvd11[2];                    // Reserved
    union   PWM1_CMPA_REG                    PWM1_CMPA;                    // PWM1 counter compare A register
    union   PWM1_CMPAS_REG                   PWM1_CMPAS;                   // PWM1 counter compare A shadow register
    union   PWM1_CMPB_REG                    PWM1_CMPB;                    // PWM1 counter compare B register
    union   PWM1_CMPBS_REG                   PWM1_CMPBS;                   // PWM1 counter compare B shadow register
    Uint16                                   rsvd12[8];                    // Reserved
    union   PWM1_AQCTLA_REG                  PWM1_AQCTLA;                  // PWM1 action qualifier A register
    union   PWM1_AQCTLAS_REG                 PWM1_AQCTLAS;                 // PWM1 action qualifier A shadow register
    union   PWM1_AQCTLB_REG                  PWM1_AQCTLB;                  // PWM1 action qualifier B register
    union   PWM1_AQCTLBS_REG                 PWM1_AQCTLBS;                 // PWM1 action qualifier B shadow register
    union   PWM1_AQSFRC_REG                  PWM1_AQSFRC;                  // PWM1 action qualifier software force
    union   PWM1_AQOTSFRC_REG                PWM1_AQOTSFRC;                // PWM1 action qualifier one time software force
    Uint16                                   rsvd13[228];                  // Reserved
    union   PWM2_CMPA_REG                    PWM2_CMPA;                    // PWM2 counter compare A register
    union   PWM2_CMPAS_REG                   PWM2_CMPAS;                   // PWM2 counter compare A shadow register
    union   PWM2_CMPB_REG                    PWM2_CMPB;                    // PWM2 counter compare B register
    union   PWM2_CMPBS_REG                   PWM2_CMPBS;                   // PWM2 counter compare B shadow register
    Uint16                                   rsvd14[8];                    // Reserved
    union   PWM2_AQCTLA_REG                  PWM2_AQCTLA;                  // PWM2 action qualifier A register
    union   PWM2_AQCTLAS_REG                 PWM2_AQCTLAS;                 // PWM2 action qualifier A shadow register
    union   PWM2_AQCTLB_REG                  PWM2_AQCTLB;                  // PWM2 action qualifier B register
    union   PWM2_AQCTLBS_REG                 PWM2_AQCTLBS;                 // PWM2 action qualifier B shadow register
    union   PWM2_AQSFRC_REG                  PWM2_AQSFRC;                  // PWM2 action qualifier software force
    union   PWM2_AQOTSFRC_REG                PWM2_AQOTSFRC;                // PWM2 action qualifier one time software force
    Uint16                                   rsvd15[228];                  // Reserved
    union   PWM3_CMPA_REG                    PWM3_CMPA;                    // PWM3 counter compare A register
    union   PWM3_CMPAS_REG                   PWM3_CMPAS;                   // PWM3 counter compare A shadow register
    union   PWM3_CMPB_REG                    PWM3_CMPB;                    // PWM3 counter compare B register
    union   PWM3_CMPBS_REG                   PWM3_CMPBS;                   // PWM3 counter compare B shadow register
    Uint16                                   rsvd16[8];                    // Reserved
    union   PWM3_AQCTLA_REG                  PWM3_AQCTLA;                  // PWM3 action qualifier A register
    union   PWM3_AQCTLAS_REG                 PWM3_AQCTLAS;                 // PWM3 action qualifier A shadow register
    union   PWM3_AQCTLB_REG                  PWM3_AQCTLB;                  // PWM3 action qualifier B register
    union   PWM3_AQCTLBS_REG                 PWM3_AQCTLBS;                 // PWM3 action qualifier B shadow register
    union   PWM3_AQSFRC_REG                  PWM3_AQSFRC;                  // PWM3 action qualifier software force
    union   PWM3_AQOTSFRC_REG                PWM3_AQOTSFRC;                // PWM3 action qualifier one time software force
};

struct MCPWM_2CH_REGS {
    union   REVISION_REG                     REVISION;                     // IP revision id register
    Uint16                                   rsvd1[6];                     // Reserved
    union   TBCTL_REG                        TBCTL;                        // Time base control register
    union   TBPRD_REG                        TBPRD;                        // Time base period register
    union   TBPRDS_REG                       TBPRDS;                       // Time base period shadow register
    union   TBPHS_REG                        TBPHS;                        // Time base phase offset register
    union   TBSTS_REG                        TBSTS;                        // Time base status register
    union   TBSTSCLR_REG                     TBSTSCLR;                     // Time base status clear register
    union   TBCTR_REG                        TBCTR;                        // Time base counter register
    Uint16                                   rsvd2[2];                     // Reserved
    union   CMPCTL_REG                       CMPCTL;                       // Counter compare control register
    Uint16                                   rsvd3[6];                     // Reserved
    union   CMPC_REG                         CMPC;                         // Counter compare C register
    union   CMPD_REG                         CMPD;                         // Counter compare D register
    union   CMPCS_REG                        CMPCS;                        // Counter compare C shadow register
    union   CMPDS_REG                        CMPDS;                        // Counter compare D shadow register
    union   AQCTL_REG                        AQCTL;                        // Action qualifier control register
    Uint16                                   rsvd4[6];                     // Reserved
    union   SOCEN_REG                        SOCEN;                        // Start of conversion enable
    union   SOCSEL_REG                       SOCSEL;                       // Start of conversion selection
    union   SOCPERIOD_REG                    SOCPERIOD;                    // Start of conversion period
    union   SOCCNT_REG                       SOCCNT;                       // Start of conversion count
    union   SOCFLAG_REG                      SOCFLAG;                      // Start of conversion flag
    union   SOCCLR_REG                       SOCCLR;                       // Start of conversion clear
    Uint16                                   rsvd5[4];                     // Reserved
    union   ETSEL_REG                        ETSEL;                        // Event trigger selection
    union   ETPERIOD_REG                     ETPERIOD;                     // Event trigger period
    union   ETCNT_REG                        ETCNT;                        // Event trigger count
    Uint16                                   rsvd6[2];                     // Reserved
    union   INTEN_REG                        INTEN;                        // Interrupt enable
    union   INTFLAG_REG                      INTFLAG;                      // Interrupt flag
    union   INTCLR_REG                       INTCLR;                       // Interrupt clear
    union   INTFRC_REG                       INTFRC;                       // Interrupt force
    union   TZSEL_REG                        TZSEL;                        // Trip Zone selection
    Uint16                                   rsvd7[4];                     // Reserved
    union   TZCTL_REG                        TZCTL;                        // Trip Zone control
    union   TZCBCOSTFLAG_REG                 TZCBCOSTFLAG;                 // Trip zone CBCOST flag
    union   TZCBCOSTCLR_REG                  TZCBCOSTCLR;                  // Trip zone CBCOST flag clear
    Uint16                                   rsvd8[4];                     // Reserved
    union   DBCTL_REG                        DBCTL;                        // Dead band control register
    Uint16                                   rsvd9[6];                     // Reserved
    union   DBFED_REG                        DBFED;                        // Dead band fall edge delay
    union   DBRED_REG                        DBRED;                        // Dead band rise edge delay
    union   DBFEDS_REG                       DBFEDS;                       // Dead band fall edge delay shadow register
    union   DBREDS_REG                       DBREDS;                       // Dead band rise edge delay shadow register
    Uint16                                   rsvd10[8];                    // Reserved
    union   GLDCTL_REG                       GLDCTL;                       // Global load control register
    union   GLDOSHTCTL_REG                   GLDOSHTCTL;                   // Global load one shot control register
    union   GLDOSHTSTS_REG                   GLDOSHTSTS;                   // Global load one shot status register
    Uint16                                   rsvd11[2];                    // Reserved
    union   PWM1_CMPA_REG                    PWM1_CMPA;                    // PWM1 counter compare A register
    union   PWM1_CMPAS_REG                   PWM1_CMPAS;                   // PWM1 counter compare A shadow register
    union   PWM1_CMPB_REG                    PWM1_CMPB;                    // PWM1 counter compare B register
    union   PWM1_CMPBS_REG                   PWM1_CMPBS;                   // PWM1 counter compare B shadow register
    Uint16                                   rsvd12[8];                    // Reserved
    union   PWM1_AQCTLA_REG                  PWM1_AQCTLA;                  // PWM1 action qualifier A register
    union   PWM1_AQCTLAS_REG                 PWM1_AQCTLAS;                 // PWM1 action qualifier A shadow register
    union   PWM1_AQCTLB_REG                  PWM1_AQCTLB;                  // PWM1 action qualifier B register
    union   PWM1_AQCTLBS_REG                 PWM1_AQCTLBS;                 // PWM1 action qualifier B shadow register
    union   PWM1_AQSFRC_REG                  PWM1_AQSFRC;                  // PWM1 action qualifier software force
    union   PWM1_AQOTSFRC_REG                PWM1_AQOTSFRC;                // PWM1 action qualifier one time software force
};

//---------------------------------------------------------------------------
// MCPWM External References & Function Declarations:
//
extern volatile struct MCPWM_6CH_REGS Pwm1Regs;
extern volatile struct MCPWM_2CH_REGS Pwm3Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
