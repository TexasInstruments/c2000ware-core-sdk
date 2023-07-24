//###########################################################################
//
// FILE:    f28p65x_globalvariabledefs.c
//
// TITLE:   f28p65x Global Variables and Data Section Pragmas.
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

#include "f28p65x_device.h"     // f28p65x Headerfile Include File

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
#pragma DATA_SECTION("AdccRegsFile")
#else
#pragma DATA_SECTION(AdccRegs,"AdccRegsFile");
#endif
volatile struct ADC_REGS AdccRegs;

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

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcSafetyIntEvtAgg1RegsFile")
#else
#pragma DATA_SECTION(AdcSafetyIntEvtAgg1Regs,"AdcSafetyIntEvtAgg1RegsFile");
#endif
volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyIntEvtAgg1Regs;
#endif // ifdef CPU1

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AdcSafetyIntEvtAgg2RegsFile")
#else
#pragma DATA_SECTION(AdcSafetyIntEvtAgg2Regs,"AdcSafetyIntEvtAgg2RegsFile");
#endif
volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyIntEvtAgg2Regs;
#endif // ifdef CPU2

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk1RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk1Regs,"ADCSafetyChk1RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk2RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk2Regs,"ADCSafetyChk2RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk3RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk3Regs,"ADCSafetyChk3RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk4RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk4Regs,"ADCSafetyChk4RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk5RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk5Regs,"ADCSafetyChk5RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk6RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk6Regs,"ADCSafetyChk6RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk7RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk7Regs,"ADCSafetyChk7RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ADCSafetyChk8RegsFile")
#else
#pragma DATA_SECTION(ADCSafetyChk8Regs,"ADCSafetyChk8RegsFile");
#endif
volatile struct ADC_SAFECHECK_REGS ADCSafetyChk8Regs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("AnalogSubsysRegsFile")
#else
#pragma DATA_SECTION(AnalogSubsysRegs,"AnalogSubsysRegsFile");
#endif
volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#endif // ifdef CPU1

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("BgcrcCpuRegsFile")
#else
#pragma DATA_SECTION(BgcrcCpuRegs,"BgcrcCpuRegsFile");
#endif
volatile struct BGCRC_REGS BgcrcCpuRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("BgcrcClaRegsFile")
#else
#pragma DATA_SECTION(BgcrcClaRegs,"BgcrcClaRegsFile");
#endif
volatile struct BGCRC_REGS BgcrcClaRegs;
#endif // ifdef CPU1

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CanaRegsFile")
#else
#pragma DATA_SECTION(CanaRegs,"CanaRegsFile");
#endif
volatile struct CAN_REGS CanaRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cla1RegsFile")
#else
#pragma DATA_SECTION(Cla1Regs,"Cla1RegsFile");
#endif
volatile struct CLA_REGS Cla1Regs;
#endif // ifdef CPU1

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
#pragma DATA_SECTION("Clb3DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb3DataExchRegs,"Clb3DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb3DataExchRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb4DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb4DataExchRegs,"Clb4DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb4DataExchRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb5DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb5DataExchRegs,"Clb5DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb5DataExchRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb6DataExchRegsFile")
#else
#pragma DATA_SECTION(Clb6DataExchRegs,"Clb6DataExchRegsFile");
#endif
volatile struct CLB_DATA_EXCHANGE_REGS Clb6DataExchRegs;

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
#pragma DATA_SECTION("Clb3LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb3LogicCfgRegs,"Clb3LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb4LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb4LogicCfgRegs,"Clb4LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb5LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb5LogicCfgRegs,"Clb5LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb5LogicCfgRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb6LogicCfgRegsFile")
#else
#pragma DATA_SECTION(Clb6LogicCfgRegs,"Clb6LogicCfgRegsFile");
#endif
volatile struct CLB_LOGIC_CONFIG_REGS Clb6LogicCfgRegs;

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
#pragma DATA_SECTION("Clb3LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb3LogicCtrlRegs,"Clb3LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb4LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb4LogicCtrlRegs,"Clb4LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb5LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb5LogicCtrlRegs,"Clb5LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb5LogicCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Clb6LogicCtrlRegsFile")
#else
#pragma DATA_SECTION(Clb6LogicCtrlRegs,"Clb6LogicCtrlRegsFile");
#endif
volatile struct CLB_LOGIC_CONTROL_REGS Clb6LogicCtrlRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbXbarRegsFile")
#else
#pragma DATA_SECTION(ClbXbarRegs,"ClbXbarRegsFile");
#endif
volatile struct CLB_XBAR_REGS ClbXbarRegs;
#endif // ifdef CPU1

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
#pragma DATA_SECTION("Cmpss5RegsFile")
#else
#pragma DATA_SECTION(Cmpss5Regs,"Cmpss5RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss6RegsFile")
#else
#pragma DATA_SECTION(Cmpss6Regs,"Cmpss6RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss7RegsFile")
#else
#pragma DATA_SECTION(Cmpss7Regs,"Cmpss7RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss8RegsFile")
#else
#pragma DATA_SECTION(Cmpss8Regs,"Cmpss8RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss8Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss9RegsFile")
#else
#pragma DATA_SECTION(Cmpss9Regs,"Cmpss9RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss9Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss10RegsFile")
#else
#pragma DATA_SECTION(Cmpss10Regs,"Cmpss10RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss10Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cmpss11RegsFile")
#else
#pragma DATA_SECTION(Cmpss11Regs,"Cmpss11RegsFile");
#endif
volatile struct CMPSS_REGS Cmpss11Regs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cpu1toCpu2IpcRegsFile")
#else
#pragma DATA_SECTION(Cpu1toCpu2IpcRegs,"Cpu1toCpu2IpcRegsFile");
#endif
volatile struct CPU1TOCPU2_IPC_REGS_CPU1VIEW Cpu1toCpu2IpcRegs;
#endif // ifdef CPU1

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Cpu2toCpu1IpcRegsFile")
#else
#pragma DATA_SECTION(Cpu2toCpu1IpcRegs,"Cpu2toCpu1IpcRegsFile");
#endif
volatile struct CPU1TOCPU2_IPC_REGS_CPU2VIEW Cpu2toCpu1IpcRegs;
#endif // ifdef CPU2

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DmaClaSrcSelRegsFile")
#else
#pragma DATA_SECTION(DmaClaSrcSelRegs,"DmaClaSrcSelRegsFile");
#endif
volatile struct CPU1_DMA_CLA_SRC_SEL_REGS DmaClaSrcSelRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LfuRegsFile")
#else
#pragma DATA_SECTION(LfuRegs,"LfuRegsFile");
#endif
volatile struct CPU1_LFU_REGS LfuRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PeriphAcRegsFile")
#else
#pragma DATA_SECTION(PeriphAcRegs,"PeriphAcRegsFile");
#endif
volatile struct CPU1_PERIPH_AC_REGS PeriphAcRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuSysRegsFile")
#else
#pragma DATA_SECTION(CpuSysRegs,"CpuSysRegsFile");
#endif
volatile struct CPU1_SYS_REGS CpuSysRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SysStatusRegsFile")
#else
#pragma DATA_SECTION(SysStatusRegs,"SysStatusRegsFile");
#endif
volatile struct CPU1_SYS_STATUS_REGS SysStatusRegs;
#endif // ifdef CPU1

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DmaClaSrcSelRegsFile")
#else
#pragma DATA_SECTION(DmaClaSrcSelRegs,"DmaClaSrcSelRegsFile");
#endif
volatile struct CPU2_DMA_CLA_SRC_SEL_REGS DmaClaSrcSelRegs;
#endif // ifdef CPU2

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LfuRegsFile")
#else
#pragma DATA_SECTION(LfuRegs,"LfuRegsFile");
#endif
volatile struct CPU2_LFU_REGS LfuRegs;
#endif // ifdef CPU2

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PeriphAcRegsFile")
#else
#pragma DATA_SECTION(PeriphAcRegs,"PeriphAcRegsFile");
#endif
volatile struct CPU2_PERIPH_AC_REGS PeriphAcRegs;
#endif // ifdef CPU2

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("CpuSysRegsFile")
#else
#pragma DATA_SECTION(CpuSysRegs,"CpuSysRegsFile");
#endif
volatile struct CPU2_SYS_REGS CpuSysRegs;
#endif // ifdef CPU2

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SysStatusRegsFile")
#else
#pragma DATA_SECTION(SysStatusRegs,"SysStatusRegsFile");
#endif
volatile struct CPU2_SYS_STATUS_REGS SysStatusRegs;
#endif // ifdef CPU2

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
#pragma DATA_SECTION("DacaRegsFile")
#else
#pragma DATA_SECTION(DacaRegs,"DacaRegsFile");
#endif
volatile struct DAC_REGS DacaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DaccRegsFile")
#else
#pragma DATA_SECTION(DaccRegs,"DaccRegsFile");
#endif
volatile struct DAC_REGS DaccRegs;

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
#pragma DATA_SECTION("Dcc2RegsFile")
#else
#pragma DATA_SECTION(Dcc2Regs,"Dcc2RegsFile");
#endif
volatile struct DCC_REGS Dcc2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmCommonRegsFile")
#else
#pragma DATA_SECTION(DcsmCommonRegs,"DcsmCommonRegsFile");
#endif
volatile struct DCSM_COMMON_REGS DcsmCommonRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("DcsmZ1RegsFile")
#else
#pragma DATA_SECTION(DcsmZ1Regs,"DcsmZ1RegsFile");
#endif
volatile struct DCSM_Z1_REGS DcsmZ1Regs;

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
#pragma DATA_SECTION("ECap3RegsFile")
#else
#pragma DATA_SECTION(ECap3Regs,"ECap3RegsFile");
#endif
volatile struct ECAP_REGS ECap3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap4RegsFile")
#else
#pragma DATA_SECTION(ECap4Regs,"ECap4RegsFile");
#endif
volatile struct ECAP_REGS ECap4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap5RegsFile")
#else
#pragma DATA_SECTION(ECap5Regs,"ECap5RegsFile");
#endif
volatile struct ECAP_REGS ECap5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap6RegsFile")
#else
#pragma DATA_SECTION(ECap6Regs,"ECap6RegsFile");
#endif
volatile struct ECAP_REGS ECap6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap7RegsFile")
#else
#pragma DATA_SECTION(ECap7Regs,"ECap7RegsFile");
#endif
volatile struct ECAP_REGS ECap7Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap1SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap1SignalMonitoringRegs,"ECap1SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap1SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap2SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap2SignalMonitoringRegs,"ECap2SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap2SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap3SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap3SignalMonitoringRegs,"ECap3SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap3SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap4SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap4SignalMonitoringRegs,"ECap4SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap4SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap5SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap5SignalMonitoringRegs,"ECap5SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap5SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap6SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap6SignalMonitoringRegs,"ECap6SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap6SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ECap7SignalMonitoringRegsFile")
#else
#pragma DATA_SECTION(ECap7SignalMonitoringRegs,"ECap7SignalMonitoringRegsFile");
#endif
volatile struct ECAP_SIGNAL_MONITORING ECap7SignalMonitoringRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Emif1ConfigRegsFile")
#else
#pragma DATA_SECTION(Emif1ConfigRegs,"Emif1ConfigRegsFile");
#endif
volatile struct EMIF1_CONFIG_REGS Emif1ConfigRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm17RegsFile")
#else
#pragma DATA_SECTION(EPwm17Regs,"EPwm17RegsFile");
#endif
volatile struct EPWM_REGS EPwm17Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm18RegsFile")
#else
#pragma DATA_SECTION(EPwm18Regs,"EPwm18RegsFile");
#endif
volatile struct EPWM_REGS EPwm18Regs;

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
#pragma DATA_SECTION("EPwm13RegsFile")
#else
#pragma DATA_SECTION(EPwm13Regs,"EPwm13RegsFile");
#endif
volatile struct EPWM_REGS EPwm13Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm14RegsFile")
#else
#pragma DATA_SECTION(EPwm14Regs,"EPwm14RegsFile");
#endif
volatile struct EPWM_REGS EPwm14Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm15RegsFile")
#else
#pragma DATA_SECTION(EPwm15Regs,"EPwm15RegsFile");
#endif
volatile struct EPWM_REGS EPwm15Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwm16RegsFile")
#else
#pragma DATA_SECTION(EPwm16Regs,"EPwm16RegsFile");
#endif
volatile struct EPWM_REGS EPwm16Regs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwmXbarBRegsFile")
#else
#pragma DATA_SECTION(EPwmXbarBRegs,"EPwmXbarBRegsFile");
#endif
volatile struct EPWM_XBAR_REGS EPwmXbarBRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EPwmXbarARegsFile")
#else
#pragma DATA_SECTION(EPwmXbarARegs,"EPwmXbarARegsFile");
#endif
volatile struct EPWM_XBAR_REGS EPwmXbarARegs;
#endif // ifdef CPU1

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
#pragma DATA_SECTION("EQep4RegsFile")
#else
#pragma DATA_SECTION(EQep4Regs,"EQep4RegsFile");
#endif
volatile struct EQEP_REGS EQep4Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EQep5RegsFile")
#else
#pragma DATA_SECTION(EQep5Regs,"EQep5RegsFile");
#endif
volatile struct EQEP_REGS EQep5Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EQep6RegsFile")
#else
#pragma DATA_SECTION(EQep6Regs,"EQep6RegsFile");
#endif
volatile struct EQEP_REGS EQep6Regs;

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
#pragma DATA_SECTION("EscssConfigRegsFile")
#else
#pragma DATA_SECTION(EscssConfigRegs,"EscssConfigRegsFile");
#endif
volatile struct ESCSS_CONFIG_REGS EscssConfigRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EscssRegsFile")
#else
#pragma DATA_SECTION(EscssRegs,"EscssRegsFile");
#endif
volatile struct ESCSS_REGS EscssRegs;

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
#pragma DATA_SECTION("FsiRxbRegsFile")
#else
#pragma DATA_SECTION(FsiRxbRegs,"FsiRxbRegsFile");
#endif
volatile struct FSI_RX_REGS FsiRxbRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiRxcRegsFile")
#else
#pragma DATA_SECTION(FsiRxcRegs,"FsiRxcRegsFile");
#endif
volatile struct FSI_RX_REGS FsiRxcRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiRxdRegsFile")
#else
#pragma DATA_SECTION(FsiRxdRegs,"FsiRxdRegsFile");
#endif
volatile struct FSI_RX_REGS FsiRxdRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiTxaRegsFile")
#else
#pragma DATA_SECTION(FsiTxaRegs,"FsiTxaRegsFile");
#endif
volatile struct FSI_TX_REGS FsiTxaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("FsiTxbRegsFile")
#else
#pragma DATA_SECTION(FsiTxbRegs,"FsiTxbRegsFile");
#endif
volatile struct FSI_TX_REGS FsiTxbRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("GpioCtrlRegsFile")
#else
#pragma DATA_SECTION(GpioCtrlRegs,"GpioCtrlRegsFile");
#endif
volatile struct GPIO_CTRL_REGS GpioCtrlRegs;
#endif // ifdef CPU1

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
#pragma DATA_SECTION("HRCap6RegsFile")
#else
#pragma DATA_SECTION(HRCap6Regs,"HRCap6RegsFile");
#endif
volatile struct HRCAP_REGS HRCap6Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("HRCap7RegsFile")
#else
#pragma DATA_SECTION(HRCap7Regs,"HRCap7RegsFile");
#endif
volatile struct HRCAP_REGS HRCap7Regs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("HwbistRegsFile")
#else
#pragma DATA_SECTION(HwbistRegs,"HwbistRegsFile");
#endif
volatile struct HWBIST_REGS HwbistRegs;
#endif // ifdef CPU1

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

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("IclXbarRegsFile")
#else
#pragma DATA_SECTION(IclXbarRegs,"IclXbarRegsFile");
#endif
volatile struct ICL_XBAR_REGS IclXbarRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("InputXbarRegsFile")
#else
#pragma DATA_SECTION(InputXbarRegs,"InputXbarRegsFile");
#endif
volatile struct INPUT_XBAR_REGS InputXbarRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbInputXbarRegsFile")
#else
#pragma DATA_SECTION(ClbInputXbarRegs,"ClbInputXbarRegsFile");
#endif
volatile struct INPUT_XBAR_REGS ClbInputXbarRegs;
#endif // ifdef CPU1

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LCMCPU2RegsFile")
#else
#pragma DATA_SECTION(LCMCPU2Regs,"LCMCPU2RegsFile");
#endif
volatile struct LCM_REGS LCMCPU2Regs;
#endif // ifdef CPU2

#ifdef CPU2
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LCMCPU2DMA1RegsFile")
#else
#pragma DATA_SECTION(LCMCPU2DMA1Regs,"LCMCPU2DMA1RegsFile");
#endif
volatile struct LCM_REGS LCMCPU2DMA1Regs;
#endif // ifdef CPU2

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LinaRegsFile")
#else
#pragma DATA_SECTION(LinaRegs,"LinaRegsFile");
#endif
volatile struct LIN_REGS LinaRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("LinbRegsFile")
#else
#pragma DATA_SECTION(LinbRegs,"LinbRegsFile");
#endif
volatile struct LIN_REGS LinbRegs;

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
#pragma DATA_SECTION("HRPWMCAL1RegsFile")
#else
#pragma DATA_SECTION(HRPWMCAL1Regs,"HRPWMCAL1RegsFile");
#endif
volatile struct HRPWMCAL_REGS HRPWMCAL1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("HRPWMCAL2RegsFile")
#else
#pragma DATA_SECTION(HRPWMCAL2Regs,"HRPWMCAL2RegsFile");
#endif
volatile struct HRPWMCAL_REGS HRPWMCAL2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("HRPWMCAL3RegsFile")
#else
#pragma DATA_SECTION(HRPWMCAL3Regs,"HRPWMCAL3RegsFile");
#endif
volatile struct HRPWMCAL_REGS HRPWMCAL3Regs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("OutputXbarRegsFile")
#else
#pragma DATA_SECTION(OutputXbarRegs,"OutputXbarRegsFile");
#endif
volatile struct OUTPUT_XBAR_EXT64_REGS OutputXbarRegs;
#endif // ifdef CPU1

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("ClbOutputXbarRegsFile")
#else
#pragma DATA_SECTION(ClbOutputXbarRegs,"ClbOutputXbarRegsFile");
#endif
volatile struct OUTPUT_XBAR_REGS ClbOutputXbarRegs;
#endif // ifdef CPU1

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("EradPCTraceRegsFile")
#else
#pragma DATA_SECTION(EradPCTraceRegs,"EradPCTraceRegsFile");
#endif
volatile struct PCTRACE_REGS EradPCTraceRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PieCtrlRegsFile")
#else
#pragma DATA_SECTION(PieCtrlRegs,"PieCtrlRegsFile");
#endif
volatile struct PIE_CTRL_REGS PieCtrlRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("PieVectTableMainFile")
#else
#pragma DATA_SECTION(PieVectTable,"PieVectTableMainFile");
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
#pragma DATA_SECTION("RomWaitStateRegsFile")
#else
#pragma DATA_SECTION(RomWaitStateRegs,"RomWaitStateRegsFile");
#endif
volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;

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
#pragma DATA_SECTION("Sdfm1RegsFile")
#else
#pragma DATA_SECTION(Sdfm1Regs,"Sdfm1RegsFile");
#endif
volatile struct SDFM_REGS Sdfm1Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Sdfm2RegsFile")
#else
#pragma DATA_SECTION(Sdfm2Regs,"Sdfm2RegsFile");
#endif
volatile struct SDFM_REGS Sdfm2Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Sdfm3RegsFile")
#else
#pragma DATA_SECTION(Sdfm3Regs,"Sdfm3RegsFile");
#endif
volatile struct SDFM_REGS Sdfm3Regs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("Sdfm4RegsFile")
#else
#pragma DATA_SECTION(Sdfm4Regs,"Sdfm4RegsFile");
#endif
volatile struct SDFM_REGS Sdfm4Regs;

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
#pragma DATA_SECTION("SpicRegsFile")
#else
#pragma DATA_SECTION(SpicRegs,"SpicRegsFile");
#endif
volatile struct SPI_REGS SpicRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SpidRegsFile")
#else
#pragma DATA_SECTION(SpidRegs,"SpidRegsFile");
#endif
volatile struct SPI_REGS SpidRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("SyncSocRegsFile")
#else
#pragma DATA_SECTION(SyncSocRegs,"SyncSocRegsFile");
#endif
volatile struct SYNC_SOC_REGS SyncSocRegs;
#endif // ifdef CPU1

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("TestErrorRegsFile")
#else
#pragma DATA_SECTION(TestErrorRegs,"TestErrorRegsFile");
#endif
volatile struct TEST_ERROR_REGS TestErrorRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("UartARegsFile")
#else
#pragma DATA_SECTION(UartARegs,"UartARegsFile");
#endif
volatile struct UART_REGS UartARegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("UartBRegsFile")
#else
#pragma DATA_SECTION(UartBRegs,"UartBRegsFile");
#endif
volatile struct UART_REGS UartBRegs;

//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("WdRegsFile")
#else
#pragma DATA_SECTION(WdRegs,"WdRegsFile");
#endif
volatile struct WD_REGS WdRegs;

#ifdef CPU1
//----------------------------------------
#ifdef __cplusplus
#pragma DATA_SECTION("XbarRegsFile")
#else
#pragma DATA_SECTION(XbarRegs,"XbarRegsFile");
#endif
volatile struct XBAR_REGS XbarRegs __attribute__((noblocked));
#endif // ifdef CPU1

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


