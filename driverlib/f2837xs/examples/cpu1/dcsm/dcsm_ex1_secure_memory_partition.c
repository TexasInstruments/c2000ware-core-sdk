//#############################################################################
//
// FILE:   dcsm_ex1_secure_memory_partition.c
//
// TITLE:  DCSM Memory partitioning Example
//
//! \addtogroup driver_example_list
//! <h1> DCSM Memory partitioning Example </h1>
//!
//! This example demonstrates how to configure and use DCSM.
//! It configures the OTP needed to change the zone passwords
//! and allocates LS2-LS3 to zone 1.
//! Zoning of memories is done by the OTP programming while the securing
//! functionalities are done through this example.
//! It Writes some data in the zones and checks before locking and after
//! locking and matches with the data set . Ideally after locking zone1 should
//! read a wrong 0 value.
//!
//! It demonstrates how to lock and and unlock zone by showing where to put
//! the password and how to check if it is secured or unsecured.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of Secure memory partitioning done through OTP
//!                programming.
//!  - \b Zone1_Locked_Array - Array demonstrating secured memory
//!  - \b Unsecure_mem_Array - Array demonstrating Unsecured memory
//!
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Defines
//
#define PASS 0
#define FAIL 1

uint32_t result = FAIL;

uint16_t Zone1_Locked_Array[256];       // Mapped to LS2 RAM
uint16_t Unsecure_mem_Array[256];       // Mapped to LS4 RAM
#pragma DATA_SECTION(Zone1_Locked_Array,"ZONE1_RAM");
#pragma DATA_SECTION(Unsecure_mem_Array,"UNSECURE_RAM");

//*ATTENTION*//
//Below code snippet programs the OTP registers to configure zone 1
//Default configurations mentioned in TRM.
//
//Tasks done for the OTP registers currently only zone 1
//Changes the password
//DCSM_Z1OTP_BASE
//PSWD 0xF0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0
//Allocate LS2 and LS3 to zone 1
//Z1_GRABRAMR 0xFFFFFFAF
//
//Uncomment the below lines for the above mentioned zone 1 tasks
//Uncomment the below line to set otp zone 1 register location
/*#pragma RETAIN(otp_data)
#pragma DATA_SECTION(otp_data,"dcsm_zsel_z1");//changing grab ram and zone 1 password.
const long otp_data[8] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFAF,0xFFFFFFFF,
                          0xF0F0F0F0,0xF0F0F0F0,0xF0F0F0F0,0xF0F0F0F0};*/

//*ATTENTION*//
//Uncomment and change the below link pointerrer to use different zone 1
// region linker pointer. Refer to TRM for this.
/*#pragma RETAIN(link_pointer)
#pragma DATA_SECTION(link_pointer,"dcsm_zsel_link_pointer");
const long link_pointer[3] ;= {0xFFFFFFFE,0xFFFFFFFE,0xFFFFFFFE};*/

//
// Main
//
void main(void)
{
    //
    // Variables showing the error occurred while testing DCSM
    //
    uint16_t i=0,error_not_locked=0,error_not_unlocked=0,error1=0,set_error=0;
    DCSM_SecurityStatus status1;

    //
    // Variable to check the status of the Ram module allocated to zone
    //
    DCSM_MemoryStatus mem_status;

    //
    // Zone1 key later checked against the zone 1 PWD to unlock
    //
    DCSM_CSMPasswordKey csmK;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Updating the key value
    //
    csmK.csmKey0 = 0xF0F0F0F0;
    csmK.csmKey1 = 0xF0F0F0F0;
    csmK.csmKey2 = 0xF0F0F0F0;
    csmK.csmKey3 = 0xF0F0F0F0;

    //
    // Unlocking the zone 1 at start of the example
    //
    DCSM_unlockZone1CSM(&csmK);

    //
    // Getting the default status of the zone 1
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_UNSECURE) set_error++;

    //
    // Getting the default status of the RAMLS2 allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAMLS2);
    if(mem_status!=DCSM_MEMORY_ZONE1) set_error++;

    //
    // Getting the default status of the RAMLS4 allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAMLS4);
    if(mem_status!=DCSM_MEMORY_FULL_ACCESS) set_error++;

    //
    // Updating the arrays one which belong to zone1 and other which belongs to z2
    //
    for(i=1;i<256;i++)
    {
        Unsecure_mem_Array[i] = i;
        Zone1_Locked_Array[i] = i;
    }

    //
    // Locking the zone1
    //
    DCSM_secureZone1();

    //
    // Getting the status of zone1 after locking it
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_LOCKED) set_error++;


    //
    // Reading both arrays one which locked so it should not be readable and
    // other which does not belong to secure zone so should be readable
    //
    for(i=1;i<256;i++)
    {
        if(Unsecure_mem_Array[i] != i) error1++;
        if(Zone1_Locked_Array[i] == i) error_not_locked++ ;
    }

    //
    // Unlocking the zone1 using the key after locking it
    //
    DCSM_unlockZone1CSM(&csmK);

    //
    // Getting the status of zone 1 after unlocking it .
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_UNSECURE) set_error++;

    //
    // Since the zone1 has been unlocked both should be readable
    //
    for(i=1;i<256;i++)
    {
        if(Unsecure_mem_Array[i] != i) error1++;
        if(Zone1_Locked_Array[i] != i) error_not_unlocked++ ;
    }

    //
    // Status of Secure memory partitioning
    //
    if (error1 | error_not_unlocked | set_error | error_not_locked)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;
    }

}

//
// End of File
//
