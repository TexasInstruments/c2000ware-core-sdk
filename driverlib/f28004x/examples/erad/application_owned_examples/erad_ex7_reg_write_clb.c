//#############################################################################
//
// FILE:   erad_ex7_reg_write_clb.c
//
// TITLE:  ERAD AND CLB.
//
//! \addtogroup driver_example_list
//! <h1>ERAD AND CLB</h1>
//!
//!  This example uses 4 BUS COMPARATORS of ERAD along with the CLB. One bus
//!  comparator monitors a write to x, another one monitors a write to y. The
//!  other two monitor a write of 0x1 and 0x0. By using the LUTs in the CLB1
//!  tile, we can monitor a write of 0x1 to x or 0x0 to x. These are used to
//!  change the state of FSM2 in the CLB1 tile. If y is accessed before writing
//!  a 0x1 to x, an interrupt is generated and y is changed to 0x0 again.
//!  The LED2 indicates when access to y is allowed(it is off at this point)
//!  The LED1 indicates if an invalid access is attempted.
//!  A COUNTER in ERAD is used to count the number of access attempts to y.
//!
//!  \b Watch \b Variables \n
//!  - y
//!  - x
//!  - a - counts the number of access attempts to y
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
// Included files
//
#include "driverlib.h"
#include "device.h"
#include "clb_config.h"
#include "board.h"

//
// Function prototypes
//
void config_XBar();
void config_CLB();
__interrupt void clb1ISR();

//
// global variables
//
volatile int x = 0, y = 0, a = 0;
void *addr_x = (void *)&x;
void *addr_y = (void *)&y;

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
    // Board initialization
    //
    Board_init();

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
    // ISRs for each CLB interrupt
    //

    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);

    //
    // Configure the modules
    //
    config_XBar();
    config_CLB();

    EINT;
    ERTM;

    CLB_clearInterruptTag(CLB1_BASE);

    ESTOP0;

//    x = 0;

    //
    // First attempt to write into y does not work as x is not 1
    //
    y += 1;
    a = ERAD_getCurrentCount(ERAD_COUNTER1_BASE);
    ESTOP0;

    //
    // x is made 1
    // Now we can write anything to y
    //
    x = 1;
    ESTOP0;
    y += 1;
    a = ERAD_getCurrentCount(ERAD_COUNTER1_BASE);
    ESTOP0;

    //
    // Making x 0 again
    // y cannot be accessed now
    //
    x = 0;
    ESTOP0;
    y += 1;
    a = ERAD_getCurrentCount(ERAD_COUNTER1_BASE);
    ESTOP0;
}

//
// Configures the CLB module
//
void
config_CLB()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    CLB_enableCLB(CLB1_BASE);
    initTILE1(CLB1_BASE);

    //
    // Select Global input instead of local input for all CLB IN
    //
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);


    //
    // Select ERAD Bus comparator 1 for CLB1, IN0
    // Select ERAD Bus comparator 2 for CLB1, IN1
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_ERAD_EVENT0);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_ERAD_EVENT1);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_ERAD_EVENT2);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_ERAD_EVENT3);

    //
    // Unused Inputs below
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM1A);

    //
    // Select External for CLB1, IN0
    // Select External for CLB1, IN1
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);

    CLB_selectInputFilter(CLB1_BASE, CLB_IN0, CLB_FILTER_RISING_EDGE);
    CLB_selectInputFilter(CLB1_BASE, CLB_IN1, CLB_FILTER_RISING_EDGE);
    CLB_selectInputFilter(CLB1_BASE, CLB_IN2, CLB_FILTER_RISING_EDGE);
    CLB_selectInputFilter(CLB1_BASE, CLB_IN3, CLB_FILTER_RISING_EDGE);

    //
    // Unused inputs to GP register
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    //
    // Configure OUTPUT-XBAR OUTPUT1 as CLB1_OUT5
    //
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX03_CLB1_OUT5);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX03);

    CLB_setGPREG(CLB1_BASE, 0);
    CLB_setOutputMask(CLB1_BASE, 1 << 0 | 1 << 2, true);
}

//
// Configures the Output X-bar and GPIOs to show output on LEDs
//
void
config_XBar()
{
    //
    // Turning off LED1
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);

    //
    // Routes the output from the X-Bar to LED2
    // LED2 will turn on
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(GPIO_34_OUTPUTXBAR1);
}

//
// ISR to be executed if there is access to y without writing 1 to x
//
__interrupt void clb1ISR(void)
{
    //
    // Makes LED1 glow when an invalid access is done
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);

    //
    // Clear the interrupt to allow for further interrupts
    //
    CLB_clearInterruptTag(CLB1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);

    //
    // Disable the bus comparator before writing to y so that
    // an interrupt is not generated. Enable it again after
    // finishing the write.
    //
    ERAD_disableModules(ERAD_INST_BUSCOMP4);
    y=0;
    ERAD_enableModules(ERAD_INST_BUSCOMP4);

    //
    // Software breakpoint(optional)so that the LED can be seen turning on.
    // May use delay instead
    //
    DEVICE_DELAY_US(1000000);//    ESTOP0;

    //
    // Turn off the LED
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
}

//
// End of file
//
