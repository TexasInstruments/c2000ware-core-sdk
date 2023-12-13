//###########################################################################
//
// FILE:   test_quick_command.c
//
// TITLE:  Quick Command Test
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
// PMBusController_initQuickCommandTest
//
//*****************************************************************************
void PMBusController_initQuickCommandTest(PMBus_TestHandle handle)
{
    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Reset test object
    //
    PMBusController_resetTestObject(handle);

    //
    // Enable the test
    //
#if ENABLE_TEST_10 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_10 == 1
}

//*****************************************************************************
//
// PMBusController_runQuickCommandTest
//
//*****************************************************************************
void PMBusController_runQuickCommandTest(PMBus_TestHandle handle)
{
    uint32_t base = I2CA_BASE;

    //
    // Do a Quick command
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    //
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);
    I2C_sendStartCondition(base);
    I2C_sendStopCondition(base);

    // Wait for I2C bus to clear
    while(I2C_getStopConditionStatus(base));
    while(I2C_isBusBusy(base));

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 1U)
    {
        handle->fail++;
    }

    return;

}

//
// End of File
//
