//###########################################################################
//
// FILE:    hw_pga.h
//
// TITLE:   Definitions for the PGA registers.
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

#ifndef HW_PGA_H
#define HW_PGA_H

//*************************************************************************************************
//
// The following are defines for the PGA register offsets
//
//*************************************************************************************************
#define PGA_O_CTL          0x0U   // PGA Control Register
#define PGA_O_MUXSEL       0x1U   // Mux Selection Register
#define PGA_O_OFFSETTRIM   0x2U   // Offset Trim Register
#define PGA_O_TYPE         0x5U   // PGA Type Register
#define PGA_O_LOCK         0x6U   // PGA Lock Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the PGACTL register
//
//*************************************************************************************************
#define PGA_CTL_PGAEN               0x1U      // PGA Enable
#define PGA_CTL_FILT_RES_SEL_S      1U
#define PGA_CTL_FILT_RES_SEL_M      0xEU      // Filter Resistor Select
#define PGA_CTL_GAIN_S              5U
#define PGA_CTL_GAIN_M              0xE0U     // PGA gain setting
#define PGA_CTL_PGA_OUTENABLE       0x100U    // PGA Output Enable
#define PGA_CTL_PGA_OUTEN_INTGAIN   0x200U    // PGA Internal Gain Output Enable
#define PGA_CTL_CHOP_EXTCTRL        0x8000U   // External Chop Signal Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the MUXSEL register
//
//*************************************************************************************************
#define PGA_MUXSEL_PMUXSEL_S     0U
#define PGA_MUXSEL_PMUXSEL_M     0x3U      // Positive Input Mux Select
#define PGA_MUXSEL_NMUXSEL_S     4U
#define PGA_MUXSEL_NMUXSEL_M     0x30U     // Negative Input Mux Select
#define PGA_MUXSEL_MMUXSEL_S     8U
#define PGA_MUXSEL_MMUXSEL_M     0x300U    // M Mux Select
#define PGA_MUXSEL_PGA_FBONPIN   0x1000U   // Connect PGAOUT to PGA_INM
#define PGA_MUXSEL_PGA_CHOP_S    13U
#define PGA_MUXSEL_PGA_CHOP_M    0x6000U   // Chopper Mode Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the OFFSETTRIM register
//
//*************************************************************************************************
#define PGA_OFFSETTRIM_PGA_OFFSETTRIMN_S   0U
#define PGA_OFFSETTRIM_PGA_OFFSETTRIMN_M   0xFFU       // OFFSET TRIM value for i/p NMOS pair
#define PGA_OFFSETTRIM_PGA_OFFSETTRIMP_S   16U
#define PGA_OFFSETTRIM_PGA_OFFSETTRIMP_M   0xFF0000U   // OFFSET TRIM value for i/p PMOS pair

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGATYPE register
//
//*************************************************************************************************
#define PGA_TYPE_REV_S    0U
#define PGA_TYPE_REV_M    0xFFU     // PGA Revision Field
#define PGA_TYPE_TYPE_S   8U
#define PGA_TYPE_TYPE_M   0xFF00U   // PGA Type Field

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGALOCK register
//
//*************************************************************************************************
#define PGA_LOCK_PGACTL       0x1U   // Lock bit for PGACTL.
#define PGA_LOCK_MUXSEL       0x2U   // Lock bit for MUXSEL
#define PGA_LOCK_OFFSETTRIM   0x4U   // Lock bit for OFFSET TRIM
#define PGA_LOCK_PGATMCTL     0x8U   // Lock but for PGATMCTL



#endif
