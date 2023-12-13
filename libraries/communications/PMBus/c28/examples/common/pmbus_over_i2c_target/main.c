//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS over I2C Target Demo Code
//
// Note: Requires connection to I2C controller running PMBus over I2C controller demo
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
#include "pmbus_over_i2c_target_test.h"

#include <string.h>

//
// Globals
//
PMBus_StackObject pmbusStackTarget;
PMBus_StackHandle pmbusStackTargetHandle = &pmbusStackTarget;
uint16_t pmbusTargetBuffer[300U];
uint16_t pmbusCRCBuffer[5];
volatile uint16_t testsCompleted = 0U;
volatile uint16_t pass = 0U, fail = 0U;

//
// Function Prototypes
//
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc")
#else
#pragma CODE_SECTION(PMBusoverI2CIntHandler, ".TI.ramfunc")
#pragma CODE_SECTION(PMBusoverI2CFIFOIntHandler, ".TI.ramfunc")
#endif // __cplusplus
__interrupt void PMBusoverI2CIntHandler(void);
__interrupt void PMBusoverI2CFIFOIntHandler(void);
__interrupt void TimerISR(void);

//
// Main
//
int main(void)
{
    //
    // Locals
    //
    uint16_t i;
    volatile uint32_t test = 0x0UL;

#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBus_over_I2C_Example_setupFlash();
#endif //defined(_FLASH)

    //
    // Setup the system clocking
    //
    PMBus_over_I2C_Example_setupSysCtrl();

    //
    // Enable the I2C GPIOs
    //
    PMBus_over_I2C_Example_setupGPIO();

    //
    // Setup the interrupt tables, register PMBus_over_I2C interrupt handler
    //
    PMBus_over_I2C_Example_setupInterrupts(PMBusoverI2CIntHandler,PMBusoverI2CFIFOIntHandler);

#ifdef TIMEOUT
    Interrupt_register(INT_TIMER0, &TimerISR); //change the interrupt line based on Timer base
    CPUTimer_enableInterrupt(TIMERBASE);
    Interrupt_enable(INT_TIMER0);
#endif
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
                                           PMBUS_TRANSACTION_QUICKCOMMAND,
                              (void (*)(void *))PMBusTarget_quickCommandTestHandler);

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

    // Overwrite the Block write transaction handler
        //
        PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                               PMBUS_TRANSACTION_BLOCKWRITE,
                                  (void (*)(void *))PMBusTarget_blockWriteTestHandler);

        PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                               PMBUS_TRANSACTION_BLOCKWRPC,
                                  (void (*)(void *))PMBusTarget_processCallTestHandler);

        PMBusStackObject_setTransactionHandler(pmbusStackTargetHandle,
                                               PMBUS_TRANSACTION_BLOCKREAD,
                                  (void (*)(void *))PMBusTarget_blockReadTestHandler);
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
#ifdef TIMEOUT
    PMBusStackObject_setTimerBase(pmbusStackTargetHandle, TIMERBASE);
    PMBusStackObject_setTimeout(pmbusStackTargetHandle, TIMEOUT_VALUE);
#endif

    PMBusStackObject_setTargetAddressMask(pmbusStackTargetHandle,
                                         TARGET_ADDRESSMASK);

    //I2C_initController(I2CA_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);

    //
    // Initialize the state machine handler
    //
    PMBusStack_initModule(pmbusStackTargetHandle, I2CA_BASE,
                          &pmbusTargetBuffer[0],&pmbusCRCBuffer[0]);


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
__interrupt void PMBusoverI2CIntHandler(void)
{
    //
    // Call the library State Machine handler
    //

    PMBusStack_targetStateHandler(pmbusStackTargetHandle);
    //
    // ACK any pending interrupts (if any got set)
    //
    Interrupt_clearACKGroup(I2C_INT_ACK);
}

__interrupt void PMBusoverI2CFIFOIntHandler(void)
{

    PMBusStack_targetRxFIFOHandler(pmbusStackTargetHandle);

    Interrupt_clearACKGroup(I2C_INT_ACK);

}

#ifdef TIMEOUT
__interrupt void TimerISR(void)
{
    PMBusStack_targetTimeoutHandler(pmbusStackTargetHandle);

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(TIMER_INT_ACK);
}
#endif
//
// End of File
//
