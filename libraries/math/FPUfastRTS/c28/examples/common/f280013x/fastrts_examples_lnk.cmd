MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080

   RAMLS0           : origin = 0x00008000, length = 0x00002000
   RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
   RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   FPU32_FAST_TABLES     	: origin = 0x3FAE7C, length = 0x00081A

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
codestart       : > BEGIN

.reset           : > RESET     TYPE = DSECT // not used
.stack           : > RAMM1


#if defined(RAM)
   .TI.ramfunc      : > RAMM1
   .text            : >> RAMLS0
   .cinit           : > RAMM0
   .switch          : > RAMM0

	#if defined(__TI_EABI__)
	   .bss             : >> RAMLS1
	   .bss:output      : > RAMLS1
	   .init_array      : > RAMM1
	   .const           : > RAMLS0
	   .data            : > RAMLS0
	   .sysmem          : > RAMLS1
	  .bss:cio          : > RAMLS0
	#else
	   .pinit           : > RAMM1
	   .ebss            : > RAMLS0
	   .econst          : > RAMLS1
	   .esysmem         : > RAMLS1
	   .cio             : > RAMLS1
	#endif

	#if !defined(ROMTABLES)
	  FPUmathTables   : >> RAMM0 | RAMLS1
	#else
	  FPUmathTables	   : > FPU32_FAST_TABLES
	#endif //ROMTABLES

#elif defined(_FLASH)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4,   ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC1,  ALIGN(8)


	#if defined(__TI_EABI__)
	   .init_array      : > FLASH_BANK0_SEC1,  ALIGN(8)
	   .bss             : > RAMLS0
	   .bss:output      : > RAMLS0
	   .bss:cio         : > RAMLS0
	   .data            : > RAMLS1
	   .sysmem          : > RAMLS1
	   .const           : > FLASH_BANK0_SEC4,  ALIGN(8)
	#else
	   .pinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
	   .ebss            : > RAMLS0
	   .esysmem         : > RAMLS1
	   .cio             : > RAMLS0
	   .econst          : > FLASH_BANK0_SEC4,  ALIGN(8)
	#endif
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
				  RUN = RAMLS0,
				  LOAD_START(RamfuncsLoadStart),
				  LOAD_SIZE(RamfuncsLoadSize),
				  LOAD_END(RamfuncsLoadEnd),
				  RUN_START(RamfuncsRunStart),
				  RUN_SIZE(RamfuncsRunSize),
				  RUN_END(RamfuncsRunEnd),
				  ALIGN(8)
				  
	#if !defined(ROMTABLES)
	   FPUmathTables    : LOAD = FLASH_BANK0_SEC1,
						  RUN = RAMLS1,
						  RUN_START(FPUmathTablesRunStart),
						  LOAD_START(FPUmathTablesLoadStart),
						  LOAD_SIZE(FPUmathTablesLoadSize),
						 

	#endif //ROMTABLES

#endif //defined(RAM)

FpuRegsFile 	 : > RAMLS1
}
