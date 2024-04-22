//###########################################################################
//
// FILE:    boostxl_afe031_F2837xD_Sci.h
//
// TITLE:   F2837xD Devices Serial Communication Interface definitions.
//
//###########################################################################
//
// 
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

#ifndef BOOSTXL_AFE031_F2837XD_SCI_H
#define BOOSTXL_AFE031_F2837XD_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Commands
//
#define CMD_UNKNOWN         0
#define CMD_GET_HELP        1
#define CMD_GET_VER_INFO    2
#define CMD_GET_MARK_GAIN   3
#define CMD_SET_MARK_GAIN   4
#define CMD_GET_SPACE_GAIN  5
#define CMD_SET_SPACE_GAIN  6
#define CMD_GET_DAC_OFFSET  7
#define CMD_SET_DAC_OFFSET  8
#define CMD_GET_CURRENT_CNT 9
#define CMD_SET_CURRENT_CNT 10
#define CMD_GET_THERMAL_CNT 11
#define CMD_SET_THERMAL_CNT 12
#define CMD_GET_USER_TM     13
#define CMD_SET_USER_TM     14

//
// Test Modes
//
#define TM_TRANSMIT_KA      0   // Transmit Keep-Alive packets (default)
#define TM_TRANSMIT_AS      1   // Transmit Accelerated Shutdown packets
#define TM_TRANSMIT_MARK    2   // Transmit MARK tone continuously
#define TM_TRANSMIT_SPACE   3   // Transmit SPACE tone continuously
#define TM_TRANSMIT_W1      4   // Transmit Logic '1' word continuously
#define TM_TRANSMIT_W0      5   // Transmit Logic '0' word continuously
#define TM_PA_SHUTDOWN      6   // Power Amp Shutdown
#define TM_PA_ENABLE        7   // Power Amp Enable

//
// External Globals
//
extern Uint32 GAIN_SPACE_x1024;     // SPACE Gain x 1024
extern Uint32 GAIN_MARK_x1024;      // MARK Gain x 1024
extern Uint32 DAC_CODE_OFFSET;      // DAC code offset
extern Uint32 intCurrent;           // Overcurrent event counter
extern Uint32 intThermal;           // Thermal shutdown event counter
extern Uint16 tmUser;               // User-selected test mode

//
// Function Prototypes
//
void scia_fifo_init(void);
void scia_gpio_init(void);
void scia_port_init(void);
void scia_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
void scia_service(void);
void scia_cmd_reset(void);
int scia_cmd_parser(char* cmd, long* num);
int scia_str2num(char* str, long* num);
char* scia_num2str(long num);
long scia_pow10(long pow);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // eof

//
// End of file
//
