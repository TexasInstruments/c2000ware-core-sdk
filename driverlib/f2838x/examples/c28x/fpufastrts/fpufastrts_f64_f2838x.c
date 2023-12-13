//#############################################################################
//
// FILE:   FPUfastRTS_Example.c
//
// TITLE:  FPUfastRTS FPU64 Example
//
// FPUfastRTS SysCfg Example
//
// This example is a FPUfastRTS example project setup for SysConfig.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
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


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

void main(void)
{
    //
    // CPU Initialization
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
    C2000Ware_libraries_init();

    //
    // Parameter declaration
    //
    float64_t param0;
    float64_t param1;
    float64_t param2;
    float64u_t cordicResultCos;
    float64u_t cordicResultSin;
    float64u_t cordic_input;

    //
    // Parameter initialization
    //
    param0 = 1.570796326795L;
    param1 = 2.0;
    param2 = 9.0;
    cordic_input.f64 = param0;

    //
    // Result declarations
    //
    float64_t atanResult;
    float64_t atan2Result;
    float64_t cosResult;
    float64_t divResult;
    float64_t isqrtResult;
    float64_t sinResult;
    float64_t sqrtResult;

    //
    // Arc Tangent
    //
    atanResult = atan(param0);

    //
    // Arc Tangent 2
    //
    atan2Result = atan2(param0, param1);

    //
    // Cosine
    //
    cosResult = cos(param0);

    //
    // Division (uses '/' operator)
    //
    divResult = param2/param1;

    //
    // Inverse Square Root
    //
    isqrtResult = isqrt(param1);

    //
    // Sine
    //
    sinResult = sin(param0);

    //
    // Square Root
    //
    sqrtResult = sqrt(param2);

    //
    // CORDIC Sine
    //
    cordicResultSin = CORDIC_F64_sin(myCOR0_handle, cordic_input);

    //
    // CORDIC Cosine
    //
    cordicResultCos = CORDIC_F64_cos(myCOR0_handle, cordic_input);

    //
    // FID (Fast Integer Division) parameter/pointer initializations
    //
    float64_t num = 26.0;
    float64_t den = 5.0;
    float64_t quo;
    double *p_num = &num;
    double *p_den = &den;
    double *p_quo = &quo;

    uint16_t var0 = 26;
    uint16_t var1 = 5;
    uint32_t var2 = 26;
    uint32_t var3 = 5;
    uint64_t var4, var5 = 26;
    uint64_t var6, var7 = 5;

    int16_t var8, var9, var10 = 26;
    int16_t var11, var12, var13 = 5;

    int32_t var14, var15, var16, var17, var18, var19, var20 = 26;
    int32_t var21, var22, var23, var24, var25, var26, var27 = 5;

    int64_t var28, var29, var30 = 26, var31, var32, var33, var34, var35 = 26;
    int64_t var36, var37, var38, var39, var40, var41, var42, var43 = 5;

    uint16_t *p_num_rem_u16 = &var0;
    uint16_t *p_den_quo_u16 = &var1;
    uint32_t *p_num_rem_u32 = &var2;
    uint32_t *p_den_quo_u32 = &var3;
    uint64_t *p_num_rem_u64 = &var4;
    uint64_t *p_num_rem_64x32_u = &var5;
    uint64_t *p_den_quo_u64 = &var6;
    uint64_t *p_den_quo_64x32_u = &var7;

    int16_t *p_num_rem_e16 = &var8;
    int16_t *p_num_rem_m16 = &var9;
    int16_t *p_num_rem_t16 = &var10;
    int16_t *p_den_quo_e16 = &var11;
    int16_t *p_den_quo_m16 = &var12;
    int16_t *p_den_quo_t16 = &var13;

    int32_t *p_num_rem_e32 = &var14;
    int32_t *p_num_rem_m32 = &var15;
    int32_t *p_num_rem_t32 = &var16;
    int32_t *p_num_rem_iui32 = &var17;
    int32_t *p_num_rem_32x16_e = &var18;
    int32_t *p_num_rem_32x16_m = &var19;
    int32_t *p_num_rem_32x16_t = &var20;
    int32_t *p_den_quo_e32 = &var21;
    int32_t *p_den_quo_m32 = &var22;
    int32_t *p_den_quo_t32 = &var23;
    int32_t *p_den_quo_iui32 = &var24;
    int32_t *p_den_quo_32x16_e = &var25;
    int32_t *p_den_quo_32x16_m = &var26;
    int32_t *p_den_quo_32x16_t = &var27;

    int64_t *p_num_rem_e64 = &var28;
    int64_t *p_num_rem_m64 = &var29;
    int64_t *p_num_rem_t64 = &var30;
    int64_t *p_num_rem_iui64 = &var31;
    int64_t *p_num_rem_64x32_e = &var32;
    int64_t *p_num_rem_64x32_m = &var33;
    int64_t *p_num_rem_64x32_t = &var34;
    int64_t *p_num_rem_64x32_iui = &var35;
    int64_t *p_den_quo_e64 = &var36;
    int64_t *p_den_quo_m64 = &var37;
    int64_t *p_den_quo_t64 = &var38;
    int64_t *p_den_quo_iui64 = &var39;
    int64_t *p_den_quo_64x32_e = &var40;
    int64_t *p_den_quo_64x32_m = &var41;
    int64_t *p_den_quo_64x32_t = &var42;
    int64_t *p_den_quo_64x32_iui = &var43;

    //
    // Floating Point FID
    //
    FID_f64byf64(p_num, p_den, p_quo);

    //
    // 16-bit by 16-bit FID
    //
    FID_i16byi16_e(p_num_rem_e16, p_den_quo_e16);
    FID_i16byi16_m(p_num_rem_m16, p_den_quo_m16);
    FID_i16byi16_t(p_num_rem_t16, p_den_quo_t16);
    FID_ui16byui16(p_num_rem_u16, p_den_quo_u16);

    //
    // 32-bit by 32-bit FID
    //
    FID_i32byi32_e(p_num_rem_e32, p_den_quo_e32);
    FID_i32byi32_m(p_num_rem_m32, p_den_quo_m32);
    FID_i32byi32_t(p_num_rem_t32, p_den_quo_t32);
    FID_i32byui32(p_num_rem_iui32, p_den_quo_iui32);
    FID_ui32byui32(p_num_rem_u32, p_den_quo_u32);

    //
    // 32-bit by 16-bit FID
    //
    FID_i32byi16_e(p_num_rem_32x16_e, p_den_quo_32x16_e);
    FID_i32byi16_m(p_num_rem_32x16_m, p_den_quo_32x16_m);
    FID_i32byi16_t(p_num_rem_32x16_t, p_den_quo_32x16_t);
    FID_ui32byui16(p_num_rem_u32, p_den_quo_u32);

    //
    // 64-bit by 64-bit FID
    //
    FID_i64byi64_e(p_num_rem_e64, p_den_quo_e64);
    FID_i64byi64_m(p_num_rem_m64, p_den_quo_m64);
    FID_i64byi64_t(p_num_rem_t64, p_den_quo_t64);
    FID_i64byui64(p_num_rem_iui64, p_den_quo_iui64);
    FID_ui64byui64(p_num_rem_u64, p_den_quo_u64);

    //
    // 64-bit by 32-bit FID
    //
    FID_i64byi32_e(p_num_rem_64x32_e, p_den_quo_64x32_e);
    FID_i64byi32_m(p_num_rem_64x32_m, p_den_quo_64x32_m);
    FID_i64byi32_t(p_num_rem_64x32_t, p_den_quo_64x32_t);
    FID_i64byui32(p_num_rem_64x32_iui, p_den_quo_64x32_iui);
    FID_ui64byui32(p_num_rem_64x32_u, p_den_quo_64x32_u);

    while(1);
}
