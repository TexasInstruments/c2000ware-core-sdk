/* Example_NLPID.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
*/

// includes
#include "driverlib.h"
#include "device.h"
#include "DCL_NLPID.h"
#include "DCL_fdlog.h"

#define DATA_LENGTH 501

// data logs
#pragma DATA_SECTION(p_array, "pDataLogSection")
#pragma DATA_SECTION(q_array, "qDataLogSection")
#pragma DATA_SECTION(s_array, "sDataLogSection")

// section addresses from linker file
extern unsigned int pData_start;
extern unsigned int qData_start;
extern unsigned int sData_start;

// data arrays
float32_t p_array[DATA_LENGTH];
float32_t q_array[DATA_LENGTH];
float32_t s_array[DATA_LENGTH];

// data log structs
FDLOG pBuf = FDLOG_DEFAULTS;
FDLOG qBuf = FDLOG_DEFAULTS;
FDLOG sBuf = FDLOG_DEFAULTS;

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
int complete = 0;
float32_t rk = 0.25f, yk, uk;
DCL_NLPID controller1 = NLPID_DEFAULTS;
DCL_NLPID_SPS sps1 = NLPID_SPS_DEFAULTS;
DCL_CSS css1 = DCL_CSS_DEFAULTS;

// function prototypes
void initCPUTimer0(float freq, float period);
__interrupt void control_isr(void);


void main(void)
{
    // device initialization
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // initialize CPU timer0 & interrupt
    Interrupt_register(INT_TIMER0, &control_isr);
    initCPUTimer0( DEVICE_SYSCLK_FREQ, 1000);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);

    // initialize data logs
    DCL_initLog(&pBuf, (float32_t *) p_array, DATA_LENGTH);
    DCL_initLog(&qBuf, (float32_t *) q_array, DATA_LENGTH);
    DCL_initLog(&sBuf, (float32_t *) s_array, DATA_LENGTH);
    DCL_clearLog(&sBuf);

    // initialize controller
    DCL_resetNLPID(&controller1);
    controller1.sps = &sps1;
    controller1.css = &css1;
    DCL_SET_CONTROLLER_PERIOD(&controller1, 0.01f);
    controller1.sps->Kp = 25.0f;
    controller1.sps->Ki = 0.002f;
    controller1.sps->Kd = 0.03f;
    controller1.sps->alpha_p = 1.2f;
    controller1.sps->alpha_i = 1.05f;
    controller1.sps->alpha_d = 0.8f;
    controller1.sps->delta_p = 0.3f;
    controller1.sps->delta_i = 0.1f;
    controller1.sps->delta_d = 0.16f;
    controller1.sps->Umax = 100.0f;
    controller1.sps->Umin = -100.0f;
    DCL_setNLPIDfilterBW(&controller1, 4.9f);

    // load gamma from the SPS
    DCL_setNLPIDgamma(&controller1);
    DCL_REQUEST_UPDATE(&controller1);
    DCL_updateNLPID(&controller1);

    // enable global interrupts
    EINT;
    ERTM;
    CPUTimer_startTimer(CPUTIMER0_BASE);

    while(1)
    {
        IdleLoopCount++;

        if (complete == 1)
        {
            DCL_BREAK_POINT;
        }
    }
}


// initialize CPU timer0
void initCPUTimer0(float freq, float period)
{
    uint32_t temp;

    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(CPUTIMER0_BASE, temp);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_setEmulationMode(CPUTIMER0_BASE,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
}


// control ISR, triggered by timer0
__interrupt void control_isr(void)
{

    if (complete == 0)
    {
        // read test data
        rk = DCL_readLog(&pBuf);
        yk = DCL_readLog(&qBuf);

        // run controller
        uk = DCL_runNLPID_C3(&controller1, rk, yk, 1.0f);

        // store controller output
        DCL_writeLog(&sBuf, uk);

        // check if data log is full
        if FDLOG_START(&sBuf)
        {
            complete = 1;
        }
    }

    // exit sequence
    IsrCount++;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

/* end of file */
