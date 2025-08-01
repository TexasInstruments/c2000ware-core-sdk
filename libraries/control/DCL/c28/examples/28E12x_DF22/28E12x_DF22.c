/* Example_DF22.c
 *
//###########################################################################
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################
 *
*/

#include "driverlib.h"
#include "device.h"
#include "DCLF32.h"
#include "DCL_fdlog.h"

#define	DATA_LENGTH	1601

// input data
#pragma DATA_SECTION(e_array, "PDataLogSection")
const float e_array[DATA_LENGTH]=
{
#include "DF22_edata.dat"
};
FDLOG eBuf = FDLOG_DEFAULTS;

// full controller results
#pragma DATA_SECTION(u1_array, "QDataLogSection")
float u1_array[DATA_LENGTH];
FDLOG u1Buf = FDLOG_DEFAULTS;

// pre-computed controller results
#pragma DATA_SECTION(u2_array, "RDataLogSection")
float u2_array[DATA_LENGTH];
FDLOG u2Buf = FDLOG_DEFAULTS;

// controller difference data
#pragma DATA_SECTION(d_array, "SDataLogSection")
float d_array[DATA_LENGTH];
FDLOG dBuf = FDLOG_DEFAULTS;

// function prototypes
void initCPUTimer0(float freq, float period);
extern interrupt void control_Isr(void);

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
int complete = 0, fail=0;
float ek;
float u1k;
float u2k;
float dk;
float upperLim;
float lowerLim;
uint16_t v;
DCL_DF22 controller1 = DF22_DEFAULTS;
DCL_DF22 controller2 = DF22_DEFAULTS;


/* main */
main()
{
	// device initialization
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    // initialize CPU timer0 & interrupt
    Interrupt_register(INT_TIMER0, &control_Isr);
    initCPUTimer0( DEVICE_SYSCLK_FREQ, 1000);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);

	// initialise data arrays
	DCL_initLog(&eBuf, (float32_t *)e_array, DATA_LENGTH);
	DCL_initLog(&u1Buf, u1_array, DATA_LENGTH);
	DCL_initLog(&u2Buf, u2_array, DATA_LENGTH);
	DCL_initLog(&dBuf, d_array, DATA_LENGTH);
	DCL_clearLog(&u1Buf);
	DCL_clearLog(&u2Buf);
	DCL_fillLog(&dBuf, 1.234567f);

	// initialise full controller
	controller1.a1 = -1.9417f;
	controller1.a2 = 0.9417f;
	controller1.b0 = 9.8549f;
	controller1.b1 = -19.4165f;
	controller1.b2 = 9.5636f;

	// initialise pre-computed controller
	controller2.a1 = controller1.a1;
	controller2.a2 = controller1.a2;
	controller2.b0 = controller1.b0;
	controller2.b1 = controller1.b1;
	controller2.b2 = controller1.b2;

	// clamp limits
	upperLim = 1000.0f;
	lowerLim = -1000.0f;

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

/* control ISR: triggered by CPU timer 0 */
interrupt void control_Isr(void)
{	

	// read data & run controllers
	if (complete == 0)
	{
		// read input data
		ek = DCL_readLog(&eBuf);

		// run full controller
		u1k = DCL_runDF22_C1(&controller1, ek);

		// run pre-computed controller
		u2k = DCL_runDF22_C2(&controller2, ek);
		v = DCL_runClamp_C1(&u2k, upperLim, lowerLim);
		if (0U == v)
		{
			DCL_runDF22_C3(&controller2, ek, u2k);
		}

		// compute difference
		dk = u1k - u2k;
		if(dk!=0)
		{
			fail++;
		}

		// store results
		DCL_writeLog(&u1Buf, u1k);
		DCL_writeLog(&u2Buf, u2k);
		DCL_writeLog(&dBuf, dk);
		
		// check if data log is full
        if FDLOG_START(&dBuf)
        {
            complete = 1;
        }
	}	

	IsrCount++;
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}


/* end of file */
