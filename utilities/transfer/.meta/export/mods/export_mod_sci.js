var deviceName = system.deviceData.device;
let exportsInfo = [
    {
        name: "fe",
        displayName: "Framing Error",
        type: 'led',
        register: "SCIRXST.FE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_FE) == SCI_RXST_FE)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "pe",
        displayName: "Parity Error",
        type: 'led',
        register: "SCIRXST.PE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_PE) == SCI_RXST_PE)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "oe",
        displayName: "Overrun Error",
        type: 'led',
        register: "SCIRXST.OE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_OE) == SCI_RXST_OE)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },  
    {
        name: "rxffovf",
        displayName: "Receive FIFO Overflow",
        type: 'led',
        register: "SCIFFRX.RXFFOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_FFRX) & SCI_FFRX_RXFFOVF) == SCI_FFRX_RXFFOVF)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName) && inst.useFifo)? true: false;
        }
    },    
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "Sci"+ instName + "Regs" },
}

let exportsRegisterSkips = [
    {
        name: "RXBUF",
        register: "SCIRXBUF"
    }
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}