//#############################################################################
//
// FILE:   clb_ex32_lp589x_api.h
//
// TITLE:  Simple APIs for configuring the LP5891 LED driver.
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
//#############################################################################

//
// Included Files
//
#include <clb_ex32_system_info.h>

//
// Globals
//
extern uint16_t vsyncDone;

//
// Function Prototypes
//
void setData(uint16_t *data, uint16_t high, uint16_t mid, uint16_t low, uint16_t bias);

void LED_Set_Chip_Index(unsigned int checkResponse);

void LED_Write_RGB_Custom_ALL(uint16_t r_value, uint16_t g_value, uint16_t b_value);
void LED_Write_Black_ALL(void);
void LED_Write_White_ALL(void);
void LED_Write_Red_ALL(void);
void LED_Write_Green_ALL(void);
void LED_Write_Blue_ALL(void);
void LED_Write_Red_Custom_ALL(uint16_t brt_value);
void LED_Write_Green_Custom_ALL(uint16_t brt_value);
void LED_Write_Blue_Custom_ALL(uint16_t brt_value);

void LED_Write_Reg_Broadcast(uint16_t fc_reg, uint16_t data2, uint16_t data1, uint16_t data0, unsigned int checkResponse);

void sendSYNC();
void sendSYNCnoWait();

//
// End of File
//
