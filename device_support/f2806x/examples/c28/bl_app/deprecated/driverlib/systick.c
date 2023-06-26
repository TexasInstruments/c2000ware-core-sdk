//###########################################################################
//
// FILE:   systick.c
//
// TITLE:  Stellaris style wrapper driver for C28x CPU Timer 0.
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
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"


//*****************************************************************************
//
//! Initializes the Timer0 Module to act as a system tick
//!
//! \return None.
//
//*****************************************************************************
void
SysTickInit(void)
{
    // CPU Timer 0
    // Initialize timer period to maximum:
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;
    // Make sure timer is stopped:
    CpuTimer0Regs.TCR.bit.TSS = 1;
    // Reload all counter register with period value:
    CpuTimer0Regs.TCR.bit.TRB = 1;
}

//*****************************************************************************
//
//! Enables the SysTick counter.
//!
//! This will start the SysTick counter.  If an interrupt handler has been
//! registered, it will be called when the SysTick counter rolls over.
//!
//! \note Calling this function will cause the SysTick counter to (re)commence
//! counting from its current value.  The counter is not automatically reloaded
//! with the period as specified in a previous call to SysTickPeriodSet().  If
//! an immediate reload is required, the \b NVIC_ST_CURRENT register must be
//! written to force this.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the supplied period on the next
//! clock.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickEnable(void)
{
    //
    // Enable SysTick.
    //
    StartCpuTimer0();
}

//*****************************************************************************
//
//! Disables the SysTick counter.
//!
//! This will stop the SysTick counter.  If an interrupt handler has been
//! registered, it will no longer be called until SysTick is restarted.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickDisable(void)
{
    //
    // Disable SysTick.
    //
    StopCpuTimer0();
}

//*****************************************************************************
//
//! Registers an interrupt handler for the SysTick interrupt.
//!
//! \param pfnHandler is a pointer to the function to be called when the
//! SysTick interrupt occurs.
//!
//! This sets the handler to be called when a SysTick interrupt occurs.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    IntRegister(INT_TINT0, pfnHandler);

    //
    // Enable the SysTick interrupt.
    //
    IntEnable(INT_TINT0);
}

//*****************************************************************************
//
//! Unregisters the interrupt handler for the SysTick interrupt.
//!
//! This function will clear the handler to be called when a SysTick interrupt
//! occurs.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntUnregister(void)
{
    //
    // Disable the SysTick interrupt.
    //
    IntDisable(INT_TINT0);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_TINT0);
}

//*****************************************************************************
//
//! Enables the SysTick interrupt.
//!
//! This function will enable the SysTick interrupt, allowing it to be
//! reflected to the processor.
//!
//! \note The SysTick interrupt handler does not need to clear the SysTick
//! interrupt source as this is done automatically by NVIC when the interrupt
//! handler is called.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntEnable(void)
{
    //
    // Enable the SysTick interrupt.
    //
    CpuTimer0Regs.TCR.bit.TIE = 1;
    IntEnable(INT_TINT0);
}

//*****************************************************************************
//
//! Disables the SysTick interrupt.
//!
//! This function will disable the SysTick interrupt, preventing it from being
//! reflected to the processor.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntDisable(void)
{
    //
    // Disable the SysTick interrupt.
    //
    CpuTimer0Regs.TCR.bit.TIE = 0;
    IntDisable(INT_TINT0);
}

//*****************************************************************************
//
//! Sets the period of the SysTick counter.
//!
//! \param ulPeriod is the number of clock ticks in each period of the SysTick
//! counter; must be between 1 and 16,777,216, inclusive.
//!
//! This function sets the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \note Calling this function does not cause the SysTick counter to reload
//! immediately.  If an immediate reload is required, the \b NVIC_ST_CURRENT
//! register must be written.  Any write to this register clears the SysTick
//! counter to 0 and will cause a reload with the \e ulPeriod supplied here on
//! the next clock after the SysTick is enabled.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickPeriodSet(unsigned long ulPeriod)
{
    //
    // Check the arguments.
    //
    ASSERT((ulPeriod > 0) && (ulPeriod <= 16777216));

    //
    // Set the period of the SysTick counter.
    //
    CpuTimer0Regs.PRD.all = ulPeriod;
}

//*****************************************************************************
//
//! Gets the period of the SysTick counter.
//!
//! This function returns the rate at which the SysTick counter wraps; this
//! equates to the number of processor clocks between interrupts.
//!
//! \return Returns the period of the SysTick counter.
//
//*****************************************************************************
unsigned long
SysTickPeriodGet(void)
{
    //
    // Return the period of the SysTick counter.
    //
    return(CpuTimer0Regs.PRD.all);
}

//*****************************************************************************
//
//! Gets the current value of the SysTick counter.
//!
//! This function returns the current value of the SysTick counter; this will
//! be a value between the period - 1 and zero, inclusive.
//!
//! \return Returns the current value of the SysTick counter.
//
//*****************************************************************************
unsigned long
SysTickValueGet(void)
{
    //
    // Return the current value of the SysTick counter.
    //
    return(CpuTimer0Regs.TIM.all);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


