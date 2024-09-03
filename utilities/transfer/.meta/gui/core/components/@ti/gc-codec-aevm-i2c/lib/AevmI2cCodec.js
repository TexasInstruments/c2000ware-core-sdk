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
const speedMap = {
    '100': 0,
    '400': 1,
    '1000': 2,
    '3400': 3
};
const I2C_TYPE = 0x03;
const opcodeAddr = (opcode, addr, addrShift) => (opcode !== undefined ? +opcode : 0) | (addr !== undefined ? addr << (addrShift ?? 0) : 0);
class AevmI2cCodec extends AbstractCodec {
    constructor(params) {
        super(params.id || 'i2c', NoopDecoderType, IAevmEncoderType, RegisterModelDecoderType, RegisterModelEncoderType);
        this.params = params;
        this.targetEncoder = nullAevmEncoder;
        this.encoderInputType = RegisterModelEncoderType;
        this.encoderOutputType = RegisterModelDecoderType;
        this.targetDecoder = nullRegisterModelDecoder;
    }
    /**
     * @hidden
     */
    onConnect(transport) {
        return this.configureFirmware();
    }
    async configureFirmware() {
        const params = this.params;
        const unit = params.unit ?? 2;
        const speed = GcUtils.parseStringProperty('speed', '' + params.speed ?? '100', speedMap);
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(I2C_TYPE, unit, 0 /* Enable */, [unit, 1], []));
        await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(I2C_TYPE, unit, 1 /* Config */, [unit, speed, params.pullup ? 1 : 0], []));
    }
    getDeviceAddress(info) {
        let addr = 0;
        if (info.deviceAddrs && !isNaN(info.deviceAddrs)) {
            addr = +info.deviceAddrs;
        }
        else if (this.targetDecoder !== undefined) {
            addr = +(this.targetDecoder.getDeviceAddressForRegister(info) ?? this.params.deviceAddress ?? 0);
        }
        return addr;
    }
    async readValue(info, coreIndex) {
        const regAddr = info.addr;
        const format = this.params.readRegisterAddressOpcodeFormat ?? 'separated';
        const opcode = this.params.readOpcode;
        const payload = [];
        if (format === 'separated') {
            if (opcode !== undefined) {
                payload.push(+opcode);
            }
            if (regAddr !== undefined) {
                const addrBytes = ((this.params.registerAddressBits ?? 8) + 7) >> 3;
                if (this.params.registerAddressEndian === 'little') {
                    GcUtils.setBytesLSB(payload, addrBytes, regAddr, payload.length);
                }
                else {
                    GcUtils.setBytes(payload, addrBytes, regAddr, payload.length);
                }
            }
        }
        else {
            const opCodeOrRegAddr = opcodeAddr(opcode, regAddr, this.params.readRegisterAddressBitShift);
            payload.push(opCodeOrRegAddr);
        }
        const unit = this.params.unit ?? 2;
        const deviceAddrs = this.getDeviceAddress(info);
        const dataBytes = info.nBytes ?? ((info.size ?? 8) + 7) >> 3;
        const params = [unit, deviceAddrs, dataBytes];
        const result = await this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(I2C_TYPE, unit, 6 /* BlockWriteBlockRead */, params, payload));
        return GcUtils.bytesToValue(getPayload(result), this.params.dataEndian ?? 'big');
    }
    writeValue(info, value, coreIndex) {
        const regAddr = info.writeAddr ?? info.addr;
        const format = this.params.writeRegisterAddressOpcodeFormat ?? 'separated';
        const opcode = this.params.writeOpcode;
        let flags = ((this.params.registerAddressBits ?? 8) + 7) >> 4;
        let opCodeOrRegAddr = 0;
        const payload = [];
        if (format === 'separated') {
            if (opcode !== undefined) {
                opCodeOrRegAddr = +opcode;
                flags = 0;
                if (regAddr !== undefined) {
                    const addrBytes = ((this.params.registerAddressBits ?? 8) + 7) >> 3;
                    if (this.params.registerAddressEndian === 'little') {
                        GcUtils.setBytesLSB(payload, addrBytes, regAddr, payload.length);
                    }
                    else {
                        GcUtils.setBytes(payload, addrBytes, regAddr, payload.length);
                    }
                }
            }
            else {
                opCodeOrRegAddr = regAddr;
            }
        }
        else {
            opCodeOrRegAddr = opcodeAddr(opcode, regAddr, this.params.writeRegisterAddressBitShift);
        }
        const dataBytes = info.nBytes ?? ((info.size ?? 8) + 7) >> 3;
        if (this.params.dataEndian === 'little') {
            GcUtils.setBytesLSB(payload, dataBytes, value, payload.length);
        }
        else {
            GcUtils.setBytes(payload, dataBytes, value, payload.length);
        }
        const unit = this.params.unit ?? 2;
        const deviceAddrs = this.getDeviceAddress(info);
        const params = [unit, deviceAddrs, opCodeOrRegAddr, flags];
        return this.targetEncoder.readResponse(this.targetEncoder.sendCommandPacket(I2C_TYPE, unit, 4 /* WriteRegister */, params, payload));
    }
}

export { AevmI2cCodec };
//# sourceMappingURL=AevmI2cCodec.js.map
