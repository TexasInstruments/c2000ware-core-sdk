//###########################################################################
//
// FILE:   sysctl.h 
//
// TITLE:  C28x system control driver.
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

#ifndef SYSCTL_H
#define SYSCTL_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup sysctl_api SysCtl
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_nmi.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_otp.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "interrupt.h"


//
// Macro used for adding delay between 2 consecutive writes to CLKSRCCTL1
// register.
// Delay = 300 NOPs
//
#define SYSCTL_CLKSRCCTL_DELAY  asm(" RPT #250 || NOP \n RPT #50 || NOP")

//
// Macro used for adding delay between 2 consecutive writes to memory mapped 
// register in System control
// Total delay = 3 * (DEVICE_SYSCLK_FREQ / WROSCDIV8 Freq) + 9
//
#define SYSCTL_REGWRITE_DELAY  asm(" RPT #69 || NOP")

//*****************************************************************************
//
// Defines for system control functions. Not intended for use by application
// code.
//
//*****************************************************************************

//
// Shifted pattern for WDCR register's WDCHK field.
//
#define SYSCTL_WD_CHKBITS       0x0028U

//
// Keys for WDKEY field. The first enables resets and the second resets.
//
#define SYSCTL_WD_ENRSTKEY      0x0055U
#define SYSCTL_WD_RSTKEY        0x00AAU

//
// Values to help decode peripheral parameter
//
#define SYSCTL_PERIPH_REG_M     0x001FU
#define SYSCTL_PERIPH_REG_S     0x0000U
#define SYSCTL_PERIPH_BIT_M     0x1F00U
#define SYSCTL_PERIPH_BIT_S     0x0008U

//
//Keys for the System control registers write protection
//
#define SYSCTL_REG_KEY       0xA5A50000U
#define SYSCTL_PLL_KEY       0XCAFE0000U

//
//Values to help access shifting of bits
//
#define SYSCTL_TYPE_LOCK_S              0xFU


//
// LPM defines for LPMCR.LPM
//
#define SYSCTL_LPM_IDLE         0x0000U
#define SYSCTL_LPM_STANDBY      0x0001U
#define SYSCTL_LPM_HALT         0x0002U

//
// Default Wide range oscillator frequency with a divider of 8 ie,  4 MHz
//
#define SYSCTL_DEFAULT_OSC_FREQ     4000000U

//
// Default Sys oscillator frequency with a divider of 4 ie, 8 MHz
//
#define SYSCTL_DEFAULT_SYSOSCDIV4_FREQ     8000000U


//
// Boot ROM Booting and Reset Status
//
#define SYSCTL_BOOT_ROM_STATUS    0x0002U
#define SYSCTL_BOOT_ROM_POR       0x2000U
#define SYSCTL_BOOT_ROM_XRS       0x1000U


//
// Device_cal function which is available in OTP memory
// This function is called in SysCtl_resetPeripheral after resetting
// analog peripherals
//
#define Device_cal ((void (*)(void))((uintptr_t)0x003fc3f4))

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_setClock() API as
// the config parameter.
//
//*****************************************************************************

#ifndef DOXYGEN_PDF_IGNORE

//
// DCC module selection for checking PLL clock validity
//
// Mask and shift for DCC module base address in config
//
#define SYSCTL_DCC_BASE_M    0x30000000UL

#define SYSCTL_DCC_BASE_S    28U

#define SYSCTL_DCC_BASE_0       0x00000000UL //!< DCC0 module


//
// Oscillator source
//
// Also used with the SysCtl_selectOscSource(), SysCtl_turnOnOsc(),
// and SysCtl_turnOffOsc() functions as the oscSource parameter.
//
#define SYSCTL_OSCSRC_M                 0x03UL // Mask for OSCSRC value in config
#define SYSCTL_OSCSRC_S                 0U     // Shift for OSCSRC value in config
//! SYSOSCDIV4
#define SYSCTL_OSCSRC_SYSOSCDIV4         0x00UL
//! External oscillator (XTAL) in crystal mode
#define SYSCTL_OSCSRC_XTAL              0x01U
//! External oscillator (XTAL) in single-ended mode
#define SYSCTL_OSCSRC_XTAL_SE           0x03U
//! Wide-range oscillator by 8 (WROSCDIV8)
#define SYSCTL_OSCSRC_WROSCDIV8       0x02UL
//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e pllConfig parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PLL_ENABLE,
    SYSCTL_PLL_DISABLE,
    SYSCTL_PLL_BYPASS,
} Sysctl_PLLConfig;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e pdiv parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PDIV_1,
    SYSCTL_PDIV_2,
    SYSCTL_PDIV_4,
    SYSCTL_PDIV_8
} Sysctl_PLLPDiv;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e multiplier parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PLLMULT_2 = 1,
    SYSCTL_PLLMULT_3,
    SYSCTL_PLLMULT_4,
    SYSCTL_PLLMULT_5,
    SYSCTL_PLLMULT_6,
    SYSCTL_PLLMULT_7,
    SYSCTL_PLLMULT_8,
    SYSCTL_PLLMULT_9,
    SYSCTL_PLLMULT_10,
    SYSCTL_PLLMULT_11,
    SYSCTL_PLLMULT_12,
    SYSCTL_PLLMULT_13,
    SYSCTL_PLLMULT_14,
    SYSCTL_PLLMULT_15,
    SYSCTL_PLLMULT_16,
    SYSCTL_PLLMULT_17,
    SYSCTL_PLLMULT_18,
    SYSCTL_PLLMULT_19,
    SYSCTL_PLLMULT_20,
    SYSCTL_PLLMULT_21,
    SYSCTL_PLLMULT_22,
    SYSCTL_PLLMULT_23,
    SYSCTL_PLLMULT_24,
    SYSCTL_PLLMULT_25,
    SYSCTL_PLLMULT_26,
    SYSCTL_PLLMULT_27,
    SYSCTL_PLLMULT_28,
    SYSCTL_PLLMULT_29,
    SYSCTL_PLLMULT_30,
    SYSCTL_PLLMULT_31,
    SYSCTL_PLLMULT_32,
    SYSCTL_PLLMULT_33,
    SYSCTL_PLLMULT_34,
    SYSCTL_PLLMULT_35,
    SYSCTL_PLLMULT_36,
    SYSCTL_PLLMULT_37,
    SYSCTL_PLLMULT_38,
    SYSCTL_PLLMULT_39,
    SYSCTL_PLLMULT_40,
    SYSCTL_PLLMULT_41,
    SYSCTL_PLLMULT_42,
    SYSCTL_PLLMULT_43,
    SYSCTL_PLLMULT_44,
    SYSCTL_PLLMULT_45,
    SYSCTL_PLLMULT_46,
    SYSCTL_PLLMULT_47,
    SYSCTL_PLLMULT_48,
    SYSCTL_PLLMULT_49,
    SYSCTL_PLLMULT_50,
    SYSCTL_PLLMULT_51,
    SYSCTL_PLLMULT_52,
    SYSCTL_PLLMULT_53,
    SYSCTL_PLLMULT_54,
    SYSCTL_PLLMULT_55,
    SYSCTL_PLLMULT_56,
    SYSCTL_PLLMULT_57,
    SYSCTL_PLLMULT_58,
    SYSCTL_PLLMULT_59,
    SYSCTL_PLLMULT_60,
    SYSCTL_PLLMULT_61,
    SYSCTL_PLLMULT_62,
    SYSCTL_PLLMULT_63,
    SYSCTL_PLLMULT_64,
    SYSCTL_PLLMULT_65,
    SYSCTL_PLLMULT_66,
    SYSCTL_PLLMULT_67,
    SYSCTL_PLLMULT_68,
    SYSCTL_PLLMULT_69,
    SYSCTL_PLLMULT_70,
    SYSCTL_PLLMULT_71,
    SYSCTL_PLLMULT_72,
    SYSCTL_PLLMULT_73,
    SYSCTL_PLLMULT_74,
    SYSCTL_PLLMULT_75,
    SYSCTL_PLLMULT_76,
    SYSCTL_PLLMULT_77,
    SYSCTL_PLLMULT_78,
    SYSCTL_PLLMULT_79,
    SYSCTL_PLLMULT_80,
    SYSCTL_PLLMULT_81,
    SYSCTL_PLLMULT_82,
    SYSCTL_PLLMULT_83,
    SYSCTL_PLLMULT_84,
    SYSCTL_PLLMULT_85,
    SYSCTL_PLLMULT_86,
    SYSCTL_PLLMULT_87,
    SYSCTL_PLLMULT_88,
    SYSCTL_PLLMULT_89,
    SYSCTL_PLLMULT_90,
    SYSCTL_PLLMULT_91,
    SYSCTL_PLLMULT_92,
    SYSCTL_PLLMULT_93,
    SYSCTL_PLLMULT_94,
    SYSCTL_PLLMULT_95,
    SYSCTL_PLLMULT_96,
    SYSCTL_PLLMULT_97,
    SYSCTL_PLLMULT_98,
    SYSCTL_PLLMULT_99,
    SYSCTL_PLLMULT_100,
    SYSCTL_PLLMULT_101,
    SYSCTL_PLLMULT_102,
    SYSCTL_PLLMULT_103,
    SYSCTL_PLLMULT_104,
    SYSCTL_PLLMULT_105,
    SYSCTL_PLLMULT_106,
    SYSCTL_PLLMULT_107,
    SYSCTL_PLLMULT_108,
    SYSCTL_PLLMULT_109,
    SYSCTL_PLLMULT_110,
    SYSCTL_PLLMULT_111,
    SYSCTL_PLLMULT_112,
    SYSCTL_PLLMULT_113,
    SYSCTL_PLLMULT_114,
    SYSCTL_PLLMULT_115,
    SYSCTL_PLLMULT_116,
    SYSCTL_PLLMULT_117,
    SYSCTL_PLLMULT_118,
    SYSCTL_PLLMULT_119,
    SYSCTL_PLLMULT_120,
    SYSCTL_PLLMULT_121,
    SYSCTL_PLLMULT_122,
    SYSCTL_PLLMULT_123,
    SYSCTL_PLLMULT_124,
    SYSCTL_PLLMULT_125,
    SYSCTL_PLLMULT_126,
    SYSCTL_PLLMULT_127,
    SYSCTL_PLLMULT_128
} Sysctl_PLLMult;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e rdivclk0 parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_RDIVCLK0_2,
    SYSCTL_RDIVCLK0_4,
    SYSCTL_RDIVCLK0_6,
    SYSCTL_RDIVCLK0_8,
    SYSCTL_RDIVCLK0_10,
    SYSCTL_RDIVCLK0_12,
    SYSCTL_RDIVCLK0_14,
    SYSCTL_RDIVCLK0_16,
    SYSCTL_RDIVCLK0_18,
    SYSCTL_RDIVCLK0_20,
    SYSCTL_RDIVCLK0_22,
    SYSCTL_RDIVCLK0_24,
    SYSCTL_RDIVCLK0_26,
    SYSCTL_RDIVCLK0_28,
    SYSCTL_RDIVCLK0_30,
    SYSCTL_RDIVCLK0_32
} Sysctl_PLLRDivClk0;

//*****************************************************************************
//
//! The following are values that can be passed to Sysctl_setClock() as
//! \e sysdiv parameter
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYSDIV_1,
    SYSCTL_SYSDIV_2,
    SYSCTL_SYSDIV_3,
    SYSCTL_SYSDIV_4,
    SYSCTL_SYSDIV_5,
    SYSCTL_SYSDIV_6,
    SYSCTL_SYSDIV_7,
    SYSCTL_SYSDIV_8,
    SYSCTL_SYSDIV_9,
    SYSCTL_SYSDIV_10,
    SYSCTL_SYSDIV_11,
    SYSCTL_SYSDIV_12,
    SYSCTL_SYSDIV_13,
    SYSCTL_SYSDIV_14,
    SYSCTL_SYSDIV_15,
    SYSCTL_SYSDIV_16,
    SYSCTL_SYSDIV_17,
    SYSCTL_SYSDIV_18,
    SYSCTL_SYSDIV_19,
    SYSCTL_SYSDIV_20,
    SYSCTL_SYSDIV_21,
    SYSCTL_SYSDIV_22,
    SYSCTL_SYSDIV_23,
    SYSCTL_SYSDIV_24,
    SYSCTL_SYSDIV_25,
    SYSCTL_SYSDIV_26,
    SYSCTL_SYSDIV_27,
    SYSCTL_SYSDIV_28,
    SYSCTL_SYSDIV_29,
    SYSCTL_SYSDIV_30,
    SYSCTL_SYSDIV_31,
    SYSCTL_SYSDIV_32,
    SYSCTL_SYSDIV_33,
    SYSCTL_SYSDIV_34,
    SYSCTL_SYSDIV_35,
    SYSCTL_SYSDIV_36,
    SYSCTL_SYSDIV_37,
    SYSCTL_SYSDIV_38,
    SYSCTL_SYSDIV_39,
    SYSCTL_SYSDIV_40,
    SYSCTL_SYSDIV_41,
    SYSCTL_SYSDIV_42,
    SYSCTL_SYSDIV_43,
    SYSCTL_SYSDIV_44,
    SYSCTL_SYSDIV_45,
    SYSCTL_SYSDIV_46,
    SYSCTL_SYSDIV_47,
    SYSCTL_SYSDIV_48,
    SYSCTL_SYSDIV_49,
    SYSCTL_SYSDIV_50,
    SYSCTL_SYSDIV_51,
    SYSCTL_SYSDIV_52,
    SYSCTL_SYSDIV_53,
    SYSCTL_SYSDIV_54,
    SYSCTL_SYSDIV_55,
    SYSCTL_SYSDIV_56,
    SYSCTL_SYSDIV_57,
    SYSCTL_SYSDIV_58,
    SYSCTL_SYSDIV_59,
    SYSCTL_SYSDIV_60,
    SYSCTL_SYSDIV_61,
    SYSCTL_SYSDIV_62,
    SYSCTL_SYSDIV_63,
    SYSCTL_SYSDIV_64
} Sysctl_PLLSysDiv;

//
// Number of PLL retries for SW work around
//
#define SYSCTL_PLL_RETRIES              100U    // Number of PLL retries
#define SYSCTL_PLLLOCK_TIMEOUT          2000U   // PLL Lock timeout
#define SYSCTL_DCC_COUNTER0_TOLERANCE   1U
#define SYSCTL_DCC_COUNTER0_WINDOW      1000U   // DCC Counter0 Window
//*****************************************************************************
//
// Values that can be passed to SysCtl_clearNMIStatus(),
// SysCtl_forceNMIFlags(), SysCtl_isNMIFlagSet(), and
// SysCtl_isNMIShadowFlagSet() as the nmiFlags parameter and returned by
// SysCtl_getNMIFlagStatus() and SysCtl_getNMIShadowFlagStatus().
//
//*****************************************************************************
#define SYSCTL_NMI_NMIINT       0x1U //!<  NMI Interrupt Flag
#define SYSCTL_NMI_CLOCKFAIL    0x2U //!<  Clock Fail Interrupt Flag
#define SYSCTL_NMI_UNCERR       0x4U //!<  Flash/RAM/ROM Uncorrectable Error NMI Flag
#define SYSCTL_NMI_SWERR        0x2000U //!<  SW Error Force NMI Flag
//*****************************************************************************
//
// Values that can be passed to/returned from SysCtl_getInterruptStatus()
// SysCtl_clearInterruptStatus() or SysCtl_setInterruptStatus()
// as the intFlags parameter
//
//*****************************************************************************
#define SYSCTL_STATUS_GINT               0x1U //!<  Global Interrupt flag
#define SYSCTL_STATUS_CORRECTABLE_ERR    0x4U //!<  RAM/Flash correctable error flag
#define SYSCTL_STATUS_FPU_UFLOW          0x10000U //!<  FPU_UFLOW Interrupt flag.
#define SYSCTL_STATUS_FPU_OFLOW          0x20000U //!<  FPU_OFLOW Interrupt flag.


//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_clearResetCause()
// API as rstCauses or returned by the SysCtl_getResetCause() API.
//
//*****************************************************************************
#define SYSCTL_CAUSE_POR                 0x00000001U //!< Power-on reset
#define SYSCTL_CAUSE_XRS                 0x00000002U //!< External reset pin
#define SYSCTL_CAUSE_WDRS                0x00000004U //!< Watchdog reset
#define SYSCTL_CAUSE_NMIWDRS             0x00000008U //!< NMI watchdog reset
#define SYSCTL_CAUSE_SCCRESET            0x00000100U //!< SCCRESETn by DCSM
#define SYSCTL_CAUSE_SIMRESET_CPU1RSN    0x00000400U //!< SIMRESET_CPU1RSn
#define SYSCTL_CAUSE_SIMRESET_XRSN       0x00000800U //!< SIMRESET_XRSn
//*****************************************************************************
//
// The following values define the adcsocSrc parameter for
// SysCtl_enableExtADCSOCSource() and SysCtl_disableExtADCSOCSource().
//
//*****************************************************************************
#define SYSCTL_ADCSOC_SRC_PWM1SOCA   0x1U //!<PWM1 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM3SOCA   0x4U //!<PWM3 SOCA for ADCSOCAO
#define SYSCTL_ADCSOC_SRC_PWM1SOCB   0x10000U //!<PWM1 SOCB for ADCSOCBO
#define SYSCTL_ADCSOC_SRC_PWM3SOCB   0x40000U //!<PWM3 SOCB for ADCSOCBO
#endif

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_enablePeripheral()
//! and SysCtl_disablePeripheral() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_CLK_TBCLKSYNC = 0x0000  //!< TBCLKSYNC clock
} SysCtl_PeripheralPCLOCKCR;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_resetPeripheral() as
//! the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_PERIPH_RES_MCPWM1 = 0x0000, //!< Reset MCPWM1 clock
    SYSCTL_PERIPH_RES_MCPWM3 = 0x0200, //!< Reset MCPWM3 clock
    SYSCTL_PERIPH_RES_ECAP1 = 0x0C00, //!< Reset ECAP1 clock
    SYSCTL_PERIPH_RES_EQEP1 = 0x0E00, //!< Reset EQEP1 clock
    SYSCTL_PERIPH_RES_ADCA = 0x0F00, //!< Reset ADC_A clock
    SYSCTL_PERIPH_RES_CMPSS1 = 0x1100, //!< Reset CMPSS1 clock
    SYSCTL_PERIPH_RES_CMPSS2 = 0x1200, //!< Reset CMPSS2 clock
    SYSCTL_PERIPH_RES_CMPSS3 = 0x1300, //!< Reset CMPSS3 clock
    SYSCTL_PERIPH_RES_PGA1 = 0x1800,  //!< Reset PGA1 clock
    SYSCTL_PERIPH_RES_I2CA = 0x0001, //!< Reset I2C_A clock
    SYSCTL_PERIPH_RES_SCIA = 0x0201, //!< Reset SCI_A clock
    SYSCTL_PERIPH_RES_SCIB = 0x0301, //!< Reset SCI_B clock
    SYSCTL_PERIPH_RES_UARTA = 0x0401, //!< Reset UART_A clock
    SYSCTL_PERIPH_RES_SPIA = 0x0601  //!< Reset SPI_A clock
} SysCtl_PeripheralSOFTPRES;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPredivider() as the \e predivider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PREDIV_2    = 0x800,  //!< PREDIVCLK = WROSCDIV8 / 2
    SYSCTL_WD_PREDIV_4    = 0x900,  //!< PREDIVCLK = WROSCDIV8 / 4
    SYSCTL_WD_PREDIV_8    = 0xA00,  //!< PREDIVCLK = WROSCDIV8 / 8
    SYSCTL_WD_PREDIV_16   = 0xB00,  //!< PREDIVCLK = WROSCDIV8 / 16
    SYSCTL_WD_PREDIV_32   = 0xC00,  //!< PREDIVCLK = WROSCDIV8 / 32
    SYSCTL_WD_PREDIV_64   = 0xD00,  //!< PREDIVCLK = WROSCDIV8 / 64
    SYSCTL_WD_PREDIV_128  = 0xE00,  //!< PREDIVCLK = WROSCDIV8 / 128
    SYSCTL_WD_PREDIV_256  = 0xF00,  //!< PREDIVCLK = WROSCDIV8 / 256
    SYSCTL_WD_PREDIV_512  = 0x000,  //!< PREDIVCLK = WROSCDIV8 / 512
    SYSCTL_WD_PREDIV_1024 = 0x100,  //!< PREDIVCLK = WROSCDIV8 / 1024
    SYSCTL_WD_PREDIV_2048 = 0x200,  //!< PREDIVCLK = WROSCDIV8 / 2048
    SYSCTL_WD_PREDIV_4096 = 0x300   //!< PREDIVCLK = WROSCDIV8 / 4096
} SysCtl_WDPredivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPrescaler() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PRESCALE_1  = 1,      //!< WDCLK = PREDIVCLK / 1
    SYSCTL_WD_PRESCALE_2  = 2,      //!< WDCLK = PREDIVCLK / 2
    SYSCTL_WD_PRESCALE_4  = 3,      //!< WDCLK = PREDIVCLK / 4
    SYSCTL_WD_PRESCALE_8  = 4,      //!< WDCLK = PREDIVCLK / 8
    SYSCTL_WD_PRESCALE_16 = 5,      //!< WDCLK = PREDIVCLK / 16
    SYSCTL_WD_PRESCALE_32 = 6,      //!< WDCLK = PREDIVCLK / 32
    SYSCTL_WD_PRESCALE_64 = 7       //!< WDCLK = PREDIVCLK / 64
} SysCtl_WDPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogMode() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    //! Watchdog can generate a reset signal
    SYSCTL_WD_MODE_RESET,
    //! Watchdog can generate an interrupt signal; reset signal is disabled
    SYSCTL_WD_MODE_INTERRUPT
} SysCtl_WDMode;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setLowSpeedClock() as
//! the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_LSPCLK_PRESCALE_1    = 0,    //!< LSPCLK = SYSCLK / 1
    SYSCTL_LSPCLK_PRESCALE_2    = 1,    //!< LSPCLK = SYSCLK / 2
    SYSCTL_LSPCLK_PRESCALE_4    = 2,    //!< LSPCLK = SYSCLK / 4 (default)
    SYSCTL_LSPCLK_PRESCALE_6    = 3,    //!< LSPCLK = SYSCLK / 6
    SYSCTL_LSPCLK_PRESCALE_8    = 4,    //!< LSPCLK = SYSCLK / 8
    SYSCTL_LSPCLK_PRESCALE_10   = 5,    //!< LSPCLK = SYSCLK / 10
    SYSCTL_LSPCLK_PRESCALE_12   = 6,    //!< LSPCLK = SYSCLK / 12
    SYSCTL_LSPCLK_PRESCALE_14   = 7     //!< LSPCLK = SYSCLK / 14
} SysCtl_LSPCLKPrescaler;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_selectClockOutSource() as the \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLOCKOUT_PLLSYS     = 0U,   //!< PLL System Clock post SYSCLKDIV
    SYSCTL_CLOCKOUT_PLLCLK     = 1U,   //!< PLL Clock after Bypass Mux
    SYSCTL_CLOCKOUT_SYSCLK     = 2U,   //!< CPU System Clock
    SYSCTL_CLOCKOUT_WROSC      = 3U,   //!< Wide-range Oscillator
    SYSCTL_CLOCKOUT_SYSOSC     = 4U,   //!< System Oscillator
    SYSCTL_CLOCKOUT_WROSCDIV8  = 5U,   //!< Wide-range Oscillator BY 8
    SYSCTL_CLOCKOUT_SYSOSCDIV4 = 6U,   //!< System Oscillator BY 4
    SYSCTL_CLOCKOUT_XTALOSC    = 7U,   //!< External Oscillator
    SYSCTL_CLOCKOUT_PLLRAW     = 12U,  //!< PLL System Clock pre SYSCLKDIV
} SysCtl_ClockOut;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setExternalOscMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XTALMODE_CRYSTAL = 1U,   //!< XTAL Oscillator Crystal Mode
    SYSCTL_XTALMODE_SINGLE  = 2U    //!< XTAL Oscillator Single-Ended Mode
} SysCtl_ExternalOscMode;


//*****************************************************************************
//
//! The following values define the \e syncSrc parameter for
//! SysCtl_setSyncOutputConfig().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_SYNC_OUT_SRC_MCPWM1SYNCOUT  = 0X0U,  //!< MCPWM1SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_MCPWM3SYNCOUT  = 0X2U,  //!< MCPWM3SYNCOUT --> EXTSYNCOUT
    SYSCTL_SYNC_OUT_SRC_ECAP1SYNCOUT  = 0x18,  //!< ECAP1SYNCOUT --> EXTSYNCOUT

} SysCtl_SyncOutputSource;

//*****************************************************************************
//
//! The following values define the \e parametric parameter for
//! SysCtl_getDeviceParametric().
//
//*****************************************************************************
typedef enum
{
    SYSCTL_DEVICE_QUAL,       //!< Device Qualification Status
    SYSCTL_DEVICE_FLASH,      //!< Device Flash size (KB)
    SYSCTL_DEVICE_FAMILY,     //!< Device Family
    SYSCTL_DEVICE_PARTNO,     //!< Device Part Number
    SYSCTL_DEVICE_CLASSID     //!< Device Class ID
} SysCtl_DeviceParametric;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_configureType()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    //! Configure ECAP Type :
    //!  - Type 0 : No EALLOW protection for ECAP registers
    //!  - Type 1 : ECAP registers are EALLOW protected
    SYSCTL_ECAPTYPE = 0x1,

}SysCtl_SelType;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setXClk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_XCLKOUT_DIV_1  = 0,      //!<  XCLKOUT =  XCLKOUT / 1
    SYSCTL_XCLKOUT_DIV_2  = 1,      //!<  XCLKOUT =  XCLKOUT / 2
    SYSCTL_XCLKOUT_DIV_4  = 2,      //!<  XCLKOUT =  XCLKOUT / 4
    SYSCTL_XCLKOUT_DIV_8  = 3       //!<  XCLKOUT =  XCLKOUT / 8

}SysCtl_XClkDivider;


//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setCputimer2Clk() as \e divider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKPRESCALE_1,   //!<  Cputimer2 clock =  Cputimer2 clock / 1
    SYSCTL_TMR2CLKPRESCALE_2,   //!<  Cputimer2 clock =  Cputimer2 clock / 2
    SYSCTL_TMR2CLKPRESCALE_4,   //!<  Cputimer2 clock =  Cputimer2 clock / 4
    SYSCTL_TMR2CLKPRESCALE_8,   //!<  Cputimer2 clock =  Cputimer2 clock / 8
    SYSCTL_TMR2CLKPRESCALE_16   //!<  Cputimer2 clock =  Cputimer2 clock / 16

}SysCtl_Cputimer2ClkDivider;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setCputimer2Clk()
//! as \e source parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_TMR2CLKSRCSEL_SYSCLK     = 0U,   //!< System Clock
    SYSCTL_TMR2CLKSRCSEL_WROSCDIV8     = 1U,   //!< Wide-range Oscillator
    SYSCTL_TMR2CLKSRCSEL_SYSOSCDIV4    = 2U,   //!< System Oscillator
    SYSCTL_TMR2CLKSRCSEL_XTAL       = 3U,   //!< Crystal oscillator
    SYSCTL_TMR2CLKSRCSEL_AUXPLLCLK  = 6U    //!< Aux PLL CLock

}SysCtl_Cputimer2ClkSource;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_lockClkConfig()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CLK_REG_SEL_ALL  = 0x0000   //!< ALL lock
} SysCtl_ClkRegSel;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_lockSysConfig()
//! as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CPU_REG_SEL_ALL  = 0x0000,  //!< ALL lock
    SYSCTL_CPU_REG_SEL_BROMPATCH  = 0x0100   //!< BROMPATCH lock
} SysCtl_CpuRegSel;


//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_setUserRegister()
//! and SysCtl_getUserRegister() as the \e reg parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_USER_REG1_SYSRSN   = 0U, //!< User register reset by SYSRSn
    SYSCTL_USER_REG2_SYSRSN   = 1U, //!< User register reset by SYSRSn
    SYSCTL_USER_REG1_XRSN     = 2U, //!< User register reset by XRSn
    SYSCTL_USER_REG2_XRSN     = 3U, //!< User register reset by XRSn
    SYSCTL_USER_REG1_PORESETN = 4U, //!< User register reset by PORESETn
    SYSCTL_USER_REG2_PORESETN = 5U, //!< User register reset by PORESETn
    SYSCTL_USER_REG3_PORESETN = 6U, //!< User register reset by PORESETn
    SYSCTL_USER_REG4_PORESETN = 7U  //!< User register reset by PORESETn
}SysCtl_UserRegister;

//*****************************************************************************
//
//! Values that can be passed to SysCtl_disableCMPSSLPMWakeupPin() and 
//! SysCtl_enableCMPSSLPMWakeupPin() as the \e pin input parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_CMPSSLPMSEL_CMPSS_1H = 0x00,   
    SYSCTL_CMPSSLPMSEL_CMPSS_1L = 0x01,   
    SYSCTL_CMPSSLPMSEL_CMPSS_2H = 0x02,   
    SYSCTL_CMPSSLPMSEL_CMPSS_2L = 0x03,   
    SYSCTL_CMPSSLPMSEL_CMPSS_3H = 0x04,   
    SYSCTL_CMPSSLPMSEL_CMPSS_3L = 0x05,   
    SYSCTL_CMPSSLPMSEL_CMPSS_4H = 0x06,   
    SYSCTL_CMPSSLPMSEL_CMPSS_4L = 0x07,   
    SYSCTL_CMPSSLPMSEL_CMPSS_5H = 0x08,   
    SYSCTL_CMPSSLPMSEL_CMPSS_5L = 0x09,   
    SYSCTL_CMPSSLPMSEL_CMPSS_6H = 0x0A,   
    SYSCTL_CMPSSLPMSEL_CMPSS_6L = 0x0B
} SysCtl_CMPSSLPMSel;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Wrapper function for Device_cal function
//!
//! \param None
//!
//! This is a wrapper function for the Device_cal function available in the OTP
//! memory.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_deviceCal(void)
{

    //
    // Call the Device_cal function
    //
    Device_cal();

}

//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param peripheral is the peripheral to reset.
//!
//! This function uses the SOFTPRESx registers to reset a specified peripheral.
//! Module registers will be returned to their reset states.
//!
//! \note This includes registers containing trim values.The peripheral
//! software reset needed by CPU2 can be communicated to CPU1 via
//! IPC for all shared peripherals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetPeripheral(SysCtl_PeripheralSOFTPRES peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)2U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Sets the appropriate reset bit and then clears it.
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES_CTRL_PERIPH + regIndex) |=  (1UL << bitIndex);
    HWREG(DEVCFG_BASE + SYSCTL_O_SOFTPRES_CTRL_PERIPH + regIndex) &= ~(1UL << bitIndex);

    //
    // Call Device_cal function
    //
    if((((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0xDU) ||      // ADCx
       (((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0xFU) ||      // PGAx
       (((uint16_t)peripheral & SYSCTL_PERIPH_REG_M) == 0x10U)        // DACx
       )
    {
        SysCtl_deviceCal();
    }

    EDIS;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! \note Note that there should be atleast 5 cycles delay between enabling the
//! peripheral clock and accessing the peripheral registers. The delay should be
//! added by the user if the peripheral is accessed immediately after this
//! function call.
//! Use asm(" RPT #5 || NOP"); to add 5 cycle delay post this function call.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)2U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Turn on the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PERCLKCR + regIndex) |= (1UL << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)2U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    EALLOW;

    //
    // Turn off the module clock.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_PERCLKCR + regIndex) &= ~(1UL << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a watchdog reset of the device.
//!
//! \return This function does not return.
//
//*****************************************************************************
static inline void
SysCtl_resetDevice(void)
{
    //
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    //
    EALLOW;

    //
    // Enable the watchdog
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = SYSCTL_WD_CHKBITS;
    SYSCTL_REGWRITE_DELAY;

    //
    // Write a bad check value
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = 0U;
    SYSCTL_REGWRITE_DELAY;

    EDIS;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while((bool)1)
    {
    }
}

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of
//! - \b SYSCTL_CAUSE_POR - Power-on reset
//! - \b SYSCTL_CAUSE_XRS - External reset pin
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCSM
//! - \b SYSCTL_CAUSE_SIMRESET_CPU1RSN - SIMRESET_CPU1RSn
//! - \b SYSCTL_CAUSE_SIMRESET_XRSN - SIMRESET_XRSn
//!
//! \note If you re-purpose the reserved boot ROM RAM, the POR and XRS reset
//! statuses won't be accurate.
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getResetCause(void)
{
    uint32_t resetCauses;

    //
    // Read CPU reset register
    //
    resetCauses = HWREG(CPUSYS_BASE + SYSCTL_O_RESC) &
                  ((uint32_t)SYSCTL_RESC_POR | (uint32_t)SYSCTL_RESC_XRSN |
                   (uint32_t)SYSCTL_RESC_WDRSN |
                   (uint32_t)SYSCTL_RESC_NMIWDRSN |
                   (uint32_t)SYSCTL_RESC_SCCRESETN
                   | (uint32_t)SYSCTL_CAUSE_SIMRESET_CPU1RSN
                   | (uint32_t)SYSCTL_CAUSE_SIMRESET_XRSN
                   );

    //
    // Set POR and XRS Causes from boot ROM Status
    //
    if((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_POR) ==
       (uint32_t)SYSCTL_BOOT_ROM_POR)
    {
        resetCauses |= SYSCTL_RESC_POR;
    }
    if((HWREG(SYSCTL_BOOT_ROM_STATUS) & (uint32_t)SYSCTL_BOOT_ROM_XRS) ==
       (uint32_t)SYSCTL_BOOT_ROM_XRS)
    {
        resetCauses |= SYSCTL_RESC_XRSN;
    }

    //
    // Return the reset reasons.
    //
    return(resetCauses);
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param rstCauses are the reset causes to be cleared; must be a logical
//! OR of
//! - \b SYSCTL_CAUSE_POR - Power-on reset
//! - \b SYSCTL_CAUSE_XRS - External reset pin
//! - \b SYSCTL_CAUSE_WDRS - Watchdog reset
//! - \b SYSCTL_CAUSE_NMIWDRS - NMI watchdog reset
//! - \b SYSCTL_CAUSE_SCCRESET - SCCRESETn reset from DCSM
//! - \b SYSCTL_CAUSE_SIMRESET_CPU1RSN - SIMRESET_CPU1RSn
//! - \b SYSCTL_CAUSE_SIMRESET_XRSN - SIMRESET_XRSn
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtl_getResetCause().
//!
//! \note Some reset causes are cleared by the boot ROM.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearResetCause(uint32_t rstCauses)
{
    //
    // Clear the given reset reasons.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_RESCCLR) = rstCauses;
}

//*****************************************************************************
//
//! Sets the low speed peripheral clock rate prescaler.
//!
//! \param prescaler is the LSPCLK rate relative to SYSCLK
//!
//! This function configures the clock rate of the low speed peripherals. The
//! \e prescaler parameter is the value by which the SYSCLK rate is divided to
//! get the LSPCLK rate. For example, a \e prescaler of
//! \b SYSCTL_LSPCLK_PRESCALE_4 will result in a LSPCLK rate that is a quarter
//! of the SYSCLK rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setLowSpeedClock(SysCtl_LSPCLKPrescaler prescaler)
{
    //
    // Write the divider selection to the appropriate register.
    //
    EALLOW;
    HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) =
        (HWREG(CLKCFG_BASE + SYSCTL_O_LOSPCP) &
         ~(uint32_t)SYSCTL_LOSPCP_LSPCLKDIV_M) | (uint32_t)prescaler;
    EDIS;
}

//*****************************************************************************
//
//! Selects a clock source to mux to an external GPIO pin (XCLKOUT).
//!
//! \param source is the internal clock source to be configured.
//!
//! This function configures the specified clock source to be muxed to an
//! external clock out (XCLKOUT) GPIO pin. The \e source parameter may take a
//! value of one of the following values:
//! - \b SYSCTL_CLOCKOUT_PLLSYS
//! - \b SYSCTL_CLOCKOUT_PLLRAW
//! - \b SYSCTL_CLOCKOUT_SYSCLK
//! - \b SYSCTL_CLOCKOUT_WROSC
//! - \b SYSCTL_CLOCKOUT_SYSOSC
//! - \b SYSCTL_CLOCKOUT_WROSCDIV8
//! - \b SYSCTL_CLOCKOUT_SYSOSCDIV4
//! - \b SYSCTL_CLOCKOUT_XTALOSC
//! - \b SYSCTL_SYSPLLCLKOUT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_selectClockOutSource(SysCtl_ClockOut source)
{
    EALLOW;

    //
    // Clear clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) &=
        ~SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M;
    SYSCTL_CLKSRCCTL_DELAY;

    //
    // Set clock out source
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) |= (uint16_t)source;

    EDIS;
}

//*****************************************************************************
//
//! Set the external oscillator mode.
//!
//! \param mode is the external oscillator mode to be configured.
//!
//! This function sets the external oscillator mode specified by the \e mode
//! parameter which may take one of two values:
//! - \b SYSCTL_XTALMODE_CRYSTAL - Crystal Mode
//! - \b SYSCTL_XTALMODE_SINGLE  - Single-Ended Mode
//!
//! \note The external oscillator must be powered off before this configuration
//! can be performed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setExternalOscMode(SysCtl_ExternalOscMode mode)
{
    EALLOW;

    switch(mode)
    {
        case SYSCTL_XTALMODE_CRYSTAL:
            //
            // Set mode to Crystal
            //
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~(uint32_t)SYSCTL_XTALCR_SE;
            SYSCTL_REGWRITE_DELAY;
            break;

        case SYSCTL_XTALMODE_SINGLE:
            //
            // Set mode to Single-Ended
            //
            HWREG(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_SE;
            SYSCTL_REGWRITE_DELAY;
            break;

        default:
            //
            // Do nothing. Not a valid mode value.
            //
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Gets the external oscillator counter value.
//!
//! This function returns the X1 clock counter value. When the return value
//! reaches 0x3FF, it freezes. Before switching from SYSOSCDIV4 to an external
//! oscillator (XTAL), an application should call this function to make sure
//! the counter is saturated.
//!
//! \return Returns the value of the 10-bit X1 clock counter.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getExternalOscCounterValue(void)
{
    return(HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) & SYSCTL_X1CNT_X1CNT_M);
}

//*****************************************************************************
//
//! Clears the external oscillator counter value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearExternalOscCounterValue(void)
{
    HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
}

//*****************************************************************************
//
//! Turns on the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns on the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//!
//! \note \b SYSCTL_OSCSRC_WROSCDIV8 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOnOsc(uint32_t oscSource)
{
    ASSERT(
           (oscSource == SYSCTL_OSCSRC_XTAL)
          );

    EALLOW;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_XTAL:
            //
            // Turn on XTALOSC
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) &= ~SYSCTL_XTALCR_OSCOFF;
            SYSCTL_REGWRITE_DELAY;

            break;

        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Turns off the specified oscillator sources.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function turns off the oscillator specified by the \e oscSource
//! parameter which may take a value of  \b SYSCTL_OSCSRC_XTAL
//!
//! \note \b SYSCTL_OSCSRC_WROSCDIV8 is not a valid value for \e oscSource.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_turnOffOsc(uint32_t oscSource)
{
    ASSERT(
           (oscSource == SYSCTL_OSCSRC_XTAL)
          );

    EALLOW;

    switch(oscSource)
    {
        case SYSCTL_OSCSRC_XTAL:
            //
            // Turn off XTALOSC
            //
            HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
            SYSCTL_REGWRITE_DELAY;
            break;

        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }

    EDIS;
}

//*****************************************************************************
//
//! Enters IDLE mode.
//!
//! This function puts the device into IDLE mode. The CPU clock is gated while
//! all peripheral clocks are left running. Any enabled interrupt will wake the
//! CPU up from IDLE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterIdleMode(void)
{
    EALLOW;

    //
    // Configure the device to go into IDLE mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint32_t)SYSCTL_LPMCR_LPM_M) | SYSCTL_LPM_IDLE;

    EDIS;

#ifndef _DUAL_HEADERS
    IDLE;
#else
    IDLE_ASM;
#endif
}

//*****************************************************************************
//
//! Enters STANDBY mode.
//!
//! This function puts the device into STANDBY mode. This will gate both the
//! CPU clock and any peripheral clocks derived from SYSCLK. The watchdog is
//! left active, and an NMI or an optional watchdog interrupt will wake the
//! CPU subsystem from STANDBY mode.
//!
//! GPIOs may be configured to wake the CPU subsystem. See
//! SysCtl_enableLPMWakeupPin().
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterStandbyMode(void)
{
    EALLOW;

    //
    // Configure the device to go into STANDBY mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint32_t)SYSCTL_LPMCR_LPM_M) | SYSCTL_LPM_STANDBY;

    EDIS;

#ifndef _DUAL_HEADERS
    IDLE;
#else
    IDLE_ASM;
#endif
}

//*****************************************************************************
//
//! Enters HALT mode.
//!
//! This function puts the device into HALT mode. This will gate almost all
//! systems and clocks and allows for the power-down of oscillators and analog
//! blocks. The watchdog may be left clocked to produce a reset. See
//! SysCtl_enableWatchdogInHalt() to enable this. GPIOs should be
//! configured to wake the CPU subsystem. See SysCtl_enableLPMWakeupPin().
//!
//!
//! The CPU will receive an interrupt (WAKEINT) on wakeup.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enterHaltMode(void)
{
    EALLOW;

    //
    // Configure the device to go into HALT mode when IDLE is executed.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREG(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint32_t)SYSCTL_LPMCR_LPM_M) | SYSCTL_LPM_HALT;

    EDIS;

#ifndef _DUAL_HEADERS
    IDLE;
#else
    IDLE_ASM;
#endif
}

//*****************************************************************************
//! Enables a pin to wake up the device from the following mode(s):
//!  - STANDBY
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function connects a pin to the LPM circuit, allowing an event on the
//! pin to wake up the device when when it is in following mode(s):
//!  - STANDBY
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are capable of
//! being connected to the LPM circuit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = 1UL << (pin % 32U);

    EALLOW;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) |= pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) |= pinMask;
    }

    EDIS;
}

//*****************************************************************************
//! Disables a pin to wake up the device from the following mode(s):
//!  - STANDBY
//!  - HALT
//!
//! \param pin is the identifying number of the pin.
//!
//! This function disconnects a pin to the LPM circuit, disallowing an event on
//! the pin to wake up the device when when it is in following mode(s):
//!  - STANDBY
//!  - HALT
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin. Only GPIOs 0 through 63 are valid.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableLPMWakeupPin(uint32_t pin)
{
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(pin <= 63U);

    pinMask = 1UL << (pin % 32U);

    EALLOW;

    if(pin < 32U)
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL0) &= ~pinMask;
    }
    else
    {
        HWREG(CPUSYS_BASE + SYSCTL_O_GPIOLPMSEL1) &= ~pinMask;
    }

    EDIS;
}

//*****************************************************************************
//! Connects the selected pin to LPM circuit
//!
//! The \param pin parameter can be a value from the enumeration
//! SysCtl_CMPSSLPMSel
//!
//! This function connects a pin to the LPM circuit
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableCMPSSLPMWakeupPin(SysCtl_CMPSSLPMSel pin)
{
    uint32_t pinMask;

    pinMask = 1UL << (uint32_t)(pin);

    EALLOW;
        HWREG(CPUSYS_BASE + SYSCTL_O_CMPSSLPMSEL) |= pinMask;
    EDIS;
}

//*****************************************************************************
//! Disonnects the selected pin from LPM circuit
//!
//! The \param pin parameter can be a value from the enumeration
//! SysCtl_CMPSSLPMSel
//!
//! This function disconnects a pin from the LPM circuit
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableCMPSSLPMWakeupPin(SysCtl_CMPSSLPMSel pin)
{
    uint32_t pinMask;

    pinMask = 1UL << (uint32_t)(pin);

    EALLOW;
        HWREG(CPUSYS_BASE + SYSCTL_O_CMPSSLPMSEL) &= ~pinMask;
    EDIS;
}

//*****************************************************************************
//
//! Sets the number of cycles to qualify an input on waking from STANDBY mode.
//!
//! \param cycles is the number of OSCCLK cycles.
//!
//! This function sets the number of OSCCLK clock cycles used to qualify the
//! selected inputs when waking from STANDBY mode. The \e cycles parameter
//! should be passed a cycle count between 2 and 65 cycles inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setStandbyQualificationPeriod(uint16_t cycles)
{
    //
    // Check the arguments.
    //
    ASSERT((cycles >= 2U) && (cycles <= 65U));

    EALLOW;

    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) =
                (HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) &
                 ~(uint16_t)SYSCTL_LPMCR_QUALSTDBY_M) |
                ((cycles - 2U) << SYSCTL_LPMCR_QUALSTDBY_S);

    EDIS;
}

//*****************************************************************************
//
//! Enable the device to wake from STANDBY mode upon a watchdog interrupt.
//!
//! \note In order to use this option, you must configure the watchdog to
//! generate an interrupt using SysCtl_setWatchdogMode().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogStandbyWakeup(void)
{
    EALLOW;

    //
    // Set the bit enables the watchdog to wake up the device from STANDBY.
    //
    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) |= SYSCTL_LPMCR_WDINTE;

    EDIS;
}

//*****************************************************************************
//
//! Disable the device from waking from STANDBY mode upon a watchdog interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdogStandbyWakeup(void)
{
    EALLOW;

    //
    // Clear the bit enables the watchdog to wake up the device from STANDBY.
    //
    HWREGH(CPUSYS_BASE + SYSCTL_O_LPMCR) &= ~SYSCTL_LPMCR_WDINTE;

    EDIS;
}

//*****************************************************************************
//
//! Enable the watchdog to run while in HALT mode.
//!
//! This function configures the watchdog to continue to run while in HALT
//! mode. Additionally, WROSCDIV8 and SYSOSCDIV4 are not powered down when the
//! system enters HALT mode. By default the watchdog is gated when the system
//! enters HALT.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogInHalt(void)
{
    EALLOW;

    //
    // Set the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) |= SYSCTL_CLKSRCCTL1_WDHALTI;
    SYSCTL_CLKSRCCTL_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Disable the watchdog from running while in HALT mode.
//!
//! This function gates the watchdog when the system enters HALT mode. WROSCDIV8
//! and SYSOSCDIV4 will be powered down. This is the default behavior of the
//! device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdogInHalt(void)
{
    EALLOW;

    //
    // Clear the watchdog HALT mode ignore bit.
    //
    HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) &= ~SYSCTL_CLKSRCCTL1_WDHALTI;
    SYSCTL_CLKSRCCTL_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Configures whether the watchdog generates a reset or an interrupt signal.
//!
//! \param mode is a flag to select the watchdog mode.
//!
//! This function configures the action taken when the watchdog counter reaches
//! its maximum value. When the \e mode parameter is
//! \b SYSCTL_WD_MODE_INTERRUPT, the watchdog is enabled to generate a watchdog
//! interrupt signal and disables the generation of a reset signal. This will
//! allow the watchdog module to wake up the device from IDLE
//! or STANDBY if desired (see SysCtl_enableWatchdogStandbyWakeup()).
//!
//! When the \e mode parameter is \b SYSCTL_WD_MODE_RESET, the watchdog will
//! be put into reset mode and generation of a watchdog interrupt signal will
//! be disabled. This is how the watchdog is configured by default.
//!
//! \note Check the status of the watchdog interrupt using
//! SysCtl_isWatchdogInterruptActive() before calling this function. If the
//! interrupt is still active, switching from interrupt mode to reset mode will
//! immediately reset the device.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogMode(SysCtl_WDMode mode)
{
    EALLOW;

    //
    // Either set or clear the WDENINT bit to that will determine whether the
    // watchdog will generate a reset signal or an interrupt signal. Take care
    // not to write a 1 to WDOVERRIDE.
    //
    if(mode == SYSCTL_WD_MODE_INTERRUPT)
    {
        HWREGH(WD_BASE + SYSCTL_O_SCSR) =
                (HWREGH(WD_BASE + SYSCTL_O_SCSR) & ~SYSCTL_SCSR_WDOVERRIDE) |
                SYSCTL_SCSR_WDENINT;
    }
    else
    {
        HWREGH(WD_BASE + SYSCTL_O_SCSR) &= ~(SYSCTL_SCSR_WDENINT |
                                             SYSCTL_SCSR_WDOVERRIDE);
    }

    EDIS;
}

//*****************************************************************************
//
//! Gets the status of the watchdog interrupt signal.
//!
//! This function returns the status of the watchdog interrupt signal. If the
//! interrupt is active, this function will return \b true. If \b false, the
//! interrupt is NOT active.
//!
//! \note Make sure to call this function to ensure that the interrupt is not
//! active before making any changes to the configuration of the watchdog to
//! prevent any unexpected behavior. For instance, switching from interrupt
//! mode to reset mode while the interrupt is active will immediately reset the
//! device.
//!
//! \return \b true if the interrupt is active and \b false if it is not.
//
//*****************************************************************************
static inline bool
SysCtl_isWatchdogInterruptActive(void)
{
    //
    // If the status bit is cleared, the WDINTn signal is active.
    //
    return((HWREGH(WD_BASE + SYSCTL_O_SCSR) & SYSCTL_SCSR_WDINTS) == 0U);
}

//*****************************************************************************
//
//! Disables the watchdog.
//!
//! This function disables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableWatchdog(void)
{
    EALLOW;

    //
    // Set the disable bit.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) |= SYSCTL_WD_CHKBITS | SYSCTL_WDCR_WDDIS;
    SYSCTL_REGWRITE_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Enables the watchdog.
//!
//! This function enables the watchdog timer. Note that the watchdog timer is
//! enabled on reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdog(void)
{
    EALLOW;

    //
    // Clear the disable bit.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~SYSCTL_WDCR_WDDIS) | SYSCTL_WD_CHKBITS;
    SYSCTL_REGWRITE_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Checks if the watchdog is enabled or not
//!
//! This function returns the watchdog status whether it is enabled or disabled
//!
//! \return \b true if the watchdog is enabled & \b false if the watchdog is 
//! disabled
//
//*****************************************************************************
static inline bool
SysCtl_isWatchdogEnabled(void)
{

    //
    // Get the watchdog enable status
    //
    return ((HWREGH(WD_BASE + SYSCTL_O_WDCR) & SYSCTL_WDCR_WDDIS) == 0U);
}

//*****************************************************************************
//
//! Services the watchdog.
//!
//! This function resets the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_serviceWatchdog(void)
{
    EALLOW;

    //
    // Enable the counter to be reset and then reset it.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_ENRSTKEY;
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_RSTKEY;

    EDIS;
}

//*****************************************************************************
//
//! Writes the first key to enter the watchdog reset.
//!
//! This function writes the first key to enter the watchdog reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableWatchdogReset(void)
{
    EALLOW;

    //
    // Enable the counter to be reset
    //
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_ENRSTKEY;

    EDIS;
}

//*****************************************************************************
//
//! Writes the second key to reset the watchdog.
//!
//! This function writes the second key to reset the watchdog.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetWatchdog(void)
{
    EALLOW;

    //
    // Reset the watchdog counter
    //
    HWREGH(WD_BASE + SYSCTL_O_WDKEY) = SYSCTL_WD_RSTKEY;
    EDIS;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) pre-divider.
//!
//! \param predivider is the value that configures the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) pre-divider. There are two
//! dividers that scale WROSCDIV8 to WDCLK. The \e predivider parameter divides
//! WROSCDIV8 down to PREDIVCLK and the prescaler (set by the
//! SysCtl_setWatchdogPrescaler() function) divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPredivider(SysCtl_WDPredivider predivider)
{
    uint16_t regVal;

    regVal = (uint16_t)predivider | SYSCTL_WD_CHKBITS;

    EALLOW;

    //
    // Write the predivider to the appropriate register.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPRECLKDIV_M)) | regVal;
    SYSCTL_REGWRITE_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) prescaler.
//!
//! \param prescaler is the value that configures the watchdog clock relative
//! to the value from the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) prescaler. There are two
//! dividers that scale WROSCDIV8 to WDCLK. The predivider (set with the
//! SysCtl_setWatchdogPredivider() function) divides WROSCDIV8 down to PREDIVCLK
//! and the \e prescaler parameter divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPrescaler(SysCtl_WDPrescaler prescaler)
{
    uint16_t regVal;

    regVal = (uint16_t)prescaler | (uint16_t)SYSCTL_WD_CHKBITS;

    EALLOW;

    //
    // Write the prescaler to the appropriate register.
    //
    HWREGH(WD_BASE + SYSCTL_O_WDCR) = (HWREGH(WD_BASE + SYSCTL_O_WDCR) &
                                       ~(SYSCTL_WDCR_WDPS_M)) | regVal;
    SYSCTL_REGWRITE_DELAY;

    EDIS;
}

//*****************************************************************************
//
//! Gets the watchdog counter value.
//!
//! \return Returns the current value of the 8-bit watchdog counter. If this
//! count value overflows, a watchdog output pulse is generated.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getWatchdogCounterValue(void)
{
    //
    // Read and return the value of the watchdog counter.
    //
    return(HWREGH(WD_BASE + SYSCTL_O_WDCNTR));
}

//*****************************************************************************
//
//! Gets the watchdog reset status.
//!
//! This function returns the watchdog reset status. If this function returns
//! \b true, that indicates that a watchdog reset generated the last reset
//! condition. Otherwise, it was an external device or power-up reset
//! condition.
//!
//! \return Returns \b true if the watchdog generated the last reset condition.
//
//*****************************************************************************
static inline bool
SysCtl_getWatchdogResetStatus(void)
{
    //
    // Read and return the status of the watchdog reset status flag.
    //
    return((HWREGH(CPUSYS_BASE + SYSCTL_O_RESC) & SYSCTL_RESC_WDRSN) != 0U);
}

//*****************************************************************************
//
//! Clears the watchdog reset status.
//!
//! This function clears the watchdog reset status. To check if it was set
//! first, see SysCtl_getWatchdogResetStatus().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogResetStatus(void)
{
    EALLOW;

    //
    // Read and return the status of the watchdog reset status flag.
    //
    HWREGH(CPUSYS_BASE + SYSCTL_O_RESCCLR) = SYSCTL_RESCCLR_WDRSN;

    EDIS;
}

//*****************************************************************************
//
//! Set the minimum threshold value for windowed watchdog
//!
//! \param value is the value to set the window threshold
//!
//! This function sets the minimum threshold value used to define the lower
//! limit of the windowed watchdog functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogWindowValue(uint16_t value)
{
    EALLOW;

    //
    // Clear the windowed value
    //
    HWREGH(WD_BASE + SYSCTL_O_WDWCR) &= ~SYSCTL_WDWCR_MIN_M;

    //
    // Set the windowed value
    //
    HWREGH(WD_BASE + SYSCTL_O_WDWCR) |= (value & SYSCTL_WDWCR_MIN_M);

    EDIS;
}

//*****************************************************************************
//
//! Clears the watchdog override.
//!
//! This function clears the watchdog override and locks the watchdog timer
//! module to remain in its prior state which could be either enable /disable.
//! The watchdog timer will remain in this state until the next system reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogOverride(void)
{
    EALLOW;

    HWREGH(WD_BASE + SYSCTL_O_SCSR) |= SYSCTL_SCSR_WDOVERRIDE;

    EDIS;
}

//*****************************************************************************
//
//! Enable the NMI Global interrupt bit
//!
//! \b Note: This bit should be set after the device security related
//! initialization is complete.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableNMIGlobalInterrupt(void)
{
    EALLOW;

    HWREGH(NMI_BASE + NMI_O_CFG) |= NMI_CFG_NMIE;

    EDIS;
}

//*****************************************************************************
//
//! Read NMI interrupts.
//!
//! Read the current state of NMI interrupt.
//!
//! \return \b true if NMI interrupt is triggered, \b false if not.
//
//*****************************************************************************
static inline bool
SysCtl_getNMIStatus(void)
{
    //
    // Read and return the current value of the NMI flag register, masking out
    // all but the NMI bit.
    //
    return((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_NMIINT) != 0U);
}

//*****************************************************************************
//
//! Read NMI Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMIFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIFlagStatus(void)
{
    //
    // Read and return the current value of the NMI flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_FLG));
}

//*****************************************************************************
//
//! Check if the individual NMI interrupts are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIFlagSet(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                         SYSCTL_NMI_NMIINT       |
                         SYSCTL_NMI_CLOCKFAIL    |
                         SYSCTL_NMI_UNCERR       |
                         SYSCTL_NMI_SWERR
                         )) == 0U);

    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_FLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Function to clear individual NMI interrupts.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//!
//! Clear NMI interrupt flags that correspond with the passed in bit mask.
//!
//! \b Note: The NMI Interrupt flag is always cleared by default and
//! therefore doesn't have to be included in the bit mask.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearNMIStatus(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                         SYSCTL_NMI_NMIINT       |
                         SYSCTL_NMI_CLOCKFAIL    |
                         SYSCTL_NMI_UNCERR       |
                         SYSCTL_NMI_SWERR
                         )) == 0U);

    EALLOW;

    //
    // Clear the individual flags as well as NMI Interrupt flag
    //
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    EDIS;
}

//*****************************************************************************
//
//! Clear all the NMI Flags that are currently set.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearAllNMIFlags(void)
{
    uint16_t nmiFlags;

    //
    // Read the flag status register and then write to the clear register,
    // clearing all the flags that were returned plus the NMI flag.
    //
    EALLOW;

    nmiFlags = SysCtl_getNMIFlagStatus();
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = nmiFlags;
    HWREGH(NMI_BASE + NMI_O_FLGCLR) = NMI_FLG_NMIINT;

    EDIS;
}

//*****************************************************************************
//
//! Function to force individual NMI interrupt fail flags
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_forceNMIFlags(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                         SYSCTL_NMI_NMIINT       |
                         SYSCTL_NMI_CLOCKFAIL    |
                         SYSCTL_NMI_UNCERR       |
                         SYSCTL_NMI_SWERR
                        )) == 0U);

    EALLOW;

    //
    // Set the Flags for the individual interrupts in the NMI flag
    // force register
    //
    HWREGH(NMI_BASE + NMI_O_FLGFRC) |= nmiFlags;

    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog counter value.
//!
//! \b Note: The counter is clocked at the SYSCLKOUT rate.
//!
//! \return Returns the NMI watchdog counter register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogCounter(void)
{
    //
    // Read and return the NMI watchdog counter register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDCNT));
}

//*****************************************************************************
//
//! Sets the NMI watchdog period value.
//!
//! \param wdPeriod is the 16-bit value at which a reset is generated.
//!
//! This function writes to the NMI watchdog period register that holds the
//! value to which the NMI watchdog counter is compared. When the two registers
//! match, a reset is generated. By default, the period is 0xFFFF.
//!
//! \note If a value smaller than the current counter value is passed into the
//! \e wdPeriod parameter, a NMIRSn will be forced.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setNMIWatchdogPeriod(uint16_t wdPeriod)
{
    EALLOW;

    //
    // Write to the period register.
    //
    HWREGH(NMI_BASE + NMI_O_WDPRD) = wdPeriod;

    EDIS;
}

//*****************************************************************************
//
//! Gets the NMI watchdog period value.
//!
//! \return Returns the NMI watchdog period register's current value.
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIWatchdogPeriod(void)
{
    //
    // Read and return the NMI watchdog period register's value.
    //
    return(HWREGH(NMI_BASE + NMI_O_WDPRD));
}

//*****************************************************************************
//
//! Read NMI Shadow Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMISHDFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//
//*****************************************************************************
static inline uint32_t
SysCtl_getNMIShadowFlagStatus(void)
{
    //
    // Read and return the current value of the NMI shadow flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_SHDFLG));
}

//*****************************************************************************
//
//! Check if the individual NMI shadow flags are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants  to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT       -  NMI Interrupt Flag
//! - \b SYSCTL_NMI_CLOCKFAIL    -  Clock Fail Interrupt Flag
//! - \b SYSCTL_NMI_UNCERR       -  Flash/RAM/ROM Uncorrectable Error NMI Flag
//! - \b SYSCTL_NMI_SWERR        -  SW Error Force NMI Flag
//!
//! Check if interrupt flags corresponding to the passed in bit mask are
//! asserted.
//!
//! \return \b true if any of the NMI asked for in the parameter bit mask
//! is set. \b false if none of the NMI requested in the parameter bit mask are
//! set.
//
//*****************************************************************************
static inline bool
SysCtl_isNMIShadowFlagSet(uint16_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(
                         SYSCTL_NMI_NMIINT       |
                         SYSCTL_NMI_CLOCKFAIL    |
                         SYSCTL_NMI_UNCERR       |
                         SYSCTL_NMI_SWERR
                        )) == 0U);

    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_SHDFLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Enable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_MCLKOFF);

    EDIS;
}

//*****************************************************************************
//
//! Disable the missing clock detection (MCD) Logic
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKOFF;

    EDIS;
}

//*****************************************************************************
//
//! Get the missing clock detection Failure Status
//!
//! \note A failure means the oscillator clock is missing
//!
//! \return Returns \b true if a failure is detected or \b false if a
//! failure isn't detected
//
//*****************************************************************************
static inline bool
SysCtl_isMCDClockFailureDetected(void)
{
    //
    //  Check the status bit to determine failure
    //
    return((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U);
}

//*****************************************************************************
//
//! Reset the missing clock detection logic after clock failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_resetMCD(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKCLR;

    EDIS;
}

//*****************************************************************************
//
//! Re-connect missing clock detection clock source to stop simulating clock
//! failure
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_connectMCDClockSource(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) &= ~(SYSCTL_MCDCR_OSCOFF);

    EDIS;
}

//*****************************************************************************
//
//! Disconnect missing clock detection clock source to simulate clock failure.
//! This is for testing the MCD functionality.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disconnectMCDClockSource(void)
{
    EALLOW;

    HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_OSCOFF;

    EDIS;
}

//*****************************************************************************
//
//! Configures the sync output source.
//!
//! \param syncSrc is sync output source selection.
//!
//! This function configures the sync output source from the PWM modules. The
//! \e syncSrc parameter is a value \b SYSCTL_SYNC_OUT_SRC_XXXX, where XXXX is
//! a sync signal coming from an PWM such as SYSCTL_SYNC_OUT_SRC_PWM1SYNCOUT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setSyncOutputConfig(SysCtl_SyncOutputSource syncSrc)
{
    //
    // Write the sync output source selection to the appropriate register.
    //
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) =
        (HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSELECT) &
         ~((uint32_t)SYSCTL_SYNCSELECT_SYNCOUT_M)) |
        ((uint32_t)syncSrc << SYSCTL_SYNCSELECT_SYNCOUT_S);
    EDIS;

}
//*****************************************************************************
//
//! Enables PWM SOC signals to drive an external (off-chip) ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be enabled
//!
//! This function configures which PWM SOC signals are enabled as a source for
//! either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical OR
//! of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableExtADCSOCSource(uint32_t adcsocSrc)
{
    //
    // Set the bits that correspond to signal to be enabled.
    //
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) |= adcsocSrc;
    EDIS;
}

//*****************************************************************************
//
//! Disables PWM SOC signals from driving an external ADCSOC signal.
//!
//! \param adcsocSrc is a bit field of the selected signals to be disabled
//!
//! This function configures which PWM SOC signals are disabled as a source
//! for either ADCSOCAO or ADCSOCBO. The \e adcsocSrc parameter takes a logical
//! OR of \b SYSCTL_ADCSOC_SRC_PWMxSOCA/B values that correspond to different
//! signals.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_disableExtADCSOCSource(uint32_t adcsocSrc)
{
    //
    // Clear the bits that correspond to signal to be disabled.
    //
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_ADCSOCOUTSELECT) &= ~adcsocSrc;
    EDIS;
}

//*****************************************************************************
//
//! Locks the SOC Select of the Trig X-BAR.
//!
//! This function locks the external ADC SOC select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockExtADCSOCSelect(void)
{
    //
    // Lock the ADCSOCOUTSELECT bit of the SYNCSOCLOCK register.
    //
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) =
        SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT;
    EDIS;
}

//*****************************************************************************
//
//! Locks the Sync Select of the Trig X-BAR.
//!
//! This function locks Sync Input and Output Select of the Trig X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockSyncSelect(void)
{
    //
    // Lock the SYNCSELECT register.
    //
    EALLOW;
    HWREG(SYNCSOC_BASE + SYSCTL_O_SYNCSOCLOCK) = SYSCTL_SYNCSOCLOCK_SYNCSELECT;
    EDIS;
}
//*****************************************************************************
//
//! Get the Device Silicon Revision ID
//!
//! This function returns the silicon revision ID for the device.
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return Returns the silicon revision ID value.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getDeviceRevision(void)
{
    //
    // Returns the device silicon revision ID
    //
    return(HWREG(DEVCFG_BASE + SYSCTL_O_REVID));
}


//*****************************************************************************
//
//! Sets up XCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the XCLK divider. There is only one
//! divider that scales WROSCDIV8 to XCLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_XClkDivider
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setXClk(SysCtl_XClkDivider divider)
{
    //
    // Clears the divider then configures it.
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) =
                        (HWREGH(CLKCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) &
                         ~(SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M)) |
                        (uint16_t)divider;
    SYSCTL_REGWRITE_DELAY;
    EDIS;
}

//*****************************************************************************
//
//! Sets up PLLSYSCLK divider.
//!
//! \param divider is the value that configures the divider.
//!
//! This function sets up the PLLSYSCLK divider. There is only one
//! divider that scales PLLSYSCLK to generate the system clock.
//!
//! The \e divider parameter can have any value (even/odd) from 1-64
//!     0x0 = /1
//!     0x1 = /2
//!     0x2 = /3 (default on reset)
//!     0x3 = /4
//!     0x4 = /5
//!    ......
//!     0x3F =/64
//!
//! \return None.
//!
//! \note Please make sure to check if the PLL is locked and valid using the
//! SysCtl_isPLLValid() before setting the divider.
//
//*****************************************************************************
static inline void
SysCtl_setPLLSysClk(uint16_t divider)
{
    //
    // Clears the divider then configures it.
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) =
                    (HWREGH(CLKCFG_BASE + SYSCTL_O_SYSCLKDIVSEL) &
                     ~(SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M)) | divider;
    SYSCTL_REGWRITE_DELAY;
    EDIS;
}

//*****************************************************************************
//
//! Sets up CPU Timer 2  CLK source & divider.
//!
//! \param divider is the value that configures the divider.
//! \param source is the source for the clock divider
//!
//! This function sets up the CPU Timer 2 CLK divider based on the source that
//! is selected. There is only one divider that scales the "source" to
//! CPU Timer 2 CLK.
//!
//! The \e divider parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkDivider
//! The \e source parameter can have one enumerated value from
//! SysCtl_Cputimer2ClkSource
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setCputimer2Clk(SysCtl_Cputimer2ClkDivider divider,
                               SysCtl_Cputimer2ClkSource source)
{
  //
    // Clears the divider & the source, then configures it.
    //
    EALLOW;
    HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) =
                    (HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) &
                     ~(SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M |
                       SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M));
    SYSCTL_REGWRITE_DELAY;

    HWREGH(CPUSYS_BASE + SYSCTL_O_TMR2CLKCTL) |=
                    ((uint16_t)divider << SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S) |
                    ((uint16_t)source << SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S);
    SYSCTL_REGWRITE_DELAY;
    EDIS;
}

//*****************************************************************************
//
//! Gets the PIE Vector Fetch Error Handler Routine Address.
//!
//! The function indicates the address of the PIE Vector Fetch Error
//! handler routine.
//!
//! \return Error Handler Address.
//!
//! \note Its the responsibility of user to initialize this register. If this
//! register is not initialized, a default error handler at address
//! 0x3fffbe will get executed.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getPIEVErrAddr(void)
{
    return(HWREG(CPUSYS_BASE + SYSCTL_O_PIEVERRADDR));
}

//*****************************************************************************
//
//! Simulates a reset to the CPU1
//!
//! \param rstCauses is the cause for the reset.
//!
//! The \e rstCauses parameter can be one/ more of these values:
//! SYSCTL_SIMRESET_CPU1RSN or SYSCTL_SIMRESET_XRSN
//!
//! \return None.
//!
//! \note This API exists only on CPU1
//
//*****************************************************************************
static inline void
SysCtl_simulateReset(uint32_t rstCauses)
{
    ASSERT((rstCauses == SYSCTL_SIMRESET_CPU1RSN) ||
           (rstCauses == SYSCTL_SIMRESET_XRSN));
    //
    //Write will succeed only if a matching key value is written
    //to the KEY field
    //Sets the appropriate reset bit.
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_SIMRESET) = (rstCauses |
                                              (SYSCTL_REG_KEY &
                                               SYSCTL_SIMRESET_KEY_M));
}

//*****************************************************************************
//
//! Gets the status of interrupts due to multiple different
//! errors in the system.
//!
//! \return the Interrupt generated on the system.
//! The values can be one/ more from:
//! - SYSCTL_STATUS_CORRECTABLE_ERR
//! - SYSCTL_STATUS_FPU_UFLOW
//! - SYSCTL_STATUS_FPU_OFLOW
//
//*****************************************************************************
static inline uint32_t
SysCtl_getInterruptStatus(void)
{
    return(HWREG(SYSSTAT_BASE + SYSCTL_O_SYS_ERR_INT_FLG));
}
//*****************************************************************************
//
//! Clears the interrupts due to multiple different errors in the system.
//!
//! \param intFlags is the interrupt that needs to be cleared.
//!
//! The \e intFlags parameter are the Interrupts generated on errors in
//! the system that need to be cleared. The values can be one or more from:
//! - SYSCTL_STATUS_GINT
//! - SYSCTL_STATUS_CORRECTABLE_ERR
//! - SYSCTL_STATUS_FPU_UFLOW
//! - SYSCTL_STATUS_FPU_OFLOW
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearInterruptStatus(uint32_t intFlags)
{
    HWREG(SYSSTAT_BASE + SYSCTL_O_SYS_ERR_INT_CLR) = intFlags;
}
//*****************************************************************************
//
//! Sets the interrupts for the multiple different errors in the system.
//!
//! \param intFlags is the interrupt that needs to be set.
//!
//! The \e intFlags parameter are the Interrupts that can be set
//! for the errors in the system. The values can be one/ more from:
//! - SYSCTL_STATUS_CORRECTABLE_ERR
//! - SYSCTL_STATUS_FPU_UFLOW
//! - SYSCTL_STATUS_FPU_OFLOW
//!
//! \return None.
//!
//! \note This API  is present only on CPU1.
//
//*****************************************************************************
static inline void
SysCtl_setInterruptStatus(uint32_t intFlags)
{
    EALLOW;
    HWREG(SYSSTAT_BASE + SYSCTL_O_SYS_ERR_INT_SET) =
                (intFlags | (SYSCTL_REG_KEY & SYSCTL_SYS_ERR_INT_SET_KEY_M));
    EDIS;
}

//*****************************************************************************
//
//! Gets the masked interrupts due to multiple different
//! errors in the system.
//!
//! \return the Interrupt generated on the system.
//! The values can be one/ more from:
//! - SYSCTL_STATUS_CORRECTABLE_ERR
//! - SYSCTL_STATUS_FPU_UFLOW
//! - SYSCTL_STATUS_FPU_OFLOW
//
//*****************************************************************************
static inline uint32_t
SysCtl_getInterruptStatusMask(void)
{
    return(HWREG(SYSSTAT_BASE + SYSCTL_O_SYS_ERR_MASK));
}

//*****************************************************************************
//
//! Masks the interrupts for the multiple different errors in the system.
//!
//! \param intFlags is the interrupt that needs to be set.
//!
//! The \e intFlags parameter are the Interrupts that can be masked
//! for the errors in the system. The values can be one/ more from:
//! - SYSCTL_STATUS_CORRECTABLE_ERR
//! - SYSCTL_STATUS_FPU_UFLOW
//! - SYSCTL_STATUS_FPU_OFLOW
//!
//! \return None.
//!
//! \note This API  is present only on CPU1.
//
//*****************************************************************************
static inline void
SysCtl_setInterruptStatusMask(uint32_t intFlags)
{
    EALLOW;
    HWREG(SYSSTAT_BASE + SYSCTL_O_SYS_ERR_MASK) =
                (intFlags | (SYSCTL_REG_KEY & SYSCTL_SYS_ERR_MASK_KEY_M));
    EDIS;
}

//*****************************************************************************
//
//!  Check if One or more of the error sources triggered
//!
//!  Following are the events/triggers that can indicate an error:
//!1. nmi interrupt on C28x
//!2. Watchdog reset
//!3. Error on a Pie vector fetch
//!4. Efuse error
//!5. nmi interrupt on CM
//!
//! \return \b true if the error is triggered
//! \b false if the error is not triggered
//
//*****************************************************************************
static inline bool
SysCtl_isErrorTriggered(void)
{
    return((HWREGH(NMI_BASE + NMI_O_ERRORSTS) & NMI_ERRORSTS_ERROR) != 0U);
}

//*****************************************************************************
//
//!  Check if Error status pin is high or not
//!
//! \return \b true if the error status pin is high
//! \b false if the error status pin is low
//
//*****************************************************************************
static inline bool
SysCtl_getErrorPinStatus(void)
{
    //
    // Read and return the status of the ErrorPin
    //
    return((HWREGH(NMI_BASE + NMI_O_ERRORSTS) & NMI_ERRORSTS_PINSTS) != 0U);
}

//*****************************************************************************
//
//! Forces an error flag to set to indicate an error being generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_forceError(void)
{
    EALLOW;
    HWREGH(NMI_BASE + NMI_O_ERRORSTSFRC) |= NMI_ERRORSTSFRC_ERROR;
    EDIS;
}

//*****************************************************************************
//
//! Clears any error flag set due to error generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearError(void)
{
    EALLOW;
    HWREGH(NMI_BASE + NMI_O_ERRORSTSCLR) |= NMI_ERRORSTSCLR_ERROR;
    EDIS;
}

//*****************************************************************************
//
//! Selects the polarity of the error pin
//!
//! \param pol is the ERROR pin polarity
//!
//! The \e pol parameter can take any of the below values:
//! 0x0U: If an error is already triggered, Error pin will be driven
//! with a value of 0, else 1.
//! 0x1U: If an error is already triggered, Error pin will be driven
//! with a value of 1, else 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_selectErrPinPolarity(uint16_t pol)
{
    EALLOW;
    //
    //Configures the error pin polarity based on the provided polarity
    //
    if(pol == 1U)
    {
        HWREGH(NMI_BASE + NMI_O_ERRORCTL) |= NMI_ERRORCTL_ERRORPOLSEL;
    }
    else
    {
        HWREGH(NMI_BASE + NMI_O_ERRORCTL) &= ~NMI_ERRORCTL_ERRORPOLSEL;
    }
    EDIS;
}

//*****************************************************************************
//
//! Locks the Error control registers
//!
//! This function locks the Error configuration registers.
//!
//! \return None.
//!
//! \note The lock register is cleared only on a system reset.
//
//*****************************************************************************
static inline void
SysCtl_lockErrControl(void)
{
    EALLOW;
    HWREG(NMI_BASE + NMI_O_ERRORLOCK) = NMI_ERRORLOCK_ERRORCTL;
    EDIS;
}

//*****************************************************************************
//
//! Sets the user register.
//!
//! \param reg is the register to be set
//! \param value is the value to be set
//!
//! This function sets sepcified user register.
//! The \e value parameter can have one enumerated value from
//! SysCtl_UserRegister.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setUserRegister(SysCtl_UserRegister reg, uint32_t value)
{
    //
    // Write to the user register
    //
    HWREG(CPUSYS_BASE + SYSCTL_O_USER_REG1_SYSRSN + ((uint16_t)reg * 2U)) = value;
}

//*****************************************************************************
//
//! Gets the user register.
//!
//! \param reg is the register to be set
//!
//! This function sets sepcified user register.
//! The \e value parameter can have one enumerated value from
//! SysCtl_UserRegister.
//!
//! \return value of the specified register.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getUserRegister(SysCtl_UserRegister reg)
{
    //
    // Return to the user register value
    //
    return(HWREG(CPUSYS_BASE + SYSCTL_O_USER_REG1_SYSRSN +
                 ((uint16_t)reg * 2U)));
}

//*****************************************************************************
//
//! Get the device UID_UNIQUE0 value
//!
//! This function returns the device UID_UNIQUE0 value
//!
//! \return Returns the device UID_UNIQUE0 value
//
//*****************************************************************************
static inline uint32_t
SysCtl_getDeviceUID0(void)
{
    //
    // Returns the device UID_UNIQUE0 value
    //
    return(HWREG(UID_BASE + OTP_O_UID_UNIQUE0));
}

//*****************************************************************************
//
//! Get the device UID_UNIQUE1 value
//!
//! This function returns the device UID_UNIQUE1 value
//!
//! \return Returns the device UID_UNIQUE1 value
//
//*****************************************************************************
static inline uint32_t
SysCtl_getDeviceUID1(void)
{
    //
    // Returns the device UID_UNIQUE1 value
    //
    return(HWREG(UID_BASE + OTP_O_UID_UNIQUE1));
}

//*****************************************************************************
//
//! Get the status of JTAG State machine and debugger connect
//!
//! This function returns the JTAG status
//!
//! \return Returns the JTAG status. The bits representing will be -
//! 0:TLR,
//! 1:IDLE,
//! 2:SELECTDR,
//! 3:CAPDR,
//! 4:SHIFTDR,
//! 5:EXIT1DR,
//! 6:PAUSEDR,
//! 7:EXIT2DR,
//! 8:UPDTDR,
//! 9:SLECTIR,
//! 10:CAPIR,
//! 11:SHIFTIR,
//! 12:EXIT1IR,
//! 13:PAUSEIR,
//! 14:EXIT2IR,
//! 15:UPDTIR
//
//*****************************************************************************
static inline uint32_t
SysCtl_getTapStatus(void)
{
    //
    // Returns the Tap status
    //
    return(HWREG(DEVCFG_BASE + SYSCTL_O_TAP_STATUS));
}
//*****************************************************************************
//
//! Delays for a fixed number of cycles.
//!
//! \param count is the number of delay loop iterations to perform.
//!
//! This function generates a constant length delay using assembly code. The
//! loop takes 5 cycles per iteration plus 9 cycles of overhead.
//!
//! \note If count is equal to zero, the loop will underflow and run for a
//! very long time.
//!
//! \note Refer to the macro DEVICE_DELAY_US(x) in device.h which can be used to
//! insert a delay in microseconds.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_delay(uint32_t count);

//*****************************************************************************
//
//! Calculates the system clock frequency (SYSCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the system clock based on the
//! frequency of the oscillator clock source (from \e clockInHz) and the PLL
//! and clock divider configuration registers.
//!
//! \return Returns the system clock frequency. If a missing clock is detected,
//! the function will return the WROSCDIV8 frequency. This needs to be
//! corrected and cleared (see SysCtl_resetMCD()) before trying to call this
//! function again.
//
//*****************************************************************************
extern uint32_t
SysCtl_getClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Configures the clocking of the device.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! \param oscSrc PLL Source. Can be one of the following values :
//!     - \b SYSCTL_OSCSRC_SYSOSCDIV4       - System Oscillator
//!     - \b SYSCTL_OSCSRC_XTAL             - External XTAL
//!     - \b SYSCTL_OSCSRC_XTAL_SE          - External XTAL Single-ended mode
//!     - \b SYSCTL_OSCSRC_WROSCDIV8        - Wide-range Oscillator 1
//!
//! \param pllConfig PLL configuration. Can be one fo the following values :
//!     - \b SYSCTL_PLL_ENABLE - This is to Enable the PLL Clock to the System
//!     - \b SYSCTL_PLL_BYPASS - This is to Bypass the PLLCLK from the System,
//!        this will also power up the PLL if the user desires to power up the
//!        PLL but not use it for System.
//!     - \b SYSCTL_PLL_DISABLE - This is to Power Down the PLL and Bypass the
//!        PLLCLK to the System.
//!
//! \param pDiv Input Clock Divider. Use Enum SYSCTL_PDIV_1..8
//! \param multiplier  PLL Multiplier. Use Enum SYSCTL_PLLMULT_2..128
//! \param rDivClk0   Output Clock Divider. Use Enum SYSCTL_RDIVCLK0_2..32
//! \param sysDiv SYSCLK Divider. Use Enum SYSCTL_SYSDIV_1..64
//! \param dccBase Base address of DCC module for PLL output validation
//!
//! This function uses the DCC to check that the PLLRAWCLK is running at the
//! expected rate. If you are using the DCC, you must back up its configuration
//! before calling this function and restore it afterward.
//! Locking PLL sequence is only done if the multipliers are updated.
//!
//! \note See your device errata for more details about locking the PLL.
//!
//! \return Returns \b false if a missing clock error is detected. This needs
//! to be cleared (see SysCtl_resetMCD()) before trying to call this function
//! again. Also, returns \b false if the PLLRAWCLK is not running and its
//! expected rate. Otherwise, returns \b true.
//
//*****************************************************************************
extern bool
SysCtl_setClock(uint32_t oscSrc, Sysctl_PLLConfig pllConfig,
                Sysctl_PLLPDiv pDiv, Sysctl_PLLMult multiplier,
                Sysctl_PLLRDivClk0 rDiv, Sysctl_PLLSysDiv sysDiv, uint32_t dccBase);

//*****************************************************************************
//
//! Validates PLL Raw Clock Frequency (PLLRAWCLK)
//!
//! \param base is the DCC module base address
//! \param oscSource PLL Source. Can be one of the following values :
//!     - \b SYSCTL_OSCSRC_SYSOSCDIV4       - System Oscillator
//!     - \b SYSCTL_OSCSRC_XTAL             - External XTAL
//!     - \b SYSCTL_OSCSRC_XTAL_SE          - External XTAL Single-ended mode
//!     - \b SYSCTL_OSCSRC_WROSCDIV8        - Wide-range Oscillator 1
//! \param pDiv Input Clock Divider. Use Enum SYSCTL_PDIV_1..8
//! \param multiplier  PLL Multiplier. Use Enum SYSCTL_PLLMULT_2..128
//! \param rDivClk0   Output Clock Divider. Use Enum SYSCTL_RDIVCLK0_2..32
//!
//!  This function uses DCC module to validate the PLL clock frequency.
//!  It uses oscSource as a reference clock for DCC, and PLL is used as clock
//!  under test. As long as the Counter0 (running of oscSource) & Counter1
//!  (running of PLL) expire at the same time, DCC will not generate an Error.
//!  This function gives 100 attempts for PLL to lock and make sure frequency
//!  is as expected.
//!
//!  \note This function does not validate if PLL output frequency (PLLRAWCLK)
//!  is within the operating range as per the datasheet.
//!
//!  \return Returns \b true if the DCCSTATUS error flag is not set.
//!    Otherwise, returns \b false.
//
//*****************************************************************************
extern bool
SysCtl_isPLLValid(uint32_t dccBase, uint32_t oscSource,
                  Sysctl_PLLPDiv pDiv, Sysctl_PLLMult multiplier,
                  Sysctl_PLLRDivClk0 rDiv);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in crystal mode. It follows the procedure to turn on
//! the oscillator, wait for it to power up, and select it as the source of the
//! system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTAL(void);

//*****************************************************************************
//
//! Configures the external oscillator for the clocking of the device in
//! single-ended mode.
//!
//! This function configures the external oscillator (XTAL) to be used for the
//! clocking of the device in single-ended mode. It follows the procedure to
//! turn on the oscillator, wait for it to power up, and select it as the
//! source of the system clock.
//!
//! Please note that this function blocks while it waits for the XTAL to power
//! up. If the XTAL does not manage to power up properly, the function will
//! loop for a long time. It is recommended that you modify this function to
//! add an appropriate timeout and error-handling procedure.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectXTALSingleEnded(void);

//*****************************************************************************
//
//! Selects the oscillator to be used for the clocking of the device.
//!
//! \param oscSource is the oscillator source to be configured.
//!
//! This function configures the oscillator to be used in the clocking of the
//! device. The \e oscSource parameter may take a value of
//! \b SYSCTL_OSCSRC_SYSOSCDIV4, \b SYSCTL_OSCSRC_XTAL,
//! \b SYSCTL_OSCSRC_XTAL_SE, or \b SYSCTL_OSCSRC_WROSCDIV8.
//!
//! \sa SysCtl_turnOnOsc()
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_selectOscSource(uint32_t oscSource);

//*****************************************************************************
//
//! Calculates the low-speed peripheral clock frequency (LSPCLK).
//!
//! \param clockInHz is the frequency of the oscillator clock source (OSCCLK).
//!
//! This function determines the frequency of the low-speed peripheral clock
//! based on the frequency of the oscillator clock source (from \e clockInHz)
//! and the PLL and clock divider configuration registers.
//!
//! \return Returns the low-speed peripheral clock frequency.
//
//*****************************************************************************
extern uint32_t
SysCtl_getLowSpeedClock(uint32_t clockInHz);

//*****************************************************************************
//
//! Get the device part parametric value
//!
//! \param parametric is the requested device parametric value
//!
//! This function gets the device part parametric value.
//!
//! The \e parametric parameter can have one the following enumerated values:
//! - \b SYSCTL_DEVICE_QUAL      - Device Qualification Status
//! - \b SYSCTL_DEVICE_PINCOUNT  - Device Pin Count
//! - \b SYSCTL_DEVICE_FLASH     - Device Flash size (KB)
//! - \b SYSCTL_DEVICE_FAMILY    - Device Family
//! - \b SYSCTL_DEVICE_PARTNO    - Device Part Number
//! - \b SYSCTL_DEVICE_CLASSID   - Device Class ID
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return Returns the specified parametric value.
//
//*****************************************************************************
extern uint16_t
SysCtl_getDeviceParametric(SysCtl_DeviceParametric parametric);

//*****************************************************************************
//
//! Configures & locks/unlocks the peripheral type
//!
//! \param type is the peripheral type that needs to be configured.
//! \param config is the configuration done to the peripheral which is
//!  dependent on the peripheral type.
//! \param lock is to decide if writes for any further configuration is to
//!  be allowed or not.
//!
//! The \e type parameter can be a value from the enumeration
//! SysCtl_SelType
//! The \e config parameter can be a value from the ones below:
//! 0x0U : disables the feature for the type.
//! 0x1U : enables the feature for the type.
//!
//! For ECAP: ECAP registers are EALLOW protected or not.
//!
//! The \e lock parameter can be a value from the ones below:
//! 0x1U : Write for any further configuration is not allowed.
//! 0x0U : Write for any further configuration is allowed.
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_configureType(SysCtl_SelType type , uint16_t config, uint16_t lock);

//*****************************************************************************
//
//!  Check if writes for any further configuration of peripheral types is to
//!  be allowed or not.
//!
//! \param type is the peripheral type for which permissions are being checked
//!
//! \note This API is applicable only for the CPU1 subsystem.
//!
//! \return \b true if Write for any further configuration is not allowed.
//! \b false if Write for any further configuration is allowed.
//
//*****************************************************************************
extern bool
SysCtl_isConfigTypeLocked(SysCtl_SelType type);

//*****************************************************************************
//
//! Locks the Clock configuration registers
//!
//! \param registerName is clock configuration register which needs to
//! be locked.
//!
//! The \e registerName parameter can be a value from the enumeration
//! SysCtl_ClkRegSel
//!
//! \return None.
//!
//! \note The register is unlocked only on a system reset.
//
//*****************************************************************************

extern void
SysCtl_lockClkConfig(SysCtl_ClkRegSel registerName);

//*****************************************************************************
//
//! Locks the CPU system configuration registers
//!
//! \param registerName is CPU system configuration register which needs to
//! be locked.
//!
//! The \e registerName parameter can be a value from the enumeration
//! SysCtl_CpuRegSel
//!
//! \return None.
//!
//! \note The register is unlocked only on a system reset.
//
//*****************************************************************************

extern void
SysCtl_lockSysConfig (SysCtl_CpuRegSel registerName);


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // SYSCTL_H
