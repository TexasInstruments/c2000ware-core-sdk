//#############################################################################
//! \file /2837x_ComplexAbsVec/main.c
//!
//! \brief  Absolute value of a complex vector test
//! \author David Alter (example modified by Vishal Coelho)  
//! \date   12/18/07
//! 
//! This example shows how to use the vector routines in the library to
//! calculate the absolute (and inverse absolute) of a vector
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
//! \addtogroup VECTOR_EXAMPLES Absolute Value of a Complex Vector

// @{
   
//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE        99U
#define N1          98U     // even size
#define N2          99U     // odd size
#define EPSILON     0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the complex vector absolute (and inverse abs) function
//!
complex_float x[SIZE] = {
    #include "data_input.h"
};

//! \brief output  of the complex vector absolute function
//!
float y[SIZE];

float y_exp[SIZE] = {
    #include "data_output_1.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
float z[SIZE];

float z_exp[SIZE] = {
    #include "data_output_2.h"
};

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Absolute Value of a Complex Vector example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# y Output for the vector absolute function
//! -# z Output for the vector inverse absolute function
//! -# x Input for the vector absolute (and inverse) function
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
    // Absolute value of a complex vector test
    //=========================================================================
    // Run the test on a vector with even number of elements
    memset(y, 0, SIZE*sizeof(float));
    __asm(" NOP");
#ifdef __TMS320C28XX_TMU__  //defined when --tmu_support=tmu0 in the project properties
    abs_SP_CV_TMU0(y, x, N1);  // complex absolute value
#else
    abs_SP_CV(y, x, N1);       // complex absolute value
#endif
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabs(y[i] - y_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }        
    }
    
    // Run the same test on a vector with odd number of elements
    memset(y, 0, SIZE*sizeof(float));
    __asm(" NOP");
#ifdef __TMS320C28XX_TMU__  //defined when --tmu_support=tmu0 in the project properties
    abs_SP_CV_TMU0(y, x, N2);  // complex absolute value
#else
    abs_SP_CV(y, x, N2);       // complex absolute value
#endif
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N2; i++){
        if(fabs(y[i] - y_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }        
    }

    // If the input has an even number of entries, it would be faster to 
    // run the abs_SP_CV_2() instead. With the TMU0 support turned on, use
    // the abs_SP_CV_TMU0() instead - note that the TMU equivalent has one
    // function for both even and odd numbered vectors
    memset(y, 0, SIZE*sizeof(float));
    __asm(" NOP");
    abs_SP_CV_2(y, x, N1);  // complex absolute value (TMU0)
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabs(y[i] - y_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }        
    }

    //=========================================================================
    // Inverse Absolute value of a complex vector test
    //=========================================================================
    // Run the test on a vector with even number of elements
    memset(z, 0, SIZE*sizeof(float));
    __asm(" NOP");
#ifdef __TMS320C28XX_TMU__  //defined when --tmu_support=tmu0 in the project properties
    iabs_SP_CV_TMU0(z, x, N1);  // complex absolute value
#else
    iabs_SP_CV(z, x, N1);        // complex absolute value
#endif
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabs(z[i] - z_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }        
    }
    
    // Run the same test on a vector with odd number of elements
    memset(z, 0, SIZE*sizeof(float));
    __asm(" NOP");
#ifdef __TMS320C28XX_TMU__  //defined when --tmu_support=tmu0 in the project properties
    iabs_SP_CV_TMU0(z, x, N2);  // complex absolute value
#else
    iabs_SP_CV(z, x, N2);        // complex absolute value
#endif
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N2; i++){
        if(fabs(z[i] - z_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }        
    }

    // If the input has an even number of entries, it would be faster to 
    // run the iabs_SP_CV_2() instead. With the TMU0 support turned on, use
    // the iabs_SP_CV_TMU0() instead - note that the TMU equivalent has one
    // function for both even and odd numbered vectors
    memset(z, 0, SIZE*sizeof(float));
    __asm(" NOP");
    iabs_SP_CV_2(z, x, N1);  // complex absolute value (TMU0)
    __asm(" NOP");

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabs(z[i] - z_exp[i]) < EPSILON){
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
