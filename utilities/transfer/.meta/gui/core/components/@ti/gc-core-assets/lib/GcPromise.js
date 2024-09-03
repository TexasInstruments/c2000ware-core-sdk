/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
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
 */
/* eslint-disable @typescript-eslint/no-explicit-any */
/**
 * An extension of a native Promise that provides the ability to test the pending, fulfilled, and rejected state of
 * a promise, and enable the ability of a promise to be cancelled, if the result of the promise is no longer needed.
 */
class GcPromise extends Promise {
    constructor() {
        super(...arguments);
        this.state = 'Pending';
        /**
         * A flag used to signal to the provider of a promise that the value of the promise is no longer needed by the client,
         * and the operation can be prematurely short circuited.  For example, if a provider creates a promise to represent
         * multiple asynchronous operations that are performed one after the other, they can check the cancelled state to
         * determine if the operation should continue, between, each asynchronous operation.  Of course this is optional,
         * and the client's signal that the promise should be cancelled may go unnoticed, and the operation is not short circuited.
         */
        this.cancelled = false;
    }
    /**
     * A factory for creating a GcPromise.  This is necessary because it is not possible to extend the constructor of the native
     * Promise.  So all GcPromise instances must be created with this factory method, instead of using new GcPromise(); otherwise,
     * this promise will not support all of the functionality.
     *
     * @returns a new instance of a GcPromise.
     */
    static create(executor) {
        const promise = new GcPromise(executor);
        promise.then(() => {
            promise.state = 'Fulfilled';
        }).catch(() => {
            promise.state = 'Rejected';
        });
        return promise;
    }
    /**
     * Property indicating that the promise has been resolved, was not rejected, and is not still pending.
     */
    get isFulfilled() {
        return this.state === 'Fulfilled';
    }
    /**
     * Property indicating that the promise is still pending, and has not been resolved or rejected.
     */
    get isPending() {
        return this.state === 'Pending';
    }
    /**
     * Property indicating that the promise was rejected, and is not still pending.
     */
    get isRejected() {
        return this.state === 'Rejected';
    }
    /**
     * Factory for creating a deferred promise.  A deferred promise has methods to resolve and reject the promise later.
     * This is useful if the asynchronous operation cannot be performed within the native Promise() constructor, but requires
     * storing the promise and resolving it later.
     *
     * @returns a deferred promise
     */
    static defer() {
        let resolveFn = function (value) { };
        let rejectFn = function (reason) { };
        const promise = this.create(function (resolve, reject) {
            resolveFn = resolve;
            rejectFn = reject;
        });
        return {
            resolve: resolveFn,
            reject: rejectFn,
            promise: promise
        };
    }
    /**
     * Method to create a timeout on a promise being fulfilled, one or more promises to be fulfilled.  This differs to the native Promise.all() method that will
     * fail if any of the promises are rejected.  This method will wait for all promises to be reject or resolved before
     * being fulfilled and returning the results of all promises.
     *
     * @returns a new promise that is either resolved when the given promise resolves, or is rejected when the timeout has expired.
     */
    static timeout(promise, time, message) {
        const deferred = GcPromise.defer();
        let done = false;
        const timer = setTimeout(() => {
            if (!done) {
                done = true;
                deferred.reject(message);
            }
        }, time);
        promise.then(value => {
            if (!done) {
                done = true;
                clearTimeout(timer);
                deferred.resolve(value);
            }
        }).catch(reason => {
            if (!done) {
                done = true;
                clearTimeout(timer);
                deferred.reject(reason);
            }
        });
        return deferred.promise;
    }
}

export { GcPromise };
//# sourceMappingURL=GcPromise.js.map
