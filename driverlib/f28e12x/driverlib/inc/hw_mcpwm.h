//###########################################################################
//
// FILE:    hw_mcpwm.h
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

#ifndef HW_MCPWM_H
#define HW_MCPWM_H

//*************************************************************************************************
//
// The following are defines for the MCPWM register offsets
//
//*************************************************************************************************
#define MCPWM_O_REVISION        0x0U     // IP revision id register
#define MCPWM_O_TBCTL           0x8U     // Time base control register
#define MCPWM_O_TBPRD           0xAU     // Time base period register
#define MCPWM_O_TBPRDS          0xCU     // Time base period shadow register
#define MCPWM_O_TBPHS           0xEU     // Time base phase offset register
#define MCPWM_O_TBSTS           0x10U    // Time base status register
#define MCPWM_O_TBSTSCLR        0x12U    // Time base status clear register
#define MCPWM_O_TBCTR           0x14U    // Time base counter register
#define MCPWM_O_CMPCTL          0x18U    // Counter compare control register
#define MCPWM_O_CMPC            0x20U    // Counter compare C register
#define MCPWM_O_CMPD            0x22U    // Counter compare D register
#define MCPWM_O_CMPCS           0x24U    // Counter compare C shadow register
#define MCPWM_O_CMPDS           0x26U    // Counter compare D shadow register
#define MCPWM_O_AQCTL           0x28U    // Action qualifier control register
#define MCPWM_O_SOCEN           0x30U    // Start of conversion enable
#define MCPWM_O_SOCSEL          0x32U    // Start of conversion selection
#define MCPWM_O_SOCPERIOD       0x34U    // Start of conversion period
#define MCPWM_O_SOCCNT          0x36U    // Start of conversion count
#define MCPWM_O_SOCFLAG         0x38U    // Start of conversion flag
#define MCPWM_O_SOCCLR          0x3AU    // Start of conversion clear
#define MCPWM_O_ETSEL           0x40U    // Event trigger selection
#define MCPWM_O_ETPERIOD        0x42U    // Event trigger period
#define MCPWM_O_ETCNT           0x44U    // Event trigger count
#define MCPWM_O_INTEN           0x48U    // Interrupt enable
#define MCPWM_O_INTFLAG         0x4AU    // Interrupt flag
#define MCPWM_O_INTCLR          0x4CU    // Interrupt clear
#define MCPWM_O_INTFRC          0x4EU    // Interrupt force
#define MCPWM_O_TZSEL           0x50U    // Trip Zone selection
#define MCPWM_O_TZCTL           0x56U    // Trip Zone control
#define MCPWM_O_TZCBCOSTFLAG    0x58U    // Trip zone CBCOST flag
#define MCPWM_O_TZCBCOSTCLR     0x5AU    // Trip zone CBCOST flag clear
#define MCPWM_O_DBCTL           0x60U    // Dead band control register
#define MCPWM_O_DBFED           0x68U    // Dead band fall edge delay
#define MCPWM_O_DBRED           0x6AU    // Dead band rise edge delay
#define MCPWM_O_DBFEDS          0x6CU    // Dead band fall edge delay shadow register
#define MCPWM_O_DBREDS          0x6EU    // Dead band rise edge delay shadow register
#define MCPWM_O_GLDCTL          0x78U    // Global load control register
#define MCPWM_O_GLDOSHTCTL      0x7AU    // Global load one shot control register
#define MCPWM_O_GLDOSHTSTS      0x7CU    // Global load one shot status register
#define MCPWM_O_PWM1_CMPA       0x80U    // PWM1 counter compare A register
#define MCPWM_O_PWM1_CMPAS      0x82U    // PWM1 counter compare A shadow register
#define MCPWM_O_PWM1_CMPB       0x84U    // PWM1 counter compare B register
#define MCPWM_O_PWM1_CMPBS      0x86U    // PWM1 counter compare B shadow register
#define MCPWM_O_PWM1_AQCTLA     0x90U    // PWM1 action qualifier A register
#define MCPWM_O_PWM1_AQCTLAS    0x92U    // PWM1 action qualifier A shadow register
#define MCPWM_O_PWM1_AQCTLB     0x94U    // PWM1 action qualifier B register
#define MCPWM_O_PWM1_AQCTLBS    0x96U    // PWM1 action qualifier B shadow register
#define MCPWM_O_PWM1_AQSFRC     0x98U    // PWM1 action qualifier software force
#define MCPWM_O_PWM1_AQOTSFRC   0x9AU    // PWM1 action qualifier one time software force
#define MCPWM_O_PWM2_CMPA       0x180U   // PWM2 counter compare A register
#define MCPWM_O_PWM2_CMPAS      0x182U   // PWM2 counter compare A shadow register
#define MCPWM_O_PWM2_CMPB       0x184U   // PWM2 counter compare B register
#define MCPWM_O_PWM2_CMPBS      0x186U   // PWM2 counter compare B shadow register
#define MCPWM_O_PWM2_AQCTLA     0x190U   // PWM2 action qualifier A register
#define MCPWM_O_PWM2_AQCTLAS    0x192U   // PWM2 action qualifier A shadow register
#define MCPWM_O_PWM2_AQCTLB     0x194U   // PWM2 action qualifier B register
#define MCPWM_O_PWM2_AQCTLBS    0x196U   // PWM2 action qualifier B shadow register
#define MCPWM_O_PWM2_AQSFRC     0x198U   // PWM2 action qualifier software force
#define MCPWM_O_PWM2_AQOTSFRC   0x19AU   // PWM2 action qualifier one time software force
#define MCPWM_O_PWM3_CMPA       0x280U   // PWM3 counter compare A register
#define MCPWM_O_PWM3_CMPAS      0x282U   // PWM3 counter compare A shadow register
#define MCPWM_O_PWM3_CMPB       0x284U   // PWM3 counter compare B register
#define MCPWM_O_PWM3_CMPBS      0x286U   // PWM3 counter compare B shadow register
#define MCPWM_O_PWM3_AQCTLA     0x290U   // PWM3 action qualifier A register
#define MCPWM_O_PWM3_AQCTLAS    0x292U   // PWM3 action qualifier A shadow register
#define MCPWM_O_PWM3_AQCTLB     0x294U   // PWM3 action qualifier B register
#define MCPWM_O_PWM3_AQCTLBS    0x296U   // PWM3 action qualifier B shadow register
#define MCPWM_O_PWM3_AQSFRC     0x298U   // PWM3 action qualifier software force
#define MCPWM_O_PWM3_AQOTSFRC   0x29AU   // PWM3 action qualifier one time software force

#define MCPWM_O_REVISION        0x0U    // IP revision id register
#define MCPWM_O_TBCTL           0x8U    // Time base control register
#define MCPWM_O_TBPRD           0xAU    // Time base period register
#define MCPWM_O_TBPRDS          0xCU    // Time base period shadow register
#define MCPWM_O_TBPHS           0xEU    // Time base phase offset register
#define MCPWM_O_TBSTS           0x10U   // Time base status register
#define MCPWM_O_TBSTSCLR        0x12U   // Time base status clear register
#define MCPWM_O_TBCTR           0x14U   // Time base counter register
#define MCPWM_O_CMPCTL          0x18U   // Counter compare control register
#define MCPWM_O_CMPC            0x20U   // Counter compare C register
#define MCPWM_O_CMPD            0x22U   // Counter compare D register
#define MCPWM_O_CMPCS           0x24U   // Counter compare C shadow register
#define MCPWM_O_CMPDS           0x26U   // Counter compare D shadow register
#define MCPWM_O_AQCTL           0x28U   // Action qualifier control register
#define MCPWM_O_SOCEN           0x30U   // Start of conversion enable
#define MCPWM_O_SOCSEL          0x32U   // Start of conversion selection
#define MCPWM_O_SOCPERIOD       0x34U   // Start of conversion period
#define MCPWM_O_SOCCNT          0x36U   // Start of conversion count
#define MCPWM_O_SOCFLAG         0x38U   // Start of conversion flag
#define MCPWM_O_SOCCLR          0x3AU   // Start of conversion clear
#define MCPWM_O_ETSEL           0x40U   // Event trigger selection
#define MCPWM_O_ETPERIOD        0x42U   // Event trigger period
#define MCPWM_O_ETCNT           0x44U   // Event trigger count
#define MCPWM_O_INTEN           0x48U   // Interrupt enable
#define MCPWM_O_INTFLAG         0x4AU   // Interrupt flag
#define MCPWM_O_INTCLR          0x4CU   // Interrupt clear
#define MCPWM_O_INTFRC          0x4EU   // Interrupt force
#define MCPWM_O_TZSEL           0x50U   // Trip Zone selection
#define MCPWM_O_TZCTL           0x56U   // Trip Zone control
#define MCPWM_O_TZCBCOSTFLAG    0x58U   // Trip zone CBCOST flag
#define MCPWM_O_TZCBCOSTCLR     0x5AU   // Trip zone CBCOST flag clear
#define MCPWM_O_DBCTL           0x60U   // Dead band control register
#define MCPWM_O_DBFED           0x68U   // Dead band fall edge delay
#define MCPWM_O_DBRED           0x6AU   // Dead band rise edge delay
#define MCPWM_O_DBFEDS          0x6CU   // Dead band fall edge delay shadow register
#define MCPWM_O_DBREDS          0x6EU   // Dead band rise edge delay shadow register
#define MCPWM_O_GLDCTL          0x78U   // Global load control register
#define MCPWM_O_GLDOSHTCTL      0x7AU   // Global load one shot control register
#define MCPWM_O_GLDOSHTSTS      0x7CU   // Global load one shot status register
#define MCPWM_O_PWM1_CMPA       0x80U   // PWM1 counter compare A register
#define MCPWM_O_PWM1_CMPAS      0x82U   // PWM1 counter compare A shadow register
#define MCPWM_O_PWM1_CMPB       0x84U   // PWM1 counter compare B register
#define MCPWM_O_PWM1_CMPBS      0x86U   // PWM1 counter compare B shadow register
#define MCPWM_O_PWM1_AQCTLA     0x90U   // PWM1 action qualifier A register
#define MCPWM_O_PWM1_AQCTLAS    0x92U   // PWM1 action qualifier A shadow register
#define MCPWM_O_PWM1_AQCTLB     0x94U   // PWM1 action qualifier B register
#define MCPWM_O_PWM1_AQCTLBS    0x96U   // PWM1 action qualifier B shadow register
#define MCPWM_O_PWM1_AQSFRC     0x98U   // PWM1 action qualifier software force
#define MCPWM_O_PWM1_AQOTSFRC   0x9AU   // PWM1 action qualifier one time software force


//*************************************************************************************************
//
// The following are defines for the bit fields in the REVISION register
//
//*************************************************************************************************
#define MCPWM_REVISION_PWM2_PRESENT    0x1U   // PWM2 Present
#define MCPWM_REVISION_PWM3_PRESENT    0x2U   // PWM3 Present
#define MCPWM_REVISION_CMPCD_PRESENT   0x4U   // Compare C and D Present
#define MCPWM_REVISION_CAP_PRESENT     0x8U   // Capture mode Present

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL register
//
//*************************************************************************************************
#define MCPWM_TBCTL_CTRMODE_S      0U
#define MCPWM_TBCTL_CTRMODE_M      0x3U          // Counter Mode
#define MCPWM_TBCTL_CLKDIV_S       2U
#define MCPWM_TBCTL_CLKDIV_M       0x3CU         // Time Base Clock Pre-scaler
#define MCPWM_TBCTL_PRDLD          0x100U        // Shadow to active load of TBPRD
#define MCPWM_TBCTL_PHSEN          0x400U        // Phase Load Enable
#define MCPWM_TBCTL_PHSDIR         0x800U        // Phase Direction Bit
#define MCPWM_TBCTL_SWSYNC         0x8000U       // Software Force Sync Pulse
#define MCPWM_TBCTL_SYNCOSEL_S     16U
#define MCPWM_TBCTL_SYNCOSEL_M     0x70000U      // Sync Output Select
#define MCPWM_TBCTL_FREE_SOFT_S    20U
#define MCPWM_TBCTL_FREE_SOFT_M    0x300000U     // Emulation Mode Bits
#define MCPWM_TBCTL_SYNCPERSEL_S   22U
#define MCPWM_TBCTL_SYNCPERSEL_M   0x1C00000U    // Sync peripheral Select
#define MCPWM_TBCTL_SYNCISEL_S     25U
#define MCPWM_TBCTL_SYNCISEL_M     0x3E000000U   // Sync Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPRD register
//
//*************************************************************************************************
#define MCPWM_TBPRD_TBPRD_S   0U
#define MCPWM_TBPRD_TBPRD_M   0xFFFFU   // Time base period register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPRDS register
//
//*************************************************************************************************
#define MCPWM_TBPRDS_TBPRDS_S   0U
#define MCPWM_TBPRDS_TBPRDS_M   0xFFFFU   // Time base period shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPHS register
//
//*************************************************************************************************
#define MCPWM_TBPHS_TBPHS_S   0U
#define MCPWM_TBPHS_TBPHS_M   0xFFFFU   // Phase Offset Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*************************************************************************************************
#define MCPWM_TBSTS_CTRDIR   0x1U   // Counter Direction Status
#define MCPWM_TBSTS_SYNCI    0x2U   // External Input Sync Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTSCLR register
//
//*************************************************************************************************
#define MCPWM_TBSTSCLR_SYNCI   0x2U   // External Input Sync Status clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTR register
//
//*************************************************************************************************
#define MCPWM_TBCTR_TBCTR_S   0U
#define MCPWM_TBCTR_TBCTR_M   0xFFFFU   // Counter Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL register
//
//*************************************************************************************************
#define MCPWM_CMPCTL_PWM1_LOADAMODE_S   0U
#define MCPWM_CMPCTL_PWM1_LOADAMODE_M   0x3U         // Shadow to active load of PWM1_CMPA
#define MCPWM_CMPCTL_PWM1_LOADBMODE_S   2U
#define MCPWM_CMPCTL_PWM1_LOADBMODE_M   0xCU         // Shadow to active load of PWM1_CMPB
#define MCPWM_CMPCTL_PWM2_LOADAMODE_S   8U
#define MCPWM_CMPCTL_PWM2_LOADAMODE_M   0x300U       // Shadow to active load of PWM2_CMPA
#define MCPWM_CMPCTL_PWM2_LOADBMODE_S   10U
#define MCPWM_CMPCTL_PWM2_LOADBMODE_M   0xC00U       // Shadow to active load of PWM2_CMPB
#define MCPWM_CMPCTL_PWM3_LOADAMODE_S   16U
#define MCPWM_CMPCTL_PWM3_LOADAMODE_M   0x30000U     // Shadow to active load of PWM3_CMPA
#define MCPWM_CMPCTL_PWM3_LOADBMODE_S   18U
#define MCPWM_CMPCTL_PWM3_LOADBMODE_M   0xC0000U     // Shadow to active load of PWM3_CMPB
#define MCPWM_CMPCTL_LOADCMODE_S        24U
#define MCPWM_CMPCTL_LOADCMODE_M        0x3000000U   // Shadow to active load of CMPC
#define MCPWM_CMPCTL_LOADDMODE_S        26U
#define MCPWM_CMPCTL_LOADDMODE_M        0xC000000U   // Shadow to active load of CMPD

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPC register
//
//*************************************************************************************************
#define MCPWM_CMPC_CMPC_S   0U
#define MCPWM_CMPC_CMPC_M   0xFFFFU   // Compare C register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPD register
//
//*************************************************************************************************
#define MCPWM_CMPD_CMPD_S   0U
#define MCPWM_CMPD_CMPD_M   0xFFFFU   // Compare D register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCS register
//
//*************************************************************************************************
#define MCPWM_CMPCS_CMPCS_S   0U
#define MCPWM_CMPCS_CMPCS_M   0xFFFFU   // Compare C shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPDS register
//
//*************************************************************************************************
#define MCPWM_CMPDS_CMPDS_S   0U
#define MCPWM_CMPDS_CMPDS_M   0xFFFFU   // Compare D shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTL register
//
//*************************************************************************************************
#define MCPWM_AQCTL_PWM1_LDAQAMODE_S   0U
#define MCPWM_AQCTL_PWM1_LDAQAMODE_M   0x3U       // Shadow to active load of PWM1_AQCTLA
#define MCPWM_AQCTL_PWM1_LDAQBMODE_S   2U
#define MCPWM_AQCTL_PWM1_LDAQBMODE_M   0xCU       // Shadow to active load of PWM1_AQCTLB
#define MCPWM_AQCTL_PWM2_LDAQAMODE_S   8U
#define MCPWM_AQCTL_PWM2_LDAQAMODE_M   0x300U     // Shadow to active load of PWM2_AQCTLA
#define MCPWM_AQCTL_PWM2_LDAQBMODE_S   10U
#define MCPWM_AQCTL_PWM2_LDAQBMODE_M   0xC00U     // Shadow to active load of PWM2_AQCTLB
#define MCPWM_AQCTL_PWM3_LDAQAMODE_S   16U
#define MCPWM_AQCTL_PWM3_LDAQAMODE_M   0x30000U   // Shadow to active load of PWM3_AQCTLA
#define MCPWM_AQCTL_PWM3_LDAQBMODE_S   18U
#define MCPWM_AQCTL_PWM3_LDAQBMODE_M   0xC0000U   // Shadow to active load of PWM3_AQCTLB

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCEN register
//
//*************************************************************************************************
#define MCPWM_SOCEN_SOCA_ENABLE   0x1U   // Start of conversion (SOC) A enable
#define MCPWM_SOCEN_SOCB_ENABLE   0x2U   // Start of conversion (SOC) B enable
#define MCPWM_SOCEN_SOCC_ENABLE   0x4U   // Start of conversion (SOC) C enable
#define MCPWM_SOCEN_SOCD_ENABLE   0x8U   // Start of conversion (SOC) D enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCSEL register
//
//*************************************************************************************************
#define MCPWM_SOCSEL_SOCA_SEL_S   0U
#define MCPWM_SOCSEL_SOCA_SEL_M   0x1FU         // Start of conversion (SOC) A select
#define MCPWM_SOCSEL_SOCB_SEL_S   8U
#define MCPWM_SOCSEL_SOCB_SEL_M   0x1F00U       // Start of conversion (SOC) B select
#define MCPWM_SOCSEL_SOCC_SEL_S   16U
#define MCPWM_SOCSEL_SOCC_SEL_M   0x1F0000U     // Start of conversion (SOC) C select
#define MCPWM_SOCSEL_SOCD_SEL_S   24U
#define MCPWM_SOCSEL_SOCD_SEL_M   0x1F000000U   // Start of conversion (SOC) D select

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCPERIOD register
//
//*************************************************************************************************
#define MCPWM_SOCPERIOD_SOCA_PERIOD_S   0U
#define MCPWM_SOCPERIOD_SOCA_PERIOD_M   0x7U         // Start of conversion (SOC) A PERIOD
#define MCPWM_SOCPERIOD_SOCB_PERIOD_S   8U
#define MCPWM_SOCPERIOD_SOCB_PERIOD_M   0x700U       // Start of conversion (SOC) B PERIOD
#define MCPWM_SOCPERIOD_SOCC_PERIOD_S   16U
#define MCPWM_SOCPERIOD_SOCC_PERIOD_M   0x70000U     // Start of conversion (SOC) C PERIOD
#define MCPWM_SOCPERIOD_SOCD_PERIOD_S   24U
#define MCPWM_SOCPERIOD_SOCD_PERIOD_M   0x7000000U   // Start of conversion (SOC) D PERIOD

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCCNT register
//
//*************************************************************************************************
#define MCPWM_SOCCNT_SOCA_CNT_S   0U
#define MCPWM_SOCCNT_SOCA_CNT_M   0x7U         // Start of conversion (SOC) A COUNT
#define MCPWM_SOCCNT_SOCB_CNT_S   8U
#define MCPWM_SOCCNT_SOCB_CNT_M   0x700U       // Start of conversion (SOC) B COUNT
#define MCPWM_SOCCNT_SOCC_CNT_S   16U
#define MCPWM_SOCCNT_SOCC_CNT_M   0x70000U     // Start of conversion (SOC) C COUNT
#define MCPWM_SOCCNT_SOCD_CNT_S   24U
#define MCPWM_SOCCNT_SOCD_CNT_M   0x7000000U   // Start of conversion (SOC) D COUNT

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCFLAG register
//
//*************************************************************************************************
#define MCPWM_SOCFLAG_SOCA   0x1U   // SOCA Flag
#define MCPWM_SOCFLAG_SOCB   0x2U   // SOCB Flag
#define MCPWM_SOCFLAG_SOCC   0x4U   // SOCC Flag
#define MCPWM_SOCFLAG_SOCD   0x8U   // SOCD Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCCLR register
//
//*************************************************************************************************
#define MCPWM_SOCCLR_SOCA   0x1U   // SOCA Clear
#define MCPWM_SOCCLR_SOCB   0x2U   // SOCB Clear
#define MCPWM_SOCCLR_SOCC   0x4U   // SOCC Clear
#define MCPWM_SOCCLR_SOCD   0x8U   // SOCD Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSEL register
//
//*************************************************************************************************
#define MCPWM_ETSEL_ET1_SEL_S   0U
#define MCPWM_ETSEL_ET1_SEL_M   0x1FU     // Event trigger1 selection
#define MCPWM_ETSEL_ET2_SEL_S   8U
#define MCPWM_ETSEL_ET2_SEL_M   0x1F00U   // Event trigger2 selection

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETPERIOD register
//
//*************************************************************************************************
#define MCPWM_ETPERIOD_ET1_PERIOD_S   0U
#define MCPWM_ETPERIOD_ET1_PERIOD_M   0x7U     // Event trigger1 PERIOD
#define MCPWM_ETPERIOD_ET2_PERIOD_S   8U
#define MCPWM_ETPERIOD_ET2_PERIOD_M   0x700U   // Event trigger2 PERIOD

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNT register
//
//*************************************************************************************************
#define MCPWM_ETCNT_ET1_CNT_S   0U
#define MCPWM_ETCNT_ET1_CNT_M   0x7U     // Event trigger1 COUNT
#define MCPWM_ETCNT_ET2_CNT_S   8U
#define MCPWM_ETCNT_ET2_CNT_M   0x700U   // Event trigger2 COUNT

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTEN register
//
//*************************************************************************************************
#define MCPWM_INTEN_CBC       0x2U    // Enable CBC interrupt
#define MCPWM_INTEN_OST       0x4U    // Enable OST interrupt
#define MCPWM_INTEN_ET1       0x8U    // Enable ET1 interrupt
#define MCPWM_INTEN_ET2       0x10U   // Enable ET2 interrupt
#define MCPWM_INTEN_CNT_OVF   0x20U   // Counter overflow interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTFLAG register
//
//*************************************************************************************************
#define MCPWM_INTFLAG_INT       0x1U    // Global Flag
#define MCPWM_INTFLAG_CBC       0x2U    // CBC interrupt flag
#define MCPWM_INTFLAG_OST       0x4U    // OST interrupt flag
#define MCPWM_INTFLAG_ET1       0x8U    // ET1 interrupt flag
#define MCPWM_INTFLAG_ET2       0x10U   // ET2 interrupt flag
#define MCPWM_INTFLAG_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTCLR register
//
//*************************************************************************************************
#define MCPWM_INTCLR_INT       0x1U    // Clear Global Flag
#define MCPWM_INTCLR_CBC       0x2U    // Clear CBC interrupt flag
#define MCPWM_INTCLR_OST       0x4U    // Clear OST interrupt flag
#define MCPWM_INTCLR_ET1       0x8U    // Clear ET1 interrupt flag
#define MCPWM_INTCLR_ET2       0x10U   // Clear ET2 interrupt flag
#define MCPWM_INTCLR_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTFRC register
//
//*************************************************************************************************
#define MCPWM_INTFRC_CBC       0x2U    // Force CBC interrupt flag
#define MCPWM_INTFRC_OST       0x4U    // Force OST interrupt flag
#define MCPWM_INTFRC_ET1       0x8U    // Force ET1 interrupt flag
#define MCPWM_INTFRC_ET2       0x10U   // Force ET2 interrupt flag
#define MCPWM_INTFRC_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*************************************************************************************************
#define MCPWM_TZSEL_CBC1   0x1U        // CBC TZ1 select
#define MCPWM_TZSEL_CBC2   0x2U        // CBC TZ2 select
#define MCPWM_TZSEL_CBC3   0x4U        // CBC TZ3 select
#define MCPWM_TZSEL_CBC4   0x8U        // CBC TZ4  select
#define MCPWM_TZSEL_CBC5   0x10U       // CBC TZ5 select
#define MCPWM_TZSEL_CBC6   0x20U       // CBC TZ6 select
#define MCPWM_TZSEL_CBC7   0x40U       // CBC TZ7 select
#define MCPWM_TZSEL_CBC8   0x80U       // CBC TZ8 select
#define MCPWM_TZSEL_OST1   0x10000U    // OST TZ1 select
#define MCPWM_TZSEL_OST2   0x20000U    // OST TZ2 select
#define MCPWM_TZSEL_OST3   0x40000U    // OST TZ3 select
#define MCPWM_TZSEL_OST4   0x80000U    // OST TZ4  select
#define MCPWM_TZSEL_OST5   0x100000U   // OST TZ5 select
#define MCPWM_TZSEL_OST6   0x200000U   // OST TZ6 select
#define MCPWM_TZSEL_OST7   0x400000U   // OST TZ7 select
#define MCPWM_TZSEL_OST8   0x800000U   // OST TZ8 select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL register
//
//*************************************************************************************************
#define MCPWM_TZCTL_TZA_S        0U
#define MCPWM_TZCTL_TZA_M        0x3U    // TZ1 to TZ8 Trip Action on PWMA
#define MCPWM_TZCTL_TZB_S        2U
#define MCPWM_TZCTL_TZB_M        0xCU    // TZ1 to TZ8 Trip Action on PWMB
#define MCPWM_TZCTL_CBCPULSE_S   4U
#define MCPWM_TZCTL_CBCPULSE_M   0x30U   // Clear Pulse for CBC Trip Latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCOSTFLAG register
//
//*************************************************************************************************
#define MCPWM_TZCBCOSTFLAG_CBC1   0x1U        // CBC TZ1 Flag
#define MCPWM_TZCBCOSTFLAG_CBC2   0x2U        // CBC TZ2 Flag
#define MCPWM_TZCBCOSTFLAG_CBC3   0x4U        // CBC TZ3 Flag
#define MCPWM_TZCBCOSTFLAG_CBC4   0x8U        // CBC TZ4 Flag
#define MCPWM_TZCBCOSTFLAG_CBC5   0x10U       // CBC TZ5 Flag
#define MCPWM_TZCBCOSTFLAG_CBC6   0x20U       // CBC TZ6 Flag
#define MCPWM_TZCBCOSTFLAG_CBC7   0x40U       // CBC TZ7 Flag
#define MCPWM_TZCBCOSTFLAG_CBC8   0x80U       // OST TZ8 Flag
#define MCPWM_TZCBCOSTFLAG_OST1   0x10000U    // OST TZ1 Flag
#define MCPWM_TZCBCOSTFLAG_OST2   0x20000U    // OST TZ2 Flag
#define MCPWM_TZCBCOSTFLAG_OST3   0x40000U    // OST TZ3 Flag
#define MCPWM_TZCBCOSTFLAG_OST4   0x80000U    // OST TZ4 Flag
#define MCPWM_TZCBCOSTFLAG_OST5   0x100000U   // OST TZ5 Flag
#define MCPWM_TZCBCOSTFLAG_OST6   0x200000U   // OST TZ6 Flag
#define MCPWM_TZCBCOSTFLAG_OST7   0x400000U   // OST TZ7 Flag
#define MCPWM_TZCBCOSTFLAG_OST8   0x800000U   // OST TZ8 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCOSTCLR register
//
//*************************************************************************************************
#define MCPWM_TZCBCOSTCLR_CBC1   0x1U        // CBC TZ1 Clear
#define MCPWM_TZCBCOSTCLR_CBC2   0x2U        // CBC TZ2 Clear
#define MCPWM_TZCBCOSTCLR_CBC3   0x4U        // CBC TZ3 Clear
#define MCPWM_TZCBCOSTCLR_CBC4   0x8U        // CBC TZ4 Clear
#define MCPWM_TZCBCOSTCLR_CBC5   0x10U       // CBC TZ5 Clear
#define MCPWM_TZCBCOSTCLR_CBC6   0x20U       // CBC TZ6 Clear
#define MCPWM_TZCBCOSTCLR_CBC7   0x40U       // CBC TZ7 Clear
#define MCPWM_TZCBCOSTCLR_CBC8   0x80U       // OST TZ8 Clear
#define MCPWM_TZCBCOSTCLR_OST1   0x10000U    // OST TZ1 Clear
#define MCPWM_TZCBCOSTCLR_OST2   0x20000U    // OST TZ2 Clear
#define MCPWM_TZCBCOSTCLR_OST3   0x40000U    // OST TZ3 Clear
#define MCPWM_TZCBCOSTCLR_OST4   0x80000U    // OST TZ4 Clear
#define MCPWM_TZCBCOSTCLR_OST5   0x100000U   // OST TZ5 Clear
#define MCPWM_TZCBCOSTCLR_OST6   0x200000U   // OST TZ6 Clear
#define MCPWM_TZCBCOSTCLR_OST7   0x400000U   // OST TZ7 Clear
#define MCPWM_TZCBCOSTCLR_OST8   0x800000U   // OST TZ8 Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL register
//
//*************************************************************************************************
#define MCPWM_DBCTL_OUT_MODE_S      0U
#define MCPWM_DBCTL_OUT_MODE_M      0x3U       // Dead Band Output Mode Control
#define MCPWM_DBCTL_POLSEL_S        2U
#define MCPWM_DBCTL_POLSEL_M        0xCU       // Polarity Select Control
#define MCPWM_DBCTL_IN_MODE_S       4U
#define MCPWM_DBCTL_IN_MODE_M       0x30U      // Dead Band Input Select Mode Control
#define MCPWM_DBCTL_OUTSWAP_S       6U
#define MCPWM_DBCTL_OUTSWAP_M       0xC0U      // Dead Band Output Swap Control
#define MCPWM_DBCTL_DEDB_MODE       0x100U     // Dead Band Dual-Edge B Mode Control
#define MCPWM_DBCTL_LOADFEDMODE_S   16U
#define MCPWM_DBCTL_LOADFEDMODE_M   0x30000U   // Shadow to active load of DBFED
#define MCPWM_DBCTL_LOADREDMODE_S   18U
#define MCPWM_DBCTL_LOADREDMODE_M   0xC0000U   // Shadow to active load of DBRED

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*************************************************************************************************
#define MCPWM_DBFED_DBFED_S   0U
#define MCPWM_DBFED_DBFED_M   0x3FFFU   // Falling edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*************************************************************************************************
#define MCPWM_DBRED_DBRED_S   0U
#define MCPWM_DBRED_DBRED_M   0x3FFFU   // Rising edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFEDS register
//
//*************************************************************************************************
#define MCPWM_DBFEDS_DBFEDS_S   0U
#define MCPWM_DBFEDS_DBFEDS_M   0x3FFFU   // Falling edge delay shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBREDS register
//
//*************************************************************************************************
#define MCPWM_DBREDS_DBREDS_S   0U
#define MCPWM_DBREDS_DBREDS_M   0x3FFFU   // Rising edge delay shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL register
//
//*************************************************************************************************
#define MCPWM_GLDCTL_GLD         0x1U    // Global load enable
#define MCPWM_GLDCTL_OSHTMODE    0x2U    // Global load one-shot enable
#define MCPWM_GLDCTL_GLDMODE_S   4U
#define MCPWM_GLDCTL_GLDMODE_M   0x30U   // Select global load event

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDOSHTCTL register
//
//*************************************************************************************************
#define MCPWM_GLDOSHTCTL_OSHTLD    0x1U   // Enable Reload Event in One Shot Mode
#define MCPWM_GLDOSHTCTL_OSHTCLR   0x2U   // Enable Reload Event in One Shot Mode
#define MCPWM_GLDOSHTCTL_GFRCLD    0x4U   // Force load event in one shot mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDOSHTSTS register
//
//*************************************************************************************************
#define MCPWM_GLDOSHTSTS_OSHTLATCH   0x1U   // One shot latch output

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPA register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPA_PWM1_CMPA_S   0U
#define MCPWM_PWM1_CMPA_PWM1_CMPA_M   0xFFFFU   // PWM1 Compare A register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPAS register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_S   0U
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_M   0xFFFFU   // PWM1 Compare A shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPB register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPB_PWM1_CMPB_S   0U
#define MCPWM_PWM1_CMPB_PWM1_CMPB_M   0xFFFFU   // PWM1 Compare B register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPBS register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_S   0U
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_M   0xFFFFU   // PWM1 Compare B shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLA register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLA_ZRO_S   0U
#define MCPWM_PWM1_AQCTLA_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLA_PRD_S   2U
#define MCPWM_PWM1_AQCTLA_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLA_CAU_S   4U
#define MCPWM_PWM1_AQCTLA_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLA_CAD_S   6U
#define MCPWM_PWM1_AQCTLA_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLA_CBU_S   8U
#define MCPWM_PWM1_AQCTLA_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLA_CBD_S   10U
#define MCPWM_PWM1_AQCTLA_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLAS register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLAS_ZRO_S   0U
#define MCPWM_PWM1_AQCTLAS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLAS_PRD_S   2U
#define MCPWM_PWM1_AQCTLAS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLAS_CAU_S   4U
#define MCPWM_PWM1_AQCTLAS_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLAS_CAD_S   6U
#define MCPWM_PWM1_AQCTLAS_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLAS_CBU_S   8U
#define MCPWM_PWM1_AQCTLAS_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLAS_CBD_S   10U
#define MCPWM_PWM1_AQCTLAS_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLB register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLB_ZRO_S   0U
#define MCPWM_PWM1_AQCTLB_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLB_PRD_S   2U
#define MCPWM_PWM1_AQCTLB_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLB_CAU_S   4U
#define MCPWM_PWM1_AQCTLB_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLB_CAD_S   6U
#define MCPWM_PWM1_AQCTLB_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLB_CBU_S   8U
#define MCPWM_PWM1_AQCTLB_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLB_CBD_S   10U
#define MCPWM_PWM1_AQCTLB_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLBS register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLBS_ZRO_S   0U
#define MCPWM_PWM1_AQCTLBS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLBS_PRD_S   2U
#define MCPWM_PWM1_AQCTLBS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLBS_CAU_S   4U
#define MCPWM_PWM1_AQCTLBS_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLBS_CAD_S   6U
#define MCPWM_PWM1_AQCTLBS_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLBS_CBU_S   8U
#define MCPWM_PWM1_AQCTLBS_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLBS_CBD_S   10U
#define MCPWM_PWM1_AQCTLBS_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQSFRC_PWMA_S   0U
#define MCPWM_PWM1_AQSFRC_PWMA_M   0x7U    // Action qualifier software force on PWMA
#define MCPWM_PWM1_AQSFRC_PWMB_S   4U
#define MCPWM_PWM1_AQSFRC_PWMB_M   0x70U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQOTSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQOTSFRC_PWMA   0x1U    // Action qualifier one time software force on PWMA
#define MCPWM_PWM1_AQOTSFRC_PWMB   0x10U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_CMPA register
//
//*************************************************************************************************
#define MCPWM_PWM2_CMPA_PWM2_CMPA_S   0U
#define MCPWM_PWM2_CMPA_PWM2_CMPA_M   0xFFFFU   // PWM2 Compare A register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_CMPAS register
//
//*************************************************************************************************
#define MCPWM_PWM2_CMPAS_PWM2_CMPAS_S   0U
#define MCPWM_PWM2_CMPAS_PWM2_CMPAS_M   0xFFFFU   // PWM2 Compare A shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_CMPB register
//
//*************************************************************************************************
#define MCPWM_PWM2_CMPB_PWM2_CMPB_S   0U
#define MCPWM_PWM2_CMPB_PWM2_CMPB_M   0xFFFFU   // PWM2 Compare B register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_CMPBS register
//
//*************************************************************************************************
#define MCPWM_PWM2_CMPBS_PWM2_CMPBS_S   0U
#define MCPWM_PWM2_CMPBS_PWM2_CMPBS_M   0xFFFFU   // PWM2 Compare B shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQCTLA register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQCTLA_ZRO_S   0U
#define MCPWM_PWM2_AQCTLA_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM2_AQCTLA_PRD_S   2U
#define MCPWM_PWM2_AQCTLA_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM2_AQCTLA_CAU_S   4U
#define MCPWM_PWM2_AQCTLA_CAU_M   0x30U    // Action When TBCTR = PWM2_CMPA on Up Count
#define MCPWM_PWM2_AQCTLA_CAD_S   6U
#define MCPWM_PWM2_AQCTLA_CAD_M   0xC0U    // Action When TBCTR = PWM2_CMPA on Down Count
#define MCPWM_PWM2_AQCTLA_CBU_S   8U
#define MCPWM_PWM2_AQCTLA_CBU_M   0x300U   // Action When TBCTR = PWM2_CMPB on Up Count
#define MCPWM_PWM2_AQCTLA_CBD_S   10U
#define MCPWM_PWM2_AQCTLA_CBD_M   0xC00U   // Action When TBCTR = PWM2_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQCTLAS register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQCTLAS_ZRO_S   0U
#define MCPWM_PWM2_AQCTLAS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM2_AQCTLAS_PRD_S   2U
#define MCPWM_PWM2_AQCTLAS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM2_AQCTLAS_CAU_S   4U
#define MCPWM_PWM2_AQCTLAS_CAU_M   0x30U    // Action When TBCTR = PWM2_CMPA on Up Count
#define MCPWM_PWM2_AQCTLAS_CAD_S   6U
#define MCPWM_PWM2_AQCTLAS_CAD_M   0xC0U    // Action When TBCTR = PWM2_CMPA on Down Count
#define MCPWM_PWM2_AQCTLAS_CBU_S   8U
#define MCPWM_PWM2_AQCTLAS_CBU_M   0x300U   // Action When TBCTR = PWM2_CMPB on Up Count
#define MCPWM_PWM2_AQCTLAS_CBD_S   10U
#define MCPWM_PWM2_AQCTLAS_CBD_M   0xC00U   // Action When TBCTR = PWM2_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQCTLB register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQCTLB_ZRO_S   0U
#define MCPWM_PWM2_AQCTLB_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM2_AQCTLB_PRD_S   2U
#define MCPWM_PWM2_AQCTLB_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM2_AQCTLB_CAU_S   4U
#define MCPWM_PWM2_AQCTLB_CAU_M   0x30U    // Action When TBCTR = PWM2_CMPA on Up Count
#define MCPWM_PWM2_AQCTLB_CAD_S   6U
#define MCPWM_PWM2_AQCTLB_CAD_M   0xC0U    // Action When TBCTR = PWM2_CMPA on Down Count
#define MCPWM_PWM2_AQCTLB_CBU_S   8U
#define MCPWM_PWM2_AQCTLB_CBU_M   0x300U   // Action When TBCTR = PWM2_CMPB on Up Count
#define MCPWM_PWM2_AQCTLB_CBD_S   10U
#define MCPWM_PWM2_AQCTLB_CBD_M   0xC00U   // Action When TBCTR = PWM2_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQCTLBS register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQCTLBS_ZRO_S   0U
#define MCPWM_PWM2_AQCTLBS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM2_AQCTLBS_PRD_S   2U
#define MCPWM_PWM2_AQCTLBS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM2_AQCTLBS_CAU_S   4U
#define MCPWM_PWM2_AQCTLBS_CAU_M   0x30U    // Action When TBCTR = PWM2_CMPA on Up Count
#define MCPWM_PWM2_AQCTLBS_CAD_S   6U
#define MCPWM_PWM2_AQCTLBS_CAD_M   0xC0U    // Action When TBCTR = PWM2_CMPA on Down Count
#define MCPWM_PWM2_AQCTLBS_CBU_S   8U
#define MCPWM_PWM2_AQCTLBS_CBU_M   0x300U   // Action When TBCTR = PWM2_CMPB on Up Count
#define MCPWM_PWM2_AQCTLBS_CBD_S   10U
#define MCPWM_PWM2_AQCTLBS_CBD_M   0xC00U   // Action When TBCTR = PWM2_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQSFRC_PWMA_S   0U
#define MCPWM_PWM2_AQSFRC_PWMA_M   0x7U    // Action qualifier software force on PWMA
#define MCPWM_PWM2_AQSFRC_PWMB_S   4U
#define MCPWM_PWM2_AQSFRC_PWMB_M   0x70U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM2_AQOTSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM2_AQOTSFRC_PWMA   0x1U    // Action qualifier one time software force on PWMA
#define MCPWM_PWM2_AQOTSFRC_PWMB   0x10U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_CMPA register
//
//*************************************************************************************************
#define MCPWM_PWM3_CMPA_PWM3_CMPA_S   0U
#define MCPWM_PWM3_CMPA_PWM3_CMPA_M   0xFFFFU   // PWM3 Compare A register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_CMPAS register
//
//*************************************************************************************************
#define MCPWM_PWM3_CMPAS_PWM3_CMPAS_S   0U
#define MCPWM_PWM3_CMPAS_PWM3_CMPAS_M   0xFFFFU   // PWM3 Compare A shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_CMPB register
//
//*************************************************************************************************
#define MCPWM_PWM3_CMPB_PWM3_CMPB_S   0U
#define MCPWM_PWM3_CMPB_PWM3_CMPB_M   0xFFFFU   // PWM3 Compare B register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_CMPBS register
//
//*************************************************************************************************
#define MCPWM_PWM3_CMPBS_PWM3_CMPBS_S   0U
#define MCPWM_PWM3_CMPBS_PWM3_CMPBS_M   0xFFFFU   // PWM3 Compare B shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQCTLA register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQCTLA_ZRO_S   0U
#define MCPWM_PWM3_AQCTLA_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM3_AQCTLA_PRD_S   2U
#define MCPWM_PWM3_AQCTLA_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM3_AQCTLA_CAU_S   4U
#define MCPWM_PWM3_AQCTLA_CAU_M   0x30U    // Action When TBCTR = PWM3_CMPA on Up Count
#define MCPWM_PWM3_AQCTLA_CAD_S   6U
#define MCPWM_PWM3_AQCTLA_CAD_M   0xC0U    // Action When TBCTR = PWM3_CMPA on Down Count
#define MCPWM_PWM3_AQCTLA_CBU_S   8U
#define MCPWM_PWM3_AQCTLA_CBU_M   0x300U   // Action When TBCTR = PWM3_CMPB on Up Count
#define MCPWM_PWM3_AQCTLA_CBD_S   10U
#define MCPWM_PWM3_AQCTLA_CBD_M   0xC00U   // Action When TBCTR = PWM3_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQCTLAS register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQCTLAS_ZRO_S   0U
#define MCPWM_PWM3_AQCTLAS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM3_AQCTLAS_PRD_S   2U
#define MCPWM_PWM3_AQCTLAS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM3_AQCTLAS_CAU_S   4U
#define MCPWM_PWM3_AQCTLAS_CAU_M   0x30U    // Action When TBCTR = PWM3_CMPA on Up Count
#define MCPWM_PWM3_AQCTLAS_CAD_S   6U
#define MCPWM_PWM3_AQCTLAS_CAD_M   0xC0U    // Action When TBCTR = PWM3_CMPA on Down Count
#define MCPWM_PWM3_AQCTLAS_CBU_S   8U
#define MCPWM_PWM3_AQCTLAS_CBU_M   0x300U   // Action When TBCTR = PWM3_CMPB on Up Count
#define MCPWM_PWM3_AQCTLAS_CBD_S   10U
#define MCPWM_PWM3_AQCTLAS_CBD_M   0xC00U   // Action When TBCTR = PWM3_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQCTLB register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQCTLB_ZRO_S   0U
#define MCPWM_PWM3_AQCTLB_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM3_AQCTLB_PRD_S   2U
#define MCPWM_PWM3_AQCTLB_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM3_AQCTLB_CAU_S   4U
#define MCPWM_PWM3_AQCTLB_CAU_M   0x30U    // Action When TBCTR = PWM3_CMPA on Up Count
#define MCPWM_PWM3_AQCTLB_CAD_S   6U
#define MCPWM_PWM3_AQCTLB_CAD_M   0xC0U    // Action When TBCTR = PWM3_CMPA on Down Count
#define MCPWM_PWM3_AQCTLB_CBU_S   8U
#define MCPWM_PWM3_AQCTLB_CBU_M   0x300U   // Action When TBCTR = PWM3_CMPB on Up Count
#define MCPWM_PWM3_AQCTLB_CBD_S   10U
#define MCPWM_PWM3_AQCTLB_CBD_M   0xC00U   // Action When TBCTR = PWM3_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQCTLBS register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQCTLBS_ZRO_S   0U
#define MCPWM_PWM3_AQCTLBS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM3_AQCTLBS_PRD_S   2U
#define MCPWM_PWM3_AQCTLBS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM3_AQCTLBS_CAU_S   4U
#define MCPWM_PWM3_AQCTLBS_CAU_M   0x30U    // Action When TBCTR = PWM3_CMPA on Up Count
#define MCPWM_PWM3_AQCTLBS_CAD_S   6U
#define MCPWM_PWM3_AQCTLBS_CAD_M   0xC0U    // Action When TBCTR = PWM3_CMPA on Down Count
#define MCPWM_PWM3_AQCTLBS_CBU_S   8U
#define MCPWM_PWM3_AQCTLBS_CBU_M   0x300U   // Action When TBCTR = PWM3_CMPB on Up Count
#define MCPWM_PWM3_AQCTLBS_CBD_S   10U
#define MCPWM_PWM3_AQCTLBS_CBD_M   0xC00U   // Action When TBCTR = PWM3_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQSFRC_PWMA_S   0U
#define MCPWM_PWM3_AQSFRC_PWMA_M   0x7U    // Action qualifier software force on PWMA
#define MCPWM_PWM3_AQSFRC_PWMB_S   4U
#define MCPWM_PWM3_AQSFRC_PWMB_M   0x70U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM3_AQOTSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM3_AQOTSFRC_PWMA   0x1U    // Action qualifier one time software force on PWMA
#define MCPWM_PWM3_AQOTSFRC_PWMB   0x10U   // Action qualifier software force on PWMB


//*************************************************************************************************
//
// The following are defines for the bit fields in the REVISION register
//
//*************************************************************************************************
#define MCPWM_REVISION_PWM2_PRESENT    0x1U   // PWM2 Present
#define MCPWM_REVISION_PWM3_PRESENT    0x2U   // PWM3 Present
#define MCPWM_REVISION_CMPCD_PRESENT   0x4U   // Compare C and D Present
#define MCPWM_REVISION_CAP_PRESENT     0x8U   // Capture mode Present

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTL register
//
//*************************************************************************************************
#define MCPWM_TBCTL_CTRMODE_S      0U
#define MCPWM_TBCTL_CTRMODE_M      0x3U          // Counter Mode
#define MCPWM_TBCTL_CLKDIV_S       2U
#define MCPWM_TBCTL_CLKDIV_M       0x3CU         // Time Base Clock Pre-scaler
#define MCPWM_TBCTL_PRDLD          0x100U        // Shadow to active load of TBPRD
#define MCPWM_TBCTL_PHSEN          0x400U        // Phase Load Enable
#define MCPWM_TBCTL_PHSDIR         0x800U        // Phase Direction Bit
#define MCPWM_TBCTL_SWSYNC         0x8000U       // Software Force Sync Pulse
#define MCPWM_TBCTL_SYNCOSEL_S     16U
#define MCPWM_TBCTL_SYNCOSEL_M     0x70000U      // Sync Output Select
#define MCPWM_TBCTL_FREE_SOFT_S    20U
#define MCPWM_TBCTL_FREE_SOFT_M    0x300000U     // Emulation Mode Bits
#define MCPWM_TBCTL_SYNCPERSEL_S   22U
#define MCPWM_TBCTL_SYNCPERSEL_M   0x1C00000U    // Sync peripheral Select
#define MCPWM_TBCTL_SYNCISEL_S     25U
#define MCPWM_TBCTL_SYNCISEL_M     0x3E000000U   // Sync Input Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPRD register
//
//*************************************************************************************************
#define MCPWM_TBPRD_TBPRD_S   0U
#define MCPWM_TBPRD_TBPRD_M   0xFFFFU   // Time base period register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPRDS register
//
//*************************************************************************************************
#define MCPWM_TBPRDS_TBPRDS_S   0U
#define MCPWM_TBPRDS_TBPRDS_M   0xFFFFU   // Time base period shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBPHS register
//
//*************************************************************************************************
#define MCPWM_TBPHS_TBPHS_S   0U
#define MCPWM_TBPHS_TBPHS_M   0xFFFFU   // Phase Offset Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTS register
//
//*************************************************************************************************
#define MCPWM_TBSTS_CTRDIR   0x1U   // Counter Direction Status
#define MCPWM_TBSTS_SYNCI    0x2U   // External Input Sync Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBSTSCLR register
//
//*************************************************************************************************
#define MCPWM_TBSTSCLR_SYNCI   0x2U   // External Input Sync Status clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the TBCTR register
//
//*************************************************************************************************
#define MCPWM_TBCTR_TBCTR_S   0U
#define MCPWM_TBCTR_TBCTR_M   0xFFFFU   // Counter Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCTL register
//
//*************************************************************************************************
#define MCPWM_CMPCTL_PWM1_LOADAMODE_S   0U
#define MCPWM_CMPCTL_PWM1_LOADAMODE_M   0x3U         // Shadow to active load of PWM1_CMPA
#define MCPWM_CMPCTL_PWM1_LOADBMODE_S   2U
#define MCPWM_CMPCTL_PWM1_LOADBMODE_M   0xCU         // Shadow to active load of PWM1_CMPB
#define MCPWM_CMPCTL_LOADCMODE_S        24U
#define MCPWM_CMPCTL_LOADCMODE_M        0x3000000U   // Shadow to active load of CMPC
#define MCPWM_CMPCTL_LOADDMODE_S        26U
#define MCPWM_CMPCTL_LOADDMODE_M        0xC000000U   // Shadow to active load of CMPD

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPC register
//
//*************************************************************************************************
#define MCPWM_CMPC_CMPC_S   0U
#define MCPWM_CMPC_CMPC_M   0xFFFFU   // Compare C register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPD register
//
//*************************************************************************************************
#define MCPWM_CMPD_CMPD_S   0U
#define MCPWM_CMPD_CMPD_M   0xFFFFU   // Compare D register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCS register
//
//*************************************************************************************************
#define MCPWM_CMPCS_CMPCS_S   0U
#define MCPWM_CMPCS_CMPCS_M   0xFFFFU   // Compare C shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPDS register
//
//*************************************************************************************************
#define MCPWM_CMPDS_CMPDS_S   0U
#define MCPWM_CMPDS_CMPDS_M   0xFFFFU   // Compare D shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the AQCTL register
//
//*************************************************************************************************
#define MCPWM_AQCTL_PWM1_LDAQAMODE_S   0U
#define MCPWM_AQCTL_PWM1_LDAQAMODE_M   0x3U   // Shadow to active load of PWM1_AQCTLA
#define MCPWM_AQCTL_PWM1_LDAQBMODE_S   2U
#define MCPWM_AQCTL_PWM1_LDAQBMODE_M   0xCU   // Shadow to active load of PWM1_AQCTLB

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCEN register
//
//*************************************************************************************************
#define MCPWM_SOCEN_SOCA_ENABLE   0x1U   // Start of conversion (SOC) A enable
#define MCPWM_SOCEN_SOCB_ENABLE   0x2U   // Start of conversion (SOC) B enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCSEL register
//
//*************************************************************************************************
#define MCPWM_SOCSEL_SOCA_SEL_S   0U
#define MCPWM_SOCSEL_SOCA_SEL_M   0x1FU     // Start of conversion (SOC) A select
#define MCPWM_SOCSEL_SOCB_SEL_S   8U
#define MCPWM_SOCSEL_SOCB_SEL_M   0x1F00U   // Start of conversion (SOC) B select

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCPERIOD register
//
//*************************************************************************************************
#define MCPWM_SOCPERIOD_SOCA_PERIOD_S   0U
#define MCPWM_SOCPERIOD_SOCA_PERIOD_M   0x7U     // Start of conversion (SOC) A PERIOD
#define MCPWM_SOCPERIOD_SOCB_PERIOD_S   8U
#define MCPWM_SOCPERIOD_SOCB_PERIOD_M   0x700U   // Start of conversion (SOC) B PERIOD

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCCNT register
//
//*************************************************************************************************
#define MCPWM_SOCCNT_SOCA_CNT_S   0U
#define MCPWM_SOCCNT_SOCA_CNT_M   0x7U     // Start of conversion (SOC) A COUNT
#define MCPWM_SOCCNT_SOCB_CNT_S   8U
#define MCPWM_SOCCNT_SOCB_CNT_M   0x700U   // Start of conversion (SOC) B COUNT

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCFLAG register
//
//*************************************************************************************************
#define MCPWM_SOCFLAG_SOCA   0x1U   // SOCA Flag
#define MCPWM_SOCFLAG_SOCB   0x2U   // SOCB Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOCCLR register
//
//*************************************************************************************************
#define MCPWM_SOCCLR_SOCA   0x1U   // SOCA Clear
#define MCPWM_SOCCLR_SOCB   0x2U   // SOCB Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETSEL register
//
//*************************************************************************************************
#define MCPWM_ETSEL_ET1_SEL_S   0U
#define MCPWM_ETSEL_ET1_SEL_M   0x1FU     // Event trigger1 selection
#define MCPWM_ETSEL_ET2_SEL_S   8U
#define MCPWM_ETSEL_ET2_SEL_M   0x1F00U   // Event trigger2 selection

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETPERIOD register
//
//*************************************************************************************************
#define MCPWM_ETPERIOD_ET1_PERIOD_S   0U
#define MCPWM_ETPERIOD_ET1_PERIOD_M   0x7U     // Event trigger1 PERIOD
#define MCPWM_ETPERIOD_ET2_PERIOD_S   8U
#define MCPWM_ETPERIOD_ET2_PERIOD_M   0x700U   // Event trigger2 PERIOD

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETCNT register
//
//*************************************************************************************************
#define MCPWM_ETCNT_ET1_CNT_S   0U
#define MCPWM_ETCNT_ET1_CNT_M   0x7U     // Event trigger1 COUNT
#define MCPWM_ETCNT_ET2_CNT_S   8U
#define MCPWM_ETCNT_ET2_CNT_M   0x700U   // Event trigger2 COUNT

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTEN register
//
//*************************************************************************************************
#define MCPWM_INTEN_CBC       0x2U    // Enable CBC interrupt
#define MCPWM_INTEN_OST       0x4U    // Enable OST interrupt
#define MCPWM_INTEN_ET1       0x8U    // Enable ET1 interrupt
#define MCPWM_INTEN_ET2       0x10U   // Enable ET2 interrupt
#define MCPWM_INTEN_CNT_OVF   0x20U   // Counter overflow interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTFLAG register
//
//*************************************************************************************************
#define MCPWM_INTFLAG_INT       0x1U    // Global Flag
#define MCPWM_INTFLAG_CBC       0x2U    // CBC interrupt flag
#define MCPWM_INTFLAG_OST       0x4U    // OST interrupt flag
#define MCPWM_INTFLAG_ET1       0x8U    // ET1 interrupt flag
#define MCPWM_INTFLAG_ET2       0x10U   // ET2 interrupt flag
#define MCPWM_INTFLAG_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTCLR register
//
//*************************************************************************************************
#define MCPWM_INTCLR_INT       0x1U    // Clear Global Flag
#define MCPWM_INTCLR_CBC       0x2U    // Clear CBC interrupt flag
#define MCPWM_INTCLR_OST       0x4U    // Clear OST interrupt flag
#define MCPWM_INTCLR_ET1       0x8U    // Clear ET1 interrupt flag
#define MCPWM_INTCLR_ET2       0x10U   // Clear ET2 interrupt flag
#define MCPWM_INTCLR_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTFRC register
//
//*************************************************************************************************
#define MCPWM_INTFRC_CBC       0x2U    // Force CBC interrupt flag
#define MCPWM_INTFRC_OST       0x4U    // Force OST interrupt flag
#define MCPWM_INTFRC_ET1       0x8U    // Force ET1 interrupt flag
#define MCPWM_INTFRC_ET2       0x10U   // Force ET2 interrupt flag
#define MCPWM_INTFRC_CNT_OVF   0x20U   // Counter overflow flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZSEL register
//
//*************************************************************************************************
#define MCPWM_TZSEL_CBC1   0x1U        // CBC TZ1 select
#define MCPWM_TZSEL_CBC2   0x2U        // CBC TZ2 select
#define MCPWM_TZSEL_CBC3   0x4U        // CBC TZ3 select
#define MCPWM_TZSEL_CBC4   0x8U        // CBC TZ4  select
#define MCPWM_TZSEL_CBC5   0x10U       // CBC TZ5 select
#define MCPWM_TZSEL_CBC6   0x20U       // CBC TZ6 select
#define MCPWM_TZSEL_CBC7   0x40U       // CBC TZ7 select
#define MCPWM_TZSEL_CBC8   0x80U       // CBC TZ8 select
#define MCPWM_TZSEL_OST1   0x10000U    // OST TZ1 select
#define MCPWM_TZSEL_OST2   0x20000U    // OST TZ2 select
#define MCPWM_TZSEL_OST3   0x40000U    // OST TZ3 select
#define MCPWM_TZSEL_OST4   0x80000U    // OST TZ4  select
#define MCPWM_TZSEL_OST5   0x100000U   // OST TZ5 select
#define MCPWM_TZSEL_OST6   0x200000U   // OST TZ6 select
#define MCPWM_TZSEL_OST7   0x400000U   // OST TZ7 select
#define MCPWM_TZSEL_OST8   0x800000U   // OST TZ8 select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCTL register
//
//*************************************************************************************************
#define MCPWM_TZCTL_TZA_S        0U
#define MCPWM_TZCTL_TZA_M        0x3U    // TZ1 to TZ8 Trip Action on PWMA
#define MCPWM_TZCTL_TZB_S        2U
#define MCPWM_TZCTL_TZB_M        0xCU    // TZ1 to TZ8 Trip Action on PWMB
#define MCPWM_TZCTL_CBCPULSE_S   4U
#define MCPWM_TZCTL_CBCPULSE_M   0x30U   // Clear Pulse for CBC Trip Latch

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCOSTFLAG register
//
//*************************************************************************************************
#define MCPWM_TZCBCOSTFLAG_CBC1   0x1U        // CBC TZ1 Flag
#define MCPWM_TZCBCOSTFLAG_CBC2   0x2U        // CBC TZ2 Flag
#define MCPWM_TZCBCOSTFLAG_CBC3   0x4U        // CBC TZ3 Flag
#define MCPWM_TZCBCOSTFLAG_CBC4   0x8U        // CBC TZ4 Flag
#define MCPWM_TZCBCOSTFLAG_CBC5   0x10U       // CBC TZ5 Flag
#define MCPWM_TZCBCOSTFLAG_CBC6   0x20U       // CBC TZ6 Flag
#define MCPWM_TZCBCOSTFLAG_CBC7   0x40U       // CBC TZ7 Flag
#define MCPWM_TZCBCOSTFLAG_CBC8   0x80U       // OST TZ8 Flag
#define MCPWM_TZCBCOSTFLAG_OST1   0x10000U    // OST TZ1 Flag
#define MCPWM_TZCBCOSTFLAG_OST2   0x20000U    // OST TZ2 Flag
#define MCPWM_TZCBCOSTFLAG_OST3   0x40000U    // OST TZ3 Flag
#define MCPWM_TZCBCOSTFLAG_OST4   0x80000U    // OST TZ4 Flag
#define MCPWM_TZCBCOSTFLAG_OST5   0x100000U   // OST TZ5 Flag
#define MCPWM_TZCBCOSTFLAG_OST6   0x200000U   // OST TZ6 Flag
#define MCPWM_TZCBCOSTFLAG_OST7   0x400000U   // OST TZ7 Flag
#define MCPWM_TZCBCOSTFLAG_OST8   0x800000U   // OST TZ8 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TZCBCOSTCLR register
//
//*************************************************************************************************
#define MCPWM_TZCBCOSTCLR_CBC1   0x1U        // CBC TZ1 Clear
#define MCPWM_TZCBCOSTCLR_CBC2   0x2U        // CBC TZ2 Clear
#define MCPWM_TZCBCOSTCLR_CBC3   0x4U        // CBC TZ3 Clear
#define MCPWM_TZCBCOSTCLR_CBC4   0x8U        // CBC TZ4 Clear
#define MCPWM_TZCBCOSTCLR_CBC5   0x10U       // CBC TZ5 Clear
#define MCPWM_TZCBCOSTCLR_CBC6   0x20U       // CBC TZ6 Clear
#define MCPWM_TZCBCOSTCLR_CBC7   0x40U       // CBC TZ7 Clear
#define MCPWM_TZCBCOSTCLR_CBC8   0x80U       // OST TZ8 Clear
#define MCPWM_TZCBCOSTCLR_OST1   0x10000U    // OST TZ1 Clear
#define MCPWM_TZCBCOSTCLR_OST2   0x20000U    // OST TZ2 Clear
#define MCPWM_TZCBCOSTCLR_OST3   0x40000U    // OST TZ3 Clear
#define MCPWM_TZCBCOSTCLR_OST4   0x80000U    // OST TZ4 Clear
#define MCPWM_TZCBCOSTCLR_OST5   0x100000U   // OST TZ5 Clear
#define MCPWM_TZCBCOSTCLR_OST6   0x200000U   // OST TZ6 Clear
#define MCPWM_TZCBCOSTCLR_OST7   0x400000U   // OST TZ7 Clear
#define MCPWM_TZCBCOSTCLR_OST8   0x800000U   // OST TZ8 Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBCTL register
//
//*************************************************************************************************
#define MCPWM_DBCTL_OUT_MODE_S      0U
#define MCPWM_DBCTL_OUT_MODE_M      0x3U       // Dead Band Output Mode Control
#define MCPWM_DBCTL_POLSEL_S        2U
#define MCPWM_DBCTL_POLSEL_M        0xCU       // Polarity Select Control
#define MCPWM_DBCTL_IN_MODE_S       4U
#define MCPWM_DBCTL_IN_MODE_M       0x30U      // Dead Band Input Select Mode Control
#define MCPWM_DBCTL_OUTSWAP_S       6U
#define MCPWM_DBCTL_OUTSWAP_M       0xC0U      // Dead Band Output Swap Control
#define MCPWM_DBCTL_DEDB_MODE       0x100U     // Dead Band Dual-Edge B Mode Control
#define MCPWM_DBCTL_LOADFEDMODE_S   16U
#define MCPWM_DBCTL_LOADFEDMODE_M   0x30000U   // Shadow to active load of DBFED
#define MCPWM_DBCTL_LOADREDMODE_S   18U
#define MCPWM_DBCTL_LOADREDMODE_M   0xC0000U   // Shadow to active load of DBRED

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFED register
//
//*************************************************************************************************
#define MCPWM_DBFED_DBFED_S   0U
#define MCPWM_DBFED_DBFED_M   0x3FFFU   // Falling edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBRED register
//
//*************************************************************************************************
#define MCPWM_DBRED_DBRED_S   0U
#define MCPWM_DBRED_DBRED_M   0x3FFFU   // Rising edge delay value

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBFEDS register
//
//*************************************************************************************************
#define MCPWM_DBFEDS_DBFEDS_S   0U
#define MCPWM_DBFEDS_DBFEDS_M   0x3FFFU   // Falling edge delay shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DBREDS register
//
//*************************************************************************************************
#define MCPWM_DBREDS_DBREDS_S   0U
#define MCPWM_DBREDS_DBREDS_M   0x3FFFU   // Rising edge delay shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDCTL register
//
//*************************************************************************************************
#define MCPWM_GLDCTL_GLD         0x1U    // Global load enable
#define MCPWM_GLDCTL_OSHTMODE    0x2U    // Global load one-shot enable
#define MCPWM_GLDCTL_GLDMODE_S   4U
#define MCPWM_GLDCTL_GLDMODE_M   0x30U   // Select global load event

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDOSHTCTL register
//
//*************************************************************************************************
#define MCPWM_GLDOSHTCTL_OSHTLD    0x1U   // Enable Reload Event in One Shot Mode
#define MCPWM_GLDOSHTCTL_OSHTCLR   0x2U   // Enable Reload Event in One Shot Mode
#define MCPWM_GLDOSHTCTL_GFRCLD    0x4U   // Force load event in one shot mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GLDOSHTSTS register
//
//*************************************************************************************************
#define MCPWM_GLDOSHTSTS_OSHTLATCH   0x1U   // One shot latch output

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPA register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPA_PWM1_CMPA_S   0U
#define MCPWM_PWM1_CMPA_PWM1_CMPA_M   0xFFFFU   // PWM1 Compare A register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPAS register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_S   0U
#define MCPWM_PWM1_CMPAS_PWM1_CMPAS_M   0xFFFFU   // PWM1 Compare A shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPB register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPB_PWM1_CMPB_S   0U
#define MCPWM_PWM1_CMPB_PWM1_CMPB_M   0xFFFFU   // PWM1 Compare B register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_CMPBS register
//
//*************************************************************************************************
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_S   0U
#define MCPWM_PWM1_CMPBS_PWM1_CMPBS_M   0xFFFFU   // PWM1 Compare B shadow register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLA register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLA_ZRO_S   0U
#define MCPWM_PWM1_AQCTLA_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLA_PRD_S   2U
#define MCPWM_PWM1_AQCTLA_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLA_CAU_S   4U
#define MCPWM_PWM1_AQCTLA_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLA_CAD_S   6U
#define MCPWM_PWM1_AQCTLA_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLA_CBU_S   8U
#define MCPWM_PWM1_AQCTLA_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLA_CBD_S   10U
#define MCPWM_PWM1_AQCTLA_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLAS register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLAS_ZRO_S   0U
#define MCPWM_PWM1_AQCTLAS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLAS_PRD_S   2U
#define MCPWM_PWM1_AQCTLAS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLAS_CAU_S   4U
#define MCPWM_PWM1_AQCTLAS_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLAS_CAD_S   6U
#define MCPWM_PWM1_AQCTLAS_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLAS_CBU_S   8U
#define MCPWM_PWM1_AQCTLAS_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLAS_CBD_S   10U
#define MCPWM_PWM1_AQCTLAS_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLB register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLB_ZRO_S   0U
#define MCPWM_PWM1_AQCTLB_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLB_PRD_S   2U
#define MCPWM_PWM1_AQCTLB_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLB_CAU_S   4U
#define MCPWM_PWM1_AQCTLB_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLB_CAD_S   6U
#define MCPWM_PWM1_AQCTLB_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLB_CBU_S   8U
#define MCPWM_PWM1_AQCTLB_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLB_CBD_S   10U
#define MCPWM_PWM1_AQCTLB_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQCTLBS register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQCTLBS_ZRO_S   0U
#define MCPWM_PWM1_AQCTLBS_ZRO_M   0x3U     // Action When TBCTR = 0
#define MCPWM_PWM1_AQCTLBS_PRD_S   2U
#define MCPWM_PWM1_AQCTLBS_PRD_M   0xCU     // Action When TBCTR = TBPRD
#define MCPWM_PWM1_AQCTLBS_CAU_S   4U
#define MCPWM_PWM1_AQCTLBS_CAU_M   0x30U    // Action When TBCTR = PWM1_CMPA on Up Count
#define MCPWM_PWM1_AQCTLBS_CAD_S   6U
#define MCPWM_PWM1_AQCTLBS_CAD_M   0xC0U    // Action When TBCTR = PWM1_CMPA on Down Count
#define MCPWM_PWM1_AQCTLBS_CBU_S   8U
#define MCPWM_PWM1_AQCTLBS_CBU_M   0x300U   // Action When TBCTR = PWM1_CMPB on Up Count
#define MCPWM_PWM1_AQCTLBS_CBD_S   10U
#define MCPWM_PWM1_AQCTLBS_CBD_M   0xC00U   // Action When TBCTR = PWM1_CMPB on Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQSFRC_PWMA_S   0U
#define MCPWM_PWM1_AQSFRC_PWMA_M   0x7U    // Action qualifier software force on PWMA
#define MCPWM_PWM1_AQSFRC_PWMB_S   4U
#define MCPWM_PWM1_AQSFRC_PWMB_M   0x70U   // Action qualifier software force on PWMB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PWM1_AQOTSFRC register
//
//*************************************************************************************************
#define MCPWM_PWM1_AQOTSFRC_PWMA   0x1U    // Action qualifier one time software force on PWMA
#define MCPWM_PWM1_AQOTSFRC_PWMB   0x10U   // Action qualifier software force on PWMB



#endif
