//###########################################################################
//
// FILE:    hw_pga.h
//
// TITLE:   Definitions for the PGA registers.
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

#ifndef HW_PGA_H
#define HW_PGA_H

//*************************************************************************************************
//
// The following are defines for the PGA register offsets
//
//*************************************************************************************************
#define PGA_O_CTL          0x0U   // PGA Control Register
#define PGA_O_LOCK         0x2U   // PGA Lock Register
#define PGA_O_GAIN3TRIM    0x4U   // PGA Gain Trim Register for a gain setting of 3
#define PGA_O_GAIN6TRIM    0x5U   // PGA Gain Trim Register for a gain setting of 6
#define PGA_O_GAIN12TRIM   0x6U   // PGA Gain Trim Register for a gain setting of 12
#define PGA_O_GAIN24TRIM   0x7U   // PGA Gain Trim Register for a gain setting of 24
#define PGA_O_TYPE         0x8U   // PGA Type Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the PGACTL register
//
//*************************************************************************************************
#define PGA_CTL_PGAEN          0x1U    // PGA Enable
#define PGA_CTL_FILTRESSEL_S   1U
#define PGA_CTL_FILTRESSEL_M   0x1EU   // Filter Resistor Select
#define PGA_CTL_GAIN_S         5U
#define PGA_CTL_GAIN_M         0xE0U   // PGA gain setting

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGALOCK register
//
//*************************************************************************************************
#define PGA_LOCK_PGACTL          0x1U    // Lock bit for PGACTL.
#define PGA_LOCK_PGAGAIN3TRIM    0x4U    // Lock bit for PGAGAIN3TRIM.
#define PGA_LOCK_PGAGAIN6TRIM    0x8U    // Lock bit for PGAGAIN6TRIM.
#define PGA_LOCK_PGAGAIN12TRIM   0x10U   // Lock bit for PGAGAIN12TRIM.
#define PGA_LOCK_PGAGAIN24TRIM   0x20U   // Lock bit for PGAGAIN24TRIM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN3TRIM register
//
//*************************************************************************************************
#define PGA_GAIN3TRIM_GAINTRIM_S     0U
#define PGA_GAIN3TRIM_GAINTRIM_M     0xFFU     // Gain TRIM value, when gain setting is 3
#define PGA_GAIN3TRIM_OFFSETTRIM_S   8U
#define PGA_GAIN3TRIM_OFFSETTRIM_M   0xFF00U   // OFFSET TRIM value, when Gain setting is 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN6TRIM register
//
//*************************************************************************************************
#define PGA_GAIN6TRIM_GAINTRIM_S     0U
#define PGA_GAIN6TRIM_GAINTRIM_M     0xFFU     // Gain TRIM value, when gain setting is 6
#define PGA_GAIN6TRIM_OFFSETTRIM_S   8U
#define PGA_GAIN6TRIM_OFFSETTRIM_M   0xFF00U   // OFFSET TRIM value, when Gain setting is 6

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN12TRIM register
//
//*************************************************************************************************
#define PGA_GAIN12TRIM_GAINTRIM_S     0U
#define PGA_GAIN12TRIM_GAINTRIM_M     0xFFU     // Gain TRIM value, when gain setting is 12
#define PGA_GAIN12TRIM_OFFSETTRIM_S   8U
#define PGA_GAIN12TRIM_OFFSETTRIM_M   0xFF00U   // OFFSET TRIM value, when Gain setting is 12

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGAGAIN24TRIM register
//
//*************************************************************************************************
#define PGA_GAIN24TRIM_GAINTRIM_S     0U
#define PGA_GAIN24TRIM_GAINTRIM_M     0xFFU     // Gain TRIM value, when gain setting is 24
#define PGA_GAIN24TRIM_OFFSETTRIM_S   8U
#define PGA_GAIN24TRIM_OFFSETTRIM_M   0xFF00U   // OFFSET TRIM value, when Gain setting is 24

//*************************************************************************************************
//
// The following are defines for the bit fields in the PGATYPE register
//
//*************************************************************************************************
#define PGA_TYPE_REV_S    0U
#define PGA_TYPE_REV_M    0xFFU     // PGA Revision Field
#define PGA_TYPE_TYPE_S   8U
#define PGA_TYPE_TYPE_M   0xFF00U   // PGA Type Field



#endif
