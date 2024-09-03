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
import { AbstractLookupOperator, testLookupBinding } from './AbstractLookupOperator';
import { QualifierFactoryMap } from '../QualifierFactoryMap';
import { StringLiteral } from './StringLiteral';
import { ExpressionParserUtils } from './ExpressionParserUtils';
const OP = '.';
class Factory {
    constructor() {
        this.operator = OP;
    }
    parseQualifiers(leftOperand, operandText) {
        const { bindName, qualifier, param } = QualifierFactoryMap.getQualifier('.' + operandText);
        if (qualifier) {
            const bind = this.parseQualifiers(leftOperand, bindName.substring(1));
            return bind && qualifier.create(bind, param);
        }
        if (operandText.length > 0) {
            // eslint-disable-next-line @typescript-eslint/no-use-before-define
            return new DotOperator(leftOperand, operandText);
        }
        return leftOperand;
    }
    parse(uri, factory, precedence) {
        // dot operator is only allowed after array or function syntax.  Otherwise it is just part of the identifier for the model binding.
        let pos = factory.findLastIndexOf(uri, '].', true);
        if (pos < 0) {
            pos = factory.findLastIndexOf(uri, ').', true);
        }
        // can't be first or last character, because it's not a unary operator
        if (pos > 0 && pos < uri.length - 1) {
            pos++;
            let operandText = uri.substring(0, pos);
            const leftOperand = factory.parseExpression(operandText, precedence, true);
            if (leftOperand) {
                testLookupBinding(leftOperand, this.operator);
                operandText = uri.substring(pos + this.operator.length);
                ExpressionParserUtils.testIdentifier(operandText, ' in dot operator field name'); // throws exception if invalid identifier.
                return this.parseQualifiers(leftOperand, operandText);
            }
        }
        return null;
    }
}
export class DotOperator extends AbstractLookupOperator {
    constructor(lookupBinding, fieldNameBinding) {
        super(lookupBinding, [new StringLiteral(fieldNameBinding)]);
        this.operator = OP;
    }
    toString() {
        return this.lookupBinding.toString() + '.' + this.indexBindings[0];
    }
}
DotOperator.factory = new Factory();
//# sourceMappingURL=DotOperator.js.map