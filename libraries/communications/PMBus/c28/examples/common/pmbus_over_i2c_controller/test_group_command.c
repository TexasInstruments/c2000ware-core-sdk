//###########################################################################
//
// FILE:   test_group_command.c
//
// TEST:   Group Command Test
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
    // Locals
    //
    uint32_t base=I2CA_BASE;

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
    // Send data
    //
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, false);

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

    //
    // Send data
    //
    I2CWrite(base, TARGET_ADDRESS+1U, pmbusControllerBuffer, handle->count, false);

    //
    // Check if target ACK is not received
    //
    (targetAckReceived == false) ? handle->pass++ : handle->fail++;

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

    //
    // Send data
    //
    I2CWrite(base, TARGET_ADDRESS+2U, pmbusControllerBuffer, handle->count, false);

    //
    // Check if target ACK is not received
    //
    (targetAckReceived == false) ? handle->pass++ : handle->fail++;

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

    //
    // Send data
    //
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);


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
