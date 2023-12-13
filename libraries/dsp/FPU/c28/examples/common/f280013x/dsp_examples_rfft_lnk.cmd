//#############################################################################
//
// FILE:    dsp_examples_rfft_lnk.cmd.cmd
//
// TITLE:   Linker Command File for the DSP library examples that run 
//          on the 280013x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          280013x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
// NOTES:
//    In addition to this memory linker command file, add the header linker 
//    command file directly to the project. The header linker command file is 
//    required to link the peripheral structures to the proper locations within
//    the memory map. This is necessary when using bit field headers over 
//    driverlib
//    
//    The header linker files are found in 
//    C2000Ware\device_support\F280013x\<version>\F280013x_headers\cmd
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################

MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM01           : origin = 0x00000128, length = 0x00000658
   //RAMM1            : origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080

   RAMLS            : origin = 0x00008000, length = 0x00003FF8
   //RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
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
   codestart       : > BEGIN
   .reset          : > RESET,       TYPE = DSECT // not used
   .stack          : > RAMLS
 
#if defined(RAM)
   .TI.ramfunc      : > RAMM01
   .text            : >> RAMLS
   .cinit           : > RAMLS
   .switch          : > RAMM01

	#if defined(__TI_EABI__)
	   .bss             : >> RAMLS
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

	#if !defined(ROMTABLES)
	   FPUfftTables    : > RAMLS
	#endif //ROMTABLES
	
	FPUmathTables   : > RAMLS


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

	#if !defined(ROMTABLES)
	   FPUfftTables    : LOAD = FLASH_BANK0_SEC_0_7,
						 RUN = RAMLS,
						 RUN_START(FPUfftTablesRunStart),
						 LOAD_START(FPUfftTablesLoadStart),
						 LOAD_SIZE(FPUfftTablesLoadSize),
	#endif //ROMTABLES

   FPUmathTables    : LOAD = FLASH_BANK0_SEC_0_7,
                     RUN = RAMLS,
                     RUN_START(FPUmathTablesRunStart),
                     LOAD_START(FPUmathTablesLoadStart),
                     LOAD_SIZE(FPUmathTablesLoadSize),
#endif //defined(RAM)   // Example specific section

#if defined(FFT_ALIGN)
   FFT_buffer_1     : > RAMLS,    ALIGN = FFT_ALIGN
#elif defined(FFT_UNALIGN)
    // Create a hole of size 10 at the beginnning of the FFT_buffer_1 section,
    // the linker will force the actual data to start at a new page, so you
    // may see a hole > 0xA in the .map file. Note that this is done purely
    // to demonstrate the unaligned FFT functions
    FFT_buffer_1:{.+=0xA;}> RAMLS
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

FFT_buffer_2     : > RAMLS
FpuRegsFile 	 : > RAMLS
}
//
//===========================================================================
// End of file.
//===========================================================================
//
