//###########################################################################
//
// FILE:   asysctl.h
//
// TITLE:  C28x driver for Analog System Control.
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

#ifndef ASYSCTL_H
#define ASYSCTL_H

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
//! \addtogroup asysctl_api ASysCtl
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_asysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "debug.h"
#include "cpu.h"

//
// OSCSTATUS value on completion
//
#define ASYSCTL_EXTR_ENABLE_COMPLETE (0xE7U)

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setAnalogReferenceInternal()
// ASysCtl_setAnalogReferenceExternal()
// ASysCtl_setAnalogReference2P5()
// ASysCtl_setAnalogReference1P65()
//
//*****************************************************************************
#define ASYSCTL_VREFHI  0x1U //!< VREFHI

//*****************************************************************************
//
// Values used for function ASysCtl_enableCMPSSExternalDAC() and
// ASysCtl_disableCMPSSExternalDAC().  These values can be OR-ed together and
// passed these functions.
//
//*****************************************************************************
#define ASYSCTL_CMPSS1_DACL 0x1U //!< CMPSS1.DACL

//*****************************************************************************
//
// Values used for function ASysCtl_selectCMPHNMux() and
// ASysCtl_selectCMPHNMuxValue().  These values can be OR-ed together and
// passed to ASysCtl_selectCMPHNMux().
//
//*****************************************************************************
#define ASYSCTL_CMPHNMUX_SELECT_1 0x1U //!< CMPHNMUX select 1
#define ASYSCTL_CMPHNMUX_SELECT_2 0x2U //!< CMPHNMUX select 2
#define ASYSCTL_CMPHNMUX_SELECT_3 0x4U //!< CMPHNMUX select 3
#define ASYSCTL_CMPHNMUX_SELECT_4 0x8U //!< CMPHNMUX select 4

//*****************************************************************************
//
// Values used for function ASysCtl_selectCMPLNMux() and
// ASysCtl_selectCMPLNMuxValue().  These values can be OR-ed together and
// passed to ASysCtl_selectCMPLNMux().
//
//*****************************************************************************
#define ASYSCTL_CMPLNMUX_SELECT_1 0x1U //!< CMPLNMUX select 1
#define ASYSCTL_CMPLNMUX_SELECT_2 0x2U //!< CMPLNMUX select 2
#define ASYSCTL_CMPLNMUX_SELECT_3 0x4U //!< CMPLNMUX select 3
#define ASYSCTL_CMPLNMUX_SELECT_4 0x8U //!< CMPLNMUX select 4

//*****************************************************************************
//
//! ASysCtl_CMPHPMuxSelect used for function ASysCtl_selectCMPHPMux().
//
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPHPMUX_SELECT_1 = 0U, //!< CMPHPMUX select 1
    ASYSCTL_CMPHPMUX_SELECT_2 = 3U, //!< CMPHPMUX select 2
    ASYSCTL_CMPHPMUX_SELECT_3 = 6U, //!< CMPHPMUX select 3
    ASYSCTL_CMPHPMUX_SELECT_4 = 9U  //!< CMPHPMUX select 4
} ASysCtl_CMPHPMuxSelect;

//*****************************************************************************
//
//! ASysCtl_CMPLPMuxSelect used for function ASysCtl_selectCMPLPMux().
//
//*****************************************************************************
typedef enum
{
    ASYSCTL_CMPLPMUX_SELECT_1 = 0U, //!< CMPLPMUX select 1
    ASYSCTL_CMPLPMUX_SELECT_2 = 3U, //!< CMPLPMUX select 2
    ASYSCTL_CMPLPMUX_SELECT_3 = 6U, //!< CMPLPMUX select 3
    ASYSCTL_CMPLPMUX_SELECT_4 = 9U  //!< CMPLPMUX select 4
} ASysCtl_CMPLPMuxSelect;

//*****************************************************************************
//
//! ASysCtl_TestSelect used for function ASysCtl_selectInternalTestNode().
//
//*****************************************************************************
typedef enum
{
    ASYSCTL_TEST_NODE_NO_CONN       = 0U,  //!< No Internal Connection
    ASYSCTL_TEST_NODE_VDDCORE         = 1U,  //!< Core VDD (1.2V) voltage
    ASYSCTL_TEST_NODE_VREFLO              = 2U,  //!< VREFLO pin voltage
    ASYSCTL_TEST_NODE_CDAC1H              = 4U,  //!< CMPSS1 High DAC output
    ASYSCTL_TEST_NODE_CDAC1L              = 5U,  //!< CMPSS1 Low DAC output
    ASYSCTL_TEST_NODE_CDAC2H              = 6U,  //!< CMPSS2 High DAC output
    ASYSCTL_TEST_NODE_CDAC2L              = 7U,  //!< CMPSS2 Low DAC output
    ASYSCTL_TEST_NODE_CDAC3H              = 8U,  //!< CMPSS3 High DAC output
    ASYSCTL_TEST_NODE_CDAC3L              = 9U,  //!< CMPSS3 Low DAC output
    ASYSCTL_TEST_NODE_CDAC4H              = 10U, //!< CMPSS4 High DAC output
    ASYSCTL_TEST_NODE_CDAC4L              = 11U, //!< CMPSS4 Low DAC output
    ASYSCTL_TEST_NODE_VDDA                = 12U, //!< VDDA voltage
    ASYSCTL_TEST_NODE_VSSA                = 13U, //!< VSSA - Analog ground pin
    ASYSCTL_TEST_NODE_ENZ_CALIB_GAIN_3P3V = 19U //!< All ADCs are placed in gain
                                                //!< calibration mode
} ASysCtl_TestSelect;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Enable temperature sensor.
//!
//! This function enables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_enableTemperatureSensor(void)
{
    EALLOW;

    //
    // Set the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_TSNSCTL) |= ASYSCTL_TSNSCTL_ENABLE;

    EDIS;
}

//*****************************************************************************
//
//! Disable temperature sensor.
//!
//! This function disables the temperature sensor output to the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_disableTemperatureSensor(void)
{
    EALLOW;

    //
    // Clear the temperature sensor enable bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_TSNSCTL) &= ~(ASYSCTL_TSNSCTL_ENABLE);

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to internal.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHI
//!
//! \note Internal reference mode is not available for packages lacking VREFHI
//! and VREFLO pins. Please see device datasheet for packages with VREFHI and
//! VREFLO pins available.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceInternal(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHI
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &= ~reference;

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to external.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHI
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceExternal(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHI
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog External Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |= reference;

    EDIS;
}
//*****************************************************************************
//
//! Set the internal analog voltage reference selection to 2.5V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHI
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference2P5(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHI
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |= (reference << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Set the internal analog voltage reference selection to 1.65V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_VREFHI
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference1P65(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHI
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &= ~(reference << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Select internal test node for ADC.
//!
//! \param testSelect is internal node to come out on ADC.
//!
//! The \e testSelect is the desired internal test node. Valid values can be
//! refered from the enum \e ASysCtl_TestSelect.
//!
//! \return None.
//!
//*****************************************************************************
static inline void ASysCtl_selectInternalTestNode(ASysCtl_TestSelect testSelect)
{
    EALLOW;

    //
    // Select internal test node for ADC
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_INTERNALTESTCTL) = 
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_INTERNALTESTCTL) &
        ~(ASYSCTL_INTERNALTESTCTL_TESTSEL_M | ASYSCTL_INTERNALTESTCTL_KEY_M)) | 
        (0xA5A50000UL | testSelect);

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPHNMXSEL.
//!
//! \param select is a combination of CMPHNMXSEL values.
//!
//! The parameter \e select can be a bitwise OR of the below values:
//!
//! - \b ASYSCTL_CMPHNMUX_SELECT_1
//! - \b ASYSCTL_CMPHNMUX_SELECT_2
//! - \b ASYSCTL_CMPHNMUX_SELECT_3
//! - \b ASYSCTL_CMPHNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);

    EALLOW;

    //
    // Write a select to the mux select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) = select;

    EDIS;
}

//*****************************************************************************
//
//! Select the value for individual CMPxHNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b ASYSCTL_CMPHNMUX_SELECT_1
//! - \b ASYSCTL_CMPHNMUX_SELECT_2
//! - \b ASYSCTL_CMPHNMUX_SELECT_3
//! - \b ASYSCTL_CMPHNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPHNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);

    EALLOW;

    //
    // Write a select to the mux select bit.
    //
    if(value == 0U)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) &= ~select;
    }
    else if(value == 1U)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHNMXSEL) |= select;
    }
    else
    {
        //Do nothing. Not a valid value
    }

    EDIS;
}

//*****************************************************************************
//
//! Select the value for individual CMPxLNMXSEL.
//!
//! \param select is a combination of CMPLNMXSEL values.
//!
//! The parameter \e select can be the bitwise OR of the below values:
//!
//! - \b ASYSCTL_CMPLNMUX_SELECT_1
//! - \b ASYSCTL_CMPLNMUX_SELECT_2
//! - \b ASYSCTL_CMPLNMUX_SELECT_3
//! - \b ASYSCTL_CMPLNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLNMux(uint16_t select)
{
    ASSERT(select <= 0x7FU);

    EALLOW;

    //
    // Write a select to the mux select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) = select;

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLNMXSEL.
//!
//! \param select is the CMPxHNMXSEL to be set.
//! \param value is 0 or 1.
//!
//! The parameter \e select can be one of the below values:
//!
//! - \b ASYSCTL_CMPLNMUX_SELECT_1
//! - \b ASYSCTL_CMPLNMUX_SELECT_2
//! - \b ASYSCTL_CMPLNMUX_SELECT_3
//! - \b ASYSCTL_CMPLNMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_selectCMPLNMuxValue(uint16_t select, uint16_t value)
{
    ASSERT(select <= 0x7FU);
    ASSERT(value <= 1U);

    EALLOW;

    //
    // Write a select to the mux select bit.
    //
    if(value == 0U)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) &= ~select;
    }
    else if(value == 1U)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLNMXSEL) |= select;
    }
    else
    {
        //Do nothing. Not a valid value
    }

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPHPMXSEL.
//!
//! \param select is of type ASysCtl_CMPHPMuxSelect.
//! \param value is 0, 1, 2, 3, 4 or 5.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPHPMUX_SELECT_1
//! - \b ASYSCTL_CMPHPMUX_SELECT_2
//! - \b ASYSCTL_CMPHPMUX_SELECT_3
//! - \b ASYSCTL_CMPHPMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPHPMux(ASysCtl_CMPHPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 5U);

    EALLOW;

    //
    // Set the value for the appropriate Mux Select.
    //
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) &
        ~((uint32_t)ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M << (uint32_t)select)) |
        (value << (uint32_t)select);

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLPMXSEL.
//!
//! \param select is of type ASysCtl_CMPLPMuxSelect.
//! \param value is 0, 1, 2, 3, 4 or 5.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPLPMUX_SELECT_1
//! - \b ASYSCTL_CMPLPMUX_SELECT_2
//! - \b ASYSCTL_CMPLPMUX_SELECT_3
//! - \b ASYSCTL_CMPLPMUX_SELECT_4
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPLPMux(ASysCtl_CMPLPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 5U);

    EALLOW;

    //
    // Set the value for the appropriate Mux Select.
    //
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) &
        ~((uint32_t)ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select)) |
        (value << (uint32_t)select);

    EDIS;
}

//*****************************************************************************
//
//! Enables the CMPSSx.DACL output to be routed to a pin.
//!
//! \param select is CMPSS instance
//!
//! This function disables CMPSSx.COMPL and the associated DAC will act as a
//! general purpose DAC with 11 bit resolution.
//! The parameter \e select can be OR of the following values:
//! - ASYSCTL_CMPSS1_DACL
//!
//! \note In this case, all other CMPSS module functionality is not useable,
//! including the high DAC, both comparators, ramp generation, and the digital
//! filters.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_enableCMPSSExternalDAC(uint32_t select)
{
    ASSERT((select & (
                      ASYSCTL_CMPSS1_DACL
                     )) == select);
    //
    // Set the specified bits and enable CMPSSCTL register
    //
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPSSCTL) =
                    (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPSSCTL) | select) |
                    ASYSCTL_CMPSSCTL_CMPSSCTLEN;
    EDIS;
}

//*****************************************************************************
//
//! Disbales the CMPSSx.DACL output to be routed to a pin.
//!
//! \param select is CMPSS instance
//!
//! This function enables CMPSSx.COMPL and the associated DAC will act as
//! reference for comparator.
//! The parameter \e select can be OR of the following values:
//! - ASYSCTL_CMPSS1_DACL
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_disableCMPSSExternalDAC(uint32_t select)
{
    ASSERT((select & (
                      ASYSCTL_CMPSS1_DACL
                     )) == select);

    //
    // Set the specified bits and enable CMPSSCTL register
    //
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPSSCTL) =
                    (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPSSCTL) & ~select) |
                    ASYSCTL_CMPSSCTL_CMPSSCTLEN;
    EDIS;
}

//*****************************************************************************
//
//! Locks the temperature sensor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockTemperatureSensor(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_TSNSCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the analog reference control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockANAREF(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ANAREFCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the voltage monitor control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVMON(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VMONCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHPMux(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHPMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLPMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLPMux(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLPMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPHNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPHNMux(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHNMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPLNMXSEL control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPLNMux(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLNMXSEL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the VREG control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockVREG(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_VREGCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the CMPSSCTL register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockCMPSSCTL(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPSSCTL;

    EDIS;
}

//*****************************************************************************
//
//! Gets the Ext-R OSC Status.
//!
//! \return Ext-R OSC Status.
//
//*****************************************************************************
static inline uint16_t ASysCtl_getExtROscStatus(void)
{
    return((HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_EXTROSCCSR1) &
           ASYSCTL_EXTROSCCSR1_OSCSTATUS_M) >> ASYSCTL_EXTROSCCSR1_OSCSTATUS_S);
}

//*****************************************************************************
//
//! Enable loopback from DAC to ADCs.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_enableADCDACLoopback(uint32_t config)
{
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) | config) |
            (0xA5A5UL << ASYSCTL_ADCDACLOOPBACK_KEY_S);
}

//*****************************************************************************
//
//! Disable loopback from DAC to ADCs.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_disableADCDACLoopback(uint32_t config)
{
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) & ~config) |
            (0xA5A5UL << ASYSCTL_ADCDACLOOPBACK_KEY_S);
}




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

#endif // ASYSCTL_H
