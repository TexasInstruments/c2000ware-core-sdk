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
import { NodeTypes } from './INode';
import { ServicesRegistry } from '../../../gc-core-services/lib/ServicesRegistry';
import { targetConfigServiceType } from '../../../gc-service-target-config/lib/TargetConfigService';
/* eslint-disable @typescript-eslint/no-var-requires */
export class XMLParser {
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
        var _a;
        this.ParseAndValidate(`<${docName}></${docName}>`, false);
        const result = (_a = this.m_pWorkingDoc) === null || _a === void 0 ? void 0 : _a.documentElement;
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
        return child !== null && child !== void 0 ? child : null;
    }
    static GetNextSibling(elementWithSibling) {
        // This function returns the next sibling node that is not a comment
        let sibling = elementWithSibling.nextSibling;
        while (sibling && NodeTypes.ELEMENT_NODE !== sibling.nodeType) {
            sibling = sibling.nextSibling;
        }
        return sibling !== null && sibling !== void 0 ? sibling : null;
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
        const attribute = attributes === null || attributes === void 0 ? void 0 : attributes.getNamedItem(name);
        const str = !attribute ? '' : attribute.value;
        return str;
    }
    GetDocumentElement() {
        var _a, _b;
        return (_b = (_a = this.m_pWorkingDoc) === null || _a === void 0 ? void 0 : _a.documentElement) !== null && _b !== void 0 ? _b : null;
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
//# sourceMappingURL=XMLParser.js.map