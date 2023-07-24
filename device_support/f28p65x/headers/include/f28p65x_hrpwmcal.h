//###########################################################################
//
// FILE:    f28p65x_hrpwmcal.h
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

#ifndef F28P65X_HRPWMCAL_H
#define F28P65X_HRPWMCAL_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// HRPWMCAL Individual Register Bit Definitions:

struct HRPWR_BITS {                     // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:4;                     // 9:6 Reserved
    Uint16 rsvd7:5;                     // 14:10 Reserved
    Uint16 CALPWRON:1;                  // 15 Calibration Power On
};

union HRPWR_REG {
    Uint16  all;
    struct  HRPWR_BITS  bit;
};

struct HRMSTEP_BITS {                   // bits description
    Uint16 HRMSTEP:8;                   // 7:0 High Resolution Micro Step Value
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union HRMSTEP_REG {
    Uint16  all;
    struct  HRMSTEP_BITS  bit;
};

struct HRPWMCAL_REGS {
    Uint16                                   rsvd1[33];                    // Reserved
    union   HRPWR_REG                        HRPWR;                        // HRPWM Power Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   HRMSTEP_REG                      HRMSTEP;                      // HRPWM MEP Step Register
};

//---------------------------------------------------------------------------
// HRPWMCAL External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct HRPWMCAL_REGS HRPWMCAL1Regs;
extern volatile struct HRPWMCAL_REGS HRPWMCAL2Regs;
extern volatile struct HRPWMCAL_REGS HRPWMCAL3Regs;
#endif
#ifdef CPU2
extern volatile struct HRPWMCAL_REGS HRPWMCAL1Regs;
extern volatile struct HRPWMCAL_REGS HRPWMCAL2Regs;
extern volatile struct HRPWMCAL_REGS HRPWMCAL3Regs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
