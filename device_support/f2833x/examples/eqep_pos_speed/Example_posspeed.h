//###########################################################################
//
// FILE:	Example_posspeed.h
//
// TITLE:	Pos/speed measurement using EQEP peripheral
//
// DESCRIPTION: Header file containing data type and object definitions and 
// initializers. 
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __POSSPEED__
#define __POSSPEED__

//
// Included Files
//
#include "IQmathLib.h"         // Include header for IQmath library

//
// Typedef for the structure of the POSSPEED Object 
//
typedef struct 
{
    int theta_elec;     	// Output: Motor Electrical angle (Q15)  
    int theta_mech;     	// Output: Motor Mechanical Angle (Q15) 
    int DirectionQep;      	// Output: Motor rotation direction (Q0) 
    int QEP_cnt_idx; 	 	// Variable: Encoder counter index (Q0)
    int theta_raw;     		// Variable: Raw angle from Timer 2 (Q0)            
    
    //
    // Parameter: 0.9999/total count, total count = 4000 (Q26)
    //
    int mech_scaler;
    
    int pole_pairs;     	// Parameter: Number of pole pairs (Q0) 
    
    //
    // Parameter: Raw angular offset between encoder and phase a (Q0) 
    //
    int cal_angle;     		
    int index_sync_flag; 	// Output: Index sync status (Q0)                   

    //
    // Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0)
    // independently with global Q
    //
    Uint32 SpeedScaler;     
    _iq Speed_pr;           // Output :  speed in per-unit
    
    //
    // Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed
    // independently with global Q
    //
    Uint32 BaseRpm;         
    
    //
    // Output : speed in r.p.m. (Q0) - independently with global Q 
    //
    int32 SpeedRpm_pr;

    _iq  oldpos;  			// Input: Electrical angle (pu) 
    _iq Speed_fr;           // Output :  speed in per-unit
    
    //
    // Output : Speed in rpm  (Q0) - independently with global Q
    //
    int32 SpeedRpm_fr;
    void (*init)();     	// Pointer to the init function          
    void (*calc)();    		// Pointer to the calc function        
} POSSPEED;

//
// Typedef for the POSSPEED_handle
//
typedef POSSPEED *POSSPEED_handle;

//
// Defines for the default initializer for the POSSPEED Object.
//
#if (CPU_FRQ_150MHZ)
    #define POSSPEED_DEFAULTS {0x0, 0x0,0x0,0x0,0x0,16776,2,0,0x0,\
        94,0,6000,0,\
        0,0,0,\
        (void (*)(long))POSSPEED_Init,\
        (void (*)(long))POSSPEED_Calc }
#endif
#if (CPU_FRQ_100MHZ)
    #define POSSPEED_DEFAULTS {0x0, 0x0,0x0,0x0,0x0,16776,2,0,0x0,\
        63,0,6000,0,\
        0,0,0,\
        (void (*)(long))POSSPEED_Init,\
        (void (*)(long))POSSPEED_Calc }
#endif

//
// Function Prototypes
//
void POSSPEED_Init(void);                                              
void POSSPEED_Calc(POSSPEED_handle);
                
#endif /*  __POSSPEED__ */

//
// End of File
//

