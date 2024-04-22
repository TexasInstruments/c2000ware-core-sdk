#ifndef _FPU_H_
#define _FPU_H_
//#############################################################################
//! \file fpu.h
//!
//! \brief  FPU Register Definitions
//! \author Vishal Coelho
//! \date   Dec 25, 2012
//
//  Group:          C2000
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************
typedef union{
    float32_t    f32;
    int32_t  i32;
    uint32_t ui32;
}reg32_t;

typedef union{
#ifdef __TI_EABI__
    double      f64;
#else
    long double f64;
#endif
    int64_t     i64;
    uint64_t    ui64;
    struct {
        reg32_t  L;
        reg32_t  H;
    };
}reg64_t;
//*****************************************************************************
// defines
//*****************************************************************************
// masks for the status flag bits
#define MASK_LVF         (1 << 0 )
#define MASK_LUF         (1 << 1 )
#define MASK_NF          (1 << 2 )
#define MASK_ZF          (1 << 3 )
#define MASK_NI          (1 << 4 )
#define MASK_ZI          (1 << 5 )
#define MASK_TF          (1 << 6 )
#define MASK_RNDF32      (1 << 9 )
#define MASK_RNDF64      (1 << 10)
#define MASK_SHDWS       (1 << 31)


//! \brief FPU status register
//
struct STF_BITS {     // bits description
    uint16_t    LVF:1;      //!< 0     Latched Overflow Float flag bit
    uint16_t    LUF:1;      //!< 1     Latched underflow float32_t flag bit
    uint16_t    NF:1;       //!< 2     Negative float32_t flag bit
    uint16_t    ZF:1;       //!< 3     Zero float32_t flag bit
    uint16_t    NI:1;       //!< 4     Negative integer flag bit
    uint16_t    ZI:1;       //!< 5     Zero integer flag bit
    uint16_t    TF:1;       //!< 6     Test flag bit
    uint16_t    rsvd1:2;    //!< 8:7   reserved
    uint16_t    RNDF32:1;   //!< 9     Round f32 mode
    uint16_t    RNDF64:1;   //!< 10    Round f64 mode
    uint16_t    rsvd2:5;    //!< 15:11 reserved
    uint16_t    rsvd3:15;   //!< 30:16 reserved
    uint16_t    SHDWS:1;    //!< 31    Shadow mode status bit
};

union STF_REG {
    uint32_t            all;
    struct STF_BITS     bit;
};

//! \brief FPU register space
//! \note
//! - The registers are mapped to data space only (like peripherals on C28x devices). Program
//!   space data reads or writes are ignored. debug reads/writes work
//! - All registers are reset to zero on system reset (SYSRSn).
//! - The RB register is part of the C28-CPI core but is made visible (read only to CPU) in the
//!   memory map. Refer to "CPI Specification" for more details.
struct FPU_REG{
    uint32_t            _RB;
    union STF_REG       _STF;
    uint32_t            rsvd1[6];
    reg64_t             _R0;
    reg64_t             _R1;
    reg64_t             _R2;
    reg64_t             _R3;
    reg64_t             _R4;
    reg64_t             _R5;
    reg64_t             _R6;
    reg64_t             _R7;
    uint32_t            rsvd2[104];
};

extern volatile struct FPU_REG FpuRegs;


#ifdef __cplusplus
}
#endif // extern "C"
#endif //end of _FPU_H_ definition
