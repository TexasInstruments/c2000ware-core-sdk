MEMORY
{
   BEGIN            : origin = 0x080000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF    
   RAMM0            : origin = 0x0001B1, length = 0x00024F    
   RAMM1            : origin = 0x000400, length = 0x0003F8
// RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMD0            : origin = 0x00C000, length = 0x000800    
   RAMD1            : origin = 0x00C800, length = 0x000800
   RAMLS01          : origin = 0x008000, length = 0x001000
   RAMLS2345        : origin = 0x009000, length = 0x002000
   RAMLS67          : origin = 0x00B000, length = 0x001000

   RAMGS04          : origin = 0x00D000, length = 0x005000
   RAMGS57          : origin = 0x012000, length = 0x003000
   RAMGS8           : origin = 0x015000, length = 0x001000
   RAMGS9           : origin = 0x016000, length = 0x001000
   RAMGS10          : origin = 0x017000, length = 0x001000
   RAMGS11          : origin = 0x018000, length = 0x001000
   RAMGS12          : origin = 0x019000, length = 0x001000
   RAMGS13          : origin = 0x01A000, length = 0x001000
   RAMGS14          : origin = 0x01B000, length = 0x001000
   RAMGS15          : origin = 0x01C000, length = 0x000FF8
// RAMGS15_RSVD     : origin = 0x01CFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800
   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800

   RESET            : origin = 0x3FFFC0, length = 0x000002

   FLASH0           : origin = 0x080002, length = 0x001FFE     
   FLASH1           : origin = 0x082000, length = 0x002000     
   FLASH2           : origin = 0x084000, length = 0x002000     
   FLASH3           : origin = 0x086000, length = 0x002000     
   FLASH4           : origin = 0x088000, length = 0x008000     
   FLASH5           : origin = 0x090000, length = 0x008000     
   FLASH6           : origin = 0x098000, length = 0x008000    
   FLASH7           : origin = 0x0A0000, length = 0x008000    
   FLASH8           : origin = 0x0A8000, length = 0x008000    
   FLASH9           : origin = 0x0B0000, length = 0x008000    
   FLASH10          : origin = 0x0B8000, length = 0x002000     
   FLASH11          : origin = 0x0BA000, length = 0x002000     
   FLASH12          : origin = 0x0BC000, length = 0x002000     
   FLASH13          : origin = 0x0BE000, length = 0x001FF0     
// FLASH13_RSVD     : origin = 0x0BFFF0, length = 0x000010     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{
   codestart        : > BEGIN
   .cinit           : > FLASH1, ALIGN(8)
   .switch          : > FLASH1, ALIGN(8)

   .text            : >> FLASH2 | FLASH3 | FLASH4 | FLASH5, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT /* not used */
   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH1, ALIGN(8)
   .const           : > FLASH1, ALIGN(8)
   .bss             : > RAMLS2345
   .bss:output      : > RAMLS2345
   .data            : > RAMLS2345
   .sysmem          : > RAMLS2345
#else
   .pinit           : > FLASH1, ALIGN(8)
   .econst          : > FLASH1, ALIGN(8)
   .ebss            : > RAMLS2345
   .esysmem         : > RAMLS2345
#endif

   .rodata.tvm      : >> FLASH6 | FLASH7 | FLASH8 | FLASH9, ALIGN(8)
   .bss.noinit.tvm  : > RAMGS04

   FFT_buffer_1     : > RAMGS57, ALIGN = 512
   FPUfftTables     : > RAMGS57

   #if defined(__TI_EABI__)
   GROUP{
       .TI.ramfunc :
       {-l c28x_fpu_dsp_library_eabi.lib}
       {-l rts2800_fpu32_fast_supplement_eabi.lib}
   }
            LOAD = FLASH2,
            RUN = RAMLS01,
            LOAD_START(RamfuncsLoadStart),
            LOAD_SIZE(RamfuncsLoadSize),
            LOAD_END(RamfuncsLoadEnd),
            RUN_START(RamfuncsRunStart),
            RUN_SIZE(RamfuncsRunSize),
            RUN_END(RamfuncsRunEnd),
            ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASH2,
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
