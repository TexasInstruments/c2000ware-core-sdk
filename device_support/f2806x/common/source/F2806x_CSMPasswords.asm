;// TI File $Revision: /main/2 $ 
;// Checkin $Date: January 4, 2011   10:10:10 $ 
;//###########################################################################
;//
;// FILE:	F2806x_CSMPasswords.asm
;//
;// TITLE:	F2806x Code Security Module Passwords.
;// 
;// DESCRIPTION:
;//
;//         This file is used to specify password values to
;//         program into the CSM password locations in Flash
;//         at 0x3F7FF8 - 0x3F7FFF.
;//
;//         In addition, the reserved locations 0x3F7F80 - 0x3F7FF5 are 
;//         all programmed to 0x0000
;//
;//###########################################################################
;// $TI Release: $
;// $Release Date: $ 
;// $Copyright:
;// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

; The "csmpasswords" section contains the actual CSM passwords that will be
; linked and programmed into to the CSM password locations (PWL) in flash.  
; These passwords must be known in order to unlock the CSM module. 
; All 0xFFFF's (erased) is the default value for the password locations (PWL).

; It is recommended that all passwords be left as 0xFFFF during code
; development.  Passwords of 0xFFFF do not activate code security and dummy 
; reads of the CSM PWL registers is all that is required to unlock the CSM.  
; When code development is complete, modify the passwords to activate the
; code security module.

      .sect "csmpasswds"

      .int	0xFFFF		;PWL0 (LSW of 128-bit password)
      .int	0xFFFF		;PWL1
      .int	0xFFFF		;PWL2
      .int	0xFFFF		;PWL3
      .int	0xFFFF		;PWL4
      .int	0xFFFF		;PWL5
      .int	0xFFFF		;PWL6
      .int	0xFFFF		;PWL7 (MSW of 128-bit password)
	
;----------------------------------------------------------------------

; For code security operation, all addresses between 0x3F7F80 and
; 0x3F7FF5 cannot be used as program code or data.  These locations
; must be programmed to 0x0000 when the code security password locations
; (PWL) are programmed.  If security is not a concern, then these addresses
; can be used for code or data.  

; The section "csm_rsvd" can be used to program these locations to 0x0000.

        .sect "csm_rsvd"
        .loop (3F7FF5h - 3F7F80h + 1)
              .int 0x0000
        .endloop

;//
;// End of file
;//

      
