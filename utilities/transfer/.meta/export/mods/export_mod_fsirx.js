var deviceName = system.deviceData.device;
let exportsInfo = [
    {
        name: "rxerrtagmatch",
        displayName: "RX Error Tag Match",
        type: 'led',
        register: "RX_EVT_STS.ERROR_TAG_MATCH",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_ERROR_TAG_MATCH) == FSI_RX_EVT_STS_ERROR_TAG_MATCH)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxframeoverrun",
        displayName: "RX Frame Overrun",
        type: 'led',
        register: "RX_EVT_STS.FRAME_OVERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_FRAME_OVERRUN) == FSI_RX_EVT_STS_FRAME_OVERRUN)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxerrframe",
        displayName: "RX Error Frame",
        type: 'led',
        register: "RX_EVT_STS.ERR_FRAME",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_ERR_FRAME) == FSI_RX_EVT_STS_ERR_FRAME)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxbufunderrun",
        displayName: "RX Buffer Underrun",
        type: 'led',
        register: "RX_EVT_STS.BUF_UNDERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_BUF_UNDERRUN) == FSI_RX_EVT_STS_BUF_UNDERRUN)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxbufoverrun",
        displayName: "RX Buffer Overrun",
        type: 'led',
        register: "RX_EVT_STS.BUF_OVERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_BUF_OVERRUN) == FSI_RX_EVT_STS_BUF_OVERRUN)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxeoferr",
        displayName: "RX End-of-Frame Error",
        type: 'led',
        register: "RX_EVT_STS.EOF_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_EOF_ERR) == FSI_RX_EVT_STS_EOF_ERR)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxtypeerr",
        displayName: "RX Type Error",
        type: 'led',
        register: "RX_EVT_STS.TYPE_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_TYPE_ERR) == FSI_RX_EVT_STS_TYPE_ERR)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
    {
        name: "rxcrcerr",
        displayName: "RX CRC Error",
        type: 'led',
        register: "RX_EVT_STS.CRC_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_CRC_ERR) == FSI_RX_EVT_STS_CRC_ERR)`,
        applicable: (inst) => {
            return ["F28003x"].includes(deviceName) ? true : false;
        },
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "FsiRx"+ instName.toUpperCase() + "Regs" },
    "fsiRx" : (instName) => { return "FsiRx"+ instName.toUpperCase() + "Regs" },
}

let exportsRegisterSkips = [
    {
        name: "TX_MASTER_CTRL",
        register: "TX_MASTER_CTRL"
    },
    {
        name: "TX_CLK_CTRL",
        register: "TX_CLK_CTRL"
    },
    {
        name: "TX_OPER_CTRL_LO",
        register: "TX_OPER_CTRL_LO"
    },
    {
        name: "TX_OPER_CTRL_HI",
        register: "TX_OPER_CTRL_HI"
    },
    {
        name: "TX_FRAME_CTRL",
        register: "TX_FRAME_CTRL"
    },
    {
        name: "TX_FRAME_TAG_UDATA",
        register: "TX_FRAME_TAG_UDATA"
    },
    {
        name: "TX_BUF_PTR_LOAD",
        register: "TX_BUF_PTR_LOAD"
    },
    {
        name: "TX_BUF_PTR_STS",
        register: "TX_BUF_PTR_STS"
    },
    {
        name: "TX_PING_CTRL",
        register: "TX_PING_CTRL"
    },
    {
        name: "TX_PING_TAG",
        register: "TX_PING_TAG"
    },
    {
        name: "TX_PING_TO_REF",
        register: "TX_PING_TO_REF"
    },
    {
        name: "TX_PING_TO_CNT",
        register: "TX_PING_TO_CNT"
    },
    {
        name: "TX_INT_CTRL",
        register: "TX_INT_CTRL"
    },
    {
        name: "TX_DMA_CTRL",
        register: "TX_DMA_CTRL"
    },
    {
        name: "TX_LOCK_CTRL",
        register: "TX_LOCK_CTRL"
    },
    {
        name: "TX_EVT_STS",
        register: "TX_EVT_STS"
    },
    {
        name: "TX_EVT_CLR",
        register: "TX_EVT_CLR"
    },
    {
        name: "TX_EVT_FRC",
        register: "TX_EVT_FRC"
    },
    {
        name: "TX_USER_CRC",
        register: "TX_USER_CRC"
    },
    {
        name: "TX_ECC_DATA",
        register: "TX_ECC_DATA"
    },
    {
        name: "TX_ECC_VAL",
        register: "TX_ECC_VAL"
    },
    {
        name: "TX_DLYLINE_CTRL",
        register: "TX_DLYLINE_CTRL"
    },
    {
        name: "TX_BUF_BASE(i)",
        register: "TX_BUF_BASE(i)"
    },
    {
        name: "RX_BUF_BASE(i)",
        register: "RX_BUF_BASE(i)"
    },
    
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}