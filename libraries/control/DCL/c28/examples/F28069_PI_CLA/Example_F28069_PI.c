/* Example_F28069_PI.c
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
#include "CLA_shared.h"

// function prototypes
interrupt void control_Isr(void);

// global  variables
long IdleLoopCount = 0;
long IsrCount = 0;
float Duty;

// shared variables
#pragma DATA_SECTION(rk, "CpuToCla1MsgRAM")
#pragma DATA_SECTION(yk, "CpuToCla1MsgRAM")
#pragma DATA_SECTION(uk, "Cla1ToCpuMsgRAM")
float rk = 0.25f;
float yk;
float uk;

#pragma DATA_SECTION(pi1, "Cla1DataRam1")
DCL_PI_CLA pi1 = PI_CLA_DEFAULTS;


main()
{
	/* initialise system */
	InitSysCtrl();							// [F2806x_SysCtrl.c]
	DINT;									// disable interrupts
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();							// initialise PIE control registers [F2806x_PieCtrl.c]
	InitPieVectTable();						// initialise PIE vector table [F2806x_PieVect.c]
	EALLOW;
	PieVectTable.ADCINT1 = &control_Isr;
	EDIS;

	/* initialise PI controller */
	pi1.Kp = 5.5f;
	pi1.Ki = 0.015f;
	pi1.i10 = 0.0f;
	pi1.i6 = 1.0f;
	pi1.Umax = 10.2f;
	pi1.Umin = -10.2f;

    /* compute CLA task vectors */
	EALLOW;
    Cla1Regs.MVECT1 = (Uint16)((Uint32)&Cla1Task1 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT2 = (Uint16)((Uint32)&Cla1Task2 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT3 = (Uint16)((Uint32)&Cla1Task3 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT4 = (Uint16)((Uint32)&Cla1Task4 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT5 = (Uint16)((Uint32)&Cla1Task5 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT6 = (Uint16)((Uint32)&Cla1Task6 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT7 = (Uint16)((Uint32)&Cla1Task7 -(Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = (Uint16)((Uint32)&Cla1Task8 -(Uint32)&Cla1Prog_Start);

    /* CLA task triggers */
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

	/* configure ePWM1 */
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPwm();								// [F2806x_EPwm.c]
	EPwm1Regs.TBCTL.bit.CTRMODE = 3;		// freeze TB counter
	EPwm1Regs.TBCTL.bit.PRDLD = 1;  		// immediate load
	EPwm1Regs.TBCTL.bit.PHSEN = 0;	   		// disable phase loading
	EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;		// disable SYNCOUT signal
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;		// TBCLK = SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;			// clock divider = /1
	EPwm1Regs.TBCTL.bit.FREE_SOFT = 2;		// free run on emulation suspend
	EPwm1Regs.TBPRD = 0x2328;	          	// set period for ePWM1 (0x2328 = 10kHz)
	EPwm1Regs.TBPHS.all = 0;			    // time-base Phase Register
	EPwm1Regs.TBCTR = 0;					// time-base Counter Register
	EPwm1Regs.ETSEL.bit.SOCAEN = 1;        	// enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = 1;       	// select SOC from zero match
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        	// generate pulse on 1st event
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;		// enable shadow mode
	EPwm1Regs.CMPCTL.bit.LOADAMODE = 2; 	// reload on CTR=zero
	EPwm1Regs.CMPA.half.CMPA = 0x0080;	 	// set compare A value
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;		// HIGH on CMPA up match
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;	// LOW on zero match
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

	/* configure ADC */
	InitAdc();								// [F2806x_Adc.c]
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 0;	// early interrupt generation
	AdcRegs.INTSEL1N2.bit.INT1E = 1;		// enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT = 0;		// disable ADCINT1 continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL = 1;		// setup EOC1 to trigger ADCINT1
	AdcRegs.INTSEL1N2.bit.INT2E = 0;	    // enable ADCINT2
	AdcRegs.INTSEL1N2.bit.INT2CONT = 0;	    // disable ADCINT1 continuous mode
	AdcRegs.INTSEL1N2.bit.INT2SEL = 0;	    // setup EOC1 to trigger ADCINT2
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;		// set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC1CTL.bit.CHSEL = 8;		// set SOC1 channel select to ADCINB0
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;		// set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;		// set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;		// set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;		// set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	EDIS;

	/* configure GPIO */
	InitGpio();  							// [F2806x_Gpio.c]
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// GPIO34 = I/O pin
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// GPIO34 = output
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;		// GPIO34 = 1
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;	// GPIO39 = I/O pin
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;		// GPIO39 = output
	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;	// GPIO39 = 0

	/* CLA setup */
	Cla1Regs.MIER.bit.INT3 = 1;
	Cla1Regs.MIER.bit.INT8 = 1;
	Cla1ForceTask8andWait();

	/* enable interrupts */
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1; 		// enable PIE INT 1.1 (ADCINT1) - [adcisr]
	IER |= M_INT1; 							// enable CPU Interrupt 1 (TINT0)
	EINT;          							// enable global interrupt mask
	EPwm1Regs.TBCTL.bit.CTRMODE = 0;		// PWM1 timer: count up and start
	EDIS;

  	/* idle loop */
	while(1)
	{
		IdleLoopCount++;
	}

}


/* control ISR: triggered by ADC EOC */
interrupt void control_Isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

	// read ADC channel
	yk = ((float) AdcResult.ADCRESULT0 - 2048.0f) / 2047.0f;

	// trigger PI controller on CLA
	EALLOW;
	Cla1ForceTask3andWait();

	// write u(k) to PWM
	Duty = (uk / 2.0f + 0.5f) * (float) EPwm1Regs.TBPRD;
	EPwm1Regs.CMPA.half.CMPA = (Uint16) Duty;

	IsrCount++;
}


/* end of file */
