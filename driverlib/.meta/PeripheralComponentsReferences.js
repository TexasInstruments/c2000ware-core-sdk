let Common   = system.getScript("/driverlib/Common.js");

let codestartbranch_asm_path=""
let driverlib_h_path=""
if ((system.getProducts()[0].name.includes("C2000MCSDK")) || (system.getProducts()[0].name.includes("C2000MDPSDK")))
{
    codestartbranch_asm_path = "../c2000ware/device_support/${DEVICE_NAME}/common/source/${DEVICE_NAME}_codestartbranch.asm"
    driverlib_h_path="../c2000ware/device_support/${DEVICE_NAME}/common/include/driverlib.h"
} 
else
{ 
    codestartbranch_asm_path = "../device_support/${DEVICE_NAME}/common/source/${DEVICE_NAME}_codestartbranch.asm"
     driverlib_h_path="../device_support/${DEVICE_NAME}/common/include/driverlib.h"
}



var references = [
    {
        name: "codestartbranch_asm",
        path: codestartbranch_asm_path,
        alwaysInclude: false,
    },
    {
        name: "driverlib_h",
        path: driverlib_h_path,
        alwaysInclude: false,
    },
]


function getReferencePath(name)
{
    for (var ref of references)
    {
        if (ref.name == name)
        {
            return ref.path
        }
    }
}

var componentReferences = []
for (var ref of references)
{
    ref.path = ref.path.replace(/\$\{DEVICE_NAME\}/g, Common.getDeviceName().toLowerCase())
    componentReferences.push({
        path: ref.path,
        alwaysInclude: ref.alwaysInclude
    })
}

function appendReferences(refObjs)
{
    componentReferences = componentReferences.concat(refObjs);
}

exports = {
    references: references,
    getReferencePath : getReferencePath,
    appendReferences : appendReferences,
    componentReferences : componentReferences
}