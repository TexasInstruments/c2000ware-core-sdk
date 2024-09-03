import { ExpressionParser } from './expressionParser/ExpressionParser';
/**
 * Abstract class that provides default implementation of IBindFactory.  This class
 * implements the getName() method for IBindFactory.
*/
export class AbstractBindProvider {
    /**
     * Constructor for AbstractBindProvider.
     *
     * @param bindings initial bindings to start with.
     */
    constructor(bindings) {
        this.expressionParser = new ExpressionParser(this, bindings);
    }
    /**
     * If the cache contains an IBindValue with the given name, this method will
     * returns it. Otherwise the binding is created by first evaluating any
     * expression then by using the registered models to create the appropriate
     * bindings to satisfy the bind expression.
     *
     * @param name the name of the binding.
     * @returns  the binding if found in the cache or created; otherwise, null.
     */
    getBinding(name) {
        return this.expressionParser.parseExpression(name);
    }
    dispose() {
        this.expressionParser.dispose();
    }
    /**
     * Method primarily used for testing.  It returns a count of the total number of data bindings.
     *
     * @private
     * @returns number of data bindings
     */
    getBindingCount() {
        return this.expressionParser.getBindingCount();
    }
}
//# sourceMappingURL=AbstractBindProvider.js.map