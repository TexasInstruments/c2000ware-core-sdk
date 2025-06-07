//###########################################################################
//
// FILE:   cmpss_lite.h
//
// TITLE:  C28x CMPSS-Lite driver.
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

#ifndef CMPSS_LITE_H
#define CMPSS_LITE_H

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
//! \addtogroup cmpss_lite_api CMPSS-Lite
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_cmpss_lite.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
#include "cmpss.h"

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to CMPSSLITE_configDAC() as the config parameter.
//
//*****************************************************************************
//
// When is DAC value loaded from shadow register
//
//! DAC value updated from SYSCLK
#define CMPSSLITE_DACVAL_SYSCLK             0x0000U
//! DAC value updated from PWMSYNC
#define CMPSSLITE_DACVAL_PWMSYNC            0x0080U
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
#define CMPSSLITE_isBaseValid              CMPSS_isLiteBaseValid
#define CMPSSLITE_enableModule             CMPSS_enableModule
#define CMPSSLITE_disableModule            CMPSS_disableModule
#define CMPSSLITE_configHighComparator     CMPSS_configHighComparator
#define CMPSSLITE_configLowComparator      CMPSS_configLowComparator
#define CMPSSLITE_configOutputsHigh        CMPSS_configOutputsHigh
#define CMPSSLITE_configOutputsLow         CMPSS_configOutputsLow
#define CMPSSLITE_getStatus                CMPSS_getStatus
#define CMPSSLITE_setDACValueHigh          CMPSS_setDACValueHigh
#define CMPSSLITE_setDACValueLow           CMPSS_setDACValueLow
#define CMPSSLITE_initFilterHigh           CMPSS_initFilterHigh
#define CMPSSLITE_initFilterLow            CMPSS_initFilterLow
#define CMPSSLITE_getDACValueHigh          CMPSS_getDACValueHigh
#define CMPSSLITE_getDACValueLow           CMPSS_getDACValueLow
#define CMPSSLITE_clearFilterLatchHigh     CMPSS_clearFilterLatchHigh
#define CMPSSLITE_clearFilterLatchLow      CMPSS_clearFilterLatchLow
#define CMPSSLITE_configureSyncSourceHigh  CMPSS_configureSyncSourceHigh
#define CMPSSLITE_setHysteresis            CMPSS_setHysteresis
#define CMPSSLITE_enableLatchResetOnPWMSYNCHigh                               \
                                           CMPSS_enableLatchResetOnPWMSYNCHigh
#define CMPSSLITE_disableLatchResetOnPWMSYNCHigh                              \
                                           CMPSS_disableLatchResetOnPWMSYNCHigh
#define CMPSSLITE_enableLatchResetOnPWMSYNCLow                                \
                                           CMPSS_enableLatchResetOnPWMSYNCLow
#define CMPSSLITE_disableLatchResetOnPWMSYNCLow                               \
                                           CMPSS_disableLatchResetOnPWMSYNCLow
#define CMPSSLITE_configBlanking           CMPSS_configBlanking
#define CMPSSLITE_enableBlanking           CMPSS_enableBlanking
#define CMPSSLITE_disableBlanking          CMPSS_disableBlanking
#define CMPSSLITE_configFilterHigh         CMPSS_configFilterHigh
#define CMPSSLITE_configFilterLow          CMPSS_configFilterLow
#define CMPSSLITE_configLatchOnPWMSYNC     CMPSS_configLatchOnPWMSYNC

//*****************************************************************************
//
//! Sets the configuration for the internal comparator DACs.
//!
//! \param base is the base address of the CMPSSLITE module.
//! \param config is the configuration of the internal DAC.
//!
//! This function configures the comparator's internal DAC.  The \e config
//! parameter configures the DAC value load trigger event between SYSCLK and
//! EPWMSYNCPER i.e. the CMPSS_DACVAL_xxx value.
//!
//! The \b CMPSS_DACVAL_xxx term can take on the following values to specify
//! when the DAC value is loaded from its shadow register:
//! - \b CMPSS_DACVAL_SYSCLK - Value register updated on system clock.
//! - \b CMPSS_DACVAL_PWMSYNC - Value register updated on PWM sync.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMPSSLITE_configDAC(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSSLITE_isBaseValid(base));

    //
    // Write the DAC configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSSLITE_O_COMPDACHCTL) =
                                     (HWREGH(base + CMPSSLITE_O_COMPDACHCTL) &
                                      ~CMPSSLITE_COMPDACHCTL_SWLOADSEL)      |
                                     config;

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

#endif // CMPSS_LITE_H
