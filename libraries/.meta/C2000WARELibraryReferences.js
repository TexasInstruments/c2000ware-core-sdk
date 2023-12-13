let controller_data = system.getScript("/libraries/control/dcl/controller_data.js");
var references = [
        // {
        //     name: "DCL_PI_A1",
        //     path: "../libraries/control/DCL/c28/source/DCL_PI_A1.asm",
        //     alwaysInclude: false,
        // },
        // {
        //     name: "DCL_error",
        //     path: "../libraries/control/DCL/c28/source/DCL_error.c",
        //     alwaysInclude: false,
        // }
]

var controller_references = controller_data.getRefFilesArr()
references = references.concat(controller_references)

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