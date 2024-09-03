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
import { AbstractDataFormatter } from './AbstractDataFormatter';
import { DataConverter } from './DataConverter';
const QUALIFIER_PREFIX = '.$';
const QUALIFIER_PARAM_REGEX = /\d+$/;
export class QualifierFactoryMap {
    constructor() {
        this.instanceQualifierFactoryMap = {};
    }
    static add(name, factory) {
        this.globalQualifierFactoryMap[QUALIFIER_PREFIX + name] = factory;
    }
    add(name, factory) {
        this.instanceQualifierFactoryMap[QUALIFIER_PREFIX + name] = factory;
    }
    static getQualifier(name, instanceQualifierFactoryMap) {
        const pos = name.lastIndexOf(QUALIFIER_PREFIX);
        if (pos > 0) {
            let qualifierName = name.substring(pos).toLowerCase();
            const paramArray = qualifierName.match(QUALIFIER_PARAM_REGEX);
            let param;
            if (paramArray) {
                qualifierName = qualifierName.substring(0, qualifierName.length - paramArray[0].length);
                param = +paramArray[0];
            }
            let qualifierFactory = this.globalQualifierFactoryMap[qualifierName];
            if (instanceQualifierFactoryMap) {
                qualifierFactory = instanceQualifierFactoryMap[qualifierName] || qualifierFactory;
            }
            if (qualifierFactory) {
                return { bindName: name.substring(0, pos), qualifier: qualifierFactory, param: param };
            }
        }
        return { bindName: name };
    }
    getQualifier(name) {
        return QualifierFactoryMap.getQualifier(name, this.instanceQualifierFactoryMap);
    }
}
QualifierFactoryMap.globalQualifierFactoryMap = {};
function doPrecision(value, precision = 0) {
    if (precision > 0) {
        if (value.length > precision) {
            value = value.substring(value.length - precision);
        }
        else {
            for (let len = value.length; len < precision; len++) {
                value = '0' + value;
            }
        }
    }
    return value;
}
class HexFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'hex';
    }
    static create(operand, precision) {
        return new HexFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '0x' + input;
        }
        if (input < 0) {
            input = 0xFFFFFFFF + input + 1;
        }
        input = input.toString(16).toUpperCase();
        return '0x' + doPrecision(input, precision);
    }
}
DataConverter.register({ convert: HexFormatter.prototype.formatValue }, 'hex');
QualifierFactoryMap.add('hex', HexFormatter);
class DecimalFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'dec';
    }
    static create(operand, precision) {
        return new DecimalFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input) || precision === undefined) {
            return '' + input;
        }
        return input.toFixed(precision);
    }
}
DataConverter.register({ convert: DecimalFormatter.prototype.formatValue }, 'dec');
QualifierFactoryMap.add('dec', DecimalFormatter);
class ScientificFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'exp';
    }
    static create(operand, precision) {
        return new ScientificFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '' + input;
        }
        return input.toExponential(precision);
    }
}
DataConverter.register({ convert: ScientificFormatter.prototype.formatValue }, 'exp');
QualifierFactoryMap.add('exp', ScientificFormatter);
class BinaryFormatter extends AbstractDataFormatter {
    constructor(operand, precision) {
        super(operand);
        this.precision = precision;
        this.operator = 'binary';
        this.unFormattedType = 'number';
    }
    static create(operand, precision) {
        return new BinaryFormatter(operand, precision);
    }
    formatValue(input, precision) {
        input = +input;
        if (isNaN(input)) {
            return '' + input;
        }
        if (input < 0) {
            input = 0xFFFFFFFF + input + 1;
        }
        return doPrecision(input.toString(2), precision);
    }
    unFormatValue(input) {
        return Number.parseInt(input, 2);
    }
}
DataConverter.register({ convert: BinaryFormatter.prototype.formatValue }, 'binary');
DataConverter.register({ convert: BinaryFormatter.prototype.unFormatValue }, 'number', 'binary');
QualifierFactoryMap.add('binary', BinaryFormatter);
//# sourceMappingURL=QualifierFactoryMap.js.map