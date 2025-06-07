import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { Events } from '../../gc-core-assets/lib/Events';
import { dsServiceType, DSProgressUpdateEventType, statusMessageEventType, targetSupportProgressEventType, debugCoreType, Location } from '../../gc-service-ds/lib/DSService';
export { statusMessageEventType } from '../../gc-service-ds/lib/DSService';
import { GcFiles } from '../../gc-core-assets/lib/GcFiles';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { targetConfigServiceType } from '../../gc-service-target-config/lib/TargetConfigService';

/**
 *  Copyright (c) 2019, 2025 Texas Instruments Incorporated
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
const TIMEOUT_MESSAGE = (param1) => `Timeout while loading ${param1}.`;
const DEFAULT_TIMEOUT = 75000;
const MODULE_NAME = 'gc-service-program-loader';
const console = new GcConsole(MODULE_NAME);
const updateFlashProgress = (monitor, message, progress) => {
    if (monitor.cancelled) {
        console.info('Flash aborted!');
        throw Error('Flash aborted!');
    }
    else {
        console.info(message);
        monitor.onProgress(message, progress);
    }
};
const DefaultProgressMonitor = new class {
    get cancelled() {
        return false;
    }
    onProgress(status, progress) {
        return true;
    }
};
const programLoaderServiceType = new ServiceType(MODULE_NAME);
class ProgramLoaderService extends Events {
    constructor() {
        super(...arguments);
        this.dsService = ServicesRegistry.getService(dsServiceType);
        this.targetConfigService = ServicesRegistry.getService(targetConfigServiceType);
    }
    addEventListener(type, listener) {
        console.logAPI(`${ProgramLoaderService.name}::${this.addEventListener.name}`, ...arguments);
        switch (type) {
            case statusMessageEventType:
                this.dsService.addEventListener(statusMessageEventType, listener);
                break;
            case DSProgressUpdateEventType:
                this.dsService.addEventListener(DSProgressUpdateEventType, listener);
                break;
        }
        super.addEventListener(type, listener);
    }
    removeEventListener(type, listener) {
        console.logAPI(`${ProgramLoaderService.name}::${this.removeEventListener.name}`, ...arguments);
        switch (type) {
            case statusMessageEventType:
                this.dsService.removeEventListener(statusMessageEventType, listener);
                break;
            case DSProgressUpdateEventType:
                this.dsService.removeEventListener(DSProgressUpdateEventType, listener);
                break;
        }
        super.removeEventListener(type, listener);
    }
    async loadProgram(core, programPath, verifyProgram = false, timeout = DEFAULT_TIMEOUT) {
        console.logAPI(this.loadProgram.name, ...arguments);
        this.fireEvent(statusMessageEventType, { type: 'log', message: 'Loading program ...' });
        const binFile = await GcFiles.readBinaryFile(programPath);
        return await GcPromise.timeout(core.loadProgram(binFile, false, verifyProgram), timeout, TIMEOUT_MESSAGE('program'));
    }
    async loadSymbols(core, symbolsPath, timeout = DEFAULT_TIMEOUT) {
        console.logAPI(this.loadSymbols.name, ...arguments);
        this.fireEvent(statusMessageEventType, { type: 'log', message: 'Loading symbols ...' });
        const symbolsFile = await GcFiles.readBinaryFile(symbolsPath);
        await GcPromise.timeout(core.loadProgram(symbolsFile, true, false), timeout, TIMEOUT_MESSAGE('symbols'));
    }
    async loadBin(core, binPath, location, verifyProgramPath, timeout = DEFAULT_TIMEOUT) {
        console.logAPI(this.loadBin.name, ...arguments);
        this.fireEvent(statusMessageEventType, { type: 'log', message: 'Loading binary ...' });
        if (verifyProgramPath) {
            try {
                const verifyProgramFile = await GcFiles.readBinaryFile(verifyProgramPath);
                await core.verifyProgram(verifyProgramFile);
                this.fireEvent(statusMessageEventType, { type: 'log', message: 'Verify program passed, skip loading program.' });
                return;
            }
            catch (e) {
                const message = 'Verify program failed, continue loading program.';
                console.info(message);
                this.fireEvent(statusMessageEventType, { type: 'log', message: message });
            }
        }
        const binFile = await GcFiles.readBinaryFile(binPath);
        await GcPromise.timeout(core.loadBin(binFile, location, true), timeout, TIMEOUT_MESSAGE('bin'));
    }
    async flash(params, monitor = DefaultProgressMonitor, timeout = DEFAULT_TIMEOUT) {
        console.logAPI(this.flash.name, ...arguments);
        if (!params.programOrBinPath) {
            throw Error('Invalid parameters: Missing a programOrBinPath property.');
        }
        let doDeconfig = false;
        try {
            updateFlashProgress(monitor, 'Preparing device configuration file ...', 0);
            let ccxml = undefined;
            if (params.ccxmlPath) {
                ccxml = await GcFiles.readTextFile(params.ccxmlPath);
            }
            else if (params.deviceName && params.connectionName) {
                ccxml = await this.targetConfigService.getConfig(params.connectionName, params.deviceName);
            }
            else {
                throw Error(`Missing a "${params.deviceName ? 'connectionId' : params.connectionName ? 'deviceName' : 'ccxmlPath'}" property.`);
            }
            const targetSupportProgressListener = (eventData) => {
                this.fireEvent(statusMessageEventType, { type: 'info', message: `${eventData.name} ${eventData.subActivity}` });
            };
            this.dsService.addEventListener(targetSupportProgressEventType, targetSupportProgressListener);
            try {
                updateFlashProgress(monitor, 'Configuring device ...', 15);
                await this.dsService.configure(ccxml);
                doDeconfig = true;
            }
            finally {
                this.dsService.removeEventListener(targetSupportProgressEventType, targetSupportProgressListener);
            }
            updateFlashProgress(monitor, 'Listing device cores...', 35);
            let cores = await this.dsService.listCores(debugCoreType);
            if (cores.length === 0) {
                throw Error(`No debuggable cores found for ${params.deviceName} device".`);
            }
            if (params.coreName) {
                cores = cores.filter(core => core.name.endsWith(params.coreName));
            }
            const core = cores[0];
            if (!core) {
                throw Error(`No debuggable core="${params.coreName}" found for ${params.deviceName} device.`);
            }
            updateFlashProgress(monitor, `Connecting to core="${core.name}" ...`, 50);
            await core.connect();
            try {
                updateFlashProgress(monitor, 'Flashing device ...', 75);
                if (params.programOrBinPath.endsWith('.bin')) {
                    await this.loadBin(core, params.programOrBinPath, new Location(params.loadAddress ?? 0), params.verifyProgramPath, params.timeout);
                }
                else if (params.symbolsOnly) {
                    await this.loadSymbols(core, params.programOrBinPath, params.timeout);
                }
                else {
                    await this.loadProgram(core, params.programOrBinPath, true, params.timeout);
                }
                updateFlashProgress(monitor, 'Flash completed!', 100);
                // to be safe make sure we free run before deConfigure.
                // ...[ PG 3/17/2021
                // The MSP430F5529 launchpad doesn't always run properly if runfree = true.  V2 code base didn't use
                // runfree, except for MSP430F2617, for all devices.  CCs Cloud always uses runFree and has the same issue
                // as I had before this change.
                // ...] params.connectionName && params.connectionName.indexOf('MSP430') >= 0 ? false : true
                await core.run(params.connectionName && params.connectionName.indexOf('MSP430 USB') >= 0 ? false : true);
            }
            finally {
                await core.disconnect();
            }
        }
        finally {
            if (doDeconfig) {
                await this.dsService.deConfigure();
            }
        }
    }
}
ServicesRegistry.register(programLoaderServiceType, ProgramLoaderService);

export { programLoaderServiceType };
//# sourceMappingURL=ProgramLoaderService.js.map
