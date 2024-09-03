/**
 *  Copyright (c) 2020, Texas Instruments Incorporated
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
// TODO Next cycle to discuss the need of Pin Model - See dialogue below.
// export interface IPinEncoder extends IEncoder<INoopDecoder, IPinEncoder> {
//     read(pinInfo: IPin): Promise<bindValueType>;
//     write(gpioInfo: IPin, data: number): Promise<void>;
// }
/*
Paul Gingrich comment

I've been thinking about the PinModel lately. What if we put the polling inside the GPIO codec, so that the pin model is no longer a polling model but a push model (where values changes are pushed from codec to model). Then we can use a standard streaming model to represent pins. So for example,
<gc-model-streaming id="pin"> and we push an object map of pin name to value.
{ GPIO1: true, GPIO2: false }, or individually { GPIO1: true } followed by { GPIO2: false }. It would simplify the model at the expense of the codec, and we would lose some of the benefits of the AbstractAsyncBindValue implementation, but if we assume that all GPIO, that are configured as inputs, should be using the interrupt model (push) anyway, and output gpio pins do not need polling. What do you think?

    Winnie Lai asked

    When GC app wants to trigger a write request to write a value to a pin, it uses the particular streaming model instance, identified by the id pinA, to say streamingModel.sendValue(...). That is, it interfaces with the streaming model directly. Is this correct?

    When GC app wants to trigger a read request to read value of a pin, is it going to interface the GPIO codec directly?


    Paul's reply
    Not exactly. The send/transmit side is correct, but think of the streaming model as a push model. So when the GPIO pin changes the streaming model gets an update with { pinA=true or false }. The assumption here is that an interrupt will be used to push the GPIO pin changes from the target to the host. If this is not the case, I was suggesting putting the polling (window.interval() for example) directly in the codec implementation and pushing the pin value through the model (rather than use a dedicated polling PinModel). In this mode, there could be a single polling function for all the GPIO pins, and push all the values through the model at the same time.
*/
//# sourceMappingURL=PinModel.js.map
