//#############################################################################
//
// FILE:    f2805x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f2805x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f2805x and depending on the active build configuration
//          (RAM or FLASH) the appropriate sections will either be loaded
//          into RAM or FLASH blocks
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// CLA_C is defined to 1 in the project properties
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
//
//--define=CLA_C=1
//
// CLA_MATH_TABLES_IN_ROM is defined in the project properties according to
// build configuration selected
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
// Set this variable to 1 to use the CLA Math Tables in the CLA Data ROM
// If set to 0, make sure the right CLA Math library (one without the _datarom
// suffix) is used in the project
//
//--define=CLA_MATH_TABLES_IN_ROM=1
//

MEMORY
{
PAGE 0 :

   BEGIN             : origin = 0x3F7FFE, length = 0x000002      /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */

   RAML3             : origin = 0x009000, length = 0x001000

   FLASHJ            : origin = 0x3E8000, length = 0x001000      /* on-chip FLASH */
   FLASHI            : origin = 0x3E9000, length = 0x001000      /* on-chip FLASH */
   FLASHH            : origin = 0x3EA000, length = 0x002000      /* on-chip FLASH */
   FLASHG            : origin = 0x3EC000, length = 0x002000      /* on-chip FLASH */
   FLASHF            : origin = 0x3EE000, length = 0x002000      /* on-chip FLASH */
   FLASHE            : origin = 0x3F0000, length = 0x002000      /* on-chip FLASH */
   FLASHD            : origin = 0x3F2000, length = 0x002000      /* on-chip FLASH */

   FLASHA            : origin = 0x3F7000, length = 0x000FFE      /* on-chip FLASH */
                     
   ROM               : origin = 0x3FF27C, length = 0x000D44      /* Boot ROM */
   RESET             : origin = 0x3FFFC0, length = 0x000002      /* part of boot ROM  */
   VECTORS           : origin = 0x3FFFC2, length = 0x00003E      /* part of boot ROM  */

PAGE 1 :

  BOOT_RSVD          : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */

  RAMM0             : origin = 0x000050, length = 0x0003B0
  RAMM1             : origin = 0x000400, length = 0x000400
                     
  RAML01             : origin = 0x008000, length = 0x000C00
  RAML2              : origin = 0x008C00, length = 0x000400     /* on-chip RAM block L2 */

  CLA1_MSGRAMLOW     : origin = 0x001480, length = 0x000080
  CLA1_MSGRAMHIGH    : origin = 0x001500, length = 0x000080
                     
  CLA1_DATAROM       : origin = 0x00F000, length = 0x001000

  FLASHB             : origin = 0x3F6000, length = 0x001000     /* on-chip FLASH */
  FLASHC             : origin = 0x3F4000, length = 0x002000      /* on-chip FLASH */
}

SECTIONS
{

   codestart         : > BEGIN,      PAGE = 0
#if defined(RAM)
   .cinit            : > RAMM0,      PAGE = 1
   .pinit            : > RAMM0,      PAGE = 1
   .text             : >> RAMM0 | RAMM1 | RAML01,      PAGE = 1
   ramfuncs          : > RAMM0,      PAGE = 1
   .econst           : > RAMM1,      PAGE = 1
   .switch           : > RAMM0,      PAGE = 1

   Cla1Prog          : {_Cla1ProgRunStart = .;} > RAML3,
                                       PAGE = 0
#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables    : > CLA1_DATAROM,      PAGE = 1
#endif


#elif defined(_FLASH)
   .cinit            : > FLASHA,     PAGE = 0
   .pinit            : > FLASHA,     PAGE = 0
   .text             : > FLASHA,     PAGE = 0

   ramfuncs          : LOAD = FLASHC,
                       RUN = RAMM0,
                       LOAD_START(_RamfuncsLoadStart),
                       RUN_START(_RamfuncsRunStart),
                       LOAD_SIZE(_RamfuncsLoadSize),
                       PAGE = 1

   .econst           : > FLASHD,     PAGE = 0
   .switch           : > FLASHD,     PAGE = 0

#if  !(CLA_MATH_TABLES_IN_ROM)
   //
   //Load tables to Flash and copy over to RAM
   //
   CLA1mathTables    : LOAD = FLASHB,
                       RUN = RAML2,
                       LOAD_START(_CLA1mathTablesLoadStart),
                       LOAD_SIZE(_CLA1mathTablesLoadSize),
                       RUN_START(_CLA1mathTablesRunStart),
                       PAGE = 1
#endif

   Cla1Prog          : LOAD = FLASHD,
                       RUN = RAML3,
                       LOAD_START(_Cla1ProgLoadStart),
                       LOAD_SIZE(_Cla1ProgLoadSize),
                       RUN_START(_Cla1ProgRunStart),
                       PAGE = 0

#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   .stack            : > RAMM1,      PAGE = 1
   .ebss             : > RAML01,     PAGE = 1
   .esysmem          : > RAMM1,      PAGE = 1

   Cla1ToCpuMsgRAM   : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM   : > CLA1_MSGRAMHIGH,  PAGE = 1

   .reset            : > RESET,      PAGE = 0, TYPE = DSECT
   vectors           : > VECTORS,    PAGE = 0, TYPE = DSECT

#ifdef CLA_C
   //
   // CLA C compiler sections
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad       : > RAML2,       PAGE = 1
   .bss_cla          : > RAML2,       PAGE = 1
   .const_cla        : > RAML2,       PAGE = 1
#endif
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/

