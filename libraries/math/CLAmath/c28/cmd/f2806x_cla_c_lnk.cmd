//#############################################################################
//
// FILE:    f2806x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f2806x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f2806x and depending on the active build configuration
//          (RAM or FLASH) the appropriate sections will either be loaded
//          into RAM or FLASH blocks
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
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

   BEGIN             : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CLAPROGRAM        : origin = 0x009000, length = 0x001000     /* on-chip RAM block L3 */
   RAMM0             : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAML5L8           : origin = 0x00C000, length = 0x008000
   OTP               : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
                     
   FLASHH            : origin = 0x3D8000, length = 0x004000     /* on-chip FLASH */
   FLASHG            : origin = 0x3DC000, length = 0x004000     /* on-chip FLASH */
   FLASHF            : origin = 0x3E0000, length = 0x004000     /* on-chip FLASH */
   FLASHE            : origin = 0x3E4000, length = 0x004000     /* on-chip FLASH */
   FLASHD            : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHC            : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHA            : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
                     
   ROM               : origin = 0x3FF3B0, length = 0x000C10     /* Boot ROM */
   RESET             : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS           : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 :

   BOOT_RSVD         : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1             : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */

   CLA1_MSGRAMLOW    : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH   : origin = 0x001500, length = 0x000080

   CLARAM0           : origin = 0x008800, length = 0x000400     /* on-chip RAM block L1 */
   CLARAM1           : origin = 0x008C00, length = 0x000400     /* on-chip RAM block L2 */
   CLARAM2           : origin = 0x008000, length = 0x000800     /* on-chip RAM block L0 */
                     
   RAML4             : origin = 0x00A000, length = 0x002000     /* on-chip RAM block L4 */
   USB_RAM           : origin = 0x040000, length = 0x000800     /* USB RAM          */
   FLASHB            : origin = 0x3F0000, length = 0x004000     /* on-chip FLASH */
}

SECTIONS
{
   codestart         : > BEGIN,      PAGE = 0
#if defined(RAM)
   .cinit            : > RAMM0,      PAGE = 0
   .pinit            : > RAMM0,      PAGE = 0
   .text             : > RAML5L8,    PAGE = 0
   ramfuncs          : > RAML5L8,    PAGE = 0
   .econst           : > RAML5L8,    PAGE = 0
   .switch           : > RAMM0,      PAGE = 0

   Cla1Prog          : {_Cla1ProgRunStart = .;} > CLAPROGRAM,
                                     PAGE = 0
   CLA1mathTables    : > CLARAM1,    PAGE = 1


#elif defined(_FLASH)
   .cinit            : > FLASHA,     PAGE = 0
   .pinit            : > FLASHA,     PAGE = 0
   .text             : > FLASHA,     PAGE = 0

   ramfuncs          : LOAD = FLASHD,
                       RUN = RAML5L8,
                       LOAD_START(_RamfuncsLoadStart),
                       RUN_START(_RamfuncsRunStart),
                       LOAD_SIZE(_RamfuncsLoadSize),
                       PAGE = 0
   .econst           : > FLASHA,     PAGE = 0
   .switch           : > FLASHA,     PAGE = 0

   Cla1Prog          : LOAD = FLASHD,
                       RUN = CLAPROGRAM,
                       LOAD_START(_Cla1ProgLoadStart),
                       LOAD_SIZE(_Cla1ProgLoadSize),
                       RUN_START(_Cla1ProgRunStart),
                       PAGE = 0
   //
   //Load tables to Flash and copy over to RAM
   //
   CLA1mathTables    : LOAD = FLASHB,
                       RUN = CLARAM1,
                       LOAD_START(_CLA1mathTablesLoadStart),
                       LOAD_SIZE(_CLA1mathTablesLoadSize),
                       RUN_START(_CLA1mathTablesRunStart),
                       PAGE = 1
#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   .stack            : > RAML4,      PAGE = 1
   .ebss             : > RAML4,      PAGE = 1
   .esysmem          : > RAML4,      PAGE = 1

   Cla1ToCpuMsgRAM   : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM   : > CLA1_MSGRAMHIGH,  PAGE = 1
   Cla1DataRam0      : > CLARAM0,          PAGE = 1
   Cla1DataRam1      : > CLARAM1,          PAGE = 1
   Cla1DataRam2      : > CLARAM2,          PAGE = 1

#ifdef CLA_C
   //
   // CLA C compiler sections
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad       : > CLARAM1,       PAGE = 1
   .bss_cla          : > CLARAM2,       PAGE = 1
   .const_cla        : > CLARAM2,       PAGE = 1
#endif

   .reset            : > RESET,      PAGE = 0, TYPE = DSECT
   vectors           : > VECTORS,    PAGE = 0, TYPE = DSECT
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/

