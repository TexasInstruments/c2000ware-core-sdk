/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
// eslint-disable-next-line @typescript-eslint/no-explicit-any
import os from 'os';
import path from 'path';
import { TextDecoder } from 'util';
import { Writable } from 'stream';
class WriteStream extends Writable {
    constructor() {
        super(...arguments);
        this.buffer = Buffer.alloc(0);
    }
    _write(chunk, encoding, done) {
        this.buffer = Buffer.concat([this.buffer, chunk]);
        done();
    }
    getData() {
        const ab = new ArrayBuffer(this.buffer.length);
        const view = new Uint8Array(ab);
        for (let i = 0; i < this.buffer.length; ++i) {
            view[i] = this.buffer[i];
        }
        return view;
    }
    getDataStr() {
        return new TextDecoder('utf-8').decode(this.getData());
    }
}
/**
 * Local CloudAgent target configuration.
 */
export class TargetConfig {
    constructor(runtimeRoot) {
        this.runtimeRoot = runtimeRoot;
    }
    async instance() {
        var _a;
        this._initPromise = (_a = this._initPromise) !== null && _a !== void 0 ? _a : new Promise((resolve, reject) => {
            /* eslint-disable @typescript-eslint/no-var-requires */
            (async () => {
                try {
                    const dInfraCommon = require(path.join(this.runtimeRoot, './ticloudagent/server/common/dinfra_common'));
                    const dInfra = require(path.join(this.runtimeRoot, './dinfra-library/desktop/dinfra'));
                    dInfraCommon.setDinfra(dInfra);
                    /* const dConfig = */ dInfra.configure({
                        origin: {
                            landscape: '127.0.0.1',
                            cluster: 'none',
                            instance: '127.0.0.1'
                        },
                        logging: {
                            'base-path': path.join(os.tmpdir(), 'ti_cloud_storage', 'gc_target_config'),
                            format: {
                                render: 'condensed'
                            }
                        },
                        databases: {
                            defaults: {
                                type: 'file',
                                path: path.join(this.runtimeRoot, './deskdb')
                            }
                        },
                        paths: {}
                    });
                    resolve({
                        generateConfigImpl: require(path.join(this.runtimeRoot, './ticloudagent/server/server_apis/generate_config')),
                        getConfigInfoImpl: require(path.join(this.runtimeRoot, './ticloudagent/server/server_apis/get_config_info')),
                        getFileImpl: require(path.join(this.runtimeRoot, './ticloudagent/server/server_apis/get_file'))
                    });
                }
                catch (e) {
                    reject(e);
                }
            })();
        });
        return this._initPromise;
    }
    createAgentPromise(callback) {
        return new Promise((resolve, reject) => {
            (async () => {
                const res = new WriteStream();
                res.on('finish', () => resolve(res.getDataStr()));
                res.on('error', reject);
                callback(res);
            })();
        });
    }
    async getConfig(OS, connectionID, deviceID, options) {
        return this.createAgentPromise(async (res) => {
            (await this.instance()).generateConfigImpl.default(connectionID, deviceID, OS, res);
        });
    }
    async getConfigInfo(OS) {
        return this.createAgentPromise(async (res) => {
            (await this.instance()).getConfigInfoImpl({ os: OS }, res);
        });
    }
    async getFile(OS, filepath, version = 'LATEST') {
        const xmlContents = await this.createAgentPromise(async (res) => {
            (await this.instance()).getFileImpl({ os: OS }, filepath, version, res);
        });
        return xmlContents;
    }
    parseConfig(ccxmlFileContents) {
        const xmldom = require(path.join(this.runtimeRoot, './ticloudagent/server/node_modules/xmldom'));
        let xmlParseError = '';
        function xmlParserErrorHandler(level, msg) {
            xmlParseError = xmlParseError !== null && xmlParseError !== void 0 ? xmlParseError : msg.toString();
        }
        const xmlDoc = new xmldom.DOMParser({
            locator: {},
            errorHandler: xmlParserErrorHandler,
        }).parseFromString(ccxmlFileContents);
        if (xmlParseError) {
            throw new Error(xmlParseError);
        }
        return xmlDoc;
    }
    serializeConfig(ccxmlDocument) {
        const xmldom = require(path.join(this.runtimeRoot, './ticloudagent/server/node_modules/xmldom'));
        // Sort attributes alphabetically to match legacy Java based Serializer.
        return new xmldom.XMLSerializer().serializeToString(ccxmlDocument, (a, b) => a.localeCompare(b));
    }
}
//# sourceMappingURL=TargetConfig.js.map