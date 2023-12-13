//#############################################################################
//
// FILE:   c28x_expN.c
//
// TITLE:  This example calls the base N exponential function (CLAexpN) of the
//         CLA math library on a test vector and compares the result with the
//         expected results "math.h" routine
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
float32_t y3[BUFFER_SIZE];
float32_t fError3[BUFFER_SIZE];

//
// Golden Test Values
//
float32_t testValues[BUFFER_SIZE] = {
    -3.1415927, -3.0921188, -3.0426449,-2.9931710,
    -2.9436971, -2.8942232, -2.8447493,-2.7952754,
    -2.7458015, -2.6963276, -2.6468537,-2.5973798,
    -2.5479059, -2.4984320, -2.4489581,-2.3994842,
    -2.3500103, -2.3005364, -2.2510625,-2.2015886,
    -2.1521147, -2.1026408, -2.0531669,-2.0036930,
    -1.9542191, -1.9047452, -1.8552713,-1.8057974,
    -1.7563235, -1.7068496, -1.6573757,-1.6079018,
    -1.5584279, -1.5089540, -1.4594801,-1.4100062,
    -1.3605323, -1.3110584, -1.2615845,-1.2121106,
    -1.1626367, -1.1131628, -1.0636889,-1.0142150,
    -0.9647411, -0.9152672, -0.8657933,-0.8163194,
    -0.7668455, -0.7173716, -0.6678977,-0.6184238,
    -0.5689499, -0.5194760, -0.4700021,-0.4205282,
    -0.3710543, -0.3215804, -0.2721065,-0.2226326,
    -0.1731587, -0.1236848, -0.0742109,-0.0247370,
    0.0247370,  0.0742109,  0.1236848, 0.1731587,
    0.2226326,  0.2721065,  0.3215804, 0.3710543,
    0.4205282,  0.4700021,  0.5194760, 0.5689499,
    0.6184238,  0.6678977,  0.7173716, 0.7668455,
    0.8163194,  0.8657933,  0.9152672, 0.9647411,
    1.0142150,  1.0636889,  1.1131628, 1.1626367,
    1.2121106,  1.2615845,  1.3110584, 1.3605323,
    1.4100062,  1.4594801,  1.5089540, 1.5584279,
    1.6079018,  1.6573757,  1.7068496, 1.7563235,
    1.8057974,  1.8552713,  1.9047452, 1.9542191,
    2.0036930,  2.0531669,  2.1026408, 2.1521147,
    2.2015886,  2.2510625,  2.3005364, 2.3500103,
    2.3994842,  2.4489581,  2.4984320, 2.5479059,
    2.5973798,  2.6468537,  2.6963276, 2.7458015,
    2.7952754,  2.8447493,  2.8942232, 2.9436971,
    2.9931710,  3.0426449,  3.0921188, 3.1415927,
};

float32_t resExpected[BUFFER_SIZE] = {
    0.0274257,  0.0290238,  0.0307149, 0.0325046,
    0.0343986,  0.0364030,  0.0385242, 0.0407689,
    0.0431445,  0.0456584,  0.0483189, 0.0511344,
    0.0541139,  0.0572671,  0.0606039, 0.0641352,
    0.0678723,  0.0718272,  0.0760124, 0.0804416,
    0.0851288,  0.0900891,  0.0953385, 0.1008938,
    0.1067727,  0.1129942,  0.1195782, 0.1265459,
    0.1339196,  0.1417229,  0.1499809, 0.1587201,
    0.1679685,  0.1777558,  0.1881134, 0.1990745,
    0.2106743,  0.2229500,  0.2359410, 0.2496890,
    0.2642380,  0.2796348,  0.2959288, 0.3131722,
    0.3314203,  0.3507317,  0.3711684, 0.3927959,
    0.4156836,  0.4399049,  0.4655376, 0.4926639,
    0.5213707,  0.5517503,  0.5839001, 0.6179232,
    0.6539287,  0.6920323,  0.7323561, 0.7750295,
    0.8201895,  0.8679808,  0.9185569, 0.9720800,
    1.0287219,  1.0886641,  1.1520992, 1.2192305,
    1.2902734,  1.3654559,  1.4450192, 1.5292186,
    1.6183242,  1.7126218,  1.8124140, 1.9180209,
    2.0297815,  2.1480542,  2.2732185, 2.4056759,
    2.5458515,  2.6941949,  2.8511820, 3.0173167,
    3.1931317,  3.3791913,  3.5760923, 3.7844665,
    4.0049823,  4.2383474,  4.4853103, 4.7466634,
    5.0232452,  5.3159431,  5.6256961, 5.9534979,
    6.3004004,  6.6675164,  7.0560238, 7.4671690,
    7.9022711,  8.3627260,  8.8500110, 9.3656894,
    9.9114158, 10.4889409, 11.1001176,11.7469068,
    12.4313836, 13.1557439, 13.9223117,14.7335465,
    15.5920508, 16.5005790, 17.4620459,18.4795363,
    19.5563145, 20.6958351, 21.9017541,23.1779404,
    24.5284884, 25.9577310, 27.4702537,29.0709091,
    30.7648326, 32.5574588, 34.4545390,36.4621595,
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
        // CLA Task 1 CLAexpN
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 CLAexpN_inline
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
        // Verify CLA Task 1 CLAexpN() function
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
