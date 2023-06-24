//###########################################################################
//
// FILE:   cpu1bootrom.h
//
// TITLE:  BootROM Definitions.
//
//###########################################################################
// $TI Release: F280013x Support Library v4.03.00.00 $
// $Release Date: 02-02-2023 $
// $Copyright:
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.co/
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



#ifndef C_BOOTROM_H_
#define C_BOOTROM_H_

#include <stdint.h>
#include "hw_types.h"
#include "hw_memmap.h"
#include "sysctl.h"
#include "cpu.h"
//#include "flash.h"
//#include "hw_flash_command.h"
#include "hw_dcsm.h"
#include "pin_map.h"
#include "gpio.h"
#include "spi.h"
#include "dcc.h"
//#include "cpu1brom_boot_modes.h"
//#include "cpu1brom_escape_point_table.h"
//#include "cpu1brom_pbist.h"
//#include "hw_memcfg.h"
//#include "cpu1brom_trims.h"
//#include "bootloader_can.h"
//#include "bootloader_i2c.h"
//#include "bootloader_parallel.h"
//#include "bootloader_sci.h"
//#include "bootloader_spi.h"

//
//Start Address of Boot ROM
//
#define ROM_START_ADDRESS               0x3F9800UL

//
//Length of ROM in KB
//
#define ROM_REGION_LENGTH               64UL

#define RAM_LSX_NOT_DONE                0x0U
#define BROM_PLL_CONFIG_ERROR           0xFFFFU
#define BROM_PLL_CONFIG_SUCCESS         0x0U

#define EFUSE_SINGLE_BIT_ERROR          (0x15UL)

//
// Flash Configurations
//

#define CPU1_FLASH_15MHZ_RWAIT           (0x3UL)
#define CPU1_FLASH_DEFAULT_RWAIT         (0xFUL)
#define CPU1_FLASH_15MHZ_TRIMENGRRWAIT   (0x4UL)
#define CPU1_FLASH_DEFAULT_TRIMENGRRWAIT (0xFUL)


//When the ROM is run with an emulator connected, these four addresses are used
//to emulate OTP configuration.
#define EMU_BOOTPIN_CONFIG  0xD00    //Equivalent to GPREG1
#define EMU_BOOT_GPREG2     0xD02    //Equivalent to GPREG2
#define EMU_BOOTDEF_LOW     0xD04    //Equivalent to GPREG3
#define EMU_BOOTDEF_HIGH    0xD06    //Equivalent to BOOTCTRL

//Emulation boot pin configuration fields. Currently, only EMU_BOOTPIN_CONFIG_KEY
//is used.
#define EMU_BOOTPIN_CONFIG_KEY      ((HWREG(EMU_BOOTPIN_CONFIG) & (uint32_t)0xFF000000UL) >> 24)

#define EMU_BOOTDEF_L(x)            ((HWREG(EMU_BOOTDEF_LOW)  & ((uint32_t)0xFFU << (8U*x))) >> (8U*x))
#define EMU_BOOTDEF_H(x)            ((HWREG(EMU_BOOTDEF_HIGH) & ((uint32_t)0xFFU << (8U*x))) >> (8U*x))

//
// Standalone Boot Defines
//

//
// DCSM OTP Boot Configuration Registers
//
#define Z1_OTP_BOOTPIN_CONFIG           (DCSM_Z1_BASE + (uint32_t)DCSM_O_Z1_GPREG1)
#define Z1_OTP_BOOT_GPREG2              (DCSM_Z1_BASE + (uint32_t)DCSM_O_Z1_GPREG2)
#define Z1_OTP_BOOTDEF_LOW              (DCSM_Z1_BASE + (uint32_t)DCSM_O_Z1_GPREG3)
#define Z1_OTP_BOOTDEF_HIGH             (DCSM_Z1_BASE + (uint32_t)DCSM_O_Z1_GPREG4)
#define Z2_OTP_BOOTPIN_CONFIG           (DCSM_Z2_BASE + (uint32_t)DCSM_O_Z2_GPREG1)
#define Z2_OTP_BOOT_GPREG2              (DCSM_Z2_BASE + (uint32_t)DCSM_O_Z2_GPREG2)
#define Z2_OTP_BOOTDEF_LOW              (DCSM_Z2_BASE + (uint32_t)DCSM_O_Z2_GPREG3)
#define Z2_OTP_BOOTDEF_HIGH             (DCSM_Z2_BASE + (uint32_t)DCSM_O_Z2_GPREG4)

//
//DCSM Z1 CSM Key Mask Values
//

#define DCSM_Z1_CSMKEY0_MASK            0xFFFFFFFFUL
#define DCSM_Z1_CSMKEY1_MASK            0xFFFFFFFFUL
#define DCSM_Z1_CSMKEY2_MASK            0xFFFFFFFFUL
#define DCSM_Z1_CSMKEY3_MASK            0xFFFFFFFFUL

//
//DCSM Z2 CSM Key Mask Values
//

#define DCSM_Z2_CSMKEY0_MASK            0xFFFFFFFFUL
#define DCSM_Z2_CSMKEY1_MASK            0xFFFFFFFFUL
#define DCSM_Z2_CSMKEY2_MASK            0xFFFFFFFFUL
#define DCSM_Z2_CSMKEY3_MASK            0xFFFFFFFFUL


/*
Z1-GPREG2[31:24] => VALIDITY_KEY (=0x5A);
Z1-GPREG2[23:8] => RESERVED; no usage defined yet.
Z1-GPREG2[7:6] => 00 - Run PBIST with PLL disabled (10MHz internal oscillator)
                       (includes CRC test on 64KB unsecure ROM)
                  01 - Run PBIST at 115MHz
                  10 - Run PBIST at 57.5MHz
                  11 - Do not run PBIST
Z1-GPREG2[5:4] => ERROR_STS_PIN config; this tells which GPIO pin is supposed to be used as ERROR_PIN and boot ROM configures the mux as such for the said pin.
                0 - GPIO24, MUX Option 13
                1 - GPIO28, MUX Option 13
                2 - GPIO29, MUX Option 13
                3 - ERROR_STS function Disable  (default)

Z1-GPREG2[3:0]  =>  CJTAGNODEID[3:0];
                boot ROM takes this values and programs the lower 4 bits of the CJTAGNODEID register.
*/

#define HWREAD_Z1_OTP_BOOT_GPREG2_KEY            ((HWREG(Z1_OTP_BOOT_GPREG2) & (uint32_t)0xFF000000UL) >> 24U)
#define HWREAD_Z2_OTP_BOOT_GPREG2_KEY            ((HWREG(Z2_OTP_BOOT_GPREG2) & (uint32_t)0xFF000000UL) >> 24U)

#define ERRORSTS_OTP_VALUE_Z1              ((HWREG(Z1_OTP_BOOT_GPREG2) & (uint32_t)0x00000030UL) >> 4U)
#define ERRORSTS_OTP_VALUE_Z2              ((HWREG(Z2_OTP_BOOT_GPREG2) & (uint32_t)0x00000030UL) >> 4U)
#define ERRORSTS_PIN_NUMBER_1              24UL
#define ERRORSTS_PIN_NUMBER_2              28UL
#define ERRORSTS_PIN_NUMBER_3              29UL
#define ERRORSTS_PIN_NUMBER_INVALID        0xFFFFFFFFUL

#define ERRORSTS_PIN_24                    0x0UL
#define ERRORSTS_PIN_28                    0x1UL
#define ERRORSTS_PIN_29                    0x2UL

#define GPREG2_KEY                         0x5AU

#define GPREG2_PBIST_RUN_PLL_BYPASS        0x0UL
#define GPREG2_PBIST_RUN_SYSCLK_95MHZ      0x1UL
#define GPREG2_PBIST_RUN_SYSCLK_47_5MHZ    0x2UL
#define GPREG2_PBIST_DISABLED              0x3UL

#define PBIST_CHECKSUM_SUCCESS             0x0U

//
// Get key to validate Z1 OTP BOOTPIN_CONFIG
//
#define HWREAD_Z1_OTP_BOOTPIN_CONFIG_KEY        ((HWREG(Z1_OTP_BOOTPIN_CONFIG) & (uint32_t)0xFF000000UL) >> 24U)
#define HWREAD_Z2_OTP_BOOTPIN_CONFIG_KEY        ((HWREG(Z2_OTP_BOOTPIN_CONFIG) & (uint32_t)0xFF000000UL) >> 24U)

//
// Standalone macros to extract boot definition from BOOTDEF table at
// specified index
//
#define HWREAD_Z1_OTP_BOOTDEF_L(x)             ((HWREG(Z1_OTP_BOOTDEF_LOW)  & ((uint32_t)0xFFUL << (8UL*(x)))) >> (8UL*(x)))
#define HWREAD_Z1_OTP_BOOTDEF_H(x)             ((HWREG(Z1_OTP_BOOTDEF_HIGH) & ((uint32_t)0xFFUL << (8UL*(x)))) >> (8UL*(x)))
#define HWREAD_Z2_OTP_BOOTDEF_L(x)             ((HWREG(Z2_OTP_BOOTDEF_LOW)  & ((uint32_t)0xFFUL << (8UL*(x)))) >> (8UL*(x)))
#define HWREAD_Z2_OTP_BOOTDEF_H(x)             ((HWREG(Z2_OTP_BOOTDEF_HIGH) & ((uint32_t)0xFFUL << (8UL*(x)))) >> (8UL*(x)))

#define FACTORY_DEFAULT_BMSP0       32      //GPIO32
#define FACTORY_DEFAULT_BMSP1       24      //GPIO24


#define HWREAD_FLASH_ENTRY_POINT_OVERRIDE_KEY  (HWREG(0x711D2UL))
#define HWREAD_FLASH_ENTRY_POINT_OVERRIDE_ADDR (HWREG(0x711D4UL))

//---------------------------------------------------------------------------
// Device Configuration
//
#define HWREAD_TI_OTP_PARTID_L          (HWREG(0x711C2UL))
#define HWREAD_TI_OTP_PARTID_H          (HWREG(0x711C4UL))

#define TI_OTP_ADDR_DC11                (0x711C7UL)
#define TI_OTP_ADDR_DC31                (0x711C8UL)

#define TI_OTP_ADDR_CPUROM_DC1          (0x711D6UL)
#define TI_OTP_ADDR_CPUROM_DC2          (0x711D7UL)

#define BROM_DCX_ENABLE_HIGH            0xFFFF0000UL

#define HWREAD_TI_OTP_PKG_TYPE          (HWREGH(0x711C6UL))
#define PKG_TYPE_KEY                    0x5AU
#define PKG_TPYE_32_QFN                 0xCUL
#define TI_OTP_ANAREFCTL_ADDR           (0x711CBUL)

#define TI_OTP_ADDR_PERCNF1             (0x711C9UL)
#define TI_OTP_ADDR_PERCNF2             (0x711CAUL)
#define PERCNF1_MASK                    0x10U
#define PERCNF2_MASK                    0x3U

#define TI_OTP_REG_VREGCTL_ENMASK       (HWREGH(0x711E6UL))
#define BROM_ANALOG_SYSCTL_O_VREGCTL    0x006AU
#define VREGCTL_ENMASK_KEY              0x5AU

//bits15:8 is the KEY ; if Value == 0x5A then the remaining bits are valid
//bits 7:2 => reserved
//bits 0:1 if set to b'00 BROM will program 0x01 in VREGCTL.ENMASK
//          - any other value the VREGCTL.ENMASK will be left at reset state.

#define TI_OTP_REG_VREGCTL_ENMASK_VAL   ((TI_OTP_REG_VREGCTL_ENMASK) & 0x03U)

#define TI_OTP_REG_VREGCTL_ENMASK_KEY   (((TI_OTP_REG_VREGCTL_ENMASK) & 0xFF00U) >> 0x8U)

//Bits [1:0]    If 01, enable the PLL, otherwise leave it disabled
//Bits [7:2]    PLL divider to use when the PLL is enabled
//Bits [31:24]  If 0x5A, use this configuration word, otherwise use the default settings
#define OTP_BOOT_CONFIGURE_WORD_ADDRESS      0x711E0UL
#define BOOT_CONFIGURE_ENABLE_PLL            0x1U
//Bit 23 is used for enabling watchdog monitoring during boot time
//if the bit is 1 then it means the watchdog monitoring is enabled
#define BOOT_CONFIG_ENABLE_WD_S         23U
#define OTP_BOOT_CONFIG_M               0x000000FCUL
#define OTP_BOOT_CONFIG_S               0x2U

#define BOOTPIN_CONFIG_STANDALONE_KEY   0xA5U
#define BOOTPIN_CONFIG_KEY              0x5AUL

#define BOOTPIN_COFIG_KEY_MASK          0xFF000000UL
#define BOOTPIN_COFIG_KEY_START         24U

#define APLL_MULT_38                    38UL
#define APLL_DIV_2                      1UL

#define SYSCLK_DIV_1                    0U
#define SYSCLK_DIV_2                    1U
#define SYSCLK_DIV_4                    2U

//
// Boot Selection Defines
//
#define CPU1_ALL_BMSP_DISABLED_MASK             0x00FFFFFFUL
#define CPU1_PIN_CONFIG_MASK                    0xFFU
#define CPU1_BMSP_DISABLED                      0xFFU

//
// OTP Keys
//
#define TI_OTP_KEY                              0x5A5AU
#define TI_OTP_KEY_32B                          0x5A5A5A5AUL

//
// SIMRESET Key
//
#define SIMRESET_KEY                            0xA5A5UL

//
// DFT Keys
//
#define DFT_BOOT_DMLED_KEY                      0xAA55AA55UL
#define DFT_BOOT_TEST_ALT_KEY                   0x55AA55AAUL

//
// GPIO Pullup Config
//
#define HWREAD_TI_OTP_GPXPUD_KEY                (HWREG(0x711CCUL))
#define HWREAD_TI_OTP_GPA_PUD_CONFIG            (HWREG(0x711CEUL))
#define HWREAD_TI_OTP_GPB_PUD_CONFIG            (HWREG(0x711D0UL))

//
//Masks for writes to GPA and GPB registers
//to pull up unbonded pins
//
#define GPA_WRITE_MASK                          0xFFFFFFFFUL
#define GPB_WRITE_MASK                          0xFFFFFFFFUL

//
// DCSM Offset Defines
//
#define DCSM_O_Zx_EXEONLYRAM        0x0UL
#define DCSM_O_Zx_EXEONLYSECT       0x2UL
#define DCSM_O_Zx_GRABRAM           0x4UL
#define DCSM_O_Zx_GRABSECT          0x6UL

//
// CPU1 Boot ROM Status Bit Fields
//
#define CPU1_BOOTROM_BOOTSTS_BOOT_MASK              0x000000FFUL

//
// CPU1 Boot mode status bit field starts from 0 and ends at 7
// It can take any values in the range 0 to 0xFF
//
#define CPU1_BOOTROM_BOOTSTS_SYSTEM_START_BOOT          0x00000001UL  //Set during the initialization phase of the boot ROM
#define CPU1_BOOTROM_BOOTSTS_IN_FLASH_BOOT              0x00000002UL
#define CPU1_BOOTROM_BOOTSTS_IN_SECURE_FLASH_BOOT       0x00000003UL
#define CPU1_BOOTROM_BOOTSTS_IN_PARALLEL_BOOT           0x00000004UL
#define CPU1_BOOTROM_BOOTSTS_IN_RAM_BOOT                0x00000005UL
#define CPU1_BOOTROM_BOOTSTS_IN_SCI_BOOT                0x00000006UL
#define CPU1_BOOTROM_BOOTSTS_IN_SPI_BOOT                0x00000007UL
#define CPU1_BOOTROM_BOOTSTS_IN_I2C_BOOT                0x00000008UL
#define CPU1_BOOTROM_BOOTSTS_IN_CAN_BOOT                0x00000009UL
#define CPU1_BOOTROM_BOOTSTS_IN_WAIT_BOOT               0x0000000BUL

#define CPU1_BOOTROM_RAM_INIT_COMPLETE                  0x00000100UL
#define CPU1_BOOTROM_DCSM_INIT_COMPLETE                 0x00000200UL
#define CPU1_BOOTROM_POR_MEM_TEST_COMPLETE              0x00000400UL
#define CPU1_BOOTROM_RESC_HANDLED                       0x00000800UL
#define CPU1_BOOTROM_HANDLED_XRSN                       0x00001000UL
#define CPU1_BOOTROM_HANDLED_POR                        0x00002000UL
#define CPU1_BOOTROM_WATCHDOG_SELFTEST_FAIL             0x00004000UL
#define CPU1_BOOTROM_BOOT_COMPLETE                      0x00008000UL

#define CPU1_BOOTROM_GOT_ITRAP                          0x00010000UL
#define CPU1_BOOTROM_GOT_A_PIE_MISMATCH                 0x00020000UL
#define CPU1_BOOTROM_GOT_AN_ERAD_NMI                    0x00040000UL
#define CPU1_BOOTROM_GOT_A_RL_NMI                       0x00080000UL
#define CPU1_BOOTROM_GOT_A_MEM_UNCERR_NMI               0x00100000UL
#define CPU1_BOOTROM_GOT_A_MCLK_NMI                     0x00400000UL

#define BOOTROM_PLL_ENABLE_SUCCESS                      0x01000000UL
#define CPU1_BOOTROM_DCSM_INIT_INVALID_LP               0x02000000UL
#define CPU1_BOOTROM_DCSM_INIT_LP_ERROR_SET             0x04000000UL
#define CPU1_BOOTROM_FLASH_VERIFICATION_ERROR           0x08000000UL
#define CPU1_BOOTROM_RAM_INIT_ERROR                     0x10000000UL
#define CPU1_BOOTROM_TRIM_LOAD_ERROR                    0x20000000UL
#define CPU1_BOOTROM_FLASH_2T_NOT_READY                 0x40000000UL

#define BROM_FLASH_ALL_START        0x80000UL
#define BROM_FLASH_ALL_END          0xA0000UL

//
//Mask for NMI enable bit (bit 0)
//
#define NMI_ENABLE_MASK             0x1U

//
// Lower word mask
//
#define WORD_MASK                  0xFFFFU

#ifndef LDRA_FILEIO
//
// Watchdog prescaler and prediv values
//
//
// setting prescale and prediv values to get timeout of 209.6 ms
//
#define WD_PRESCALE_VALUE SYSCTL_WD_PRESCALE_8
#define WD_PREDIV_VALUE   SYSCTL_WD_PREDIV_1024
#else
#define WD_PRESCALE_VALUE SYSCTL_WD_PRESCALE_16
#define WD_PREDIV_VALUE   SYSCTL_WD_PREDIV_2048
#endif

//
// the reset values of prescalar and prediv
//
#define WD_DEF_PRESCALE_VALUE SYSCTL_WD_PRESCALE_1
#define WD_DEF_PREDIV_VALUE   SYSCTL_WD_PREDIV_512

#ifndef LDRA_FILEIO
//
// min values of prediv and prescale values so as to ensure maximum speed for watchdog clk
//
#define WD_PRESCALE_VALUE_MIN SYSCTL_WD_PRESCALE_1
#define WD_PREDIV_VALUE_MIN   SYSCTL_WD_PREDIV_2
#else
//
// min values of prediv and prescale values so as to ensure maximum speed for watchdog clk
//
#define WD_PRESCALE_VALUE_MIN SYSCTL_WD_PRESCALE_8
#define WD_PREDIV_VALUE_MIN   SYSCTL_WD_PREDIV_512
#endif

//
// Function prototypes
//
extern void cbrom_configure_flash(void);
extern uint32_t Gather_Bx_Zx_ZSB(uint16_t bank, uint16_t zone, uint32_t *csmkey);

extern interrupt void CPU1BROM_itrapISR(void);
extern interrupt void CPU1BROM_nmiHandler(void);

extern uint32_t I2C_Boot(uint32_t  bootMode);
extern uint32_t SCI_Boot(uint32_t  bootMode);
extern uint32_t SPI_Boot(uint32_t  bootMode);
uint32_t DCAN_Boot(uint32_t bootMode, uint32_t bitTimingRegValue, uint16_t switchToXTAL);
extern uint32_t SPI_Alternate_IO_Boot(void);
extern uint32_t Parallel_Boot(uint32_t  BootMode);

extern uint32_t CPU1BROM_selectBootMode(void);

extern void CPU1BROM_triggerSysPLLLock(uint32_t multiplier, uint32_t divider);
extern uint16_t CPU1BROM_switchToPLL(uint32_t bootConfig);
extern uint32_t PBIST_PORMemoryTest(void);
extern void CPU1BROM_devcalInit(void);
extern void CPU1BROM_configureHardwarePatching(uint32_t startAddress);

#endif //C_BOOTROM_H_
