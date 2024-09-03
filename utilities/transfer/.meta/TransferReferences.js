let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

var references = [
    {
        name: "TRANSFER_RING_BUFFER_C",
        path: transferCommon.getTransferSourcePath() + "/source/transfer_ringbuffer.c",
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