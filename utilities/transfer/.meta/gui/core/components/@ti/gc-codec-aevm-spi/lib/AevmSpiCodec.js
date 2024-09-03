import { AbstractCodec, NoopDecoderType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { IAevmEncoderType, nullAevmEncoder, getPayload } from '../../gc-codec-aevm/lib/AevmCodec';
import { RegisterModelDecoderType, RegisterModelEncoderType, nullRegisterModelDecoder } from '../../gc-model-register/lib/RegisterModel';
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
const modeMap = {
    'moto_mode_0': 0x0,
    'moto_mode_1': 0x2,
    'moto_mode_2': 0x1,
    'moto_mode_3': 0x3,
    'ti': 0x10,
    'bi_read': 0x140,
    'bi_write': 0x40,
};
const csActiveMap = { 'high': 1, 'low': 0 };
const parityMap = { 'even': 0, 'odd': 1 };
const SPI_TYPE = 0x05;
class AevmSpiCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'spi', NoopDecoderType, IAevmEncoderType, RegisterModelDecoderType, RegisterModelEncoderType);
        this.params = params;
        this.targetEncoder = nullAevmEncoder;
        this.encoderInputType = RegisterModelEncoderType;
        this.encoderOutputType = RegisterModelDecoderType;
        this.targetDecoder = nullRegisterModelDecoder;
        this.readCmd = 0;
        this.writeCmd = 0;
        this.addressBitsOffset = 0;
        this.dataBitsOffset = 0;
        this.dataBitsMask = 0;
        this.parityBitsOffset = 0;
        this.byteSize = 0;
        this.chipSelectPinMask = 0;
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        const params = this.params;
        this.readCmd = params.readCmd ?? 0;
        this.writeCmd = params.writeCmd ?? 0;
        this.addressBitsOffset = params.addressBitsOffset ?? 0;
        const addressBits = params.addressBits ?? 0;
        this.dataBitsOffset = params.dataBitsOffset ?? 0;
        const dataBits = params.dataBits ?? 0;
        this.dataBitsMask = (1 << dataBits) - 1;
        if (params.parity !== undefined) {
            this.parity = GcUtils.parseStringProperty('parity', params.parity, parityMap);
        }
        this.parityBitsOffset = params.parityBitsOffset ?? 0;
        const bitSize = Math.max(this.addressBitsOffset + addressBits, this.dataBitsOffset + dataBits, this.parityBitsOffset);
        this.byteSize = (bitSize + 7) >> 3;
        while ((1 << (this.byteSize * 8)) < this.readCmd) {
            this.byteSize += 1;
        }
        while ((1 << (this.byteSize * 8)) < this.writeCmd) {
            this.byteSize += 1;
        }
        this.chipSelectPinMask = (params.chipSelectPin !== undefined) ? 1 << params.chipSelectPin : 0;
        return this.configureFirmware();
    }
    async configureFirmware() {
        const params = this.params;
        const unit = params.unit ?? 2;
        const mode = GcUtils.parseStringProperty('mode', '' + params.mode ?? 'moto_mode_0', modeMap);
        const dataWidth = GcUtils.parseNumberProperty('dataWidth', params.dataWidth ?? 8, 4, 16);
        const csMode = GcUtils.parseStringProperty('chipSelectActive', '' + params.chipSelectActive ?? 'high', csActiveMap);
        const csChange = params.chipSelectChange ? 1 : 0;
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(SPI_TYPE, unit, 0 /* Enable */, [unit, 1], []));
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(SPI_TYPE, unit, 1 /* Config */, [unit, params.bitRate ?? 1, mode, dataWidth, csMode, csChange], []));
    }
    async readValue(info, coreIndex) {
        const regAddr = info.addr;
        let cmd = this.readCmd | (regAddr << this.addressBitsOffset);
        if (this.parity !== undefined) {
            cmd |= ((this.parity ^ GcUtils.computeParity(cmd, this.byteSize * 8)) << this.parityBitsOffset);
        }
        const payload = [];
        if (this.params.dataEndian === 'little') {
            GcUtils.setBytesLSB(payload, this.byteSize, cmd, payload.length);
        }
        else {
            GcUtils.setBytes(payload, this.byteSize, cmd, payload.length);
        }
        const unit = this.params.unit ?? 2;
        const result = await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(SPI_TYPE, unit, 2 /* WriteAndRead */, [unit, this.chipSelectPinMask, payload.length], payload));
        return (GcUtils.bytesToValue(getPayload(result), this.params.dataEndian ?? 'big') >>> this.dataBitsOffset) & this.dataBitsMask;
    }
    writeValue(info, value, coreIndex) {
        const regAddr = info.writeAddr ?? info.addr;
        let cmd = this.writeCmd | (regAddr << this.addressBitsOffset) | (value << this.dataBitsOffset);
        if (this.parity !== undefined) {
            cmd |= ((this.parity ^ GcUtils.computeParity(cmd, this.byteSize * 8)) << this.parityBitsOffset);
        }
        const payload = [];
        if (this.params.dataEndian === 'little') {
            GcUtils.setBytesLSB(payload, this.byteSize, cmd, payload.length);
        }
        else {
            GcUtils.setBytes(payload, this.byteSize, cmd, payload.length);
        }
        const unit = this.params.unit ?? 2;
        return this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(SPI_TYPE, unit, 2 /* WriteAndRead */, [unit, this.chipSelectPinMask, payload.length], payload));
    }
}

export { AevmSpiCodec };
//# sourceMappingURL=AevmSpiCodec.js.map
