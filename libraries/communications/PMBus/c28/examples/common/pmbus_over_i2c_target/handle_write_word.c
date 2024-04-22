//###########################################################################
//
// FILE:   handle_write_word.c
//
// TITLE:  Write Word
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
// PMBusTarget_writeWordTestHandler
//
//*****************************************************************************
void PMBusTarget_writeWordTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(handle);
    uint16_t CRCBufferSize = PMBusStackObject_getCRCBufferSize(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Check received data, transaction type, and PEC
    //
    (nBytes == 3U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : 
                                                                  fail++;
    (handle->bufferPointer[1U] == TEST3_DATA_BYTE_1) ? pass++ : fail++;
    (handle->bufferPointer[2U] == TEST3_DATA_BYTE_2) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEWORD) ? pass++ : fail++;

#ifdef PEC_ENABLED
    if(verifyPEC(CRCBuffer,CRCBufferSize, buffer, nBytes, buffer[3]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

#endif

    //
    // Change the write word handler for the next test
    //
    //PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEWORD,
    //                  (void (*)(void *))PMBusTarget_blockWrite2BytesTestHandler);

    //
    // Change the write word handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEWORD,
                        (void (*)(void *))PMBusTarget_extendedWriteWordTestHandler);

    //
    // Check that expected pass counter value is correct
    //
#ifdef PEC_ENABLED
    if((pass - preRunPass) != 6U)
#else
    if((pass-preRunPass != 5U))
#endif
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
