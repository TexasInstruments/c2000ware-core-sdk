/**
 *  Copyright (c) 2020, 2023 Texas Instruments Incorporated
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
import { NoopDataEncoderType, NoopDataDecoderType } from './CodecDataTypes';
import { codecRegistry } from './CodecRegistry';
import { Events } from '../../../gc-core-assets/lib/Events';
/**
 * Null codec to be used in lieu of null pointers.
 */
export const nullDataCodec = new (class {
    constructor() {
        this.decoderInputType = NoopDataDecoderType;
        this.decoderOutputType = NoopDataEncoderType;
        this.encoderInputType = NoopDataEncoderType;
        this.encoderOutputType = NoopDataDecoderType;
        this.id = '';
    }
    addChildDecoder() {
    }
    setParentEncoder() {
    }
    dispose() {
    }
    encode(data) {
    }
    decode(data) {
        return false;
    }
})();
/**
 * Abstract Encoder implementation that manages the targetDecoder pointer.
 */
export class AbstractEncoder extends Events {
    constructor(id, encoderInputType, encoderOutputType) {
        super();
        this.id = id;
        this.encoderInputType = encoderInputType;
        this.encoderOutputType = encoderOutputType;
        codecRegistry.register(this);
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `codec id="${this.id}"`;
    }
    dispose() {
    }
}
/**
 * Abstract decoder implementation that manages the targetEncoder pointer.
 */
export class AbstractDecoder extends Events {
    constructor(id, decoderInputType, decoderOutputType) {
        super();
        this.id = id;
        this.decoderInputType = decoderInputType;
        this.decoderOutputType = decoderOutputType;
        codecRegistry.register(this);
    }
    setParentEncoder(parent) {
        this.targetEncoder = parent;
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `codec id="${this.id}"`;
    }
    dispose() {
        codecRegistry.unregister(this);
    }
}
/**
 * Abstract codec implementation that manages both the targetEncoder, and the targetDecoder, pointers.
 */
export class AbstractCodec extends AbstractDecoder {
    constructor(id, decoderInputType, decoderOutputType, encoderOutputType, encoderInputType) {
        super(id, decoderInputType, decoderOutputType);
        this.encoderOutputType = encoderOutputType;
        this.encoderInputType = encoderInputType;
    }
    addChildDecoder(child) {
        this.targetDecoder = child;
    }
}
/**
 * Abstract data decoder implementation that manages the targetEncoder pointer.
 */
export class AbstractDataDecoder extends AbstractDecoder {
    constructor(id, decoderInputType, decoderOutputType) {
        super(id, decoderInputType, decoderOutputType);
        this.targetEncoder = nullDataCodec;
    }
    deconfigure() {
        this.targetEncoder = nullDataCodec;
    }
}
/**
 * Abstract data encoder implementation that manages the targetDecoder pointer.
 */
export class AbstractDataEncoder extends AbstractEncoder {
    constructor(id, encoderInputType, encoderOutputType) {
        super(id, encoderInputType, encoderOutputType);
        this.targetDecoder = nullDataCodec;
    }
    deconfigure() {
        this.targetDecoder = nullDataCodec;
    }
}
/**
 * Abstract data codec implementation that manages both the targetEncoder, and the targetDecoder pointers.
 */
export class AbstractDataCodec extends AbstractDataDecoder {
    constructor(id, decoderInputType, decoderOutputType, encoderOutputType, encoderInputType) {
        super(id, decoderInputType, decoderOutputType);
        this.encoderOutputType = encoderOutputType;
        this.encoderInputType = encoderInputType;
        this.targetDecoder = nullDataCodec;
    }
    addChildDecoder(child) {
        if (this.targetDecoder && this.targetDecoder !== nullDataCodec) {
            // eslint-disable-next-line @typescript-eslint/no-use-before-define
            this.targetDecoder = new DataDecoderTap(child, this.targetDecoder, this.encoderOutputType, this.encoderInputType);
        }
        else {
            this.targetDecoder = child;
        }
    }
    deconfigure() {
        super.deconfigure();
        this.targetDecoder = nullDataCodec;
    }
}
class DataDecoderTap extends AbstractDataDecoder {
    constructor(targetDecoder, next, decoderInputType, decoderOutputType) {
        super('tap', decoderInputType, decoderOutputType);
        this.targetDecoder = targetDecoder;
        this.next = next;
        this.params = {};
    }
    decode(data) {
        const result1 = this.targetDecoder.decode(data);
        const result2 = this.next.decode(data);
        return result1 instanceof Error ? result1 : result2 instanceof Error ? result2 : result1 && result2;
    }
}
//# sourceMappingURL=AbstractCodec.js.map