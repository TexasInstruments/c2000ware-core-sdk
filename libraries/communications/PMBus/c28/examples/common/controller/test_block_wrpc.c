//###########################################################################
//
// FILE:   test_block_wrpc.c
//
// TITLE:  Block Write-Read Process Call (255 bytes) Test
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
// PMBusController_initBlockWriteReadProcessCallTest
//
//*****************************************************************************
void PMBusController_initBlockWriteReadProcessCallTest(PMBus_TestHandle handle)
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
    // Set count to 255
    //
    handle->count = 255U;

    //
    // Enable the test
    //
#if ENABLE_TEST_9 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_9 == 1
}

//*****************************************************************************
//
// PMBusController_runBlockWriteReadProcessCallTest
//
//*****************************************************************************
void PMBusController_runBlockWriteReadProcessCallTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t i;
    uint16_t count = 0U;
    uint16_t nBytes = 0U;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // command, soon to be overwritten by block read
    //
    pmbusControllerBuffer[0]  = PMBUS_CMD_PAGE_PLUS_READ;

    for(i = 1U; i <= handle->count; i++)
    {
        //
        // Bytes #0 to #N-1
        //
        pmbusControllerBuffer[i] = pmbusControllerBuffer[0] ^ i;
    }

    //
    // Block-Write, Block-Read, and Process Call
    // Config the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // enable process call (the controller does the block read, with the repeated
    // start, right after the block write finishes)
    // Write, and then read, handle->count bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, handle->count,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_PRC_CALL |
                        PMBUS_CONTROLLER_ENABLE_CMD));

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
            // remaining bytes < 4U
            //
            PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[i],
                                (handle->count + 1U - i));

            i += (handle->count + 1U - i);
        }

        //
        // NOTE: PEC is not transmitted for a Block Write-Read Process Call
        //
    }
    //
    // Controller automatically issues a repeated start (because of the process
    // call), and waits for the target to respond with the block data...when
    // the necessary bytes (specified in PMBMC.BYTE_COUNT) is received, controller
    // NACKs last byte and generates an EOM
    // However, if the target is transmitting more than 3 bytes, the
    // DATA_READY goes high first, the RXBUF is full and must be read
    // before the target can send any more data
    //

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
        if(pmbusControllerBuffer[i] == PMBUS_CMD_PAGE_PLUS_READ)
        {
            handle->pass++;
        }
        else
        {
            handle->fail++;
        }
    }

    (receivedPecValid == true) ? handle->pass++: handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 258U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
