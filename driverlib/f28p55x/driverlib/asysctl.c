//###########################################################################
//
// FILE:   asysctl.c
//
// TITLE:  C28x Driver for Analog System Control.
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

#include "asysctl.h"

//*****************************************************************************
//
// ASysCtl_setAnalogReferenceInternal
//
//*****************************************************************************
void
ASysCtl_setAnalogReferenceInternal(uint16_t reference)
{

    ASSERT((reference & (
                        ASYSCTL_ANAREF_INTREF_ADCA |
                        ASYSCTL_ANAREF_INTREF_ADCB |
                        ASYSCTL_ANAREF_INTREF_ADCC |
                        ASYSCTL_ANAREF_INTREF_ADCD |
                        ASYSCTL_ANAREF_INTREF_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &=
                                                ~((uint16_t)reference);

    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) &=
                                                ~((uint16_t)reference);

    EDIS;
}

//*****************************************************************************
//
// ASysCtl_setAnalogReferenceExternal
//
//*****************************************************************************
void
ASysCtl_setAnalogReferenceExternal(uint16_t reference)
{
    uint16_t refMask;

    ASSERT((reference & (
                         ASYSCTL_ANAREF_VREFHI_ADCA |
                         ASYSCTL_ANAREF_VREFHI_ADCB |
                         ASYSCTL_ANAREF_VREFHI_ADCC |
                         ASYSCTL_ANAREF_VREFHI_ADCD |
                         ASYSCTL_ANAREF_VREFHI_ADCE
                        )) == reference);

    refMask = (reference << 1) | reference;

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) =
                            (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &
                            ~refMask) | reference;

    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) =
                            (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) &
                            ~refMask) | reference;

    EDIS;

}

//*****************************************************************************
//
// ASysCtl_setAnalogReferenceVDDA
//
//*****************************************************************************
void
ASysCtl_setAnalogReferenceVDDA(uint16_t reference)
{

    ASSERT((reference & (
                        ASYSCTL_ANAREF_VDDA_ADCA |
                        ASYSCTL_ANAREF_VDDA_ADCB |
                        ASYSCTL_ANAREF_VDDA_ADCC |
                        ASYSCTL_ANAREF_VDDA_ADCD |
                        ASYSCTL_ANAREF_VDDA_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |= reference;

    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) |= reference;

    EDIS;

}
