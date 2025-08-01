//###########################################################################
//
// FILE:   f28p65x_globalprototypes.h
//
// TITLE:  Global prototypes for F28P65X Examples
//
//###########################################################################
//
//
// 
// C2000Ware v6.00.00.00
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

#ifndef F28P65X_GLOBALPROTOTYPES_H
#define F28P65X_GLOBALPROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Function Prototypes (Shared)
//
extern void EnableInterrupts(void);
extern void InitAPwm1Gpio(void);
extern void InitCAN(void);
extern void InitECap(void);
extern void InitECapGpio(void);
extern void InitECap1Gpio(Uint16 pin);
extern void InitECap2Gpio(Uint16 pin);
extern void InitECap3Gpio(Uint16 pin);
extern void InitECap4Gpio(Uint16 pin);
extern void InitECap5Gpio(Uint16 pin);
extern void InitECap6Gpio(Uint16 pin);
extern void InitECap7Gpio(Uint16 pin);
extern void InitEQep1Gpio(void);
extern void InitEQep2Gpio(void);
extern void InitEQep3Gpio(void);
extern void InitEPwmGpio(void);
extern void InitEPwm1Gpio(void);
extern void InitEPwm2Gpio(void);
extern void InitEPwm3Gpio(void);
extern void InitEPwm4Gpio(void);
extern void InitEPwm5Gpio(void);
extern void InitEPwm6Gpio(void);
extern void InitEPwm7Gpio(void);
extern void InitEPwm8Gpio(void);
extern void InitEPwm9Gpio(void);
extern void InitEPwm10Gpio(void);
extern void InitEPwm11Gpio(void);
extern void InitEPwm12Gpio(void);
extern void InitEPwm13Gpio(void);
extern void InitEPwm14Gpio(void);
extern void InitEPwm15Gpio(void);
extern void InitEPwm16Gpio(void);
extern void InitPeripheralClocks(void);
extern void DisablePeripheralClocks(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitSysCtrl(void);
#ifdef CPU1
extern void InitSysPll(Uint16 clock_source, Uint16 imult, Uint32 refdiv, Uint32 odiv,
                       Uint16 divsel, Uint32 dccbase);
#if 0
extern void InitAuxPll(Uint16 clock_source,  Uint16 imult, Uint32 refdiv, Uint32 odiv,
                       Uint16 divsel, Uint32 dccbase);
#endif
extern bool IsPLLValid(Uint32 base, Uint16 oscSource, Uint16 pllclk, Uint16 imult,
                       Uint16 odiv, Uint16 refdiv);
extern bool VerifyXTAL(float freq);
extern void ComputeCntrSeedValue(Uint32 base, float fclk1_0ratio, Uint32 tolerance);
#endif
#define KickDog ServiceDog     // For compatibility with previous versions
extern void ServiceDog(void);
extern void DisableDog(void);

extern Uint16 CsmUnlock(void);
extern void SysIntOsc1Sel (void);
extern void SysIntOsc2Sel (void);
extern void SysXtalOscSel (void);
extern void SysXtalOscSESel (void);
extern void AuxIntOsc2Sel (void);
extern void AuxXtalOscSel (void);
extern void AuxAuxClkSel (void);
extern void AuxXtalOscSESel(void);

extern void SetDBGIER(Uint16 dbgier);

//
//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
//
extern void InitFlash(void);
extern void InitFlash_Bank0(void);
extern void InitFlash_Bank1(void);
extern void SeizeFlashPump(void);
extern void SeizeFlashPump_Bank0(void);
extern void SeizeFlashPump_Bank1(void);
extern void ReleaseFlashPump(void);

//
//LPM functions in f28p65x_sysctrl.c
//
void IDLE();
void STANDBY();
void HALT();

//
//ADC functions
//
extern void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode);
extern void CalAdcINL(Uint16 adc);

//
// DMA Functions
//
extern void DMAInitialize(void);

//
// DMA Channel 1
//
extern void DMACH1AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH1AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH1BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH1TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH1WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH1ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH1(void);

//
// DMA Channel 2
//
extern void DMACH2AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH2AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH2BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH2TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH2WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH2ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH2(void);

//
// DMA Channel 3
//
extern void DMACH3AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH3AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH3BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH3TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH3WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH3ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH3(void);

//
// DMA Channel 4
//
extern void DMACH4AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH4AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH4BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH4TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH4WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH4ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH4(void);

//
// DMA Channel 5
//
extern void DMACH5AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH5AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH5BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH5TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH5WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH5ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH5(void);

//
// DMA Channel 6
//
extern void DMACH6AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH6AddrConfig32bit(volatile Uint32 *DMA_Dest,
                                  volatile Uint32 *DMA_Source);
extern void DMACH6BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH6TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH6WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH6ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH6(void);

//
//GPIO Functions
//
extern void InitGpio();
extern void GPIO_SetupPinMux(Uint16 gpioNumber, Uint16 cpu, Uint16 muxPosition);
extern void GPIO_SetupPinOptions(Uint16 gpioNumber, Uint16 output, Uint16 flags);
extern void GPIO_SetupLock(Uint16 gpioNumber, Uint16 flags);
extern void GPIO_SetupXINT1Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT2Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT3Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT4Gpio(Uint16 gpioNumber);
extern void GPIO_SetupXINT5Gpio(Uint16 gpioNumber);
extern void GPIO_SelectIpcInt(Uint16 newFlag);
Uint16 GPIO_ReadPin(Uint16 gpioNumber);
void GPIO_WritePin(Uint16 gpioNumber, Uint16 outVal);


//
// CAN Functions
//
extern void CanGpioPinMuxing(Uint32 ulBase, Uint16 canTxRxPin);
extern void CanAGpioConfig(Uint16 canaTxRxPin);
extern void CanBGpioConfig(Uint16 canbTxRxPin);
extern void CanModuleClkSelect(Uint32 ulBase, Uint16 ucSource);

//
// I2C Functions
//
extern void I2cAGpioConfig(Uint16 I2caDataClkPin);
extern void I2cBGpioConfig(Uint16 I2cbDataClkPin);

//
// McBSP functions
// McBSPA
//
extern void InitMcbspa(void);
extern void InitMcbspaInt(void);
extern void InitMcbspa8bit(void);
extern void InitMcbspa12bit(void);
extern void InitMcbspa16bit(void);
extern void InitMcbspa20bit(void);
extern void InitMcbspa24bit(void);
extern void InitMcbspa32bit(void);
extern void InitMcbspaGpio(void);
extern void delay_loop(void);

//
// McBSPB
//
extern void InitMcbspb(void);
extern void InitMcbspbInt(void);
extern void InitMcbspb8bit(void);
extern void InitMcbspb12bit(void);
extern void InitMcbspb16bit(void);
extern void InitMcbspb20bit(void);
extern void InitMcbspb24bit(void);
extern void InitMcbspb32bit(void);
extern void InitMcbspbGpio(void);

//
// Temp Sensor Functions
//
extern void InitTempSensor(float32 vrefhi_voltage);

//
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

//
// External Boot ROM variable definitions
//
extern Uint16 EmuBMode;
extern Uint16 EmuBootPins;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F28P65X_GLOBALPROTOTYPES_H

//
// End of file
//
