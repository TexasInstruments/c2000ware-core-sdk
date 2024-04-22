//#############################################################################
//
// FILE:    f2838x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f2838x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f2838x and depending on the active build configuration
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

#if defined(RAM)
   BEGIN             : origin = 0x000000, length = 0x000002
#elif defined(_FLASH)
   BEGIN             : origin = 0x080000, length = 0x000002
#endif

   RAMM0             : origin = 0x0001B0, length = 0x000250
   RAMM1             : origin = 0x000400, length = 0x000400

   RAMD0             : origin = 0x00C000, length = 0x000800
   RAMD1             : origin = 0x00C800, length = 0x000800

   RAMLS0_1          : origin = 0x008000, length = 0x001000

   RAMGS0_1          : origin = 0x00D000, length = 0x002000

   RAMGS8            : origin = 0x015000, length = 0x001000
   RAMGS9            : origin = 0x016000, length = 0x001000
   RAMGS10           : origin = 0x017000, length = 0x001000
   RAMGS11           : origin = 0x018000, length = 0x001000

   RESET             : origin = 0x3FFFC0, length = 0x000002

   IQTABLES          : origin = 0x3FE000, length = 0x000B50
   IQTABLES2         : origin = 0x3FEB50, length = 0x00008C
   IQTABLES3         : origin = 0x3FEBDC, length = 0x0000AA

   FLASH0            : origin = 0x080002, length = 0x001FFE
   FLASH1            : origin = 0x082000, length = 0x002000
   FLASH2            : origin = 0x084000, length = 0x002000
   FLASH3            : origin = 0x086000, length = 0x002000
   FLASH4            : origin = 0x088000, length = 0x008000
   FLASH5            : origin = 0x090000, length = 0x008000
   FLASH6            : origin = 0x098000, length = 0x008000
   FLASH7            : origin = 0x0A0000, length = 0x008000
   FLASH8            : origin = 0x0A8000, length = 0x008000
   FLASH9            : origin = 0x0B0000, length = 0x008000
   FLASH10           : origin = 0x0B8000, length = 0x002000


PAGE 1 :
   BOOT_RSVD         : origin = 0x000002, length = 0x0001AE

   CLA1_MSGRAMLOW    : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH   : origin = 0x001500, length = 0x000080

   RAMLS2_3          : origin = 0x009000, length = 0x001000
   RAMLS4_5          : origin = 0x00A000, length = 0x001000
   RAMLS6            : origin = 0x00B000, length = 0x000800
   RAMLS7            : origin = 0x00B800, length = 0x000800

   RAMGS2            : origin = 0x00F000, length = 0x001000
   RAMGS3_4          : origin = 0x010000, length = 0x002000
   RAMGS5_6          : origin = 0x012000, length = 0x002000
   RAMGS7            : origin = 0x014000, length = 0x001000

   RAMGS12           : origin = 0x019000, length = 0x001000
   RAMGS13           : origin = 0x01A000, length = 0x001000
   RAMGS14           : origin = 0x01B000, length = 0x001000
   RAMGS15           : origin = 0x01C000, length = 0x001000
   
   CPU1TOCPU2RAM   : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM   : origin = 0x03B000, length = 0x000800
   CPUTOCMRAM      : origin = 0x039000, length = 0x000800
   CMTOCPURAM      : origin = 0x038000, length = 0x000800

   FLASH11           : origin = 0x0BA000, length = 0x002000
   FLASH12           : origin = 0x0BC000, length = 0x002000
   FLASH13           : origin = 0x0BE000, length = 0x002000
}

SECTIONS
{
   codestart         : > BEGIN,                 PAGE = 0

   .bss           : > RAMGS0_1,                 PAGE = 0
   .const         : > RAMGS0_1,                 PAGE = 0
   .data          : > RAMGS0_1,                 PAGE = 0
   .init_array    : > RAMGS0_1,                 PAGE = 0

#if defined(RAM)
   .TI.ramfunc       : > RAMM0,                 PAGE = 0
   .text             :>> RAMM1 | RAMD0 | RAMD1, PAGE = 0
   .cinit            : > RAMGS0_1,              PAGE = 0

   .pinit            : > RAMGS0_1,              PAGE = 0
   .switch           : > RAMGS0_1,              PAGE = 0
   .econst           : > RAMGS3_4,              PAGE = 1
#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables    : > RAMLS4_5,              PAGE = 1
#endif

   Cla1Prog          : > RAMLS0_1,              PAGE = 0


#elif defined(_FLASH)
   .TI.ramfunc       :  LOAD = FLASH3,
                        RUN = RAMGS0_1,
                        RUN_START(RamfuncsRunStart),
                        LOAD_START(RamfuncsLoadStart),
                        LOAD_SIZE(RamfuncsLoadSize),
                        PAGE = 0

   .text             : > FLASH0,                PAGE = 0
   .cinit            : > FLASH1,                PAGE = 0

   .pinit            : > FLASH1,                PAGE = 0
   .switch           : > FLASH1,                PAGE = 0
   .econst           : > FLASH2,                PAGE = 0

#if  !(CLA_MATH_TABLES_IN_ROM)
   //
   //Load tables to Flash and copy over to RAM
   //
   CLA1mathTables    :  LOAD = FLASH11,
                        RUN = RAMLS4_5,
                        RUN_START(CLA1mathTablesRunStart),
                        LOAD_START(CLA1mathTablesLoadStart),
                        LOAD_SIZE(CLA1mathTablesLoadSize),
                        PAGE = 1
#endif

   Cla1Prog          :  LOAD = FLASH3,
                        RUN = RAMLS0_1,
                        RUN_START(Cla1ProgRunStart),
                        LOAD_START(Cla1ProgLoadStart),
                        LOAD_SIZE(Cla1ProgLoadSize),
                        PAGE = 0

#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   Cla1ToCpuMsgRAM     : > CLA1_MSGRAMLOW,      PAGE = 1
   CpuToCla1MsgRAM     : > CLA1_MSGRAMHIGH,     PAGE = 1
   
   MSGRAM_CPU1_TO_CPU2 : > CPU1TOCPU2RAM,       PAGE = 1, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 : > CPU2TOCPU1RAM,       PAGE = 1, type=NOINIT
   MSGRAM_CPU_TO_CM    : > CPUTOCMRAM,          PAGE = 1, type=NOINIT
   MSGRAM_CM_TO_CPU    : > CMTOCPURAM,          PAGE = 1, type=NOINIT

#ifdef CLA_C
   //
   // CLA C compiler sections
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad       : > RAMLS4_5,              PAGE = 1
   .bss_cla          : > RAMLS4_5,              PAGE = 1
   .const_cla        : > RAMLS4_5,              PAGE = 1
#endif

   IOBuffer          : > RAMLS2_3,              PAGE = 1

   .reset            : > RESET,                 PAGE = 0, TYPE = DSECT /* not used, */

   .cio              : > RAMGS7,                PAGE = 1
   .sysmem           : > RAMGS7,                PAGE = 1

   .stack            : > RAMGS2,                PAGE = 1 /* Needs to be in lower 64K memory */
   .ebss             : > RAMGS5_6,              PAGE = 1
   .esysmem          : > RAMGS7,                PAGE = 1
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/
