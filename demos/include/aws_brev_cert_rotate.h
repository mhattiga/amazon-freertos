/*
 * Amazon FreeRTOS V1.4.7
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef _AWS_BREV_CERT_ROTATE_H_
#define _AWS_BREV_CERT_ROTATE_H_

/*
 * States to identify if rotating out the whitelisted factory 
 * cert or a cert from the cloud.  This is used in the case
 * of a different set of actions are taken during 
 * the whitelisting process with a cert that has limited
 * privileges vs a cert rotation of a fully privileged 
 * cert from the cloud.
 */
typedef enum 
{
    CR_STATE_WHITELIST_CERT,  /* White listed Cert limited priv */
    CR_STATE_CLOUD_CERT,      /* Cloud Cert with full privilegs */
} CERT_ROTATE_STATE;

/* 
 * Store a null terminated string
 */
typedef uint8_t (*pxCR_Put)(char *);
/* 
 * Get a null terminated string
 */
typedef char (* (*pxCR_Get)( void ));
/* 
 * Write value to fixed location in NV memmory
 */
typedef uint8_t (*pxCR_Write)(CERT_ROTATE_STATE val);
/* 
 * Read value from fixed location in NV memmory
 */
typedef CERT_ROTATE_STATE (*pxCR_Read)( void );


typedef struct _CertRotate_Functions {
    pxCR_Write  xWriteCertRotationStateNVM;
    pxCR_Read   xReadCertRotationStateNVM;
    pxCR_Put    xPutDeviceCert;
    pxCR_Get    xGetDeviceCert;
    pxCR_Put    xPutDevicePrivateKey;
    pxCR_Get    xGetDevicePrivateKey;
    pxCR_Put    xPutCSR;
    pxCR_Get    xGetCSR;
    pxCR_Put    xPutSerialNumber;
    pxCR_Get    xGetSerialNumber;
} CertRotate_t;

#endif
