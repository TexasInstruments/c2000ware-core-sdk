///#############################################################################
//!
//! FILE:   erad_ex6_interrupt_order.c
//!
//! TITLE:  ERAD INTERRUPT ORDER
//!
//! \addtogroup driver_example_list
//! <h1>ERAD INTERRUPT ORDER</h1>
//!
//!  This example uses a COUNTER to monitor the sequence of ISRs executed. An
//!  interrupt is generated if the ISRs executed are not in the expected order.
//!  The expected order is CPUTimer0 ,then CPUTimer1 and then CPUTimer2
//!
//!  The counter is configured in Start-Stop Mode to count the number of times
//!  CPUTimer interrupt occurs between the CPUTimer1 interrupt and CPUTimer2
//!  ISRs. Ideally, this count should be zero if the interrupts are occurring
//!  in the expected order. we configure a threshold value of 1 to genarete an
//!  RTOS interrupt. This indicates that the CPUTimer2 interrupt has come out
//!  of order.
//!
//!  For demonstaration puproses, this example disables CPUTimer1 to simulate
//!  this error.
//!
//!  \b Watch \b Variables \n
//!  - cpuTimer0IntCount: Number of executions of ISR0
//!  - cpuTimer1IntCount: Number of executions of ISR1
//!  - cpuTimer2IntCount: Number of executions of ISR2
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

//
// Globals
//
uint64_t cpuTimer0IntCount;
uint64_t cpuTimer1IntCount;
uint64_t cpuTimer2IntCount;

//
// Function Prototypes
//
interrupt void cpuTimer0ISR(void);
interrupt void cpuTimer1ISR(void);
interrupt void cpuTimer2ISR(void);
interrupt void RTOSISR(void);
void initCPUTimers(void);
void configERAD(void);
void configCPUTimer(uint32_t, float, float);

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
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2,1);

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
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);
    Interrupt_register(INT_TIMER2, &cpuTimer2ISR);
    Interrupt_register(INT_RTOS, &RTOSISR);
    Interrupt_enableInCPU(INTERRUPT_CPU_RTOSINT);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every 1000 cycles
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 10);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 10);
    configCPUTimer(CPUTIMER2_BASE, DEVICE_SYSCLK_FREQ, 10);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_TIMER1);
    Interrupt_enable(INT_TIMER2);
    Interrupt_enable(INT_RTOS);

    configERAD();

    ERAD_enableModules(ERAD_INST_BUSCOMP1 |
                       ERAD_INST_BUSCOMP2 |
                       ERAD_INST_COUNTER1);
    //
    // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER1_BASE);
    CPUTimer_startTimer(CPUTIMER2_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop for sometime
    //
    int i;
    for(i = 0; i < 500; i++)
    {
        NOP;
    }

    //
    // Now stop CPU - Timer 1. The ERAD will detect that the order of occurrence
    // of interrupts is not maintained and generate an interrupt.
    //
    CPUTimer_stopTimer(CPUTIMER1_BASE);

    while(1);
}

//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void
initCPUTimers(void)
{
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);
    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

//
// Configure the ERAD
//
void
configERAD(void)
{
    ERAD_BusComp_Config buscomp_params;
    ERAD_Counter_Config counter_params;

    //
    // Initialises the module with the APPLICATION as the owner
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Configuring the bus comparators
    // First one is set to monitor the execution of cpuTimer0ISR
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_VPC;
    buscomp_params.reference   = (uint32_t)&cpuTimer0ISR;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_int  = 0;
    buscomp_params.enable_stop = 0;
    ERAD_configBusComp(ERAD_HWBP1_BASE, buscomp_params);

    //
    // Second one is set to monitor the execution of cpuTimer1ISR
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_VPC;
    buscomp_params.reference   = (uint32_t)&cpuTimer1ISR;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_int  = 0;
    buscomp_params.enable_stop = 0;
    ERAD_configBusComp(ERAD_HWBP2_BASE, buscomp_params);

    //
    // Counter is set to monitor the number of interrupts from the 3rd
    // Timer fired between the other 2 interrupts. Generates a RTOS as
    // soon as even one fires
    //
    counter_params.event        = ERAD_EVENT_TIMER2_TINT2;
    counter_params.event_mode   = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.reference    = 0x1;
    counter_params.rst_on_match = 0;
    counter_params.enable_int   = 1;
    counter_params.enable_stop  = 0;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER1_BASE, counter_params,
                                      ERAD_EVENT_HWBP1, ERAD_EVENT_HWBP2);
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "Freq" and "Period" parameters. The "Freq" is
// entered as "Hz" and the period in "uSeconds". The timer is held in the
// stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t) (freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
interrupt void
cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    //ESTOP0;
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
interrupt void
cpuTimer1ISR(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer1IntCount++;

    //ESTOP0;
}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
interrupt void
cpuTimer2ISR(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer2IntCount++;

    //ESTOP0;
}

//
// Interrupt is raised if CPUTimer1 occurs before CPUTimer2 and after
// CPUTimer0
//
interrupt void
RTOSISR(void)
{
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
    ERAD_setCurrentCount(ERAD_COUNTER1_BASE, 0);
    ESTOP0;
}

//
// End of file
//
