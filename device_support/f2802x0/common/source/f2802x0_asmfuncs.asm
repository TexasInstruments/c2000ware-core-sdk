;//###########################################################################
;//
;// FILE:  F2802x0_asmfuncs.asm
;//
;// TITLE: Assembly Functions
;//###########################################################################
;// $TI Release:  $
;// $Release Date:  $
;// $Copyright:
;// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

;// DSP28x_usDelay
;// DESCRIPTION:
;//  
;// This is a simple delay function that can be used to insert a specified
;// delay into code.  
;// 
;// This function is only accurate if executed from internal zero-waitstate
;// SARAM. If it is executed from waitstate memory then the delay will be
;// longer then specified. 
;// 
;// To use this function:
;//
;//  1 - update the CPU clock speed in the f2802x0_examples.h
;//    file. For example:
;//    #define CPU_RATE 16.667L // for a 60MHz CPU clock speed
;//
;//  2 - Call this function by using the DELAY_US(A) macro
;//    that is defined in the f2802x0_examples.h file.  This macro
;//    will convert the number of microseconds specified
;//    into a loop count for use with this function.  
;//    This count will be based on the CPU frequency you specify.
;//
;//  3 - For the most accurate delay 
;//    - Execute this function in 0 waitstate RAM.  
;//    - Disable interrupts before calling the function
;//      If you do not disable interrupts, then think of
;//      this as an "at least" delay function as the actual
;//      delay may be longer. 
;//
;//  The C assembly call from the DELAY_US(time) macro will
;//  look as follows: 
;//
;//  extern void Delay(long LoopCount);                
;//
;//        MOV   AL,#LowLoopCount
;//        MOV   AH,#HighLoopCount
;//        LCR   _Delay
;//
;//  Or as follows (if count is less then 16-bits):
;//
;//        MOV   ACC,#LoopCount
;//        LCR   _Delay
;//
;//

       .def _DSP28x_usDelay
       .sect "ramfuncs"

        .global  __DSP28x_usDelay
_DSP28x_usDelay:
        SUB    ACC,#1
        BF     _DSP28x_usDelay,GEQ    ;; Loop if ACC >= 0
        LRETR 

;There is a 9/10 cycle overhead and each loop
;takes five cycles. The LoopCount is given by
;the following formula:
;  DELAY_CPU_CYCLES = 9 + 5*LoopCount
; LoopCount = (DELAY_CPU_CYCLES - 9) / 5
; The macro DELAY_US(A) performs this calculation for you


;//  Function to set the DBGIER register (for realtime emulation).
;//  Function Prototype: void SetDBGIER(Uint16)
;//  Usage: SetDBGIER(value);
;//  Input Parameters: Uint16 value = value to put in DBGIER register. 
;//  Return Value: none      
        .global _setDBGIER
        .text
        
_setDBGIER:
        MOV     *SP++,AL
        POP     DBGIER
        LRETR

;//      Uint16 DSP28x_DisableInt();
;// and  void DSP28x_RestoreInt(Uint16 Stat0);
;//
;// Usage:
;//
;//      DSP28x_DisableInt() sets both the INTM and DBGM
;//      bits to disable maskable interrupts.  Before doing
;//      this, the current value of ST1 is stored on the stack
;//      so that the values can be restored later.  The value
;//      of ST1 before the masks are set is returned to the
;//      user in AL.  This is then used to restore their state
;//      via the DSP28x_RestoreInt(Uint16 ST1) function.
;//
;// Example
;//
;//   Uint16 StatusReg1    
;//   StatusReg1 = DSP28x_DisableInt();
;//
;//   ... May also want to disable INTM here
;// 
;//   ... code here
;//
;//   DSP28x_RestoreInt(StatusReg1);
;//
;//   ... Restore INTM enable
;//

   .def _DSP28x_DisableInt
   .def _DSP28x_RestoreInt

_DSP28x_DisableInt:
    PUSH  ST1
    SETC  INTM,DBGM
    MOV   AL, *--SP
    LRETR

_DSP28x_RestoreInt:
    MOV   *SP++, AL
    POP   ST1
    LRETR

;
;//
;// End of file
;//

