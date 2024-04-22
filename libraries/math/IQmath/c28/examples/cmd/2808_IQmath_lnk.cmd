/*
// TI File $Revision: /main/5 $
// Checkin $Date: July 9, 2008   14:18:26 $
//###########################################################################
//
// FILE:    2808_IQmath_lnk.cmd
//
// TITLE:   Linker Command File For IQmath examples that run out of RAM
//
// NOTE; The example project uses memory protected by the
//       Code Security Module (CSM).  Make sure the CSM is
//       unlocked before you load the project.  One quick way
//       to do this on an erased device is to open a memory
//       window to the CSM password locations.  If these locations
//       read back 0xFFFF (or non-zero), then the CSM is unlocked:
//
//      Device    Password locations
//      2808:     0x3F7FF8 - 0x3F7FFF
//
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
*/


MEMORY
{
PAGE 0 :

   /* IQTABLES is part of the boot ROM.  The boot ROM
      is available in both program or data space so this
      can be defined on page 0 or page 1
   */
   IQTABLES   : origin = 0x3FF000, length = 0x000b50
   BEGIN      : origin = 0x000000, length = 0x000002
   RAMM0      : origin = 0x000002, length = 0x0003FE
   RAMH0      : origin = 0x3FA000, length = 0x002000
   RESET      : origin = 0x3FFFC0, length = 0x000002


PAGE 1 :

   /* For this example, H0 is split between PAGE 0 and PAGE 1 */

   RAML0L1     : origin = 0x008000, length = 0x002000
   BOOT_RSVD   : origin = 0x000400, length = 0x000080     /* Part of M1, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000480, length = 0x000380     /* on-chip RAM block M1 */
}


SECTIONS
{

   /* IQmath inclues the assembly routines in the IQmath library
      IQmathTables is used by division, IQsin, IQcos, IQatan, IQatan2
                   this is in boot ROM so we make it NOLOAD.  Using
                   the ROM version saves space at the cost of 1 cycle
                   per access (boot ROM is 1 wait).
      IQmathTablesRam is used by IQasin, IQacos, and IQexp
   */
   IQmath           : > RAMH0,      PAGE = 0
   IQmathTables     : > IQTABLES,   PAGE = 0, type = NOLOAD
   IQmathTablesRam  : > RAML0L1,    PAGE = 1


   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > RAMM0       PAGE = 0
   .text            : > RAMH0,      PAGE = 0
   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,      PAGE = 1
   .cio             : > RAML0L1,    PAGE = 1
   .ebss            : > RAML0L1,    PAGE = 1
   .econst          : > RAML0L1,    PAGE = 1
   .sysmem          : > RAML0L1,    PAGE = 1





}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
