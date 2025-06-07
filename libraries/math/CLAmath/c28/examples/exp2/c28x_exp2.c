//#############################################################################
//
// FILE:   c28x_exp2.c
//
// TITLE:  This example calls the exponential of a ratio function (CLAexp2) of
//         the CLA math library on a test vector and compares the result with
//         the expected results "math.h" routine
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
float32_t fNum;
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float32_t fDen;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult1;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult2;
#else
#pragma DATA_SECTION(fNum,"CpuToCla1MsgRAM")
float32_t fNum;
#pragma DATA_SECTION(fDen,"CpuToCla1MsgRAM")
float32_t fDen;
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
float32_t testNum[BUFFER_SIZE] = {
  1.0000,   2.0000,   3.0000,   4.0000,   5.0000,   6.0000,   7.0000,   8.0000,
  9.0000,  10.0000,  11.0000,  12.0000,  13.0000,  14.0000,  15.0000,  16.0000,
 17.0000,  18.0000,  19.0000,  20.0000,  21.0000,  22.0000,  23.0000,  24.0000,
 25.0000,  26.0000,  27.0000,  28.0000,  29.0000,  30.0000,  31.0000,  32.0000,
 33.0000,  34.0000,  35.0000,  36.0000,  37.0000,  38.0000,  39.0000,  40.0000,
 41.0000,  42.0000,  43.0000,  44.0000,  45.0000,  46.0000,  47.0000,  48.0000,
 49.0000,  50.0000,  51.0000,  52.0000,  53.0000,  54.0000,  55.0000,  56.0000,
 57.0000,  58.0000,  59.0000,  60.0000,  61.0000,  62.0000,  63.0000,  64.0000,
 65.0000,  66.0000,  67.0000,  68.0000,  69.0000,  70.0000,  71.0000,  72.0000,
 73.0000,  74.0000,  75.0000,  76.0000,  77.0000,  78.0000,  79.0000,  80.0000,
 81.0000,  82.0000,  83.0000,  84.0000,  85.0000,  86.0000,  87.0000,  88.0000,
 89.0000,  90.0000,  91.0000,  92.0000,  93.0000,  94.0000,  95.0000,  96.0000,
 97.0000,  98.0000,  99.0000, 100.0000, 101.0000, 102.0000, 103.0000, 104.0000,
105.0000, 106.0000, 107.0000, 108.0000, 109.0000, 110.0000, 111.0000, 112.0000,
113.0000, 114.0000, 115.0000, 116.0000, 117.0000, 118.0000, 119.0000, 120.0000,
121.0000, 122.0000, 123.0000, 124.0000, 125.0000, 126.0000, 127.0000, 128.0000
};

float32_t testDen[BUFFER_SIZE] = {
  3.0000,   4.0000,   5.0000,   6.0000,   7.0000,   8.0000,   9.0000,  10.0000,
 11.0000,  12.0000,  13.0000,  14.0000,  15.0000,  16.0000,  17.0000,  18.0000,
 19.0000,  20.0000,  21.0000,  22.0000,  23.0000,  24.0000,  25.0000,  26.0000,
 27.0000,  28.0000,  29.0000,  30.0000,  31.0000,  32.0000,  33.0000,  34.0000,
 35.0000,  36.0000,  37.0000,  38.0000,  39.0000,  40.0000,  41.0000,  42.0000,
 43.0000,  44.0000,  45.0000,  46.0000,  47.0000,  48.0000,  49.0000,  50.0000,
 51.0000,  52.0000,  53.0000,  54.0000,  55.0000,  56.0000,  57.0000,  58.0000,
 59.0000,  60.0000,  61.0000,  62.0000,  63.0000,  64.0000,  65.0000,  66.0000,
 67.0000,  68.0000,  69.0000,  70.0000,  71.0000,  72.0000,  73.0000,  74.0000,
 75.0000,  76.0000,  77.0000,  78.0000,  79.0000,  80.0000,  81.0000,  82.0000,
 83.0000,  84.0000,  85.0000,  86.0000,  87.0000,  88.0000,  89.0000,  90.0000,
 91.0000,  92.0000,  93.0000,  94.0000,  95.0000,  96.0000,  97.0000,  98.0000,
 99.0000, 100.0000, 101.0000, 102.0000, 103.0000, 104.0000, 105.0000, 106.0000,
107.0000, 108.0000, 109.0000, 110.0000, 111.0000, 112.0000, 113.0000, 114.0000,
115.0000, 116.0000, 117.0000, 118.0000, 119.0000, 120.0000, 121.0000, 122.0000,
123.0000, 124.0000, 125.0000, 126.0000, 127.0000, 128.0000, 129.0000, 130.0000
};

float32_t resExpected[BUFFER_SIZE] = {
  1.3956,   1.6487,   1.8221,   1.9477,   2.0427,   2.1170,   2.1766,   2.2255,
  2.2664,   2.3010,   2.3307,   2.3564,   2.3790,   2.3989,   2.4166,   2.4324,
  2.4467,   2.4596,   2.4713,   2.4821,   2.4919,   2.5009,   2.5093,   2.5170,
  2.5242,   2.5309,   2.5371,   2.5430,   2.5484,   2.5536,   2.5584,   2.5630,
  2.5673,   2.5714,   2.5752,   2.5789,   2.5824,   2.5857,   2.5889,   2.5919,
  2.5947,   2.5975,   2.6001,   2.6026,   2.6050,   2.6073,   2.6096,   2.6117,
  2.6137,   2.6157,   2.6176,   2.6194,   2.6212,   2.6229,   2.6246,   2.6261,
  2.6277,   2.6292,   2.6306,   2.6320,   2.6333,   2.6346,   2.6359,   2.6371,
  2.6383,   2.6395,   2.6406,   2.6417,   2.6428,   2.6438,   2.6448,   2.6458,
  2.6468,   2.6477,   2.6486,   2.6495,   2.6503,   2.6512,   2.6520,   2.6528,
  2.6536,   2.6543,   2.6551,   2.6558,   2.6565,   2.6572,   2.6579,   2.6585,
  2.6592,   2.6598,   2.6604,   2.6611,   2.6617,   2.6622,   2.6628,   2.6634,
  2.6639,   2.6645,   2.6650,   2.6655,   2.6660,   2.6665,   2.6670,   2.6675,
  2.6679,   2.6684,   2.6689,   2.6693,   2.6697,   2.6702,   2.6706,   2.6710,
  2.6714,   2.6718,   2.6722,   2.6726,   2.6730,   2.6734,   2.6737,   2.6741,
  2.6744,   2.6748,   2.6751,   2.6755,   2.6758,   2.6761,   2.6765,   2.6768
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
        fNum = testNum[i];
        fDen = testDen[i];

        //
        // CLA Task 1 CLAexp2
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 exp2
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
        // Verify CLA Task 1 CLAexp2() function
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
