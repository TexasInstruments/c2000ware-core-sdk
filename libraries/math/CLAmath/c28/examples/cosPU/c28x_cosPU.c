//#############################################################################
//
// FILE:   c28x_cosPU.c
//
// TITLE:  This example calls the cosine per-unit function (CLAcosPU) of the CLA
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
float32_t fAngle;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult1;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float32_t fResult2;
#else
#pragma DATA_SECTION(fAngle,"CpuToCla1MsgRAM")
float32_t fAngle;
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
-6.283185, -6.184237, -6.085289, -5.986342, -5.887394, 
-5.788446, -5.689498, -5.590551, -5.491603, -5.392655, 
-5.293707, -5.194759, -5.095812, -4.996864, -4.897916, 
-4.798968, -4.700020, -4.601073, -4.502125, -4.403177, 
-4.304229, -4.205282, -4.106334, -4.007386, -3.908438, 
-3.809490, -3.710542, -3.611595, -3.512647, -3.413699, 
-3.314751, -3.215803, -3.116856, -3.017908, -2.918960, 
-2.820012, -2.721065, -2.622117, -2.523169, -2.424221, 
-2.325273, -2.226326, -2.127378, -2.028430, -1.929482, 
-1.830534, -1.731586, -1.632639, -1.533691, -1.434743, 
-1.335795, -1.236848, -1.137900, -1.038952, -0.9400041, 
-0.8410563, -0.7421085, -0.6431607, -0.5442129, -0.4452651, 
-0.3463173, -0.2473695, -0.1484217, -0.04947390, 0.04947390, 
0.1484217, 0.2473695, 0.3463173, 0.4452651, 0.5442129, 
0.6431607, 0.7421085, 0.8410563, 0.9400041, 1.038952, 
1.137900, 1.236848, 1.335795, 1.434743, 1.533691, 
1.632639, 1.731586, 1.830534, 1.929482, 2.028430, 
2.127378, 2.226326, 2.325273, 2.424221, 2.523169, 
2.622117, 2.721065, 2.820012, 2.918960, 3.017908, 
3.116856, 3.215803, 3.314751, 3.413699, 3.512647, 
3.611595, 3.710542, 3.809490, 3.908438, 4.007386, 
4.106334, 4.205282, 4.304229, 4.403177, 4.502125, 
4.601073, 4.700020, 4.798968, 4.897916, 4.996864, 
5.095812, 5.194759, 5.293707, 5.392655, 5.491603, 
5.590551, 5.689498, 5.788446, 5.887394, 5.986342, 
6.085289, 6.184237, 6.283185
};

float32_t resExpected[BUFFER_SIZE] = {
1, 0.9951087, 0.9804825, 0.9562646, 0.9226918, 
0.8800927, 0.8288838, 0.7695664, 0.7027203, 0.6289998, 
0.5491263, 0.4638804, 0.3740970, 0.2806534, 0.1844648, 
0.08647121, -0.01236835, -0.1110864, -0.2087183, -0.3043078, 
-0.3969209, -0.4856506, -0.5696297, -0.6480363, -0.7201030, 
-0.7851254, -0.8424671, -0.8915673, -0.9319457, -0.9632069, 
-0.9850455, -0.9972476, -0.9996940, -0.9923608, -0.9753196, 
-0.9487371, -0.9128735, -0.8680795, -0.8147932, -0.7535362, 
-0.6849077, -0.6095788, -0.5282867, -0.4418265, -0.3510439, 
-0.2568274, -0.1600982, -0.06180295, 0.03709688, 0.1356339, 
0.2328440, 0.3277762, 0.4195019, 0.5071239, 0.5897847, 
0.6666759, 0.7370452, 0.8002042, 0.8555351, 0.9024965, 
0.9406291, 0.9695598, 0.9890057, 0.9987764, 0.9987764, 
0.9890057, 0.9695598, 0.9406291, 0.9024965, 0.8555351, 
0.8002042, 0.7370452, 0.6666759, 0.5897847, 0.5071239, 
0.4195019, 0.3277762, 0.2328440, 0.1356339, 0.03709688, 
-0.06180295, -0.1600982, -0.2568274, -0.3510439, -0.4418265, 
-0.5282867, -0.6095788, -0.6849077, -0.7535362, -0.8147932, 
-0.8680795, -0.9128735, -0.9487371, -0.9753196, -0.9923608, 
-0.9996940, -0.9972476, -0.9850455, -0.9632069, -0.9319457, 
-0.8915673, -0.8424671, -0.7851254, -0.7201030, -0.6480363, 
-0.5696297, -0.4856506, -0.3969209, -0.3043078, -0.2087183, 
-0.1110864, -0.01236835, 0.08647121, 0.1844648, 0.2806534, 
0.3740970, 0.4638804, 0.5491263, 0.6289998, 0.7027203, 
0.7695664, 0.8288838, 0.8800927, 0.9226918, 0.9562646, 
0.9804825, 0.9951087, 1
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
        fAngle = testValues[i]/(TWO_PI); //Angle per unit circle i.e per 2PI radians

        //
        // CLA Task 1 CLAcosPU
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 cosPU
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
        // Verify CLA Task 1 CLAcosPU() function
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
