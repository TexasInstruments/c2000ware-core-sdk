//#############################################################################
//! \file /2837x_VectorMath/main.c
//!
//! \brief  Matrix and Vector Arithmetic Tests
//! \author David Alter
//! \date   July 18, 2012
//! 
//! This example exercises the matrix, vector arithmetic routines
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"
#include "fpu_vector.h"
#include "string.h"


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
float x1[SIZE] = {
    #include "data_input_1.h"
};

//! \brief Scalar inputs to the arithmetic routines
//!
float x2[SIZE] = {
    #include "data_input_2.h"
};

//! \brief Scalar inputs to mac_SP_RVxCV()
//!
float x3[SIZE] = {
    #include "data_input_5.h"
};


//! \brief Scalar inputs to mac_SP_i16RVxCV()
//!
int16_t x4[SIZE] = {
    #include "data_input_7.h"
};

//! \brief Scalar output of the arithmetic routines
//! 
float y[SIZE];

//! \brief expected output from the mpy_SP_RSxRV_2()
//!
float y1[SIZE] = {
    #include "data_output_1.h"
};

//! \brief expected output from the mpy_SP_RVxRV_2()
//!
float y2[SIZE] = {
    #include "data_output_2.h"
};

//! \brief expected output from the mpy_SP_RSxRVxRV_2()
//!
float y3[SIZE] = {
    #include "data_output_3.h"
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
complex_float w1[SIZE] = {
    #include "data_input_3.h"
};

//! \brief Complex inputs to the arithmetic routines
//!
complex_float w2[SIZE] = {
    #include "data_input_4.h"
};

//! \brief Complex inputs to mac_SP_RVxCV
//!
complex_float w3[SIZE] = {
    #include "data_input_6.h"
};

//! \brief Complex inputs to mac_SP_i16RVxCV
//!
complex_float w4[SIZE] = {
    #include "data_input_8.h"
};

//! \brief Complex output of the arithmetic routines
//! 
complex_float z[SIZE];

//! \brief expected output from the mpy_SP_RVxCV()
//!
complex_float z1[SIZE] = {
    #include "data_output_4.h"
};

//! \brief expected output from the mpy_SP_CVxCV()
//!
complex_float z2[SIZE] = {
    #include "data_output_5.h"
};

//! \brief expected output from the sub_SP_CVxCV()
//!
complex_float z3[SIZE] = {
    #include "data_output_6.h"
};

//! \brief expected output from the add_SP_CVxCV()
//!
complex_float z4[SIZE] = {
    #include "data_output_7.h"
};

//! \brief expected output from the sub_SP_CSxCV()
//!
complex_float z5[SIZE] = {
    #include "data_output_8.h"
};

//! \brief expected output from the add_SP_CSxCV()
//!
complex_float z6[SIZE] = {
    #include "data_output_9.h"
};

//! \brief expected output from the mpy_SP_CVxCVC()
//!
complex_float z7[SIZE] = {
    #include "data_output_10.h"
};

//! \brief constant input to some of the multiplication routines
//!
float c;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the Matrix, Vector Arithmetic example
//! \return returns a 1
//!
//!  Watch Variables:
//! -# x1, x2, y Scalar inputs to the arithmetic routines
//! -# w1, w2, z Complex inputs to the arithmetic routines
//! -# c constant input to some of the multiplication routines
//
int main(void)
{
    // Locals
    uint16_t i;

#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();
    
    //=========================================================================
    //--- mpy_SP_RSxRV_2() test
    //=========================================================================
    c = PI;

    __asm(" NOP");
    mpy_SP_RSxRV_2(y, x1, c, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if(fabs(y[i] - y1[i]) < EPSILON){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_RVxRV_2() test
    //=========================================================================

    memset(y, 0, sizeof(float)*SIZE);
    __asm(" NOP");
    mpy_SP_RVxRV_2(y, x1, x2, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if(fabs(y[i] - y2[i]) < EPSILON){
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
    __asm(" NOP");
    mpy_SP_RSxRVxRV_2(y, x1, x2, c, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if(fabs(y[i] - y3[i]) < EPSILON){
               pass++;
           }else{
               fail++;
           }
    }
    
    //=========================================================================
    //--- mpy_SP_RVxCV() test
    //=========================================================================

    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    mpy_SP_RVxCV(z, w1, x1, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z1[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z1[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mpy_SP_CVxCV() test
    //=========================================================================

    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    mpy_SP_CVxCV(z, w1, w2, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z2[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z2[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- sub_SP_CVxCV() and add_SP_CVxCV() test
    //=========================================================================

    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    sub_SP_CVxCV(z, w1, w2, SIZE);
    __asm(" NOP");
    
    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z3[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z3[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    add_SP_CVxCV(z, w1, w2, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z4[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z4[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }
    //=========================================================================
    //--- sub_SP_CSxCV() and add_SP_CSxCV() test
    //=========================================================================

    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    sub_SP_CSxCV(z, w1, w2[0], SIZE);
    __asm(" NOP");
    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z5[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z5[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }
    
    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    add_SP_CSxCV(z, w1, w2[0], SIZE);
    __asm(" NOP");
    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z6[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z6[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }
    
    //=========================================================================
    //--- mpy_SP_CVxCVC() test
    //=========================================================================
    memset(z, 0, sizeof(complex_float)*SIZE);
    __asm(" NOP");
    mpy_SP_CVxCVC(z, w1, w2, SIZE);
    __asm(" NOP");

    for(i = 0; i < SIZE; i++){
        if((fabs(z[i].dat[0] - z7[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z7[i].dat[1]) < EPSILON)){
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
        __asm(" NOP");
        z[i] = mpy_SP_CSxCS(w1[i], w2[i]);
        __asm(" NOP");
        if((fabs(z[i].dat[0] - z2[i].dat[0]) < EPSILON) &&
           (fabs(z[i].dat[1] - z2[i].dat[1]) < EPSILON)){
               pass++;
           }else{
               fail++;
           }
    }

    //=========================================================================
    //--- mac_SP_RVxCV() test
    //=========================================================================
    __asm(" NOP");
    p1 = mac_SP_RVxCV(w3, x3, SIZE );
    __asm(" NOP");
    if((fabs(p1.dat[0] - q1.dat[0]) < EPSILON1) &&
       (fabs(p1.dat[1] - q1.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }
    __asm(" NOP");
    p1 = mac_SP_RVxCV(w3, x3, SIZE-1 );
    __asm(" NOP");
    if((fabs(p1.dat[0] - q2.dat[0]) < EPSILON1) &&
       (fabs(p1.dat[1] - q2.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }
    //=========================================================================
    //--- mac_SP_i16RVxCV() test
    //=========================================================================
    __asm(" NOP");
    p2 = mac_SP_i16RVxCV(w4, x4, SIZE );
    __asm(" NOP");
    if((fabs(p2.dat[0] - q3.dat[0]) < EPSILON1) &&
       (fabs(p2.dat[1] - q3.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }
    __asm(" NOP");
    p2 = mac_SP_i16RVxCV(w4, x4, SIZE-1 );
    __asm(" NOP");
    if((fabs(p2.dat[0] - q4.dat[0]) < EPSILON1) &&
       (fabs(p2.dat[1] - q4.dat[1]) < EPSILON1)){
        pass++;
    }else{
        fail++;
    }

    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file

