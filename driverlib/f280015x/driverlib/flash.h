//###########################################################################
//
// FILE:   flash.h
//
// TITLE:  C28x Flash driver.
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

#ifndef FLASH_H
#define FLASH_H

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
#ifndef __TMS320C28XX_CLA__

//*****************************************************************************
//
//! \addtogroup flash_api Flash
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_flash.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#ifndef __cplusplus
#pragma CODE_SECTION(Flash_disableCache, ".TI.ramfunc");
#pragma CODE_SECTION(Flash_disablePrefetch, ".TI.ramfunc");
#pragma CODE_SECTION(Flash_setWaitstates, ".TI.ramfunc");
#pragma CODE_SECTION(Flash_enableCache, ".TI.ramfunc");
#pragma CODE_SECTION(Flash_enablePrefetch, ".TI.ramfunc");
#pragma CODE_SECTION(Flash_enableECC, ".TI.ramfunc");
#endif

//*********************************
//
//! Flash Trim Defines
//
//**********************************
// Flash Configuration Base
#define FLASHCONFIG_BASE                                    0x00051000U



// Trim Control Register  
#define FLASH_O_TRIMCTL                                     0x1600U
// Trim Lock Register      
#define FLASH_O_TRIMLOCK                                    0x1604U
// Trim Commit Register      
#define FLASH_O_TRIMCOMMIT                                  0x1608U


#define FLASH_TRIMCTL_ENABLE_M                              0x1U      
#define FLASH_TRIMCTL_ENABLE_S                              0x0U      
#define FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_M         0x3U      
#define FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_S         0x0U      
#define FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_M   0x3U      
#define FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_S   0x0U      


//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************
#define    FLASH_DELAY_CONFIG     __asm(" RPT #7 || NOP")

//*****************************************************************************
//
// Values used for enabling/disabling ECC Test Logic
//
//*****************************************************************************
#define FLASH_SINGLE_BIT_ECC_TEST_EN   0x1U // Enable ECC Single Bit Test Logic
#define FLASH_DOUBLE_BIT_ECC_TEST_EN   0x3U // Enable ECC Double Bit Test Logic
//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks a flash wrapper base address for the control registers.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! This function determines if a flash wrapper control base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
Flash_isCtrlBaseValid(uint32_t ctrlBase)
{
    return((ctrlBase == FLASH0CTRL_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks a flash wrapper base address for the ECC registers.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! This function determines if a flash wrapper ECC base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
Flash_isECCBaseValid(uint32_t eccBase)
{
    return((eccBase == FLASH0ECC_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the random read wait state amount.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param waitstates is the wait-state value.
//!
//! This function sets the number of wait states for a flash read access. The
//! \e waitstates parameter is a number between 0 and 15. It is \b important
//! to look at your device's datasheet for information about what the required
//! minimum flash wait-state is for your selected SYSCLK frequency.
//!
//! By default the wait state amount is configured to the maximum 15.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_setWaitstates(uint32_t ctrlBase, uint16_t waitstates)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    //
    // waitstates is 4 bits wide.
    //
    ASSERT(waitstates <= 0xFU);

    EALLOW;
    //
    // Write flash read wait-state amount to appropriate register.
    //
    HWREG(ctrlBase + FLASH_O_FRDCNTL) =
        (HWREG(ctrlBase + FLASH_O_FRDCNTL) &
         ~(uint32_t)FLASH_FRDCNTL_RWAIT_M) |
         ((uint32_t)waitstates << FLASH_FRDCNTL_RWAIT_S);
    EDIS;
}

//*****************************************************************************
//
//! Enables prefetch mechanism.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_enablePrefetch(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    EALLOW;

    //
    // Set the prefetch enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) |=
            FLASH_FRD_INTF_CTRL_PREFETCH_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables prefetch mechanism.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_disablePrefetch(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    EALLOW;

    //
    // Clear the prefetch enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_PREFETCH_EN;
    EDIS;
}

//*****************************************************************************
//
//! Enables data cache.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_enableCache(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    EALLOW;

    //
    // Set the data cache enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) |=
            FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables data cache.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_disableCache(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    EALLOW;

    //
    // Clear the data cache enable bit.
    //
    HWREG(ctrlBase + FLASH_O_FRD_INTF_CTRL) &=
            ~(uint32_t)FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;
    EDIS;
}

//*****************************************************************************
//
//! Sets the FLWEPROT value of the FLPROT register.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_setFLWEPROT(uint32_t ctrlBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isCtrlBaseValid(ctrlBase));

    EALLOW;

    //
    // Set the FLWEPROT value from the FLPROT register.
    //
    HWREG(ctrlBase + FLASH_O_FLPROT) &= ~(uint32_t)FLASH_FLPROT_FLWEPROT;
    HWREG(ctrlBase + FLASH_O_FLPROT) |= (uint32_t)FLASH_FLPROT_FLWEPROT;

    EDIS;
}

//*****************************************************************************
//
//! Enables flash error correction code (ECC) protection.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#endif
static inline void
Flash_enableECC(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    EALLOW;

    //
    // Write the key value 0xA to ECC_ENABLE register.
    //
    HWREG(eccBase + FLASH_O_ECC_ENABLE) =
        (HWREG(eccBase + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_ENABLE_M) | 0xAU;
    EDIS;
}

//*****************************************************************************
//
//! Disables flash error correction code (ECC) protection.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_disableECC(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    EALLOW;

    //
    // Clear ECC enable field with the one's complement of the key.
    //
    HWREG(eccBase + FLASH_O_ECC_ENABLE) =
        (HWREG(eccBase + FLASH_O_ECC_ENABLE) &
         ~(uint32_t)FLASH_ECC_ENABLE_ENABLE_M) | 0x5U;
    EDIS;
}



//*****************************************************************************
//
//! Enables Single Bit ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_enableSingleBitECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Set the ECC test mode bit.
    //
    EALLOW;
    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
    FLASH_SINGLE_BIT_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Enables Double Bit ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_enableDoubleBitECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Set the ECC test mode bit.
    //
    EALLOW;
    HWREG(eccBase + FLASH_O_FECC_CTRL) |=
    FLASH_DOUBLE_BIT_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables Single Bit ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_disableSingleBitECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Clear the ECC test mode bit.
    //
    EALLOW;
    HWREG(eccBase + FLASH_O_FECC_CTRL) &=
    ~(uint32_t)FLASH_SINGLE_BIT_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables Double Bit ECC Test mode.
//!
//! \param eccBase is the base address of the flash wrapper ECC registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Flash_disableDoubleBitECCTestMode(uint32_t eccBase)
{
    //
    // Check the arguments.
    //
    ASSERT(Flash_isECCBaseValid(eccBase));

    //
    // Clear the ECC test mode bit.
    //
    EALLOW;
    HWREG(eccBase + FLASH_O_FECC_CTRL) &=
    ~(uint32_t)FLASH_DOUBLE_BIT_ECC_TEST_EN;
    EDIS;
}

//*****************************************************************************
//
//! Initializes the flash control registers.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//! \param eccBase is the base address of the flash wrapper ECC registers.
//! \param waitstates is the wait-state value.
//!
//! This function initializes the flash control registers. At reset bank and
//! pump are in sleep.  A flash access will power up the bank and pump
//! automatically. This function will power up Flash bank and pump and set the
//! fallback mode of flash and pump as active.
//!
//! This function also sets the number of wait-states for a flash access
//! (see Flash_setWaitstates() for more details), and enables cache, the
//! prefetch mechanism, and ECC.
//!
//! \return None.
//
//*****************************************************************************
extern void
Flash_initModule(uint32_t ctrlBase, uint32_t eccBase, uint16_t waitstates);

//*****************************************************************************
//
//! Initializes the flash trim registers.
//!
//! \return None.
//!
//!
//*****************************************************************************
static inline void 
Flash_writeTrims(uint32_t reg_offset, uint32_t mask, 
                 uint32_t shift, uint32_t value)
{

    EALLOW;
    //
    // Set the requested bits to the value.
    //
    HWREG_BP(FLASHCONFIG_BASE + reg_offset) &= ~(uint32_t)mask;

	HWREG_BP(FLASHCONFIG_BASE + reg_offset) |= ((uint32_t)value << shift);

    EDIS;
} 


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif  // #ifdef __TMS320C28XX_CLA__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // FLASH_H
