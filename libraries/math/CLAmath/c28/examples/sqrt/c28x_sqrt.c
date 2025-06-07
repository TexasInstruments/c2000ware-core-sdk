//#############################################################################
//
// FILE:   c28x_sqrt.c
//
// TITLE:  This example calls the square root function (CLAsqrt) of the CLA
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
1, 1.779528, 2.559055, 3.338583, 4.118110, 
4.897638, 5.677166, 6.456693, 7.236220, 8.015748, 
8.795276, 9.574803, 10.35433, 11.13386, 11.91339, 
12.69291, 13.47244, 14.25197, 15.03150, 15.81102, 
16.59055, 17.37008, 18.14961, 18.92913, 19.70866, 
20.48819, 21.26772, 22.04725, 22.82677, 23.60630, 
24.38583, 25.16535, 25.94488, 26.72441, 27.50394, 
28.28346, 29.06299, 29.84252, 30.62205, 31.40158, 
32.18110, 32.96063, 33.74016, 34.51968, 35.29921, 
36.07874, 36.85827, 37.63779, 38.41732, 39.19685, 
39.97638, 40.75591, 41.53543, 42.31496, 43.09449, 
43.87402, 44.65354, 45.43307, 46.21260, 46.99213, 
47.77165, 48.55118, 49.33071, 50.11024, 50.88976, 
51.66929, 52.44882, 53.22835, 54.00787, 54.78740, 
55.56693, 56.34646, 57.12598, 57.90551, 58.68504, 
59.46457, 60.24409, 61.02362, 61.80315, 62.58268, 
63.36221, 64.14173, 64.92126, 65.70079, 66.48032, 
67.25984, 68.03937, 68.81890, 69.59843, 70.37795, 
71.15748, 71.93700, 72.71654, 73.49606, 74.27559, 
75.05511, 75.83465, 76.61417, 77.39370, 78.17323, 
78.95276, 79.73228, 80.51181, 81.29134, 82.07087, 
82.85040, 83.62992, 84.40945, 85.18898, 85.96851, 
86.74803, 87.52756, 88.30708, 89.08662, 89.86614, 
90.64567, 91.42519, 92.20473, 92.98425, 93.76378, 
94.54330, 95.32284, 96.10236, 96.88189, 97.66142, 
98.44095, 99.22047, 100
};

float32_t resExpected[BUFFER_SIZE] = {
1, 1.333989, 1.599705, 1.827179, 2.029313, 
2.213061, 2.382680, 2.541002, 2.690022, 2.831210, 
2.965683, 3.094318, 3.217815, 3.336744, 3.451577, 
3.562711, 3.670482, 3.775178, 3.877047, 3.976308, 
4.073150, 4.167743, 4.260235, 4.350762, 4.439444, 
4.526388, 4.611693, 4.695449, 4.777737, 4.858632, 
4.938201, 5.016508, 5.093612, 5.169566, 5.244420, 
5.318220, 5.391010, 5.462831, 5.533719, 5.603711, 
5.672839, 5.741135, 5.808628, 5.875346, 5.941314, 
6.006558, 6.071101, 6.134965, 6.198171, 6.260739, 
6.322688, 6.384035, 6.444799, 6.504995, 6.564639, 
6.623746, 6.682331, 6.740406, 6.797985, 6.855080, 
6.911704, 6.967868, 7.023582, 7.078858, 7.133706, 
7.188136, 7.242156, 7.295776, 7.349005, 7.401851, 
7.454323, 7.506428, 7.558173, 7.609567, 7.660616, 
7.711327, 7.761707, 7.811762, 7.861498, 7.910922, 
7.960038, 8.008853, 8.057373, 8.105602, 8.153546, 
8.201210, 8.248598, 8.295715, 8.342567, 8.389157, 
8.435490, 8.481568, 8.527399, 8.572985, 8.618329, 
8.663436, 8.708309, 8.752953, 8.797369, 8.841562, 
8.885536, 8.929294, 8.972837, 9.016171, 9.059298, 
9.102220, 9.144939, 9.187462, 9.229788, 9.271920, 
9.313863, 9.355617, 9.397185, 9.438571, 9.479775, 
9.520802, 9.561652, 9.602329, 9.642835, 9.683170, 
9.723338, 9.763341, 9.803182, 9.842860, 9.882380, 
9.921741, 9.960947, 10
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
        // CLA Task 1 CLAsqrt
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 sqrt_inline
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
        // Verify CLA Task 1 CLAsqrt() function
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
