//###########################################################################
//
// FILE:    hw_hrcap.h
//
// TITLE:   Definitions for the HRCAP registers.
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

#ifndef HW_HRCAP_H
#define HW_HRCAP_H

//*************************************************************************************************
//
// The following are defines for the HRCAP register offsets
//
//*************************************************************************************************
#define HRCAP_O_TSCTR           0x0U    // Time-Stamp Counter
#define HRCAP_O_CTRPHS          0x2U    // Counter Phase Offset Value Register
#define HRCAP_O_CAP1            0x4U    // Capture 1 Register
#define HRCAP_O_CAP2            0x6U    // Capture 2 Register
#define HRCAP_O_CAP3            0x8U    // Capture 3 Register
#define HRCAP_O_CAP4            0xAU    // Capture 4 Register
#define HRCAP_O_ECCTL0          0x12U   // Capture Control Register 0
#define HRCAP_O_ECCTL1          0x14U   // Capture Control Register 1
#define HRCAP_O_ECCTL2          0x15U   // Capture Control Register 2
#define HRCAP_O_ECEINT          0x16U   // Capture Interrupt Enable Register
#define HRCAP_O_ECFLG           0x17U   // Capture Interrupt Flag Register
#define HRCAP_O_ECCLR           0x18U   // Capture Interrupt Clear Register
#define HRCAP_O_ECFRC           0x19U   // Capture Interrupt Force Register
#define HRCAP_O_ECAPSYNCINSEL   0x1EU   // SYNC source select register

#define HRCAP_O_HRCTL         0x0U    // High-Res Control Register
#define HRCAP_O_HRINTEN       0x4U    // High-Res Calibration Interrupt Enable Register
#define HRCAP_O_HRFLG         0x6U    // High-Res Calibration Interrupt Flag Register
#define HRCAP_O_HRCLR         0x8U    // High-Res Calibration Interrupt Clear Register
#define HRCAP_O_HRFRC         0xAU    // High-Res Calibration Interrupt Force Register
#define HRCAP_O_HRCALPRD      0xCU    // High-Res Calibration Period Register
#define HRCAP_O_HRSYSCLKCTR   0xEU    // High-Res Calibration SYSCLK Counter Register
#define HRCAP_O_HRSYSCLKCAP   0x10U   // High-Res Calibration SYSCLK Capture Register
#define HRCAP_O_HRCLKCTR      0x12U   // High-Res Calibration HRCLK Counter Register
#define HRCAP_O_HRCLKCAP      0x14U   // High-Res Calibration HRCLK Capture Register

#define HRCAP_O_MUNIT_COMMON_CTL          0x0U    // Control registers for monitoring unit {#}
#define HRCAP_O_MUNIT_1_CTL               0x20U   // Control registers for monitoring unit 1
#define HRCAP_O_MUNIT_1_SHADOW_CTL        0x22U   // Shadow control registers for monitoring unit 1
#define HRCAP_O_MUNIT_1_MIN               0x28U   // Min value for monitoring unit 1
#define HRCAP_O_MUNIT_1_MAX               0x2AU   // Max value for monitoring unit 1
#define HRCAP_O_MUNIT_1_MIN_SHADOW        0x2CU   // Shadow register for Min value of monitoring
                                                  // unit 1
#define HRCAP_O_MUNIT_1_MAX_SHADOW        0x2EU   // Shadow register for Max value of monitoring
                                                  // unit 1
#define HRCAP_O_MUNIT_1_DEBUG_RANGE_MIN   0x30U   // Observed Min value of check being enabled on
                                                  // minotoring unit 1
#define HRCAP_O_MUNIT_1_DEBUG_RANGE_MAX   0x32U   // Observed Max value of check being enabled on
                                                  // minotoring unit 1
#define HRCAP_O_MUNIT_2_CTL               0x40U   // Control registers for monitoring unit 2
#define HRCAP_O_MUNIT_2_SHADOW_CTL        0x42U   // Shadow control registers for monitoring unit 2
#define HRCAP_O_MUNIT_2_MIN               0x48U   // Min value for monitoring unit 2
#define HRCAP_O_MUNIT_2_MAX               0x4AU   // Max value for monitoring unit 2
#define HRCAP_O_MUNIT_2_MIN_SHADOW        0x4CU   // Shadow register for Min value of monitoring
                                                  // unit 2
#define HRCAP_O_MUNIT_2_MAX_SHADOW        0x4EU   // Shadow register for Max value of monitoring
                                                  // unit 2
#define HRCAP_O_MUNIT_2_DEBUG_RANGE_MIN   0x50U   // Observed Min value of check being enabled on
                                                  // minotoring unit 2
#define HRCAP_O_MUNIT_2_DEBUG_RANGE_MAX   0x52U   // Observed Max value of check being enabled on
                                                  // minotoring unit 2


//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL0 register
//
//*************************************************************************************************
#define HRCAP_ECCTL0_INPUTSEL_S    0U
#define HRCAP_ECCTL0_INPUTSEL_M    0xFFU      // INPUT source select
#define HRCAP_ECCTL0_QUALPRD_S     12U
#define HRCAP_ECCTL0_QUALPRD_M     0xF000U    // Reserved
#define HRCAP_ECCTL0_SOCEVTSEL_S   16U
#define HRCAP_ECCTL0_SOCEVTSEL_M   0x30000U   // Reserved

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL1 register
//
//*************************************************************************************************
#define HRCAP_ECCTL1_CAP1POL       0x1U      // Capture Event 1 Polarity select
#define HRCAP_ECCTL1_CTRRST1       0x2U      // Counter Reset on Capture Event 1
#define HRCAP_ECCTL1_CAP2POL       0x4U      // Capture Event 2 Polarity select
#define HRCAP_ECCTL1_CTRRST2       0x8U      // Counter Reset on Capture Event 2
#define HRCAP_ECCTL1_CAP3POL       0x10U     // Capture Event 3 Polarity select
#define HRCAP_ECCTL1_CTRRST3       0x20U     // Counter Reset on Capture Event 3
#define HRCAP_ECCTL1_CAP4POL       0x40U     // Capture Event 4 Polarity select
#define HRCAP_ECCTL1_CTRRST4       0x80U     // Counter Reset on Capture Event 4
#define HRCAP_ECCTL1_CAPLDEN       0x100U    // Enable Loading CAP1-4 regs on a Cap Event
#define HRCAP_ECCTL1_PRESCALE_S    9U
#define HRCAP_ECCTL1_PRESCALE_M    0x3E00U   // Event Filter prescale select
#define HRCAP_ECCTL1_FREE_SOFT_S   14U
#define HRCAP_ECCTL1_FREE_SOFT_M   0xC000U   // Emulation mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL2 register
//
//*************************************************************************************************
#define HRCAP_ECCTL2_CONT_ONESHT    0x1U      // Continuous or one-shot
#define HRCAP_ECCTL2_STOP_WRAP_S    1U
#define HRCAP_ECCTL2_STOP_WRAP_M    0x6U      // Stop value for one-shot, Wrap for continuous
#define HRCAP_ECCTL2_REARM          0x8U      // One-shot re-arm
#define HRCAP_ECCTL2_TSCTRSTOP      0x10U     // TSCNT counter stop
#define HRCAP_ECCTL2_SYNCI_EN       0x20U     // Counter sync-in select
#define HRCAP_ECCTL2_SYNCO_SEL_S    6U
#define HRCAP_ECCTL2_SYNCO_SEL_M    0xC0U     // Sync-out mode
#define HRCAP_ECCTL2_SWSYNC         0x100U    // SW forced counter sync
#define HRCAP_ECCTL2_CAP_APWM       0x200U    // CAP/APWM operating mode select
#define HRCAP_ECCTL2_APWMPOL        0x400U    //  APWM output polarity select
#define HRCAP_ECCTL2_CTRFILTRESET   0x800U    // Reset event filter, modulus counter, and interrupt
                                              // flags.
#define HRCAP_ECCTL2_DMAEVTSEL_S    12U
#define HRCAP_ECCTL2_DMAEVTSEL_M    0x3000U   // DMA event select
#define HRCAP_ECCTL2_MODCNTRSTS_S   14U
#define HRCAP_ECCTL2_MODCNTRSTS_M   0xC000U   // modulo counter status

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECEINT register
//
//*************************************************************************************************
#define HRCAP_ECEINT_CEVT1                0x2U      // Capture Event 1 Interrupt Enable
#define HRCAP_ECEINT_CEVT2                0x4U      // Capture Event 2 Interrupt Enable
#define HRCAP_ECEINT_CEVT3                0x8U      // Capture Event 3 Interrupt Enable
#define HRCAP_ECEINT_CEVT4                0x10U     // Capture Event 4 Interrupt Enable
#define HRCAP_ECEINT_CTROVF               0x20U     // Counter Overflow Interrupt Enable
#define HRCAP_ECEINT_CTR_EQ_PRD           0x40U     // Period Equal Interrupt Enable
#define HRCAP_ECEINT_CTR_EQ_CMP           0x80U     // Compare Equal Interrupt Enable
#define HRCAP_ECEINT_MUNIT_1_ERROR_EVT1   0x200U    // Monitoring unit 1 error event-1 interrupt
                                                    // enable
#define HRCAP_ECEINT_MUNIT_1_ERROR_EVT2   0x400U    // Monitoring unit 1 error event-2 interrupt
                                                    // enable
#define HRCAP_ECEINT_MUNIT_2_ERROR_EVT1   0x800U    // Monitoring unit 2 error event-1 interrupt
                                                    // enable
#define HRCAP_ECEINT_MUNIT_2_ERROR_EVT2   0x1000U   // Monitoring unit 2 error event-2 interrupt
                                                    // enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECFLG register
//
//*************************************************************************************************
#define HRCAP_ECFLG_INT                  0x1U      // Global Flag
#define HRCAP_ECFLG_CEVT1                0x2U      // Capture Event 1 Interrupt Flag
#define HRCAP_ECFLG_CEVT2                0x4U      // Capture Event 2 Interrupt Flag
#define HRCAP_ECFLG_CEVT3                0x8U      // Capture Event 3 Interrupt Flag
#define HRCAP_ECFLG_CEVT4                0x10U     // Capture Event 4 Interrupt Flag
#define HRCAP_ECFLG_CTROVF               0x20U     // Counter Overflow Interrupt Flag
#define HRCAP_ECFLG_CTR_PRD              0x40U     // Period Equal Interrupt Flag
#define HRCAP_ECFLG_CTR_CMP              0x80U     // Compare Equal Interrupt Flag
#define HRCAP_ECFLG_MUNIT_1_ERROR_EVT1   0x200U    // Error event 2 Interrupt Flag from monitoring
                                                   // unit 1
#define HRCAP_ECFLG_MUNIT_1_ERROR_EVT2   0x400U    // Error event 2 Interrupt Flag from monitoring
                                                   // unit 1
#define HRCAP_ECFLG_MUNIT_2_ERROR_EVT1   0x800U    // Error event 2 Interrupt Flag from monitoring
                                                   // unit 2
#define HRCAP_ECFLG_MUNIT_2_ERROR_EVT2   0x1000U   // Error event 2 Interrupt Flag from monitoring
                                                   // unit 2

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCLR register
//
//*************************************************************************************************
#define HRCAP_ECCLR_INT                  0x1U      // ECAP Global Interrupt Status Clear
#define HRCAP_ECCLR_CEVT1                0x2U      // Capture Event 1 Status Clear
#define HRCAP_ECCLR_CEVT2                0x4U      // Capture Event 2 Status Clear
#define HRCAP_ECCLR_CEVT3                0x8U      // Capture Event 3 Status Clear
#define HRCAP_ECCLR_CEVT4                0x10U     // Capture Event 4 Status Clear
#define HRCAP_ECCLR_CTROVF               0x20U     // Counter Overflow Status Clear
#define HRCAP_ECCLR_CTR_PRD              0x40U     // Period Equal Status Clear
#define HRCAP_ECCLR_CTR_CMP              0x80U     // Compare Equal Status Clear
#define HRCAP_ECCLR_MUNIT_1_ERROR_EVT1   0x200U    // MUNIT_1_ERROR_EVT1 interrupt flag Clear
#define HRCAP_ECCLR_MUNIT_1_ERROR_EVT2   0x400U    // MUNIT_1_ERROR_EVT2 interrupt flag Clear
#define HRCAP_ECCLR_MUNIT_2_ERROR_EVT1   0x800U    // MUNIT_2_ERROR_EVT1 interrupt flag Clear
#define HRCAP_ECCLR_MUNIT_2_ERROR_EVT2   0x1000U   // MUNIT_2_ERROR_EVT2 interrupt flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECFRC register
//
//*************************************************************************************************
#define HRCAP_ECFRC_CEVT1                0x2U      // Capture Event 1 Force Interrupt
#define HRCAP_ECFRC_CEVT2                0x4U      // Capture Event 2 Force Interrupt
#define HRCAP_ECFRC_CEVT3                0x8U      // Capture Event 3 Force Interrupt
#define HRCAP_ECFRC_CEVT4                0x10U     // Capture Event 4 Force Interrupt
#define HRCAP_ECFRC_CTROVF               0x20U     // Counter Overflow Force Interrupt
#define HRCAP_ECFRC_CTR_PRD              0x40U     // Period Equal Force Interrupt
#define HRCAP_ECFRC_CTR_CMP              0x80U     // Compare Equal Force Interrupt
#define HRCAP_ECFRC_MUNIT_1_ERROR_EVT1   0x200U    // MUNIT_1_ERROR_EVT1 interrupt flag Set
#define HRCAP_ECFRC_MUNIT_1_ERROR_EVT2   0x400U    // MUNIT_1_ERROR_EVT2 interrupt flag Set
#define HRCAP_ECFRC_MUNIT_2_ERROR_EVT1   0x800U    // MUNIT_2_ERROR_EVT1 interrupt flag Set
#define HRCAP_ECFRC_MUNIT_2_ERROR_EVT2   0x1000U   // MUNIT_2_ERROR_EVT2 interrupt flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAPSYNCINSEL register
//
//*************************************************************************************************
#define HRCAP_ECAPSYNCINSEL_SEL_S   0U
#define HRCAP_ECAPSYNCINSEL_SEL_M   0x7FU   // SYNCIN source select


//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCTL register
//
//*************************************************************************************************
#define HRCAP_HRCTL_HRE          0x1U    // High Resolution Enable
#define HRCAP_HRCTL_HRCLKE       0x2U    // High Resolution Clock Enable
#define HRCAP_HRCTL_PRDSEL       0x4U    // Calibration Period Match
#define HRCAP_HRCTL_CALIBSTART   0x8U    // Calibration start
#define HRCAP_HRCTL_CALIBSTS     0x10U   // Calibration status
#define HRCAP_HRCTL_CALIBCONT    0x20U   // Continuous mode Calibration Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRINTEN register
//
//*************************************************************************************************
#define HRCAP_HRINTEN_CALIBDONE      0x2U   // Calibration doe interrupt enable
#define HRCAP_HRINTEN_CALPRDCHKSTS   0x4U   // Calibration period check status enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRFLG register
//
//*************************************************************************************************
#define HRCAP_HRFLG_CALIBINT       0x1U   // Global calibration Interrupt Status Flag
#define HRCAP_HRFLG_CALIBDONE      0x2U   // Calibration Done Interrupt Flag Bit
#define HRCAP_HRFLG_CALPRDCHKSTS   0x4U   // Calibration period check status Flag Bi

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRCLR register
//
//*************************************************************************************************
#define HRCAP_HRCLR_CALIBINT       0x1U   // Clear Global calibration Interrupt Flag
#define HRCAP_HRCLR_CALIBDONE      0x2U   // Clear Calibration Done Interrupt Flag Bit
#define HRCAP_HRCLR_CALPRDCHKSTS   0x4U   // Clear Calibration period check status Flag Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRFRC register
//
//*************************************************************************************************
#define HRCAP_HRFRC_CALIBDONE      0x2U   // Force Calibration Done Interrupt Flag Bit
#define HRCAP_HRFRC_CALPRDCHKSTS   0x4U   // Force Calibration period check status Flag Bit


//*************************************************************************************************
//
// The following are defines for the bit fields in the MUNIT_COMMON_CTL register
//
//*************************************************************************************************
#define HRCAP_MUNIT_COMMON_CTL_TRIPSEL_S      0U
#define HRCAP_MUNIT_COMMON_CTL_TRIPSEL_M      0x7FU     // Trip signal select
#define HRCAP_MUNIT_COMMON_CTL_GLDSTRBSEL_S   8U
#define HRCAP_MUNIT_COMMON_CTL_GLDSTRBSEL_M   0x7F00U   // Global Load strobe select

//*************************************************************************************************
//
// The following are defines for the bit fields in the MUNIT_1_CTL register
//
//*************************************************************************************************
#define HRCAP_MUNIT_1_CTL_EN                      0x1U     // Enable bit
#define HRCAP_MUNIT_1_CTL_DEBUG_RANGE_EN          0x2U     // Debug enable to aquire the range of
                                                           // check being done
#define HRCAP_MUNIT_1_CTL_DISABLE_EARLY_MAX_ERR   0x4U     // Disable early max error check
#define HRCAP_MUNIT_1_CTL_MON_SEL_S               8U
#define HRCAP_MUNIT_1_CTL_MON_SEL_M               0xF00U   // Selects type of monitoring

//*************************************************************************************************
//
// The following are defines for the bit fields in the MUNIT_1_SHADOW_CTL register
//
//*************************************************************************************************
#define HRCAP_MUNIT_1_SHADOW_CTL_SYNCI_EN   0x1U   // Enable for shadowing on Min and Max Registers
#define HRCAP_MUNIT_1_SHADOW_CTL_SWSYNC     0x2U   // SW sync to copy shadow to active Min and Max
                                                   // registers
#define HRCAP_MUNIT_1_SHADOW_CTL_LOADMODE   0x4U   // Load mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the MUNIT_2_CTL register
//
//*************************************************************************************************
#define HRCAP_MUNIT_2_CTL_EN                      0x1U     // Enable bit
#define HRCAP_MUNIT_2_CTL_DEBUG_RANGE_EN          0x2U     // Debug enable to aquire the range of
                                                           // check being done
#define HRCAP_MUNIT_2_CTL_DISABLE_EARLY_MAX_ERR   0x4U     // Disable early max error check
#define HRCAP_MUNIT_2_CTL_MON_SEL_S               8U
#define HRCAP_MUNIT_2_CTL_MON_SEL_M               0xF00U   // Selects type of monitoring

//*************************************************************************************************
//
// The following are defines for the bit fields in the MUNIT_2_SHADOW_CTL register
//
//*************************************************************************************************
#define HRCAP_MUNIT_2_SHADOW_CTL_SYNCI_EN   0x1U   // Enable for shadowing on Min and Max Registers
#define HRCAP_MUNIT_2_SHADOW_CTL_SWSYNC     0x2U   // SW sync to copy shadow to active Min and Max
                                                   // registers
#define HRCAP_MUNIT_2_SHADOW_CTL_LOADMODE   0x4U   // Load mode



#endif
