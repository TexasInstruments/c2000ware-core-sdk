//###########################################################################
//
// FILE:    hw_hrpwmcal.h
//
// TITLE:   Definitions for the HRPWMCAL registers.
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

#ifndef HW_HRPWMCAL_H
#define HW_HRPWMCAL_H

//*************************************************************************************************
//
// The following are defines for the HRPWMCAL register offsets
//
//*************************************************************************************************
#define HRPWMCAL_O_HRPWR     0x21U   // HRPWM Power Register
#define HRPWMCAL_O_HRMSTEP   0x26U   // HRPWM MEP Step Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWR register
//
//*************************************************************************************************
#define HRPWMCAL_HRPWR_CALPWRON   0x8000U   // Calibration Power On

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRMSTEP register
//
//*************************************************************************************************
#define HRPWMCAL_HRMSTEP_HRMSTEP_S   0U
#define HRPWMCAL_HRMSTEP_HRMSTEP_M   0xFFU   // High Resolution Micro Step Value



#endif
