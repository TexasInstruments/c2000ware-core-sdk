MEMORY
{
   BEGIN            : origin = 0x00080000, length = 0x00000008
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8
   // RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS0           : origin = 0x00008000, length = 0x00002000
   RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
   // RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
	// Only sections being used need to be filled
   FLASH_BANK0_SEC_0_7     : origin = 0x080008, length = 0x1FF8, fill=0xFFFF
   FLASH_BANK0_SEC_8_15    : origin = 0x082000, length = 0x2000, fill=0xFFFF
   FLASH_BANK0_SEC_16_23   : origin = 0x084000, length = 0x2000, fill=0xFFFF
   FLASH_BANK0_SEC_24      : origin = 0x086000, length = 0x0380, fill=0xFFFF
   FLASH_BANK0_SEC_25      : origin = 0x086400, length = 0x0380
   FLASH_BANK0_SEC_26      : origin = 0x086800, length = 0x0380
   FLASH_BANK0_SEC_27      : origin = 0x086C00, length = 0x0380
   FLASH_BANK0_SEC_28      : origin = 0x087000, length = 0x0380
   FLASH_BANK0_SEC_29      : origin = 0x087400, length = 0x0380
   FLASH_BANK0_SEC_30      : origin = 0x087800, length = 0x0380
   FLASH_BANK0_SEC_31      : origin = 0x087C00, length = 0x0380
   FLASH_BANK0_SEC_32      : origin = 0x088080, length = 0x0380
   FLASH_BANK0_SEC_33      : origin = 0x088480, length = 0x0380
   FLASH_BANK0_SEC_34      : origin = 0x088880, length = 0x0380
   FLASH_BANK0_SEC_35      : origin = 0x088C80, length = 0x0380
   FLASH_BANK0_SEC_36      : origin = 0x089080, length = 0x0380
   FLASH_BANK0_SEC_37      : origin = 0x089480, length = 0x0380
   FLASH_BANK0_SEC_38      : origin = 0x089880, length = 0x0380
   FLASH_BANK0_SEC_39      : origin = 0x089C80, length = 0x0380
   FLASH_BANK0_SEC_40_47   : origin = 0x08A000, length = 0x2000
   FLASH_BANK0_SEC_48_55   : origin = 0x08C000, length = 0x2000
   FLASH_BANK0_SEC_56_63   : origin = 0x08E000, length = 0x2000
   FLASH_BANK0_SEC_64_71   : origin = 0x090000, length = 0x2000
   FLASH_BANK0_SEC_72_79   : origin = 0x092000, length = 0x2000
   FLASH_BANK0_SEC_80_87   : origin = 0x094000, length = 0x2000
   FLASH_BANK0_SEC_88      : origin = 0x096000, length = 0x0380
   FLASH_BANK0_SEC_89      : origin = 0x096400, length = 0x0380
   FLASH_BANK0_SEC_90      : origin = 0x096800, length = 0x0380
   FLASH_BANK0_SEC_91      : origin = 0x096C00, length = 0x0380
   FLASH_BANK0_SEC_92      : origin = 0x097000, length = 0x0380
   FLASH_BANK0_SEC_93      : origin = 0x097400, length = 0x0380
   FLASH_BANK0_SEC_94      : origin = 0x097800, length = 0x0380
   FLASH_BANK0_SEC_95      : origin = 0x097C00, length = 0x0380
   FLASH_BANK0_SEC_96      : origin = 0x098080, length = 0x0380
   FLASH_BANK0_SEC_97      : origin = 0x098480, length = 0x0380
   FLASH_BANK0_SEC_98      : origin = 0x098880, length = 0x0380
   FLASH_BANK0_SEC_99      : origin = 0x098C80, length = 0x0380
   FLASH_BANK0_SEC_100     : origin = 0x099080, length = 0x0380
   FLASH_BANK0_SEC_101     : origin = 0x099480, length = 0x0380
   FLASH_BANK0_SEC_102     : origin = 0x099880, length = 0x0380
   FLASH_BANK0_SEC_103     : origin = 0x099C80, length = 0x0380
   FLASH_BANK0_SEC_104_111 : origin = 0x09A000, length = 0x2000
   FLASH_BANK0_SEC_112_119 : origin = 0x09C000, length = 0x2000
   FLASH_BANK0_SEC_120_127 : origin = 0x09E000, length = 0x1FF0, fill=0xFFFF


  /* Flash sectors */
	/*
   FLASH_BANK0_SEC_0_7     : origin = 0x080008, length = 0x1FF8
   FLASH_BANK0_SEC_8_15    : origin = 0x082000, length = 0x2000
   FLASH_BANK0_SEC_16_23   : origin = 0x084000, length = 0x2000
   FLASH_BANK0_SEC_24      : origin = 0x086000, length = 0x0380
   FLASH_BANK0_SEC_25      : origin = 0x086400, length = 0x0380
   FLASH_BANK0_SEC_26      : origin = 0x086800, length = 0x0380
   FLASH_BANK0_SEC_27      : origin = 0x086C00, length = 0x0380
   FLASH_BANK0_SEC_28      : origin = 0x087000, length = 0x0380
   FLASH_BANK0_SEC_29      : origin = 0x087400, length = 0x0380
   FLASH_BANK0_SEC_30      : origin = 0x087800, length = 0x0380
   FLASH_BANK0_SEC_31      : origin = 0x087C00, length = 0x0380
   FLASH_BANK0_SEC_32      : origin = 0x088080, length = 0x0380
   FLASH_BANK0_SEC_33      : origin = 0x088480, length = 0x0380
   FLASH_BANK0_SEC_34      : origin = 0x088880, length = 0x0380
   FLASH_BANK0_SEC_35      : origin = 0x088C80, length = 0x0380
   FLASH_BANK0_SEC_36      : origin = 0x089080, length = 0x0380
   FLASH_BANK0_SEC_37      : origin = 0x089480, length = 0x0380
   FLASH_BANK0_SEC_38      : origin = 0x089880, length = 0x0380
   FLASH_BANK0_SEC_39      : origin = 0x089C80, length = 0x0380
   FLASH_BANK0_SEC_40_47   : origin = 0x08A000, length = 0x2000
   FLASH_BANK0_SEC_48_55   : origin = 0x08C000, length = 0x2000
   FLASH_BANK0_SEC_56_63   : origin = 0x08E000, length = 0x2000
   FLASH_BANK0_SEC_64_71   : origin = 0x090000, length = 0x2000
   FLASH_BANK0_SEC_72_79   : origin = 0x092000, length = 0x2000
   FLASH_BANK0_SEC_80_87   : origin = 0x094000, length = 0x2000
   FLASH_BANK0_SEC_88      : origin = 0x096000, length = 0x0380
   FLASH_BANK0_SEC_89      : origin = 0x096400, length = 0x0380
   FLASH_BANK0_SEC_90      : origin = 0x096800, length = 0x0380
   FLASH_BANK0_SEC_91      : origin = 0x096C00, length = 0x0380
   FLASH_BANK0_SEC_92      : origin = 0x097000, length = 0x0380
   FLASH_BANK0_SEC_93      : origin = 0x097400, length = 0x0380
   FLASH_BANK0_SEC_94      : origin = 0x097800, length = 0x0380
   FLASH_BANK0_SEC_95      : origin = 0x097C00, length = 0x0380
   FLASH_BANK0_SEC_96      : origin = 0x098080, length = 0x0380
   FLASH_BANK0_SEC_97      : origin = 0x098480, length = 0x0380
   FLASH_BANK0_SEC_98      : origin = 0x098880, length = 0x0380
   FLASH_BANK0_SEC_99      : origin = 0x098C80, length = 0x0380
   FLASH_BANK0_SEC_100     : origin = 0x099080, length = 0x0380
   FLASH_BANK0_SEC_101     : origin = 0x099480, length = 0x0380
   FLASH_BANK0_SEC_102     : origin = 0x099880, length = 0x0380
   FLASH_BANK0_SEC_103     : origin = 0x099C80, length = 0x0380
   FLASH_BANK0_SEC_104_111 : origin = 0x09A000, length = 0x2000
   FLASH_BANK0_SEC_112_119 : origin = 0x09C000, length = 0x2000
   FLASH_BANK0_SEC_120_127 : origin = 0x09E000, length = 0x1FF0
	*/


   // FLASH_BANK0_SEC_127_RSVD : origin = 0x0A0FF0, length = 0x0010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}

SECTIONS
{
   codestart        : > BEGIN, ALIGN(8)

   .text            : >> FLASH_BANK0_SEC_8_15    | FLASH_BANK0_SEC_16_23   | FLASH_BANK0_SEC_40_47 |
                         FLASH_BANK0_SEC_48_55   | FLASH_BANK0_SEC_56_63   | FLASH_BANK0_SEC_64_71 |
                         FLASH_BANK0_SEC_64_71   | FLASH_BANK0_SEC_72_79   | FLASH_BANK0_SEC_80_87 |
                         FLASH_BANK0_SEC_104_111 | FLASH_BANK0_SEC_112_119 , ALIGN(8)

   .cinit           : > FLASH_BANK0_SEC_24 | FLASH_BANK0_SEC_25 | FLASH_BANK0_SEC_26 | FLASH_BANK0_SEC_27, ALIGN(8)
   .switch          : > FLASH_BANK0_SEC_24 | FLASH_BANK0_SEC_25 | FLASH_BANK0_SEC_26 | FLASH_BANK0_SEC_27, ALIGN(8)

   .reset           : > RESET,  TYPE = DSECT /* not used, */

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .bss             : > RAMLS0
   .bss:output      : > RAMLS0
   .init_array      : >> FLASH_BANK0_SEC_28 | FLASH_BANK0_SEC_29 | FLASH_BANK0_SEC_30 | FLASH_BANK0_SEC_31, ALIGN(8)
   .const           : >> FLASH_BANK0_SEC_120_127, ALIGN(8)
   .data            : > RAMLS0
   .sysmem          : > RAMLS0
  .bss:cio          : > RAMLS0
#else
   .pinit           : >> FLASH_BANK0_SEC_28 | FLASH_BANK0_SEC_29 | FLASH_BANK0_SEC_30 | FLASH_BANK0_SEC_31, ALIGN(8)
   .ebss            : > RAMLS0
   .econst          : >> FLASH_BANK0_SEC_88 | FLASH_BANK0_SEC_89 | FLASH_BANK0_SEC_90 | FLASH_BANK0_SEC_91, ALIGN(8)
   .esysmem         : > RAMLS0
   .cio             : > RAMLS0
#endif

#if defined(__TI_EABI__)
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC_0_7,
                      RUN = RAMLS0,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                       ALIGN(8)
#else
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC_0_7,
                      RUN = RAMLS0,
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                       ALIGN(8)
#endif

    /*  Allocate IQ math areas: */
   IQmath           : > RAMLS1
   IQmathTables     : > RAMLS1
}
