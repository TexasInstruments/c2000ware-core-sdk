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
//! It configures the 1st Zone Select Block in the OTP to change the zone 
//! passwords and allocates LS0-LS3 to zone 1 & LS4-LS7 to zone 2.
//!
//!                 Zone1  |  Zone2
//!                        |
//!                LS0-LS3 |  LS4-LS7
//!                        |
//!
//! In this example, zoning of memories is done by the OTP programming whose 
//! values are configured in dcsm_ex1_f2838x_dcsm_zxotp.asm while the securing 
//! functionalities are done through this file.
//! It writes some data in the zones and checks before locking and after
//! locking and matches with the data set . Ideally after locking zone1, the 
//! data set stored in zone1 should not be readable( or reads a 0 value) and  
//! zone2 that is not secured matches the written data set.
//! It demonstrates how to lock and and unlock zones by showing where to put
//! the password and how to check if it is secured or unsecured.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of Secure memory partitioning done through OTP
//!                programming.
//!  - \b set_error, error_not_locked ,error_not_unlocked ,error1 - Count of 
//!       errors occurring during the execution of the example.
//!  - \b Zone1_Locked_Array - Array demonstrating secured memory
//!  - \b Unsecure_mem_Array - Array demonstrating Unsecured memory
//!
//!  \note Before running the example, the below configuration is expected to 
//! be done through the dcsm_ex1_f2838x_dcsm_zxotp.asm :
//! 
//! - Allocate LS0-LS3 to zone 1 , LS4-LS7 to zone 2
//! 	ZSBx_Z1_GRABRAM1R 0x000AAA55
//! 	ZSBx_Z2_GRABRAM1R 0x000A55AA
//! - Password of zone 1 is 0xFFFFFFFF4D7FFFFFFFFFFFFFFFFFFFFF
//! - Password of zone 2 is 0xFFFFFFFF1F7FFFFFFFFFFFFFFFFFFFFF
//!
//! \note  DCSM_unlockZone*CSM function should not be called in an actual 
//! application, should only be used for once to program the OTP memory. 
//! Ensure flash data cache is disabled before calling this function.
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
DCSM_CSMPasswordKey csmK_z1;	//Zone1 key
DCSM_CSMPasswordKey csmK_z2;    //Zone2 key

#pragma DATA_SECTION(Zone1_Locked_Array,"ZONE1_RAM");
#pragma DATA_SECTION(Unsecure_mem_Array,"UNSECURE_RAM");
#pragma DATA_SECTION(csmK_z1,"CSMKEY_RAM");
#pragma DATA_SECTION(csmK_z2,"CSMKEY_RAM");

//
// Main
//
void main(void)
{
    //
    //Variables showing the error occurred while testing DCSM
    //
    uint16_t i=0,error_not_locked=0,error_not_unlocked=0,error1=0,set_error=0;
    uint32_t cacheEnable;

    DCSM_SecurityStatus status1;

    //
    //Variable to check the status of the Ram module allocated to zone
    //
    DCSM_MemoryStatus mem_status;

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
    // Save the state of the cache enable bit
    //
    cacheEnable = HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &
                    FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    //
    // Disable cache before unlocking the zone
    //
    Flash_disableCache(FLASH0CTRL_BASE);

    //
    //Unlocking the zone1 using the key since the password maybe
    //different from the default
    //
    DCSM_unlockZone1CSM(&csmK_z1);

    //
    //Unlocking the zone2 using the key since the password maybe
    //different from the default
    //
    DCSM_unlockZone2CSM(&csmK_z2);

    //
    // Restore the state of the cache enable bit.
    //
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |= cacheEnable;

    //
    //Initialize device clock and peripherals
    //
    Device_init();

    //
    //Getting the default status of the zone 1
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_UNSECURE) set_error++;
    
    //
    //Getting the default status of the RAMLS2 allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAMLS2,DCSM_CPUSEL_CPU1);
    if(mem_status!=DCSM_MEMORY_ZONE1) set_error++;
    
    //
    //Getting the default status of the RAMLS4 allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAMLS4,DCSM_CPUSEL_CPU1);
    if(mem_status!=DCSM_MEMORY_ZONE2) set_error++;

    //
    //Updating the arrays one which belong to zone1 and other which belongs to z2
    //
    for(i=1;i<256;i++)
    {
        Unsecure_mem_Array[i] = i;
        Zone1_Locked_Array[i] = i;
    }

    //
    //Locking the zone1
    //
    DCSM_secureZone1();

    //
    //Getting the status of zone1 after locking it
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_SECURE) set_error++;

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
    // Save the state of the cache enable bit
    //
    cacheEnable = HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) &
                    FLASH_FRD_INTF_CTRL_DATA_CACHE_EN;

    //
    // Disable cache before unlocking the zone
    //
    Flash_disableCache(FLASH0CTRL_BASE);

    //
    //Unlocking the zone1 using the key after locking it
    //
    DCSM_unlockZone1CSM(&csmK_z1);

    //
    // Restore the state of the cache enable bit.
    //
    HWREG(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) |= cacheEnable;

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
    //Status of Secure memory partitioning
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
