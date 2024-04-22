//###########################################################################
//
// FILE:   test_extended_read_byte.c
//
// TITLE:  Read Byte (Extended)
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
// PMBusController_initExtendedReadByteTest
//
//*****************************************************************************
void PMBusController_initExtendedReadByteTest(PMBus_TestHandle handle)
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
    handle->count = 1;

    //
    // Enable the test
    //
#if ENABLE_TEST_20 == 1
    handle->enabled = true;
#else
    handle->enabled = false;
#endif //ENABLE_TEST_20 == 1
}

//*****************************************************************************
//
// PMBusController_runExtendedReadByteTest
//
//*****************************************************************************
void PMBusController_runExtendedReadByteTest(PMBus_TestHandle handle)
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
    // Do an extended read byte
    // Config the controller to send an extended read-byte command
    // (by asserting the command and extended command bits) and then to issue
    // a repeated start followed by a read (i.e. enable
    // read) and get a data byte and a PEC from the target. Also enable PEC
    // processing on the controller side to verify the PEC
    //
    //
    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_OPERATION command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_OPERATION;

    I2CWrite(base, TARGET_ADDRESS, pmbusControllerBuffer,TEST20_2BYTES, false);


#if PEC_ENABLED
    handle->count+=1;
#endif
    //
    // Read received data
    //
     bytesReceived = I2CRead(base, TARGET_ADDRESS, pmbusControllerBuffer, handle->count, true);

      while(I2C_isBusBusy(base));

    //
    // Wait for the EOM, the target transmits all its data, the
    // controller NACKs it, and then issues an EOM on the bus
    // -- this flag is set in the ISR
    // NOTE: Although the controller issues a NACK to the target to indicate the
    // end of transmission, the NACK bit (status) is not asserted at the controller
    // end, only at the target end.
    //

    //
    // Check the received byte
    //
    (bytesReceived == handle->count) ? handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[0] == (PMBUS_CMD_OPERATION ^ CMD_XOR_MASK_V1)) ? 
                             handle->pass++ : handle->fail++;

   // (receivedPecValid == true) ? handle->pass++ : handle->fail++;

    //
    // Check that expected pass counter value is correct
    //
    if(handle->pass != 2U)
    {
        handle->fail++;
    }

    return;
}

//
// End of File
//
