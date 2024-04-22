//###########################################################################
//
// FILE:   handle_extended_read_word.c
//
// TITLE:  Read Word (Extended)
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_over_i2c_target_test.h"

//*****************************************************************************
//
// PMBusTarget_extendedReadWordTestHandler
//
//*****************************************************************************
void PMBusTarget_extendedReadWordTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t command = buffer[1];
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Set the number of bytes to send
    //
    PMBusStackObject_setNumOfBytes(handle, 2U);

    //
    // Send message to controller
    //
    buffer[0] = buffer[0] ^ CMD_XOR_MASK_V1;
    buffer[1] = buffer[1] ^ CMD_XOR_MASK_V2;

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_READWORD) ? pass++: fail++;

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

    //
    // Change the read word handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_READWORD,
                      (void (*)(void *))PMBusTarget_readWordTestHandler);

}

//
// End of File
//
