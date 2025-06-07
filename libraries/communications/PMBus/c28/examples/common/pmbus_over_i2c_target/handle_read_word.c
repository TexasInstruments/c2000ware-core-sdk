//###########################################################################
//
// FILE:   handle_read_word.c
//
// TITLE:  Read Word
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_over_i2c_target_test.h"

//*****************************************************************************
//
// PMBusTarget_readWordTestHandler
//
//*****************************************************************************
void PMBusTarget_readWordTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t command = buffer[0];
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Set the number of bytes to send
    //
    PMBusStackObject_setNumOfBytes(handle, 2U);

    //
    // Send message to controller
    //
    buffer[0] = command ^ CMD_XOR_MASK_V1;
    buffer[1] = command ^ CMD_XOR_MASK_V2;

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_READWORD) ? pass++: fail++;

    //
    // Change the read word handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_READWORD,
                      (void (*)(void *))PMBusTarget_extendedReadWordTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 1U)
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
