//###########################################################################
//
// FILE:    hw_aes.h
//
// TITLE:   Definitions for the AES registers.
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

#ifndef HW_AES_H
#define HW_AES_H

//*************************************************************************************************
//
// The following are defines for the AES register offsets
//
//*************************************************************************************************
#define AES_O_KEY2_6          0x0U    // XTS Second Key or CBC-MAC Third Key
#define AES_O_KEY2_7          0x4U    // XTS Second Key or CBC-MAC Third Key
#define AES_O_KEY2_4          0x8U    // XTS/CCM Second Key or CBC-MAC Third Key
#define AES_O_KEY2_5          0xCU    // XTS Second Key or CBC-MAC Third Key
#define AES_O_KEY2_2          0x10U   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
#define AES_O_KEY2_3          0x14U   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
#define AES_O_KEY2_0          0x18U   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
#define AES_O_KEY2_1          0x1CU   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
#define AES_O_KEY1_6          0x20U   // Key
#define AES_O_KEY1_7          0x24U   // Key
#define AES_O_KEY1_4          0x28U   // Key
#define AES_O_KEY1_5          0x2CU   // Key
#define AES_O_KEY1_2          0x30U   // Key
#define AES_O_KEY1_3          0x34U   // Key
#define AES_O_KEY1_0          0x38U   // Key
#define AES_O_KEY1_1          0x3CU   // Key
#define AES_O_IV_IN_OUT_0     0x40U   // Initialization Vector 0
#define AES_O_IV_IN_OUT_1     0x44U   // Initialization Vector 1
#define AES_O_IV_IN_OUT_2     0x48U   // Initialization Vector 2
#define AES_O_IV_IN_OUT_3     0x4CU   // Initialization Vector 3
#define AES_O_CTRL            0x50U   // Input/Output Buffer Control and Mode Selection
#define AES_O_C_LENGTH_0      0x54U   // Crypto Data Length 0
#define AES_O_C_LENGTH_1      0x58U   // Crypto Data Length 1
#define AES_O_AUTH_LENGTH     0x5CU   // AAD Data Length
#define AES_O_DATA_IN_OUT_0   0x60U   // Data Word 0
#define AES_O_DATA_IN_OUT_1   0x64U   // Data Word 1
#define AES_O_DATA_IN_OUT_2   0x68U   // Data Word 2
#define AES_O_DATA_IN_OUT_3   0x6CU   // Data Word 3
#define AES_O_TAG_OUT_0       0x70U   // Hash Result 0
#define AES_O_TAG_OUT_1       0x74U   // Hash Result 1
#define AES_O_TAG_OUT_2       0x78U   // Hash Result 2
#define AES_O_TAG_OUT_3       0x7CU   // Hash Result 3
#define AES_O_REV             0x80U   // Module Revision Number
#define AES_O_SYSCONFIG       0x84U   // System Configuration
#define AES_O_SYSSTATUS       0x88U   // Reset Status
#define AES_O_IRQSTATUS       0x8CU   // Interrupt Status
#define AES_O_IRQENABLE       0x90U   // Interrupt Enable
#define AES_O_DIRTY_BITS      0x94U   // Accessed / Dirty Bits


//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_CTRL register
//
//*************************************************************************************************
#define AES_CTRL_OUTPUT_READY   0x1U          // Output Ready Status
#define AES_CTRL_INPUT_READY    0x2U          // Input Ready Status
#define AES_CTRL_DIRECTION      0x4U          // Encryption/Decryption Selection
#define AES_CTRL_KEY_SIZE_S     3U
#define AES_CTRL_KEY_SIZE_M     0x18U         // Key Size
#define AES_CTRL_MODE           0x20U         // ECB/CBC Mode
#define AES_CTRL_CTR            0x40U         // Counter Mode
#define AES_CTRL_CTR_WIDTH_S    7U
#define AES_CTRL_CTR_WIDTH_M    0x180U        // AES-CTR Mode Counter Width
#define AES_CTRL_ICM            0x200U        // AES Integer Counter Mode (ICM) Enable
#define AES_CTRL_CFB            0x400U        // Full block AES cipher feedback mode (CFB128)
                                              // Enable
#define AES_CTRL_XTS_S          11U
#define AES_CTRL_XTS_M          0x1800U       // AES-XTS Operation Enable
#define AES_CTRL_F8             0x2000U       // AES f8 Mode Enable
#define AES_CTRL_F9             0x4000U       // AES f9 Mode Enable
#define AES_CTRL_CBCMAC         0x8000U       // AES-CBC MAC Enable
#define AES_CTRL_GCM_S          16U
#define AES_CTRL_GCM_M          0x30000U      // AES-GCM Mode Enable
#define AES_CTRL_CCM            0x40000U      // AES-CCM Mode Enable
#define AES_CTRL_CCM_L_S        19U
#define AES_CTRL_CCM_L_M        0x380000U     // Width of the length field for CCM operations
#define AES_CTRL_CCM_M_S        22U
#define AES_CTRL_CCM_M_M        0x1C00000U    // Length of the authentication field for CCM
                                              // operations
#define AES_CTRL_SAVE_CONTEXT   0x20000000U   // TAG or Result IV Save
#define AES_CTRL_SVCTXTRDY      0x40000000U   // AES TAG/IV Block(s) Ready
#define AES_CTRL_CTXTRDY        0x80000000U   // Context Data Registers Ready

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_SYSCONFIG register
//
//*************************************************************************************************
#define AES_SYSCONFIG_AUTOIDLE                      0x1U     // autoidle
#define AES_SYSCONFIG_SOFTRESET                     0x2U     // Soft Reset
#define AES_SYSCONFIG_SIDLE_S                       2U
#define AES_SYSCONFIG_SIDLE_M                       0xCU     // Slave Idle Mode
#define AES_SYSCONFIG_DMA_REQ_DATA_IN_EN            0x20U    // DMA Request Data In Enable
#define AES_SYSCONFIG_DMA_REQ_DATA_OUT_EN           0x40U    // DMA Request Data Out Enable
#define AES_SYSCONFIG_DMA_REQ_CONTEXT_IN_EN         0x80U    // DMA Request Context In Enable
#define AES_SYSCONFIG_DMA_REQ_CONTEXT_OUT_EN        0x100U   // DMA Request Context Out Enable
#define AES_SYSCONFIG_MAP_CONTEXT_OUT_ON_DATA_OUT   0x200U   // Map Context Out on Data Out Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_SYSSTATUS register
//
//*************************************************************************************************
#define AES_SYSSTATUS_RESETDONE   0x1U   // Reset Done

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_IRQSTATUS register
//
//*************************************************************************************************
#define AES_IRQSTATUS_CONTEXT_IN    0x1U   // Context In Interrupt Status
#define AES_IRQSTATUS_DATA_IN       0x2U   // Data In Interrupt Status
#define AES_IRQSTATUS_DATA_OUT      0x4U   // Data Out Interrupt Status
#define AES_IRQSTATUS_CONTEXT_OUT   0x8U   // Context Output Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_IRQENABLE register
//
//*************************************************************************************************
#define AES_IRQENABLE_CONTEXT_IN    0x1U   // Context In Interrupt Enable
#define AES_IRQENABLE_DATA_IN       0x2U   // Data In Interrupt Enable
#define AES_IRQENABLE_DATA_OUT      0x4U   // Data Out Interrupt Enable
#define AES_IRQENABLE_CONTEXT_OUT   0x8U   // Context Out Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_DIRTY_BITS register
//
//*************************************************************************************************
#define AES_DIRTY_BITS_S_ACCESS   0x1U   // AES Access Bit
#define AES_DIRTY_BITS_S_DIRTY    0x2U   // AES Dirty Bit



#endif
