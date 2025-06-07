import { connectionManager } from '../../gc-target-connection-manager/lib/ConnectionManager';
import { AbstractTransport, codecRegistry } from '../../gc-target-configuration/lib/TargetConfiguration';
import { ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { ProgramModelEncoderType, ProgramModelDecoderType, activeCoreChangedEventType } from '../../gc-model-program/lib/ProgramModel';
import { dsServiceType, ccsDebugCoreChangedEventType, ccsSymbolsChangedEventType, debugCoreType, DSProgressUpdateEventType, targetSupportProgressEventType, statusMessageEventType, LOAD_PROGRAM_FILENAME, Location } from '../../gc-service-ds/lib/DSService';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';
import { programLoaderServiceType } from '../../gc-service-program-loader/lib/ProgramLoaderService';
import { targetConfigServiceType } from '../../gc-service-target-config/lib/TargetConfigService';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

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
class XdsTransport extends AbstractTransport {
    constructor(params, serialPort) {
        super();
        this.params = params;
        this.serialPort = serialPort;
        this.encoderInputType = ProgramModelEncoderType;
        this.encoderOutputType = ProgramModelDecoderType;
        this.activeCoreMap = new Map(); // map of core names and aliases to active debuggable cores.
        this.activeCoreList = []; // list of active debuggable cores currently connected.
        this.isConfigured = false;
        this.callbackForStatusMessageEvent = (details) => {
            switch (details.type) {
                case 'info':
                    this.addProgressMessage(details.message);
                    break;
                case 'fatal':
                case 'error':
                    this.addErrorMessage(details.message, undefined, details.type === 'fatal');
                    break;
                case 'warning':
                    this.addWarningMessage(details.message);
                    break;
            }
        };
        this.dsLiteProgressUpdateHandler = (details) => {
            this.addProgressMessage(details.name, undefined, details.percent ?? 0);
        };
        this.connectionDeferred = GcPromise.defer();
        this.connectionSequencer = this.connectionDeferred.promise;
        this.console = new GcConsole('gc-transport-xds', this.id);
        connectionManager.registerTransport(this);
        codecRegistry.register(this);
        if (GcUtils.isCCS) {
            this.initCCSCores();
        }
    }
    async initCCSCores() {
        const ds = ServicesRegistry.getService(dsServiceType);
        const coreName = (await ds.getActiveCCSDebugCore())?.name;
        if (coreName) {
            this.updateActiveCore(coreName);
        }
        ds.addEventListener(ccsDebugCoreChangedEventType, ({ data }) => {
            this.updateActiveCore(data.coreName);
        });
        ds.addEventListener(ccsSymbolsChangedEventType, ({ data }) => {
            if (data.coreName && this.activeCoreMap.get('active')?.name === data.coreName) {
                this.fireEvent(activeCoreChangedEventType, { coreName: data.coreName });
            }
        });
    }
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    async getCloudAgentEventBroker() {
        const backplaneService = ServicesRegistry.getService(backplaneServiceType);
        return backplaneService.getSubModule('EventBroker');
    }
    get isXdsTransport() {
        return true;
    }
    get id() {
        return this.params.id || 'xds';
    }
    async updateActiveCore(name) {
        if (name) {
            const ds = ServicesRegistry.getService(dsServiceType);
            const cores = await ds.listCores(debugCoreType);
            const core = cores.filter(c => c.name === name)[0];
            if (core) {
                this.activeCoreMap.set('active', core);
            }
            else {
                this.activeCoreMap.delete('active');
            }
        }
        else {
            this.activeCoreMap.delete('active');
        }
        this.fireEvent(activeCoreChangedEventType, { coreName: name });
    }
    getCcxmlFileContents() {
        // use cached ccxml file if available, and params have not changed.
        const ccxmlParams = `${this.params.ccxmlPath || '*'}-${this.params.deviceName || '*'}-${this.params.connectionName || '*'}`;
        if (this.priorCcxmlFileParams !== ccxmlParams || !this.ccxmlFileContents) {
            if (this.params.ccxmlPath) {
                this.ccxmlFileContents = GcFiles.readTextFile(this.params.ccxmlPath);
            }
            else {
                const connectionType = this.serialPort ? 'UARTConnection' : this.params.connectionName;
                if (!connectionType || !this.params.deviceName) {
                    throw Error(`Missing ${connectionType ? 'device' : 'connection'}-name for <gc-transport-xds${this.params.id ? ' id="' + this.params.id + '"' : ''}>`);
                }
                const targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
                this.ccxmlFileContents = targetConfigService.getConfig(connectionType, this.params.deviceName);
            }
        }
        return this.ccxmlFileContents;
    }
    clearCcxmlFileContentsCache() {
        this.ccxmlFileContents = undefined;
        this.priorCcxmlFileParams = undefined;
    }
    async onConnect() {
        if (this.activeCoreMap.size !== 0) {
            throw Error('Programmer Error: this.activeCoreMap is not empty.');
        }
        let ccxml = undefined;
        if (!GcUtils.isCCS) {
            ccxml = await this.getCcxmlFileContents();
            if (this.serialPort) {
                this.assertStillConnecting();
                const [comName, baudRate] = await this.serialPort();
                const configService = ServicesRegistry.getService(targetConfigServiceType);
                if (this.params.deviceName) {
                    ccxml = configService.addCpuPropertiesToCCxmlFile(ccxml, this.params.deviceName, '<property Type="stringfield" Value="%SERIALPORT%" id="COM Port"/>\n' +
                        '<property Type="stringfield" Value="%BAUDRATE%" id="Baud Rate"/>\n');
                }
                ccxml = ccxml.replace(/%SERIALPORT%/g, comName);
                ccxml = ccxml.replace(/%BAUDRATE%/g, '' + baudRate);
                this.setConnectionDescription(`${comName}:${baudRate}`);
            }
            this.assertStillConnecting();
        }
        const targetSupportProgressListener = (eventData) => {
            this.addProgressMessage(`${eventData.name} ${eventData.subActivity}`, undefined, eventData.percent);
        };
        const ds = ServicesRegistry.getService(dsServiceType);
        ds.addEventListener(DSProgressUpdateEventType, this.dsLiteProgressUpdateHandler);
        ds.addEventListener(targetSupportProgressEventType, targetSupportProgressListener);
        ds.addEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
        try {
            await ds.configure(ccxml);
            this.isConfigured = true;
            this.console.debug('configured debug server');
            if (GcUtils.isCCS) {
                const eventBroker = await this.getCloudAgentEventBroker();
                const { data: activeCore } = await eventBroker.fetchData('activeCore');
                this.updateActiveCore(activeCore.name);
            }
        }
        finally {
            ds.removeEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
            ds.removeEventListener(targetSupportProgressEventType, targetSupportProgressListener);
            ds.removeEventListener(DSProgressUpdateEventType, this.dsLiteProgressUpdateHandler);
        }
        // allow initCore() promises to start connecting, loading programs, and running.
        this.connectionDeferred.resolve();
    }
    async onDisconnect() {
        // reset initCore() sequencer for next connection cycle.
        this.connectionDeferred = GcPromise.defer();
        this.connectionSequencer = this.connectionDeferred.promise;
        const ds = ServicesRegistry.getService(dsServiceType);
        if (!this.serialPort) {
            for (let i = 0; i < this.activeCoreList.length; i++) {
                const core = this.activeCoreList[i];
                try {
                    await core.disconnect();
                }
                catch (e) {
                    this.console.warning(`Disconnecting from core=${core.name} failed: ${e.message || e.toString()}`);
                }
            }
        }
        this.activeCoreMap.clear();
        this.activeCoreList = [];
        if (this.isConfigured) {
            this.isConfigured = false;
            await ds.deConfigure();
        }
    }
    addChildDecoder(decoder) {
    }
    deconfigure() {
    }
    dispose() {
        connectionManager.unregisterTransport(this);
        codecRegistry.unregister(this);
    }
    async readValue(expression, coreName) {
        const core = this.activeCoreMap.get(coreName || 'active');
        if (!core) {
            throw Error('Cannot read value when target is disconnected');
        }
        return core.readValue(expression);
    }
    async writeValue(expression, value, coreName) {
        const core = this.activeCoreMap.get(coreName || 'active');
        if (!core) {
            throw Error('Cannot write value when target is disconnected');
        }
        return await core.writeValue(expression, value);
    }
    async connectToTarget(params) {
        const ds = ServicesRegistry.getService(dsServiceType);
        const cores = await ds.listCores(debugCoreType);
        if (cores.length <= 0) {
            throw Error('Target configuration has no debuggable cores.');
        }
        let activeCore = cores[0];
        if (params.coreName) {
            activeCore = cores.reduce((pick, core) => core.name.endsWith(params.coreName) ? core : pick, undefined);
            if (!activeCore) {
                throw Error(`Target configuration has no debuggable core named ${params.coreName}`);
            }
        }
        this.console.debug(`active core: ${activeCore.toString()}`);
        if (!this.activeCoreList.includes(activeCore)) {
            this.assertStillConnecting();
            if (!this.serialPort) {
                try {
                    ds.addEventListener(DSProgressUpdateEventType, this.dsLiteProgressUpdateHandler);
                    ds.addEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
                    await activeCore.connect();
                }
                catch (e) {
                    // don't stop connect if core is already connected
                    if (!(e.message || e.toString()).includes('already connected')) {
                        throw e;
                    }
                }
                finally {
                    ds.removeEventListener(DSProgressUpdateEventType, this.dsLiteProgressUpdateHandler);
                    ds.removeEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
                }
            }
        }
        return activeCore;
    }
    async loadProgramOrSymbols(activeCore, params, programAlreadyLoaded = false, skipLoadingSymbols = false) {
        const loaderService = ServicesRegistry.getService(programLoaderServiceType);
        const coreDescription = params.coreName ? ` core="${params.coreName}"` : '';
        const description = `${this.deviceId || this.params.deviceName}${coreDescription}`;
        let message = '';
        const progressHandler = (details) => {
            if (details.name.endsWith(LOAD_PROGRAM_FILENAME)) {
                details = { ...details, name: message };
            }
            this.dsLiteProgressUpdateHandler(details);
        };
        try {
            loaderService.addEventListener(DSProgressUpdateEventType, progressHandler);
            loaderService.addEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
            if (params.programOrBinPath.endsWith('.bin')) {
                message = `Loading binary image for ${description} ...`;
                this.addProgressMessage(message);
                await loaderService.loadBin(activeCore, params.programOrBinPath, new Location(params.loadAddress ?? 0), params.verifyProgramPath, params.timeout);
            }
            else if (params.symbolsOnly || programAlreadyLoaded || this.serialPort) {
                message = `Loading symbols for ${description} ...`;
                this.addProgressMessage(message);
                await loaderService.loadSymbols(activeCore, params.programOrBinPath, params.timeout);
            }
            else {
                message = `Loading program for ${description} ...`;
                this.addProgressMessage(message);
                await loaderService.loadProgram(activeCore, params.programOrBinPath, true, params.timeout);
            }
        }
        catch (e) {
            throw Error(message.replace('...', `failed: ${e.message || e.toString()}`));
        }
        finally {
            loaderService.removeEventListener(DSProgressUpdateEventType, progressHandler);
            loaderService.removeEventListener(statusMessageEventType, this.callbackForStatusMessageEvent);
        }
    }
    async waitForSequencerThenDo(nextStep) {
        const done = GcPromise.defer();
        try {
            const wait = this.connectionSequencer;
            this.connectionSequencer = done.promise;
            await wait;
            this.assertStillConnecting();
            return await nextStep();
        }
        finally {
            done.resolve();
        }
    }
    async initCore(params, programAlreadyLoaded = false, skipLoadingSymbols = false) {
        const activeCore = await this.waitForSequencerThenDo(() => {
            if (GcUtils.isCCS) {
                return Promise.resolve(undefined);
            }
            else {
                return this.connectToTarget(params);
            }
        });
        const coreName = params.coreName || 'active';
        if (activeCore && !this.activeCoreList.includes(activeCore)) {
            try {
                if (params.programOrBinPath) {
                    await this.waitForSequencerThenDo(() => this.loadProgramOrSymbols(activeCore, params, programAlreadyLoaded, skipLoadingSymbols));
                }
                else if (!skipLoadingSymbols) {
                    throw Error(`Missing a programOrBinPath property for core=${coreName}.`);
                }
                if (!this.serialPort) {
                    await this.waitForSequencerThenDo(() => activeCore.run());
                }
            }
            catch (err) {
                if (!this.serialPort) {
                    await activeCore.disconnect();
                }
                throw err;
            }
            this.activeCoreList.push(activeCore);
            this.activeCoreMap.set(activeCore.name, activeCore);
        }
        if (activeCore) {
            this.activeCoreMap.set(coreName, activeCore);
        }
        return activeCore;
    }
    async run(coreName) {
        const core = this.activeCoreMap.get(coreName || 'active');
        if (!core) {
            throw Error('Cannot run when target is disconnected');
        }
        await core.run();
    }
    async halt(coreName) {
        const core = this.activeCoreMap.get(coreName || 'active');
        if (!core) {
            throw Error('Cannot halt when target is disconnected');
        }
        await core.halt();
    }
}

export { XdsTransport };
//# sourceMappingURL=XdsTransport.js.map
