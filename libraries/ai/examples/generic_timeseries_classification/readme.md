# Generic Timeseries Classification on C28x Devices

## 1. Purpose

Generic Timeseries Classification is a hello world example for understanding usage of AI models on TI MCU. We have used a simple classification dataset. This project demonstrates implementation of an AI-based waveform detection system on TI C28x microcontrollers. It showcases how to deploy machine learning models for real-time waveform classification in embedded systems, serving as a hello world example. The onboard hardware accelerates AI processing faster than software implementations. Complementing this hardware advantage, TI provides a complete development ecosystem with toolchains and SDKs that significantly streamline all stages of Edge AI solution development.

## 2. Dataset & AI Model Details

### 2.1 **Dataset**

TI has created a specialized waveform dataset containing signal measurements. The dataset is divided into three classes: sine waveform, sawtooth waveform and square waveform. The data is organized into three folders, one for each class. Each folder contains multiple CSV files, with each file storing thousands of signal measurement samples in a each column. These sequential measurements provide the necessary data for training effective detection models.

| Parameter | Value |
|-----------|-------|
| **Sensor** | Signal readings |
| **Sampling Rates** | 40 Hz |
| **Channels** | 1 (signal magnitude) |
| **Samples per File** | Variable: 25,600 samples |
| **Total Files** | 75 files (~25 files in each of 3 classes) |

Each file is a CSV (Excel format) with the following structure:

**Columns:**
- Column 1: Signal Magnitude

**Example data (csv): Square Wave**
```csv
Signal Magnitude
1125
1126
1133
1129
3003
2997
```

### 2.2 **Model Architecture**

This lightweight classification model `CLS_1k_NPU` contains approximately 1,000 parameters and follows a streamlined architecture consisting of four convolutional layers (each enhanced with BatchNorm and ReLU activation functions) followed by a single linear layer. The model is specifically designed to be fully compatible with TI's Neural Processing Unit (NPU) specifications as documented in the [NPU compliance guidelines](https://software-dl.ti.com/mctools/nnc/mcu/users_guide/), adhering to the required m4 channel configuration and maintaining kernel heights of 7 or less.

### 2.3  **Input Features**

The model takes 4D input (N,C,H,W)
  - N (1)    : batch size which is restricted to 1
  - C (1)    : channels which is 1 for signal
  - H (256)  : samples of timeseries signals which is 256 in this example
  - W (1)    : width of samples is restricted to 1 for timeseries applications

### 2.4 **Output Classes**

This model produces a 1D output representing the three possible classes. The position of the highest value in this output indicates the classification result. If the first element of the array has the highest value, it means the AI model detected it as sine waveform.

### 2.5 **Performance Metrics**

The AI model's memory requirements differ significantly when targeting CPU versus NPU execution. Flash memory stores the model's core components (weights, biases, and architectural definition), while SRAM provides the working memory needed for runtime operations, including input processing and output storage. These memory footprints vary based on the chosen processing unit implementation.

| Configuration | FLASH (B) | SRAM (B) |
|---------------|-----------|----------|
|      CPU      |    4126   |  12320   |
|      NPU      |    3519   |   4256   |

## 3. Project Structure
```
|_ generic_timeseries_classification
    |_ application_main.c         # Main application containing API calls to Feature Extraction and AI Model
    |_ user_input_config.h        # Flags representing Feature Extraction to apply on the raw input from sensors
    |_ test_vector.c              # Test cases to verify working of Feature Extraction and AI model on device
    |_ lnk.cmd                    # Defines utilization of memory banks
    |_ artifacts
        |_ mod.a                  # Contains the compiled AI model
        |_ tvmgen_default.h       # Exposing APIs to use AI model and model definition
    |_ feature_extract
        |_ feature_extract_c28.c  # Implementation of optimized FFT function
        |_ feature_extract.c      # Implementation of feature extraction
        |_ feature_extract.h      # Exposing APIs to use feature extraction
```

## 4. Feature Extraction Used

Feature extraction transforms raw data into meaningful inputs for our AI model. For this waveform detection system, our experimental testing revealed that applying FFT to identify frequencies, followed by binning and logarithmic scaling, produces superior results. This approach also reduces the input dimensions for the AI model.

The feature extraction pipeline is configured in the user_input_config.h file, where various processing flags (prefixed with FE_) control the data transformation. In this example we have used the following preset `Generic_1024Input_FFTBIN_64Feature_8Frame`. Below is the breakdown of this preset:

- **FE_FFT**: Performs Fast Fourier Transform on the raw frame, calculating magnitude values from complex outputs. FFT converts the time-domain signal into frequency components, which is crucial since waveforms exhibit distinctive frequency signatures.
- **FE_DC_REM**: Removes the DC component from Fourier transform.
- **FE_BIN**: Groups frequencies into FE_BIN_SIZE bins, starting from FE_MIN_FFT_BIN. Binning reduces dimensionality while preserving the frequency distribution pattern that distinguishes waveforms.
- **FE_BIN_NORMALIZE**: Normalizes the bin using the FE_BIN_SIZE when this flag is present.
- **FE_LOG**: Applies logarithmic scaling to the binned frequency data. Log scaling compresses the dynamic range, emphasizing smaller frequency components that might contain critical waveform indicators.
- **FE_CONCAT**: Combines scaled outputs from multiple data frames (quantity specified by FE_NUM_FRAME_CONCAT). Concatenation provides temporal context by incorporating information from previous frames, helping detect evolving waveform patterns. The concatenation feature improves detection accuracy but requires additional storage capacity.

In the yaml configuration of modelzoo, we have selected the Generic_512Input_FFTBIN_32Feature_8Frame, which means the feature extraction library will take a data frame of size 512 and compute FFT of it. Then it will calculate the magnitude of the FFT and result in frame of size 257. It will remove the DC and result in size of 256. Binning will be performed to get the output of size 32, so it will create bins of 256/32 size which is 8. It will do this for 8 frames and concatenate the output from it to finally give us 32*8 features which is 256 for the AI model.

Within test_vector.c, we've included two sample signal readings from each type of waveform conditions. The visualizations below demonstrate how our feature extraction pipeline transforms these raw signals, highlighting the distinct differences between each waveform condition signatures after processing.

### 4.1 Sawtooth Waveform
![Bearing Normal](assets/sawtooth.png)

### 4.2 Sine Waveform
![Bearing Contaminated](assets/sine.png)

Notice how the graph for sawtooth turns out to be different than the one for sine waveform. These differences are analyzed further by the AI model to give better results than the traditional methods. Hence improving the detection of various types of signals.

## 5. How to Recreate AI Model

To develop an AI model for waveform detection, we need a complete workflow that includes dataset loading, pre-processing, model training, validation, and exporting with metadata. TI offers two toolchain options for this process: Edge AI Studio or TinyML Modelzoo. This example demonstrates how to use Modelzoo to generate the necessary artifacts and golden vectors for deployment on C28x devices.

### 5.1 Modelzoo

Setting up modelzoo can be found [here](https://github.com/TexasInstruments/tinyml-tensorlab/tree/main/tinyml-modelzoo).

#### 5.1.1 Step-by-step guide to use TI Modelzoo for model creation

```bash
./run_tinyml_modelzoo.sh examples/hello_world/config.yaml
```
- **run_tinyml_modelzoo.sh** : represents the script invoking the modelzoo, takes one argument which is the path of yaml
- **examples/hello_world/config.yaml** : path of configuration file to execute

After executing the above command, you can see the modelzoo starts working according to the yaml file passed to it. In the logs you can observe the following
- Downloading the dataset
- Performing feature extraction
- Training of the AI Model
- Quantization Aware Training of the AI model
- Accuracy of the exported quantized model on test data
- Compilation of the model using [TI Neural Network Compiler for MCUs](https://software-dl.ti.com/mctools/nnc/mcu/users_guide/index.html)

At the end of the logs you can find the path of compiled model.

#### 5.1.2 Exporting the model for C28x deployment

From executing the above command you can find the results stored in tinyml-modelmaker. The results for a particular instance have path in the following manner:

- tinyml-modelmaker/data/projects/hello_world_example_dsg/run/**20260122-102510**/CLS_1k_NPU

The directory marked bold represents the time at which the script was invoked. The target device (such as c28x) has four useful file outputs by ModelMaker.

- `mod.a`: The ONNX model is compiled by tvm to get C files, which are converted into a single mod.a that can run on device.
- `tvmgen_default.h`: Mod.a exposes few APIs to interact with model which are present here. You can use these APIs in your application to run model

- `test_vector.c`: ModelMaker gives a test dataset and the expected output. You can use the model to inference this test dataset and check if the output is matching. 
- `user_input_config.h`: This configuration file has preprocessing flag definitions for the parameters used for feature extraction.

### 5.2 CCS Project

#### 5.2.1 Creating a new project in Code Composer Studio

- Install the [C2000Ware SDK](https://www.ti.com/tool/C2000WARE)
- In research explorer, search for generic_timeseries_classification project
- Import the project
- Replace the files in CCS Project with the ones generated from modelmaker.

#### 5.2.2 Compiled model files

- mod.a: The compiled model is present in this file. 
  - Path Modelmaker: *tinyml-modelmaker/data/projects/hello_world_example_dsg/run/20260122-102510/CLS_1k_NPU/compilation/artifacts/mod.a*
  - Path CCS Project: *generic_timeseries_classification_f28p55x/artifacts/mod.a*
- tvmgen_default.h: Header file to access the model inference APIs from mod.a 
  - Path Modelmaker: *tinyml-modelmaker/data/projects/hello_world_example_dsg/run/20260122-102510/CLS_1k_NPU/compilation/artifacts/tvmgen_default.h*
  - Path CCS Project: *generic_timeseries_classification_f28p55x/artifacts/tvmgen_default.h*

#### 5.2.3 Feature Extraction configuration & Test data for device verification

- test_vector.c: Test cases to check if the model works on device currently
  - Path Modelmaker: *tinyml-modelmaker/data/projects/hello_world_example_dsg/run/20260122-102510/CLS_1k_NPU/training/quantization/golden_vectors/test_vector.c*
  - Path CCS Project: *generic_timeseries_classification_f28p55x/test_vector.c*
- user_input_config.h: Configuration of feature extraction library in SDK. 
  - Path Modelmaker: *tinyml-modelmaker/data/projects/hello_world_example_dsg/run/20260122-102510/CLS_1k_NPU/training/quantization/golden_vectors/user_input_config.h*
  - Path CCS Project: *generic_timeseries_classification_f28p55x/user_input_config.h*

#### 5.2.4 Building the application

After preparing the project, we'll build and flash it to the C28x device. The main application logic resides in 'application_main.c', which contains the code responsible for configuring the feature extraction library and executing the waveform detection model inference.

1. Now we will build the project. Go to Project Tab -> Select Build Project(s)
![Build project](assets/build_project.png)
2. Connect launchpad F28P55x to your system.

## 6. Deploying on C28x Device

Now we will flash the built project on the device. We will use debug mode to see the result of model inference present in *test_result*.

3. Switch the active target device from **TMS320F28P550SJ9.ccxml** to **TMS320F28P550SJ9_LaunchPad.ccxml**.
![Select CPU](assets/select_target.png)
4. Flash the built project in device. Go to Run tab -> Select Flash Project
![Flash application](assets/flash_application.png)
5. After the application is flashed, debug screen will appear. Select the debug icon.
![Debug Screen](assets/debug_screen.png)
6. Continue the program in debug mode.
![Continue](assets/continue.png)
7. In the CIO tab of CCS Studio, you can see that 'All tests have passed'
![All Test Passed](assets/all_test_passed.png)


## 7. Performance Analysis

We conducted performance profiling of both the Feature Extraction Library and the AI model on the f28p55x device. The measurements below show the processing cycles required for each component. Note that these values will vary across different devices of c28x. 

| Configuration | FE Cycles | FE Time (us) |  AI Model Cycles | Inference Time (us) |
|---------------|-----------|--------------|------------------|---------------------|
|      CPU      |   65282   |     435.21   |      1766215     |      11774.76       |
|      NPU      |   66961   |     446.40   |       145824     |        972.16       |

Notably, the AI model executes 12.1 times faster when running on the NPU compared to CPU implementation.

<hr>
Update history:
[22nd Jan 2026]: Compatible with v1.3 of Tiny ML Modelmaker
