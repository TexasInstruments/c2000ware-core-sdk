-stack 0x300
-heap 0x1C0

MEMORY
{
   BEGIN            : origin = 0x00080000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8
   // RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS01          : origin = 0x00008000, length = 0x00003FF8
   // RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC_0_7     : origin = 0x080002, length = 0x1FFE
   FLASH_BANK0_SEC_8_15    : origin = 0x082000, length = 0x2000
   FLASH_BANK0_SEC_16_23   : origin = 0x084000, length = 0x2000
   FLASH_BANK0_SEC_24_31   : origin = 0x086000, length = 0x2000
   FLASH_BANK0_SEC_32_39   : origin = 0x088000, length = 0x2000
   FLASH_BANK0_SEC_40_79   : origin = 0x08A000, length = 0x8000
   // FLASH_BANK0_SEC_48_55   : origin = 0x08C000, length = 0x2000
   // FLASH_BANK0_SEC_56_63   : origin = 0x08E000, length = 0x2000
   // FLASH_BANK0_SEC_64_71   : origin = 0x090000, length = 0x2000
   // FLASH_BANK0_SEC_72_79   : origin = 0x092000, length = 0x2000
   FLASH_BANK0_SEC_80_87   : origin = 0x094000, length = 0x2000
   FLASH_BANK0_SEC_88_95   : origin = 0x096000, length = 0x2000
   FLASH_BANK0_SEC_96_103  : origin = 0x098000, length = 0x2000
   FLASH_BANK0_SEC_104_111 : origin = 0x09A000, length = 0x2000
   FLASH_BANK0_SEC_112_119 : origin = 0x09C000, length = 0x2000
   FLASH_BANK0_SEC_120_127 : origin = 0x09E000, length = 0x1FF0
   // FLASH_BANK0_SEC_127_RSVD : origin = 0x09FFF0, length = 0x0010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

}


SECTIONS
{
   codestart        : > BEGIN,              ALIGN(8)
   .text            : >> FLASH_BANK0_SEC_8_15  |
                         FLASH_BANK0_SEC_16_23 |
                         FLASH_BANK0_SEC_24_31, ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC_0_7,   ALIGN(8)
   .switch          : > FLASH_BANK0_SEC_0_7,   ALIGN(8)
   .reset           : > RESET,                 TYPE = DSECT

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0_SEC_0_7,    ALIGN(8)
   .bss             : > RAMLS01
   .bss:output      : > RAMLS01
   .bss:cio         : > RAMLS01
   .data            : > RAMLS01
   .sysmem          : > RAMM0
   .const           : >> FLASH_BANK0_SEC_32_39, ALIGN(8)
#else
   .pinit           : > FLASH_BANK0_SEC_0_7,    ALIGN(8)
   .ebss            : > RAMLS01
   .esysmem         : > RAMLS01
   .cio             : > RAMLS01
   .econst          : >> FLASH_BANK0_SEC_32_39, ALIGN(8)
#endif

   .rodata.tvm      : >> FLASH_BANK0_SEC_40_79, ALIGN(8)

   UNION {
      FFT_buffer_1
      .bss.noinit.tvm  : {}
   } > RAMLS01

   FPUfftTables     : >> FLASH_BANK0_SEC_96_103 | FLASH_BANK0_SEC_104_111, ALIGN(8)
   FPUmathTables    : >  FLASH_BANK0_SEC_104_111, ALIGN(8)
   IQmath           : >  FLASH_BANK0_SEC_112_119, ALIGN(8)
   IQmathTables     : >  FLASH_BANK0_SEC_112_119 | FLASH_BANK0_SEC_120_127, ALIGN(8)

#if defined(__TI_EABI__)
   /* Flash_initModule MUST run from RAM - DSP lib funcs run from Flash (slower but necessary) */
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC_88_95,
                      RUN = RAMM0,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)
#else
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC_88_95,
                      RUN = RAMM0,
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                      ALIGN(8)
#endif

}
