//###########################################################################
//
// FILE:   test_block_read.c
//
// TITLE:  Block Read (16 bytes) Test
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
#include "pmbus_over_i2c_controller_test.h"
#include "pmbus_over_i2c_lib.h"

//*****************************************************************************
//
// PMBusController_initBlockReadTest
//
//*****************************************************************************
void PMBusController_initBlockReadTest(PMBus_TestHandle handle)
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
    // Set count to 16
    //
    handle->count = 16U;

    //
    // Enable the test
    //
#if ENABLE_TEST_8 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_8 == 1
}

//*****************************************************************************
//
// PMBusController_runBlockReadTest
//
//*****************************************************************************
void PMBusController_runBlockReadTest(PMBus_TestHandle handle)
{
    //
    // Locals    //
    uint16_t nBytes = 0U;
    uint16_t i = 0U;
    uint32_t base = I2CA_BASE;
    bytesReceived = 0U;
    volatile uint16_t byteCount =0U;
    uint16_t buff_pos = 1;

    //
    // Clear the spot where the command will go
    //
    memset(&pmbusControllerBuffer[0], 0xBAADU, handle->count * sizeof(uint16_t));

    //
    // Do a read byte
    // Config the controller to send a read-block command (by asserting the command
    // bit) and then to issue a repeated start followed by a read (i.e. enable
    // read) and get handle->count data bytes and a PEC from the target. Also
    // enable PEC proecessing on the controller side to verify the PEC
    //
    //
    // Load the command byte into the transmit register,
    // in this case the PMBUS_CMD_READ_EIN command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_READ_EIN;

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, 1, false);

    // Get the response - first byte is the data count
    nBytes = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);


    I2C_clearStatus(base, I2C_STS_STOP_CONDITION | I2C_STS_NO_ACK | I2C_STS_BYTE_SENT);


    //
    // Check that we got nBytes  (byte count) bytes
    //
    (nBytes == handle->count ) ? handle->pass++ : handle->fail++;
    (pmbusControllerBuffer[0] == handle->count) ? handle->pass++ : handle->fail++;

    for(i = 1U; i < handle->count; i++)
    {
        if(pmbusControllerBuffer[i] == (PMBUS_CMD_READ_EIN ^ i))
        {
            handle->pass++;
        }
        else
        {
            handle->fail++;
        }
    }

    //(receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != (handle->count +1U))
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
