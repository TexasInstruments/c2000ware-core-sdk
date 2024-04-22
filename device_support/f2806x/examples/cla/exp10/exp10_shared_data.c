//###########################################################################
//
// TITLE:   exp10_shared_data.c
//
// Description: Declare shared memory variables and assign them to specific 
// CLA-accessible memory locations
//
//! \addtogroup f2806x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAML2)
//!    - CLAexpTable - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - ExpRes - Result of the exponentiation operation
//!  - CPU to CLA1 Message RAM
//!    - Val - Test Input
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//
// Globals
//

//
// Ensure that all data is placed in the data rams
//

//
// Task 1 (C) Variables
//
float y[BUFFER_SIZE];
#pragma DATA_SECTION(Val,"CpuToCla1MsgRAM");
float Val;
#pragma DATA_SECTION(ExpRes,"Cla1ToCpuMsgRAM")
float ExpRes;

//
// Task 2 (C) Variables
//

//
// Task 3 (C) Variables
//

//
// Task 4 (C) Variables
//

//
// Task 5 (C) Variables
//

//
// Task 6 (C) Variables
//

//
// Task 7 (C) Variables
//

//
// Task 8 (C) Variables
//

//
// Common (C) Variables
//

//
// The Exponential table
//
#pragma DATA_SECTION(CLAexpTable,"CLA1mathTables")
float CLAexpTable[] = {
	1.0, 2.7182818285e+0, 7.3890560989e+0, 2.0085536923e+1, 
	5.4598150033e+1, 1.484131591e+2, 4.0342879349e+2, 1.0966331584e+3, 
	2.980957987e+3, 8.1030839276e+3, 2.2026465795e+4, 5.9874141715e+4, 
	1.6275479142e+5, 4.4241339201e+5, 1.2026042842e+6, 3.2690173725e+6, 
	8.8861105205e+6, 2.4154952754e+7, 6.5659969137e+7, 1.7848230096e+8, 
	4.8516519541e+8, 1.3188157345e+9, 3.5849128461e+9, 9.7448034462e+9, 
	2.648912213e+10, 7.2004899337e+10, 1.9572960943e+11, 5.320482406e+11, 
	1.4462570643e+12, 3.9313342971e+12, 1.0686474582e+13, 2.9048849665e+13, 
	7.8962960183e+13, 2.1464357979e+14, 5.8346174253e+14, 1.5860134523e+15, 
	4.3112315471e+15, 1.1719142373e+16, 3.1855931757e+16, 8.6593400424e+16, 
	2.3538526684e+17, 6.3984349353e+17, 1.7392749415e+18, 4.7278394682e+18, 
	1.2851600114e+19, 3.4934271057e+19, 9.4961194206e+19, 2.5813128862e+20, 
	7.0167359121e+20, 1.9073465725e+21, 5.1847055286e+21, 1.4093490824e+22, 
	3.8310080007e+22, 1.0413759433e+23, 2.8307533033e+23, 7.6947852651e+23, 
	2.091659496e+24, 5.6857199993e+24, 1.5455389356e+25, 4.2012104038e+25, 
	1.1420073898e+26, 3.1042979357e+26, 8.4383566687e+26, 2.2937831595e+27, 
	6.2351490808e+27, 1.6948892444e+28, 4.6071866343e+28, 1.2523631708e+29, 
	3.4042760499e+29, 9.2537817256e+29, 2.5154386709e+30, 6.8376712298e+30, 
	1.8586717453e+31, 5.0523936303e+31, 1.3733829795e+32, 3.7332419968e+32, 
	1.0148003881e+33, 2.7585134545e+33, 7.498416997e+33, 2.0382810665e+34, 
	5.5406223844e+34, 1.5060973146e+35, 4.0939969621e+35, 1.1128637548e+36, 
	3.0250773222e+36, 8.2230127146e+36, 2.2352466037e+37, 6.0760302251e+37, 
	1.651636255e+38
};

#pragma DATA_SECTION(CLALOG10_E,"CpuToCla1MsgRAM");
float CLALOG10_E = 2.30258509;

//
// Coefficients in the Taylor series expansion of exp(A/B)
//
#pragma DATA_SECTION(CLAINV1,"CpuToCla1MsgRAM")
float CLAINV1 =   1.0 ;
#pragma DATA_SECTION(CLAINV2,"CpuToCla1MsgRAM")
float CLAINV2 =   0.5 ; //1/2
#pragma DATA_SECTION(CLAINV3,"CpuToCla1MsgRAM")
float CLAINV3 =   0.333333333333333333; //1/3
#pragma DATA_SECTION(CLAINV4,"CpuToCla1MsgRAM")
float CLAINV4 =   0.25; //1/4
#pragma DATA_SECTION(CLAINV5,"CpuToCla1MsgRAM")
float CLAINV5 =   0.20; //1/5
#pragma DATA_SECTION(CLAINV6,"CpuToCla1MsgRAM")
float CLAINV6 =   0.166666666666666666; //1/6
#pragma DATA_SECTION(CLAINV7,"CpuToCla1MsgRAM")
float CLAINV7 =   0.142857142857142857; //1/7

//
// End of File
//

