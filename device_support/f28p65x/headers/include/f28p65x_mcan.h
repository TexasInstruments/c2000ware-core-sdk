//###########################################################################
//
// FILE:    f28p65x_mcan.h
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

#ifndef F28P65X_MCAN_H
#define F28P65X_MCAN_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MCAN Individual Register Bit Definitions:

struct MCANSS_PID_BITS {                // bits description
    bp_16 MINOR:6;                      // 5:0 Minor Revision
    bp_16 rsvd1:2;                      // 7:6 Reserved
    bp_16 MAJOR:3;                      // 10:8 Major Revision
    bp_16 rsvd2:5;                      // 15:11 Reserved
    bp_32 MODULE_ID:12;                 // 27:16 Module Identification Number
    bp_32 rsvd3:2;                      // 29:28 Reserved
    bp_32 SCHEME:2;                     // 31:30 PID Register Scheme
};

union MCANSS_PID_REG {
    bp_32  all;
    struct  MCANSS_PID_BITS  bit;
};

struct MCANSS_CTRL_BITS {               // bits description
    bp_16 rsvd1:3;                      // 2:0 Reserved
    bp_16 DBGSUSP_FREE:1;               // 3 Debug Suspend Free
    bp_16 WAKEUPREQEN:1;                // 4 Wakeup Request Enable
    bp_16 AUTOWAKEUP:1;                 // 5 Automatic Wakeup Enable
    bp_16 EXT_TS_CNTR_EN:1;             // 6 External Timestamp Counter Enable
    bp_16 rsvd2:9;                      // 15:7 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANSS_CTRL_REG {
    bp_32  all;
    struct  MCANSS_CTRL_BITS  bit;
};

struct MCANSS_STAT_BITS {               // bits description
    bp_16 RESET:1;                      // 0 Soft Reset Status
    bp_16 MEM_INIT_DONE:1;              // 1 Memory Initialization Done
    bp_16 ENABLE_FDOE:1;                // 2 Flexible Datarate Operation Enable
    bp_16 rsvd1:13;                     // 15:3 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_STAT_REG {
    bp_32  all;
    struct  MCANSS_STAT_BITS  bit;
};

struct MCANSS_ICS_BITS {                // bits description
    bp_16 EXT_TS_CNTR_OVFL:1;           // 0 External Timestamp Counter Overflow Interrupt Status Clear
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_ICS_REG {
    bp_32  all;
    struct  MCANSS_ICS_BITS  bit;
};

struct MCANSS_IRS_BITS {                // bits description
    bp_16 EXT_TS_CNTR_OVFL:1;           // 0 External Timestamp Counter Overflow Interrupt Status
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_IRS_REG {
    bp_32  all;
    struct  MCANSS_IRS_BITS  bit;
};

struct MCANSS_IECS_BITS {               // bits description
    bp_16 EXT_TS_CNTR_OVFL:1;           // 0 External Timestamp Counter Overflow Interrupt Enable Clear
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_IECS_REG {
    bp_32  all;
    struct  MCANSS_IECS_BITS  bit;
};

struct MCANSS_IE_BITS {                 // bits description
    bp_16 EXT_TS_CNTR_OVFL:1;           // 0 External Timestamp Counter Overflow Interrupt Enable
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_IE_REG {
    bp_32  all;
    struct  MCANSS_IE_BITS  bit;
};

struct MCANSS_IES_BITS {                // bits description
    bp_16 EXT_TS_CNTR_OVFL:1;           // 0 External Timestamp Counter Overflow Interrupt Enable Status
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_IES_REG {
    bp_32  all;
    struct  MCANSS_IES_BITS  bit;
};

struct MCANSS_EOI_BITS {                // bits description
    bp_16 EOI:8;                        // 7:0 External Timestamp Counter Overflow End of Interrupt
    bp_16 rsvd1:8;                      // 15:8 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_EOI_REG {
    bp_32  all;
    struct  MCANSS_EOI_BITS  bit;
};

struct MCANSS_EXT_TS_PRESCALER_BITS {   // bits description
    bp_32 PRESCALER:24;                 // 23:0 External Timestamp Prescaler
    bp_32 rsvd1:8;                      // 31:24 Reserved
};

union MCANSS_EXT_TS_PRESCALER_REG {
    bp_32  all;
    struct  MCANSS_EXT_TS_PRESCALER_BITS  bit;
};

struct MCANSS_EXT_TS_UNSERVICED_INTR_CNTR_BITS {// bits description
    bp_16 EXT_TS_INTR_CNTR:5;           // 4:0 External Timestamp Counter Unserviced Rollover Interrupts
    bp_16 rsvd1:11;                     // 15:5 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANSS_EXT_TS_UNSERVICED_INTR_CNTR_REG {
    bp_32  all;
    struct  MCANSS_EXT_TS_UNSERVICED_INTR_CNTR_BITS  bit;
};

struct MCANSS_REGS {
    union   MCANSS_PID_REG                   MCANSS_PID;                   // MCAN Subsystem Revision Register
    union   MCANSS_CTRL_REG                  MCANSS_CTRL;                  // MCAN Subsystem Control Register
    union   MCANSS_STAT_REG                  MCANSS_STAT;                  // MCAN Subsystem Status Register
    union   MCANSS_ICS_REG                   MCANSS_ICS;                   // MCAN Subsystem Interrupt Clear Shadow Register
    union   MCANSS_IRS_REG                   MCANSS_IRS;                   // MCAN Subsystem Interrupt Raw Satus Register
    union   MCANSS_IECS_REG                  MCANSS_IECS;                  // MCAN Subsystem Interrupt Enable Clear Shadow Register
    union   MCANSS_IE_REG                    MCANSS_IE;                    // MCAN Subsystem Interrupt Enable Register
    union   MCANSS_IES_REG                   MCANSS_IES;                   // MCAN Subsystem Interrupt Enable Status
    union   MCANSS_EOI_REG                   MCANSS_EOI;                   // MCAN Subsystem End of Interrupt
    union   MCANSS_EXT_TS_PRESCALER_REG      MCANSS_EXT_TS_PRESCALER;      // MCAN Subsystem External Timestamp Prescaler 0
    union   MCANSS_EXT_TS_UNSERVICED_INTR_CNTR_REG MCANSS_EXT_TS_UNSERVICED_INTR_CNTR; // MCAN Subsystem External Timestamp Unserviced Interrupts Counter
};

struct MCAN_CREL_BITS {                 // bits description
    bp_16 DAY:8;                        // 7:0 Time Stamp Day
    bp_16 MON:8;                        // 15:8 Time Stamp Month
    bp_32 YEAR:4;                       // 19:16 Time Stamp Year
    bp_32 SUBSTEP:4;                    // 23:20 Sub-Step of Core Release
    bp_32 STEP:4;                       // 27:24 Step of Core Release
    bp_32 REL:4;                        // 31:28 Core Release
};

union MCAN_CREL_REG {
    bp_32  all;
    struct  MCAN_CREL_BITS  bit;
};

struct MCAN_DBTP_BITS {                 // bits description
    bp_16 DSJW:4;                       // 3:0 Data Resynchronization Jump Width
    bp_16 DTSEG2:4;                     // 7:4 Data Time Segment After Sample Point
    bp_16 DTSEG1:5;                     // 12:8 Data Time Segment Before Sample Point
    bp_16 rsvd1:3;                      // 15:13 Reserved
    bp_32 DBRP:5;                       // 20:16 Data Bit Rate Prescaler
    bp_32 rsvd2:2;                      // 22:21 Reserved
    bp_32 TDC:1;                        // 23 Transmitter Delay Compensation
    bp_32 rsvd3:8;                      // 31:24 Reserved
};

union MCAN_DBTP_REG {
    bp_32  all;
    struct  MCAN_DBTP_BITS  bit;
};

struct MCAN_TEST_BITS {                 // bits description
    bp_16 rsvd1:4;                      // 3:0 Reserved
    bp_16 LBCK:1;                       // 4 Loop Back Mode
    bp_16 TX:2;                         // 6:5 Control of Transmit Pin
    bp_16 RX:1;                         // 7 Receive Pin
    bp_16 rsvd2:8;                      // 15:8 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCAN_TEST_REG {
    bp_32  all;
    struct  MCAN_TEST_BITS  bit;
};

struct MCAN_RWD_BITS {                  // bits description
    bp_16 WDC:8;                        // 7:0 Watchdog Configuration
    bp_16 WDV:8;                        // 15:8 Watchdog Value
    bp_32 rsvd1:16;                     // 31:16 Reserved
};

union MCAN_RWD_REG {
    bp_32  all;
    struct  MCAN_RWD_BITS  bit;
};

struct MCAN_CCCR_BITS {                 // bits description
    bp_16 INIT:1;                       // 0 Initialization
    bp_16 CCE:1;                        // 1 Configuration Change Enable
    bp_16 ASM:1;                        // 2 Restricted Operation Mode
    bp_16 CSA:1;                        // 3 Clock Stop Acknowledge
    bp_16 CSR:1;                        // 4 Clock Stop Request
    bp_16 MON:1;                        // 5 Bus Monitoring Mode
    bp_16 DAR:1;                        // 6 Disable Automatic Retransmission
    bp_16 TEST:1;                       // 7 Test Mode Enable
    bp_16 FDOE:1;                       // 8 Flexible Datarate Operation Enable
    bp_16 BRSE:1;                       // 9 Bit Rate Switch Enable
    bp_16 rsvd1:2;                      // 11:10 Reserved
    bp_16 PXHD:1;                       // 12 Protocol Exception Handling Disable
    bp_16 EFBI:1;                       // 13 Edge Filtering During Bus Integration
    bp_16 TXP:1;                        // 14 Transmit Pause
    bp_16 NISO:1;                       // 15 Non-ISO Operation
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_CCCR_REG {
    bp_32  all;
    struct  MCAN_CCCR_BITS  bit;
};

struct MCAN_NBTP_BITS {                 // bits description
    bp_16 NTSEG2:7;                     // 6:0 Nominal Time Segment After Sample Point
    bp_16 rsvd1:1;                      // 7 Reserved
    bp_16 NTSEG1:8;                     // 15:8 Nominal Time Segment Before Sample Point
    bp_32 NBRP:9;                       // 24:16 Nominal Bit Rate Prescaler
    bp_32 NSJW:7;                       // 31:25 Nominal (Re)Synchronization Jump Width
};

union MCAN_NBTP_REG {
    bp_32  all;
    struct  MCAN_NBTP_BITS  bit;
};

struct MCAN_TSCC_BITS {                 // bits description
    bp_16 TSS:2;                        // 1:0 Timestamp Select
    bp_16 rsvd1:14;                     // 15:2 Reserved
    bp_32 TCP:4;                        // 19:16 Timestamp Counter Prescaler
    bp_32 rsvd2:12;                     // 31:20 Reserved
};

union MCAN_TSCC_REG {
    bp_32  all;
    struct  MCAN_TSCC_BITS  bit;
};

struct MCAN_TSCV_BITS {                 // bits description
    bp_16 TSC:16;                       // 15:0 Timestamp Counter
    bp_32 rsvd1:16;                     // 31:16 Reserved
};

union MCAN_TSCV_REG {
    bp_32  all;
    struct  MCAN_TSCV_BITS  bit;
};

struct MCAN_TOCC_BITS {                 // bits description
    bp_16 ETOC:1;                       // 0 Enable Timeout Counter
    bp_16 TOS:2;                        // 2:1 Timeout Select
    bp_16 rsvd1:13;                     // 15:3 Reserved
    bp_32 TOP:16;                       // 31:16 Timeout Period
};

union MCAN_TOCC_REG {
    bp_32  all;
    struct  MCAN_TOCC_BITS  bit;
};

struct MCAN_TOCV_BITS {                 // bits description
    bp_16 TOC:16;                       // 15:0 Timeout Counter
    bp_32 rsvd1:16;                     // 31:16 Reserved
};

union MCAN_TOCV_REG {
    bp_32  all;
    struct  MCAN_TOCV_BITS  bit;
};

struct MCAN_ECR_BITS {                  // bits description
    bp_16 TEC:8;                        // 7:0 Transmit Error Counter
    bp_16 REC:7;                        // 14:8 Receive Error Counter
    bp_16 RP:1;                         // 15 Receive Error Passive
    bp_32 CEL:8;                        // 23:16 CAN Error Logging
    bp_32 rsvd1:8;                      // 31:24 Reserved
};

union MCAN_ECR_REG {
    bp_32  all;
    struct  MCAN_ECR_BITS  bit;
};

struct MCAN_PSR_BITS {                  // bits description
    bp_16 LEC:3;                        // 2:0 Last Error Code
    bp_16 ACT:2;                        // 4:3 Node Activity
    bp_16 EP:1;                         // 5 Error Passive
    bp_16 EW:1;                         // 6 Warning Status
    bp_16 BO:1;                         // 7 Bus_Off Status
    bp_16 DLEC:3;                       // 10:8 Data Phase Last Error Code
    bp_16 RESI:1;                       // 11 ESI Flag of Last Received CAN FD Message
    bp_16 RBRS:1;                       // 12 BRS Flag of Last Received CAN FD Message
    bp_16 RFDF:1;                       // 13 Received a CAN FD Message
    bp_16 PXE:1;                        // 14 Protocol Exception Event
    bp_16 rsvd1:1;                      // 15 Reserved
    bp_32 TDCV:7;                       // 22:16 Transmitter Delay Compensation Value
    bp_32 rsvd2:9;                      // 31:23 Reserved
};

union MCAN_PSR_REG {
    bp_32  all;
    struct  MCAN_PSR_BITS  bit;
};

struct MCAN_TDCR_BITS {                 // bits description
    bp_16 TDCF:7;                       // 6:0 Transmitter Delay Compensation Filter Window Length
    bp_16 rsvd1:1;                      // 7 Reserved
    bp_16 TDCO:7;                       // 14:8 Transmitter Delay Compensation Offset
    bp_16 rsvd2:1;                      // 15 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCAN_TDCR_REG {
    bp_32  all;
    struct  MCAN_TDCR_BITS  bit;
};

struct MCAN_IR_BITS {                   // bits description
    bp_16 RF0N:1;                       // 0 Rx FIFO 0 New Message
    bp_16 RF0W:1;                       // 1 Rx FIFO 0 Watermark Reached
    bp_16 RF0F:1;                       // 2 Rx FIFO 0 Full
    bp_16 RF0L:1;                       // 3 Rx FIFO 0 Message Lost
    bp_16 RF1N:1;                       // 4 Rx FIFO 1 New Message
    bp_16 RF1W:1;                       // 5 Rx FIFO 1 Watermark Reached
    bp_16 RF1F:1;                       // 6 Rx FIFO 1 Full
    bp_16 RF1L:1;                       // 7 Rx FIFO 1 Message Lost
    bp_16 HPM:1;                        // 8 High Priority Message
    bp_16 TC:1;                         // 9 Transmission Completed
    bp_16 TCF:1;                        // 10 Transmission Cancellation Finished
    bp_16 TFE:1;                        // 11 Tx FIFO Empty
    bp_16 TEFN:1;                       // 12 Tx Event FIFO New Entry
    bp_16 TEFW:1;                       // 13 Tx Event FIFO Watermark Reached
    bp_16 TEFF:1;                       // 14 Tx Event FIFO Full
    bp_16 TEFL:1;                       // 15 Tx Event FIFO Element Lost
    bp_32 TSW:1;                        // 16 Timestamp Wraparound
    bp_32 MRAF:1;                       // 17 Message RAM Access Failure
    bp_32 TOO:1;                        // 18 Timeout Occurred
    bp_32 DRX:1;                        // 19 Message Stored to Dedicated Rx Buffer
    bp_32 rsvd1:1;                      // 20 Reserved
    bp_32 BEU:1;                        // 21 Bit Error Uncorrected
    bp_32 ELO:1;                        // 22 Error Logging Overflow
    bp_32 EP:1;                         // 23 Error Passive
    bp_32 EW:1;                         // 24 Warning Status
    bp_32 BO:1;                         // 25 Bus_Off Status
    bp_32 WDI:1;                        // 26 Watchdog Interrupt
    bp_32 PEA:1;                        // 27 Protocol Error in Arbitration Phase
    bp_32 PED:1;                        // 28 Protocol Error in Data Phase
    bp_32 ARA:1;                        // 29 Access to Reserved Address
    bp_32 rsvd2:1;                      // 30 Reserved
    bp_32 rsvd3:1;                      // 31 Reserved
};

union MCAN_IR_REG {
    bp_32  all;
    struct  MCAN_IR_BITS  bit;
};

struct MCAN_IE_BITS {                   // bits description
    bp_16 RF0NE:1;                      // 0 Rx FIFO 0 New Message Enable
    bp_16 RF0WE:1;                      // 1 Rx FIFO 0 Watermark Reached Enable
    bp_16 RF0FE:1;                      // 2 Rx FIFO 0 Full Enable
    bp_16 RF0LE:1;                      // 3 Rx FIFO 0 Message Lost Enable
    bp_16 RF1NE:1;                      // 4 Rx FIFO 1 New Message Enable
    bp_16 RF1WE:1;                      // 5 Rx FIFO 1 Watermark Reached Enable
    bp_16 RF1FE:1;                      // 6 Rx FIFO 1 Full Enable
    bp_16 RF1LE:1;                      // 7 Rx FIFO 1 Message Lost Enable
    bp_16 HPME:1;                       // 8 High Priority Message Enable
    bp_16 TCE:1;                        // 9 Transmission Completed Enable
    bp_16 TCFE:1;                       // 10 Transmission Cancellation Finished Enable
    bp_16 TFEE:1;                       // 11 Tx FIFO Empty Enable
    bp_16 TEFNE:1;                      // 12 Tx Event FIFO New Entry Enable
    bp_16 TEFWE:1;                      // 13 Tx Event FIFO Watermark Reached Enable
    bp_16 TEFFE:1;                      // 14 Tx Event FIFO Full Enable
    bp_16 TEFLE:1;                      // 15 Tx Event FIFO Element Lost Enable
    bp_32 TSWE:1;                       // 16 Timestamp Wraparound Enable
    bp_32 MRAFE:1;                      // 17 Message RAM Access Failure Enable
    bp_32 TOOE:1;                       // 18 Timeout Occurred Enable
    bp_32 DRXE:1;                       // 19 Message Stored to Dedicated Rx Buffer Enable
    bp_32 BECE:1;                       // 20 Bit Error Corrected Enable
    bp_32 BEUE:1;                       // 21 Bit Error Uncorrected Enable
    bp_32 ELOE:1;                       // 22 Error Logging Overflow Enable
    bp_32 EPE:1;                        // 23 Error Passive Enable
    bp_32 EWE:1;                        // 24 Warning Status Enable
    bp_32 BOE:1;                        // 25 Bus_Off Status Enable
    bp_32 WDIE:1;                       // 26 Watchdog Interrupt Enable
    bp_32 PEAE:1;                       // 27 Protocol Error in Arbitration Phase Enable
    bp_32 PEDE:1;                       // 28 Protocol Error in Data Phase Enable
    bp_32 ARAE:1;                       // 29 Access to Reserved Address Enable
    bp_32 rsvd1:2;                      // 31:30 Reserved
};

union MCAN_IE_REG {
    bp_32  all;
    struct  MCAN_IE_BITS  bit;
};

struct MCAN_ILS_BITS {                  // bits description
    bp_16 RF0NL:1;                      // 0 Rx FIFO 0 New Message Line
    bp_16 RF0WL:1;                      // 1 Rx FIFO 0 Watermark Reached Line
    bp_16 RF0FL:1;                      // 2 Rx FIFO 0 Full Line
    bp_16 RF0LL:1;                      // 3 Rx FIFO 0 Message Lost Line
    bp_16 RF1NL:1;                      // 4 Rx FIFO 1 New Message Line
    bp_16 RF1WL:1;                      // 5 Rx FIFO 1 Watermark Reached Line
    bp_16 RF1FL:1;                      // 6 Rx FIFO 1 Full Line
    bp_16 RF1LL:1;                      // 7 Rx FIFO 1 Message Lost Line
    bp_16 HPML:1;                       // 8 High Priority Message Line
    bp_16 TCL:1;                        // 9 Transmission Completed Line
    bp_16 TCFL:1;                       // 10 Transmission Cancellation Finished Line
    bp_16 TFEL:1;                       // 11 Tx FIFO Empty Line
    bp_16 TEFNL:1;                      // 12 Tx Event FIFO New Entry Line
    bp_16 TEFWL:1;                      // 13 Tx Event FIFO Watermark Reached Line
    bp_16 TEFFL:1;                      // 14 Tx Event FIFO Full Line
    bp_16 TEFLL:1;                      // 15 Tx Event FIFO Element Lost Line
    bp_32 TSWL:1;                       // 16 Timestamp Wraparound Line
    bp_32 MRAFL:1;                      // 17 Message RAM Access Failure Line
    bp_32 TOOL:1;                       // 18 Timeout Occurred Line
    bp_32 DRXL:1;                       // 19 Message Stored to Dedicated Rx Buffer Line
    bp_32 BECL:1;                       // 20 Bit Error Corrected Line
    bp_32 BEUL:1;                       // 21 Bit Error Uncorrected Line
    bp_32 ELOL:1;                       // 22 Error Logging Overflow Line
    bp_32 EPL:1;                        // 23 Error Passive Line
    bp_32 EWL:1;                        // 24 Warning Status Line
    bp_32 BOL:1;                        // 25 Bus_Off Status Line
    bp_32 WDIL:1;                       // 26 Watchdog Interrupt Line
    bp_32 PEAL:1;                       // 27 Protocol Error in Arbitration Phase Line
    bp_32 PEDL:1;                       // 28 Protocol Error in Data Phase Line
    bp_32 ARAL:1;                       // 29 Access to Reserved Address Line
    bp_32 rsvd1:2;                      // 31:30 Reserved
};

union MCAN_ILS_REG {
    bp_32  all;
    struct  MCAN_ILS_BITS  bit;
};

struct MCAN_ILE_BITS {                  // bits description
    bp_16 EINT0:1;                      // 0 Enable Interrupt Line 0
    bp_16 EINT1:1;                      // 1 Enable Interrupt Line 1
    bp_16 rsvd1:14;                     // 15:2 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_ILE_REG {
    bp_32  all;
    struct  MCAN_ILE_BITS  bit;
};

struct MCAN_GFC_BITS {                  // bits description
    bp_16 RRFE:1;                       // 0 Reject Remote Frames Extended
    bp_16 RRFS:1;                       // 1 Reject Remote Frames Standard
    bp_16 ANFE:2;                       // 3:2 Accept Non-matching Frames Extended
    bp_16 ANFS:2;                       // 5:4 Accept Non-matching Frames Standard
    bp_16 rsvd1:10;                     // 15:6 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_GFC_REG {
    bp_32  all;
    struct  MCAN_GFC_BITS  bit;
};

struct MCAN_SIDFC_BITS {                // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 FLSSA:14;                     // 15:2 Filter List Standard Start Address
    bp_32 LSS:8;                        // 23:16 List Size Standard
    bp_32 rsvd2:8;                      // 31:24 Reserved
};

union MCAN_SIDFC_REG {
    bp_32  all;
    struct  MCAN_SIDFC_BITS  bit;
};

struct MCAN_XIDFC_BITS {                // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 FLESA:14;                     // 15:2 Filter List Extended Start Address
    bp_32 LSE:7;                        // 22:16 List Size Extended
    bp_32 rsvd2:9;                      // 31:23 Reserved
};

union MCAN_XIDFC_REG {
    bp_32  all;
    struct  MCAN_XIDFC_BITS  bit;
};

struct MCAN_XIDAM_BITS {                // bits description
    bp_32 EIDM:29;                      // 28:0 Extended ID Mask
    bp_32 rsvd1:3;                      // 31:29 Reserved
};

union MCAN_XIDAM_REG {
    bp_32  all;
    struct  MCAN_XIDAM_BITS  bit;
};

struct MCAN_HPMS_BITS {                 // bits description
    bp_16 BIDX:6;                       // 5:0 Buffer Index
    bp_16 MSI:2;                        // 7:6 Message Storage Indicator
    bp_16 FIDX:7;                       // 14:8 Filter Index
    bp_16 FLST:1;                       // 15 Filter List
    bp_32 rsvd1:16;                     // 31:16 Reserved
};

union MCAN_HPMS_REG {
    bp_32  all;
    struct  MCAN_HPMS_BITS  bit;
};

struct MCAN_NDAT1_BITS {                // bits description
    bp_16 ND0:1;                        // 0 New Data RX Buffer 0
    bp_16 ND1:1;                        // 1 New Data RX Buffer 1
    bp_16 ND2:1;                        // 2 New Data RX Buffer 2
    bp_16 ND3:1;                        // 3 New Data RX Buffer 3
    bp_16 ND4:1;                        // 4 New Data RX Buffer 4
    bp_16 ND5:1;                        // 5 New Data RX Buffer 5
    bp_16 ND6:1;                        // 6 New Data RX Buffer 6
    bp_16 ND7:1;                        // 7 New Data RX Buffer 7
    bp_16 ND8:1;                        // 8 New Data RX Buffer 8
    bp_16 ND9:1;                        // 9 New Data RX Buffer 9
    bp_16 ND10:1;                       // 10 New Data RX Buffer 10
    bp_16 ND11:1;                       // 11 New Data RX Buffer 11
    bp_16 ND12:1;                       // 12 New Data RX Buffer 12
    bp_16 ND13:1;                       // 13 New Data RX Buffer 13
    bp_16 ND14:1;                       // 14 New Data RX Buffer 14
    bp_16 ND15:1;                       // 15 New Data RX Buffer 15
    bp_32 ND16:1;                       // 16 New Data RX Buffer 16
    bp_32 ND17:1;                       // 17 New Data RX Buffer 17
    bp_32 ND18:1;                       // 18 New Data RX Buffer 18
    bp_32 ND19:1;                       // 19 New Data RX Buffer 19
    bp_32 ND20:1;                       // 20 New Data RX Buffer 20
    bp_32 ND21:1;                       // 21 New Data RX Buffer 21
    bp_32 ND22:1;                       // 22 New Data RX Buffer 22
    bp_32 ND23:1;                       // 23 New Data RX Buffer 23
    bp_32 ND24:1;                       // 24 New Data RX Buffer 24
    bp_32 ND25:1;                       // 25 New Data RX Buffer 25
    bp_32 ND26:1;                       // 26 New Data RX Buffer 26
    bp_32 ND27:1;                       // 27 New Data RX Buffer 27
    bp_32 ND28:1;                       // 28 New Data RX Buffer 28
    bp_32 ND29:1;                       // 29 New Data RX Buffer 29
    bp_32 ND30:1;                       // 30 New Data RX Buffer 30
    bp_32 ND31:1;                       // 31 New Data RX Buffer 31
};

union MCAN_NDAT1_REG {
    bp_32  all;
    struct  MCAN_NDAT1_BITS  bit;
};

struct MCAN_NDAT2_BITS {                // bits description
    bp_16 ND32:1;                       // 0 New Data RX Buffer 32
    bp_16 ND33:1;                       // 1 New Data RX Buffer 33
    bp_16 ND34:1;                       // 2 New Data RX Buffer 34
    bp_16 ND35:1;                       // 3 New Data RX Buffer 35
    bp_16 ND36:1;                       // 4 New Data RX Buffer 36
    bp_16 ND37:1;                       // 5 New Data RX Buffer 37
    bp_16 ND38:1;                       // 6 New Data RX Buffer 38
    bp_16 ND39:1;                       // 7 New Data RX Buffer 39
    bp_16 ND40:1;                       // 8 New Data RX Buffer 40
    bp_16 ND41:1;                       // 9 New Data RX Buffer 41
    bp_16 ND42:1;                       // 10 New Data RX Buffer 42
    bp_16 ND43:1;                       // 11 New Data RX Buffer 43
    bp_16 ND44:1;                       // 12 New Data RX Buffer 44
    bp_16 ND45:1;                       // 13 New Data RX Buffer 45
    bp_16 ND46:1;                       // 14 New Data RX Buffer 46
    bp_16 ND47:1;                       // 15 New Data RX Buffer 47
    bp_32 ND48:1;                       // 16 New Data RX Buffer 48
    bp_32 ND49:1;                       // 17 New Data RX Buffer 49
    bp_32 ND50:1;                       // 18 New Data RX Buffer 50
    bp_32 ND51:1;                       // 19 New Data RX Buffer 51
    bp_32 ND52:1;                       // 20 New Data RX Buffer 52
    bp_32 ND53:1;                       // 21 New Data RX Buffer 53
    bp_32 ND54:1;                       // 22 New Data RX Buffer 54
    bp_32 ND55:1;                       // 23 New Data RX Buffer 55
    bp_32 ND56:1;                       // 24 New Data RX Buffer 56
    bp_32 ND57:1;                       // 25 New Data RX Buffer 57
    bp_32 ND58:1;                       // 26 New Data RX Buffer 58
    bp_32 ND59:1;                       // 27 New Data RX Buffer 59
    bp_32 ND60:1;                       // 28 New Data RX Buffer 60
    bp_32 ND61:1;                       // 29 New Data RX Buffer 61
    bp_32 ND62:1;                       // 30 New Data RX Buffer 62
    bp_32 ND63:1;                       // 31 New Data RX Buffer 63
};

union MCAN_NDAT2_REG {
    bp_32  all;
    struct  MCAN_NDAT2_BITS  bit;
};

struct MCAN_RXF0C_BITS {                // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 F0SA:14;                      // 15:2 Rx FIFO 0 Start Address
    bp_32 F0S:7;                        // 22:16 Rx FIFO 0 Size
    bp_32 rsvd2:1;                      // 23 Reserved
    bp_32 F0WM:7;                       // 30:24 Rx FIFO 0 Watermark
    bp_32 F0OM:1;                       // 31 FIFO 0 Operation Mode
};

union MCAN_RXF0C_REG {
    bp_32  all;
    struct  MCAN_RXF0C_BITS  bit;
};

struct MCAN_RXF0S_BITS {                // bits description
    bp_16 F0FL:7;                       // 6:0 Rx FIFO 0 Fill Level
    bp_16 rsvd1:1;                      // 7 Reserved
    bp_16 F0GI:6;                       // 13:8 Rx FIFO 0 Get Index
    bp_16 rsvd2:2;                      // 15:14 Reserved
    bp_32 F0PI:6;                       // 21:16 Rx FIFO 0 Put Index
    bp_32 rsvd3:2;                      // 23:22 Reserved
    bp_32 F0F:1;                        // 24 Rx FIFO 0 Full
    bp_32 RF0L:1;                       // 25 Rx FIFO 0 Message Lost
    bp_32 rsvd4:6;                      // 31:26 Reserved
};

union MCAN_RXF0S_REG {
    bp_32  all;
    struct  MCAN_RXF0S_BITS  bit;
};

struct MCAN_RXF0A_BITS {                // bits description
    bp_16 F0AI:6;                       // 5:0 Rx FIFO 0 Acknowledge Index
    bp_16 rsvd1:10;                     // 15:6 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_RXF0A_REG {
    bp_32  all;
    struct  MCAN_RXF0A_BITS  bit;
};

struct MCAN_RXBC_BITS {                 // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 RBSA:14;                      // 15:2 Rx Buffer Start Address
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_RXBC_REG {
    bp_32  all;
    struct  MCAN_RXBC_BITS  bit;
};

struct MCAN_RXF1C_BITS {                // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 F1SA:14;                      // 15:2 Rx FIFO 1 Start Address
    bp_32 F1S:7;                        // 22:16 Rx FIFO 1 Size
    bp_32 rsvd2:1;                      // 23 Reserved
    bp_32 F1WM:7;                       // 30:24 Rx FIFO 1 Watermark
    bp_32 F1OM:1;                       // 31 FIFO 1 Operation Mode
};

union MCAN_RXF1C_REG {
    bp_32  all;
    struct  MCAN_RXF1C_BITS  bit;
};

struct MCAN_RXF1S_BITS {                // bits description
    bp_16 F1FL:7;                       // 6:0 Rx FIFO 1 Fill Level
    bp_16 rsvd1:1;                      // 7 Reserved
    bp_16 F1GI:6;                       // 13:8 Rx FIFO 1 Get Index
    bp_16 rsvd2:2;                      // 15:14 Reserved
    bp_32 F1PI:6;                       // 21:16 Rx FIFO 1 Put Index
    bp_32 rsvd3:2;                      // 23:22 Reserved
    bp_32 F1F:1;                        // 24 Rx FIFO 1 Full
    bp_32 RF1L:1;                       // 25 Rx FIFO 1 Message Lost
    bp_32 rsvd4:4;                      // 29:26 Reserved
    bp_32 DMS:2;                        // 31:30 Debug Message Status
};

union MCAN_RXF1S_REG {
    bp_32  all;
    struct  MCAN_RXF1S_BITS  bit;
};

struct MCAN_RXF1A_BITS {                // bits description
    bp_16 F1AI:6;                       // 5:0 Rx FIFO 1 Acknowledge Index
    bp_16 rsvd1:10;                     // 15:6 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_RXF1A_REG {
    bp_32  all;
    struct  MCAN_RXF1A_BITS  bit;
};

struct MCAN_RXESC_BITS {                // bits description
    bp_16 F0DS:3;                       // 2:0 Rx FIFO 0 Data Field Size
    bp_16 rsvd1:1;                      // 3 Reserved
    bp_16 F1DS:3;                       // 6:4 Rx FIFO 1 Data Field Size
    bp_16 rsvd2:1;                      // 7 Reserved
    bp_16 RBDS:3;                       // 10:8 Rx Buffer Data Field Size
    bp_16 rsvd3:5;                      // 15:11 Reserved
    bp_32 rsvd4:16;                     // 31:16 Reserved
};

union MCAN_RXESC_REG {
    bp_32  all;
    struct  MCAN_RXESC_BITS  bit;
};

struct MCAN_TXBC_BITS {                 // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 TBSA:14;                      // 15:2 Tx Buffers Start Address
    bp_32 NDTB:6;                       // 21:16 Number of Dedicated Transmit Buffers
    bp_32 rsvd2:2;                      // 23:22 Reserved
    bp_32 TFQS:6;                       // 29:24 Transmit FIFO/Queue Size
    bp_32 TFQM:1;                       // 30 Tx FIFO/Queue Mode
    bp_32 rsvd3:1;                      // 31 Reserved
};

union MCAN_TXBC_REG {
    bp_32  all;
    struct  MCAN_TXBC_BITS  bit;
};

struct MCAN_TXFQS_BITS {                // bits description
    bp_16 TFFL:6;                       // 5:0 Tx FIFO Free Level
    bp_16 rsvd1:2;                      // 7:6 Reserved
    bp_16 TFGI:5;                       // 12:8 Tx FIFO Get Index
    bp_16 rsvd2:3;                      // 15:13 Reserved
    bp_32 TFQP:5;                       // 20:16 Tx FIFO/Queue Put Index
    bp_32 TFQF:1;                       // 21 Tx FIFO/Queue Full
    bp_32 rsvd3:10;                     // 31:22 Reserved
};

union MCAN_TXFQS_REG {
    bp_32  all;
    struct  MCAN_TXFQS_BITS  bit;
};

struct MCAN_TXESC_BITS {                // bits description
    bp_16 TBDS:3;                       // 2:0 Tx Buffer Data Field Size
    bp_16 rsvd1:13;                     // 15:3 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_TXESC_REG {
    bp_32  all;
    struct  MCAN_TXESC_BITS  bit;
};

struct MCAN_TXBRP_BITS {                // bits description
    bp_16 TRP0:1;                       // 0 Transmission Request Pending 0
    bp_16 TRP1:1;                       // 1 Transmission Request Pending 1
    bp_16 TRP2:1;                       // 2 Transmission Request Pending 2
    bp_16 TRP3:1;                       // 3 Transmission Request Pending 3
    bp_16 TRP4:1;                       // 4 Transmission Request Pending 4
    bp_16 TRP5:1;                       // 5 Transmission Request Pending 5
    bp_16 TRP6:1;                       // 6 Transmission Request Pending 6
    bp_16 TRP7:1;                       // 7 Transmission Request Pending 7
    bp_16 TRP8:1;                       // 8 Transmission Request Pending 8
    bp_16 TRP9:1;                       // 9 Transmission Request Pending 9
    bp_16 TRP10:1;                      // 10 Transmission Request Pending 10
    bp_16 TRP11:1;                      // 11 Transmission Request Pending 11
    bp_16 TRP12:1;                      // 12 Transmission Request Pending 12
    bp_16 TRP13:1;                      // 13 Transmission Request Pending 13
    bp_16 TRP14:1;                      // 14 Transmission Request Pending 14
    bp_16 TRP15:1;                      // 15 Transmission Request Pending 15
    bp_32 TRP16:1;                      // 16 Transmission Request Pending 16
    bp_32 TRP17:1;                      // 17 Transmission Request Pending 17
    bp_32 TRP18:1;                      // 18 Transmission Request Pending 18
    bp_32 TRP19:1;                      // 19 Transmission Request Pending 19
    bp_32 TRP20:1;                      // 20 Transmission Request Pending 20
    bp_32 TRP21:1;                      // 21 Transmission Request Pending 21
    bp_32 TRP22:1;                      // 22 Transmission Request Pending 22
    bp_32 TRP23:1;                      // 23 Transmission Request Pending 23
    bp_32 TRP24:1;                      // 24 Transmission Request Pending 24
    bp_32 TRP25:1;                      // 25 Transmission Request Pending 25
    bp_32 TRP26:1;                      // 26 Transmission Request Pending 26
    bp_32 TRP27:1;                      // 27 Transmission Request Pending 27
    bp_32 TRP28:1;                      // 28 Transmission Request Pending 28
    bp_32 TRP29:1;                      // 29 Transmission Request Pending 29
    bp_32 TRP30:1;                      // 30 Transmission Request Pending 30
    bp_32 TRP31:1;                      // 31 Transmission Request Pending 31
};

union MCAN_TXBRP_REG {
    bp_32  all;
    struct  MCAN_TXBRP_BITS  bit;
};

struct MCAN_TXBAR_BITS {                // bits description
    bp_16 AR0:1;                        // 0 Add Request 0
    bp_16 AR1:1;                        // 1 Add Request 1
    bp_16 AR2:1;                        // 2 Add Request 2
    bp_16 AR3:1;                        // 3 Add Request 3
    bp_16 AR4:1;                        // 4 Add Request 4
    bp_16 AR5:1;                        // 5 Add Request 5
    bp_16 AR6:1;                        // 6 Add Request 6
    bp_16 AR7:1;                        // 7 Add Request 7
    bp_16 AR8:1;                        // 8 Add Request 8
    bp_16 AR9:1;                        // 9 Add Request 9
    bp_16 AR10:1;                       // 10 Add Request 10
    bp_16 AR11:1;                       // 11 Add Request 11
    bp_16 AR12:1;                       // 12 Add Request 12
    bp_16 AR13:1;                       // 13 Add Request 13
    bp_16 AR14:1;                       // 14 Add Request 14
    bp_16 AR15:1;                       // 15 Add Request 15
    bp_32 AR16:1;                       // 16 Add Request 16
    bp_32 AR17:1;                       // 17 Add Request 17
    bp_32 AR18:1;                       // 18 Add Request 18
    bp_32 AR19:1;                       // 19 Add Request 19
    bp_32 AR20:1;                       // 20 Add Request 20
    bp_32 AR21:1;                       // 21 Add Request 21
    bp_32 AR22:1;                       // 22 Add Request 22
    bp_32 AR23:1;                       // 23 Add Request 23
    bp_32 AR24:1;                       // 24 Add Request 24
    bp_32 AR25:1;                       // 25 Add Request 25
    bp_32 AR26:1;                       // 26 Add Request 26
    bp_32 AR27:1;                       // 27 Add Request 27
    bp_32 AR28:1;                       // 28 Add Request 28
    bp_32 AR29:1;                       // 29 Add Request 29
    bp_32 AR30:1;                       // 30 Add Request 30
    bp_32 AR31:1;                       // 31 Add Request 31
};

union MCAN_TXBAR_REG {
    bp_32  all;
    struct  MCAN_TXBAR_BITS  bit;
};

struct MCAN_TXBCR_BITS {                // bits description
    bp_16 CR0:1;                        // 0 Cancellation Request 0
    bp_16 CR1:1;                        // 1 Cancellation Request 1
    bp_16 CR2:1;                        // 2 Cancellation Request 2
    bp_16 CR3:1;                        // 3 Cancellation Request 3
    bp_16 CR4:1;                        // 4 Cancellation Request 4
    bp_16 CR5:1;                        // 5 Cancellation Request 5
    bp_16 CR6:1;                        // 6 Cancellation Request 6
    bp_16 CR7:1;                        // 7 Cancellation Request 7
    bp_16 CR8:1;                        // 8 Cancellation Request 8
    bp_16 CR9:1;                        // 9 Cancellation Request 9
    bp_16 CR10:1;                       // 10 Cancellation Request 10
    bp_16 CR11:1;                       // 11 Cancellation Request 11
    bp_16 CR12:1;                       // 12 Cancellation Request 12
    bp_16 CR13:1;                       // 13 Cancellation Request 13
    bp_16 CR14:1;                       // 14 Cancellation Request 14
    bp_16 CR15:1;                       // 15 Cancellation Request 15
    bp_32 CR16:1;                       // 16 Cancellation Request 16
    bp_32 CR17:1;                       // 17 Cancellation Request 17
    bp_32 CR18:1;                       // 18 Cancellation Request 18
    bp_32 CR19:1;                       // 19 Cancellation Request 19
    bp_32 CR20:1;                       // 20 Cancellation Request 20
    bp_32 CR21:1;                       // 21 Cancellation Request 21
    bp_32 CR22:1;                       // 22 Cancellation Request 22
    bp_32 CR23:1;                       // 23 Cancellation Request 23
    bp_32 CR24:1;                       // 24 Cancellation Request 24
    bp_32 CR25:1;                       // 25 Cancellation Request 25
    bp_32 CR26:1;                       // 26 Cancellation Request 26
    bp_32 CR27:1;                       // 27 Cancellation Request 27
    bp_32 CR28:1;                       // 28 Cancellation Request 28
    bp_32 CR29:1;                       // 29 Cancellation Request 29
    bp_32 CR30:1;                       // 30 Cancellation Request 30
    bp_32 CR31:1;                       // 31 Cancellation Request 31
};

union MCAN_TXBCR_REG {
    bp_32  all;
    struct  MCAN_TXBCR_BITS  bit;
};

struct MCAN_TXBTO_BITS {                // bits description
    bp_16 TO0:1;                        // 0 Transmission Occurred 0
    bp_16 TO1:1;                        // 1 Transmission Occurred 1
    bp_16 TO2:1;                        // 2 Transmission Occurred 2
    bp_16 TO3:1;                        // 3 Transmission Occurred 3
    bp_16 TO4:1;                        // 4 Transmission Occurred 4
    bp_16 TO5:1;                        // 5 Transmission Occurred 5
    bp_16 TO6:1;                        // 6 Transmission Occurred 6
    bp_16 TO7:1;                        // 7 Transmission Occurred 7
    bp_16 TO8:1;                        // 8 Transmission Occurred 8
    bp_16 TO9:1;                        // 9 Transmission Occurred 9
    bp_16 TO10:1;                       // 10 Transmission Occurred 10
    bp_16 TO11:1;                       // 11 Transmission Occurred 11
    bp_16 TO12:1;                       // 12 Transmission Occurred 12
    bp_16 TO13:1;                       // 13 Transmission Occurred 13
    bp_16 TO14:1;                       // 14 Transmission Occurred 14
    bp_16 TO15:1;                       // 15 Transmission Occurred 15
    bp_32 TO16:1;                       // 16 Transmission Occurred 16
    bp_32 TO17:1;                       // 17 Transmission Occurred 17
    bp_32 TO18:1;                       // 18 Transmission Occurred 18
    bp_32 TO19:1;                       // 19 Transmission Occurred 19
    bp_32 TO20:1;                       // 20 Transmission Occurred 20
    bp_32 TO21:1;                       // 21 Transmission Occurred 21
    bp_32 TO22:1;                       // 22 Transmission Occurred 22
    bp_32 TO23:1;                       // 23 Transmission Occurred 23
    bp_32 TO24:1;                       // 24 Transmission Occurred 24
    bp_32 TO25:1;                       // 25 Transmission Occurred 25
    bp_32 TO26:1;                       // 26 Transmission Occurred 26
    bp_32 TO27:1;                       // 27 Transmission Occurred 27
    bp_32 TO28:1;                       // 28 Transmission Occurred 28
    bp_32 TO29:1;                       // 29 Transmission Occurred 29
    bp_32 TO30:1;                       // 30 Transmission Occurred 30
    bp_32 TO31:1;                       // 31 Transmission Occurred 31
};

union MCAN_TXBTO_REG {
    bp_32  all;
    struct  MCAN_TXBTO_BITS  bit;
};

struct MCAN_TXBCF_BITS {                // bits description
    bp_16 CF0:1;                        // 0 Cancellation Finished 0
    bp_16 CF1:1;                        // 1 Cancellation Finished 1
    bp_16 CF2:1;                        // 2 Cancellation Finished 2
    bp_16 CF3:1;                        // 3 Cancellation Finished 3
    bp_16 CF4:1;                        // 4 Cancellation Finished 4
    bp_16 CF5:1;                        // 5 Cancellation Finished 5
    bp_16 CF6:1;                        // 6 Cancellation Finished 6
    bp_16 CF7:1;                        // 7 Cancellation Finished 7
    bp_16 CF8:1;                        // 8 Cancellation Finished 8
    bp_16 CF9:1;                        // 9 Cancellation Finished 9
    bp_16 CF10:1;                       // 10 Cancellation Finished 10
    bp_16 CF11:1;                       // 11 Cancellation Finished 11
    bp_16 CF12:1;                       // 12 Cancellation Finished 12
    bp_16 CF13:1;                       // 13 Cancellation Finished 13
    bp_16 CF14:1;                       // 14 Cancellation Finished 14
    bp_16 CF15:1;                       // 15 Cancellation Finished 15
    bp_32 CF16:1;                       // 16 Cancellation Finished 16
    bp_32 CF17:1;                       // 17 Cancellation Finished 17
    bp_32 CF18:1;                       // 18 Cancellation Finished 18
    bp_32 CF19:1;                       // 19 Cancellation Finished 19
    bp_32 CF20:1;                       // 20 Cancellation Finished 20
    bp_32 CF21:1;                       // 21 Cancellation Finished 21
    bp_32 CF22:1;                       // 22 Cancellation Finished 22
    bp_32 CF23:1;                       // 23 Cancellation Finished 23
    bp_32 CF24:1;                       // 24 Cancellation Finished 24
    bp_32 CF25:1;                       // 25 Cancellation Finished 25
    bp_32 CF26:1;                       // 26 Cancellation Finished 26
    bp_32 CF27:1;                       // 27 Cancellation Finished 27
    bp_32 CF28:1;                       // 28 Cancellation Finished 28
    bp_32 CF29:1;                       // 29 Cancellation Finished 29
    bp_32 CF30:1;                       // 30 Cancellation Finished 30
    bp_32 CF31:1;                       // 31 Cancellation Finished 31
};

union MCAN_TXBCF_REG {
    bp_32  all;
    struct  MCAN_TXBCF_BITS  bit;
};

struct MCAN_TXBTIE_BITS {               // bits description
    bp_16 TIE0:1;                       // 0 Transmission Interrupt Enable 0
    bp_16 TIE1:1;                       // 1 Transmission Interrupt Enable 1
    bp_16 TIE2:1;                       // 2 Transmission Interrupt Enable 2
    bp_16 TIE3:1;                       // 3 Transmission Interrupt Enable 3
    bp_16 TIE4:1;                       // 4 Transmission Interrupt Enable 4
    bp_16 TIE5:1;                       // 5 Transmission Interrupt Enable 5
    bp_16 TIE6:1;                       // 6 Transmission Interrupt Enable 6
    bp_16 TIE7:1;                       // 7 Transmission Interrupt Enable 7
    bp_16 TIE8:1;                       // 8 Transmission Interrupt Enable 8
    bp_16 TIE9:1;                       // 9 Transmission Interrupt Enable 9
    bp_16 TIE10:1;                      // 10 Transmission Interrupt Enable 10
    bp_16 TIE11:1;                      // 11 Transmission Interrupt Enable 11
    bp_16 TIE12:1;                      // 12 Transmission Interrupt Enable 12
    bp_16 TIE13:1;                      // 13 Transmission Interrupt Enable 13
    bp_16 TIE14:1;                      // 14 Transmission Interrupt Enable 14
    bp_16 TIE15:1;                      // 15 Transmission Interrupt Enable 15
    bp_32 TIE16:1;                      // 16 Transmission Interrupt Enable 16
    bp_32 TIE17:1;                      // 17 Transmission Interrupt Enable 17
    bp_32 TIE18:1;                      // 18 Transmission Interrupt Enable 18
    bp_32 TIE19:1;                      // 19 Transmission Interrupt Enable 19
    bp_32 TIE20:1;                      // 20 Transmission Interrupt Enable 20
    bp_32 TIE21:1;                      // 21 Transmission Interrupt Enable 21
    bp_32 TIE22:1;                      // 22 Transmission Interrupt Enable 22
    bp_32 TIE23:1;                      // 23 Transmission Interrupt Enable 23
    bp_32 TIE24:1;                      // 24 Transmission Interrupt Enable 24
    bp_32 TIE25:1;                      // 25 Transmission Interrupt Enable 25
    bp_32 TIE26:1;                      // 26 Transmission Interrupt Enable 26
    bp_32 TIE27:1;                      // 27 Transmission Interrupt Enable 27
    bp_32 TIE28:1;                      // 28 Transmission Interrupt Enable 28
    bp_32 TIE29:1;                      // 29 Transmission Interrupt Enable 29
    bp_32 TIE30:1;                      // 30 Transmission Interrupt Enable 30
    bp_32 TIE31:1;                      // 31 Transmission Interrupt Enable 31
};

union MCAN_TXBTIE_REG {
    bp_32  all;
    struct  MCAN_TXBTIE_BITS  bit;
};

struct MCAN_TXBCIE_BITS {               // bits description
    bp_16 CFIE0:1;                      // 0 Cancellation Finished Interrupt Enable 0
    bp_16 CFIE1:1;                      // 1 Cancellation Finished Interrupt Enable 1
    bp_16 CFIE2:1;                      // 2 Cancellation Finished Interrupt Enable 2
    bp_16 CFIE3:1;                      // 3 Cancellation Finished Interrupt Enable 3
    bp_16 CFIE4:1;                      // 4 Cancellation Finished Interrupt Enable 4
    bp_16 CFIE5:1;                      // 5 Cancellation Finished Interrupt Enable 5
    bp_16 CFIE6:1;                      // 6 Cancellation Finished Interrupt Enable 6
    bp_16 CFIE7:1;                      // 7 Cancellation Finished Interrupt Enable 7
    bp_16 CFIE8:1;                      // 8 Cancellation Finished Interrupt Enable 8
    bp_16 CFIE9:1;                      // 9 Cancellation Finished Interrupt Enable 9
    bp_16 CFIE10:1;                     // 10 Cancellation Finished Interrupt Enable 10
    bp_16 CFIE11:1;                     // 11 Cancellation Finished Interrupt Enable 11
    bp_16 CFIE12:1;                     // 12 Cancellation Finished Interrupt Enable 12
    bp_16 CFIE13:1;                     // 13 Cancellation Finished Interrupt Enable 13
    bp_16 CFIE14:1;                     // 14 Cancellation Finished Interrupt Enable 14
    bp_16 CFIE15:1;                     // 15 Cancellation Finished Interrupt Enable 15
    bp_32 CFIE16:1;                     // 16 Cancellation Finished Interrupt Enable 16
    bp_32 CFIE17:1;                     // 17 Cancellation Finished Interrupt Enable 17
    bp_32 CFIE18:1;                     // 18 Cancellation Finished Interrupt Enable 18
    bp_32 CFIE19:1;                     // 19 Cancellation Finished Interrupt Enable 19
    bp_32 CFIE20:1;                     // 20 Cancellation Finished Interrupt Enable 20
    bp_32 CFIE21:1;                     // 21 Cancellation Finished Interrupt Enable 21
    bp_32 CFIE22:1;                     // 22 Cancellation Finished Interrupt Enable 22
    bp_32 CFIE23:1;                     // 23 Cancellation Finished Interrupt Enable 23
    bp_32 CFIE24:1;                     // 24 Cancellation Finished Interrupt Enable 24
    bp_32 CFIE25:1;                     // 25 Cancellation Finished Interrupt Enable 25
    bp_32 CFIE26:1;                     // 26 Cancellation Finished Interrupt Enable 26
    bp_32 CFIE27:1;                     // 27 Cancellation Finished Interrupt Enable 27
    bp_32 CFIE28:1;                     // 28 Cancellation Finished Interrupt Enable 28
    bp_32 CFIE29:1;                     // 29 Cancellation Finished Interrupt Enable 29
    bp_32 CFIE30:1;                     // 30 Cancellation Finished Interrupt Enable 30
    bp_32 CFIE31:1;                     // 31 Cancellation Finished Interrupt Enable 31
};

union MCAN_TXBCIE_REG {
    bp_32  all;
    struct  MCAN_TXBCIE_BITS  bit;
};

struct MCAN_TXEFC_BITS {                // bits description
    bp_16 rsvd1:2;                      // 1:0 Reserved
    bp_16 EFSA:14;                      // 15:2 Event FIFO Start Address
    bp_32 EFS:6;                        // 21:16 Event FIFO Size
    bp_32 rsvd2:2;                      // 23:22 Reserved
    bp_32 EFWM:6;                       // 29:24 Event FIFO Watermark
    bp_32 rsvd3:2;                      // 31:30 Reserved
};

union MCAN_TXEFC_REG {
    bp_32  all;
    struct  MCAN_TXEFC_BITS  bit;
};

struct MCAN_TXEFS_BITS {                // bits description
    bp_16 EFFL:6;                       // 5:0 Event FIFO Fill Level
    bp_16 rsvd1:2;                      // 7:6 Reserved
    bp_16 EFGI:5;                       // 12:8 Event FIFO Get Index
    bp_16 rsvd2:3;                      // 15:13 Reserved
    bp_32 EFPI:5;                       // 20:16 Event FIFO Put Index
    bp_32 rsvd3:3;                      // 23:21 Reserved
    bp_32 EFF:1;                        // 24 Event FIFO Full
    bp_32 TEFL:1;                       // 25 Tx Event FIFO Element Lost
    bp_32 rsvd4:6;                      // 31:26 Reserved
};

union MCAN_TXEFS_REG {
    bp_32  all;
    struct  MCAN_TXEFS_BITS  bit;
};

struct MCAN_TXEFA_BITS {                // bits description
    bp_16 EFAI:5;                       // 4:0 Event FIFO Acknowledge Index
    bp_16 rsvd1:11;                     // 15:5 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCAN_TXEFA_REG {
    bp_32  all;
    struct  MCAN_TXEFA_BITS  bit;
};

struct MCAN_REGS {
    union   MCAN_CREL_REG                    MCAN_CREL;                    // MCAN Core Release Register
    bp_32                                    MCAN_ENDN;                    // MCAN Endian Register
    uint32_t                                 rsvd1[2];                     // Reserved
    union   MCAN_DBTP_REG                    MCAN_DBTP;                    // MCAN Data Bit Timing and Prescaler Register
    union   MCAN_TEST_REG                    MCAN_TEST;                    // MCAN Test Register
    union   MCAN_RWD_REG                     MCAN_RWD;                     // MCAN RAM Watchdog
    union   MCAN_CCCR_REG                    MCAN_CCCR;                    // MCAN CC Control Register
    union   MCAN_NBTP_REG                    MCAN_NBTP;                    // MCAN Nominal Bit Timing and Prescaler Register
    union   MCAN_TSCC_REG                    MCAN_TSCC;                    // MCAN Timestamp Counter Configuration
    union   MCAN_TSCV_REG                    MCAN_TSCV;                    // MCAN Timestamp Counter Value
    union   MCAN_TOCC_REG                    MCAN_TOCC;                    // MCAN Timeout Counter Configuration
    union   MCAN_TOCV_REG                    MCAN_TOCV;                    // MCAN Timeout Counter Value
    uint32_t                                 rsvd2[8];                     // Reserved
    union   MCAN_ECR_REG                     MCAN_ECR;                     // MCAN Error Counter Register
    union   MCAN_PSR_REG                     MCAN_PSR;                     // MCAN Protocol Status Register
    union   MCAN_TDCR_REG                    MCAN_TDCR;                    // MCAN Transmitter Delay Compensation Register
    uint32_t                                 rsvd3[2];                     // Reserved
    union   MCAN_IR_REG                      MCAN_IR;                      // MCAN Interrupt Register
    union   MCAN_IE_REG                      MCAN_IE;                      // MCAN Interrupt Enable
    union   MCAN_ILS_REG                     MCAN_ILS;                     // MCAN Interrupt Line Select
    union   MCAN_ILE_REG                     MCAN_ILE;                     // MCAN Interrupt Line Enable
    uint32_t                                 rsvd4[16];                    // Reserved
    union   MCAN_GFC_REG                     MCAN_GFC;                     // MCAN Global Filter Configuration
    union   MCAN_SIDFC_REG                   MCAN_SIDFC;                   // MCAN Standard ID Filter Configuration
    union   MCAN_XIDFC_REG                   MCAN_XIDFC;                   // MCAN Extended ID Filter Configuration
    uint32_t                                 rsvd5[2];                     // Reserved
    union   MCAN_XIDAM_REG                   MCAN_XIDAM;                   // MCAN Extended ID and Mask
    union   MCAN_HPMS_REG                    MCAN_HPMS;                    // MCAN High Priority Message Status
    union   MCAN_NDAT1_REG                   MCAN_NDAT1;                   // MCAN New Data 1
    union   MCAN_NDAT2_REG                   MCAN_NDAT2;                   // MCAN New Data 2
    union   MCAN_RXF0C_REG                   MCAN_RXF0C;                   // MCAN Rx FIFO 0 Configuration
    union   MCAN_RXF0S_REG                   MCAN_RXF0S;                   // MCAN Rx FIFO 0 Status
    union   MCAN_RXF0A_REG                   MCAN_RXF0A;                   // MCAN Rx FIFO 0 Acknowledge
    union   MCAN_RXBC_REG                    MCAN_RXBC;                    // MCAN Rx Buffer Configuration
    union   MCAN_RXF1C_REG                   MCAN_RXF1C;                   // MCAN Rx FIFO 1 Configuration
    union   MCAN_RXF1S_REG                   MCAN_RXF1S;                   // MCAN Rx FIFO 1 Status
    union   MCAN_RXF1A_REG                   MCAN_RXF1A;                   // MCAN Rx FIFO 1 Acknowledge
    union   MCAN_RXESC_REG                   MCAN_RXESC;                   // MCAN Rx Buffer / FIFO Element Size Configuration
    union   MCAN_TXBC_REG                    MCAN_TXBC;                    // MCAN Tx Buffer Configuration
    union   MCAN_TXFQS_REG                   MCAN_TXFQS;                   // MCAN Tx FIFO / Queue Status
    union   MCAN_TXESC_REG                   MCAN_TXESC;                   // MCAN Tx Buffer Element Size Configuration
    union   MCAN_TXBRP_REG                   MCAN_TXBRP;                   // MCAN Tx Buffer Request Pending
    union   MCAN_TXBAR_REG                   MCAN_TXBAR;                   // MCAN Tx Buffer Add Request
    union   MCAN_TXBCR_REG                   MCAN_TXBCR;                   // MCAN Tx Buffer Cancellation Request
    union   MCAN_TXBTO_REG                   MCAN_TXBTO;                   // MCAN Tx Buffer Transmission Occurred
    union   MCAN_TXBCF_REG                   MCAN_TXBCF;                   // MCAN Tx Buffer Cancellation Finished
    union   MCAN_TXBTIE_REG                  MCAN_TXBTIE;                  // MCAN Tx Buffer Transmission Interrupt Enable
    union   MCAN_TXBCIE_REG                  MCAN_TXBCIE;                  // MCAN Tx Buffer Cancellation Finished Interrupt Enable
    uint32_t                                 rsvd6[4];                     // Reserved
    union   MCAN_TXEFC_REG                   MCAN_TXEFC;                   // MCAN Tx Event FIFO Configuration
    union   MCAN_TXEFS_REG                   MCAN_TXEFS;                   // MCAN Tx Event FIFO Status
    union   MCAN_TXEFA_REG                   MCAN_TXEFA;                   // MCAN Tx Event FIFO Acknowledge
};

struct MCANERR_REV_BITS {               // bits description
    bp_16 REVMIN:6;                     // 5:0 Minor Revision
    bp_16 rsvd1:2;                      // 7:6 Reserved
    bp_16 REVMAJ:3;                     // 10:8 Major Revision
    bp_16 rsvd2:5;                      // 15:11 Reserved
    bp_32 MODULE_ID:12;                 // 27:16 Module Identification Number
    bp_32 rsvd3:2;                      // 29:28 Reserved
    bp_32 SCHEME:2;                     // 31:30 PID Register Scheme
};

union MCANERR_REV_REG {
    bp_32  all;
    struct  MCANERR_REV_BITS  bit;
};

struct MCANERR_VECTOR_BITS {            // bits description
    bp_16 ECC_VECTOR:11;                // 10:0 ECC RAM ID
    bp_16 rsvd1:4;                      // 14:11 Reserved
    bp_16 RD_SVBUS:1;                   // 15 Read Trigger
    bp_32 RD_SVBUS_ADDRESS:8;           // 23:16 Read Address Offset
    bp_32 RD_SVBUS_DONE:1;              // 24 Read Completion Flag
    bp_32 rsvd2:7;                      // 31:25 Reserved
};

union MCANERR_VECTOR_REG {
    bp_32  all;
    struct  MCANERR_VECTOR_BITS  bit;
};

struct MCANERR_STAT_BITS {              // bits description
    bp_16 NUM_RAMS:11;                  // 10:0 Number of RAMs
    bp_16 rsvd1:5;                      // 15:11 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_STAT_REG {
    bp_32  all;
    struct  MCANERR_STAT_BITS  bit;
};

struct MCANERR_WRAP_REV_BITS {          // bits description
    bp_16 REVMIN:6;                     // 5:0 Minor Revision
    bp_16 rsvd1:2;                      // 7:6 Reserved
    bp_16 REVMAJ:3;                     // 10:8 Major Revision
    bp_16 rsvd2:5;                      // 15:11 Reserved
    bp_32 MODULE_ID:12;                 // 27:16 Module Identification Number
    bp_32 rsvd3:2;                      // 29:28 Reserved
    bp_32 SCHEME:2;                     // 31:30 PID Register Scheme
};

union MCANERR_WRAP_REV_REG {
    bp_32  all;
    struct  MCANERR_WRAP_REV_BITS  bit;
};

struct MCANERR_CTRL_BITS {              // bits description
    bp_16 ECC_ENABLE:1;                 // 0 Enable ECC Generation
    bp_16 ECC_CHECK:1;                  // 1 Enable ECC Check
    bp_16 ENABLE_RMW:1;                 // 2 Enable Read-Modify-Write
    bp_16 FORCE_SEC:1;                  // 3 Force Single Bit Error Corrected Error
    bp_16 FORCE_DED:1;                  // 4 Force Double Bit Error Detected Error
    bp_16 FORCE_N_ROW:1;                // 5 Force Next Single/Double Bit Error
    bp_16 ERROR_ONCE:1;                 // 6 Force Error Only Once Enable
    bp_16 rsvd1:1;                      // 7 Reserved
    bp_16 CHECK_SVBUS_TIMEOUT:1;        // 8 SVBUS Timeout Enable
    bp_16 rsvd2:7;                      // 15:9 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_CTRL_REG {
    bp_32  all;
    struct  MCANERR_CTRL_BITS  bit;
};

struct MCANERR_ERR_CTRL2_BITS {         // bits description
    bp_16 ECC_BIT1:16;                  // 15:0 Force Error Bit1 Column Index
    bp_32 ECC_BIT2:16;                  // 31:16 Force Error Bit2 Column Index
};

union MCANERR_ERR_CTRL2_REG {
    bp_32  all;
    struct  MCANERR_ERR_CTRL2_BITS  bit;
};

struct MCANERR_ERR_STAT1_BITS {         // bits description
    bp_16 ECC_SEC:2;                    // 1:0 Single Bit Error Corrected Status
    bp_16 ECC_DED:2;                    // 3:2 Double Bit Error Detected Status
    bp_16 ECC_OTHER:1;                  // 4 SEC While Writeback Error Status
    bp_16 rsvd1:2;                      // 6:5 Reserved
    bp_16 CTRL_REG_ERROR:1;             // 7 Control Register Error
    bp_16 CLR_ECC_SEC:2;                // 9:8 Clear ECC_SEC
    bp_16 CLR_ECC_DED:2;                // 11:10 Clear ECC_DED
    bp_16 CLR_ECC_OTHER:1;              // 12 Clear ECC_OTHER
    bp_16 rsvd2:2;                      // 14:13 Reserved
    bp_16 CLR_CTRL_REG_ERROR:1;         // 15 Clear Control Register Error
    bp_32 ECC_BIT1:16;                  // 31:16 ECC Error Bit Position
};

union MCANERR_ERR_STAT1_REG {
    bp_32  all;
    struct  MCANERR_ERR_STAT1_BITS  bit;
};

struct MCANERR_ERR_STAT3_BITS {         // bits description
    bp_16 WB_PEND:1;                    // 0 Delayed Write Back Pending Status
    bp_16 SVBUS_TIMEOUT:1;              // 1 Serial VBUS Timeout Flag
    bp_16 rsvd1:7;                      // 8:2 Reserved
    bp_16 CLR_SVBUS_TIMEOUT:1;          // 9 Clear Serial VBUS Timeout
    bp_16 rsvd2:6;                      // 15:10 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_ERR_STAT3_REG {
    bp_32  all;
    struct  MCANERR_ERR_STAT3_BITS  bit;
};

struct MCANERR_SEC_EOI_BITS {           // bits description
    bp_16 EOI_WR:1;                     // 0 End of Interrupt
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_SEC_EOI_REG {
    bp_32  all;
    struct  MCANERR_SEC_EOI_BITS  bit;
};

struct MCANERR_SEC_STATUS_BITS {        // bits description
    bp_16 MSGMEM_PEND:1;                // 0 Message RAM SEC Interrupt Pending
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_SEC_STATUS_REG {
    bp_32  all;
    struct  MCANERR_SEC_STATUS_BITS  bit;
};

struct MCANERR_SEC_ENABLE_SET_BITS {    // bits description
    bp_16 MSGMEM_ENABLE_SET:1;          // 0 Message RAM SEC Interrupt Pending Enable Set
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_SEC_ENABLE_SET_REG {
    bp_32  all;
    struct  MCANERR_SEC_ENABLE_SET_BITS  bit;
};

struct MCANERR_SEC_ENABLE_CLR_BITS {    // bits description
    bp_16 MSGMEM_ENABLE_CLR:1;          // 0 Message RAM SEC Interrupt Pending Enable Clear
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_SEC_ENABLE_CLR_REG {
    bp_32  all;
    struct  MCANERR_SEC_ENABLE_CLR_BITS  bit;
};

struct MCANERR_DED_EOI_BITS {           // bits description
    bp_16 EOI_WR:1;                     // 0 End of Interrupt
    bp_16 rsvd1:15;                     // 15:1 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_DED_EOI_REG {
    bp_32  all;
    struct  MCANERR_DED_EOI_BITS  bit;
};

struct MCANERR_DED_STATUS_BITS {        // bits description
    bp_16 MSGMEM_PEND:1;                // 0 Message RAM DED Interrupt Pending
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_DED_STATUS_REG {
    bp_32  all;
    struct  MCANERR_DED_STATUS_BITS  bit;
};

struct MCANERR_DED_ENABLE_SET_BITS {    // bits description
    bp_16 MSGMEM_ENABLE_SET:1;          // 0 Message RAM DED Interrupt Pending Enable Set
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_DED_ENABLE_SET_REG {
    bp_32  all;
    struct  MCANERR_DED_ENABLE_SET_BITS  bit;
};

struct MCANERR_DED_ENABLE_CLR_BITS {    // bits description
    bp_16 MSGMEM_ENABLE_CLR:1;          // 0 Message RAM DED Interrupt Pending Enable Clear
    bp_16 rsvd1:1;                      // 1 Reserved
    bp_16 rsvd2:14;                     // 15:2 Reserved
    bp_32 rsvd3:16;                     // 31:16 Reserved
};

union MCANERR_DED_ENABLE_CLR_REG {
    bp_32  all;
    struct  MCANERR_DED_ENABLE_CLR_BITS  bit;
};

struct MCANERR_AGGR_ENABLE_SET_BITS {   // bits description
    bp_16 ENABLE_PARITY_SET:1;          // 0 Enable Parity Errors Set
    bp_16 ENABLE_TIMEOUT_SET:1;         // 1 Enable Timeout Errors Set
    bp_16 rsvd1:14;                     // 15:2 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_AGGR_ENABLE_SET_REG {
    bp_32  all;
    struct  MCANERR_AGGR_ENABLE_SET_BITS  bit;
};

struct MCANERR_AGGR_ENABLE_CLR_BITS {   // bits description
    bp_16 ENABLE_PARITY_CLR:1;          // 0 Enable Parity Errors Clear
    bp_16 ENABLE_TIMEOUT_CLR:1;         // 1 Enable Timeout Errors Clear
    bp_16 rsvd1:14;                     // 15:2 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_AGGR_ENABLE_CLR_REG {
    bp_32  all;
    struct  MCANERR_AGGR_ENABLE_CLR_BITS  bit;
};

struct MCANERR_AGGR_STATUS_SET_BITS {   // bits description
    bp_16 AGGR_PARITY_ERR:2;            // 1:0 Aggregator Parity Error Status
    bp_16 SVBUS_TIMEOUT:2;              // 3:2 Aggregator Serial VBUS Timeout Error Status
    bp_16 rsvd1:12;                     // 15:4 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_AGGR_STATUS_SET_REG {
    bp_32  all;
    struct  MCANERR_AGGR_STATUS_SET_BITS  bit;
};

struct MCANERR_AGGR_STATUS_CLR_BITS {   // bits description
    bp_16 AGGR_PARITY_ERR:2;            // 1:0 Aggregator Parity Error Status
    bp_16 SVBUS_TIMEOUT:2;              // 3:2 Aggregator Serial VBUS Timeout Error Status
    bp_16 rsvd1:12;                     // 15:4 Reserved
    bp_32 rsvd2:16;                     // 31:16 Reserved
};

union MCANERR_AGGR_STATUS_CLR_REG {
    bp_32  all;
    struct  MCANERR_AGGR_STATUS_CLR_BITS  bit;
};

struct MCAN_ERROR_REGS {
    union   MCANERR_REV_REG                  MCANERR_REV;                  // MCAN Error Aggregator Revision Register
    uint32_t                                 rsvd1[2];                     // Reserved
    union   MCANERR_VECTOR_REG               MCANERR_VECTOR;               // MCAN ECC Vector Register
    union   MCANERR_STAT_REG                 MCANERR_STAT;                 // MCAN Error Misc Status
    union   MCANERR_WRAP_REV_REG             MCANERR_WRAP_REV;             // MCAN ECC Wrapper Revision Register
    union   MCANERR_CTRL_REG                 MCANERR_CTRL;                 // MCAN ECC Control
    bp_32                                    MCANERR_ERR_CTRL1;            // MCAN ECC Error Control 1 Register
    union   MCANERR_ERR_CTRL2_REG            MCANERR_ERR_CTRL2;            // MCAN ECC Error Control 2 Register
    union   MCANERR_ERR_STAT1_REG            MCANERR_ERR_STAT1;            // MCAN ECC Error Status 1 Register
    bp_32                                    MCANERR_ERR_STAT2;            // MCAN ECC Error Status 2 Register
    union   MCANERR_ERR_STAT3_REG            MCANERR_ERR_STAT3;            // MCAN ECC Error Status 3 Register
    uint32_t                                 rsvd2[8];                     // Reserved
    union   MCANERR_SEC_EOI_REG              MCANERR_SEC_EOI;              // MCAN Single Error Corrected End of Interrupt Register
    union   MCANERR_SEC_STATUS_REG           MCANERR_SEC_STATUS;           // MCAN Single Error Corrected Interrupt Status Register
    uint32_t                                 rsvd3[30];                    // Reserved
    union   MCANERR_SEC_ENABLE_SET_REG       MCANERR_SEC_ENABLE_SET;       // MCAN Single Error Corrected Interrupt Enable Set Register
    uint32_t                                 rsvd4[30];                    // Reserved
    union   MCANERR_SEC_ENABLE_CLR_REG       MCANERR_SEC_ENABLE_CLR;       // MCAN Single Error Corrected Interrupt Enable Clear Register
    uint32_t                                 rsvd5[60];                    // Reserved
    union   MCANERR_DED_EOI_REG              MCANERR_DED_EOI;              // MCAN Double Error Detected End of Interrupt Register
    union   MCANERR_DED_STATUS_REG           MCANERR_DED_STATUS;           // MCAN Double Error Detected Interrupt Status Register
    uint32_t                                 rsvd6[30];                    // Reserved
    union   MCANERR_DED_ENABLE_SET_REG       MCANERR_DED_ENABLE_SET;       // MCAN Double Error Detected Interrupt Enable Set Register
    uint32_t                                 rsvd7[30];                    // Reserved
    union   MCANERR_DED_ENABLE_CLR_REG       MCANERR_DED_ENABLE_CLR;       // MCAN Double Error Detected Interrupt Enable Clear Register
    uint32_t                                 rsvd8[30];                    // Reserved
    union   MCANERR_AGGR_ENABLE_SET_REG      MCANERR_AGGR_ENABLE_SET;      // MCAN Error Aggregator Enable Set Register
    union   MCANERR_AGGR_ENABLE_CLR_REG      MCANERR_AGGR_ENABLE_CLR;      // MCAN Error Aggregator Enable Clear Register
    union   MCANERR_AGGR_STATUS_SET_REG      MCANERR_AGGR_STATUS_SET;      // MCAN Error Aggregator Status Set Register
    union   MCANERR_AGGR_STATUS_CLR_REG      MCANERR_AGGR_STATUS_CLR;      // MCAN Error Aggregator Status Clear Register
};

//---------------------------------------------------------------------------
// MCAN External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct MCANSS_REGS McanaSsRegs;
extern volatile struct MCAN_REGS McanaRegs;
extern volatile struct MCAN_ERROR_REGS McanaErrorRegs;
extern volatile struct MCANSS_REGS McanbSsRegs;
extern volatile struct MCAN_REGS McanbRegs;
extern volatile struct MCAN_ERROR_REGS McanbErrorRegs;
#endif
#ifdef CPU2
extern volatile struct MCANSS_REGS McanaSsRegs;
extern volatile struct MCAN_REGS McanaRegs;
extern volatile struct MCAN_ERROR_REGS McanaErrorRegs;
extern volatile struct MCANSS_REGS McanbSsRegs;
extern volatile struct MCAN_REGS McanbRegs;
extern volatile struct MCAN_ERROR_REGS McanbErrorRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
