//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
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

#ifndef HW_MEMMAP_H
#define HW_MEMMAP_H

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define C1RAM_BASE                0x1FFFC000U
#define C0RAM_BASE                0x1FFFE000U
#define S0RAM_BASE                0x20000000U
#define S1RAM_BASE                0x20004000U
#define S2RAM_BASE                0x20008000U
#define S3RAM_BASE                0x2000C000U
#define E0RAM_BASE                0x20010000U
#define CPU1TOCMMSGRAM0_BASE      0x20080000U
#define CPU1TOCMMSGRAM1_BASE      0x20080800U
#define CMTOCPU1MSGRAM0_BASE      0x20082000U
#define CMTOCPU1MSGRAM1_BASE      0x20082800U
#define CPU2TOCMMSGRAM0_BASE      0x20084000U
#define CPU2TOCMMSGRAM1_BASE      0x20084800U
#define CMTOCPU2MSGRAM0_BASE      0x20086000U
#define CMTOCPU2MSGRAM1_BASE      0x20086800U
#define SSI0_BASE                 0x40008000U
#define UART0_BASE                0x4000C000U
#define I2C0_BASE                 0x40020000U
#define GCRC_BASE                 0x40040000U
#define AES_BASE                  0x4004A000U
#define AESW_BASE                 0x4004AC00U
#define USB0_BASE                 0x40050000U
#define CANA_BASE                 0x40070000U
#define CANB_BASE                 0x40074000U
#define MCAN0_BASE                0x40078000U
#define MCAN_SS_BASE              0x4007C400U
#define MCAN_BASE                 0x4007C600U
#define MCAN_ERROR_BASE           0x4007C800U
#define WD_BASE                   0x40080000U
#define NMI_BASE                  0x40081000U
#define GPIODATA_BASE             0x40083000U
#define GPIODATAREAD_BASE         0x40083100U
#define CPUTIMER0_BASE            0x40084000U
#define CPUTIMER1_BASE            0x40084010U
#define CPUTIMER2_BASE            0x40084020U
#define DCSM_Z1_BASE              0x40085000U
#define DCSM_Z2_BASE              0x40085100U
#define DCSMCOMMON_BASE           0x40085180U
#define ESC_SS_BASE               0x400AFC00U
#define ESC_SS_CONFIG_BASE        0x400AFE00U
#define EMAC_BASE                 0x400C0000U
#define EMAC_SS_BASE              0x400C2000U
#define DMPU_BASE                 0x400CC000U
#define EMPU_BASE                 0x400CD000U
#define FLASH0CTRL_BASE           0x400FA000U
#define FLASH0ECC_BASE            0x400FA600U
#define CMSYSCTL_BASE             0x400FC000U
#define IPC_CMTOCPU1_BASE         0x400FD000U
#define FLASHPUMPSEMAPHORE_BASE   0x400FD048U
#define IPC_CMTOCPU2_BASE         0x400FD080U
#define CMMEMCFG_BASE             0x400FE000U
#define CMMEMORYERROR_BASE        0x400FE400U
#define CMMEMORYDIAGERROR_BASE    0x400FE800U
#define UDMA_BASE                 0x400FF000U
#define NVIC_BASE                 0xE000E000U
#endif
