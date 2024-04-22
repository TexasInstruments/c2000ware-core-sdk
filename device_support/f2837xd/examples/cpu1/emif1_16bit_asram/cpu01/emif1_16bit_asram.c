//###########################################################################
//
// FILE:   emif1_16bit_asram.c
//
// TITLE:  EMIF1 module accessing 16bit ASRAM.
//
//! \addtogroup cpu01_example_list
//! <h1> EMIF ASYNC module (emif1_16bit_asram)</h1>
//!
//! This example configures EMIF1 in 16bit ASYNC mode
//! This example uses CS2 as chip enable.
//!
//! \b Watch \b Variables: \n
//! - \b TEST_STATUS - Equivalent to \b TEST_PASS if test finished correctly,
//!                    else the value is set to \b TEST_FAIL
//! - \b ErrCount - Error counter
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

#define TEST_PASS            0xABCDABCD
#define TEST_FAIL            0xDEADDEAD
#define ASRAM_CS2_START_ADDR 0x100000
#define ASRAM_CS2_SIZE       0x8000
#define EMIF1                0
#define EMIF2                1
#define MEM_D_WIDTH          1            // 16Bit Memory Interface
#define TURN_AROUND_TIME     0            // Turn Around time of 2 Emif Clock
#define RD_SETUP_TIME        0            // Read Setup time of 1 Emif Clock
#define RD_STROBE_TIME       3            // Read Strobe time of 4 Emif Clock
#define RD_HOLD_TIME         0            // Read Hold time of 1 Emif Clock
#define WR_SETUP_TIME        0            // Write Hold time of 1 Emif Clock
#define WR_STROBE_TIME       0            // Write Setup time of 1 Emif Clock
#define WR_HOLD_TIME         0            // Write Hold time of 1 Emif Clock
#define EXTEND_WAIT          0            // Disable Extended Wait
#define STROBE_SEL           0            // Disable Strobe Mode.
#define WAIT_POLAR_INV       0
#define WAIT_COUNT           0

//
// Globals
//
Uint16  ErrCount = 0;
Uint32  TEST_STATUS;
int i;

//
// Function Prototypes
//
extern void setup_emif1_pinmux_async_16bit(Uint16);

//
// mem_read_write - This function performs simple read/write word accesses
//                  to memory.
//
char
mem_read_write(Uint32 start_addr, Uint32 mem_size)
{
    unsigned long mem_rds;
    unsigned long mem_wds;
    long *XMEM_ps;
    unsigned int i;

    //
    //Write data
    //
    XMEM_ps = (long *)start_addr;

    //
    //Fill memory
    //
    mem_wds = 0x01234567;
    for (i=0; i < mem_size; i++)
    {
        *XMEM_ps++ = mem_wds;
        mem_wds += 0x11111111;
    }

    //
    //Verify memory
    //
    mem_wds = 0x01234567;
    XMEM_ps = (long *)start_addr;
    for (i=0; i < mem_size; i++)
    {
        mem_rds = *XMEM_ps;
        if( mem_rds != mem_wds)
        {
            return(1);
        }
        XMEM_ps++;
        mem_wds += 0x11111111;
    }
    return(0);
}

//
//  mem_data_walk - This function performs a walking 0 & 1 on data lines for
//                  SRAM RD & WR
//
char
mem_data_walk(Uint32 start_addr, Uint32 mem_size)
{
    unsigned long sram_rd;
    unsigned long sram_wd;
    unsigned long i;
    int k;
    int m;
    unsigned long  *XM_p;
    unsigned long  *XMEM_p;

    XM_p = (unsigned long *)start_addr;

    for (i=0; i < mem_size; i=i+64)
    {
        for (m=0; m < 2; m++)
        {
            //
            //Write loop
            //
            XMEM_p = XM_p;
            sram_wd = 0x01;
            for (k=0; k < 32; k++)
            {
                if(m==0)
                {
                    *XMEM_p++ =  sram_wd;
                }
                else
                {
                    *XMEM_p++ = ~sram_wd;
                }
                sram_wd   = sram_wd<<1;
            }

            //
            //Read loop
            //
            XMEM_p = XM_p;
            sram_wd = 0x01;
            for (k=0; k < 32; k++)
            {
                sram_rd = *XMEM_p;
                if(m==1)
                {
                    sram_rd = ~sram_rd;
                }
                if(sram_rd != sram_wd)
                {
                    return(1);
                }
                XMEM_p++;
                sram_wd=sram_wd<<1;
            }
        }
        XM_p = XMEM_p;
    }
    return(0);
}

//
// mem_addr_walk - This function performs a toggle on each address bit.
//
char
mem_addr_walk(Uint32 start_addr, Uint32 addr_size)
{
    unsigned long sram_rd;
    unsigned long sram_wd;
    unsigned int k;
    unsigned long xshift;
    unsigned long  *XM_p;
    unsigned long  *XMEM_p;

    XM_p = (unsigned long *)start_addr;

    //
    //Write loop
    //
    xshift = 0x00000001;
    sram_wd = 0x00;
    for (k=0; k < addr_size; k++)
    {
        XMEM_p = (unsigned long *)(start_addr + xshift);
        *XMEM_p = sram_wd++;
        xshift = xshift<<1;
    }

    //
    //Read loop
    //
    XMEM_p = XM_p;
    xshift = 0x00000001;
    sram_wd = 0x00;
    for (k=0; k < addr_size; k++)
    {
        XMEM_p = (unsigned long *)(start_addr + xshift);
        sram_rd = *XMEM_p;
       if(sram_rd != sram_wd)
       {
           return(1);
       }

       xshift = xshift<<1;
       sram_wd++;
    }
    return(0);
}

//
// mem_data_size - This function performs different data type
//                (HALFWORD/WORD) access.
//
char
mem_data_size(Uint32 start_addr, Uint32 size_to_check)
{
    unsigned short mem_rds;
    unsigned long  mem_rdl;
    unsigned short mem_wds;
    unsigned long  mem_wdl;
    int i;

    short *XMEM_ps;
    long  *XMEM_pl;

    //
    //Write data short
    //
    XMEM_ps = (short *)start_addr;
    mem_wds = 0x0605;

    for (i=0; i < 2; i++)
    {
        *XMEM_ps++ = mem_wds;
        mem_wds += 0x0202;
    }

    //
    //Write data long
    //
    XMEM_pl = (long *)XMEM_ps;
    mem_wdl = 0x0C0B0A09;
    for (i=0; i < 2; i++)
    {
        *XMEM_pl++ = mem_wdl;
        mem_wdl += 0x04040404;
    }

    //
    //Read data short
    //
    XMEM_ps = (short *)start_addr;
    mem_wds = 0x0605;
    for (i=0; i < 6; i++)
    {
        mem_rds = *XMEM_ps;
        if( mem_rds != mem_wds)
        {
            return(1);
        }
        XMEM_ps++;
        mem_wds += 0x0202;
    }

    //
    //Read data long
    //
    XMEM_pl = (long *)start_addr;
    mem_wdl = 0x08070605;
    for (i=0; i < 3; i++)
    {
        mem_rdl = *XMEM_pl;
        if(mem_rdl != mem_wdl)
        {
            return(1);
        }
        XMEM_pl++;
        mem_wdl += 0x04040404;
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
// Initialize system control
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
//Configure to run EMIF1 on full Rate (EMIF1CLK = CPU1SYSCLK)
//
  EALLOW;
  ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x0;
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
// Commit the configuration related to protection. Till this bit remains set
// content of EMIF1ACCPROT0 register can't be changed.
//
  Emif1ConfigRegs.EMIF1COMMIT.all = 0x1;
  if(Emif1ConfigRegs.EMIF1COMMIT.all != 0x1)
  {
     ErrCount++;
  }

//
// Lock the configuration so that EMIF1COMMIT register can't be
// changed any more.
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
  setup_emif1_pinmux_async_16bit(0);

//
//Configure the access timing for CS2 space
//
  Emif1Regs.ASYNC_CS2_CR.all =  (EMIF_ASYNC_ASIZE_16    | // 16Bit Memory
                                                          // Interface
                                 EMIF_ASYNC_TA_1        | // Turn Around time
                                                          // of 2 Emif Clock
                                 EMIF_ASYNC_RHOLD_1     | // Read Hold time
                                                          // of 1 Emif Clock
                                 EMIF_ASYNC_RSTROBE_4   | // Read Strobe time
                                                          // of 4 Emif Clock
                                 EMIF_ASYNC_RSETUP_1    | // Read Setup time
                                                          // of 1 Emif Clock
                                 EMIF_ASYNC_WHOLD_1     | // Write Hold time
                                                          // of 1 Emif Clock
                                 EMIF_ASYNC_WSTROBE_1   | // Write Strobe time
                                                          // of 1 Emif Clock
                                 EMIF_ASYNC_WSETUP_1    | // Write Setup time
                                                          // of 1 Emif Clock
                                 EMIF_ASYNC_EW_DISABLE  | // Extended Wait
                                                          // Disable.
                                 EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode
                                                          // Disable.
                                );

//
//Check basic RD/WR access to CS2 space
//
  ErrCount_local = mem_read_write(ASRAM_CS2_START_ADDR, ASRAM_CS2_SIZE);
  ErrCount = ErrCount + ErrCount_local;

//
//Address walk checks (Tested for Memory with address width of 16bit)
//
  ErrCount_local = mem_addr_walk(ASRAM_CS2_START_ADDR, 16);
  ErrCount = ErrCount + ErrCount_local;

//
//Data walk checks
//
  ErrCount_local = mem_data_walk(ASRAM_CS2_START_ADDR, ASRAM_CS2_SIZE);
  ErrCount = ErrCount + ErrCount_local;

//
//Data size checks
//
  ErrCount_local = mem_data_size(ASRAM_CS2_START_ADDR, 4);
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
