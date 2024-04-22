//#############################################################################
//
// FILE:   c28x_atan.c
//
// TITLE:  This example calls the arc-tangent function (CLAatan) of the CLA
//         math library on a test vector and compares the result with the
//         expected results "math.h" routine
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
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
 -1.0000,  -0.9756,  -0.9517,  -0.9284,  -0.9056,  -0.8834,  -0.8616,  -0.8403,
 -0.8194,  -0.7989,  -0.7789,  -0.7592,  -0.7399,  -0.7209,  -0.7023,  -0.6839,
 -0.6659,  -0.6482,  -0.6308,  -0.6137,  -0.5968,  -0.5801,  -0.5637,  -0.5475,
 -0.5315,  -0.5158,  -0.5002,  -0.4848,  -0.4697,  -0.4546,  -0.4398,  -0.4251,
 -0.4106,  -0.3962,  -0.3820,  -0.3679,  -0.3539,  -0.3400,  -0.3263,  -0.3127,
 -0.2991,  -0.2857,  -0.2724,  -0.2591,  -0.2460,  -0.2329,  -0.2199,  -0.2070,
 -0.1941,  -0.1813,  -0.1685,  -0.1558,  -0.1432,  -0.1306,  -0.1180,  -0.1055,
 -0.0930,  -0.0806,  -0.0681,  -0.0557,  -0.0433,  -0.0309,  -0.0186,  -0.0062,
  0.0062,   0.0186,   0.0309,   0.0433,   0.0557,   0.0681,   0.0806,   0.0930,
  0.1055,   0.1180,   0.1306,   0.1432,   0.1558,   0.1685,   0.1813,   0.1941,
  0.2070,   0.2199,   0.2329,   0.2460,   0.2591,   0.2724,   0.2857,   0.2991,
  0.3127,   0.3263,   0.3400,   0.3539,   0.3679,   0.3820,   0.3962,   0.4106,
  0.4251,   0.4398,   0.4546,   0.4697,   0.4848,   0.5002,   0.5158,   0.5315,
  0.5475,   0.5637,   0.5801,   0.5968,   0.6137,   0.6308,   0.6482,   0.6659,
  0.6839,   0.7023,   0.7209,   0.7399,   0.7592,   0.7789,   0.7989,   0.8194,
  0.8403,   0.8616,   0.8834,   0.9056,   0.9284,   0.9517,   0.9756,   1.0000
};

float32_t resExpected[BUFFER_SIZE] = {
 -0.7854,  -0.7730,  -0.7607,  -0.7483,  -0.7359,  -0.7236,  -0.7112,  -0.6988,
 -0.6865,  -0.6741,  -0.6617,  -0.6493,  -0.6370,  -0.6246,  -0.6122,  -0.5999,
 -0.5875,  -0.5751,  -0.5628,  -0.5504,  -0.5380,  -0.5257,  -0.5133,  -0.5009,
 -0.4886,  -0.4762,  -0.4638,  -0.4514,  -0.4391,  -0.4267,  -0.4143,  -0.4020,
 -0.3896,  -0.3772,  -0.3649,  -0.3525,  -0.3401,  -0.3278,  -0.3154,  -0.3030,
 -0.2907,  -0.2783,  -0.2659,  -0.2536,  -0.2412,  -0.2288,  -0.2164,  -0.2041,
 -0.1917,  -0.1793,  -0.1670,  -0.1546,  -0.1422,  -0.1299,  -0.1175,  -0.1051,
 -0.0928,  -0.0804,  -0.0680,  -0.0557,  -0.0433,  -0.0309,  -0.0186,  -0.0062,
  0.0062,   0.0186,   0.0309,   0.0433,   0.0557,   0.0680,   0.0804,   0.0928,
  0.1051,   0.1175,   0.1299,   0.1422,   0.1546,   0.1670,   0.1793,   0.1917,
  0.2041,   0.2164,   0.2288,   0.2412,   0.2536,   0.2659,   0.2783,   0.2907,
  0.3030,   0.3154,   0.3278,   0.3401,   0.3525,   0.3649,   0.3772,   0.3896,
  0.4020,   0.4143,   0.4267,   0.4391,   0.4514,   0.4638,   0.4762,   0.4886,
  0.5009,   0.5133,   0.5257,   0.5380,   0.5504,   0.5628,   0.5751,   0.5875,
  0.5999,   0.6122,   0.6246,   0.6370,   0.6493,   0.6617,   0.6741,   0.6865,
  0.6988,   0.7112,   0.7236,   0.7359,   0.7483,   0.7607,   0.7730,   0.7854
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
        // CLA Task 1 CLAatan
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 atan
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
        // Verify CLA Task 1 CLAatan() function
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
