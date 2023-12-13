/* Example_F28069_DF23.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED  
 *
*/

// header files
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "DCLCLA.h"
#include "DCL_fdlog.h"
#include "CLA_shared.h"

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

// function prototypes
interrupt void control_Isr(void);

// shared variables
#pragma DATA_SECTION(ek, "CpuToCla1MsgRAM")
#pragma DATA_SECTION(u1k, "Cla1ToCpuMsgRAM")
#pragma DATA_SECTION(u2k, "Cla1ToCpuMsgRAM")
float ek;
float u1k;
float u2k;

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
float dk;


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

    // compute CLA task vectors
	EALLOW;
    Cla1Regs.MVECT1 = (Uint16)((Uint32)&Cla1Task1 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT2 = (Uint16)((Uint32)&Cla1Task2 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT3 = (Uint16)((Uint32)&Cla1Task3 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT4 = (Uint16)((Uint32)&Cla1Task4 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT5 = (Uint16)((Uint32)&Cla1Task5 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT6 = (Uint16)((Uint32)&Cla1Task6 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT7 = (Uint16)((Uint32)&Cla1Task7 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = (Uint16)((Uint32)&Cla1Task8 -(Uint32)&Cla1Prog_Start);

    // CLA task triggers
 	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL = CLA_INT1_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL = CLA_INT2_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT3SEL = CLA_INT3_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT4SEL = CLA_INT4_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT5SEL = CLA_INT5_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT6SEL = CLA_INT6_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT7SEL = CLA_INT7_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT8SEL = CLA_INT8_NONE;
	Cla1Regs.MIER.all = 0x00FF;

     /* Switch the CLA program space to the CLA and enable software forcing
      * Also switch over CLA data ram 0,1 and 2
 	 * CAUTION: The RAMxCPUE bits can only be enabled by writing to the register
 	 * and not the individual bit field. Furthermore, the status of these bitfields
 	 * is not reflected in either the watch or register views - they always read as
 	 * zeros. This is a known bug and the user is advised to test CPU accessibilty
 	 * first before proceeding
    	 */
 	Cla1Regs.MMEMCFG.all = CLA_PROG_ENABLE|CLARAM0_ENABLE|CLARAM1_ENABLE|CLARAM2_ENABLE|CLA_RAM1CPUE;
 	Cla1Regs.MCTL.bit.IACKE = 1;
 	EDIS;

	// enable CLA interrupts and run task 8
	Cla1Regs.MIER.bit.INT3 = 1;
	Cla1Regs.MIER.bit.INT8 = 1;
	Cla1ForceTask8andWait();

	// enable CPU interrupts & start timer 0
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


/* control ISR: triggered by timer 0 */
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

		// run DF23 controllers on CLA
		EALLOW;
		Cla1ForceTask3andWait();
		EDIS;

		// compute difference in controller results
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
