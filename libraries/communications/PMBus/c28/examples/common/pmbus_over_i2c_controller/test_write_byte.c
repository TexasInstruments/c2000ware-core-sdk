//###########################################################################
//
// FILE:   test_write_byte.c
//
// TITLE:  Write Byte Test
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
// PMBusController_initWriteByteTest
//
//*****************************************************************************
void PMBusController_initWriteByteTest(PMBus_TestHandle handle)
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
#if ENABLE_TEST_2 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_2 == 1
}

//*****************************************************************************
//
// PMBusController_runWriteByteTest
//
//*****************************************************************************
void PMBusController_runWriteByteTest(PMBus_TestHandle handle)
{
    //
    // Locals
    //
    uint32_t base = I2CA_BASE;
    uint16_t nBytes = 2U;
    uint16_t index = 0U;

    //
    // Put command (index 0) into buffer and 1 byte of data (index 1)
    //
    pmbusControllerBuffer[index] = PMBUS_CMD_VIN_OV_FAULT_LIMIT;
    index++;
    pmbusControllerBuffer[index] = TEST2_DATA_BYTE;
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
    // Do a write byte

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer, nBytes, true); //Write byte

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
