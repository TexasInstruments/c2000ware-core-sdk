//###########################################################################
//
// FILE:   test_extended_write_word.c
//
// TITLE:  Write Word (Extended) Test
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
// PMBusController_initExtendedWriteWordTest
//
//*****************************************************************************
void PMBusController_initExtendedWriteWordTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_19 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_19 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedWriteWordTest
//
//*****************************************************************************
void PMBusController_runExtendedWriteWordTest(PMBus_TestHandle handle)
{
    //
    // Add extended command (index 0), command (index 1), and
    // word data to buffer (index 2 and 3)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_VOUT_COMMAND;
    pmbusControllerBuffer[2] = PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V1;
    pmbusControllerBuffer[3] = PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2;

    //
    // Do an extended write word
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable extended command,
    // 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, TEST19_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_EXT_CMD |
                        PMBUS_CONTROLLER_ENABLE_CMD));
                        
    //
    // Send extended command, command, and 1 word of data
    //    
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], TEST19_4BYTES);

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
