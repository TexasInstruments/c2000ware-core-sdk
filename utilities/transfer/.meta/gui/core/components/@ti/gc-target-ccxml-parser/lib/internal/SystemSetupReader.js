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
import { ProcessorID } from './ProcessorID';
import { StringBuilder } from './StringBuilder';
import { Tag } from './Tag';
import { XMLParser } from './XMLParser';
const CCXML_FILEEXT = 'ccxml';
const CACHE_FILENAME = 'targetdb.cache';
const CACHE_TIMESTAMP_FILENAME = 'targetdb.timestamp';
const TIMESTAMP_FILENAME = 'timestamp';
export class ErrorReport {
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
            this.driverFilename = driverFilename !== null && driverFilename !== void 0 ? driverFilename : null;
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
export class Cpu extends AbstractSystemSetupComponent {
    constructor(id, name, isa, connection) {
        super();
        this.connection = null;
        this.isa = null;
        if (id instanceof CpuIdentifier) {
            this.id = id;
            this.name = (!name || name.length === 0) ? null : name;
            this.isa = (!isa || isa.length === 0) ? null : isa;
            this.connection = connection !== null && connection !== void 0 ? connection : null;
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
        this.listOfOperations = listOfOperations !== null && listOfOperations !== void 0 ? listOfOperations : [];
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
        var _a, _b;
        return (_b = (_a = this.cur) === null || _a === void 0 ? void 0 : _a.connectionType) !== null && _b !== void 0 ? _b : '';
    }
    getName() {
        var _a, _b;
        return (_b = (_a = this.cur) === null || _a === void 0 ? void 0 : _a.driverToAdd.isa) !== null && _b !== void 0 ? _b : null;
    }
    getDescription() {
        var _a, _b;
        return (_b = (_a = this.cur) === null || _a === void 0 ? void 0 : _a.driverToAdd.description) !== null && _b !== void 0 ? _b : null;
    }
    getProcId() {
        var _a, _b;
        return (_b = (_a = this.cur) === null || _a === void 0 ? void 0 : _a.driverToAdd.procId) !== null && _b !== void 0 ? _b : null;
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
                    connections === null || connections === void 0 ? void 0 : connections.push(setupElement);
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
        var _a;
        ((_a = this.cpuOperations) !== null && _a !== void 0 ? _a : []).forEach(cpuOperation => {
            if (cpuOperation instanceof AddDeviceOperation) {
                return cpuOperation.partnum;
            }
        });
        return null;
    }
    doesDeviceHaveProcessorsTag() {
        var _a;
        ((_a = this.cpuOperations) !== null && _a !== void 0 ? _a : []).forEach(cpuOperation => {
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
        var _a;
        const result = new StringBuilder();
        result.append(' last modified = ');
        result.append(this.lastModified.toString());
        if (this.lastErrorMessage !== null) {
            result.append('\n\tException = ');
            result.append((_a = this.lastErrorMessage.message) !== null && _a !== void 0 ? _a : this.lastErrorMessage.toString());
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
    var _a;
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
                const capableMultiProccessor = driverTag.getPropertyString('multiProcessor', 'yes').toLowerCase().localeCompare('yes') === 0;
                const driver = new Driver(isaType, procId, driverId, debuggable, isaDescription, driverFilename, capableMultiProccessor);
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
        childNode = (_a = childNode.nextSibling) !== null && _a !== void 0 ? _a : null;
    }
}
function createPropertyOperation(node, parentId) {
    var _a, _b, _c;
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
                let subPropertyNode = (_a = childNode.firstChild) !== null && _a !== void 0 ? _a : null;
                while (subPropertyNode !== null) {
                    const subProperty = new Tag(node, subPropertyNode);
                    tag = subProperty.getName();
                    if (tag.localeCompare(HWDB.PROPERTY_TAG) === 0) {
                        choice.addSubProperty(createPropertyOperation(subProperty, parentId));
                    }
                    subPropertyNode = (_b = subPropertyNode.nextSibling) !== null && _b !== void 0 ? _b : null;
                }
            }
            childNode = (_c = childNode.nextSibling) !== null && _c !== void 0 ? _c : null;
        }
        return choiceList;
    }
}
export class SystemSetupReader {
    static getSchemaDirectory() {
        return this.schemaDirectory;
    }
    static getTargetDbDirectory() {
        return this.installDirectories[0] + '/';
    }
    static getRootDirectories() {
        return this.installDirectories;
    }
    onTargetDBDirectoriesChanged() {
    }
    static findNode(flatRoot, forCpu) {
        const id = forCpu instanceof Cpu ? forCpu.id : forCpu;
        if (id.parent !== null) {
            const flatParentNode = this.findNode(flatRoot, id.parent);
            if (flatParentNode === null)
                return null; // found: not,abort.
            flatRoot = new Tag(flatRoot, flatParentNode);
        }
        return flatRoot.getChildByID(null, id.id);
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
        var _a, _b, _c;
        const connectionNames = new Array();
        const cpuNames = new Array();
        const subpathNames = new Array();
        const errorMessages = new Array();
        let debuggableCpuCount = 0;
        let lastMultiBoardCapableCpu = null;
        let lastMultiProcessorCapableCpu = null;
        if (cpuCacheItem !== null) {
            const setupElements = cpuCacheItem.getSetupElements(null, fileName, SystemSetupReader.installDirectories);
            //    		Array<Connection> connections = cpuCacheItem.getConnections(fileName, installDirectories);
            // test for unique connection names
            if (setupElements !== null) {
                setupElements.forEach(setupElement => {
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
                        driverLocation = (_a = setupElement.getDriverLocation()) !== null && _a !== void 0 ? _a : '';
                        break;
                    }
                }
                for (let i = setupElements.length; i-- > 0;) {
                    const setupElement = setupElements[i];
                    if (setupElement instanceof Cpu) {
                        const cpu = setupElement;
                        let name = cpu.getName();
                        if (!name.match(/^[a-zA-Z][a-zA-Z0-9_]*$/)) {
                            errorMessages.push(new ErrorReport('Name has invalid characters.  Cpu, router, and subpath names must begin with a letter and only contain numbers letters and the underscore character.', cpu.toString()));
                        }
                        // test for unique and valid names
                        name = cpu.toString().toLowerCase();
                        if (cpu.isSubpath()) {
                            if (subpathNames.includes(name)) {
                                errorMessages.push(new ErrorReport('More than one subpath is named ' + cpu.getName(), cpu.toString()));
                            }
                            else {
                                subpathNames.push(name);
                            }
                        }
                        else {
                            if (cpuNames.includes(name)) {
                                errorMessages.push(new ErrorReport('More than one cpu is named ' + cpu.getName(), cpu.toString()));
                            }
                            else {
                                cpuNames.push(name);
                            }
                            // test for missing drivers
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
                    errorMessages.push(new ErrorReport('One or more drivers does not support heterogeneous multiprocessing.\nPlease bypass one or more processors.', (_b = lastMultiBoardCapableCpu === null || lastMultiBoardCapableCpu === void 0 ? void 0 : lastMultiBoardCapableCpu.toString()) !== null && _b !== void 0 ? _b : null));
                }
                else if (capableMultiProcessor === false && debuggableCpuCount > 1) {
                    errorMessages.push(new ErrorReport('One or more drivers does not support multiple processors.\nPlease bypass all but one processor.', (_c = lastMultiProcessorCapableCpu === null || lastMultiProcessorCapableCpu === void 0 ? void 0 : lastMultiProcessorCapableCpu.toString()) !== null && _c !== void 0 ? _c : null));
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
//# sourceMappingURL=SystemSetupReader.js.map