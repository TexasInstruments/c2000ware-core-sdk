//###########################################################################
//
// FILE:   asysctl.h
//
// TITLE:  C28x driver for Analog System Control.
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
// These values can be used as the parameter \e config in the function
// ASysCtl_setAGPIOFilter functions
//
#define ASYSCTL_AGPIOFILTER_BYPASS  0U // Filter bypass (min ACQPS = 90ns)
#define ASYSCTL_AGPIOFILTER_333OHM  1U // 333Ohm filter (min ACQPS = 125ns)
#define ASYSCTL_AGPIOFILTER_500OHM  2U // 500 Ohm filter (min ACQPS = 160ns)
#define ASYSCTL_AGPIOFILTER_1000OHM 3U // 1KOhm filter  (min ACQPS = 230ns)

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setAnalogReferenceInternal()
// ASysCtl_setAnalogReferenceExternal()
// ASysCtl_setAnalogReference2P5()
// ASysCtl_setAnalogReference1P65()
//
//*****************************************************************************
#define ASYSCTL_VREFHIA  0x1U //!< VREFHIA
#define ASYSCTL_VREFHIB  0x2U //!< VREFHIB
#define ASYSCTL_VREFHIC  0x4U //!< VREFHIC

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
#define ASYSCTL_CMPHNMUX_SELECT_5 0x10U //!< CMPHNMUX select 5
#define ASYSCTL_CMPHNMUX_SELECT_6 0x20U //!< CMPHNMUX select 6
#define ASYSCTL_CMPHNMUX_SELECT_7 0x40U //!< CMPHNMUX select 7
#define ASYSCTL_CMPHNMUX_SELECT_8 0x80U //!< CMPHNMUX select 8
#define ASYSCTL_CMPHNMUX_SELECT_9 0x100U //!< CMPHNMUX select 9
#define ASYSCTL_CMPHNMUX_SELECT_10 0x200U //!< CMPHNMUX select 10
#define ASYSCTL_CMPHNMUX_SELECT_11 0x400U //!< CMPHNMUX select 11

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
#define ASYSCTL_CMPLNMUX_SELECT_5 0x10U //!< CMPLNMUX select 5
#define ASYSCTL_CMPLNMUX_SELECT_6 0x20U //!< CMPLNMUX select 6
#define ASYSCTL_CMPLNMUX_SELECT_7 0x40U //!< CMPLNMUX select 7
#define ASYSCTL_CMPLNMUX_SELECT_8 0x80U //!< CMPLNMUX select 8
#define ASYSCTL_CMPLNMUX_SELECT_9 0x100U //!< CMPLNMUX select 9
#define ASYSCTL_CMPLNMUX_SELECT_10 0x200U //!< CMPLNMUX select 10
#define ASYSCTL_CMPLNMUX_SELECT_11 0x400U //!< CMPLNMUX select 11

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
    ASYSCTL_CMPHPMUX_SELECT_4 = 9U, //!< CMPHPMUX select 4
    ASYSCTL_CMPHPMUX_SELECT_5 = 12U, //!< CMPHPMUX select 5
    ASYSCTL_CMPHPMUX_SELECT_6 = 15U, //!< CMPHPMUX select 6
    ASYSCTL_CMPHPMUX_SELECT_7 = 18U, //!< CMPHPMUX select 7
    ASYSCTL_CMPHPMUX_SELECT_8 = 21U, //!< CMPHPMUX select 8
    ASYSCTL_CMPHPMUX_SELECT_9 = 24U, //!< CMPHPMUX select 9
    ASYSCTL_CMPHPMUX_SELECT_10 = 27U, //!< CMPHPMUX select 10
    ASYSCTL_CMPHPMUX_SELECT_11 = 0U + 32U  //!< CMPHPMUX select 11
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
    ASYSCTL_CMPLPMUX_SELECT_4 = 9U, //!< CMPLPMUX select 4
    ASYSCTL_CMPLPMUX_SELECT_5 = 12U, //!< CMPLPMUX select 5
    ASYSCTL_CMPLPMUX_SELECT_6 = 15U, //!< CMPLPMUX select 6
    ASYSCTL_CMPLPMUX_SELECT_7 = 18U, //!< CMPLPMUX select 7
    ASYSCTL_CMPLPMUX_SELECT_8 = 21U, //!< CMPLPMUX select 8
    ASYSCTL_CMPLPMUX_SELECT_9 = 24U, //!< CMPLPMUX select 9
    ASYSCTL_CMPLPMUX_SELECT_10 = 27U, //!< CMPLPMUX select 10
    ASYSCTL_CMPLPMUX_SELECT_11 = 0U + 32U  //!< CMPLPMUX select 11
} ASysCtl_CMPLPMuxSelect;

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
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceInternal(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHIA |
                         ASYSCTL_VREFHIB |
                         ASYSCTL_VREFHIC
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
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_setAnalogReferenceExternal(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHIA |
                         ASYSCTL_VREFHIB |
                         ASYSCTL_VREFHIC
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
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference2P5(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHIA |
                         ASYSCTL_VREFHIB |
                         ASYSCTL_VREFHIC
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
//! - \b ASYSCTL_VREFHIA
//! - \b ASYSCTL_VREFHIB
//! - \b ASYSCTL_VREFHIC
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference1P65(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_VREFHIA |
                         ASYSCTL_VREFHIB |
                         ASYSCTL_VREFHIC
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
//! - \b ASYSCTL_CMPHNMUX_SELECT_5
//! - \b ASYSCTL_CMPHNMUX_SELECT_6
//! - \b ASYSCTL_CMPHNMUX_SELECT_7
//! - \b ASYSCTL_CMPHNMUX_SELECT_8
//! - \b ASYSCTL_CMPHNMUX_SELECT_9
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
//! - \b ASYSCTL_CMPHNMUX_SELECT_5
//! - \b ASYSCTL_CMPHNMUX_SELECT_6
//! - \b ASYSCTL_CMPHNMUX_SELECT_7
//! - \b ASYSCTL_CMPHNMUX_SELECT_8
//! - \b ASYSCTL_CMPHNMUX_SELECT_9
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
//! - \b ASYSCTL_CMPLNMUX_SELECT_5
//! - \b ASYSCTL_CMPLNMUX_SELECT_6
//! - \b ASYSCTL_CMPLNMUX_SELECT_7
//! - \b ASYSCTL_CMPLNMUX_SELECT_8
//! - \b ASYSCTL_CMPLNMUX_SELECT_9
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
//! - \b ASYSCTL_CMPLNMUX_SELECT_5
//! - \b ASYSCTL_CMPLNMUX_SELECT_6
//! - \b ASYSCTL_CMPLNMUX_SELECT_7
//! - \b ASYSCTL_CMPLNMUX_SELECT_8
//! - \b ASYSCTL_CMPLNMUX_SELECT_9
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
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPHPMUX_SELECT_1
//! - \b ASYSCTL_CMPHPMUX_SELECT_2
//! - \b ASYSCTL_CMPHPMUX_SELECT_3
//! - \b ASYSCTL_CMPHPMUX_SELECT_4
//! - \b ASYSCTL_CMPHPMUX_SELECT_5
//! - \b ASYSCTL_CMPHPMUX_SELECT_6
//! - \b ASYSCTL_CMPHPMUX_SELECT_7
//! - \b ASYSCTL_CMPHPMUX_SELECT_8
//! - \b ASYSCTL_CMPHPMUX_SELECT_9
//! - \b ASYSCTL_CMPHPMUX_SELECT_10
//! - \b ASYSCTL_CMPHPMUX_SELECT_11
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPHPMux(ASysCtl_CMPHPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 4U);

    EALLOW;

    //
    // Set the value for the appropriate Mux Select.
    //
    if((uint16_t)select > 32U)
    {
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL1) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL1) &
        ~((uint32_t)ASYSCTL_CMPHPMXSEL1_CMP11HPMXSEL_M << (uint32_t)select)) |
        (value << ((uint32_t)select - 32U));
    }
    else
    {
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) &
        ~((uint32_t)ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M << (uint32_t)select)) |
        (value << (uint32_t)select);
    }

    EDIS;
}

//*****************************************************************************
//
//! Select the value for CMPLPMXSEL.
//!
//! \param select is of type ASysCtl_CMPLPMuxSelect.
//! \param value is 0, 1, 2, 3, or 4.
//!
//! This function is used to write a value to one mux select at a time.
//! The parameter \e select can be one of the following values:
//!
//! - \b ASYSCTL_CMPLPMUX_SELECT_1
//! - \b ASYSCTL_CMPLPMUX_SELECT_2
//! - \b ASYSCTL_CMPLPMUX_SELECT_3
//! - \b ASYSCTL_CMPLPMUX_SELECT_4
//! - \b ASYSCTL_CMPLPMUX_SELECT_5
//! - \b ASYSCTL_CMPLPMUX_SELECT_6
//! - \b ASYSCTL_CMPLPMUX_SELECT_7
//! - \b ASYSCTL_CMPLPMUX_SELECT_8
//! - \b ASYSCTL_CMPLPMUX_SELECT_9
//!
//! \return None.
//
//*****************************************************************************
static inline void
ASysCtl_selectCMPLPMux(ASysCtl_CMPLPMuxSelect select, uint32_t value)
{
    ASSERT(value <= 4U);

    EALLOW;

    //
    // Set the value for the appropriate Mux Select.
    //
    if((uint16_t)select > 32U)
    {
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL1) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL1) &
        ~((uint32_t)ASYSCTL_CMPLPMXSEL1_CMP11LPMXSEL_S << (uint32_t)select)) |
        (value << ((uint32_t)select - 32U));
    }
    else
    {
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) &
        ~((uint32_t)ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select)) |
        (value << (uint32_t)select);
    }

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
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPHPMXSEL1;

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
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_CMPLPMXSEL1;

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
//! Enable loopback from DAC to ADCs.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCB
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
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCB
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
//! Configure AGPIO Filter control for right side pins.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_AGPIOFILTER_BYPASS - Filter bypass configuration(min ACQPS = 90ns)
//! - ASYSCTL_AGPIOFILTER_333OHM - 333Ohm filter setting (min ACQPS = 125ns)
//! - ASYSCTL_AGPIOFILTER_500OHM - 500 Ohm filter setting (min ACQPS = 160ns)
//! - ASYSCTL_AGPIOFILTER_1000OHM - 1KOhm filter setting (min ACQPS = 230ns)
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_setAGPIOFilterRight(uint32_t config)
{
    ASSERT(config <= 3U);

    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) &
             ~ASYSCTL_AGPIOFILTER_RIGHT_M) |
            (config << ASYSCTL_AGPIOFILTER_RIGHT_S);
    EDIS;
}

//*****************************************************************************
//
//! Configure AGPIO Filter control for bottom side pins.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_AGPIOFILTER_BYPASS - Filter bypass configuration(min ACQPS = 90ns)
//! - ASYSCTL_AGPIOFILTER_333OHM - 333Ohm filter setting (min ACQPS = 125ns)
//! - ASYSCTL_AGPIOFILTER_500OHM - 500 Ohm filter setting (min ACQPS = 160ns)
//! - ASYSCTL_AGPIOFILTER_1000OHM - 1KOhm filter setting (min ACQPS = 230ns)
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_setAGPIOFilterBottom(uint32_t config)
{
    ASSERT(config <= 3U);

    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) &
             ~ASYSCTL_AGPIOFILTER_BOTTOM_M) |
            (config << ASYSCTL_AGPIOFILTER_BOTTOM_S);
    EDIS;
}

//*****************************************************************************
//
//! Enable GPIO Input buffer (INENA control).
//!
//! \param pin can be 0, 23, 25, 31, 46 or 103
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_enableGPIOInputBuffer(uint32_t pin)
{
    ASSERT((pin == 0U)  || (pin == 23U) || (pin == 25U) ||
           (pin == 32U) || (pin == 46U) || (pin == 103U));

    uint16_t mask =
                    (pin == 0U)   ? ASYSCTL_GPIOINENACTRL_GPIO0   :
                    (pin == 23U)   ? ASYSCTL_GPIOINENACTRL_GPIO23   :
                    (pin == 25U)   ? ASYSCTL_GPIOINENACTRL_GPIO25   :
                    (pin == 31U)   ? ASYSCTL_GPIOINENACTRL_GPIO31   :
                    (pin == 46U)   ? ASYSCTL_GPIOINENACTRL_GPIO46   :
                    (pin == 103U)   ? ASYSCTL_GPIOINENACTRL_GPIO103   :
                    0U;

    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_GPIOINENACTRL) |= mask;
    EDIS;
}

//*****************************************************************************
//
//! Disable GPIO Input buffer (INENA control).
//!
//! \param pin can be 0, 23, 25, 31, 46 or 103
//!
//! \return None
//
//*****************************************************************************
static inline void ASysCtl_disableGPIOInputBuffer(uint32_t pin)
{
    ASSERT((pin == 0U)  || (pin == 23U) || (pin == 25U) ||
           (pin == 32U) || (pin == 46U) || (pin == 103U));

    uint16_t mask =
                    (pin == 0U)   ? ASYSCTL_GPIOINENACTRL_GPIO0   :
                    (pin == 23U)   ? ASYSCTL_GPIOINENACTRL_GPIO23   :
                    (pin == 25U)   ? ASYSCTL_GPIOINENACTRL_GPIO25   :
                    (pin == 31U)   ? ASYSCTL_GPIOINENACTRL_GPIO31   :
                    (pin == 46U)   ? ASYSCTL_GPIOINENACTRL_GPIO46   :
                    (pin == 103U)   ? ASYSCTL_GPIOINENACTRL_GPIO103   :
                    0U;

    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_GPIOINENACTRL) &= ~mask;
    EDIS;
}

//*****************************************************************************
//
//! Configure the ADCs for Global SW Trigger
//!
//! \param adcSelect can be bitwsie OR of the following :
//!
//! \return None
//
//*****************************************************************************
static inline void AsysCtl_configADCGlobalSOC(uint32_t adcSelect)
{
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCSOCFRCGBSEL) = adcSelect;
    EDIS;
}

//*****************************************************************************
//
//! Generate Global SOC force for specified SOCs
//!
//! \param socSelect can be bitwsie OR of the following :
//!
//! \return None
//
//*****************************************************************************
static inline void AsysCtl_forceADCGlobalSOC(uint32_t socSelect)
{
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCSOCFRCGB) = socSelect;
    EDIS;
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
