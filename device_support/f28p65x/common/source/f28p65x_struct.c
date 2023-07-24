//###########################################################################
//
// FILE:    f28p65x_struct.c
//
// TITLE:   F28P65x SDFM structure
//
//###########################################################################
//
//
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

//
// Included Files
//
#include "f28p65x_device.h"
#include "f28p65x_struct.h"

//
// Globals
//
#if defined(CPU1)
volatile struct ADC_REGS *ADC[MAX_ADC] =
{   0, &AdcaRegs, &AdcbRegs,
       &AdccRegs};
#endif

volatile struct ECAP_REGS *ECAP[MAX_ECAP] =
{   0, &ECap1Regs, &ECap2Regs, &ECap3Regs,
       &ECap4Regs, &ECap5Regs, &ECap6Regs,
       &ECap7Regs };

volatile struct EPWM_REGS *EPWM[MAX_EPWM] =
{   0, &EPwm1Regs, &EPwm2Regs, &EPwm3Regs,
       &EPwm4Regs, &EPwm5Regs, &EPwm6Regs,
       &EPwm7Regs, &EPwm8Regs, &EPwm9Regs,
       &EPwm10Regs, &EPwm11Regs, &EPwm12Regs,
       &EPwm13Regs, &EPwm14Regs, &EPwm15Regs, 
       &EPwm16Regs };

volatile struct EQEP_REGS *EQEP[MAX_EQEP] =
{   0, &EQep1Regs, &EQep2Regs, &EQep3Regs };

volatile struct I2C_REGS *I2C[MAX_I2C] =
{   0, &I2caRegs ,&I2cbRegs };

volatile struct SPI_REGS *SPI[MAX_SPI] =
{   0, &SpiaRegs, &SpibRegs, &SpicRegs,
	   &SpicRegs };

volatile struct SDFM_REGS *SDFM[MAX_SDFM] =
{   0, &Sdfm1Regs, &Sdfm2Regs};

#if defined(CPU1)
volatile Uint16 *TRIP_SEL[MAX_TRIPSEL] =
{   0, &InputXbarRegs.INPUT1SELECT, &InputXbarRegs.INPUT2SELECT,
       &InputXbarRegs.INPUT3SELECT, &InputXbarRegs.INPUT4SELECT,
       &InputXbarRegs.INPUT5SELECT, &InputXbarRegs.INPUT6SELECT,
       &InputXbarRegs.INPUT7SELECT, &InputXbarRegs.INPUT8SELECT,
       &InputXbarRegs.INPUT9SELECT, &InputXbarRegs.INPUT10SELECT,
       &InputXbarRegs.INPUT11SELECT, &InputXbarRegs.INPUT12SELECT,
       &InputXbarRegs.INPUT13SELECT, &InputXbarRegs.INPUT14SELECT
};
#endif

//
// End of file
//
