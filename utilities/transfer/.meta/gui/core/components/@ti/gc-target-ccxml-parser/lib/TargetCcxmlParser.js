import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { targetConfigServiceType } from '../../gc-service-target-config/lib/TargetConfigService';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';

/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
class HardwareDbException extends Error {
    constructor(msg) {
        super(msg);
        this.lineNo = 0;
        this.column = 0;
    }
    HardwareDbException(msg, lineNo, column) {
        this.message = msg;
        this.setLineNumber(lineNo);
        this.setColumnNumber(column);
    }
    setLineNumber(lineNo) {
        this.lineNo = lineNo;
    }
    getLineNumber() {
        return this.lineNo;
    }
    setColumnNumber(column) {
        this.column = column;
    }
    getColumnNumber() {
        return this.column;
    }
}
HardwareDbException.serialVersionUID = 0;

/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
class HWDB {
}
// Hardware database TAG's
HWDB.CONFIGURATIONS_TAG = 'configurations';
HWDB.CONFIGURATION_TAG = 'configuration';
HWDB.CONNECTION_TYPE_TAG = 'connectionType';
HWDB.CONNECTION_TAG = 'connection';
HWDB.PLATFORM_TAG = 'platform';
HWDB.BOARD_TAG = 'board';
HWDB.CPU_TAG = 'cpu';
HWDB.DEVICE_TAG = 'device';
HWDB.CORE_TAG = 'core';
HWDB.SUBPATH_TAG = 'subpath';
HWDB.ROUTER_TAG = 'router';
HWDB.PROCESSORS_TAG = 'processors';
HWDB.DRIVERS_TAG = 'drivers';
HWDB.DRIVER_TAG = 'driver';
HWDB.ISA_TAG = 'isa';
HWDB.PROPERTY_TAG = 'property';
HWDB.INSTANCE_TAG = 'instance';
HWDB.INCLUDE_TAG = 'include';
HWDB.CHOICE_TAG = 'choice';
HWDB.DRIVER_PROPERTIES_TAG = 'driverProperties';
HWDB.HIERARCHY_TAG = 'hierarchy';
HWDB.CURRENT_TAG = 'current';
HWDB.CHOICELIST_TAG = 'choicelist';
HWDB.INFERENCE_TAG = 'inference';
HWDB.CURRENT_CHOICE_TAG = 'cchoice';
HWDB.HIERACHY_CHOICE_TAG = 'hchoice';
HWDB.JTAG_TAG = 'jtag';
// Hardware database Attributes
HWDB.TYPE_ATTRIBUTE = 'Type';
HWDB.NAME_ATTRIBUTE = 'desc';
HWDB.PROPERTY_NAME_ATTRIBUTE = 'Name';
HWDB.DESCRIPTION_ATTRIBUTE = 'description';
HWDB.ID_ATTRIBUTE = 'id';
HWDB.ISA_ATTRIBUTE = 'isa';
HWDB.PARTNUM_ATTRIBUTE = 'partnum';
HWDB.HW_REV_ATTRIBUTE = 'HW_revision';
HWDB.PROCID_ATTRIBUTE = 'ProcID';
HWDB.DATA_FILE_PROPERTY = 'dataFile';
HWDB.INITINDEX_PROPERTY = 'initIndex';
//    public static readonly  INCLUDED_FILE_ATTRIBUTE = "instanceFile";
HWDB.SUBPATH_ATTRIBUTE = 'SubPath';
HWDB.SUBPATH_TYPE_PROPERTY = 'Type';
HWDB.SUBPATH_PORT_PROPERTY = 'Port Number';
HWDB.SUBPATH_ADDRESS = 'subpath.address';
HWDB.SUBPATH_COUNT_PROPERTY = 'subPathCount';
HWDB.BYPASS_PROPERTY = 'bypass';
HWDB.COM_PORT_PROPERTY = 'COM Port';
HWDB.BAUD_RATE_PROPERTY = 'Baud Rate';
HWDB.FILE_ATTRIBUTE = 'file';
HWDB.VALUE_ATTRIBUTE = 'Value';
HWDB.CHOICE_VALUE_ATTRIBUTE = 'value';
HWDB.INTEGER_TYPE = 'numericfield';
HWDB.NUMERIC_TYPE = 'numeric';
HWDB.STRING_TYPE = 'stringfield';
HWDB.FILE_TYPE = 'filepathfield';
HWDB.FILE_PATH_TYPE = 'FILE_PATH_EXTN';
HWDB.CHOICE_TYPE = 'choicelist';
HWDB.STRING_LIST_TYPE = 'string_list';
HWDB.HIDDEN_TYPE = 'hiddenfield';
HWDB.UART_CONNECTION_NAME = 'UARTConnection';
HWDB.NONDEBUG_ATTRIBUTE = 'nonDebug';
HWDB.HREF_ATTRIBUTE = 'href';
HWDB.XML_ATTRIBUTE = 'xml';
HWDB.XMLPATH_ATTRIBUTE = 'xmlpath';
HWDB.EXTENSIONS_ATTRIBUTE = 'Extensions';
HWDB.VER_ATTRIBUTE = 'XML_version';
HWDB.VERSION = '1.2';
HWDB.MOVABLE_ATTRIBUTE = 'CanChildNodesBeMoved';
HWDB.KEY_ATTRIBUTE = 'key';
HWDB.EXTN_ATTRIBUTE = 'extn';
HWDB.UPPER_RANGE_ATTRIBUTE = 'upper_range';
HWDB.LOWER_RANGE_ATTRIBUTE = 'lower_range';
HWDB.UPPER_BOUND_ATTRIBUTE = 'UpperBound';
HWDB.LOWER_BOUND_ATTRIBUTE = 'LowerBound';
HWDB.ADVICE_ATTRIBUTE = 'advice';
HWDB.SUMMARY_ATTRIBUTE = 'summary';
HWDB.DRIVER_TYPE_ATTRIBUTE = 'type';
HWDB.BYPASS_ROUTER_ICON = 'bypass_router';
HWDB.COMPONENT_NAME = 'uid';
HWDB.SCHEMA_FILENAME = 'setup_parser.xsd';

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
class NodeTypes {
}
NodeTypes.COMMENT_NODE = 8;
NodeTypes.TEXT_NODE = 3;
NodeTypes.ELEMENT_NODE = 1;

/**
 *  Copyright (c) 2022, 2024 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* eslint-disable @typescript-eslint/no-var-requires */
class XMLParser {
    constructor() {
        this.m_pWorkingDoc = null;
    }
    XMLParser() {
    }
    CreateStringNode(name, value) {
        // This function creates a new node that contains a string value.  Note that the value is actually
        // stored in a text node which is a child of the node returned.  If the name were "expression" and
        // the value were "foo()" this would create the following XML:
        //
        // <expression>foo()</expression>
        if (this.m_pWorkingDoc === null) {
            throw new Error('no xml document loaded');
        }
        const newNode = this.m_pWorkingDoc.createElement(name);
        const textNode = this.m_pWorkingDoc.createTextNode(value);
        newNode.appendChild(textNode);
        return newNode;
    }
    CreateIntegerNode(name, value) {
        // This function creates a new node that contains an integer value.  Note that the value is actually
        // stored in a text node which is a child of the node returned.  If the name were "line" and the
        // value were 10 this would create the following XML:
        //
        // <line>10</line>
        return this.CreateStringNode(name, `${value}`);
    }
    CreateBooleanNode(name, value) {
        // This function creates a new node that contains a boolean value
        return this.CreateIntegerNode(name, value ? 1 : 0);
    }
    CreateEntityNode(name) {
        if (this.m_pWorkingDoc === null) {
            throw new Error('no xml document loaded');
        }
        return this.m_pWorkingDoc.createElement(name);
    }
    // ---------------------------------------------------------------------------
    CreateNewDocument(docName) {
        this.ParseAndValidate(`<?xml version="1.0" encoding="UTF-8" standalone="no"?>\n<${docName}></${docName}>`, false);
        const result = this.m_pWorkingDoc?.documentElement;
        if (!result) {
            throw new Error('Unable to create a new XML Document.');
        }
        return result;
    }
    static GetName(element) {
        // This function simply returns the name of the element.  So in the following example,
        // "expression" would be returned.
        //
        // <expression>main</expression>
        return element.nodeName;
    }
    static GetStringValue(elementWithStringValue) {
        // This function returns the string value stored in the element.  In the following example,
        // the element has the string value "main".  Note that the actual value is in a text node
        // which is a child of the passed in node.
        //
        // <expression>main</expression>
        const textChild = XMLParser.GetFirstChild(elementWithStringValue);
        let str = null;
        if (textChild !== null) {
            str = textChild.nodeValue;
        }
        return str;
    }
    static GetIntegerValue(elementWithIntegerValue) {
        // This function returns the integer value stored in the element.  In the following example,
        // the element has the integer value 10.  Note that the actual value is in a text node which
        // is a child of the passed in node.
        //
        // <line>10</line>
        const textChild = XMLParser.GetFirstChild(elementWithIntegerValue);
        return textChild ? Number.parseInt(textChild.nodeValue) : 0;
    }
    static GetBooleanValue(elementWithIntegerValue) {
        // This function returns the boolean value stored in the element.  In the following example,
        // the element has the boolean value true.  Note that the actual value is in a text node which
        // is a child of the passed in node.
        //
        // <enabled>1</enabled>
        return 0 !== XMLParser.GetIntegerValue(elementWithIntegerValue);
    }
    static GetFirstChild(elementWithChild) {
        // This function returns the first child node that is not a comment
        let child = elementWithChild.firstChild;
        while (child && NodeTypes.ELEMENT_NODE !== child.nodeType) {
            child = child.nextSibling;
        }
        return child ?? null;
    }
    static GetNextSibling(elementWithSibling) {
        // This function returns the next sibling node that is not a comment
        let sibling = elementWithSibling.nextSibling;
        while (sibling && NodeTypes.ELEMENT_NODE !== sibling.nodeType) {
            sibling = sibling.nextSibling;
        }
        return sibling ?? null;
    }
    static GetLastTextNode(elementWithChild) {
        let child = elementWithChild.firstChild;
        while (child?.nextSibling) {
            child = child.nextSibling;
        }
        return child?.nodeType === NodeTypes.TEXT_NODE ? child : undefined;
    }
    static CountChildrenByName(elementWithChildren, pszNameOfChildrenToCount) {
        let child = XMLParser.GetFirstChild(elementWithChildren);
        let count = 0;
        while (child !== null) {
            if (XMLParser.GetName(child) === pszNameOfChildrenToCount) {
                count++;
            }
            child = XMLParser.GetNextSibling(child);
        }
        return count;
    }
    static FindChildByName(elementWithChildren, pszNameOfChild, n = 0) {
        let child = XMLParser.GetFirstChild(elementWithChildren);
        while (child !== null) {
            if (XMLParser.GetName(child) === pszNameOfChild) {
                if (n-- === 0) {
                    break;
                }
            }
            child = XMLParser.GetNextSibling(child);
        }
        return child;
    }
    SetAttribute(elementWithAttribute, name, value) {
        if (this.m_pWorkingDoc === null) {
            throw new Error('no xml document loaded');
        }
        const attribute = this.m_pWorkingDoc.createAttribute(name);
        attribute.value = value;
        elementWithAttribute.attributes.setNamedItem(attribute);
    }
    static GetAttributeString(elementWithAttribute, name) {
        if (elementWithAttribute === null) {
            return '';
        }
        const attributes = elementWithAttribute.attributes;
        const attribute = attributes?.getNamedItem(name);
        const str = !attribute ? '' : attribute.value;
        return str;
    }
    GetDocumentElement() {
        return this.m_pWorkingDoc?.documentElement ?? null;
    }
    async loadSchema(schemaDirectory) {
        // TODO: not supported on browser side.
    }
    ParseAndValidate(xmlText, validate) {
        this.m_pWorkingDoc = null;
        const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
        this.m_pWorkingDoc = targetConfigService.parseConfig(xmlText);
    }
    serializeXMLDocument() {
        if (this.m_pWorkingDoc) {
            const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
            return targetConfigService.serializeConfig(this.m_pWorkingDoc);
        }
        throw new Error('No xml file loaded to serialize.');
    }
}

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
function isAbsolute(path) {
    return path.indexOf(':') === 1 || path.startsWith('/');
}
function join(parent, filename) {
    if (isAbsolute(filename)) {
        return filename;
    }
    if (parent.endsWith('/')) {
        return parent + filename;
    }
    return `${parent}/${filename}`;
}
function normalize(path) {
    path = path.split('\\').join('/');
    path = path.split('/./').join('/');
    let pos = path.indexOf('/../');
    while (pos > 0) {
        const parent = path.substring(0, pos);
        const filename = path.substring(pos + '/../'.length);
        pos = parent.lastIndexOf('/');
        if (pos > 0) {
            path = parent.substring(0, pos + 1) + filename;
        }
        else {
            path = filename;
        }
        pos = path.indexOf('/../');
    }
    return path;
}
function exists(path) {
    if (path.startsWith('ccs_base/common/')) {
        const commonTargetDbPaths = ['boarddat', 'boards', 'connections', 'cpus', 'devices', 'drivers', 'Modules', 'options', 'routers'];
        const segments = path.split('/');
        // test for known bad paths.
        // for example, ccs_base/common/emulation/gel/xxxx.gel
        // or ccs_base/common/targetdb/cpus/Modules/cortex_m5.xml
        if (segments[2] !== 'targetdb' || commonTargetDbPaths.includes(segments[4])) {
            return 0;
        }
        if (commonTargetDbPaths.includes(segments[3])) {
            return 2;
        }
    }
    else if (path.startsWith('ccs_base/emulation')) {
        return 2;
    }
    return 1;
}
class Tag {
    constructor(tag, node) {
        this.m_pXmlParser = tag instanceof XMLParser ? tag : tag.m_pXmlParser;
        this.m_pNode = node;
    }
    static convertToAbsPath(fileName, curDirectory, rootDirectories) {
        if (isAbsolute(fileName)) {
            return fileName;
        }
        let relFilename = normalize(join(curDirectory, fileName));
        let score = exists(relFilename);
        for (let i = 0; i < rootDirectories.length; i++) {
            const altRelFilename = normalize(join(rootDirectories[i], fileName));
            const altScore = exists(altRelFilename);
            if (altScore > score) {
                score = altScore;
                relFilename = altRelFilename;
            }
        }
        return relFilename;
    }
    static convertToRelPath(absFileName, toDirectories) {
        let result = absFileName;
        const absFileSegments = absFileName.split('/');
        let score = 0;
        toDirectories.forEach(directory => {
            const directorySegments = normalize(directory).split('/');
            let i = 0;
            while (i < absFileSegments.length && i < directorySegments.length && absFileSegments[i] === directorySegments[i]) {
                i++;
            }
            if (i >= score) {
                const relativePath = [...new Array(directorySegments.length - i).fill('..'), ...absFileSegments.slice(i)].join('/');
                if (i > score || relativePath.length < result.length) {
                    result = relativePath;
                    score = i;
                }
            }
        });
        return result;
    }
    getFirstChild() {
        return XMLParser.GetFirstChild(this.m_pNode);
    }
    getLastTextNode() {
        return XMLParser.GetLastTextNode(this.m_pNode);
    }
    countChildrenByName(name) {
        return XMLParser.CountChildrenByName(this.m_pNode, name);
    }
    getName() {
        return XMLParser.GetName(this.m_pNode);
    }
    getParent(nameOfParent) {
        let result = this.m_pNode.parentNode ?? null;
        while (nameOfParent !== null && result !== null && XMLParser.GetName(result) !== nameOfParent) {
            result = result.parentNode ?? null;
        }
        return result;
    }
    getChildByName(name, nIndex) {
        return XMLParser.FindChildByName(this.m_pNode, name, nIndex);
    }
    getChildByID(name, id, idAttributeName = HWDB.ID_ATTRIBUTE) {
        let newChild = null;
        if (id !== null && id.length > 0) {
            newChild = this.getFirstChild();
            while (newChild !== null) {
                if ((name === null || name.localeCompare(XMLParser.GetName(newChild)) === 0)
                    && id.localeCompare(XMLParser.GetAttributeString(newChild, idAttributeName)) === 0) {
                    break;
                }
                newChild = XMLParser.GetNextSibling(newChild);
            }
        }
        return newChild;
    }
    getChildIndexByID(name, id, idAttributeName) {
        let i = -1;
        if (id !== null && id.length > 0) {
            let newChild = this.getFirstChild();
            while (newChild !== null) {
                if (name === null || name.localeCompare(XMLParser.GetName(newChild)) === 0) {
                    i++; // increment index only for tags matching "name".
                    if (id.toLowerCase().localeCompare(XMLParser.GetAttributeString(newChild, idAttributeName).toLowerCase()) === 0) {
                        return i; // fond the tag with the matching id.
                    }
                }
                newChild = XMLParser.GetNextSibling(newChild);
            }
        }
        return -1;
    }
    getAllChildrenByName(name) {
        const result = [];
        for (let i = this.countChildrenByName(name); i-- > 0;) {
            result.push(this.getChildByName(name, i));
        }
        return result;
    }
    createChild(name, id, version, insertBefore) {
        // Need to handle the case for inserting in connections
        if (!insertBefore && this.getName().localeCompare(HWDB.CONNECTION_TAG) === 0) {
            for (let i = Tag.connectionChildTagNames.length; i-- > 0;) {
                if (name.localeCompare(Tag.connectionChildTagNames[i]) === 0) {
                    break;
                }
                const nextInsertBefore = this.getChildByName(Tag.connectionChildTagNames[i], 0);
                insertBefore = (nextInsertBefore === null) ? insertBefore : nextInsertBefore;
            }
        }
        // insert before text node, if there is one, which may contain line return and indentation specific to the parent sibling or closing tag.
        if (!insertBefore) {
            insertBefore = this.getLastTextNode();
        }
        // now create the child and set some common attributes
        const child = this.m_pXmlParser.CreateEntityNode(name);
        if (id !== null)
            this.m_pXmlParser.SetAttribute(child, HWDB.ID_ATTRIBUTE, id);
        if (version !== null)
            this.m_pXmlParser.SetAttribute(child, HWDB.VER_ATTRIBUTE, version);
        this.m_pNode.insertBefore(child, insertBefore);
        return child;
    }
    getProperty(name) {
        const n = XMLParser.CountChildrenByName(this.m_pNode, HWDB.PROPERTY_TAG);
        for (let i = 0; i < n; i++) {
            const child = XMLParser.FindChildByName(this.m_pNode, HWDB.PROPERTY_TAG, i);
            if (child && (XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE).localeCompare(name) === 0
                || XMLParser.GetAttributeString(child, HWDB.PROPERTY_NAME_ATTRIBUTE).localeCompare(name) === 0)) {
                return child;
            }
        }
        return null;
    }
    getPropertyInteger(name, defaultValue) {
        let value = defaultValue;
        const child = this.getProperty(name);
        if (child !== null) {
            try {
                const sValue = XMLParser.GetAttributeString(child, HWDB.VALUE_ATTRIBUTE);
                value = sValue.startsWith('0x') ?
                    Number.parseInt(sValue.substring(2), 16) :
                    Number.parseInt(sValue);
            }
            catch (e) {
                value = 0;
            }
        }
        return value;
    }
    setPropertyInteger(name, value, defaultValue) {
        if (value !== defaultValue) {
            this.setProperty(name, HWDB.INTEGER_TYPE, value > 256 ? `0x${value.toString(16)}` : value.toString(), null);
            return true;
        }
        return false;
    }
    getPropertyString(name, defaultValue) {
        return this.getPropertyValue(name, HWDB.STRING_TYPE, defaultValue);
    }
    setPropertyString(name, value, defaultValue) {
        return this.setProperty(name, HWDB.STRING_TYPE, value, defaultValue);
    }
    getPropertyFile(name, defaultValue) {
        return this.getPropertyValue(name, HWDB.FILE_TYPE, defaultValue);
    }
    setPropertyFile(name, value, defaultValue) {
        return this.setProperty(name, HWDB.FILE_TYPE, value, defaultValue);
    }
    getPropertyValue(name, type, defaultValue) {
        let value = defaultValue;
        const child = this.getProperty(name);
        if (child !== null) {
            value = XMLParser.GetAttributeString(child, HWDB.VALUE_ATTRIBUTE);
        }
        return value;
    }
    setProperty(name, type, value, defaultValue) {
        // remove leading white space from value
        value = value.trim();
        // compare to default value
        if (defaultValue === null || value !== defaultValue) {
            // find the property tag
            let child = this.getProperty(name);
            if (child === null) {
                // if not found, create a new one
                child = this.m_pXmlParser.CreateEntityNode(HWDB.PROPERTY_TAG);
                this.m_pNode.appendChild(child);
                this.m_pXmlParser.SetAttribute(child, HWDB.ID_ATTRIBUTE, name);
                this.m_pXmlParser.SetAttribute(child, HWDB.TYPE_ATTRIBUTE, type);
            }
            // set the attribute on the property tag that was found or created.
            this.m_pXmlParser.SetAttribute(child, HWDB.VALUE_ATTRIBUTE, value);
            return true;
        }
        return false;
    }
    getAttribute(name) {
        return this.getChildAttribute(null, name);
    }
    setAttributeOf(node, attrName, attrValue) {
        this.m_pXmlParser.SetAttribute(node, attrName, attrValue);
    }
    setAttribute(name, value) {
        this.setChildAttribute(null, name, value);
    }
    getChildAttribute(childName, attrName) {
        let value = '';
        const child = (childName === null) ? this.m_pNode : XMLParser.FindChildByName(this.m_pNode, childName);
        if (child !== null) {
            value = XMLParser.GetAttributeString(child, attrName);
        }
        return value;
    }
    setChildAttribute(childName, attrName, value) {
        if (value !== null) {
            let child = (childName === null) ? this.m_pNode : XMLParser.FindChildByName(this.m_pNode, childName);
            if (child === null) {
                if (value.length > 1 || (value.length === 1 && value.charAt(0) !== ' ')) {
                    // don't bother creating child just to add a blank attribute.
                    return;
                }
                child = this.m_pXmlParser.CreateEntityNode(childName);
                this.m_pNode.appendChild(child);
            }
            this.m_pXmlParser.SetAttribute(child, attrName, value);
        }
    }
    getAttributeInteger(attrName, defaultValue = 0) {
        try {
            const attrValue = this.getAttribute(attrName);
            if (attrValue.length === 0) {
                return defaultValue;
            }
            if (attrValue.startsWith('0x')) {
                // hex encoded
                return Number.parseInt(attrValue.substring(2), 16);
            }
            // decimal encoded
            return Number.parseInt(attrValue);
        }
        catch (e) {
            return 0;
        }
    }
    setAttributeInteger(attrName, nValue) {
        this.setAttribute(attrName, nValue > 256 ? '0x' + nValue.toString(16) : nValue.toString(nValue));
    }
    getPropertyAttribute(name, attrName, defaultValue) {
        let value = defaultValue;
        const property = this.getProperty(name);
        if (property !== null) {
            value = XMLParser.GetAttributeString(property, attrName);
        }
        return value;
    }
    setPropertyAttribute(name, attrName, value, defaultValue) {
        if (value.localeCompare(defaultValue) !== 0) {
            let property = this.getProperty(name);
            if (property === null) {
                // create property
                property = this.m_pXmlParser.CreateEntityNode(HWDB.PROPERTY_TAG);
                this.m_pNode.appendChild(property);
                this.m_pXmlParser.SetAttribute(property, HWDB.ID_ATTRIBUTE, name);
            }
            this.m_pXmlParser.SetAttribute(property, attrName, value);
            return true;
        }
        return false;
    }
    serializeXMLDocument() {
        if (this.m_pXmlParser === null) {
            throw new Error('No xml document loaded to serialize.');
        }
        return this.m_pXmlParser.serializeXMLDocument();
    }
    toString() {
        return `<${this.getName()} ${this.m_pNode.attributes?.toString() ?? ''}>`;
    }
    getNode() {
        return this.m_pNode;
    }
    copyAttribute(from, attrName, curDirectory = null, rootDirectories = null) {
        const attributes = from.m_pNode.attributes;
        const attribute = attributes?.getNamedItem(attrName);
        if (attribute) {
            let attrValue = attribute.value;
            if (curDirectory !== null && rootDirectories !== null) {
                if (attrName.localeCompare(HWDB.FILE_ATTRIBUTE) === 0) {
                    attrValue = Tag.convertToAbsPath(attrValue, curDirectory, rootDirectories);
                }
                else if (attrName.localeCompare(HWDB.VALUE_ATTRIBUTE) === 0) {
                    const type = from.getAttribute(HWDB.TYPE_ATTRIBUTE);
                    if (type !== null && type.localeCompare(HWDB.FILE_TYPE) === 0) {
                        attrValue = Tag.convertToAbsPath(attrValue, curDirectory, rootDirectories);
                    }
                }
            }
            if (attrValue === null || attrValue === undefined) {
                attrValue = '';
            }
            this.m_pXmlParser.SetAttribute(this.m_pNode, attrName, attrValue);
        }
    }
}
Tag.connectionChildTagNames = [
    HWDB.INCLUDE_TAG,
    HWDB.INSTANCE_TAG,
    HWDB.CONNECTION_TYPE_TAG,
    HWDB.PROPERTY_TAG,
    HWDB.DRIVERS_TAG,
    HWDB.PLATFORM_TAG
];

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* eslint-disable @typescript-eslint/no-var-requires */
function getParent(fileName) {
    if (GcUtils.isNodeJS) {
        const path = require('path');
        return path.dirname(fileName);
    }
    return fileName.substring(0, fileName.lastIndexOf('/'));
}
function getFileName(fileName) {
    if (GcUtils.isNodeJS) {
        const path = require('path');
        return path.basename(fileName);
    }
    return fileName.substring(fileName.lastIndexOf('/') + 1);
}
class HardwareDatabaseReader {
    constructor() {
        this.tagNames = new Array();
        this.attributeNames = new Array();
        this.singletonTagNames = new Array();
        this.singletonTagNames.push(HWDB.DRIVER_PROPERTIES_TAG);
        this.singletonTagNames.push(HWDB.JTAG_TAG);
        this.singletonTagNames.push(HWDB.DRIVER_TAG);
        this.singletonTagNames.push(HWDB.HIERARCHY_TAG);
        this.singletonTagNames.push(HWDB.CURRENT_TAG);
    }
    addAttributesToFilter(attributeNames) {
        for (let i = attributeNames.length; i-- > 0;) {
            this.attributeNames.push(attributeNames[i]);
        }
    }
    addTagsToFilter(tagNames) {
        for (let i = tagNames.length; i-- > 0;) {
            this.tagNames.push(tagNames[i]);
        }
    }
    static newConfig(createConfigurationTag = true) {
        // create parser
        const xmlParser = new XMLParser();
        let root = xmlParser.CreateNewDocument(HWDB.CONFIGURATIONS_TAG);
        xmlParser.SetAttribute(root, HWDB.VER_ATTRIBUTE, HWDB.VERSION);
        xmlParser.SetAttribute(root, HWDB.ID_ATTRIBUTE, 'configurations_0');
        if (createConfigurationTag) {
            const configuration = xmlParser.CreateEntityNode(HWDB.CONFIGURATION_TAG);
            xmlParser.SetAttribute(configuration, HWDB.VER_ATTRIBUTE, HWDB.VERSION);
            xmlParser.SetAttribute(configuration, HWDB.ID_ATTRIBUTE, 'configuration_0');
            root.appendChild(configuration);
            root = configuration;
        }
        return new Tag(xmlParser, root);
    }
    async loadFlatConfig(fileName, rootDirectories, schemaDirectory) {
        const root = await this.loadConfig(fileName, rootDirectories, schemaDirectory);
        return await this.convertToFlatFile(root, fileName, rootDirectories);
    }
    async loadConfig(filename, rootDirectories, schemaDirectory) {
        let xmlContents;
        if (filename.startsWith('ccs_base/') || filename.startsWith('ccs_base\\')) {
            const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
            xmlContents = await targetConfigService.getFile(filename);
        }
        else {
            xmlContents = await GcFiles.readTextFile(filename);
        }
        return await this.parseConfig(xmlContents, rootDirectories, schemaDirectory);
    }
    async parseConfig(xmlFile, rootDirectories, schemaDirectory) {
        // create parser
        const xmlParser = new XMLParser();
        if (schemaDirectory) {
            await xmlParser.loadSchema(schemaDirectory);
        }
        xmlParser.ParseAndValidate(xmlFile, schemaDirectory !== null);
        // read boards
        const rootNode = xmlParser.GetDocumentElement();
        if (rootNode === null) {
            throw new HardwareDbException('XML configuration file has no root node\n');
        }
        return new Tag(xmlParser, rootNode);
    }
    async convertToFlatFile(root, fileName, rootDirectories, isCancelled) {
        // create a flat file, by copying everything of interest from include and instance tags.
        const xmlFlatParser = new XMLParser();
        const newRoot = xmlFlatParser.CreateNewDocument(root.getName());
        const result = new Tag(xmlFlatParser, newRoot);
        await this.copyNode(root, result, getParent(fileName), rootDirectories, true, true, isCancelled);
        return result;
    }
    static isCompatibleISA(name1, name2) {
        const length = Math.min(name1.length, name2.length);
        name1 = name1.toLowerCase();
        name2 = name2.toLowerCase();
        for (let i = 0; i < length; i++) {
            const ch1 = name1.charAt(i);
            const ch2 = name2.charAt(i);
            if (ch1 === '*' || ch2 === '*')
                return true;
            //            if (ch1 == 'X' || ch2 == 'X'  || ch1 == ch2)
            if (ch1 === ch2)
                continue;
            return false;
        }
        return name1.length === name2.length;
    }
    static getISA(connection, id) {
        const driver = this.getDriver(connection, id);
        return driver === null ? null : (driver.parentNode ?? null);
    }
    static getISATag(processor) {
        const driver = this.getDriverFrom(processor);
        const parent = driver?.getParent(null);
        return (!driver || !parent) ? null : new Tag(driver, parent);
    }
    static getDriver(connection, id) {
        const drivers = connection.getChildByName(HWDB.DRIVERS_TAG, 0);
        if (drivers === null) {
            throw new HardwareDbException('XML configuration file has no drivers\n');
        }
        const sConnectionType = connection.getChildAttribute(HWDB.CONNECTION_TYPE_TAG, HWDB.TYPE_ATTRIBUTE);
        let isaChild = XMLParser.GetFirstChild(drivers);
        let driver = null;
        let found = false;
        for (; isaChild !== null; isaChild = isaChild.nextSibling ?? null) {
            if (XMLParser.GetName(isaChild) === HWDB.ISA_TAG) {
                const isaNode = new Tag(connection, isaChild);
                const nDrivers = isaNode.countChildrenByName(HWDB.DRIVER_TAG);
                for (let i = 0; i < nDrivers; i++) {
                    driver = isaNode.getChildByName(HWDB.DRIVER_TAG, i);
                    if (driver !== null) {
                        const driverNode = new Tag(isaNode, driver);
                        const nConnectionTypes = driverNode.countChildrenByName(HWDB.CONNECTION_TYPE_TAG);
                        let validConnectionType = true; // if no connection type found, assume all connections supported.
                        for (let iConnectionType = 0; iConnectionType < nConnectionTypes; iConnectionType++) {
                            validConnectionType = false;
                            const connectionTypeNode = new Tag(driverNode, driverNode.getChildByName(HWDB.CONNECTION_TYPE_TAG, iConnectionType));
                            const sDriverConnectionType = connectionTypeNode.getAttribute(HWDB.TYPE_ATTRIBUTE);
                            if (sDriverConnectionType.length > 0 && sDriverConnectionType.localeCompare(sConnectionType) === 0) {
                                validConnectionType = true;
                                break;
                            }
                        }
                        if (!validConnectionType) {
                            continue; // skip to next, driver or next ISA
                        }
                    }
                    // connectionType is either valid or missing, so check for ISA match next
                    let procID = XMLParser.GetAttributeString(isaChild, HWDB.ID_ATTRIBUTE);
                    if (procID === null || procID.length === 0) {
                        procID = XMLParser.GetAttributeString(isaChild, HWDB.TYPE_ATTRIBUTE);
                    }
                    if (procID !== null && this.isCompatibleISA(procID, id))
                        found = true; // exit both loops (see break below)
                    break; // exit loop no point in looking at other drivers if ISA doesn't match.
                }
                if (found)
                    break; // exit loop if found.
            }
        }
        return found ? driver : null;
    }
    static getDriverFrom(processor) {
        const connection = processor.getParent(HWDB.CONNECTION_TAG);
        if (connection === null) {
            return null;
        }
        else {
            const conn = new Tag(processor, connection);
            const isa = this.getDriver(conn, processor.getAttribute(HWDB.ISA_ATTRIBUTE));
            if (isa !== null) {
                return new Tag(processor, isa);
            }
        }
        return null;
    }
    copyAttributes(from, to, curDirectory, rootDirectories) {
        for (let i = 0; i < this.attributeNames.length; i++) {
            const attr = this.attributeNames[i];
            to.copyAttribute(from, attr, curDirectory, rootDirectories);
        }
    }
    async copyNode(from, to, curDirectory, rootDirectories, topLevelNode, topLevelChildren, isCancelled) {
        // copy all attributes, we're interested in
        this.copyAttributes(from, to, curDirectory, rootDirectories);
        if (!topLevelNode) {
            to.setAttribute(HWDB.MOVABLE_ATTRIBUTE, 'no');
        }
        // copy children
        let child = from.getFirstChild();
        while (child !== null && !isCancelled?.()) {
            let childNode;
            let tag = XMLParser.GetName(child);
            if (tag.localeCompare(HWDB.PROCESSORS_TAG) === 0) {
                // go in one level and skip the remaining children at this level.
                child = child.firstChild ?? null;
                continue;
            }
            let id = XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE);
            if ((id === null || id.length === 0) && tag.localeCompare(HWDB.PROPERTY_TAG) === 0) {
                id = XMLParser.GetAttributeString(child, 'Name');
            }
            let parentFolder = null;
            if (tag.localeCompare(HWDB.INSTANCE_TAG) === 0 || tag.localeCompare(HWDB.INCLUDE_TAG) === 0) {
                let fileName = null;
                let href = null;
                // get filename of instance
                href = XMLParser.GetAttributeString(child, HWDB.HREF_ATTRIBUTE);
                fileName = Tag.convertToAbsPath(href, curDirectory, rootDirectories);
                if (fileName.startsWith('ccs_base/common/targetdb/Modules/') || from.getName() === HWDB.CPU_TAG) {
                    // skip Module includes, register includes
                    child = XMLParser.GetNextSibling(child);
                    continue;
                }
                try {
                    childNode = await this.loadConfig(fileName, rootDirectories, null);
                }
                catch (e) {
                    try {
                        const fileName2 = Tag.convertToAbsPath(href, rootDirectories[0], [curDirectory]);
                        if (fileName === fileName2) {
                            throw e; // will generate the same error
                        }
                        childNode = await this.loadConfig(fileName2, rootDirectories, null);
                        fileName = fileName2; // found it.
                    }
                    catch (ignore2ndError) {
                        const errorPreamble = 'Trouble parsing include file';
                        if ((e.message || e.toString()).indexOf(errorPreamble) === 0) {
                            // already prepended this error message once
                            throw e;
                        }
                        throw new HardwareDbException(errorPreamble + ` "${fileName}"<br>${e.message || e.toString()} `);
                    }
                }
                const includeTag = new Tag(from, child);
                if (tag.localeCompare(HWDB.INCLUDE_TAG) === 0) {
                    id = childNode.getAttribute(HWDB.ID_ATTRIBUTE);
                    includeTag.setAttribute(HWDB.ID_ATTRIBUTE, id);
                }
                // get type of node
                tag = childNode.getName();
                const componentName = childNode.getAttribute(HWDB.NAME_ATTRIBUTE) || childNode.getAttribute(HWDB.ID_ATTRIBUTE);
                if (componentName) {
                    childNode.setAttribute(HWDB.COMPONENT_NAME, componentName);
                }
                // copy all attributes from instance
                parentFolder = getParent(fileName);
                this.copyAttributes(includeTag, childNode, parentFolder, rootDirectories);
            }
            else {
                childNode = new Tag(from, child);
            }
            // only process tags we care about
            for (let i = this.tagNames.length; i-- > 0;) {
                if (tag.localeCompare(this.tagNames[i]) === 0) {
                    // determine attribute to search on
                    let identifier = id;
                    let idAttribute = HWDB.ID_ATTRIBUTE;
                    if (childNode.getName().localeCompare(HWDB.CHOICE_TAG) === 0) {
                        idAttribute = HWDB.PROPERTY_NAME_ATTRIBUTE;
                        identifier = childNode.getAttribute(idAttribute);
                        if (identifier === null || identifier.length === 0) {
                            idAttribute = HWDB.CHOICE_VALUE_ATTRIBUTE;
                            identifier = childNode.getAttribute(idAttribute);
                        }
                    }
                    else if (childNode.getName().localeCompare(HWDB.CURRENT_CHOICE_TAG) === 0) {
                        idAttribute = HWDB.KEY_ATTRIBUTE;
                        identifier = childNode.getAttribute(idAttribute);
                    }
                    // find child
                    let newChild = null;
                    if (identifier !== null && identifier.length > 0) {
                        newChild = to.getFirstChild();
                        while (newChild !== null) {
                            if (tag.localeCompare(XMLParser.GetName(newChild)) === 0
                                && identifier.localeCompare(XMLParser.GetAttributeString(newChild, idAttribute)) === 0) {
                                break;
                            }
                            newChild = XMLParser.GetNextSibling(newChild);
                        }
                    }
                    else {
                        for (let j = this.singletonTagNames.length; j-- > 0;) {
                            if (tag.localeCompare(this.singletonTagNames[j]) === 0) {
                                newChild = to.getChildByName(tag, 0);
                                break;
                            }
                        }
                    }
                    if (newChild === null) {
                        // create child
                        newChild = to.createChild(tag, id, null);
                    }
                    // recursively copy children
                    const newChildNode = new Tag(to, newChild);
                    await this.copyNode(childNode, newChildNode, parentFolder === null ? curDirectory : parentFolder, rootDirectories, topLevelChildren, parentFolder === null ? topLevelChildren : false);
                    if (tag.localeCompare(HWDB.ISA_TAG) === 0) {
                        // copy driver properties under the isa tag so they don't get merged with all other isas.
                        const driverPropertiesNode = from.getChildByName(HWDB.DRIVER_PROPERTIES_TAG, 0);
                        if (driverPropertiesNode !== null && newChildNode.getChildByName(HWDB.DRIVER_PROPERTIES_TAG, 0) === null) {
                            // only copy properties if they do not already exist
                            const driverProperties = new Tag(from, driverPropertiesNode);
                            const isaDriverProperties = new Tag(newChildNode, newChildNode.createChild(HWDB.DRIVER_PROPERTIES_TAG, null, null));
                            await this.copyNode(driverProperties, isaDriverProperties, curDirectory, rootDirectories, topLevelChildren, topLevelChildren);
                        }
                    }
                    break;
                }
            }
            child = XMLParser.GetNextSibling(child);
        }
    }
    static includeFile(atNode, xmlFileToInclude, id, name, insertBefore) {
        const child = new Tag(atNode, atNode.createChild(HWDB.INSTANCE_TAG, id, HWDB.VERSION, insertBefore));
        const directory = getParent(xmlFileToInclude);
        child.setAttribute(HWDB.XMLPATH_ATTRIBUTE, (directory === null || directory.length === 0) ? '.' : directory.replace('\\', '/'));
        child.setAttribute(HWDB.XML_ATTRIBUTE, getFileName(xmlFileToInclude));
        child.setAttribute(HWDB.HREF_ATTRIBUTE, xmlFileToInclude.replace('\\', '/'));
        if (name !== null) {
            child.setAttribute(HWDB.NAME_ATTRIBUTE, name);
        }
    }
    async createFlatNodeFromFile(parent, fileName, id, name, rootDirectories, insertBefore) {
        const includedRootNode = await this.loadFlatConfig(fileName, rootDirectories, null);
        // see if a node already exists and needs to be merged.
        let newChild = parent.getChildByID(includedRootNode.getName(), id);
        if (newChild === null) {
            newChild = parent.createChild(includedRootNode.getName(), null, null, insertBefore);
        }
        const newChildTag = new Tag(parent, newChild);
        const componentName = includedRootNode.getAttribute(HWDB.NAME_ATTRIBUTE) || includedRootNode.getAttribute(HWDB.ID_ATTRIBUTE);
        if (componentName) {
            newChildTag.setAttribute(HWDB.COMPONENT_NAME, componentName);
        }
        await this.copyNode(includedRootNode, newChildTag, getParent(fileName), rootDirectories, true, false);
        newChildTag.setAttribute(HWDB.ID_ATTRIBUTE, id);
        newChildTag.setAttribute(HWDB.VER_ATTRIBUTE, HWDB.VERSION);
        if (name !== null) {
            newChildTag.setAttribute(HWDB.NAME_ATTRIBUTE, name);
        }
        return newChildTag;
    }
}

/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
class StringBuilder {
    constructor(initialValue) {
        this.str = initialValue ?? '';
    }
    append(text) {
        this.str += text;
    }
    toString() {
        return this.str;
    }
    get length() {
        return this.str.length;
    }
}

/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* eslint-disable no-console */
var DriverType;
(function (DriverType) {
    DriverType[DriverType["EMU"] = 0] = "EMU";
    DriverType[DriverType["SIM"] = 1] = "SIM";
    DriverType[DriverType["DSK"] = 2] = "DSK";
    DriverType[DriverType["MOD"] = 3] = "MOD";
    DriverType[DriverType["NONDEBUG"] = 4] = "NONDEBUG";
    DriverType[DriverType["ROUTER"] = 5] = "ROUTER";
})(DriverType || (DriverType = {}));
class ProcessorID {
    constructor(procID = 0) {
        this.procID = procID;
    }
    getFamily() {
        return (this.procID >> ProcessorID.SHIFT_FAMILY) & ProcessorID.MASK_FAMILY;
    }
    setFamily(family) {
        this.procID = (this.procID & ~(ProcessorID.MASK_FAMILY << ProcessorID.SHIFT_FAMILY)) | ((family & ProcessorID.MASK_FAMILY) << ProcessorID.SHIFT_FAMILY);
    }
    getSubFamily() {
        return (this.procID >> ProcessorID.SHIFT_SUBFAMILY) & ProcessorID.MASK_SUBFAMILY;
    }
    setSubFamily(subFamily) {
        this.procID = (this.procID & ~(ProcessorID.MASK_SUBFAMILY << ProcessorID.SHIFT_SUBFAMILY)) | ((subFamily & ProcessorID.MASK_SUBFAMILY) << ProcessorID.SHIFT_SUBFAMILY);
    }
    getRevision() {
        return (this.procID >> ProcessorID.SHIFT_REV) & ProcessorID.MASK_REV;
    }
    setRevision(revision) {
        this.procID = (this.procID & ~(ProcessorID.MASK_REV << ProcessorID.SHIFT_REV)) | ((revision & ProcessorID.MASK_REV) << ProcessorID.SHIFT_REV);
    }
    getType() {
        return (this.procID >> ProcessorID.SHIFT_TYPE) & ProcessorID.MASK_TYPE;
    }
    setType(type) {
        this.procID = (this.procID & ~(ProcessorID.MASK_TYPE << ProcessorID.SHIFT_TYPE)) | ((type & ProcessorID.MASK_TYPE) << ProcessorID.SHIFT_TYPE);
    }
    getProcessorID() {
        return this.procID;
    }
    setProcessorID(newProcID) {
        this.procID = newProcID;
    }
    isNonDebug() {
        return (this.getType() === DriverType.NONDEBUG);
    }
    isRouter() {
        return (this.getType() === DriverType.ROUTER);
    }
    toString() {
        let cstrOut = '';
        // process the family
        const family = this.getFamily();
        let subFamily = this.getSubFamily();
        if (family === 240) {
            cstrOut += `${ProcessorID.ICEPick}A${subFamily}`;
        }
        else if (family === 100) { // DRP Script processors have the family 100
            cstrOut += `${ProcessorID.DRP_SCRIPT}${subFamily}`;
        }
        else if (family === 430) { // MSP430
            cstrOut += ProcessorID.MSP430;
        }
        else if (family === 470 && subFamily === 0) {
            cstrOut += ProcessorID.ARM;
        }
        else if (family === 470 && subFamily <= 3) { // arm devices
            cstrOut += `${ProcessorID.ARM}${subFamily * 2 + 5}`;
        }
        else if (family === 470 && subFamily === 13) {
            cstrOut += `${ProcessorID.CORTEX}R`;
        }
        else if (family === 470 && (subFamily === 10 || subFamily === 14 || subFamily === 0x33)) { // cortexM devices
            cstrOut += `${ProcessorID.CORTEX}M`;
        }
        else if (family === 470 && [0x5, 0x7, 0xC, 0x9, 0x12, 0x15, 0x17, 0x32, 0x35, 0x53, 0x57, 0x72, 0x73].includes(subFamily)) { // cortexA devices
            cstrOut += `${ProcessorID.CORTEX}A`;
        }
        else if (family === 700) {
            cstrOut += ProcessorID.ARP32;
        }
        else {
            cstrOut += `${ProcessorID.TMS}${family}`;
            // TMS470R (RISC), TMS370P (MCU), and TMS320C (DSP)
            cstrOut += `${family === 470 ? 'R' : family === 370 ? 'P' : 'C'}`;
            // hide 56xx and 29xx under 55xx and 28xx
            if (family === 320) {
                if (subFamily === 0x56)
                    subFamily = 0x55;
                if (subFamily === 0x29)
                    subFamily = 0x28;
            }
            // process the sub-family
            let bFoundNonZero = false;
            for (let i = 2; i >= 0; i--) {
                // grab digit at hex position i
                const nDigit = (subFamily >> (i * 4)) & 0xF;
                // display all non-leading zeros and leading zeros for MCU's
                if (nDigit === 0) {
                    if (bFoundNonZero || family === 370)
                        cstrOut += '0';
                }
                else if (nDigit >= 0x1 && nDigit <= 0x9) {
                    cstrOut += '0' + nDigit;
                    bFoundNonZero = true;
                }
                else if (nDigit === 0xF) {
                    cstrOut += 'X';
                    bFoundNonZero = true;
                }
                else {
                    cstrOut += 'A' + (nDigit - 0xA);
                    bFoundNonZero = true;
                }
            }
            // process the revision
            const revision = this.getRevision();
            if (subFamily >= 0x001 && subFamily <= 0x009) { // single-digit revision
                if (revision >= 0 && revision <= 9)
                    cstrOut += '0' + revision;
                else
                    cstrOut += 'X';
            }
            else { // two-digit revision
                if (revision < 10)
                    cstrOut += '0';
                if (revision < 100) // ##
                    cstrOut += revision;
                else if (revision < 110) // #x
                    cstrOut += (revision - 100) + 'X';
                else if (revision < 120) // x#
                    cstrOut += 'X' + (revision - 110);
                else // xx
                    cstrOut += 'XX';
            }
        }
        return cstrOut.toString();
    }
    toStringProjectType() {
        const saveProcId = this.procID;
        let mask;
        const family = this.getFamily();
        if (family === 240) {
            return 'ICEPick';
        }
        else if (family === 100) {
            return 'DRP_SCRIPT';
        }
        else if (family === 192) {
            const result = toString();
            if (result === 'TMS192C2026')
                return 'PRU';
            else if (result === 'TMS192C2006' || result === 'TMS192C2007')
                return 'CLA';
            else
                mask = 0;
        }
        else if (family === 320) {
            const subFamily = this.getSubFamily();
            if (subFamily < 0x50 || subFamily >= 0x5F) {
                // Except for TMS320C5000, the project type is the family and subFamily with last digit changed to 0.
                mask = 0xF << ProcessorID.SHIFT_SUBFAMILY | ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
            }
            else {
                // Use both the family and subFamily to distinguish between C5400 and C5500 projects.
                mask = ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
            }
        }
        else {
            // for ARM or MSP430, the family is used for the project type
            mask = ProcessorID.MASK_SUBFAMILY << ProcessorID.SHIFT_SUBFAMILY | ProcessorID.MASK_REV << ProcessorID.SHIFT_REV;
        }
        this.procID = this.procID & (~mask);
        const result = toString();
        this.procID = saveProcId;
        if (result.startsWith('TMS320')) {
            return result.substring(6);
        }
        return result;
    }
    parse(processorName) {
        this.procID = 0;
        if (processorName.startsWith(ProcessorID.ICEPick)) {
            this.setFamily(240);
            this.setSubFamily(processorName.charCodeAt(ProcessorID.ICEPick.length) - 'A'.charCodeAt(0));
        }
        else if (processorName.startsWith(ProcessorID.DRP_SCRIPT)) {
            this.setFamily(100);
            this.setSubFamily(Number.parseInt(processorName.substring(ProcessorID.DRP_SCRIPT.length), 10));
        }
        else if (processorName.startsWith(ProcessorID.MSP430)) {
            this.setFamily(430);
        }
        else if (processorName.startsWith(ProcessorID.ARM)) {
            this.setFamily(470);
            const subFamily = Number.parseInt(processorName.substring(ProcessorID.ARM.length), 10);
            this.setSubFamily((subFamily - 5) / 2);
        }
        else if (processorName.startsWith(ProcessorID.CORTEX)) {
            this.setFamily(470);
            const subFamilyText = processorName.substring(ProcessorID.CORTEX.length).trim();
            if (subFamilyText.startsWith('A'))
                this.setSubFamily(12);
            else if (subFamilyText.startsWith('R'))
                this.setSubFamily(13);
            else if (subFamilyText.startsWith('M'))
                this.setSubFamily(14);
            else
                this.setSubFamily(0);
        }
        else if (processorName.startsWith(ProcessorID.ARP32)) {
            this.setFamily(700);
            this.setSubFamily(0x40);
        }
        else if (processorName.startsWith(ProcessorID.TMS)) {
            if (processorName.startsWith(ProcessorID.TMS470R)) {
                this.setFamily(470);
                processorName = processorName.substring(ProcessorID.TMS470R.length);
            }
            else if (processorName.startsWith(ProcessorID.TMS370P)) {
                this.setFamily(370);
                processorName = processorName.substring(ProcessorID.TMS370P.length);
            }
            else if (processorName.startsWith(ProcessorID.TMS320C)) {
                this.setFamily(320);
                processorName = processorName.substring(ProcessorID.TMS320C.length);
            }
            else {
                this.setFamily(Number.parseInt(processorName.substring(ProcessorID.TMS.length, ProcessorID.TMS.length + 3)));
                processorName = processorName.substring(ProcessorID.TMS.length + 3);
            }
            // read sub family and revision as hexadecimal with 'x' representing 'F'.
            processorName = processorName.toUpperCase();
            let revision = Number.parseInt(processorName.split('X').join('F'), 16);
            // now try to figure out where the division is  between sub family and revision
            if (revision <= 0x9F) {
                // single digit sub-family and revision.
                this.setSubFamily(revision >> 4);
                this.setRevision(revision & 0xF);
            }
            else { // two digit revision
                this.setSubFamily(revision >> 8);
                revision = revision & 0xFF;
                if (revision === 0xFF) {
                    this.setRevision(revision);
                }
                else if (revision >= 0xF0) {
                    this.setRevision(110 + revision - 0xF0);
                }
                else if ((revision & 0xF) === 0xF) {
                    this.setRevision(100 + (revision >> 4));
                }
                else {
                    // reinterpret hex as decimal
                    this.setRevision((revision >> 4) * 10 + (revision & 0xF));
                }
            }
        }
    }
    static test() {
        let passed = true;
        const family = [240, 100, 470, 370, 320, 430, 700];
        const subFamily = [1, 2, 3, 4, 5, 7, 9, 10, 11, 0x15, 0x54, 0x55, 0x56, 0x62, 0x64, 0x27, 0x24, 0x60, 0x50, 0x52, 0x6F, 0x5f, 0x2f];
        const revision = [0, 1, 2, 9, 10, 11, 99, 100, 101, 109, 110, 111, 119, 120, 121, 256];
        const procID = new ProcessorID();
        for (let i = family.length; i-- > 0;) {
            for (let j = subFamily.length; j-- > 0;) {
                for (let k = revision.length; k-- > 0;) {
                    procID.setFamily(family[i]);
                    procID.setSubFamily(subFamily[j]);
                    procID.setRevision(revision[k]);
                    const name = procID.toString();
                    procID.parse(name);
                    const nameAgain = procID.toString();
                    if (name.localeCompare(nameAgain) !== 0) {
                        const errorMessage = `Test Case Failed: family=${family[i]}, subFamily=${subFamily[j]}, revision=${revision[k]} name should be ${name} but was ${nameAgain}`;
                        console.error(errorMessage);
                        passed = false;
                    }
                    const familyGroup = procID.toStringProjectType();
                    let shouldBe = '';
                    if (family[i] === 470) {
                        shouldBe = 'ARM';
                    }
                    else if (family[i] === 320 && subFamily[j] > 15) {
                        if (subFamily[j] >= 0x50 && subFamily[j] < 0x5F) {
                            if (subFamily[j] !== 0x56) {
                                shouldBe = `C${subFamily[j].toString(16)}00`;
                            }
                            else {
                                shouldBe = 'C5500';
                            }
                        }
                        else {
                            shouldBe = `C${subFamily[j] >>> 4}000`;
                        }
                    }
                    else if (family[i] === 430) {
                        shouldBe = 'MSP430';
                    }
                    else if (family[i] === 240) {
                        shouldBe = 'ICEPick';
                    }
                    else if (family[i] === 100) {
                        shouldBe = 'DRP_SCRIPT';
                    }
                    if (shouldBe.length > 0 && shouldBe.localeCompare(familyGroup) !== 0) {
                        const errorMessage = `Test Case Failed: family=${family[i]}, subFamily=${subFamily[j]}, revision=${revision[k]} family group should be ${shouldBe} but was ${familyGroup}`;
                        console.error(errorMessage);
                        passed = false;
                    }
                }
            }
        }
        if (passed) {
            console.log('Test Cases Passed');
        }
    }
}
ProcessorID.BITS_TYPE = 3;
ProcessorID.BITS_REV = 7;
ProcessorID.BITS_SUBFAMILY = 12;
ProcessorID.BITS_FAMILY = 10;
ProcessorID.MASK_TYPE = (1 << ProcessorID.BITS_TYPE) - 1;
ProcessorID.MASK_REV = (1 << ProcessorID.BITS_REV) - 1;
ProcessorID.MASK_SUBFAMILY = (1 << ProcessorID.BITS_SUBFAMILY) - 1;
ProcessorID.MASK_FAMILY = (1 << ProcessorID.BITS_FAMILY) - 1;
ProcessorID.SHIFT_TYPE = 0;
ProcessorID.SHIFT_REV = ProcessorID.SHIFT_TYPE + ProcessorID.BITS_TYPE;
ProcessorID.SHIFT_SUBFAMILY = ProcessorID.SHIFT_REV + ProcessorID.BITS_REV;
ProcessorID.SHIFT_FAMILY = ProcessorID.SHIFT_SUBFAMILY + ProcessorID.BITS_SUBFAMILY;
ProcessorID.ICEPick = 'ICEPick_';
ProcessorID.DRP_SCRIPT = 'DRP_SCRIPT_';
ProcessorID.TMS470R = 'TMS470R';
ProcessorID.TMS370P = 'TMS370P';
ProcessorID.TMS320C = 'TMS320C';
ProcessorID.TMS = 'TMS';
ProcessorID.MSP430 = 'MSP430';
ProcessorID.ARM = 'ARM';
ProcessorID.CORTEX = 'Cortex ';
ProcessorID.ARP32 = 'ARP32';

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
class ErrorReport {
    constructor(errorMessage, location) {
        this.location = location;
        this.errorMessage = errorMessage;
    }
    getErrorMessage() {
        return this.errorMessage;
    }
    getLocation() {
        return this.location;
    }
    compareTo(errorReport) {
        let result = this.errorMessage.localeCompare(errorReport.errorMessage);
        if (result === 0) {
            if (this.location === null) {
                result = errorReport.location === null ? 0 : -1;
            }
            else if (errorReport.location === null) {
                result = this.location === null ? 0 : +1;
            }
            else {
                result = this.location.localeCompare(errorReport.location);
            }
        }
        return result;
    }
}
class CpuIdentifier {
    constructor(id, newParent) {
        this.id = '<root>';
        this.parent = null;
        if (id instanceof CpuIdentifier) {
            let copy = id;
            if (typeof newParent === 'number') {
                const num_parents = newParent;
                let cur = this;
                cur.id = copy.id;
                cur.parent = null;
                for (let i = num_parents; i-- > 0 && copy.parent !== null;) {
                    cur.parent = new CpuIdentifier(copy.parent.id, null);
                    cur = cur.parent;
                    copy = copy.parent;
                }
            }
            else {
                if (copy === null || copy.id.length === 0) {
                    if (newParent === null) {
                        this.id = '';
                        this.parent = null;
                    }
                    else {
                        this.id = newParent.id;
                        this.parent = newParent.parent;
                    }
                }
                else {
                    this.id = copy.id;
                    this.parent = newParent;
                    let prev = null;
                    let cur = copy.parent;
                    while (cur !== null) {
                        const tmp = new CpuIdentifier(cur.id, newParent);
                        if (prev !== null) {
                            prev.parent = tmp;
                        }
                        else {
                            this.parent = tmp;
                        }
                        prev = tmp;
                        cur = cur.parent;
                    }
                }
            }
        }
        else {
            const parent = newParent;
            this.id = id === null ? '' : id;
            this.parent = (parent !== null && parent.id.length === 0) ? parent.parent : parent;
        }
    }
    compareTo(to) {
        if (to === null) {
            return (this.id === null || this.id.length === 0) && this.parent === null ? 0 : 1;
        }
        let result = this.id.localeCompare(to.id);
        if (result === 0) {
            if (this.parent === null) {
                result = to.parent === null ? 0 : -1;
            }
            else if (to.parent === null) {
                result = 1;
            }
            else {
                result = this.parent.compareTo(to.parent);
            }
        }
        return result;
    }
    isChildOf(obj) {
        let result = 0;
        if (obj === null)
            return result;
        let cur = this.parent;
        while (cur !== null) {
            result++;
            if (obj.compareTo(cur) === 0) {
                return result;
            }
            cur = cur.parent;
        }
        return 0;
    }
    toString() {
        let result = this.id;
        let cur = this.parent;
        while (cur !== null) {
            result += `.${cur.id}`;
            cur = cur.parent;
        }
        return result;
    }
}
class AbstractSystemSetupComponent {
    constructor() {
        this.name = null;
        this.id = new CpuIdentifier(null, null);
        this.children = null;
    }
    getId() {
        return (this.id === null) ? '' : this.id.id;
    }
    getName() {
        return (this.name === null || this.name.length === 0) ? this.getId() : this.name;
    }
    getDecoratedLabelText() {
        return this.getName();
    }
    toString() {
        return this.getName();
    }
    getChildren() {
        return this.children;
    }
    addChild(child) {
        if (this.children === null) {
            this.children = new Array();
        }
        this.children.push(child);
    }
    findParent(elements) {
        let highScore = Number.MAX_SAFE_INTEGER;
        let result = null;
        elements.forEach((element) => {
            const score = this.id.isChildOf(element.id);
            if (score > 0 && score < highScore) {
                highScore = score;
                result = element;
            }
        });
        return result;
    }
    assign(from) {
        if (from !== null) {
            this.id = from.id;
            if (from.name !== null && from.name.length > 0)
                this.name = from.name;
        }
    }
    static findElementInList(setupElements, setupElementId) {
        setupElements.forEach(setupElement => {
            if (setupElement.id.compareTo(setupElementId) === 0) {
                return setupElement;
            }
        });
        return null;
    }
}
class Board extends AbstractSystemSetupComponent {
    constructor(name, id) {
        super();
        this.name = name === null || name.length === 0 ? null : name;
        this.id = id;
    }
    getIconDescriptor() {
        return HWDB.BOARD_TAG;
    }
}
class Connection extends AbstractSystemSetupComponent {
    constructor(name, connectionType, connectionName, id) {
        super();
        this.connectionName = null;
        this.connectionType = null;
        this.drivers = null;
        if (name instanceof Connection) {
            this.assign(name);
        }
        else {
            this.name = name === null || name.length === 0 ? null : name;
            this.id = id;
            this.connectionName = (!connectionName || connectionName.length === 0) ? null : connectionName;
            this.connectionType = (!connectionType || connectionType.length === 0) ? null : connectionType;
        }
    }
    assign(from) {
        if (from !== null) {
            super.assign(from);
            if (this.connectionName === null) // only change connectionName first time.
                this.connectionName = from.connectionName;
            if (this.connectionType === null) // only change connectionName first time.
                this.connectionType = from.connectionType;
        }
    }
    addDriver(driver) {
        if (this.drivers === null) {
            this.drivers = new Array(3);
        }
        this.drivers.forEach(item => {
            if (item.id.compareTo(driver.id) === 0) {
                item.assign(driver);
                return;
            }
        });
        this.drivers.push(driver);
    }
    findDriver(isaType) {
        if (this.drivers !== null) {
            this.drivers.forEach(driver => {
                if (driver.isa !== null && HardwareDatabaseReader.isCompatibleISA(driver.isa, isaType)) {
                    return driver;
                }
            });
        }
        return null;
    }
    static findConnectionInList(setupElements, setupElementId) {
        const connection = AbstractSystemSetupComponent.findElementInList(setupElements, setupElementId);
        if (connection !== null && connection instanceof Connection) {
            return connection;
        }
        return null;
    }
    getIconDescriptor() {
        return HWDB.CONNECTION_TAG;
    }
}
class Device extends AbstractSystemSetupComponent {
    constructor(id, name, fileName, partnum) {
        super();
        if (id instanceof Device) {
            this.id = id.id;
            this.partnum = id.partnum;
            this.fileName = id.fileName;
            this.assign(id);
        }
        else {
            this.id = id;
            this.name = (!name || name.length === 0) ? null : name;
            this.fileName = fileName;
            this.partnum = partnum;
        }
    }
    assign(from) {
        if (from !== null) {
            super.assign(from);
            this.partnum = from.partnum;
            this.fileName = from.fileName;
        }
    }
    getFileName() {
        return this.fileName;
    }
    getPartNumber() {
        return this.partnum;
    }
    getIconDescriptor() {
        return HWDB.DEVICE_TAG;
    }
}
class SystemRoot extends AbstractSystemSetupComponent {
    getName() {
        return 'System';
    }
    getIconDescriptor() {
        return 'system';
    }
}
class Driver {
    constructor(isa, procId, id, debuggable, description, driverFilename, multiProcessorSupport) {
        this.isa = null;
        this.procId = 0;
        this.debuggable = false;
        this.description = null;
        this.driverFilename = null;
        this.multiProcessorSupport = false;
        if (isa instanceof Driver) {
            this.id = isa.id;
            this.assign(isa);
        }
        else {
            this.isa = (isa === null || isa.length === 0) ? null : isa;
            this.procId = procId;
            this.id = id;
            this.debuggable = debuggable;
            this.description = (!description || description.length === 0) ? null : description;
            this.driverFilename = driverFilename ?? null;
            this.multiProcessorSupport = multiProcessorSupport;
        }
    }
    assign(obj) {
        if (obj !== null) {
            this.id = obj.id;
            if (obj.isa !== null && obj.isa.length > 0)
                this.isa = obj.isa;
            if (obj.procId !== 0)
                this.procId = obj.procId;
            if (!obj.debuggable)
                this.debuggable = false;
            this.description = obj.description;
            this.driverFilename = obj.driverFilename;
            this.multiProcessorSupport = obj.multiProcessorSupport;
        }
    }
    isDebuggable() {
        return this.debuggable;
    }
    isRouter() {
        return new ProcessorID(this.procId).isRouter();
    }
    isMultiProcessor() {
        return this.multiProcessorSupport;
    }
    isMultiBoard(driverLocation) {
        return this.driverFilename === null ? true : this.driverFilename.localeCompare(driverLocation) === 0;
    }
    getDriverLocation() {
        return this.driverFilename;
    }
    toString() {
        return 'Driver for ' + this.isa;
    }
}
class Property {
    constructor(id, name, defaultValue) {
        this.id = id;
        this.name = name;
        this.defaultValue = defaultValue;
    }
    getSubProperties(overrideValue) {
        return null;
    }
    getValue(overrideValue) {
        return (overrideValue === null || overrideValue.length === 0) ? this.defaultValue : overrideValue;
    }
    getName() {
        return name;
    }
    toString() {
        return 'Property ' + name + ' = ' + this.defaultValue;
    }
    static findLastProperty(properties, id) {
        // search the list from the end to the beginning to return the last property found in the list.
        for (let i = properties.length; i-- > 0;) {
            const property = properties[i];
            if (property.id.id.localeCompare(id) === 0)
                return property;
        }
        return null;
    }
    static getProperties(defaults, overrides) {
        const result = new Map();
        defaults.forEach(property => {
            let override = null;
            if (overrides !== null) {
                override = Property.findLastProperty(overrides, property.id.id);
            }
            try {
                result.set(property.id.id, property.getValue(override === null ? null : override.defaultValue));
            }
            catch (e) {
                // don't add properties that generate null pointer exceptions.  This occurs when
                // you try to read properties from device files where the default choices from the driver
                // are not available because it is not a full configuration.
            }
        });
        return result;
    }
}
class NumericProperty extends Property {
    constructor(id, name, value) {
        super(id, name, value);
    }
    getIntValue(overrideValue) {
        const value = (overrideValue === null || overrideValue.length === 0) ? this.defaultValue : overrideValue;
        if (value.startsWith('0x')) {
            return Number.parseInt(value.substring(2), 16);
        }
        return Number.parseInt(value);
    }
}
class Choice {
    constructor(value) {
        this.subProperties = new Array(2);
        this.value = value;
    }
    addSubProperty(subProperty) {
        this.subProperties.push(subProperty);
    }
    getSubProperties() {
        return this.subProperties;
    }
    getValue() {
        return this.value;
    }
    toString() {
        return 'Choice ' + this.value;
    }
}
class ChoiceListProperty extends NumericProperty {
    constructor(id, name, value) {
        super(id, name, value);
        this.choices = new Array(2);
    }
    getChoices() {
        if (this.choices.length > 0) {
            const result = new Array(this.choices.length);
            for (let i = 0; i < this.choices.length; i++) {
                result[i] = this.choices[i].getValue();
            }
            return result;
        }
        return null;
    }
    getSubProperties(overrideValue) {
        return this.getChoice(overrideValue).getSubProperties();
    }
    getChoice(overrideValue) {
        let index = this.getIntValue(overrideValue);
        if (index < 0 || index > this.choices.length) {
            index = 0;
        }
        return this.choices[index];
    }
    getValue(overrideValue) {
        return this.getChoice(overrideValue).getValue();
    }
    addChoice(value) {
        const choice = new Choice(value);
        this.choices.push(choice);
        return choice;
    }
    findSubProperties(choiceValue) {
        this.choices.forEach(choice => {
            if (choice.getValue().localeCompare(choiceValue) === 0) {
                return choice.getSubProperties();
            }
        });
        return null;
    }
}
class Cpu extends AbstractSystemSetupComponent {
    constructor(id, name, isa, connection) {
        super();
        this.connection = null;
        this.isa = null;
        if (id instanceof CpuIdentifier) {
            this.id = id;
            this.name = (!name || name.length === 0) ? null : name;
            this.isa = (!isa || isa.length === 0) ? null : isa;
            this.connection = connection ?? null;
        }
        else {
            this.assign(id);
        }
    }
    toString() {
        if (this.name === null && this.id === null)
            return '';
        if (this.connection === null)
            return this.name === null ? this.id.id : this.name;
        return this.connection.toString() + '\\' + (this.name === null ? this.id.id : this.name);
    }
    getDecoratedLabelText() {
        if (this.isBypassed() && !this.isRouter() && !this.isSubpath()) {
            return this.getName() + ' (bypassed)';
        }
        return this.getName();
    }
    getBoardName() {
        return this.connection === null ? null : this.connection.toString();
    }
    findParentCpu(potentialParents) {
        let highScore = Number.MAX_SAFE_INTEGER;
        let result = null;
        potentialParents.forEach(parent => {
            if (this.id.compareTo(parent.id) !== 0 && !parent.isSubpath()) {
                const score = this.id.isChildOf(parent.id);
                if (score > 0 && score < highScore) {
                    highScore = score;
                    result = parent;
                }
            }
        });
        return result;
    }
    findParentSubPath(potentialParents) {
        let highScore = Number.MAX_SAFE_INTEGER;
        let result = null;
        potentialParents.forEach(parent => {
            if (this.id.compareTo(parent.id) !== 0 && parent.isSubpath()) {
                const score = this.id.isChildOf(parent.id);
                if (score > 0 && score < highScore) {
                    highScore = score;
                    result = parent;
                }
            }
        });
        return result;
    }
    findParentDevice(devices) {
        let highScore = Number.MAX_SAFE_INTEGER;
        let result = null;
        devices.forEach(device => {
            const score = this.id.isChildOf(device.id);
            if (score > 0 && score < highScore) {
                highScore = score;
                result = device;
            }
        });
        return result;
    }
    assign(from) {
        if (from !== null) {
            super.assign(from);
            this.isa = from.isa === null ? this.isa : from.isa;
            this.connection = from.connection === null ? this.connection : from.connection;
        }
    }
    isSubpath() {
        return (this.isa === null ? false : this.isa.localeCompare(Cpu.SUB_PATH) === 0);
    }
    isDebuggable() {
        if (this.isa !== null && !this.isa.startsWith('BYPASS')) {
            // assume cpu is debugable if not connection available yet.
            if (this.connection === null) {
                return true;
            }
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return driver.isDebuggable();
            }
        }
        return false;
    }
    isBypassed() {
        return this.isa !== null && this.isa.startsWith('BYPASS');
    }
    isMissingDriver() {
        if (this.connection !== null && this.isa !== null && !this.isa.startsWith('BYPASS')) {
            const driver = this.connection.findDriver(this.isa);
            return driver === null;
        }
        return false;
    }
    isMultiBoard(boardLocation) {
        if (this.connection !== null && this.isa !== null && !this.isa.startsWith('BYPASS')) {
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return driver.isMultiBoard(boardLocation);
            }
        }
        return true;
    }
    isMultiProcessor() {
        if (this.connection !== null && this.isa !== null && !this.isa.startsWith('BYPASS')) {
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return driver.isMultiProcessor();
            }
        }
        return true;
    }
    getDriverLocation() {
        if (this.connection !== null && this.isa !== null && !this.isa.startsWith('BYPASS')) {
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return driver.getDriverLocation();
            }
        }
        return null;
    }
    isRouter() {
        if (this.connection !== null && this.isa !== null) {
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return driver.isRouter();
            }
        }
        return false;
    }
    getProcID() {
        if (this.connection !== null && this.isa !== null) {
            const driver = this.connection.findDriver(this.isa);
            if (driver !== null) {
                return new ProcessorID(driver.procId);
            }
        }
        return null;
    }
    isNonDebug() {
        const procID = this.getProcID();
        return procID === null ? false : procID.isNonDebug();
    }
    getIconDescriptor() {
        if (this.isRouter()) {
            return HWDB.ROUTER_TAG;
        }
        else if (this.isSubpath()) {
            return HWDB.SUBPATH_TAG;
        }
        else if (this.isBypassed()) {
            return HWDB.BYPASS_PROPERTY;
        }
        else if (this.isNonDebug()) {
            return 'nondebug';
        }
        else if (this.isDebuggable()) {
            return HWDB.CPU_TAG;
        }
        else {
            return 'nodriver';
        }
    }
}
Cpu.SUB_PATH = '<subpath>';
class HardwareDbFileInfo {
    constructor(root) {
        this.rootId = null;
        this.rootName = null;
        this.rootDescription = null;
        this.rootConnectionType = null;
        this.rootTagName = null;
        this.rootIsa = null;
        this.simulation = null;
        if (root !== null) {
            this.rootId = root.getAttribute(HWDB.ID_ATTRIBUTE);
            if (this.rootId !== null && this.rootId.length === 0) {
                this.rootId = null;
            }
            this.rootName = root.getAttribute(HWDB.NAME_ATTRIBUTE);
            if (this.rootName !== null && this.rootName.length === 0) {
                this.rootName = this.rootId;
            }
            if (this.rootName !== null && this.rootName.localeCompare('configuration_0') === 0) {
                // case: special,lets get the name: connection,because it might be more meaningful
                const connection = root.getChildByName(HWDB.CONNECTION_TAG, 0);
                if (connection !== null) {
                    this.rootName = XMLParser.GetAttributeString(connection, HWDB.NAME_ATTRIBUTE);
                    if (this.rootName === null || this.rootName.length === 0) {
                        this.rootName = XMLParser.GetAttributeString(connection, HWDB.ID_ATTRIBUTE);
                    }
                }
            }
            this.rootDescription = root.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
            if (this.rootDescription !== null && this.rootDescription.length === 0) {
                this.rootDescription = null;
            }
            this.rootConnectionType = root.getChildAttribute(HWDB.CONNECTION_TYPE_TAG, HWDB.TYPE_ATTRIBUTE);
            if (this.rootConnectionType !== null && this.rootConnectionType.length === 0) {
                this.rootConnectionType = null;
            }
            this.rootTagName = root.getName();
            if (this.rootTagName !== null && this.rootTagName.length === 0) {
                this.rootTagName = null;
            }
            this.rootIsa = root.getAttribute(HWDB.ISA_ATTRIBUTE);
            if (this.rootIsa !== null && this.rootIsa.length === 0) {
                this.rootIsa = null;
            }
            this.simulation = root.getAttribute('simulation');
            if (this.simulation !== null && this.simulation.length === 0) {
                this.simulation = null;
            }
        }
    }
}
class AbstractCpuOperation {
    addToListOfSetupElements(setupElements, name, isa, connection, filterByConnectionName, parentId, fileName, installDirectories) {
        // do nothing
    }
    addToListOfProperties(properties, parentId, subPathPropertiesOnly, fileName, installDirectories) {
        // do nothing
    }
}
class AddCpuOperation extends AbstractCpuOperation {
    constructor(cpuToAdd) {
        super();
        this.cpuToAdd = cpuToAdd;
    }
    addToListOfSetupElements(cpus, newName, newIsa, connection, connectionName, parentId, fileName, installDirectories) {
        if (cpus === null)
            return;
        const newCpu = new Cpu(this.cpuToAdd);
        if (newName !== null && newCpu.id === null) {
            newCpu.name = newName;
        }
        if (newIsa !== null && newCpu.id === null) {
            newCpu.isa = newIsa;
        }
        if (parentId !== null) {
            newCpu.id = new CpuIdentifier(newCpu.id, parentId);
        }
        if (newCpu.connection !== null) {
            // update connection pointer to point to a connection in the list and get correct connectionName for filtering next.
            newCpu.connection = Connection.findConnectionInList(cpus, new CpuIdentifier(newCpu.connection.id, parentId));
        }
        else {
            newCpu.connection = connection;
        }
        // filter cpus with wrong connectionName
        if (connectionName === null || (newCpu.connection !== null && newCpu.connection.connectionName !== null &&
            connectionName.localeCompare(newCpu.connection.connectionName) === 0)) {
            this.addCpu(cpus, newCpu);
        }
    }
    addCpu(cpuList, newCpu) {
        // check if already in the list
        cpuList.forEach(item => {
            if (item.id.compareTo(newCpu.id) === 0) {
                // found match: a,so update and quit.
                item.assign(newCpu);
                return;
            }
        });
        cpuList.push(newCpu);
    }
    toString() {
        if (this.cpuToAdd.isSubpath()) {
            return 'Add subpath ' + this.cpuToAdd.getName();
        }
        return 'Add Cpu ' + this.cpuToAdd.getName();
    }
}
class DriverIterator {
    constructor(listOfOperations) {
        this.cur = null;
        this.it = 0;
        this.listOfOperations = listOfOperations ?? [];
    }
    next() {
        while (this.it < this.listOfOperations.length) {
            const op = this.listOfOperations[this.it];
            ++this.it;
            if (op instanceof AddDriverOperation) {
                this.cur = op;
                return true;
            }
        }
        return false;
    }
    getConnectionType() {
        return this.cur?.connectionType ?? '';
    }
    getName() {
        return this.cur?.driverToAdd.isa ?? null;
    }
    getDescription() {
        return this.cur?.driverToAdd.description ?? null;
    }
    getProcId() {
        return this.cur?.driverToAdd.procId ?? null;
    }
}
class CpuCacheItem extends HardwareDbFileInfo {
    constructor(root) {
        super(root);
        this.lastModified = 0;
        this.readOnly = false;
        this.lastErrorMessage = null;
        this.lastModified = 0;
        this.readOnly = false;
        this.cpuOperations = null;
    }
    getDrivers() {
        return new DriverIterator(this.cpuOperations === null ? null : this.cpuOperations);
    }
    addToListOfSetupElements(setupElements, newName, newIsa, newConnection, filterByConnectionName, parentId, fileName, installDirectories) {
        if (this.cpuOperations !== null) {
            this.cpuOperations.forEach(operation => {
                operation.addToListOfSetupElements(setupElements, newName, newIsa, newConnection, filterByConnectionName, parentId, fileName, installDirectories);
            });
        }
    }
    addToListOfProperties(properties, parentId, subPathPropertiesOnly, fileName, installDirectories) {
        if (this.cpuOperations !== null) {
            this.cpuOperations.forEach(operation => {
                operation.addToListOfProperties(properties, parentId, subPathPropertiesOnly, fileName, installDirectories);
            });
        }
    }
    getSetupElements(connectionNameFilter, fileName, installDirectories) {
        if (this.cpuOperations !== null && this.cpuOperations.length > 0) {
            const elements = new Array(8);
            this.addToListOfSetupElements(elements, null, null, null, connectionNameFilter, null, fileName, installDirectories);
            if (elements.length > 0) {
                return elements;
            }
        }
        return null;
    }
    getConnections(fileName, installDirectories) {
        let connections = null;
        if (this.cpuOperations !== null && this.cpuOperations.length > 0) {
            connections = new Array(1);
            const setupElements = new Array();
            this.addToListOfSetupElements(setupElements, null, null, null, null, null, fileName, installDirectories);
            setupElements.forEach(setupElement => {
                if (setupElement instanceof Connection) {
                    connections?.push(setupElement);
                }
            });
            if (connections.length === 0) {
                connections = null;
            }
        }
        return connections;
    }
    getListOfProperties(id, subPathPropertiesOnly, fileName, installDirectories) {
        let properties = null;
        if (this.cpuOperations !== null && this.cpuOperations.length > 0) {
            properties = new Array(5);
            this.addToListOfProperties(properties, id, subPathPropertiesOnly, fileName, installDirectories);
            if (properties.length === 0) {
                properties = null;
            }
        }
        return properties;
    }
    getDevicePartNum() {
        (this.cpuOperations ?? []).forEach(cpuOperation => {
            if (cpuOperation instanceof AddDeviceOperation) {
                return cpuOperation.partnum;
            }
        });
        return null;
    }
    doesDeviceHaveProcessorsTag() {
        (this.cpuOperations ?? []).forEach(cpuOperation => {
            if (cpuOperation instanceof AddBoardOperation) {
                return cpuOperation.hasProcessorsTag;
            }
            else if (cpuOperation instanceof AddDeviceOperation) {
                return cpuOperation.hasProcessorsTag;
            }
        });
        return false;
    }
    clear() {
        this.cpuOperations = null;
    }
    getRootId() {
        return this.rootId;
    }
    add(newOperation) {
        if (this.cpuOperations === null) {
            this.cpuOperations = new Array(2);
        }
        this.cpuOperations.push(newOperation);
    }
    toString() {
        const result = new StringBuilder();
        result.append(' last modified = ');
        result.append(this.lastModified.toString());
        if (this.lastErrorMessage !== null) {
            result.append('\n\tException = ');
            result.append(this.lastErrorMessage.message ?? this.lastErrorMessage.toString());
            result.append('\n');
        }
        else {
            result.append('\n<');
            result.append(this.rootTagName);
            if (this.rootId !== null) {
                result.append(' id=');
                result.append(this.rootId);
            }
            if (this.rootName !== null) {
                result.append(' desc=');
                result.append(this.rootName);
            }
            if (this.rootDescription !== null) {
                result.append(' description=');
                result.append(this.rootDescription);
            }
            if (this.simulation !== null) {
                result.append(' simulation=');
                result.append(this.simulation);
            }
            result.append('>\n');
            if (this.rootConnectionType !== null) {
                result.append('\t<connectionType type=');
                result.append(this.rootConnectionType);
                result.append('>\n');
            }
            if (this.cpuOperations !== null) {
                this.cpuOperations.forEach(operation => {
                    result.append('\t');
                    result.append(operation.toString());
                    result.append('\n');
                });
            }
        }
        return result.toString();
    }
}
class AddPropertyOperation extends AbstractCpuOperation {
    constructor(propertyToAdd, subPathProperty) {
        super();
        this.propertyToAdd = propertyToAdd;
        this.subPathProperty = subPathProperty;
    }
    addToListOfProperties(properties, parentId, subPathPropertiesOnly, fileName, installDirectories) {
        if (this.propertyToAdd.id.parent && parentId.compareTo(this.propertyToAdd.id.parent) === 0 && this.subPathProperty === subPathPropertiesOnly) {
            properties.push(this.propertyToAdd);
        }
    }
    toString() {
        return 'Add Property ' + this.propertyToAdd.id === null ? '<null>' : this.propertyToAdd.id.toString();
    }
}
class AddDeviceOperation extends AbstractCpuOperation {
    constructor(id, name, partnum, hasProcessorsTag) {
        super();
        this.id = id;
        this.name = name === null || name.length === 0 ? null : name;
        this.partnum = partnum;
        this.hasProcessorsTag = hasProcessorsTag;
    }
    addToListOfSetupElements(setupElements, newName, newIsa, connection, filterByConnectionName, parentId, fileName, installDirectories) {
        if (setupElements !== null) {
            const newId = new CpuIdentifier(this.id, parentId);
            this.addDevice(setupElements, new Device(newId, newName !== null && this.id === null ? newName : this.name, fileName, this.partnum));
        }
    }
    addDevice(setupElements, newDevice) {
        // check if already in the list
        setupElements.forEach(item => {
            if (item.id.compareTo(newDevice.id) === 0) {
                // found a match, so update and quit.
                item.assign(newDevice);
                return;
            }
        });
        setupElements.push(newDevice);
    }
    toString() {
        return 'Add Device ' + this.id === null ? '<null>' : this.id.toString();
    }
}
class AddBoardOperation extends AbstractCpuOperation {
    constructor(id, name, hasProcessorsTag) {
        super();
        this.id = id;
        this.name = (!name || name.length === 0) ? null : name;
        this.hasProcessorsTag = hasProcessorsTag;
    }
    addToListOfSetupElements(setupElements, newName, newIsa, connection, filterByConnectionName, parentId, fileName, installDirectories) {
        if (setupElements !== null) {
            const newId = new CpuIdentifier(this.id, parentId);
            this.addBoard(setupElements, new Board(newName !== null && this.id === null ? newName : this.name, newId));
        }
    }
    addBoard(setupElements, newBoard) {
        // check if already in the list
        setupElements.forEach(item => {
            if (item.id.compareTo(newBoard.id) === 0) {
                item.assign(newBoard);
                return;
            }
        });
        setupElements.push(newBoard);
    }
    toString() {
        return 'Add Board ' + this.id === null ? '<null>' : this.id.toString();
    }
}
class AddConnectionOperation extends AbstractCpuOperation {
    constructor(connectionToAdd) {
        super();
        this.connectionToAdd = connectionToAdd;
    }
    addToListOfSetupElements(setupElements, newName, newIsa, connection, filterByConnectionName, parentId, fileName, installDirectories) {
        const newConnection = new Connection(this.connectionToAdd);
        if (newName !== null && newConnection.id === null) {
            newConnection.name = newName;
        }
        newConnection.id = new CpuIdentifier(newConnection.id, parentId);
        this.addConnection(setupElements, newConnection);
    }
    addConnection(connectionList, newConnection) {
        if (newConnection !== null && connectionList !== null) {
            // check if already in the list
            connectionList.forEach(item => {
                if (item.id.compareTo(newConnection.id) === 0) {
                    item.assign(newConnection);
                    return;
                }
            });
            connectionList.push(newConnection);
        }
    }
    toString() {
        return 'Add Connection ' + this.connectionToAdd.id === null ? '<null>' : this.connectionToAdd.id.toString();
    }
}
class AddDriverOperation extends AbstractCpuOperation {
    constructor(connectionType, driverToAdd, connectionId) {
        super();
        this.connectionType = connectionType;
        this.driverToAdd = driverToAdd;
        this.connectionId = connectionId;
    }
    addToListOfSetupElements(setupElements, newName, newIsa, connection, filterByConnectionName, parentId, fileName, installDirectories) {
        // find the correct connection to add driver to from list of connections.
        if (connection === null) {
            connection = Connection.findConnectionInList(setupElements, new CpuIdentifier(this.connectionId, parentId));
        }
        if (connection !== null && connection.connectionType !== null && connection.connectionType.localeCompare(this.connectionType) === 0) {
            const newDriver = new Driver(this.driverToAdd);
            if (parentId !== null) {
                newDriver.id = new CpuIdentifier(newDriver.id, parentId);
            }
            connection.addDriver(newDriver);
        }
    }
    toString() {
        return 'Add Driver ' + this.driverToAdd.id === null ? '<null>' : this.driverToAdd.id.toString();
    }
}
function addToListOfCpuOperations(node, parentId, cpus, includeRouters, connection) {
    let tag = node.getName();
    if (tag.localeCompare('module') === 0) {
        return;
    }
    if (tag.localeCompare(HWDB.CONNECTION_TAG) === 0) {
        connection = new Connection(node.getAttribute(HWDB.NAME_ATTRIBUTE), node.getChildAttribute(HWDB.CONNECTION_TYPE_TAG, HWDB.TYPE_ATTRIBUTE), node.getAttribute(HWDB.ID_ATTRIBUTE), parentId);
        cpus.add(new AddConnectionOperation(connection));
    }
    else if (tag.localeCompare(HWDB.ISA_TAG) === 0) {
        let isaType = node.getAttribute(HWDB.ID_ATTRIBUTE);
        if (isaType === null || isaType.length === 0) {
            isaType = node.getAttribute(HWDB.TYPE_ATTRIBUTE);
        }
        const isaDescription = node.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
        const procId = node.getAttributeInteger(HWDB.PROCID_ATTRIBUTE);
        const driverId = new CpuIdentifier(isaType, parentId);
        const nDrivers = node.countChildrenByName(HWDB.DRIVER_TAG);
        for (let i = 0; i < nDrivers; i++) {
            // make sure the driver file is not "NONE".
            let driverFilename = node.getChildAttribute(HWDB.DRIVER_TAG, HWDB.FILE_ATTRIBUTE);
            let debuggable = true;
            if (driverFilename !== null && driverFilename.endsWith('NONE')) {
                debuggable = false;
            }
            const driverTag = new Tag(node, node.getChildByName(HWDB.DRIVER_TAG, i));
            const nConnectionTypes = driverTag.countChildrenByName(HWDB.CONNECTION_TYPE_TAG);
            for (let j = 0; j < nConnectionTypes; j++) {
                const connectionTypeTag = new Tag(driverTag, driverTag.getChildByName(HWDB.CONNECTION_TYPE_TAG, j));
                // get multiBoard and multiProcessor support in driver
                if (driverTag.getPropertyString('multiBoard', 'yes').toLowerCase().localeCompare('yes') === 0) {
                    driverFilename = null; // indicate multiBoard support with a null driver name (saves storage).
                }
                const capableMultiProcessor = driverTag.getPropertyString('multiProcessor', 'yes').toLowerCase().localeCompare('yes') === 0;
                const driver = new Driver(isaType, procId, driverId, debuggable, isaDescription, driverFilename, capableMultiProcessor);
                cpus.add(new AddDriverOperation(connectionTypeTag.getAttribute(HWDB.TYPE_ATTRIBUTE), driver, connection !== null ? connection.id : null));
            }
            const nProperties = driverTag.countChildrenByName(HWDB.PROPERTY_TAG);
            for (let p = 0; p < nProperties; p++) {
                const property = new Tag(driverTag, driverTag.getChildByName(HWDB.PROPERTY_TAG, p));
                addToListOfCpuOperations(property, new CpuIdentifier(property.getAttribute(HWDB.ID_ATTRIBUTE), driverId), cpus, includeRouters, connection);
            }
        }
        return; // don't bother continuing down child nodes.
    }
    else if ((tag.localeCompare(HWDB.CPU_TAG) === 0
        || (includeRouters && tag.localeCompare(HWDB.ROUTER_TAG) === 0))) {
        let isaType = node.getAttribute(HWDB.ISA_ATTRIBUTE);
        if (node.getPropertyString(HWDB.BYPASS_PROPERTY, '0').localeCompare('1') === 0) {
            isaType = 'BYPASS';
        }
        cpus.add(new AddCpuOperation(new Cpu(parentId, node.getAttribute(HWDB.NAME_ATTRIBUTE), isaType, connection)));
    }
    else if (tag.localeCompare(HWDB.SUBPATH_TAG) === 0) {
        cpus.add(new AddCpuOperation(new Cpu(parentId, node.getAttribute(HWDB.NAME_ATTRIBUTE), Cpu.SUB_PATH, connection)));
    }
    else if (tag.localeCompare(HWDB.DEVICE_TAG) === 0) {
        cpus.add(new AddDeviceOperation(parentId, node.getAttribute(HWDB.NAME_ATTRIBUTE), node.getAttribute(HWDB.PARTNUM_ATTRIBUTE), node.countChildrenByName(HWDB.PROCESSORS_TAG) !== 0));
    }
    else if (tag.localeCompare(HWDB.BOARD_TAG) === 0) {
        cpus.add(new AddBoardOperation(parentId, node.getAttribute(HWDB.NAME_ATTRIBUTE), node.countChildrenByName(HWDB.PROCESSORS_TAG) !== 0));
    }
    else if (tag.localeCompare(HWDB.PROPERTY_TAG) === 0) {
        const subpathAttr = node.getAttribute(HWDB.SUBPATH_ATTRIBUTE);
        const subPathProperty = subpathAttr !== null && subpathAttr.localeCompare('true') === 0;
        cpus.add(new AddPropertyOperation(createPropertyOperation(node, parentId === null ? new CpuIdentifier('', null) : parentId), subPathProperty));
        return; // don't traverse children.  Already don't in CreatePropertyOperation.
    }
    else if (tag.localeCompare(HWDB.JTAG_TAG) === 0) {
        return; // skip this tag.  It is only used for overriding default properties.
    }
    let childNode = node.getFirstChild();
    while (childNode !== null) {
        const child = new Tag(node, childNode);
        tag = child.getName();
        if (tag.localeCompare(HWDB.PROCESSORS_TAG) === 0) {
            childNode = child.getFirstChild();
            continue;
        }
        else if (tag.localeCompare(HWDB.INSTANCE_TAG) === 0
            || tag.localeCompare(HWDB.INCLUDE_TAG) === 0) {
            const href = child.getAttribute(HWDB.HREF_ATTRIBUTE);
            if (!(href.indexOf('/Modules/') >= 0 || href.indexOf('\\Modules\\') >= 0
                || href.startsWith('Modules\\') || href.startsWith('Modules/'))) {
                // const newOp = new IncludeFileOperation(child, parentId, connection);
                // cpus.add(newOp);
            }
        }
        else {
            addToListOfCpuOperations(child, new CpuIdentifier(child.getAttribute(HWDB.ID_ATTRIBUTE), parentId), cpus, includeRouters, connection);
        }
        childNode = childNode.nextSibling ?? null;
    }
}
function createPropertyOperation(node, parentId) {
    const propertyType = node.getAttribute(HWDB.TYPE_ATTRIBUTE);
    let propertyName = node.getAttribute(HWDB.PROPERTY_NAME_ATTRIBUTE);
    if (parentId.id === null || parentId.id.length === 0) {
        parentId.id = propertyName;
    }
    if (parentId.id === null || parentId.id.length === 0) {
        parentId.id = node.getAttribute('ID');
    }
    if (propertyName === null || propertyName.length === 0) {
        propertyName = node.getAttribute(HWDB.NAME_ATTRIBUTE);
    }
    if (propertyName === null || propertyName.length === 0) {
        propertyName = parentId.id;
    }
    if (propertyType.localeCompare(HWDB.CHOICE_TYPE) !== 0) {
        return new Property(parentId, propertyName, node.getAttribute(HWDB.VALUE_ATTRIBUTE));
    }
    else {
        const choiceList = new ChoiceListProperty(parentId, propertyName, node.getAttribute(HWDB.VALUE_ATTRIBUTE));
        let childNode = node.getFirstChild();
        while (childNode !== null) {
            const child = new Tag(node, childNode);
            let tag = child.getName();
            if (tag.localeCompare(HWDB.CHOICE_TAG) === 0) {
                let value = child.getAttribute(HWDB.PROPERTY_NAME_ATTRIBUTE);
                if (value === null || value.length === 0) {
                    value = child.getAttribute(HWDB.CHOICE_VALUE_ATTRIBUTE);
                }
                const choice = choiceList.addChoice(value);
                let subPropertyNode = childNode.firstChild ?? null;
                while (subPropertyNode !== null) {
                    const subProperty = new Tag(node, subPropertyNode);
                    tag = subProperty.getName();
                    if (tag.localeCompare(HWDB.PROPERTY_TAG) === 0) {
                        choice.addSubProperty(createPropertyOperation(subProperty, parentId));
                    }
                    subPropertyNode = subPropertyNode.nextSibling ?? null;
                }
            }
            childNode = childNode.nextSibling ?? null;
        }
        return choiceList;
    }
}
class SystemSetupReader {
    static getSchemaDirectory() {
        return this.schemaDirectory;
    }
    static getTargetDbDirectory() {
        return this.installDirectories[0] + '/';
    }
    static getRootDirectories() {
        return this.installDirectories;
    }
    getErrorMessages(flatRootNode, fileName) {
        try {
            let cpuCacheItem = null;
            if (flatRootNode !== null) {
                cpuCacheItem = new CpuCacheItem(flatRootNode);
                addToListOfCpuOperations(flatRootNode, new CpuIdentifier(null, null), cpuCacheItem, true, null);
            }
            return this.doGetErrorMessages(cpuCacheItem, fileName);
        }
        catch (e) {
            const errors = new Array(1);
            errors.push(new ErrorReport(e.getLocalizedMessage(), null));
            return errors;
        }
    }
    doGetErrorMessages(cpuCacheItem, fileName) {
        const connectionNames = new Array();
        const cpuNames = new Map();
        const subpathNames = new Array();
        const errorMessages = new Array();
        let debuggableCpuCount = 0;
        let lastMultiBoardCapableCpu = null;
        let lastMultiProcessorCapableCpu = null;
        if (cpuCacheItem !== null) {
            const setupElements = cpuCacheItem.getSetupElements(null, fileName, SystemSetupReader.installDirectories);
            if (setupElements !== null) {
                setupElements.forEach(setupElement => {
                    // test for unique connection names
                    if (setupElement instanceof Connection) {
                        const connection = setupElement;
                        let connectionName = connection.toString();
                        if (connectionName !== null && connectionName.length > 0) {
                            connectionName = connectionName.toLowerCase();
                            if (connectionNames.includes(connectionName)) {
                                errorMessages.push(new ErrorReport('More that one connection is named ' + connectionName, connectionName));
                            }
                            else {
                                connectionNames.push(connectionName);
                            }
                        }
                    }
                });
            }
            if (setupElements !== null) {
                let driverLocation = '';
                let capableMultiProcessor = true;
                let capableMultiBoard = true;
                for (let i = 0; i < setupElements.length; i++) {
                    const setupElement = setupElements[i];
                    if (setupElement instanceof Cpu) {
                        driverLocation = setupElement.getDriverLocation() ?? '';
                        break;
                    }
                }
                for (let i = setupElements.length; i-- > 0;) {
                    const setupElement = setupElements[i];
                    if (setupElement instanceof Cpu) {
                        const cpu = setupElement;
                        let name = cpu.getName();
                        if (!name.match(/^[a-zA-Z_]\w*$/)) {
                            errorMessages.push(new ErrorReport('Name has invalid characters.  Cpu, router, and subpath names must begin with a letter and only contain numbers letters and the underscore character.', cpu.toString()));
                        }
                        // test for unique and valid names
                        name = cpu.toString().toLowerCase();
                        // test for unique cpu names per connection
                        const connectionName = cpu.getBoardName()?.toLowerCase();
                        if (connectionName && !cpu.isSubpath() && !cpu.isRouter()) {
                            if (!cpuNames.has(connectionName)) {
                                cpuNames.set(connectionName, new Set());
                            }
                            if (cpuNames.get(connectionName).has(name)) {
                                errorMessages.push(new ErrorReport('More than one cpu is named ' + cpu.getName(), cpu.toString()));
                            }
                            else {
                                cpuNames.get(connectionName).add(name);
                            }
                        }
                        // test for missing drivers
                        if (!cpu.isSubpath()) {
                            if (cpu.isMissingDriver()) {
                                errorMessages.push(new ErrorReport('Cannot find a driver for Cpu ' + cpu.getName(), cpu.toString()));
                                debuggableCpuCount++; // don't generate errors for no cpus.
                            }
                            else if (cpu.isDebuggable() && !cpu.isRouter()) {
                                debuggableCpuCount++;
                                // test for multi-board and multi-processor support
                                if (capableMultiProcessor) {
                                    capableMultiProcessor = capableMultiProcessor && cpu.isMultiProcessor();
                                    lastMultiProcessorCapableCpu = cpu;
                                }
                                if (capableMultiBoard) {
                                    capableMultiBoard = capableMultiBoard && cpu.isMultiBoard(driverLocation);
                                    lastMultiBoardCapableCpu = cpu;
                                }
                            }
                        }
                    }
                }
                if (capableMultiBoard === false) {
                    errorMessages.push(new ErrorReport('One or more drivers does not support heterogeneous multiprocessing.\nPlease bypass one or more processors.', lastMultiBoardCapableCpu?.toString() ?? null));
                }
                else if (capableMultiProcessor === false && debuggableCpuCount > 1) {
                    errorMessages.push(new ErrorReport('One or more drivers does not support multiple processors.\nPlease bypass all but one processor.', lastMultiProcessorCapableCpu?.toString() ?? null));
                }
            }
        }
        // test for no debuggable Cpus
        if (debuggableCpuCount === 0) {
            errorMessages.push(new ErrorReport('There are no debuggable cpus', null));
        }
        if (errorMessages.length === 0) {
            return null;
        }
        return errorMessages;
    }
}
SystemSetupReader.schemaDirectory = 'ccs_base/common/targetdb';
SystemSetupReader.installDirectories = [SystemSetupReader.schemaDirectory];

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
const nodesToShow = new Set();
const nodesToSuppress = new Set();
const hideConfigurations = true;
/* nodesToShow */ {
    if (!hideConfigurations)
        nodesToShow.add(HWDB.CONFIGURATION_TAG);
    nodesToShow.add(HWDB.CONNECTION_TAG);
    nodesToShow.add(HWDB.CPU_TAG);
    nodesToShow.add(HWDB.CORE_TAG);
    nodesToShow.add(HWDB.ROUTER_TAG);
    nodesToShow.add(HWDB.SUBPATH_TAG);
    nodesToShow.add(HWDB.BOARD_TAG);
    nodesToShow.add(HWDB.DEVICE_TAG);
}
/* nodesToSuppress */ {
    nodesToSuppress.add(HWDB.CONFIGURATIONS_TAG);
    if (hideConfigurations)
        nodesToSuppress.add(HWDB.CONFIGURATION_TAG);
    nodesToSuppress.add(HWDB.PLATFORM_TAG);
    nodesToSuppress.add(HWDB.PROCESSORS_TAG);
}
class SystemSetupWriter extends SystemSetupReader {
    /**
     * Constructor.
     */
    constructor() {
        super();
        this.xmlReader = new HardwareDatabaseReader();
        this.xmlReader.addTagsToFilter([
            HWDB.CONFIGURATIONS_TAG,
            HWDB.CONFIGURATION_TAG,
            HWDB.CONNECTION_TAG,
            HWDB.CONNECTION_TYPE_TAG,
            HWDB.DRIVERS_TAG,
            HWDB.ISA_TAG,
            HWDB.DRIVER_TAG,
            HWDB.PLATFORM_TAG,
            HWDB.BOARD_TAG,
            HWDB.PROCESSORS_TAG,
            HWDB.CPU_TAG,
            HWDB.CORE_TAG,
            HWDB.DEVICE_TAG,
            HWDB.SUBPATH_TAG,
            HWDB.ROUTER_TAG,
            HWDB.PROPERTY_TAG,
            HWDB.CHOICE_TAG,
            HWDB.DRIVER_PROPERTIES_TAG,
            HWDB.CHOICELIST_TAG,
            HWDB.CURRENT_TAG,
            HWDB.INFERENCE_TAG,
            HWDB.CURRENT_CHOICE_TAG,
            HWDB.JTAG_TAG
        ]);
        this.xmlReader.addAttributesToFilter([
            HWDB.ID_ATTRIBUTE,
            HWDB.PROCID_ATTRIBUTE,
            HWDB.ISA_ATTRIBUTE,
            HWDB.HW_REV_ATTRIBUTE,
            HWDB.PARTNUM_ATTRIBUTE,
            HWDB.VER_ATTRIBUTE,
            HWDB.NAME_ATTRIBUTE,
            HWDB.PROPERTY_NAME_ATTRIBUTE,
            HWDB.DESCRIPTION_ATTRIBUTE,
            HWDB.VALUE_ATTRIBUTE,
            HWDB.KEY_ATTRIBUTE,
            HWDB.EXTN_ATTRIBUTE,
            HWDB.UPPER_RANGE_ATTRIBUTE,
            HWDB.LOWER_RANGE_ATTRIBUTE,
            HWDB.UPPER_BOUND_ATTRIBUTE,
            HWDB.LOWER_BOUND_ATTRIBUTE,
            HWDB.ADVICE_ATTRIBUTE,
            HWDB.SUMMARY_ATTRIBUTE,
            HWDB.CHOICE_VALUE_ATTRIBUTE,
            HWDB.DRIVER_TYPE_ATTRIBUTE,
            HWDB.SUBPATH_ATTRIBUTE,
            HWDB.TYPE_ATTRIBUTE,
            'value2',
            'ID'
        ]);
    }
    /**
     * Returns the system setup writer instance.
     */
    static getInstance() {
        if (SystemSetupWriter.instance === null)
            SystemSetupWriter.instance = new SystemSetupWriter();
        return SystemSetupWriter.instance;
    }
    setDefaultJtagProperties(connectionDefaults, connectionOverrides, jtagDefaults) {
        if (jtagDefaults === undefined) {
            // get first board, device, or cpu if it exists.
            const platformNode = connectionDefaults.getChildByName(HWDB.PLATFORM_TAG, 0);
            if (platformNode !== null) {
                const platform = new Tag(connectionDefaults, platformNode);
                this.setDefaultJtagPropertyForDevices(platform, connectionDefaults, connectionOverrides);
            }
        }
        else {
            // for all connection properties
            const nProperties = connectionDefaults.countChildrenByName(HWDB.PROPERTY_TAG);
            for (let i = 0; i < nProperties; i++) {
                const connectionDefault = new Tag(connectionDefaults, connectionDefaults.getChildByName(HWDB.PROPERTY_TAG, i));
                let idAttribute = HWDB.ID_ATTRIBUTE;
                let id = connectionDefault.getAttribute(idAttribute);
                if (id === null || id.length === 0) {
                    idAttribute = HWDB.PROPERTY_NAME_ATTRIBUTE;
                    id = connectionDefault.getAttribute(idAttribute);
                }
                // look for connection override, and if it exists we don't use jtag defaults.
                // jtag must be new schema so just look for id
                let jtagDefaultNode = jtagDefaults.getChildByID(HWDB.PROPERTY_TAG, id);
                if (jtagDefaultNode === null) {
                    // if not found, then look for property by jtag config parameter ID.
                    const ID = connectionDefault.getAttribute('ID');
                    if (ID !== null && ID.length > 0) {
                        jtagDefaultNode = jtagDefaults.getChildByID(HWDB.PROPERTY_TAG, ID, 'ID');
                        if (jtagDefaultNode === null) {
                            jtagDefaultNode = jtagDefaults.getChildByID(HWDB.PROPERTY_TAG, ID);
                        }
                    }
                }
                if (jtagDefaultNode !== null && connectionOverrides !== null) {
                    // found a jtag override
                    let connectionOverrideNode = connectionOverrides.getChildByID(HWDB.PROPERTY_TAG, id, idAttribute);
                    if (connectionOverrideNode === null) {
                        const jtagDefault = new Tag(jtagDefaults, jtagDefaultNode);
                        let value = jtagDefault.getAttribute(HWDB.VALUE_ATTRIBUTE);
                        const type = jtagDefault.getAttribute(HWDB.TYPE_ATTRIBUTE);
                        value = value.trim(); // get rid of spaces, then check if non-numeric choice index.
                        if (type.localeCompare(HWDB.CHOICE_TYPE) === 0 && isNaN(Number.parseInt(value.charAt(0)))) {
                            // not an index into the choice list, so lets find the appropriate index by matching values
                            const choice = connectionDefault.getChildIndexByID(HWDB.CHOICE_TAG, value, HWDB.CHOICE_VALUE_ATTRIBUTE);
                            if (choice < 0)
                                continue; // skip it if we can't match the choice selection
                            // convert index choice back to as string value.
                            value = choice.toString();
                        }
                        // no override so lets copy jtag defaults to connection defaults
                        connectionDefault.setAttribute(HWDB.VALUE_ATTRIBUTE, value);
                        connectionDefault.setAttribute(HWDB.TYPE_ATTRIBUTE, type);
                        // now copy jtag defaults to connection overrides
                        connectionOverrideNode = connectionOverrides.createChild(HWDB.PROPERTY_TAG, id, null);
                        const connectionOverride = new Tag(connectionOverrides, connectionOverrideNode);
                        connectionOverride.setAttribute(HWDB.VALUE_ATTRIBUTE, value);
                        connectionOverride.setAttribute(HWDB.TYPE_ATTRIBUTE, type);
                        // check if choicelist property
                        if (type.localeCompare(HWDB.CHOICE_TYPE) === 0) {
                            const choice = connectionDefault.getAttributeInteger(HWDB.VALUE_ATTRIBUTE);
                            const connectionDefaultChoiceNode = connectionDefault.getChildByName(HWDB.CHOICE_TAG, choice);
                            if (connectionDefaultChoiceNode !== null) {
                                const connectionDefaultChoice = new Tag(connectionDefault, connectionDefaultChoiceNode);
                                // find Jtag default choice
                                idAttribute = HWDB.PROPERTY_NAME_ATTRIBUTE;
                                id = connectionDefaultChoice.getAttribute(idAttribute);
                                if (id === null || id.length === 0) {
                                    idAttribute = HWDB.CHOICE_VALUE_ATTRIBUTE;
                                    id = connectionDefaultChoice.getAttribute(idAttribute);
                                }
                                const jtagDefaultChoiceNode = jtagDefault.getChildByID(HWDB.CHOICE_TAG, id, idAttribute);
                                if (jtagDefaultChoiceNode !== null) {
                                    const jtagDefaultChoice = new Tag(jtagDefault, jtagDefaultChoiceNode);
                                    if (jtagDefaultChoice.countChildrenByName(HWDB.PROPERTY_TAG) > 0) {
                                        // create override choice
                                        const connectionOverrideChoice = new Tag(connectionOverride, connectionOverride.createChild(HWDB.CHOICE_TAG, null, null));
                                        connectionOverrideChoice.copyAttribute(connectionDefaultChoice, HWDB.CHOICE_VALUE_ATTRIBUTE);
                                        connectionOverrideChoice.copyAttribute(connectionDefaultChoice, HWDB.PROPERTY_NAME_ATTRIBUTE);
                                        // recursively copy sub-properties
                                        this.setDefaultJtagProperties(connectionDefaultChoice, connectionOverrideChoice, jtagDefaultChoice);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    setDefaultJtagPropertyForDevices(parent, connectionDefaults, connectionOverrides) {
        if (parent !== null) {
            let deviceNode = parent.getFirstChild();
            while (deviceNode !== null) {
                const device = new Tag(parent, deviceNode);
                const jtagNode = device.getChildByName(HWDB.JTAG_TAG, 0);
                if (jtagNode !== null) {
                    // we have overrides.  Now we need to determine if they are appropriate to set
                    this.setDefaultJtagProperties(connectionDefaults, connectionOverrides, new Tag(device, jtagNode));
                }
                this.setDefaultJtagPropertyForDevices(device, connectionDefaults, connectionOverrides);
                deviceNode = deviceNode.nextSibling ?? null;
            }
        }
    }
    static createUniqueNames(parent, flatRootNode, rootNode, existingNames) {
        if (parent.nodeName === 'connection') {
            existingNames = [];
        }
        for (let child = this.getFirstVisibleChild(parent); child !== null; child = XMLParser.GetNextSibling(child)) {
            if (child.nodeName === 'cpu') {
                let childName = XMLParser.GetAttributeString(child, HWDB.NAME_ATTRIBUTE);
                if (childName === null || childName.length === 0) {
                    childName = XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE);
                }
                if (childName !== null && childName.length > 0) {
                    let nameChanged = false;
                    while (existingNames.includes(childName.toLowerCase())) {
                        // create unique name
                        childName = this.generateUniqueString(childName);
                        nameChanged = true;
                    }
                    if (nameChanged) {
                        // set new name in flat file
                        const flatNode = new Tag(flatRootNode, child);
                        flatNode.setAttribute(HWDB.NAME_ATTRIBUTE, childName);
                        // set in top level system setup xml file as well.
                        const topLevelNode = this.gotoNode(flatNode, flatRootNode, rootNode, true);
                        topLevelNode?.setAttribute(HWDB.NAME_ATTRIBUTE, childName);
                    }
                    existingNames.push(childName.toLowerCase());
                }
            }
            this.createUniqueNames(child, flatRootNode, rootNode, existingNames);
        }
    }
    static createUniqueId(parent, name, existingNames) {
        while (parent.getChildByID(null, name) !== null || existingNames?.includes(name.toLowerCase())) {
            name = this.generateUniqueString(name);
        }
        existingNames?.push(name.toLowerCase());
        return name;
    }
    static generateUniqueString(name) {
        const pos = name.lastIndexOf('_');
        if (pos > 0) {
            // may have an existing suffix
            const suffix = name.substring(pos + 1);
            if (!isNaN(+suffix)) {
                // numeric suffix
                return `${name.substring(0, pos)}_${+suffix + 1}`;
            }
            else if (suffix.length === 1) {
                // it wasn't a number, and it is only one character.
                const lastCh = suffix.charAt(0);
                let lastChCode = suffix.charCodeAt(0);
                if ((lastCh < 'Z' && lastCh >= 'A') || (lastCh < 'z' && lastCh >= 'a')) {
                    return `${name.substring(0, pos)}_${String.fromCharCode(++lastChCode)}`; // increment alpha suffix
                }
            }
        }
        // default case, start a new numeric suffix
        return `${name}_0`;
    }
    static gotoNode(flatNode, flatRootNode, rootNode, createNode) {
        if (flatNode.getNode() === flatRootNode.getNode()) {
            return rootNode;
        }
        const parentNode = flatNode.getParent(null);
        const parentTag = parentNode && this.gotoNode(new Tag(flatNode, parentNode), flatRootNode, rootNode, createNode);
        if (parentTag === null)
            return null;
        const nodeName = flatNode.getName();
        let idAttribute;
        const isChoiceTag = nodeName.localeCompare(HWDB.CHOICE_TAG) === 0;
        if (isChoiceTag) {
            idAttribute = HWDB.PROPERTY_NAME_ATTRIBUTE;
            const propName = flatNode.getAttribute(idAttribute);
            if (propName === null || propName.length === 0) {
                idAttribute = HWDB.CHOICE_VALUE_ATTRIBUTE;
            }
        }
        else {
            idAttribute = HWDB.ID_ATTRIBUTE;
        }
        const id = flatNode.getAttribute(idAttribute);
        let child = parentTag.getChildByID(nodeName, id, idAttribute);
        if (createNode === false && child === null)
            return null;
        if (child === null) {
            // determine if a version is required
            let version = flatNode.getAttribute(HWDB.VER_ATTRIBUTE);
            if (version !== null && version.length > 0) {
                // if so, then use latest version, don't copy for flat child.
                version = HWDB.VERSION;
            }
            else {
                version = null;
            }
            child = parentTag.createChild(nodeName, null, version);
            // copy attributes that may be required
            const childTag = new Tag(parentTag, child);
            childTag.setAttribute(idAttribute, id);
            childTag.copyAttribute(flatNode, HWDB.PARTNUM_ATTRIBUTE);
            childTag.copyAttribute(flatNode, HWDB.HW_REV_ATTRIBUTE);
            childTag.copyAttribute(flatNode, HWDB.ISA_ATTRIBUTE);
            childTag.copyAttribute(flatNode, HWDB.TYPE_ATTRIBUTE);
            childTag.copyAttribute(flatNode, HWDB.DESCRIPTION_ATTRIBUTE);
            if (isChoiceTag) {
                childTag.copyAttribute(flatNode, HWDB.CHOICE_VALUE_ATTRIBUTE);
                childTag.copyAttribute(flatNode, HWDB.PROPERTY_NAME_ATTRIBUTE);
            }
            else {
                childTag.copyAttribute(flatNode, HWDB.VALUE_ATTRIBUTE);
            }
        }
        return new Tag(parentTag, child);
    }
    static getComponentNames(parentNode, flatRootNodeOrElementNames, recursive) {
        const result = new Array();
        if (parentNode instanceof Tag && flatRootNodeOrElementNames instanceof Tag) {
            const flatRootNode = flatRootNodeOrElementNames;
            const parent = parentNode;
            const connection = parent.getParent(HWDB.CONNECTION_TAG);
            this.getComponentNames(connection === null ? flatRootNode?.getNode() ?? null : connection, result, connection !== null);
        }
        else {
            const elementNames = flatRootNodeOrElementNames;
            const parent = parentNode;
            for (let child = this.getFirstVisibleChild(parent); child !== null; child = this.getNextVisibleChild(child)) {
                let childName = XMLParser.GetAttributeString(child, HWDB.NAME_ATTRIBUTE);
                if (childName === null || childName.length === 0) {
                    childName = XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE);
                }
                if (childName !== null && childName.length > 0) {
                    elementNames.push({ type: child.nodeName, name: childName.toLowerCase() });
                }
                if (recursive) {
                    this.getComponentNames(child, elementNames, true);
                }
            }
        }
        return result;
    }
    static getFirstVisibleChild(parent) {
        return this.findNextVisibleChild(parent, XMLParser.GetFirstChild(parent));
    }
    static getNextVisibleChild(child) {
        if (child !== null) {
            child = this.findNextVisibleChild(child.parentNode ?? null, child.nextSibling ?? null);
        }
        return child;
    }
    static findNextVisibleChild(parent, child) {
        // eslint-disable-next-line no-constant-condition
        while (true) {
            if (child !== null) {
                if (nodesToShow.has(child.nodeName)) {
                    break; // found it
                }
                else if (nodesToSuppress.has(child.nodeName)) {
                    // go in one level
                    parent = child;
                    child = XMLParser.GetFirstChild(parent);
                }
                else {
                    // ignore it and go to next sibling
                    child = child.nextSibling ?? null;
                }
            }
            else if (parent !== null && nodesToSuppress.has(parent.nodeName)) {
                // go up one level if no more siblings and parent was suppressed.
                child = parent.nextSibling ?? null;
                parent = parent.parentNode ?? null;
            }
            else { // parent not suppressed and no more siblings
                break; // child = null;
            }
        }
        return child;
    }
    addDeviceDriver(connection, relDriverXmlFile) {
        // insert before connectionType, drivers, or platform which ever exists in that order.
        const insertBefore = connection.getChildByName(HWDB.CONNECTION_TYPE_TAG, 0) ??
            connection.getChildByName(HWDB.PROPERTY_TAG, 0) ??
            connection.getChildByName(HWDB.DRIVERS_TAG, 0) ??
            connection.getChildByName(HWDB.PLATFORM_TAG, 0) ??
            undefined;
        HardwareDatabaseReader.includeFile(connection, relDriverXmlFile, HWDB.DRIVERS_TAG, null, insertBefore);
    }
    async addDeviceDrivers(connection, connectionName, boardOrDevice) {
        if (boardOrDevice.type === 'connection') {
            return;
        }
        const targetConfig = ServicesRegistry.getService(targetConfigServiceType);
        const ccxmlText = await targetConfig.getConfig(connectionName, boardOrDevice.id);
        function reduce(result, element) {
            for (let child = element?.firstChild; child; child = child.nextSibling) {
                if (child.nodeType === NodeTypes.ELEMENT_NODE) {
                    if (child.nodeName === HWDB.INSTANCE_TAG && child.attributes?.getNamedItem(HWDB.XMLPATH_ATTRIBUTE)?.value === HWDB.DRIVERS_TAG) {
                        const href = child.attributes?.getNamedItem(HWDB.HREF_ATTRIBUTE);
                        if (!href) {
                            throw Error('Missing href attribute from driver <instance> tag.');
                        }
                        result.push(href.value);
                    }
                    else {
                        reduce(result, child);
                    }
                }
            }
            return result;
        }
        const document = targetConfig.parseConfig(ccxmlText);
        const driverXmlFiles = reduce([], document.documentElement);
        if (driverXmlFiles.length === 0) {
            throw Error('Device or Board does not contain any debuggable CPU\'s\nPlease select a different device or board');
        }
        driverXmlFiles.forEach(driverXmlFile => {
            this.addDeviceDriver(connection, driverXmlFile);
        });
    }
}

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
const nullTreeDataProvider = new (class {
    constructor() {
        this.rowCount = 0;
    }
    setValue() { }
    getValue() {
        return;
    }
    isExpandable() {
        return false;
    }
    getChildDataProvider(row) {
        return nullTreeDataProvider;
    }
})();
class TreeElement {
    constructor(id, item, parent, systemSetup) {
        this.systemSetup = systemSetup;
        this.item = item;
        this.parent = parent;
        this._children = null;
        this.id = (id === null ? '' : id);
    }
    get children() {
        if (this._children === null) {
            const childNodes = this.systemSetup.getChildNodes(this.item);
            this._children = childNodes.map(node => {
                const childID = XMLParser.GetAttributeString(node, HWDB.ID_ATTRIBUTE);
                return new TreeElement(childID, node, this, this.systemSetup);
            });
        }
        return this._children;
    }
    updateChildren() {
        this._children = null;
    }
    getParent() {
        return this.parent;
    }
    getErrorLocation() {
        if (this.parent !== null) {
            const type = XMLParser.GetName(this.item);
            if (type.localeCompare(HWDB.CPU_TAG) === 0 || type.localeCompare(HWDB.SUBPATH_TAG) === 0
                || type.localeCompare(HWDB.ROUTER_TAG) === 0) {
                // get connection name
                let parentConnection = this;
                for (; parentConnection !== null; parentConnection = parentConnection.getParent()) {
                    const type = XMLParser.GetName(parentConnection.item);
                    if (type.localeCompare(HWDB.CONNECTION_TAG) === 0) {
                        const location = new StringBuilder();
                        location.append(TreeElement.getLabel(parentConnection.item, this.systemSetup));
                        location.append('\\');
                        location.append(TreeElement.getLabel(this.item, this.systemSetup));
                        return location.toString();
                    }
                }
            }
            else if (type.localeCompare(HWDB.CONNECTION_TAG) === 0) {
                return TreeElement.getLabel(this.item, this.systemSetup);
            }
        }
        return null;
    }
    getName() {
        return TreeElement.getLabel(this.item, this.systemSetup);
    }
    static getLabel(item, systemSetup) {
        let label = '';
        if (item !== null) {
            const node = new Tag(systemSetup.flatRootNode, item);
            label = node.getAttribute(HWDB.NAME_ATTRIBUTE);
            if (label === null || label.length === 0) {
                label = node.getAttribute(HWDB.ID_ATTRIBUTE);
            }
        }
        return label;
    }
    getDecoratorText() {
        if (this.item !== null) {
            const node = new Tag(this.systemSetup.flatRootNode, this.item);
            const name = node.getName();
            if (name.localeCompare(HWDB.CPU_TAG) === 0) {
                if (node.getName().localeCompare(HWDB.CPU_TAG) === 0) {
                    if (node.getPropertyString(HWDB.BYPASS_PROPERTY, '0').localeCompare('1') === 0) {
                        return 'bypassed';
                    }
                }
            }
        }
        const iconName = this.systemSetup.getIconNameToDisplay(this);
        if (iconName.includes('bypass')) {
            return 'bypassed';
        }
        return null;
    }
    findElement(node) {
        let found = null;
        if (this.item === node)
            return this;
        if (this.children !== null && this.children.length > 0) {
            for (let i = this.children.length; i-- > 0 && found === null;) {
                found = this.children[i].findElement(node);
            }
        }
        return found;
    }
    findElementByPath(path) {
        if (!path) {
            return this;
        }
        return path.split('/').reduce((result, segment) => {
            if (!result) {
                return result;
            }
            const row = result.lookupRowByName(segment);
            return result.children[row] ?? null;
        }, this);
    }
    toString() {
        let result = null;
        if (this.item !== null) {
            result = XMLParser.GetAttributeString(this.item, HWDB.NAME_ATTRIBUTE);
        }
        if (result === null || result.length === 0) {
            result = this.id;
        }
        return result === null ? '' + this : result;
    }
    get rowCount() {
        return this.children.length;
    }
    getValue(childIndex, column) {
        const child = this.children[childIndex];
        if (!child) {
            return '';
        }
        const decoratorText = column === 'name' ? undefined : child.getDecoratorText();
        if (decoratorText) {
            return `${child.getName()} (${decoratorText})`;
        }
        return child.getName();
    }
    setValue(childIndex, column, value) {
    }
    isExpandable(childIndex) {
        const child = this.children[childIndex];
        if (!child) {
            return false;
        }
        return child.children.length > 0;
    }
    getChildDataProvider(childIndex) {
        const child = this.children[childIndex];
        if (!child) {
            return nullTreeDataProvider;
        }
        return child;
    }
    lookupRowByName(name) {
        return this.children.findIndex(child => child.getName() === name) ?? -1;
    }
    getIconName(childIndex) {
        const iconMap = {
            subpath: 'action:timeline',
            cpu: 'hardware:computer',
            core: 'hardware:computer',
            bypass: 'hardware:computer',
            board: 'hardware:developer_board',
            nondebug: 'av:play_disabled',
            router: 'hardware:device_hub',
            bypass_router: 'hardware:device_hub',
            connection: 'content:link',
            device: 'hardware:memory'
        };
        const child = this.children[childIndex];
        const iconName = child ? this.systemSetup.getIconNameToDisplay(child) : 'nondebug';
        return iconMap[iconName] ?? '';
    }
}
class AbstractProperty {
    constructor(descriptor, name = null) {
        this.descriptor = descriptor;
        this.name = name;
        this.description = '';
        this.toolTip = null;
    }
    getName() {
        return this.name === null ? this.description : this.name;
    }
    get caption() {
        return this.description ?? this.id;
    }
    get id() {
        return this.name ?? undefined;
    }
    get infoText() {
        return this.toolTip ?? undefined;
    }
    get errorText() {
        return this.descriptor.getPropertyError() ?? undefined;
    }
    get label() {
        return undefined;
    }
}
class TextProperty extends AbstractProperty {
    constructor() {
        super(...arguments);
        this.widgetType = 'input';
        this.format = 'text';
    }
}
class DropListProperty extends AbstractProperty {
    constructor(property, propStruct, name, nChoices) {
        super(propStruct);
        this.choices = [];
        this.initialValue = '';
        this.isBoolean = false;
        let hasSubProperties = false;
        this.description = name;
        if (nChoices > 0) {
            this.choices = new Array(nChoices);
        }
        for (let j = 0; j < nChoices; j++) {
            const choice = new Tag(property, property.getChildByName(HWDB.CHOICE_TAG, j));
            let value = choice.getAttribute(HWDB.PROPERTY_NAME_ATTRIBUTE);
            if (value === null || value.length === 0) {
                value = choice.getAttribute(HWDB.CHOICE_VALUE_ATTRIBUTE);
            }
            this.choices[j] = value;
            // determine if there are sub properties associated with this drop list property.
            let child = choice.getFirstChild();
            while (child !== null && hasSubProperties === false) {
                const tag = XMLParser.GetName(child);
                if (tag.localeCompare(HWDB.PROPERTY_TAG) === 0 || tag.localeCompare(HWDB.CHOICELIST_TAG) === 0) {
                    hasSubProperties = true;
                }
                else if (tag.localeCompare(HWDB.INFERENCE_TAG) === 0) {
                    const key = XMLParser.GetAttributeString(child, HWDB.KEY_ATTRIBUTE);
                    if (key.localeCompare(HWDB.ADVICE_ATTRIBUTE) === 0 || key.localeCompare(HWDB.SUMMARY_ATTRIBUTE) === 0)
                        hasSubProperties = true;
                }
                child = child.nextSibling ?? null;
            }
        }
        if (nChoices > 0) {
            this.initialValue = this.choices[0];
        }
        propStruct.setHasSubProperties(hasSubProperties);
        if (this.choices.length === 2) {
            const choice1 = this.choices[0].toLowerCase();
            const choice2 = this.choices[1].toLowerCase();
            if ((choice1 === 'yes' && choice2 === 'no') || (choice1 === 'no' && choice2 === 'yes')) {
                this.isBoolean = true;
            }
        }
    }
    getDefaultChoiceLabel() {
        return this.getDefaultChoiceValue();
    }
    getDefaultChoiceValue() {
        return this.initialValue;
    }
    get widgetType() {
        return this.isBoolean ? 'checkbox' : 'select';
    }
    get format() {
        return this.isBoolean ? 'boolean' : 'text';
    }
    get caption() {
        return this.isBoolean ? '' : super.caption;
    }
    get label() {
        return this.isBoolean ? super.caption : undefined;
    }
    get options() {
        return this.isBoolean ? undefined : this.choices;
    }
}
class FileProperty extends AbstractProperty {
    constructor() {
        super(...arguments);
        this.extensions = [];
        this.extensionNames = [];
        this.widgetType = 'input'; // TODO: support for file type in property view.
        this.format = 'text';
    }
    setExtensions(extensionAttribute) {
        if (extensionAttribute !== null && extensionAttribute.length > 0) {
            const exts = extensionAttribute.split(/[,;|]/);
            if (exts !== null && exts.length > 0) {
                const nExts = Math.floor(exts.length / 2);
                if (nExts === 0) {
                    this.extensions = new Array(1);
                    this.extensions[0] = exts[0];
                }
                else {
                    this.extensionNames = new Array(nExts);
                    this.extensions = new Array(nExts);
                    for (let j = 0; j < nExts; j++) {
                        this.extensionNames[j] = exts[2 * j];
                        this.extensions[j] = exts[2 * j + 1];
                    }
                }
            }
        }
    }
}
class NumberProperty extends AbstractProperty {
    constructor() {
        super(...arguments);
        this.upperbound = 0;
        this.lowerbound = 0;
        this.widgetType = 'input';
        this.precision = 0;
    }
    get format() {
        const value = +this.descriptor.getProperty();
        if (isNaN(value) || value < -100 || value > 100) {
            return 'hex';
        }
        return 'dec';
    }
    get minValue() {
        return this.lowerbound;
    }
    get maxValue() {
        return this.upperbound;
    }
    get infoText() {
        if (this.toolTip) {
            return this.toolTip;
        }
        function toHexString(value) {
            if (isNaN(value) || (value >= -100 && value <= 100)) {
                return value.toString();
            }
            const result = value.toString(16);
            if (result.startsWith('-')) {
                return '-0x' + result.substring(1);
            }
            return '0x' + result;
        }
        return `Enter a number between ${toHexString(this.lowerbound)} and ${toHexString(this.upperbound)}`;
    }
}
class InfoBoxProperty extends AbstractProperty {
    constructor(title, content, image) {
        super(new InfoBoxPropertyDescriptor(content), '');
        this.content = content;
        this.disabled = true;
        this.format = 'text';
        this.widgetType = 'input';
        this.description = title;
        this.imageFileName = image;
    }
}
class APropertyDescriptor {
    constructor() {
        this.fireEvent = false;
    }
    hasSubProperties() {
        return this.fireEvent;
    }
    setHasSubProperties(hasSubProperties) {
        this.fireEvent = hasSubProperties;
    }
    getPropertyError() {
        return null;
    }
    isFilePathProperty() {
        return false;
    }
    isReadOnly() {
        return false;
    }
}
class InfoBoxPropertyDescriptor extends APropertyDescriptor {
    constructor(content) {
        super();
        this.content = content;
    }
    setProperty(value) {
        throw new Error('Method not implemented.');
    }
    getProperty() {
        return this.content;
    }
    setHasSubProperties(hasSubProperties) {
        throw new Error('Method not implemented.');
    }
    getValueAttributeName() {
        throw new Error('Method not implemented.');
    }
    isReadOnly() {
        return true;
    }
}
class BypassBitsPropertyDescriptor extends APropertyDescriptor {
    constructor(node, rootNode) {
        super();
        this.node = node;
        this.root = rootNode;
    }
    getProperty() {
        return SystemSetupEditor.getBypassBits(this.node).toString();
    }
    setProperty(value) {
        SystemSetupEditor.setBypassBits(this.node, this.root, +value);
        return this.node;
    }
    getValueAttributeName() {
        return HWDB.ISA_ATTRIBUTE;
    }
    isFilePathProperty() {
        return false;
    }
    isReadOnly() {
        return false;
    }
}
class PropertyDescriptor extends APropertyDescriptor {
    constructor(defaultProperty, overriddenProperty, overrideParent, parentProperty, isChoiceList) {
        super();
        this.simulationProperty = false;
        this.defaultProperty = defaultProperty;
        this.overriddenProperty = overriddenProperty;
        this.overrideParent = overrideParent;
        this.parentProperty = parentProperty;
        this.choiceListProperty = isChoiceList;
    }
    createDefaultProperty() {
        if (this.overriddenProperty === null) {
            if (this.overrideParent === null) {
                this.overrideParent = this.parentProperty.createDefaultProperty();
                // must create a Choice tag between properties
                const defaultParentNode = this.defaultProperty.getParent(null) ?? null;
                this.overrideParent = new Tag(this.overrideParent, this.overrideParent.createChild(HWDB.CHOICE_TAG, null, null));
                this.overrideParent.setAttribute(HWDB.CHOICE_VALUE_ATTRIBUTE, XMLParser.GetAttributeString(defaultParentNode, HWDB.CHOICE_VALUE_ATTRIBUTE));
                const name = XMLParser.GetAttributeString(defaultParentNode, HWDB.PROPERTY_NAME_ATTRIBUTE);
                if (name !== null && name.length > 0) {
                    this.overrideParent.setAttribute(HWDB.PROPERTY_NAME_ATTRIBUTE, name);
                }
            }
            this.overriddenProperty = new Tag(this.overrideParent, this.overrideParent.createChild(HWDB.PROPERTY_TAG, null, null));
            // copy necessary attributes from default properties
            this.overriddenProperty.setAttribute(HWDB.ID_ATTRIBUTE, this.defaultProperty.getAttribute(this.simulationProperty ? HWDB.KEY_ATTRIBUTE : HWDB.ID_ATTRIBUTE));
            if (!this.simulationProperty) {
                this.overriddenProperty.setAttribute('ID', this.defaultProperty.getAttribute('ID'));
                this.overriddenProperty.setAttribute(HWDB.VALUE_ATTRIBUTE, this.defaultProperty.getAttribute(HWDB.VALUE_ATTRIBUTE));
            }
            const type = this.simulationProperty ? HWDB.STRING_TYPE : this.defaultProperty.getAttribute(HWDB.TYPE_ATTRIBUTE);
            this.overriddenProperty.setAttribute(HWDB.TYPE_ATTRIBUTE, type);
        }
        return this.overriddenProperty;
    }
    setProperty(value, setIndexForChoice = false) {
        this.createDefaultProperty();
        let valueToWrite = null;
        if (this.choiceListProperty && !this.simulationProperty) {
            valueToWrite = '0';
            for (let i = this.defaultProperty.countChildrenByName(HWDB.CHOICE_TAG); i-- > 0;) {
                if (setIndexForChoice) {
                    if (i.toString() === value.toString()) {
                        valueToWrite = value.toString();
                        break;
                    }
                }
                else {
                    const choice = this.defaultProperty.getChildByName(HWDB.CHOICE_TAG, i);
                    let val = XMLParser.GetAttributeString(choice, HWDB.PROPERTY_NAME_ATTRIBUTE);
                    if (val === null || val.length === 0) {
                        val = XMLParser.GetAttributeString(choice, HWDB.CHOICE_VALUE_ATTRIBUTE);
                    }
                    if (val !== null && val.localeCompare(value.toString()) === 0) {
                        valueToWrite = i.toString();
                        break;
                    }
                }
            }
        }
        if (valueToWrite === null) {
            valueToWrite = value.toString();
        }
        this.overriddenProperty?.setAttribute(HWDB.VALUE_ATTRIBUTE, valueToWrite);
        return this.overriddenProperty;
    }
    getProperty(getIndexForChoice = false) {
        let value = null;
        if (this.overriddenProperty !== null) {
            value = this.overriddenProperty.getAttribute(HWDB.VALUE_ATTRIBUTE);
        }
        else {
            value = this.defaultProperty.getAttribute(this.simulationProperty ? HWDB.CHOICE_VALUE_ATTRIBUTE
                : HWDB.VALUE_ATTRIBUTE);
        }
        if (!this.simulationProperty && this.choiceListProperty) {
            let index;
            try {
                index = +value;
            }
            catch (e) {
                index = 0;
            }
            if (index < 0 || index >= this.defaultProperty.countChildrenByName(HWDB.CHOICE_TAG)) {
                index = 0;
            }
            if (getIndexForChoice) {
                value = index.toString();
            }
            else {
                const choice = this.defaultProperty.getChildByName(HWDB.CHOICE_TAG, index);
                value = XMLParser.GetAttributeString(choice, HWDB.PROPERTY_NAME_ATTRIBUTE);
                if (value === null || value.length === 0) {
                    value = XMLParser.GetAttributeString(choice, HWDB.CHOICE_VALUE_ATTRIBUTE);
                }
            }
        }
        return value;
    }
    getValueAttributeName() {
        return HWDB.VALUE_ATTRIBUTE;
    }
    static isDuplicateProperty(override, properties) {
        if (override === null)
            return false;
        for (let i = 0; i < properties.length; i++) {
            const id = properties[i].descriptor;
            if (id instanceof PropertyDescriptor) {
                const overrideProperty = id.overriddenProperty;
                if (overrideProperty !== null && overrideProperty.getNode() === override)
                    return true;
            }
        }
        return false;
    }
    isFilePathProperty() {
        const type = this.defaultProperty.getAttribute(HWDB.TYPE_ATTRIBUTE);
        return type.localeCompare(HWDB.FILE_TYPE) === 0 || type.localeCompare(HWDB.FILE_PATH_TYPE) === 0;
    }
    isReadOnly() {
        return false;
    }
}
class SimulationPropertyDescriptor extends PropertyDescriptor {
    constructor(driverProperty, defaultPropertyValue, overriddenProperty, overrideParent) {
        super(defaultPropertyValue, overriddenProperty, overrideParent, null, false);
        this.simulationProperty = true;
        this.driverProperty = driverProperty;
    }
    getBoardName() {
        if (this.driverProperty !== null) {
            const defaults = this.defaultProperty.getParent(null) ?? null;
            if (defaults !== null) {
                return SimulationPropertyDescriptor.getBoardName(new Tag(this.defaultProperty, defaults), this.overrideParent, this.driverProperty);
            }
        }
        return null;
    }
    static getBoardName(defaults, overrides, property) {
        const type = property.getAttribute(HWDB.DRIVER_TYPE_ATTRIBUTE);
        if (type.localeCompare(HWDB.STRING_LIST_TYPE) === 0) {
            const name = property.getAttribute(HWDB.ID_ATTRIBUTE);
            let overriddenProperty = null;
            if (overrides !== null) {
                overriddenProperty = overrides.getChildByID(HWDB.PROPERTY_TAG, name);
            }
            let value = null;
            if (overriddenProperty !== null) {
                value = XMLParser.GetAttributeString(overriddenProperty, HWDB.VALUE_ATTRIBUTE);
            }
            else {
                const defaultProperty = defaults.getChildByID(HWDB.CURRENT_CHOICE_TAG, name, HWDB.KEY_ATTRIBUTE);
                if (defaultProperty !== null) {
                    value = XMLParser.GetAttributeString(defaultProperty, HWDB.CHOICE_VALUE_ATTRIBUTE);
                }
            }
            if (value !== null && value.length > 0) {
                const currentChoice = property.getChildByID(HWDB.CHOICE_TAG, value, HWDB.CHOICE_VALUE_ATTRIBUTE);
                if (currentChoice !== null) {
                    const choice = new Tag(property, currentChoice);
                    const nInferences = choice.countChildrenByName(HWDB.INFERENCE_TAG);
                    for (let i = 0; i < nInferences; i++) {
                        const inference = choice.getChildByName(HWDB.INFERENCE_TAG, i);
                        const key = XMLParser.GetAttributeString(inference, HWDB.KEY_ATTRIBUTE);
                        if (key !== null && key.localeCompare('FixedEntry') === 0) {
                            const val = XMLParser.GetAttributeString(inference, HWDB.CHOICE_VALUE_ATTRIBUTE);
                            if (val !== null && val.localeCompare('BOARDNAME') === 0) {
                                return XMLParser.GetAttributeString(inference, 'value2');
                            }
                        }
                    }
                    const nProperties = choice.countChildrenByName(HWDB.CHOICELIST_TAG);
                    for (let i = 0; i < nProperties; i++) {
                        const subProperty = new Tag(choice, choice.getChildByName(HWDB.CHOICELIST_TAG, i));
                        // recursively look in sub-properties to find board name
                        const boardName = SimulationPropertyDescriptor.getBoardName(defaults, overrides, subProperty);
                        if (boardName !== null && boardName.length > 0) {
                            return boardName;
                        }
                    }
                }
            }
        }
        return null;
    }
}
class SystemSetupEditor extends SystemSetupWriter {
    constructor() {
        super();
        this.errorReports = null;
        this.fileName = '';
        this.xmlReader.addAttributesToFilter([HWDB.COMPONENT_NAME, HWDB.XML_ATTRIBUTE]);
        // create configurations tag
        const xmlParser = new XMLParser();
        const root = xmlParser.CreateNewDocument(HWDB.CONFIGURATIONS_TAG);
        xmlParser.SetAttribute(root, HWDB.VER_ATTRIBUTE, HWDB.VERSION);
        xmlParser.SetAttribute(root, HWDB.ID_ATTRIBUTE, 'configurations_0');
        this.flatRootNode = new Tag(xmlParser, root);
        const xmlParser1 = new XMLParser();
        const root1 = xmlParser1.CreateNewDocument(HWDB.CONFIGURATIONS_TAG);
        xmlParser1.SetAttribute(root1, HWDB.VER_ATTRIBUTE, HWDB.VERSION);
        xmlParser1.SetAttribute(root1, HWDB.ID_ATTRIBUTE, 'configurations_0');
        this.rootNode = new Tag(xmlParser1, root1);
        this.rootTreeElement = new TreeElement(null, this.flatRootNode.getNode(), null, this);
    }
    async load(xmlInput, fileName, isCancelled) {
        this.fileName = fileName;
        const rootDirectories = SystemSetupReader.getRootDirectories();
        this.rootNode = await this.xmlReader.parseConfig(xmlInput, rootDirectories, SystemSetupReader.getSchemaDirectory());
        this.flatRootNode = await this.xmlReader.convertToFlatFile(this.rootNode, fileName, rootDirectories, isCancelled);
        this.rootTreeElement = new TreeElement(null, this.flatRootNode.getNode(), null, this);
        // recalculate error messages and test that something has changed
        this.generateErrorReports();
    }
    async loadFlatConfig(fileName) {
        return this.xmlReader.loadFlatConfig(fileName, SystemSetupReader.getRootDirectories(), SystemSetupReader.getSchemaDirectory());
    }
    static isLegacyProperty(id) {
        return id.localeCompare('portAddr1') === 0 || id.localeCompare('portAddr2') === 0
            || id.localeCompare('irq') === 0 || id.localeCompare('dma') === 0
            || id.localeCompare('driver') === 0 || id.localeCompare('dataFile') === 0;
    }
    addProperties(defaultNode, overrideNode, properties, excludeHiddenProperty, subPathPropertiesOnly, parentProperty) {
        const n = defaultNode.countChildrenByName(HWDB.PROPERTY_TAG);
        for (let i = 0; i < n; i++) {
            const property = defaultNode.getChildByName(HWDB.PROPERTY_TAG, i);
            const subpathAttr = XMLParser.GetAttributeString(property, HWDB.SUBPATH_ATTRIBUTE);
            if (subpathAttr !== null && (subpathAttr.localeCompare('true') === 0 ? subPathPropertiesOnly : !subPathPropertiesOnly)) {
                const defaultProperty = new Tag(defaultNode, property);
                let id = defaultProperty.getAttribute(HWDB.ID_ATTRIBUTE);
                if (id === null || id.length === 0) {
                    id = defaultProperty.getAttribute('ID');
                }
                let name = defaultProperty.getAttribute(HWDB.PROPERTY_NAME_ATTRIBUTE);
                if (name === null || name.length === 0) {
                    name = defaultProperty.getAttribute(HWDB.NAME_ATTRIBUTE);
                }
                if (name === null || name.length === 0) {
                    name = id;
                }
                const overriddenPropertyNode = overrideNode === null ? null : overrideNode.getChildByID(HWDB.PROPERTY_TAG, id);
                if (PropertyDescriptor.isDuplicateProperty(overriddenPropertyNode, properties)
                    || SystemSetupEditor.isLegacyProperty(name)) {
                    continue;
                }
                const overriddenProperty = overriddenPropertyNode === null ? null : new Tag(overrideNode, overriddenPropertyNode);
                // get type of property and allow override to change the type (to hidden for example).
                let type = overriddenProperty === null ? null : overriddenProperty.getAttribute(HWDB.TYPE_ATTRIBUTE);
                if (type === null || type.length === 0) {
                    type = defaultProperty.getAttribute(HWDB.TYPE_ATTRIBUTE);
                }
                const propStruct = new PropertyDescriptor(defaultProperty, overriddenProperty, overrideNode, parentProperty, type.localeCompare(HWDB.CHOICE_TYPE) === 0);
                if (type.localeCompare(HWDB.STRING_TYPE) === 0) {
                    const prop = new TextProperty(propStruct, id);
                    prop.description = name;
                    prop.toolTip = defaultProperty.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
                    properties.push(prop);
                }
                else if (type.localeCompare(HWDB.INTEGER_TYPE) === 0) {
                    const prop = new NumberProperty(propStruct, id);
                    prop.description = name;
                    prop.toolTip = defaultProperty.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
                    prop.upperbound = defaultProperty.getAttributeInteger(HWDB.UPPER_BOUND_ATTRIBUTE, Number.MAX_SAFE_INTEGER);
                    prop.lowerbound = defaultProperty.getAttributeInteger(HWDB.LOWER_BOUND_ATTRIBUTE, Number.MIN_SAFE_INTEGER);
                    properties.push(prop);
                }
                else if (type.localeCompare(HWDB.FILE_TYPE) === 0) {
                    const prop = new FileProperty(propStruct, id);
                    prop.description = name;
                    prop.toolTip = defaultProperty.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
                    prop.setExtensions(defaultProperty.getAttribute(HWDB.EXTENSIONS_ATTRIBUTE));
                    properties.push(prop);
                }
                else if (type.localeCompare(HWDB.CHOICE_TYPE) === 0) {
                    const nChoices = defaultProperty.countChildrenByName(HWDB.CHOICE_TAG);
                    if (nChoices > 0) {
                        const prop = new DropListProperty(defaultProperty, propStruct, name, nChoices);
                        prop.toolTip = defaultProperty.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
                        prop.name = id;
                        properties.push(prop);
                        // look for dynamic properties associated with the current selection
                        let curChoice = (overriddenProperty === null ? defaultProperty : overriddenProperty)
                            .getAttributeInteger(HWDB.VALUE_ATTRIBUTE);
                        if (curChoice < 0 || curChoice >= nChoices) {
                            curChoice = 0;
                        }
                        // recursively add sub properties
                        const defaultChoice = new Tag(defaultProperty, defaultProperty.getChildByName(HWDB.CHOICE_TAG, curChoice));
                        let overriddenChoiceNode = null;
                        if (overriddenProperty !== null) {
                            let idAttribute = HWDB.PROPERTY_NAME_ATTRIBUTE;
                            let identifier = defaultChoice.getAttribute(idAttribute);
                            if (identifier === null || identifier.length === 0) {
                                idAttribute = HWDB.CHOICE_VALUE_ATTRIBUTE;
                                identifier = defaultChoice.getAttribute(idAttribute);
                            }
                            overriddenChoiceNode = overriddenProperty.getChildByID(HWDB.CHOICE_TAG, identifier, idAttribute);
                        }
                        const overriddenChoice = (!overriddenChoiceNode || !overriddenProperty) ? null :
                            new Tag(overriddenProperty, overriddenChoiceNode);
                        this.addProperties(defaultChoice, overriddenChoice, properties, excludeHiddenProperty, subPathPropertiesOnly, propStruct);
                    }
                }
                else if ((type.localeCompare(HWDB.HIDDEN_TYPE) === 0) && !excludeHiddenProperty) {
                    const prop = new TextProperty(propStruct, id);
                    prop.description = name;
                    prop.toolTip = defaultProperty.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
                    properties.push(prop);
                }
            }
        }
    }
    static addBulletToFormattedText(formattedText, newBullet) {
        if (newBullet !== null && newBullet.length > 0) {
            formattedText.append('<li>');
            newBullet = newBullet.trim();
            if (newBullet.startsWith('-')) {
                newBullet = newBullet.substring(1);
                newBullet = newBullet.trim();
            }
            formattedText.append(newBullet);
            formattedText.append('</li>');
        }
    }
    addSimulatorDriverProperties6(driverProperties, defaultValues, overrideNode, properties, tips, summary) {
        const nProperties = driverProperties.countChildrenByName(HWDB.CHOICELIST_TAG);
        for (let i = 0; i < nProperties; i++) {
            const property = new Tag(driverProperties, driverProperties.getChildByName(HWDB.CHOICELIST_TAG, i));
            const type = property.getAttribute(HWDB.DRIVER_TYPE_ATTRIBUTE);
            const name = property.getAttribute(HWDB.ID_ATTRIBUTE);
            const overriddenProperty = overrideNode.getChildByID(HWDB.PROPERTY_TAG, name);
            if (overriddenProperty !== null && XMLParser.GetAttributeString(overriddenProperty, HWDB.TYPE_ATTRIBUTE).localeCompare(HWDB.HIDDEN_TYPE) === 0)
                continue; // skip properties that are overridden.
            const defaultValue = new Tag(defaultValues, defaultValues.getChildByID(HWDB.CURRENT_CHOICE_TAG, name, HWDB.KEY_ATTRIBUTE));
            const propStruct = new SimulationPropertyDescriptor(property, defaultValue, overriddenProperty !== null ? new Tag(overrideNode, overriddenProperty) : null, overrideNode);
            if (type.localeCompare(HWDB.STRING_LIST_TYPE) === 0) {
                const nChoices = property.countChildrenByName(HWDB.CHOICE_TAG);
                if (nChoices > 0) {
                    properties.push(new DropListProperty(property, propStruct, name, nChoices));
                    // look for dynamic properties associated with the current selection
                    const value = propStruct.getProperty().toString();
                    const currentChoice = property.getChildByID(HWDB.CHOICE_TAG, value, HWDB.CHOICE_VALUE_ATTRIBUTE);
                    if (currentChoice !== null) {
                        const choice = new Tag(property, currentChoice);
                        // recursively add sub-properties
                        this.addSimulatorDriverProperties6(choice, defaultValues, overrideNode, properties, tips, summary);
                    }
                }
            }
            else if (type.localeCompare('string') === 0) {
                const prop = new TextProperty(propStruct);
                prop.description = name;
                properties.push(prop);
            }
            else if (type.localeCompare(HWDB.FILE_PATH_TYPE) === 0) {
                const prop = new FileProperty(propStruct);
                prop.description = name;
                prop.setExtensions(property.getAttribute(HWDB.EXTN_ATTRIBUTE));
                properties.push(prop);
            }
            else if (type.localeCompare(HWDB.NUMERIC_TYPE) === 0) {
                const prop = new NumberProperty(propStruct);
                prop.description = name;
                prop.upperbound = property.getAttributeInteger(HWDB.UPPER_RANGE_ATTRIBUTE, Number.MAX_SAFE_INTEGER);
                prop.lowerbound = property.getAttributeInteger(HWDB.LOWER_RANGE_ATTRIBUTE, Number.MIN_SAFE_INTEGER);
                properties.push(prop);
            }
        }
        const nInferences = driverProperties.countChildrenByName(HWDB.INFERENCE_TAG);
        for (let i = 0; i < nInferences; i++) {
            const inference = driverProperties.getChildByName(HWDB.INFERENCE_TAG, i);
            const key = XMLParser.GetAttributeString(inference, HWDB.KEY_ATTRIBUTE);
            if (key.localeCompare(HWDB.ADVICE_ATTRIBUTE) === 0) {
                SystemSetupEditor.addBulletToFormattedText(tips, XMLParser.GetAttributeString(inference, HWDB.CHOICE_VALUE_ATTRIBUTE));
            }
            else if (key.localeCompare(HWDB.SUMMARY_ATTRIBUTE) === 0) {
                SystemSetupEditor.addBulletToFormattedText(summary, XMLParser.GetAttributeString(inference, HWDB.CHOICE_VALUE_ATTRIBUTE));
            }
        }
    }
    addSimulatorDriverProperties3(defaultNode, overrideNode, properties) {
        // Node driversNode = defaultNode.getParent(null);
        // Tag drivers = new Tag(defaultNode, driversNode);
        // Node driverPropertiesNode = drivers.getChildByName(HWDB.DRIVER_PROPERTIES_TAG, 0);
        const driverPropertiesNode = defaultNode.getChildByName(HWDB.DRIVER_PROPERTIES_TAG, 0);
        if (driverPropertiesNode !== null) {
            const driverProperties = new Tag(defaultNode, driverPropertiesNode);
            const defaultValues = new Tag(driverProperties, driverProperties.getChildByName(HWDB.CURRENT_TAG, 0));
            const tips = new StringBuilder();
            const summary = new StringBuilder();
            this.addSimulatorDriverProperties6(driverProperties, defaultValues, overrideNode, properties, tips, summary);
            if (tips.length !== 0) {
                properties.push(new InfoBoxProperty('Tips', tips.toString()));
            }
            if (summary.length !== 0) {
                properties.push(new InfoBoxProperty('Summary', summary.toString()));
            }
        }
    }
    addBypassProperties(flatNode, properties) {
        const prop = new NumberProperty(new BypassBitsPropertyDescriptor(flatNode, this.flatRootNode));
        prop.description = 'Bypass Bits';
        prop.upperbound = 1024;
        prop.lowerbound = 1;
        properties.push(prop);
    }
    async ensureBuiltInProperties(componentName) {
        // read built in properties from defaultProperties.dat files.
        if (!SystemSetupEditor.builtinProperties.has(componentName)) {
            let builtinPropertiesRoot = null;
            try {
                // first time for this component, must read builtinProperties and cache them.
                const defaultPropertiesFile = SystemSetupEditor.getTargetDbDirectory() + componentName + 's/defaultProperties.dat';
                // load XML file and validate
                const instanceParser = new XMLParser();
                const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
                const defaultPropertiesText = await targetConfigService.getFile(defaultPropertiesFile);
                instanceParser.ParseAndValidate(defaultPropertiesText, false);
                const root = instanceParser.GetDocumentElement();
                if (root !== null) {
                    builtinPropertiesRoot = new Tag(instanceParser, root);
                }
            }
            catch (e) {
                // can't parse defaultProperties so there aren't any.
            }
            SystemSetupEditor.builtinProperties.set(componentName, builtinPropertiesRoot);
        }
    }
    addBuiltInProperties(flatNode, properties) {
        // read built in properties from defaultProperties.dat files.
        const componentName = flatNode.getName();
        const defaultProperties = SystemSetupEditor.builtinProperties.get(componentName);
        // add builtin properties read from defaultProperties.dat file.
        if (defaultProperties) {
            this.addProperties(defaultProperties, flatNode, properties, true, false, null);
        }
    }
    addDriverProperties(flatNode, properties, excludeHiddenProperty = true) {
        try {
            const type = flatNode.getName();
            let isaTag = null;
            let subPath = false;
            if (type.localeCompare(HWDB.CPU_TAG) === 0
                || type.localeCompare(HWDB.ROUTER_TAG) === 0) {
                // cpu driver properties
                isaTag = HardwareDatabaseReader.getISATag(flatNode);
            }
            else if (type.localeCompare(HWDB.SUBPATH_TAG) === 0) {
                // sub path properties
                const router = flatNode.getParent(HWDB.ROUTER_TAG) ?? null;
                if (router !== null) {
                    isaTag = HardwareDatabaseReader.getISATag(new Tag(flatNode, router));
                }
                subPath = true;
            }
            if (isaTag !== null) {
                const driverNode = isaTag.getChildByName(HWDB.DRIVER_TAG, 0);
                if (driverNode !== null) {
                    this.addProperties(new Tag(isaTag, driverNode), flatNode, properties, excludeHiddenProperty, subPath, null);
                }
                if (type.localeCompare(HWDB.CPU_TAG) === 0) {
                    this.addSimulatorDriverProperties3(isaTag, flatNode, properties);
                }
            }
        }
        catch (e) {
            // can find driver tag, so there aren't any driver properties.
        }
    }
    getProperties(object, excludeHiddenProperty = true) {
        let properties = new Array();
        const flatNode = new Tag(this.flatRootNode, object.item);
        if (SystemSetupEditor.getBypassBits(flatNode) > 0) {
            this.addBypassProperties(flatNode, properties);
        }
        else {
            // add built-in properties
            this.addBuiltInProperties(flatNode, properties);
            const prop = properties.length > 0 ? properties[0] : null;
            if (flatNode.getName().localeCompare(HWDB.CONNECTION_TAG) === 0) {
                // add connection properties
                if (prop === null || !(prop instanceof DropListProperty)
                    || prop.description.localeCompare('dataFileRequired') !== 0
                    || this.getProperty(prop).toString().localeCompare('specify custom') !== 0) {
                    // don't add connection properties if we user specifying their own board.dat config file.
                    this.addProperties(flatNode, flatNode, properties, excludeHiddenProperty, false, null);
                }
            }
            else if (prop !== null && prop.description.toLowerCase().localeCompare(HWDB.BYPASS_PROPERTY) === 0) {
                // indicate that it has sub-properties because if bypassed we skip other properties.
                prop.descriptor.setHasSubProperties(true);
                // determine if current state is bypassed
                if (this.getProperty(prop).toString().toLowerCase() === 'yes') {
                    // remove all other default properties when bypass is selected
                    while (properties.length > 1) {
                        properties = properties.slice(1);
                    }
                }
                else {
                    // add driver properties unless device is bypassed
                    this.addDriverProperties(flatNode, properties);
                }
            }
            else {
                // add driver properties
                this.addDriverProperties(flatNode, properties);
            }
        }
        return properties;
    }
    resetProperty(prop) {
        this.setProperty(prop, '');
    }
    isPropertySet(id) {
        return id.getAttribute(HWDB.VALUE_ATTRIBUTE).length > 0;
    }
    getProperty(prop, getIndexForChoice = false, fileSeparator = '/') {
        const result = prop.descriptor.getProperty(getIndexForChoice);
        if (prop.widgetType === 'checkbox') {
            return result.toLowerCase() === 'yes';
        }
        if (prop.format === 'hex') {
            return +result;
        }
        if (prop instanceof FileProperty) {
            const path = Tag.convertToRelPath(result, [getParent(this.fileName), ...SystemSetupEditor.getRootDirectories()]);
            return GcUtils.findAndReplace(path, '/', fileSeparator);
        }
        return result;
    }
    getBoardName(object) {
        const flatProperty = new Tag(this.flatRootNode, object.item);
        const connectionNode = flatProperty.getParent(HWDB.CONNECTION_TAG);
        const connection = connectionNode && this.rootTreeElement.findElement(connectionNode);
        if (connection) {
            return connection.getName();
        }
        return null;
    }
    getRecommendedBoardName(object) {
        let boardName = null;
        let flatNode = null;
        if (object instanceof TreeElement) {
            flatNode = new Tag(this.flatRootNode, object.item);
            const type = flatNode.getName();
            let isaTag = null;
            if (type.localeCompare(HWDB.CPU_TAG) === 0) {
                try {
                    isaTag = HardwareDatabaseReader.getISATag(flatNode);
                    if (isaTag !== null) {
                        const driverPropertiesNode = isaTag.getChildByName(HWDB.DRIVER_PROPERTIES_TAG, 0);
                        if (driverPropertiesNode !== null) {
                            const driverProperties = new Tag(isaTag, driverPropertiesNode);
                            const defaultValues = new Tag(driverProperties, driverProperties.getChildByName(HWDB.CURRENT_TAG, 0));
                            const nProperties = driverProperties.countChildrenByName(HWDB.CHOICELIST_TAG);
                            for (let i = 0; i < nProperties; i++) {
                                const property = new Tag(driverProperties, driverProperties.getChildByName(HWDB.CHOICELIST_TAG, i));
                                boardName = SimulationPropertyDescriptor.getBoardName(defaultValues, flatNode, property);
                                if (boardName !== null && boardName.length > 0) {
                                    break;
                                }
                            }
                        }
                    }
                }
                catch (e) {
                    // ignore
                }
            }
        }
        else if (object instanceof SimulationPropertyDescriptor) {
            boardName = object.getBoardName();
            flatNode = object.driverProperty;
        }
        if (flatNode !== null && boardName !== null && boardName.length > 0) {
            const configurationNode = flatNode.getParent(HWDB.CONFIGURATION_TAG);
            if (configurationNode) {
                const parent = new Tag(this.flatRootNode, configurationNode);
                boardName = SystemSetupEditor.createUniqueId(parent, boardName, SystemSetupEditor.getComponentNames(parent, this.flatRootNode).map(item => item.name));
            }
        }
        return boardName;
    }
    getNodeType(element) {
        const tag = new Tag(this.flatRootNode, element.item);
        return tag.getName();
    }
    getAttributeString(element, name) {
        let attribute = null;
        const tag = new Tag(this.flatRootNode, element.item);
        attribute = tag.getAttribute(name);
        return attribute === null ? '' : attribute;
    }
    getChildAttributeString(element, childName, attributeName) {
        let attribute = null;
        const tag = new Tag(this.flatRootNode, element.item);
        attribute = tag.getChildAttribute(childName, attributeName);
        return attribute === null ? '' : attribute;
    }
    getNodeDescriptionToDisplay(element) {
        let description = this.getErrorMessage(element);
        if (description === null) {
            const flatNode = new Tag(this.flatRootNode, element.item);
            description = flatNode.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
        }
        return description === null ? '' : description;
    }
    findNodesOrIncludeTags(flatNode, includeTextNodes = false) {
        const retVal = [];
        // parent must exist in original file first
        const flatParentNode = flatNode.getParent(null) ?? null;
        const flatParent = flatParentNode && new Tag(flatNode, flatParentNode);
        const parent = flatParent && SystemSetupEditor.gotoNode(flatParent, this.flatRootNode, this.rootNode, false);
        if (parent !== null && flatNode.getAttribute(HWDB.MOVABLE_ATTRIBUTE).localeCompare('no') !== 0) {
            const id = flatNode.getAttribute(HWDB.ID_ATTRIBUTE);
            // find child node with matching href
            let child = parent.getNode().firstChild;
            let prevNode = null;
            while (child) {
                if (child.nodeType === NodeTypes.ELEMENT_NODE && id.localeCompare(XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE)) === 0) {
                    // found direct reference
                    if (includeTextNodes && prevNode !== null && prevNode.nodeType === NodeTypes.TEXT_NODE) {
                        retVal.push(new Tag(parent, prevNode));
                    }
                    retVal.push(new Tag(parent, child));
                }
                prevNode = child;
                child = child.nextSibling;
            }
        }
        return retVal;
    }
    setPropertyByName(rootElement, cpuId, propId, value) {
        const root = rootElement ?? this.getRoot();
        // set property on the root
        if ((cpuId === null)
            || (root.id !== null && cpuId.localeCompare(root.id) === 0)) {
            const properties = this.getProperties(root);
            if (properties !== null) {
                properties.forEach(property => {
                    if (propId.localeCompare(property.getName()) === 0) {
                        this.setProperty(property, value);
                    }
                });
            }
        }
        // recursively set property on children of root
        const children = root.children;
        if (children !== null) {
            children.forEach(child => {
                this.setPropertyByName(child, cpuId, propId, value);
            });
        }
    }
    getPropertyError(prop) {
        return prop.getPropertyError();
    }
    setProperty(prop, value, setIndexForChoice = false) {
        const descriptor = prop.descriptor;
        if (descriptor.isReadOnly()) {
            return false;
        }
        if (prop instanceof FileProperty && typeof value === 'string') {
            value = GcUtils.findAndReplace(value, '\\', '/');
            value = Tag.convertToRelPath(value, [getParent(this.fileName), ...SystemSetupEditor.getRootDirectories()]);
        }
        const curValue = this.getProperty(prop, setIndexForChoice);
        if (curValue === value) {
            return false;
        }
        if (typeof value === 'boolean') {
            const choices = prop.choices;
            if (choices?.length === 2) {
                if (choices[0].toLowerCase() === 'yes') {
                    value = value ? choices[0] : choices[1];
                }
                else {
                    value = value ? choices[1] : choices[0];
                }
            }
            else {
                value = '';
            }
        }
        if (typeof value === 'number') {
            if (prop.format === 'hex') {
                value = value.toString(16);
                while ((value.length < 8 && value.length > 4) || (value.length < 4 && value.length > 1)) {
                    value = '0' + value;
                }
                value = '0x' + value;
            }
            else {
                value = value.toString();
            }
        }
        const flatProperty = descriptor.setProperty(value, setIndexForChoice);
        if (flatProperty !== null) {
            // must set the value in the system setup xml file as well
            const newProperty = SystemSetupWriter.gotoNode(flatProperty, this.flatRootNode, this.rootNode, true);
            newProperty?.setAttribute(descriptor.getValueAttributeName(), flatProperty.getAttribute(descriptor.getValueAttributeName()));
            if (descriptor.hasSubProperties()) {
                // special case if bypass property changed then errors could be
                // generated or removed.
                if (descriptor instanceof BypassBitsPropertyDescriptor) {
                    this.generateErrorReports();
                }
            }
        }
        return true;
    }
    renameComponent(element, value) {
        const node = new Tag(this.flatRootNode, element.item);
        // set new name in flat file
        node.setAttribute(HWDB.NAME_ATTRIBUTE, value);
        // set in top level system setup xml file as well.
        const topLevelNodes = this.findNodesOrIncludeTags(node, false).filter(element => element.getAttribute(HWDB.NAME_ATTRIBUTE));
        if (topLevelNodes.length === 0) {
            topLevelNodes.push(SystemSetupWriter.gotoNode(node, this.flatRootNode, this.rootNode, true));
        }
        topLevelNodes.forEach(topLevelNode => topLevelNode.setAttribute(HWDB.NAME_ATTRIBUTE, value));
        // regenerate Error Messages
        this.generateErrorReports();
    }
    getRoot() {
        return this.rootTreeElement;
    }
    getChildNodes(parentNode) {
        const count = this.countChildNodes(parentNode);
        if (count > 0) {
            const result = new Array(count);
            let node = SystemSetupWriter.getFirstVisibleChild(parentNode);
            for (let i = 0; i < count; i++) {
                result[i] = node;
                node = SystemSetupWriter.getNextVisibleChild(node);
            }
            return result;
        }
        return [];
    }
    countChildren(element) {
        return this.countChildNodes(element.item);
    }
    countChildNodes(parentNode) {
        let count = 0;
        let node = SystemSetupWriter.getFirstVisibleChild(parentNode);
        while (node !== null) {
            count++;
            node = SystemSetupWriter.getNextVisibleChild(node);
        }
        return count;
    }
    getParent(object) {
        let parent = null;
        if (object instanceof TreeElement) {
            parent = object.getParent();
        }
        else if (object instanceof Node) {
            let parentNode = null;
            parentNode = object.parentNode;
            while (parentNode !== null) {
                if (nodesToShow.has(parentNode.nodeName)) {
                    parent = this.rootTreeElement.findElement(parentNode);
                    break; // found it
                }
                parentNode = parentNode.parentNode ?? null;
            }
        }
        return parent === null ? this.getRoot() : parent;
    }
    findErrorLocation(errorLocation, parent) {
        parent = parent ?? this.getRoot();
        let result;
        const thisErrorLocation = parent.getErrorLocation();
        if (thisErrorLocation && thisErrorLocation.localeCompare(errorLocation) === 0)
            return parent;
        const children = (parent && parent.children) ?? undefined;
        if (children) {
            for (let i = 0; result === undefined && i < children.length; i++) {
                result = this.findErrorLocation(errorLocation, children[i]);
            }
        }
        return result;
    }
    getErrorMessage(id) {
        if (this.errorReports !== null && id instanceof TreeElement) {
            const location = id.getErrorLocation();
            if (location !== null) {
                this.errorReports.forEach(errorReport => {
                    const location = errorReport.getLocation();
                    if (location !== null && location.toLowerCase().localeCompare(location.toLowerCase()) === 0) {
                        return errorReport.getErrorMessage();
                    }
                });
            }
        }
        else if (!id && this.errorReports !== null && this.errorReports.length > 0) {
            return this.errorReports[0].getErrorMessage();
        }
        return null;
    }
    hasErrors() {
        return this.errorReports !== null && this.errorReports.length > 0;
    }
    getXmlText() {
        const result = this.rootNode.serializeXMLDocument();
        const pos = result.indexOf('><configurations');
        if (pos > 0 && pos < 100) {
            return result.substring(0, pos + 1) + '\n' + result.substring(pos + 1);
        }
        return result;
    }
    static getBypassBits(node) {
        const isa = node.getAttribute(HWDB.ISA_ATTRIBUTE);
        if (isa !== null && isa.startsWith('BYPASS')) {
            return Number.parseInt(isa.substring(6), 10);
        }
        return -1;
    }
    static setBypassBits(node, flatRootNode, bits) {
        node.setAttribute(HWDB.ISA_ATTRIBUTE, (bits < 10 ? 'BYPASS0' : 'BYPASS')
            + bits.toString());
    }
    getIconNameToDisplay(element, longName = false) {
        let iconName = hideConfigurations ? HWDB.CONNECTION_TAG : HWDB.CONFIGURATION_TAG;
        if (element !== null) {
            iconName = XMLParser.GetName(element.item);
            if ((iconName.localeCompare(HWDB.CPU_TAG) === 0 || iconName.localeCompare(HWDB.ROUTER_TAG) === 0)) {
                const node = new Tag(this.flatRootNode, element.item);
                if (SystemSetupEditor.getBypassBits(node) > 0 ||
                    node.getPropertyString(HWDB.BYPASS_PROPERTY, '0').localeCompare('1') === 0) {
                    iconName = (!longName) ? HWDB.BYPASS_PROPERTY : ((iconName.localeCompare(HWDB.CPU_TAG) === 0) ? HWDB.BYPASS_PROPERTY : HWDB.BYPASS_ROUTER_ICON);
                }
            }
        }
        return iconName;
    }
    canRemoveComponent(node) {
        const flatChild = node.item;
        const flatChildTag = new Tag(this.flatRootNode, flatChild);
        return flatChildTag.getAttribute(HWDB.MOVABLE_ATTRIBUTE).localeCompare('no') !== 0;
    }
    removeComponent(node) {
        let flatChild = node.item;
        let flatChildTag = new Tag(this.flatRootNode, flatChild);
        if (!this.canRemoveComponent(node)) {
            throw Error(`${node.getName()} ${flatChild.nodeName} cannot be removed.`);
        }
        // remove configuration node when last connection is removed.
        if (hideConfigurations && flatChildTag.getName() === HWDB.CONNECTION_TAG) {
            const configuration = flatChildTag.getParent(HWDB.CONFIGURATION_TAG);
            if (configuration !== null) {
                const configurationTag = new Tag(this.flatRootNode, configuration);
                if (configurationTag.countChildrenByName(HWDB.CONNECTION_TAG) === 1) {
                    flatChild = configuration;
                    flatChildTag = configurationTag;
                }
            }
        }
        // get child in top level file, assume first that it was included
        const childTags = this.findNodesOrIncludeTags(flatChildTag, true);
        if (childTags.length === 0) {
            return false;
        }
        // remove all children from top level xml file
        for (let i = childTags.length; i-- > 0;) {
            const childTag = childTags[i];
            const parent = childTag.getParent(null);
            if (parent !== null) {
                parent.removeChild(childTag.getNode());
            }
        }
        // remove from flat file too
        const flatParent = flatChildTag.getParent(null);
        if (flatParent !== null) {
            flatParent.removeChild(flatChild);
        }
        node.getParent()?.updateChildren();
        this.generateErrorReports(); // removing things can clear errors
        return true;
    }
    canMoveUp(node) {
        return this.doMove(node, true);
    }
    canMoveDown(node) {
        return this.doMove(node, false);
    }
    moveUp(node) {
        this.doMove(node, true, true);
    }
    moveDown(node) {
        this.doMove(node, false, true);
    }
    doMove(node, up, doit = false) {
        const flatParent = this.getParent(node);
        if (!flatParent) {
            return false;
        }
        const siblings = flatParent.children;
        if (siblings.length <= 1) {
            return false;
        }
        // get first (up) or last (down) sibling and make sure its possible to move
        const flatChild = node.item;
        const index = siblings.findIndex(sibling => sibling.item === flatChild);
        const flatSibling = siblings[up ? index - 1 : index + 1]?.item;
        if (!flatSibling) {
            return false; // already at the top or bottom of children list
        }
        const flatChildTag = new Tag(this.flatRootNode, flatChild);
        const flatSiblingTag = new Tag(this.flatRootNode, flatSibling);
        // get child in top level file, assume first that it was included
        const childTags = this.findNodesOrIncludeTags(flatChildTag, true);
        const siblingTags = this.findNodesOrIncludeTags(flatSiblingTag, true);
        if (childTags.length === 0 || siblingTags.length === 0) {
            return false;
        }
        if (doit) {
            this.swapComponents(childTags, siblingTags);
            this.swapComponents([flatChildTag], [flatSiblingTag]); // must modify flat xml file as well.
            flatParent.updateChildren();
        }
        return true;
    }
    swapComponents(elements1, withElements2) {
        // validate parameters
        if (elements1.length === 0 || withElements2.length === 0) {
            return; // nothing to do because there are no elements to swap with.
        }
        const parent1 = elements1[0].getParent(null);
        const parent2 = withElements2[0].getParent(null);
        if (!parent1 || !parent2) {
            throw new Error('Cannot swapComponents that do not have parent elements.');
        }
        // insert a placeholder before elements1
        const placeholder = new Tag(elements1[0], parent1).createChild('junk', null, null, elements1[0].getNode());
        // move elements1 before elements2
        const insertBefore = withElements2[0].getNode();
        elements1.forEach(element1 => {
            parent2.insertBefore(element1.getNode(), insertBefore);
        });
        // move elements2 before placeholder
        withElements2.forEach(element2 => {
            parent1.insertBefore(element2.getNode(), placeholder);
        });
        // remove placeholder
        parent1.removeChild(placeholder);
    }
    async addComponent(parent, newComponent) {
        parent = parent ?? this.getRoot();
        let parentNode = parent.item;
        if (newComponent.type === 'connection') {
            // create a new configuration tag to include the connection in.
            parentNode = this.flatRootNode.createChild(HWDB.CONFIGURATION_TAG, SystemSetupWriter.createUniqueId(this.flatRootNode, 'configuration_0', null), HWDB.VERSION);
        }
        const flatParent = new Tag(this.flatRootNode, parentNode);
        await this.includeComponent(flatParent, newComponent);
        this.setAllDefaultJtagProperties();
        parent.updateChildren();
    }
    async includeComponent(flatParent, component) {
        let flatConnection = null;
        let id = component.id;
        // test if parent is a connection
        if (flatParent.getName().localeCompare(HWDB.CONNECTION_TAG) === 0) {
            let platform = flatParent.getChildByName(HWDB.PLATFORM_TAG, 0);
            if (platform === null) {
                // create the platform node to add includeFiles to
                platform = flatParent.createChild(HWDB.PLATFORM_TAG, 'platform_0', HWDB.VERSION);
            }
            flatConnection = flatParent;
            flatParent = new Tag(flatParent, platform);
        }
        else {
            // add device drivers
            const connectionNode = flatParent.getParent(HWDB.CONNECTION_TAG);
            if (connectionNode !== null) {
                flatConnection = new Tag(flatParent, connectionNode);
            }
        }
        if (flatConnection !== null && component.type !== 'connection') {
            // get xml attribute of connection
            const nodes = this.findNodesOrIncludeTags(flatConnection);
            let connectionPath = nodes.reduce((xmlAttribute, node) => xmlAttribute || node.getAttribute(HWDB.XML_ATTRIBUTE), '');
            if (!connectionPath) {
                throw Error('Cannot add component because connection is missing from top level .ccxml');
            }
            connectionPath = connectionPath.substring(0, connectionPath.indexOf('.xml'));
            const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
            const connections = (await targetConfigService.getConnections(component.id));
            const connection = connections.filter(connection => connection.xmlFile === connectionPath)[0];
            if (!connection) {
                throw Error(`Cannot add component to connection=${flatConnection.getAttribute(HWDB.ID_ATTRIBUTE)}`);
            }
            await this.addDeviceDrivers(flatConnection, connection.id, component);
        }
        // add child to top level system setup.
        const parent = SystemSetupWriter.gotoNode(flatParent, this.flatRootNode, this.rootNode, true);
        if (!parent) {
            throw Error('Cannot add component because parent is missing from top level .ccxml');
        }
        const relFilePath = `${component.type}s/${component.xmlFile}.xml`;
        let insertBefore = parent.getChildByName(HWDB.CONFIGURATION_TAG, 0) ?? parent.getChildByName(HWDB.CONNECTION_TAG, 0);
        // Ensure name is unique
        const existingNames = SystemSetupWriter.getComponentNames(flatParent, this.flatRootNode);
        id = SystemSetupWriter.createUniqueId(flatParent, id, existingNames.map(item => item.name));
        HardwareDatabaseReader.includeFile(parent, relFilePath, id, id, insertBefore ?? undefined);
        // add child to flat file, by reading include file and inserting the node.
        if (insertBefore !== null) {
            insertBefore = flatParent.getChildByID(null, XMLParser.GetAttributeString(insertBefore, HWDB.ID_ATTRIBUTE));
        }
        const absFilePath = `${SystemSetupReader.getTargetDbDirectory()}${relFilePath}`;
        const newFlatChild = await this.xmlReader.createFlatNodeFromFile(flatParent, absFilePath, id, id, SystemSetupReader.getRootDirectories(), insertBefore ?? undefined);
        SystemSetupWriter.createUniqueNames(newFlatChild.getNode(), this.flatRootNode, this.rootNode, existingNames.filter(item => item.type === 'cpu').map(item => item.name));
        this.generateErrorReports();
    }
    addDeviceDriver(flatConnection, relDriverXmlFile) {
        relDriverXmlFile = relDriverXmlFile.split('\\').join('/');
        const connection = SystemSetupWriter.gotoNode(flatConnection, this.flatRootNode, this.rootNode, true);
        if (!connection) {
            throw Error('Cannot add device driver because <connection> tag is missing.');
        }
        const existingDrivers = connection.getAllChildrenByName(HWDB.INSTANCE_TAG).map(driver => driver.attributes?.getNamedItem(HWDB.HREF_ATTRIBUTE)?.value ?? '');
        if (existingDrivers.includes(relDriverXmlFile)) {
            return; // done, driver is already included.
        }
        const platformTag = flatConnection.getChildByName(HWDB.PLATFORM_TAG, 0);
        if (!platformTag) {
            throw Error('Cannot add device driver because <platform> tag is missing.');
        }
        try {
            const absDriverXmlFile = `${SystemSetupReader.getTargetDbDirectory()}${relDriverXmlFile}`;
            this.xmlReader.createFlatNodeFromFile(flatConnection, absDriverXmlFile, 'drivers', null, SystemSetupReader.getRootDirectories(), platformTag);
            super.addDeviceDriver(connection, relDriverXmlFile);
        }
        catch (e) {
            throw Error(`Can't use device driver due to parsing errors in ${getFileName(relDriverXmlFile)}.\nPlease select a different driver or a different device.`);
        }
    }
    generateErrorReports() {
        const newErrorReports = this.getErrorMessages(this.flatRootNode, this.fileName);
        if (newErrorReports !== null) {
            if (this.errorReports !== null) {
                // compare error reports to see if they are different
                if (this.errorReports.length !== newErrorReports.length) {
                    this.errorReports = newErrorReports;
                    return true;
                }
                else {
                    for (let i = this.errorReports.length; i-- > 0;) {
                        if (this.errorReports[i].compareTo(newErrorReports[i]) !== 0) {
                            this.errorReports = newErrorReports;
                            return true;
                        }
                    }
                }
            }
            else {
                this.errorReports = newErrorReports;
                return true;
            }
        }
        else if (this.errorReports !== null) {
            this.errorReports = null;
            return true;
        }
        return false;
    }
    setAllDefaultJtagProperties() {
        // refresh overridden connection properties for all connections
        const nConfigurations = this.flatRootNode.countChildrenByName(HWDB.CONFIGURATION_TAG);
        for (let i = 0; i < nConfigurations; i++) {
            const flatConfiguration = new Tag(this.flatRootNode, this.flatRootNode.getChildByName(HWDB.CONFIGURATION_TAG, i));
            const nConnections = flatConfiguration.countChildrenByName(HWDB.CONNECTION_TAG);
            for (let j = 0; j < nConnections; j++) {
                const flatConnection = new Tag(flatConfiguration, flatConfiguration.getChildByName(HWDB.CONNECTION_TAG, j));
                this.setDefaultJtagProperties(flatConnection, SystemSetupEditor.gotoNode(flatConnection, this.flatRootNode, this.rootNode, true));
            }
        }
    }
    getCpusList() {
        return this.getComponentList('cpu');
    }
    getComponentList(type, parent) {
        const result = [];
        this.addComponentsToList(type, parent ?? this.getRoot(), result);
        return result;
    }
    addComponentsToList(type, node, list) {
        if (!node) {
            return;
        }
        if (this.getNodeType(node) === type) {
            list.push(node);
            return;
        }
        node.children.forEach(childNode => this.addComponentsToList(type, childNode, list));
    }
    getComponentName(component) {
        if (component) {
            return new Tag(this.flatRootNode, component.item).getAttribute(HWDB.COMPONENT_NAME);
        }
    }
    findElementByPath(path) {
        return this.rootTreeElement.findElementByPath(path);
    }
    findElementTypeByPath(path) {
        const element = this.findElementByPath(path);
        return element ? this.getNodeType(element) : null;
    }
}
SystemSetupEditor.builtinProperties = new Map();

/**
 *  Copyright (c) 2022, 2025 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

export { AbstractProperty, HardwareDatabaseReader, SystemSetupEditor, Tag };
//# sourceMappingURL=TargetCcxmlParser.js.map
