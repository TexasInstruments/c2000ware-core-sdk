import { EncoderType, bufferOrStringDataType } from '../../gc-target-configuration/lib/TargetConfiguration';
import { Events, EventType } from '../../gc-core-assets/lib/Events';

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
const API_VERSION = 1;
var DeviceAgentStreamingDataType;
(function (DeviceAgentStreamingDataType) {
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["image"] = 1] = "image";
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["audio"] = 2] = "audio";
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["time1D"] = 3] = "time1D";
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["time2D"] = 4] = "time2D";
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["time3D"] = 5] = "time3D";
    DeviceAgentStreamingDataType[DeviceAgentStreamingDataType["featureSet"] = 6] = "featureSet";
})(DeviceAgentStreamingDataType || (DeviceAgentStreamingDataType = {}));
var DeviceAgentPipeline;
(function (DeviceAgentPipeline) {
    DeviceAgentPipeline[DeviceAgentPipeline["SENSOR_DATA_ACQUISITION"] = 1] = "SENSOR_DATA_ACQUISITION";
    DeviceAgentPipeline[DeviceAgentPipeline["SENSOR_DATA_INFERENCING"] = 2] = "SENSOR_DATA_INFERENCING";
    DeviceAgentPipeline[DeviceAgentPipeline["HOST_DATA_INFERENCING"] = 3] = "HOST_DATA_INFERENCING";
    DeviceAgentPipeline[DeviceAgentPipeline["LOOPBACK"] = 4] = "LOOPBACK";
})(DeviceAgentPipeline || (DeviceAgentPipeline = {}));
const deviceAgentEncoderType = new EncoderType('device-agent');
const nullDeviceAgentEncoder = new (class extends Events {
    constructor() {
        super(...arguments);
        this.encoderInputType = deviceAgentEncoderType;
        this.encoderOutputType = bufferOrStringDataType;
        this.id = 'null';
    }
    getCapabilities() {
        throw new Error('Method not implemented.');
    }
    listSensors() {
        throw new Error('Method not implemented.');
    }
    startStreaming() {
        throw new Error('Method not implemented.');
    }
    stopStreaming() {
        throw new Error('Method not implemented.');
    }
    configurePipeline() {
        throw new Error('Method not implemented.');
    }
    listModels() {
        throw new Error('Method not implemented.');
    }
    uploadModel(model, data) {
        throw new Error('Method not implemented.');
    }
    removeModel(name) {
        throw new Error('Method not implemented.');
    }
    setProperty(name, value) {
        throw new Error('Method not implemented.');
    }
    getProperty(name) {
        return Promise.resolve(undefined);
    }
    encode(data) {
    }
    addChildDecoder(child) {
    }
    dispose() {
    }
});
const sensorErrorEventType = new EventType('sensorError');
const inferenceLogEventType = new EventType('inferenceLog');
const inferenceValuesEventType = new EventType('inferenceValues');
const multipartStreamingEventType = new EventType('multipartStreaming');

export { API_VERSION, DeviceAgentPipeline, DeviceAgentStreamingDataType, deviceAgentEncoderType, inferenceLogEventType, inferenceValuesEventType, multipartStreamingEventType, nullDeviceAgentEncoder, sensorErrorEventType };
//# sourceMappingURL=DeviceAgentModel.js.map
