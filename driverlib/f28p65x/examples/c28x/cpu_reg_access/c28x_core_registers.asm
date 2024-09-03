;//###########################################################################
;//
;// FILE:   c28x_core_registers.asm
;//
;// TITLE: C-Callable assembly API for core register access
;//
;//###########################################################################
;//
;//
;// 
;// C2000Ware v5.03.00.00
;//Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;//###########################################################################


	.cdecls C,NOLIST
	%{
		#include "c28x_core_registers.h"
	%}

	.global __get_SP
	.global __set_SP
	.global __get_PC
	.global __get_Aux
	.global __get_Status0
	.global __get_Status1

    .text
;;*****************************************************************************
;;
;;	uint16_t __get_SP(void);
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;
;;*****************************************************************************

__get_SP:
	MOV AL, @SP    ;; AL == current SP value
	SUB AL, #2     ;; subtract 2 to adjust for the push of RPC by the function call
	LRETR

;;*****************************************************************************
;;
;; void __set_SP(uint16_t TopOfMainStack);
;;
;; Calling function should disable/enable interrupts if required
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;   * After this function call the RPC register will no longer be valid
;;     since the return LRETR will restored RPC from the "new stack"
;;
;;*****************************************************************************

__set_SP:
    ADDB AL, #2     ;; Adjust by +2 since the LRETR will decrement SP by 2
	PUSH AL			;; on entry AL == TopOfMainStack
	POP  SP			;; update SP
	LRETR

;;*****************************************************************************
;;
;; uint32_t __get_PC(void);
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;
;; * Function call using LCR will:
;;		* push RPC register onto the stack
;;		* move the new return PC value into the RPC register
;;
;; 	For example:
;;      0x8723   LCR __getPC		 <- LCR instruction is 2 16-bit words
;;      0x8725   <next instruction>  <- return PC is pushed into RPC on _getPC call
;;
;; * This function returns the PC at the __getPC function. In this example 0x8723
;;
;;*****************************************************************************

__get_PC:
	PUSH RPC		;; push the return PC value onto the stack
	POP  ACC		;; pop the return PC into ACC
	SUB  ACC, #2	;; subtract 2 to adjust for the push of RPC by the function call
	LRETR

;;*****************************************************************************
;;
;; uint32_t __getAux(uint16_t auxNum);
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;
;;*****************************************************************************

__get_Aux:
	MOV PL, #0x5A5A	  ;; Change this to be the default value returned if
    MOV PH, #0x5A5A   ;; auxNum is not valid

	CMPB AL, #8
    BF  GET_AUX_DONE, GEQ ;; auxNum >= 8?

	MOVL P, XAR0
	CMPB AL, #0		  ;; auxNum == 0?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR1
	CMPB AL, #1		  ;; auxNum == 1?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR2
	CMPB AL, #2		  ;; auxNum == 2?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR3
	CMPB AL, #3		  ;; auxNum == 3?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR4
	CMPB AL, #4		  ;; auxNum == 4?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR5
	CMPB AL, #5		  ;; auxNum == 5?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR6
	CMPB AL, #6		  ;; auxNum == 6?
	SBF  GET_AUX_DONE, EQ

	MOVL P, XAR7	  ;; auxNum == 7

GET_AUX_DONE:
	MOVL ACC, P
	LRETR


;;*****************************************************************************
;;
;; uint16_t __get_Status0 (void);
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;   * The POP into AL can change flag bits in ST0 (for example setting/clearing N)
;;   * This was seperated from __get_Status0 since compare instructions impact
;;     flags in ST0
;;
;;*****************************************************************************
__get_Status0:
    PUSH ST0	;; push the ST0 value onto the stack
    POP  AL		;; pop the value into AL to return to the calling function
	LRETR

;;*****************************************************************************
;;
;; uint16_t __get_Status1 (void);
;;
;; Notes:
;; 	 * Calling function should disable/enable interrupts if required
;;   * The POP into AL can change flag bits in STO (for example setting/clearing N)
;;   * This was seperated from __get_Status1 since compare instructions impact
;;     flags in ST0
;;
;;*****************************************************************************
__get_Status1:
    PUSH ST1	;; push the ST1 value onto the stack
    POP  AL		;; pop the value into AL to return to the calling function
	LRETR

;//
;// End of file.
;//
