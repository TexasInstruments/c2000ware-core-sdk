//###########################################################################
//
// FILE:   handle_extended_read_byte.c
//
// TITLE:  Read Byte (Extended)
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
// PMBusTarget_extendedReadByteTestHandler
//
//*****************************************************************************
void PMBusTarget_extendedReadByteTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t command = buffer[1];
    uint16_t preRunPass = pass;

    //
    // Set the number of bytes to send
    //
    PMBusStackObject_setNumOfBytes(handle, 1U);

    //
    // Send message to controller
    //
    buffer[0] = command ^ CMD_XOR_MASK_V1;

    //
    // Check transaction type
    //
    (transaction == PMBUS_TRANSACTION_READBYTE) ? pass++: fail++;

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 1U)
    {
        fail++;
    }

    //
    // Update number of completed tests
    //
    testsCompleted++;

    //
    // Change the read byte handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle, PMBUS_TRANSACTION_READBYTE,
                      (void (*)(void *))PMBusTarget_readByteTestHandler);


}

//
// End of File
//
