let exportsInfo = [
    {
        name: "fe",
        displayName: "Framing Error",
        type: 'led',
        register: "SCIRXST.FE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_FE) == SCI_RXST_FE)`,
        applicable: (inst) => true
    },
    {
        name: "pe",
        displayName: "Parity Error",
        type: 'led',
        register: "SCIRXST.PE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_PE) == SCI_RXST_PE)`,
        applicable: (inst) => true
    },  
    {
        name: "rxffovf",
        displayName: "Receive FIFO Overflow",
        type: 'led',
        register: "SCIFFRX.RXFFOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_FFRX) & SCI_FFRX_RXFFOVF) == SCI_FFRX_RXFFOVF)`,
        applicable: (inst) => inst.useFifo
    },    
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "Sci"+ instName + "Regs" },
}

let exportsRegisterSkips = [
    {
        name: "RXBUF"
    }
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}