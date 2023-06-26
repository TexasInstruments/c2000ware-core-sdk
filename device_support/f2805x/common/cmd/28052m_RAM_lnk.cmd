/*
// TI File $Revision: /main/2 $
// Checkin $Date: December 7, 2011   18:24:43 $
//###########################################################################
//
// FILE:    28052M_RAM_lnk.cmd
//
// TITLE:   Linker Command File For 28052M examples that run out of RAM
//
//          This ONLY includes all SARAM blocks on the 28052M device.
//          This does not include flash or OTP.
//
//          Keep in mind that L0,L1,L2, and L3 are protected by the code
//          security module.
//
//          What this means is in most cases you will want to move to
//          another memory map file which has more memory defined.
//
//###########################################################################
// $TI Release: 2805x C/C++ Header Files vBeta1 $
// $Release Date: December 9, 2011 $
// $Copyright:
// Copyright (C) 2012-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// The header linker files are found in <base>\F28052M_headers\cmd
//
// For BIOS applications add:      F28052M_Headers_BIOS.cmd
// For nonBIOS applications add:   F28052M_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l F28052M_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l F28052M_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\F28052M_headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F28052M
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F28052M are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN           : origin = 0x000000, length = 0x000002
   RAMM0           : origin = 0x000050, length = 0x0003B0
   RAML1L2         : origin = 0x008800, length = 0x000800
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   Z1_SCC_ROM      : origin = 0x3F8000, length = 0x000400     /* Zone 1 Safe-Copy Code Secure ROM */
   Z2_SCC_ROM      : origin = 0x3F8400, length = 0x000400     /* Zone 2 Safe-Copy Code Secure ROM */ 
   Z1_SECURE_ROM   : origin = 0x3F8808, length = 0x0044F8     /* Z1 Secure ROM */

   IQTABLES   	   : origin = 0x3FDB52, length = 0x000b50
   IQTABLES2  	   : origin = 0x3FE6A2, length = 0x00008C
   IQTABLES3  	   : origin = 0x3FE72E, length = 0x0000AA
                   
   BOOTROM         : origin = 0x3FF27C, length = 0x000D44


PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML3           : origin = 0x009000, length = 0x001000
}


SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranchasm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAMM0      PAGE = 0
   .text            : > RAML1L2,   PAGE = 0
   .cinit           : > RAMM0,     PAGE = 0
   .pinit           : > RAMM0,     PAGE = 0
   .switch          : > RAMM0,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,     PAGE = 1
   .ebss            : > RAML3,     PAGE = 1
   .econst          : > RAML3,     PAGE = 1
   .esysmem         : > RAML3,     PAGE = 1

   IQmath           : > RAML1L2,   PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD

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
