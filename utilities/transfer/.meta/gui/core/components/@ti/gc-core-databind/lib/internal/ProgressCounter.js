import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
export const nullProgressCounter = new (class {
    constructor() {
        this.promise = Promise.resolve(0);
        this.count = 0;
        this.totalCount = 0;
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    wait() {
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    done() {
    }
    getProgress() {
        return 100;
    }
})();
/**
 * Class that implements IProgressCounter interface to count progress.
 * This class is constructed with a
 * callback that will be called when the progress reaches 100%.
 * A single initial job is added to the progress counter automatically.
 * in the constructor.
 * As a result, the client must call IProgressCounter.done() once to
 * complete the job.  Typically, the client will pass this object
 * around to other parties who may or may not add their own jobs
 * to the progress counter.  Only when all jobs are completed will
 * the client receive the callback.
 *
 */
export class ProgressCounter {
    constructor(callback) {
        this.callback = callback;
        this.jobCount = 1;
        this.jobsDone = 0;
        this.deferred = GcPromise.defer();
        this.promise = this.deferred.promise;
    }
    wait(jobs = 1) {
        this.jobCount += jobs;
    }
    done(jobs = 1) {
        this.jobsDone += jobs;
        if (this.jobsDone === this.jobCount) {
            if (this.callback) { // make sure callback is called immediately, instead of waiting for next clock tick for promise.
                this.callback({ jobsCompleted: this.jobCount - 1 });
                this.callback = undefined;
            }
            this.deferred.resolve(this.jobCount - 1);
        }
    }
    getProgress() {
        return 100 * this.jobsDone / this.jobCount;
    }
    get count() {
        return this.jobsDone;
    }
    get totalCount() {
        return this.jobCount;
    }
}
//# sourceMappingURL=ProgressCounter.js.map