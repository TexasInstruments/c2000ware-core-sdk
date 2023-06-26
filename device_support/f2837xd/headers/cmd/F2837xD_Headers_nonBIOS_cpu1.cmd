MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ACCESSPROTECTION           : origin = 0x0005F4C0, length = 0x00000040
   ADCA                       : origin = 0x00007400, length = 0x00000080
   ADCB                       : origin = 0x00007480, length = 0x00000080
   ADCC                       : origin = 0x00007500, length = 0x00000080
   ADCD                       : origin = 0x00007580, length = 0x00000080
   ADCARESULT                 : origin = 0x00000B00, length = 0x00000018
   ADCBRESULT                 : origin = 0x00000B20, length = 0x00000018
   ADCCRESULT                 : origin = 0x00000B40, length = 0x00000018
   ADCDRESULT                 : origin = 0x00000B60, length = 0x00000018
   ANALOGSUBSYS               : origin = 0x0005D180, length = 0x00000048
   CANA                       : origin = 0x00048000, length = 0x00000200
   CANB                       : origin = 0x0004A000, length = 0x00000200
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
   CLKCFG                     : origin = 0x0005D200, length = 0x00000032
   CMPSS1                     : origin = 0x00005C80, length = 0x00000020
   CMPSS2                     : origin = 0x00005CA0, length = 0x00000020
   CMPSS3                     : origin = 0x00005CC0, length = 0x00000020
   CMPSS4                     : origin = 0x00005CE0, length = 0x00000020
   CMPSS5                     : origin = 0x00005D00, length = 0x00000020
   CMPSS6                     : origin = 0x00005D20, length = 0x00000020
   CMPSS7                     : origin = 0x00005D40, length = 0x00000020
   CMPSS8                     : origin = 0x00005D60, length = 0x00000020
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   CPUSYS                     : origin = 0x0005D300, length = 0x00000082
   DACA                       : origin = 0x00005C00, length = 0x00000008
   DACB                       : origin = 0x00005C10, length = 0x00000008
   DACC                       : origin = 0x00005C20, length = 0x00000008
   DCSMCOMMON                 : origin = 0x0005F070, length = 0x00000008
   DCSMZ1                     : origin = 0x0005F000, length = 0x00000024
   DCSMZ2                     : origin = 0x0005F040, length = 0x00000024
   DEVCFG                     : origin = 0x0005D000, length = 0x0000012E
   DMACLASRCSEL               : origin = 0x00007980, length = 0x0000001A
   DMA                        : origin = 0x00001000, length = 0x00000200
   ECAP1                      : origin = 0x00005000, length = 0x00000020
   ECAP2                      : origin = 0x00005020, length = 0x00000020
   ECAP3                      : origin = 0x00005040, length = 0x00000020
   ECAP4                      : origin = 0x00005060, length = 0x00000020
   ECAP5                      : origin = 0x00005080, length = 0x00000020
   ECAP6                      : origin = 0x000050A0, length = 0x00000020
   EMIF1CONFIG                : origin = 0x0005F480, length = 0x00000020
   EMIF2CONFIG                : origin = 0x0005F4A0, length = 0x00000020
   EMIF1                      : origin = 0x00047000, length = 0x00000070
   EMIF2                      : origin = 0x00047800, length = 0x00000070
   EPWM1                      : origin = 0x00004000, length = 0x00000100
   EPWM2                      : origin = 0x00004100, length = 0x00000100
   EPWM3                      : origin = 0x00004200, length = 0x00000100
   EPWM4                      : origin = 0x00004300, length = 0x00000100
   EPWM5                      : origin = 0x00004400, length = 0x00000100
   EPWM6                      : origin = 0x00004500, length = 0x00000100
   EPWM7                      : origin = 0x00004600, length = 0x00000100
   EPWM8                      : origin = 0x00004700, length = 0x00000100
   EPWM9                      : origin = 0x00004800, length = 0x00000100
   EPWM10                     : origin = 0x00004900, length = 0x00000100
   EPWM11                     : origin = 0x00004A00, length = 0x00000100
   EPWM12                     : origin = 0x00004B00, length = 0x00000100
   EPWMXBAR                   : origin = 0x00007A00, length = 0x00000040
   EQEP1                      : origin = 0x00005100, length = 0x00000022
   EQEP2                      : origin = 0x00005140, length = 0x00000022
   EQEP3                      : origin = 0x00005180, length = 0x00000022
   FLASH0CTRL                 : origin = 0x0005F800, length = 0x00000182
   FLASH0ECC                  : origin = 0x0005FB00, length = 0x00000028
   FLASHPUMPSEMAPHORE         : origin = 0x00050024, length = 0x00000002
   GPIOCTRL                   : origin = 0x00007C00, length = 0x00000180
   GPIODATA                   : origin = 0x00007F00, length = 0x00000030
   I2CA                       : origin = 0x00007300, length = 0x00000022
   I2CB                       : origin = 0x00007340, length = 0x00000022
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   IPC                        : origin = 0x00050000, length = 0x00000024
   MEMORYERROR                : origin = 0x0005F500, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x00000080
   MCBSPA                     : origin = 0x00006000, length = 0x00000024
   MCBSPB                     : origin = 0x00006040, length = 0x00000024
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000007
   OUTPUTXBAR                 : origin = 0x00007A80, length = 0x00000040
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   ROMPREFETCH                : origin = 0x0005E608, length = 0x00000002
   ROMWAITSTATE               : origin = 0x0005F540, length = 0x00000002
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SCIB                       : origin = 0x00007210, length = 0x00000010
   SCIC                       : origin = 0x00007220, length = 0x00000010
   SCID                       : origin = 0x00007230, length = 0x00000010
   SDFM1                      : origin = 0x00005E00, length = 0x00000080
   SDFM2                      : origin = 0x00005E80, length = 0x00000080
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SPIB                       : origin = 0x00006110, length = 0x00000010
   SPIC                       : origin = 0x00006120, length = 0x00000010
   SYNCSOC                    : origin = 0x00007940, length = 0x00000006
   UPP                        : origin = 0x00006200, length = 0x00000048
   WD                         : origin = 0x00007000, length = 0x0000002B
   XBAR                       : origin = 0x00007920, length = 0x00000020
   XINT                       : origin = 0x00007070, length = 0x0000000B

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
   AdcdRegsFile               : > ADCD, type=NOINIT
   AdcaResultRegsFile         : > ADCARESULT, type=NOINIT
   AdcbResultRegsFile         : > ADCBRESULT, type=NOINIT
   AdccResultRegsFile         : > ADCCRESULT, type=NOINIT
   AdcdResultRegsFile         : > ADCDRESULT, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   CanaRegsFile               : > CANA, type=NOINIT
   CanbRegsFile               : > CANB, type=NOINIT
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
   ClbXbarRegsFile            : > CLBXBAR, type=NOINIT
   ClkCfgRegsFile             : > CLKCFG, type=NOINIT
   Cmpss1RegsFile             : > CMPSS1, type=NOINIT
   Cmpss2RegsFile             : > CMPSS2, type=NOINIT
   Cmpss3RegsFile             : > CMPSS3, type=NOINIT
   Cmpss4RegsFile             : > CMPSS4, type=NOINIT
   Cmpss5RegsFile             : > CMPSS5, type=NOINIT
   Cmpss6RegsFile             : > CMPSS6, type=NOINIT
   Cmpss7RegsFile             : > CMPSS7, type=NOINIT
   Cmpss8RegsFile             : > CMPSS8, type=NOINIT
   CpuTimer0RegsFile          : > CPUTIMER0, type=NOINIT
   CpuTimer1RegsFile          : > CPUTIMER1, type=NOINIT
   CpuTimer2RegsFile          : > CPUTIMER2, type=NOINIT
   CpuSysRegsFile             : > CPUSYS, type=NOINIT
   DacaRegsFile               : > DACA, type=NOINIT
   DacbRegsFile               : > DACB, type=NOINIT
   DaccRegsFile               : > DACC, type=NOINIT
   DcsmCommonRegsFile         : > DCSMCOMMON, type=NOINIT
   DcsmZ1RegsFile             : > DCSMZ1, type=NOINIT
   DcsmZ2RegsFile             : > DCSMZ2, type=NOINIT
   DevCfgRegsFile             : > DEVCFG, type=NOINIT
   DmaClaSrcSelRegsFile       : > DMACLASRCSEL, type=NOINIT
   DmaRegsFile                : > DMA, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   ECap2RegsFile              : > ECAP2, type=NOINIT
   ECap3RegsFile              : > ECAP3, type=NOINIT
   ECap4RegsFile              : > ECAP4, type=NOINIT
   ECap5RegsFile              : > ECAP5, type=NOINIT
   ECap6RegsFile              : > ECAP6, type=NOINIT
   Emif1ConfigRegsFile        : > EMIF1CONFIG, type=NOINIT
   Emif2ConfigRegsFile        : > EMIF2CONFIG, type=NOINIT
   Emif1RegsFile              : > EMIF1, type=NOINIT
   Emif2RegsFile              : > EMIF2, type=NOINIT
   EPwm1RegsFile              : > EPWM1, type=NOINIT
   EPwm2RegsFile              : > EPWM2, type=NOINIT
   EPwm3RegsFile              : > EPWM3, type=NOINIT
   EPwm4RegsFile              : > EPWM4, type=NOINIT
   EPwm5RegsFile              : > EPWM5, type=NOINIT
   EPwm6RegsFile              : > EPWM6, type=NOINIT
   EPwm7RegsFile              : > EPWM7, type=NOINIT
   EPwm8RegsFile              : > EPWM8, type=NOINIT
   EPwm9RegsFile              : > EPWM9, type=NOINIT
   EPwm10RegsFile             : > EPWM10, type=NOINIT
   EPwm11RegsFile             : > EPWM11, type=NOINIT
   EPwm12RegsFile             : > EPWM12, type=NOINIT
   EPwmXbarRegsFile           : > EPWMXBAR, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   EQep2RegsFile              : > EQEP2, type=NOINIT
   EQep3RegsFile              : > EQEP3, type=NOINIT
   Flash0CtrlRegsFile         : > FLASH0CTRL, type=NOINIT
   Flash0EccRegsFile          : > FLASH0ECC, type=NOINIT
   FlashPumpSemaphoreRegsFile : > FLASHPUMPSEMAPHORE, type=NOINIT
   GpioCtrlRegsFile           : > GPIOCTRL, type=NOINIT
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   I2cbRegsFile               : > I2CB, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   IpcRegsFile                : > IPC, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   McbspaRegsFile             : > MCBSPA, type=NOINIT
   McbspbRegsFile             : > MCBSPB, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   PieVectTableFile           : > PIEVECTTABLE, type=NOINIT
   RomPrefetchRegsFile        : > ROMPREFETCH, type=NOINIT
   RomWaitStateRegsFile       : > ROMWAITSTATE, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   ScibRegsFile               : > SCIB, type=NOINIT
   ScicRegsFile               : > SCIC, type=NOINIT
   ScidRegsFile               : > SCID, type=NOINIT
   Sdfm1RegsFile              : > SDFM1, type=NOINIT
   Sdfm2RegsFile              : > SDFM2, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SpibRegsFile               : > SPIB, type=NOINIT
   SpicRegsFile               : > SPIC, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   UppRegsFile                : > UPP, type=NOINIT
   WdRegsFile                 : > WD, type=NOINIT
   XbarRegsFile               : > XBAR, type=NOINIT
   XintRegsFile               : > XINT, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

