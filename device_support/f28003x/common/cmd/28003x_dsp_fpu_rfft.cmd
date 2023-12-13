MEMORY
{
   BEGIN           	: origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM0            : origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080


   RAMLS0           : origin = 0x00008000, length = 0x00000800
   RAMLS1           : origin = 0x00008800, length = 0x00000800
   RAMLS2           : origin = 0x00009000, length = 0x00000800
   RAMLS3           : origin = 0x00009800, length = 0x00000800
   RAMLS4           : origin = 0x0000A000, length = 0x00000800
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800

   RAMGS0           : origin = 0x0000C000, length = 0x00001000
   RAMGS1           : origin = 0x0000D000, length = 0x00001000
   RAMGS2           : origin = 0x0000E000, length = 0x00001000
   RAMGS3           : origin = 0x0000F000, length = 0x00001000

   BOOTROM          : origin = 0x003F8000, length = 0x00007FC0
   SECURE_ROM       : origin = 0x003F2000, length = 0x00006000


   RESET            : origin = 0x003FFFC0, length = 0x00000002

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
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000

   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000

  /* BANK 2 */
   FLASH_BANK2_SEC0  : origin = 0x0A0000, length = 0x001000
   FLASH_BANK2_SEC1  : origin = 0x0A1000, length = 0x001000
   FLASH_BANK2_SEC2  : origin = 0x0A2000, length = 0x001000
   FLASH_BANK2_SEC3  : origin = 0x0A3000, length = 0x001000
   FLASH_BANK2_SEC4  : origin = 0x0A4000, length = 0x001000
   FLASH_BANK2_SEC5  : origin = 0x0A5000, length = 0x001000
   FLASH_BANK2_SEC6  : origin = 0x0A6000, length = 0x001000
   FLASH_BANK2_SEC7  : origin = 0x0A7000, length = 0x001000
   FLASH_BANK2_SEC8  : origin = 0x0A8000, length = 0x001000
   FLASH_BANK2_SEC9  : origin = 0x0A9000, length = 0x001000
   FLASH_BANK2_SEC10 : origin = 0x0AA000, length = 0x001000
   FLASH_BANK2_SEC11 : origin = 0x0AB000, length = 0x001000
   FLASH_BANK2_SEC12 : origin = 0x0AC000, length = 0x001000
   FLASH_BANK2_SEC13 : origin = 0x0AD000, length = 0x001000
   FLASH_BANK2_SEC14 : origin = 0x0AE000, length = 0x001000
   FLASH_BANK2_SEC15 : origin = 0x0AF000, length = 0x001000

}


SECTIONS
{
   codestart       : > BEGIN
   .reset          : > RESET,       TYPE = DSECT // not used
   .stack          : > RAMLS6

#if defined(RAM)
   .TI.ramfunc      : > RAMM0
   .text            : >> RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4
   .cinit           : > RAMLS3
   .switch          : > RAMM0

	#if defined(__TI_EABI__)
	   .bss             : >> RAMLS2 | RAMGS3
	   .bss:output      : > RAMLS5
	   .init_array      : > RAMM0
	   .const           : > RAMGS3
	   .data            : > RAMLS5
	   .sysmem          : > RAMLS5
	  .bss:cio          : > RAMLS0
	#else
	   .pinit           : > RAMM0
	   .ebss            : > RAMLS5
	   .econst          : > RAMLS5
	   .esysmem         : > RAMLS5
	   .cio             : > RAMLS0
	#endif

	#if !defined(ROMTABLES)
	   FPUfftTables    : > RAMGS2
	#endif //ROMTABLES

	FPUmathTables   : > RAMGS3


#elif defined(_FLASH)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4,   ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC1,  ALIGN(8)

	#if defined(__TI_EABI__)
	   .init_array      : > FLASH_BANK0_SEC1,  ALIGN(8)
	   .bss             : > RAMLS5
	   .bss:output      : > RAMLS3
	   .bss:cio         : > RAMLS0
	   .data            : > RAMLS5
	   .sysmem          : > RAMLS5
	   .const           : > FLASH_BANK0_SEC4,  ALIGN(8)
	#else
	   .pinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
	   .ebss            : > RAMLS5
	   .esysmem         : > RAMLS5
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
	   FPUfftTables    : LOAD = FLASH_BANK0_SEC1,
						 RUN = RAMGS2,
						 RUN_START(FPUfftTablesRunStart),
						 LOAD_START(FPUfftTablesLoadStart),
						 LOAD_SIZE(FPUfftTablesLoadSize),
	#endif //ROMTABLES

   FPUmathTables    : LOAD = FLASH_BANK0_SEC1,
                     RUN = RAMGS3,
                     RUN_START(FPUmathTablesRunStart),
                     LOAD_START(FPUmathTablesLoadStart),
                     LOAD_SIZE(FPUmathTablesLoadSize),
#endif //defined(RAM)   // Example specific section

#if defined(FFT_ALIGN)
   FFT_buffer_1     : > RAMGS0,    ALIGN = FFT_ALIGN
#elif defined(FFT_UNALIGN)
    // Create a hole of size 10 at the beginnning of the FFT_buffer_1 section,
    // the linker will force the actual data to start at a new page, so you
    // may see a hole > 0xA in the .map file. Note that this is done purely
    // to demonstrate the unaligned FFT functions
    FFT_buffer_1:{.+=0xA;}> RAMGS0
#else
#error The FFT example requires the user to either define FFT_ALIGN to \
4(double precision) * 1(real) * size of the FFT, for double precision \
routines and 2(single precision) * 1(real) * size of the FFT, for \
single precision routines. \.
For example, for a 128 point FFT, FFT_ALIGN=512 for DP, and FFT_ALIGN=256\
for SP. If using the unaligned version of the complex FFT, FFT_UNALIGN must be\
defined instead. FFT_ALIGN or FFT_UNALIGN is defined in the project \
properties \
C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif

FFT_buffer_2     : > RAMGS1
FpuRegsFile 	 : > RAMGS2
}
//
//===========================================================================
// End of file.
//===========================================================================
//
