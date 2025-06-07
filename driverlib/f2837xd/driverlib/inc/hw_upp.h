//###########################################################################
//
// FILE:    hw_upp.h
//
// TITLE:   Definitions for the UPP registers.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef HW_UPP_H
#define HW_UPP_H

//*************************************************************************************************
//
// The following are defines for the UPP register offsets
//
//*************************************************************************************************
#define UPP_O_PID        0x0U    // Peripheral ID Register
#define UPP_O_PERCTL     0x2U    // Peripheral Control Register
#define UPP_O_CHCTL      0x8U    // General Control Register
#define UPP_O_IFCFG      0xAU    // Interface Configuration Register
#define UPP_O_IFIVAL     0xCU    // Interface Idle Value Register
#define UPP_O_THCFG      0xEU    // Threshold Configuration Register
#define UPP_O_RAWINTST   0x10U   // Raw Interrupt Status Register
#define UPP_O_ENINTST    0x12U   // Enable Interrupt Status Register
#define UPP_O_INTENSET   0x14U   // Interrupt Enable Set Register
#define UPP_O_INTENCLR   0x16U   // Interrupt Enable Clear Register
#define UPP_O_CHIDESC0   0x20U   // DMA Channel I Descriptor 0 Register
#define UPP_O_CHIDESC1   0x22U   // DMA Channel I Descriptor 1 Register
#define UPP_O_CHIDESC2   0x24U   // DMA Channel I Descriptor 2 Register
#define UPP_O_CHIST0     0x28U   // DMA Channel I Status 0 Register
#define UPP_O_CHIST1     0x2AU   // DMA Channel I Status 1 Register
#define UPP_O_CHIST2     0x2CU   // DMA Channel I Status 2 Register
#define UPP_O_CHQDESC0   0x30U   // DMA Channel Q Descriptor 0 Register
#define UPP_O_CHQDESC1   0x32U   // DMA Channel Q Descriptor 1 Register
#define UPP_O_CHQDESC2   0x34U   // DMA Channel Q Descriptor 2 Register
#define UPP_O_CHQST0     0x38U   // DMA Channel Q Status 0 Register
#define UPP_O_CHQST1     0x3AU   // DMA Channel Q Status 1 Register
#define UPP_O_CHQST2     0x3CU   // DMA Channel Q Status 2 Register
#define UPP_O_GINTEN     0x40U   // Global Peripheral Interrupt Enable Register
#define UPP_O_GINTFLG    0x42U   // Global Peripheral Interrupt Flag Register
#define UPP_O_GINTCLR    0x44U   // Global Peripheral Interrupt Clear Register
#define UPP_O_DLYCTL     0x46U   // IO clock data skew control Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the PERCTL register
//
//*************************************************************************************************
#define UPP_PERCTL_FREE      0x1U    // Emulation control.
#define UPP_PERCTL_SOFT      0x2U    // Emulation control.
#define UPP_PERCTL_RTEMU     0x4U    // Realtime emulation control.
#define UPP_PERCTL_PEREN     0x8U    // Peripheral Enable
#define UPP_PERCTL_SOFTRST   0x10U   // Software Reset
#define UPP_PERCTL_DMAST     0x80U   // DMA Burst transaction status

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHCTL register
//
//*************************************************************************************************
#define UPP_CHCTL_MODE_S     0U
#define UPP_CHCTL_MODE_M     0x3U       // Operating mode
#define UPP_CHCTL_SDRTXILA   0x8U       // SDR TX Interleve mode
#define UPP_CHCTL_DEMUXA     0x10U      // DDR de-multiplexing mode
#define UPP_CHCTL_DRA        0x10000U   // Data rate

//*************************************************************************************************
//
// The following are defines for the bit fields in the IFCFG register
//
//*************************************************************************************************
#define UPP_IFCFG_STARTPOLA   0x1U      // Polarity of START(SELECT) signal
#define UPP_IFCFG_ENAPOLA     0x2U      // Polarity of ENABLE(WRITE) signal
#define UPP_IFCFG_WAITPOLA    0x4U      // Polarity of WAIT signal.
#define UPP_IFCFG_STARTA      0x8U      // Enable Usage of START (SELECT) signal
#define UPP_IFCFG_ENAA        0x10U     // Enable Usage of ENABLE (WRITE) signal
#define UPP_IFCFG_WAITA       0x20U     // Enable Usage of WAIT signal
#define UPP_IFCFG_CLKDIVA_S   8U
#define UPP_IFCFG_CLKDIVA_M   0xF00U    // Clock divider for tx mode
#define UPP_IFCFG_CLKINVA     0x1000U   // Clock inversion
#define UPP_IFCFG_TRISENA     0x2000U   // Pin Tri-state Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the IFIVAL register
//
//*************************************************************************************************
#define UPP_IFIVAL_VALA_S   0U
#define UPP_IFIVAL_VALA_M   0x1FFU   // Idle Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the THCFG register
//
//*************************************************************************************************
#define UPP_THCFG_RDSIZEI_S   0U
#define UPP_THCFG_RDSIZEI_M   0x3U       // DMA Read Threshold for DMA Channel I
#define UPP_THCFG_RDSIZEQ_S   8U
#define UPP_THCFG_RDSIZEQ_M   0x300U     // DMA Read Threshold for DMA Channel Q
#define UPP_THCFG_TXSIZEA_S   16U
#define UPP_THCFG_TXSIZEA_M   0x30000U   // I/O Transmit Threshold Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAWINTST register
//
//*************************************************************************************************
#define UPP_RAWINTST_DPEI   0x1U      // Interrupt raw status for DMA programming error
#define UPP_RAWINTST_UOEI   0x2U      // Interrupt raw status for DMA under-run or over-run
#define UPP_RAWINTST_EOWI   0x8U      // Interrupt raw status for end-of window condition
#define UPP_RAWINTST_EOLI   0x10U     // Interrupt raw status for end-of-line condition
#define UPP_RAWINTST_DPEQ   0x100U    // Interrupt raw status for DMA programming error
#define UPP_RAWINTST_UOEQ   0x200U    // Interrupt raw status for DMA under-run or over-run
#define UPP_RAWINTST_EOWQ   0x800U    // Interrupt raw status for end-of window condition
#define UPP_RAWINTST_EOLQ   0x1000U   // Interrupt raw status for end-of-line condition

//*************************************************************************************************
//
// The following are defines for the bit fields in the ENINTST register
//
//*************************************************************************************************
#define UPP_ENINTST_DPEI   0x1U      // Interrupt enable status for DMA programming error
#define UPP_ENINTST_UOEI   0x2U      // Interrupt enable status for DMA under-run or over-run
#define UPP_ENINTST_EOWI   0x8U      // Interrupt enable status for end-of window condition
#define UPP_ENINTST_EOLI   0x10U     // Interrupt enable status for end-of-line condition
#define UPP_ENINTST_DPEQ   0x100U    // Interrupt enable status for DMA programming error
#define UPP_ENINTST_UOEQ   0x200U    // Interrupt enable status for DMA under-run or over-run
#define UPP_ENINTST_EOWQ   0x800U    // Interrupt enable status for end-of window condition
#define UPP_ENINTST_EOLQ   0x1000U   // Interrupt enable status for end-of-line condition

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTENSET register
//
//*************************************************************************************************
#define UPP_INTENSET_DPEI   0x1U      // Interrupt enable for DMA programming error
#define UPP_INTENSET_UOEI   0x2U      // Interrupt enable for DMA under-run or over-run
#define UPP_INTENSET_EOWI   0x8U      // Interrupt enable for end-of window condition
#define UPP_INTENSET_EOLI   0x10U     // Interrupt enable for end-of-line condition
#define UPP_INTENSET_DPEQ   0x100U    // Interrupt enable for DMA programming error
#define UPP_INTENSET_UOEQ   0x200U    // Interrupt enable for DMA under-run or over-run
#define UPP_INTENSET_EOWQ   0x800U    // Interrupt enable for end-of window condition
#define UPP_INTENSET_EOLQ   0x1000U   // Interrupt enable for end-of-line condition

//*************************************************************************************************
//
// The following are defines for the bit fields in the INTENCLR register
//
//*************************************************************************************************
#define UPP_INTENCLR_DPEI   0x1U      // Interrupt clear for DMA programming error
#define UPP_INTENCLR_UOEI   0x2U      // Interrupt clear for DMA under-run or over-run
#define UPP_INTENCLR_EOWI   0x8U      // Interrupt clear for end-of window condition
#define UPP_INTENCLR_EOLI   0x10U     // Interrupt clear for end-of-line condition
#define UPP_INTENCLR_DPEQ   0x100U    // Interrupt clear for DMA programming error
#define UPP_INTENCLR_UOEQ   0x200U    // Interrupt clear for DMA under-run or over-run
#define UPP_INTENCLR_EOWQ   0x800U    // Interrupt clear for end-of window condition
#define UPP_INTENCLR_EOLQ   0x1000U   // Interrupt clear for end-of-line condition

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHIDESC1 register
//
//*************************************************************************************************
#define UPP_CHIDESC1_BCNT_S   0U
#define UPP_CHIDESC1_BCNT_M   0xFFFFU       // Number of bytes in a line for DMA Channel I
                                            // transfer.
#define UPP_CHIDESC1_LCNT_S   16U
#define UPP_CHIDESC1_LCNT_M   0xFFFF0000U   // Number of lines in a window for DMA Channel I
                                            // transfer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHIDESC2 register
//
//*************************************************************************************************
#define UPP_CHIDESC2_LOFFSET_S   0U
#define UPP_CHIDESC2_LOFFSET_M   0xFFFFU   // Current start address to next start address offset.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHIST1 register
//
//*************************************************************************************************
#define UPP_CHIST1_BCNT_S   0U
#define UPP_CHIST1_BCNT_M   0xFFFFU       // Current byte number.
#define UPP_CHIST1_LCNT_S   16U
#define UPP_CHIST1_LCNT_M   0xFFFF0000U   // Current line number.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHIST2 register
//
//*************************************************************************************************
#define UPP_CHIST2_ACT    0x1U    // Status of DMA descriptor.
#define UPP_CHIST2_PEND   0x2U    // Status of DMA.
#define UPP_CHIST2_WM_S   4U
#define UPP_CHIST2_WM_M   0xF0U   // Watermark for FIFO block count for DMA Channel I tranfer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHQDESC1 register
//
//*************************************************************************************************
#define UPP_CHQDESC1_BCNT_S   0U
#define UPP_CHQDESC1_BCNT_M   0xFFFFU       // Number of bytes in a line for DMA Channel Q
                                            // transfer.
#define UPP_CHQDESC1_LCNT_S   16U
#define UPP_CHQDESC1_LCNT_M   0xFFFF0000U   // Number of lines in a window for DMA Channel Q
                                            // transfer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHQDESC2 register
//
//*************************************************************************************************
#define UPP_CHQDESC2_LOFFSET_S   0U
#define UPP_CHQDESC2_LOFFSET_M   0xFFFFU   // Current start address to next start address offset.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHQST1 register
//
//*************************************************************************************************
#define UPP_CHQST1_BCNT_S   0U
#define UPP_CHQST1_BCNT_M   0xFFFFU       // Current byte number.
#define UPP_CHQST1_LCNT_S   16U
#define UPP_CHQST1_LCNT_M   0xFFFF0000U   // Current line number.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CHQST2 register
//
//*************************************************************************************************
#define UPP_CHQST2_ACT    0x1U    // Status of DMA descriptor.
#define UPP_CHQST2_PEND   0x2U    // Status of DMA.
#define UPP_CHQST2_WM_S   4U
#define UPP_CHQST2_WM_M   0xF0U   // Watermark for FIFO block count for DMA Channel Q tranfer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTEN register
//
//*************************************************************************************************
#define UPP_GINTEN_GINTEN   0x1U   // Global Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTFLG register
//
//*************************************************************************************************
#define UPP_GINTFLG_GINTFLG   0x1U   // Global Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the GINTCLR register
//
//*************************************************************************************************
#define UPP_GINTCLR_GINTCLR   0x1U   // Global Interrupt Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the DLYCTL register
//
//*************************************************************************************************
#define UPP_DLYCTL_DLYDIS     0x1U   // IO dealy control disable.
#define UPP_DLYCTL_DLYCTL_S   1U
#define UPP_DLYCTL_DLYCTL_M   0x6U   // IO delay control.



#endif
