//###########################################################################
//
// FILE:   emif_dc_pages.c
//
// TITLE:  EMIF Daughtercard CS2 Virtual Pages
//
//! \addtogroup cpu01_example_list
//! <h1>EMIF Daughtercard CS2 Virtual Pages (emif_dc_pages)</h1>
//!
//!  This example runs on an EMIF Daughtercard that connects through
//!  the high density connector on F2837X evaluation boards:
//!    - TMDSCNCD28379D
//!    - LAUNCHXL-F28379D
//!    - LAUNCHXL-F28377S
//!
//!  GPIO-controlled virtual page selection is demonstrated for CS2.
//!
//!  The following values must match the target evaluation board:
//!     - EMIF_NUM (emif_dc_cpu.c)
//!     - EMIF_DC_F2837X_LAUNCHPAD_V1 (emif_dc.h)
//!     - _LAUNCHXL_F28377S or _LAUNCHXL_F28379D (Predefined Symbols)
//!
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

//
// Included Files
//
#include "F28x_Project.h"
#include "emif_dc.h"

//
// Constants
//
#define EMIF_NUM      EMIF_DC_F2837X_LAUNCHPAD_EMIF_NUM
#define BUFFER_WORDS  16

//
// Global Variabls
//
#if( EMIF_NUM == EMIF_DC_F2837X_LAUNCHPAD_EMIF_NUM   )
#pragma DATA_SECTION(dataBuffer, ".em1_cs2");
#endif
#if( EMIF_NUM == EMIF_DC_F2837X_CONTROLCARD_EMIF_NUM )
#pragma DATA_SECTION(dataBuffer, ".em2_cs2");
#endif
Uint16 dataBuffer[BUFFER_WORDS];

//
// Main
//
void main(void)
{
    Uint16 word;
    Uint16 page;
    Uint16 errors;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Initialize EMIF module for use with daughtercard
    //
    EMIF_DC_setupPinmux(EMIF_NUM, GPIO_MUX_CPU1);
    EMIF_DC_initModule(EMIF_NUM);
    EMIF_DC_initCS0(EMIF_NUM);
    EMIF_DC_initCS2(EMIF_NUM, EMIF_DC_ASRAM);

    //
    // Initialize data buffer pages
    //
    for(page=0; page<EMIF_DC_ASRAM_PAGES; page++)
    {
        EMIF_DC_selectCS2Page(EMIF_NUM, page);

        for(word=0; word<BUFFER_WORDS; word++)
        {
            dataBuffer[word] = (page * BUFFER_WORDS) + word;
        }
    }

    //
    // Verify data buffer pages
    // If buffers are not initialized correctly, check the following:
    //      EMIF_NUM (emif_dc_cla.c)
    //      EMIF_DC_F2837X_LAUNCHPAD_V1 (emif_dc.h)
    //      _LAUNCHXL_F28377S or _LAUNCHXL_F28379D (Predefined Symbols)
    //
    errors = 0;

    for(page=0; page<EMIF_DC_ASRAM_PAGES; page++)
    {
        EMIF_DC_selectCS2Page(EMIF_NUM, page);

        for(word=0; word<BUFFER_WORDS; word++)
        {
            if(dataBuffer[word] != ((page * BUFFER_WORDS) + word))
            {
                errors++;
                ESTOP0;
                break;
            }
        }
    }

    if(errors == 0)
    {
        ESTOP0; // PASS
    }
    else
    {
        ESTOP0; // FAIL
    }
}

//
// End of file
//
