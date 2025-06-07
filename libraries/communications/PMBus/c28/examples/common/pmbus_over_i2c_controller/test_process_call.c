//###########################################################################
//
// FILE:   test_process_call.c
//
// TITLE:  Process Call (write word, then read word)
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
#include "pmbus_over_i2c_controller_test.h"
#include "pmbus_over_i2c_lib.h"

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
    uint32_t base = I2CA_BASE;

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

    //
    // Send data
    //
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, 3U, false);

    //
    // Controller automatically issues a repeated start (because of the process
    // call), and waits for the target to respond with the word...when
    // the necessary bytes (specified in PMBMC.BYTE_COUNT) is received, controller
    // NACKs last byte and generates an EOM
    //

    //
    // Read received data
    //
    nBytes = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, 2U, true);

    while(I2C_isBusBusy(base));

    //
    // Check that we got 2 bytes, correct data, and valid PEC
    //
    (nBytes == 2U) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == (TEST14_DATA_BYTE_1 ^ TEST14_XOR_MASK)) ? 
                             handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[1] == (TEST14_DATA_BYTE_2 ^ TEST14_XOR_MASK)) ? 
                             handle->pass++ : handle->fail++;
   // (receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 3U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
