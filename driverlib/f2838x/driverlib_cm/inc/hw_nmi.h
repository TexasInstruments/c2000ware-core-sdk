//###########################################################################
//
// FILE:    hw_nmi.h
//
// TITLE:   Definitions for the NMI registers.
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

#ifndef HW_NMI_H
#define HW_NMI_H

//*************************************************************************************************
//
// The following are defines for the NMI register offsets
//
//*************************************************************************************************
#define NMI_O_CMNMICFG       0x0U    // CM NMI Configuration Register
#define NMI_O_CMNMIFLG       0x4U    // CM NMI Flag Register
#define NMI_O_CMNMIFLGCLR    0x8U    // CMNMI Flag Clear Register
#define NMI_O_CMNMIFLGFRC    0xCU    // CMNMI Flag Force Register
#define NMI_O_CMNMIWDCNT     0x10U   // CMNMI Watchdog Counter Register
#define NMI_O_CMNMIWDPRD     0x14U   // CMNMI Watchdog Period Register
#define NMI_O_CMNMISHDWFLG   0x18U   // CMNMI Shadow Flag Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMICFG register
//
//*************************************************************************************************
#define NMI_CMNMICFG_NMIE    0x1U          // Global NMI Enable
#define NMI_CMNMICFG_KEY_S   16U
#define NMI_CMNMICFG_KEY_M   0xFFFF0000U   // Key protection

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMIFLG register
//
//*************************************************************************************************
#define NMI_CMNMIFLG_NMIINT       0x1U    // NMI Interrupt Flag
#define NMI_CMNMIFLG_CLOCKFAIL    0x2U    // Clock Fail Interrupt Flag
#define NMI_CMNMIFLG_MEMUNCERR    0x4U    // RAM, ROM Uncorrectable Error NMI Flag
#define NMI_CMNMIFLG_FLUNCERR     0x8U    // Flash Uncorrectable Error NMI Flag
#define NMI_CMNMIFLG_MCANUNCERR   0x10U   // MCAN Uncorrectable Error NMI Flag
#define NMI_CMNMIFLG_WWDNMI       0x20U   // CM WWD NMI flag
#define NMI_CMNMIFLG_ECATNMI      0x40U   // NMI from EtherCAT reset out

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMIFLGCLR register
//
//*************************************************************************************************
#define NMI_CMNMIFLGCLR_NMIINT       0x1U          // NMIINT  Flag Clear
#define NMI_CMNMIFLGCLR_CLOCKFAIL    0x2U          // CLOCKFAIL  Flag Clear
#define NMI_CMNMIFLGCLR_MEMUNCERR    0x4U          // MEMUNCERR  Flag Clear
#define NMI_CMNMIFLGCLR_FLUNCERR     0x8U          // FLUNCERR  Flag Clear
#define NMI_CMNMIFLGCLR_MCANUNCERR   0x10U         // MCANUNCERR  Flag Clear
#define NMI_CMNMIFLGCLR_WWDNMI       0x20U         // WWDNMI  Flag Clear
#define NMI_CMNMIFLGCLR_ECATNMI      0x40U         // ECATNMI  Flag Clear
#define NMI_CMNMIFLGCLR_KEY_S        16U
#define NMI_CMNMIFLGCLR_KEY_M        0xFFFF0000U   // Key protection

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMIFLGFRC register
//
//*************************************************************************************************
#define NMI_CMNMIFLGFRC_CLOCKFAIL    0x2U          // CLOCKFAIL  Flag Force
#define NMI_CMNMIFLGFRC_MEMUNCERR    0x4U          // MEMUNCERR  Flag Force
#define NMI_CMNMIFLGFRC_FLUNCERR     0x8U          // FLUNCERR  Flag Force
#define NMI_CMNMIFLGFRC_MCANUNCERR   0x10U         // MCANUNCERR  Flag Force
#define NMI_CMNMIFLGFRC_WWDNMI       0x20U         // WWDNMI  Flag Force
#define NMI_CMNMIFLGFRC_ECATNMI      0x40U         // ECATNMI  Flag Force
#define NMI_CMNMIFLGFRC_KEY_S        16U
#define NMI_CMNMIFLGFRC_KEY_M        0xFFFF0000U   // Key protection

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMIWDCNT register
//
//*************************************************************************************************
#define NMI_CMNMIWDCNT_NMIWDCNT_S   0U
#define NMI_CMNMIWDCNT_NMIWDCNT_M   0xFFFFU   // NMI Watchdog Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMIWDPRD register
//
//*************************************************************************************************
#define NMI_CMNMIWDPRD_NMIWDPRD_S   0U
#define NMI_CMNMIWDPRD_NMIWDPRD_M   0xFFFFU       // NMI Watchdog Period
#define NMI_CMNMIWDPRD_KEY_S        16U
#define NMI_CMNMIWDPRD_KEY_M        0xFFFF0000U   // Key protection

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMNMISHDWFLG register
//
//*************************************************************************************************
#define NMI_CMNMISHDWFLG_CLOCKFAIL    0x2U    // CLOCKFAIL  Shadow flag
#define NMI_CMNMISHDWFLG_MEMUNCERR    0x4U    // MEMUNCERR  Shadow flag
#define NMI_CMNMISHDWFLG_FLUNCERR     0x8U    // FLUNCERR  Shadow flag
#define NMI_CMNMISHDWFLG_MCANUNCERR   0x10U   // MCANUNCERR  Shadow flag
#define NMI_CMNMISHDWFLG_WWDNMI       0x20U   // WWDNMI  Shadow flag
#define NMI_CMNMISHDWFLG_ECATNMI      0x40U   // ECATNMI  Shadow flag



#endif
