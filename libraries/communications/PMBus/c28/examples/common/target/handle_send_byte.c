//###########################################################################
//
// FILE:   handle_send_byte.c
//
// TITLE:  Send Byte
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
// PMBusTarget_sendByteTestHandler
//
//*****************************************************************************
void PMBusTarget_sendByteTestHandler(PMBus_StackHandle handle)
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
    // Check received data, transaction type, and PEC
    //
    (nBytes == 2U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == TEST1_DATA_BYTE) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_SENDBYTE) ? pass++: fail++;

    if(PMBus_verifyPEC(base, buffer, (uint16_t *)PMBus_crc8Table,
                       nBytes - 1, buffer[1]))
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
    if((pass - preRunPass) != 4U)
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
