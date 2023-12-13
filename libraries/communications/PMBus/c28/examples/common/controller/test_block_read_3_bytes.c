//###########################################################################
//
// FILE:   test_block_read_3_bytes.c
//
// TITLE:  Block Read (3 bytes) Test
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
// PMBusController_initBlockRead3BytesTest
//
//*****************************************************************************
void PMBusController_initBlockRead3BytesTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_13 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_13 == 1
}

//*****************************************************************************
//
// PMBusController_runBlockRead3BytesTest
//
//*****************************************************************************
void PMBusController_runBlockRead3BytesTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t count = 0U;
    uint16_t nBytes = 0U;
    uint16_t i = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Do a read byte
    // Config the controller to send a read-block command (by asserting the command
    // bit) and then to issue a repeated start followed by a read (i.e. enable
    // read) and get handle->count data bytes and a PEC from the target. Also
    // enable PEC proecessing on the controller side to verify the PEC
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, handle->count,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_READ |
                        PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Load the command byte into the transmit register,
    // in this case the PMBUS_CMD_READ_EOUT command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_READ_EOUT;
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 1U);

    //
    // Wait for the EOM, the target transmits all its data, the
    // controller NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the controller issues a NACK to the target to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the controller
    // end, only at the target end.
    //
    while(endOfMessage == false)
    {
        if(controllerDataAvailable == true)
        {
            //
            // Reset the flag
            //
            controllerDataAvailable = false;
            count = PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[nBytes],
                                        pmbusStatus);
            nBytes += count;
        }
    }

    if((endOfMessage == true) && (controllerDataAvailable == true))
    {
        //
        // EOM = 1 DATA_READY = 1, but this wasnt captured in the while loop
        // above
        //
        count = PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[nBytes],
                                    pmbusStatus);
        nBytes += count;

        //
        // No need to reset these flags, they will be reset at the start of the
        // next test
        //
    }

    //
    // Check that we got nBytes + 1 (byte count) bytes
    //
    (nBytes == handle->count + 1) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == handle->count) ? handle->pass++ : handle->fail++;

    for(i = 1U; i <= handle->count; i++)
    {
        if(pmbusControllerBuffer[i] == (PMBUS_CMD_READ_EOUT ^ i))
        {
            handle->pass++;
        }
        else
        {
            handle->fail++;
        }
    }

    (receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 6U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
