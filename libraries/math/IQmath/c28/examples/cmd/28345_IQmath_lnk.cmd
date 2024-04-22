/*
// TI File $Revision: /main/1 $
// Checkin $Date: July 9, 2009   09:24:26 $
//###########################################################################
//
// FILE:    28345_RAM_lnk.cmd
//
// TITLE:   Linker Command File For 28345 examples that run out of RAM
//
//
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
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
// The header linker files are found in <base>\DSP2834x_Headers\cmd
//
// For BIOS applications add:      DSP2834x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP2834x_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP2834x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP2834x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP2834x_headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the C28345
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on C28345 are uniform (ie same
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
   /* BEGIN is used for the "boot to SARAM" bootloader mode      */

   BEGIN        : origin = 0x000000, length = 0x000002     /* Boot to M0 will go here                      */

   RAMM0        : origin = 0x000052, length = 0x0003AE
   RAML0        : origin = 0x008000, length = 0x002000
   RAML1        : origin = 0x00A000, length = 0x002000
   ZONE7A       : origin = 0x200000, length = 0x00FC00    /* XINTF zone 7 - program space */
   RAMH0        : origin = 0x300000, length = 0x008000
   RAMH1        : origin = 0x308000, length = 0x008000
   RAMH2        : origin = 0x310000, length = 0x008000
   CSM_RSVD     : origin = 0x33FF80, length = 0x000076     /* Reserved - for compatibility to legacy C28x designs. */
   CSM_PWL_PROG : origin = 0x33FFF8, length = 0x000008     /* 128-bit password locations */
   IQTABLES     : origin = 0x3FE000, length = 0x000b50
   IQTABLES2    : origin = 0x3FEB50, length = 0x00008c
   FPUTABLES    : origin = 0x3FEBDC, length = 0x0006A0
   BOOTROM      : origin = 0x3FF27C, length = 0x000D44
   RESET        : origin = 0x3FFFC0, length = 0x000002


PAGE 1 :
   /* BOOT_RSVD is used by the boot ROM for stack.               */
   /* This section is only reserved to keep the BOOT ROM from    */
   /* corrupting this area during the debug process              */

   BOOT_RSVD    : origin = 0x000002, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1        : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML2        : origin = 0x00C000, length = 0x002000
   RAML3        : origin = 0x00E000, length = 0x002000
   RAML4        : origin = 0x010000, length = 0x002000
   RAML5        : origin = 0x012000, length = 0x002000
   RAML6        : origin = 0x014000, length = 0x002000
   RAML7        : origin = 0x016000, length = 0x002000
   ZONE7B       : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
   RAMH3        : origin = 0x318000, length = 0x008000
   RAMH4        : origin = 0x320000, length = 0x008000
   RAMH5        : origin = 0x328000, length = 0x008000
}


SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAML0,     PAGE = 0
   .text            : > RAML1,     PAGE = 0
   .cinit           : > RAML0,     PAGE = 0
   .pinit           : > RAML0,     PAGE = 0
   .switch          : > RAML0,     PAGE = 0
   .cio				: > RAML0,     PAGE = 0
   
   .stack           : > RAMM1,     PAGE = 1
   .ebss            : > RAML2,     PAGE = 1
   .econst          : > RAML3,     PAGE = 1
   .esysmem         : > RAML2,     PAGE = 1

   IQmath           : > RAML1,     PAGE = 0
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

   FPUmathTables    : > FPUTABLES,      PAGE = 0, TYPE = NOLOAD

   DMARAML2         : > RAML2,          PAGE = 1
   DMARAML3         : > RAML3,          PAGE = 1
   DMARAML4         : > RAML4,          PAGE = 1
   DMARAML5         : > RAML5,          PAGE = 1
   DMARAML6         : > RAML6,          PAGE = 1
   DMARAML7         : > RAML7,          PAGE = 1

   ZONE7DATA        : > ZONE7B,         PAGE = 1

   .reset           : > RESET,          PAGE = 0, TYPE = DSECT /* not used                    */
   csm_rsvd         : > CSM_RSVD        PAGE = 0, TYPE = DSECT
   csmpasswds       : > CSM_PWL_PROG    PAGE = 0, TYPE = DSECT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
