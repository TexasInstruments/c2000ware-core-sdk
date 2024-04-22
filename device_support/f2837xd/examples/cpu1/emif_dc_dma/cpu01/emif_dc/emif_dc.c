//###########################################################################
//
// FILE:   emif_dc.c
//
// TITLE:  EMIF Daughtercard Support Functions and Constants
//
//###########################################################################
//
// $Release Date: $
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
#define EMIF_DC_MODULE_CNT           2 // Number of EMIF modules on device

#define EMIF_DC_EM1_CS2_ADDR ((Uint32)0x00100000) // CS2 base address on EMIF1
#define EMIF_DC_EM2_CS2_ADDR ((Uint32)0x00002000) // CS2 base address on EMIF2

// Pins used for Virtual page should not interfere with SDRAM operation
#define EMIF_DC_EM1_PAGE_SHIFT      14 // Virtual page starts with A[14] on memory
#define EMIF_DC_EM2_PAGE_SHIFT      14 // Virtual page starts with A[14] on memory
#define EMIF_DC_EM2_EM2A12         119 // EM2A12 does not exist so will need to control with GPIO
#define EMIF_DC_EM2_SDCKE          117 // EM2_SDCKE is pinned out on F28377 LaunchPad v1.x instead of EM1_SDCKE

#define EMIF_DC_FLASH_BUSY_DELAY     1 // us delay between Flash Command and Read/Busy# valid

const Uint16 EMIF_DC_CS2_SELECT[EMIF_DC_MODULE_CNT+1]  = {0, 107, 136}; // Analog switch control signal to select between ASRAM or FLASH
const Uint16 EMIF_DC_FLASH_READY[EMIF_DC_MODULE_CNT+1] = {0,  36, 110}; // Flash Ready/Busy# signal
const Uint16 EMIF_DC_FLASH_RESET[EMIF_DC_MODULE_CNT+1] = {0, 108, 137}; // Flash reset control signal

const Uint16 EMIF_DC_EM1_MUX2_PINS[36] = {
         38,  //  EM1A0
         39,  //  EM1A1
         40,  //  EM1A2
         41,  //  EM1A3
         44,  //  EM1A4
         45,  //  EM1A5
         46,  //  EM1A6
         47,  //  EM1A7
         48,  //  EM1A8
         49,  //  EM1A9
         50,  //  EM1A10
         51,  //  EM1A11
         52,  //  EM1A12
         85,  //  EM1D0
         83,  //  EM1D1
         82,  //  EM1D2
         81,  //  EM1D3
         80,  //  EM1D4
         79,  //  EM1D5
         78,  //  EM1D6
         77,  //  EM1D7
         76,  //  EM1D8
         75,  //  EM1D9
         74,  //  EM1D10
         73,  //  EM1D11
         72,  //  EM1D12
         71,  //  EM1D13
         70,  //  EM1D14
         69,  //  EM1D15
         32,  //  EM1CS0
         29,  //  EM1SDCKE
         30,  //  EM1CLK
         31,  //  EM1WE
         37,  //  EM1OE
         34   //  EM1CS2
};

const Uint16 EMIF_DC_EM1_MUX3_PINS[6] = {
         93,  //  EM1BA0
         92,  //  EM1BA1
         86,  //  EM1CAS
         87,  //  EM1RAS
         88,  //  EM1DQM0
         89   //  EM1DQM1
};

#if EMIF_DC_F2837X_LAUNCHPAD_V1
const Uint16 EMIF_DC_EM1_PAGE_PINS[6] = {
        103,  //  GPIO-Controlled EM1A[13]
        102,  //  GPIO-Controlled EM1A[14]
        100,  //  GPIO-Controlled EM1A[15]
        101,  //  GPIO-Controlled EM1A[16]
        106,  //  GPIO-Controlled EM1A[17]
        109   //  GPIO-Controlled EM1A[18]
}; // EM1A[13:18]
#else
const Uint16 EMIF_DC_EM1_PAGE_PINS[6] = {
        103,  //  GPIO-Controlled EM1A[13]
        102,  //  GPIO-Controlled EM1A[14]
        100,  //  GPIO-Controlled EM1A[15]
        101,  //  GPIO-Controlled EM1A[16]
        105,  //  GPIO-Controlled EM1A[17]
        104   //  GPIO-Controlled EM1A[18]
}; // EM1A[13:18]
#endif

const Uint16 EMIF_DC_EM2_MUX2_PINS[0] = {};

const Uint16 EMIF_DC_EM2_MUX3_PINS[41] = {
        111,  //  EM2BA0
        112,  //  EM2BA1
         98,  //  EM2A0
         99,  //  EM2A1
        100,  //  EM2A2
        101,  //  EM2A3
        102,  //  EM2A4
        103,  //  EM2A5
        104,  //  EM2A6
        105,  //  EM2A7
        106,  //  EM2A8
        107,  //  EM2A9
        108,  //  EM2A10
        109,  //  EM2A11
         68,  //  EM2D0
         67,  //  EM2D1
         66,  //  EM2D2
         65,  //  EM2D3
         64,  //  EM2D4
         63,  //  EM2D5
         62,  //  EM2D6
         61,  //  EM2D7
         60,  //  EM2D8
         59,  //  EM2D9
         58,  //  EM2D10
         57,  //  EM2D11
         56,  //  EM2D12
         55,  //  EM2D13
         54,  //  EM2D14
         53,  //  EM2D15
        120,  //  EM2WE
        115,  //  EM2CS0
        117,  //  EM2SDCKE
        118,  //  EM2CLK
        113,  //  EM2CAS
        114,  //  EM2RAS
         97,  //  EM2DQM0
         96,  //  EM2DQM1
        116,  //  EM2CS2
        121   //  EM2OE
};

const Uint16 EMIF_DC_EM2_PAGE_PINS[6] = {
        125,  //  GPIO-Controlled EM2A[13]
        124,  //  GPIO-Controlled EM2A[14]
        122,  //  GPIO-Controlled EM2A[15]
        123,  //  GPIO-Controlled EM2A[16]
         92,  //  GPIO-Controlled EM2A[17]
         91   //  GPIO-Controlled EM2A[18]
}; // EM2A[13:18]

#define EMIF_DC_FLASH_SEQ_ADDR 0
#define EMIF_DC_FLASH_SEQ_DATA 1

const Uint16 EMIF_DC_FLASH_PROG_SEQ[3][2] = {
        {0x555,0xAA},
        {0x2AA,0x55},
        {0X555,0xA0}
};

const Uint16 EMIF_DC_FLASH_CHIP_ERASE_SEQ[6][2] = {
        {0x555,0xAA},
        {0x2AA,0x55},
        {0x555,0x80},
        {0x555,0xAA},
        {0x2AA,0x55},
        {0x555,0x10}
};

const Uint16 EMIF_DC_FLASH_CFI_ENTER_SEQ[1][2] = {
        {0x55,0x98}
};

const Uint16 EMIF_DC_FLASH_CFI_EXIT_SEQ[1][2] = {
        {0x00,0xF0}
};

volatile struct EMIF_REGS *const EMIF_DC_REGS[EMIF_DC_MODULE_CNT+1]  = {0, &Emif1Regs, &Emif2Regs};
Uint16 EMIF_DC_activeCS2Page;

//
// EMIF_DC_setupPinmux - Configure Pinmux specifically for EMIF_DC connections with:
//     TMDSCNCD28379D
//     LAUNCHXL-F28379D
//     LAUNCHXL-F28377S
//
void EMIF_DC_setupPinmux(Uint16 emifModule, Uint16 cpuSel) {
    Uint16 pin;

	if( emifModule == 1 ) {
	    for(pin=0;pin<sizeof(EMIF_DC_EM1_MUX2_PINS);pin++) {
	        GPIO_SetupPinMux(EMIF_DC_EM1_MUX2_PINS[pin],cpuSel,2);
            GPIO_SetupPinOptions(EMIF_DC_EM1_MUX2_PINS[pin],GPIO_INPUT,GPIO_ASYNC);
        }

        for(pin=0;pin<sizeof(EMIF_DC_EM1_MUX3_PINS);pin++) {
            GPIO_SetupPinMux(EMIF_DC_EM1_MUX3_PINS[pin],cpuSel,3);
            GPIO_SetupPinOptions(EMIF_DC_EM1_MUX3_PINS[pin],GPIO_INPUT,GPIO_ASYNC);
        }

        for(pin=0;pin<sizeof(EMIF_DC_EM1_PAGE_PINS);pin++) {
            GPIO_SetupPinMux(EMIF_DC_EM1_PAGE_PINS[pin],cpuSel,0);
            GPIO_SetupPinOptions(EMIF_DC_EM1_PAGE_PINS[pin],GPIO_OUTPUT,GPIO_PULLUP);
        }
	}

	if( emifModule == 2) {
        for(pin=0;pin<sizeof(EMIF_DC_EM2_MUX2_PINS);pin++) {
            GPIO_SetupPinMux(EMIF_DC_EM2_MUX2_PINS[pin],cpuSel,2);
            GPIO_SetupPinOptions(EMIF_DC_EM2_MUX2_PINS[pin],GPIO_INPUT,GPIO_ASYNC);
        }

        for(pin=0;pin<sizeof(EMIF_DC_EM2_MUX3_PINS);pin++) {
            GPIO_SetupPinMux(EMIF_DC_EM2_MUX3_PINS[pin],cpuSel,3);
            GPIO_SetupPinOptions(EMIF_DC_EM2_MUX3_PINS[pin],GPIO_INPUT,GPIO_ASYNC);
        }

        for(pin=0;pin<sizeof(EMIF_DC_EM2_PAGE_PINS);pin++) {
            GPIO_SetupPinMux(EMIF_DC_EM2_PAGE_PINS[pin],cpuSel,0);
            GPIO_SetupPinOptions(EMIF_DC_EM2_PAGE_PINS[pin],GPIO_OUTPUT,GPIO_PULLUP);
        }

        GPIO_SetupPinMux(EMIF_DC_EM2_EM2A12,cpuSel,0);
        GPIO_SetupPinOptions(EMIF_DC_EM2_EM2A12,GPIO_OUTPUT,GPIO_PULLUP);
        GPIO_WritePin(EMIF_DC_EM2_EM2A12,0); // Drive GPIO-Controlled EM2A12 signal low; EM2A12==1 can interfere with SDRAM
	}

	if( EMIF_DC_F2837X_LAUNCHPAD_V1 ) {
	    GPIO_SetupPinMux(EMIF_DC_EM2_SDCKE,cpuSel,0);
        GPIO_SetupPinOptions(EMIF_DC_EM2_SDCKE,GPIO_OUTPUT,GPIO_PULLUP);
        GPIO_WritePin(EMIF_DC_EM2_SDCKE,1); // Drive GPIO-Controlled EM2_SDCKE signal high so that SDRAM CLK is enabled on LaunchPad v1.x
	}

	GPIO_SetupPinMux(EMIF_DC_CS2_SELECT[emifModule],cpuSel,0);
	GPIO_SetupPinOptions(EMIF_DC_CS2_SELECT[emifModule],GPIO_OUTPUT,GPIO_PULLUP);
	GPIO_WritePin(EMIF_DC_CS2_SELECT[emifModule],EMIF_DC_ASRAM);

	GPIO_SetupPinMux(EMIF_DC_FLASH_RESET[emifModule],cpuSel,0);
	GPIO_SetupPinOptions(EMIF_DC_FLASH_RESET[emifModule],GPIO_OUTPUT,GPIO_PULLUP);
	GPIO_WritePin(EMIF_DC_FLASH_RESET[emifModule],1); // Deassert FLASH RESET/

    GPIO_SetupPinMux(EMIF_DC_FLASH_READY[emifModule],cpuSel,0);
    GPIO_SetupPinOptions(EMIF_DC_FLASH_READY[emifModule],GPIO_INPUT,GPIO_PULLUP);
}

//
// EMIF_DC_initModule - Enable EMIF module clock and disable register protection
//
void EMIF_DC_initModule(Uint16 emifModule) {
    EALLOW;

    // Configure EMIF clock to SYSCLK/2 for SDRAM 100MHz max frequency
    if( emifModule == 1 ) {
        CpuSysRegs.PCLKCR1.bit.EMIF1            = 0x1;
        ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;
        Emif1ConfigRegs.EMIF1ACCPROT0.all       = 0x0;
        #if( !defined(_LAUNCHXL_F28377S) && !defined (_LAUNCHXL_F28379D) )
        asm(" ESTOP0"); // _LAUNCHXL_F28377S or _LAUNCHXL_F28379D must be defined for correct InitSysPll() call from InitSysCtrl()
        #endif
    }
    if( emifModule == 2 ) {
        CpuSysRegs.PCLKCR1.bit.EMIF2            = 0x1;
        ClkCfgRegs.PERCLKDIVSEL.bit.EMIF2CLKDIV = 0x1;
        Emif2ConfigRegs.EMIF2ACCPROT0.all       = 0x0;
        #if( defined(_LAUNCHXL_F28377S) || defined(_LAUNCHXL_F28379D) )
        asm(" ESTOP0"); // _LAUNCHXL_F28377S or _LAUNCHXL_F28379D must not be defined for correct InitSysPll() call from InitSysCtrl()
        #endif
    }

    EDIS;
}

//
// EMIF_DC_initCS0 - Configure CS0 to work with SDRAM on EMIF_DC
//
void EMIF_DC_initCS0(Uint16 emifModule) {
    EMIF_DC_REGS[emifModule]->SDRAM_RCR.bit.REFRESH_RATE = 781;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RFC         =   5;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RP          =   1;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RCD         =   1;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_WR          =   1;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RAS         =   4;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RC          =   5;
    EMIF_DC_REGS[emifModule]->SDRAM_TR.bit.T_RRD         =   1;
    EMIF_DC_REGS[emifModule]->SDR_EXT_TMNG.bit.T_XS      =   6;
    EMIF_DC_REGS[emifModule]->SDRAM_CR.all = (1 << 14) | // NM
                                             (2 <<  9) | // CL
                                             (1 <<  8) | // LOCK
                                             (2 <<  4) | // IBANK
                                             (1 <<  0);  // PAGESIZE
}

//
// EMIF_DC_selectCS2Memory - Set analog switch to route CS2 to ASRAM or FLASH
//
void EMIF_DC_selectCS2Memory(Uint16 emifModule, Uint16 CS2Mem) {
    GPIO_WritePin(EMIF_DC_CS2_SELECT[emifModule],CS2Mem);
}

//
// EMIF_DC_initCS2 - Configure CS2 to work with ASRAM or FLASH on EMIF_DC
//
void EMIF_DC_initCS2(Uint16 emifModule, Uint16 CS2Mem) {
    EMIF_DC_selectCS2Memory(emifModule, CS2Mem);
    EMIF_DC_selectCS2Page(emifModule, 0);

    if( CS2Mem == EMIF_DC_ASRAM ) {
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.SS       = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.EW       = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_SETUP  = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_STROBE = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_HOLD   = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_SETUP  = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_STROBE = 2;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_HOLD   = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.TA       = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.ASIZE    = 1;
    }

    if( CS2Mem == EMIF_DC_FLASH ) {
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.SS       = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.EW       = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_SETUP  = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_STROBE = 4;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.W_HOLD   = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_SETUP  = 3;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_STROBE = 5;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.R_HOLD   = 0;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.TA       = 2;
        EMIF_DC_REGS[emifModule]->ASYNC_CS2_CR.bit.ASIZE    = 1;
    }
}

//
// EMIF_DC_selectCS2Page - Select virtual page using GPIO. Upper address
//                         signals are not routed to the EMIF header on
//                         controlCARD and LaunchPad so GPIO must be used
//                         instead of the native address signals.
//
void EMIF_DC_selectCS2Page(Uint16 emifModule, Uint16 page) {
    Uint16 pin;

    if( emifModule == 1 ) {
        for(pin=0;pin<sizeof(EMIF_DC_EM1_PAGE_PINS);pin++) {
            GPIO_WritePin(EMIF_DC_EM1_PAGE_PINS[pin], (page & (0x1<<pin)) != 0);
        }
    }
    if( emifModule == 2 ) {
        for(pin=0;pin<sizeof(EMIF_DC_EM2_PAGE_PINS);pin++) {
            GPIO_WritePin(EMIF_DC_EM2_PAGE_PINS[pin], (page & (0x1<<pin)) != 0);
        }
    }
    EMIF_DC_activeCS2Page = page;
}

//
// EMIF_DC_programCS2Flash - Program single 16b word to Flash address
//
void EMIF_DC_programCS2Flash(Uint16 emifModule, Uint32 addr, Uint16 data) {
    Uint16 cmdNum;
    Uint32 CS2Addr;
    Uint16 restorePage;

    restorePage = EMIF_DC_activeCS2Page;

    EMIF_DC_selectCS2Page(emifModule, 0);

    if( emifModule == 1 ) {
        CS2Addr = EMIF_DC_EM1_CS2_ADDR;
    }
    if( emifModule == 2 ) {
        CS2Addr = EMIF_DC_EM2_CS2_ADDR;
    }

    for(cmdNum=0;cmdNum<sizeof(EMIF_DC_FLASH_PROG_SEQ)/2;cmdNum++) {
        *(Uint16*)(CS2Addr + EMIF_DC_FLASH_PROG_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_ADDR]) = EMIF_DC_FLASH_PROG_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_DATA];
    }

    if( restorePage != EMIF_DC_activeCS2Page ) {
        EMIF_DC_selectCS2Page(emifModule, restorePage);
    }

    *(Uint16*)addr = data;

    F28x_usDelay(EMIF_DC_FLASH_BUSY_DELAY); // Wait for Ready/Busy# signal to become valid

    while( GPIO_ReadPin(EMIF_DC_FLASH_READY[emifModule]) == 0 ); // Wait for Flash to complete command
}

//
// EMIF_DC_eraseCS2Flash - Erase entire Flash memory space
//
void EMIF_DC_eraseCS2Flash(Uint16 emifModule) {
    Uint16 cmdNum;
    Uint32 CS2Addr;
    Uint16 restorePage;

    restorePage = EMIF_DC_activeCS2Page;

    EMIF_DC_selectCS2Page(emifModule, 0);

    if( emifModule == 1 ) {
        CS2Addr = EMIF_DC_EM1_CS2_ADDR;
    }
    if( emifModule == 2 ) {
        CS2Addr = EMIF_DC_EM2_CS2_ADDR;
    }

    for(cmdNum=0;cmdNum<sizeof(EMIF_DC_FLASH_CHIP_ERASE_SEQ)/2;cmdNum++) {
        *(Uint16*)(CS2Addr + EMIF_DC_FLASH_CHIP_ERASE_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_ADDR]) = EMIF_DC_FLASH_CHIP_ERASE_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_DATA];
    }

    F28x_usDelay(EMIF_DC_FLASH_BUSY_DELAY); // Wait for Ready/Busy# signal to become valid

    while( GPIO_ReadPin(EMIF_DC_FLASH_READY[emifModule]) == 0 ); // Wait for Flash to complete command

    if( restorePage != EMIF_DC_activeCS2Page ) {
        EMIF_DC_selectCS2Page(emifModule, restorePage);
    }
}

//
// EMIF_DC_enterCS2FlashCFI - Enter Flash CFI mode to access device information
//
void EMIF_DC_enterCS2FlashCFI(Uint16 emifModule) {
    Uint16 cmdNum;
    Uint32 CS2Addr;
    Uint16 restorePage;

    restorePage = EMIF_DC_activeCS2Page;

    EMIF_DC_selectCS2Page(emifModule, 0);

    if( emifModule == 1 ) {
        CS2Addr = EMIF_DC_EM1_CS2_ADDR;
    }
    if( emifModule == 2 ) {
        CS2Addr = EMIF_DC_EM2_CS2_ADDR;
    }

    for(cmdNum=0;cmdNum<sizeof(EMIF_DC_FLASH_CFI_ENTER_SEQ)/2;cmdNum++) {
        *(Uint16*)(CS2Addr + EMIF_DC_FLASH_CFI_ENTER_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_ADDR]) = EMIF_DC_FLASH_CFI_ENTER_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_DATA];
    }

    if( restorePage != EMIF_DC_activeCS2Page ) {
        EMIF_DC_selectCS2Page(emifModule, restorePage);
    }
}

//
// EMIF_DC_exitCS2FlashCFI - Exit Flash CFI mode for normal operation
//
void EMIF_DC_exitCS2FlashCFI(Uint16 emifModule) {
    Uint16 cmdNum;
    Uint32 CS2Addr;
    Uint16 restorePage;

    restorePage = EMIF_DC_activeCS2Page;

    EMIF_DC_selectCS2Page(emifModule, 0);

    if( emifModule == 1 ) {
        CS2Addr = EMIF_DC_EM1_CS2_ADDR;
    }
    if( emifModule == 2 ) {
        CS2Addr = EMIF_DC_EM2_CS2_ADDR;
    }

    for(cmdNum=0;cmdNum<sizeof(EMIF_DC_FLASH_CFI_EXIT_SEQ)/2;cmdNum++) {
        *(Uint16*)(CS2Addr + EMIF_DC_FLASH_CFI_EXIT_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_ADDR]) = EMIF_DC_FLASH_CFI_EXIT_SEQ[cmdNum][EMIF_DC_FLASH_SEQ_DATA];
    }

    if( restorePage != EMIF_DC_activeCS2Page ) {
        EMIF_DC_selectCS2Page(emifModule, restorePage);
    }
}

