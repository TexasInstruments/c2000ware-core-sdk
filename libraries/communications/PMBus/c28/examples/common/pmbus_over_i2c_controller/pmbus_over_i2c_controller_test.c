//###########################################################################
//
// FILE:   pmbus_over_i2c_controller_test.c
//
// TITLE:  Various controller transactions for testing target state machine
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

//
// Globals
//
PMBus_TestObject PMBUS_TESTS[NTESTS];
PMBus_TestHandle handle;

void (*initTestList[NTESTS])(PMBus_TestHandle) =
{

     PMBusController_initQuickCommandTest,
     PMBusController_initSendByteTest,
     PMBusController_initWriteByteTest,
     PMBusController_initWriteWordTest,
     PMBusController_initReceiveByteTest,
     PMBusController_initReadByteTest,
     PMBusController_initReadWordTest,
     PMBusController_initExtendedWriteByteTest,
     PMBusController_initExtendedWriteWordTest,
     PMBusController_initExtendedReadByteTest,
     PMBusController_initExtendedReadWordTest,
     PMBusController_initProcessCallTest,
     PMBusController_initBlockReadTest,
     PMBusController_initBlockWriteTest






 };

void (*runTestList[NTESTS])(PMBus_TestHandle) =
{
     PMBusController_runQuickCommandTest,
     PMBusController_runSendByteTest,
     PMBusController_runWriteByteTest,
     PMBusController_runWriteWordTest,
     PMBusController_runReceiveByteTest,
     PMBusController_runReadByteTest,
     PMBusController_runReadWordTest,
     PMBusController_runExtendedWriteByteTest,
     PMBusController_runExtendedWriteWordTest,
     PMBusController_runExtendedReadByteTest,
     PMBusController_runExtendedReadWordTest,
     PMBusController_runProcessCallTest,
     PMBusController_runBlockReadTest,
     PMBusController_runBlockWriteTest

 };

//
// End of File
//
