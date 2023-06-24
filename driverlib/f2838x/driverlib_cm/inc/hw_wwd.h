//###########################################################################
//
// FILE:    hw_wwd.h
//
// TITLE:   Definitions for the WWD registers.
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

#ifndef HW_WWD_H
#define HW_WWD_H

//*************************************************************************************************
//
// The following are defines for the WWD register offsets
//
//*************************************************************************************************
#define WWD_O_SCSR     0x0U    // System Control & Status Register
#define WWD_O_WDCNTR   0x4U    // Watchdog Counter Register
#define WWD_O_WDKEY    0x8U    // Watchdog Reset Key Register
#define WWD_O_WDCR     0xCU    // Watchdog Control Register
#define WWD_O_WDWCR    0x10U   // Watchdog Windowed Control Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the SCSR register
//
//*************************************************************************************************
#define WWD_SCSR_WDOVERRIDE   0x1U          // WD Override for WDDIS bit
#define WWD_SCSR_WDENINT      0x2U          // WD Interrupt Enable
#define WWD_SCSR_RSVD_S       3U
#define WWD_SCSR_RSVD_M       0xFFF8U       // Reserved
#define WWD_SCSR_KEY_S        16U
#define WWD_SCSR_KEY_M        0xFFFF0000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCNTR register
//
//*************************************************************************************************
#define WWD_WDCNTR_WDCNTR_S   0U
#define WWD_WDCNTR_WDCNTR_M   0xFFU         // WD Counter
#define WWD_WDCNTR_RSVD_S     8U
#define WWD_WDCNTR_RSVD_M     0xFFFFFF00U   // Reserved

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDKEY register
//
//*************************************************************************************************
#define WWD_WDKEY_WDKEY_S   0U
#define WWD_WDKEY_WDKEY_M   0xFFU         // WD KEY
#define WWD_WDKEY_RSVD_S    8U
#define WWD_WDKEY_RSVD_M    0xFFFFFF00U   // Reserved

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCR register
//
//*************************************************************************************************
#define WWD_WDCR_WDPS_S          0U
#define WWD_WDCR_WDPS_M          0x7U          // WD Clock Prescalar
#define WWD_WDCR_WDCHK_S         3U
#define WWD_WDCR_WDCHK_M         0x38U         // WD Check Bits
#define WWD_WDCR_WDDIS           0x40U         // WD Disable
#define WWD_WDCR_WDFLG           0x80U         // WD Reset Status Flag
#define WWD_WDCR_WDPRECLKDIV_S   8U
#define WWD_WDCR_WDPRECLKDIV_M   0xF00U        // WD Pre Clock Divider
#define WWD_WDCR_RSVD_S          12U
#define WWD_WDCR_RSVD_M          0xFFFFF000U   // Reserved

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDWCR register
//
//*************************************************************************************************
#define WWD_WDWCR_MIN_S      0U
#define WWD_WDWCR_MIN_M      0xFFU         // WD Min Threshold setting for Windowed Watchdog
                                           // functionality
#define WWD_WDWCR_FIRSTKEY   0x100U        // First Key Detect Flag
#define WWD_WDWCR_RSVD_S     9U
#define WWD_WDWCR_RSVD_M     0xFE00U       // Reserved
#define WWD_WDWCR_KEY_S      16U
#define WWD_WDWCR_KEY_M      0xFFFF0000U   // KEY field



#endif
