import { AbstractBinaryOperator, AbstractBinaryOperatorFactory } from './AbstractBinaryOperator';
const OP = '-';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new SubtractionOperator(leftOperand, rightOperand);
    }
}
export class SubtractionOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = function (left, right) {
            return left - right;
        };
    }
    doSetValue(value, constant, isLeftParamConstant) {
        return isLeftParamConstant ? constant - value : value + constant;
    }
    getType() {
        return 'number';
    }
}
SubtractionOperator.factory = new Factory();
//# sourceMappingURL=SubtractionOperator.js.map