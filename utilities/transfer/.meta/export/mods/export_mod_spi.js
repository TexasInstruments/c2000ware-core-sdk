let exportsInfo = [
    {
        name: "ffovf",
        displayName: "FIFO Overflow Error",
        type: 'led',
        register: "SPIFFRX.RXFFOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFRX) & SPI_FFRX_RXFFOVF) == SPI_FFRX_RXFFOVF)`,
        applicable: (inst) => inst.useFifo
    },
    {
        name: "overrun",
        displayName: "Overrun Error",
        type: 'led',
        register: "SPISTS.OVERRUN_FLAG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_STS) & SPI_STS_OVERRUN_FLAG) == SPI_STS_OVERRUN_FLAG)`,
        applicable: (inst) => !inst.useFifo
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "Spi"+ instName + "Regs" },
}

let exportsRegisterSkips = [
    {
        name: "RXBUF"
    }
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames: bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}