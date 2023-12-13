//#############################################################################
//
// FILE:    dsp_examples_vector_lnk.cmd.cmd
//
// TITLE:   Linker Command File for the DSP library examples that run 
//          on the 280015x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          280015x
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

   RAMM01           : origin = 0x00000128, length = 0x000006D0
   //RAMM1            : origin = 0x00000400, length = 0x000003F8
   // RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS            : origin = 0x00008000, length = 0x00003FF8
   //RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
   // RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
   //TODO

}

SECTIONS
{
	codestart       : > BEGIN

	.reset           : > RESET     TYPE = DSECT // not used
	.stack           : > RAMLS

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

	FpuRegsFile 	 : > RAMLS
}
