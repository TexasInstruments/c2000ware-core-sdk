//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  Stellaris style wrapper driver for C28x system control.
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
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

//
// Included Files
//
#include "DSP28x_Project.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"


//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param ulPeripheral is the peripheral to reset.
//!
//! The f2806x devices do not have a means of resetting peripherals via
//! via software.  This is a dummy function that does nothing.
//!
//!
//! \return None.
//
//*****************************************************************************
void SysCtlPeripheralReset(unsigned long ulPeripheral)
{
    return;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param ulPeripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_SPI0, \b SYSCTL_PERIPH_SPI1,
//! \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB0.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(unsigned long ulPeripheral)
{
    EALLOW;
    switch(ulPeripheral)
    {
    case SYSCTL_PERIPH_UART0:
        SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
        break;

    case SYSCTL_PERIPH_UART1:
        SysCtrlRegs.PCLKCR0.bit.SCIBENCLK=1;
        break;

    case SYSCTL_PERIPH_SPI0:
        SysCtrlRegs.PCLKCR0.bit.SPIAENCLK=1;
        break;

    case SYSCTL_PERIPH_SPI1:
        SysCtrlRegs.PCLKCR0.bit.SPIBENCLK=1;
        break;

    case SYSCTL_PERIPH_DMA:
        SysCtrlRegs.PCLKCR3.bit.DMAENCLK=1;
        break;

    case SYSCTL_PERIPH_USB0:
        SysCtrlRegs.PCLKCR3.bit.USB0ENCLK=1;
        break;

    default:
        break;
    }
    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param ulPeripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_SPI0, \b SYSCTL_PERIPH_SPI1,
//! \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB0.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(unsigned long ulPeripheral)
{

    EALLOW;
    switch(ulPeripheral)
    {
    case SYSCTL_PERIPH_UART0:
        SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
        break;

    case SYSCTL_PERIPH_UART1:
        SysCtrlRegs.PCLKCR0.bit.SCIBENCLK=1;
        break;

    case SYSCTL_PERIPH_SPI0:
        SysCtrlRegs.PCLKCR0.bit.SPIAENCLK=1;
        break;

    case SYSCTL_PERIPH_SPI1:
        SysCtrlRegs.PCLKCR0.bit.SPIBENCLK=1;
        break;

    case SYSCTL_PERIPH_DMA:
        SysCtrlRegs.PCLKCR3.bit.DMAENCLK=1;
        break;

    case SYSCTL_PERIPH_USB0:
        SysCtrlRegs.PCLKCR3.bit.USB0ENCLK=1;
        break;

    default:
        break;
    }
    EDIS;
}

//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param ulPeripheral is the peripheral in question.
//!
//! Determines if a particular peripheral is present in the device.
//!
//! The \e ulPeripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_SPI0, \b SYSCTL_PERIPH_SPI1,
//! \b SYSCTL_PERIPH_UART0, \b SYSCTL_PERIPH_UART1,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB0.
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
tBoolean
SysCtlPeripheralPresent(unsigned long ulPeripheral)
{

    return true;
}

//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 3 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlDelay(unsigned long ulCount)
{
    unsigned long i;

    for(i=0; i<ulCount; i++)
    {
        __asm(" nop");
    }

}

//*****************************************************************************
//
//! Gets the processor clock rate.
//!
//! \param u32ClockIn is the processor clock
//!
//! This function determines the clock rate of the processor clock.
//!
//! \note Because of the many different clocking options available, this
//!  function cannot determine the clock speed of the processor.  This function
//!  should be modified to return the actual clock speed of the processor in
//!  your specific application.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
unsigned long
SysCtlClockGet(unsigned long u32ClockIn)
{

    return SYSTEM_CLOCK_SPEED;

}

//*****************************************************************************
//
//! Powers up the USB PLL.
//!
//! This function will enable the USB controller's PLL.
//!
//! \note Because every application is different, the user will likely have to
//! modify this function to ensure the PLL multiplier is set correctly to
//! achieve the 60 MHz required by the USB controller.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLEnable(void)
{
    //
    // Select X1 as USB PLL Clk In
    //
    SysCtrlRegs.PLL2CTL.bit.PLL2CLKSRCSEL=0;
    
    //
    // Set Pll Multiplier
    //
    SysCtrlRegs.PLL2MULT.bit.PLL2MULT=1;
    
    //
    // Enable the PLL
    //
    SysCtrlRegs.PLL2CTL.bit.PLL2EN=1;
    
    //
    // Wait for PLL Lock
    //
    while(!SysCtrlRegs.PLL2STS.bit.PLL2LOCKS);

}

//*****************************************************************************
//
//! Powers down the USB PLL.
//!
//! This function will disable the USB controller's PLL.  The USB registers
//! are still accessible, but the physical layer will no longer function.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLDisable(void)
{
    //
    // Disable the PLL
    //
    SysCtrlRegs.PLL2CTL.bit.PLL2EN=0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


