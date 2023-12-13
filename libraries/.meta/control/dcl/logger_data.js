//==========================================================================
// CONFIG ENTRIES DICTIONARY
// These get directly dropped into the config list of the controller.js
//==========================================================================
var config_entries = []
 
//==========================================================================
// REFERENCE FILES AND HEADER FILES
// Functions and data for the reference files that should be pulled in
//==========================================================================
// c and asm files, to be pulled in using submodules
var refFiles = {
    "DCL_calcGamma":    {"name":"DCL_calcGamma",    "path":"../libraries/control/DCL/c28/source/DCL_calcGamma.asm",     "alwaysInclude":false},
    "DCL_clamp_C1":     {"name":"DCL_clamp_C1",     "path":"../libraries/control/DCL/c28/source/DCL_clamp_C1.asm",      "alwaysInclude":false},
    "DCL_clamp_L1":     {"name":"DCL_clamp_L1",     "path":"../libraries/control/DCL/c28/source/DCL_clamp_L1.asm",      "alwaysInclude":false},
    "DCL_DF11_C1":      {"name":"DCL_DF11_C1",      "path":"../libraries/control/DCL/c28/source/DCL_DF11_C1.asm",       "alwaysInclude":false},
    "DCL_DF11_L1":      {"name":"DCL_DF11_L1",      "path":"../libraries/control/DCL/c28/source/DCL_DF11_L1.asm",       "alwaysInclude":false},
    "DCL_DF13_C1":      {"name":"DCL_DF13_C1",      "path":"../libraries/control/DCL/c28/source/DCL_DF13_C1.asm",       "alwaysInclude":false},
    "DCL_DF13_C2C3":    {"name":"DCL_DF13_C2C3",    "path":"../libraries/control/DCL/c28/source/DCL_DF13_C2C3.asm",     "alwaysInclude":false},
    "DCL_DF13_L1":      {"name":"DCL_DF13_L1",      "path":"../libraries/control/DCL/c28/source/DCL_DF13_L1.asm",       "alwaysInclude":false},
    "DCL_DF13_L2L3":    {"name":"DCL_DF13_L2L3",    "path":"../libraries/control/DCL/c28/source/DCL_DF13_L2L3.asm",     "alwaysInclude":false},
    "DCL_DF22_C1":      {"name":"DCL_DF22_C1",      "path":"../libraries/control/DCL/c28/source/DCL_DF22_C1.asm",       "alwaysInclude":false},
    "DCL_DF22_C2C3":    {"name":"DCL_DF22_C2C3",    "path":"../libraries/control/DCL/c28/source/DCL_DF22_C2C3.asm",     "alwaysInclude":false},
    "DCL_DF22_L1":      {"name":"DCL_DF22_L1",      "path":"../libraries/control/DCL/c28/source/DCL_DF22_L1.asm",       "alwaysInclude":false},
    "DCL_DF22_L2L3":    {"name":"DCL_DF22_L2L3",    "path":"../libraries/control/DCL/c28/source/DCL_DF22_L2L3.asm",     "alwaysInclude":false},
    "DCL_DF23_C1":      {"name":"DCL_DF23_C1",      "path":"../libraries/control/DCL/c28/source/DCL_DF23_C1.asm",       "alwaysInclude":false},
    "DCL_DF23_C2C3":    {"name":"DCL_DF23_C2C3",    "path":"../libraries/control/DCL/c28/source/DCL_DF23_C2C3.asm",     "alwaysInclude":false},
    "DCL_DF23_L1":      {"name":"DCL_DF23_L1",      "path":"../libraries/control/DCL/c28/source/DCL_DF23_L1.asm",       "alwaysInclude":false},
    "DCL_DF23_L2L3":    {"name":"DCL_DF23_L2L3",    "path":"../libraries/control/DCL/c28/source/DCL_DF23_L2L3.asm",     "alwaysInclude":false},
    "DCL_error":        {"name":"DCL_error",        "path":"../libraries/control/DCL/c28/source/DCL_error.c",           "alwaysInclude":false},
    "DCL_frwlog":       {"name":"DCL_frwlog",       "path":"../libraries/control/DCL/c28/source/DCL_frwlog.asm",        "alwaysInclude":false},
    "DCL_futils":       {"name":"DCL_futils",       "path":"../libraries/control/DCL/c28/source/DCL_futils.asm",        "alwaysInclude":false},
    "DCL_futils32":     {"name":"DCL_futils32",     "path":"../libraries/control/DCL/c28/source/DCL_futils32.asm",      "alwaysInclude":false},
    "DCL_index":        {"name":"DCL_index",        "path":"../libraries/control/DCL/c28/source/DCL_index.asm",         "alwaysInclude":false},
    "DCL_NLPID_C3":     {"name":"DCL_NLPID_C3",     "path":"../libraries/control/DCL/c28/source/DCL_NLPID_C3.asm",      "alwaysInclude":false},
    "DCL_PI_A1":        {"name":"DCL_PI_A1",        "path":"../libraries/control/DCL/c28/source/DCL_PI_A1.asm",         "alwaysInclude":false},
    "DCL_PI_C1":        {"name":"DCL_PI_C1",        "path":"../libraries/control/DCL/c28/source/DCL_PI_C1.asm",         "alwaysInclude":false},
    "DCL_PI_C4":        {"name":"DCL_PI_C4",        "path":"../libraries/control/DCL/c28/source/DCL_PI_C4.asm",         "alwaysInclude":false},
    "DCL_PI_C7":        {"name":"DCL_PI_C7",        "path":"../libraries/control/DCL/c28/source/DCL_PI_C7.asm",         "alwaysInclude":false},
    "DCL_PI_L1":        {"name":"DCL_PI_L1",        "path":"../libraries/control/DCL/c28/source/DCL_PI_L1.asm",         "alwaysInclude":false},
    "DCL_PI_L2":        {"name":"DCL_PI_L2",        "path":"../libraries/control/DCL/c28/source/DCL_PI_L2.asm",         "alwaysInclude":false},
    "DCL_PI2_C2":       {"name":"DCL_PI2_C2",       "path":"../libraries/control/DCL/c28/source/DCL_PI2_C2.asm",        "alwaysInclude":false},
    "DCL_PID_A1":       {"name":"DCL_PID_A1",       "path":"../libraries/control/DCL/c28/source/DCL_PID_A1.asm",        "alwaysInclude":false},
    "DCL_PID_C1":       {"name":"DCL_PID_C1",       "path":"../libraries/control/DCL/c28/source/DCL_PID_C1.asm",        "alwaysInclude":false},
    "DCL_PID_C4":       {"name":"DCL_PID_C4",       "path":"../libraries/control/DCL/c28/source/DCL_PID_C4.asm",        "alwaysInclude":false},
    "DCL_PID_L1":       {"name":"DCL_PID_L1",       "path":"../libraries/control/DCL/c28/source/DCL_PID_L1.asm",        "alwaysInclude":false},
    "DCL_PID_L2":       {"name":"DCL_PID_L2",       "path":"../libraries/control/DCL/c28/source/DCL_PID_L2.asm",        "alwaysInclude":false}
}

// h files, to be pulled in using c2000_libraries.h.xdt
// some of these header files have certain refFiles (asm/c files) dependencies
// NOTE: (probably) cannot move the refFilesList into the control_struct_dict since each header file references these reference files lists. If a reference file doesn't exist when the header file is imported, it may flag an error.
var headerFiles = {
    "DCL":          {"path":"../libraries/control/DCL/c28/include/DCL.h",          "refFilesList":["DCL_error"]},
    "DCLC28":       {"path":"../libraries/control/DCL/c28/include/DCLC28.h",       "refFilesList":["DCL_futils32","DCL_PID_A1","DCL_futils32","DCL_PI_A1"]},
    "DCLCLA":       {"path":"../libraries/control/DCL/c28/include/DCLCLA.h",       "refFilesList":["DCL_PID_L1","DCL_PID_L2","DCL_PI_L1","DCL_PI_L2","DCL_DF11_L1","DCL_DF13_L1","DCL_DF13_L2L3","DCL_DF13_L2L3","DCL_DF22_L1","DCL_DF22_L2L3","DCL_DF22_L2L3","DCL_DF23_L1","DCL_DF23_L2L3","DCL_DF23_L2L3","DCL_clamp_L1"]},
    "DCLF32":       {"path":"../libraries/control/DCL/c28/include/DCLF32.h",       "refFilesList":["DCL_futils","DCL_PID_C1","DCL_PID_C4","DCL_futils","DCL_PI_C1","DCL_PI_C4","DCL_PI_C7","DCL_futils","DCL_futils","DCL_DF11_C1","DCL_futils","DCL_DF13_C1","DCL_DF13_C2C3","DCL_DF13_C2C3","DCL_futils","DCL_DF22_C1","DCL_DF22_C2C3","DCL_DF22_C2C3","DCL_futils","DCL_DF23_C1","DCL_DF23_C2C3","DCL_DF23_C2C3","DCL_clamp_C1","DCL_futils"]},
    "DCLF64":       {"path":"../libraries/control/DCL/c28/include/DCLF64.h",       "refFilesList":[]},
    "DCL_fdlog":    {"path":"../libraries/control/DCL/c28/include/DCL_fdlog.h",    "refFilesList":["DCL_frwlog","DCL_frwlog"]},
    "DCL_fdlog64":  {"path":"../libraries/control/DCL/c28/include/DCL_fdlog64.h",  "refFilesList":[]},
    "DCL_log32":    {"path":"../libraries/control/DCL/c28/include/DCL_log32.h",    "refFilesList":[]},
    "DCL_MLOG":     {"path":"../libraries/control/DCL/c28/include/DCL_MLOG.h",     "refFilesList":[]},
    "DCL_MLOG32":   {"path":"../libraries/control/DCL/c28/include/DCL_MLOG32.h",   "refFilesList":[]},
    "DCL_NLPID":    {"path":"../libraries/control/DCL/c28/include/DCL_NLPID.h",    "refFilesList":["DCL_futils","DCL_calcGamma","DCL_NLPID_C3"]},
    "DCL_refgen":   {"path":"../libraries/control/DCL/c28/include/DCL_refgen.h",   "refFilesList":[]},
    "DCL_refgen64": {"path":"../libraries/control/DCL/c28/include/DCL_refgen64.h", "refFilesList":[]},
    "DCL_TCM":      {"path":"../libraries/control/DCL/c28/include/DCL_TCM.h",      "refFilesList":["DCL_index","DCL_index","DCL_index"]},
}

//==========================================================================
// CONTROL STRUCT LOOKUP DICTIONARY
// For each controller structure, determine which header files to use, and 
// the config lookup list for this controller
//==========================================================================
var control_struct_dict = {
    "LOG32":    {"headerFilesList":["DCL_log32"],                   "config_entries_list":['arrName','logSize','linkerEn','linkerVal','fillEn','fillVal']},
    "FDLOG":    {"headerFilesList":["DCL","DCL_fdlog"],             "config_entries_list":['arrName','logSize','linkerEn','linkerVal','fillEn','fillVal']},
    "FDLOG64":  {"headerFilesList":["DCL","DCL_fdlog64"],           "config_entries_list":['arrName','logSize','linkerEn','linkerVal','fillEn','fillVal']},
}

function getHeaderFilesList(controlStruct)
{
    return control_struct_dict[controlStruct]['headerFilesList'];
}

function getOptIncludePaths(controlStruct)
{
    var headerFilesList = control_struct_dict[controlStruct]['headerFilesList'];
    var includePathList = []
    for (var i in headerFilesList)
    {
        var headerFileName  = headerFilesList[i];
        var headerFileObj   = headerFiles[headerFileName];
        var headerFilePath  = headerFileObj["path"];
        var includePath = headerFilePath.split("/").slice(0,-1).join("/");
        if (!(includePathList.includes(includePath)))
        {
            includePathList.push(includePath);
        }
    }
    return includePathList;
}

function getRefFilesModuleArrFromControlStruct(controlStruct)
{
    if (controlStruct.length === 0)
    {
        return [];
    }
    var arr = [];
    var headerFilesList = control_struct_dict[controlStruct]['headerFilesList'];
    var pathToDynamicJsFiles = "/libraries/control/dcl/templates/dynamic_mods/"
    for (var i in headerFilesList)
    {
        var h = headerFilesList[i]
        var refFilesList = headerFiles[h]['refFilesList'];
        for (var j in refFilesList)
        {
            var refFileName = refFilesList[j]
            var moduleNamePath = pathToDynamicJsFiles + refFileName + "_dynamic.js"
            // if it hasn't been added yet, add it
            var alreadyInArray = arr.some(el => refFileName === el["name"])
            if (!alreadyInArray)
            {
                arr.push({
                    name:refFileName,
                    moduleName:moduleNamePath,
                });
            }
        }
    }
    // all available Sysconfig devices use at least FPU32, and so require FPU.js to be included
    arr.push({name:"fpu", moduleName:"/libraries/.meta/math/FPU/FPU.js", hidden:false});
    return arr;
}

function getModuleDataObj(inst)
{
    var loggerChoice = inst.structDisplay;
    // get the data type
    var type = null;
    // also get the fillLogCmd command, like "fillLog32"
    var fillLogCmd = null;
    if (inst.loggerPrecision == "FIXED")
    {
        type = "int32_t";
        fillLogCmd = "DCL_fillLog32";
    }
    else if(inst.loggerPrecision == "F32")
    {
        type = "float32_t";
        fillLogCmd = "DCL_fillLog";
    }
    else if(inst.loggerPrecision == "F64")
    {
        type = "float64_t";
        fillLogCmd = "DCL_fillLog64";
    }
    // default to F32
    else
    {
        type = "float32_t";
        fillLogCmd = "DCL_fillLog";
    }

    // get the arrName, update with recommendation if empty string
    var arrName = inst.arrName;
    if (arrName=="")
    {
        arrName = inst.$name + "Arr";
    }

    // get the logSize value
    var logSize = inst.logSize;

    // get the linkerVal (if any)
    var linkerVal = null;
    if (inst.linkerEn == true)
    {
        linkerVal = inst.linkerVal;
        // replace empty string with the instance name by default
        if (linkerVal=="")
        {
            linkerVal = inst.$name + 'DataLogSection';
        }
    }

    // get the fillVal (if any)
    var fillVal = null;
    if (inst.fillEn == true)
    {
        fillVal = inst.fillVal;
    }

    // get the initLogCmd
    var initLogCmdObj = {
        "FDLOG":   "DCL_initLog",
        "FDLOG64": "DCL_initLog64",
        "LOG32":   "DCL_initLog32",
    };
    var initLogCmd = initLogCmdObj[loggerChoice];

    var resData = {
        "loggerChoice":loggerChoice,
        "type":type,
        "instName":inst.$name,
        "arrName":arrName,
        "logSize":logSize,
        "linkerVal":linkerVal,
        "fillVal":fillVal,
        "fillLogCmd":fillLogCmd,
        "initLogCmd":initLogCmd,
        "arrEn":inst.arrEn,
    };

    return resData;
}

//==========================================================================
// EXPORTS
// Export all of the functions so variables/structures can be accessed
// in other .js files
//==========================================================================
exports = {
    getRefFilesModuleArrFromControlStruct: getRefFilesModuleArrFromControlStruct,
    getOptIncludePaths:getOptIncludePaths,
    getHeaderFilesList:getHeaderFilesList,
    getModuleDataObj:getModuleDataObj,
}