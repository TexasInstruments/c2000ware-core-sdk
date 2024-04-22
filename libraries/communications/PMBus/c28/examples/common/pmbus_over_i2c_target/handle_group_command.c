//###########################################################################
//
// FILE:   handle_group_command.c
//
// TITLE:  Group Command (Target is 2nd addressed)
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
// PMBusTarget_groupCommandTestHandler
//
//*****************************************************************************
void PMBusTarget_groupCommandTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Check that received data, transaction type, and PEC are correct
    //
    (nBytes == 3U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_MFR_VOUT_MIN) ? pass++ : fail++;
    (handle->bufferPointer[1U] == PMBUS_CMD_MFR_VOUT_MIN ^ CMD_XOR_MASK_V3) ? 
                                  pass++ : fail++;
    (handle->bufferPointer[2U] == PMBUS_CMD_MFR_VOUT_MIN ^ CMD_XOR_MASK_V4) ? 
                                  pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEWORD) ? pass++: fail++;

    /*
    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
                       nBytes - 1, buffer[3]))
    {
        pass++;
    }
    else
    {
        fail++;
    }
    */

    //
    // Change the write word handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEWORD,
                     (void (*)(void *))PMBusTarget_extendedWriteWordTestHandler);

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
