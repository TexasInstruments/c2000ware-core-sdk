//###########################################################################
//
// FILE:   emif1_32bit_sdram.c
//
// TITLE:  EMIF1 module accessing 32bit SDRAM.
//
//! \addtogroup cpu01_example_list
//! <h1> EMIF1 SDRAM Module (emif1_32bit_sdram)</h1>
//!
//! This example configures EMIF1 in 32bit SDRAM mode.
//! This example uses CS0 (SDRAM) as chip enable.
//!
//! \b Watch \b Variables: \n
//! - \b TEST_STATUS - Equivalent to \b TEST_PASS if test finished correctly,
//!                    else the value is set to \b TEST_FAIL
//! - \b ErrCount - Error counter
//!
//
//
//###########################################################################
//
// $Release Date:  $
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

//
// Defines
//
#define TEST_PASS             0xABCDABCD
#define TEST_FAIL             0xDEADDEAD
#define SDRAM_CS0_START_ADDR  0x80000000
#define SDRAM_CS0_SIZE        0x300000

//
// Globals
//
Uint16  ErrCount = 0;
Uint32  TEST_STATUS;
int i;

//
// Function Prototypes
//
extern void setup_emif1_pinmux_sdram_32bit(Uint16);

//
// sdram_data_walk - This function performs a walking 0 & 1 For SDRAM RD & WR
//
char
sdram_data_walk(Uint32 start_addr, Uint32 mem_size)
{
    Uint32  XM_p, XMEM_p;
    unsigned long sdram_rdl;
    unsigned long sdram_wdl;
    int i;
    int k;
    int m;

    XM_p = start_addr;

    for (i=0; i < mem_size; i=i+64)
    {
        for (m=0; m < 2; m++)
        {
            XMEM_p = XM_p;

            //
            //Write loop
            //
            sdram_wdl = 0x0001;
            for (k=0; k < 32; k++)
            {
                  if(m==0)
                  {
                      __addr32_write_uint32(XMEM_p, sdram_wdl);
                  }
                  else
                  {
                      __addr32_write_uint32(XMEM_p, ~sdram_wdl);
                  }
                  XMEM_p = XMEM_p+2;
                 sdram_wdl   = sdram_wdl<<1;
            }

            //
            //Read loop
            //
            XMEM_p = XM_p;
            sdram_wdl = 0x0001;
            for (k=0; k < 32; k++)
            {
                sdram_rdl =  __addr32_read_uint32(XMEM_p);
                if(m==1)
                {
                    sdram_rdl = ~sdram_rdl;
                }
                if(sdram_rdl != sdram_wdl)
                {
                    return(1);
                }

                XMEM_p = XMEM_p+2;
                sdram_wdl=sdram_wdl<<1;
            }
        }
        XM_p = XMEM_p;
    }
    return(0);
}

//
// sdram_addr_walk - This function performs a toggle on each address bit.
//                   In this case memory assumed is 4Mb.
//                   MA = BA[1:0]ROW[11:0]COL[7:0]
//
char
sdram_addr_walk(Uint32 start_addr, Uint32 addr_size)
{
    Uint32  XMEM_p;
    unsigned long sdram_rdl;
    unsigned long sdram_wdl;
    int i;
    unsigned long xshift;
    unsigned long xshift2;

    //
    //Write loop
    //
    xshift = 0x00000001;
    sdram_wdl = 0x5678abcd;
    for (i=0; i < addr_size; i++)
    {
        xshift2 = ((xshift+1)<<1);
        XMEM_p =  start_addr + xshift2;
        __addr32_write_uint32(XMEM_p, sdram_wdl);
        sdram_wdl = sdram_wdl+0x11111111;
        xshift   = xshift<<1;
    }

   //
   //Read loop
   //
   xshift = 0x00000001;
   sdram_wdl = 0x5678abcd;
   for (i=0; i < addr_size; i++)
   {
       xshift2 = ((xshift+1)<<1);
       XMEM_p= start_addr + xshift2;
       sdram_rdl = __addr32_read_uint32(XMEM_p);
      if( sdram_rdl != sdram_wdl)
      {
          return(1);
      }
      xshift   = xshift<<1;
      sdram_wdl = sdram_wdl + 0x11111111;
   }
   return(0);
}

//
// sdram_data_size - This function performs different data type
//                  (HALFWORD/WORD) access.
//
char
sdram_data_size(Uint32 start_addr, Uint32 mem_size)
{
    unsigned short sdram_rds;
    unsigned long  sdram_rdl;
    unsigned short sdram_wds;
    unsigned long  sdram_wdl;
    int i;
    Uint32 XMEM_p;

    //
    //Write data short
    //
    XMEM_p = start_addr;
    sdram_wds = 0x0605;
    for (i=0; i < 2; i++)
    {
        __addr32_write_uint16(XMEM_p, sdram_wds);
        XMEM_p++;
        sdram_wds += 0x0202;
    }

    //
    //Write data long
    //
    sdram_wdl = 0x0C0B0A09;
    for (i=0; i < 2; i++)
    {
        __addr32_write_uint32(XMEM_p, sdram_wdl);
        XMEM_p = XMEM_p+2;
        sdram_wdl += 0x04040404;
    }

    //
    //Read data short
    //
    XMEM_p = start_addr;
    sdram_wds=0x0605;
    for (i=0; i < 6; i++)
    {
        sdram_rds = __addr32_read_uint16(XMEM_p);
        if( sdram_rds != sdram_wds)
        {
            return(1);
        }
        XMEM_p++;
        sdram_wds += 0x0202;
    }

    //
    //Read data long
    //
    XMEM_p = start_addr;
    sdram_wdl=0x08070605;
    for (i=0; i < 3; i++)
    {
        sdram_rdl = __addr32_read_uint32(XMEM_p);
        if( sdram_rdl != sdram_wdl)
        {
            return(1);
        }
        XMEM_p = XMEM_p+2;
        sdram_wdl += 0x04040404;
    }
    return(0);
}

//
// sdram_read_write - This function performs simple read/write accesses
//                    to memory.
//
char
sdram_read_write(Uint32 start_addr, Uint32 mem_size)
{
    unsigned long mem_rdl;
    unsigned long mem_wdl;
    Uint32 XMEM_p;
    Uint32 i;

    //
    //Write data
    //
    XMEM_p = start_addr;

    //
    //Fill memory
    //
    mem_wdl = 0x01234567;
    for (i=0; i < mem_size; i++)
    {
        __addr32_write_uint32(XMEM_p, mem_wdl);
        XMEM_p = XMEM_p+2;
        mem_wdl += 0x11111111;
    }

    //
    //Verify memory
    //
    mem_wdl = 0x01234567;
    XMEM_p = start_addr;
    for (i=0; i < mem_size; i++)
    {
        mem_rdl = __addr32_read_uint32(XMEM_p);
        if( mem_rdl != mem_wdl)
        {
            return(1);
        }
        XMEM_p = XMEM_p+2;
        mem_wdl += 0x11111111;
    }
    return(0);
}

//
// Main
//
void main(void)
{
    char ErrCount_local;
    TEST_STATUS = TEST_FAIL;

    //
    // Initialize the device system and clocks
    //
    InitSysCtrl();

    DINT;

    //
    //  Initialize the PIE control registers to their default state.
    //  The default state is all PIE interrupts disabled and flags
    //  are cleared.
    //  This function is found in the F2837xD_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    EALLOW;
    IER = 0x0000;
    IFR = 0x0000;
    EDIS;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // GService Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2837xD_DefaultIsr.c.
    // This function is found in F2837xD_PieVect.c.
    //
    InitPieVectTable();

    //
    //Configure to run EMIF1 on half Rate (EMIF1CLK = CPU1SYSCLK/2)
    //
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;
    EDIS;

    EALLOW;
    //
    // Grab EMIF1 For CPU1
    //
    Emif1ConfigRegs.EMIF1MSEL.all = 0x93A5CE71;
    if(Emif1ConfigRegs.EMIF1MSEL.all != 0x1)
    {
        ErrCount++;
    }

    //
    //Disable Access Protection (CPU_FETCH/CPU_WR/DMA_WR)
    //
    Emif1ConfigRegs.EMIF1ACCPROT0.all = 0x0;
    if(Emif1ConfigRegs.EMIF1ACCPROT0.all != 0x0)
    {
        ErrCount++;
    }

    //
    // Commit the configuration related to protection. Till this bit remains
    // set content of EMIF1ACCPROT0 register can't be changed.
    //
    Emif1ConfigRegs.EMIF1COMMIT.all = 0x1;
    if(Emif1ConfigRegs.EMIF1COMMIT.all != 0x1)
    {
        ErrCount++;
    }

    //
    // Lock the configuration so that EMIF1COMMIT register can't be changed
    // any more.
    //
    Emif1ConfigRegs.EMIF1LOCK.all = 0x1;
    if(Emif1ConfigRegs.EMIF1LOCK.all != 1)
    {
        ErrCount++;
    }

    EDIS;

    //
    //Configure GPIO pins for EMIF1
    //
    setup_emif1_pinmux_sdram_32bit(0);

    //
    //Configure SDRAM control registers
    //
    // Need to be programmed based on SDRAM Data-Sheet.
    //T_RFC = 60ns = 0x6
    //T_RP  = 18ns = 0x1
    //T_RCD = 18ns = 0x1
    //T_WR  = 1CLK + 6 ns = 0x1
    //T_RAS = 42ns = 0x4
    //T_RC  = 60ns = 0x6
    //T_RRD = 12ns = 0x1
    //
    Emif1Regs.SDRAM_TR.all = 0x31114610;

    //
    //Txsr = 70ns = 0x7
    //
    Emif1Regs.SDR_EXT_TMNG.all = 0x7;

    //
    //Tref = 64ms for 4096 ROW, RR = 64000*100(Tfrq)/4096 = 1562.5 (0x61B)
    //
    Emif1Regs.SDRAM_RCR.all = 0x61B;

    //
    //PAGESIZE=0 (256 elements per ROW), IBANK = 2 (4 BANK), CL = 3,
    //NM = 0 (32bit)
    //
    Emif1Regs.SDRAM_CR.all = 0x00000720;

    //
    //Add some delay
    //
    for(i=0;i<123;i++) { }

    //
    // Basic read/write check.
    //
    ErrCount_local = sdram_read_write(SDRAM_CS0_START_ADDR, SDRAM_CS0_SIZE);
    ErrCount = ErrCount + ErrCount_local;

    //
    //run different addr walk checks
    //
    ErrCount_local = sdram_addr_walk(SDRAM_CS0_START_ADDR, 15);
    ErrCount = ErrCount + ErrCount_local;

    //
    //run different data walk checks
    //
    ErrCount_local = sdram_data_walk(SDRAM_CS0_START_ADDR, SDRAM_CS0_SIZE);
    ErrCount = ErrCount + ErrCount_local;

    //
    //run different data size checks
    //
    ErrCount_local = sdram_data_size(SDRAM_CS0_START_ADDR, 4);
    ErrCount = ErrCount + ErrCount_local;

    if (ErrCount == 0x0)
    {
        TEST_STATUS = TEST_PASS;
    }

    while (1);
}

//
// End of file
//
