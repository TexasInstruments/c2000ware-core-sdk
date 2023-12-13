//###########################################################################
//
// FILE:   handle_block_write.c
//
// TITLE:  Block Write (255 bytes)
//
//###########################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.09.00.00 $
// $Release Date: 11-17-2023 $
// $Copyright: Copyright (C) 2015-2021 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_over_i2c_target_test.h"

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
    uint16_t *buffer = PMBusStackObject_getCurrentPositionPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t i;

    static bool firstTransaction = true;
    static uint16_t command = 0;
    static uint16_t bytecount = 0;

    uint16_t preRunPass = pass;

    if(firstTransaction)
    {
        command     = handle->bufferPointer[0U];
        bytecount   = handle->bufferPointer[1U];

        (command    == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : fail++;
        (bytecount  == DATA_BYTE_COUNT) ? pass++ : fail++;

        //
        // Update number of completed tests
        //
        testsCompleted++;

        firstTransaction = false;
    }


    (transaction == PMBUS_TRANSACTION_BLOCKWRITE) ? pass++: fail++;



    PMBusStackObject_setCurrentPositionPointer(handle, &buffer[nBytes]);





//    for(i = 0U; i < DATA_BYTE_COUNT; i++)
//    {
//        (handle->bufferPointer[i + 2U] == i) ? pass++ : fail++;
//    }

//    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table, nBytes - 1,
//                       buffer[257U]))
//    {
//        pass++;
//    }
//    else
//    {
//        fail++;
//    }
//
//    //
//    // Change the block write handler for the next test
//    //
//    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_BLOCKWRITE,
//                      (void (*)(void *))PMBusTarget_blockWrite3BytesTestHandler);

    //
    // Check that expected pass counter value is correct
    //
//    if((pass - preRunPass) != 260U)
//    {
//        fail++;
//    }


}

//
// End of File
//
