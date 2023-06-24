//###########################################################################
//
// FILE:    hw_pbist.h
//
// TITLE:   Definitions for the PBIST registers.
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

#ifndef HW_PBIST_H
#define HW_PBIST_H

//*****************************************************************************
//
// The following are defines for the PBIST register offsets
//
//*****************************************************************************
#define PBIST_O_RAMT              0x160U       // RAM Configuration Register
#define PBIST_O_DLRT              0x164U       // PBIST Data Logger Register
#define PBIST_O_STR               0x16CU       // Program Control Register
#define PBIST_O_PACT              0x180U       // PBIST Activate Register
#define PBIST_O_OVERRIDE          0x188U       // PBIST Override Register
#define PBIST_O_FSRF0             0x190U       // Fail Status - Port 0
#define PBIST_O_FSRF1             0x194U       // Fail Status - Port 1
#define PBIST_O_FSRC0             0x198U       // Fail Status Count - Port 0
#define PBIST_O_FSRC1             0x19CU       // Fail Status Count - Port 1
#define PBIST_O_ALGO              0x1C4U       // PBIST Algorithm
#define PBIST_O_RINFOL            0x1C8U       // RAM Info Mask Register Lower
#define PBIST_O_RINFOU            0x1CCU       // RAM Info Mask Register Higher

//*****************************************************************************
//
// The following are defines for the bit fields in the RAMT register
//
//*****************************************************************************
#define PBIST_RAMT_RDS_S          16U
#define PBIST_RAMT_RDS_M          0xFF0000U    // Return Data Select
#define PBIST_RAMT_RGS_S          24U
#define PBIST_RAMT_RGS_M          0xFF000000U  // RAM Group Select

//*****************************************************************************
//
// The following are defines for the bit fields in the DLRT register
//
//*****************************************************************************
#define PBIST_DLRT_ROM_TEST       0x4U         // ROM-based testing
#define PBIST_DLRT_TCK_GATED      0x8U         // TCK gated
#define PBIST_DLRT_CONFIG_ACC     0x10U        // Config Access
#define PBIST_DLRT_GO_NOGO_TEST   0x200U       // GO/ NO-GO Testing

//*****************************************************************************
//
// The following are defines for the bit fields in the STR register
//
//*****************************************************************************
#define PBIST_STR_RESUME          0x2U         // Resume / Emulation Read
#define PBIST_STR_STOP            0x4U         // Stops PBIST testing

//*****************************************************************************
//
// The following are defines for the bit fields in the PACT register
//
//*****************************************************************************
#define PBIST_PACT_ENABLE         0x1U         // Enable clocks to PBIST

//*****************************************************************************
//
// The following are defines for the bit fields in the OVERRIDE register
//
//*****************************************************************************
#define PBIST_OVERRIDE_RINFO_MEM_OVER  0x1U         // ROM Memory Information
                                               // Override
#define PBIST_OVERRIDE_ALGO_OVER  0x8U         // ROM Algorithm Override
#endif
