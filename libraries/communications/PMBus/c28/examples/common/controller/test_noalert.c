//###########################################################################
//
// FILE:   test_noalert.c
//
// TITLE:  Alert Response to a different target Test
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
// PMBusController_initNoAlertTest
//
//*****************************************************************************
void PMBusController_initNoAlertTest(PMBus_TestHandle handle)
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
    handle->count = 1U;

    //
    // Enable the test
    //
#if ENABLE_TEST_16 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_16 == 1
}

//*****************************************************************************
//
// PMBusController_runNoAlertTest
//
//*****************************************************************************
void PMBusController_runNoAlertTest(PMBus_TestHandle handle)
{
    //
    // Important: A 2nd target is required to be on the network to assert
    // the alert line in order to test the 1st target software stack response.
    //
    // Lets assume 2nd target address is 0x39
    //

    //
    // Increment fail, a DATA_REQUEST should set it back to 0
    //
    handle->fail++;

    //
    // Do a Quick command
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_2_ADDRESS, 0U, PMBUS_ENABLE_WRITE);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
        if(controllerDataRequested == true)
        {
            //
            // decrement fail if DATA_REQUEST was asserted
            //
            handle->fail--;

            //
            // Reset the flag
            //
            controllerDataRequested = false;

            //
            // NACK the transaction to complete the quick command
            //
            PMBus_nackTransaction(PMBUSA_BASE);
        }
    }

    //
    // Reset the EOM flag
    //
    endOfMessage = false;

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Loop till the alert signal is asserted
    //
    while(alertEdgeAsserted == false)
    {
    }

    //
    // Clear the spot where the alerting target's address will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // An alert was recevied
    // Configure the controller to set the address to the alert address,
    // enable Read and expect the alerting target's address (no PEC)
    //
    PMBus_configController(PMBUSA_BASE, ALERT_RESPONSE_ADDRESS, 1U,
                       PMBUS_CONTROLLER_ENABLE_READ);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
    }
    PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0],
                        pmbusStatus);

    //
    // NOTE:  the alert line needs to be asserted for the target to respond
    // to the alert response address, if you de-assert early the target
    // ignores the alert response address line. The target state machine will
    // de-assert when it detects an EOM, NACK and ALERT_EDGE
    //

    //
    // Check DATA_READY is asserted at the end of alert response
    //
    (controllerDataAvailable == true) ? handle->pass++ : handle->fail++;

    //
    // Check that the alerting target sent its address
    //
    (bytesReceived == 1U) ? handle->pass++ : handle->fail++;

    //
    // Target sends its address in the 7 most significant bits with a
    // 0 or 1 in the LSb, which we dont care about
    //
    ((pmbusControllerBuffer[0] & TARGET_ADDRESS_MASK) == (TARGET_2_ADDRESS << 1U)) ?
                                                    handle->pass++ :
                                                    handle->fail++;

    //
    // Reset flags
    //
    PMBusController_resetGlobalFlags();

    //
    // Increment fail, a DATA_REQUEST should set it back to 0
    //
    handle->fail++;

    //
    // Do a Quick command to 1st target
    // Config the controller enable Write (by omitting the read
    // option from the configWord, you enable write), 0 byte
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 0U, 0U);

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    while(endOfMessage == false)
    {
        if(controllerDataRequested == true)
        {
            //
            // decrement fail if DATA_REQUEST was asserted
            //
            handle->fail--;

            //
            // Reset the flag
            //
            controllerDataRequested = false;

            //
            // NACK the transaction to complete the quick command
            //
            PMBus_nackTransaction(PMBUSA_BASE);
        }
    }

    //
    // Once the bus is free, if the target NACK'd its a failure
    //
    (targetAckReceived == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 5U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
