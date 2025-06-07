/* Stucture for comparator input signals per device and CMPSS Instance*/
let CMPSS_comparatorInputSignals = {
    F28002x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/C9"},
            {name: "1", displayName: "A11/C0"},
            {name: "2", displayName: "A6"},
            {name: "3", displayName: "A15/C7"},
            {name: "4", displayName: "A1"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A12/C1"},
            {name: "2", displayName: "A9/C8"},
            {name: "3", displayName: "A10/C10"},
            {name: "4", displayName: "A8/C11 "},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "C6"},
            {name: "1", displayName: "A5/C2 "},
            {name: "2", displayName: "A0/C15"},
            {name: "3", displayName: "A3/C5/VDAC"},
            {name: "4", displayName: "A14/C4"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A9/C8"},
            {name: "1", displayName: "A7/C3"},
            {name: "2", displayName: "A12/C1"},
            {name: "3", displayName: "A4/C14"},
            {name: "4", displayName: "A8/C11 "},
        ]
    },
    F28003x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/B6/C9"},
            {name: "1", displayName: "A11/B10/C0"},
            {name: "2", displayName: "A6"},
            {name: "3", displayName: "A15"},
            {name: "4", displayName: "A1/B7/DACB_OUT"},
            {name: "5", displayName: "B5"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4/B8"},
            {name: "1", displayName: "A12"},
            {name: "2", displayName: "A9"},
            {name: "3", displayName: "A10/B1/C10"},
            {name: "4", displayName: "B0/C11"},
            {name: "5", displayName: "A5"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2/C6"},
            {name: "1", displayName: "B12/C2"},
            {name: "2", displayName: "A0/B15/C15/DACA_OUT"},
            {name: "3", displayName: "B3/VDAC"},
            {name: "4", displayName: "A14/B14/C4"},
            {name: "5", displayName: "A3"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "B4/C8"},
            {name: "1", displayName: "A7/C3"},
            {name: "2", displayName: "C1"},
            {name: "3", displayName: "C14"},
            {name: "4", displayName: "A8"},
            {name: "5", displayName: "B11"},
        ]
    },
    F280013x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/C9"},
            {name: "1", displayName: "A11/C0"},
            {name: "2", displayName: "A6"},
            {name: "3", displayName: "A15/C7"},
            {name: "4", displayName: "A1"},
        ]
    },
	F280015x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/C9"},
            {name: "1", displayName: "A11/C0"},
            {name: "2", displayName: "A6"},
            {name: "3", displayName: "A15/C7"},
            {name: "4", displayName: "A1"},
        ]
    },
    F28004x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/B6/PGA1_OF"},
            {name: "1", displayName: "C0"},
            {name: "2", displayName: "PGA1_IN"},
            {name: "3", displayName: "A3"},
            {name: "4", displayName: "PGA1_OUT"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4/B8/PGA2_OF"},
            {name: "1", displayName: "C1"},
            {name: "2", displayName: "PGA2_IN"},
            {name: "3", displayName: "A5"},
            {name: "4", displayName: "PGA2_OUT"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2/C6/PGA3_OF"},
            {name: "1", displayName: "C2"},
            {name: "2", displayName: "PGA3_IN"},
            {name: "3", displayName: "B3/VDAC"},
            {name: "4", displayName: "PGA3_OUT"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "B4/C8/PGA4_OF"},
            {name: "1", displayName: "C3"},
            {name: "2", displayName: "PGA4_IN"},
            {name: "3", displayName: "B5"},
            {name: "4", displayName: "PGA4_OUT"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "A6/PGA5_OF"},
            {name: "1", displayName: "C4"},
            {name: "2", displayName: "PGA5_IN"},
            {name: "3", displayName: "A7"},
            {name: "4", displayName: "PGA5_OUT"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "A8/PGA6_OF "},
            {name: "1", displayName: "C5"},
            {name: "2", displayName: "PGA6_IN"},
            {name: "3", displayName: "A9"},
            {name: "4", displayName: "PGA6_OUT"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "A10/B1/C10/PGA7_OF"},
            {name: "1", displayName: "C14"},
            {name: "2", displayName: "PGA7_IN"},
            {name: "3", displayName: "B0"},
            {name: "4", displayName: "PGA7_OUT"},
        ],
    },
    F28P65x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2"},
            {name: "1", displayName: "A0/DACA_OUT"},
            {name: "2", displayName: "A1"},
            {name: "3", displayName: "A3"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4"},
            {name: "1", displayName: "B8"},
            {name: "2", displayName: "B9"},
            {name: "3", displayName: "A5"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2"},
            {name: "1", displayName: "B0/VDAC"},
            {name: "2", displayName: "B1/DACC_OUT"},
            {name: "3", displayName: "TempSensor"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A14/B14/C14"},
            {name: "1", displayName: "B10"},
            {name: "2", displayName: "B11"},
            {name: "3", displayName: "A15/B15/C15"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "C4"},
            {name: "1", displayName: "B4"},
            {name: "2", displayName: "B5"},
            {name: "3", displayName: "TempSensor"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "C2"},
            {name: "1", displayName: "C0"},
            {name: "2", displayName: "C1"},
            {name: "3", displayName: "0.9*VREFHIA"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "A6"},
            {name: "1", displayName: "B6"},
            {name: "2", displayName: "B7"},
            {name: "3", displayName: "0.9*VREFHIB"},
        ],
        CMPSS8_BASE: [
            {name: "0", displayName: "A8"},
            {name: "1", displayName: "A10"},
            {name: "2", displayName: "A11"},
            {name: "3", displayName: "0.9*VREFHIC"},
        ],
        CMPSS9_BASE: [
            {name: "0", displayName: "B13"},
            {name: "1", displayName: "C13"},
            {name: "2", displayName: "A7"},
        ],
        CMPSS10_BASE: [
            {name: "0", displayName: "C10"},
            {name: "1", displayName: "C6"},
            {name: "2", displayName: "C8"},
        ],
        CMPSS11_BASE: [
            {name: "0", displayName: "C11"},
            {name: "1", displayName: "C7"},
            {name: "2", displayName: "C9"},
        ],
    },
    F28P55x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/B6/C9/PGA1_INP"},
            {name: "1", displayName: "A11/B10/C0/PGA2_OUT"},
            {name: "2", displayName: "A6/D14/E14"},
            {name: "3", displayName: "A15"},
            {name: "4", displayName: "A1/B7/D11/DACB_OUT"},
            {name: "5", displayName: "B5/D15/E15"},
            {name: "6", displayName: "PGA1_OUT_INT"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4/B8"},
            {name: "1", displayName: "A12"},
            {name: "2", displayName: "A9"},
            {name: "3", displayName: "A10/B1/C10/B0/C11/GPIO253"},
            {name: "4", displayName: "NA"},
            {name: "5", displayName: "A5"},
            {name: "6", displayName: "PGA3_OUT_INT"},
            {name: "7", displayName: "TempSensor"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2/C6/E12"},
            {name: "1", displayName: "B12/C2/PGA2_INM"},
            {name: "2", displayName: "A0/B15/C15/DACA_OUT"},
            {name: "3", displayName: "B3/PGA2_INP"},
            {name: "4", displayName: "A14/B14/C4/PGA1_OUT"},
            {name: "5", displayName: "A3"},
            {name: "6", displayName: "PGA2_OUT_INT"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "B4/C8"},
            {name: "1", displayName: "A7/B30/C3/D12/E30"},
            {name: "2", displayName: "C1/E11/PGA3_INP"},
            {name: "3", displayName: "C14"},
            {name: "4", displayName: "A8/B0/C11"},
            {name: "5", displayName: "B11/D16/E16"},
        ]
    },
}

/* Stucture for comparator negative input signals per device & CMPSS Instance*/
let CMPSS_comparatorNegInputSignals = {
    F28002x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A15/C7"},
            {name: "1", displayName: "A11/C0"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A10/C10"},
            {name: "1", displayName: "A12/C1"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "A3/C5"},
            {name: "1", displayName: "A5/C2"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A7/C3"},
        ],
    },
    F28003x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A15/B9"}, /* not avl in 100PZ*/
            {name: "1", displayName: "A11"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A10/B1"},
            {name: "1", displayName: "A12/C5"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B3"},
            {name: "1", displayName: "B12"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "C14"},
            {name: "1", displayName: "A7/C3"},
        ],
    },
    F28004x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A3"},
            {name: "1", displayName: "C0"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A5"},
            {name: "1", displayName: "C1"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B3"},
            {name: "1", displayName: "C2"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "Rsv"}, /*Check: HN0/LN0 not avl for CMPSS4*/
            {name: "1", displayName: "C3"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "Rsv"}, /*Check: HN0/LN0 not avl for CMPSS5*/
            {name: "1", displayName: "C4"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "A9"},
            {name: "1", displayName: "C5"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "B0"},
            {name: "1", displayName: "C14"},
        ],
    },
    F280013x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A15/C7"},
            {name: "1", displayName: "A11/C0"},
        ],
    },
    F280015x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A15/C7"},
            {name: "1", displayName: "A11/C0"},
        ],
    },
    F28P65x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A3"},
            {name: "1", displayName: "A1"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A5"},
            {name: "1", displayName: "A2"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B3"},
            {name: "1", displayName: "B7"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A15/B15/C15"},
            {name: "1", displayName: "B10"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "C5"},
            {name: "1", displayName: "B4"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "C3"},
            {name: "1", displayName: "C0"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "A7"},
            {name: "1", displayName: "B6"},
        ],
        CMPSS8_BASE: [
            {name: "0", displayName: "A9"},
            {name: "1", displayName: "A10"},
        ],
        CMPSS9_BASE: [
            {name: "0", displayName: "A0/DACA_OUT"},
            {name: "1", displayName: "B9"},
        ],
        CMPSS10_BASE: [
            {name: "0", displayName: "B8"},
            {name: "1", displayName: "C4"},
        ],
        CMPSS11_BASE: [
            {name: "0", displayName: "B0/VDAC"},
            {name: "1", displayName: "C13"},
        ],
    },
    F28P55x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A15"}, /* not avl in 100PZ*/
            {name: "1", displayName: "A11/B10/C0/PGA2_OUT"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A10/B1/C10"},
            {name: "1", displayName: "A12"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B3/PGA2_INP"},
            {name: "1", displayName: "B12/C2/PGA2_INM"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "C14"},
            {name: "1", displayName: "A7/B30/C3/D12/E30"},
        ],
    },
}

/* Stucture for comparator low positive input signals per device & CMPSS Instance (currently only for F28P65x)*/
let CMPSS_comparatorLowPositiveInputSignals = {
    F28P65x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2"},
            {name: "1", displayName: "A0/DACA_OUT"},
            {name: "2", displayName: "A1"},
            {name: "3", displayName: "B3"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4"},
            {name: "1", displayName: "B8"},
            {name: "2", displayName: "B9"},
            {name: "3", displayName: "C5"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2"},
            {name: "1", displayName: "B0/VDAC"},
            {name: "2", displayName: "B1/DACC_OUT"},
            {name: "3", displayName: "C3"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "A14/B14/C14"},
            {name: "1", displayName: "B10"},
            {name: "2", displayName: "B11"},
            {name: "3", displayName: "A7"},
        ],
        CMPSS5_BASE: [
            {name: "0", displayName: "C4"},
            {name: "1", displayName: "B4"},
            {name: "2", displayName: "B5"},
            {name: "3", displayName: "A9"},
        ],
        CMPSS6_BASE: [
            {name: "0", displayName: "C2"},
            {name: "1", displayName: "C0"},
            {name: "2", displayName: "C1"},
            {name: "3", displayName: "0.9*VREFHIA"},
        ],
        CMPSS7_BASE: [
            {name: "0", displayName: "A6"},
            {name: "1", displayName: "B6"},
            {name: "2", displayName: "B7"},
            {name: "3", displayName: "0.9*VREFHIB"},
        ],
        CMPSS8_BASE: [
            {name: "0", displayName: "A8"},
            {name: "1", displayName: "A10"},
            {name: "2", displayName: "A11"},
            {name: "3", displayName: "0.9*VREFHIC"},
        ],
        CMPSS9_BASE: [
            {name: "0", displayName: "B13"},
            {name: "1", displayName: "C13"},
            {name: "2", displayName: "A5"},
        ],
        CMPSS10_BASE: [
            {name: "0", displayName: "C10"},
            {name: "1", displayName: "C6"},
            {name: "2", displayName: "C8"},
        ],
        CMPSS11_BASE: [
            {name: "0", displayName: "C11"},
            {name: "1", displayName: "C7"},
            {name: "2", displayName: "C9"},
        ],
    },
    F28P55x: {
        CMPSS1_BASE: [
            {name: "0", displayName: "A2/B6/C9/PGA1_INP"},
            {name: "1", displayName: "A11/B10/C0/PGA2_OUT"},
            {name: "2", displayName: "A6/D14/E14"},
            {name: "3", displayName: "A15"},
            {name: "4", displayName: "A1/B7/D11/DACB_OUT"},
            {name: "5", displayName: "B5/D15/E15"},
            {name: "6", displayName: "PGA1_OUT_INT"},
        ],
        CMPSS2_BASE: [
            {name: "0", displayName: "A4/B8"},
            {name: "1", displayName: "A12"},
            {name: "2", displayName: "A9"},
            {name: "3", displayName: "A10/B1/C10"},
            {name: "4", displayName: "NA"},
            {name: "5", displayName: "A5"},
            {name: "6", displayName: "PGA3_OUT_INT"},
        ],
        CMPSS3_BASE: [
            {name: "0", displayName: "B2/C6/E12"},
            {name: "1", displayName: "B12/C2/PGA2_INM"},
            {name: "2", displayName: "A0/B15/C15/DACA_OUT"},
            {name: "3", displayName: "B3/PGA2_INP"},
            {name: "4", displayName: "A14/B14/C4/PGA1_OUT"},
            {name: "5", displayName: "A3"},
            {name: "6", displayName: "PGA2_OUT_INT"},
        ],
        CMPSS4_BASE: [
            {name: "0", displayName: "B4/C8"},
            {name: "1", displayName: "A7/B30/C3/D12/E30"},
            {name: "2", displayName: "C1/E11/PGA3_INP"},
            {name: "3", displayName: "C14"},
            {name: "4", displayName: "A8/B0/C11"},
            {name: "5", displayName: "B11/D16/E16"},
        ]
    },
}

exports = {
    CMPSS_comparatorInputSignals: CMPSS_comparatorInputSignals,
    CMPSS_comparatorNegInputSignals: CMPSS_comparatorNegInputSignals,
    CMPSS_comparatorLowPositiveInputSignals: CMPSS_comparatorLowPositiveInputSignals,
}
