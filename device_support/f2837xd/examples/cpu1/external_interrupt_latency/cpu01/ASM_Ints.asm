;******************************************************************************
; FILE: ASM_Ints.asm
; 
; DESCRIPTION: External Interrupts in assembly
; 
;;#############################################################################
;;
;;
;;$Copyright:
;// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
; XINT interrupts in assembly. These are tweaked for the shortest possible 
; response time. Both of them toggle GPIO19. These only save a couple cycles vs.
; their C equivalents.

	.global _XINT_ASM_ISR_RAM
	.global _XINT_ASM_ISR_FLASH

	;This copy of the function runs out of RAM with zero wait states. The delay
    ;from GPIO16 going low to GPIO19 going high was measured as 
    ;125 nanoseconds, which is 25 cycles at 200 MHz.
	.sect ".TI.ramfunc"
_XINT_ASM_ISR_RAM:
	ASP                   ;Align stack pointer. Real ISRs will probably need this.
	MOVZ DP, #7f00h >> 6  ;Load DP with the GPIO data registers' base address (0x7f00)
	MOV @7h, #0008h       ;Set bit 19 of GPATOGGLE (address 0x7f06)
	MOVZ DP, #0cc0h >> 6  ;Load DP with a value close to the PIEACK address (0xcc0).
	                      ;We can't use the PIE base address of 0xce0 because the
	                      ;0x20 bit gets dropped during the right-shift.
	MOV @21h, #0001h      ;Write to PIEACK to re-enable the interrupt group
	NASP                  ;Unalign stack pointer. Again, this is only here for realism.
	MOVZ DP, #7f00h >> 6  ;Load DP with the GPIO data registers' base address (0x7f00)
	MOV @7h, #0008h       ;Set bit 19 of GPATOGGLE (address 0x7f06)
	IRET                  ;Return from the interrupt

	;This copy of the function runs out of flash with three wait states. It's 
    ;aligned to an 8-word (128-bit) boundary so that the first several 
    ;instructions will be in a single flash word. The delay from GPIO16 going 
    ;low to GPIO19 going high was measured as 135 nanoseconds, which is 
    ;27 cycles at 200 MHz.
	.sect ".text"
	.align 8
_XINT_ASM_ISR_FLASH:
	ASP                   ;Align stack pointer. Real ISRs will probably need this.
	MOVZ DP, #7f00h >> 6  ;Load DP with the GPIO data registers' base address
	MOV @7h, #0008h       ;Set bit 19 of GPATOGGLE (address 0x7f06)
	MOVZ DP, #0cc0h >> 6  ;Load DP with a value close to the PIEACK address (0xcc0).
	                      ;We can't use the PIE base address of 0xce0 because the
	                      ;0x20 bit gets dropped during the right-shift.
	MOV @21h, #0001h      ;Write to PIEACK to re-enable the interrupt group
	NASP                  ;Unalign stack pointer. Again, this is only here for realism.
	MOVZ DP, #7f00h >> 6  ;Load DP with the GPIO data registers' base address (0x7f00)
	MOV @7h, #0008h       ;Set bit 19 of GPATOGGLE (address 0x7f06)
	IRET                  ;Return from the interrupt

;//===========================================================================
;// End of file.
;//===========================================================================
