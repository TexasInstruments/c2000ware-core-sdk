import { Events } from '../../gc-core-assets/lib/Events';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';

/**
 *  Copyright (c) 2023, Texas Instruments Incorporated
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
const MODULE_NAME = 'gc-service-websocket';
const logger = new GcConsole(MODULE_NAME);
/**
 * Web Socket service type.
 */
const webSocketServiceType = new ServiceType(MODULE_NAME);
/**
 * Web Socket service implementation
 */
class WsService extends Events {
    createWebSocket(url) {
        const useCloudAgent = GcUtils.isCloud && document.location.protocol.startsWith('https') && document.location.hostname.endsWith('.ti.com');
        if (useCloudAgent) {
            return new WebSocketProxy(url);
        }
        return new WebSocket(url);
    }
}
class WebSocketProxy {
    constructor(url) {
        this.id = -1;
        this.onMessageHandler = (event) => {
            if (this.onmessage && this.id === event.id) {
                try {
                    this.onmessage.call(null, { data: event.data });
                }
                catch (e) {
                    logger.error(`Exception from onmessage() callback: ${e.message || e.toString()}`);
                }
            }
        };
        this.onErrorHandler = (event) => {
            if (this.onerror && this.id === event.id) {
                try {
                    this.onerror.call(null, { message: event.message });
                }
                catch (e) {
                    logger.error(`Exception from onmessage() callback: ${e.message || e.toString()}`);
                }
            }
        };
        this.onClosedHandler = async (event) => {
            if (this.id === event.id) {
                if (this.onclose) {
                    try {
                        this.onclose.call(null, {});
                    }
                    catch (e) {
                        logger.error(`Exception from onmessage() callback: ${e.message || e.toString()}`);
                    }
                }
                this.removeEventListeners(WebSocketProxy.WebSocketModule);
            }
        };
        this.ready = this.open(url);
    }
    async open(url) {
        const service = ServicesRegistry.getService(backplaneServiceType);
        WebSocketProxy.WebSocketModule = WebSocketProxy.WebSocketModule ?? await service.getSubModule('WsPipe', 'http_requestor', 'ccs_base/http_requestor/ws_pipe.js');
        const { id } = await WebSocketProxy.WebSocketModule.openPipe(url);
        this.id = id;
        const eventTarget = WebSocketProxy.WebSocketModule;
        eventTarget.addListener('closed', this.onClosedHandler);
        eventTarget.addListener('message', this.onMessageHandler);
        eventTarget.addListener('error', this.onErrorHandler);
    }
    async close() {
        if (this.id !== -1) {
            await this.ready; // make sure initialization has completed
            await WebSocketProxy.WebSocketModule.closePipe(this.id);
            this.removeEventListeners(WebSocketProxy.WebSocketModule);
        }
    }
    removeEventListeners(eventTarget) {
        eventTarget.removeListener('message', this.onMessageHandler);
        eventTarget.removeListener('error', this.onErrorHandler);
        eventTarget.removeListener('closed', this.onClosedHandler);
        this.id = -1;
    }
}
ServicesRegistry.register(webSocketServiceType, WsService);

export { webSocketServiceType };
//# sourceMappingURL=WsService.js.map
