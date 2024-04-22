//#############################################################################
//
//! \file   dsp_examples_setup.c
//!
//! \brief  DSP Examples Common Code
//! \author Ritvik Sadana
//! \date   Jan 8, 2018
//
//  Group:          C2000

//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"
#include "sysctl.h"
#include "fpu.h"


//*****************************************************************************
// the defines
//*****************************************************************************
#if defined(ADC_INPUT)
#define TEST_SIZE       (256U) //must be same as dsp_rfft_adc.c
							   //fpu32 examples, set to 512U
                               //fpu64 examples, set to 512U
#endif //defined(ADC_INPUT)

//*****************************************************************************
// the globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("FpuRegsFile")
#else
#pragma DATA_SECTION(FpuRegs,"FpuRegsFile");
#endif
//! \brief FPU Register object
//
volatile struct FPU_REG FpuRegs;

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// DSP_Example_setupSysCtrl()
//=============================================================================
void DSP_Example_setupSysCtrl( void )
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Set up PLL control and clock dividers
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
/*
    NOTE: This section needs to be uncommented if the examples are using the CM
    //
    // Set up AUXPLL control and clock dividers needed for CMCLK
    //
    SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG);

    //
    // Set up CMCLK to use AUXPLL as the clock source and set the
    // clock divider to 1.
    //
    SysCtl_setCMClk(SYSCTL_CMCLKOUT_DIV_1,SYSCTL_SOURCE_AUXPLL);
    //
*/
    // Enable Peripherals
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);


}

//=============================================================================
// DSP_Example_initGPIO()
//=============================================================================
void DSP_Example_initGPIO(void)
{
    //
    // Disable pin locks.
    //
   GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
  //  GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF); //Needs to be uncommented out for f2838x
}

//=============================================================================
// DSP_Example_setupFlash()
//=============================================================================
void DSP_Example_setupFlash( void )
{
#if defined(_FLASH)
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);

    //
    // Copy FPU FFT Tables from Flash to RAM (for FFT examples)
    //
    // The FPUfftTablesRunStart, FPUfftTablesLoadStart and
    // FPUfftTablesLoadSize symbols are created by the linker. Refer to the
    // device .cmd file.
    //
#if defined(__TMS320C28XX_FPU64__)
    memcpy(&FPU64fftTablesRunStart, &FPU64fftTablesLoadStart,
            (uint32_t)&FPU64fftTablesLoadSize);
#else
    memcpy(&FPUfftTablesRunStart, &FPUfftTablesLoadStart,
                (uint32_t)&FPUfftTablesLoadSize);
#endif

    //
    // Copy FPU Math Tables from Flash to RAM (for FFT examples)
    //
    // The FPUmathTablesRunStart, FPUmathTablesLoadStart and
    // FPUmathTablesLoadSize symbols are created by the linker. Refer to the
    // device .cmd file.
    //
#if defined(__TMS320C28XX_FPU64__)
    memcpy(&FPU64mathTablesRunStart, &FPU64mathTablesLoadStart,
            (uint32_t)&FPU64mathTablesLoadSize);
#else
    memcpy(&FPUmathTablesRunStart, &FPUmathTablesLoadStart,
                (uint32_t)&FPUmathTablesLoadSize);
#endif

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif //defined(_FLASH)
}

//=============================================================================
// DSP_Example_initADCA()
//=============================================================================
void DSP_Example_initADCA(void)
{
#if USE_REAL_ADC_INPUT == 1U
    //
    // Enable internal reference on ADCs; only available for certain devices
    // (check your device technical reference manual for more information)
    //
    //ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    //ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    //ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
//
//    //
//    // Set pulse positions to late
//    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
//
//    //
//    // Power up the ADCs and then delay for 1 ms
//    //
    ADC_enableConverter(ADCA_BASE);
//
    DEVICE_DELAY_US(1000);
#endif
}

//=============================================================================
// DSP_Example_initADCSOC()
//=============================================================================
void DSP_Example_initADCSOC( void )
{
#if USE_REAL_ADC_INPUT == 1U
    //
    // Configure SOC0 of ADCA
    // - SOC0 will be triggered by EPWM1SOCA
    // - SOC0 will convert pin A0 with a sample window of 100 SYSCLK cycles.
    // - EOC0 will be generated at the end of conversion
    // - SOC0 will sample on each trigger regardless of the interrupt flag
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, 100);
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);
//
//    //
//    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
//    // sure its flag is cleared.
//    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
#endif
}
//=============================================================================
// DSP_Example_initEPWM()
//=============================================================================
void DSP_Example_initEPWM(void)
{
#if USE_REAL_ADC_INPUT == 1U
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK/(2*(4*8))
    // - have a period of EPWM1_PERIOD
    // - run in count up mode
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_4,
                           EPWM_HSCLOCK_DIVIDER_8);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
//
//    //
//    // Enable SOC-A and set it to assert when the counter hits
//    // zero. It asserts on every event
//    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1U);
//
//    //
//    // EPWM1 should toggle each time its counter hits zero
//    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
            EPWM_AQ_OUTPUT_TOGGLE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
//
//    //
//    // Set up EPWM2 to
//    // - run on a base clock of SYSCLK/(2*(4*8))
//    // - have a period of EPWM2_PERIOD
//    // - run in count up/down mode
//    // - have its CMPA value set for a 50% duty cycle
//    //
    EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_4,
                           EPWM_HSCLOCK_DIVIDER_8);
    EPWM_setTimeBasePeriod(EPWM2_BASE, EPWM2_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);
    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A,
            EPWM2_DUTY_CYCLE);
//
//    //
//    // On compare A, when counting up, pull the EPWM A output high
//    // On compare A, when counting down, pull the EPWM A output low
//    //
    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_A,
            EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_A,
                EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // EPWM 1 and 2 should run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    EPWM_setEmulationMode(EPWM2_BASE, EPWM_EMULATION_FREE_RUN);
#endif
}

//=============================================================================
// DSP_Example_adcaIsr()
//=============================================================================
__interrupt void DSP_Example_adcaIsr()
{
#if USE_REAL_ADC_INPUT == 1U
	test_input[sampleIndex++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
//
//
    if(sampleIndex == TEST_SIZE){
        sampleIndex    = 0;
        flagInputReady = 1;
    }


    //
    // clear INT1 flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
#endif //ADC_INPUT
}

//=============================================================================
// done()
//=============================================================================
void done( void )
{
    for(;;);
}

//=============================================================================
// __error__()
//=============================================================================
void __error__(const char *filename, uint32_t line)
{
    __asm(" ESTOP0");
}

// End of File
