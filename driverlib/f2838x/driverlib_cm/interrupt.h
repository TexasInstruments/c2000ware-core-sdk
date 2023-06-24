//###########################################################################
//
// FILE:   interrupt.h
//
// TITLE:  Driver for the NVIC Interrupt Controller.
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

#ifndef INTERRUPT_H
#define INTERRUPT_H

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
//! \addtogroup interrupt_api INTERRUPT
//! \brief This module configures the NVIC interrupt controller.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "cpu.h"
#include "debug.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Defines for specifying NVIC module register offset increment.
//
//*****************************************************************************
#define NVIC_OFFSET_INC            0x4U //!< 8-bit offset increment

//*****************************************************************************
//
// Define for specifying the key for AIRCR register.
//
//*****************************************************************************
#define NVIC_AIRCR_VECTKEY         0x05FA0000U

//*****************************************************************************
//
// Flash Vector Table defined in startup.ccs.
//
//*****************************************************************************
#ifndef USE_RTOS
extern void (*vectorTableFlash[NUM_INTERRUPTS])(void);
#endif

//*****************************************************************************
//
// RAM Vector Table to be used as dstVectorTable in
// Interrupt_initRAMVectorTable(). Set the size of the vector table to the
// largest number of interrupts of any device.
//
//*****************************************************************************
#ifndef USE_RTOS
extern void (*vectorTableRAM[NUM_INTERRUPTS])(void);
#endif
#endif

//*****************************************************************************
//
//! Values that can be passed to Interrupt_setPriorityGrouping() as priGroup
//! parameter.
//
//*****************************************************************************
typedef enum
{
    Interrupt_PriorityGrouping_7_1 = 0x00000000U, //!<Priority group 7.1 split
    Interrupt_PriorityGrouping_6_2 = 0x00000100U, //!<Priority group 6.2 split
    Interrupt_PriorityGrouping_5_3 = 0x00000200U, //!<Priority group 5.3 split
    Interrupt_PriorityGrouping_4_4 = 0x00000300U, //!<Priority group 4.4 split
    Interrupt_PriorityGrouping_3_5 = 0x00000400U, //!<Priority group 3.5 split
    Interrupt_PriorityGrouping_2_6 = 0x00000500U, //!<Priority group 2.6 split
    Interrupt_PriorityGrouping_1_7 = 0x00000600U, //!<Priority group 1.7 split
    Interrupt_PriorityGrouping_0_8 = 0x00000700U  //!<Priority group 0.8 split
} Interrupt_PriorityGrouping;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler for all interrupts.  It simply loops
//! forever so that the system state is preserved for observation by a
//! debugger.  Since interrupts must be disabled before unregistering the
//! corresponding handler, this should never be called during normal operation.
//!
//! \return None.
//
//*****************************************************************************
#ifndef USE_RTOS
static inline void
Interrupt_defaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while((bool)true)
    {
    }
}
#endif

//*****************************************************************************
//
//! Enables the processor interrupt.
//!
//! This function allows the processor to respond to interrupts.  This function
//! does not affect the set of interrupts enabled in the interrupt controller,
//! it just gates the single interrupt from the controller to the processor.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool
Interrupt_enableInProcessor(void)
{
    //
    // Enable processor interrupts.
    //
    return(CPU_clearPRIMASK() == 0x1UL);
}

//*****************************************************************************
//
//! Disables the processor interrupt.
//!
//! This function prevents the processor from receiving interrupts.  This
//! function does not affect the set of interrupts enabled in the interrupt
//! controller; it just gates the single interrupt from the controller to the
//! processor.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool
Interrupt_disableInProcessor(void)
{
    //
    // Disable processor interrupts.
    //
    return(CPU_setPRIMASK() == 0x1UL);
}

//*****************************************************************************
//
//! Triggers an interrupt.
//!
//! \param interruptNum specifies the interrupt to be triggered.
//!
//! This function performs a software trigger of an interrupt.The interrupt
//! controller behaves as if the corresponding interrupt line was asserted,
//! and the interrupt is handled in the same manner (meaning that it must be
//! enabled in order to be processed, and the processing is based on its
//! priority with respect to other unhandled interrupts).
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setSoftwareTrigger(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT((interruptNum >= 16U) && (interruptNum < NUM_INTERRUPTS));

    //
    // Trigger this interrupt.
    //
    HWREG(NVIC_BASE + NVIC_O_STIR) = interruptNum - 16U;
}

//*****************************************************************************
//
//! Sets the offset address of the vector table.
//!
//! \param addr is the new address of the vector table.
//!
//! Sets the address of the vector table. This function is for advanced users
//! who might want to switch between multiple instances of vector tables
//! (perhaps between flash/ram). The param addr can take following values:
//! (uint32_t)vectorTableFlash - Offset address for Flash Vector Table
//! (uint32_t)vectorTableRAM   - Offset address for RAM Vector Table
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setVectorTableOffset(uint32_t addr)
{
    HWREG(NVIC_BASE + NVIC_O_VTOR) = addr;
}

//*****************************************************************************
//
//! Returns the offset address of the interrupt vector table.
//!
//! This function returns the offset address of the interrupt vector table.
//!
//! \return Offset address of the vector table.
//
//*****************************************************************************
static inline uint32_t
Interrupt_getVectorTableOffset(void)
{
    return(HWREG(NVIC_BASE + NVIC_O_VTOR));
}

//*****************************************************************************
//
//! Sets the priority grouping of the interrupt controller.
//!
//! \param priGrouping specifies the required priority grouping
//!
//! This function specifies the split between preemptable priority levels and
//! sub-priority levels in the interrupt priority specification.  The range of
//! the grouping values are dependent upon the hardware implementation; on
//! the MSP432 family, three bits are available for hardware interrupt
//! prioritization and therefore priority grouping values of three through
//! seven have the same effect.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setPriorityGrouping(Interrupt_PriorityGrouping priGrouping)
{
    //
    // Check the arguments.
    //
    ASSERT(priGrouping < NUM_PRIORITY);

    //
    // Set the priority grouping.
    //
    HWREG(NVIC_BASE + NVIC_O_AIRCR) = NVIC_AIRCR_VECTKEY |
                                      (uint32_t)priGrouping;
}

//*****************************************************************************
//
//! Gets the priority grouping of the interrupt controller.
//!
//! This function returns the split between preemptable priority levels and
//! sub-priority levels in the interrupt priority specification.
//!
//! \return The number of bits of preemptable priority.
//
//*****************************************************************************
static inline uint32_t
Interrupt_getPriorityGrouping(void)
{
    //
    // Read the priority grouping.
    //
    return(HWREG(NVIC_BASE + NVIC_O_AIRCR) & NVIC_AIRCR_PRIGROUP_M);
}

//*****************************************************************************
//! Resets the core and all on-chip peripherals except Debug interface.
//!
//! This function will perform a software reset of the entire device.  The
//! processor and all peripherals will be reset and all device registers will
//! return to their default values (with the exception of the reset cause
//! register, which will maintain its current value but have the software reset
//! bit set as well).
//!
//! \return None
//*****************************************************************************
static inline void
Interrupt_requestSystemReset(void)
{
    //
    // Perform a software reset request.  This will cause the device to reset,
    // no further code will be executed.
    //
    HWREG(NVIC_BASE + NVIC_O_AIRCR) = NVIC_AIRCR_VECTKEY |
                                      NVIC_AIRCR_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while((bool)true)
    {
    }
}

//*****************************************************************************
//
//! Sets the priority masking level.
//!
//! \param priorityMask is the priority level that is masked.
//!
//! This function sets the interrupt priority masking level so that all
//! interrupts at the specified or lesser priority level are masked.  Masking
//! interrupts can be used to globally disable a set of interrupts with
//! priority below a predetermined threshold.  A value of 0 disables priority
//! masking.
//!
//! Smaller numbers correspond to higher interrupt priorities.  So for example
//! a priority level mask of 4 allows interrupts of priority level 0-3,
//! and interrupts with a numerical priority of 4 and greater are blocked.
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_setPriorityMask(uint32_t priorityMask)
{
    //
    // Set the priority mask.
    //
    CPU_setBASEPRI(priorityMask);
}

//*****************************************************************************
//
//! Gets the priority masking level.
//!
//! This function gets the current setting of the interrupt priority masking
//! level.  The value returned is the priority level such that all interrupts
//! of that and lesser priority are masked.  A value of 0 means that priority
//! masking is disabled.
//!
//! Smaller numbers correspond to higher interrupt priorities.  So for example
//! a priority level mask of 4 allows interrupts of priority level 0-3,
//! and interrupts with a numerical priority of 4 and greater are blocked.
//!
//! \return Returns the value of the interrupt priority level mask.
//
//*****************************************************************************
static inline uint32_t
Interrupt_getPriorityMask(void)
{
    //
    // Return the current priority mask.
    //
    return((uint32_t)CPU_getBASEPRI());
}

//*****************************************************************************
//
//! Enables the processor to sleep when exiting an ISR.
//!
//! This function enables the processor to sleep when exiting an ISR. For low
//! power operation, this is ideal as power cycles are not wasted with the
//! processing required for waking up from an ISR and going back to sleep.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_enableSleepOnISRExit(void)
{
    HWREG(NVIC_BASE + NVIC_O_SCR) |= NVIC_SCR_SLEEPONEXIT;
}

//*****************************************************************************
//
//! Disables the processor to sleep when exiting an ISR.
//!
//! This function disables the processor to sleep when exiting an ISR.
//!
//! \return None
//
//*****************************************************************************
static inline void
Interrupt_disableSleepOnISRExit(void)
{
    HWREG(NVIC_BASE + NVIC_O_SCR) &= ~NVIC_SCR_SLEEPONEXIT;
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! This function is used to indicate that no handler should be called when the
//! given interrupt is asserted to the processor.  The interrupt source is
//! automatically disabled (via Interrupt_disableInterrupt()) if necessary.
//!
//! \sa Interrupt_registerInterrupt() for important information about
//! registering interrupt handlers.
//!
//! See \link Interrupt_enable() \endlink for details about the interrupt
//! parameter
//!
//! \return None.
//
//*****************************************************************************
static inline void
Interrupt_unregisterHandler(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT(interruptNum < NUM_INTERRUPTS);

    //
    // Reset the interrupt handler.
    //
    vectorTableRAM[interruptNum] = Interrupt_defaultHandler;
}

//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! \param interruptNum specifies the interrupt in question.
//! \param intHandler is a pointer to the function to be called.
//!
//! \note The use of this function (directly or indirectly via a peripheral
//! driver interrupt register function) moves the interrupt vector table from
//! flash to SRAM.  Therefore, care must be taken when linking the application
//! to ensure that the SRAM vector table is located at the beginning of SRAM,
//! otherwise the NVIC does not look in the correct portion of memory for the
//! vector table (it requires the vector table be on a 1 kB memory alignment).
//! Normally, the SRAM vector table is so placed via the use of linker scripts.
//! See the discussion of compile-time versus run-time interrupt handler
//! registration in the introduction to this chapter.
//!
//! \note This function is only used if the customer wants to specify the
//!  interrupt handler at run time. In most cases, this is done through means
//!  of the user setting the ISR function pointer in the startup file. Refer
//!  Refer to the Module Operation section for more details.
//!
//! See \link Interrupt_enable() \endlink for details about the interrupt
//! parameter
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_registerHandler(uint32_t interruptNum, void (*intHandler)(void));

//*****************************************************************************
//
//! Enables an interrupt in interrupt controller.
//!
//! \param interruptNum is the interrupt to be enabled.
//!
//! This function enables the specified interrupt in the interrupt controller.
//! The parameter interruptNum can take any of the valid interrupts from
//! hw_ints.h file. Other enables for the interrupt (such as at the peripheral
//! level) are unaffected by this function.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_enable(uint32_t interruptNum);

//*****************************************************************************
//
//! Disables an interrupt in interrupt controller.
//!
//! \param interruptNum is the interrupt to be disabled.
//!
//! This function disables the specified interrupt in the interrupt controller.
//! The parameter interruptNum can take any of the valid interrupts from
//! hw_ints.h file. Other enables for the interrupt (such as at the peripheral
//! level) are unaffected by this function.
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_disable(uint32_t interruptNum);

//*****************************************************************************
//
//! Returns if a peripheral interrupt is enabled.
//!
//! \param interruptNum is the interrupt to be checked.
//!
//! This function checks if the specified interrupt is enabled in the interrupt
//! controller.  The \e interruptNum parameter must be one of the valid
//! interrupts defined in the inc/hw_ints.h header file.
//!
//! \return None.
//
//*****************************************************************************
extern bool
Interrupt_isEnabled(uint32_t interruptNum);

//*****************************************************************************
//
//! Pends an interrupt.
//!
//! \param interruptNum specifies the interrupt to be pended.
//!
//! The specified interrupt is pended in the interrupt controller.  Pending an
//! interrupt causes the interrupt controller to execute the corresponding
//! interrupt handler at the next available time, based on the current
//! interrupt state priorities. For example, if called by a higher priority
//! interrupt handler, the specified interrupt handler is not called until
//! after the current interrupt handler has completed execution.  The interrupt
//! must have been enabled for it to be called.
//!
//! See \link Interrupt_enable() \endlink for details about the
//! interrupt parameter
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_pend(uint32_t interruptNum);

//*****************************************************************************
//
//! Un-pends an interrupt.
//!
//! \param interruptNum specifies the interrupt to be un-pended.
//!
//! The specified interrupt is un-pended in the interrupt controller.  This
//! will cause any previously generated interrupts that have not been handled
//! yet (due to higher priority interrupts or the interrupt no having been
//! enabled yet) to be discarded.
//!
//! See \link Interrupt_enable() \endlink for details about the interrupt
//! parameter
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_unpend(uint32_t interruptNum);

//*****************************************************************************
//
//! Sets the priority of an interrupt.
//!
//! \param interruptNum specifies the interrupt in question.
//! \param priority specifies the priority of the interrupt.
//!
//! This function is used to set the priority of an interrupt.  When multiple
//! interrupts are asserted simultaneously, the ones with the highest priority
//! are processed before the lower priority interrupts.  Smaller numbers
//! correspond to higher interrupt priorities; priority 0 is the highest
//! interrupt priority.
//!
//! The hardware priority mechanism only looks at the upper N bits of the
//! priority level, so any prioritization must be performed in those bits.
//! The remaining bits can be used to sub-prioritize the interrupt sources,
//! and may be used by the hardware priority mechanism on a future part. This
//! arrangement allows priorities to migrate to different NVIC implementations
//! without changing the gross prioritization of the interrupts.
//!
//! See \link Interrupt_enable() \endlink for details about the interrupt
//! parameter
//!
//! \return None.
//
//*****************************************************************************
extern void
Interrupt_setPriority(uint32_t interruptNum, uint32_t priority);

//*****************************************************************************
//
//! Gets the priority of an interrupt.
//!
//! \param interruptNum specifies the interrupt in question.
//!
//! This function gets the priority of an interrupt.  See
//! Interrupt_setPriority() for a definition of the priority value.
//!
//! See \link Interrupt_enable() \endlink for details about the interrupt
//! parameter
//!
//! \return Returns the interrupt priority, or -1 if an invalid interrupt was
//! specified.
//
//*****************************************************************************
extern uint32_t
Interrupt_getPriority(uint32_t interruptNum);

//*****************************************************************************
//
//! Initializes all the ISRs in the RAM vector table.
//!
//! \param srcVectorTable is source vector table array
//! \param dstVectorTable is destination vector table array
//!
//! This function initializes all the ISRs in the RAM vector table. It copies
//! the ISR addresses from temporary source table to destination RAM vector
//! table. The \e srcVectorTable can be preinitialised table which can be used
//! to initialize vector table in one go. \e dstVectorTable can be the RAM
//! vector table to be populated.
//!
//! \return None
//
//*****************************************************************************
extern void
Interrupt_initRAMVectorTable(void (*srcVectorTable[])(void),
                             void (*dstVectorTable[])(void));

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

#endif // INTERRUPT_H
