let exportsInfo = [
    {
        name: "clkf",
        displayName: "Clock Fail",
        type: 'led',
        register: "NMIFLG.CLOCKFAIL",
        bitfiledInstanceNames: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CLOCKFAIL) == NMI_FLG_CLOCKFAIL)`,
        applicable: (inst) => true
    },
    {
        name: "ramuncerr",
        displayName: "RAM Uncorrectable Error",
        type: 'led',
        register: "NMIFLG.RAMUNCERR",
        bitfiledInstanceNames: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_RAMUNCERR) == NMI_FLG_RAMUNCERR)`,
        applicable: (inst) => true
    },
    {
        name: "fluncerr",
        displayName: "Flash Uncorrectable Error",
        type: 'led',
        register: "NMIFLG.FLUNCERR",
        bitfiledInstanceNames: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_FLUNCERR) == NMI_FLG_FLUNCERR)`,
        applicable: (inst) => true
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "NmiIntruptRegs" },
    "nmi": (instName) => { return "NmiIntruptRegs" },
}

let exportsRegisterSkips = [
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}