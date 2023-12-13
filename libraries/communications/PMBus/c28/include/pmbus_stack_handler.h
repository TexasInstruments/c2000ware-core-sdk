//###########################################################################
//
// FILE:   pmbus_stack_Handler.h
//
// TITLE:  PMBUS Communications State Machine
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################

#ifndef PMBUS_STACK_HANDLER_H
#define PMBUS_STACK_HANDLER_H

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
//!
//! \defgroup PMBUS_STACK_HANDLER PMBus State Machine Handler
//
//!
//! \ingroup PMBUS_STACK_HANDLER
// @{
//
//*****************************************************************************

//
// Includes
//
#include "pmbus_stack_assert.h"
#ifndef PMBUS_OVER_I2C
#include "pmbus_stack_config.h"
#else
#include "pmbus_over_i2c_stack_config.h"


#define TARGET_RECEIVER      (I2C_getStatus(base) & I2C_STS_TARGET_DIR) == 0
#define TARGET_TRANSMITTER   (I2C_getStatus(base) & I2C_STS_TARGET_DIR) == I2C_STS_TARGET_DIR

#define STOP_CONDITION_DETECTED     (I2C_getStatus(base) & I2C_STS_STOP_CONDITION) == I2C_STS_STOP_CONDITION

#define STOP_CONDITION_NOT_DETECTED (I2C_getStatus(base) & I2C_STS_STOP_CONDITION) == 0

#define WAIT_TILL_TX_FIFO_IS_EMPTY     I2C_getTxFIFOStatus(base)

#define WAIT_TILL_RX_FIFO_IS_FULL    !(I2C_getRxFIFOStatus(base) == I2C_FIFO_RXFULL)

#define WAIT_TILL_RX_FIFO_HAS(x)     !(I2C_getRxFIFOStatus(base) == x)

#endif

#ifdef TIMEOUT
#include "driverlib.h"
#endif

//*****************************************************************************
//
//! PMBus Target Stack State Machine Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function implements the state machine of the PMBus in target mode.
//! This handler is designed to operate within the PMBus interrupt service
//! routine (ISR) triggered by the following interrupts:
//! - Data Ready (Read buffer is full)
//! - Data Request (Controller has requested data) / SDIR bit in I2C
//! - EOM (Controller signals an end of a block message)
//!
//! \note The handler must be called in the PMBus ISR only
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Idle State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the idle state in the target state machine.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetIdleStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Receive Byte Wait-for-EOM State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the state in the target state machine that is entered
//! when a receive byte request is active and target is waiting for
//! end-of-message.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetReceiveByteWaitForEOMStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Read Block State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the state in the target state machine that is entered
//! when a read block command is used.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetReadBlockStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Read/Wait for EOM State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the state in the target state machine that is entered
//! when reading/waiting for the end-of-message.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetReadWaitForEOMStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Block Write or Process Call State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the state in the target state machine that is entered
//! when a block write or process call commands are used.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetBlockWriteOrProcessCallStateHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! PMBus Target Extended Read/Write Byte/Word State Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function handles the state in the target state machine that is entered
//! when extended commands are used. These include extended read byte,
//! read word, write byte, and write word transactions.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBusStack_targetExtendedCommandStateHandler(PMBus_StackHandle handle);

extern void
PMBusStack_targetRxFIFOHandler(PMBus_StackHandle handle);

extern void
PMBusStack_targetTimeoutHandler(PMBus_StackHandle handle);
//*****************************************************************************
//
// Close the Doxygen group.
// @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif // extern "C"

#endif // PMBUS_STACK_HANDLER_H
