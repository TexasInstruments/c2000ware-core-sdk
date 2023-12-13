//#############################################################################
//! \file /2837x_Median/main.c
//!
//! \brief  Find the median of a scalar vector
//! \author David Alter (example modified by Vishal Coelho)  
//! \date   12/18/07
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
//! \addtogroup VECTOR_EXAMPLES Index of the Maximum Value in an Array

// @{
   
//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            256U
#define MEDIAN_VALUE    2.637057027747737f
#define EPSILON         0.000001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the median function
//!
float x[SIZE] = {
    #include "data_input.h"
};

//! \brief copy of the input
//!
float y[SIZE];

//! \brief Median of the array
//!
float median = 0.0f;

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Median example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# median Median of the array
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
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();
    
    //=========================================================================
    // Median test
    //=========================================================================
    // Copy the input "x" over to "y"
    memcpy_fast(y, x, sizeof(float)*SIZE);
    __asm(" NOP");
    // Run the median algorithm, while re-ordering the input
    median = median_SP_RV(x, SIZE);
    __asm(" NOP");
    
    //Check the output
    if(fabs(median - MEDIAN_VALUE) < EPSILON){
        pass++;
    }else{
        fail++;
    }
    
    //=========================================================================
    // Median test (without reordering)
    //=========================================================================
    // Copy the "y" back over to "x"
    memcpy_fast(x, y, sizeof(float)*SIZE);
    median = 0.0f;
    __asm(" NOP");
    median = median_noreorder_SP_RV(y, SIZE);
    __asm(" NOP");

    //Check the output
    if(fabs(median - MEDIAN_VALUE) < EPSILON){
        pass++;
    }else{
        fail++;
    }
    
    // Check no reordering happens
    for(i = 0; i < SIZE; i++){
        if(fabs(x[i] - y[i]) < EPSILON){
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
