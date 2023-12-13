//#############################################################################
//! \file  /examples/common/examples_setup.c
//!
//! \brief  Initialization routines for the FPU library examples
//! \author Vishal Coelho
//! \date   Feb 26, 2015
//
//  Group:             C2000

//
//#############################################################################
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void FPU_initSystemClocks()
{
    InitSysCtrl();      //Enable peripheral clocks

    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0x00;
}

void FPU_initEpie()
{
    DINT;               //Globally disable maskable CPU interrupts
    InitPieCtrl();      //Clear and disable all PIE interrupts
    IER = 0x0000;       //Individually disable maskable CPU interrupts
    IFR = 0x0000;       //Clear all CPU interrupt flags
    InitPieVectTable(); //Populate PIE interrupt vector table with shell ISRs
}

#ifdef FLASH
void FPU_initFlash()
{
    EALLOW;

    //At reset bank and pump are in sleep
    //A Flash access will power up the bank and pump automatically
    //After a Flash access, bank and pump go to low power mode (configurable in
    //FBFALLBACK/FPAC1 registers)-
    //if there is no further access to flash
    //Power up Flash bank and pump and this also sets the fall back mode of 
    //flash and pump as active
    Flash0CtrlRegs.FPAC1.bit.PMPPWR = 0x1;
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;

    //Disable Cache and prefetch mechanism before changing wait states
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;

    //Set waitstates according to frequency
    //CAUTION
    //Minimum waitstates required for the flash operating
    //at a given CPU rate must be characterized by TI.
    //Refer to the datasheet for the latest information.
#if CPU_FRQ_200MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
#endif

#if CPU_FRQ_150MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

#if CPU_FRQ_120MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

    //Enable Cache and prefetch mechanism to improve performance
    //of code executed from Flash.
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;

    //At reset, ECC is enabled
    //If it is disabled by application software and if application again wants 
    //to enable ECC
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    EDIS;

    //Force a pipeline flush to ensure that the write to
    //the last register configured occurs before returning.

    __asm(" RPT #7 || NOP");
}
#endif //FLASH

#ifdef ADCA
void FPU_initADCA(void)
{
    EALLOW;
    //write configurations
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //Set pulse positions to early
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 0;

    //power up the ADC
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);

    //Select the channels to convert and end of conversion flag ADCA
    AdcaRegs.ADCSOC0CTL.bit.CHSEL     = 0;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS     = 14; //sample window is 15 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;  //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  //EOC0 is set to trigger ADCINT1
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1;  //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  //make sure INT1 flag is cleared
    EDIS;
}

void FPU_initEPWM(void)
{
    CpuSysRegs.PCLKCR2.bit.EPWM1             =1;  // Enable EPWM1 clocks
    CpuSysRegs.PCLKCR2.bit.EPWM2             =1;  // Enable EPWM1 clocks
    
    //Enable EPWM GPIOs
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    
    EALLOW;
    // EPWM clock divider set to /2
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;                
    // Turn off the EPWM clock
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC       = 0;                
    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCAEN             = 0;                
    // Select SOC on up-count
    EPwm1Regs.ETSEL.bit.SOCASEL            = 4;                
    // Generate pulse on 1st event
    EPwm1Regs.ETPS.bit.SOCAPRD             = 1;                
    // Set compare A value to 2000 counts
    EPwm1Regs.CMPA.bit.CMPA                = EPWM1_DUTY_CYCLE; 
    // Set period to 4000 counts
    EPwm1Regs.TBPRD                        = EPWM1_PERIOD;     
    // freeze counter
    EPwm1Regs.TBCTL.bit.CTRMODE            = 3;                
    //enable SOCA
    EPwm1Regs.ETSEL.bit.SOCAEN             = 1;                
    EPwm1Regs.TBCTL.bit.HSPCLKDIV          = EPWM_HSPCLKDIV;
    // Disable SOC on A group
    EPwm2Regs.ETSEL.bit.SOCAEN             = 0;                
    // Set compare A value to 10000 counts
    EPwm2Regs.CMPA.bit.CMPA                = EPWM2_DUTY_CYCLE; 
    // Set period to 20000 counts
    EPwm2Regs.TBPRD                        = EPWM2_PERIOD;     
    // freeze counter
    EPwm2Regs.TBCTL.bit.CTRMODE            = 3;                
    EPwm2Regs.TBCTL.bit.HSPCLKDIV          = EPWM_HSPCLKDIV;
    // Clear PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU               = AQ_SET;           
    EPwm1Regs.AQCTLA.bit.PRD               = AQ_CLEAR;         
    // Clear PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.CAU               = AQ_SET;           
    EPwm2Regs.AQCTLA.bit.PRD               = AQ_CLEAR;
    
    EDIS;
}

void FPU_startEPWM(void)
{
    // Turn on the EPWM
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm1Regs.TBCTL.bit.CTRMODE      = 0; //unfreeze, and enter up count mode
    EPwm2Regs.TBCTL.bit.CTRMODE      = 0; //unfreeze, and enter up count mode
    EDIS;
}
#endif //ADCA

void done(void)
{
    for(;;);
}
// End of file
