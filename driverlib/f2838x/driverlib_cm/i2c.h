//###########################################################################
//
// FILE:   i2c.h
//
// TITLE:  CM I2C driver.
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

#ifndef I2C_H
#define I2C_H

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
//! \addtogroup i2c_api I2C
//! @{
//
//*****************************************************************************

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "interrupt.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
//Values that can be returned from I2C_getMasterErr() as I2C Master error
//status
//
//*****************************************************************************
#define I2C_MASTER_ERR_NONE     0X00000000U  //!< No error
#define I2C_MASTER_ERR_ADDR_ACK 0x00000004U  //!< Acknowledge Address error
#define I2C_MASTER_ERR_DATA_ACK 0x00000008U  //!< Acknowledge Data error
#define I2C_MASTER_ERR_ARB_LOST 0x00000010U  //!< Arbitration Lost error
#define I2C_MASTER_ERR_CLK_TOUT 0x00000080U  //!< Clock Timeout error

//*****************************************************************************
//
// Values that can be passed to I2C_enableMasterIntSource() as I2C Master
// interrupts
//
//*****************************************************************************
#define I2C_MASTER_INT_RX_FIFO_FULL   0x00000800U  //!< RX FIFO Full Interrupt
#define I2C_MASTER_INT_TX_FIFO_EMPTY  0x00000400U  //!< TX FIFO Empty Intrpt
#define I2C_MASTER_INT_RX_FIFO_REQ    0x00000200U  //!< RX FIFO Request Intrpt
#define I2C_MASTER_INT_TX_FIFO_REQ    0x00000100U  //!< TX FIFO Request Intrpt
#define I2C_MASTER_INT_ARB_LOST       0x00000080U  //!< Arb Lost Interrupt
#define I2C_MASTER_INT_STOP           0x00000040U  //!< Stop Condition Intrpt
#define I2C_MASTER_INT_START          0x00000020U  //!< Start Condition Intrpt
#define I2C_MASTER_INT_NACK           0x00000010U  //!< Addr/Data NACK Intrpt
#define I2C_MASTER_INT_TX_DMA_DONE    0x00000008U  //!< TX DMA Complete Intrpt
#define I2C_MASTER_INT_RX_DMA_DONE    0x00000004U  //!< RX DMA Complete Intrpt
#define I2C_MASTER_INT_TIMEOUT        0x00000002U  //!< Clock Timeout Intrpt
#define I2C_MASTER_INT_DATA           0x00000001U  //!< Data Interrupt

//*****************************************************************************
//
// Values that are returned from I2C_getSlaveStatus() as I2C Slave
// action requests
//
//*****************************************************************************
#define I2C_SLAVE_ACT_NONE      0x00000000U  //!< Master has sent no command
#define I2C_SLAVE_ACT_RREQ      0x00000001U  //!< Master has sent data
#define I2C_SLAVE_ACT_TREQ      0x00000002U  //!< Master has requested data
#define I2C_SLAVE_ACT_RREQ_FBR  0x00000005U  //!< Master has sent first byte
#define I2C_SLAVE_ACT_OWN2SEL   0x00000008U  //!< Master requested secondary
                                             //!< slave
#define I2C_SLAVE_ACT_QCMD      0x00000010U  //!< Master has sent Quick Command
#define I2C_SLAVE_ACT_QCMD_DATA 0x00000020U  //!< Master Quick Command value

//*****************************************************************************
//
// Values that are returned from I2C_getSlaveStatus() as I2C DMA status
//
//*****************************************************************************
#define I2C_SLAVE_DMA_TX    0x00000040U  //!< DMA TX active
#define I2C_SLAVE_DMA_RX    0x00000080U  //!< DMA RX active

//*****************************************************************************
//
// Miscellaneous I2C driver definitions.
//
//*****************************************************************************
#define I2C_MASTER_MAX_RETRIES    1000U        //!< Number of retries

#define I2C_SA_A6_0_MASK          0x80U        //!< Mask for Slave Address A6-0
#define I2C_TXFIFO_MASK           0xffff0000U  //!< TX FIFO Mask
#define I2C_RXFIFO_MASK           0x0000ffffU  //!< RX FIFO Mask
#define I2C_SCL_FREQ_FAST_MODE    400000U      //!< SCL freq Fast mode
#define I2C_SCL_FREQ_STD_MODE     100000U      //!< SCL freq Std mode
#define I2C_SCL_FREQ_HS_MODE      3400000U     //!< SCL freq High speed mode

//*****************************************************************************
//
// Values that can be passed to I2C_enableSlaveIntSource() as I2C Slave
// interrupts
//
//*****************************************************************************
#define I2C_SLAVE_INT_RX_FIFO_FULL     0x00000100U  //!< RX FIFO Full Intrpt
#define I2C_SLAVE_INT_TX_FIFO_EMPTY    0x00000080U  //!< TX FIFO Empty Intrpt
#define I2C_SLAVE_INT_RX_FIFO_REQ      0x00000040U  //!< RX FIFO Req Intrpt
#define I2C_SLAVE_INT_TX_FIFO_REQ      0x00000020U  //!< TX FIFO Req Intrpt
#define I2C_SLAVE_INT_TX_DMA_DONE      0x00000010U  //!< TX DMA Complete Intrpt
#define I2C_SLAVE_INT_RX_DMA_DONE      0x00000008U  //!< RX DMA Complete Intrpt
#define I2C_SLAVE_INT_STOP             0x00000004U  //!< Stop Condition Intrpt
#define I2C_SLAVE_INT_START            0x00000002U  //!< Start Condition Intrpt
#define I2C_SLAVE_INT_DATA             0x00000001U  //!< Data Interrupt

//*****************************************************************************
//
// Values that can be passed to I2C_enableFIFO() for I2C FIFO configuration
//
//*****************************************************************************
#define I2C_SLAVE_TX_FIFO_ENABLE          0x00000002U //!< TX FIFO enable
#define I2C_SLAVE_RX_FIFO_ENABLE          0x00000004U //!< RX FIFO enable

//*****************************************************************************
//
// Values that can be passed to I2C_configureSlaveAckOverride() as  I2C Slave
// Ack override enable/Disable configuration
//
//*****************************************************************************
#define I2C_SLAVE_ACK_OVERRIDE_ENABLE    true  //!<Slave ACK override enable
#define I2C_SLAVE_ACK_OVERRIDE_DISABLE   false //!<Slave ACK override disable

//*****************************************************************************
//
// Values that can be passed to I2C_setSlaveAckValue() for I2C
// Slave Ack / Nack configuration
//
//*****************************************************************************
#define I2C_SLAVE_ACK     true    //!<Slave ACK
#define I2C_SLAVE_NACK    false   //!<Slave NACK

//*****************************************************************************
//
// Values that are returned from I2C_getTxFIFOStatus() & I2C_getRxFIFOStatus()
// as I2C FIFO status
//
//*****************************************************************************
#define I2C_FIFO_RX_BELOW_TRIG_LEVEL     0x00040000U //!< RX FIFO below Trigger
                                                     //!< level
#define I2C_FIFO_RX_FULL                 0x00020000U //!< RX FIFO Full
#define I2C_FIFO_RX_EMPTY                0x00010000U //!< RX FIFO Empty
#define I2C_FIFO_TX_BELOW_TRIG_LEVEL     0x00000004U //!< TX FIFO below Trigger
                                                     //!< level
#define I2C_FIFO_TX_FULL                 0x00000002U //!< TX FIFO Full
#define I2C_FIFO_TX_EMPTY                0x00000001U //!< TX FIFO Empty

#define I2C_FIFOSTATUS_TX_M              0x00000007U //!< TX FIFO mask
#define I2C_FIFOSTATUS_RX_M              0x00070000U //!< RX FIFO mask

//*****************************************************************************
//
// Values that can be passed to I2C_initMaster() as I2C clock frequency in Hz
//
//*****************************************************************************
#define I2C_CLK_FREQ                CM_CLK_FREQ    //!<CM CPU freq

//*****************************************************************************
//
// Values that can be passed to I2C_isMasterIntActive(),
// I2C_getMasterIntStatus(),I2C_isSlaveIntActive() &
// I2C_getSlaveIntStatus() as I2C interrupt type
//
//*****************************************************************************

#define I2C_MASTER_RAW_INT             false //!<raw interrupt
#define I2C_MASTER_MASKED_INT          true  //!<masked interrupt
typedef bool I2C_MasterIntType;

//*****************************************************************************
//
// Values that can be passed to I2C_setSlaveAddress() to select
// I2C Master Read / write
//
//*****************************************************************************
typedef enum
{
    I2C_MASTER_WRITE        = 0x00U, //!<Master Read from slave
    I2C_MASTER_READ         = 0x01U  //!<Master write to slave

} I2C_MasterRW;

//*****************************************************************************
//
// Values that can be passed to I2C_setOwnSlaveAddress() for I2C Slave
// Address configuration
//
//*****************************************************************************

typedef enum
{
    I2C_SLAVE_ADDR_PRIMARY          = 0x00U, //!<primary address
    I2C_SLAVE_ADDR_SECONDARY        = 0x01U  //!<secondary address

} I2C_SlaveAddrmode;

//*****************************************************************************
//
// Values that can be passed to I2C_setMasterConfig() as I2C Master commands
//
//*****************************************************************************

typedef enum
{
    //! SINGLE SEND
    I2C_MASTER_CMD_SINGLE_SEND                   = 0x00000007U,
    //! SINGLE RECV
    I2C_MASTER_CMD_SINGLE_RECEIVE                = 0x00000007U,
    //! BURST SEND START
    I2C_MASTER_CMD_BURST_SEND_START              = 0x00000003U,
    //! BURST SEND CONT
    I2C_MASTER_CMD_BURST_SEND_CONT               = 0x00000001U,
    //! BURST SEND FINISH
    I2C_MASTER_CMD_BURST_SEND_FINISH             = 0x00000005U,
    //! BURST SEND STOP
    I2C_MASTER_CMD_BURST_SEND_STOP               = 0x00000004U,
    //! BURST SEND ERROR_STOP
    I2C_MASTER_CMD_BURST_SEND_ERROR_STOP         = 0x00000004U,
    //! BURST RECEIVE START
    I2C_MASTER_CMD_BURST_RECEIVE_START           = 0x0000000bU,
    //! BURST RECEIVE CONT
    I2C_MASTER_CMD_BURST_RECEIVE_CONT            = 0x00000009U,
    //! BURST RECEIVE FINISH
    I2C_MASTER_CMD_BURST_RECEIVE_FINISH          = 0x00000005U,
    //! BURST RECEIVE ERROR STOP
    I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP      = 0x00000004U,
    //! QUICK COMMAND
    I2C_MASTER_CMD_QUICK_COMMAND                 = 0x00000027U,
    //! HS MASTER CODE SEND
    I2C_MASTER_CMD_HS_MASTER_CODE_SEND           = 0x00000013U,
    //! FIFO SINGLE SEND
    I2C_MASTER_CMD_FIFO_SINGLE_SEND              = 0x00000046U,
    //! FIFO SINGLE RECEIVE
    I2C_MASTER_CMD_FIFO_SINGLE_RECEIVE           = 0x00000046U,
    //! FIFO BURST SEND START
    I2C_MASTER_CMD_FIFO_BURST_SEND_START         = 0x00000042U,
    //! FIFO BURST SEND CONT
    I2C_MASTER_CMD_FIFO_BURST_SEND_CONT          = 0x00000040U,
    //! FIFO BURST SEND FINISH
    I2C_MASTER_CMD_FIFO_BURST_SEND_FINISH        = 0x00000044U,
    //! BURST SEND ERROR STOP
    I2C_MASTER_CMD_FIFO_BURST_SEND_ERROR_STOP    = 0x00000004U,
    //! BURST RECEIVE START
    I2C_MASTER_CMD_FIFO_BURST_RECEIVE_START      = 0x0000004aU,
    //! BURST RECEIVE CONT
    I2C_MASTER_CMD_FIFO_BURST_RECEIVE_CONT       = 0x00000048U,
    //! FIFO BURST RECEIVE FINISH
    I2C_MASTER_CMD_FIFO_BURST_RECEIVE_FINISH     = 0x00000044U,
    //! FIFO BURST RECEIVE ERROR STOP
    I2C_MASTER_CMD_FIFO_BURST_RECEIVE_ERROR_STOP = 0x00000004U
} I2C_MasterControl;

//*****************************************************************************
//
// Values that can be passed to I2C_configureMasterGlitchFilter() as I2C
// Master glitch filter configuration
//
//*****************************************************************************
typedef enum
{
    I2C_MASTER_GLITCH_FILTER_DISABLED    = 0x00000000U,      //!< Bypass
    I2C_MASTER_GLITCH_FILTER_1           = 0x00010000U,      //!< 1 clock
    I2C_MASTER_GLITCH_FILTER_2           = 0x00020000U,      //!< 2 clocks
    I2C_MASTER_GLITCH_FILTER_3           = 0x00030000U,      //!< 3 clocks
    I2C_MASTER_GLITCH_FILTER_4           = 0x00040000U,      //!< 4 clocks
    I2C_MASTER_GLITCH_FILTER_8           = 0x00050000U,      //!< 8 clocks
    I2C_MASTER_GLITCH_FILTER_16          = 0x00060000U,      //!< 16 clocks
    I2C_MASTER_GLITCH_FILTER_31          = 0x00070000U       //!< 31 clocks

} I2C_GlitchFilter;

//*****************************************************************************
//
//  Values that can be passed to I2C_configureTxFIFO()for I2C FIFO configuring
//
//*****************************************************************************

typedef enum
{
    I2C_FIFO_CFG_TX_MASTER              = 0x00000000U, //!< TX Master
    I2C_FIFO_CFG_TX_SLAVE               = 0x00008000U, //!< TX slave
    I2C_FIFO_CFG_TX_MASTER_DMA          = 0x00002000U, //!< TX Master DMA
    I2C_FIFO_CFG_TX_SLAVE_DMA           = 0x0000a000U  //!< TX slave DMA

} I2C_TxFIFOCfg;

typedef enum
{
  I2C_FIFO_CFG_TX_NO_TRIG = 0x00000000U, //!< Trigger when TX FIFO empty
  I2C_FIFO_CFG_TX_TRIG_1  = 0x00000001U, //!< Trigger when TX FIFO has 1 byte
  I2C_FIFO_CFG_TX_TRIG_2  = 0x00000002U, //!< Trigger when TX FIFO has 2 byte
  I2C_FIFO_CFG_TX_TRIG_3  = 0x00000003U, //!< Trigger when TX FIFO has 3 byte
  I2C_FIFO_CFG_TX_TRIG_4  = 0x00000004U, //!< Trigger when TX FIFO has 4 byte
  I2C_FIFO_CFG_TX_TRIG_5  = 0x00000005U, //!< Trigger when TX FIFO has 5 byte
  I2C_FIFO_CFG_TX_TRIG_6  = 0x00000006U, //!< Trigger when TX FIFO has 6 byte
  I2C_FIFO_CFG_TX_TRIG_7  = 0x00000007U  //!< Trigger when TX FIFO has 7 byte

} I2C_TxTrigger;

//*****************************************************************************
//
//Values that can be passed to I2C_configureRxFIFO() for I2C FIFO configuring
//
//*****************************************************************************

typedef enum
{
    I2C_FIFO_CFG_RX_MASTER          = 0x00000000U, //!< RX Master
    I2C_FIFO_CFG_RX_SLAVE           = 0x80000000U, //!< RX slave
    I2C_FIFO_CFG_RX_MASTER_DMA      = 0x20000000U, //!< RX Master DMA
    I2C_FIFO_CFG_RX_SLAVE_DMA       = 0xa0000000U  //!< RX slave DMA

} I2C_RxFIFOCfg;

typedef enum
{
  I2C_FIFO_CFG_RX_NO_TRIG = 0x00000000U, //!< Trigger when RX FIFO empty
  I2C_FIFO_CFG_RX_TRIG_1  = 0x00010000U, //!< Trigger when RX FIFO has 1 byte
  I2C_FIFO_CFG_RX_TRIG_2  = 0x00020000U, //!< Trigger when RX FIFO has 2 byte
  I2C_FIFO_CFG_RX_TRIG_3  = 0x00030000U, //!< Trigger when RX FIFO has 3 byte
  I2C_FIFO_CFG_RX_TRIG_4  = 0x00040000U, //!< Trigger when RX FIFO has 4 byte
  I2C_FIFO_CFG_RX_TRIG_5  = 0x00050000U, //!< Trigger when RX FIFO has 5 byte
  I2C_FIFO_CFG_RX_TRIG_6  = 0x00060000U, //!< Trigger when RX FIFO has 6 byte
  I2C_FIFO_CFG_RX_TRIG_7  = 0x00070000U  //!< Trigger when RX FIFO has 7 byte

} I2C_RxTrigger;



//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an I2C base address.
//!
//! \param base is the base address of the I2C instance used.
//!
//! This function determines if a I2C module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
I2C_isBaseValid(uint32_t base)
{
    return(base == I2C0_BASE);
}
#endif

//*****************************************************************************
//
//! Enables the I2C Master block.
//!
//! \param base is the base address of the I2C module.
//!
//! This function enables operation of the I2C Master block.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableMaster(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the master block.
    //
    HWREG(base + I2C_O_MCR) |= I2C_MCR_MFE;
}

//*****************************************************************************
//
//! Enables the I2C Slave block.
//!
//! \param base is the base address of the I2C module.
//!
//! This function enables operation of the I2C Slave block.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableSlave(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the clock to the slave block.
    //
    HWREG(base + I2C_O_MCR) |= I2C_MCR_SFE;

    //
    // Enable the slave.
    //
    HWREG(base + I2C_O_SCSR_WRITE) = I2C_SCSR_WRITE_DA;
}

//*****************************************************************************
//
//! Initializes the I2C Slave block.
//!
//! \param base is the base address of the I2C module.
//! \param slaveAddr 7-bit slave address
//!
//! This function initializes operation of the I2C Slave block by configuring
//! the slave address and enabling the I2C Slave block.
//!
//! The parameter \e slaveAddr is the value that is compared against the
//! slave address sent by an I2C master.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_initSlave(uint32_t base, uint8_t slaveAddr)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));
    ASSERT((slaveAddr & I2C_SA_A6_0_MASK) == 0U);

    //
    // Must enable the device before doing anything else.
    //
    I2C_enableSlave(base);

    //
    // Set up the slave address.
    //
    HWREG(base + I2C_O_SOAR) = slaveAddr;
}

//*****************************************************************************
//
//! Disables the I2C master block.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables operation of the I2C master block.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableMaster(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the master block.
    //
    HWREG(base + I2C_O_MCR) &= ~(I2C_MCR_MFE);
}

//*****************************************************************************
//
//! Disables the I2C slave block.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables operation of the I2C slave block.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableSlave(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the slave.
    //
    HWREG(base + I2C_O_SCSR_WRITE) &= ~I2C_SCSR_WRITE_DA ;

    //
    // Disable the clock to the slave block.
    //
    HWREG(base + I2C_O_MCR) &= ~(I2C_MCR_SFE);
}

//*****************************************************************************
//
//! Enables the I2C Master interrupt.
//!
//! \param base is the base address of the I2C module.
//!
//! This function enables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableMasterInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the master interrupt.
    //
    HWREG(base + I2C_O_MIMR) |= I2C_MASTER_INT_DATA;
}

//*****************************************************************************
//
//! Enables individual I2C Master interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated I2C Master interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b I2C_MASTER_INT_RX_FIFO_FULL - RX FIFO Full interrupt
//! - \b I2C_MASTER_INT_TX_FIFO_EMPTY - TX FIFO Empty interrupt
//! - \b I2C_MASTER_INT_RX_FIFO_REQ - RX FIFO Request interrupt
//! - \b I2C_MASTER_INT_TX_FIFO_REQ - TX FIFO Request interrupt
//! - \b I2C_MASTER_INT_ARB_LOST - Arbitration Lost interrupt
//! - \b I2C_MASTER_INT_STOP - Stop Condition interrupt
//! - \b I2C_MASTER_INT_START - Start Condition interrupt
//! - \b I2C_MASTER_INT_NACK - Address/Data NACK interrupt
//! - \b I2C_MASTER_INT_TX_DMA_DONE - TX DMA Complete interrupt
//! - \b I2C_MASTER_INT_RX_DMA_DONE - RX DMA Complete interrupt
//! - \b I2C_MASTER_INT_TIMEOUT - Clock Timeout interrupt
//! - \b I2C_MASTER_INT_DATA - Data interrupt
//!
//! \note Please consult the device data sheet to determine if these
//! features are supported.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableMasterIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the master interrupt.
    //
    HWREG(base + I2C_O_MIMR) |= intFlags;
}

//*****************************************************************************
//
//! Enables the I2C Slave interrupt.
//!
//! \param base is the base address of the I2C module.
//!
//! This function enables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableSlaveInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the slave interrupt.
    //
    HWREG(base + I2C_O_SIMR) |= I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Enables individual I2C Slave interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated I2C Slave interrupt sources. Only the
//! sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b I2C_SLAVE_INT_RX_FIFO_FULL - RX FIFO Full interrupt
//! - \b I2C_SLAVE_INT_TX_FIFO_EMPTY - TX FIFO Empty interrupt
//! - \b I2C_SLAVE_INT_RX_FIFO_REQ - RX FIFO Request interrupt
//! - \b I2C_SLAVE_INT_TX_FIFO_REQ - TX FIFO Request interrupt
//! - \b I2C_SLAVE_INT_TX_DMA_DONE - TX DMA Complete interrupt
//! - \b I2C_SLAVE_INT_RX_DMA_DONE - RX DMA Complete interrupt
//! - \b I2C_SLAVE_INT_STOP - Stop condition detected interrupt
//! - \b I2C_SLAVE_INT_START - Start condition detected interrupt
//! - \b I2C_SLAVE_INT_DATA - Data interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableSlaveIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the slave interrupt.
    //
    HWREG(base + I2C_O_SIMR) |= intFlags;
}

//*****************************************************************************
//
//! Disables the I2C Master interrupt.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables the I2C Master interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableMasterInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the master interrupt.
    //
    HWREG(base + I2C_O_MIMR) &= ~I2C_MASTER_INT_DATA;
}

//*****************************************************************************
//
//! Disables individual I2C Master interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be
//!        disabled.
//!
//! This function disables the indicated I2C Master interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to I2C_enableMasterIntSource().
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableMasterIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the master interrupt.
    //
    HWREG(base + I2C_O_MIMR) &= ~intFlags;
}

//*****************************************************************************
//
//! Disables the I2C Slave interrupt.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables the I2C Slave interrupt source.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableSlaveInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the slave interrupt.
    //
    HWREG(base + I2C_O_SIMR) &= ~I2C_SLAVE_INT_DATA;
}

//*****************************************************************************
//
//! Disables individual I2C Slave interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is the bit mask of the interrupt sources to be
//!        disabled.
//!
//! This function disables the indicated I2C Slave interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt
//! disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to I2C_enableSlaveIntSource().
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableSlaveIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable the slave interrupt.
    //
    HWREG(base + I2C_O_SIMR) &= ~intFlags;
}

//*****************************************************************************
//
//! Checks if the current I2C Master has any interrupts active.
//!
//! \param base is the base address of the I2C module.
//! \param masked of type I2C_MasterIntType is I2C_MASTER_RAW_INT
//! if the raw interrupt status is requested and I2C_MASTER_MASKED_INT
//! if the masked interrupt status is requested.
//!
//! This function returns the interrupt status as active or not for the I2C.
//! Either the raw interrupt status or the status of interrupts that are
//! allowed to reflect to the processor can be returned as being active or not
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//
//*****************************************************************************
static inline bool
I2C_isMasterIntActive(uint32_t base, I2C_MasterIntType masked)
{
    bool ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(masked)
    {
        ret = ((HWREG(base + I2C_O_MMIS)) ? true : false);
    }
    else
    {
        ret = ((HWREG(base + I2C_O_MRIS)) ? true : false);
    }
    return(ret);
}

//*****************************************************************************
//
//! Gets the current I2C Master interrupt status.
//!
//! \param base is the base address of the I2C module.
//! \param masked of type I2C_MasterIntType is I2C_MASTER_RAW_INT
//! if the raw interrupt status is requested and I2C_MASTER_MASKED_INT
//! if the masked interrupt status is requested..
//!
//! This function returns the interrupt status for the I2C module.
//! Either the raw interrupt status or the status of interrupts that are
//! allowed to reflect to the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in I2C_enableMasterIntSource().
//
//*****************************************************************************
static inline uint32_t
I2C_getMasterIntStatus(uint32_t base, I2C_MasterIntType masked)
{
    uint32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(masked)
    {
        ret = HWREG(base + I2C_O_MMIS);
    }
    else
    {
        ret = HWREG(base + I2C_O_MRIS);
    }

    return(ret);
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param base is the base address of the I2C module.
//! \param masked of type I2C_MasterIntType is I2C_MASTER_RAW_INT
//! if the raw interrupt status is requested and I2C_MASTER_MASKED_INT
//! if the masked interrupt status is requested.
//!
//! This function returns the interrupt status for the I2C Slave.
//! Either the raw interrupt status or the status of interrupts that are
//! allowed to reflect to the processor can be returned.
//!
//! \return The current interrupt status, returned as \b true if active
//! or \b false if not active.
//
//*****************************************************************************
static inline bool
I2C_isSlaveIntActive(uint32_t base, I2C_MasterIntType masked)
{
    bool ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(masked)
    {
        ret = ((HWREG(base + I2C_O_SMIS)) ? true : false);
    }
    else
    {
        ret = ((HWREG(base + I2C_O_SRIS)) ? true : false);
    }

    return(ret);
}

//*****************************************************************************
//
//! Gets the current I2C Slave interrupt status.
//!
//! \param base is the base address of the I2C module.
//! \param masked of type I2C_MasterIntType is I2C_MASTER_RAW_INT
//! if the raw interrupt status is requested and I2C_MASTER_MASKED_INT
//! if the masked interrupt status is requested.
//!
//! This function returns the interrupt status for the I2C Slave.
//! Either the raw interrupt status or the status of interrupts that are
//! allowed to reflect to the processor can be returned.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! values described in I2C_enableSlaveIntSource().
//
//*****************************************************************************
static inline uint32_t
I2C_getSlaveIntStatus(uint32_t base, I2C_MasterIntType masked)
{
    uint32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(masked)
    {
        ret = HWREG(base + I2C_O_SMIS);
    }
    else
    {
        ret = HWREG(base + I2C_O_SRIS);
    }
    return(ret);
}

//*****************************************************************************
//
//! Clears I2C Master interrupt sources.
//!
//! \param base is the base address of the I2C module.
//!
//! The I2C Master interrupt source is cleared, so that it no longer
//! asserts.  This function must be called in the interrupt handler to keep the
//! interrupt from being triggered again immediately upon exit.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler(as opposed to the very last action) to astatic inline
//! void returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_clearMasterInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the I2C master interrupt source.
    //
    HWREG(base + I2C_O_MICR) = I2C_MICR_IC;

}

//*****************************************************************************
//
//! Clears I2C Master interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified I2C Master interrupt sources are cleared, so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupt from being triggered again immediately upon exit.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to I2C_enableMasterIntSource().
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler(as opposed to the very last action) to astatic inline
//! void returning from the interrupt handler before the interrupt source is
//! actually cleared. Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_clearMasterIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the I2C master interrupt source.
    //
    HWREG(base + I2C_O_MICR) = intFlags;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param base is the base address of the I2C module.
//!
//! The I2C Slave interrupt source is cleared, so that it no longer asserts.
//! This function must be called in the interrupt handler to keep the interrupt
//! from being triggered again immediately upon exit.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler(as opposed to the very last action) to astatic inline
//! void returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_clearSlaveInt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the I2C slave interrupt source.
    //
    HWREG(base + I2C_O_SICR) = I2C_SICR_DATAIC;
}

//*****************************************************************************
//
//! Clears I2C Slave interrupt sources.
//!
//! \param base is the base address of the I2C module.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! The specified I2C Slave interrupt sources are cleared, so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupt from being triggered again immediately upon exit.
//!
//! The \e intFlags parameter has the same definition as the
//! \e intFlags parameter to I2C_enableSlaveIntSource().
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler(as opposed to the very last action) to astatic inline
//! void returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_clearSlaveIntSource(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the I2C slave interrupt source.
    //
    HWREG(base + I2C_O_SICR) = intFlags;
}

//*****************************************************************************
//
//! Sets the address that the I2C Master places on the bus.
//!
//! \param base is the base address of the I2C module.
//! \param slaveAddr 7-bit slave address
//! \param bReceive flag indicating the type of communication with the slave
//!
//! This function configures the address that the I2C Master places on the
//! bus when initiating a transaction.  When the \e bReceive parameter is set
//! to \b I2C_MASTER_READ, the address indicates that the I2C Master is
//! initiating a read from the slave else set to I2C_MASTER_WRITE the
//! address indicates that the I2C Master is initiating a write to
//! the slave.This is done using I2C_MasterRW type.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_setSlaveAddress(uint32_t base, uint8_t slaveAddr,
                               I2C_MasterRW bReceive)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));
    ASSERT((slaveAddr & I2C_SA_A6_0_MASK) == 0U);

    //
    // Set the address of the slave with which the master will communicate.
    //
    HWREG(base + I2C_O_MSA) = ((slaveAddr << (uint8_t)I2C_MSA_SA_S) |
                               (uint8_t)bReceive);
}

//*****************************************************************************
//
//! Reads the state of the SDA and SCL pins.
//!
//! \param base is the base address of the I2C module.
//!
//! This function returns the state of the I2C bus by providing the real time
//! values of the SDA and SCL pins.
//!
//! \return Returns the state of the bus with SDA in bit position 1 and SCL in
//! bit position 0.
//
//*****************************************************************************
static inline uint32_t
I2C_getMasterLineState(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return the line state.
    //
    return(HWREG(base + I2C_O_MBMON));
}

//*****************************************************************************
//
//! Indicates whether or not the I2C Master is busy.
//!
//! \param base is the base address of the I2C module.
//!
//! This function returns an indication of whether or not the I2C Master is
//! busy transmitting or receiving data.
//!
//! \return Returns \b true if the I2C Master is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool
I2C_isMasterBusy(uint32_t base)
{
    bool ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return the busy status.
    //
    if((HWREG(base + I2C_O_MCS) & I2C_MCS_BUSY) == I2C_MCS_BUSY)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return(ret);
}

//*****************************************************************************
//
//! Indicates whether or not the I2C bus is busy.
//!
//! \param base is the base address of the I2C module.
//!
//! This function returns an indication of whether or not the I2C bus is busy.
//! This function can be used in a multi-master environment to determine if
//! another master is currently using the bus.
//!
//! \return Returns \b true if the I2C bus is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool
I2C_isBusBusy(uint32_t base)
{
    bool ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return the bus busy status.
    //
    if((HWREG(base + I2C_O_MCS) & I2C_MCS_BUSBSY) == I2C_MCS_BUSBSY)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return(ret);
}

//*****************************************************************************
//
//! Controls the state of the I2C Master.
//!
//! \param base is the base address of the I2C module.
//! \param cmd command to be issued to the I2C Master.
//! This is provided as a I2C_MasterControl Type .
//!
//! This function is used to control the state of the Master send and
//! receive operations.  The \e ui8Cmd parameter can be one of the following
//! values:
//!
//! - \b I2C_MASTER_CMD_SINGLE_SEND
//! - \b I2C_MASTER_CMD_SINGLE_RECEIVE
//! - \b I2C_MASTER_CMD_BURST_SEND_START
//! - \b I2C_MASTER_CMD_BURST_SEND_CONT
//! - \b I2C_MASTER_CMD_BURST_SEND_FINISH
//! - \b I2C_MASTER_CMD_BURST_SEND_ERROR_STOP
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_START
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_CONT
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_FINISH
//! - \b I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP
//! - \b I2C_MASTER_CMD_QUICK_COMMAND
//! - \b I2C_MASTER_CMD_HS_MASTER_CODE_SEND
//! - \b I2C_MASTER_CMD_FIFO_SINGLE_SEND
//! - \b I2C_MASTER_CMD_FIFO_SINGLE_RECEIVE
//! - \b I2C_MASTER_CMD_FIFO_BURST_SEND_START
//! - \b I2C_MASTER_CMD_FIFO_BURST_SEND_CONT
//! - \b I2C_MASTER_CMD_FIFO_BURST_SEND_FINISH
//! - \b I2C_MASTER_CMD_FIFO_BURST_SEND_ERROR_STOP
//! - \b I2C_MASTER_CMD_FIFO_BURST_RECEIVE_START
//! - \b I2C_MASTER_CMD_FIFO_BURST_RECEIVE_CONT
//! - \b I2C_MASTER_CMD_FIFO_BURST_RECEIVE_FINISH
//! - \b I2C_MASTER_CMD_FIFO_BURST_RECEIVE_ERROR_STOP
//!
//! \note Please consult the device data sheet to determine if this
//! feature is supported.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_setMasterConfig(uint32_t base, I2C_MasterControl cmd)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));
    ASSERT((cmd == I2C_MASTER_CMD_SINGLE_SEND) ||
           (cmd == I2C_MASTER_CMD_SINGLE_RECEIVE) ||
           (cmd == I2C_MASTER_CMD_BURST_SEND_START) ||
           (cmd == I2C_MASTER_CMD_BURST_SEND_CONT) ||
           (cmd == I2C_MASTER_CMD_BURST_SEND_FINISH) ||
           (cmd == I2C_MASTER_CMD_BURST_SEND_ERROR_STOP) ||
           (cmd == I2C_MASTER_CMD_BURST_RECEIVE_START) ||
           (cmd == I2C_MASTER_CMD_BURST_RECEIVE_CONT) ||
           (cmd == I2C_MASTER_CMD_BURST_RECEIVE_FINISH) ||
           (cmd == I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP) ||
           (cmd == I2C_MASTER_CMD_QUICK_COMMAND) ||
           (cmd == I2C_MASTER_CMD_FIFO_SINGLE_SEND) ||
           (cmd == I2C_MASTER_CMD_FIFO_SINGLE_RECEIVE) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_SEND_START) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_SEND_CONT) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_SEND_FINISH) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_SEND_ERROR_STOP) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_RECEIVE_START) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_RECEIVE_CONT) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_RECEIVE_FINISH) ||
           (cmd == I2C_MASTER_CMD_FIFO_BURST_RECEIVE_ERROR_STOP) ||
           (cmd == I2C_MASTER_CMD_HS_MASTER_CODE_SEND));

    //
    // Send the command.
    //
    HWREG(base + I2C_O_MCS_WRITE) = (uint32_t)cmd;
}
//*****************************************************************************
//
//! Transmits a byte from the I2C Master.
//!
//! \param base is the base address of the I2C module.
//! \param data data to be transmitted from the I2C Master.
//!
//! This function places the supplied data into I2C Master Data Register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_putMasterData(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Write the byte.
    //
    HWREG(base + I2C_O_MDR) = data;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Master.
//!
//! \param base is the base address of the I2C module.
//!
//! This function reads a byte of data from the I2C Master Data Register.
//!
//! \return Returns the byte received from by the I2C Master, cast as an
//! uint32_t.
//
//*****************************************************************************
static inline uint32_t
I2C_getMasterData(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Read a byte.
    //
    return(HWREG(base + I2C_O_MDR));
}

//*****************************************************************************
//
//! Sets the Master clock timeout value.
//!
//! \param base is the base address of the I2C module.
//! \param value is the number of I2C clocks before the timeout is
//!        asserted.
//!
//! This function enables and configures the clock low timeout feature in the
//! I2C peripheral.  This feature is implemented as a 12-bit counter, with the
//! upper 8-bits being programmable.  For example, to program a timeout of 20ms
//! with a 100-kHz SCL frequency, \e value is 0x7d.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_setMasterClkTimeout(uint32_t base, uint32_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Write the timeout value.
    //
    HWREG(base + I2C_O_MCLKOCNT) = value;
}

//*****************************************************************************
//
//! Configures ACK override behaviour of the I2C Slave.
//!
//! \param base is the base address of the I2C module.
//! \param enable enables or disables ACK override using the macros
//! I2C_SLAVE_ACK_OVERRIDE_ENABLE / I2C_SLAVE_ACK_OVERRIDE_DISABLE
//!
//! This function enables or disables ACK override, allowing the user
//! application to drive the value on SDA during the ACK cycle.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_configureSlaveAckOverride(uint32_t base, bool enable)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable or disable based on bEnable.
    //
    if(enable)
    {
        HWREG(base + I2C_O_SACKCTL) |= I2C_SACKCTL_ACKOEN;
    }
    else
    {
        HWREG(base + I2C_O_SACKCTL) &= ~I2C_SACKCTL_ACKOEN;
    }
}

//*****************************************************************************
//
//! Writes the ACK value.
//!
//! \param base is the base address of the I2C module.
//! \param ack chooses whether to ACK (true) or NACK (false) the transfer.
//!  using the macros I2C_SLAVE_ACK or I2C_SLAVE_NACK resp.
//!
//! This function puts the desired ACK value on SDA during the ACK cycle.  The
//! value written is only valid when ACK override is enabled using
//! I2C_configureSlaveACK().
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_setSlaveAckValue(uint32_t base, bool ack)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // ACK or NACK based on the value of bACK.
    //
    if(ack)
    {
        HWREG(base + I2C_O_SACKCTL) &= ~I2C_SACKCTL_ACKOVAL;
    }
    else
    {
        HWREG(base + I2C_O_SACKCTL) |= I2C_SACKCTL_ACKOVAL;
    }
}

//*****************************************************************************
//
//! Gets the I2C Slave status
//!
//! \param base is the base address of the I2C module.
//!
//! This function returns the action requested from a master, if any.
//! Possible values are:
//!
//! - \b I2C_SLAVE_ACT_NONE
//! - \b I2C_SLAVE_ACT_RREQ
//! - \b I2C_SLAVE_ACT_TREQ
//! - \b I2C_SLAVE_ACT_RREQ_FBR
//! - \b I2C_SLAVE_ACT_OWN2SEL
//! - \b I2C_SLAVE_ACT_QCMD
//! - \b I2C_SLAVE_ACT_QCMD_DATA
//! - \b I2C_SLAVE_DMA_TX
//! - \b I2C_SLAVE_DMA_RX
//!
//! \return Returns \b I2C_SLAVE_ACT_NONE to indicate that no action has been
//! requested of the I2C Slave, \b I2C_SLAVE_ACT_RREQ to indicate that
//! an I2C master has sent data to the I2C Slave, \b I2C_SLAVE_ACT_TREQ
//! to indicate that an I2C master has requested that the I2C Slave send
//! data, \b I2C_SLAVE_ACT_RREQ_FBR to indicate that an I2C master has sent
//! data to the I2C slave and the first byte following the slave's own address
//! has been received, \b I2C_SLAVE_ACT_OWN2SEL to indicate that the second I2C
//! slave address was matched, \b I2C_SLAVE_ACT_QCMD to indicate that a quick
//! command was received, \b I2C_SLAVE_ACT_QCMD_DATA to indicate that the
//! data bit was set when the quick command was received , \b I2C_SLAVE_DMA_TX
//! to indicate that the DMA TX is active and \b I2C_SLAVE_DMA_RX to indicate
//! that the DMA RX is active.
//
//*****************************************************************************
static inline uint32_t
I2C_getSlaveStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Return the slave status.
    //
    return(HWREG(base + I2C_O_SCSR));
}

//*****************************************************************************
//
//! Transmits a byte from the I2C Slave.
//!
//! \param base is the base address of the I2C module.
//! \param data is the data to be transmitted from the I2C Slave
//!
//! This function places the supplied data into I2C Slave Data Register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_putSlaveData(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Write the byte.
    //
    HWREG(base + I2C_O_SDR) = data;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the I2C Slave.
//!
//! \param base is the base address of the I2C module.
//!
//! This function reads a byte of data from the I2C Slave Data Register.
//!
//! \return Returns the byte received from by the I2C Slave, cast as an
//! uint32_t.
//
//*****************************************************************************
static inline uint32_t
I2C_getSlaveData(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Read a byte.
    //
    return(HWREG(base + I2C_O_SDR));
}

//*****************************************************************************
//
//! Configures the I2C transmit (TX) FIFO.
//!
//! \param base is the base address of the I2C module.
//! \param config is the configuration of the FIFO.
//! \param trigger is to select the trigger level of TX the FIFO.
//!
//! This configures the I2C peripheral's transmit FIFO.  The transmit FIFO can
//! be used by the master or slave, but not both.  The following macros are
//! used to configure the TX FIFO behaviour for master or slave, with
//! or without DMA:
//!
//! \b I2C_FIFO_CFG_TX_MASTER, \b I2C_FIFO_CFG_TX_SLAVE,
//! \b I2C_FIFO_CFG_TX_MASTER_DMA, \b I2C_FIFO_CFG_TX_SLAVE_DMA
//!
//! To select the trigger level, one of the following macros should be used:
//!
//! \b I2C_FIFO_CFG_TX_TRIG_1, \b I2C_FIFO_CFG_TX_TRIG_2,
//! \b I2C_FIFO_CFG_TX_TRIG_3, \b I2C_FIFO_CFG_TX_TRIG_4,
//! \b I2C_FIFO_CFG_TX_TRIG_5, \b I2C_FIFO_CFG_TX_TRIG_6,
//! \b I2C_FIFO_CFG_TX_TRIG_7
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_configureTxFIFO(uint32_t base, I2C_TxFIFOCfg config, I2C_TxTrigger trigger)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear transmit configuration data.
    //
    HWREG(base + I2C_O_FIFOCTL) &= ~I2C_RXFIFO_MASK;

    //
    // Store new transmit configuration data.
    //
    HWREG(base + I2C_O_FIFOCTL) |= ((uint32_t)config | (uint32_t)trigger);
}

//*****************************************************************************
//
//! Flushes the transmit (TX) FIFO.
//!
//! \param base is the base address of the I2C module.
//!
//! This function flushes the I2C transmit FIFO.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_flushTxFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Flush the TX FIFO.
    //
    HWREG(base + I2C_O_FIFOCTL) |= I2C_FIFOCTL_TXFLUSH;
}

//*****************************************************************************
//
//! Configures the I2C receive (RX) FIFO.
//!
//! \param base is the base address of the I2C module.
//! \param config is the configuration of the FIFO using specified macros.
//! \param trigger is to select the trigger level of RX the FIFO.
//!
//! This configures the I2C peripheral's receive FIFO.  The receive FIFO can be
//! used by the master or slave, but not both.  The following macros are used
//! to configure the RX FIFO behaviour for master or slave,with or without DMA:
//!
//! \b I2C_FIFO_CFG_RX_MASTER, \b I2C_FIFO_CFG_RX_SLAVE,
//! \b I2C_FIFO_CFG_RX_MASTER_DMA, \b I2C_FIFO_CFG_RX_SLAVE_DMA
//!
//! To select the trigger level, one of the following macros should be used:
//!
//! \b I2C_FIFO_CFG_RX_TRIG_1, \b I2C_FIFO_CFG_RX_TRIG_2,
//! \b I2C_FIFO_CFG_RX_TRIG_3, \b I2C_FIFO_CFG_RX_TRIG_4,
//! \b I2C_FIFO_CFG_RX_TRIG_5, \b I2C_FIFO_CFG_RX_TRIG_6,
//! \b I2C_FIFO_CFG_RX_TRIG_7
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_configureRxFIFO(uint32_t base, I2C_RxFIFOCfg config, I2C_RxTrigger trigger)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear receive configuration data.
    //
    HWREG(base + I2C_O_FIFOCTL) &= ~(I2C_RXFIFO_MASK << 16U);

    //
    // Store new receive configuration data.
    //
    HWREG(base + I2C_O_FIFOCTL) |= ((uint32_t)config | (uint32_t)trigger);
}

//*****************************************************************************
//
//! Flushes the receive (RX) FIFO.
//!
//! \param base is the base address of the I2C module.
//!
//! This function flushes the I2C receive FIFO.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_flushRxFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Flush the RX FIFO.
    //
    HWREG(base + I2C_O_FIFOCTL) |= I2C_FIFOCTL_RXFLUSH;
}

//*****************************************************************************
//
//! Gets the TX FIFO status.
//!
//! \param base is the base address of the I2C module.
//!
//! This function retrieves the status for the transmit (TX) FIFO.
//! The trigger level for the transmit FIFO is set using I2C_setTxFIFOConfig().
//!
//! \return Returns the FIFO status, enumerated as a bit field containing
//! \b I2C_FIFO_TX_BELOW_TRIG_LEVEL, \b I2C_FIFO_TX_FULL, and
//! \b I2C_FIFO_TX_EMPTY.
//
//*****************************************************************************
static inline uint32_t
I2C_getTxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Get the TX FIFO status
    //
    return(HWREGH(base + I2C_O_FIFOSTATUS) & I2C_FIFOSTATUS_TX_M);
}

//*****************************************************************************
//
//! Gets the RX FIFO status.
//!
//! \param base is the base address of the I2C module.
//!
//! This function retrieves the status for the receive (RX) FIFO.
//! The trigger level for the receive FIFO is set using I2C_setRxFIFOConfig().
//!
//! \return Returns the FIFO status, enumerated as a bit field containing
//! \b I2C_FIFO_RX_BELOW_TRIG_LEVEL, \b I2C_FIFO_RX_FULL,
//! and \b I2C_FIFO_RX_EMPTY.
//
//*****************************************************************************
static inline uint32_t
I2C_getRxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Get the RX FIFO status
    //
    return(HWREGH(base + I2C_O_FIFOSTATUS) & I2C_FIFOSTATUS_RX_M);

}

//*****************************************************************************
//
//! Writes a data byte to the I2C transmit FIFO.
//!
//! \param base is the base address of the I2C module.
//! \param data is the data to be placed into the transmit FIFO.
//!
//! This function adds a byte of data to the I2C transmit FIFO.  If there is
//! no space available in the FIFO,  this function waits for space to become
//! available before returning.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_putFIFOData(uint32_t base, uint8_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Wait until there is space.
    //
    while((HWREG(base + I2C_O_FIFOSTATUS) &
           I2C_FIFOSTATUS_TXFF) == I2C_FIFOSTATUS_TXFF)
    {
    }

    //
    // Place data into the FIFO.
    //
    HWREG(base + I2C_O_FIFODATATX) = data;
}

//*****************************************************************************
//
//! Writes a data byte to the I2C transmit FIFO.
//!
//! \param base is the base address of the I2C module.
//! \param data is the data to be placed into the transmit FIFO.
//!
//! This function adds a byte of data to the I2C transmit FIFO.  If there is
//! no space available in the FIFO, this function returns a zero.
//!
//! \return The number of elements added to the I2C transmit FIFO.
//
//*****************************************************************************
static inline uint32_t
I2C_putFIFODataNonBlocking(uint32_t base, uint8_t data)
{
    uint32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // If FIFO is full, return zero.
    //
    if((HWREG(base + I2C_O_FIFOSTATUS) &
        I2C_FIFOSTATUS_TXFF) == I2C_FIFOSTATUS_TXFF)
    {
        ret = 0U;
    }
    else
    {
        HWREG(base + I2C_O_FIFODATATX) = data;
        ret = 1U;
    }
    return(ret);
}

//*****************************************************************************
//
//! Reads a byte from the I2C receive FIFO.
//!
//! \param base is the base address of the I2C module.
//!
//! This function reads a byte of data from I2C receive FIFO and places it in
//! the location specified by the \e pdata parameter.  If there is no data
//! available, this function waits until data is received before returning.
//!
//! \return The data byte.
//
//*****************************************************************************
static inline uint32_t
I2C_getFIFOData(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Wait until there is data to read.
    //
    while((HWREG(base + I2C_O_FIFOSTATUS) &
          I2C_FIFOSTATUS_RXFE) == I2C_FIFOSTATUS_RXFE)
    {
    }

    //
    // Read a byte.
    //
    return(HWREG(base + I2C_O_FIFODATARX));
}

//*****************************************************************************
//
//! Reads a byte from the I2C receive FIFO.
//!
//! \param base is the base address of the I2C module.
//! \param dataptr is a pointer where the read data is stored.
//!
//! This function reads a byte of data from I2C receive FIFO and places it in
//! the location specified by the \e pdata parameter.  If there is no data
//! available, this functions returns 0.
//!
//! \return The number of elements read from the I2C receive FIFO.
//
//*****************************************************************************
static inline uint32_t
I2C_getFIFODataNonBlocking(uint32_t base, uint8_t *dataptr)
{
    uint32_t ret;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // If nothing in the FIFO, return zero.
    //
    if((HWREG(base + I2C_O_FIFOSTATUS) &
        I2C_FIFOSTATUS_RXFE) == I2C_FIFOSTATUS_RXFE)
    {
        ret = 0U;
    }
    else
    {
        *dataptr = HWREG(base + I2C_O_FIFODATARX);
        ret = 1U;
    }
    return(ret);
}

//*****************************************************************************
//
//! Set the burst length for a I2C master FIFO operation.
//!
//! \param base is the base address of the I2C module.
//! \param length is the length of the burst transfer.
//!
//! This function configures the burst length for a I2C Master FIFO operation.
//! The burst field is limited to 8 bits or 256 bytes.  The burst length
//! applies to a single I2CMCS BURST operation meaning that it specifies the
//! burst length for only the current operation (can be TX or RX).  Each burst
//! operation must configure the burst length prior to writing the BURST bit
//! in the I2CMCS using I2C_controlMaster().
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_setMasterBurstLength(uint32_t base, uint8_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base) && (length < 256U));

    //
    // Set the burst length.
    //
    HWREG(base + I2C_O_MBLEN) = length;
}

//*****************************************************************************
//
//! Returns the current value of the burst transfer counter.
//!
//! \param base is the base address of the I2C module.
//!
//! This function returns the current value of the burst transfer counter that
//! is used by the FIFO mechanism.  Software can use this value to determine
//! how many bytes remain in a transfer, or where in the transfer the burst
//! operation was if an error has occurred.
//!
//! \return None.
//
//*****************************************************************************
static inline uint32_t
I2C_getMasterBurstCount(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Get burst count.
    //
    return(HWREG(base + I2C_O_MBCNT));
}

//*****************************************************************************
//
//! Enables FIFO usage for the I2C Slave.
//!
//! \param base is the base address of the I2C module.
//! \param config is the desired FIFO configuration of the I2C Slave.
//!
//! This function configures the I2C Slave to use the FIFO(s).  This
//! function should be used in combination with I2C_setTxFIFOConfig() and/or
//! I2C_setRxFIFOConfig(), which configure the FIFO trigger level and tell
//! the FIFO hardware whether to interact with the I2C Master or Slave.  The
//! application appropriate combination of \b I2C_SLAVE_TX_FIFO_ENABLE and
//! \b I2C_SLAVE_RX_FIFO_ENABLE should be passed in to the \e config
//! field.
//!
//! The Slave I2CSCSR register is write-only, so any call to I2C_enableSlave(),
//! I2C_disableSlave or I2C_enableSlaveFIFO() overwrites the slave
//! configuration.Therefore, application software should call I2C_enableSlave()
//!  followed by I2C_enableSlaveFIFO() with the desired FIFO configuration.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_enableFIFO(uint32_t base, uint32_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Enable the FIFOs for the slave.
    //
    HWREG(base + I2C_O_SCSR_WRITE) = config | I2C_SCSR_WRITE_DA;
}

//*****************************************************************************
//
//! Disable FIFO usage for the I2C Slave.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables the FIFOs for the I2C Slave.  After calling this
//! this function, the FIFOs are disabled, but the Slave remains active.
//!
//! \return None.
//
//*****************************************************************************
static inline void
I2C_disableFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Disable slave FIFOs.
    //
    HWREG(base + I2C_O_SCSR_WRITE) = I2C_SCSR_WRITE_DA;
}

//*****************************************************************************
//
//! Enables internal loopback mode for an I2C port.
//!
//! \param base is the base address of the I2C module.
//!
//! This function configures an I2C port in internal loopback mode to help with
//! diagnostics and debug.  In this mode, the SDA and SCL signals from master
//! and slave modules are internally connected.  This allows data to be
//! transferred between the master and slave modules of the same I2C port,
//! without having to go through I/O's.I2C_putMasterData(),I2C_putSlaveData(),
//! I2C_getMasterData(),I2C_getSlaveData()can be used along with this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void I2C_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Write the loopback enable bit to the register.
    //
    HWREG(base + I2C_O_MCR) |= I2C_MCR_LPBK;
}

//*****************************************************************************
//
//! Disables internal loopback mode for an I2C port.
//!
//! \param base is the base address of the I2C module.
//!
//! This function disables the internal loopback mode in an I2C port
//! In this mode, the SDA and SCL signals from the master and slave
//! modules are not internally connected. Loopback mode is disabled by
//! default after reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void I2C_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear the bit that enables loopback mode.
    //
    HWREG(base + I2C_O_MCR) &= ~I2C_MCR_LPBK;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the I2C module.
//!
//! \param interruptNum specifies the interrupt in question.
//! \param pfnHandler is a pointer to the function to be called when the
//! I2C interrupt occurs.
//!
//! This function sets the handler to be called when an I2C interrupt occurs.
//! This function enables the global interrupt in the interrupt controller
//! specific I2C interrupts must be enabled via I2C_enableMasterInt() and
//! I2C_enableSlaveInt().  If necessary, it is the interrupt handler's
//! responsibility to clear the interrupt source via I2C_clearMasterInt() and
//! I2C_clearSlaveInt().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************

static inline void
I2C_registerInt(uint32_t interruptNum, void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_registerHandler(interruptNum, pfnHandler);

    //
    // Enable the I2C interrupt.
    //
    Interrupt_enable(interruptNum);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the I2C module.
//!
//! \param interruptNum specifies the interrupt in question.
//!
//! This function clears the handler to be called when an I2C interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************

static inline void
I2C_unregisterInt(uint32_t interruptNum)
{
    //
    // Disable the interrupt.
    //
    Interrupt_disable(interruptNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregisterHandler(interruptNum);
}


//*****************************************************************************
//
//! Configures the I2C Master glitch filter.
//!
//! \param base is the base address of the I2C module.
//! \param config is the glitch filter configuration provided
//! by I2C_GlitchFilter type
//!
//! This function configures the I2C Master glitch filter.  The value passed in
//! to \e config determines the sampling range of the glitch filter, which
//! is configurable between 1 and 31 system clock cycles.  The default
//! configuration of the glitch filter is 0 system clock cycles, which means
//! that it's disabled.
//!
//! The \e config field should be any of the following values:
//!
//! - \b I2C_MASTER_GLITCH_FILTER_DISABLED
//! - \b I2C_MASTER_GLITCH_FILTER_1
//! - \b I2C_MASTER_GLITCH_FILTER_2
//! - \b I2C_MASTER_GLITCH_FILTER_3
//! - \b I2C_MASTER_GLITCH_FILTER_4
//! - \b I2C_MASTER_GLITCH_FILTER_8
//! - \b I2C_MASTER_GLITCH_FILTER_16
//! - \b I2C_MASTER_GLITCH_FILTER_31
//!
//!
//! \return None.
//
//*****************************************************************************

static inline void
I2C_configureMasterGlitchFilter(uint32_t base, I2C_GlitchFilter config)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Clear glitch filter configuration
    //
    HWREG(base + I2C_O_MTPR) &= ~I2C_MTPR_PULSEL_M;

    //
    // Configure the glitch filter field of MTPR
    //
    HWREG(base + I2C_O_MTPR) |= (uint32_t)config;
}

//*****************************************************************************
//
//! Initializes the I2C Master block.
//!
//! \param base is the base address of the I2C module.
//! \param i2cClk is the rate of the clock supplied to the I2C module.
//! It should be provided as I2C_CLK_FREQ using the updated clk rate
//! \param fast set up for fast data transfers.
//!
//! This function initializes operation of the I2C Master block by configuring
//! the bus speed for the master and enabling the I2C Master block.
//!
//! If the parameter \e fast is \b true, then the master block is set up to
//! transfer data at 400 Kbps; otherwise, it is set up to transfer data at
//! 100 Kbps.  If Fast Mode Plus (1 Mbps) is desired, software should manually
//! write the I2CMTPR after calling this function.  For High Speed (3.4 Mbps)
//! mode, a specific command is used to switch to the faster clocks after the
//! initial communication with the slave is done at either 100 Kbps or
//! 400 Kbps.
//!
//! The peripheral clock is the same as the processor clock.
//!
//! \return None.
//
//*****************************************************************************

extern void
I2C_initMaster(uint32_t base, uint32_t i2cClk,
               bool fast);

//*****************************************************************************
//
//! Sets the I2C slave address.
//!
//! \param base is the base address of the I2C module.
//! \param addrNum determines which slave address is set.
//! This should be provided as I2C_SlaveAddrmode type for Primary or Secondary
//! \param slaveAddr is the 7-bit slave address
//!
//! This function writes the specified slave address.  The \e addrNum field
//! dictates which slave address is configured.  For example, a value of
//! I2C_SLAVE_ADDR_PRIMARY configures the primary address and a
//! value of I2C_SLAVE_ADDR_SECONDARY configures the secondary.
//!
//! \return None.
//
//*****************************************************************************

extern void
I2C_setOwnSlaveAddress(uint32_t base, I2C_SlaveAddrmode addrNum,
                       uint8_t slaveAddr);

//*****************************************************************************
//
//! Gets the error status of the I2C Master.
//!
//! \param base is the base address of the I2C module.
//!
//! This function is used to obtain the error status of the Master send
//! and receive operations.
//!
//! \return Returns the error status, as one of \b I2C_MASTER_ERR_NONE,
//! \b I2C_MASTER_ERR_ADDR_ACK, \b I2C_MASTER_ERR_DATA_ACK,
//! \b I2C_MASTER_ERR_ARB_LOST or \b I2C_MASTER_ERR_CLK_TOUT .
//
//*****************************************************************************

extern uint32_t
I2C_getMasterErr(uint32_t base);

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

#endif // I2C_H
