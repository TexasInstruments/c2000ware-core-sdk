MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ACCESSPROTECTION           : origin = 0x0005F500, length = 0x0000003E
   ADCA                       : origin = 0x00007400, length = 0x00000080
   ADCC                       : origin = 0x00007500, length = 0x00000080
   ADCARESULT                 : origin = 0x00000B00, length = 0x00000018
   ADCCRESULT                 : origin = 0x00000B40, length = 0x00000018
   ANALOGSUBSYS               : origin = 0x0005D700, length = 0x0000012A
   CANA                       : origin = 0x00048000, length = 0x00000200
   CLKCFG                     : origin = 0x0005D200, length = 0x00000100
   CMPSSLITE2                 : origin = 0x00005540, length = 0x00000040
   CMPSSLITE3                 : origin = 0x00005580, length = 0x00000040
   CMPSSLITE4                 : origin = 0x000055C0, length = 0x00000040
   CMPSS1                     : origin = 0x00005500, length = 0x00000040
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   CPUSYS                     : origin = 0x0005D300, length = 0x00000100
   DCC0                       : origin = 0x0005E700, length = 0x00000038
   DCSMCOMMON                 : origin = 0x0005F0C0, length = 0x00000040
   DCSMZ1OTP                  : origin = 0x00078000, length = 0x00000020
   DCSMZ1                     : origin = 0x0005F000, length = 0x0000003E
   DCSMZ2OTP                  : origin = 0x00078200, length = 0x00000020
   DCSMZ2                     : origin = 0x0005F080, length = 0x0000003E
   DEVCFG                     : origin = 0x0005D000, length = 0x000001AC
   ECAP1                      : origin = 0x00005200, length = 0x00000020
   ECAP2                      : origin = 0x00005240, length = 0x00000020
   EPG1MUX                    : origin = 0x0005ECD0, length = 0x00000010
   EPG1                       : origin = 0x0005EC00, length = 0x00000050
   EPWM1                      : origin = 0x00004000, length = 0x00000100
   EPWM2                      : origin = 0x00004100, length = 0x00000100
   EPWM3                      : origin = 0x00004200, length = 0x00000100
   EPWM4                      : origin = 0x00004300, length = 0x00000100
   EPWM5                      : origin = 0x00004400, length = 0x00000100
   EPWM6                      : origin = 0x00004500, length = 0x00000100
   EPWM7                      : origin = 0x00004600, length = 0x00000100
   EPWMXBAR                   : origin = 0x00007A00, length = 0x00000040
   EQEP1                      : origin = 0x00005100, length = 0x00000040
   FLASH0CTRL                 : origin = 0x0005F800, length = 0x00000182
   FLASH0ECC                  : origin = 0x0005FB00, length = 0x00000028
   GPIOCTRL                   : origin = 0x00007C00, length = 0x00000200
   GPIODATAREAD               : origin = 0x00007F80, length = 0x00000010
   GPIODATA                   : origin = 0x00007F00, length = 0x00000040
   I2CA                       : origin = 0x00007300, length = 0x00000022
   I2CB                       : origin = 0x00007340, length = 0x00000022
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   MEMORYERROR                : origin = 0x0005F540, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x000000C0
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000010
   OUTPUTXBAR                 : origin = 0x00007A80, length = 0x00000040
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SCIB                       : origin = 0x00007210, length = 0x00000010
   SCIC                       : origin = 0x00007220, length = 0x00000010
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SYNCSOC                    : origin = 0x00007940, length = 0x00000006
   SYSSTATUS                  : origin = 0x0005D400, length = 0x00000040
   TESTERROR                  : origin = 0x0005F590, length = 0x00000010
   UID                        : origin = 0x00071140, length = 0x00000010
   WD                         : origin = 0x00007000, length = 0x0000002C
   XBAR                       : origin = 0x00007920, length = 0x00000020
   XINT                       : origin = 0x00007070, length = 0x0000000C

}


SECTIONS
{
/*** PIE Vect Table and Boot ROM Variables Structures ***/
UNION run = PIEVECTTABLE
{
    PieVectTableFile      : TYPE=DSECT
    GROUP
    {
        EmuKeyVar         : TYPE=DSECT
        EmuBModeVar       : TYPE=DSECT
        EmuBootPinsVar    : TYPE=DSECT
        FlashCallbackVar  : TYPE=DSECT
        FlashScalingVar   : TYPE=DSECT
    }
}

   AccessProtectionRegsFile   : > ACCESSPROTECTION, type=NOINIT
   AdcaRegsFile               : > ADCA, type=NOINIT
   AdccRegsFile               : > ADCC, type=NOINIT
   AdcaResultRegsFile         : > ADCARESULT, type=NOINIT
   AdccResultRegsFile         : > ADCCRESULT, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   CanaRegsFile               : > CANA, type=NOINIT
   ClkCfgRegsFile             : > CLKCFG, type=NOINIT
   CmpssLite2RegsFile         : > CMPSSLITE2, type=NOINIT
   CmpssLite3RegsFile         : > CMPSSLITE3, type=NOINIT
   CmpssLite4RegsFile         : > CMPSSLITE4, type=NOINIT
   Cmpss1RegsFile             : > CMPSS1, type=NOINIT
   CpuTimer0RegsFile          : > CPUTIMER0, type=NOINIT
   CpuTimer1RegsFile          : > CPUTIMER1, type=NOINIT
   CpuTimer2RegsFile          : > CPUTIMER2, type=NOINIT
   CpuSysRegsFile             : > CPUSYS, type=NOINIT
   Dcc0RegsFile               : > DCC0, type=NOINIT
   DcsmCommonRegsFile         : > DCSMCOMMON, type=NOINIT
   DcsmZ1OtpRegsFile          : > DCSMZ1OTP, type=NOINIT
   DcsmZ1RegsFile             : > DCSMZ1, type=NOINIT
   DcsmZ2OtpRegsFile          : > DCSMZ2OTP, type=NOINIT
   DcsmZ2RegsFile             : > DCSMZ2, type=NOINIT
   DevCfgRegsFile             : > DEVCFG, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   ECap2RegsFile              : > ECAP2, type=NOINIT
   Epg1MuxRegsFile            : > EPG1MUX, type=NOINIT
   Epg1RegsFile               : > EPG1, type=NOINIT
   EPwm1RegsFile              : > EPWM1, type=NOINIT
   EPwm2RegsFile              : > EPWM2, type=NOINIT
   EPwm3RegsFile              : > EPWM3, type=NOINIT
   EPwm4RegsFile              : > EPWM4, type=NOINIT
   EPwm5RegsFile              : > EPWM5, type=NOINIT
   EPwm6RegsFile              : > EPWM6, type=NOINIT
   EPwm7RegsFile              : > EPWM7, type=NOINIT
   EPwmXbarRegsFile           : > EPWMXBAR, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   Flash0CtrlRegsFile         : > FLASH0CTRL, type=NOINIT
   Flash0EccRegsFile          : > FLASH0ECC, type=NOINIT
   GpioCtrlRegsFile           : > GPIOCTRL, type=NOINIT
   GpioDataReadRegsFile       : > GPIODATAREAD, type=NOINIT
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   I2cbRegsFile               : > I2CB, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   ScibRegsFile               : > SCIB, type=NOINIT
   ScicRegsFile               : > SCIC, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   SysStatusRegsFile          : > SYSSTATUS, type=NOINIT
   TestErrorRegsFile          : > TESTERROR, type=NOINIT
   UidRegsFile                : > UID, type=NOINIT
   WdRegsFile                 : > WD, type=NOINIT
   XbarRegsFile               : > XBAR, type=NOINIT
   XintRegsFile               : > XINT, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

