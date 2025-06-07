import { GcUtils } from '../../gc-core-assets/lib/GcUtils';
import { AbstractDataDecoder, bufferOrStringDataType, stringDataType } from '../../gc-target-configuration/lib/TargetConfiguration';

/**
 *  Copyright (c) 2023, 2024 Texas Instruments Incorporated
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
 */
const UserLoginName = 'root';
const UserLoginPassword = 'root';
/**
  * Codec to parse ssh or linux terminal output and send commands to login, auto detect IP address, and start the device agent program for edgeai
  * linux based starter kits.
  */
class DeviceAgentTerminalCodec extends AbstractDataDecoder {
    constructor(params = {}) {
        super(params.id || 'deviceAgentTerminal', bufferOrStringDataType, stringDataType);
        this.params = params;
        this.agentIsRunning = false;
        this.buffer = '';
        this._deviceName = '';
        this._ipAddress = '';
    }
    async onConnect(transport) {
        this.buffer = '';
        this._ipAddress = '';
        this._deviceName = '';
        this.agentIsRunning = false;
        let result = 'timeout';
        // attempt five <cr> to get a prompt.
        for (let i = 1; i < 5 && result !== 'prompt'; i++) {
            this.sendCommand(); // send carriage return
            result = await this.waitForPrompt(1000);
            if (result === 'missing') {
                this.stopAgent();
                result = await this.waitForPrompt(2000);
            }
            // if the prompt is login, then enter password, and wait for 10s to get result
            if (result === 'login') {
                this.sendCommand(UserLoginPassword);
                result = await this.waitForPrompt(10000);
            }
        }
        if (result === 'prompt') {
            this.sendCommand('ifconfig');
            result = await this.waitForPrompt(3000);
            if (this.deviceIp && result === 'prompt') {
                try {
                    transport.addProgressMessage(`Starting device agent on ${this.deviceName} ...`);
                    await this.startAgent();
                }
                catch (e) {
                    transport.addErrorMessage(`Failed to start device agent on ${this.deviceName}.`, 'This application needs to run a device agent on the target board.  Please ensure you are using the latest SDK for you device.');
                    transport.disconnect();
                }
            }
            else {
                transport.addErrorMessage(`Failed to acquire the IP address of ${this.deviceName} board.`, 'Please ensure that you have plugging in an ethernet cable on the same local network as your computer.');
                transport.disconnect();
            }
        }
        else {
            throw new Error('Failed to login to remote target.');
        }
    }
    async onDisconnect() {
        if (this.agentIsRunning) {
            this.stopAgent();
            await this.waitForPrompt(100);
            this._deviceName = '';
            this._ipAddress = '';
        }
    }
    /**
      * Sends terminal commands to the target.
      *
      * @param command command to be send to the next encoder
      */
    sendCommand(command) {
        this.targetEncoder.encode((command || '') + '\n');
    }
    /**
      * Decodes data and send it to the next decoder.
      *
      * @param {bufferOrStringDataType} data data received from the previous decoder
      */
    decode(data) {
        let message;
        try {
            message = typeof data === 'string' ? data : String.fromCharCode(...data);
        }
        catch (e) {
            return Error('Error converting buffer to string.');
        }
        try {
            this.buffer += message;
        }
        catch (e) {
            return Error(`Received bad JSON data string: ${message}.`);
        }
        let pos = this.buffer.lastIndexOf('\neth0: ');
        if (pos > 0) {
            let endPos = this.buffer.indexOf('ether ', pos);
            pos = this.buffer.indexOf(' inet ', pos);
            if (pos > 0 && pos < endPos) {
                endPos = this.buffer.indexOf(' netmask ', pos);
                if (pos > 0 && endPos > 0) {
                    this._ipAddress = this.buffer.substring(pos + ' inet '.length, endPos).trim();
                }
            }
        }
        const login = this.buffer.endsWith('login: ');
        if (login) {
            this._ipAddress = '';
        }
        return true;
    }
    clearLog() {
        this.buffer = '';
    }
    async waitForPrompt(timeout) {
        const waitTm = 200;
        for (let i = Math.round(timeout / waitTm); i-- > 0;) {
            // wait for data to settle
            const count = this.buffer.length;
            await GcUtils.delay(waitTm);
            // if new data
            const diff = this.buffer.length - count;
            if (diff > 0) {
                let line = this.buffer.trim();
                if (line === '') {
                    return 'missing';
                }
                // get last line of output
                const pos = line.lastIndexOf('\n');
                if (pos > 0) {
                    line = line.substring(pos + 1);
                }
                // test for login
                if (line.endsWith('login:')) {
                    return 'login';
                }
                if (line.startsWith(`${UserLoginName}@`) && line.endsWith('#')) {
                    this._deviceName = line.substring(`${UserLoginName}@`.length);
                    this._deviceName = this._deviceName.split(/[-x:]/)[0].toUpperCase();
                    return 'prompt';
                }
                if (line.indexOf('Application startup complete.') >= 0) {
                    return 'running';
                }
            }
        }
        if (this.buffer.trim() === '') {
            return 'missing';
        }
        return 'timeout';
    }
    async startAgent() {
        this.sendCommand('cd /opt/edgeai-studio-agent/src');
        await this.waitForPrompt(200);
        this.sendCommand('python3 device_agent.py');
        if ('running' !== await this.waitForPrompt(15000)) {
            throw new Error('Failed to start the device agent.');
        }
        this.agentIsRunning = true;
    }
    stopAgent() {
        this.agentIsRunning = false;
        this.sendCommand(String.fromCharCode(3));
    }
    get deviceIp() {
        return this._ipAddress;
    }
    get deviceName() {
        return this._deviceName;
    }
}
// Create a new instance of the codec
new DeviceAgentTerminalCodec();

export { DeviceAgentTerminalCodec };
//# sourceMappingURL=DeviceAgentTerminalCodec.js.map
