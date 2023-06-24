//###########################################################################
//
// FILE:    hw_ssi.h
//
// TITLE:   Definitions for the SSI registers.
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

#ifndef HW_SSI_H
#define HW_SSI_H

//*************************************************************************************************
//
// The following are defines for the SSI register offsets
//
//*************************************************************************************************
#define SSI_O_CR0         0x0U     // SSI Control 0
#define SSI_O_CR1         0x4U     // SSI Control 1
#define SSI_O_DR          0x8U     // SSI Data
#define SSI_O_SR          0xCU     // SSI Status
#define SSI_O_CPSR        0x10U    // SSI Clock Prescale
#define SSI_O_IM          0x14U    // SSI Interrupt Mask
#define SSI_O_RIS         0x18U    // SSI Raw Interrupt Status
#define SSI_O_MIS         0x1CU    // SSI Masked Interrupt      Status
#define SSI_O_ICR         0x20U    // SSI Interrupt Clear
#define SSI_O_DMACTL      0x24U    // SSI DMA Control
#define SSI_O_PV          0xFB0U   // SSI Peripheral Version
#define SSI_O_PP          0xFC0U   // SSI Peripheral Properties
#define SSI_O_PERIPHID4   0xFD0U   // SSI Peripheral      Identification 4
#define SSI_O_PERIPHID5   0xFD4U   // SSI Peripheral      Identification 5
#define SSI_O_PERIPHID6   0xFD8U   // SSI Peripheral      Identification 6
#define SSI_O_PERIPHID7   0xFDCU   // SSI Peripheral      Identification 7
#define SSI_O_PERIPHID0   0xFE0U   // SSI Peripheral      Identification 0
#define SSI_O_PERIPHID1   0xFE4U   // SSI Peripheral      Identification 1
#define SSI_O_PERIPHID2   0xFE8U   // SSI Peripheral      Identification 2
#define SSI_O_PERIPHID3   0xFECU   // SSI Peripheral      Identification 3
#define SSI_O_PCELLID0    0xFF0U   // SSI PrimeCell      Identification 0
#define SSI_O_PCELLID1    0xFF4U   // SSI PrimeCell      Identification 1
#define SSI_O_PCELLID2    0xFF8U   // SSI PrimeCell      Identification 2
#define SSI_O_PCELLID3    0xFFCU   // SSI PrimeCell      Identification 3


//*************************************************************************************************
//
// The following are defines for the bit fields in the SSICR0 register
//
//*************************************************************************************************
#define SSI_CR0_DSS_S   0U
#define SSI_CR0_DSS_M   0xFU      // SSI Data Size Select
#define SSI_CR0_FRF_S   4U
#define SSI_CR0_FRF_M   0x30U     // SSI FRame Format Select
#define SSI_CR0_SPO     0x40U     // SSI Serial clock POlarity
#define SSI_CR0_SPH     0x80U     // SSI Serial clock PHase
#define SSI_CR0_SCR_S   8U
#define SSI_CR0_SCR_M   0xFF00U   // SSI Serial Clock Rate

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSICR1 register
//
//*************************************************************************************************
#define SSI_CR1_LBM         0x1U     // SSI Loopback Mode
#define SSI_CR1_SSE         0x2U     // SSI Synchronous Serial Port Enable
#define SSI_CR1_MS          0x4U     // SSI Master/Slave Select
#define SSI_CR1_EOT         0x10U    // End of Transmission
#define SSI_CR1_DIR         0x100U   // SSI Direction of Operation
#define SSI_CR1_HSCLKEN     0x200U   // High Speed Clock Enable
#define SSI_CR1_FSSHLDFRM   0x400U   // FSS Hold Frame

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIDR register
//
//*************************************************************************************************
#define SSI_DR_DATA_S   0U
#define SSI_DR_DATA_M   0xFFFFU   // SSI Receive/Transmit Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSISR register
//
//*************************************************************************************************
#define SSI_SR_TFE   0x1U    // SSI Transmit FIFO Empty
#define SSI_SR_TNF   0x2U    // SSI Transmit FIFO Not Full
#define SSI_SR_RNE   0x4U    // SSI Receive FIFO Not Empty
#define SSI_SR_RFF   0x8U    // SSI Receive FIFO Full
#define SSI_SR_BSY   0x10U   // SSI Busy Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSICPSR register
//
//*************************************************************************************************
#define SSI_CPSR_CPSDVSR_S   0U
#define SSI_CPSR_CPSDVSR_M   0xFFU   // SSI Clock Prescale Divisor

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIIM register
//
//*************************************************************************************************
#define SSI_IM_RORIM     0x1U    // SSI Receive Overrun Interrupt Mask
#define SSI_IM_RTIM      0x2U    // SSI Receive Time-Out Interrupt Mask
#define SSI_IM_RXIM      0x4U    // SSI Receive FIFO Interrupt Mask
#define SSI_IM_TXIM      0x8U    // SSI Transmit FIFO Interrupt Mask
#define SSI_IM_DMARXIM   0x10U   // SSI Receive DMA Interrupt Mask
#define SSI_IM_DMATXIM   0x20U   // SSI Transmit DMA Interrupt Mask
#define SSI_IM_EOTIM     0x40U   // End of Transmit Interrupt Mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIRIS register
//
//*************************************************************************************************
#define SSI_RIS_RORRIS     0x1U    // SSI Receive Overrun Raw Interrupt Status
#define SSI_RIS_RTRIS      0x2U    // SSI Receive Time-Out Raw Interrupt Status
#define SSI_RIS_RXRIS      0x4U    // SSI Receive FIFO Raw Interrupt Status
#define SSI_RIS_TXRIS      0x8U    // SSI Transmit FIFO Raw Interrupt Status
#define SSI_RIS_DMARXRIS   0x10U   // SSI Receive DMA Raw Interrupt Status
#define SSI_RIS_DMATXRIS   0x20U   // SSI Transmit DMA Raw Interrupt Status
#define SSI_RIS_EOTRIS     0x40U   // End of Transmit Raw Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIMIS register
//
//*************************************************************************************************
#define SSI_MIS_RORMIS     0x1U    // SSI Receive Overrun Masked Interrupt Status
#define SSI_MIS_RTMIS      0x2U    // SSI Receive Time-Out Masked Interrupt Status
#define SSI_MIS_RXMIS      0x4U    // SSI Receive FIFO Masked Interrupt Status
#define SSI_MIS_TXMIS      0x8U    // SSI Transmit FIFO Masked Interrupt Status
#define SSI_MIS_DMARXMIS   0x10U   // SSI Receive DMA Masked Interrupt Status
#define SSI_MIS_DMATXMIS   0x20U   // SSI Transmit DMA Masked Interrupt Status
#define SSI_MIS_EOTMIS     0x40U   // End of Transmit Masked Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIICR register
//
//*************************************************************************************************
#define SSI_ICR_RORIC     0x1U    // SSI Receive Overrun Interrupt Clear
#define SSI_ICR_RTIC      0x2U    // SSI Receive Time-Out Interrupt Clear
#define SSI_ICR_DMARXIC   0x10U   // SSI Receive DMA Interrupt Clear
#define SSI_ICR_DMATXIC   0x20U   // SSI Transmit DMA Interrupt Clear
#define SSI_ICR_EOTIC     0x40U   // End of Transmit Interrupt Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIDMACTL register
//
//*************************************************************************************************
#define SSI_DMACTL_RXDMAE   0x1U   // Receive DMA Enable
#define SSI_DMACTL_TXDMAE   0x2U   // Transmit DMA Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPV register
//
//*************************************************************************************************
#define SSI_PV_MINOR_S   0U
#define SSI_PV_MINOR_M   0xFFU     // Minor Revision
#define SSI_PV_MAJOR_S   8U
#define SSI_PV_MAJOR_M   0xFF00U   // Major Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPP register
//
//*************************************************************************************************
#define SSI_PP_HSCLK       0x1U   // High Speed Capability
#define SSI_PP_MODE_S      1U
#define SSI_PP_MODE_M      0x6U   // Mode of Operation
#define SSI_PP_FSSHLDFRM   0x8U   //  SSInFss Hold Frame Capability

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID4 register
//
//*************************************************************************************************
#define SSI_PERIPHID4_PID4_S   0U
#define SSI_PERIPHID4_PID4_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID5 register
//
//*************************************************************************************************
#define SSI_PERIPHID5_PID5_S   0U
#define SSI_PERIPHID5_PID5_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID6 register
//
//*************************************************************************************************
#define SSI_PERIPHID6_PID6_S   0U
#define SSI_PERIPHID6_PID6_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID7 register
//
//*************************************************************************************************
#define SSI_PERIPHID7_PID7_S   0U
#define SSI_PERIPHID7_PID7_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID0 register
//
//*************************************************************************************************
#define SSI_PERIPHID0_PID0_S   0U
#define SSI_PERIPHID0_PID0_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID1 register
//
//*************************************************************************************************
#define SSI_PERIPHID1_PID1_S   0U
#define SSI_PERIPHID1_PID1_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID2 register
//
//*************************************************************************************************
#define SSI_PERIPHID2_PID2_S   0U
#define SSI_PERIPHID2_PID2_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPeriphID3 register
//
//*************************************************************************************************
#define SSI_PERIPHID3_PID3_S   0U
#define SSI_PERIPHID3_PID3_M   0xFFU   // SSI Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPCellID0 register
//
//*************************************************************************************************
#define SSI_PCELLID0_CID0_S   0U
#define SSI_PCELLID0_CID0_M   0xFFU   // SSI PrimeCell ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPCellID1 register
//
//*************************************************************************************************
#define SSI_PCELLID1_CID1_S   0U
#define SSI_PCELLID1_CID1_M   0xFFU   // SSI PrimeCell ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPCellID2 register
//
//*************************************************************************************************
#define SSI_PCELLID2_CID2_S   0U
#define SSI_PCELLID2_CID2_M   0xFFU   // SSI PrimeCell ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SSIPCellID3 register
//
//*************************************************************************************************
#define SSI_PCELLID3_CID3_S   0U
#define SSI_PCELLID3_CID3_M   0xFFU   // SSI PrimeCell ID Register



#endif
