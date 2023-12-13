//###########################################################################
//
// FILE:   uart.h
//
// TITLE:  UART driver.
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

#ifndef UART_H
#define UART_H

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
//! \addtogroup uart_api UART
//! \brief The UART module is used for UART configurations.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************

//*****************************************************************************
//
// Values that can be passed to UART_enableInterrupt,
// UART_disableInterrupt, and UART_clearInterruptStatus
// as the intFlags parameter, and returned from UART_getInterruptStatus.
//
//*****************************************************************************
#define UART_INT_DMATX          0x20000U     //!<DMA TX interrupt
#define UART_INT_DMARX          0x10000U     //!< DMA RX interrupt
#define UART_INT_9BIT           0x1000U      //!<9-bit address match interrupt
#define UART_INT_EOT            0x800U       //!<Receive Interrupt Mask
#define UART_INT_OE             0x400U       //!<Overrun Error Interrupt Mask
#define UART_INT_BE             0x200U       //!<Break Error Interrupt Mask
#define UART_INT_PE             0x100U       //!<Parity Error Interrupt Mask
#define UART_INT_FE             0x080U       //!<Framing Error Interrupt Mask
#define UART_INT_RT             0x040U       //!<Receive Timeout Interrupt Mask
#define UART_INT_TX             0x020U       //!<Transmit Interrupt Mask
#define UART_INT_RX             0x010U       //!<Receive Interrupt Mask

//*****************************************************************************
//
// Values that can be passed to UART_setConfig as the config parameter
// and returned by UART_getConfig in the config parameter.
// Additionally, the UART_CONFIG_PAR_* subset can be passed to
// UART_setParityMode as the parity parameter, and are returned by
// UART_getParityMode.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK   0x00000060UL  //!<Mask for extracting wordlength
#define UART_CONFIG_WLEN_8      0x00000060UL  //!< 8 bit data
#define UART_CONFIG_WLEN_7      0x00000040UL  //!< 7 bit data
#define UART_CONFIG_WLEN_6      0x00000020UL  //!< 6 bit data
#define UART_CONFIG_WLEN_5      0x00000000UL  //!< 5 bit data
#define UART_CONFIG_STOP_MASK   0x00000008UL  //!< Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE    0x00000000UL  //!< One stop bit
#define UART_CONFIG_STOP_TWO    0x00000008UL  //!< Two stop bits
#define UART_CONFIG_PAR_MASK    0x00000086UL  //!< Mask for extracting parity
#define UART_CONFIG_PAR_NONE    0x00000000UL  //!< No parity
#define UART_CONFIG_PAR_EVEN    0x00000006UL  //!< Even parity
#define UART_CONFIG_PAR_ODD     0x00000002UL  //!< Odd parity
#define UART_CONFIG_PAR_ONE     0x00000082UL  //!< Parity bit is one
#define UART_CONFIG_PAR_ZERO    0x00000086UL  //!< Parity bit is zero

//*****************************************************************************
//
// Values that can be passed to UART_setFIFOLevel as the txLevel parameter
// and returned by UART_getFIFOLevel in the txLevel.
// These are 8 bit (1 byte) wide and 16 locations deep FIFOs.
// For example, to get a transmit interrupt after 4 data bytes are transmitted,
// we need a trigger after the transmit FIFO has 4 bytes with 4 locations deep,
// that is, 4 out of 16 locations deep which is 1/4 full.(UART_FIFO_TX2_8)
//
//*****************************************************************************
#define UART_FIFO_TX1_8      0x00000000UL  //!< Transmit interrupt at 1/8 Full
#define UART_FIFO_TX2_8      0x00000001UL  //!< Transmit interrupt at 1/4 Full
#define UART_FIFO_TX4_8      0x00000002UL  //!< Transmit interrupt at 1/2 Full
#define UART_FIFO_TX6_8      0x00000003UL  //!< Transmit interrupt at 3/4 Full
#define UART_FIFO_TX7_8      0x00000004UL  //!< Transmit interrupt at 7/8 Full

//*****************************************************************************
//
// Values that can be passed to UART_setFIFOLevel as the rxLevel parameter
// and returned by UART_getFIFOLevel in the rxLevel.
// These are 8 bit (1 byte) wide and 16 locations deep FIFOs.
// For example, to get a receive interrupt after 4 data bytes are received,
// we need a trigger after the receive FIFO has 4 bytes with 4 locations deep,
// that is, 4 out of 16 locations deep which is 1/4 full.(UART_FIFO_RX2_8)
//
//*****************************************************************************
#define UART_FIFO_RX1_8         0x00000000UL  //!< Receive interrupt at 1/8 Full
#define UART_FIFO_RX2_8         0x00000008UL  //!< Receive interrupt at 1/4 Full
#define UART_FIFO_RX4_8         0x00000010UL  //!< Receive interrupt at 1/2 Full
#define UART_FIFO_RX6_8         0x00000018UL  //!< Receive interrupt at 3/4 Full
#define UART_FIFO_RX7_8         0x00000020UL  //!< Receive interrupt at 7/8 Full

//*****************************************************************************
//
// Values that can be passed to UART_enableDMA() and UART_disableDMA().
//
//*****************************************************************************
#define UART_DMA_ERR_RXSTOP   0x00000004UL  //!< Stop DMA receive if UART error
#define UART_DMA_TX           0x00000002UL  //!< Enable DMA for transmit
#define UART_DMA_RX           0x00000001UL  //!< Enable DMA for receive

//*****************************************************************************
//
// Values returned from UART_getRxError().
//
//*****************************************************************************
#define UART_RXERROR_OVERRUN    0x00000008UL
#define UART_RXERROR_BREAK      0x00000004UL
#define UART_RXERROR_PARITY     0x00000002UL
#define UART_RXERROR_FRAMING    0x00000001UL

//*****************************************************************************
//
// Values that can be passed to UART_setTxIntMode() or returned from
// UART_getTxIntMode().
//
//*****************************************************************************
#define UART_TXINT_MODE_FIFO    0x00000000UL  //!< trigger based on tx FIFOlevel
#define UART_TXINT_MODE_EOT     0x00000010UL  //!< trigger when transmitter idle

//*****************************************************************************
//
// The system clock divider defining the maximum baud rate supported by the
// UART.
//
//*****************************************************************************
#define UART_CLK_DIVIDER        8U

//*****************************************************************************
//
// UART clock frequency in HZ .
// Value that can be passed to UART_setConfig() & UART_getConfig().
//
//*****************************************************************************
#define UART_CLK_FREQ        DEVICE_SYSCLK_FREQ  //!< CPU SYSCLK frequency

//
//Mask for all errors
//
#define UART_RSR_ALL_M  (UART_RSR_BE | UART_RSR_FE | UART_RSR_OE | UART_RSR_PE)

//*****************************************************************************
//
//SIR ( IrDA ) Low Power Baud macro . IrLPBaud16 is nominally 1.8432 MHz.
// Value that can be passed to  UART_setIrDALPDivisor().
//
//*****************************************************************************
#define UART_CLK_IRLPBAUD16       1843200U

//*****************************************************************************
//
// UART interrupt type.Values that can be passed to UART_getInterruptStatus()
//
//*****************************************************************************

#define UART_RAW_INT         false //!<raw interrupt
#define UART_MASKED_INT      true  //!<masked interrupt
typedef bool Uart_IntType;

//*****************************************************************************
//
// Values that can be passed to UART_enableSIR().
//
//*****************************************************************************

#define UART_SIR_LOWPOWER_DISABLE         false //!<raw interrupt
#define UART_SIR_LOWPOWER_ENABLE          true  //!<masked interrupt
typedef bool Uart_SirLPMode;

//*****************************************************************************
//
//! \internal
//! Checks a UART base address.
//!
//! \param base is the base address of the UART port.
//!
//! This function determines if a UART port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UART_isBaseValid(uint32_t base)
{
    return(
           (base == UARTA_BASE) ||
           (base == UARTB_BASE)
          );

}
#endif

//*****************************************************************************
//
//! Sets the type of parity.
//!
//! \param base is the base address of the UART port.
//! \param parity specifies the type of parity to use.
//!
//! This function configures the type of parity to use for transmitting and
//! expect when receiving.  The \e parity parameter must be one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! or \b UART_CONFIG_PAR_ZERO.  The last two parameters allow direct
//! control of the parity bit; it is always either one or zero based on the
//! mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setParityMode(uint32_t base, uint32_t parity)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));
    ASSERT((parity == UART_CONFIG_PAR_NONE) ||
           (parity == UART_CONFIG_PAR_EVEN) ||
           (parity == UART_CONFIG_PAR_ODD) ||
           (parity == UART_CONFIG_PAR_ONE) ||
           (parity == UART_CONFIG_PAR_ZERO));

    //
    // Set the parity mode.
    //
    HWREG(base + UART_O_LCRH) = ((HWREG(base + UART_O_LCRH) &
                                ~(UART_LCRH_SPS | UART_LCRH_EPS |
                                UART_LCRH_PEN)) | parity);
}

//*****************************************************************************
//
//! Gets the type of parity currently being used.
//!
//! \param base is the base address of the UART port.
//!
//! This function gets the type of parity used for transmitting data and
//! expected when receiving data.
//!
//! \return Returns the current parity settings, specified as one of
//! \b UART_CONFIG_PAR_NONE, \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD,
//! \b UART_CONFIG_PAR_ONE, or \b UART_CONFIG_PAR_ZERO.
//
//*****************************************************************************
static inline uint32_t
UART_getParityMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current parity setting.
    //
    return(HWREG(base + UART_O_LCRH) & (UART_LCRH_SPS |
                                        UART_LCRH_EPS |
                                        UART_LCRH_PEN));
}

//*****************************************************************************
//
//! Sets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the UART port.
//! \param txLevel is the transmit FIFO interrupt level, specified as one
//! of \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8, \b UART_FIFO_TX4_8,
//! \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param rxLevel is the receive FIFO interrupt level, specified as one of
//! \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8, \b UART_FIFO_RX4_8,
//! \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function configures the FIFO level at which transmit and receive
//! interrupts are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setFIFOLevel(uint32_t base, uint32_t txLevel,
                     uint32_t rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));
    ASSERT((txLevel == UART_FIFO_TX1_8) ||
           (txLevel == UART_FIFO_TX2_8) ||
           (txLevel == UART_FIFO_TX4_8) ||
           (txLevel == UART_FIFO_TX6_8) ||
           (txLevel == UART_FIFO_TX7_8));
    ASSERT((rxLevel == UART_FIFO_RX1_8) ||
           (rxLevel == UART_FIFO_RX2_8) ||
           (rxLevel == UART_FIFO_RX4_8) ||
           (rxLevel == UART_FIFO_RX6_8) ||
           (rxLevel == UART_FIFO_RX7_8));

    //
    // Set the FIFO interrupt levels.
    //
    HWREG(base + UART_O_IFLS) = txLevel | rxLevel;
}

//*****************************************************************************
//
//! Gets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the UART port.
//! \param txLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b UART_FIFO_TX1_8, \b UART_FIFO_TX2_8,
//! \b UART_FIFO_TX4_8, \b UART_FIFO_TX6_8, or \b UART_FIFO_TX7_8.
//! \param rxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b UART_FIFO_RX1_8, \b UART_FIFO_RX2_8,
//! \b UART_FIFO_RX4_8, \b UART_FIFO_RX6_8, or \b UART_FIFO_RX7_8.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_getFIFOLevel(uint32_t base, uint32_t *txLevel,
                     uint32_t *rxLevel)
{
    uint32_t temp;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Read the FIFO level register.
    //
    temp = HWREG(base + UART_O_IFLS);

    //
    // Extract the transmit and receive FIFO levels.
    //
    *txLevel = temp & UART_IFLS_TXIFLSEL_M;
    *rxLevel = temp & UART_IFLS_RXIFLSEL_M;
}

//*****************************************************************************
//
//! Enables transmitting and receiving.
//!
//! \param base is the base address of the UART port.
//!
//! This function enables the UART and its transmit and receive FIFOs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the FIFO.
    //
    HWREG(base + UART_O_LCRH) |= UART_LCRH_FEN;

    //
    // Enable RX, TX, and the UART.
    //
    HWREG(base + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                 UART_CTL_RXE);
}

//*****************************************************************************
//
//! Disables transmitting and receiving.
//!
//! \param base is the base address of the UART port.
//!
//! This function disables the UART, waits for the end of transmission of the
//! current character, and flushes the transmit FIFO.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait for end of TX.
    //
    while((HWREG(base + UART_O_FR) & UART_FR_BUSY) == UART_FR_BUSY)
    {
    }

    //
    // Disable the FIFO.
    //
    HWREG(base + UART_O_LCRH) &= ~(UART_LCRH_FEN);

    //
    // Disable the UART.
    //
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE |
                                  UART_CTL_RXE);
}

//*****************************************************************************
//
//! Enables the transmit and receive FIFOs.
//!
//! \param base is the base address of the UART port.
//!
//! This functions enables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the FIFO.
    //
    HWREG(base + UART_O_LCRH) |= UART_LCRH_FEN;
}

//*****************************************************************************
//
//! Disables the transmit and receive FIFOs.
//!
//! \param base is the base address of the UART port.
//!
//! This function disables the transmit and receive FIFOs in the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the FIFO.
    //
    HWREG(base + UART_O_LCRH) &= ~(UART_LCRH_FEN);
}

//*****************************************************************************
//
//! Enables transmitting and receiving without FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This function enables the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableModuleNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable RX, TX, and the UART.
    //
    HWREG(base + UART_O_CTL) |= (UART_CTL_UARTEN | UART_CTL_TXE |
                                 UART_CTL_RXE);
}

//*****************************************************************************
//
//! Disables transmitting and receiving without FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This function disables the UART, waits for the end of transmission of the
//! current character.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableModuleNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait for end of TX.
    //
    while((HWREG(base + UART_O_FR) & UART_FR_BUSY) == UART_FR_BUSY)
    {
    }

    //
    // Disable the UART.
    //
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_UARTEN | UART_CTL_TXE |
                                  UART_CTL_RXE);
}

//*****************************************************************************
//
//! Determines if the transmit and receive FIFOs are enabled
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not the
//! transmit and receive FIFOs are enabled.
//!
//! \return Returns \b true if FIFOs are enabled or \b false
//! if FIFOs are not enabled.
//
//*****************************************************************************
static inline bool
UART_isFIFOEnabled(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Returns the FIFO is enabled or disabled.
    //
    return(((HWREG(base + UART_O_LCRH) & UART_LCRH_FEN)== UART_LCRH_FEN) ?
            true : false);
}

//*****************************************************************************
//
//! Enables SIR (IrDA) mode on the specified UART.
//!
//! \param base is the base address of the UART port.
//! \param bLowPower indicates if SIR Low Power Mode is to be used.
//!  This parameter is of type UART_SirLPMode.
//!
//! This function enables SIR (IrDA) mode on the UART.  If the \e bLowPower
//! flag is set, then SIR low power mode will be selected as well.  This
//! function only has an effect if the UART has not been enabled by a call to
//! UART_enableModule().  The call UART_enableSIR() must be made before
//! a call to UART_setConfig() because the UART_setConfig() function
//! calls the UART_enableModule() function.  Another option is to call
//! UART_disableModule() followed by UART_enableSIR() and then enable
//! the UART by calling UART_enableModule().
//!
//! \note The IrDA SIR physical layer specifies a minimum 10-ms delay
//! between transmission and reception which needs to be provided.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableSIR(uint32_t base, Uart_SirLPMode bLowPower)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable SIR and SIRLP (if appropriate).
    //
    if(bLowPower)
    {
        HWREG(base + UART_O_CTL) |= (UART_CTL_SIREN | UART_CTL_SIRLP);
    }
    else
    {
        HWREG(base + UART_O_CTL) = ((HWREG(base + UART_O_CTL) &
                                    ~(UART_CTL_SIREN | UART_CTL_SIRLP)) |
                                    (UART_CTL_SIREN));
    }
}

//*****************************************************************************
//
//! Disables SIR (IrDA) mode on the specified UART.
//!
//! \param base is the base address of the UART port.
//!
//! This function disables SIR(IrDA) mode on the UART.  This function only has
//! an effect if the UART has not been enabled by a call to
//! UART_enableModule().  The call UART_enableSIR() must be made before
//! a call to UART_setConfig() because the UART_setConfig() function
//! calls the UART_enableModule() function.
//! Another option is to call UART_disableModule() followed by
//! UART_enableSIR() and then enable the UART by calling
//! UART_enableModule().
//!
//! \note The IrDA SIR physical layer specifies a minimum 10-ms delay
//! between transmission and reception which needs to be provided.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableSIR(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable SIR and SIRLP (if appropriate).
    //
    HWREG(base + UART_O_CTL) &= ~(UART_CTL_SIREN | UART_CTL_SIRLP);
}

//*****************************************************************************
//
//! Sets the operating mode for the UART transmit interrupt.
//!
//! \param base is the base address of the UART port.
//! \param mode is the operating mode for the transmit interrupt.  It may
//! be \b UART_TXINT_MODE_EOT to trigger interrupts when the transmitter is
//! idle or \b UART_TXINT_MODE_FIFO to trigger based on the current transmit
//! FIFO level.
//!
//! This function allows the mode of the UART transmit interrupt to be set.  By
//! default, the transmit interrupt is asserted when the FIFO level falls past
//! a threshold set via a call to UART_setFIFOLevel().  Alternatively, if this
//! function is called with \e mode set to \b UART_TXINT_MODE_EOT, the
//! transmit interrupt is asserted once the transmitter is completely idle -
//! the transmit FIFO is empty and all bits, including any stop bits, have
//! cleared the transmitter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setTxIntMode(uint32_t base, uint32_t mode)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));
    ASSERT((mode == UART_TXINT_MODE_EOT) ||
           (mode == UART_TXINT_MODE_FIFO));

    //
    // Set or clear the EOT bit of the UART control register as appropriate.
    //
    HWREG(base + UART_O_CTL) = ((HWREG(base + UART_O_CTL) &
                               ~(UART_TXINT_MODE_EOT |
                               UART_TXINT_MODE_FIFO)) | mode);
}

//*****************************************************************************
//
//! Returns the current operating mode for the UART transmit interrupt.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns the current operating mode for the UART transmit
//! interrupt.  The return value is \b UART_TXINT_MODE_EOT if the transmit
//! interrupt is currently configured to be asserted once the transmitter is
//! completely idle - the transmit FIFO is empty and all bits, including any
//! stop bits, have cleared the transmitter.  The return value is
//! \b UART_TXINT_MODE_FIFO if the interrupt is configured to be asserted
//! based on the level of the transmit FIFO.
//!
//! \return Returns \b UART_TXINT_MODE_FIFO or \b UART_TXINT_MODE_EOT.
//
//*****************************************************************************
static inline uint32_t
UART_getTxIntMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current transmit interrupt mode.
    //
    return(HWREG(base + UART_O_CTL) & (UART_TXINT_MODE_EOT |
                                       UART_TXINT_MODE_FIFO));
}

//*****************************************************************************
//
//! Determines if there are any characters in the receive FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is data
//! available in the receive FIFO.
//!
//! \return Returns \b true if there is data in the receive FIFO or \b false
//! if there is no data in the receive FIFO.
//
//*****************************************************************************
static inline bool
UART_isDataAvailable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the availability of characters.
    //
    return(((HWREG(base + UART_O_FR) & UART_FR_RXFE)== UART_FR_RXFE) ?
            false : true);
}

//*****************************************************************************
//
//! Determines if there is any space in the transmit FIFO.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns a flag indicating whether or not there is space
//! available in the transmit FIFO.
//!
//! \return Returns \b true if there is space available in the transmit FIFO
//! or \b false if there is no space available in the transmit FIFO.
//
//*****************************************************************************
static inline bool
UART_isSpaceAvailable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the availability of space.
    //
    return(((HWREG(base + UART_O_FR) & UART_FR_TXFF)== UART_FR_TXFF) ?
            false : true);
}

//*****************************************************************************
//
//! Receives a character from the specified port.
//!
//! \param base is the base address of the UART port.
//!
//! This function gets a character from the receive FIFO for the specified
//! port.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e int32_t.  A \b -1 is returned if there are no characters present in the
//! receive FIFO.  The UART_isDataAvailable() function should be called
//! before attempting to call this function.
//
//*****************************************************************************
static inline int32_t
UART_readCharNonBlocking(uint32_t base)
{
    int32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // See if there are any characters in the receive FIFO.
    //
    if(((HWREG(base + UART_O_FR) & UART_FR_RXFE)) == 0U)
    {
        //
        // Read and return the next character.
        //
        ret = HWREG(base + UART_O_DR);
    }
    else
    {
        //
        // There are no characters, so return a failure.
        //
        ret = -1;
    }
    return(ret);
}

//*****************************************************************************
//
//! Waits for a character from the specified port.
//!
//! \param base is the base address of the UART port.
//!
//! This function gets a character from the receive FIFO for the specified
//! port.  If there are no characters available, this function waits until a
//! character is received before returning.
//!
//! \return Returns the character read from the specified port, cast as a
//! \e int32_t.
//
//*****************************************************************************
static inline int32_t
UART_readChar(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until a char is available.
    //
    while((HWREG(base + UART_O_FR) & UART_FR_RXFE)== UART_FR_RXFE)
    {
    }

    //
    // Now get the char.
    //
    return(HWREG(base + UART_O_DR));
}

//*****************************************************************************
//
//! Waits to send a character from the specified port.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! This function sends the character \e data to the transmit FIFO for the
//! specified port.  If there is no space available in the transmit FIFO, this
//! function waits until there is space available before returning.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_writeChar(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until space is available.
    //
    while((HWREG(base + UART_O_FR) & UART_FR_TXFF)== UART_FR_TXFF)
    {
    }

    //
    // Send the char.
    //
    HWREG(base + UART_O_DR) = data;
}

//*****************************************************************************
//
//! Causes a BREAK to be sent.
//!
//! \param base is the base address of the UART port.
//! \param breakState controls the output level.
//!
//! Calling this function with \e bBreakState set to \b true asserts a break
//! condition on the UART.  Calling this function with \e bBreakState set to
//! \b false removes the break condition.  For proper transmission of a break
//! command, the break must be asserted for at least two complete frames.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setBreakConfig(uint32_t base, bool breakState)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the break condition as requested.
    //
    HWREG(base + UART_O_LCRH) = (breakState ?
                                (HWREG(base + UART_O_LCRH) | UART_LCRH_BRK) :
                                (HWREG(base + UART_O_LCRH) & ~(UART_LCRH_BRK)));
}

//*****************************************************************************
//
//! Determines whether the UART transmitter is busy or not.
//!
//! \param base is the base address of the UART port.
//!
//! This function allows the caller to determine whether all transmitted bytes
//! have cleared the transmitter hardware.  If \b false is returned, the
//! transmit FIFO is empty and all bits of the last transmitted character,
//! including all stop bits, have left the hardware shift register.
//!
//! \return Returns \b true if the UART is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
static inline bool
UART_isBusy(uint32_t base)
{
    //
    // Check the argument.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Determine if the UART is busy.
    //
    return(((HWREG(base + UART_O_FR) & UART_FR_BUSY) == UART_FR_BUSY) ?
            true : false);
}

//*****************************************************************************
//
//! Registers an interrupt handler for a UART interrupt.
//!
//! \param interruptNum specifies the interrupt in question.
//! \param pfnHandler is a pointer to the function to be called when the
//! UART interrupt occurs.
//!
//! This function does the actual registering of the interrupt handler.  This
//! function enables the global interrupt in the interrupt controller; specific
//! UART interrupts must be enabled via UART_enableInterrupt().  It is the
//! interrupt handler's responsibility to clear the interrupt source.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_registerInterrupt(uint32_t interruptNum, void (*pfnHandler)(void))
{

    //
    // Register the interrupt handler.
    //
    Interrupt_register(interruptNum, pfnHandler);

    //
    // Enable the UART interrupt.
    //
    Interrupt_enable(interruptNum);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for a UART interrupt.
//!
//! \param interruptNum specifies the interrupt in question.
//!
//! This function does the actual unregistering of the interrupt handler.  It
//! clears the handler to be called when a UART interrupt occurs.  This
//! function also masks off the interrupt in the interrupt controller so that
//! the interrupt handler no longer is called.
//!
//! \sa Interrupt_unregister() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_unregisterInterrupt(uint32_t interruptNum)
{


    //
    // Disable the interrupt.
    //
    Interrupt_disable(interruptNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregister(interruptNum);
}

//*****************************************************************************
//
//! Clears UART global interrupt flag.
//!
//! \param base is the base address of the UART port.
//!
//! This function clears the indicated UART global interrupt flag register.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_clearGlobalInterruptFlag(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the specified interrupt flag.
    //
    HWREG(base + UART_O_GLB_INT_CLR) = 1U;
}

//*****************************************************************************
//
//! Returns the status of UART global interrupt flag.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns the status of UART global interrupt flag register.
//!
//! \return Returns the status of UART global interrupt flag register.
//
//*****************************************************************************
static inline bool
UART_getGlobalInterruptFlagStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the global interrupt flag status.
    //
    return(HWREG(base + UART_O_GLB_INT_FLG));
}

//*****************************************************************************
//
//! Enables individual UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated UART interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b UART_INT_DMATX - Transmit DMA interrupt
//! - \b UART_INT_DMARX - Receive DMA interrupt
//! - \b UART_INT_9BIT - 9-bit Address Match interrupt
//! - \b UART_INT_EOT - End of Transmission interrupt
//! - \b UART_INT_OE - Overrun Error interrupt
//! - \b UART_INT_BE - Break Error interrupt
//! - \b UART_INT_PE - Parity Error interrupt
//! - \b UART_INT_FE - Framing Error interrupt
//! - \b UART_INT_RT - Receive Timeout interrupt
//! - \b UART_INT_TX - Transmit interrupt
//! - \b UART_INT_RX - Receive interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable the specified interrupts.
    //
    HWREG(base + UART_O_IM) |= intFlags;
}

//*****************************************************************************
//
//! Disables individual UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is the bit mask of the interrupt sources to be
//! disabled.
//!
//! This function disables the indicated UART interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to UART_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable the specified interrupts.
    //
    HWREG(base + UART_O_IM) &= ~(intFlags);
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base is the base address of the UART port.
//! \param masked of type Uart_IntType is UART_RAW_INT
//! if the raw interrupt status is requested and UART_MASKED_INT
//! if the masked interrupt status is requested.
//!
//! This function returns the interrupt status for the specified UART.  Either
//! the raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in UART_enableInterrupt().
//
//*****************************************************************************
static inline uint32_t
UART_getInterruptStatus(uint32_t base, Uart_IntType masked)
{
    uint32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(masked)
    {
        ret = HWREG(base + UART_O_MIS);
    }
    else
    {
        ret = HWREG(base + UART_O_RIS);
    }
    return(ret);
}

//*****************************************************************************
//
//! Clears UART interrupt sources.
//!
//! \param base is the base address of the UART port.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified UART interrupt sources are cleared, so that they no longer
//! assert.  This function must be called in the interrupt handler to keep the
//! interrupt from being triggered again immediately upon exit.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to UART_enableInterrupt().
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    HWREG(base + UART_O_ICR) = intFlags;
}

//*****************************************************************************
//
//! Enable UART uDMA operation.
//!
//! \param base is the base address of the UART port.
//! \param dmaFlags is a bit mask of the uDMA features to enable.
//!
//! The specified UART uDMA features are enabled.  The UART can be
//! configured to use uDMA for transmit or receive and to disable
//! receive if an error occurs.  The \e dmaFlags parameter is the
//! logical OR of any of the following values:
//!
//! - \b UART_DMA_RX - enable uDMA for receive
//! - \b UART_DMA_TX - enable uDMA for transmit
//! - \b UART_DMA_ERR_RXSTOP - disable uDMA receive on UART error
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enableDMA(uint32_t base, uint32_t dmaFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the requested bits in the UART uDMA control register.
    //
    HWREG(base + UART_O_DMACTL) |= dmaFlags;
}

//*****************************************************************************
//
//! Disable UART uDMA operation.
//!
//! \param base is the base address of the UART port.
//! \param dmaFlags is a bit mask of the uDMA features to disable.
//!
//! This function is used to disable UART uDMA features that were enabled
//! by UART_enableDMA().  The specified UART uDMA features are disabled.  The
//! \e dmaFlags parameter is the logical OR of any of the following values:
//!
//! - \b UART_DMA_RX - disable uDMA for receive
//! - \b UART_DMA_TX - disable uDMA for transmit
//! - \b UART_DMA_ERR_RXSTOP - do not disable uDMA receive on UART error
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disableDMA(uint32_t base, uint32_t dmaFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Clear the requested bits in the UART uDMA control register.
    //
    HWREG(base + UART_O_DMACTL) &= ~dmaFlags;
}

//*****************************************************************************
//
//! Gets current receiver errors.
//!
//! \param base is the base address of the UART port.
//!
//! This function returns the current state of each of the 4 receiver error
//! sources.  The returned errors are equivalent to the four error bits
//! returned via the previous call to UART_readChar() or
//! UART_readCharNonBlocking() with the exception that the overrun error is
//! set immediately when the overrun occurs rather than when a character is
//! next read.
//!
//! \return Returns a logical OR combination of the receiver error flags,
//! \b UART_RXERROR_FRAMING, \b UART_RXERROR_PARITY,
//! \b UART_RXERROR_BREAK and \b UART_RXERROR_OVERRUN.
//
//*****************************************************************************
static inline uint32_t
UART_getRxError(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Return the current value of the receive status register.
    //
    return(HWREG(base + UART_O_RSR) & UART_RSR_ALL_M);
}

//*****************************************************************************
//
//! Clears all reported receiver errors.
//!
//! \param base is the base address of the UART port.
//!
//! This function is used to clear all receiver error conditions reported via
//! UART_getRxError().  If using the overrun, framing error, parity error or
//! break interrupts, this function must be called after clearing the interrupt
//! to ensure that later errors of the same type trigger another interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_clearRxError(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Any write to the Error Clear Register clears all bits which are
    // currently set.
    //
    HWREG(base + UART_O_ECR) &= ~UART_RSR_ALL_M;
}

//*****************************************************************************
//
//! Enables 9-bit mode on the specified UART.
//!
//! \param base is the base address of the UART port.
//!
//! This function enables the 9-bit operational mode of the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_enable9Bit(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Enable 9-bit mode.
    //
    HWREG(base + UART_O_9BITADDR) |= UART_9BITADDR_9BITEN;
}

//*****************************************************************************
//
//! Disables 9-bit mode on the specified UART.
//!
//! \param base is the base address of the UART port.
//!
//! This function disables the 9-bit operational mode of the UART.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_disable9Bit(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Disable 9-bit mode.
    //
    HWREG(base + UART_O_9BITADDR) &= ~UART_9BITADDR_9BITEN;
}

//*****************************************************************************
//
//! Sets the device address(es) for 9-bit mode.
//!
//! \param base is the base address of the UART port.
//! \param addr is the device address.
//! \param mask is the device address mask.
//!
//! This function configures the device address or range of device addresses
//! that respond to requests on the 9-bit UART port.  The received address is
//! masked with the mask and then compared against the given address, allowing
//! either a single address (if \b mask is 0xff) or a set of addresses to be
//! matched.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_set9BitAddress(uint32_t base, uint8_t addr,
                    uint8_t mask)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Set the address and mask.
    //
    HWREG(base + UART_O_9BITADDR) = addr << UART_9BITADDR_ADDR_S;
    HWREG(base + UART_O_9BITAMASK) = mask << UART_9BITAMASK_MASK_S;
}

//*****************************************************************************
//
//! Sets the SIR (IrDA) Low Power Divisor.
//!
//! \param base is the base address of the UART port.
//! \param uartClk is the rate of the clock supplied to the UART module.
//! It should be provided as UART_CLK_FREQ using the updated clk rate.
//!
//!
//! This function configures the SIR (IrDA) Low power divisor. This
//! function is used only if the SIR ( IrDA ) is to be used in Low Power
//! mode which is indicated as part of the UART_enableSIR().
//!
//! \return None.
//
//*****************************************************************************
static inline void
UART_setIrDALPDivisor(uint32_t base, uint32_t uartClk)
{
    uint32_t divider;

    //
    // Compute the IrDA Low Power divisor.
    //
    divider = uartClk / UART_CLK_IRLPBAUD16;

    //
    // Set the IrDA Low Power divisor.
    //
    HWREG(base + UART_O_ILPR) = divider;

}

//*****************************************************************************
//
//! Enables internal loopback mode for an UART port.
//!
//! \param base is the base address of the UART module.
//!
//! This function configures an UART port in internal loopback mode to help
//! with diagnostics and debug.In this mode, the UART Tx path is fed through
//! the UARTRx path. This allows data to be transferred between the TX and RX
//! of the same UART port, without having to go through I/O's.UART_writeChar()
//! & UART_writeCharNonBlocking() can be used along with this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void UART_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Write the loopback enable bit to the register.
    //
    HWREG(base + UART_O_CTL) |= UART_CTL_LBE;
}

//*****************************************************************************
//
//! Disables internal loopback mode for an UART port.
//!
//! \param base is the base address of the UART module.
//!
//! This function disables internal loopback mode in an UART port.
//! In this mode, the UARTTx path is not fed through the
//! UARTRx path. This prevents data to be transferred between the TX and RX
//! of the same UART port, without having to go through I/O's.
//!
//! \return None.
//
//*****************************************************************************
static inline void UART_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // clears the loopback enable bit of the register.
    //
    HWREG(base + UART_O_CTL) &= ~UART_CTL_LBE;
}
//*****************************************************************************
//
//! Sends an address character from the specified port when operating in 9-bit
//! mode.
//!
//! \param base is the base address of the UART port.
//! \param addr is the address to be transmitted.
//!
//! This function waits until all data has been sent from the specified port
//! and then sends the given address as an address byte.  It then waits until
//! the address byte has been transmitted before returning.
//!
//! \return None.
//
//*****************************************************************************
extern void UART_send9BitAddress(uint32_t base, uint8_t addr);

//*****************************************************************************
//
//! Exits the 9-bit data transmission mode for the specified port.
//!
//! \param base is the base address of the UART port.
//! \param lcrh is the address/data setting needed to restore the normal
//!  transmission mode after the full 9-bit data transmission.
//!
//! This function waits until all data has been sent from the specified port
//! and then restores the settings for the normal transmission mode.
//!
//! \return None.
//
//*****************************************************************************
extern void UART_stop9BitDataMode(uint32_t base, uint32_t lcrh);

//*****************************************************************************
//
//! Configures the specified port to operate in 9-bit data mode.
//!
//! \param base is the base address of the UART port.
//!
//! This function waits until all data has been sent from the specified port
//! and then configures to send 9-bit data.
//!
//! \note The 9-bit data is sent after the UART_send9BitAddress() is complete.
//!  The data transmission is left to the user to handle outside this API.
//!  This can be done using UART_writeChar() or UART_writeCharNonBlocking().
//!
//! \return Returns the address/data setting needed to restore the normal
//!  transmission mode after the full 9-bit data transmission.
//
//*****************************************************************************
extern uint32_t UART_configure9BitDataMode(uint32_t base);

//*****************************************************************************
//
//! Sets the configuration of a UART.
//!
//! \param base is the base address of the UART port.
//! \param uartClk is the rate of the clock supplied to the UART module.
//! It should be provided as UART_CLK_FREQ using the updated clk rate
//!
//! \param baud is the desired baud rate.
//! \param config is the data format for the port (number of data bits,
//! number of stop bits, and parity).
//!
//! This function configures the UART for operation in the specified data
//! format.  The baud rate is provided in the \e baud parameter and the
//! data format in the \e config parameter.
//!
//! The \e config parameter is the logical OR of three values: the number
//! of data bits, the number of stop bits, and the parity.
//! \b UART_CONFIG_WLEN_8, \b UART_CONFIG_WLEN_7,
//! \b UART_CONFIG_WLEN_6, and \b UART_CONFIG_WLEN_5 select from eight
//! to five data bits per byte (respectively).  \b UART_CONFIG_STOP_ONE
//! and \b UART_CONFIG_STOP_TWO select one or two stop bits (respectively).
//! \b UART_CONFIG_PAR_NONE \b UART_CONFIG_PAR_EVEN,
//! \b UART_CONFIG_PAR_ODD, \b UART_CONFIG_PAR_ONE,
//! and \b UART_CONFIG_PAR_ZERO select the parity mode (no parity bit, even
//! parity bit, odd parity bit, parity bit always one, and parity bit always
//! zero, respectively).
//!
//! \return None.
//
//*****************************************************************************

extern void UART_setConfig(uint32_t base, uint32_t uartClk,
                           uint32_t baud, uint32_t config);

//*****************************************************************************
//
//! Gets the current configuration of a UART.
//!
//! \param base is the base address of the UART port.
//! \param uartClk is the rate of the clock supplied to the UART module.
//! It should be provided as UART_CLK_FREQ using the updated clk rate
//!
//! \param baud is the desired baud rate.
//! \param baud is a pointer to storage for the baud rate.
//! \param config is a pointer to storage for the data format.
//!
//! This function determines the baud rate and data format for the UART, given
//! an explicitly provided peripheral clock.  The
//! returned baud rate is the actual baud rate; it may not be the exact baud
//! rate requested or an ``official'' baud rate.  The data format returned in
//! \e config is enumerated the same as the \e config parameter of
//! UART_setConfig().
//!
//! \return None.
//
//*****************************************************************************

extern void UART_getConfig(uint32_t base, uint32_t uartClk,
                           uint32_t *baud, uint32_t *config);

//*****************************************************************************
//
//! Sends a character to the specified port.
//!
//! \param base is the base address of the UART port.
//! \param data is the character to be transmitted.
//!
//! This function writes the character \e data to the transmit FIFO for the
//! specified port.  This function does not block, so if there is no space
//! available, then a \b false is returned and the application must retry the
//! function later.
//!
//! \return Returns \b true if the character was successfully placed in the
//! transmit FIFO or \b false if there was no space available in the transmit
//! FIFO.
//
//*****************************************************************************

extern bool UART_writeCharNonBlocking(uint32_t base, uint8_t data);

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

#endif // UART_H

