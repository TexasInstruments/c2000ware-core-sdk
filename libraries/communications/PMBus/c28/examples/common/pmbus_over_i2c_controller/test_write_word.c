//###########################################################################
//
// FILE:   test_write_word.c
//
// TITLE:  Write Word Test
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
#include "pmbus_over_i2c_controller_test.h"
#include "pmbus_over_i2c_lib.h"

//*****************************************************************************
//
// PMBusController_initWriteWordTest
//
//*****************************************************************************
void PMBusController_initWriteWordTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_3 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_3 == 1
}

//*****************************************************************************
//
// PMBusController_runWriteWordTest
//
//*****************************************************************************
void PMBusController_runWriteWordTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 3U;
    uint16_t index = 0U;

    //
    // Add command (index 0)  and
    // word data to buffer (index 1 and 2)
    //
    pmbusControllerBuffer[index] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    index++;
    pmbusControllerBuffer[index] = TEST3_DATA_BYTE_1;
    index++;
    pmbusControllerBuffer[index] = TEST3_DATA_BYTE_2;
    index++;

#ifdef PEC_ENABLED
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(pmbusStackControllerHandle);
    CRCBuffer[0]= TARGET_ADDRESS <<1;
    pmbusCRCMsgSize = 1U;
    //Calculate PEC
    pmbusControllerBuffer[index]  = calc_PEC(CRCBuffer,pmbusCRCMsgSize, pmbusControllerBuffer, nBytes);
    nBytes+=1U;
#endif
    //
    // Do a write word
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // 2 bytes
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, nBytes, true); //Write word

    //
    // Wait for the EOM, and target to ack the address before
    // reading data -- done in the ISR
    //
    // Wait for I2C bus to clear
    while(I2C_getStopConditionStatus(base));
    while(I2C_isBusBusy(base));
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
