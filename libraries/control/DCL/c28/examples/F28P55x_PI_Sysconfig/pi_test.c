//#############################################################################
//! \file pi_test.c
//!
//!
//! This example demonstrates how to use DCL's PI controller along with SysConfig
//! setup
//
//  Group:             C2000
//  Target Family:     F28P55X
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
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

#include "pi_test.h"

//!
//! \addtogroup DCL_EXAMPLES PI controller example

// @{


uint16_t currIdx = 0;
uint16_t completed = 0;
int16_t errors = -1;

void Init_DCL_Logger(void)
{
    //
    // Initialize Log pointers to the data buffer
    //
    DCL_initLog(&rkLog, (float32_t*)rkLogArr, DATA_LENGTH);
    DCL_initLog(&ykLog, (float32_t*)ykLogArr, DATA_LENGTH);
    DCL_initLog(&ctlLog, (float32_t*)ctlLogArr, DATA_LENGTH);
    DCL_initLog(&outLog, (float32_t*)outLogArr, DATA_LENGTH);

    // Reset PI controller as well
    DCL_resetPI(&myController0);
}

int Run_PI_Logger()
{


    //
    // rk = Target referenced value
    // yk = Current feedback value
    // uk = Output control effort
    //
    float32_t rk,yk,uk;

    //
    // Read the input data buffers
    //
    rk = DCL_freadLog(&rkLog);
    yk = DCL_freadLog(&ykLog);

    //
    // Run the controller
    // Equivalent to uk = DCL_runPI_series(ctrl_handle, rk, yk);
    //
    uk = DCL_runPI_C1(&myController0, rk, yk);

    //
    // Write the results to the output buffer
    //
    DCL_fwriteLog(&outLog, uk);

    return 1;
}

int Compare_Results()
{
    int i;

    //
    // Reset the log pointer so it starts from the beginning
    //
    DCL_resetLog(&outLog);

    //
    // Check output against expected output with tolerance (1e-06)
    //
    int errors = 0;
    for (i = 0; i < NUM_ELEMENTS; i++)
    {
        float32_t output = DCL_freadLog(&outLog);   // outLogArr[i]
        float32_t expected = DCL_freadLog(&ctlLog); // ctlLogArr[i]
        float32_t error = fabsf(output - expected);
        if (error > EPSILON)
        {
            errors++;
            printf("FAIL at sample %d, outputs %f, should be %f\n", i, output, expected);
        }
    }

    return errors;
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
    // DCL Logger Initialization
    //
    Init_DCL_Logger();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        if (completed)
        {
            errors = Compare_Results();
            printf("PI test produced %d error\n",errors);
            DCL_BREAK_POINT;
        }
    }
}

// initialize CPU timer0 in sysconfig
interrupt void control_Isr(void)
{
    if (currIdx < NUM_ELEMENTS)
    {
        Run_PI_Logger();
        currIdx++;
    }
    else
    {
        completed = 1;
        Interrupt_disable(INT_myCPUTIMER0);
    }

    Interrupt_clearACKGroup(INT_myCPUTIMER0_INTERRUPT_ACK_GROUP);
}

// End of main

// @} //addtogroup

// End of file
