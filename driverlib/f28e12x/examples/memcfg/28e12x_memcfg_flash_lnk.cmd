MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x080000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x000126     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x000128, length = 0x0002D8
   RAMM1            : origin = 0x000400, length = 0x000400
   
   RAMGS0           : origin = 0x00C000, length = 0x001800

   /* Flash Banks */
   FLASH_BANK0_SEC_0_63      : origin = 0x080002, length = 0xFFFE

   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .switch          : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM0
#if defined(__TI_EABI__)
   .bss             : > RAMGS0
   .bss:output      : > RAMGS0
   .init_array      : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .const           : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .data            : > RAMGS0
   .sysmem          : > RAMGS0
#else
   .pinit           : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .ebss            : > RAMGS0
   .econst          : > FLASH_BANK0_SEC_0_63, ALIGN(8)
   .esysmem         : > RAMGS0
#endif

   ramgs0 : >> RAMGS0

   #if defined(__TI_EABI__)
       .TI.ramfunc : {} LOAD = FLASH_BANK0_SEC_0_63,
                        RUN = RAMGS0,
                        LOAD_START(RamfuncsLoadStart),
                        LOAD_SIZE(RamfuncsLoadSize),
                        LOAD_END(RamfuncsLoadEnd),
                        RUN_START(RamfuncsRunStart),
                        RUN_SIZE(RamfuncsRunSize),
                        RUN_END(RamfuncsRunEnd),
                        ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASH_BANK0_SEC_0_63,
                        RUN = RAMGS0,
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart),
                        RUN_SIZE(_RamfuncsRunSize),
                        RUN_END(_RamfuncsRunEnd),
                        ALIGN(8)
   #endif

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
