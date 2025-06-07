/*
 *  Created on: Aug 30, 2024
 */
//#############################################################################
//
// FILE:   dap_interface.c
//
//!
//! This contains definition of top level user accessible API functions required
//! to support device agent protocol(dap)
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
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

#include "dap_core.h"
#include "dap_interface.h"

/***********Device Name where the firmware will be running from**************/
const char Device_name[] = "f28p55x";

/************All available sensor info****************/
uint8_t total_sensor_count = 4;

const char sensor_dummy_info[] = "{\"name\":\"dummy\",\"type\":7,\"dataFormat\":6,\"labels\":\"x\"}";
const char sensor_index1_info[] = "{\"name\":\"AFE_Ch1_current\",\"type\":6,\"dataFormat\":5,\"labels\":\"Arc current if Ch1 is selected\"}";
const char sensor_index2_info[] = "{\"name\":\"AFE_Ch2_current\",\"type\":6,\"dataFormat\":5,\"labels\":\"Arc current if Ch2 is selected\"}";
const char sensor_index3_info[] = "{\"name\":\"AFE_Ch3_current\",\"type\":6,\"dataFormat\":5,\"labels\":\"Arc current if Ch3 is selected\"}";
//const char sensor_index4_info[] = "{\"name\":\"AFE_Ch4_current\",\"type\":6,\"dataFormat\":5,\"labels\":\"Arc current if Ch4 is selected\"}";
const char sensor_index4_info[] = "{\"name\":\"Vib_sensor1\",\"type\":7,\"dataFormat\":6,\"labels\":\"x\"}";

void list_all_sensors()
{
    list_sensor_response(total_sensor_count,sensor_index1,sensor_index1_info);
    list_sensor_response(total_sensor_count,sensor_index2,sensor_index2_info);
    list_sensor_response(total_sensor_count,sensor_index3,sensor_index3_info);
    list_sensor_response(total_sensor_count,sensor_index4,sensor_index4_info);
}

/************All supported AI model info for the application****************/
uint8_t total_model_count = 3;

const char model_index1_info[] = "{\"name\":\"ArcFault_model_200_t\",\"task\":\"ArcFault_model\",\"projectID\":\"Project_Name\"}";
const char model_index2_info[] = "{\"name\":\"ArcFault_model_300_t\",\"task\":\"ArcFault_model\",\"projectID\":\"Project_Name\"}";
const char model_index3_info[] = "{\"name\":\"ArcFault_model_700_t\",\"task\":\"ArcFault_model\",\"projectID\":\"Project_Name\"}";

void list_all_models()
{
    list_model_response(total_model_count,model_index1,model_index1_info);
    list_model_response(total_model_count,model_index2,model_index2_info);
    list_model_response(total_model_count,model_index3,model_index3_info);
}

/*************All supported property info for the application**************/
uint8_t total_property_count = 1;

const char property_index1_info[] = "Property1";

void list_all_properties()
{
    list_property_response(total_property_count, property_index1, property_dataformat5, property_index1_info);
}
//In current version property_dataformat5 (uint16) & property_dataformat6 (uint32) supported

/*************All supported inference info for the application**************/
uint8_t total_interface_count = 1;

const char inference_index1_info[] = "inferenceA";

void list_all_inferences()
{
    list_inference_values_response(total_interface_count, inference_index1, inference_dataformat5, inference_index1_info);
}

//In current version inference_dataformat5 (uint16) & inference_dataformat6 (uint32) supported

/***********Debug Functions************/
void sci_write_char_array(uint16_t* msg, int len)
{
    SCI_writeCharArray(SCI_INST_BASE_ADDR, (uint16_t*)msg, len);
}

