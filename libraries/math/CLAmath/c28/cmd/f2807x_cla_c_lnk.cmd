//#############################################################################
//
// FILE:    f2807x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f2807x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f2807x and depending on the active build configuration
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
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
#if defined(RAM)
   BEGIN             : origin = 0x000000, length = 0x000002
#elif defined(_FLASH)
   BEGIN             : origin = 0x080000, length = 0x000002
#endif               
                     
   RAMM0             : origin = 0x000122, length = 0x0002DE
   RAMM1             : origin = 0x000400, length = 0x000400
                     
   RAMD0             : origin = 0x00B000, length = 0x000800
   RAMD1             : origin = 0x00B800, length = 0x000800
                     
   RAMLS0_1          : origin = 0x008000, length = 0x001000
                     
   RAMGS0_1          : origin = 0x00C000, length = 0x002000
                     
   RAMGS8            : origin = 0x014000, length = 0x001000
   RAMGS9            : origin = 0x015000, length = 0x001000
   RAMGS10           : origin = 0x016000, length = 0x001000
   RAMGS11           : origin = 0x017000, length = 0x001000
                     
   RESET             : origin = 0x3FFFC0, length = 0x000002
                     
   IQTABLES          : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2         : origin = 0x3FEB50, length = 0x00008C
   IQTABLES3         : origin = 0x3FEBDC, length = 0x0000AA
                     
   FLASHA            : origin = 0x080002, length = 0x001FFE   /* on-chip Flash */
   FLASHB            : origin = 0x082000, length = 0x002000   /* on-chip Flash */
   FLASHC            : origin = 0x084000, length = 0x002000   /* on-chip Flash */
   FLASHD            : origin = 0x086000, length = 0x002000   /* on-chip Flash */
   FLASHE            : origin = 0x088000, length = 0x008000   /* on-chip Flash */
   FLASHF            : origin = 0x090000, length = 0x008000   /* on-chip Flash */
   FLASHG            : origin = 0x098000, length = 0x008000   /* on-chip Flash */
   FLASHH            : origin = 0x0A0000, length = 0x008000   /* on-chip Flash */
   FLASHI            : origin = 0x0A8000, length = 0x008000   /* on-chip Flash */
   FLASHJ            : origin = 0x0B0000, length = 0x008000   /* on-chip Flash */
   FLASHK            : origin = 0x0B8000, length = 0x002000   /* on-chip Flash */

PAGE 1 :
   BOOT_RSVD         : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
                     
   CLA1_MSGRAMLOW    : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH   : origin = 0x001500, length = 0x000080
                     
   RAMLS2_3          : origin = 0x009000, length = 0x001000
   RAMLS4_5          : origin = 0x00A000, length = 0x001000
                     
   RAMGS2            : origin = 0x00E000, length = 0x001000
   RAMGS3_4          : origin = 0x00F000, length = 0x002000
   RAMGS5_6          : origin = 0x011000, length = 0x002000
   RAMGS7            : origin = 0x013000, length = 0x001000
                     
   RAMGS12           : origin = 0x018000, length = 0x001000
   RAMGS13           : origin = 0x019000, length = 0x001000
   RAMGS14           : origin = 0x01A000, length = 0x001000
   RAMGS15           : origin = 0x01B000, length = 0x001000
                     
   FLASHL            : origin = 0x0BA000, length = 0x002000   /* on-chip Flash */
   FLASHM            : origin = 0x0BC000, length = 0x002000   /* on-chip Flash */
   FLASHN            : origin = 0x0BE000, length = 0x002000   /* on-chip Flash */

}


SECTIONS
{
   codestart         : > BEGIN,                    PAGE = 0
#if defined(RAM)     
   .TI.ramfunc       : > RAMM0,                    PAGE = 0
   .text             :>> RAMM1 | RAMD0 | RAMD1,    PAGE = 0
   .cinit            : > RAMGS0_1,                 PAGE = 0
                     
   .pinit            : > RAMGS0_1,                 PAGE = 0
   .switch           : > RAMGS0_1,                 PAGE = 0
   .econst           : > RAMGS3_4,                 PAGE = 1
#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables    : > RAMLS4_5,                 PAGE = 1
#endif               
                     
   Cla1Prog          : > RAMLS0_1,                 PAGE = 0


#elif defined(_FLASH)
   .TI.ramfunc       :  LOAD = FLASHD,
                        RUN = RAMGS0_1,
                        RUN_START(_RamfuncsRunStart),
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        PAGE = 0
                     
   .text             : > FLASHA,                   PAGE = 0
   .cinit            : > FLASHB,                   PAGE = 0
                     
   .pinit            : > FLASHB,                   PAGE = 0
   .switch           : > FLASHB,                   PAGE = 0
   .econst           : > FLASHC,                   PAGE = 0

#if  !(CLA_MATH_TABLES_IN_ROM)
   //
   //Load tables to Flash and copy over to RAM
   //
   CLA1mathTables    :  LOAD = FLASHL,
                        RUN = RAMLS4_5,
                        RUN_START(_CLA1mathTablesRunStart),
                        LOAD_START(_CLA1mathTablesLoadStart),
                        LOAD_SIZE(_CLA1mathTablesLoadSize),
                        PAGE = 1
#endif               
                     
   Cla1Prog          :  LOAD = FLASHD,
                        RUN = RAMLS0_1,
                        RUN_START(_Cla1ProgRunStart),
                        LOAD_START(_Cla1ProgLoadStart),
                        LOAD_SIZE(_Cla1ProgLoadSize),
                        PAGE = 0

#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   Cla1ToCpuMsgRAM   : > CLA1_MSGRAMLOW,           PAGE = 1
   CpuToCla1MsgRAM   : > CLA1_MSGRAMHIGH,          PAGE = 1

#ifdef CLA_C
   //
   // CLA C compiler sections
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad       : > RAMLS4_5,                 PAGE = 1
   .bss_cla          : > RAMLS4_5,                 PAGE = 1
   .const_cla        : > RAMLS4_5,                 PAGE = 1
#endif               
                     
   IOBuffer          : > RAMLS2_3,                 PAGE = 1
                     
   .reset            : > RESET,                    PAGE = 0, TYPE = DSECT /* not used, */
                     
   .cio              : > RAMGS7,                   PAGE = 1
   .sysmem           : > RAMGS7,                   PAGE = 1
                     
   .stack            : > RAMGS2,                   PAGE = 1 /* Needs to be in lower 64K memory */
   .ebss             : > RAMGS5_6,                 PAGE = 1
   .esysmem          : > RAMGS7,                   PAGE = 1
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/
