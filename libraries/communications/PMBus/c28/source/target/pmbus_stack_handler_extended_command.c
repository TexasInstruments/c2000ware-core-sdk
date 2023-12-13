//###########################################################################
//
// FILE:   pmbus_stack_handler_extended_command.c
//
// TITLE: PMBUS_STACK_STATE_EXTENDED_COMMAND handler
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
PMBUS_STACK_FILENUM(8)

//*****************************************************************************
//
// PMBusStack_targetExtendedCommandStateHandler
//
//*****************************************************************************
void PMBusStack_targetExtendedCommandStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t command = buffer[1U];
    uint16_t nBytes = 0U;


    //
    // Set the current state to PMBUS_STACK_STATE_EXTENDED_COMMAND
    //
    PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_EXTENDED_COMMAND);

    if((status & PMBUS_PMBSTS_DATA_REQUEST) != 0U)
    {
        //
        // DATA_REQUEST = 1 (an extended read)
        //
        if(PMBusStackObject_isCommandAndTransactionValid(command,
           PMBUS_TRANSACTION_READBYTE))
        {
            //
            // Set the object transaction type
            //
            PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_READBYTE);

            //
            // Call the handler for the READBYTE transaction
            //
            (void)handle->transactionHandle[PMBUS_TRANSACTION_READBYTE](handle);

            //
            // Get the number of bytes to transfer, buffer pointer
            //
            nBytes = PMBusStackObject_getNumOfBytes(handle);

            //
            // Put the data to the PMBUS Transmit buffer, with PEC
            //
            PMBus_putTargetData(base, buffer, nBytes, true);
        }
        else if(PMBusStackObject_isCommandAndTransactionValid(command,
                 PMBUS_TRANSACTION_READWORD))
        {
            //
            // Set the object transaction type
            //
            PMBusStackObject_setTransactionType(handle,
                                                PMBUS_TRANSACTION_READWORD);

            //
            // Call the handler for the READWORD transaction
            //
            (void)handle->transactionHandle[PMBUS_TRANSACTION_READWORD](handle);

            //
            // Get the number of bytes to transfer, buffer pointer
            //
            nBytes = PMBusStackObject_getNumOfBytes(handle);

            //
            // Put the data to the PMBUS Transmit buffer, with PEC
            //
            PMBus_putTargetData(base, buffer, nBytes, true);
        }
        else
        {
            //
            // Unhandled exception
            //
            PMBUS_STACK_ASSERT(0);
        }
    }
    else if((status & PMBUS_PMBSTS_EOM) != 0U)
    {
        //
        // EOM = 1, DATA_REQUEST = 0
        //
        if(((status & PMBUS_PMBSTS_NACK) != 0U) &&
           ((status & PMBUS_PMBSTS_DATA_READY) == 0U))
        {
            //
            // EOM = 1, NACK = 1, DATA_REQUEST = 0, DATA_READY = 0
            // Controller NACKs the extended read, ack and
            // change state to IDLE
            //
            PMBus_ackTransaction(base);
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
        }
        else if(((status & PMBUS_PMBSTS_NACK) == 0U) &&
                ((status & PMBUS_PMBSTS_DATA_READY) != 0U))
        {
            //
            // EOM = 1, DATA_READY = 1, NACK = 0, DATA_REQUEST = 0
            // Controller completes either an ext write byte/word
            //

             //
            // Set buffer pointer to the current pointer
            //
            buffer = PMBusStackObject_getCurrentPositionPointer(handle);

            if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 2U)
            {
                //
                // RD_BYTE_COUNT = 2, EOM = 1, DATA_READY = 1
                // extended write Byte (Receive buffer has Byte & PEC)
                //

                //
                // Read the data
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Set the object's nBytes field
                // Set the pointer in the buffer to point to the next
                // available spot
                //
                PMBusStackObject_setCurrentPositionPointer(handle,
                                                           &buffer[nBytes]);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, (nBytes +
                                       PMBusStackObject_getNumOfBytes(handle)));

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
            else if(((status & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                     PMBUS_PMBSTS_RD_BYTE_COUNT_S) == 3U)
            {
                //
                // RD_BYTE_COUNT = 3, EOM = 1, DATA_READY = 1
                // Write word (Receive buffer has Byte #1, Byte #2, PEC)
                //

                //
                // Read the data
                //
                nBytes = PMBus_getTargetData(base, buffer, status);

                //
                // Set the object's nBytes field
                // Set the pointer in the buffer to point to the next
                // available spot
                //
                PMBusStackObject_setCurrentPositionPointer(handle,
                                                           &buffer[nBytes]);

                //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, (nBytes +
                                       PMBusStackObject_getNumOfBytes(handle)));

                //
                // Set the object transaction type
                //
                PMBusStackObject_setTransactionType(handle,
                                                   PMBUS_TRANSACTION_WRITEWORD);

                //
                // Call the handler for the WRITEWORD transaction
                //
                (void)handle->
                transactionHandle[PMBUS_TRANSACTION_WRITEWORD](handle);

                //
                // ACK the entire transaction
                //
                PMBus_ackTransaction(base);
            }
            else
            {
                //
                // Unhandled exception
                //
                PMBUS_STACK_ASSERT(0);
            }

            //
            // Set next state to IDLE
            //
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
        }
        else
        {
            //
            // Unhandled exception
            //
            PMBUS_STACK_ASSERT(0);
        }
    }
    else
    {
        //
        // EOM = 0, DATA_REQUEST = 0, DATA_READY = X, NACK = X
        // Unhandled exception
        //
        PMBUS_STACK_ASSERT(0);
    }

}
#endif
//
// End of File
//
