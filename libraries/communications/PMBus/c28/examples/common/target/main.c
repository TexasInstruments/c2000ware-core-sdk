//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS Target Demo Code
//
// Note: Requires connection to PMBus controller running controller demo
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
#include "pmbus_target_test.h"
#include <string.h>
#include "board.h"

//
// Globals
//
PMBus_StackObject pmbusStackTarget;
PMBus_StackHandle pmbusStackTargetHandle = &pmbusStackTarget;
uint16_t pmbusTargetBuffer[300U];
volatile uint16_t testsCompleted = 0U;
volatile uint16_t pass = 0U, fail = 0U;

//
// Function Prototypes
//
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc")
#else
#pragma CODE_SECTION(pmbusIntHandler, ".TI.ramfunc")
#endif // __cplusplus
__interrupt void pmbusIntHandler(void);
void PMBusStack_defaultErrorHandler(void);
void (*PMBusStack_errorHandler)(void);
//
// Main
//
int main(void)
{
    //
    // Locals
    //
    uint16_t i;
    //uint32_t moduleFreq = 0U;
    PMBusStack_errorHandler = PMBusStack_defaultErrorHandler;
#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBusExample_setupFlash();
#endif //defined(_FLASH)

    //
    // Setup the system clocking
    //
    PMBusExample_setupSysCtrl();

    //
    // Enable the PMBUS GPIOs
    //
    PMBusExample_setupGPIO();

    //
    // Setup the interrupt tables, register PMBUS interrupt handler
    //
    PMBusExample_setupInterrupts(pmbusIntHandler);

    //
    // Board initialization
    //
    Board_init();
    //
    // Transaction Handlers
    //
    // Set the default handlers, user must overwrite
    //
    for(i = 0U; i < NTRANSACTIONS; i++)
    {
        PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                        (PMBus_Transaction)i, (void (*)(void *))
                                        PMBusStack_defaultTransactionHandler);
    }

    //
    // Overwrite the send byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_SENDBYTE,
                              (void (*)(void *))PMBusTarget_sendByteTestHandler);

    //
    // Overwrite the write byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_WRITEBYTE,
                             (void (*)(void *))PMBusTarget_writeByteTestHandler);

    //
    // Overwrite the write word transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_WRITEWORD,
                             (void (*)(void *))PMBusTarget_writeWordTestHandler);

    //
    // Overwrite the block write transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_BLOCKWRITE,
                            (void (*)(void *))PMBusTarget_blockWriteTestHandler);

    //
    // Overwrite the Receive Byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_RECEIVEBYTE,
                           (void (*)(void *))PMBusTarget_receiveByteTestHandler);

    //
    // Overwrite the Read Byte transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_READBYTE,
                              (void (*)(void *))PMBusTarget_readByteTestHandler);

    //
    // Overwrite the Read Word transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_READWORD,
                              (void (*)(void *))PMBusTarget_readWordTestHandler);

    //
    // Overwrite the Block Read transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                           PMBUS_TRANSACTION_BLOCKREAD,
                             (void (*)(void *))PMBusTarget_blockReadTestHandler);

    //
    // Overwrite the Block Write Read Process Call transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                 PMBUS_TRANSACTION_BLOCKWRPC, (void (*)(void *))
                               PMBusTarget_blockWriteReadProcessCallTestHandler);

    //
    // Overwrite the Quick Command transaction handler
    //
    PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                          PMBUS_TRANSACTION_QUICKCOMMAND,
                         (void (*)(void *))PMBusTarget_quickCommandTestHandler);

    //
    // Set the buffer to some default non-zero value
    //
    memset(pmbusTargetBuffer, 0xBAADU, sizeof(pmbusTargetBuffer));

    //
    // Setup the PMBUS Stack Object
    //
    PMBusStackObject_setMode(pmbusStackTargetHandle, PMBUS_STACK_MODE_TARGET);

    //
    // Set the target address and mask
    //
    PMBusStackObject_setTargetAddress(pmbusStackTargetHandle, TARGET_ADDRESS);
    PMBusStackObject_setTargetAddressMask(pmbusStackTargetHandle,
                                         TARGET_ADDRESSMASK);

    //
    // Initialize the state machine handler
    //
    PMBusStack_initModule(pmbusStackTargetHandle, PMBUSA_BASE,
                          &pmbusTargetBuffer[0]);

    //
    // Configure the PMBUS module clock to be PMBUS_MODULE_FREQ_MAX
    //
   // moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
   //                                      PMBUS_SYS_FREQ_MAX);

    //
    // Configure the PMBUS bus clock
    ///
    //PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD, moduleFreq);

    //
    // Loop until tests complete
    //
    while(testsCompleted != NENABLEDTESTS)
    {
        if(fail > 0U)
        {
            //
            // Upon fail, halt debugger
            //
            __asm(" ESTOP0");
        }
    };

    //
    // Tests complete - Enter wait loop
    //
    done();

    //
    // Code does not reach this point
    //
    return(1);
}

//
// pmbusIntHandler - This is the main PMBus interrupt handler. Calls target
//                   stack state machine.
//
__interrupt void pmbusIntHandler(void)
{
    //
    // Call the library State Machine handler
    //
    PMBusStack_targetStateHandler(pmbusStackTargetHandle);

    //
    // ACK any pending interrupts (if any got set)
    //
    Interrupt_clearACKGroup(PMBUS_INT_ACK);
}
void PMBusStack_defaultErrorHandler(void)
{
    // User must rewrite this to handle error
    for(;;);
}
//
// End of File
//
