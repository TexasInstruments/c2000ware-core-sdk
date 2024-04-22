//###########################################################################
//
// FILE:    hw_mcan.h
//
// TITLE:   Definitions for the MCAN registers.
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

#ifndef HW_MCAN_H
#define HW_MCAN_H

//*************************************************************************************************
//
// The following are defines for the MCAN register offsets
//
//*************************************************************************************************
#define MCAN_O_SS_PID                           0x0U    // MCAN Subsystem Revision Register
#define MCAN_O_SS_CTRL                          0x2U    // MCAN Subsystem Control Register
#define MCAN_O_SS_STAT                          0x4U    // MCAN Subsystem Status Register
#define MCAN_O_SS_ICS                           0x6U    // MCAN Subsystem Interrupt Clear Shadow
                                                        // Register
#define MCAN_O_SS_IRS                           0x8U    // MCAN Subsystem Interrupt Raw Satus
                                                        // Register
#define MCAN_O_SS_IECS                          0xAU    // MCAN Subsystem Interrupt Enable Clear
                                                        // Shadow Register
#define MCAN_O_SS_IE                            0xCU    // MCAN Subsystem Interrupt Enable Register
#define MCAN_O_SS_IES                           0xEU    // MCAN Subsystem Interrupt Enable Status
#define MCAN_O_SS_EOI                           0x10U   // MCAN Subsystem End of Interrupt
#define MCAN_O_SS_EXT_TS_PRESCALER              0x12U   // MCAN Subsystem External Timestamp
                                                        // Prescaler 0
#define MCAN_O_SS_EXT_TS_UNSERVICED_INTR_CNTR   0x14U   // MCAN Subsystem External Timestamp
                                                        // Unserviced Interrupts Counter

#define MCAN_O_CREL     0x0U    // MCAN Core Release Register
#define MCAN_O_ENDN     0x2U    // MCAN Endian Register
#define MCAN_O_DBTP     0x6U    // MCAN Data Bit Timing and Prescaler Register
#define MCAN_O_TEST     0x8U    // MCAN Test Register
#define MCAN_O_RWD      0xAU    // MCAN RAM Watchdog
#define MCAN_O_CCCR     0xCU    // MCAN CC Control Register
#define MCAN_O_NBTP     0xEU    // MCAN Nominal Bit Timing and Prescaler Register
#define MCAN_O_TSCC     0x10U   // MCAN Timestamp Counter Configuration
#define MCAN_O_TSCV     0x12U   // MCAN Timestamp Counter Value
#define MCAN_O_TOCC     0x14U   // MCAN Timeout Counter Configuration
#define MCAN_O_TOCV     0x16U   // MCAN Timeout Counter Value
#define MCAN_O_ECR      0x20U   // MCAN Error Counter Register
#define MCAN_O_PSR      0x22U   // MCAN Protocol Status Register
#define MCAN_O_TDCR     0x24U   // MCAN Transmitter Delay Compensation Register
#define MCAN_O_IR       0x28U   // MCAN Interrupt Register
#define MCAN_O_IE       0x2AU   // MCAN Interrupt Enable
#define MCAN_O_ILS      0x2CU   // MCAN Interrupt Line Select
#define MCAN_O_ILE      0x2EU   // MCAN Interrupt Line Enable
#define MCAN_O_GFC      0x40U   // MCAN Global Filter Configuration
#define MCAN_O_SIDFC    0x42U   // MCAN Standard ID Filter Configuration
#define MCAN_O_XIDFC    0x44U   // MCAN Extended ID Filter Configuration
#define MCAN_O_XIDAM    0x48U   // MCAN Extended ID and Mask
#define MCAN_O_HPMS     0x4AU   // MCAN High Priority Message Status
#define MCAN_O_NDAT1    0x4CU   // MCAN New Data 1
#define MCAN_O_NDAT2    0x4EU   // MCAN New Data 2
#define MCAN_O_RXF0C    0x50U   // MCAN Rx FIFO 0 Configuration
#define MCAN_O_RXF0S    0x52U   // MCAN Rx FIFO 0 Status
#define MCAN_O_RXF0A    0x54U   // MCAN Rx FIFO 0 Acknowledge
#define MCAN_O_RXBC     0x56U   // MCAN Rx Buffer Configuration
#define MCAN_O_RXF1C    0x58U   // MCAN Rx FIFO 1 Configuration
#define MCAN_O_RXF1S    0x5AU   // MCAN Rx FIFO 1 Status
#define MCAN_O_RXF1A    0x5CU   // MCAN Rx FIFO 1 Acknowledge
#define MCAN_O_RXESC    0x5EU   // MCAN Rx Buffer / FIFO Element Size Configuration
#define MCAN_O_TXBC     0x60U   // MCAN Tx Buffer Configuration
#define MCAN_O_TXFQS    0x62U   // MCAN Tx FIFO / Queue Status
#define MCAN_O_TXESC    0x64U   // MCAN Tx Buffer Element Size Configuration
#define MCAN_O_TXBRP    0x66U   // MCAN Tx Buffer Request Pending
#define MCAN_O_TXBAR    0x68U   // MCAN Tx Buffer Add Request
#define MCAN_O_TXBCR    0x6AU   // MCAN Tx Buffer Cancellation Request
#define MCAN_O_TXBTO    0x6CU   // MCAN Tx Buffer Transmission Occurred
#define MCAN_O_TXBCF    0x6EU   // MCAN Tx Buffer Cancellation Finished
#define MCAN_O_TXBTIE   0x70U   // MCAN Tx Buffer Transmission Interrupt Enable
#define MCAN_O_TXBCIE   0x72U   // MCAN Tx Buffer Cancellation Finished Interrupt Enable
#define MCAN_O_TXEFC    0x78U   // MCAN Tx Event FIFO Configuration
#define MCAN_O_TXEFS    0x7AU   // MCAN Tx Event FIFO Status
#define MCAN_O_TXEFA    0x7CU   // MCAN Tx Event FIFO Acknowledge

#define MCAN_O_ERR_REV               0x0U     // MCAN Error Aggregator Revision Register
#define MCAN_O_ERR_VECTOR            0x4U     // MCAN ECC Vector Register
#define MCAN_O_ERR_STAT              0x6U     // MCAN Error Misc Status
#define MCAN_O_ERR_WRAP_REV          0x8U     // MCAN ECC Wrapper Revision Register
#define MCAN_O_ERR_CTRL              0xAU     // MCAN ECC Control
#define MCAN_O_ERR_ERR_CTRL1         0xCU     // MCAN ECC Error Control 1 Register
#define MCAN_O_ERR_ERR_CTRL2         0xEU     // MCAN ECC Error Control 2 Register
#define MCAN_O_ERR_ERR_STAT1         0x10U    // MCAN ECC Error Status 1 Register
#define MCAN_O_ERR_ERR_STAT2         0x12U    // MCAN ECC Error Status 2 Register
#define MCAN_O_ERR_ERR_STAT3         0x14U    // MCAN ECC Error Status 3 Register
#define MCAN_O_ERR_SEC_EOI           0x1EU    // MCAN Single Error Corrected End of Interrupt
                                              // Register
#define MCAN_O_ERR_SEC_STATUS        0x20U    // MCAN Single Error Corrected Interrupt Status
                                              // Register
#define MCAN_O_ERR_SEC_ENABLE_SET    0x40U    // MCAN Single Error Corrected Interrupt Enable Set
                                              // Register
#define MCAN_O_ERR_SEC_ENABLE_CLR    0x60U    // MCAN Single Error Corrected Interrupt Enable Clear
                                              // Register
#define MCAN_O_ERR_DED_EOI           0x9EU    // MCAN Double Error Detected End of Interrupt
                                              // Register
#define MCAN_O_ERR_DED_STATUS        0xA0U    // MCAN Double Error Detected Interrupt Status
                                              // Register
#define MCAN_O_ERR_DED_ENABLE_SET    0xC0U    // MCAN Double Error Detected Interrupt Enable Set
                                              // Register
#define MCAN_O_ERR_DED_ENABLE_CLR    0xE0U    // MCAN Double Error Detected Interrupt Enable Clear
                                              // Register
#define MCAN_O_ERR_AGGR_ENABLE_SET   0x100U   // MCAN Error Aggregator Enable Set Register
#define MCAN_O_ERR_AGGR_ENABLE_CLR   0x102U   // MCAN Error Aggregator Enable Clear Register
#define MCAN_O_ERR_AGGR_STATUS_SET   0x104U   // MCAN Error Aggregator Status Set Register
#define MCAN_O_ERR_AGGR_STATUS_CLR   0x106U   // MCAN Error Aggregator Status Clear Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_PID register
//
//*************************************************************************************************
#define MCAN_SS_PID_MINOR_S       0U
#define MCAN_SS_PID_MINOR_M       0x3FU         // Minor Revision
#define MCAN_SS_PID_MAJOR_S       8U
#define MCAN_SS_PID_MAJOR_M       0x700U        // Major Revision
#define MCAN_SS_PID_MODULE_ID_S   16U
#define MCAN_SS_PID_MODULE_ID_M   0xFFF0000U    // Module Identification Number
#define MCAN_SS_PID_SCHEME_S      30U
#define MCAN_SS_PID_SCHEME_M      0xC0000000U   // PID Register Scheme

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_CTRL register
//
//*************************************************************************************************
#define MCAN_SS_CTRL_DBGSUSP_FREE     0x8U    // Debug Suspend Free
#define MCAN_SS_CTRL_WAKEUPREQEN      0x10U   // Wakeup Request Enable
#define MCAN_SS_CTRL_AUTOWAKEUP       0x20U   // Automatic Wakeup Enable
#define MCAN_SS_CTRL_EXT_TS_CNTR_EN   0x40U   // External Timestamp Counter Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_STAT register
//
//*************************************************************************************************
#define MCAN_SS_STAT_RESET           0x1U   // Soft Reset Status
#define MCAN_SS_STAT_MEM_INIT_DONE   0x2U   // Memory Initialization Done
#define MCAN_SS_STAT_ENABLE_FDOE     0x4U   // Flexible Datarate Operation Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_ICS register
//
//*************************************************************************************************
#define MCAN_SS_ICS_EXT_TS_CNTR_OVFL   0x1U   // External Timestamp Counter Overflow Interrupt
                                              // Status Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_IRS register
//
//*************************************************************************************************
#define MCAN_SS_IRS_EXT_TS_CNTR_OVFL   0x1U   // External Timestamp Counter Overflow Interrupt
                                              // Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_IECS register
//
//*************************************************************************************************
#define MCAN_SS_IECS_EXT_TS_CNTR_OVFL   0x1U   // External Timestamp Counter Overflow Interrupt
                                               // Enable Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_IE register
//
//*************************************************************************************************
#define MCAN_SS_IE_EXT_TS_CNTR_OVFL   0x1U   // External Timestamp Counter Overflow Interrupt
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_IES register
//
//*************************************************************************************************
#define MCAN_SS_IES_EXT_TS_CNTR_OVFL   0x1U   // External Timestamp Counter Overflow Interrupt
                                              // Enable Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_EOI register
//
//*************************************************************************************************
#define MCAN_SS_EOI_EOI_S   0U
#define MCAN_SS_EOI_EOI_M   0xFFU   // External Timestamp Counter Overflow End of Interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_EXT_TS_PRESCALER register
//
//*************************************************************************************************
#define MCAN_SS_EXT_TS_PRESCALER_PRESCALER_S   0U
#define MCAN_SS_EXT_TS_PRESCALER_PRESCALER_M   0xFFFFFFU   // External Timestamp Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANSS_EXT_TS_UNSERVICED_INTR_CNTR register
//
//*************************************************************************************************
#define MCAN_SS_EXT_TS_UNSERVICED_INTR_CNTR_EXT_TS_INTR_CNTR_S   0U
#define MCAN_SS_EXT_TS_UNSERVICED_INTR_CNTR_EXT_TS_INTR_CNTR_M   0x1FU   // External Timestamp
                                                                         // Counter Unserviced Rollover
                                                                         // Interrupts


//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_CREL register
//
//*************************************************************************************************
#define MCAN_CREL_DAY_S       0U
#define MCAN_CREL_DAY_M       0xFFU         // Time Stamp Day
#define MCAN_CREL_MON_S       8U
#define MCAN_CREL_MON_M       0xFF00U       // Time Stamp Month
#define MCAN_CREL_YEAR_S      16U
#define MCAN_CREL_YEAR_M      0xF0000U      // Time Stamp Year
#define MCAN_CREL_SUBSTEP_S   20U
#define MCAN_CREL_SUBSTEP_M   0xF00000U     // Sub-Step of Core Release
#define MCAN_CREL_STEP_S      24U
#define MCAN_CREL_STEP_M      0xF000000U    // Step of Core Release
#define MCAN_CREL_REL_S       28U
#define MCAN_CREL_REL_M       0xF0000000U   // Core Release

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_DBTP register
//
//*************************************************************************************************
#define MCAN_DBTP_DSJW_S     0U
#define MCAN_DBTP_DSJW_M     0xFU        // Data Resynchronization Jump Width
#define MCAN_DBTP_DTSEG2_S   4U
#define MCAN_DBTP_DTSEG2_M   0xF0U       // Data Time Segment After Sample Point
#define MCAN_DBTP_DTSEG1_S   8U
#define MCAN_DBTP_DTSEG1_M   0x1F00U     // Data Time Segment Before Sample Point
#define MCAN_DBTP_DBRP_S     16U
#define MCAN_DBTP_DBRP_M     0x1F0000U   // Data Bit Rate Prescaler
#define MCAN_DBTP_TDC        0x800000U   // Transmitter Delay Compensation

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TEST register
//
//*************************************************************************************************
#define MCAN_TEST_LBCK   0x10U   // Loop Back Mode
#define MCAN_TEST_TX_S   5U
#define MCAN_TEST_TX_M   0x60U   // Control of Transmit Pin
#define MCAN_TEST_RX     0x80U   // Receive Pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RWD register
//
//*************************************************************************************************
#define MCAN_RWD_WDC_S   0U
#define MCAN_RWD_WDC_M   0xFFU     // Watchdog Configuration
#define MCAN_RWD_WDV_S   8U
#define MCAN_RWD_WDV_M   0xFF00U   // Watchdog Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_CCCR register
//
//*************************************************************************************************
#define MCAN_CCCR_INIT   0x1U      // Initialization
#define MCAN_CCCR_CCE    0x2U      // Configuration Change Enable
#define MCAN_CCCR_ASM    0x4U      // Restricted Operation Mode
#define MCAN_CCCR_CSA    0x8U      // Clock Stop Acknowledge
#define MCAN_CCCR_CSR    0x10U     // Clock Stop Request
#define MCAN_CCCR_MON    0x20U     // Bus Monitoring Mode
#define MCAN_CCCR_DAR    0x40U     // Disable Automatic Retransmission
#define MCAN_CCCR_TEST   0x80U     // Test Mode Enable
#define MCAN_CCCR_FDOE   0x100U    // Flexible Datarate Operation Enable
#define MCAN_CCCR_BRSE   0x200U    // Bit Rate Switch Enable
#define MCAN_CCCR_PXHD   0x1000U   // Protocol Exception Handling Disable
#define MCAN_CCCR_EFBI   0x2000U   // Edge Filtering During Bus Integration
#define MCAN_CCCR_TXP    0x4000U   // Transmit Pause
#define MCAN_CCCR_NISO   0x8000U   // Non-ISO Operation

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_NBTP register
//
//*************************************************************************************************
#define MCAN_NBTP_NTSEG2_S   0U
#define MCAN_NBTP_NTSEG2_M   0x7FU         // Nominal Time Segment After Sample Point
#define MCAN_NBTP_NTSEG1_S   8U
#define MCAN_NBTP_NTSEG1_M   0xFF00U       // Nominal Time Segment Before Sample Point
#define MCAN_NBTP_NBRP_S     16U
#define MCAN_NBTP_NBRP_M     0x1FF0000U    // Nominal Bit Rate Prescaler
#define MCAN_NBTP_NSJW_S     25U
#define MCAN_NBTP_NSJW_M     0xFE000000U   // Nominal (Re)Synchronization Jump Width

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TSCC register
//
//*************************************************************************************************
#define MCAN_TSCC_TSS_S   0U
#define MCAN_TSCC_TSS_M   0x3U       // Timestamp Select
#define MCAN_TSCC_TCP_S   16U
#define MCAN_TSCC_TCP_M   0xF0000U   // Timestamp Counter Prescaler

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TSCV register
//
//*************************************************************************************************
#define MCAN_TSCV_TSC_S   0U
#define MCAN_TSCV_TSC_M   0xFFFFU   // Timestamp Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TOCC register
//
//*************************************************************************************************
#define MCAN_TOCC_ETOC    0x1U          // Enable Timeout Counter
#define MCAN_TOCC_TOS_S   1U
#define MCAN_TOCC_TOS_M   0x6U          // Timeout Select
#define MCAN_TOCC_TOP_S   16U
#define MCAN_TOCC_TOP_M   0xFFFF0000U   // Timeout Period

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TOCV register
//
//*************************************************************************************************
#define MCAN_TOCV_TOC_S   0U
#define MCAN_TOCV_TOC_M   0xFFFFU   // Timeout Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_ECR register
//
//*************************************************************************************************
#define MCAN_ECR_TEC_S   0U
#define MCAN_ECR_TEC_M   0xFFU       // Transmit Error Counter
#define MCAN_ECR_REC_S   8U
#define MCAN_ECR_REC_M   0x7F00U     // Receive Error Counter
#define MCAN_ECR_RP      0x8000U     // Receive Error Passive
#define MCAN_ECR_CEL_S   16U
#define MCAN_ECR_CEL_M   0xFF0000U   // CAN Error Logging

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_PSR register
//
//*************************************************************************************************
#define MCAN_PSR_LEC_S    0U
#define MCAN_PSR_LEC_M    0x7U        // Last Error Code
#define MCAN_PSR_ACT_S    3U
#define MCAN_PSR_ACT_M    0x18U       // Node Activity
#define MCAN_PSR_EP       0x20U       // Error Passive
#define MCAN_PSR_EW       0x40U       // Warning Status
#define MCAN_PSR_BO       0x80U       // Bus_Off Status
#define MCAN_PSR_DLEC_S   8U
#define MCAN_PSR_DLEC_M   0x700U      // Data Phase Last Error Code
#define MCAN_PSR_RESI     0x800U      // ESI Flag of Last Received CAN FD Message
#define MCAN_PSR_RBRS     0x1000U     // BRS Flag of Last Received CAN FD Message
#define MCAN_PSR_RFDF     0x2000U     // Received a CAN FD Message
#define MCAN_PSR_PXE      0x4000U     // Protocol Exception Event
#define MCAN_PSR_TDCV_S   16U
#define MCAN_PSR_TDCV_M   0x7F0000U   // Transmitter Delay Compensation Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TDCR register
//
//*************************************************************************************************
#define MCAN_TDCR_TDCF_S   0U
#define MCAN_TDCR_TDCF_M   0x7FU     // Transmitter Delay Compensation Filter Window Length
#define MCAN_TDCR_TDCO_S   8U
#define MCAN_TDCR_TDCO_M   0x7F00U   // Transmitter Delay Compensation Offset

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_IR register
//
//*************************************************************************************************
#define MCAN_IR_RF0N   0x1U          // Rx FIFO 0 New Message
#define MCAN_IR_RF0W   0x2U          // Rx FIFO 0 Watermark Reached
#define MCAN_IR_RF0F   0x4U          // Rx FIFO 0 Full
#define MCAN_IR_RF0L   0x8U          // Rx FIFO 0 Message Lost
#define MCAN_IR_RF1N   0x10U         // Rx FIFO 1 New Message
#define MCAN_IR_RF1W   0x20U         // Rx FIFO 1 Watermark Reached
#define MCAN_IR_RF1F   0x40U         // Rx FIFO 1 Full
#define MCAN_IR_RF1L   0x80U         // Rx FIFO 1 Message Lost
#define MCAN_IR_HPM    0x100U        // High Priority Message
#define MCAN_IR_TC     0x200U        // Transmission Completed
#define MCAN_IR_TCF    0x400U        // Transmission Cancellation Finished
#define MCAN_IR_TFE    0x800U        // Tx FIFO Empty
#define MCAN_IR_TEFN   0x1000U       // Tx Event FIFO New Entry
#define MCAN_IR_TEFW   0x2000U       // Tx Event FIFO Watermark Reached
#define MCAN_IR_TEFF   0x4000U       // Tx Event FIFO Full
#define MCAN_IR_TEFL   0x8000U       // Tx Event FIFO Element Lost
#define MCAN_IR_TSW    0x10000U      // Timestamp Wraparound
#define MCAN_IR_MRAF   0x20000U      // Message RAM Access Failure
#define MCAN_IR_TOO    0x40000U      // Timeout Occurred
#define MCAN_IR_DRX    0x80000U      // Message Stored to Dedicated Rx Buffer
#define MCAN_IR_BEU    0x200000U     // Bit Error Uncorrected
#define MCAN_IR_ELO    0x400000U     // Error Logging Overflow
#define MCAN_IR_EP     0x800000U     // Error Passive
#define MCAN_IR_EW     0x1000000U    // Warning Status
#define MCAN_IR_BO     0x2000000U    // Bus_Off Status
#define MCAN_IR_WDI    0x4000000U    // Watchdog Interrupt
#define MCAN_IR_PEA    0x8000000U    // Protocol Error in Arbitration Phase
#define MCAN_IR_PED    0x10000000U   // Protocol Error in Data Phase
#define MCAN_IR_ARA    0x20000000U   // Access to Reserved Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_IE register
//
//*************************************************************************************************
#define MCAN_IE_RF0NE   0x1U          // Rx FIFO 0 New Message Enable
#define MCAN_IE_RF0WE   0x2U          // Rx FIFO 0 Watermark Reached Enable
#define MCAN_IE_RF0FE   0x4U          // Rx FIFO 0 Full Enable
#define MCAN_IE_RF0LE   0x8U          // Rx FIFO 0 Message Lost Enable
#define MCAN_IE_RF1NE   0x10U         // Rx FIFO 1 New Message Enable
#define MCAN_IE_RF1WE   0x20U         // Rx FIFO 1 Watermark Reached Enable
#define MCAN_IE_RF1FE   0x40U         // Rx FIFO 1 Full Enable
#define MCAN_IE_RF1LE   0x80U         // Rx FIFO 1 Message Lost Enable
#define MCAN_IE_HPME    0x100U        // High Priority Message Enable
#define MCAN_IE_TCE     0x200U        // Transmission Completed Enable
#define MCAN_IE_TCFE    0x400U        // Transmission Cancellation Finished Enable
#define MCAN_IE_TFEE    0x800U        // Tx FIFO Empty Enable
#define MCAN_IE_TEFNE   0x1000U       // Tx Event FIFO New Entry Enable
#define MCAN_IE_TEFWE   0x2000U       // Tx Event FIFO Watermark Reached Enable
#define MCAN_IE_TEFFE   0x4000U       // Tx Event FIFO Full Enable
#define MCAN_IE_TEFLE   0x8000U       // Tx Event FIFO Element Lost Enable
#define MCAN_IE_TSWE    0x10000U      // Timestamp Wraparound Enable
#define MCAN_IE_MRAFE   0x20000U      // Message RAM Access Failure Enable
#define MCAN_IE_TOOE    0x40000U      // Timeout Occurred Enable
#define MCAN_IE_DRXE    0x80000U      // Message Stored to Dedicated Rx Buffer Enable
#define MCAN_IE_BECE    0x100000U     // Bit Error Corrected Enable
#define MCAN_IE_BEUE    0x200000U     // Bit Error Uncorrected Enable
#define MCAN_IE_ELOE    0x400000U     // Error Logging Overflow Enable
#define MCAN_IE_EPE     0x800000U     // Error Passive Enable
#define MCAN_IE_EWE     0x1000000U    // Warning Status Enable
#define MCAN_IE_BOE     0x2000000U    // Bus_Off Status Enable
#define MCAN_IE_WDIE    0x4000000U    // Watchdog Interrupt Enable
#define MCAN_IE_PEAE    0x8000000U    // Protocol Error in Arbitration Phase Enable
#define MCAN_IE_PEDE    0x10000000U   // Protocol Error in Data Phase Enable
#define MCAN_IE_ARAE    0x20000000U   // Access to Reserved Address Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_ILS register
//
//*************************************************************************************************
#define MCAN_ILS_RF0NL   0x1U          // Rx FIFO 0 New Message Line
#define MCAN_ILS_RF0WL   0x2U          // Rx FIFO 0 Watermark Reached Line
#define MCAN_ILS_RF0FL   0x4U          // Rx FIFO 0 Full Line
#define MCAN_ILS_RF0LL   0x8U          // Rx FIFO 0 Message Lost Line
#define MCAN_ILS_RF1NL   0x10U         // Rx FIFO 1 New Message Line
#define MCAN_ILS_RF1WL   0x20U         // Rx FIFO 1 Watermark Reached Line
#define MCAN_ILS_RF1FL   0x40U         // Rx FIFO 1 Full Line
#define MCAN_ILS_RF1LL   0x80U         // Rx FIFO 1 Message Lost Line
#define MCAN_ILS_HPML    0x100U        // High Priority Message Line
#define MCAN_ILS_TCL     0x200U        // Transmission Completed Line
#define MCAN_ILS_TCFL    0x400U        // Transmission Cancellation Finished Line
#define MCAN_ILS_TFEL    0x800U        // Tx FIFO Empty Line
#define MCAN_ILS_TEFNL   0x1000U       // Tx Event FIFO New Entry Line
#define MCAN_ILS_TEFWL   0x2000U       // Tx Event FIFO Watermark Reached Line
#define MCAN_ILS_TEFFL   0x4000U       // Tx Event FIFO Full Line
#define MCAN_ILS_TEFLL   0x8000U       // Tx Event FIFO Element Lost Line
#define MCAN_ILS_TSWL    0x10000U      // Timestamp Wraparound Line
#define MCAN_ILS_MRAFL   0x20000U      // Message RAM Access Failure Line
#define MCAN_ILS_TOOL    0x40000U      // Timeout Occurred Line
#define MCAN_ILS_DRXL    0x80000U      // Message Stored to Dedicated Rx Buffer Line
#define MCAN_ILS_BECL    0x100000U     // Bit Error Corrected Line
#define MCAN_ILS_BEUL    0x200000U     // Bit Error Uncorrected Line
#define MCAN_ILS_ELOL    0x400000U     // Error Logging Overflow Line
#define MCAN_ILS_EPL     0x800000U     // Error Passive Line
#define MCAN_ILS_EWL     0x1000000U    // Warning Status Line
#define MCAN_ILS_BOL     0x2000000U    // Bus_Off Status Line
#define MCAN_ILS_WDIL    0x4000000U    // Watchdog Interrupt Line
#define MCAN_ILS_PEAL    0x8000000U    // Protocol Error in Arbitration Phase Line
#define MCAN_ILS_PEDL    0x10000000U   // Protocol Error in Data Phase Line
#define MCAN_ILS_ARAL    0x20000000U   // Access to Reserved Address Line

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_ILE register
//
//*************************************************************************************************
#define MCAN_ILE_EINT0   0x1U   // Enable Interrupt Line 0
#define MCAN_ILE_EINT1   0x2U   // Enable Interrupt Line 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_GFC register
//
//*************************************************************************************************
#define MCAN_GFC_RRFE     0x1U    // Reject Remote Frames Extended
#define MCAN_GFC_RRFS     0x2U    // Reject Remote Frames Standard
#define MCAN_GFC_ANFE_S   2U
#define MCAN_GFC_ANFE_M   0xCU    // Accept Non-matching Frames Extended
#define MCAN_GFC_ANFS_S   4U
#define MCAN_GFC_ANFS_M   0x30U   // Accept Non-matching Frames Standard

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_SIDFC register
//
//*************************************************************************************************
#define MCAN_SIDFC_FLSSA_S   2U
#define MCAN_SIDFC_FLSSA_M   0xFFFCU     // Filter List Standard Start Address
#define MCAN_SIDFC_LSS_S     16U
#define MCAN_SIDFC_LSS_M     0xFF0000U   // List Size Standard

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_XIDFC register
//
//*************************************************************************************************
#define MCAN_XIDFC_FLESA_S   2U
#define MCAN_XIDFC_FLESA_M   0xFFFCU     // Filter List Extended Start Address
#define MCAN_XIDFC_LSE_S     16U
#define MCAN_XIDFC_LSE_M     0x7F0000U   // List Size Extended

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_XIDAM register
//
//*************************************************************************************************
#define MCAN_XIDAM_EIDM_S   0U
#define MCAN_XIDAM_EIDM_M   0x1FFFFFFFU   // Extended ID Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_HPMS register
//
//*************************************************************************************************
#define MCAN_HPMS_BIDX_S   0U
#define MCAN_HPMS_BIDX_M   0x3FU     // Buffer Index
#define MCAN_HPMS_MSI_S    6U
#define MCAN_HPMS_MSI_M    0xC0U     // Message Storage Indicator
#define MCAN_HPMS_FIDX_S   8U
#define MCAN_HPMS_FIDX_M   0x7F00U   // Filter Index
#define MCAN_HPMS_FLST     0x8000U   // Filter List

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_NDAT1 register
//
//*************************************************************************************************
#define MCAN_NDAT1_ND0    0x1U          // New Data RX Buffer 0
#define MCAN_NDAT1_ND1    0x2U          // New Data RX Buffer 1
#define MCAN_NDAT1_ND2    0x4U          // New Data RX Buffer 2
#define MCAN_NDAT1_ND3    0x8U          // New Data RX Buffer 3
#define MCAN_NDAT1_ND4    0x10U         // New Data RX Buffer 4
#define MCAN_NDAT1_ND5    0x20U         // New Data RX Buffer 5
#define MCAN_NDAT1_ND6    0x40U         // New Data RX Buffer 6
#define MCAN_NDAT1_ND7    0x80U         // New Data RX Buffer 7
#define MCAN_NDAT1_ND8    0x100U        // New Data RX Buffer 8
#define MCAN_NDAT1_ND9    0x200U        // New Data RX Buffer 9
#define MCAN_NDAT1_ND10   0x400U        // New Data RX Buffer 10
#define MCAN_NDAT1_ND11   0x800U        // New Data RX Buffer 11
#define MCAN_NDAT1_ND12   0x1000U       // New Data RX Buffer 12
#define MCAN_NDAT1_ND13   0x2000U       // New Data RX Buffer 13
#define MCAN_NDAT1_ND14   0x4000U       // New Data RX Buffer 14
#define MCAN_NDAT1_ND15   0x8000U       // New Data RX Buffer 15
#define MCAN_NDAT1_ND16   0x10000U      // New Data RX Buffer 16
#define MCAN_NDAT1_ND17   0x20000U      // New Data RX Buffer 17
#define MCAN_NDAT1_ND18   0x40000U      // New Data RX Buffer 18
#define MCAN_NDAT1_ND19   0x80000U      // New Data RX Buffer 19
#define MCAN_NDAT1_ND20   0x100000U     // New Data RX Buffer 20
#define MCAN_NDAT1_ND21   0x200000U     // New Data RX Buffer 21
#define MCAN_NDAT1_ND22   0x400000U     // New Data RX Buffer 22
#define MCAN_NDAT1_ND23   0x800000U     // New Data RX Buffer 23
#define MCAN_NDAT1_ND24   0x1000000U    // New Data RX Buffer 24
#define MCAN_NDAT1_ND25   0x2000000U    // New Data RX Buffer 25
#define MCAN_NDAT1_ND26   0x4000000U    // New Data RX Buffer 26
#define MCAN_NDAT1_ND27   0x8000000U    // New Data RX Buffer 27
#define MCAN_NDAT1_ND28   0x10000000U   // New Data RX Buffer 28
#define MCAN_NDAT1_ND29   0x20000000U   // New Data RX Buffer 29
#define MCAN_NDAT1_ND30   0x40000000U   // New Data RX Buffer 30
#define MCAN_NDAT1_ND31   0x80000000U   // New Data RX Buffer 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_NDAT2 register
//
//*************************************************************************************************
#define MCAN_NDAT2_ND32   0x1U          // New Data RX Buffer 32
#define MCAN_NDAT2_ND33   0x2U          // New Data RX Buffer 33
#define MCAN_NDAT2_ND34   0x4U          // New Data RX Buffer 34
#define MCAN_NDAT2_ND35   0x8U          // New Data RX Buffer 35
#define MCAN_NDAT2_ND36   0x10U         // New Data RX Buffer 36
#define MCAN_NDAT2_ND37   0x20U         // New Data RX Buffer 37
#define MCAN_NDAT2_ND38   0x40U         // New Data RX Buffer 38
#define MCAN_NDAT2_ND39   0x80U         // New Data RX Buffer 39
#define MCAN_NDAT2_ND40   0x100U        // New Data RX Buffer 40
#define MCAN_NDAT2_ND41   0x200U        // New Data RX Buffer 41
#define MCAN_NDAT2_ND42   0x400U        // New Data RX Buffer 42
#define MCAN_NDAT2_ND43   0x800U        // New Data RX Buffer 43
#define MCAN_NDAT2_ND44   0x1000U       // New Data RX Buffer 44
#define MCAN_NDAT2_ND45   0x2000U       // New Data RX Buffer 45
#define MCAN_NDAT2_ND46   0x4000U       // New Data RX Buffer 46
#define MCAN_NDAT2_ND47   0x8000U       // New Data RX Buffer 47
#define MCAN_NDAT2_ND48   0x10000U      // New Data RX Buffer 48
#define MCAN_NDAT2_ND49   0x20000U      // New Data RX Buffer 49
#define MCAN_NDAT2_ND50   0x40000U      // New Data RX Buffer 50
#define MCAN_NDAT2_ND51   0x80000U      // New Data RX Buffer 51
#define MCAN_NDAT2_ND52   0x100000U     // New Data RX Buffer 52
#define MCAN_NDAT2_ND53   0x200000U     // New Data RX Buffer 53
#define MCAN_NDAT2_ND54   0x400000U     // New Data RX Buffer 54
#define MCAN_NDAT2_ND55   0x800000U     // New Data RX Buffer 55
#define MCAN_NDAT2_ND56   0x1000000U    // New Data RX Buffer 56
#define MCAN_NDAT2_ND57   0x2000000U    // New Data RX Buffer 57
#define MCAN_NDAT2_ND58   0x4000000U    // New Data RX Buffer 58
#define MCAN_NDAT2_ND59   0x8000000U    // New Data RX Buffer 59
#define MCAN_NDAT2_ND60   0x10000000U   // New Data RX Buffer 60
#define MCAN_NDAT2_ND61   0x20000000U   // New Data RX Buffer 61
#define MCAN_NDAT2_ND62   0x40000000U   // New Data RX Buffer 62
#define MCAN_NDAT2_ND63   0x80000000U   // New Data RX Buffer 63

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF0C register
//
//*************************************************************************************************
#define MCAN_RXF0C_F0SA_S   2U
#define MCAN_RXF0C_F0SA_M   0xFFFCU       // Rx FIFO 0 Start Address
#define MCAN_RXF0C_F0S_S    16U
#define MCAN_RXF0C_F0S_M    0x7F0000U     // Rx FIFO 0 Size
#define MCAN_RXF0C_F0WM_S   24U
#define MCAN_RXF0C_F0WM_M   0x7F000000U   // Rx FIFO 0 Watermark
#define MCAN_RXF0C_F0OM     0x80000000U   // FIFO 0 Operation Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF0S register
//
//*************************************************************************************************
#define MCAN_RXF0S_F0FL_S   0U
#define MCAN_RXF0S_F0FL_M   0x7FU        // Rx FIFO 0 Fill Level
#define MCAN_RXF0S_F0GI_S   8U
#define MCAN_RXF0S_F0GI_M   0x3F00U      // Rx FIFO 0 Get Index
#define MCAN_RXF0S_F0PI_S   16U
#define MCAN_RXF0S_F0PI_M   0x3F0000U    // Rx FIFO 0 Put Index
#define MCAN_RXF0S_F0F      0x1000000U   // Rx FIFO 0 Full
#define MCAN_RXF0S_RF0L     0x2000000U   // Rx FIFO 0 Message Lost

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF0A register
//
//*************************************************************************************************
#define MCAN_RXF0A_F0AI_S   0U
#define MCAN_RXF0A_F0AI_M   0x3FU   // Rx FIFO 0 Acknowledge Index

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXBC register
//
//*************************************************************************************************
#define MCAN_RXBC_RBSA_S   2U
#define MCAN_RXBC_RBSA_M   0xFFFCU   // Rx Buffer Start Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF1C register
//
//*************************************************************************************************
#define MCAN_RXF1C_F1SA_S   2U
#define MCAN_RXF1C_F1SA_M   0xFFFCU       // Rx FIFO 1 Start Address
#define MCAN_RXF1C_F1S_S    16U
#define MCAN_RXF1C_F1S_M    0x7F0000U     // Rx FIFO 1 Size
#define MCAN_RXF1C_F1WM_S   24U
#define MCAN_RXF1C_F1WM_M   0x7F000000U   // Rx FIFO 1 Watermark
#define MCAN_RXF1C_F1OM     0x80000000U   // FIFO 1 Operation Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF1S register
//
//*************************************************************************************************
#define MCAN_RXF1S_F1FL_S   0U
#define MCAN_RXF1S_F1FL_M   0x7FU         // Rx FIFO 1 Fill Level
#define MCAN_RXF1S_F1GI_S   8U
#define MCAN_RXF1S_F1GI_M   0x3F00U       // Rx FIFO 1 Get Index
#define MCAN_RXF1S_F1PI_S   16U
#define MCAN_RXF1S_F1PI_M   0x3F0000U     // Rx FIFO 1 Put Index
#define MCAN_RXF1S_F1F      0x1000000U    // Rx FIFO 1 Full
#define MCAN_RXF1S_RF1L     0x2000000U    // Rx FIFO 1 Message Lost
#define MCAN_RXF1S_DMS_S    30U
#define MCAN_RXF1S_DMS_M    0xC0000000U   // Debug Message Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXF1A register
//
//*************************************************************************************************
#define MCAN_RXF1A_F1AI_S   0U
#define MCAN_RXF1A_F1AI_M   0x3FU   // Rx FIFO 1 Acknowledge Index

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_RXESC register
//
//*************************************************************************************************
#define MCAN_RXESC_F0DS_S   0U
#define MCAN_RXESC_F0DS_M   0x7U     // Rx FIFO 0 Data Field Size
#define MCAN_RXESC_F1DS_S   4U
#define MCAN_RXESC_F1DS_M   0x70U    // Rx FIFO 1 Data Field Size
#define MCAN_RXESC_RBDS_S   8U
#define MCAN_RXESC_RBDS_M   0x700U   // Rx Buffer Data Field Size

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBC register
//
//*************************************************************************************************
#define MCAN_TXBC_TBSA_S   2U
#define MCAN_TXBC_TBSA_M   0xFFFCU       // Tx Buffers Start Address
#define MCAN_TXBC_NDTB_S   16U
#define MCAN_TXBC_NDTB_M   0x3F0000U     // Number of Dedicated Transmit Buffers
#define MCAN_TXBC_TFQS_S   24U
#define MCAN_TXBC_TFQS_M   0x3F000000U   // Transmit FIFO/Queue Size
#define MCAN_TXBC_TFQM     0x40000000U   // Tx FIFO/Queue Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXFQS register
//
//*************************************************************************************************
#define MCAN_TXFQS_TFFL_S   0U
#define MCAN_TXFQS_TFFL_M   0x3FU       // Tx FIFO Free Level
#define MCAN_TXFQS_TFGI_S   8U
#define MCAN_TXFQS_TFGI_M   0x1F00U     // Tx FIFO Get Index
#define MCAN_TXFQS_TFQP_S   16U
#define MCAN_TXFQS_TFQP_M   0x1F0000U   // Tx FIFO/Queue Put Index
#define MCAN_TXFQS_TFQF     0x200000U   // Tx FIFO/Queue Full

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXESC register
//
//*************************************************************************************************
#define MCAN_TXESC_TBDS_S   0U
#define MCAN_TXESC_TBDS_M   0x7U   // Tx Buffer Data Field Size

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBRP register
//
//*************************************************************************************************
#define MCAN_TXBRP_TRP0    0x1U          // Transmission Request Pending 0
#define MCAN_TXBRP_TRP1    0x2U          // Transmission Request Pending 1
#define MCAN_TXBRP_TRP2    0x4U          // Transmission Request Pending 2
#define MCAN_TXBRP_TRP3    0x8U          // Transmission Request Pending 3
#define MCAN_TXBRP_TRP4    0x10U         // Transmission Request Pending 4
#define MCAN_TXBRP_TRP5    0x20U         // Transmission Request Pending 5
#define MCAN_TXBRP_TRP6    0x40U         // Transmission Request Pending 6
#define MCAN_TXBRP_TRP7    0x80U         // Transmission Request Pending 7
#define MCAN_TXBRP_TRP8    0x100U        // Transmission Request Pending 8
#define MCAN_TXBRP_TRP9    0x200U        // Transmission Request Pending 9
#define MCAN_TXBRP_TRP10   0x400U        // Transmission Request Pending 10
#define MCAN_TXBRP_TRP11   0x800U        // Transmission Request Pending 11
#define MCAN_TXBRP_TRP12   0x1000U       // Transmission Request Pending 12
#define MCAN_TXBRP_TRP13   0x2000U       // Transmission Request Pending 13
#define MCAN_TXBRP_TRP14   0x4000U       // Transmission Request Pending 14
#define MCAN_TXBRP_TRP15   0x8000U       // Transmission Request Pending 15
#define MCAN_TXBRP_TRP16   0x10000U      // Transmission Request Pending 16
#define MCAN_TXBRP_TRP17   0x20000U      // Transmission Request Pending 17
#define MCAN_TXBRP_TRP18   0x40000U      // Transmission Request Pending 18
#define MCAN_TXBRP_TRP19   0x80000U      // Transmission Request Pending 19
#define MCAN_TXBRP_TRP20   0x100000U     // Transmission Request Pending 20
#define MCAN_TXBRP_TRP21   0x200000U     // Transmission Request Pending 21
#define MCAN_TXBRP_TRP22   0x400000U     // Transmission Request Pending 22
#define MCAN_TXBRP_TRP23   0x800000U     // Transmission Request Pending 23
#define MCAN_TXBRP_TRP24   0x1000000U    // Transmission Request Pending 24
#define MCAN_TXBRP_TRP25   0x2000000U    // Transmission Request Pending 25
#define MCAN_TXBRP_TRP26   0x4000000U    // Transmission Request Pending 26
#define MCAN_TXBRP_TRP27   0x8000000U    // Transmission Request Pending 27
#define MCAN_TXBRP_TRP28   0x10000000U   // Transmission Request Pending 28
#define MCAN_TXBRP_TRP29   0x20000000U   // Transmission Request Pending 29
#define MCAN_TXBRP_TRP30   0x40000000U   // Transmission Request Pending 30
#define MCAN_TXBRP_TRP31   0x80000000U   // Transmission Request Pending 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBAR register
//
//*************************************************************************************************
#define MCAN_TXBAR_AR0    0x1U          // Add Request 0
#define MCAN_TXBAR_AR1    0x2U          // Add Request 1
#define MCAN_TXBAR_AR2    0x4U          // Add Request 2
#define MCAN_TXBAR_AR3    0x8U          // Add Request 3
#define MCAN_TXBAR_AR4    0x10U         // Add Request 4
#define MCAN_TXBAR_AR5    0x20U         // Add Request 5
#define MCAN_TXBAR_AR6    0x40U         // Add Request 6
#define MCAN_TXBAR_AR7    0x80U         // Add Request 7
#define MCAN_TXBAR_AR8    0x100U        // Add Request 8
#define MCAN_TXBAR_AR9    0x200U        // Add Request 9
#define MCAN_TXBAR_AR10   0x400U        // Add Request 10
#define MCAN_TXBAR_AR11   0x800U        // Add Request 11
#define MCAN_TXBAR_AR12   0x1000U       // Add Request 12
#define MCAN_TXBAR_AR13   0x2000U       // Add Request 13
#define MCAN_TXBAR_AR14   0x4000U       // Add Request 14
#define MCAN_TXBAR_AR15   0x8000U       // Add Request 15
#define MCAN_TXBAR_AR16   0x10000U      // Add Request 16
#define MCAN_TXBAR_AR17   0x20000U      // Add Request 17
#define MCAN_TXBAR_AR18   0x40000U      // Add Request 18
#define MCAN_TXBAR_AR19   0x80000U      // Add Request 19
#define MCAN_TXBAR_AR20   0x100000U     // Add Request 20
#define MCAN_TXBAR_AR21   0x200000U     // Add Request 21
#define MCAN_TXBAR_AR22   0x400000U     // Add Request 22
#define MCAN_TXBAR_AR23   0x800000U     // Add Request 23
#define MCAN_TXBAR_AR24   0x1000000U    // Add Request 24
#define MCAN_TXBAR_AR25   0x2000000U    // Add Request 25
#define MCAN_TXBAR_AR26   0x4000000U    // Add Request 26
#define MCAN_TXBAR_AR27   0x8000000U    // Add Request 27
#define MCAN_TXBAR_AR28   0x10000000U   // Add Request 28
#define MCAN_TXBAR_AR29   0x20000000U   // Add Request 29
#define MCAN_TXBAR_AR30   0x40000000U   // Add Request 30
#define MCAN_TXBAR_AR31   0x80000000U   // Add Request 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBCR register
//
//*************************************************************************************************
#define MCAN_TXBCR_CR0    0x1U          // Cancellation Request 0
#define MCAN_TXBCR_CR1    0x2U          // Cancellation Request 1
#define MCAN_TXBCR_CR2    0x4U          // Cancellation Request 2
#define MCAN_TXBCR_CR3    0x8U          // Cancellation Request 3
#define MCAN_TXBCR_CR4    0x10U         // Cancellation Request 4
#define MCAN_TXBCR_CR5    0x20U         // Cancellation Request 5
#define MCAN_TXBCR_CR6    0x40U         // Cancellation Request 6
#define MCAN_TXBCR_CR7    0x80U         // Cancellation Request 7
#define MCAN_TXBCR_CR8    0x100U        // Cancellation Request 8
#define MCAN_TXBCR_CR9    0x200U        // Cancellation Request 9
#define MCAN_TXBCR_CR10   0x400U        // Cancellation Request 10
#define MCAN_TXBCR_CR11   0x800U        // Cancellation Request 11
#define MCAN_TXBCR_CR12   0x1000U       // Cancellation Request 12
#define MCAN_TXBCR_CR13   0x2000U       // Cancellation Request 13
#define MCAN_TXBCR_CR14   0x4000U       // Cancellation Request 14
#define MCAN_TXBCR_CR15   0x8000U       // Cancellation Request 15
#define MCAN_TXBCR_CR16   0x10000U      // Cancellation Request 16
#define MCAN_TXBCR_CR17   0x20000U      // Cancellation Request 17
#define MCAN_TXBCR_CR18   0x40000U      // Cancellation Request 18
#define MCAN_TXBCR_CR19   0x80000U      // Cancellation Request 19
#define MCAN_TXBCR_CR20   0x100000U     // Cancellation Request 20
#define MCAN_TXBCR_CR21   0x200000U     // Cancellation Request 21
#define MCAN_TXBCR_CR22   0x400000U     // Cancellation Request 22
#define MCAN_TXBCR_CR23   0x800000U     // Cancellation Request 23
#define MCAN_TXBCR_CR24   0x1000000U    // Cancellation Request 24
#define MCAN_TXBCR_CR25   0x2000000U    // Cancellation Request 25
#define MCAN_TXBCR_CR26   0x4000000U    // Cancellation Request 26
#define MCAN_TXBCR_CR27   0x8000000U    // Cancellation Request 27
#define MCAN_TXBCR_CR28   0x10000000U   // Cancellation Request 28
#define MCAN_TXBCR_CR29   0x20000000U   // Cancellation Request 29
#define MCAN_TXBCR_CR30   0x40000000U   // Cancellation Request 30
#define MCAN_TXBCR_CR31   0x80000000U   // Cancellation Request 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBTO register
//
//*************************************************************************************************
#define MCAN_TXBTO_TO0    0x1U          // Transmission Occurred 0
#define MCAN_TXBTO_TO1    0x2U          // Transmission Occurred 1
#define MCAN_TXBTO_TO2    0x4U          // Transmission Occurred 2
#define MCAN_TXBTO_TO3    0x8U          // Transmission Occurred 3
#define MCAN_TXBTO_TO4    0x10U         // Transmission Occurred 4
#define MCAN_TXBTO_TO5    0x20U         // Transmission Occurred 5
#define MCAN_TXBTO_TO6    0x40U         // Transmission Occurred 6
#define MCAN_TXBTO_TO7    0x80U         // Transmission Occurred 7
#define MCAN_TXBTO_TO8    0x100U        // Transmission Occurred 8
#define MCAN_TXBTO_TO9    0x200U        // Transmission Occurred 9
#define MCAN_TXBTO_TO10   0x400U        // Transmission Occurred 10
#define MCAN_TXBTO_TO11   0x800U        // Transmission Occurred 11
#define MCAN_TXBTO_TO12   0x1000U       // Transmission Occurred 12
#define MCAN_TXBTO_TO13   0x2000U       // Transmission Occurred 13
#define MCAN_TXBTO_TO14   0x4000U       // Transmission Occurred 14
#define MCAN_TXBTO_TO15   0x8000U       // Transmission Occurred 15
#define MCAN_TXBTO_TO16   0x10000U      // Transmission Occurred 16
#define MCAN_TXBTO_TO17   0x20000U      // Transmission Occurred 17
#define MCAN_TXBTO_TO18   0x40000U      // Transmission Occurred 18
#define MCAN_TXBTO_TO19   0x80000U      // Transmission Occurred 19
#define MCAN_TXBTO_TO20   0x100000U     // Transmission Occurred 20
#define MCAN_TXBTO_TO21   0x200000U     // Transmission Occurred 21
#define MCAN_TXBTO_TO22   0x400000U     // Transmission Occurred 22
#define MCAN_TXBTO_TO23   0x800000U     // Transmission Occurred 23
#define MCAN_TXBTO_TO24   0x1000000U    // Transmission Occurred 24
#define MCAN_TXBTO_TO25   0x2000000U    // Transmission Occurred 25
#define MCAN_TXBTO_TO26   0x4000000U    // Transmission Occurred 26
#define MCAN_TXBTO_TO27   0x8000000U    // Transmission Occurred 27
#define MCAN_TXBTO_TO28   0x10000000U   // Transmission Occurred 28
#define MCAN_TXBTO_TO29   0x20000000U   // Transmission Occurred 29
#define MCAN_TXBTO_TO30   0x40000000U   // Transmission Occurred 30
#define MCAN_TXBTO_TO31   0x80000000U   // Transmission Occurred 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBCF register
//
//*************************************************************************************************
#define MCAN_TXBCF_CF0    0x1U          // Cancellation Finished 0
#define MCAN_TXBCF_CF1    0x2U          // Cancellation Finished 1
#define MCAN_TXBCF_CF2    0x4U          // Cancellation Finished 2
#define MCAN_TXBCF_CF3    0x8U          // Cancellation Finished 3
#define MCAN_TXBCF_CF4    0x10U         // Cancellation Finished 4
#define MCAN_TXBCF_CF5    0x20U         // Cancellation Finished 5
#define MCAN_TXBCF_CF6    0x40U         // Cancellation Finished 6
#define MCAN_TXBCF_CF7    0x80U         // Cancellation Finished 7
#define MCAN_TXBCF_CF8    0x100U        // Cancellation Finished 8
#define MCAN_TXBCF_CF9    0x200U        // Cancellation Finished 9
#define MCAN_TXBCF_CF10   0x400U        // Cancellation Finished 10
#define MCAN_TXBCF_CF11   0x800U        // Cancellation Finished 11
#define MCAN_TXBCF_CF12   0x1000U       // Cancellation Finished 12
#define MCAN_TXBCF_CF13   0x2000U       // Cancellation Finished 13
#define MCAN_TXBCF_CF14   0x4000U       // Cancellation Finished 14
#define MCAN_TXBCF_CF15   0x8000U       // Cancellation Finished 15
#define MCAN_TXBCF_CF16   0x10000U      // Cancellation Finished 16
#define MCAN_TXBCF_CF17   0x20000U      // Cancellation Finished 17
#define MCAN_TXBCF_CF18   0x40000U      // Cancellation Finished 18
#define MCAN_TXBCF_CF19   0x80000U      // Cancellation Finished 19
#define MCAN_TXBCF_CF20   0x100000U     // Cancellation Finished 20
#define MCAN_TXBCF_CF21   0x200000U     // Cancellation Finished 21
#define MCAN_TXBCF_CF22   0x400000U     // Cancellation Finished 22
#define MCAN_TXBCF_CF23   0x800000U     // Cancellation Finished 23
#define MCAN_TXBCF_CF24   0x1000000U    // Cancellation Finished 24
#define MCAN_TXBCF_CF25   0x2000000U    // Cancellation Finished 25
#define MCAN_TXBCF_CF26   0x4000000U    // Cancellation Finished 26
#define MCAN_TXBCF_CF27   0x8000000U    // Cancellation Finished 27
#define MCAN_TXBCF_CF28   0x10000000U   // Cancellation Finished 28
#define MCAN_TXBCF_CF29   0x20000000U   // Cancellation Finished 29
#define MCAN_TXBCF_CF30   0x40000000U   // Cancellation Finished 30
#define MCAN_TXBCF_CF31   0x80000000U   // Cancellation Finished 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBTIE register
//
//*************************************************************************************************
#define MCAN_TXBTIE_TIE0    0x1U          // Transmission Interrupt Enable 0
#define MCAN_TXBTIE_TIE1    0x2U          // Transmission Interrupt Enable 1
#define MCAN_TXBTIE_TIE2    0x4U          // Transmission Interrupt Enable 2
#define MCAN_TXBTIE_TIE3    0x8U          // Transmission Interrupt Enable 3
#define MCAN_TXBTIE_TIE4    0x10U         // Transmission Interrupt Enable 4
#define MCAN_TXBTIE_TIE5    0x20U         // Transmission Interrupt Enable 5
#define MCAN_TXBTIE_TIE6    0x40U         // Transmission Interrupt Enable 6
#define MCAN_TXBTIE_TIE7    0x80U         // Transmission Interrupt Enable 7
#define MCAN_TXBTIE_TIE8    0x100U        // Transmission Interrupt Enable 8
#define MCAN_TXBTIE_TIE9    0x200U        // Transmission Interrupt Enable 9
#define MCAN_TXBTIE_TIE10   0x400U        // Transmission Interrupt Enable 10
#define MCAN_TXBTIE_TIE11   0x800U        // Transmission Interrupt Enable 11
#define MCAN_TXBTIE_TIE12   0x1000U       // Transmission Interrupt Enable 12
#define MCAN_TXBTIE_TIE13   0x2000U       // Transmission Interrupt Enable 13
#define MCAN_TXBTIE_TIE14   0x4000U       // Transmission Interrupt Enable 14
#define MCAN_TXBTIE_TIE15   0x8000U       // Transmission Interrupt Enable 15
#define MCAN_TXBTIE_TIE16   0x10000U      // Transmission Interrupt Enable 16
#define MCAN_TXBTIE_TIE17   0x20000U      // Transmission Interrupt Enable 17
#define MCAN_TXBTIE_TIE18   0x40000U      // Transmission Interrupt Enable 18
#define MCAN_TXBTIE_TIE19   0x80000U      // Transmission Interrupt Enable 19
#define MCAN_TXBTIE_TIE20   0x100000U     // Transmission Interrupt Enable 20
#define MCAN_TXBTIE_TIE21   0x200000U     // Transmission Interrupt Enable 21
#define MCAN_TXBTIE_TIE22   0x400000U     // Transmission Interrupt Enable 22
#define MCAN_TXBTIE_TIE23   0x800000U     // Transmission Interrupt Enable 23
#define MCAN_TXBTIE_TIE24   0x1000000U    // Transmission Interrupt Enable 24
#define MCAN_TXBTIE_TIE25   0x2000000U    // Transmission Interrupt Enable 25
#define MCAN_TXBTIE_TIE26   0x4000000U    // Transmission Interrupt Enable 26
#define MCAN_TXBTIE_TIE27   0x8000000U    // Transmission Interrupt Enable 27
#define MCAN_TXBTIE_TIE28   0x10000000U   // Transmission Interrupt Enable 28
#define MCAN_TXBTIE_TIE29   0x20000000U   // Transmission Interrupt Enable 29
#define MCAN_TXBTIE_TIE30   0x40000000U   // Transmission Interrupt Enable 30
#define MCAN_TXBTIE_TIE31   0x80000000U   // Transmission Interrupt Enable 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXBCIE register
//
//*************************************************************************************************
#define MCAN_TXBCIE_CFIE0    0x1U          // Cancellation Finished Interrupt Enable 0
#define MCAN_TXBCIE_CFIE1    0x2U          // Cancellation Finished Interrupt Enable 1
#define MCAN_TXBCIE_CFIE2    0x4U          // Cancellation Finished Interrupt Enable 2
#define MCAN_TXBCIE_CFIE3    0x8U          // Cancellation Finished Interrupt Enable 3
#define MCAN_TXBCIE_CFIE4    0x10U         // Cancellation Finished Interrupt Enable 4
#define MCAN_TXBCIE_CFIE5    0x20U         // Cancellation Finished Interrupt Enable 5
#define MCAN_TXBCIE_CFIE6    0x40U         // Cancellation Finished Interrupt Enable 6
#define MCAN_TXBCIE_CFIE7    0x80U         // Cancellation Finished Interrupt Enable 7
#define MCAN_TXBCIE_CFIE8    0x100U        // Cancellation Finished Interrupt Enable 8
#define MCAN_TXBCIE_CFIE9    0x200U        // Cancellation Finished Interrupt Enable 9
#define MCAN_TXBCIE_CFIE10   0x400U        // Cancellation Finished Interrupt Enable 10
#define MCAN_TXBCIE_CFIE11   0x800U        // Cancellation Finished Interrupt Enable 11
#define MCAN_TXBCIE_CFIE12   0x1000U       // Cancellation Finished Interrupt Enable 12
#define MCAN_TXBCIE_CFIE13   0x2000U       // Cancellation Finished Interrupt Enable 13
#define MCAN_TXBCIE_CFIE14   0x4000U       // Cancellation Finished Interrupt Enable 14
#define MCAN_TXBCIE_CFIE15   0x8000U       // Cancellation Finished Interrupt Enable 15
#define MCAN_TXBCIE_CFIE16   0x10000U      // Cancellation Finished Interrupt Enable 16
#define MCAN_TXBCIE_CFIE17   0x20000U      // Cancellation Finished Interrupt Enable 17
#define MCAN_TXBCIE_CFIE18   0x40000U      // Cancellation Finished Interrupt Enable 18
#define MCAN_TXBCIE_CFIE19   0x80000U      // Cancellation Finished Interrupt Enable 19
#define MCAN_TXBCIE_CFIE20   0x100000U     // Cancellation Finished Interrupt Enable 20
#define MCAN_TXBCIE_CFIE21   0x200000U     // Cancellation Finished Interrupt Enable 21
#define MCAN_TXBCIE_CFIE22   0x400000U     // Cancellation Finished Interrupt Enable 22
#define MCAN_TXBCIE_CFIE23   0x800000U     // Cancellation Finished Interrupt Enable 23
#define MCAN_TXBCIE_CFIE24   0x1000000U    // Cancellation Finished Interrupt Enable 24
#define MCAN_TXBCIE_CFIE25   0x2000000U    // Cancellation Finished Interrupt Enable 25
#define MCAN_TXBCIE_CFIE26   0x4000000U    // Cancellation Finished Interrupt Enable 26
#define MCAN_TXBCIE_CFIE27   0x8000000U    // Cancellation Finished Interrupt Enable 27
#define MCAN_TXBCIE_CFIE28   0x10000000U   // Cancellation Finished Interrupt Enable 28
#define MCAN_TXBCIE_CFIE29   0x20000000U   // Cancellation Finished Interrupt Enable 29
#define MCAN_TXBCIE_CFIE30   0x40000000U   // Cancellation Finished Interrupt Enable 30
#define MCAN_TXBCIE_CFIE31   0x80000000U   // Cancellation Finished Interrupt Enable 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXEFC register
//
//*************************************************************************************************
#define MCAN_TXEFC_EFSA_S   2U
#define MCAN_TXEFC_EFSA_M   0xFFFCU       // Event FIFO Start Address
#define MCAN_TXEFC_EFS_S    16U
#define MCAN_TXEFC_EFS_M    0x3F0000U     // Event FIFO Size
#define MCAN_TXEFC_EFWM_S   24U
#define MCAN_TXEFC_EFWM_M   0x3F000000U   // Event FIFO Watermark

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXEFS register
//
//*************************************************************************************************
#define MCAN_TXEFS_EFFL_S   0U
#define MCAN_TXEFS_EFFL_M   0x3FU        // Event FIFO Fill Level
#define MCAN_TXEFS_EFGI_S   8U
#define MCAN_TXEFS_EFGI_M   0x1F00U      // Event FIFO Get Index
#define MCAN_TXEFS_EFPI_S   16U
#define MCAN_TXEFS_EFPI_M   0x1F0000U    // Event FIFO Put Index
#define MCAN_TXEFS_EFF      0x1000000U   // Event FIFO Full
#define MCAN_TXEFS_TEFL     0x2000000U   // Tx Event FIFO Element Lost

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCAN_TXEFA register
//
//*************************************************************************************************
#define MCAN_TXEFA_EFAI_S   0U
#define MCAN_TXEFA_EFAI_M   0x1FU   // Event FIFO Acknowledge Index


//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_REV register
//
//*************************************************************************************************
#define MCAN_ERR_REV_REVMIN_S      0U
#define MCAN_ERR_REV_REVMIN_M      0x3FU         // Minor Revision
#define MCAN_ERR_REV_REVMAJ_S      8U
#define MCAN_ERR_REV_REVMAJ_M      0x700U        // Major Revision
#define MCAN_ERR_REV_MODULE_ID_S   16U
#define MCAN_ERR_REV_MODULE_ID_M   0xFFF0000U    // Module Identification Number
#define MCAN_ERR_REV_SCHEME_S      30U
#define MCAN_ERR_REV_SCHEME_M      0xC0000000U   // PID Register Scheme

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_VECTOR register
//
//*************************************************************************************************
#define MCAN_ERR_VECTOR_ECC_VECTOR_S         0U
#define MCAN_ERR_VECTOR_ECC_VECTOR_M         0x7FFU       // ECC RAM ID
#define MCAN_ERR_VECTOR_RD_SVBUS             0x8000U      // Read Trigger
#define MCAN_ERR_VECTOR_RD_SVBUS_ADDRESS_S   16U
#define MCAN_ERR_VECTOR_RD_SVBUS_ADDRESS_M   0xFF0000U    // Read Address Offset
#define MCAN_ERR_VECTOR_RD_SVBUS_DONE        0x1000000U   // Read Completion Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_STAT register
//
//*************************************************************************************************
#define MCAN_ERR_STAT_NUM_RAMS_S   0U
#define MCAN_ERR_STAT_NUM_RAMS_M   0x7FFU   // Number of RAMs

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_WRAP_REV register
//
//*************************************************************************************************
#define MCAN_ERR_WRAP_REV_REVMIN_S      0U
#define MCAN_ERR_WRAP_REV_REVMIN_M      0x3FU         // Minor Revision
#define MCAN_ERR_WRAP_REV_REVMAJ_S      8U
#define MCAN_ERR_WRAP_REV_REVMAJ_M      0x700U        // Major Revision
#define MCAN_ERR_WRAP_REV_MODULE_ID_S   16U
#define MCAN_ERR_WRAP_REV_MODULE_ID_M   0xFFF0000U    // Module Identification Number
#define MCAN_ERR_WRAP_REV_SCHEME_S      30U
#define MCAN_ERR_WRAP_REV_SCHEME_M      0xC0000000U   // PID Register Scheme

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_CTRL register
//
//*************************************************************************************************
#define MCAN_ERR_CTRL_ECC_ENABLE            0x1U     // Enable ECC Generation
#define MCAN_ERR_CTRL_ECC_CHECK             0x2U     // Enable ECC Check
#define MCAN_ERR_CTRL_ENABLE_RMW            0x4U     // Enable Read-Modify-Write
#define MCAN_ERR_CTRL_FORCE_SEC             0x8U     // Force Single Bit Error Corrected Error
#define MCAN_ERR_CTRL_FORCE_DED             0x10U    // Force Double Bit Error Detected Error
#define MCAN_ERR_CTRL_FORCE_N_ROW           0x20U    // Force Next Single/Double Bit Error
#define MCAN_ERR_CTRL_ERROR_ONCE            0x40U    // Force Error Only Once Enable
#define MCAN_ERR_CTRL_CHECK_SVBUS_TIMEOUT   0x100U   // SVBUS Timeout Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_ERR_CTRL2 register
//
//*************************************************************************************************
#define MCAN_ERR_ERR_CTRL2_ECC_BIT1_S   0U
#define MCAN_ERR_ERR_CTRL2_ECC_BIT1_M   0xFFFFU       // Force Error Bit1 Column Index
#define MCAN_ERR_ERR_CTRL2_ECC_BIT2_S   16U
#define MCAN_ERR_ERR_CTRL2_ECC_BIT2_M   0xFFFF0000U   // Force Error Bit2 Column Index

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_ERR_STAT1 register
//
//*************************************************************************************************
#define MCAN_ERR_ERR_STAT1_ECC_SEC_S            0U
#define MCAN_ERR_ERR_STAT1_ECC_SEC_M            0x3U          // Single Bit Error Corrected Status
#define MCAN_ERR_ERR_STAT1_ECC_DED_S            2U
#define MCAN_ERR_ERR_STAT1_ECC_DED_M            0xCU          // Double Bit Error Detected Status
#define MCAN_ERR_ERR_STAT1_ECC_OTHER            0x10U         // SEC While Writeback Error Status
#define MCAN_ERR_ERR_STAT1_CTRL_REG_ERROR       0x80U         // Control Register Error
#define MCAN_ERR_ERR_STAT1_CLR_ECC_SEC_S        8U
#define MCAN_ERR_ERR_STAT1_CLR_ECC_SEC_M        0x300U        // Clear ECC_SEC
#define MCAN_ERR_ERR_STAT1_CLR_ECC_DED_S        10U
#define MCAN_ERR_ERR_STAT1_CLR_ECC_DED_M        0xC00U        // Clear ECC_DED
#define MCAN_ERR_ERR_STAT1_CLR_ECC_OTHER        0x1000U       // Clear ECC_OTHER
#define MCAN_ERR_ERR_STAT1_CLR_CTRL_REG_ERROR   0x8000U       // Clear Control Register Error
#define MCAN_ERR_ERR_STAT1_ECC_BIT1_S           16U
#define MCAN_ERR_ERR_STAT1_ECC_BIT1_M           0xFFFF0000U   // ECC Error Bit Position

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_ERR_STAT3 register
//
//*************************************************************************************************
#define MCAN_ERR_ERR_STAT3_WB_PEND             0x1U     // Delayed Write Back Pending Status
#define MCAN_ERR_ERR_STAT3_SVBUS_TIMEOUT       0x2U     // Serial VBUS Timeout Flag
#define MCAN_ERR_ERR_STAT3_CLR_SVBUS_TIMEOUT   0x200U   // Clear Serial VBUS Timeout

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_SEC_EOI register
//
//*************************************************************************************************
#define MCAN_ERR_SEC_EOI_EOI_WR   0x1U   // End of Interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_SEC_STATUS register
//
//*************************************************************************************************
#define MCAN_ERR_SEC_STATUS_MSGMEM_PEND   0x1U   // Message RAM SEC Interrupt Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_SEC_ENABLE_SET register
//
//*************************************************************************************************
#define MCAN_ERR_SEC_ENABLE_SET_MSGMEM_ENABLE_SET   0x1U   // Message RAM SEC Interrupt Pending
                                                           // Enable Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_SEC_ENABLE_CLR register
//
//*************************************************************************************************
#define MCAN_ERR_SEC_ENABLE_CLR_MSGMEM_ENABLE_CLR   0x1U   // Message RAM SEC Interrupt Pending
                                                           // Enable Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_DED_EOI register
//
//*************************************************************************************************
#define MCAN_ERR_DED_EOI_EOI_WR   0x1U   // End of Interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_DED_STATUS register
//
//*************************************************************************************************
#define MCAN_ERR_DED_STATUS_MSGMEM_PEND   0x1U   // Message RAM DED Interrupt Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_DED_ENABLE_SET register
//
//*************************************************************************************************
#define MCAN_ERR_DED_ENABLE_SET_MSGMEM_ENABLE_SET   0x1U   // Message RAM DED Interrupt Pending
                                                           // Enable Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_DED_ENABLE_CLR register
//
//*************************************************************************************************
#define MCAN_ERR_DED_ENABLE_CLR_MSGMEM_ENABLE_CLR   0x1U   // Message RAM DED Interrupt Pending
                                                           // Enable Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_AGGR_ENABLE_SET register
//
//*************************************************************************************************
#define MCAN_ERR_AGGR_ENABLE_SET_ENABLE_PARITY_SET    0x1U   // Enable Parity Errors Set
#define MCAN_ERR_AGGR_ENABLE_SET_ENABLE_TIMEOUT_SET   0x2U   // Enable Timeout Errors Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_AGGR_ENABLE_CLR register
//
//*************************************************************************************************
#define MCAN_ERR_AGGR_ENABLE_CLR_ENABLE_PARITY_CLR    0x1U   // Enable Parity Errors Clear
#define MCAN_ERR_AGGR_ENABLE_CLR_ENABLE_TIMEOUT_CLR   0x2U   // Enable Timeout Errors Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_AGGR_STATUS_SET register
//
//*************************************************************************************************
#define MCAN_ERR_AGGR_STATUS_SET_AGGR_PARITY_ERR_S   0U
#define MCAN_ERR_AGGR_STATUS_SET_AGGR_PARITY_ERR_M   0x3U   // Aggregator Parity Error Status
#define MCAN_ERR_AGGR_STATUS_SET_SVBUS_TIMEOUT_S     2U
#define MCAN_ERR_AGGR_STATUS_SET_SVBUS_TIMEOUT_M     0xCU   // Aggregator Serial VBUS Timeout Error
                                                            // Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANERR_AGGR_STATUS_CLR register
//
//*************************************************************************************************
#define MCAN_ERR_AGGR_STATUS_CLR_AGGR_PARITY_ERR_S   0U
#define MCAN_ERR_AGGR_STATUS_CLR_AGGR_PARITY_ERR_M   0x3U   // Aggregator Parity Error Status
#define MCAN_ERR_AGGR_STATUS_CLR_SVBUS_TIMEOUT_S     2U
#define MCAN_ERR_AGGR_STATUS_CLR_SVBUS_TIMEOUT_M     0xCU   // Aggregator Serial VBUS Timeout Error
                                                            // Status



#endif
