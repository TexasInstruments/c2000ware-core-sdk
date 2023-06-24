//#############################################################################
//
// FILE:   pga_ex1_dac_adc_ext_loopback.c
//
// TITLE:   PGA DAC-ADC External Loopback Example.
//
//! \addtogroup driver_example_list
//! <h1>PGA DAC-ADC External Loopback Example</h1>
//!
//! This example generates 400 mV using the DAC output (it uses an internal
//! voltage reference). The output of the DAC is externally connected to PGA2
//! for a 3x gain amplification. It uses two ADC channels to sample the
//! DAC output and the amplified voltage output from PGA2. The ADC is connected
//! to these signals internally.
//!
//! \b External \b Connections on Control Card\n
//!  - Connect DACA_OUT (Analog Pin A0) to PGA2_IN (Pin 21 on HSEC connector of
//!  - ControlCard)
//!  - Connect PGA246NEG to GND
//!
//! \b External \b Connections on Launchpad\n
//!  - Connect DACA_OUT (Analog Pin A0) to PGA2_IN (Analog Pin A3).
//!  - Connect PGA246NEG to GND
//!
//! \b Watch \b Variables \n
//!  - \b dacResult - The DAC output voltage.
//!  - \b pgaResult - The amplified DAC voltage.
//!  - \b pgaGain   - The ratio of the amplified DAC voltage to the original
//!                   DAC output. This should always read a value of ~3.0.
//!
//
//#############################################################################
// $TI Release:
// $Release Date:
// $Copyright:
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
volatile uint16_t dacResult;
volatile uint16_t pgaResult;
float pgaGain;

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

	Board_init();

	//
	// Enable Global Interrupt (INTM) and real time interrupt (DBGM)
	//
	EINT;
	ERTM;

	//
	// Force ADC conversion
	//
    ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
    ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Check if conversion is complete
	    //
	    if(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1))
	    {
	        //
	        // Acknowledge flag
	        //
	        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

	        dacResult = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0);
	        pgaResult = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1);
	        pgaGain   = (float)pgaResult / (float)dacResult;

	        //
	        // Force ADC conversion
	        //
	        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
	        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);
	    }
	}
}

//
// End of File
//
