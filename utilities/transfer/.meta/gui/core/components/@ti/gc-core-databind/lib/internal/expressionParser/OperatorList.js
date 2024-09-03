export class OperatorList {
    constructor(samePrecedenceOperators) {
        this.samePrecedenceOperators = samePrecedenceOperators;
        this.operator = '';
    }
    parse(uri, factory, precedence) {
        // search for first operator from right to left order
        let firstOperator = -1;
        let operator = null;
        for (let i = 0; i < this.samePrecedenceOperators.length; i++) {
            const parser = this.samePrecedenceOperators[i];
            const pos = factory.findLastIndexOf(uri, parser.operator);
            if (pos > firstOperator) {
                firstOperator = pos;
                operator = parser;
            }
        }
        if (operator !== null) {
            return operator.parse(uri, factory, precedence);
        }
        return null;
    }
}
//# sourceMappingURL=OperatorList.js.map