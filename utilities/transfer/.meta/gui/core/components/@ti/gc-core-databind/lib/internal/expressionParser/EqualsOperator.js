import { AbstractComparisonOperatorFactory, AbstractComparisonOperator } from './AbstractComparisonOperator';
const OP = '==';
class Factory extends AbstractComparisonOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new EqualsOperator(leftOperand, rightOperand);
    }
}
function doEvalEquals(left, right) {
    // eslint-disable-next-line eqeqeq
    return left == right;
}
export class EqualsOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalNumber = doEvalEquals;
        this.evalBoolean = doEvalEquals;
        this.evalString = doEvalEquals;
    }
}
EqualsOperator.factory = new Factory();
//# sourceMappingURL=EqualsOperator.js.map