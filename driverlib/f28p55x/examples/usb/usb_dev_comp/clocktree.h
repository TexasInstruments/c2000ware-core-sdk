//#############################################################################
//
// FILE:   clockTree.h
//
// TITLE:  Setups device clocking for examples.
//
//#############################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef CLOCKTREE_H
#define CLOCKTREE_H

//*****************************************************************************
//
// Summary of SYSPLL related clock configuration
//
//*****************************************************************************
//
// Input Clock to SYSPLL (OSCCLK)   = 20 MHz    (XTAL provides OSCCLK)
//
//##### SYSPLL ENABLED #####
//
// PLLRAWCLK                = 300 MHz   (Output of SYSPLL if enabled)
// PLLSYSCLK                = 150 MHz
// CPUCLK                   = 150 MHz
// SYSCLK                   = 150 MHz
// LSPCLK                   = 37.5 MHz

//*****************************************************************************
//
// Macro definitions used in device.c (SYSPLL / LSPCLK)
//
//*****************************************************************************
//
//  Input Clock to SYSPLL (OSCCLK) = XTAL = 20 MHz
//
#define DEVICE_OSCSRC_FREQ          20000000U
//
// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// SYSPLL ENABLED
// SYSCLK = 150 MHz = 20 MHz (OSCCLK) * 30 (IMULT) / (2 (REFDIV) * 1 (ODIV) * 2 (SYSCLKDIVSEL))
#define DEVICE_SYSCLK_FREQ          ((DEVICE_OSCSRC_FREQ * 30) / (2 * 1 * 2))
//
#define DEVICE_SETCLOCK_CFG         (SYSCTL_OSCSRC_XTAL  | SYSCTL_IMULT(30) | \
                                     SYSCTL_REFDIV(2) | SYSCTL_ODIV(1)| \
                                     SYSCTL_SYSDIV(2) | SYSCTL_PLL_ENABLE | \
                                     SYSCTL_DCC_BASE_0)


//
// Define to pass to SysCtl_setLowSpeedClock().
// Low Speed Clock (LSPCLK) = 150 MHz / 4 = 37.5 MHz
//
#define DEVICE_LSPCLK_CFG           SYSCTL_LSPCLK_PRESCALE_4

#define DEVICE_LSPCLK_FREQ          (DEVICE_SYSCLK_FREQ / 4)

//*****************************************************************************
//
// CPUCLK Domain (150 MHz)
//
//*****************************************************************************
// FPU
// TMU
//
//*****************************************************************************
//
// SYSCLK Domain (150 MHz)
//
//*****************************************************************************
// ePIE
// GPIO
// MxRAMs
// LsxRAMs
// GsxRAMS
// Flash
// BootROM
// DCSM
// SystemControl
// WD
// XINT
// CLA
// CLAROM
// ECAP
// EQEP
// ETPWM
// MessageRAMs
//

/////////////////////
// Gated CPU1 SYSCLK
/////////////////////
// CPUTIMERs
// CLB
// EPWM
// HRCAL
// EPG
// I2C
// ADC
// CMPSS
// BufferedDAC
// DCC
// PMBus
// AES
// FSITX/FSIRX
//

//*****************************************************************************
//
// Gated Peripheral SYSCLK Domain (150 MHz) 
//
//*****************************************************************************
// CPUTIMERs
// CLB
// EPWM
// HRCAL
// EPG
// I2C
// ADC
// CMPSS
// BufferedDAC
// DCC
// PMBus
// AES
// FSITX/FSIRX
//

//*****************************************************************************
//
// Gated LSPCLK Domain (37.5 MHz) 
//
//*****************************************************************************
// SCI
// SPI

#endif // CLOCKTREE_H

