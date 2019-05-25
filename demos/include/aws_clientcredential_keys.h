/*
 * Amazon FreeRTOS V1.4.1
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

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUSJMNlfQ+9qzRJ7NI/AbNaS1XLeIwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MDUyNDE1NDQw\n"\
"NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKXEh05RbtSO6s4ulJUx\n"\
"+eV8So1hz4pSiF6AcKR9rvMOmm+m+k9H+K+LrWaMuORXlLSX+4bqGmkoexN7Lf4U\n"\
"6YoaGoasDILQ7PD6ZFr2tXplDO11Yrl3j2nCfRpkI89c+YuYPy1/c+1t6HevFaik\n"\
"NpD33KNz6pBYV72de2HX5Pl/Xe/70M/EYIacxxvtxvLWh34tXPWF/4vlNi5efxHN\n"\
"osytNlQHLLeqyIaB5UTjKqautincgG/jQLv/7kzyy7fhLMvZbbVcV2MJkblb/zIL\n"\
"wJUS44VAGpRe2E0MEr9pfpXPGvbLrAj+Zg3Url0hQM9CRukYe/VNSz+HSJhMtQ5G\n"\
"EjUCAwEAAaNgMF4wHwYDVR0jBBgwFoAU6A9jLLXf3oKAqLzSpk4TJ3OpSpMwHQYD\n"\
"VR0OBBYEFDUEt3Ab0HtnYxl52Vxnjsqz8jdQMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQChTQO/9i4PiYqrcfdl4iP2pBIo\n"\
"hg23r4hZfwzKQTcBhGCefyynStu3C9k/ptrNCTNt8iqUuOGju7LABSusBKC2VYIL\n"\
"Wn6DUrx/7Evj3SC9bb+yue0BSPQd75bFgUzYMapI9HIA0/0J+nn8Pv0Sg3/el60e\n"\
"CQ0vKf1P5XlVignj0bo7iNUtZsQBb2lpohLkkD+9OlcQ9tfhNzme10u+zLVktFxt\n"\
"X44b/T2bTx5rEKAtY5dZ6okEddsBnpP8yAyygoZp+zq9OvBUFdDIs+OY8njGyZSI\n"\
"HuayTy8IgdAoMabWwvAFvRQebArTiU6IxEn2kZDs+onbjrqZiGZOfbr2U4Mn\n"\
"-----END CERTIFICATE-----\n"

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate 
 * Authority) of the client certificate is used by the server for routing the 
 * device's initial request. (The device client certificate must always be 
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html, 
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 * 
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  NULL

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEApcSHTlFu1I7qzi6UlTH55XxKjWHPilKIXoBwpH2u8w6ab6b6\n"\
"T0f4r4utZoy45FeUtJf7huoaaSh7E3st/hTpihoahqwMgtDs8PpkWva1emUM7XVi\n"\
"uXePacJ9GmQjz1z5i5g/LX9z7W3od68VqKQ2kPfco3PqkFhXvZ17Ydfk+X9d7/vQ\n"\
"z8RghpzHG+3G8taHfi1c9YX/i+U2Ll5/Ec2izK02VAcst6rIhoHlROMqpq62KdyA\n"\
"b+NAu//uTPLLt+Esy9lttVxXYwmRuVv/MgvAlRLjhUAalF7YTQwSv2l+lc8a9sus\n"\
"CP5mDdSuXSFAz0JG6Rh79U1LP4dImEy1DkYSNQIDAQABAoIBAF+Zq/7679QeaERo\n"\
"kMBKhjhXKhfHpQ2883Cs2knDQjZi4aYqwokelMmI4IQX/DmUWOqeDC2OrZSgB/sA\n"\
"O1IhdV50F4A7kSuQmlWP0nizd44S4RXBcSJNVaREyimCPzTEBhb/ws/WhWEU1dDQ\n"\
"ZMlRizan+9M4crq0eEWeoR2YiTFp2RY2lLSs4yuoA7qlB2R5wt008I/K2bwphpQ5\n"\
"OJaVUvNhpKDuVUq1VNPdBwRyGukRdlQC/vw0TOItAIRkIt7Cy60T1riWAMQLLZcz\n"\
"k6eqDAWvJ634xnB49Q1NrOcugYSI3+QzqSoUXx4w9kCKr7Wp+aZutIyacOk0vhRm\n"\
"bdBvwIECgYEA2q87mNW3HFGNTOOaV+nUwYtPJ3GHdn7A8TI+rk6UWB2RIYVjJ/Vf\n"\
"gHQSV7XB6Xbq8n0XzoRON5P3HnpznkqOvEcPLuf2Ug69eQdLf1bfahvKL3A/D71N\n"\
"K/Gl3hWjBC9KlByDfbTs6IUMmAJr8i12aeVFhGh1qXk7EgWPnLL1Kh0CgYEAwg28\n"\
"whLpiDTgVxAIpM3h8ZM7UKhbWFFrquVr/rac2PGQeNEBOtszofU3ljgE1rC5VnQp\n"\
"mG5rD8cAlZ4RWSKdqOZT0vFmZBYJ0P3qmrXT6LIMjFRKMK4puKtAGSh+DeZ1+ZxL\n"\
"8Ae8ykVY11p1Qg7+/fvwC2MEkZNTLk1ZuxV1zPkCgYEAnibEjw9gUdaYvdaMtK+i\n"\
"8iXxpLDyKrwYhVa1BhJGLkOTxg5VW3yVCKzo5w3HozQhTiUxpmUAvCkCOsSMARoi\n"\
"h/9L97xB465NUM35x6noATD/07b1pEhfGzyznB1Bu7EH2n2UisDh5Hb0WKrHrmk6\n"\
"jfMFh3CUR3ApTCtBZS33J/ECgYAfkqqejQMwJSJHKBWv8suLSaBB/FJ4aS7ybEeI\n"\
"9t9IMO2HqsHfeKDK/iHgMBchczmEhnvqEDUdKQzASyqZbRdnzqnezWYSbL+GIHoW\n"\
"V/U1jBqcjm5Pw1aIdFyGe18fFdsmFLcKQ8gExQmyaEZhzBzS6DXjNGYe5XCIPQ+X\n"\
"b+NtyQKBgQCssgVoeBApJVb89X/nBFFBC5O9aM4ZgrQrPfyXzb/DmhG1nA1Zk8Dj\n"\
"mUKekCB9pTTKr+bElRFFTInItvPrqZtOuCZV5OXExda99d5ifyW+VVSQFSTVKk/5\n"\
"rVVn76beMcug2GID05+TAdwUHZI/8rOFnEampUe2VObNSjvtEuDm/A==\n"\
"-----END RSA PRIVATE KEY-----\n"

/* The constants above are set to const char * pointers defined in aws_demo_runner.c,
 * and externed here for use in C files.  NOTE!  THIS IS DONE FOR CONVENIENCE
 * DURING AN EVALUATION PHASE AND IS NOT GOOD PRACTICE FOR PRODUCTION SYSTEMS 
 * WHICH MUST STORE KEYS SECURELY. */
extern const char clientcredentialCLIENT_CERTIFICATE_PEM[];
extern const char* clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM;
extern const char clientcredentialCLIENT_PRIVATE_KEY_PEM[];
extern const uint32_t clientcredentialCLIENT_CERTIFICATE_LENGTH;
extern const uint32_t clientcredentialCLIENT_PRIVATE_KEY_LENGTH;

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
