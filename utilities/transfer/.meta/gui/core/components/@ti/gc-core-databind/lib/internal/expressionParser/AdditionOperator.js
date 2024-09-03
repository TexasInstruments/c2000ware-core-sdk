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
const OP = '+';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new AdditionOperator(leftOperand, rightOperand);
    }
}
function doAdd(left, right) {
    return left + right;
}
export class AdditionOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalArray = function (left, right) {
            let result;
            if (left.length === 0) {
                result = right;
            }
            else if (right.length === 0) {
                result = left;
            }
            else {
                result = [];
                let i;
                for (i = 0; i < left.length; i++) {
                    result.push(left[i]);
                }
                for (i = 0; i < right.length; i++) {
                    result.push(right[i]);
                }
            }
            return result;
        };
        this.evalString = doAdd;
        this.evalNumber = doAdd;
    }
    doSetValue(value, constant, isLeftParamConstant) {
        const type = this.getType();
        if (type === 'string') {
            const match = constant.toString();
            if (isLeftParamConstant) {
                if (value.indexOf(match) === 0) {
                    return value.substring(match.length);
                }
            }
            else if (value.lastIndexOf(match) + match.length === value.length) {
                return value.substring(0, value.length - match.length);
            }
        }
        else if (type === 'number') {
            return value - constant;
        }
        return value;
    }
}
AdditionOperator.factory = new Factory();
//# sourceMappingURL=AdditionOperator.js.map