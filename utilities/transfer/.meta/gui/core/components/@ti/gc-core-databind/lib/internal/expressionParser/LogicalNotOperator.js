import { AbstractUnaryOperator, AbstractUnaryOperatorFactory } from './AbstractUnaryOperator';
const OP = '!';
class Factory extends AbstractUnaryOperatorFactory {
    constructor() {
        super(...arguments);
        this.operator = OP;
    }
    createOperator(operand) {
        // eslint-disable-next-line @typescript-eslint/no-use-before-define
        return new LogicalNotOperator(operand);
    }
}
export class LogicalNotOperator extends AbstractUnaryOperator {
    constructor() {
        super(...arguments);
        this.operator = OP;
        // eslint-disable-next-line @typescript-eslint/no-unused-vars
        this.evalBoolean = function (value, write) {
            return !value;
        };
        this.evalNumber = function (value, write) {
            if (write) {
                return value ? 0 : 1;
            }
            return !value;
        };
    }
    getType() {
        return 'boolean';
    }
}
LogicalNotOperator.factory = new Factory();
//# sourceMappingURL=LogicalNotOperator.js.map