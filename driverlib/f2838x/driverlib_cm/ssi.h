//###########################################################################
//
// FILE:   ssi.h
//
// TITLE:  Driver for the SSI module.
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

#ifndef SSI_H
#define SSI_H

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
//! \addtogroup ssi_api SSI
//! \brief This module is used for SSI configurations.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "interrupt.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Values that can be passed to SSI_enableInterrupt, SSI_disableInterrupt,
// and SSI_clearInterruptStatus as the interrupts parameter,
// and returned by SSI_getInterruptStatus.
//
//*****************************************************************************
#define SSI_INT_TXEOT           0x00000040U  // Transmit FIFO is empty
#define SSI_INT_DMATX           0x00000020U  // DMA Transmit complete
#define SSI_INT_DMARX           0x00000010U  // DMA Receive complete
#define SSI_INT_TXFF            0x00000008U  // TX FIFO half full or less
#define SSI_INT_RXFF            0x00000004U  // RX FIFO half full or more
#define SSI_INT_RXTO            0x00000002U  // RX timeout
#define SSI_INT_RXOR            0x00000001U  // RX overrun

//*****************************************************************************
//
// Values that can be passed to SSI_setConfig.
//
//*****************************************************************************
#define SSI_FRF_MOTO_MODE_0     0x00000000U  // Moto/Freescale fmt, pol 0, ph 0
#define SSI_FRF_MOTO_MODE_1     0x00000002U  // Moto/Freescale fmt, pol 0, ph 1
#define SSI_FRF_MOTO_MODE_2     0x00000001U  // Moto/Freescale fmt, pol 1, ph 0
#define SSI_FRF_MOTO_MODE_3     0x00000003U  // Moto/Freescale fmt, pol 1, ph 1
#define SSI_FRF_TI              0x00000010U  // TI frame format

#define SSI_MODE_MASTER         0x00000000U  // SSI master
#define SSI_MODE_SLAVE          0x00000001U  // SSI slave

//*****************************************************************************
//
// Values that can be passed to SSI_enableDMA() and SSI_disableDMA().
//
//*****************************************************************************
#define SSI_DMA_TX              0x00000002U  // Enable DMA for transmit
#define SSI_DMA_RX              0x00000001U  // Enable DMA for receive


//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an SSI base address.
//!
//! \param base specifies the SSI module base address.
//!
//! This function determines if a SSI module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
SSI_isBaseValid(uint32_t base)
{
    return(base == SSI0_BASE);
}
#endif


//*****************************************************************************
//
//! Enables the synchronous serial interface.
//!
//! \param base specifies the SSI module base address.
//!
//! This function enables operation of the synchronous serial interface.  The
//! synchronous serial interface must be configured before it is enabled.
//!
//! \note The function SSI_setConfig() must be called before calling
//! SSI_enableModule() function
//!
//! \return None.
//
//*****************************************************************************

static inline void
SSI_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Read-modify-write the enable bit.
    //
    HWREG(base + SSI_O_CR1) |= SSI_CR1_SSE;
}


//*****************************************************************************
//
//! Disables the synchronous serial interface.
//!
//! \param base specifies the SSI module base address.
//!
//! This function disables operation of the synchronous serial interface.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Read-modify-write the enable bit.
    //
    HWREG(base + SSI_O_CR1) &= ~(SSI_CR1_SSE);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the synchronous serial interface.
//!
//! \param intNum specifies the SSI interrupt number
//! \param pfnHandler is a pointer to the function to be called when the
//! SSI interrupt occurs.
//!
//! This function registers the handler to be called when an SSI interrupt
//! occurs.  This function enables the global interrupt in the interrupt
//! controller; specific SSI interrupts must be enabled via
//! SSI_enableInterrupt().  If necessary, it is the interrupt handler's
//! responsibility to clear the interrupt source via SSI_clearInterruptStatus().
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_registerInterrupt(uint32_t intNum, void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_registerHandler(intNum, pfnHandler);

    //
    // Enable the synchronous serial interface interrupt.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the synchronous serial interface.
//!
//! \param intNum specifies the SSI interrupt number
//!
//! This function clears the handler to be called when an SSI interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_unregisterInterrupt(uint32_t intNum)
{
    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregisterHandler(intNum);
}

//*****************************************************************************
//
//! Enables individual SSI interrupt sources.
//!
//! \param base specifies the SSI module base address.
//! \param interrupts is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated SSI interrupt sources.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt; disabled sources have no effect on the processor.
//! The \e interrupts parameter can be any of the \\b SSI_INT_TXEOT,
//! \b SSI_INT_DMATX, \b SSI_INT_DMARX, \b SSI_INT_TXFF, \b SSI_INT_RXFF,
//! \b SSI_INT_RXTO, or \b SSI_INT_RXOR values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_enableInterrupt(uint32_t base, uint32_t interrupts)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Enable the specified interrupts.
    //
    HWREG(base + SSI_O_IM) |= interrupts;
}


//*****************************************************************************
//
//! Disables individual SSI interrupt sources.
//!
//! \param base specifies the SSI module base address.
//! \param interrupts is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated SSI interrupt sources.  The
//! \e interrupts parameter can be any of the \b SSI_INT_TXEOT,
//! \b SSI_INT_DMATX, \b SSI_INT_DMARX, \b SSI_INT_TXFF, \b SSI_INT_RXFF,
//! \b SSI_INT_RXTO, or \b SSI_INT_RXOR values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_disableInterrupt(uint32_t base, uint32_t interrupts)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Disable the specified interrupts.
    //
    HWREG(base + SSI_O_IM) &= ~(interrupts);
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base specifies the SSI module base address.
//! \param masked is \b false if the raw interrupt status is required or
//! \b true if the masked interrupt status is required.
//!
//! This function returns the interrupt status for the SSI module.  Either the
//! raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return The current interrupt status, enumerated as a bit field of
//! \b SSI_INT_TXEOT, \b SSI_INT_DMATX, b SSI_INT_DMARX, \b SSI_INT_TXFF,
//! \b SSI_INT_RXFF, \b SSI_RXTO, or \b SSI_RXOR
//
//*****************************************************************************
static inline uint32_t
SSI_getInterruptStatus(uint32_t base, bool masked)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //

    return(masked ? HWREG(base + SSI_O_MIS) : HWREG(base + SSI_O_RIS));

}
//*****************************************************************************
//
//! Clears SSI interrupt sources.
//!
//! \param base specifies the SSI module base address.
//! \param interrupts is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears the specified SSI interrupt sources so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupts from being triggered again immediately upon exit.  The
//! \e interrupts parameter can consist of either or both the \b SSI_RXTO and
//! \b SSI_RXOR values.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
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
static inline void
SSI_clearInterruptStatus(uint32_t base, uint32_t interrupts)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    HWREG(base + SSI_O_ICR) = interrupts;
}

//*****************************************************************************
//
//! Enables SSI DMA operation.
//!
//! \param base is the base address of the SSI module.
//! \param dmaFlags is a bit mask of the DMA features to enable.
//!
//! This function enables the specified SSI DMA features.  The SSI can be
//! configured to use DMA for transmit and/or receive data transfers.
//! The \e dmaFlags parameter is the logical OR of any of the following
//! values:
//!
//! - SSI_DMA_RX - enable DMA for receive
//! - SSI_DMA_TX - enable DMA for transmit
//!
//! \note The uDMA controller must also be set up before DMA can be used
//! with the SSI.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_enableDMA(uint32_t base, uint32_t dmaFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Set the requested bits in the SSI DMA control register.
    //
    HWREG(base + SSI_O_DMACTL) |= dmaFlags;
}

//*****************************************************************************
//
//! Disables SSI DMA operation.
//!
//! \param base is the base address of the SSI module.
//! \param dmaFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable SSI DMA features that were enabled
//! by SSI_enableDMA().  The specified SSI DMA features are disabled.  The
//! \e dmaFlags parameter is the logical OR of any of the following values:
//!
//! - SSI_DMA_RX - disable DMA for receive
//! - SSI_DMA_TX - disable DMA for transmit
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_disableDMA(uint32_t base, uint32_t dmaFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Clear the requested bits in the SSI DMA control register.
    //
    HWREG(base + SSI_O_DMACTL) &= ~dmaFlags;
}

//*****************************************************************************
//
//! Determines whether the SSI transmitter is busy or not.
//!
//! \param base is the base address of the SSI module.
//!
//! This function allows the caller to determine whether all transmitted bytes
//! have cleared the transmitter hardware.  If \b false is returned, then the
//! transmit FIFO is empty and all bits of the last transmitted word have left
//! the hardware shift register.
//!
//! \return Returns \b true if the SSI is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
static inline bool
SSI_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Determine if the SSI is busy.
    //
     return(((HWREG(base + SSI_O_SR) & SSI_SR_BSY) == SSI_SR_BSY));
}

//*****************************************************************************
//
//! Enables internal loopback mode for SSI.
//!
//! \param base is the base address of the SSI module.
//!
//! This function configures SSI port in internal loopback mode to help with
//! diagnostics and debug.  In this mode, Output of the transmit serial
//! shift register is connected internally to the input of the receive
//! serial shift register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Enable loopback
    //
    HWREG(base + SSI_O_CR1) |= SSI_CR1_LBM;
}

//*****************************************************************************
//
//! Disables internal loopback mode for SSI.
//!
//! \param base is the base address of the SSI module.
//!
//! This function is used to disable SSI internal loopback that was enabled by
//! SSI_enableLoopback().
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Enable loopback
    //
    HWREG(base + SSI_O_CR1) &= ~SSI_CR1_LBM;
}

//*****************************************************************************
//
//! Enables the Fss hold feature
//!
//! \param base is the base address of the SSI module.
//!
//! This function configures the SSI module to hold the FSS low when there is
//! available data in the Tx FIFO. The Fss signal is de-asserted when the Tx
//! FIFO is empty
//!
//! \note This feature is not available in TI frame format. It is only
//! available in Freescale frame format.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_enableFssHold(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Set the hold frame bit.
    //
    HWREG(base + SSI_O_CR1) |= SSI_CR1_FSSHLDFRM;
}

//*****************************************************************************
//
//! Disables the Fss hold feature
//!
//! \param base is the base address of the SSI module.
//!
//! This function configures the SSI module to de-assert the SSIFss signal
//! for one SSI clock cycle after every byte is transferred.
//! This mode is the default operation.
//!
//! \note This feature is not available in TI frame format. It is only
//! available in Freescale frame format.
//!
//! \return None.
//
//*****************************************************************************
static inline void
SSI_disableFssHold(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SSI_isBaseValid(base));

    //
    // Clear the hold frame bit.
    //
    HWREG(base + SSI_O_CR1) &= ~(SSI_CR1_FSSHLDFRM);
}


//*****************************************************************************
//
//! Configures the synchronous serial interface.
//!
//! \param base specifies the SSI module base address.
//! \param ssiClk is the rate of the clock supplied to the SSI module.
//! \param protocol specifies the data transfer protocol.
//! \param mode specifies the mode of operation.
//! \param bitRate specifies the clock rate.
//! \param dataWidth specifies number of bits transferred per frame.
//!
//! This function configures the synchronous serial interface.  It sets
//! the SSI protocol, mode of operation, bit rate, and data width.
//!
//! The \e protocol parameter defines the data frame format.  The
//! \e protocol parameter can be one of the following values:
//! \b SSI_FRF_MOTO_MODE_0, \b SSI_FRF_MOTO_MODE_1, \b SSI_FRF_MOTO_MODE_2,
//! \b SSI_FRF_MOTO_MODE_3 or \b SSI_FRF_TI.
//! The Motorola/Freescale frame formats encode the following polarity and phase
//! configurations:
//!
//! <pre>
//! Polarity Phase       mode
//!   0       0   SSI_FRF_MOTO_MODE_0
//!   0       1   SSI_FRF_MOTO_MODE_1
//!   1       0   SSI_FRF_MOTO_MODE_2
//!   1       1   SSI_FRF_MOTO_MODE_3
//! </pre>
//!
//! The \e mode parameter defines the operating mode of the SSI module.
//! The SSI module can operate as a master or slave. The \e mode parameter
//! can be one of the following values: \b SSI_MODE_MASTER or \b SSI_MODE_SLAVE.
//!
//! The \e bitRate parameter defines the bit rate for the SSI.  This bit
//! rate must satisfy the following clock ratio criteria:
//!
//! - ssiClk >= 2 * bit rate (master mode)
//! - ssiClk >= 12 * bit rate (slave modes)
//!
//! where ssiClk is the frequency of the clock supplied to the SSI module. Note
//! that there are frequency limits for FSSI that are described in the Bit Rate
//! Generation section of the SSI chapter in the data sheet.
//!
//! The \e dataWidth parameter defines the width of the data transfers and
//! can be a value between 4 and 16, inclusive.
//!
//! The peripheral clock is the same as the processor clock. The macro
//! CM_CLK_FREQ from sysctl.h can be used as the parameter
//!
//! \return None.
//
//*****************************************************************************
extern void
SSI_setConfig(uint32_t base, uint32_t ssiClk, uint32_t protocol,
              uint32_t mode, uint32_t bitRate, uint32_t dataWidth);

//*****************************************************************************
//
//! Puts a data element into the SSI transmit FIFO.
//!
//! \param base specifies the SSI module base address.
//! \param data is the data to be transmitted over the SSI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SSI module.  If there is no space available in the transmit FIFO,
//! this function waits until there is space available before returning.
//!
//! \note The upper 32 - N bits of \e data are discarded by the hardware,
//! where N is the data width as configured by SSI_setConfig().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e data are discarded.
//!
//! \return None.
//
//*****************************************************************************
extern void
SSI_writeData(uint32_t base, uint32_t data);

//*****************************************************************************
//
//! Puts a data element into the SSI transmit FIFO.
//!
//! \param base specifies the SSI module base address.
//! \param data is the data to be transmitted over the SSI interface.
//!
//! This function places the supplied data into the transmit FIFO of the
//! specified SSI module.  If there is no space in the FIFO, then this function
//! returns a zero.
//!
//! \note The upper 32 - N bits of \e data are discarded by the hardware,
//! where N is the data width as configured by SSI_setConfig().  For
//! example, if the interface is configured for 8-bit data width, the upper 24
//! bits of \e data are discarded.
//!
//! \return Returns the number of elements written to the SSI transmit FIFO.
//
//*****************************************************************************
extern int32_t
SSI_writeDataNonBlocking(uint32_t base, uint32_t data);

//*****************************************************************************
//
//! Gets a data element from the SSI receive FIFO.
//!
//! \param base specifies the SSI module base address.
//! \param dataPtr is a pointer to a storage location for data that was
//! received over the SSI interface.
//!
//! This function gets received data from the receive FIFO of the specified
//! SSI module and places that data into the location specified by the
//! \e dataPtr parameter.  If there is no data available, this function waits
//! until data is received before returning.
//!
//! \note Only the lower N bits of the value written to \e dataPtr contain
//! valid data, where N is the data width as configured by
//! SSI_setConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to
//! \e dataPtr contain valid data.
//!
//! \return None.
//
//*****************************************************************************
extern void
SSI_readData(uint32_t base, uint32_t *dataPtr);

//*****************************************************************************
//
//! Gets a data element from the SSI receive FIFO.
//!
//! \param base specifies the SSI module base address.
//! \param dataPtr is a pointer to a storage location for data that was
//! received over the SSI interface.
//!
//! This function gets received data from the receive FIFO of the specified SSI
//! module and places that data into the location specified by the \e data
//! parameter.  If there is no data in the FIFO, then this function returns a
//! zero.
//!
//! \note Only the lower N bits of the value written to \e dataPtr contain
//! valid data, where N is the data width as configured by
//! SSI_setConfig().  For example, if the interface is configured for
//! 8-bit data width, only the lower 8 bits of the value written to
//! \e dataPtr contain valid data.
//!
//! \return Returns the number of elements read from the SSI receive FIFO.
//
//*****************************************************************************
extern int32_t
SSI_readDataNonBlocking(uint32_t base, uint32_t *dataPtr);


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

#endif // SSI_H
