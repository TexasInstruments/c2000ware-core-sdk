//#############################################################################
//
// FILE:    f28p55x_cla_c_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the f28P55x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          f28P55x and depending on the active build configuration
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

#if defined(RAM)
   BEGIN           	: origin = 0x00000000, length = 0x00000002
#elif defined(_FLASH)
   BEGIN           	: origin = 0x00080000, length = 0x00000002
#endif

   BOOT_RSVD        : origin = 0x000002, length = 0x000126     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x000128, length = 0x0002D8
   RAMM1            : origin = 0x000400, length = 0x000400
   
   RAMLS0           : origin = 0x008000, length = 0x000800
   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6           : origin = 0x00B000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RAMLS8           : origin = 0x014000, length = 0x002000  // When configured as CLA program use the address 0x4000
   RAMLS9           : origin = 0x016000, length = 0x002000  // When configured as CLA program use the address 0x6000

   // RAMLS8_CLA    : origin = 0x004000, length = 0x002000  // Use only if configured as CLA program memory
   // RAMLS9_CLA    : origin = 0x006000, length = 0x002000  // Use only if configured as CLA program memory

   RAMGS0           : origin = 0x00C000, length = 0x002000
   RAMGS1           : origin = 0x00E000, length = 0x002000
   #if defined(f28p55x)
   RAMGS2           : origin = 0x010000, length = 0x002000 // Not available on P551x 
   RAMGS3           : origin = 0x012000, length = 0x002000 // Not available on P551x
   #endif

   /* Flash Banks (128 sectors each) */
   FLASH_BANK0     : origin = 0x080002, length = 0x1fffd
   #if defined(f28p55x)
   FLASH_BANK1     : origin = 0x0A0000, length = 0x20000   // Not available on P551x
   #endif
   FLASH_BANK2     : origin = 0x0C0000, length = 0x20000
   #if defined(f28p55x)
   FLASH_BANK3     : origin = 0x0E0000, length = 0x20000   // Not available on P551x
   #endif
   FLASH_BANK4     : origin = 0x100000, length = 0x20000


   CLATOCPURAM      : origin = 0x001480,   length = 0x000080
   CPUTOCLARAM      : origin = 0x001500,   length = 0x000080
   CLATODMARAM      : origin = 0x001680,   length = 0x000080
   DMATOCLARAM      : origin = 0x001700,   length = 0x000080

   RESET            : origin = 0x3FFFC0, length = 0x000002
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

   .econst           : > RAMGS1

#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables    : > RAMLS4
#endif

   Cla1Prog          : > RAMLS0


#elif defined(_FLASH)

#if defined(__TI_EABI__)
   .TI.ramfunc       :  LOAD = FLASH_BANK0,
                        RUN = RAMGS1,
                        RUN_START(RamfuncsRunStart),
                        LOAD_START(RamfuncsLoadStart),
                        LOAD_SIZE(RamfuncsLoadSize)


#else
   .TI.ramfunc       :  LOAD = FLASH_BANK0,
                        RUN = RAMGS1,
                        RUN_START(_RamfuncsRunStart),
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize)

#endif

   .text             : >> FLASH_BANK0
   .cinit            : > FLASH_BANK0
                     
   .pinit            : > FLASH_BANK0
   .switch           : > FLASH_BANK0

   .econst           : > FLASH_BANK0

#if  !(CLA_MATH_TABLES_IN_ROM)
   //
   //Load tables to Flash and copy over to RAM
   //
#if defined(__TI_EABI__)
   CLA1mathTables    :  LOAD = FLASH_BANK0,
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
   Cla1Prog          :  LOAD = FLASH_BANK2,
                        RUN = RAMLS0,
                        RUN_START(Cla1ProgRunStart),
                        LOAD_START(Cla1ProgLoadStart),
                        LOAD_SIZE(Cla1ProgLoadSize)

#else
   Cla1Prog          :  LOAD = FLASH_BANK2,
                        RUN = RAMLS0,
                        RUN_START(_Cla1ProgRunStart),
                        LOAD_START(_Cla1ProgLoadStart),
                        LOAD_SIZE(_Cla1ProgLoadSize)

#endif

#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

   Cla1ToCpuMsgRAM   : > CLATOCPURAM
   CpuToCla1MsgRAM   : > CPUTOCLARAM

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
                     
   .cio              : > RAMGS0
   .sysmem           : > RAMGS0
                     
   .stack            : > RAMM1        /* Needs to be in lower 64K memory */

   .ebss             : > RAMGS0
   .esysmem          : > RAMGS0
}

/*
//=============================================================================
// End of file.
//=============================================================================
*/
