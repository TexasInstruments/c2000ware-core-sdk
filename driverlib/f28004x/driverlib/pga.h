//###########################################################################
//
// FILE:   pga.h
//
// TITLE:  C28x PGA driver.
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

#ifndef PGA_H
#define PGA_H

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
//! \addtogroup pga_api PGA
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_pga.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
//! Values that can be passed to PGA_setGain() as the \e gainValue parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_GAIN_3 = 0x0,   //!< PGA gain value of 3
    PGA_GAIN_6 = 0x20,  //!< PGA gain value of 6
    PGA_GAIN_12 = 0x40, //!< PGA gain value of 12
    PGA_GAIN_24 = 0x60  //!< PGA gain value of 24
}PGA_GainValue;

//*****************************************************************************
//
//! Values that can be passed to PGA_setFilterResistor() as the \e
//! resistorValue parameter.
//
//*****************************************************************************
typedef enum
{
    //! Low pass filter disabled (open circuit)
    PGA_LOW_PASS_FILTER_DISABLED = 0,
    //! Resistor value of 200 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_200_OHM = 2,
    //! Resistor value of 160 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_160_OHM = 4,
    //! Resistor value of 130 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_130_OHM = 6,
    //! Resistor value of 100 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_100_OHM = 8,
    //! Resistor value of 80 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_80_OHM = 10,
    //! Resistor value of 50 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_50_OHM = 12
}PGA_LowPassResistorValue;



//*****************************************************************************
//
// Values that can be passed to PGA_lockRegisters() as the registerType
// parameter.
//
//*****************************************************************************
//! PGA Register PGACTL
//!
#define PGA_REGISTER_PGACTL                   PGA_LOCK_PGACTL
//! PGA Register GAIN3TRIM
//!
#define PGA_REGISTER_GAIN3TRIM                PGA_LOCK_PGAGAIN3TRIM
//! PGA Register GAIN6TRIM
//!
#define PGA_REGISTER_GAIN6TRIM                PGA_LOCK_PGAGAIN6TRIM
//! PGA Register GAIN12TRIM
//!
#define PGA_REGISTER_GAIN12TRIM               PGA_LOCK_PGAGAIN12TRIM
//! PGA Register GAIN24TRIM
//!
#define PGA_REGISTER_GAIN24TRIM               PGA_LOCK_PGAGAIN24TRIM

//*****************************************************************************
//
//! \internal
//! Checks PGA wrapper base address.
//!
//! \param base specifies the PGA wrapper base address.
//!
//! This function determines if a PGA wrapper base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PGA_isBaseValid(uint32_t base)
{
    return(
           (base == PGA1_BASE) ||
           (base == PGA2_BASE) ||
           (base == PGA3_BASE) ||
           (base == PGA4_BASE) ||
           (base == PGA5_BASE) ||
           (base == PGA6_BASE) ||
           (base == PGA7_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function enables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_enable(uint32_t base)
{
   ASSERT(PGA_isBaseValid(base));

   //
   // Set PGAEN bit
   //
   EALLOW;
   HWREG(base + PGA_O_CTL) |= (uint32_t)PGA_CTL_PGAEN;
   EDIS;
}

//*****************************************************************************
//
//! Disables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function disables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_disable(uint32_t base)
{
   ASSERT(PGA_isBaseValid(base));

   //
   // Clear PGAEN bit
   //
   EALLOW;
   HWREG(base + PGA_O_CTL) &= ~((uint32_t)PGA_CTL_PGAEN);
   EDIS;
}

//*****************************************************************************
//
//! Sets PGA gain value.
//!
//! \param base is the base address of the PGA module.
//! \param gainValue is the PGA gain value.
//!
//! This function sets the PGA gain value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setGain(uint32_t base, PGA_GainValue gainValue)
{
    ASSERT(PGA_isBaseValid(base));

    //
    // Write to the GAIN bits
    //
    EALLOW;
    HWREG(base + PGA_O_CTL) = ((HWREG(base + PGA_O_CTL) &
                                ~((uint32_t)PGA_CTL_GAIN_M)) |
                               (uint16_t)gainValue);
    EDIS;
}

//*****************************************************************************
//
//! Sets PGA output filter resistor value.
//!
//! \param base is the base address of the PGA module.
//! \param resistorValue is the PGA output resistor value.
//!
//! This function sets the resistor value for the PGA output low pass RC
//! filter. The resistance for the RC low pass filter is provided within the
//! microprocessor and is determined by the value of resistorValue. The
//! capacitor, however, has to be connected outside the microprocessor.
//!
//! \b Note: Setting a value of PGA_LOW_PASS_FILTER_RESISTOR_0_OHM will
//!          disable the internal resistance value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setFilterResistor(uint32_t base,
                                       PGA_LowPassResistorValue resistorValue)
{
    ASSERT(PGA_isBaseValid(base));

    //
    // Write to the FILTRESSEL bits
    //
    EALLOW;
    HWREG(base + PGA_O_CTL) =
                          ((HWREG(base + PGA_O_CTL) &
                            ~((uint32_t)PGA_CTL_FILTRESSEL_M)) |
                           (uint16_t)resistorValue);
    EDIS;
}


//*****************************************************************************
//
//! Returns the PGA revision number.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA revision number.
//!
//! \return Returns PGA revision.
//
//*****************************************************************************
static inline uint16_t PGA_getPGARevision(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    //
    // return PGA revision number
    //
    return((uint16_t)(HWREGH(base + PGA_O_TYPE) & PGA_TYPE_REV_M));
}

//*****************************************************************************
//
//! Returns the PGA Type.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA Type number.
//!
//! \return Returns PGA type.
//
//*****************************************************************************
static inline uint16_t PGA_getPGAType(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    //
    // return PGA Type number
    //
    return((uint16_t)(HWREGH(base + PGA_O_TYPE) >> PGA_TYPE_TYPE_S));
}

//*****************************************************************************
//
//! Locks PGA registers.
//!
//! \param base is the base address of the PGA module.
//! \param registerType is the PGA register to be locked.
//!
//! This function locks the PGA registers specified by registerType. Valid
//! values for registerType are:
//! PGA_REGISTER_PGACTL, PGA_REGISTER_GAINxTRIM, where x is
//! 3,6,12 or 24.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_lockRegisters(uint32_t base, uint16_t registerType)
{

    ASSERT(PGA_isBaseValid(base));
    ASSERT((registerType < 0x3DU) &&
           ((registerType & 0x2U) == 0U));

    //
    // Write to the appropriate bits of PGALOCK register bits
    //
    EALLOW;
    HWREGH(base + PGA_O_LOCK) |= registerType;
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

#endif // PGA_H
