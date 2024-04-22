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
// ASysCtl_setVrefHiReferenceINTREF()
// ASysCtl_setVrefLoReferenceVREFLO()
// ASysCtl_setAnalogReferenceInternal()
//
//*****************************************************************************
#define ASYSCTL_ANAREF_INTREF_ADCA  0x3U //!< INTREFA
#define ASYSCTL_ANAREF_INTREF_ADCB  0xCU //!< INTREFB
#define ASYSCTL_ANAREF_INTREF_ADCC  0x30U //!< INTREFC
#define ASYSCTL_ANAREF_INTREF_ADCD  0xC0U //!< INTREFD
#define ASYSCTL_ANAREF_INTREF_ADCE  0x300U //!< INTREFE

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setVrefHiReferenceVREFHI()
// ASysCtl_setAnalogReferenceExternal()
//
//*****************************************************************************
#define ASYSCTL_ANAREF_VREFHI_ADCA  0x1U   // VREFHIA
#define ASYSCTL_ANAREF_VREFHI_ADCB  0x4U   // VREFHIB
#define ASYSCTL_ANAREF_VREFHI_ADCC  0x10U  // VREFHIC
#define ASYSCTL_ANAREF_VREFHI_ADCD  0x40U  // VREFHID
#define ASYSCTL_ANAREF_VREFHI_ADCE  0x100U // VREFHIE

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setVrefHiReferenceVDDA()
// ASysCtl_setVrefLoiReferenceVSSA()
// ASysCtl_setAnalogReferenceVDDA()
//
//*****************************************************************************
#define ASYSCTL_ANAREF_VDDA_ADCA  0x3U //!< VDDAA
#define ASYSCTL_ANAREF_VDDA_ADCB  0xCU //!< VDDAB
#define ASYSCTL_ANAREF_VDDA_ADCC  0x30U //!< VDDAC
#define ASYSCTL_ANAREF_VDDA_ADCD  0xC0U //!< VDDAD
#define ASYSCTL_ANAREF_VDDA_ADCE  0x300U //!< VDDAE

//*****************************************************************************
//
// Defines used for setting AnalogReference functions.
// ASysCtl_setAnalogReference2P5()
// ASysCtl_setAnalogReference1P65()
//
//*****************************************************************************
#define ASYSCTL_ANAREF_ADCA  1U  // ANAREFA
#define ASYSCTL_ANAREF_ADCB  2U  // ANAREFB
#define ASYSCTL_ANAREF_ADCC  4U  // ANAREFC
#define ASYSCTL_ANAREF_ADCD  8U  // ANAREFD
#define ASYSCTL_ANAREF_ADCE  16U // ANAREFE

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
    ASYSCTL_TEST_NODE_VDDA                = 2U,  //!< VDDA voltage
    ASYSCTL_TEST_NODE_VSSA                = 3U,  //!< VSSA - Analog ground pin
    ASYSCTL_TEST_NODE_VREFLO              = 4U,  //!< VREFLO pin voltage
    ASYSCTL_TEST_NODE_CDAC1H              = 5U,  //!< CMPSS1 High DAC output
    ASYSCTL_TEST_NODE_CDAC1L              = 6U,  //!< CMPSS1 Low DAC output
    ASYSCTL_TEST_NODE_CDAC2H              = 7U,  //!< CMPSS2 High DAC output
    ASYSCTL_TEST_NODE_CDAC2L              = 8U,  //!< CMPSS2 Low DAC output
    ASYSCTL_TEST_NODE_CDAC3H              = 9U,  //!< CMPSS3 High DAC output
    ASYSCTL_TEST_NODE_CDAC3L              = 10U, //!< CMPSS3 Low DAC output
    ASYSCTL_TEST_NODE_CDAC4H              = 11U, //!< CMPSS4 High DAC output
    ASYSCTL_TEST_NODE_CDAC4L              = 12U, //!< CMPSS4 Low DAC output
    ASYSCTL_TEST_NODE_ENZ_CALIB_GAIN_3P3V = 29U //!< All ADCs are placed in gain
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
//! - \b ASYSCTL_ANAREF_INTREF_ADCA
//! - \b ASYSCTL_ANAREF_INTREF_ADCB
//! - \b ASYSCTL_ANAREF_INTREF_ADCC
//! - \b ASYSCTL_ANAREF_INTREF_ADCD
//! - \b ASYSCTL_ANAREF_INTREF_ADCE
//!
//! \note If any one ADC chooses INTREF then VREFHI option will become invalid
//! for all other ADCs.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setVrefHiReferenceINTREF(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_INTREF_ADCA |
                         ASYSCTL_ANAREF_INTREF_ADCB |
                         ASYSCTL_ANAREF_INTREF_ADCC |
                         ASYSCTL_ANAREF_INTREF_ADCD |
                         ASYSCTL_ANAREF_INTREF_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &=
                                                ~((uint16_t)reference);

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to external VREFHI.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_VREFHI_ADCA
//! - \b ASYSCTL_ANAREF_VREFHI_ADCB
//! - \b ASYSCTL_ANAREF_VREFHI_ADCC
//! - \b ASYSCTL_ANAREF_VREFHI_ADCD
//! - \b ASYSCTL_ANAREF_VREFHI_ADCE
//!
//! \note If any one ADC chooses INTREF then VREFHI option will become invalid
//! for all other ADCs.
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setVrefHiReferenceVREFHI(uint16_t reference)
{
    uint16_t refMask;

    ASSERT((reference & (
                         ASYSCTL_ANAREF_VREFHI_ADCA |
                         ASYSCTL_ANAREF_VREFHI_ADCB |
                         ASYSCTL_ANAREF_VREFHI_ADCC |
                         ASYSCTL_ANAREF_VREFHI_ADCD |
                         ASYSCTL_ANAREF_VREFHI_ADCE
                        )) == reference);

    refMask = (reference << 1) | reference;

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) =
                            (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &
                             ~refMask) | reference;

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to VDDA.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_VDDA_ADCA
//! - \b ASYSCTL_ANAREF_VDDA_ADCB
//! - \b ASYSCTL_ANAREF_VDDA_ADCC
//! - \b ASYSCTL_ANAREF_VDDA_ADCD
//! - \b ASYSCTL_ANAREF_VDDA_ADCE
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setVrefHiReferenceVDDA(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_VDDA_ADCA |
                         ASYSCTL_ANAREF_VDDA_ADCB |
                         ASYSCTL_ANAREF_VDDA_ADCC |
                         ASYSCTL_ANAREF_VDDA_ADCD |
                         ASYSCTL_ANAREF_VDDA_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |= reference;

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
//! - \b ASYSCTL_ANAREF_ADCA
//! - \b ASYSCTL_ANAREF_ADCB
//! - \b ASYSCTL_ANAREF_ADCC
//! - \b ASYSCTL_ANAREF_ADCD
//! - \b ASYSCTL_ANAREF_ADCE
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference2P5(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_ADCA |
                         ASYSCTL_ANAREF_ADCB |
                         ASYSCTL_ANAREF_ADCC |
                         ASYSCTL_ANAREF_ADCD |
                         ASYSCTL_ANAREF_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &= ~(reference << 10U);

    EDIS;
}

//*****************************************************************************
//
//! Set the internal and external analog voltage reference selection to 1.65V.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_ADCA
//! - \b ASYSCTL_ANAREF_ADCB
//! - \b ASYSCTL_ANAREF_ADCC
//! - \b ASYSCTL_ANAREF_ADCD
//! - \b ASYSCTL_ANAREF_ADCE
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setAnalogReference1P65(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_ADCA |
                         ASYSCTL_ANAREF_ADCB |
                         ASYSCTL_ANAREF_ADCC |
                         ASYSCTL_ANAREF_ADCD |
                         ASYSCTL_ANAREF_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Voltage Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |= (reference << 10U);

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to VREFLO.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_INTREF_ADCA
//! - \b ASYSCTL_ANAREF_INTREF_ADCB
//! - \b ASYSCTL_ANAREF_INTREF_ADCC
//! - \b ASYSCTL_ANAREF_INTREF_ADCD
//! - \b ASYSCTL_ANAREF_INTREF_ADCE
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setVrefLoReferenceVREFLO(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_INTREF_ADCA |
                         ASYSCTL_ANAREF_INTREF_ADCB |
                         ASYSCTL_ANAREF_INTREF_ADCC |
                         ASYSCTL_ANAREF_INTREF_ADCD |
                         ASYSCTL_ANAREF_INTREF_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) &=
                                                ~((uint16_t)reference);

    EDIS;
}

//*****************************************************************************
//
//! Set the analog voltage reference selection to VSSA.
//!
//! \param reference is the analog reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_VDDA_ADCA
//! - \b ASYSCTL_ANAREF_VDDA_ADCB
//! - \b ASYSCTL_ANAREF_VDDA_ADCC
//! - \b ASYSCTL_ANAREF_VDDA_ADCD
//! - \b ASYSCTL_ANAREF_VDDA_ADCE
//!
//! \return None.
//
//*****************************************************************************
static inline void ASysCtl_setVrefLoReferenceVSSA(uint16_t reference)
{
    ASSERT((reference & (
                         ASYSCTL_ANAREF_VDDA_ADCA |
                         ASYSCTL_ANAREF_VDDA_ADCB |
                         ASYSCTL_ANAREF_VDDA_ADCC |
                         ASYSCTL_ANAREF_VDDA_ADCD |
                         ASYSCTL_ANAREF_VDDA_ADCE
                        )) == reference);

    EALLOW;

    //
    // Write selection to the Analog Internal Reference Select bit.
    //
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) |= reference;

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
//! Enable loopback from DAC to ADCs.
//!
//! \param config can be bitwise OR of the following values:
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCB
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCD
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCE
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
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCD
//! - ASYSCTL_ADCDACLOOPBACK_ENLB2ADCE
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
//! Configure AGPIO Filter control for Group1 side pins
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
static inline void ASysCtl_setAGPIOFilterGroup1(uint32_t config)
{
    ASSERT(config <= 3U);

    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) &
             ~ASYSCTL_AGPIOFILTER_GROUP1_M) |
            (config << ASYSCTL_AGPIOFILTER_GROUP1_S);
    EDIS;
}

//*****************************************************************************
//
//! Configure AGPIO Filter control for Group2 side pins.
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
static inline void ASysCtl_setAGPIOFilterGroup2(uint32_t config)
{
    ASSERT(config <= 3U);

    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) =
            (HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_AGPIOFILTER) &
             ~ASYSCTL_AGPIOFILTER_GROUP2_M) |
            (config << ASYSCTL_AGPIOFILTER_GROUP2_S);
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
                    (pin == 20U)   ? ASYSCTL_GPIOINENACTRL_GPIO20   :
                    (pin == 21U)   ? ASYSCTL_GPIOINENACTRL_GPIO21   :
                    (pin == 62U)   ? ASYSCTL_GPIOINENACTRL_GPIO62   :
                    (pin == 63U)   ? ASYSCTL_GPIOINENACTRL_GPIO63   :
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
                    (pin == 20U)   ? ASYSCTL_GPIOINENACTRL_GPIO20   :
                    (pin == 21U)   ? ASYSCTL_GPIOINENACTRL_GPIO21   :
                    (pin == 62U)   ? ASYSCTL_GPIOINENACTRL_GPIO62   :
                    (pin == 63U)   ? ASYSCTL_GPIOINENACTRL_GPIO63   :
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
//! Set the analog voltage reference selection to internal.
//!
//! \param reference is the analog reference.
//!
//! This function sets the vrefhi and vreflo reference voltage for internal
//! reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_INTREF_ADCA
//! - \b ASYSCTL_ANAREF_INTREF_ADCB
//! - \b ASYSCTL_ANAREF_INTREF_ADCC
//! - \b ASYSCTL_ANAREF_INTREF_ADCD
//! - \b ASYSCTL_ANAREF_INTREF_ADCE
//!
//! \note If any one ADC chooses INTREF then VREFHI option will become invalid
//! for all other ADCs.
//!
//! \return None.
//
//*****************************************************************************
extern void
ASysCtl_setAnalogReferenceInternal(uint16_t reference);

//*****************************************************************************
//
//! Set the analog voltage reference selection to external VREFHI.
//!
//! \param reference is the analog reference.
//!
//! This function sets the VREFHI and VREFLO reference voltage for the external
//! VREFHI reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_VREFHI_ADCA
//! - \b ASYSCTL_ANAREF_VREFHI_ADCB
//! - \b ASYSCTL_ANAREF_VREFHI_ADCC
//! - \b ASYSCTL_ANAREF_VREFHI_ADCD
//! - \b ASYSCTL_ANAREF_VREFHI_ADCE
//!
//! \note If any one ADC chooses INTREF then VREFHI option will become invalid
//! for all other ADCs.
//!
//! \return None.
//
//*****************************************************************************
extern void
ASysCtl_setAnalogReferenceExternal(uint16_t reference);

//*****************************************************************************
//
//! Set the analog voltage reference selection to VDDA.
//!
//! \param reference is the analog reference.
//!
//! This function sets the VREFHI and VREFLO reference voltage for VDDA
//! reference.
//!
//! The parameter \e reference can be a combination of the following values:
//!
//! - \b ASYSCTL_ANAREF_VDDA_ADCA
//! - \b ASYSCTL_ANAREF_VDDA_ADCB
//! - \b ASYSCTL_ANAREF_VDDA_ADCC
//! - \b ASYSCTL_ANAREF_VDDA_ADCD
//! - \b ASYSCTL_ANAREF_VDDA_ADCE
//!
//! \return None.
//
//*****************************************************************************
extern void
ASysCtl_setAnalogReferenceVDDA(uint16_t reference);


typedef enum 
{
    ASYSCTL_IO_DRVSEL_GPIO2,
    ASYSCTL_IO_DRVSEL_GPIO3,
    ASYSCTL_IO_DRVSEL_GPIO9,
    ASYSCTL_IO_DRVSEL_GPIO32
} AsysCtl_IO_Drvsel_GPIO;
//*****************************************************************************
//
//! Set the IO Drive strength of PMBUS IP as 12 mA
//!
//! \param gpioNumber the GPIO number to toggle
//!
//! This function sets the drive current for PMBUS module as 12 mA. The default current is 4mA.
//!
//! The parameter \e gpioNumber can be a combination of the following values:
//! - \b ASYSCTL_IO_DRVSEL_GPIO2
//! - \b ASYSCTL_IO_DRVSEL_GPIO3
//! - \b ASYSCTL_IO_DRVSEL_GPIO9
//! - \b ASYSCTL_IO_DRVSEL_GPIO32
//! 
//! \return None.
//
//*****************************************************************************
static inline void AsysCtl_setDriveStrength(AsysCtl_IO_Drvsel_GPIO gpioNumber)
{
    uint16_t gpio = 0;
    switch (gpioNumber)
    {
        case ASYSCTL_IO_DRVSEL_GPIO2:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO2;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO3:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO3;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO9:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO9;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO32:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO32;
        break;
    }
    ASSERT(gpio > 0U);
    EALLOW;
    HWREG(ASYSCTL_O_IO_DRVSEL) |= gpio;
    EDIS;
}

static inline void AsysCtl_clearDriveStrength(AsysCtl_IO_Drvsel_GPIO gpioNumber)
{
    uint16_t gpio = 0;
    switch (gpioNumber)
    {
        case ASYSCTL_IO_DRVSEL_GPIO2:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO2;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO3:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO3;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO9:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO9;
        break;

        case ASYSCTL_IO_DRVSEL_GPIO32:
        gpio = ASYSCTL_IO_DRVSEL_DRVSEL_GPIO32;
        break;
    }
    ASSERT(gpio > 0U);
    EALLOW;
    HWREG(ASYSCTL_O_IO_DRVSEL) &= ~(gpio);
    EDIS;
}

typedef enum 
{
    ASYSCTL_IO_MODESEL_GPIO2,
    ASYSCTL_IO_MODESEL_GPIO3,
    ASYSCTL_IO_MODESEL_GPIO9,
    ASYSCTL_IO_MODESEL_GPIO32
} AsysCtl_IO_Modesel_GPIO;
//*****************************************************************************
//
//! Set the IO mode of PMBUS IP as 1.35 Volts 
//!
//! \param gpioNumber the GPIO number to toggle
//!
//! This function sets the IO Mode for PMBUS module as 1.35v. The default current is 3.3v.
//!
//! The parameter \e gpioNumber can be a combination of the following values:
//! - \b ASYSCTL_IO_MODESEl_GPIO2
//! - \b ASYSCTL_IO_MODESEl_GPIO3
//! - \b ASYSCTL_IO_MODESEl_GPIO9
//! - \b ASYSCTL_IO_MODESEl_GPIO32
//! 
//! \return None.
//
//*****************************************************************************
static inline void AsysCtl_setDriveMode(AsysCtl_IO_Modesel_GPIO gpioNumber)
{
    uint16_t gpio = 0;
    switch (gpioNumber)
    {
        case ASYSCTL_IO_MODESEL_GPIO2:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO2;
        break;

        case ASYSCTL_IO_MODESEL_GPIO3:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO3;
        break;

        case ASYSCTL_IO_MODESEL_GPIO9:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO9;
        break;

        case ASYSCTL_IO_MODESEL_GPIO32:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO32;
        break;
    }
    ASSERT(gpio > 0U);
    EALLOW;
    HWREG(ASYSCTL_O_IO_MODESEL) |= gpio;
    EDIS;
}

static inline void AsysCtl_clearDriveMode(AsysCtl_IO_Modesel_GPIO gpioNumber)
{
    uint16_t gpio = 0;
    switch (gpioNumber)
    {
        case ASYSCTL_IO_MODESEL_GPIO2:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO2;
        break;

        case ASYSCTL_IO_MODESEL_GPIO3:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO3;
        break;

        case ASYSCTL_IO_MODESEL_GPIO9:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO9;
        break;

        case ASYSCTL_IO_MODESEL_GPIO32:
        gpio = ASYSCTL_IO_MODESEL_MODESEL_GPIO32;
        break;
    }
    ASSERT(gpio > 0U);
    EALLOW;
    HWREG(ASYSCTL_O_IO_MODESEL) &= ~(gpio);
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
