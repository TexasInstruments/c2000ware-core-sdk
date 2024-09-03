import { IUsb2anyEncoderType, nullUsb2anyEncoder, Command } from '../../gc-codec-usb2any/lib/Usb2anyCodec';
import { AbstractCodec, NoopDecoderType, bufferDataType, nullDataCodec } from '../../gc-target-configuration/lib/TargetConfiguration';
import { receivePayloadEventType } from '../../gc-target-configuration/lib/ICodecAnalogControllerBaseParams';
import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';

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
const parityMap = { 'none': 0, 'even': 1, 'odd': 2 };
const bitDirectionMap = { 'lsb': 0, 'msb': 1 };
const baudRateMap = {
    '9600': 0,
    '19200': 1,
    '38400': 2,
    '57600': 3,
    '115200': 4,
    '230400': 5,
    '300': 6,
    '320': 7,
    '600': 8,
    '1200': 9,
    '2400': 10,
    '4800': 11
};
class Usb2anyUartCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'uart', NoopDecoderType, IUsb2anyEncoderType, bufferDataType, bufferDataType);
        this.params = params;
        this.targetEncoder = nullUsb2anyEncoder;
        this.targetDecoder = nullDataCodec;
        this.receivePacketEventListsener = (details) => {
            this.targetDecoder.decode(details.payload);
        };
    }
    /**
     * @hidden
     */
    async onDisconnect(transport) {
        this.targetEncoder.removeEventListener(receivePayloadEventType, this.receivePacketEventListsener);
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        this.targetEncoder.addEventListener(receivePayloadEventType, this.receivePacketEventListsener);
        return this.configureFirmware();
    }
    async configureFirmware() {
        const params = this.params;
        const baudRate = GcUtils.parseStringProperty('baudRate', '' + params.baudRate ?? '9600', baudRateMap);
        const parity = GcUtils.parseStringProperty('parity', params.parity ?? 'none', parityMap);
        const bitDirection = GcUtils.parseStringProperty('bitDirection', params.bitDirection ?? 'lsb', bitDirectionMap);
        const characterLength = 8 - GcUtils.parseNumberProperty('characterLength', params.characterLength ?? 8, 7, 8);
        const stopBits = GcUtils.parseNumberProperty('stopBits', params.stopBits ?? 1, 1, 2) === 1 ? 0 : 1;
        const promises = [];
        promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(Command.Cmd_UART_Control, [
            baudRate, parity, bitDirection, characterLength, stopBits
        ])));
        promises.push(this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(Command.Cmd_UART_SetMode, [0])));
        return GcPromise.timeout(Promise.all(promises), this.targetEncoder.connectTimeout, 'USB2ANY UART configure timeout');
    }
    encode(data) {
        return this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(Command.Cmd_UART_Write, data));
    }
}

export { Usb2anyUartCodec };
//# sourceMappingURL=Usb2anyUartCodec.js.map
