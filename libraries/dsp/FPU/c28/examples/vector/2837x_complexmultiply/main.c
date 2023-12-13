//#############################################################################
//! \file /2837x_ComplexMultiply/main.c
//!
//! \brief  Complex Multiplication
//! \author David Alter (example modified by Vishal Coelho)  
//! \date   12/18/07
//! 
//! This example shows how to use the vector routines in the library to
//! calculate the complex product of two complex vectors
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
//! \addtogroup VECTOR_EXAMPLES Complex Multiplication

// @{
   
//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE        99U
#define EPSILON     0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the complex multiply function
//!
complex_float x[SIZE] = {
    #include "data_input_1.h"
};

//! \brief input to the complex multiply function
//!
complex_float y[SIZE] = {
    #include "data_input_2.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
complex_float z[SIZE];

complex_float z_exp[SIZE] = {
    #include "data_output.h"
};

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Complex Multiply example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# y Input 
//! -# x Input 
//! -# z Output
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
    // Complex multiplication test
    //=========================================================================
    memset(z, 0, SIZE*sizeof(complex_float));

    for(i = 0; i < SIZE; i++){
        __asm(" NOP");
        z[i] = mpy_SP_CSxCS(x[i], y[i]); // complex multiply
        __asm(" NOP");
        if((fabs(z[i].dat[0]- z_exp[i].dat[0]) < EPSILON) &&
                (fabs(z[i].dat[1]- z_exp[i].dat[1]) < EPSILON)){
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
