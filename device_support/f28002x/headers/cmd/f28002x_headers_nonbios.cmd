MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ACCESSPROTECTION           : origin = 0x0005F500, length = 0x0000003E
   ADCA                       : origin = 0x00007400, length = 0x00000080
   ADCC                       : origin = 0x00007500, length = 0x00000080
   ADCARESULT                 : origin = 0x00000B00, length = 0x00000018
   ADCCRESULT                 : origin = 0x00000B40, length = 0x00000018
   ANALOGSUBSYS               : origin = 0x0005D700, length = 0x00000100
   BGCRCCPU                   : origin = 0x00006340, length = 0x00000040
   CANA                       : origin = 0x00048000, length = 0x00000200
   CLB1DATAEXCH               : origin = 0x00003180, length = 0x00000080
   CLB2DATAEXCH               : origin = 0x00003580, length = 0x00000080
   CLB1LOGICCFG               : origin = 0x00003000, length = 0x00000052
   CLB2LOGICCFG               : origin = 0x00003400, length = 0x00000052
   CLB1LOGICCTRL              : origin = 0x00003100, length = 0x00000040
   CLB2LOGICCTRL              : origin = 0x00003500, length = 0x00000040
   CLBXBAR                    : origin = 0x00007A40, length = 0x00000040
   CLKCFG                     : origin = 0x0005D200, length = 0x00000100
   CMPSS1                     : origin = 0x00005C80, length = 0x00000020
   CMPSS2                     : origin = 0x00005CA0, length = 0x00000020
   CMPSS3                     : origin = 0x00005CC0, length = 0x00000020
   CMPSS4                     : origin = 0x00005CE0, length = 0x00000020
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   CPUSYS                     : origin = 0x0005D300, length = 0x000000A0
   DCC0                       : origin = 0x0005E700, length = 0x00000038
   DCC1                       : origin = 0x0005E740, length = 0x00000038
   DCSMBANK0Z1OTP             : origin = 0x00078000, length = 0x00000020
   DCSMBANK0Z1                : origin = 0x0005F000, length = 0x00000024
   DCSMBANK0Z2OTP             : origin = 0x00078200, length = 0x00000020
   DCSMBANK0Z2                : origin = 0x0005F040, length = 0x00000024
   DCSMCOMMON                 : origin = 0x0005F070, length = 0x00000010
   DEVCFG                     : origin = 0x0005D000, length = 0x000001AC
   DMACLASRCSEL               : origin = 0x00007980, length = 0x0000001A
   DMA                        : origin = 0x00001000, length = 0x00000200
   ECAP1                      : origin = 0x00005200, length = 0x00000020
   ECAP2                      : origin = 0x00005240, length = 0x00000020
   ECAP3                      : origin = 0x00005280, length = 0x00000020
   EPWM1                      : origin = 0x00004000, length = 0x00000100
   EPWM2                      : origin = 0x00004100, length = 0x00000100
   EPWM3                      : origin = 0x00004200, length = 0x00000100
   EPWM4                      : origin = 0x00004300, length = 0x00000100
   EPWM5                      : origin = 0x00004400, length = 0x00000100
   EPWM6                      : origin = 0x00004500, length = 0x00000100
   EPWM7                      : origin = 0x00004600, length = 0x00000100
   EPWMXBAR                   : origin = 0x00007A00, length = 0x00000040
   EQEP1                      : origin = 0x00005100, length = 0x00000040
   EQEP2                      : origin = 0x00005140, length = 0x00000040
   ERADCOUNTER1               : origin = 0x0005E980, length = 0x00000010
   ERADCOUNTER2               : origin = 0x0005E990, length = 0x00000010
   ERADCOUNTER3               : origin = 0x0005E9A0, length = 0x00000010
   ERADCOUNTER4               : origin = 0x0005E9B0, length = 0x00000010
   ERADCRCGLOBAL              : origin = 0x0005EA00, length = 0x00000010
   ERADCRC1                   : origin = 0x0005EA10, length = 0x00000010
   ERADCRC2                   : origin = 0x0005EA20, length = 0x00000010
   ERADCRC3                   : origin = 0x0005EA30, length = 0x00000010
   ERADCRC4                   : origin = 0x0005EA40, length = 0x00000010
   ERADCRC5                   : origin = 0x0005EA50, length = 0x00000010
   ERADCRC6                   : origin = 0x0005EA60, length = 0x00000010
   ERADCRC7                   : origin = 0x0005EA70, length = 0x00000010
   ERADCRC8                   : origin = 0x0005EA80, length = 0x00000010
   ERADGLOBAL                 : origin = 0x0005E800, length = 0x00000014
   ERADHWBP1                  : origin = 0x0005E900, length = 0x00000008
   ERADHWBP2                  : origin = 0x0005E908, length = 0x00000008
   ERADHWBP3                  : origin = 0x0005E910, length = 0x00000008
   ERADHWBP4                  : origin = 0x0005E918, length = 0x00000008
   ERADHWBP5                  : origin = 0x0005E920, length = 0x00000008
   ERADHWBP6                  : origin = 0x0005E928, length = 0x00000008
   ERADHWBP7                  : origin = 0x0005E930, length = 0x00000008
   ERADHWBP8                  : origin = 0x0005E938, length = 0x00000008
   FLASH0CTRL                 : origin = 0x0005F800, length = 0x00000182
   FLASH0ECC                  : origin = 0x0005FB00, length = 0x00000028
   FSIRXA                     : origin = 0x00006680, length = 0x00000050
   FSITXA                     : origin = 0x00006600, length = 0x00000050
   GPIOCTRL                   : origin = 0x00007C00, length = 0x00000200
   GPIODATAREAD               : origin = 0x00007F80, length = 0x00000010
   GPIODATA                   : origin = 0x00007F00, length = 0x00000040
   HIC                        : origin = 0x00006500, length = 0x00000080
   HRCAP3                     : origin = 0x000052A0, length = 0x00000020
   I2CA                       : origin = 0x00007300, length = 0x00000022
   I2CB                       : origin = 0x00007340, length = 0x00000022
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   CLBINPUTXBAR               : origin = 0x00007960, length = 0x00000020
   LINA                       : origin = 0x00006A00, length = 0x000000EC
   LINB                       : origin = 0x00006B00, length = 0x000000EC
   MEMORYERROR                : origin = 0x0005F540, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x000000C0
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000010
   OUTPUTXBAR                 : origin = 0x00007A80, length = 0x00000040
   CLBOUTPUTXBAR              : origin = 0x00007BC0, length = 0x00000040
   SYSPERIPHAC                : origin = 0x0005D500, length = 0x00000200
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   PMBUSA                     : origin = 0x00006400, length = 0x00000020
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SPIB                       : origin = 0x00006110, length = 0x00000010
   SYNCSOC                    : origin = 0x00007940, length = 0x00000006
   TESTERROR                  : origin = 0x0005F590, length = 0x00000010
   WD                         : origin = 0x00007000, length = 0x0000002C
   XBAR                       : origin = 0x00007920, length = 0x00000020
   XINT                       : origin = 0x00007070, length = 0x0000000C

}


SECTIONS
{
/*** PIE Vect Table and Boot ROM Variables Structures ***/
UNION run = PIEVECTTABLE
{
    PieVectTableFile
    GROUP
    {
        EmuKeyVar
        EmuBModeVar
        EmuBootPinsVar
        FlashCallbackVar
        FlashScalingVar
    }
}

   AccessProtectionRegsFile   : > ACCESSPROTECTION, type=NOINIT
   AdcaRegsFile               : > ADCA, type=NOINIT
   AdccRegsFile               : > ADCC, type=NOINIT
   AdcaResultRegsFile         : > ADCARESULT, type=NOINIT
   AdccResultRegsFile         : > ADCCRESULT, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   BgcrcCpuRegsFile           : > BGCRCCPU, type=NOINIT
   CanaRegsFile               : > CANA, type=NOINIT
   Clb1DataExchRegsFile       : > CLB1DATAEXCH, type=NOINIT
   Clb2DataExchRegsFile       : > CLB2DATAEXCH, type=NOINIT
   Clb1LogicCfgRegsFile       : > CLB1LOGICCFG, type=NOINIT
   Clb2LogicCfgRegsFile       : > CLB2LOGICCFG, type=NOINIT
   Clb1LogicCtrlRegsFile      : > CLB1LOGICCTRL, type=NOINIT
   Clb2LogicCtrlRegsFile      : > CLB2LOGICCTRL, type=NOINIT
   ClbXbarRegsFile            : > CLBXBAR, type=NOINIT
   ClkCfgRegsFile             : > CLKCFG, type=NOINIT
   Cmpss1RegsFile             : > CMPSS1, type=NOINIT
   Cmpss2RegsFile             : > CMPSS2, type=NOINIT
   Cmpss3RegsFile             : > CMPSS3, type=NOINIT
   Cmpss4RegsFile             : > CMPSS4, type=NOINIT
   CpuTimer0RegsFile          : > CPUTIMER0, type=NOINIT
   CpuTimer1RegsFile          : > CPUTIMER1, type=NOINIT
   CpuTimer2RegsFile          : > CPUTIMER2, type=NOINIT
   CpuSysRegsFile             : > CPUSYS, type=NOINIT
   Dcc0RegsFile               : > DCC0, type=NOINIT
   Dcc1RegsFile               : > DCC1, type=NOINIT
   DcsmBank0Z1OtpRegsFile     : > DCSMBANK0Z1OTP, type=NOINIT
   DcsmBank0Z1RegsFile        : > DCSMBANK0Z1, type=NOINIT
   DcsmBank0Z2OtpRegsFile     : > DCSMBANK0Z2OTP, type=NOINIT
   DcsmBank0Z2RegsFile        : > DCSMBANK0Z2, type=NOINIT
   DcsmCommonRegsFile         : > DCSMCOMMON, type=NOINIT
   DevCfgRegsFile             : > DEVCFG, type=NOINIT
   DmaClaSrcSelRegsFile       : > DMACLASRCSEL, type=NOINIT
   DmaRegsFile                : > DMA, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   ECap2RegsFile              : > ECAP2, type=NOINIT
   ECap3RegsFile              : > ECAP3, type=NOINIT
   EPwm1RegsFile              : > EPWM1, type=NOINIT
   EPwm2RegsFile              : > EPWM2, type=NOINIT
   EPwm3RegsFile              : > EPWM3, type=NOINIT
   EPwm4RegsFile              : > EPWM4, type=NOINIT
   EPwm5RegsFile              : > EPWM5, type=NOINIT
   EPwm6RegsFile              : > EPWM6, type=NOINIT
   EPwm7RegsFile              : > EPWM7, type=NOINIT
   EPwmXbarRegsFile           : > EPWMXBAR, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   EQep2RegsFile              : > EQEP2, type=NOINIT
   EradCounter1RegsFile       : > ERADCOUNTER1, type=NOINIT
   EradCounter2RegsFile       : > ERADCOUNTER2, type=NOINIT
   EradCounter3RegsFile       : > ERADCOUNTER3, type=NOINIT
   EradCounter4RegsFile       : > ERADCOUNTER4, type=NOINIT
   EradCRCGlobalRegsFile      : > ERADCRCGLOBAL, type=NOINIT
   EradCRC1RegsFile           : > ERADCRC1, type=NOINIT
   EradCRC2RegsFile           : > ERADCRC2, type=NOINIT
   EradCRC3RegsFile           : > ERADCRC3, type=NOINIT
   EradCRC4RegsFile           : > ERADCRC4, type=NOINIT
   EradCRC5RegsFile           : > ERADCRC5, type=NOINIT
   EradCRC6RegsFile           : > ERADCRC6, type=NOINIT
   EradCRC7RegsFile           : > ERADCRC7, type=NOINIT
   EradCRC8RegsFile           : > ERADCRC8, type=NOINIT
   EradGlobalRegsFile         : > ERADGLOBAL, type=NOINIT
   EradHWBP1RegsFile          : > ERADHWBP1, type=NOINIT
   EradHWBP2RegsFile          : > ERADHWBP2, type=NOINIT
   EradHWBP3RegsFile          : > ERADHWBP3, type=NOINIT
   EradHWBP4RegsFile          : > ERADHWBP4, type=NOINIT
   EradHWBP5RegsFile          : > ERADHWBP5, type=NOINIT
   EradHWBP6RegsFile          : > ERADHWBP6, type=NOINIT
   EradHWBP7RegsFile          : > ERADHWBP7, type=NOINIT
   EradHWBP8RegsFile          : > ERADHWBP8, type=NOINIT
   Flash0CtrlRegsFile         : > FLASH0CTRL, type=NOINIT
   Flash0EccRegsFile          : > FLASH0ECC, type=NOINIT
   FsiRxaRegsFile             : > FSIRXA, type=NOINIT
   FsiTxaRegsFile             : > FSITXA, type=NOINIT
   GpioCtrlRegsFile           : > GPIOCTRL, type=NOINIT
   GpioDataReadRegsFile       : > GPIODATAREAD, type=NOINIT
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   HicRegsFile                : > HIC, type=NOINIT
   HRCap3RegsFile             : > HRCAP3, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   I2cbRegsFile               : > I2CB, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   ClbInputXbarRegsFile       : > CLBINPUTXBAR, type=NOINIT
   LinaRegsFile               : > LINA, type=NOINIT
   LinbRegsFile               : > LINB, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   ClbOutputXbarRegsFile      : > CLBOUTPUTXBAR, type=NOINIT
   SysPeriphAcRegsFile        : > SYSPERIPHAC, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   PieVectTableFile           : > PIEVECTTABLE, type=NOINIT
   PmbusaRegsFile             : > PMBUSA, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SpibRegsFile               : > SPIB, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   TestErrorRegsFile          : > TESTERROR, type=NOINIT
   WdRegsFile                 : > WD, type=NOINIT
   XbarRegsFile               : > XBAR, type=NOINIT
   XintRegsFile               : > XINT, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

