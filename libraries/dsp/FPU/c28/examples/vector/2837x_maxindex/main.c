//#############################################################################
//! \file /2837x_MaxIndex/main.c
//!
//! \brief  Find the index of the maximum value in an array
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
#define SIZE            100U
#define MAX_POSITION    45U
#define MAX_VALUE       3.1321782f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the max index function
//!
float x[SIZE] = {
    #include "data_input.h"
};

//! \brief Index of the maximum array value
//!
uint16_t index = SIZE + 1;

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Max Index example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# index Index of the max value in the array
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
    // Max Index test
    //=========================================================================
    __asm(" NOP");
    index = maxidx_SP_RV_2(x, SIZE);
    __asm(" NOP");

    // Check the output
    if((index == MAX_POSITION) && (x[index] == MAX_VALUE)){
        pass++;
    }else{
        fail++;
    }        
    
    // sort the array and run the test again
    qsort_SP_RV(x, SIZE);
    __asm(" NOP");
    index = maxidx_SP_RV_2(x, SIZE);
    __asm(" NOP");
    
    // Check the output
    if((index == (SIZE - 1)) && (x[index] == MAX_VALUE)){
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

