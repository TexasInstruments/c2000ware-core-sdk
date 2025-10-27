//###########################################################################
//
// FILE:   adc_ex1_epwm_input_cpu2.c
//
// TITLE:  Example to demonstrate ADCA and EPWM1 on CPU2
//
// This example demonstrates how to make use of the ADC and EPWM peripherals
// from CPU2.  Device clocking (PLL) and GPIO setup are done using CPU1,
// while all other configuration of the peripherals is done using CPU2.
//
// CPU2 configures EPWM1 in up count mode in a similar fashion to what is
// done in the epwm_up_aq example.  The ADC is configured in continuous
// conversion mode similar to the adc_soc_continuous example.  GPIO0 can be
// connected to ADCINA0 and the results buffer AdcaResults graphed in CCS to
// view the duty cycle of the generated waveform.
//
//###########################################################################
// 
// C2000Ware v6.00.01.00
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

//
// Included Files
//
#include "f28x_project.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256   // buffer for storing conversion results
                                      // (size must be multiple of 16)
#define EPWM1_TIMER_TBPRD       4096  // Period register
#define EPWM1_MAX_CMPA          4050
#define EPWM1_MIN_CMPA          50
#define EPWM1_MAX_CMPB          4050
#define EPWM1_MIN_CMPB          50
#define EPWM_CMP_UP             1
#define EPWM_CMP_DOWN           0

//
// Globals
//
Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
Uint16 resultsIndex;

typedef struct
{
    volatile struct EPWM_REGS *EPwmRegHandle;
    Uint16 EPwm_CMPA_Direction;
    Uint16 EPwm_CMPB_Direction;
    Uint16 EPwmTimerIntCount;
    Uint16 EPwmMaxCMPA;
    Uint16 EPwmMinCMPA;
    Uint16 EPwmMaxCMPB;
    Uint16 EPwmMinCMPB;
}EPWM_INFO;

EPWM_INFO epwm1_info;

//
// Function Prototypes
//
void ConfigureADC(void);
void SetupADCContinuous(Uint16 channel);
void InitEPwm1Example(void);
__interrupt void epwm1_isr(void);
void update_compare(EPWM_INFO*);

//
// Main
//
void main(void)
{
    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2838x_sysctrl.c file.
    //
    InitSysCtrl();

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2838x_piectrl.c file.
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
    // The shell ISR routines are found in f2838x_defaultisr.c.
    // This function is found in f2838x_pievect.c.
    //
    InitPieVectTable();

    //
    // Register the EPWM interrupt handler for EPWM1
    //
    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_isr;
    EDIS;

    //
    // Configure the ADC and power it up
    //
    ConfigureADC();

    //
    // Setup the ADC for continuous conversions on channel 0
    //
    SetupADCContinuous(0);

    //
    // Configure EPWM1
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Enable CPU INT3 which is connected to EPWM1 INT:
    //
    IER |= M_INT3;

    //
    // Enable EPWM INTn in the PIE: Group 3 interrupt 1
    //
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        AdcaResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

    EALLOW;

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Enable ADCINT flags
        //
        AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
        AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;
        AdcaRegs.ADCINTSEL3N4.bit.INT3E = 1;
        AdcaRegs.ADCINTSEL3N4.bit.INT4E = 1;
        AdcaRegs.ADCINTFLGCLR.all = 0x000F;

        //
        // Initialize results index
        //
        resultsIndex = 0;

        //
        // Software force start SOC0 to SOC7
        //
        AdcaRegs.ADCSOCFRC1.all = 0x00FF;

        //
        // Keep taking samples until the results buffer is full
        //
        while(resultsIndex < RESULTS_BUFFER_SIZE)
        {
            //
            // Wait for first set of 8 conversions to complete
            //
            while(0 == AdcaRegs.ADCINTFLG.bit.ADCINT3);

            //
            // Clear both INT flags generated by first 8 conversions
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT3 = 1;

            //
            // Save results for first 8 conversions
            //
            // Note that during this time, the second 8 conversions have
            // already been triggered by EOC6->ADCIN1 and will be actively
            // converting while first 8 results are being saved
            //
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT0;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT1;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT2;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT3;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT4;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT5;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT6;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT7;

            //
            // Wait for the second set of 8 conversions to complete
            //
            while(0 == AdcaRegs.ADCINTFLG.bit.ADCINT4);

            //
            // Clear both INT flags generated by second 8 conversions
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT4 = 1;

            //
            // Save results for second 8 conversions
            //
            // Note that during this time, the first 8 conversions have
            // already been triggered by EOC14->ADCIN2 and will be actively
            // converting while second 8 results are being saved
            //
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT8;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT9;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT10;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT11;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT12;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT13;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT14;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT15;
        }

        //
        // Disable all ADCINT flags to stop sampling
        //
        AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0;
        AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0;
        AdcaRegs.ADCINTSEL3N4.bit.INT3E = 0;
        AdcaRegs.ADCINTSEL3N4.bit.INT4E = 0;

        //
        // At this point, AdcaResults[] contains a sequence of conversions
        // from the selected channel
        //

//        //
//        // Software breakpoint, hit run again to get updated conversions
//        //
//        asm("   ESTOP0");
        DELAY_US(1000);
    }while(1);
}

//
// epwm1_isr - Update compare values and acknowledge interrupt
//
__interrupt void epwm1_isr(void)
{
    //
    // Update the CMPA and CMPB values
    //
    update_compare(&epwm1_info);

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// InitEPwm1Example - Configure EPWM1 settings
//
void InitEPwm1Example()
{
   //
   // Setup TBCLK
   //
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
   EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;   // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV2;

   //
   // Setup shadow register load on ZERO
   //
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm1Regs.CMPA.bit.CMPA = EPWM1_MIN_CMPA;     // Set compare A value
   EPwm1Regs.CMPB.bit.CMPB = EPWM1_MIN_CMPB;     // Set Compare B value

   //
   // Set actions
   //
   EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;      // Set PWM1A on Zero
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;    // Clear PWM1A on event A, up count

   EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;      // Set PWM1B on Zero
   EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;    // Clear PWM1B on event B, up count

   //
   // Interrupt where we will change the Compare Values
   //
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct ePWM registers
   //
   epwm1_info.EPwm_CMPA_Direction = EPWM_CMP_UP;
   epwm1_info.EPwm_CMPB_Direction = EPWM_CMP_UP;
   epwm1_info.EPwmTimerIntCount = 0;      // Zero the interrupt counter
   epwm1_info.EPwmRegHandle = &EPwm1Regs; // Set the pointer to the ePWM module
   epwm1_info.EPwmMaxCMPA = EPWM1_MAX_CMPA; // Setup min/max CMPA/CMPB values
   epwm1_info.EPwmMinCMPA = EPWM1_MIN_CMPA;
   epwm1_info.EPwmMaxCMPB = EPWM1_MAX_CMPB;
   epwm1_info.EPwmMinCMPB = EPWM1_MIN_CMPB;
}

//
// ConfigureADC - Write ADC configurations and power up the ADC for
//                both ADC A and ADC B
//
void ConfigureADC(void)
{
    EALLOW;

    //
    // Write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADC
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
    // Delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);

    EDIS;
}

//
// SetupADCContinuous - Setup the ADC to continuously convert on one channel
//
void SetupADCContinuous(Uint16 channel)
{
    Uint16 acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else // resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC1CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC2CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC3CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC4CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC5CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC6CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC7CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC8CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC9CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC10CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC11CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC12CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC13CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC14CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC15CTL.bit.CHSEL = channel;  //SOC will convert on channel

    AdcaRegs.ADCSOC0CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC6CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC7CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC9CTL.bit.ACQPS  = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC10CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC11CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC12CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC13CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC14CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles
    AdcaRegs.ADCSOC15CTL.bit.ACQPS = acqps; //sample is acqps + 1 SYSCLK cycles

    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0; //disable INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0; //disable INT2 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT3E = 0; //disable INT3 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT4E = 0; //disable INT4 flag

    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    AdcaRegs.ADCINTSEL3N4.bit.INT3CONT = 0;
    AdcaRegs.ADCINTSEL3N4.bit.INT4CONT = 0;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 6;  //end of SOC6 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 14; //end of SOC14 will set INT2 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT3SEL = 7;  //end of SOC7 will set INT3 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT4SEL = 15; //end of SOC15 will set INT4 flag

    //
    // ADCINT2 will trigger first 8 SOCs
    //
    AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC2 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC3 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC4 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC5 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC6 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC7 = 2;

    //
    // ADCINT1 will trigger second 8 SOCs
    //
    AdcaRegs.ADCINTSOCSEL2.bit.SOC8 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC9 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC15 = 1;
}

//
// update_compare - Update compare values
//
void update_compare(EPWM_INFO *epwm_info)
{
   //
   // Every 10'th interrupt, change the CMPA/CMPB values
   //
   if(epwm_info->EPwmTimerIntCount == 10)
   {
       epwm_info->EPwmTimerIntCount = 0;

       //
       // If we were increasing CMPA, check to see if
       // we reached the max value.  If not, increase CMPA
       // else, change directions and decrease CMPA
       //
       if(epwm_info->EPwm_CMPA_Direction == EPWM_CMP_UP)
       {
           if(epwm_info->EPwmRegHandle->CMPA.bit.CMPA < epwm_info->EPwmMaxCMPA)
           {
              epwm_info->EPwmRegHandle->CMPA.bit.CMPA++;
           }
           else
           {
              epwm_info->EPwm_CMPA_Direction = EPWM_CMP_DOWN;
              epwm_info->EPwmRegHandle->CMPA.bit.CMPA--;
           }
       }

       //
       // If we were decreasing CMPA, check to see if
       // we reached the min value.  If not, decrease CMPA
       // else, change directions and increase CMPA
       //
       else
       {
           if(epwm_info->EPwmRegHandle->CMPA.bit.CMPA == epwm_info->EPwmMinCMPA)
           {
              epwm_info->EPwm_CMPA_Direction = EPWM_CMP_UP;
              epwm_info->EPwmRegHandle->CMPA.bit.CMPA++;
           }
           else
           {
              epwm_info->EPwmRegHandle->CMPA.bit.CMPA--;
           }
       }

       //
       // If we were increasing CMPB, check to see if
       // we reached the max value.  If not, increase CMPB
       // else, change directions and decrease CMPB
       //
       if(epwm_info->EPwm_CMPB_Direction == EPWM_CMP_UP)
       {
           if(epwm_info->EPwmRegHandle->CMPB.bit.CMPB < epwm_info->EPwmMaxCMPB)
           {
              epwm_info->EPwmRegHandle->CMPB.bit.CMPB++;
           }
           else
           {
              epwm_info->EPwm_CMPB_Direction = EPWM_CMP_DOWN;
              epwm_info->EPwmRegHandle->CMPB.bit.CMPB--;
           }
       }

       //
       // If we were decreasing CMPB, check to see if
       // we reached the min value.  If not, decrease CMPB
       // else, change directions and increase CMPB
       //
       else
       {
           if(epwm_info->EPwmRegHandle->CMPB.bit.CMPB == epwm_info->EPwmMinCMPB)
           {
              epwm_info->EPwm_CMPB_Direction = EPWM_CMP_UP;
              epwm_info->EPwmRegHandle->CMPB.bit.CMPB++;
           }
           else
           {
              epwm_info->EPwmRegHandle->CMPB.bit.CMPB--;
           }
       }
   }
   else
   {
      epwm_info->EPwmTimerIntCount++;
   }

   return;
}

//
// End of file
//
