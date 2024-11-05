/*
 *  Created on: Aug 30, 2024
 */
//#############################################################################
//
// FILE:   dap_interface.h
//
//!
//! This contains function prototyping of top level user accessible APIs and
//! user define macros
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
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

#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

//Whether to debug in the terminal (1) or in the GC application (0)
//#define TERMINAL_DEBUGGING_MODE 1
#define TERMINAL_DEBUGGING_MODE 0

#define SCI_BAUD_RATE 2343750         // 37.5Mhz/16
//#define SCI_BAUD_RATE 9375000         // 37.5Mhz/16 *4
//#define SCI_BAUD_RATE 4687500         // 37.5Mhz/16 *2

#define PROPERTY_VAL_TYPE_UINT16    1   //default value is 1
#define PROPERTY_VAL_TYPE_UINT32    0   //default value is 0

enum receive_data_reponse_payload_channel_value_comp { //Response payload components
    sensor_signal = 0x01,
    inferencing_signal = 0x03,
    inferencing_result = 0x04,
    inferencing_value = 0x05,
    inferencing_log = 0x06
};

/***********Main Functions************/
void guiInitialization();
void received_data_response(uint32_t data_payload_length, uint16_t channel_value, uint16_t* data_array);
void data_conversion_from_16_to_8_bits(uint16_t* input_buf, int input_buf_size, uint8_t* output_buf);
void data_conversion_from_32_to_8_bits(uint32_t* input_buf, int input_buf_size, uint8_t* output_buf);
void sci_write_char_array(uint16_t* msg, int len);


/***********Other Functions************/
void list_all_sensors();
void list_all_models();
void list_all_properties();
void list_all_inferences();

#endif /* USER_INTERFACE_H_ */
