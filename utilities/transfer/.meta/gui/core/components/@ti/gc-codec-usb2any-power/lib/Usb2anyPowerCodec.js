import { IUsb2anyEncoderType, nullUsb2anyEncoder, Command, PACKET_PAYLOAD } from '../../gc-codec-usb2any/lib/Usb2anyCodec';
import { AbstractDecoder, NoopDecoderType } from '../../gc-target-configuration/lib/TargetConfiguration';
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
class Usb2anyPowerCodec extends AbstractDecoder {
    constructor(params) {
        super(params.id || 'power', NoopDecoderType, IUsb2anyEncoderType);
        this.params = params;
        this.targetEncoder = nullUsb2anyEncoder;
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        return this.configureFirmware();
    }
    async configureFirmware() {
        const settings = this.params;
        const v33power = settings.v33 ? 1 : 0;
        const v50power = settings.v50 ? 1 : 0;
        const vadjpower = settings.vAdj ? 1 : 0;
        const cfgFunction = async () => {
            await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(Command.Cmd_Power_Enable, [v33power, v50power, vadjpower, 0]));
            const status = await this.readStatus();
            if ((status & 7) !== 0) {
                const voltage = (status & 1) ? '3.3V' : (status & 2) ? '5.0V' : 'Vadj';
                throw Error(`USB2ANY power fault detected for ${voltage}.`);
            }
        };
        return GcPromise.timeout(cfgFunction(), this.targetEncoder.connectTimeout, 'USB2ANY Power configure timeout');
    }
    async readStatus() {
        return this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(Command.Cmd_Power_ReadStatus, [0, 0, 0x5a, 0x5a])).then((packet) => {
            return packet[PACKET_PAYLOAD] | (packet[PACKET_PAYLOAD + 1] << 1) | (packet[PACKET_PAYLOAD + 2] << 2) | (packet[PACKET_PAYLOAD + 3] << 3);
        });
    }
}

export { Usb2anyPowerCodec };
//# sourceMappingURL=Usb2anyPowerCodec.js.map
