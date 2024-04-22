#ifndef _DSP_EXAMPLES_SETUP_H_
#define _DSP_EXAMPLES_SETUP_H_
//#############################################################################
//
//! \file   dsp_examples_setup.h
//!
//! \brief  DSP Examples Common Code
//! \author Vishal Coelho
//! \date   Jan 8, 2016
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
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "device.h"
#include "inc/hw_types.h"

//!
//! \defgroup DSP_EXAMPLES_SETUP DSP Examples Setup Code

//!
//! \ingroup DSP_EXAMPLES_SETUP
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
//For f2838x, EPWM_CLK = DEVICE_SYSCLK_FREQ/2. For f28002x, EPWM_CLK = DEVICE_SYSCLK_FRE//shNTY DD IFDEF
#ifndef f2838x
#define EPWM_CLK            DEVICE_SYSCLK_FREQ
#else
#define EPWM_CLK            DEVICE_SYSCLK_FREQ/2
#endif

#define EPWM_CLKDIV         32UL        // TBCTL_CLKDIV(4)*TBCTL_HSPCLKDIV(8)

#define EPWM1_FREQ          10000UL
#define EPWM2_FREQ          1000UL
#define EPWM1_PERIOD        (uint16_t)(EPWM_CLK/(EPWM_CLKDIV*EPWM1_FREQ))
#define EPWM2_PERIOD        (uint16_t)(EPWM_CLK/(2UL*EPWM_CLKDIV*EPWM2_FREQ))
#define EPWM2_DUTY_CYCLE    (EPWM2_PERIOD/2)

#define USE_REAL_ADC_INPUT  0U

#if USE_REAL_ADC_INPUT == 1U
#define ADC_INPUT 1
#endif //defined(USE_REAL_ADC_INPUT)

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************
#if defined(_FLASH)
extern uint16_t RamfuncsRunStart, RamfuncsLoadStart, RamfuncsLoadSize;
#if defined(__TMS320C28XX_FPU64__)
extern uint16_t FPU64fftTablesRunStart, FPU64fftTablesLoadStart,
                FPU64fftTablesLoadSize;
extern uint16_t FPU64mathTablesRunStart, FPU64mathTablesLoadStart,
                FPU64mathTablesLoadSize;
#else
extern uint16_t FPUfftTablesRunStart, FPUfftTablesLoadStart,
                FPUfftTablesLoadSize;
extern uint16_t FPUmathTablesRunStart, FPUmathTablesLoadStart,
                FPUmathTablesLoadSize;
#endif
#endif //defined(_FLASH)

// Each test will define these variables
extern uint16_t pass, fail;
#if defined(__TMS320C28XX_FPU64__)
extern float64_t tolerance;
extern uint64_t toleranceLSBMantissa;
#if defined(ADC_INPUT)
extern uint16_t test_input[];
#else
extern float64_t test_input[];
#endif //defined(ADC_INPUT)
extern const float64_t test_golden[];
extern float64_t test_output[];
extern float64_t test_error[];
#elif defined (__TMS320C28XX_FPU32__)
extern float tolerance;
extern uint32_t toleranceLSBMantissa;
#if defined(ADC_INPUT)
extern uint16_t test_input[];
#else
extern float test_input[];
#endif //defined(ADC_INPUT)
extern const float test_golden[];
extern float test_output[];
extern float test_error[];
#else
#error "--float_support=fpu64 option must be set to build the FPU64        \
    version of the library. --float_support=fpu32 must be set to build the \
    FPU32 version of the DSP library"
#endif

#if defined(ADC_INPUT)
// Used in the RFFT ADC examples
//
// Flag to signal the ADC has finished sampling, and storing, 
// N points in the FFT input buffer
extern volatile uint16_t flagInputReady;

// Index into the FFT input buffer
extern volatile uint16_t sampleIndex;

// Maximum Frequency component index
extern uint32_t max_idx;
#endif// ADC_INPUT
//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup system controls
//! 
extern void DSP_Example_setupSysCtrl( void );

//! \brief Function to disable pin locks and enable pullups on GPIOs.
//!
extern void DSP_Example_initGPIO(void);

//! \brief Setup flash
//! 
extern void DSP_Example_setupFlash( void );

//! \brief Run a particular Fast RTS routine
//! 
extern void DSP_runTest( void );

//! \brief Initialize ADCA
//! Function to configure and power up ADC A
//
void DSP_Example_initADCA(void);

//! \breif ADC SOC Initialization
//!
//! This function will configure the ADC, channel A0 to start its conversion
//! on a trigger from EPWM1 (EPMW1SOCA). The ADC will sample this channel
//! continuously. After each conversion it will assert ADCINT1, which
//! is then used to trigger task 1 of the CLA (the filter)
//
void DSP_Example_initADCSOC(void);

//! \brief EPWM Initialization
//!
//!  EPWM1A will run at EPWM1_FREQ Hz and serves as the sampling
//!  clock for ADC channel A1 which will be sampling the slower running EPWM2A
//!  (at EPWM2_FREQ Hz). The default time base for the EPWM module is half the
//!  system clock i.e.
//!        TBCLK = SYSCLKOUT/2
//!  EPWM1A will be setup in count-up mode and an event generated every period
//!  this event will trigger the ADC to start sampling on channel A1
//!  EPWM2A is setup for updown count mode with CMPA level at the half period
//!  point giving a 50% duty cycle square wave at EPWM2_FREQ Hz
//!  For a desired PWM frequency F_pwm (1/T_pwm), we have
//!        T_pwm = 2 x TBPRD / TBCLK
//!        TBPRD = TBCLK/(2*F_pwm)
//!  For e.g. F_pwm = 10KHz, TBCLK = 50e6
//!        TBPRD = 50e6/(2*10e3)
//!              = 2500
//!  For e.g. F_pwm = 1KHz, TBCLK = 50e6
//!        TBPRD = 50e6/(2*1e3)
//!              = 25000
//!  For e.g. F_pwm = 100Hz, TBCLK = 50e6
//!        TBPRD = 50e6/(2*1e2)
//!              = 250000
//
void DSP_Example_initEPWM(void);

//! \brief ADC Interrupt Service Routine
//! The ISR will store each sampled value in the FFT buffer, and
//! raise the flag once the buffer is full
//!
__interrupt void DSP_Example_adcaIsr()

#if __TI_COMPILER_VERSION__ >= 15009000
  __attribute__((section(".TI.ramfunc")));
#else
  __attribute__((section(".ramfuncs")));
#endif

#if defined(__TMS320C28XX_FPU64__)
//! \brief Error calculation
//!
//! This function computes the double precision error between the output
//! obtained from running one of the library routines on the target
//! devices and the golden reference obtained from running a similar
//! routine in MATLAB on an x86 platform.
//!
//! The error is stored to an array and then compared against a user provided
//! tolerance value. If the error is found to be within bounds the function
//! returns a 1, else a -1. It also calculates how many ULPs of difference
//! exist between the output and golden and returns it in a user passed
//! variable. If the ULPs are within tolerance the function returns 2
//!
//! \param[in]  p_out , pointer to the calculated output
//! \param[in]  p_gold , pointer to the golden reference
//! \param[out] p_lderr , pointer to the double precision error
//! \param[out] p_ullerr , pointer to the unsigned long long error
//! \param[in]  ldtol , double precision tolerance
//! \param[in]  ulltol , Erroneous ULPs
//!
//! \returns
//! - 1  , if the double precision error is within tolerable limits
//! - 2  , additionally if the ULP of the error is withing limits
//! - -1 , if either check fails
//!
int16_t DSP_Example_calcError(const float64_t *p_out,
                              const float64_t *p_gold,
                              const float64_t *p_lderr,
                              const uint64_t  *p_ullerr,
                              const float64_t *p_ldtol,
                              const uint64_t  ulltol);
#endif //__TMS320C28XX_FPU64__

//! \brief Function indicating end of test (Autobot regression)
//!
extern void done( void );

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _DSP_EXAMPLES_SETUP_H_ definition

// End of File
