//###########################################################################
//
// FILE:    f28p65x_epwm.h
//
// TITLE:   Definitions for the EPWM registers.
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

#ifndef F28P65X_EPWM_H
#define F28P65X_EPWM_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// EPWM Individual Register Bit Definitions:

struct TBCTL_BITS {                     // bits description
    Uint16 CTRMODE:2;                   // 1:0 Counter Mode
    Uint16 PHSEN:1;                     // 2 Phase Load Enable
    Uint16 PRDLD:1;                     // 3 Active Period Load
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 SWFSYNC:1;                   // 6 Software Force Sync Pulse
    Uint16 HSPCLKDIV:3;                 // 9:7 High Speed TBCLK Pre-scaler
    Uint16 CLKDIV:3;                    // 12:10 Time Base Clock Pre-scaler
    Uint16 PHSDIR:1;                    // 13 Phase Direction Bit
    Uint16 FREE_SOFT:2;                 // 15:14 Emulation Mode Bits
};

union TBCTL_REG {
    Uint16  all;
    struct  TBCTL_BITS  bit;
};

struct TBCTL2_BITS {                    // bits description
    Uint16 rsvd1:5;                     // 4:0 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 OSHTSYNCMODE:1;              // 6 One shot sync mode
    Uint16 OSHTSYNC:1;                  // 7 One shot sync
    Uint16 rsvd3:4;                     // 11:8 Reserved
    Uint16 rsvd4:2;                     // 13:12 Reserved
    Uint16 PRDLDSYNC:2;                 // 15:14 PRD Shadow to Active Load on SYNC Event
};

union TBCTL2_REG {
    Uint16  all;
    struct  TBCTL2_BITS  bit;
};

struct EPWMSYNCINSEL_BITS {             // bits description
    Uint16 SEL:7;                       // 6:0 EPWMxSYNCI source select
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union EPWMSYNCINSEL_REG {
    Uint16  all;
    struct  EPWMSYNCINSEL_BITS  bit;
};

struct TBSTS_BITS {                     // bits description
    Uint16 CTRDIR:1;                    // 0 Counter Direction Status
    Uint16 SYNCI:1;                     // 1 External Input Sync Status
    Uint16 CTRMAX:1;                    // 2 Counter Max Latched Status
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union TBSTS_REG {
    Uint16  all;
    struct  TBSTS_BITS  bit;
};

struct EPWMSYNCOUTEN_BITS {             // bits description
    Uint16 SWEN:1;                      // 0 EPWMxSYNCO Software Force Enable
    Uint16 ZEROEN:1;                    // 1 EPWMxSYNCO Zero Count Event Enable
    Uint16 CMPBEN:1;                    // 2 EPWMxSYNCO Compare B Event Enable
    Uint16 CMPCEN:1;                    // 3 EPWMxSYNCO Compare C Event Enable
    Uint16 CMPDEN:1;                    // 4 EPWMxSYNCO Compare D Event Enable
    Uint16 DCAEVT1EN:1;                 // 5 EPWMxSYNCO Digital Compare A Event 1 Sync Enable
    Uint16 DCBEVT1EN:1;                 // 6 EPWMxSYNCO Digital Compare B Event 1 Sync Enable
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union EPWMSYNCOUTEN_REG {
    Uint16  all;
    struct  EPWMSYNCOUTEN_BITS  bit;
};

struct TBCTL3_BITS {                    // bits description
    Uint16 OSSFRCEN:1;                  // 0 One Shot Sync Force Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union TBCTL3_REG {
    Uint16  all;
    struct  TBCTL3_BITS  bit;
};

struct CMPCTL_BITS {                    // bits description
    Uint16 LOADAMODE:2;                 // 1:0 Active Compare A Load
    Uint16 LOADBMODE:2;                 // 3:2 Active Compare B Load
    Uint16 SHDWAMODE:1;                 // 4 Compare A Register Block Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWBMODE:1;                 // 6 Compare B Register Block Operating Mode
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 SHDWAFULL:1;                 // 8 Compare A Shadow Register Full Status
    Uint16 SHDWBFULL:1;                 // 9 Compare B Shadow Register Full Status
    Uint16 LOADASYNC:2;                 // 11:10 Active Compare A Load on SYNC
    Uint16 LOADBSYNC:2;                 // 13:12 Active Compare B Load on SYNC
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 LINKDUTYHR:1;                // 15 Enable same values on CMPAHR/CMPBHR
};

union CMPCTL_REG {
    Uint16  all;
    struct  CMPCTL_BITS  bit;
};

struct CMPCTL2_BITS {                   // bits description
    Uint16 LOADCMODE:2;                 // 1:0 Active Compare C Load
    Uint16 LOADDMODE:2;                 // 3:2 Active Compare D load
    Uint16 SHDWCMODE:1;                 // 4 Compare C Block Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWDMODE:1;                 // 6 Compare D Block Operating Mode
    Uint16 rsvd2:3;                     // 9:7 Reserved
    Uint16 LOADCSYNC:2;                 // 11:10 Active Compare C Load on SYNC
    Uint16 LOADDSYNC:2;                 // 13:12 Active Compare D Load on SYNC
    Uint16 rsvd3:2;                     // 15:14 Reserved
};

union CMPCTL2_REG {
    Uint16  all;
    struct  CMPCTL2_BITS  bit;
};

struct DBCTL_BITS {                     // bits description
    Uint16 OUT_MODE:2;                  // 1:0 Dead Band Output Mode Control
    Uint16 POLSEL:2;                    // 3:2 Polarity Select Control
    Uint16 IN_MODE:2;                   // 5:4 Dead Band Input Select Mode Control
    Uint16 LOADREDMODE:2;               // 7:6 Active DBRED Load Mode
    Uint16 LOADFEDMODE:2;               // 9:8 Active DBFED Load Mode
    Uint16 SHDWDBREDMODE:1;             // 10 DBRED Block Operating Mode
    Uint16 SHDWDBFEDMODE:1;             // 11 DBFED Block Operating Mode
    Uint16 OUTSWAP:2;                   // 13:12 Dead Band Output Swap Control
    Uint16 DEDB_MODE:1;                 // 14 Dead Band Dual-Edge B Mode Control
    Uint16 HALFCYCLE:1;                 // 15 Half Cycle Clocking Enable
};

union DBCTL_REG {
    Uint16  all;
    struct  DBCTL_BITS  bit;
};

struct DBCTL2_BITS {                    // bits description
    Uint16 LOADDBCTLMODE:2;             // 1:0 DBCTL Load from Shadow Mode Select
    Uint16 SHDWDBCTLMODE:1;             // 2 DBCTL Load mode Select
    Uint16 rsvd1:13;                    // 15:3 Reserved
};

union DBCTL2_REG {
    Uint16  all;
    struct  DBCTL2_BITS  bit;
};

struct AQCTL_BITS {                     // bits description
    Uint16 LDAQAMODE:2;                 // 1:0 Action Qualifier A Load Select
    Uint16 LDAQBMODE:2;                 // 3:2 Action Qualifier B Load Select
    Uint16 SHDWAQAMODE:1;               // 4 Action Qualifer A Operating Mode
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 SHDWAQBMODE:1;               // 6 Action Qualifier B Operating Mode
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 LDAQASYNC:2;                 // 9:8 AQCTLA Register Load on SYNC
    Uint16 LDAQBSYNC:2;                 // 11:10 AQCTLB Register Load on SYNC
    Uint16 rsvd3:4;                     // 15:12 Reserved
};

union AQCTL_REG {
    Uint16  all;
    struct  AQCTL_BITS  bit;
};

struct AQTSRCSEL_BITS {                 // bits description
    Uint16 T1SEL:4;                     // 3:0 T1 Event Source Select Bits
    Uint16 T2SEL:4;                     // 7:4 T2 Event Source Select Bits
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQTSRCSEL_REG {
    Uint16  all;
    struct  AQTSRCSEL_BITS  bit;
};

struct PCCTL_BITS {                     // bits description
    Uint16 CHPEN:1;                     // 0 PWM chopping enable
    Uint16 OSHTWTH:4;                   // 4:1 One-shot pulse width
    Uint16 CHPFREQ:3;                   // 7:5 Chopping clock frequency
    Uint16 CHPDUTY:3;                   // 10:8 Chopping clock Duty cycle
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union PCCTL_REG {
    Uint16  all;
    struct  PCCTL_BITS  bit;
};

struct VCAPCTL_BITS {                   // bits description
    Uint16 VCAPE:1;                     // 0 Valley  Capture mode
    Uint16 VCAPSTART:1;                 // 1 Valley  Capture Start
    Uint16 TRIGSEL:3;                   // 4:2 Capture Trigger Select
    Uint16 rsvd1:2;                     // 6:5 Reserved
    Uint16 VDELAYDIV:3;                 // 9:7 Valley Delay Mode Divide Enable
    Uint16 EDGEFILTDLYSEL:1;            // 10 Valley Switching Mode Delay Select
    Uint16 rsvd2:5;                     // 15:11 Reserved
};

union VCAPCTL_REG {
    Uint16  all;
    struct  VCAPCTL_BITS  bit;
};

struct VCNTCFG_BITS {                   // bits description
    Uint16 STARTEDGE:4;                 // 3:0 Counter Start Edge Selection
    Uint16 rsvd1:3;                     // 6:4 Reserved
    Uint16 STARTEDGESTS:1;              // 7 Start Edge Status Bit
    Uint16 STOPEDGE:4;                  // 11:8 Counter Start Edge Selection
    Uint16 rsvd2:3;                     // 14:12 Reserved
    Uint16 STOPEDGESTS:1;               // 15 Stop Edge Status Bit
};

union VCNTCFG_REG {
    Uint16  all;
    struct  VCNTCFG_BITS  bit;
};

struct HRCNFG_BITS {                    // bits description
    Uint16 EDGMODE:2;                   // 1:0 ePWMxA Edge Mode Select Bits
    Uint16 CTLMODE:1;                   // 2 ePWMxA Control Mode Select Bits
    Uint16 HRLOAD:2;                    // 4:3 ePWMxA Shadow Mode Select Bits
    Uint16 SELOUTB:1;                   // 5 EPWMB Output Selection Bit
    Uint16 AUTOCONV:1;                  // 6 Autoconversion Bit
    Uint16 SWAPAB:1;                    // 7 Swap EPWMA and EPWMB Outputs Bit
    Uint16 EDGMODEB:2;                  // 9:8 ePWMxB Edge Mode Select Bits
    Uint16 CTLMODEB:1;                  // 10 ePWMxB Control Mode Select Bits
    Uint16 HRLOADB:2;                   // 12:11 ePWMxB Shadow Mode Select Bits
    Uint16 rsvd1:1;                     // 13 Reserved
    Uint16 rsvd2:2;                     // 15:14 Reserved
};

union HRCNFG_REG {
    Uint16  all;
    struct  HRCNFG_BITS  bit;
};

struct HRCNFG2_BITS {                   // bits description
    Uint16 EDGMODEDB:2;                 // 1:0 Dead-Band Edge-Mode Select Bits
    Uint16 CTLMODEDBRED:2;              // 3:2 DBRED Control Mode Select Bits
    Uint16 CTLMODEDBFED:2;              // 5:4 DBFED Control Mode Select Bits
    Uint16 rsvd1:8;                     // 13:6 Reserved
    Uint16 rsvd2:1;                     // 14 Reserved
    Uint16 rsvd3:1;                     // 15 Reserved
};

union HRCNFG2_REG {
    Uint16  all;
    struct  HRCNFG2_BITS  bit;
};

struct HRPCTL_BITS {                    // bits description
    Uint16 HRPE:1;                      // 0 High Resolution Period Enable
    Uint16 PWMSYNCSEL:1;                // 1 EPWMSYNCPER Source Select
    Uint16 TBPHSHRLOADE:1;              // 2 TBPHSHR Load Enable
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMSYNCSELX:3;               // 6:4 EPWMSYNCPER Extended Source Select Bit:
    Uint16 rsvd2:9;                     // 15:7 Reserved
};

union HRPCTL_REG {
    Uint16  all;
    struct  HRPCTL_BITS  bit;
};

struct TRREM_BITS {                     // bits description
    Uint16 TRREM:11;                    // 10:0 HRPWM Remainder Bits
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union TRREM_REG {
    Uint16  all;
    struct  TRREM_BITS  bit;
};

struct GLDCTL_BITS {                    // bits description
    Uint16 GLD:1;                       // 0 Global Shadow to Active load event control
    Uint16 GLDMODE:4;                   // 4:1 Shadow to Active Global Load Pulse Selection
    Uint16 OSHTMODE:1;                  // 5 One Shot Load mode control bit
    Uint16 rsvd1:1;                     // 6 Reserved
    Uint16 GLDPRD:3;                    // 9:7 Global Load Strobe Period Select Register
    Uint16 GLDCNT:3;                    // 12:10 Global Load Strobe Counter Register
    Uint16 rsvd2:3;                     // 15:13 Reserved
};

union GLDCTL_REG {
    Uint16  all;
    struct  GLDCTL_BITS  bit;
};

struct GLDCFG_BITS {                    // bits description
    Uint16 TBPRD_TBPRDHR:1;             // 0 Global load event configuration for TBPRD:TBPRDHR
    Uint16 CMPA_CMPAHR:1;               // 1 Global load event configuration for CMPA:CMPAHR
    Uint16 CMPB_CMPBHR:1;               // 2 Global load event configuration for CMPB:CMPBHR
    Uint16 CMPC:1;                      // 3 Global load event configuration for CMPC
    Uint16 CMPD:1;                      // 4 Global load event configuration for CMPD
    Uint16 DBRED_DBREDHR:1;             // 5 Global load event configuration for DBRED:DBREDHR
    Uint16 DBFED_DBFEDHR:1;             // 6 Global load event configuration for DBFED:DBFEDHR
    Uint16 DBCTL:1;                     // 7 Global load event configuration for DBCTL
    Uint16 AQCTLA_AQCTLA2:1;            // 8 Global load event configuration for AQCTLA/A2
    Uint16 AQCTLB_AQCTLB2:1;            // 9 Global load event configuration for AQCTLB/B2
    Uint16 AQCSFRC:1;                   // 10 Global load event configuration for AQCSFRC
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union GLDCFG_REG {
    Uint16  all;
    struct  GLDCFG_BITS  bit;
};

struct EPWMXLINK_BITS {                 // bits description
    Uint16 TBPRDLINK:5;                 // 4:0 TBPRD:TBPRDHR  Link
    Uint16 CMPALINK:5;                  // 9:5 CMPA:CMPAHR Link
    Uint16 CMPBLINK:5;                  // 14:10 CMPB:CMPBHR Link
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 CMPCLINK:5;                  // 20:16 CMPC Link
    Uint16 CMPDLINK:5;                  // 25:21 CMPD Link
    Uint16 GLDCTL2LINK:5;               // 30:26 GLDCTL2 Link
    Uint16 rsvd2:1;                     // 31 Reserved
};

union EPWMXLINK_REG {
    Uint32  all;
    struct  EPWMXLINK_BITS  bit;
};

struct EPWMXLINK2_BITS {                // bits description
    Uint16 DBREDLINK:5;                 // 4:0 DBRED:DBREDHR Link
    Uint16 DBFEDLINK:5;                 // 9:5 DBFED:DBFEDHR Link
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWMXLINK2_REG {
    Uint32  all;
    struct  EPWMXLINK2_BITS  bit;
};

struct AQCTLA_BITS {                    // bits description
    Uint16 ZRO:2;                       // 1:0 Action Counter = Zero
    Uint16 PRD:2;                       // 3:2 Action Counter = Period
    Uint16 CAU:2;                       // 5:4 Action Counter = Compare A Up
    Uint16 CAD:2;                       // 7:6 Action Counter = Compare A Down
    Uint16 CBU:2;                       // 9:8 Action Counter = Compare B Up
    Uint16 CBD:2;                       // 11:10 Action Counter = Compare B Down
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union AQCTLA_REG {
    Uint16  all;
    struct  AQCTLA_BITS  bit;
};

struct AQCTLA2_BITS {                   // bits description
    Uint16 T1U:2;                       // 1:0 Action when event occurs on T1 in UP-Count
    Uint16 T1D:2;                       // 3:2 Action when event occurs on T1 in DOWN-Count
    Uint16 T2U:2;                       // 5:4 Action when event occurs on T2 in UP-Count
    Uint16 T2D:2;                       // 7:6 Action when event occurs on T2 in DOWN-Count
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQCTLA2_REG {
    Uint16  all;
    struct  AQCTLA2_BITS  bit;
};

struct AQCTLB_BITS {                    // bits description
    Uint16 ZRO:2;                       // 1:0 Action Counter = Zero
    Uint16 PRD:2;                       // 3:2 Action Counter = Period
    Uint16 CAU:2;                       // 5:4 Action Counter = Compare A Up
    Uint16 CAD:2;                       // 7:6 Action Counter = Compare A Down
    Uint16 CBU:2;                       // 9:8 Action Counter = Compare B Up
    Uint16 CBD:2;                       // 11:10 Action Counter = Compare B Down
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union AQCTLB_REG {
    Uint16  all;
    struct  AQCTLB_BITS  bit;
};

struct AQCTLB2_BITS {                   // bits description
    Uint16 T1U:2;                       // 1:0 Action when event occurs on T1 in UP-Count
    Uint16 T1D:2;                       // 3:2 Action when event occurs on T1 in DOWN-Count
    Uint16 T2U:2;                       // 5:4 Action when event occurs on T2 in UP-Count
    Uint16 T2D:2;                       // 7:6 Action when event occurs on T2 in DOWN-Count
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQCTLB2_REG {
    Uint16  all;
    struct  AQCTLB2_BITS  bit;
};

struct AQSFRC_BITS {                    // bits description
    Uint16 ACTSFA:2;                    // 1:0 Action when One-time SW Force A Invoked
    Uint16 OTSFA:1;                     // 2 One-time SW Force A Output
    Uint16 ACTSFB:2;                    // 4:3 Action when One-time SW Force B Invoked
    Uint16 OTSFB:1;                     // 5 One-time SW Force A Output
    Uint16 RLDCSF:2;                    // 7:6 Reload from Shadow Options
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union AQSFRC_REG {
    Uint16  all;
    struct  AQSFRC_BITS  bit;
};

struct AQCSFRC_BITS {                   // bits description
    Uint16 CSFA:2;                      // 1:0 Continuous Software Force on output A
    Uint16 CSFB:2;                      // 3:2 Continuous Software Force on output B
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union AQCSFRC_REG {
    Uint16  all;
    struct  AQCSFRC_BITS  bit;
};

struct DBREDHR_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:7;                     // 7:1 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 DBREDHR:7;                   // 15:9 DBREDHR High Resolution Bits
};

union DBREDHR_REG {
    Uint16  all;
    struct  DBREDHR_BITS  bit;
};

struct DBRED_BITS {                     // bits description
    Uint16 DBRED:14;                    // 13:0 Rising edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
};

union DBRED_REG {
    Uint16  all;
    struct  DBRED_BITS  bit;
};

struct DBFEDHR_BITS {                   // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:7;                     // 7:1 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 DBFEDHR:7;                   // 15:9 DBFEDHR High Resolution Bits
};

union DBFEDHR_REG {
    Uint16  all;
    struct  DBFEDHR_BITS  bit;
};

struct DBFED_BITS {                     // bits description
    Uint16 DBFED:14;                    // 13:0 Falling edge delay value
    Uint16 rsvd1:2;                     // 15:14 Reserved
};

union DBFED_REG {
    Uint16  all;
    struct  DBFED_BITS  bit;
};

struct TBPHS_BITS {                     // bits description
    Uint16 TBPHSHR:16;                  // 15:0 Extension Register for HRPWM Phase (8-bits)
    Uint16 TBPHS:16;                    // 31:16 Phase Offset Register
};

union TBPHS_REG {
    Uint32  all;
    struct  TBPHS_BITS  bit;
};

struct CMPA_BITS {                      // bits description
    Uint16 CMPAHR:16;                   // 15:0 Compare A HRPWM Extension Register
    Uint16 CMPA:16;                     // 31:16 Compare A Register
};

union CMPA_REG {
    Uint32  all;
    struct  CMPA_BITS  bit;
};

struct CMPB_BITS {                      // bits description
    Uint16 CMPBHR:16;                   // 15:0 Compare B High Resolution Bits
    Uint16 CMPB:16;                     // 31:16 Compare B Register
};

union CMPB_REG {
    Uint32  all;
    struct  CMPB_BITS  bit;
};

struct GLDCTL2_BITS {                   // bits description
    Uint16 OSHTLD:1;                    // 0 Enable reload event in one shot mode
    Uint16 GFRCLD:1;                    // 1 Force reload event in one shot mode
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union GLDCTL2_REG {
    Uint16  all;
    struct  GLDCTL2_BITS  bit;
};

struct TZSEL_BITS {                     // bits description
    Uint16 CBC1:1;                      // 0 TZ1 CBC select
    Uint16 CBC2:1;                      // 1 TZ2 CBC select
    Uint16 CBC3:1;                      // 2 TZ3 CBC select
    Uint16 CBC4:1;                      // 3 TZ4 CBC select
    Uint16 CBC5:1;                      // 4 TZ5 CBC select
    Uint16 CBC6:1;                      // 5 TZ6 CBC select
    Uint16 DCAEVT2:1;                   // 6 DCAEVT2 CBC select
    Uint16 DCBEVT2:1;                   // 7 DCBEVT2 CBC select
    Uint16 OSHT1:1;                     // 8 One-shot TZ1 select
    Uint16 OSHT2:1;                     // 9 One-shot TZ2 select
    Uint16 OSHT3:1;                     // 10 One-shot TZ3 select
    Uint16 OSHT4:1;                     // 11 One-shot TZ4 select
    Uint16 OSHT5:1;                     // 12 One-shot TZ5 select
    Uint16 OSHT6:1;                     // 13 One-shot TZ6 select
    Uint16 DCAEVT1:1;                   // 14 One-shot DCAEVT1 select
    Uint16 DCBEVT1:1;                   // 15 One-shot DCBEVT1 select
};

union TZSEL_REG {
    Uint16  all;
    struct  TZSEL_BITS  bit;
};

struct TZSEL2_BITS {                    // bits description
    Uint16 CAPEVTCBC:1;                 // 0 CAPEVT CBC select
    Uint16 rsvd1:7;                     // 7:1 Reserved
    Uint16 CAPEVTOST:1;                 // 8 CAPEVT One-shot select
    Uint16 rsvd2:7;                     // 15:9 Reserved
};

union TZSEL2_REG {
    Uint16  all;
    struct  TZSEL2_BITS  bit;
};

struct TZDCSEL_BITS {                   // bits description
    Uint16 DCAEVT1:3;                   // 2:0 Digital Compare Output A Event 1
    Uint16 DCAEVT2:3;                   // 5:3 Digital Compare Output A Event 2
    Uint16 DCBEVT1:3;                   // 8:6 Digital Compare Output B Event 1
    Uint16 DCBEVT2:3;                   // 11:9 Digital Compare Output B Event 2
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZDCSEL_REG {
    Uint16  all;
    struct  TZDCSEL_BITS  bit;
};

struct TZCTL_BITS {                     // bits description
    Uint16 TZA:2;                       // 1:0 TZ1 to TZ6 Trip Action On EPWMxA
    Uint16 TZB:2;                       // 3:2 TZ1 to TZ6 Trip Action On EPWMxB
    Uint16 DCAEVT1:2;                   // 5:4 EPWMxA action on DCAEVT1
    Uint16 DCAEVT2:2;                   // 7:6 EPWMxA action on DCAEVT2
    Uint16 DCBEVT1:2;                   // 9:8 EPWMxB action on DCBEVT1
    Uint16 DCBEVT2:2;                   // 11:10 EPWMxB action on DCBEVT2
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTL_REG {
    Uint16  all;
    struct  TZCTL_BITS  bit;
};

struct TZCTL2_BITS {                    // bits description
    Uint16 TZAU:3;                      // 2:0 Trip Action On EPWMxA while Count direction is UP
    Uint16 TZAD:3;                      // 5:3 Trip Action On EPWMxA while Count direction is DOWN
    Uint16 TZBU:3;                      // 8:6 Trip Action On EPWMxB while Count direction is UP
    Uint16 TZBD:3;                      // 11:9 Trip Action On EPWMxB while Count direction is DOWN
    Uint16 rsvd1:3;                     // 14:12 Reserved
    Uint16 ETZE:1;                      // 15 TZCTL2 Enable
};

union TZCTL2_REG {
    Uint16  all;
    struct  TZCTL2_BITS  bit;
};

struct TZCTLDCA_BITS {                  // bits description
    Uint16 DCAEVT1U:3;                  // 2:0 DCAEVT1 Action On EPWMxA while Count direction is UP
    Uint16 DCAEVT1D:3;                  // 5:3 DCAEVT1 Action On EPWMxA while Count direction is DOWN
    Uint16 DCAEVT2U:3;                  // 8:6 DCAEVT2 Action On EPWMxA while Count direction is UP
    Uint16 DCAEVT2D:3;                  // 11:9 DCAEVT2 Action On EPWMxA while Count direction is DOWN
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTLDCA_REG {
    Uint16  all;
    struct  TZCTLDCA_BITS  bit;
};

struct TZCTLDCB_BITS {                  // bits description
    Uint16 DCBEVT1U:3;                  // 2:0 DCBEVT1 Action On EPWMxA while Count direction is UP
    Uint16 DCBEVT1D:3;                  // 5:3 DCBEVT1 Action On EPWMxA while Count direction is DOWN
    Uint16 DCBEVT2U:3;                  // 8:6 DCBEVT2 Action On EPWMxA while Count direction is UP
    Uint16 DCBEVT2D:3;                  // 11:9 DCBEVT2 Action On EPWMxA while Count direction is DOWN
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union TZCTLDCB_REG {
    Uint16  all;
    struct  TZCTLDCB_BITS  bit;
};

struct TZEINT_BITS {                    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Trip Zones Cycle By Cycle Int Enable
    Uint16 OST:1;                       // 2 Trip Zones One Shot Int Enable
    Uint16 DCAEVT1:1;                   // 3 Digital Compare A Event 1 Int Enable
    Uint16 DCAEVT2:1;                   // 4 Digital Compare A Event 2 Int Enable
    Uint16 DCBEVT1:1;                   // 5 Digital Compare B Event 1 Int Enable
    Uint16 DCBEVT2:1;                   // 6 Digital Compare B Event 2 Int Enable
    Uint16 CAPEVT:1;                    // 7 Capture Eveent Interrupt Enable
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union TZEINT_REG {
    Uint16  all;
    struct  TZEINT_BITS  bit;
};

struct TZFLG_BITS {                     // bits description
    Uint16 INT:1;                       // 0 Global Int Status Flag
    Uint16 CBC:1;                       // 1 Trip Zones Cycle By Cycle Flag
    Uint16 OST:1;                       // 2 Trip Zones One Shot Flag
    Uint16 DCAEVT1:1;                   // 3 Digital Compare A Event 1 Flag
    Uint16 DCAEVT2:1;                   // 4 Digital Compare A Event 2 Flag
    Uint16 DCBEVT1:1;                   // 5 Digital Compare B Event 1 Flag
    Uint16 DCBEVT2:1;                   // 6 Digital Compare B Event 2 Flag
    Uint16 CAPEVT:1;                    // 7 Capture Event Flag
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TZFLG_REG {
    Uint16  all;
    struct  TZFLG_BITS  bit;
};

struct TZCBCFLG_BITS {                  // bits description
    Uint16 CBC1:1;                      // 0 Latched Status Flag for CBC1 Trip Latch
    Uint16 CBC2:1;                      // 1 Latched Status Flag for CBC2 Trip Latch
    Uint16 CBC3:1;                      // 2 Latched Status Flag for CBC3 Trip Latch
    Uint16 CBC4:1;                      // 3 Latched Status Flag for CBC4 Trip Latch
    Uint16 CBC5:1;                      // 4 Latched Status Flag for CBC5 Trip Latch
    Uint16 CBC6:1;                      // 5 Latched Status Flag for CBC6 Trip Latch
    Uint16 DCAEVT2:1;                   // 6 Latched Status Flag for Digital Compare Output A Event 2
    Uint16 DCBEVT2:1;                   // 7 Latched Status Flag for Digital Compare Output B Event 2
    Uint16 CAPEVT:1;                    // 8 Capture Event Flag
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union TZCBCFLG_REG {
    Uint16  all;
    struct  TZCBCFLG_BITS  bit;
};

struct TZOSTFLG_BITS {                  // bits description
    Uint16 OST1:1;                      // 0 Latched Status Flag for OST1 Trip Latch
    Uint16 OST2:1;                      // 1 Latched Status Flag for OST2 Trip Latch
    Uint16 OST3:1;                      // 2 Latched Status Flag for OST3 Trip Latch
    Uint16 OST4:1;                      // 3 Latched Status Flag for OST4 Trip Latch
    Uint16 OST5:1;                      // 4 Latched Status Flag for OST5 Trip Latch
    Uint16 OST6:1;                      // 5 Latched Status Flag for OST6 Trip Latch
    Uint16 DCAEVT1:1;                   // 6 Latched Status Flag for Digital Compare Output A Event 1
    Uint16 DCBEVT1:1;                   // 7 Latched Status Flag for Digital Compare Output B Event 1
    Uint16 CAPEVT:1;                    // 8 Capture Event Flag
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union TZOSTFLG_REG {
    Uint16  all;
    struct  TZOSTFLG_BITS  bit;
};

struct TZCLR_BITS {                     // bits description
    Uint16 INT:1;                       // 0 Global Interrupt Clear Flag
    Uint16 CBC:1;                       // 1 Cycle-By-Cycle Flag Clear
    Uint16 OST:1;                       // 2 One-Shot Flag Clear
    Uint16 DCAEVT1:1;                   // 3 DCAVET1 Flag Clear
    Uint16 DCAEVT2:1;                   // 4 DCAEVT2 Flag Clear
    Uint16 DCBEVT1:1;                   // 5 DCBEVT1 Flag Clear
    Uint16 DCBEVT2:1;                   // 6 DCBEVT2 Flag Clear
    Uint16 CAPEVT:1;                    // 7 Capture Event Clear
    Uint16 rsvd1:6;                     // 13:8 Reserved
    Uint16 CBCPULSE:2;                  // 15:14 Clear Pulse for CBC Trip Latch
};

union TZCLR_REG {
    Uint16  all;
    struct  TZCLR_BITS  bit;
};

struct TZCBCCLR_BITS {                  // bits description
    Uint16 CBC1:1;                      // 0 Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch
    Uint16 CBC2:1;                      // 1 Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch
    Uint16 CBC3:1;                      // 2 Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch
    Uint16 CBC4:1;                      // 3 Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch
    Uint16 CBC5:1;                      // 4 Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch
    Uint16 CBC6:1;                      // 5 Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch
    Uint16 DCAEVT2:1;                   // 6 Clear Flag forDCAEVT2 selected for CBC
    Uint16 DCBEVT2:1;                   // 7 Clear Flag for DCBEVT2 selected for CBC
    Uint16 CAPEVT:1;                    // 8 Clear Flag for CAPEVT selected for CBC
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union TZCBCCLR_REG {
    Uint16  all;
    struct  TZCBCCLR_BITS  bit;
};

struct TZOSTCLR_BITS {                  // bits description
    Uint16 OST1:1;                      // 0 Clear Flag for Oneshot (OST1) Trip Latch
    Uint16 OST2:1;                      // 1 Clear Flag for Oneshot (OST2) Trip Latch
    Uint16 OST3:1;                      // 2 Clear Flag for Oneshot (OST3) Trip Latch
    Uint16 OST4:1;                      // 3 Clear Flag for Oneshot (OST4) Trip Latch
    Uint16 OST5:1;                      // 4 Clear Flag for Oneshot (OST5) Trip Latch
    Uint16 OST6:1;                      // 5 Clear Flag for Oneshot (OST6) Trip Latch
    Uint16 DCAEVT1:1;                   // 6 Clear Flag for DCAEVT1 selected for OST
    Uint16 DCBEVT1:1;                   // 7 Clear Flag for DCBEVT1 selected for OST
    Uint16 CAPEVT:1;                    // 8 Clear Flag for CAPEVT selected for OST
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union TZOSTCLR_REG {
    Uint16  all;
    struct  TZOSTCLR_BITS  bit;
};

struct TZFRC_BITS {                     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CBC:1;                       // 1 Force Trip Zones Cycle By Cycle Event
    Uint16 OST:1;                       // 2 Force Trip Zones One Shot Event
    Uint16 DCAEVT1:1;                   // 3 Force Digital Compare A Event 1
    Uint16 DCAEVT2:1;                   // 4 Force Digital Compare A Event 2
    Uint16 DCBEVT1:1;                   // 5 Force Digital Compare B Event 1
    Uint16 DCBEVT2:1;                   // 6 Force Digital Compare B Event 2
    Uint16 CAPEVT:1;                    // 7 Force Capture Event
    Uint16 rsvd2:8;                     // 15:8 Reserved
};

union TZFRC_REG {
    Uint16  all;
    struct  TZFRC_BITS  bit;
};

struct TZTRIPOUTSEL_BITS {              // bits description
    Uint16 OST:1;                       // 0 OST TRIPOUT select
    Uint16 CBC:1;                       // 1 CBC TRIPOUT select
    Uint16 TZ1:1;                       // 2 TZ1 TRIPOUT select
    Uint16 TZ2:1;                       // 3 TZ2 TRIPOUT select
    Uint16 TZ3:1;                       // 4 TZ3 TRIPOUT select
    Uint16 TZ4:1;                       // 5 TZ4 TRIPOUT select
    Uint16 TZ5:1;                       // 6 TZ5 TRIPOUT select
    Uint16 TZ6:1;                       // 7 TZ6 TRIPOUT select
    Uint16 DCAEVT1:1;                   // 8 DCAEVT1.force TRIPOUT select
    Uint16 DCAEVT2:1;                   // 9 DCAEVT2.force TRIPOUT select
    Uint16 DCBEVT1:1;                   // 10 DCBEVT1.force TRIPOUT select
    Uint16 DCBEVT2:1;                   // 11 DCBEVT2.force TRIPOUT select
    Uint16 CAPEVT:1;                    // 12 CAPEVT TRIPOUT select
    Uint16 rsvd1:3;                     // 15:13 Reserved
};

union TZTRIPOUTSEL_REG {
    Uint16  all;
    struct  TZTRIPOUTSEL_BITS  bit;
};

struct ETSEL_BITS {                     // bits description
    Uint16 INTSEL:3;                    // 2:0 EPWMxINTn Select
    Uint16 INTEN:1;                     // 3 EPWMxINTn Enable
    Uint16 SOCASELCMP:1;                // 4 EPWMxSOCA Compare Select
    Uint16 SOCBSELCMP:1;                // 5 EPWMxSOCB Compare Select
    Uint16 INTSELCMP:1;                 // 6 EPWMxINT Compare Select
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 SOCASEL:3;                   // 10:8 Start of Conversion A Select
    Uint16 SOCAEN:1;                    // 11 Start of Conversion A Enable
    Uint16 SOCBSEL:3;                   // 14:12 Start of Conversion B Select
    Uint16 SOCBEN:1;                    // 15 Start of Conversion B Enable
};

union ETSEL_REG {
    Uint16  all;
    struct  ETSEL_BITS  bit;
};

struct ETPS_BITS {                      // bits description
    Uint16 INTPRD:2;                    // 1:0 EPWMxINTn Period Select
    Uint16 INTCNT:2;                    // 3:2 EPWMxINTn Counter Register
    Uint16 INTPSSEL:1;                  // 4 EPWMxINTn Pre-Scale Selection Bits
    Uint16 SOCPSSEL:1;                  // 5 EPWMxSOC A/B  Pre-Scale Selection Bits
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 SOCAPRD:2;                   // 9:8 EPWMxSOCA Period Select
    Uint16 SOCACNT:2;                   // 11:10 EPWMxSOCA Counter Register
    Uint16 SOCBPRD:2;                   // 13:12 EPWMxSOCB Period Select
    Uint16 SOCBCNT:2;                   // 15:14 EPWMxSOCB Counter
};

union ETPS_REG {
    Uint16  all;
    struct  ETPS_BITS  bit;
};

struct ETFLG_BITS {                     // bits description
    Uint16 INT:1;                       // 0 EPWMxINTn Flag
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 EPWMxSOCA Flag
    Uint16 SOCB:1;                      // 3 EPWMxSOCB Flag
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETFLG_REG {
    Uint16  all;
    struct  ETFLG_BITS  bit;
};

struct ETCLR_BITS {                     // bits description
    Uint16 INT:1;                       // 0 EPWMxINTn Clear
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 EPWMxSOCA Clear
    Uint16 SOCB:1;                      // 3 EPWMxSOCB Clear
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETCLR_REG {
    Uint16  all;
    struct  ETCLR_BITS  bit;
};

struct ETFRC_BITS {                     // bits description
    Uint16 INT:1;                       // 0 EPWMxINTn Force
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 SOCA:1;                      // 2 EPWMxSOCA Force
    Uint16 SOCB:1;                      // 3 EPWMxSOCB Force
    Uint16 rsvd2:12;                    // 15:4 Reserved
};

union ETFRC_REG {
    Uint16  all;
    struct  ETFRC_BITS  bit;
};

struct ETINTPS_BITS {                   // bits description
    Uint16 INTPRD2:4;                   // 3:0 EPWMxINTn Period Select
    Uint16 INTCNT2:4;                   // 7:4 EPWMxINTn Counter Register
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union ETINTPS_REG {
    Uint16  all;
    struct  ETINTPS_BITS  bit;
};

struct ETSOCPS_BITS {                   // bits description
    Uint16 SOCAPRD2:4;                  // 3:0 EPWMxSOCA Period Select
    Uint16 SOCACNT2:4;                  // 7:4 EPWMxSOCA Counter Register
    Uint16 SOCBPRD2:4;                  // 11:8 EPWMxSOCB Period Select
    Uint16 SOCBCNT2:4;                  // 15:12 EPWMxSOCB Counter Register
};

union ETSOCPS_REG {
    Uint16  all;
    struct  ETSOCPS_BITS  bit;
};

struct ETCNTINITCTL_BITS {              // bits description
    Uint16 rsvd1:10;                    // 9:0 Reserved
    Uint16 INTINITFRC:1;                // 10 EPWMxINT Counter Initialization Force
    Uint16 SOCAINITFRC:1;               // 11 EPWMxSOCA Counter Initialization Force
    Uint16 SOCBINITFRC:1;               // 12 EPWMxSOCB Counter Initialization Force
    Uint16 INTINITEN:1;                 // 13 EPWMxINT Counter Initialization Enable
    Uint16 SOCAINITEN:1;                // 14 EPWMxSOCA Counter Initialization Enable
    Uint16 SOCBINITEN:1;                // 15 EPWMxSOCB Counter Initialization Enable
};

union ETCNTINITCTL_REG {
    Uint16  all;
    struct  ETCNTINITCTL_BITS  bit;
};

struct ETCNTINIT_BITS {                 // bits description
    Uint16 INTINIT:4;                   // 3:0 EPWMxINT Counter Initialization Bits
    Uint16 SOCAINIT:4;                  // 7:4 EPWMxSOCA Counter Initialization Bits
    Uint16 SOCBINIT:4;                  // 11:8 EPWMxSOCB Counter Initialization Bits
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union ETCNTINIT_REG {
    Uint16  all;
    struct  ETCNTINIT_BITS  bit;
};

struct ETINTMIXEN_BITS {                // bits description
    Uint16 ZRO:1;                       // 0 Zero match enable to ETINTMIX
    Uint16 PRD:1;                       // 1 Period match enable to ETINTMIX
    Uint16 CAU:1;                       // 2 CMPA up-count match enable to ETINTMIX
    Uint16 CAD:1;                       // 3 CMPA down-count match enable to ETINTMIX
    Uint16 CBU:1;                       // 4 CMPB up-count match enable to ETINTMIX
    Uint16 CBD:1;                       // 5 CMPB down-count match enable to ETINTMIX
    Uint16 CCU:1;                       // 6 CMPC up-count match enable to ETINTMIX
    Uint16 CCD:1;                       // 7 CMPC down-count match enable to ETINTMIX
    Uint16 CDU:1;                       // 8 CMPD up-count match enable to ETINTMIX
    Uint16 CDD:1;                       // 9 CMPD down-count match enable to ETINTMIX
    Uint16 DCAEVT1:1;                   // 10 DCAEVT1.inter enable to ETINTMIX
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union ETINTMIXEN_REG {
    Uint16  all;
    struct  ETINTMIXEN_BITS  bit;
};

struct ETSOCAMIXEN_BITS {               // bits description
    Uint16 ZRO:1;                       // 0 Zero match enable to ETSOCAMIX
    Uint16 PRD:1;                       // 1 Period match enable to ETSOCAMIX
    Uint16 CAU:1;                       // 2 CMPA up-count match enable to ETSOCAMIX
    Uint16 CAD:1;                       // 3 CMPA down-count match enable to ETSOCAMIX
    Uint16 CBU:1;                       // 4 CMPB up-count match enable to ETSOCAMIX
    Uint16 CBD:1;                       // 5 CMPB down-count match enable to ETSOCAMIX
    Uint16 CCU:1;                       // 6 CMPC up-count match enable to ETSOCAMIX
    Uint16 CCD:1;                       // 7 CMPC down-count match enable to ETSOCAMIX
    Uint16 CDU:1;                       // 8 CMPD up-count match enable to ETSOCAMIX
    Uint16 CDD:1;                       // 9 CMPD down-count match enable to ETSOCAMIX
    Uint16 DCAEVT1:1;                   // 10 DCAEVT1.inter enable to ETSOCAMIX
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union ETSOCAMIXEN_REG {
    Uint16  all;
    struct  ETSOCAMIXEN_BITS  bit;
};

struct ETSOCBMIXEN_BITS {               // bits description
    Uint16 ZRO:1;                       // 0 Zero match enable to ETSOCBMIX
    Uint16 PRD:1;                       // 1 Period match enable to ETSOCBMIX
    Uint16 CAU:1;                       // 2 CMPA up-count match enable to ETSOCBMIX
    Uint16 CAD:1;                       // 3 CMPA down-count match enable to ETSOCBMIX
    Uint16 CBU:1;                       // 4 CMPB up-count match enable to ETSOCBMIX
    Uint16 CBD:1;                       // 5 CMPB down-count match enable to ETSOCBMIX
    Uint16 CCU:1;                       // 6 CMPC up-count match enable to ETSOCBMIX
    Uint16 CCD:1;                       // 7 CMPC down-count match enable to ETSOCBMIX
    Uint16 CDU:1;                       // 8 CMPD up-count match enable to ETSOCBMIX
    Uint16 CDD:1;                       // 9 CMPD down-count match enable to ETSOCBMIX
    Uint16 DCBEVT1:1;                   // 10 DCBEVT1.inter enable to ETSOCBMIX
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union ETSOCBMIXEN_REG {
    Uint16  all;
    struct  ETSOCBMIXEN_BITS  bit;
};

struct DCTRIPSEL_BITS {                 // bits description
    Uint16 DCAHCOMPSEL:4;               // 3:0 Digital Compare A High COMP Input Select
    Uint16 DCALCOMPSEL:4;               // 7:4 Digital Compare A Low COMP Input Select
    Uint16 DCBHCOMPSEL:4;               // 11:8 Digital Compare B High COMP Input Select
    Uint16 DCBLCOMPSEL:4;               // 15:12 Digital Compare B Low COMP Input Select
};

union DCTRIPSEL_REG {
    Uint16  all;
    struct  DCTRIPSEL_BITS  bit;
};

struct DCACTL_BITS {                    // bits description
    Uint16 EVT1SRCSEL:1;                // 0 DCAEVT1 Source Signal
    Uint16 EVT1FRCSYNCSEL:1;            // 1 DCAEVT1 Force Sync Signal
    Uint16 EVT1SOCE:1;                  // 2 DCAEVT1 SOC Enable
    Uint16 EVT1SYNCE:1;                 // 3 DCAEVT1 SYNC Enable
    Uint16 EVT1LATSEL:1;                // 4 DCAEVT1 Latched signal select
    Uint16 EVT1LATCLRSEL:2;             // 6:5 DCAEVT1 Latched clear source select
    Uint16 EVT1LAT:1;                   // 7 Indicates the status of DCAEVT1LAT signal.
    Uint16 EVT2SRCSEL:1;                // 8 DCAEVT2 Source Signal
    Uint16 EVT2FRCSYNCSEL:1;            // 9 DCAEVT2 Force Sync Signal
    Uint16 rsvd1:2;                     // 11:10 Reserved
    Uint16 EVT2LATSEL:1;                // 12 DCAEVT2 Latched signal select
    Uint16 EVT2LATCLRSEL:2;             // 14:13 DCAEVT2 Latched clear source select
    Uint16 EVT2LAT:1;                   // 15 Indicates the status of DCAEVT2LAT signal.
};

union DCACTL_REG {
    Uint16  all;
    struct  DCACTL_BITS  bit;
};

struct DCBCTL_BITS {                    // bits description
    Uint16 EVT1SRCSEL:1;                // 0 DCBEVT1 Source Signal
    Uint16 EVT1FRCSYNCSEL:1;            // 1 DCBEVT1 Force Sync Signal
    Uint16 EVT1SOCE:1;                  // 2 DCBEVT1 SOC Enable
    Uint16 EVT1SYNCE:1;                 // 3 DCBEVT1 SYNC Enable
    Uint16 EVT1LATSEL:1;                // 4 DCBEVT1 Latched signal select
    Uint16 EVT1LATCLRSEL:2;             // 6:5 DCBEVT1 Latched clear source select
    Uint16 EVT1LAT:1;                   // 7 Indicates the status of DCBEVT1LAT signal.
    Uint16 EVT2SRCSEL:1;                // 8 DCBEVT2 Source Signal
    Uint16 EVT2FRCSYNCSEL:1;            // 9 DCBEVT2 Force Sync Signal
    Uint16 rsvd1:2;                     // 11:10 Reserved
    Uint16 EVT2LATSEL:1;                // 12 DCBEVT2 Latched signal select
    Uint16 EVT2LATCLRSEL:2;             // 14:13 DCBEVT2 Latched clear source select
    Uint16 EVT2LAT:1;                   // 15 Indicates the status of DCBEVT2LAT signal.
};

union DCBCTL_REG {
    Uint16  all;
    struct  DCBCTL_BITS  bit;
};

struct DCFCTL_BITS {                    // bits description
    Uint16 SRCSEL:2;                    // 1:0 Filter Block Signal Source Select
    Uint16 BLANKE:1;                    // 2 Blanking Enable/Disable
    Uint16 BLANKINV:1;                  // 3 Blanking Window Inversion
    Uint16 PULSESEL:2;                  // 5:4 Pulse Select for Blanking & Capture Alignment
    Uint16 EDGEFILTSEL:1;               // 6 Edge Filter Select
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 EDGEMODE:2;                  // 9:8 Edge Mode
    Uint16 EDGECOUNT:3;                 // 12:10 Edge Count
    Uint16 EDGESTATUS:3;                // 15:13 Edge Status
};

union DCFCTL_REG {
    Uint16  all;
    struct  DCFCTL_BITS  bit;
};

struct DCCAPCTL_BITS {                  // bits description
    Uint16 CAPE:1;                      // 0 Counter Capture Enable
    Uint16 SHDWMODE:1;                  // 1 Counter Capture Mode
    Uint16 rsvd1:11;                    // 12:2 Reserved
    Uint16 CAPSTS:1;                    // 13 Latched Status Flag for Capture Event
    Uint16 CAPCLR:1;                    // 14 DC Capture Latched Status Clear Flag
    Uint16 CAPMODE:1;                   // 15 Counter Capture Mode
};

union DCCAPCTL_REG {
    Uint16  all;
    struct  DCCAPCTL_BITS  bit;
};

struct BLANKPULSEMIXSEL_BITS {          // bits description
    Uint16 ZRO:1;                       // 0 Zero match enable to BLANKPULSEMIX
    Uint16 PRD:1;                       // 1 Period match enable to BLANKPULSEMIX
    Uint16 CAU:1;                       // 2 CMPA up-count match enable to BLANKPULSEMIX
    Uint16 CAD:1;                       // 3 CMPA down-count match enable to BLANKPULSEMIX
    Uint16 CBU:1;                       // 4 CMPB up-count match enable to BLANKPULSEMIX
    Uint16 CBD:1;                       // 5 CMPB down-count match enable to BLANKPULSEMIX
    Uint16 CCU:1;                       // 6 CMPC up-count match enable to BLANKPULSEMIX
    Uint16 CCD:1;                       // 7 CMPC down-count match enable to BLANKPULSEMIX
    Uint16 CDU:1;                       // 8 CMPD up-count match enable to BLANKPULSEMIX
    Uint16 CDD:1;                       // 9 CMPD down-count match enable to BLANKPULSEMIX
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union BLANKPULSEMIXSEL_REG {
    Uint16  all;
    struct  BLANKPULSEMIXSEL_BITS  bit;
};

struct DCCAPMIXSEL_BITS {               // bits description
    Uint16 ZRO:1;                       // 0 Zero match enable to DCCAPMIX
    Uint16 PRD:1;                       // 1 Period match enable to DCCAPMIX
    Uint16 CAU:1;                       // 2 CMPA up-count match enable to DCCAPMIX
    Uint16 CAD:1;                       // 3 CMPA down-count match enable to DCCAPMIX
    Uint16 CBU:1;                       // 4 CMPB up-count match enable to DCCAPMIX
    Uint16 CBD:1;                       // 5 CMPB down-count match enable to DCCAPMIX
    Uint16 CCU:1;                       // 6 CMPC up-count match enable to DCCAPMIX
    Uint16 CCD:1;                       // 7 CMPC down-count match enable to DCCAPMIX
    Uint16 CDU:1;                       // 8 CMPD up-count match enable to DCCAPMIX
    Uint16 CDD:1;                       // 9 CMPD down-count match enable to DCCAPMIX
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union DCCAPMIXSEL_REG {
    Uint16  all;
    struct  DCCAPMIXSEL_BITS  bit;
};

struct DCAHTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCAH Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCAH Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCAH Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCAH Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCAH Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCAH Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCAH Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCAH Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCAH Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCAH Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCAH Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCAH Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCAH Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCAH Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCAHTRIPSEL_REG {
    Uint16  all;
    struct  DCAHTRIPSEL_BITS  bit;
};

struct DCALTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCAL Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCAL Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCAL Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCAL Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCAL Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCAL Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCAL Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCAL Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCAL Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCAL Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCAL Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCAL Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCAL Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCAL Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCALTRIPSEL_REG {
    Uint16  all;
    struct  DCALTRIPSEL_BITS  bit;
};

struct DCBHTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCBH Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCBH Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCBH Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCBH Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCBH Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCBH Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCBH Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCBH Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCBH Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCBH Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCBH Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCBH Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCBH Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCBH Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCBHTRIPSEL_REG {
    Uint16  all;
    struct  DCBHTRIPSEL_BITS  bit;
};

struct DCBLTRIPSEL_BITS {               // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to DCBL Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to DCBL Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to DCBL Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to DCBL Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to DCBL Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to DCBL Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to DCBL Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to DCBL Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to DCBL Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to DCBL Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to DCBL Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to DCBL Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to DCBL Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to DCBL Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union DCBLTRIPSEL_REG {
    Uint16  all;
    struct  DCBLTRIPSEL_BITS  bit;
};

struct CAPCTL_BITS {                    // bits description
    Uint16 SRCSEL:1;                    // 0 Capture Logic Input Selection
    Uint16 CAPGATEPOL:2;                // 2:1 Polarity selection for Capture Gate input
    Uint16 CAPINPOL:1;                  // 3 Polarity selection for Capture input
    Uint16 PULSECTL:1;                  // 4 Polarity selection for Capture input
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 FRCLOAD:1;                   // 8 Capture event force load
    Uint16 rsvd2:7;                     // 15:9 Reserved
};

union CAPCTL_REG {
    Uint16  all;
    struct  CAPCTL_BITS  bit;
};

struct CAPGATETRIPSEL_BITS {            // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to CAPGATE Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to CAPGATE Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to CAPGATE Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to CAPGATE Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to CAPGATE Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to CAPGATE Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to CAPGATE Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to CAPGATE Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to CAPGATE Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to CAPGATE Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to CAPGATE Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to CAPGATE Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to CAPGATE Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to CAPGATE Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union CAPGATETRIPSEL_REG {
    Uint16  all;
    struct  CAPGATETRIPSEL_BITS  bit;
};

struct CAPINTRIPSEL_BITS {              // bits description
    Uint16 TRIPINPUT1:1;                // 0 Trip Input 1 Select to CAPIN Mux
    Uint16 TRIPINPUT2:1;                // 1 Trip Input 2 Select to CAPIN Mux
    Uint16 TRIPINPUT3:1;                // 2 Trip Input 3 Select to CAPIN Mux
    Uint16 TRIPINPUT4:1;                // 3 Trip Input 4 Select to CAPIN Mux
    Uint16 TRIPINPUT5:1;                // 4 Trip Input 5 Select to CAPIN Mux
    Uint16 TRIPINPUT6:1;                // 5 Trip Input 6 Select to CAPIN Mux
    Uint16 TRIPINPUT7:1;                // 6 Trip Input 7 Select to CAPIN Mux
    Uint16 TRIPINPUT8:1;                // 7 Trip Input 8 Select to CAPIN Mux
    Uint16 TRIPINPUT9:1;                // 8 Trip Input 9 Select to CAPIN Mux
    Uint16 TRIPINPUT10:1;               // 9 Trip Input 10 Select to CAPIN Mux
    Uint16 TRIPINPUT11:1;               // 10 Trip Input 11 Select to CAPIN Mux
    Uint16 TRIPINPUT12:1;               // 11 Trip Input 12 Select to CAPIN Mux
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 TRIPINPUT14:1;               // 13 Trip Input 14 Select to CAPIN Mux
    Uint16 TRIPINPUT15:1;               // 14 Trip Input 15 Select to CAPIN Mux
    Uint16 rsvd2:1;                     // 15 Reserved
};

union CAPINTRIPSEL_REG {
    Uint16  all;
    struct  CAPINTRIPSEL_BITS  bit;
};

struct CAPTRIPSEL_BITS {                // bits description
    Uint16 CAPINCOMPSEL:4;              // 3:0 CAPIN Comparator Input Select
    Uint16 CAPGATECOMPSEL:4;            // 7:4 CAPGATE Comparator COMP Input Select
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union CAPTRIPSEL_REG {
    Uint16  all;
    struct  CAPTRIPSEL_BITS  bit;
};

struct EPWMLOCK_BITS {                  // bits description
    Uint16 HRLOCK:1;                    // 0 HRPWM Register Set Lock
    Uint16 GLLOCK:1;                    // 1 Global Load Register Set Lock
    Uint16 TZCFGLOCK:1;                 // 2 TripZone Register Set Lock
    Uint16 TZCLRLOCK:1;                 // 3 TripZone Clear Register Set Lock
    Uint16 DCLOCK:1;                    // 4 Digital Compare Register Set Lock
    Uint16 rsvd1:11;                    // 15:5 Reserved
    Uint16 KEY:16;                      // 31:16 Key to write to this register
};

union EPWMLOCK_REG {
    Uint32  all;
    struct  EPWMLOCK_BITS  bit;
};

struct EPWM_REGS {
    union   TBCTL_REG                        TBCTL;                        // Time Base Control Register
    union   TBCTL2_REG                       TBCTL2;                       // Time Base Control Register 2
    Uint16                                   rsvd1;                        // Reserved
    union   EPWMSYNCINSEL_REG                EPWMSYNCINSEL;                // EPWMxSYNCIN Source Select Register
    Uint16                                   TBCTR;                        // Time Base Counter Register
    union   TBSTS_REG                        TBSTS;                        // Time Base Status Register
    union   EPWMSYNCOUTEN_REG                EPWMSYNCOUTEN;                // EPWMxSYNCOUT Source Enable Register
    union   TBCTL3_REG                       TBCTL3;                       // Time Base Control Register 3
    union   CMPCTL_REG                       CMPCTL;                       // Counter Compare Control Register
    union   CMPCTL2_REG                      CMPCTL2;                      // Counter Compare Control Register 2
    Uint16                                   rsvd2[2];                     // Reserved
    union   DBCTL_REG                        DBCTL;                        // Dead-Band Generator Control Register
    union   DBCTL2_REG                       DBCTL2;                       // Dead-Band Generator Control Register 2
    Uint16                                   rsvd3[2];                     // Reserved
    union   AQCTL_REG                        AQCTL;                        // Action Qualifier Control Register
    union   AQTSRCSEL_REG                    AQTSRCSEL;                    // Action Qualifier Trigger Event Source Select Register
    Uint16                                   rsvd4[2];                     // Reserved
    union   PCCTL_REG                        PCCTL;                        // PWM Chopper Control Register
    Uint16                                   rsvd5[3];                     // Reserved
    union   VCAPCTL_REG                      VCAPCTL;                      // Valley Capture Control Register
    union   VCNTCFG_REG                      VCNTCFG;                      // Valley Counter Config Register
    Uint16                                   rsvd6[6];                     // Reserved
    union   HRCNFG_REG                       HRCNFG;                       // HRPWM Configuration Register
    Uint16                                   rsvd7[6];                     // Reserved
    union   HRCNFG2_REG                      HRCNFG2;                      // HRPWM Configuration 2 Register
    Uint16                                   rsvd8[5];                     // Reserved
    union   HRPCTL_REG                       HRPCTL;                       // High Resolution Period Control Register
    union   TRREM_REG                        TRREM;                        // HRPWM High Resolution Remainder Register
    Uint16                                   rsvd9[5];                     // Reserved
    union   GLDCTL_REG                       GLDCTL;                       // Global PWM Load Control Register
    union   GLDCFG_REG                       GLDCFG;                       // Global PWM Load Config Register
    Uint16                                   rsvd10[2];                    // Reserved
    union   EPWMXLINK_REG                    EPWMXLINK;                    // EPWMx Link Register
    union   EPWMXLINK2_REG                   EPWMXLINK2;                   // EPWMx Link 2 Register
    Uint16                                   rsvd11[4];                    // Reserved
    union   AQCTLA_REG                       AQCTLA;                       // Action Qualifier Control Register For Output A
    union   AQCTLA2_REG                      AQCTLA2;                      // Additional Action Qualifier Control Register For Output A
    union   AQCTLB_REG                       AQCTLB;                       // Action Qualifier Control Register For Output B
    union   AQCTLB2_REG                      AQCTLB2;                      // Additional Action Qualifier Control Register For Output B
    Uint16                                   rsvd12[3];                    // Reserved
    union   AQSFRC_REG                       AQSFRC;                       // Action Qualifier Software Force Register
    Uint16                                   rsvd13;                       // Reserved
    union   AQCSFRC_REG                      AQCSFRC;                      // Action Qualifier Continuous S/W Force Register
    Uint16                                   rsvd14[6];                    // Reserved
    union   DBREDHR_REG                      DBREDHR;                      // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   DBRED_REG                        DBRED;                        // Dead-Band Generator Rising Edge Delay High Resolution Mirror Register
    union   DBFEDHR_REG                      DBFEDHR;                      // Dead-Band Generator Falling Edge Delay High Resolution Register
    union   DBFED_REG                        DBFED;                        // Dead-Band Generator Falling Edge Delay Count Register
    Uint16                                   rsvd15[12];                   // Reserved
    union   TBPHS_REG                        TBPHS;                        // Time Base Phase High
    Uint16                                   TBPRDHR;                      // Time Base Period High Resolution Register
    Uint16                                   TBPRD;                        // Time Base Period Register
    Uint16                                   rsvd16[6];                    // Reserved
    union   CMPA_REG                         CMPA;                         // Counter Compare A Register
    union   CMPB_REG                         CMPB;                         // Compare B Register
    Uint16                                   rsvd17;                       // Reserved
    Uint16                                   CMPC;                         // Counter Compare C Register
    Uint16                                   rsvd18;                       // Reserved
    Uint16                                   CMPD;                         // Counter Compare D Register
    Uint16                                   rsvd19[2];                    // Reserved
    union   GLDCTL2_REG                      GLDCTL2;                      // Global PWM Load Control Register 2
    Uint16                                   rsvd20[2];                    // Reserved
    Uint16                                   SWVDELVAL;                    // Software Valley Mode Delay Register
    Uint16                                   rsvd21[8];                    // Reserved
    union   TZSEL_REG                        TZSEL;                        // Trip Zone Select Register
    union   TZSEL2_REG                       TZSEL2;                       // Trip Zone Select Register 2
    union   TZDCSEL_REG                      TZDCSEL;                      // Trip Zone Digital Comparator Select Register
    Uint16                                   rsvd22;                       // Reserved
    union   TZCTL_REG                        TZCTL;                        // Trip Zone Control Register
    union   TZCTL2_REG                       TZCTL2;                       // Additional Trip Zone Control Register
    union   TZCTLDCA_REG                     TZCTLDCA;                     // Trip Zone Control Register Digital Compare A
    union   TZCTLDCB_REG                     TZCTLDCB;                     // Trip Zone Control Register Digital Compare B
    Uint16                                   rsvd23[5];                    // Reserved
    union   TZEINT_REG                       TZEINT;                       // Trip Zone Enable Interrupt Register
    Uint16                                   rsvd24[5];                    // Reserved
    union   TZFLG_REG                        TZFLG;                        // Trip Zone Flag Register
    union   TZCBCFLG_REG                     TZCBCFLG;                     // Trip Zone CBC Flag Register
    union   TZOSTFLG_REG                     TZOSTFLG;                     // Trip Zone OST Flag Register
    Uint16                                   rsvd25;                       // Reserved
    union   TZCLR_REG                        TZCLR;                        // Trip Zone Clear Register
    union   TZCBCCLR_REG                     TZCBCCLR;                     // Trip Zone CBC Clear Register
    union   TZOSTCLR_REG                     TZOSTCLR;                     // Trip Zone OST Clear Register
    Uint16                                   rsvd26;                       // Reserved
    union   TZFRC_REG                        TZFRC;                        // Trip Zone Force Register
    Uint16                                   rsvd27;                       // Reserved
    union   TZTRIPOUTSEL_REG                 TZTRIPOUTSEL;                 // Trip Out Select Register
    Uint16                                   rsvd28[6];                    // Reserved
    union   ETSEL_REG                        ETSEL;                        // Event Trigger Selection Register
    Uint16                                   rsvd29;                       // Reserved
    union   ETPS_REG                         ETPS;                         // Event Trigger Pre-Scale Register
    Uint16                                   rsvd30;                       // Reserved
    union   ETFLG_REG                        ETFLG;                        // Event Trigger Flag Register
    Uint16                                   rsvd31;                       // Reserved
    union   ETCLR_REG                        ETCLR;                        // Event Trigger Clear Register
    Uint16                                   rsvd32;                       // Reserved
    union   ETFRC_REG                        ETFRC;                        // Event Trigger Force Register
    Uint16                                   rsvd33;                       // Reserved
    union   ETINTPS_REG                      ETINTPS;                      // Event-Trigger Interrupt Pre-Scale Register
    Uint16                                   rsvd34;                       // Reserved
    union   ETSOCPS_REG                      ETSOCPS;                      // Event-Trigger SOC Pre-Scale Register
    Uint16                                   rsvd35;                       // Reserved
    union   ETCNTINITCTL_REG                 ETCNTINITCTL;                 // Event-Trigger Counter Initialization Control Register
    Uint16                                   rsvd36;                       // Reserved
    union   ETCNTINIT_REG                    ETCNTINIT;                    // Event-Trigger Counter Initialization Register
    Uint16                                   rsvd37;                       // Reserved
    union   ETINTMIXEN_REG                   ETINTMIXEN;                   // Event-Trigger Mixed INT Selection
    Uint16                                   rsvd38;                       // Reserved
    union   ETSOCAMIXEN_REG                  ETSOCAMIXEN;                  // Event-Trigger Mixed SOCA Selection
    Uint16                                   rsvd39;                       // Reserved
    union   ETSOCBMIXEN_REG                  ETSOCBMIXEN;                  // Event-Trigger Mixed SOCB Selection
    Uint16                                   rsvd40[5];                    // Reserved
    union   DCTRIPSEL_REG                    DCTRIPSEL;                    // Digital Compare Trip Select Register
    Uint16                                   rsvd41[2];                    // Reserved
    union   DCACTL_REG                       DCACTL;                       // Digital Compare A Control Register
    union   DCBCTL_REG                       DCBCTL;                       // Digital Compare B Control Register
    Uint16                                   rsvd42[2];                    // Reserved
    union   DCFCTL_REG                       DCFCTL;                       // Digital Compare Filter Control Register
    union   DCCAPCTL_REG                     DCCAPCTL;                     // Digital Compare Capture Control Register
    Uint16                                   DCFOFFSET;                    // Digital Compare Filter Offset Register
    Uint16                                   DCFOFFSETCNT;                 // Digital Compare Filter Offset Counter Register
    Uint16                                   DCFWINDOW;                    // Digital Compare Filter Window Register
    Uint16                                   DCFWINDOWCNT;                 // Digital Compare Filter Window Counter Register
    union   BLANKPULSEMIXSEL_REG             BLANKPULSEMIXSEL;             // Blanking window trigger pulse select register
    union   DCCAPMIXSEL_REG                  DCCAPMIXSEL;                  // Capture Event pulse select register
    Uint16                                   DCCAP;                        // Digital Compare Counter Capture Register
    Uint16                                   rsvd43[2];                    // Reserved
    union   DCAHTRIPSEL_REG                  DCAHTRIPSEL;                  // Digital Compare AH Trip Select
    union   DCALTRIPSEL_REG                  DCALTRIPSEL;                  // Digital Compare AL Trip Select
    union   DCBHTRIPSEL_REG                  DCBHTRIPSEL;                  // Digital Compare BH Trip Select
    union   DCBLTRIPSEL_REG                  DCBLTRIPSEL;                  // Digital Compare BL Trip Select
    union   CAPCTL_REG                       CAPCTL;                       // Event Capture Control Register
    union   CAPGATETRIPSEL_REG               CAPGATETRIPSEL;               // Event Capture Gate Trip input select
    union   CAPINTRIPSEL_REG                 CAPINTRIPSEL;                 // Event Capture Trip input select
    union   CAPTRIPSEL_REG                   CAPTRIPSEL;                   // Event Capture Signal Select
    Uint16                                   rsvd44[32];                   // Reserved
    union   EPWMLOCK_REG                     EPWMLOCK;                     // EPWM Lock Register
    Uint16                                   rsvd45;                       // Reserved
    Uint16                                   HWVDELVAL;                    // Hardware Valley Mode Delay Register
    Uint16                                   VCNTVAL;                      // Hardware Valley Counter Register
};

struct XCMPCTL1_BITS {                  // bits description
    Uint16 XCMPEN:1;                    // 0 XCMP Compare Register Operation Enable
    Uint16 XCMPSPLIT:1;                 // 1 XCMP Register Allocation Options
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 XCMPA_ALLOC:4;               // 7:4 XCMPn register allocation for CMPA
    Uint16 XCMPB_ALLOC:4;               // 11:8 XCMPn register allocation for CMPB
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union XCMPCTL1_REG {
    Uint32  all;
    struct  XCMPCTL1_BITS  bit;
};

struct XLOADCTL_BITS {                  // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 LOADMODE:1;                  // 2 Load mode selection for Shadow registers
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 SHDWLEVEL:2;                 // 5:4 Shadow Register Level Allocation Options
    Uint16 rsvd3:2;                     // 7:6 Reserved
    Uint16 SHDWBUFPTR_LOADONCE:2;       // 9:8 Register Load event count
    Uint16 SHDWBUFPTR_LOADMULTIPLE:2;   // 11:10 Register Load event count
    Uint16 rsvd4:4;                     // 15:12 Reserved
    Uint16 RPTBUF2PRD:3;                // 18:16 Repeat Count Shadow Buffer 2
    Uint16 rsvd5:1;                     // 19 Reserved
    Uint16 RPTBUF2CNT:3;                // 22:20 Repeat Count Status Shadow Buffer 2
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 RPTBUF3PRD:3;                // 26:24 Repeat Count Shadow Buffer 3
    Uint16 rsvd7:1;                     // 27 Reserved
    Uint16 RPTBUF3CNT:3;                // 30:28 Repeat Count Status Shadow Buffer 3
    Uint16 rsvd8:1;                     // 31 Reserved
};

union XLOADCTL_REG {
    Uint32  all;
    struct  XLOADCTL_BITS  bit;
};

struct XLOAD_BITS {                     // bits description
    Uint16 STARTLD:1;                   // 0 Enable register loading of shadow buffers
    Uint16 FRCLD:1;                     // 1 Force register loading of shadow buffers
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union XLOAD_REG {
    Uint32  all;
    struct  XLOAD_BITS  bit;
};

struct EPWMXLINKXLOAD_BITS {            // bits description
    Uint16 XLOADLINK:5;                 // 4:0 XLOAD  Link Register
    Uint16 rsvd1:11;                    // 15:5 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWMXLINKXLOAD_REG {
    Uint32  all;
    struct  EPWMXLINKXLOAD_BITS  bit;
};

struct XREGSHDW1STS_BITS {              // bits description
    Uint16 XCMP1_SHDW1FULL:1;           // 0 XCMP1_SHDW1 register full Status flag
    Uint16 XCMP2_SHDW1FULL:1;           // 1 XCMP2_SHDW1 register full Status flag
    Uint16 XCMP3_SHDW1FULL:1;           // 2 XCMP3_SHDW1 register full Status flag
    Uint16 XCMP4_SHDW1FULL:1;           // 3 XCMP4_SHDW1 register full Status flag
    Uint16 XCMP5_SHDW1FULL:1;           // 4 XCMP5_SHDW1 register full Status flag
    Uint16 XCMP6_SHDW1FULL:1;           // 5 XCMP6_SHDW1 register full Status flag
    Uint16 XCMP7_SHDW1FULL:1;           // 6 XCMP7_SHDW1 register full Status flag
    Uint16 XCMP8_SHDW1FULL:1;           // 7 XCMP8_SHDW1 register full Status flag
    Uint16 XTBPRD_SHDW1FULL:1;          // 8 XTBPRD_SHDW1 register full Status flag:
    Uint16 CMPC_SHDW1FULL:1;            // 9 CMPC_SHDW1 register full Status flag:
    Uint16 CMPD_SHDW1FULL:1;            // 10 CMPD_SHDW1 register full Status flag:
    Uint16 XAQCTLA_SHDW1FULL:1;         // 11 XAQCTLA_SHDW1 register full Status flag:
    Uint16 XAQCTLB_SHDW1FULL:1;         // 12 XAQCTLB_SHDW1 register full Status flag:
    Uint16 XMAX_SHDW1FULL:1;            // 13 XMINMAX_SHDW1 register full Status flag:MAX field update
    Uint16 XMIN_SHDW1FULL:1;            // 14 XMINMAX_SHDW1 register full Status flag: MIN field update
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union XREGSHDW1STS_REG {
    Uint32  all;
    struct  XREGSHDW1STS_BITS  bit;
};

struct XREGSHDW2STS_BITS {              // bits description
    Uint16 XCMP1_SHDW2FULL:1;           // 0 XCMP1_SHDW2 register full Status flag
    Uint16 XCMP2_SHDW2FULL:1;           // 1 XCMP2_SHDW2 register full Status flag
    Uint16 XCMP3_SHDW2FULL:1;           // 2 XCMP3_SHDW2 register full Status flag
    Uint16 XCMP4_SHDW2FULL:1;           // 3 XCMP4_SHDW2 register full Status flag
    Uint16 XCMP5_SHDW2FULL:1;           // 4 XCMP5_SHDW2 register full Status flag
    Uint16 XCMP6_SHDW2FULL:1;           // 5 XCMP6_SHDW2 register full Status flag
    Uint16 XCMP7_SHDW2FULL:1;           // 6 XCMP7_SHDW2 register full Status flag
    Uint16 XCMP8_SHDW2FULL:1;           // 7 XCMP8_SHDW2 register full Status flag
    Uint16 XTBPRD_SHDW2FULL:1;          // 8 XTBPRD_SHDW2 register full Status flag:
    Uint16 CMPC_SHDW2FULL:1;            // 9 CMPC_SHDW2 register full Status flag:
    Uint16 CMPD_SHDW2FULL:1;            // 10 CMPD_SHDW2 register full Status flag:
    Uint16 XAQCTLA_SHDW2FULL:1;         // 11 XAQCTLA_SHDW2 register full Status flag:
    Uint16 XAQCTLB_SHDW2FULL:1;         // 12 XAQCTLB_SHDW2 register full Status flag:
    Uint16 XMAX_SHDW2FULL:1;            // 13 XMINMAX_SHDW2 register full Status flag:MAX field update
    Uint16 XMIN_SHDW2FULL:1;            // 14 XMINMAX_SHDW2 register full Status flag: MIN field update
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union XREGSHDW2STS_REG {
    Uint32  all;
    struct  XREGSHDW2STS_BITS  bit;
};

struct XREGSHDW3STS_BITS {              // bits description
    Uint16 XCMP1_SHDW3FULL:1;           // 0 XCMP1_SHDW3 register full Status flag
    Uint16 XCMP2_SHDW3FULL:1;           // 1 XCMP2_SHDW3 register full Status flag
    Uint16 XCMP3_SHDW3FULL:1;           // 2 XCMP3_SHDW3 register full Status flag
    Uint16 XCMP4_SHDW3FULL:1;           // 3 XCMP4_SHDW3 register full Status flag
    Uint16 XCMP5_SHDW3FULL:1;           // 4 XCMP5_SHDW3 register full Status flag
    Uint16 XCMP6_SHDW3FULL:1;           // 5 XCMP6_SHDW3 register full Status flag
    Uint16 XCMP7_SHDW3FULL:1;           // 6 XCMP7_SHDW3 register full Status flag
    Uint16 XCMP8_SHDW3FULL:1;           // 7 XCMP8_SHDW3 register full Status flag
    Uint16 XTBPRD_SHDW3FULL:1;          // 8 XTBPRD_SHDW3 register full Status flag:
    Uint16 CMPC_SHDW3FULL:1;            // 9 CMPC_SHDW3 register full Status flag:
    Uint16 CMPD_SHDW3FULL:1;            // 10 CMPD_SHDW3 register full Status flag:
    Uint16 XAQCTLA_SHDW3FULL:1;         // 11 XAQCTLA_SHDW3 register full Status flag:
    Uint16 XAQCTLB_SHDW3FULL:1;         // 12 XAQCTLB_SHDW3 register full Status flag:
    Uint16 XMAX_SHDW3FULL:1;            // 13 XMINMAX_SHDW3 register full Status flag:MAX field update
    Uint16 XMIN_SHDW3FULL:1;            // 14 XMINMAX_SHDW3 register full Status flag: MIN field update
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union XREGSHDW3STS_REG {
    Uint32  all;
    struct  XREGSHDW3STS_BITS  bit;
};

struct XCMP1_ACTIVE_BITS {              // bits description
    Uint16 XCMP1HR_ACTIVE:16;           // 15:0 Additional Compare 1 Active HR Register
    Uint16 XCMP1_ACTIVE:16;             // 31:16 Additional Compare 1 Active Register
};

union XCMP1_ACTIVE_REG {
    Uint32  all;
    struct  XCMP1_ACTIVE_BITS  bit;
};

struct XCMP2_ACTIVE_BITS {              // bits description
    Uint16 XCMP2HR_ACTIVE:16;           // 15:0 Additional Compare 2 Active HR Register
    Uint16 XCMP2_ACTIVE:16;             // 31:16 Additional Compare 2 Active Register
};

union XCMP2_ACTIVE_REG {
    Uint32  all;
    struct  XCMP2_ACTIVE_BITS  bit;
};

struct XCMP3_ACTIVE_BITS {              // bits description
    Uint16 XCMP3HR_ACTIVE:16;           // 15:0 Additional Compare 3 Active HR Register
    Uint16 XCMP3_ACTIVE:16;             // 31:16 Additional Compare 3 Active Register
};

union XCMP3_ACTIVE_REG {
    Uint32  all;
    struct  XCMP3_ACTIVE_BITS  bit;
};

struct XCMP4_ACTIVE_BITS {              // bits description
    Uint16 XCMP4HR_ACTIVE:16;           // 15:0 Additional Compare 4 Active HR Register
    Uint16 XCMP4_ACTIVE:16;             // 31:16 Additional Compare 4 Active Register
};

union XCMP4_ACTIVE_REG {
    Uint32  all;
    struct  XCMP4_ACTIVE_BITS  bit;
};

struct XCMP5_ACTIVE_BITS {              // bits description
    Uint16 XCMP5HR_ACTIVE:16;           // 15:0 Additional Compare 5 Active HR Register
    Uint16 XCMP5_ACTIVE:16;             // 31:16 Additional Compare 5 Active Register
};

union XCMP5_ACTIVE_REG {
    Uint32  all;
    struct  XCMP5_ACTIVE_BITS  bit;
};

struct XCMP6_ACTIVE_BITS {              // bits description
    Uint16 XCMP6HR_ACTIVE:16;           // 15:0 Additional Compare 6 Active HR Register
    Uint16 XCMP6_ACTIVE:16;             // 31:16 Additional Compare 6 Active Register
};

union XCMP6_ACTIVE_REG {
    Uint32  all;
    struct  XCMP6_ACTIVE_BITS  bit;
};

struct XCMP7_ACTIVE_BITS {              // bits description
    Uint16 XCMP7HR_ACTIVE:16;           // 15:0 Additional Compare 7 Active HR Register
    Uint16 XCMP7_ACTIVE:16;             // 31:16 Additional Compare 7 Active Register
};

union XCMP7_ACTIVE_REG {
    Uint32  all;
    struct  XCMP7_ACTIVE_BITS  bit;
};

struct XCMP8_ACTIVE_BITS {              // bits description
    Uint16 XCMP8HR_ACTIVE:16;           // 15:0 Additional Compare 8 Active HR Register
    Uint16 XCMP8_ACTIVE:16;             // 31:16 Additional Compare 8 Active Register
};

union XCMP8_ACTIVE_REG {
    Uint32  all;
    struct  XCMP8_ACTIVE_BITS  bit;
};

struct XTBPRD_ACTIVE_BITS {             // bits description
    Uint16 XTBPRDHR_ACTIVE:16;          // 15:0 Additional Time Base Period Active HR Register
    Uint16 XTBPRD_ACTIVE:16;            // 31:16 Additional Time Base Period Active Register
};

union XTBPRD_ACTIVE_REG {
    Uint32  all;
    struct  XTBPRD_ACTIVE_BITS  bit;
};

struct XAQCTLA_ACTIVE_BITS {            // bits description
    Uint16 XCMP1:2;                     // 1:0 XCMP1 Action
    Uint16 XCMP2:2;                     // 3:2 XCMP2 Action
    Uint16 XCMP3:2;                     // 5:4 XCMP3 Action
    Uint16 XCMP4:2;                     // 7:6 XCMP4 Action
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLA_ACTIVE_REG {
    Uint16  all;
    struct  XAQCTLA_ACTIVE_BITS  bit;
};

struct XAQCTLB_ACTIVE_BITS {            // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLB_ACTIVE_REG {
    Uint16  all;
    struct  XAQCTLB_ACTIVE_BITS  bit;
};

struct XMINMAX_ACTIVE_BITS {            // bits description
    Uint16 XMAX_ACTIVE:16;              // 15:0 Maximum Valude  for Capture Counter Active Register
    Uint16 XMIN_ACTIVE:16;              // 31:16 Minimum Valude  for Capture Counter Active Register
};

union XMINMAX_ACTIVE_REG {
    Uint32  all;
    struct  XMINMAX_ACTIVE_BITS  bit;
};

struct XCMP1_SHDW1_BITS {               // bits description
    Uint16 XCMP1HR_SHDW1:16;            // 15:0 Additional Compare 1 Shadow 1 HR Register
    Uint16 XCMP1_SHDW1:16;              // 31:16 Additional Compare 1 Shadow 1 Register
};

union XCMP1_SHDW1_REG {
    Uint32  all;
    struct  XCMP1_SHDW1_BITS  bit;
};

struct XCMP2_SHDW1_BITS {               // bits description
    Uint16 XCMP2HR_SHDW1:16;            // 15:0 Additional Compare 2 Shadow 1 HR Register
    Uint16 XCMP2_SHDW1:16;              // 31:16 Additional Compare 2 Shadow 1 Register
};

union XCMP2_SHDW1_REG {
    Uint32  all;
    struct  XCMP2_SHDW1_BITS  bit;
};

struct XCMP3_SHDW1_BITS {               // bits description
    Uint16 XCMP3HR_SHDW1:16;            // 15:0 Additional Compare 3 Shadow 1 HR Register
    Uint16 XCMP3_SHDW1:16;              // 31:16 Additional Compare 3 Shadow 1 Register
};

union XCMP3_SHDW1_REG {
    Uint32  all;
    struct  XCMP3_SHDW1_BITS  bit;
};

struct XCMP4_SHDW1_BITS {               // bits description
    Uint16 XCMP4HR_SHDW1:16;            // 15:0 Additional Compare 4 Shadow 1 HR Register
    Uint16 XCMP4_SHDW1:16;              // 31:16 Additional Compare 4 Shadow 1 Register
};

union XCMP4_SHDW1_REG {
    Uint32  all;
    struct  XCMP4_SHDW1_BITS  bit;
};

struct XCMP5_SHDW1_BITS {               // bits description
    Uint16 XCMP5HR_SHDW1:16;            // 15:0 Additional Compare 5 Shadow 1 HR Register
    Uint16 XCMP5_SHDW1:16;              // 31:16 Additional Compare 5 Shadow 1 Register
};

union XCMP5_SHDW1_REG {
    Uint32  all;
    struct  XCMP5_SHDW1_BITS  bit;
};

struct XCMP6_SHDW1_BITS {               // bits description
    Uint16 XCMP6HR_SHDW1:16;            // 15:0 Additional Compare 6 Shadow 1 HR Register
    Uint16 XCMP6_SHDW1:16;              // 31:16 Additional Compare 6 Shadow 1 Register
};

union XCMP6_SHDW1_REG {
    Uint32  all;
    struct  XCMP6_SHDW1_BITS  bit;
};

struct XCMP7_SHDW1_BITS {               // bits description
    Uint16 XCMP7HR_SHDW1:16;            // 15:0 Additional Compare 7 Shadow 1 HR Register
    Uint16 XCMP7_SHDW1:16;              // 31:16 Additional Compare 7 Shadow 1 Register
};

union XCMP7_SHDW1_REG {
    Uint32  all;
    struct  XCMP7_SHDW1_BITS  bit;
};

struct XCMP8_SHDW1_BITS {               // bits description
    Uint16 XCMP8HR_SHDW1:16;            // 15:0 Additional Compare 8 Shadow 1 HR Register
    Uint16 XCMP8_SHDW1:16;              // 31:16 Additional Compare 8 Shadow 1 Register
};

union XCMP8_SHDW1_REG {
    Uint32  all;
    struct  XCMP8_SHDW1_BITS  bit;
};

struct XTBPRD_SHDW1_BITS {              // bits description
    Uint16 XTBPRDHR_SHDW1:16;           // 15:0 Additional Time Base Period Shadow 1 HR Register
    Uint16 XTBPRD_SHDW1:16;             // 31:16 Additional Time Base Period Shadow 1 Register
};

union XTBPRD_SHDW1_REG {
    Uint32  all;
    struct  XTBPRD_SHDW1_BITS  bit;
};

struct XAQCTLA_SHDW1_BITS {             // bits description
    Uint16 XCMP1:2;                     // 1:0 XCMP1 Action
    Uint16 XCMP2:2;                     // 3:2 XCMP2 Action
    Uint16 XCMP3:2;                     // 5:4 XCMP3 Action
    Uint16 XCMP4:2;                     // 7:6 XCMP4 Action
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLA_SHDW1_REG {
    Uint16  all;
    struct  XAQCTLA_SHDW1_BITS  bit;
};

struct XAQCTLB_SHDW1_BITS {             // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLB_SHDW1_REG {
    Uint16  all;
    struct  XAQCTLB_SHDW1_BITS  bit;
};

struct XMINMAX_SHDW1_BITS {             // bits description
    Uint16 XMAX_SHDW1:16;               // 15:0 Maximum Valude  for Capture Counter Active Register
    Uint16 XMIN_SHDW1:16;               // 31:16 Minimum Valude  for Capture Counter Active Register
};

union XMINMAX_SHDW1_REG {
    Uint32  all;
    struct  XMINMAX_SHDW1_BITS  bit;
};

struct XCMP1_SHDW2_BITS {               // bits description
    Uint16 XCMP1HR_SHDW2:16;            // 15:0 Additional Compare 1 Shadow 2 HR Register
    Uint16 XCMP1_SHDW2:16;              // 31:16 Additional Compare 1 Shadow 2 Register
};

union XCMP1_SHDW2_REG {
    Uint32  all;
    struct  XCMP1_SHDW2_BITS  bit;
};

struct XCMP2_SHDW2_BITS {               // bits description
    Uint16 XCMP2HR_SHDW2:16;            // 15:0 Additional Compare 2 Shadow 2 HR Register
    Uint16 XCMP2_SHDW2:16;              // 31:16 Additional Compare 2 Shadow 2 Register
};

union XCMP2_SHDW2_REG {
    Uint32  all;
    struct  XCMP2_SHDW2_BITS  bit;
};

struct XCMP3_SHDW2_BITS {               // bits description
    Uint16 XCMP3HR_SHDW2:16;            // 15:0 Additional Compare 3 Shadow 2 HR Register
    Uint16 XCMP3_SHDW2:16;              // 31:16 Additional Compare 3 Shadow 2 Register
};

union XCMP3_SHDW2_REG {
    Uint32  all;
    struct  XCMP3_SHDW2_BITS  bit;
};

struct XCMP4_SHDW2_BITS {               // bits description
    Uint16 XCMP4HR_SHDW2:16;            // 15:0 Additional Compare 4 Shadow 2 HR Register
    Uint16 XCMP4_SHDW2:16;              // 31:16 Additional Compare 4 Shadow 2 Register
};

union XCMP4_SHDW2_REG {
    Uint32  all;
    struct  XCMP4_SHDW2_BITS  bit;
};

struct XCMP5_SHDW2_BITS {               // bits description
    Uint16 XCMP5HR_SHDW2:16;            // 15:0 Additional Compare 5 Shadow 2 HR Register
    Uint16 XCMP5_SHDW2:16;              // 31:16 Additional Compare 5 Shadow 2 Register
};

union XCMP5_SHDW2_REG {
    Uint32  all;
    struct  XCMP5_SHDW2_BITS  bit;
};

struct XCMP6_SHDW2_BITS {               // bits description
    Uint16 XCMP6HR_SHDW2:16;            // 15:0 Additional Compare 6 Shadow 2 HR Register
    Uint16 XCMP6_SHDW2:16;              // 31:16 Additional Compare 6 Shadow 2 Register
};

union XCMP6_SHDW2_REG {
    Uint32  all;
    struct  XCMP6_SHDW2_BITS  bit;
};

struct XCMP7_SHDW2_BITS {               // bits description
    Uint16 XCMP7HR_SHDW2:16;            // 15:0 Additional Compare 7 Shadow 2 HR Register
    Uint16 XCMP7_SHDW2:16;              // 31:16 Additional Compare 7 Shadow 2 Register
};

union XCMP7_SHDW2_REG {
    Uint32  all;
    struct  XCMP7_SHDW2_BITS  bit;
};

struct XCMP8_SHDW2_BITS {               // bits description
    Uint16 XCMP8HR_SHDW2:16;            // 15:0 Additional Compare 8 Shadow 2 HR Register
    Uint16 XCMP8_SHDW2:16;              // 31:16 Additional Compare 8 Shadow 2 Register
};

union XCMP8_SHDW2_REG {
    Uint32  all;
    struct  XCMP8_SHDW2_BITS  bit;
};

struct XTBPRD_SHDW2_BITS {              // bits description
    Uint16 XTBPRDHR_SHDW2:16;           // 15:0 Additional Time Base Period Shadow 1 HR Register
    Uint16 XTBPRD_SHDW2:16;             // 31:16 Additional Time Base Period Shadow 1 Register
};

union XTBPRD_SHDW2_REG {
    Uint32  all;
    struct  XTBPRD_SHDW2_BITS  bit;
};

struct XAQCTLA_SHDW2_BITS {             // bits description
    Uint16 XCMP1:2;                     // 1:0 XCMP1 Action
    Uint16 XCMP2:2;                     // 3:2 XCMP2 Action
    Uint16 XCMP3:2;                     // 5:4 XCMP3 Action
    Uint16 XCMP4:2;                     // 7:6 XCMP4 Action
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLA_SHDW2_REG {
    Uint16  all;
    struct  XAQCTLA_SHDW2_BITS  bit;
};

struct XAQCTLB_SHDW2_BITS {             // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLB_SHDW2_REG {
    Uint16  all;
    struct  XAQCTLB_SHDW2_BITS  bit;
};

struct XMINMAX_SHDW2_BITS {             // bits description
    Uint16 XMAX_SHDW2:16;               // 15:0 Maximum Valude  for Capture Counter Active Register
    Uint16 XMIN_SHDW2:16;               // 31:16 Minimum Valude  for Capture Counter Active Register
};

union XMINMAX_SHDW2_REG {
    Uint32  all;
    struct  XMINMAX_SHDW2_BITS  bit;
};

struct XCMP1_SHDW3_BITS {               // bits description
    Uint16 XCMP1HR_SHDW3:16;            // 15:0 Additional Compare 1 Shadow 3 HR Register
    Uint16 XCMP1_SHDW3:16;              // 31:16 Additional Compare 1 Shadow 3 Register
};

union XCMP1_SHDW3_REG {
    Uint32  all;
    struct  XCMP1_SHDW3_BITS  bit;
};

struct XCMP2_SHDW3_BITS {               // bits description
    Uint16 XCMP2HR_SHDW3:16;            // 15:0 Additional Compare 2 Shadow 3 HR Register
    Uint16 XCMP2_SHDW3:16;              // 31:16 Additional Compare 2 Shadow 3 Register
};

union XCMP2_SHDW3_REG {
    Uint32  all;
    struct  XCMP2_SHDW3_BITS  bit;
};

struct XCMP3_SHDW3_BITS {               // bits description
    Uint16 XCMP3HR_SHDW3:16;            // 15:0 Additional Compare 3 Shadow 3 HR Register
    Uint16 XCMP3_SHDW3:16;              // 31:16 Additional Compare 3 Shadow 3 Register
};

union XCMP3_SHDW3_REG {
    Uint32  all;
    struct  XCMP3_SHDW3_BITS  bit;
};

struct XCMP4_SHDW3_BITS {               // bits description
    Uint16 XCMP4HR_SHDW3:16;            // 15:0 Additional Compare 4 Shadow 3 HR Register
    Uint16 XCMP4_SHDW3:16;              // 31:16 Additional Compare 4 Shadow 3 Register
};

union XCMP4_SHDW3_REG {
    Uint32  all;
    struct  XCMP4_SHDW3_BITS  bit;
};

struct XCMP5_SHDW3_BITS {               // bits description
    Uint16 XCMP5HR_SHDW3:16;            // 15:0 Additional Compare 5 Shadow 3 HR Register
    Uint16 XCMP5_SHDW3:16;              // 31:16 Additional Compare 5 Shadow 3 Register
};

union XCMP5_SHDW3_REG {
    Uint32  all;
    struct  XCMP5_SHDW3_BITS  bit;
};

struct XCMP6_SHDW3_BITS {               // bits description
    Uint16 XCMP6HR_SHDW3:16;            // 15:0 Additional Compare 6 Shadow 3 HR Register
    Uint16 XCMP6_SHDW3:16;              // 31:16 Additional Compare 6 Shadow 3 Register
};

union XCMP6_SHDW3_REG {
    Uint32  all;
    struct  XCMP6_SHDW3_BITS  bit;
};

struct XCMP7_SHDW3_BITS {               // bits description
    Uint16 XCMP7HR_SHDW3:16;            // 15:0 Additional Compare 7 Shadow 3 HR Register
    Uint16 XCMP7_SHDW3:16;              // 31:16 Additional Compare 7 Shadow 3 Register
};

union XCMP7_SHDW3_REG {
    Uint32  all;
    struct  XCMP7_SHDW3_BITS  bit;
};

struct XCMP8_SHDW3_BITS {               // bits description
    Uint16 XCMP8HR_SHDW3:16;            // 15:0 Additional Compare 8 Shadow 3 HR Register
    Uint16 XCMP8_SHDW3:16;              // 31:16 Additional Compare 8 Shadow 3 Register
};

union XCMP8_SHDW3_REG {
    Uint32  all;
    struct  XCMP8_SHDW3_BITS  bit;
};

struct XTBPRD_SHDW3_BITS {              // bits description
    Uint16 XTBPRDHR_SHDW3:16;           // 15:0 Additional Time Base Period Shadow 1 HR Register
    Uint16 XTBPRD_SHDW3:16;             // 31:16 Additional Time Base Period Shadow 1 Register
};

union XTBPRD_SHDW3_REG {
    Uint32  all;
    struct  XTBPRD_SHDW3_BITS  bit;
};

struct XAQCTLA_SHDW3_BITS {             // bits description
    Uint16 XCMP1:2;                     // 1:0 XCMP1 Action
    Uint16 XCMP2:2;                     // 3:2 XCMP2 Action
    Uint16 XCMP3:2;                     // 5:4 XCMP3 Action
    Uint16 XCMP4:2;                     // 7:6 XCMP4 Action
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLA_SHDW3_REG {
    Uint16  all;
    struct  XAQCTLA_SHDW3_BITS  bit;
};

struct XAQCTLB_SHDW3_BITS {             // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 XCMP5:2;                     // 9:8 XCMP5 Action
    Uint16 XCMP6:2;                     // 11:10 XCMP6 Action
    Uint16 XCMP7:2;                     // 13:12 XCMP7 Action
    Uint16 XCMP8:2;                     // 15:14 XCMP8 Action
};

union XAQCTLB_SHDW3_REG {
    Uint16  all;
    struct  XAQCTLB_SHDW3_BITS  bit;
};

struct XMINMAX_SHDW3_BITS {             // bits description
    Uint16 XMAX_SHDW3:16;               // 15:0 Maximum Valude  for Capture Counter Active Register
    Uint16 XMIN_SHDW3:16;               // 31:16 Minimum Valude  for Capture Counter Active Register
};

union XMINMAX_SHDW3_REG {
    Uint32  all;
    struct  XMINMAX_SHDW3_BITS  bit;
};

struct EPWM_XCMP_REGS {
    union   XCMPCTL1_REG                     XCMPCTL1;                     // XCMP Mode Control Register
    Uint16                                   rsvd1[6];                     // Reserved
    union   XLOADCTL_REG                     XLOADCTL;                     // XCMP Mode Load Control Register
    Uint16                                   rsvd2[2];                     // Reserved
    union   XLOAD_REG                        XLOAD;                        // XCMP Mode Load Enable Register
    union   EPWMXLINKXLOAD_REG               EPWMXLINKXLOAD;               // Link register across PWM modules
    union   XREGSHDW1STS_REG                 XREGSHDW1STS;                 // Shadow Buffer 1 Update Status Register
    Uint16                                   rsvd3[2];                     // Reserved
    union   XREGSHDW2STS_REG                 XREGSHDW2STS;                 // Shadow Buffer 2 Update Status Register
    Uint16                                   rsvd4[2];                     // Reserved
    union   XREGSHDW3STS_REG                 XREGSHDW3STS;                 // Shadow Buffer 3 Update Status Register
    Uint16                                   rsvd5[6];                     // Reserved
    union   XCMP1_ACTIVE_REG                 XCMP1_ACTIVE;                 // Additional Compare 1 Active Register
    union   XCMP2_ACTIVE_REG                 XCMP2_ACTIVE;                 // Additional Compare 2 Active Register
    union   XCMP3_ACTIVE_REG                 XCMP3_ACTIVE;                 // Additional Compare 3 Active Register
    union   XCMP4_ACTIVE_REG                 XCMP4_ACTIVE;                 // Additional Compare 4 Active Register
    union   XCMP5_ACTIVE_REG                 XCMP5_ACTIVE;                 // Additional Compare 5 Active Register
    union   XCMP6_ACTIVE_REG                 XCMP6_ACTIVE;                 // Additional Compare 6 Active Register
    union   XCMP7_ACTIVE_REG                 XCMP7_ACTIVE;                 // Additional Compare 7 Active Register
    union   XCMP8_ACTIVE_REG                 XCMP8_ACTIVE;                 // Additional Compare 8 Active Register
    union   XTBPRD_ACTIVE_REG                XTBPRD_ACTIVE;                // Additional Time Base Period Active Register
    Uint16                                   rsvd6[2];                     // Reserved
    union   XAQCTLA_ACTIVE_REG               XAQCTLA_ACTIVE;               // AQCTLA Active Register
    union   XAQCTLB_ACTIVE_REG               XAQCTLB_ACTIVE;               // AQCTLB Active Register
    Uint16                                   rsvd7[8];                     // Reserved
    union   XMINMAX_ACTIVE_REG               XMINMAX_ACTIVE;               // XMINMAX Active Register
    union   XCMP1_SHDW1_REG                  XCMP1_SHDW1;                  // Additional Compare 1 Shadow 1 Register
    union   XCMP2_SHDW1_REG                  XCMP2_SHDW1;                  // Additional Compare 2 Shadow 1 Register
    union   XCMP3_SHDW1_REG                  XCMP3_SHDW1;                  // Additional Compare 3 Shadow 1 Register
    union   XCMP4_SHDW1_REG                  XCMP4_SHDW1;                  // Additional Compare 4 Shadow 1 Register
    union   XCMP5_SHDW1_REG                  XCMP5_SHDW1;                  // Additional Compare 5 Shadow 1 Register
    union   XCMP6_SHDW1_REG                  XCMP6_SHDW1;                  // Additional Compare 6 Shadow 1 Register
    union   XCMP7_SHDW1_REG                  XCMP7_SHDW1;                  // Additional Compare 7 Shadow 1 Register
    union   XCMP8_SHDW1_REG                  XCMP8_SHDW1;                  // Additional Compare 8 Shadow 1 Register
    union   XTBPRD_SHDW1_REG                 XTBPRD_SHDW1;                 // Additional Time Base Period Shadow 1 Register
    Uint16                                   rsvd8[2];                     // Reserved
    union   XAQCTLA_SHDW1_REG                XAQCTLA_SHDW1;                // XAQCTLA Shadow 1 Register
    union   XAQCTLB_SHDW1_REG                XAQCTLB_SHDW1;                // XAQCTLB Shadow 1 Register
    Uint16                                   rsvd9;                        // Reserved
    Uint16                                   CMPC_SHDW1;                   // CMPC Shadow 1 Register
    Uint16                                   rsvd10;                       // Reserved
    Uint16                                   CMPD_SHDW1;                   // CMPD Shadow 1 Register
    Uint16                                   rsvd11[4];                    // Reserved
    union   XMINMAX_SHDW1_REG                XMINMAX_SHDW1;                // XMINMAX Shadow 1 Register
    union   XCMP1_SHDW2_REG                  XCMP1_SHDW2;                  // Additional Compare 1 Shadow 2 Register
    union   XCMP2_SHDW2_REG                  XCMP2_SHDW2;                  // Additional Compare 2 Shadow 2 Register
    union   XCMP3_SHDW2_REG                  XCMP3_SHDW2;                  // Additional Compare 3 Shadow 2 Register
    union   XCMP4_SHDW2_REG                  XCMP4_SHDW2;                  // Additional Compare 4 Shadow 2 Register
    union   XCMP5_SHDW2_REG                  XCMP5_SHDW2;                  // Additional Compare 5 Shadow 2 Register
    union   XCMP6_SHDW2_REG                  XCMP6_SHDW2;                  // Additional Compare 6 Shadow 2 Register
    union   XCMP7_SHDW2_REG                  XCMP7_SHDW2;                  // Additional Compare 7 Shadow 2 Register
    union   XCMP8_SHDW2_REG                  XCMP8_SHDW2;                  // Additional Compare 8 Shadow 2 Register
    union   XTBPRD_SHDW2_REG                 XTBPRD_SHDW2;                 // Additional Time Base Period Shadow 2 Register
    Uint16                                   rsvd12[2];                    // Reserved
    union   XAQCTLA_SHDW2_REG                XAQCTLA_SHDW2;                // XAQCTLA Shadow 2 Register
    union   XAQCTLB_SHDW2_REG                XAQCTLB_SHDW2;                // XAQCTLB Shadow 2 Register
    Uint16                                   rsvd13;                       // Reserved
    Uint16                                   CMPC_SHDW2;                   // CMPC Shadow 2 Register
    Uint16                                   rsvd14;                       // Reserved
    Uint16                                   CMPD_SHDW2;                   // CMPD Shadow 2 Register
    Uint16                                   rsvd15[4];                    // Reserved
    union   XMINMAX_SHDW2_REG                XMINMAX_SHDW2;                // XMINMAX Shadow 2 Register
    union   XCMP1_SHDW3_REG                  XCMP1_SHDW3;                  // Additional Compare 1 Shadow 3 Register
    union   XCMP2_SHDW3_REG                  XCMP2_SHDW3;                  // Additional Compare 2 Shadow 3 Register
    union   XCMP3_SHDW3_REG                  XCMP3_SHDW3;                  // Additional Compare 3 Shadow 3 Register
    union   XCMP4_SHDW3_REG                  XCMP4_SHDW3;                  // Additional Compare 4 Shadow 3 Register
    union   XCMP5_SHDW3_REG                  XCMP5_SHDW3;                  // Additional Compare 5 Shadow 3 Register
    union   XCMP6_SHDW3_REG                  XCMP6_SHDW3;                  // Additional Compare 6 Shadow 3 Register
    union   XCMP7_SHDW3_REG                  XCMP7_SHDW3;                  // Additional Compare 7 Shadow 3 Register
    union   XCMP8_SHDW3_REG                  XCMP8_SHDW3;                  // Additional Compare 8 Shadow 3 Register
    union   XTBPRD_SHDW3_REG                 XTBPRD_SHDW3;                 // Additional Time Base Period Shadow 3 Register
    Uint16                                   rsvd16[2];                    // Reserved
    union   XAQCTLA_SHDW3_REG                XAQCTLA_SHDW3;                // XAQCTLA Shadow 3 Register
    union   XAQCTLB_SHDW3_REG                XAQCTLB_SHDW3;                // XAQCTLB Shadow 3 Register
    Uint16                                   rsvd17;                       // Reserved
    Uint16                                   CMPC_SHDW3;                   // CMPC Shadow 3 Register
    Uint16                                   rsvd18;                       // Reserved
    Uint16                                   CMPD_SHDW3;                   // CMPD Shadow 3 Register
    Uint16                                   rsvd19[4];                    // Reserved
    union   XMINMAX_SHDW3_REG                XMINMAX_SHDW3;                // XMINMAX Shadow 3 Register
};

struct DECTL_BITS {                     // bits description
    Uint16 ENABLE:1;                    // 0 DE function enable.
    Uint16 MODE:1;                      // 1 DE Mode
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 REENTRYDLY:8;                // 15:8 Re-entry delay value
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DECTL_REG {
    Uint32  all;
    struct  DECTL_BITS  bit;
};

struct DECOMPSEL_BITS {                 // bits description
    Uint16 TRIPL:6;                     // 5:0 Comparator TRIPL source select.
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 TRIPH:6;                     // 21:16 Comparator TRIPH source select.
    Uint16 rsvd2:10;                    // 31:22 Reserved
};

union DECOMPSEL_REG {
    Uint32  all;
    struct  DECOMPSEL_BITS  bit;
};

struct DEACTCTL_BITS {                  // bits description
    Uint16 PWMA:2;                      // 1:0 Comparator source select.
    Uint16 TRIPSELA:1;                  // 2 Trip source select on PWMA output
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 PWMB:2;                      // 5:4 Comparator source select.
    Uint16 TRIPSELB:1;                  // 6 Trip source select on PWMB output
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 TRIPENABLE:1;                // 16 Enables PWMTRIP condition to bypassDiode emulation logic.
    Uint16 rsvd3:15;                    // 31:17 Reserved
};

union DEACTCTL_REG {
    Uint32  all;
    struct  DEACTCTL_BITS  bit;
};

struct DESTS_BITS {                     // bits description
    Uint16 DEACTIVE:1;                  // 0 Diode Emulation mode active flag.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DESTS_REG {
    Uint32  all;
    struct  DESTS_BITS  bit;
};

struct DEFRC_BITS {                     // bits description
    Uint16 DEACTIVE:1;                  // 0 Diode Emulation mode active flag force.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DEFRC_REG {
    Uint32  all;
    struct  DEFRC_BITS  bit;
};

struct DECLR_BITS {                     // bits description
    Uint16 DEACTIVE:1;                  // 0 Diode Emulation mode active flag clear.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DECLR_REG {
    Uint32  all;
    struct  DECLR_BITS  bit;
};

struct DEMONCNT_BITS {                  // bits description
    Uint16 CNT:16;                      // 15:0 DEACTIVE monitor counter
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union DEMONCNT_REG {
    Uint32  all;
    struct  DEMONCNT_BITS  bit;
};

struct DEMONCTL_BITS {                  // bits description
    Uint16 ENABLE:1;                    // 0 DEACTIVE monitor counter
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DEMONCTL_REG {
    Uint32  all;
    struct  DEMONCTL_BITS  bit;
};

struct DEMONSTEP_BITS {                 // bits description
    Uint16 INCSTEP:8;                   // 7:0 DE monitor counter increment step.
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 DECSTEP:8;                   // 23:16 DE monitor counter decrement step.
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union DEMONSTEP_REG {
    Uint32  all;
    struct  DEMONSTEP_BITS  bit;
};

struct DEMONTHRES_BITS {                // bits description
    Uint16 THRESHOLD:16;                // 15:0 DE monitor counter compare threshold.
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union DEMONTHRES_REG {
    Uint32  all;
    struct  DEMONTHRES_BITS  bit;
};

struct DE_REGS {
    union   DECTL_REG                        DECTL;                        // DE control register
    union   DECOMPSEL_REG                    DECOMPSEL;                    // DE comparator source select register
    union   DEACTCTL_REG                     DEACTCTL;                     // DE Action Control
    union   DESTS_REG                        DESTS;                        // DE Status register
    union   DEFRC_REG                        DEFRC;                        // DE Status force register
    union   DECLR_REG                        DECLR;                        // DE Status clear register
    Uint16                                   rsvd1[4];                     // Reserved
    union   DEMONCNT_REG                     DEMONCNT;                     // DE trip monitor counter
    union   DEMONCTL_REG                     DEMONCTL;                     // DE monitor mode control
    union   DEMONSTEP_REG                    DEMONSTEP;                    // DE monitor counter step
    union   DEMONTHRES_REG                   DEMONTHRES;                   // DE monitor counter threshold
};

struct MINDBCFG_BITS {                  // bits description
    Uint16 ENABLEA:1;                   // 0 Minimum dead band logic enable on PWMA
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 INVERTA:1;                   // 2 Invert the selected reference signal on PWMA
    Uint16 SELBLOCKA:1;                 // 3 BLOCK signal source select on PWMA
    Uint16 SELA:4;                      // 7:4 Reference source select on PWMA min dead band logic.
    Uint16 POLSELA:1;                   // 8 Select signal for the AND OR logic of PWMA
    Uint16 rsvd2:7;                     // 15:9 Reserved
    Uint16 ENABLEB:1;                   // 16 Minimum dead band logic enable on PWMB
    Uint16 rsvd3:1;                     // 17 Reserved
    Uint16 INVERTB:1;                   // 18 Invert the selected reference signal on PWMB
    Uint16 SELBLOCKB:1;                 // 19 BLOCK signal source select on PWMB
    Uint16 SELB:4;                      // 23:20 Reference source select on PWMB min dead band logic.
    Uint16 POLSELB:1;                   // 24 Select signal for the AND OR logic of PWMB
    Uint16 rsvd4:7;                     // 31:25 Reserved
};

union MINDBCFG_REG {
    Uint32  all;
    struct  MINDBCFG_BITS  bit;
};

struct MINDBDLY_BITS {                  // bits description
    Uint16 DELAYA:16;                   // 15:0 Minimum dead band delay on PWMA
    Uint16 DELAYB:16;                   // 31:16 Minimum dead band delay on PWMB
};

union MINDBDLY_REG {
    Uint32  all;
    struct  MINDBDLY_BITS  bit;
};

struct LUTCTLA_BITS {                   // bits description
    Uint16 BYPASS:1;                    // 0 Bypass LUTA
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 SELXBAR:4;                   // 7:4 ICSS XBAR select
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 LUTDEC0:1;                   // 16 LUT output PWMA value on decoding 0
    Uint16 LUTDEC1:1;                   // 17 LUT output PWMA value on decoding 1
    Uint16 LUTDEC2:1;                   // 18 LUT output PWMA value on decoding 2
    Uint16 LUTDEC3:1;                   // 19 LUT output PWMA value on decoding 3
    Uint16 LUTDEC4:1;                   // 20 LUT output PWMA value on decoding 4
    Uint16 LUTDEC5:1;                   // 21 LUT output PWMA value on decoding 5
    Uint16 LUTDEC6:1;                   // 22 LUT output PWMA value on decoding 6
    Uint16 LUTDEC7:1;                   // 23 LUT output PWMA value on decoding 7
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union LUTCTLA_REG {
    Uint32  all;
    struct  LUTCTLA_BITS  bit;
};

struct LUTCTLB_BITS {                   // bits description
    Uint16 BYPASS:1;                    // 0 Bypass LUTB
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 SELXBAR:4;                   // 7:4 ICSS XBAR select
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 LUTDEC0:1;                   // 16 LUT output PWMB value on decoding 0
    Uint16 LUTDEC1:1;                   // 17 LUT output PWMB value on decoding 1
    Uint16 LUTDEC2:1;                   // 18 LUT output PWMB value on decoding 2
    Uint16 LUTDEC3:1;                   // 19 LUT output PWMB value on decoding 3
    Uint16 LUTDEC4:1;                   // 20 LUT output PWMB value on decoding 4
    Uint16 LUTDEC5:1;                   // 21 LUT output PWMB value on decoding 5
    Uint16 LUTDEC6:1;                   // 22 LUT output PWMB value on decoding 6
    Uint16 LUTDEC7:1;                   // 23 LUT output PWMB value on decoding 7
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union LUTCTLB_REG {
    Uint32  all;
    struct  LUTCTLB_BITS  bit;
};

struct MINDB_LUT_REGS {
    union   MINDBCFG_REG                     MINDBCFG;                     // Minimum dead band configuration register.
    union   MINDBDLY_REG                     MINDBDLY;                     // Minimum dead band delay register
    Uint16                                   rsvd1[12];                    // Reserved
    union   LUTCTLA_REG                      LUTCTLA;                      // LUT control register on PWMA
    union   LUTCTLB_REG                      LUTCTLB;                      // LUT control register on PWMB
};

//---------------------------------------------------------------------------
// EPWM External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct EPWM_REGS EPwm17Regs;
extern volatile struct EPWM_REGS EPwm18Regs;
extern volatile struct EPWM_REGS EPwm1Regs;
extern volatile struct EPWM_REGS EPwm2Regs;
extern volatile struct EPWM_REGS EPwm3Regs;
extern volatile struct EPWM_REGS EPwm4Regs;
extern volatile struct EPWM_REGS EPwm5Regs;
extern volatile struct EPWM_REGS EPwm6Regs;
extern volatile struct EPWM_REGS EPwm7Regs;
extern volatile struct EPWM_REGS EPwm8Regs;
extern volatile struct EPWM_REGS EPwm9Regs;
extern volatile struct EPWM_REGS EPwm10Regs;
extern volatile struct EPWM_REGS EPwm11Regs;
extern volatile struct EPWM_REGS EPwm12Regs;
extern volatile struct EPWM_REGS EPwm13Regs;
extern volatile struct EPWM_REGS EPwm14Regs;
extern volatile struct EPWM_REGS EPwm15Regs;
extern volatile struct EPWM_REGS EPwm16Regs;
#endif
#ifdef CPU2
extern volatile struct EPWM_REGS EPwm17Regs;
extern volatile struct EPWM_REGS EPwm18Regs;
extern volatile struct EPWM_REGS EPwm1Regs;
extern volatile struct EPWM_REGS EPwm2Regs;
extern volatile struct EPWM_REGS EPwm3Regs;
extern volatile struct EPWM_REGS EPwm4Regs;
extern volatile struct EPWM_REGS EPwm5Regs;
extern volatile struct EPWM_REGS EPwm6Regs;
extern volatile struct EPWM_REGS EPwm7Regs;
extern volatile struct EPWM_REGS EPwm8Regs;
extern volatile struct EPWM_REGS EPwm9Regs;
extern volatile struct EPWM_REGS EPwm10Regs;
extern volatile struct EPWM_REGS EPwm11Regs;
extern volatile struct EPWM_REGS EPwm12Regs;
extern volatile struct EPWM_REGS EPwm13Regs;
extern volatile struct EPWM_REGS EPwm14Regs;
extern volatile struct EPWM_REGS EPwm15Regs;
extern volatile struct EPWM_REGS EPwm16Regs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
