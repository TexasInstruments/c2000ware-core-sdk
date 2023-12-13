//###########################################################################
//
// FILE:   pmbus_stack_handler_target_block_write_process_call.c
//
// TITLE:  PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL handler
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
PMBUS_STACK_FILENUM(5)

//*****************************************************************************
//
// PMBusStack_targetBlockWriteOrProcessCallStateHandler
//
//*****************************************************************************
void PMBusStack_targetBlockWriteOrProcessCallStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getCurrentPositionPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t nBytes = 0U;


    //
    // Set the current state to block write/Process Call
    //
    PMBusStackObject_setCurrentState(handle,
                                 PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);

    if((status & PMBUS_PMBSTS_EOM) != 0U)
    {
        //
        // EOM = 1
        //
        if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
        {
            //
            // RD_BYTE_COUNT != 0, EOM = 1, DATA_READY = 1, DATA_REQUEST = 0
            // This must be the last few bytes of the block write command
            // or an extended write byte/word command
            //

            //
            // Start saving data in the buffer from the currPtr position
            // Read the data
            //
            nBytes = PMBus_getTargetData(base, buffer, status);

            //
            // Set the pointer in the buffer to point to the next
            // available spot
            //
            PMBusStackObject_setCurrentPositionPointer(handle, &buffer[nBytes]);

            //
            // Set the object's nBytes field
            //
            PMBusStackObject_setNumOfBytes(handle, (nBytes +
                                       PMBusStackObject_getNumOfBytes(handle)));

            //
            // Set the object transaction type
            //
            PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_BLOCKWRITE);

            //
            // Call the handler for the BLOCKWRITE transaction
            //
            handle->transactionHandle[PMBUS_TRANSACTION_BLOCKWRITE](handle);

            //
            // ACK the entire transaction
            //
            PMBus_ackTransaction(base);

            //
            // Set the next state to PMBUS_STACK_STATE_IDLE
            //
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
        }
        else
        {
            //
            // RD_BYTE_COUNT = 0, EOM = 1, DATA_READY = 0, DATA_REQUEST = 0
            // End-of-message, no data ready, no data requested, no bytes
            // received. This must be a write word command
            //

            //
            //ACK the entire transaction
            //
            PMBus_ackTransaction(base);

            //
            // Set the object transaction type
            //
            PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_WRITEWORD);

            //
            // Call the handler for the WRITEWORD transaction
            //
            handle->transactionHandle[PMBUS_TRANSACTION_WRITEWORD](handle);

            //
            // Set the next state to PMBUS_STACK_STATE_IDLE
            //
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
        }
    }
    else
    {
        //
        // EOM = 0
        //
        if((status & PMBUS_PMBSTS_DATA_READY) != 0U)
        {
            //
            // EOM = 0, DATA_READY = 1 RD_BYTE_COUNT = ?
            // Start saving data in the buffer from the currPtr position
            // Read the data
            //
            nBytes = PMBus_getTargetData(base, buffer, status);

            //
            // Set the pointer in the buffer to point to the next
            // available spot
            //
            PMBusStackObject_setCurrentPositionPointer(handle, &buffer[nBytes]);

            //
            // Set the object's nBytes field
            //
            PMBusStackObject_setNumOfBytes(handle, (nBytes +
                                       PMBusStackObject_getNumOfBytes(handle)));

            //
            // ACK the entire transaction
            //
            PMBus_ackTransaction(base);

            //
            // Stay in the same state, i.e.
            // PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL
            //
        }
        else if ((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
        {
            //
            // EOM = 0, DATA_READY = 0 RD_BYTE_COUNT  = 0, DATA_REQUEST = 1
            // This is a Block Write, Read, Process Call
            // Set the object transaction type
            //
            PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_BLOCKWRPC);

            //
            // Call the handler for the BLOCKWRPC transaction
            //
            (void)handle->transactionHandle[PMBUS_TRANSACTION_BLOCKWRPC](handle);

            //
            // Get the number of bytes to transfer, buffer pointer
            //
            nBytes = PMBusStackObject_getNumOfBytes(handle);

            //
            // Rewind the buffer pointer
            //
            buffer = PMBusStackObject_getBufferPointer(handle);

            if(nBytes <= 4U)
            {
                //
                // Put the data to the PMBUS Transmit buffer, with PEC
                //
                PMBus_putTargetData(base, buffer, nBytes, true);
            }
            else // nBytes > 4
            {
                //
                // Put the data to the PMBUS Transmit buffer, without PEC
                //
                PMBus_putTargetData(base, buffer, 4U, false);

                //
                // Update the current index into the buffer
                //
                PMBusStackObject_setCurrentPositionPointer(handle, &buffer[4U]);
            }
            //
            // Proceed to the READ_BLOCK state
            //
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_READ_BLOCK);
        }
        else
        {
            //
            // EOM = 0, DATA_READY = ? RD_BYTE_COUNT = ?, DATA_REQUEST = 0
            // A Fault condition
            //
            PMBUS_STACK_ASSERT(0);
        }
    }
}
#endif
//
// End of File
//
