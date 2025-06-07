//###########################################################################
//
// FILE:   test_extended_read_word.c
//
// TITLE:  Read Word (Extended) Test
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
// PMBusController_initExtendedReadWordTest
//
//*****************************************************************************
void PMBusController_initExtendedReadWordTest(PMBus_TestHandle handle)
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
    // Set count to 2
    //
    handle->count = 2;

    //
    // Enable the test
    //
#if ENABLE_TEST_21 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_21 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedReadWordTest
//
//*****************************************************************************
void PMBusController_runExtendedReadWordTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0U, handle->count * sizeof(uint16_t));

    //
    // Do a extended read byte
    // Configure the controller to send a read-word command (by asserting the
    // command and extended command bits) and then to issue a repeated start
    // followed by a read (i.e. enable read) and get two data bytes and a
    // PEC from the target. Also enable PEC processing on the controller side to
    // verify the PEC
    //
     //
    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_VOUT_COMMAND command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_VOUT_COMMAND;

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer,handle->count, false);

#if PEC_ENABLED
    handle->count+=1;
#endif
    //
    // Read received data
    //
    bytesReceived = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);

    while(I2C_isBusBusy(base));

    //
    // Check the received byte
    //
    (bytesReceived == handle->count) ? handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[0] == (PMBUS_CMD_MFR_SPECIFIC_COMMAND ^ CMD_XOR_MASK_V1)) ?
                             handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[1] == (PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2)) ?
                             handle->pass++ : handle->fail++;

    //(receivedPecValid == true) ? handle->pass++ : handle->fail++;

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
