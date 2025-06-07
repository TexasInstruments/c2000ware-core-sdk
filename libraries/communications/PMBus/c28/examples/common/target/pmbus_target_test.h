//###########################################################################
//
// FILE:   pmbus_target_test.h
//
// TITLE:  Prototypes for the different target command handlers
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifndef PMBUS_TARGET_TEST_H
#define PMBUS_TARGET_TEST_H

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
//! \defgroup PMBUS_TARGET_TESTS PMBus Target Mode Tests
//
//!
//! \ingroup PMBUS_TARGET_TESTS
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
#include "pmbus_stack_config.h"
#include "pmbus_stack_handler.h"

//
// Globals
//
extern PMBus_StackObject pmbusStackTarget;
extern PMBus_StackHandle pmbusStackTargetHandle;
extern uint16_t pmbusTargetBuffer[300U];

extern volatile uint16_t testsCompleted;
extern volatile uint16_t pass, fail;

//
// Function Prototypes
//

//*****************************************************************************
//
//! Send Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_sendByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Write Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 5
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_writeByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Write Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_writeWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 260
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWriteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Receive Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_receiveByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Read Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_readByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Read Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_readWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Read (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockReadTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Read (3 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockRead3BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write/Read/Process Call (255 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 259
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWriteReadProcessCallTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Quick Command Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 4
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_quickCommandTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (2 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note An attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the controller does not put the byte count on the line.
//!
//! \note Make sure to run the write word test before this, as the original
//! write word Handler overwrites the handler to point to this function.
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWrite2BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Block Write (3 bytes) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note An attempted block write with 1 byte is a write byte, 2 bytes
//! a write word - the controller does not put the byte count on the line.
//!
//! \note Make sure to run the block write test before this, as the original
//! block write handler overwrites the handler to point to this function.
//!
//! \note Expected Pass Value: 8
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_blockWrite3BytesTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Process Call Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 5
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_processCallTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Alert Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_alertTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Alert (from 2nd target) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note This test requires a 2nd PMBus target on the network asserting
//!       the alert line.
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_noAlertTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Group Command (target 1st addressed) Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_groupCommandTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Write Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 6
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedWriteByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Write Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 7
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedWriteWordTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Extended Read Byte Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedReadByteTestHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! ExtendedRead Word Test Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! \note Expected Pass Value: 1
//!
//! \return None.
//
//*****************************************************************************
void
PMBusTarget_extendedReadWordTestHandler(PMBus_StackHandle handle);

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

#endif  // PMBUS_TARGET_TEST_H
