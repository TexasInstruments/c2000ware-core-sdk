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
import { AbstractBinaryOperatorFactory, AbstractBinaryOperator } from './AbstractBinaryOperator';
import { DataConverter } from '../DataConverter';
import { QualifierFactoryMap } from '../QualifierFactoryMap';
import { NumberLiteral } from './NumberLiteral';
/* eslint-disable @typescript-eslint/no-unused-vars */
const OP = 'Q()';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    parse(uri, factory, precedence) {
        const pos = factory.findFirstIndexOf(uri, ',');
        if (pos <= 0 || pos >= uri.length - 1 || pos !== factory.findLastIndexOf(uri, ',')) {
            throw new Error('Invalid number of paramters for Q() function.  The Q() function requires two and only two parameters separated by a single comma.');
        }
        let operandText = uri.substring(0, pos);
        const leftOperand = factory.parseExpression(operandText, precedence);
        operandText = uri.substring(pos + ','.length);
        const rightOperand = factory.parseExpression(operandText, precedence);
        if (leftOperand === null || rightOperand === null) {
            throw new Error(`Missing operands for the ${this.operator} operator.`);
        }
        return this.createOperator(leftOperand, rightOperand);
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new QFunctionOperator(leftOperand, rightOperand);
    }
}
export class QFunctionOperator extends AbstractBinaryOperator {
    constructor(leftOperand, rightOperand) {
        super(leftOperand, rightOperand);
        this.operator = OP;
    }
    getValue() {
        const value = +this.leftOperand.getValue();
        const q = +this.rightOperand.getValue();
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return formatValue(value, q);
    }
    setValue(newValue, progress, forceWrite) {
        newValue = +newValue;
        const q = +this.rightOperand.getValue();
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        this.leftOperand.setValue(unFormatValue(newValue, q), progress, forceWrite);
    }
    toString() {
        return 'Q(' + this.leftOperand.toString() + ', ' + this.rightOperand.toString() + ')';
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    doSetValue(lparam, rparam, write) {
    }
    getType() {
        return 'number';
    }
}
QFunctionOperator.factory = new Factory();
function formatValue(value, q) {
    if (isNaN(value)) {
        return value;
    }
    if (isNaN(q)) {
        return q;
    }
    return value / (Math.pow(2, q));
}
function unFormatValue(value, q) {
    if (isNaN(q)) {
        value = q;
    }
    else if (!isNaN(value)) {
        value = Math.round(value * Math.pow(2, q));
    }
    return value;
}
DataConverter.register({ convert: formatValue }, 'q');
DataConverter.register({ convert: unFormatValue }, 'number', 'q');
QualifierFactoryMap.add('q', class extends QFunctionOperator {
    constructor(leftOperand, qValue = 0) {
        super(leftOperand, new NumberLiteral(qValue));
    }
    static create(leftOperand, qValue = 0) {
        return new this(leftOperand, qValue);
    }
});
//# sourceMappingURL=QFunctionOperator.js.map