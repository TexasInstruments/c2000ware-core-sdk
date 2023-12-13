//#############################################################################
//
//! \file   fastintdiv_example.c
//!
//! \brief  Performs various types of fast Division using FASTINTDIV Intrinsics
//! \date   Feb 14, 2019
//
//  Group:          C2000
//  Target Device:  TMS320f28002xx
//
// The following example showcases how various FASTINTDIV intrinsics can be used
// to perform various types of division in the fastest way possible. The
// example tests each of the 21 intrinsics by providing two sets of input data
// and compares the quotient and remainder with the expect value. If both the
// values match the pass counter is incremented for every intrinsic test. If
// all the intrinsics give correct value then the value of "pass_count" should
// be 21 at the end of the code and value of "success" will be 1.
//
// Add following watch variables to expressions window
//   -: pass_count
//   -: success
//
// Number of software cycles required for each integer division intrinsic including 
// cycles for output value assignment are indicated below
//
//     16-bit by 16-bit
//               __traditional_div_i16byi16() or int/int -> 16 cycles
//               __euclidean_div_i16byi16() -> 14 cycles
//               __modulo_div_i16byi16() -> 14 cycles
//               __traditional_div_u16byu16() or uint16_t/uint16_t -> 14 cycles
//
//     32-bit by 32-bit
//               __traditional_div_i32byi32() or long/long -> 13 cycles
//               __euclidean_div_i32byi32() -> 14 cycles
//               __modulo_div_i32byi32() -> 14 cycles
//               __traditional_div_i32byu32() or long/unsigned long ->  14 cycles
//               __modulo_div_i32byu32() -> 14 cycles
//               __traditional_div_u32byu32() or unsigned long/unsigned long -> 12 cycles
//
//     32-bit by 16-bit
//               __traditional_div_i32byi16() or long/int -> 18 cycles
//               __euclidean_div_i32byi16() -> 16 cycles
//               __modulo_div_i32byi16() -> 16 cycles
//               __traditional_div_u32byu16() or unsigned long/uint16_t -> 13 cycles
//
//     64-bit by 64-bit
//               __traditional_div_i64byi64() or long long/long long -> 42 cycles
//               __euclidean_div_i64byi64() -> 42 cycles
//               __modulo_div_i64byi64() -> 42 cycles
//               __traditional_div_i64byu64() or long long/unsigned long long -> 42 cycles
//               __euclidean_div_i64byu64() -> 42 cycles
//               __modulo_div_i64byu64() -> 42 cycles
//               __traditional_div_u64byu64() or unsigned long long/unsigned long long -> 42 cycles
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include <stdlib.h>
#include "fastintdiv_example.h"

//
// Function Prototypes
//

// 16-bit by 16-bit
uint16_t test_traditional_div_i16byi16();
uint16_t test_euclidean_div_i16byi16();
uint16_t test_modulo_div_i16byi16();
uint16_t test_traditional_div_u16byu16();

// 32-bit by 32-bit
uint16_t test_traditional_div_i32byi32();
uint16_t test_euclidean_div_i32byi32();
uint16_t test_modulo_div_i32byi32();
uint16_t test_traditional_div_i32byu32();
uint16_t test_modulo_div_i32byu32();
uint16_t test_traditional_div_u32byu32();


// 32-bit by 16-bit
uint16_t test_traditional_div_i32byi16();
uint16_t test_euclidean_div_i32byi16();
uint16_t test_modulo_div_i32byi16();
uint16_t test_traditional_div_u32byu16();

// 64-bit by 64-bit
uint16_t test_traditional_div_i64byi64();
uint16_t test_euclidean_div_i64byi64();
uint16_t test_modulo_div_i64byi64();
uint16_t test_traditional_div_i64byu64();
uint16_t test_euclidean_div_i64byu64();
uint16_t test_modulo_div_i64byu64();
uint16_t test_euclidean_div_i64byi64();
uint16_t test_traditional_div_u64byu64();


//
// Globals
//
uint16_t pass_count = 0, success = 0;


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
    // Disable pin locks and enable internal pullups.
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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    //
    // Calling routines for testing the fast division intrinsics
    // and updating pass counter value
    //

    // 16-bit by 16-bit
    pass_count += test_traditional_div_i16byi16();
    pass_count += test_euclidean_div_i16byi16();
    pass_count += test_modulo_div_i16byi16();
    pass_count += test_traditional_div_u16byu16();

    // 32-bit by 32-bit
    pass_count += test_traditional_div_i32byi32();
    pass_count += test_euclidean_div_i32byi32();
    pass_count += test_modulo_div_i32byi32();
    pass_count += test_traditional_div_i32byu32();
    pass_count += test_modulo_div_i32byu32();
    pass_count += test_traditional_div_u32byu32();


    // 32-bit by 16-bit
    pass_count += test_traditional_div_i32byi16();
    pass_count += test_euclidean_div_i32byi16();
    pass_count += test_modulo_div_i32byi16();
    pass_count += test_traditional_div_u32byu16();

    // 64-bit by 64-bit
    pass_count += test_traditional_div_i64byi64();
    pass_count += test_euclidean_div_i64byi64();
    pass_count += test_modulo_div_i64byi64();
    pass_count += test_traditional_div_i64byu64();
    pass_count += test_euclidean_div_i64byu64();
    pass_count += test_modulo_div_i64byu64();
    pass_count += test_traditional_div_u64byu64();

    //
    // Updating the "success" variable based on pass counter
    //
    if (pass_count == 21)
        success = 1;
    else
        success = 0;

    //
    // Loop indefinitely
    //
    while(1)
    {

    }
}

//
// Routine for testing traditional i16/i16
//
uint16_t test_traditional_div_i16byi16()
{
    parameters_div_i16byi16 data1 = {-512,20,-25,-12}, data2 = {2477,-23,-107,16};
    ldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing euclidean i16/i16
//
uint16_t test_euclidean_div_i16byi16()
{
    parameters_div_i16byi16 data1 = {-512,20,-26,8}, data2 = {2477,-23,-107,16};
    ldiv_t result1,result2;

    result1 = __euclidean_div_i16byi16(data1.dividend, data1.divisor);
    result2 = __euclidean_div_i16byi16(data2.dividend, data2.divisor);
    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i16/i16
//
uint16_t test_modulo_div_i16byi16()
{
    parameters_div_i16byi16 data1 = {-512,20,-26,8}, data2 = {2477,-23,-108,-7};
    ldiv_t result1,result2;

    result1 = __modulo_div_i16byi16(data1.dividend, data1.divisor);
    result2 = __modulo_div_i16byi16(data2.dividend, data2.divisor);
    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional u16/u16
//
uint16_t test_traditional_div_u16byu16()
{
    parameters_div_u16byu16 data1 = {512,20,25,12}, data2 = {2477,23,107,16};
    __uldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional i32/i32
//
uint16_t test_traditional_div_i32byi32()
{
    parameters_div_i32byi32 data1 = {-19016,246,-77,-74},data2 = {10414,-83,-125,39};
    ldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing euclidean i32/i32
//
uint16_t test_euclidean_div_i32byi32()
{
    parameters_div_i32byi32 data1 = {-19016,246,-78,172}, data2 = {10414,-83,-125,39};
    ldiv_t result1,result2;

    result1 = __euclidean_div_i32byi32(data1.dividend, data1.divisor);
    result2 = __euclidean_div_i32byi32(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i32/i32
//
uint16_t test_modulo_div_i32byi32()
{
    parameters_div_i32byi32 data1 = {-19016,246,-78,172}, data2 = {10414,-83,-126,-44};
    ldiv_t result1,result2;

    result1 = __modulo_div_i32byi32(data1.dividend, data1.divisor);
    result2 = __modulo_div_i32byi32(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional i32/u32
//
uint16_t test_traditional_div_i32byu32()
{
    parameters_div_i32byu32 data1 = {-19016,246,-77,-74}, data2 = {-10414,83,-125,-39};
    ldiv_t result1,result2;

    result1 = __traditional_div_i32byu32(data1.dividend, data1.divisor);
    result2 = __traditional_div_i32byu32(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i32/u32
//
uint16_t test_modulo_div_i32byu32()
{
    parameters_div_i32byu32 data1 = {-19016,246,-78,172}, data2 = {-10414,83,-126,44};
    ldiv_t result1,result2;

    result1 = __modulo_div_i32byu32(data1.dividend, data1.divisor);
    result2 = __modulo_div_i32byu32(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional u32/u32
//
uint16_t test_traditional_div_u32byu32()
{
    parameters_div_u32byu32 data1 = {19016,246,77,74}, data2 = {10414,83,125,39};
    __uldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;
}

//
// Routine for testing traditional i32/i16
//
uint16_t test_traditional_div_i32byi16()
{
    parameters_div_i32byi16 data1 = {-19016,20,-950,-16}, data2 = {10414,-23,-452,18};
    ldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;
}

//
// Routine for testing euclidean i32/i16
//
uint16_t test_euclidean_div_i32byi16()
{
    parameters_div_i32byi16 data1 = {-19016,20,-951,4}, data2 = {10414,-23,-452,18};
    ldiv_t result1,result2;

    result1 = __euclidean_div_i32byi16(data1.dividend, data1.divisor);
    result2 = __euclidean_div_i32byi16(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i32/i16
//
uint16_t test_modulo_div_i32byi16()
{
    parameters_div_i32byi16 data1 = {-19016,20,-951,4}, data2 = {10414,-23,-453,-5};
    ldiv_t result1,result2;

    result1 = __modulo_div_i32byi16(data1.dividend, data1.divisor);
    result2 = __modulo_div_i32byi16(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional u32/u16
//
uint16_t test_traditional_div_u32byu16()
{
    parameters_div_u32byu16 data1 = {19016,20,950,16}, data2 = {10414,23,452,18};
    __uldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;
}

//
// Routine for testing traditional i64/i64
//
uint16_t test_traditional_div_i64byi64()
{
    parameters_div_i64byi64 data1 = {-3218837,1289,-2497,-204}, data2 = {5949371,-3471,-1714,77};
    lldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;
}

//
// Routine for testing euclidean i64/i64
//
uint16_t test_euclidean_div_i64byi64()
{
    parameters_div_i64byi64 data1 = {-3218837,1289,-2498,1085}, data2 = {5949371,-3471,-1714,77};
    lldiv_t result1,result2;

    result1 = __euclidean_div_i64byi64(data1.dividend, data1.divisor);
    result2 = __euclidean_div_i64byi64(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i64/i64
//
uint16_t test_modulo_div_i64byi64()
{
    parameters_div_i64byi64 data1 = {-3218837,1289,-2498,1085}, data2 = {5949371,-3471,-1715,-3394};
    lldiv_t result1,result2;

    result1 = __modulo_div_i64byi64(data1.dividend, data1.divisor);
    result2 = __modulo_div_i64byi64(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional i64/u64
//
uint16_t test_traditional_div_i64byu64()
{
    parameters_div_i64byu64 data1 = {-3218837,1289,-2497,-204}, data2 = {5949371,3471,1714,77};
    lldiv_t result1,result2;

    result1 = __traditional_div_i64byu64(data1.dividend, data1.divisor);
    result2 = __traditional_div_i64byu64(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing euclidean i64/u64
//
uint16_t test_euclidean_div_i64byu64()
{
    parameters_div_i64byu64 data1 = {-3218837,1289,-2498,1085}, data2 = {5949371,3471,1714,77};
    lldiv_t result1,result2;

    result1 = __euclidean_div_i64byu64(data1.dividend, data1.divisor);
    result2 = __euclidean_div_i64byu64(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing modulo i64/u64
//
uint16_t test_modulo_div_i64byu64()
{
    parameters_div_i64byu64 data1 = {-3218837,1289,-2498,1085}, data2 = {5949371,3471,1714,77};
    lldiv_t result1,result2;

    result1 = __modulo_div_i64byu64(data1.dividend, data1.divisor);
    result2 = __modulo_div_i64byu64(data2.dividend, data2.divisor);

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;

}

//
// Routine for testing traditional u64/u64
//
uint16_t test_traditional_div_u64byu64()
{
    parameters_div_u64byu64 data1 = {3218837,1289,2497,204}, data2 = {5949371,3471,1714,77};
    __ulldiv_t result1,result2;

    result1.quot = data1.dividend / data1.divisor;
    result1.rem = data1.dividend % data1.divisor;
    result2.quot = data2.dividend / data2.divisor;
    result2.rem = data2.dividend % data2.divisor;

    if ((result1.quot == data1.quotient) && (result1.rem == data1.remainder) &&
            (result2.quot == data2.quotient) && (result2.rem = data2.remainder))
        return 1;
    else
        return 0;
}


//
// End of File
//

