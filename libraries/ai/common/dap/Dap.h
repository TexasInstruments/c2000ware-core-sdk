/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \defgroup DAP Device Agent Protocol (DAP) API
 * \ingroup AI
 *
 * Device Agent Protocol (DAP) for Edge AI Studio communication.
 *
 * The DAP component provides a communication interface between Edge AI Studio
 * (host) and TI devices (target) for data acquisition and sensor streaming.
 *
 * @{
 */

#ifndef DAP_H
#define DAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "dap_link/Dap_Link.h"
#include "dap_core/Dap_Core.h"
#include "dap_interface/Dap_Interface.h"

/* ========================================================================== */
/*                 Public Definitions and Macros                              */
/* ========================================================================== */

/**
 * \anchor Dap_ErrorType
 * \name DAP module error codes
 *
 * Unified error codes used across all DAP layers:
 * - 0-9: Core validation errors (all layers)
 * - 10-19: Frame validation errors (Core layer)
 * - 20-29: Hardware/Link layer errors
 * - 30-39: Application/API errors
 *
 * Protocol error codes sent to the host are defined separately (see
 * DAP_PROTOCOL_ERROR_* in Dap_Core.h).
 *
 * @{
 */

/** \brief No error */
#define DAP_ERROR_NONE                 (0)
/** \brief Invalid instance pointer */
#define DAP_ERROR_INVALID_INSTANCE     (1)
/** \brief Invalid parameters */
#define DAP_ERROR_INVALID_PARAMS       (2)
/** \brief Not initialized */
#define DAP_ERROR_NOT_INITIALIZED      (3)
/** \brief Frame start byte incorrect */
#define DAP_ERROR_INVALID_START_BYTE   (10)
/** \brief Frame end byte incorrect */
#define DAP_ERROR_INVALID_END_BYTE     (11)
/** \brief Frame CRC mismatch */
#define DAP_ERROR_INVALID_CRC          (12)
/** \brief Frame payload malformed */
#define DAP_ERROR_INVALID_PAYLOAD      (13)
/** \brief Buffer overflow */
#define DAP_ERROR_BUFFER_OVERFLOW      (14)
/** \brief Hardware busy */
#define DAP_ERROR_HW_BUSY              (20)
/** \brief Transfer timeout */
#define DAP_ERROR_LINK_TIMEOUT         (21)
/** \brief Unsupported operation mode */
#define DAP_ERROR_UNSUPPORTED_MODE     (22)
/** \brief Streaming not active */
#define DAP_ERROR_NOT_STREAMING        (30)
/** \brief Stream not started - header not sent yet */
#define DAP_ERROR_STREAM_NOT_STARTED   (31)
/** \brief Invalid sensor index */
#define DAP_ERROR_INVALID_SENSOR_INDEX (32)
/** \brief Stream busy - Operation cannot be performed */
#define DAP_ERROR_STREAM_BUSY          (33)

/** @} */

/* ========================================================================== */
/*                 Public Typedefs                                            */
/* ========================================================================== */

/**
 * \brief Pipeline mode enumeration
 *
 * Defines the operating mode for the data pipeline.
 */
typedef enum
{
    DAP_PIPELINE_MODE_UNINITIALIZED    = 0x00U, /**< Pipeline not yet initialized  */
    DAP_PIPELINE_MODE_DATA_ACQUISITION = 0x01U, /**< Data acquisition mode */
    DAP_PIPELINE_MODE_SENSOR_INFERENCE = 0x02U, /**< Sensor inference mode */
    DAP_PIPELINE_MODE_HOST_INFERENCE   = 0x03U, /**< Host inference mode */
    DAP_PIPELINE_MODE_LOOPBACK         = 0x04U  /**< Loopback mode */
} Dap_PipelineModeType;

/**
 * \brief Data channel type for streaming
 *
 * Identifies the data channel for streaming operations.
 * Maps to \ref Dap_Core_DataChannels values.
 */
typedef enum
{
    DAP_DATA_CHANNEL_SENSOR_SIGNAL = DAP_CHANNEL_SENSOR_SIGNAL, /**< Sensor signal data channel */
    DAP_DATA_CHANNEL_INF_SIGNAL    = DAP_CHANNEL_INF_SIGNAL,    /**< Inference signal data channel */
    DAP_DATA_CHANNEL_INF_RESULT    = DAP_CHANNEL_INF_RESULT,    /**< Inference result data channel */
    DAP_DATA_CHANNEL_INF_VALUE     = DAP_CHANNEL_INF_VALUE,     /**< Inference value data channel */
    DAP_DATA_CHANNEL_INF_LOG       = DAP_CHANNEL_INF_LOG        /**< Inference log data channel */
} Dap_DataChannelType;

/**
 * \brief Streaming mode enumeration
 *
 * Defines the pattern of streaming packets
 */
typedef enum
{
    DAP_STREAMING_MODE_CLUSTERED = 0U, /**< Stream cluster of N-sample sets per packet (default) */
    DAP_STREAMING_MODE_DISCRETE  = 1U  /**< Stream 1 sample set per packet */
} Dap_StreamingModeType;

/**
 * \brief Pipeline configuration structure
 *
 * Contains the current pipeline configuration state.
 */
typedef struct
{
    /** \brief Pipeline operating mode */
    Dap_PipelineModeType Mode;
    /** \brief Selected model index (0 if no model) */
    uint8                ModelIndex;
    /** \brief Array of configured sensor indices */
    uint8                SensorIndex[DAP_INTERFACE_MAX_SENSORS];
    /** \brief Number of configured sensors */
    uint8                SensorCount;
} Dap_PipelineConfigType;

/**
 * \brief DAP interface configuration structure
 *
 * Contains all application-provided sensor, model, property, and inference value data.
 */
typedef struct
{
    /** \brief Array of sensor JSON strings (pre-formatted) */
    const char                           *SensorList[DAP_INTERFACE_MAX_SENSORS];
    /** \brief Number of sensors */
    uint8                                 SensorCount;
    /** \brief Array of model JSON strings (pre-formatted) */
    const char                           *ModelList[DAP_INTERFACE_MAX_MODELS];
    /** \brief Number of models */
    uint8                                 ModelCount;
    /** \brief Array of property information pointers */
    Dap_Interface_PropertyInfoType       *PropertyList[DAP_INTERFACE_MAX_PROPERTIES];
    /** \brief Number of properties */
    uint8                                 PropertyCount;
    /** \brief Array of inference value information pointers */
    const Dap_Interface_InfValueInfoType *InfValueList[DAP_INTERFACE_MAX_INF_VALUES];
    /** \brief Number of inference values */
    uint8                                 InfValueCount;
} Dap_InterfaceConfigType;

/**
 * \brief Streaming context structure
 *
 * Maintains state for multi-sensor continuous streaming mode.
 */
typedef struct
{
    /** \brief Per-sensor packet sequence number **/
    uint32                SequenceNumber[DAP_INTERFACE_MAX_SENSORS];
    /** \brief Total samples to stream */
    uint32                TotalSampleCount;
    /** \brief Samples streamed so far */
    uint32                CurrentSampleCount;
    /** \brief TRUE after stream header has been transmitted */
    boolean               HeaderSent;
    /** \brief Active streaming channel (\ref Dap_DataChannelType) */
    uint8                 Channel;
    /** \brief TRUE when streaming is active */
    volatile boolean      IsActive;
    /** \brief Streaming mode */
    Dap_StreamingModeType StreamingMode;
} Dap_StreamingContextType;

/**
 * \brief DAP initialization parameters
 */
typedef struct
{
    /** \brief Link hardware configuration */
    Dap_Link_InitParamsType        LinkParams;
    /** \brief Interface configuration */
    const Dap_InterfaceConfigType *InterfaceConfigPtr;
    /** \brief Streaming mode selection (default: Clustered Mode) */
    Dap_StreamingModeType          StreamingMode;
} Dap_InitParamsType;

/**
 * \brief DAP instance structure
 */
typedef struct Dap_InstanceTag
{
    /** \brief Link layer instance */
    Dap_Link_InstanceType    LinkInstance;
    /** \brief Pipeline configuration */
    Dap_PipelineConfigType   PipelineConfig;
    /** \brief Interface configuration */
    Dap_InterfaceConfigType  InterfaceConfig;
    /** \brief Streaming context */
    Dap_StreamingContextType StreamingContext;
    /** \brief Initialization flag */
    boolean                  IsInitialized;
} Dap_InstanceType;

/* ========================================================================== */
/*                 Public Functions                                           */
/* ========================================================================== */

/**
 * \brief Set default initialization parameters
 *
 * Sets all fields in the initialization parameters structure to default values.
 * Application should call this before modifying specific fields.
 *
 * \param[out] paramsPtr Pointer to initialization parameters structure
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_InitParamsSetDefault(Dap_InitParamsType *paramsPtr);

/**
 * \brief Initialize DAP instance
 *
 * Initializes all DAP layers (link, core, interface) and prepares
 * for communication with the host. The communication hardware is
 * initialized internally by the link layer.
 *
 * \param[out] instancePtr Pointer to DAP instance structure
 * \param[in]  paramsPtr   Pointer to initialization parameters
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Init(Dap_InstanceType *instancePtr, const Dap_InitParamsType *paramsPtr);

/**
 * \brief Start DAP instance
 *
 * Start receiving incoming frames from host. Dap_Init must be called prior
 * to calling this function
 *
 * \param[out] instancePtr Pointer to DAP instance structure
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Open(Dap_InstanceType *instancePtr);

/**
 * \brief Process DAP communication
 *
 * Main processing function to be called in the application's main loop.
 * Checks for received commands, processes them, and sends responses.
 *
 * \param[in] instancePtr Pointer to DAP instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Process(Dap_InstanceType *instancePtr);

/**
 * \brief Start streaming to host
 *
 * Initializes the streaming context and sends the stream header.
 *
 * In Clustered mode: totalSamples indicates the number of distinct sample sets included
 * in a single streaming packet
 * In Discrete mode: There is exactly 1 set of samples per packet, this argument is ignored
 *
 * After calling this function, use Dap_StreamSensorSample() to send sensor samples
 * without per-packet framing.
 *
 * \param[in] instancePtr         Pointer to DAP instance
 * \param[in] sampleSizesBytesPtr Array of sample sizes in bytes per sensor (indexed by sensor slot)
 * \param[in] sampleSizesCount    Number of elements in sampleSizesBytesPtr array
 * \param[in] totalSamples        Total samples to stream per burst
 * \param[in] channel             Data channel to stream on (\ref Dap_DataChannelType)
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_StartSensorStream(Dap_InstanceType *instancePtr, const uint16 *sampleSizesBytesPtr, uint32 sampleSizesCount,
                             uint32 totalSamples, Dap_DataChannelType channel);

/**
 * \brief Send a streaming packet to host
 *
 * Must call Dap_StartSensorStream() first.
 *
 * Sends a sample packet in streaming mode. The sample is sent without per-packet framing.
 * Sequence header is sent per-sample if DAP_INTERFACE_USE_SEQUENCE_HEADERS is enabled.
 *
 * In Discrete mode, Dap_StartSensorStream() and Dap_StreamSensorSample() must be called
 * separately per packet. In Clustered mode, one single call to each API will send all N
 * sample sets framed as a single packet.
 *
 * When the count reaches TotalSampleCount, Dap_StopSensorStream() is called automatically.
 *
 * \param[in] instancePtr  Pointer to DAP instance
 * \param[in] sensorIndex  Index into pipeline sensor configuration (0-based)
 * \param[in] dataPtr      Pointer to sensor sample data
 * \param[in] sizeInBytes  Size of sample data in bytes
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_StreamSensorSample(Dap_InstanceType *instancePtr, uint8 sensorIndex, const uint8 *dataPtr,
                              uint32 sizeInBytes);

/**
 * \brief Stop the currently ongoing stream
 *
 * Sends the stream end byte and resets the streaming context.
 *
 * \param[in] instancePtr Pointer to DAP instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_StopSensorStream(Dap_InstanceType *instancePtr);

/**
 * \brief Get the current streaming mode
 *
 * \param[in]  instancePtr Pointer to DAP instance
 * \param[out] modePtr     Pointer to store the streaming mode
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_GetStreamingMode(const Dap_InstanceType *instancePtr, Dap_StreamingModeType *modePtr);

/**
 * \brief Set the streaming mode
 *
 * \param[in] instancePtr Pointer to DAP instance
 * \param[in] mode        Streaming mode to set
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_SetStreamingMode(Dap_InstanceType *instancePtr, Dap_StreamingModeType mode);

/**
 * \brief Reset stream state
 *
 * Deactivate the stream, and reset streaming context to the initial state. Streaming mode
 * remains unchanged.
 *
 * \param[in] instancePtr Pointer to DAP instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_ResetStream(Dap_InstanceType *instancePtr);

/**
 * \brief Check if streaming is active
 *
 * \param[in]  instancePtr    Pointer to DAP instance
 * \param[out] isStreamingPtr Pointer to store streaming status
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_IsStreaming(const Dap_InstanceType *instancePtr, boolean *isStreamingPtr);

/**
 * \brief Check if command frame is ready to process
 *
 * \param[in]  instancePtr     Pointer to DAP instance
 * \param[out] isFrameReadyPtr Pointer to store frame ready status
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_IsFrameReady(const Dap_InstanceType *instancePtr, boolean *isFrameReadyPtr);

/**
 * \brief Get current pipeline configuration
 *
 * \param[in]  instancePtr Pointer to DAP instance
 * \param[out] configPtr   Pointer to store pipeline configuration
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_GetPipelineConfig(const Dap_InstanceType *instancePtr, Dap_PipelineConfigType *configPtr);

/**
 * \brief De-initialize DAP instance
 *
 * Stops any active streaming, de-initializes all layers, and releases
 * resources.
 *
 * \param[in] instancePtr Pointer to DAP instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_DeInit(Dap_InstanceType *instancePtr);

/**
 * \brief UART receive completion callback
 *
 * This function must be invoked in UART HAL RX complete callback
 * It continues the DAP frame reception state machine by calling Dap_Link_ContinueReceive.
 *
 * \param[in] instancePtr Pointer to UART HAL instance (from callback)
 * \param[in] statusPtr   Pointer to RX status structure (from callback)
 * \param[in] userArgsPtr User arguments pointer (points to DAP link instance)
 */
void Dap_ReceiveCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_RxStatusType *statusPtr, void *userArgsPtr);

/**
 * \brief UART transmit completion callback
 *
 * This function must be invoked in UART HAL TX complete callback
 * It updates the DAP link layer transmit state by calling Dap_Link_ContinueTransmit.
 *
 * \param[in] instancePtr Pointer to UART HAL instance (from callback)
 * \param[in] statusPtr   Pointer to TX status structure (from callback)
 * \param[in] userArgsPtr User arguments pointer (points to DAP link instance)
 */
void Dap_TransmitCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_TxStatusType *statusPtr, void *userArgsPtr);

#ifdef __cplusplus
}
#endif

#endif /* DAP_H */

/** @} */
