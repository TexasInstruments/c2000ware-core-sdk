//###########################################################################
//
// FILE:   pga.h
//
// TITLE:  C28x PGA driver.
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
    PGA_GAIN_1 = 0x0U,   //!< PGA gain value of 1
    PGA_GAIN_2 = 0x20U,  //!< PGA gain value of 2 or -1
    PGA_GAIN_4 = 0x40U,  //!< PGA gain value of 4 or -3
    PGA_GAIN_8 = 0x60U,  //!< PGA gain value of 8 or -7
    PGA_GAIN_16 = 0x80U, //!< PGA gain value of 16 or -15
    PGA_GAIN_32 = 0xA0U, //!< PGA gain value of 32 or -31
    PGA_GAIN_64 = 0xC0U  //!< PGA gain value of 64 or -63
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
    PGA_LOW_PASS_FILTER_DISABLED = 0U,
    //! Resistor value of 50 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_50_OHM = 2U,
    //! Resistor value of 100 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_100_OHM = 4U,
    //! Resistor value of 200 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_200_OHM = 6U,
    //! Resistor value of 400 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_400_OHM = 8U,
    //! Resistor value of 800 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_800_OHM = 10U
}PGA_LowPassResistorValue;

//*****************************************************************************
//
//! Values that can be passed to PGA_selectPMUXInput() as the \e
//! pmuxinput parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_PMUX_POS  = 0x00U,   //!< PGA_POS as non-inverting input
    PGA_PMUX_VSSA = 0x01U    //!< VSSA as non-inverting input
}PGA_PMUXInput;

//*****************************************************************************
//
//! Values that can be passed to PGA_selectNMUXInput() as the \e
//! nmuxinput parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_NMUX_RTOP = 0x00U,   //!< RTOP as inverting input
    PGA_NMUX_RTAP = 0x01U,   //!< RTAP as inverting input
    PGA_NMUX_NEG  = 0x02U    //!< PGA_NEG as inverting input
}PGA_NMUXInput;

//*****************************************************************************
//
//! Values that can be passed to PGA_selectMMUXInput() as the \e
//! mmuxinput parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_MMUX_NAKED_OPAMP               = 0x00U, //!< Naked op-amp mode
    PGA_MMUX_NON_INVERTING_GAIN_VSSA   = 0x01U, //!< VSSA as MMUX input for
                                                //!< Non-Inverting gain mode
    PGA_MMUX_INVERTING_GAIN_NEG        = 0x02U, //!< PGA_NEG as MMUX input for
                                                //!< Inverting gain mode
    PGA_MMUX_INVERTING_GAIN_NEG_SHARED = 0x03U //!< PGA_NEG_SHARED as MMUX input
                                               //!< for Inverting gain mode
}PGA_MMUXInput;

//*****************************************************************************
//
//! Values that can be passed to PGA_Chop() as the \e chop parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_CHOP_DISABLE                = 0x00U, //!< Chopping is disabled
    PGA_CHOP_REGULAR_INTOSC         = 0x01U, //!< Regular chopping using INTOSC
    PGA_CHOP_ADC_ASSISTED_ADCSOC    = 0x02U, //!< ADC assisted chop using ADCSOC
    PGA_CHOP_ADC_ASSISTED_EXTCTRL   = 0x03U  //!< ADC assisted chop using
                                            //!< PGA_CHOP_EXTCTRL
}PGA_Chop;


//*****************************************************************************
//
// Values that can be passed to PGA_lockRegisters() as the registerType
// parameter.
//
//*****************************************************************************
//! PGA Register PGACTL
//!
#define PGA_REGISTER_PGACTL                   PGA_LOCK_PGACTL
//! PGA Register MUXSEL
//!
#define PGA_REGISTER_MUXSEL                   PGA_LOCK_MUXSEL
//! PGA Register OFFSETTRIM
//!
#define PGA_REGISTER_OFFSETTRIM               PGA_LOCK_OFFSETTRIM

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
           (base == PGA3_BASE)
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
    HWREGH(base + PGA_O_CTL) =
                          ((HWREGH(base + PGA_O_CTL) &
                            ~((uint16_t)PGA_CTL_FILT_RES_SEL_M)) |
                           (uint16_t)resistorValue);
    EDIS;
}

//*****************************************************************************
//
//! Enable PGA output on the pin.
//!
//! \param base is the base address of the PGA module.
//!
//! This function send the PGA output to the pin.
//!
//! \return None.
//
//
//*****************************************************************************
static inline void PGA_enableOutput(uint32_t base)
{

    EALLOW;
    HWREGH(base + PGA_O_CTL) |= (uint16_t)PGA_CTL_PGA_OUTENABLE;
    EDIS;

}

//*****************************************************************************
//
//! Disable PGA output on the pin.
//!
//! \param base is the base address of the PGA module.
//!
//! This function prevents the PGA output to the pin.
//!
//! \return None.
//
//
//*****************************************************************************
static inline void PGA_disableOutput(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_CTL) &= ~((uint16_t)PGA_CTL_PGA_OUTENABLE);
    EDIS;

}

//*****************************************************************************
//
//! Enable PGA internal gain output on the pin.
//!
//! \param base is the base address of the PGA module.
//!
//! This function send the PGA internal gain output to the pin.
//!
//! \return None.
//
//
//*****************************************************************************
static inline void PGA_enableInternalGainOutput(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_CTL) |= (uint16_t)PGA_CTL_PGA_OUTEN_INTGAIN;
    EDIS;

}

//*****************************************************************************
//
//! Disable PGA internal gain output on the pin.
//!
//! \param base is the base address of the PGA module.
//!
//! This function prevents the PGA internal gain output to the pin.
//!
//! \return None.
//
//
//*****************************************************************************
static inline void PGA_disableInternalGainOutput(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_CTL) &= ~((uint16_t)PGA_CTL_PGA_OUTEN_INTGAIN);
    EDIS;

}

//*****************************************************************************
//
//! Enable external Chopping signal for PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function enables the external chopping signal for PGA.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_enableExternalChop(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_CTL) |= (uint16_t)PGA_CTL_CHOP_EXTCTRL;
    EDIS;

}

//*****************************************************************************
//
//! Disable external Chopping signal for PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function disables the external chopping signal for PGA.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_disableExternalChop(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_CTL) &= ~((uint16_t)PGA_CTL_CHOP_EXTCTRL);
    EDIS;

}

//*****************************************************************************
//
//! Selects PGA positive input Mux source.
//!
//! \param base is the base address of the PGA module.
//! \param pmuxinput is source of the Mux's positive input.
//!
//! This function selects the whether the positive input of the Mux will be
//! connected with PGA_POS pin or VSSA by \e pmuxinput. Valid values for
//! \e pmuxinput are:
//! - \e PGA_PMUX_POS - PGA_POS pin will be selected as non-inverting input.
//! - \e PGA_PMUX_VSSA - Positive pin will be grounded or VSSA will be connected
//! as non-inverting input.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_selectPMUXInput(uint32_t base, PGA_PMUXInput pmuxinput)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_MUXSEL) = (HWREGH(base + PGA_O_MUXSEL) &
                                    ~PGA_MUXSEL_PMUXSEL_M) | pmuxinput;
    EDIS;

}

//*****************************************************************************
//
//! Selects PGA negative input Mux source.
//!
//! \param base is the base address of the PGA module.
//! \param nmuxinput is source of the Mux's negative input.
//!
//! This function selects the source for the negative input of the Mux by
//! \e nmuxinput. Valid values for \e nmuxinput are:
//! - \e PGA_NMUX_RTOP - RTOP(inter gain resistor tap point) will be selected
//! as inverting input
//! - \e PGA_NMUX_RTAP - RTAP(pre gain resistor tap point) will be selected as
//! inverting input
//! - \e PGA_NMUX_NEG - PGA_NEG pin will be selected as inverting input.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_selectNMUXInput(uint32_t base, PGA_NMUXInput nmuxinput)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_MUXSEL) =
                        (HWREGH(base + PGA_O_MUXSEL) & ~(PGA_MUXSEL_NMUXSEL_M)) |
                        (nmuxinput << PGA_MUXSEL_NMUXSEL_S);
    EDIS;

}

//*****************************************************************************
//
//! Selects input source of the M-Mux.
//!
//! \param base is the base address of the PGA module.
//! \param mmuxinput is source of the Mux's negative input.
//!
//! This function selects the input source for the M-Mux by \e mmuxinput.
//! Valid values for \e mmuxinput are:
//! - \e PGA_MMUX_NAKED_OPAMP - VSSA will be connected as M-Mux input source
//! - \e PGA_MMUX_NON_INVERTING_GAIN_VSSA - VSSA_RESARRAY will be connected
//! to M-Mux input for non-inverting gain settings
//! - \e PGA_MMUX_INVERTING_GAIN_NEG - PGA_NEG pin will be connected as M-Mux
//! input source for inverting gain settings
//! - \e PGA_MMUX_INVERTING_GAIN_NEG_SHARED - PGA_NEG_SHARED will be connected
//! as M-Mux input source for inverting gain settings
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_selectMMUXInput(uint32_t base, PGA_MMUXInput mmuxinput)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_MUXSEL) =
                        (HWREGH(base + PGA_O_MUXSEL) & ~(PGA_MUXSEL_MMUXSEL_M)) |
                        (mmuxinput << PGA_MUXSEL_MMUXSEL_S);
    EDIS;

}

//*****************************************************************************
//
//! Configures feedback to PGA negative input pin.
//!
//! \param base is the base address of the PGA module.
//!
//! This function configures feedback to PGA negative input pin and connects
//! PGA_NEG and PGA inverting input.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_configurefeedbackOnPin(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_MUXSEL) |= (uint16_t)PGA_MUXSEL_PGA_FBONPIN;
    EDIS;

}

//*****************************************************************************
//
//! Selects PGA chop mode.
//!
//! \param base is the base address of the PGA module.
//! \param chop is the chop mode.
//!
//! This function selects the chopping mode to reduce the input offset to
//! a very small number (~uV level).
//!
//! \e chop is the chop mode to be selected. Valid values for this parameter
//! can be referred from the enum \e PGA_Chop.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_chop(uint32_t base, PGA_Chop chop)
{
    ASSERT(PGA_isBaseValid(base));

    EALLOW;
    HWREGH(base + PGA_O_MUXSEL) =
                       (HWREGH(base + PGA_O_MUXSEL) & ~(PGA_MUXSEL_PGA_CHOP_M)) |
                       (chop << PGA_MUXSEL_PGA_CHOP_S);
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
//! PGA_REGISTER_PGACTL, PGA_REGISTER_MUXSEL and PGA_REGISTER_OFFSETTRIM
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_lockRegisters(uint32_t base, uint16_t registerType)
{

    ASSERT(PGA_isBaseValid(base));
    ASSERT(registerType < 0xFU);

    //
    // Write to the appropriate bits of PGALOCK register bits
    //
    EALLOW;
    HWREGH(base + PGA_O_LOCK) |= registerType;
    EDIS;
}

//*****************************************************************************
//
//! Configures the offset trim for NMOS pair of the desired PGA instance
//!
//! \param base is the base address of the PGA module.
//!
//! This function loads the offset trims for NMOS pair of the desired
//! PGA instance.
//!
//! \return None.
//
//*****************************************************************************
extern void
PGA_setOffsetTrimNMOS(uint32_t base);

//*****************************************************************************
//
//! Configures the offset trim for PMOS pair of the desired PGA instance
//!
//! \param base is the base address of the PGA module.
//!
//! This function loads the offset trims for PMOS pair of the desired
//! PGA instance.
//!
//! \return None.
//
//*****************************************************************************
extern void
PGA_setOffsetTrimPMOS(uint32_t base);


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
