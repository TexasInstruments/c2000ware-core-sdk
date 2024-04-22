let BGCRC_NMI = [
	{ name: "BGCRC_NMI_ENABLE", displayName: "Generate NMI on memory check failure" },
	{ name: "BGCRC_NMI_DISABLE", displayName: "Do not generate NMI on memory check" },
]
let BGCRC_EMUCTRL = [
	{ name: "BGCRC_EMUCTRL_SOFT", displayName: "CRC module and CRC watchdog stops" },
	{ name: "BGCRC_EMUCTRL_FREE", displayName: "CRC calculation and CRC watchdog is" },
]
let BGCRC_SIZE = [
	{ name: "BGCRC_SIZE_BYTES_0", displayName: "SIZE BYTES 0" },
	{ name: "BGCRC_SIZE_BYTES_256", displayName: "SIZE BYTES 256" },
	{ name: "BGCRC_SIZE_BYTES_512", displayName: "SIZE BYTES 512" },
	{ name: "BGCRC_SIZE_BYTES_768", displayName: "SIZE BYTES 768" },
	{ name: "BGCRC_SIZE_KBYTES(x)", displayName: "SIZE KBYTES(X)" },
]
let BGCRC_REG = [
	{ name: "BGCRC_REG_EN", displayName: "REG EN" },
	{ name: "BGCRC_REG_CTRL1", displayName: "REG CTRL1" },
	{ name: "BGCRC_REG_CTRL2", displayName: "REG CTRL2" },
	{ name: "BGCRC_REG_START_ADDR", displayName: "REG START ADDR" },
	{ name: "BGCRC_REG_SEED", displayName: "REG SEED" },
	{ name: "BGCRC_REG_GOLDEN", displayName: "REG GOLDEN" },
	{ name: "BGCRC_REG_WD_CFG", displayName: "REG WD CFG" },
	{ name: "BGCRC_REG_WD_MIN", displayName: "REG WD MIN" },
	{ name: "BGCRC_REG_WD_MAX", displayName: "REG WD MAX" },
	{ name: "BGCRC_REG_NMIFRC", displayName: "REG NMIFRC" },
	{ name: "BGCRC_REG_INTEN", displayName: "REG INTEN" },
	{ name: "BGCRC_REG_INTFRC", displayName: "REG INTFRC" },
	{ name: "BGCRC_REG_ALL", displayName: "REG ALL" },
]
module.exports = {
	BGCRC_NMI: BGCRC_NMI,
	BGCRC_EMUCTRL: BGCRC_EMUCTRL,
	BGCRC_SIZE: BGCRC_SIZE,
	BGCRC_REG: BGCRC_REG,
}
