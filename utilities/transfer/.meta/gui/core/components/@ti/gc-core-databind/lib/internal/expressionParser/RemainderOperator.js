import { AbstractBinaryOperator, AbstractBinaryOperatorFactory } from './AbstractBinaryOperator';
/* eslint-disable @typescript-eslint/no-unused-vars */
const OP = '%';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new RemainderOperator(leftOperand, rightOperand);
    }
}
export class RemainderOperator extends AbstractBinaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = function (left, right) {
            return left % right;
        };
    }
    getType() {
        return 'number';
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    doSetValue(value, constant, isLeftParamConstant) {
    }
    get readOnly() {
        return true;
    }
}
RemainderOperator.factory = new Factory();
//# sourceMappingURL=RemainderOperator.js.map