//###########################################################################
//
// FILE:   test_receive_byte.c
//
// TITLE:  Receive Byte Test
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
#include "pmbus_over_i2c_controller_test.h"
#include "pmbus_over_i2c_lib.h"

//*****************************************************************************
//
// PMBusController_initReceiveByteTest
//
//*****************************************************************************
void PMBusController_initReceiveByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_5 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_5 == 1
}

//*****************************************************************************
//
// PMBusController_runReceiveByteTest
//
//*****************************************************************************
void PMBusController_runReceiveByteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    nBytes = I2CRead(I2CA_BASE, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);

    while(I2C_getStatus(I2CA_BASE) & I2C_STS_BUS_BUSY);

    //
    // Check the received byte, data, and PEC
    //
    (nBytes == handle->count) ? handle->pass++ : handle->fail++;

    //
    // Check the received byte and data
    //
    //(bytesReceived == 1U) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == TEST5_DATA_BYTE) ? handle->pass++ : handle->fail++;

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
