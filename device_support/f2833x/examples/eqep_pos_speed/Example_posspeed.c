//###########################################################################
//
// FILE:	Example_posspeed.c
//
// TITLE:	EXAMPLE_POSSPEED_C Position/Speed Calculation 
//
//! \addtogroup f2833x_example_list
//! \section EXAMPLE_POSSPEED_C Position/Speed Calculation (Example_posspeed.c)
//! This file includes the EQEP initialization and position and speed 
//! calculation functions called by Example_2833xEqep_posspeed.c.  The position
//! and speed calculation steps performed by POSSPEED_Calc() at  
//! SYSCLKOUT =  150 MHz and 100 MHz are described below:
//!
//! -# This program calculates: \b **theta_mech** for SYSCLKOUT = 150Mhz \n
//! \f[ theta\_mech\ = \frac{QPOSCNT}{mech\_scaler}= \frac {QPOSCNT}{4000} \f]
//! where 4000 is the number of
//! counts in 1 revolution.(4000/4 = 1000 line/rev. quadrature encoder)
//! -# This program calculates: \b **theta_elec** for SYSCLKOUT = 150MHz \n
//! \f[ theta\_elec\ = (# pole pairs) * theta\_mech\ = \
\frac {2*QPOSCNT}{4000} \f]
//! -# This program calculates: \b **SpeedRpm_fr** for SYSCLKOUT = 150Mhz \n
//! \f[ SpeedRpm\_fr\ = \frac {x_{2}-x_{1}}{4000*T}........1 \f]
//!
//! \note \f$ x_{2}-x_{1} \f$ is the difference in number of QPOSCNT counts. 
//! Dividing \f$ x_{2}-x_{1} \f$ by
//! \f$ 4000 \f$ gives position relative to Index in one revolution. \n
//!
//! If \f$ base RPM  = 6000 rpm \f$ :
//! \f[ 6000 rpm = \frac {x_{2}-x_{1}}{4000*10ms}........2 \f]
//! \f[ = \frac {\frac{x_{2}-x_{1}}{4000}}{\frac {.01s*1 min}{60 sec}} \f]
//! \f[ = \frac {\frac {x_{2}-x_{1}}{4000}}{\frac {1}{6000} min} \f]
//! max \f$ x_{2}-x_{1} = 4000 \f$ counts, or 1 revolution in 10 ms
//!
//! If both sides of Equation 2 are divided by 6000 rpm, then:
//! \f[ 1 =\frac {\frac {x_{2}-x_{1}}{4000}rev.}{\frac {1}{6000}min*6000rpm}\f]
//! Because \f$ x_{2}-x_{1} \f$ must be \f$ <4000 (max) \f$  for 
//! QPOSCNT increment, \f$ \frac {x_{2}-x_{1}}{4000} < 1 \f$ for CW rotation \n
//! And because \f$ x_{2}-x_{1} \f$ must be \f$ >-4000 \f$ for 
//! QPOSCNT decrement, \f$ \frac {x_{2}-x_{1}}{4000}>-1 \f$ for CCW rotation
//! \f[ speed\_fr\ = \
\frac {\frac {x_{2}-x_{1}}{4000}}{\frac{1}{6000} min * 6000rpm} = \
\frac {x_{2}-x{1}}{4000}........3 \f]
//!
//! To convert speed_fr to RPM, multiply Equation 3 by 6000 rpm
//! \f[ SpeedRpm\_fr\ = 6000rpm * \frac {x_{2}-x_{1}}{4000}.........final \f]\n
//!
//! -# **min rpm ** = selected at 10 rpm based on CCPS prescaler options 
//!    available (128 is greatest)
//! -# **SpeedRpm_pr**
//! \f[ SpeedRpm\_pr\ = \frac {X}{t_2-t_1}.........4 \f]
//! where X = QCAPCTL [UPPS]/4000 rev. 
//! (position relative to Index in 1 revolution)
//!
//! If \f$ \frac {max}{base}speed= 6000 rpm:  6000 = \
\frac {\frac {32}{4000}}{\frac {t_2-t_1}{\frac {150MHz}{128}}} \f$
//! where,
//! - 32 = QCAPCTL [UPPS] (Unit timeout - once every 32 edges)
//! - \f$ \frac {32}{4000} = \f$ position in 1 revolution 
//!   (position as a fraction of 1 revolution)
//!
//! - \f$ \frac {t_2-t_1}{\frac{150MHz}{128}}, t_2-t_1 =\f$ # of QCAPCLK cycles
//! - 1 QCAPCLK cycle = \f$ \frac {1}{\frac {150MHz}{128}} \f$ = QCPRDLAT
//!
//! So:\f[ 6000 rpm = \frac{32 \frac {150MHz}{128}* 60s/min}{4000(t_2-t_1)} \f]
//! \f[ t_2-t_1 = \
\frac {32 \frac {150MHz}{128}*60 s/min}{4000*6000rpm}..........5 \f]
//! \f[ = 94 CAPCLK cycles = maximum (t2-t1) = SpeedScaler \f]
//! Divide both sides by \f$ t_2-t_1 \f$, and: \n
//! \f[ 1 = \frac {94}{t_2-t_1} = \
\frac {\frac {32 \frac {150MHz}{128}*60 s/min}{4000*6000rpm}}{t_2-t_1} \f]
//! Because \f$ t_2-t_1 \f$ must be \f$ < 94 \f$ for QPOSCNT increment:
//! \f$ \frac {94}{t_2-t_1} < 1 \f$ for CW rotation \n
//! And because \f$ t_2-t_1 \f$ must be \f$ >-94 \f$ for QPOSCNT decrement:
//! \f$ \frac {94}{t_2-t_1}> -1 \f$ for CCW rotation
//! \f[ speed_pr = \frac {94}{t_2-t_1} \f] or \f[ \
\frac {\frac {32 \frac {150MHz}{128}*60 s/min}{(4000*6000rpm)}}{t_2-t_1}........6\f]
//!
//! To convert speed_pr to RPM: \n
//! Multiply Equation 6 by 6000rpm:
//! \f[ SpeedRpm\_fr  = 6000rpm * \
\frac {\frac {32 \frac {150MHz}{128}*60 s/min}{(4000*6000rpm)}}{t_2-t_1} \f]
//! \f[ = \frac {32 \frac {150MHz}{128}*60 s/min}{4000*(t_2-t_1)} \f]
//! or \f[ \frac {\frac {32}{4000rev} * 60 s/min}{(t_2-t_1)(QCPRDLAT)}\
............Final Equation \f]
//!
//! For 100 MHz Operation:
//! The same calculations as above are performed, but with 100 MHz
//! instead of 150MHz when calculating SpeedRpm_pr. \n
//! The value for freqScaler_pr becomes: 
//! [32*(100MHz/128)*60s/min]/(4000*6000rpm) = 63 \n
//! More detailed calculation results can be found in the Example_freqcal.xls
//! spreadsheet included in the example folder.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "Example_posspeed.h"   // Example specific Include file

//
// POSSPEED_Init - 
//
void
POSSPEED_Init(void)
{
    #if (CPU_FRQ_150MHZ)
        EQep1Regs.QUPRD=1500000;  // Unit Timer for 100Hz at 150 MHz SYSCLKOUT
	#endif
    #if (CPU_FRQ_100MHZ)
        EQep1Regs.QUPRD=1000000;  // Unit Timer for 100Hz at 100 MHz SYSCLKOUT
	#endif

	EQep1Regs.QDECCTL.bit.QSRC=00;		// QEP quadrature count mode

	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
	
    //
    // PCRM=00 mode - QPOSCNT reset on index event
    //
    EQep1Regs.QEPCTL.bit.PCRM=00;
    
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep1Regs.QPOSMAX=0xffffffff;
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	EQep1Regs.QCAPCTL.bit.UPPS=5;   	// 1/32 for unit position
	EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable
}

//
// POSSPEED_Calc -
// 
void 
POSSPEED_Calc(POSSPEED *p)
{
    long tmp;
    unsigned int pos16bval,temp1;
    _iq Tmp1,newp,oldp;

    //
    // Position calculation - mechanical and electrical motor angle
    //
    
    //
    // Motor direction: 0=CCW/reverse, 1=CW/forward
    //
    p->DirectionQep = EQep1Regs.QEPSTS.bit.QDF;

    //
    // capture position once per QA/QB period
    //
    pos16bval=(unsigned int)EQep1Regs.QPOSCNT;
    
    //
    // raw theta = current pos. + ang. offset from QA
    //
    p->theta_raw = pos16bval+ p->cal_angle;

    //
    // The following lines calculate p->theta_mech ~= 
    // QPOSCNT/mech_scaler [current cnt/(total cnt in 1 rev.)]
    // where mech_scaler = 4000 cnts/revolution
    //
    tmp = (long)((long)p->theta_raw*(long)p->mech_scaler);  // Q0*Q26 = Q26
    tmp &= 0x03FFF000;
    p->theta_mech = (int)(tmp>>11);         		// Q26 -> Q15
    p->theta_mech &= 0x7FFF;

    //
    // The following lines calculate p->elec_mech
    //
    p->theta_elec = p->pole_pairs*p->theta_mech;    // Q0*Q15 = Q15
    p->theta_elec &= 0x7FFF;

    //
    // Check an index occurrence
    //
    if (EQep1Regs.QFLG.bit.IEL == 1)
    {
        p->index_sync_flag = 0x00F0;
        EQep1Regs.QCLR.bit.IEL=1;					// Clear interrupt flag
    }

    //
    // High Speed Calculation using QEP Position counter
    // Check unit Time out-event for speed calculation:
    // Unit Timer is configured for 100Hz in INIT function
    //
    if(EQep1Regs.QFLG.bit.UTO==1)      // If unit timeout (one 100Hz period)
    {
        //
        // Differentiator
        // The following lines calculate position = 
        // (x2-x1)/4000 (position in 1 revolution)
        //
        pos16bval=(unsigned int)EQep1Regs.QPOSLAT;	    // Latched POSCNT value
        tmp = (long)((long)pos16bval*(long)p->mech_scaler); // Q0*Q26 = Q26
        tmp &= 0x03FFF000;
        tmp = (int)(tmp>>11);           // Q26 -> Q15
        tmp &= 0x7FFF;
        newp=_IQ15toIQ(tmp);
        oldp=p->oldpos;

        if (p->DirectionQep==0)      	// POSCNT is counting down
        {
            if (newp>oldp)
            {
                Tmp1 = - (_IQ(1) - newp + oldp);    // x2-x1 should be negative
            }
            else
            {
                Tmp1 = newp -oldp;
            }
        }
        else if (p->DirectionQep==1)    // POSCNT is counting up
        {
            if (newp<oldp)
            {
                Tmp1 = _IQ(1) + newp - oldp;
            }
            else
            {
                Tmp1 = newp - oldp;     // x2-x1 should be positive
            }
        }

        if (Tmp1>_IQ(1))
        {
            p->Speed_fr = _IQ(1);
        }
        else if (Tmp1<_IQ(-1))
        {
            p->Speed_fr = _IQ(-1);
        }
        else
        {
            p->Speed_fr = Tmp1;
        }

        //
        // Update the electrical angle
        //
        p->oldpos = newp;

        //
        // Change motor speed from pu value to rpm value (Q15 -> Q0)
        // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
        //
        p->SpeedRpm_fr = _IQmpy(p->BaseRpm,p->Speed_fr);
        
        EQep1Regs.QCLR.bit.UTO=1;					// Clear interrupt flag
    }

    //
    // Low-speed computation using QEP capture counter
    //
    if(EQep1Regs.QEPSTS.bit.UPEVNT==1)     // Unit position event
    {
        if(EQep1Regs.QEPSTS.bit.COEF==0)   // No Capture overflow
        {
            temp1=(unsigned long)EQep1Regs.QCPRDLAT;   // temp1 = t2-t1
        }
        else   // Capture overflow, saturate the result
        {
            temp1=0xFFFF;
        }

        //
        // p->Speed_pr = p->SpeedScaler/temp1
        //
        p->Speed_pr = _IQdiv(p->SpeedScaler,temp1);
        Tmp1=p->Speed_pr;

        if (Tmp1>_IQ(1))
        {
            p->Speed_pr = _IQ(1);
        }
        else
        {
            p->Speed_pr = Tmp1;
        }
        
        //
        // Convert p->Speed_pr to RPM
        //
        if (p->DirectionQep==0)     // Reverse direction = negative
        {
            //
            // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
            //
            p->SpeedRpm_pr = -_IQmpy(p->BaseRpm,p->Speed_pr);
        }
        else                        // Forward direction = positive
        {
            //
            // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
            //
            p->SpeedRpm_pr = _IQmpy(p->BaseRpm,p->Speed_pr);
        }

        EQep1Regs.QEPSTS.all=0x88;	// Clear Unit position event flag
                                    // Clear overflow error flag
    }
}

//
// End of File
//

