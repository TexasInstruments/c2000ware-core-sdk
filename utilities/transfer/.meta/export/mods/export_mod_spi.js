//=============================================================================
// export_mod_spi.js - SPI Export Module for CDT
//=============================================================================
// Purpose: Expose SPI diagnostic information for Clinic Diagnostic Tool
// Devices: All Gen3 devices have SPI peripheral
// Reference: driverlib/<device>/driverlib/inc/hw_spi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_SPI = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // SPI Status Flags (SPI_O_STS)
    //-------------------------------------------------------------------------
    {
        name: "overrun",
        displayName: "Receiver Overrun",
        description: "Receive buffer overrun error. RED indicates new data arrived before previous was read, causing data loss. Increase read rate or use FIFO mode.",
        type: 'led',
        register: "SPISTS.OVERRUN_FLAG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_STS) & SPI_STS_OVERRUN_FLAG) == SPI_STS_OVERRUN_FLAG)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "intflag",
        displayName: "SPI Interrupt Flag",
        description: "SPI interrupt pending. GREEN indicates transfer complete or data ready. Set when configured interrupt event occurs.",
        type: 'led',
        register: "SPISTS.INT_FLAG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_STS) & SPI_STS_INT_FLAG) == SPI_STS_INT_FLAG)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "buffull",
        displayName: "TX Buffer Full",
        description: "Transmit buffer full. GREEN indicates data is waiting to be shifted out. Writing when full overwrites pending data.",
        type: 'led',
        register: "SPISTS.BUFFULL_FLAG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_STS) & SPI_STS_BUFFULL_FLAG) == SPI_STS_BUFFULL_FLAG)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // SPI FIFO Status
    //-------------------------------------------------------------------------
    {
        name: "rxffovf",
        displayName: "RX FIFO Overflow",
        description: "Receive FIFO overflow error. RED indicates FIFO was full when new data arrived. Data was lost. Read FIFO faster or enable flow control.",
        type: 'led',
        register: "SPIFFRX.RXFFOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFRX) & SPI_FFRX_RXFFOVF) == SPI_FFRX_RXFFOVF)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "txffint",
        displayName: "TX FIFO Interrupt Flag",
        description: "TX FIFO level reached threshold. GREEN indicates TX FIFO has room for more data. Use to trigger DMA or ISR to refill transmit FIFO.",
        type: 'led',
        register: "SPIFFTX.TXFFINT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFTX) & SPI_FFTX_TXFFINT) == SPI_FFTX_TXFFINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "rxffint",
        displayName: "RX FIFO Interrupt Flag",
        description: "RX FIFO level reached threshold. GREEN indicates receive data available. Use to trigger DMA or ISR to read received data.",
        type: 'led',
        register: "SPIFFRX.RXFFINT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFRX) & SPI_FFRX_RXFFINT) == SPI_FFRX_RXFFINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "txffst",
        displayName: "TX FIFO Level",
        description: "Number of words currently in TX FIFO (0-16). Shows how much transmit data is queued. 0 means FIFO empty, 16 means FIFO full.",
        type: 'value',
        register: "SPIFFTX.TXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFTX) & SPI_FFTX_TXFFST_M) >> SPI_FFTX_TXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
    {
        name: "rxffst",
        displayName: "RX FIFO Level",
        description: "Number of words currently in RX FIFO (0-16). Shows how much receive data is waiting. 0 means FIFO empty, 16 means FIFO full.",
        type: 'value',
        register: "SPIFFRX.RXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SPI_O_FFRX) & SPI_FFRX_RXFFST_M) >> SPI_FFRX_RXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_SPI.includes(deviceName);
        }
    },
]

let bitfieldInstanceNames = {
    "default": (instName) => { return "Spi"+ instName + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (volatile data registers)
// Note: FIFO registers contain W1C bits (TXFFINTCLR, RXFFINTCLR, RXFFOVFCLR)
// but these are handled as bitfields within FFTX/FFRX, not separate registers
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    { name: "RXBUF", register: "SPIRXBUF" },
    { name: "TXBUF", register: "SPITXBUF" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}