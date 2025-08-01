//#############################################################################
//! \file /28E12x_maxindex.c
//!
//! \brief  Find the index of the maximum value in an array
//
//  Group:             C2000
//  Target Family:     F28E12x
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


//!
//! \addtogroup VECTOR_EXAMPLES Maximum Array Index

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
float32_t x[SIZE] = {
    #include "data_input_maxidx.h"
};

//! \brief Index of the maximum array value
//!
uint16_t index = SIZE + 1;

uint16_t pass = 0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Max Index example
//! \return 1
//!
//!  Watch Variables:
//!
//! -# index Index of the max value in the array
//!
int max_idx_test(void)
{
    //=========================================================================
    // Max Index test
    //=========================================================================
    index = maxidx_SP_RV_2(x, SIZE);

    // Check the output
    if((index == MAX_POSITION) && (x[index] == MAX_VALUE)){
        pass++;
    }else{
        fail++;
    }

    // sort the array and run the test again
    qsort_SP_RV(x, SIZE);

    index = maxidx_SP_RV_2(x, SIZE);

    // Check the output
    if((index == (SIZE - 1)) && (x[index] == MAX_VALUE)){
        pass++;
    }else{
        fail++;
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

    max_idx_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
