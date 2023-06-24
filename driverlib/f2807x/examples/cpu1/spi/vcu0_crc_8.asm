;;*****************************************************************************
;;! \file source/vcu0/vcu0_crc_8.asm
;;!
;;! \brief  8-bit CRC that uses the polynomial 0x07
;;
;;  \date   Apr 7, 2011
;;!
;;
;;  Group:            C2000
;;  Target Family:    F2837x
;;
;;#############################################################################
;;
;; $Release Date:  $
;; $Copyright:
;// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
;;#############################################################################
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines

;
;/*! ASM- function to get the 8-bit CRC
; *
; * \param ACC = The initial value of crc, in case the message has been
; *  chopped into several parts, you can use the crc8 of the previous
; *  segment as the init value for the current segment crc8 calculation
; *  until the final crc is derived.
; * \param *+XAR4 = Address of the message buffer
; * \param AR5 = Parity of the first message byte, i.e. whether its on an even
; *  or odd address
; * \param *-SP[1]/AR0 = Length of the message in bytes
; *
; * Calculate the 8-bit CRC of a message buffer by using the VCU instructions,
; * VCRC8L_1 and VCRC8H_1
; *
; * \return CRC result in AL
; */

      .if __TI_EABI__
      .asg getCRC8_vcu, _getCRC8_vcu
      .endif

      .def _getCRC8_vcu

_getCRC8_vcu:
      PUSH        XAR0
      PUSH        XAR1
      MOVZ        AR0, *-SP[7]       ; load rxLen
      ADDB        SP, #4              ; allocate 4 words for local
      VMOV32      *-SP[2], VCRC       ; Store current CRC
      VCRCCLR
      MOV         *-SP[4], ACC
      VMOV32      VCRC,*-SP[4]        ; VCRC = Inital value
      MOV         AL, AR5             ; check the parity
      SBF         _CRC8_loop_prep, EQ
      VCRC8H_1    *XAR4++             ; if parity=1, calculate high byte first
      DEC         AR0
      SBF         _CRC8done, EQ

_CRC8_loop_prep:
      MOV         AL, AR0
      MOV         AH, AR0
      AND         AL, #0xFFF8         ; check to see if the length is greater than 8 bytes
      BF          _CRC8_LSB,EQ
      LSR         AL, #3              ; loop in 8 bytes
      MOV         AR1, AL
      SUB         AR1, #1

      .align     (2)                  ; align at 32-bit boundary to remove penalty
      RPTB        _CRC8_post, AR1  ; loop for the middle part of the packet
      VCRC8L_1   *XAR4
      VCRC8H_1   *XAR4++
      VCRC8L_1   *XAR4
      VCRC8H_1   *XAR4++
      VCRC8L_1   *XAR4
      VCRC8H_1   *XAR4++
      VCRC8L_1   *XAR4
      VCRC8H_1   *XAR4++
_CRC8_post

      LSL         AL, #3              ; calculating remaining number of bytes
      SUB         AH, AL
      SBF         _CRC8done, EQ       ; if multiple of 8, done
      MOV         AR0, AH
_CRC8_LSB
      VCRC8L_1    *XAR4               ; if parity=0, calculate the low byte
      DEC         AR0
      SBF         _CRC8done, EQ
      VCRC8H_1    *XAR4++
      DEC         AR0
      SBF         _CRC8_LSB, NEQ
_CRC8done
      VMOV32       *-SP[4], VCRC        ; Store CRC
      MOV          AL, *-SP[4]          ; return AL
      VMOV32       VCRC, *-SP[2]        ; Restore VCRC
      SUBB         SP, #4               ; restore stack pointer
      POP          XAR1
      POP          XAR0
      LRETR

;; End of file
