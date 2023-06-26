
MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001A7     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001A9, length = 0x000257
   RAMM1            : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
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
   RAMGS15          : origin = 0x01C000, length = 0x000FF8
//   RAMGS15_RSVD     : origin = 0x01CFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   /* Flash sectors */
   FLASH0           : origin = 0x080000, length = 0x002000	/* on-chip Flash */
   FLASH1           : origin = 0x082000, length = 0x002000	/* on-chip Flash */
   FLASH2           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASH3           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
   FLASH4           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASH5           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   FLASH6           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
   FLASH7           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
   FLASH8           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
   FLASH9           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASH10          : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASH11          : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASH12          : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASH13          : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */   
   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET           	: origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : >>RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss             : > RAMLS5
   .bss:output      : > RAMLS3
   .init_array	    : > RAMM0
   .const           : > RAMLS5
   .data			: > RAMLS5
   .sysmem			: > RAMLS4
#else
   .pinit           : > RAMM0
   .ebss            : > RAMLS5
   .econst          : > RAMLS5
   .esysmem         : > RAMLS5
#endif
   SHARERAMGS0		: > RAMGS0, type=NOINIT
   SHARERAMGS1		: > RAMGS1, type=NOINIT
   SHARERAMGS2		: > RAMGS2, type=NOINIT
   SHARERAMGS3		: > RAMGS3, type=NOINIT
   SHARERAMGS4		: > RAMGS4, type=NOINIT
   SHARERAMGS5		: > RAMGS5, type=NOINIT
   SHARERAMGS6		: > RAMGS6, type=NOINIT
   SHARERAMGS7		: > RAMGS7, type=NOINIT
   SHARERAMGS8		: > RAMGS8, type=NOINIT
   SHARERAMGS9		: > RAMGS9, type=NOINIT
   SHARERAMGS10		: > RAMGS10, type=NOINIT
   SHARERAMGS11		: > RAMGS11, type=NOINIT
   SHARERAMGS12		: > RAMGS12, type=NOINIT
   SHARERAMGS13		: > RAMGS13, type=NOINIT
   SHARERAMGS14		: > RAMGS14, type=NOINIT
   SHARERAMGS15		: > RAMGS15, type=NOINIT

   .cpu1tocpu2RAM > CPU1TOCPU2RAM, type=NOINIT
   .cpu2tocpu1RAM > CPU2TOCPU1RAM, type=NOINIT
   .cputocmRAM	  > CPUTOCMRAM, type=NOINIT
   .cmtocpuRAM    > CMTOCPURAM, type=NOINIT

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT
   MSGRAM_CPU_TO_CM    > CPUTOCMRAM, type=NOINIT
   MSGRAM_CM_TO_CPU    > CMTOCPURAM, type=NOINIT

    .TI.ramfunc : {} > RAMM0

    /* The following section definition are for SDFM examples */
   Filter_RegsFile  : > RAMGS0
   Filter1_RegsFile : > RAMGS1, fill=0x1111
   Filter2_RegsFile : > RAMGS2, fill=0x2222
   Filter3_RegsFile : > RAMGS3, fill=0x3333
   Filter4_RegsFile : > RAMGS4, fill=0x4444
   Difference_RegsFile : >RAMGS5, fill=0x3333

   /* Following section is for MEMCFG examples*/
   #if defined(__TI_EABI__)
  isrfunc  :   LOAD = RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,
                RUN = RAMGS14,
                LOAD_START(isrfuncLoadStart),
                LOAD_END(isrfuncLoadEnd),
                RUN_START(isrfuncRunStart),
                LOAD_SIZE(isrfuncLoadSize)
#else
  isrfunc  :   LOAD = RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,
                RUN = RAMGS14,
                LOAD_START(_isrfuncLoadStart),
                LOAD_END(_isrfuncLoadEnd),
                RUN_START(_isrfuncRunStart),
                LOAD_SIZE(_isrfuncLoadSize)
#endif
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
