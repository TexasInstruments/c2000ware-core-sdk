//###########################################################################
//
// FILE:   test_receive_byte.c
//
// TITLE:  Receive Byte Test
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

    //
    // Set count to 1
    //
    handle->count = 1;

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
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Do a receive byte
    // Configure the controller to enable PEC, enable Read
    // Expect 1 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 1U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_READ));

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }

    //
    // Get received data
    //
    PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], pmbusStatus);

    //
    // Check the received byte and data
    //
    (bytesReceived == 1U) ? handle->pass++ : handle->fail++;
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
