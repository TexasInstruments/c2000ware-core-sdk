//#############################################################################
//
// FILE:   systick_ex1_interrupt.c
//
// TITLE:  SysTick interrupt example
//
//! \addtogroup driver_example_cm_list
//! <h1>Systick interrupt example</h1>
//!
//! This example showcases how to use configure Systick interrupt. It increments 
//! a counter every time the SysTick interrupt is asserted
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b isrCount - ISR counter
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "systick.h"

uint32_t isrCount = 0;

void sysTickHandler(void)
{
	isrCount++;
}

//
// Main
//
void main(void)
{
	//
	// Register Systick interrupt
	//
	SYSTICK_registerInterruptHandler(sysTickHandler);

	//
	// Set timer period as 100 ticks
	//
	SYSTICK_setPeriod(100);
	
	//
	// Enable counter
	//
	SYSTICK_enableCounter();

	//
	// Loop forever
	//
	while(1);
}
