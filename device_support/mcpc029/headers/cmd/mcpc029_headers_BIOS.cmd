MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ADCA                       : origin = 0x00007400, length = 0x00000200
   ADCARESULT                 : origin = 0x00001800, length = 0x00000080
   ANALOGSUBSYS               : origin = 0x0005D700, length = 0x0000014A
   CLKCFG                     : origin = 0x0005D200, length = 0x00000040
   CMPSSLITE1                 : origin = 0x00005500, length = 0x00000040
   CMPSSLITE2                 : origin = 0x00005540, length = 0x00000040
   CMPSSLITE3                 : origin = 0x00005580, length = 0x00000040
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   CPUSYS                     : origin = 0x0005D300, length = 0x00000040
   DCC0                       : origin = 0x0005E700, length = 0x00000040
   DCSMCOMMON                 : origin = 0x0005F0C0, length = 0x00000040
   DCSMZ1OTP                  : origin = 0x00078000, length = 0x00000020
   DCSMZ1                     : origin = 0x0005F000, length = 0x00000040
   DCSMZ2OTP                  : origin = 0x00078200, length = 0x00000020
   DCSMZ2                     : origin = 0x0005F080, length = 0x0000003E
   DEVCFG                     : origin = 0x0005D000, length = 0x00000040
   DMACLASRCSEL               : origin = 0x00007980, length = 0x00000010
   DMA                        : origin = 0x00001000, length = 0x00000200
   ECAP1                      : origin = 0x00005200, length = 0x00000020
   EQEP1                      : origin = 0x00005100, length = 0x00000040
   FLASH0CTRL                 : origin = 0x0005F800, length = 0x00000010
   FLASH0ECC                  : origin = 0x0005FB00, length = 0x00000010
   GPIOCTRL                   : origin = 0x00007C00, length = 0x00000200
   GPIODATAREAD               : origin = 0x00007F80, length = 0x00000010
   GPIODATA                   : origin = 0x00007F00, length = 0x00000040
   I2CA                       : origin = 0x00007300, length = 0x00000022
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   PWM3                       : origin = 0x00004800, length = 0x00000100
   PWM1                       : origin = 0x00004000, length = 0x00000400
   MEMORYERROR                : origin = 0x0005F540, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x00000040
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000010
   OUTPUTXBAR                 : origin = 0x00007A80, length = 0x00000040
   PGA1                       : origin = 0x00005B00, length = 0x00000010
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   PWMXBAR                    : origin = 0x00007A00, length = 0x00000040
   ROMWAITSTATE               : origin = 0x0005F580, length = 0x00000002
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SCIB                       : origin = 0x00007210, length = 0x00000010
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SYNCSOC                    : origin = 0x00007940, length = 0x00000010
   SYSSTATUS                  : origin = 0x0005D400, length = 0x00000010
   TESTERROR                  : origin = 0x0005F590, length = 0x00000008
   UARTA                      : origin = 0x0006A000, length = 0x00000800
   UID                        : origin = 0x00072172, length = 0x00000010
   WD                         : origin = 0x00007000, length = 0x00000040
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

   AdcaRegsFile               : > ADCA, type=NOINIT
   AdcaResultRegsFile         : > ADCARESULT, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   ClkCfgRegsFile             : > CLKCFG, type=NOINIT
   CmpssLite1RegsFile         : > CMPSSLITE1, type=NOINIT
   CmpssLite2RegsFile         : > CMPSSLITE2, type=NOINIT
   CmpssLite3RegsFile         : > CMPSSLITE3, type=NOINIT
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
   DmaClaSrcSelRegsFile       : > DMACLASRCSEL, type=NOINIT
   DmaRegsFile                : > DMA, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   Flash0CtrlRegsFile         : > FLASH0CTRL, type=NOINIT
   Flash0EccRegsFile          : > FLASH0ECC, type=NOINIT
   GpioCtrlRegsFile           : > GPIOCTRL, type=NOINIT
   GpioDataReadRegsFile       : > GPIODATAREAD, type=NOINIT
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   Pwm3RegsFile               : > PWM3, type=NOINIT
   Pwm1RegsFile               : > PWM1, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   Pga1RegsFile               : > PGA1, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   PieVectTableFile           : > PIEVECTTABLE, type=NOINIT
   PwmXbarRegsFile            : > PWMXBAR, type=NOINIT
   RomWaitStateRegsFile       : > ROMWAITSTATE, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   ScibRegsFile               : > SCIB, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   SysStatusRegsFile          : > SYSSTATUS, type=NOINIT
   TestErrorRegsFile          : > TESTERROR, type=NOINIT
   UartaRegsFile              : > UARTA, type=NOINIT
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

