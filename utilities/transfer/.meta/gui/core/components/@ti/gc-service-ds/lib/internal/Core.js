/**
 *  Copyright (c) 2020, 2021 Texas Instruments Incorporated
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
/* eslint-disable prefer-rest-params */
/* eslint-disable @typescript-eslint/no-empty-interface */
/**
 * `Core` provides XDS/JTAG communication with TI device, such as run, halt, readMemory, writeMemory, etc...
 *
 * @example
 * ```typescript
 * import { ServiceRegistry } from '<path-to>/gc-core-service/lib/ServiceRegistry';
 * import { dsServiceType, debugCoreType } from '<path-to>/gc-service-ds/lib/DSService';
 *
 * const service = ServiceRegistry.getService(dsServiceType);
 * await service.configure(ccxmlString);
 * const [core] = await service.listCores(debugCoreType);
 * await core.connect();
 * await core.run();
 * await service.deConfigure();
 * ```
 *
 * @packageDocumentation
 */
import { AbstractDSModule, DSEventType } from './AbstractDSModule';
import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
import { ServicesRegistry } from '../../../gc-core-services/lib/ServicesRegistry';
import { backplaneServiceType } from '../../../gc-service-backplane/lib/BackplaneService';
const CONNECTION_TIMEOUT = 10000; /* default to 10 seconds timeout */
const ERR_CONNECT = new Error('Communication with target failed, no response.');
const backplaneService = ServicesRegistry.getService(backplaneServiceType);
export const refreshEventType = new DSEventType('refresh');
export const targetStateChangedEventType = new DSEventType('changed', 'targetState');
/**
 * @hidden
 */
export class CoreType {
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
export const debugCoreType = new CoreType('DebugCore');
export const nonDebugCoreType = new CoreType('NonDebugCore');
/**
 * @hidden
 */
export class Location {
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
export class DebugCore extends AbstractDebugCore {
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
        const { path: outPath } = await this.fileModule.write('ds-service-firmware.data', await (await backplaneService.getUtil()).encodeAsBase64(data));
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
            this.setDsModuleSettings(defaultSettings);
        }
    }
    async verifyProgram(data) {
        this.prolog(this.verifyProgram.name, '[...]');
        const { path: binPath } = await this.fileModule.write('ds-service-firmware-verify.bin', await (await backplaneService.getUtil()).encodeAsBase64(data));
        await this.dsModule.symbols.verifyProgram(binPath);
    }
    async loadBin(data, location, verifyBin = false) {
        this.prolog(this.loadBin.name, '[...]', location, verifyBin);
        const { path: binPath } = await this.fileModule.write('ds-service-firmware.bin', await (await backplaneService.getUtil()).encodeAsBase64(data));
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
    getDsModuleSettings() {
        return this.dsModule.settings.get([
            'VerifyAfterProgramLoad',
            'AutoRunToLabelName',
            'AutoRunToLabelOnRestart',
            'AutoRunToLabelOnReset'
        ]);
    }
    setDsModuleSettings(settings) {
        return this.dsModule.settings.set({
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
export class NonDebugCore extends AbstractDebugCore {
    constructor() {
        super(...arguments);
        this.type = nonDebugCoreType;
    }
}
//# sourceMappingURL=Core.js.map