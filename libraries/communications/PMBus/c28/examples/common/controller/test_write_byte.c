//###########################################################################
//
// FILE:   test_write_byte.c
//
// TITLE:  Write Byte Test
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
// PMBusController_initWriteByteTest
//
//*****************************************************************************
void PMBusController_initWriteByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_2 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_2 == 1
}

//*****************************************************************************
//
// PMBusController_runWriteByteTest
//
//*****************************************************************************
void PMBusController_runWriteByteTest(PMBus_TestHandle handle)
{
    //
    // Put command (index 0) into buffer and 1 byte of data (index 1)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    pmbusControllerBuffer[1] = TEST2_DATA_BYTE;

    //
    // Do a write byte
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // 1 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 1U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 2U);

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
