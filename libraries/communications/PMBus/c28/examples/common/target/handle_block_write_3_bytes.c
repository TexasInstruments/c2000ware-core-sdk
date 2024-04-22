//###########################################################################
//
// FILE:   handle_block_write_3_bytes.c
//
// TITLE:  Block Write (3 bytes)
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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_blockWrite3BytesTestHandler
//
//*****************************************************************************
void PMBusTarget_blockWrite3BytesTestHandler(PMBus_StackHandle handle)
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
    // Check command, byte count, bytes #0, 1, 2 and PEC
    //
    (nBytes == 6U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_PAGE_PLUS_WRITE) ? pass++ : fail++;
    (handle->bufferPointer[1U] == 3U) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_BLOCKWRITE) ? pass++: fail++;

    for(i = 1U; i <= 3U; i++)
    {
        if(handle->bufferPointer[i + 1U] == (PMBUS_CMD_PAGE_PLUS_WRITE ^ i))
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
                       nBytes - 1, buffer[5U]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 8U)
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
