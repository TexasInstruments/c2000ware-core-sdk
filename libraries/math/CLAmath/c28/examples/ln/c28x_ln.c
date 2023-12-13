//#############################################################################
//
// FILE:   c28x_ln.c
//
// TITLE:  This example calls the natural logarithm function (CLAln) of the CLA
//         math library on a test vector and compares the result with the
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
0, 0.5763479, 0.9396381, 1.205546, 1.415394, 
1.588753, 1.736452, 1.865117, 1.979099, 2.081408, 
2.174215, 2.259135, 2.337405, 2.409991, 2.477663, 
2.541044, 2.600646, 2.656895, 2.710148, 2.760707, 
2.808833, 2.854749, 2.898649, 2.940702, 2.981058, 
3.019849, 3.057190, 3.093188, 3.127934, 3.161514, 
3.194002, 3.225468, 3.255974, 3.285577, 3.314329, 
3.342277, 3.369466, 3.395934, 3.421720, 3.446858, 
3.471380, 3.495314, 3.518689, 3.541530, 3.563861, 
3.585704, 3.607080, 3.628009, 3.648509, 3.668596, 
3.688289, 3.707601, 3.726547, 3.745141, 3.763395, 
3.781322, 3.798934, 3.816240, 3.833252, 3.849980, 
3.866432, 3.882618, 3.898547, 3.914225, 3.929662, 
3.944864, 3.959838, 3.974591, 3.989130, 4.003460, 
4.017588, 4.031519, 4.045259, 4.058813, 4.072185, 
4.085381, 4.098404, 4.111261, 4.123954, 4.136488, 
4.148868, 4.161095, 4.173175, 4.185111, 4.196906, 
4.208563, 4.220087, 4.231478, 4.242742, 4.253880, 
4.264895, 4.275791, 4.286569, 4.297232, 4.307782, 
4.318223, 4.328555, 4.338782, 4.348906, 4.358927, 
4.368850, 4.378675, 4.388404, 4.398039, 4.407583, 
4.417037, 4.426401, 4.435679, 4.444872, 4.453981, 
4.463008, 4.471954, 4.480820, 4.489609, 4.498321, 
4.506958, 4.515521, 4.524012, 4.532430, 4.540779, 
4.549058, 4.557270, 4.565414, 4.573493, 4.581507, 
4.589457, 4.597344, 4.605170
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
        // CLA Task 1 CLAln
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 ln
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
        // Verify CLA Task 1 CLAln() function
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
