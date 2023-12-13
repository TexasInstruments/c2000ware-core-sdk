#ifndef _FIR_H_
#define _FIR_H_
//#############################################################################
//! \file include/fir.h
//!
//! \brief  Header file containing  object definitions, prototype declaration 
//! and default object initializers for FIR modules.
//!
//! \date   Mar 20, 2000
//! 
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################
  
//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>

//! 
//! \defgroup FIR Finite Impulse Response Filters

//!
//! \ingroup FIR
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define NULL    0         

//! \brief Initialization defaults for the 16-bit FIR filter
//!
#define FIR16_DEFAULTS {              \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR16_init,     \
    (void (*)(void *))FIR16_calc}    

//! \brief Initialization defaults for the 16-bit Alternate FIR filter
//!
#define FIR16_ALT_DEFAULTS {          \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR16_alt_init, \
    (void (*)(void *))FIR16_alt_calc}

//! \brief Initialization defaults for the 32-bit FIR filter
//!
#define FIR32_DEFAULTS {              \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR32_init,     \
    (void (*)(void *))FIR32_calc} 

//! \brief Initialization defaults for the 32-bit Alternate FIR filter
//!             
#define FIR32_ALT_DEFAULTS {          \
    (int32_t *)NULL,                  \
    (int32_t *)NULL,                  \
    0,                                \
    6,                                \
    0,                                \
    0,                                \
    (void (*)(void *))FIR32_alt_init, \
    (void (*)(void *))FIR32_alt_calc}


//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief 16-bit FIR filter structure
//!
typedef struct { 
    int32_t *coeff_ptr;     //!< Pointer to Filter coefficients
    int32_t * dbuffer_ptr;  //!< Delay buffer pointer              
    int16_t cbindex;        //!< Circular Buffer Index         
    int16_t order;          //!< Order of the Filter           
    int16_t input;          //!< Latest Input sample            
    int16_t output;         //!< Filter Output                 
    void (*init)(void *);   //!< Pointer to initialization function           
    void (*calc)(void *);   //!< Pointer to calculation function              
}FIR16; 

//! \brief Handle to the FIR16 object
//!
typedef FIR16 *FIR16_Handle;

//! \brief 32-bit FIR filter structure
//!
typedef struct { 
    int32_t *coeff_ptr;     //!< Pointer to Filter coefficient 
    int32_t * dbuffer_ptr;  //!< Delay buffer pointer              
    int16_t cbindex;        //!< Circular Buffer Index         
    int16_t order;          //!< Order of the Filter           
    int32_t input;          //!< Latest Input sample            
    int32_t output;         //!< Filter Output                 
    void (*init)(void *);   //!< Pointer to initialization function         
    void (*calc)(void *);   //!< Pointer to calculation function                  
}FIR32; 

//! \brief Handle to the FIR32 object
//!
typedef FIR32 *FIR32_Handle;
                                                       
//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief 16-bit FIR initialization routine
//! \param pointer (handle) to FIR16 object
//! This function zeros out the delay line buffer and, if necessary, alter
//! the "order" element of the object to make it even if its odd. This is done
//! purely to aid in the use of the DMAC operation in the filter calculation 
//! routine and should not be interpreted as a reduction in the true order of 
//! the filter
void FIR16_init(void *);

//! \brief 16-bit FIR calculation routine
//! \param pointer (handle) to FIR16 object
//! This routine implements the non-recursive difference equation of an 
//! all-zero filter(FIR), of order N. All the coefficients of an all-zero 
//! filter are assumed to be less than 1 in magnitude.
//! \note This filter works up to an order of 255, the delay line buffer must be 
//! aligned to a 256 word boundary on account of the use of the C28x circular 
//! addressing mode used in this filter
//! \note The filter coefficients need to be stored in the following order for the
//! filter to work correctly i.e. (filter size is L = Order + 1)
//! Index       LSW       MSW
//!         +---------+---------+
//!  0      | h(L/2-1)| h(L-1)  |
//!  2      | h(L/2-2)| h(L-2)  |
//!  4      | h(L/2-3)| h(L-3)  |
//!  6      | h(L/2-4)| h(L-4)  |
//!  ...    | ...     | ...     |
//!  L/2-3  | h(2)    | h(L/2+2)|
//!  L/2-2  | h(1)    | h(L/2+1)|
//!  L/2-1  | h(0)    | h(L/2)  |
//!         +---------+---------+
void FIR16_calc(void *);

//! \brief 16-bit Alternate FIR initialization routine
//! \param pointer (handle) to FIR16 object
//! This function zeros out the delay line buffer and, if necessary, alter
//! the "order" element of the object to make it even if its odd. This is done
//! purely to aid in the use of the DMAC operation in the filter calculation 
//! routine and should not be interpreted as a reduction in the true order of 
//! the filter
void FIR16_alt_init(void *);

//! \brief 16-bit Alternate FIR calculation routine
//! \param pointer (handle) to FIR16 object
//! This routine implements the non-recursive difference equation of an 
//! all-zero filter(FIR), of order N. All the coefficients of an all-zero 
//! filter are assumed to be less than 1 in magnitude.
//! \note This routine will use the LP addressing mode for circular buffer addressing
//! i.e *+XAR6[AR1%++] instead of *AR6%++, allowing for greater than 256 tap filters
//! (upto order 65535); no alignment of the delay line buffer is necessary
//! \note The filter coefficients need to be stored in the following order for the
//! filter to work correctly i.e. (filter size is L = Order + 1)
//! Index       LSW       MSW
//!         +---------+---------+
//!  0      | h(L/2-1)| h(L-1)  |
//!  2      | h(L/2-2)| h(L-2)  |
//!  4      | h(L/2-3)| h(L-3)  |
//!  6      | h(L/2-4)| h(L-4)  |
//!  ...    | ...     | ...     |
//!  L/2-3  | h(2)    | h(L/2+2)|
//!  L/2-2  | h(1)    | h(L/2+1)|
//!  L/2-1  | h(0)    | h(L/2)  |
//!         +---------+---------+
void FIR16_alt_calc(void *);

//! \brief 32-bit FIR initialization routine
//! \param pointer (handle) to FIR32 object
//! This function zeros out the delay line buffer and, if necessary, alter
//! the "order" element of the object to make it even if its odd. This is done
//! purely to aid in the use of the QMACL operation (with C28x mode circular 
//! addressing) in the filter calculation routine and should not be interpreted 
//! as a reduction in the true order of the filter
void FIR32_init(void *);

//! \brief 32-bit FIR calculation routine
//! \param pointer (handle) to FIR32 object
//! This routine implements the non-recursive difference equation of an 
//! all-zero filter(FIR), of order N. All the coefficients of an all-zero 
//! filter are assumed to be less than 1 in magnitude.
//! \note This filter works up to an order of 127, the delay line buffer must be 
//! aligned to a 256 word (128 double words) boundary on account of the use of the 
//! C28x circular addressing mode used in this filter
//! \note The filter coefficients can be stored in regular order
void FIR32_calc(void *);

//! \brief 32-bit Alternate FIR initialization routine
//! \param pointer (handle) to FIR32 object
//! This function only zeros out the delay line buffer 
void FIR32_alt_init(void *);

//! \brief 32-bit Alternate FIR calculation routine
//! \param pointer (handle) to FIR32 object
//! This routine implements the non-recursive difference equation of an 
//! all-zero filter(FIR), of order N. All the coefficients of an all-zero 
//! filter are assumed to be less than 1 in magnitude.
//! \note This routine will use the LP addressing mode for circular buffer addressing
//! i.e *+XAR6[AR1%++] instead of *AR6%++, allowing for greater than 256 tap filters
//! (upto order 65535); no alignment of the delay line buffer is necessary
//! \note The filter coefficients need to be stored in the following order for the
//! filter to work correctly i.e. (filter size is L = Order + 1)
//!
//! Index       
//!         +---------+
//!  0      | h(L-1)  |
//!  2      | h(L-2)  |
//!  4      | h(L-3)  |
//!  6      | h(L-4)  |
//!  ...    | ...     |
//!  L-3    | h(2)    |
//!  L-2    | h(1)    |
//!  L-1    | h(0)    |
//!         +---------+
void FIR32_alt_calc(void *);

//*****************************************************************************
// Sample FIR Co-efficients
//*****************************************************************************
// Even Order (50): LPF co-efficients for FIR16 module 
const int16_t FIR16_LPF6_TEST[6]={-3368,    347,  17612,  17612,    347,  -3368};

const int16_t FIR16_LPF7_TEST[7]={-891,  -4096,   9083,  21178,   9083,  -4096,   -891};


const int16_t FIR16_LPF8_TEST[8]={-1699,  -3664,   5174,  14555,  14555,   5174,  -3664,  -1699};

const int16_t FIR16_LPF16_TEST[16]={ -384,-774,947,1166,-1768,-2686,4783,14680,14680,\
                                4783,-2686,-1768,1166,947,-774,-384};

const int16_t FIR16_LPF32_TEST[32]={
      -31,    -61,     92,    122,   -186,   -248,    348,    449,   -607,
     -778,   1043,   1370,  -1909,  -2789,   4835,  14710,  14710,   4835,
    -2789,  -1909,   1370,   1043,   -778,   -607,    449,    348,   -248,
     -186,    122,     92,    -61,    -31
};
                                
const int16_t FIR16_LPF64_TEST[64] = {\
        0,     -1,      1,      2,     -4,     -5,      9,     12,    -18,\
      -23,     33,     42,    -58,    -73,     96,    118,   -153,   -185,\
      234,    281,   -350,   -418,    516,    619,   -765,   -931,   1173,\
     1490,  -1999,  -2863,   4872,  14729,  14729,   4872,  -2863,  -1999,\
     1490,   1173,   -931,   -765,    619,    516,   -418,   -350,    281,\
      234,   -185,   -153,    118,     96,    -73,    -58,     42,     33,\
      -23,    -18,     12,      9,     -5,     -4,      2,      1,     -1,\
        0
};

const int16_t FIR16_LPF128_TEST[128]={\
        0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,
        1,      1,     -1,     -1,      2,      2,     -3,     -4,      5,
        7,     -9,    -10,     13,     16,    -20,    -24,     30,     35,
      -43,    -50,     60,     70,    -83,    -96,    114,    130,   -154,
     -175,    205,    233,   -271,   -308,    357,    406,   -472,   -540,
      630,    730,   -864,  -1025,   1252,   1561,  -2050,  -2905,   4894,
    14739,  14739,   4894,  -2905,  -2050,   1561,   1252,  -1025,   -864,
      730,    630,   -540,   -472,    406,    357,   -308,   -271,    233,
      205,   -175,   -154,    130,    114,    -96,    -83,     70,     60,
      -50,    -43,     35,     30,    -24,    -20,     16,     13,    -10,
       -9,      7,      5,     -4,     -3,      2,      2,     -1,     -1,
        1,      1,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0
};

#define FIR32_LPF8_TEST {\
    -111375369,  -240131315,   339092334,   953892485,   953892485,   339092334,\
    -240131315,  -111375369}

#define FIR32_LPF16_TEST {\
    -25182461,   -50721385,    62039612,    76411275,  -115843051,  -176061088,\
    313474543,   962062071,   962062071,   313474543,  -176061088,  -115843051,\
    76411275,    62039612,   -50721385,   -25182461}

#define FIR32_LPF32_TEST {\
    -2013465,    -3972436,     6056023,     8015159,   -12191477,   -16239507,\
    22805854,    29416457,   -39784147,   -51018844,    68331981,    89804355,-125125486,\
    -182784383, 316867161,   964016297,   964016297,   316867161,  -182784383,\
    -125125486,  89804355,    68331981,   -51018844,   -39784147,    29416457,\
    22805854,   -16239507,   -12191477,     8015159,     6056023,-    3972436, -2013465}
    
#define FIR32_LPF64_TEST {\
        -18910,      -37101,       84245,      128335,     -238598,     -340733,\
        559705,      760957,    -1155143,    -1515843,     2173955,     2775512,\
      -3811543,    -4761214,     6318472,     7757046,   -10017173,   -12135127,\
      15340013,    18414170,   -22919849,   -27400773,    33814288,    40552606,\
     -50113660,   -61039555,    76903839,    97663515,  -130983784,  -187613868,\
     319323094,   965268202,   965268202,   319323094,  -187613868,  -130983784,\
      97663515,    76903839,   -61039555,   -50113660,    40552606,    33814288,\
     -27400773,   -22919849,    18414170,    15340013,   -12135127,   -10017173,\
       7757046,     6318472,    -4761214,    -3811543,     2775512,     2173955,\
      -1515843,    -1155143,      760957,      559705,     -340733,     -238598,\
        128335,       84245,      -37101,      -18910}

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif // _FIR_H_

