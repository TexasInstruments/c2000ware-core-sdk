//###########################################################################
//
// FILE:    hw_cmpss_lite.h
//
// TITLE:   Definitions for the CMPSSLITE registers.
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

#ifndef HW_CMPSS_LITE_H
#define HW_CMPSS_LITE_H

//*************************************************************************************************
//
// The following are defines for the CMPSSLITE register offsets
//
//*************************************************************************************************
#define CMPSSLITE_O_COMPCTL           0x0U    // CMPSS Comparator Control Register
#define CMPSSLITE_O_COMPHYSCTL        0x1U    // CMPSS Comparator Hysteresis Control Register
#define CMPSSLITE_O_COMPSTS           0x2U    // CMPSS Comparator Status Register
#define CMPSSLITE_O_COMPSTSCLR        0x3U    // CMPSS Comparator Status Clear Register
#define CMPSSLITE_O_COMPDACHCTL       0x4U    // CMPSS High DAC Control Register
#define CMPSSLITE_O_DACHVALS          0x6U    // CMPSS High DAC Value Shadow Register
#define CMPSSLITE_O_DACHVALA          0x7U    // CMPSS High DAC Value Active Register
#define CMPSSLITE_O_DACLVALS          0x12U   // CMPSS Low DAC Value Shadow Register
#define CMPSSLITE_O_DACLVALA          0x13U   // CMPSS Low DAC Value Active Register
#define CMPSSLITE_O_CTRIPLFILCTL      0x16U   // CTRIPL Filter Control Register
#define CMPSSLITE_O_CTRIPLFILCLKCTL   0x17U   // CTRIPL Filter Clock Control Register
#define CMPSSLITE_O_CTRIPHFILCTL      0x18U   // CTRIPH Filter Control Register
#define CMPSSLITE_O_CTRIPHFILCLKCTL   0x19U   // CTRIPH Filter Clock Control Register
#define CMPSSLITE_O_COMPLOCK          0x1AU   // CMPSS Lock Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPCTL register
//
//*************************************************************************************************
#define CMPSSLITE_COMPCTL_COMPHSOURCE      0x1U      // High Comparator Source Select
#define CMPSSLITE_COMPCTL_COMPHINV         0x2U      // High Comparator Invert Select
#define CMPSSLITE_COMPCTL_CTRIPHSEL_S      2U
#define CMPSSLITE_COMPCTL_CTRIPHSEL_M      0xCU      // High Comparator Trip Select
#define CMPSSLITE_COMPCTL_CTRIPOUTHSEL_S   4U
#define CMPSSLITE_COMPCTL_CTRIPOUTHSEL_M   0x30U     // High Comparator Trip Output Select
#define CMPSSLITE_COMPCTL_ASYNCHEN         0x40U     // High Comparator Asynchronous Path Enable
#define CMPSSLITE_COMPCTL_COMPLSOURCE      0x100U    // Low Comparator Source Select
#define CMPSSLITE_COMPCTL_COMPLINV         0x200U    // Low Comparator Invert Select
#define CMPSSLITE_COMPCTL_CTRIPLSEL_S      10U
#define CMPSSLITE_COMPCTL_CTRIPLSEL_M      0xC00U    // Low Comparator Trip Select
#define CMPSSLITE_COMPCTL_CTRIPOUTLSEL_S   12U
#define CMPSSLITE_COMPCTL_CTRIPOUTLSEL_M   0x3000U   // Low Comparator Trip Output Select
#define CMPSSLITE_COMPCTL_ASYNCLEN         0x4000U   // Low Comparator Asynchronous Path Enable
#define CMPSSLITE_COMPCTL_COMPDACE         0x8000U   // Comparator/DAC Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPHYSCTL register
//
//*************************************************************************************************
#define CMPSSLITE_COMPHYSCTL_COMPHYS_S   0U
#define CMPSSLITE_COMPHYSCTL_COMPHYS_M   0xFU   // Comparator Hysteresis Trim

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPSTS register
//
//*************************************************************************************************
#define CMPSSLITE_COMPSTS_COMPHSTS     0x1U     // High Comparator Status
#define CMPSSLITE_COMPSTS_COMPHLATCH   0x2U     // High Comparator Latched Status
#define CMPSSLITE_COMPSTS_COMPLSTS     0x100U   // Low Comparator Status
#define CMPSSLITE_COMPSTS_COMPLLATCH   0x200U   // Low Comparator Latched Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPSTSCLR register
//
//*************************************************************************************************
#define CMPSSLITE_COMPSTSCLR_HLATCHCLR    0x2U     // High Comparator Latched Status Clear
#define CMPSSLITE_COMPSTSCLR_HSYNCCLREN   0x4U     // High Comparator EPWMSYNCPER Clear Enable
#define CMPSSLITE_COMPSTSCLR_LLATCHCLR    0x200U   // Low Comparator Latched Status Clear
#define CMPSSLITE_COMPSTSCLR_LSYNCCLREN   0x400U   // Low Comparator EPWMSYNCPER Clear Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPDACHCTL register
//
//*************************************************************************************************
#define CMPSSLITE_COMPDACHCTL_RAMPSOURCE_S    1U
#define CMPSSLITE_COMPDACHCTL_RAMPSOURCE_M    0x1EU     // Ramp Generator Source Control
#define CMPSSLITE_COMPDACHCTL_SWLOADSEL       0x80U     // Software Load Select
#define CMPSSLITE_COMPDACHCTL_BLANKSOURCE_S   8U
#define CMPSSLITE_COMPDACHCTL_BLANKSOURCE_M   0xF00U    // EPWMBLANK Source Select
#define CMPSSLITE_COMPDACHCTL_BLANKEN         0x1000U   // EPWMBLANK Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACHVALS register
//
//*************************************************************************************************
#define CMPSSLITE_DACHVALS_DACVAL_S   0U
#define CMPSSLITE_DACHVALS_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACHVALA register
//
//*************************************************************************************************
#define CMPSSLITE_DACHVALA_DACVAL_S   0U
#define CMPSSLITE_DACHVALA_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACLVALS register
//
//*************************************************************************************************
#define CMPSSLITE_DACLVALS_DACVAL_S   0U
#define CMPSSLITE_DACLVALS_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACLVALA register
//
//*************************************************************************************************
#define CMPSSLITE_DACLVALA_DACVAL_S   0U
#define CMPSSLITE_DACLVALA_DACVAL_M   0xFFFU   // DAC Value Control

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPLFILCTL register
//
//*************************************************************************************************
#define CMPSSLITE_CTRIPLFILCTL_SAMPWIN_S   3U
#define CMPSSLITE_CTRIPLFILCTL_SAMPWIN_M   0xF8U     // Sample Window
#define CMPSSLITE_CTRIPLFILCTL_THRESH_S    9U
#define CMPSSLITE_CTRIPLFILCTL_THRESH_M    0x3E00U   // Majority Voting Threshold
#define CMPSSLITE_CTRIPLFILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CTRIPHFILCTL register
//
//*************************************************************************************************
#define CMPSSLITE_CTRIPHFILCTL_SAMPWIN_S   3U
#define CMPSSLITE_CTRIPHFILCTL_SAMPWIN_M   0xF8U     // Sample Window
#define CMPSSLITE_CTRIPHFILCTL_THRESH_S    9U
#define CMPSSLITE_CTRIPHFILCTL_THRESH_M    0x3E00U   // Majority Voting Threshold
#define CMPSSLITE_CTRIPHFILCTL_FILINIT     0x8000U   // Filter Initialization Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the COMPLOCK register
//
//*************************************************************************************************
#define CMPSSLITE_COMPLOCK_COMPCTL      0x1U   // COMPCTL Lock
#define CMPSSLITE_COMPLOCK_COMPHYSCTL   0x2U   // COMPHYSCTL Lock
#define CMPSSLITE_COMPLOCK_DACCTL       0x4U   // DACCTL Lock
#define CMPSSLITE_COMPLOCK_CTRIP        0x8U   // CTRIP Lock



#endif
