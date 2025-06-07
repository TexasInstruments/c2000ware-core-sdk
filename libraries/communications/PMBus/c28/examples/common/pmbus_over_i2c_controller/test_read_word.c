//###########################################################################
//
// FILE:   test_read_word.c
//
// TITLE:  Read Word Test
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
// PMBusController_initReadWordTest
//
//*****************************************************************************
void PMBusController_initReadWordTest(PMBus_TestHandle handle)
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
    // Set count to 2 byte + 1 PEC byte
    //
    handle->count = 3;
#else
    //
    // Set count to 2 byte
    //
    handle->count = 2;
#endif

    //
    // Enable the test
    //
#if ENABLE_TEST_7 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_7 == 1
}

//*****************************************************************************
//
// PMBusController_runReadWordTest
//
//*****************************************************************************
void PMBusController_runReadWordTest(PMBus_TestHandle handle)
{
    //locals
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Load the command byte into the transmit register,
    // in this case the PMBUS_CMD_VOUT_COMMAND command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VOUT_COMMAND;

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, 1, false);

    nBytes = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);

    while(I2C_isBusBusy(base));


     //
    // Check the received byte, data, and PEC
    //
    (nBytes == handle->count) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == (PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V1)) ?
                             handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[1] == (PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2)) ?
                             handle->pass++ : handle->fail++;
//    (receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 3U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
