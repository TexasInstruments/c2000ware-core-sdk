//###########################################################################
//
// FILE:    2838x_RAM_lnk_CProj_cpu1.cmd
//
// TITLE:   Linker Command File For C IQmath examples that run out of RAM
//
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AE     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001B0, length = 0x000250
   RAMM1            : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMD0            : origin = 0x00C000, length = 0x000800
   RAMD1            : origin = 0x00C800, length = 0x000800
   RAMLS0           : origin = 0x008000, length = 0x000800
   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6           : origin = 0x00B000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RAMGS0           : origin = 0x00D000, length = 0x001000
   RAMGS1           : origin = 0x00E000, length = 0x001000
   RAMGS2           : origin = 0x00F000, length = 0x001000
   RAMGS3           : origin = 0x010000, length = 0x001000
   RAMGS4           : origin = 0x011000, length = 0x001000
   RAMGS5           : origin = 0x012000, length = 0x001000
   RAMGS6           : origin = 0x013000, length = 0x001000
   RAMGS7           : origin = 0x014000, length = 0x001000
   RAMGS8           : origin = 0x015000, length = 0x001000
   RAMGS9           : origin = 0x016000, length = 0x001000
   RAMGS10          : origin = 0x017000, length = 0x001000
   RAMGS11          : origin = 0x018000, length = 0x001000
   RAMGS12          : origin = 0x019000, length = 0x001000
   RAMGS13          : origin = 0x01A000, length = 0x001000
   RAMGS14          : origin = 0x01B000, length = 0x001000
   RAMGS15          : origin = 0x01C000, length = 0x001000

   /* Flash sectors */
   FLASH0           : origin = 0x080000, length = 0x002000  /* on-chip Flash */
   FLASH1           : origin = 0x082000, length = 0x002000  /* on-chip Flash */
   FLASH2           : origin = 0x084000, length = 0x002000  /* on-chip Flash */
   FLASH3           : origin = 0x086000, length = 0x002000  /* on-chip Flash */
   FLASH4           : origin = 0x088000, length = 0x008000  /* on-chip Flash */
   FLASH5           : origin = 0x090000, length = 0x008000  /* on-chip Flash */
   FLASH6           : origin = 0x098000, length = 0x008000  /* on-chip Flash */
   FLASH7           : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */
   FLASH8           : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
   FLASH9           : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
   FLASH10          : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
   FLASH11          : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */
   FLASH12          : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */
   FLASH13          : origin = 0x0BE000, length = 0x002000  /* on-chip Flash */
   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : >> RAMD0 | RAMD1 | RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3
   .cinit           : > RAMM0 | RAMM1
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss             : > RAMLS5
   .bss:output      : > RAMLS3
   .init_array      : > RAMM0
   .const           : > RAMLS5
   .data            : > RAMLS5
   .sysmem          : > RAMLS4
#else
   .pinit           : > RAMM0
   .ebss            : >> RAMLS5 | RAMLS6
   .econst          : > RAMLS5
   .esysmem         : > RAMLS5
#endif

   ramgs0 : > RAMGS0
   ramgs1 : > RAMGS1

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM
   MSGRAM_CPU_TO_CM   > CPUTOCMRAM
   MSGRAM_CM_TO_CPU   > CMTOCPURAM

    /* The following section definition are for IQMATH */
   IQmath                   : > RAMGS15
   IQmathTables         : > RAMGS15
   IQmathTablesRam  : > RAMGS15

   /* The following section definition are for SDFM examples */
   Filter_RegsFile  : > RAMGS0
   Filter1_RegsFile : > RAMGS1, fill=0x1111
   Filter2_RegsFile : > RAMGS2, fill=0x2222
   Filter3_RegsFile : > RAMGS3, fill=0x3333
   Filter4_RegsFile : > RAMGS4, fill=0x4444
   Difference_RegsFile : >RAMGS5, fill=0x3333

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0
   #else
    ramfuncs    : > RAMM0
   #endif
#endif

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
