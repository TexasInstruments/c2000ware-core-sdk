//#############################################################################
//
// FILE:   f2805x_examples_setup.c
//
// TITLE:  Initialization routines for CLA Math library examples
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include <stdint.h>
#include "DSP28x_Project.h"
#include "cla_shared.h"

//
// Globals
//
int16_t pass = 0, fail = 0;
extern uint16_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint16_t CLA1mathTablesRunStart, CLA1mathTablesLoadStart;
extern uint16_t CLA1mathTablesLoadSize;

//
// Prototypes
//
void done(void);

//
// int main(void)
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

#ifdef _FLASH
    //
    // Copy over code and tables from FLASH to RAM
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);
    memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
            (uint32_t)&Cla1ProgLoadSize);

#if !(CLA_MATH_TABLES_IN_ROM)
    //
    // Copy over CLA Math tables from FLASH to RAM
    //
    memcpy((uint32_t *)&CLA1mathTablesRunStart, (uint32_t *)&CLA1mathTablesLoadStart,
            (uint32_t)&CLA1mathTablesLoadSize);
#endif

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    InitFlash();
#endif

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();

    //
    // Compute all CLA task vectors
    //
    // Assign the task vectors
    //
    EALLOW;
    Cla1Regs.MVECT1 = (uint16_t)((uint32_t)&Cla1Task1 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT2 = (uint16_t)((uint32_t)&Cla1Task2 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT3 = (uint16_t)((uint32_t)&Cla1Task3 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT4 = (uint16_t)((uint32_t)&Cla1Task4 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT5 = (uint16_t)((uint32_t)&Cla1Task5 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT6 = (uint16_t)((uint32_t)&Cla1Task6 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT7 = (uint16_t)((uint32_t)&Cla1Task7 - 
                                 (uint32_t)&Cla1ProgRunStart);
    Cla1Regs.MVECT8 = (uint16_t)((uint32_t)&Cla1Task8 - 
                                 (uint32_t)&Cla1ProgRunStart);
    EDIS;
   
    //
    // Set task triggers to none
    // Enable all CLA tasks
    //
    EALLOW;
    Cla1Regs.MPISRCSEL1.bit.PERINT1SEL  = CLA_INT1_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL  = CLA_INT2_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT3SEL  = CLA_INT3_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT4SEL  = CLA_INT4_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT5SEL  = CLA_INT5_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT6SEL  = CLA_INT6_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT7SEL  = CLA_INT7_NONE;
    Cla1Regs.MPISRCSEL1.bit.PERINT8SEL  = CLA_INT8_NONE;
    Cla1Regs.MIER.all                   = 0x00FF;
    EDIS;

    //
    // Switch the CLA program space to the CLA and enable software forcing
    // Also switch over CLA data RAM1 (RAML2)
    //
    EALLOW;
    Cla1Regs.MMEMCFG.bit.PROGE  = 1;
    Cla1Regs.MCTL.bit.IACKE     = 1;
    Cla1Regs.MMEMCFG.bit.RAM1E  = 1; // RAM1 is RAML2
    EDIS;   

    //
    // Run the test with the input test vectors
    //
    test_run();

    //
    // Verify the results
    //
    test_report();

    //
    // End of Test
    //
    done();

    //
    // Code must never reach this point
    //
    return(1);
}

//
// void done(void)
//
// This is an infinite loop.
//
void done(void)
{
    for(;;)
    {
    }
}

//
// End of file
//
