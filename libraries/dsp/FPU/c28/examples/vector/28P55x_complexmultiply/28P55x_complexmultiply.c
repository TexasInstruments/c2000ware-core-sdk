//#############################################################################
//! \file /28P55x_complexmultiply.c
//!
//! \brief  Complex Multiplication
//!
//! This example shows how to use the vector routines in the library to
//! calculate the complex product of two complex vectors
//!
//
//  Group:             C2000
//  Target Family:     F28P55X
//
//#############################################################################
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"
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
const complex_float x[SIZE] = {
    #include "data_input_cmplxmul1.h"
};

//! \brief input to the complex multiply function
//!
const complex_float y[SIZE] = {
    #include "data_input_cmplxmul2.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
complex_float z[SIZE];

complex_float z_exp[SIZE] = {
    #include "data_output_cmplxmul.h"
};

uint16_t pass = 0, fail = 0;

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
int cmplx_mul_test(void)
{
    int i;

    //=========================================================================
    // Complex multiplication test
    //=========================================================================
    memset(z, 0, SIZE*sizeof(complex_float));

    for(i = 0; i < SIZE; i++){
        z[i] = mpy_SP_CSxCS(x[i], y[i]); // complex multiply


        if((fabsf(z[i].dat[0]- z_exp[i].dat[0]) < EPSILON) &&
                (fabsf(z[i].dat[1]- z_exp[i].dat[1]) < EPSILON)){
            pass++;
        }else{
            fail++;
        }
    }

    printf("Total of %d tests pass, and %d failure",pass,fail);
    return 1;
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

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
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    cmplx_mul_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
