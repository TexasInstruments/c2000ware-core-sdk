//###########################################################################
//
// FILE:   clapromcrc.h
//
// TITLE:  C28x and CLA CLAPROMCRC driver.
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

#ifndef CLAPROMCRC_H
#define CLAPROMCRC_H

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
//! \addtogroup clapromcrc_api CLAPROMCRC
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_clapromcrc.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
//! Values that can be passed to CLAPROMCRC_setEmulationMode().
//
//*****************************************************************************
typedef enum
{
    CLAPROMCRC_MODE_SOFT = 0x00,    //!< Soft Mode
    CLAPROMCRC_MODE_FREE = 0x10     //!< Free Mode
} CLAPROMCRC_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to CLAPROMCRC_getInterruptStatus() and
//! CLAPROMCRC_clearInterruptFlag().
//
//*****************************************************************************
typedef enum
{
    CLAPROMCRC_INT_FLG = 0x01,      //!< Global Interrupt Flag
    CLAPROMCRC_CRCDONE_FLG = 0x02   //!< CRCDONE Interrupt Flag
} CLAPROMCRC_IntFlag;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an CLAPROMCRC base address.
//!
//! \param base specifies the CLAPROMCRC module base address.
//!
//! This function determines if the CLAPROMCRC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CLAPROMCRC_isBaseValid(uint32_t base)
{
    return((base == CLA1PROMCRC_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the Emulation Mode.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param emulationMode is soft mode or free mode.  It can take values
//!   CLAPROMCRC_MODE_SOFT or CLAPROMCRC_MODE_FREE.
//!
//! This function sets the emulation mode which controls the behaviour of the
//! CRC32 calculation during emulation. CLAPROMCRC_MODE_SOFT mode will stop the
//! CLAPROMCRC module on CLA debug suspend.  CLAPROMCRC_MODE_FREE mode sets the
//! CLAPROMCRC module so that the CRC32 calculation is not affected by debug
//! halt of the CLA.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_setEmulationMode(uint32_t base,
                            CLAPROMCRC_EmulationMode emulationMode)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Clear the FREE_SOFT bit.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) &=
            ~(CLAPROMCRC_CRC32_CONTROLREG_FREE_SOFT);

    //
    // Write the emulation mode to the FREE_SOFT bit.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) =
            HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) |
            (uint16_t)emulationMode;
    EDIS;
}

//*****************************************************************************
//
//! Starts the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function starts CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_start(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Write to the START bit.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) |=
                    CLAPROMCRC_CRC32_CONTROLREG_START;
    EDIS;
}

//*****************************************************************************
//
//! Halts the CRC32 calculations.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function halts the CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_halt(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Write to the HALT bit.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) |=
                    CLAPROMCRC_CRC32_CONTROLREG_HALT;
    EDIS;
}

//*****************************************************************************
//
//! Resumes the CRC32 calculations.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function resumes the CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_resume(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Clear the HALT bit.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CONTROLREG) &=
                    ~(CLAPROMCRC_CRC32_CONTROLREG_HALT);
    EDIS;
}

//*****************************************************************************
//
//! Sets the Block Size of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param blockSize is the number of KB.  The maximum value is 128 KB
//!
//! This function sets the block size for the CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_setBlockSize(uint32_t base, uint16_t blockSize)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    ASSERT((blockSize > 0U));
    ASSERT((blockSize <= 128U));
    EALLOW;

    //
    // Clear the BLOCKSIZE field.
    //
    HWREG(base + CLAPROMCRC_O_CRC32_CONTROLREG) &=
                    ~((uint32_t)CLAPROMCRC_CRC32_CONTROLREG_BLOCKSIZE_M);

    //
    // Subtract 1 from blockSize and write it to the BLOCKSIZE field.
    //
    HWREG(base + CLAPROMCRC_O_CRC32_CONTROLREG) |=
                    (((uint32_t)blockSize - 1UL) <<
                        CLAPROMCRC_CRC32_CONTROLREG_BLOCKSIZE_S) &
                        CLAPROMCRC_CRC32_CONTROLREG_BLOCKSIZE_M;
    EDIS;
}

//*****************************************************************************
//
//! Sets the Start Address of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param startAddress defines the starting point for the CRC32 calculation.
//! A startAddress corresponding to the CLA memory map is to be used.
//! startAddress has to be a 1KB aligned address.  If it is not aligned, then
//! the LSB bits are ignored to get a 1KB aligned address.
//!
//! This function sets the start address with \e startAddress for the CRC32
//! calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_setStartAddress(uint32_t base, uint32_t startAddress)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Write the STARTADDRESS register.
    //
    HWREG(base + CLAPROMCRC_O_CRC32_STARTADDRESS) = startAddress;
    EDIS;
}

//*****************************************************************************
//
//! Sets the Seed of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param seed is the initial value of the CRC32 calculation.
//!
//! This function sets the seed with \e Seed for CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_setSeed(uint32_t base, uint32_t seed)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Write to the SEED register.
    //
    HWREG(base + CLAPROMCRC_O_CRC32_SEED) = seed;
    EDIS;
}

//*****************************************************************************
//
//! Gets the Current Address of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function returns the current CLA memory map address of the data fetch
//! unit of the CLAPROMCRC.
//!
//! \return Returns the current address.
//
//*****************************************************************************
static inline uint16_t
CLAPROMCRC_getCurrentAddress(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Returns the lower 16 bits of STATUSREG which corresponds to the
    // CURRENTADDR field.
    //
    return(HWREGH(base + CLAPROMCRC_O_CRC32_STATUSREG));
}

//*****************************************************************************
//
//! Check the status of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function returns the status for the CLAPROMCRC.  Return value of true
//! means PASS.  Return value of false means FAIL.  The comparison is enabled
//! after CRC calculation is completed.
//!
//! \return Returns true (PASS) or false (FAIL) as the status of the CRC32
//! calculation.
//
//*****************************************************************************
static inline bool
CLAPROMCRC_checkStatus(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // If the CRCCHECKSTATUS bit is set, then return false corresponding to
    // FAIL.
    //
    return(!((HWREG(base + CLAPROMCRC_O_CRC32_STATUSREG) &
              CLAPROMCRC_CRC32_STATUSREG_CRCCHECKSTATUS) ==
             CLAPROMCRC_CRC32_STATUSREG_CRCCHECKSTATUS));
}

//*****************************************************************************
//
//! Gets the Run Status of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function returns the run status for the CLAPROMCRC with the base
//! address passed in the \e base parameter.  Return value of false means IDLE.
//! Return value of true means ACTIVE.
//!
//! \return Returns true (Active) or false (Idle) as the run status of the
//! CRC32 calculation.
//
//*****************************************************************************
static inline bool
CLAPROMCRC_getRunStatus(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // If the RUNSTATUS bit is set, then return true corresponding to Active.
    //
    return((HWREG(base + CLAPROMCRC_O_CRC32_STATUSREG) &
                 CLAPROMCRC_CRC32_STATUSREG_RUNSTATUS) ==
                 CLAPROMCRC_CRC32_STATUSREG_RUNSTATUS);
}

//*****************************************************************************
//
//! Gets the Result of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function returns the result of the CRC32 calculation.
//!
//! \return Returns the result of the CRC32 calculation.
//
//*****************************************************************************
static inline uint32_t
CLAPROMCRC_getResult(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Return the 32-bit CRCRESULT register.
    //
    return(HWREG(base + CLAPROMCRC_O_CRC32_CRCRESULT));
}

//*****************************************************************************
//
//! Sets the Golden CRC of the CRC32 calculation.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param goldenCRC is value which will be compared with CRCRESULT.
//!
//! This function sets the GOLDENCRC register with \e goldenCRC for the
//! CLAPROMCRC module.  The value of GOLDENCRC is compared with CRCRESULT to
//! determine a PASS or FAIL.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_setGoldenCRC(uint32_t base, uint32_t goldenCRC)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Write goldenCRC to the GOLDENCRC register.
    //
    HWREG(base + CLAPROMCRC_O_CRC32_GOLDENCRC) = goldenCRC;
}

//*****************************************************************************
//
//! Disables Interrupts the CRC32 calculations.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function disables interrupts for the CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_disableDoneInterrupt(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Disable the CRCDONE interrupt.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_INTEN) &=
                    ~CLAPROMCRC_CRC32_INTEN_CRCDONE;
    EDIS;
}

//*****************************************************************************
//
//! Enables Interrupts the CRC32 calculations.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function enables interrupts for the CRC32 calculation.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_enableDoneInterrupt(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));
    EALLOW;

    //
    // Enable the CRCDONE interrupt.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_INTEN) |=
                    CLAPROMCRC_CRC32_INTEN_CRCDONE;
    EDIS;
}

//*****************************************************************************
//
//! Gets the Interrupt Status of of flag.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param intFlag is a CLAPROMCRC_IntFlag type and is either
//! CLAPROMCRC_INT_FLG or CLAPROMCRC_CRCDONE_FLG.
//!
//! This function returns the interrupt status for \e intFlag. Return value of
//! false means no interrupt generated.  Return value of true means interrupt
//! was generated.
//!
//! \return Returns the interrupt status.  True means interrupt was generated
//! and false means no interrupt was generated.
//
//*****************************************************************************
static inline bool
CLAPROMCRC_getInterruptStatus(uint32_t base, CLAPROMCRC_IntFlag intFlag)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Return the status of the interrupt flag.
    //
    return((HWREGH(base + CLAPROMCRC_O_CRC32_FLG) & (uint16_t)intFlag ) ==
            (uint16_t)intFlag);
}

//*****************************************************************************
//
//! Clears the Global Interrupt Flag of the CLAPROMCRC.
//!
//! \param base is the base address of the CLAPROMCRC module.
//! \param intFlag is either CLAPROMCRC_INT_FLG or CLAPROMCRC_CRCDONE_FLG.
//!
//! This function clears the interrupt flag for the CLAPROMCRC with the base
//! address passed in the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CLAPROMCRC_clearInterruptFlag(uint32_t base, CLAPROMCRC_IntFlag intFlag)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Clear the interrupt flag.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_CLR) =
           HWREGH(base + CLAPROMCRC_O_CRC32_CLR) | (uint16_t)intFlag;
}

//*****************************************************************************
//
//! Force the CRCDONE Interrupt Flag of the CLAPROMCRC.
//!
//! \param base is the base address of the CLAPROMCRC module.
//!
//! This function forces the CRCDONE interrupt flag for the CLAPROMCRC with the
//! base address passed in the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CLAPROMCRC_forceDoneFlag(uint32_t base)
{
    ASSERT(CLAPROMCRC_isBaseValid(base));

    //
    // Force the CRCDONE interrupt flag.
    //
    HWREGH(base + CLAPROMCRC_O_CRC32_FRC) |= CLAPROMCRC_CRC32_FRC_CRCDONE;
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

#endif // CLAPROMCRC_H
