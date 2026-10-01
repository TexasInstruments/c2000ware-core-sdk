let errataPrereqRegisters = [
    {
        description: "ADCAINT1 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL1N2.INT1CONT",
        name: "adcaintsel1",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCAINT2 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL1N2.INT2CONT",
        name: "adcaintsel2",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCAINT3 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL3N4.INT3CONT",
        name: "adcaintsel3",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCAINT4 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL3N4.INT4CONT",
        name: "adcaintsel4",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL1N2.INT1CONT",
        name: "adcbintsel1",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL1N2.INT2CONT",
        name: "adcbintsel2",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL3N4.INT3CONT",
        name: "adcbintsel3",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL3N4.INT4CONT",
        name: "adcbintsel4",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCCINT1 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL1N2.INT1CONT",
        name: "adccintsel1",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCCINT2 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL1N2.INT2CONT",
        name: "adccintsel2",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCCINT3 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL3N4.INT3CONT",
        name: "adccintsel3",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCCINT4 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL3N4.INT4CONT",
        name: "adccintsel4",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "eQEP1 POS COUNTER RESET",
        register: "EQep1Regs.QEPCTL.PCRM",
        name: "eqep1posctrreset",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "eQEP2 POS COUNTER RESET",
        register: "EQep2Regs.QEPCTL.PCRM",
        name: "eqep2posctrreset",
        applicable: (device) => {
            return ["F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCA POWERDOWN",
        register: "AdcaRegs.ADCCTL1.ADCPWDNZ",
        name: "adcapowerdownerrata",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCB POWERDOWN",
        register: "AdcbRegs.ADCCTL1.ADCPWDNZ",
        name: "adcbpowerdownerrata",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCC POWERDOWN",
        register: "AdccRegs.ADCCTL1.ADCPWDNZ",
        name: "adccpowerdownerrata",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCCCLK PRESCALE",
        register: "AdccRegs.ADCCTL2.PRESCALE",
        name: "adccclkprescaleerrata",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK PRESCALE",
        register: "AdcbRegs.ADCCTL2.PRESCALE",
        name: "adcbclkprescaleerrata",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCACLK PRESCALE",
        register: "AdcaRegs.ADCCTL2.PRESCALE",
        name: "adcaclkprescaleerrata",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ERROR THRESHOLD RAM/FLASH",
        register: "MemoryErrorRegs.CERRTHRES.CERRTHRES",
        name: "memoryerrorthreshold",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "PLL REFERENCE CLOCK MISSING FLAG",
        register: "ClkCfgRegs.SYSPLLSTS.REF_LOSTS",
        name: "pllrefclklostflag",
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }
    },
    {
        description: "SYSCLK DIVSEL",
        register: "ClkCfgRegs.SYSCLKDIVSEL.PLLSYSCLKDIV",
        name: "sysclkdivsel",
        applicable: (device) => {
            return ["F280015x"].includes(device);
        }
    },
]

let errataPrereqMemoryLocs = [
    {
        description: "OTP REVISION NUMBER",
        address: "0x000711DE",
        name: "otprevisionnumberMemoryLoc",
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }
    },
    {
        description: "PREFETCH BOUNDARY M1",
        address: "0x000007F8",
        name: "prefetchboundaryMemoryLocM1",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
        {
        description: "PREFETCH BOUNDARY GS3",
        address: "0x0000FFF8",
        name: "prefetchboundaryMemoryLocGS3",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "PREFETCH BOUNDARY FLASH",
        address: "0x000AFFF0",
        name: "prefetchboundaryMemoryLocFlash",
        applicable: (device) => {
            return ["F28003x"].includes(device);    
        }
    },
]

let memoryValueCalculators = [
    {
        name: "otprevisionnumber",
        get: (otprevisionnumberMemoryLoc) => {
            return otprevisionnumberMemoryLoc & 0x000000FF;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }
    },
    {
        name: "prefetchboundarym1",
        get: (prefetchboundaryMemoryLocM1) => {
            return prefetchboundaryMemoryLocM1 & 0xFFFFFFFF;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "prefetchboundarygs3",
        get: (prefetchboundaryMemoryLocGS3) => {
            return prefetchboundaryMemoryLocGS3 & 0xFFFFFFFF;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "prefetchboundaryflash",
        get: (prefetchboundaryMemoryLocFlash) => {
            return prefetchboundaryMemoryLocFlash & 0xFFFFFFFF;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    }
]


let errataChecks = [
    {
        name: "adccContInterruptNotSet",
        displayName: "ADCC INTxCONT Not Set",
        referenceLink : {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0DDFBED-54C9-4F94-BF76-89EBA7ECA72C/TITLE-SPRZ466X3264",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264"
        },
        description: "Future ADC Interrupts may not occur.",
        check: (adccintsel1, adccintsel2, adccintsel3, adccintsel4, adccpowerdownerrata) => {
            if(adccpowerdownerrata == 0)
            {
                return true;
            }
            if(adccintsel1 == 0 || adccintsel2 == 0 || adccintsel3 == 0 || adccintsel4 == 0)
            {
                return false;
                
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "adcbContInterruptNotSet",
        displayName: "ADCB INTxCONT Not Set",
        referenceLink : {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264"
        },
        description: "Future ADC Interrupts may not occur.",
        check: (adcbintsel1, adcbintsel2, adcbintsel3, adcbintsel4, adcbpowerdownerrata) => {
            if(adcbpowerdownerrata == 0)
            {
                return true;
            }
            if(adcbintsel1 == 0 || adcbintsel2 == 0 || adcbintsel3 == 0 || adcbintsel4 == 0)
            {
                return false;
                
            }
            return true;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "adcaContInterruptNotSet",
        displayName: "ADCA INTxCONT Not Set",
        referenceLink : {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0DDFBED-54C9-4F94-BF76-89EBA7ECA72C/TITLE-SPRZ466X3264",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264"
        },          
        check: (adcaintsel1, adcaintsel2, adcaintsel3, adcaintsel4,adcapowerdownerrata) => {
            if(adcapowerdownerrata == 0)
            {
                return true;
            }
            if(adcaintsel1 == 0 || adcaintsel2 == 0 || adcaintsel3 == 0 || adcaintsel4 == 0)
            {
                return false;
                
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "adccFractionalDivider",
        displayName: "ADCC Fractional Divider Set",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-54731D89-E043-44AB-A73D-F6F70AD6168B/TITLE-SPRZ439SPRZ439676",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676"
        },
        check: (adccclkprescaleerrata) => {

            if(adccclkprescaleerrata % 2 != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "adcbFractionalDivider",
        displayName: "ADCB Fractional Divider Set",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676"
        },
        check: (adcbclkprescaleerrata) => {

            if(adcbclkprescaleerrata % 2 != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "adcaFractionalDivider",
        displayName: "ADCA Fractional Divider Set",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-54731D89-E043-44AB-A73D-F6F70AD6168B/TITLE-SPRZ439SPRZ439676",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676"
        },
        check: (adcaclkprescaleerrata) => {
            if(adcaclkprescaleerrata % 2 != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "eqep1PositionCounter",
        displayName: "eQEP1 Position Counter Incorrect Reset",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-379C7C8A-BEED-4B1B-B1D2-1544117F5D22/TITLE-SPRZ466SPRZ4122012",
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-379C7C8A-BEED-4B1B-B1D2-1544117F5D22/TITLE-SPRZ466SPRZ4122012",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-CB9E2FA5-4E20-4F78-81E4-C6224B5057D4/TITLE-SPRZ466SPRZ4122012",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6A08D2E0-DF53-4158-9D7D-8E2ACFF30168/TITLE-SPRZ466SPRZ4122012"
        },
        check: (eqep1posctrreset) => {
            if(eqep1posctrreset == 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "eqep2PositionCounter",
        displayName: "eQEP2 Position Counter Incorrect Reset",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-CB9E2FA5-4E20-4F78-81E4-C6224B5057D4/TITLE-SPRZ466SPRZ4122012",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-CB9E2FA5-4E20-4F78-81E4-C6224B5057D4/TITLE-SPRZ466SPRZ4122012",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6A08D2E0-DF53-4158-9D7D-8E2ACFF30168/TITLE-SPRZ466SPRZ4122012"
        },
        check: (eqep2posctrreset) => {
            if(eqep2posctrreset == 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "mpostNotWorking",
        displayName: "Memory Power-On Self-Test Not Executing",
        referenceLink:{
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-B9FBC6EC-F67C-45B1-94C5-912BE4A5F6F7/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A",
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-B9FBC6EC-F67C-45B1-94C5-912BE4A5F6F7/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A"
        },
        check: (otprevisionnumber) => {
            if(otprevisionnumber <= 2)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
             return ["F280013x"].includes(device);
        }
    },
    {
        name: "mpostNotWorking",
        displayName: "Memory Power-On Self-Test Not Executing",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-2C414985-15EA-48AF-96C8-73249B17C36B/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-2C414985-15EA-48AF-96C8-73249B17C36B/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A"
        },
        check: (otprevisionnumber) => {
            if(otprevisionnumber <= 1)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
             return ["F280015x"].includes(device);
        }
    },
    {
        name: "prefetchBeyondValidMemoryM1",
        displayName: "Prefetching Beyond Valid Memory M1",
        referenceLink:  {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-22BAEE22-C34F-462B-A9E7-AC292157557A/TITLE-SPRZ466SPRZ4588434",
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-22BAEE22-C34F-462B-A9E7-AC292157557A/TITLE-SPRZ466SPRZ4588434",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0A87E1F-5C47-4AFF-99D1-C79207B1949D/TITLE-SPRZ466SPRZ4588434",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundarym1) => {
            if(prefetchboundarym1 != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "prefetchBeyondValidMemoryGS3",
        displayName: "Prefetching Beyond Valid Memory GS3",
        referenceLink: {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundarygs3) => {
            if(prefetchboundarygs3 != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "prefetchValidMemoryFlash",
        displayName: "Prefetching Valid Memory Flash",
        referenceLink: {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundaryflash) => {
            if(prefetchboundaryflash != 65535)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "pllRefClkMissingFlag",
        displayName: "PLL Reference Clock Missing Flag may be Incorrectly Activated",
        referenceLink: {
            "default":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-E8CA025A-80E8-4A6C-BD83-C315C6A9D5C0/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84",
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-E8CA025A-80E8-4A6C-BD83-C315C6A9D5C0/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-8CCCB916-7245-43D1-A7D6-938425ED4F73/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-104EC1C1-D186-471B-B913-5BC8893DEA88/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84"
        },
        check: (pllrefclklostflag) =>{
            if(pllrefclklostflag != 0)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }

    },
    {
        name: "lcmCompareError",
        displayName: "LCM Compare Error can be caused by Consecutive Reset Cycles",
        referenceLink: {
            "default": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-F3608321-4F24-44B2-98E6-2DFF3F8F5811/GUID-7EF13FBF-46F9-43FF-9866-6E290AB1389F",
            "F280015x":"https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-F3608321-4F24-44B2-98E6-2DFF3F8F5811/GUID-7EF13FBF-46F9-43FF-9866-6E290AB1389F"
        },
        check: (sysclkdivsel) => {
            var divValue = (sysclkdivsel)? 2*sysclkdivsel: 1;
            if(divValue == 1)
            {
                return false;
            }
            return true;
        }, 
        applicable: (device) => {
            return  ["F280015x"].includes(device);
        }
    }

]

exports = {
    errataPrereqMemoryLocs: errataPrereqMemoryLocs,
    errataPrereqRegisters: errataPrereqRegisters,
    memoryValueCalculators: memoryValueCalculators,
    errataChecks: errataChecks
} 