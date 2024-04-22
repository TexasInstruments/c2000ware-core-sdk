/*
// TI File $Revision: /main/4 $
// Checkin $Date: July 9, 2008   14:12:52 $
//###########################################################################
//
// FILE:    F2812_IQmath_lnk.cmd
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
//      2812:     0x3F7FF8 - 0x3F7FFF
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
   RAMM0      : origin = 0x000000, length = 0x000400
   BEGIN      : origin = 0x3F8000, length = 0x000002
   RAMH0      : origin = 0x3F8002, length = 0x001FFE
   RESET      : origin = 0x3FFFC0, length = 0x000002


PAGE 1 :

   RAMM1    : origin = 0x000400, length = 0x000400
   RAML0L1  : origin = 0x008000, length = 0x002000
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

   IQmath           : > RAMH0,       PAGE = 0
   IQmathTables     : > IQTABLES,    PAGE = 0, type = NOLOAD
   IQmathTablesRam  : > RAML0L1,     PAGE = 1

   codestart        : > BEGIN,       PAGE = 0
   ramfuncs         : > RAMH0        PAGE = 0
   .text            : > RAMH0,       PAGE = 0
   .cinit           : > RAMM0,       PAGE = 0
   .pinit           : > RAMH0,       PAGE = 0
   .switch          : > RAMM0,       PAGE = 0
   .reset           : > RESET,       PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,       PAGE = 1
   .cio             : > RAML0L1,     PAGE = 1
   .ebss            : > RAML0L1,     PAGE = 1
   .econst          : > RAML0L1,     PAGE = 1
   .esysmem         : > RAML0L1,     PAGE = 1


}
