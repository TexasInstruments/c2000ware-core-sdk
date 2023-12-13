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

 codestart        : > RAMM0
   .text            : >> RAMM0 | RAMM1 | RAMLS4567 | RAMGS0
   .cinit           : > RAMGS0
   .switch          : > RAMM0
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM1 | RAMLS4567
#if defined(__TI_EABI__)
   .bss             : > RAMLS4567
   .bss:output      : > RAMLS4567
   .init_array      : > RAMM0
   .const           : > RAMLS4567
   .data            : > RAMLS4567
   .sysmem          : > RAMLS4567
#else
   .pinit           : > RAMM0
   .ebss            : >> RAMLS4567
   .econst          : > RAMLS4567
   .esysmem         : > RAMLS4567
#endif

   ramgs0 : > RAMGS0
   ramgs1 : > RAMGS0

/*
   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM
   MSGRAM_CPU_TO_CM   > CPUTOCMRAM
   MSGRAM_CM_TO_CPU   > CMTOCPURAM
*/

/* The following section definition are for IQMATH */
   IQmath           : > RAMGS0
   IQmathTables     : > RAMGS0 | RAMLS4567
   IQmathTablesRam  : > RAMGS0

   /* The following section definition are for SDFM examples */
   Filter_RegsFile  : > RAMGS0
   Filter1_RegsFile : > RAMGS0, fill=0x1111
   Filter2_RegsFile : > RAMGS0, fill=0x2222
   Filter3_RegsFile : > RAMGS0, fill=0x3333
   Filter4_RegsFile : > RAMGS0, fill=0x4444
   Difference_RegsFile : >RAMGS0, fill=0x3333

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0
   #else
    ramfuncs    : > RAMM0
   #endif
#endif

}
