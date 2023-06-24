//###########################################################################
//
// FILE:   cpu.h
//
// TITLE:  Instruction wrappers for special CPU instructions needed by the
//         drivers.
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

#ifndef CPU_H
#define CPU_H

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
//! \addtogroup cpu_api CPU
//! \brief The module is used for configuring Cortex-M core registers
//! @{
//
//*****************************************************************************
#include <stdint.h>

//
// Define for no operation
//
#ifndef NOP
#define NOP    __asm(" NOP")
#endif

//*****************************************************************************
//
//! Returns the state of FAULTMASK register on entry and disable all
//! interrupts except NMI.
//!
//! This function is wrapper function for the CPSID instruction. It returns
//! the state of FAULTMASK on entry and disable all interrupts except NMI.
//!
//! \return Returns the state of FAULTMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_setFAULTMASK(void)
{
    //
    // Disable interrupts and return previous FAULTMASK.
    //
    return(_disable_interrupts());
}

//*****************************************************************************
//
//! Returns the state of FAULTMASK register
//!
//! This function is wrapper function for returning the state of FAULTMASK
//! register(indicating whether interrupts except NMI are enabled or disabled).
//!
//! \return Returns the state of FAULTMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_getFAULTMASK(void)
{
    //
    // Read FAULTMASK register.
    //
    __asm("    mrs     r0, FAULTMASK\n"
          "    bx      lr\n");

    //
    // The following keeps the compiler happy, because it wants to see a
    // return value from this function.  It will generate code to return
    // a zero.  However, the real return is the "bx lr" above, so the
    // return(0) is never executed and the function returns with the value
    // you expect in R0.
    //
    return(0U);
}

//*****************************************************************************
//
//! Returns the state of FAULTMASK register and enable the interrupts
//!
//! This function is wrapper function for returning the state of FAULTMASK
//! register and enabling the interrupts.
//!
//! \return Returns the state of FAULTMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_clearFAULTMASK(void)
{
    //
    // Enable interrupts and return previous FAULTMASK status.
    //
    return(_enable_interrupts());
}

//*****************************************************************************
//
//! Returns the state of PRIMASK register on entry and disable interrupts
//!
//! This function is wrapper function for the CPSID instruction. It returns
//! the state of PRIMASK on entry and disable interrupts.
//!
//! \return Returns the state of PRIMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_setPRIMASK(void)
{
    //
    // Read PRIMASK and Disable interrupts.
    //
    return(_disable_IRQ());
}

//*****************************************************************************
//
//! Returns the state of PRIMASK register
//!
//! This function is wrapper function for returning the state of PRIMASK
//! register(indicating whether interrupts are enabled or disabled).
//!
//! \return Returns the state of PRIMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_getPRIMASK(void)
{
    //
    // Return PRIMASK register status.
    //
    return(__get_PRIMASK());
}

//*****************************************************************************
//
//! Returns the state of PRIMASK register and enable the interrupts
//!
//! This function is wrapper function for returning the state of PRIMASK
//! register and enabling the interrupts.
//!
//! \return Returns the state of PRIMASK register.
//
//*****************************************************************************
static inline uint32_t
CPU_clearPRIMASK(void)
{
    //
    // Enable interrupts and return previous PRIMASK setting.
    //
    return(_enable_IRQ());
}

//*****************************************************************************
//
//! Wrapper function for the WFI instruction
//!
//! This function is wrapper function for the WFI instruction.
//!
//! \return None
//
//*****************************************************************************
static inline void
CPU_wfi(void)
{
    //
    // Wait for the next interrupt.
    //
    __asm("    wfi\n");
}

//*****************************************************************************
//
//! Writes the BASEPRI register
//!
//! \param basePriority is the value to be set
//!
//! This function is wrapper function for writing the BASEPRI register. MSB
//! 3-bits are enabled for setting the priority and non-implemented low-order
//! bits read as zero and ignore writes. To set the base priority of 0x2U,
//! the param \e basePriority to be passed should be 0x20U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CPU_setBASEPRI(uint32_t basePriority)
{
    //
    // Set the BASEPRI register
    //
    _set_interrupt_priority(basePriority);
}

//*****************************************************************************
//
//! Returns the state of BASEPRI register
//!
//! This function is wrapper function for reading the BASEPRI register.
//!
//! \return Returns the state of BASEPRI register
//
//*****************************************************************************
static inline uint32_t
CPU_getBASEPRI(void)
{
    //
    // Read BASEPRI register.
    //
    __asm("    mrs     r0, BASEPRI\n"
          "    bx      lr\n");

    //
    // The following keeps the compiler happy, because it wants to see a
    // return value from this function.  It will generate code to return
    // a zero.  However, the real return is the "bx lr" above, so the
    // return(0) is never executed and the function returns with the value
    // you expect in R0.
    //
    return(0U);
}

//*****************************************************************************
//
// Extern compiler intrinsic prototypes. See compiler User's Guide for details.
//
//*****************************************************************************
extern uint32_t __get_PRIMASK(void);
extern uint32_t _disable_interrupts(void);
extern uint32_t _enable_interrupts();
extern uint32_t _disable_IRQ();
extern uint32_t _enable_IRQ();
extern uint32_t _set_interrupt_priority(uint32_t priority);

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

#endif // CPU_H
