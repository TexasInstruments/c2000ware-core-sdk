//###########################################################################
//
// FILE:   emif_dc.h
//
// TITLE:  Constants and function prototypes for emif_dc.c
//
//###########################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef EMIF_DC_H
#define EMIF_DC_H

// Set EMIF_DC_F2837X_LAUNCHPAD_V1 to 1 if using F2837x LaunchPad v1.x
#define EMIF_DC_F2837X_LAUNCHPAD_V1         1

// EMIF number used by tool platform
#define EMIF_DC_F2837X_LAUNCHPAD_EMIF_NUM   1
#define EMIF_DC_F2837X_CONTROLCARD_EMIF_NUM 2

// GPIO value for CS switch control
#define EMIF_DC_ASRAM                       0
#define EMIF_DC_FLASH                       1

// Virtual pages supported for each memory
#define EMIF_DC_ASRAM_PAGES                16
#define EMIF_DC_FLASH_PAGES                64

// Function prototypes
extern void EMIF_DC_setupPinmux(Uint16 emifModule, Uint16 cpuSel);
extern void EMIF_DC_initModule(Uint16 emifModule);
extern void EMIF_DC_initCS0(Uint16 emifModule);
extern void EMIF_DC_initCS2(Uint16 emifModule, Uint16 CS2Mem);
extern void EMIF_DC_selectCS2Memory(Uint16 emifModule, Uint16 CS2Mem);
extern void EMIF_DC_selectCS2Page(Uint16 emifModule, Uint16 page);
extern void EMIF_DC_programCS2Flash(Uint16 emifModule, Uint32 addr, Uint16 data);
extern void EMIF_DC_eraseCS2Flash(Uint16 emifModule);
extern void EMIF_DC_enterCS2FlashCFI(Uint16 emifModule);
extern void EMIF_DC_exitCS2FlashCFI(Uint16 emifModule);
#endif
