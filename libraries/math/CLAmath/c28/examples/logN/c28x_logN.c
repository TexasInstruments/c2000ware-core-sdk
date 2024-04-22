//#############################################################################
//
// FILE:   c28x_logN.c
//
// TITLE:  This example calls the logarithm(base N) function (CLAlogN) of the
//         CLA math library on a test vector and compares the result with the
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
    1.0000000,  1.7795276,  2.5590551, 3.3385827,
    4.1181102,  4.8976378,  5.6771654, 6.4566929,
    7.2362205,  8.0157480,  8.7952756, 9.5748031,
    10.3543307, 11.1338583, 11.9133858,12.6929134,
    13.4724409, 14.2519685, 15.0314961,15.8110236,
    16.5905512, 17.3700787, 18.1496063,18.9291339,
    19.7086614, 20.4881890, 21.2677165,22.0472441,
    22.8267717, 23.6062992, 24.3858268,25.1653543,
    25.9448819, 26.7244094, 27.5039370,28.2834646,
    29.0629921, 29.8425197, 30.6220472,31.4015748,
    32.1811024, 32.9606299, 33.7401575,34.5196850,
    35.2992126, 36.0787402, 36.8582677,37.6377953,
    38.4173228, 39.1968504, 39.9763780,40.7559055,
    41.5354331, 42.3149606, 43.0944882,43.8740157,
    44.6535433, 45.4330709, 46.2125984,46.9921260,
    47.7716535, 48.5511811, 49.3307087,50.1102362,
    50.8897638, 51.6692913, 52.4488189,53.2283465,
    54.0078740, 54.7874016, 55.5669291,56.3464567,
    57.1259843, 57.9055118, 58.6850394,59.4645669,
    60.2440945, 61.0236220, 61.8031496,62.5826772,
    63.3622047, 64.1417323, 64.9212598,65.7007874,
    66.4803150, 67.2598425, 68.0393701,68.8188976,
    69.5984252, 70.3779528, 71.1574803,71.9370079,
    72.7165354, 73.4960630, 74.2755906,75.0551181,
    75.8346457, 76.6141732, 77.3937008,78.1732283,
    78.9527559, 79.7322835, 80.5118110,81.2913386,
    82.0708661, 82.8503937, 83.6299213,84.4094488,
    85.1889764, 85.9685039, 86.7480315,87.5275591,
    88.3070866, 89.0866142, 89.8661417,90.6456693,
    91.4251969, 92.2047244, 92.9842520,93.7637795,
    94.5433071, 95.3228346, 96.1023622,96.8818898,
    97.6614173, 98.4409449, 99.2204724,100.0000000,
};

float32_t resExpected[BUFFER_SIZE] = {
    0.0000000,  0.5034794,  0.8208383, 1.0531274,
    1.2364440,  1.3878846,  1.5169099, 1.6293077,
    1.7288786,  1.8182526,  1.8993255, 1.9735092,
    2.0418833,  2.1052921,  2.1644081, 2.2197759,
    2.2718427,  2.3209799,  2.3674998, 2.4116671,
    2.4537084,  2.4938190,  2.5321684, 2.5689049,
    2.6041586,  2.6380447,  2.6706652, 2.7021113,
    2.7324647,  2.7617988,  2.7901797, 2.8176675,
    2.8443167,  2.8701770,  2.8952936, 2.9197083,
    2.9434591,  2.9665812,  2.9891071, 3.0110667,
    3.0324878,  3.0533961,  3.0738157, 3.0937689,
    3.1132765,  3.1323580,  3.1510315, 3.1693142,
    3.1872222,  3.2047703,  3.2219730, 3.2388433,
    3.2553941,  3.2716370,  3.2875835, 3.3032441,
    3.3186289,  3.3337474,  3.3486087, 3.3632214,
    3.3775937,  3.3917333,  3.4056478, 3.4193440,
    3.4328289,  3.4461087,  3.4591897, 3.4720777,
    3.4847783,  3.4972969,  3.5096386, 3.5218084,
    3.5338110,  3.5456509,  3.5573325, 3.5688599,
    3.5802372,  3.5914682,  3.6025567, 3.6135062,
    3.6243201,  3.6350018,  3.6455545, 3.6559812,
    3.6662849,  3.6764685,  3.6865348, 3.6964863,
    3.7063258,  3.7160557,  3.7256784, 3.7351963,
    3.7446116,  3.7539265,  3.7631431, 3.7722635,
    3.7812896,  3.7902235,  3.7990669, 3.8078216,
    3.8164896,  3.8250723,  3.8335715, 3.8419889,
    3.8503259,  3.8585841,  3.8667649, 3.8748699,
    3.8829003,  3.8908576,  3.8987431, 3.9065580,
    3.9143036,  3.9219812,  3.9295919, 3.9371368,
    3.9446171,  3.9520339,  3.9593883, 3.9666813,
    3.9739139,  3.9810871,  3.9882019, 3.9952592,
    4.0022599,  4.0092050,  4.0160953, 4.0229317,
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
        // CLA Task 1 CLAlogN
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

//        //
//        // CLA Task 2 logN
//        //
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
        // Verify CLA Task 1 CLAlogN() function
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
