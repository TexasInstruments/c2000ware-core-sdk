//###########################################################################
//
// FILE:   uart.c
//
// TITLE:  Stellaris style wrapper driver for C28x SCI peripheral.
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
//! \addtogroup uart_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

//*****************************************************************************
//
//! \internal
//! Checks a UART base address.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static tBoolean
UARTBaseValid(unsigned long ulBase)
{
    return((ulBase == UART0_BASE) || (ulBase == UART1_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the type of parity.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulParity specifies the type of parity to use.
//!
//! Sets the type of parity to use for transmitting and expect when receiving.
//! The \e ulParity parameter must be one of \b UART_CONFIG_PAR_NONE,
//! \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! or \b UART_CONFIG_PAR_ZERO.  The last two allow direct control of the
//! parity bit; it is always either one or zero based on the mode.
//!
//! \return None.
//
//*****************************************************************************
void
UARTParityModeSet(unsigned long ulBase, unsigned long ulParity)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));
    ASSERT((ulParity == UART_CONFIG_PAR_NONE) ||
           (ulParity == UART_CONFIG_PAR_EVEN) ||
           (ulParity == UART_CONFIG_PAR_ODD) ||
           (ulParity == UART_CONFIG_PAR_ONE) ||
           (ulParity == UART_CONFIG_PAR_ZERO));

    //
    // Set the parity mode.
    //
    HWREGB(ulBase + UART_O_CR) = ((HWREGB(ulBase + UART_O_CR) &
                                   ~(UART_CONFIG_PAR_MASK)) | ulParity);
}

//*****************************************************************************
//
//! Gets the type of parity currently being used.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data and
//! expected when receiving data.
//!
//! \return Returns the current parity settings, specified as one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN, \b UART_CONFIG_PAR_ODD,
//! \b UART_CONFIG_PAR_ONE, or \b UART_CONFIG_PAR_ZERO.
//
//*****************************************************************************
unsigned long
UARTParityModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the current parity setting.
    //
    return(HWREGB(ulBase + UART_O_CR) &
           (UART_CONFIG_PAR_MASK));
}

//*****************************************************************************
//
//! Sets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulTxLevel is the transmit FIFO interrupt level, specified as one of
//! \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8, \b UART_FIFO_TX4_8,
//! \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param ulRxLevel is the receive FIFO interrupt level, specified as one of
//! \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8, \b UART_FIFO_RX4_8,
//! \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelSet(unsigned long ulBase, unsigned long ulTxLevel,
                 unsigned long ulRxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));
    ASSERT((ulTxLevel == UART_FIFO_TX1_8) ||
           (ulTxLevel == UART_FIFO_TX2_8) ||
           (ulTxLevel == UART_FIFO_TX4_8) ||
           (ulTxLevel == UART_FIFO_TX6_8) ||
           (ulTxLevel == UART_FIFO_TX7_8));
    ASSERT((ulRxLevel == UART_FIFO_RX1_8) ||
           (ulRxLevel == UART_FIFO_RX2_8) ||
           (ulRxLevel == UART_FIFO_RX4_8) ||
           (ulRxLevel == UART_FIFO_RX6_8) ||
           (ulRxLevel == UART_FIFO_RX7_8));

    //
    // Set the FIFO interrupt levels.
    //
    HWREGH(ulBase + UART_O_FFTX) = (HWREGH(ulBase + UART_O_FFTX)& (~UART_FFTX_TXFFIL_M)) | ulTxLevel ;
    HWREGH(ulBase + UART_O_FFRX) = (HWREGH(ulBase + UART_O_FFRX)& (~UART_FFRX_RXFFIL_M)) | ulRxLevel ;
}

//*****************************************************************************
//
//! Gets the FIFO level at which interrupts are generated.
//!
//! \param ulBase is the base address of the UART port.
//! \param pulTxLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8,
//! \b UART_FIFO_TX4_8, \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param pulRxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8,
//! \b UART_FIFO_RX4_8, \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                 unsigned long *pulRxLevel)
{

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Extract the transmit and receive FIFO levels.
    //
    *pulTxLevel = HWREGH(ulBase + UART_O_FFTX) & UART_FFTX_TXFFIL_M;
    *pulRxLevel = HWREGH(ulBase + UART_O_FFRX) & UART_FFRX_RXFFIL_M;
}

//*****************************************************************************
//
//! Sets the configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUARTClk is the rate of the clock supplied to the UART module.
//! \param ulBaud is the desired baud rate.
//! \param ulConfig is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e ulBaud parameter and the data
//! format in the \e ulConfig parameter.
//!
//! The \e ulConfig parameter is the logical OR of three values: the number of
//! data bits, the number of stop bits, and the parity.  \b UART_CONFIG_WLEN_8,
//! \b UART_CONFIG_WLEN_7, \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5
//! select from eight to five data bits per byte (respectively).
//! \b UART_CONFIG_STOP_ONE and \b UART_CONFIG_STOP_TWO select one or two stop
//! bits (respectively).  \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE, and \b UART_CONFIG_PAR_ZERO
//! select the parity mode (no parity bit, even parity bit, odd parity bit,
//! parity bit always one, and parity bit always zero, respectively).
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original UARTConfigSet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
//Changed for C28x
void
UARTConfigSetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                    unsigned long ulBaud, unsigned long ulConfig)
{
    unsigned long ulDiv;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));
    ASSERT(ulBaud != 0);
    ASSERT(ulUARTClk >= (ulBaud * UART_CLK_DIVIDER));

    //
    // Stop the UART.
    //
    UARTDisable(ulBase);

    //
    // Is the required baud rate greater than the maximum rate supported?
    //
    if((ulBaud * 16) > ulUARTClk)
    {
        //
        // Baud Rate Not supported with current clock
        //
        return;
    }

    //
    // Compute the baud rate divider.
    //
    ulDiv = ((ulUARTClk  / (ulBaud * 8)) - 1);

    //
    // Set the baud rate.
    //
    HWREGB(ulBase + UART_O_HBAUD) = (ulDiv & 0xFF00) >> 8;
    HWREGB(ulBase + UART_O_LBAUD) = ulDiv & 0x00FF;

    //
    // Set parity, data length, and number of stop bits.
    //
    HWREGB(ulBase + UART_O_CR) = ((HWREGB(ulBase + UART_O_CR) &
                                   ~(UART_CONFIG_PAR_MASK | UART_CONFIG_STOP_MASK | UART_CONFIG_WLEN_MASK))
                                  | ulConfig);


    //
    // Start the UART.
    //
    UARTEnable(ulBase);
}

//*****************************************************************************
//
//! Gets the current configuration of a UART.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulUARTClk is the rate of the clock supplied to the UART module.
//! \param pulBaud is a pointer to storage for the baud rate.
//! \param pulConfig is a pointer to storage for the data format.
//!
//! The baud rate and data format for the UART is determined, given an
//! explicitly provided peripheral clock (hence the ExpClk suffix).  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e pulConfig is enumerated the same as the \e ulConfig parameter of
//! UARTConfigSetExpClk().
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original UARTConfigGet() API and performs the
//! same actions.  A macro is provided in <tt>uart.h</tt> to map the original
//! API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
UARTConfigGetExpClk(unsigned long ulBase, unsigned long ulUARTClk,
                    unsigned long *pulBaud, unsigned long *pulConfig)
{

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Compute the baud rate.
    //
    *pulBaud = ulUARTClk / ((1 + (HWREGB(ulBase + UART_O_HBAUD) << 8 ) | HWREGB(ulBase + UART_O_LBAUD)) * 8);

    //
    // Get the parity, data length, and number of stop bits.
    //
    *pulConfig = HWREGB(ulBase + UART_O_CR) &
                 (UART_CONFIG_PAR_MASK | UART_CONFIG_STOP_MASK | UART_CONFIG_WLEN_MASK);
}

//*****************************************************************************
//
//! Enables transmitting and receiving.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Sets the UARTEN, TXE, and RXE bits, and enables the transmit and receive
//! FIFOs.
//!
//! \return None.
//
//*****************************************************************************
void
UARTEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Enable RX, TX, and the UART.
    //
    HWREGB(ulBase + UART_O_CTL1) |= (UART_CTL1_TXENA | UART_CTL1_RXENA | UART_CTL1_SWRST);
}

//*****************************************************************************
//
//! Disables transmitting and receiving.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Clears the UARTEN, TXE, and RXE bits, then waits for the end of
//! transmission of the current character, and flushes the transmit FIFO.
//!
//! \return None.
//
//*****************************************************************************
void
UARTDisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Wait for end of TX.
    //
    while(!(HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXEMPTY))
    {
    }

    //
    // Disable the FIFO.
    //
    HWREGH(ulBase + UART_O_FFTX) &= ~(UART_FFTX_FFENA);

    //
    // Disable the UART.
    //
    HWREGB(ulBase + UART_O_CTL1) &= ~(UART_CTL1_TXENA | UART_CTL1_RXENA);
}

//*****************************************************************************
//
//! Enables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFOEnable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Enable the FIFO.
    //
    HWREGH(ulBase + UART_O_FFTX) |= UART_FFTX_FFENA;
}

//*****************************************************************************
//
//! Disables the transmit and receive FIFOs.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This functions disables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFIFODisable(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Disable the FIFO.
    //
    HWREGH(ulBase + UART_O_FFTX) &= ~UART_FFTX_FFENA;
}

//*****************************************************************************
//
//! Sets the operating mode for the UART transmit interrupt.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulMode is the operating mode for the transmit interrupt.  It may be
//! \b UART_TXINT_MODE_EOT to trigger interrupts when the transmitter is idle
//! or \b UART_TXINT_MODE_FIFO to trigger based on the current transmit FIFO
//! level.
//!
//! This function allows the mode of the UART transmit interrupt to be set.  By
//! default, the transmit interrupt is asserted when the FIFO level falls past
//! a threshold set via a call to UARTFIFOLevelSet().  Alternatively, if this
//! function is called with \e ulMode set to \b UART_TXINT_MODE_EOT, the
//! transmit interrupt will only be asserted once the transmitter is completely
//! idle - the transmit FIFO is empty and all bits, including any stop bits,
//! have cleared the transmitter.
//!
//! \return None.
//
//*****************************************************************************
void
UARTTxIntModeSet(unsigned long ulBase, unsigned long ulMode)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));
    ASSERT((ulMode == UART_TXINT_MODE_EOT) ||
           (ulMode == UART_TXINT_MODE_FIFO_M));

    //
    // Set or clear the EOT bit of the UART control register as appropriate.
    //
    HWREGH(ulBase + UART_O_FFTX) = (HWREG(ulBase + UART_O_FFTX) &
                                    ~(UART_TXINT_MODE_FIFO_M) | ulMode);
}

//*****************************************************************************
//
//! Returns the current operating mode for the UART transmit interrupt.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current operating mode for the UART transmit
//! interrupt.  The return value will be \b UART_TXINT_MODE_EOT if the
//! transmit interrupt is currently set to be asserted once the transmitter is
//! completely idle - the transmit FIFO is empty and all bits, including any
//! stop bits, have cleared the transmitter.  The return value will be \b
//! UART_TXINT_MODE_FIFO if the interrupt is set to be asserted based upon the
//! level of the transmit FIFO.
//!
//! \return Returns \b UART_TXINT_MODE_FIFO or \b UART_TXINT_MODE_EOT.
//
//*****************************************************************************
unsigned long
UARTTxIntModeGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the current transmit interrupt mode.
    //
    return(HWREGH(ulBase + UART_O_FFTX) & UART_TXINT_MODE_FIFO_M);
}

//*****************************************************************************
//
//! Determines if there are any characters in the receive FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \return Returns \b true if there is data in the receive FIFO or \b false
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
tBoolean
UARTCharsAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the availability of characters.
    //
    return((HWREGB(ulBase + UART_O_RXST) & UART_RXST_RXRDY) ? true : false);
}

//*****************************************************************************
//
//! Determines if there is any space in the transmit FIFO.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \return Returns \b true if there is space available in the transmit FIFO
//! or \b false if there is no space available in the transmit FIFO.
//
//*****************************************************************************
tBoolean
UARTSpaceAvail(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the availability of space.
    //
    return((HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXRDY) ? true : false);
}

//*****************************************************************************
//
//! Receives a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.
//!
//! This function replaces the original UARTCharNonBlockingGet() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.  A \b -1 is returned if there are no characters present in the
//! receive FIFO.  The UARTCharsAvail() function should be called before
//! attempting to call this function.
//
//*****************************************************************************
long
UARTCharGetNonBlocking(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(HWREGB(ulBase + UART_O_RXST) & UART_RXST_RXRDY)
    {
        //
        // Read and return the next character.
        //
        return(HWREGH(ulBase + UART_O_RXBUF) & UART_RXBUF_RXDT_M);
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        return(-1);
    }
}

//*****************************************************************************
//
//! Waits for a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Gets a character from the receive FIFO for the specified port.  If there
//! are no characters available, this function waits until a character is
//! received before returning.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e long.
//
//*****************************************************************************
long
UARTCharGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Wait until a char is available.
    //
    while(!HWREGB(ulBase + UART_O_RXST) & UART_RXST_RXRDY)
    {
    }

    //
    // Now get the char.
    //
    return(HWREGH(ulBase + UART_O_RXBUF) & UART_RXBUF_RXDT_M);
}

//*****************************************************************************
//
//! Sends a character to the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Writes the character \e ucData to the transmit FIFO for the specified port.
//! This function does not block, so if there is no space available, then a
//! \b false is returned, and the application must retry the function later.
//!
//! This function replaces the original UARTCharNonBlockingPut() API and
//! performs the same actions.  A macro is provided in <tt>uart.h</tt> to map
//! the original API to this API.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************
tBoolean
UARTCharPutNonBlocking(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // See if there is space in the transmit FIFO.
    //
    if(HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXRDY)
    {
        //
        // Write this character to the transmit FIFO.
        //
        HWREGB(ulBase + UART_O_TXBUF) = ucData;

        //
        // Success.
        //
        return(true);
    }
    else
    {
        //
        // There is no space in the transmit FIFO, so return a failure.
        //
        return(false);
    }
}

//*****************************************************************************
//
//! Waits to send a character from the specified port.
//!
//! \param ulBase is the base address of the UART port.
//! \param ucData is the character to be transmitted.
//!
//! Sends the character \e ucData to the transmit FIFO for the specified port.
//! If there is no space available in the transmit FIFO, this function waits
//! until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
void
UARTCharPut(unsigned long ulBase, unsigned char ucData)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Wait until space is available.
    //
    while(!(HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXRDY))
    {
    }

    //
    // Send the char.
    //
    HWREGB(ulBase + UART_O_TXBUF) = ucData;
}

//*****************************************************************************
//
//! Determines whether the UART transmitter is busy or not.
//!
//! \param ulBase is the base address of the UART port.
//!
//! Allows the caller to determine whether all transmitted bytes have cleared
//! the transmitter hardware.  If \b false is returned, the transmit FIFO is
//! empty and all bits of the last transmitted character, including all stop
//! bits, have left the hardware shift register.
//!
//! \return Returns \b true if the UART is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
tBoolean
UARTBusy(unsigned long ulBase)
{
    //
    // Check the argument.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine if the UART is busy.
    //
    return((HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXEMPTY) ? false : true);
}

//*****************************************************************************
//
//! Registers an interrupt handler for a UART RX interrupt.
//!
//! \param ulBase is the base address of the UART port.
//! \param pfnHandler is a pointer to the function to be called when the
//! UART interrupt occurs.
//!
//! This function does the actual registering of the interrupt handler.  This
//! will enable the global interrupt in the interrupt controller; specific UART
//! interrupts must be enabled via UARTIntEnable().  It is the interrupt
//! handler's responsibility to clear the interrupt source.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTRXIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_SCIRXINTA : INT_SCIRXINTB );

    //
    // Register the interrupt handler.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the UART interrupt.
    //
    IntEnable(ulInt);
}

//*****************************************************************************
//
//! Registers an interrupt handler for a UART TX interrupt.
//!
//! \param ulBase is the base address of the UART port.
//! \param pfnHandler is a pointer to the function to be called when the
//! UART interrupt occurs.
//!
//! This function does the actual registering of the interrupt handler.  This
//! will enable the global interrupt in the interrupt controller; specific UART
//! interrupts must be enabled via UARTIntEnable().  It is the interrupt
//! handler's responsibility to clear the interrupt source.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTTXIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_SCITXINTA : INT_SCITXINTB );

    //
    // Register the interrupt handler.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the UART interrupt.
    //
    IntEnable(ulInt);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for a UART RX interrupt.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function does the actual unregistering of the interrupt handler.  It
//! will clear the handler to be called when a UART interrupt occurs.  This
//! will also mask off the interrupt in the interrupt controller so that the
//! interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTRXIntUnregister(unsigned long ulBase)
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_SCIRXINTA : INT_SCIRXINTB );

    //
    // Disable the interrupt.
    //
    IntDisable(ulInt);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulInt);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for a UART TX interrupt.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function does the actual unregistering of the interrupt handler.  It
//! will clear the handler to be called when a UART interrupt occurs.  This
//! will also mask off the interrupt in the interrupt controller so that the
//! interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
UARTTXIntUnregister(unsigned long ulBase)
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine the interrupt number based on the UART port.
    //
    ulInt = ((ulBase == UART0_BASE) ? INT_SCITXINTA : INT_SCITXINTB );

    //
    // Disable the interrupt.
    //
    IntDisable(ulInt);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulInt);
}

//*****************************************************************************
//
//! Enables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter is the logical OR of any of the following:
//!
//! - \b UART_INT_OE - Overrun Error interrupt
//! - \b UART_INT_BE - Break Error interrupt
//! - \b UART_INT_PE - Parity Error interrupt
//! - \b UART_INT_FE - Framing Error interrupt
//! - \b UART_INT_RT - Receive Timeout interrupt
//! - \b UART_INT_TX - Transmit interrupt
//! - \b UART_INT_RX - Receive interrupt
//! - \b UART_INT_DSR - DSR interrupt
//! - \b UART_INT_DCD - DCD interrupt
//! - \b UART_INT_CTS - CTS interrupt
//! - \b UART_INT_RI - RI interrupt
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntEnable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Enable the specified interrupts.
    //
    if(ulIntFlags & UART_INT_RXERR)
        HWREGB(ulBase + UART_O_CTL1) |= UART_CTL1_RXERIE;

    if(ulIntFlags & UART_INT_RXRDY_BRKDT)
        HWREGB(ulBase + UART_O_CTL2) |= UART_CTL2_RXBKINTEN;

    if(ulIntFlags & UART_INT_TXRDY)
        HWREGB(ulBase + UART_O_CTL2) |= UART_CTL2_TXINTEN;

    if(ulIntFlags & UART_INT_TXFF)
        HWREGB(ulBase + UART_O_FFTX) |= UART_FFTX_TXFFIENA;

    if(ulIntFlags & UART_INT_RXFF)
        HWREGB(ulBase + UART_O_FFRX) |= UART_FFRX_RXFFIENA;


}

//*****************************************************************************
//
//! Disables individual UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is the bit mask of the interrupt sources to be disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntDisable(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Disable the specified interrupts.
    //
    if(ulIntFlags & UART_INT_RXERR)
        HWREGB(ulBase + UART_O_CTL1) &= ~UART_CTL1_RXERIE;

    if(ulIntFlags & UART_INT_RXRDY_BRKDT)
        HWREGB(ulBase + UART_O_CTL2) &= ~UART_CTL2_RXBKINTEN;

    if(ulIntFlags & UART_INT_TXRDY)
        HWREGB(ulBase + UART_O_CTL2) &= ~UART_CTL2_TXINTEN;

    if(ulIntFlags & UART_INT_TXFF)
        HWREGB(ulBase + UART_O_FFTX) &= ~UART_FFTX_TXFFIENA;

    if(ulIntFlags & UART_INT_RXFF)
        HWREGB(ulBase + UART_O_FFRX) &= ~UART_FFRX_RXFFIENA;
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param ulBase is the base address of the UART port.
//! \param bMasked is \b false if the raw interrupt status is required and
//! \b true if the masked interrupt status is required.
//!
//! This returns the interrupt status for the specified UART.  Either the raw
//! interrupt status or the status of interrupts that are allowed to reflect to
//! the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in UARTIntEnable().
//
//*****************************************************************************
unsigned long
UARTIntStatus(unsigned long ulBase, tBoolean bMasked)
{

    unsigned long temp = 0;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //


    if(HWREGB(ulBase + UART_O_CTL2) & UART_CTL2_TXRDY)
        temp |= UART_INT_TXRDY;

    if(HWREGB(ulBase + UART_O_RXST) & UART_RXST_RXERR)
        temp |= UART_INT_RXERR;

    if(HWREGB(ulBase + UART_O_RXST) & (UART_RXST_RXRDY | UART_RXST_BRKDT))
        temp |= UART_INT_RXRDY_BRKDT;

    if(HWREGB(ulBase + UART_O_FFTX) & UART_FFTX_TXFFINT)
        temp |= UART_INT_TXFF;

    if(HWREGB(ulBase + UART_O_FFRX) & UART_FFRX_RXFFINT)
        temp |= UART_INT_RXFF;

    return temp;
}

//*****************************************************************************
//
//! Clears UART interrupt sources.
//!
//! \param ulBase is the base address of the UART port.
//! \param ulIntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupt from being recognized again immediately upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to UARTIntEnable().
//!
//! \note Because there is a write buffer in the Cortex-M3 processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
UARTIntClear(unsigned long ulBase, unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Clear the requested interrupt sources.
    //
    if(ulIntFlags & (UART_INT_RXERR | UART_INT_RXRDY_BRKDT))
    {
        HWREGB(ulBase + UART_O_CTL1) &= ~UART_CTL1_SWRST;
       __asm(" nop");
       __asm(" nop");
       __asm(" nop");
       __asm(" nop");
        HWREGB(ulBase + UART_O_CTL1) |= UART_CTL1_SWRST;
    }

    if(ulIntFlags & UART_INT_TXFF)
        HWREGB(ulBase + UART_O_FFTX) |= UART_FFTX_TXFFINTCLR;

    if(ulIntFlags & UART_INT_RXFF)
        HWREGB(ulBase + UART_O_FFRX) |= UART_FFRX_RXFFINTCLR;

}

//*****************************************************************************
//
//! Gets current receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function returns the current state of each of the 4 receiver error
//! sources.  The returned errors are equivalent to the four error bits
//! returned via the previous call to UARTCharGet() or UARTCharGetNonBlocking()
//! with the exception that the overrun error is set immediately the overrun
//! occurs rather than when a character is next read.
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b UART_RXERROR_FRAMING, \b UART_RXERROR_PARITY, \b UART_RXERROR_BREAK
//! and \b UART_RXERROR_OVERRUN.
//
//*****************************************************************************
unsigned long
UARTRxErrorGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Return the current value of the receive status register.
    //
    return(HWREG(ulBase + UART_O_RXST));
}

//*****************************************************************************
//
//! Clears all reported receiver errors.
//!
//! \param ulBase is the base address of the UART port.
//!
//! This function is used to clear all receiver error conditions reported via
//! UARTRxErrorGet().  If using the overrun, framing error, parity error or
//! break interrupts, this function must be called after clearing the interrupt
//! to ensure that later errors of the same type trigger another interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
UARTRxErrorClear(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // To clear all errors a sw reset of the module is required
    //
    HWREGB(ulBase + UART_O_CTL1) &= ~UART_CTL1_SWRST;
   __asm(" nop");
   __asm(" nop");
   __asm(" nop");
   __asm(" nop");
    HWREGB(ulBase + UART_O_CTL1) |= UART_CTL1_SWRST;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


