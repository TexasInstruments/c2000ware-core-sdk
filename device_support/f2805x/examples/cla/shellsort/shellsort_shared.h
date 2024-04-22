//###########################################################################
//
// FILE:  shellsort_shared.h
//
// TITLE: Shell Sort Shared Header Report
//
// DESCRIPTION: Declare shared Variables
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef SHELLSORT_SHARED_H_
#define SHELLSORT_SHARED_H_
#ifdef __cplusplus
extern "C" {
#endif

//
// Task 1 (C) Variables
//
#define LENGTH1 (int32)((sizeof(vector1)/sizeof(vector1[0])))
extern float32 vector1[5];
extern float32 vector1_sorted[];

//
// Task 2 (C) Variables
#define LENGTH2 (int32)((sizeof(vector2)/sizeof(vector2[0])))
extern float32 vector2[10];
extern float32 vector2_sorted[];

//
// Task 3 (C) Variables
#define LENGTH3 (int32)((sizeof(vector3)/sizeof(vector2[0])))
extern int32   vector3[9];
extern int32   vector3_sorted[];

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
// CLA C Tasks
//
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//
// C Function Prototypes
//
void test_run();
void test_report();

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /*SHELLSORT_SHARED_H_*/
