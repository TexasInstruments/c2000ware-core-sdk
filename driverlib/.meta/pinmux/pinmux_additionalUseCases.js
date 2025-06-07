let Common   = system.getScript("/driverlib/Common.js");

var F28X7X_SERIES = [
    "F2837xD",
    "F2837xS",
    "F2807x"
]

var ALL_DEVICES = [
    "F28004x",
    "F28003x",
    "F28002x",
    "F2838x",
    "F280013x",
    "F280015x",
    "F2837xD",
    "F2837xS",
    "F2807x",
    "F28P65x",
    "F28P55x",
    "F28E12x"
]



let ADDITIONAL_USECASES = {
    EQEP : [
        {
            name: "NO STROBE",
            interfaces: [
                "EQEP#A",
                "EQEP#B",
                "EQEP#I",
            ],
            devices: F28X7X_SERIES
        },
        {
            name: "NO STROBE",
            interfaces: [
                "EQEP#_A", 
                "EQEP#_B", 
                "EQEP#_INDEX", 
            ],
            devices: Common.removeArrayFromArray(ALL_DEVICES, F28X7X_SERIES)
        }
    ],
    ECAT : [
        {
            name: "EVM",
            interfaces: [
                "ESC_I2C_SDA",
                "ESC_I2C_SCL",
                "ESC_TX1_DATA0",
                "ESC_TX1_DATA1",
                "ESC_TX1_DATA2",
                "ESC_TX1_DATA3",
                "ESC_MDIO_CLK",
                "ESC_MDIO_DATA",
                "ESC_PHY_CLK",
                "ESC_RX1_CLK",
                "ESC_RX1_DV",
                "ESC_RX1_ERR",
                "ESC_RX1_DATA0",
                "ESC_RX1_DATA1",
                "ESC_RX1_DATA2",
                "ESC_RX1_DATA3",
                "ESC_PHY_RESETn",
                "ESC_LED_RUN",
                "ESC_LED_ERR",
                "ESC_LED_LINK0_ACTIVE",
                "ESC_LED_LINK1_ACTIVE",
                "ESC_RX0_CLK",
                "ESC_RX0_DV",
                "ESC_RX0_ERR",
                "ESC_RX0_DATA0",
                "ESC_RX0_DATA1",
                "ESC_RX0_DATA2",
                "ESC_RX0_DATA3",
                "ESC_TX0_ENA",
                "ESC_TX0_CLK",
                "ESC_TX0_DATA0",
                "ESC_TX0_DATA1",
                "ESC_TX0_DATA2",
                "ESC_TX0_DATA3",
                "ESC_TX1_ENA",
                "ESC_TX1_CLK",
                "ESC_PHY0_LINKSTATUS",
                "ESC_PHY1_LINKSTATUS",
            ],
            devices: ["F28P65x","F2838x"]
        }
    ]
}

function getAdditionalUseCase(periph)
{
    if (ADDITIONAL_USECASES[periph]){
        return ADDITIONAL_USECASES[periph].filter(useCase => useCase.devices.includes(Common.getDeviceName()))
    }
    return null
    
}


function getAdditionalUseCaseNames(periph)
{
    if (ADDITIONAL_USECASES[periph]){
        return ADDITIONAL_USECASES[periph].filter(useCase => useCase.devices.includes(Common.getDeviceName())).map(useCase => useCase.name)
    }
    return null
    
}

function getAdditionalUseCaseInterfaces(periph, useCase)
{
    var additionalUseCases = getAdditionalUseCase(periph)
    if (additionalUseCases){
        var selectedAddUseCase = additionalUseCases.filter(addUseCase => (addUseCase.name == useCase));
        if (selectedAddUseCase && selectedAddUseCase[0])
        {
            return selectedAddUseCase[0].interfaces
        }
    }
        
    return null
}


exports = {
    getAdditionalUseCase : getAdditionalUseCase,
    getAdditionalUseCaseInterfaces : getAdditionalUseCaseInterfaces,
    getAdditionalUseCaseNames : getAdditionalUseCaseNames
}