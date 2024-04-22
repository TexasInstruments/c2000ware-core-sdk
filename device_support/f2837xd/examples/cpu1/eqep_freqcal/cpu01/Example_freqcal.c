//###########################################################################
//
// FILE:    Example_freqcal.c
//
// TITLE:    Frequency measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file includes the EQEP initialization and frequency calculation
// functions called by Eqep_freqcal.c.  The frequency calculation
// steps performed by FREQCAL_Calc() at SYSCLKOUT = 200 MHz are
// described below:
//
//
// 1. This program calculates: **freqhz_fr**
//    freqhz_fr or v = (x2-x1)/T      - Equation 1
//
// If max/base freq = 10kHz:   10kHz = (x2-x1)/(2/100Hz)    - Equation 2
//                      max (x2-x1) = 200 counts = freqScaler_fr
//   Note: T = 2/100Hz. 2 is from (x2-x1)/2 - because QPOSCNT counts 2 edges
//                                            per cycle(rising and falling)
//
// If both sides of Equation 2 are divided by 10 kHz, then:
//      1 = (x2-x1)/[10kHz*(2/100Hz)] where [10kHz* (2/100Hz)] = 200
//      Because (x2-x1) must be <200 (max),
//      (x2-x1)/200 < 1 for all frequencies less than max
//      freq_fr = (x2-x1)/200 or (x2-x1)/[10kHz*(2/100Hz)]    - Equation 3
//
// To get back to original velocity equation, Equation 1,
// multiply Equation 3 by 10 kHz
//      freqhz_fr (or velocity) = 10kHz*(x2-x1)/[10kHz*(2/100Hz)]
//                              = (x2-x1)/(2/100Hz)           - Final equation
//
// 2. **min freq** = 1 count/(2/100Hz) = 50 Hz
//
// 3. **freqhz_pr**
//    freqhz_pr or v = X/(t2-t1)   - Equation 4
//
// If max/base freq = 10kHz:  10kHz = (8/2)/T = 8/2T
//    where 8 = QCAPCTL [UPPS] (Unit timeout - once every 8 edges)
//            2 = divide by 2 because QPOSCNT counts 2 edges per cycle
//                (rising and falling)
//            T = time in seconds
//            = t2-t1/(100MHz/128),  t2-t1= # of QCAPCLK cycles, and
//                          1 QCAPCLK cycle = 1/(100MHz/128)
//                                          = QCPRDLAT
//
// So: 10 kHz = 8(200MHz/128)/2(t2-t1)
//      t2-t1 = 8(200MHz/128)/(10kHz*2) = (200MHz/128)/(2*10kHz/8) - Equation 5
//            = 625QCAPCLK cycles = maximum (t2-t1) = freqScaler_pr
//
// Divide both sides by (t2-t1), and:
//          1 = 625/(t2-t1) = [(200MHz/128)/(2*10kHz/8)]/(t2-t1)
//  Because (t2-t1) must be <625 (max).
//              625/(t2-t1) < 1 for all frequencies less than max
//    freq_pr = 625/(t2-t1) or [(200MHz/128)/(2*10kHz/8)]/(t2-t1) - Equation 6
// Now within velocity limits, to get back to original velocity equation,
// Equation 1, multiply Equation 6 by 10 kHz:
//  freqhz_fr (or velocity) = 10kHz*[200MHz/128)/(2*10kHz/8)]/(t2-t1)
//                          = (200MHz/128)*8/[2(t2-t1)]
//                          or 8/[2*(t2-t1)(QCPRDLAT)]        - Final Equation
//
//
// More detailed calculation results can be found in the Example_freqcal.xls
// spreadsheet included in the example folder.
//
//
// This file contains source for the freq calculation module.
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"
#include "Example_freqcal.h"

//
// FREQCAL_Init - Initialize EQEP1 configuration
//
void  FREQCAL_Init(void)
{
    EQep1Regs.QUPRD=2000000;          // Unit Timer for 100Hz at
                                      // 200 MHz SYSCLKOUT

    EQep1Regs.QDECCTL.bit.QSRC=2;     // Up count mode (freq. measurement)
    EQep1Regs.QDECCTL.bit.XCR=0;      // 2x resolution (cnt falling and
                                      //                rising edges)

    EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
    EQep1Regs.QEPCTL.bit.PCRM=00;     // QPOSCNT reset on index evnt
    EQep1Regs.QEPCTL.bit.UTE=1;       // Unit Timer Enable
    EQep1Regs.QEPCTL.bit.QCLM=1;      // Latch on unit time out
    EQep1Regs.QPOSMAX=0xffffffff;
    EQep1Regs.QEPCTL.bit.QPEN=1;      // QEP enable

    EQep1Regs.QCAPCTL.bit.UPPS=3;     // 1/8 for unit position
    EQep1Regs.QCAPCTL.bit.CCPS=7;     // 1/128 for CAP clock
    EQep1Regs.QCAPCTL.bit.CEN=1;      // QEP Capture Enable
}

//
// FREQCAL_Calc - Perform Frequency calculations
//
void FREQCAL_Calc(FREQCAL *p)
{
    unsigned long tmp;
    _iq newp,oldp;

//
// Check unit Time out-event for speed calculation:
// Unit Timer is configured for 100Hz in INIT function
// For a more detailed explanation of the calculation, read
// the description at the top of this file
//
    if(EQep1Regs.QFLG.bit.UTO==1)   // Unit Timeout event
    {
        //
        // Differentiator
        //
        newp=EQep1Regs.QPOSLAT;    // Latched POSCNT value
        oldp=p->oldpos;

        if (newp>oldp) // x2-x1 in v=(x2-x1)/T equation
        {
            tmp = newp - oldp;
        }
        else
        {
            tmp = (0xFFFFFFFF-oldp)+newp;
        }

        //
        // p->freq_fr = (x2-x1)/(T*10KHz)
        //
        p->freq_fr = _IQdiv(tmp,p->freqScaler_fr);
        tmp=p->freq_fr;

        if (tmp>=_IQ(1))// is freq greater than max freq (10KHz for this)?
        {
            p->freq_fr = _IQ(1);
        }
        else
        {
             p->freq_fr = tmp;
        }

        //
        // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
        // p->freqhz_fr = (p->freq_fr)*10kHz = (x2-x1)/T
        //
        p->freqhz_fr = _IQmpy(p->BaseFreq,p->freq_fr);

        //
        // Update position counter
        //
        p->oldpos = newp;

        EQep1Regs.QCLR.bit.UTO=1;   // Clear __interrupt flag
    }

    //
    // Freq Calculation using QEP capture counter
    //
    if(EQep1Regs.QEPSTS.bit.UPEVNT==1)  // Unit Position Event
    {
        if(EQep1Regs.QEPSTS.bit.COEF==0)  // No Capture overflow
        {
            tmp=(unsigned long)EQep1Regs.QCPRDLAT;
        }
        else // Capture overflow, saturate the result
        {
            tmp=0xFFFF;
        }

        //
        // p->freq_pr = X/[(t2-t1)*10KHz]
        //
        p->freq_pr = _IQdiv(p->freqScaler_pr,tmp);
        tmp=p->freq_pr;

        if (tmp>_IQ(1))
        {
             p->freq_pr = _IQ(1);
        }
        else
        {
             p->freq_pr = tmp;
        }

        //
        // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
        // p->freqhz_pr =( p->freq_pr)*10kHz = X/(t2-t1)
        //
        p->freqhz_pr = _IQmpy(p->BaseFreq,p->freq_pr);

        //
        // Clear Unit position event flag
        // Clear overflow error flag
        //
        EQep1Regs.QEPSTS.all=0x88;
    }
}

//
// End of file
//
