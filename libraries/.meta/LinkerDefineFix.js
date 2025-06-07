let longDescription = `
**Note: Most of FFT calculation requires FFT data buffers to have a proper memory alignment (packed format), unless the function is denoted by 'u' (unpacked).**

For functions that require memory alignment of data buffers, the buffer must be aligned by **FFT_ALIGN = (4 * FFT_SIZE) for FPU32** configuration, or **FFT_ALIGN = (8 * FFT_SIZE) for FPU64 configuration**. This alignment can be specified to a section in the linker file (.cmd file), which then user could map the section to buffers via variable attributes in code. See the following steps for details:

1. Specify alignment to a linker section
    - Using SysConfig generated the linker file (in Sysconfig under LINKER COMMAND FILE CONFIGURATION -> CMD):
        +   Create a section under User Defined Sections with "Enable Alignment" checked and input the calculated alignment number FFT_ALIGN in "Alignment in bytes".
    - Using a standalone linker file (.cmd file): 
        +   Use "ALIGN()" or "ALIGN=" specifier to add alignment to a defined section, for instance: "FFT_buffer_1 : > RAMGS1, ALIGN(FFT_ALIGN)"
        +   Where FFT_ALIGN is the calculated alignment bytes, in either raw number or macro to the raw number.

2. Map data buffers to the memory aligned sections
    -   Add the following compiler attribute to the FFT buffers: #pragma SET_DATA_SECTION("aligned_section_name")
    -   Where "aligned_section_name" is the name of the linker section that has the alignment.
---
`

exports = {
    errorFix : longDescription
}