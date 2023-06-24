//###########################################################################
//
// FILE:    hw_udma.h
//
// TITLE:   Definitions for the UDMA registers.
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

#ifndef HW_UDMA_H
#define HW_UDMA_H

//*************************************************************************************************
//
// The following are defines for the UDMA register offsets
//
//*************************************************************************************************
#define UDMA_O_DMASRCENDP   0x0U   // DMA Channel Source Address End Pointer
#define UDMA_O_DMADSTENDP   0x4U   // DMA Channel Destination Address End Pointer
#define UDMA_O_DMACHCTL     0x8U   // DMA Channel Control Word

#define UDMA_O_DMASTAT          0x0U     // DMA Status
#define UDMA_O_DMACFG           0x4U     // DMA Configuration
#define UDMA_O_DMACTLBASE       0x8U     // DMA Channel Control Base Pointer
#define UDMA_O_DMAALTBASE       0xCU     // DMA Alternate Channel Control Base Pointer
#define UDMA_O_DMASWREQ         0x14U    // DMA Channel Software Request
#define UDMA_O_DMAUSEBURSTSET   0x18U    // DMA Channel Useburst Set
#define UDMA_O_DMAUSEBURSTCLR   0x1CU    // DMA Channel Useburst Clear
#define UDMA_O_DMAREQMASKSET    0x20U    // DMA Channel Request Mask Set
#define UDMA_O_DMAREQMASKCLR    0x24U    // DMA Channel Request Mask Clear
#define UDMA_O_DMAENASET        0x28U    // DMA Channel Enable Set
#define UDMA_O_DMAENACLR        0x2CU    // DMA Channel Enable Clear
#define UDMA_O_DMAALTSET        0x30U    // DMA Channel Primary Alternate Set
#define UDMA_O_DMAALTCLR        0x34U    // DMA Channel Primary Alternate Clear
#define UDMA_O_DMAPRIOSET       0x38U    // DMA Channel Priority Set
#define UDMA_O_DMAPRIOCLR       0x3CU    // DMA Channel Priority Clear
#define UDMA_O_DMAERRCLR        0x4CU    // DMA Bus Error Clear
#define UDMA_O_DMACHMAP0        0x510U   // DMA Channel Map Select 0
#define UDMA_O_DMACHMAP1        0x514U   // DMA Channel Map Select 1
#define UDMA_O_DMACHMAP2        0x518U   // DMA Channel Map Select 2
#define UDMA_O_DMACHMAP3        0x51CU   // DMA Channel Map Select 3
#define UDMA_O_DMAPERIPHID4     0xFD0U   // DMA Peripheral Identification 4
#define UDMA_O_DMAPERIPHID0     0xFE0U   // DMA Peripheral Identification 0
#define UDMA_O_DMAPERIPHID1     0xFE4U   // DMA Peripheral Identification 1
#define UDMA_O_DMAPERIPHID2     0xFE8U   // DMA Peripheral Identification 2
#define UDMA_O_DMAPERIPHID3     0xFECU   // DMA Peripheral Identification 3
#define UDMA_O_DMAPCELLID0      0xFF0U   // DMA PrimeCell Identification 0
#define UDMA_O_DMAPCELLID1      0xFF4U   // DMA PrimeCell Identification 1
#define UDMA_O_DMAPCELLID2      0xFF8U   // DMA PrimeCell Identification 2
#define UDMA_O_DMAPCELLID3      0xFFCU   // DMA PrimeCell Identification 3


//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHCTL register
//
//*************************************************************************************************
#define UDMA_DMACHCTL_XFERMODE_S    0U
#define UDMA_DMACHCTL_XFERMODE_M    0x7U          // DMA Transfer Mode
#define UDMA_DMACHCTL_NXTUSEBURST   0x8U          // Next Useburst
#define UDMA_DMACHCTL_XFERSIZE_S    4U
#define UDMA_DMACHCTL_XFERSIZE_M    0x3FF0U       // Transfer Size (minus 1)
#define UDMA_DMACHCTL_ARBSIZE_S     14U
#define UDMA_DMACHCTL_ARBSIZE_M     0x3C000U      // Arbitration Size
#define UDMA_DMACHCTL_SRCPROT0      0x40000U      // Source Privilege Access
#define UDMA_DMACHCTL_DSTPROT0      0x200000U     // Destination Privilege Access
#define UDMA_DMACHCTL_SRCSIZE_S     24U
#define UDMA_DMACHCTL_SRCSIZE_M     0x3000000U    // Source Data Size
#define UDMA_DMACHCTL_SRCINC_S      26U
#define UDMA_DMACHCTL_SRCINC_M      0xC000000U    // Source Address Increment
#define UDMA_DMACHCTL_DSTSIZE_S     28U
#define UDMA_DMACHCTL_DSTSIZE_M     0x30000000U   // Destination Data Size
#define UDMA_DMACHCTL_DSTINC_S      30U
#define UDMA_DMACHCTL_DSTINC_M      0xC0000000U   // Destination Address Increment


//*************************************************************************************************
//
// The following are defines for the bit fields in the DMASTAT register
//
//*************************************************************************************************
#define UDMA_DMASTAT_MASTEN       0x1U        // Master Enable Status
#define UDMA_DMASTAT_STATE_S      4U
#define UDMA_DMASTAT_STATE_M      0xF0U       // Control State Machine Status
#define UDMA_DMASTAT_DMACHANS_S   16U
#define UDMA_DMASTAT_DMACHANS_M   0x1F0000U   // Available DMA Channels Minus 1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACFG register
//
//*************************************************************************************************
#define UDMA_DMACFG_MASTEN   0x1U   // Controller Master Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACTLBASE register
//
//*************************************************************************************************
#define UDMA_DMACTLBASE_ADDR_S   10U
#define UDMA_DMACTLBASE_ADDR_M   0xFFFFFC00U   // Channel Control Base Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAERRCLR register
//
//*************************************************************************************************
#define UDMA_DMAERRCLR_ERRCLR   0x1U   // DMA Bus Error Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHMAP0 register
//
//*************************************************************************************************
#define UDMA_DMACHMAP0_CH0SEL_S   0U
#define UDMA_DMACHMAP0_CH0SEL_M   0xFU          // DMA Channel 0 Source Select
#define UDMA_DMACHMAP0_CH1SEL_S   4U
#define UDMA_DMACHMAP0_CH1SEL_M   0xF0U         // DMA Channel 1 Source Select
#define UDMA_DMACHMAP0_CH2SEL_S   8U
#define UDMA_DMACHMAP0_CH2SEL_M   0xF00U        // DMA Channel 2 Source Select
#define UDMA_DMACHMAP0_CH3SEL_S   12U
#define UDMA_DMACHMAP0_CH3SEL_M   0xF000U       // DMA Channel 3 Source Select
#define UDMA_DMACHMAP0_CH4SEL_S   16U
#define UDMA_DMACHMAP0_CH4SEL_M   0xF0000U      // DMA Channel 4 Source Select
#define UDMA_DMACHMAP0_CH5SEL_S   20U
#define UDMA_DMACHMAP0_CH5SEL_M   0xF00000U     // DMA Channel 5 Source Select
#define UDMA_DMACHMAP0_CH6SEL_S   24U
#define UDMA_DMACHMAP0_CH6SEL_M   0xF000000U    // DMA Channel 6 Source Select
#define UDMA_DMACHMAP0_CH7SEL_S   28U
#define UDMA_DMACHMAP0_CH7SEL_M   0xF0000000U   // DMA Channel 7 Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHMAP1 register
//
//*************************************************************************************************
#define UDMA_DMACHMAP1_CH8SEL_S    0U
#define UDMA_DMACHMAP1_CH8SEL_M    0xFU          // DMA Channel 8 Source Select
#define UDMA_DMACHMAP1_CH9SEL_S    4U
#define UDMA_DMACHMAP1_CH9SEL_M    0xF0U         // DMA Channel 9 Source Select
#define UDMA_DMACHMAP1_CH10SEL_S   8U
#define UDMA_DMACHMAP1_CH10SEL_M   0xF00U        // DMA Channel 10 Source Select
#define UDMA_DMACHMAP1_CH11SEL_S   12U
#define UDMA_DMACHMAP1_CH11SEL_M   0xF000U       // DMA Channel 11 Source Select
#define UDMA_DMACHMAP1_CH12SEL_S   16U
#define UDMA_DMACHMAP1_CH12SEL_M   0xF0000U      // DMA Channel 12 Source Select
#define UDMA_DMACHMAP1_CH13SEL_S   20U
#define UDMA_DMACHMAP1_CH13SEL_M   0xF00000U     // DMA Channel 13 Source Select
#define UDMA_DMACHMAP1_CH14SEL_S   24U
#define UDMA_DMACHMAP1_CH14SEL_M   0xF000000U    // DMA Channel 14 Source Select
#define UDMA_DMACHMAP1_CH15SEL_S   28U
#define UDMA_DMACHMAP1_CH15SEL_M   0xF0000000U   // DMA Channel 15 Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHMAP2 register
//
//*************************************************************************************************
#define UDMA_DMACHMAP2_CH16SEL_S   0U
#define UDMA_DMACHMAP2_CH16SEL_M   0xFU          // DMA Channel 16 Source Select
#define UDMA_DMACHMAP2_CH17SEL_S   4U
#define UDMA_DMACHMAP2_CH17SEL_M   0xF0U         // DMA Channel 17 Source Select
#define UDMA_DMACHMAP2_CH18SEL_S   8U
#define UDMA_DMACHMAP2_CH18SEL_M   0xF00U        // DMA Channel 18 Source Select
#define UDMA_DMACHMAP2_CH19SEL_S   12U
#define UDMA_DMACHMAP2_CH19SEL_M   0xF000U       // DMA Channel 19 Source Select
#define UDMA_DMACHMAP2_CH20SEL_S   16U
#define UDMA_DMACHMAP2_CH20SEL_M   0xF0000U      // DMA Channel 20 Source Select
#define UDMA_DMACHMAP2_CH21SEL_S   20U
#define UDMA_DMACHMAP2_CH21SEL_M   0xF00000U     // DMA Channel 21 Source Select
#define UDMA_DMACHMAP2_CH22SEL_S   24U
#define UDMA_DMACHMAP2_CH22SEL_M   0xF000000U    // DMA Channel 22 Source Select
#define UDMA_DMACHMAP2_CH23SEL_S   28U
#define UDMA_DMACHMAP2_CH23SEL_M   0xF0000000U   // DMA Channel 23 Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHMAP3 register
//
//*************************************************************************************************
#define UDMA_DMACHMAP3_CH24SEL_S   0U
#define UDMA_DMACHMAP3_CH24SEL_M   0xFU          // DMA Channel 24 Source Select
#define UDMA_DMACHMAP3_CH25SEL_S   4U
#define UDMA_DMACHMAP3_CH25SEL_M   0xF0U         // DMA Channel 25 Source Select
#define UDMA_DMACHMAP3_CH26SEL_S   8U
#define UDMA_DMACHMAP3_CH26SEL_M   0xF00U        // DMA Channel 26 Source Select
#define UDMA_DMACHMAP3_CH27SEL_S   12U
#define UDMA_DMACHMAP3_CH27SEL_M   0xF000U       // DMA Channel 27 Source Select
#define UDMA_DMACHMAP3_CH28SEL_S   16U
#define UDMA_DMACHMAP3_CH28SEL_M   0xF0000U      // DMA Channel 28 Source Select
#define UDMA_DMACHMAP3_CH29SEL_S   20U
#define UDMA_DMACHMAP3_CH29SEL_M   0xF00000U     // DMA Channel 29 Source Select
#define UDMA_DMACHMAP3_CH30SEL_S   24U
#define UDMA_DMACHMAP3_CH30SEL_M   0xF000000U    // DMA Channel 30 Source Select
#define UDMA_DMACHMAP3_CH31SEL_S   28U
#define UDMA_DMACHMAP3_CH31SEL_M   0xF0000000U   // DMA Channel 31 Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPeriphID4 register
//
//*************************************************************************************************
#define UDMA_DMAPERIPHID4_PID4_S   0U
#define UDMA_DMAPERIPHID4_PID4_M   0xFFU   // DMA Peripheral ID Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPeriphID0 register
//
//*************************************************************************************************
#define UDMA_DMAPERIPHID0_PID0_S   0U
#define UDMA_DMAPERIPHID0_PID0_M   0xFFU   // DMA Peripheral ID Register [7:0]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPeriphID1 register
//
//*************************************************************************************************
#define UDMA_DMAPERIPHID1_PID1_S   0U
#define UDMA_DMAPERIPHID1_PID1_M   0xFFU   // DMA Peripheral ID Register [15:8]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPeriphID2 register
//
//*************************************************************************************************
#define UDMA_DMAPERIPHID2_PID2_S   0U
#define UDMA_DMAPERIPHID2_PID2_M   0xFFU   // DMA Peripheral ID Register [23:16]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPeriphID3 register
//
//*************************************************************************************************
#define UDMA_DMAPERIPHID3_PID3_S   0U
#define UDMA_DMAPERIPHID3_PID3_M   0xFFU   // DMA Peripheral ID Register [31:24]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPCellID0 register
//
//*************************************************************************************************
#define UDMA_DMAPCELLID0_CID0_S   0U
#define UDMA_DMAPCELLID0_CID0_M   0xFFU   // DMA PrimeCell ID Register [7:0]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPCellID1 register
//
//*************************************************************************************************
#define UDMA_DMAPCELLID1_CID1_S   0U
#define UDMA_DMAPCELLID1_CID1_M   0xFFU   // DMA PrimeCell ID Register [15:8]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPCellID2 register
//
//*************************************************************************************************
#define UDMA_DMAPCELLID2_CID2_S   0U
#define UDMA_DMAPCELLID2_CID2_M   0xFFU   // DMA PrimeCell ID Register [23:16]

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMAPCellID3 register
//
//*************************************************************************************************
#define UDMA_DMAPCELLID3_CID3_S   0U
#define UDMA_DMAPCELLID3_CID3_M   0xFFU   // DMA PrimeCell ID Register [31:24]



#endif
