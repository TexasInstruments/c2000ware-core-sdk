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
#include "sysctl.h"

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
    ASYSCTL_CMPHPMUX_SELECT_6 = 16U, //!< CMPHPMUX select 6
    ASYSCTL_CMPHPMUX_SELECT_7 = 19U  //!< CMPHPMUX select 7
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
    ASYSCTL_CMPLPMUX_SELECT_6 = 16U, //!< CMPLPMUX select 6
    ASYSCTL_CMPLPMUX_SELECT_7 = 19U  //!< CMPLPMUX select 7
} ASysCtl_CMPLPMuxSelect;

//*****************************************************************************
//
//! ASysCtl_getInductorFaultStatus &  ASysCtl_getSwitchSequenceStatus used
//! for function ASysCtl_enableDCDC().
//
//*****************************************************************************
static inline bool ASysCtl_getInductorFaultStatus(void);
static inline bool ASysCtl_getSwitchSequenceStatus(void);

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
//! Enable DC-DC.
//!
//! This function enables the DC-DC and checks if the enable was successful
//! when switching from the VREG to the DC-DC .
//!
//! \return Return value \b true indicates that the DC-DC enable was
//! successful when switching from the VREG to the DC-DC . Return
//! value of \b false indicates that the DC-DC enable with switch failed.
//!
//! \note The internal DC-DC regulator is disabled by default. To use this
//! supply, the device must power up initially with the internal LDO (VREG)
//! and then transition to the internal DC-DC regulator.
//
//*****************************************************************************
static inline bool ASysCtl_enableDCDC(void)
{
    EALLOW;

    //
    // Write 1 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) |= ASYSCTL_DCDCCTL_DCDCEN;

    EDIS;

    //
    // Wait till the transition from VREG to DC-DC was successful
    //
    while(ASysCtl_getSwitchSequenceStatus() == false);

    //
    // Check if the external inductor connected to the DC-DC is functional
    //
    if(ASysCtl_getInductorFaultStatus() == true)
    {
        //
        // Delay 80us for the DC-DC regulator output to settle
        //
        SysCtl_delay(1599U);

        //
        // The DC-DC enable was successful when switching
        // from the VREG to the DC-DC
        //
        return(true);
    }
    else
    {
        //
        // The DC-DC enable was unsuccessful when switching
        // from the VREG to the DC-DC
        //
        return(false);
    }
}

//*****************************************************************************
//
//! Disable DC-DC.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_disableDCDC(void)
{
    EALLOW;

    //
    // Write 0 to enable bit.
    //
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCCTL) &= ~ASYSCTL_DCDCCTL_DCDCEN;

   //
   // Delay 80us for the internal LDO (VREG) to power back up
   //
   SysCtl_delay(1599U);

    EDIS;
}

//*****************************************************************************
//
//! Gets the inductor status.
//!
//! This function returns the inductor status.
//!
//! \return Return value \b true indicates that the external inductor connected
//! to DC-DC is functional.  Return value of \b false indicates it is faulty or
//! not connected.
//
//*****************************************************************************
static inline bool ASysCtl_getInductorFaultStatus(void)
{
    //
    // Return the status the INDDETECT bit.
    //
    return((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) &
            ASYSCTL_DCDCSTS_INDDETECT) == ASYSCTL_DCDCSTS_INDDETECT);
}

//*****************************************************************************
//
//! Gets the Switch Sequence Status.
//!
//! This function returns the Switch Sequence Status.
//!
//! \return Return value \b false indicates that the switch to DC-DC is not
//! complete. Return value of \b true indicates it is complete.
//
//*****************************************************************************
static inline bool ASysCtl_getSwitchSequenceStatus(void)
{
    //
    // Return the status the SWSEQDONE bit.
    //
    return((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_DCDCSTS) &
            ASYSCTL_DCDCSTS_SWSEQDONE) == ASYSCTL_DCDCSTS_SWSEQDONE);
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
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) =
        (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) &
        ~((uint32_t)ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M << (uint32_t)select)) |
        (value << (uint32_t)select);

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
//! Locks the DCDC control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockDCDC(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_DCDCCTL;

    EDIS;
}

//*****************************************************************************
//
//! Locks the ADCIN control register.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_lockPGAADCINMux(void)
{
    EALLOW;

    //
    // Write a 1 to the lock bit in the LOCK register.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) |= ASYSCTL_LOCK_ADCINMXSEL;

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
