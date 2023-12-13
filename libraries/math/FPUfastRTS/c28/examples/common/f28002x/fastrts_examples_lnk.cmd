MEMORY
{

   BOOT_RSVD		: origin = 0x00000000, length = 0x00000050
   RAMM0           	: origin = 0x00000050, length = 0x000003B0

   RAMLS4567        : origin = 0x0000A000, length = 0x00002000
   
   RESET           	: origin = 0x003FFFC0, length = 0x00000002

   FLASHBANK1 		: origin = 0x00080000, length = 0x00010000
   BOOTROM			: origin = 0x003F0000, length = 0x00008000
   BOOTROM_EXT		: origin = 0x003F8000, length = 0x00007FC0


   RAMM1           	: origin = 0x00000400, length = 0x00000380
   BOOT_RSVD_SYSBIOS: origin = 0x00000780, length = 0x00000080
   RAMGS0     	   	: origin = 0x0000C000, length = 0x00000800

}


SECTIONS
{
   .text            : > RAMLS4567
 #ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
		.TI.ramfunc		: > RAMM0
	#else
		ramfuncs		: > RAMM0 
	#endif 
#endif	

   .cinit           : > RAMM1
   .switch          : > RAMM0
   .reset           : > RESET,					TYPE = DSECT /* not used, */
   .cio				: > RAMGS0
   codestart		: > BOOT_RSVD

//   .stack           : > RAMLS4567
    .sysmem			: > RAMLS4567 | RAMM0 | RAMM1
#if defined(__TI_EABI__)
   .bss             : >> RAMLS4567 | RAMM0 | RAMM1 | RAMGS0
   .bss:output      : > RAMLS4567
   
#else
    .ebss            : > RAMLS4567
   .esysmem         : > RAMLS4567
#endif   
 
#if defined(__TI_EABI__)
   .init_array	    : > RAMM0
   .const           : >> RAMGS0 | RAMLS4567 | RAMM0 | RAMM1
#else 
	.pinit			: > RAMM0
	.econst			: > RAMGS0 | RAMLS4567 | RAMM0 | RAMM1
#endif 

   .data			: > RAMLS4567 | RAMM0 | RAMM1


#if !defined(RAM_ROMTABLES)
    FPUmathTables   : >> RAMM0 | RAMM1 | RAMLS4567
#endif
	ramgs0 : > RAMGS0

    /*  Allocate IQ math areas: */
//   IQmath			: > RAMLS4567
 //  IQmathTables		: > RAMLS4567
}
