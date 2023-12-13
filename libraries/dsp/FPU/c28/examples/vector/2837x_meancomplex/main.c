//#############################################################################
//! \file /2837x_InvComplexAbsVec/main.c
//!
//! \brief  Mean of complex vector test
//! \author David Alter (example modified by Vishal Coelho)  
//! \date   12/18/07
//! 
//! This example shows how to use the vector routines in the library to
//! calculate the mean of complex vector
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
#include "examples_setup.h"
#include "fpu_vector.h"
#include "string.h"

//!
//! \addtogroup VECTOR_EXAMPLES Mean of a Complex Vector

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            100U
#define MEAN_VALUE_REAL 2.554267207580118f
#define MEAN_VALUE_IMAG 2.423102303419162f
#define EPSILON         0.00001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the mean function
//!
complex_float x[SIZE] = {
    #include "data_input.h"
};

//! \brief mean of the complex vector
//!
complex_float mean = {0,0};

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Mean example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# mean Mean of the complex vector
//!
int16_t main(void)
{
    // Locals

#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();
    
    //=========================================================================
    // Mean test
    //=========================================================================
    __asm(" NOP");
    mean = mean_SP_CV_2(x, SIZE);
    __asm(" NOP");

    // Check the output
    if((fabs(mean.dat[0] - MEAN_VALUE_REAL) < EPSILON) && 
       (fabs(mean.dat[1] - MEAN_VALUE_IMAG) < EPSILON)){
        pass++;
    }else{
        fail++;
    }        
    
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file
