let Common   = system.getScript("/driverlib/Common.js");
let PinmuxMigrations   = system.getScript("/driverlib/pinmux/pinmux_migration.js");
let PinmuxAdditionalUseCases   = system.getScript("/driverlib/pinmux/pinmux_additionalUseCases.js");

var NO_DEVICE_PIN_FOUND = "No Device Pin Found"
let PINMUX_QUAL_GROUPNAME = "GROUP_pinmuxQual"


function getGpioQualificationModInstDefinitions(peripheralName, inst){
    var ownedInstances = []
    var selectedPinmuxInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, inst.useCase);
    //console.log(selectedPinmuxInterfaces)
    for (var interfaceName of selectedPinmuxInterfaces)
    {
        var legacyInclusiveNames = PinmuxMigrations.interfaceInclusiveRename(interfaceName, peripheralName);

        //console.log(legacyInclusiveNames)
        //console.log(interfaceName)
        var qualModName = interfaceNameToQualModeName(legacyInclusiveNames.inclusiveName, peripheralName);
        var qualModDisplayName = legacyInclusiveNames.inclusiveName.replace("#", "").replace("@", "").replace("_", " ")
        //console.log(qualModName)

        if(!legacyInclusiveNames.legacyName)
        {
            ownedInstances.push({
                name: qualModName,      
                displayName: qualModDisplayName + " Pin Qualification",
                //legacyNames: legacyInclusiveNames.legacyName,
                moduleName: "/driverlib/gpio/gpioQual.js",
                collapsed: true,
                group: PINMUX_QUAL_GROUPNAME,
                args: {
                    $name : inst.$name + "_" + qualModName,
                },
                requiredArgs : {

                }
            })
        }
        else
        {
            var legacyNamesArray = [];
            for(let i = 0; i < legacyInclusiveNames.legacyName.length; i++)
            {
                var legacyQualName = interfaceNameToQualModeName(legacyInclusiveNames.legacyName[i], peripheralName);
                if((legacyQualName != qualModName) && (!legacyNamesArray.includes(legacyQualName)))
                {
                    legacyNamesArray[i] = legacyQualName
                }
            }

            ownedInstances.push({
                name: qualModName,      
                displayName: qualModDisplayName + " Pin Qualification",
                legacyNames: legacyNamesArray,
                moduleName: "/driverlib/gpio/gpioQual.js",
                collapsed: true,
                group: PINMUX_QUAL_GROUPNAME,
                args: {
                    $name : inst.$name + "_" + qualModName,
                },
                requiredArgs : {
    
                }
            })
        }
        //console.log(ownedInstances);
    }
    return ownedInstances
}

function interfaceNameToQualModeName(interfaceName, peripheralName)
{
    var interfaceNameCopy = PinmuxMigrations.interfaceMigrationRename(interfaceName, peripheralName)
    return interfaceNameCopy.toLowerCase().replace("#", "").replace("@", "").replace("_", "").replace("-", "").replace(peripheralName.toLowerCase(), "") + "Qual"
}

function addPinMuxQualGroupToConfig(mod)
{
    //console.log(mod)
    //console.log(mod.config)
    mod.config.push({
        name: PINMUX_QUAL_GROUPNAME,
        displayName : "PinMux Qualification",
        config: [],
    })
}

function getDeviceDACName(dacInput)
{
    //
    // dacInput is DACA DACB etc.
    //
    var dacout = dacInput + "_OUT"

    if (["F2838x"].includes(Common.getDeviceName()))
    {
        dacout = dacInput.substring(0, 3) + "OUT" + dacInput.substring(3)
        return dacout
    }
    return dacout
}

function getDeviceADCName(adcInput)
{
    if (["F2807x", "F2837xD", "F2837xS" ,"F2838x"].includes(Common.getDeviceName()))
    {
        return "ADCIN" + adcInput;
    }
    else
    {
        return adcInput;
    }
}

// Functions for Calculated Values
function calculateADCPinInfo(inst,sociX){
    var adcMod = inst.adcBase.replace("_BASE", "").replace("ADC", "");
    var sociChannel = inst["soc" + sociX.toString() + "Channel"].replace("ADC_CH_ADCIN", "").replace("ADCIN", "");
    var sociChannels = sociChannel.split("_");
    var adcInputs = "";
    var adcChannelArray = []
    var adcPinInfosDescriptions = "";
    var adcPinInfosArray = [];
    for (sociChannel of sociChannels)
    {
        var adcInput = adcMod + sociChannel;
        adcChannelArray.push(adcInput);
        adcInputs += (adcInputs != "")?", ": "";
        adcInputs += adcInput;

        var adcPinInfos = findAllAnalogPin(getDeviceADCName(adcInput));
        if (["14", "15"].includes(sociChannel))
        {
            if (adcPinInfos.length <= 0)
            {
                adcPinInfos = findAllAnalogPin("ADCIN" + sociChannel);
            }
        }

        adcPinInfosDescriptions += (adcPinInfosDescriptions != "")?", ": "";
        adcPinInfosDescriptions += getDevicePinInfoDescription(adcPinInfos);
        for (var apinfo of adcPinInfos){
            adcPinInfosArray.push(apinfo.PinDesignSignalName);
        }
    }
    return {
        "adcInput":adcInput,
        "adcInputs":adcInputs,
        "adcPinInfosDescriptions":adcPinInfosDescriptions,
        "adcPinInfosArray":adcPinInfosArray,
        "adcChannelArray": adcChannelArray
    }
}

function findAllAnalogPin(selectedChannel)
{
    var selectedPinName = "";
    var selectedPinSignalName = "";
    var replaceCommaWith = "/";
    var pinInfos = [];
    for (var devicePinIndex in system.deviceData.devicePins){
        var devicePin = system.deviceData.devicePins[devicePinIndex]
        if (!isNaN(devicePin.designSignalName)){
            continue
        }
        var pin = devicePin.name.replace(/,/g, replaceCommaWith)
        var pinSignalName = devicePin.designSignalName.replace(/,/g, replaceCommaWith)
        var pinSignalNamesSplitArray = pinSignalName.split('/')
        for (var pinSignalNameSplitIndex = 0;
            pinSignalNameSplitIndex < pinSignalNamesSplitArray.length;
            pinSignalNameSplitIndex++)
        {
            var pinSignalNameSplitItem = pinSignalNamesSplitArray[pinSignalNameSplitIndex].trim();
            if (selectedChannel == pinSignalNameSplitItem)
            {
                selectedPinName = pin;
                selectedPinSignalName = pinSignalName;
                pinInfos = pinInfos.concat([{
                    PinName: selectedPinName,
                    PinSignalName : selectedPinSignalName,
                    PinDesignSignalName: devicePin.designSignalName,
                }]);
            }
        }

    }

    return pinInfos;
}

function findAnalogPin(selectedChannel)
{
    var selectedPinName = "";
    var selectedPinSignalName = "";
    var replaceCommaWith = "/";
    for (var devicePinIndex in system.deviceData.devicePins){
        var devicePin = system.deviceData.devicePins[devicePinIndex]
        if (!isNaN(devicePin.designSignalName)){
            continue
        }
        var pin = devicePin.name.replace(/,/g, replaceCommaWith)
        var pinSignalName = devicePin.designSignalName.replace(/,/g, replaceCommaWith)
        var pinSignalNamesSplitArray = pinSignalName.split('/')
        for (var pinSignalNameSplitIndex = 0;
            pinSignalNameSplitIndex < pinSignalNamesSplitArray.length;
            pinSignalNameSplitIndex++)
        {
            var pinSignalNameSplitItem = pinSignalNamesSplitArray[pinSignalNameSplitIndex].trim();
            if (selectedChannel == pinSignalNameSplitItem)
            {
                selectedPinName = pin;
                selectedPinSignalName = pinSignalName;
                return {
                    valid : true,
                    PinName: selectedPinName,
                    PinSignalName : selectedPinSignalName,
                    PinDesignSignalName : devicePin.designSignalName,
                }
            }
        }

    }

    return {
        valid : false,
        PinName: "",
        PinSignalName : "",
        PinDesignSignalName: "",
    }
}

function getADCPinsUsed()
{
    let device_driverlib_peripheral =
        system.getScript("/driverlib/device_driverlib_peripherals/" +
            Common.getDeviceName().toLowerCase() + "_adc.js");
    var mods = system.modules['/driverlib/adc.js'];
    var adcPins = [];
    if (mods != null)
    {
        for (var modInst of mods.$instances)
        {
            for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
                var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
                var soci = (currentSOC).replace(/[^0-9]/g,'')
                if((modInst.enabledSOCs).includes(currentSOC)){
                    var pinSelectedArray = calculateADCPinInfo(modInst,soci).adcPinInfosArray
                    adcPins = adcPins.concat(pinSelectedArray);
                }
            }
        }
    }
    return adcPins;
}

function getCMPSSPinsUsed()
{
    var mods = system.modules['/driverlib/cmpss.js'];
    let ComparatorInputs = system.getScript("/driverlib/cmpss/cmpss_inputSignals.js")

    var cmpssPins = [];
    if (mods != null)
    {
        for (var modInst of mods.$instances)
        {
            if (modInst.asysCMPHPMXSELValue)
            {
                var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssBase][modInst.asysCMPHPMXSELValue].displayName
                var tempPinNameH = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssBase][modInst.asysCMPHPMXSELValue].displayName
                var tempPinInfoH = findAllAnalogPin(getDeviceADCName(tempPinName.split("/")[0]))

                for (var apinfo of tempPinInfoH){
                    var pinSelected = apinfo.PinDesignSignalName;
                    cmpssPins.push(pinSelected);
                }
            }
            if (modInst.asysCMPLPMXSELValue)
            {
                var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssBase][modInst.asysCMPLPMXSELValue].displayName
                var tempPinNameL = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssBase][modInst.asysCMPLPMXSELValue].displayName
                var tempPinInfoL = findAllAnalogPin(getDeviceADCName(tempPinName.split("/")[0]))

                for (var apinfo of tempPinInfoL){
                    var pinSelected = apinfo.PinDesignSignalName;
                    cmpssPins.push(pinSelected);
                }
            }
        }
    }

    return cmpssPins;
}

function getCMPSSLitePinsUsed()
{
    var mods = system.modules['/driverlib/cmpss_lite.js'];
    let ComparatorLiteInputs = system.getScript("/driverlib/cmpss_lite/cmpss_lite_inputSignals.js")

    var cmpssLitePins = [];
    if (mods != null)
    {
        for (var modInst of mods.$instances)
        {
            if (modInst.asysCMPHPMXSELValue)
            {
                var tempPinName = ComparatorLiteInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssLiteBase][modInst.asysCMPHPMXSELValue].displayName
                var tempPinNameH = ComparatorLiteInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssLiteBase][modInst.asysCMPHPMXSELValue].displayName
                var tempPinInfoH = findAllAnalogPin(getDeviceADCName(tempPinName.split("/")[0]))

                for (var apinfo of tempPinInfoH){
                    var pinSelected = apinfo.PinDesignSignalName;
                    cmpssLitePins.push(pinSelected);
                }
            }
            if (modInst.asysCMPLPMXSELValue)
            {
                var tempPinName = ComparatorLiteInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssLiteBase][modInst.asysCMPLPMXSELValue].displayName
                var tempPinNameL = ComparatorLiteInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][modInst.cmpssLiteBase][modInst.asysCMPLPMXSELValue].displayName
                var tempPinInfoL = findAllAnalogPin(getDeviceADCName(tempPinName.split("/")[0]))

                for (var apinfo of tempPinInfoL){
                    var pinSelected = apinfo.PinDesignSignalName;
                    cmpssLitePins.push(pinSelected);
                }
            }
        }
    }

    return cmpssLitePins;
}

function getDevicePinInfoDescription(pinInfos)
{
    if (pinInfos.length > 0)
    {
        var pinInfoDescriptions = "";
        for (var pinInfo of pinInfos)
        {
            pinInfoDescriptions += pinInfo.PinName + ": " + pinInfo.PinSignalName + ", ";
        }
        pinInfoDescriptions = pinInfoDescriptions.substring(0, pinInfoDescriptions.length - ", ".length);
        return pinInfoDescriptions;
    }
    else
    {
        return NO_DEVICE_PIN_FOUND
    }
}

function useCaseChanged(inst, ui)
{
    try
    {
        if (inst.useCase == "CUSTOM") {
            ui.useInterfacePins.hidden = false;
        }
        else {
            ui.useInterfacePins.hidden = true;
        }
    } catch (error)
    {
        console.log("An error occured when changing the pinmux usecase");
    }
}

function addCustomPinmuxEnumToConfig(module)
{
    var peripheralName = module.peripheralName;

    var options = []
    var InterfaceNames = getPeripheralInterfaces(peripheralName);
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];
        try
        {
            if (interfaceName.includes("EMU0") || interfaceName.includes("EMU1") || interfaceName.includes("AUXCLKIN"))
            {
                continue;
            }
        } catch (error) {}
        var interfaceInclusiveName = PinmuxMigrations.interfaceInclusiveRename(interfaceName, peripheralName)
        options.push({name:interfaceName, displayName:interfaceInclusiveName.inclusiveName.replace("#", "").replace("@", "")});
    }

    module.config.push(
        {
            name        : "useInterfacePins",
            displayName : "Pins Used",
            description : 'The pins used by the pinmux section.',
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : options,
        }
        /*,
        {
            name: "cfgMultiEnum2",
            //getDisabledOptions: generateDisabledOptions("cfgMultiEnum2"),
            displayName: "MultiEnum2",
            options: [
                {
                    name: "opt1",
                    displayName: "Option1"
                },
                {
                    name: "opt2",
                    displayName: "Option2"
                },
                {
                    name: "opt3",
                    displayName: "Option3"
                }
            ],
            default: ["opt1", "opt2"]
        },*/
    )
}


function usbPinmuxRequirements(inst)
{
    var peripheralName = "USB";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        if (pt.displayName.includes("EPEN") || pt.displayName.includes("FLT"))
        {

        }
        else
        {
            resources.push(pt);
            signalTypes[pt.name] = interfaceName;
        }
        i++;
    }

    let usb = {
        name          : "usb",
        displayName   : "USB Peripheral",
        interfaceName : "USB",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [usb];
}


function uppPinmuxRequirements(inst)
{
    var peripheralName = "UPP";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    //console.log(useCaseInterfaces);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    //console.log(InterfaceNames);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let upp = {
        name          : "upp",
        displayName   : "UPP Peripheral",
        interfaceName : "UPP",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [upp];
}

function fsitxPinmuxRequirements(inst)
{
    var peripheralName = "FSITX";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let fsitx = {
        name          : "fsitx",
        displayName   : "FSITX Peripheral",
        interfaceName : "FSITX",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [fsitx];
}
function fsirxPinmuxRequirements(inst)
{
    var peripheralName = "FSIRX";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let fsirx = {
        name          : "fsirx",
        displayName   : "FSIRX Peripheral",
        interfaceName : "FSIRX",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [fsirx];
}
function emif1PinmuxRequirements(inst)
{
    var peripheralName = "EMIF1";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
   var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1 ||
        // Special Case
            interfaceName.includes("A20") ||
            interfaceName.includes("A21"))
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let emif1 = {
        name          : "emif1",
        displayName   : "EMIF1 Peripheral",
        interfaceName : "EMIF1",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [emif1];
}
function emif2PinmuxRequirements(inst)
{
    var peripheralName = "EMIF2";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1||
        // No options available
        system.deviceData.interfaces[peripheralName].interfacePins[interfaceName].pinMappings[0].pinMappings.length <= 0)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let emif2 = {
        name          : "emif2",
        displayName   : "EMIF2 Peripheral",
        interfaceName : "EMIF2",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [emif2];
}

function otherPinmuxRequirements(inst)
{
    var peripheralName = "OTHER";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1 ||
            // No options available
            system.deviceData.interfaces[peripheralName].interfacePins[interfaceName].pinMappings[0].pinMappings.length <= 0 ||
            // No EMUs
            // Special Case
            interfaceName.includes("EMU")  ||
            // No AUXCLKIN
            // Special Case
            interfaceName.includes("AUXCLKIN") 
        )
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let other = {
        name          : "other",
        displayName   : "Other Peripheral",
        interfaceName : "OTHER",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [other];
}


function analogPinmuxRequirements(inst)
{
    var peripheralName = "ANALOG";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1 ||
            // No options available
            system.deviceData.interfaces[peripheralName].interfacePins[interfaceName].pinMappings[0].pinMappings.length <= 0 
        )
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let analog = {
        name          : "analog",
        displayName   : "ANALOG Peripheral",
        interfaceName : "ANALOG",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [analog];
}


function dcdcPinmuxRequirements(inst)
{
    var peripheralName = "DC-DC";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let dcdc = {
        name          : "dcdc",
        displayName   : "DC-DC Peripheral",
        interfaceName : "DC-DC",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [dcdc];
}

function linPinmuxRequirements(inst)
{
    var peripheralName = "LIN";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let lin = {
        name          : "lin",
        displayName   : "LIN Peripheral",
        interfaceName : "LIN",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [lin];
}


function spiPinmuxRequirements(inst)
{
    var peripheralName = "SPI";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];
        var legacyInclusiveNames = PinmuxMigrations.interfaceInclusiveRename(interfaceName, peripheralName);

        //console.log(legacyInclusiveNames)

        if(!legacyInclusiveNames.legacyName)
        {
            if (useCaseInterfaces.indexOf(interfaceName) == -1)
            {
                continue;
            }
            let pt = {
                name              : legacyInclusiveNames.inclusiveName.toLowerCase().replace("#", "").replace("@", "") + "Pin",
                displayName       : interfaceName.replace("#", "").replace("@", ""),
                interfaceNames    : [interfaceName]
            };

            resources.push(pt);
            signalTypes[pt.name] = interfaceName;
            i++;
        }
        else
        {
            //console.log(interfaceName)
            //console.log(legacyInclusiveNames.legacyName)
            for(let i = 0; i < legacyInclusiveNames.legacyName.length; i++)
            {
                legacyInclusiveNames.legacyName[i] = legacyInclusiveNames.legacyName[i].toLowerCase().replace("#", "").replace("@", "") + "Pin";
            }

            if (useCaseInterfaces.indexOf(interfaceName) == -1)
            {
                continue;
            }
            let pt = {
                name              : legacyInclusiveNames.inclusiveName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
                legacyNames       : legacyInclusiveNames.legacyName,
                displayName       : legacyInclusiveNames.inclusiveName.replace("#", "").replace("@", ""), /* GUI name */
                interfaceNames    : [interfaceName]    /* pinmux tool name */
            };

            resources.push(pt);
            signalTypes[pt.name] = interfaceName;
            i++;
            //console.log(resources)
        }
    }

    //console.log(resources)

    let spi = {
        name          : "spi",
        displayName   : "SPI Peripheral",
        interfaceName : "SPI",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [spi];
}

function getPeripheralUseCaseNames(peripheralName)
{
    var useCaseOptions = [];
    if (system.deviceData.interfaces[peripheralName] == null)
        return [{name: "ALL"}, {name: "CUSTOM"}];
    var useCases = Object.keys(system.deviceData.interfaces[peripheralName].useCases);

    var containsALL = false;
    for (var useCaseNumber in useCases)
    {
        var useCaseName = useCases[useCaseNumber];
        if(useCaseName == "ALL")
        {
            containsALL = true;
        }
        useCaseOptions.push({name: useCaseName, displayName: PinmuxMigrations.useCaseInclusiveRename(useCaseName, peripheralName)});
    }
    if (!containsALL)
    {
        useCaseOptions.unshift({name: "ALL"});
    }
    useCaseOptions.unshift({name: "CUSTOM"});
    return useCaseOptions;
}

function addPeripheralUseCaseCustom()
{
    
}

function getAdditionalUseCaseNameConfigsNotInDeviceData(periph)
{
    var useCaseNameConfigs = []
    var additionalUseCases = PinmuxAdditionalUseCases.getAdditionalUseCase(periph)
    for (var addUseCase of additionalUseCases)
    {
        var matchingUseCaseName = getPeripheralUseCaseNames(periph).filter(useCaseOption => useCaseOption.name == addUseCase.name);
        if (matchingUseCaseName.length < 1)
        {
            useCaseNameConfigs.push({
                name: addUseCase.name
            })
        }
    }

    return useCaseNameConfigs;
}

function getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName)
{
    var useCaseInterfaces = [];
    //console.log("Finding use cases...");
    //console.log(system.deviceData.interfaces[peripheralName].useCases);



    if (useCaseName == "CUSTOM")
    {
        //console.log("Doing custom use cases...");
        return getCustomPeripheralInterfaces(inst, peripheralName);
    }

    if (system.deviceData.interfaces[peripheralName].useCases[useCaseName] == null)
    {
        //console.log("Use case not found, showing all!");
        var additionalUseCaseInterface = PinmuxAdditionalUseCases.getAdditionalUseCaseInterfaces(peripheralName, useCaseName)
        if (additionalUseCaseInterface)
        {
            return additionalUseCaseInterface
        }
        
        return getPeripheralInterfaces(peripheralName);
    }

    if (useCaseName == "ALL")
    {
        return getPeripheralInterfaces(peripheralName);
    }


    //console.log("Use case found. Showing only relevant interfaces!");
    var numberOfPinsInUseCase = system.deviceData.interfaces[peripheralName].useCases[useCaseName].useCasePin.length;
    
    for (var useCasePinNumber = 0; useCasePinNumber < numberOfPinsInUseCase; useCasePinNumber++)
    {
        if (!system.deviceData.interfaces[peripheralName].useCases[useCaseName].useCasePin[useCasePinNumber].optional)
        {
            useCaseInterfaces.push(system.deviceData.interfaces[peripheralName].useCases[useCaseName].useCasePin[useCasePinNumber].name);
        }
    }
    return useCaseInterfaces;
}

function getCustomPeripheralInterfaces(inst, peripheralName)
{
    return inst.useInterfacePins;
    //console.log(inst.useInterfacePins)
    var interfaces = [];
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    for (var interfaceNumber in InterfaceNames)
    {
        interfaces.push(InterfaceNames[interfaceNumber]);
    }

    return interfaces;
}

function getPeripheralInterfaces(peripheralName)
{
    var interfaces = [];
    //console.log(peripheralName)
    //console.log(system.deviceData.interfaces)
    //console.log(system.deviceData.interfaces[peripheralName])
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    for (var interfaceNumber in InterfaceNames)
    {
        interfaces.push(InterfaceNames[interfaceNumber]);
    }

    return interfaces;
}

function sciPinmuxRequirements(inst)
{
    var peripheralName = "SCI";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);

    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let sci = {
        name          : "sci",
        displayName   : "SCI Peripheral",
        interfaceName : "SCI",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [sci];
}

function sdPinmuxRequirements(inst)
{
    var peripheralName = "SD";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let sd = {
        name          : "sd",
        displayName   : "Sigma-Delta Peripheral",
        interfaceName : "SD",
        resources     : resources,
        signalTypes   : signalTypes
    };


    return [sd];
}


function mcbspPinmuxRequirements(inst)
{
    var peripheralName = "MCBSP";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let mcbsp = {
        name          : "mcbsp",
        displayName   : "MCBSP Peripheral",
        interfaceName : "MCBSP",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [mcbsp];
}

function eqepPinmuxRequirements(inst)
{
    var peripheralName = "EQEP";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let eqep = {
        name          : "eqep",
        displayName   : "EQEP Peripheral",
        interfaceName : "EQEP",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [eqep];
}

function epwm_pinmux(periph){
    return true
}

function hrpwm_pinmux(periph){
    if (["F28002x", "F2838x", "F28003x"].includes(Common.getDeviceName()))
    {
        if (["EPWM1", "EPWM2", "EPWM3", "EPWM4"].includes(periph.name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (["F280013x"].includes(Common.getDeviceName()))
    {
        if (["EPWM1"].includes(periph.name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (["F280015x"].includes(Common.getDeviceName()))
    {
        if (["EPWM1", "EPWM2"].includes(periph.name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (["EPWM1", "EPWM2", "EPWM3", "EPWM4", "EPWM5", "EPWM6", "EPWM7", "EPWM8"].includes(periph.name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

function epwmPinmuxRequirements(inst)
{
    var peripheralName = "EPWM";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];
        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }

        //console.log(interfaceName);

        if(interfaceName.includes("_"))
        {
            let pt = {
                name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
                legacyNames       : [interfaceName.toLowerCase().replace("#", "").replace("@", "").replace("_", "") + "Pin"],
                displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
                interfaceNames    : [interfaceName]    /* pinmux tool name */
            };
    
            resources.push(pt);
            signalTypes[pt.name] = interfaceName;
        }
        else
        {
            let pt = {
                name              : interfaceName.toLowerCase().replace("#", "_").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
                legacyNames       : [interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin"],
                displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
                interfaceNames    : [interfaceName]    /* pinmux tool name */
            };
    
            resources.push(pt);
            signalTypes[pt.name] = interfaceName;
        }

//        let pt = {
//            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
//            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
//            interfaceNames    : [interfaceName]    /* pinmux tool name */
//        };
//
//        resources.push(pt);
//        signalTypes[pt.name] = interfaceName;
        i++;
    }
    var filter = epwm_pinmux
    if (inst.hrpwm_enable)
    {
        filter = hrpwm_pinmux
    }
    //console.log(resources)
    let epwm = {
        name          : "epwm",
        displayName   : "EPWM Peripheral",
        interfaceName : "EPWM",
        resources     : resources,
        signalTypes   : signalTypes,
        filter        : filter
    };
    return [epwm];
}

function i2cPinmuxRequirements(inst)
{
    var peripheralName = "I2C";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }
    let i2c = {
        name          : "i2c",
        displayName   : "I2C Peripheral",
        interfaceName : "I2C",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [i2c];
}


function canPinmuxRequirements(inst)
{
    var peripheralName = "CAN";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
            continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }
    let can = {
        name          : "can",
        displayName   : "CAN Peripheral",
        interfaceName : "CAN",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [can];
}

function outputxbarPinmuxRequirements(inst)
{

    let resources = [];
    var peripheralName = "OUTPUTXBAR";
    var signalTypes = {};
    //var useCaseName = inst.useCase;
    //var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        //if (useCaseInterfaces.indexOf(interfaceName) == -1)
        //{
        //    continue;
        //}
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let outputxbar = {
        name          : "outputxbar",
        displayName   : "OUTPUTXBAR Peripheral",
        interfaceName : "OUTPUTXBAR",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [outputxbar];
}



function clb_outputxbarPinmuxRequirements(inst)
{

    let resources = [];
    var peripheralName = "CLB_OUTPUTXBAR";
    var signalTypes = {};
    //var useCaseName = inst.useCase;
    //var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        //if (useCaseInterfaces.indexOf(interfaceName) == -1)
        //{
        //    continue;
        //}
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let clb_outputxbar = {
        name          : "clb_outputxbar",
        displayName   : "CLB OUTPUTXBAR Peripheral",
        interfaceName : "CLB_OUTPUTXBAR",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [clb_outputxbar];
}


function inputxbarPinmuxRequirements(inst)
{

    let resources = [];
    var INPUTXBARInterfaceNames = Object.keys(system.deviceData.interfaces.INPUTXBAR.interfacePins);
    var i = 1;
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);

    for (var useCaseNumber in INPUTXBARInterfaceNames)
    {
        var interfaceName = INPUTXBARInterfaceNames[interfaceNumber];
        let ix1 = {
            name              : "inputxbar" + i + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : "INPUTXBAR" + i, /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(ix1);

        signalTypes[ix1.name] = interfaceName;
        i++;
    }


    let inputxbar = {
        name          : "inputxbar",
        displayName   : "INPUTXBAR Peripheral",
        interfaceName : "INPUTXBAR",
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [inputxbar];
}

function gpioWithPeripheralPinmuxRequirements(inst)
{
    let resources = [];

    var GPIOInterfaceName = "GPIO#";
    
    let gpio = {
        name          : "gpioPin",
        displayName   : "GPIO Peripheral",
        interfaceName : "GPIO", 
        signalTypes   : {
            "gpioPin" : GPIOInterfaceName
        }       
    };

    return [gpio];
}

function gpioPinmuxRequirements(inst)
{

    let resources = [];

    var GPIOInterfaceName = "GPIO#";
    
    let gpio = {
        name          : "gpioPin",
        displayName   : "GPIO",
        interfaceName : "GPIO",
        signalTypes   : [GPIOInterfaceName]
        
    };

    return [gpio];
}

function aioPinmuxRequirements(inst)
{

    let resources = [];


    let aio = {
        name          : "aioPin",
        displayName   : "AIO Peripheral",
        interfaceName : "AIO",        
    };

    return [aio];
}

function pmbusPinmuxRequirements(inst)
{
    var peripheralName = "PMBUS";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let pmbus = {
        name          : "pmbus",
        displayName   : "PMBUS Peripheral",
        interfaceName : "PMBUS",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [pmbus];
}


function cmi2cPinmuxRequirements(inst)
{
    var peripheralName = "CM-I2C";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let cmi2c = {
        name          : "cmi2c",
        displayName   : "CM-I2C Peripheral",
        interfaceName : "CM-I2C",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [cmi2c];
}


function mcanPinmuxRequirements(inst)
{
    var peripheralName = "MCAN";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let mcan = {
        name          : "mcan",
        displayName   : "MCAN Peripheral",
        interfaceName : "MCAN",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [mcan];
}

function uartPinmuxRequirements(inst)
{
    var peripheralName = "UART";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let uart = {
        name          : "uart",
        displayName   : "UART Peripheral",
        interfaceName : "UART",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [uart];
}

function ssiPinmuxRequirements(inst)
{
    var peripheralName = "SSI";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let ssi = {
        name          : "ssi",
        displayName   : "SSI Peripheral",
        interfaceName : "SSI",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [ssi];
}


function ecatPinmuxRequirements(inst)
{
    var peripheralName = "ECAT";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1)
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let ecat = {
        name          : "ecat",
        displayName   : "ECAT Peripheral",
        interfaceName : "ECAT",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [ecat];
}

function ethernetPinmuxRequirements(inst)
{
    var peripheralName = "ETHERNET";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1 ||
            // No options available
            system.deviceData.interfaces[peripheralName].interfacePins[interfaceName].pinMappings[0].pinMappings.length <= 0    
        )
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let ethernet = {
        name          : "ethernet",
        displayName   : "ETHERNET Peripheral",
        interfaceName : "ETHERNET",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [ethernet];
}


function hicPinmuxRequirements(inst)
{
    var peripheralName = "HIC";
    let resources = [];
    var signalTypes = {};
    var useCaseName = inst.useCase;
    var useCaseInterfaces = getPeripheralUseCaseInterfaces(inst, peripheralName, useCaseName);
    var InterfaceNames = Object.keys(system.deviceData.interfaces[peripheralName].interfacePins);
    var i = 1;
    for (var interfaceNumber in InterfaceNames)
    {
        var interfaceName = InterfaceNames[interfaceNumber];

        if (useCaseInterfaces.indexOf(interfaceName) == -1 ||
            // No options available
            system.deviceData.interfaces[peripheralName].interfacePins[interfaceName].pinMappings[0].pinMappings.length <= 0    
        )
        {
           continue;
        }
        let pt = {
            name              : interfaceName.toLowerCase().replace("#", "").replace("@", "") + "Pin",  /* config script name  THE ACTUAL NAME USED to find the pin*/
            displayName       : interfaceName.replace("#", "").replace("@", ""), /* GUI name */
            interfaceNames    : [interfaceName]    /* pinmux tool name */
        };

        resources.push(pt);

        signalTypes[pt.name] = interfaceName;
        i++;
    }

    let hic = {
        name          : "hic",
        displayName   : "HIC Peripheral",
        interfaceName : "HIC",
        
        resources     : resources,
        signalTypes   : signalTypes
    };

    return [hic];
}

function getGPIOFromDevicePinName(devicePinName)
{
    var gpioNames = []
    var isAgpioPin = false
    var gpioName = devicePinName;
    if (!gpioName.startsWith("GPIO"))
    { 
        isAgpioPin = true 
    }
    gpioName = gpioName.substring(gpioName.indexOf("GPIO"))
    if ((gpioName.match(/GPIO/g) || []).length > 1)
    { 
        //
        // Double bonded
        //
        var gpiosOnThisPin = gpioName.split("GPIO");
        gpiosOnThisPin.splice(0, 1)
        for (var gpioOnThisPin of gpiosOnThisPin)
        {
            var gpioNumberOnThisPin = Common.gpioNameToNumber(gpioOnThisPin);
            gpioNames.push("GPIO" + gpioNumberOnThisPin)
        }
        return gpioNames
        
    }
    gpioName = gpioName.substring(4); // determine which GPIO
    var gpioNumber = Common.gpioNameToNumber(gpioName);
    gpioNames.push("GPIO" + gpioNumber)
    return gpioNames
}

exports = {
    NO_DEVICE_PIN_FOUND : NO_DEVICE_PIN_FOUND,
    getADCPinsUsed : getADCPinsUsed,
    getCMPSSPinsUsed : getCMPSSPinsUsed,
    getCMPSSLitePinsUsed : getCMPSSLitePinsUsed,
    getDeviceDACName : getDeviceDACName,
    findAllAnalogPin: findAllAnalogPin,
    findAnalogPin : findAnalogPin,
    calculateADCPinInfo : calculateADCPinInfo,
    getDeviceADCName : getDeviceADCName,
    getDevicePinInfoDescription : getDevicePinInfoDescription,
    getPeripheralUseCaseInterfaces: getPeripheralUseCaseInterfaces,
    useCaseChanged : useCaseChanged,
    addCustomPinmuxEnumToConfig : addCustomPinmuxEnumToConfig,
    getPeripheralUseCaseNames : getPeripheralUseCaseNames,
    spiPinmuxRequirements : spiPinmuxRequirements,
    sciPinmuxRequirements : sciPinmuxRequirements,
    gpioPinmuxRequirements : gpioPinmuxRequirements,
    i2cPinmuxRequirements : i2cPinmuxRequirements,
    inputxbarPinmuxRequirements: inputxbarPinmuxRequirements,
    outputxbarPinmuxRequirements : outputxbarPinmuxRequirements,
    clb_outputxbarPinmuxRequirements : clb_outputxbarPinmuxRequirements,
    aioPinmuxRequirements : aioPinmuxRequirements,
    canPinmuxRequirements : canPinmuxRequirements,
    epwmPinmuxRequirements : epwmPinmuxRequirements,
    eqepPinmuxRequirements : eqepPinmuxRequirements,
    mcbspPinmuxRequirements : mcbspPinmuxRequirements,
    sdPinmuxRequirements : sdPinmuxRequirements,
    uppPinmuxRequirements : uppPinmuxRequirements,
    usbPinmuxRequirements : usbPinmuxRequirements,
    fsitxPinmuxRequirements : fsitxPinmuxRequirements,
    fsirxPinmuxRequirements : fsirxPinmuxRequirements,
    otherPinmuxRequirements : otherPinmuxRequirements,
    dcdcPinmuxRequirements : dcdcPinmuxRequirements,
    emif1PinmuxRequirements : emif1PinmuxRequirements,
    emif2PinmuxRequirements : emif2PinmuxRequirements,
    linPinmuxRequirements : linPinmuxRequirements,
    pmbusPinmuxRequirements : pmbusPinmuxRequirements,
    cmi2cPinmuxRequirements : cmi2cPinmuxRequirements,
    mcanPinmuxRequirements : mcanPinmuxRequirements,
    uartPinmuxRequirements : uartPinmuxRequirements,
    ssiPinmuxRequirements : ssiPinmuxRequirements,
    ecatPinmuxRequirements : ecatPinmuxRequirements,
    ethernetPinmuxRequirements : ethernetPinmuxRequirements,
    hicPinmuxRequirements : hicPinmuxRequirements,
    gpioWithPeripheralPinmuxRequirements : gpioWithPeripheralPinmuxRequirements,
    analogPinmuxRequirements : analogPinmuxRequirements,
    getGpioQualificationModInstDefinitions : getGpioQualificationModInstDefinitions,
    addPinMuxQualGroupToConfig : addPinMuxQualGroupToConfig,
    interfaceNameToQualModeName : interfaceNameToQualModeName,
    getAdditionalUseCaseNameConfigsNotInDeviceData : getAdditionalUseCaseNameConfigsNotInDeviceData,
    getGPIOFromDevicePinName : getGPIOFromDevicePinName
};