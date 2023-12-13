//###########################################################################
//
// FILE:   test_block_write.c
//
// TITLE:  Block Write (255 bytes) Test
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
// PMBusController_initBlockWriteTest
//
//*****************************************************************************
void PMBusController_initBlockWriteTest(PMBus_TestHandle handle)
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
    // Set the block length to 255
    //
    handle->count = 255U;

    //
    // Enable the test
    //
#if ENABLE_TEST_4 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_4 == 1
}

//*****************************************************************************
//
// PMBusController_runBlockWriteTest
//
//*****************************************************************************
void PMBusController_runBlockWriteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t i = 0U;

    //
    // Set command in buffer
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;

    for(i = 1U; i <= handle->count; i++)
    {
        //
        // Bytes #0 to #N-1 (254)
        //
        pmbusControllerBuffer[i] = i - 1;
    }

    //
    // Block writes must be done in chunks of 4 bytes starting with the
    // command byte
    //

    //
    // Config the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // >=3 bytes to transfer
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, handle->count,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Transfer the first 4 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 4U);

    //
    // Write the remaining bytes in chunks of 4, last transaction is N+2 % 4
    //
    for(i = 4U; i <= handle->count;)
    {
        //
        // Wait for DATA_REQUEST to assert
        //
        while(controllerDataRequested == false)
        {
        }

        controllerDataRequested = false;

        if((handle->count - i - 1U) >= 4U)
        {
            //
            // Transfer 4 bytes at a time
            //
            PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[i], 4U);

            i = i + 4U;
        }
        else
        {
            //
            // Remaing bytes < 4U
            //
            PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[i],
                                (handle->count + 1U - i));

            i += (handle->count + 1U - i);
        }

        //
        // NOTE: PEC is automatically inserted at the end of block write
        // transmission
        //
    }

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
