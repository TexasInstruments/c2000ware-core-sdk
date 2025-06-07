//#############################################################################
//
// FILE:   dcsm_ex1_cpu_access_control.c
//
// TITLE:  DCSM master CPU Access control Example
//
//! \addtogroup driver_cm_c28x_dual_example_list
//! <h1> DCSM Memory Access control by master CPU1</h1>
//!
//! This example demonstrates how to configure the 1st Zone Select Block 
//! in the OTP to allocate CM's C0RAM to zone 1 & CM's C1RAM to zone 2, 
//! later accessed by CM.
//!
//!                 Zone1  |  Zone2
//!                        |
//!             CM's C0RAM |  CM's C1RAM
//!                        |
//!
//! In this example, zoning of memories is done by the OTP programming whose 
//! values are configured in dcsm_ex1_f2838x_dcsm_zxotp.asm while the securing 
//! functionalities are done through this file.
//! It demonstrates how to control the access of the memories which would
//! later be accessed by CM.
//! This would even do a dummy read of the password needed by CM to
//! unsecure the memory. The communication between the 2 CPUs are done 
//! using IPC ( Inter process communication) through a synch function. 
//! This enables the CPU Core to wait until the expected task is 
//! completed on the other core.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b result - Status of Memory Access control by CPU1
//!  - \b set_error - Count of errors occurring during the execution of the
//!       example.
//!
//!  \note Before running the example, the below configuration is expected to 
//! be done through the dcsm_ex1_f2838x_dcsm_zxotp.asm :
//! 
//! - Allocate CM's C0RAM to zone 1 , C1RAM to zone 2
//! 	ZSBx_Z1_GRABRAM2R 0x0AAAAA09
//! 	ZSBx_Z2_GRABRAM2R 0x0AAAAA06
//! - Password of zone 1 is 0xFFFFFFFF4D7FFFFFFFFFFFFFFFFFFFFF
//! - Password of zone 2 is 0xFFFFFFFF1F7FFFFFFFFFFFFFFFFFFFFF
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

uint32_t result = FAIL;

//
// Main
//
void main(void)
{
    //
    //Variable showing the error occurred while testing DCSM
    //
    uint16_t set_error=0;

    DCSM_SecurityStatus status1;

    //
    //Variable to check the status of the CM's Ram module allocated to zone
    //
    DCSM_MemoryStatus mem_status;

    //
    //Initialize device clock and peripherals
    //
    Device_init();

    //
    //Boot CM core
    //
#ifdef _FLASH
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCM(BOOTMODE_BOOT_TO_S0RAM);
#endif

    //
    //Synchronize CPU1 and CM cores - CPU1 device init & CM boot complete
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG12);

    //
    //Synchronize CPU1 and CM cores - CM has finished unlocking all
    //zones at start
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG11);

    //
    //Getting the default status of the zone 1
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_UNSECURE) set_error++;
    
    //
    //Since this example writes/reads to CM's C0RAM & C1RAM
    //memories, only the status of these RAMs are checked.
    //
    //Getting the default status of the CM's C0RAM allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAM_CM_C0,DCSM_CPUSEL_CM);
    if(mem_status!=DCSM_MEMORY_ZONE1) set_error++;
    
    //
    //Getting the default status of the CM's C1RAM allocation
    //
    mem_status = DCSM_getRAMZone(DCSM_RAM_CM_C1,DCSM_CPUSEL_CM);
    if(mem_status!=DCSM_MEMORY_ZONE2) set_error++;

    //
    //Synchronize CPU1 and CM cores - CM has finished writing to the memories
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG11);

    //
    //Synchronize CPU1 and CM cores - CM's memories are secure
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG12);

    //
    //Getting the status of zone1 after locking it
    //
    status1 = DCSM_getZone1CSMSecurityStatus();
    if(status1!=DCSM_STATUS_SECURE) set_error++;

    //
    //Perform dummy read of the Zone 1 CSM password before 
    //the CM writes to the CSM key to unlock the memories
    //
    DCSM_readZone1CSMPwd();

    //
    //Synchronize CPU1 and CM cores - CPU1 dummy read of the Zone 1 
    //CSM password before the CM writes to the CSM key complete
    //
    IPC_sync(IPC_CPU1_L_CM_R, IPC_FLAG11);

    //
    //Status of Memory Access control by CPU1
    //
    if (set_error)
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
