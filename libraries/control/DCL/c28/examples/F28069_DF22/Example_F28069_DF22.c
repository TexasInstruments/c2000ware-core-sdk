/* Example_F28069_DF22.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED 
 *
*/

#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "DCLF32.h"
#include "DCL_fdlog.h"

#define	DATA_LENGTH	1601

// input data
#pragma DATA_SECTION(e_array, "PDataLogSection")
float e_array[DATA_LENGTH];
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

extern interrupt void control_Isr(void);

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
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
	// initialise system
	InitSysCtrl();
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();
	InitPieVectTable();
	EALLOW;
	PieVectTable.TINT0 = &control_Isr;
	EDIS;

	// configure CPU timer 0
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 90.0, 1.0e+03);

	// initialise data arrays
	DCL_initLog(&eBuf, e_array, DATA_LENGTH);
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

	// enable interrupts
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	IER |= M_INT1;
	EINT;
	StartCpuTimer0();

	// idle loop
	while(1)
	{
		IdleLoopCount++;
	}

}


/* control ISR: triggered by CPU timer 0 */
interrupt void control_Isr(void)
{
	// clear timer flag & acknowledge interrupt
	CpuTimer0Regs.TCR.bit.TIF = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	// read data & run controllers
	if (eBuf.dptr < eBuf.lptr)
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

		// store results
		DCL_writeLog(&u1Buf, u1k);
		DCL_writeLog(&u2Buf, u2k);
		DCL_writeLog(&dBuf, dk);
	}
	else
	{
		// place break-point here
		asm(" NOP");
	}

	IsrCount++;
}


/* end of file */
