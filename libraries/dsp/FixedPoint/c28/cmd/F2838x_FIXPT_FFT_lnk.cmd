/*
For complex FFT, set FFT_ALIGN = 4N
       real FFT, set FFT_ALIGN = 2N
*/
--define=FFT_ALIGN=0x80
MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AE     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001B0, length = 0x000250
   RAMM1            : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMD0            : origin = 0x00C000, length = 0x000800
   RAMD1            : origin = 0x00C800, length = 0x000800

   RAMLS           : origin = 0x008000, length = 0x004000
//   RAMLS1           : origin = 0x008800, length = 0x000800
//   RAMLS2           : origin = 0x009000, length = 0x000800
//   RAMLS3           : origin = 0x009800, length = 0x000800
//   RAMLS4567           : origin = 0x00A000, length = 0x002000

   RAMGS           : origin = 0x00D000, length = 0x010000

//	RAMGS234			: origin = 0x00F000, length = 0x003000

 //  RAMGS567           : origin = 0x012000, length = 0x003000

//   RAMGS89          : origin = 0x015000, length = 0x002000
//   RAMGS1011        : origin = 0x017000, length = 0x002000
//   RAMGS12131415          : origin = 0x019000, length = 0x004000


   /* Flash sectors */
//   FLASH0           : origin = 0x080000, length = 0x002000  /* on-chip Flash */
//   FLASH1           : origin = 0x082000, length = 0x002000  /* on-chip Flash */
//   FLASH2           : origin = 0x084000, length = 0x002000  /* on-chip Flash */
	FLASH012		  : origin = 0x080000, length = 0x006000
//   FLASH3           : origin = 0x086000, length = 0x002000  /* on-chip Flash */
//   FLASH4           : origin = 0x088000, length = 0x008000  /* on-chip Flash */
//   FLASH5           : origin = 0x090000, length = 0x008000  /* on-chip Flash */
	FLASH345			: origin  = 0x086000, length = 0x012000
   FLASH6           : origin = 0x098000, length = 0x008000  /* on-chip Flash */
   FLASH7           : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */
   FLASH8           : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
   FLASH9           : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
   FLASH10          : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
   FLASH11          : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */
   FLASH12          : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */
   FLASH13          : origin = 0x0BE000, length = 0x002000  /* on-chip Flash */
   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .reset           : > RESET, TYPE = DSECT // not used,
#if defined(RAM)
   .text            : >> RAMD0 | RAMD1 |  RAMLS| RAMGS
   .cinit           : > RAMLS
   .switch          : > RAMM0
   .stack           : > RAMLS
   .TI.ramfunc		: > RAMLS
#if defined(__TI_EABI__)
   .bss             : >>RAMGS
   .bss:output      : > RAMGS
   .init_array      : > RAMM0
   .const           : >> RAMGS
   .data            : >> RAMLS
   .sysmem          : > RAMLS
#else
   .pinit           : > RAMM0
   .ebss            : >> RAMGS
   .econst          : > RAMGS
   .esysmem         : > RAMGS
#endif

   // The following section definition are for SDFM examples
   Filter_RegsFile  : > RAMGS
   Filter1_RegsFile : > RAMGS, fill=0x1111
   Filter2_RegsFile : > RAMGS, fill=0x2222
   Filter3_RegsFile : > RAMGS, fill=0x3333
   Filter4_RegsFile : > RAMGS, fill=0x4444
   Difference_RegsFile : >RAMGS, fill=0x3333

#elif defined(_FLASH)
	.text 			:> FLASH012
	.cinit			:> FLASH012 | FLASH345
	.switch			:> FLASH012
	.stack			:> RAMM1
	.data			 : >> RAMGS
	.sysmem			:> 	FLASH012
	#if defined(__TI_EABI__)
   		.bss             : >> RAMGS
   		.bss:output      : > RAMGS
   		.init_array      : > FLASH345
   		.const           : >> FLASH012
   		.sysmem          : > FLASH012
		.TI.ramfunc		 : {}	LOAD = FLASH012,
							RUN = RAMM0,
							LOAD_START(RamfuncsLoadStart),
                        	LOAD_SIZE(RamfuncsLoadSize),
                        	LOAD_END(RamfuncsLoadEnd),
                        	RUN_START(RamfuncsRunStart),
                        	RUN_SIZE(RamfuncsRunSize),
                        	RUN_END(RamfuncsRunEnd),
                        	ALIGN(4)
	#else
   		.pinit           : > FLASH012
   		.ebss            : > RAMGS
   		.cio 			 : > RAMGS
   		.econst          : > FLASH345
   		.esysmem         : > FLASH345
		.TI.ramfunc		 :{}	LOAD = FLASH012,
							RUN = RAMM0,
							LOAD_START(_RamfuncsLoadStart),
                        	LOAD_SIZE(_RamfuncsLoadSize),
                       	 	LOAD_END(_RamfuncsLoadEnd),
                       		 RUN_START(_RamfuncsRunStart),
                       	 	RUN_SIZE(_RamfuncsRunSize),
                        	RUN_END(_RamfuncsRunEnd),
                       		 ALIGN(4)
	#endif//TI_EABI



   // The following section definition are for SDFM examples
   Filter_RegsFile  : > FLASH345
   Filter1_RegsFile : > FLASH345
   Filter2_RegsFile : > FLASH345
   Filter3_RegsFile : > FLASH345
   Filter4_RegsFile : > FLASH345
   Difference_RegsFile : >FLASH345
#endif//RAM


    ramgs0 			: > RAMGS, type=NOINIT
    ramgs1 			: > RAMGS, type=NOINIT
	FFTipcb 		: >> RAMGS, ALIGN(16384)
	FFTipcbsrc		: >> RAMLS //| RAMD0 | RAMD1
#if defined(RAM)
   FFTtf               : > RAMGS
#elif defined(_FLASH)
   FFTtf               : > FLASH012
#endif //RAM

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT
   MSGRAM_CPU_TO_CM   > CPUTOCMRAM, type=NOINIT
   MSGRAM_CM_TO_CPU   > CMTOCPURAM, type=NOINIT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
