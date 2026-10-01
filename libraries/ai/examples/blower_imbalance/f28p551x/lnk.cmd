MEMORY
{
   BEGIN            : origin = 0x080000, length = 0x000002

   BOOT_RSVD        : origin = 0x000002, length = 0x000126    
   RAMM0            : origin = 0x000128, length = 0x0002D8
   RAMM1            : origin = 0x000400, length = 0x000400
// RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS01          : origin = 0x008000, length = 0x001000
   RAMLS2345        : origin = 0x009000, length = 0x002000
   RAMLS67          : origin = 0x00B000, length = 0x001000
   RAMLS89          : origin = 0x014000, length = 0x004000

   RAMGS01          : origin = 0x00C000, length = 0x004000

   CLATOCPURAM      : origin = 0x001480, length = 0x000080
   CPUTOCLARAM      : origin = 0x001500, length = 0x000080
   CLATODMARAM      : origin = 0x001680, length = 0x000080
   DMATOCLARAM      : origin = 0x001700, length = 0x000080

   RESET            : origin = 0x3FFFC0, length = 0x000002

   FLASH_BANK0     : origin = 0x080002, length = 0x01FFFE     
   FLASH_BANK2     : origin = 0x0C0000, length = 0x020000     
   FLASH_BANK4     : origin = 0x100000, length = 0x008000     
}


SECTIONS
{
   codestart        : > BEGIN
   .cinit           : > FLASH_BANK0, ALIGN(8)
   .switch          : > FLASH_BANK0, ALIGN(8)
   .text            : >> FLASH_BANK0, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0, ALIGN(8)
   .const           : > FLASH_BANK0, ALIGN(8)
   .bss             : > RAMLS2345
   .bss:output      : > RAMLS2345
   .data            : > RAMLS2345
   .sysmem          : > RAMLS2345
#else
   .pinit           : > FLASH_BANK0, ALIGN(8)
   .econst          : > FLASH_BANK0, ALIGN(8)
   .ebss            : > RAMLS2345
   .esysmem         : > RAMLS2345
#endif

   .rodata.tvm      : >> FLASH_BANK2, ALIGN(8)
   .bss.noinit.tvm  : > RAMLS89

   FFT_buffer_1     : > RAMGS01
   FPUfftTables     : > RAMGS01

   #if defined(__TI_EABI__)
   GROUP{
       .TI.ramfunc :
       {-l c28x_fpu_dsp_library_eabi.lib}
       {-l rts2800_fpu32_fast_supplement_eabi.lib}
   }
            LOAD = FLASH_BANK0,
            RUN = RAMLS01,
            LOAD_START(RamfuncsLoadStart),
            LOAD_SIZE(RamfuncsLoadSize),
            LOAD_END(RamfuncsLoadEnd),
            RUN_START(RamfuncsRunStart),
            RUN_SIZE(RamfuncsRunSize),
            RUN_END(RamfuncsRunEnd),
            ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASH_BANK0,
                        RUN = RAMLS01,
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart),
                        RUN_SIZE(_RamfuncsRunSize),
                        RUN_END(_RamfuncsRunEnd),
                        ALIGN(8)
   #endif

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
