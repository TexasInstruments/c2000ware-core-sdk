//#############################################################################
//
// FILE:   c28x_sinPU.c
//
// TITLE:  This example calls the sine of a per-unit function (CLAsinPU) of the
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
2.449294e-16, 0.09878642, 0.1966064, 0.2925031, 0.3855383, 
0.4748020, 0.5594208, 0.6385669, 0.7114661, 0.7774054, 
0.8357394, 0.8858978, 0.9273896, 0.9598091, 0.9828392, 
0.9962543, 0.9999235, 0.9938107, 0.9779758, 0.9525737, 
0.9178528, 0.8741529, 0.8219014, 0.7616096, 0.6938671, 
0.6193367, 0.5387476, 0.4528881, 0.3625982, 0.2687610, 
0.1722946, 0.07414275, -0.02473443, -0.1233696, -0.2207980, 
-0.3160663, -0.4082426, -0.4964253, -0.5797516, -0.6574063, 
-0.7286299, -0.7927254, -0.8490661, -0.8971006, -0.9363590, 
-0.9664573, -0.9871011, -0.9980884, -0.9993117, -0.9907590, 
-0.9725141, -0.9447554, -0.9077544, -0.8618732, -0.8075605, 
-0.7453477, -0.6758435, -0.5997276, -0.5177448, -0.4306971, 
-0.3394361, -0.2448544, -0.1478774, -0.04945372, 0.04945372, 
0.1478774, 0.2448544, 0.3394361, 0.4306971, 0.5177448, 
0.5997276, 0.6758435, 0.7453477, 0.8075605, 0.8618732, 
0.9077544, 0.9447554, 0.9725141, 0.9907590, 0.9993117, 
0.9980884, 0.9871011, 0.9664573, 0.9363590, 0.8971006, 
0.8490661, 0.7927254, 0.7286299, 0.6574063, 0.5797516, 
0.4964253, 0.4082426, 0.3160663, 0.2207980, 0.1233696, 
0.02473443, -0.07414275, -0.1722946, -0.2687610, -0.3625982, 
-0.4528881, -0.5387476, -0.6193367, -0.6938671, -0.7616096, 
-0.8219014, -0.8741529, -0.9178528, -0.9525737, -0.9779758, 
-0.9938107, -0.9999235, -0.9962543, -0.9828392, -0.9598091, 
-0.9273896, -0.8858978, -0.8357394, -0.7774054, -0.7114661, 
-0.6385669, -0.5594208, -0.4748020, -0.3855383, -0.2925031, 
-0.1966064, -0.09878642, -2.449294e-16
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
        fVal= testValues[i]/(TWO_PI); //Angle per unit circle i.e per 2PI radians

        //
        // CLA Task 1 CLAsinPU
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 sinPU
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
        // Verify CLA Task 1 CLAsinPU() function
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
