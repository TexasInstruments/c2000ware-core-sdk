//###########################################################################
//
// FILE:   test_block_write_2_bytes.c
//
// TITLE:  Block Write (2 bytes) Test
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
// PMBusController_initBlockWrite2BytesTest
//
//*****************************************************************************
void PMBusController_initBlockWrite2BytesTest(PMBus_TestHandle handle)
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
    // Set the block length to 2
    //
    handle->count = 2U;

    //
    // Enable the test
    //
#if ENABLE_TEST_11 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_11 == 1
}

//*****************************************************************************
//
// PMBusController_runBlockWrite2BytesTest
//
//*****************************************************************************
void PMBusController_runBlockWrite2BytesTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t i = 0U;

    //
    // Set command in buffer
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_PAGE_PLUS_WRITE;

    for(i = 1U; i <= handle->count; i++)
    {
        //
        // Bytes #0 to #N-1 (1)
        //
        pmbusControllerBuffer[i] = pmbusControllerBuffer[0] ^ i;
    }

    //
    // Block writes must be done in chunks of 4 bytes starting with the
    // command byte
    //

    //
    // Config the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // >3 bytes to transfer
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, handle->count,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Transfer the first 3 bytes, i.e., command, byte #0, #1,
    // NOTE: Byte count is NOT automatically inserted after command
    //        sinces less than 3 bytes are being transferred. This
    //        is an anomalous condition
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 3U);

    //
    // NOTE: PEC is automatically inserted at the end of block write
    // transmission
    //

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
