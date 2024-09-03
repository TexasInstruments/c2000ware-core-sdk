//#############################################################################
//
// FILE:   watchdog_ex1_nmi_handling.c
//
// TITLE:  Windowed watchdog expiry with NMI handling
//
//! \addtogroup driver_example_cm_list
//! <h1>Windowed watchdog expiry with NMI handling</h1>
//!
//! This program demonstrates an NMI generation to the CM4 core when
//! the Windowed watchdog ( WWD ) expires.
//!
//! A delay is provided after enabling the WWD to make the watchdog
//! count up from 0 to 0xFF. Once 0 is reached, an NMI is triggered.
//! Currently on triggering an NMI, a status flag is set indicating if the NMI
//! was handled after the WWD expired.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b wdstatus - Indicates if the WWD caused an NMI on expiry.
//!  - \b cmnmi - Indicates if the NMI was handled after the WWD expired
//!  - \b fail - Status if the Windowed watchdog expired generating an NMI 
//!       with proper NMI handling
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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
#include <stdint.h>
#include <stdbool.h>

#include "cm.h"

//
// Defines
//
uint16_t cmnmi;
bool wdstatus = false;
uint32_t nmiflagstatus = 0, fail = 0;

//
// Function Prototypes
//
__interrupt void cmnmiISR(void);

//
// Main
//
void main(void)
{   
    //
    // Register the interrupt handler.
    //
    Interrupt_registerHandler(FAULT_NMI,cmnmiISR);

    //
    // Enable the NMI interrupt.
    //
    Interrupt_enable(FAULT_NMI);
    
    //
    // Clear All NMI flags
    //
    SysCtl_clearAllNMIFlags();
    
    //SysCtl_setWatchdogWindowValue(0x0F);
        
    //
    // Enable the watchdog.
    //
    SysCtl_enableWatchdog();

    //
    // Enable global interrupts.
    //
    SysCtl_enableGlobalNMI();
    
    //
    // Wait till the NMI is triggered
    //
    while(wdstatus == false)
    {
      //
      // Provide a delay to get the wwd
      // to expire
      //
      SysCtl_delay(1000);
    }
    
    //
    // Check if the WWD caused an non-maskable interrupt on expiry.
    //
    if(nmiflagstatus != (SYSCTL_NMI_WWDNMI | SYSCTL_NMI_NMIINT))
    { 
        fail++;       
    }
    
    //
    // Check if the NMI was handled after
    // the WWD expired
    //
    if(cmnmi != 1)
    { 
        fail++;       
    }
    
    //
    // Disable the watchdog.
    //
    SysCtl_disableWatchdog();
}

//
// NMI ISR
//
 __interrupt void cmnmiISR(void)
{
    //
    // Get the WWD status and clear it
    //
    wdstatus = SysCtl_getWatchdogStatus();
    SysCtl_clearWatchdogStatus();

    //
    // NMI was handled after the WWD expired
    // 
    cmnmi = 1;
    nmiflagstatus = SysCtl_getNMIFlagStatus();
    SysCtl_clearAllNMIFlags();
}

//
// End of File
//

