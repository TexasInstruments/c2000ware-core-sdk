/*
// TI File $Revision: /main/3 $
// Checkin $Date: March 3, 2011   13:45:35 $
//###########################################################################
//
// FILE:    28065_RAM_CLA_C_lnk.cmd
//
// TITLE:   Linker Command File For F28065 examples that run out of RAM
//
//          This ONLY includes all SARAM blocks on the F28065 device.
//          This does not include flash or OTP.
//
//          Keep in mind that L0,L1,L2,L3 and L4 are protected by the code
//          security module.
//
//          What this means is in most cases you will want to move to
//          another memory map file which has more memory defined.
//
//###########################################################################
// $TI Release: 2806x C/C++ Header Files V1.10 $ 
// $Release Date: April 7, 2011 $ 
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
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file,
// add the header linker command file directly to the project.
// The header linker command file is required to link the
// peripheral structures to the proper locations within
// the memory map.
//
// The header linker files are found in <base>\headers\cmd
//
// For BIOS applications add:      F2806x_Headers_BIOS.cmd
// For nonBIOS applications add:   F2806x_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l F2806x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l F2806x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F2806x
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F28065 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/
_Cla1Prog_Start = _Cla1funcsRunStart;
-heap 0x400
-stack 0x400

// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are. 
// CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN      		: origin = 0x000000, length = 0x000002
   RAMM0      		: origin = 0x000050, length = 0x0003B0
   RAML5L8          : origin = 0x00C000, length = 0x008000
   
  /* RAML0_L2       : origin = 0x008000, length = 0x001000  */
   RAML3		    : origin = 0x009000, length = 0x001000     
   RESET      		: origin = 0x3FFFC0, length = 0x000002
   FPUTABLES        : origin = 0x3FD590, length = 0x0006A0	   /* FPU Tables in Boot ROM */
   IQTABLES   		: origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2  		: origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3  		: origin = 0x3FEADC, length = 0x0000AA	   /* IQ Math Tables in Boot ROM */

   BOOTROM    		: origin = 0x3FF3B0, length = 0x000C10


PAGE 1 :

   BOOT_RSVD   			: origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       			: origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   CLARAM0              : origin = 0x008800, length = 0x000400
   CLARAM1              : origin = 0x008C00, length = 0x000400
   CLARAM2				: origin = 0x008000, length = 0x000800
   RAML4				: origin = 0x00a000, length = 0x002000     /* on-chip RAM block L4 */
/*   RAML5       		: origin = 0x00C000, length = 0x002000 */    /* on-chip RAM block L5 */
/*   RAML6       		: origin = 0x00E000, length = 0x002000 */     /* on-chip RAM block L6 */
/*   RAML7       		: origin = 0x010000, length = 0x002000 */     /* on-chip RAM block L7 */
/*   RAML8       		: origin = 0x012000, length = 0x002000 */     /* on-chip RAM block L8 */
   USB_RAM              : origin = 0x040000, length = 0x000800     /* USB RAM		  */
   CLA1_MSGRAMLOW       : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH      : origin = 0x001500, length = 0x000080
}


SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAMM0,     PAGE = 0
   .text            : > RAML5L8,   PAGE = 0
   .cinit           : > RAMM0,     PAGE = 0
   .pinit           : > RAMM0,     PAGE = 0
   .switch          : > RAMM0,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAML4,     PAGE = 1
   .ebss            : > RAML4,     PAGE = 1
   .econst          : > RAML4,     PAGE = 1
   .esysmem         : > RAML4,     PAGE = 1
   .sysmem          : > RAML4,     PAGE = 1
   .cio             : > RAML4,     PAGE = 1

   .scratchpad      : > CLARAM0,   PAGE = 1
   .bss_cla		    : > CLARAM0,   PAGE = 1
   .const_cla	    : > CLARAM0,   PAGE = 1 
   
   IQmath           : > RAML4,     PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD
   
   /* Allocate FPU math areas: */
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD

   Cla1Prog        : > RAML3,
                     LOAD_START(_Cla1funcsLoadStart),
                     LOAD_END(_Cla1funcsLoadEnd),
                     LOAD_SIZE(_Cla1funcsLoadSize),
                     RUN_START(_Cla1funcsRunStart),
                     PAGE = 0
   
   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1
   Cla1DataRam0		: > CLARAM0,		  PAGE = 1
   Cla1DataRam1		: > CLARAM1,		  PAGE = 1
   Cla1DataRam2		: > CLARAM2,		  PAGE = 1
   
   CLA1mathTables	: > CLARAM1,
                      LOAD_START(_Cla1mathTablesLoadStart),
                      LOAD_END(_Cla1mathTablesLoadEnd), 
                      LOAD_SIZE(_Cla1mathTablesLoadSize),
                      RUN_START(_Cla1mathTablesRunStart),
                      PAGE = 1

   CLAscratch       : 
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } > CLARAM0,
					 PAGE = 1
                     
  /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)

   }
   */
   /* Uncomment the section below if calling the IQNasin() or IQasin()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables3    : > IQTABLES3, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)

   }
   */

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
