MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x000126     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x000128, length = 0x0002D8
   RAMM1            : origin = 0x000400, length = 0x000400
   

   RAMGS0           : origin = 0x00C000, length = 0x001800

   /* Flash Banks */
   FLASH_BANK0_SEC_0_63      : origin = 0x080000, length = 0x10000

   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : > RAMGS0
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM0
#if defined(__TI_EABI__)
   .bss             : > RAMGS0
   .bss:output      : > RAMGS0
   .init_array      : > RAMM0
   .const           : > RAMGS0
   .data            : > RAMGS0
   .sysmem          : > RAMGS0
#else
   .pinit           : > RAMM0
   .ebss            : > RAMGS0
   .econst          : > RAMGS0
   .esysmem         : > RAMGS0
#endif

   ramgs0 : >> RAMGS0

    .TI.ramfunc : {} > RAMM0

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
