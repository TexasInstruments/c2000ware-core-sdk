//###########################################################################
//
// FILE:   handle_extended_write_byte.c
//
// TITLE:  Write Byte
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
#include "pmbus_over_i2c_target_test.h"

//*****************************************************************************
//
// PMBusTarget_extendedWriteByteTestHandler
//
//*****************************************************************************
void PMBusTarget_extendedWriteByteTestHandler(PMBus_StackHandle handle)
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
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t preRunPass = pass;

    //
    // Check that received data and transaction type are correct
    //
    (nBytes == 3U) ? pass++ : fail++;
    (handle->bufferPointer[0U] ==  PMBUS_CMD_MFR_SPECIFIC_COMMAND) ? pass++ : 
                                                                     fail++;
    (handle->bufferPointer[1U] ==  PMBUS_CMD_STORE_DEFAULT_CODE) ? pass++ : 
                                                                   fail++;
    (handle->bufferPointer[2U] ==  PMBUS_CMD_STORE_DEFAULT_CODE ^ 
                                   CMD_XOR_MASK_V1) ? pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEBYTE) ? pass++: fail++;

    //
    // For extended read/writes have to run CRC on
    // Addr+W, Extension, Command, Addr+R/W, Byte(s)
    // Cant run PMBus_verifyPEC, just check the PEC_VALID bit
    //
    /*
    if((status & PMBUS_PMBSTS_PEC_VALID) != 0U)
    {
        pass++;
    }
    else
    {
        fail++;
    }
    */
#ifdef PEC_ENABLED
    //nBytes is reduced by two since the command and extcommand are already included in CRCBufferSize
    if(verifyPEC(CRCBuffer,CRCBufferSize, &buffer[2], nBytes-2, buffer[3]))
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

    // Change the write byte handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_WRITEBYTE,
                     (void (*)(void *))PMBusTarget_writeByteTestHandler);

}

//
// End of File
//
