;;#############################################################################
;;! \file examples/common/fastrts_error.asm
;;!
;;! \brief  Error Computation Function
;;! \author Vishal Coelho
;;
;; DESCRIPTION:
;;
;;   This function computes the double precision error between the output
;;   obtained from running one of the library routines on the target
;;   devices and the golden reference obtained from running a similar
;;   routine in MATLAB on an x86 platform.
;;
;;   The error is stored to an array and then compared against a user provided
;;   tolerance value. If the error is found to be within bounds the function
;;   returns a 1, else a -1. It also calculates how many ULPs of difference
;;   exist between the output and golden and returns it in a user passed
;;   variable. If the ULPs are within tolerance the function returns 2
;;
;; FUNCTIONS:
;;
;;  int16_t FastRTS_Example_calcError(const float64_t *p_out,
;;                                    const float64_t *p_gold,
;;                                    const float64_t *p_lderr,
;;                                    const uint64_t  *p_ullerr,
;;                                    const float64_t ldtol,
;;                                    const uint64_t  ulltol);
;;
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;;      lderr  = out - gold
;;      ullerr = out - gold, where - is a 64-bit unsigned integer subtraction
;;                           out and gold are merely interpreted as unsigned
;;                           long long integers
;;      if (|lderr| < ldtol){
;;          if(|ullerr| < ulltol){
;;              return 2
;;          }else{
;;              return 1
;;          }
;;      }else{
;;          return -1
;;      }
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU64
;;
;;#############################################################################
;;
;;
;; $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
;;             http://www.ti.com/ ALL RIGHTS RESERVED $
;;#############################################################################


;; the includes
;;    .cdecls C, LIST, "fastrts_examples_setup.h"

;; external references
    .if __TI_EABI__
        .ref    __c28xabi_cmpull
    .else
        .ref    ULL$$CMP
    .endif
    

;;*****************************************************************************
;; Register Usage:
;;   XAR0  : p_ldtol
;;   XAR4  : arg(p_out)
;;   XAR5  : arg(p_gold)
;;   XAR6  : p_lderr
;;   XAR7  : p_ullerr
;;   R0    : out
;;   R1    : gold
;;   R2    : lderr
;;   R3    : ldtol
;;   ACC:P : arg(ulltol) / gold (treat as unsigned long long)
;;
;; Stack Usage:
;;
;;   |_______|
;;   |_______|<- Stack Pointer(SP) <---SP
;;   |_______|<- cmp_arg_ulltol_h  (SP-2) <----.--LF
;;   |_______|<- cmp_arg_ulltol_l  (SP-4) <----'
;;   |_______|<- rpc of calling fn (SP-6)
;;   |_______|<- p_lderr  (SP-8)
;;   |_______|<- p_ullerr (SP-10)
;;   |_______|<- p_ldtol  (SP-12)
;;
;;*****************************************************************************
LF_SIZE     .set   4

    .page
    .if __TI_EABI__
    .asg FastRTS_Example_calcError, _FastRTS_Example_calcError
    .endif
    .global _FastRTS_Example_calcError
    .sect   ".text"
_FastRTS_Example_calcError:
    .asmfunc
    .asg    *-SP[2],  CMP_ARG_ULLTOL_H
    .asg    *-SP[4],  CMP_ARG_ULLTOL_L
    .asg    *-SP[8],  PTR_LDERR
    .asg    *-SP[10], PTR_ULLERR
    .asg    *-SP[12], PTR_LDTOL
    ADDB    SP, #LF_SIZE
    MOVL    XAR0, PTR_LDTOL
    MOVL    XAR6, PTR_LDERR
    MOVL    XAR7, PTR_ULLERR
    MOVL    CMP_ARG_ULLTOL_L, P     ; store ulltol to the local frame
    MOVL    CMP_ARG_ULLTOL_H, ACC   ; to be used as the second argument to
                                    ; ULL$CMP later on
    ZAPA
    MOV32   R0L, *+XAR4[0]          ; R0 = out
    MOV32   R0H, *+XAR4[2]
    MOV32   R1L, *+XAR5[0]          ; R1 = gold
    MOV32   R1H, *+XAR5[2]
;;-----------------------------------------------------------------------------
;; Do the ULP (unsigned long long) comparison
;;-----------------------------------------------------------------------------
    MOVL    P, *+XAR4[0]            ; ACC:P = out (treat as unsigned long long)
    MOVL    ACC, *+XAR4[2]
    SUBUL   P, *+XAR5[0]            ; ACC:P = out - gold (ull subtraction)
    SUBBL   ACC, *+XAR5[2]          ;
    CMP64   ACC:P                   ; if ACC:P < 0, ACC:P = -ACC:P
    B       _FastRTS_Example_calcError_ullcomp, GEQ
    NEG64   ACC:P
_FastRTS_Example_calcError_ullcomp:
    MOVL    *+XAR7[0], P            ; save ullerr to memory
    MOVL    *+XAR7[2], ACC
    .if __TI_EABI__
    LCR     __c28xabi_cmpull        ; if (ACC:P < ulltol) AL=-1,
    .else
    FFC     XAR7,#ULL$$CMP          ; if (ACC:P < ulltol) AL=-1,
    .endif 
    CMPB    AL, #0                  ; else AL=0 eq /1 gt
    MOVB    AL, #0, GEQ             ; AL = 0 if N,Z=0, then set Z=0
    MOVB    AL, #1, LT              ; AL = 1 if N=1,Z=0, then set N=0
;;-----------------------------------------------------------------------------
;; Do the double precision comparison
;;-----------------------------------------------------------------------------
_FastRTS_Example_calcError_ldcomp:
    SUBF64  R2, R0, R1              ; *| R2 (lderr) = out - gold
    MOV32   R3L, *+XAR0[0]          ; 1| R3 = ldtol
    MOV32   R3H, *+XAR0[2]          ; 2|
    ABSF64  R2, R2                  ; R2 = |lderr|
    CMPF64  R2, R3                  ; if (|lderr| < ldtol) ZF=0, NF=1
                                    ; ZF, NF in the STF is mapped to Z, N in ST0
    MOV32   *+XAR6[0], R2L          ; save lderr to the memory
    MOV32   *+XAR6[2], R2H
    MOVST0  ZF, NF                  ; export NF, ZF flags from STF to ST0
    B       _FastRTS_Example_calcError_fail, GEQ
    ADDB    AL, #1                  ; AL = 2 pass
    B       _FastRTS_Example_calcError_done, UNC
_FastRTS_Example_calcError_fail:
    MOVB    AL, #1                  ; AL = -1 (1 or 2 fail)
    NEG     AL
_FastRTS_Example_calcError_done:
    SUBB    SP, #LF_SIZE
    LRETR
    .unasg  CMP_ARG_ULLTOL_H
    .unasg  CMP_ARG_ULLTOL_L
    .unasg  PTR_LDERR
    .unasg  PTR_ULLERR
    .unasg  PTR_LDTOL
    .endasmfunc


;; End of File
