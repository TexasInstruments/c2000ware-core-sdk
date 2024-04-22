//###########################################################################
//
// FILE:   handle_alert.c
//
// TITLE:  Alert
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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_alertTestHandler
//
//*****************************************************************************
void PMBusTarget_alertTestHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    PMBus_Transaction transaction = PMBusStackObject_getTransactionType(handle);
    uint16_t addressedAs = PMBus_getOwnAddress(base);
    PMBus_accessType aType = PMBus_getCurrentAccessType(base);
    uint16_t preRunPass = pass;

    if(transaction == PMBUS_TRANSACTION_QUICKCOMMAND)
    {
        //
        // Got the quick command? assert the alert line
        //
        PMBus_assertAlertLine(base);
        pass++;
    }
    else
    {
        fail++;
    }

    //
    // Change the quick command handler for the next test
    //
    PMBusStackObject_setTransactionHandler(handle,
                                           PMBUS_TRANSACTION_QUICKCOMMAND,
                               (void (*)(void *))PMBusTarget_noAlertTestHandler);

    //
    // Check that expected pass counter value is correct
    //
    if((pass - preRunPass) != 1U)
    {
        fail++;
    }

    //
    // Update number of completed tests
    //
    testsCompleted++;
}

//
// End of File
//
