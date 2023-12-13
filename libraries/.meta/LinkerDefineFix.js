let longDescription = `
For modules such as FFT, there are preprocessor pre-defines that need to be added from the .genlibs. As of right now,
no current 
implementation of this exists in SysConfig, this must be done manually. To do this, right-click on the project name 
and select Properties, then go to: **CCS Build -> C2000 Linker -> Advanced Options -> Command File Preprocessing**.
Then add in the pre-define variable that exists in your c2000ware_libraries.cmd.genlibs file (with its value, if 
necessary), and rebuild the project.

For example, for the FFT add in FFT_ALIGN=(4 * FFT_SIZE) for FPU32 configuration 
or FFT_ALIGN=(8 * FFT_SIZE) for FPU64 configuration.

![Image Missing](../../libraries/.meta/dsp/FPU/FFT/references/LinkerDefineFix.png)

---

`

exports = {
    errorFix : longDescription
}