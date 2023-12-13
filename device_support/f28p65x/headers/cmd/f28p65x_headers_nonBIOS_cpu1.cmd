MEMORY
{
 PAGE 0:    /* Program Memory */
 PAGE 1:    /* Data Memory */
   ACCESSPROTECTION           : origin = 0x0005F500, length = 0x0000003E
   ADCA                       : origin = 0x00007400, length = 0x00000100
   ADCB                       : origin = 0x00007500, length = 0x00000100
   ADCC                       : origin = 0x00007600, length = 0x00000100
   ADCARESULT                 : origin = 0x00000A00, length = 0x00000048
   ADCBRESULT                 : origin = 0x00000A80, length = 0x00000048
   ADCCRESULT                 : origin = 0x00000B00, length = 0x00000048
   ADCSAFETYINTEVTAGG1        : origin = 0x0005EE00, length = 0x00000040
   ADCSAFETYCHK1              : origin = 0x0005EE80, length = 0x00000010
   ADCSAFETYCHK2              : origin = 0x0005EE90, length = 0x00000010
   ADCSAFETYCHK3              : origin = 0x0005EEA0, length = 0x00000010
   ADCSAFETYCHK4              : origin = 0x0005EEB0, length = 0x00000010
   ADCSAFETYCHK5              : origin = 0x0005EEC0, length = 0x00000010
   ADCSAFETYCHK6              : origin = 0x0005EED0, length = 0x00000010
   ADCSAFETYCHK7              : origin = 0x0005EEE0, length = 0x00000010
   ADCSAFETYCHK8              : origin = 0x0005EEF0, length = 0x00000010
   ANALOGSUBSYS               : origin = 0x0005D700, length = 0x00000136
   BGCRCCPU                   : origin = 0x00006340, length = 0x00000040
   BGCRCCLA                   : origin = 0x00006380, length = 0x00000040
   CANA                       : origin = 0x00048000, length = 0x00000200
   CLA1                       : origin = 0x00001400, length = 0x00000080
   CLB1DATAEXCH               : origin = 0x00002180, length = 0x00000080
   CLB2DATAEXCH               : origin = 0x00002380, length = 0x00000080
   CLB3DATAEXCH               : origin = 0x00002580, length = 0x00000080
   CLB4DATAEXCH               : origin = 0x00002780, length = 0x00000080
   CLB5DATAEXCH               : origin = 0x00002980, length = 0x00000080
   CLB6DATAEXCH               : origin = 0x00002B80, length = 0x00000080
   CLB1LOGICCFG               : origin = 0x00002000, length = 0x00000052
   CLB2LOGICCFG               : origin = 0x00002200, length = 0x00000052
   CLB3LOGICCFG               : origin = 0x00002400, length = 0x00000052
   CLB4LOGICCFG               : origin = 0x00002600, length = 0x00000052
   CLB5LOGICCFG               : origin = 0x00002800, length = 0x00000052
   CLB6LOGICCFG               : origin = 0x00002A00, length = 0x00000052
   CLB1LOGICCTRL              : origin = 0x00002100, length = 0x00000040
   CLB2LOGICCTRL              : origin = 0x00002300, length = 0x00000040
   CLB3LOGICCTRL              : origin = 0x00002500, length = 0x00000040
   CLB4LOGICCTRL              : origin = 0x00002700, length = 0x00000040
   CLB5LOGICCTRL              : origin = 0x00002900, length = 0x00000040
   CLB6LOGICCTRL              : origin = 0x00002B00, length = 0x00000040
   CLBXBAR                    : origin = 0x00007A80, length = 0x00000040
   CLKCFG                     : origin = 0x0005D200, length = 0x00000100
   CMPSS1                     : origin = 0x00005900, length = 0x00000040
   CMPSS2                     : origin = 0x00005940, length = 0x00000040
   CMPSS3                     : origin = 0x00005980, length = 0x00000040
   CMPSS4                     : origin = 0x000059C0, length = 0x00000040
   CMPSS5                     : origin = 0x00005A00, length = 0x00000040
   CMPSS6                     : origin = 0x00005A40, length = 0x00000040
   CMPSS7                     : origin = 0x00005A80, length = 0x00000040
   CMPSS8                     : origin = 0x00005AC0, length = 0x00000040
   CMPSS9                     : origin = 0x00005B00, length = 0x00000040
   CMPSS10                    : origin = 0x00005B40, length = 0x00000040
   CMPSS11                    : origin = 0x00005B80, length = 0x00000040
   CPU1TOCPU2IPC              : origin = 0x0005CE00, length = 0x00000026
   DMACLASRCSEL               : origin = 0x00007980, length = 0x0000001A
   LFU                        : origin = 0x00007FE0, length = 0x00000020
   PERIPHAC                   : origin = 0x0005D500, length = 0x00000200
   CPUSYS                     : origin = 0x0005D300, length = 0x00000100
   SYSSTATUS                  : origin = 0x0005D400, length = 0x00000050
   CPUTIMER0                  : origin = 0x00000C00, length = 0x00000008
   CPUTIMER1                  : origin = 0x00000C08, length = 0x00000008
   CPUTIMER2                  : origin = 0x00000C10, length = 0x00000008
   DACA                       : origin = 0x00005C00, length = 0x00000008
   DACC                       : origin = 0x00005C20, length = 0x00000008
   DCC0                       : origin = 0x0005E700, length = 0x00000038
   DCC1                       : origin = 0x0005E740, length = 0x00000038
   DCC2                       : origin = 0x0005E780, length = 0x00000038
   DCSMCOMMON                 : origin = 0x0005F0C0, length = 0x00000046
   DCSMZ1                     : origin = 0x0005F000, length = 0x00000040
   DCSMZ2                     : origin = 0x0005F080, length = 0x00000040
   DEVCFG                     : origin = 0x0005D000, length = 0x000001E8
   DMA                        : origin = 0x00001000, length = 0x00000200
   ECAP1                      : origin = 0x00005200, length = 0x00000020
   ECAP2                      : origin = 0x00005300, length = 0x00000020
   ECAP3                      : origin = 0x00005400, length = 0x00000020
   ECAP4                      : origin = 0x00005500, length = 0x00000020
   ECAP5                      : origin = 0x00005600, length = 0x00000020
   ECAP6                      : origin = 0x00005700, length = 0x00000020
   ECAP7                      : origin = 0x00005800, length = 0x00000020
   ECAP1SIGNALMONITORING      : origin = 0x00005240, length = 0x00000060
   ECAP2SIGNALMONITORING      : origin = 0x00005340, length = 0x00000060
   ECAP3SIGNALMONITORING      : origin = 0x00005440, length = 0x00000060
   ECAP4SIGNALMONITORING      : origin = 0x00005540, length = 0x00000060
   ECAP5SIGNALMONITORING      : origin = 0x00005640, length = 0x00000060
   ECAP6SIGNALMONITORING      : origin = 0x00005740, length = 0x00000060
   ECAP7SIGNALMONITORING      : origin = 0x00005840, length = 0x00000060
   EMIF1CONFIG                : origin = 0x0005F4C0, length = 0x00000020
   EPWM17                     : origin = 0x00002C00, length = 0x00000100
   EPWM18                     : origin = 0x00002E00, length = 0x00000100
   EPWM1                      : origin = 0x00003000, length = 0x00000100
   EPWM2                      : origin = 0x00003200, length = 0x00000100
   EPWM3                      : origin = 0x00003400, length = 0x00000100
   EPWM4                      : origin = 0x00003600, length = 0x00000100
   EPWM5                      : origin = 0x00003800, length = 0x00000100
   EPWM6                      : origin = 0x00003A00, length = 0x00000100
   EPWM7                      : origin = 0x00003C00, length = 0x00000100
   EPWM8                      : origin = 0x00003E00, length = 0x00000100
   EPWM9                      : origin = 0x00004000, length = 0x00000100
   EPWM10                     : origin = 0x00004200, length = 0x00000100
   EPWM11                     : origin = 0x00004400, length = 0x00000100
   EPWM12                     : origin = 0x00004600, length = 0x00000100
   EPWM13                     : origin = 0x00004800, length = 0x00000100
   EPWM14                     : origin = 0x00004A00, length = 0x00000100
   EPWM15                     : origin = 0x00004C00, length = 0x00000100
   EPWM16                     : origin = 0x00004E00, length = 0x00000100
   EPWMXBARB                  : origin = 0x00007800, length = 0x00000070
   EPWMXBARA                  : origin = 0x00007A00, length = 0x00000070
   EQEP1                      : origin = 0x00005080, length = 0x00000040
   EQEP2                      : origin = 0x000050C0, length = 0x00000040
   EQEP3                      : origin = 0x00005100, length = 0x00000040
   EQEP4                      : origin = 0x00005140, length = 0x00000040
   EQEP5                      : origin = 0x00005180, length = 0x00000040
   EQEP6                      : origin = 0x000051C0, length = 0x00000040
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
   ESCSSCONFIG                : origin = 0x00057F00, length = 0x00000016
   ESCSS                      : origin = 0x00057E00, length = 0x00000024
   FLASH0CTRL                 : origin = 0x0005F800, length = 0x00000182
   FLASH0ECC                  : origin = 0x0005FB00, length = 0x00000028
   FSIRXA                     : origin = 0x00006680, length = 0x00000050
   FSIRXB                     : origin = 0x00006780, length = 0x00000050
   FSIRXC                     : origin = 0x00006880, length = 0x00000050
   FSIRXD                     : origin = 0x00006980, length = 0x00000050
   FSITXA                     : origin = 0x00006600, length = 0x00000050
   FSITXB                     : origin = 0x00006700, length = 0x00000050
   GPIOCTRL                   : origin = 0x00007C00, length = 0x00000200
   GPIODATAREAD               : origin = 0x00007F80, length = 0x00000010
   GPIODATA                   : origin = 0x00007F00, length = 0x00000040
   HRCAP6                     : origin = 0x00005720, length = 0x00000020
   HRCAP7                     : origin = 0x00005820, length = 0x00000020
   HWBIST                     : origin = 0x0005E000, length = 0x000000D0
   I2CA                       : origin = 0x00007300, length = 0x00000022
   I2CB                       : origin = 0x00007340, length = 0x00000022
   ICLXBAR                    : origin = 0x000079E0, length = 0x00000020
   INPUTXBAR                  : origin = 0x00007900, length = 0x00000020
   CLBINPUTXBAR               : origin = 0x00007960, length = 0x00000020
   LINA                       : origin = 0x00006E00, length = 0x000000EC
   LINB                       : origin = 0x00006F00, length = 0x000000EC
   MCANASS                    : origin = 0x0005A400, length = 0x0000002C
   MCANBSS                    : origin = 0x0005C400, length = 0x0000002C
   MCANAERROR                 : origin = 0x0005A800, length = 0x00000210
   MCANBERROR                 : origin = 0x0005C800, length = 0x00000210
   MCANA                      : origin = 0x0005A600, length = 0x00000100
   MCANB                      : origin = 0x0005C600, length = 0x00000100
   MEMORYERROR                : origin = 0x0005F540, length = 0x00000040
   MEMCFG                     : origin = 0x0005F400, length = 0x000000C0
   NMIINTRUPT                 : origin = 0x00007060, length = 0x00000010
   HRPWMCAL1                   : origin = 0x00005C80, length = 0x00000040
   HRPWMCAL2                   : origin = 0x00005CC0, length = 0x00000040
   HRPWMCAL3                   : origin = 0x00005D00, length = 0x00000040
   OUTPUTXBAR                 : origin = 0x00007B00, length = 0x00000070
   CLBOUTPUTXBAR              : origin = 0x00007B80, length = 0x00000070
   ERADPCTRACE                : origin = 0x0005EAD0, length = 0x0000000A
   PIECTRL                    : origin = 0x00000CE0, length = 0x0000001A
   PIEVECTTABLE               : origin = 0x00000D00, length = 0x00000200
   PMBUSA                     : origin = 0x00006400, length = 0x00000020
   ROMWAITSTATE               : origin = 0x0005F580, length = 0x00000002
   SCIA                       : origin = 0x00007200, length = 0x00000010
   SCIB                       : origin = 0x00007210, length = 0x00000010
   SDFM1                      : origin = 0x00005E00, length = 0x00000080
   SDFM2                      : origin = 0x00005E80, length = 0x00000080
   SDFM3                      : origin = 0x00005F00, length = 0x00000080
   SDFM4                      : origin = 0x00005F80, length = 0x00000080
   SPIA                       : origin = 0x00006100, length = 0x00000010
   SPIB                       : origin = 0x00006110, length = 0x00000010
   SPIC                       : origin = 0x00006120, length = 0x00000010
   SPID                       : origin = 0x00006130, length = 0x00000010
   SYNCSOC                    : origin = 0x000078F8, length = 0x00000008
   TESTERROR                  : origin = 0x0005F590, length = 0x00000010
   UARTA                      : origin = 0x0006A000, length = 0x00000800
   UARTB                      : origin = 0x0006A800, length = 0x00000800
   WD                         : origin = 0x00007000, length = 0x0000002C
   XBAR                       : origin = 0x00007920, length = 0x00000040
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
   AdcSafetyIntEvtAgg1RegsFile: > ADCSAFETYINTEVTAGG1, type=NOINIT
   ADCSafetyChk1RegsFile      : > ADCSAFETYCHK1, type=NOINIT
   ADCSafetyChk2RegsFile      : > ADCSAFETYCHK2, type=NOINIT
   ADCSafetyChk3RegsFile      : > ADCSAFETYCHK3, type=NOINIT
   ADCSafetyChk4RegsFile      : > ADCSAFETYCHK4, type=NOINIT
   ADCSafetyChk5RegsFile      : > ADCSAFETYCHK5, type=NOINIT
   ADCSafetyChk6RegsFile      : > ADCSAFETYCHK6, type=NOINIT
   ADCSafetyChk7RegsFile      : > ADCSAFETYCHK7, type=NOINIT
   ADCSafetyChk8RegsFile      : > ADCSAFETYCHK8, type=NOINIT
   AnalogSubsysRegsFile       : > ANALOGSUBSYS, type=NOINIT
   BgcrcCpuRegsFile           : > BGCRCCPU, type=NOINIT
   BgcrcClaRegsFile           : > BGCRCCLA, type=NOINIT
   CanaRegsFile               : > CANA, type=NOINIT
   Cla1RegsFile               : > CLA1, type=NOINIT
   Clb1DataExchRegsFile       : > CLB1DATAEXCH, type=NOINIT
   Clb2DataExchRegsFile       : > CLB2DATAEXCH, type=NOINIT
   Clb3DataExchRegsFile       : > CLB3DATAEXCH, type=NOINIT
   Clb4DataExchRegsFile       : > CLB4DATAEXCH, type=NOINIT
   Clb5DataExchRegsFile       : > CLB5DATAEXCH, type=NOINIT
   Clb6DataExchRegsFile       : > CLB6DATAEXCH, type=NOINIT
   Clb1LogicCfgRegsFile       : > CLB1LOGICCFG, type=NOINIT
   Clb2LogicCfgRegsFile       : > CLB2LOGICCFG, type=NOINIT
   Clb3LogicCfgRegsFile       : > CLB3LOGICCFG, type=NOINIT
   Clb4LogicCfgRegsFile       : > CLB4LOGICCFG, type=NOINIT
   Clb5LogicCfgRegsFile       : > CLB5LOGICCFG, type=NOINIT
   Clb6LogicCfgRegsFile       : > CLB6LOGICCFG, type=NOINIT
   Clb1LogicCtrlRegsFile      : > CLB1LOGICCTRL, type=NOINIT
   Clb2LogicCtrlRegsFile      : > CLB2LOGICCTRL, type=NOINIT
   Clb3LogicCtrlRegsFile      : > CLB3LOGICCTRL, type=NOINIT
   Clb4LogicCtrlRegsFile      : > CLB4LOGICCTRL, type=NOINIT
   Clb5LogicCtrlRegsFile      : > CLB5LOGICCTRL, type=NOINIT
   Clb6LogicCtrlRegsFile      : > CLB6LOGICCTRL, type=NOINIT
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
   Cmpss9RegsFile             : > CMPSS9, type=NOINIT
   Cmpss10RegsFile            : > CMPSS10, type=NOINIT
   Cmpss11RegsFile            : > CMPSS11, type=NOINIT
   Cpu1toCpu2IpcRegsFile      : > CPU1TOCPU2IPC, type=NOINIT
   DmaClaSrcSelRegsFile       : > DMACLASRCSEL, type=NOINIT
   LfuRegsFile                : > LFU, type=NOINIT
   PeriphAcRegsFile           : > PERIPHAC, type=NOINIT
   CpuSysRegsFile             : > CPUSYS, type=NOINIT
   SysStatusRegsFile          : > SYSSTATUS, type=NOINIT
   CpuTimer0RegsFile          : > CPUTIMER0, type=NOINIT
   CpuTimer1RegsFile          : > CPUTIMER1, type=NOINIT
   CpuTimer2RegsFile          : > CPUTIMER2, type=NOINIT
   DacaRegsFile               : > DACA, type=NOINIT
   DaccRegsFile               : > DACC, type=NOINIT
   Dcc0RegsFile               : > DCC0, type=NOINIT
   Dcc1RegsFile               : > DCC1, type=NOINIT
   Dcc2RegsFile               : > DCC2, type=NOINIT
   DcsmCommonRegsFile         : > DCSMCOMMON, type=NOINIT
   DcsmZ1RegsFile             : > DCSMZ1, type=NOINIT
   DcsmZ2RegsFile             : > DCSMZ2, type=NOINIT
   DevCfgRegsFile             : > DEVCFG, type=NOINIT
   DmaRegsFile                : > DMA, type=NOINIT
   ECap1RegsFile              : > ECAP1, type=NOINIT
   ECap2RegsFile              : > ECAP2, type=NOINIT
   ECap3RegsFile              : > ECAP3, type=NOINIT
   ECap4RegsFile              : > ECAP4, type=NOINIT
   ECap5RegsFile              : > ECAP5, type=NOINIT
   ECap6RegsFile              : > ECAP6, type=NOINIT
   ECap7RegsFile              : > ECAP7, type=NOINIT
   ECap1SignalMonitoringRegsFile: > ECAP1SIGNALMONITORING, type=NOINIT
   ECap2SignalMonitoringRegsFile: > ECAP2SIGNALMONITORING, type=NOINIT
   ECap3SignalMonitoringRegsFile: > ECAP3SIGNALMONITORING, type=NOINIT
   ECap4SignalMonitoringRegsFile: > ECAP4SIGNALMONITORING, type=NOINIT
   ECap5SignalMonitoringRegsFile: > ECAP5SIGNALMONITORING, type=NOINIT
   ECap6SignalMonitoringRegsFile: > ECAP6SIGNALMONITORING, type=NOINIT
   ECap7SignalMonitoringRegsFile: > ECAP7SIGNALMONITORING, type=NOINIT
   Emif1ConfigRegsFile        : > EMIF1CONFIG, type=NOINIT
   EPwm17RegsFile             : > EPWM17, type=NOINIT
   EPwm18RegsFile             : > EPWM18, type=NOINIT
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
   EPwm13RegsFile             : > EPWM13, type=NOINIT
   EPwm14RegsFile             : > EPWM14, type=NOINIT
   EPwm15RegsFile             : > EPWM15, type=NOINIT
   EPwm16RegsFile             : > EPWM16, type=NOINIT
   EPwmXbarBRegsFile          : > EPWMXBARB, type=NOINIT
   EPwmXbarARegsFile          : > EPWMXBARA, type=NOINIT
   EQep1RegsFile              : > EQEP1, type=NOINIT
   EQep2RegsFile              : > EQEP2, type=NOINIT
   EQep3RegsFile              : > EQEP3, type=NOINIT
   EQep4RegsFile              : > EQEP4, type=NOINIT
   EQep5RegsFile              : > EQEP5, type=NOINIT
   EQep6RegsFile              : > EQEP6, type=NOINIT
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
   EscssConfigRegsFile        : > ESCSSCONFIG, type=NOINIT
   EscssRegsFile              : > ESCSS, type=NOINIT
   Flash0CtrlRegsFile         : > FLASH0CTRL, type=NOINIT
   Flash0EccRegsFile          : > FLASH0ECC, type=NOINIT
   FsiRxaRegsFile             : > FSIRXA, type=NOINIT
   FsiRxbRegsFile             : > FSIRXB, type=NOINIT
   FsiRxcRegsFile             : > FSIRXC, type=NOINIT
   FsiRxdRegsFile             : > FSIRXD, type=NOINIT
   FsiTxaRegsFile             : > FSITXA, type=NOINIT
   FsiTxbRegsFile             : > FSITXB, type=NOINIT
   GpioCtrlRegsFile           : > GPIOCTRL, type=NOINIT
   GpioDataReadRegsFile       : > GPIODATAREAD, type=NOINIT
   GpioDataRegsFile           : > GPIODATA, type=NOINIT
   HRCap6RegsFile             : > HRCAP6, type=NOINIT
   HRCap7RegsFile             : > HRCAP7, type=NOINIT
   HwbistRegsFile             : > HWBIST, type=NOINIT
   I2caRegsFile               : > I2CA, type=NOINIT
   I2cbRegsFile               : > I2CB, type=NOINIT
   IclXbarRegsFile            : > ICLXBAR, type=NOINIT
   InputXbarRegsFile          : > INPUTXBAR, type=NOINIT
   ClbInputXbarRegsFile       : > CLBINPUTXBAR, type=NOINIT
   LinaRegsFile               : > LINA, type=NOINIT
   LinbRegsFile               : > LINB, type=NOINIT
   McanaSsRegsFile            : > MCANASS, type=NOINIT
   McanbSsRegsFile            : > MCANBSS, type=NOINIT
   McanaErrorRegsFile         : > MCANAERROR, type=NOINIT
   McanbErrorRegsFile         : > MCANBERROR, type=NOINIT
   McanaRegsFile              : > MCANA, type=NOINIT
   McanbRegsFile              : > MCANB, type=NOINIT
   MemoryErrorRegsFile        : > MEMORYERROR, type=NOINIT
   MemCfgRegsFile             : > MEMCFG, type=NOINIT
   NmiIntruptRegsFile         : > NMIINTRUPT, type=NOINIT
   HRPWMCAL1RegsFile           : > HRPWMCAL1, type=NOINIT
   HRPWMCAL2RegsFile           : > HRPWMCAL2, type=NOINIT
   HRPWMCAL3RegsFile           : > HRPWMCAL3, type=NOINIT
   OutputXbarRegsFile         : > OUTPUTXBAR, type=NOINIT
   ClbOutputXbarRegsFile      : > CLBOUTPUTXBAR, type=NOINIT
   EradPCTraceRegsFile        : > ERADPCTRACE, type=NOINIT
   PieCtrlRegsFile            : > PIECTRL, type=NOINIT
   PieVectTableMainFile       : > PIEVECTTABLE type=NOINIT
   PmbusaRegsFile             : > PMBUSA, type=NOINIT
   RomWaitStateRegsFile       : > ROMWAITSTATE, type=NOINIT
   SciaRegsFile               : > SCIA, type=NOINIT
   ScibRegsFile               : > SCIB, type=NOINIT
   Sdfm1RegsFile              : > SDFM1, type=NOINIT
   Sdfm2RegsFile              : > SDFM2, type=NOINIT
   Sdfm3RegsFile              : > SDFM3, type=NOINIT
   Sdfm4RegsFile              : > SDFM4, type=NOINIT
   SpiaRegsFile               : > SPIA, type=NOINIT
   SpibRegsFile               : > SPIB, type=NOINIT
   SpicRegsFile               : > SPIC, type=NOINIT
   SpidRegsFile               : > SPID, type=NOINIT
   SyncSocRegsFile            : > SYNCSOC, type=NOINIT
   TestErrorRegsFile          : > TESTERROR, type=NOINIT
   UartARegsFile              : > UARTA, type=NOINIT
   UartBRegsFile              : > UARTB, type=NOINIT
   WdRegsFile                 : > WD, type=NOINIT
   XbarRegsFile               : > XBAR, type=NOINIT
   XintRegsFile               : > XINT, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

