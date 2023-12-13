//###########################################################################
//
// FILE:   handle_block_write.c
//
// TITLE:  Block Write (255 bytes)
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
// PMBusTarget_blockWriteTestHandler
//
//*****************************************************************************
void PMBusTarget_blockWriteTestHandler(PMBus_StackHandle handle)
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
    // Check received data, transaction type, and PEC
    //
    (nBytes == 258U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : 
                                                                  fail++;
    (handle->bufferPointer[1U] == DATA_BYTE_COUNT) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_BLOCKWRITE) ? pass++: fail++;

    for(i = 0U; i < DATA_BYTE_COUNT; i++)
    {
        (handle->bufferPointer[i + 2U] == i) ? pass++ : fail++;
    }

    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table, nBytes - 1,
                       buffer[257U]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

    //
    // Change the block write handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_BLOCKWRITE,
                      (void (*)(void *))PMBusTarget_blockWrite3BytesTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 260U)
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
