/*
 *  Created on: July 16, 2024
 */

//#############################################################################
//
// FILE:   feature_extract.c
//
//!
//! This contains definition of core API functions required to feature
//! extraction operations
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************

#include "feature_extract_priv.h"


//************Variable Defines*************//

//*** for FFT ***
//extern const float fftWindow[frame_size>>1] = HANN1024;
//const float fftWindow[frame_size>>1] = HANN1024;
const float fftWindow[] = HANN1024;


//*** for Feature_extraction ***
#ifdef NPU_VERIFICATION
extern float model_input_top_float[];
#endif



//*****************************************************************************
// Function Prototyping
//*****************************************************************************
void run_Pre_processing(uint16_t *prerecorded_dataPtr, float *Window_outputPtr, float *FFT_inputPtr, float *FFT_outputPtr, float *MagbuffPtr, float *binOutPtr);
//void run_Windowing(uint16_t *prerecorded_dataPtr, float *Window_outputPtr);
void run_Windowing(Feature_Extract_State_Params *state_params);
//void run_CFFT(float *FFT_inputPtr, float *FFT_outputPtr);
void run_CFFT(Feature_Extract_State_Params *state_params);
//void run_RFFT(float *FFT_inputPtr, float *FFT_outputPtr, float *MagbuffPtr);
void run_RFFT(Feature_Extract_State_Params *state_params);
//void run_BIN(float *MagbuffPtr, float *binOutPtr);
void run_BIN(Feature_Extract_State_Params *state_params);
//void batch_normalization(float *pIn1, uint16_t ch, uint16_t wl, uint16_t hl, int8_t *pOut1);
void batch_normalization(Feature_Extract_State_Params *state_params);
//void batch_normalization_1d(float *pIn2, uint16_t inLen, int8_t *pOut2);
void batch_normalization_1d(Feature_Extract_State_Params *state_params);
//void concat_multi_frames(int8_t *pIn3, int8_t *pInNew);
void concat_multi_frames(Feature_Extract_State_Params *state_params);
//void run_data_reframe(float *FFT_inputPtr);
void run_data_reframe(Feature_Extract_State_Params *state_params);
//void run_frame_rearrange(float *NNinput_testdataPtr);
void run_frame_rearrange(Feature_Extract_State_Params *state_params);





//*****************************************************************************
// Function definitions
//*****************************************************************************

//=================================================================================================
// Apply the FFT-Windowing to the input data, here the input data is a pre-record ADC data vector
// In real applications, users need to insure the data is streaming continuously
// A pair of ping-pong buffer, each has the size of one FFT frame, is recommended.
//=================================================================================================
//void run_Windowing(uint16_t *prerecorded_dataPtr, float *Window_outputPtr)
void run_Windowing(Feature_Extract_State_Params *state_params)
{
    int ii;
    float *prerecorded_dataPtr = state_params->prerecorded_dataPtr;
    float *Window_outputPtr = state_params->Window_outputPtr;
    uint16_t frame_size1 = state_params->init_params.size_of_frame;

    for (ii = 0; ii < (frame_size1/2); ii++)
    {
        Window_outputPtr[ii] = (float) fftWindow[ii]*prerecorded_dataPtr[ii];
    }
    for (ii = (frame_size1/2); ii < frame_size1; ii++)
    {
        Window_outputPtr[ii] = (float) fftWindow[(frame_size1-1)-ii]*prerecorded_dataPtr[ii];
    }
}


//void run_CFFT(float *FFT_inputPtr, float *FFT_outputPtr)
void run_CFFT(Feature_Extract_State_Params *state_params)
{
    float *p_temp;
    float *FFT_inputPtr = state_params->FFT_inputPtr;
    float *FFT_outputPtr = state_params->FFT_outputPtr;
    uint16_t frame_size1 = state_params->init_params.size_of_frame;
    uint16_t fft_stages1 = state_params->init_params.fft_stage_num;
    uint16_t fft_size1 = state_params->init_params.fft_size;
    //int ii;

    // Configure the FFT object
    CFFT_f32_setInputPtr(state_params->hnd_cfft, FFT_inputPtr);
    CFFT_f32_setOutputPtr(state_params->hnd_cfft, FFT_outputPtr);
    CFFT_f32_setTwiddlesPtr(state_params->hnd_cfft, CFFT_f32_twiddleFactors);
    CFFT_f32_setStages(state_params->hnd_cfft, (fft_stages1 - 1U));
    CFFT_f32_setFFTSize(state_params->hnd_cfft, (fft_size1 >> 1));

    // Run the N/2 point complex FFT
    // NOTE: Can only use the 't' version of the CFFT with the
    // pack and unpack functions
    CFFT_f32t(state_params->hnd_cfft);                   // Calculate FFT

    // Run the unpack function on the N/2 point complex spectrum
    // to get the N/2+1 point complex spectrum of the N point real
    // data. The unpack function will generate the complex
    // spectrum from F(0) to F(N/2).
    // The pointer, p_currOutput points to the complex spectrum
    // of the real N-point input data.
    CFFT_f32_unpack(state_params->hnd_cfft);

    //
    // switch the CurrentInPtr and CurrentOutPtr pointers
    //
    //here check the buffer "test_output" for FFT results
    p_temp = CFFT_f32_getCurrInputPtr(state_params->hnd_cfft);
    CFFT_f32_setCurrInputPtr(state_params->hnd_cfft, CFFT_f32_getCurrOutputPtr(state_params->hnd_cfft));
    CFFT_f32_setCurrOutputPtr(state_params->hnd_cfft, p_temp);

    // Run the magnitude function
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project
                           // properties
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag_TMU0(state_params->hnd_cfft);
#else
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag(state_params->hnd_cfft);
#endif
    //
    // NOTE: the N/2 point is not calculated by the mag functions;
    // we dont need to calculate |F(N/2)| as its real, so we just copy
    // it over
    //
    FFT_inputPtr[frame_size1/2] = FFT_outputPtr[frame_size1];

    //Now the buffer "test_input" has the FFT magnitude results
}


//void run_RFFT(float *FFT_inputPtr, float *FFT_outputPtr, float *MagbuffPtr)
void run_RFFT(Feature_Extract_State_Params *state_params)
{

    float *FFT_inputPtr = state_params->FFT_inputPtr;
    float *FFT_outputPtr = state_params->FFT_outputPtr;
    float *MagbuffPtr = state_params->MagbuffPtr;
    uint16_t fft_stages1 = state_params->init_params.fft_stage_num;
    uint16_t fft_size1 = state_params->init_params.fft_size;

    // Configure the FFT object
    RFFT_f32_setInputPtr(state_params->hnd_rfft, FFT_inputPtr);                       //Input buffer
    RFFT_f32_setOutputPtr(state_params->hnd_rfft, FFT_outputPtr);       //Output buffer
    RFFT_f32_setMagnitudePtr(state_params->hnd_rfft, MagbuffPtr);   //Magnitude buffer (no fft_size/2 normalization and no 2*abs())
    RFFT_f32_setTwiddlesPtr(state_params->hnd_rfft, FPU32RFFTtwiddleFactors);
    RFFT_f32_setStages(state_params->hnd_rfft, fft_stages1);
    RFFT_f32_setFFTSize(state_params->hnd_rfft, fft_size1);

    RFFT_f32(state_params->hnd_rfft);                     //Calculate real FFT

    #ifdef __TMS320C28XX_TMU__
        RFFT_f32_mag_TMU0(state_params->hnd_rfft);
    #else
        RFFT_f32_mag(state_params->hnd_rfft);
    #endif

}

//==================================================================================
// biasing, scaling and shifting the feature data from float-point to 8-bit integer
//==================================================================================
int8_t model_input_conversion(float model_input_float)
{
    float temp_add_bias;
   // biasing, scaling and shifting to convert floating model input to fixed point model input
    temp_add_bias = model_input_float + tvmgen_default_bias_data[0];
    int32_t scale = (int32_t)floorf(temp_add_bias * tvmgen_default_scale_data[0]);
    int32_t shift = scale >> tvmgen_default_shift_data[0];
    int8_t max_val = shift > 127 ? 127 : shift;
    int8_t min_val = max_val < -128 ? -128 : max_val;
    return min_val;
}

//===========================================================================================
// extracting features from FFT results and format them before feeding to AI detection model
//===========================================================================================
//void run_data_reframe(float *FFT_inputPtr)
void run_data_reframe(Feature_Extract_State_Params *state_params)
{
    //float *FFT_inputPtr = state_params->FFT_inputPtr;
    float *data_reframe_inputPtr = state_params->data_reframe_inputPtr;
    int8_t *data_reframe_outputPtr = state_params->data_reframe_outputPtr;
    uint16_t minimum_bin_size = state_params->init_params.min_fft_bin_size;
    uint16_t fft_bin_size1 = state_params->init_params.fft_bin_size;
    uint16_t feature_size_per_frame1 = state_params->init_params.feature_size_per_frame;
    uint16_t num_frame_concat1 = state_params->init_params.num_frame_concat;
    uint16_t frame_size1 = state_params->init_params.size_of_frame;        //Added without check

    //int8_t model_input_top[feature_size_per_frame1];
    #ifdef NPU_VERIFICATION
    //float model_input_top_float[feature_size_per_frame1];
    const int feature_size_total = feature_size_per_frame1 * num_frame_concat1;
    for (int idx = 0; idx < feature_size_total; idx++)
    {
        model_input_top[idx] = model_input_conversion(model_input_top_float[idx]);
    }
#else
    // derived parameters
    const int feature_shift_start_idx = feature_size_per_frame1;
    const int feature_shift_stop_idx = feature_size_per_frame1*num_frame_concat1 - feature_shift_start_idx;
    volatile int idx = 0;
    volatile int idx_bin = 0;

    float temp_buf_sum, temp_model_input_float;
    float32_t exp = 2.71828183f;
    float fft_offset = 0;
    if(state_params->init_params.log_base != (float)exp)
    {
        fft_offset = (state_params->init_params.log_multiply)*(logf(frame_size1)/logf(state_params->init_params.log_base));
    }
    else
    {
        fft_offset = (state_params->init_params.log_multiply)*logf(frame_size1);
    }
     //input model buffer shifting by feature_size_per_frame units
    for (idx = 0; idx < feature_shift_stop_idx; idx++)
    {
        data_reframe_outputPtr[idx] = data_reframe_outputPtr[idx+feature_shift_start_idx];
    }
    //update model input for current frame
    for (idx = 0; idx < feature_shift_start_idx; idx++)
    {
        temp_buf_sum = 0;
        for (idx_bin = 0; idx_bin < fft_bin_size1; idx_bin++)
        {   // FFT binning
            temp_buf_sum = temp_buf_sum + data_reframe_inputPtr[idx*fft_bin_size1 + minimum_bin_size + idx_bin];
        }
        if(state_params->init_params.log_base != (float)exp)
        {
            temp_model_input_float = (state_params->init_params.log_multiply)*(logf(temp_buf_sum)/logf(state_params->init_params.log_base)) - fft_offset; // Calculate FFT/N in logarithm
        }
        else
        {
            temp_model_input_float = (state_params->init_params.log_multiply)*logf(temp_buf_sum) - fft_offset; // Calculate FFT/N in logarithm
        }
        data_reframe_outputPtr[idx+feature_shift_stop_idx] = model_input_conversion(temp_model_input_float);
    }
#endif
}

void run_frame_rearrange(Feature_Extract_State_Params *state_params)
{
    float *NNinput_testdataPt = state_params->rearrangedataPtr;
    uint16_t feature_size_per_frame1 = state_params->init_params.feature_size_per_frame;
    uint16_t num_frame_concat1 = state_params->init_params.num_frame_concat;

    uint16_t j;

    for(j=num_frame_concat1-1; j>=1; j--)
    {
       memcpy(&NNinput_testdataPt[j*feature_size_per_frame1], &NNinput_testdataPt[(j-1)*feature_size_per_frame1], feature_size_per_frame1*2); //*2 is needed due to float (2*16b)
    }
}


/*****************************************************************************************/
// *MagbuffPtr: pointer to the FFT magnitude result
// inLen: length of the frequency points (include DC)
// *pOut: pointer to output
// outLen: number of bins
// bDC: set DC component to 0 if bDC=1
// Difference with python processing, always discard the last remaining points, while python script
// takes the average to the end.
/*****************************************************************************************/
//void run_BIN(float *MagbuffPtr, float *binOutPtr)
void run_BIN(Feature_Extract_State_Params *state_params)
{
    float *MagbuffPtr = state_params->MagbuffPtr;
    float *binOutPtr = state_params->binOutPtr;
    uint16_t minimum_bin_size = state_params->init_params.min_fft_bin_size;
    uint16_t feature_size_per_frame1 = state_params->init_params.feature_size_per_frame;
    uint16_t total_feature_size_per_frame1 = state_params->init_params.total_feature_size_per_frame;

    uint16_t nSamples, inLen;
    uint16_t i, m, i1, i2;
    float tmp;

    MagbuffPtr = MagbuffPtr + minimum_bin_size; // update pointer to skip the first few bin; for DC remove, set min_bin=1
    inLen = (state_params->init_params.fft_size>>1)+1;
    nSamples = (inLen - minimum_bin_size)/feature_size_per_frame1;

    for(i=0; i<feature_size_per_frame1; i++)
    {
        tmp = 0;
        i1 = i*nSamples;
        i2 = i1 + nSamples;
        for(m=i1; m<i2; m++)
        {
            tmp = tmp + MagbuffPtr[m];
        }
        //binOutPtr[i] = (float)tmp; // reduce 1 division
        binOutPtr[i] = ((float)tmp/nSamples);
    }

    // Calculate 20*log10(x)
    //#ifdef Log_Base10
    int j=0;
    for(j=0; j<total_feature_size_per_frame1; j++)
    {
        binOutPtr[j] = (state_params->init_params.log_multiply)*(logf(binOutPtr[j])/logf(state_params->init_params.log_base));
    }
    //#endif
}


//void batch_normalization(float *pIn1, uint16_t ch, uint16_t wl, uint16_t hl, int8_t *pOut1)
void batch_normalization(Feature_Extract_State_Params *state_params)
{
    float *pIn1 = state_params->batchnormInPtr;
    uint16_t ch = state_params->init_params.num_input_channels;
    uint16_t wl = state_params->init_params.output_feature_width;
    uint16_t hl = state_params->init_params.output_feature_height;
    int8_t *pOut1 = state_params->batchnormOutPtr;

    uint16_t index=0;
    //uint16_t ch,wl,hl;
    int c,w,h=0;

    int tvmgen_shift_data_length = state_params->init_params.output_convert_shift_len;
    int tvmgen_shift_data_offset = tvmgen_shift_data_length > 1 ? 1 : 0;

    for (c=0; c<ch; c++)
    {
        for (w=0; w<wl; w++)
        {
            for (h=0; h<hl; h++)
            {
                float bias = *(pIn1+index) + state_params->init_params.output_convert_bias[c];
                int32_t scale = (int32_t)floorf(bias * state_params->init_params.output_convert_scale[c]);
                int32_t shift = scale >> state_params->init_params.output_convert_shift[c*tvmgen_shift_data_offset];
                int8_t max_val = shift > 127 ? 127 : shift;
                int8_t min_val = max_val < -128 ? -128 : max_val;
                *(pOut1+index) = min_val;
                index++;
            }
        }
    }
}

//void batch_normalization_1d(float *pIn2, uint16_t inLen, int8_t *pOut2)
void batch_normalization_1d(Feature_Extract_State_Params *state_params)
{
    float *pIn2 = state_params->batchnormInPtr;
    uint16_t inLen = state_params->init_params.num_input_channels;
    int8_t *pOut2 = state_params->batchnormOutPtr;
    int i=0;
    for (i=0; i<inLen; i++)
    {
        float bias = pIn2[i] + tvmgen_default_bias_data[0];
        int32_t scale = (int32_t)floorf(bias * tvmgen_default_scale_data[0]);
        int32_t shift = scale >> tvmgen_default_shift_data[0];
        int8_t max_val = shift > 127 ? 127 : shift;
        int8_t min_val = max_val < -128 ? -128 : max_val;
        pOut2[i] = min_val;
    }
}

//void concat_multi_frames(int8_t *pIn3, int8_t *pInNew)
void concat_multi_frames(Feature_Extract_State_Params *state_params)
{
    int8_t *pIn3 = state_params->concatframeInPtr;
    int8_t *pInNew = state_params->concatframeOutPtr;
    uint16_t feature_size_per_frame1 = state_params->init_params.feature_size_per_frame;
    uint16_t num_frame_concat1 = state_params->init_params.num_frame_concat;
    // Shift frames
    uint16_t i;
    for(i=0; i<(num_frame_concat1-1); i++)
    {
        memcpy(&pIn3[i*feature_size_per_frame1], &pIn3[(i+1)*feature_size_per_frame1], feature_size_per_frame1);
    }

    // Insert new frames
    memcpy(&pIn3[(num_frame_concat1-1)*feature_size_per_frame1], &pInNew[0], feature_size_per_frame1);
}




//******************************************************************
//Main interface
//******************************************************************
int alloc_feature_extract(Feature_Extract_Init_Params* init_params, Feature_Extract_Alloc_Params* alloc_params)
{
    alloc_params->handle_size = sizeof(Feature_Extract_State_Params);
    alloc_params->scratch_size = init_params->fft_size * 4 * sizeof(float);
    return 1;
}


int init_feature_extract(Feature_Extract_Init_Params* init_params, Feature_Extract_Handle_Params *handle_params)
{
    Feature_Extract_State_Params *state_params = (Feature_Extract_State_Params*)handle_params;

    state_params->init_params = *init_params;
    state_params->hnd_cfft = &state_params->cfft;
    state_params->hnd_rfft = &state_params->rfft;
    return 1;
}


int run_feature_extract(Feature_Extract_Handle_Params *handle_params, void* input_buffer, void* output_buffer, void* scratch_buffer)
{
    Feature_Extract_State_Params *state_params = (Feature_Extract_State_Params*)handle_params;

    float* input_ptr = (float*)input_buffer;
    int8_t *output_ptr = (int8_t*)output_buffer;
    float *xyz_buff = (float*)scratch_buffer; //[fft_size*3];
    float *vib_a = &xyz_buff[0];
    float *vib_b = &xyz_buff[state_params->init_params.fft_size];
    float *vib_c = &xyz_buff[(state_params->init_params.fft_size)*2];

    memcpy(vib_a, &input_ptr[0], (state_params->init_params.fft_size)*sizeof(float));
    memcpy(vib_b, &input_ptr[state_params->init_params.fft_size], (state_params->init_params.fft_size)*sizeof(float));
    memcpy(vib_c, &input_ptr[(state_params->init_params.fft_size)*2], (state_params->init_params.fft_size)*sizeof(float));


    if(state_params->init_params.type == FEATURE_EXTRACT_RAW) {

        // compute dc
        int num_channel, k, p = 0;

        for(num_channel=0; num_channel<(state_params->init_params.num_input_channels); num_channel++)
        {
            float acc = 0.0, dc = 0.0;
            for(k=0; k<state_params->init_params.fft_size; k++)
            {
                //vib_acc[num_channel] = vib_acc[num_channel] + (int32_t)xyz_buff[k+(num_channel*(state_params->init_params.fft_size))];
                acc = acc + xyz_buff[k+(num_channel*(state_params->init_params.fft_size))];
            }
            dc = acc / state_params->init_params.fft_size;

            for(p=0; p<state_params->init_params.fft_size; p++)
            {
                xyz_buff[p+(num_channel*(state_params->init_params.fft_size))] = xyz_buff[p+(num_channel*(state_params->init_params.fft_size))] - dc;
            }
        }

        //feature_extract_setbatchnorm_inPtr(state_params, vib_a);
        feature_extract_setbatchnorm_inPtr(state_params, &xyz_buff[0]);
        feature_extract_setbatchnorm_outPtr(state_params, output_ptr);
        batch_normalization(state_params);

    } else if(state_params->init_params.type == FEATURE_EXTRACT_FFT) {

        float *fft_output = &xyz_buff[(state_params->init_params.fft_size)*3];
        float *RFFTmagBuff = &xyz_buff[(state_params->init_params.fft_size)*5];
        float *Temp_resultBuff = &xyz_buff[(state_params->init_params.fft_size)*6];

        int num_channel = 0;

        for(num_channel=0; num_channel<(state_params->init_params.num_input_channels); num_channel++)
        {
            feature_extract_setFFT_inputPtr(state_params, &xyz_buff[num_channel*(state_params->init_params.fft_size)]);
            feature_extract_setFFT_outputPtr(state_params, fft_output);
            feature_extract_setMagbuffPtr(state_params, RFFTmagBuff);

            run_RFFT(state_params);

            int i1 = 0;

            for(i1=0;i1<state_params->init_params.feature_size_per_frame;i1++)
            {
                Temp_resultBuff[i1+(num_channel*(state_params->init_params.feature_size_per_frame))] = (state_params->init_params.log_multiply)*(logf(RFFTmagBuff[i1+1])/logf(state_params->init_params.log_base));
            }
        }

        feature_extract_setbatchnorm_inPtr(state_params, Temp_resultBuff);
        feature_extract_setbatchnorm_outPtr(state_params, output_ptr);

        batch_normalization(state_params);

    } else if(state_params->init_params.type == FEATURE_EXTRACT_FFT_BIN) {

        float *fft_output = &xyz_buff[(state_params->init_params.fft_size)*3];
        float *RFFTmagBuff = &xyz_buff[(state_params->init_params.fft_size)*5];
        float *binResult = &xyz_buff[(state_params->init_params.fft_size)*6];
        int8_t *binResultBN = (int8_t*)&xyz_buff[(state_params->init_params.fft_size)*7];

        //Step 3: Do preprocessing on last frame for each column and append it with test data

        if(state_params->init_params.num_input_channels == 1)             // For 1D
        {
            feature_extract_setFFT_inputPtr(state_params, vib_a);
            feature_extract_setFFT_outputPtr(state_params, fft_output);
            feature_extract_setMagbuffPtr(state_params, RFFTmagBuff);
            feature_extract_setbinOutPtr(state_params, &binResult[0]);

            run_RFFT(state_params);
            run_BIN(state_params);


            feature_extract_setbatchnorm_inPtr(state_params, binResult);
            feature_extract_setbatchnorm_outPtr(state_params, binResultBN);
            feature_extract_setchannellength(state_params, 1);
            feature_extract_setchannelwidth(state_params, 1);
            feature_extract_setchannelheight(state_params, state_params->init_params.total_feature_size_per_frame);

            batch_normalization(state_params);

            int ii=0;

            for(ii=0; ii<(state_params->init_params.num_input_channels); ii++)
            {
                feature_extract_setconcatframe_inPtr(state_params, &output_ptr[ii*state_params->init_params.output_feature_size]);
                feature_extract_setconcatframe_outPtr(state_params, &binResultBN[ii*(state_params->init_params.feature_size_per_frame)]);

                concat_multi_frames(state_params);
            }

        }
        else           // For 2D1
        {
            int num_channel = 0;

            for(num_channel=0; num_channel<(state_params->init_params.num_input_channels); num_channel++)
            {
                feature_extract_setFFT_inputPtr(state_params, &xyz_buff[num_channel*(state_params->init_params.fft_size)]);
                feature_extract_setFFT_outputPtr(state_params, fft_output);
                feature_extract_setMagbuffPtr(state_params, RFFTmagBuff);
                feature_extract_setbinOutPtr(state_params, &binResult[num_channel*(state_params->init_params.feature_size_per_frame)]);

                run_RFFT(state_params);
                run_BIN(state_params);
            }


            feature_extract_setbatchnorm_inPtr(state_params, binResult);
            feature_extract_setbatchnorm_outPtr(state_params, binResultBN);
            //feature_extract_setchannellength(state_params, NN_CH);
            //feature_extract_setchannelwidth(state_params, NN_WL);
            feature_extract_setchannelheight(state_params, state_params->init_params.feature_size_per_frame);

            batch_normalization(state_params);

            int k=0;

            for(k=0; k<(state_params->init_params.num_input_channels); k++)
            {
                feature_extract_setconcatframe_inPtr(state_params, &output_ptr[k*(state_params->init_params.output_feature_size_per_channel)]);
                feature_extract_setconcatframe_outPtr(state_params, &binResultBN[k*(state_params->init_params.feature_size_per_frame)]);
                //concat_multi_frames(&nnData.nn_input_int.data[k][0][0], &binResultBN[k*feature_size_per_frame]);
                concat_multi_frames(state_params);
            }
        }
    }
    if(state_params->init_params.type == FEATURE_EXTRACT_WIN_FFT_BIN)
    {
        //uint16_t* input_ptr1 = (uint16_t*)input_buffer;
        float *test_input = &xyz_buff[0];
        float *test_output = &xyz_buff[state_params->init_params.fft_size];
        int8_t *output_ptr1 = (int8_t*)output_buffer;

        feature_extract_setrecorded_dataPtr(state_params, input_ptr);
        feature_extract_setWindow_outputPtr(state_params, test_input);
        feature_extract_setFFT_inputPtr(state_params, test_input);
        feature_extract_setFFT_outputPtr(state_params, test_output);
        feature_extract_setdatareframeinputPtr(state_params, test_input);
        feature_extract_setdatareframeoutputPtr(state_params, output_ptr1);

        run_Windowing(state_params);
        run_CFFT(state_params);
        run_data_reframe(state_params);

    }
    return 1;
}


int init_nn_input_with_test_data(Feature_Extract_Handle_Params *handle_params, float *model_test_input, float32_t* nn_input_test_data_flatten, int8_t *nnData_flatten) {
    Feature_Extract_State_Params *state_params = (Feature_Extract_State_Params *)handle_params;
    ASSERT(sizeof(Feature_Extract_Handle_Params) >= sizeof(Feature_Extract_State_Params));

    uint16_t ln,wd,hi;

    for (ln=0; ln<state_params->init_params.num_input_channels; ln++)
    {
        for (wd=0; wd<state_params->init_params.output_feature_width; wd++)
        {
            for (hi=0; hi<state_params->init_params.output_feature_height; hi++)
            {
                int offset = ln*(state_params->init_params.output_feature_width)*(state_params->init_params.output_feature_height)+wd*(state_params->init_params.output_feature_height)+hi;
                memcpy(&nn_input_test_data_flatten[offset], &model_test_input[offset], sizeof(float32_t));
            }
        }
    }

    // prepare the history for test purpose
    if(state_params->init_params.type == FEATURE_EXTRACT_FFT_BIN) {
        // Test : RAW input, pre-process features, NN output

        //run_frame_rearrange();
        // Step 1: shift frames backwards; new frame features will be calculated from RAW input, batch normalized, then shift/insert

        float *pIn;
        uint16_t i;

        for(i=0; i<state_params->init_params.num_input_channels; i++)
        {

        if(state_params->init_params.num_input_channels == 1)
        {
            pIn = &nn_input_test_data_flatten[i*(state_params->init_params.output_feature_height)];
        }
        else if(state_params->init_params.num_input_channels == 3)
        {
            pIn = &nn_input_test_data_flatten[i*(state_params->init_params.output_feature_height)];
        }

            feature_extract_setrearrangedataPtr(state_params, pIn);

            run_frame_rearrange(state_params);
        }

        // Step 2: Perform batch normalization to the input test vector (floating point to fix point)
        feature_extract_setbatchnorm_inPtr(state_params, &nn_input_test_data_flatten[0]);
        feature_extract_setbatchnorm_outPtr(state_params, &nnData_flatten[0]);
        batch_normalization(state_params);
    }
    return 1;
}


// End of File
