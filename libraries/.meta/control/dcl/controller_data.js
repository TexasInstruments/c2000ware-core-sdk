var longDescriptionObj = system.getScript("/libraries/control/dcl/controller_longdesc.js").get_longDescriptionObj();
let fpu_obj = system.getScript("/libraries/.meta/math/FPU/FPU.js").moduleStatic.config;
//==========================================================================
// CONFIG ENTRIES LOOKUP LISTS
// Use to lookup which config entries to enable/disable per controller 
// structure. Stored as "{name:default_val}"
//==========================================================================
// PID
var PID32   = [["Kp","0x01000000"],["Ki","0L"],["Kd","0L"],["c1","0x01000000"],["c2","0L"],["d2","0L"],["d3","0L"],["i10","0L"],["i14","0x01000000"],["Umax","0x01000000"],["Umin","0xFF000000"]]
var PID_CLA = [["Kp","1.0f"],["Ki","0.0f"],["Kd","0.0f"],["Kr","1.0f"],["c1","0.0f"],["c2","0.0f"],["d2","0.0f"],["d3","0.0f"],["i10","0.0f"],["i14","0.0f"],["Umax","1.0f"],["Umin","-1.0f"]]
var PID     = [["Kp","1.0f"],["Ki","0.0f"],["Kd","0.0f"],["Kr","1.0f"],["c1","1.0f"],["c2","0.0f"],["d2","0.0f"],["d3","0.0f"],["i10","0.0f"],["i14","1.0f"],["Umax","1.0f"],["Umin","-1.0f"]]
var PIDF64  = [["Kp","1.0L"],["Ki","0.0L"],["Kd","0.0L"],["Kr","1.0L"],["c1","0.0L"],["c2","0.0L"],["d2","0.0L"],["d3","0.0L"],["i10","0.0L"],["i14","0.0L"],["i16","0.0L"],["Umax","1.0L"],["Umin","-1.0L"]]

// PI
var PI32 =  [["Kp","0x01000000"],["Ki","0L"],["i6","0x01000000"],["i10","0L"],["Umax","0x01000000"],["Umin","0xFF000000"]]
var PI_CLA  = [["Kp","1.0f"],["Ki","0.0f"],["i10","0.0f"],["Umax","1.0f"],["Umin","-1.0f"],["i6","1.0f"],["i11","0.0f"],["Imax","1.0f"],["Imin","-1.0f"]]
var PI      = [["Kp","1.0f"],["Ki","0.0f"],["i10","0.0f"],["Umax","1.0f"],["Umin","-1.0f"],["i6","1.0f"],["i11","0.0f"],["Imax","1.0f"],["Imin","-1.0f"]]
var PI2     = [["Kp","1.0f"],["Ki","0.0f"],["i6{PI2}","0.0f"],["i9","0.0f"],["i12","1.0f"],["i13","1.0f"],["Umax","1.0f"],["Umin","-1.0f"]]

//NLPID
var NLPID       = [["Kp","1.0f"],["Ki","0.0f"],["Kd","0.0f"],["alpha_p","1.0f"],["alpha_i","1.0f"],["alpha_d","1.0f"],["delta_p","0.1f"],["delta_i","0.1f"],["delta_d","0.1f"],["gamma_p","1.0f"],["gamma_i","1.0f"],["gamma_d","1.0f"],["c1","1.0f"],["c2","0.0f"],["d2","0.0f"],["d3","0.0f"],["i7","0.0f"],["i16","1.0f"],["i18","0.0f"],["Umax","1.0f"],["Umin","-1.0f"]]

// DF
var DF11_CLA = [["b0","0.5f"],["b1","0.5f"],["a1","1.0f"],["d1","0.0f"],["d2{DF11}","0.0f"]]
var DF13_CLA = [["b0","0.25f"],["b1","0.25f"],["b2","0.25f"],["b3","0.25f"],["a0","0.0f"],["a1","0.0f"],["a2","0.0f"],["a3","0.0f"],["d0","0.0f"],["d1","0.0f"],["d2{DF13}","0.0f"],["d3{DF13}","0.0f"],["d4","0.0f"],["d5","0.0f"],["d6","0.0f"],["d7","0.0f"]]
var DF22_CLA = [["b0","1.0f"],["b1","0.0f"],["b2","0.0f"],["a1","0.0f"],["a2","0.0f"],["x1","0.0f"],["x2","0.0f"]]
var DF23_CLA = [["b0","1.0f"],["b1","0.0f"],["b2","0.0f"],["b3","0.0f"],["a1","0.0f"],["a2","0.0f"],["a3","0.0f"],["x1","0.0f"],["x2","0.0f"],["x3","0.0f"]]
var DF11 = [["b0","0.5f"],["b1","0.5f"],["a1","0.0f"],["d1","0.0f"],["d2{DF11}","0.0f"]]
var DF13 = [["b0","0.25f"],["b1","0.25f"],["b2","0.25f"],["b3","0.25f"],["a0","1.0f"],["a1","0.0f"],["a2","0.0f"],["a3","0.0f"],["d0","0.0f"],["d1","0.0f"],["d2{DF13}","0.0f"],["d3{DF13}","0.0f"],["d4","0.0f"],["d5","0.0f"],["d6","0.0f"],["d7","0.0f"]]
var DF22 = [["b0","1.0f"],["b1","0.0f"],["b2","0.0f"],["a1","0.0f"],["a2","0.0f"],["x1","0.0f"],["x2","0.0f"]]
var DF23 = [["b0","1.0f"],["b1","0.0f"],["b2","0.0f"],["b3","0.0f"],["a1","0.0f"],["a2","0.0f"],["a3","0.0f"],["x1","0.0f"],["x2","0.0f"],["x3","0.0f"]]
var DF22F64 = [["b0","1.0"],["b1","0.0"],["b2","0.0"],["a1","0.0"],["a2","0.0"],["x1","0.0"],["x2","0.0"]]

//==========================================================================
// CONFIG ENTRIES DICTIONARY
// These get directly dropped into the config list of the controller.js
//==========================================================================
var config_entries = [
    {name:"Kp",         displayName:"Proportional Gain (Kp)",                       description:"Controller Proportional Gain",             hidden:true, default:""},// PID
    {name:"Ki",         displayName:"Integral Gain (Ki)",                           description:"Controller Integral Gain",                 hidden:true, default:""},
    {name:"Kd",         displayName:"Derivative Gain (Kd)",                         description:"Controller Derivative Gain",               hidden:true, default:""},
    {name:"Kr",         displayName:"Set Point Weight (Kr)",                        description:"Set Point Weight",                         hidden:true, default:""},
    {name:"c1",         displayName:"D-term filter coefficient 1 (c1)",             description:"D-term filter coefficient 1",              hidden:true, default:""},
    {name:"c2",         displayName:"D-term filter coefficient 2 (c2)",             description:"D-term filter coefficient 2",              hidden:true, default:""},
    {name:"d2",         displayName:"D-term filter Intermediate Storage 1 (d2)",    description:"D-term filter Intermediate Storage 1",     hidden:true, default:""},
    {name:"d3",         displayName:"D-term filter Intermediate Storage 2 (d3)",    description:"D-term filter Intermediate Storage 2",     hidden:true, default:""},
    {name:"i10",        displayName:"I-term Intermediate Storage (i10)",            description:"I-term Intermediate Storage",              hidden:true, default:""},
    {name:"i14",        displayName:"Intermediate Saturation Storage (i14)",        description:"Intermediate Saturation Storage",          hidden:true, default:""},
    {name:"i16",        displayName:"Spare (i16)",                                  description:"Spare",                                    hidden:true, default:""},
    {name:"Umax",       displayName:"Upper Saturation Limit (Umax)",                description:"Upper Saturation Limit",                   hidden:true, default:""},
    {name:"Umin",       displayName:"Lower Saturation Limit (Umin)",                description:"Lower Saturation Limit",                   hidden:true, default:""},
    {name:"i6",         displayName:"Saturation Storage (i6)",                      description:"Saturation Storage",                       hidden:true, default:""},// PI unique
    {name:"i6{PI2}",    displayName:"Integrator 1 Storage (i6)",                    description:"Integrator 1 Storage",                     hidden:true, default:""},
    {name:"i9",         displayName:"Integrator 2 Storage (i9)",                    description:"Integrator 2 Storage",                     hidden:true, default:""},
    {name:"i11",        displayName:"I Storage (i11)",                              description:"I Storage",                                hidden:true, default:""},
    {name:"i12",        displayName:"Saturation 1 Storage (i12)",                   description:"Saturation 1 Storage",                     hidden:true, default:""},
    {name:"i13",        displayName:"Saturation 2 Storage (i13)",                   description:"Saturation 2 Storage",                     hidden:true, default:""},
    {name:"Imax",       displayName:"Upper integrator saturation limit (Imax)",     description:"Upper integrator saturation limit",        hidden:true, default:""},
    {name:"Imin",       displayName:"Lower integrator saturation limit (Imin)",     description:"Lower integrator saturation limit",        hidden:true, default:""},
    {name:"alpha_p",    displayName:"P path non-linear exponent (alpha_p)",         description:"P path non-linear exponent",               hidden:true, default:""},// NLPID unique
    {name:"alpha_i",    displayName:"I path non-linear exponent (alpha_i)",         description:"I path non-linear exponent",               hidden:true, default:""},
    {name:"alpha_d",    displayName:"D path non-linear exponent (alpha_d)",         description:"D path non-linear exponent",               hidden:true, default:""},
    {name:"delta_p",    displayName:"P path linearized range (delta_p)",            description:"P path linearized range",                  hidden:true, default:""},
    {name:"delta_i",    displayName:"I path linearized range (delta_i)",            description:"I path linearized range",                  hidden:true, default:""},
    {name:"delta_d",    displayName:"D path linearized range (delta_d)",            description:"D path linearized range",                  hidden:true, default:""},
    {name:"gamma_p",    displayName:"P path gain limit (gamma_p)",                  description:"P path gain limit",                        hidden:true, default:""},
    {name:"gamma_i",    displayName:"I path gain limit (gamma_i)",                  description:"I path gain limit",                        hidden:true, default:""},
    {name:"gamma_d",    displayName:"D path gain limit (gamma_d)",                  description:"D path gain limit",                        hidden:true, default:""},
    {name:"i7",         displayName:"I path intermediate storage (i7)",             description:"I path intermediate storage",              hidden:true, default:""},
    {name:"i18",        displayName:"Spare (i18)",                                  description:"Spare",                                    hidden:true, default:""},
    {name:"a0",         displayName:"a0",                                           description:"a0",                                       hidden:true, default:""},// DF unique
    {name:"a1",         displayName:"a1",                                           description:"a1",                                       hidden:true, default:""},
    {name:"a2",         displayName:"a2",                                           description:"a2",                                       hidden:true, default:""},
    {name:"a3",         displayName:"a3",                                           description:"a3",                                       hidden:true, default:""},
    {name:"b0",         displayName:"b0",                                           description:"b0",                                       hidden:true, default:""},
    {name:"b1",         displayName:"b1",                                           description:"b1",                                       hidden:true, default:""},
    {name:"b2",         displayName:"b2",                                           description:"b2",                                       hidden:true, default:""},
    {name:"b3",         displayName:"b3",                                           description:"b3",                                       hidden:true, default:""},
    {name:"d0",         displayName:"e(k) (d0)",                                    description:"e(k)",                                     hidden:true, default:""},
    {name:"d1",         displayName:"e(k-1) (d1)",                                  description:"e(k-1)",                                   hidden:true, default:""},
    {name:"d2{DF11}",   displayName:"u(k-1) (d2)",                                  description:"u(k-1)",                                   hidden:true, default:""},
    {name:"d2{DF13}",   displayName:"e(k-2) (d2)",                                  description:"e(k-2)",                                   hidden:true, default:""},
    {name:"d3{DF13}",   displayName:"e(k-3) (d3)",                                  description:"e(k-3)",                                   hidden:true, default:""},
    {name:"d4",         displayName:"u(k) (d4)",                                    description:"u(k)",                                     hidden:true, default:""},
    {name:"d5",         displayName:"u(k-1) (d5)",                                  description:"u(k-1)",                                   hidden:true, default:""},
    {name:"d6",         displayName:"u(k-2) (d6)",                                  description:"u(k-2)",                                   hidden:true, default:""},
    {name:"d7",         displayName:"u(k-3) (d7)",                                  description:"u(k-3)",                                   hidden:true, default:""},
    {name:"x1",         displayName:"x1",                                           description:"x1",                                       hidden:true, default:""},
    {name:"x2",         displayName:"x2",                                           description:"x2",                                       hidden:true, default:""},
    {name:"x3",         displayName:"x3",                                           description:"x3",                                       hidden:true, default:""},
]

/**
 * Get the config_entries list of dictionaries, for use in config array
 * @returns config_entries list of dictionaries
 */
function get_config_entries_list()
{
    return config_entries;
}

/**
 * Get a specific dictionary within config_entries
 * @param {string} name - The "name" of the dicitonary in 
 * config_entries to return
 * @returns 
 */
function get_config_entry(name)
{
    for (obj of config_entries){
        if (obj.name === name){
            return obj
        }
    }
}

/**
 * Get the default values for a given control structure
 * @param {string} name - Name of the control type (like "PID") to have its variables unhidden
 */
 function get_default_param_val(name, param_name)
 {
     var config_entries_list = get_control_struct_entry(name)["config_entries_list"];
     for (var name_val_list of config_entries_list)
     {
         if (name_val_list[0]==param_name)
        {
            return name_val_list[1];
        }
     }
     return 0;
 }

/**
 * Choose which controller to have its parameters be unhidden by default
 * @param {string} name - Name of the control type (like "PID") to have its variables unhidden
 */
 function set_config_entries_default_unhidden(name)
 {
     var config_entries_list = get_control_struct_entry(name)["config_entries_list"];
     for (var obj of config_entries)
     {
         for (var name_val_list of config_entries_list)
         {
            if (name_val_list[0]==obj["name"])
            {
                obj["hidden"] = false;
                obj["default"] = name_val_list[1];
                break;
            }
         }
     }
 }

 
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

function getRefFilesArr()
{
    var refArr = []
    for (var ref in refFiles)
    {
        refArr.push(refFiles[ref])
    }
    return refArr
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

function getLongDescriptionConfigEntries(defaultControllerChoice)
{
    var defaultLongDescName = control_struct_dict[defaultControllerChoice]["longDescName"];
    var configArr = [];
    for (var [c,longDescStr] of Object.entries(longDescriptionObj))
    {
        var hideByDefault = true;
        if (c == defaultLongDescName)
        {
            hideByDefault = false;
        }
        configArr.push({
            name:"longDesc_" + c,
            hidden:hideByDefault,
            default:"Click Question Mark for Details",
            displayName:"Detailed Description",
            longDescription:longDescStr,
            readOnly:true
        });
    }
    return configArr;
}

//==========================================================================
// CONTROL STRUCT LOOKUP DICTIONARY
// For each controller structure, determine which header files to use, and 
// the config lookup list for this controller
//==========================================================================
var control_struct_dict = {
    "PID32":    {"headerFilesList":["DCL","DCLC28"],    "longDescName":"PID32",  "config_entries_list":PID32},
    "PID_CLA":  {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"PID",    "config_entries_list":PID_CLA},
    "PID":      {"headerFilesList":["DCL","DCLF32"],    "longDescName":"PID",    "config_entries_list":PID},
    "PIDF64":   {"headerFilesList":["DCL","DCLF64"],    "longDescName":"PID",    "config_entries_list":PIDF64},
    "PI32":     {"headerFilesList":["DCL","DCLC28"],    "longDescName":"PI32",   "config_entries_list":PI32},
    "PI_CLA":   {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"PI",     "config_entries_list":PI_CLA},
    "PI":       {"headerFilesList":["DCL","DCLF32"],    "longDescName":"PI",     "config_entries_list":PI},
    "PI2":      {"headerFilesList":["DCL","DCLF32"],    "longDescName":"PI2",    "config_entries_list":PI2},
    "NLPID":    {"headerFilesList":["DCL","DCL_NLPID"], "longDescName":"NLPID",  "config_entries_list":NLPID},
    "DF11_CLA": {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"DF11",   "config_entries_list":DF11_CLA},
    "DF13_CLA": {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"DF13",   "config_entries_list":DF13_CLA},
    "DF22_CLA": {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"DF22",   "config_entries_list":DF22_CLA},
    "DF23_CLA": {"headerFilesList":["DCL","DCLCLA"],    "longDescName":"DF23",   "config_entries_list":DF23_CLA},
    "DF11":     {"headerFilesList":["DCL","DCLF32"],    "longDescName":"DF11",   "config_entries_list":DF11},
    "DF13":     {"headerFilesList":["DCL","DCLF32"],    "longDescName":"DF13",   "config_entries_list":DF13},
    "DF22":     {"headerFilesList":["DCL","DCLF32"],    "longDescName":"DF22",   "config_entries_list":DF22},
    "DF23":     {"headerFilesList":["DCL","DCLF32"],    "longDescName":"DF23",   "config_entries_list":DF23},
    "DF22F64":  {"headerFilesList":["DCL","DCLF64"],    "longDescName":"DF22",   "config_entries_list":DF22F64},

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

/**
 * Get the full control_struct_dict, which has every control structure
 * @returns {dict} control_struct_dict, which contains each control stucture 
 *      type, the header/asm files, and the corresponding config_entries_list
 */
function get_control_struct_dict()
{
    return control_struct_dict;
}

/**
 * Get a specific control_struct_dict entry by name.
 * @param {string} name - The name of the control structure to return (like "PID32")
 * @returns A specific control_struct_dict entry
 */
function get_control_struct_entry(name)
{
    return control_struct_dict[name];
}

//==========================================================================
// DROPDOWN TO CONTROL STRUCTURE DICTIONARY
// List the displayName and control structures (like "PIDF64") available for
// each dropdown option (controller, precision, and accelerator).
//==========================================================================
var dropdown_to_controlstruct_dict = {
    "controller":{
        "PID":{
            "displayName": "PID",
            "structAvail":["PID32","PID_CLA","PID","PIDF64"]
        },
        "PI":{
            "displayName": "PI",
            "structAvail":["PI32","PI_CLA","PI"]
        },
        "PI2":{
            "displayName": "PI\xB2",
            "structAvail":["PI2"]
        },
        "NLPID":{
            "displayName": "Non-Linear PID",
            "structAvail":["NLPID"]
        },
        "DF11":{
            "displayName": "Direct-Form 1, 1st Order",
            "structAvail":["DF11","DF11_CLA"]
        },
        "DF13":{
            "displayName": "Direct-Form 1, 3rd Order",
            "structAvail":["DF13","DF13_CLA"]
        },
        "DF22":{
            "displayName": "Direct-Form 2, 2nd Order",
            "structAvail":["DF22","DF22_CLA","DF22F64"]
        },
        "DF23":{
            "displayName": "Direct-Form 2, 3rd Order",
            "structAvail":["DF23","DF23_CLA"]
        },
    },

    "precision":{
        "FIXED":{
            "displayName": "Fixed-Point (32-bit)",
            "structAvail":["PID32","PI32"]
        },
        "F32":{
            "displayName": "Floating-Point (32-bit)",
            "structAvail":["PID_CLA","PID","PI_CLA","PI","PI2","NLPID","DF11","DF11_CLA","DF13","DF13_CLA","DF22","DF22_CLA","DF23","DF23_CLA"]
        },
        "F64":{
            "displayName": "Floating-Point (64-bit)",
            "structAvail":["PIDF64","DF22F64"]
        }
    },

    "accelerator": {
        "NONE":{
            "displayName": "NONE",
            "structAvail":["PID32","PID","PIDF64","PI32","PI","PI2","NLPID","DF11","DF13","DF22","DF23","DF22F64"]
        },
        // "CLA":{
        //     "displayName": "Control Law Accelerator (CLA)",
        //     "structAvail":["PID_CLA","PI_CLA","DF11_CLA","DF13_CLA","DF22_CLA","DF23_CLA"]
        // }
    }
}

// check FPU and TMU support
var fpu_types = fpu_obj.filter(fpu_or_tmu_list => fpu_or_tmu_list.name === "fpuType")[0].options;
var tmu_types = fpu_obj.filter(fpu_or_tmu_list => fpu_or_tmu_list.name === "tmuType")[0].options;
var fpu64_supported = false;
var tmu1_supported  = false;
if (fpu_types.length >= 2) {
    // 2 options available means that both FPU32 (all Sysconfig devices) and FPU64 (some Sysconfig devices) are supported
    fpu64_supported = true;
}
if (tmu_types.filter(tmu_obj => tmu_obj.name === "TMU1").length > 0) {
    // look for TMU1 support from FPU.js
    tmu1_supported = true;
}
// remove certain options depending on FPU/TMU support available 
// (don't remove F64 since it can technically be used with FPU32 processor, but with degraded performance)
if (!tmu1_supported)    {delete dropdown_to_controlstruct_dict["controller"]["NLPID"];}

//==========================================================================
// STRUCTURES AVAILABLE PER DEVICE
// List the device GPN and control structures (like "PIDF64") available for
// each device. Some devices don't have FPU64 (which would prevent *64 
// usage), and some don't have TMU1 (which would prevent NLPID usage)
//==========================================================================
// start with a list of structures available on all devices (devices with at least C28x and FPU32)
var structs_avail_per_device = ["PID32","PID","PIDF64","PI32","PI","PI2",/*"NLPID",*/"DF11","DF13","DF22","DF23","DF22F64"];
// add TMU1 entries if there is "TMU1" available
// NLPID only available on devices with TMU1 (like F28002x and F28003x)
if (tmu1_supported)     {structs_avail_per_device = structs_avail_per_device.concat(["NLPID"]);}

/**
 * 
 */
 function intersect(a, b) {
    var setA = new Set(a);
    var setB = new Set(b);
    var intersection = new Set([...setA].filter(x => setB.has(x)));
    return Array.from(intersection);
  }

/**
 * Get the controllerChoice options to be displayed within Sysconfig
 * @returns list of dicts with {name, displayName} entries for each control option
 */
function get_dropdown_list(list_name)
{
    var l = [];
    for (var opt in dropdown_to_controlstruct_dict[list_name])
    {
        l.push({name:opt, displayName:dropdown_to_controlstruct_dict[list_name][opt]['displayName']});
    }
    return l;
}

function get_struct_options(dropdown_choices_dict)
{
    var all_controlstruct_lists = []
    // using the list of options, get a list of structures available for each option (like "precision==FPU64")
    for (var accelerator in dropdown_choices_dict)
    {
        var choice = dropdown_choices_dict[accelerator];
        all_controlstruct_lists.push(dropdown_to_controlstruct_dict[accelerator][choice]['structAvail']);
    }

    // now get the options that are device specific (like TMU1 or FPU64 availability)
    all_controlstruct_lists.push(structs_avail_per_device);
    
    // find the intersection of a bunch of lists, returns elements that are in all lists

    // make the first list the starting array
    var intersection = all_controlstruct_lists[0];
    // get intersection of all the other lists and the first one
    for (var i = 1; i < all_controlstruct_lists.length; i++)
    {
        intersection = intersect(intersection,all_controlstruct_lists[i]);
    }
    
    return intersection;
    // return intersection
}

function getModuleDataObj(inst)
{
    var controllerChoice = inst.structDisplay;
    var type = controllerChoice;
    var defaultsListName = controllerChoice+'_DEFAULTS';
    // the following 4 controllers prepend DCL_ to their *_DEFAULTS list, so do the same here
    if(['PI32','PID32','REFGEN','REFGEN64'].includes(controllerChoice))
    {
        defaultsListName = 'DCL_'+defaultsListName;
    }

    var configEntriesList = get_control_struct_entry(controllerChoice)["config_entries_list"];
    var configEntriesVals = [];
    // create parameter,val pairs in lists, like [Ki,0]
    for (var j in configEntriesList)
    {
        configEntriesVals.push  ([
            configEntriesList[j][0],
            inst[configEntriesList[j][0]] 
        ]);
    }

    var resData = {
        "controllerChoice":controllerChoice,
        "type":type,
        "defaultsListName":defaultsListName,
        "instName":inst.$name,
        "configEntriesVals":configEntriesVals,
    };

    return resData;
}
//==========================================================================
// EXPORTS
// Export all of the functions so variables/structures can be accessed
// in other .js files
//==========================================================================
exports = {
    get_config_entries_list : get_config_entries_list,
    get_config_entry : get_config_entry,
    set_config_entries_default_unhidden : set_config_entries_default_unhidden,
    get_control_struct_dict : get_control_struct_dict,
    get_control_struct_entry : get_control_struct_entry,
    get_dropdown_list : get_dropdown_list,
    get_struct_options : get_struct_options,
    getRefFilesArr: getRefFilesArr,
    getRefFilesModuleArrFromControlStruct: getRefFilesModuleArrFromControlStruct,
    getOptIncludePaths:getOptIncludePaths,
    getHeaderFilesList:getHeaderFilesList,
    getModuleDataObj:getModuleDataObj,
    get_default_param_val:get_default_param_val,
    getLongDescriptionConfigEntries:getLongDescriptionConfigEntries,
    fpu64_supported:fpu64_supported,
    tmu1_supported:tmu1_supported
}