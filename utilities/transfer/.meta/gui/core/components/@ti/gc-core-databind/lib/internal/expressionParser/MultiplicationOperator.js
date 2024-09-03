import { AbstractBinaryOperatorFactory, AbstractBinaryOperator } from './AbstractBinaryOperator';
const OP = '*';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new MultiplicationOperator(leftOperand, rightOperand);
    }
}
export class MultiplicationOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = function (left, right) {
            return left * right;
        };
    }
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    doSetValue(value, constant, isLeftParamConstant) {
        return value / constant;
    }
    getType() {
        return 'number';
    }
}
MultiplicationOperator.factory = new Factory();
//# sourceMappingURL=MultiplicationOperator.js.map