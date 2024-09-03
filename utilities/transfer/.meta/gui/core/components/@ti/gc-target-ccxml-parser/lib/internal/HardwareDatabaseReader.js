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
import { HardwareDbException } from './HardwareDbException';
import { HWDB } from './HWDB';
import { Tag } from './Tag';
import { XMLParser } from './XMLParser';
import { GcFiles } from '../../../gc-core-assets/lib/GcFiles';
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { ServicesRegistry } from '../../../gc-core-services/lib/ServicesRegistry';
import { targetConfigServiceType } from '../../../gc-service-target-config/lib/TargetConfigService';
/* eslint-disable @typescript-eslint/no-var-requires */
export function getParent(fileName) {
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
export class HardwareDatabaseReader {
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
        var _a;
        const driver = this.getDriver(connection, id);
        return driver === null ? null : ((_a = driver.parentNode) !== null && _a !== void 0 ? _a : null);
    }
    static getISATag(processor) {
        const driver = this.getDriverFrom(processor);
        const parent = driver === null || driver === void 0 ? void 0 : driver.getParent(null);
        return (!driver || !parent) ? null : new Tag(driver, parent);
    }
    static getDriver(connection, id) {
        var _a;
        const drivers = connection.getChildByName(HWDB.DRIVERS_TAG, 0);
        if (drivers === null) {
            throw new HardwareDbException('XML configuration file has no drivers\n');
        }
        const sConnectionType = connection.getChildAttribute(HWDB.CONNECTION_TYPE_TAG, HWDB.TYPE_ATTRIBUTE);
        let isaChild = XMLParser.GetFirstChild(drivers);
        let driver = null;
        let found = false;
        for (; isaChild !== null; isaChild = (_a = isaChild.nextSibling) !== null && _a !== void 0 ? _a : null) {
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
        var _a;
        // copy all attributes, we're interested in
        this.copyAttributes(from, to, curDirectory, rootDirectories);
        if (!topLevelNode) {
            to.setAttribute(HWDB.MOVABLE_ATTRIBUTE, 'no');
        }
        // copy children
        let child = from.getFirstChild();
        while (child !== null && !(isCancelled === null || isCancelled === void 0 ? void 0 : isCancelled())) {
            let childNode;
            let tag = XMLParser.GetName(child);
            if (tag.localeCompare(HWDB.PROCESSORS_TAG) === 0) {
                // go in one level and skip the remaining children at this level.
                child = (_a = child.firstChild) !== null && _a !== void 0 ? _a : null;
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
                const componentName = childNode.getAttribute(HWDB.NAME_ATTRIBUTE);
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
        await this.copyNode(includedRootNode, newChildTag, getParent(fileName), rootDirectories, true, false);
        newChildTag.setAttribute(HWDB.ID_ATTRIBUTE, id);
        newChildTag.setAttribute(HWDB.VER_ATTRIBUTE, HWDB.VERSION);
        if (name !== null) {
            newChildTag.setAttribute(HWDB.NAME_ATTRIBUTE, name);
        }
        return newChildTag;
    }
}
//# sourceMappingURL=HardwareDatabaseReader.js.map