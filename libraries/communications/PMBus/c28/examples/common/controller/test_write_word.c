//###########################################################################
//
// FILE:   test_write_word.c
//
// TITLE:  Write Word Test
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_controller_test.h"

//*****************************************************************************
//
// PMBusController_initWriteWordTest
//
//*****************************************************************************
void PMBusController_initWriteWordTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_3 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_3 == 1
}

//*****************************************************************************
//
// PMBusController_runWriteWordTest
//
//*****************************************************************************
void PMBusController_runWriteWordTest(PMBus_TestHandle handle)
{
    //
    // Add command (index 0)  and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    pmbusControllerBuffer[1] = TEST3_DATA_BYTE_1;
    pmbusControllerBuffer[2] = TEST3_DATA_BYTE_2;

    //
    // Do a write word
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 2U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 3U);

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
