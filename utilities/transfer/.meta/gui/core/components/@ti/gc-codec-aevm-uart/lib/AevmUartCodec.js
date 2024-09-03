import { AbstractCodec, NoopDecoderType, bufferDataType, nullDataCodec } from '../../gc-target-configuration/lib/TargetConfiguration';
import { IAevmEncoderType, nullAevmEncoder } from '../../gc-codec-aevm/lib/AevmCodec';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';

/**
 *  Copyright (c) 2020, 2021 Texas Instruments Incorporated
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
const parityMap = { 'none': 0, 'even': 1, 'odd': 2, 'zero': 3, 'one': 4 };
const UART_TYPE = 0x06;
class AevmUartCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'uart', NoopDecoderType, IAevmEncoderType, bufferDataType, bufferDataType);
        this.params = params;
        this.targetEncoder = nullAevmEncoder;
        this.targetDecoder = nullDataCodec;
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        return this.configureFirmware();
    }
    async configureFirmware() {
        const params = this.params;
        const unit = params.unit ?? 6;
        const baudRate = params.baudRate ?? 9600;
        const parity = GcUtils.parseStringProperty('parity', params.parity ?? 'none', parityMap);
        const characterLength = GcUtils.parseNumberProperty('characterLength', params.characterLength ?? 8, 5, 8) - 5;
        const stopBits = GcUtils.parseNumberProperty('stopBits', params.stopBits ?? 1, 1, 2) === 1 ? 0 : 1;
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(UART_TYPE, unit, 0 /* Enable */, [unit, 1], []));
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(UART_TYPE, unit, 1 /* Config */, [unit, baudRate, parity, characterLength, stopBits], []));
    }
    encode(data) {
        const unit = this.params.unit ?? 6;
        return this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(UART_TYPE, unit, 2 /* Write */, [unit, data.length], data));
    }
}

export { AevmUartCodec };
//# sourceMappingURL=AevmUartCodec.js.map
