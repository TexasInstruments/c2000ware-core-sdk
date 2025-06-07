//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
//
//###########################################################################
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
#define ADCARESULT_BASE           0x00000B00U     //ADC_RESULT_REGS
#define ADCCRESULT_BASE           0x00000B40U     //ADC_RESULT_REGS
#define CPUTIMER0_BASE            0x00000C00U     //CPUTIMER_REGS
#define CPUTIMER1_BASE            0x00000C08U     //CPUTIMER_REGS
#define CPUTIMER2_BASE            0x00000C10U     //CPUTIMER_REGS
#define PIECTRL_BASE              0x00000CE0U     //PIE_CTRL_REGS
#define PIEVECTTABLE_BASE         0x00000D00U     //PIE_VECT_TABLE
#define EPWM1_BASE                0x00004000U     //EPWM_REGS
#define EPWM2_BASE                0x00004100U     //EPWM_REGS
#define EPWM3_BASE                0x00004200U     //EPWM_REGS
#define EPWM4_BASE                0x00004300U     //EPWM_REGS
#define EPWM5_BASE                0x00004400U     //EPWM_REGS
#define EPWM6_BASE                0x00004500U     //EPWM_REGS
#define EPWM7_BASE                0x00004600U     //EPWM_REGS
#define EQEP1_BASE                0x00005100U     //EQEP_REGS
#define ECAP1_BASE                0x00005200U     //ECAP_REGS
#define ECAP2_BASE                0x00005240U     //ECAP_REGS
#define CMPSS1_BASE               0x00005500U     //CMPSS_REGS
#define CMPSSLITE2_BASE           0x00005540U     //CMPSS_LITE_REGS
#define CMPSSLITE3_BASE           0x00005580U     //CMPSS_LITE_REGS
#define CMPSSLITE4_BASE           0x000055C0U     //CMPSS_LITE_REGS
#define SPIA_BASE                 0x00006100U     //SPI_REGS
#define PMBUSA_BASE               0x00006400U     //PMBUS_REGS
#define LINA_BASE                 0x00006A00U     //LIN_REGS
#define WD_BASE                   0x00007000U     //WD_REGS
#define NMI_BASE                  0x00007060U     //NMI_INTRUPT_REGS
#define XINT_BASE                 0x00007070U     //XINT_REGS
#define SCIA_BASE                 0x00007200U     //SCI_REGS
#define SCIB_BASE                 0x00007210U     //SCI_REGS
#define SCIC_BASE                 0x00007220U     //SCI_REGS
#define I2CA_BASE                 0x00007300U     //I2C_REGS
#define I2CB_BASE                 0x00007340U     //I2C_REGS
#define ADCA_BASE                 0x00007400U     //ADC_REGS
#define ADCC_BASE                 0x00007500U     //ADC_REGS
#define INPUTXBAR_BASE            0x00007900U     //INPUT_XBAR_REGS
#define XBAR_BASE                 0x00007920U     //XBAR_REGS
#define SYNCSOC_BASE              0x00007940U     //SYNC_SOC_REGS
#define EPWMXBAR_BASE             0x00007A00U     //EPWM_XBAR_REGS
#define OUTPUTXBAR_BASE           0x00007A80U     //OUTPUT_XBAR_REGS
#define GPIOCTRL_BASE             0x00007C00U     //GPIO_CTRL_REGS
#define GPIODATA_BASE             0x00007F00U     //GPIO_DATA_REGS
#define GPIODATAREAD_BASE         0x00007F80U     //GPIO_DATA_READ_REGS
#define LS0_RAM_BASE              0x00008000U
#define LS1_RAM_BASE              0x0000A000U
#define CANA_BASE                 0x00048000U     //CAN_REGS
#define CANA_MSG_RAM_BASE         0x00049000U
#define LCM_CPU1_BASE             0x0004C000U     //LCM_REGS
#define MCANA_DRIVER_BASE         0x00058000U
#define MCANA_MSG_RAM_BASE        0x00058000U
#define MCANASS_BASE              0x0005C400U     //MCANSS_REGS
#define MCANA_BASE                0x0005C600U     //MCAN_REGS
#define MCANA_ERROR_BASE          0x0005C800U     //MCAN_ERROR_REGS
#define DEVCFG_BASE               0x0005D000U     //DEV_CFG_REGS
#define CLKCFG_BASE               0x0005D200U     //CLK_CFG_REGS
#define CPUSYS_BASE               0x0005D300U     //CPU_SYS_REGS
#define SYSSTAT_BASE              0x0005D400U     //SYS_STATUS_REGS
#define ANALOGSUBSYS_BASE         0x0005D700U     //ANALOG_SUBSYS_REGS
#define MPOST_BASE                0x0005E200U     //MPOST_REGS
#define DCC0_BASE                 0x0005E700U     //DCC_REGS
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
#define UID_BASE                  0x00071140U     //UID_REGS
#define DCSM_Z1OTP_BASE           0x00078000U     //DCSM_Z1_OTP
#define DCSM_Z2OTP_BASE           0x00078200U     //DCSM_Z2_OTP
#endif
