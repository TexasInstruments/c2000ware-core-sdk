//###########################################################################
//
// FILE:    f28p65x_aes.h
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

#ifndef F28P65X_AES_H
#define F28P65X_AES_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// AES Individual Register Bit Definitions:

struct AES_CTRL_BITS {                  // bits description
    Uint16 OUTPUT_READY:1;              // 0 Output Ready Status
    Uint16 INPUT_READY:1;               // 1 Input Ready Status
    Uint16 DIRECTION:1;                 // 2 Encryption/Decryption Selection
    Uint16 KEY_SIZE:2;                  // 4:3 Key Size
    Uint16 MODE:1;                      // 5 ECB/CBC Mode
    Uint16 CTR:1;                       // 6 Counter Mode
    Uint16 CTR_WIDTH:2;                 // 8:7 AES-CTR Mode Counter Width
    Uint16 ICM:1;                       // 9 AES Integer Counter Mode (ICM) Enable
    Uint16 CFB:1;                       // 10 Full block AES cipher feedback mode (CFB128) Enable
    Uint16 XTS:2;                       // 12:11 AES-XTS Operation Enable
    Uint16 F8:1;                        // 13 AES f8 Mode Enable
    Uint16 F9:1;                        // 14 AES f9 Mode Enable
    Uint16 CBCMAC:1;                    // 15 AES-CBC MAC Enable
    Uint16 GCM:2;                       // 17:16 AES-GCM Mode Enable
    Uint16 CCM:1;                       // 18 AES-CCM Mode Enable
    Uint16 CCM_L:3;                     // 21:19 Width of the length field for CCM operations
    Uint16 CCM_M:3;                     // 24:22 Length of the authentication field for CCM operations
    Uint16 rsvd1:4;                     // 28:25 Reserved
    Uint16 SAVE_CONTEXT:1;              // 29 TAG or Result IV Save
    Uint16 SVCTXTRDY:1;                 // 30 AES TAG/IV Block(s) Ready
    Uint16 CTXTRDY:1;                   // 31 Context Data Registers Ready
};

union AES_CTRL_REG {
    Uint32  all;
    struct  AES_CTRL_BITS  bit;
};

struct AES_SYSCONFIG_BITS {             // bits description
    Uint16 AUTOIDLE:1;                  // 0 autoidle
    Uint16 SOFTRESET:1;                 // 1 Soft Reset
    Uint16 SIDLE:2;                     // 3:2 Slave Idle Mode
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 DMA_REQ_DATA_IN_EN:1;        // 5 DMA Request Data In Enable
    Uint16 DMA_REQ_DATA_OUT_EN:1;       // 6 DMA Request Data Out Enable
    Uint16 DMA_REQ_CONTEXT_IN_EN:1;     // 7 DMA Request Context In Enable
    Uint16 DMA_REQ_CONTEXT_OUT_EN:1;    // 8 DMA Request Context Out Enable
    Uint16 MAP_CONTEXT_OUT_ON_DATA_OUT:1; // 9 Map Context Out on Data Out Enable
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 rsvd5:3;                     // 15:13 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union AES_SYSCONFIG_REG {
    Uint32  all;
    struct  AES_SYSCONFIG_BITS  bit;
};

struct AES_SYSSTATUS_BITS {             // bits description
    Uint16 RESETDONE:1;                 // 0 Reset Done
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AES_SYSSTATUS_REG {
    Uint32  all;
    struct  AES_SYSSTATUS_BITS  bit;
};

struct AES_IRQSTATUS_BITS {             // bits description
    Uint16 CONTEXT_IN:1;                // 0 Context In Interrupt Status
    Uint16 DATA_IN:1;                   // 1 Data In Interrupt Status
    Uint16 DATA_OUT:1;                  // 2 Data Out Interrupt Status
    Uint16 CONTEXT_OUT:1;               // 3 Context Output Interrupt Status
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AES_IRQSTATUS_REG {
    Uint32  all;
    struct  AES_IRQSTATUS_BITS  bit;
};

struct AES_IRQENABLE_BITS {             // bits description
    Uint16 CONTEXT_IN:1;                // 0 Context In Interrupt Enable
    Uint16 DATA_IN:1;                   // 1 Data In Interrupt Enable
    Uint16 DATA_OUT:1;                  // 2 Data Out Interrupt Enable
    Uint16 CONTEXT_OUT:1;               // 3 Context Out Interrupt Enable
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AES_IRQENABLE_REG {
    Uint32  all;
    struct  AES_IRQENABLE_BITS  bit;
};

struct AES_DIRTY_BITS_BITS {            // bits description
    Uint16 S_ACCESS:1;                  // 0 AES Access Bit
    Uint16 S_DIRTY:1;                   // 1 AES Dirty Bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union AES_DIRTY_BITS_REG {
    Uint32  all;
    struct  AES_DIRTY_BITS_BITS  bit;
};

struct AES_REGS {
    Uint32                                   AES_KEY2_6;                   // XTS Second Key or CBC-MAC Third Key
    Uint32                                   AES_KEY2_7;                   // XTS Second Key or CBC-MAC Third Key
    Uint32                                   AES_KEY2_4;                   // XTS/CCM Second Key or CBC-MAC Third Key
    Uint32                                   AES_KEY2_5;                   // XTS Second Key or CBC-MAC Third Key
    Uint32                                   AES_KEY2_2;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    Uint32                                   AES_KEY2_3;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    Uint32                                   AES_KEY2_0;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    Uint32                                   AES_KEY2_1;                   // XTS/CCM/CBC-MAC Second Key or Hash Key Input
    Uint32                                   AES_KEY1_6;                   // Key
    Uint32                                   AES_KEY1_7;                   // Key
    Uint32                                   AES_KEY1_4;                   // Key
    Uint32                                   AES_KEY1_5;                   // Key
    Uint32                                   AES_KEY1_2;                   // Key
    Uint32                                   AES_KEY1_3;                   // Key
    Uint32                                   AES_KEY1_0;                   // Key
    Uint32                                   AES_KEY1_1;                   // Key
    Uint32                                   AES_IV_IN_OUT_0;              // Initialization Vector 0
    Uint32                                   AES_IV_IN_OUT_1;              // Initialization Vector 1
    Uint32                                   AES_IV_IN_OUT_2;              // Initialization Vector 2
    Uint32                                   AES_IV_IN_OUT_3;              // Initialization Vector 3
    union   AES_CTRL_REG                     AES_CTRL;                     // Input/Output Buffer Control and Mode Selection
    Uint32                                   AES_C_LENGTH_0;               // Crypto Data Length 0
    Uint32                                   AES_C_LENGTH_1;               // Crypto Data Length 1
    Uint32                                   AES_AUTH_LENGTH;              // AAD Data Length
    Uint32                                   AES_DATA_IN_OUT_0;            // Data Word 0
    Uint32                                   AES_DATA_IN_OUT_1;            // Data Word 1
    Uint32                                   AES_DATA_IN_OUT_2;            // Data Word 2
    Uint32                                   AES_DATA_IN_OUT_3;            // Data Word 3
    Uint32                                   AES_TAG_OUT_0;                // Hash Result 0
    Uint32                                   AES_TAG_OUT_1;                // Hash Result 1
    Uint32                                   AES_TAG_OUT_2;                // Hash Result 2
    Uint32                                   AES_TAG_OUT_3;                // Hash Result 3
    Uint32                                   AES_REV;                      // Module Revision Number
    union   AES_SYSCONFIG_REG                AES_SYSCONFIG;                // System Configuration
    union   AES_SYSSTATUS_REG                AES_SYSSTATUS;                // Reset Status
    union   AES_IRQSTATUS_REG                AES_IRQSTATUS;                // Interrupt Status
    union   AES_IRQENABLE_REG                AES_IRQENABLE;                // Interrupt Enable
    union   AES_DIRTY_BITS_REG               AES_DIRTY_BITS;               // Accessed / Dirty Bits
};

//---------------------------------------------------------------------------
// AES External References & Function Declarations:
//
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
