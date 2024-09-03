/**
 *  Copyright (c) 2020, 2022 Texas Instruments Incorporated
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
import { GcPromise } from '../../../gc-core-assets/lib/GcPromise';
import { AbstractDataDecoder } from './AbstractCodec';
import { bufferDataType, binaryOrBufferDataType } from './CodecDataTypes';
class FIFOCommandResponseQueue {
    constructor(name) {
        this.name = name;
        this.first = this.last = {};
    }
    addCommand(command, sequenceNumber) {
        const deferred = GcPromise.defer();
        this.last.next =
            {
                seqNo: sequenceNumber,
                command: command,
                deferred: deferred
            };
        this.last = this.last.next;
        return deferred.promise;
    }
    addResponse(response, command, sequenceNumber, isError) {
        let step = -1;
        let cur = this.first;
        let missingResponseLimit = sequenceNumber === this.last.seqNo ? 0 : -2;
        while (cur !== this.last && step < 0) {
            const prev = cur;
            cur = cur.next;
            step = sequenceNumber === undefined ? 0 : cur.seqNo - sequenceNumber;
            if (step < -100) {
                step += 255;
            }
            else if (step > 100) {
                step -= 255;
            }
            if (step < missingResponseLimit) {
                cur.deferred.reject(this.name + ' error: missing response for command sequence #' + cur.seqNo);
                this.first = cur;
                missingResponseLimit = -2;
            }
            else if (step === 0) {
                if (cur.command !== command) {
                    cur.deferred.reject(this.name + ' error: Command Mismatch.  Expected ' + cur.command + ', but received ' + command);
                }
                else if (isError) {
                    cur.deferred.reject(response);
                }
                else {
                    cur.deferred.resolve(response);
                }
                prev.next = cur.next; // remove item from list
                if (this.last === cur) {
                    this.last = prev; // move end pointer when removing the last element.
                }
            }
        }
    }
    clearAll() {
        while (this.first !== this.last) {
            this.first = this.first.next;
            this.first.deferred.reject('Skipping response from ' + this.name + ' due to reset operation');
        }
        this.first = this.last = {};
    }
    isEmpty() {
        return this.first === this.last;
    }
}
export class AbstractMessageBasedDecoder extends AbstractDataDecoder {
    /**
     * Abstract class for command/response, message based, packet codecs.  This class manages messages
     * sent and received from a controller/firmware.  This class provides helper methods for adding
     * commands to a queue waiting for responses from the controller/firmware and associating responses with
     * the appropriate command.  Messages can optionally have command id's as well as sequence numbers to aid in
     * matching up responses to commands.  If not provided, all commands are expected to have responses, and then must
     * be processed in order.  If sequence numbers are provided, commands will be matched up by sequence number, but
     * they still must be processed in order.  Out of order responses, with sequence numbers, are not supported.
     */
    constructor(name, console) {
        super(name, binaryOrBufferDataType, bufferDataType);
        this.console = console;
        this.pendingTransmissions = undefined;
        this.commandQueue = new FIFOCommandResponseQueue(name);
        // this.initAnalytics();
    }
    /**
     * Implementation of the disconnect method.  This method clears the command/response queue on disconnect.
     * If you override this method, be sure to call this base method in addition to other cleanup activities.
     */
    doDisconnect() {
        this.commandQueue.clearAll();
        this.pendingTransmissions = undefined;
        return Promise.resolve();
    }
    logPacket(name, message, buffer, len) {
        this.console.debug(function () {
            len = len || buffer.length;
            for (let i = 0; i < len; i++) {
                message = message + buffer[i].toString(16) + ', ';
            }
            return message;
        });
    }
    /**
     * Implementation of the IPacketCodec.encode() method.  This implementation logs the encoded packet using
     * GcConsole.debug() method for debug purposes before forwarding the packet to the next
     * encoder in the packet encoding chain.  The derived implementation should call this
     * method to send packets to the target.
     *
     * @param data the packet for transmission.
     */
    encode(data) {
        if (this.pendingTransmissions !== undefined) {
            this.pendingTransmissions.push(data);
        }
        else if (this.shouldPauseTransmission(data)) {
            this.console.log('pausing transmissions');
            this.pendingTransmissions = [data];
        }
        else {
            this.logPacket(this.id, 'send    ', data);
            this.targetEncoder.encode(data);
        }
    }
    /**
     * Implementation of the IPacketCodec.decode() method.  This implementation logs the incoming packet
     * to GcConsole.debug().  The derived implementation should override this method to implement the
     * necessary decoding of incoming packet, and it should call this base method first to perform the
     * logging function, before decoding the incoming and passing it along to the target decoder/model.
     *
     * @param value the packet received for decoding.
     */
    decode(data) {
        this.logPacket(this.id, 'receive ', data);
        if (this.pendingTransmissions !== undefined) {
            let pending = this.pendingTransmissions;
            this.pendingTransmissions = undefined;
            while (!this.shouldPauseTransmission(pending[0])) {
                const pendingData = pending.shift();
                pendingData && this.targetEncoder.encode(pendingData); // get ts error about undefined if using pending.shift() inline directly.
                if (pending.length <= 0) {
                    this.console.log('resuming transmissions');
                    pending = undefined;
                    break;
                }
            }
            this.pendingTransmissions = pending;
        }
        return true;
    }
    /**
     * Helper method to add a command to the command/response queue.  This method returns a promise that can be used
     * to process the response received by this method.  Only messages that require response handling need be
     * added to the command/response queue.  Messages that are sent that do not require handling may be omitted.
     *
     * @param command the specific command sent that requires a response.
     * @param sequence the sequence number of the packet that requires a response.
     * @returns promise of command's response
     */
    addCommand(command, sequenceNumber) {
        return this.commandQueue.addCommand(command, sequenceNumber);
    }
    /**
     * Helper method to process responses in command/response queue.  This method will find the appropriate
     * command in the command/response queue and reject any pending commands that did not receive a response, based
     * on the optional sequence numbers provided.
     *
     * @param response the raw response message received.
     * @param toCommand the specific command that this response is for.
     * @param sequenceNumber the sequence number of the packet received, if there is one.
     */
    addResponse(response, toCommand, sequenceNumber) {
        return this.commandQueue.addResponse(response, toCommand, sequenceNumber, false);
    }
    /**
     * Helper method to process error responses in command/response queue.  This method will find the appropriate
     * command in the command/response queue and reject it.  Any pending commands that did not receive a response,
     * based on the optional sequence numbers provided, will also be rejected.
     *
     * @param response the error message for the command.
     * @param toCommand the specific command that this error is for.
     * @param sequenceNumber the sequence number of the packet received, if there is one.
     */
    addErrorResponse(response, toCommand, sequenceNumber) {
        return this.commandQueue.addResponse(response, toCommand, sequenceNumber, true);
    }
    /**
     * Method to determine if the target is still connected.  The gc-transport-usb calls this api to
     * determine if there has been a loss of connection when it has not received any data in a while.  This method returns
     * a promise that either resolves if there are no commands in the queue expecting a response; otherwise, if returns fails, indicating that
     * there are commands that have not been responded to.  Derived classes should call the base class, and if it succeeds, they should
     * attempt to ping the target to ensure that the connection is indeed valid.  Just because there are no outstanding messages
     * does not imply the connection is good.
     *
     * @returns promise that resolves if still connected, or fails if the connection is lost with an error message.
     */
    ping() {
        if (!this.commandQueue.isEmpty()) {
            return Promise.reject('No response from ' + this.id + ' controller');
        }
        return Promise.resolve();
    }
    /**
     * Abstract method to determine if the transmission of packets should be paused or not.
     * This method is optional, and if implemented can return true to temporarily pause transmission of packets.
     * Each packet sent by the base classes encode() method will be test to see if transmission should be paused.
     * Once paused, the decode() method will test if the pending packet(s) should remain paused, or if transmission
     * can resume.  In other words, each packet sent will be tested repeatedly until this method returns false, at which point the
     * packet is transmitted to the target.
     *
     * @params packet the packet to test if it should be paused/delayed before sending to the target.
     * @returns {boolean}
     */
    shouldPauseTransmission(packet) {
        return false;
    }
    static registerFirmwareCheck(impl, name) {
        AbstractMessageBasedDecoder.firmwareChecks[name] = impl;
    }
    checkFirmware(info, behaviorControl) {
        const promises = [];
        for (const x in AbstractMessageBasedDecoder.firmwareChecks) {
            promises.push(AbstractMessageBasedDecoder.firmwareChecks[x](info, behaviorControl));
        }
        return Promise.all(promises);
    }
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    static register_crc_user(impl, interfaceName) {
        // impl (required) - provides customized logic to embed crc bytes in data, and verify crc bytes and extract data
        // impl is an object  {
        //  embed_crc_data: function(crc, arg) {
        //      return {payload: crc_embedded_payload, num_read_bytes: num_byes_to_read_include_crc}
        //  }
        //  , verify_crc_data: function(crc, arg) {
        //      return {valid: true, payload: payload_without_crc};
        //  }
        // }
        // interface_name (required) - specific interfaces that needs the given crc implementation, e.g. 'i2c'
        AbstractMessageBasedDecoder.crcUsers[interfaceName] = impl;
    }
    static getCrcUser(interfaceName) {
        return AbstractMessageBasedDecoder.crcUsers[interfaceName];
    }
}
AbstractMessageBasedDecoder.firmwareChecks = {};
// eslint-disable-next-line @typescript-eslint/no-explicit-any
AbstractMessageBasedDecoder.crcUsers = {}; // TODO (next PR cycle define crcUser type)
//# sourceMappingURL=AbstractMessageBasedDecoder.js.map