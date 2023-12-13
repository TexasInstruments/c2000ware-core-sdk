//#############################################################################
//
// FILE:   handle_process_call.c
//
// TITLE:  Process Call (write word then read word)
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_processCallTestHandler
//
//*****************************************************************************
void PMBusTarget_processCallTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t command;
    uint16_t preRunPass = pass;

    //
    // Check that target received command, 2 bytes but no PEC
    //
    (nBytes == 3U) ? pass++ : fail++;
    (buffer[0U] == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : fail++;
    (buffer[1U] == TEST14_DATA_BYTE_1) ? pass++ : fail++;
    (buffer[2U] == TEST14_DATA_BYTE_2) ? pass++ : fail++;

    //
    // Save command
    //
    command = buffer[0U];

    //
    // Set the number of bytes to send and send message to controller
    //
    PMBusStackObject_setNumOfBytes(handle, 2U);
    buffer[0U] =  buffer[1U] ^ command;
    buffer[1U] =  buffer[2U] ^ command;

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_BLOCKWRPC) ? pass++: fail++;

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 5U)
    {
        fail++;
    }

    //
    // Update number of completed tests
    //
    testsCompleted++;
}

//
// End of File
//
