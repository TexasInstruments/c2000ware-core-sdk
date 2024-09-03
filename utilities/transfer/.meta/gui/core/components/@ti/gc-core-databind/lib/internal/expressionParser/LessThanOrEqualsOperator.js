import { AbstractComparisonOperator, AbstractComparisonOperatorFactory } from './AbstractComparisonOperator';
const OP = '<=';
class Factory extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LessThanOrEqualsOperator(leftOperand, rightOperand);
    }
}
function doEval(left, right) {
    return left <= right;
}
export class LessThanOrEqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = doEval;
        this.evalString = doEval;
    }
}
LessThanOrEqualsOperator.factory = new Factory();
//# sourceMappingURL=LessThanOrEqualsOperator.js.map