import { connectionManager } from '../../gc-target-connection-manager/lib/ConnectionManager';
import { ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { Events } from '../../gc-core-assets/lib/Events';
import { programLoaderServiceType, statusMessageEventType } from '../../gc-service-program-loader/lib/ProgramLoaderService';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { LOAD_PROGRAM_FILENAME, DSProgressUpdateEventType } from '../../gc-service-ds/lib/DSService';

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
/**
 * A target program loader for loading or flashing target programs onto specfic devices and cores.  Target program loaders are
 * registered with the connection manager, and are loaded during connection to the target if the autoProgram parameter is enabled.
 * If not enabled, programs must be loaded manually, either programmatically or by user actions in the UI.
 */
class TargetProgramLoader extends Events {
    /**
     * Constructor for a target program loader.
     *
     * @param params parameters for configuring the target program loader.
     */
    constructor(params) {
        super();
        this.params = params;
        this.alreadyLoaded = false;
        connectionManager.registerProgramLoader(this);
    }
    dispose() {
        connectionManager.unregisterProgramLoader(this);
    }
    /**
     * Retrieve the optional deviceId that specifies which specific device, by unique identifier this program loader is targeting in the target configuration.
     */
    get deviceId() {
        return this.params.deviceId;
    }
    /**
     * Test if this program loader is optional.  If it is, the target connection will not necessarily fail if the program fails to load.
     */
    get optional() {
        return this.params.optional || false;
    }
    toString() {
        const coreName = this.params.coreName ? ` core="${this.params.coreName}"` : '';
        return `${this.deviceId || this.params.deviceName} device${coreName}`;
    }
    /**
     * Method to load the program.
     *
     * @param logger a callback for logging error, warning, progress, and debug messages while loading a program.
     * @param progressCallback a callback for updating progress, as a percentage, while loading a program.
     * @param force option to force a program load even if the autoProgram parameter is not set, or the program has already been loaded once.
     */
    async loadProgram(logger, progressCallback, force = false) {
        const description = `Loading program for ${this.toString()}`;
        if (force || (this.params.autoProgram && !this.alreadyLoaded && !GcUtils.isCCS && !GcUtils.isInDesigner)) {
            const loaderService = ServicesRegistry.getService(programLoaderServiceType);
            const statusMessageHandler = (details) => {
                switch (details.type) {
                    case 'info':
                        logger.addProgressMessage(details.message);
                        break;
                    case 'fatal':
                    case 'error':
                        logger.addErrorMessage(details.message, undefined, details.type === 'fatal');
                        break;
                    case 'warning':
                        logger.addWarningMessage(details.message);
                        break;
                }
            };
            loaderService.addEventListener(statusMessageEventType, statusMessageHandler);
            const progressHandler = (details) => {
                if (details.name.endsWith(LOAD_PROGRAM_FILENAME)) {
                    details = { ...details, name: `${description} ...` };
                }
                logger.addProgressMessage(details.name, undefined, details.percent ?? 0);
            };
            loaderService.addEventListener(DSProgressUpdateEventType, progressHandler);
            try {
                logger.addProgressMessage(`${description} ...`);
                await loaderService.flash(this.params, {
                    onProgress: (message, progress) => {
                        logger.addDebugMessage(message);
                        progressCallback?.(progress);
                    },
                    get cancelled() {
                        try {
                            logger.assertStillConnecting();
                            return false;
                        }
                        catch (e) {
                            return true;
                        }
                    }
                });
                if (!this.params.sram) {
                    this.alreadyLoaded = true;
                }
                logger.addProgressMessage(`${description} succeeded.`);
            }
            catch (e) {
                throw Error(`${description} failed: ${e.message || e.toString()}`);
            }
            finally {
                loaderService.removeEventListener(statusMessageEventType, statusMessageHandler);
                loaderService.removeEventListener(DSProgressUpdateEventType, progressHandler);
            }
        }
        else if (this.params.autoProgram) {
            logger.addDebugMessage(`${description} was skipped because it should be already loaded.`);
        }
    }
}

export { TargetProgramLoader };
//# sourceMappingURL=TargetProgramLoader.js.map
