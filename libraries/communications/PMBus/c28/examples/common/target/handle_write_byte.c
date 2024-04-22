//###########################################################################
//
// FILE:   handle_write_byte.c
//
// TITLE:  Write Byte
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
// PMBusTarget_writeByteTestHandler
//
//*****************************************************************************
void PMBusTarget_writeByteTestHandler(PMBus_StackHandle handle)
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
    // Check data received, transaction type, and PEC
    //
    (nBytes == 3U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : 
                                                                  fail++;
    (handle->bufferPointer[1U] == TEST2_DATA_BYTE) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEBYTE) ? pass++: fail++;

    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
                       nBytes - 1, buffer[2]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

    //
    // Change the write byte handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEBYTE,
                     (void (*)(void *))PMBusTarget_extendedWriteByteTestHandler);

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
