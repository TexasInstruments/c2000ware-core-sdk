;* ======================================================================== *
;* c2000asm.inc  v6.0.1                                                     *
;*                                                                          *
;* Copyright (c) 2004-2015 Texas Instruments Incorporated                   *
;* http://www.ti.com/                                                       *
;*                                                                          *
;*  Redistribution and  use in source  and binary forms, with  or without   *
;*  modification,  are permitted provided  that the  following conditions   *
;*  are met:                                                                *
;*                                                                          *
;*     Redistributions  of source  code must  retain the  above copyright   *
;*     notice, this list of conditions and the following disclaimer.        *
;*                                                                          *
;*     Redistributions in binary form  must reproduce the above copyright   *
;*     notice, this  list of conditions  and the following  disclaimer in   *
;*     the  documentation  and/or   other  materials  provided  with  the   *
;*     distribution.                                                        *
;*                                                                          *
;*     Neither the  name of Texas Instruments Incorporated  nor the names   *
;*     of its  contributors may  be used to  endorse or  promote products   *
;*     derived  from   this  software  without   specific  prior  written   *
;*     permission.                                                          *
;*                                                                          *
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   *
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   *
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   *
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   *
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   *
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
;*                                                                          *
;* ======================================================================== *
* ========================================================================= *
*                                                                           *
*   TEXAS INSTRUMENTS, INC.                                                 *
*                                                                           *
*   NAME                                                                    *
*       c2000asm.inc -- pseudo-op compatibility bridge for pre-5.00 tools   *
*                                                                           *
*   USAGE                                                                   *
*       Just .include at top of your source file.  Alternately, use         *
*       the compiler flag -ahi or -ahc to force inclusion in the            *
*       source-file.                                                        *
*                                                                           *
*   DESCRIPTION                                                             *
*       This file provides a set of pseudo-operations that are intended     *
*       to replace existing mnemonics in certain usage scenarios.  The      *
*       point of the new pseudo-ops is to allow the tools to provide more   *
*       precise information to the profiler as to the *purpose* of a        *
*       branch, so that it can provide more accurate profile data.          *
*                                                                           *
*       Mnemonic    Purpose                                                 *
*       FFCRET      Return from a Fast-Function Call.                       *
*                   Equivalent to "LB", but only accepts *XAR7 as an        *
*                   operand.                                                *
*                                                                           *
*   NOTES                                                                   *
*       This file is actually just a compatibility shim, intended to        *
*       provide forward compatibility between tool versions < 5.00          *
*       and tool versions >= 5.00.  The purpose of this file it purely      *
*       compatibility.  Tool versions >= 5.00 are required to gain the      *
*       greater-precision information for the profiler.                     *
* ========================================================================= *

* ========================================================================= *
* Create "asmver" with current version of assembler. Value is 0 if assembler
* version predates the predefined symbol.
* ========================================================================= *
           .if $isdefed("__TI_ASSEMBLER_VERSION__")
           .asg    __TI_ASSEMBLER_VERSION__, asmver
           .else
           .asg    0, asmver
           .endif

* ========================================================================= *
* If the assembler version predates the support call mnemonics
* ========================================================================= *
           .if asmver < 500
           .asg    LB,    FFCRET     ; Return from Fast-Function Call
           .asg ";", .asmfunc
           .asg ";", .endasmfunc
           .endif


