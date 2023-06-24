var fs = require('fs');
var path = require('path');
var childProcess = require('child_process');

function runScript(scriptPath, args, callback) {

    // keep track of whether callback has been invoked to prevent multiple invocations
    var invoked = false;

    var process = childProcess.fork(scriptPath, args);

    // listen for errors as they may prevent the exit event from firing
    process.on('error', function (err) {
        if (invoked) return;
        invoked = true;
        callback(err);
    });

    // execute the callback once the process has finished running
    process.on('exit', function (code) {
        if (invoked) return;
        invoked = true;
        var err = code === 0 ? null : new Error('exit code ' + code);
        callback(err);
    });

}



var c2000ware_root_path = process.argv.slice(2)[0];
var outputFolderPath = process.argv.slice(2)[1];
var inputFolderPath = process.argv.slice(2)[2];

var module_diagrams_info = [
    {
        name: "adc", 
        engine: "neato"

    },
    { 
        name: "epwm",
        engine: "dot"
    },
    { 
        name: "clb",
        engine: "dot"
    }
]

for (var module_diagram_info of module_diagrams_info)
{
    var inputFileName = module_diagram_info.name;
    var inputFileEngine = module_diagram_info.engine;

    runScript(c2000ware_root_path + '/utilities/clb_tool/clb_syscfg/dot_file_libraries/renderDotFull.js', 
        [
            c2000ware_root_path + "/utilities/clb_tool/clb_syscfg",
            outputFolderPath,
            inputFolderPath + "/" + inputFileName + ".dot",
            inputFileName,
            inputFileEngine
        ], function (err) {
            //console.log('finished running script with errors');
        }
    );

}