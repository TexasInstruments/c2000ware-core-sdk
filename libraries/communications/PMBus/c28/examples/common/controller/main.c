//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS Controller Demo Code
//
// Note: Requires connection to PMBus target running target demo
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
#include "pmbus_controller_test.h"
#include "board.h"
//
// Defines
//
#define ZERO_BYTES               0U
#define FOUR_BYTES               4U
#define PMBSTS_EOM_S             5U
#define PMBSTS_NACK_S            6U
#define PMBSTS_DATAREQUEST_S     4U
#define PMBSTS_PEC_VALID_S       7U
#define PMBSTS_ALERT_EDGE_S      16U
#define PMBSTS_CLK_LOW_TIMEOUT_S 8U

//
// Globals
//
PMBus_StackObject pmbusStackController;
PMBus_StackHandle pmbusStackControllerHandle = &pmbusStackController;
uint16_t pmbusControllerBuffer[256];

volatile bool targetAckReceived = false;
volatile bool controllerDataAvailable = false;
volatile bool controllerDataRequested = false;
volatile bool receivedPecValid = false;
volatile bool endOfMessage = false;
volatile bool alertEdgeAsserted = false;
volatile bool clockLowTimeout = false;
volatile uint16_t bytesReceived = ZERO_BYTES;
volatile uint32_t pmbusStatus = 0UL;
volatile int16_t pass = 0U, fail = 0U;

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
    uint16_t i, counter;
    uint32_t moduleFreq = 0U;
    PMBusStack_errorHandler = PMBusStack_defaultErrorHandler;
#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBusExample_setupFlash();
#endif // _FLASH

    //
    // Setup the system clocking
    //
    PMBusExample_setupSysCtrl();

    //
    // Enable the PMBUS GPIOs
    //
    //PMBusExample_setupGPIO();

    //
    // Setup the interrupt tables, register PMBUS interrupt handler
    //
    PMBusExample_setupInterrupts(pmbusIntHandler);

    //
    // Board initialization
    //
    Board_init();

    //
    // Setup the PMBUS Library Stack Object
    //
    PMBusStackObject_setMode(pmbusStackControllerHandle, PMBUS_STACK_MODE_CONTROLLER);
    PMBusStack_initModule(pmbusStackControllerHandle, PMBUSA_BASE,
                          &pmbusControllerBuffer[0]);

    //
    // Configure the PMBUS module clock to be less than PMBUS_MODULE_FREQ_MAX
    //
    //moduleFreq = PMBus_configModuleClock(PMBUSA_BASE, PMBUS_MODULE_FREQ_MAX,
    //                                     PMBUS_SYS_FREQ_MAX);

    //
    // Configure the PMBUS bus clock
    //
    //PMBus_configBusClock(PMBUSA_BASE, PMBUS_CLOCKMODE_STANDARD, moduleFreq);

    //
    // Call each test sequentially and check the outputs
    //
    for(i = 0; i < NTESTS; i++)
    {
        //
        // Clear the buffer
        // Set the buffer to some default non-zero value
        //
        memset(pmbusControllerBuffer, 0xBAADU, sizeof(pmbusControllerBuffer));

        handle = &PMBUS_TESTS[i];
        handle->init = (void (*)(void *))initTestList[i];
        handle->run = (void (*)(void *))runTestList[i];

        if(handle->init != NULL)
        {
            handle->init(handle);
        }

        //
        // Reset pass, fail statuses
        //
        handle->pass = 0;
        handle->fail = 0;

        //
        // Run test when enabled
        //
        if(handle->enabled == true)
        {
            //
            // Run test
            //
            handle->run(handle);

            //
            // Wait some time to allow the target to complete processing the
            // transaction before proceeding
            //
            for(counter = 0U; counter < 1000U; counter++)
            {
            }

            //
            // Tally the pass/fail metrics
            //
            pass += handle->pass;
            fail += handle->fail;

            //
            // Halt debugger if test failed
            //
            if(handle->fail > 0U)
            {
                __asm(" ESTOP0");
            }
        }
        //
        // Test is disabled
        //
        else
        {
            handle->pass = -1;
            handle->fail = -1;
        }
    }

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
// pmbusIntHandler - This is the main PMBus interrupt handler. Read out the data
//                   from the PMBus module status register and acknowledge the
//                   interrupt.
//
__interrupt void pmbusIntHandler(void)
{
    //
    // Read the PMBus module status register
    //
    pmbusStatus = PMBus_getStatus(PMBUSA_BASE);

    //
    // Write to the PMBUS_STACK object
    //
    PMBusStackObject_setModuleStatus(pmbusStackControllerHandle, pmbusStatus);

    //
    // Read out individual status information into global variables
    //
    bytesReceived = (pmbusStatus & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
                    PMBUS_PMBSTS_RD_BYTE_COUNT_S;
    endOfMessage = (bool)((pmbusStatus & PMBUS_PMBSTS_EOM) >> PMBSTS_EOM_S);
    targetAckReceived = (bool)((~pmbusStatus & PMBUS_PMBSTS_NACK) >>
                              PMBSTS_NACK_S);
    controllerDataRequested = (bool)((pmbusStatus & PMBUS_PMBSTS_DATA_REQUEST) >>
                                 PMBSTS_DATAREQUEST_S);
    receivedPecValid = (bool)((pmbusStatus & PMBUS_PMBSTS_PEC_VALID) >>
                              PMBSTS_PEC_VALID_S);
    alertEdgeAsserted = (bool)((pmbusStatus & PMBUS_PMBSTS_ALERT_EDGE) >>
                               PMBSTS_ALERT_EDGE_S);
    clockLowTimeout = (bool)((pmbusStatus & PMBUS_PMBSTS_CLK_LOW_TIMEOUT) >>
                             PMBSTS_CLK_LOW_TIMEOUT_S);

    //
    // Check if data is available for controller
    // (Bytes of data received isn't zero or is equal to 4 bytes with
    //  data ready status set)
    //
    if((bytesReceived != ZERO_BYTES) ||
       ((bytesReceived == FOUR_BYTES) &&
        ((pmbusStatus & PMBUS_PMBSTS_DATA_READY) != 0U)))
    {
        controllerDataAvailable = true;
    }

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
