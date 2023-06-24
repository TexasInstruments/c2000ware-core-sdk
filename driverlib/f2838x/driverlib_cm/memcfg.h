//###########################################################################
//
// FILE:   memcfg.h
//
// TITLE:  CM SRAM config driver.
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
//! \brief This module is used for CM SRAM configurations.
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
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Define for specifying the key for writing error registers
//
//*****************************************************************************
#define MEMCFG_KEY                     0xA5A50000U //!< Key for error registers

//*****************************************************************************
//
// Masks to decode memory section defines.
//
//*****************************************************************************
#define MEMCFG_SECT_TYPE_MASK          0xFF000000U //!< Mask for section type
#define MEMCFG_SECT_TYPE_CX            0x00000000U //!< Mask for Cx memory
#define MEMCFG_SECT_TYPE_CMMSGX        0x01000000U //!< Mask for CMMSGRAM
#define MEMCFG_SECT_TYPE_SX            0x02000000U //!< Mask for S/Ex memory
#define MEMCFG_SECT_TYPE_ROM           0x03000000U //!< Mask for ROM memory
#define MEMCFG_SECT_TYPE_PERIMEM       0x04000000U //!< Mask for peripheral
                                                   //!< memory(EMAC & EtherCAT)
#define MEMCFG_SECT_NUM_MASK           0x00FFFFFFU //!< Mask for selecting the
                                                   //!< section number
//*****************************************************************************
//
// Define to specify the mask for memory test mode.
//
//*****************************************************************************
#define MEMCFG_TESTMODE_M              MEMCFG_CXTEST_TEST_C0_M //!< Mask for
                                                               //!< test mode

//*****************************************************************************
//
// Values that can be passed to MemCfg_lockConfig(), MemCfg_unlockConfig(),
// MemCfg_setTestMode() as memSection(s) parameter; to MemCfg_initSections(),
// MemCfg_getInitStatus() as ramSections parameter; to  MemCfg_forceMemError(),
// MemCfg_enablePeriMemTestMode(), MemCfg_disablePeriMemTestMode() as the
// memTypes parameter.
//
//*****************************************************************************

//
// Cx Memories - Dedicated to core CM, accessible on CODE bus.
//
#define MEMCFG_SECT_C0                 0x00000001U   //!< C0 RAM
#define MEMCFG_SECT_C1                 0x00000002U   //!< C1 RAM
#define MEMCFG_SECT_CX_ALL             0x00000003U   //!< All Cx RAM

//
// CMMSGx Memories - For exchanging data between CM & C28x subsystem.
//
#define MEMCFG_SECT_CMTOCPU1MSGRAM0    0x01000001U  //!< CM TO CPU1 MSG RAM0
#define MEMCFG_SECT_CMTOCPU1MSGRAM1    0x01000002U  //!< CM TO CPU1 MSG RAM1
#define MEMCFG_SECT_CMTOCPU2MSGRAM0    0x01000004U  //!< CM TO CPU2 MSG RAM0
#define MEMCFG_SECT_CMTOCPU2MSGRAM1    0x01000008U  //!< CM TO CPU2 MSG RAM1
#define MEMCFG_SECT_CMMSGX_ALL         0x0100000FU  //!< All CM MSG RAMs

//
// Sx and Ex Memories - shared between bus masters.
//
#define MEMCFG_SECT_S0                 0x02000001U //!< S0 RAM
#define MEMCFG_SECT_S1                 0x02000002U //!< S1 RAM
#define MEMCFG_SECT_S2                 0x02000004U //!< S2 RAM
#define MEMCFG_SECT_S3                 0x02000008U //!< S3 RAM
#define MEMCFG_SECT_E0                 0x02000010U //!< E0 RAM
#define MEMCFG_SECT_SX_ALL             0x0200001FU //!< All Sx and Ex RAM

//
// ROM memory - read only
//
#define MEMCFG_SECT_ROM                0x03000001U //!< ROM Section

//
// Peripheral Memories - EMAC & EtherCAT
//
#define MEMCFG_SECT_PERIMEM_EMAC       0x04000002U //!< EMAC memory
#define MEMCFG_SECT_PERIMEM_ETHERCAT   0x04000020U //!< EtherCAT memory
#define MEMCFG_SECT_PERIMEM_ALL        0x04000001U //!< All peripheral memories

//
// All Memory Sections
//
#define MEMCFG_SECT_ALL                0xFFFFFFFFU //!< All memory Sections

//*****************************************************************************
//
// Values that can be passed to MemCfg_forceUncorrErrorStatus(),
// MemCfg_clearUncorrErrorStatus(), MemCfg_getUncorrErrorAddress() as stsFlags
// parameter and returned by MemCfg_getUncorrErrorStatus().
//
//*****************************************************************************
#define MEMCFG_UCERR_M4READ            0x00000001U //!< Uncorr M4 Read Error
#define MEMCFG_UCERR_M4WRITE           0x00000002U //!< Uncorr M4 Write Error
#define MEMCFG_UCERR_EMACREAD          0x00000004U //!< Uncorr EMAC Read Error
#define MEMCFG_UCERR_UDMAREAD          0x00000010U //!< Uncorr uDMA Read Error
#define MEMCFG_UCERR_UDMAWRITE         0x00000020U //!< Uncorr uDMA Write Error
#define MEMCFG_UCERR_ETHERCATMEMREAD   0x00000040U //!< Uncorr ECAT Mem Read
                                                   //!< Error
#define MEMCFG_UCERR_EMACMEMREAD       0x00000080U //!< Uncorr EMAC Mem Read
                                                   //!< Error

//*****************************************************************************
//
// Values that can be passed to MemCfg_getCorrErrorStatus(),
// MemCfg_forceCorrErrorStatus(), MemCfg_clearCorrErrorStatus(),
// MemCfg_getCorrErrorAddress(), as stsFlag(s) parameter; to
// MemCfg_enableCorrErrorInterrupt(), MemCfg_disableCorrErrorInterrupt(),
// MemCfg_clearCorrErrorInterruptStatus() as intFlags parameter and returned by
// MemCfg_getCorrErrorStatus() and MemCfg_getCorrErrorInterruptStatus().
//
//*****************************************************************************
#define MEMCFG_CERR_M4READ             0x00000001U //!< Corr M4 Read Error
#define MEMCFG_CERR_M4WRITE            0x00000002U //!< Corr M4 Write Error
#define MEMCFG_CERR_EMACREAD           0x00000004U //!< Corr EMAC Read Error
#define MEMCFG_CERR_UDMAREAD           0x00000010U //!< Corr uDMA Read Error
#define MEMCFG_CERR_UDMAWRITE          0x00000020U //!< Corr uDMA Write Error

//*****************************************************************************
//
// Values that can be passed to MemCfg_clearDiagErrorStatus() as stsFlags
// parameter and returned by MemCfg_getDiagErrorStatus().
//
//*****************************************************************************
#define MEMCFG_DIAGERR_UNCORR_READ     0x00000001U //!< Diag Uncorr Read Error
#define MEMCFG_DIAGERR_UNCORR_WRITE    0x00000002U //!< Diag Uncorr Write Error
#define MEMCFG_DIAGERR_CORR_READ       0x00000004U //!< Diag Corr Read Error
#define MEMCFG_DIAGERR_CORR_WRITE      0x00000008U //!< Diag Corr Write Error

//*****************************************************************************
//
// Values that can be passed to MemCfg_getBusFaultAddress(),
// MemCfg_clearBusFaultStatus(), MemCfg_getBusFaultStatus() as busMaster(s)
// parameter.
//
//*****************************************************************************

//
// Select M4 as bus master
//
#define MEMCFG_BUSMASTER_M4            MEMCFG_BUSFAULTFLG_M4BUSFAULT

//
// Select uDMA as bus master
//
#define MEMCFG_BUSMASTER_UDMA          MEMCFG_BUSFAULTFLG_UDMABUSFAULT

//
// Select EMAC as bus master
//
#define MEMCFG_BUSMASTER_EMAC          MEMCFG_BUSFAULTFLG_EMACBUSFAULT

//
// Select all the bus masters
//
#define MEMCFG_BUSMATER_ALL            (MEMCFG_BUSMASTER_M4    |               \
                                        MEMCFG_BUSMASTER_UDMA  |               \
                                        MEMCFG_BUSMASTER_EMAC)

//*****************************************************************************
//
// Values that can be returned by MemCfg_getBusFaultStatus().
//
//*****************************************************************************

//
// M4 access encountered busfault
//
#define MEMCFG_BUSFAULT_M4             MEMCFG_BUSFAULTFLG_M4BUSFAULT

//
// uDMA access encountered busfault
//
#define MEMCFG_BUSFAULT_UDMA           MEMCFG_BUSFAULTFLG_UDMABUSFAULT

//
// EMAC access encountered busfault
//
#define MEMCFG_BUSFAULT_EMAC           MEMCFG_BUSFAULTFLG_EMACBUSFAULT

//*****************************************************************************
//
//! Values that can be passed to MemCfg_setTestMode() as the \e testMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    MEMCFG_TEST_FUNCTIONAL             = 0x0U, //!< Functional mode
    MEMCFG_TEST_WRITE_DATA             = 0x1U, //!< Writes allowed to data only
    MEMCFG_TEST_WRITE_ECC              = 0x2U, //!< Writes allowed to ECC only
    MEMCFG_TEST_FUNC_DIAG              = 0x3U  //!< Diagnostic mode, similar to
                                               //!< functional mode but NMI is
                                               //!< not generated
} MemCfg_TestMode;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Gets the current uncorrectable memory read/write error status.
//!
//! \return Returns the current error status, enumerated as a bit field of
//! \b MEMCFG_UCERR_M4READ, \b MEMCFG_UCERR_M4WRITE, \b MEMCFG_UCERR_EMACREAD,
//! \b MEMCFG_UCERR_UDMAREAD, \b MEMCFG_UCERR_UDMAWRITE,
//! \b MEMCFG_UCERR_ETHERCATMEMREAD or/and \b MEMCFG_UCERR_EMACMEMREAD.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getUncorrErrorStatus(void)
{
    //
    // Read and return RAM error status flags.
    //
    return(HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCERRFLG));
}

//*****************************************************************************
//
//! Sets the specified uncorrectable memory read/write error status flag.
//!
//! \param stsFlags is a bit mask of the error sources.
//!
//! This function sets the specified uncorrectable memory read/write error
//! status flag. The \e stsFlags parameter can take any of the following values:
//! \b MEMCFG_UCERR_M4READ, \b MEMCFG_UCERR_M4WRITE, \b MEMCFG_UCERR_EMACREAD,
//! \b MEMCFG_UCERR_UDMAREAD, \b MEMCFG_UCERR_UDMAWRITE,
//! \b MEMCFG_UCERR_ETHERCATMEMREAD or/and \b MEMCFG_UCERR_EMACMEMREAD.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCERRSET) = (MEMCFG_KEY | stsFlags);
}

//*****************************************************************************
//
//! Clears uncorrectable memory read/write error flags.
//!
//! \param stsFlags is a bit mask of the status flags to be cleared.
//!
//! This function clears the specified uncorrectable memory read/write error
//! flags. The \e stsFlags parameter can take any of the following values or
//! their logical OR: \b MEMCFG_UCERR_M4READ, \b MEMCFG_UCERR_M4WRITE,
//! \b MEMCFG_UCERR_EMACREAD, \b MEMCFG_UCERR_UDMAREAD,
//! \b MEMCFG_UCERR_UDMAWRITE, \b MEMCFG_UCERR_ETHERCATMEMREAD or/and
//! \b MEMCFG_UCERR_EMACMEMREAD.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearUncorrErrorStatus(uint32_t stsFlags)
{
    //
    // Clear the respective error flags.
    //
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCERRCLR) = (MEMCFG_KEY | stsFlags);
}

//*****************************************************************************
//
//! Gets the bus fault status of the selected bus master.
//!
//! \param busMasters specifies the bus master for which status is to be
//! returned.
//!
//! This function returns the bus fault status for selected bus masters.The
//! parameter \e busMasters can be logical OR of any of the following values:
//! \b MEMCFG_BUSMASTER_M4, \b MEMCFG_BUSMASTER_UDMA, \b MEMCFG_BUSMASTER_EMAC,
//! or \b MEMCFG_BUSMATER_ALL to get the status for all the bus masters.
//!
//! \return Returns bus fault status of the bus masters. It can return below
//! values or their logical OR's:
//! - \b MEMCFG_BUSFAULT_M4 - M4 access encountered busfault
//! - \b MEMCFG_BUSFAULT_UDMA - uDMA access encountered busfault
//! - \b MEMCFG_BUSFAULT_EMAC - EMAC access encountered busfault
//
//*****************************************************************************
static inline uint32_t
MemCfg_getBusFaultStatus(uint32_t busMasters)
{
    //
    // Return the bus fault status.
    //
    return(HWREG(CMMEMORYERROR_BASE + MEMCFG_O_BUSFAULTFLG) & busMasters);
}

//*****************************************************************************
//
//! Clears the bus fault status of the selected bus master.
//!
//! \param busMasters specifies the bus masters for which fault status is to be
//! cleared.
//!
//! This function clears the bus fault status for selected bus masters. The
//! \e busMasters parameter can be logical OR of any of the following values:
//! \b MEMCFG_BUSMASTER_M4, MEMCFG_BUSMASTER_UDMA, MEMCFG_BUSMASTER_EMAC, or
//! \b MEMCFG_BUSMATER_ALL to clear the status for all the bus masters.
//!
//! \return None
//
//*****************************************************************************
static inline void
MemCfg_clearBusFaultStatus(uint32_t busMasters)
{
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_BUSFAULTCLR) =
                                                    (MEMCFG_KEY | busMasters);
}

//*****************************************************************************
//
//! Gets the current correctable memory read/write error status.
//!
//! \return Returns the current error status, enumerated as a bit field of
//! \b MEMCFG_CERR_M4READ, \b MEMCFG_CERR_M4WRITE, \b MEMCFG_CERR_EMACREAD,
//! \b MEMCFG_CERR_UDMAREAD, and/or \b MEMCFG_CERR_UDMAWRITE.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorStatus(void)
{
    //
    // Read and return RAM error status flags.
    //
    return(HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRFLG));
}

//*****************************************************************************
//
//! Sets the specified correctable memory read/write error status flag.
//!
//! \param stsFlags is a bit mask of the error sources.
//!
//! This function sets the specified correctable memory read/write error status
//! flag. The \e stsFlags parameter can take any of the following values:
//! \b MEMCFG_CERR_M4READ, \b MEMCFG_CERR_M4WRITE, \b MEMCFG_CERR_EMACREAD,
//! \b MEMCFG_CERR_UDMAREAD, and/or \b MEMCFG_CERR_UDMAWRITE.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRSET) = (MEMCFG_KEY | stsFlags);
}

//*****************************************************************************
//
//! Clears correctable memory read/write error flags.
//!
//! \param stsFlags is a bit mask of the status flags to be cleared.
//!
//! This function clears the specified correctable memory read/write error
//! flags. The \e stsFlags parameter can take any of the following values:
//! \b MEMCFG_CERR_M4READ, \b MEMCFG_CERR_M4WRITE, \b MEMCFG_CERR_EMACREAD,
//! \b MEMCFG_CERR_UDMAREAD and/or \b MEMCFG_CERR_UDMAWRITE.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRCLR) = (MEMCFG_KEY | stsFlags);
}

//*****************************************************************************
//
//! Gets the correctable error count.
//!
//! \return Returns the number of correctable error which have occurred.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorCount(void)
{
    //
    // Read and return the number of errors that have occurred.
    //
    return(HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRCNT));
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CERRTHRES) = threshold;
}

//*****************************************************************************
//
//! Enables correctable error interrupt source.
//!
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated correctable error interrupt
//! source. Only the sources that are enabled can be reflected to the
//! processor interrupt; disabled sources have no effect on the processor. The
//! param \e intFlags can take the value \b MEMCFG_CERR_M4READ only. Other
//! values are reserved.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEINTEN) = (MEMCFG_KEY | intFlags);
}

//*****************************************************************************
//
//! Disables individual correctable error interrupt sources.
//!
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated correctable error interrupt
//! sources. Only the sources that are enabled can be reflected to the
//! processor interrupt; disabled sources have no effect on the processor. The
//! param \e intFlags can take the value \b MEMCFG_CERR_M4READ only. Other
//! values are reserved.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEINTEN) = (MEMCFG_KEY | (~(intFlags) &
                                                    0x0000FFFFU));
}

//*****************************************************************************
//
//! Gets the current RAM correctable error interrupt status.
//!
//! \return Returns the current error interrupt status. Will return a value of
//! \b MEMCFG_CERR_M4READ if an interrupt has been generated. If not, the
//! function will return 0.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getCorrErrorInterruptStatus(void)
{
    //
    // Read and return /correctable error interrupt flags.
    //
    return(HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEINTFLG));
}

//*****************************************************************************
//
//! Sets the correctable error interrupt status.
//!
//! \param intFlags is a bit mask of the interrupt sources to be set.
//!
//! This function sets the correctable error interrupt flag. The parameter
//! \e intFlags can take the value \b MEMCFG_CERR_M4READ only. Other values are
//! reserved.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEINTSET) = (MEMCFG_KEY | intFlags);
}

//*****************************************************************************
//
//! Clears the correctable error interrupt status.
//!
//! \param intFlags is a bit mask of the interrupt sources to be cleared. Can
//! take the value \b MEMCFG_CERR_M4READ only. Other values are reserved.
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
    HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEINTCLR) = (MEMCFG_KEY | intFlags);
}

//*****************************************************************************
//
//! Gets the diagnostics corr/uncorr memory error status.
//!
//! \return Returns the diagnostics error status. It can return following
//! values: \b MEMCFG_DIAGERR_UNCORR_READ, \b MEMCFG_DIAGERR_UNCORR_WRITE,
//! \b MEMCFG_DIAGERR_CORR_READ and/or \b MEMCFG_DIAGERR_CORR_WRITE.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getDiagErrorStatus(void)
{
    //
    // Returns diag error status.
    //
    return(HWREG(CMMEMORYDIAGERROR_BASE + MEMCFG_O_DIAGERRFLG));
}

//*****************************************************************************
//
//! Clears the diagnostics corr/uncorr memory error status.
//!
//! \param stsFlags is a bit mask of the status flags to be cleared.
//!
//! This function clears the specified diagnostics corr/uncorr memory read/write
//! error flags. The param \e stsFlags can be any of the following values:
//! \b MEMCFG_DIAGERR_UNCORR_READ, \b MEMCFG_DIAGERR_UNCORR_WRITE,
//! \b MEMCFG_DIAGERR_CORR_READ and/or MEMCFG_DIAGERR_CORR_WRITE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MemCfg_clearDiagErrorStatus(uint32_t stsFlags)
{
    //
    // Clear diag error status.
    //
    HWREG(CMMEMORYDIAGERROR_BASE + MEMCFG_O_DIAGERRCLR ) |= stsFlags;
}

//*****************************************************************************
//
//! Gets address location of diagnostics corr/uncorr memory read/write error.
//!
//! \return Return address location of diagnostics corr/uncorr memory
//! read/write error.
//
//*****************************************************************************
static inline uint32_t
MemCfg_getDiagErrorAddress(void)
{
    //
    // Return diag error address.
    //
    return(HWREG(CMMEMORYDIAGERROR_BASE + MEMCFG_O_DIAGERRADDR));
}

//*****************************************************************************
//
//! Locks the write to the configuration of specified memory sections.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function locks writes to the init and test configuration of RAM
//! sections, test configuration of boot ROM & peripheral(EMAC & EtherCAT)
//! memory sections. That means calling MemCfg_setTestMode(),
//! MemCfg_initSections() for a locked RAM section; MemCfg_setTestMode() for
//! locked BootROM & peripheral memory will have no effect until
//! MemCfg_unlockConfig() is called.
//!
//! The \e ramSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_C0 through \b MEMCFG_SECT_C1 or \b MEMCFG_SECT_CX_ALL,
//! - \b MEMCFG_SECT_CMTOCPU1MSGRAM0 through \b MEMCFG_SECT_CMTOCPU2MSGRAM1 or
//!   \b MEMCFG_SECT_CMMSGX_ALL,
//! - \b MEMCFG_SECT_S0 through \b MEMCFG_SECT_S3, \b MEMCFG_SECT_E0 or
//!   \b MEMCFG_SECT_SX_ALL,
//! - \b MEMCFG_SECT_ROM,
//! - \b MEMCFG_SECT_PERIMEM_ALL,
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_lockConfig(uint32_t memSections);

//*****************************************************************************
//
//! Unlocks the writes to the configuration of specified memory sections.
//!
//! \param memSections is the logical OR of the sections to be configured.
//!
//! This function unlocks writes to the init and test configuration of RAM
//! sections, test configuration of boot ROM & peripheral(EMAC & EtherCAT)
//! memory sections that has been locked using MemCfg_lockConfig().
//!
//! The \e ramSections parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_C0 through \b MEMCFG_SECT_C1 or \b MEMCFG_SECT_CX_ALL,
//! - \b MEMCFG_SECT_CMTOCPU1MSGRAM0 through \b MEMCFG_SECT_CMTOCPU2MSGRAM1 or
//!   \b MEMCFG_SECT_CMMSGX_ALL,
//! - \b MEMCFG_SECT_S0 through \b MEMCFG_SECT_S3, \b MEMCFG_SECT_E0 or
//!   \b MEMCFG_SECT_SX_ALL,
//! - \b MEMCFG_SECT_ROM,
//! - \b MEMCFG_SECT_PERIMEM_ALL,
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
//!
//! \sa MemCfg_lockConfig()
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_unlockConfig(uint32_t memSections);

//*****************************************************************************
//
//! Sets the test mode of the specified memory section.
//!
//! \param memSection is the memory section to be configured.
//! \param testMode is the test mode selected.
//!
//! This function sets the test mode configuration of the RAM section. The
//! \e testMode parameter can take one of the following values:
//! - \b MEMCFG_TEST_FUNCTIONAL,
//! - \b MEMCFG_TEST_WRITE_DATA,
//! - \b MEMCFG_TEST_WRITE_ECC, or
//! - \b MEMCFG_TEST_FUNC_DIAG
//!
//! The \e ramSection parameter is one of the following indicators:
//! - \b MEMCFG_SECT_C0 through \b MEMCFG_SECT_C1 or \b MEMCFG_SECT_CX_ALL,
//! - \b MEMCFG_SECT_CMTOCPU1MSGRAM0 through \b MEMCFG_SECT_CMTOCPU2MSGRAM1 or
//!   \b MEMCFG_SECT_CMMSGX_ALL,
//! - \b MEMCFG_SECT_S0 through \b MEMCFG_SECT_S3, \b MEMCFG_SECT_E0 or
//!   \b MEMCFG_SECT_SX_ALL,
//! - \b OR use \b MEMCFG_SECT_ROM.
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
//! - \b MEMCFG_SECT_C0 through \b MEMCFG_SECT_C1 or \b MEMCFG_SECT_CX_ALL,
//! - \b MEMCFG_SECT_CMTOCPU1MSGRAM0 through \b MEMCFG_SECT_CMTOCPU2MSGRAM1 or
//!   \b MEMCFG_SECT_CMMSGX_ALL,
//! - \b MEMCFG_SECT_S0 through \b MEMCFG_SECT_S3, \b MEMCFG_SECT_E0 or
//!   \b MEMCFG_SECT_SX_ALL,
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
//! - \b MEMCFG_SECT_C0 through \b MEMCFG_SECT_C1 or \b MEMCFG_SECT_CX_ALL,
//! - \b MEMCFG_SECT_CMTOCPU1MSGRAM0 through \b MEMCFG_SECT_CMTOCPU2MSGRAM1 or
//!   \b MEMCFG_SECT_CMMSGX_ALL,
//! - \b MEMCFG_SECT_S0 through \b MEMCFG_SECT_S3, \b MEMCFG_SECT_E0 or
//!   \b MEMCFG_SECT_SX_ALL,
//! - \b OR use \b MEMCFG_SECT_ALL to configure all possible sections.
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
//! Forces parity error in the selected memory.
//!
//! \param memTypes is the logical OR of the sections to be tested.
//!
//! This function forces the parity error in the memories specified
//! by the \e memTypes parameter.
//!
//! The \e memTypes parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_ROM,
//! - \b MEMCFG_SECT_PERIMEM_EMAC,
//! - \b MEMCFG_SECT_PERIMEM_ETHERCAT, or
//! - \b OR use \b MEMCFG_SECT_ALL to get status of all possible sections.
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_forceMemError(uint32_t memTypes);

//*****************************************************************************
//
//! Enables test mode for selected peripheral memories.
//!
//! \param memTypes is the logical OR of the memories to be tested.
//!
//! This function enables test mode for selected peripheral memories specified
//! by the \e memTypes parameter.
//!
//! The \e memTypes parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_PERIMEM_EMAC,
//! - \b MEMCFG_SECT_PERIMEM_ETHERCAT, or
//! - \b MEMCFG_SECT_PERIMEM_ALL
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_enablePeriMemTestMode(uint32_t memTypes);

//*****************************************************************************
//
//! Disables the test mode for selected peripheral memories.
//!
//! \param memTypes is the logical OR of the memories to be tested.
//!
//! This function disables test mode for selected peripheral memories specified
//! by the \e memTypes parameter.
//!
//! The \e memTypes parameter is an OR of one of the following sets of
//! indicators:
//! - \b MEMCFG_SECT_PERIMEM_EMAC,
//! - \b MEMCFG_SECT_PERIMEM_ETHERCAT, or
//! - \b MEMCFG_SECT_PERIMEM_ALL
//!
//! \return None.
//
//*****************************************************************************
extern void
MemCfg_disablePeriMemTestMode(uint32_t memTypes);

//*****************************************************************************
//
//! Gets the address location of uncorrectable memory read/write error.
//!
//! \param stsFlag is the error for which address needs to be returned.
//!
//! This function returns the address location of uncorrectable read/write
//! error for the specified error. The parameter \e stsFlag can be any of the
//! \b MEMCFG_UCERR_M4READ, \b MEMCFG_UCERR_M4WRITE, \b MEMCFG_UCERR_EMACREAD,
//! \b MEMCFG_UCERR_EMACWRITE,\b MEMCFG_UCERR_UDMAREAD,
//! \b MEMCFG_UCERR_UDMAWRITE, \b MEMCFG_UCERR_ETHERCATMEMREAD or/and
//! \b MEMCFG_UCERR_EMACMEMREAD values.
//!
//! \return Return address location of uncorrectable read/write error.
//
//*****************************************************************************
extern uint32_t
MemCfg_getUncorrErrorAddress(uint32_t stsFlag);

//*****************************************************************************
//
//! Gets the address location of correctable memory read/write error.
//!
//! \param stsFlag is the error for which address needs to be returned.
//!
//! This function returns the address location of correctable read/write
//! error for the specified error. The param \e stsFlag can take any of the
//! \b MEMCFG_CERR_M4READ, \b MEMCFG_CERR_M4WRITE, \b MEMCFG_CERR_EMACREAD,
//! MEMCFG_CERR_EMACWRITE, \b MEMCFG_CERR_UDMAREAD and/or
//! \b MEMCFG_CERR_UDMAWRITE values.
//!
//! \return Return address location of correctable read/write error.
//
//*****************************************************************************
extern uint32_t
MemCfg_getCorrErrorAddress(uint32_t stsFlag);

//*****************************************************************************
//
//! Gets the bus fault address for the selected bus master.
//!
//! \param busMaster specifies the bus masters for which fault address is to be
//! returned.
//!
//! This function return the bus fault address for selected bus master. The
//! parameter \e busMaster can be any of the following values:
//! \b MEMCFG_BUSMASTER_M4, MEMCFG_BUSMASTER_UDMA, or MEMCFG_BUSMASTER_EMAC.
//!
//! \return Returns bus fault address for the selected bus master.
//
//*****************************************************************************
extern uint32_t
MemCfg_getBusFaultAddress(uint32_t busMaster);

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
