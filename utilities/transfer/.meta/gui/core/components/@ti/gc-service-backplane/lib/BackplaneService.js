import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { EventType, Events } from '../../gc-core-assets/lib/Events';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import './internal/q.js';

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
const MODULE_NAME = 'gc-service-backplane';
const console = new GcConsole(MODULE_NAME);
/**
 * Backplane service type.
 */
const backplaneServiceType = new ServiceType(MODULE_NAME);
const errorEventType = new EventType('errorEvent');
class BackplaneService extends Events {
    async init() {
        if (!this.initPromise) {
            console.logAPI(this.init.name, ...arguments);
            this.initPromise = new Promise(async (resolve, reject) => {
                let agent, TICloudAgent;
                try {
                    /* NodeJs environment */
                    if (GcUtils.isNodeJS && !GcUtils.isCCS) {
                        /*
                        * Gets runtimeRoot in the following cases
                        *    Running from a standalone package
                        *    Running from source
                        */
                        const runtimeRoot = GcUtils.runtimeRoot;
                        require(['..', '..', 'gc-core-assets', 'lib', 'NodeJSEnv'].join('/'));
                        require(`${runtimeRoot}/ticloudagent/server/public/agent`);
                        const agentHost = require(`${runtimeRoot}/TICloudAgentHostApp/src/host_agent`);
                        const info = await agentHost.start();
                        // @ts-ignore
                        agent = await global.TICloudAgent.createClientModule(info.port);
                        // @ts-ignore
                        TICloudAgent = global.TICloudAgent;
                        /* Browser environment */
                    }
                    else {
                        TICloudAgent = GcUtils.rootWin?.TICloudAgent || window.TICloudAgent;
                        if (!TICloudAgent) {
                            /* externalize the path to workaround rollup */
                            const agentPath = '/ticloudagent/agent.js';
                            try {
                                // @ts-ignore
                                await import(agentPath);
                            }
                            catch (e) {
                                // ignore errors, maybe agent.js was imported in the top level .html already to avoid webpack and rollup tyring to resolve dynamic imports.
                            }
                            TICloudAgent = GcUtils.rootWin?.TICloudAgent || window.TICloudAgent;
                            if (!TICloudAgent) {
                                throw new Error('Unable to import external dependency /ticloudagent/agent.js');
                            }
                        }
                        agent = await TICloudAgent.Init();
                    }
                    resolve({ agent: agent, TICloudAgent: TICloudAgent });
                }
                catch (e) {
                    const errors = [];
                    if (Array.isArray(e)) {
                        e.forEach(error => errors.push(error));
                    }
                    else {
                        errors.push(e);
                    }
                    this.fireEvent(errorEventType, { errors: errors });
                    reject(e);
                }
            });
        }
        return this.initPromise;
    }
    async getSubModule(name, category, path) {
        console.logAPI(this.getSubModule.name, ...arguments);
        const { agent } = await this.init();
        if (path) {
            if (category && GcUtils.isCloud) {
                const targetSupport = await agent.getSubModule('TargetSupport');
                await targetSupport.addByCategory([category]);
            }
            await agent.registerModuleByPath(path);
        }
        return agent.getSubModule(name);
    }
    async getUtil() {
        console.logAPI(this.getUtil.name, ...arguments);
        const { TICloudAgent } = await this.init();
        return Promise.resolve(TICloudAgent.Util);
    }
}
ServicesRegistry.register(backplaneServiceType, BackplaneService);

export { backplaneServiceType, errorEventType };
//# sourceMappingURL=BackplaneService.js.map
