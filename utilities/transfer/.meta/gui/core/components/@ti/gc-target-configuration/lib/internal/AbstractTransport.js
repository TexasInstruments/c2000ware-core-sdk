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
import { codecRegistry } from './CodecRegistry';
import { TRANSPORT_STATE, connectedStateChangedEventType, abortEventType } from './ITransport';
import { AbstractConnectionLogger, capitalize } from './AbstractConnectionLogger';
/**
 * Base class for all transports, and the connection manager, to manage connected, connecting, disconnected, and disconnecting states.
 */
export class AbstractTransport extends AbstractConnectionLogger {
    constructor() {
        super(...arguments);
        this.disconnectPromise = Promise.resolve();
        this._state = TRANSPORT_STATE.DISCONNECTED;
        this._connectionDescription = '';
    }
    get isXdsTransport() {
        return false;
    }
    /**
     * current connection state of the transport.
     */
    get state() {
        return this._state;
    }
    get isConnected() {
        return this.state === TRANSPORT_STATE.CONNECTED;
    }
    /**
     * True if the transport is in the process of connecting to the target.
     */
    get isConnecting() {
        return this.state === TRANSPORT_STATE.CONNECTING;
    }
    get canConnect() {
        return this.isDisconnected || this.isDisconnecting;
    }
    get isDisconnected() {
        return this.state === TRANSPORT_STATE.DISCONNECTED;
    }
    /**
     * True if the transport is in the process of disconnecting from the target.
     */
    get isDisconnecting() {
        return this.state === TRANSPORT_STATE.DISCONNECTING;
    }
    get canDisconnect() {
        return this.isConnected || this.isConnecting;
    }
    get isPartiallyConnected() {
        return this.isConnected && codecRegistry.isPartiallyConnected(this.id);
    }
    assertStillConnecting() {
        if (this.isDisconnecting || this.isDisconnected) {
            throw Error('Connecting to target was aborted by the user.');
        }
    }
    setState(newState, didPartiallyConnectedStateChange = false) {
        if (this._state !== newState || didPartiallyConnectedStateChange) {
            if (this.canDisconnect && newState === TRANSPORT_STATE.CONNECTED) {
                this._state = newState; // state needs to be updated before calling isPartiallyConnected
                this.addProgressMessage(`Hardware ${this.isPartiallyConnected ? 'partially ' : ''}connected.`);
            }
            else if (this.isDisconnecting && newState === TRANSPORT_STATE.DISCONNECTED) {
                this.addProgressMessage('Hardware not connected.');
            }
            this._state = newState;
            this.fireEvent(connectedStateChangedEventType, { newState: this.state, transport: this });
            this.console.debug(`${capitalize(this.toString())} state changed to ${newState}.`);
        }
    }
    disconnect() {
        if (this.canDisconnect) {
            this.setState(TRANSPORT_STATE.DISCONNECTING);
            // eslint-disable-next-line no-async-promise-executor
            this.disconnectPromise = new Promise(async (resolve, reject) => {
                try {
                    await this.doAbort();
                    await this.doDisconnect();
                    if (this.state === TRANSPORT_STATE.DISCONNECTING) {
                        this.setState(TRANSPORT_STATE.DISCONNECTED);
                    }
                    resolve();
                }
                catch (e) {
                    reject(e);
                }
            });
        }
        return this.disconnectPromise;
    }
    connect(failedDevicesList = []) {
        if (this.canConnect) {
            // eslint-disable-next-line no-async-promise-executor
            this.connectPromise = this.connectPromise || new Promise(async (resolve, reject) => {
                try {
                    if (this.isDisconnecting) {
                        this.console.debug('Waiting for disconnect to complete before connecting.');
                    }
                    await this.disconnectPromise;
                    // clear logger every time we connect, but not on disconnect to preserve last error/warning message.
                    this.clearProgressMessage();
                    this.setConnectionDescription();
                    this.setState(TRANSPORT_STATE.CONNECTING);
                    await this.doConnect(failedDevicesList);
                    if (this.isConnecting) {
                        this.setState(TRANSPORT_STATE.CONNECTED);
                    }
                    resolve();
                }
                catch (e) {
                    if (this.isConnecting) {
                        let errMsg = e.message || e.toString();
                        if (errMsg.indexOf('failed to connect') < 0) {
                            errMsg = 'Failed to connect: ' + errMsg;
                        }
                        this.addErrorMessage(errMsg);
                        this.disconnect();
                    }
                    reject(e);
                }
                finally {
                    this.connectPromise = undefined;
                }
            });
        }
        return this.connectPromise || Promise.resolve();
    }
    async doConnect(failedDevicesList = []) {
        this.addProgressMessage('Connecting to target ...');
        await codecRegistry.connect(this.id, this, failedDevicesList);
    }
    doDisconnect() {
        return codecRegistry.disconnect(this.id, this);
    }
    async doAbort() {
        if (this.connectPromise) {
            this.console.debug('Aborting connection.');
            this.fireEvent(abortEventType, {});
            try {
                await (this.connectPromise || Promise.resolve());
            }
            catch (_a) {
                // not looking for errors here, just trying to serialize operations.
            }
        }
    }
    get connectionDescription() {
        return this._connectionDescription;
    }
    setConnectionDescription(description = '') {
        if (this._connectionDescription !== description) {
            this._connectionDescription = description;
            if (description) {
                this.addProgressMessage(`Connecting to ${description} ...`);
            }
        }
    }
    get optional() {
        return this.params.optional;
    }
    get deviceId() {
        return this.params.deviceId;
    }
    toString() {
        return `transport id="${this.id}"`;
    }
}
//# sourceMappingURL=AbstractTransport.js.map