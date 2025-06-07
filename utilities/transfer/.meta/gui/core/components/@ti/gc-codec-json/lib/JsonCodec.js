import { AbstractDataCodec, bufferOrStringDataType, stringDataType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { streamingCodecDataType } from '../../gc-model-streaming/lib/StreamingDataModel';

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
class JsonCodec extends AbstractDataCodec {
    constructor(params) {
        super(params.id || 'json', bufferOrStringDataType, stringDataType, streamingCodecDataType, streamingCodecDataType);
        this.params = params;
        this.numPacketsReceived = 0;
    }
    encode(data) {
        this.targetEncoder.encode(JSON.stringify(data));
    }
    decode(rawData) {
        let result = false;
        try {
            let cleanPacket = '';
            const message = typeof rawData === 'string' ? rawData : String.fromCharCode(...rawData);
            // remove any leading or trailing garbage characters
            const start = message.indexOf('{');
            const end = message.lastIndexOf('}');
            if (end <= start) {
                if (this.numPacketsReceived > 0) { // ignore incomplete or partial json data before connection
                    result = Error(`Received bad JSON data string: ${message}`);
                }
            }
            else {
                try {
                    // remove any leading or trailing garbage characters
                    cleanPacket = message.substring(start, end + 1);
                    const data = JSON.parse(cleanPacket);
                    try {
                        result = this.targetDecoder.decode(data);
                    }
                    catch (e) {
                        result = e;
                    }
                }
                catch (e) {
                    if (this.numPacketsReceived > 0) {
                        result = Error(`Received bad JSON data string: ${cleanPacket}.`);
                    }
                }
                this.numPacketsReceived++;
            }
        }
        catch (ex) {
            result = new Error('Error converting buffer to text string');
        }
        return result;
    }
    async onConnect(transport) {
        this.numPacketsReceived = 0;
    }
}

export { JsonCodec };
//# sourceMappingURL=JsonCodec.js.map
