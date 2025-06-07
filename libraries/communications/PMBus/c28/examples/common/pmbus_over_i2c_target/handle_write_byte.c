//###########################################################################
//
// FILE:   handle_write_byte.c
//
// TITLE:  Write Byte
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
#include "pmbus_over_i2c_target_test.h"

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
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(handle);
    uint16_t CRCBufferSize = PMBusStackObject_getCRCBufferSize(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t preRunPass = pass;

    //
    // Check data received, transaction type, and PEC
    //
    (nBytes == 2U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_VIN_OV_FAULT_LIMIT) ? pass++ : 
                                                                  fail++;
    (handle->bufferPointer[1U] == TEST2_DATA_BYTE) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEBYTE) ? pass++: fail++;

#ifdef PEC_ENABLED

    if(verifyPEC(CRCBuffer,CRCBufferSize, buffer, nBytes, buffer[2]))
    {
        pass++;
    }
    else
    {
        fail++;
    }

#endif

    // Change the write byte handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEBYTE,
                     (void (*)(void *))PMBusTarget_extendedWriteByteTestHandler);

    //
    // Check that expected pass counter value is correct
    //
#ifdef PEC_ENABLED
    if((pass - preRunPass) != 5U)
#else
    if((pass-preRunPass != 4U))
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
