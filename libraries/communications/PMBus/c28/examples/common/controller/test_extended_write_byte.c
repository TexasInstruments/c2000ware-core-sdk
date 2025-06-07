//###########################################################################
//
// FILE:   test_extended_write_byte.c
//
// TITLE:  Write Byte (Extended)
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
// PMBusController_initExtendedWriteByteTest
//
//*****************************************************************************
void PMBusController_initExtendedWriteByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_18 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_18 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedWriteByteTest
//
//*****************************************************************************
void PMBusController_runExtendedWriteByteTest(PMBus_TestHandle handle)
{
    //
    // Add extended command (index 0), command (index 1), and
    // byte data to buffer (index 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_STORE_DEFAULT_CODE;
    pmbusControllerBuffer[2] = PMBUS_CMD_STORE_DEFAULT_CODE ^ CMD_XOR_MASK_V1;

    //
    // Do an extended write byte
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable extended command,
    // 1 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 1U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_EXT_CMD |
                        PMBUS_CONTROLLER_ENABLE_CMD));
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
