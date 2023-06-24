;//###########################################################################
;//
;// FILE:   flash_kernel_ex3_codestartbranch.asm
;//
;// TITLE: Branch for redirecting code execution after boot.
;//
;// For these examples, code_start is the first code that is executed after
;// exiting the boot ROM code.
;//
;// The codestart section in the linker cmd file is used to physically place
;// this code at the correct memory location. This section should be placed
;// at the location the BOOT ROM will re-direct the code to. For example,
;// for boot to FLASH this code will be located at 0x80000.
;//
;// In addition, the example f280013x projects are setup such that the codegen
;// entry point is also set to the codestart label. This is done by linker
;// option -e in the project build options. When the debugger loads the code,
;// it will automatically set the PC to the "entry point" address indicated by
;// the -e linker option. In this case the debugger is simply assigning the PC,
;// it is not the same as a full reset of the device.
;//
;// The compiler may warn that the entry point for the project is other then
;//  _c_init00. _c_init00 is the C environment setup and is run before
;// main() is entered. The codestart code will re-direct the execution
;// to _c_init00 and thus there is no worry and this warning can be ignored.
;//
;//###########################################################################
;//
;//
;// $Copyright:
;// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
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

***********************************************************************

WD_DISABLE  .set  1    ;set to 1 to disable WD, else set to 0

    .ref _c_int00
    .ref main
    .global code_start
    .global ExitBoot

***********************************************************************
* Function: codestart section
*
* Description: Branch to code starting point
***********************************************************************

    .sect "codestart"
    .retain

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ;Branch to watchdog disable code
    .else
        LB _c_int00         ;Branch to start of boot._asm in RTS library
    .endif

;end codestart section

***********************************************************************
* Function: wd_disable
*
* Description: Disables the watchdog timer
***********************************************************************
    .if WD_DISABLE == 1

    .text
wd_disable:
    SETC OBJMODE        ;Set OBJMODE for 28x object code
    EALLOW              ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6  ;Set data page for WDCR register
    MOV @7029h, #0068h  ;Set WDDIS bit in WDCR to disable WD
    EDIS                ;Disable EALLOW protected register access
    ;LB _c_int00         ;Branch to start of boot._asm in RTS library
    LCR main

 ; Cleanup and exit.  At this point the EntryAddr
; is located in the ACC register
    LB  ExitBoot
    .endif

;end wd_disable

;-----------------------------------------------
; ExitBoot
;-----------------------------------------------
;-----------------------------------------------
;This module cleans up after the boot loader
;
; 1) Make sure the stack is deallocated.
;    SP = 0x400 after exiting the boot
;    loader
; 2) Push 0 onto the stack so RPC will be
;    0 after using LRETR to jump to the
;    entry point
; 2) Load RPC with the entry point
; 3) Clear all XARn registers
; 4) Clear ACC, P and XT registers
; 5) LRETR - this will also clear the RPC
;    register since 0 was on the stack
;-----------------------------------------------

ExitBoot:

__stack:    .usect ".stack",0

;-----------------------------------------------
;   Insure that the stack is deallocated
;-----------------------------------------------

    MOV SP,#__stack

;-----------------------------------------------
; Clear the bottom of the stack.  This will endup
; in RPC when we are finished
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0

;-----------------------------------------------
; Load RPC with the entry point as determined
; by the boot mode.  This address will be returned
; in the ACC register.
;-----------------------------------------------

    PUSH ACC
    POP  RPC

;-----------------------------------------------
; Put registers back in their reset state.
;
; Clear all the XARn, ACC, XT, and P and DP
; registers
;
; NOTE: Leave the device in C28x operating mode
;       (OBJMODE = 1, AMODE = 0)
;-----------------------------------------------
    ZAPA
    MOVL  XT,ACC
    MOVZ  AR0,AL
    MOVZ  AR1,AL
    MOVZ  AR2,AL
    MOVZ  AR3,AL
    MOVZ  AR4,AL
    MOVZ  AR5,AL
    MOVZ  AR6,AL
    MOVZ  AR7,AL
    MOVW  DP, #0

;------------------------------------------------
;   Restore ST0 and ST1.  Note OBJMODE is
;   the only bit not restored to its reset state.
;   OBJMODE is left set for C28x object operating
;   mode.
;
;  ST0 = 0x0000     ST1 = 0x0A0B
;  15:10 OVC = 0    15:13      ARP = 0
;   9: 7  PM = 0       12       XF = 0
;      6   V = 0       11  M0M1MAP = 1
;      5   N = 0       10  reserved
;      4   Z = 0        9  OBJMODE = 1
;      3   C = 0        8    AMODE = 0
;      2  TC = 0        7 IDLESTAT = 0
;      1 OVM = 0        6   EALLOW = 0
;      0 SXM = 0        5     LOOP = 0
;                       4      SPA = 0
;                       3     VMAP = 1
;                       2    PAGE0 = 0
;                       1     DBGM = 1
;                       0     INTM = 1
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0x0A0B
    POP  ST1
    POP  ST0

;------------------------------------------------
;   Jump to the EntryAddr as defined by the
;   boot mode selected and continue execution
;-----------------------------------------------

    LRETR

;eof ----------

	.end


;//
;// End of file.
;//
