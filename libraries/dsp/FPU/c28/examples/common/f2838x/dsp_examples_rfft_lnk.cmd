//#############################################################################
//
// FILE:    dsp_examples_rfft_lnk.cmd.cmd
//
// TITLE:   Linker Command File for the DSP library examples that run 
//          on the 2838x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          2838x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
// NOTES:
// 1. In addition to this memory linker command file, add the header linker 
//    command file directly to the project. The header linker command file is 
//    required to link the peripheral structures to the proper locations within
//    the memory map. This is necessary when using bit field headers over 
//    driverlib
//    
//    The header linker files are found in 
//    C2000Ware\device_support\f2838x(D/S)\<version>\f2838x_headers\cmd
//    
//    For BIOS applications add:      f2838x(D/S)_Headers_BIOS_cpuX.cmd
//    For nonBIOS applications add:   f2838x(D/S)_Headers_nonBIOS_cpuX.cmd
//
// 2. Memory blocks on f2838x are uniform (ie same physical memory) in both 
//    PAGE 0 and PAGE 1. That is, the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program
//    and/or data.
//    
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################
#if (!defined(RAM) && !defined(_FLASH))
#error Requires either RAM or _FLASH to be defined, do this \
from the project properties, C2000 Linker -> Advanced Options -> \
Command File Preprocessing -> --define. Dont forget to also define the \
variable in the predefined symbols under the compiler setting.
#endif //(!defined(RAM) || !defined(_FLASH))

MEMORY
{
PAGE 0 :
   // BEGIN is used for the "boot to SARAM" bootloader mode
#if defined(RAM)
   BEGIN           : origin = 0x000000, length = 0x000002
#elif defined(_FLASH)
   BEGIN           : origin = 0x080000, length = 0x000002
#endif 
   RAMM0           : origin = 0x000122, length = 0x0002DE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMLS0          : origin = 0x008000, length = 0x000800
   //RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS123        : origin = 0x008800, length = 0x001800
   //RAMLS3          : origin = 0x009800, length = 0x000800
   
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   FLASHA          : origin = 0x080002, length = 0x001FFE // on-chip Flash
   FLASHC          : origin = 0x084000, length = 0x002000 // on-chip Flash
   FLASHD          : origin = 0x086000, length = 0x002000 // on-chip Flash
   FLASHE          : origin = 0x088000, length = 0x008000 // on-chip Flash
   FLASHF          : origin = 0x090000, length = 0x008000 // on-chip Flash
   FLASHG          : origin = 0x098000, length = 0x008000 // on-chip Flash

PAGE 1 :
   FPU             : origin = 0x000F00, length = 0x000100 // FPU registers*/
   // Part of M0, BOOT rom will use this for stack 
   BOOT_RSVD       : origin = 0x000002, length = 0x000120   

   RAMLS4          : origin = 0x00A000, length = 0x000800
   RAMLS567        : origin = 0x00A800, length = 0x001800
   //RAMLS6          : origin = 0x00B000, length = 0x000800
   //RAMLS7          : origin = 0x00B800, length = 0x000800
   
   RAMGS01         : origin = 0x00C000, length = 0x004000
   //RAMGS1          : origin = 0x00E000, length = 0x002000
   RAMGS2          : origin = 0x010000, length = 0x002000
   RAMGS3          : origin = 0x012000, length = 0x002000
   RAMGS4          : origin = 0x014000, length = 0x002000

   FLASHB          : origin = 0x082000, length = 0x002000 // on-chip Flash
}
 
SECTIONS
{
   codestart       : > BEGIN,     PAGE = 0
#if defined(RAM)
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,     PAGE = 0
   #else
    ramfuncs        : > RAMM0,     PAGE = 0
   #endif
#endif
   .text           :>> RAMM1 | RAMLS0 | RAMLS123,
                                  PAGE = 0
   .cinit          : > RAMLS123,  PAGE = 0
   .switch         : > RAMM0,     PAGE = 0   
#if defined(__TI_EABI__)
   .init_array	   : > RAMM0,     PAGE = 0
   .const          : > RAMGS01,   PAGE = 1
#else
   .pinit          : > RAMM0,     PAGE = 0
   .econst         : > RAMGS01,   PAGE = 1
#endif //__TI_EABI__
#if !defined(ROMTABLES)
//#if defined(__TMS320C28XX_FPU64__)
   FPU64fftTables  : > RAMGS2,    PAGE = 1
//#else
  // FPUfftTables    : > RAMGS2,    PAGE = 1
//#endif
#endif //ROMTABLES

#if defined(__TMS320C28XX_FPU64__)
   FPU64mathTables : > RAMGS3,    PAGE = 1
#else
   FPUmathTables   : > RAMGS3,    PAGE = 1
#endif

#elif defined(_FLASH)
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
     #if defined(__TI_EABI__)
        .TI.ramfunc     :  LOAD = FLASHC,
                           RUN = RAMLS123,
                           RUN_START(RamfuncsRunStart),
                           LOAD_START(RamfuncsLoadStart),
                           LOAD_SIZE(RamfuncsLoadSize),
                           PAGE = 0
                           
     #else
        .TI.ramfunc     :  LOAD = FLASHC,
                           RUN = RAMLS123,
                           RUN_START(_RamfuncsRunStart),
                           LOAD_START(_RamfuncsLoadStart),
                           LOAD_SIZE(_RamfuncsLoadSize),
                           PAGE = 0
                           
     #endif
    #else
   ramfuncs        :     LOAD = FLASHC,
                         RUN = RAMLS123,
                         RUN_START(_RamfuncsRunStart),
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         PAGE = 0
                         
   #endif
  #endif
   .text           : > FLASHA,    PAGE = 0
   .cinit          : > FLASHC,    PAGE = 0
#if defined(__TI_EABI__)
   .init_array	   : > FLASHC,    PAGE = 0
   .const          : > FLASHG,    PAGE = 0
#else
   .pinit          : > FLASHC,    PAGE = 0
   .econst         : > FLASHG,    PAGE = 0
#endif //__TI_EABI__
   .switch         : > FLASHC,    PAGE = 0
#if !defined(ROMTABLES)
#if defined(__TMS320C28XX_FPU64__)
  #if defined(__TI_EABI__)
   FPU64fftTables  : LOAD = FLASHB,
                     RUN = RAMGS2,
                     RUN_START(FPU64fftTablesRunStart),
                     LOAD_START(FPU64fftTablesLoadStart),
                     LOAD_SIZE(FPU64fftTablesLoadSize),
                     PAGE = 1
  #else
   FPU64fftTables  : LOAD = FLASHB,
                     RUN = RAMGS2,
                     RUN_START(_FPU64fftTablesRunStart),
                     LOAD_START(_FPU64fftTablesLoadStart),
                     LOAD_SIZE(_FPU64fftTablesLoadSize),
                     PAGE = 1
  #endif
#else
  #if defined(__TI_EABI__)
   FPUfftTables    : LOAD = FLASHB,
                     RUN = RAMGS2,
                     RUN_START(FPUfftTablesRunStart),
                     LOAD_START(FPUfftTablesLoadStart),
                     LOAD_SIZE(FPUfftTablesLoadSize),
                     PAGE = 1
  #else
   FPUfftTables    : LOAD = FLASHB,
                     RUN = RAMGS2,
                     RUN_START(_FPUfftTablesRunStart),
                     LOAD_START(_FPUfftTablesLoadStart),
                     LOAD_SIZE(_FPUfftTablesLoadSize),
                     PAGE = 1
  #endif
#endif
#endif //ROMTABLES
 #if defined(__TMS320C28XX_FPU64__)
  #if defined(__TI_EABI__)
   FPU64mathTables  : LOAD = FLASHB,
                     RUN = RAMGS3,
                     RUN_START(FPU64mathTablesRunStart),
                     LOAD_START(FPU64mathTablesLoadStart),
                     LOAD_SIZE(FPU64mathTablesLoadSize),
                     PAGE = 1
  #else
   FPU64mathTables  : LOAD = FLASHB,
                     RUN = RAMGS3,
                     RUN_START(_FPU64mathTablesRunStart),
                     LOAD_START(_FPU64mathTablesLoadStart),
                     LOAD_SIZE(_FPU64mathTablesLoadSize),
                     PAGE = 1
  #endif
#else
  #if defined(__TI_EABI__)
   FPUmathTables    : LOAD = FLASHB,
                     RUN = RAMGS3,
                     RUN_START(FPUmathTablesRunStart),
                     LOAD_START(FPUmathTablesLoadStart),
                     LOAD_SIZE(FPUmathTablesLoadSize),
                     PAGE = 1
  #else
   FPUmathTables    : LOAD = FLASHB,
                     RUN = RAMGS3,
                     RUN_START(_FPUmathTablesRunStart),
                     LOAD_START(_FPUmathTablesLoadStart),
                     LOAD_SIZE(_FPUmathTablesLoadSize),
                     PAGE = 1
  #endif
#endif
#endif //defined(RAM)
   FpuRegsFile      : > FPU,       PAGE = 1
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT // not used
   .stack           : > RAMLS567,  PAGE = 1
   .data			: > RAMLS567,  PAGE = 1
   .sysmem          : > RAMLS4,    PAGE = 1
#if defined(__TI_EABI__)
   .bss             : > RAMLS567,    PAGE = 1
   .bss:.cio        : > RAMLS4,    PAGE = 1
#else
   .cio             : > RAMLS4,    PAGE = 1
   .ebss            : > RAMLS567,  PAGE = 1
   .esysmem         : > RAMLS567,  PAGE = 1
#endif //__TI_EABI__
   // Example specific section
#if defined(FFT_ALIGN)
   FFT_buffer_1     : > RAMGS01,   PAGE = 1, ALIGN = FFT_ALIGN
#elif defined(FFT_UNALIGN)
    // Create a hole of size 10 at the beginnning of the FFT_buffer_1 section,
    // the linker will force the actual data to start at a new page, so you
    // may see a hole > 0xA in the .map file. Note that this is done purely
    // to demonstrate the unaligned FFT functions
    FFT_buffer_1:{.+=0xA;}> RAMGS01,   PAGE = 1
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
   FFT_buffer_2     : > RAMGS4,    PAGE = 1

   
}
//
//===========================================================================
// End of file.
//===========================================================================
//
