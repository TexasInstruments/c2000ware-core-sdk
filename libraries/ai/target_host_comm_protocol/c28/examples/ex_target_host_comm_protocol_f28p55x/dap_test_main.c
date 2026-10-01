//#############################################################################
//
// FILE:   dap_test_main.c
//
//! This example shows how to run the Device Agent Protocol (DAP) on the
//! MCU side.
//
//#############################################################################
//
//
// 
// C2000Ware v26.02.00.00
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
//   documentation and/or other materials provided with the distribution.
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

#include "board.h"
#include "Dap.h"

/* ========================================================================== */
/*                 Private Function Prototypes                                */
/* ========================================================================== */

static void App_LiveCapture_Run(void);

/* ========================================================================== */
/*                 DAP Interface Configuration                                */
/* ========================================================================== */

/* Sensor JSON descriptors */
static const char gSensor1Json[] =
    "{\"name\":\"AFE1_current\",\"type\":6,\"dataFormat\":5,\"sequenceNumbers\":true, "
    "\"labels\":\"Arc current if Ch1 is selected\"}";
static const char gSensor2Json[] =
    "{\"name\":\"AFE2_current\",\"type\":6,\"dataFormat\":5,"
    "\"labels\":\"Arc current if Ch2 is selected\"}";
static const char gSensor3Json[] =
    "{\"name\":\"AFE_Ch3_current\",\"type\":6,\"dataFormat\":5,"
    "\"labels\":\"Arc current if Ch3 is selected\"}";
static const char gSensor4Json[] =
    "{\"name\":\"Vib_sensor1\",\"type\":7,\"dataFormat\":6,\"labels\":\"x\"}";

/* Model JSON descriptors */
static const char gModel1Json[] =
    "{\"name\":\"ArcFault_model_200_t\",\"task\":\"ArcFault_model\","
    "\"projectID\":\"Project_Name\"}";
static const char gModel2Json[] =
    "{\"name\":\"ArcFault_model_300_t\",\"task\":\"ArcFault_model\","
    "\"projectID\":\"Project_Name\"}";
static const char gModel3Json[] =
    "{\"name\":\"ArcFault_model_700_t\",\"task\":\"ArcFault_model\","
    "\"projectID\":\"Project_Name\"}";

/* Properties */
static Dap_Interface_PropertyInfoType gProperty1 = {
    "Property1", DAP_DATA_FORMAT_UINT16, {0U}
};

/* Inference value */
static const Dap_Interface_InfValueInfoType gInference1 = {
    "inferenceA", DAP_DATA_FORMAT_UINT16
};

/* Interface configuration populated in main() */
static Dap_InterfaceConfigType gInterfaceConfig;

/* ========================================================================== */
/*                 Global Instances                                           */
/* ========================================================================== */

Uart_Hal_InstanceType gUartInstance;
Dap_InstanceType      gDapInstance;


/* ========================================================================== */
/*                 Main                                                       */
/* ========================================================================== */

void main(void)
{
    Uart_Hal_InitParamsType halParams;
    Dap_InitParamsType      dapParams;

    /* ---------------------------------------------------------------------- */
    /* Device and GPIO initialisation                                          */
    /* ---------------------------------------------------------------------- */

    Device_init();
    Device_initGPIO();

    /* GPIO28 — SCI-A Rx */
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    /* GPIO29 — SCI-A Tx */
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    /* PIE initialisation */
    Interrupt_initModule();
    Interrupt_initVectorTable();

    /* ---------------------------------------------------------------------- */
    /* UART HAL initialisation                                                 */
    /* ---------------------------------------------------------------------- */

    halParams.BaudRateBps = 9600UL;
    Uart_Hal_Init(&gUartInstance, &halParams);

    /* ---------------------------------------------------------------------- */
    /* Build interface configuration                                           */
    /* ---------------------------------------------------------------------- */

    gProperty1.Value.U16 = 1000U;

    gInterfaceConfig.SensorList[0]  = gSensor1Json;
    gInterfaceConfig.SensorList[1]  = gSensor2Json;
    gInterfaceConfig.SensorList[2]  = gSensor3Json;
    gInterfaceConfig.SensorList[3]  = gSensor4Json;
    gInterfaceConfig.SensorCount    = 4U;

    gInterfaceConfig.ModelList[0]   = gModel1Json;
    gInterfaceConfig.ModelList[1]   = gModel2Json;
    gInterfaceConfig.ModelList[2]   = gModel3Json;
    gInterfaceConfig.ModelCount     = 3U;

    gInterfaceConfig.PropertyList[0]  = &gProperty1;
    gInterfaceConfig.PropertyCount    = 1U;

    gInterfaceConfig.InfValueList[0]  = &gInference1;
    gInterfaceConfig.InfValueCount    = 1U;

    /* ---------------------------------------------------------------------- */
    /* DAP initialisation                                                      */
    /* ---------------------------------------------------------------------- */

    Dap_InitParamsSetDefault(&dapParams);
    dapParams.LinkParams.UartInstancePtr = &gUartInstance;
    dapParams.InterfaceConfigPtr         = &gInterfaceConfig;
    dapParams.StreamingMode              = DAP_STREAMING_MODE_DISCRETE;

    Dap_Init(&gDapInstance, &dapParams);
    Dap_Open(&gDapInstance);

    /* Enable global interrupts and real-time debug */
    EINT;
    ERTM;

    /* ---------------------------------------------------------------------- */
    /* Main loop                                                               */
    /* ---------------------------------------------------------------------- */

    while (1)
    {
        Dap_Process(&gDapInstance);

        boolean                isStreaming = FALSE;
        Dap_PipelineConfigType pipelineConfig;

        Dap_IsStreaming(&gDapInstance, &isStreaming);
        Dap_GetPipelineConfig(&gDapInstance, &pipelineConfig);

        if (isStreaming == TRUE)
        {
            if (pipelineConfig.Mode == DAP_PIPELINE_MODE_DATA_ACQUISITION)
            {
                App_LiveCapture_Run();
            }
        }
    }
}

/* ========================================================================== */
/*                 Private Functions                                          */
/* ========================================================================== */

static void App_LiveCapture_Run(void)
{
    static const uint16 sensorSampleSizes[1] = {2U};
    static uint16       sawtoothValue        = 0U;
    uint8               temp_databuff[2];
    sint32              status;

    temp_databuff[0] = (uint8)((sawtoothValue >> 8U) & 0xFFU);
    temp_databuff[1] = (uint8)(sawtoothValue & 0xFFU);

    status = Dap_StartSensorStream(&gDapInstance, sensorSampleSizes, sizeof(sensorSampleSizes), 1U,
                                   DAP_DATA_CHANNEL_SENSOR_SIGNAL);
    if (status == DAP_ERROR_NONE)
    {
        (void)Dap_StreamSensorSample(&gDapInstance, 0U, temp_databuff, 2U);

        sawtoothValue = (sawtoothValue < 500U) ? (sawtoothValue + 1U) : 0U;

        DEVICE_DELAY_US(4000);
    }
}

/* ========================================================================== */
/*                 UART HAL Callbacks                                         */
/* ========================================================================== */

void Uart_Hal_RxCompleteCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_RxStatusType *statusPtr,
                                 void *userArgsPtr)
{
    Dap_ReceiveCallback(instancePtr, statusPtr, userArgsPtr);
}

void Uart_Hal_TxCompleteCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_TxStatusType *statusPtr,
                                 void *userArgsPtr)
{
    Dap_TransmitCallback(instancePtr, statusPtr, userArgsPtr);
}

//
// End of File
//
