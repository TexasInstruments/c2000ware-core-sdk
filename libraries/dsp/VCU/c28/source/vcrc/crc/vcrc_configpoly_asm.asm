;;###############################################################################
;;! \file /crc/vcrc_configpoly_asm.asm
;;!
;;! \brief  Generic polynomial CRC calculation for byte wise and bitwise data
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines

;; Argument structure defines
SEEDVAL_OFFSET      .set     0
NBYTES_OFFSET       .set     2
PARITY_OFFSET       .set     3
CRCRESULT_OFFSET    .set     4
MSGBUFFER_OFFSET    .set     6
NBITS_OFFSET		.set	10
POLYNOMIAL_OFFSET   .set    12
PSIZE_OFFSET        .set    14
DSIZE_OFFSET        .set    15
REFLECTED_OFFSET    .set    16
LOCAL_FRAME_SIZE    .set    4
VRX_BASE            .set    0
VCRC_OFFSET         .set    2
ARG_OFFSET          .set    4

;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'CRC_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 6
;; USAGE   : Called on entry into CRC routine
;;
CRC_CONTEXT_SAVE    .macro
    PUSH      XAR0
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE            ; allocate stack space for local frame
    VMOV32    *-SP[VRX_BASE+VCRC_OFFSET], VCRC ; save VCRC to stack
    .endm
;;
;; MACRO   : 'CRC_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 6
;; USAGE   : Called on exit from CRC routine
;;
CRC_CONTEXT_RESTORE    .macro
    VMOV32    VCRC, *-SP[VRX_BASE+VCRC_OFFSET]
    SUBB      SP, #LOCAL_FRAME_SIZE          ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    POP       XAR0
    .endm

	.if __TI_EABI__
	.asg CRC_init16Bit, _CRC_init16Bit
	.asg CRC_init32Bit, _CRC_init32Bit
	.asg CRC_runConfigPolyBits, _CRC_runConfigPolyBits
	.asg CRC_runConfigPolyBytes, _CRC_runConfigPolyBytes
	.asg CRC_runConfigPolyBitsReflected, _CRC_runConfigPolyBitsReflected
	.asg CRC_runConfigPolyBytesReflected, _CRC_runConfigPolyBytesReflected
	.endif

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _CRC_init16Bit
    .global _CRC_init32Bit
    .global _CRC_runConfigPolyBits
    .global _CRC_runConfigPolyBytes
    .global _CRC_runConfigPolyBitsReflected
    .global _CRC_runConfigPolyBytesReflected
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;*****************************************************************************
;;
;; \brief Calculate the n-bit CRC using Generic CRC polynomial using functions
;;        _CRC_runConfigPolyBytes and _CRC_runConfigPolyBits
;; \param Handle to the structure, CRC_Obj(passed in XAR4)
;; - *+XAR4[0]:  uint32_t seedValue -> Initial value of the CRC calculation
;; - *+XAR4[2]:  uint32_t nMsgBytes -> the number of bytes in the message buffer
;; - *+XAR4[3]:  Parity_e parity -> the location, in a word, of the first byte of the CRC calculation
;; - *+XAR4[4]:  uint32_t crcResult -> the calculated CRC
;; - *+XAR4[6]: void *pMsgBuffer -> Pointer to the message buffer
;; - *+XAR4[8]: void *pCrcTable -> Pointer to the CRC lookup table
;; - *+XAR4[10]:  uint32_t nMsgBits -> provde the data size in bits if the CRC is to be computed bitwise
;; - *+XAR4[12]: uint32_t polynomial -> added to ensure customized polynomial can be added by the user
;; - *+XAR4[14]; uint32_t polySize -> provide the polynomial size for the customized polynomial 
;; PolySize - Polynomial size - size of of 1 bit - indicated by programming a value of 0x0
;;            Polynomial size - size of of 32bits - indicated by programming a value of 0x1F
;; - *+XAR4[15]; uint32_t dataSize -> data size for CRC computation
;; dataSize - Data size - size of 1 bit - indicated by prograaming a value of 0x0
;;            Data size - size of 8 bits is indicated by programming a value of 0x7 
;; These are to be set in the VCRCSIZE register - PSIZE and DSIZE fields
;; - *+XAR4[16]; uint32_t reflected -> choose CRC computation in either reflected or non-reflected mode
;; \brief : Assembly function for generic CRC calculation in bytewise mode

_CRC_runConfigPolyBytes:
    CRC_CONTEXT_SAVE
    MOVL       		 XAR2, XAR4

;; Register Usage:
;;   XAR0:         Number of bytes to process
;;   XAR1:         Loading polynomial, polynomial size, data size and repeat block counter
;;   XAR2:         Pointer to iterate through the CRC object
;;   XAR4:         Points to the CRC object
;;   XAR5:         Points to the message buffer
;;
   	MOV				 AR1, #POLYNOMIAL_OFFSET			; Load Polynomial
   	VMOV32  		 VCRCPOLY, *+XAR4[AR1]

   	MOV				 AR1, #PSIZE_OFFSET				  	; Initialize polynomial size
   	VMOV16  		 VCRCPSIZE, *+XAR4[AR1]

   	MOV				 AR1, #DSIZE_OFFSET				   	; Initialize data size
   	VMOV16  		 VCRCDSIZE, *+XAR4[AR1]
														;   Need 2+ cyc before using VCRC
    VCRCCLR                                      		; Clear out the CRC result register

    MOVL         	 XAR0, *+XAR4[NBYTES_OFFSET]     	; Load number of message bytes into AR0
    VMOV32       	 VCRC, *+XAR4[SEEDVAL_OFFSET]   	; Load seed value into the CRC result register

	MOV				 AR1, #MSGBUFFER_OFFSET
    MOVL         	 XAR5, *+XAR4[AR1] 					; XAR5 points to the message buffer

    MOV           	 AL,  *+XAR4[PARITY_OFFSET]     	; Check the parity

    SBF          	_CRC_runConfigPolyBytes_Loop, EQ    ; If Parity = LOW_BYTE, skip to loop
    VCRCH			*XAR5++                             ; Parity = HIGH_BYTE, calculate high byte of the first word,
                                                    	; ignore the low byte and proceed to next word
    DEC          	 AR0
    SBF          	_CRC_runConfigPolyBytes_End, EQ    ; Jump to end if no more bytes

_CRC_runConfigPolyBytes_Loop:
    MOV          	AL, AR0
    MOV          	AH, AR0
    AND          	AL, #0xFFF8                   		; Check to see if length greater than 8 bytes
                           	                      		; if true, handle the <8 bytes in a loop
                                                 		; AL is now a multiple of 8
    SBF         	_CRC_runConfigPolyBytes_LT8BytesLeft, EQ
    LSR          	AL, #3                          	; loop in 8 bytes at a time
    MOV          	AR1, AL                         	; move count into AR1
    SUB          	AR1, #1                         	; subtract 1, accounts for the RPTB instruction i.e. it loops
                                                 		; N + 1 times

    .align       	2                               	; align at 32-bit boundary to remove penalty
                                                 		; loop through the message 8 bytes at a time
    RPTB         	_CRC_runConfigPolyBytes_RepeatBlock, AR1
    VCRCL			*XAR5
    NOP
    NOP
    VCRCH			*XAR5++
    NOP
    NOP
    VCRCL			*XAR5
    NOP
    NOP
    VCRCH			*XAR5++
    NOP
    NOP
    VCRCL			*XAR5
    NOP
    NOP
    VCRCH			*XAR5++
    NOP
    NOP
    VCRCL			*XAR5
    NOP
    NOP
    VCRCH			*XAR5++
    NOP
    NOP

_CRC_runConfigPolyBytes_RepeatBlock:
    LSL         	 AL, #3                         	; multiply by 8 to get the pre RPTB count
    SUB         	 AH, AL                          	; AH holds the number of remaining bytes(<8)
    SBF         	_CRC_runConfigPolyBytes_End, EQ     ; if multiple of 8, AH is 0, done processing
    MOV         	 AR0, AH

_CRC_runConfigPolyBytes_LT8BytesLeft:
    VCRCL			*XAR5
    DEC         	 AR0
    SBF        		_CRC_runConfigPolyBytes_End, EQ
    VCRCH			*XAR5++
    DEC         	 AR0
    SBF         	_CRC_runConfigPolyBytes_LT8BytesLeft, NEQ

_CRC_runConfigPolyBytes_End:
	MOV				 AR1, #REFLECTED_OFFSET
	CMP				*+XAR4[AR1], #0x0
	SBF     		_CRC_runConfigPolyBytes_End_NotReflected, EQ

	;MOV				 AR1, #CRCRESULT_OFFSET
    VMOV32      	*+XAR4[CRCRESULT_OFFSET], VCRC  					; Save the result to the structure

    CRC_CONTEXT_RESTORE
    LRETR

_CRC_runConfigPolyBytes_End_NotReflected:

	MOV				 AR1, #PSIZE_OFFSET				  	; Initialize polynomial size
	CMP				*+XAR4[AR1], #0x1F
	SBF				_CRC_runConfigPolyBytes_End_NotReflected_32Bits, EQ

    ;MOV				 AR1, #CRCRESULT_OFFSET
	VMOV32      	*+XAR4[CRCRESULT_OFFSET], VCRC  					; Save the result to the structure
    MOVL		     ACC, *+XAR4[CRCRESULT_OFFSET]
    FLIP			 AL
    MOVL			*+XAR4[CRCRESULT_OFFSET], ACC

    CRC_CONTEXT_RESTORE
    LRETR


_CRC_runConfigPolyBytes_End_NotReflected_32Bits:
    ;MOV				 AR1, #CRCRESULT_OFFSET
    VMOV32           *+XAR4[CRCRESULT_OFFSET], VCRC

    ; Swap words during save
    MOV				AH, *+XAR4[CRCRESULT_OFFSET]
    ;MOV				AR1, #CRCRESULT_OFFSET+1
    MOV				AL, *+XAR4[CRCRESULT_OFFSET+1]
    ; Reverse both halves
    FLIP			AH									; Flip the result in case of not reflected mode for 32 bits
    FLIP			AL

    MOVL			*+XAR4[CRCRESULT_OFFSET], ACC

    CRC_CONTEXT_RESTORE
    LRETR

;;*****************************************************************************
;; \brief: Assembly for CRC calculation in bitwise mode

_CRC_runConfigPolyBits:
    CRC_CONTEXT_SAVE

;; Register Usage:
;;   XAR0:         Number of bytes to process
;;   XAR1:         Loading polynomial, polynomial size, data size and pointer index to DataSize
;;   XAR4:         Points to the CRC object
;;   XAR5:         Points to the message buffer
;;
    VCRCCLR

   	MOV		       AR1, #POLYNOMIAL_OFFSET					; Load Polynomial
   	VMOV32         VCRCPOLY, *+XAR4[AR1]

   	MOV		       AR1, #PSIZE_OFFSET				    	; Initialize polynomial size
   	VMOV16         VCRCPSIZE, *+XAR4[AR1]

    VMOV32         VCRC, *+XAR4[SEEDVAL_OFFSET]    		    ; Load seed value into the CRC result register

   	MOV		       AR1, #MSGBUFFER_OFFSET
    MOVL           XAR5, *+XAR4[AR1] 						; XAR5 points to the message buffer

   	MOV		       AR1, #DSIZE_OFFSET				    	; Initialize data size size
   	VMOV16         VCRCDSIZE, *+XAR4[AR1]

	;;; Load # of bits, store modulus 8 (remaining bits after all full bytes processed)
	;;;  minus one back to CRC.dataSize
	MOV		       AR1, #NBITS_OFFSET						; Initialize the data size
	AND		       AL, *+XAR4[AR1], #7						; AND with #7 to get the remaining number of bits after absolute byte conversion
	SUBB	       ACC, #1									; subtract 1 and load to the accumulator
	MOV		       AR1, #DSIZE_OFFSET    					; keep the remaining bits in DSIZE_OFFSET. e.g if NBITS_OFFSET = 13 then at this point DSIZE_OFFSET will hold value 5 which is the remaining bits after absolute byte count
	MOV		      *+XAR4[AR1], AL							; load the remaining bits to CRC.dataSize

    ;;; Load # of bits, right shift to bytes, and store in # of bytes XAR0 (if needed)

    MOV  		  AR1, #NBITS_OFFSET				   		 ; Initialize data size
	MOV			  AL, *+XAR4[AR1]						     ; Load # of bits
    LSR			  AL, #3									 ; Divide by 8
    MOV  		  AR1, #DSIZE_OFFSET						 ; ensure that AR1 still points to the remaining number of bits for CRC computation after absolute byte count

    BF			 _LESS_THAN_A_BYTE_LOW, EQ					 ; If no full bytes, skip ahead
    SUBB		  ACC, #1
	MOV			  AR0, AL									 ; XAR0 = # of whole bytes - 1

	MOV			  AL, *+XAR4[PARITY_OFFSET]								 ; branch to lower byte or higher byte depending on parity inputs
	BF			 _PROCESS_HIGH_BYTE, NEQ


_PROCESS_LOW_BYTE:
	VCRCL	     *XAR5										; Takes 3 cycles
	BANZ	     _PROCESS_HIGH_BYTE, AR0--

_LESS_THAN_A_BYTE_HIGH:
	CMP		     *+XAR4[AR1], #0xFFFF
	BF		     _CRC_runConfigPolyBits_End, EQ
	VMOV16	      VCRCDSIZE, *+XAR4[AR1]					; Load data size for last (< byte) CRC
	VCRCH	     *XAR5++
	BF		     _CRC_runConfigPolyBits_End, UNC

_PROCESS_HIGH_BYTE:
	VCRCH	     *XAR5++									; process the CRC for highger byte of a 16 bit word
	BANZ	     _PROCESS_LOW_BYTE, AR0--

_LESS_THAN_A_BYTE_LOW:
	CMP		     *+XAR4[AR1], #0xFFFF
	BF		     _CRC_runConfigPolyBits_End, EQ
	VMOV16	      VCRCDSIZE, *+XAR4[AR1]					; Load data size for last (< byte) CRC
	VCRCL	     *XAR5
	BF		     _CRC_runConfigPolyBits_End, UNC

_CRC_runConfigPolyBits_End:
	MOV		     AR1, #REFLECTED_OFFSET
	CMP		     *+XAR4[AR1], #0x0

	SBF          _CRC_runConfigPolyBits_End_NotReflected, EQ
	;MOV		      AR1, #CRCRESULT_OFFSET
    VMOV32       *+XAR4[CRCRESULT_OFFSET], VCRC 	 						; Save the result to the structure

    CRC_CONTEXT_RESTORE
    LRETR

_CRC_runConfigPolyBits_End_NotReflected:
	MOV				 AR1, #PSIZE_OFFSET				  		; Initialize polynomial size
	CMP				*+XAR4[AR1], #0x1F
	SBF				_CRC_runConfigPolyBits_End_NotReflected_32Bits, EQ

    ;MOV				 AR1, #CRCRESULT_OFFSET
	VMOV32      	*+XAR4[CRCRESULT_OFFSET], VCRC  						; Save the result to the structure
    MOVL		     ACC, *+XAR4[CRCRESULT_OFFSET]
    FLIP			 AL
    MOVL			*+XAR4[CRCRESULT_OFFSET], ACC

    CRC_CONTEXT_RESTORE
    LRETR


_CRC_runConfigPolyBits_End_NotReflected_32Bits:
    ;MOV				 AR1, #CRCRESULT_OFFSET
    VMOV32           *+XAR4[CRCRESULT_OFFSET], VCRC

    ; Swap words during save
    MOV				AH, *+XAR4[CRCRESULT_OFFSET]
    ;MOV				AR1, #CRCRESULT_OFFSET+1
    MOV				AL, *+XAR4[CRCRESULT_OFFSET+1]
    ; Reverse both halves
    FLIP			AH										; Flip the result in case of not reflected mode for 32 bits
    FLIP			AL
    MOVL			*+XAR4[CRCRESULT_OFFSET], ACC

    CRC_CONTEXT_RESTORE
    LRETR

;;*****************************************************************************

_CRC_runConfigPolyBytesReflected:
    VSETCRCMSGFLIP
    LCR       _CRC_runConfigPolyBytes
    VCLRCRCMSGFLIP
    LRETR

;;*****************************************************************************

_CRC_runConfigPolyBitsReflected:
    VSETCRCMSGFLIP
    LCR       _CRC_runConfigPolyBits
    VCLRCRCMSGFLIP
    LRETR

;;*****************************************************************************
;; End of file
