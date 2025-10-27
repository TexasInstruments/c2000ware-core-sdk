//###########################################################################
//
// FILE:    f28p55x_globalvariabledefs.c
//
// TITLE:   f28p55x Global Variables and Data Section Pragmas.
//
//###########################################################################
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

#include "f28p55x_device.h"     // f28p55x Headerfile Include File

//---------------------------------------------------------------------------
// Define Global Peripheral Variables:
//

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AccessProtectionRegsFile")
#else
#pragma DATA_SECTION(AccessProtectionRegs,"AccessProtectionRegsFile");
#endif
volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdccRegsFile")
#else
#pragma DATA_SECTION(AdccRegs,"AdccRegsFile");
#endif
volatile struct ADC_REGS AdccRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcdRegsFile")
#else
#pragma DATA_SECTION(AdcdRegs,"AdcdRegsFile");
#endif
volatile struct ADC_REGS AdcdRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdceRegsFile")
#else
#pragma DATA_SECTION(AdceRegs,"AdceRegsFile");
#endif
volatile struct ADC_REGS AdceRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcaRegsFile")
#else
#pragma DATA_SECTION(AdcaRegs,"AdcaRegsFile");
#endif
volatile struct ADC_REGS AdcaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcbRegsFile")
#else
#pragma DATA_SECTION(AdcbRegs,"AdcbRegsFile");
#endif
volatile struct ADC_REGS AdcbRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcaResultRegsFile")
#else
#pragma DATA_SECTION(AdcaResultRegs,"AdcaResultRegsFile");
#endif
volatile struct ADC_RESULT_REGS AdcaResultRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcbResultRegsFile")
#else
#pragma DATA_SECTION(AdcbResultRegs,"AdcbResultRegsFile");
#endif
volatile struct ADC_RESULT_REGS AdcbResultRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdccResultRegsFile")
#else
#pragma DATA_SECTION(AdccResultRegs,"AdccResultRegsFile");
#endif
volatile struct ADC_RESULT_REGS AdccResultRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcdResultRegsFile")
#else
#pragma DATA_SECTION(AdcdResultRegs,"AdcdResultRegsFile");
#endif
volatile struct ADC_RESULT_REGS AdcdResultRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdceResultRegsFile")
#else
#pragma DATA_SECTION(AdceResultRegs,"AdceResultRegsFile");
#endif
volatile struct ADC_RESULT_REGS AdceResultRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AesaRegsFile")
#else
#pragma DATA_SECTION(AesaRegs,"AesaRegsFile");
#endif
volatile struct AES_REGS AesaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AesaSsRegsFile")
#else
#pragma DATA_SECTION(AesaSsRegs,"AesaSsRegsFile");
#endif
volatile struct AES_SS_REGS AesaSsRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AnalogSubsysRegsFile")
#else
#pragma DATA_SECTION(AnalogSubsysRegs,"AnalogSubsysRegsFile");
#endif
volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cla1RegsFile")
#else
#pragma DATA_SECTION(Cla1Regs,"Cla1RegsFile");
#endif
volatile struct CLA_REGS Cla1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb1DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb1DataExchRegs,"Clb1DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb1DataExchRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb2DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb2DataExchRegs,"Clb2DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb2DataExchRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb1LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb1LogicCfgRegs,"Clb1LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb2LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb2LogicCfgRegs,"Clb2LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb1LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb1LogicCtrlRegs,"Clb1LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb2LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb2LogicCtrlRegs,"Clb2LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbXbarRegsFile")
#else
#pragma DATA_SECTION(ClbXbarRegs,"ClbXbarRegsFile");
#endif
volatile struct CLB_XBAR_REGS ClbXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClkCfgRegsFile")
#else
#pragma DATA_SECTION(ClkCfgRegs,"ClkCfgRegsFile");
#endif
volatile struct CLK_CFG_REGS ClkCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss1RegsFile")
#else
#pragma DATA_SECTION(Cmpss1Regs,"Cmpss1RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss2RegsFile")
#else
#pragma DATA_SECTION(Cmpss2Regs,"Cmpss2RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss3RegsFile")
#else
#pragma DATA_SECTION(Cmpss3Regs,"Cmpss3RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss4RegsFile")
#else
#pragma DATA_SECTION(Cmpss4Regs,"Cmpss4RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuTimer0RegsFile")
#else
#pragma DATA_SECTION(CpuTimer0Regs,"CpuTimer0RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer0Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuTimer1RegsFile")
#else
#pragma DATA_SECTION(CpuTimer1Regs,"CpuTimer1RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuTimer2RegsFile")
#else
#pragma DATA_SECTION(CpuTimer2Regs,"CpuTimer2RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuSysRegsFile")
#else
#pragma DATA_SECTION(CpuSysRegs,"CpuSysRegsFile");
#endif
volatile struct CPU_SYS_REGS CpuSysRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DacaRegsFile")
#else
#pragma DATA_SECTION(DacaRegs,"DacaRegsFile");
#endif
volatile struct DAC_REGS DacaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Dcc0RegsFile")
#else
#pragma DATA_SECTION(Dcc0Regs,"Dcc0RegsFile");
#endif
volatile struct DCC_REGS Dcc0Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Dcc1RegsFile")
#else
#pragma DATA_SECTION(Dcc1Regs,"Dcc1RegsFile");
#endif
volatile struct DCC_REGS Dcc1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmCommonRegsFile")
#else
#pragma DATA_SECTION(DcsmCommonRegs,"DcsmCommonRegsFile");
#endif
volatile struct DCSM_COMMON_REGS DcsmCommonRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmZ1OtpRegsFile")
#else
#pragma DATA_SECTION(DcsmZ1OtpRegs,"DcsmZ1OtpRegsFile");
#endif
volatile struct DCSM_Z1_OTP DcsmZ1OtpRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmZ1RegsFile")
#else
#pragma DATA_SECTION(DcsmZ1Regs,"DcsmZ1RegsFile");
#endif
volatile struct DCSM_Z1_REGS DcsmZ1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmZ2OtpRegsFile")
#else
#pragma DATA_SECTION(DcsmZ2OtpRegs,"DcsmZ2OtpRegsFile");
#endif
volatile struct DCSM_Z2_OTP DcsmZ2OtpRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmZ2RegsFile")
#else
#pragma DATA_SECTION(DcsmZ2Regs,"DcsmZ2RegsFile");
#endif
volatile struct DCSM_Z2_REGS DcsmZ2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DevCfgRegsFile")
#else
#pragma DATA_SECTION(DevCfgRegs,"DevCfgRegsFile");
#endif
volatile struct DEV_CFG_REGS DevCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DmaClaSrcSelRegsFile")
#else
#pragma DATA_SECTION(DmaClaSrcSelRegs,"DmaClaSrcSelRegsFile");
#endif
volatile struct DMA_CLA_SRC_SEL_REGS DmaClaSrcSelRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DmaRegsFile")
#else
#pragma DATA_SECTION(DmaRegs,"DmaRegsFile");
#endif
volatile struct DMA_REGS DmaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap1RegsFile")
#else
#pragma DATA_SECTION(ECap1Regs,"ECap1RegsFile");
#endif
volatile struct ECAP_REGS ECap1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap2RegsFile")
#else
#pragma DATA_SECTION(ECap2Regs,"ECap2RegsFile");
#endif
volatile struct ECAP_REGS ECap2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Epg1MuxRegsFile")
#else
#pragma DATA_SECTION(Epg1MuxRegs,"Epg1MuxRegsFile");
#endif
volatile struct EPG_MUX_REGS Epg1MuxRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Epg1RegsFile")
#else
#pragma DATA_SECTION(Epg1Regs,"Epg1RegsFile");
#endif
volatile struct EPG_REGS Epg1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm1RegsFile")
#else
#pragma DATA_SECTION(EPwm1Regs,"EPwm1RegsFile");
#endif
volatile struct EPWM_REGS EPwm1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm2RegsFile")
#else
#pragma DATA_SECTION(EPwm2Regs,"EPwm2RegsFile");
#endif
volatile struct EPWM_REGS EPwm2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm3RegsFile")
#else
#pragma DATA_SECTION(EPwm3Regs,"EPwm3RegsFile");
#endif
volatile struct EPWM_REGS EPwm3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm4RegsFile")
#else
#pragma DATA_SECTION(EPwm4Regs,"EPwm4RegsFile");
#endif
volatile struct EPWM_REGS EPwm4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm5RegsFile")
#else
#pragma DATA_SECTION(EPwm5Regs,"EPwm5RegsFile");
#endif
volatile struct EPWM_REGS EPwm5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm6RegsFile")
#else
#pragma DATA_SECTION(EPwm6Regs,"EPwm6RegsFile");
#endif
volatile struct EPWM_REGS EPwm6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm7RegsFile")
#else
#pragma DATA_SECTION(EPwm7Regs,"EPwm7RegsFile");
#endif
volatile struct EPWM_REGS EPwm7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm8RegsFile")
#else
#pragma DATA_SECTION(EPwm8Regs,"EPwm8RegsFile");
#endif
volatile struct EPWM_REGS EPwm8Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm9RegsFile")
#else
#pragma DATA_SECTION(EPwm9Regs,"EPwm9RegsFile");
#endif
volatile struct EPWM_REGS EPwm9Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm10RegsFile")
#else
#pragma DATA_SECTION(EPwm10Regs,"EPwm10RegsFile");
#endif
volatile struct EPWM_REGS EPwm10Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm11RegsFile")
#else
#pragma DATA_SECTION(EPwm11Regs,"EPwm11RegsFile");
#endif
volatile struct EPWM_REGS EPwm11Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm12RegsFile")
#else
#pragma DATA_SECTION(EPwm12Regs,"EPwm12RegsFile");
#endif
volatile struct EPWM_REGS EPwm12Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwmXbarRegsFile")
#else
#pragma DATA_SECTION(EPwmXbarRegs,"EPwmXbarRegsFile");
#endif
volatile struct EPWM_XBAR_REGS EPwmXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EQep1RegsFile")
#else
#pragma DATA_SECTION(EQep1Regs,"EQep1RegsFile");
#endif
volatile struct EQEP_REGS EQep1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EQep2RegsFile")
#else
#pragma DATA_SECTION(EQep2Regs,"EQep2RegsFile");
#endif
volatile struct EQEP_REGS EQep2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EQep3RegsFile")
#else
#pragma DATA_SECTION(EQep3Regs,"EQep3RegsFile");
#endif
volatile struct EQEP_REGS EQep3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCounter1RegsFile")
#else
#pragma DATA_SECTION(EradCounter1Regs,"EradCounter1RegsFile");
#endif
volatile struct ERAD_COUNTER_REGS EradCounter1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCounter2RegsFile")
#else
#pragma DATA_SECTION(EradCounter2Regs,"EradCounter2RegsFile");
#endif
volatile struct ERAD_COUNTER_REGS EradCounter2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCounter3RegsFile")
#else
#pragma DATA_SECTION(EradCounter3Regs,"EradCounter3RegsFile");
#endif
volatile struct ERAD_COUNTER_REGS EradCounter3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCounter4RegsFile")
#else
#pragma DATA_SECTION(EradCounter4Regs,"EradCounter4RegsFile");
#endif
volatile struct ERAD_COUNTER_REGS EradCounter4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRCGlobalRegsFile")
#else
#pragma DATA_SECTION(EradCRCGlobalRegs,"EradCRCGlobalRegsFile");
#endif
volatile struct ERAD_CRC_GLOBAL_REGS EradCRCGlobalRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC1RegsFile")
#else
#pragma DATA_SECTION(EradCRC1Regs,"EradCRC1RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC2RegsFile")
#else
#pragma DATA_SECTION(EradCRC2Regs,"EradCRC2RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC3RegsFile")
#else
#pragma DATA_SECTION(EradCRC3Regs,"EradCRC3RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC4RegsFile")
#else
#pragma DATA_SECTION(EradCRC4Regs,"EradCRC4RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC5RegsFile")
#else
#pragma DATA_SECTION(EradCRC5Regs,"EradCRC5RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC6RegsFile")
#else
#pragma DATA_SECTION(EradCRC6Regs,"EradCRC6RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC7RegsFile")
#else
#pragma DATA_SECTION(EradCRC7Regs,"EradCRC7RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradCRC8RegsFile")
#else
#pragma DATA_SECTION(EradCRC8Regs,"EradCRC8RegsFile");
#endif
volatile struct ERAD_CRC_REGS EradCRC8Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradGlobalRegsFile")
#else
#pragma DATA_SECTION(EradGlobalRegs,"EradGlobalRegsFile");
#endif
volatile struct ERAD_GLOBAL_REGS EradGlobalRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP1RegsFile")
#else
#pragma DATA_SECTION(EradHWBP1Regs,"EradHWBP1RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP2RegsFile")
#else
#pragma DATA_SECTION(EradHWBP2Regs,"EradHWBP2RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP3RegsFile")
#else
#pragma DATA_SECTION(EradHWBP3Regs,"EradHWBP3RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP4RegsFile")
#else
#pragma DATA_SECTION(EradHWBP4Regs,"EradHWBP4RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP5RegsFile")
#else
#pragma DATA_SECTION(EradHWBP5Regs,"EradHWBP5RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP6RegsFile")
#else
#pragma DATA_SECTION(EradHWBP6Regs,"EradHWBP6RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP7RegsFile")
#else
#pragma DATA_SECTION(EradHWBP7Regs,"EradHWBP7RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradHWBP8RegsFile")
#else
#pragma DATA_SECTION(EradHWBP8Regs,"EradHWBP8RegsFile");
#endif
volatile struct ERAD_HWBP_REGS EradHWBP8Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Flash0CtrlRegsFile")
#else
#pragma DATA_SECTION(Flash0CtrlRegs,"Flash0CtrlRegsFile");
#endif
volatile struct FLASH_CTRL_REGS Flash0CtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Flash0EccRegsFile")
#else
#pragma DATA_SECTION(Flash0EccRegs,"Flash0EccRegsFile");
#endif
volatile struct FLASH_ECC_REGS Flash0EccRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiRxaRegsFile")
#else
#pragma DATA_SECTION(FsiRxaRegs,"FsiRxaRegsFile");
#endif
volatile struct FSI_RX_REGS FsiRxaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiTxaRegsFile")
#else
#pragma DATA_SECTION(FsiTxaRegs,"FsiTxaRegsFile");
#endif
volatile struct FSI_TX_REGS FsiTxaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("GpioCtrlRegsFile")
#else
#pragma DATA_SECTION(GpioCtrlRegs,"GpioCtrlRegsFile");
#endif
volatile struct GPIO_CTRL_REGS GpioCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("GpioDataReadRegsFile")
#else
#pragma DATA_SECTION(GpioDataReadRegs,"GpioDataReadRegsFile");
#endif
volatile struct GPIO_DATA_READ_REGS GpioDataReadRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("GpioDataRegsFile")
#else
#pragma DATA_SECTION(GpioDataRegs,"GpioDataRegsFile");
#endif
volatile struct GPIO_DATA_REGS GpioDataRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("I2caRegsFile")
#else
#pragma DATA_SECTION(I2caRegs,"I2caRegsFile");
#endif
volatile struct I2C_REGS I2caRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("I2cbRegsFile")
#else
#pragma DATA_SECTION(I2cbRegs,"I2cbRegsFile");
#endif
volatile struct I2C_REGS I2cbRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("InputXbarRegsFile")
#else
#pragma DATA_SECTION(InputXbarRegs,"InputXbarRegsFile");
#endif
volatile struct INPUT_XBAR_REGS InputXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbInputXbarRegsFile")
#else
#pragma DATA_SECTION(ClbInputXbarRegs,"ClbInputXbarRegsFile");
#endif
volatile struct INPUT_XBAR_REGS ClbInputXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LfuRegsFile")
#else
#pragma DATA_SECTION(LfuRegs,"LfuRegsFile");
#endif
volatile struct LFU_REGS LfuRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LinaRegsFile")
#else
#pragma DATA_SECTION(LinaRegs,"LinaRegsFile");
#endif
volatile struct LIN_REGS LinaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanaSsRegsFile")
#else
#pragma DATA_SECTION(McanaSsRegs,"McanaSsRegsFile");
#endif
volatile struct MCANSS_REGS McanaSsRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanbSsRegsFile")
#else
#pragma DATA_SECTION(McanbSsRegs,"McanbSsRegsFile");
#endif
volatile struct MCANSS_REGS McanbSsRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanaErrorRegsFile")
#else
#pragma DATA_SECTION(McanaErrorRegs,"McanaErrorRegsFile");
#endif
volatile struct MCAN_ERROR_REGS McanaErrorRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanbErrorRegsFile")
#else
#pragma DATA_SECTION(McanbErrorRegs,"McanbErrorRegsFile");
#endif
volatile struct MCAN_ERROR_REGS McanbErrorRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanaRegsFile")
#else
#pragma DATA_SECTION(McanaRegs,"McanaRegsFile");
#endif
volatile struct MCAN_REGS McanaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("McanbRegsFile")
#else
#pragma DATA_SECTION(McanbRegs,"McanbRegsFile");
#endif
volatile struct MCAN_REGS McanbRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("MemoryErrorRegsFile")
#else
#pragma DATA_SECTION(MemoryErrorRegs,"MemoryErrorRegsFile");
#endif
volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("MemCfgRegsFile")
#else
#pragma DATA_SECTION(MemCfgRegs,"MemCfgRegsFile");
#endif
volatile struct MEM_CFG_REGS MemCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("NmiIntruptRegsFile")
#else
#pragma DATA_SECTION(NmiIntruptRegs,"NmiIntruptRegsFile");
#endif
volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("OutputXbarRegsFile")
#else
#pragma DATA_SECTION(OutputXbarRegs,"OutputXbarRegsFile");
#endif
volatile struct OUTPUT_XBAR_REGS OutputXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbOutputXbarRegsFile")
#else
#pragma DATA_SECTION(ClbOutputXbarRegs,"ClbOutputXbarRegsFile");
#endif
volatile struct OUTPUT_XBAR_REGS ClbOutputXbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradPCTraceBufferRegsFile")
#else
#pragma DATA_SECTION(EradPCTraceBufferRegs,"EradPCTraceBufferRegsFile");
#endif
volatile struct PCTRACE_BUFFER_REGS EradPCTraceBufferRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradPCTraceRegsFile")
#else
#pragma DATA_SECTION(EradPCTraceRegs,"EradPCTraceRegsFile");
#endif
volatile struct PCTRACE_REGS EradPCTraceRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PeriphAcRegsFile")
#else
#pragma DATA_SECTION(PeriphAcRegs,"PeriphAcRegsFile");
#endif
volatile struct PERIPH_AC_REGS PeriphAcRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Pga1RegsFile")
#else
#pragma DATA_SECTION(Pga1Regs,"Pga1RegsFile");
#endif
volatile struct PGA_REGS Pga1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Pga2RegsFile")
#else
#pragma DATA_SECTION(Pga2Regs,"Pga2RegsFile");
#endif
volatile struct PGA_REGS Pga2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Pga3RegsFile")
#else
#pragma DATA_SECTION(Pga3Regs,"Pga3RegsFile");
#endif
volatile struct PGA_REGS Pga3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PieCtrlRegsFile")
#else
#pragma DATA_SECTION(PieCtrlRegs,"PieCtrlRegsFile");
#endif
volatile struct PIE_CTRL_REGS PieCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PieVectTableFile")
#else
#pragma DATA_SECTION(PieVectTable,"PieVectTableFile");
#endif
volatile struct PIE_VECT_TABLE PieVectTable;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PmbusaRegsFile")
#else
#pragma DATA_SECTION(PmbusaRegs,"PmbusaRegsFile");
#endif
volatile struct PMBUS_REGS PmbusaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SciaRegsFile")
#else
#pragma DATA_SECTION(SciaRegs,"SciaRegsFile");
#endif
volatile struct SCI_REGS SciaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ScibRegsFile")
#else
#pragma DATA_SECTION(ScibRegs,"ScibRegsFile");
#endif
volatile struct SCI_REGS ScibRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ScicRegsFile")
#else
#pragma DATA_SECTION(ScicRegs,"ScicRegsFile");
#endif
volatile struct SCI_REGS ScicRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SpiaRegsFile")
#else
#pragma DATA_SECTION(SpiaRegs,"SpiaRegsFile");
#endif
volatile struct SPI_REGS SpiaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SpibRegsFile")
#else
#pragma DATA_SECTION(SpibRegs,"SpibRegsFile");
#endif
volatile struct SPI_REGS SpibRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SyncSocRegsFile")
#else
#pragma DATA_SECTION(SyncSocRegs,"SyncSocRegsFile");
#endif
volatile struct SYNC_SOC_REGS SyncSocRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SysStatusRegsFile")
#else
#pragma DATA_SECTION(SysStatusRegs,"SysStatusRegsFile");
#endif
volatile struct SYS_STATUS_REGS SysStatusRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("TestErrorRegsFile")
#else
#pragma DATA_SECTION(TestErrorRegs,"TestErrorRegsFile");
#endif
volatile struct TEST_ERROR_REGS TestErrorRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("UidRegsFile")
#else
#pragma DATA_SECTION(UidRegs,"UidRegsFile");
#endif
volatile struct UID_REGS UidRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("WdRegsFile")
#else
#pragma DATA_SECTION(WdRegs,"WdRegsFile");
#endif
volatile struct WD_REGS WdRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("XbarRegsFile")
#else
#pragma DATA_SECTION(XbarRegs,"XbarRegsFile");
#endif
volatile struct XBAR_REGS XbarRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("XintRegsFile")
#else
#pragma DATA_SECTION(XintRegs,"XintRegsFile");
#endif
volatile struct XINT_REGS XintRegs;



//===========================================================================
// End of file.
//===========================================================================


