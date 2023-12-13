//#############################################################################
// \file     main.c
// \breif    Test the TMU instructions
// \author   original: Alex Tessarolo 
// \history	
//
// \note 
// -# This is built using g++ and make files
// -# Target is an x86 system
//
// Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//
//
//#############################################################################
#include "TMU.h"
//*****************************************************************************
// globals
//*****************************************************************************
FILE *OutPtr;
char OutputFileName[40];

F32_UI32 X;
F32_UI32 Z;
F32_UI32 Y1;
F32_UI32 Y3;
F32_UI32 Y4;
F32_UI32 Q1;
F32_UI32 Q3;

// <<VC161025: had to change long double to double for the following vars>>
double TestCount;

double ErrorMaxY3posF64;
double ErrorMaxY3negF64;
double ErrorAvgY3posF64;
double ErrorAvgY3negF64;
double ErrorCountY3posF64;
double ErrorCountY3negF64;
double ErrorCountY3posF64_half;
double ErrorCountY3negF64_half;

double ErrorMaxY4posF64;
double ErrorMaxY4negF64;
double ErrorAvgY4posF64;
double ErrorAvgY4negF64;
double ErrorCountY4posF64;
double ErrorCountY4negF64;

double Y1QuadrantF64;
double Y1RatioF64;
double Y3QuadrantF64;
double Y3RatioF64;
double Y3ErrorPosF64;
double Y3ErrorNegF64;
//*****************************************************************************
// prototypes
//*****************************************************************************
extern void SQRTF32_Test(void);
extern void DIVF32_Test(void);
extern void SINF32_Test(void);
extern void COSF32_Test(void);
extern void ATANF32_Test(void);
//===========================================================================
// Start Of Program: main
//===========================================================================

int main(int argc, char* argv[])
{   
   if(argc < 2U) //Requires 2 argument
   {
       /* We print argv[0] assuming it is the program name */
       printf( "\n\nusage: %s TMU_INSTRUCTION\n"
               "example: %s SQRT \n"
               "Pick from the following tests \n"
               "1. SQRT \n"
               "2. DIV \n"
               "3. ATAN \n"
               "4. SINCOS \n"
               "5. QUAD \n"
               ,argv[0], argv[0]);
       (void)getchar();
   }     
   
   if(strcmp((const char *)argv[1], "SQRT")==0U)
   {
        printf("\nTest TMU SQRTF32 Algorithms, Version %s, Table Size %3d", VERSION, SQRT_TABLE_SIZE);
        printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");
    
        sprintf(OutputFileName, "SQRTF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, SQRT_TABLE_SIZE);
    
        if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
        {  
            printf("\n");
            printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
            printf("\n");
            exit(0);
        }           
    
        fprintf(OutPtr,  ";;##########################################################################");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Title:     TMU SQRTF32 Algorithm Test Results");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Version:   %s", VERSION );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;TableSize: %3d", SQRT_TABLE_SIZE );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;##########################################################################");
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n");
    
        // Run algorithm:
        SQRTF32_Generate_Coefficients();
        SQRTF32_Test();
    
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;; End Of File.");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n");
    
        printf("\n");
        printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
        printf("\n");
   }
   else if (strcmp((const char *)argv[1], "DIV")==0U)
   {    
        printf("\nTest TMU DIVF32 Algorithms, Version %s, Table Size %3d", VERSION, DIV_TABLE_SIZE);
        printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");
    
        sprintf(OutputFileName, "DIVF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, DIV_TABLE_SIZE);
    
        if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
        {  
            printf("\n");
            printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
            printf("\n");
            exit(0);
        }           
    
        fprintf(OutPtr,  ";;##########################################################################");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Title:     TMU DIVF32 Algorithm Test Results");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Version:   %s", VERSION );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;TableSize: %3d", DIV_TABLE_SIZE );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;##########################################################################");
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n");
    
        // Run algorithm:
        DIVF32_Generate_Coefficients();
        DIVF32_Test();
    
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;; End Of File.");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n");
    
        printf("\n");
        printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
        printf("\n");
   }
   else if (strcmp((const char *)argv[1], "SINCOS")==0U)
   {
        printf("\nTest TMU SINF32 and COSF32 Algorithms, Version %s, Table Size %3d", SINCOS_VERSION, SINCOS_TABLE_SIZE);
        printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");
    
        #if	(RETURN_FLOAT == 1)
            sprintf(OutputFileName, "SINF32_COSF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, SINCOS_TABLE_SIZE);
        #else
            sprintf(OutputFileName, "SINF32_COSF32_Results_long_Q%2d_TableSize%3d.txt", Q_RESULT, SINCOS_TABLE_SIZE);
        #endif
    
        if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
        {  
            printf("\n");
            printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
            printf("\n");
            exit(0);
        }           
    
        fprintf(OutPtr,  ";;##########################################################################");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Title:     TMU SINF32 and COSF32 Algorithm Test Results");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Version:   %s", SINCOS_VERSION );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;TableSize: %3d", SINCOS_TABLE_SIZE );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;##########################################################################");
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n");
    
        // Run algorithm:
        SINCOSF32_Generate_Coefficients();
        SINF32_Test();
        COSF32_Test();
    
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;; End Of File.");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n");
    
        printf("\n");
        printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
        printf("\n");
   }
   else if (strcmp((const char *)argv[1], "ATAN")==0U)
   {
        printf("\nTest TMU ATANF32 Algorithm, Version %s, Table Size %3d", ATAN_VERSION, ATAN_TABLE_SIZE);
        printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");
    
        sprintf(OutputFileName, "ATANF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, ATAN_TABLE_SIZE);
    
        if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
        {  
            printf("\n");
            printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
            printf("\n");
            exit(0);
        }           
    
        fprintf(OutPtr,  ";;##########################################################################");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Title:     TMU ATANF32 Algorithm Test Results");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Version:   %s",ATAN_VERSION );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;TableSize: %3d", ATAN_TABLE_SIZE );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;##########################################################################");
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n");
    
        // Run algorithm:
        ATANF32_Generate_Coefficients();
        ATANF32_Test();
    
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;; End Of File.");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n");
    
        printf("\n");
        printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
        printf("\n");
   }
   else if (strcmp((const char *)argv[1], "QUAD")==0U)
   {
        printf("\nTest TMU QUADF32 Algorithms, Version %s, Table Size %3d", QUAD_VERSION, DIV_TABLE_SIZE);
        printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");
    
        sprintf(OutputFileName, "QUADF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, DIV_TABLE_SIZE);
    
        if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
        {  
            printf("\n");
            printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
            printf("\n");
            exit(0);
        }           
    
        fprintf(OutPtr,  ";;##########################################################################");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Title:     TMU QUADF32 Algorithm Test Results");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;Version:   %s", QUAD_VERSION );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;TableSize: %3d", DIV_TABLE_SIZE );
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;;##########################################################################");
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n");
    
        // Run algorithm:
        DIVF32_Generate_Coefficients();
        QUADF32_Test();
    
        fprintf(OutPtr,"\n");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n;; End Of File.");
        fprintf(OutPtr,"\n;;");
        fprintf(OutPtr,"\n");
    
        printf("\n");
        printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
        printf("\n");
   }
   else
   {
      /* We print argv[0] assuming it is the program name */
       printf( "Illegal Option\n"
               "\n\nusage: %s TMU_INSTRUCTION\n"
               "example: %s SQRT \n"
               "Pick from the following tests \n"
               "1. SQRT \n"
               "2. DIV \n"
               "3. ATAN \n"
               "4. SINCOS  \n"
               "5. QUAD \n"
               ,argv[0], argv[0]);
       exit(1); // Illegal option
   }
    fcloseall();
	exit(0); 		
} 		          		                                                           

//===========================================================================
// Print results
//===========================================================================

void PrintResult(void)
{
	fprintf(OutPtr,"\nTest Count = %16.1f", TestCount);
	fprintf(OutPtr,"\nError For Hardware Emulation : pos (Max, Avg, Count, Half) > %16.14f, %16.14f, %16.1f, %16.1f", (ErrorMaxY3posF64 * Q_SCALE), ((ErrorAvgY3posF64/ErrorCountY3posF64) * Q_SCALE), ErrorCountY3posF64, ErrorCountY3posF64_half);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count, Half) > %16.14f, %16.14f, %16.1f, %16.1f", (ErrorMaxY3negF64 * Q_SCALE), ((ErrorAvgY3negF64/ErrorCountY3negF64) * Q_SCALE), ErrorCountY3negF64, ErrorCountY3negF64_half);
	fprintf(OutPtr,"\nError For FastRTS  Emulation : pos (Max, Avg, Count      ) > %16.14f, %16.14f, %16.1f",         (ErrorMaxY4posF64 * Q_SCALE), ((ErrorAvgY4posF64/ErrorCountY4posF64) * Q_SCALE), ErrorCountY4posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count      ) > %16.14f, %16.14f, %16.1f",         (ErrorMaxY4negF64 * Q_SCALE), ((ErrorAvgY4negF64/ErrorCountY4negF64) * Q_SCALE), ErrorCountY4negF64);
}

void ATANF32_PrintResult(void)
{
	fprintf(OutPtr,"\nTest Count = %16.1f", TestCount);
	fprintf(OutPtr,"\nError For Hardware Emulation : pos (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY3posF64 * Q_SCALE), ((ErrorAvgY3posF64/ErrorCountY3posF64) * Q_SCALE), ErrorCountY3posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY3negF64 * Q_SCALE), ((ErrorAvgY3negF64/ErrorCountY3negF64) * Q_SCALE), ErrorCountY3negF64);
	fprintf(OutPtr,"\nError For FastRTS  Emulation : pos (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY4posF64 * Q_SCALE), ((ErrorAvgY4posF64/ErrorCountY4posF64) * Q_SCALE), ErrorCountY4posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY4negF64 * Q_SCALE), ((ErrorAvgY4negF64/ErrorCountY4negF64) * Q_SCALE), ErrorCountY4negF64);
}

void QUADF32_PrintResult(void)
{
	fprintf(OutPtr,"\n\nZ input                      :     > %16.14f", Z.f32 );
	fprintf(OutPtr,"\nX input                      :     > %16.14f", X.f32 );
	fprintf(OutPtr,"\nReference Ratio              :     > %16.14f", Y1RatioF64 );
	fprintf(OutPtr,"\nHardware  Ratio              :     > %16.14f", Y3.f32 );
	fprintf(OutPtr,"\nError For Hardware Emulation : pos > %16.14f", (Y3ErrorPosF64 * Q_SCALE) );
	fprintf(OutPtr,"\n                             : neg > %16.14f", (Y3ErrorNegF64 * Q_SCALE) );
	fprintf(OutPtr,"\nReference Quadrant           :     > %16.14f", Y1QuadrantF64 );
	fprintf(OutPtr,"\nHardware  Quadrant           :     > %16.14f", Q3.f32 );
}

// End of file
