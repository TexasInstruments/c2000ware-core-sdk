//#############################################################################
//
// FILE:    f28p65x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f28003x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f28003x and depending on the active build configuration
//          (RAM or FLASH) the appropriate sections will either be loaded
//          into RAM or FLASH blocks
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
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

#if defined(RAM)
   BEGIN           	: origin = 0x00000000, length = 0x00000002
#elif defined(_FLASH)
   BEGIN           	: origin = 0x00080000, length = 0x00000002
#endif

   RAMM0            : origin = 0x0001B1, length = 0x00024F
   RAMM1            : origin = 0x000400, length = 0x000400
                     
   RAMLS0           : origin = 0x008000, length = 0x000800
   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6           : origin = 0x00B000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RAMLS8           : origin = 0x022000, length = 0x002000  // When configured as CLA program use the address 0x4000
   RAMLS9           : origin = 0x024000, length = 0x002000  // When configured as CLA program use the address 0x6000
                     
   RAMGS0           : origin = 0x010000, length = 0x002000
   RAMGS1           : origin = 0x012000, length = 0x002000
   RAMGS2           : origin = 0x014000, length = 0x002000
   RAMGS3           : origin = 0x016000, length = 0x002000
   RAMGS4           : origin = 0x018000, length = 0x002000
                     
   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000 /* on-chip Flash */

   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF     /* Part of M0, BOOT rom will use this for stack */
                     
   CLA1_MSGRAMLOW    : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH   : origin = 0x001500, length = 0x000080
   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800
                     
                     

   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE /* on-chip Flash */
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000 /* on-chip Flash */
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000 /* on-chip Flash */
}

SECTIONS
{
   codestart         : > BEGIN

   .bss              : > RAMGS0
   .const            : > RAMGS0
   .data             : > RAMGS0
   .init_array       : > RAMGS0

#if defined(RAM)     
   .TI.ramfunc       : > RAMGS0
   .text             : > RAMGS1
   .cinit            : > RAMGS0
                     
   .pinit            : > RAMGS0
   .switch           : > RAMGS0

   .econst           : > RAMGS3

#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables    : > RAMLS4
#endif

   Cla1Prog          : > RAMLS0


#elif defined(_FLASH)

#if defined(__TI_EABI__)
   .TI.ramfunc       :  LOAD = FLASH_BANK0_SEC1,
                        RUN = RAMGS2,
                        RUN_START(RamfuncsRunStart),
                        LOAD_START(RamfuncsLoadStart),
                        LOAD_SIZE(RamfuncsLoadSize)


#else
   .TI.ramfunc       :  LOAD = FLASH_BANK0_SEC1,
                        RUN = RAMGS2,
                        RUN_START(_RamfuncsRunStart),
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize)

#endif

   .text             : >> FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4
   .cinit            : > FLASH_BANK0_SEC5
                     
   .pinit            : > FLASH_BANK0_SEC0
   .switch           : > FLASH_BANK0_SEC0

   .econst           : > FLASH_BANK0_SEC2

#if  !(CLA_MATH_TABLES_IN_ROM)
   //
   //Load tables to Flash and copy over to RAM
   //
#if defined(__TI_EABI__)
   CLA1mathTables    :  LOAD = FLASH_BANK0_SEC1,
                        RUN = RAMLS4,
                        RUN_START(CLA1mathTablesRunStart),
                        LOAD_START(CLA1mathTablesLoadStart),
                        LOAD_SIZE(CLA1mathTablesLoadSize)

#else
   CLA1mathTables    :  LOAD = FLASH_BANK0_SEC1,
                        RUN = RAMLS4,
                        RUN_START(_CLA1mathTablesRunStart),
                        LOAD_START(_CLA1mathTablesLoadStart),
                        LOAD_SIZE(_CLA1mathTablesLoadSize)

#endif

#endif
#if defined(__TI_EABI__)
   Cla1Prog          :  LOAD = FLASH_BANK1_SEC1,
                        RUN = RAMLS0,
                        RUN_START(Cla1ProgRunStart),
                        LOAD_START(Cla1ProgLoadStart),
                        LOAD_SIZE(Cla1ProgLoadSize)

#else
   Cla1Prog          :  LOAD = FLASH_BANK1_SEC1,
                        RUN = RAMLS0,
                        RUN_START(_Cla1ProgRunStart),
                        LOAD_START(_Cla1ProgLoadStart),
                        LOAD_SIZE(_Cla1ProgLoadSize)

#endif

#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   Cla1ToCpuMsgRAM   : > CLA1_MSGRAMLOW
   CpuToCla1MsgRAM   : > CLA1_MSGRAMHIGH
   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT

#ifdef CLA_C
   //
   // CLA C compiler sections
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad       : > RAMLS5
   .bss_cla          : > RAMLS5
   .const_cla        : > RAMLS5
#endif               
                     
   IOBuffer          : > RAMLS3
                     
   .reset            : > RESET,      TYPE = DSECT /* not used, */
                     
   .cio              : > RAMGS3
   .sysmem           : > RAMGS3
                     
   .stack            : > RAMM1        /* Needs to be in lower 64K memory */

   .ebss             : > RAMGS3
   .esysmem          : > RAMGS3
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/
