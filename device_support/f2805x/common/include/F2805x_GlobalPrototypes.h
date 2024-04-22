//###########################################################################
//
// FILE:   F2805x_GlobalPrototypes.h
//
// TITLE:  Global prototypes for F2805x Examples
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_GLOBALPROTOTYPES_H
#define F2805x_GLOBALPROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*---- shared global function prototypes -----------------------------------*/
extern void InitAdc(void);
extern void AdcOffsetSelfCal(void);
extern void AdcChanSelect(Uint16 ch_no);
extern Uint16 AdcConversion (void);
extern void InitAnalogSubsys(void);
extern void InitCTRIPGpio(void);
extern void InitCTRIPM1Gpio();
extern void InitCTRIPM2Gpio();
extern void InitCTRIPPFCGpio();
extern void InitPeripherals(void);
#if DSP28_ECANA
extern void InitECan(void);
extern void InitECana(void);
extern void InitECanGpio(void);
extern void InitECanaGpio(void);
#endif // endif DSP28_ECANA
extern void InitECap(void);
extern void InitECapGpio(void);
extern void InitECap1Gpio(void);
extern void InitEPwm(void);
extern void InitEPwmGpio(void);
extern void InitEPwm1Gpio(void);
extern void InitEPwm2Gpio(void);
extern void InitEPwm3Gpio(void);
#if DSP28_EPWM4
extern void InitEPwm4Gpio(void);
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
extern void InitEPwm5Gpio(void);
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
extern void InitEPwm6Gpio(void);
#endif // endif DSP28_EPWM6
#if DSP28_EPWM7
extern void InitEPwm7Gpio(void);
#endif // endif DSP28_EPWM7
#if DSP28_EQEP1
extern void InitEQep(void);
extern void InitEQepGpio(void);
extern void InitEQep1Gpio(void);
#endif // endif DSP28_EQEP1
extern void InitGpio(void);
extern void InitI2CGpio(void);

extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitSci(void);
extern void InitSciGpio(void);
extern void InitSciaGpio(void);
#if DSP28_SCIB
extern void InitScibGpio(void);
#endif // endif SCIB
#if DSP28_SCIC
extern void InitScicGpio(void);
#endif // endif SCIC
extern void InitSpi(void);
extern void InitSpiGpio(void);
extern void InitSpiaGpio(void);
extern void InitSysCtrl(void);
extern void InitTzGpio(void);
extern void InitXIntrupt(void);
extern void InitPll(Uint16 pllcr, Uint16 clkindiv);
extern void InitPeripheralClocks(void);
extern void EnableInterrupts(void);
extern void DSP28x_usDelay(Uint32 Count);
#define KickDog ServiceDog     // For compatibility with previous versions
extern void ServiceDog(void);
extern void DisableDog(void);
extern Uint16 DcsmZ1Unlock(void);
extern Uint16 DcsmZ2Unlock(void);
extern void IntOsc1Sel (void);
extern void IntOsc2Sel (void);
extern void XtalOscSel (void);
extern void ExtOscSel (void);

extern int16 GetTemperatureC(int16 sensorSample); // returns temp in deg. C
extern int16 GetTemperatureK(int16 sensorSample); // returns temp in deg. K
extern void Osc1Comp(int16 sensorSample);
extern void Osc2Comp(int16 sensorSample);
extern Uint16 PgaComp(Uint16 pga_ch, Uint16 pga_gain, Uint16 adc_conv);

//
// DSP28_DBGIERasm
//
extern void SetDBGIER(Uint16 dbgier);

//
//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
//
extern void InitFlash(void);

//
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in Flash to a different RUN location in internal
// RAM or CLA RAM
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1funcsRunStart;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2805x_GLOBALPROTOTYPES_H

//
// End of file.
//
