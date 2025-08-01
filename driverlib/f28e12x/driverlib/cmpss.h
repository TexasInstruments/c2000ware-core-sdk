//###########################################################################
//
// FILE:   cmpss.h
//
// TITLE:  C28x CMPSS driver.
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
// F28E12x device only supports CMPSS_LITE features.
//
//*****************************************************************************

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
// as the pwmSyncSrc parameter.
//
//*****************************************************************************

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
           (base == CMPSSLITE1_BASE) ||
           (base == CMPSSLITE2_BASE) ||
           (base == CMPSSLITE3_BASE)
          );
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks the CMPSS-Lite base address.
//!
//! \param base is the base address of the CMPSS-Lite module.
//!
//! This function determines if a CMPSS-Lite base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CMPSS_isLiteBaseValid(uint32_t base)
{
    return(
           (base == CMPSSLITE1_BASE) ||
           (base == CMPSSLITE2_BASE) ||
           (base == CMPSSLITE3_BASE)
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
//! Configures sync source for high comparator
//!
//! \param base is the base address of the comparator module.
//! \param syncSource is the desired MCPWMxSYNCPER source
//!
//! This function configures desired MCPWMxSYNCPER source for high comparator
//! blocks. Configured MCPWMxSYNCPER signal can be used to synchronize loading
//! of DAC input value from shadow to active register. It can also be used to
//! synchronize Ramp generator, if applicable. Refer to device manual to check
//! if Ramp generator is available in the desired CMPSS instance.
//!
//! Valid values for \e syncSource parameter can be 1 to n, where n represents
//! the maximum number of MCPWMSYNCPER signals available on the device. For
//! instance, passing 2 into \e syncSource will select MCPWM2SYNCPER.
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
//! \param syncSource is the desired MCPWMxSYNCPER source
//!
//! This function configures desired MCPWMxSYNCPER source for low comparator
//! blocks. Configured MCPWMxSYNCPER signal can be used to synchronize loading
//! of DAC input value from shadow to active register. It can also be used to
//! synchronize Ramp generator, if applicable. Refer to device manual to check
//! if Ramp generator is available in the desired CMPSS instance.
//!
//! Valid values for \e syncSource parameter can be 1 to n, where n represents
//! the maximum number of MCPWMSYNCPER signals available on the device. For
//! instance, passing 2 into \e syncSource will select MCPWM2SYNCPER.
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
        ASSERT(value <= 7U);

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
//! This function enables MCPWMSYNCPER reset of High comparator digital filter
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
//! This function disables MCPWMSYNCPER reset of High comparator digital filter
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
//! This function enables MCPWMSYNCPER reset of Low comparator digital filter
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
//! This function disables MCPWMSYNCPER reset of Low comparator digital filter
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
