//###########################################################################
//
// FILE:   Example_EPwmSetup.c
//
// TITLE:  EXAMPLE_EPWMSETUP_C EPWM Setup Example
//
//!  \addtogroup f2806x_example_list
//!  \section EXAMPLE_EPWMSETUP_C EPWM Setup(Example_EPwmSetup.c)
//!
//!  This file contains source for the ePWM initialization for the
//!  freq calculation module. EPWM1 is set to operate in up-down count
//!  mode at a frequency of 5KHz
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_freqcal.h"    // Example specific include file

//
// Defines
//
#define CPU_CLK   80e6

#define PWM_CLK   5e3
#define SP        CPU_CLK/(2*PWM_CLK)
#define TBCTLVAL  0x200E              // Up-down cnt, timebase = SYSCLKOUT

//
// EPwmSetup -
//
void
EPwmSetup()
{
    EPwm1Regs.TBSTS.all=0;
    EPwm1Regs.TBPHS.half.TBPHS=0;
    EPwm1Regs.TBCTR=0;

    EPwm1Regs.CMPCTL.all=0x50;    // Immediate mode for CMPA and CMPB
    EPwm1Regs.CMPA.half.CMPA =SP/2;
    EPwm1Regs.CMPB=0;

    EPwm1Regs.AQCTLA.all=0x60;    // EPWMxA = 1 when CTR=CMPA and counter inc
                                  // EPWMxA = 0 when CTR=CMPA and counter dec
    EPwm1Regs.AQCTLB.all=0;
    EPwm1Regs.AQSFRC.all=0;
    EPwm1Regs.AQCSFRC.all=0;

    EPwm1Regs.DBCTL.all=0xb;      // EPWMxB is inverted
    EPwm1Regs.DBRED=0;
    EPwm1Regs.DBFED=0;

    EPwm1Regs.TZSEL.all=0;
    EPwm1Regs.TZCTL.all=0;
    EPwm1Regs.TZEINT.all=0;
    EPwm1Regs.TZFLG.all=0;
    EPwm1Regs.TZCLR.all=0;
    EPwm1Regs.TZFRC.all=0;

    EPwm1Regs.ETSEL.all=9;       // Interrupt when TBCTR = 0x0000
    EPwm1Regs.ETPS.all=1;	     // Interrupt on first event
    EPwm1Regs.ETFLG.all=0;
    EPwm1Regs.ETCLR.all=0;
    EPwm1Regs.ETFRC.all=0;

    EPwm1Regs.PCCTL.all=0;

    EPwm1Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
    EPwm1Regs.TBPRD=SP;
}

//
// End of File
//

