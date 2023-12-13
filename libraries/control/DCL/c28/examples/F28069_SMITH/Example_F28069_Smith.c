/* Example_F28069_Smith.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
*/

// header files
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "DCLF32.h"
#include "DCL_fdlog.h"

// function prototypes
extern interrupt void control_Isr(void);

// global  variables
uint32_t IdleLoopCount = 0;
uint32_t IsrCount = 0;
float32_t rk = 0.25f, yk, uk;
float32_t Duty;

// controller
DCL_DF23 F = DF23_DEFAULTS;
DCL_CSS Fcss = DCL_CSS_DEFAULTS;
DCL_DF23_SPS Fsps = DF23_SPS_DEFAULTS;
float32_t v3, v5 = 0.0f, v6 = 0.0f;

// plant model
DCL_DF13 GH = DF13_DEFAULTS;

// modelled delay
#define GH_DELAY_LINE_LENGTH 13
#pragma DATA_SECTION(p_array, "PDataLogSection")
float32_t p_array[GH_DELAY_LINE_LENGTH];
FDLOG pBuf = FDLOG_DEFAULTS;


/* main */
main()
{
    /* initialise system */
    InitSysCtrl();                          // [F2806x_SysCtrl.c]
    DINT;                                   // disable interrupts
    IER = 0x0000;
    IFR = 0x0000;
    InitPieCtrl();                          // initialise PIE control registers [F2806x_PieCtrl.c]
    InitPieVectTable();                     // initialise PIE vector table [F2806x_PieVect.c]

    EALLOW;
    PieVectTable.ADCINT1 = &control_Isr;    // load interrupt vector
    EDIS;

    /* configure ePWM1 */
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    InitEPwm();                             // [F2806x_EPwm.c]
    EPwm1Regs.TBCTL.bit.CTRMODE = 3;        // freeze TB counter
    EPwm1Regs.TBCTL.bit.PRDLD = 1;          // immediate load
    EPwm1Regs.TBCTL.bit.PHSEN = 0;          // disable phase loading
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;       // disable SYNCOUT signal
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;      // TBCLK = SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;         // clock divider = /1
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 2;      // free run on emulation suspend
    EPwm1Regs.TBPRD = 0x2328;               // set period for ePWM1 (0x2328 = 10kHz)
    EPwm1Regs.TBPHS.all = 0;                // time-base Phase Register
    EPwm1Regs.TBCTR = 0;                    // time-base Counter Register
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;         // enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 1;        // select SOC from zero match
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;         // generate pulse on 1st event
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;     // enable shadow mode
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 2;     // reload on CTR=zero
    EPwm1Regs.CMPA.half.CMPA = 0x0080;      // set compare A value
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;      // HIGH on CMPA up match
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;    // LOW on zero match
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    /* configure ADC */
    InitAdc();                              // [F2806x_Adc.c]
    EALLOW;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 0;    // early interrupt generation
    AdcRegs.INTSEL1N2.bit.INT1E = 1;        // enable ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;     // disable ADCINT1 continuous mode
    AdcRegs.INTSEL1N2.bit.INT1SEL = 1;      // setup EOC1 to trigger ADCINT1
    AdcRegs.INTSEL1N2.bit.INT2E = 0;        // disable ADCINT2
    AdcRegs.INTSEL1N2.bit.INT2CONT = 0;     // disable ADCINT1 continuous mode
    AdcRegs.INTSEL1N2.bit.INT2SEL = 0;      // no trigger to ADCINT2
    AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;       // set SOC0 channel select to ADCINA0
    AdcRegs.ADCSOC1CTL.bit.CHSEL = 8;       // set SOC1 channel select to ADCINB0
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 5;     // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;     // set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
    AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;       // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;       // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    EDIS;

    /* delay line initialization */
    DCL_initLog(&pBuf, p_array, GH_DELAY_LINE_LENGTH);
    DCL_clearLog(&pBuf);

    /* initialize plant model */
//           4.95e-05 z^2 + 4.926e-07 z - 4.901e-05
//   GH(z) = --------------------------------------
//              z^3 - 2.97 z^2 + 2.94 z - 0.9704

    GH.b0 = 0.0f;
    GH.b1 = 4.95e-05f;
    GH.b2 = 4.926e-07f;
    GH.b3 = -4.901e-05f;
    GH.a0 = 1.0f;
    GH.a1 = -2.97f;
    GH.a2 = 2.94f;
    GH.a3 = -0.9704f;

    /* initalize controller */
    F.b0 = 9.6580f;
    F.b1 = -9.1580f;
    F.b2 = -9.6521f;
    F.b3 = 9.1639f;
    F.a1 = -2.1280f;
    F.a2 = 1.3968f;
    F.a3 = -0.2689f;

    /* enable interrupts */
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;      // enable PIE INT 1.1 (ADCINT1) - [adcisr]
    IER |= M_INT1;                          // enable core interrupt 1 (ADC) - [control_isr]
    SetDBGIER(0x0001);                      // enable real-time debug interrupts
    EINT;                                   // enable global interrupt mask

    EALLOW;
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;        // PWM1 timer: count up and start
    EDIS;

    /* idle loop */
    while(1)
    {
        IdleLoopCount++;                    // increment loop counter
        asm(" NOP");
    } // while

} // main


/* control ISR: triggered by ADC EOC */
interrupt void control_Isr(void)
{
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    // read feedback
    yk = ((float) AdcResult.ADCRESULT0 - 2048.0f) / 2047.0f;

    // run controller
    v3 = rk - yk + v6 - v5;
    uk = DCL_runDF23_C4(&F, v3);            // control effort
    v5 = DCL_runDF13_C4(&GH, uk);           // plant model
    v6 = DCL_writeLog(&pBuf, v5);           // delay line

    // write u(k) to PWM
    Duty = (uk / 2.0f + 0.5f) * (float) EPwm1Regs.TBPRD;
    EPwm1Regs.CMPA.half.CMPA = (Uint16) Duty;

    IsrCount++;
}


/* end of file */
