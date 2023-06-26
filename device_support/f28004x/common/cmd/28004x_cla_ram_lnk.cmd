
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN            : origin = 0x000000, length = 0x000002
   RAMM0            : origin = 0x0000F6, length = 0x00030A

   RAMLS0           : origin = 0x008000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002

 /* Flash sectors: you can use FLASH for program memory when the RAM is filled up*/
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000	/* on-chip Flash */

  /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000	/* on-chip Flash */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x0000F1     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6           : origin = 0x00B000, length = 0x000800

   RAMGS0           : origin = 0x00C000, length = 0x002000
   RAMGS1           : origin = 0x00E000, length = 0x002000
   RAMGS2           : origin = 0x010000, length = 0x002000
   RAMGS3           : origin = 0x012000, length = 0x001FF8
//   RAMGS3_RSVD      : origin = 0x013FF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080
}

/*You can arrange the .text, .cinit, .const, .pinit, .switch and .econst to FLASH when RAM is filled up.*/
SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0
   .TI.ramfunc      : > RAMM0      PAGE = 0
   .text            : >>RAMLS3 | RAMLS4 | RAMLS7 | RAMM0,   PAGE = 0
   .cinit           : > RAMM0,     PAGE = 0
   .switch          : > RAMM0,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,     PAGE = 1

   #if defined(__TI_EABI__)
   .bss             : > RAMLS5,     PAGE = 1
   .bss:output      : > RAMLS5,     PAGE = 1
   .init_array      : > RAMM0,      PAGE = 0
   .const           : > RAMLS6,     PAGE = 1
   .data            : > RAMLS6,     PAGE = 1
   .sysmem          : > RAMLS6,     PAGE = 1
   .bss:cio         : > RAMLS5,     PAGE = 1
#else
   .pinit           : > RAMM0,      PAGE = 0
   .ebss            : >>RAMLS5 | RAMLS6,     PAGE = 1
   .econst          : > RAMLS6,     PAGE = 1
   .esysmem         : > RAMLS6,     PAGE = 1
   .cio             : > RAMLS5,     PAGE = 1
#endif

   ramgs0           : > RAMGS0,    PAGE = 1
   ramgs1           : > RAMGS1,    PAGE = 1

   dclfuncs         : > RAMLS5,     PAGE = 1

   // CLA Sections
   Cla1Prog         : > RAMLS0,           PAGE = 0
   .scratchpad      : > RAMLS1,           PAGE = 1
   .bss_cla         : > RAMLS1,           PAGE = 1
   .const_cla       : > RAMLS1,           PAGE = 1
   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1
   Cla1DataRam      : > RAMLS2,           PAGE = 1
   cla_shared       : > RAMLS1,           PAGE = 1
   CLADataLS1       : > RAMLS1,           PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
