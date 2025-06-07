//###########################################################################
//
// FILE:   test_read_byte.c
//
// TITLE:  Read Byte Test
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
#include "pmbus_over_i2c_controller_test.h"
#include "pmbus_over_i2c_lib.h"

//*****************************************************************************
//
// PMBusController_initReadByteTest
//
//*****************************************************************************
void PMBusController_initReadByteTest(PMBus_TestHandle handle)
{
    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Reset test object
    //
    PMBusController_resetTestObject(handle);

#ifdef PEC_ENABLED
    //
    // Set count to 1 byte + 1 PEC byte
    //
    handle->count = 2;
#else
    //
    // Set count to 1 byte
    //
    handle->count = 1;
#endif


    //
    // Enable the test
    //
#if ENABLE_TEST_6 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_6 == 1
}

//*****************************************************************************
//
// PMBusController_runReadByteTest
//
//*****************************************************************************
void PMBusController_runReadByteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 0U;

    bytesReceived = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

     //
    //Load the command byte into the transmit register,
    // in this case the PMBUS_CMD_OPERATION command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_OPERATION;

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, 1, false);

    //
    // Read received data
    //
    nBytes = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);

    while(I2C_isBusBusy(base));

    //
    // Check the received byte, data, and PEC
    //
    (nBytes == handle->count) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == (PMBUS_CMD_OPERATION ^ CMD_XOR_MASK_V1)) ?
                             handle->pass++ : handle->fail++;
    //(receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 2U)
    {
        handle->fail++;
    }

    return;
}


//
// End of File
//
