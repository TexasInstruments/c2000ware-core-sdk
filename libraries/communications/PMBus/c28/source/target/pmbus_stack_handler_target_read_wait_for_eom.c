//###########################################################################
//
// FILE:   pmbus_stack_handler_target_read_wait_for_eom.c
//
// TITLE:  PMBUS_STACK_STATE_READ_WAIT_FOR_EOM handler
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
PMBUS_STACK_FILENUM(6)

//*****************************************************************************
//
// PMBusStack_targetReadWaitForEOMStateHandler
//
//*****************************************************************************
void PMBusStack_targetReadWaitForEOMStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t nBytes = 0U;
    uint16_t command = buffer[0U];

#ifndef PMBUS_OVER_I2C
    //
    // Set the current state to Read/Wait for EOM
    //
    PMBusStackObject_setCurrentState(handle,
                                     PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);

    if(((status & PMBUS_PMBSTS_EOM) != 0U) &&
       ((status & PMBUS_PMBSTS_NACK) != 0U))
    {
        //
        // EOM = 1, NACK = 1
        // NOTE: ACK is required to allow the target to ack its address in
        // any subsequent transaction.
        //
        PMBus_ackTransaction(base);

        //
        // Read byte/word/block was successful, return to the
        // Idle state
        //
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
    }
    //
    // At this point the command is already in the buffer
    //
    else if(PMBusStackObject_isCommandAndTransactionValid(command,
                                                    PMBUS_TRANSACTION_READBYTE))
    {
        //
        // Set the object transaction type
        //
        PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_READBYTE);

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
        PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_READWORD);

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
    else if(PMBusStackObject_isCommandAndTransactionValid(command,
                                                   PMBUS_TRANSACTION_BLOCKREAD))
    {
        //
        // Set the object transaction type
        //
        PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_BLOCKREAD);

        //
        // Call the handler for the READBLOCK transaction
        //
        (void)handle->transactionHandle[PMBUS_TRANSACTION_BLOCKREAD](handle);

        //
        // Get the number of bytes to transfer, buffer pointer
        //
        nBytes = PMBusStackObject_getNumOfBytes(handle);

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
        // Unhandled exception
        //
        PMBUS_STACK_ASSERT(0);
    }
#endif

}
#endif
//
// End of File
//
