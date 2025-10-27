//#############################################################################
//! \file /28P55x_vectormath.c
//!
//! \brief  Matrix and Vector Arithmetic Tests
//!
//! This example exercises the matrix, vector arithmetic routines
//!
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// 
// C2000Ware v6.00.01.00
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
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"
#include <string.h>


//!
//! \addtogroup VECTOR_EXAMPLES Matrix and Vector Arithmetic

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            64U
#define PI              3.14159265f
#define EPSILON         0.0001f
#define EPSILON1        0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Scalar inputs to the arithmetic routines
//!
const float32_t x1[SIZE] = {
    #include "data_input_vec1.h"
};

//! \brief Scalar inputs to the arithmetic routines
//!
const float32_t x2[SIZE] = {
    #include "data_input_vec2.h"
};

//! \brief Scalar inputs to mac_SP_RVxCV()
//!
const float32_t x3[SIZE] = {
    #include "data_input_vec5.h"
};


//! \brief Scalar inputs to mac_SP_i16RVxCV()
//!
const int16_t x4[SIZE] = {
    #include "data_input_vec7.h"
};

//! \brief Scalar output of the arithmetic routines
//!
float32_t y[SIZE];

//! \brief expected output from the mpy_SP_RSxRV_2()
//!
float32_t y1[SIZE] = {
    #include "data_output_vec1.h"
};

//! \brief expected output from the mpy_SP_RVxRV_2()
//!
float32_t y2[SIZE] = {
    #include "data_output_vec2.h"
};

//! \brief expected output from the mpy_SP_RSxRVxRV_2()
//!
float32_t y3[SIZE] = {
    #include "data_output_vec3.h"
};

//! \brief complex output from the mac_SP_RVxCV()
//!
complex_float p1 = {0.0, 0.0};

//! \brief expected output from the mac_SP_RVxCV()
//! In MATLAB, run the following code after generating the
//! inputs x3 and W3_c as outlined in their respective data input files
//! sum(x3 .* W3_c)
complex_float q1 = {3.459624158897680e+02 , 3.241643102658968e+02};
complex_float q2 = {3.403728390565875e+02 , 3.133186556874802e+02};

//! \brief complex output from the mac_SP_i16RVxCV()
//!
complex_float p2 = {0.0, 0.0};

//! \brief expected output from the mac_SP_i16RVxCV()
//! In MATLAB, run the following code after generating the
//! inputs x4 and W4_c as outlined in their respective data input files
//! sum(single(x4) .* W4_c)
complex_float q3 = {-9.2024438e+02, - 6.4920024e+03};
complex_float q4 = {-1.088706648280001e+03 , -6.827583302910004e+03};

//! \brief Complex inputs to the arithmetic routines
//!
const complex_float w1[SIZE] = {
    #include "data_input_vec3.h"
};

//! \brief Complex inputs to the arithmetic routines
//!
const complex_float w2[SIZE] = {
    #include "data_input_vec4.h"
};

//! \brief Complex inputs to mac_SP_RVxCV
//!
const complex_float w3[SIZE] = {
    #include "data_input_vec6.h"
};

//! \brief Complex inputs to mac_SP_i16RVxCV
//!
const complex_float w4[SIZE] = {
    #include "data_input_vec8.h"
};

//! \brief Complex output of the arithmetic routines
//!
complex_float z[SIZE];

//! \brief expected output from the mpy_SP_RVxCV()
//!
complex_float z1[SIZE] = {
    #include "data_output_vec4.h"
};

//! \brief expected output from the mpy_SP_CVxCV()
//!
complex_float z2[SIZE] = {
    #include "data_output_vec5.h"
};

//! \brief expected output from the sub_SP_CVxCV()
//!
complex_float z3[SIZE] = {
    #include "data_output_vec6.h"
};

//! \brief expected output from the add_SP_CVxCV()
//!
complex_float z4[SIZE] = {
    #include "data_output_vec7.h"
};

//! \brief expected output from the sub_SP_CSxCV()
//!
complex_float z5[SIZE] = {
    #include "data_output_vec8.h"
};

//! \brief expected output from the add_SP_CSxCV()
//!
complex_float z6[SIZE] = {
    #include "data_output_vec9.h"
};

//! \brief expected output from the mpy_SP_CVxCVC()
//!
complex_float z7[SIZE] = {
    #include "data_output_vec10.h"
};

//! \brief constant input to some of the multiplication routines
//!
float32_t c;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Matrix, Vector Arithmetic example
//! \return returns void
//!
//!  Watch Variables:
//! -# x1, x2, y Scalar inputs to the arithmetic routines
//! -# w1, w2, z Complex inputs to the arithmetic routines
//! -# c constant input to some of the multiplication routines
//!
void vec_arithmetic_test(void)
{
    int i;

    //=========================================================================
    //--- mpy_SP_RSxRV_2() test
    //=========================================================================
    c = PI;

    mpy_SP_RSxRV_2(y, x1, c, SIZE);
    for(i = 0; i < SIZE; i++){
        if(fabsf(y[i] - y1[i]) < EPSILON){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_RVxRV_2() test
    //=========================================================================
    memset(y, 0, sizeof(float)*SIZE);

    mpy_SP_RVxRV_2(y, x1, x2, SIZE);

    for(i = 0; i < SIZE; i++){
        if(fabsf(y[i] - y2[i]) < EPSILON){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_RSxRVxRV_2() test
    //=========================================================================
    c = PI;

    memset(y, 0, sizeof(float)*SIZE);

    mpy_SP_RSxRVxRV_2(y, x1, x2, c, SIZE);
    for(i = 0; i < SIZE; i++){
        if(fabsf(y[i] - y3[i]) < EPSILON){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_RVxCV() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);

    mpy_SP_RVxCV(z, w1, x1, SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z1[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z1[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_CVxCV() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);

    mpy_SP_CVxCV(z, w1, w2, SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z2[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z2[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- sub_SP_CVxCV() and add_SP_CVxCV() test
    //=========================================================================

    memset(z, 0, sizeof(complex_float)*SIZE);

    sub_SP_CVxCV(z, w1, w2, SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z3[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z3[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    memset(z, 0, sizeof(complex_float)*SIZE);

    add_SP_CVxCV(z, w1, w2, SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z4[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z4[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- sub_SP_CSxCV() and add_SP_CSxCV() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);

    sub_SP_CSxCV(z, w1, w2[0], SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z5[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z5[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    memset(z, 0, sizeof(complex_float)*SIZE);

    add_SP_CSxCV(z, w1, w2[0], SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z6[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z6[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_CVxCVC() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);

    mpy_SP_CVxCVC(z, w1, w2, SIZE);
    for(i = 0; i < SIZE; i++){
        if((fabsf(z[i].dat[0] - z7[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z7[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_CSxCS() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);

    for(i = 0; i < SIZE; i++){
        z[i] = mpy_SP_CSxCS(w1[i], w2[i]);
        if((fabsf(z[i].dat[0] - z2[i].dat[0]) < EPSILON) &&
           (fabsf(z[i].dat[1] - z2[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mac_SP_RVxCV() test
    //=========================================================================
    p1 = mac_SP_RVxCV(w3, x3, SIZE );
    if((fabsf(p1.dat[0] - q1.dat[0]) < EPSILON1) &&
       (fabsf(p1.dat[1] - q1.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }

    p1 = mac_SP_RVxCV(w3, x3, SIZE-1 );
    if((fabsf(p1.dat[0] - q2.dat[0]) < EPSILON1) &&
       (fabsf(p1.dat[1] - q2.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }
    //=========================================================================
    //--- mac_SP_i16RVxCV() test
    //=========================================================================
    p2 = mac_SP_i16RVxCV(w4, x4, SIZE );
    if((fabsf(p2.dat[0] - q3.dat[0]) < EPSILON1) &&
       (fabsf(p2.dat[1] - q3.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }

    p2 = mac_SP_i16RVxCV(w4, x4, SIZE-1 );
    if((fabsf(p2.dat[0] - q4.dat[0]) < EPSILON1) &&
       (fabsf(p2.dat[1] - q4.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }


    printf("Total of %d tests pass, and %d failure",pass,fail);
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    vec_arithmetic_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
