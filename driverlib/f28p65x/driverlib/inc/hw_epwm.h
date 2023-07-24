//###########################################################################
//
// FILE:    hw_epwm.h
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

#ifndef HW_EPWM_H
#define HW_EPWM_H

//*************************************************************************************************
//
// The following are defines for the EPWM register offsets
//
//*************************************************************************************************
#define EPWM_O_TBCTL              0x0U    // Time Base Control Register
#define EPWM_O_TBCTL2             0x1U    // Time Base Control Register 2
#define EPWM_O_SYNCINSEL          0x3U    // EPWMxSYNCIN Source Select Register
#define EPWM_O_TBCTR              0x4U    // Time Base Counter Register
#define EPWM_O_TBSTS              0x5U    // Time Base Status Register
#define EPWM_O_SYNCOUTEN          0x6U    // EPWMxSYNCOUT Source Enable Register
#define EPWM_O_TBCTL3             0x7U    // Time Base Control Register 3
#define EPWM_O_CMPCTL             0x8U    // Counter Compare Control Register
#define EPWM_O_CMPCTL2            0x9U    // Counter Compare Control Register 2
#define EPWM_O_DBCTL              0xCU    // Dead-Band Generator Control Register
#define EPWM_O_DBCTL2             0xDU    // Dead-Band Generator Control Register 2
#define EPWM_O_AQCTL              0x10U   // Action Qualifier Control Register
#define EPWM_O_AQTSRCSEL          0x11U   // Action Qualifier Trigger Event Source Select Register
#define EPWM_O_PCCTL              0x14U   // PWM Chopper Control Register
#define EPWM_O_VCAPCTL            0x18U   // Valley Capture Control Register
#define EPWM_O_VCNTCFG            0x19U   // Valley Counter Config Register
#define EPWM_O_HRCNFG             0x20U   // HRPWM Configuration Register
#define EPWM_O_HRCNFG2            0x27U   // HRPWM Configuration 2 Register
#define EPWM_O_HRPCTL             0x2DU   // High Resolution Period Control Register
#define EPWM_O_TRREM              0x2EU   // HRPWM High Resolution Remainder Register
#define EPWM_O_GLDCTL             0x34U   // Global PWM Load Control Register
#define EPWM_O_GLDCFG             0x35U   // Global PWM Load Config Register
#define EPWM_O_XLINK              0x38U   // EPWMx Link Register
#define EPWM_O_XLINK2             0x3AU   // EPWMx Link 2 Register
#define EPWM_O_AQCTLA             0x40U   // Action Qualifier Control Register For Output A
#define EPWM_O_AQCTLA2            0x41U   // Additional Action Qualifier Control Register For
                                          // Output A
#define EPWM_O_AQCTLB             0x42U   // Action Qualifier Control Register For Output B
#define EPWM_O_AQCTLB2            0x43U   // Additional Action Qualifier Control Register For
                                          // Output B
#define EPWM_O_AQSFRC             0x47U   // Action Qualifier Software Force Register
#define EPWM_O_AQCSFRC            0x49U   // Action Qualifier Continuous S/W Force Register
#define EPWM_O_DBREDHR            0x50U   // Dead-Band Generator Rising Edge Delay High Resolution
                                          // Mirror Register
#define EPWM_O_DBRED              0x51U   // Dead-Band Generator Rising Edge Delay High Resolution
                                          // Mirror Register
#define EPWM_O_DBFEDHR            0x52U   // Dead-Band Generator Falling Edge Delay High Resolution
                                          // Register
#define EPWM_O_DBFED              0x53U   // Dead-Band Generator Falling Edge Delay Count Register
#define EPWM_O_TBPHS              0x60U   // Time Base Phase High
#define EPWM_O_TBPRDHR            0x62U   // Time Base Period High Resolution Register
#define EPWM_O_TBPRD              0x63U   // Time Base Period Register
#define EPWM_O_CMPA               0x6AU   // Counter Compare A Register
#define EPWM_O_CMPB               0x6CU   // Compare B Register
#define EPWM_O_CMPC               0x6FU   // Counter Compare C Register
#define EPWM_O_CMPD               0x71U   // Counter Compare D Register
#define EPWM_O_GLDCTL2            0x74U   // Global PWM Load Control Register 2
#define EPWM_O_SWVDELVAL          0x77U   // Software Valley Mode Delay Register
#define EPWM_O_TZSEL              0x80U   // Trip Zone Select Register
#define EPWM_O_TZSEL2             0x81U   // Trip Zone Select Register 2
#define EPWM_O_TZDCSEL            0x82U   // Trip Zone Digital Comparator Select Register
#define EPWM_O_TZCTL              0x84U   // Trip Zone Control Register
#define EPWM_O_TZCTL2             0x85U   // Additional Trip Zone Control Register
#define EPWM_O_TZCTLDCA           0x86U   // Trip Zone Control Register Digital Compare A
#define EPWM_O_TZCTLDCB           0x87U   // Trip Zone Control Register Digital Compare B
#define EPWM_O_TZEINT             0x8DU   // Trip Zone Enable Interrupt Register
#define EPWM_O_TZFLG              0x93U   // Trip Zone Flag Register
#define EPWM_O_TZCBCFLG           0x94U   // Trip Zone CBC Flag Register
#define EPWM_O_TZOSTFLG           0x95U   // Trip Zone OST Flag Register
#define EPWM_O_TZCLR              0x97U   // Trip Zone Clear Register
#define EPWM_O_TZCBCCLR           0x98U   // Trip Zone CBC Clear Register
#define EPWM_O_TZOSTCLR           0x99U   // Trip Zone OST Clear Register
#define EPWM_O_TZFRC              0x9BU   // Trip Zone Force Register
#define EPWM_O_TZTRIPOUTSEL       0x9DU   // Trip Out Select Register
#define EPWM_O_ETSEL              0xA4U   // Event Trigger Selection Register
#define EPWM_O_ETPS               0xA6U   // Event Trigger Pre-Scale Register
#define EPWM_O_ETFLG              0xA8U   // Event Trigger Flag Register
#define EPWM_O_ETCLR              0xAAU   // Event Trigger Clear Register
#define EPWM_O_ETFRC              0xACU   // Event Trigger Force Register
#define EPWM_O_ETINTPS            0xAEU   // Event-Trigger Interrupt Pre-Scale Register
#define EPWM_O_ETSOCPS            0xB0U   // Event-Trigger SOC Pre-Scale Register
#define EPWM_O_ETCNTINITCTL       0xB2U   // Event-Trigger Counter Initialization Control Register
#define EPWM_O_ETCNTINIT          0xB4U   // Event-Trigger Counter Initialization Register
#define EPWM_O_ETINTMIXEN         0xB6U   // Event-Trigger Mixed INT Selection
#define EPWM_O_ETSOCAMIXEN        0xB8U   // Event-Trigger Mixed SOCA Selection
#define EPWM_O_ETSOCBMIXEN        0xBAU   // Event-Trigger Mixed SOCB Selection
#define EPWM_O_DCTRIPSEL          0xC0U   // Digital Compare Trip Select Register
#define EPWM_O_DCACTL             0xC3U   // Digital Compare A Control Register
#define EPWM_O_DCBCTL             0xC4U   // Digital Compare B Control Register
#define EPWM_O_DCFCTL             0xC7U   // Digital Compare Filter Control Register
#define EPWM_O_DCCAPCTL           0xC8U   // Digital Compare Capture Control Register
#define EPWM_O_DCFOFFSET          0xC9U   // Digital Compare Filter Offset Register
#define EPWM_O_DCFOFFSETCNT       0xCAU   // Digital Compare Filter Offset Counter Register
#define EPWM_O_DCFWINDOW          0xCBU   // Digital Compare Filter Window Register
#define EPWM_O_DCFWINDOWCNT       0xCCU   // Digital Compare Filter Window Counter Register
#define EPWM_O_BLANKPULSEMIXSEL   0xCDU   // Blanking window trigger pulse select register
#define EPWM_O_DCCAPMIXSEL        0xCEU   // Capture Event pulse select register
#define EPWM_O_DCCAP              0xCFU   // Digital Compare Counter Capture Register
#define EPWM_O_DCAHTRIPSEL        0xD2U   // Digital Compare AH Trip Select
#define EPWM_O_DCALTRIPSEL        0xD3U   // Digital Compare AL Trip Select
#define EPWM_O_DCBHTRIPSEL        0xD4U   // Digital Compare BH Trip Select
#define EPWM_O_DCBLTRIPSEL        0xD5U   // Digital Compare BL Trip Select
#define EPWM_O_CAPCTL             0xD6U   // Event Capture Control Register
#define EPWM_O_CAPGATETRIPSEL     0xD7U   // Event Capture Gate Trip input select
#define EPWM_O_CAPINTRIPSEL       0xD8U   // Event Capture Trip input select
#define EPWM_O_CAPTRIPSEL         0xD9U   // Event Capture Signal Select
#define EPWM_O_LOCK               0xFAU   // EPWM Lock Register
#define EPWM_O_HWVDELVAL          0xFDU   // Hardware Valley Mode Delay Register
#define EPWM_O_VCNTVAL            0xFEU   // Hardware Valley Counter Register

#define EPWM_O_XCMPCTL1         0x0U    // XCMP Mode Control Register
#define EPWM_O_XLOADCTL         0x8U    // XCMP Mode Load Control Register
#define EPWM_O_XLOAD            0xCU    // XCMP Mode Load Enable Register
#define EPWM_O_XLINKXLOAD       0xEU    // Link register across PWM modules
#define EPWM_O_XREGSHDW1STS     0x10U   // Shadow Buffer 1 Update Status Register
#define EPWM_O_XREGSHDW2STS     0x14U   // Shadow Buffer 2 Update Status Register
#define EPWM_O_XREGSHDW3STS     0x18U   // Shadow Buffer 3 Update Status Register
#define EPWM_O_XCMP1_ACTIVE     0x20U   // Additional Compare 1 Active Register
#define EPWM_O_XCMP2_ACTIVE     0x22U   // Additional Compare 2 Active Register
#define EPWM_O_XCMP3_ACTIVE     0x24U   // Additional Compare 3 Active Register
#define EPWM_O_XCMP4_ACTIVE     0x26U   // Additional Compare 4 Active Register
#define EPWM_O_XCMP5_ACTIVE     0x28U   // Additional Compare 5 Active Register
#define EPWM_O_XCMP6_ACTIVE     0x2AU   // Additional Compare 6 Active Register
#define EPWM_O_XCMP7_ACTIVE     0x2CU   // Additional Compare 7 Active Register
#define EPWM_O_XCMP8_ACTIVE     0x2EU   // Additional Compare 8 Active Register
#define EPWM_O_XTBPRD_ACTIVE    0x30U   // Additional Time Base Period Active Register
#define EPWM_O_XAQCTLA_ACTIVE   0x34U   // AQCTLA Active Register
#define EPWM_O_XAQCTLB_ACTIVE   0x35U   // AQCTLB Active Register
#define EPWM_O_XMINMAX_ACTIVE   0x3EU   // XMINMAX Active Register
#define EPWM_O_XCMP1_SHDW1      0x40U   // Additional Compare 1 Shadow 1 Register
#define EPWM_O_XCMP2_SHDW1      0x42U   // Additional Compare 2 Shadow 1 Register
#define EPWM_O_XCMP3_SHDW1      0x44U   // Additional Compare 3 Shadow 1 Register
#define EPWM_O_XCMP4_SHDW1      0x46U   // Additional Compare 4 Shadow 1 Register
#define EPWM_O_XCMP5_SHDW1      0x48U   // Additional Compare 5 Shadow 1 Register
#define EPWM_O_XCMP6_SHDW1      0x4AU   // Additional Compare 6 Shadow 1 Register
#define EPWM_O_XCMP7_SHDW1      0x4CU   // Additional Compare 7 Shadow 1 Register
#define EPWM_O_XCMP8_SHDW1      0x4EU   // Additional Compare 8 Shadow 1 Register
#define EPWM_O_XTBPRD_SHDW1     0x50U   // Additional Time Base Period Shadow 1 Register
#define EPWM_O_XAQCTLA_SHDW1    0x54U   // XAQCTLA Shadow 1 Register
#define EPWM_O_XAQCTLB_SHDW1    0x55U   // XAQCTLB Shadow 1 Register
#define EPWM_O_CMPC_SHDW1       0x57U   // CMPC Shadow 1 Register
#define EPWM_O_CMPD_SHDW1       0x59U   // CMPD Shadow 1 Register
#define EPWM_O_XMINMAX_SHDW1    0x5EU   // XMINMAX Shadow 1 Register
#define EPWM_O_XCMP1_SHDW2      0x60U   // Additional Compare 1 Shadow 2 Register
#define EPWM_O_XCMP2_SHDW2      0x62U   // Additional Compare 2 Shadow 2 Register
#define EPWM_O_XCMP3_SHDW2      0x64U   // Additional Compare 3 Shadow 2 Register
#define EPWM_O_XCMP4_SHDW2      0x66U   // Additional Compare 4 Shadow 2 Register
#define EPWM_O_XCMP5_SHDW2      0x68U   // Additional Compare 5 Shadow 2 Register
#define EPWM_O_XCMP6_SHDW2      0x6AU   // Additional Compare 6 Shadow 2 Register
#define EPWM_O_XCMP7_SHDW2      0x6CU   // Additional Compare 7 Shadow 2 Register
#define EPWM_O_XCMP8_SHDW2      0x6EU   // Additional Compare 8 Shadow 2 Register
#define EPWM_O_XTBPRD_SHDW2     0x70U   // Additional Time Base Period Shadow 2 Register
#define EPWM_O_XAQCTLA_SHDW2    0x74U   // XAQCTLA Shadow 2 Register
#define EPWM_O_XAQCTLB_SHDW2    0x75U   // XAQCTLB Shadow 2 Register
#define EPWM_O_CMPC_SHDW2       0x77U   // CMPC Shadow 2 Register
#define EPWM_O_CMPD_SHDW2       0x79U   // CMPD Shadow 2 Register
#define EPWM_O_XMINMAX_SHDW2    0x7EU   // XMINMAX Shadow 2 Register
#define EPWM_O_XCMP1_SHDW3      0x80U   // Additional Compare 1 Shadow 3 Register
#define EPWM_O_XCMP2_SHDW3      0x82U   // Additional Compare 2 Shadow 3 Register
#define EPWM_O_XCMP3_SHDW3      0x84U   // Additional Compare 3 Shadow 3 Register
#define EPWM_O_XCMP4_SHDW3      0x86U   // Additional Compare 4 Shadow 3 Register
#define EPWM_O_XCMP5_SHDW3      0x88U   // Additional Compare 5 Shadow 3 Register
#define EPWM_O_XCMP6_SHDW3      0x8AU   // Additional Compare 6 Shadow 3 Register
#define EPWM_O_XCMP7_SHDW3      0x8CU   // Additional Compare 7 Shadow 3 Register
#define EPWM_O_XCMP8_SHDW3      0x8EU   // Additional Compare 8 Shadow 3 Register
#define EPWM_O_XTBPRD_SHDW3     0x90U   // Additional Time Base Period Shadow 3 Register
#define EPWM_O_XAQCTLA_SHDW3    0x94U   // XAQCTLA Shadow 3 Register
#define EPWM_O_XAQCTLB_SHDW3    0x95U   // XAQCTLB Shadow 3 Register
#define EPWM_O_CMPC_SHDW3       0x97U   // CMPC Shadow 3 Register
#define EPWM_O_CMPD_SHDW3       0x99U   // CMPD Shadow 3 Register
#define EPWM_O_XMINMAX_SHDW3    0x9EU   // XMINMAX Shadow 3 Register

#define EPWM_O_DECTL        0x0U    // DE control register
#define EPWM_O_DECOMPSEL    0x2U    // DE comparator source select register
#define EPWM_O_DEACTCTL     0x4U    // DE Action Control
#define EPWM_O_DESTS        0x6U    // DE Status register
#define EPWM_O_DEFRC        0x8U    // DE Status force register
#define EPWM_O_DECLR        0xAU    // DE Status clear register
#define EPWM_O_DEMONCNT     0x10U   // DE trip monitor counter
#define EPWM_O_DEMONCTL     0x12U   // DE monitor mode control
#define EPWM_O_DEMONSTEP    0x14U   // DE monitor counter step
#define EPWM_O_DEMONTHRES   0x16U   // DE monitor counter threshold

#define EPWM_O_MINDBCFG   0x0U    // Minimum dead band configuration register.
#define EPWM_O_MINDBDLY   0x2U    // Minimum dead band delay register
#define EPWM_O_LUTCTLA    0x10U   // LUT control register on PWMA
#define EPWM_O_LUTCTLB    0x12U   // LUT control register on PWMB


//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL register
//
//*************************************************************************************************
#define EPWM_TBCTL_CTRMODE_S     0U
#define EPWM_TBCTL_CTRMODE_M     0x3U      // Counter Mode
#define EPWM_TBCTL_PHSEN         0x4U      // Phase Load Enable
#define EPWM_TBCTL_PRDLD         0x8U      // Active Period Load
#define EPWM_TBCTL_SWFSYNC       0x40U     // Software Force Sync Pulse
#define EPWM_TBCTL_HSPCLKDIV_S   7U
#define EPWM_TBCTL_HSPCLKDIV_M   0x380U    // High Speed TBCLK Pre-scaler
#define EPWM_TBCTL_CLKDIV_S      10U
#define EPWM_TBCTL_CLKDIV_M      0x1C00U   // Time Base Clock Pre-scaler
#define EPWM_TBCTL_PHSDIR        0x2000U   // Phase Direction Bit
#define EPWM_TBCTL_FREE_SOFT_S   14U
#define EPWM_TBCTL_FREE_SOFT_M   0xC000U   // Emulation Mode Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL2 register
//
//*************************************************************************************************
#define EPWM_TBCTL2_OSHTSYNCMODE   0x40U     // One shot sync mode
#define EPWM_TBCTL2_OSHTSYNC       0x80U     // One shot sync
#define EPWM_TBCTL2_PRDLDSYNC_S    14U
#define EPWM_TBCTL2_PRDLDSYNC_M    0xC000U   // PRD Shadow to Active Load on SYNC Event

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMSYNCINSEL register
//
//*************************************************************************************************
#define EPWM_SYNCINSEL_SEL_S   0U
#define EPWM_SYNCINSEL_SEL_M   0x7FU   // EPWMxSYNCI source select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*************************************************************************************************
#define EPWM_TBSTS_CTRDIR   0x1U   // Counter Direction Status
#define EPWM_TBSTS_SYNCI    0x2U   // External Input Sync Status
#define EPWM_TBSTS_CTRMAX   0x4U   // Counter Max Latched Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMSYNCOUTEN register
//
//*************************************************************************************************
#define EPWM_SYNCOUTEN_SWEN        0x1U    // EPWMxSYNCO Software Force Enable
#define EPWM_SYNCOUTEN_ZEROEN      0x2U    // EPWMxSYNCO Zero Count Event Enable
#define EPWM_SYNCOUTEN_CMPBEN      0x4U    // EPWMxSYNCO Compare B Event Enable
#define EPWM_SYNCOUTEN_CMPCEN      0x8U    // EPWMxSYNCO Compare C Event Enable
#define EPWM_SYNCOUTEN_CMPDEN      0x10U   // EPWMxSYNCO Compare D Event Enable
#define EPWM_SYNCOUTEN_DCAEVT1EN   0x20U   // EPWMxSYNCO Digital Compare A Event 1 Sync Enable
#define EPWM_SYNCOUTEN_DCBEVT1EN   0x40U   // EPWMxSYNCO Digital Compare B Event 1 Sync Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL3 register
//
//*************************************************************************************************
#define EPWM_TBCTL3_OSSFRCEN   0x1U   // One Shot Sync Force Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL register
//
//*************************************************************************************************
#define EPWM_CMPCTL_LOADAMODE_S   0U
#define EPWM_CMPCTL_LOADAMODE_M   0x3U      // Active Compare A Load
#define EPWM_CMPCTL_LOADBMODE_S   2U
#define EPWM_CMPCTL_LOADBMODE_M   0xCU      // Active Compare B Load
#define EPWM_CMPCTL_SHDWAMODE     0x10U     // Compare A Register Block Operating Mode
#define EPWM_CMPCTL_SHDWBMODE     0x40U     // Compare B Register Block Operating Mode
#define EPWM_CMPCTL_SHDWAFULL     0x100U    // Compare A Shadow Register Full Status
#define EPWM_CMPCTL_SHDWBFULL     0x200U    // Compare B Shadow Register Full Status
#define EPWM_CMPCTL_LOADASYNC_S   10U
#define EPWM_CMPCTL_LOADASYNC_M   0xC00U    // Active Compare A Load on SYNC
#define EPWM_CMPCTL_LOADBSYNC_S   12U
#define EPWM_CMPCTL_LOADBSYNC_M   0x3000U   // Active Compare B Load on SYNC
#define EPWM_CMPCTL_LINKDUTYHR    0x8000U   // Enable same values on CMPAHR/CMPBHR

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL2 register
//
//*************************************************************************************************
#define EPWM_CMPCTL2_LOADCMODE_S   0U
#define EPWM_CMPCTL2_LOADCMODE_M   0x3U      // Active Compare C Load
#define EPWM_CMPCTL2_LOADDMODE_S   2U
#define EPWM_CMPCTL2_LOADDMODE_M   0xCU      // Active Compare D load
#define EPWM_CMPCTL2_SHDWCMODE     0x10U     // Compare C Block Operating Mode
#define EPWM_CMPCTL2_SHDWDMODE     0x40U     // Compare D Block Operating Mode
#define EPWM_CMPCTL2_LOADCSYNC_S   10U
#define EPWM_CMPCTL2_LOADCSYNC_M   0xC00U    // Active Compare C Load on SYNC
#define EPWM_CMPCTL2_LOADDSYNC_S   12U
#define EPWM_CMPCTL2_LOADDSYNC_M   0x3000U   // Active Compare D Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL register
//
//*************************************************************************************************
#define EPWM_DBCTL_OUT_MODE_S      0U
#define EPWM_DBCTL_OUT_MODE_M      0x3U      // Dead Band Output Mode Control
#define EPWM_DBCTL_POLSEL_S        2U
#define EPWM_DBCTL_POLSEL_M        0xCU      // Polarity Select Control
#define EPWM_DBCTL_IN_MODE_S       4U
#define EPWM_DBCTL_IN_MODE_M       0x30U     // Dead Band Input Select Mode Control
#define EPWM_DBCTL_LOADREDMODE_S   6U
#define EPWM_DBCTL_LOADREDMODE_M   0xC0U     // Active DBRED Load Mode
#define EPWM_DBCTL_LOADFEDMODE_S   8U
#define EPWM_DBCTL_LOADFEDMODE_M   0x300U    // Active DBFED Load Mode
#define EPWM_DBCTL_SHDWDBREDMODE   0x400U    // DBRED Block Operating Mode
#define EPWM_DBCTL_SHDWDBFEDMODE   0x800U    // DBFED Block Operating Mode
#define EPWM_DBCTL_OUTSWAP_S       12U
#define EPWM_DBCTL_OUTSWAP_M       0x3000U   // Dead Band Output Swap Control
#define EPWM_DBCTL_DEDB_MODE       0x4000U   // Dead Band Dual-Edge B Mode Control
#define EPWM_DBCTL_HALFCYCLE       0x8000U   // Half Cycle Clocking Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL2 register
//
//*************************************************************************************************
#define EPWM_DBCTL2_LOADDBCTLMODE_S   0U
#define EPWM_DBCTL2_LOADDBCTLMODE_M   0x3U   // DBCTL Load from Shadow Mode Select
#define EPWM_DBCTL2_SHDWDBCTLMODE     0x4U   // DBCTL Load mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTL register
//
//*************************************************************************************************
#define EPWM_AQCTL_LDAQAMODE_S   0U
#define EPWM_AQCTL_LDAQAMODE_M   0x3U     // Action Qualifier A Load Select
#define EPWM_AQCTL_LDAQBMODE_S   2U
#define EPWM_AQCTL_LDAQBMODE_M   0xCU     // Action Qualifier B Load Select
#define EPWM_AQCTL_SHDWAQAMODE   0x10U    // Action Qualifer A Operating Mode
#define EPWM_AQCTL_SHDWAQBMODE   0x40U    // Action Qualifier B Operating Mode
#define EPWM_AQCTL_LDAQASYNC_S   8U
#define EPWM_AQCTL_LDAQASYNC_M   0x300U   // AQCTLA Register Load on SYNC
#define EPWM_AQCTL_LDAQBSYNC_S   10U
#define EPWM_AQCTL_LDAQBSYNC_M   0xC00U   // AQCTLB Register Load on SYNC

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQTSRCSEL register
//
//*************************************************************************************************
#define EPWM_AQTSRCSEL_T1SEL_S   0U
#define EPWM_AQTSRCSEL_T1SEL_M   0xFU    // T1 Event Source Select Bits
#define EPWM_AQTSRCSEL_T2SEL_S   4U
#define EPWM_AQTSRCSEL_T2SEL_M   0xF0U   // T2 Event Source Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCCTL register
//
//*************************************************************************************************
#define EPWM_PCCTL_CHPEN       0x1U     // PWM chopping enable
#define EPWM_PCCTL_OSHTWTH_S   1U
#define EPWM_PCCTL_OSHTWTH_M   0x1EU    // One-shot pulse width
#define EPWM_PCCTL_CHPFREQ_S   5U
#define EPWM_PCCTL_CHPFREQ_M   0xE0U    // Chopping clock frequency
#define EPWM_PCCTL_CHPDUTY_S   8U
#define EPWM_PCCTL_CHPDUTY_M   0x700U   // Chopping clock Duty cycle

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCAPCTL register
//
//*************************************************************************************************
#define EPWM_VCAPCTL_VCAPE            0x1U     // Valley  Capture mode
#define EPWM_VCAPCTL_VCAPSTART        0x2U     // Valley  Capture Start
#define EPWM_VCAPCTL_TRIGSEL_S        2U
#define EPWM_VCAPCTL_TRIGSEL_M        0x1CU    // Capture Trigger Select
#define EPWM_VCAPCTL_VDELAYDIV_S      7U
#define EPWM_VCAPCTL_VDELAYDIV_M      0x380U   // Valley Delay Mode Divide Enable
#define EPWM_VCAPCTL_EDGEFILTDLYSEL   0x400U   // Valley Switching Mode Delay Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the VCNTCFG register
//
//*************************************************************************************************
#define EPWM_VCNTCFG_STARTEDGE_S    0U
#define EPWM_VCNTCFG_STARTEDGE_M    0xFU      // Counter Start Edge Selection
#define EPWM_VCNTCFG_STARTEDGESTS   0x80U     // Start Edge Status Bit
#define EPWM_VCNTCFG_STOPEDGE_S     8U
#define EPWM_VCNTCFG_STOPEDGE_M     0xF00U    // Counter Start Edge Selection
#define EPWM_VCNTCFG_STOPEDGESTS    0x8000U   // Stop Edge Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCNFG register
//
//*************************************************************************************************
#define EPWM_HRCNFG_EDGMODE_S    0U
#define EPWM_HRCNFG_EDGMODE_M    0x3U      // ePWMxA Edge Mode Select Bits
#define EPWM_HRCNFG_CTLMODE      0x4U      // ePWMxA Control Mode Select Bits
#define EPWM_HRCNFG_HRLOAD_S     3U
#define EPWM_HRCNFG_HRLOAD_M     0x18U     // ePWMxA Shadow Mode Select Bits
#define EPWM_HRCNFG_SELOUTB      0x20U     // EPWMB Output Selection Bit
#define EPWM_HRCNFG_AUTOCONV     0x40U     // Autoconversion Bit
#define EPWM_HRCNFG_SWAPAB       0x80U     // Swap EPWMA and EPWMB Outputs Bit
#define EPWM_HRCNFG_EDGMODEB_S   8U
#define EPWM_HRCNFG_EDGMODEB_M   0x300U    // ePWMxB Edge Mode Select Bits
#define EPWM_HRCNFG_CTLMODEB     0x400U    // ePWMxB Control Mode Select Bits
#define EPWM_HRCNFG_HRLOADB_S    11U
#define EPWM_HRCNFG_HRLOADB_M    0x1800U   // ePWMxB Shadow Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCNFG2 register
//
//*************************************************************************************************
#define EPWM_HRCNFG2_EDGMODEDB_S      0U
#define EPWM_HRCNFG2_EDGMODEDB_M      0x3U    // Dead-Band Edge-Mode Select Bits
#define EPWM_HRCNFG2_CTLMODEDBRED_S   2U
#define EPWM_HRCNFG2_CTLMODEDBRED_M   0xCU    // DBRED Control Mode Select Bits
#define EPWM_HRCNFG2_CTLMODEDBFED_S   4U
#define EPWM_HRCNFG2_CTLMODEDBFED_M   0x30U   // DBFED Control Mode Select Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPCTL register
//
//*************************************************************************************************
#define EPWM_HRPCTL_HRPE            0x1U    // High Resolution Period Enable
#define EPWM_HRPCTL_PWMSYNCSEL      0x2U    // EPWMSYNCPER Source Select
#define EPWM_HRPCTL_TBPHSHRLOADE    0x4U    // TBPHSHR Load Enable
#define EPWM_HRPCTL_PWMSYNCSELX_S   4U
#define EPWM_HRPCTL_PWMSYNCSELX_M   0x70U   // EPWMSYNCPER Extended Source Select Bit:

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRREM register
//
//*************************************************************************************************
#define EPWM_TRREM_TRREM_S   0U
#define EPWM_TRREM_TRREM_M   0x7FFU   // HRPWM Remainder Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL register
//
//*************************************************************************************************
#define EPWM_GLDCTL_GLD         0x1U      // Global Shadow to Active load event control
#define EPWM_GLDCTL_GLDMODE_S   1U
#define EPWM_GLDCTL_GLDMODE_M   0x1EU     // Shadow to Active Global Load Pulse Selection
#define EPWM_GLDCTL_OSHTMODE    0x20U     // One Shot Load mode control bit
#define EPWM_GLDCTL_GLDPRD_S    7U
#define EPWM_GLDCTL_GLDPRD_M    0x380U    // Global Load Strobe Period Select Register
#define EPWM_GLDCTL_GLDCNT_S    10U
#define EPWM_GLDCTL_GLDCNT_M    0x1C00U   // Global Load Strobe Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCFG register
//
//*************************************************************************************************
#define EPWM_GLDCFG_TBPRD_TBPRDHR    0x1U     // Global load event configuration for TBPRD:TBPRDHR
#define EPWM_GLDCFG_CMPA_CMPAHR      0x2U     // Global load event configuration for CMPA:CMPAHR
#define EPWM_GLDCFG_CMPB_CMPBHR      0x4U     // Global load event configuration for CMPB:CMPBHR
#define EPWM_GLDCFG_CMPC             0x8U     // Global load event configuration for CMPC
#define EPWM_GLDCFG_CMPD             0x10U    // Global load event configuration for CMPD
#define EPWM_GLDCFG_DBRED_DBREDHR    0x20U    // Global load event configuration for DBRED:DBREDHR
#define EPWM_GLDCFG_DBFED_DBFEDHR    0x40U    // Global load event configuration for DBFED:DBFEDHR
#define EPWM_GLDCFG_DBCTL            0x80U    // Global load event configuration for DBCTL
#define EPWM_GLDCFG_AQCTLA_AQCTLA2   0x100U   // Global load event configuration for AQCTLA/A2
#define EPWM_GLDCFG_AQCTLB_AQCTLB2   0x200U   // Global load event configuration for AQCTLB/B2
#define EPWM_GLDCFG_AQCSFRC          0x400U   // Global load event configuration for AQCSFRC

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMXLINK register
//
//*************************************************************************************************
#define EPWM_XLINK_TBPRDLINK_S     0U
#define EPWM_XLINK_TBPRDLINK_M     0x1FU         // TBPRD:TBPRDHR  Link
#define EPWM_XLINK_CMPALINK_S      5U
#define EPWM_XLINK_CMPALINK_M      0x3E0U        // CMPA:CMPAHR Link
#define EPWM_XLINK_CMPBLINK_S      10U
#define EPWM_XLINK_CMPBLINK_M      0x7C00U       // CMPB:CMPBHR Link
#define EPWM_XLINK_CMPCLINK_S      16U
#define EPWM_XLINK_CMPCLINK_M      0x1F0000U     // CMPC Link
#define EPWM_XLINK_CMPDLINK_S      21U
#define EPWM_XLINK_CMPDLINK_M      0x3E00000U    // CMPD Link
#define EPWM_XLINK_GLDCTL2LINK_S   26U
#define EPWM_XLINK_GLDCTL2LINK_M   0x7C000000U   // GLDCTL2 Link

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMXLINK2 register
//
//*************************************************************************************************
#define EPWM_XLINK2_DBREDLINK_S   0U
#define EPWM_XLINK2_DBREDLINK_M   0x1FU    // DBRED:DBREDHR Link
#define EPWM_XLINK2_DBFEDLINK_S   5U
#define EPWM_XLINK2_DBFEDLINK_M   0x3E0U   // DBFED:DBFEDHR Link

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLA register
//
//*************************************************************************************************
#define EPWM_AQCTLA_ZRO_S   0U
#define EPWM_AQCTLA_ZRO_M   0x3U     // Action Counter = Zero
#define EPWM_AQCTLA_PRD_S   2U
#define EPWM_AQCTLA_PRD_M   0xCU     // Action Counter = Period
#define EPWM_AQCTLA_CAU_S   4U
#define EPWM_AQCTLA_CAU_M   0x30U    // Action Counter = Compare A Up
#define EPWM_AQCTLA_CAD_S   6U
#define EPWM_AQCTLA_CAD_M   0xC0U    // Action Counter = Compare A Down
#define EPWM_AQCTLA_CBU_S   8U
#define EPWM_AQCTLA_CBU_M   0x300U   // Action Counter = Compare B Up
#define EPWM_AQCTLA_CBD_S   10U
#define EPWM_AQCTLA_CBD_M   0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLA2 register
//
//*************************************************************************************************
#define EPWM_AQCTLA2_T1U_S   0U
#define EPWM_AQCTLA2_T1U_M   0x3U    // Action when event occurs on T1 in UP-Count
#define EPWM_AQCTLA2_T1D_S   2U
#define EPWM_AQCTLA2_T1D_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define EPWM_AQCTLA2_T2U_S   4U
#define EPWM_AQCTLA2_T2U_M   0x30U   // Action when event occurs on T2 in UP-Count
#define EPWM_AQCTLA2_T2D_S   6U
#define EPWM_AQCTLA2_T2D_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLB register
//
//*************************************************************************************************
#define EPWM_AQCTLB_ZRO_S   0U
#define EPWM_AQCTLB_ZRO_M   0x3U     // Action Counter = Zero
#define EPWM_AQCTLB_PRD_S   2U
#define EPWM_AQCTLB_PRD_M   0xCU     // Action Counter = Period
#define EPWM_AQCTLB_CAU_S   4U
#define EPWM_AQCTLB_CAU_M   0x30U    // Action Counter = Compare A Up
#define EPWM_AQCTLB_CAD_S   6U
#define EPWM_AQCTLB_CAD_M   0xC0U    // Action Counter = Compare A Down
#define EPWM_AQCTLB_CBU_S   8U
#define EPWM_AQCTLB_CBU_M   0x300U   // Action Counter = Compare B Up
#define EPWM_AQCTLB_CBD_S   10U
#define EPWM_AQCTLB_CBD_M   0xC00U   // Action Counter = Compare B Down

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTLB2 register
//
//*************************************************************************************************
#define EPWM_AQCTLB2_T1U_S   0U
#define EPWM_AQCTLB2_T1U_M   0x3U    // Action when event occurs on T1 in UP-Count
#define EPWM_AQCTLB2_T1D_S   2U
#define EPWM_AQCTLB2_T1D_M   0xCU    // Action when event occurs on T1 in DOWN-Count
#define EPWM_AQCTLB2_T2U_S   4U
#define EPWM_AQCTLB2_T2U_M   0x30U   // Action when event occurs on T2 in UP-Count
#define EPWM_AQCTLB2_T2D_S   6U
#define EPWM_AQCTLB2_T2D_M   0xC0U   // Action when event occurs on T2 in DOWN-Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQSFRC register
//
//*************************************************************************************************
#define EPWM_AQSFRC_ACTSFA_S   0U
#define EPWM_AQSFRC_ACTSFA_M   0x3U    // Action when One-time SW Force A Invoked
#define EPWM_AQSFRC_OTSFA      0x4U    // One-time SW Force A Output
#define EPWM_AQSFRC_ACTSFB_S   3U
#define EPWM_AQSFRC_ACTSFB_M   0x18U   // Action when One-time SW Force B Invoked
#define EPWM_AQSFRC_OTSFB      0x20U   // One-time SW Force A Output
#define EPWM_AQSFRC_RLDCSF_S   6U
#define EPWM_AQSFRC_RLDCSF_M   0xC0U   // Reload from Shadow Options

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCSFRC register
//
//*************************************************************************************************
#define EPWM_AQCSFRC_CSFA_S   0U
#define EPWM_AQCSFRC_CSFA_M   0x3U   // Continuous Software Force on output A
#define EPWM_AQCSFRC_CSFB_S   2U
#define EPWM_AQCSFRC_CSFB_M   0xCU   // Continuous Software Force on output B

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBREDHR register
//
//*************************************************************************************************
#define EPWM_DBREDHR_DBREDHR_S   9U
#define EPWM_DBREDHR_DBREDHR_M   0xFE00U   // DBREDHR High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*************************************************************************************************
#define EPWM_DBRED_DBRED_S   0U
#define EPWM_DBRED_DBRED_M   0x3FFFU   // Rising edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFEDHR register
//
//*************************************************************************************************
#define EPWM_DBFEDHR_DBFEDHR_S   9U
#define EPWM_DBFEDHR_DBFEDHR_M   0xFE00U   // DBFEDHR High Resolution Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*************************************************************************************************
#define EPWM_DBFED_DBFED_S   0U
#define EPWM_DBFED_DBFED_M   0x3FFFU   // Falling edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPHS register
//
//*************************************************************************************************
#define EPWM_TBPHS_TBPHSHR_S   0U
#define EPWM_TBPHS_TBPHSHR_M   0xFFFFU       // Extension Register for HRPWM Phase (8-bits)
#define EPWM_TBPHS_TBPHS_S     16U
#define EPWM_TBPHS_TBPHS_M     0xFFFF0000U   // Phase Offset Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPA register
//
//*************************************************************************************************
#define EPWM_CMPA_CMPAHR_S   0U
#define EPWM_CMPA_CMPAHR_M   0xFFFFU       // Compare A HRPWM Extension Register
#define EPWM_CMPA_CMPA_S     16U
#define EPWM_CMPA_CMPA_M     0xFFFF0000U   // Compare A Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPB register
//
//*************************************************************************************************
#define EPWM_CMPB_CMPBHR_S   0U
#define EPWM_CMPB_CMPBHR_M   0xFFFFU       // Compare B High Resolution Bits
#define EPWM_CMPB_CMPB_S     16U
#define EPWM_CMPB_CMPB_M     0xFFFF0000U   // Compare B Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL2 register
//
//*************************************************************************************************
#define EPWM_GLDCTL2_OSHTLD   0x1U   // Enable reload event in one shot mode
#define EPWM_GLDCTL2_GFRCLD   0x2U   // Force reload event in one shot mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*************************************************************************************************
#define EPWM_TZSEL_CBC1      0x1U      // TZ1 CBC select
#define EPWM_TZSEL_CBC2      0x2U      // TZ2 CBC select
#define EPWM_TZSEL_CBC3      0x4U      // TZ3 CBC select
#define EPWM_TZSEL_CBC4      0x8U      // TZ4 CBC select
#define EPWM_TZSEL_CBC5      0x10U     // TZ5 CBC select
#define EPWM_TZSEL_CBC6      0x20U     // TZ6 CBC select
#define EPWM_TZSEL_DCAEVT2   0x40U     // DCAEVT2 CBC select
#define EPWM_TZSEL_DCBEVT2   0x80U     // DCBEVT2 CBC select
#define EPWM_TZSEL_OSHT1     0x100U    // One-shot TZ1 select
#define EPWM_TZSEL_OSHT2     0x200U    // One-shot TZ2 select
#define EPWM_TZSEL_OSHT3     0x400U    // One-shot TZ3 select
#define EPWM_TZSEL_OSHT4     0x800U    // One-shot TZ4 select
#define EPWM_TZSEL_OSHT5     0x1000U   // One-shot TZ5 select
#define EPWM_TZSEL_OSHT6     0x2000U   // One-shot TZ6 select
#define EPWM_TZSEL_DCAEVT1   0x4000U   // One-shot DCAEVT1 select
#define EPWM_TZSEL_DCBEVT1   0x8000U   // One-shot DCBEVT1 select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL2 register
//
//*************************************************************************************************
#define EPWM_TZSEL2_CAPEVTCBC   0x1U     // CAPEVT CBC select
#define EPWM_TZSEL2_CAPEVTOST   0x100U   // CAPEVT One-shot select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZDCSEL register
//
//*************************************************************************************************
#define EPWM_TZDCSEL_DCAEVT1_S   0U
#define EPWM_TZDCSEL_DCAEVT1_M   0x7U     // Digital Compare Output A Event 1
#define EPWM_TZDCSEL_DCAEVT2_S   3U
#define EPWM_TZDCSEL_DCAEVT2_M   0x38U    // Digital Compare Output A Event 2
#define EPWM_TZDCSEL_DCBEVT1_S   6U
#define EPWM_TZDCSEL_DCBEVT1_M   0x1C0U   // Digital Compare Output B Event 1
#define EPWM_TZDCSEL_DCBEVT2_S   9U
#define EPWM_TZDCSEL_DCBEVT2_M   0xE00U   // Digital Compare Output B Event 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL register
//
//*************************************************************************************************
#define EPWM_TZCTL_TZA_S       0U
#define EPWM_TZCTL_TZA_M       0x3U     // TZ1 to TZ6 Trip Action On EPWMxA
#define EPWM_TZCTL_TZB_S       2U
#define EPWM_TZCTL_TZB_M       0xCU     // TZ1 to TZ6 Trip Action On EPWMxB
#define EPWM_TZCTL_DCAEVT1_S   4U
#define EPWM_TZCTL_DCAEVT1_M   0x30U    // EPWMxA action on DCAEVT1
#define EPWM_TZCTL_DCAEVT2_S   6U
#define EPWM_TZCTL_DCAEVT2_M   0xC0U    // EPWMxA action on DCAEVT2
#define EPWM_TZCTL_DCBEVT1_S   8U
#define EPWM_TZCTL_DCBEVT1_M   0x300U   // EPWMxB action on DCBEVT1
#define EPWM_TZCTL_DCBEVT2_S   10U
#define EPWM_TZCTL_DCBEVT2_M   0xC00U   // EPWMxB action on DCBEVT2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL2 register
//
//*************************************************************************************************
#define EPWM_TZCTL2_TZAU_S   0U
#define EPWM_TZCTL2_TZAU_M   0x7U      // Trip Action On EPWMxA while Count direction is UP
#define EPWM_TZCTL2_TZAD_S   3U
#define EPWM_TZCTL2_TZAD_M   0x38U     // Trip Action On EPWMxA while Count direction is DOWN
#define EPWM_TZCTL2_TZBU_S   6U
#define EPWM_TZCTL2_TZBU_M   0x1C0U    // Trip Action On EPWMxB while Count direction is UP
#define EPWM_TZCTL2_TZBD_S   9U
#define EPWM_TZCTL2_TZBD_M   0xE00U    // Trip Action On EPWMxB while Count direction is DOWN
#define EPWM_TZCTL2_ETZE     0x8000U   // TZCTL2 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCA register
//
//*************************************************************************************************
#define EPWM_TZCTLDCA_DCAEVT1U_S   0U
#define EPWM_TZCTLDCA_DCAEVT1U_M   0x7U     // DCAEVT1 Action On EPWMxA while Count direction is UP
#define EPWM_TZCTLDCA_DCAEVT1D_S   3U
#define EPWM_TZCTLDCA_DCAEVT1D_M   0x38U    // DCAEVT1 Action On EPWMxA while Count direction is
                                            // DOWN
#define EPWM_TZCTLDCA_DCAEVT2U_S   6U
#define EPWM_TZCTLDCA_DCAEVT2U_M   0x1C0U   // DCAEVT2 Action On EPWMxA while Count direction is UP
#define EPWM_TZCTLDCA_DCAEVT2D_S   9U
#define EPWM_TZCTLDCA_DCAEVT2D_M   0xE00U   // DCAEVT2 Action On EPWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTLDCB register
//
//*************************************************************************************************
#define EPWM_TZCTLDCB_DCBEVT1U_S   0U
#define EPWM_TZCTLDCB_DCBEVT1U_M   0x7U     // DCBEVT1 Action On EPWMxA while Count direction is UP
#define EPWM_TZCTLDCB_DCBEVT1D_S   3U
#define EPWM_TZCTLDCB_DCBEVT1D_M   0x38U    // DCBEVT1 Action On EPWMxA while Count direction is
                                            // DOWN
#define EPWM_TZCTLDCB_DCBEVT2U_S   6U
#define EPWM_TZCTLDCB_DCBEVT2U_M   0x1C0U   // DCBEVT2 Action On EPWMxA while Count direction is UP
#define EPWM_TZCTLDCB_DCBEVT2D_S   9U
#define EPWM_TZCTLDCB_DCBEVT2D_M   0xE00U   // DCBEVT2 Action On EPWMxA while Count direction is
                                            // DOWN

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZEINT register
//
//*************************************************************************************************
#define EPWM_TZEINT_CBC       0x2U    // Trip Zones Cycle By Cycle Int Enable
#define EPWM_TZEINT_OST       0x4U    // Trip Zones One Shot Int Enable
#define EPWM_TZEINT_DCAEVT1   0x8U    // Digital Compare A Event 1 Int Enable
#define EPWM_TZEINT_DCAEVT2   0x10U   // Digital Compare A Event 2 Int Enable
#define EPWM_TZEINT_DCBEVT1   0x20U   // Digital Compare B Event 1 Int Enable
#define EPWM_TZEINT_DCBEVT2   0x40U   // Digital Compare B Event 2 Int Enable
#define EPWM_TZEINT_CAPEVT    0x80U   // Capture Eveent Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZFLG register
//
//*************************************************************************************************
#define EPWM_TZFLG_INT       0x1U    // Global Int Status Flag
#define EPWM_TZFLG_CBC       0x2U    // Trip Zones Cycle By Cycle Flag
#define EPWM_TZFLG_OST       0x4U    // Trip Zones One Shot Flag
#define EPWM_TZFLG_DCAEVT1   0x8U    // Digital Compare A Event 1 Flag
#define EPWM_TZFLG_DCAEVT2   0x10U   // Digital Compare A Event 2 Flag
#define EPWM_TZFLG_DCBEVT1   0x20U   // Digital Compare B Event 1 Flag
#define EPWM_TZFLG_DCBEVT2   0x40U   // Digital Compare B Event 2 Flag
#define EPWM_TZFLG_CAPEVT    0x80U   // Capture Event Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCFLG register
//
//*************************************************************************************************
#define EPWM_TZCBCFLG_CBC1      0x1U     // Latched Status Flag for CBC1 Trip Latch
#define EPWM_TZCBCFLG_CBC2      0x2U     // Latched Status Flag for CBC2 Trip Latch
#define EPWM_TZCBCFLG_CBC3      0x4U     // Latched Status Flag for CBC3 Trip Latch
#define EPWM_TZCBCFLG_CBC4      0x8U     // Latched Status Flag for CBC4 Trip Latch
#define EPWM_TZCBCFLG_CBC5      0x10U    // Latched Status Flag for CBC5 Trip Latch
#define EPWM_TZCBCFLG_CBC6      0x20U    // Latched Status Flag for CBC6 Trip Latch
#define EPWM_TZCBCFLG_DCAEVT2   0x40U    // Latched Status Flag for Digital Compare Output A Event
                                         // 2
#define EPWM_TZCBCFLG_DCBEVT2   0x80U    // Latched Status Flag for Digital Compare Output B Event
                                         // 2
#define EPWM_TZCBCFLG_CAPEVT    0x100U   // Capture Event Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZOSTFLG register
//
//*************************************************************************************************
#define EPWM_TZOSTFLG_OST1      0x1U     // Latched Status Flag for OST1 Trip Latch
#define EPWM_TZOSTFLG_OST2      0x2U     // Latched Status Flag for OST2 Trip Latch
#define EPWM_TZOSTFLG_OST3      0x4U     // Latched Status Flag for OST3 Trip Latch
#define EPWM_TZOSTFLG_OST4      0x8U     // Latched Status Flag for OST4 Trip Latch
#define EPWM_TZOSTFLG_OST5      0x10U    // Latched Status Flag for OST5 Trip Latch
#define EPWM_TZOSTFLG_OST6      0x20U    // Latched Status Flag for OST6 Trip Latch
#define EPWM_TZOSTFLG_DCAEVT1   0x40U    // Latched Status Flag for Digital Compare Output A Event
                                         // 1
#define EPWM_TZOSTFLG_DCBEVT1   0x80U    // Latched Status Flag for Digital Compare Output B Event
                                         // 1
#define EPWM_TZOSTFLG_CAPEVT    0x100U   // Capture Event Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCLR register
//
//*************************************************************************************************
#define EPWM_TZCLR_INT          0x1U      // Global Interrupt Clear Flag
#define EPWM_TZCLR_CBC          0x2U      // Cycle-By-Cycle Flag Clear
#define EPWM_TZCLR_OST          0x4U      // One-Shot Flag Clear
#define EPWM_TZCLR_DCAEVT1      0x8U      // DCAVET1 Flag Clear
#define EPWM_TZCLR_DCAEVT2      0x10U     // DCAEVT2 Flag Clear
#define EPWM_TZCLR_DCBEVT1      0x20U     // DCBEVT1 Flag Clear
#define EPWM_TZCLR_DCBEVT2      0x40U     // DCBEVT2 Flag Clear
#define EPWM_TZCLR_CAPEVT       0x80U     // Capture Event Clear
#define EPWM_TZCLR_CBCPULSE_S   14U
#define EPWM_TZCLR_CBCPULSE_M   0xC000U   // Clear Pulse for CBC Trip Latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCCLR register
//
//*************************************************************************************************
#define EPWM_TZCBCCLR_CBC1      0x1U     // Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch
#define EPWM_TZCBCCLR_CBC2      0x2U     // Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch
#define EPWM_TZCBCCLR_CBC3      0x4U     // Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch
#define EPWM_TZCBCCLR_CBC4      0x8U     // Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch
#define EPWM_TZCBCCLR_CBC5      0x10U    // Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch
#define EPWM_TZCBCCLR_CBC6      0x20U    // Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch
#define EPWM_TZCBCCLR_DCAEVT2   0x40U    // Clear Flag forDCAEVT2 selected for CBC
#define EPWM_TZCBCCLR_DCBEVT2   0x80U    // Clear Flag for DCBEVT2 selected for CBC
#define EPWM_TZCBCCLR_CAPEVT    0x100U   // Clear Flag for CAPEVT selected for CBC

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZOSTCLR register
//
//*************************************************************************************************
#define EPWM_TZOSTCLR_OST1      0x1U     // Clear Flag for Oneshot (OST1) Trip Latch
#define EPWM_TZOSTCLR_OST2      0x2U     // Clear Flag for Oneshot (OST2) Trip Latch
#define EPWM_TZOSTCLR_OST3      0x4U     // Clear Flag for Oneshot (OST3) Trip Latch
#define EPWM_TZOSTCLR_OST4      0x8U     // Clear Flag for Oneshot (OST4) Trip Latch
#define EPWM_TZOSTCLR_OST5      0x10U    // Clear Flag for Oneshot (OST5) Trip Latch
#define EPWM_TZOSTCLR_OST6      0x20U    // Clear Flag for Oneshot (OST6) Trip Latch
#define EPWM_TZOSTCLR_DCAEVT1   0x40U    // Clear Flag for DCAEVT1 selected for OST
#define EPWM_TZOSTCLR_DCBEVT1   0x80U    // Clear Flag for DCBEVT1 selected for OST
#define EPWM_TZOSTCLR_CAPEVT    0x100U   // Clear Flag for CAPEVT selected for OST

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZFRC register
//
//*************************************************************************************************
#define EPWM_TZFRC_CBC       0x2U    // Force Trip Zones Cycle By Cycle Event
#define EPWM_TZFRC_OST       0x4U    // Force Trip Zones One Shot Event
#define EPWM_TZFRC_DCAEVT1   0x8U    // Force Digital Compare A Event 1
#define EPWM_TZFRC_DCAEVT2   0x10U   // Force Digital Compare A Event 2
#define EPWM_TZFRC_DCBEVT1   0x20U   // Force Digital Compare B Event 1
#define EPWM_TZFRC_DCBEVT2   0x40U   // Force Digital Compare B Event 2
#define EPWM_TZFRC_CAPEVT    0x80U   // Force Capture Event

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZTRIPOUTSEL register
//
//*************************************************************************************************
#define EPWM_TZTRIPOUTSEL_OST       0x1U      // OST TRIPOUT select
#define EPWM_TZTRIPOUTSEL_CBC       0x2U      // CBC TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ1       0x4U      // TZ1 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ2       0x8U      // TZ2 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ3       0x10U     // TZ3 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ4       0x20U     // TZ4 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ5       0x40U     // TZ5 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_TZ6       0x80U     // TZ6 TRIPOUT select
#define EPWM_TZTRIPOUTSEL_DCAEVT1   0x100U    // DCAEVT1.force TRIPOUT select
#define EPWM_TZTRIPOUTSEL_DCAEVT2   0x200U    // DCAEVT2.force TRIPOUT select
#define EPWM_TZTRIPOUTSEL_DCBEVT1   0x400U    // DCBEVT1.force TRIPOUT select
#define EPWM_TZTRIPOUTSEL_DCBEVT2   0x800U    // DCBEVT2.force TRIPOUT select
#define EPWM_TZTRIPOUTSEL_CAPEVT    0x1000U   // CAPEVT TRIPOUT select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSEL register
//
//*************************************************************************************************
#define EPWM_ETSEL_INTSEL_S     0U
#define EPWM_ETSEL_INTSEL_M     0x7U      // EPWMxINTn Select
#define EPWM_ETSEL_INTEN        0x8U      // EPWMxINTn Enable
#define EPWM_ETSEL_SOCASELCMP   0x10U     // EPWMxSOCA Compare Select
#define EPWM_ETSEL_SOCBSELCMP   0x20U     // EPWMxSOCB Compare Select
#define EPWM_ETSEL_INTSELCMP    0x40U     // EPWMxINT Compare Select
#define EPWM_ETSEL_SOCASEL_S    8U
#define EPWM_ETSEL_SOCASEL_M    0x700U    // Start of Conversion A Select
#define EPWM_ETSEL_SOCAEN       0x800U    // Start of Conversion A Enable
#define EPWM_ETSEL_SOCBSEL_S    12U
#define EPWM_ETSEL_SOCBSEL_M    0x7000U   // Start of Conversion B Select
#define EPWM_ETSEL_SOCBEN       0x8000U   // Start of Conversion B Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETPS register
//
//*************************************************************************************************
#define EPWM_ETPS_INTPRD_S    0U
#define EPWM_ETPS_INTPRD_M    0x3U      // EPWMxINTn Period Select
#define EPWM_ETPS_INTCNT_S    2U
#define EPWM_ETPS_INTCNT_M    0xCU      // EPWMxINTn Counter Register
#define EPWM_ETPS_INTPSSEL    0x10U     // EPWMxINTn Pre-Scale Selection Bits
#define EPWM_ETPS_SOCPSSEL    0x20U     // EPWMxSOC A/B  Pre-Scale Selection Bits
#define EPWM_ETPS_SOCAPRD_S   8U
#define EPWM_ETPS_SOCAPRD_M   0x300U    // EPWMxSOCA Period Select
#define EPWM_ETPS_SOCACNT_S   10U
#define EPWM_ETPS_SOCACNT_M   0xC00U    // EPWMxSOCA Counter Register
#define EPWM_ETPS_SOCBPRD_S   12U
#define EPWM_ETPS_SOCBPRD_M   0x3000U   // EPWMxSOCB Period Select
#define EPWM_ETPS_SOCBCNT_S   14U
#define EPWM_ETPS_SOCBCNT_M   0xC000U   // EPWMxSOCB Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETFLG register
//
//*************************************************************************************************
#define EPWM_ETFLG_INT    0x1U   // EPWMxINTn Flag
#define EPWM_ETFLG_SOCA   0x4U   // EPWMxSOCA Flag
#define EPWM_ETFLG_SOCB   0x8U   // EPWMxSOCB Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCLR register
//
//*************************************************************************************************
#define EPWM_ETCLR_INT    0x1U   // EPWMxINTn Clear
#define EPWM_ETCLR_SOCA   0x4U   // EPWMxSOCA Clear
#define EPWM_ETCLR_SOCB   0x8U   // EPWMxSOCB Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETFRC register
//
//*************************************************************************************************
#define EPWM_ETFRC_INT    0x1U   // EPWMxINTn Force
#define EPWM_ETFRC_SOCA   0x4U   // EPWMxSOCA Force
#define EPWM_ETFRC_SOCB   0x8U   // EPWMxSOCB Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETINTPS register
//
//*************************************************************************************************
#define EPWM_ETINTPS_INTPRD2_S   0U
#define EPWM_ETINTPS_INTPRD2_M   0xFU    // EPWMxINTn Period Select
#define EPWM_ETINTPS_INTCNT2_S   4U
#define EPWM_ETINTPS_INTCNT2_M   0xF0U   // EPWMxINTn Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSOCPS register
//
//*************************************************************************************************
#define EPWM_ETSOCPS_SOCAPRD2_S   0U
#define EPWM_ETSOCPS_SOCAPRD2_M   0xFU      // EPWMxSOCA Period Select
#define EPWM_ETSOCPS_SOCACNT2_S   4U
#define EPWM_ETSOCPS_SOCACNT2_M   0xF0U     // EPWMxSOCA Counter Register
#define EPWM_ETSOCPS_SOCBPRD2_S   8U
#define EPWM_ETSOCPS_SOCBPRD2_M   0xF00U    // EPWMxSOCB Period Select
#define EPWM_ETSOCPS_SOCBCNT2_S   12U
#define EPWM_ETSOCPS_SOCBCNT2_M   0xF000U   // EPWMxSOCB Counter Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNTINITCTL register
//
//*************************************************************************************************
#define EPWM_ETCNTINITCTL_INTINITFRC    0x400U    // EPWMxINT Counter Initialization Force
#define EPWM_ETCNTINITCTL_SOCAINITFRC   0x800U    // EPWMxSOCA Counter Initialization Force
#define EPWM_ETCNTINITCTL_SOCBINITFRC   0x1000U   // EPWMxSOCB Counter Initialization Force
#define EPWM_ETCNTINITCTL_INTINITEN     0x2000U   // EPWMxINT Counter Initialization Enable
#define EPWM_ETCNTINITCTL_SOCAINITEN    0x4000U   // EPWMxSOCA Counter Initialization Enable
#define EPWM_ETCNTINITCTL_SOCBINITEN    0x8000U   // EPWMxSOCB Counter Initialization Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNTINIT register
//
//*************************************************************************************************
#define EPWM_ETCNTINIT_INTINIT_S    0U
#define EPWM_ETCNTINIT_INTINIT_M    0xFU     // EPWMxINT Counter Initialization Bits
#define EPWM_ETCNTINIT_SOCAINIT_S   4U
#define EPWM_ETCNTINIT_SOCAINIT_M   0xF0U    // EPWMxSOCA Counter Initialization Bits
#define EPWM_ETCNTINIT_SOCBINIT_S   8U
#define EPWM_ETCNTINIT_SOCBINIT_M   0xF00U   // EPWMxSOCB Counter Initialization Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETINTMIXEN register
//
//*************************************************************************************************
#define EPWM_ETINTMIXEN_ZRO       0x1U     // Zero match enable to ETINTMIX
#define EPWM_ETINTMIXEN_PRD       0x2U     // Period match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CAU       0x4U     // CMPA up-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CAD       0x8U     // CMPA down-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CBU       0x10U    // CMPB up-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CBD       0x20U    // CMPB down-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CCU       0x40U    // CMPC up-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CCD       0x80U    // CMPC down-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CDU       0x100U   // CMPD up-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_CDD       0x200U   // CMPD down-count match enable to ETINTMIX
#define EPWM_ETINTMIXEN_DCAEVT1   0x400U   // DCAEVT1.inter enable to ETINTMIX

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSOCAMIXEN register
//
//*************************************************************************************************
#define EPWM_ETSOCAMIXEN_ZRO       0x1U     // Zero match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_PRD       0x2U     // Period match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CAU       0x4U     // CMPA up-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CAD       0x8U     // CMPA down-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CBU       0x10U    // CMPB up-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CBD       0x20U    // CMPB down-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CCU       0x40U    // CMPC up-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CCD       0x80U    // CMPC down-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CDU       0x100U   // CMPD up-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_CDD       0x200U   // CMPD down-count match enable to ETSOCAMIX
#define EPWM_ETSOCAMIXEN_DCAEVT1   0x400U   // DCAEVT1.inter enable to ETSOCAMIX

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSOCBMIXEN register
//
//*************************************************************************************************
#define EPWM_ETSOCBMIXEN_ZRO       0x1U     // Zero match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_PRD       0x2U     // Period match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CAU       0x4U     // CMPA up-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CAD       0x8U     // CMPA down-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CBU       0x10U    // CMPB up-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CBD       0x20U    // CMPB down-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CCU       0x40U    // CMPC up-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CCD       0x80U    // CMPC down-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CDU       0x100U   // CMPD up-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_CDD       0x200U   // CMPD down-count match enable to ETSOCBMIX
#define EPWM_ETSOCBMIXEN_DCBEVT1   0x400U   // DCBEVT1.inter enable to ETSOCBMIX

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCTRIPSEL register
//
//*************************************************************************************************
#define EPWM_DCTRIPSEL_DCAHCOMPSEL_S   0U
#define EPWM_DCTRIPSEL_DCAHCOMPSEL_M   0xFU      // Digital Compare A High COMP Input Select
#define EPWM_DCTRIPSEL_DCALCOMPSEL_S   4U
#define EPWM_DCTRIPSEL_DCALCOMPSEL_M   0xF0U     // Digital Compare A Low COMP Input Select
#define EPWM_DCTRIPSEL_DCBHCOMPSEL_S   8U
#define EPWM_DCTRIPSEL_DCBHCOMPSEL_M   0xF00U    // Digital Compare B High COMP Input Select
#define EPWM_DCTRIPSEL_DCBLCOMPSEL_S   12U
#define EPWM_DCTRIPSEL_DCBLCOMPSEL_M   0xF000U   // Digital Compare B Low COMP Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCACTL register
//
//*************************************************************************************************
#define EPWM_DCACTL_EVT1SRCSEL        0x1U      // DCAEVT1 Source Signal
#define EPWM_DCACTL_EVT1FRCSYNCSEL    0x2U      // DCAEVT1 Force Sync Signal
#define EPWM_DCACTL_EVT1SOCE          0x4U      // DCAEVT1 SOC Enable
#define EPWM_DCACTL_EVT1SYNCE         0x8U      // DCAEVT1 SYNC Enable
#define EPWM_DCACTL_EVT1LATSEL        0x10U     // DCAEVT1 Latched signal select
#define EPWM_DCACTL_EVT1LATCLRSEL_S   5U
#define EPWM_DCACTL_EVT1LATCLRSEL_M   0x60U     // DCAEVT1 Latched clear source select
#define EPWM_DCACTL_EVT1LAT           0x80U     // Indicates the status of DCAEVT1LAT signal.
#define EPWM_DCACTL_EVT2SRCSEL        0x100U    // DCAEVT2 Source Signal
#define EPWM_DCACTL_EVT2FRCSYNCSEL    0x200U    // DCAEVT2 Force Sync Signal
#define EPWM_DCACTL_EVT2LATSEL        0x1000U   // DCAEVT2 Latched signal select
#define EPWM_DCACTL_EVT2LATCLRSEL_S   13U
#define EPWM_DCACTL_EVT2LATCLRSEL_M   0x6000U   // DCAEVT2 Latched clear source select
#define EPWM_DCACTL_EVT2LAT           0x8000U   // Indicates the status of DCAEVT2LAT signal.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBCTL register
//
//*************************************************************************************************
#define EPWM_DCBCTL_EVT1SRCSEL        0x1U      // DCBEVT1 Source Signal
#define EPWM_DCBCTL_EVT1FRCSYNCSEL    0x2U      // DCBEVT1 Force Sync Signal
#define EPWM_DCBCTL_EVT1SOCE          0x4U      // DCBEVT1 SOC Enable
#define EPWM_DCBCTL_EVT1SYNCE         0x8U      // DCBEVT1 SYNC Enable
#define EPWM_DCBCTL_EVT1LATSEL        0x10U     // DCBEVT1 Latched signal select
#define EPWM_DCBCTL_EVT1LATCLRSEL_S   5U
#define EPWM_DCBCTL_EVT1LATCLRSEL_M   0x60U     // DCBEVT1 Latched clear source select
#define EPWM_DCBCTL_EVT1LAT           0x80U     // Indicates the status of DCBEVT1LAT signal.
#define EPWM_DCBCTL_EVT2SRCSEL        0x100U    // DCBEVT2 Source Signal
#define EPWM_DCBCTL_EVT2FRCSYNCSEL    0x200U    // DCBEVT2 Force Sync Signal
#define EPWM_DCBCTL_EVT2LATSEL        0x1000U   // DCBEVT2 Latched signal select
#define EPWM_DCBCTL_EVT2LATCLRSEL_S   13U
#define EPWM_DCBCTL_EVT2LATCLRSEL_M   0x6000U   // DCBEVT2 Latched clear source select
#define EPWM_DCBCTL_EVT2LAT           0x8000U   // Indicates the status of DCBEVT2LAT signal.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCFCTL register
//
//*************************************************************************************************
#define EPWM_DCFCTL_SRCSEL_S       0U
#define EPWM_DCFCTL_SRCSEL_M       0x3U      // Filter Block Signal Source Select
#define EPWM_DCFCTL_BLANKE         0x4U      // Blanking Enable/Disable
#define EPWM_DCFCTL_BLANKINV       0x8U      // Blanking Window Inversion
#define EPWM_DCFCTL_PULSESEL_S     4U
#define EPWM_DCFCTL_PULSESEL_M     0x30U     // Pulse Select for Blanking & Capture Alignment
#define EPWM_DCFCTL_EDGEFILTSEL    0x40U     // Edge Filter Select
#define EPWM_DCFCTL_EDGEMODE_S     8U
#define EPWM_DCFCTL_EDGEMODE_M     0x300U    // Edge Mode
#define EPWM_DCFCTL_EDGECOUNT_S    10U
#define EPWM_DCFCTL_EDGECOUNT_M    0x1C00U   // Edge Count
#define EPWM_DCFCTL_EDGESTATUS_S   13U
#define EPWM_DCFCTL_EDGESTATUS_M   0xE000U   // Edge Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCAPCTL register
//
//*************************************************************************************************
#define EPWM_DCCAPCTL_CAPE       0x1U      // Counter Capture Enable
#define EPWM_DCCAPCTL_SHDWMODE   0x2U      // Counter Capture Mode
#define EPWM_DCCAPCTL_CAPSTS     0x2000U   // Latched Status Flag for Capture Event
#define EPWM_DCCAPCTL_CAPCLR     0x4000U   // DC Capture Latched Status Clear Flag
#define EPWM_DCCAPCTL_CAPMODE    0x8000U   // Counter Capture Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the BLANKPULSEMIXSEL register
//
//*************************************************************************************************
#define EPWM_BLANKPULSEMIXSEL_ZRO   0x1U     // Zero match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_PRD   0x2U     // Period match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CAU   0x4U     // CMPA up-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CAD   0x8U     // CMPA down-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CBU   0x10U    // CMPB up-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CBD   0x20U    // CMPB down-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CCU   0x40U    // CMPC up-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CCD   0x80U    // CMPC down-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CDU   0x100U   // CMPD up-count match enable to BLANKPULSEMIX
#define EPWM_BLANKPULSEMIXSEL_CDD   0x200U   // CMPD down-count match enable to BLANKPULSEMIX

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCCAPMIXSEL register
//
//*************************************************************************************************
#define EPWM_DCCAPMIXSEL_ZRO   0x1U     // Zero match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_PRD   0x2U     // Period match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CAU   0x4U     // CMPA up-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CAD   0x8U     // CMPA down-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CBU   0x10U    // CMPB up-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CBD   0x20U    // CMPB down-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CCU   0x40U    // CMPC up-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CCD   0x80U    // CMPC down-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CDU   0x100U   // CMPD up-count match enable to DCCAPMIX
#define EPWM_DCCAPMIXSEL_CDD   0x200U   // CMPD down-count match enable to DCCAPMIX

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCAHTRIPSEL register
//
//*************************************************************************************************
#define EPWM_DCAHTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCAH Mux
#define EPWM_DCAHTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCAH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCALTRIPSEL register
//
//*************************************************************************************************
#define EPWM_DCALTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCAL Mux
#define EPWM_DCALTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCAL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBHTRIPSEL register
//
//*************************************************************************************************
#define EPWM_DCBHTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCBH Mux
#define EPWM_DCBHTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCBH Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCBLTRIPSEL register
//
//*************************************************************************************************
#define EPWM_DCBLTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to DCBL Mux
#define EPWM_DCBLTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to DCBL Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAPCTL register
//
//*************************************************************************************************
#define EPWM_CAPCTL_SRCSEL         0x1U     // Capture Logic Input Selection
#define EPWM_CAPCTL_CAPGATEPOL_S   1U
#define EPWM_CAPCTL_CAPGATEPOL_M   0x6U     // Polarity selection for Capture Gate input
#define EPWM_CAPCTL_CAPINPOL       0x8U     // Polarity selection for Capture input
#define EPWM_CAPCTL_PULSECTL       0x10U    // Polarity selection for Capture input
#define EPWM_CAPCTL_FRCLOAD        0x100U   // Capture event force load

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAPGATETRIPSEL register
//
//*************************************************************************************************
#define EPWM_CAPGATETRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to CAPGATE Mux
#define EPWM_CAPGATETRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to CAPGATE Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAPINTRIPSEL register
//
//*************************************************************************************************
#define EPWM_CAPINTRIPSEL_TRIPINPUT1    0x1U      // Trip Input 1 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT2    0x2U      // Trip Input 2 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT3    0x4U      // Trip Input 3 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT4    0x8U      // Trip Input 4 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT5    0x10U     // Trip Input 5 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT6    0x20U     // Trip Input 6 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT7    0x40U     // Trip Input 7 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT8    0x80U     // Trip Input 8 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT9    0x100U    // Trip Input 9 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT10   0x200U    // Trip Input 10 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT11   0x400U    // Trip Input 11 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT12   0x800U    // Trip Input 12 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT14   0x2000U   // Trip Input 14 Select to CAPIN Mux
#define EPWM_CAPINTRIPSEL_TRIPINPUT15   0x4000U   // Trip Input 15 Select to CAPIN Mux

//*************************************************************************************************
//
// The following are defines for the bit fields in the CAPTRIPSEL register
//
//*************************************************************************************************
#define EPWM_CAPTRIPSEL_CAPINCOMPSEL_S     0U
#define EPWM_CAPTRIPSEL_CAPINCOMPSEL_M     0xFU    // CAPIN Comparator Input Select
#define EPWM_CAPTRIPSEL_CAPGATECOMPSEL_S   4U
#define EPWM_CAPTRIPSEL_CAPGATECOMPSEL_M   0xF0U   // CAPGATE Comparator COMP Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMLOCK register
//
//*************************************************************************************************
#define EPWM_LOCK_HRLOCK      0x1U          // HRPWM Register Set Lock
#define EPWM_LOCK_GLLOCK      0x2U          // Global Load Register Set Lock
#define EPWM_LOCK_TZCFGLOCK   0x4U          // TripZone Register Set Lock
#define EPWM_LOCK_TZCLRLOCK   0x8U          // TripZone Clear Register Set Lock
#define EPWM_LOCK_DCLOCK      0x10U         // Digital Compare Register Set Lock
#define EPWM_LOCK_KEY_S       16U
#define EPWM_LOCK_KEY_M       0xFFFF0000U   // Key to write to this register


//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMPCTL1 register
//
//*************************************************************************************************
#define EPWM_XCMPCTL1_XCMPEN          0x1U     // XCMP Compare Register Operation Enable
#define EPWM_XCMPCTL1_XCMPSPLIT       0x2U     // XCMP Register Allocation Options
#define EPWM_XCMPCTL1_XCMPA_ALLOC_S   4U
#define EPWM_XCMPCTL1_XCMPA_ALLOC_M   0xF0U    // XCMPn register allocation for CMPA
#define EPWM_XCMPCTL1_XCMPB_ALLOC_S   8U
#define EPWM_XCMPCTL1_XCMPB_ALLOC_M   0xF00U   // XCMPn register allocation for CMPB

//*************************************************************************************************
//
// The following are defines for the bit fields in the XLOADCTL register
//
//*************************************************************************************************
#define EPWM_XLOADCTL_LOADMODE                    0x4U          // Load mode selection for Shadow
                                                                // registers
#define EPWM_XLOADCTL_SHDWLEVEL_S                 4U
#define EPWM_XLOADCTL_SHDWLEVEL_M                 0x30U         // Shadow Register Level Allocation
                                                                // Options
#define EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_S       8U
#define EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_M       0x300U        // Register Load event count
#define EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_S   10U
#define EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_M   0xC00U        // Register Load event count
#define EPWM_XLOADCTL_RPTBUF2PRD_S                16U
#define EPWM_XLOADCTL_RPTBUF2PRD_M                0x70000U      // Repeat Count Shadow Buffer 2
#define EPWM_XLOADCTL_RPTBUF2CNT_S                20U
#define EPWM_XLOADCTL_RPTBUF2CNT_M                0x700000U     // Repeat Count Status Shadow
                                                                // Buffer 2
#define EPWM_XLOADCTL_RPTBUF3PRD_S                24U
#define EPWM_XLOADCTL_RPTBUF3PRD_M                0x7000000U    // Repeat Count Shadow Buffer 3
#define EPWM_XLOADCTL_RPTBUF3CNT_S                28U
#define EPWM_XLOADCTL_RPTBUF3CNT_M                0x70000000U   // Repeat Count Status Shadow
                                                                // Buffer 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the XLOAD register
//
//*************************************************************************************************
#define EPWM_XLOAD_STARTLD   0x1U   // Enable register loading of shadow buffers
#define EPWM_XLOAD_FRCLD     0x2U   // Force register loading of shadow buffers

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWMXLINKXLOAD register
//
//*************************************************************************************************
#define EPWM_XLINKXLOAD_XLOADLINK_S   0U
#define EPWM_XLINKXLOAD_XLOADLINK_M   0x1FU   // XLOAD  Link Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XREGSHDW1STS register
//
//*************************************************************************************************
#define EPWM_XREGSHDW1STS_XCMP1_SHDW1FULL     0x1U      // XCMP1_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP2_SHDW1FULL     0x2U      // XCMP2_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP3_SHDW1FULL     0x4U      // XCMP3_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP4_SHDW1FULL     0x8U      // XCMP4_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP5_SHDW1FULL     0x10U     // XCMP5_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP6_SHDW1FULL     0x20U     // XCMP6_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP7_SHDW1FULL     0x40U     // XCMP7_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XCMP8_SHDW1FULL     0x80U     // XCMP8_SHDW1 register full Status flag
#define EPWM_XREGSHDW1STS_XTBPRD_SHDW1FULL    0x100U    // XTBPRD_SHDW1 register full Status flag:
#define EPWM_XREGSHDW1STS_CMPC_SHDW1FULL      0x200U    // CMPC_SHDW1 register full Status flag:
#define EPWM_XREGSHDW1STS_CMPD_SHDW1FULL      0x400U    // CMPD_SHDW1 register full Status flag:
#define EPWM_XREGSHDW1STS_XAQCTLA_SHDW1FULL   0x800U    // XAQCTLA_SHDW1 register full Status flag:
#define EPWM_XREGSHDW1STS_XAQCTLB_SHDW1FULL   0x1000U   // XAQCTLB_SHDW1 register full Status flag:
#define EPWM_XREGSHDW1STS_XMAX_SHDW1FULL      0x2000U   // XMINMAX_SHDW1 register full Status
                                                        // flag:MAX field update
#define EPWM_XREGSHDW1STS_XMIN_SHDW1FULL      0x4000U   // XMINMAX_SHDW1 register full Status flag:
                                                        // MIN field update

//*************************************************************************************************
//
// The following are defines for the bit fields in the XREGSHDW2STS register
//
//*************************************************************************************************
#define EPWM_XREGSHDW2STS_XCMP1_SHDW2FULL     0x1U      // XCMP1_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP2_SHDW2FULL     0x2U      // XCMP2_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP3_SHDW2FULL     0x4U      // XCMP3_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP4_SHDW2FULL     0x8U      // XCMP4_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP5_SHDW2FULL     0x10U     // XCMP5_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP6_SHDW2FULL     0x20U     // XCMP6_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP7_SHDW2FULL     0x40U     // XCMP7_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XCMP8_SHDW2FULL     0x80U     // XCMP8_SHDW2 register full Status flag
#define EPWM_XREGSHDW2STS_XTBPRD_SHDW2FULL    0x100U    // XTBPRD_SHDW2 register full Status flag:
#define EPWM_XREGSHDW2STS_CMPC_SHDW2FULL      0x200U    // CMPC_SHDW2 register full Status flag:
#define EPWM_XREGSHDW2STS_CMPD_SHDW2FULL      0x400U    // CMPD_SHDW2 register full Status flag:
#define EPWM_XREGSHDW2STS_XAQCTLA_SHDW2FULL   0x800U    // XAQCTLA_SHDW2 register full Status flag:
#define EPWM_XREGSHDW2STS_XAQCTLB_SHDW2FULL   0x1000U   // XAQCTLB_SHDW2 register full Status flag:
#define EPWM_XREGSHDW2STS_XMAX_SHDW2FULL      0x2000U   // XMINMAX_SHDW2 register full Status
                                                        // flag:MAX field update
#define EPWM_XREGSHDW2STS_XMIN_SHDW2FULL      0x4000U   // XMINMAX_SHDW2 register full Status flag:
                                                        // MIN field update

//*************************************************************************************************
//
// The following are defines for the bit fields in the XREGSHDW3STS register
//
//*************************************************************************************************
#define EPWM_XREGSHDW3STS_XCMP1_SHDW3FULL     0x1U      // XCMP1_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP2_SHDW3FULL     0x2U      // XCMP2_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP3_SHDW3FULL     0x4U      // XCMP3_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP4_SHDW3FULL     0x8U      // XCMP4_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP5_SHDW3FULL     0x10U     // XCMP5_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP6_SHDW3FULL     0x20U     // XCMP6_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP7_SHDW3FULL     0x40U     // XCMP7_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XCMP8_SHDW3FULL     0x80U     // XCMP8_SHDW3 register full Status flag
#define EPWM_XREGSHDW3STS_XTBPRD_SHDW3FULL    0x100U    // XTBPRD_SHDW3 register full Status flag:
#define EPWM_XREGSHDW3STS_CMPC_SHDW3FULL      0x200U    // CMPC_SHDW3 register full Status flag:
#define EPWM_XREGSHDW3STS_CMPD_SHDW3FULL      0x400U    // CMPD_SHDW3 register full Status flag:
#define EPWM_XREGSHDW3STS_XAQCTLA_SHDW3FULL   0x800U    // XAQCTLA_SHDW3 register full Status flag:
#define EPWM_XREGSHDW3STS_XAQCTLB_SHDW3FULL   0x1000U   // XAQCTLB_SHDW3 register full Status flag:
#define EPWM_XREGSHDW3STS_XMAX_SHDW3FULL      0x2000U   // XMINMAX_SHDW3 register full Status
                                                        // flag:MAX field update
#define EPWM_XREGSHDW3STS_XMIN_SHDW3FULL      0x4000U   // XMINMAX_SHDW3 register full Status flag:
                                                        // MIN field update

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP1_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_S   0U
#define EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_M   0xFFFFU       // Additional Compare 1 Active HR
                                                           // Register
#define EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_S     16U
#define EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_M     0xFFFF0000U   // Additional Compare 1 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP2_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_S   0U
#define EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_M   0xFFFFU       // Additional Compare 2 Active HR
                                                           // Register
#define EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_S     16U
#define EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_M     0xFFFF0000U   // Additional Compare 2 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP3_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_S   0U
#define EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_M   0xFFFFU       // Additional Compare 3 Active HR
                                                           // Register
#define EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_S     16U
#define EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_M     0xFFFF0000U   // Additional Compare 3 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP4_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_S   0U
#define EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_M   0xFFFFU       // Additional Compare 4 Active HR
                                                           // Register
#define EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_S     16U
#define EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_M     0xFFFF0000U   // Additional Compare 4 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP5_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_S   0U
#define EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_M   0xFFFFU       // Additional Compare 5 Active HR
                                                           // Register
#define EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_S     16U
#define EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_M     0xFFFF0000U   // Additional Compare 5 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP6_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_S   0U
#define EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_M   0xFFFFU       // Additional Compare 6 Active HR
                                                           // Register
#define EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_S     16U
#define EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_M     0xFFFF0000U   // Additional Compare 6 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP7_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_S   0U
#define EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_M   0xFFFFU       // Additional Compare 7 Active HR
                                                           // Register
#define EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_S     16U
#define EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_M     0xFFFF0000U   // Additional Compare 7 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP8_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_S   0U
#define EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_M   0xFFFFU       // Additional Compare 8 Active HR
                                                           // Register
#define EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_S     16U
#define EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_M     0xFFFF0000U   // Additional Compare 8 Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTBPRD_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_S   0U
#define EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_M   0xFFFFU       // Additional Time Base Period Active
                                                             // HR Register
#define EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_S     16U
#define EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_M     0xFFFF0000U   // Additional Time Base Period Active
                                                             // Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLA_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XAQCTLA_ACTIVE_XCMP1_S   0U
#define EPWM_XAQCTLA_ACTIVE_XCMP1_M   0x3U      // XCMP1 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP2_S   2U
#define EPWM_XAQCTLA_ACTIVE_XCMP2_M   0xCU      // XCMP2 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP3_S   4U
#define EPWM_XAQCTLA_ACTIVE_XCMP3_M   0x30U     // XCMP3 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP4_S   6U
#define EPWM_XAQCTLA_ACTIVE_XCMP4_M   0xC0U     // XCMP4 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP5_S   8U
#define EPWM_XAQCTLA_ACTIVE_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP6_S   10U
#define EPWM_XAQCTLA_ACTIVE_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP7_S   12U
#define EPWM_XAQCTLA_ACTIVE_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLA_ACTIVE_XCMP8_S   14U
#define EPWM_XAQCTLA_ACTIVE_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLB_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XAQCTLB_ACTIVE_XCMP5_S   8U
#define EPWM_XAQCTLB_ACTIVE_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLB_ACTIVE_XCMP6_S   10U
#define EPWM_XAQCTLB_ACTIVE_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLB_ACTIVE_XCMP7_S   12U
#define EPWM_XAQCTLB_ACTIVE_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLB_ACTIVE_XCMP8_S   14U
#define EPWM_XAQCTLB_ACTIVE_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XMINMAX_ACTIVE register
//
//*************************************************************************************************
#define EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_S   0U
#define EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_M   0xFFFFU       // Maximum Valude  for Capture Counter
                                                          // Active Register
#define EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_S   16U
#define EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_M   0xFFFF0000U   // Minimum Valude  for Capture Counter
                                                          // Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP1_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_S   0U
#define EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_M   0xFFFFU       // Additional Compare 1 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP1_SHDW1_XCMP1_SHDW1_S     16U
#define EPWM_XCMP1_SHDW1_XCMP1_SHDW1_M     0xFFFF0000U   // Additional Compare 1 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP2_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_S   0U
#define EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_M   0xFFFFU       // Additional Compare 2 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP2_SHDW1_XCMP2_SHDW1_S     16U
#define EPWM_XCMP2_SHDW1_XCMP2_SHDW1_M     0xFFFF0000U   // Additional Compare 2 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP3_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_S   0U
#define EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_M   0xFFFFU       // Additional Compare 3 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP3_SHDW1_XCMP3_SHDW1_S     16U
#define EPWM_XCMP3_SHDW1_XCMP3_SHDW1_M     0xFFFF0000U   // Additional Compare 3 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP4_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_S   0U
#define EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_M   0xFFFFU       // Additional Compare 4 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP4_SHDW1_XCMP4_SHDW1_S     16U
#define EPWM_XCMP4_SHDW1_XCMP4_SHDW1_M     0xFFFF0000U   // Additional Compare 4 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP5_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_S   0U
#define EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_M   0xFFFFU       // Additional Compare 5 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP5_SHDW1_XCMP5_SHDW1_S     16U
#define EPWM_XCMP5_SHDW1_XCMP5_SHDW1_M     0xFFFF0000U   // Additional Compare 5 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP6_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_S   0U
#define EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_M   0xFFFFU       // Additional Compare 6 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP6_SHDW1_XCMP6_SHDW1_S     16U
#define EPWM_XCMP6_SHDW1_XCMP6_SHDW1_M     0xFFFF0000U   // Additional Compare 6 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP7_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_S   0U
#define EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_M   0xFFFFU       // Additional Compare 7 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP7_SHDW1_XCMP7_SHDW1_S     16U
#define EPWM_XCMP7_SHDW1_XCMP7_SHDW1_M     0xFFFF0000U   // Additional Compare 7 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP8_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_S   0U
#define EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_M   0xFFFFU       // Additional Compare 8 Shadow 1 HR
                                                         // Register
#define EPWM_XCMP8_SHDW1_XCMP8_SHDW1_S     16U
#define EPWM_XCMP8_SHDW1_XCMP8_SHDW1_M     0xFFFF0000U   // Additional Compare 8 Shadow 1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTBPRD_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_S   0U
#define EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_M   0xFFFFU       // Additional Time Base Period Shadow 1
                                                           // HR Register
#define EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_S     16U
#define EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_M     0xFFFF0000U   // Additional Time Base Period Shadow 1
                                                           // Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLA_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XAQCTLA_SHDW1_XCMP1_S   0U
#define EPWM_XAQCTLA_SHDW1_XCMP1_M   0x3U      // XCMP1 Action
#define EPWM_XAQCTLA_SHDW1_XCMP2_S   2U
#define EPWM_XAQCTLA_SHDW1_XCMP2_M   0xCU      // XCMP2 Action
#define EPWM_XAQCTLA_SHDW1_XCMP3_S   4U
#define EPWM_XAQCTLA_SHDW1_XCMP3_M   0x30U     // XCMP3 Action
#define EPWM_XAQCTLA_SHDW1_XCMP4_S   6U
#define EPWM_XAQCTLA_SHDW1_XCMP4_M   0xC0U     // XCMP4 Action
#define EPWM_XAQCTLA_SHDW1_XCMP5_S   8U
#define EPWM_XAQCTLA_SHDW1_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLA_SHDW1_XCMP6_S   10U
#define EPWM_XAQCTLA_SHDW1_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLA_SHDW1_XCMP7_S   12U
#define EPWM_XAQCTLA_SHDW1_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLA_SHDW1_XCMP8_S   14U
#define EPWM_XAQCTLA_SHDW1_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLB_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XAQCTLB_SHDW1_XCMP5_S   8U
#define EPWM_XAQCTLB_SHDW1_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLB_SHDW1_XCMP6_S   10U
#define EPWM_XAQCTLB_SHDW1_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLB_SHDW1_XCMP7_S   12U
#define EPWM_XAQCTLB_SHDW1_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLB_SHDW1_XCMP8_S   14U
#define EPWM_XAQCTLB_SHDW1_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XMINMAX_SHDW1 register
//
//*************************************************************************************************
#define EPWM_XMINMAX_SHDW1_XMAX_SHDW1_S   0U
#define EPWM_XMINMAX_SHDW1_XMAX_SHDW1_M   0xFFFFU       // Maximum Valude  for Capture Counter
                                                        // Active Register
#define EPWM_XMINMAX_SHDW1_XMIN_SHDW1_S   16U
#define EPWM_XMINMAX_SHDW1_XMIN_SHDW1_M   0xFFFF0000U   // Minimum Valude  for Capture Counter
                                                        // Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP1_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_S   0U
#define EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_M   0xFFFFU       // Additional Compare 1 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP1_SHDW2_XCMP1_SHDW2_S     16U
#define EPWM_XCMP1_SHDW2_XCMP1_SHDW2_M     0xFFFF0000U   // Additional Compare 1 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP2_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_S   0U
#define EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_M   0xFFFFU       // Additional Compare 2 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP2_SHDW2_XCMP2_SHDW2_S     16U
#define EPWM_XCMP2_SHDW2_XCMP2_SHDW2_M     0xFFFF0000U   // Additional Compare 2 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP3_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_S   0U
#define EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_M   0xFFFFU       // Additional Compare 3 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP3_SHDW2_XCMP3_SHDW2_S     16U
#define EPWM_XCMP3_SHDW2_XCMP3_SHDW2_M     0xFFFF0000U   // Additional Compare 3 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP4_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_S   0U
#define EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_M   0xFFFFU       // Additional Compare 4 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP4_SHDW2_XCMP4_SHDW2_S     16U
#define EPWM_XCMP4_SHDW2_XCMP4_SHDW2_M     0xFFFF0000U   // Additional Compare 4 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP5_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_S   0U
#define EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_M   0xFFFFU       // Additional Compare 5 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP5_SHDW2_XCMP5_SHDW2_S     16U
#define EPWM_XCMP5_SHDW2_XCMP5_SHDW2_M     0xFFFF0000U   // Additional Compare 5 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP6_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_S   0U
#define EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_M   0xFFFFU       // Additional Compare 6 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP6_SHDW2_XCMP6_SHDW2_S     16U
#define EPWM_XCMP6_SHDW2_XCMP6_SHDW2_M     0xFFFF0000U   // Additional Compare 6 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP7_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_S   0U
#define EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_M   0xFFFFU       // Additional Compare 7 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP7_SHDW2_XCMP7_SHDW2_S     16U
#define EPWM_XCMP7_SHDW2_XCMP7_SHDW2_M     0xFFFF0000U   // Additional Compare 7 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP8_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_S   0U
#define EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_M   0xFFFFU       // Additional Compare 8 Shadow 2 HR
                                                         // Register
#define EPWM_XCMP8_SHDW2_XCMP8_SHDW2_S     16U
#define EPWM_XCMP8_SHDW2_XCMP8_SHDW2_M     0xFFFF0000U   // Additional Compare 8 Shadow 2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTBPRD_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_S   0U
#define EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_M   0xFFFFU       // Additional Time Base Period Shadow 1
                                                           // HR Register
#define EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_S     16U
#define EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_M     0xFFFF0000U   // Additional Time Base Period Shadow 1
                                                           // Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLA_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XAQCTLA_SHDW2_XCMP1_S   0U
#define EPWM_XAQCTLA_SHDW2_XCMP1_M   0x3U      // XCMP1 Action
#define EPWM_XAQCTLA_SHDW2_XCMP2_S   2U
#define EPWM_XAQCTLA_SHDW2_XCMP2_M   0xCU      // XCMP2 Action
#define EPWM_XAQCTLA_SHDW2_XCMP3_S   4U
#define EPWM_XAQCTLA_SHDW2_XCMP3_M   0x30U     // XCMP3 Action
#define EPWM_XAQCTLA_SHDW2_XCMP4_S   6U
#define EPWM_XAQCTLA_SHDW2_XCMP4_M   0xC0U     // XCMP4 Action
#define EPWM_XAQCTLA_SHDW2_XCMP5_S   8U
#define EPWM_XAQCTLA_SHDW2_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLA_SHDW2_XCMP6_S   10U
#define EPWM_XAQCTLA_SHDW2_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLA_SHDW2_XCMP7_S   12U
#define EPWM_XAQCTLA_SHDW2_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLA_SHDW2_XCMP8_S   14U
#define EPWM_XAQCTLA_SHDW2_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLB_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XAQCTLB_SHDW2_XCMP5_S   8U
#define EPWM_XAQCTLB_SHDW2_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLB_SHDW2_XCMP6_S   10U
#define EPWM_XAQCTLB_SHDW2_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLB_SHDW2_XCMP7_S   12U
#define EPWM_XAQCTLB_SHDW2_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLB_SHDW2_XCMP8_S   14U
#define EPWM_XAQCTLB_SHDW2_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XMINMAX_SHDW2 register
//
//*************************************************************************************************
#define EPWM_XMINMAX_SHDW2_XMAX_SHDW2_S   0U
#define EPWM_XMINMAX_SHDW2_XMAX_SHDW2_M   0xFFFFU       // Maximum Valude  for Capture Counter
                                                        // Active Register
#define EPWM_XMINMAX_SHDW2_XMIN_SHDW2_S   16U
#define EPWM_XMINMAX_SHDW2_XMIN_SHDW2_M   0xFFFF0000U   // Minimum Valude  for Capture Counter
                                                        // Active Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP1_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_S   0U
#define EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_M   0xFFFFU       // Additional Compare 1 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP1_SHDW3_XCMP1_SHDW3_S     16U
#define EPWM_XCMP1_SHDW3_XCMP1_SHDW3_M     0xFFFF0000U   // Additional Compare 1 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP2_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_S   0U
#define EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_M   0xFFFFU       // Additional Compare 2 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP2_SHDW3_XCMP2_SHDW3_S     16U
#define EPWM_XCMP2_SHDW3_XCMP2_SHDW3_M     0xFFFF0000U   // Additional Compare 2 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP3_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_S   0U
#define EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_M   0xFFFFU       // Additional Compare 3 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP3_SHDW3_XCMP3_SHDW3_S     16U
#define EPWM_XCMP3_SHDW3_XCMP3_SHDW3_M     0xFFFF0000U   // Additional Compare 3 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP4_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_S   0U
#define EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_M   0xFFFFU       // Additional Compare 4 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP4_SHDW3_XCMP4_SHDW3_S     16U
#define EPWM_XCMP4_SHDW3_XCMP4_SHDW3_M     0xFFFF0000U   // Additional Compare 4 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP5_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_S   0U
#define EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_M   0xFFFFU       // Additional Compare 5 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP5_SHDW3_XCMP5_SHDW3_S     16U
#define EPWM_XCMP5_SHDW3_XCMP5_SHDW3_M     0xFFFF0000U   // Additional Compare 5 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP6_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_S   0U
#define EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_M   0xFFFFU       // Additional Compare 6 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP6_SHDW3_XCMP6_SHDW3_S     16U
#define EPWM_XCMP6_SHDW3_XCMP6_SHDW3_M     0xFFFF0000U   // Additional Compare 6 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP7_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_S   0U
#define EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_M   0xFFFFU       // Additional Compare 7 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP7_SHDW3_XCMP7_SHDW3_S     16U
#define EPWM_XCMP7_SHDW3_XCMP7_SHDW3_M     0xFFFF0000U   // Additional Compare 7 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCMP8_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_S   0U
#define EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_M   0xFFFFU       // Additional Compare 8 Shadow 3 HR
                                                         // Register
#define EPWM_XCMP8_SHDW3_XCMP8_SHDW3_S     16U
#define EPWM_XCMP8_SHDW3_XCMP8_SHDW3_M     0xFFFF0000U   // Additional Compare 8 Shadow 3 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTBPRD_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_S   0U
#define EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_M   0xFFFFU       // Additional Time Base Period Shadow 1
                                                           // HR Register
#define EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_S     16U
#define EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_M     0xFFFF0000U   // Additional Time Base Period Shadow 1
                                                           // Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLA_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XAQCTLA_SHDW3_XCMP1_S   0U
#define EPWM_XAQCTLA_SHDW3_XCMP1_M   0x3U      // XCMP1 Action
#define EPWM_XAQCTLA_SHDW3_XCMP2_S   2U
#define EPWM_XAQCTLA_SHDW3_XCMP2_M   0xCU      // XCMP2 Action
#define EPWM_XAQCTLA_SHDW3_XCMP3_S   4U
#define EPWM_XAQCTLA_SHDW3_XCMP3_M   0x30U     // XCMP3 Action
#define EPWM_XAQCTLA_SHDW3_XCMP4_S   6U
#define EPWM_XAQCTLA_SHDW3_XCMP4_M   0xC0U     // XCMP4 Action
#define EPWM_XAQCTLA_SHDW3_XCMP5_S   8U
#define EPWM_XAQCTLA_SHDW3_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLA_SHDW3_XCMP6_S   10U
#define EPWM_XAQCTLA_SHDW3_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLA_SHDW3_XCMP7_S   12U
#define EPWM_XAQCTLA_SHDW3_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLA_SHDW3_XCMP8_S   14U
#define EPWM_XAQCTLA_SHDW3_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XAQCTLB_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XAQCTLB_SHDW3_XCMP5_S   8U
#define EPWM_XAQCTLB_SHDW3_XCMP5_M   0x300U    // XCMP5 Action
#define EPWM_XAQCTLB_SHDW3_XCMP6_S   10U
#define EPWM_XAQCTLB_SHDW3_XCMP6_M   0xC00U    // XCMP6 Action
#define EPWM_XAQCTLB_SHDW3_XCMP7_S   12U
#define EPWM_XAQCTLB_SHDW3_XCMP7_M   0x3000U   // XCMP7 Action
#define EPWM_XAQCTLB_SHDW3_XCMP8_S   14U
#define EPWM_XAQCTLB_SHDW3_XCMP8_M   0xC000U   // XCMP8 Action

//*************************************************************************************************
//
// The following are defines for the bit fields in the XMINMAX_SHDW3 register
//
//*************************************************************************************************
#define EPWM_XMINMAX_SHDW3_XMAX_SHDW3_S   0U
#define EPWM_XMINMAX_SHDW3_XMAX_SHDW3_M   0xFFFFU       // Maximum Valude  for Capture Counter
                                                        // Active Register
#define EPWM_XMINMAX_SHDW3_XMIN_SHDW3_S   16U
#define EPWM_XMINMAX_SHDW3_XMIN_SHDW3_M   0xFFFF0000U   // Minimum Valude  for Capture Counter
                                                        // Active Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DECTL register
//
//*************************************************************************************************
#define EPWM_DECTL_ENABLE         0x1U      // DE function enable.
#define EPWM_DECTL_MODE           0x2U      // DE Mode
#define EPWM_DECTL_REENTRYDLY_S   8U
#define EPWM_DECTL_REENTRYDLY_M   0xFF00U   // Re-entry delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DECOMPSEL register
//
//*************************************************************************************************
#define EPWM_DECOMPSEL_TRIPL_S   0U
#define EPWM_DECOMPSEL_TRIPL_M   0x3FU       // Comparator TRIPL source select.
#define EPWM_DECOMPSEL_TRIPH_S   16U
#define EPWM_DECOMPSEL_TRIPH_M   0x3F0000U   // Comparator TRIPH source select.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEACTCTL register
//
//*************************************************************************************************
#define EPWM_DEACTCTL_PWMA_S       0U
#define EPWM_DEACTCTL_PWMA_M       0x3U       // Comparator source select.
#define EPWM_DEACTCTL_TRIPSELA     0x4U       // Trip source select on PWMA output
#define EPWM_DEACTCTL_PWMB_S       4U
#define EPWM_DEACTCTL_PWMB_M       0x30U      // Comparator source select.
#define EPWM_DEACTCTL_TRIPSELB     0x40U      // Trip source select on PWMB output
#define EPWM_DEACTCTL_TRIPENABLE   0x10000U   // Enables PWMTRIP condition to bypassDiode emulation
                                              // logic.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DESTS register
//
//*************************************************************************************************
#define EPWM_DESTS_DEACTIVE   0x1U   // Diode Emulation mode active flag.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEFRC register
//
//*************************************************************************************************
#define EPWM_DEFRC_DEACTIVE   0x1U   // Diode Emulation mode active flag force.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DECLR register
//
//*************************************************************************************************
#define EPWM_DECLR_DEACTIVE   0x1U   // Diode Emulation mode active flag clear.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEMONCNT register
//
//*************************************************************************************************
#define EPWM_DEMONCNT_CNT_S   0U
#define EPWM_DEMONCNT_CNT_M   0xFFFFU   // DEACTIVE monitor counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEMONCTL register
//
//*************************************************************************************************
#define EPWM_DEMONCTL_ENABLE   0x1U   // DEACTIVE monitor counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEMONSTEP register
//
//*************************************************************************************************
#define EPWM_DEMONSTEP_INCSTEP_S   0U
#define EPWM_DEMONSTEP_INCSTEP_M   0xFFU       // DE monitor counter increment step.
#define EPWM_DEMONSTEP_DECSTEP_S   16U
#define EPWM_DEMONSTEP_DECSTEP_M   0xFF0000U   // DE monitor counter decrement step.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEMONTHRES register
//
//*************************************************************************************************
#define EPWM_DEMONTHRES_THRESHOLD_S   0U
#define EPWM_DEMONTHRES_THRESHOLD_M   0xFFFFU   // DE monitor counter compare threshold.


//*************************************************************************************************
//
// The following are defines for the bit fields in the MINDBCFG register
//
//*************************************************************************************************
#define EPWM_MINDBCFG_ENABLEA     0x1U         // Minimum dead band logic enable on PWMA
#define EPWM_MINDBCFG_INVERTA     0x4U         // Invert the selected reference signal on PWMA
#define EPWM_MINDBCFG_SELBLOCKA   0x8U         // BLOCK signal source select on PWMA
#define EPWM_MINDBCFG_SELA_S      4U
#define EPWM_MINDBCFG_SELA_M      0xF0U        // Reference source select on PWMA min dead band
                                               // logic.
#define EPWM_MINDBCFG_POLSELA     0x100U       // Select signal for the AND OR logic of PWMA
#define EPWM_MINDBCFG_ENABLEB     0x10000U     // Minimum dead band logic enable on PWMB
#define EPWM_MINDBCFG_INVERTB     0x40000U     // Invert the selected reference signal on PWMB
#define EPWM_MINDBCFG_SELBLOCKB   0x80000U     // BLOCK signal source select on PWMB
#define EPWM_MINDBCFG_SELB_S      20U
#define EPWM_MINDBCFG_SELB_M      0xF00000U    // Reference source select on PWMB min dead band
                                               // logic.
#define EPWM_MINDBCFG_POLSELB     0x1000000U   // Select signal for the AND OR logic of PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the MINDBDLY register
//
//*************************************************************************************************
#define EPWM_MINDBDLY_DELAYA_S   0U
#define EPWM_MINDBDLY_DELAYA_M   0xFFFFU       // Minimum dead band delay on PWMA
#define EPWM_MINDBDLY_DELAYB_S   16U
#define EPWM_MINDBDLY_DELAYB_M   0xFFFF0000U   // Minimum dead band delay on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the LUTCTLA register
//
//*************************************************************************************************
#define EPWM_LUTCTLA_BYPASS      0x1U        // Bypass LUTA
#define EPWM_LUTCTLA_SELXBAR_S   4U
#define EPWM_LUTCTLA_SELXBAR_M   0xF0U       // ICSS XBAR select
#define EPWM_LUTCTLA_LUTDEC0     0x10000U    // LUT output PWMA value on decoding 0
#define EPWM_LUTCTLA_LUTDEC1     0x20000U    // LUT output PWMA value on decoding 1
#define EPWM_LUTCTLA_LUTDEC2     0x40000U    // LUT output PWMA value on decoding 2
#define EPWM_LUTCTLA_LUTDEC3     0x80000U    // LUT output PWMA value on decoding 3
#define EPWM_LUTCTLA_LUTDEC4     0x100000U   // LUT output PWMA value on decoding 4
#define EPWM_LUTCTLA_LUTDEC5     0x200000U   // LUT output PWMA value on decoding 5
#define EPWM_LUTCTLA_LUTDEC6     0x400000U   // LUT output PWMA value on decoding 6
#define EPWM_LUTCTLA_LUTDEC7     0x800000U   // LUT output PWMA value on decoding 7

//*************************************************************************************************
//
// The following are defines for the bit fields in the LUTCTLB register
//
//*************************************************************************************************
#define EPWM_LUTCTLB_BYPASS      0x1U        // Bypass LUTB
#define EPWM_LUTCTLB_SELXBAR_S   4U
#define EPWM_LUTCTLB_SELXBAR_M   0xF0U       // ICSS XBAR select
#define EPWM_LUTCTLB_LUTDEC0     0x10000U    // LUT output PWMB value on decoding 0
#define EPWM_LUTCTLB_LUTDEC1     0x20000U    // LUT output PWMB value on decoding 1
#define EPWM_LUTCTLB_LUTDEC2     0x40000U    // LUT output PWMB value on decoding 2
#define EPWM_LUTCTLB_LUTDEC3     0x80000U    // LUT output PWMB value on decoding 3
#define EPWM_LUTCTLB_LUTDEC4     0x100000U   // LUT output PWMB value on decoding 4
#define EPWM_LUTCTLB_LUTDEC5     0x200000U   // LUT output PWMB value on decoding 5
#define EPWM_LUTCTLB_LUTDEC6     0x400000U   // LUT output PWMB value on decoding 6
#define EPWM_LUTCTLB_LUTDEC7     0x800000U   // LUT output PWMB value on decoding 7



#endif
