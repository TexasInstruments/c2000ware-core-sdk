//###########################################################################
//
// FILE:   cmpss.h
//
// TITLE:  C28x CMPSS driver.
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

#ifndef CMPSS_H
#define CMPSS_H

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
//! \addtogroup cmpss_api CMPSS
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_cmpss.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define CMPSS_HICMP_CTL_M   (CMPSS_COMPCTL_COMPHSOURCE |                       \
                             CMPSS_COMPCTL_COMPHINV |                          \
                             CMPSS_COMPCTL_ASYNCHEN)

#define CMPSS_LOCMP_CTL_M   (CMPSS_COMPCTL_COMPLSOURCE |                       \
                             CMPSS_COMPCTL_COMPLINV |                          \
                             CMPSS_COMPCTL_ASYNCLEN)

#ifndef DOXYGEN_PDF_IGNORE

//*****************************************************************************
//
// Defines for the bit fields in the COMPDACHCTL2 and COMPDACLCTL2 register
//
//*****************************************************************************
#define CMPSS_BLANKSOURCEUSEL_S    8U
#define CMPSS_RAMPSOURCEUSEL_S     10U

//*****************************************************************************
//
// Values that can be passed to CMPSS_configLowComparator() and
// CMPSS_configHighComparator() as the config parameter.
//
//*****************************************************************************
//
// Comparator negative input source
//
//! Input driven by internal DAC
#define CMPSS_INSRC_DAC                 0x0000U
//! Input driven by external pin
#define CMPSS_INSRC_PIN                 0x0001U

//
// Extra options
//
//! Comparator output is inverted
#define CMPSS_INV_INVERTED              0x0002U
//! Asynch comparator output feeds into OR with latched digital filter output
#define CMPSS_OR_ASYNC_OUT_W_FILT       0x0040U

//*****************************************************************************
//
// Values that can be passed to CMPSS_configOutputsLow() and
// CMPSS_configOutputsHigh() as the config parameter.
//
//*****************************************************************************
//
// Signal driving CTRIPOUT
//
//! Asynchronous comparator output drives CTRIPOUT
#define CMPSS_TRIPOUT_ASYNC_COMP        0x0000U
//! Synchronous comparator output drives CTRIPOUT
#define CMPSS_TRIPOUT_SYNC_COMP         0x0010U
//! Filter output drives CTRIPOUT
#define CMPSS_TRIPOUT_FILTER            0x0020U
//! Latched filter output drives CTRIPOUT
#define CMPSS_TRIPOUT_LATCH             0x0030U

//
// Signal driving CTRIP
//
//! Asynchronous comparator output drives CTRIP
#define CMPSS_TRIP_ASYNC_COMP           0x0000U
//! Synchronous comparator output drives CTRIP
#define CMPSS_TRIP_SYNC_COMP            0x0004U
//! Filter output drives CTRIP
#define CMPSS_TRIP_FILTER               0x0008U
//! Latched filter output drives CTRIP
#define CMPSS_TRIP_LATCH                0x000CU

//*****************************************************************************
//
// Values that can be returned by CMPSS_getStatus().
//
//*****************************************************************************
//! High digital filter output
#define CMPSS_STS_HI_FILTOUT            0x0001U
//! Latched value of high digital filter output
#define CMPSS_STS_HI_LATCHFILTOUT       0x0002U
//! Low digital filter output
#define CMPSS_STS_LO_FILTOUT            0x0100U
//! Latched value of low digital filter output
#define CMPSS_STS_LO_LATCHFILTOUT       0x0200U

//*****************************************************************************
//
// Values that can be passed to CMPSS_configDAC() the config parameter.
//
//*****************************************************************************
//
// When is DAC value loaded from shadow register
//
//! DAC value updated from SYSCLK
#define CMPSS_DACVAL_SYSCLK             0x0000U
//! DAC value updated from PWMSYNC
#define CMPSS_DACVAL_PWMSYNC            0x0080U

//
// DAC reference voltage
//
//! VDDA is the voltage reference
#define CMPSS_DACREF_VDDA               0x0000U
//! VDAC is the voltage reference
#define CMPSS_DACREF_VDAC               0x0020U

//
// DAC value source
//
//! DAC value updated from shadow register
#define CMPSS_DACSRC_SHDW               0x0000U
//! DAC value is updated from the ramp register
#define CMPSS_DACSRC_RAMP               0x0001U
#endif

//*****************************************************************************
//
// Values that can be passed to CMPSS_configRamp()
// CMPSS_configRampHigh() and CMPSS_configRampLow()
// as the pwmSyncSrc parameter.
//
//*****************************************************************************
#define CMPSS_PWMSYNC17  17U //!< PWMSYNC17
#define CMPSS_PWMSYNC18  18U //!< PWMSYNC18
#define CMPSS_PWMSYNC1  1U //!< PWMSYNC1
#define CMPSS_PWMSYNC2  2U //!< PWMSYNC2
#define CMPSS_PWMSYNC3  3U //!< PWMSYNC3
#define CMPSS_PWMSYNC4  4U //!< PWMSYNC4
#define CMPSS_PWMSYNC5  5U //!< PWMSYNC5
#define CMPSS_PWMSYNC6  6U //!< PWMSYNC6
#define CMPSS_PWMSYNC7  7U //!< PWMSYNC7
#define CMPSS_PWMSYNC8  8U //!< PWMSYNC8
#define CMPSS_PWMSYNC9  9U //!< PWMSYNC9
#define CMPSS_PWMSYNC10  10U //!< PWMSYNC10
#define CMPSS_PWMSYNC11  11U //!< PWMSYNC11
#define CMPSS_PWMSYNC12  12U //!< PWMSYNC12
#define CMPSS_PWMSYNC13  13U //!< PWMSYNC13
#define CMPSS_PWMSYNC14  14U //!< PWMSYNC14
#define CMPSS_PWMSYNC15  15U //!< PWMSYNC15
#define CMPSS_PWMSYNC16  16U //!< PWMSYNC16

//*****************************************************************************
//
// Values that can be passed to CMPSS_configureFilterInputHigh() and
// CMPSS_configureFilterInputLow() as the filtInput parameter.
//
//*****************************************************************************
//
// Comparator digital filter input selection
//
typedef enum
{
    CMPSS_FILTIN_COMPOUT = 0x0000,  //!< Filter input driven by comp output
    CMPSS_FILTIN_EXT_H1  = 0x0001,  //!< Filter input driven by EXT_FILTIN_H[1]
    CMPSS_FILTIN_EXT_H2  = 0x0002,  //!< Filter input driven by EXT_FILTIN_H[2]
    CMPSS_FILTIN_EXT_H3  = 0x0003,  //!< Filter input driven by EXT_FILTIN_H[3]
    CMPSS_FILTIN_EXT_H4  = 0x0004,  //!< Filter input driven by EXT_FILTIN_H[4]
    CMPSS_FILTIN_EXT_H5  = 0x0005,  //!< Filter input driven by EXT_FILTIN_H[5]
    CMPSS_FILTIN_EXT_H6  = 0x0006,  //!< Filter input driven by EXT_FILTIN_H[6]
    CMPSS_FILTIN_EXT_H7  = 0x0007,  //!< Filter input driven by EXT_FILTIN_H[7]

} CMPSS_FilterInput;

//*****************************************************************************
//
// Values that can be passed to CMPSS_setRampDirectionHigh() as the dir
// parameter.
//
//*****************************************************************************
typedef enum
{
    CMPSS_RAMP_DIR_DOWN = 0x0000,                    //!< Decrementing Ramp
    CMPSS_RAMP_DIR_UP   = CMPSS_COMPDACHCTL_RAMPDIR, //!< Incrementing Ramp
} CMPSS_RampDirection;

//*****************************************************************************
//
//! Values that can be passed to CMPSS_configureRampXTriggerHigh() as the
//! \e trigger parameter.
//
//*****************************************************************************
typedef enum
{
    CMPSS_RAMP_XTRIGGER_DISABLE   = 0x0000,//!< RAMPH & RAMPL SOR trigger is
                                           //!< the independently configured
                                           //!< PWMSYNCx signal
    CMPSS_RAMP_XTRIGGER_RAMPH_EOR = 0x0001,//!< RAMPH SOR trigger is the
                                           //!< configured PWMSYNCx signal &
                                           //!< RAMPL SOR trigger is RAMPH EOR
    CMPSS_RAMP_XTRIGGER_RAMPL_EOR = 0x0002 //!< RAMPL SOR trigger is the
                                           //!< configured PWMSYNCx signal and
                                           //!< RAMPH SOR trigger is RAMPL EOR
} CMPSS_RampXTrigger;


//*****************************************************************************
//
//! Values that can be passed to CMPSS_selectDEACTIVESource() API
//! as the \e deactivesel parameter.
//
//*****************************************************************************
typedef enum
{
    CMPSS_DEACTIVE_EPWM1   = 0x00U,  //!< EPWM1 DEACTIVE
    CMPSS_DEACTIVE_EPWM2   = 0x01U,  //!< EPWM2 DEACTIVE
    CMPSS_DEACTIVE_EPWM3   = 0x02U,  //!< EPWM3 DEACTIVE
    CMPSS_DEACTIVE_EPWM4   = 0x03U,  //!< EPWM4 DEACTIVE
    CMPSS_DEACTIVE_EPWM5   = 0x04U,  //!< EPWM5 DEACTIVE
    CMPSS_DEACTIVE_EPWM6   = 0x05U,  //!< EPWM6 DEACTIVE
    CMPSS_DEACTIVE_EPWM7   = 0x06U,  //!< EPWM7 DEACTIVE
    CMPSS_DEACTIVE_EPWM8   = 0x07U,  //!< EPWM8 DEACTIVE
    CMPSS_DEACTIVE_EPWM9   = 0x08U,  //!< EPWM9 DEACTIVE
    CMPSS_DEACTIVE_EPWM10  = 0x09U,  //!< EPWM10 DEACTIVE
    CMPSS_DEACTIVE_EPWM11  = 0x0AU,  //!< EPWM11 DEACTIVE
    CMPSS_DEACTIVE_EPWM12  = 0x0BU,  //!< EPWM12 DEACTIVE
    CMPSS_DEACTIVE_EPWM13  = 0x0CU,  //!< EPWM13 DEACTIVE
    CMPSS_DEACTIVE_EPWM14  = 0x0DU,  //!< EPWM14 DEACTIVE
    CMPSS_DEACTIVE_EPWM15  = 0x0EU,  //!< EPWM15 DEACTIVE
    CMPSS_DEACTIVE_EPWM16  = 0x0FU,  //!< EPWM16 DEACTIVE
    CMPSS_DEACTIVE_EPWM17  = 0x10U,  //!< EPWM17 DEACTIVE
    CMPSS_DEACTIVE_EPWM18  = 0x11U,  //!< EPWM18 DEACTIVE
} CMPSS_DEActiveSelect;

//*****************************************************************************
//
// Values that can be passed to CMPSS_setRampClockDividerHigh() and
// CMPSS_setRampClockDividerLow() APIs as the divider parameter.
//
//*****************************************************************************
typedef enum
{
    CMPSS_RAMP_CLOCK_DIV1   = 0x0U,  //!< RAMPCLK = SYSCLK/1
    CMPSS_RAMP_CLOCK_DIV2   = 0x1U,  //!< RAMPCLK = SYSCLK/2
    CMPSS_RAMP_CLOCK_DIV3   = 0x2U,  //!< RAMPCLK = SYSCLK/3
    CMPSS_RAMP_CLOCK_DIV4   = 0x3U,  //!< RAMPCLK = SYSCLK/4
    CMPSS_RAMP_CLOCK_DIV5   = 0x4U,  //!< RAMPCLK = SYSCLK/5
    CMPSS_RAMP_CLOCK_DIV6   = 0x5U,  //!< RAMPCLK = SYSCLK/6
    CMPSS_RAMP_CLOCK_DIV7   = 0x6U,  //!< RAMPCLK = SYSCLK/7
    CMPSS_RAMP_CLOCK_DIV8   = 0x7U,  //!< RAMPCLK = SYSCLK/8
    CMPSS_RAMP_CLOCK_DIV9   = 0x8U,  //!< RAMPCLK = SYSCLK/9
    CMPSS_RAMP_CLOCK_DIV10  = 0x9U,  //!< RAMPCLK = SYSCLK/10
    CMPSS_RAMP_CLOCK_DIV11  = 0xAU,  //!< RAMPCLK = SYSCLK/11
    CMPSS_RAMP_CLOCK_DIV12  = 0xBU,  //!< RAMPCLK = SYSCLK/12
    CMPSS_RAMP_CLOCK_DIV13  = 0xCU,  //!< RAMPCLK = SYSCLK/13
    CMPSS_RAMP_CLOCK_DIV14  = 0xDU,  //!< RAMPCLK = SYSCLK/14
    CMPSS_RAMP_CLOCK_DIV15  = 0xEU,  //!< RAMPCLK = SYSCLK/15
    CMPSS_RAMP_CLOCK_DIV16  = 0xFU,  //!< RAMPCLK = SYSCLK/16
} CMPSS_RampClockDiv;

//*****************************************************************************
//
// Values that can be passed to CMPSS_selectBlankSourceGroupHigh(),
// CMPSS_selectBlankSourceGroupLow(), CMPSS_selectRampSourceGroupHigh() and
// CMPSS_selectRampSourceGroupLow() APIs as the group parameter.
//
//*****************************************************************************
typedef enum
{
    CMPSS_EPWM_GROUP_0TO15   = 0x0U,  //!< Select EPWM0-EPWM15 group
    CMPSS_EPWM_GROUP_16TO31  = 0x1U,  //!< Select EPWM16-EPWM31 group
} CMPSS_EPWMGroup;


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks the CMPSS base address.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function determines if a CMPSS base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CMPSS_isBaseValid(uint32_t base)
{
    return(
           (base == CMPSS1_BASE) ||
           (base == CMPSS2_BASE) ||
           (base == CMPSS3_BASE) ||
           (base == CMPSS4_BASE) ||
           (base == CMPSS5_BASE) ||
           (base == CMPSS6_BASE) ||
           (base == CMPSS7_BASE) ||
           (base == CMPSS8_BASE) ||
           (base == CMPSS9_BASE) ||
           (base == CMPSS10_BASE) ||
           (base == CMPSS11_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enables the CMPSS module.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function enables the CMPSS module passed into the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the CMPSS module.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) |= CMPSS_COMPCTL_COMPDACE;

    EDIS;
}

//*****************************************************************************
//
//! Disables the CMPSS module.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function disables the CMPSS module passed into the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the CMPSS module.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) &= ~CMPSS_COMPCTL_COMPDACE;

    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the high comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the high comparator.
//!
//! This function configures a comparator.  The \e config parameter is the
//! result of a logical OR operation between a \b CMPSS_INSRC_xxx value and if
//! desired, \b CMPSS_INV_INVERTED and \b CMPSS_OR_ASYNC_OUT_W_FILT values.
//!
//! The \b CMPSS_INSRC_xxx term can take on the following values to specify
//! the high comparator negative input source:
//! - \b CMPSS_INSRC_DAC - The internal DAC.
//! - \b CMPSS_INSRC_PIN - An external pin.
//!
//! \b CMPSS_INV_INVERTED may be ORed into \e config if the comparator output
//! should be inverted.
//!
//! \b CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e config if the
//! asynchronous comparator output should be fed into an OR gate with the
//! latched digital filter output before it is made available for CTRIPH or
//! CTRIPOUTH.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configHighComparator(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the high comparator configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) =
        (HWREGH(base + CMPSS_O_COMPCTL) & ~CMPSS_HICMP_CTL_M) | config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the low comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the low comparator.
//!
//! This function configures a comparator.  The \e config parameter is the
//! result of a logical OR operation between a \b CMPSS_INSRC_xxx value and if
//! desired, \b CMPSS_INV_INVERTED and \b CMPSS_OR_ASYNC_OUT_W_FILT values.
//!
//! The \b CMPSS_INSRC_xxx term can take on the following values to specify
//! the low comparator negative input source:
//! - \b CMPSS_INSRC_DAC - The internal DAC.
//! - \b CMPSS_INSRC_PIN - An external pin.
//!
//! \b CMPSS_INV_INVERTED may be ORed into \e config if the comparator output
//! should be inverted.
//!
//! \b CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e config if the
//! asynchronous comparator output should be fed into an OR gate with the
//! latched digital filter output before it is made available for CTRIPL or
//! CTRIPOUTL.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configLowComparator(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the low comparator configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) =
        (HWREGH(base + CMPSS_O_COMPCTL) & ~CMPSS_LOCMP_CTL_M) | (config << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Sets the output signal configuration for the high comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the high comparator output signals.
//!
//! This function configures a comparator's output signals CTRIP and CTRIPOUT.
//! The \e config parameter is the result of a logical OR operation between the
//! \b CMPSS_TRIPOUT_xxx and \b CMPSS_TRIP_xxx values.
//!
//! The \b CMPSS_TRIPOUT_xxx term can take on the following values to specify
//! which signal drives CTRIPOUTH:
//! - \b CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIPOUT_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
//!
//! The \b CMPSS_TRIP_xxx term can take on the following values to specify
//! which signal drives CTRIPH:
//! - \b CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIP_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIP_LATCH - The latched output of the digital filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configOutputsHigh(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the high comparator output settings to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) = (HWREGH(base + CMPSS_O_COMPCTL) &
                                      ~(CMPSS_COMPCTL_CTRIPOUTHSEL_M |
                                        CMPSS_COMPCTL_CTRIPHSEL_M))  |
                                     config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the output signal configuration for the low comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the low comparator output signals.
//!
//! This function configures a comparator's output signals CTRIP and CTRIPOUT.
//! The \e config parameter is the result of a logical OR operation between the
//! \b CMPSS_TRIPOUT_xxx and \b CMPSS_TRIP_xxx values.
//!
//! The \b CMPSS_TRIPOUT_xxx term can take on the following values to specify
//! which signal drives CTRIPOUTL:
//! - \b CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIPOUT_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
//!
//! The \b CMPSS_TRIP_xxx term can take on the following values to specify
//! which signal drives CTRIPL:
//! - \b CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIP_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIP_LATCH - The latched output of the digital filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configOutputsLow(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the low comparator output settings to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) = (HWREGH(base + CMPSS_O_COMPCTL) &
                                      ~(CMPSS_COMPCTL_CTRIPOUTLSEL_M |
                                        CMPSS_COMPCTL_CTRIPLSEL_M)) |
                                     (config << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Gets the current comparator status.
//!
//! \param base is the base address of the comparator module.
//!
//! This function returns the current status for the comparator, specifically
//! the digital filter output and latched digital filter output.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! the following values:
//! - \b CMPSS_STS_HI_FILTOUT - High digital filter output
//! - \b CMPSS_STS_HI_LATCHFILTOUT - Latched value of high digital filter
//!   output
//! - \b CMPSS_STS_LO_FILTOUT - Low digital filter output
//! - \b CMPSS_STS_LO_LATCHFILTOUT - Latched value of low digital filter output
//
//*****************************************************************************
static inline uint16_t
CMPSS_getStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Return contents of the status register.
    //
    return(HWREGH(base + CMPSS_O_COMPSTS));
}

//*****************************************************************************
//
//! Sets the configuration for the internal comparator DACs.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the internal DAC.
//!
//! This function configures the comparator's internal DAC.  The \e config
//! parameter is the result of a logical OR operation between the
//! \b CMPSS_DACVAL_xxx, \b CMPSS_DACREF_xxx, and \b CMPSS_DACSRC_xxx.
//!
//! The \b CMPSS_DACVAL_xxx term can take on the following values to specify
//! when the DAC value is loaded from its shadow register:
//! - \b CMPSS_DACVAL_SYSCLK - Value register updated on system clock.
//! - \b CMPSS_DACVAL_PWMSYNC - Value register updated on PWM sync.
//!
//! The \b CMPSS_DACREF_xxx term can take on the following values to specify
//! which voltage supply is used as reference for the DACs:
//! - \b CMPSS_DACREF_VDDA - VDDA is the voltage reference for the DAC.
//! - \b CMPSS_DACREF_VDAC - VDAC is the voltage reference for the DAC.
//!
//! The \b CMPSS_DACSRC_xxx term can take on the following values to specify
//! the DAC value source for the high comparator's internal DAC:
//! - \b CMPSS_DACSRC_SHDW - The user-programmed DACVALS register.
//! - \b CMPSS_DACSRC_RAMP - The ramp generator RAMPSTS register
//!
//! \note This API configures only the high comparator DAC and is
//! to be deprecated in future. Use APIs \e CMPSS_configDACHigh() and
//! \e CMPSS_configDACLow() to configure the high and low comparator DACs
//! respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configDAC(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACHCTL) = (HWREGH(base + CMPSS_O_COMPDACHCTL) &
                                          ~(CMPSS_COMPDACHCTL_SWLOADSEL      |
                                            CMPSS_COMPDACHCTL_SELREF         |
                                        CMPSS_COMPDACHCTL_DACSOURCE)) | config;
    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the internal DAC of high comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the internal DAC.
//!
//! This function configures the high comparator's internal DAC.  The \e config
//! parameter is the result of a logical OR operation between the
//! \b CMPSS_DACVAL_xxx, \b CMPSS_DACREF_xxx, and \b CMPSS_DACSRC_xxx.
//!
//! The \b CMPSS_DACVAL_xxx term can take on the following values to specify
//! when the DAC value is loaded from its shadow register:
//! - \b CMPSS_DACVAL_SYSCLK - Value register updated on system clock.
//! - \b CMPSS_DACVAL_PWMSYNC - Value register updated on PWM sync.
//!
//! The \b CMPSS_DACREF_xxx term can take on the following values to specify
//! which voltage supply is used as reference for the DACs:
//! - \b CMPSS_DACREF_VDDA - VDDA is the voltage reference for the DAC.
//! - \b CMPSS_DACREF_VDAC - VDAC is the voltage reference for the DAC.
//!
//!
//! The \b CMPSS_DACSRC_xxx term can take on the following values to specify
//! the DAC value source for the high comparator's internal DAC:
//! - \b CMPSS_DACSRC_SHDW - The user-programmed DACHVALS register.
//! - \b CMPSS_DACSRC_RAMP - The ramp generator RAMPHSTS register
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configDACHigh(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACHCTL) = (HWREGH(base + CMPSS_O_COMPDACHCTL) &
                                          ~(CMPSS_COMPDACHCTL_SWLOADSEL      |
                                            CMPSS_COMPDACHCTL_SELREF         |
                                        CMPSS_COMPDACHCTL_DACSOURCE)) | config;
    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the internal DAC of low comparator
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the internal DAC.
//!
//! This function configures the low comparator's internal DAC. The \e config
//! parameter can take on the following values to specify the DAC value source
//! for the low comparator's internal DAC:
//! - \b CMPSS_DACSRC_SHDW - The user-programmed DACLVALS register.
//! - \b CMPSS_DACSRC_RAMP - The ramp generator RAMPLSTS register
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configDACLow(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACLCTL) = (HWREGH(base + CMPSS_O_COMPDACLCTL) &
                                          ~(CMPSS_COMPDACLCTL_DACSOURCE))    |
                                          config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the value of the internal DAC of the high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param value is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the high
//! comparator. This function will load the value into the shadow register from
//! which the actual DAC value register will be loaded. To configure which
//! event causes this shadow load to take place, use CMPSS_configDAC().
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setDACValueHigh(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 4096U);

    //
    // Write the DAC value to the DAC value shadow register.
    //
    HWREGH(base + CMPSS_O_DACHVALS) = value;
}

//*****************************************************************************
//
//! Sets the value of the internal DAC of the low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param value is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the low
//! comparator. This function will load the value into the shadow register from
//! which the actual DAC value register will be loaded. To configure which
//! event causes this shadow load to take place, use CMPSS_configDAC().
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setDACValueLow(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 4096U);

    //
    // Write the DAC value to the DAC value shadow register.
    //
    HWREGH(base + CMPSS_O_DACLVALS) = value;
}

//*****************************************************************************
//
//! Initializes the digital filter of the high comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function initializes all the samples in the high comparator digital
//! filter to the filter input value.
//!
//! \note See CMPSS_configFilterHigh() for the proper initialization sequence
//! to avoid glitches.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_initFilterHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the high comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPHFILCTL) |= CMPSS_CTRIPHFILCTL_FILINIT;

    EDIS;
}

//*****************************************************************************
//
//! Initializes the digital filter of the low comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function initializes all the samples in the low comparator digital
//! filter to the filter input value.
//!
//! \note See CMPSS_configFilterLow() for the proper initialization sequence
//! to avoid glitches.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_initFilterLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the low comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPLFILCTL) |= CMPSS_CTRIPLFILCTL_FILINIT;

    EDIS;
}

//*****************************************************************************
//
//! Configures input for the digital filter of the high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param filtInput is the desired filter input
//!
//! This function configures input for the digital filter of the high
//! comparator. The filter input can either be high comparator output or
//! an external signal configured through XBAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configureFilterInputHigh(uint32_t base, CMPSS_FilterInput filtInput)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)filtInput <= 7U);

    //
    // Set the high comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPHFILCTL) = (HWREGH(base + CMPSS_O_CTRIPHFILCTL) &
                                           ~CMPSS_CTRIPHFILCTL_FILTINSEL_M)    |
                                          (uint16_t)filtInput ;

    EDIS;
}

//*****************************************************************************
//
//! Initializes the digital filter of the low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param filtInput is the desired filter input
//!
//! This function configures input for the digital filter of the low comparator.
//! The filter input can either be low comparator output or an external signal
//! configured through XBAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configureFilterInputLow(uint32_t base, CMPSS_FilterInput filtInput)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)filtInput <= 7U);

    //
    // Set the low comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPLFILCTL) = (HWREGH(base + CMPSS_O_CTRIPLFILCTL) &
                                           ~CMPSS_CTRIPLFILCTL_FILTINSEL_M)    |
                                          (uint16_t)filtInput;

    EDIS;
}

//*****************************************************************************
//
//! Gets the value of the internal DAC of the high comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function gets the value of the internal DAC of the high comparator.
//! The value is read from the \e active register--not the shadow register to
//! which CMPSS_setDACValueHigh() writes.
//!
//! \return Returns the value driven by the internal DAC of the high comparator.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getDACValueHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC value to the DAC value shadow register.
    //
    return(HWREGH(base + CMPSS_O_DACHVALA));
}

//*****************************************************************************
//
//! Gets the value of the internal DAC of the low comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function gets the value of the internal DAC of the low comparator.
//! The value is read from the \e active register--not the shadow register to
//! which CMPSS_setDACValueLow() writes.
//!
//! \return Returns the value driven by the internal DAC of the low comparator.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getDACValueLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC value to the DAC value shadow register.
    //
    return(HWREGH(base + CMPSS_O_DACLVALA));
}

//*****************************************************************************
//
//! Causes a software reset of the high comparator digital filter output latch.
//!
//! \param base is the base address of the comparator module.
//!
//! This function causes a software reset of the high comparator digital filter
//! output latch. It will generate a single pulse of the latch reset signal.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_clearFilterLatchHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that generates a reset pulse to the digital filter latch.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_HLATCHCLR;

    EDIS;
}

//*****************************************************************************
//
//! Causes a software reset of the low comparator digital filter output latch.
//!
//! \param base is the base address of the comparator module.
//!
//! This function causes a software reset of the low comparator digital filter
//! output latch. It will generate a single pulse of the latch reset signal.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_clearFilterLatchLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that generates a reset pulse to the digital filter latch.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_LLATCHCLR;

    EDIS;
}

//*****************************************************************************
//
//! Sets the ramp generator maximum reference value.
//!
//! \param base is the base address of the comparator module.
//! \param value the ramp maximum reference value.
//!
//! This function sets the ramp maximum reference value that will be loaded
//! into the ramp generator.
//!
//! \note This API returns the reference value for only the high ramp generator
//! and is to be deprecated in future. Use APIs \e CMPSS_getRampReferenceHigh()
//! and \e CMPSS_getRampReferenceLow() to get reference value for high and low
//! ramp generators respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setMaxRampValue(uint32_t base,  uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the maximum ramp value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHREFS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator maximum reference value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API returns the reference value for only the high ramp generator
//! and is to be deprecated in future. Use APIs \e CMPSS_getRampReferenceHigh()
//! and \e CMPSS_getRampReferenceLow() to get reference value for high and low
//! ramp generators respectively.
//!
//! \return Returns the latched ramp maximum reference value that will be
//! loaded into the ramp generator.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getMaxRampValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the maximum ramp value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHREFA));
}

//*****************************************************************************
//
//! Sets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the ramp decrement value.
//!
//! This function sets the value that is subtracted from the ramp value on
//! every system clock cycle.
//!
//! \note This API configures the step value only for the high ramp generator
//! in down count mode and is to be deprecated in future. Use APIs
//! \e CMPSS_setRampStepHigh() and \e CMPSS_setRampStepLow() to configure the
//! step value for high and low ramp ramp generators respectively for up/down
//! count mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDecValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp decrement value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHSTEPVALS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API returns the high ramp generator step value only and is
//! to be deprecated in future. Use APIs \e CMPSS_getRampStepHigh() and
//! \e CMPSS_getRampStepLow() to configure the step value for high and
//! low ramp ramp generators respectively for up/down count mode.
//!
//! \return Returns the latched ramp decrement value that is subtracted from
//! the ramp value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampDecValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp decrement value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHSTEPVALA));
}

//*****************************************************************************
//
//! Sets the ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the 13-bit ramp delay value.
//!
//! This function sets the value that configures the number of system clock
//! cycles to delay the start of the ramp generator decrementer after a PWMSYNC
//! event is received. Delay value can be no greater than 8191.
//!
//! \note This API configures the delay value for only the high ramp generator
//! configured in down count mode and is to be deprecated in future. Use APIs
//! \e CMPSS_setRampDelayHigh() and \e CMPSS_setRampDelayLow() to configure
//! the delay value for high and low ramp generators respectively for up/down
//! count mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDelayValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 8192U);

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHDLYS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API returns delay value for only the high ramp generator and
//! is to be deprecated in future. Use APIs \e CMPSS_getRampDelayHigh() and
//! \e CMPSS_getRampDelayLow() to configure the delay value for high and
//! low ramp ramp generators respectively for up/down count mode.
//!
//! \return Returns the latched ramp delay value that is subtracted from
//! the ramp value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampDelayValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp delay value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHDLYA));
}

//*****************************************************************************
//
//! Sets the ramp direction for the high ramp generator
//!
//! \param base is the base address of the comparator module.
//! \param dir is the ramp direction for high ramp generator.
//!
//! This function sets the ramp direction for the high ramp generator.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDirectionHigh(uint32_t base, CMPSS_RampDirection dir)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp direction value to the shadow register.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) = (HWREGH(base + CMPSS_O_COMPDACHCTL) &
                                          ~(CMPSS_COMPDACHCTL_RAMPDIR)) |
                                          (uint16_t)dir;
    EDIS;
}

//*****************************************************************************
//
//! Sets the high ramp generator reference value.
//!
//! \param base is the base address of the comparator module.
//! \param value the high ramp generator reference value.
//!
//! This function sets the reference value that will be loaded into the high
//! ramp generator.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampReferenceHigh(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp reference value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHREFS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator  reference value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp reference value that will be loaded into
//! the high ramp generator.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampReferenceHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the maximum ramp value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHREFA));
}

//*****************************************************************************
//
//! Sets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the ramp decrement value.
//!
//! This function sets the value that is subtracted from the ramp value on
//! every system clock cycle.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampStepHigh(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp step value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHSTEPVALS) = value;
}

//*****************************************************************************
//
//! Gets the ramp step value for high ramp generator.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp step value that is added/subtracted from
//! the ramp reference value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampStepHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the high ramp generator step value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHSTEPVALA));
}

//*****************************************************************************
//
//! Sets the high ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the 13-bit ramp delay value.
//!
//! This function sets the value that configures the number of system clock
//! cycles to delay the start of the ramp generator incrementor/decrementor
//! after a PWMSYNC event is received. Delay value can be no greater than 8191.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDelayHigh(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 8192U);

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHDLYS) = value;
}

//*****************************************************************************
//
//! Gets the high ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp delay value that configures the number
//! of system clock cycles to delay the start of the ramp generator incrementor/
//! decrementor after a PWMSYNC event is received.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampDelayHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp delay value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHDLYA));
}

//*****************************************************************************
//
//! Sets the ramp direction for the low ramp generator
//!
//! \param base is the base address of the comparator module.
//! \param dir is the ramp direction for low ramp generator.
//!
//! This function sets the ramp direction for the low ramp generator.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDirectionLow(uint32_t base, CMPSS_RampDirection dir)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp direction value to the shadow register.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL) = (HWREGH(base + CMPSS_O_COMPDACLCTL) &
                                          ~(CMPSS_COMPDACLCTL_RAMPDIR)) |
                                          (uint16_t)dir;
    EDIS;
}

//*****************************************************************************
//
//! Sets the low ramp generator reference value.
//!
//! \param base is the base address of the comparator module.
//! \param value the low ramp generator reference value.
//!
//! This function sets the reference value that will be loaded into the low
//! ramp generator.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampReferenceLow(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp reference value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPLREFS) = value;
}

//*****************************************************************************
//
//! Gets the low ramp generator reference value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp reference value that will be loaded into
//! the low ramp generator.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampReferenceLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp reference value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPLREFA));
}

//*****************************************************************************
//
//! Sets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the ramp decrement value.
//!
//! This function sets the value that is added/subtracted from the ramp value
//! on every system clock cycle.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampStepLow(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp step value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPLSTEPVALS) = value;
}

//*****************************************************************************
//
//! Gets the ramp step value for low ramp generator.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp step value that is added/subtracted from
//! the ramp reference value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampStepLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the low ramp generator step value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPLSTEPVALA));
}

//*****************************************************************************
//
//! Sets the low ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the 13-bit ramp delay value.
//!
//! This function sets the value that configures the number of system clock
//! cycles to delay the start of the ramp generator incrementor/decrementor
//! after a PWMSYNC event is received. Delay value can be no greater than 8191.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampDelayLow(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 8192U);

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPLDLYS) = value;
}

//*****************************************************************************
//
//! Gets the low ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return Returns the latched ramp delay value that configures the number
//! of system clock cycles to delay the start of the ramp generator incrementor/
//! decrementor after a PWMSYNC event is received.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampDelayLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp delay value from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPLDLYA));
}

//*****************************************************************************
//
//! Configures high ramp generator cross trigger feature
//!
//! \param base is the base address of the comparator module.
//! \param trigger is the desired cross trigger for ramp generation
//!
//! This function configures the cross trigger feature for the high ramp
//! generators. Cross triggering allows usage of both high and low ramp
//! generators in the CMPSS with the involvement of single PWM trigger. When
//! enabled, cross triggering allows selected PWMSYNCx signal to trigger start
//! of ramp(SOR) of primary ramp while secondary ramp can be triggered by the
//! end of ramp (EOR) of primary ramp generator.
//!
//! \note The primary ramp generator trigger can be configured through
//! CMPSS_configureSyncSourceHigh() API.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configureRampXTriggerHigh(uint32_t base, CMPSS_RampXTrigger trigger)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp delay value to the shadow register.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) =
                                     (HWREGH(base + CMPSS_O_COMPDACHCTL2) &
                                      ~CMPSS_COMPDACHCTL2_XTRIGCFG_M)     |
                                     ((uint16_t)trigger <<
                                      CMPSS_COMPDACHCTL2_XTRIGCFG_S);
    EDIS;
}

//*****************************************************************************
//
//! Configures sync source for high comparator
//!
//! \param base is the base address of the comparator module.
//! \param syncSource is the desired EPWMxSYNCPER source
//!
//! This function configures desired EPWMxSYNCPER source for high comparator
//! blocks. Configured EPWMxSYNCPER signal can be used to synchronize loading
//! of DAC input value from shadow to active register. It can also be used to
//! synchronize Ramp generator, if applicable. Refer to device manual to check
//! if Ramp generator is available in the desired CMPSS instance.
//!
//! Valid values for \e syncSource parameter can be 1 to n, where n represents
//! the maximum number of EPWMSYNCPER signals available on the device. For
//! instance, passing 2 into \e syncSource will select EPWM2SYNCPER.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configureSyncSourceHigh(uint32_t base, uint16_t syncSource)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp delay value to the shadow register.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) = (HWREGH(base + CMPSS_O_COMPDACHCTL) &
                                          ~CMPSS_COMPDACHCTL_RAMPSOURCE_M)   |
                                         ((uint16_t)(syncSource - 1U)       <<
                                          CMPSS_COMPDACHCTL_RAMPSOURCE_S);
    EDIS;
}

//*****************************************************************************
//
//! Configures sync source for low comparator
//!
//! \param base is the base address of the comparator module.
//! \param syncSource is the desired EPWMxSYNCPER source
//!
//! This function configures desired EPWMxSYNCPER source for low comparator
//! blocks. Configured EPWMxSYNCPER signal can be used to synchronize loading
//! of DAC input value from shadow to active register. It can also be used to
//! synchronize Ramp generator, if applicable. Refer to device manual to check
//! if Ramp generator is available in the desired CMPSS instance.
//!
//! Valid values for \e syncSource parameter can be 1 to n, where n represents
//! the maximum number of EPWMSYNCPER signals available on the device. For
//! instance, passing 2 into \e syncSource will select EPWM2SYNCPER.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configureSyncSourceLow(uint32_t base, uint16_t syncSource)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp delay value to the shadow register.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL) = (HWREGH(base + CMPSS_O_COMPDACLCTL) &
                                          ~CMPSS_COMPDACLCTL_RAMPSOURCE_M)   |
                                         ((uint16_t)(syncSource - 1U)       <<
                                          CMPSS_COMPDACLCTL_RAMPSOURCE_S);
    EDIS;
}

//*****************************************************************************
//
//! Sets the high ramp generator clock divider value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the ramp clock divider value.
//!
//! This function sets the ramp clock divider value for high comparator(COMPH)
//! to be divided from SYSCLK to configure the ramp generator clock. Valid
//! values for param \e divider can be refered from enum \e CMPSS_RampClockDiv.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampClockDividerHigh(uint32_t base, CMPSS_RampClockDiv divider)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)divider <= CMPSS_RAMPHCTLS_RAMPCLKDIV_M);

    //
    // Write the high ramp generator clock divider to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHCTLS) = (uint16_t)divider;
}

//*****************************************************************************
//
//! Gets the high ramp generator clock divider value.
//!
//! \param base is the base address of the comparator module.
//!
//! \return Returns the latched ramp clock divider value that is divided from
//! the SYSCLK to configure the ramp generator clock.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampClockDividerHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the high ramp generator clock divider from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPHCTLA) & CMPSS_RAMPHCTLA_RAMPCLKDIV_M);
}

//*****************************************************************************
//
//! Sets the low ramp generator clock divider value.
//!
//! \param base is the base address of the comparator module.
//! \param divider is the ramp clock divider value.
//!
//! This function sets the ramp clock divider value for low comparator(COMPL)
//! to be divided from SYSCLK to configure the ramp generator clock. Valid
//! values for param \e divider can be refered from enum \e CMPSS_RampClockDiv.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setRampClockDividerLow(uint32_t base, CMPSS_RampClockDiv divider)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)divider <= CMPSS_RAMPLCTLS_RAMPCLKDIV_M);

    //
    // Write the low ramp generator clock divider to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPLCTLS) = (uint16_t)divider;
}

//*****************************************************************************
//
//! Gets the low ramp generator clock divider value.
//!
//! \param base is the base address of the comparator module.
//!
//! \return Returns the latched ramp clock divider value that is divided from
//! the SYSCLK to configure the low ramp generator clock.
//
//*****************************************************************************
static inline uint16_t
CMPSS_getRampClockDividerLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the low ramp generator clock divider from the register.
    //
    return(HWREGH(base + CMPSS_O_RAMPLCTLA) & CMPSS_RAMPLCTLA_RAMPCLKDIV_M);
}
//*****************************************************************************
//
//! Sets the comparator hysteresis settings.
//!
//! \param base is the base address of the comparator module.
//! \param value is the amount of hysteresis on the comparator inputs.
//!
//! This function sets the amount of hysteresis on the comparator inputs. The
//! \e value parameter indicates the amount of hysteresis desired. Passing in 0
//! results in none, passing in 1 results in typical hysteresis, passing in 2
//! results in 2x of typical hysteresis, and so on where \e value x of typical
//! hysteresis is the amount configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_setHysteresis(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value <= 4U);

    //
    // Read the ramp delay value from the register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPHYSCTL) = value;

    EDIS;
}

//*****************************************************************************
//
//! Enables reset of HIGH comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables EPWMSYNCPER reset of High comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableLatchResetOnPWMSYNCHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_HSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Disables reset of HIGH comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables EPWMSYNCPER reset of High comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableLatchResetOnPWMSYNCHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_HSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Enables reset of LOW comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables EPWMSYNCPER reset of Low comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableLatchResetOnPWMSYNCLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_LSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Disables reset of LOW comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables EPWMSYNCPER reset of Low comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableLatchResetOnPWMSYNCLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_LSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Sets the ePWM module blanking signal that holds trip in reset.
//!
//! \param base is the base address of the comparator module.
//! \param pwmBlankSrc is the number of the PWMBLANK source.
//!
//! This function configures which PWMBLANK signal from the ePWM module will
//! hold trip in reset when blanking is enabled.
//!
//! The number of the PWMBLANK signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmBlankSrc parameter. For
//! instance, passing a 2 into \e pwmBlankSrc will select PWMBLANK2.
//!
//! \note This API configures blanking source for only the high comparator and
//! is to be deprecated in future. Use APIs \e CMPSS_configBlankingSourceHigh()
//! and \e CMPSS_configBlankingSourceLow() to configure the blanking source for
//! high and low comparators respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configBlanking(uint32_t base, uint16_t pwmBlankSrc)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((pwmBlankSrc >= 1U) && (pwmBlankSrc <= 16U));

    //
    // Write the blank source number to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACHCTL) =
       (HWREGH(base + CMPSS_O_COMPDACHCTL) & ~CMPSS_COMPDACHCTL_BLANKSOURCE_M) |
       ((pwmBlankSrc - 1U) << CMPSS_COMPDACHCTL_BLANKSOURCE_S);

    EDIS;
}

//*****************************************************************************
//
//! Enables an ePWM blanking signal to hold trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables a selected ePWM blanking signal to hold trip in
//! reset.
//!
//! \note This API enables blanking for only the high comparator subsystem and
//! is to be deprecated in future. Use APIs \e CMPSS_enableBlankingHigh() and
//! \e CMPSS_enableBlankingLow() to enable the blanking for high and low
//! comparators respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableBlanking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) |= CMPSS_COMPDACHCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables an ePWM blanking signal from holding trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables a selected ePWM blanking signal from holding trip in
//! reset.
//!
//! \note This API disables blanking for only the high comparator subsystem and
//! is to be deprecated in future. Use APIs \e CMPSS_disableBlankingHigh() and
//! \e CMPSS_disableBlankingLow() to disable the blanking for high and low
//! comparators respectively.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableBlanking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) &= ~CMPSS_COMPDACHCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets the high comparator ePWM module blanking signal source that holds
//! trip in reset.
//!
//! \param base is the base address of the comparator module.
//! \param pwmBlankSrc is the number of the PWMBLANK source.
//!
//! This function configures which PWMBLANK signal from the ePWM module will
//! hold trip in reset when blanking is enabled in high comparator digital
//! filter.
//!
//! The number of the PWMBLANK signal to be used should be specified by passing
//! it into the \e pwmBlankSrc parameter. For instance, passing a 2 into
//! \e pwmBlankSrc will select PWMBLANK2.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configBlankingSourceHigh(uint32_t base, uint16_t pwmBlankSrc)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((pwmBlankSrc >= 1U) && (pwmBlankSrc <= 16U));

    //
    // Write the blank source number to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACHCTL) =
       (HWREGH(base + CMPSS_O_COMPDACHCTL) & ~CMPSS_COMPDACHCTL_BLANKSOURCE_M) |
       ((pwmBlankSrc - 1U) << CMPSS_COMPDACHCTL_BLANKSOURCE_S);

    EDIS;
}

//*****************************************************************************
//
//! Enables high comparator's ePWM blanking signal to hold trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables high comparator's selected ePWM blanking signal
//! to hold trip in reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableBlankingHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) |= CMPSS_COMPDACHCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables high comparator's ePWM blanking signal from holding trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables high comparator's selected ePWM blanking signal from
//! holding trip in reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableBlankingHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL) &= ~CMPSS_COMPDACHCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets the low comparator's ePWM module blanking signal source that holds
//! trip in reset.
//!
//! \param base is the base address of the comparator module.
//! \param pwmBlankSrc is the number of the PWMBLANK source.
//!
//! This function configures which PWMBLANK signal from the ePWM module will
//! hold trip in reset when blanking is enabled for low comparator.
//!
//! The number of the PWMBLANK signal to be used should be specified by passing
//! it into the \e pwmBlankSrc parameter. For instance, passing a 2 into
//! \e pwmBlankSrc will select PWMBLANK2.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configBlankingSourceLow(uint32_t base, uint16_t pwmBlankSrc)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((pwmBlankSrc >= 1U) && (pwmBlankSrc <= 16U));

    //
    // Write the blank source number to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACLCTL) = (HWREGH(base + CMPSS_O_COMPDACLCTL) &
                        ~CMPSS_COMPDACLCTL_BLANKSOURCE_M) |
                        ((pwmBlankSrc - 1U) << CMPSS_COMPDACLCTL_BLANKSOURCE_S);

    EDIS;
}

//*****************************************************************************
//
//! Enables low comparator's ePWM blanking signal to hold trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables low comparator's selected ePWM blanking signal to
//! hold trip in reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableBlankingLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL) |= CMPSS_COMPDACLCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables low comparator's ePWM blanking signal from holding trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables low comparator's selected ePWM blanking signal from
//! holding trip in reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableBlankingLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL) &= ~CMPSS_COMPDACLCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Enables the CMPSS diode emulation mode.
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables the CMPSS diode emulation mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_enableDEmode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Enable diode emulation mode.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) |=  CMPSS_COMPDACHCTL2_DEENABLE;
    EDIS;
}

//*****************************************************************************
//
//! Disables the CMPSS diode emulation mode
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables the CMPSS diode emulation mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_disableDEmode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Disable diode emulation mode.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) &=  ~CMPSS_COMPDACHCTL2_DEENABLE;
    EDIS;
}

//*****************************************************************************
//
//! Select the CMPSS diode emulation mode DEACTIVE source
//!
//! \param base is the base address of the comparator module.
//! \param deactivesel is the DEACTIVE source select
//!
//! This function selects the CMPSS diode emulation mode DEACTIVE source
//! Valid values for param \e deactivesel are to be referred from
//! \e CMPSS_DEActiveSelect enum.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_selectDEACTIVESource(uint32_t base, uint16_t deactivesel)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(deactivesel <= 31U);

    //
    // Select diode emulation active source.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) =
                             (HWREGH(base + CMPSS_O_COMPDACHCTL2)  &
                              ~(CMPSS_COMPDACHCTL2_DEACTIVESEL_M)) |
                             (deactivesel << CMPSS_COMPDACHCTL2_DEACTIVESEL_S);
    EDIS;
}

//*****************************************************************************
//
//! Sets the shadow value 2 (used in DE mode) of the internal DAC of the high
//! comparator.
//!
//! \param base is the base address of the comparator module.
//! \param dacval is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the high
//! comparator. This function will load the value into the shadow register 2
//! from which the actual DAC value register will be loaded in DE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configHighDACShadowValueDE(uint32_t base, uint16_t dacval)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(dacval <= 4095U);

    //
    // Configure high comp DAC shadow value 2.
    //
    HWREGH(base + CMPSS_O_DACHVALS2) = (dacval & CMPSS_DACHVALS2_DACVAL_M);
}

//*****************************************************************************
//
//! Sets the shadow value 2 (used in DE mode) of the internal DAC of the low
//! comparator.
//!
//! \param base is the base address of the comparator module.
//! \param dacval is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the low
//! comparator. This function will load the value into the shadow register 2
//! from which the actual DAC value register will be loaded in DE mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_configLowDACShadowValueDE(uint32_t base, uint16_t dacval)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(dacval <= 4095U);

    //
    // Configure low comp DAC shadow value 2.
    //
    HWREGH(base + CMPSS_O_DACLVALS2) = (dacval & CMPSS_DACLVALS2_DACVAL_M);
}

//*****************************************************************************
//
//! Select the Blank source group for high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param group is the blank source group
//!
//! This function selects the Blank source group for high comparator(COMPH).
//! Valid values for param \e group can be: CMPSS_EPWM_GROUP_0TO15 or
//! CMPSS_EPWM_GROUP_16TO31.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_selectBlankSourceGroupHigh(uint32_t base, CMPSS_EPWMGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)group <= 1U);

    //
    // Configure the Blanking source group.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) =
                                (HWREGH(base + CMPSS_O_COMPDACHCTL2) &
                                 ~CMPSS_COMPDACHCTL2_BLANKSOURCEUSEL) |
                                ((uint16_t)group << CMPSS_BLANKSOURCEUSEL_S);
    EDIS;
}

//*****************************************************************************
//
//! Select the Blank source group for low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param group is the blank source group.
//!
//! This function selects the Blank source group for low comparator(COMPL).
//! Valid values for param \e group can be: CMPSS_EPWM_GROUP_0TO15 or
//! CMPSS_EPWM_GROUP_16TO31.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_selectBlankSourceGroupLow(uint32_t base, CMPSS_EPWMGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)group <= 1U);

    //
    // Configure the Blanking source group.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL2) =
                                (HWREGH(base + CMPSS_O_COMPDACLCTL2) &
                                 ~CMPSS_COMPDACLCTL2_BLANKSOURCEUSEL) |
                                ((uint16_t)group << CMPSS_BLANKSOURCEUSEL_S);
    EDIS;
}

//*****************************************************************************
//
//! Select the Ramp source group for high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param group is the ramp source group.
//!
//! This function selects the Ramp source group for high comparator(COMPH).
//! Valid values for param \e group can be: CMPSS_EPWM_GROUP_0TO15 or
//! CMPSS_EPWM_GROUP_16TO31.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_selectRampSourceGroupHigh(uint32_t base, CMPSS_EPWMGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)group <= 1U);

    //
    // Configure the Blanking source group.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACHCTL2) =
                                    (HWREGH(base + CMPSS_O_COMPDACHCTL2) &
                                     ~CMPSS_COMPDACHCTL2_RAMPSOURCEUSEL) |
                                    ((uint16_t)group << CMPSS_RAMPSOURCEUSEL_S);
    EDIS;
}

//*****************************************************************************
//
//! Select the Ramp source group for low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param group is the ramp source group.
//!
//! This function selects the Ramp source group for low comparator(COMPL).
//! Valid values for param \e group can be: CMPSS_EPWM_GROUP_0TO15 or
//! CMPSS_EPWM_GROUP_16TO31.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSS_selectRampSourceGroupLow(uint32_t base, CMPSS_EPWMGroup group)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((uint16_t)group <= 1U);

    //
    // Configure the Blanking source group.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACLCTL2) =
                                    (HWREGH(base + CMPSS_O_COMPDACLCTL2) &
                                     ~CMPSS_COMPDACLCTL2_RAMPSOURCEUSEL) |
                                    ((uint16_t)group << CMPSS_RAMPSOURCEUSEL_S);
    EDIS;
}

//*****************************************************************************
//
//! Configures the digital filter of the high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param samplePrescale is the number of system clock cycles between samples.
//! \param sampleWindow is the number of FIFO samples to monitor.
//! \param threshold is the majority threshold of samples to change state.
//!
//! This function configures the operation of the digital filter of the high
//! comparator.
//!
//! The \e samplePrescale parameter specifies the number of system clock cycles
//! between samples.It is a 24-bit value so a number higher than 16777215 should
//! not be passed as this parameter. The prescaler used by digital filter is 1
//! more than \e samplePrescale value. So, the input provided should be 1 less
//! than the expected prescaler.
//!
//! The \e sampleWindow parameter configures the size of the window of FIFO
//! samples taken from the input that will be monitored to determine when to
//! change the filter output. This sample window may be no larger than 64
//! samples.
//!
//! The \e threshold parameter configures the threshold value to be used by
//! the digital filter.
//!
//! The filter output resolves to the majority value of the sample window where
//! majority is defined by the value passed into the \e threshold parameter.
//! For proper operation, the value of \e threshold must be greater than
//! sampleWindow / 2.
//!
//! To ensure proper operation of the filter, the following is the recommended
//! function call sequence for initialization:
//!
//! -# Configure and enable the comparator using CMPSS_configHighComparator()
//!    and CMPSS_enableModule()
//! -# Configure the digital filter using CMPSS_configFilterHigh()
//! -# Initialize the sample values using CMPSS_initFilterHigh()
//! -# Configure the module output signals CTRIP and CTRIPOUT using
//!    CMPSS_configOutputsHigh()
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configFilterHigh(uint32_t base, uint32_t samplePrescale,
                       uint16_t sampleWindow, uint16_t threshold);

//*****************************************************************************
//
//! Configures the digital filter of the low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param samplePrescale is the number of system clock cycles between samples.
//! \param sampleWindow is the number of FIFO samples to monitor.
//! \param threshold is the majority threshold of samples to change state.
//!
//! This function configures the operation of the digital filter of the low
//! comparator.
//!
//! The \e samplePrescale parameter specifies the number of system clock cycles
//! between samples.It is a 24-bit value so a number higher than 16777215 should
//! not be passed as this parameter. The prescaler used by digital filter is 1
//! more than \e samplePrescale value. So, the input provided should be 1 less
//! than the expected prescaler.
//!
//! The \e sampleWindow parameter configures the size of the window of FIFO
//! samples taken from the input that will be monitored to determine when to
//! change the filter output. This sample window may be no larger than 64
//! samples.
//!
//! The \e threshold parameter configures the threshold value to be used by
//! the digital filter.
//!
//! The filter output resolves to the majority value of the sample window where
//! majority is defined by the value passed into the \e threshold parameter.
//! For proper operation, the value of \e threshold must be greater than
//! sampleWindow / 2.
//!
//! To ensure proper operation of the filter, the following is the recommended
//! function call sequence for initialization:
//!
//! -# Configure and enable the comparator using CMPSS_configLowComparator()
//!    and CMPSS_enableModule()
//! -# Configure the digital filter using CMPSS_configFilterLow()
//! -# Initialize the sample values using CMPSS_initFilterLow()
//! -# Configure the module output signals CTRIP and CTRIPOUT using
//!    CMPSS_configOutputsLow()
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configFilterLow(uint32_t base, uint32_t samplePrescale,
                      uint16_t sampleWindow, uint16_t threshold);

//*****************************************************************************
//
//! Configures whether or not the digital filter latches are reset by PWMSYNC
//!
//! \param base is the base address of the comparator module.
//! \param highEnable indicates filter latch settings in the high comparator.
//! \param lowEnable indicates filter latch settings in the low comparator.
//!
//! This function configures whether or not the digital filter latches in both
//! the high and low comparators should be reset by PWMSYNC. If the
//! \e highEnable parameter is \b true, the PWMSYNC will be allowed to reset
//! the high comparator's digital filter latch. If it is false, the ability of
//! the PWMSYNC to reset the latch will be disabled. The \e lowEnable parameter
//! has the same effect on the low comparator's digital filter latch.
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configLatchOnPWMSYNC(uint32_t base, bool highEnable, bool lowEnable);

//*****************************************************************************
//
//! Configures the comparator subsystem's ramp generator.
//!
//! \param base is the base address of the comparator module.
//! \param maxRampVal is the ramp maximum reference value.
//! \param decrementVal value is the ramp decrement value.
//! \param delayVal is the ramp delay value.
//! \param pwmSyncSrc is the number of the PWMSYNC source.
//! \param useRampValShdw indicates if the max ramp shadow should be used.
//!
//! This function configures many of the main settings of the comparator
//! subsystem's ramp generator. The \e maxRampVal parameter should be passed
//! the ramp maximum reference value that will be loaded into the ramp
//! generator. The \e decrementVal parameter should be passed the decrement
//! value that will be subtracted from the ramp generator on each system clock
//! cycle. The \e delayVal parameter should be passed the 13-bit number of
//! system clock cycles the ramp generator should delay before beginning to
//! decrement the ramp generator after a PWMSYNC signal is received.
//!
//!
//! The number of the PWMSYNC signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmSyncSrc parameter. For
//! instance, passing a CMPSS_PWMSYNCx into \e pwmSyncSrc will select PWMSYNCx.
//!
//! To indicate whether the ramp generator should reset with the value from the
//! ramp max reference value shadow register or with the latched ramp max
//! reference value, use the \e useRampValShdw parameter. Passing it \b true
//! will result in the latched value being bypassed. The ramp generator will be
//! loaded right from the shadow register. A value of \b false will load the
//! ramp generator from the latched value.
//!
//! \note This API configures the high ramp generator in down count mode
//! only and is to be deprecated for this device. Use \e CMPSS_configRampHigh()
//! and \e CMPSS_configRampLow() for configuring the hign and low ramp
//! generators respectively in up/down count mode as per the requirement.
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configRamp(uint32_t base, uint16_t maxRampVal, uint16_t decrementVal,
                 uint16_t delayVal, uint16_t pwmSyncSrc, bool useRampValShdw);

//*****************************************************************************
//
//! Configures the comparator subsystem's high ramp generator.
//!
//! \param base is the base address of the comparator module.
//! \param rampDir is ramp direction of high ramp generator.
//! \param rampRef is the ramp reference value of high ramp generator.
//! \param stepVal value is ramp step value of high ramp generator.
//! \param delayVal is ramp delay value of high ramp generator.
//! \param pwmSyncSrc is the number of the PWMSYNC source.
//! \param useRampValShdw indicates if ramp reference shadow should be used.
//!
//! This function configures many of the main settings of the comparator
//! subsystem's high ramp generator. The \e rampDir parameter should be passed
//! the desired ramp direction. The \e rampRef parameter should be passed
//! the ramp reference value based on the direction that will be loaded into
//! the ramp generator. The \e stepVal parameter should be passed the ramp step
//! value that will be added/subtracted based on the direction from the ramp
//! generator on each system clock cycle. The \e delayVal parameter should be
//! passed the 13-bit number of system clock cycles the ramp generator should
//! delay before beginning to decrement the ramp generator after a PWMSYNC
//! signal is received.
//!
//! Values for parameters \e rampDir, \e rampRef, \e stepVal, \e delayVal and
//! \e pwmSyncSrc may be set individually using \b CMPSS_setRampDirectionHigh(),
//! \b CMPSS_setRampReferenceHigh(), \b CMPSS_setRampStepHigh(),
//! \b CMPSS_setRampDelayHigh() and \b CMPSS_configureSyncSourceHigh() APIs
//! respectively.
//!
//! The number of the PWMSYNC signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmSyncSrc parameter. For
//! instance, passing a CMPSS_PWMSYNCx into \e pwmSyncSrc will select PWMSYNCx.
//!
//! To indicate whether the ramp generator should reset with the value from the
//! ramp reference value shadow register or with the latched ramp reference
//! value, use the \e useRampValShdw parameter. Passing it \b true will result
//! in the latched value being bypassed. The ramp generator will be loaded right
//! from the shadow register. A value of \b false will load the ramp generator
//! from the latched value.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configRampHigh(uint32_t base, CMPSS_RampDirection rampDir,
                     uint16_t rampRef, uint16_t stepVal, uint16_t delayVal,
                     uint16_t pwmSyncSrc, bool useRampValShdw);

//*****************************************************************************
//
//! Configures the comparator subsystem's low ramp generator.
//!
//! \param base is the base address of the comparator module.
//! \param rampDir is ramp direction of low ramp generator.
//! \param rampRef is the ramp reference value of low ramp generator.
//! \param stepVal value is ramp step value of low ramp generator.
//! \param delayVal is ramp delay value of low ramp generator.
//! \param pwmSyncSrc is the number of the PWMSYNC source.
//! \param useRampValShdw indicates if ramp reference shadow should be used.
//!
//! This function configures many of the main settings of the comparator
//! subsystem's low ramp generator. The \e rampDir parameter should be passed
//! the desired ramp direction. The \e rampRef parameter should be passed
//! the ramp reference value based on the direction that will be loaded into
//! the ramp generator. The \e stepVal parameter should be passed the ramp step
//! value that will be added/subtracted based on the direction from the ramp
//! generator on each system clock cycle. The \e delayVal parameter should be
//! passed the 13-bit number of system clock cycles the ramp generator should
//! delay before beginning to decrement the ramp generator after a PWMSYNC
//! signal is received.
//!
//! Values for parameters \e rampDir, \e rampRef, \e stepVal, \e delayVal and
//! \e pwmSyncSrc may be set individually using \b CMPSS_setRampDirectionLow(),
//! \b CMPSS_setRampReferenceLow(), \b CMPSS_setRampStepLow(),
//! \b CMPSS_setRampDelayLow() and \b CMPSS_configureSyncSourceLow() APIs
//! respectively.
//!
//! The number of the PWMSYNC signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmSyncSrc parameter. For
//! instance, passing a CMPSS_PWMSYNCx into \e pwmSyncSrc will select PWMSYNCx.
//!
//! To indicate whether the ramp generator should reset with the value from the
//! ramp reference value shadow register or with the latched ramp reference
//! value, use the \e useRampValShdw parameter. Passing it \b true will result
//! in the latched value being bypassed. The ramp generator will be loaded right
//! from the shadow register. A value of \b false will load the ramp generator
//! from the latched value.
//!
//! \note This API is not valid for CMPSS-Lite IP.
//!
//! \return None.
//
//*****************************************************************************
extern void
CMPSS_configRampLow(uint32_t base, CMPSS_RampDirection rampDir,
                    uint16_t rampRef, uint16_t stepVal, uint16_t delayVal,
                    uint16_t pwmSyncSrc, bool useRampValShdw);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // CMPSS_H
