/* Stucture for ADC Internal Connections with VREFLO*/
// TODO: Verify if need to add individual package support
let ADC_internalSignals = {
    F28002x: {
        A13: "VREFLO",
        C12: "TempSensor",
        C13: "VREFLO",
    },
    F28003x: {
        A13: "VREFLO",
        B13: "VREFLO",
        C12: "TempSensor",
        C13: "VREFLO",
    },
    F280013x: {
        A13: "VREFLO",
        C12: "TempSensor",
        C13: "VREFLO",
    },
	F280015x: {
        A13: "VREFLO",
        C12: "TempSensor",
        C13: "VREFLO",
    },
    F28004x: {
        A13: "VREFLOA",
        B13: "VREFLOB",
        B14: "TempSensor",
        C13: "VREFLOC",
    },
    F2838x: {
        A8: "VREFLOA",
        A9: "VREFLOA",
        A13: "TempSensor",
        B8: "VREFLOB",
        B9: "VREFLOB",
        C8: "VREFLOC",
        C9: "VREFLOC",
        D8: "VREFLOD",
        D9: "VREFLOD",
    }, 
    F2837xD: {
        A8: "VREFLOA",
        A9: "VREFLOA",
        A13: "TempSensor",
        B8: "VREFLOB",
        B9: "VREFLOB",
        C8: "VREFLOC",
        C9: "VREFLOC",
        D8: "VREFLOD",
        D9: "VREFLOD",
    }, 
    F2837xS: {
        A8: "VREFLOA",
        A9: "VREFLOA",
        A13: "TempSensor",
        B8: "VREFLOB",
        B9: "VREFLOB",
        C8: "VREFLOC",
        C9: "VREFLOC",
        D8: "VREFLOD",
        D9: "VREFLOD",
    },
    F2807x: {
        A8: "VREFLOA",
        A9: "VREFLOA",
        A13: "TempSensor",
        B8: "VREFLOB",
        B9: "VREFLOB",
        D8: "VREFLOD",
        D9: "VREFLOD",
    },
}

exports = {
    ADC_internalSignals: ADC_internalSignals,
}