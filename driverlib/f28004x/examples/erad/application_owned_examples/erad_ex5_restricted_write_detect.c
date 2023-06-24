//#############################################################################
//!
//! FILE:   erad_ex5_restricted_write_detect.c
//!
//! TITLE:  erad_ex5_restrictedwrite_detect
//!
//! \addtogroup driver_example_list
//! <h1>ERAD MEMORY ACCESS RESTRICT</h1>
//!
//!  This example uses BUSCOMP1 to monitor the Data Write Address Bus.
//!  It monitors the bus and generates an RTOS interrupt if a certain
//!  region of memory is accessed by the PC. The user may disable the Bus
//!  Comparator to access that region.
//!
//!  Use the COM port (Baud=9600) to try to write to the restricted area.
//!
//!  \b Watch \b Variables \n
//!  - x : stores the number of times the region of memory is accessed
//!
//! \b External \b Connections \n
//!  - None
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include <string.h>
#include <stdlib.h>

//
// Variable to detect if the restricted region was accessed
//
uint32_t x = 0, y=0;

//
// Function Prototypes
//

//
// This is the function stored in the memory region under
// consideration
//
void try_func(void);

//
// Initialising SCI
//
void initSCI(void);

//
// Configuring the ERAD module
//
void configERAD(void);

//
// ISR to be executed on RTOS generation
//
interrupt void RTOSISR(void);

//
// Main
//
void main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // ISRs for each RTOS interrupt
    //
    Interrupt_register(INT_RTOS, &RTOSISR);
    Interrupt_enableInCPU(INTERRUPT_CPU_RTOSINT);

    //
    // Enable RTOS Interrupt
    //
    Interrupt_enable(INT_RTOS);

    //
    // Initialise SCI for interaction with user
    //
    initSCI();

    //
    // Configure the ERAD module as required
    //
    configERAD();

    EINT;
    ERTM;

    //
    // SCI COM port interface
    //
    uint16_t receivedChar;
    char val;
    char *msg, *msg_x, *msg_g;
    msg   = "\r\nHi!\0";
    msg_x = "\r\nValue of x = \0";
    msg_g = "\r\nAccess given.\0";

    ltoa(x, &val, 10);

    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, strlen(msg));
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg_x, strlen(msg_x));
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)(&val), 1);

    msg = "\r\nPress a to try to access the restricted region, g to get access or d to disable access:\0";

    while(x < 5)
    {
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, strlen(msg));
        receivedChar = SCI_readCharBlockingFIFO(SCIA_BASE);

        //
        // User enters 'a' to access the restricted region, i.e. try_func
        //
        if(receivedChar == 'a')
        {
            try_func();
        }

        //
        // User enters 'd' to enable the bus comparator. An interrupt is
        // generated when the restriction region is accessed.
        //
        else if(receivedChar == 'd')
        {
            ERAD_enableModules(ERAD_INST_BUSCOMP1);
        }

        //
       // User enters 'd' to enable the bus comparator. No interrupt is
        // generated when the restriction region is accessed.
        //
        else if(receivedChar == 'g')
        {
            SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg_g, strlen(msg_g));
            ERAD_disableModules(ERAD_INST_BUSCOMP1);
        }

        //
        // Value of x denotes how many times try_func was accessed
        //
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg_x, strlen(msg_x));
        ltoa(x, &val,10);
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)(&val), 1);
    }
    //
    // Loop exits after x becomes 5
    //
    msg = "\r\nGuess you've played enough.Bye!\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, strlen(msg));

    ESTOP0;
    while(1);
}

void
initSCI(void)
{
    //
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Configure SCIA for echoback.
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);

    #ifdef AUTOBAUD
    //
    // Perform an autobaud lock.
    // SCI expects an 'a' or 'A' to lock the baud rate.
    //
    SCI_lockAutobaud(SCIA_BASE);
    #endif

}

void
configERAD(void)
{
    //
    // Initialise the ERAD module with the APPLICATION as owner
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Configuring the bus comparator to generate an RTOS interrupt
    // if the restricted region is accessed
    //
    ERAD_BusComp_Config buscomp_config;
    buscomp_config.bus_sel     = ERAD_BUSCOMP_BUS_VPC;
    buscomp_config.reference   = (uint32_t)&try_func;
    buscomp_config.mask        = 0x0;
    buscomp_config.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_config.enable_int  = 1;
    buscomp_config.enable_stop = 0;
    ERAD_configBusComp(ERAD_HWBP1_BASE, buscomp_config);

    //
    // Enabling the bus comparator
    //
    ERAD_enableModules(ERAD_INST_BUSCOMP1);
}

//
// ISR to be executed if bus comparator generates RTOS interrupt
//
interrupt void
RTOSISR(void)
{
    char *msg;
    msg = "\r\nEntering restricted region without getting access.\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, strlen(msg));
    y += 1;
}

//
// This is the code stored in the restricted region
// The linker command file specifies where it is to be stored in memory
//
#pragma CODE_SECTION(try_func, ".try_sect")
void
try_func(void)
{
    char *msg;
    msg = "\r\nEntered restricted region \0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, strlen(msg));
    //
    // Increment x to show that this code has executed.
    //
    x+=1;
}

//
// End of File
//
