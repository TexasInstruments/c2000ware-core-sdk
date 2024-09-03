let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

let Common;
if (transferCommon.isC2000())
{
    Common = system.getScript("/driverlib/Common.js");
}

/* Global variables */
var tx_frame_structure = "END"
var rx_frame_structure = "END"



function onChangeOperationMode(inst, ui){
    /*JSON FRAME SETTINGS*/
    ui["exportMods"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "JSON")
    ui["exportCustomLog"].hidden = !(inst["mode"].includes("data") && (inst["packageMode"] == "JSON" || inst["packageMode"] == "START/END"))
    ui["exportCustomLogTimestamp"].hidden = !(inst["mode"].includes("data") && (inst["packageMode"] == "JSON" || inst["packageMode"] == "START/END"))
    ui["maxExportLength"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "JSON")
    ui["exportRXLength"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "JSON")
    ui["exportBuffer"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "JSON")
    /*CUSTOM FRAME SETTINGS*/
    ui["maxTXFrameLength"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    //ui["txkeys"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    //ui["txLengthBytes"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    //ui["txLengthAvailable"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    //ui["txFrameStructure"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    // ui["txChecksumEnable"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    ui["txEndByte"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    ui["txStartByte"].hidden = !(inst["mode"].includes("data") && inst["packageMode"] == "START/END")
    ui["maxRXFrameLength"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    //ui["rxkeys"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    //ui["rxLengthBytes"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    //ui["rxLengthAvailable"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    //ui["rxFrameStructure"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    ui["rxStartByteEnable"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    ui["rxStartByte"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END" && inst["rxStartByteEnable"] == true)
    ui["rxChecksumEnable"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
    ui["rxEndByte"].hidden = !(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END")
}

let config = [
    {
        name: "mode",
        displayName: "Mode of Operation",
        options: [
            { name: "data", displayName: "Data Exporter"},
            { name: "dataBidirectional", displayName: "Data Export/Import - Bidirectional"},
        ],
        getDisabledOptions: (inst) => {
            if (!transferCommon.isC2000()){
                return [{ name: "dataBidirectional", reason: "Only supported in C2000 devices"}];
            }
            return [];
        },
        default: "data",
        onChange: onChangeOperationMode
    },
    {
        name: "comsLink",
        displayName: "Communication Link",
        options: [
            { name: "uart", displayName: "UART" },
            { name: "sci", displayName: "SCI" },
            { name: "usb", displayName: "USB" },
            { name: "fsi", displayName: "FSI" },
			{ name: "spi", displayName: "SPI" }
            // TODO: Implement these communication peripherals
            //{ name: "mcan", displayName: "MCAN" },
			//{ name: "i2c", displayName: "I2C" },
			//{ name: "lin", displayName: "LIN" },
			//{ name: "can", displayName: "CAN" },
			//{ name: "ecat", displayName: "ECAT" },

        ],
        getDisabledOptions: (inst) => {
		// need additional logic to disable or enable options from above list
            if (transferCommon.isC2000()){
                return transferCommon.getCommPeripheralsOnDevice()
            }
            else {
                return [
                    { name: "sci", reason: "Not supported on MCU+" },
                    { name: "fsi", reason: "Not supported on MCU+" }
                ]
            }
        },
		// add logic to default to first available comm peripheral here
        default: transferCommon.isC28x()?"sci":"uart"
    },
    {
        name: "packageMode",
        displayName: "Package Mode",
        default: "JSON",
        options: [
            { name: "JSON" },
            { name: "START/END" },
            { name: "MSGPACK" }
        ],
        getDisabledOptions: (inst) => {
            return [
                { name: "MSGPACK", reason: "Not yet implemented" },
            ]
        },
        onChange: onChangeOperationMode,
    },
    {
        name: "maxExportLength",
        displayName: "Max Export Length",
        default: 50
    },
    {
        name: "exportRXLength",
        displayName: "Export RX Length",
        default: 16,
        readOnly: true,
        hidden: true
    },
    {
        name: "maxTXFrameLength",
        displayName: "Max Transmit Frame Length",
        description: "Max Transmit Frame Length for all message type definitions.",
        default: 50,
        readOnly: false,
        hidden: true,
    },
    {
        name: "maxRXFrameLength",
        displayName: "Max Receive Frame Length",
        description: "Max Receive Frame Length for all message type definitions",
        default: 16,
        readOnly: true,
        hidden: true
    },
    {
        name: "GROUP_EXPORT_DIAGNOSTICS",
        displayName: "Export Diagnostics Configuration",
        config: [
            {
                name: "exportMods",
                displayName: "Export Device Diagnostic Modules",
                default: false,
                hidden: transferCommon.isC29x()
            },
        ]
    },
    {
        name: "GROUP_EXPORT_LOGS",
        displayName: "Export Custom Logs Configuration",
        config: [
            {
                name: "exportCustomLog",
                legacyNames: ["exportLog"],
                displayName: "Export Log Support",
                default: false,
                hidden: !transferCommon.isC2000()
            },
            {
                name: "exportCustomLogTimestamp",
                displayName: "Export Log Timestamp",
                default: false,
                hidden: !transferCommon.isC2000()
            },
        ]
    },            
    {
        name: "exportBuffer",
        legacyNames: ["exportLogBuffer"],
        displayName: "Buffer Logs",
        default: false,
        hidden: !transferCommon.isC2000()
    },
    {
        name: "GROUP_CUSTOM_TRANSMIT",
        displayName: "Transmit Frame Definition",
        config: [
            {
                name: "txFrameStructure",
                displayName: "Frame Structure",
                hidden: true,
                readOnly: true,
                default: "END",
                getValue: (inst) => {
                    /*let tempStructure = "END"
                    let currentKeyNum = 0
                    if(inst.txChecksumEnable){
                        tempStructure = "CHECKSUM|" + tempStructure
                    }
                    if(system.modules["/utilities/transfer/logger/keys.js"] != undefined){
                        currentKeyNum = system.modules["/utilities/transfer/logger/keys.js"].$instances.length
                    }
                    for(let i = 1; i < currentKeyNum+1; i++){
                        tempStructure = "KEY" + str(currentKeyNum) + "|VALUE"
                    }
                    }*/
                    return "END"
                }
        
            },
            {
                name: "txStartByte",
                displayName: "Start Byte",
                displayFormat: "hex",
                default: 0x0A,
                hidden: true,
            },
            {
                name: "txChecksumEnable",
                displayName: "Checksum Byte Enable",
                description: "Whether or not to include automatically computed checksum byte in message frames. If enabled, the checksum byte will be sent before the stop byte",
                default: false,
                hidden: true,
                onChange: (inst, ui) => {
                    if(inst.txChecksumEnable){
                        if(tx_frame_structure != "END"){
                            let splitStr = tx_frame_structure.split('|')
                            tx_frame_structure = splitStr.splice(splitStr.length-1, 0, "CHECKSUM").join('|')
                        }
                        else{
                            tx_frame_structure = "CHECKSUM|END"
                        }
                    }
                    else{
                        let splitStr = tx_frame_structure.split('|')
                        tx_frame_structure = splitStr.splice(splitStr.length-1, 1).join('|')
                    }
                }
            },
            {
                name: "txEndByte",
                displayName: "End Byte",
                description: "By default, end byte will be a newline character used to seperate message frames.",
                displayFormat: "hex",
                default: 0x0A,
                hidden: true
            },

            {
                name: "txkeys",
                displayName: "TX KEYS DEBUG",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    return 0;
                }
        
            },
            {
                name: "txLengthBytes",  //length amount refers to key + values in bytes
                displayName: "TX Length Bytes",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    //get max length based on selections
                    let maxlength1L = 0;
                    let maxlength2L = 0;
                    let maxlength3L = 0;
                    let start = 0;
                    let checksum = 0;
                    let key = 1;  //add calculation later?
                    let end = 1; //always atleast 1
                    if(inst.txChecksumEnable){
                        checksum = 1;
                    }
                    maxlength1L = start + 1 + key + checksum + end + 255; //260
                    maxlength2L = start + 2 + key + checksum + end + 65535; //65541
                    maxlength3L = start + 3 + key + checksum + end + 16777215;  
                    if(inst.maxTXFrameLength  <= maxlength1L){
                        return 1;
                    }
                    else if(inst.maxTXFrameLength <= maxlength2L){
                        return 2;
                    }
                    else if(inst.maxTXFrameLength <= maxlength3L){
                        return 3;
                    }
                    else{
                        return 0; //max length inputted is too big
                    }
                }
            },
            {
                name: "txKeyBytes",
                displayName: "TX Length Bytes",
                default: 0,
                hidden: true,

            },
            {
                name: "txLengthAvailable",  //Length they could actually use based on selection
                displayName: "TX Length Available",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    let start = 0;
                    let checksum = 0;
                    if(inst.txChecksumEnable){
                        checksum = 1;
                    }
                    let key = 1;  //add calculation later?
                    let end = 1; //always atleast 1
                    return inst.maxTXFrameLength - start - checksum - key - end - inst.txLengthBytes;
                }
        
            },
        ]

    },
    {
        name: "GROUP_CUSTOM_RECEIVE",
        displayName: "Receive Frame Definition",
        config: [
            {
                name: "rxFrameStructure",
                displayName: "Frame Structure",
                hidden: true,
                readOnly: true,
                default: "|END|",
                getValue: (inst) => {
                    return rx_frame_structure
                }
        
            },
            {
                name: "rxStartByteEnable",
                displayName: "Configure Message Start Byte",
                description: "By default, no start byte will be sent.",
                default: false,
                hidden: true,
                onChange: (inst, ui) =>{
                    if(inst.rxStartByteEnable){
                        ui.rxStartByte.hidden = false
                        rx_frame_structure = "START|" + rx_frame_structure
                    }
                    else{
                        ui.rxStartByte.hidden = true
                    }
                },
            },
            {
                name: "rxStartByte",
                displayName: "Start Byte (in Hexadecimal)",
                default: "00",
                hidden: true,
            },
            {
                name: "rxChecksumEnable",
                displayName: "Checksum Byte Enable",
                description: "Whether or not to include automatically computed checksum byte in message frames. If enabled, the checksum byte will be sent before the stop byte",
                default: false,
                hidden: true,
                onChange: (inst, ui) => {
                    let splitStr = rx_frame_structure.split('|')
                    let attributes = splitStr.length
                    rx_frame_structure = splitStr.splice(1, 0, "CHECKSUM").join('|')
                }
            },
            {
                name: "rxEndByte",
                displayName: "End Byte (in Hexadecimal)",
                description: "By default, end byte will be a newline character used to seperate message frames.",
                default: "0A",
                hidden: true
            },
            {
                name: "rxkeys",
                displayName: "RX KEYS DEBUG",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    return 0;
                },
      
            },
            {
                name: "rxLengthBytes",
                displayName: "RX Length Bytes",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    //get max length based on selections
                    let maxlength1L = 0;
                    let maxlength2L = 0;
                    let maxlength3L = 0;
                    let start = 0;
                    let checksum = 0;
                    let key = 1;  //add calculation later?
                    let end = 1; //always atleast 1
                    if(inst.rxStartByteEnable){
                        start = 1;
                    }
                    if(inst.rxChecksumEnable){
                        checksum = 1;
                    }
                    maxlength1L = start + 1 + key + checksum + end + 255; //260
                    maxlength2L = start + 2 + key + checksum + end + 65535; //65541
                    maxlength3L = start + 3 + key + checksum + end + 16777215;  
                    if(inst.maxRXFrameLength  <= maxlength1L){
                        return 1;
                    }
                    else if(inst.maxRXFrameLength <= maxlength2L){
                        return 2;
                    }
                    else if(inst.maxRXFrameLength <= maxlength3L){
                        return 3;
                    }
                    else{
                        return 0; //max length inputted is too big
                    }                    
                }
        
            },
            {
                name: "rxLengthAvailable",
                displayName: "RX Length Available",
                default: 0,
                hidden: true,
                getValue: (inst) => {
                    let start = 0;
                    let checksum = 0;
                    if(inst.rxStartByteEnable){
                        start = 1;
                    }
                    if(inst.rxChecksumEnable){
                        checksum = 1;
                    }
                    let key = 1;  //add calculation later?
                    let end = 1; //always atleast 1
                    return inst.maxRXFrameLength - start - checksum - key - end - inst.txLengthBytes;
                }
            },
        ]
    }

];

function moduleInstances(inst)
{
    var ownedInstances = []

    if(inst["mode"].includes("data") && inst["packageMode"] == "START/END"){
        if(inst.exportCustomLog){
            ownedInstances.push({
                name: "txKeyValuePairs",
                displayName: " Key Types",
                moduleName: transferCommon.getTransferPath() + "logger/keys.js",
                group: "GROUP_CUSTOM_TRANSMIT",
                useArray: true,
                minInstanceCount: 1,
                collapsed: false,
                fixedRequiredArgs: [{
                    $name: "cLog",
                    lengthToggle: "Variable Message Length",
                    valType: "uint8_t",

                }],
                args: {
                    group: "txKeyValuePairs",
                }
            })
        }else{
            ownedInstances.push({
                name: "txKeyValuePairs",
                displayName: " Key Types",
                moduleName: transferCommon.getTransferPath() + "logger/keys.js",
                group: "GROUP_CUSTOM_TRANSMIT",
                useArray: true,
                minInstanceCount: 0,
                collapsed: false,
                args: {
                    group: "txKeyValuePairs",
                }
            })
        }

    }

    if(inst["mode"].includes("Bidirectional") && inst["packageMode"] == "START/END"){
        ownedInstances.push({
            name: "rxKeyValuePairs",
            displayName: " Key Types",
            moduleName: transferCommon.getTransferPath() + "logger/keys.js",
            group: "GROUP_CUSTOM_RECEIVE",
            useArray: true,
            defaultInstanceCount: 0,
            collapsed: false,
            requiredArgs: {
                group: "rxKeyValuePairs"
            }
        })
    }


    
   /* if(inst.packageMode == "START/END")
    {
        ownedInstances.push({
            name: "packageTXMsgTypes",
            displayName: "Transmit Message Structure Definitions",
            moduleName: transferCommon.getTransferPath() + "logger/packagedatatype.js",
            useArray: true,
            collapsed: true,
        })      
    }
    if(inst.packageMode == "START/END" && (inst["mode"].includes("Bidirectional"))){
        ownedInstances.push({            
            name: "packageRXMsgTypes",
            displayName: "Receive Message Structure Definitions",
            moduleName: transferCommon.getTransferPath() + "logger/packagedatatype.js",
            useArray: true,
            collapsed: true
        })
    }*/
    if (inst.comsLink == "uart"){
        if (!transferCommon.isC2000())
        {
            var uartModInst = {
                name: "comsLinkModule",      
                displayName: "UART Transfer Communication Link",
                moduleName: "/drivers/uart/uart", // add Common function to check for drivers / driverlib ?
                collapsed: true,
                args: {
                    $name : inst.$name + "_UART",
                },
                requiredArgs: {
                    dataLength: "8",
                    stopBits: "1",
                    parityType: 'NONE',
                    readReturnMode: "FULL",
                    readMode: "BLOCKING",
                    writeMode: "BLOCKING",
                }
            }
            ownedInstances = ownedInstances.concat([uartModInst]);
        }
        else
        {
			if(transferCommon.isC28x()){
				var uartModInst = {
            	    name: "comsLinkModule",      
            	    displayName: "UART Transfer Communication Link",
            	    moduleName: "/driverlib/uart.js",
            	    collapsed: true,
            	    args: {
            	        $name : inst.$name + "_UART",
            	    },
            	    requiredArgs: {
            	        baud: 115200,
            	        wlen: "UART_CONFIG_WLEN_8",
            	        stp2: 'UART_CONFIG_STOP_ONE',
						fen: true,
						loopback: false,
						useCase: "ALL"
            	    }
            	}
			}else{
				var uartModInst = {
            	    name: "comsLinkModule",      
            	    displayName: "UART Transfer Communication Link",
            	    moduleName: "/driverlib/uart.js",
            	    collapsed: true,
            	    args: {
            	        $name : inst.$name + "_UART",
            	    },
            	    requiredArgs: {
            	        baudSelect: "115200",
            	        wlen: "UART_CONFIG_WLEN_8",
            	        stp2: 'UART_CONFIG_STOP_ONE',
						fen: true,
						loopback: false,
						useCase: "ALL"
            	    }
            	}
			}
            ownedInstances = ownedInstances.concat([uartModInst]);
        }
    }
	if (inst.comsLink == "spi"){
		if(transferCommon.isC2000()){
			var spiModInst = {
        	    name: "comsLinkModule",      
        	    displayName: "SPI Transfer Communication Link",
        	    moduleName: "/driverlib/spi.js",
        	    collapsed: true,
        	    args: {
        	        $name : inst.$name + "_SPI",
                    bitRate: 1000000,
        	    },
        	    requiredArgs: {
					dataWidth: "8",
					useInterrupts: true,
                    enabledFIFOInterrupts: ["SPI_INT_RXFF"],
                    registerInterrupts: true,
					useFifo: true,
					mode: "SPI_MODE_CONTROLLER",
					useCase: "ALL",
                    spiRXInt: {
                        enableInterrupt: true,
                    }
        	    }
        	}
		}
        ownedInstances = ownedInstances.concat([spiModInst]);
    }
    if (inst.comsLink == "sci")
    {
        var sciModInst = {
            name: "comsLinkModule",      
            displayName: "SCI Transfer Communication Link",
            moduleName: "/driverlib/sci.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_SCI",
            },
            requiredArgs: {
                wordLenght: '8',
                stop: 'ONE',
                parity: 'SCI_CONFIG_PAR_NONE',
                useFifo: true,
                loopback: false,
                useCase: "ALL"
            }
        }

        if (inst.mode.includes("Bidirectional"))
        {
            sciModInst.requiredArgs = {
                ...sciModInst.requiredArgs, 
                ...{
                    useInterrupts: true,
                    registerInterrupts: true,
                    rxFifo: "SCI_FIFO_RX" + inst.exportRXLength,
                    txFifo: "SCI_FIFO_TX0",
                    enabledFIFOInterrupts: ["SCI_INT_RXFF"],
                    sciRXInt : {
                        enableInterrupt: true
                    },
                    sciTXInt : {
                        enableInterrupt: false
                    }
                }
            }
        }
        else
        {
            sciModInst.requiredArgs = {
                ...sciModInst.requiredArgs, 
                ...{
                    useInterrupts: false,
                    // Removed in latest version of SysConfig
                    // registerInterrupts: false,
                }
            }
        }

        ownedInstances = ownedInstances.concat([sciModInst]);
    }
    if (inst.comsLink == "usb")
    {
        if (transferCommon.isC2000()) {
            var usbModInst = {
                name: "comsLinkModule",      
                displayName: "USB Transfer Communication Link",
                moduleName: "/driverlib/usb.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_USB",
                    usbLib: {
                        $name: inst.$name + "_USB_LIB"
                    }
                },
                requiredArgs: {
                    useCase: "ALL",
                    registerInterrupts: true,
                    usbLib: {
                        usb_mode: "Device",
                        deviceClasses: "CDC"
                    },
                    USBInt: {
                        enableInterrupt: true
                    }
                }
            }

            ownedInstances = ownedInstances.concat([usbModInst]);
        } else {
            var usbModInst = {
                name: "comsLinkModule",      
                displayName: "USB Transfer Communication Link",
                moduleName: "/usb/tinyusb/tinyusb",
                collapsed: true,
                args: {
                    $name : inst.$name + "_USB",
                },
            }

            ownedInstances = ownedInstances.concat([usbModInst]);
        }
    }
    if (inst.comsLink == "fsi" && transferCommon.isC2000())
    {
        ownedInstances = ownedInstances.concat([{
            name: "comsLinkModule",      
            displayName: "FSI TX Communication",
            moduleName: "/driverlib/fsitx.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_FSITX",
                clkPres: 8
            },
            requiredArgs: {
                startOfTransmissionMode: "FSI_TX_START_FRAME_CTRL",
                frameType: "FSI_FRAME_TYPE_NWORD_DATA",
                softwareFrameSize: inst.exportRXLength.toString(),
                enableInterrupt: false,  
                userCRC: false,
                eccComputeWidth: "FSI_32BIT_ECC_COMPUTE",                
                pingTimeout: false,
                enableInterrupt        : true,
                useInterrupts          : ["FSI_INT1"],
                enabledINT1Interrupts  : ["FSI_TX_EVT_FRAME_DONE"],
                registerInterruptLine1 : true,
                fsiTxInt1: {
                    enableInterrupt : true
                }
            }
        }]);
        if (inst.mode.includes("Bidirectional"))
        {
            let fsiLinkModInstAlt = {
                name: "comsLinkModuleAlt",      
                displayName: "FSI RX Communication",
                moduleName: "/driverlib/fsirx.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSIRX",
                },
                requiredArgs: {
                    softwareFrameSize: inst.exportRXLength.toString(),
                    enableLoopback: false,
                    enableTagMatching: false,
                    enableInterrupt: true,
                    useInterrupts: ["FSI_INT1"],
                    enabledINT1Interrupts: ["FSI_RX_EVT_FRAME_DONE"],
                    registerInterruptLine1: true,
                    pingTimeout: false,
                    fsiRxInt1 : {
                        enableInterrupt: true
                    }
                },
            }
            ownedInstances = ownedInstances.concat([fsiLinkModInstAlt]);
        }
    }
    if (inst.exportBuffer)
    {
        ownedInstances = ownedInstances.concat([{
            name: "exportLogBufferModule",      
            displayName: "Log Buffer",
            moduleName: transferCommon.getTransferPath() + "transferringbuff.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_logRingBuff",
            },
            requiredArgs: {
                elemPerBuffEntry: inst.exportRXLength
            },
        }]);
    }
    if (inst.exportCustomLog && inst.exportCustomLogTimestamp){
        if (transferCommon.isC2000()) {
            ownedInstances = ownedInstances.concat([{
                name: "exportLogTimestampModule",      
                displayName: "Log Timestamp",
                moduleName: "/driverlib/cputimer.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_logTimestamp",
                },
                requiredArgs: {
                    emulationMode: "CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT",
                    timerPrescaler: Common.SYSCLK_getMaxMHz(),
                    timerPeriod: 4294967295,
                    enableInterrupt: false,
                    registerInterrupts: false,
                    startTimer: false
                },
                group: "GROUP_EXPORT_LOGS"
            }]);
        }
    }

    return ownedInstances
}

function modules(inst)
{
    var staticOwnedInstances = []
    if (inst.exportMods)
    {
        staticOwnedInstances = staticOwnedInstances.concat([{
            name: "exportMods",
            moduleName: transferCommon.getTransferPath() + "export/export_mods.js",
        }]);
    }

    if (inst.exportCustomLog)
    {
        staticOwnedInstances = staticOwnedInstances.concat([{
            name: "exportCustomLog",
            moduleName: transferCommon.getTransferPath() + "export/export_log.js",
        }]);
    }

    if (inst.exportBuffer)
    {
        staticOwnedInstances = staticOwnedInstances.concat([{
            name: "exportBuffer",
            moduleName: transferCommon.getTransferPath() + "export/export_buffer.js",
        }]);
    }

    // if (inst.packageMode == "JSON")
    // {
    //     staticOwnedInstances = staticOwnedInstances.concat([{
    //         name: "exportJson",
    //         moduleName: transferCommon.getTransferPath() + "export/export_json.js",
    //     }]);
    // }

    if (inst.packageMode == "JSON" || inst.packageMode == "START/END")
    {
        staticOwnedInstances = staticOwnedInstances.concat([{
            name: "exportPackage",
            moduleName: transferCommon.getTransferPath() + "export/export_package.js",
        }]);
    }

    return staticOwnedInstances
}

function onValidate(inst, validation){
    if ((inst["comsLink"] == "usb") && inst.exportBuffer && transferCommon.isC2000())
    {
        validation.logWarning(
            "C2000 USB software stack already has an internal buffer, using a second buffer within the Data Transfer module is not necessary", 
            inst, "exportBuffer");
    }
    /*if(inst.txLength > inst.maxTXFrameLength){
        validation.logError(
            "Too many keys added, max TX frame length exceeded",
            inst, "txKeyValuePairs");
    }
    if(inst.rxLength > inst.maxRXFrameLength){
        validation.logError(
            "Too many keys added, max RX frame length exceeded",
            inst, "rxKeyValuePairs");
    }*/
}

var exportModule = {
    displayName: "Data Transfer (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myEXPORT",
    description: "Data Transfer Module",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
		[transferCommon.getTransferPath() + "export/export.c.xdt"] : "",
		[transferCommon.getTransferPath() + "export/export.h.xdt"] : "",
        [transferCommon.getTransferPath() + "transfer.opt.xdt"]: "",
        [transferCommon.getTransferPath() + "transfer_utils.h.xdt"]: "",
        [transferCommon.getTransferPath() + "transfer_utils.c.xdt"]: ""
	},
    validate: onValidate
};




exports = exportModule;
