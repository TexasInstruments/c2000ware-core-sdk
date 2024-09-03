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
export class ExpressionParserUtils {
    static isDigit(c) {
        return (c >= '0' && c <= '9') || c === '.';
    }
    static composeUnrecognizedTextErrMsg(text, literalErrorMessage) {
        // Unrecognized character
        let msg = 'Unexpected character';
        if (text.length > 1) {
            msg += 's "' + text + '" were';
        }
        else {
            msg += ' "' + text + '" was';
        }
        msg += ' found.  If this was suppose to be an operator, it is not supported.';
        if (literalErrorMessage !== null) {
            msg += '  Also, I do not recognize this as part of a literal.  ' + literalErrorMessage;
        }
        throw new Error(msg);
    }
    static composeUnexpectedWhiteSpaceErrMsg(text) {
        // spaces are not allowed in identifiers
        throw new Error('Unexpected white space was found in the following expression "' + text +
            '".  To be honest, I was expecting an operator, or something other than blank.');
    }
    static composeUnrecognizedIdentifier(unrecognizedText, literalErrorMessage) {
        if (unrecognizedText.trim().length === 0) {
            this.composeUnexpectedWhiteSpaceErrMsg(unrecognizedText);
        }
        else {
            this.composeUnrecognizedTextErrMsg(unrecognizedText, literalErrorMessage);
        }
    }
    static composeMissingClosingBraceErrMsg(uri, brace) {
        throw new Error('To be honest, I was expecting to find a terminating ' + brace + ' after "' + uri + '".');
    }
    static composeMissingOperatorErrMsg(uri) {
        throw new Error('To be honest, I was expecting to find an operator at the beginning of this expression: ' + uri);
    }
    static testIdentifier(text, errMessageContext) {
        if (!this.isDigit(text.charAt(0))) {
            const unexpectedCharacters = this.notIdentifierRegExp.exec(text);
            if (unexpectedCharacters !== null) {
                this.composerInvalidIdentifierErrorMessage(text, `I was not expecting to find "${unexpectedCharacters[0]}"`, errMessageContext);
            }
        }
        else if (text.charAt(0) === '.') {
            this.composerInvalidIdentifierErrorMessage(text, 'I was not expecting it to begin with a period.', errMessageContext);
        }
        else {
            this.composerInvalidIdentifierErrorMessage(text, 'I was not expecting it to begin with a number.', errMessageContext);
        }
    }
    static getIdentifiers(text) {
        const matches = text.match(this.identifierSearch);
        return (matches === null || matches === void 0 ? void 0 : matches.filter(match => this.firstCharacterInIdentifier.test(match))) || [];
    }
    static composerInvalidIdentifierErrorMessage(text, errDetailMessage, errMessageContext = '') {
        throw new Error('Invalid identifier found' + errMessageContext + ': "' + text + '".  To be honest, ' + errDetailMessage);
    }
}
// eslint-disable-next-line no-useless-escape
ExpressionParserUtils.notIdentifierRegExp = /[^A-Za-z$_.0-9]+/;
ExpressionParserUtils.identifierSearch = /[A-Za-z$_.0-9]+|'[^']*'|"[^"]"/g;
ExpressionParserUtils.firstCharacterInIdentifier = /^[A-Za-z$_]/;
//# sourceMappingURL=ExpressionParserUtils.js.map