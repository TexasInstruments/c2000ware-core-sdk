//###########################################################################
//
// FILE:   sdfm.h
//
// TITLE:   C28x SDFM Driver
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#ifndef SDFM_H
#define SDFM_H

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
//! \addtogroup sdfm_api SDFM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_sdfm.h"
#include "inc/hw_memmap.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//! Macro to get the low threshold
//!
#define SDFM_GET_LOW_THRESHOLD(C)    ((uint16_t)(C))

//! Macro to get the high threshold
//!
#define SDFM_GET_HIGH_THRESHOLD(C)   ((uint16_t)((uint32_t)(C) >> 16U))


//! Macro to convert comparator over sampling ratio to acceptable bit location
//!
#define SDFM_SET_OSR(X)         (((X) - 1U) << 8U)
//! Macro to convert the data shift bit values to acceptable bit location
//!
#define SDFM_SHIFT_VALUE(X)     ((X) << 2U)

//! Macro to combine high threshold and low threshold values
//!
#define SDFM_THRESHOLD(H, L)     ((((uint32_t)(H)) << 16U) | (L))

//! Macro to set the FIFO level to acceptable bit location
//!
#define SDFM_SET_FIFO_LEVEL(X)  ((X) << 7U)

//! Macro to set and enable the zero cross threshold value.
//!
#define SDFM_SET_ZERO_CROSS_THRESH_VALUE(X) (0x8000 | (X))

//! Macros to enable or disable filter.
//!
#define SDFM_FILTER_DISABLE     0x0U
#define SDFM_FILTER_ENABLE      0x2U

//*****************************************************************************
//
//! Values that can be returned from SDFM_getThresholdStatus()
//
//*****************************************************************************
typedef enum
{
    SDFM_OUTPUT_WITHIN_THRESHOLD = 0,   //!< SDFM output is within threshold
    SDFM_OUTPUT_ABOVE_THRESHOLD  = 1,   //!< SDFM output is above threshold
    SDFM_OUTPUT_BELOW_THRESHOLD  = 2    //!< SDFM output is below threshold
} SDFM_OutputThresholdStatus;

//*****************************************************************************
//
//! Values that can be passed to all functions as the \e filterNumber
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SDFM_FILTER_1 = 0, //!< Digital filter 1
    SDFM_FILTER_2 = 1, //!< Digital filter 2
    SDFM_FILTER_3 = 2, //!< Digital filter 3
    SDFM_FILTER_4 = 3  //!< Digital filter 4
} SDFM_FilterNumber;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setFilterType(),
//! SDFM_setComparatorFilterType() as the \e filterType parameter.
//
//*****************************************************************************
typedef enum
{
    //! Digital filter with SincFast structure.
    SDFM_FILTER_SINC_FAST = 0x00,
    //! Digital filter with Sinc1 structure
    SDFM_FILTER_SINC_1    = 0x10,
    //! Digital filter with Sinc3 structure.
    SDFM_FILTER_SINC_2    = 0x20,
    //! Digital filter with Sinc4 structure.
    SDFM_FILTER_SINC_3    = 0x30
} SDFM_FilterType;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setupModulatorClock(),as the
//! \e clockMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! Modulator clock is identical to the data rate
   SDFM_MODULATOR_CLK_EQUAL_DATA_RATE  = 0,
   //! Modulator clock is half the data rate
   SDFM_MODULATOR_CLK_HALF_DATA_RATE   = 1,
   //! Modulator clock is off. Data is Manchester coded.
   SDFM_MODULATOR_CLK_OFF              = 2,
   //! Modulator clock is double the data rate.
   SDFM_MODULATOR_CLK_DOUBLE_DATA_RATE = 3
} SDFM_ModulatorClockMode;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setOutputDataFormat(),as the
//! \e dataFormat parameter.
//
//*****************************************************************************
typedef enum
{
   //! Filter output is in 16 bits 2's complement format.
   SDFM_DATA_FORMAT_16_BIT = 0,
   //! Filter output is in 32 bits 2's complement format.
   SDFM_DATA_FORMAT_32_BIT = 1
} SDFM_OutputDataFormat;

//*****************************************************************************
//
// Values that can be passed to SDFM_enableInterrupt and SDFM_disableInterrupt
// as intFlags parameter
//
//*****************************************************************************
//! Interrupt is generated if Modulator fails.
//!
#define SDFM_MODULATOR_FAILURE_INTERRUPT    0x200U
//! Interrupt on Comparator low-level threshold.
//!
#define SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT  0x40U
//! Interrupt on Comparator high-level threshold.
//!
#define SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT 0x20U
//! Interrupt on Acknowledge flag
//!
#define SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT 0x1U

//*****************************************************************************
//
// Values that can be passed to SDFM_clearInterruptFlag flags parameter
//
//*****************************************************************************
//! Main interrupt flag
//!
#define SDFM_MAIN_INTERRUPT_FLAG           0x80000000U
//! Filter 1 high -level threshold flag
//!
#define SDFM_FILTER_1_HIGH_THRESHOLD_FLAG  0x1U
//! Filter 1 low -level threshold flag
//!
#define SDFM_FILTER_1_LOW_THRESHOLD_FLAG   0x2U
//! Filter 2 high -level threshold flag
//!
#define SDFM_FILTER_2_HIGH_THRESHOLD_FLAG  0x4U
//! Filter 2 low -level threshold flag
//!
#define SDFM_FILTER_2_LOW_THRESHOLD_FLAG   0x8U
//! Filter 3 high -level threshold flag
//!
#define SDFM_FILTER_3_HIGH_THRESHOLD_FLAG  0x10U
//! Filter 3 low -level threshold flag
//!
#define SDFM_FILTER_3_LOW_THRESHOLD_FLAG   0x20U
//! Filter 4 high -level threshold flag
//!
#define SDFM_FILTER_4_HIGH_THRESHOLD_FLAG  0x40U
//! Filter 4 low -level threshold flag
//!
#define SDFM_FILTER_4_LOW_THRESHOLD_FLAG   0x80U
//! Filter 1 modulator failed flag
//!
#define SDFM_FILTER_1_MOD_FAILED_FLAG      0x100U
//! Filter 2 modulator failed flag
//!
#define SDFM_FILTER_2_MOD_FAILED_FLAG      0x200U
//! Filter 3 modulator failed flag
//!
#define SDFM_FILTER_3_MOD_FAILED_FLAG      0x400U
//! Filter 4 modulator failed flag
//!
#define SDFM_FILTER_4_MOD_FAILED_FLAG      0x800U
//! Filter 1 new data flag
//!
#define SDFM_FILTER_1_NEW_DATA_FLAG        0x1000U
//! Filter 2 new data flag
//!
#define SDFM_FILTER_2_NEW_DATA_FLAG        0x2000U
//! Filter 3 new data flag
//!
#define SDFM_FILTER_3_NEW_DATA_FLAG        0x4000U
//! Filter 4 new data flag
//!
#define SDFM_FILTER_4_NEW_DATA_FLAG        0x8000U

//*****************************************************************************
//
//! \internal
//! Checks SDFM base address.
//!
//! \param base specifies the SDFM module base address.
//!
//! This function determines if SDFM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
SDFM_isBaseValid(uint32_t base)
{
    return(
           (base == SDFM1_BASE) ||
           (base == SDFM2_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables data filter to be reset by an external source (PWM
//! compare output).
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_enableExternalReset(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set the SDSYNCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) |=
        SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables data filter from being reset by an external source
//! (PWM compare output).
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_disableExternalReset(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear the SDSYNCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) &=
        ~SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter specified by the \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_enableFilter(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set the FEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) |=
        SDFM_SDDFPARM1_FEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter specified by the \e filterNumber
//! variable.
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_disableFilter(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear the FEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) &=
        ~SDFM_SDDFPARM1_FEN;
    EDIS;
}

//*****************************************************************************
//
//! Set filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the filter type or structure.
//!
//! This function sets the filter type or structure to be used as specified by
//! filterType for the selected filter number as specified by filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_setFilterType(uint32_t base, SDFM_FilterNumber filterNumber,
                   SDFM_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to SST bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDFPARM1_SST_M)) |
                      ((uint16_t)filterType << 6U);
    EDIS;
}

//*****************************************************************************
//
//! Set data filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the data filter over sampling ratio.
//!
//! This function sets the filter oversampling ratio for the filter specified
//! by the filterNumber variable.Valid values for the variable
//! overSamplingRatio are 0 to 255 inclusive. The actual oversampling ratio
//! will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_setFilterOverSamplingRatio(uint32_t base, SDFM_FilterNumber filterNumber,
                                uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(overSamplingRatio < 256U);

    address = base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to DOSR bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDFPARM1_DOSR_M)) |
                      overSamplingRatio;
    EDIS;
}

//*****************************************************************************
//
//! Set modulator clock mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param clockMode is the modulator clock mode.
//!
//! This function sets the modulator clock mode specified by clockMode
//! for the filter specified by filterNumber.
//!
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_setupModulatorClock(uint32_t base, SDFM_FilterNumber filterNumber,
                         SDFM_ModulatorClockMode clockMode)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDCTLPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to MOD bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCTLPARM1_MOD_M)) |
                      (uint16_t)clockMode;

    EDIS;
}

//*****************************************************************************
//
//! Set the output data format
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param dataFormat is the output data format.
//!
//! This function sets the output data format for the filter specified by
//! filterNumber.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_setOutputDataFormat(uint32_t base, SDFM_FilterNumber filterNumber,
                         SDFM_OutputDataFormat dataFormat)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDDPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to DR bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDPARM1_DR)) |
                      ((uint16_t)dataFormat << 10U);
    EDIS;
}

//*****************************************************************************
//
//! Set data shift value.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param shiftValue is the data shift value.
//!
//! This function sets the shift value for the 16 bit 2's complement data
//! format. The valid maximum value for shiftValue is 31.
//!
//! \b Note: Use this function with 16 bit 2's complement data format only.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_setDataShiftValue(uint32_t base, SDFM_FilterNumber filterNumber,
                       uint16_t shiftValue)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(shiftValue < 32U);

    address = base + SDFM_O_SDDPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to SH bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDPARM1_SH_M)) |
                      (shiftValue << SDFM_SDDPARM1_SH_S);
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output high-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param highThreshold is the high-level threshold.
//!
//! This function sets the unsigned high-level threshold value for the
//! Comparator filter output. If the output value of the filter exceeds
//! highThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_setCompFilterHighThreshold(uint32_t base, SDFM_FilterNumber filterNumber,
                                uint16_t highThreshold)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(highThreshold < 0x7FFFU);

    address = base + SDFM_O_SDCMPH1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to HLT bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDCMPH1_HLT_M) | highThreshold;
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output low-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param lowThreshold is the low-level threshold.
//!
//! This function sets the unsigned low-level threshold value for the
//! Comparator filter output. If the output value of the filter gets below
//! lowThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_setCompFilterLowThreshold(uint32_t base, SDFM_FilterNumber filterNumber,
                               uint16_t lowThreshold)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(lowThreshold < 0x7FFFU);

    address = base + SDFM_O_SDCMPL1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to LLT bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDCMPL1_LLT_M) | lowThreshold;
    EDIS;
}

//*****************************************************************************
//
//! Enable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function enables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter specified
//! by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT,SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_enableInterrupt(uint32_t base, SDFM_FilterNumber filterNumber,
                     uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U;

    EALLOW;

    //
    // Low, high threshold, Modulator failure
    //
    if((intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                    SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                    SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
        //
        HWREGH(base + SDFM_O_SDCPARM1 + offset) |=
                (intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                             SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) |= SDFM_SDDFPARM1_AE;
    }
    EDIS;
}

//*****************************************************************************
//
//! Disable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function disables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter
//! specified by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT,SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void
SDFM_disableInterrupt(uint32_t base, SDFM_FilterNumber filterNumber,
                      uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U;

    EALLOW;

    //
    // Low, high threshold, modulator failure interrupts
    //
    if((intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                    SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                    SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT)) != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
        //
        HWREGH(base + SDFM_O_SDCPARM1 + offset) &=
            ~(intFlags & (SDFM_MODULATOR_FAILURE_INTERRUPT |
                          SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT |
                          SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) &= ~SDFM_SDDFPARM1_AE;
    }
    EDIS;
}

//*****************************************************************************
//
//! Set the comparator filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the comparator filter type or structure.
//!
//! This function sets the Comparator filter type or structure to be used as
//! specified by filterType for the selected filter number as specified by
//! filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_setComparatorFilterType(uint32_t base, SDFM_FilterNumber filterNumber,
                             SDFM_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to CS1_CS0 bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCPARM1_CS1_CS0_M)) |
                      ((uint16_t)filterType << 3U);
    EDIS;
}

//*****************************************************************************
//
//! Set Comparator filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the comparator filter over sampling ration.
//!
//! This function sets the comparator filter oversampling ratio for the filter
//! specified by the filterNumber.Valid values for the variable
//! overSamplingRatio are 0 to 31 inclusive.
//! The actual oversampling ratio will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void
SDFM_setCompFilterOverSamplingRatio(uint32_t base,
                                    SDFM_FilterNumber filterNumber,
                                    uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(overSamplingRatio < 32U);

    address = base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to COSR bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCPARM1_COSR_M)) |
                      overSamplingRatio;
    EDIS;
}

//*****************************************************************************
//
//! Get the filter data output.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest data filter output. Depending on the
//! filter data output format selected, the valid value will be the lower 16
//! bits or the whole 32 bits of the returned value.
//!
//! \return Returns the latest data filter output.
//*****************************************************************************
static inline uint32_t
SDFM_getFilterData(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDDATA bits
    //
    return(HWREG(base + SDFM_O_SDDATA1 + ((uint32_t)filterNumber * 16U)));
}

//*****************************************************************************
//
//! Get the Comparator threshold status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator output threshold status for the given
//! filterNumber.
//!
//! \return Returns the following status flags.
//! - \b SDFM_OUTPUT_WITHIN_THRESHOLD if the output is within the
//!                                   specified threshold.
//! - \b SDFM_OUTPUT_ABOVE_THRESHOLD  if the output is above the high
//!                                   threshold
//! - \b SDFM_OUTPUT_BELOW_THRESHOLD  if the output is below the low
//!                                   threshold.
//!
//*****************************************************************************
static inline SDFM_OutputThresholdStatus
SDFM_getThresholdStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG high/low threshold bits
    //
    return((SDFM_OutputThresholdStatus)((HWREG(base + SDFM_O_SDIFLG) >>
                                        (2U * (uint16_t)filterNumber)) & 0x3U));
}

//*****************************************************************************
//
//! Get the Modulator status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Modulator status.
//!
//! \return Returns true if the Modulator is operating normally
//!         Returns false if the Modulator has failed
//!
//*****************************************************************************
static inline bool
SDFM_getModulatorStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG MF1, MF2, MF3 OR MF4 bits
    //
    return(((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 8U)) &
            0x1U) != 0x1U);
}

//*****************************************************************************
//
//! Check if new Filter data is available.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns new filter data status.
//!
//! \return Returns \b true if new filter data is available
//!         Returns \b false if no new filter data is available
//!
//*****************************************************************************
static inline bool
SDFM_getNewFilterDataStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG AF1, AF2, AF3 OR AF4 bits
    //
    return(((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 12U)) &
            0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Get pending interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function returns any pending interrupt status.
//!
//! \return Returns \b true if there is a pending interrupt.
//!         Returns \b false if no interrupt is pending.
//!
//*****************************************************************************
static inline bool
SDFM_getIsrStatus(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG MIF
    //
    return((HWREG(base + SDFM_O_SDIFLG) >> 31U) == 0x1U);
}

//*****************************************************************************
//
//! Clear pending flags.
//!
//! \param base is the base address of the SDFM module
//! \param flag is the SDFM status
//!
//! This function clears the specified pending interrupt flag.
//! Valid values are
//! SDFM_MAIN_INTERRUPT_FLAG,SDFM_FILTER_1_NEW_DATA_FLAG,
//! SDFM_FILTER_2_NEW_DATA_FLAG,SDFM_FILTER_3_NEW_DATA_FLAG,
//! SDFM_FILTER_4_NEW_DATA_FLAG,SDFM_FILTER_1_MOD_FAILED_FLAG,
//! SDFM_FILTER_2_MOD_FAILED_FLAG,SDFM_FILTER_3_MOD_FAILED_FLAG,
//! SDFM_FILTER_4_MOD_FAILED_FLAG,SDFM_FILTER_1_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_1_LOW_THRESHOLD_FLAG,SDFM_FILTER_2_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_2_LOW_THRESHOLD_FLAG,SDFM_FILTER_3_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_3_LOW_THRESHOLD_FLAG,SDFM_FILTER_4_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_4_LOW_THRESHOLD_FLAG or any combination of the above
//! flags.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDFM_clearInterruptFlag(uint32_t base, uint32_t flag)
{
    ASSERT(SDFM_isBaseValid(base));
    ASSERT((flag & 0x8000FFFFU) == flag);

    //
    // Write to  SDIFLGCLR register
    //
    HWREG(base + SDFM_O_SDIFLGCLR) |= flag;
}

//*****************************************************************************
//
//! Enable main interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables the main SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDFM_enableMainInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set SDCTL MIE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) |= SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Disable main interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables the main SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDFM_disableMainInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear SDCTL MIE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) &= ~SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Enable main filter.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables main filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDFM_enableMainFilter(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set SDMFILEN MFE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) |= SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
//! Disable main filter.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables main filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void
SDFM_disableMainFilter(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear SDMFILEN MFE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) &= ~SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Configures SDFM comparator for filter config & threshold values
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is high-level and low-level threshold values.
//!
//! This function configures the comparator filter for filter config and
//! threshold values based on provided inputs.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDFM_FILTER_1 | SDFM_FILTER_SINC_2 | SDFM_SET_OSR(16))
//! will select Filter 1, SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the logical OR of the filter high and low
//! threshold values.
//! The bit definitions for config2 are as follow:
//!   - config2.[15:0]  low threshold
//!   - config2.[31:16] high threshold
//! The upper 16 bits define the high threshold and the lower
//! 16 bits define the low threshold.
//! SDFM_THRESHOLD(H,L) can be used to combine the high and low thresholds.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDFM_configComparator(uint32_t base, uint16_t config1, uint32_t config2);

//*****************************************************************************
//
//! Configure SDFM data filter
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                configuration.
//!
//! This function configures the data filter based on configurations
//! config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  Filter number
//!   - config1.[7:4]  Filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, and data shift values
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  Filter switch
//!   - config2.[15:2]  Shift values
//! Valid values for data representation are given in SDFM_OutputDataFormat
//! enumeration. SDFM_FILTER_DISABLE or SDFM_FILTER_ENABLE will define the
//! filter switch values.SDFM_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The shift value is valid only in SDFM_DATA_FORMAT_16_BIT data
//! representation format.
//!
//! \return None.
//!
//*****************************************************************************
extern void
SDFM_configDataFilter(uint32_t base, uint16_t config1, uint16_t config2);

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
#endif // SDFM_H
