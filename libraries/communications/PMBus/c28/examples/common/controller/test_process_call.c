//###########################################################################
//
// FILE:   test_process_call.c
//
// TITLE:  Process Call (write word, then read word)
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
// PMBusController_initProcessCallTest
//
//*****************************************************************************
void PMBusController_initProcessCallTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_14 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_14 == 1
}

//*****************************************************************************
//
// PMBusController_runProcessCallTest
//
//*****************************************************************************
void PMBusController_runProcessCallTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t nBytes = 0U;

    //
    // Add command (index 0) and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    pmbusControllerBuffer[1] = TEST14_DATA_BYTE_1;
    pmbusControllerBuffer[2] = TEST14_DATA_BYTE_2;

    //
    // Do a Process Call (write word then read word)
    // Configure the controller to enable PEC (processing), enable Write (by
    // omitting the read option from the configWord, you enable write),
    // enable command, enable process call (the controller does the read word,
    // with the repeated start, right after the write word finishes)
    // Write, and then read 2 bytes
    //
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, 2U,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_PRC_CALL |
                        PMBUS_CONTROLLER_ENABLE_CMD));

    //
    // Send data
    //
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 3U);

    //
    // Controller automatically issues a repeated start (because of the process
    // call), and waits for the target to respond with the word...when
    // the necessary bytes (specified in PMBMC.BYTE_COUNT) is received, controller
    // NACKs last byte and generates an EOM
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
    }

    if((endOfMessage == true) && (controllerDataAvailable == true))
    {
        //
        // EOM = 1 DATA_READY = 1
        //
        nBytes = PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[nBytes],
                                     pmbusStatus);

        //
        // No need to reset these flags, they will be reset at the start of the
        // next test
        //
    }

    //
    // Check that we got 2 bytes, correct data, and valid PEC
    //
    (nBytes == 2U) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == (TEST14_DATA_BYTE_1 ^ TEST14_XOR_MASK)) ? 
                             handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[1] == (TEST14_DATA_BYTE_2 ^ TEST14_XOR_MASK)) ? 
                             handle->pass++ : handle->fail++;
    (receivedPecValid == true) ? handle->pass++ : handle->fail++;

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
