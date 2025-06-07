//#############################################################################
//
// FILE:   cla_shared.h
//
// TITLE:  Declare shared variables
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef CLA_SHARED_H
#define CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define BUFFER_SIZE     128
#define PI                      3.14159f
#define TWO_PI                  2.0f*PI
#define FREQ_S                  100000.0
#define FREQ_1                  1000.0
#define K1                      FREQ_1/FREQ_S

//
// Globals
//
extern float fVal;

// Task 1 (C) Variables
extern float fResult1;

//Task 2 (C) Variables
extern float fResult2;

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//
// CLA C Task Prototypes
//
__attribute__((interrupt)) void Cla1Task1(void);
__attribute__((interrupt)) void Cla1Task2(void);
__attribute__((interrupt)) void Cla1Task3(void);
__attribute__((interrupt)) void Cla1Task4(void);
__attribute__((interrupt)) void Cla1Task5(void);
__attribute__((interrupt)) void Cla1Task6(void);
__attribute__((interrupt)) void Cla1Task7(void);
__attribute__((interrupt)) void Cla1Task8(void);

//
// C28 C Prototypes
//
void test_report(void);
void test_run(void);
void test_error(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /*CLA_SHARED_H*/
