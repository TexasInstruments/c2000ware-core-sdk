//###########################################################################
//
// FILE:   sysctl.h
//
// TITLE:  CM system control driver.
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
//! \brief The System Control module is used for miscellaneous system
//! configurations.
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_nmi.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_wwd.h"
#include "debug.h"
#include "cpu.h"

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
//Keys for the NMI registers write protection
//
#define SYSCTL_CMNMIFLGCLR_KEY 0x5674U
#define SYSCTL_CMNMIFLGFRC_KEY 0x2732U
#define SYSCTL_CMNMICFG_KEY 0x6789U
#define SYSCTL_CMNMIWDPRD_KEY 0x9238U

//
//Keys for the CPU Sysctrl registers write protection
//
#define SYSCTL_CMSYSCTL_KEY 0x5634U

//
//Keys for the WD registers write protection
//
#define SYSCTL_WWD_KEY 0x1234U

//
//Enable / disable the ETHERCAT I2C Loopback
//
#define SYSCTL_ETHERCAT_I2C_LOOPBACK 0x1U

//
//Enable / disable the Global NMI
//
#define SYSCTL_NMI_GLOBAL 0x1U

//*****************************************************************************
//
// Values that can be passed to SysCtl_clearNMIStatus(),
// SysCtl_forceNMIFlags(), SysCtl_isNMIFlagSet(), and
// SysCtl_isNMIShadowFlagSet() as the nmiFlags parameter and returned by
// SysCtl_getNMIFlagStatus() and SysCtl_getNMIShadowFlagStatus().
//
//*****************************************************************************
#define SYSCTL_NMI_NMIINT           0x0001U //!< Non-maskable interrupt
#define SYSCTL_NMI_CLOCKFAIL        0x0002U //!< Clock Failure
#define SYSCTL_NMI_MEMUNCERR        0x0004U //!< RAM/ROM Uncorrectable error
#define SYSCTL_NMI_FLUNCERR         0x0008U //!< Uncorrectable Flash error
#define SYSCTL_NMI_MCANUNCERR       0x0010U //!< MCAN Uncorrectable Error
#define SYSCTL_NMI_WWDNMI           0x0020U //!< CM Windowed Watchdog
#define SYSCTL_NMI_ECATNMI          0x0040U //!< EtherCAT reset out

//*****************************************************************************
//
// The following are values that can be passed to the SysCtl_clearResetCause()
// API as rstCauses or returned by the SysCtl_getResetCause() API.
//
//*****************************************************************************
#define SYSCTL_CAUSE_PORESETN            0x00000001U //!< Power-on reset
#define SYSCTL_CAUSE_XRSN                0x00000002U //!< External reset pin
#define SYSCTL_CAUSE_CPU1WDRSN           0x00000004U //!< CPU1 Watchdog reset
#define SYSCTL_CAUSE_CPU1NMIWDRSN        0x00000008U //!< CPU1 NMI WD reset
#define SYSCTL_CAUSE_CPU1SYSRSN          0x00000010U //!< CPU1 System reset
#define SYSCTL_CAUSE_CPU1SCCRESETN       0x00000020U //!< CPU1 SCCRESETn reset
#define SYSCTL_CAUSE_ECAT_RESET_OUT      0x00000040U //!< ECAT Reset
#define SYSCTL_CAUSE_CPU1SIMRESET_CPURSN 0x00000080U //!< SIMRESET_CPURSn-CPU1
#define SYSCTL_CAUSE_CMRSTCTLRESETREQ    0x00000100U //!< Reset req from CM
#define SYSCTL_CAUSE_CMVECTRESETN        0x00010000U //!< CM Vector Reset
#define SYSCTL_CAUSE_CMSYSRESETREQ       0x00020000U //!< CM System reset
#define SYSCTL_CAUSE_CMNMIWDRSTN         0x00040000U //!< CM NMI WD Reset
#define SYSCTL_CAUSE_CMEOLRESETN         0x00080000U //!< CM Execute Override
                                                     //!< Logic reset

//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtl_lockAccessControlRegs() API as access protection of
// which control Registers.
//
//*****************************************************************************

#define SYSCTL_CMECATCTL_LOCK 0x1U //!<block writes to CM-Ethercat control Reg

//*****************************************************************************
//
// This frequency will be the CM clock frequency driven by c28x.
//
//*****************************************************************************

#ifndef CM_CLK_FREQ
#define CM_CLK_FREQ       125000000U
#endif

//*****************************************************************************
//
// SysCtl delay macro defined to allow a delay of fixed cycles.
// This asm macro would be called through the SysCtl_delay API.
//
//*****************************************************************************

#define SYSCTL_DELAY  __asm(  "    .sect \".TI.ramfunc\"\n"                    \
                              "    .clink\n"                                   \
                              "    .thumbfunc SysCtl_delay\n"                  \
                              "    .thumb\n"                                   \
                              "    .global SysCtl_delay\n"                     \
                              "SysCtl_delay:\n"                                \
                              "    subs r0, #1\n"                              \
                              "    bne.n SysCtl_delay\n"                       \
                              "    bx lr\n");
//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_enablePeripheral()
//! and SysCtl_disablePeripheral() as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    //
    // PCLKCR0
    //
    SYSCTL_PERIPH_CLK_UART0      = 0x0000U,  //!< UART0 clock
    SYSCTL_PERIPH_CLK_SSI0       = 0x0400U,  //!< SSI0 clock
    SYSCTL_PERIPH_CLK_I2C0       = 0x0800U,  //!< I2C0 clock
    SYSCTL_PERIPH_CLK_USB        = 0x0C00U,  //!< USB clock

    //
    // PCLKCR1
    //
    SYSCTL_PERIPH_CLK_ENET       = 0x0001U,  //!< ENET clock
    SYSCTL_PERIPH_CLK_ECAT       = 0x0201U,  //!< ECAT clock
    SYSCTL_PERIPH_CLK_CAN_A      = 0x0401U,  //!< CAN_A clock
    SYSCTL_PERIPH_CLK_CAN_B      = 0x0501U,  //!< CAN_B clock
    SYSCTL_PERIPH_CLK_MCAN_A     = 0x0801U,  //!< MCAN_A clock

    //
    // PCLKCR2
    //
    SYSCTL_PERIPH_CLK_TIMER0      = 0x0002U,  //!< CPUtimer0 clock
    SYSCTL_PERIPH_CLK_TIMER1      = 0x0102U,  //!< CPUtimer1 clock
    SYSCTL_PERIPH_CLK_TIMER2      = 0x0202U,  //!< CPUtimer2 clock
    SYSCTL_PERIPH_CLK_UDMA        = 0x0402U,  //!< UDMA clock
    SYSCTL_PERIPH_CLK_AESIP       = 0x0602U,  //!< AESIP clock
    SYSCTL_PERIPH_CLK_GCRC        = 0x0802U,  //!< GCRC clock

} SysCtl_PeripheralPCLOCKCR;

//*****************************************************************************
//
//! The following are values that can be passed to SysCtl_resetPeripheral() as
//! the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    //
    // SOFTPRES0
    //
    SYSCTL_PERIPH_RES_UART0      = 0x0000U,  //!< UART0 Reset
    SYSCTL_PERIPH_RES_SSI0       = 0x0400U,  //!< SSI0 Reset
    SYSCTL_PERIPH_RES_I2C0       = 0x0800U,  //!< I2C0 Reset
    SYSCTL_PERIPH_RES_USB        = 0x0C00U,  //!< USB Reset

    //
    // SOFTPRES1
    //
    SYSCTL_PERIPH_RES_ENET       = 0x0001U,  //!< ENET Reset
    SYSCTL_PERIPH_RES_ECAT       = 0x0201U,  //!< ECAT Reset
    SYSCTL_PERIPH_RES_CAN_A      = 0x0401U,  //!< CAN_A Reset
    SYSCTL_PERIPH_RES_CAN_B      = 0x0501U,  //!< CAN_B Reset
    SYSCTL_PERIPH_RES_MCAN_A     = 0x0801U,  //!< MCAN_A Reset

    //
    // SOFTPRES2
    //
    SYSCTL_PERIPH_RES_AESIP       = 0x0602U,  //!< AESIP Reset
    SYSCTL_PERIPH_RES_GCRC        = 0x0802U,  //!<GCRC Reset


} SysCtl_PeripheralSOFTPRES;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_isPeripheralClockStopAcked()as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    //
    // CMCLKSTOPACK1
    //
    SYSCTL_PERIPH_ACK_MCAN_A      = 0x0800U,  //!< MCAN_A clock

} SysCtl_PeripheralCMCLKSTOPACK;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_reqPeripheralClockStop()as the \e peripheral parameter.
//
//*****************************************************************************
typedef enum
{
    //
    //CMCLKSTOPREQ1
    //
    SYSCTL_PERIPH_REQ_MCAN_A      = 0x0801U,  //!< MCAN_A clock

} SysCtl_PeripheralCMCLKSTOPREQ;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPredivider() as the \e predivider parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PREDIV_2    = 0x800U,  //!< PREDIVCLK = INTOSC1 / 2
    SYSCTL_WD_PREDIV_4    = 0x900U,  //!< PREDIVCLK = INTOSC1 / 4
    SYSCTL_WD_PREDIV_8    = 0xA00U,  //!< PREDIVCLK = INTOSC1 / 8
    SYSCTL_WD_PREDIV_16   = 0xB00U,  //!< PREDIVCLK = INTOSC1 / 16
    SYSCTL_WD_PREDIV_32   = 0xC00U,  //!< PREDIVCLK = INTOSC1 / 32
    SYSCTL_WD_PREDIV_64   = 0xD00U,  //!< PREDIVCLK = INTOSC1 / 64
    SYSCTL_WD_PREDIV_128  = 0xE00U,  //!< PREDIVCLK = INTOSC1 / 128
    SYSCTL_WD_PREDIV_256  = 0xF00U,  //!< PREDIVCLK = INTOSC1 / 256
    SYSCTL_WD_PREDIV_512  = 0x000U,  //!< PREDIVCLK = INTOSC1 / 512
    SYSCTL_WD_PREDIV_1024 = 0x100U,  //!< PREDIVCLK = INTOSC1 / 1024
    SYSCTL_WD_PREDIV_2048 = 0x200U,  //!< PREDIVCLK = INTOSC1 / 2048
    SYSCTL_WD_PREDIV_4096 = 0x300U   //!< PREDIVCLK = INTOSC1 / 4096
} SysCtl_WDPredivider;

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setWatchdogPrescaler() as the \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    SYSCTL_WD_PRESCALE_1  = 1U,      //!< WDCLK = PREDIVCLK / 1
    SYSCTL_WD_PRESCALE_2  = 2U,      //!< WDCLK = PREDIVCLK / 2
    SYSCTL_WD_PRESCALE_4  = 3U,      //!< WDCLK = PREDIVCLK / 4
    SYSCTL_WD_PRESCALE_8  = 4U,      //!< WDCLK = PREDIVCLK / 8
    SYSCTL_WD_PRESCALE_16 = 5U,      //!< WDCLK = PREDIVCLK / 16
    SYSCTL_WD_PRESCALE_32 = 6U,      //!< WDCLK = PREDIVCLK / 32
    SYSCTL_WD_PRESCALE_64 = 7U       //!< WDCLK = PREDIVCLK / 64
} SysCtl_WDPrescaler;


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Gets the reason for a reset.
//!
//! This function will return the reason(s) for a reset.  Since the reset
//! reasons are sticky until either cleared by software or an external reset,
//! multiple reset reasons may be returned if multiple resets have occurred.
//! The reset reason will be a logical OR of
//! - \b SYSCTL_CAUSE_PORESETN - Power-on reset
//! - \b SYSCTL_CAUSE_XRSN - External reset pin
//! - \b SYSCTL_CAUSE_CPU1WDRSN - Watchdog reset from CPU1
//! - \b SYSCTL_CAUSE_CPU1NMIWDRSN -NMI Watchdog reset from CPU1
//! - \b SYSCTL_CAUSE_CPU1SYSRSN   - System reset from CPU1
//! - \b SYSCTL_CAUSE_CPU1SCCRESETN - SCCRESETn from CPU1
//! - \b SYSCTL_CAUSE_ECAT_RESET_OUT  - ECAT reset
//! - \b SYSCTL_CAUSE_CPU1SIMRESET_CPURSN - SIMRESET from CPU1
//! - \b SYSCTL_CAUSE_CMRSTCTLRESETREQ - System reset request from CM4
//! - \b SYSCTL_CAUSE_CMVECTRESETN - Vectreset from CM4
//! - \b SYSCTL_CAUSE_CMSYSRESETREQ - System reset request from CPU1
//! - \b SYSCTL_CAUSE_CMNMIWDRSTN - NMI watchdog reset from CM4
//! - \b SYSCTL_CAUSE_CMEOLRESETN - EOLRESETn reset from CM4
//!
//! \return Returns the reason(s) for a reset.
//
//*****************************************************************************
static inline uint32_t
SysCtl_getResetCause(void)
{
    //
    // Return the reset reasons.
    //
 return(HWREG(CMSYSCTL_BASE + SYSCTL_O_CMRESC) &
       ((uint32_t)SYSCTL_CMRESC_PORESETN | (uint32_t)SYSCTL_CMRESC_XRSN |
       (uint32_t)SYSCTL_CMRESC_CPU1_WDRSN |
       (uint32_t)SYSCTL_CMRESC_CPU1_SYSRSN |
       (uint32_t)SYSCTL_CMRESC_CMNMIWDRSTN |
       (uint32_t)SYSCTL_CMRESC_CMEOLRESETN |
       (uint32_t)SYSCTL_CMRESC_CPU1_NMIWDRSN |
       (uint32_t)SYSCTL_CMRESC_CPU1_SCCRESETN |
       (uint32_t)SYSCTL_CMRESC_ECAT_RESET_OUT |
       (uint32_t)SYSCTL_CMRESC_CMRSTCTL_RESETREQ |
       (uint32_t)SYSCTL_CMRESC_CPU1_SIMRESET_CPURSN |
       (uint32_t)SYSCTL_CMRESC_CMSYSRESETREQ |
       (uint32_t)SYSCTL_CMRESC_CMVECTRESETN));
}

//*****************************************************************************
//
//! Clears reset reasons.
//!
//! \param rstCauses are the reset causes to be cleared; must be a logical
//! OR of \b SYSCTL_CAUSE_PORESETN, \b SYSCTL_CAUSE_XRSN,
//! \b SYSCTL_CAUSE_CPU1WDRSN,\b SYSCTL_CAUSE_CPU1NMIWDRSN,
//! \b SYSCTL_CAUSE_CPU1SYSRSN ,\b SYSCTL_CAUSE_CPU1SCCRESETN,
//! \b SYSCTL_CAUSE_ECAT_RESET_OUT , \b SYSCTL_CAUSE_CPU1SIMRESET_CPURSN,
//! \b SYSCTL_CAUSE_CMRSTCTLRESETREQ  ,\b SYSCTL_CAUSE_CMVECTRESETN,
//! \b SYSCTL_CAUSE_CMSYSRESETREQ,
//! \b SYSCTL_CAUSE_CMNMIWDRSN and/or \b SYSCTL_CAUSE_CMEOLRESETN.
//!
//! This function clears the specified sticky reset reasons.  Once cleared,
//! another reset for the same reason can be detected, and a reset for a
//! different reason can be distinguished (instead of having two reset causes
//! set).  If the reset reason is used by an application, all reset causes
//! should be cleared after they are retrieved with SysCtl_getResetCause().
//!
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
    HWREG(CMSYSCTL_BASE + SYSCTL_O_CMRESCCLR) = rstCauses;
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
    //
    // Set the disable bit.
    //
    HWREGH(WD_BASE + WWD_O_WDCR) |= SYSCTL_WD_CHKBITS | WWD_WDCR_WDDIS;

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

    //
    // Clear the disable bit.
    //
    HWREGH(WD_BASE + WWD_O_WDCR) = (HWREGH(WD_BASE + WWD_O_WDCR) &
                                    ~WWD_WDCR_WDDIS) | SYSCTL_WD_CHKBITS;

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

    //
    // Enable the counter to be reset and then reset it.
    //
    HWREGH(WD_BASE + WWD_O_WDKEY) = SYSCTL_WD_ENRSTKEY;
    HWREGH(WD_BASE + WWD_O_WDKEY) = SYSCTL_WD_RSTKEY;

}


//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) pre-divider.
//!
//! \param predivider is the value that configures the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) pre-divider. There are two
//! dividers that scale INTOSC1 to WDCLK. The \e predivider parameter divides
//! INTOSC1 down to PREDIVCLK and the prescaler (set by the
//! SysCtl_setWatchdogPrescaler() function) divides PREDIVCLK down to WDCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_setWatchdogPredivider(SysCtl_WDPredivider predivider)
{
    uint16_t regVal;

    regVal = (uint16_t)predivider | (uint16_t)SYSCTL_WD_CHKBITS;

    //
    // Write the predivider to the appropriate register.
    //
    HWREGH(WD_BASE + WWD_O_WDCR) = (HWREGH(WD_BASE + WWD_O_WDCR) &
                                    ~(WWD_WDCR_WDPRECLKDIV_M)) | regVal;

}

//*****************************************************************************
//
//! Sets up watchdog clock (WDCLK) prescaler.
//!
//! \param prescaler is the value that configures the watchdog clock relative
//! to the value from the pre-divider.
//!
//! This function sets up the watchdog clock (WDCLK) prescaler. There are two
//! dividers that scale INTOSC1 to WDCLK. The predivider (set with the
//! SysCtl_setWatchdogPredivider() function) divides INTOSC1 down to PREDIVCLK
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

    //
    // Write the prescaler to the appropriate register.
    //
    HWREGH(WD_BASE + WWD_O_WDCR) = (HWREGH(WD_BASE + WWD_O_WDCR) &
                                    ~(WWD_WDCR_WDPS_M)) | regVal;

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
    return(HWREGH(WD_BASE + WWD_O_WDCNTR));
}

//*****************************************************************************
//
//! Gets the watchdog status.
//!
//!This function returns the watchdog status.
//!This bit, if set, indicates a NMI was fired to CM4 from WWD.
//!This bit remains latched until the user writes a 1 to clear the condition.
//!Writes of 0 will be ignored.
//!
//! \return Returns \b true if the watchdog generated the NMI condition.
//
//*****************************************************************************
static inline bool
SysCtl_getWatchdogStatus(void)
{
    //
    // Read and return the status of the watchdog status flag.
    //
    return((HWREGH(WD_BASE + WWD_O_WDCR) & WWD_WDCR_WDFLG) != 0U);
}

//*****************************************************************************
//
//! Clears the watchdog status.
//!
//! This function clears the watchdog status. To check if it was set
//! first, see SysCtl_getWatchdogStatus().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearWatchdogStatus(void)
{
    //
    // Clears the status of the watchdog reset flag.
    //
    HWREGH(WD_BASE + WWD_O_WDCR) |= SYSCTL_WD_CHKBITS | WWD_WDCR_WDFLG;
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
    uint16_t clearvalue,    wvalue;
    uint32_t readval;

    wvalue = value;

    //
    //Write will succeed only if a matching key value is written
    //to the KEY field
    // Clear the windowed value
    //
    readval = HWREGH(WD_BASE + WWD_O_WDWCR);
    clearvalue = (uint16_t)readval;
    clearvalue &= ~((uint16_t)WWD_WDWCR_MIN_M);
    HWREG(WD_BASE + WWD_O_WDWCR) = (((uint32_t)SYSCTL_WWD_KEY << 16U) &
                                    WWD_WDWCR_KEY_M) | clearvalue;
    //
    // Set the windowed value
    //
    wvalue &= (uint16_t)WWD_WDWCR_MIN_M;
    HWREG(WD_BASE + WWD_O_WDWCR) |= ((((uint32_t)SYSCTL_WWD_KEY << 16U) &
                                     WWD_WDWCR_KEY_M) | wvalue);
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
    return((HWREGH(NMI_BASE + NMI_O_CMNMIFLG) & NMI_CMNMIFLG_NMIINT) != 0U);
}

//*****************************************************************************
//
//! Read NMI Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of NMIFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL - Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR - RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIFlagStatus(void)
{
    //
    // Read and return the current value of the NMI flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_CMNMIFLG));
}

//*****************************************************************************
//
//! Check if the individual NMI interrupts are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL - Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR -RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
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
SysCtl_isNMIFlagSet(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_MEMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_MCANUNCERR | SYSCTL_NMI_ECATNMI |
                         SYSCTL_NMI_WWDNMI)) == 0U);

    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_CMNMIFLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Function to clear individual NMI interrupts.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the CMNMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL -Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR - RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
//!
//! Clear NMI interrupt flags that correspond with the passed in bit mask.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearNMIStatus(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_MEMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_MCANUNCERR | SYSCTL_NMI_ECATNMI |
                         SYSCTL_NMI_WWDNMI)) == 0U);

    //
    // Clear the individual flags
    //
    HWREG(NMI_BASE + NMI_O_CMNMIFLGCLR) = nmiFlags |
                                          (((uint32_t)SYSCTL_CMNMIFLGCLR_KEY
                                            << 16U) & NMI_CMNMIFLGCLR_KEY_M);

}

//*****************************************************************************
//
//! Clear all the NMI Flags.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_clearAllNMIFlags(void)
{
    uint32_t nmiFlags;

    //
    // Directly write to the clear register,
    // clearing all the flags.
    //

  nmiFlags = ((uint32_t)SYSCTL_NMI_NMIINT | (uint32_t)SYSCTL_NMI_CLOCKFAIL |
             (uint32_t)SYSCTL_NMI_MEMUNCERR | (uint32_t)SYSCTL_NMI_FLUNCERR |
             (uint32_t)SYSCTL_NMI_MCANUNCERR | (uint32_t)SYSCTL_NMI_ECATNMI |
             (uint32_t)SYSCTL_NMI_WWDNMI);

  HWREG(NMI_BASE + NMI_O_CMNMIFLGCLR) = nmiFlags |
                                        (((uint32_t)SYSCTL_CMNMIFLGCLR_KEY
                                          << 16U) & NMI_CMNMIFLGCLR_KEY_M);

}

//*****************************************************************************
//
//! Function to force individual NMI interrupt fail flags
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants to clear.
//! The bit format of this parameter is same as of the NMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL - Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR - RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_forceNMIFlags(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_MEMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_MCANUNCERR | SYSCTL_NMI_ECATNMI |
                         SYSCTL_NMI_WWDNMI)) == 0U);

    //
    // Write to any of the fields will succeed only if right key appears on the
    // KEY field.
    // Set the Flags for the individual interrupts in the NMI flag
    // force register
    //
    HWREG(NMI_BASE + NMI_O_CMNMIFLGFRC) |= (nmiFlags |
                                           (((uint32_t)SYSCTL_CMNMIFLGFRC_KEY
                                            << 16U) & NMI_CMNMIFLGFRC_KEY_M));

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
    return(HWREGH(NMI_BASE + NMI_O_CMNMIWDCNT));
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

    //
    // Write to the period register.
    //
    HWREG(NMI_BASE + NMI_O_CMNMIWDPRD) = (((uint32_t)SYSCTL_CMNMIWDPRD_KEY
                                           << 16U) & NMI_CMNMIWDPRD_KEY_M)
                                          | wdPeriod ;
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
    return(HWREGH(NMI_BASE + NMI_O_CMNMIWDPRD));
}

//*****************************************************************************
//
//! Read NMI Shadow Flags.
//!
//! Read the current state of individual NMI interrupts
//!
//! \return Value of CMNMISHDFLG register. These defines are provided to decode
//! the value:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL - Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR - RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
//
//*****************************************************************************
static inline uint16_t
SysCtl_getNMIShadowFlagStatus(void)
{
    //
    // Read and return the current value of the NMI shadow flag register.
    //
    return(HWREGH(NMI_BASE + NMI_O_CMNMISHDWFLG));
}

//*****************************************************************************
//
//! Check if the individual NMI shadow flags are set.
//!
//! \param nmiFlags Bit mask of the NMI interrupts that user wants  to clear.
//! The bit format of this parameter is same as of the CMNMIFLG register. These
//! defines are provided:
//! - \b SYSCTL_NMI_NMIINT - Non-maskable interrupt
//! - \b SYSCTL_NMI_CLOCKFAIL - Clock Failure
//! - \b SYSCTL_NMI_MEMUNCERR - RAM, ROM Uncorrectable Error
//! - \b SYSCTL_NMI_FLUNCERR - Uncorrectable Flash error
//! - \b SYSCTL_NMI_MCANUNCERR -MCAN Uncorrectable Error
//! - \b SYSCTL_NMI_WWDNMI- CM WWD
//! - \b SYSCTL_NMI_ECATNMI -EtherCAT reset out
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
SysCtl_isNMIShadowFlagSet(uint32_t nmiFlags)
{
    //
    // Check the arguments.
    // Make sure if reserved bits are not set in nmiFlags.
    //
    ASSERT((nmiFlags & ~(SYSCTL_NMI_NMIINT | SYSCTL_NMI_CLOCKFAIL |
                         SYSCTL_NMI_MEMUNCERR | SYSCTL_NMI_FLUNCERR |
                         SYSCTL_NMI_MCANUNCERR | SYSCTL_NMI_ECATNMI |
                         SYSCTL_NMI_WWDNMI)) == 0U);


    //
    // Read the flag register and return true if any of them are set.
    //
    return((HWREGH(NMI_BASE + NMI_O_CMNMISHDWFLG) & nmiFlags) != 0U);
}

//*****************************************************************************
//
//! Blocks  writes to the CM System control registers
//!
//! \param controlreg is the Control Register whose access is blocked.
//! SYSCTL_CMECATCTL_LOCK is for the CMECATCTL register
//!
//! This function locks the configuration registers of CM System Control
//! register.
//!
//!\b Note: Today only writes to the CMECATCTL register are blocked .
//!\b Writes to CMECATCTL register is unblocked on reset .
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_lockAccessControlRegs(uint16_t controlreg)
{
    HWREGH(CMSYSCTL_BASE + SYSCTL_O_CMSYSCTLLOCK) = controlreg;
}

//*****************************************************************************
//! Puts the processor into sleep mode.
//!
//! This function places the processor into sleep mode
//!
//! \return None.
//*****************************************************************************
static inline void
SysCtl_sleep(void)
{
    //
    // Wait for an interrupt.
    //
    CPU_wfi();
}

//*****************************************************************************
//
//! Enable the Global NMI
//!
//! This function writes to the NMI configuration register that enables the
//! global NMI.
//!
//! \note Global NMI is disabled on reset
//!
//! \return None.
//
//*****************************************************************************
static inline void
SysCtl_enableGlobalNMI(void)
{

  //
  // Write to the NMI config register to enable global NMI.
  //
  HWREG(NMI_BASE + NMI_O_CMNMICFG) = (((uint32_t)SYSCTL_CMNMICFG_KEY << 16U) &
                                      NMI_CMNMICFG_KEY_M) | SYSCTL_NMI_GLOBAL;
}

//*****************************************************************************
//
//!  Check if the Watchdog First Valid Key Detect Flag is set or not.
//!
//! \return \b true if the First Valid key after non-zero MIN configuration
//!  got detected \b false if the First Valid Key after non-zero MIN
//!  configuration has not happened
//
//*****************************************************************************

static inline bool
SysCtl_isWatchdogFirstKeyDetectFlagset(void)
{
    //
    // Read the First Valid Key Detect and return true if set.
    //
    return((HWREGH(WD_BASE + WWD_O_WDWCR) & WWD_WDWCR_FIRSTKEY) != 0U);
}

//*****************************************************************************
//
//!  Check if the MCAN wakeup event has occured.
//!
//! \return \b true if the MCAN wakeup event has occured.
//!  \b false if the MCAN wakeup event has not occured.
//
//*****************************************************************************

static inline bool
SysCtl_isMCANWakeStatusSet(void)
{
    //
    // Read the MCAN wakeup event status and return true if set.
    //
    return((HWREGH(CMSYSCTL_BASE + SYSCTL_O_MCANWAKESTATUS) &
            SYSCTL_MCANWAKESTATUS_WAKE) != 0U);
}

//*****************************************************************************
//
//! Clears the MCAN wakeup event status.
//!
//! This function clears the MCAN wakeup event status. To check if it was set
//! first, see SysCtl_isMCANWakeStatusSet().
//!
//! \return None.
//
//*****************************************************************************

static inline void
SysCtl_clearMCANWakeStatus(void)
{
    //
    // Clear the MCAN wakeup event status
    //
    HWREGH(CMSYSCTL_BASE +
           SYSCTL_O_MCANWAKESTATUSCLR) |= SYSCTL_MCANWAKESTATUSCLR_WAKE ;

}

//*****************************************************************************
//
//! Delays for a fixed number of cycles.
//!
//! \param count is the number of delay loop iterations to perform.
//!
//! This function generates a constant length delay using assembly code. The
//! loop takes around 6 cycles per iteration plus 9 cycles of overhead.
//!
//! It is important to note that this function is a fairly accurate
//! timing mechanism.  Although the delay loop is deterministic,
//! the execution time of the loop will vary dramatically depending upon the
//! application's interrupt environment (the loop will be interrupted unless
//! run with interrupts disabled and this is generally an unwise thing to do)
//! and also the current system clock rate and flash timings (wait states and
//! the operation of the prefetch buffer affect the timing).
//!
//! For best accuracy, a system timer should be used with code either polling
//! for a particular timer value being exceeded or processing the timer
//! interrupt to determine when a particular time period has elapsed.
//!
//!
//! \return None.
//
//*****************************************************************************

extern void
SysCtl_delay(uint32_t count);

//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param peripheral is the peripheral to reset.
//!
//! This function uses the SOFTPRESx registers to reset a specified peripheral.
//! Module registers will be returned to their reset states.
//!
//! \note This includes registers containing trim values.
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_resetPeripheral(SysCtl_PeripheralSOFTPRES peripheral);


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
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral);

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
extern void
SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral);

//*****************************************************************************
//
//!  Request to stop the clock to a Peripheral.
//!
//! \param peripheral is the peripheral to which the Stop clock request
//! is sent.
//! \param enable is the value to be written to the Clk stop request register.
//!  This can take values of either 1U(enable) or 0U(disable).
//!
//! Once set, this bit is cleared either explicitly by passing a 0U to the API
//! or when clock to peripheral is turned on as a result of a wakeup event in
//! hardware
//!
//! \return None.
//
//*****************************************************************************
extern void
SysCtl_requestPeripheralClockStop(SysCtl_PeripheralCMCLKSTOPREQ peripheral,
                                  uint16_t enable);

//*****************************************************************************
//
//!  Check if request to stop the clock to a Peripheral is Acked or Not.
//!
//! \param peripheral is the peripheral which acked the Stop clock Req or not .
//!
//! \return \b true if the peripheral acked the Stop clock Request
//! \b false if peripheral did not ack the Stop clock Request
//
//*****************************************************************************
extern bool
SysCtl_isPeripheralClockStopAcked(SysCtl_PeripheralCMCLKSTOPACK peripheral);

//*****************************************************************************
//
//!  Gets the value of the Peripheral clock Stop register.
//!
//! \param peripheral is the peripheral to which the Stop clock request
//! is sent.
//!
//! \return Value of CMCLKSTOPREQ register.
//
//*****************************************************************************
extern uint16_t
SysCtl_getPeripheralClockStop(SysCtl_PeripheralCMCLKSTOPREQ peripheral);

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

#endif // __SYSCTL_H__
