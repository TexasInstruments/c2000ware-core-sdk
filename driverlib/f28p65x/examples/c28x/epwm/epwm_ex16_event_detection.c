//#############################################################################
//
// FILE:   epwm_ex16_event_detection.c
//
// TITLE:  ePWM Monitoring for Event Detection
// 
//! \addtogroup driver_example_list
//! <h1>ePWM Event Detection</h1> 
//!
//! (Note - base frequency and duty cycle of all ePWM's are 50 KHz and 50%
//!  respectively. Value of TBPRD = 1999)
//! This example configures ePWM1 and ePWM2 in identical fashion
//! with XCMP1-8 allocated to channel A. No shadow registers are used.
//!  - XCMP1 = 250, XMP2 = 500, XCMP3 = 750 ..... XCMP 8 = 1750.
//!  - In ePWM1, XMIN = 300 and XMAX = 400. 
//!      - This window has no edge and generates a CAPEVT pulse every period.
//!  - In ePWM2, XMIN = 300 and XMAX = 600. 
//!      - This window has an edge and doesn't generate CAPEVT pulse signal.
//!
//!  \b External \b Connections \n
//!  - ePWM1A is on GPIO0
//!  - ePWM2A is on GPIO2
//!  - ePWM1 Tripout is on GPIO24
//!  - ePWM2 Tripout is on GPIO25
//!  - LED1 is on GPIO31    (For control card)
//!  - LED2 is on GPIO34    (For control card)
//!
//! CAPIN and CAPGATE signals are both sourced as
//! Trip4 for ePWM1 and Trip5 for ePWM2.
//! Trip4 and Trip5 are routed from the INPUT X-BAR through EPWM-XBAR
//! which feeds into the Digital Compare submodule.
//! CAPEVT signal is used as Tripout and Trip-Zone interrupt source.
//!
//! For ePWM1, Trip-Zone ISR configured to make LED1 blink 1 second on/off.
//! For ePWM2, Trip-Zone ISR configured to make LED2 turn on
//! if an interrupt ever occurs.
//!
//
//             _____________              ______________            
//             |           |              |            |
//  GPIO0 -----| I/P X-BAR |----INPUT1----| EPWM X-BAR |
//             |___________|              |____________|
//                                              |
//                                              |
//                                            TRIP4
//                                              |
//                                      ________|_________
//                                      |                |    
//                                      | ePWM DC module |----ePWM1 Tripout
//                                      |________________|       (GPIO24)
// 
//             _____________              ______________            
//             |           |              |            |
//  GPIO1 -----| I/P X-BAR |----INPUT2----| EPWM X-BAR |
//             |___________|              |____________|
//                                              |
//                                              |
//                                            TRIP5
//                                              |
//                                      ________|_________
//                                      |                |    
//                                      | ePWM DC module |----ePWM1 Tripout
//                                      |________________|       (GPIO25)
// 
// 
// 
//#############################################################################
//
//
// $Copyright:
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

//
// Globals
//
uint32_t tz_Int_Count=0U;

//
// Function Prototypes
//
__interrupt void epwm1_TZ_ISR(void);
__interrupt void epwm2_TZ_ISR(void);

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Configuring GPIO for LED and turning them off initially.
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1U);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1U);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // 
    // Set EPWM Clock Divider to 1 to feed 200 MHz SysClock. 
    // Note: Default value is 2.
    // 
    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {

    }
}

__interrupt void epwm1_TZ_ISR(void)
{   
    tz_Int_Count++;
    if (tz_Int_Count == 50000U) 
    {
        //
        // Toggle LED
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
        tz_Int_Count = 0U;
    }

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
    EPWM_clearTripZoneFlag(myEPWM1_BASE,EPWM_TZ_FLAG_CAPEVT);
    EPWM_clearTripZoneFlag(myEPWM1_BASE,EPWM_TZ_INTERRUPT);

}

__interrupt void epwm2_TZ_ISR(void)
{
    //
    // Turn on LED
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0U);

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
    EPWM_clearTripZoneFlag(myEPWM2_BASE,EPWM_TZ_FLAG_CAPEVT);
    EPWM_clearTripZoneFlag(myEPWM2_BASE,EPWM_TZ_INTERRUPT);
}

//
// End of File
//
