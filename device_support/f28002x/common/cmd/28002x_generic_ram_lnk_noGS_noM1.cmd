MEMORY
{
   BOOT_RSVD        : origin = 0x00000000, length = 0x00000050
   RAMM0            : origin = 0x00000050, length = 0x000003B0

/* RAMLS4           : origin = 0x0000A000, length = 0x00000800
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800 */

   /* Combining all the LS RAMs */
   RAMLS4567        : origin = 0x0000A000, length = 0x00002000

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   FLASHBANK1       : origin = 0x00080000, length = 0x00010000
   BOOTROM          : origin = 0x003F0000, length = 0x00008000
   BOOTROM_EXT      : origin = 0x003F8000, length = 0x00007FC0


   RAMM1            : origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080
   RAMGS0           : origin = 0x0000C000, length = 0x00000800
}


SECTIONS
{
   .text            : > RAMLS4567
   .TI.ramfunc      : > RAMM0
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET,                  TYPE = DSECT /* not used, */
   .cio             : > RAMLS4567
   codestart        : > RAMLS4567

   .stack           : > RAMM0
#if defined(__TI_EABI__)
   .bss             : > RAMLS4567
   .bss:output      : > RAMLS4567
   .init_array      : > RAMM0
   .const           : > RAMLS4567
   .data            : > RAMLS4567
   .sysmem          : > RAMLS4567
#else
   .pinit           : > RAMM0
   .ebss            : > RAMLS4567
   .econst          : > RAMLS4567
   .esysmem         : > RAMLS4567
#endif


    /*  Allocate IQ math areas: */
   IQmath           : > RAMLS4567
   IQmathTables     : > RAMLS4567
}
/*
//===========================================================================
// End of file.
//===========================================================================
*/
