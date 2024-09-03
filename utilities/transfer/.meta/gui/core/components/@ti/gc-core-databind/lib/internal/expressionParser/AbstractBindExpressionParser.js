import { NumberLiteral } from './NumberLiteral';
import { StringLiteral } from './StringLiteral';
import { BooleanLiteral } from './BooleanLiteral';
import { ExpressionParserUtils } from './ExpressionParserUtils';
import { OperatorList } from './OperatorList';
import { isDisposable } from '../IDisposable';
// below is a regular expression. It has three alternatives to match
// 1. ^\s+ this matches all leading spaces
// 2. this matches two alternatives plus the optional spaces around it
// 2a. [^A-Za-z0-9$_ ']+ this matches anything that is not an identifier or
// anything in quotes.
// The space is a terminator for the character group. Dots are not included
// because we can
// remove the spaces around them.
// 2b. '[^']' this matches quoted text and includes spaces in between quotes
// 3. \s+$ this matches trailing spaces
// Alternative 1 & 3 have an empty capture group, and alternative 2's
// capture group excludes the
// surrounding spaces.
const stripSpacesMatchString = /^\s+|\s*([^A-Za-z0-9$_ ']+|'[^']*')\s*|\s+$/g;
export class Bracket {
    constructor(openingBrace, closingBrace, link) {
        this.openingBrace = openingBrace;
        this.closingBrace = closingBrace;
        this.link = link;
    }
    countBraces(text, brace, endingPos) {
        let count = 0;
        for (let pos = 0; pos <= endingPos;) {
            pos = text.indexOf(brace, pos);
            if (pos < 0 || pos > endingPos) {
                break;
            }
            else if (pos === 0 || (text.charAt(pos - 1) !== '\\' &&
                (this.link === undefined || !this.link.isInBracket(text, pos)))) {
                count++;
            }
            pos = pos + brace.length;
        }
        return count;
    }
    isInBracket(text, endingPos) {
        let count = this.countBraces(text, this.openingBrace, endingPos);
        if (count > 0) {
            if (this.closingBrace !== this.openingBrace) {
                count -= this.countBraces(text, this.closingBrace, endingPos);
                return count !== 0;
            }
            else if ((count & 1) !== 0) { // if odd count, then we are in a bracket; otherwise we are not.
                return true;
            }
        }
        // if not in this bracket, try the next one
        if (this.link !== undefined) {
            return this.link.isInBracket(text, endingPos);
        }
        return false; // we are not in any of the brackets.
    }
}
export class AbstractBindExpressionParser {
    constructor(bindings = new Map()) {
        this.bindings = bindings;
        this.operatorFactories = [];
        this.brackets = new Bracket('(', ')');
    }
    addOperatorFactory(...factories) {
        if (factories.length > 1) {
            this.operatorFactories.push(new OperatorList(factories));
        }
        else if (factories.length > 0) {
            this.operatorFactories.push(factories[0]);
        }
    }
    addBraces(openingBrace, closingBrace) {
        // ensure parenthesis () are kept at front of list, because order matters.
        this.brackets.link = new Bracket(openingBrace, closingBrace, this.brackets.link);
    }
    static parseLiteral(uri) {
        let result = NumberLiteral.parseLiteral(uri);
        if (result === null) {
            result = BooleanLiteral.parseLiteral(uri);
        }
        if (result === null) {
            result = StringLiteral.parseLiteral(uri);
        }
        return result;
    }
    findFirstIndexOf(text, operator, startingPos = 0) {
        let pos = startingPos;
        const len = operator.length - 2;
        // eslint-disable-next-line no-constant-condition
        while (true) {
            pos = text.indexOf(operator, pos);
            if (pos > 0 && this.brackets.isInBracket(text, pos + len)) {
                pos = pos + operator.length;
                if (pos >= text.length) {
                    pos = -1; // ran out of text, so indicate no match found.
                    break;
                }
            }
            else {
                break;
            }
        }
        return pos;
    }
    findLastIndexOf(text, operator, includeOperator) {
        let pos = text.lastIndexOf(operator);
        const len = includeOperator ? operator.length - 1 : -1;
        while (pos > 0 && this.brackets.isInBracket(text, pos + len)) {
            pos = text.lastIndexOf(operator, pos - operator.length);
        }
        return pos;
    }
    findMatchingBrace(text, openingBrace, closingBrace) {
        let pos = -1;
        let nestedBracePos = -1;
        do {
            pos = this.findFirstIndexOf(text, closingBrace, pos + 1);
            nestedBracePos = this.findFirstIndexOf(text, openingBrace, nestedBracePos + 1);
        } while (nestedBracePos >= 0 && pos > nestedBracePos);
        return pos;
    }
    parseExpression(uri, precedence, isLookupBinding = false) {
        if (uri.length === 0) {
            return null;
        }
        if (precedence === undefined) {
            // first time strip extra spaces in the expression so that
            // expressions that
            // differ only in extra spaces can be matched by string compares.
            // second time (called from expressionParser) there will be a hint
            // provided.
            uri = uri.replace(stripSpacesMatchString, '$1');
            precedence = 0;
        }
        if (!isLookupBinding && this.bindings.has(uri)) {
            return this.bindings.get(uri) || null;
        }
        let result = null;
        const unrecognizedText = ExpressionParserUtils.notIdentifierRegExp.exec(uri);
        // parse operators first
        if (unrecognizedText !== null) {
            for (let i = precedence; i < this.operatorFactories.length && result === null; i++) {
                const operatorFactory = this.operatorFactories[i];
                result = operatorFactory.parse(uri, this, i);
            }
        }
        // no operators found, try parsing literal
        let literalErrorMessage = null;
        if (result === null) {
            try {
                result = AbstractBindExpressionParser.parseLiteral(uri);
            }
            catch (e) {
                if (ExpressionParserUtils.isDigit(uri.charAt(0))) {
                    // identifiers can't start with a digit, so re throw this exception.
                    // hopefully this error message will be more meaningful that the identifier error message.
                    throw e;
                }
                literalErrorMessage = e.toString();
            }
        }
        // try parsing config variable references
        if (result === null) {
            if (unrecognizedText === null) {
                result = this.bindValue(uri, isLookupBinding);
            }
            else {
                ExpressionParserUtils.composeUnrecognizedIdentifier(unrecognizedText[0], literalErrorMessage);
            }
        }
        if (result) {
            result.uri = uri;
            if (typeof result.setIndex === 'function') {
                result.setIndex(); // kick start index lookups if parseLookupExpression returns a lookup operator.
            }
        }
        if (!isLookupBinding) {
            this.bindings.set(uri, result);
        }
        return result;
    }
    dispose() {
        this.bindings.forEach((bind) => {
            if (bind !== null && isDisposable(bind)) {
                bind.dispose();
            }
        });
        this.bindings.clear();
    }
    getBindingCount() {
        return this.bindings.size;
    }
}
//# sourceMappingURL=AbstractBindExpressionParser.js.map