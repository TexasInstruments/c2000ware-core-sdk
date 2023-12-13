//#############################################################################
//! \file /2837x_FIR/main.c
//!
//! \brief  Demo code for the Finite Impulse Response Filter
//! \author Vishal Coelho
//! \date   03/24/2015
//! 
//! This example demonstrates the FIR filter module
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "fpu_filter.h"
#include "math.h"
#include "examples_setup.h"

//!
//! \addtogroup FIR_EXAMPLES Finite Impulse Response Filter

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define FIR_ORDER       63              // ORDER = NUM_TAPS - 1    
#define SIGNAL_LENGTH   (FIR_ORDER+1)* 4 
#define EPSILON         0.1
//*****************************************************************************
// globals
//***************************************************************************** 
#ifdef __cplusplus
#pragma DATA_SECTION("firldb")
#else
#pragma DATA_SECTION(dbuffer, "firldb")
#endif //__cplusplus
//! \brief The Delay buffer for the filter
//! 
float dbuffer[FIR_ORDER+1];

#ifdef __cplusplus
#pragma DATA_SECTION("sigIn");
#else
#pragma DATA_SECTION(sigIn, "sigIn");
#endif //__cplusplus
//! \brief Input signal
//!
float sigIn[SIGNAL_LENGTH];

#ifdef __cplusplus
#pragma DATA_SECTION("sigOut");  
#else
#pragma DATA_SECTION(sigOut, "sigOut");  
#endif //__cplusplus
//! \brief Output signal
//! 
float sigOut[SIGNAL_LENGTH];
         
#ifdef __cplusplus
#pragma DATA_SECTION("coefffilt");
#else
#pragma DATA_SECTION(coeff, "coefffilt");
#endif //__cplusplus
//! \brief Co-efficient Array
//! \note For best performance in standalone mode, the user
//! is encouraged to copy these coefficient from FLASH to RAM
//! at runtime
float const coeff[FIR_ORDER+1]= {
#include "coeffs.h"
};

float FIRgoldenOut[SIGNAL_LENGTH] = {
    #include "data_output.h"
};

// 
// Calculating a digital frequency
// Let sampling frequency = 1MHz
// primary signal @ 10KHz and a secondary signal @ 40KHz
// Therefore k1 = 1K/100k = 0.01
//           k2 = 33K/100k = 0.33
// composite signal = 1/2(sin(2*pi*i*k1) + sin(2*pi*i*k2))
//                  = 1/2(sin(0.062831853071 * i) + sin(2.073451151*i))
// 
float    RadStep  = 0.062831853071f;     
float    RadStep2 = 2.073451151f;
float    Rad      = 0.0f;
float    Rad2     = 0.0f;

#ifdef __cplusplus
#pragma DATA_SECTION("firfilt")
#else
#pragma DATA_SECTION(firFP, "firfilt")
#endif //__cplusplus
//! \brief Object of the structure FIR_FP
//! 
FIR_FP  firFP = FIR_FP_DEFAULTS;

//! \brief Handle to the FIR_FP object                                   
//!
FIR_FP_Handle hnd_firFP = &firFP;

//! \brief Linker variables related to the "coefffilt" section
//!
extern uint16_t CoeffFiltRunStart, CoeffFiltLoadStart, CoeffFiltLoadSize;

// Filter Input and Output Variables
float xn,yn;
int16_t  count = 0;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the FIR example
//! \return returns a 1
//!
//!  Watch Variables:
//!  -# sigIn  Input buffer
//!  -# sigOut Output buffer
//!
int16_t main(void)
{
    // Locals
    uint16_t i;
   
#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    memcpy((uint32_t *)&CoeffFiltRunStart, (uint32_t *)&CoeffFiltLoadStart,
            (uint32_t)&CoeffFiltLoadSize );        
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();
    
    // Generate sample waveforms:
    Rad = 0.0f;
       
    for(i=0; i < SIGNAL_LENGTH; i++)
    {
        sigIn[i]=0;
        sigOut[i]=0;
    }   
    
    // FIR Generic Filter Initialization
    hnd_firFP->order       = FIR_ORDER; 
    hnd_firFP->dbuffer_ptr = dbuffer;
    hnd_firFP->coeff_ptr   = (float *)coeff; 
    hnd_firFP->init(hnd_firFP);
    
    
    for(i=0; i < SIGNAL_LENGTH; i++)
    {
        xn = 0.5*sin(Rad) + 0.5*sin(Rad2); //Q15
        sigIn[i]         = xn;
        hnd_firFP->input = xn;
        hnd_firFP->calc(&firFP);
        yn = hnd_firFP->output;
        sigOut[i]        = yn;
        Rad              = Rad + RadStep;
        Rad2             = Rad2 + RadStep2;
    }   
    
    // Check the output
    for(i = 0; i < SIGNAL_LENGTH; i++){
        if(fabs(FIRgoldenOut[i] - sigOut[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file
