//###########################################################################
//
// FILE:   lcm.h
//
// TITLE:  C28x LCM config driver.
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

#ifndef LCM_H
#define LCM_H

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

#ifdef __TMS320C28XX__

//*****************************************************************************
//
//! \addtogroup lcm_api LCM
//! \brief This module is used for LockStep Compare Module (LCM) configuration
//! @{
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_lcm.h"
#include "debug.h"


//*****************************************************************************
//
//! LCM status used as return value by the driver functions
//
//*****************************************************************************
typedef enum
{
    LCM_PASS,
    LCM_FAIL,
    LCM_NOT_RUN
} LCM_Status;


//*****************************************************************************
//
//! LCM Flags that can be used as \e flags parameter to LCM_clearLCMFlags
//! function
//
//*****************************************************************************
#define LCM_FLAG_CMP_FAIL              0x2U
#define LCM_FLAG_STPASS                0x10000U
#define LCM_FLAG_STDONE                0x20000U
#define LCM_FLAG_CMP1_ERR_FORCE_PASS   0x80000U
#define LCM_FLAG_CMP1_ERR_FORCE_DONE   0x100000U
#define LCM_FLAG_CMP2_ERR_FORCE_PASS   0x200000U
#define LCM_FLAG_CMP2_ERR_FORCE_DONE   0x400000U


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \internal
//! Checks LCM base address.
//!
//! \param base specifies the LCM module base address.
//!
//! This function determines if an LCM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
LCM_isBaseValid(uint32_t base)
{
      return((base == LCM_CPU2_BASE) || (base == LCM_CPU2_DMA1_BASE));
}
#endif

//*****************************************************************************
//
//! Enables LockStep Compare
//!
//! \param base is the base address of the LCM module.
//!
//! \return none
//!
//
//*****************************************************************************
static inline void
LCM_enableLockstepCompare(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    HWREGH(base + LCM_O_CONTROL) = LCM_CONTROL_CMPEN;
}

//*****************************************************************************
//
//! Disables LockStep Compare
//!
//! \param base is the base address of the LCM module.
//!
//! \return none
//!
//
//*****************************************************************************
static inline void
LCM_disableLockstepCompare(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    HWREGH(base + LCM_O_CONTROL) = 0U;
}

//*****************************************************************************
//
//! Return the lock step configuration status
//!
//! \param base is the base address of the LCM module.
//!
//! \return true if lockstep is enabled, false if lockstep is disabled
//!
//
//*****************************************************************************
static inline bool
LCM_isLockStepEnabled(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    return((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_LSEN) != 0U);
}


//*****************************************************************************
//
//! Return the debugger connection status
//!
//! \param base is the base address of the LCM module.
//!
//! - When debugger is connected, lockstep comparison of the CPU is disabled.
//! - Self-test can still be performed with debugger connected.
//! - Error forcing mode cannot be checked with debugger connected
//!
//! \return true if debugger is connected, false if not
//!
//
//*****************************************************************************
static inline bool
LCM_isDebuggerConnected(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    return((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_DBGCON) != 0U);
}

//*****************************************************************************
//
//! Return the Lockstep compare status
//!
//! \param base is the base address of the LCM module.
//!
//! \return LCM_PASS - if lockstep compare fail flag is not set,
//!         LCM_FAIL - if lockstep compare fail flag is set
//!
//
//*****************************************************************************
static inline LCM_Status
LCM_getLockStepCompareStatus(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    return(((HWREG_BP(base + LCM_O_STATUS) & LCM_STATUS_CMP_FAIL) == 0U) ?
           LCM_PASS : LCM_FAIL);
}


//*****************************************************************************
//
//! Returns the self test status
//!
//! \param base is the base address of the LCM module.
//!
//! \return LCM_NOT_RUN - if the self test is not run or is in progress,
//!         LCM_FAIL    - if the self test has failed
//!         LCM_PASS    - if the self test has passed
//!
//
//*****************************************************************************
static inline LCM_Status
LCM_getSelfTestStatus(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    uint32_t st = HWREG_BP(base + LCM_O_STATUS);

    return(
        ((st & LCM_STATUS_STDONE) == 0U) ? LCM_NOT_RUN :
        ((st & LCM_STATUS_STPASS) == 0U) ? LCM_FAIL : LCM_PASS
    );
}

//*****************************************************************************
//
//! Returns the Comparator 1 error forcing Test status
//!
//! \param base is the base address of the LCM module.
//!
//! \return LCM_NOT_RUN - if the self test is not run or is in progress,
//!         LCM_FAIL    - if the self test has failed
//!         LCM_PASS    - if the self test has passed
//
//*****************************************************************************
static inline LCM_Status
LCM_getComp1ErrForceTestStatus(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    uint32_t st = HWREG_BP(base + LCM_O_STATUS);

    return(
        ((st & LCM_STATUS_CMP1_ERR_FORCE_DONE) == 0U) ? LCM_NOT_RUN :
        ((st & LCM_STATUS_CMP1_ERR_FORCE_PASS) == 0U) ? LCM_FAIL : LCM_PASS
    );
}

//*****************************************************************************
//
//! Returns the Comparator 2 error forcing Test status
//!
//! \param base is the base address of the LCM module.
//!
//! \return LCM_NOT_RUN - if the self test is not run or is in progress,
//!         LCM_FAIL    - if the self test has failed
//!         LCM_PASS    - if the self test has passed
//
//*****************************************************************************
static inline LCM_Status
LCM_getComp2ErrForceTestStatus(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    uint32_t st = HWREG_BP(base + LCM_O_STATUS);

    return(
        ((st & LCM_STATUS_CMP2_ERR_FORCE_DONE) == 0U) ? LCM_NOT_RUN :
        ((st & LCM_STATUS_CMP2_ERR_FORCE_PASS) == 0U) ? LCM_FAIL : LCM_PASS
    );
}

//*****************************************************************************
//
//! Clears the specified LCM flags
//!
//! \param base is the base address of the LCM module.
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_clearFlags(uint32_t base, uint32_t flags)
{
    ASSERT(LCM_isBaseValid(base));

    HWREG_BP(base + LCM_O_STATUS_CLEAR) = flags;
}

//*****************************************************************************
//
//! Enable parity test.
//!
//! \param base is the base address of the LCM module.
//!
//! When the parity test feature is enabled, actual registers are not accessible
//! in the memory map. Instead, the parity values (final XOR output indicating
//! the parity error) are accessible. Parity is computed for every byte and the
//! corresponding parity value is available at the bit-0 of every byte
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_enableParityTest(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    HWREGH(base + LCM_O_PARITY_TEST) = 0xA;
}

//*****************************************************************************
//
//! Disable parity test.
//!
//! \param base is the base address of the LCM module.
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_disableParityTest(uint32_t base)
{
    ASSERT(LCM_isBaseValid(base));

    HWREGH(base + LCM_O_PARITY_TEST) = 0x5;
}

//*****************************************************************************
//
//! Lock registers
//!
//! \param base is the base address of the LCM module.
//! \param regs is the logical OR of the registers to be locked
//!             - LCM_LOCK_LCM_CONTROL
//!             - LCM_LOCK_LCM_STATUS_CLEAR
//!             - LCM_LOCK_PARITY_TEST
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_lockRegister(uint32_t base, uint32_t regs)
{
    ASSERT(LCM_isBaseValid(base));

    HWREG_BP(base + LCM_O_LOCK) |= regs;
}

//*****************************************************************************
//
//! Unlock registers
//!
//! \param base is the base address of the LCM module.
//! \param regs is the logical OR of the registers to be unlocked.
//!             - LCM_LOCK_LCM_CONTROL
//!             - LCM_LOCK_LCM_STATUS_CLEAR
//!             - LCM_LOCK_PARITY_TEST
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_unlockRegister(uint32_t base, uint32_t regs)
{
    ASSERT(LCM_isBaseValid(base));

    HWREG_BP(base + LCM_O_LOCK) &= ~regs;
}


//*****************************************************************************
//
//! Commit registers
//!
//! \param base is the base address of the LCM module.
//! \param regs is the logical OR of the registers to be committed.
//!             - LCM_COMMIT_LCM_CONTROL
//!             - LCM_COMMIT_LCM_STATUS_CLEAR
//!             - LCM_COMMIT_PARITY_TEST
//!
//! \return None
//
//*****************************************************************************
static inline void
LCM_commitRegister(uint32_t base, uint32_t regs)
{
    ASSERT(LCM_isBaseValid(base));

    HWREG_BP(base + LCM_O_COMMIT) &= ~regs;
}


//*****************************************************************************
//
//! Runs LCM Self test.
//!
//! \param base is the base address of the LCM module.
//!
//! The test cannot be run if lockstep feature is disabled, or if there are
//! pending functional failure or test failure. This function checks if there
//! are any pending failures, runs the self test and returns the test status.
//!
//! Once the test is initiated, both the comparators will be tested one after
//! the other. It should be possible to execute this test with debugger
//! connected.
//!
//! \note This function clears the status flags at the end of the test
//!
//! \return - LCM_NOT_RUN - if the self test is not run
//!         - LCM_FAIL    - if the self test has failed
//!         - LCM_PASS    - if the self test has passed
//!
//
//*****************************************************************************
extern LCM_Status
LCM_runSelfTest(uint32_t base);

//*****************************************************************************
//
//! Runs Comparator 1 Error Force Test.
//!
//! \param base is the base address of the LCM module.
//!
//! The test cannot be run if lockstep feature is disabled, or if there are
//! pending functional failure or test failure. This function checks if there
//! are any pending failures, runs the self test and returns the test status.
//!
//! Once the test is triggered, comparator 1 compare error output will be
//! asserted for one cycle. This feature is used to check the error propagation
//! path from comparator 1 compare error output to the observation point
//! defined in system control.
//!
//! This function generates an NMI and needs to be serviced by the application.
//! The function LCM_getComp1ErrForceTestStatus() can be used to check the
//! status in the NMI handler
//!
//! \note This function clears the status flags at the end of the test
//! \note It is NOT possible to execute this test with debugger connected.
//!
//! \return LCM_NOT_RUN - if the self test is not run
//!         LCM_FAIL    - if the self test has failed
//!         LCM_PASS    - if the self test has passed
//!
//
//*****************************************************************************
extern LCM_Status
LCM_runComp1ErrorForceTest(uint32_t base);

//*****************************************************************************
//
//! Runs Comparator 2 Error Force Test.
//!
//! \param base is the base address of the LCM module.
//!
//! The test cannot be run if lockstep feature is disabled, or if there are
//! pending functional failure or test failure. This function checks if there
//! are any pending failures, runs the self test and returns the test status.
//!
//! Once the test is triggered, comparator 1 compare error output will be
//! asserted for one cycle. This feature is used to check the error propagation
//! path from comparator 1 compare error output to the observation point
//! defined in system control.
//!
//! This function generates an NMI and needs to be serviced by the application.
//! The function LCM_getComp1ErrForceTestStatus() can be used to check the
//! status in the NMI handler
//!
//! \note This function clears the status flags at the end of the test
//! \note It is NOT possible to execute this test with debugger connected.
//!
//! \return LCM_NOT_RUN - if the self test is not run
//!         LCM_FAIL    - if the self test has failed
//!         LCM_PASS    - if the self test has passed
//!
//
//*****************************************************************************
extern LCM_Status
LCM_runComp2ErrorForceTest(uint32_t base);


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif // #ifdef __TMS320C28XX__

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // LCM_H

