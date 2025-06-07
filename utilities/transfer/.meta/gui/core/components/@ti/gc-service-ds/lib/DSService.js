import { EventType, Events } from '../../gc-core-assets/lib/Events';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';
import { ServicesRegistry, ServiceType } from '../../gc-core-services/lib/ServicesRegistry';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

/**
 *  Copyright (c) 2020, 2023 Texas Instruments Incorporated
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
 */
/**
 * @hidden
 */
const MODULE_NAME = 'gc-service-ds';
class DSEventType extends EventType {
    constructor(eventName, subObjectName) {
        super(eventName);
        this.subObjectName = subObjectName;
        this.dsEventType = true;
    }
}
class DSEventBrokerType extends EventType {
    constructor() {
        super(...arguments);
        this.dsEventBrokerEventType = true;
    }
}
/**
 * @hidden
 */
class AbstractDSModule extends Events {
    constructor(moduleName, dsModule) {
        super();
        this.moduleName = moduleName;
        this.console = new GcConsole(MODULE_NAME);
        // @ts-ignore
        this.dsModule = dsModule;
    }
    async ensureDsModule() {
        if (!this.dsModule) {
            const backplaneService = ServicesRegistry.getService(backplaneServiceType);
            this.dsEventBroker = await backplaneService.getSubModule('EventBroker');
            this.dsModule = await backplaneService.getSubModule('DS');
        }
    }
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    prolog(apiName, ...params) {
        this.console.logAPI(apiName, ...params);
    }
    toString() {
        return this.moduleName;
    }
    isDSEvent(object) {
        return 'dsEventType' in object;
    }
    isEventBrokerEvent(object) {
        return 'dsEventBrokerEventType' in object;
    }
    addEventListener(type, listener) {
        this.prolog(this.addEventListener.name, ...arguments);
        if (this.isDSEvent(type)) {
            this.ensureDsModule().then(() => {
                if (type.subObjectName) {
                    // @ts-ignore
                    this.dsModule[type.subObjectName].addListener(type.eventName, listener);
                }
                else {
                    // @ts-ignore
                    this.dsModule.addListener(type.eventName, listener);
                }
            });
        }
        else if (this.isEventBrokerEvent(type)) {
            this.ensureDsModule().then(() => {
                this.dsEventBroker.addListener(type.eventName, listener);
            });
        }
        else {
            super.addEventListener(type, listener);
        }
    }
    removeEventListener(type, listener) {
        this.prolog(this.removeEventListener.name, ...arguments);
        if (this.isDSEvent(type)) {
            this.ensureDsModule().then(() => {
                if (type.subObjectName) {
                    // @ts-ignore
                    this.dsModule[type.subObjectName].removeListener(type.eventName, listener);
                }
                else {
                    // @ts-ignore
                    this.dsModule.removeListener(type.eventName, listener);
                }
            });
        }
        else if (this.isEventBrokerEvent(type)) {
            this.ensureDsModule().then(() => {
                this.dsEventBroker.removeListener(type.eventName, listener);
            });
        }
        else {
            super.removeEventListener(type, listener);
        }
    }
}

/**
 *  Copyright (c) 2020, 2025 Texas Instruments Incorporated
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
 */
const CONNECTION_TIMEOUT = 10000; /* default to 10 seconds timeout */
const ERR_CONNECT = new Error('Communication with target failed, no response.');
const backplaneService$1 = ServicesRegistry.getService(backplaneServiceType);
const refreshEventType = new DSEventType('refresh');
const targetStateChangedEventType = new DSEventType('changed', 'targetState');
const LOAD_PROGRAM_FILENAME = 'ds-service-firmware.data';
/**
 * @hidden
 */
class CoreType {
    constructor(name) {
        this.name = name;
    }
    asCore(core) {
        return this === core.type ? core : undefined;
    }
    toString() {
        return this.name;
    }
}
const debugCoreType = new CoreType('DebugCore');
const nonDebugCoreType = new CoreType('NonDebugCore');
/**
 * @hidden
 */
class Location {
    constructor(address /* for address > 53 bits, use hex string */, page = 0) {
        this.address = address;
        this.page = page;
    }
    toString() {
        let result = this.address.toString(16).padStart(8, '0') + '@' + this.page;
        if (!result.startsWith('0x'))
            result = '0x' + result;
        return result;
    }
}
/**
 * @hidden
 */
class AbstractDebugCore extends AbstractDSModule {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    constructor(fileModule, name, dsModule) {
        super(name, dsModule);
        this.fileModule = fileModule;
    }
    get name() {
        return this.moduleName;
    }
}
/**
 * @hidden
 */
class DebugCore extends AbstractDebugCore {
    constructor() {
        super(...arguments);
        this.type = debugCoreType;
    }
    async getResets() {
        this.prolog(this.getResets.name, ...arguments);
        const results = new Array();
        Object.entries((await this.dsModule.targetState.getResets()).nameValueMap).forEach(([type, allowed]) => {
            results.push({ type: type, allowed: allowed });
        });
        return results;
    }
    async reset(type) {
        this.prolog(this.reset.name, ...arguments);
        await this.dsModule.targetState.reset(type);
    }
    async connect() {
        this.prolog(this.connect.name, ...arguments);
        await GcPromise.timeout(this.dsModule.targetState.connect(), CONNECTION_TIMEOUT, ERR_CONNECT);
    }
    async disconnect() {
        this.prolog(this.disconnect.name, ...arguments);
        await this.dsModule.targetState.disconnect();
    }
    async run(runFree = false) {
        this.prolog(this.run.name, ...arguments);
        await this.dsModule.targetState.run(runFree);
    }
    async halt() {
        this.prolog(this.halt.name, ...arguments);
        await this.dsModule.targetState.halt();
    }
    async loadProgram(data, symbolOnly, verifyProgram = false) {
        this.prolog(this.loadProgram.name, '[...]', symbolOnly, verifyProgram);
        const { path: outPath } = await this.fileModule.write(LOAD_PROGRAM_FILENAME, await (await backplaneService$1.getUtil()).encodeAsBase64(data));
        const defaultSettings = await this.getDsModuleSettings();
        await this.setDsModuleSettings({
            VerifyAfterProgramLoad: verifyProgram ? 'Fast verification' : 'No verification'
        });
        try {
            if (symbolOnly) {
                await this.dsModule.symbols.loadSymbols(outPath);
            }
            else {
                await this.dsModule.symbols.loadProgram(outPath);
            }
        }
        finally {
            await this.setDsModuleSettings(defaultSettings);
        }
    }
    async verifyProgram(data) {
        this.prolog(this.verifyProgram.name, '[...]');
        const { path: binPath } = await this.fileModule.write('ds-service-firmware-verify.bin', await (await backplaneService$1.getUtil()).encodeAsBase64(data));
        await this.dsModule.symbols.verifyProgram(binPath);
    }
    async loadBin(data, location, verifyBin = false) {
        this.prolog(this.loadBin.name, '[...]', location, verifyBin);
        const { path: binPath } = await this.fileModule.write('ds-service-firmware.bin', await (await backplaneService$1.getUtil()).encodeAsBase64(data));
        const defaultSettings = await this.getDsModuleSettings();
        await this.setDsModuleSettings({
            VerifyAfterProgramLoad: verifyBin ? 'Fast verification' : 'No verification'
        });
        try {
            await this.dsModule.symbols.loadProgramOnly({ filename: binPath, loadAddress: location.address });
        }
        finally {
            this.setDsModuleSettings(defaultSettings);
        }
    }
    async evaluate(expression, frame = 0) {
        this.prolog(this.evaluate.name, ...arguments);
        return await this.dsModule.expressions.evaluate(expression, frame);
    }
    get registers() {
        return this.dsModule.registers;
    }
    async getDsModuleSettings() {
        return (await this.dsModule.settings.get([
            'VerifyAfterProgramLoad',
            'AutoRunToLabelName',
            'AutoRunToLabelOnRestart',
            'AutoRunToLabelOnReset'
        ])).nameValueMap;
    }
    async setDsModuleSettings(settings) {
        await this.dsModule.settings.set({
            VerifyAfterProgramLoad: 'No verification',
            AutoRunToLabelName: '',
            AutoRunToLabelOnRestart: 'false',
            AutoRunToLabelOnReset: 'false',
            ...settings
        });
    }
    static getArrayValueConverter(type) {
        if (this.arrayValueConverter.get(type) === undefined) {
            this.arrayValueConverter.set(type, data => data.values.map(value => this.convertDataType(type, value)));
        }
        return this.arrayValueConverter.get(type);
    }
    static convertDataType(type, value) {
        if (type) {
            if (type.indexOf('enum') === 0 || this.supportedScalarTypes[type]) {
                // check for negative numbers
                if (value.indexOf('0x') === 0 && value.charAt(2) > '7') {
                    return (+value) - (1 << (4 * (value.length - 2))); // converts text to number while performing a negation at the same time.
                }
                else {
                    return +value; // converts text to number without altering it.
                }
            }
            else if (type.indexOf('unsigned') === 0) {
                return +value;
            }
        }
        return value;
    }
    onReadStringComplete(data) {
        return data.text;
    }
    async onReadMemberComplete(data) {
        if (data.arrayInfo && data.arrayInfo.size) {
            return await this.readArrayValue(data.value, data.arrayInfo.elementType, data.arrayInfo.size, data.arrayInfo.expression);
        }
        else if (data.type === 'char *' || data.type === 'unsigned char *') {
            return await this.dsModule.expressions.readString(data.value, 80, 0).then(this.onReadStringComplete);
        }
        else {
            return DebugCore.convertDataType(data.type, data.value);
        }
    }
    onReadValueComplete(data) {
        return data.members.length > 0 && !data.type.endsWith('*') ? this.readStructValue(data.members) : this.onReadMemberComplete(data);
    }
    async readArrayValue(location, type, size, expression) {
        if (type.indexOf('[') > 0 || type.indexOf('struct') === 0) {
            const promises = new Array();
            for (let i = 0; i < size; ++i) {
                promises.push(this.dsModule.expressions.evaluate(`${expression}[${i}]`).then(this.onReadValueComplete.bind(this)));
            }
            return await Promise.all(promises);
        }
        else if (type === 'char') {
            return await this.dsModule.expressions.readString(location, size, 0).then(this.onReadStringComplete.bind(this));
        }
        else {
            return await this.dsModule.memory.read(location, type, size).then(DebugCore.getArrayValueConverter(type));
        }
    }
    async readStructValue(members) {
        const promises = new Array();
        members.forEach(m => promises.push(this.dsModule.expressions.evaluate(m.expression).then(this.onReadValueComplete.bind(this))));
        const expressValues = await Promise.all(promises);
        const result = {};
        for (let i = 0; i < expressValues.length; ++i) {
            result[members[i].name] = expressValues[i];
        }
        return result;
    }
    async doMemoryWrite(arrayOfValuesToWrite, data) {
        if (data.members.length > 0) {
            throw new Error('Cannot write array values to a struct.');
        }
        else if (!(data.arrayInfo && data.arrayInfo.size)) {
            throw new Error(`Cannot write array values to a non array type of ${data.type}.`);
        }
        let valueToWrite = arrayOfValuesToWrite;
        if (data.arrayInfo && data.arrayInfo.size) {
            /* truncate the array to the correct length */
            valueToWrite = arrayOfValuesToWrite.slice(0, data.arrayInfo.size);
            /* terminate char array */
            if (data.arrayInfo.elementType === 'char') {
                valueToWrite[valueToWrite.length - 1] = 0;
            }
        }
        return await this.dsModule.memory.write(data.value, data.arrayInfo.elementType, valueToWrite);
    }
    /** *************************************************************************************************************************** */
    /** Private helper methods for readValue and writeValue end ******************************************************************* */
    /** *************************************************************************************************************************** */
    async readValue(expression) {
        this.prolog(this.readValue.name, ...arguments);
        return await this.evaluate(expression).then(this.onReadValueComplete.bind(this));
    }
    async writeValue(expression, value) {
        this.prolog(this.writeValue.name, expression, Array.isArray(value) && value.length > 128 ? '[...]' : value);
        if (typeof value === 'object') {
            if (value instanceof Array) {
                await this.dsModule.expressions.evaluate(expression).then(this.doMemoryWrite.bind(this, value));
            }
            else {
                const promises = [];
                for (const fieldName in value) {
                    if (Object.prototype.hasOwnProperty.call(value, fieldName)) {
                        promises.push(this.writeValue(`${expression}.${fieldName}`, value[fieldName]));
                    }
                }
                await Promise.all(promises);
            }
        }
        else if (typeof value === 'string') {
            await this.dsModule.expressions.evaluate(expression).then(this.doMemoryWrite.bind(this, (value + '\0').split('').map(e => e.charCodeAt(0))));
        }
        else {
            await this.dsModule.expressions.evaluate(`${expression}=${value}`);
        }
    }
    async readMemory(location, typeOrBytes, size) {
        this.prolog(this.readMemory.name, ...arguments);
        size = size || 1;
        typeOrBytes = typeOrBytes || 'int';
        const data = await this.dsModule.memory.read(location.toString(), typeOrBytes, size);
        return data && data.values ? Uint8Array.from(data.values) : new Uint8Array();
    }
    async writeMemory(location, typeOrBytes, arrayOfValues) {
        this.prolog(this.writeMemory.name, location, typeOrBytes, '[...]');
        typeOrBytes = typeOrBytes || 'int';
        const values = [];
        arrayOfValues.forEach(e => {
            values.push('0x' + e.toString(16));
        });
        await this.dsModule.memory.write(location.toString(), typeOrBytes, values);
    }
}
DebugCore.supportedScalarTypes = { 'char': true, int: true, short: true, long: true, float: true, double: true };
/** *************************************************************************************************************************** */
/** Private helper methods for readValue and writeValue begin ***************************************************************** */
/** *************************************************************************************************************************** */
DebugCore.arrayValueConverter = new Map();
/**
 * @hidden
 */
class NonDebugCore extends AbstractDebugCore {
    constructor() {
        super(...arguments);
        this.type = nonDebugCoreType;
    }
}

/**
 *  Copyright (c) 2020, 2025 Texas Instruments Incorporated
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
 */
const ccsDebugSessionChangedEventType = new DSEventBrokerType('debugSessionChanged');
const ccsDebugCoreChangedEventType = new DSEventBrokerType('debugCoreChanged');
const ccsSymbolsChangedEventType = new DSEventBrokerType('symbolsChanged');
const gelOutputEventType = new DSEventType('gelOutput');
const configChangedEventType = new DSEventType('configChanged');
const statusMessageEventType = new DSEventType('statusMessage');
const targetSupportProgressEventType = new EventType('targetSupportProgress');
const DSProgressUpdateEventType = new EventType('DSProgressUpdate');
const DSDialogEventType = new EventType('DSDialogEvent');
const dsServiceType = new ServiceType(MODULE_NAME);
/**
 * DS service implementation
 */
const backplaneService = ServicesRegistry.getService(backplaneServiceType);
class DSService extends AbstractDSModule {
    constructor(cores = []) {
        super('DS');
        this.cores = cores;
        this._timeOfLastDeConfigure = 0;
        this._ccxml = undefined;
        this.dsModuleListenersAdded = false;
    }
    async configure(ccxml) {
        this.prolog(this.configure.name, ...arguments);
        this._ccxml = ccxml;
        let cores = [];
        let nonDebugCores = [];
        const fileModule = await backplaneService.getSubModule('File');
        if (ccxml) {
            // create temporary ccxml file
            const { path: ccxmlPath } = await fileModule.write('ds-service.ccxml', await (await backplaneService.getUtil()).encodeAsBase64(ccxml));
            // initialize target support
            if (!GcUtils.isInDesigner && GcUtils.isCloud) {
                const targetSupport = await backplaneService.getSubModule('TargetSupport');
                // eslint-disable-next-line @typescript-eslint/no-explicit-any
                const progressListener = (params) => {
                    this.fireEvent(targetSupportProgressEventType, params);
                };
                targetSupport.addListener('progress', progressListener);
                await targetSupport.add(ccxmlPath);
                targetSupport.removeListener('progress', progressListener);
            }
            // Work around for DSLite issue where it crashes if configure is called too soon after deconfigure.
            // TODO: remove this workaround after Jira CCBT-2711, filed against CCBT-2711 is resolved.
            const delay = 250 - Date.now() + this._timeOfLastDeConfigure;
            if (delay > 0) {
                await GcUtils.delay(delay); // make sure at least 250ms has elapsed since calling deConfigure().
            }
            await this.ensureDsModule(); // get the the DS module, if we haven't already.
            if (!this.dsModuleListenersAdded) {
                this.addDSModuleListeners();
            }
            this.dsModule.dialogs.willHandleDialogs(this.hasAnyListeners(DSDialogEventType));
            // configure the ds module with the ccxml path
            const result = await this.dsModule.configure(ccxmlPath);
            cores = result.cores;
            nonDebugCores = result.nonDebugCores;
        }
        else {
            await this.ensureDsModule(); // get the the DS module, if we haven't already.
            const result = await this.dsModule.listCores();
            cores = result.cores;
            nonDebugCores = result.nonDebugCores;
        }
        // get the core module for each core
        this.cores.push(...await Promise.all(cores.map(async (name) => new DebugCore(fileModule, name, await this.dsModule.getSubModule(name)))));
        const optionalNonDebugCores = await Promise.all(nonDebugCores.map(async (name) => {
            try {
                return new NonDebugCore(fileModule, name, await this.dsModule.getSubModule(name));
            }
            catch (e) {
                this.console.warning(`Failed to getSubModule(${name}: ${e.message || e.toString}`);
                return null; // Don't fail configuration if a non-debug task cannot be instantiated through cloud agent.
            }
        }));
        this.cores.push(...optionalNonDebugCores.filter(core => core !== null));
    }
    addDSModuleListeners() {
        this.dsModule.dialogs.addListener('new', (params) => {
            const DSDialogParams = { ...params, response: this.dsModule.dialogs.setButtonResponse };
            this.fireEvent(DSDialogEventType, DSDialogParams);
        });
        this.dsModule.progress.addListener('update', (params) => {
            this.fireEvent(DSProgressUpdateEventType, params);
        });
        this.dsModuleListenersAdded = true;
    }
    async deConfigure() {
        this.prolog(this.deConfigure.name, ...arguments);
        if (this.dsModule) {
            this.cores.splice(0, this.cores.length);
            if (this._ccxml) {
                await this.dsModule.deConfigure();
            }
            this._timeOfLastDeConfigure = Date.now();
        }
        this._ccxml = undefined;
    }
    async listCores(coreType) {
        this.prolog(this.listCores.name, ...arguments);
        return this.cores.filter(e => !coreType || coreType.asCore(e));
    }
    async getActiveCCSDebugCore() {
        if (GcUtils.isCCS) {
            try {
                const eventBroker = await this.getEventBroker();
                const { data: activeCore } = await eventBroker.fetchData('activeCore');
                return (await this.listCores()).filter(e => e.name === activeCore?.name)[0];
            }
            catch {
                // ignore - fetchData failed if there is no data to fetch
            }
        }
        return undefined;
    }
    async getActiveCCSDebugSession() {
        if (GcUtils.isCCS) {
            try {
                const eventBroker = await this.getEventBroker();
                const { data: debugSession } = await eventBroker.fetchData('debugSession');
                return debugSession?.name;
            }
            catch {
                // ignore - fetchData failed if there is no data to fetch
            }
        }
        return undefined;
    }
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    async getEventBroker() {
        const backplaneService = ServicesRegistry.getService(backplaneServiceType);
        return backplaneService.getSubModule('EventBroker');
    }
    changeDSDialogHandler(willHandle) {
        this.dsModule.dialogs.willHandleDialogs(willHandle);
    }
}
ServicesRegistry.register(dsServiceType, DSService);

export { AbstractDSModule, CoreType, DSDialogEventType, DSEventBrokerType, DSEventType, DSProgressUpdateEventType, DebugCore, LOAD_PROGRAM_FILENAME, Location, MODULE_NAME, NonDebugCore, ccsDebugCoreChangedEventType, ccsDebugSessionChangedEventType, ccsSymbolsChangedEventType, configChangedEventType, debugCoreType, dsServiceType, gelOutputEventType, nonDebugCoreType, refreshEventType, statusMessageEventType, targetStateChangedEventType, targetSupportProgressEventType };
//# sourceMappingURL=DSService.js.map
