//###########################################################################
//
// FILE:    f28e12x_input_xbar.h
//
// TITLE:   Definitions for the INPUT_XBAR registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28E12X_INPUT_XBAR_H
#define F28E12X_INPUT_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUT1SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT1 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT1SELECT_REG {
    Uint16  all;
    struct  INPUT1SELECT_BITS  bit;
};

struct INPUT2SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT2 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT2SELECT_REG {
    Uint16  all;
    struct  INPUT2SELECT_BITS  bit;
};

struct INPUT3SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT3 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT3SELECT_REG {
    Uint16  all;
    struct  INPUT3SELECT_BITS  bit;
};

struct INPUT4SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT4 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT4SELECT_REG {
    Uint16  all;
    struct  INPUT4SELECT_BITS  bit;
};

struct INPUT5SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT5 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT5SELECT_REG {
    Uint16  all;
    struct  INPUT5SELECT_BITS  bit;
};

struct INPUT6SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT6 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT6SELECT_REG {
    Uint16  all;
    struct  INPUT6SELECT_BITS  bit;
};

struct INPUT7SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT7 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT7SELECT_REG {
    Uint16  all;
    struct  INPUT7SELECT_BITS  bit;
};

struct INPUT8SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT8 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT8SELECT_REG {
    Uint16  all;
    struct  INPUT8SELECT_BITS  bit;
};

struct INPUT9SELECT_BITS {              // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT9 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT9SELECT_REG {
    Uint16  all;
    struct  INPUT9SELECT_BITS  bit;
};

struct INPUT10SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT10 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT10SELECT_REG {
    Uint16  all;
    struct  INPUT10SELECT_BITS  bit;
};

struct INPUT11SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT11 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT11SELECT_REG {
    Uint16  all;
    struct  INPUT11SELECT_BITS  bit;
};

struct INPUT12SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT12 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT12SELECT_REG {
    Uint16  all;
    struct  INPUT12SELECT_BITS  bit;
};

struct INPUT13SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT13 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT13SELECT_REG {
    Uint16  all;
    struct  INPUT13SELECT_BITS  bit;
};

struct INPUT14SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT14 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT14SELECT_REG {
    Uint16  all;
    struct  INPUT14SELECT_BITS  bit;
};

struct INPUT15SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT15 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT15SELECT_REG {
    Uint16  all;
    struct  INPUT15SELECT_BITS  bit;
};

struct INPUT16SELECT_BITS {             // bits description
    Uint16 SELECT:9;                    // 8:0 Select GPIO for INPUT16 signal
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union INPUT16SELECT_REG {
    Uint16  all;
    struct  INPUT16SELECT_BITS  bit;
};

struct INPUTSELECTLOCK_BITS {           // bits description
    Uint16 INPUT1SELECT:1;              // 0 Lock bit for INPUT1SELECT Register
    Uint16 INPUT2SELECT:1;              // 1 Lock bit for INPUT2SELECT Register
    Uint16 INPUT3SELECT:1;              // 2 Lock bit for INPUT3SELECT Register
    Uint16 INPUT4SELECT:1;              // 3 Lock bit for INPUT4SELECT Register
    Uint16 INPUT5SELECT:1;              // 4 Lock bit for INPUT5SELECT Register
    Uint16 INPUT6SELECT:1;              // 5 Lock bit for INPUT6SELECT Register
    Uint16 INPUT7SELECT:1;              // 6 Lock bit for INPUT7SELECT Register
    Uint16 INPUT8SELECT:1;              // 7 Lock bit for INPUT8SELECT Register
    Uint16 INPUT9SELECT:1;              // 8 Lock bit for INPUT9SELECT Register
    Uint16 INPUT10SELECT:1;             // 9 Lock bit for INPUT10SELECT Register
    Uint16 INPUT11SELECT:1;             // 10 Lock bit for INPUT11SELECT Register
    Uint16 INPUT12SELECT:1;             // 11 Lock bit for INPUT12SELECT Register
    Uint16 INPUT13SELECT:1;             // 12 Lock bit for INPUT13SELECT Register
    Uint16 INPUT14SELECT:1;             // 13 Lock bit for INPUT14SELECT Register
    Uint16 INPUT15SELECT:1;             // 14 Lock bit for INPUT15SELECT Register
    Uint16 INPUT16SELECT:1;             // 15 Lock bit for INPUT16SELECT Register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union INPUTSELECTLOCK_REG {
    Uint32  all;
    struct  INPUTSELECTLOCK_BITS  bit;
};

struct INPUT_XBAR_REGS {
    union   INPUT1SELECT_REG                 INPUT1SELECT;                 // INPUT1 Input Select Register (GPIO0 to x)
    union   INPUT2SELECT_REG                 INPUT2SELECT;                 // INPUT2 Input Select Register (GPIO0 to x)
    union   INPUT3SELECT_REG                 INPUT3SELECT;                 // INPUT3 Input Select Register (GPIO0 to x)
    union   INPUT4SELECT_REG                 INPUT4SELECT;                 // INPUT4 Input Select Register (GPIO0 to x)
    union   INPUT5SELECT_REG                 INPUT5SELECT;                 // INPUT5 Input Select Register (GPIO0 to x)
    union   INPUT6SELECT_REG                 INPUT6SELECT;                 // INPUT6 Input Select Register (GPIO0 to x)
    union   INPUT7SELECT_REG                 INPUT7SELECT;                 // INPUT7 Input Select Register (GPIO0 to x)
    union   INPUT8SELECT_REG                 INPUT8SELECT;                 // INPUT8 Input Select Register (GPIO0 to x)
    union   INPUT9SELECT_REG                 INPUT9SELECT;                 // INPUT9 Input Select Register (GPIO0 to x)
    union   INPUT10SELECT_REG                INPUT10SELECT;                // INPUT10 Input Select Register (GPIO0 to x)
    union   INPUT11SELECT_REG                INPUT11SELECT;                // INPUT11 Input Select Register (GPIO0 to x)
    union   INPUT12SELECT_REG                INPUT12SELECT;                // INPUT12 Input Select Register (GPIO0 to x)
    union   INPUT13SELECT_REG                INPUT13SELECT;                // INPUT13 Input Select Register (GPIO0 to x)
    union   INPUT14SELECT_REG                INPUT14SELECT;                // INPUT14 Input Select Register (GPIO0 to x)
    union   INPUT15SELECT_REG                INPUT15SELECT;                // INPUT15 Input Select Register (GPIO0 to x)
    union   INPUT16SELECT_REG                INPUT16SELECT;                // INPUT16 Input Select Register (GPIO0 to x)
    Uint16                                   rsvd1[14];                    // Reserved
    union   INPUTSELECTLOCK_REG              INPUTSELECTLOCK;              // Input Select Lock Register
};

//---------------------------------------------------------------------------
// INPUT_XBAR External References & Function Declarations:
//
extern volatile struct INPUT_XBAR_REGS InputXbarRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
