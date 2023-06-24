//###########################################################################
//
// FILE:    flash_kernel_ex3_verify.h
//
// TITLE:   Verify Data functions
//
// Functions:
//
//     void verifyData()
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __FLASH_KERNEL_EX3_VERIFY_H__
#define __FLASH_KERNEL_EX3_VERIFY_H__

//
// Included Files
//
#include "cpu1bootrom.h"
#include "cpu1brom_boot_modes.h"
#include "flash_kernel_ex3_commands.h"
#include "FlashTech_F280013x_C28x.h"
#include "cpu1brom_boot_modes.h"
#include "flash_programming_f280013x.h" // Flash API example header file


#include "assert.h"

//
// Function Prototypes
//
extern void sciSendChecksum(void);
void verifyData(void);
extern uint32_t getLongData(void);
extern void readReservedFn(void);
extern uint16_t sciaGetWordData(void);
extern void setFlashAPIError(Fapi_StatusType status);

#endif //__FLASH_KERNEL_EX3_VERIFY_H__

//
// End of file
//
