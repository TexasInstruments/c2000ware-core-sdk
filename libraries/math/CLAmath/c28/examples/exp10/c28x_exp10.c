//#############################################################################
//
// FILE:   c28x_exp10.c
//
// TITLE:  This example calls the base 10 exponential function (CLAexp10) of the
//         CLA math library on a test vector and compares the result with the
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
-3.141593, -3.092119, -3.042645, -2.993171, -2.943697, 
-2.894223, -2.844749, -2.795275, -2.745801, -2.696327, 
-2.646854, -2.597380, -2.547906, -2.498432, -2.448958, 
-2.399484, -2.350010, -2.300536, -2.251062, -2.201589, 
-2.152115, -2.102641, -2.053167, -2.003693, -1.954219, 
-1.904745, -1.855271, -1.805797, -1.756323, -1.706850, 
-1.657376, -1.607902, -1.558428, -1.508954, -1.459480, 
-1.410006, -1.360532, -1.311058, -1.261584, -1.212111, 
-1.162637, -1.113163, -1.063689, -1.014215, -0.9647411, 
-0.9152672, -0.8657932, -0.8163193, -0.7668455, -0.7173715, 
-0.6678976, -0.6184238, -0.5689499, -0.5194759, -0.4700021, 
-0.4205281, -0.3710543, -0.3215804, -0.2721064, -0.2226326, 
-0.1731586, -0.1236847, -0.07421085, -0.02473695, 0.02473695, 
0.07421085, 0.1236847, 0.1731586, 0.2226326, 0.2721064, 
0.3215804, 0.3710543, 0.4205281, 0.4700021, 0.5194759, 
0.5689499, 0.6184238, 0.6678976, 0.7173715, 0.7668455, 
0.8163193, 0.8657932, 0.9152672, 0.9647411, 1.014215, 
1.063689, 1.113163, 1.162637, 1.212111, 1.261584, 
1.311058, 1.360532, 1.410006, 1.459480, 1.508954, 
1.558428, 1.607902, 1.657376, 1.706850, 1.756323, 
1.805797, 1.855271, 1.904745, 1.954219, 2.003693, 
2.053167, 2.102641, 2.152115, 2.201589, 2.251062, 
2.300536, 2.350010, 2.399484, 2.448958, 2.498432, 
2.547906, 2.597380, 2.646854, 2.696327, 2.745801, 
2.795275, 2.844749, 2.894223, 2.943697, 2.993171, 
3.042645, 3.092119, 3.141593
};

float32_t resExpected[BUFFER_SIZE] = {
0.0007217841, 0.0008088747, 0.0009064735, 0.001015849, 0.001138421, 
0.001275783, 0.001429719, 0.001602229, 0.001795554, 0.002012206, 
0.002254999, 0.002527087, 0.002832006, 0.003173716, 0.003556657, 
0.003985803, 0.004466731, 0.005005687, 0.005609673, 0.006286537, 
0.007045071, 0.007895130, 0.008847756, 0.009915327, 0.01111171, 
0.01245245, 0.01395496, 0.01563877, 0.01752575, 0.01964040, 
0.02201022, 0.02466597, 0.02764217, 0.03097748, 0.03471522, 
0.03890396, 0.04359812, 0.04885867, 0.05475396, 0.06136058, 
0.06876435, 0.07706146, 0.08635970, 0.09677988, 0.1084573, 
0.1215438, 0.1362093, 0.1526443, 0.1710624, 0.1917028, 
0.2148337, 0.2407555, 0.2698051, 0.3023598, 0.3388426, 
0.3797273, 0.4255452, 0.4768916, 0.5344334, 0.5989181, 
0.6711836, 0.7521687, 0.8429254, 0.9446329, 1.058612, 
1.186345, 1.329489, 1.489905, 1.669677, 1.871141, 
2.096913, 2.349926, 2.633469, 2.951223, 3.307318, 
3.706379, 4.153591, 4.654764, 5.216408, 5.845820, 
6.551178, 7.341643, 8.227486, 9.220215, 10.33273, 
11.57947, 12.97666, 14.54242, 16.29711, 18.26352, 
20.46720, 22.93677, 25.70432, 28.80581, 32.28152, 
36.17661, 40.54168, 45.43344, 50.91545, 57.05891, 
63.94364, 71.65908, 80.30547, 89.99514, 100.8540, 
113.0230, 126.6604, 141.9432, 159.0701, 178.2635, 
199.7728, 223.8774, 250.8905, 281.1629, 315.0881, 
353.1066, 395.7125, 443.4592, 496.9670, 556.9311, 
624.1304, 699.4380, 783.8323, 878.4095, 984.3985, 
1103.176, 1236.285, 1385.456
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
        // CLA Task 1 CLAexp10
        //
        Cla1ForceTask1andWait();
        WAITSTEP;
        y1[i] = fResult1;

        //
        // CLA Task 2 exp10
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
        // Verify CLA Task 1 CLAexp10() function
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
