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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
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
import { AbstractBindExpressionParser } from './AbstractBindExpressionParser';
import { ConditionalOperator } from './ConditionalOperator';
import { EqualsOperator } from './EqualsOperator';
import { AdditionOperator } from './AdditionOperator';
import { NotEqualsOperator } from './NotEqualsOperator';
import { DivisionOperator } from './DivisionOperator';
import { NegationOperator } from './NegationOperator';
import { ArrayOperator } from './ArrayOperator';
import { GreaterThanOrEqualsOperator } from './GreaterThanOrEqualsOperator';
import { GreaterThanOperator } from './GreaterThanOperator';
import { FunctionOperator } from './FunctionOperator';
import { LogicalOrOperator } from './LogicalOrOperator';
import { LogicalAndOperator } from './LogicalAndOperator';
import { LessThanOrEqualsOperator } from './LessThanOrEqualsOperator';
import { LessThanOperator } from './LessThanOperator';
import { SubtractionOperator } from './SubtractionOperator';
import { MultiplicationOperator } from './MultiplicationOperator';
import { RemainderOperator } from './RemainderOperator';
import { LogicalNotOperator } from './LogicalNotOperator';
import { ArithmeticNotOperator } from './ArithmeticNotOperator';
export class ExpressionParser extends AbstractBindExpressionParser {
    constructor(bindProvider, bindings) {
        super(bindings);
        this.bindProvider = bindProvider;
        // add brackets that exclude operators
        this.addBraces('[', ']'); // array operator
        this.addBraces('\'', '\''); // string literal single quotes
        // add operator factories for parser here in reverse precedence order
        // Priority 13: conditional ?: operator
        this.addOperatorFactory(ConditionalOperator.factory);
        // Priority 12: logical or || operator.
        this.addOperatorFactory(LogicalOrOperator.factory);
        // Priority 11: logical and && operator.
        this.addOperatorFactory(LogicalAndOperator.factory);
        // Priority 10: bit wise or | operator.
        // Priority 9: bit wise xor ^ operator.
        // Priority 8: bit wise and & operator.
        // Priority 7: equality == and != operators
        this.addOperatorFactory(EqualsOperator.factory, NotEqualsOperator.factory);
        // Priority 6: comparison >, >=, <, <= operators
        this.addOperatorFactory(GreaterThanOrEqualsOperator.factory, LessThanOrEqualsOperator.factory, GreaterThanOperator.factory, LessThanOperator.factory);
        // Priority 5: shift >>, <<, >>> operators
        // Priority 4: arithmetic +, - operators
        this.addOperatorFactory(AdditionOperator.factory, SubtractionOperator.factory);
        // Priority 3: arithmetic *, /, % operators
        this.addOperatorFactory(MultiplicationOperator.factory, DivisionOperator.factory, RemainderOperator.factory);
        // Priority 2: unary operators
        this.addOperatorFactory(NegationOperator.factory, ArithmeticNotOperator.factory, LogicalNotOperator.factory);
        // Priority 1: array index [] operator, and function() operator
        this.addOperatorFactory(ArrayOperator.factory);
        this.addOperatorFactory(FunctionOperator.factory);
    }
    parseQualifiers(model, modelName, uri, isLookupBinding) {
        const { bindName, qualifier, param } = model.parseQualifier(uri);
        if (qualifier) {
            let bind = isLookupBinding ? null : this.bindings.get(modelName + bindName) || null;
            bind = bind || this.parseQualifiers(model, modelName, bindName, isLookupBinding);
            return bind ? qualifier.create(bind, param) : null;
        }
        if (isLookupBinding) {
            return model.createNewBind(bindName);
        }
        return model.getBinding(bindName);
    }
    bindValue(uri, isLookupBinding = false) {
        if (uri.length === 0) {
            throw new Error('Empty Param');
        }
        const { model, bindName } = this.bindProvider.parseModelFromBinding(uri);
        const modelName = uri.substring(0, uri.length - bindName.length);
        return this.parseQualifiers(model, modelName, bindName, isLookupBinding);
    }
}
//# sourceMappingURL=ExpressionParser.js.map