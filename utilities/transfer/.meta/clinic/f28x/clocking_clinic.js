let prereqRegisters = [
    {
        description: "OSCCLK Source Select",
        register: "ClkCfgRegs.CLKSRCCTL1.OSCCLKSRCSEL",
        name: "oscclksrcsel",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "SYSPLL IMULT",
        register: "ClkCfgRegs.SYSPLLMULT.IMULT",
        name: "imult",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "SYSPLL ODIV",
        register: "ClkCfgRegs.SYSPLLMULT.ODIV",
        name: "odiv",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "SYSPLL REFDIV",
        register: "ClkCfgRegs.SYSPLLMULT.REFDIV",
        name: "refdiv",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "SYSPLL CLOCKEN",
        register: "ClkCfgRegs.SYSPLLCTL1.PLLCLKEN",
        name: "syspllclken",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "SYSCLK DIVSEL",
        register: "ClkCfgRegs.SYSCLKDIVSEL.PLLSYSCLKDIV",
        name: "sysclkdivsel",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "LSPCLK DIVSEL",
        register: "ClkCfgRegs.LOSPCP.LSPCLKDIV",
        name: "lspclkdivsel",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCCCLK PRESCALE",
        register: "AdccRegs.ADCCTL2.PRESCALE",
        name: "adccclkprescale",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCBCLK PRESCALE",
        register: "AdcbRegs.ADCCTL2.PRESCALE",
        name: "adcbclkprescale",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCACLK PRESCALE",
        register: "AdcaRegs.ADCCTL2.PRESCALE",
        name: "adcaclkprescale",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCA POWERDOWN",
        register: "AdcaRegs.ADCCTL1.ADCPWDNZ",
        name: "adcapowerdown",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        description: "ADCB POWERDOWN",
        register: "AdcbRegs.ADCCTL1.ADCPWDNZ",
        name: "adcbpowerdown",
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        description: "ADCC POWERDOWN",
        register: "AdccRegs.ADCCTL1.ADCPWDNZ",
        name: "adccpowerdown",
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    }
]


let clockCalculators = [
     {
        name: "oscclk",
        get: (oscclksrcsel, xtal) => {
            if (oscclksrcsel == 0) {
                return 10000000;
            }
            return 10000000;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "pllrawclk",
        get: (oscclk, refdiv, imult, odiv) => {
            return oscclk/(refdiv+1)*imult/(odiv+1);
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "intclk",
        get: (oscclk, refdiv) => {
            return oscclk/(refdiv + 1);
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "vcoclk",
        get: (oscclk, refdiv, imult) =>{
            return oscclk/(refdiv + 1)*imult;
        },
        applicable: (device) => {
            return  ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "pllsysclk",
        get: (oscclk, pllrawclk, syspllclken, sysclkdivsel) => {
            if (syspllclken){
                var divValue = (sysclkdivsel)? 2*sysclkdivsel: 1;
                return pllrawclk/divValue;
            }
            else
            {
                return oscclk/sysclkdivsel;
            }
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "sysclk",
        get: (pllsysclk) => {
            return pllsysclk
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "lspclk",
        get: (sysclk, lspclkdivsel) => {

            var divValue = (lspclkdivsel)? 2*lspclkdivsel : 1;
            return sysclk/divValue;

        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "adccclk",
        get: (sysclk, adccclkprescale) => {
            var prescaleValue;
            switch(adccclkprescale)
            {
                case 0:
                    prescaleValue = 1.0;
                    break;
                case 1:
                    console.log("Invalid Input");
                    return false;
                case 2:
                    prescaleValue = 2.0;
                    break;
                default:
                    prescaleValue = ((adccclkprescale - 2.0) * 0.5 ) + 2.0;
                    break;
            }
            return sysclk/prescaleValue;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }
    },
    {
        name: "adccclk",
        get: (sysclk, adccclkprescale) => {
            if(adccclkprescale % 2 != 0)
            {
                console.log("Invalid Input");
                return false;
            }
            var prescaleValue;
            switch(adccclkprescale)
            {
                case 0:
                    prescaleValue = 1.0;
                    break;
                case 1:
                    console.log("Invalid Input");
                    return false;
                case 2:
                    prescaleValue = 2.0;
                    break;
                default:
                    prescaleValue = ((adccclkprescale - 2.0) * 0.5 ) + 2.0;
                    break;
            }
            return sysclk/prescaleValue;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "adcaclk",
        get: (sysclk, adcaclkprescale) => {
            var prescaleValue;
            switch(adcaclkprescale)
            {
                case 0:
                    prescaleValue = 1.0;
                    break;
                case 1:
                    console.log("Invalid Input");
                    return false;
                case 2:
                    prescaleValue = 2.0;
                    break;
                default:
                    prescaleValue = ((adcaclkprescale - 2.0) * 0.5 ) + 2.0;
                    break;
            }
            return sysclk/prescaleValue;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x"].includes(device);
        }
    },
    {
        name: "adcaclk",
        get: (sysclk, adcaclkprescale) => {
            if(adcaclkprescale % 2 != 0)
            {
                console.log("Invalid Input");
                return false;
            }
            var prescaleValue;
            switch(adcaclkprescale)
            {
                case 0:
                    prescaleValue = 1.0;
                    break;
                case 1:
                    console.log("Invalid Input");
                    return false;
                case 2:
                    prescaleValue = 2.0;
                    break;
                default:
                    prescaleValue = ((adcaclkprescale - 2.0) * 0.5 ) + 2.0;
                    break;
            }
            return sysclk/prescaleValue;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "adcbclk",
        get: (sysclk, adcbclkprescale) => {
            if(adcbclkprescale % 2 != 0)
            {
                console.log("Invalid Input");
                return false;
            }
            var prescaleValue;
            switch(adcbclkprescale)
            {
                case 0:
                    prescaleValue = 1.0;
                    break;
                case 1:
                    console.log("Invalid Input");
                    return false;
                case 2:
                    prescaleValue = 2.0;
                    break;
                default:
                    prescaleValue = ((adcbclkprescale - 2.0) * 0.5 ) + 2.0;
                    break;
            }
            return sysclk/prescaleValue;
        },
        applicable: (device) => {
            return ["F28003x"].includes(device);
        }
    },
    {
        name: "epwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }

    },
    {
        name: "hrpwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    }
]


let clockingChecks = [
    {
        name: "sysclkMaxMinFreq",
        displayName: "SYSCLK Max/Min Freq",
        check: (sysclk) => {
            if (sysclk > 120000000 || sysclk < 2000000)
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
        name: "pllsysclkMaxMinFreq",
        displayName: "PLLSYSCLK Max/Min Freq",
        check: (pllsysclk) => {
            if (pllsysclk > 120000000 || pllsysclk < 2000000)
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
        name: "lspclkMaxMinFreq",
        displayName: "LSPCLK Max/Min Freq",
        check: (lspclk) => {
            if(lspclk > 120000000 || lspclk < 2000000)
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
        name: "pllrawclkMaxMinFreq",
        displayName: "PLLRAWCLK Max/Min Freq",
        check: (pllrawclk) => {
            if(pllrawclk > 240000000 || pllrawclk < 6000000)
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
        name: "vcoclkMaxMinFreq",
        displayName: "VCOCLK Max/Min Freq",
        check: (vcoclk) =>{
            if(vcoclk >  600000000|| vcoclk < 220000000){
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    },
    {
        name: "intclkMaxMinFreq",
        displayName: "INTCLK Max/Min Freq",
        check: (intclk) => {
            if(intclk > 20000000 || intclk < 2000000)
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
        name: "adccclkMaxMinFreq",
        displayName: "ADCCCLK Max/Min Freq",
        check: (adccclk,adccpowerdown) => {
            if(adccpowerdown == 0)
            {
                return true;
            }
            if(adccclk > 60000000 || adccclk < 5000000)
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
        name: "adcbclkMaxMinFreq",
        displayName: "ADCBCLK Max/Min Freq",
        check: (adcbclk,adcbpowerdown) => {
            if(adcbpowerdown == 0)
            {
                return true;
            }
            if(adcbclk > 60000000 || adcbclk < 5000000)
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
        name: "adcaclkMaxMinFreq",
        displayName: "ADCACLK Max/Min Freq",
        check: (adcaclk,adcapowerdown) => {
            if(adcapowerdown == 0)
            {
                return true;
            }
            if(adcaclk > 60000000 || adcaclk < 5000000)
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
        name: "epwmclkMaxfreq",
        displayName: "EPWMCLK Max Freq",
        check: (epwmclk) => {
            if(epwmclk > 120000000)
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
        name: "hrpwmMaxMinfreq",
        displayName: "HRPWMCLK Max/Min Freq",
        check: (hrpwmclk) => {
            if(hrpwmclk > 120000000 || hrpwmclk < 60000000)
            {
                return false;
            }
            return true;
        },
        applicable: (device) => {
            return ["F280013x", "F280015x", "F28003x"].includes(device);
        }
    }
]


exports = {
    prereqRegisters: prereqRegisters,
    clockCalculators: clockCalculators,
    clockingChecks: clockingChecks
}