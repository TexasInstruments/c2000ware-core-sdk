//#############################################################################
//
// FILE:    dsp_examples_vector_lnk.cmd.cmd
//
// TITLE:   Linker Command File for the DSP library examples that run 
//          on the 28002x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          28002x
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
//    C2000Ware\device_support\F28002x\<version>\F28002x_headers\cmd
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################

MEMORY
{
   BOOT_RSVD		: origin = 0x00000000, length = 0x00000050
   RAMM0           	: origin = 0x00000050, length = 0x000003B0
   
   RAMLS4567        : origin = 0x0000A000, length = 0x00002000
   
   RESET           	: origin = 0x003FFFC0, length = 0x00000002

   FLASHBANK1 		: origin = 0x00080000, length = 0x00010000
   BOOTROM			: origin = 0x003F0000, length = 0x00008000
   BOOTROM_EXT		: origin = 0x003F8000, length = 0x00007FC0


   RAMM1           	: origin = 0x00000400, length = 0x00000380     /* on-chip RAM block M1 */
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080
   RAMGS0     	   	: origin = 0x0000C000, length = 0x00000800
}

SECTIONS
{
#if defined(RAM)
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000	
	.TI.ramfunc : >	RAMM0 | RAMM1	
	#else 
	ramfuncs	: >	RAMM0 | RAMM1
#endif
	
	.cinit		: > RAMM0	
#if defined(__TI_EABI__)	
	.const		: >	RAMGS0	
#else
	.econst		: > RAMGS0 
#endif 

	.data		: >	RAMLS4567	
	.text		: >	RAMLS4567	
	
#if defined(__TI_EABI__)
	.bss		: >>	RAMM1 | RAMM0	
#else
	.ebiss		: >> RAMM1 | RAMM0 
#endif

	.stack		: >	RAMGS0	

#endif
}
