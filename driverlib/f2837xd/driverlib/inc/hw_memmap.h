//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
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
#define ADCARESULT_BASE           0x00000B00U
#define ADCBRESULT_BASE           0x00000B20U
#define ADCCRESULT_BASE           0x00000B40U
#define ADCDRESULT_BASE           0x00000B60U
#define CPUTIMER0_BASE            0x00000C00U
#define CPUTIMER1_BASE            0x00000C08U
#define CPUTIMER2_BASE            0x00000C10U
#define CLA1_SOFTINT_BASE         0x00000CE0U
#define PIECTRL_BASE              0x00000CE0U
#define PIEVECTTABLE_BASE         0x00000D00U
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
#define CLB1_BASE                 0x00003000U
#define CLB1_LOGICCFG_BASE        0x00003000U
#define CLB1_LOGICCTL_BASE        0x00003100U
#define CLB1_DATAEXCH_BASE        0x00003200U
#define CLB2_BASE                 0x00003400U
#define CLB2_LOGICCFG_BASE        0x00003400U
#define CLB2_LOGICCTL_BASE        0x00003500U
#define CLB2_DATAEXCH_BASE        0x00003600U
#define CLB3_BASE                 0x00003800U
#define CLB3_LOGICCFG_BASE        0x00003800U
#define CLB3_LOGICCTL_BASE        0x00003900U
#define CLB3_DATAEXCH_BASE        0x00003A00U
#define CLB4_BASE                 0x00003C00U
#define CLB4_LOGICCFG_BASE        0x00003C00U
#define CLB4_LOGICCTL_BASE        0x00003D00U
#define CLB4_DATAEXCH_BASE        0x00003E00U
#define EPWM1_BASE                0x00004000U
#define EPWM2_BASE                0x00004100U
#define EPWM3_BASE                0x00004200U
#define EPWM4_BASE                0x00004300U
#define EPWM5_BASE                0x00004400U
#define EPWM6_BASE                0x00004500U
#define EPWM7_BASE                0x00004600U
#define EPWM8_BASE                0x00004700U
#define EPWM9_BASE                0x00004800U
#define EPWM10_BASE               0x00004900U
#define EPWM11_BASE               0x00004A00U
#define EPWM12_BASE               0x00004B00U
#define ECAP1_BASE                0x00005000U
#define ECAP2_BASE                0x00005020U
#define ECAP3_BASE                0x00005040U
#define ECAP4_BASE                0x00005060U
#define ECAP5_BASE                0x00005080U
#define ECAP6_BASE                0x000050A0U
#define EQEP1_BASE                0x00005100U
#define EQEP2_BASE                0x00005140U
#define EQEP3_BASE                0x00005180U
#define DACA_BASE                 0x00005C00U
#define DACB_BASE                 0x00005C10U
#define DACC_BASE                 0x00005C20U
#define CMPSS1_BASE               0x00005C80U
#define CMPSS2_BASE               0x00005CA0U
#define CMPSS3_BASE               0x00005CC0U
#define CMPSS4_BASE               0x00005CE0U
#define CMPSS5_BASE               0x00005D00U
#define CMPSS6_BASE               0x00005D20U
#define CMPSS7_BASE               0x00005D40U
#define CMPSS8_BASE               0x00005D60U
#define SDFM1_BASE                0x00005E00U
#define SDFM2_BASE                0x00005E80U
#define MCBSPA_BASE               0x00006000U
#define MCBSPB_BASE               0x00006040U
#define SPIA_BASE                 0x00006100U
#define SPIB_BASE                 0x00006110U
#define SPIC_BASE                 0x00006120U
#define UPP_BASE                  0x00006200U
#define UPP_TX_MSG_RAM_BASE       0x00006C00U
#define UPP_RX_MSG_RAM_BASE       0x00006E00U
#define WD_BASE                   0x00007000U
#define NMI_BASE                  0x00007060U
#define XINT_BASE                 0x00007070U
#define SCIA_BASE                 0x00007200U
#define SCIB_BASE                 0x00007210U
#define SCIC_BASE                 0x00007220U
#define SCID_BASE                 0x00007230U
#define I2CA_BASE                 0x00007300U
#define I2CB_BASE                 0x00007340U
#define ADCA_BASE                 0x00007400U
#define ADCB_BASE                 0x00007480U
#define ADCC_BASE                 0x00007500U
#define ADCD_BASE                 0x00007580U
#define INPUTXBAR_BASE            0x00007900U
#define XBAR_BASE                 0x00007920U
#define SYNCSOC_BASE              0x00007940U
#define DMACLASRCSEL_BASE         0x00007980U
#define EPWMXBAR_BASE             0x00007A00U
#define CLBXBAR_BASE              0x00007A40U
#define OUTPUTXBAR_BASE           0x00007A80U
#define GPIOCTRL_BASE             0x00007C00U
#define GPIODATA_BASE             0x00007F00U
#define LS0_RAM_BASE              0x00008000U
#define LS1_RAM_BASE              0x00008800U
#define LS2_RAM_BASE              0x00009000U
#define LS3_RAM_BASE              0x00009800U
#define LS4_RAM_BASE              0x0000A000U
#define LS5_RAM_BASE              0x0000A800U
#define D0_RAM_BASE               0x0000B000U
#define D1_RAM_BASE               0x0000B800U
#define GS0_RAM_BASE              0x0000C000U
#define GS1_RAM_BASE              0x0000D000U
#define GS2_RAM_BASE              0x0000E000U
#define GS3_RAM_BASE              0x0000F000U
#define GS4_RAM_BASE              0x00010000U
#define GS5_RAM_BASE              0x00011000U
#define GS6_RAM_BASE              0x00012000U
#define GS7_RAM_BASE              0x00013000U
#define GS8_RAM_BASE              0x00014000U
#define GS9_RAM_BASE              0x00015000U
#define GS10_RAM_BASE             0x00016000U
#define GS11_RAM_BASE             0x00017000U
#define GS12_RAM_BASE             0x00018000U
#define GS13_RAM_BASE             0x00019000U
#define GS14_RAM_BASE             0x0001A000U
#define GS15_RAM_BASE             0x0001B000U
#define CPU2_TO_CPU1_MSG_RAM_BASE 0x0003F800U
#define CPU1_TO_CPU2_MSG_RAM_BASE 0x0003FC00U
#define USBA_BASE                 0x00040000U
#define EMIF1_BASE                0x00047000U
#define EMIF2_BASE                0x00047800U
#define CANA_BASE                 0x00048000U
#define CANA_MSG_RAM_BASE         0x00049000U
#define CANB_BASE                 0x0004A000U
#define CANB_MSG_RAM_BASE         0x0004B000U
#define IPC_BASE                  0x00050000U
#define FLASHPUMPSEMAPHORE_BASE   0x00050024U
#define DEVCFG_BASE               0x0005D000U
#define ANALOGSUBSYS_BASE         0x0005D180U
#define CLKCFG_BASE               0x0005D200U
#define CPUSYS_BASE               0x0005D300U
#define ROMPREFETCH_BASE          0x0005E608U
#define DCSM_Z1_BASE              0x0005F000U
#define DCSM_Z2_BASE              0x0005F040U
#define DCSMCOMMON_BASE           0x0005F070U
#define MEMCFG_BASE               0x0005F400U
#define EMIF1CONFIG_BASE          0x0005F480U
#define EMIF2CONFIG_BASE          0x0005F4A0U
#define ACCESSPROTECTION_BASE     0x0005F4C0U
#define MEMORYERROR_BASE          0x0005F500U
#define ROMWAITSTATE_BASE         0x0005F540U
#define FLASH0CTRL_BASE           0x0005F800U
#define FLASH0ECC_BASE            0x0005FB00U
#define DCSM_Z1OTP_BASE           0x00078000U
#define DCSM_Z2OTP_BASE           0x00078200U
#define UID_BASE                  0x000703C0U
#endif
