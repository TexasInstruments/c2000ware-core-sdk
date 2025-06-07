import { AbstractDataCodec, bufferOrStringDataType, stringDataType } from '../../gc-target-configuration/lib/TargetConfiguration';

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
class Base64PacketCodec extends AbstractDataCodec {
    constructor(params) {
        super(params.id || 'base64', bufferOrStringDataType, stringDataType, stringDataType, bufferOrStringDataType);
        this.params = params;
    }
    encode(data) {
        const message = data instanceof Array ? String.fromCharCode.apply(null, data) : data;
        this.targetEncoder.encode(window.btoa(message));
    }
    decode(rawdata) {
        try {
            const message = typeof rawdata === 'string' ? rawdata : String.fromCharCode.apply(null, rawdata);
            return this.targetDecoder.decode(window.atob(message));
        }
        catch (ex) {
            return new Error('Error converting base64 string to binary');
        }
    }
}

export { Base64PacketCodec };
//# sourceMappingURL=Base64PacketCodec.js.map
