//###########################################################################
//
// FILE:   interrupt.c
//
// TITLE:  Stellaris style wrapper driver for C28x PIE Interrupt Controller.
//
//###########################################################################
// $TI Release: f2806x Support Library v1.15 $
// $Release Date: December 12, 2011 $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

//*****************************************************************************
//
//! \addtogroup interrupt_api
//! @{
//
//*****************************************************************************

//
// Included Files
//
#include "DSP28x_Project.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include <string.h>

//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler.  Whenever an interrupt is
//! unregisterd this handler takes it place.
//!
//! \return None.
//
//*****************************************************************************
__interrupt void IntDefaultHandler(void)
{
    return;
}

//*****************************************************************************
//
//! Enables the processor interrupt.
//!
//! Allows the processor to respond to interrupts.  This does not affect the
//! set of interrupts enabled in the interrupt controller; it just gates the
//! single interrupt from the controller to the processor.
//!
//! \note Previously, this function had no return value.  As such, it was
//! possible to include <tt>interrupt.h</tt> and call this function without
//! having included <tt>hw_types.h</tt>.  Now that the return is a
//! <tt>tBoolean</tt>, a compiler error will occur in this case.  The solution
//! is to include <tt>hw_types.h</tt> before including <tt>interrupt.h</tt>.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
tBoolean
IntMasterEnable(void)
{
    //
    // Enable processor interrupts.
    //
    __asm(" CLRC INTM");

    //
    // TODO: Return previous interrupt status
    //
    return 0;
}

//*****************************************************************************
//
//! Disables the processor interrupt.
//!
//! Prevents the processor from receiving interrupts.  This does not affect the
//! set of interrupts enabled in the interrupt controller; it just gates the
//! single interrupt from the controller to the processor.
//!
//! \note Previously, this function had no return value.  As such, it was
//! possible to include <tt>interrupt.h</tt> and call this function without
//! having included <tt>hw_types.h</tt>.  Now that the return is a
//! <tt>tBoolean</tt>, a compiler error will occur in this case.  The solution
//! is to include <tt>hw_types.h</tt> before including <tt>interrupt.h</tt>.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially enabled.
//
//*****************************************************************************
tBoolean
IntMasterDisable(void)
{
    //
    // Disable processor interrupts.
    //
    __asm(" SETC INTM");

    //
    // TODO: Return previous interrupt status
    //
    return 0;

}

//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//
//! Assumes PIE is enabled
//!
//! \param ulInterrupt specifies the interrupt in question.
//! \param pfnHandler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  When the interrupt occurs,
//! if it is enabled (via IntEnable()), the handler function will be called in
//! interrupt context.  Since the handler function can preempt other code, care
//! must be taken to protect memory or peripherals that are accessed by the
//! handler and other non-handler code.
//!
//! \note The use of this function (directly or indirectly via a peripheral
//! driver interrupt register function) moves the interrupt vector table from
//! flash to SRAM.  Therefore, care must be taken when linking the application
//! to ensure that the SRAM vector table is located at the beginning of SRAM;
//! otherwise NVIC will not look in the correct portion of memory for the
//! vector table (it requires the vector table be on a 1 kB memory alignment).
//! Normally, the SRAM vector table is so placed via the use of linker scripts;
//! some tool chains, such as the evaluation version of RV-MDK, do not support
//! linker scripts and therefore will not produce a valid executable.  See the
//! discussion of compile-time versus run-time interrupt handler registration
//! in the introduction to this chapter.
//!
//! \return None.
//
//*****************************************************************************
void
IntRegister(unsigned long ulInterrupt, void (*pfnHandler)(void))
{
    EALLOW;
    
    //
    // Copy ISR address into PIE table
    //
    memcpy((Uint16 *)&PieVectTable+0x30+(ulInterrupt & 0xF0)+(2*((ulInterrupt & 0x0F)-1)), (Uint16 *) &pfnHandler, (size_t) 2);
    EDIS;
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param ulInterrupt specifies the interrupt in question.
//!
//! This function is used to indicate that no handler should be called when the
//! given interrupt is asserted to the processor.  The interrupt source will be
//! automatically disabled (via IntDisable()) if necessary.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
IntUnregister(unsigned long ulInterrupt)
{
    unsigned long temp;

    temp = (unsigned long) IntDefaultHandler;

    EALLOW;
    
    //
    // Copy default ISR address into PIE table
    //
    memcpy((Uint16 *)&PieVectTable+0x30+(ulInterrupt & 0xF0)+(2*((ulInterrupt & 0x0F)-1)), (Uint16 *) &temp, (size_t) 2);
    EDIS;
}

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! \return None.
//
//*****************************************************************************
void
IntEnable(unsigned long ulInterrupt)
{
    EALLOW;
    
    //
    // Ensure that PIE is enabled
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE=1;

    //
    // Enable Individual PIE interrupt
    //
    *(unsigned short *)((&PieCtrlRegs.PIEIER1.all) + (2*(((ulInterrupt & 0xF0) >> 4) -1))) |= 1 << ((ulInterrupt & 0x0F) - 1);

    //
    // Enable PIE Group Interrupt
    //
    IER |= 1 << (((ulInterrupt & 0xF0) >> 4) -1);

    EDIS;

}

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param ulInterrupt specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! \return None.
//
//*****************************************************************************
void
IntDisable(unsigned long ulInterrupt)
{
    EALLOW;

    //
    // Disable Individual PIE interrupt
    //
    *(unsigned short *)((&PieCtrlRegs.PIEIER1.all) + (2*(((ulInterrupt & 0xF0) >> 4) -1))) &= ~(1 << ((ulInterrupt & 0x0F) - 1));

    EDIS;
}

//*****************************************************************************
//
//! \internal
//! Clears the IFR flag in the CPU.
//!
//! \param group specifies the interrupt group to be cleared.
//!
//! This function clears the IFR flag.  This switch is needed because the
//! clearing of the IFR can only be done with a constant.
//
//*****************************************************************************
static void Interrupt_clearIFR(uint16_t group)
{
    switch(group)
    {
        case 0x0001U:
            IFR &= ~0x0001U;
            break;
        case 0x0002U:
            IFR &= ~0x0002U;
            break;
        case 0x0004U:
            IFR &= ~0x0004U;
            break;
        case 0x0008U:
            IFR &= ~0x0008U;
            break;
        case 0x0010U:
            IFR &= ~0x0010U;
            break;
        case 0x0020U:
            IFR &= ~0x0020U;
            break;
        case 0x0040U:
            IFR &= ~0x0040U;
            break;
        case 0x0080U:
            IFR &= ~0x0080U;
            break;
        case 0x0100U:
            IFR &= ~0x0100U;
            break;
        case 0x0200U:
            IFR &= ~0x0200U;
            break;
        case 0x0400U:
            IFR &= ~0x0400U;
            break;
        case 0x0800U:
            IFR &= ~0x0800U;
            break;
        case 0x1000U:
            IFR &= ~0x1000U;
            break;
        case 0x2000U:
            IFR &= ~0x2000U;
            break;
        case 0x4000U:
            IFR &= ~0x4000U;
            break;
        case 0x8000U:
            IFR &= ~0x8000U;
            break;
        default:
            //
            // Invalid group mask.
            //
            break;
    }
}

//*****************************************************************************
//
//! Interrupt_enable
//!
//! \param interruptNumber is the interrupt number.
//!
//! Enable interrupts in the proper way. Written like the Potenza and Soprano
//! interrupt driver.
//!
//! \return None.
//
//*****************************************************************************
void
Interrupt_enable(uint32_t interruptNumber)
{
    bool intsEnabled;
    uint16_t intGroup;
    uint16_t groupMask;
    uint16_t vectID;

    vectID = (uint16_t)(interruptNumber >> 16);

    EALLOW;

    //
    // Ensure that PIE is enabled
    //
    PieCtrlRegs.PIECTRL.all |= 0x1;

    intsEnabled = IntMasterDisable();

    //
    // PIE Interrupts
    //
    if(vectID >= 0x20U)
    {
        intGroup = ((uint16_t)(interruptNumber & 0xFF00U) >> 8) - 1U;
        groupMask = 1U << intGroup;

        HWREGH(0xCE0 + 0x02 + (intGroup * 2U)) |=
            1U << ((uint16_t)(interruptNumber & 0xFFU) - 1U);

        //
        // Wait for any pending interrupts to get to the CPU
        //
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");

        //
        // Acknowledge any interrupts
        //
        PieCtrlRegs.PIEACK.all = groupMask;

        //
        // Enable PIE Group Interrupt
        //
        IER |= groupMask;
    }
    
    //
    // INT13, INT14, DLOGINT, & RTOSINT
    //
    else if((vectID >= 0x0DU) && (vectID <= 0x10U))
    {
        IER |= 1U << (vectID - 1U);
    }
    else
    {
        //
        // Other interrupts
        //
    }

    EDIS;

    //
    // Re-enable interrupts if they were enabled
    //
    if(!intsEnabled)
    {
        (void)IntMasterEnable();
    }
}

//*****************************************************************************
//
//! Interrupt_disable
//!
//! \param interruptNumber is the interrupt number.
//!
//! Disable interrupts in the proper way. Written like the Potenza and Soprano
//! interrupt driver.
//!
//! \return None.
//
//*****************************************************************************
void
Interrupt_disable(uint32_t interruptNumber)
{
    bool intsEnabled;
    uint16_t intGroup;
    uint16_t groupMask;
    uint16_t vectID;

    vectID = (uint16_t)(interruptNumber >> 16);

    EALLOW;

    intsEnabled = IntMasterDisable();

    //
    // PIE Interrupts
    //
    if(vectID >= 0x20U)
    {
        intGroup = ((uint16_t)(interruptNumber & 0xFF00U) >> 8) - 1U;
        groupMask = 1U << intGroup;

        //
        // Disable individual PIE interrupt
        //
        HWREGH(0xCE0 + 0x02 + (intGroup * 2U)) &=
            ~(1U << ((uint16_t)(interruptNumber & 0xFFU) - 1U));

        //
        // Wait for any pending interrupts to get to the CPU
        //
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");
        __asm(" nop");

        Interrupt_clearIFR(groupMask);

        //
        // Acknowledge any interrupts
        //
        PieCtrlRegs.PIEACK.all = groupMask;
    }
    
    //
    // INT13, INT14, DLOGINT, & RTOSINT
    //
    else if((vectID >= 0x0DU) && (vectID <= 0x10U))
    {
        IER |= ~(1U << (vectID - 1U));
    }
    else
    {
        //
        // Other interrupts
        //
    }

    EDIS;

    //
    // Re-enable interrupts if they were enabled
    //
    if(!intsEnabled)
    {
        (void)IntMasterEnable();
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


