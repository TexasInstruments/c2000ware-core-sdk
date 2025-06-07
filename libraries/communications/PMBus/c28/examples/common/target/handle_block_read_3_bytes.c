//###########################################################################
//
// FILE:   handle_block_read_3_bytes.c
//
// TITLE:  Block Read (3 bytes)
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
// PMBusTarget_blockRead3BytesTestHandler
//
//*****************************************************************************
void PMBusTarget_blockRead3BytesTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t command = buffer[0];
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t i;
    uint16_t preRunPass = pass;

    //
    // Set the number of bytes to send (including the byte count)
    //
    PMBusStackObject_setNumOfBytes(handle, 4U);

    //
    // Set the byte cont as the first byte to be transmitted
    //
    buffer[0] = 3U;

    //
    // Send message to controller
    //
    for(i = 1U; i <= 3U; i++)
    {
        buffer[i] = command ^ i;
    }

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_BLOCKREAD) ? pass++: fail++;

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
