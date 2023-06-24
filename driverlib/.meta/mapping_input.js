function callParser(memoryData, debug, device_name, IP_NAME, defaults){
    //Inputs
    var regData = require('device_driverlib_peripherals/' + device_name.toLowerCase() + '_' + IP_NAME + '_registers')[IP_NAME.toUpperCase() + 'Registers']; //Read parsed registers
    let syscfgData = system.getScript(IP_NAME + '/' + IP_NAME + '.json'); //Read SysConfig JSON
    //console.log(syscfgData);
    for(let i = 0; i < syscfgData[IP_NAME].length; i++){
        syscfgData[IP_NAME][i]["MapHit"] = 0;
        if(syscfgData[IP_NAME][i].devices.includes(device_name)){continue;}
        else{syscfgData[IP_NAME].splice(i, 1); i--;}
    }
    //console.log(syscfgData);
    let syscfgConfigs = system.getScript(IP_NAME + '/' + IP_NAME + '_syscfg_configs/' + device_name.toLowerCase() + '_' + IP_NAME + '_syscfg_configs.json'); //Read SysConfig Configs JSON
    let enumValueData = require('device_driverlib_peripherals/' + device_name.toLowerCase() + '_' + IP_NAME + '_values'); //Read parsed registers 
    let driverlibInfo = require('device_driverlib_peripherals/functions/' + device_name.toLowerCase() + '/' + IP_NAME)[IP_NAME + '_driverlib'].functions;
    let mapHandlers = require(IP_NAME + '/' + IP_NAME + '_map_handlers');
    //Initialize outputs to be written
    var syscfgMemOut = "";
    var mappedMemOut = "";
    var regMap = [];
    var handlerConfigs = [];
    var useHandler = 0;
    //still need to add in error checking for functions of conversion
    //convert the memory data the user inputted into the register memory equivalent
    //the below three functions returns an array where the 0th index is a string holding the entirety of the register memory and the 1st index is an array of dictionaries
    //where the whitespace, newlines, and toplevel register names and values (where not needed) have been removed and cleaned.
    const conversionFunctions = require("./reBasedMemoryMapper");
    let parsedMemoryRegisters = conversionFunctions.parseMemoryIntoReg(memoryData, regData);
    //console.log(parsedMemoryRegisters);

    //remove all spaces and break component name and value into seperate chunks to make data easier to parse later on
    var parsedSyscfgMemory = conversionFunctions.parseRegIntoSyscfgMem(syscfgData[IP_NAME], parsedMemoryRegisters[1], mapHandlers);
    //console.log(parsedSyscfgMemory);
    var parsedMappedMemory = conversionFunctions.parseSyscfgMemToValues(parsedSyscfgMemory[1], enumValueData, syscfgConfigs);
    if (!defaults){
        return parsedMappedMemory[2];
    }
    else if (defaults){
        return parsedMappedMemory[1];
    }
    else{
        throw new Error('DEFAULT FLAG EITHER NOT PASSED IN OR INCORRECTLY CONFIGURED AS A NON-BOOLEAN, PLEASE CONFIRM');
    }
}

module.exports = {
    callParser : callParser
}
