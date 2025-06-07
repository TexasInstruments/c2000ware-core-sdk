//###########################################################################
//
// FILE:   pmbus_controller_test.h
//
// TITLE:  Various controller transactions for testing target state machine
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifndef PMBUS_CONTROLLER_TEST_H
#define PMBUS_CONTROLLER_TEST_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//!
//! \defgroup PMBUS_CONTROLLER_TESTS PMBus Controller Mode Tests
//
//!
//! \ingroup PMBUS_CONTROLLER_TESTS
// @{
//
//*****************************************************************************

//
// Includes
//
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pmbus_examples_setup.h"
#include "pmbus_stack_handler.h"

//
// Defines
//
#define ENABLE_TEST_1       1 // Send Byte
#define ENABLE_TEST_2       1 // Write Byte
#define ENABLE_TEST_3       1 // Write Word
#define ENABLE_TEST_4       1 // Block Write
#define ENABLE_TEST_5       1 // Receive Byte
#define ENABLE_TEST_6       1 // Read Byte
#define ENABLE_TEST_7       1 // Read Word
#define ENABLE_TEST_8       1 // Block Read
#define ENABLE_TEST_9       1 // Block Write/ Read/ Process Call
#define ENABLE_TEST_10      1 // Quick Command
#define ENABLE_TEST_11      1 // Block Write (command, byte count, 2 bytes)
                              // - this is actually a write word
#define ENABLE_TEST_12      1 // Block Write (command, byte count, 3 bytes)
#define ENABLE_TEST_13      1 // Block Read (3 bytes)
#define ENABLE_TEST_14      1 // Process call (write word then read word)
#define ENABLE_TEST_15      0 // Alert
#define ENABLE_TEST_16      0 // Alert (from non-existent target)
#define ENABLE_TEST_17      1 // Group Command (target 1st to be addressed)
#define ENABLE_TEST_18      1 // Extended Write Byte
#define ENABLE_TEST_19      1 // Extended Write Word
#define ENABLE_TEST_20      1 // Extended Read Byte
#define ENABLE_TEST_21      1 // Extended Read Word

#define TARGET_ADDRESS_MASK  0xFEU

//
// Typedefs
//

//*****************************************************************************
//
//! PMBUS_TEST structure
//
//*****************************************************************************
typedef struct
{
    uint16_t    count;          //!< #bytes (block transactions > 4)
    int16_t     pass;           //!< pass metric
    int16_t     fail;           //!< fail metric
    bool        enabled;        //!< bool if this test is enabled or not
    void (*init)(void *);       //!< Function pointer to test init routine
    void (*run)(void *);        //!< Function pointer to test run routine
} PMBus_TestObject;

//*****************************************************************************
//
//! Handle to the PMBUS_TEST structure
//
//*****************************************************************************
typedef PMBus_TestObject *PMBus_TestHandle;

//
// Globals
//
extern PMBus_TestObject PMBUS_TESTS[NTESTS];
extern PMBus_TestHandle handle;

extern void (*runTestList[NTESTS])(PMBus_TestHandle);
extern void (*initTestList[NTESTS])(PMBus_TestHandle);

extern volatile int16_t pass, fail;

extern PMBus_StackObject pmbusStackController;
extern PMBus_StackHandle pmbusStackControllerHandle;
extern uint16_t pmbusControllerBuffer[256];

extern volatile bool targetAckReceived;
extern volatile bool endOfMessage;
extern volatile bool controllerDataAvailable;
extern volatile bool controllerDataRequested;
extern volatile bool receivedPecValid;
extern volatile bool alertEdgeAsserted;
extern volatile bool clockLowTimeout;
extern volatile uint16_t bytesReceived;
extern volatile uint32_t pmbusStatus;

//
// Function Prototypes
//

//*****************************************************************************
//
//! Reset the global PMBus module flags
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusController_resetGlobalFlags(void)
{
    targetAckReceived = false;
    endOfMessage = false;
    controllerDataAvailable = false;
    controllerDataRequested = false;
    receivedPecValid = false;
    alertEdgeAsserted = false;
    clockLowTimeout = false;
    bytesReceived = 0U;
}

//*****************************************************************************
//
//! Reset the PMBus Stack Object Test Statues and Counts
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusController_resetTestObject(PMBus_TestHandle handle)
{
    handle->count = 0U;
    handle->pass = 0U;
    handle->fail = 0U;
    handle->enabled = false;
}

//*****************************************************************************
//
//! Initialize the "Send Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initSendByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Send Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runSendByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Write Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initWriteByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Write Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runWriteByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Write Word" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initWriteWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Write Word" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runWriteWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Write" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockWriteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Write" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockWriteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Receive Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initReceiveByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Receive Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 2
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runReceiveByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Read Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initReadByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Read Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 3
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runReadByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Read Word" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initReadWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Read Word" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runReadWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Read" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockReadTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Read" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 258
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockReadTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Read (3 Bytes)" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockRead3BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Read (3 Bytes)" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockRead3BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Write, Block Read, Process Call" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockWriteReadProcessCallTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Write, Block Read, Process Call" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 258
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockWriteReadProcessCallTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Quick Command" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initQuickCommandTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Quick Command" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runQuickCommandTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Write (2 Bytes)" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockWrite2BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Write (2 Bytes)" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockWrite2BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Block Write (3 Bytes)" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initBlockWrite3BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Block Write (3 Bytes)" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runBlockWrite3BytesTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Process Call" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initProcessCallTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Process Call" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runProcessCallTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Alert" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initAlertTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Alert" Response Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runAlertTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "No Alert" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initNoAlertTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "No Alert" Response Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note This test requires a 2nd PMBus target on the network asserting the
//!       alert line.
//! \note Expected pass value: 5
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runNoAlertTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Group Command" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initGroupCommandTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Group Command" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runGroupCommandTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Extended Write Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initExtendedWriteByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Extended Write Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runExtendedWriteByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Extended Write Word" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initExtendedWriteWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Extended Write Word" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runExtendedWriteWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Extended Read Byte" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initExtendedReadByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Extended Read Byte" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 3
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runExtendedReadByteTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Initialize the "Extended Read Word" Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_initExtendedReadWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
//! Run the "Extended Read Word" Command Test
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected pass value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusController_runExtendedReadWordTest(PMBus_TestHandle handle);

//*****************************************************************************
//
// Close the Doxygen group.
// @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // PMBUS_CONTROLLER_TEST_H
