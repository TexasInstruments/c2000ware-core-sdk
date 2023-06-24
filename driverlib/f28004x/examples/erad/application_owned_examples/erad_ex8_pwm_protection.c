//#############################################################################
//
// FILE:   erad_ex8_pwm_protection.c
//
// TITLE:  ERAD PWM PROTECTION.
//
//! \addtogroup driver_example_list
//! <h1>ERAD PWM PROTECTION</h1>
//!
//!  This example uses a BUS COMPARATOR and the CLB to detect the event when
//!  the delay between the interrupt and the ISR execution is longer than
//!  expected. The PWM output is also tripped in this case.
//!
//!  \b Watch \b Variables \n
//!  - adcAResults stores the results of the conversions from the ADC
//!
//! \b External \b Connections \n
//!  - Monitor the PWM output (GPIO0)
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
// Macros for configuring the CLB
//
#define RESULTS_BUFFER_SIZE 256

//
// Function prototypes
//
void config_XBar();
void config_CLB();
__interrupt void clb1ISR();
void initADC(void);
void initEPWM(void);
void initADCSOC(void);
__interrupt void adcA1ISR(void);
__interrupt void epwm1TZISR(void);

//
// global variables
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];   // Buffer for results
uint16_t index;                              // Index into result buffer
volatile uint16_t bufferFull;                // Flag to indicate buffer is full
uint16_t epwm1TZIntCount = 0;                // Variable to indicate that trip interrupt executed

void *addr_adcA1ISR = (void *)&adcA1ISR;

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
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ADCA1, &adcA1ISR);
    Interrupt_register(INT_EPWM1_TZ, &epwm1TZISR);

    //
    // Board initialization
    //
    Board_init();

    //
    // Set up the ADC and the ePWM and initialize the SOC
    //
    initADC();
    initEPWM();
    initADCSOC();

    //
    // Configure the modules
    //
    config_XBar();
    config_CLB();

    //
    // Initialize results buffer
    //
    for(index = 0; index < RESULTS_BUFFER_SIZE; index++)
    {
        adcAResults[index] = 0;
    }

    index = 0;
    bufferFull = 0;

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);
    Interrupt_enable(INT_EPWM1_TZ);

    CLB_clearInterruptTag(CLB1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    ESTOP0;
    int i = 0;
    //
    // Loop indefinitely
    //
    for(;i<3;i++)
    {
        //
        // Start ePWM1, enabling SOCA and putting the counter in up-count mode
        //
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

        //
        // Wait while ePWM1 causes ADC conversions which then cause interrupts.
        // When the results buffer is filled, the bufferFull flag will be set.
        //
        while(bufferFull == 0)
        {
        }
        bufferFull = 0;     // Clear the buffer full flag

        //
        // Stop ePWM1, disabling SOCA and freezing the counter
        //
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        //
        // Software breakpoint. At this point, conversion results are stored in
        // adcAResults.
        //
        // Hit run again to get updated conversions.
        //
        ESTOP0;
    }
    //
    // Disable the interrupt from the ADC to simulate a longer time between
    // interrupt generation and the ISR execution
    //
    Interrupt_disable(INT_ADCA1);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    while(1)
    {
    }
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);
}

//
// initEPWM - Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 2048 and the period to 4096
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0x0800);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 0x1000);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

    //
    // Enable and select trip input4 to the DCAL output
    //
    EPWM_enableDigitalCompareTripCombinationInput(EPWM1_BASE, EPWM_DC_COMBINATIONAL_TRIPIN4,  EPWM_DC_TYPE_DCAL);
    EPWM_selectDigitalCompareTripInput(EPWM1_BASE,  EPWM_DC_TRIP_COMBINATION, EPWM_DC_TYPE_DCAL);

    //
    // Set event condition as DCAL going high
    //
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXL_HIGH);

    //
    // No filter required
    //
    EPWM_setDigitalCompareEventSource(EPWM1_BASE, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // Make the PWM go low on trip
    //
    EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_LOW);

    //
    // Enable interrupt as well on trip
    //
    EPWM_enableTripZoneInterrupt(EPWM1_BASE, EPWM_TZ_INTERRUPT_DCAEVT1);

    //
    // Enable the trip zone signal as DCAEVT1
    //
    EPWM_enableTripZoneSignals(EPWM1_BASE, EPWM_TZ_SIGNAL_OSHT6);

    //
    // Monitor GPIO0 to see the PWM
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);

}

//
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by ePWM1.
//
void initADCSOC(void)
{
    //
    // Configure SOC0 of ADCA to convert pin A0 with a sample window of 10
    // SYSCLK cycles. The EPWM1SOCA signal will be the trigger.
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, 10);

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
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
    // Select the Comparator A in the EPWM 1 module for CLB1, IN0
    // Select ERAD Bus comparator 2 for CLB1, IN1
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM1_CTR_CMPA);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_ERAD_EVENT0);

    //
    // Unused Inputs below
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1A);
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

    CLB_selectInputFilter(CLB1_BASE, CLB_IN0, CLB_FILTER_RISING_EDGE);
    CLB_selectInputFilter(CLB1_BASE, CLB_IN1, CLB_FILTER_RISING_EDGE);

    //
    // Unused inputs to GP register
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN2, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN3, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    //
    // Configure OUTPUT-XBAR OUTPUT1 as CLB1_OUT5
    //
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX03_CLB1_OUT5);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX03);

    //
    // Routes the output of the CLB to the EPWM module
    // through the EPWM X-Bar
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX01_CLB1_OUT4);
    XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX01);

    CLB_setGPREG(CLB1_BASE, 0);
    CLB_setOutputMask(CLB1_BASE, CLB_OUTPUT_04|CLB_OUTPUT_05, true);
}

//
// Configures the Output X-bar and GPIOs to show output on LEDs
//
void
config_XBar()
{
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);

    //
    // Routes the output from the Output X-Bar to LED2
    // LED2 will turn on
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(GPIO_34_OUTPUTXBAR1);
}


//
// epwm1TZISR - ePWM1 TZ ISR
//
__interrupt void epwm1TZISR(void)
{
    epwm1TZIntCount++;

    //
    // Makes LED1 glow
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);

    //
    // To re-enable the OST Interrupt, uncomment the below code:
    //
    // EPWM_clearTripZoneFlag(EPWM1_BASE,
    //                       (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
    ESTOP0;
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{
    //
    // Add the latest result to the buffer
    //
    adcAResults[index++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= index)
    {
        index = 0;
        bufferFull = 1;
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
