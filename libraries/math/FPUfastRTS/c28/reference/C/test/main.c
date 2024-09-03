//#############################################################################
//! \file   reference/C/test/$FILENAME$
//! \brief  Test a particular routine
//! \author Vishal Coelho 
//! \date   19-Aug-2015
//! 
//
//  Group:            C2000
//  Target Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "fastrts.h"
#include "fid.h"
#include "fastrts_assert.h"
#include "fastrts_error.h"
#include "fastrts_cordic.h"
//*****************************************************************************
// defines
//*****************************************************************************
FASTRTS_FILENUM(100)
//*****************************************************************************
// globals
//*****************************************************************************
#if USE_FID == 0
extern fsize_t test_input[];
extern fsize_t test_golden[];
fsize_t test_output[1024]; //Allocate a maximum size
fsize_t test_error[1024];  //Allocate a maximum size
#else
#if UI32BYUI32 == 1    
extern uint32_t test_dividend[], test_divisor[], test_quotient[],
    test_remainder[];
//Allocate a maximum size
uint32_t test_output_quo[1024], test_output_rem[1024]; 
uint32_t test_error_quo[1024], test_error_rem[1024]; 
#elif I32BYI32 == 1
extern int32_t test_dividend[], test_divisor[], test_quotient[],
    test_remainder[];
//Allocate a maximum size
int32_t test_output_quo[1024], test_output_rem[1024]; 
int32_t test_error_quo[1024], test_error_rem[1024]; 
#elif I32BYUI32 == 1
extern int32_t test_dividend[], test_quotient[], test_remainder[];
extern uint32_t test_divisor[];
//Allocate a maximum size
int32_t test_output_quo[1024], test_output_rem[1024]; 
int32_t test_error_quo[1024], test_error_rem[1024]; 
#elif UI64BYUI32 == 1    
extern uint64_t test_dividend[], test_quotient[];
extern uint32_t test_divisor[],  test_remainder[];
//Allocate a maximum size
uint64_t test_output_quo[1024], test_error_quo[1024];
uint32_t test_output_rem[1024], test_error_rem[1024]; 
#elif I64BYI32 == 1
extern int64_t test_dividend[], test_quotient[];
extern int32_t test_divisor[], test_remainder[];
//Allocate a maximum size
int64_t test_output_quo[1024], test_error_quo[1024]; 
int32_t test_output_rem[1024], test_error_rem[1024]; 
#elif I64BYUI32 == 1
extern int64_t test_dividend[], test_quotient[], test_remainder[];
extern uint32_t test_divisor[];
//Allocate a maximum size
int64_t test_output_quo[1024], test_output_rem[1024]; 
int64_t test_error_quo[1024], test_error_rem[1024]; 
#elif UI64BYUI64 == 1    
extern uint64_t test_dividend[], test_quotient[];
extern uint64_t test_divisor[],  test_remainder[];
//Allocate a maximum size
uint64_t test_output_quo[1024], test_error_quo[1024];
uint64_t test_output_rem[1024], test_error_rem[1024];
#elif I64BYI64 == 1    
extern int64_t test_dividend[], test_quotient[];
extern int64_t test_divisor[],  test_remainder[];
//Allocate a maximum size
int64_t test_output_quo[1024], test_error_quo[1024];
int64_t test_output_rem[1024], test_error_rem[1024]; 
#elif I64BYUI64 == 1    
extern int64_t test_dividend[], test_quotient[], test_remainder[];
extern uint64_t test_divisor[]; 
//Allocate a maximum size
int64_t test_output_quo[1024], test_error_quo[1024];
int64_t test_output_rem[1024], test_error_rem[1024];
#elif UI16BYUI16 == 1    
extern uint16_t test_dividend[], test_divisor[], test_quotient[],
    test_remainder[];
//Allocate a maximum size
uint16_t test_output_quo[1024], test_output_rem[1024]; 
uint16_t test_error_quo[1024], test_error_rem[1024]; 
#elif I16BYI16 == 1
extern int16_t test_dividend[], test_divisor[], test_quotient[],
    test_remainder[];
//Allocate a maximum size
int16_t test_output_quo[1024], test_output_rem[1024]; 
int16_t test_error_quo[1024], test_error_rem[1024]; 
#elif UI32BYUI16 == 1    
extern uint32_t test_dividend[], test_quotient[]; 
extern uint16_t test_divisor[], test_remainder[];
//Allocate a maximum size
uint32_t test_output_quo[1024], test_error_quo[1024];
uint16_t test_output_rem[1024], test_error_rem[1024]; 
#elif I32BYI16 == 1
extern int32_t test_dividend[], test_quotient[];
extern int16_t test_divisor[], test_remainder[];
//Allocate a maximum size
int32_t test_output_quo[1024], test_error_quo[1024]; 
int16_t test_output_rem[1024], test_error_rem[1024]; 
#elif F64BYF64 == 1
extern double test_dividend[], test_quotient[];
extern double test_divisor[], test_remainder[];
//Allocate a maximum size
double test_output_quo[1024], test_error_quo[1024]; 
double test_output_rem[1024], test_error_rem[1024]; 
#else
#warn "Define an FID type"
#endif // UI32BYUI32
#endif //USE_FID


//*****************************************************************************
// main - expects 4 argument, 
// - the program name
// - the number of input tuples, 
// - type of error metric
//   1. ABS
//   2. REL
//   3. UI32
//   4. I32
//   5. UI64
//   6. I64
//   7. UI16
//   8. I16
// - the error tolerance (e.g. 1e-9 for IEEE754 and positive integers for FID)
//*****************************************************************************
int16_t main(int16_t argc, char *argv[])
{
   if(argc != 4) //Requires 4 argument
   {
       /* We print argv[0] assuming it is the program name */
       printf( "usage: %s NTUPLES ERRORTYPE TOLERANCE\n"
               "example (FPU64): ./acos 512 ABS 1.045e-10 \n"
               "example (FID)  : ./i64byi64 256 I64 1\n"
               "example (FID)  : ./f64byf64 256 ABS 1e-10\n", argv[0] );
       (void)getchar();
   }
   
   // // locals
   int16_t i, j;
   fsize_t res, num, den, x, y;
   uint32_t n_ui32, d_ui32, *pui32_q, *pui32_r;
   int32_t  n_i32, d_i32, *pi32_q, *pi32_r;
   uint64_t n_ui64, d_ui64, *pui64_q, *pui64_r;
   int64_t  n_i64, d_i64, *pi64_q, *pi64_r;
   uint16_t n_ui16, d_ui16, *pui16_q, *pui16_r;
   int16_t  n_i16, d_i16, *pi16_q, *pi16_r;
   double n_f64, d_f64, *pf64_q;
   sincos_t res_sc;
   int16_t size = atoi((const char *)argv[1]);
   char *fn = (char *)argv[0];
   char *pch;
   errorType  et;
   fsize_t tolerance = (fsize_t)atof((const char*)argv[3]);
   
   // If the program was run at the bash shell, strip out the leading ./ and
   // any other / and keep just the last token, i.e. the program name
   pch = strtok(fn,"./");
   while(pch != NULL)
   {
       fn  = pch;
       pch = strtok(NULL, "./");
   }  
   error eo;
   errorHandle eh = &eo;
   error_setSize     (eh, size);
   error_setTolerance(eh, tolerance);
#if ((USE_FID == 0) || !defined(USE_FID)) // double precision routines
   // Declare and initialize the error object
   error_setTestPtr  (eh, &test_output[0]);
   error_setGoldPtr  (eh, &test_golden[0]);
   error_setErrPtr   (eh, &test_error[0]);
#else
   error_setTestPtr  (eh, &test_output_quo[0]);
   error_setGoldPtr  (eh, &test_quotient[0]);
   error_setErrPtr   (eh, &test_error_quo[0]);
#endif  //((USE_FID == 0) || !defined(USE_FID))

   if(strcmp((const char *)argv[2],"ABS")==0U)
   {
       et = ERRORTYPE_ABSOLUTE;
   }
   else if(strcmp((const char *)argv[2],"REL")==0U)
   {
       et = ERRORTYPE_RELATIVE;
   }
   else if(strcmp((const char *)argv[2],"UI32")==0U)
   {
       et = ERRORTYPE_UI32;
   }
   else if(strcmp((const char *)argv[2],"I32")==0U)
   {
       et = ERRORTYPE_I32;
   }
   else if(strcmp((const char *)argv[2],"UI64")==0U)
   {
       et = ERRORTYPE_UI64;
   }
   else if(strcmp((const char *)argv[2],"I64")==0U)
   {
       et = ERRORTYPE_I64;
   }
   else if(strcmp((const char *)argv[2],"UI16")==0U)
   {
       et = ERRORTYPE_UI16;
   }
   else if(strcmp((const char *)argv[2],"I16")==0U)
   {
       et = ERRORTYPE_I16;
   }
   else
   {
       FASTRTS_ASSERT(0); //Invalid fourth argument
   }

#ifdef _DEBUG
   // Debugging prints
   printf("Program name is %s\n", fn);
   printf("Size of the vectors is %d\n", size);
   printf("Error Tolerance is %f\n", tolerance);
   printf("Error Metric is %s\n\n", argv[2]);
#endif 
   error_setErrType(eh, et);
#if ((USE_FID == 0) || !defined(USE_FID))
   if(strcmp(fn, "cos") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_cos(x, &FastRTS_SinCosTbl[0]);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "sin") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_sin(x, &FastRTS_SinCosTbl[0]);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "sincos") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res_sc = FastRTS_sincos(x, &FastRTS_SinCosTbl[0]);
         test_output[j++] = res_sc.s;
         test_output[j++] = res_sc.c;
      }
      size = size * 2; // Two outputs for each input
      error_setSize     (eh, size);
   }
   else if (strcmp(fn, "sqrt") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_sqrt(x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "isqrt") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_isqrt(x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "div") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         num = test_input[j++];
         den = test_input[j++];
         res = FastRTS_div(num, den);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "atan") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_atan(x, &FastRTS_Arctan2Tbl[0]);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "atan2") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         y = test_input[j++];
         x = test_input[j++];
         res = FastRTS_atan2(y, x, &FastRTS_Arctan2Tbl[0]);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "cordic_sin") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_CORDIC_sin(x);
         test_output[i] = res;
      }
   }
  else if (strcmp(fn, "cordic_cos") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_CORDIC_cos(x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "cordic_atan2") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         y = test_input[j++];
         x = test_input[j++];
         res = FastRTS_CORDIC_atan2(y, x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "exp") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_exp(x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "log") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[i];
         res = FastRTS_log(x);
         test_output[i] = res;
      }
   }
   else if (strcmp(fn, "powf") == 0U)
   {
      for(i = 0U, j = 0U; i < size; i++)
      {
         x = test_input[j++];
         y = test_input[j++];
         res = FastRTS_powf(x, y);
         test_output[i] = res;
      }
   }
   else
   {
       FASTRTS_ASSERT(0); //Invalid third argument
   }

   // Calculate the error metrics, print them
   FastRTS_error(eh);
#else //USE_FID == 1
   if (strcmp(fn, "ui32byui32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_ui32 = test_dividend[i]; // numerator
         d_ui32 = test_divisor[i];  // denominator
         pui32_q = (uint32_t *)&test_output_quo[i];
         pui32_r = (uint32_t *)&test_output_rem[i];
         FID_ui32byui32(n_ui32, d_ui32, pui32_q, pui32_r);
      }
   }
   else if (strcmp(fn, "i32byi32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i32 = test_dividend[i]; // numerator
         d_i32 = test_divisor[i];  // denominator
         pi32_q = (int32_t *)&test_output_quo[i];
         pi32_r = (int32_t *)&test_output_rem[i];
         FID_i32byi32(n_i32, d_i32, pi32_q, pi32_r);
      }
   }
   else if (strcmp(fn, "i32byui32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i32  = test_dividend[i]; // numerator
         d_ui32 = test_divisor[i];  // denominator
         pi32_q = (int32_t *)&test_output_quo[i];
         pi32_r = (int32_t *)&test_output_rem[i];
         FID_i32byui32(n_i32, d_ui32, pi32_q, pi32_r);
      }
   }
    else if (strcmp(fn, "ui64byui32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_ui64  = test_dividend[i]; // numerator
         d_ui32  = test_divisor[i];  // denominator
         pui64_q = (uint64_t *)&test_output_quo[i];
         pui32_r = (uint32_t *)&test_output_rem[i];
         FID_ui64byui32(n_ui64, d_ui32, pui64_q, pui32_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_UI32; 
   }
    else if (strcmp(fn, "i64byi32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i64  = test_dividend[i]; // numerator
         d_i32  = test_divisor[i];  // denominator
         pi64_q = (int64_t *)&test_output_quo[i];
         pi32_r = (int32_t *)&test_output_rem[i];
         FID_i64byi32(n_i64, d_i32, pi64_q, pi32_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I32; 
   }
    else if (strcmp(fn, "i64byui32") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i64  = test_dividend[i]; // numerator
         d_ui32 = test_divisor[i];  // denominator
         pi64_q = (int64_t *)&test_output_quo[i];
         pi64_r = (int64_t *)&test_output_rem[i];
         FID_i64byui32(n_i64, d_ui32, pi64_q, pi64_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I64; 
   }
    else if (strcmp(fn, "ui64byui64") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_ui64  = test_dividend[i]; // numerator
         d_ui64  = test_divisor[i];  // denominator
         pui64_q = (uint64_t *)&test_output_quo[i];
         pui64_r = (uint64_t *)&test_output_rem[i];
         FID_ui64byui64(n_ui64, d_ui64, pui64_q, pui64_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_UI64; 
   }
    else if (strcmp(fn, "i64byi64") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i64  = test_dividend[i]; // numerator
         d_i64  = test_divisor[i];  // denominator
         pi64_q = (int64_t *)&test_output_quo[i];
         pi64_r = (int64_t *)&test_output_rem[i];
         FID_i64byi64(n_i64, d_i64, pi64_q, pi64_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I64; 
   }
    else if (strcmp(fn, "i64byui64") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i64   = test_dividend[i]; // numerator
         d_ui64  = test_divisor[i];  // denominator
         pi64_q = (int64_t *)&test_output_quo[i];
         pi64_r = (int64_t *)&test_output_rem[i];
         FID_i64byui64(n_i64, d_ui64, pi64_q, pi64_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I64; 
   }
   else if (strcmp(fn, "ui16byui16") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_ui16  = test_dividend[i]; // numerator
         d_ui16  = test_divisor[i];  // denominator
         pui16_q = (uint16_t *)&test_output_quo[i];
         pui16_r = (uint16_t *)&test_output_rem[i];
         FID_ui16byui16(n_ui16, d_ui16, pui16_q, pui16_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_UI16; 
   }
   else if (strcmp(fn, "i16byi16") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i16  = test_dividend[i]; // numerator
         d_i16  = test_divisor[i];  // denominator
         pi16_q = (int16_t *)&test_output_quo[i];
         pi16_r = (int16_t *)&test_output_rem[i];
         FID_i16byi16(n_i16, d_i16, pi16_q, pi16_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I16; 
   }
   else if (strcmp(fn, "ui32byui16") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_ui32 = test_dividend[i]; // numerator
         d_ui16 = test_divisor[i];  // denominator
         pui32_q = (uint32_t *)&test_output_quo[i];
         pui16_r = (uint16_t *)&test_output_rem[i];
         FID_ui32byui16(n_ui32, d_ui16, pui32_q, pui16_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_UI16; 
   }
   else if (strcmp(fn, "i32byi16") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_i32  = test_dividend[i]; // numerator
         d_i16  = test_divisor[i];  // denominator
         pi32_q = (int32_t *)&test_output_quo[i];
         pi16_r = (int16_t *)&test_output_rem[i];
         FID_i32byi16(n_i32, d_i16, pi32_q, pi16_r);
      }
      // Set error type for the remainder
      et = ERRORTYPE_I16; 
   }
   else if (strcmp(fn, "f64byf64") == 0U)
   {
      for(i = 0U; i < size; i++)
      {
         n_f64  = test_dividend[i]; // numerator
         d_f64  = test_divisor[i];  // denominator
         pf64_q = (double *)&test_output_quo[i];
         FID_f64byf64(n_f64, d_f64, pf64_q);
      }
   }
   else
   {
       printf("Undefined Routine Called !!\n");
       FASTRTS_ASSERT(0); //Invalid third argument
   }

   // Calculate the error metrics for the quotient, print them
   FastRTS_error(eh);
   // Set the error object to the remainder matrices now
   error_setTestPtr  (eh, &test_output_rem[0]);
   error_setGoldPtr  (eh, &test_remainder[0]);
   error_setErrPtr   (eh, &test_error_rem[0]);
   // Calculate the error metrics for the remainder, print them
   error_setErrType(eh, et);
   FastRTS_error(eh);
#endif //((USE_FID == 0) || !defined(USE_FID))

    
    return 1;
}

// End of File
