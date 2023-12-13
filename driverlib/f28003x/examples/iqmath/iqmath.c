//#############################################################################
//
// FILE:   IQmath_main.c
//
// TITLE:  IQmath SysConfig Example
//
// IQmath SysCfg Example
//
// This example is an IQmath project setup for SysConfig and Driverlib
// development.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

//
// Main
//
void main(void)
{
    //
    // CPU Initialization
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
	Board_init();

	//
	// Convert floating-point to fixed-point (_iq) value
	// NOTE: Default N data type value for _iq is _iq24
	//
    _iq param0 = _IQ(9.0);
    _iq param1 = _IQ(3.0);

    //
    // Perform arithmetic (multiplication and division)
    //
    _iq resultMult = _IQmpy(param0, param1);
    _iq resultDivi = _IQdiv(param0, param1);

    //
    // Convert results and parameters to floating point to verify results
    // and proper conversion
    //
    float32_t floatParam0 = _IQtoF(param0);
    float32_t floatParam1 = _IQtoF(param1);
    float32_t floatResultMult = _IQtoF(resultMult);
    float32_t floatResultDivi = _IQtoF(resultDivi);

	while(1);
}

//
// End of File
//
