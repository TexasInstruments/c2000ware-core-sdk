//###########################################################################
//
// FILE:   test_block_write.c
//
// TITLE:  Block Write (255 bytes) Test
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
#if 0
void PMBusController_runBlockWriteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t i = 0U;
    uint32_t base = I2CA_BASE;
    uint32_t bytes_sent = 0U;

    //
    // Set command in buffer
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;

    pmbusControllerBuffer[1] = handle->count;

    for(i = 2U; i <= handle->count; i++)
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

    //
    // Transfer the first 4 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    //
    //PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 4U);
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, 4U, false); //Write word
    bytes_sent = 2U;

    //
    // Write the remaining bytes in chunks of 4, last transaction is N+2 % 4
    //
    for(i = 4U; i <= (handle->count+2U);) // 2U - one for command + one for byte count
    {
        //
        // Wait for DATA_REQUEST to assert
        //
        while(controllerDataRequested == false)
        {
        }

        controllerDataRequested = false;


        //if((handle->count - i - 1U) >= 4U)
        if((handle->count - bytes_sent)>=4U)
        {
            //
            // Transfer 4 bytes at a time
            //
            //PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[i], 4U);
            if((handle->count - bytes_sent )>4U)
            {
                I2CWrite(base, TARGET_ADDRESS, &pmbusControllerBuffer[i], 4U, false);
            }
            else
            {
                I2CWrite(base, TARGET_ADDRESS, &pmbusControllerBuffer[i], 4U, true); //last 4 bytes
            }
            i = i + 4U;
            bytes_sent = bytes_sent + 4U;
        }
        else
        {
            //
            // Remaing bytes < 4U
            //
            I2CWrite(base, TARGET_ADDRESS, &pmbusControllerBuffer[i], (handle->count -bytes_sent), true); //Write word

            //PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[i],
            //                    (handle->count + 1U - i));

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
#endif


void PMBusController_runBlockWriteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint16_t i = 0U;
    uint32_t base = I2CA_BASE;

    //
    // Set command in buffer
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;

    pmbusControllerBuffer[1] = handle->count;

    for(i = 2U; i <= handle->count; i++)
    {
        //
        // Bytes #0 to #N-1 (254)
        //
        pmbusControllerBuffer[i] = i - 2;
    }

#ifdef PEC_ENABLED
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(pmbusStackControllerHandle);
    CRCBuffer[0]= TARGET_ADDRESS <<1;
    pmbusCRCMsgSize = 1U;
    //Calculate PEC
    pmbusControllerBuffer[i+1]  = calc_PEC(CRCBuffer,pmbusCRCMsgSize, pmbusControllerBuffer, handle->count);
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count+3U, true); //count = command + byte_count + bytes + PEC

#else
    //
    // Block writes must be done in chunks of 4 bytes starting with the
    // command byte
    //

    //
    // Config the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // >=3 bytes to transfer
    //

    //
    // Transfer the first 4 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    //
    //PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], 4U);
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count+2U, true); //count = command + byte_count + bytes
#endif
    // Wait for I2C bus to clear
    while(I2C_getStopConditionStatus(base));
    while(I2C_isBusBusy(base));

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
