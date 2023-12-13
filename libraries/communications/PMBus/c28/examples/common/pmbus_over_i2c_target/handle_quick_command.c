//###########################################################################
//
// FILE:   handle_quick_command.c
//
// TITLE:  Quick Command
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
#include "pmbus_over_i2c_target_test.h"

//*****************************************************************************
//
// PMBusTarget_quickCommandTestHandler
//
//*****************************************************************************
void PMBusTarget_quickCommandTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t address = PMBusStackObject_getTargetAddress(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Check number of bytes, target address, access type, and transaction type
    //
    (nBytes == 0U) ? pass++ : fail++;
    (address == TARGET_ADDRESS) ? pass++ : fail++;

    (transaction == PMBUS_TRANSACTION_QUICKCOMMAND) ? pass++ : fail++;

    //
    // Change the quick command handler for the next test
    //
    //PMBusStackObject_setTransactionHandler(handle,
    //                                       PMBUS_TRANSACTION_QUICKCOMMAND,
    //                             (void (*)(void *))PMBusTarget_alertTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 3U)
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
