MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ACCESSPROTECTION           : origin = 0x0005F4C0, length = 0x00000040
   ADCA                       : origin = 0x00007400, length = 0x00000080
   ADCB                       : origin = 0x00007480, length = 0x00000080
   ADCC                       : origin = 0x00007500, length = 0x00000080
   ADCARESULT                 : origin = 0x00000B00, length = 0x00000018
   ADCBRESULT                 : origin = 0x00000B20, length = 0x00000018
   ADCCRESULT                 : origin = 0x00000B40, length = 0x00000018
   ANALOGSUBSYS               : origin = 0x0005D700, length = 0x00000090
   CANA                       : origin = 0x00048000, length = 0x00000200
   CANB                       : origin = 0x0004A000, length = 0x00000200
   CLAPROMCRC0                : origin = 0x000061C0, length = 0x00000020
   CLA1                       : origin = 0x00001400, length = 0x00000080
   CLB1DATAEXCH               : origin = 0x00003200, length = 0x00000200
   CLB2DATAEXCH               : origin = 0x00003600, length = 0x00000200
   CLB3DATAEXCH               : origin = 0x00003A00, length = 0x00000200
   CLB4DATAEXCH               : origin = 0x00003E00, length = 0x00000200
   CLB1LOGICCFG               : origin = 0x00003000, length = 0x00000052
   CLB2LOGICCFG               : origin = 0x00003400, length = 0x00000052
   CLB3LOGICCFG               : origin = 0x00003800, length = 0x00000052
   CLB4LOGICCFG               : origin = 0x00003C00, length = 0x00000052
   CLB1LOGICCTRL              : origin = 0x00003100, length = 0x00000040
   CLB2LOGICCTRL              : origin = 0x00003500, length = 0x00000040
   CLB3LOGICCTRL              : origin = 0x00003900, length = 0x00000040
   CLB4LOGICCTRL              : origin = 0x00003D00, length = 0x00000040
   CLBXBAR                    : origin = 0x00007A40, length = 0x00000040
   CLKCFG                     : origin = 0x0005D200, length = 0x00000036
   CMPSS1                     : origin = 0x00005C80, length = 0x00000020
   CMPSS2                     : origin = 0x00005CA0, length = 0x00000020
   CMPSS3                     : origin = 0x00005CC0, length = 0x00000020
   CMPSS4                     : origin = 0x00005CE0, length = 0x00000020
   CMPSS5                     : origin = 0x00005D00, length = 0x00000020
   CMPSS6                     : origin = 0x00005D20, length = 0x00000020
   CMPSS7                     : origin = 0x00005D40, length = 0x00000020
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   CPUSYS                     : origin = 0x0005D300, length = 0x00000082
   DACA                       : origin = 0x00005C00, length = 0x00000008
   DACB                       : origin = 0x00005C10, length = 0x00000008
   DCC0                       : origin = 0x0005E700, length = 0x0000002C
   DCSMBANK0Z1                : origin = 0x0005F000, length = 0x00000024
   DCSMBANK0Z2                : origin = 0x0005F040, length = 0x00000024
   DCSMBANK1Z1                : origin = 0x0005F100, length = 0x00000024
   DCSMBANK1Z2                : origin = 0x0005F140, length = 0x00000024
   DCSMCOMMON                 : origin = 0x0005F070, length = 0x00000010
   DEVCFG                     : origin = 0x0005D000, length = 0x00000180
   DMACLASRCSEL               : origin = 0x00007980, length = 0x0000001A
   DMA                        : origin = 0x00001000, length = 0x00000200
   ECAP1                      : origin = 0x00005200, length = 0x0000001E
   ECAP2                      : origin = 0x00005240, length = 0x0000001E
   ECAP3                      : origin = 0x00005280, length = 0x0000001E
   ECAP4                      : origin = 0x000052C0, length = 0x0000001E
   ECAP5                      : origin = 0x00005300, length = 0x0000001E
   ECAP6                      : origin = 0x00005340, length = 0x0000001E
   ECAP7                      : origin = 0x00005380, length = 0x0000001E
   EPWM1                      : origin = 0x00004000, length = 0x00000100
   EPWM2                      : origin = 0x00004100, length = 0x00000100
   EPWM3                      : origin = 0x00004200, length = 0x00000100
   EPWM4                      : origin = 0x00004300, length = 0x00000100
   EPWM5                      : origin = 0x00004400, length = 0x00000100
   EPWM6                      : origin = 0x00004500, length = 0x00000100
   EPWM7                      : origin = 0x00004600, length = 0x00000100
   EPWM8                      : origin = 0x00004700, length = 0x00000100
   EPWMXBAR                   : origin = 0x00007A00, length = 0x00000040
   EQEP1                      : origin = 0x00005100, length = 0x00000040
   EQEP2                      : origin = 0x00005140, length = 0x00000040
   ERADCOUNTER1               : origin = 0x0005E980, length = 0x00000010
   ERADCOUNTER2               : origin = 0x0005E990, length = 0x00000010
   ERADCOUNTER3               : origin = 0x0005E9A0, length = 0x00000010
   ERADCOUNTER4               : origin = 0x0005E9B0, length = 0x00000010
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
   GPIODATA                   : origin = 0x00007F00, length = 0x00000040
   HRCAP6                     : origin = 0x00005360, length = 0x00000020
   HRCAP7                     : origin = 0x000053A0, length = 0x00000020
   I2CA                       : origin = 0x00007300, length = 0x00000022
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   LINA                       : origin = 0x00006A00, length = 0x000000EC
   MEMORYERROR                : origin = 0x0005F500, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x00000080
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000008
   OUTPUTXBAR                 : origin = 0x00007A80, length = 0x00000040
   SYSPERIPHAC                : origin = 0x0005D500, length = 0x00000200
   PGA1                       : origin = 0x00005B00, length = 0x00000010
   PGA2                       : origin = 0x00005B10, length = 0x00000010
   PGA3                       : origin = 0x00005B20, length = 0x00000010
   PGA4                       : origin = 0x00005B30, length = 0x00000010
   PGA5                       : origin = 0x00005B40, length = 0x00000010
   PGA6                       : origin = 0x00005B50, length = 0x00000010
   PGA7                       : origin = 0x00005B60, length = 0x00000010
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   PMBUSA                     : origin = 0x00006400, length = 0x00000020
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SCIB                       : origin = 0x00007210, length = 0x00000010
   SDFM1                      : origin = 0x00005E00, length = 0x00000070
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SPIB                       : origin = 0x00006110, length = 0x00000010
   SYNCSOC                    : origin = 0x00007940, length = 0x00000006
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
   AdcbRegsFile               : > ADCB, type=NOINIT
   AdccRegsFile               : > ADCC, type=NOINIT
   AdcaResultRegsFile         : > ADCARESULT, type=NOINIT
   AdcbResultRegsFile         : > ADCBRESULT, type=NOINIT
   AdccResultRegsFile         : > ADCCRESULT, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   CanaRegsFile               : > CANA, type=NOINIT
   CanbRegsFile               : > CANB, type=NOINIT
   ClaPromCrc0RegsFile        : > CLAPROMCRC0, type=NOINIT
   Cla1RegsFile               : > CLA1, type=NOINIT
   Clb1DataExchRegsFile       : > CLB1DATAEXCH, type=NOINIT
   Clb2DataExchRegsFile       : > CLB2DATAEXCH, type=NOINIT
   Clb3DataExchRegsFile       : > CLB3DATAEXCH, type=NOINIT
   Clb4DataExchRegsFile       : > CLB4DATAEXCH, type=NOINIT
   Clb1LogicCfgRegsFile       : > CLB1LOGICCFG, type=NOINIT
   Clb2LogicCfgRegsFile       : > CLB2LOGICCFG, type=NOINIT
   Clb3LogicCfgRegsFile       : > CLB3LOGICCFG, type=NOINIT
   Clb4LogicCfgRegsFile       : > CLB4LOGICCFG, type=NOINIT
   Clb1LogicCtrlRegsFile      : > CLB1LOGICCTRL, type=NOINIT
   Clb2LogicCtrlRegsFile      : > CLB2LOGICCTRL, type=NOINIT
   Clb3LogicCtrlRegsFile      : > CLB3LOGICCTRL, type=NOINIT
   Clb4LogicCtrlRegsFile      : > CLB4LOGICCTRL, type=NOINIT
   CLBXbarRegsFile            : > CLBXBAR, type=NOINIT
   ClkCfgRegsFile             : > CLKCFG, type=NOINIT
   Cmpss1RegsFile             : > CMPSS1, type=NOINIT
   Cmpss2RegsFile             : > CMPSS2, type=NOINIT
   Cmpss3RegsFile             : > CMPSS3, type=NOINIT
   Cmpss4RegsFile             : > CMPSS4, type=NOINIT
   Cmpss5RegsFile             : > CMPSS5, type=NOINIT
   Cmpss6RegsFile             : > CMPSS6, type=NOINIT
   Cmpss7RegsFile             : > CMPSS7, type=NOINIT
   CpuTimer0RegsFile          : > CPUTIMER0, type=NOINIT
   CpuTimer1RegsFile          : > CPUTIMER1, type=NOINIT
   CpuTimer2RegsFile          : > CPUTIMER2, type=NOINIT
   CpuSysRegsFile             : > CPUSYS, type=NOINIT
   DacaRegsFile               : > DACA, type=NOINIT
   DacbRegsFile               : > DACB, type=NOINIT
   Dcc0RegsFile               : > DCC0, type=NOINIT
   DcsmBank0Z1RegsFile        : > DCSMBANK0Z1, type=NOINIT
   DcsmBank0Z2RegsFile        : > DCSMBANK0Z2, type=NOINIT
   DcsmBank1Z1RegsFile        : > DCSMBANK1Z1, type=NOINIT
   DcsmBank1Z2RegsFile        : > DCSMBANK1Z2, type=NOINIT
   DcsmCommonRegsFile         : > DCSMCOMMON, type=NOINIT
   DevCfgRegsFile             : > DEVCFG, type=NOINIT
   DmaClaSrcSelRegsFile       : > DMACLASRCSEL, type=NOINIT
   DmaRegsFile                : > DMA, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   ECap2RegsFile              : > ECAP2, type=NOINIT
   ECap3RegsFile              : > ECAP3, type=NOINIT
   ECap4RegsFile              : > ECAP4, type=NOINIT
   ECap5RegsFile              : > ECAP5, type=NOINIT
   ECap6RegsFile              : > ECAP6, type=NOINIT
   ECap7RegsFile              : > ECAP7, type=NOINIT
   EPwm1RegsFile              : > EPWM1, type=NOINIT
   EPwm2RegsFile              : > EPWM2, type=NOINIT
   EPwm3RegsFile              : > EPWM3, type=NOINIT
   EPwm4RegsFile              : > EPWM4, type=NOINIT
   EPwm5RegsFile              : > EPWM5, type=NOINIT
   EPwm6RegsFile              : > EPWM6, type=NOINIT
   EPwm7RegsFile              : > EPWM7, type=NOINIT
   EPwm8RegsFile              : > EPWM8, type=NOINIT
   EPwmXbarRegsFile           : > EPWMXBAR, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   EQep2RegsFile              : > EQEP2, type=NOINIT
   EradCounter1RegsFile       : > ERADCOUNTER1, type=NOINIT
   EradCounter2RegsFile       : > ERADCOUNTER2, type=NOINIT
   EradCounter3RegsFile       : > ERADCOUNTER3, type=NOINIT
   EradCounter4RegsFile       : > ERADCOUNTER4, type=NOINIT
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
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   HRCap6RegsFile             : > HRCAP6, type=NOINIT
   HRCap7RegsFile             : > HRCAP7, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   LinaRegsFile               : > LINA, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   SysPeriphAcRegsFile        : > SYSPERIPHAC, type=NOINIT
   Pga1RegsFile               : > PGA1, type=NOINIT
   Pga2RegsFile               : > PGA2, type=NOINIT
   Pga3RegsFile               : > PGA3, type=NOINIT
   Pga4RegsFile               : > PGA4, type=NOINIT
   Pga5RegsFile               : > PGA5, type=NOINIT
   Pga6RegsFile               : > PGA6, type=NOINIT
   Pga7RegsFile               : > PGA7, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   PieVectTableFile           : > PIEVECTTABLE, type=NOINIT
   PmbusaRegsFile             : > PMBUSA, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   ScibRegsFile               : > SCIB, type=NOINIT
   Sdfm1RegsFile              : > SDFM1, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SpibRegsFile               : > SPIB, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   WdRegsFile                 : > WD, type=NOINIT
   XbarRegsFile               : > XBAR, type=NOINIT
   XintRegsFile               : > XINT, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

