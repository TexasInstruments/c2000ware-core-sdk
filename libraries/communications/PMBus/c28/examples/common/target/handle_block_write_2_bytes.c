//###########################################################################
//
// FILE:    handle_block_write_2_bytes.c
//
// TITLE:   Block Write (2 bytes)
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
// PMBusTarget_blockWrite2BytesTestHandler
//
//*****************************************************************************
void PMBusTarget_blockWrite2BytesTestHandler(PMBus_StackHandle handle)
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
    (nBytes == 4U) ? pass++ : fail++;
    (handle->bufferPointer[0U] ==  PMBUS_CMD_PAGE_PLUS_WRITE) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEWORD) ? pass++: fail++;

    for(i = 1U; i <= 2U; i++)
    {
        if(handle->bufferPointer[i] == (PMBUS_CMD_PAGE_PLUS_WRITE ^ i))
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
                       nBytes - 1, buffer[3U]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

    //
    // Change the write word handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEWORD,
                          (void (*)(void *))PMBusTarget_groupCommandTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 6U)
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
