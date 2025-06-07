//###########################################################################
//
// FILE:   handle_block_wrpc.c
//
// TITLE:  Block Write-Read Process Call (255 bytes)
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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_blockWriteReadProcessCallTestHandler
//
//*****************************************************************************
void PMBusTarget_blockWriteReadProcessCallTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t i;
    uint16_t preRunPass = pass;

    //
    // Check that target received command, byte count, 255 bytes but no PEC
    //
    (nBytes == 257U) ? pass++ : fail++;
    (buffer[0U] == PMBUS_CMD_PAGE_PLUS_READ) ? pass++ : fail++;
    (buffer[1U] == DATA_BYTE_COUNT) ? pass++ : fail++;

    for(i = 1U; i <= DATA_BYTE_COUNT; i++)
    {
        if(buffer[i + 1U] == PMBUS_CMD_PAGE_PLUS_READ ^ i)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    //
    // The Block Read portion
    // Set the number of bytes to send (inlcuding the byte count)
    //
    PMBusStackObject_setNumOfBytes(handle, (DATA_BYTE_COUNT + 1U));

    //
    // Set the byte cont as the first byte to be transmitted
    //
    buffer[0] = DATA_BYTE_COUNT;

    //
    // Send message to controller
    //
    for(i = 1U; i <= DATA_BYTE_COUNT; i++)
    {
        buffer[i] = buffer[i+1] ^ i;
    }

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_BLOCKWRPC) ? pass++: fail++;

    //
    // Change the Block Write/Read/Process Call handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_BLOCKWRPC,
                           (void (*)(void *))PMBusTarget_processCallTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 259U)
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
