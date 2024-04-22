//###########################################################################
//
// FILE:   test_send_byte.c
//
// TITLE:  Send Byte Test
//
//###########################################################################
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
// PMBusController_initSendByteTest
//
//*****************************************************************************
void PMBusController_initSendByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_1 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_1 == 1
}

//*****************************************************************************
//
// PMBusController_runSendByteTest
//
//*****************************************************************************
void PMBusController_runSendByteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 1U;
    uint16_t index = 0U;

    //
    // Place data in buffer
    //
    pmbusControllerBuffer[index] = TEST1_DATA_BYTE;
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
    // Do a send byte
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), 1 byte
    //
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, nBytes, true); //Send byte

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
