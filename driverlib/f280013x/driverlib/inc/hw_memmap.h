//###########################################################################
//
// FILE:    hw_memmap.h
//
// TITLE:   Macros defining the memory map of the C28x.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#define ADCCRESULT_BASE           0x00000B40U
#define CPUTIMER0_BASE            0x00000C00U
#define CPUTIMER1_BASE            0x00000C08U
#define CPUTIMER2_BASE            0x00000C10U
#define PIECTRL_BASE              0x00000CE0U
#define PIEVECTTABLE_BASE         0x00000D00U
#define EPWM1_BASE                0x00004000U
#define EPWM2_BASE                0x00004100U
#define EPWM3_BASE                0x00004200U
#define EPWM4_BASE                0x00004300U
#define EPWM5_BASE                0x00004400U
#define EPWM6_BASE                0x00004500U
#define EPWM7_BASE                0x00004600U
#define EQEP1_BASE                0x00005100U
#define ECAP1_BASE                0x00005200U
#define ECAP2_BASE                0x00005240U
#define CMPSS1_BASE               0x00005500U
#define CMPSSLITE2_BASE           0x00005540U
#define CMPSSLITE3_BASE           0x00005580U
#define CMPSSLITE4_BASE           0x000055C0U
#define SPIA_BASE                 0x00006100U
#define WD_BASE                   0x00007000U
#define NMI_BASE                  0x00007060U
#define XINT_BASE                 0x00007070U
#define SCIA_BASE                 0x00007200U
#define SCIB_BASE                 0x00007210U
#define SCIC_BASE                 0x00007220U
#define I2CA_BASE                 0x00007300U
#define I2CB_BASE                 0x00007340U
#define ADCA_BASE                 0x00007400U
#define ADCC_BASE                 0x00007500U
#define INPUTXBAR_BASE            0x00007900U
#define XBAR_BASE                 0x00007920U
#define SYNCSOC_BASE              0x00007940U
#define EPWMXBAR_BASE             0x00007A00U
#define OUTPUTXBAR_BASE           0x00007A80U
#define GPIOCTRL_BASE             0x00007C00U
#define GPIODATA_BASE             0x00007F00U
#define GPIODATAREAD_BASE         0x00007F80U
#define LS0_RAM_BASE              0x00008000U
#define LS1_RAM_BASE              0x0000A000U
#define CANA_BASE                 0x00048000U
#define CANA_MSG_RAM_BASE         0x00049000U
#define DEVCFG_BASE               0x0005D000U
#define CLKCFG_BASE               0x0005D200U
#define CPUSYS_BASE               0x0005D300U
#define SYSSTAT_BASE              0x0005D400U
#define ANALOGSUBSYS_BASE         0x0005D700U
#define MPOST_BASE                0x0005E200U
#define DCC0_BASE                 0x0005E700U
#define EPG1_BASE                 0x0005EC00U
#define EPG1MUX_BASE              0x0005ECD0U
#define DCSM_Z1_BASE              0x0005F000U
#define DCSM_Z2_BASE              0x0005F080U
#define DCSMCOMMON_BASE           0x0005F0C0U
#define MEMCFG_BASE               0x0005F400U
#define ACCESSPROTECTION_BASE     0x0005F500U
#define MEMORYERROR_BASE          0x0005F540U
#define TESTERROR_BASE            0x0005F590U
#define FLASH0CTRL_BASE           0x0005F800U
#define FLASH0ECC_BASE            0x0005FB00U
#define UID_BASE                  0x00071140U
#define DCSM_Z1OTP_BASE           0x00078000U
#define DCSM_Z2OTP_BASE           0x00078200U
#endif
