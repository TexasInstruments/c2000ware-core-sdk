//###########################################################################
//
// FILE:   upp.h
//
// TITLE:  C28x uPP driver.
//
//###########################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef UPP_H
#define UPP_H

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
//! \addtogroup upp_api UPP
//! @{
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_upp.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Defines that can be passed as addr field of UPP_DMADescriptor to
// UPP_setDMADescriptor(). Since the addresses for Tx & Rx MSG RAMs are
// different for CPU & DMA views, these defines can be used as DMA descriptor
// addresses.
//
//*****************************************************************************
#define UPP_DMA_TX_MSGRAM_STARTADDR     UPP_TX_MSG_RAM_BASE
#define UPP_DMA_RX_MSGRAM_STARTADDR     0x00007000U

//*****************************************************************************
//
// Defines that can be used in user program as start address for CPU/CLA write
// to TX MSG RAM for transmitting data & for CPU/CLA read from RX MSG RAM for
// receiving data. Since the addresses for Tx & Rx MSG RAMs are different for
// CPU & DMA views, these defines can be used for CPU read/writes.
//
//*****************************************************************************
#define UPP_CPU_TX_MSGRAM_STARTADDR     UPP_TX_MSG_RAM_BASE
#define UPP_CPU_RX_MSGRAM_STARTADDR     UPP_RX_MSG_RAM_BASE

//*****************************************************************************
//
// Defines to specify the size of the uPP Tx and Rx MSG RAMs.
//
//*****************************************************************************
#define UPP_TX_MSGRAM_MAX_SIZE   0x200U
#define UPP_RX_MSGRAM_MAX_SIZE   0x200U

//*****************************************************************************
//
// Define to specify 32 cycle delay between software reset issue & release in
// UPP_performSoftReset().
//
//*****************************************************************************
#ifndef UPP_32_CYCLE_NOP
#define UPP_32_CYCLE_NOP  __asm(" RPT #31 || NOP")
#endif

//*****************************************************************************
//
// Define to specify mask for setting emulation mode in UPP_setEmulationMode().
//
//*****************************************************************************
#define UPP_SOFT_FREE_M        ((uint16_t)UPP_PERCTL_SOFT |                   \
                                (uint16_t)UPP_PERCTL_FREE)

//*****************************************************************************
//
// Defines to specify masks for enabling/disabling uPP Tx/Rx control signals in
// UPP_setTxControlSignalMode() & UPP_setRxControlSignalMode() respectively.
//
//*****************************************************************************
#define UPP_TX_SIGNAL_MODE_M    UPP_IFCFG_WAITA
#define UPP_RX_SIGNAL_MODE_M   ((uint16_t)UPP_IFCFG_STARTA |                   \
                                (uint16_t)UPP_IFCFG_ENAA)

//*****************************************************************************
//
// Define to specify mask for configuring polarities for uPP control signals
// in UPP_setControlSignalPolarity().
//
//*****************************************************************************
#define UPP_SIGNAL_POLARITY_M  ((uint16_t)UPP_IFCFG_WAITPOLA |                 \
                                (uint16_t)UPP_IFCFG_ENAPOLA  |                 \
                                (uint16_t)UPP_IFCFG_STARTPOLA)

//*****************************************************************************
//
// Define to specify masks for returning interrupt status in
// UPP_getInterruptStatus() & UPP_getRawInterruptStatus().
//
//*****************************************************************************
#define UPP_INT_M  ((uint16_t)UPP_ENINTST_DPEI | (uint16_t)UPP_ENINTST_UOEI | \
                    (uint16_t)UPP_ENINTST_EOWI | (uint16_t)UPP_ENINTST_EOLI | \
                    (uint16_t)UPP_ENINTST_DPEQ | (uint16_t)UPP_ENINTST_UOEQ | \
                    (uint16_t)UPP_ENINTST_EOWQ | (uint16_t)UPP_ENINTST_EOLQ)

//*****************************************************************************
//
// Values that can be passed to UPP_enableInterrupt(),
// UPP_disableInterrupt() and UPP_clearInterruptStatus() as the
// intFlags parameter and returned by UPP_getInterruptStatus() &
// UPP_getRawInterruptStatus().
//
//*****************************************************************************
#define UPP_INT_CHI_DMA_PROG_ERR   0x0001U //!<DMA Channel I Programming Error
#define UPP_INT_CHI_UNDER_OVER_RUN 0x0002U //!<DMA Channel I Underrun/Overrun
#define UPP_INT_CHI_END_OF_WINDOW  0x0008U //!<DMA Channel I EndOfWindow Event
#define UPP_INT_CHI_END_OF_LINE    0x0010U //!<DMA Channel I EndOfLine Event
#define UPP_INT_CHQ_DMA_PROG_ERR   0x0100U //!<DMA Channel Q Programming Error
#define UPP_INT_CHQ_UNDER_OVER_RUN 0x0200U //!<DMA Channel Q Underrun/Overrun
#define UPP_INT_CHQ_END_OF_WINDOW  0x0800U //!<DMA Channel Q EndOfWindow Event
#define UPP_INT_CHQ_END_OF_LINE    0x1000U //!<DMA Channel Q EndOfLine Event

//*****************************************************************************
//
//! Values that can be passed to UPP_setEmulationMode() as \e emuMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_EMULATIONMODE_HARDSTOP = 0x0U, //!< uPP stops immediately
    UPP_EMULATIONMODE_RUNFREE  = 0x1U, //!< uPP unaffected by suspend
    UPP_EMULATIONMODE_SOFTSTOP = 0x2U  //!< uPP stops at DMA transaction finish
} UPP_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setOperationMode() as \e opMode parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_RECEIVE_MODE  = 0x0U,  //!< uPP to be configured as Receiver
    UPP_TRANSMIT_MODE = 0x1U   //!< uPP to be configured as Transmitter
} UPP_OperationMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setDataRate() as \e dataRate
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_DATA_RATE_SDR = 0x00000U, //!< uPP to operate in Single Data Rate Mode
    UPP_DATA_RATE_DDR = 0x10000U  //!< uPP to operate in Double Data Rate Mode
} UPP_DataRate;

//*****************************************************************************
//
//! Values that can be passed to UPP_setTxSDRInterleaveMode() as \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_TX_SDR_INTERLEAVE_DISABLE = 0x0U, //!<Interleaving disabled in Tx SDR
    UPP_TX_SDR_INTERLEAVE_ENABLE  = 0x8U  //!<Interleaving enabled in Tx SDR
} UPP_TxSDRInterleaveMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setDDRDemuxMode() as \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_DDR_DEMUX_DISABLE = 0x00U, //!< Demultiplexing disabled in DDR mode
    UPP_DDR_DEMUX_ENABLE  = 0x10U  //!< Demultiplexing enabled in DDR mode
} UPP_DDRDemuxMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setControlSignalPolarity() as \e waitPola,
//! \e enablePola & \e startPola parameters.
//
//*****************************************************************************
typedef enum
{
    UPP_SIGNAL_POLARITY_HIGH  = 0x0U, //!< Signal polarity is active high
    UPP_SIGNAL_POLARITY_LOW   = 0x1U  //!< Signal polarity is active low
} UPP_SignalPolarity;

//*****************************************************************************
//
//! Values that can be passed to UPP_setTxControlSignalMode() &
//! UPP_setRxControlSignalMode() as \e waitMode & \e startMode, \e enableMode
//! parameters respectively.
//
//*****************************************************************************
typedef enum
{
    UPP_SIGNAL_DISABLE = 0x0U,  //!< Control Signal is disabled for uPP
    UPP_SIGNAL_ENABLE  = 0x1U   //!< Control Signal is enabled for uPP
} UPP_SignalMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setClockPolarity() as \e clkPolarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_CLK_NOT_INVERTED = 0x0000U, //!< uPP Clock is not inverted
    UPP_CLK_INVERTED     = 0x1000U  //!< uPP clock is inverted
} UPP_ClockPolarity;

//*****************************************************************************
//
//! Values that can be passed to UPP_configTxIdleDataMode() as \e config
//! parameter. It specifies whether the data lines will drive idle value or
//! get tri-stated when uPP goes to idle state.
//
//*****************************************************************************
typedef enum
{
    UPP_TX_IDLE_DATA_IDLE      = 0x0000U, //!<Data lines will drive idle val
    UPP_TX_IDLE_DATA_TRISTATED = 0x2000U  //!<Data lines will be tristated
} UPP_TxIdleDataMode;

//*****************************************************************************
//
//! Values that can be passed to UPP_setDMAReadThreshold(),
//! UPP_getDMAChannelStatus(), UPP_setDMADescriptor(), UPP_isDescriptorPending(),
//! UPP_isDescriptorActive() & UPP_getDMAFIFOWatermark() as \e channel
//! parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_DMA_CHANNEL_I = 0U,  //!< uPP internal DMA channel I
    UPP_DMA_CHANNEL_Q = 1U   //!< uPP internal DMA channel Q
} UPP_DMAChannel;

//*****************************************************************************
//
//! Values that can be passed to UPP_setTxThreshold() and
//! UPP_setDMAReadThreshold() as \e size parameter.
//
//*****************************************************************************
typedef enum
{
    UPP_THR_SIZE_64BYTE  = 0x0U,  //!< Tx threshold size is 64 bytes
    UPP_THR_SIZE_128BYTE = 0x1U,  //!< Tx threshold size is 128 bytes
    UPP_THR_SIZE_256BYTE = 0x3U   //!< Tx threshold size is 256 bytes
} UPP_ThresholdSize;

//*****************************************************************************
//
//! Values that can be passed to UPP_setInputDelay() as \e delay parameter. All
//! the following values lead to 2 cycle delay on clock pin.
//
//*****************************************************************************
typedef enum
{
    UPP_INPUT_DLY_4  = 0x0U, //!< 4 cycle delay for data & control pins
    UPP_INPUT_DLY_6  = 0x2U, //!< 6 cycle delay for data & control pins
    UPP_INPUT_DLY_9  = 0x4U, //!< 9 cycle delay for data & control pins
    UPP_INPUT_DLY_14 = 0x6U  //!< 14 cycle delay for data & control pins
} UPP_InputDelay;

//*****************************************************************************
//
//! Values that can be passed to UPP_setDMADescriptor() as \e desc
//! parameter.
//
//*****************************************************************************
typedef struct
{
    uint32_t addr;        //!< Starting address of DMA channel transfer
    uint16_t lineCount;   //!< No. of lines in a window for a DMA channel
    uint16_t byteCount;   //!< No. of bytes in a line for a DMA channel
    uint16_t lineOffset;  //!< Offset between start address of two lines
} UPP_DMADescriptor;

//*****************************************************************************
//
//! Values that can be returned by UPP_getDMAChannelStatus() as uPP internal
//! DMA channel current status.
//
//*****************************************************************************
typedef struct
{
    uint32_t curAddr;      //!< Current address of transfer for a DMA channel
    uint16_t curByteCount; //!< Current line no. of transfer for a DMA channel
    uint16_t curLineCount; //!< Current byte no of transfer for a DMA channel
} UPP_DMAChannelStatus;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks the uPP base address.
//!
//! \param base is the base address of the uPP instance used.
//!
//! This function determines if uPP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UPP_isBaseValid(uint32_t base)
{
    return((base == UPP_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks the uPP Rx MSG RAM base address.
//!
//! \param rxBase is the base address of the uPP Rx MSG RAM.
//!
//! This function determines if uPP Rx MSG RAM base address is valid.
//!
//! \return Returns \b true if the rxBase address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UPP_isRxBaseValid(uint32_t rxBase)
{
    return((rxBase == UPP_RX_MSG_RAM_BASE));
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks the uPP Tx MSG RAM base address.
//!
//! \param txBase is the base address of the uPP Tx MSG RAM.
//!
//! This function determines if uPP module base address is valid.
//!
//! \return Returns \b true if the txBase address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UPP_isTxBaseValid(uint32_t txBase)
{
    return((txBase == UPP_TX_MSG_RAM_BASE));
}
#endif

//*****************************************************************************
//
//! Returns uPP internal DMA state machine status.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function returns whether the uPP internal DMA state machine status
//! is idle or burst transaction is active.
//!
//! \return Returns the DMA machine status. It can return following values:
//! - \b true  - DMA burst transaction is active
//! - \b false - DMA is idle
//
//*****************************************************************************
static inline bool
UPP_isDMAActive(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Return the uPP internal DMA status.
    //
    return((HWREGH(base + UPP_O_PERCTL) & UPP_PERCTL_DMAST) != 0U);
}

//*****************************************************************************
//
//! Resets the uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function initiates software reset in uPP.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_performSoftReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Issue uPP software reset.
    //
    HWREGH(base + UPP_O_PERCTL) |= UPP_PERCTL_SOFTRST;

    //
    // Wait for few device clock cycles(~32).
    //
    UPP_32_CYCLE_NOP;

    //
    // Release uPP software reset.
    //
    HWREGH(base + UPP_O_PERCTL) &= ~(uint16_t)UPP_PERCTL_SOFTRST;
}

//*****************************************************************************
//
//! Enables the uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function enables the uPP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable the uPP module.
    //
    HWREGH(base + UPP_O_PERCTL) |= UPP_PERCTL_PEREN;
}

//*****************************************************************************
//
//! Disables the uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function disables the uPP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Disable the uPP module.
    //
    HWREGH(base + UPP_O_PERCTL) &= ~(uint16_t)UPP_PERCTL_PEREN;
}

//*****************************************************************************
//
//! Enables real time emulation mode for uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function enables real time emulation mode in uPP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_enableEmulationMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable uPP real time emulation.
    //
    HWREGH(base + UPP_O_PERCTL) |= UPP_PERCTL_RTEMU;
}

//*****************************************************************************
//
//! Disables real time emulation mode for uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function disables real time emulation mode for uPP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_disableEmulationMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Disable uPP real time emulation.
    //
    HWREGH(base + UPP_O_PERCTL) &= ~(uint16_t)UPP_PERCTL_RTEMU;
}

//*****************************************************************************
//
//! Sets the emulation mode for the uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param emuMode is the mode of operation upon an emulation suspend.
//!
//! This function sets the uPP module's emulation mode. This mode determines
//! how the uPP module is affected by an emulation suspend. Valid
//! values for \e emuMode parameter are the following:
//!
//! - \b UPP_EMULATIONMODE_HARDSTOP - The uPP module stops immediately.
//!
//! - \b UPP_EMULATIONMODE_RUNFREE  - The uPP module is unaffected by an
//!   emulation suspend.
//!
//! - \b UPP_EMULATIONMODE_SOFTSTOP - The uPP module stops after completing
//!   current DMA burst transaction.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setEmulationMode(uint32_t base, UPP_EmulationMode emuMode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set the uPP emulation mode.
    //
    HWREGH(base + UPP_O_PERCTL) = (HWREGH(base + UPP_O_PERCTL) &
                                   ~UPP_SOFT_FREE_M) | (uint16_t)emuMode;

}

//*****************************************************************************
//
//! Sets uPP mode of operation.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param opMode is mode of operation for uPP module.
//!
//! This function sets the uPP mode of opeartion. The \e opMode parameter
//! determines whether uPP module should be configured as transmitter or
//! receiver. It should be passed any of the following values:
//! - \b UPP_RECEIVE_MODE  - uPP is to be operated in Rx mode.
//! - \b UPP_TRANSMIT_MODE - uPP is to be operated in Tx mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setOperationMode(uint32_t base, UPP_OperationMode opMode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set the operation mode for uPP.
    //
    HWREGH(base + UPP_O_CHCTL) = (HWREGH(base + UPP_O_CHCTL)   &
                                  ~(uint16_t)UPP_CHCTL_MODE_M) |
                                 (uint16_t)opMode;
}

//*****************************************************************************
//
//! Sets uPP data rate mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param dataRate is the required uPP data rate mode.
//!
//! This function sets the data rate mode for uPP module as single data rate
//! or double data rate mode. It should be passed any of the following values:
//! - \b UPP_DATA_RATE_SDR - uPP is to be operated in single data rate mode.
//! - \b UPP_DATA_RATE_DDR - uPP is to be operated in double data rate mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setDataRate(uint32_t base, UPP_DataRate dataRate)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set the uPP data rate.
    //
    HWREG(base + UPP_O_CHCTL) = (HWREG(base + UPP_O_CHCTL) &
                                 ~(uint32_t)UPP_CHCTL_DRA) |
                                (uint32_t)dataRate;
}

//*****************************************************************************
//
//! Sets Tx SDR interleave mode for uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param mode is the required SDR interleave mode.
//!
//! This function sets the required interleave mode for SDR Tx uPP. It is
//! valid only for Tx SDR mode & not for Rx SDR mode. The \e mode parameter
//! determines whether interleaving should be enabled or disabled for SDR Tx
//! uPP mode. It should be passed any of the following values:
//! - \b UPP_TX_SDR_INTERLEAVE_DISABLE - specifies interleaving is disabled
//! - \b UPP_TX_SDR_INTERLEAVE_ENABLE  - specifies interleaving is enabled
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setTxSDRInterleaveMode(uint32_t base, UPP_TxSDRInterleaveMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set SDR interleave mode for uPP operating in Tx mode.
    //
    HWREGH(base + UPP_O_CHCTL) = (HWREGH(base + UPP_O_CHCTL)     &
                                  ~(uint16_t)UPP_CHCTL_SDRTXILA) |
                                 (uint16_t)mode;
}

//*****************************************************************************
//
//! Sets DDR de-multiplexing mode for uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param mode is the required DDR de-multiplexing mode.
//!
//! This function sets the demultiplexing mode for uPP DDR mode. The \e mode
//! parameter determines whether demuliplexing to enabled or disabled in DDR
//! mode. It should take following values:
//! - \b UPP_DDR_DEMUX_DISABLE - specifies demultiplexing is disabled
//! - \b UPP_DDR_DEMUX_ENABLE  - specifies demultiplexing is enabled
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setDDRDemuxMode(uint32_t base, UPP_DDRDemuxMode mode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set DDR demultiplexing mode for uPP module.
    //
    HWREGH(base + UPP_O_CHCTL) = (HWREGH(base + UPP_O_CHCTL)   &
                                  ~(uint16_t)UPP_CHCTL_DEMUXA) |
                                 (uint16_t)mode;
}

//*****************************************************************************
//
//! Sets control signal polarity for uPP module.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param waitPola is the required wait signal polarity.
//! \param enablePola is the required enable signal polarity.
//! \param startPola is the required start signal polarity.
//!
//! This function sets the control signal polarity for uPP module. The
//! \e waitPola, \e enablePola, \e startPola parameters determines the
//! control signal polarities. Valid values for these parameters are
//! the following:
//! - \b UPP_SIGNAL_POLARITY_HIGH - Signal polarity to be set as active high.
//! - \b UPP_SIGNAL_POLARITY_LOW  - Signal polarity to be set as active low.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setControlSignalPolarity(uint32_t base, UPP_SignalPolarity waitPola,
                             UPP_SignalPolarity enablePola,
                             UPP_SignalPolarity startPola)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set uPP control signal polarity.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)     &
                                  ~UPP_SIGNAL_POLARITY_M)        |
                                 (((uint16_t)waitPola   << 0x2U) |
                                  ((uint16_t)enablePola << 0x1U) |
                                  (uint16_t)startPola);
}

//*****************************************************************************
//
//! Sets the mode for optional control signals for uPP module in Tx mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param waitMode is the required mode for wait signal.
//!
//! This function sets the mode for optional control signals in Tx mode for
//! uPP module. The \e waitMode parameter determine whether the wait signal
//! is to be enabled or disabled while uPP is in transmit mode. It can take
//! following values:
//! - \b UPP_SIGNAL_DISABLE - Wait signal will be disabled.
//! - \b UPP_SIGNAL_ENABLE  - Wait signal will be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setTxControlSignalMode(uint32_t base, UPP_SignalMode waitMode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable/Disable Tx uPP optional control signals.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)         &
                                  ~(uint16_t)UPP_TX_SIGNAL_MODE_M)   |
                                 ((uint16_t)waitMode << 0x5U);
}

//*****************************************************************************
//
//! Sets the mode for optional control signals for uPP module in Rx mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param enableMode is the required mode for enable signal.
//! \param startMode is the required  mode for start signal.
//!
//! This function sets the mode for optional control signal mode in Rx mode
//! for uPP module.The \e enableMode & \e startMode parameter determine
//! whether the enable & start signals are to be enabled or disabled while
//! uPP is in receive mode. These can take following values:
//! - \b UPP_SIGNAL_DISABLE - Signal will be disabled.
//! - \b UPP_SIGNAL_ENABLE  - Signal will be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setRxControlSignalMode(uint32_t base, UPP_SignalMode enableMode,
                           UPP_SignalMode startMode)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable/Disable Rx uPP optional control signals.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)      &
                                  ~UPP_RX_SIGNAL_MODE_M)          |
                                 (((uint16_t)enableMode << 0x4U)  |
                                  ((uint16_t)startMode  << 0x3U));
}

//*****************************************************************************
//
//! Sets the clock divider when uPP is in Tx mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param divider is the value by which PLLSYSCLK (or CPU1.SYSCLK on a dual
//! core device) is divided.
//!
//! This function configures the clock rate of uPP when it is operating in Tx
//! mode. The \e divider parameter is the value by which SYSCLK rate is divided
//! to get the desired uPP Tx clock rate.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setTxClockDivider(uint32_t base, uint16_t divider)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    ASSERT(divider <= 0xFU);

    //
    // Set the clock divider for uPP Tx mode.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)      &
                                  ~(uint16_t)UPP_IFCFG_CLKDIVA_M) |
                                 (divider << UPP_IFCFG_CLKDIVA_S);
}

//*****************************************************************************
//
//! Sets the uPP clock polarity.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param clkPolarity is the required clock polarity.
//!
//! This function sets the uPP clock polarity. The \e clkPolarity parameter
//! in Tx mode determines whether output Tx clock is to be inverted or not,
//! while in Rx mode it determines whether the Rx input clock is to be treated
//! as inverted or not.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setClockPolarity(uint32_t base, UPP_ClockPolarity clkPolarity)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set uPP clock polarity.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)    &
                                  ~(uint16_t)UPP_IFCFG_CLKINVA) |
                                 (uint16_t)clkPolarity;
}

//*****************************************************************************
//
//! Configures data line behaviour when uPP goes to idle state in Tx mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param config is the required idle mode data line behaviour.
//!
//! This function configures the Tx mode data line behaviour in uPP. The
//! \e config determines whether tri-state is enabled or disabled for uPP
//! idlle time. It can take following values:
//! - \b UPP_TX_IDLE_DATA_IDLE      - uPP will drive idle values to data lines
//!   when it goes to idle mode while operating in Tx mode.
//! - \b UPP_TX_IDLE_DATA_TRISTATED - uPP will tri-state data lines when it
//!   goes to idle mode while operating in Tx mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_configTxIdleDataMode(uint32_t base, UPP_TxIdleDataMode config)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Configure Tx uPP idle data mode.
    //
    HWREGH(base + UPP_O_IFCFG) = (HWREGH(base + UPP_O_IFCFG)    &
                                  ~(uint16_t)UPP_IFCFG_TRISENA) |
                                 (uint16_t)config;
}

//*****************************************************************************
//
//! Sets idle value to be driven by data line when uPP goes to idle state when
//! operating in Tx mode.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param idleVal is the required idle value to be driven in Tx idle state.
//!
//! This function sets idle value to be driven in idle state while uPP is
//! operating in Tx mode. The parameter \e idleVal is the value to be driven
//! \e when Tx uPP is in idle state.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setTxIdleValue(uint32_t base, uint16_t idleVal)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    ASSERT(idleVal <= UPP_IFIVAL_VALA_M);

    //
    // Set Tx uPP idle data line value.
    //
    HWREGH(base + UPP_O_IFIVAL) = (HWREGH(base + UPP_O_IFIVAL)   &
                                   ~(uint16_t)UPP_IFIVAL_VALA_M) | idleVal;
}

//*****************************************************************************
//
//! Sets the I/O transmit threshold.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param size is the required Tx threshold size in bytes.
//!
//! This function sets the i/o transmit threshold. The \e size parameter
//! determines the required size for the threshold to reach in transmit buffer
//! before the tranmission begins. It can take following values:
//! - \b UPP_THR_SIZE_64BYTE  - Sets the Tx threshold to 64 bytes.
//! - \b UPP_THR_SIZE_128BYTE - Sets the Tx threshold to 128 bytes.
//! - \b UPP_THR_SIZE_256BYTE - Sets the Tx threshold to 256 bytes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setTxThreshold(uint32_t base, UPP_ThresholdSize size)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set uPP I/O transmit threshold.
    //
    HWREG(base + UPP_O_THCFG) = (HWREG(base + UPP_O_THCFG)       &
                                 ~(uint32_t)UPP_THCFG_TXSIZEA_M) |
                                ((uint32_t)size << UPP_THCFG_TXSIZEA_S);
}

//*****************************************************************************
//
//! Enables individual uPP module interrupts.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables uPP module interrupt sources. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b UPP_INT_CHI_DMA_PROG_ERR   - DMA Channel I Programming Error
//! - \b UPP_INT_CHI_UNDER_OVER_RUN - DMA Channel I Underrun/Overrun
//! - \b UPP_INT_CHI_END_OF_WINDOW  - DMA Channel I End of Window Event
//! - \b UPP_INT_CHI_END_OF_LINE    - DMA Channel I End of Line Event
//! - \b UPP_INT_CHQ_DMA_PROG_ERR   - DMA Channel Q Programming Error
//! - \b UPP_INT_CHQ_UNDER_OVER_RUN - DMA Channel Q Underrun/Overrun
//! - \b UPP_INT_CHQ_END_OF_WINDOW  - DMA Channel Q End of Window Event
//! - \b UPP_INT_CHQ_END_OF_LINE    - DMA Channel Q End of Line Event
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_enableInterrupt(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable uPP interrupts.
    //
    HWREGH(base + UPP_O_INTENSET) = intFlags;
}

//*****************************************************************************
//
//! Disables individual uPP module interrupts.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables uPP module interrupt sources. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b UPP_INT_CHI_DMA_PROG_ERR   - DMA Channel I Programming Error
//! - \b UPP_INT_CHI_UNDER_OVER_RUN - DMA Channel I Underrun/Overrun
//! - \b UPP_INT_CHI_END_OF_WINDOW  - DMA Channel I End of Window Event
//! - \b UPP_INT_CHI_END_OF_LINE    - DMA Channel I End of Line Event
//! - \b UPP_INT_CHQ_DMA_PROG_ERR   - DMA Channel Q Programming Error
//! - \b UPP_INT_CHQ_UNDER_OVER_RUN - DMA Channel Q Underrun/Overrun
//! - \b UPP_INT_CHQ_END_OF_WINDOW  - DMA Channel Q End of Window Event
//! - \b UPP_INT_CHQ_END_OF_LINE    - DMA Channel Q End of Line Event
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_disableInterrupt(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Disable uPP Interrupts.
    //
    HWREGH(base + UPP_O_INTENCLR) = intFlags;
}

//*****************************************************************************
//
//! Gets the current uPP interrupt status for enabled interrupts.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function returns the interrupt status of enabled interrupts for the
//! uPP module.
//!
//! \return Returns current interrupt status for enabled interrupts,
//! enumerated as a bit field of any of the following values:
//! - \b UPP_INT_CHI_DMA_PROG_ERR   - DMA Channel I Programming Error
//! - \b UPP_INT_CHI_UNDER_OVER_RUN - DMA Channel I Underrun/Overrun
//! - \b UPP_INT_CHI_END_OF_WINDOW  - DMA Channel I End of Window Event
//! - \b UPP_INT_CHI_END_OF_LINE    - DMA Channel I End of Line Event
//! - \b UPP_INT_CHQ_DMA_PROG_ERR   - DMA Channel Q Programming Error
//! - \b UPP_INT_CHQ_UNDER_OVER_RUN - DMA Channel Q Underrun/Overrun
//! - \b UPP_INT_CHQ_END_OF_WINDOW  - DMA Channel Q End of Window Event
//! - \b UPP_INT_CHQ_END_OF_LINE    - DMA Channel Q End of Line Event
//
//*****************************************************************************
static inline uint16_t
UPP_getInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Return uPP interrupt status.
    //
    return(HWREGH(base + UPP_O_ENINTST) & UPP_INT_M);
}

//*****************************************************************************
//
//! Gets the current uPP interrupt status for all the interrupts.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function returns the interrupt status of all the interrupts for the
//! uPP module.
//!
//! \return Returns current interrupt status for all the interrupts,
//! enumerated as a bit field of any of the following values:
//! - \b UPP_INT_CHI_DMA_PROG_ERR   - DMA Channel I Programming Error
//! - \b UPP_INT_CHI_UNDER_OVER_RUN - DMA Channel I Underrun/Overrun
//! - \b UPP_INT_CHI_END_OF_WINDOW  - DMA Channel I End of Window Event
//! - \b UPP_INT_CHI_END_OF_LINE    - DMA Channel I End of Line Event
//! - \b UPP_INT_CHQ_DMA_PROG_ERR   - DMA Channel Q Programming Error
//! - \b UPP_INT_CHQ_UNDER_OVER_RUN - DMA Channel Q Underrun/Overrun
//! - \b UPP_INT_CHQ_END_OF_WINDOW  - DMA Channel Q End of Window Event
//! - \b UPP_INT_CHQ_END_OF_LINE    - DMA Channel Q End of Line Event
//
//*****************************************************************************
static inline uint16_t
UPP_getRawInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Return uPP raw interrupt status.
    //
    return(HWREGH(base + UPP_O_RAWINTST) & UPP_INT_M);
}

//*****************************************************************************
//
//! Clears individual uPP module interrupts.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears uPP module interrupt flags. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b UPP_INT_CHI_DMA_PROG_ERR   - DMA Channel I Programming Error
//! - \b UPP_INT_CHI_UNDER_OVER_RUN - DMA Channel I Underrun/Overrun
//! - \b UPP_INT_CHI_END_OF_WINDOW  - DMA Channel I End of Window Event
//! - \b UPP_INT_CHI_END_OF_LINE    - DMA Channel I End of Line Event
//! - \b UPP_INT_CHQ_DMA_PROG_ERR   - DMA Channel Q Programming Error
//! - \b UPP_INT_CHQ_UNDER_OVER_RUN - DMA Channel Q Underrun/Overrun
//! - \b UPP_INT_CHQ_END_OF_WINDOW  - DMA Channel Q End of Window Event
//! - \b UPP_INT_CHQ_END_OF_LINE    - DMA Channel Q End of Line Event
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_clearInterruptStatus(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Clear uPP interrupt status.
    //
    HWREGH(base + UPP_O_ENINTST) = intFlags;
}

//*****************************************************************************
//
//! Enables uPP global interrupt.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function enables the global interrupt for uPP module which allows
//! uPP to generate interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_enableGlobalInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable uPP global interrupt.
    //
    HWREGH(base + UPP_O_GINTEN) |= UPP_GINTEN_GINTEN;
}

//*****************************************************************************
//
//! Disables uPP global interrupt.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function disables global interrupt for uPP module which restricts
//! uPP to generate any interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_disableGlobalInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Disable uPP global interrupt.
    //
    HWREGH(base + UPP_O_GINTEN) &= ~(uint16_t)UPP_GINTEN_GINTEN;
}

//*****************************************************************************
//
//! Get uPP global interrupt status.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function returns whether any of the uPP interrupt is generated.
//!
//! \return Returns global interrupt status. It can return following values:
//! - \b true  - Interrupt has been generated.
//! - \b false - No interrupt has been generated.
//
//*****************************************************************************
static inline bool
UPP_isInterruptGenerated(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Returns uPP global interrupt status.
    //
    return((HWREGH(base + UPP_O_GINTFLG)   &
            (uint16_t)UPP_GINTFLG_GINTFLG) != 0U);
}

//*****************************************************************************
//
//! Clears uPP global interrupt status.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function clears global interrupt status for uPP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_clearGlobalInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Clear uPP global interrupt status.
    //
    HWREGH(base + UPP_O_GINTCLR) = UPP_GINTCLR_GINTCLR;
}

//*****************************************************************************
//
//! Enables extra delay on uPP input pins.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function enables configurable extra delay on uPP input pins.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_enableInputDelay(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Enable uPP input delay.
    //
    HWREGH(base + UPP_O_DLYCTL) &= ~(uint16_t)UPP_DLYCTL_DLYDIS;
}

//*****************************************************************************
//
//! Disables extra delay on uPP input pins.
//!
//! \param base is the configuration address of the uPP instance used.
//!
//! This function disables extra delay on uPP input pins.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_disableInputDelay(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Disable uPP input delay.
    //
    HWREGH(base + UPP_O_DLYCTL) |= UPP_DLYCTL_DLYDIS;
}

//*****************************************************************************
//
//! Configures delay for uPP input pins.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param delay is the delay to be introduced in input & clock pins.
//!
//! This function sets input delay for uPP input pins. The \e delay parameter
//! specifies the delay to be introduced to input & clock pins. It can take
//! following values. All the following values lead to 2 cycle delay on
//! clock pin.
//! - \b UPP_INPUT_DLY_4  - 4 cycle delay for data & control pins
//! - \b UPP_INPUT_DLY_6  - 6 cycle delay for data & control pins
//! - \b UPP_INPUT_DLY_9  - 9 cycle delay for data & control pins
//! - \b UPP_INPUT_DLY_14 - 14 cycle delay for data & control pins
//!
//! \return None.
//
//*****************************************************************************
static inline void
UPP_setInputDelay(uint32_t base, UPP_InputDelay delay)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));

    //
    // Set uPP input delay.
    //
    HWREGH(base + UPP_O_DLYCTL) = (HWREGH(base + UPP_O_DLYCTL)     &
                                   ~(uint16_t)UPP_DLYCTL_DLYCTL_M) |
                                  (uint16_t)delay;
}

//*****************************************************************************
//
//! Sets the read threshold for uPP internal DMA channels.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel to be configured.
//! \param size is the required read threshold size in bytes.
//!
//! This function sets the read threshold for DMA channel I or Q. The \e size
//! parameter specifies the read threshold in bytes. It can following values:
//! - \b UPP_THR_SIZE_64BYTE  - Sets the DMA read threshold to 64 bytes.
//! - \b UPP_THR_SIZE_128BYTE - Sets the DMA read threshold to 128 bytes.
//! - \b UPP_THR_SIZE_256BYTE - Sets the DMA read threshold to 256 bytes.
//!
//! \return None.
//
//*****************************************************************************
extern void
UPP_setDMAReadThreshold(uint32_t base, UPP_DMAChannel channel,
                        UPP_ThresholdSize size);

//*****************************************************************************
//
//! Sets uPP Internal DMA Channel Descriptors.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel to be configured.
//! \param desc is the required DMA descriptor setting.
//!
//! This function configures DMA descriptors for either channel I or Q which
//! includes starting address of DMA transfer, line count, byte count & line
//! offset address for DMA transfer. In Tx mode, starting address is the
//! address of data buffer to be transmitted while in Rx mode it is the
//! address of buffer where recieved data is to be copied. The \e channel
//! parameter can take any of the following values:
//! - \b UPP_DMA_CHANNEL_I - uPP DMA channel I
//! - \b UPP_DMA_CHANNEL_Q - uPP DMA channel Q
//!
//! \return None.
//
//*****************************************************************************
extern void
UPP_setDMADescriptor(uint32_t base, UPP_DMAChannel channel,
                     const UPP_DMADescriptor * const desc);

//*****************************************************************************
//
//! Returns current status of uPP internal DMA channel transfer.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel.
//! \param status is current status for DMA channel returned by the api.
//!
//! This function returns the current status for either channel I or Q active
//! transfer which includes current DMA transfer address, current line & byte
//! number of the transfer. The \e channel parameter can take any of the
//! following values:
//! - \b UPP_DMA_CHANNEL_I - uPP DMA channel I
//! - \b UPP_DMA_CHANNEL_Q - uPP DMA channel Q
//!
//! \return None.
//
//*****************************************************************************
extern void
UPP_getDMAChannelStatus(uint32_t base, UPP_DMAChannel channel,
                        UPP_DMAChannelStatus * const status);

//*****************************************************************************
//
//! Returns Pend status of uPP internal DMA channel descriptor.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel.
//!
//! This function returns the Pend status for DMA channel I or Q descriptor
//! which specifies whether previous descriptor is copied from shadow register
//! to original register & new descriptor can be programmed or the previous
//! descriptor is still pending & new descriptor cannot be programmed. The
//! \e channel parameter can take following values:
//! - \b UPP_DMA_CHANNEL_I - uPP DMA channel I
//! - \b UPP_DMA_CHANNEL_Q - uPP DMA channel Q
//!
//! \return Returns pend status of DMA channel I descriptor. It can return
//! following values:
//! - \b true  - specifies that writing of new DMA descriptor is not allowed.
//! - \b false - specifies that writing of new DMA descriptor is allowed.
//
//*****************************************************************************
extern bool
UPP_isDescriptorPending(uint32_t base, UPP_DMAChannel channel);

//*****************************************************************************
//
//! Returns active status of uPP Internal DMA Channel descriptor.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel to be configured.
//!
//! This function returns the active status of uPP internal DMA channel I or Q
//! descriptor which specifies whether the descriptor is being currently
//! active(transferring data) or idle. The \e channel parameter can take
//! following values:
//! - \b UPP_DMA_CHANNEL_I - uPP DMA channel I
//! - \b UPP_DMA_CHANNEL_Q - uPP DMA channel Q
//!
//! \return Returns active status of uPP internal DMA channel descriptor.
//! It can return following values:
//! - \b true  - specifies that desciptor is currently active.
//! - \b false - specifies that desciptor is currently idle.
//
//*****************************************************************************
extern bool
UPP_isDescriptorActive(uint32_t base, UPP_DMAChannel channel);

//*****************************************************************************
//
//! Returns watermark for FIFO block count for uPP internal DMA Channel.
//!
//! \param base is the configuration address of the uPP instance used.
//! \param channel is the required uPP internal DMA channel.
//!
//! This function returns watermark for FIFO block count for uPP internal
//! DMA Channel I or Q based on \e channel parameter. The \e channel
//! paramter can take following values:
//! - \b UPP_DMA_CHANNEL_I - uPP DMA channel I
//! - \b UPP_DMA_CHANNEL_Q - uPP DMA channel Q
//!
//! \return Returns active status of DMA channel I descriptor. It can return
//! following values:
//! - \b true  - specifies that desciptor is currently active.
//! - \b false - specifies that desciptor is currently idle.
//
//*****************************************************************************
extern uint16_t
UPP_getDMAFIFOWatermark(uint32_t base, UPP_DMAChannel channel);

//*****************************************************************************
//
//! Reads the received data from uPP Rx MSG RAM.
//!
//! \param rxBase is the uPP Rx MSG RAM base address.
//! \param array is the address of the array of words to be transmitted.
//! \param length is the number of words in the array to be transmitted.
//! \param offset is offset in Rx Data RAM from where data read will start.
//!
//! This function reads the received data from uPP Rx MSG RAM. The sum of
//! parameters \e length & \e offset should be less than the size of the Rx
//! MSG RAM.
//!
//! \return None.
//
//*****************************************************************************
extern void
UPP_readRxMsgRAM(uint32_t rxBase, uint16_t array[], uint16_t length,
                 uint16_t offset);

//*****************************************************************************
//
//! Writes the data to be transmitted in uPP Tx MSG RAM.
//!
//! \param txBase is the uPP Tx MSG RAM base address.
//! \param array is the address of the array of words to be transmitted.
//! \param length is the number of words in the array to be transmitted.
//! \param offset is offset in Tx Data RAM from where data write will start.
//!
//! This function writes the data to be transmitted to uPP Rx MSG RAM. The sum
//! of parameters \e length & \e offset should be less than the size of the Tx
//! MSG RAM.
//!
//! \return None.
//
//*****************************************************************************
extern void
UPP_writeTxMsgRAM(uint32_t txBase, const uint16_t array[], uint16_t length,
                  uint16_t offset);

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

#endif // UPP_H
