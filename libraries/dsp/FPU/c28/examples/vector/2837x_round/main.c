//#############################################################################
//! \file /2837x_Round/main.c
//!
//! \brief  Demo code for the Rounding example
//! \author David Alter
//! \date   July 18, 2012
//! 
//! This example shows how to use the rnd_SP_RS() to round a floating
//! point scalar argument
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
//! \addtogroup VECTOR_EXAMPLES Rounding of a Floating Point Scalar

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            100U

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the rounding function
//!
float x[SIZE] = {
    #include "data_input.h"
};

//! \brief Output from the rounding
//!
float y[SIZE];


//! \brief Expected output
//!
float y_exp[SIZE] = {
    #include "data_output.h"
};

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the Rounding example
//! \return returns a 1
//!
//! The code will round a series of floating point scalars using
//! the FPU library's rnd_SP_RS()
//!
//!  Watch Variables:
//! -# x Input
//! -# y Output
//!
int main(void)
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
    // Rounding test
    //=========================================================================
    for(i = 0; i < SIZE; i++){
        __asm(" NOP");
        y[i] = rnd_SP_RS(x[i]);
        __asm(" NOP");
        if(y[i] == y_exp[i]){
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
