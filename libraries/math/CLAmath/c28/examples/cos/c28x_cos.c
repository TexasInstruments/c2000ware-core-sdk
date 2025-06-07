//#############################################################################
//
// FILE:   c28x_cos.c
//
// TITLE:  This example calls the cosine function (CLAcos) of the CLA
//         math library on a test vector and compares the result with the 
//         expected results "math.h" routine
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include <stdint.h>
#if defined (F2806x) || defined (F2805x)
#include "DSP28x_Project.h"
#elif defined (F2837x) || defined (F2807x)
#include "F28x_Project.h"
#elif  defined (F28004x) || defined (F2838x) || defined (F28003x)
#include "driverlib.h"
#endif
#include "CLAmath.h"
#include "cla_shared.h"


//
// Defines
//
#define WAITSTEP    __asm(" RPT #255||NOP")
#define EPSILON             1e-1f

//
// Globals
//
extern int16_t pass, fail;

//
//Task 1 (C) Global Variables
//
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float32_t fVal;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult1;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult2;
#else
#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM")
float32_t fVal;
#pragma DATA_SECTION(fResult1,"Cla1ToCpuMsgRAM")
float32_t fResult1;
#pragma DATA_SECTION(fResult2,"Cla1ToCpuMsgRAM")
float32_t fResult2;
#endif

float32_t y1[BUFFER_SIZE];
float32_t fError1[BUFFER_SIZE];
float32_t y2[BUFFER_SIZE];
float32_t fError2[BUFFER_SIZE];

//
// Golden Test Values
//
float32_t testValues[BUFFER_SIZE] = {
 -1.5708,  -1.5461,  -1.5213,  -1.4966,  -1.4718,  -1.4471,  -1.4224,  -1.3976,
 -1.3729,  -1.3482,  -1.3234,  -1.2987,  -1.2740,  -1.2492,  -1.2245,  -1.1997,
 -1.1750,  -1.1503,  -1.1255,  -1.1008,  -1.0761,  -1.0513,  -1.0266,  -1.0018,
 -0.9771,  -0.9524,  -0.9276,  -0.9029,  -0.8782,  -0.8534,  -0.8287,  -0.8040,
 -0.7792,  -0.7545,  -0.7297,  -0.7050,  -0.6803,  -0.6555,  -0.6308,  -0.6061,
 -0.5813,  -0.5566,  -0.5318,  -0.5071,  -0.4824,  -0.4576,  -0.4329,  -0.4082,
 -0.3834,  -0.3587,  -0.3339,  -0.3092,  -0.2845,  -0.2597,  -0.2350,  -0.2103,
 -0.1855,  -0.1608,  -0.1361,  -0.1113,  -0.0866,  -0.0618,  -0.0371,  -0.0124,
  0.0124,   0.0371,   0.0618,   0.0866,   0.1113,   0.1361,   0.1608,   0.1855,
  0.2103,   0.2350,   0.2597,   0.2845,   0.3092,   0.3339,   0.3587,   0.3834,
  0.4082,   0.4329,   0.4576,   0.4824,   0.5071,   0.5318,   0.5566,   0.5813,
  0.6061,   0.6308,   0.6555,   0.6803,   0.7050,   0.7297,   0.7545,   0.7792,
  0.8040,   0.8287,   0.8534,   0.8782,   0.9029,   0.9276,   0.9524,   0.9771,
  1.0018,   1.0266,   1.0513,   1.0761,   1.1008,   1.1255,   1.1503,   1.1750,
  1.1997,   1.2245,   1.2492,   1.2740,   1.2987,   1.3234,   1.3482,   1.3729,
  1.3976,   1.4224,   1.4471,   1.4718,   1.4966,   1.5213,   1.5461,   1.5708
};  
    
float32_t resExpected[BUFFER_SIZE] = {
  0.0000,   0.0247,   0.0495,   0.0741,   0.0988,   0.1234,   0.1479,   0.1723,
  0.1966,   0.2208,   0.2449,   0.2688,   0.2925,   0.3161,   0.3394,   0.3626,
  0.3855,   0.4082,   0.4307,   0.4529,   0.4748,   0.4964,   0.5177,   0.5387,
  0.5594,   0.5798,   0.5997,   0.6193,   0.6386,   0.6574,   0.6758,   0.6939,
  0.7115,   0.7286,   0.7453,   0.7616,   0.7774,   0.7927,   0.8076,   0.8219,
  0.8357,   0.8491,   0.8619,   0.8742,   0.8859,   0.8971,   0.9078,   0.9179,
  0.9274,   0.9364,   0.9448,   0.9526,   0.9598,   0.9665,   0.9725,   0.9780,
  0.9828,   0.9871,   0.9908,   0.9938,   0.9963,   0.9981,   0.9993,   0.9999,
  0.9999,   0.9993,   0.9981,   0.9963,   0.9938,   0.9908,   0.9871,   0.9828,
  0.9780,   0.9725,   0.9665,   0.9598,   0.9526,   0.9448,   0.9364,   0.9274,
  0.9179,   0.9078,   0.8971,   0.8859,   0.8742,   0.8619,   0.8491,   0.8357,
  0.8219,   0.8076,   0.7927,   0.7774,   0.7616,   0.7453,   0.7286,   0.7115,
  0.6939,   0.6758,   0.6574,   0.6386,   0.6193,   0.5997,   0.5798,   0.5594,
  0.5387,   0.5177,   0.4964,   0.4748,   0.4529,   0.4307,   0.4082,   0.3855,
  0.3626,   0.3394,   0.3161,   0.2925,   0.2688,   0.2449,   0.2208,   0.1966,
  0.1723,   0.1479,   0.1234,   0.0988,   0.0741,   0.0495,   0.0247,   0.0000
};

//
// Prototypes
//
#if  defined (F28004x) || defined (F2838x) || defined (F28003x)
void Cla1ForceTask1andWait(void);
void Cla1ForceTask2andWait(void);
void Cla1ForceTask3andWait(void);
#endif

//
// void test_run(void)
//
void test_run(void)
{
    int16_t i;

    for(i=0; i < BUFFER_SIZE; i++)
    {
        fVal= testValues[i];

        //
        // CLA Task 1 CLAcos
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 cos
        //
        Cla1ForceTask2andWait();
        WAITSTEP;
        y2[i] = fResult2;
    }
}

//
// void test_report(void)
//
void test_report(void)
{
    uint16_t i;
    
    float32_t fErrMetric;
    for(i=0; i < BUFFER_SIZE; i++)
    {
        //
        // Verify CLA Task 1 CLAcos() function
        //
        fError1[i] = fabsf(resExpected[i] - y1[i]);
        fErrMetric = fError1[i];
        if( fErrMetric < EPSILON)
        {
            pass++;
        }
        else
        {
            fail++;
        }

        //
        // Verify CLA Task 2 inline function
        //
        fError2[i] = fabsf(resExpected[i] - y2[i]);
        fErrMetric = fError2[i];
        if( fErrMetric < EPSILON)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }
    if(fail)
    {
        test_error();
    }
}

//
// void test_error(void)
//
void test_error(void)
{
    __asm(" ESTOP0"); 
}

//
// void Cla1ForceTask1andWait(void)
//
#if  defined (F28004x) || defined (F2838x) || defined (F28003x)
void Cla1ForceTask1andWait(void)
{
    __asm("  IACK  #0x0001");
    __asm("  RPT #3 || NOP");
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_1) == true)
    {
    }
}
void Cla1ForceTask2andWait(void)
{
    __asm("  IACK  #0x0002");
    __asm("  RPT #3 || NOP");
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_2) == true)
    {
    }
}
void Cla1ForceTask3andWait(void)
{
    __asm("  IACK  #0x0004");
    __asm("  RPT #3 || NOP");
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_3) == true)
    {
    }
}
#endif

//
// End of File
//
