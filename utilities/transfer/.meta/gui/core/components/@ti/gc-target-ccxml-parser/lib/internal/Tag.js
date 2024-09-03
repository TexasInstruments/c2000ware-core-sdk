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
import { HWDB } from './HWDB';
import { XMLParser } from './XMLParser';
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
export class Tag {
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
    countChildrenByName(name) {
        return XMLParser.CountChildrenByName(this.m_pNode, name);
    }
    getName() {
        return XMLParser.GetName(this.m_pNode);
    }
    getParent(nameOfParent) {
        var _a, _b;
        let result = (_a = this.m_pNode.parentNode) !== null && _a !== void 0 ? _a : null;
        while (nameOfParent !== null && result !== null && XMLParser.GetName(result) !== nameOfParent) {
            result = (_b = result.parentNode) !== null && _b !== void 0 ? _b : null;
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
        return `<${this.getName()} ${this.m_pNode.attributes.toString()}>`;
    }
    getNode() {
        return this.m_pNode;
    }
    copyAttribute(from, attrName, curDirectory = null, rootDirectories = null) {
        const attributes = from.m_pNode.attributes;
        const attribute = attributes === null || attributes === void 0 ? void 0 : attributes.getNamedItem(attrName);
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
//# sourceMappingURL=Tag.js.map