//###########################################################################
//
// FILE:   Example_freqcal.c
//
// TITLE:  EXAMPLE_FREQCAL_C Frequency Calculation
//
//!  \addtogroup f2823x_example_list
//!  \section EXAMPLE_FREQCAL_C Frequency Calculation (Example_freqal.c)
//!
//!  This file includes the EQEP initialization and frequency calculation
//!  functions called by \b Example_2823xEqep_freqcal.c.  
//!  The frequency calculation steps performed by FREQCAL_Calc()at  
//!  SYSCLKOUT = 150 MHz and 100 MHZ are described below:
//!
//!  -# This program calculates: \b **freqhz_fr** for SYSCLKOUT = 150MHz \n
//!  \f[ freqhz\_fr\ or\ v = \frac{x_{2}-x_{1}}{T} .......... 1 \f] \n
//!  If \f[ \frac{max}{base}\ freq = 10kHz => 10kHz = \
\frac{x_{2}-x_{1}}{(2/100Hz)} .......... 2\f] \n
//!  \f[ max (x_{2}-x_{1}) = 200 counts = freqScaler\_fr \f]
//!
//!  \note \f$ T = \frac{2}{100Hz} \f$ . 2 is from \f$ \frac{x_{2}-x_{1}}{2}\f$
//!  because QPOSCNT counts 2 edges per cycle (rising and falling)
//!
//!  If both sides of Equation 2 are divided by 10 kHz, then: \n
//!  \f[ 1 = \frac{x_{2}-x_{1}}{10kHz*(2/100Hz)}\f]\n where, 
//!  \f[ [10kHz*\frac{2}{100Hz}] = 200 \f]\n
//!  Because \f[ x_{2}-x_{1} < 200 (max)\f]
//!  \f[ \frac{x_{2}-x_{1}}{200} < 1 \f]\n for all frequencies less than max\n
//!  \f[ freq\_fr = \frac{x_{2}-x_{1}}{200}\ or\ \
\frac{x_{2}-x_{1}}{10kHz*(2/100Hz)} .......... 3\f] \n
//!
//!  To get back to original velocity equation, Equation 1, multiply 
//!  Equation 3 by 10 kHz\n
//!  \f[ freqhz\_fr(or\ velocity) = \
10kHz*\frac{x_{2}-x_{1}}{10kHz*(2/100Hz)}\f]\n
//!  \f[ = \frac{x_{2}-x_{1}}{(2/100Hz)} .......... final\ equation\f] \n
//!
//!  -# \b **min \b freq** \f$ = \frac{1\ count}{(2/100Hz)} = 50 Hz\f$
//!  -# \b **freqhz_pr** \n
//!  \f[ freqhz\_pr\ or\ v = \frac{X}{t_{2}-t_{1}} .......... 4\f] \n
//!  If \f[ \frac{max}{base}\ freq = 10kHz => 10kHz = \frac{(4/2)}{T} = \
\frac{4}{2T} \f] \n
//!  where,
//!    - 4 = QCAPCTL [UPPS] (Unit timeout - once every 4 edges)
//!    - 2 = divide by 2 because QPOSCNT counts 2 edges per cycle 
//!          (rising and falling)
//!    - T = time in seconds
//!        = \f$ \frac{t_{2}-t_{1}}{(150MHz/128)}, t_{2}-t_{1} \f$ = 
//!         # of QCAPCLK cycles,
//!        \n and \f$ 1\ QCAPCLK\ cycle = \frac{1}{(150MHz/128)} = QCPRDLAT \f$
//!
//!  So: \f[ 10 kHz = 4*\frac{(150MHz/128)}{2*(t_{2}-t_{1})} \f] \n
//!  \f[ t_{2}-t_{1} = 4*\frac{(150MHz/128)}{10kHz*2} = \
\frac{(150MHz/128)}{((2*10KHz)/4)} .......... 5\f] \n
//!  \f[ = 234\ QCAPCLK\ cycles = maximum (t_{2}-t_{1})  = freqScaler\_pr \f]
//!  Divide both sides by \f$ (t_{2}-t_{1}) \f$, and:\n
//!  \f[ 1 = \frac{234}{t_{2}-t_{1}} = \
\frac{(150MHz/128)/((2*10KHz)/4)}{t_{2}-t_{1}} \f]\n
//!  Because \f$ (t_{2}-t_{1}) < 234 (max) \f$,
//!  \f$ \frac{234}{t_{2}-t_{1}} < 1 \f$ for all frequencies less than max \n
//!  \f[ freq\_pr = \frac{234}{t_{2}-t_{1}}\ or\ \
\frac{(150MHz/128)/((2*10KHz)/4)}{t_{2}-t_{1}} .......... 6\f] \n
//!  Now within velocity limits, to get back to original velocity equation, 
//!  Equation 1, multiply Equation 6 by 10 kHz: \n
//!  \f[ freqhz\_fr(or\ velocity) = \
10kHz*\frac{(150MHz/128)/((2*10KHz)/4)}{t_{2}-t_{1}}\f]\n
//!  \f[ = \frac{(150MHz/128)*4}{2*(t_{2}-t_{1})} \f]\n
//!  or 
//!  \f[ \frac{4}{2*(t_{2}-t_{1})*(QCPRDLAT)} .......... final\ equation\f] \n
//!
//!  For 100 MHz Operation:
//!
//!  The same calculations as above are performed, but with 100 MHz
//!  instead of 150MHz when calculating freqhz_pr, and at UPPS of 8 
//!  instead of 4. The value for freqScaler_pr becomes: 
//!  (100MHz/128)/(2*10kHz/8) = 313
//!
//!  More detailed calculation results can be found in the Example_freqcal.xls
//!  spreadsheet included in the example folder.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
// FREQCAL_Init - 
//
void
FREQCAL_Init(void)
{
#if (CPU_FRQ_150MHZ)
    EQep1Regs.QUPRD=1500000;	// Unit Timer for 100Hz at 150MHz SYSCLKOUT
#endif
#if (CPU_FRQ_100MHZ)
    EQep1Regs.QUPRD=1000000;	// Unit Timer for 100Hz at 100MHz SYSCLKOUT
#endif

    EQep1Regs.QDECCTL.bit.QSRC=2;		// Up count mode (freq. measurement)
    EQep1Regs.QDECCTL.bit.XCR=0;        

    EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
    EQep1Regs.QEPCTL.bit.PCRM=00;		// QPOSCNT reset on index evnt
    EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timer Enable
    EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
    EQep1Regs.QPOSMAX=0xffffffff;
    EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

#if (CPU_FRQ_150MHZ)
    EQep1Regs.QCAPCTL.bit.UPPS=2;  // 1/4 for unit position at 150MHz SYSCLKOUT
#endif
#if (CPU_FRQ_100MHZ)
    EQep1Regs.QCAPCTL.bit.UPPS=3;  // 1/8 for unit position at 100MHz SYSCLKOUT
#endif

    EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
    EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable
}

//
// FREQCAL_Calc - 
//
void 
FREQCAL_Calc(FREQCAL *p)
{
    unsigned long tmp;
    _iq newp,oldp;

    //
    // Freq Calculation using QEP position counter
    // Check unit Time out-event for speed calculation
    //
    
    //
    // Unit Timer is configured for 100Hz in INIT function
    //

    //
    // For a more detailed explanation of the calculation, read
    // the description at the top of this file
    //
    if(EQep1Regs.QFLG.bit.UTO==1)  // Unit Timeout event
    {
        //
        // Differentiator
        //
        newp=EQep1Regs.QPOSLAT;         // Latched POSCNT value
        oldp=p->oldpos;

        if (newp>oldp)
        {
            tmp = newp - oldp;          // x2-x1 in v=(x2-x1)/T equation
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

        if (tmp>=_IQ(1))
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

        EQep1Regs.QCLR.bit.UTO=1;		// Clear interrupt flag
    }

    //
    // Freq Calculation using QEP capture counter
    //
    if(EQep1Regs.QEPSTS.bit.UPEVNT==1)        // Unit Position Event
    {
        if(EQep1Regs.QEPSTS.bit.COEF==0)      // No Capture overflow
        {
            tmp=(unsigned long)EQep1Regs.QCPRDLAT;
        }
        else	            // Capture overflow, saturate the result
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
// End of File
//

