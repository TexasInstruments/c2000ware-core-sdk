//###########################################################################
//
// FILE:   test_group_command.c
//
// TEST:   Group Command Test
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
// PMBusController_initGroupCommandTest
//
//*****************************************************************************
void PMBusController_initGroupCommandTest(PMBus_TestHandle handle)
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
    // Set count to 3
    //
    handle->count = 3U;

    //
    // Enable the test
    //
#if ENABLE_TEST_17 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_17 == 1
}

//*****************************************************************************
//
// PMBusController_runGroupCommandTest
//
//*****************************************************************************
void PMBusController_runGroupCommandTest(PMBus_TestHandle handle)
{
    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Add command (index 0) and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_VOUT_MIN;
    pmbusControllerBuffer[1] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V3;
    pmbusControllerBuffer[2] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V4;

    //
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, TEST17_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_GRP_CMD |
                        PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], handle->count);

    //
    // Wait on DATA_REQUEST
    //
    while(controllerDataRequested == false)
    {
        //
        // Fail if EOM & NACK after the 1st message
        //
        if(endOfMessage == true && targetAckReceived == false)
        {
            handle->fail++;
            break;
        }
    }

    //
    // Reset data requested flag
    //
    controllerDataRequested = false;

    //
    // Check if target ACK is received
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Add command (index 0) and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_VOUT_MAX;
    pmbusControllerBuffer[1] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V3;
    pmbusControllerBuffer[2] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V4;

    //
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS + 1U, TEST17_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_GRP_CMD |
                        PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], handle->count);

    //
    // Wait on DATA_REQUEST
    //
    while(controllerDataRequested == false)
    {
        //
        // exit if EOM & NACK after the 2nd message
        // This target doesnt exist on the bus and controller will see
        // a NACK for this address, which generateds the EOM.
        //
        if((endOfMessage == true) && (targetAckReceived == false))
        {
            handle->pass++;
            break;
        }
    }

    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Add command (index 0) and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_IOUT_MAX;
    pmbusControllerBuffer[1] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V3;
    pmbusControllerBuffer[2] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V4;

    //
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable group command,
    // enable command, 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS + 2U, TEST17_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_GRP_CMD |
                        PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], handle->count);

    //
    // Wait on DATA_REQUEST
    //
    while(controllerDataRequested == false)
    {
        //
        // exit if EOM & NACK after the 3rd message
        // This target doesnt exist on the bus and controller will see
        // a NACK for this address, which generateds the EOM.
        //
        if((endOfMessage == true) && (targetAckReceived == false))
        {
            handle->pass++;
            break;
        }
    }

    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Add command (index 0) and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_POUT_MAX;
    pmbusControllerBuffer[1] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V3;
    pmbusControllerBuffer[2] = pmbusControllerBuffer[0] ^ CMD_XOR_MASK_V4;

    //
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), disable group command
    // (by ommitting it), enable command, 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS + 3U, TEST17_2BYTES,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], handle->count);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }

    //
    // if EOM & NACK after the 4th message
    // This target doesnt exist on the bus and controller will see
    // a NACK for this address, which generateds the EOM.
    //
    if((endOfMessage == true) && (targetAckReceived == false))
    {
        handle->pass++;
    }

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 4U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
