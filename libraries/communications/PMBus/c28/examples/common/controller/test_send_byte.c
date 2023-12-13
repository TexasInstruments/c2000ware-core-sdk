//###########################################################################
//
// FILE:   test_send_byte.c
//
// TITLE:  Send Byte Test
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
#include "pmbus_controller_test.h"

//*****************************************************************************
//
// PMBusController_initSendByteTest
//
//*****************************************************************************
void PMBusController_initSendByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_1 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_1 == 1
}

//*****************************************************************************
//
// PMBusController_runSendByteTest
//
//*****************************************************************************
void PMBusController_runSendByteTest(PMBus_TestHandle handle)
{
    //
    // Place data in buffer
    //
    pmbusControllerBuffer[0] = TEST1_DATA_BYTE;

    //
    // Do a send byte
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), 1 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 1U, PMBUS_CONTROLLER_ENABLE_PEC);

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 1U);

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
