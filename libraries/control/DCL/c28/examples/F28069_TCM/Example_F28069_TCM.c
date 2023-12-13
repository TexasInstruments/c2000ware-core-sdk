/* Example_F28069_TCM.c
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
#include "DCL_TCM.h"

#define	DATA_LENGTH	1601
#define TCM_DATA_LENGTH	350
#define ISR_FREQ	10000.0f

// input reference data
#pragma DATA_SECTION(r_array, "PDataLogSection")
float r_array[DATA_LENGTH];
FDLOG rBuf = FDLOG_DEFAULTS;

// feedback data
#pragma DATA_SECTION(y_array, "QDataLogSection")
float y_array[DATA_LENGTH];
FDLOG yBuf = FDLOG_DEFAULTS;

// servo loop error
#pragma DATA_SECTION(e_array, "RDataLogSection")
float e_array[DATA_LENGTH];
FDLOG eBuf = FDLOG_DEFAULTS;

// transient data
#pragma DATA_SECTION(d_array, "SDataLogSection")
float d_array[DATA_LENGTH];
FDLOG dBuf = FDLOG_DEFAULTS;

interrupt void control_Isr(void);

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
float rk;
float yk;
float ek;
TCM tcm1 = TCM_DEFAULTS;
float P1;
float P2;
float P3;


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
	ConfigCpuTimer(&CpuTimer0, 90.0, ISR_FREQ);

	// initialise data arrays
	DCL_initLog(&rBuf, r_array, DATA_LENGTH);
	DCL_initLog(&yBuf, y_array, DATA_LENGTH);
	DCL_initLog(&eBuf, e_array, DATA_LENGTH);
	DCL_initLog(&dBuf, d_array, TCM_DATA_LENGTH);
	DCL_clearLog(&eBuf);

	// initialise TCM
	DCL_initTCM(&tcm1, dBuf.fptr, TCM_DATA_LENGTH, 25, -0.001f, 0.001f);
	DCL_armTCM(&tcm1);

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
	IsrCount++;

	// read feedback data from log
	rk = DCL_freadLog(&rBuf);
	yk = DCL_freadLog(&yBuf);

	// run the TCM
	DCL_runTCM(&tcm1, yk);

	// log the servo error
	ek = rk - yk;
	DCL_fwriteLog(&eBuf, ek);

	// if data read-out complete
	if FDLOG_START(&rBuf)
	{
		// stop interrupt
		PieCtrlRegs.PIEIER1.bit.INTx7 = 0;

		// compute performance indices
		P1 = DCL_runITAE_C1(&eBuf, 1/ISR_FREQ);
		P2 = DCL_runIAE_C1(&eBuf);
		P3 = DCL_runIES_C1(&eBuf);
		
		// place preak-point here
		asm(" NOP");
	}
}


/* end of file */
