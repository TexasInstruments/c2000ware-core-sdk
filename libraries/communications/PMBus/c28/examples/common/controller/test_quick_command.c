//###########################################################################
//
// FILE:   test_quick_command.c
//
// TITLE:  Quick Command Test
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
#include "pmbus_controller_test.h"

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
    //
    // Increment fail, a DATA_REQUEST should set it back to 0
    //
    handle->fail++;

    //
    // Do a Quick command
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 0U, PMBUS_ENABLE_WRITE);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
        if(controllerDataRequested == true)
        {
            //
            // decrement fail if DATA_REQUEST was asserted
            //
            handle->fail--;

            //
            // Reset the data request flag
            //
            controllerDataRequested = false;

            //
            // NACK the transaction to complete the quick command
            //
            PMBus_nackTransaction(PMBUSA_BASE);
        }
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
