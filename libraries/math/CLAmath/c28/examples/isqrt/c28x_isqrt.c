//#############################################################################
//
// FILE:   c28x_isqrt.c
//
// TITLE:  This example calls the inverse square root function (CLAisqrt) of
//         the CLA math library on a test vector and compares the result with
//         the expected results "math.h" routine
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
1, 0.7496312, 0.6251153, 0.5472918, 0.4927776, 
0.4518628, 0.4196954, 0.3935455, 0.3717441, 0.3532059, 
0.3371904, 0.3231730, 0.3107699, 0.2996934, 0.2897226, 
0.2806851, 0.2724437, 0.2648882, 0.2579283, 0.2514896, 
0.2455102, 0.2399380, 0.2347288, 0.2298448, 0.2252534, 
0.2209267, 0.2168401, 0.2129722, 0.2093041, 0.2058193, 
0.2025029, 0.1993418, 0.1963243, 0.1934398, 0.1906789, 
0.1880328, 0.1854940, 0.1830553, 0.1807103, 0.1784532, 
0.1762786, 0.1741816, 0.1721577, 0.1702028, 0.1683129, 
0.1664847, 0.1647148, 0.1630001, 0.1613379, 0.1597256, 
0.1581606, 0.1566407, 0.1551639, 0.1537280, 0.1523313, 
0.1509720, 0.1496484, 0.1483590, 0.1471024, 0.1458772, 
0.1446821, 0.1435159, 0.1423775, 0.1412657, 0.1401796, 
0.1391181, 0.1380804, 0.1370656, 0.1360728, 0.1351013, 
0.1341503, 0.1332192, 0.1323071, 0.1314135, 0.1305378, 
0.1296794, 0.1288376, 0.1280121, 0.1272022, 0.1264075, 
0.1256275, 0.1248618, 0.1241099, 0.1233715, 0.1226460, 
0.1219332, 0.1212327, 0.1205441, 0.1198672, 0.1192015, 
0.1185468, 0.1179027, 0.1172691, 0.1166455, 0.1160318, 
0.1154276, 0.1148329, 0.1142472, 0.1136703, 0.1131022, 
0.1125425, 0.1119909, 0.1114475, 0.1109118, 0.1103838, 
0.1098633, 0.1093501, 0.1088440, 0.1083449, 0.1078525, 
0.1073668, 0.1068877, 0.1064148, 0.1059482, 0.1054877, 
0.1050332, 0.1045844, 0.1041414, 0.1037039, 0.1032720, 
0.1028453, 0.1024239, 0.1020077, 0.1015965, 0.1011902, 
0.1007888, 0.1003921, 0.1000000
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
        // CLA Task 1 CLAisqrt
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 isqrt
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
        // Verify CLA Task 1 CLAisqrt() function
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
