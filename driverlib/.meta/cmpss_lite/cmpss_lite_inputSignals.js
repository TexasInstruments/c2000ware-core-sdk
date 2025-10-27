/* Stucture for comparator positive input signals per device & CMPSS Instance*/
let CMPSSLITE_comparatorInputSignals = {
    F280013x: {
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A12/C1"},
            {name: "2", displayName: "A9/C8"},
            {name: "3", displayName: "A10/C10"},
            {name: "4", displayName: "A8/C11"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "C6"},
            {name: "1", displayName: "A5/C2"},
            {name: "2", displayName: "A0/C15"},
            {name: "3", displayName: "A3/C5"},
            {name: "4", displayName: "A14/C4"},
        ],
        CMPSSLITE4_BASE: [
            {name: "0", displayName: "C8/A9"},
            {name: "1", displayName: "A7/C3"},
            {name: "2", displayName: "A12/C1"},
            {name: "3", displayName: "A4/C14"},
            {name: "4", displayName: "A8/C11"},
        ]
    },
    F28E12x: {
        CMPSSLITE1_BASE: [
            {name: "0", displayName: "A2"},
            {name: "1", displayName: "A11"},
            {name: "2", displayName: "A6"},
            {name: "3", displayName: "A15"},
            {name: "4", displayName: "A1"},
            {name: "5", displayName: "NA"},
            {name: "6", displayName: "NA"},
        ],
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A4"},
            {name: "1", displayName: "A12"},
            {name: "2", displayName: "A9"},
            {name: "3", displayName: "A10"},
            {name: "4", displayName: "A8"},
            {name: "5", displayName: "NA"},
            {name: "6", displayName: "PGA1_OUT_INT"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "A21"},
            {name: "1", displayName: "A5"},
            {name: "2", displayName: "A0"},
            {name: "3", displayName: "A3"},
            {name: "4", displayName: "A14"},
            {name: "5", displayName: "NA"},
            {name: "6", displayName: "NA"},
        ]
    },

    F280015x: {
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A12/C1"},
            {name: "2", displayName: "A9/C8"},
            {name: "3", displayName: "A10/C10"},
            {name: "4", displayName: "A8/C11"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "C6"},
            {name: "1", displayName: "A5/C2"},
            {name: "2", displayName: "A0/C15/CMP1_DACL"},
            {name: "3", displayName: "A3/C5"},
            {name: "4", displayName: "A14/C4"},
        ],
        CMPSSLITE4_BASE: [
            {name: "0", displayName: "A9/C8"},
            {name: "1", displayName: "A7/C3"},
            {name: "2", displayName: "A12/C1"},
            {name: "3", displayName: "A4/C14"},
            {name: "4", displayName: "A8/C11"},
        ]
    },
}

/* Stucture for comparator negative input signals per device & CMPSS Instance*/
let CMPSSLITE_comparatorNegInputSignals = {
    F280013x: {
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A10/C10"},
            {name: "1", displayName: "A12/C1"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "A3/C5"},
            {name: "1", displayName: "A5/C2"},
        ],
        CMPSSLITE4_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A7/C3"},
        ]
    },

    F28E12x: {
        CMPSSLITE1_BASE: [
            {name: "0", displayName: "A15"},
            {name: "1", displayName: "A11"},
        ],
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A10"},
            {name: "1", displayName: "A12"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "A3"},
            {name: "1", displayName: "A5"},
        ]
    },

    F280015x: {
        CMPSSLITE2_BASE: [
            {name: "0", displayName: "A10/C10"},
            {name: "1", displayName: "A12/C1"},
        ],
        CMPSSLITE3_BASE: [
            {name: "0", displayName: "A3/C5"},
            {name: "1", displayName: "A5/C2"},
        ],
        CMPSSLITE4_BASE: [
            {name: "0", displayName: "A4/C14"},
            {name: "1", displayName: "A7/C3"},
        ]
    },
}

exports = {
    CMPSSLITE_comparatorInputSignals: CMPSSLITE_comparatorInputSignals,
    CMPSSLITE_comparatorNegInputSignals: CMPSSLITE_comparatorNegInputSignals,
}
