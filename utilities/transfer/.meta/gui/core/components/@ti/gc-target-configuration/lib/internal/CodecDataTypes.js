export class EncoderType {
    constructor(name) {
        this.name = name;
    }
    asEncoder(encoder) {
        if (!this.isCompatible(encoder.encoderInputType)) {
            throw new Error(`Type Mismatch.  ${encoder.id}'s encoder type ${encoder.encoderInputType.name} is not compatible with ${this.name}`);
        }
        return encoder;
    }
    isCompatible(type) {
        return this === type;
    }
}
export class DecoderType {
    constructor(name) {
        this.name = name;
    }
    asDecoder(decoder) {
        if (!this.isCompatible(decoder.decoderInputType)) {
            throw new Error(`Type Mismatch.  ${decoder.id}'s encoder type ${decoder.decoderInputType.name} is not compatible with ${this.name}`);
        }
        return decoder;
    }
    isCompatible(type) {
        return this === type;
    }
}
export const NoopEncoderType = new EncoderType('void');
export const NoopDecoderType = new DecoderType('void');
export const NoopDataEncoderType = new EncoderType('void');
export const NoopDataDecoderType = new DecoderType('void');
export class PrimitiveDataType extends EncoderType {
    asDecoder(decoder) {
        if (!this.isCompatible(decoder.decoderInputType)) {
            throw new Error(`Type Mismatch.  ${decoder.id}'s encoder type ${decoder.decoderInputType.name} is not compatible with ${this.name}`);
        }
        return decoder;
    }
}
export class CompositeDataType extends PrimitiveDataType {
    constructor(...inputTypes) {
        super(`${inputTypes.map((type) => type.name).join('|')}`);
        this.baseTypes = inputTypes;
    }
    isCompatible(outputType) {
        return this.baseTypes.reduce((result, type) => result || outputType === type, false);
    }
}
export const bufferDataType = new PrimitiveDataType('buffer');
export const binaryDataType = new PrimitiveDataType('uint8array');
export const stringDataType = new PrimitiveDataType('string');
export const bufferOrStringDataType = new CompositeDataType(stringDataType, bufferDataType);
export const binaryOrBufferDataType = new CompositeDataType(binaryDataType, bufferDataType);
//# sourceMappingURL=CodecDataTypes.js.map