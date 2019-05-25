/*
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file iot_demo_mqtt.c
 * @brief Demonstrates usage of the MQTT library.
 */

/* The config header is always included first. */
#include "iot_config.h"

/* Standard includes. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Set up logging for this demo. */
#include "iot_demo_logging.h"

/* Platform layer includes. */
#include "platform/iot_clock.h"
#include "platform/iot_threads.h"

/* MQTT include. */
#include "iot_mqtt.h"

/* Brev Demo include */
#include "aws_clientcredential_keys.h"
#include "aws_clientcredential.h"
#include "aws_brev_cert_rotate.h"

/**
 * Brev Demo simulated storeage: 
 *      cr_state - store in NV memory
 *      cr_certificate - store in secure element
 *      cr_private_key - store in secure element
 *      cr_csr - big chuck of RAM, make sure it's big enough, but not too big
 */
#define _CR_SUB_TOPIC_COUNT      1
#define _CR_PUB_TOPIC_COUNT      1
#define _CR_CERTIFICATE_SIZE     ( 5000 )
#define _CR_CSR_SIZE             ( sizeof( keyCLIENT_CSR_PEM ) + 1 )  
#define _CR_PRIVATE_KEY_SIZE     ( sizeof( keyCLIENT_PRIVATE_KEY_PEM ) + 1 )
#define _CERT_ROTATION_DELAY_MS  ( 20000 )
#define _CR_TOPIC_PREFIX         "cdf/certificates/"
#define _CR_TOPIC_PREFIX_LEN     ( sizeof( _CR_TOPIC_PREFIX ) + 1 )
#define _CR_TOPIC_SUFFIX_LEN     20
#define _CR_TOPIC_LEN            ( sizeof(clientcredentialIOT_THING_NAME) +_CR_TOPIC_SUFFIX_LEN +\
                                   _CR_TOPIC_PREFIX_LEN )
#define _CR_ACK_RESPONSE_STR            "OK"
#define _CR_GET_RESPONSE_STR            "{\"certificate\":\"-----BEGIN CERTIFICATE-----"
#define _CR_GET_RESPONSE_OFFSET  ( 16 )
#define _PUBLISH_PAYLOAD_BUFFER_LENGTH   (_CR_CSR_SIZE + 50)
#define _MAX_MQTT_PUBLISH_ATTEMPTS       ( 4 ) 
#define _MAX_MQTT_CONNECT_ATTEMPTS       ( 4 ) 
static CERT_ROTATE_STATE _cr_state;
static char _cr_certificate[ _CR_CERTIFICATE_SIZE ];
static char _cr_private_key[ _CR_PRIVATE_KEY_SIZE ];
static char _cr_csr[ _CR_CSR_SIZE ];


/**
 * @brief The first characters in the client identifier. A timestamp is appended
 * to this prefix to create a unique client identifer.
 *
 * This prefix is also used to generate topic names and topic filters used in this
 * demo.
 */
#define _CLIENT_IDENTIFIER_PREFIX                 "iotdemo"

/**
 * @brief The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. Add 1 to include the length of the NULL
 * terminator.
 */
#define _CLIENT_IDENTIFIER_MAX_LENGTH             ( 24 )

/**
 * @brief The keep-alive interval used for this demo.
 *
 * An MQTT ping request will be sent periodically at this interval.
 */
#define _KEEP_ALIVE_SECONDS                       ( 60 )

/**
 * @brief The timeout for MQTT operations in this demo.
 */
#define _MQTT_TIMEOUT_MS                          ( 5000 )

/**
 * @brief The Last Will and Testament topic name in this demo.
 *
 * The MQTT server will publish a message to this topic name if this client is
 * unexpectedly disconnected.
 */
#define _WILL_TOPIC_NAME                          _CR_TOPIC_PREFIX "/will"

/**
 * @brief The length of #_WILL_TOPIC_NAME.
 */
#define _WILL_TOPIC_NAME_LENGTH                   ( ( uint16_t ) ( sizeof( _WILL_TOPIC_NAME ) - 1 ) )

/**
 * @brief The message to publish to #_WILL_TOPIC_NAME.
 */
#define _WILL_MESSAGE                             "MQTT demo unexpectedly disconnected."

/**
 * @brief The length of #_WILL_MESSAGE.
 */
#define _WILL_MESSAGE_LENGTH                      ( ( size_t ) ( sizeof( _WILL_MESSAGE ) - 1 ) )

/**
 * @brief The maximum number of times each PUBLISH in this demo will be retried.
 */
#define _PUBLISH_RETRY_LIMIT                      ( 10 )

/**
 * @brief A PUBLISH message is retried if no response is received within this
 * time.
 */
#define _PUBLISH_RETRY_MS                         ( 1000 )

/**
 * @brief The topic name on which acknowledgement messages for incoming publishes
 * should be published.
 */
#define _ACKNOWLEDGEMENT_TOPIC_NAME               _CR_TOPIC_PREFIX "/acknowledgements"

/**
 * @brief The length of #_ACKNOWLEDGEMENT_TOPIC_NAME.
 */
#define _ACKNOWLEDGEMENT_TOPIC_NAME_LENGTH        ( ( uint16_t ) ( sizeof( _ACKNOWLEDGEMENT_TOPIC_NAME ) - 1 ) )

/**
 * @brief Format string of PUBLISH acknowledgement messages in this demo.
 */
#define _ACKNOWLEDGEMENT_MESSAGE_FORMAT           "Client has received PUBLISH %.*s from server."

/**
 * @brief Size of the buffers that hold acknowledgement messages in this demo.
 */
#define _ACKNOWLEDGEMENT_MESSAGE_BUFFER_LENGTH    ( sizeof( _ACKNOWLEDGEMENT_MESSAGE_FORMAT ) + 2 )


/*-----------------------------------------------------------*/

/* Declaration of demo function. */
int RunMqttDemo( bool awsIotMqttMode,
                 const char * pIdentifier,
                 void * pNetworkServerInfo,
                 void * pNetworkCredentialInfo,
                 const IotNetworkInterface_t * pNetworkInterface );

/*-----------------------------------------------------------*/

/**
 * @brief Called by the MQTT library when an incoming PUBLISH message is received.
 *
 * The demo uses this callback to handle incoming PUBLISH messages. This callback
 * prints the contents of an incoming message and publishes an acknowledgement
 * to the MQTT server.
 * @param[in] param1 Counts the total number of received PUBLISH messages. This
 * callback will increment this counter.
 * @param[in] pPublish Information about the incoming PUBLISH message passed by
 * the MQTT library.
 */
static void _mqttSubscriptionCallback( void * param1,
                                       IotMqttCallbackParam_t * const pPublish )
{
    int acknowledgementLength = 0;
    char * certStr;
    CR_subCallBackParams_t * subCallBackParams;
    CR_MQTT_STEP * mqttStep;
    CertRotate_t * crFuncs;
    IotSemaphore_t * pPublishesReceived;
    const char * pPayload = pPublish->u.message.info.pPayload;
    char pAcknowledgementMessage[ _ACKNOWLEDGEMENT_MESSAGE_BUFFER_LENGTH ] = { 0 };
    IotMqttPublishInfo_t acknowledgementInfo = IOT_MQTT_PUBLISH_INFO_INITIALIZER;
    IotMqttError_t pubStatus;

    subCallBackParams = (CR_subCallBackParams_t *) param1;
    pPublishesReceived = subCallBackParams->pPublishesReceived;
    mqttStep = subCallBackParams->mqttStep;
    crFuncs = subCallBackParams->crFuncs;


    /* Print information about the incoming PUBLISH message. */
    IotLogInfo( "Incoming PUBLISH received:\n"
                "Subscription topic filter: %s\n"
                "Publish topic name: %s\n"
                "Publish retain flag: %d\n"
                "Publish QoS: %d\n",
                pPublish->u.message.pTopicFilter,
                pPublish->u.message.info.pTopicName,
                pPublish->u.message.info.retain,
                pPublish->u.message.info.qos);

    IotLogInfo( "Sub Payload Len: %d", strlen(pPayload ));
    IotLogInfo( "Sub Payload: %100s", pPayload );
    IotLogInfo( "Mqtt Step: %d", *mqttStep );

    /* Set the members of the publish info for the acknowledgement message. */
    acknowledgementInfo.qos = IOT_MQTT_QOS_1;
    acknowledgementInfo.pTopicName = _ACKNOWLEDGEMENT_TOPIC_NAME;
    acknowledgementInfo.topicNameLength = _ACKNOWLEDGEMENT_TOPIC_NAME_LENGTH;
    acknowledgementInfo.pPayload = pAcknowledgementMessage;
    acknowledgementInfo.payloadLength = ( size_t ) acknowledgementLength;
    acknowledgementInfo.retryMs = _PUBLISH_RETRY_MS;
    acknowledgementInfo.retryLimit = _PUBLISH_RETRY_LIMIT;

    pubStatus = IotMqtt_TimedPublish( pPublish->mqttConnection,
                         &acknowledgementInfo,
                         0,
                         _MQTT_TIMEOUT_MS);

    if ( pubStatus == IOT_MQTT_SUCCESS )
    {
        pubStatus = IOT_MQTT_BAD_PARAMETER;
        IotLogInfo( "Acknowledgment message for PUBLISH sent.");
        if (*mqttStep == CR_GET_CERT)
        {
            if (strncmp(pPayload, _CR_GET_RESPONSE_STR, _CR_GET_RESPONSE_OFFSET) == 0)
            {
                certStr = (char *) (pPayload + _CR_GET_RESPONSE_OFFSET);
                IotLogInfo( "Certificate : %100s", certStr);
                if (crFuncs->xPutDeviceCert(certStr) == EXIT_SUCCESS)
                {
                    pubStatus = IOT_MQTT_SUCCESS;
                }
            }
            else
            {
                IotLogInfo( "callback strcmp failed");
            }
        }
        else if (*mqttStep == CR_ACK_CERT)
        {
            if (strcmp(pPayload, _CR_ACK_RESPONSE_STR) == 0)
            {
                pubStatus = IOT_MQTT_SUCCESS;
            }
        }
        if ( pubStatus == IOT_MQTT_SUCCESS )
        {
            /* Increment the number of PUBLISH messages received. */
            IotSemaphore_Post( pPublishesReceived );
        }
    }
    else
    {
        IotLogWarn( "Acknowledgment message for PUBLISH %s will NOT be sent.",
                         IotMqtt_strerror( pubStatus ) );
    }
}

/*-----------------------------------------------------------*/

/**
 * @brief Establish a new connection to the MQTT server.
 *
 * @param[in] awsIotMqttMode Specify if this demo is running with the AWS IoT
 * MQTT server. Set this to `false` if using another MQTT server.
 * @param[in] pIdentifier NULL-terminated MQTT client identifier.
 * @param[in] pNetworkServerInfo Passed to the MQTT connect function when
 * establishing the MQTT connection.
 * @param[in] pNetworkCredentialInfo Passed to the MQTT connect function when
 * establishing the MQTT connection.
 * @param[in] pNetworkInterface The network interface to use for this demo.
 * @param[out] pMqttConnection Set to the handle to the new MQTT connection.
 *
 * @return `EXIT_SUCCESS` if the connection is successfully established; `EXIT_FAILURE`
 * otherwise.
 */
static int _establishMqttConnection( bool awsIotMqttMode,
                                     const char * pIdentifier,
                                     void * pNetworkServerInfo,
                                     void * pNetworkCredentialInfo,
                                     const IotNetworkInterface_t * pNetworkInterface,
                                     IotMqttConnection_t * pMqttConnection )
{
    int status = EXIT_SUCCESS;
    IotMqttError_t connectStatus = IOT_MQTT_STATUS_PENDING;
    IotMqttNetworkInfo_t networkInfo = IOT_MQTT_NETWORK_INFO_INITIALIZER;
    IotMqttConnectInfo_t connectInfo = IOT_MQTT_CONNECT_INFO_INITIALIZER;
    IotMqttPublishInfo_t willInfo = IOT_MQTT_PUBLISH_INFO_INITIALIZER;
    char pClientIdentifierBuffer[ _CLIENT_IDENTIFIER_MAX_LENGTH ] = { 0 };

    /* Set the members of the network info not set by the initializer. This
     * struct provided information on the transport layer to the MQTT connection. */
    networkInfo.createNetworkConnection = true;
    networkInfo.u.setup.pNetworkServerInfo = pNetworkServerInfo;
    networkInfo.u.setup.pNetworkCredentialInfo = pNetworkCredentialInfo;
    networkInfo.pNetworkInterface = pNetworkInterface;

#if IOT_MQTT_ENABLE_SERIALIZER_OVERRIDES == 1
    networkInfo.pMqttSerializer = IOT_MQTT_SERIALIZER_OVERRIDE;
#endif

    /* Set the members of the connection info not set by the initializer. */
    connectInfo.awsIotMqttMode = awsIotMqttMode;
    connectInfo.cleanSession = true;
    connectInfo.keepAliveSeconds = _KEEP_ALIVE_SECONDS;
    connectInfo.pWillInfo = &willInfo;

    /* Set the members of the Last Will and Testament (LWT) message info. The
     * MQTT server will publish the LWT message if this client disconnects
     * unexpectedly. */
    willInfo.pTopicName = _WILL_TOPIC_NAME;
    willInfo.topicNameLength = _WILL_TOPIC_NAME_LENGTH;
    willInfo.pPayload = _WILL_MESSAGE;
    willInfo.payloadLength = _WILL_MESSAGE_LENGTH;

    /* Use the parameter client identifier if provided. Otherwise, generate a
     * unique client identifier. */
    if( pIdentifier != NULL )
    {
        connectInfo.pClientIdentifier = pIdentifier;
        connectInfo.clientIdentifierLength = ( uint16_t ) strlen( pIdentifier );
    }
    else
    {
        /* Every active MQTT connection must have a unique client identifier. The demos
         * generate this unique client identifier by appending a timestamp to a common
         * prefix. */
        status = snprintf( pClientIdentifierBuffer,
                           _CLIENT_IDENTIFIER_MAX_LENGTH,
                           _CLIENT_IDENTIFIER_PREFIX "%lu",
                           ( long unsigned int ) IotClock_GetTimeMs() );

        /* Check for errors from snprintf. */
        if( status < 0 )
        {
            IotLogError( "Failed to generate unique client identifier for demo." );
            status = EXIT_FAILURE;
        }
        else
        {
            /* Set the client identifier buffer and length. */
            connectInfo.pClientIdentifier = pClientIdentifierBuffer;
            connectInfo.clientIdentifierLength = ( uint16_t ) status;

            status = EXIT_SUCCESS;
        }
    }

    /* Establish the MQTT connection. */
    if( status == EXIT_SUCCESS )
    {
        IotLogInfo( "MQTT demo client identifier is %.*s (length %hu).",
                    connectInfo.clientIdentifierLength,
                    connectInfo.pClientIdentifier,
                    connectInfo.clientIdentifierLength );

        connectStatus = IotMqtt_Connect( &networkInfo,
                                         &connectInfo,
                                         _MQTT_TIMEOUT_MS,
                                         pMqttConnection );

        if( connectStatus != IOT_MQTT_SUCCESS )
        {
            IotLogError( "MQTT CONNECT returned error %s.",
                         IotMqtt_strerror( connectStatus ) );

            status = EXIT_FAILURE;
        }
    }

    return status;
}

/*-----------------------------------------------------------*/

/**
 * @brief Add or remove subscriptions by either subscribing or unsubscribing.
 *
 * @param[in] mqttConnection The MQTT connection to use for subscriptions.
 * @param[in] operation Either #IOT_MQTT_SUBSCRIBE or #IOT_MQTT_UNSUBSCRIBE.
 * @param[in] pTopicFilters Array of topic filters for subscriptions.
 * @param[in] pCallbackParameter The parameter to pass to the subscription
 * callback.
 *
 * @return `EXIT_SUCCESS` if the subscription operation succeeded; `EXIT_FAILURE`
 * otherwise.
 */
static int _modifySubscriptions( IotMqttConnection_t mqttConnection,
                                 IotMqttOperationType_t operation,
                                 const char ** pTopicFilters,
                                 void * pCallbackParameter)
{
    int status = EXIT_SUCCESS;
    int32_t i = 0;
    IotMqttError_t subscriptionStatus = IOT_MQTT_STATUS_PENDING;
    IotMqttSubscription_t pSubscriptions[ _CR_SUB_TOPIC_COUNT ] = { IOT_MQTT_SUBSCRIPTION_INITIALIZER };

    /* Set the members of the subscription list. */
    for( i = 0; i < _CR_SUB_TOPIC_COUNT; i++ )
    {
        pSubscriptions[ i ].qos = IOT_MQTT_QOS_1;
        pSubscriptions[ i ].pTopicFilter = pTopicFilters[ i ];
        /* TBD: question why original code had a len - 1, look for this if there is a problem */
        pSubscriptions[ i ].topicFilterLength = strlen( pSubscriptions[ i ].pTopicFilter );
        pSubscriptions[ i ].callback.pCallbackContext = pCallbackParameter;
        pSubscriptions[ i ].callback.function = _mqttSubscriptionCallback;
        IotLogInfo( "Subscribe filter %s.", pSubscriptions[ i ].pTopicFilter );
    }

    /* Modify subscriptions by either subscribing or unsubscribing. */
    if( operation == IOT_MQTT_SUBSCRIBE )
    {
        subscriptionStatus = IotMqtt_TimedSubscribe( mqttConnection,
                                                     pSubscriptions,
                                                     _CR_SUB_TOPIC_COUNT,
                                                     0,
                                                     _MQTT_TIMEOUT_MS );

        /* Check the status of SUBSCRIBE. */
        switch( subscriptionStatus )
        {
            case IOT_MQTT_SUCCESS:
                IotLogInfo( "All demo topic filter subscriptions accepted." );
                break;

            case IOT_MQTT_SERVER_REFUSED:

                /* Check which subscriptions were rejected before exiting the demo. */
                for( i = 0; i < _CR_SUB_TOPIC_COUNT; i++ )
                {
                    if( IotMqtt_IsSubscribed( mqttConnection,
                                              pSubscriptions[ i ].pTopicFilter,
                                              pSubscriptions[ i ].topicFilterLength,
                                              NULL ) == true )
                    {
                        IotLogInfo( "Topic filter %.*s was accepted.",
                                    pSubscriptions[ i ].topicFilterLength,
                                    pSubscriptions[ i ].pTopicFilter );
                    }
                    else
                    {
                        IotLogError( "Topic filter %.*s was rejected.",
                                     pSubscriptions[ i ].topicFilterLength,
                                     pSubscriptions[ i ].pTopicFilter );
                    }
                }

                status = EXIT_FAILURE;
                break;

            default:

                status = EXIT_FAILURE;
                break;
        }
    }
    else if( operation == IOT_MQTT_UNSUBSCRIBE )
    {
        subscriptionStatus = IotMqtt_TimedUnsubscribe( mqttConnection,
                                                       pSubscriptions,
                                                       _CR_SUB_TOPIC_COUNT,
                                                       0,
                                                       _MQTT_TIMEOUT_MS );

        /* Check the status of UNSUBSCRIBE. */
        if( subscriptionStatus != IOT_MQTT_SUCCESS )
        {
            status = EXIT_FAILURE;
        }
    }
    else
    {
        /* Only SUBSCRIBE and UNSUBSCRIBE are valid for modifying subscriptions. */
        IotLogError( "MQTT operation %s is not valid for modifying subscriptions.",
                     IotMqtt_OperationType( operation ) );

        status = EXIT_FAILURE;
    }

    return status;
}

/*-----------------------------------------------------------*/

/**
 * @brief Transmit all messages and wait for them to be received on topic filters.
 *
 * @param[in] mqttConnection The MQTT connection to use for publishing.
 * @param[in] pTopicNames Array of topic names for publishing. These were previously
 * subscribed to as topic filters.
 * @param[in] pPublishReceivedCounter Counts the number of messages received on
 * topic filters.
 *
 * @return `EXIT_SUCCESS` if all messages are published and received; `EXIT_FAILURE`
 * otherwise.
 */
static int _publishAllMessages( IotMqttConnection_t mqttConnection,
                                CR_subCallBackParams_t * subCallBackParams,
                                const char ** pubTopics)
{
    int status = EXIT_SUCCESS;
    int pubTopicLen = 0, pubPayloadLen = 0;
    CR_MQTT_STEP *mqttStep;
    CertRotate_t *crFuncs;
    IotSemaphore_t * pPublishesReceived;
    IotMqttError_t publishStatus = IOT_MQTT_STATUS_PENDING;
    IotMqttPublishInfo_t publishInfo = IOT_MQTT_PUBLISH_INFO_INITIALIZER;
    char pPublishPayload[ _PUBLISH_PAYLOAD_BUFFER_LENGTH ] = { 0 };

    IotLogError( "_publishAllMessages: start");
    IotClock_SleepMs( 1000 );

    mqttStep = subCallBackParams->mqttStep;
    pPublishesReceived = subCallBackParams->pPublishesReceived;
    crFuncs = subCallBackParams->crFuncs;

    /* Set the common members of the publish info. */
    publishInfo.qos = IOT_MQTT_QOS_1;
    publishInfo.retryMs = _PUBLISH_RETRY_MS;
    publishInfo.pTopicName = (*pubTopics);
    publishInfo.pPayload = pPublishPayload;
    publishInfo.retryLimit = _PUBLISH_RETRY_LIMIT;

    /* Generate an publish topic */
    pubTopicLen = strlen ((*pubTopics)) ;
    publishInfo.topicNameLength = pubTopicLen;

    IotLogError( "_publishAllMessages: one");
    IotClock_SleepMs( 1000 );
    /* Generate the payload for the PUBLISH. */
    if (*mqttStep == CR_GET_CERT)
    {
        IotLogError( "_publishAllMessages: MQTT Step = CR_GET_CERT");
        IotClock_SleepMs( 1000 );
        pubPayloadLen = snprintf( pPublishPayload, _PUBLISH_PAYLOAD_BUFFER_LENGTH,
                           "{\"csr\": \"%s\"}",
                           crFuncs->xGetCSR());
    }
    else if (*mqttStep == CR_ACK_CERT)
    {
        IotLogError( "_publishAllMessages: MQTT Step = CR_ACK_CERT");
        IotClock_SleepMs( 1000 );
        strcpy( pPublishPayload, "");
        pubPayloadLen = 2;
    }
    else
    {
        IotLogError( "_publishAllMessages: MQTT Step ERROR");
        IotClock_SleepMs( 1000 );
    }

    /* Check for errors in loading the payload */
    if( pubPayloadLen <= 0 )
    {
        IotLogError( "_publishAllMessages: Failed to generate MQTT PUBLISH payload for PUBLISH ");
        IotClock_SleepMs( 1000 );
        status = EXIT_FAILURE;
    }
    else
    {
        publishInfo.payloadLength = ( size_t ) pubPayloadLen;

        IotLogError( "_publishAllMessages: MQTT PUBLISH topic %s.", publishInfo.pTopicName );
        IotLogError( "_publishAllMessages: MQTT PUBLISH payload .%80s.", publishInfo.pPayload );
        IotClock_SleepMs( 1000 );

        /* PUBLISH a message. This is an asynchronous function that notifies of
         * completion through a callback. */
        publishStatus = IotMqtt_TimedPublish( mqttConnection,
                                         &publishInfo,
                                         0,
                                         _MQTT_TIMEOUT_MS);

        if( publishStatus != IOT_MQTT_SUCCESS )
        {
            IotLogError( "_publishAllMessages: MQTT PUBLISH returned error %s.",
                         IotMqtt_strerror( publishStatus ) );
            IotClock_SleepMs( 1000 );
            status = EXIT_FAILURE;
        }
        /* Wait on the semaphonre twice as long as the pub timeout */
        else if( IotSemaphore_TimedWait( pPublishesReceived,
                                    (_MQTT_TIMEOUT_MS * 2) ) == false )
        {
            IotLogError( "_publishAllMessages: Timed out waiting for incoming PUBLISH messages." );
            IotClock_SleepMs( 1000 );

            status = EXIT_FAILURE;
        }
    }
    IotLogError( "_publishAllMessages: exit status = %d, EXIT_SUCCESS = %d.", status, EXIT_SUCCESS);
    IotClock_SleepMs( 1000 );

    return status;
}

static uint8_t prvBrevDemo_WriteState (CERT_ROTATE_STATE val)
{
    _cr_state = val;
    return EXIT_SUCCESS;
}

static CERT_ROTATE_STATE prvBrevDemo_ReadState ()
{
    return _cr_state;
}

static uint8_t prvBrevDemo_PutDeviceCert (char *cert_str)
{
    int status = EXIT_FAILURE;
    if (strlen(cert_str) < _CR_CERTIFICATE_SIZE)
    {
        status = EXIT_SUCCESS;
        strcpy(&_cr_certificate[0], cert_str);
    }
    else
    {
        IotLogError( "prvBrevDemo_PutDeviceCert: cert_str size = %d, _CR_CERTIFICATE_SIZE= %d.", strlen(cert_str), _CR_CERTIFICATE_SIZE);
    }
    return status;
}

static char * prvBrevDemo_GetDeviceCert (void)
{
    return (&_cr_certificate[0]);
}

static uint8_t prvBrevDemo_PutDevicePrivateKey (char *private_key_str)
{
    int status = EXIT_FAILURE;
    if (strlen(private_key_str) < _CR_PRIVATE_KEY_SIZE)
    {
        status = EXIT_SUCCESS;
        strcpy(&_cr_private_key[0], private_key_str);
    }
    return status;
}

static char * prvBrevDemo_GetDevicePrivateKey ( void )
{
    return (&_cr_private_key[0]);
}

static uint8_t prvBrevDemo_PutCSR (char *csr_str)
{
    int status = EXIT_FAILURE;
    if (strlen(csr_str) < _CR_CSR_SIZE)
    {
        status = EXIT_SUCCESS;
        strcpy(&_cr_csr[0], csr_str);
    }
    return status;
}

static char * prvBrevDemo_GetCSR ( void )
{
    return (&_cr_csr[0]);
}

static void BrevDemo_CertRotationInit( CertRotate_t *crFuncs )
{
    IotLogInfo( "************** CERT ROTATION INIT **********");
    crFuncs->xWriteCertRotationStateNVM = &prvBrevDemo_WriteState;
    crFuncs->xReadCertRotationStateNVM  = &prvBrevDemo_ReadState;
    crFuncs->xPutDeviceCert             = &prvBrevDemo_PutDeviceCert;
    crFuncs->xGetDeviceCert             = &prvBrevDemo_GetDeviceCert;
    crFuncs->xPutDevicePrivateKey       = &prvBrevDemo_PutDevicePrivateKey;
    crFuncs->xGetDevicePrivateKey       = &prvBrevDemo_GetDevicePrivateKey;
    crFuncs->xPutCSR                    = &prvBrevDemo_PutCSR;
    crFuncs->xGetCSR                    = &prvBrevDemo_GetCSR;

    ( * crFuncs->xWriteCertRotationStateNVM ) ( CR_STATE_CLOUD_CERT );
    ( * crFuncs->xPutDeviceCert ) ( keyCLIENT_CERTIFICATE_PEM );
    ( * crFuncs->xPutDevicePrivateKey ) ( keyCLIENT_PRIVATE_KEY_PEM );
    ( * crFuncs->xPutCSR ) ( keyCLIENT_CSR_PEM );
}

/**
 * @brief Initialize the MQTT library.
 *
 * @return `EXIT_SUCCESS` if all libraries were successfully initialized;
 * `EXIT_FAILURE` otherwise.
 */
static int _initializeDemo( CertRotate_t *crFuncs )
{
    int ret = EXIT_SUCCESS;
    IotMqttError_t mqttInitStatus = IOT_MQTT_SUCCESS;

    BrevDemo_CertRotationInit( crFuncs );

    /* Initialize the MQTT library. */
    mqttInitStatus = IotMqtt_Init();
    if( mqttInitStatus != IOT_MQTT_SUCCESS )
    {
        ret = EXIT_FAILURE;
    }

    return ret;
}

/**
 * @brief Clean up the  the MQTT library.
 */
static void _cleanupDemo( void )
{
    IotMqtt_Cleanup();
}


int _mqttStep(
    IotMqttConnection_t mqttConnection,
    const char ** subTopics,
    const char ** pubTopics,
    CertRotate_t * crFuncs,
    CR_MQTT_STEP * mqttStep)
{
    int status;
    int mqtt_publish_attempts;
    CR_subCallBackParams_t subCallBackParams;

    /* Counts the number of incoming PUBLISHES received (and allows the demo
     * application to wait on incoming PUBLISH messages). */
    IotSemaphore_t publishesReceived; 

    /* Store data in struct used in subscritption callback */
    subCallBackParams.pPublishesReceived = &publishesReceived;
    subCallBackParams.mqttStep = mqttStep;
    subCallBackParams.crFuncs = crFuncs;

    /* Add the topic filter subscriptions used in this demo. */
    status = _modifySubscriptions( mqttConnection,
                                   IOT_MQTT_SUBSCRIBE,
                                   subTopics,
                                   &subCallBackParams);
    if (status != EXIT_SUCCESS )
    {
        IotLogError( "_mqttStep: Failed to subscribe topics");
    }
    else
    {
        IotLogError( "_mqttStep: subscribe topics succeeded");
        IotClock_SleepMs( 1000 );

        /* Create the semaphore to count incoming PUBLISH messages. */
        if( IotSemaphore_Create( &publishesReceived,
                                 0,
                                 IOT_DEMO_MQTT_PUBLISH_BURST_SIZE ) == true )
        {
            IotLogError( "_mqttStep: created Semaphore");
            IotClock_SleepMs( 1000 );
            status = EXIT_FAILURE;

            for (mqtt_publish_attempts = 0; 
                 mqtt_publish_attempts < _MAX_MQTT_PUBLISH_ATTEMPTS &&
                 status != EXIT_SUCCESS; 
                 mqtt_publish_attempts++)
            {
                /* PUBLISH (and wait) for all messages. */
                IotLogError( "_mqttStep: for loop %d", mqtt_publish_attempts);
                IotClock_SleepMs( 1000 );
                status = _publishAllMessages( mqttConnection,
                                              &subCallBackParams,
                                              pubTopics);

                IotLogError( "_mqttStep: post for loop status = %d, EXIT_SUCCESS = %d", status, EXIT_SUCCESS);
                IotClock_SleepMs( 1000 );
            }
            /* Destroy the incoming PUBLISH counter. */
            IotSemaphore_Destroy( &publishesReceived );
        }
        else
        {
            /* Failed to create incoming PUBLISH counter. */
            status = EXIT_FAILURE;
        }
    }

    if( status == EXIT_SUCCESS )
    {
        /* Remove the topic subscription filters used in this demo. */
        status = _modifySubscriptions( mqttConnection,
                                       IOT_MQTT_UNSUBSCRIBE,
                                       subTopics,
                                       NULL);
    }
    return (status);
}

int BrevDemo_GetNewCert( 
    bool awsIotMqttMode,
    const char * pIdentifier,
    void * pNetworkServerInfo,
    void * pNetworkCredentialInfo,
    const IotNetworkInterface_t * pNetworkInterface,
    CertRotate_t * crFuncs)
{
    int status = EXIT_FAILURE;
    int mqtt_connect_attempts;
    CR_MQTT_STEP mqttStep;

    /* Handle of the MQTT connection used in this demo. */
    IotMqttConnection_t mqttConnection = IOT_MQTT_CONNECTION_INITIALIZER;

    /* Flag for tracking which cleanup functions must be called. */
    int connectionEstablished = false;

    /* Subscribe Topics to Get a Certificate */
    const char * subGetTopics[ _CR_SUB_TOPIC_COUNT ] =
    {
       _CR_TOPIC_PREFIX clientcredentialIOT_THING_NAME "/get/+",
    };
    const char * pubGetTopics[ _CR_PUB_TOPIC_COUNT ] =
    {
       _CR_TOPIC_PREFIX clientcredentialIOT_THING_NAME "/get",
    };

    /* Subscribe Topics to Acknowledge a Certificate */
    const char * subAckTopics[ _CR_SUB_TOPIC_COUNT ] =
    {
       _CR_TOPIC_PREFIX clientcredentialIOT_THING_NAME "/ack/+",
    };
    const char * pubAckTopics[ _CR_PUB_TOPIC_COUNT ] =
    {
       _CR_TOPIC_PREFIX clientcredentialIOT_THING_NAME "/ack",
    };


    for (mqtt_connect_attempts = 0; 
         mqtt_connect_attempts < _MAX_MQTT_CONNECT_ATTEMPTS &&
         status != EXIT_SUCCESS; 
         mqtt_connect_attempts++)
    {

        /* Establish a new MQTT connection. */
        status = _establishMqttConnection( awsIotMqttMode,
                                           pIdentifier,
                                           pNetworkServerInfo,
                                           pNetworkCredentialInfo,
                                           pNetworkInterface,
                                           &mqttConnection );
        if (status != EXIT_SUCCESS )
        {
            IotLogError( "BrevDemo_GetNewCert: Failed to establish MQTT connection");
        }
        else
        {
            /* Mark the MQTT connection as established. */
            connectionEstablished = true;
            mqttStep = CR_GET_CERT;

            /* Get the new cert */
            status =  _mqttStep(
                        mqttConnection,
                        subGetTopics,
                        pubGetTopics,
                        crFuncs,
                        &mqttStep);

            IotLogError( "***********************post get cert, cert is %100s", crFuncs->xGetDeviceCert() );
            IotClock_SleepMs( 1000 );

            if (status == EXIT_SUCCESS)
            {
                /* Acknowledge the new cert */
                mqttStep = CR_ACK_CERT;
                status =  _mqttStep(
                            mqttConnection,
                            subAckTopics,
                            pubAckTopics,
                            crFuncs,
                            &mqttStep);
            }
        }

        /* Disconnect the MQTT connection if it was established. */
        if( connectionEstablished == true )
        {
            IotMqtt_Disconnect( mqttConnection, 0 );
        }
    }
    return status;
}

int BrevDemo_RotateCert()
{
    return EXIT_SUCCESS;
}

/* 
 * Major hack to see what's inside a data structure. Not recommended practice
 */
typedef struct LocalIotNetworkServerInfoAfr
{
    const char * pHostName; /**< @brief Server host name. Must be NULL-terminated. */
    uint16_t port;          /**< @brief Server port in host-order. */
} LocalIotNetworkServerInfoAfr_t;

/*-----------------------------------------------------------*/

/**
 * @brief The function that runs the MQTT demo, called by the demo runner.
 *
 * @param[in] awsIotMqttMode Specify if this demo is running with the AWS IoT
 * MQTT server. Set this to `false` if using another MQTT server.
 * @param[in] pIdentifier NULL-terminated MQTT client identifier.
 * @param[in] pNetworkServerInfo Passed to the MQTT connect function when
 * establishing the MQTT connection.
 * @param[in] pNetworkCredentialInfo Passed to the MQTT connect function when
 * establishing the MQTT connection.
 * @param[in] pNetworkInterface The network interface to use for this demo.
 *
 * @return `EXIT_SUCCESS` if the demo completes successfully; `EXIT_FAILURE` otherwise.
 */
int RunMqttDemo( bool awsIotMqttMode,
                 const char * pIdentifier,
                 void * pNetworkServerInfo,
                 void * pNetworkCredentialInfo,
                 const IotNetworkInterface_t * pNetworkInterface )
{

    LocalIotNetworkServerInfoAfr_t * pLocal; 
    int status = EXIT_SUCCESS;

    /* Flags for tracking which cleanup functions must be called. */
    bool librariesInitialized = false;

    /* All the data and CallBack for the Brev Cert Rotate Demo */
    CertRotate_t crFuncs; 

    /* Initialize the libraries required for this demo. */
    status = _initializeDemo( &crFuncs );

    if( status == EXIT_SUCCESS )
    {
        /* Mark the libraries as initialized. */
        librariesInitialized = true;

        while (1)
        {
            /* 
             * Loop through:
             *  1) BrevDemo_GetNewCert()
             *  3) BrevDemo_RotateCert()
             */
            status = BrevDemo_GetNewCert(
                awsIotMqttMode,
                pIdentifier,
                pNetworkServerInfo,
                pNetworkCredentialInfo,
                pNetworkInterface,
                &crFuncs);

            
            pLocal = (LocalIotNetworkServerInfoAfr_t *) pNetworkServerInfo;
            IotLogInfo( "Host Name = %s", (LocalIotNetworkServerInfoAfr_t *) pLocal->pHostName) ;

            IotLogInfo( "Device Cert = %70s\n", (*crFuncs.xGetDeviceCert)() ); 
            IotLogInfo( "Length of Device Cert = %d", strlen( (*crFuncs.xGetDeviceCert)() ));
            IotLogInfo( "Private Key = %70s\n", (*crFuncs.xGetDevicePrivateKey)() ); 
            IotLogInfo( "Length of Private Key = %d", strlen( (*crFuncs.xGetDevicePrivateKey)() )); 
            IotLogInfo( "CSR = %70s\n", (*crFuncs.xGetCSR )() ); 
            IotLogInfo( "Length of CSR = %d", strlen( ( *crFuncs.xGetCSR )() ));
            IotLogInfo( "State = %d", (uint8_t) (*crFuncs.xReadCertRotationStateNVM)() ); 

            if (status != EXIT_SUCCESS)
            {
                IotLogInfo( "Current cert is not working.");
                break;
            }


#ifdef SAVE
            status = BrevDemo_RotateCert(
                awsIotMqttMode,
                pIdentifier,
                pNetworkServerInfo,
                pNetworkCredentialInfo,
                pNetworkInterface
                &crFuncs);
            if (status != EXIT_SUCCESS)
            {
                IotLogInfo( "Could not get new cert.");
                break;
            }
#endif
            IotClock_SleepMs(_CERT_ROTATION_DELAY_MS);
        }

    }

    /* Clean up libraries if they were initialized. */
    if( librariesInitialized == true )
    {
        _cleanupDemo();
    }

    return status;
}
