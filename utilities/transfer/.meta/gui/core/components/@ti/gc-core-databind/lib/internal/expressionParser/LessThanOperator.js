import { AbstractComparisonOperatorFactory, AbstractComparisonOperator } from './AbstractComparisonOperator';
const OP = '<';
class Factory extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LessThanOperator(leftOperand, rightOperand);
    }
}
function doEval(left, right) {
    return left < right;
}
export class LessThanOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = doEval;
        this.evalString = doEval;
    }
}
LessThanOperator.factory = new Factory();
//# sourceMappingURL=LessThanOperator.js.map