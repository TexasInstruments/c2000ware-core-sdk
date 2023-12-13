//###########################################################################
//
// FILE:   test_extended_write_word.c
//
// TITLE:  Write Word (Extended) Test
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
// PMBusController_initExtendedWriteWordTest
//
//*****************************************************************************
void PMBusController_initExtendedWriteWordTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_19 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_19 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedWriteWordTest
//
//*****************************************************************************
void PMBusController_runExtendedWriteWordTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 4U;
    uint16_t index = 0U;

    //
    // Add extended command (index 0), command (index 1), and
    // word data to buffer (index 2 and 3)
    //
    pmbusControllerBuffer[index] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    index++;
    pmbusControllerBuffer[index] = PMBUS_CMD_VOUT_COMMAND;
    index++;
    pmbusControllerBuffer[index] = PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V1;
    index++;
    pmbusControllerBuffer[index] = PMBUS_CMD_VOUT_COMMAND ^ CMD_XOR_MASK_V2;
    index++;


#ifdef PEC_ENABLED
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(pmbusStackControllerHandle);
    CRCBuffer[0]= TARGET_ADDRESS <<1;
    CRCBuffer[1]=pmbusControllerBuffer[0];
    CRCBuffer[2]=pmbusControllerBuffer[1];
    CRCBuffer[3]=TARGET_ADDRESS <<1;
    pmbusCRCMsgSize = 4U;
    //Calculate PEC
    pmbusControllerBuffer[index]  = calc_PEC(CRCBuffer,pmbusCRCMsgSize, &pmbusControllerBuffer[2], 2);
    nBytes+=1U;
#endif
    //
    // Do an extended write word
    // Configure the controller to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable extended command,
    // 2 bytes
    //
    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, nBytes, true);

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
