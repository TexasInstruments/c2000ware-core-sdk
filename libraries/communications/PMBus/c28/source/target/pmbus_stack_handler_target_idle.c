//###########################################################################
//
// FILE:   pmbus_stack_handler_target_idle.c
//
// TITLE:  PMBUS_STACK_STATE_IDLE handler
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

#ifndef PMBUS_OVER_I2C
//
// Includes
//
#include "pmbus_stack_handler.h"

//
// Defines
//
PMBUS_STACK_FILENUM(3)

//*****************************************************************************
//
// PMBusStack_targetIdleStateHandler
//
//*****************************************************************************
void PMBusStack_targetIdleStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t nBytes = 0U;
    uint16_t *currentPointer;

    //
    // Set the current state to idle
    //
    PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);

    //
    // Rewind the current pointer
    //
    PMBusStackObject_setCurrentPositionPointer(handle, buffer);

    //
    // Set the object transaction type
    //
    PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_NONE);

    //
    // Check if the unit is busy
    //
    if((status & PMBUS_PMBSTS_UNIT_BUSY) == 0U)
    {
        //
        // Neither PMBUS hardware nor firmware are stuck,
        //
        // The user must use the clock low timeout feature to
        // fire an interrupt off to the CPU, query the comms
        // stack object, take remedial measures and reset
        // the state machine prior to returning from the interrupt
        //
    }

    if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
    {
        if((status & PMBUS_PMBSTS_EOM) != 0U)
        {
            //
            // EOM = 1, DATA_READY = 1
            //
            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
                //
                // RD_BYTE_COUNT = 2, EOM = 1, DATA_READY = 1
                // Send Byte (Receive buffer has Byte #0, PEC)
                //

                //
                // Read the data
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, nBytes);

                //
                // Set the object transaction type
                //
                PMBusStackObject_setTransactionType(handle,
                                                    PMBUS_TRANSACTION_SENDBYTE);

                //
                // Call the handler for the SENDBYTE transaction
                //
                (void)handle->
                transactionHandle[PMBUS_TRANSACTION_SENDBYTE](handle);

                //
                // ACK the entire transaction
                //
                PMBus_ackTransaction(base);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                     PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 3U)
            {
                //
                // RD_BYTE_COUNT = 3, EOM = 1, DATA_READY = 1
                // Write Byte (Receive buffer has Command, Byte #0, PEC)
                //

                //
                // Read the data
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, nBytes);

                //
                // Set the object transaction type
                //
                PMBusStackObject_setTransactionType(handle,
                                                    PMBUS_TRANSACTION_WRITEBYTE);

                //
                // Call the handler for the WRITEBYTE transaction
                //
                (void)handle->
                transactionHandle[PMBUS_TRANSACTION_WRITEBYTE](handle);

                //
                // ACK the entire transaction
                //
                PMBus_ackTransaction(base);
            }
            else
            {
                //
                // RD_BYTE_COUNT = 1, EOM = 1, DATA_READY = 1
                // Unhandled exception
                //
                PMBUS_STACK_ASSERT(0);
            }
        }
        else
        {
            //
            // EOM = 0, DATA_READY = 1
            //
            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                PMBUS_PMBSTS_RD_BYTE_COUNT_S) >= 3U)
            {
                //
                // RD_BYTE_COUNT = 3/4, EOM = 0, DATA_READY = 1
                // Read buffer is full, this must either be a write word,
                // block write or process call
                //
                // Read the RXBUF, ack the transaction and then proceed
                // to the BLOCK_WRITE_OR_PROCESS_CALL state
                //
                // Read the data
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Set the pointer in the buffer to point to the next
                // available spot
                //
                currentPointer = PMBusStackObject_getCurrentPositionPointer(handle);
                PMBusStackObject_setCurrentPositionPointer(handle,
                                                           &currentPointer[nBytes]);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, nBytes);

                //
                // ACK the entire transaction
                //
                PMBus_ackTransaction(base);

                //
                // Set the next state to
                // PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL
                //
                PMBusStackObject_setNextState(handle,
                                 PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                     PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
                //
                // RD_BYTE_COUNT = 2, EOM = 0, DATA_READY = 1
                // This must be either an extended
                // - Read Byte
                // - Read Word
                // - Write Byte
                // - Write Word
                //

                //
                // Read the command
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Check the first byte for the extended command byte
                //
                PMBUS_STACK_ASSERT((buffer[0] ==
                                    PMBUS_CMD_MFR_SPECIFIC_COMMAND) ||
                                   (buffer[0] == PMBUS_CMD_PMBUS_COMMAND_EXT));

                //
                // Set the pointer in the buffer to point to the next
                // available spot
                //
                PMBusStackObject_setCurrentPositionPointer(handle,
                                                           &buffer[nBytes]);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, nBytes);

                //
                // ACK the command for the target to be able to proceed
                //
                PMBus_ackTransaction(base);

                //
                // Transition to the state PMBUS_STACK_STATE_EXTENDED_COMMAND
                //
                PMBusStackObject_setNextState(handle,
                                            PMBUS_STACK_STATE_EXTENDED_COMMAND);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                     PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 1U)
            {
                //
                // RD_BYTE_COUNT = 1, EOM = 0, DATA_READY = 1
                // This could be either a
                // - Read Byte
                // - Read Word
                // - Block Read
                // The command determines which read transaction is being
                // requested by the controller. We need to wait for DATA_REQUEST
                // to come in
                //

                //
                // Read the command
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // ACK the command, for the controller to be able to issue
                // the repeated start, and therby the DATA_REQUEST interrupt
                //
                PMBus_ackTransaction(base);

                //
                // Transition to the state PMBUS_STATE_READ_WAIT_FOR_EOM
                //
                PMBusStackObject_setNextState(handle,
                                           PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);
            }
            else
            {
                //
                // Unhandled exception
                //
                PMBUS_STACK_ASSERT(0);
            }
        }
    }
    else
    {
        //
        // DATA_READY = 0
        //
        if((status & PMBUS_PMBSTS_EOM) == 0U)
        {
            //
            // DATA_READY = 0, EOM = 0
            //
            if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
            {
                //
                // DATA_READY = 0, EOM = 0, DATA_REQUEST = 1
                // This is a receive byte request
                // Set the object transaction type
                //
                PMBusStackObject_setTransactionType(handle,
                                                 PMBUS_TRANSACTION_RECEIVEBYTE);

                //
                // Call the handler for the RECEIVEBYTE transaction
                //
                (void)handle->
                transactionHandle[PMBUS_TRANSACTION_RECEIVEBYTE](handle);

                //
                // Get the number of bytes to transfer, buffer pointer
                //
                nBytes = PMBusStackObject_getNumOfBytes(handle);

                //
                // Put the data to the PMBUS Transmit buffer, with PEC
                //
                PMBus_putTargetData(base, buffer, nBytes, true);

                //
                // Transition to the RECEIVE_BYTE_WAIT_FOR_EOM
                //
                PMBusStackObject_setNextState(handle,
                                   PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);
            }
            else
            {
                //
                // DATA_READY = 0, EOM = 0, DATA_REQUEST = 0
                // Unhandled Exception
                //
                PMBUS_STACK_ASSERT(0);
            }
        }
        else
        {
            //
            // DATA_READY = 0 EOM = 1
            //
            if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
            {
                //
                // DATA_READY = 0, EOM = 1, DATA_REQUEST = 1
                // Unhandled Exception
                //
                PMBUS_STACK_ASSERT(0);

            }
            else if (((status & PMBUS_PMBSTS_NACK) != 0U) &&
                     ((status & PMBUS_PMBSTS_ALERT_EDGE) != 0U))
            {
                //
                // DATA_READY = 0, EOM = 1, NACK = 1, ALERT_EDGE = 1
                // This is an alert response
                // ACK the transaction
                //
                PMBus_ackTransaction(base);
            }
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                       PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 0U)
            {
                //
                // RD_BYTE_COUNT = 0, EOM = 1, DATA_READY = 0, NACK = 0
                // Quick Command
                //

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, 0U);

                //
                // Set the object transaction type
                //
                PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_QUICKCOMMAND);

                //
                // Call the handler for the QUCIKCOMMAND transaction
                //
                (void)handle->
                transactionHandle[PMBUS_TRANSACTION_QUICKCOMMAND](handle);

                //
                // ACK the entire transaction
                //
                PMBus_ackTransaction(base);
            }
            else
            {
                //
                // DATA_READY = 0, EOM = 1, DATA_REQUEST = 0,
                // RD_BYTE_COUNT != 0
                // Unhandled Exception
                //
                PMBUS_STACK_ASSERT(0);
            }
        }
    }
}
#endif
//
// End of File
//
