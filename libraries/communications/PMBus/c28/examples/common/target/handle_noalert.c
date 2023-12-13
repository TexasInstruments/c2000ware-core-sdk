//###########################################################################
//
// FILE:    handle_noalert.c
//
// TITLE:   Alert (different target on the line, this target does not respond)
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
#include "pmbus_target_test.h"

//*****************************************************************************
//
// PMBusTarget_noAlertTestHandler
//
//*****************************************************************************
void PMBusTarget_noAlertTestHandler(PMBus_StackHandle handle)
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

    //
    // Check transaction type
    //
    if(transaction == PMBUS_TRANSACTION_QUICKCOMMAND)
    {
        pass++;
    }
    else
    {
        fail++;
    }

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
