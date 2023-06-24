let Common   = system.getScript("/driverlib/Common.js");

var references = [
    {
        name: "codestartbranch_asm",
        path: "../device_support/${DEVICE_NAME}/common/source/${DEVICE_NAME}_codestartbranch.asm",
        alwaysInclude: false,
    },
    {
        name: "driverlib_h",
        path: "../device_support/${DEVICE_NAME}/common/include/driverlib.h",
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