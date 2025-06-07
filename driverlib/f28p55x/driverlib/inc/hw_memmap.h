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
#define CPUTIMER0_BASE            0x00000C00U     //CPUTIMER_REGS
#define CLA1_ONLY_BASE            0x00000C00U     //
#define CPUTIMER1_BASE            0x00000C08U     //CPUTIMER_REGS
#define CPUTIMER2_BASE            0x00000C10U     //CPUTIMER_REGS
#define CLA1_SOFTINT_BASE         0x00000CE0U     //
#define PIECTRL_BASE              0x00000CE0U     //PIE_CTRL_REGS
#define PIEVECTTABLE_BASE         0x00000D00U     //PIE_VECT_TABLE
#define DMA_BASE                  0x00001000U     //DMA_REGS
#define DMA_CH1_BASE              0x00001020U     //DMA_CH_REGS
#define DMA_CH2_BASE              0x00001040U     //DMA_CH_REGS
#define DMA_CH3_BASE              0x00001060U     //DMA_CH_REGS
#define DMA_CH4_BASE              0x00001080U     //DMA_CH_REGS
#define DMA_CH5_BASE              0x000010A0U     //DMA_CH_REGS
#define DMA_CH6_BASE              0x000010C0U     //DMA_CH_REGS
#define CLA1_BASE                 0x00001400U     //CLA_REGS
#define ADCARESULT_BASE           0x00001800U     //ADC_RESULT_REGS
#define ADCBRESULT_BASE           0x00001880U     //ADC_RESULT_REGS
#define ADCCRESULT_BASE           0x00001900U     //ADC_RESULT_REGS
#define ADCDRESULT_BASE           0x00001980U     //ADC_RESULT_REGS
#define ADCERESULT_BASE           0x00001A00U     //ADC_RESULT_REGS
#define CLB1_BASE                 0x00003000U
#define CLB1_LOGICCFG_BASE        0x00003000U     //CLB_LOGIC_CONFIG_REGS
#define CLB1_LOGICCTRL_BASE       0x00003100U     //CLB_LOGIC_CONTROL_REGS
#define CLB1_DATAEXCH_BASE        0x00003180U     //CLB_DATA_EXCHANGE_REGS
#define CLB2_BASE                 0x00003400U
#define CLB2_LOGICCFG_BASE        0x00003400U     //CLB_LOGIC_CONFIG_REGS
#define CLB2_LOGICCTRL_BASE       0x00003500U     //CLB_LOGIC_CONTROL_REGS
#define CLB2_DATAEXCH_BASE        0x00003580U     //CLB_DATA_EXCHANGE_REGS
#define LS8_RAM_BASE              0x00004000U
#define EPWM1_BASE                0x00004000U     //EPWM_REGS
#define EPWM2_BASE                0x00004100U     //EPWM_REGS
#define EPWM3_BASE                0x00004200U     //EPWM_REGS
#define EPWM4_BASE                0x00004300U     //EPWM_REGS
#define EPWM5_BASE                0x00004400U     //EPWM_REGS
#define EPWM6_BASE                0x00004500U     //EPWM_REGS
#define EPWM7_BASE                0x00004600U     //EPWM_REGS
#define EPWM8_BASE                0x00004700U     //EPWM_REGS
#define EPWM9_BASE                0x00004800U     //EPWM_REGS
#define EPWM10_BASE               0x00004900U     //EPWM_REGS
#define EPWM11_BASE               0x00004A00U     //EPWM_REGS
#define EPWM12_BASE               0x00004B00U     //EPWM_REGS
#define EQEP1_BASE                0x00005100U     //EQEP_REGS
#define EQEP2_BASE                0x00005140U     //EQEP_REGS
#define EQEP3_BASE                0x00005180U     //EQEP_REGS
#define ECAP1_BASE                0x00005200U     //ECAP_REGS
#define ECAP2_BASE                0x00005240U     //ECAP_REGS
#define CMPSS1_BASE               0x00005500U     //CMPSS_REGS
#define CMPSS2_BASE               0x00005540U     //CMPSS_REGS
#define CMPSS3_BASE               0x00005580U     //CMPSS_REGS
#define CMPSS4_BASE               0x000055C0U     //CMPSS_REGS
#define PGA1_BASE                 0x00005B00U     //PGA_REGS
#define PGA2_BASE                 0x00005B10U     //PGA_REGS
#define PGA3_BASE                 0x00005B20U     //PGA_REGS
#define DACA_BASE                 0x00005C00U     //DAC_REGS
#define LS9_RAM_BASE              0x00006000U
#define SPIA_BASE                 0x00006100U     //SPI_REGS
#define SPIB_BASE                 0x00006110U     //SPI_REGS
#define PMBUSA_BASE               0x00006400U     //PMBUS_REGS
#define FSITXA_BASE               0x00006600U     //FSI_TX_REGS
#define FSIRXA_BASE               0x00006680U     //FSI_RX_REGS
#define LINA_BASE                 0x00006800U     //LIN_REGS
#define ADCC_BASE                 0x00006A00U     //ADC_REGS
#define ADCD_BASE                 0x00006C00U     //ADC_REGS
#define ADCE_BASE                 0x00006E00U     //ADC_REGS
#define WD_BASE                   0x00007000U     //WD_REGS
#define NMI_BASE                  0x00007060U     //NMI_INTRUPT_REGS
#define XINT_BASE                 0x00007070U     //XINT_REGS
#define SCIA_BASE                 0x00007200U     //SCI_REGS
#define SCIB_BASE                 0x00007210U     //SCI_REGS
#define SCIC_BASE                 0x00007220U     //SCI_REGS
#define I2CA_BASE                 0x00007300U     //I2C_REGS
#define I2CB_BASE                 0x00007340U     //I2C_REGS
#define ADCA_BASE                 0x00007400U     //ADC_REGS
#define ADCB_BASE                 0x00007600U     //ADC_REGS
#define INPUTXBAR_BASE            0x00007900U     //INPUT_XBAR_REGS
#define XBAR_BASE                 0x00007920U     //XBAR_REGS
#define SYNCSOC_BASE              0x00007940U     //SYNC_SOC_REGS
#define CLBINPUTXBAR_BASE         0x00007960U     //INPUT_XBAR_REGS
#define DMACLASRCSEL_BASE         0x00007980U     //DMA_CLA_SRC_SEL_REGS
#define EPWMXBAR_BASE             0x00007A00U     //EPWM_XBAR_REGS
#define CLBXBAR_BASE              0x00007A40U     //CLB_XBAR_REGS
#define OUTPUTXBAR_BASE           0x00007A80U     //OUTPUT_XBAR_REGS
#define CLBOUTPUTXBAR_BASE        0x00007BC0U     //OUTPUT_XBAR_REGS
#define GPIOCTRL_BASE             0x00007C00U     //GPIO_CTRL_REGS
#define GPIODATA_BASE             0x00007F00U     //GPIO_DATA_REGS
#define GPIODATAREAD_BASE         0x00007F80U     //GPIO_DATA_READ_REGS
#define LFU_BASE                  0x00007FE0U     //LFU_REGS
#define LS0_RAM_BASE              0x00008000U
#define LS1_RAM_BASE              0x00008800U
#define LS2_RAM_BASE              0x00009000U
#define LS3_RAM_BASE              0x00009800U
#define LS4_RAM_BASE              0x0000A000U
#define LS5_RAM_BASE              0x0000A800U
#define LS6_RAM_BASE              0x0000B000U
#define LS7_RAM_BASE              0x0000B800U
#define GS0_RAM_BASE              0x0000C000U
#define GS1_RAM_BASE              0x0000E000U
#define GS2_RAM_BASE              0x00010000U
#define GS3_RAM_BASE              0x00012000U
#define LS8_RAM_CPU1_BASE         0x00014000U
#define LS9_RAM_CPU1_BASE         0x00016000U
#define USBA_BASE                 0x00040000U     //USB_REGS
#define AESA_BASE                 0x00042000U     //AES_REGS
#define AESA_SS_BASE              0x00042C00U     //AES_SS_REGS
#define EXTEVT_BASE               0x00054000U     //EXT_EVT_REGS
#define EXTGPRCM_BASE             0x0005400AU     //EXT_GPRCM_REGS
#define IPSTANDARD_BASE           0x00054020U     //IPSTANDARD_REGS
#define IPSPECIFIC_BASE           0x00054100U     //IPSPECIFIC_REGS
#define DATA_BASE                 0x00054700U     //DATA_REGS
#define ACC_BASE                  0x00054C00U     //ACC_REGS
#define INSTRUCTION_BASE          0x00055000U     //INSTRUCTION_REGS
#define RFDATA_BASE               0x00055800U     //RFDATA_REGS
#define MCANA_DRIVER_BASE         0x00058000U
#define MCANA_MSG_RAM_BASE        0x00058000U
#define MCANA_DRIVER_BASE         0x00058000U
#define MCANA_MSG_RAM_BASE        0x00058000U
#define MCANASS_BASE              0x00059400U     //MCANSS_REGS
#define MCANA_BASE                0x00059600U     //MCAN_REGS
#define MCANA_ERROR_BASE          0x00059800U     //MCAN_ERROR_REGS
#define MCANB_DRIVER_BASE         0x0005A000U
#define MCANB_MSG_RAM_BASE        0x0005A000U
#define MCANB_DRIVER_BASE         0x0005A000U
#define MCANB_MSG_RAM_BASE        0x0005A000U
#define MCANBSS_BASE              0x0005B400U     //MCANSS_REGS
#define MCANB_BASE                0x0005B600U     //MCAN_REGS
#define MCANB_ERROR_BASE          0x0005B800U     //MCAN_ERROR_REGS
#define DEVCFG_BASE               0x0005D000U     //DEV_CFG_REGS
#define CLKCFG_BASE               0x0005D200U     //CLK_CFG_REGS
#define CPUSYS_BASE               0x0005D300U     //CPU_SYS_REGS
#define SYSSTAT_BASE              0x0005D400U     //SYS_STATUS_REGS
#define PERIPHAC_BASE             0x0005D500U     //PERIPH_AC_REGS
#define ANALOGSUBSYS_BASE         0x0005D700U     //ANALOG_SUBSYS_REGS
#define DCC0_BASE                 0x0005E700U     //DCC_REGS
#define DCC1_BASE                 0x0005E740U     //DCC_REGS
#define ERAD_GLOBAL_BASE          0x0005E800U     //ERAD_GLOBAL_REGS
#define ERAD_HWBP1_BASE           0x0005E900U     //ERAD_HWBP_REGS
#define ERAD_HWBP2_BASE           0x0005E908U     //ERAD_HWBP_REGS
#define ERAD_HWBP3_BASE           0x0005E910U     //ERAD_HWBP_REGS
#define ERAD_HWBP4_BASE           0x0005E918U     //ERAD_HWBP_REGS
#define ERAD_HWBP5_BASE           0x0005E920U     //ERAD_HWBP_REGS
#define ERAD_HWBP6_BASE           0x0005E928U     //ERAD_HWBP_REGS
#define ERAD_HWBP7_BASE           0x0005E930U     //ERAD_HWBP_REGS
#define ERAD_HWBP8_BASE           0x0005E938U     //ERAD_HWBP_REGS
#define ERAD_COUNTER1_BASE        0x0005E980U     //ERAD_COUNTER_REGS
#define ERAD_COUNTER2_BASE        0x0005E990U     //ERAD_COUNTER_REGS
#define ERAD_COUNTER3_BASE        0x0005E9A0U     //ERAD_COUNTER_REGS
#define ERAD_COUNTER4_BASE        0x0005E9B0U     //ERAD_COUNTER_REGS
#define ERAD_CRC_GLOBAL_BASE      0x0005EA00U     //ERAD_CRC_GLOBAL_REGS
#define ERAD_CRC1_BASE            0x0005EA10U     //ERAD_CRC_REGS
#define ERAD_CRC2_BASE            0x0005EA20U     //ERAD_CRC_REGS
#define ERAD_CRC3_BASE            0x0005EA30U     //ERAD_CRC_REGS
#define ERAD_CRC4_BASE            0x0005EA40U     //ERAD_CRC_REGS
#define ERAD_CRC5_BASE            0x0005EA50U     //ERAD_CRC_REGS
#define ERAD_CRC6_BASE            0x0005EA60U     //ERAD_CRC_REGS
#define ERAD_CRC7_BASE            0x0005EA70U     //ERAD_CRC_REGS
#define ERAD_CRC8_BASE            0x0005EA80U     //ERAD_CRC_REGS
#define ERAD_PCTRACE_BASE         0x0005EAD0U     //PCTRACE_REGS
#define EPG1_BASE                 0x0005EC00U     //EPG_REGS
#define EPG1MUX_BASE              0x0005ECD0U     //EPG_MUX_REGS
#define DCSM_Z1_BASE              0x0005F000U     //DCSM_Z1_REGS
#define DCSM_Z2_BASE              0x0005F080U     //DCSM_Z2_REGS
#define DCSMCOMMON_BASE           0x0005F0C0U     //DCSM_COMMON_REGS
#define MEMCFG_BASE               0x0005F400U     //MEM_CFG_REGS
#define ACCESSPROTECTION_BASE     0x0005F500U     //ACCESS_PROTECTION_REGS
#define MEMORYERROR_BASE          0x0005F540U     //MEMORY_ERROR_REGS
#define TESTERROR_BASE            0x0005F590U     //TEST_ERROR_REGS
#define FLASH0CTRL_BASE           0x0005F800U     //FLASH_CTRL_REGS
#define FLASH0ECC_BASE            0x0005FB00U     //FLASH_ECC_REGS
#define ERAD_PCTRACE_BUFFER_BASE  0x0005FE00U     //PCTRACE_BUFFER_REGS
#define UID_BASE                  0x00072168U     //UID_REGS
#define DCSM_Z1OTP_BASE           0x00078000U     //DCSM_Z1_OTP
#define DCSM_Z2OTP_BASE           0x00078200U     //DCSM_Z2_OTP
#endif
