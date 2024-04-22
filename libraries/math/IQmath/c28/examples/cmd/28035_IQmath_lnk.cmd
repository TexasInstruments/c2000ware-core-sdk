/*
// TI File $Revision: /main/2 $
// Checkin $Date: June 2, 2009   15:56:31 $
//###########################################################################
//
// FILE:    28035_IQmath_lnk.cmd
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
//      28027:    0x3F7FF8 - 0x3F7FFF
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

   /* IQTABLES, IQTABLES2 and IQTABLES3 are part of the boot ROM.
      The boot ROM is available in both program or
      data space so this can be defined on page 0 or page 1
   */

   IQTABLES   : origin = 0x3FE000, length = 0x000b50
   IQTABLES2  : origin = 0x3FEB50, length = 0x00008C
   IQTABLES3  : origin = 0x3FEBDC, length = 0x0000AA
   BEGIN      : origin = 0x000000, length = 0x000002
   RAMM0      : origin = 0x000002, length = 0x0003FE
   RAML0      : origin = 0x008000, length = 0x000800
   RESET      : origin = 0x3FFFC0, length = 0x000002


PAGE 1 :

   RAML1L2   : origin = 0x008800, length = 0x000800
   BOOT_RSVD : origin = 0x000400, length = 0x000080     /* Part of M1, BOOT rom will use this for stack */
   RAMM1     : origin = 0x000480, length = 0x000380     /* on-chip RAM block M1 */
}


SECTIONS
{

   /* IQmath inclues the assembly routines in the IQmath library
      IQmathTables is used by division, IQsin, IQcos, IQatan, IQatan2
                   this is in boot ROM so we make it NOLOAD.  Using
                   the ROM version saves space at the cost of 1 cycle
                   per access (boot ROM is 1 wait).
      IQmathTablesRam is used by IQasin, IQacos, and IQexp
      Noticed these tables are linked seperatly since they are from
      two source files within the library.
   */
   IQmath           : > RAML0 | RAMM0,      PAGE = 0
   IQmathTables     : > IQTABLES,   PAGE = 0, TYPE = NOLOAD
   IQmathTables2    : > IQTABLES2,  PAGE = 0, TYPE = NOLOAD
   {
        IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)
   }
   IQmathTables3    :> IQTABLES3,   PAGE = 0, type = NOLOAD
   {
       IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)
   }


   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > RAMM0       PAGE = 0
   .text            : > RAML0,      PAGE = 0
   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,      PAGE = 1
   .cio             : > RAML1L2,    PAGE = 1
   .ebss            : > RAML1L2,    PAGE = 1
   .econst          : > RAML1L2,    PAGE = 1
   .sysmem          : > RAML1L2,    PAGE = 1





}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
