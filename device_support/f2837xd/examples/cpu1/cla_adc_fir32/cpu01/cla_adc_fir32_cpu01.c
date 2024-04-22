//###########################################################################
//
// FILE:   cla_adc_fir32_cpu01.c
//
// TITLE:  CLA 5 Tap FIR Filter Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA 5 Tap Finite Impulse Response Filter (cla_adc_fir32_cpu01)</h1>
//!
//! This example implements a 5 Tap FIR filter. It will setup
//! EPWM1 to trigger ADCA at a frequency of 50KHz. Once the ADC
//! completes sampling, it will trigger task 7 of the CLA which
//! runs the filter on the ADC sample.
//!
//! EPWM2 is setup to switch at 10KHz. Connect pin EPWM2A to ADCA0
//! on the board to see the filtering effect.
//!
//! \b Memory \b Allocation \n
//!  - CPU to CLA1 Message RAM
//!    - A - Filter Coefficients
//!  - CLA1 to CPU Message RAM
//!    - voltFilt - Filtered sample
//!    - X - filter sample delay line
//!
//! \b Watch \b Variables \n
//!  - voltFilt - Filtered sample
//!  - X - filter sample delay line
//!
//! \b External \b Connections \n
//!  - EPWM2A (GPIO2) to ADCA0
//!
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "cla_adc_fir32_shared.h"

//
// Defines
//

//
//ADC defines
//definitions for selecting ADC reference
//CAUTION: internal reference mode will drive a voltage onto the VREF pin,
//make sure that this pin is not also being driven externally in this case
//
#define REFERENCE_INTERNAL     0 //internal reference (12-bit only)
#define REFERENCE_EXTERNAL     1 //external reference

//
//EPWM defines
//
#define PWM1_PERIOD            2000
#define PWM1_DUTY_CYCLE        1000
#define PWM2_PERIOD            10000
#define PWM2_DUTY_CYCLE        5000

//
//CLA defines
//
#define WAITSTEP               asm(" RPT #255 || NOP")

//
//Common
//
#define ADC_BUF_LEN            200
#define LOWPASS                1
#define HIGHPASS               (~LOWPASS)

//
// Globals
//

//
//Task 1 (ASM) Variables
//
#ifdef __cplusplus
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM")
    uint16_t voltFilt;
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM")
    float  X[FILTER_LEN];
    #pragma DATA_SECTION(A,"CpuToCla1MsgRAM");
    #if LOWPASS
    float A[FILTER_LEN] = {0.0625L, 0.25L, 0.375L, 0.25L, 0.0625L};
    #elif HIGHPASS
    float A[FILTER_LEN] = {0.0625L, -0.25L, 0.375L, -0.25L, 0.0625L};
    #endif
#else
    #pragma DATA_SECTION(voltFilt,"Cla1ToCpuMsgRAM")
    uint16_t voltFilt;
    #pragma DATA_SECTION(X,"Cla1ToCpuMsgRAM")
    float X[FILTER_LEN];
    #pragma DATA_SECTION(A,"CpuToCla1MsgRAM");
    float A[FILTER_LEN];
#endif //__cplusplus

//
//Task 2 (ASM) Variables
//

//
//Task 3 (ASM) Variables
//

//
//Task 4 (ASM) Variables
//

//
//Task 5 (ASM) Variables
//

//
//Task 6 (ASM) Variables
//

//
//Task 7 (ASM) Variables
//

//
//Task 8 (ASM) Variables
//

//
//Common (ASM) Variables
//
uint16_t SampleCount;
uint16_t AdcBuf[ADC_BUF_LEN];
uint16_t AdcFiltBuf[ADC_BUF_LEN];
#if LOWPASS
float Coeffs[FILTER_LEN] = {0.0625L, 0.25L, 0.375L, 0.25L, 0.0625L};
#elif HIGHPASS
float Coeffs[FILTER_LEN] = {0.0625L, -0.25L, 0.375L, -0.25L, 0.0625L};
#endif

//
// Function Prototypes
//
void CLA_runTest(void);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);
void EPWM_initEpwm(void);
void ADC_initAdcA(void);
__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

//
// Start of main
//
void main(void)
{
    int16_t i;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. enable PWM1 and PWM2 and their GPIOs
//
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;

//
// For this case just init GPIO pins for ePWM1, ePWM2
// These functions are in the F2837xD_EPwm.c file
//
    InitEPwm1Gpio();
    InitEPwm2Gpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Step 4. Configure the CLA memory spaces first followed by
// the CLA task vectors. Force task 8.
//
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

//
// Force CLA task 8 using the IACK instruction
// Task 8 will initialize the filter input delay
// line to zero (X[0] - X[4]).
//
// No need to wait, the task will finish by the time
// we configure the ePWM and ADC modules
//
    Cla1ForceTask8();

//
// The CLA_configClaMemory wipes the message RAM so instead of
// global initialization, init A here
//
    for(i = 0; i < FILTER_LEN; i++)
    {
        A[i] = Coeffs[i];
    }

//
// Step 5. Configure the ADC to start sampling on an EPWM period
//
    ADC_initAdcA();

//
// Step 6. Configure EPWM to trigger ADC every 20us
//
    EPWM_initEpwm();

//
// Step 7. Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Step 8. Turn on the EPWM
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm1Regs.TBCTL.bit.CTRMODE = 0; //unfreeze, and enter up count mode
    EPwm2Regs.TBCTL.bit.CTRMODE = 0; //unfreeze, and enter up count mode
    EDIS;

//
// Step 9. Buffer till full
//
// The main CPU will receive an interrupt from the
// CLA each time task 7 (CLA FIR filter) completes
//
// In the meantime the main CPU can do other work
//
// After the CLA has fired ADC_BUF_LEN interrupts,
// the main CPU  will halt here
//
// You can view the results by graphing AdcBuf and
// AdcFiltBuf.  Both are unsigned int arrays.
//
    SampleCount = 0;
    for(;;)
    {
      if(SampleCount == ADC_BUF_LEN-1)
      {
          asm(" ESTOP0");
      }
    }
}

//
// CLA_configClaMemory - Configure CLA memory sections
//
void CLA_configClaMemory(void)
{
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;

    EALLOW;
#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
            (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

    //
    // Select LS4RAM and LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS4 and LS5 and then
    // set the space to be a program block
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 1;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1;

    EDIS;
}

//
// CLA_initCpu1Cla1 - Initialize CLA1 task vectors and end of task interrupts
//
void CLA_initCpu1Cla1(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    EALLOW;
    Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
    Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
    Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
    Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
    Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
    Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
    Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
    Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);

    //
    // Enable the IACK instruction to start a task on CLA in software
    // for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
    // subset of tasks) by writing to their respective bits in the
    // MIER register
    //
    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all = (M_INT8 | M_INT7);

    //
    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
    //
    PieVectTable.CLA1_1_INT = &cla1Isr1;
    PieVectTable.CLA1_2_INT = &cla1Isr2;
    PieVectTable.CLA1_3_INT = &cla1Isr3;
    PieVectTable.CLA1_4_INT = &cla1Isr4;
    PieVectTable.CLA1_5_INT = &cla1Isr5;
    PieVectTable.CLA1_6_INT = &cla1Isr6;
    PieVectTable.CLA1_7_INT = &cla1Isr7;
    PieVectTable.CLA1_8_INT = &cla1Isr8;

    //
    // Set the adca.1 as the trigger for task 7
    //
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK7 = 1;

    //
    // Enable CLA interrupts at the group and subgroup levels
    //
    PieCtrlRegs.PIEIER11.all = 0xFFFF;
    IER |= (M_INT11 );
    EDIS;
}

//
// EPWM_initEpwm - Initialize EPWM1 and EPWM2 settings
//
void EPWM_initEpwm(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;       // Turn off the EPWM clock
    EPwm1Regs.ETSEL.bit.SOCAEN    = 0;          // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL    = 4;         // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;             // Generate pulse on 1st event
    EPwm1Regs.CMPA.bit.CMPA = PWM1_DUTY_CYCLE;  // Set compare A value to 2000
                                                // counts
    EPwm1Regs.TBPRD = PWM1_PERIOD;              // Set period to 4000 counts
    EPwm1Regs.TBCTL.bit.CTRMODE = 3;            // freeze counter
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;             //enable SOCA
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;

    EPwm2Regs.ETSEL.bit.SOCAEN    = 0;          // Disable SOC on A group
    EPwm2Regs.CMPA.bit.CMPA = PWM2_DUTY_CYCLE;  // Set compare A value to 10000
                                                // counts
    EPwm2Regs.TBPRD = PWM2_PERIOD;              // Set period to 20000 counts
    EPwm2Regs.TBCTL.bit.CTRMODE = 3;            // freeze counter
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.PRD = AQ_CLEAR;

    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.PRD = AQ_CLEAR;

    EDIS;
}

//
// ADC_initAdcA - Initialize ADCA configurations and power it up
//
void ADC_initAdcA(void)
{
    uint16_t i;

    EALLOW;

    //
    //write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    //Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    //power up the ADC
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
    //delay for > 1ms to allow ADC time to power up
    //
    for(i = 0; i < 1000; i++)
    {
        asm("   RPT#255 || NOP");
    }

    //
    //Select the channels to convert and end of conversion flag ADCA
    //
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 99; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //trigger on ePWM1 SOCA/C
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; //end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    EDIS;
}

//
// cla1Isr1 - CLA1 ISR 1
//
__interrupt void cla1Isr1 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr2 - CLA1 ISR 2
//
__interrupt void cla1Isr2 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr3 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr4 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr5 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr6 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr7 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    //
    // Clear the ADC interrupt flag so the next SOC can occur
    // Clear the PIEACK bits so another interrupt can be taken
    //
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    PieCtrlRegs.PIEACK.all = (PIEACK_GROUP1 | PIEACK_GROUP11);

    //
    // Read the raw ADC RESULT1 register value and
    // put it into the AdcBuf buffer
    // This can be compared to the CLA filtered value
    //
    AdcBuf[SampleCount] = AdcaResultRegs.ADCRESULT0;

    //
    // Read the CLA filtered value and put it in the
    // AdcFiltBuf buffer
    //
    AdcFiltBuf[SampleCount] = voltFilt;

    //
    // Make sure that the buffer does not overflow
    // the buffer size.  If it is larger than ADC_BUF_LEN
    // then rewind back to the sample 0
    //
    SampleCount++;
    if( SampleCount == ADC_BUF_LEN )
    {
        SampleCount = 0;
    }

    //
    // Uncomment to halt debugger here
    //
//    asm(" ESTOP0");
}

//
// cla1Isr8 - CLA1 ISR 8
//
__interrupt void cla1Isr8 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 8
    //
    PieCtrlRegs.PIEACK.all = M_INT11;

    //
    // Uncomment to halt debugger here
    //
//    asm(" ESTOP0");
}

// End of File
