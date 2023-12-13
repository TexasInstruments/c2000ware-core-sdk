//###########################################################################
//
// FILE:   pmbus_controller_test.c
//
// TITLE:  Various controller transactions for testing target state machine
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
#include "pmbus_controller_test.h"

//
// Globals
//
PMBus_TestObject PMBUS_TESTS[NTESTS];
PMBus_TestHandle handle;

void (*initTestList[NTESTS])(PMBus_TestHandle) =
{
        PMBusController_initSendByteTest,
        PMBusController_initWriteByteTest,
        PMBusController_initWriteWordTest,
        PMBusController_initBlockWriteTest,
        PMBusController_initReceiveByteTest,
        PMBusController_initReadByteTest,
        PMBusController_initReadWordTest,
        PMBusController_initBlockReadTest,
        PMBusController_initBlockWriteReadProcessCallTest,
        PMBusController_initQuickCommandTest,
        PMBusController_initBlockWrite2BytesTest,
        PMBusController_initBlockWrite3BytesTest,
        PMBusController_initBlockRead3BytesTest,
        PMBusController_initProcessCallTest,
        PMBusController_initAlertTest,
        PMBusController_initNoAlertTest,
        PMBusController_initGroupCommandTest,
        PMBusController_initExtendedWriteByteTest,
        PMBusController_initExtendedWriteWordTest,
        PMBusController_initExtendedReadByteTest,
        PMBusController_initExtendedReadWordTest,
};

void (*runTestList[NTESTS])(PMBus_TestHandle) =
{
        PMBusController_runSendByteTest,
        PMBusController_runWriteByteTest,
        PMBusController_runWriteWordTest,
        PMBusController_runBlockWriteTest,
        PMBusController_runReceiveByteTest,
        PMBusController_runReadByteTest,
        PMBusController_runReadWordTest,
        PMBusController_runBlockReadTest,
        PMBusController_runBlockWriteReadProcessCallTest,
        PMBusController_runQuickCommandTest,
        PMBusController_runBlockWrite2BytesTest,
        PMBusController_runBlockWrite3BytesTest,
        PMBusController_runBlockRead3BytesTest,
        PMBusController_runProcessCallTest,
        PMBusController_runAlertTest,
        PMBusController_runNoAlertTest,
        PMBusController_runGroupCommandTest,
        PMBusController_runExtendedWriteByteTest,
        PMBusController_runExtendedWriteWordTest,
        PMBusController_runExtendedReadByteTest,
        PMBusController_runExtendedReadWordTest,
};

//
// End of File
//
