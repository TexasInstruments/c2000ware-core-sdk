#ifndef _FID_H_
#define _FID_H_
//#############################################################################
//
//! \file   fid.h
//!
//! \brief  Fast Integer Division
//! \author Vishal Coelho
//! \date   Dec 25, 2015
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
//! \defgroup FID_F64 Fast Integer Division Definitions and Types
//!
//! \ingroup FID_F64 
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define SIGNED_DIV_TRUNCATED    (1)
#define SIGNED_DIV_MODULO       (0)
#define SIGNED_DIV_EUCLIDEAN    (0)

#if SIGNED_DIV_TRUNCATED == 1
#define FID_i32byi32    FID_i32byi32_t
#define FID_i64byi32	FID_i64byi32_t
#define FID_i64byi64    FID_i64byi64_t
#define FID_i16byi16    FID_i16byi16_t
#define FID_i32byi16    FID_i32byi16_t
#elif SIGNED_DIV_MODULO == 1
#define FID_i32byi32    FID_i32byi32_m
#define FID_i64byi32	FID_i64byi32_m
#define FID_i64byi64    FID_i64byi64_m
#define FID_i16byi16    FID_i16byi16_m
#define FID_i32byi16    FID_i32byi16_m
#elif SIGNED_DIV_EUCLIDEAN == 1
#define FID_i32byi32    FID_i32byi32_e
#define FID_i64byi32	FID_i64byi32_e
#define FID_i64byi64    FID_i64byi64_e
#define FID_i16byi16    FID_i16byi16_e
#define FID_i32byi16    FID_i32byi16_e
#else
#error "Pick one of the signed division methods: truncated, modulo or \
euclidean or use a specific signed operation"
#endif //SIGNED_DIV_TRUNCATED
//*****************************************************************************
// typedefs
//*****************************************************************************


//*****************************************************************************
//globals
//*****************************************************************************

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Division: ui32/ui32
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 23 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_ui32byui32(uint32_t *p_num_rem, uint32_t *p_den_quo);

//! \brief Division: i32/i32 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = trunc(\frac{dividend}{divisor})                            \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor}) \f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 24 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi32_t(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: i32/i32 (Modulo or Floored)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = {\lfloor}\frac{dividend}{divisor}{\rfloor}                           \f]
//! \f[ R = dividend - divisor \times {\lfloor}\frac{dividend}{divisor}{\rfloor} \f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 24 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi32_m(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: i32/i32 (Euclidean)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = sgn(n){\lfloor}\frac{dividend}{|divisor|}{\rfloor}                    \f]
//! \f[ R = dividend-|divisor|{\times}{\lfloor}\frac{dividend}{|divisor|}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 24 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi32_e(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: i32/ui32 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = trunc(\frac{dividend}{divisor})                            \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor}) \f]
//!
//! \note 
//! -# please note that the divisor is unsigned, so you can
//! use the full 32-bit unsigned range for the denominator. When
//! calling the function be sure to cast the pointer to this
//! unsigned denominator as a signed pointer (int32_t *)
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! \return none
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 24 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byui32(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: ui64/ui32
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! \return none
//! 
//! \note 
//! -# Since the memory location that holds the divisor must also hold the 
//! quotient it must be 64-bits wide. The same is true of the memory location
//! that holds the 64-bit dividend and subsequently the 32-bit remainder
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 35 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_ui64byui32(uint64_t *p_num_rem, uint64_t *p_den_quo);

//! \brief Division: i64/i32 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = trunc(\frac{dividend}{divisor})                           \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor})\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 36 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi32_t(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/i32 (Modulo or Floored)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = {\lfloor}\frac{dividend}{divisor}{\rfloor}                          \f]
//! \f[ R = dividend - divisor \times {\lfloor}\frac{dividend}{divisor}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 36 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi32_m(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/i32 (Euclidean)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = sgn(n){\lfloor}\frac{dividend}{|divisor|}{\rfloor}                     \f]
//! \f[ R = dividend-|divisor|{\times}{\lfloor}\frac{dividend}{|divisor|}{\rfloor} \f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 36 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi32_e(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/ui32 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = trunc(\frac{dividend}{divisor})                           \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor})\f]
//!
//! \return none
//!
//! \note 
//! -# please note that the divisor is unsigned, so you can
//! use the full 32-bit unsigned range for the denominator. This 
//! variable will also hold the 33-bit signed  remainder, which must then be 
//! sign-extended to 64-bits (standard integer size). The divisor (remainder)
//! variable needs to be of signed 64-bit integer type.
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 38 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byui32(int64_t *p_num_rem, int64_t *p_den_quo);


//! \brief Division: ui64/ui64
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_ui64byui64(uint64_t *p_num_rem, uint64_t *p_den_quo);

//! \brief Division: i64/i64 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = trunc(\frac{dividend}{divisor})                           \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor})\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi64_t(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/i64 (Modulo or Floored)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = {\lfloor}\frac{dividend}{divisor}{\rfloor}                          \f]
//! \f[ R = dividend - divisor \times {\lfloor}\frac{dividend}{divisor}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi64_m(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/i64 (Euclidean)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = sgn(n){\lfloor}\frac{dividend}{|divisor|}{\rfloor}                    \f]
//! \f[ R = dividend-|divisor|{\times}{\lfloor}\frac{dividend}{|divisor|}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byi64_e(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: i64/ui64 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \f[ Q = trunc(\frac{dividend}{divisor})                            \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor}) \f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 52 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i64byui64(int64_t *p_num_rem, int64_t *p_den_quo);

//! \brief Division: ui16/ui16
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 24 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_ui16byui16(uint16_t *p_num_rem, uint16_t *p_den_quo);

//! \brief Division: i16/i16 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = trunc(\frac{dividend}{divisor})                            \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor}) \f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 26 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i16byi16_t(int16_t *p_num_rem, int16_t *p_den_quo);

//! \brief Division: i16/i16 (Modulo or Floored)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = {\lfloor}\frac{dividend}{divisor}{\rfloor}                          \f]
//! \f[ R = dividend - divisor \times {\lfloor}\frac{dividend}{divisor}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 26 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i16byi16_m(int16_t *p_num_rem, int16_t *p_den_quo);

//! \brief Division: i16/i16 (Euclidean)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = sgn(n){\lfloor}\frac{dividend}{|divisor|}{\rfloor}                    \f]
//! \f[ R = dividend-|divisor|{\times}{\lfloor}\frac{dividend}{|divisor|}{\rfloor}\f]
//!
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 26 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i16byi16_e(int16_t *p_num_rem, int16_t *p_den_quo);

//! \brief Division: ui32/ui16
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//!
//! \return none
//!
//! \note 
//! -# while the divisor (denominator) is unsigned 16-bits, the quotient
//!  is larger than 16-bit and occupies the same memory location. Therefore
//! the divisor must occupy a 32-bit location
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 26 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_ui32byui16(uint32_t *p_num_rem, uint32_t *p_den_quo);

//! \brief Division: i32/i16 (Truncated)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = trunc(\frac{dividend}{divisor})                           \f]
//! \f[ R = dividend -  divisor \times trunc(\frac{dividend}{divisor})\f]
//!
//! \return none
//!
//! \note 
//! -# while the divisor (denominator) is signed 16-bits, the quotient
//!  is larger than 16-bit and occupies the same memory location. Therefore
//! the divisor must occupy a 32-bit location
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 28 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi16_t(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: i32/i16 (Modulo or Floored)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = {\lfloor}\frac{dividend}{divisor}{\rfloor}                          \f]
//! \f[ R = dividend - divisor \times {\lfloor}\frac{dividend}{divisor}{\rfloor}\f]
//!
//! \return none
//!
//! \note 
//! -# while the divisor (denominator) is signed 16-bits, the quotient
//!  is larger than 16-bit and occupies the same memory location. Therefore
//! the divisor must occupy a 32-bit location
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 28 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi16_m(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: i16/i16 (Euclidean)
//! \param[out] p_num_rem, pointer to the dividend and subsequently remainder
//! \param[out] p_den_quo, pointer to the divisor and subsequently quotient
//! 
//! \f[ Q = sgn(n){\lfloor}\frac{dividend}{|divisor|}{\rfloor}                    \f]
//! \f[ R = dividend-|divisor|{\times}{\lfloor}\frac{dividend}{|divisor|}{\rfloor}\f]
//!
//! \return none
//!
//! \note 
//! -# while the divisor (denominator) is signed 16-bits, the quotient
//!  is larger than 16-bit and occupies the same memory location. Therefore
//! the divisor must occupy a 32-bit location
//! -# For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 28 <td> Cycle count includes the call and return
//! </table>
//
extern void FID_i32byi16_e(int32_t *p_num_rem, int32_t *p_den_quo);

//! \brief Division: f64/f64
//! \param[out] p_num, pointer to the dividend
//! \param[out] p_den, pointer to the divisor
//! \param[out] p_quo, pointer to the quotient
//! \return none
//!
//! \note For best performance, make the arguments to the function global; 
//! local variables are pushed on to the stack and will cause pipeline stalls
//! when multiple back-to-back stack accesses (read followed by write or 
//! vice versa) take place in the algorihtm.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 36 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
extern void FID_f64byf64(double *p_num, double *p_den, double *p_quo);
#else
extern void FID_f64byf64(long double *p_num, long double *p_den,
		long double *p_quo);
#endif //__TI_EABI__

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _FID_H_ definition

// End of File
