//###########################################################################
//
// FILE:    hw_nmi.h
//
// TITLE:   Definitions for the NMI registers.
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

#ifndef HW_NMI_H
#define HW_NMI_H

//*************************************************************************************************
//
// The following are defines for the NMI register offsets
//
//*************************************************************************************************
#define NMI_O_CFG           0x0U   // NMI Configuration Register
#define NMI_O_FLG           0x1U   // NMI Flag Register (SYSRsn Clear)
#define NMI_O_FLGCLR        0x2U   // NMI Flag Clear Register
#define NMI_O_FLGFRC        0x3U   // NMI Flag Force Register
#define NMI_O_WDCNT         0x4U   // NMI Watchdog Counter Register
#define NMI_O_WDPRD         0x5U   // NMI Watchdog Period Register
#define NMI_O_SHDFLG        0x6U   // NMI Shadow Flag Register
#define NMI_O_ERRORSTS      0x7U   // Error pin status
#define NMI_O_ERRORSTSCLR   0x8U   // ERRORSTS clear register
#define NMI_O_ERRORSTSFRC   0x9U   // ERRORSTS force register
#define NMI_O_ERRORCTL      0xAU   // Error pin control register
#define NMI_O_ERRORLOCK     0xBU   // Lock register to Error pin registers.


//*************************************************************************************************
//
// The following are defines for the bit fields in the NMICFG register
//
//*************************************************************************************************
#define NMI_CFG_NMIE   0x1U   // Global NMI Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMIFLG register
//
//*************************************************************************************************
#define NMI_FLG_NMIINT      0x1U      // NMI Interrupt Flag
#define NMI_FLG_CLOCKFAIL   0x2U      // Clock Fail Interrupt Flag
#define NMI_FLG_UNCERR      0x4U      // Flash/RAM/ROM Uncorrectable Error NMI Flag
#define NMI_FLG_SWERR       0x2000U   // SW Error Force NMI Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMIFLGCLR register
//
//*************************************************************************************************
#define NMI_FLGCLR_NMIINT      0x1U      // NMIINT Flag Clear
#define NMI_FLGCLR_CLOCKFAIL   0x2U      // CLOCKFAIL Flag Clear
#define NMI_FLGCLR_UNCERR      0x4U      // Flash/RAM/ROM Uncorrectable Error NMI Flag clear
#define NMI_FLGCLR_SWERR       0x2000U   // SW Error Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMIFLGFRC register
//
//*************************************************************************************************
#define NMI_FLGFRC_CLOCKFAIL   0x2U      // CLOCKFAIL Flag Force
#define NMI_FLGFRC_UNCERR      0x4U      // Flash/RAM/ROM Uncorrectable Error NMI Flag force
#define NMI_FLGFRC_SWERR       0x2000U   // SW Error Flag Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMISHDFLG register
//
//*************************************************************************************************
#define NMI_SHDFLG_CLOCKFAIL   0x2U      // Shadow CLOCKFAIL Flag
#define NMI_SHDFLG_UNCERR      0x4U      // Flash/RAM/ROM Uncorrectable Error NMI shadow flag
#define NMI_SHDFLG_SWERR       0x2000U   // Shadow SW Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERRORSTS register
//
//*************************************************************************************************
#define NMI_ERRORSTS_ERROR    0x1U   // Error flag.
#define NMI_ERRORSTS_PINSTS   0x2U   // Error pin status.

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERRORSTSCLR register
//
//*************************************************************************************************
#define NMI_ERRORSTSCLR_ERROR   0x1U   // ERRORFLG.ERROR clear bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERRORSTSFRC register
//
//*************************************************************************************************
#define NMI_ERRORSTSFRC_ERROR   0x1U   // ERRORSTS.ERROR pin force.

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERRORCTL register
//
//*************************************************************************************************
#define NMI_ERRORCTL_ERRORPOLSEL   0x1U   // ERROR pin polarity select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERRORLOCK register
//
//*************************************************************************************************
#define NMI_ERRORLOCK_ERRORCTL   0x1U   // ERRORCTL Lock bit



#endif
