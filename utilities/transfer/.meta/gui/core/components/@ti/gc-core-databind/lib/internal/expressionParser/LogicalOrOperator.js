import { AbstractBinaryOperatorFactory } from './AbstractBinaryOperator';
import { AbstractComparisonOperator } from './AbstractComparisonOperator';
const OP = '||';
class Factory extends AbstractBinaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(leftOperand, rightOperand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LogicalOrOperator(leftOperand, rightOperand);
    }
}
export class LogicalOrOperator extends AbstractComparisonOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        this.evalBoolean = function (left, right) {
            return left || right;
        };
        this.evalNumber = function (left, right) {
            // eslint-disable-next-line eqeqeq
            return left != 0 || right != 0;
        };
    }
}
LogicalOrOperator.factory = new Factory();
//# sourceMappingURL=LogicalOrOperator.js.map