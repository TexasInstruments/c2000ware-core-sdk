//###########################################################################
//
// FILE:   test_extended_read_byte.c
//
// TITLE:  Read Byte (Extended)
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
#include "pmbus_controller_test.h"

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
    uint16_t nBytes = 0U;

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
    PMBus_configController(PMBUSA_BASE, TARGET_ADDRESS, handle->count,
                       (PMBUS_CONTROLLER_ENABLE_PEC | PMBUS_CONTROLLER_ENABLE_READ |
                        PMBUS_CONTROLLER_ENABLE_CMD | PMBUS_CONTROLLER_ENABLE_EXT_CMD));

    //
    // Load the extended command and command bytes into the transmit register,
    // in this case the PMBUS_CMD_OPERATION command
    //
    pmbusControllerBuffer[0] = PMBUS_CMD_MFR_SPECIFIC_COMMAND;
    pmbusControllerBuffer[1] = PMBUS_CMD_OPERATION;
    PMBus_putControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0], TEST20_2BYTES);

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

    nBytes = PMBus_getControllerData(PMBUSA_BASE, &pmbusControllerBuffer[0],
                                 pmbusStatus);

    //
    // Check the received byte
    //
    (nBytes == handle->count) ? handle->pass++ : handle->fail++;

    (pmbusControllerBuffer[0] == (PMBUS_CMD_OPERATION ^ CMD_XOR_MASK_V1)) ? 
                             handle->pass++ : handle->fail++;

    (receivedPecValid == true) ? handle->pass++ : handle->fail++;

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
