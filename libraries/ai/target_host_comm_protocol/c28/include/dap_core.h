/*
 *  Created on: Aug 30, 2024
 */

//#############################################################################
//
// FILE:   dap_core.h
//
//!
//! This contains prototyping of core API functions required to support device
//! agent protocol(dap)
//
//#############################################################################
//
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

#ifndef GUI_API_H_
#define GUI_API_H_

#include "protocol_packaging.h"

//Function Prototypes
__interrupt void sciaRXFIFOISR(void);
void SCI_init();
void get_capabilites_response();
void list_sensor_response(uint16_t sensor_count, uint16_t sensor_index, const char sensor_index_info[]);
extern void list_model_response(uint16_t model_count, uint16_t model_index, const char model_index_info[]);

void RX_FIFO_level_reset_before_pipeline_config();
void configure_pipeline_response();
void RX_FIFO_level_reset_after_pipeline_config();
void start_streaming_response();
void stop_streaming_response();
void property_read_response_uint16(uint16_t property_index, uint16_t property_value);
void property_read_response_uint32(uint16_t property_index, uint32_t property_value);
void property_written_response(uint16_t property_index);
void list_property_response(uint16_t property_count, uint16_t property_index, uint16_t property_dataformat, const char property_index_info[]);
void list_inference_values_response(uint16_t inference_count, uint16_t inference_index, uint16_t inference_dataformat, const char inference_index_info[]);

int payload_length_cal(uint32_t original_data_length);


#endif /* GUI_API_H_ */
