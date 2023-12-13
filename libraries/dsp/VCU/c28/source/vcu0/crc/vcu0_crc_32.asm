;;*****************************************************************************
;;! \file source/vcu0/vcu0_crc_32.asm
;;!
;;! \brief  32-bit CRC that uses the polynomial 0x04c11db7
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
;;
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines

;/*! ASM- function to get the 32-bit CRC
; *
; * \param ACC = The initial value of crc, in case the message has been
; *  chopped into several parts, you can use the crc32 of the previous
; *  segment as the init value for the current segment crc32 calculation
; *  until the final crc is derived.
; * \param *+XAR4 = Address of the message buffer
; * \param AR5 = Parity of the first message byte, i.e. whether its on an even
; *  or odd address
; * \param *-SP[1]/AR0 = Length of the message in bytes
; *  
; * Calculate the 32-bit CRC of a message buffer by using the VCU instructions
; * VCRC32H_1 and VCRC32L_1
; *
; * \return CRC result in ACC
; */   
      .if __TI_EABI__
	  .asg getCRC32_vcu,_getCRC32_vcu
	  .endif
	  .def _getCRC32_vcu

_getCRC32_vcu:
	  PUSH		  XAR0
	  PUSH		  XAR1
      MOVZ        AR0, *-SP[7]       ; load rxLen
	  ADDB        SP, #4              ; allocate 4 words for local
      VMOV32      *-SP[2], VCRC       ; Store current CRC
      VCRCCLR    
      MOVL        *-SP[4], ACC
      VMOV32      VCRC,*-SP[4]        ; VCRC = Inital value
      MOV         AL, AR5              ; check the parity       
      SBF         _CRC32_loop_prep, EQ
      VCRC32H_1   *XAR4++             ; if parity=1, calculate high byte first
      DEC         AR0            
      SBF         _CRC32done, EQ
      
_CRC32_loop_prep:      
      MOV         AL, AR0
      MOV         AH, AR0
      AND         AL, #0xFFF8         ; check to see if the length is greater than 8 bytes
      BF          _CRC32_LSB,EQ
      LSR         AL, #3              ; loop in 8 bytes
      MOV         AR1, AL
      SUB         AR1, #1
      
      .align     (2)                  ; align at 32-bit boundary to remove penalty
      RPTB        _CRC32_post, AR1  ; loop for the middle part of the packet
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
_CRC32_post: 
      LSL         AL, #3              ; calculating remaining number of bytes
      SUB         AH, AL
      SBF         _CRC32done, EQ      ; if multiple of 8, done
      MOV         AR0, AH
_CRC32_LSB
      VCRC32L_1   *XAR4               ; if parity=0, calculate the low byte
      DEC         AR0       
      SBF         _CRC32done, EQ
      VCRC32H_1   *XAR4++
      DEC         AR0       
      SBF         _CRC32_LSB, NEQ
_CRC32done
      VMOV32       *-SP[4], VCRC        ; Store CRC
      MOVL        ACC, *-SP[4]          ; return ACC 
      VMOV32       VCRC, *-SP[2]        ; Restore VCRC
      SUBB         SP, #4               ; restore stack pointer
      POP		   XAR1
      POP		   XAR0
      LRETR
      
;; End of file
