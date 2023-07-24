//###########################################################################
//
// FILE:   memcfg.h
//
// TITLE:  C28x RAM config driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef MEMCFG_H
#define MEMCFG_H

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
//! \addtogroup memcfg_api MemCfg
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memcfg.h"
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
//
// Masks to decode memory section defines.
//
#define MEMCFG_SECT_TYPE_MASK   0xFF000000U
#define MEMCFG_SECT_TYPE_D      0x00000000U
#define MEMCFG_SECT_TYPE_LS     0x01000000U
#define MEMCFG_SECT_TYPE_GS     0x02000000U
#define MEMCFG_SECT_TYPE_ROM      0x04000000U
#define MEMCFG_SECT_NUM_MASK    0x00FFFFFFU
#define MEMCFG_XACCPROTX_M      ((uint32_t)MEMCFG_GSXACCPROT0_FETCHPROT_GS0 | \
                                 (uint32_t)MEMCFG_GSXACCPROT0_CPUWRPROT_GS0 | \
                                 (uint32_t)MEMCFG_GSXACCPROT0_HICWRPROT_GS0 | \
                                 (uint32_t)MEMCFG_GSXACCPROT0_DMAWRPROT_GS0)
#define MEMCFG_XTEST_M          MEMCFG_DXTEST_TEST_M0_M

//
// Used for access violation functions.
//
#define MEMCFG_NMVIOL_MASK      0x0000FFFFU
#define MEMCFG_MVIOL_MASK       0x000F0000U
#define MEMCFG_MVIOL_SHIFT      16U

//
// Key for writing to memory test config lock registers
//
#define MEMCFG_TESTLOCK_KEY     0xA5A50000U

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to MemCfg_lockConfig(), MemCfg_unlockConfig(),
// MemCfg_commitConfig(), MemCfg_setProtection(), MemCfg_initSections(),
// MemCfg_setCLAMemType(), MemCfg_setLSRAMControllerSel(),
// MemCfg_getInitStatus() as the memSection(s) or ramSection(s) parameter.
//
//*****************************************************************************
//
// DxRAM - Dedicated RAM config
//
#define MEMCFG_SECT_M0              0x00000001U //!< M0 RAM
#define MEMCFG_SECT_M1              0x00000002U //!< M1 RAM
#define MEMCFG_SECT_DX_ALL          0x00000003U //!< All M and D RAM

//
// LSxRAM - Local shared RAM config
//
#define MEMCFG_SECT_LS4             0x01000010U //!< LS4 RAM
#define MEMCFG_SECT_LS5             0x01000020U //!< LS5 RAM
#define MEMCFG_SECT_LS6             0x01000040U //!< LS6 RAM
#define MEMCFG_SECT_LS7             0x01000080U //!< LS7 RAM
#define MEMCFG_SECT_LSX_ALL         0x010000F0U //!< All LS RAM

//
// GSxRAM - Global shared RAM config
//
#define MEMCFG_SECT_GS0             0x02000001U //!< GS0 RAM
#define MEMCFG_SECT_GSX_ALL         0x02000001U //!< All GS RAM


//
// ROM memory sections
//
#define MEMCFG_SECT_ROMBOOT           0x04000001U //!< BOOT ROM
#define MEMCFG_SECT_ROMSECURE         0x04000002U //!< Secure ROM
#define MEMCFG_SECT_ROM_ALL           0x04000003U //!< All ROMs

//
// All sections
//
#define MEMCFG_SECT_ALL             0xFFFFFFFFU //!< All configurable RAM

//*****************************************************************************
//
// Values that can be passed to MemCfg_setProtection() as the protectMode
// parameter.
//
//*****************************************************************************
#define MEMCFG_PROT_ALLOWCPUFETCH   0x00000000U //!< CPU fetch allowed
#define MEMCFG_PROT_BLOCKCPUFETCH   0x00000001U //!< CPU fetch blocked

#define MEMCFG_PROT_ALLOWCPUWRITE   0x00000000U //!< CPU write allowed
#define MEMCFG_PROT_BLOCKCPUWRITE   0x00000002U //!< CPU write blocked

#define MEMCFG_PROT_ALLOWDMAWRITE   0x00000000U //!< DMA write allowed (GSxRAM)
#define MEMCFG_PROT_BLOCKDMAWRITE   0x00000004U //!< DMA write blocked (GSxRAM)

#define MEMCFG_PROT_ALLOWHICWRITE   0x00000000U //!< HIC write allowed (GSxRAM)
#define MEMCFG_PROT_BLOCKHICWRITE   0x00000008U //!< HIC write blocked (GSxRAM)

//*****************************************************************************
//
// Values that can be passed to MemCfg_enableViolationInterrupt()
// MemCfg_disableViolationInterrupt(), MemCfg_forceViolationInterrupt(),
// MemCfg_clearViolationInterruptStatus(), and MemCfg_getViolationAddress() as
// the intFlags parameter. They also make up the return value of
// MemCfg_getViolationInterruptStatus().
//
//*****************************************************************************
#define MEMCFG_NMVIOL_CPUREAD    0x00000001U //!< Non-controller CPU read access
#define MEMCFG_NMVIOL_CPUWRITE   0x00000002U //!< Non-controller CPU write access
#define MEMCFG_NMVIOL_CPUFETCH   0x00000004U //!< Non-controller CPU fetch access
#define MEMCFG_NMVIOL_DMAWRITE   0x00000008U //!< Non-controller DMA write access
#define MEMCFG_NMVIOL_DMAREAD    0x00000400U //!< Non-controller DMA read access
#define MEMCFG_NMVIOL_HICREAD    0x00000800U //!< Non-controller HIC read access
#define MEMCFG_NMVIOL_HICWRITE   0x00001000U //!< Non-controller HIC write access

//*****************************************************************************
//
// Values that can be passed to MemCfg_enableViolationInterrupt()
// MemCfg_disableViolationInterrupt(), MemCfg_forceViolationInterrupt(),
// MemCfg_clearViolationInterruptStatus(), and MemCfg_getViolationAddress() as
// the intFlags parameter. They also make up the return value of
// MemCfg_getViolationInterruptStatus().
//
//*****************************************************************************
#define MEMCFG_MVIOL_CPUFETCH    0x00010000U //!< Controller CPU fetch access
#define MEMCFG_MVIOL_CPUWRITE    0x00020000U //!< Controller CPU write access
#define MEMCFG_MVIOL_DMAWRITE    0x00040000U //!< Controller DMA write access
#define MEMCFG_MVIOL_HICWRITE    0x00080000U //!< Controller HIC write access

//*****************************************************************************
//
// Values that can be passed to MemCfg_forceCorrErrorStatus(),
// MemCfg_clearCorrErrorStatus(), and MemCfg_getCorrErrorAddress() as the
// stsFlag(s) parameter and returned by MemCfg_getCorrErrorStatus().
//
// Note that MEMCFG_CERR_CPUREAD is the only value below that has a
// corresponding interrupt and may be used with the error functions that take
// an intFlag(s) parameter.
//
//*****************************************************************************
#define MEMCFG_CERR_CPUREAD      0x0001U //!< Correctable CPU read error
//*****************************************************************************
//
// Values that can be passed to MemCfg_forceUncorrErrorStatus(),
// MemCfg_clearUncorrErrorStatus(), and MemCfg_getUncorrErrorAddress() as the
// stsFlag(s) parameter and returned by MemCfg_getUncorrErrorStatus().
//
//*****************************************************************************
#define MEMCFG_UCERR_CPUREAD     0x0001U //!< Uncorrectable CPU read error
#define MEMCFG_UCERR_DMAREAD     0x0002U //!< Uncorrectable DMA read error
#define MEMCFG_UCERR_HICREAD     0x0020U //!< Uncorrectable HIC read error

#endif


//*****************************************************************************
//
//! Values that can be passed to MemCfg_setTestMode() as the \e testMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Functional mode. Test mode is disabled.
    MEMCFG_TEST_FUNCTIONAL   = 0,
    //! Writes allowed to data only
    MEMCFG_TEST_WRITE_DATA   = 1,
    //! Writes allowed to ECC only (for DxRAM/MxRAM)
    MEMCFG_TEST_WRITE_ECC    = 2,
    //! Writes allowed to parity only (for LSxRAM and GSxRAM)
    MEMCFG_TEST_WRITE_PARITY = 2
} MemCfg_TestMode;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! Enables individual RAM access violation interrupt sources.
//!
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//! Can be a logical OR any of the following values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//! This function enables the indicated RAM access violation interrupt sources.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt; disabled sources have no effect on the processor.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_enableViolationInterrupt(uint32_t intFlags)
{
    //
    // Enable the specified interrupts.
    //
    EALLOW;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_NMAVINTEN) |=
        intFlags & MEMCFG_NMVIOL_MASK;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_MAVINTEN) |=
        (intFlags & MEMCFG_MVIOL_MASK) >> MEMCFG_MVIOL_SHIFT;

    EDIS;
}

//*****************************************************************************
//
//! Disables individual RAM access violation interrupt sources.
//!
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//! Can be a logical OR any of the following values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//!
//! This function disables the indicated RAM access violation interrupt
//! sources. Only the sources that are enabled can be reflected to the
//! processor interrupt; disabled sources have no effect on the processor.
//!
//! \note Note that only non-controller violations may generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_disableViolationInterrupt(uint32_t intFlags)
{
    //
    // Disable the specified interrupts.
    //
    EALLOW;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_NMAVINTEN) &=
        ~(intFlags & MEMCFG_NMVIOL_MASK);

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_MAVINTEN) &=
        ~((intFlags & MEMCFG_MVIOL_MASK) >> MEMCFG_MVIOL_SHIFT);

    EDIS;
}

//*****************************************************************************
//
//! Gets the current RAM access violation status.
//!
//! This function returns the RAM access violation status. This function will
//! return flags for both controller and non-controller access violations
//! although only the non-controller flags have the ability to cause the
//! generation of an interrupt.
//!
//! \return Returns the current violation status, enumerated as a bit field of
//! the values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//*****************************************************************************
static inline uint32_t
MemCfg_getViolationInterruptStatus(void)
{
    uint32_t status;

    //
    // Read and return RAM access status flags.
    //
    status = (HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_NMAVFLG)) |
             (HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_MAVFLG) <<
              MEMCFG_MVIOL_SHIFT);

    return(status);
}

//*****************************************************************************
//
//! Sets the RAM access violation status.
//!
//! \param intFlags is a bit mask of the access violation flags to be set.
//! Can be a logical OR any of the following values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//!
//! This function sets the RAM access violation status. This function will
//! set flags for both controller and non-controller access violations, and an
//! interrupt will be generated if it is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_forceViolationInterrupt(uint32_t intFlags)
{
    //
    // Shift and mask the flags appropriately and write them to the
    // corresponding SET register.
    //
    EALLOW;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_NMAVSET) =
        intFlags & MEMCFG_NMVIOL_MASK;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_MAVSET) =
        (intFlags & MEMCFG_MVIOL_MASK) >> MEMCFG_MVIOL_SHIFT;

    EDIS;
}

//*****************************************************************************
//
//! Clears RAM access violation flags.
//!
//! \param intFlags is a bit mask of the access violation flags to be cleared.
//! Can be a logical OR any of the following values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearViolationInterruptStatus(uint32_t intFlags)
{
    //
    // Clear the requested access violation flags.
    //
    EALLOW;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_NMAVCLR) |=
        intFlags & MEMCFG_NMVIOL_MASK;

    HWREG(ACCESSPROTECTION_BASE + MEMCFG_O_MAVCLR) |=
        (intFlags & MEMCFG_MVIOL_MASK) >> MEMCFG_MVIOL_SHIFT;

    EDIS;
}

//*****************************************************************************
//
//! Sets the correctable error threshold value.
//!
//! \param threshold is the correctable error threshold.
//!
//! This value sets the error-count threshold at which a correctable error
//! interrupt is generated. That is when the error count register reaches the
//! value specified by the \e threshold parameter, an interrupt is
//! generated if it is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_setCorrErrorThreshold(uint32_t threshold)
{
    //
    // Write the threshold value to the appropriate register.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRTHRES) = threshold;

    EDIS;
}

//*****************************************************************************
//
//! Gets the correctable error count.
//!
//! \return Returns the number of correctable error have occurred.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorCount(void)
{
    //
    // Read and return the number of errors that have occurred.
    //
    return(HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRCNT));
}

//*****************************************************************************
//
//! Enables individual RAM correctable error interrupt sources.
//!
//! \param intFlags is a bit mask of the interrupt sources to be enabled. Can
//! take the value \b MEMCFG_CERR_CPUREAD only. Other values are reserved.
//!
//! This function enables the indicated RAM correctable error interrupt
//! sources. Only the sources that are enabled can be reflected to the
//! processor interrupt; disabled sources have no effect on the processor.
//!
//! \note Note that only correctable errors may generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_enableCorrErrorInterrupt(uint32_t intFlags)
{
    //
    // Enable the specified interrupts.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTEN) |= intFlags;

    EDIS;
}

//*****************************************************************************
//
//! Disables individual RAM correctable error interrupt sources.
//!
//! \param intFlags is a bit mask of the interrupt sources to be disabled. Can
//! take the value \b MEMCFG_CERR_CPUREAD only. Other values are reserved.
//!
//! This function disables the indicated RAM correctable error interrupt
//! sources. Only the sources that are enabled can be reflected to the
//! processor interrupt; disabled sources have no effect on the processor.
//!
//! \note Note that only correctable errors may generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_disableCorrErrorInterrupt(uint32_t intFlags)
{
    //
    // Disable the specified interrupts.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTEN) &= ~(intFlags);

    EDIS;
}

//*****************************************************************************
//
//! Gets the current RAM correctable error interrupt status.
//!
//! \return Returns the current error interrupt status. Will return a value of
//! \b MEMCFG_CERR_CPUREAD if an interrupt has been generated. If not, the
//! function will return 0.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorInterruptStatus(void)
{
    //
    // Read and return correctable error interrupt flags.
    //
    return(HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTFLG));
}

//*****************************************************************************
//
//! Sets the RAM correctable error interrupt status.
//!
//! \param intFlags is a bit mask of the interrupt sources to be set. Can take
//! the value \b MEMCFG_CERR_CPUREAD only. Other values are reserved.
//!
//! This function sets the correctable error interrupt flag.
//!
//! \note Note that only correctable errors may generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_forceCorrErrorInterrupt(uint32_t intFlags)
{
    //
    // Write the flags to the appropriate SET register.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTSET) = intFlags;

    EDIS;
}

//*****************************************************************************
//
//! Clears the RAM correctable error interrupt status.
//!
//! \param intFlags is a bit mask of the interrupt sources to be cleared. Can
//! take the value \b MEMCFG_CERR_CPUREAD only. Other values are reserved.
//!
//! This function clears the correctable error interrupt flag.
//!
//! \note Note that only correctable errors may generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearCorrErrorInterruptStatus(uint32_t intFlags)
{
    //
    // Clear the requested flags.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTCLR) |= intFlags;

    EDIS;
}

//*****************************************************************************
//
//! Gets the current correctable RAM error status.
//!
//! \return Returns the current error status, enumerated as a bit field of
//! \b MEMCFG_CERR_CPUREAD
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorStatus(void)
{
    //
    // Read and return RAM error status flags.
    //
    return(HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRFLG));
}

//*****************************************************************************
//
//! Gets the current uncorrectable RAM error status.
//!
//! \return Returns the current error status, enumerated as a bit field of
//! \b MEMCFG_UCERR_CPUREAD, \b MEMCFG_UCERR_DMAREAD, \b MEMCFG_UCERR_HICREAD
//
//*****************************************************************************
static inline uint32_t
MemCfg_getUncorrErrorStatus(void)
{
    //
    // Read and return RAM error status flags.
    //
    return(HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRFLG));
}

//*****************************************************************************
//
//! Sets the specified correctable RAM error status flag.
//!
//! \param stsFlags is a bit mask of the error sources. This parameter can be
//! any of the following values:
//! \b MEMCFG_CERR_CPUREAD
//!
//! This function sets the specified correctable RAM error status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_forceCorrErrorStatus(uint32_t stsFlags)
{
    //
    // Write the flags to the appropriate SET register.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRSET) = stsFlags;

    EDIS;
}

//*****************************************************************************
//
//! Sets the specified uncorrectable RAM error status flag.
//!
//! \param stsFlags is a bit mask of the error sources. This parameter can be
//! any of the following values:
//! \b MEMCFG_UCERR_CPUREAD, \b MEMCFG_UCERR_DMAREAD, \b MEMCFG_UCERR_HICREAD
//!
//! This function sets the specified uncorrectable RAM error status flag.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_forceUncorrErrorStatus(uint32_t stsFlags)
{
    //
    // Write the flags to the appropriate SET register.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRSET) = stsFlags;

    EDIS;
}

//*****************************************************************************
//
//! Clears correctable RAM error flags.
//!
//! \param stsFlags is a bit mask of the status flags to be cleared.
//! This parameter can be any of the following :
//! \b MEMCFG_CERR_CPUREAD
//!
//! This function clears the specified correctable RAM error flags.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearCorrErrorStatus(uint32_t stsFlags)
{
    //
    // Clear the requested flags.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRCLR) |= stsFlags;

    EDIS;
}

//*****************************************************************************
//
//! Clears uncorrectable RAM error flags.
//!
//! \param stsFlags is a bit mask of the status flags to be cleared.
//! This parameter can be any of the following :
//! \b MEMCFG_UCERR_CPUREAD, \b MEMCFG_UCERR_DMAREAD, \b MEMCFG_UCERR_HICREAD
//!
//! This function clears the specified uncorrectable RAM error flags.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearUncorrErrorStatus(uint32_t stsFlags)
{
    //
    // Clear the requested flags.
    //
    EALLOW;

    HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRCLR) |= stsFlags;

    EDIS;
}

//*****************************************************************************
//
//! Locks the writes to the configuration of specified memory sections.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function locks writes to the access protection, initialization control
//! and test mode configuration of a memory section. This means calling APIs
//! like MemCfg_setProtection() or MemCfg_initSections() for a locked memory
//! section will have no effect until MemCfg_unlockConfig() is called.
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0 and \b MEMCFG_SECT_M1 or \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx or \b MEMCFG_SECT_LSX_ALL
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx or \b MEMCFG_SECT_GSX_ALL
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_lockConfig(uint32_t memSections);

//*****************************************************************************
//
//! Unlocks the writes to the configuration of a memory section.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function unlocks writes to the access protection and controller select
//! configuration of a memory section that has been locked using
//! MemCfg_lockConfig().
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0 and \b MEMCFG_SECT_M1 or \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx or \b MEMCFG_SECT_LSX_ALL
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx or \b MEMCFG_SECT_GSX_ALL
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_unlockConfig(uint32_t memSections);

//*****************************************************************************
//
//! Permanently locks writes to the configuration of a memory section.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function permanently locks writes to the access protection and
//! controller select configuration of a memory section. That means calling
//! MemCfg_setProtection() or MemCfg_setLSRAMControllerSel() for a locked memory
//! section will have no effect. To lock the configuration in a nonpermanent
//! way, use MemCfg_lockConfig().
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0 and \b MEMCFG_SECT_M1 or \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx or \b MEMCFG_SECT_LSX_ALL
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx or \b MEMCFG_SECT_GSX_ALL
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_commitConfig(uint32_t memSections);

//*****************************************************************************
//
//! Sets the access protection mode of a single memory section.
//!
//! \param memSection is the memory section to be configured.
//! \param protectMode is the logical OR of the settings to be applied.
//!
//! This function sets the access protection mode of a specified memory section.
//! The mode is passed into the \e protectMode parameter as the logical OR of
//! the following values:
//! - \b MEMCFG_PROT_ALLOWCPUFETCH or \b MEMCFG_PROT_BLOCKCPUFETCH - CPU fetch
//! - \b MEMCFG_PROT_ALLOWCPUWRITE or \b MEMCFG_PROT_BLOCKCPUWRITE - CPU write
//! - \b MEMCFG_PROT_ALLOWDMAWRITE or \b MEMCFG_PROT_BLOCKDMAWRITE - DMA write
//! - \b MEMCFG_PROT_ALLOWHICWRITE or \b MEMCFG_PROT_BLOCKHICWRITE - HIC write
//!
//! The \e memSection parameter is one of the following indicators:
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx
//!
//! This function will have no effect if the associated registers have been
//! locked by MemCfg_lockConfig() or MemCfg_commitConfig().
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_setProtection(uint32_t memSection, uint32_t protectMode);

//*****************************************************************************
//
//! Locks the writes to the test mode configuration of specified memory
//! sections.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function locks writes to the test mode configuration of a RAM section.
//! That means calling MemCfg_setTestMode() for a locked RAM section will have
//! no effect until MemCfg_unlockTestConfig() is called.
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0, \b MEMCFG_SECT_M1, or use \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx or use
//!   \b MEMCFG_SECT_LSX_ALL to configure all possible LSRAM sections.
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx or use
//!   \b MEMCFG_SECT_GSX_ALL to configure all possible GSRAM sections.
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_lockTestConfig(uint32_t memSections);

//*****************************************************************************
//
//! Unlocks the writes to the test mode configuration of specified memory
//! sections.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function unlocks writes to the test mode configuration of a RAM
//! section that has been locked using MemCfg_lockTestConfig().
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0, \b MEMCFG_SECT_M1, or use \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx or use
//!   \b MEMCFG_SECT_LSX_ALL to configure all possible LSRAM sections.
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx or use
//!   \b MEMCFG_SECT_GSX_ALL to configure all possible GSRAM sections.
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_unlockTestConfig(uint32_t memSections);

//*****************************************************************************
//
//! Sets the test mode of the specified memory section.
//!
//! \param memSection is the memory section to be configured.
//! \param testMode is the test mode selected.
//!
//! This function sets the test mode configuration of the RAM section. The
//! \e testMode parameter can take one of the following values:
//! - \b MEMCFG_TEST_FUNCTIONAL
//! - \b MEMCFG_TEST_WRITE_DATA
//! - \b MEMCFG_TEST_WRITE_ECC
//! - \b MEMCFG_TEST_WRITE_PARITY
//!
//! The \e memSection parameter is one of the following indicators:
//! - \b MEMCFG_SECT_M0, \b MEMCFG_SECT_M1
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_setTestMode(uint32_t memSection, MemCfg_TestMode testMode);

//*****************************************************************************
//
//! Starts the initialization the specified RAM sections.
//!
//! \param ramSections is the logical OR of the sections to be initialized.
//!
//! This function starts the initialization of the specified RAM sections. Use
//! MemCfg_getInitStatus() to check if the initialization is done.
//!
//! The \e ramSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0, \b MEMCFG_SECT_M1, or \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx, or \b MEMCFG_SECT_LSX_ALL
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx, or \b MEMCFG_SECT_GSX_ALL
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_initSections(uint32_t ramSections);

//*****************************************************************************
//
//! Get the status of initialized RAM sections.
//!
//! \param ramSections is the logical OR of the sections to be checked.
//!
//! This function gets the initialization status of the RAM sections specified
//! by the \e ramSections parameter.
//!
//! The \e ramSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_M0, \b MEMCFG_SECT_M1, or \b MEMCFG_SECT_DX_ALL
//! - \b MEMCFG_SECT_LS4 through \b MEMCFG_SECT_LSx, or \b MEMCFG_SECT_LSX_ALL
//! - \b MEMCFG_SECT_GS0 through \b MEMCFG_SECT_GSx, or \b MEMCFG_SECT_GSX_ALL
//! - \b OR use \b MEMCFG_SECT_ALL to get status of all possible sections.
//!
//! \note Use MemCfg_initSections() to start the initialization.
//!
//! \return Returns \b true if all the sections specified by \e ramSections
//! have been initialized and \b false if not.
//
//*****************************************************************************
extern bool
MemCfg_getInitStatus(uint32_t ramSections);

//*****************************************************************************
//
//! Get the violation address associated with a intFlag.
//!
//! \param intFlag is the type of access violation as indicated by ONE of
//! these values:
//!  - \b MEMCFG_NMVIOL_CPUREAD   - Non-controller CPU read access
//!  - \b MEMCFG_NMVIOL_CPUWRITE  - Non-controller CPU write access
//!  - \b MEMCFG_NMVIOL_CPUFETCH  - Non-controller CPU fetch access
//!  - \b MEMCFG_NMVIOL_DMAWRITE  - Non-controller DMA write access
//!  - \b MEMCFG_NMVIOL_DMAREAD   - Non-controller DMA read access
//!  - \b MEMCFG_NMVIOL_HICREAD   - Non-controller HIC read access
//!  - \b MEMCFG_NMVIOL_HICWRITE  - Non-controller HIC write access
//!  - \b MEMCFG_MVIOL_CPUFETCH   - Controller CPU fetch access
//!  - \b MEMCFG_MVIOL_CPUWRITE   - Controller CPU write access
//!  - \b MEMCFG_MVIOL_DMAWRITE   - Controller DMA write access
//!  - \b MEMCFG_MVIOL_HICWRITE   - Controller HIC write access
//!
//! \return Returns the violation address associated with the \e intFlag.
//
//*****************************************************************************
extern uint32_t
MemCfg_getViolationAddress(uint32_t intFlag);

//*****************************************************************************
//
//! Get the correctable error address associated with a stsFlag.
//!
//! \param stsFlag is the type of error to which the returned address will
//! correspond.  Can currently take the value \b MEMCFG_CERR_CPUREAD only.
//! Other values are reserved.
//!
//! \return Returns the error address associated with the stsFlag.
//
//*****************************************************************************
extern uint32_t
MemCfg_getCorrErrorAddress(uint32_t stsFlag);

//*****************************************************************************
//
//! Get the uncorrectable error address associated with a stsFlag.
//!
//! \param stsFlag is the type of error to which the returned address will
//! correspond. It may be passed one of these values:
//! \b MEMCFG_UCERR_CPUREAD, or \b MEMCFG_UCERR_DMAREAD values
//!
//! \return Returns the error address associated with the stsFlag.
//
//*****************************************************************************
extern uint32_t
MemCfg_getUncorrErrorAddress(uint32_t stsFlag);

//*****************************************************************************
//
//! Forces parity error in the selected memory.
//!
//! \param memSections is the logical OR of the sections to be tested.
//!
//! This function forces the parity error in the memories specified
//! by the \e memSections parameter.
//!
//! The \e memSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_ROMBOOT, \b MEMCFG_SECT_ROMSECURE
//! - \b OR use \b MEMCFG_SECT_ALL to force parity error in all possible
//!      memory sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_forceMemError(uint32_t memSections);

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

#endif // MEMCFG_H
