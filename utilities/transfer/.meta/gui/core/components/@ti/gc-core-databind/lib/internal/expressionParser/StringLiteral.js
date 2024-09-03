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
import { ExpressionParserUtils } from './ExpressionParserUtils';
const singleQuote = '\'';
export class StringLiteral extends AbstractLiteralBinding {
    constructor(literal) {
        super(literal);
        this.cachedValue = literal.split('\\\'').join(singleQuote);
        this.cachedValue = this.cachedValue.split('\\\\').join('\\');
    }
    static parseLiteral(uri) {
        if (uri.indexOf(singleQuote) === 0) {
            // find end pos skipping escaped quotes preceded by backslash character.
            let endPos = 0;
            let escaped;
            do {
                endPos = uri.indexOf(singleQuote, endPos + 1);
                escaped = false;
                for (let i = endPos; i > 0 && uri.charAt(i - 1) === '\\'; i--) {
                    escaped = !escaped;
                }
            } while (escaped);
            if (endPos <= 0) {
                ExpressionParserUtils.composeMissingClosingBraceErrMsg(uri, 'single quote');
            }
            else if (endPos !== uri.length - 1) {
                ExpressionParserUtils.composeMissingOperatorErrMsg(uri.substring(endPos + 1));
            }
            else {
                // strip quotes
                uri = uri.substring(1, uri.length - 1);
                return new StringLiteral(uri);
            }
        }
        return null;
    }
}
//# sourceMappingURL=StringLiteral.js.map