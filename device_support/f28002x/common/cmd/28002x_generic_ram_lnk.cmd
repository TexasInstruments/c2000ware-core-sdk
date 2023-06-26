MEMORY
{
   BEGIN           	: origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126
   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8     /* on-chip RAM block M1 */
// RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   
/* RAMLS4           : origin = 0x0000A000, length = 0x00000800
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800 */

   /* Combining all the LS RAMs */
   RAMLS4567        : origin = 0x0000A000, length = 0x00002000
   RAMGS0           : origin = 0x0000C000, length = 0x000007F8
// RAMGS0_RSVD      : origin = 0x0000C7F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
   
   RESET            : origin = 0x003FFFC0, length = 0x00000002

   // FLASHBANK1       : origin = 0x00080000, length = 0x00010000
   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x000FF8
// FLASH_BANK0_SEC15_RSVD : origin = 0x08FFF0, length = 0x000010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   BOOTROM          : origin = 0x003F0000, length = 0x00008000
   BOOTROM_EXT      : origin = 0x003F8000, length = 0x00007FC0
}


SECTIONS
{
   .text            : > RAMLS4567 | RAMGS0
   .TI.ramfunc      : > RAMM0
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET,                  TYPE = DSECT /* not used, */
   .cio             : > RAMGS0
   codestart        : > BEGIN

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss             : > RAMLS4567
   .bss:output      : > RAMLS4567
   .init_array      : > RAMM0
   .const           : > RAMLS4567 | RAMGS0
   .data            : > RAMLS4567 | RAMGS0
   .sysmem          : > RAMLS4567
#else
   .pinit           : > RAMM0
   .ebss            : > RAMLS4567
   .econst          : > RAMLS4567 | RAMGS0
   .esysmem         : > RAMLS4567
#endif

    ramgs0 : > RAMGS0

    /*  Allocate IQ math areas: */
   IQmath           : > RAMLS4567 | RAMGS0
   IQmathTables     : > RAMLS4567 | RAMGS0
}
/*
//===========================================================================
// End of file.
//===========================================================================
*/
