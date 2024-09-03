/**
 *  Copyright (c) 2022, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * Class to manage undo and redo stacks, as well as editor dirty state.
 */
class UndoStack {
    constructor() {
        this.operations = [];
        this.topOfStack = 0;
        this.cleanPosition = 0;
        /**
         * list of undo operations
         */
        this.undoStack = new Proxy(this, {
            get: function (target, prop) {
                if (prop === 'length') {
                    return target.topOfStack;
                }
                const n = +prop.toString();
                if (isNaN(n)) {
                    return undefined;
                }
                return target.operations[target.topOfStack - 1 - n];
            }
        });
        /**
         * List of redo operations
         */
        this.redoStack = new Proxy(this, {
            get: function (target, prop) {
                if (prop === 'length') {
                    return target.operations.length - target.topOfStack;
                }
                const n = +prop.toString();
                if (isNaN(n)) {
                    return undefined;
                }
                return target.operations[target.topOfStack + n];
            }
        });
    }
    /**
     * Flag indicating if an undo operation is possible.
     */
    get canUndo() {
        return this.topOfStack > 0;
    }
    /**
     * Flag indicating if a redo operation is possible.
     */
    get canRedo() {
        return this.topOfStack < this.operations.length;
    }
    /**
     * Flag indicating the if the current point in the undo stack represents a dirty or clean state.
     * Set the dirty state to false when committing changes, to indicate the current point in the
     * undo stack now represents a clean state.
     */
    get dirty() {
        return this.topOfStack !== this.cleanPosition;
    }
    set dirty(isDirty) {
        if (isDirty) {
            this.cleanPosition = -1; // setting dirty means it can never be clean.
        }
        else {
            this.cleanPosition = this.topOfStack;
        }
    }
    /**
     * Add a new edit operation to the end of the undo stack, and clear the redo stack.
     */
    pushOperation(op) {
        if (this.canRedo) {
            // clear redo stack
            this.operations.splice(this.topOfStack);
            if (this.cleanPosition > this.topOfStack) {
                this.dirty = true;
            }
        }
        this.operations.push(op);
        this.topOfStack++;
    }
    /**
     * Pop the first operation from the undo stack, and push it onto the redo stack.
     *
     * @returns operation popped from undo stack.
     */
    popUndoStack() {
        let result;
        if (this.canUndo) {
            this.topOfStack--;
            result = this.operations[this.topOfStack];
        }
        return result;
    }
    /**
     * Pop the first operation from the redo stack, and push it onto the undo stack.
     *
     * @returns operation popped from the redo stack.
     */
    popRedoStack() {
        let result;
        if (this.canRedo) {
            result = this.operations[this.topOfStack];
            this.topOfStack++;
        }
        return result;
    }
}

export { UndoStack };
//# sourceMappingURL=UndoStack.js.map
