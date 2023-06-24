//###########################################################################
//
// FILE:    hw_i2c.h
//
// TITLE:   Definitions for the I2C registers.
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

#ifndef HW_I2C_H
#define HW_I2C_H

//*************************************************************************************************
//
// The following are defines for the I2C register offsets
//
//*************************************************************************************************
#define I2C_O_MSA          0x0U     // I2C Master Slave Address
#define I2C_O_MCS          0x4U     // I2C Master Control/Status
#define I2C_O_MDR          0x8U     // I2C Master Data
#define I2C_O_MTPR         0xCU     // I2C Master Timer Period
#define I2C_O_MIMR         0x10U    // I2C Master Interrupt Mask
#define I2C_O_MRIS         0x14U    // I2C Master Raw Interrupt Status
#define I2C_O_MMIS         0x18U    // I2C Master Masked Interrupt Status
#define I2C_O_MICR         0x1CU    // I2C Master Interrupt Clear
#define I2C_O_MCR          0x20U    // I2C Master Configuration
#define I2C_O_MCLKOCNT     0x24U    // I2C Master Clock Low Timeout Count
#define I2C_O_MBMON        0x2CU    // I2C Master Bus Monitor
#define I2C_O_MBLEN        0x30U    // I2C Master Burst Length
#define I2C_O_MBCNT        0x34U    // I2C Master Burst Count
#define I2C_O_SOAR         0x800U   // I2C Slave Own Address
#define I2C_O_SCSR         0x804U   // I2C Slave Control/Status
#define I2C_O_SDR          0x808U   // I2C Slave Data
#define I2C_O_SIMR         0x80CU   // I2C Slave Interrupt Mask
#define I2C_O_SRIS         0x810U   // I2C Slave Raw Interrupt Status
#define I2C_O_SMIS         0x814U   // I2C Slave Masked Interrupt Status
#define I2C_O_SICR         0x818U   // I2C Slave Interrupt Clear
#define I2C_O_SOAR2        0x81CU   // I2C Slave Own Address 2
#define I2C_O_SACKCTL      0x820U   // I2C Slave ACK Control
#define I2C_O_FIFODATARX   0xF00U   // I2C FIFO Data RX
#define I2C_O_FIFOCTL      0xF04U   // I2C FIFO Control
#define I2C_O_FIFOSTATUS   0xF08U   // I2C FIFO Status
#define I2C_O_PP           0xFC0U   // I2C Peripheral Properties
#define I2C_O_PC           0xFC4U   // I2C Peripheral Configuration

#define I2C_O_MCS_WRITE    0x4U     // I2C Master Control/Status
#define I2C_O_SCSR_WRITE   0x804U   // I2C Slave Control/Status
#define I2C_O_FIFODATATX   0xF00U   // I2C FIFO Data TX


//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMSA register
//
//*************************************************************************************************
#define I2C_MSA_RS     0x1U    // Receive/Send
#define I2C_MSA_SA_S   1U
#define I2C_MSA_SA_M   0xFEU   // I2C Slave Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMCS register
//
//*************************************************************************************************
#define I2C_MCS_BUSY       0x1U          // I2C Busy
#define I2C_MCS_ERROR      0x2U          // Error
#define I2C_MCS_ADRACK     0x4U          // Acknowledge Address
#define I2C_MCS_DATACK     0x8U          // Acknowledge Data
#define I2C_MCS_ARBLST     0x10U         // Arbitration Lost
#define I2C_MCS_IDLE       0x20U         // I2C Idle
#define I2C_MCS_BUSBSY     0x40U         // Bus Busy
#define I2C_MCS_CLKTO      0x80U         // Clock Timeout Error
#define I2C_MCS_ACTDMATX   0x40000000U   // DMA TX Active Status
#define I2C_MCS_ACTDMARX   0x80000000U   // DMA RX Active Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMDR register
//
//*************************************************************************************************
#define I2C_MDR_DATA_S   0U
#define I2C_MDR_DATA_M   0xFFU   // Data transmitted/received

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMTPR register
//
//*************************************************************************************************
#define I2C_MTPR_TPR_S      0U
#define I2C_MTPR_TPR_M      0x7FU      // Timer Period
#define I2C_MTPR_HS         0x80U      // High-Speed Enable
#define I2C_MTPR_PULSEL_S   16U
#define I2C_MTPR_PULSEL_M   0x70000U   // Glitch Suppression Pulse Width

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMIMR register
//
//*************************************************************************************************
#define I2C_MIMR_IM          0x1U     // Master Interrupt Mask
#define I2C_MIMR_CLKIM       0x2U     // Clock Timeout Interrupt Mask
#define I2C_MIMR_DMARXIM     0x4U     // Receive DMA Interrupt Mask
#define I2C_MIMR_DMATXIM     0x8U     // Transmit DMA Interrupt Mask
#define I2C_MIMR_NACKIM      0x10U    // Address/Data NACK Interrupt Mask
#define I2C_MIMR_STARTIM     0x20U    // START Detection Interrupt Mask
#define I2C_MIMR_STOPIM      0x40U    // STOP Detection Interrupt Mask
#define I2C_MIMR_ARBLOSTIM   0x80U    // Arbitration Lost Interrupt Mask
#define I2C_MIMR_TXIM        0x100U   // Transmit FIFO Request Interrupt Mask
#define I2C_MIMR_RXIM        0x200U   // Receive FIFO Request Interrupt Mask
#define I2C_MIMR_TXFEIM      0x400U   // Transmit FIFO Empty Interrupt Mask
#define I2C_MIMR_RXFFIM      0x800U   // Receive FIFO Full Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMRIS register
//
//*************************************************************************************************
#define I2C_MRIS_RIS          0x1U     // Master Raw Interrupt Status
#define I2C_MRIS_CLKRIS       0x2U     // Clock Timeout Raw Interrupt Status
#define I2C_MRIS_DMARXRIS     0x4U     // Receive DMA Raw Interrupt Status
#define I2C_MRIS_DMATXRIS     0x8U     // Transmit DMA Raw Interrupt Status
#define I2C_MRIS_NACKRIS      0x10U    // Address/Data NACK Raw Interrupt Status
#define I2C_MRIS_STARTRIS     0x20U    // START Detection Raw Interrupt Status
#define I2C_MRIS_STOPRIS      0x40U    // STOP Detection Raw Interrupt Status
#define I2C_MRIS_ARBLOSTRIS   0x80U    // Arbitration Lost Raw Interrupt Status
#define I2C_MRIS_TXRIS        0x100U   // Transmit Request Raw Interrupt Status
#define I2C_MRIS_RXRIS        0x200U   // Receive FIFO Request Raw Interrupt Status
#define I2C_MRIS_TXFERIS      0x400U   // Transmit FIFO Empty Raw Interrupt Status
#define I2C_MRIS_RXFFRIS      0x800U   // Receive FIFO Full Raw Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMMIS register
//
//*************************************************************************************************
#define I2C_MMIS_MIS          0x1U     // Masked Interrupt Status
#define I2C_MMIS_CLKMIS       0x2U     // Clock Timeout Masked Interrupt Status
#define I2C_MMIS_DMARXMIS     0x4U     // Receive DMA Interrupt Status
#define I2C_MMIS_DMATXMIS     0x8U     // Transmit DMA Interrupt Status
#define I2C_MMIS_NACKMIS      0x10U    // Address/Data NACK Interrupt Mask
#define I2C_MMIS_STARTMIS     0x20U    // START Detection Interrupt Mask
#define I2C_MMIS_STOPMIS      0x40U    // STOP Detection Interrupt Mask
#define I2C_MMIS_ARBLOSTMIS   0x80U    // Arbitration Lost Interrupt Mask
#define I2C_MMIS_TXMIS        0x100U   // Transmit Request Interrupt Mask
#define I2C_MMIS_RXMIS        0x200U   // Receive FIFO Request Interrupt Mask
#define I2C_MMIS_TXFEMIS      0x400U   // Transmit FIFO Empty Interrupt Mask
#define I2C_MMIS_RXFFMIS      0x800U   // Receive FIFO Full Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMICR register
//
//*************************************************************************************************
#define I2C_MICR_IC          0x1U     // Master Interrupt Clear
#define I2C_MICR_CLKIC       0x2U     // Clock Timeout Interrupt Clear
#define I2C_MICR_DMARXIC     0x4U     // Receive DMA Interrupt Clear
#define I2C_MICR_DMATXIC     0x8U     // Transmit DMA Interrupt Clear
#define I2C_MICR_NACKIC      0x10U    // Address/Data NACK Interrupt Clear
#define I2C_MICR_STARTIC     0x20U    // START Detection Interrupt Clear
#define I2C_MICR_STOPIC      0x40U    // STOP Detection Interrupt Clear
#define I2C_MICR_ARBLOSTIC   0x80U    // Arbitration Lost Interrupt Clear
#define I2C_MICR_TXIC        0x100U   // Transmit FIFO Request Interrupt Clear
#define I2C_MICR_RXIC        0x200U   // Receive FIFO Request Interrupt Clear
#define I2C_MICR_TXFEIC      0x400U   // Transmit FIFO Empty Interrupt Clear
#define I2C_MICR_RXFFIC      0x800U   // Receive FIFO Full Interrupt Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMCR register
//
//*************************************************************************************************
#define I2C_MCR_LPBK   0x1U    // I2C Loopback
#define I2C_MCR_MFE    0x10U   // I2C Master Function Enable
#define I2C_MCR_SFE    0x20U   // I2C Slave Function Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMCLKOCNT register
//
//*************************************************************************************************
#define I2C_MCLKOCNT_CNTL_S   0U
#define I2C_MCLKOCNT_CNTL_M   0xFFU   // I2C Master Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMBMON register
//
//*************************************************************************************************
#define I2C_MBMON_SCL   0x1U   // I2C SCL Status
#define I2C_MBMON_SDA   0x2U   // I2C SDA Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMBLEN register
//
//*************************************************************************************************
#define I2C_MBLEN_CNTL_S   0U
#define I2C_MBLEN_CNTL_M   0xFFU   // I2C Burst Length

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMBCNT register
//
//*************************************************************************************************
#define I2C_MBCNT_CNTL_S   0U
#define I2C_MBCNT_CNTL_M   0xFFU   // I2C Master Burst Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSOAR register
//
//*************************************************************************************************
#define I2C_SOAR_OAR_S   0U
#define I2C_SOAR_OAR_M   0x7FU   // I2C Slave Own Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSCSR register
//
//*************************************************************************************************
#define I2C_SCSR_RREQ       0x1U          // Receive Request
#define I2C_SCSR_TREQ       0x2U          // Transmit Request
#define I2C_SCSR_FBR        0x4U          // First Byte Received
#define I2C_SCSR_OAR2SEL    0x8U          // OAR2 Address Matched
#define I2C_SCSR_QCMDST     0x10U         // Quick Command Status
#define I2C_SCSR_QCMDRW     0x20U         // Quick Command Read / Write
#define I2C_SCSR_ACTDMATX   0x40000000U   // DMA TX Active Status
#define I2C_SCSR_ACTDMARX   0x80000000U   // DMA RX Active Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSDR register
//
//*************************************************************************************************
#define I2C_SDR_DATA_S   0U
#define I2C_SDR_DATA_M   0xFFU   // Data for Transfer

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSIMR register
//
//*************************************************************************************************
#define I2C_SIMR_DATAIM    0x1U     // Data Interrupt Mask
#define I2C_SIMR_STARTIM   0x2U     // Start Condition Interrupt Mask
#define I2C_SIMR_STOPIM    0x4U     // Stop Condition Interrupt Mask
#define I2C_SIMR_DMARXIM   0x8U     // Receive DMA Interrupt Mask
#define I2C_SIMR_DMATXIM   0x10U    // Transmit DMA Interrupt Mask
#define I2C_SIMR_TXIM      0x20U    // Transmit FIFO Request Interrupt Mask
#define I2C_SIMR_RXIM      0x40U    // Receive FIFO Request Interrupt Mask
#define I2C_SIMR_TXFEIM    0x80U    // Transmit FIFO Empty Interrupt Mask
#define I2C_SIMR_RXFFIM    0x100U   // Receive FIFO Full Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSRIS register
//
//*************************************************************************************************
#define I2C_SRIS_DATARIS    0x1U     // Data Raw Interrupt Status
#define I2C_SRIS_STARTRIS   0x2U     // Start Condition Raw Interrupt Status
#define I2C_SRIS_STOPRIS    0x4U     // Stop Condition Raw Interrupt Status
#define I2C_SRIS_DMARXRIS   0x8U     // Receive DMA Raw Interrupt Status
#define I2C_SRIS_DMATXRIS   0x10U    // Transmit DMA Raw Interrupt Status
#define I2C_SRIS_TXRIS      0x20U    // Transmit Request Raw Interrupt Status
#define I2C_SRIS_RXRIS      0x40U    // Receive FIFO Request Raw Interrupt Status
#define I2C_SRIS_TXFERIS    0x80U    // Transmit FIFO Empty Raw Interrupt Status
#define I2C_SRIS_RXFFRIS    0x100U   // Receive FIFO Full Raw Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSMIS register
//
//*************************************************************************************************
#define I2C_SMIS_DATAMIS    0x1U     // Data Masked Interrupt Status
#define I2C_SMIS_STARTMIS   0x2U     // Start Condition Masked Interrupt Status
#define I2C_SMIS_STOPMIS    0x4U     // Stop Condition Masked Interrupt Status
#define I2C_SMIS_DMARXMIS   0x8U     // Receive DMA Masked Interrupt Status
#define I2C_SMIS_DMATXMIS   0x10U    // Transmit DMA Masked Interrupt Status
#define I2C_SMIS_TXMIS      0x20U    // Transmit FIFO Request Interrupt Mask
#define I2C_SMIS_RXMIS      0x40U    // Receive FIFO Request Interrupt Mask
#define I2C_SMIS_TXFEMIS    0x80U    // Transmit FIFO Empty Interrupt Mask
#define I2C_SMIS_RXFFMIS    0x100U   // Receive FIFO Full Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSICR register
//
//*************************************************************************************************
#define I2C_SICR_DATAIC    0x1U     // Data Interrupt Clear
#define I2C_SICR_STARTIC   0x2U     // Start Condition Interrupt Clear
#define I2C_SICR_STOPIC    0x4U     // Stop Condition Interrupt Clear
#define I2C_SICR_DMARXIC   0x8U     // Receive DMA Interrupt Clear
#define I2C_SICR_DMATXIC   0x10U    // Transmit DMA Interrupt Clear
#define I2C_SICR_TXIC      0x20U    // Transmit Request Interrupt Mask
#define I2C_SICR_RXIC      0x40U    // Receive Request Interrupt Mask
#define I2C_SICR_TXFEIC    0x80U    // Transmit FIFO Empty Interrupt Mask
#define I2C_SICR_RXFFIC    0x100U   // Receive FIFO Full Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSOAR2 register
//
//*************************************************************************************************
#define I2C_SOAR2_OAR2_S   0U
#define I2C_SOAR2_OAR2_M   0x7FU   // I2C Slave Own Address 2
#define I2C_SOAR2_OAR2EN   0x80U   // I2C Slave Own Address 2 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSACKCTL register
//
//*************************************************************************************************
#define I2C_SACKCTL_ACKOEN    0x1U   // I2C Slave ACK Override Enable
#define I2C_SACKCTL_ACKOVAL   0x2U   // I2C Slave ACK Override Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CFIFODATARX register
//
//*************************************************************************************************
#define I2C_FIFODATARX_DATA_S   0U
#define I2C_FIFODATARX_DATA_M   0xFFU   // I2C RX FIFO Read Data Byte

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CFIFOCTL register
//
//*************************************************************************************************
#define I2C_FIFOCTL_TXTRIG_S   0U
#define I2C_FIFOCTL_TXTRIG_M   0x7U          // TX FIFO Trigger
#define I2C_FIFOCTL_DMATXENA   0x2000U       // DMA TX Channel Enable
#define I2C_FIFOCTL_TXFLUSH    0x4000U       // TX FIFO Flush
#define I2C_FIFOCTL_TXASGNMT   0x8000U       // TX Control Assignment
#define I2C_FIFOCTL_RXTRIG_S   16U
#define I2C_FIFOCTL_RXTRIG_M   0x70000U      // RX FIFO Trigger
#define I2C_FIFOCTL_DMARXENA   0x20000000U   // DMA RX Channel Enable
#define I2C_FIFOCTL_RXFLUSH    0x40000000U   // RX FIFO Flush
#define I2C_FIFOCTL_RXASGNMT   0x80000000U   // RX Control Assignment

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CFIFOSTATUS register
//
//*************************************************************************************************
#define I2C_FIFOSTATUS_TXFE        0x1U       // TX FIFO Empty
#define I2C_FIFOSTATUS_TXFF        0x2U       // TX FIFO Full
#define I2C_FIFOSTATUS_TXBLWTRIG   0x4U       // TX FIFO Below Trigger Level
#define I2C_FIFOSTATUS_RXFE        0x10000U   // RX FIFO Empty
#define I2C_FIFOSTATUS_RXFF        0x20000U   // RX FIFO Full
#define I2C_FIFOSTATUS_RXABVTRIG   0x40000U   // RX FIFO Above Trigger Level

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CPP register
//
//*************************************************************************************************
#define I2C_PP_HS   0x1U   // High-Speed Capable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CPC register
//
//*************************************************************************************************
#define I2C_PC_HS   0x1U   // High-Speed Capable


//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CMCS_WRITE register
//
//*************************************************************************************************
#define I2C_MCS_WRITE_RUN     0x1U    // I2C Master Enable
#define I2C_MCS_WRITE_START   0x2U    // Generate START
#define I2C_MCS_WRITE_STOP    0x4U    // Generate STOP
#define I2C_MCS_WRITE_ACK     0x8U    // Data Acknowledge Enable
#define I2C_MCS_WRITE_HS      0x10U   // High-Speed Enable
#define I2C_MCS_WRITE_QCMD    0x20U   // Quick Command
#define I2C_MCS_WRITE_BURST   0x40U   // Burst Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CSCSR_WRITE register
//
//*************************************************************************************************
#define I2C_SCSR_WRITE_DA       0x1U   // Device Active
#define I2C_SCSR_WRITE_TXFIFO   0x2U   // TX FIFO Enable
#define I2C_SCSR_WRITE_RXFIFO   0x4U   // RX FIFO Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CFIFODATATX register
//
//*************************************************************************************************
#define I2C_FIFODATATX_DATA_S   0U
#define I2C_FIFODATATX_DATA_M   0xFFU   // I2C TX FIFO Write Data Byte



#endif
