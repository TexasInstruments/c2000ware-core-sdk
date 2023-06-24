
//###########################################################################
//
// FILE:   boot_ex2_customBootConfig.h
//
// TITLE:  Defines and Function Prototypes for Custom Boot Configuration
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef _BOOT_EX2_CUSTOMBOOTCONFIG_H_
#define _BOOT_EX2_CUSTOMBOOTCONFIG_H_

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//

//
// Change the value of STANDALONE_BOOT to a non-zero value in order to emulate the
// standalone boot process. WARNING: the standalone boot process requires the
// user-configurable DCSM OTP (one-time programmable) registers to be programmed.
// Please ensure the DCSM OTP registers are programmed before choosing to emulate
// the standalone boot process.
//
#define STANDALONE_BOOT        0

//
// When the standalone boot flow is emulated, the 3 OTP registers below are programmed.
// The table below specifies the content in each register.
//
//                              Bits       Name                                 Description
// Z1_OTP_BOOTPIN_CONFIG:       31-24      Key                                  Write 0x5A to use custom boot config.
//                                                                              Write any other value in order to
//                                                                              use factory default.
//
//                              23-16      Boot Mode Select Pin 2 (BMSP2)       Set to GPIO to be used during boot
//                              15-8       Boot Mode Select Pin 1 (BMSP1)       Refer to BMSP2
//                              7-0        Boot Mode Select Pin 0 (BMSP0)       Refer to BMSP2
//
// Z1_OTP_BOOTDEF_LOW:          31-24      BOOTDEF3                             BOOTDEF option 3
//                              23-16      BOOTDEF2                             BOOTDEF option 2
//                              15-8       BOOTDEF1                             BOOTDEF option 1
//                              7-0        BOOTDEF0                             BOOTDEF option 0
//
// Z1_OTP_BOOTDEF_HIGH:         31-24      BOOTDEF7                             BOOTDEF option 7
//                              23-16      BOOTDEF6                             BOOTDEF option 6
//                              15-8       BOOTDEF5                             BOOTDEF option 5
//                              7-0        BOOTDEF4                             BOOTDEF option 4
//
// Z1_OTP_BOOTPIN_CONFIG is read by boot ROM from address 0x0005F008, but address 0x7800C needs to be written to
// Z1_OTP_BOOTDEF_LOW is read by boot ROM from address 0x0005F00C, but address 0x7801E needs to be written to
// Z1_OTP_BOOTDEF_HIGH is read by boot ROM from address 0x0005F004, but address 0x7801F needs to be written to
//

//
// EMU_BOOTPIN_CONFIG is the emulation equivalent of Z1_OTP_BOOTPIN_CONFIG.
//                              Bits       Name                                 Description
// EMU_BOOTPIN_CONFIG:          31-24      Key                                  Write 0x5A to use emulation custom
//                                                                              boot config. Write 0xA5 to emulate
//                                                                              standalone boot mode. Write any other
//                                                                              value for Wait Boot.
//
//                              23-16      Boot Mode Select Pin 2 (BMSP2)       Set to GPIO to be used during boot
//                              15-8       Boot Mode Select Pin 1 (BMSP1)       Refer to BMSP2
//                              7-0        Boot Mode Select Pin 0 (BMSP0)       Refer to BMSP2
//
// The address of EMU_BOOTPIN_CONFIG is 0xD00
//
#define EMU_BOOTPIN_CONFIG        (uint32_t)0xD00

//
// EMU_BOOTDEF_LOW is the emulation equivalent of Z1_OTP_BOOTDEF_LOW.
//
// EMU_BOOTDEF_LOW:          31-24      BOOTDEF3                             BOOTDEF option 3
//                           23-16      BOOTDEF2                             BOOTDEF option 2
//                           15-8       BOOTDEF1                             BOOTDEF option 1
//                           7-0        BOOTDEF0                             BOOTDEF option 0
//
// The address of EMU_BOOTDEF_LOW is 0xD04
//
#define EMU_BOOTDEF_LOW        (uint32_t)0xD04

//
// EMU_BOOTDEF_HIGH is the emulation equivalent of Z1_OTP_BOOTDEF_HIGH.
//
// EMU_BOOTDEF_HIGH:         31-24      BOOTDEF7                             BOOTDEF option 7
//                           23-16      BOOTDEF6                             BOOTDEF option 6
//                           15-8       BOOTDEF5                             BOOTDEF option 5
//                           7-0        BOOTDEF4                             BOOTDEF option 4
//
// The address of EMU_BOOTDEF_HIGH is 0xD06
//
#define EMU_BOOTDEF_HIGH        (uint32_t)0xD06

//
// BOOTPIN_CONFIG_KEY is the value for the
// bootpin config key that allows for a custom
// boot process to be executed.
//
#define BOOTPIN_CONFIG_KEY        (uint32_t)0x5A

//
// EMU_STANDALONE_KEYVAL is the value for the
// emulation bootpin config key that allows
// the standalone boot process to be executed
// while debugger is connected.
//
#define EMU_STANDALONE_KEYVAL        (uint32_t)0xA5

//
// Boot Mode Definitions
//

//
// Parallel Boot
//
#define PARALLEL_BOOT        (uint32_t)0x00

//
// SCI Boot
// GPIO28; GPIO29 
//
#define SCI_BOOT        (uint32_t)0x01

//
// SCI Boot Alternative
// GPIO16; GPIO17
//
#define SCI_BOOT_ALT1        (uint32_t)0x21

//
// CAN Boot
// GPIO32; GPIO33
//
#define CAN_BOOT        (uint32_t)0x02

//
// Flash Boot
// begin of BANK 0 Sector 0
//
#define FLASH_BOOT        (uint32_t)0x03

//
// Flash Boot Alternative
// begin of BANK 0 Sector 15
//
#define FLASH_BOOT_ALT1        (uint32_t)0x23

//
// Wait Boot
// WDog enabled
//
#define WAIT_BOOT        (uint32_t)0x04

//
// RAM Boot
//
#define RAM_BOOT        (uint32_t)0x05

//
// SPI_MASTER_BOOT
// GPIO16-GPIO19
//
#define SPI_MASTER_BOOT        (uint32_t)0x06

//
// I2C_MASTER_BOOT
// GPIO32, GPIO33
//
#define I2C_MASTER_BOOT        (uint32_t)0x07

//
// BOOTPIN_CONFIG_BMSPDISABLE is the value that
// causes a BMSP to be disabled.
//
#define BOOTPIN_CONFIG_BMSPDISABLE        (uint32_t)0xFF

//
// GPIO definitions
//
#define GPIO2        (uint32_t)2
#define GPIO1        (uint32_t)1
#define GPIO0        (uint32_t)0

//
// BMSP Definitions
//

//
// The following GPIOs cannot be used as a BMSP: GPIO 20 to 23,
// GPIO 36, GPIO 38, GPIO 60 to 223. If set to one of the mentioned
// GPIOs, the factory default for the corresponding BMSP will
// be selected by the boot ROM code. A value of 0xFF can be used
// to disable the corresponding BMSP.
//

//
// BOOTPIN_CONFIG_BMSP2 is the value used for BMSP2 of Bootpin Config.
// Change to value of desired GPIO to be used for BMSP2.
//
#define BOOTPIN_CONFIG_BMSP2        GPIO2

//
// BOOTPIN_CONFIG_BMSP1 is the value used for BMSP1 of Bootpin Config.
// Change to value of desired GPIO to be used for BMSP1.
//
#define BOOTPIN_CONFIG_BMSP1        GPIO1

//
// BOOTPIN_CONFIG_BMSP0 is the value used for BMSP0 of Bootpin Config.
// Change to value of desired GPIO to be used for BMSP0.
//
#define BOOTPIN_CONFIG_BMSP0        GPIO0

//
// BOOTDEF Option Definitions
//

//
// BOOTDEF Option 0
//
#define BOOTDEF_LOW_0        FLASH_BOOT

//
// BOOTDEF Option 1
//
#define BOOTDEF_LOW_1        SCI_BOOT

//
// BOOTDEF Option 2
//
#define BOOTDEF_LOW_2        FLASH_BOOT_ALT1

//
// BOOTDEF Option 3
//
#define BOOTDEF_LOW_3        SCI_BOOT_ALT1

//
// BOOTDEF Option 4
//
#define BOOTDEF_HIGH_4        CAN_BOOT

//
// BOOTDEF Option 5
//
#define BOOTDEF_HIGH_5        SPI_MASTER_BOOT

//
// BOOTDEF Option 6
//
#define BOOTDEF_HIGH_6        RAM_BOOT

//
// BOOTDEF Option 7
//
#define BOOTDEF_HIGH_7        I2C_MASTER_BOOT

//
// Function Prototypes
//
void configBMSPS0(void);
void configBMSPS1(void);
void configBMSPS3(void);

#endif // _BOOT_EX2_CUSTOMBOOTCONFIG_H_

// 
// End of File 
//
