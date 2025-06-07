//###########################################################################
//
// FILE:        PWM_DualUpDwnCnt_Cnf.c
//
// Description: Driver Config to support independent duty contol on chA 
//              and chB of the PWM
//
// Target:      TMS320F2802x 
//
// The function call is:  PWM_DualUPDwnCnt_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//
// n =       Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// Period =  PWM period in Sysclks
// Mode =    Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// Phase =   phase offset from upstream master in Sysclks,
//           applicable only if mode=0, i.e. slave
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
#include "DSP28x_Project.h"
#include "f2802x_epwm_defines.h"

extern volatile struct EPWM_REGS *ePWM[];

//
// PWM_DualUpDwnCnt_CNF - 
//
void PWM_DualUpDwnCnt_CNF(int16 n, int16 Period, int16 Mode, int16 Phase)
{
    //
    // Time Base SubModule Register
    //
    (*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;    // set Immediate load
    (*ePWM[n]).TBPRD=((Period>>1));
    (*ePWM[n]).TBPHS.half.TBPHS =0;
    (*ePWM[n]).TBCTR = 0;
    (*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    (*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
    (*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;
    
    if(Mode == 1) // config as a Master
    {
        (*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
        (*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
    }
    
    //
    // config as a Slave (Note: Phase+2 value used to compensate for 
    // logic delay)
    //
    if(Mode == 0)
    {
        (*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;
        (*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

        if( (0 <= Phase)&&(Phase <= 2))    
        {
            (*ePWM[n]).TBPHS.half.TBPHS = (2-Phase);
            (*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP;  // set to count up after sync
        }
        else if ((2 < Phase)&&(Phase <= Period/2))
        {
            (*ePWM[n]).TBPHS.half.TBPHS = (Phase-2);
            //
            // set to count down after sync
            //
            (*ePWM[n]).TBCTL.bit.PHSDIR = TB_DOWN;
        }
        else if ((Period/2 < Phase)&&(Phase <= Period))
        {
            (*ePWM[n]).TBPHS.half.TBPHS = (Period-Phase+2);
            (*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP;  // set to count up after sync
        }
    }
    
    (*ePWM[n]).CMPA.half.CMPA = 0;             // set duty 0% initially
    (*ePWM[n]).CMPB = (*ePWM[n]).TBPRD;        // set duty 0% initially
    
    //
    // Counter compare submodule registers
    //
    (*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    (*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    (*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    (*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    //
    // Action Qualifier SubModule Registers
    //
    (*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
    (*ePWM[n]).AQCTLA.bit.CAD = AQ_SET;
    (*ePWM[n]).AQCTLB.bit.CBU = AQ_SET;
    (*ePWM[n]).AQCTLB.bit.CBD = AQ_CLEAR;
}

//
// End of File
//

