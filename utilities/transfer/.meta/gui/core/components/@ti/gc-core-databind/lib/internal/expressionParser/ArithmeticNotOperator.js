import { AbstractUnaryOperatorFactory, AbstractUnaryOperator } from './AbstractUnaryOperator';
const OP = '~';
class Factory extends AbstractUnaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(operand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new ArithmeticNotOperator(operand);
    }
}
export class ArithmeticNotOperator extends AbstractUnaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        // eslint-disable-next-line @typescript-eslint/no-unused-vars
        this.evalNumber = function (value, write) {
            return ~value;
        };
    }
}
ArithmeticNotOperator.factory = new Factory();
//# sourceMappingURL=ArithmeticNotOperator.js.map