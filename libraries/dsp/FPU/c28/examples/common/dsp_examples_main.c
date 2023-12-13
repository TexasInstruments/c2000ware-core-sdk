//#############################################################################
//
//! \file   dsp_examples_main.c
//!
//! \brief  DSP Examples - The main()
//! \author Ritvik Sadana
//! \date   Jan 8, 2018
//
//  Group:          C2000

//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"

//*****************************************************************************
// the globals
//*****************************************************************************

//*****************************************************************************
// the function definitions
//*****************************************************************************
int main(void)
{
#if defined(_FLASH)
    //
    // Setup the FLASH Banks
    //
    DSP_Example_setupFlash();
#endif //defined(_FLASH)

    //
    // Setup system clocking
    //
    DSP_Example_setupSysCtrl();



#if USE_REAL_ADC_INPUT == 1U
    //
    // Initialize device clock and peripherals
    //
    DSP_Example_initGPIO();

    //
    // GPIO0 is set to EPWM1A
    //
  // GPIO_setMasterCore(0, GPIO_CORE_CPU1); //This needs to be uncommented for dual core devices.
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);

    //
    // GPIO2 is set to EPWM2A
    //
 //   GPIO_setMasterCore(2, GPIO_CORE_CPU1); //This needs to be uncommented for dual core devices.
    GPIO_setPadConfig(2,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2A);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Map the ISR to the ADC EOC interrupt
    //
    Interrupt_register(INT_ADCA1, DSP_Example_adcaIsr);

    //
    // Setup ADC-A
    //
    DSP_Example_initADCA();
    DSP_Example_initADCSOC();

    //
    // Setup EPWM1A as the sampling clock, EPWM2A as the signal to be sampled
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    DSP_Example_initEPWM(); 
    
    //
    // Enable the interrupts in the PIE: Group 1 interrupt 1.
    //
    Interrupt_enable(INT_ADCA1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

#endif // USE_REAL_ADC_INPUT == 1

    //
    // Run the test
    //
    DSP_runTest();
    
    // 
    //
    // End Test - loop forever
    //
    done();
    
    //
    // Code does not get to this point
    //
    return(1);
}

// End of File
