import { QFunctionOperator } from './QFunctionOperator';
import { DotOperator } from './DotOperator';
import { testLookupBinding } from './AbstractLookupOperator';
export class AbstractLookupOperatorFactory {
    parse(uri, factory, precedence) {
        const openingBrace = this.operator.charAt(0);
        const closingBrace = this.operator.charAt(1);
        const endPos = factory.findLastIndexOf(uri, closingBrace, true);
        if (endPos >= 0) {
            if (endPos === uri.length - 1) {
                // valid lookup operation
                const pos = factory.findLastIndexOf(uri, openingBrace);
                if (pos === 0) {
                    // literal array or just plain parentheses
                    return this.parseLiteral(uri.substring(1, uri.length - 1), factory, precedence);
                }
                else if (pos < 0) {
                    // missing matching '[' or '(' operator.
                    throw new Error(`I found a '${closingBrace}' operator, but I couldn't find the matching '${openingBrace}' operator.  ` +
                        `To be honest I was expecting one in the following text: ${uri.substring(0, endPos + 1)}`);
                }
                else if (pos === endPos - 1) {
                    // empty middle paramenter
                    throw new Error(`I found an empty operator '${this.operator}'.  To be honest, I was expecting to find something inside.`);
                }
                else {
                    // empty right paramenter, this is the normal case, nothing following the <expression>[].
                    let arrayText = uri.substring(0, pos);
                    const indexText = uri.substring(pos + 1, endPos);
                    if (arrayText === 'Q') {
                        return QFunctionOperator.factory.parse(indexText, factory, 0);
                    }
                    // strip parenthesis (since we are not registering lookup bindings in binding Registry)
                    while (arrayText.charAt(0) === '(' && arrayText.charAt(arrayText.length - 1) === ')') {
                        precedence = 0; // reset precedence do to parentheses found
                        arrayText = arrayText.substring(1, arrayText.length - 1);
                    }
                    const lookupBinding = factory.parseExpression(arrayText, precedence, true);
                    if (lookupBinding) {
                        testLookupBinding(lookupBinding, this.operator); // throw exception if invalid binding found.
                        const indexBindings = [];
                        const parameters = indexText.split(',');
                        for (let i = 0; i < parameters.length; i++) {
                            const parameter = parameters[i];
                            if (parameter.length === 0) {
                                throw new Error('Empty array index or function parameter.  ' +
                                    'To be honest, I was expecting one or more parameters separated by commas, ' +
                                    'but found that one of the parameters was empty in: ' + indexText);
                            }
                            const indexBinding = factory.parseExpression(parameter, 0);
                            if (!indexBinding) {
                                throw new Error(`Index binding "${parameter}" does not exist`);
                            }
                            indexBindings.push(indexBinding);
                        }
                        return this.createOperator(lookupBinding, indexBindings);
                    }
                    else {
                        throw new Error(`Array binding '${arrayText}[] does not exist.`);
                    }
                }
            }
            else if (uri.charAt(endPos + 1) === '.' && endPos < uri.length - 2) {
                // dot operator found
                return DotOperator.factory.parse(uri, factory, precedence);
            }
            else { // extra trailing text.
                throw new Error(`I found an operator '${this.operator}' with unexpected characters following it.  ` +
                    `To be honest, I was not expecting to find another operator after the last '${closingBrace}` +
                    ` in the following text: ${uri.substring(endPos + 1)}`);
            }
        }
        return null;
    }
}
//# sourceMappingURL=AbstractLookupOperatorFactory.js.map