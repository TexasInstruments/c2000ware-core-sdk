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
import { AbstractLiteralBinding } from './AbstractLiteralBinding';
import { BooleanLiteral } from './BooleanLiteral';
import { NumberLiteral } from './NumberLiteral';
const openingBracket = '[';
const closingBracket = ']';
const separator = ',';
export class ArrayLiteral extends AbstractLiteralBinding {
    constructor(valueArray) {
        super(valueArray);
    }
    toString() {
        let text = openingBracket + (this.cachedValue.length === 0 ? '' : this.cachedValue[0].toString());
        for (let i = 1; i < this.cachedValue.length; i++) {
            text += separator + this.cachedValue[i].toString();
        }
        return text + closingBracket;
    }
    static parseLiteral(uri) {
        const values = uri.split(separator);
        if (values === null || values.length === 0) {
            return new ArrayLiteral([]);
        }
        else if (values.length === 1) {
            return new ArrayLiteral([values[0]]);
        }
        const stringLiterals = [];
        let numberLiterals = [];
        let booleanLiterals = [];
        for (let i = 0; i < values.length; i++) {
            const value = values[i].trim();
            if (value.length > 0) {
                stringLiterals.push(value);
                if (booleanLiterals !== null) {
                    const booleanLiteral = BooleanLiteral.parse(value);
                    if (booleanLiteral !== null) {
                        booleanLiterals.push(booleanLiteral);
                    }
                    else {
                        booleanLiterals = null;
                    }
                }
                if (numberLiterals !== null) {
                    const numberLiteral = NumberLiteral.parse(value);
                    if (numberLiteral !== null) {
                        numberLiterals.push(numberLiteral);
                    }
                    else {
                        numberLiterals = null;
                    }
                }
            }
            else {
                // empty item
                stringLiterals.push('');
                if (numberLiterals !== null) {
                    numberLiterals.push(0);
                }
                if (booleanLiterals !== null) {
                    booleanLiterals.push(false);
                }
            }
        }
        return new ArrayLiteral(booleanLiterals || numberLiterals || stringLiterals);
    }
}
//# sourceMappingURL=ArrayLiteral.js.map