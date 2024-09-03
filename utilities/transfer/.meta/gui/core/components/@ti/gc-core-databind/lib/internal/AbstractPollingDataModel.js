/**
 *  Copyright (c) 2020, 2021 Texas Instruments Incorporated
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
import { DataStorageProvider } from './DataStorageProvider';
import { AbstractBindFactory } from './AbstractBindFactory';
import { RefreshIntervalBindValue } from './RefreshIntervalBindValue';
/**
 * Abstract class that provides default implementation of IBindFactory for a polling data model.  This class
 * provides a "$refresh_interval" binding can be used to control the polling interval any bindings that are created.
 * Alternatively, each binding could have it's own polling interval as needed.  The $refresh_interval is available
 * to app developers so that they could allow end users to control the polling interval.  The refresh interval represents
 * a delay between polling cycles, and does not reflect real time constraints.  This way if refresh interval is too short
 * it doesn't backlog polling operations, instead it simply polls as fast as possible.
*/
export class AbstractPollingDataModel extends AbstractBindFactory {
    /**
     * @param name uniquely identifiable name for this bind factory.
     * @param defaultRefreshInterval the default interval for polling in milliseconds.
     */
    constructor(name, defaultRefreshInterval = 100) {
        super(name);
        this.defaultRefreshInterval = defaultRefreshInterval;
        DataStorageProvider.addDataModel(this);
        this.defaultRefreshBinding = new RefreshIntervalBindValue(defaultRefreshInterval);
        this.modelBindings.set('$refresh_interval', this.defaultRefreshBinding);
        this.refreshIntervalBindList = [this.defaultRefreshBinding];
    }
    createNewBind(uri) {
        let result = null;
        if (uri.indexOf('$refresh_interval.') === 0) {
            result = new RefreshIntervalBindValue(this.defaultRefreshInterval);
            this.refreshIntervalBindList.push(result);
        }
        return result;
    }
    /**
     * Helper method to refresh, or re-read, all bindings associated with this model.  This method goes through
     * all refresh interval providers created by this model and forces them to refresh all their bindings that are
     * registered with them.
     *
     * @param progress a progress counter to optionally use for this operation.
     * @returns a promise that resolves to the number of registers refreshed by this method.
     */
    async refreshAllBindings(progress) {
        const results = await Promise.all(this.refreshIntervalBindList.map(refreshBind => refreshBind.onRefresh(progress)));
        return results.reduce((total, result) => total + result);
    }
    /**
     * Implementation for reading value from the target.
     *
     * @param uri the name of the binding to read
     * @returns a promise that resolves to the value read.
     */
    async scriptRead(uri) {
        const binding = this.getBinding(uri);
        if (binding && binding.refresh) {
            await binding.refresh();
            return binding.getValue();
        }
        else {
            return super.scriptRead(uri);
        }
    }
}
//# sourceMappingURL=AbstractPollingDataModel.js.map