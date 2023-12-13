MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM01           : origin = 0x00000128, length = 0x00000658
   //RAMM1            : origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080

   RAMLS_BUFFERS    : origin = 0x00008000, length = 0x00002000
   RAMLS           : origin = 0x0000A000, length = 0x00001FF8
   RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
   FLASH_BANK0_SEC_0_7     : origin = 0x080002, length = 0x1FFE  /* on-chip Flash */
   FLASH_BANK0_SEC_8_15    : origin = 0x082000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_16_23   : origin = 0x084000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_24      : origin = 0x086000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_25      : origin = 0x086400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_26      : origin = 0x086800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_27      : origin = 0x086C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_28      : origin = 0x087000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_29      : origin = 0x087400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_30      : origin = 0x087800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_31      : origin = 0x087C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_32      : origin = 0x088080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_33      : origin = 0x088480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_34      : origin = 0x088880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_35      : origin = 0x088C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_36      : origin = 0x089080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_37      : origin = 0x089480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_38      : origin = 0x089880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_39      : origin = 0x089C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_40_47   : origin = 0x08A000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_48_55   : origin = 0x08C000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_56_63   : origin = 0x08E000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_64_71   : origin = 0x090000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_72_79   : origin = 0x092000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_80_87   : origin = 0x094000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_88      : origin = 0x096000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_89      : origin = 0x096400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_90      : origin = 0x096800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_91      : origin = 0x096C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_92      : origin = 0x097000, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_93      : origin = 0x097400, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_94      : origin = 0x097800, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_95      : origin = 0x097C00, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_96      : origin = 0x098080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_97      : origin = 0x098480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_98      : origin = 0x098880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_99      : origin = 0x098C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_100     : origin = 0x099080, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_101     : origin = 0x099480, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_102     : origin = 0x099880, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_103     : origin = 0x099C80, length = 0x0380  /* on-chip Flash */
   FLASH_BANK0_SEC_104_111 : origin = 0x09A000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_112_119 : origin = 0x09C000, length = 0x2000  /* on-chip Flash */
   FLASH_BANK0_SEC_120_127 : origin = 0x09E000, length = 0x1FF0  /* on-chip Flash */

   FLASH_BANK0_SEC_127_RSVD : origin = 0x0A0FF0, length = 0x0010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{
   codestart        : > BEGIN
   .reset           : > RESET,                  TYPE = DSECT /* not used, */
   .stack           : > RAMM01

#if defined(RAM)
	   .TI.ramfunc      : > RAMM01
	   .text            : >> RAMLS
	   .cinit           : > RAMM01
	   .switch          : > RAMM01


	#if defined(__TI_EABI__)
	   .bss             : > RAMLS
	   .bss:output      : > RAMLS
	   .init_array      : > RAMM01
	   .const           : > RAMLS
	   .data            : > RAMLS
	   .sysmem          : > RAMLS
	  .bss:cio          : > RAMLS
	#else
	   .pinit           : > RAMM01
	   .ebss            : > RAMLS
	   .econst          : > RAMLS
	   .esysmem         : > RAMLS
	   .cio             : > RAMLS
	#endif
	
	coefffilt		: > RAMLS, ALIGN(0x100)

#elif defined(_FLASH)
   .text            : >> FLASH_BANK0_SEC_0_7,   ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC_0_7,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC_0_7,  ALIGN(8)

	#if defined(__TI_EABI__)
	   .init_array      : > FLASH_BANK0_SEC_0_7,  ALIGN(8)
	   .bss             : > RAMLS
	   .bss:output      : > RAMLS
	   .bss:cio         : > RAMLS
	   .data            : > RAMLS
	   .sysmem          : > RAMLS
	   .const           : > FLASH_BANK0_SEC_0_7,  ALIGN(8)
	#else
	   .pinit           : > FLASH_BANK0_SEC_0_7,  ALIGN(8)
	   .ebss            : > RAMLS
	   .esysmem         : > RAMLS
	   .cio             : > RAMLS
	   .econst          : > FLASH_BANK0_SEC_0_7,  ALIGN(8)
	#endif

   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC_0_7,
                      RUN = RAMLS,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)
     
	 coefffilt  		:> FLASH_BANK0_SEC_0_7, ALIGN(0x100)
#endif//RAM

   firfilt 			: >> RAMLS_BUFFERS
   firldb 			: > RAMLS_BUFFERS, ALIGN(0x100)
   revcoeff		    : > RAMLS_BUFFERS
   sigIn			: >> RAMLS_BUFFERS
   sigOut			: >> RAMLS_BUFFERS

ramgs0 : > RAMLS
ramgs1 : > RAMLS
}
