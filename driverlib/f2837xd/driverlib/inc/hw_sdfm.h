//###########################################################################
//
// FILE:    hw_sdfm.h
//
// TITLE:   Definitions for the SDFM registers.
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

#ifndef HW_SDFM_H
#define HW_SDFM_H

//*************************************************************************************************
//
// The following are defines for the SDFM register offsets
//
//*************************************************************************************************
#define SDFM_O_SDIFLG       0x0U    // Interrupt Flag Register
#define SDFM_O_SDIFLGCLR    0x2U    // Interrupt Flag Clear Register
#define SDFM_O_SDCTL        0x4U    // SD Control Register
#define SDFM_O_SDMFILEN     0x6U    // SD Master Filter Enable
#define SDFM_O_SDCTLPARM1   0x10U   // Control Parameter Register for Ch1
#define SDFM_O_SDDFPARM1    0x11U   // Data Filter Parameter Register for Ch1
#define SDFM_O_SDDPARM1     0x12U   // Integer Parameter Register for Ch1
#define SDFM_O_SDCMPH1      0x13U   // High-level Threshold Register for Ch1
#define SDFM_O_SDCMPL1      0x14U   // Low-level Threshold Register for Ch1
#define SDFM_O_SDCPARM1     0x15U   // Comparator Parameter Register for Ch1
#define SDFM_O_SDDATA1      0x16U   // Filter Data Register (16 or 32bit) for Ch1
#define SDFM_O_SDCTLPARM2   0x20U   // Control Parameter Register for Ch2
#define SDFM_O_SDDFPARM2    0x21U   // Data Filter Parameter Register for Ch2
#define SDFM_O_SDDPARM2     0x22U   // Integer Parameter Register for Ch2
#define SDFM_O_SDCMPH2      0x23U   // High-level Threshold Register for Ch2
#define SDFM_O_SDCMPL2      0x24U   // Low-level Threshold Register for Ch2
#define SDFM_O_SDCPARM2     0x25U   // Comparator Parameter Register for Ch2
#define SDFM_O_SDDATA2      0x26U   // Filter Data Register (16 or 32bit) for Ch2
#define SDFM_O_SDCTLPARM3   0x30U   // Control Parameter Register for Ch3
#define SDFM_O_SDDFPARM3    0x31U   // Data Filter Parameter Register for Ch3
#define SDFM_O_SDDPARM3     0x32U   // Integer Parameter Register for Ch3
#define SDFM_O_SDCMPH3      0x33U   // High-level Threshold Register for Ch3
#define SDFM_O_SDCMPL3      0x34U   // Low-level Threshold Register for Ch3
#define SDFM_O_SDCPARM3     0x35U   // Comparator Parameter Register for Ch3
#define SDFM_O_SDDATA3      0x36U   // Filter Data Register (16 or 32bit) for Ch3
#define SDFM_O_SDCTLPARM4   0x40U   // Control Parameter Register for Ch4
#define SDFM_O_SDDFPARM4    0x41U   // Data Filter Parameter Register for Ch4
#define SDFM_O_SDDPARM4     0x42U   // Integer Parameter Register for Ch4
#define SDFM_O_SDCMPH4      0x43U   // High-level Threshold Register for Ch4
#define SDFM_O_SDCMPL4      0x44U   // Low-level Threshold Register for Ch4
#define SDFM_O_SDCPARM4     0x45U   // Comparator Parameter Register for Ch4
#define SDFM_O_SDDATA4      0x46U   // Filter Data Register (16 or 32bit) for Ch4


//*************************************************************************************************
//
// The following are defines for the bit fields in the SDIFLG register
//
//*************************************************************************************************
#define SDFM_SDIFLG_IFH1   0x1U          // High-level Interrupt flag Filter 1
#define SDFM_SDIFLG_IFL1   0x2U          // Low-Level Interrupt flag Filter 1
#define SDFM_SDIFLG_IFH2   0x4U          // High-level Interrupt flag Filter 2
#define SDFM_SDIFLG_IFL2   0x8U          // Low-Level Interrupt flag Filter 2
#define SDFM_SDIFLG_IFH3   0x10U         // High-level Interrupt flag Filter 3
#define SDFM_SDIFLG_IFL3   0x20U         // Low-Level Interrupt flag Filter 3
#define SDFM_SDIFLG_IFH4   0x40U         // High-level Interrupt flag Filter 4
#define SDFM_SDIFLG_IFL4   0x80U         // Low-Level Interrupt flag Filter 4
#define SDFM_SDIFLG_MF1    0x100U        // Modulator Failure for Filter 1
#define SDFM_SDIFLG_MF2    0x200U        // Modulator Failure for Filter 2
#define SDFM_SDIFLG_MF3    0x400U        // Modulator Failure for Filter 3
#define SDFM_SDIFLG_MF4    0x800U        // Modulator Failure for Filter 4
#define SDFM_SDIFLG_AF1    0x1000U       // Acknowledge flag for Filter 1
#define SDFM_SDIFLG_AF2    0x2000U       // Acknowledge flag for Filter 2
#define SDFM_SDIFLG_AF3    0x4000U       // Acknowledge flag for Filter 3
#define SDFM_SDIFLG_AF4    0x8000U       // Acknowledge flag for Filter 4
#define SDFM_SDIFLG_MIF    0x80000000U   // Master Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDIFLGCLR register
//
//*************************************************************************************************
#define SDFM_SDIFLGCLR_IFH1   0x1U          // High-level Interrupt flag Filter 1
#define SDFM_SDIFLGCLR_IFL1   0x2U          // Low-Level Interrupt flag Filter 1
#define SDFM_SDIFLGCLR_IFH2   0x4U          // High-level Interrupt flag Filter 2
#define SDFM_SDIFLGCLR_IFL2   0x8U          // Low-Level Interrupt flag Filter 2
#define SDFM_SDIFLGCLR_IFH3   0x10U         // High-level Interrupt flag Filter 3
#define SDFM_SDIFLGCLR_IFL3   0x20U         // Low-Level Interrupt flag Filter 3
#define SDFM_SDIFLGCLR_IFH4   0x40U         // High-level Interrupt flag Filter 4
#define SDFM_SDIFLGCLR_IFL4   0x80U         // Low-Level Interrupt flag Filter 4
#define SDFM_SDIFLGCLR_MF1    0x100U        // Modulator Failure for Filter 1
#define SDFM_SDIFLGCLR_MF2    0x200U        // Modulator Failure for Filter 2
#define SDFM_SDIFLGCLR_MF3    0x400U        // Modulator Failure for Filter 3
#define SDFM_SDIFLGCLR_MF4    0x800U        // Modulator Failure for Filter 4
#define SDFM_SDIFLGCLR_AF1    0x1000U       // Acknowledge flag for Filter 1
#define SDFM_SDIFLGCLR_AF2    0x2000U       // Acknowledge flag for Filter 2
#define SDFM_SDIFLGCLR_AF3    0x4000U       // Acknowledge flag for Filter 3
#define SDFM_SDIFLGCLR_AF4    0x8000U       // Acknowledge flag for Filter 4
#define SDFM_SDIFLGCLR_MIF    0x80000000U   // Master Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCTL register
//
//*************************************************************************************************
#define SDFM_SDCTL_MIE   0x2000U   // Master Interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDMFILEN register
//
//*************************************************************************************************
#define SDFM_SDMFILEN_MFE   0x800U   // Master Filter Enable.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM1 register
//
//*************************************************************************************************
#define SDFM_SDCTLPARM1_MOD_S   0U
#define SDFM_SDCTLPARM1_MOD_M   0x3U   // Delta-Sigma Modulator mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM1 register
//
//*************************************************************************************************
#define SDFM_SDDFPARM1_DOSR_S     0U
#define SDFM_SDDFPARM1_DOSR_M     0xFFU     // Data Filter Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM1_FEN        0x100U    // Filter Enable
#define SDFM_SDDFPARM1_AE         0x200U    // Ack Enable
#define SDFM_SDDFPARM1_SST_S      10U
#define SDFM_SDDFPARM1_SST_M      0xC00U    // Data Filter Structure (DataFast/1/2/3)
#define SDFM_SDDFPARM1_SDSYNCEN   0x1000U   // Data FILTER Reset Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDPARM1 register
//
//*************************************************************************************************
#define SDFM_SDDPARM1_DR     0x400U    // Data Representation (0/1 = 16/32b 2's complement)
#define SDFM_SDDPARM1_SH_S   11U
#define SDFM_SDDPARM1_SH_M   0xF800U   // Shift Control (# bits to shift in 16b mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPH1 register
//
//*************************************************************************************************
#define SDFM_SDCMPH1_HLT_S   0U
#define SDFM_SDCMPH1_HLT_M   0x7FFFU   // High-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPL1 register
//
//*************************************************************************************************
#define SDFM_SDCMPL1_LLT_S   0U
#define SDFM_SDCMPL1_LLT_M   0x7FFFU   // Low-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCPARM1 register
//
//*************************************************************************************************
#define SDFM_SDCPARM1_COSR_S      0U
#define SDFM_SDCPARM1_COSR_M      0x1FU    // Comparator Oversample Ratio = COSR + 1
#define SDFM_SDCPARM1_IEH         0x20U    // High-level interrupt enable
#define SDFM_SDCPARM1_IEL         0x40U    // Low-level interrupt enable
#define SDFM_SDCPARM1_CS1_CS0_S   7U
#define SDFM_SDCPARM1_CS1_CS0_M   0x180U   // Comparator filter structure
                                           // (Sincfast/Sinc1/Sinc2/Sinc3
#define SDFM_SDCPARM1_MFIE        0x200U   // Modulator Failure Interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDATA1 register
//
//*************************************************************************************************
#define SDFM_SDDATA1_DATA16_S     0U
#define SDFM_SDDATA1_DATA16_M     0xFFFFU       // 16-bit Data in 16b mode, Lo-order 16b in 32b
                                                // mode
#define SDFM_SDDATA1_DATA32HI_S   16U
#define SDFM_SDDATA1_DATA32HI_M   0xFFFF0000U   // Hi-order 16b in 32b mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM2 register
//
//*************************************************************************************************
#define SDFM_SDCTLPARM2_MOD_S   0U
#define SDFM_SDCTLPARM2_MOD_M   0x3U   // Delta-Sigma Modulator mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM2 register
//
//*************************************************************************************************
#define SDFM_SDDFPARM2_DOSR_S     0U
#define SDFM_SDDFPARM2_DOSR_M     0xFFU     // Data Filter Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM2_FEN        0x100U    // Filter Enable
#define SDFM_SDDFPARM2_AE         0x200U    // Ack Enable
#define SDFM_SDDFPARM2_SST_S      10U
#define SDFM_SDDFPARM2_SST_M      0xC00U    // Data Filter Structure (SincFast/1/2/3)
#define SDFM_SDDFPARM2_SDSYNCEN   0x1000U   // Data FILTER Reset Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDPARM2 register
//
//*************************************************************************************************
#define SDFM_SDDPARM2_DR     0x400U    // Data Representation (0/1 = 16/32b 2's complement)
#define SDFM_SDDPARM2_SH_S   11U
#define SDFM_SDDPARM2_SH_M   0xF800U   // Shift Control (# bits to shift in 16b mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPH2 register
//
//*************************************************************************************************
#define SDFM_SDCMPH2_HLT_S   0U
#define SDFM_SDCMPH2_HLT_M   0x7FFFU   // High-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPL2 register
//
//*************************************************************************************************
#define SDFM_SDCMPL2_LLT_S   0U
#define SDFM_SDCMPL2_LLT_M   0x7FFFU   // Low-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCPARM2 register
//
//*************************************************************************************************
#define SDFM_SDCPARM2_COSR_S      0U
#define SDFM_SDCPARM2_COSR_M      0x1FU    // Comparator Oversample Ratio = COSR + 1
#define SDFM_SDCPARM2_IEH         0x20U    // High-level interrupt enable
#define SDFM_SDCPARM2_IEL         0x40U    // Low-level interrupt enable
#define SDFM_SDCPARM2_CS1_CS0_S   7U
#define SDFM_SDCPARM2_CS1_CS0_M   0x180U   // Comparator filter structure
                                           // (Sincfast/Sinc1/Sinc2/Sinc3
#define SDFM_SDCPARM2_MFIE        0x200U   // Modulator Failure Interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDATA2 register
//
//*************************************************************************************************
#define SDFM_SDDATA2_DATA16_S     0U
#define SDFM_SDDATA2_DATA16_M     0xFFFFU       // 16-bit Data in 16b mode, Lo-order 16b in 32b
                                                // mode
#define SDFM_SDDATA2_DATA32HI_S   16U
#define SDFM_SDDATA2_DATA32HI_M   0xFFFF0000U   // Hi-order 16b in 32b mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM3 register
//
//*************************************************************************************************
#define SDFM_SDCTLPARM3_MOD_S   0U
#define SDFM_SDCTLPARM3_MOD_M   0x3U   // Delta-Sigma Modulator mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM3 register
//
//*************************************************************************************************
#define SDFM_SDDFPARM3_DOSR_S     0U
#define SDFM_SDDFPARM3_DOSR_M     0xFFU     // Data Filter Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM3_FEN        0x100U    // Filter Enable
#define SDFM_SDDFPARM3_AE         0x200U    // Ack Enable
#define SDFM_SDDFPARM3_SST_S      10U
#define SDFM_SDDFPARM3_SST_M      0xC00U    // Data filter structure (SincFast/1/2/3)
#define SDFM_SDDFPARM3_SDSYNCEN   0x1000U   // Data FILTER Reset Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDPARM3 register
//
//*************************************************************************************************
#define SDFM_SDDPARM3_DR     0x400U    // Data Representation (0/1 = 16/32b 2's complement)
#define SDFM_SDDPARM3_SH_S   11U
#define SDFM_SDDPARM3_SH_M   0xF800U   // Shift Control (# bits to shift in 16b mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPH3 register
//
//*************************************************************************************************
#define SDFM_SDCMPH3_HLT_S   0U
#define SDFM_SDCMPH3_HLT_M   0x7FFFU   // High-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPL3 register
//
//*************************************************************************************************
#define SDFM_SDCMPL3_LLT_S   0U
#define SDFM_SDCMPL3_LLT_M   0x7FFFU   // Low-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCPARM3 register
//
//*************************************************************************************************
#define SDFM_SDCPARM3_COSR_S      0U
#define SDFM_SDCPARM3_COSR_M      0x1FU    // Comparator Oversample Ratio = COSR + 1
#define SDFM_SDCPARM3_IEH         0x20U    // High-level interrupt enable
#define SDFM_SDCPARM3_IEL         0x40U    // Low-level interrupt enable
#define SDFM_SDCPARM3_CS1_CS0_S   7U
#define SDFM_SDCPARM3_CS1_CS0_M   0x180U   // Comparator filter structure
                                           // (Sincfast/Sinc1/Sinc2/Sinc3
#define SDFM_SDCPARM3_MFIE        0x200U   // Modulator Failure Interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDATA3 register
//
//*************************************************************************************************
#define SDFM_SDDATA3_DATA16_S     0U
#define SDFM_SDDATA3_DATA16_M     0xFFFFU       // 16-bit Data in 16b mode, Lo-order 16b in 32b
                                                // mode
#define SDFM_SDDATA3_DATA32HI_S   16U
#define SDFM_SDDATA3_DATA32HI_M   0xFFFF0000U   // Hi-order 16b in 32b mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCTLPARM4 register
//
//*************************************************************************************************
#define SDFM_SDCTLPARM4_MOD_S   0U
#define SDFM_SDCTLPARM4_MOD_M   0x3U   // Delta-Sigma Modulator mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDFPARM4 register
//
//*************************************************************************************************
#define SDFM_SDDFPARM4_DOSR_S     0U
#define SDFM_SDDFPARM4_DOSR_M     0xFFU     // SINC Filter Oversample Ratio= DOSR+1
#define SDFM_SDDFPARM4_FEN        0x100U    // Filter Enable
#define SDFM_SDDFPARM4_AE         0x200U    // Ack Enable
#define SDFM_SDDFPARM4_SST_S      10U
#define SDFM_SDDFPARM4_SST_M      0xC00U    // Data filter structure (SincFast/1/2/3)
#define SDFM_SDDFPARM4_SDSYNCEN   0x1000U   // SINC FILTER Reset Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDPARM4 register
//
//*************************************************************************************************
#define SDFM_SDDPARM4_DR     0x400U    // Data Representation (0/1 = 16/32b 2's complement)
#define SDFM_SDDPARM4_SH_S   11U
#define SDFM_SDDPARM4_SH_M   0xF800U   // Shift Control (# bits to shift in 16b mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPH4 register
//
//*************************************************************************************************
#define SDFM_SDCMPH4_HLT_S   0U
#define SDFM_SDCMPH4_HLT_M   0x7FFFU   // High-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCMPL4 register
//
//*************************************************************************************************
#define SDFM_SDCMPL4_LLT_S   0U
#define SDFM_SDCMPL4_LLT_M   0x7FFFU   // Low-level threshold for the comparator filter output.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDCPARM4 register
//
//*************************************************************************************************
#define SDFM_SDCPARM4_COSR_S      0U
#define SDFM_SDCPARM4_COSR_M      0x1FU    // Comparator Oversample Ratio = COSR + 1
#define SDFM_SDCPARM4_IEH         0x20U    // High-level interrupt enable
#define SDFM_SDCPARM4_IEL         0x40U    // Low-level interrupt enable
#define SDFM_SDCPARM4_CS1_CS0_S   7U
#define SDFM_SDCPARM4_CS1_CS0_M   0x180U   // Comparator filter structure
                                           // (Sincfast/Sinc1/Sinc2/Sinc3
#define SDFM_SDCPARM4_MFIE        0x200U   // Modulator Failure Interrupt enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDDATA4 register
//
//*************************************************************************************************
#define SDFM_SDDATA4_DATA16_S     0U
#define SDFM_SDDATA4_DATA16_M     0xFFFFU       // 16-bit Data in 16b mode, Lo-order 16b in 32b
                                                // mode
#define SDFM_SDDATA4_DATA32HI_S   16U
#define SDFM_SDDATA4_DATA32HI_M   0xFFFF0000U   // Hi-order 16b in 32b mode



#endif
