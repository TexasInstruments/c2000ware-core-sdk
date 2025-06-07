//###########################################################################
//
// FILE:    hw_flash.h
//
// TITLE:   Definitions for the FLASH registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef HW_FLASH_H
#define HW_FLASH_H

//*************************************************************************************************
//
// The following are defines for the FLASH register offsets
//
//*************************************************************************************************
#define FLASH_O_FRDCNTL         0x0U     // Flash Read Control Register
#define FLASH_O_FLPROT          0x4U     // Flash program/erase protect register
#define FLASH_O_FRD_INTF_CTRL   0x180U   // Flash Read Interface Control Register

#define FLASH_O_ECC_ENABLE   0x0U    // ECC Enable
#define FLASH_O_FECC_CTRL    0x20U   // ECC Control


//*************************************************************************************************
//
// The following are defines for the bit fields in the FRDCNTL register
//
//*************************************************************************************************
#define FLASH_FRDCNTL_RWAIT_S   8U
#define FLASH_FRDCNTL_RWAIT_M   0xF00U   // Random Read Waitstate

//*************************************************************************************************
//
// The following are defines for the bit fields in the FLPROT register
//
//*************************************************************************************************
#define FLASH_FLPROT_FLWEPROT   0x1U   // Flash write/erase protect bit.

//*************************************************************************************************
//
// The following are defines for the bit fields in the FRD_INTF_CTRL register
//
//*************************************************************************************************
#define FLASH_FRD_INTF_CTRL_PREFETCH_EN     0x1U   // Prefetch Enable
#define FLASH_FRD_INTF_CTRL_DATA_CACHE_EN   0x2U   // Data Cache Enable


//*************************************************************************************************
//
// The following are defines for the bit fields in the ECC_ENABLE register
//
//*************************************************************************************************
#define FLASH_ECC_ENABLE_ENABLE_S   0U
#define FLASH_ECC_ENABLE_ENABLE_M   0xFU   // Enable ECC

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_CTRL register
//
//*************************************************************************************************
#define FLASH_FECC_CTRL_ECC_TEST_EN_S   0U
#define FLASH_FECC_CTRL_ECC_TEST_EN_M   0x3U   // Enable ECC Test Logic



#endif
