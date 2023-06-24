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
    "F2807x"
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