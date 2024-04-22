//###########################################################################
//
// FILE:   handle_send_byte.c
//
// TITLE:  Send Byte
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
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(handle);
    uint16_t CRCBufferSize = PMBusStackObject_getCRCBufferSize(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Check received data, transaction type, and PEC
    //
    (nBytes == 1U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == TEST1_DATA_BYTE) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_SENDBYTE) ? pass++: fail++;

#ifdef PEC_ENABLED

    if(verifyPEC(CRCBuffer,CRCBufferSize, buffer, nBytes, buffer[1]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

#endif
    //
    // Check that expected pass counter value is correct
    //
#ifdef PEC_ENABLED
    if((pass - preRunPass) != 4U)
#else
    if((pass-preRunPass != 3U))
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
