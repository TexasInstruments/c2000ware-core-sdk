//###########################################################################
//
// FILE:   main.c
//
// TITLE:  PMBUS over I2C Controller Demo Code
//
// Note: Requires connection to PMBus target running PMBus over I2C target demo
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
#include "pmbus_over_i2c_controller_test.h"

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
uint16_t pmbusCRCBuffer[5];
uint16_t pmbusCRCMsgSize =0;

volatile bool targetAckReceived = false;
volatile bool controllerDataAvailable = false;
volatile bool controllerDataRequested = false;
volatile bool receivedPecValid = false;
volatile bool endOfMessage = false;
volatile bool alertEdgeAsserted = false;
volatile bool clockLowTimeout = false;
volatile bool intFlag = false;
volatile uint16_t bytesReceived = ZERO_BYTES;
volatile uint32_t busStatus = 0UL;
volatile int16_t pass = 0U, fail = 0U;
volatile bool allBytesReceived = false;
//
// Function Prototypes
//
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc")
#else
#pragma CODE_SECTION(PMBus_over_I2C_IntHandler, ".TI.ramfunc")
#pragma CODE_SECTION(PMBusoverI2CFIFOIntHandler, ".TI.ramfunc")
#endif // __cplusplus
__interrupt void PMBus_over_I2C_IntHandler(void);
__interrupt void PMBusoverI2CFIFOIntHandler(void);

//
// Main
//
int main(void)
{
    //
    // Locals
    //
    uint16_t i, counter;

#if defined(_FLASH)
    //
    // Setup the Flash banks
    //
    PMBus_over_I2C_Example_setupFlash();
#endif // _FLASH

    //
    // Setup the system clocking
    //
    PMBus_over_I2C_Example_setupSysCtrl();

    //
    // Enable the PMBUS GPIOs
    //
    PMBus_over_I2C_Example_setupGPIO();

    //
    // Setup the interrupt tables, register PMBUS interrupt handler
    //
    PMBus_over_I2C_Example_setupInterrupts_Controller(PMBus_over_I2C_IntHandler);

    //
    // Setup the PMBUS Library Stack Object
    //
    PMBusStackObject_setMode(pmbusStackControllerHandle, PMBUS_STACK_MODE_CONTROLLER);
    PMBusStackObject_setTargetAddress(pmbusStackControllerHandle, TARGET_ADDRESS);
    PMBusStack_initModule(pmbusStackControllerHandle, I2CA_BASE,
                          &pmbusControllerBuffer[0], &pmbusCRCBuffer[0]);

     //
     // I2C configuration. Use a 400kHz I2CCLK with a 50% duty cycle.
     //
     I2C_initController(I2CA_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);


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
__interrupt void PMBus_over_I2C_IntHandler(void)
{
    //
    // Read the PMBus module status register
    //
    busStatus = I2C_getStatus(I2CA_BASE);

    //
    // Write to the PMBUS_STACK object
    //
    PMBusStackObject_setModuleStatus(pmbusStackControllerHandle, busStatus);


    //
    // Read out individual status information into global variables
    //
    //bytesReceived = (busStatus & PMBUS_PMBSTS_RD_BYTE_COUNT_M) >>
    //                PMBUS_PMBSTS_RD_BYTE_COUNT_S;

    bytesReceived = I2C_getRxFIFOStatus(I2CA_BASE);

    //endOfMessage = (bool)((busStatus & PMBUS_PMBSTS_EOM) >> PMBSTS_EOM_S);

    endOfMessage = (bool)(busStatus & I2C_STS_STOP_CONDITION);

    intFlag = (bool)(busStatus & I2C_STS_REG_ACCESS_RDY);

    if(endOfMessage == true)
    {
        I2C_clearStatus(I2CA_BASE, I2C_STS_STOP_CONDITION);
        I2C_clearInterruptStatus(I2CA_BASE, I2C_STS_STOP_CONDITION );
    }

    targetAckReceived = ~(bool)((busStatus & I2C_STS_NACK_SENT));

   // controllerDataRequested = (bool)((busStatus & PMBUS_PMBSTS_DATA_REQUEST) >>
   //                              PMBSTS_DATAREQUEST_S);
  //  receivedPecValid = (bool)((busStatus & PMBUS_PMBSTS_PEC_VALID) >>
  //                            PMBSTS_PEC_VALID_S);
  //  alertEdgeAsserted = (bool)((busStatus & PMBUS_PMBSTS_ALERT_EDGE) >>
  //                             PMBSTS_ALERT_EDGE_S);
  //  clockLowTimeout = (bool)((busStatus & PMBUS_PMBSTS_CLK_LOW_TIMEOUT) >>
  //                           PMBSTS_CLK_LOW_TIMEOUT_S);

    //
    // Check if data is available for controller
    // (Bytes of data received isn't zero or is equal to 4 bytes with
    //  data ready status set)
    //
    if((bytesReceived != ZERO_BYTES) ||
       ((bytesReceived == FOUR_BYTES) &&
        ((busStatus & I2C_STS_RX_DATA_RDY) != 0U)))
    {
        controllerDataAvailable = true;
    }

    //
    // ACK any pending interrupts (if any got set)
    //
    Interrupt_clearACKGroup(I2C_INT_ACK);
}

__interrupt void PMBusoverI2CFIFOIntHandler(void)
{

    //PMBus_StackHandle handle = pmbusStackTargetHandle;
    uint32_t base = PMBusStackObject_getModuleBase(pmbusStackControllerHandle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(pmbusStackControllerHandle);
    static uint16_t nBytes = 0U;
    static uint16_t TotalBytesToReceive=0U;

     static bool first_time = true;

    if(first_time)
    {
        nBytes += PMBus_over_I2C_getTargetData(base, buffer) -1; //remove the data count byte
        TotalBytesToReceive = buffer[0]; //first byte is the data count
        first_time = false;
    }
    else
    {
        while(allBytesReceived==false)
        {
            nBytes += PMBus_over_I2C_getTargetData(base, buffer);
            if (nBytes == TotalBytesToReceive)
            {
                allBytesReceived = true;
            }
        }

    }
    PMBusStackObject_setCurrentPositionPointer(pmbusStackControllerHandle, &buffer[nBytes]);
    I2C_clearInterruptStatus(base,I2C_INT_RXFF);
    Interrupt_clearACKGroup(I2C_INT_ACK);

}
//
// End of File
//
