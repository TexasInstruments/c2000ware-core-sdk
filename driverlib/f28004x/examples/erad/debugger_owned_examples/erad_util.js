importPackage(Packages.com.ti.debug.engine.scripting)
importPackage(Packages.com.ti.ccstudio.scripting.environment)
importPackage(Packages.org.w3c.dom)
importPackage(Packages.javax.xml.parsers)
importPackage(Packages.java.lang)
importPackage(Packages.java.util)
importPackage(Packages.java.io)

function getFuncAddressXML(funcName)
{
    //
    // Check for the existence of script environment variables. An error message
    // is printed if the string has not been defined in the current scripting
    // session. Note: These error messages will not trigger if the variables
    // are defined, but are set to incorrect values. It is up to the user to
    // make sure that each of these variables is set accordingly prior to
    // running the example program
    //

    print("....Looking for the XML file....");
    if (typeof PROJ_NAME == 'undefined')
    {
        print("\nERROR: Please set PROJ_NAME to the name of the" +
              " CCS project\n");
    }

    if (typeof PROJ_WKSPC_LOC == 'undefined')
    {
        print("\nERROR: Please set PROJ_WKSPC_LOC to the correct" +
              " CCS workspace path\n");
    }

    if (typeof PROJ_CONFIG == 'undefined')
    {
        print("\nERROR: Please set PROJ_CONFIG to the name of the" +
              " active configuration\n");
    }

    var xmlFileName = PROJ_WKSPC_LOC + "\\" + PROJ_NAME + "\\" + PROJ_CONFIG +
                 "\\" + PROJ_NAME + "_linkinfo.xml";

    print("....XML file: " + xmlFileName);


    var xmlFile = new File(xmlFileName);
    var dbFactory = DocumentBuilderFactory.newInstance();
    var dBuilder = dbFactory.newDocumentBuilder();
    var xmlDom = dBuilder.parse(xmlFile);
    xmlDom.getDocumentElement().normalize();
    /*
    print("Root element :" + xmlDom.getDocumentElement().getNodeName());
    */
    var nodeList = xmlDom.getElementsByTagName("object_component");
    var length = nodeList.getLength();

    print("Number of nodes: " + nodeList.getLength() + " with name: " + nodeList.item(0).getNodeName() );

    var myFuncStart, myFuncLength, myFuncEnd;

    for(var index = 0; index < length; index++)
    {

        var myName = nodeList.item(index).getElementsByTagName("name");
        /*
        print("Node " + index + ": " + myName.item(0).firstChild.nodeValue);
        */
        if( (myName.item(0).firstChild.nodeValue == ".text:" + funcName) || (myName.item(0).firstChild.nodeValue == ".TI.ramfunc:" + funcName) )
        {
            print("....Found: " + nodeList.item(0).getNodeName() + " with " + myName.item(0).getNodeName() + " and child value: " + myName.item(0).firstChild.nodeValue);
            myFuncStart = nodeList.item(index).getElementsByTagName("run_address").item(0).firstChild.nodeValue;
            myFuncLength = nodeList.item(index).getElementsByTagName("size").item(0).firstChild.nodeValue;
            myFuncEnd = parseInt(myFuncStart) + parseInt(myFuncLength) -1;
            /*
            print("....run_address: " + (myFuncStart) + "   size: " + myFuncLength + "   end: 0x" + myFuncEnd.toString(16));
            */
            break;
        }
        /*
        print("Node: " + myName.getLength() + "name: " + myName.item(0).getNodeName() + " child value: " + myName.item(0).firstChild.nodeValue);
        */
    }
    return [parseInt(myFuncStart), myFuncEnd];
}
