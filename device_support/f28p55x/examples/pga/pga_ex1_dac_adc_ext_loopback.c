//#############################################################################
//
// FILE:   pga_ex1_dac_adc_ext_loopback.c
//
// TITLE:   PGA DAC-ADC External Loopback Example.
//
//! \addtogroup bitfield_example_list
//! <h1>PGA DAC-ADC External Loopback Example</h1>
//!
//! This example generates 400 mV using the DAC output (it uses an internal
//! voltage reference). The output of the DAC is externally connected to PGA1
//! for a 4x gain amplification. It uses two ADC channels to sample the
//! DAC output and the amplified voltage output from PGA1. The ADC is connected
//! to these signals internally.
//!
//! \b External \b Connections \n
//!  - Connect DACA_OUT (Analog Pin A0) to PGA2_INP (Analog Pin A2).
//!  - Connect PGA1_INM (Analog Pin A3) to GND
//!
//! \b Watch \b Variables \n
//!  - \b dacResult - The DAC output voltage.
//!  - \b pgaResult - The amplified DAC voltage.
//!  - \b pgaGain   - The ratio of the amplified DAC voltage to the original
//!                   DAC output. This should always read a value of ~4.0.
//!
//
//#############################################################################
// $Copyright:
//#############################################################################

//
// Included Files
//
#include "F28x_Project.h"

//
// Globals
//
volatile uint16_t dacResult;
volatile uint16_t pgaResult;
float pgaGain;

//
// Function Prototypes
//
void initPGA(void);
void initDAC(void);
void initADC(void);
void initADCSOC(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();

    //
    // Configure PGA1_INP as AGPIO 
    //
    EALLOW;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 1;
    EDIS;

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
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
    //
    InitPieVectTable();

    //
    // Initialize PGA, DAC, and ADC
    //
    initPGA();

    initDAC();
    DacaRegs.DACVALS.all = 500;

    initADC();
    initADCSOC();

    DELAY_US(3000);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Force ADC conversion
    //
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;
    AdcaRegs.ADCSOCFRC1.bit.SOC1 = 1;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Check if conversion is complete
        //
        if(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 1)
        {
            //
            // Acknowledge flag
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

            dacResult = AdcaResultRegs.ADCRESULT0;
            pgaResult = AdcaResultRegs.ADCRESULT1;
            pgaGain   = (float)pgaResult / (float)dacResult;

            //
            // Force ADC conversion
            //
            AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;
            AdcaRegs.ADCSOCFRC1.bit.SOC1 = 1;
        }
    }
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Set the voltage reference
    //
    // NOTE:
    // VREFHI pin must not be driven by an external reference
    // voltage. Disconnect any external reference before proceeding
    //
    ESTOP0;
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

    EALLOW;

    //
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADC and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    EDIS;

    DELAY_US(1000);
}

//
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by ePWM1.
//
void initADCSOC(void)
{
    //
    // Select the channels to convert and the end of conversion flag
    //
    EALLOW;

    //
    // Convert DACA output
    //
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;     // SOC0 will convert A0 (DACA_OUT)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0;   // Trigger by software

    //
    // Convert PGA1 output
    //
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 14;    // SOC1 will convert A14 (PGA1_OUT)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0;   // Trigger by software

    //
    // Configure ADC interrupt status flags
    //
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 1; // End of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   // Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    EDIS;
}

//
// initDAC - Configure DAC
//
void initDAC(void)
{
    EALLOW;

    //
    // Set the DAC gain to 2
    //
    DacaRegs.DACCTL.bit.MODE = 1;

    //
    // Use ADC voltage reference
    //
    DacaRegs.DACCTL.bit.DACREFSEL = 1;

    //
    // Load count value for DAC on next SYSCLK
    //
    DacaRegs.DACCTL.bit.LOADMODE = 0;

    //
    // Enable DAC output
    //
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;

    EDIS;
}

//
// initPGA - Configure PGA1 gain
//
void initPGA(void)
{
    EALLOW;

    //
    // Set the PGA mode
    //
    Pga1Regs.MUXSEL.bit.PMUXSEL = 0;
    Pga1Regs.MUXSEL.bit.NMUXSEL = 1;
    Pga1Regs.MUXSEL.bit.MMUXSEL = 1;

    //
    // Set a gain of 4 to PGA1
    //
    Pga1Regs.PGACTL.bit.GAIN = 2;

    //
    // No filter resistor for output
    //
    Pga1Regs.PGACTL.bit.FILT_RES_SEL = 0;

    //
    // Enable PGA1
    //
    Pga1Regs.PGACTL.bit.PGAEN = 1;

    Pga1Regs.PGACTL.bit.PGA_OUTENABLE = 1;
    Pga1Regs.PGACTL.bit.PGA_OUTEN_INTGAIN = 1;

    EDIS;
}

//
// End of File
//
