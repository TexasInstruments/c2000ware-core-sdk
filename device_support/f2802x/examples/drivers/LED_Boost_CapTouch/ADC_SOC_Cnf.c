//###########################################################################
//
// FILE:        ADC_SOC_CNF.c.c
//
// Description: ADC configuration to support up to 16 conversions on 
//              Start of Conversion(SOC) based ADCs (type 3) found on F2802x  
//              and F3803x devices.  Independent selection of Channel, Trigger  
//              and acquisition window using ChSel[],TrigSel[] and ACQPS[].
//
// Dependencies:  Assumes the {DeviceName}-usDelay.asm is inlcuded in the 
//                project   
// Version:       3.0
//
// Target:   TMS320F2802x(PiccoloA), TMS320F2803x(PiccoloB), 
//
// The function call is: void ADC_SOC_CNF(int ChSel[], int Trigsel[], 
//                                        int ACQPS[], int IntChSel, int mode)
//
// Function arguments defined as:
//
// ChSel[]  = Channel selection made via a channel # array passed as an 
//            argument
// TrigSel[]= Source for triggering conversion of a channel, 
//            selection made via a trigger # array passed as argument
// ACQPS[]  = AcqWidth is the S/H aperture in #ADCCLKS, # array passed as 
//            argument
// IntChSel = Channel number that would trigger an ADC Interrupt 1 on 
//            completion(EOC) if no channel triggers ADC interrupt pass 
//            value > 15
// Mode     = Operating mode:     0 = Start / Stop mode, needs trigger event
//                                1 = Continuous mode, no trigger needed
//                                2 = CLA Mode, start stop mode with auto clr 
//                                    INT Flag
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include "DSP28x_Project.h"

//
// ADC_SOC_CNF - 
//
void ADC_SOC_CNF(int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, 
                 int mode)
{
    extern void DSP28x_usDelay(Uint32 Count);
 
    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCREFSEL   = 0;
    AdcRegs.ADCCTL1.bit.ADCBGPWD    = 1;    // Power up band gap
    AdcRegs.ADCCTL1.bit.ADCREFPWD   = 1;    // Power up reference
    AdcRegs.ADCCTL1.bit.ADCPWDN     = 1;    // Power up rest of ADC
    AdcRegs.ADCCTL1.bit.ADCENABLE   = 1;    // Enable ADC

    DSP28x_usDelay(1000);         // Delay before converting ADC channels

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    AdcRegs.ADCSOC0CTL.bit.ACQPS = ACQPS[0];
    AdcRegs.ADCSOC1CTL.bit.ACQPS = ACQPS[1];
    AdcRegs.ADCSOC2CTL.bit.ACQPS = ACQPS[2];
    AdcRegs.ADCSOC3CTL.bit.ACQPS = ACQPS[3];
    AdcRegs.ADCSOC4CTL.bit.ACQPS = ACQPS[4];
    AdcRegs.ADCSOC5CTL.bit.ACQPS = ACQPS[5];
    AdcRegs.ADCSOC6CTL.bit.ACQPS = ACQPS[6];
    AdcRegs.ADCSOC7CTL.bit.ACQPS = ACQPS[7];
    AdcRegs.ADCSOC8CTL.bit.ACQPS = ACQPS[8];
    AdcRegs.ADCSOC9CTL.bit.ACQPS = ACQPS[9];
    AdcRegs.ADCSOC10CTL.bit.ACQPS = ACQPS[10];
    AdcRegs.ADCSOC11CTL.bit.ACQPS = ACQPS[11];
    AdcRegs.ADCSOC12CTL.bit.ACQPS = ACQPS[12];
    AdcRegs.ADCSOC13CTL.bit.ACQPS = ACQPS[13];
    AdcRegs.ADCSOC14CTL.bit.ACQPS = ACQPS[14];
    AdcRegs.ADCSOC15CTL.bit.ACQPS = ACQPS[15];

    AdcRegs.INTSEL1N2.bit.INT1SEL = IntChSel; // IntChSel causes ADCInterrupt 1

    if (mode == 0)        // Start-Stop conv mode
    {
        AdcRegs.ADCINTFLG.bit.ADCINT1 = 0;  // clear interrupt flag for ADCINT1
        
        //
        // clear ADCINT1 flag to begin a new set of conversions
        //
        AdcRegs.INTSEL1N2.bit.INT1CONT = 0;
        
        AdcRegs.ADCINTSOCSEL1.all=0x0000;  // No ADCInterrupt will trigger SOCx
        AdcRegs.ADCINTSOCSEL2.all=0x0000;
    }
    
    if (mode == 1)        // Continuous conv mode
    {
        AdcRegs.INTSEL1N2.bit.INT1CONT = 1;   // set ADCInterrupt 1 to auto clr
        
        //
        // ADCInterrupt 1 will trigger SOCx, TrigSel is ignored
        //
        AdcRegs.ADCINTSOCSEL1.all=0xFF;
        
        AdcRegs.ADCINTSOCSEL2.all=0xFF;
    }

    if (mode == 2)        // CLA mode, Start Stop ADC with auto clr ADC Flag
    {
        AdcRegs.ADCINTFLG.bit.ADCINT1 = 0;  // clear interrupt flag for ADCINT1
        AdcRegs.INTSEL1N2.bit.INT1CONT = 1; // set ADCInterrupt 1 to auto clr
        AdcRegs.ADCINTSOCSEL1.all=0x0000;  // No ADCInterrupt will trigger SOCx
        AdcRegs.ADCINTSOCSEL2.all=0x0000;
    }

    if(IntChSel<15)
    {
        AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADC interrupt 1
    }
    else
    {
        AdcRegs.INTSEL1N2.bit.INT1E = 0;        // disable the ADC interrupt 1
    }

    //
    // Select the channel to be converted when SOCx is received
    //
    AdcRegs.ADCSOC0CTL.bit.CHSEL= ChSel[0];
    AdcRegs.ADCSOC1CTL.bit.CHSEL= ChSel[1];
    AdcRegs.ADCSOC2CTL.bit.CHSEL= ChSel[2];
    AdcRegs.ADCSOC3CTL.bit.CHSEL= ChSel[3];
    AdcRegs.ADCSOC4CTL.bit.CHSEL= ChSel[4];
    AdcRegs.ADCSOC5CTL.bit.CHSEL= ChSel[5];
    AdcRegs.ADCSOC6CTL.bit.CHSEL= ChSel[6];
    AdcRegs.ADCSOC7CTL.bit.CHSEL= ChSel[7];
    AdcRegs.ADCSOC8CTL.bit.CHSEL= ChSel[8];
    AdcRegs.ADCSOC9CTL.bit.CHSEL= ChSel[9];
    AdcRegs.ADCSOC10CTL.bit.CHSEL= ChSel[10];
    AdcRegs.ADCSOC11CTL.bit.CHSEL= ChSel[11];
    AdcRegs.ADCSOC12CTL.bit.CHSEL= ChSel[12];
    AdcRegs.ADCSOC13CTL.bit.CHSEL= ChSel[13];
    AdcRegs.ADCSOC14CTL.bit.CHSEL= ChSel[14];
    AdcRegs.ADCSOC15CTL.bit.CHSEL= ChSel[15];

    AdcRegs.ADCSOC0CTL.bit.TRIGSEL= Trigsel[0];
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL= Trigsel[1];
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL= Trigsel[2];
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL= Trigsel[3];
    AdcRegs.ADCSOC4CTL.bit.TRIGSEL= Trigsel[4];
    AdcRegs.ADCSOC5CTL.bit.TRIGSEL= Trigsel[5];
    AdcRegs.ADCSOC6CTL.bit.TRIGSEL= Trigsel[6];
    AdcRegs.ADCSOC7CTL.bit.TRIGSEL= Trigsel[7];
    AdcRegs.ADCSOC8CTL.bit.TRIGSEL= Trigsel[8];
    AdcRegs.ADCSOC9CTL.bit.TRIGSEL= Trigsel[9];
    AdcRegs.ADCSOC10CTL.bit.TRIGSEL= Trigsel[10];
    AdcRegs.ADCSOC11CTL.bit.TRIGSEL= Trigsel[11];
    AdcRegs.ADCSOC12CTL.bit.TRIGSEL= Trigsel[12];
    AdcRegs.ADCSOC13CTL.bit.TRIGSEL= Trigsel[13];
    AdcRegs.ADCSOC14CTL.bit.TRIGSEL= Trigsel[14];
    AdcRegs.ADCSOC15CTL.bit.TRIGSEL= Trigsel[15];
    EDIS;

    AdcRegs.ADCSOCFRC1.all = 0xFFFF;        // kick-start ADC
}

//
// End of File
//

