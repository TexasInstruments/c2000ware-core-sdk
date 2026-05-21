//=============================================================================
// export_mod_i2c.js - I2C Export Module for CDT
//=============================================================================
// Purpose: Expose I2C diagnostic information for Clinic Diagnostic Tool
// Devices: All Gen3 devices have I2C peripheral
// Reference: driverlib/<device>/driverlib/inc/hw_i2c.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_I2C = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // I2C Status Flags (I2C_O_STR) - Error Conditions
    //-------------------------------------------------------------------------
    {
        name: "arbl",
        displayName: "Arbitration Lost",
        description: "I2C bus arbitration lost. RED indicates another master took control of the bus. Retry transaction or check for bus conflicts.",
        type: 'led',
        register: "I2CSTR.ARBL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_ARBL) == I2C_STR_ARBL)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "nack",
        displayName: "No Acknowledgement",
        description: "NACK received from slave. RED indicates slave did not acknowledge address or data. Check slave address, wiring, and pull-up resistors.",
        type: 'led',
        register: "I2CSTR.NACK",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_NACK) == I2C_STR_NACK)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "nacksnt",
        displayName: "NACK Sent",
        description: "This device sent NACK. GREEN indicates we intentionally rejected incoming data (e.g., end of read transfer in slave mode).",
        type: 'led',
        register: "I2CSTR.NACKSNT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_NACKSNT) == I2C_STR_NACKSNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // I2C Status Flags - Bus State
    //-------------------------------------------------------------------------
    {
        name: "bb",
        displayName: "Bus Busy",
        description: "I2C bus is busy. GREEN indicates a transfer is in progress (by this or another master). Wait for idle before starting new transaction.",
        type: 'led',
        register: "I2CSTR.BB",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_BB) == I2C_STR_BB)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "scd",
        displayName: "Stop Condition Detected",
        description: "I2C STOP condition detected. GREEN indicates transaction ended. Used to identify transfer completion.",
        type: 'led',
        register: "I2CSTR.SCD",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_SCD) == I2C_STR_SCD)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // I2C Status Flags - Data Ready
    //-------------------------------------------------------------------------
    {
        name: "rrdy",
        displayName: "Receive Data Ready",
        description: "Receive data available. GREEN indicates byte received and ready to read from I2CDRR. Read promptly to avoid overrun.",
        type: 'led',
        register: "I2CSTR.RRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_RRDY) == I2C_STR_RRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "xrdy",
        displayName: "Transmit Data Ready",
        description: "Ready to transmit. GREEN indicates I2CDXR can accept new data byte. Write data to continue transfer.",
        type: 'led',
        register: "I2CSTR.XRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_XRDY) == I2C_STR_XRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "rsfull",
        displayName: "Receive Shift Register Full",
        description: "Receive shift register full. GREEN indicates byte being clocked in from bus. Will transfer to I2CDRR when complete.",
        type: 'led',
        register: "I2CSTR.RSFULL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_RSFULL) == I2C_STR_RSFULL)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "xsmt",
        displayName: "Transmit Shift Register Empty",
        description: "Transmit shift register empty. GREEN indicates all bits shifted out. Data from I2CDXR will load when available.",
        type: 'led',
        register: "I2CSTR.XSMT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_XSMT) == I2C_STR_XSMT)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // I2C Slave Mode Status
    //-------------------------------------------------------------------------
    {
        name: "aas",
        displayName: "Addressed As Slave",
        description: "Device addressed as slave. GREEN indicates a master is communicating with this device. Active during slave transactions.",
        type: 'led',
        register: "I2CSTR.AAS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_AAS) == I2C_STR_AAS)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "sdir",
        displayName: "Slave Direction (1=TX)",
        description: "Slave transfer direction. GREEN = master is reading (slave transmits), OFF = master is writing (slave receives).",
        type: 'led',
        register: "I2CSTR.SDIR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_SDIR) == I2C_STR_SDIR)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // I2C FIFO Status
    //-------------------------------------------------------------------------
    {
        name: "txffint",
        displayName: "TX FIFO Interrupt Flag",
        description: "TX FIFO reached threshold. GREEN indicates FIFO level at or below programmed level. Use to refill transmit data.",
        type: 'led',
        register: "I2CFFTX.TXFFINT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_FFTX) & I2C_FFTX_TXFFINT) == I2C_FFTX_TXFFINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "rxffint",
        displayName: "RX FIFO Interrupt Flag",
        description: "RX FIFO reached threshold. GREEN indicates FIFO level at or above programmed level. Use to read received data.",
        type: 'led',
        register: "I2CFFRX.RXFFINT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_FFRX) & I2C_FFRX_RXFFINT) == I2C_FFRX_RXFFINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "txffst",
        displayName: "TX FIFO Level",
        description: "Number of bytes in TX FIFO (0-4). Shows pending transmit data. 0 means FIFO empty, 4 means FIFO full.",
        type: 'value',
        register: "I2CFFTX.TXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_FFTX) & I2C_FFTX_TXFFST_M) >> I2C_FFTX_TXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
    {
        name: "rxffst",
        displayName: "RX FIFO Level",
        description: "Number of bytes in RX FIFO (0-4). Shows received data waiting. 0 means FIFO empty, 4 means FIFO full.",
        type: 'value',
        register: "I2CFFRX.RXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_FFRX) & I2C_FFRX_RXFFST_M) >> I2C_FFRX_RXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_I2C.includes(deviceName);
        }
    },
]

let bitfieldInstanceNames = {
    "default": (instName) => { return "I2c"+ instName + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (volatile data registers)
// Note: FIFO registers contain W1C bits (TXFFINTCLR, RXFFINTCLR)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    { name: "DRR", register: "I2CDRR" },
    { name: "DXR", register: "I2CDXR" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}