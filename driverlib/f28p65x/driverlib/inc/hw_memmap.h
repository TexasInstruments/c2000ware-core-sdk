//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
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

#ifndef HW_MEMMAP_H
#define HW_MEMMAP_H

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define M0_RAM_BASE               0x00000000U
#define M1_RAM_BASE               0x00000400U
#define ADCARESULT_BASE           0x00000A00U
#define ADCBRESULT_BASE           0x00000A80U
#define ADCCRESULT_BASE           0x00000B00U
#define CPUTIMER0_BASE            0x00000C00U
#define CLA1_ONLY_BASE            0x00000C00U
#define CPUTIMER1_BASE            0x00000C08U
#define CPUTIMER2_BASE            0x00000C10U
#define CLA1_SOFTINT_BASE         0x00000CE0U
#define PIECTRL_BASE              0x00000CE0U
#define PIEVECTTABLEMAIN_BASE     0x00000D00U
#define PIEVECTTABLEEXTENSION_BASE 0x00000E00U
#define DMA_BASE                  0x00001000U
#define DMA_CH1_BASE              0x00001020U
#define DMA_CH2_BASE              0x00001040U
#define DMA_CH3_BASE              0x00001060U
#define DMA_CH4_BASE              0x00001080U
#define DMA_CH5_BASE              0x000010A0U
#define DMA_CH6_BASE              0x000010C0U
#define CLA1_BASE                 0x00001400U
#define CLATOCPU_RAM_BASE         0x00001480U
#define CPUTOCLA_RAM_BASE         0x00001500U
#define CLATODMA_RAM_BASE         0x00001680U
#define DMATOCLA_RAM_BASE         0x00001700U
#define CLB1_BASE                 0x00002000U
#define CLB1_LOGICCFG_BASE        0x00002000U
#define CLB1_LOGICCTRL_BASE       0x00002100U
#define CLB1_DATAEXCH_BASE        0x00002180U
#define CLB2_BASE                 0x00002200U
#define CLB2_LOGICCFG_BASE        0x00002200U
#define CLB2_LOGICCTRL_BASE       0x00002300U
#define CLB2_DATAEXCH_BASE        0x00002380U
#define CLB3_BASE                 0x00002400U
#define CLB3_LOGICCFG_BASE        0x00002400U
#define CLB3_LOGICCTRL_BASE       0x00002500U
#define CLB3_DATAEXCH_BASE        0x00002580U
#define CLB4_BASE                 0x00002600U
#define CLB4_LOGICCFG_BASE        0x00002600U
#define CLB4_LOGICCTRL_BASE       0x00002700U
#define CLB4_DATAEXCH_BASE        0x00002780U
#define CLB5_BASE                 0x00002800U
#define CLB5_LOGICCFG_BASE        0x00002800U
#define CLB5_LOGICCTRL_BASE       0x00002900U
#define CLB5_DATAEXCH_BASE        0x00002980U
#define CLB6_BASE                 0x00002A00U
#define CLB6_LOGICCFG_BASE        0x00002A00U
#define CLB6_LOGICCTRL_BASE       0x00002B00U
#define CLB6_DATAEXCH_BASE        0x00002B80U
#define EPWM17_BASE               0x00002C00U
#define EPWM18_BASE               0x00002E00U
#define EPWM1_BASE                0x00003000U
#define EPWM2_BASE                0x00003200U
#define EPWM3_BASE                0x00003400U
#define EPWM4_BASE                0x00003600U
#define EPWM5_BASE                0x00003800U
#define EPWM6_BASE                0x00003A00U
#define EPWM7_BASE                0x00003C00U
#define EPWM8_BASE                0x00003E00U
#define EPWM9_BASE                0x00004000U
#define LS8_RAM_BASE              0x00004000U
#define EPWM10_BASE               0x00004200U
#define EPWM11_BASE               0x00004400U
#define EPWM12_BASE               0x00004600U
#define EPWM13_BASE               0x00004800U
#define EPWM14_BASE               0x00004A00U
#define EPWM15_BASE               0x00004C00U
#define EPWM16_BASE               0x00004E00U
#define EQEP1_BASE                0x00005080U
#define EQEP2_BASE                0x000050C0U
#define EQEP3_BASE                0x00005100U
#define EQEP4_BASE                0x00005140U
#define EQEP5_BASE                0x00005180U
#define EQEP6_BASE                0x000051C0U
#define ECAP1_BASE                0x00005200U
#define ECAP1SIGNALMONITORING_BASE 0x00005240U
#define ECAP2_BASE                0x00005300U
#define ECAP2SIGNALMONITORING_BASE 0x00005340U
#define ECAP3_BASE                0x00005400U
#define ECAP3SIGNALMONITORING_BASE 0x00005440U
#define ECAP4_BASE                0x00005500U
#define ECAP4SIGNALMONITORING_BASE 0x00005540U
#define ECAP5_BASE                0x00005600U
#define ECAP5SIGNALMONITORING_BASE 0x00005640U
#define ECAP6_BASE                0x00005700U
#define HRCAP6_BASE               0x00005720U
#define ECAP6SIGNALMONITORING_BASE 0x00005740U
#define ECAP7_BASE                0x00005800U
#define HRCAP7_BASE               0x00005820U
#define ECAP7SIGNALMONITORING_BASE 0x00005840U
#define CMPSS1_BASE               0x00005900U
#define CMPSS2_BASE               0x00005940U
#define CMPSS3_BASE               0x00005980U
#define CMPSS4_BASE               0x000059C0U
#define CMPSS5_BASE               0x00005A00U
#define CMPSS6_BASE               0x00005A40U
#define CMPSS7_BASE               0x00005A80U
#define CMPSS8_BASE               0x00005AC0U
#define CMPSS9_BASE               0x00005B00U
#define CMPSS10_BASE              0x00005B40U
#define CMPSS11_BASE              0x00005B80U
#define DACA_BASE                 0x00005C00U
#define DACC_BASE                 0x00005C20U
#define HRPWMCAL1_BASE            0x00005C80U
#define HRPWMCAL2_BASE            0x00005CC0U
#define HRPWMCAL3_BASE            0x00005D00U
#define SDFM1_BASE                0x00005E00U
#define SDFM2_BASE                0x00005E80U
#define SDFM3_BASE                0x00005F00U
#define SDFM4_BASE                0x00005F80U
#define LS9_RAM_BASE              0x00006000U
#define SPIA_BASE                 0x00006100U
#define SPIB_BASE                 0x00006110U
#define SPIC_BASE                 0x00006120U
#define SPID_BASE                 0x00006130U
#define BGCRC_CPU_BASE            0x00006340U
#define BGCRC_CLA1_BASE           0x00006380U
#define PMBUSA_BASE               0x00006400U
#define FSITXA_BASE               0x00006600U
#define FSIRXA_BASE               0x00006680U
#define FSITXB_BASE               0x00006700U
#define FSIRXB_BASE               0x00006780U
#define FSIRXC_BASE               0x00006880U
#define FSIRXD_BASE               0x00006980U
#define LINA_BASE                 0x00006E00U
#define LINB_BASE                 0x00006F00U
#define WD_BASE                   0x00007000U
#define NMI_BASE                  0x00007060U
#define XINT_BASE                 0x00007070U
#define SCIA_BASE                 0x00007200U
#define SCIB_BASE                 0x00007210U
#define I2CA_BASE                 0x00007300U
#define I2CB_BASE                 0x00007340U
#define ADCA_BASE                 0x00007400U
#define ADCB_BASE                 0x00007500U
#define ADCC_BASE                 0x00007600U
#define EPWMXBARB_BASE            0x00007800U
#define SYNCSOC_BASE              0x000078F8U
#define INPUTXBAR_BASE            0x00007900U
#define XBAR_BASE                 0x00007920U
#define CLBINPUTXBAR_BASE         0x00007960U
#define DMACLASRCSEL_BASE         0x00007980U
#define MINDBXBAR_BASE            0x000079C0U
#define ICLXBAR_BASE              0x000079E0U
#define EPWMXBARA_BASE            0x00007A00U
#define CLBXBAR_BASE              0x00007A80U
#define OUTPUTXBAR_BASE           0x00007B00U
#define CLBOUTPUTXBAR_BASE        0x00007B80U
#define GPIOCTRL_BASE             0x00007C00U
#define GPIODATA_BASE             0x00007F00U
#define GPIODATAREAD_BASE         0x00007F80U
#define LFU_BASE                  0x00007FE0U
#define D2_RAM_CPU2_BASE          0x00008000U
#define LS0_RAM_BASE              0x00008000U
#define LS1_RAM_BASE              0x00008800U
#define LS2_RAM_BASE              0x00009000U
#define LS3_RAM_BASE              0x00009800U
#define LS4_RAM_BASE              0x0000A000U
#define D3_RAM_CPU2_BASE          0x0000A000U
#define LS5_RAM_BASE              0x0000A800U
#define LS6_RAM_BASE              0x0000B000U
#define LS7_RAM_BASE              0x0000B800U
#define D4_RAM_CPU2_BASE          0x0000C000U
#define D0_RAM_BASE               0x0000C000U
#define D5_RAM_CPU2_BASE          0x0000E000U
#define D1_RAM_BASE               0x0000E000U
#define GS0_RAM_BASE              0x00010000U
#define GS1_RAM_BASE              0x00012000U
#define GS2_RAM_BASE              0x00014000U
#define GS3_RAM_BASE              0x00016000U
#define GS4_RAM_BASE              0x00018000U
#define D2_RAM_CPU1_BASE          0x0001A000U
#define D3_RAM_CPU1_BASE          0x0001C000U
#define D4_RAM_CPU1_BASE          0x0001E000U
#define D5_RAM_CPU1_BASE          0x00020000U
#define LS8_RAM_CPU1_BASE         0x00022000U
#define LS9_RAM_CPU1_BASE         0x00024000U
#define CPU1TOCPU2MSGRAM0_BASE    0x0003A000U
#define CPU2TOCPU1MSGRAM0_BASE    0x0003B000U
#define USBA_BASE                 0x00040000U
#define AESA_BASE                 0x00042000U
#define AESA_SS_BASE              0x00042C00U
#define EMIF1_BASE                0x00047000U
#define CANA_BASE                 0x00048000U
#define CANA_MSG_RAM_BASE         0x00049000U
#define LCM_CPU2_BASE             0x0004C800U
#define LCM_CPU2_DMA1_BASE        0x0004E800U
#define ESC_SS_BASE               0x00057E00U
#define ESC_SS_CONFIG_BASE        0x00057F00U
#define FLASH0CMD_BASE            0x00058000U
#define MCANA_DRIVER_BASE         0x00059000U
#define MCANA_MSG_RAM_BASE        0x00059000U
#define MCANASS_BASE              0x0005A400U
#define MCANA_BASE                0x0005A600U
#define MCANA_ERROR_BASE          0x0005A800U
#define MCANB_DRIVER_BASE         0x0005B000U
#define MCANB_MSG_RAM_BASE        0x0005B000U
#define MCANBSS_BASE              0x0005C400U
#define MCANB_BASE                0x0005C600U
#define MCANB_ERROR_BASE          0x0005C800U
#define IPC_CPUXTOCPUX_BASE       0x0005CE00U
#define IPC_CPUXTOCPUX_BASE       0x0005CE00U
#define DEVCFG_BASE               0x0005D000U
#define CLKCFG_BASE               0x0005D200U
#define CPUSYS_BASE               0x0005D300U
#define SYSSTAT_BASE              0x0005D400U
#define PERIPHAC_BASE             0x0005D500U
#define ANALOGSUBSYS_BASE         0x0005D700U
#define HWBIST_BASE               0x0005E000U
#define MPOST_BASE                0x0005E200U
#define DCC0_BASE                 0x0005E700U
#define DCC1_BASE                 0x0005E740U
#define DCC2_BASE                 0x0005E780U
#define ERAD_GLOBAL_BASE          0x0005E800U
#define ERAD_HWBP1_BASE           0x0005E900U
#define ERAD_HWBP2_BASE           0x0005E908U
#define ERAD_HWBP3_BASE           0x0005E910U
#define ERAD_HWBP4_BASE           0x0005E918U
#define ERAD_HWBP5_BASE           0x0005E920U
#define ERAD_HWBP6_BASE           0x0005E928U
#define ERAD_HWBP7_BASE           0x0005E930U
#define ERAD_HWBP8_BASE           0x0005E938U
#define ERAD_COUNTER1_BASE        0x0005E980U
#define ERAD_COUNTER2_BASE        0x0005E990U
#define ERAD_COUNTER3_BASE        0x0005E9A0U
#define ERAD_COUNTER4_BASE        0x0005E9B0U
#define ERAD_CRC_GLOBAL_BASE      0x0005EA00U
#define ERAD_CRC1_BASE            0x0005EA10U
#define ERAD_CRC2_BASE            0x0005EA20U
#define ERAD_CRC3_BASE            0x0005EA30U
#define ERAD_CRC4_BASE            0x0005EA40U
#define ERAD_CRC5_BASE            0x0005EA50U
#define ERAD_CRC6_BASE            0x0005EA60U
#define ERAD_CRC7_BASE            0x0005EA70U
#define ERAD_CRC8_BASE            0x0005EA80U
#define ERAD_PCTRACE_BASE         0x0005EAD0U
#define EPG1_BASE                 0x0005EC00U
#define EPG1MUX_BASE              0x0005ECD0U
#define ADCSAFETYINTEVTAGG1_BASE  0x0005EE00U
#define ADCSAFETYINTEVTAGG2_BASE  0x0005EE40U
#define ADCSAFETYCHK1_BASE        0x0005EE80U
#define ADCSAFETYCHK2_BASE        0x0005EE90U
#define ADCSAFETYCHK3_BASE        0x0005EEA0U
#define ADCSAFETYCHK4_BASE        0x0005EEB0U
#define ADCSAFETYCHK5_BASE        0x0005EEC0U
#define ADCSAFETYCHK6_BASE        0x0005EED0U
#define ADCSAFETYCHK7_BASE        0x0005EEE0U
#define ADCSAFETYCHK8_BASE        0x0005EEF0U
#define DCSM_Z1_BASE              0x0005F000U
#define DCSM_Z2_BASE              0x0005F080U
#define DCSMCOMMON_BASE           0x0005F0C0U
#define MEMCFG_BASE               0x0005F400U
#define EMIF1CONFIG_BASE          0x0005F4C0U
#define ACCESSPROTECTION_BASE     0x0005F500U
#define MEMORYERROR_BASE          0x0005F540U
#define ROMWAITSTATE_BASE         0x0005F580U
#define ROMPREFETCH_BASE          0x0005F588U
#define TESTERROR_BASE            0x0005F590U
#define FLASH0CTRL_BASE           0x0005F800U
#define FLASH0ECC_BASE            0x0005FB00U
#define ERAD_PCTRACE_CPU_BASE     0x0005FE00U
#define UARTA_BASE                0x0006A000U
#define UARTB_BASE                0x0006A800U
#define UID_BASE                  0x00072172U
#define DCSMBANK0_Z1OTP_BASE      0x00078000U
#define DCSMBANK0_Z2OTP_BASE      0x00078200U
#endif
