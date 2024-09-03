import { Events } from '../../gc-core-assets/lib/Events';
import { backplaneServiceType } from '../../gc-service-backplane/lib/BackplaneService';
import { ServiceType, ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';

/**
 *  Copyright (c) 2023 Texas Instruments Incorporated
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
const MODULE_NAME = 'gc-service-http';
/**
 * Service type for HttpService.
 */
const httpServiceType = new ServiceType(MODULE_NAME);
class HttpService extends Events {
    async getRequestor() {
        if (this.requestorModule === undefined) {
            const service = ServicesRegistry.getService(backplaneServiceType);
            this.requestorModule = await service.getSubModule('HttpRequestor', 'http_requestor', 'ccs_base/http_requestor/http_requestor.js');
        }
        return this.requestorModule;
    }
    async request(op, url, options) {
        if (options?.responseType === 'stream' && op !== 'GET') {
            throw new Error('Only GET requests support responseType="stream" at present.');
        }
        try {
            const requestor = await this.getRequestor();
            if (options?.params) {
                url = `${url}?${JSON.stringify(options.params)}`;
            }
            const requestOptions = {
                type: options?.formData ? 'multipart/form-data' : 'json',
                timeout: options?.timeout
            };
            HttpService.logger.log(JSON.stringify(requestOptions));
            const payload = typeof options?.payload === 'object' ? JSON.stringify(options.payload) : options?.payload;
            if (options?.responseType === 'stream') {
                return this.doCloudAgentStreamRequest(op, url, options?.formData ? options.formData : payload, requestOptions);
            }
            const { data, headers } = await requestor.request(op, url, options?.formData ? options.formData : payload, requestOptions);
            try {
                // TODO: support responseType in options
                return { data: JSON.parse(atob(data)), headers };
            }
            catch {
                return { data, headers }; // ignore json parse errors, not all responses are JSON strings.
            }
        }
        catch (e) {
            HttpService.logger.log(e);
            throw e;
        }
    }
    async doCloudAgentStreamRequest(op, url, payload, options) {
        const requestor = await this.getRequestor();
        const { id, headers } = await requestor.streamRequest(op, url, payload, options);
        const requestId = id;
        const stream = {
            close: () => {
                return requestor.closeStreamRequest(requestId);
            }
        };
        const onData = ({ id, data }) => {
            if (id === requestId) {
                stream.onData?.call(null, data);
            }
        };
        const onError = ({ id, message }) => {
            if (id === requestId) {
                HttpService.logger.error(`streamRequest received error: ${message}`);
                stream.onError?.call(null, message);
            }
        };
        const onEnd = ({ id }) => {
            if (id === requestId) {
                removeListeners();
                stream.onEnd?.call(null);
            }
        };
        const htmlRequester = requestor;
        const removeListeners = () => {
            htmlRequester.removeListener('data', onData);
            htmlRequester.removeListener('end', onEnd);
            htmlRequester.removeListener('error', onError);
        };
        htmlRequester.addListener('data', onData);
        htmlRequester.addListener('end', onEnd);
        htmlRequester.addListener('error', onError);
        return {
            data: [],
            headers,
            stream
        };
    }
}
HttpService.logger = new GcConsole(MODULE_NAME);
ServicesRegistry.register(httpServiceType, HttpService);

export { httpServiceType };
//# sourceMappingURL=HttpService.js.map
