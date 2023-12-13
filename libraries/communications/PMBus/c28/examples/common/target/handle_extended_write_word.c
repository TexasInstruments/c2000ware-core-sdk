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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_extendedWriteWordTestHandler
//
//*****************************************************************************
void PMBusTarget_extendedWriteWordTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t preRunPass = pass;

    //
    // Check that received data and transaction type is correct
    //
    (nBytes == 5U) ? pass++ : fail++;
    (handle->bufferPointer[0U] == PMBUS_CMD_MFR_SPECIFIC_COMMAND) ? pass++ : 
                                                                    fail++;
    (handle->bufferPointer[1U] == PMBUS_CMD_VOUT_COMMAND) ? pass++ : fail++;
    (handle->bufferPointer[2U] == PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V1) ? 
                                  pass++ : fail++;
    (handle->bufferPointer[3U] == PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2) ? 
                                  pass++ : fail++;
    (transaction == PMBUS_TRANSACTION_WRITEWORD) ? pass++: fail++;

    //
    // For extended read/writes have to run CRC on
    // Addr+W, Extension, Command, Addr+R/W, Byte(s)
    // Cant run PMBus_verifyPEC, just check the PEC_VALID bit
    //
    if((status & PMBUS_PMBSTS_PEC_VALID) != 0U)
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
    if((pass - preRunPass) != 7U)
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
