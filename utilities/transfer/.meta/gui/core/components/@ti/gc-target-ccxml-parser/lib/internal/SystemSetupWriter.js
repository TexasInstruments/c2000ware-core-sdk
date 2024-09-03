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
import { HardwareDatabaseReader } from './HardwareDatabaseReader';
import { HWDB } from './HWDB';
import { SystemSetupReader } from './SystemSetupReader';
import { Tag } from './Tag';
import { XMLParser } from './XMLParser';
export const nodesToShow = new Set();
export const nodesToSuppress = new Set();
export const hideConfigurations = true;
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
export class SystemSetupWriter extends SystemSetupReader {
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
    /* (non-Javadoc)
     * @see com.ti.ccstudio.system.setup.SystemSetupReader#onTargetDBDirectoriesChanged()
     */
    onTargetDBDirectoriesChanged() {
        super.onTargetDBDirectoriesChanged();
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
                                    // create override choice
                                    const connectionOverrideChoice = new Tag(connectionOverride, connectionOverride.createChild(HWDB.CHOICE_TAG, null, null));
                                    connectionOverrideChoice.copyAttribute(connectionDefaultChoice, HWDB.CHOICE_VALUE_ATTRIBUTE);
                                    connectionOverrideChoice.copyAttribute(connectionDefaultChoice, HWDB.PROPERTY_NAME_ATTRIBUTE);
                                    // recursively copy sub-properties
                                    this.setDefaultJtagProperties(connectionDefaultChoice, connectionOverrideChoice, new Tag(jtagDefault, jtagDefaultChoiceNode));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    setDefaultJtagPropertyForDevices(parent, connectionDefaults, connectionOverrides) {
        var _a;
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
                deviceNode = (_a = deviceNode.nextSibling) !== null && _a !== void 0 ? _a : null;
            }
        }
    }
    static createUniqueNames(parent, flatRootNode, rootNode, existingNames) {
        let child = this.getFirstVisibleChild(parent);
        while (child !== null) {
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
                if (nameChanged && flatRootNode !== null) {
                    // set new name in flat file
                    const flatNode = new Tag(flatRootNode, child);
                    flatNode.setAttribute(HWDB.NAME_ATTRIBUTE, childName);
                    // set in top level system setup xml file as well.
                    const topLevelNode = this.gotoNode(flatNode, flatRootNode, rootNode, true);
                    topLevelNode === null || topLevelNode === void 0 ? void 0 : topLevelNode.setAttribute(HWDB.NAME_ATTRIBUTE, childName);
                }
                existingNames.push(childName.toLowerCase());
            }
            this.createUniqueNames(child, flatRootNode, rootNode, existingNames);
            child = XMLParser.GetNextSibling(child);
        }
    }
    static createUniqueId(parent, name, existingNames) {
        while (parent.getChildByID(null, name) !== null || (existingNames !== null && existingNames.includes(name.toLowerCase()))) {
            name = this.generateUniqueString(name);
        }
        if (existingNames !== null) {
            existingNames.push(name.toLowerCase());
        }
        return name;
    }
    static generateUniqueString(name) {
        const t = name.lastIndexOf('_');
        let newSuffix = '_0';
        if (t > 0) {
            const suffix = name.substring(t + 1);
            try {
                newSuffix = (Number.parseInt(suffix) + 1).toString();
                name = name.substring(0, t + 1);
            }
            catch (e) {
                // it wasn't an integer
                if (suffix.length === 1) {
                    const lastCh = suffix.charAt(0);
                    let lastChCode = suffix.charCodeAt(0);
                    if ((lastCh <= 'Z' && lastCh >= 'A') || (lastCh <= 'z' && lastCh >= 'a')) {
                        name = name.substring(0, t + 1);
                        newSuffix = '' + String.fromCharCode(++lastChCode); // increment alpha suffix
                    }
                }
            }
        }
        return name + newSuffix;
    }
    static gotoNode(flatNode, flatRootNode, rootNode, createNode) {
        // do thing if the file is empty
        if (flatRootNode === null) {
            return null;
        }
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
        var _a;
        const result = new Array();
        if (parentNode instanceof Tag && flatRootNodeOrElementNames instanceof Tag) {
            const flatRootNode = flatRootNodeOrElementNames;
            const parent = parentNode;
            const connection = parent.getParent(HWDB.CONNECTION_TAG);
            this.getComponentNames(connection === null ? (_a = flatRootNode === null || flatRootNode === void 0 ? void 0 : flatRootNode.getNode()) !== null && _a !== void 0 ? _a : null : connection, result, connection !== null);
        }
        else {
            const elementNames = flatRootNodeOrElementNames;
            const parent = parentNode;
            let child = this.getFirstVisibleChild(parent);
            while (child !== null) {
                let childName = XMLParser.GetAttributeString(child, HWDB.NAME_ATTRIBUTE);
                if (childName === null || childName.length === 0) {
                    childName = XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE);
                }
                if (childName !== null && childName.length > 0) {
                    elementNames.push(childName.toLowerCase());
                }
                if (recursive) {
                    this.getComponentNames(child, elementNames, true);
                }
                child = this.getNextVisibleChild(child);
            }
        }
        return result;
    }
    static getFirstVisibleChild(parent) {
        return this.findNextVisibleChild(parent, XMLParser.GetFirstChild(parent));
    }
    static getNextVisibleChild(child) {
        var _a, _b;
        if (child !== null) {
            child = this.findNextVisibleChild((_a = child.parentNode) !== null && _a !== void 0 ? _a : null, (_b = child.nextSibling) !== null && _b !== void 0 ? _b : null);
        }
        return child;
    }
    static findNextVisibleChild(parent, child) {
        var _a, _b, _c;
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
                    child = (_a = child.nextSibling) !== null && _a !== void 0 ? _a : null;
                }
            }
            else if (parent !== null && nodesToSuppress.has(parent.nodeName)) {
                // go up one level if no more siblings and parent was suppressed.
                child = (_b = parent.nextSibling) !== null && _b !== void 0 ? _b : null;
                parent = (_c = parent.parentNode) !== null && _c !== void 0 ? _c : null;
            }
            else { // parent not suppressed and no more siblings
                break; // child = null;
            }
        }
        return child;
    }
}
//# sourceMappingURL=SystemSetupWriter.js.map