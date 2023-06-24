//#############################################################################
//
// FILE:    erad_ex1_profile_interrupt.c
//
// TITLE:   ERAD Profiling Interrupts Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Profiling Interrupts </h1>
//!
//! This example shows how an ISR can be profiled by ERAD. The CPU timer
//! generates interrupts periodically. We set up the counters to count the
//! CPU cycles elapsed while executing the ISR, to count the number of
//! interrupts, the number of ISR executions and the CPU cycles elapsed
//! between the interrupt and the execution of the ISR.
//!
//! This example uses 2 bus comparators and 4 counters:
//!  - BUSCOMP_1 : PC = start address of cpuTimer1ISR
//!  - BUSCOMP_2 : PC = address of cpuTimer1IntCount variable access. This
//!                     specifies the end address of the code of interest.
//!  - COUNTER_1 : Used to count the cpuTimer1ISR execution cycles.
//!                Configured in start-stop mode with start event as BUSCOMP_1
//!                and stop event as BUSCOMP_2
//!  - COUNTER_2 : Used to count the number of times the system event
//!                TIMER1_TINT1 has occurred.
//!                Configured in rising-edge count mode with counting input as
//!                system event TIMER1_TINT1
//!  - COUNTER_3 : Used to count the number of times cputTimer2ISR executes.
//!                Configured in rising-edge count mode with counting input as
//!                BUSCOMP_1
//!  - COUNTER_4 : Used to count the latency from the system event TIMER1_TINT1
//!                to cpuTimer1ISR entry.
//!                Configured in start-stop mode with start event as
//!                TIMER1_TINT1 and stop event as BUSCOMP_1
//!
//!  We configure the COUNTER1 to generate an interrupt once it reaches a
//!  threshold value.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Profiling \b Output
//!  - Current ISR cycle count (COUNTER_1)
//!  - Interrupt occurrence count (COUNTER_2)
//!  - ISR execution count (COUNTER_3)
//!  - ISR entry delay cycle count (maximum value of COUNTER_4)
//!  - x - To show that the ISR executed
//!
//
//##############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Globals
//

//
// Threshold for COUNTER1 to generate interrupt
// Interrupt is invoked if the ISR takes more than 500 cycles to complete
//
const uint16_t threshold = 500;

//
// Variable accessed at the end of the ISR. We are interested in measuring the
// time between the start if ISR to the write to this variable
//
uint64_t cpuTimer1IntCount;

//
// Time taken by ISR to complete
//
uint32_t time_isr = 0;

//
// Number of interrupts generated
//
uint32_t number_of_interrupts = 0;

//
// Number of times the ISR actually gets executed
//
uint32_t number_of_executions = 0;

//
// Time elapsed between the interrupt and the execution of the ISR
//
uint32_t time_bw_int_ex = 0;


//
// Function Prototypes
//
interrupt void cpuTimer1ISR(void) __attribute__((ramfunc));
interrupt void RTOSISR(void) __attribute__((ramfunc));
void initCPUTimers(void);
void configERAD(void);
void configCPUTimer(uint32_t, float, float);

//
// Globals
//

//
// Variable to show RTOS interrupt was invoked
//
bool RTOSintCount = 0;

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
    // ISR for CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);

    //
    // ISRs for RTOS interrupt
    //
    Interrupt_register(INT_RTOS, &RTOSISR);
    Interrupt_enableInCPU(INTERRUPT_CPU_RTOSINT);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timer.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 1 to interrupt every 20000 cycles
    //
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 200);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    //
    // Enables CPU int13 which is connected to CPU-Timer 1
    //
    Interrupt_enable(INT_TIMER1);

    //
    // Configure the ERAD module
    //
    configERAD();

    //
    // Enable the necessary sub-modules in ERAD
    //
    ERAD_enableModules(ERAD_INST_BUSCOMP1 | ERAD_INST_BUSCOMP2 |
                       ERAD_INST_COUNTER1 | ERAD_INST_COUNTER2 |
                       ERAD_INST_COUNTER3 | ERAD_INST_COUNTER4);


    //
    // Starts CPU-Timer 1
    //
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
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
    CPUTimer_stopTimer(CPUTIMER1_BASE);

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer1IntCount = 0;
}

void
configERAD(void)
{
    ERAD_BusComp_Config buscomp_params;
    ERAD_Counter_Config counter_params;

    //
    // Initialise the ERAD module with the APPLICATION as owner
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Configure BUSCOMP1 to generate an event when the ISR begins
    // execution
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_VPC;
    buscomp_params.reference   = (uint32_t)&cpuTimer1ISR;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_stop = 0;
    buscomp_params.enable_int  = 0;
    ERAD_configBusComp(ERAD_HWBP1_BASE, buscomp_params);

    //
    // Configure BUSCOMP2 to generate and event when there is write to
    // cpuTimer1IntCount.
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_DWAB;
    buscomp_params.reference   = (uint32_t)&cpuTimer1IntCount;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_stop = 0;
    buscomp_params.enable_int  = 0;
    ERAD_configBusComp(ERAD_HWBP2_BASE, buscomp_params);

    //
    // Time spent between the start of execution and the write to
    // cpuTimer1IntCount is what is of interest.
    // Configure COUNTER1 to measure CPU cycles elapsed between them
    // (between the BUSCOMP1 event to BUSCOMP2 event)
    //
    counter_params.event        = ERAD_EVENT_NO_EVENT;
    counter_params.event_mode   = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.reference    = threshold;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 1;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER1_BASE, counter_params,
                                      ERAD_EVENT_HWBP1, ERAD_EVENT_HWBP2);

    //
    // Configure COUNTER2 to count the number of interrupts that are raised
    //
    counter_params.event        = ERAD_EVENT_TIMER1_TINT1;
    counter_params.event_mode   = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInCountingMode(ERAD_COUNTER2_BASE, counter_params);

    //
    // Configure COUNTER3 to count the number of times the ISR is executed
    // (the number of times the BUSCOMP1 event has occurred)
    //
    counter_params.event        = ERAD_EVENT_HWBP1;
    counter_params.event_mode   = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInCountingMode(ERAD_COUNTER3_BASE, counter_params);

    //
    // Configure COUNTER4 to count the number of CPU cycles that elapsed
    // between the interrupt and the actual execution of the ISR
    //
    counter_params.event        = ERAD_EVENT_NO_EVENT;
    counter_params.event_mode   = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER4_BASE, counter_params, ERAD_EVENT_TIMER1_TINT1, ERAD_EVENT_HWBP1);
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
    // Resets interrupt counters for the cpuTimer
    //
    cpuTimer1IntCount = 0;
}

//
// cpuTimer1ISR - Counter for CpuTimer2
//
interrupt void
cpuTimer1ISR(void)
{
    //
    // Simulate storing data to a location. "volatile" keyword ensures this is
    // not optimized out by the compiler.
    //
    volatile uint32_t output;

    //
    // Simulate a task that can take some time to complete. Loop a "random"
    // number of times and store values to a location.
    //
    uint32_t i;
    for(i = 0; i < cpuTimer1IntCount; i++)
    {
        output = i;
    }

    //
    // The CPU acknowledges the interrupt. We are interested in the ISR
    // until here. Rest is to display the results.
    //
    cpuTimer1IntCount++;

    //
    // Get all the required values
    //
    time_isr             = ERAD_getMaxCount(ERAD_COUNTER1_BASE);
    number_of_interrupts = ERAD_getCurrentCount(ERAD_COUNTER2_BASE);
    number_of_executions = ERAD_getCurrentCount(ERAD_COUNTER3_BASE);
    time_bw_int_ex       = ERAD_getMaxCount(ERAD_COUNTER4_BASE);
    ERAD_setMaxCount(ERAD_COUNTER1_BASE, 0);
    ERAD_setMaxCount(ERAD_COUNTER4_BASE, 0);

    ESTOP0;
}

//
// ISR to be executed if counter generates RTOS interrupt
//
interrupt void
RTOSISR(void)
{
    //
    // Variable to show that ISR executed
    //
    RTOSintCount++;
    ESTOP0;
}


//
// End of File
//
