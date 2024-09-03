import { connectionManager } from '../../gc-target-connection-manager/lib/ConnectionManager';
import { NoopDataEncoderType, NoopDataDecoderType, EncoderType, PrimitiveDataType, AbstractTransport, nullDataCodec, codecRegistry } from '../../gc-target-configuration/lib/TargetConfiguration';
import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { ServicesRegistry } from '../../gc-core-services/lib/ServicesRegistry';
import { httpServiceType } from '../../gc-service-http/lib/HttpService';
import { webSocketServiceType } from '../../gc-service-ws/lib/WsService';

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
/**
  * Noop implementation for transport encoder.
  */
const nullNetworkTransportEncoder = new (class {
    constructor() {
        this.encoderInputType = NoopDataEncoderType;
        this.encoderOutputType = NoopDataDecoderType;
        this.id = '';
        this.ipAddress = '';
    }
    encode(data) {
        throw new Error('Method not implemented.');
    }
    httpRequest(op, path, options) {
        throw new Error('Method not implemented.');
    }
    createWebSocket(port, path) {
        throw new Error('Method not implemented.');
    }
    startStreaming(op, path, options) {
        throw new Error('Method not implemented.');
    }
    addChildDecoder() {
    }
    setParentEncoder() {
    }
    dispose() {
    }
});
/**
  * Network transport type.
  */
const networkTransportType = new EncoderType('http');
/**
  * Multi-part data streaming codec type.
  */
const multiPartStreamingType = new PrimitiveDataType('multi-part');
/**
  * Network transport for sending http requests, including streaming multi-part data, and opening web sockets.
  */
class NetworkTransport extends AbstractTransport {
    constructor(params) {
        super();
        this.params = params;
        this.encoderInputType = networkTransportType;
        this.encoderOutputType = multiPartStreamingType;
        this.targetDecoder = nullDataCodec;
        this.console = new GcConsole('gc-transport-network', params.id);
        if (this.id) {
            connectionManager.registerTransport(this);
            codecRegistry.register(this);
        }
    }
    get id() {
        return this.params.id || 'net';
    }
    httpRequest(op, path, options) {
        if (this.getUrl === undefined) {
            throw new Error(`Cannot do http request when target is ${this.state}`);
        }
        const http = ServicesRegistry.getService(httpServiceType);
        return http.request(op, this.getUrl('http', options?.port, path), options);
    }
    async startStreaming(op, path, options) {
        const contentTypeRegex = /^multipart\/x-mixed-replace;boundary=(.*)$/;
        // The boundary between parts
        let boundary;
        let buffer = '';
        const { headers, stream } = await this.httpRequest('GET', path, { ...options, responseType: 'stream' });
        if (!stream) {
            throw new Error('Streaming is not supported.');
        }
        if (typeof headers['content-type'] === 'string') {
            const m = headers['content-type'].match(contentTypeRegex);
            if (m) {
                // no need to prefix with '--', this server includes it
                boundary = `${m[1]}\r\n`;
            }
            else {
                this.console.error('unexpected content-type for stream request response');
                await stream.close();
                return;
            }
        }
        else {
            this.console.error('no content-type on stream request response');
            await stream.close();
            return;
        }
        stream.onData = (data) => {
            // We know the current buffer doesn't contain a boundary
            const searchStart = Math.max(buffer.length - boundary.length, 0);
            buffer += atob(data);
            // Do we now have a complete part?
            let partStart = 0;
            let partEnd = buffer.indexOf(boundary, searchStart);
            if (partEnd >= 0) {
                // We might have received multiple parts at once
                const lastBoundary = buffer.lastIndexOf(boundary);
                if (lastBoundary > partEnd) {
                    partEnd = lastBoundary;
                    partStart = buffer.lastIndexOf(boundary, lastBoundary - 1) + boundary.length;
                }
            }
            if (partEnd === partStart) {
                // empty part, this should only be the very first part
                // if not, we need extra logic to avoid potentially ignoring non-empty frames
                buffer = buffer.substring(partEnd + boundary.length);
            }
            else if (partEnd > 0) {
                if (partStart > 0) {
                    buffer = buffer.substring(partStart);
                    partEnd -= partStart;
                }
                const headerEnd = buffer.indexOf('\r\n\r\n'); // marks the end of the header of the part
                const frameHeader = this.readPartHeader(buffer.substring(0, headerEnd));
                const frameData = buffer.substring(headerEnd + 4, partEnd);
                const frameType = frameHeader['Content-Type'];
                if (frameType) {
                    this.targetDecoder.decode({ type: frameType, data: frameData });
                }
                else {
                    this.console.logger.error('Missing \'Content-Type\' on part header');
                }
                buffer = buffer.substring(partEnd + boundary.length);
            }
        };
    }
    createWebSocket(port, path) {
        if (this.getUrl === undefined) {
            throw new Error(`Cannot create websocket when target is ${this.state}`);
        }
        const ws = ServicesRegistry.getService(webSocketServiceType);
        return ws.createWebSocket(this.getUrl('ws', port, path));
    }
    addChildDecoder(decoder) {
        this.targetDecoder = decoder;
    }
    dispose() {
        if (this.id) {
            connectionManager.unregisterTransport(this);
            codecRegistry.unregister(this);
        }
    }
    async onConnect(transport) {
        const { ipAddress, defaultPort, subdirectory } = this.params;
        if (!ipAddress) {
            throw new Error('Missing the IP address.');
        }
        this.setConnectionDescription(ipAddress);
        this.getUrl = (protocol, port, path) => {
            return `${protocol}://${ipAddress}:${port ?? defaultPort ?? 80}${subdirectory ? '/' + subdirectory : ''}${path ? '/' + path : ''}`;
        };
        this._ipAddress = ipAddress;
    }
    get ipAddress() {
        return this._ipAddress ?? '';
    }
    async onDisconnect(transport) {
        this.getUrl = undefined;
    }
    encode(data) {
        throw new Error('Not implemented yet.');
    }
    readPartHeader(headerStr) {
        const header = {};
        for (const line of headerStr.split('\r\n')) {
            const [key, value] = line.split(': ', 2);
            header[key] = value;
        }
        return header;
    }
}

export { NetworkTransport, multiPartStreamingType, networkTransportType, nullNetworkTransportEncoder };
//# sourceMappingURL=NetworkTransport.js.map
