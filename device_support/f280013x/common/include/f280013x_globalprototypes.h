//###########################################################################
//
// FILE:   f280013x_globalprototypes.h
//
// TITLE:  Global prototypes for f280013x Examples
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F280013x_GLOBALPROTOTYPES_H
#define F280013x_GLOBALPROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// shared global function prototypes
//
extern void EnableInterrupts(void);
extern void InitPeripheralClocks(void);
extern void DisablePeripheralClocks(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitSpi(void);
extern void InitSpiGpio(void);
extern void InitSpiaGpio(void);
extern void InitSysCtrl(void);
extern void InitSysPll(Uint16 clock_source, Uint16 imult, Uint32 refdiv, Uint32 odiv,
                       Uint16 divsel, Uint32 dccbase);
extern bool IsPLLValid(Uint32 base, Uint16 oscSource, Uint16 pllclk, Uint16 imult,
                       Uint16 odiv, Uint16 refdiv);
extern void ComputeCntrSeedValue(Uint32 base, float fclk1_0ratio, Uint32 tolerance);

//
// For compatibility with previous versions
//
#define KickDog ServiceDog
extern void ServiceDog(void);
extern void DisableDog(void);

extern Uint16 CsmUnlock(void);
extern void SysIntOsc1Sel (void);
extern void SysIntOsc2Sel (void);
extern void SysXtalOscSel (void);
extern void SysXtalOscSESel (void);

//
//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
//
extern void InitFlash(void);
extern void FlashOff(void);

//
// LPM functions in f280013x_sysctrl.c
//
void IDLE(void);
void HALT(void);

//
// ADC functions
//
extern void SetVREF(int module, int mode, int ref);

//
// GPIO Functions
//
extern void InitGpio(void);
extern void GPIO_SetupPinMux(Uint16 gpioNumber, Uint16 cpu,
                             Uint16 muxPosition);
extern void GPIO_SetupPinOptions(Uint16 gpioNumber, Uint16 output,
                                 Uint16 flags);
extern void GPIO_SetupLock(Uint16 gpioNumber, Uint16 flags);
extern void GPIO_SetupXINT1Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT2Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT3Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT4Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT5Gpio(Uint16 gpioNumber);
Uint16 GPIO_ReadPin(Uint16 gpioNumber);
void GPIO_WritePin(Uint16 gpioNumber, Uint16 outVal);

// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in Flash to a different RUN location in internal
// RAM
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsRunEnd;
extern Uint16 RamfuncsRunSize;


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F280013x_GLOBALPROTOTYPES_H

//
// End of file.
//
