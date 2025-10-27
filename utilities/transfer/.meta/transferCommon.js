function getProductName() {
    var currnetSDKProduct = system.getProducts()[0].name;
    return (currnetSDKProduct);
}

function getSDKPath() {
    var currnetSDKProductPath = system.getProducts()[0].path
    var sdkPath = system.utils.path.join(currnetSDKProductPath + "../../../")
    sdkPath = sdkPath.replace(new RegExp('\\' + system.utils.path.sep, 'g'), '/')
    if (system.getProducts()[0].name != "C2000WARE" && isC2000() && !isC29x()) {
        sdkPath = sdkPath + "c2000ware/"
    }

    return sdkPath
}
function getDeviceName() {
    var deviceName = system.deviceData.device;
    return deviceName
}

function isC2000() {
    if (getProductName().includes("C2000") || getProductName().includes("F29") || getProductName().includes("MCSDK")) {
        return true;
    }
    return false;
}

function isC29x() {
    if (getProductName().includes("F29")) {
        return true;
    }
    return false;
}

function isC28x() {
    if (getProductName().includes("C2000")) {
        return true;
    }
    return false;
}

function isAMx() {
    if (getProductName().includes("AM")) {
        return true;
    }
    return false;
}

function getTransferPath() {
    if (system.getProducts()[0].name.includes("C2000")) {
        return "/utilities/transfer/"
    }
    else {
        return "/transfer/"
    }
}

function getDeviceTypeName() {
    if (isC2000() && !isC29x()) {
        return "c2000"
    } else if (isC29x()) {
        return "c29"
    }
    else {
        return "am243x"
    }
}

function getAbsoluteTransferPath() {
    return getSDKPath() + getTransferSourcePath().replace("../", "");
}

function getTransferSourcePath() {
    if (system.getProducts()[0].name.includes("C2000")) {
        return "../utilities/transfer/"
    }
    if (system.getProducts()[0].name.includes("F29")) {
        return "../source/../tools/transfer/"
    }
    else {
        return "../source/transfer/"
    }
}

function getCommPeripheralsOnDevice() {
    // Filter out what is able to be an option for export.js <TO DO>
    if (["F28002x", "F28003x", "F28004x"].includes(getDeviceName())) {
        return [
            { name: "usb", reason: "Not supported on this device" },
            { name: "uart", reason: "Not supported on this device" }
        ]
    }
    if (["F280013x", "F280015x"].includes(getDeviceName())) {
        return [
            { name: "usb", reason: "Not supported on this device" },
            { name: "uart", reason: "Not supported on this device" },
            { name: "fsi", reason: "Not supported on this device" }

        ]
    }
    if(["F2837xD", "F2837xS", "F2807x"].includes(getDeviceName())){
        return [
            { name: "uart", reason: "Not supported on this device" },
            { name: "fsi", reason: "Not supported on this device" }

        ]
    }
    if (["F28P55x"].includes(getDeviceName())) {
        return [
            { name: "uart", reason: "Not supported on this device" }

        ]
    }
    if (getDeviceName().includes("F29")) {
        return [
            { name: "sci", reason: "Not supported on this device" },
            { name: "usb", reason: "Not supported on this device" }
        ]
    }
    return [
    ]
}

function hasFSISupport() {
    if (!isC2000()) {
        return true;
    }
    else {
        let fsiNotSupported = (getCommPeripheralsOnDevice().filter(perph => (perph.name == "fsi")).length >= 1);
        return !fsiNotSupported;
    }
}

function getNumberHashTableInstances() {
    let hashTables = system.modules['/hashTable.js'];
    if (hashTables) {
        return hashTables.$instances.length
    }
    return 0;
}


//
// Check if tool is loaded in SETUP mode in system context
//

function isAllocationSetupMode() {

    let val = system.resourceAllocation ? (system.resourceAllocation.mode == "SETUP") : false    
    return ( val && system.context == "system");
}


module.exports = {
    isC2000: isC2000,
    isC28x: isC28x,
    isC29x: isC29x,
    getTransferSourcePath: getTransferSourcePath,
    getProductName: getProductName,
    getTransferPath: getTransferPath,
    getSDKPath: getSDKPath,
    getAbsoluteTransferPath: getAbsoluteTransferPath,
    getDeviceTypeName: getDeviceTypeName,
    getCommPeripheralsOnDevice: getCommPeripheralsOnDevice,
    getDeviceName: getDeviceName,
    hasFSISupport: hasFSISupport,
    getNumberHashTableInstances: getNumberHashTableInstances,
    isAllocationSetupMode: isAllocationSetupMode
}
