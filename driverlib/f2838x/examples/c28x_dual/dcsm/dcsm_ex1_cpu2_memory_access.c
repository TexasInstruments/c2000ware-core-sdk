//#############################################################################
//
// FILE:   dcsm_ex1_cpu2_memory_access.c
//
// TITLE:  DCSM CPU2 Secure Memory Access
//
//! \addtogroup driver_dual_example_list
//! <h1> DCSM Memory Access by CPU2 </h1>
//!
//! This example demonstrates how the access of the memory is affected
//! when the memories are secured by CPU1. 
//! CPU1 allocate CPU2's LS4-LS5 to zone 1 & CPU2's LS6-LS7 to zone 2 using 
//! the 1st Zone Select Block.
//!
//!                 Zone1  |  Zone2
//!                        |
//!         CPU2's LS4-LS5 |  CPU2's LS6-LS7
//!                        |
//!
//! It writes some data in the zones and checks after the CPU1 does a memory
//! locking and matches with the data set . Further, once the CPU2 unlocks the 
//! memories, it matches with the data set written before CPU1 lock. 
//! Ideally after locking, zone1 should not be readable(or reads a 0 value) 
//! and zone2 that is not secured matches the written data set.
//! It demonstrates how to lock and and unlock zone by showing where to put
//! the password and how to check if it is secured or unsecured.
//! 
//! The communication between the 2 CPUs are handled using IPC 
//!(Inter process communication) through a synch function. 
//! This enables the CPU Core to wait until the expected task is 
//! completed on the other core.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of CPU2's secure memory access
//!  - \b set_error, error_not_locked ,error_not_unlocked ,error1 - Count of 
//!       errors occurring during the execution of the example.
//!  - \b Zone1_Locked_Array - Array demonstrating secured memory
//!  - \b Unsecure_mem_Array - Array demonstrating Unsecured memory
//!
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

uint16_t Zone1_Locked_Array[256];       // Mapped to LS4 RAM
uint16_t Unsecure_mem_Array[256];       // Mapped to LS6 RAM
DCSM_CSMPasswordKey csmK_z1;    //Zone1 key
DCSM_CSMPasswordKey csmK_z2;    //Zone2 key

#pragma DATA_SECTION(Zone1_Locked_Array,"ZONE1_RAM");
#pragma DATA_SECTION(Unsecure_mem_Array,"UNSECURE_RAM");
#pragma DATA_SECTION(csmK_z1,"CSMKEY_RAM");
#pragma DATA_SECTION(csmK_z2,"CSMKEY_RAM");

uint32_t result = FAIL;

//
// Main
//
void main(void)
{
    //
    //Variables showing the error occurred while testing DCSM
    //
    uint16_t i=0,error_not_locked=0,error_not_unlocked=0,error1=0,set_error=0;

    DCSM_SecurityStatus status1;

    //
    //Synchronize CPU1 and CPU2 cores - CPU1 device init and CPU2 
    //boot complete
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG12);

    //
    //Updating the Zone1 key value
    //
    csmK_z1.csmKey0 = 0xFFFFFFFF;
    csmK_z1.csmKey1 = 0x4D7FFFFF;
    csmK_z1.csmKey2 = 0xFFFFFFFF;
    csmK_z1.csmKey3 = 0xFFFFFFFF;

    //
    //Updating the Zone2 key value
    //
    csmK_z2.csmKey0 = 0xFFFFFFFF;
    csmK_z2.csmKey1 = 0x1F7FFFFF;
    csmK_z2.csmKey2 = 0xFFFFFFFF;
    csmK_z2.csmKey3 = 0xFFFFFFFF;

    //
    //Unlocking the zone1 using the key since the password maybe
    //different from the default
    //
    DCSM_writeZone1CSM(&csmK_z1);

    //
    //Unlocking the zone2 using the key since the password maybe
    //different from the default
    //
    DCSM_writeZone2CSM(&csmK_z2);

    //
    //Synchronize CPU1 and CPU2 cores - CPU2 has finished device zone unlock
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG11);

    //
    //Initialize device clock and peripherals
    //
    Device_init();
    
    //
    //Updating the arrays one which belong to zone1 and other 
    //which belongs to zone2
    //
    for(i=1;i<256;i++)
    {
        Unsecure_mem_Array[i] = i;
        Zone1_Locked_Array[i] = i;
    }

    //
    //Synchronize CPU1 and CPU2 cores - CPU1 has finished checking 
    //status of Zones
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG11);

    //
    //Locking the zone1
    //
    DCSM_secureZone1();

    //
    //Synchronize CPU1 and CPU2 cores - CPU1 has finished checking 
    //status of Zones
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG12);

    //
    //Read both the arrays. One which is not secured would be 
    //readable unlike the other secured one that wouldn't be.
    //
    for(i=1;i<256;i++)
    {
        if(Unsecure_mem_Array[i] != i) error1++;
        if(Zone1_Locked_Array[i] == i) error_not_locked++ ;
    }

    //
    //Synchronize CPU1 and CPU2 cores - CPU1 dummy read of the 
    //Zone1 CSM Password complete
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG11);

    //
    //Unlocking the zone1 by writing the Zone1 CSM key 
    //
    DCSM_writeZone1CSM(&csmK_z1);

    //
    //Getting the status of zone 1 after unlocking it .
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_UNSECURE) set_error++;
    
    //
    //Since the zone1 has been unlocked both should be readable
    //
    for(i=1;i<256;i++)
    {
        if(Unsecure_mem_Array[i] != i) error1++;
        if(Zone1_Locked_Array[i] != i) error_not_unlocked++ ;
    }

    //
    //Status of CPU2's secure memory access
    //
    if (error1 | error_not_unlocked | set_error | error_not_locked)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;

    }

    while(1);

}

//
// End of File
//
