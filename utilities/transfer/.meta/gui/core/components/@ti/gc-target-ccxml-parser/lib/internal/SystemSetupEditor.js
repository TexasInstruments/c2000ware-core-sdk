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
import { GcUtils } from '../../../gc-core-assets/lib/GcUtils';
import { ServicesRegistry } from '../../../gc-core-services/lib/ServicesRegistry';
import { targetConfigServiceType } from '../../../gc-service-target-config/lib/TargetConfigService';
import { HardwareDatabaseReader, getParent } from './HardwareDatabaseReader';
import { HWDB } from './HWDB';
import { NodeTypes } from './INode';
import { StringBuilder } from './StringBuilder';
import { SystemSetupReader } from './SystemSetupReader';
import { hideConfigurations, nodesToShow, SystemSetupWriter } from './SystemSetupWriter';
import { Tag } from './Tag';
import { XMLParser } from './XMLParser';
const nullTreeDataProvider = new (class {
    constructor() {
        this.rowCount = 0;
    }
    setValue() { }
    getValue() {
        return;
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
            this._children = this.systemSetup.getChildren(this);
        }
        return this._children;
    }
    getChildren(rawChildren) {
        if (rawChildren === null || rawChildren.length === 0) {
            return [];
        }
        const newChildren = new Array(rawChildren.length);
        let nOldChildren = this._children === null ? 0 : this._children.length;
        for (let i = rawChildren.length; i-- > 0;) {
            let newChild = null;
            const childID = XMLParser.GetAttributeString(rawChildren[i], HWDB.ID_ATTRIBUTE);
            // String childLabel = getLabel(rawChildren[i], systemSetup);
            if (this._children !== null) {
                for (let j = nOldChildren; j-- > 0;) {
                    if (this._children[j].id.localeCompare(childID) === 0) {
                        newChild = this._children[j];
                        newChild.item = rawChildren[i];
                        // remove child from list in case another new child has same label, don't want to share old child element.
                        this._children[j] = this._children[--nOldChildren];
                        break;
                    }
                }
            }
            if (newChild === null) {
                newChild = new TreeElement(childID, rawChildren[i], this, this.systemSetup);
            }
            newChildren[i] = newChild;
        }
        return newChildren;
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
    getTextToDisplay() {
        return TreeElement.getLabel(this.item, this.systemSetup);
    }
    static getLabel(item, systemSetup) {
        let label = '';
        if (item !== null && systemSetup.flatRootNode !== null) {
            const node = new Tag(systemSetup.flatRootNode, item);
            label = node.getAttribute(HWDB.NAME_ATTRIBUTE);
            if (label === null || label.length === 0) {
                label = node.getAttribute(HWDB.ID_ATTRIBUTE);
            }
        }
        return label;
    }
    getDecoratorText() {
        if (this.item !== null && this.systemSetup.flatRootNode !== null) {
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
        var _a, _b;
        return (_b = (_a = this.children) === null || _a === void 0 ? void 0 : _a.length) !== null && _b !== void 0 ? _b : 0;
    }
    getValue(childIndex, column) {
        var _a;
        const child = (_a = this.children) === null || _a === void 0 ? void 0 : _a[childIndex];
        if (!child) {
            return '';
        }
        const decoratorText = column === 'name' ? undefined : child.getDecoratorText();
        if (decoratorText) {
            return `${child.getTextToDisplay()} (${decoratorText})`;
        }
        return child.getTextToDisplay();
    }
    setValue(childIndex, column, value) {
    }
    isExpandable(childIndex) {
        var _a, _b, _c;
        const child = (_a = this.children) === null || _a === void 0 ? void 0 : _a[childIndex];
        if (!child) {
            return false;
        }
        return ((_c = (_b = child.children) === null || _b === void 0 ? void 0 : _b.length) !== null && _c !== void 0 ? _c : 0) > 0;
    }
    getChildDataProvider(childIndex) {
        var _a;
        const child = (_a = this.children) === null || _a === void 0 ? void 0 : _a[childIndex];
        if (!child) {
            return nullTreeDataProvider;
        }
        return child;
    }
    lookupRowByName(name) {
        var _a, _b;
        return (_b = (_a = this.children) === null || _a === void 0 ? void 0 : _a.findIndex(child => child.getTextToDisplay() === name)) !== null && _b !== void 0 ? _b : -1;
    }
    getIconName(childIndex) {
        var _a, _b;
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
        const child = (_a = this.children) === null || _a === void 0 ? void 0 : _a[childIndex];
        const iconName = child ? this.systemSetup.getIconNameToDisplay(child) : 'nondebug';
        return (_b = iconMap[iconName]) !== null && _b !== void 0 ? _b : '';
    }
}
export class AbstractProperty {
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
        var _a;
        return (_a = this.description) !== null && _a !== void 0 ? _a : this.id;
    }
    get id() {
        var _a;
        return (_a = this.name) !== null && _a !== void 0 ? _a : undefined;
    }
    get infoText() {
        var _a;
        return (_a = this.toolTip) !== null && _a !== void 0 ? _a : undefined;
    }
    get errorText() {
        var _a;
        return (_a = this.descriptor.getPropertyError()) !== null && _a !== void 0 ? _a : undefined;
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
        var _a;
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
                child = (_a = child.nextSibling) !== null && _a !== void 0 ? _a : null;
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
        var _a;
        if (this.overriddenProperty === null) {
            if (this.overrideParent === null) {
                this.overrideParent = this.parentProperty.createDefaultProperty();
                // must create a Choice tag between properties
                const defaultParentNode = (_a = this.defaultProperty.getParent(null)) !== null && _a !== void 0 ? _a : null;
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
        var _a;
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
        (_a = this.overriddenProperty) === null || _a === void 0 ? void 0 : _a.setAttribute(HWDB.VALUE_ATTRIBUTE, valueToWrite);
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
        var _a;
        if (this.driverProperty !== null) {
            const defaults = (_a = this.defaultProperty.getParent(null)) !== null && _a !== void 0 ? _a : null;
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
export class SystemSetupEditor extends SystemSetupWriter {
    constructor() {
        super();
        this.errorReports = null;
        this.rootTreeElement = null;
        this.fileName = '';
        this.rootNode = null;
        this.flatRootNode = null;
        this.xmlReader.addAttributesToFilter([HWDB.COMPONENT_NAME, HWDB.XML_ATTRIBUTE]);
    }
    async load(xmlInput, fileName, isCancelled) {
        this.fileName = fileName;
        const rootDirectories = SystemSetupReader.getRootDirectories();
        this.rootNode = await this.xmlReader.parseConfig(xmlInput, rootDirectories, SystemSetupReader.getSchemaDirectory());
        this.flatRootNode = await this.xmlReader.convertToFlatFile(this.rootNode, fileName, rootDirectories, isCancelled);
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
        if (this.flatRootNode === null) {
            throw new Error('No xml file loaded to add byPass properties on.');
        }
        // Create the root node in case the file is an empty file or invalid XML file
        this.createFlatRootNode();
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
        var _a;
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
                const router = (_a = flatNode.getParent(HWDB.ROUTER_TAG)) !== null && _a !== void 0 ? _a : null;
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
        if (this.flatRootNode !== null) {
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
        var _a;
        if (this.flatRootNode !== null) {
            const flatProperty = new Tag(this.flatRootNode, object.item);
            const connectionNode = flatProperty.getParent(HWDB.CONNECTION_TAG);
            const connection = connectionNode && ((_a = this.rootTreeElement) === null || _a === void 0 ? void 0 : _a.findElement(connectionNode));
            if (connection) {
                return connection.getTextToDisplay();
            }
        }
        return null;
    }
    getRecommendedBoardName(object) {
        let boardName = null;
        let flatNode = null;
        if (object instanceof TreeElement && this.flatRootNode !== null) {
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
            if (configurationNode && this.flatRootNode !== null) {
                const parent = new Tag(this.flatRootNode, configurationNode);
                boardName = SystemSetupEditor.createUniqueId(parent, boardName, SystemSetupEditor.getComponentNames(parent, this.flatRootNode));
            }
        }
        return boardName;
    }
    renameBoard(element, recommendedBoardName) {
        var _a;
        if (this.flatRootNode === null) {
            throw new Error('No xml file to rename board on.');
        }
        const cpuNode = new Tag(this.flatRootNode, element.item);
        const connection = cpuNode.getParent(HWDB.CONNECTION_TAG);
        const connectionNode = connection && ((_a = this.rootTreeElement) === null || _a === void 0 ? void 0 : _a.findElement(connection));
        if (connectionNode) {
            this.rename(connectionNode, recommendedBoardName);
        }
    }
    getNodeType(element) {
        if (this.flatRootNode !== null) {
            const tag = new Tag(this.flatRootNode, element.item);
            return tag.getName();
        }
        return null;
    }
    getAttributeString(element, name) {
        let attribute = null;
        if (this.flatRootNode !== null) {
            const tag = new Tag(this.flatRootNode, element.item);
            attribute = tag.getAttribute(name);
        }
        return attribute === null ? '' : attribute;
    }
    getChildAttributeString(element, childName, attributeName) {
        let attribute = null;
        if (this.flatRootNode !== null) {
            const tag = new Tag(this.flatRootNode, element.item);
            attribute = tag.getChildAttribute(childName, attributeName);
        }
        return attribute === null ? '' : attribute;
    }
    getNodeDescriptionToDisplay(element) {
        let description = this.getErrorMessage(element);
        if (description === null && this.flatRootNode !== null) {
            const flatNode = new Tag(this.flatRootNode, element.item);
            description = flatNode.getAttribute(HWDB.DESCRIPTION_ATTRIBUTE);
        }
        return description === null ? '' : description;
    }
    findNodesOrIncludeTags(flatNode, includeTextNodes = false) {
        var _a, _b;
        if (this.rootNode === null) {
            throw new Error('No xml file loaded to find nodes or include tags on.');
        }
        let retVal = null;
        // parent must exist in original file first
        const flatParentNode = (_a = flatNode.getParent(null)) !== null && _a !== void 0 ? _a : null;
        const flatParent = flatParentNode && new Tag(flatNode, flatParentNode);
        const parent = flatParent && SystemSetupEditor.gotoNode(flatParent, this.flatRootNode, this.rootNode, false);
        if (parent !== null && flatNode.getAttribute(HWDB.MOVABLE_ATTRIBUTE).localeCompare('no') !== 0) {
            const id = flatNode.getAttribute(HWDB.ID_ATTRIBUTE);
            // find child node with matching href
            let child = parent.getFirstChild();
            let prevNode = null;
            while (child !== null) {
                if (id.localeCompare(XMLParser.GetAttributeString(child, HWDB.ID_ATTRIBUTE)) === 0) {
                    // found direct reference
                    if (retVal === null) {
                        retVal = new Array(2);
                    }
                    if (includeTextNodes && prevNode !== null && prevNode.nodeType === NodeTypes.TEXT_NODE) {
                        retVal.push(new Tag(parent, prevNode));
                    }
                    retVal.push(new Tag(parent, child));
                }
                prevNode = child;
                child = (_b = child.nextSibling) !== null && _b !== void 0 ? _b : null;
            }
        }
        return retVal;
    }
    async setPropertyByName(root, cpuId, propId, value) {
        if (root === null) {
            root = this.getRoot();
        }
        // set property on the root
        if (root !== null) {
            const r = root;
            if ((cpuId === null)
                || (r.id !== null && cpuId.localeCompare(r.id) === 0)) {
                const properties = await this.getProperties(root);
                if (properties !== null) {
                    properties.forEach(property => {
                        if (propId.localeCompare(property.getName()) === 0) {
                            this.setProperty(property, value);
                        }
                    });
                }
            }
            // recursively set property on children of root
            const children = this.getChildren(root);
            if (children !== null) {
                children.forEach(child => {
                    this.setPropertyByName(child, cpuId, propId, value);
                });
            }
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
        if (this.rootNode === null) {
            throw new Error('No xml file loaded to set properties on.');
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
            if ((choices === null || choices === void 0 ? void 0 : choices.length) === 2) {
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
            newProperty === null || newProperty === void 0 ? void 0 : newProperty.setAttribute(descriptor.getValueAttributeName(), flatProperty.getAttribute(descriptor.getValueAttributeName()));
            if (descriptor.hasSubProperties() && this.rootTreeElement !== null) {
                // special case if bypass property changed then errors could be
                // generated or removed.
                if (descriptor instanceof BypassBitsPropertyDescriptor) {
                    this.generateErrorReports();
                }
            }
        }
        return true;
    }
    rename(element, value) {
        if (this.flatRootNode !== null && this.rootNode !== null) {
            const node = new Tag(this.flatRootNode, element.item);
            // set new name in flat file
            node.setAttribute(HWDB.NAME_ATTRIBUTE, value);
            // set in top level system setup xml file as well.
            const topLevelNode = SystemSetupWriter.gotoNode(node, this.flatRootNode, this.rootNode, true);
            topLevelNode === null || topLevelNode === void 0 ? void 0 : topLevelNode.setAttribute(HWDB.NAME_ATTRIBUTE, value);
            // regenerate Error Messages
            this.generateErrorReports();
        }
    }
    getRoot() {
        if (this.rootTreeElement === null) {
            if (this.flatRootNode !== null) {
                this.rootTreeElement = new TreeElement(null, this.flatRootNode.getNode(), null, this);
            }
        }
        return this.rootTreeElement === null ? null : this.rootTreeElement;
    }
    getChildren(element) {
        return element.getChildren(this.getChildNodes(element.item));
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
        return null;
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
        var _a;
        let parent = null;
        if (object instanceof TreeElement) {
            parent = object.getParent();
        }
        else if (object instanceof Node) {
            let parentNode = null;
            parentNode = object.parentNode;
            while (parentNode !== null) {
                if (nodesToShow.has(parentNode.nodeName)) {
                    if (this.rootTreeElement !== null) {
                        parent = this.rootTreeElement.findElement(parentNode);
                    }
                    break; // found it
                }
                parentNode = (_a = parentNode.parentNode) !== null && _a !== void 0 ? _a : null;
            }
        }
        return parent === null ? this.getRoot() : parent;
    }
    findErrorLocation(errorLocation, parent) {
        var _a, _b;
        parent = (_a = parent !== null && parent !== void 0 ? parent : this.getRoot()) !== null && _a !== void 0 ? _a : undefined;
        let result;
        const thisErrorLocation = parent === null || parent === void 0 ? void 0 : parent.getErrorLocation();
        if (thisErrorLocation && thisErrorLocation.localeCompare(errorLocation) === 0)
            return parent;
        const children = (_b = (parent && this.getChildren(parent))) !== null && _b !== void 0 ? _b : undefined;
        if (children) {
            for (let i = 0; result === null && i < children.length; i++) {
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
        if (this.rootNode !== null) {
            const result = this.rootNode.serializeXMLDocument();
            const pos = result.indexOf('><configurations');
            if (pos > 0 && pos < 100) {
                return result.substring(0, pos + 1) + '\n' + result.substring(pos + 1);
            }
            return result;
        }
        return '';
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
            if ((iconName.localeCompare(HWDB.CPU_TAG) === 0 || iconName.localeCompare(HWDB.ROUTER_TAG) === 0) && this.flatRootNode !== null) {
                const node = new Tag(this.flatRootNode, element.item);
                if (SystemSetupEditor.getBypassBits(node) > 0 ||
                    node.getPropertyString(HWDB.BYPASS_PROPERTY, '0').localeCompare('1') === 0) {
                    iconName = (!longName) ? HWDB.BYPASS_PROPERTY : ((iconName.localeCompare(HWDB.CPU_TAG) === 0) ? HWDB.BYPASS_PROPERTY : HWDB.BYPASS_ROUTER_ICON);
                }
            }
        }
        return iconName;
    }
    generateErrorReports() {
        if (this.flatRootNode === null || !this.fileName) {
            return false;
        }
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
        if (this.rootNode === null || this.flatRootNode === null) {
            throw new Error('No xml file loaded to set all default jtag properties on.');
        }
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
    getFlatConnections() {
        const retVal = new Array(1);
        if (this.flatRootNode !== null) {
            const nConfigurations = this.flatRootNode.countChildrenByName(HWDB.CONFIGURATION_TAG);
            for (let i = 0; i < nConfigurations; i++) {
                const flatConfiguration = new Tag(this.flatRootNode, this.flatRootNode.getChildByName(HWDB.CONFIGURATION_TAG, i));
                const nConnections = flatConfiguration.countChildrenByName(HWDB.CONNECTION_TAG);
                for (let j = 0; j < nConnections; j++) {
                    retVal.push(flatConfiguration.getChildByName(HWDB.CONNECTION_TAG, j));
                }
            }
        }
        return retVal;
    }
    createFlatRootNode() {
        if (this.flatRootNode === null) {
            // Regenerate the configuration node
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
        }
    }
    getComponentList(type, parent) {
        var _a;
        const result = [];
        this.addComponentsToList(type, (_a = parent) !== null && _a !== void 0 ? _a : this.getRoot(), result);
        return result;
    }
    getCpusList() {
        return this.getComponentList('cpu');
    }
    addComponentsToList(type, node, list) {
        var _a;
        if (!node) {
            return;
        }
        if (this.getNodeType(node) === type) {
            list.push(node);
            return;
        }
        (_a = this.getChildren(node)) === null || _a === void 0 ? void 0 : _a.forEach(childNode => this.addComponentsToList(type, childNode, list));
    }
    getComponentName(component) {
        if (component && this.flatRootNode) {
            return new Tag(this.flatRootNode, component.item).getAttribute(HWDB.COMPONENT_NAME);
        }
    }
    findElementByPath(path) {
        let result = this.getRoot();
        path.split('/').forEach(segment => {
            var _a, _b;
            if (!result) {
                return null;
            }
            const row = result.lookupRowByName(segment);
            result = (_b = (_a = result.children) === null || _a === void 0 ? void 0 : _a[row]) !== null && _b !== void 0 ? _b : null;
        });
        return result;
    }
    findElementTypeByPath(path) {
        const element = this.findElementByPath(path);
        return element ? this.getNodeType(element) : null;
    }
}
SystemSetupEditor.builtinProperties = new Map();
//# sourceMappingURL=SystemSetupEditor.js.map