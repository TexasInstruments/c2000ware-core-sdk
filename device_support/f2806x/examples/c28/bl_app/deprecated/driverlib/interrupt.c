//###########################################################################
//
// FILE:   interrupt.c
//
// TITLE:  Stellaris style wrapper driver for C28x PIE Interrupt Controller.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//*****************************************************************************
//
//! @{
//
//*****************************************************************************

#include "DSP28x_Project.h"

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

    //TODO: Return previous interrupt status
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

    //TODO: Return previous interrupt status
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
    //Copy ISR address into PIE table
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
    //Copy default ISR address into PIE table
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
    //Ensure that PIE is enabled
    PieCtrlRegs.PIECTRL.bit.ENPIE=1;

    //Enable Individual PIE interrupt
    *(unsigned short *)((&PieCtrlRegs.PIEIER1.all) + (2*(((ulInterrupt & 0xF0) >> 4) -1))) |= 1 << ((ulInterrupt & 0x0F) - 1);

    //Enable PIE Group Interrupt
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

    //Disable Individual PIE interrupt
    *(unsigned short *)((&PieCtrlRegs.PIEIER1.all) + (2*(((ulInterrupt & 0xF0) >> 4) -1))) &= ~(1 << ((ulInterrupt & 0x0F) - 1));

    EDIS;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


