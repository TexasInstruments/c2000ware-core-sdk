//###########################################################################
//
// FILE:   f28p55x_adc.c
//
// TITLE:  F28p55x Adc Support Functions.
//
//###########################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "f28p55x_device.h"
#include "f28p55x_examples.h"

//
// SetVREF - Set the resolution and signalmode for a given ADC. This will
//              ensure that the correct trim is loaded.
//
void SetVREF(int module, int mode, int ref)
{
    Uint16 *offset;  // pointer to offset trim location in OTP

    //
    // Set up pointer to offset trim in OTP for ADCA.
    //
    offset = (Uint16 *)((Uint32)0x72064U);

    EALLOW;

    //
    // Get offset trim from OTP and write it to the register for ADCA.
    //
    AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCB.
    //
    offset = (Uint16 *)((Uint32)0x72066U);

    //
    // Get offset trim from OTP and write it to the register for ADCB.
    //
    AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCC.
    //
    offset = (Uint16 *)((Uint32)0x72068U);

    //
    // Get offset trim from OTP and write it to the register for ADCC.
    //
    AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCD.
    //
    offset = (Uint16 *)((Uint32)0x7206AU);

    //
    // Get offset trim from OTP and write it to the register for ADCD.
    //
    AdcdRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCE.
    //
    offset = (Uint16 *)((Uint32)0x7206CU);

    //
    // Get offset trim from OTP and write it to the register for ADCE.
    //
    AdceRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Configure the reference mode for all ADCs.
    //
    if(mode == ADC_INTERNAL)
    {
        //
        // This Configures reference mode for ADCA (internal). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;
    }
    else if(mode == ADC_EXTERNAL)
    {
        //
        // This configures reference mode for ADCA (external). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;
    }
    else
    {
        //
        // This configures reference mode for ADCA (VDDA). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;        
    }


    //
    // Configure the reference voltage for all ADCs (3.3V or 2.5V).
    //
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFA1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFB1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFC1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFD1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFE1P65SEL = ref;

    EDIS;
}

//
// End of file
//
