import { VariableBindValue } from './VariableBindValue';
import { ProgressCounter } from './ProgressCounter';
import { refreshEventType, preRefreshEventType } from './IRefreshIntervalProvider';
/**
 * Class that implements IBindValue for a refresh interval value.  Clients can
 * set the interval (in milliseconds) by calling setValue().  Also, clients can
 * register for onRefresh() listeners that will be called periodically based on
 * the current refresh interval.  This class is useful for providing the polling
 * events other bindings that need to poll to detect changes.
 *
 * @constructor
 * @extends gc.databind.VariableBindValue
 * @implements gc.databind.IValueBind
 */
export class RefreshIntervalBindValue extends VariableBindValue {
    constructor(defaultValue = 100) {
        super(defaultValue);
        this.hasListeners = false;
        this.excludeFromStorageProviderData = true;
        this.doOnRefresh = this.onRefresh.bind(this);
        this.doOnResetTimer = this.onResetTimer.bind(this);
        this.addEventListenerOnFirstAdded(refreshEventType, () => {
            this.hasListeners = true;
            this.onResetTimer();
        });
        this.removeEventListenerOnLastRemoved(refreshEventType, () => {
            this.hasListeners = false;
        });
    }
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    onValueChanged(details) {
        this.excludeFromStorageProviderData = false;
        this.onResetTimer(); // kick start timer in case new value is not negative.
    }
    dispose() {
        if (this.timer) {
            clearTimeout(this.timer);
            this.timer = undefined;
        }
    }
    async onRefresh(progressCounter) {
        // clear outstanding timer if there is one.
        if (this.timer) {
            clearTimeout(this.timer);
            this.timer = undefined;
        }
        let progress = new ProgressCounter();
        this.fireEvent(preRefreshEventType, { progress });
        progress.done();
        if (progress.getProgress() < 100) { // test if promise is resolve without waiting for next clock tick.
            await progress.promise;
        }
        progress = progressCounter !== null && progressCounter !== void 0 ? progressCounter : new ProgressCounter(this.doOnResetTimer);
        this.fireEvent(refreshEventType, { progress });
        progress.done();
        return await progress.promise;
    }
    onResetTimer() {
        // only restart the timer if we have listeners and a timer is not pending.
        if (this.timer === undefined && this.hasListeners) {
            const delay = this.getValue();
            if (delay >= 0) {
                this.timer = setTimeout(this.doOnRefresh, delay);
            }
        }
    }
    onDisconnected() {
        if (this.timer === undefined && this.hasListeners) {
            const delay = this.getValue();
            if (delay < 0) {
                // kick start a refresh in case we aren't polling, and we need to queue up one read operation for the next
                // time we connect.
                this.onRefresh();
            }
        }
    }
}
//# sourceMappingURL=RefreshIntervalBindValue.js.map