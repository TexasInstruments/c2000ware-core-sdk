#ifndef _EXAMPLES_SETUP_H_
#define _EXAMPLES_SETUP_H_
//#############################################################################
//
// FILE:        examples_setup.h
//
// Description: Initialization routines for the CLA_DSP library examples
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_200MHZ	1

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void CLA_DSP_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void CLA_DSP_initEpie(void);

// \brief Configure CLA memory space
//
void CLA_DSP_configClaMemory(void);

// \brief Intialize the MVECT registers for the CLA
//
void CLA_DSP_initCpu1Cla1(void);

//*****************************************************************************
// CLA function prototypes
//*****************************************************************************
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//CLA End of Task Interrupts
__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _EXAMPLES_SETUP_H_ definition
