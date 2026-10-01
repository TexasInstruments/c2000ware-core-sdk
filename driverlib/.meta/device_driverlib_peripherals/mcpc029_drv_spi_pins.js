let drvPins = {
    PICO: {
        SPIA: {pins:["GPIO7, SDI"]},
    },
    POCI: {
        SPIA: {pins:["GPIO45, SDO"]},
    },
    CLK: {
        SPIA: {pins:["GPIO41, SCLK"]},
    },
    PTE: {
        SPIA: {pins:["GPIO23, NSCS"]},
    }
}

module.exports = {
	drvPins: drvPins,
}