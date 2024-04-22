//#############################################################################
//
// FILE:    F2837x_VCU2_RFFT_128_lnk.cmd
//
// TITLE:   Linker Command File for VCU-II library examples that run 
//          on the 2837x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          2837x and depending on the active build configuration(RAM or FLASH)
//          the appropriate sections will either be loaded into RAM or FLASH 
//          blocks
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
// NOTES:
// 1. In addition to this memory linker command file, add the header linker 
//    command file directly to the project. The header linker command file is 
//    required to link the peripheral structures to the proper locations within
//    the memory map.
//    
//    The header linker files are found in 
//    c2000\C2000Ware_X_XX_XX_XX\device_support\f2837x(d/s)\headers\cmd
//    
//    For BIOS applications add:      F2837x(D/S)_Headers_BIOS_cpuX.cmd
//    For nonBIOS applications add:   F2837x(D/S)_Headers_nonBIOS_cpuX.cmd
//
// 2. On reset all RAMGSx blocks are under the mastership of CPU1. The user
//     must configure the appropriate control registers to transfer mastership
//     of a RAMGSx block over to CPU2
//
// 3. Memory blocks on F2837x are uniform (ie same physical memory) in both 
//    PAGE 0 and PAGE 1. That is the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program
//    and/or data.
//    
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
#if defined(RAM)
   BEGIN           : origin = 0x000000, length = 0x000002
#elif defined(FLASH)
   BEGIN           : origin = 0x080000, length = 0x000002
#endif 
   RAMM0           : origin = 0x000122, length = 0x0002DE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMD0		   : origin = 0x00B000, length = 0x000800
   RAMD1		   : origin = 0x00B800, length = 0x000800
   
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS2          : origin = 0x009000, length = 0x000800
   
   RAMGS0		   : origin = 0x00C000, length = 0x001000
   RAMGS1		   : origin = 0x00D000, length = 0x001000
   RAMGS2		   : origin = 0x00E000, length = 0x001000
   RAMGS3		   : origin = 0x00F000, length = 0x001000
   
   RAMGS8		   : origin = 0x014000, length = 0x001000
   RAMGS9		   : origin = 0x015000, length = 0x001000
   RAMGS10		   : origin = 0x016000, length = 0x001000
   RAMGS11		   : origin = 0x017000, length = 0x001000
   
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   FLASHA           : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHF           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASHG           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASHH           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASHI           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASHJ           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */   

PAGE 1 :
   BOOT_RSVD       : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */

   RAMLS3          : origin = 0x009800, length = 0x000800
   RAMLS4          : origin = 0x00A000, length = 0x000800
   RAMLS5          : origin = 0x00A800, length = 0x000800
   
   RAMGS4		   : origin = 0x010000, length = 0x001000
   RAMGS5		   : origin = 0x011000, length = 0x001000
   RAMGS6		   : origin = 0x012000, length = 0x001000
   RAMGS7		   : origin = 0x013000, length = 0x001000
   
   RAMGS12		   : origin = 0x018000, length = 0x001000
   RAMGS13		   : origin = 0x019000, length = 0x001000
   RAMGS14		   : origin = 0x01A000, length = 0x001000
   RAMGS15		   : origin = 0x01B000, length = 0x001000

   FLASHB          : origin = 0x082000, length = 0x002000	/* on-chip Flash */
}

SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0
#if defined(RAM)
   .TI.ramfunc      : > RAMM0,     PAGE = 0
   .text            :>> RAMM1 | RAMD0 | RAMD1 | RAMLS0,  PAGE = 0
   .cinit           : > RAMLS1,    PAGE = 0
   
   .pinit           : > RAMLS1,    PAGE = 0
   .switch          : > RAMLS1,    PAGE = 0
   .econst          : > RAMLS4,    PAGE = 1
   twiddleFactors   : > RAMLS5,    PAGE  = 1

#elif defined(FLASH)
   .TI.ramfunc      :  LOAD = FLASHC,
                       RUN = RAMLS1,
                       RUN_START(_RamfuncsRunStart),
                       LOAD_START(_RamfuncsLoadStart),
                       LOAD_SIZE(_RamfuncsLoadSize),
                       PAGE = 0

   .text            : > FLASHN,    PAGE = 0
   .cinit           : > FLASHM,    PAGE = 0

   .pinit           : > FLASHM,    PAGE = 0
   .switch          : > FLASHM,    PAGE = 0
   .econst          : > FLASHB,    PAGE = 1
   twiddleFactors   : > FLASHB,    PAGE  = 1
#else
#error Add either "RAM" or "FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif //RAM

   /* Test specific sections */
   buffer1          : > RAMLS3, ALIGN = 128, PAGE = 1
   buffer2          : > RAMLS4, ALIGN = 128, PAGE = 1

   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .cio             : > RAMLS3,    PAGE = 1
   .sysmem          : > RAMLS3,    PAGE = 1

   .stack           : > RAMLS4,    PAGE = 1
   .ebss            : > RAMLS4,    PAGE = 1
   .esysmem         : > RAMLS4,    PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
