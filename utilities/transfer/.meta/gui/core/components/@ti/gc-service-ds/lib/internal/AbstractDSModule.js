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
/* eslint-disable prefer-rest-params */
import { Events, EventType } from '../../../gc-core-assets/lib/Events';
import { GcConsole } from '../../../gc-core-assets/lib/GcConsole';
import { ServicesRegistry } from '../../../gc-core-services/lib/ServicesRegistry';
import { backplaneServiceType } from '../../../gc-service-backplane/lib/BackplaneService';
/**
 * @hidden
 */
export const MODULE_NAME = 'gc-service-ds';
export class DSEventType extends EventType {
    constructor(eventName, subObjectName) {
        super(eventName);
        this.subObjectName = subObjectName;
        this.dsEventType = true;
    }
}
export class DSEventBrokerType extends EventType {
    constructor() {
        super(...arguments);
        this.dsEventBrokerEventType = true;
    }
}
/**
 * @hidden
 */
export class AbstractDSModule extends Events {
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
//# sourceMappingURL=AbstractDSModule.js.map