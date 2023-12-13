/* Example_F28388D_PIDF64.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
*/

#include "device.h"
#include "DCLF64.h"
#include "DCL_fdlog64.h"

#define	ISR_PRD		10000

// data logs
#pragma DATA_SECTION(p_array, "PDataLogSection")
#pragma DATA_SECTION(q_array, "QDataLogSection")
#pragma DATA_SECTION(r_array, "RDataLogSection")
#pragma DATA_SECTION(s_array, "SDataLogSection")

// section addresses from linker file
extern unsigned int pData_start;
extern unsigned int qData_start;
extern unsigned int rData_start;
extern unsigned int sData_start;

// data arrays
float64_t p_array[FDLOG64_DEFAULT_SIZE];
float64_t q_array[FDLOG64_DEFAULT_SIZE];
float64_t r_array[FDLOG64_DEFAULT_SIZE];
float64_t s_array[FDLOG64_DEFAULT_SIZE];

// data log structs
FDLOG64 pBuf = FDLOG64_DEFAULTS;
FDLOG64 qBuf = FDLOG64_DEFAULTS;
FDLOG64 rBuf = FDLOG64_DEFAULTS;
FDLOG64 sBuf = FDLOG64_DEFAULTS;

// global  variables
uint32_t IdleLoopCount = 0L;
uint32_t IsrCount = 0L;
float64_t rk = 0.25f;
float64_t yk;
float64_t lk;
float64_t uk;
DCL_PIDF64 pid = PIDF64_DEFAULTS;

// function prototypes
__interrupt void control_isr(void);
void configCPUTimer(uint32_t, uint32_t);


void main(void)
{
	// device initialization
    Device_init();
	SysCtl_disableWatchdog();
    Device_initGPIO();
    Interrupt_initModule();
	DINT;
    Interrupt_initVectorTable();
	
	// configure CPU timer 0 interrupt
    Interrupt_register(INT_TIMER0, &control_isr);
    configCPUTimer(CPUTIMER0_BASE, ISR_PRD);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);
   
    // initialize data logs
    DCL_initLog64(&pBuf, (float64_t *) &pData_start, FDLOG64_DEFAULT_SIZE);
    DCL_initLog64(&qBuf, (float64_t *) &qData_start, FDLOG64_DEFAULT_SIZE);
    DCL_initLog64(&rBuf, (float64_t *) &rData_start, FDLOG64_DEFAULT_SIZE);
    DCL_initLog64(&sBuf, (float64_t *) &sData_start, FDLOG64_DEFAULT_SIZE);
	DCL_fillLog64(&rBuf, 1.0);
	DCL_clearLog64(&sBuf);
	
	// controller initialization
	pid.Kp = 5.4;
	pid.Ki = 0.0014;
	pid.Kd = 0.25;
	pid.Kr = 1.0;
	pid.c1 = 628.2199;
	pid.c2 = -0.9997;
    pid.c1 = 151.7094;
    pid.c2 = 0.5171;

	DCL_BREAK_POINT;
	
    // enable interrupt
	CPUTimer_startTimer(CPUTIMER0_BASE);
    EINT;
    ERTM;

    // idle loop
    do {
		if (FDLOG64_END(&sBuf))
		{
			DCL_BREAK_POINT;
		}
		
        IdleLoopCount++;
    } while(1);
}


// control interrupt service routine
__interrupt void control_isr(void)
{
	// read inputs
	rk = DCL_readLog64(&pBuf);
	yk = DCL_readLog64(&qBuf);
	lk = DCL_readLog64(&rBuf);

	// run PIDF64 controller
    uk = DCL_runPIDF64_S1(&pid, rk, yk, lk);

	// store the control
    DCL_writeLog64(&sBuf, uk);

	// stop timer at end of buffer
	if (FDLOG64_END(&sBuf))
	{
		CPUTimer_stopTimer(CPUTIMER0_BASE);
	}

    IsrCount++;
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


// CPU timer configuration
void configCPUTimer(uint32_t cpuTimer, uint32_t period)
{
    CPUTimer_setPeriod(cpuTimer, period);
    CPUTimer_setPreScaler(cpuTimer, 0);
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
}

 /* end of file */
