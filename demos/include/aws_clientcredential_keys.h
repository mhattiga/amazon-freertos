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
 * Connect to demo server, not the normal AWS IoT Endpoint
 */
#define DEMO_SERVER_AWS_CLIENT_CREDENTIAL_KEYS


#ifdef DEMO_SERVER_AWS_CLIENT_CREDENTIAL_KEYS
/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUayfi2INFLe2Pu1REXy3ysGI3yFQwDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MDUxNzA0Mjk0\n" \
"MFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJlKbGEBYOD1ju5jV9JT\n" \
"3JTCxGPxTMmLXwG3zNoK8H3JoD6ZiURJZktH8+XGfBRMYua9gLWTmBP4I9Fju4FP\n" \
"keBs+7SxU2MqUlurfcH5uKrDGYMhPC8jYZfnmzUpT+ZrUXDtBJCWWrYYyWsRueoM\n" \
"Fwrijmut9qGa+ZPjN61NouSEkK4PAX/Y84caFbGycqPw4iWMEWPO85ePhM//zms9\n" \
"TlILz6LWbbD2AsrpaTkWUN83LBGxSZV2/trQQ/kO4Z+kaVDiATxAK0NzLTISDmRu\n" \
"PR3cJVWhlKgspgYsiHkytcJ9Psmbqc9t+eJ4xBbsmQNo8uP/hBri4ufAfJ/to352\n" \
"mpUCAwEAAaNgMF4wHwYDVR0jBBgwFoAUwa+FfTwPlSDD873oGiYLJdJTa/gwHQYD\n" \
"VR0OBBYEFIbiTxRoYV7l2AU3NsUPfFU4TusYMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCBafSIgfeLGVr5FMvEhc2j7t77\n" \
"H6AVOvmSDPCBkJ6iaCBycCBj64ue4MVPyuhxnHAFnF5g8PtwVVxy+W/7xThpcCTn\n" \
"iMFPLH5NfTURDSbJsAw27EzVnXctDGiutAO6a9ZCzYhNzTfkypfRVIZEMQu1EVyK\n" \
"sBLB8gxif/UHWMn2yOVMKG5AOO1lW1aY+csn91SE46IIRSqXnDwALNMZrCMroWfe\n" \
"ZPh9XaN9mZJckvHIAsucDvuWXnMKmnynG/thFj1Z/gGHPSrE15gXfS/oiLfXGpLR\n" \
"JRjXQRQgJ8u+SqgqGU92HdWADLUj3ulqRNJIAmodYqWRGl2KvbKMbY6IFjXX\n" \
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
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEAmUpsYQFg4PWO7mNX0lPclMLEY/FMyYtfAbfM2grwfcmgPpmJ\n" \
"RElmS0fz5cZ8FExi5r2AtZOYE/gj0WO7gU+R4Gz7tLFTYypSW6t9wfm4qsMZgyE8\n" \
"LyNhl+ebNSlP5mtRcO0EkJZathjJaxG56gwXCuKOa632oZr5k+M3rU2i5ISQrg8B\n" \
"f9jzhxoVsbJyo/DiJYwRY87zl4+Ez//Oaz1OUgvPotZtsPYCyulpORZQ3zcsEbFJ\n" \
"lXb+2tBD+Q7hn6RpUOIBPEArQ3MtMhIOZG49HdwlVaGUqCymBiyIeTK1wn0+yZup\n" \
"z2354njEFuyZA2jy4/+EGuLi58B8n+2jfnaalQIDAQABAoIBAFF9lxAaw33UDR/9\n" \
"//n4SxNqVy0qYj/ir6ciJuzjU+YLAf1FcguzWYY7whUs51mDIjC4HWxqAjbbe28d\n" \
"LdkYi9xbE5SDkGjvXskM6dXtA5cEENP9HxmQHZm7rm8cfzVnZ+w4lGypAaA8nRcm\n" \
"XUdnFfjbaAsmeC6BTJyp9jdTRn1kiUWTDyR8q2rAMVruEAgEloO/2iBTfULzgwkn\n" \
"GUPYWme3fV/CNSXrrwfK1RzL/8VKLUdxPAXtfHy07jMviRPO9/KCZL1yYjDQnd2T\n" \
"W2MoaPB0Y+ZBk9QLa5mtdXHbEGxYlNP8aAd2Kji3EX9zrew2bu0lMdwVumx6V7B2\n" \
"3T5UzyECgYEAxtrfcxTsFv/2l5IuJ/AJJg/sH/XAR3yGKM+2DsnquYEDUUnBCenB\n" \
"q5ALm/DBNh3gx7XT/fKDLR1eaAi6YpnIvt4uHl+DJ35yo5RiFO5ke4I9lJi62tC9\n" \
"Wy45AgpuBIkLnQJB8gpFmvBRv0b1vZeiNn1DC5g9vDHZjQFE1wP0w9cCgYEAxVeI\n" \
"hOXuGLnXg81Xp1vfhA/ROAbpIK8L5t8AT5FwdLhyrVI1ggzqPN6fR43OSBFEnuUT\n" \
"LIvl/M/VW38/icFvLv4tdHgMqxnsRGIDf39MRL8VzdpPsnPNlTmzGvt9uXVWHOVD\n" \
"DpBxTugIQk9tNOO4bbktsbJhRI5daXTRBe4eR3MCgYBO0gjJ+9wMzc53i9jBudJW\n" \
"hO8qR+W8MC6ZVKOsPvrMJsgi22IpxL8gessvN4HOKo+jeX4a5Zp7Mm3uPK9sT9qT\n" \
"VUvgfClnaSaVkkZCV6/6iMhR8yv1edHkp3CvT2UGZS/2PyPWhZ3LaUBt2fmj+cux\n" \
"X3tIyEKIKxY5Xuxjccz+JwKBgQC3LW5Cdi+RcgfzhwrDBYuvSQNab0e8l9+DWSIv\n" \
"uX/aSE/iRDn40sYm5DqTL7T3vlek6lvm8KD2D3Erci1nUE9FHpjQ0JJpzDE8tIIs\n" \
"udvwwDKcFvX9XnLI/nsbI7BrEthxD/ozra4PoV/xNUrYWjyaVNZuaHbTLRbWSaGw\n" \
"UHx4swKBgQCr1RJBOkDhkrMvilo2CRqpFgCtI1EI5o3P9X4+L3YEUaeoRGx1wFwc\n" \
"RAo5NCCSCtGb4d3kvuZsY7u7WLYwPYgUDScWl+okuNKnway/BEpQCvwm12gteiqb\n" \
"kM24y9bHDj4dKB3VyhM5a54ULekQBWMbnarn+pM4fIjRfJHVvysiBw==\n" \
"-----END RSA PRIVATE KEY-----\n"

#define key_FIRST_CSR_PEM \
"-----BEGIN CERTIFICATE REQUEST-----\n" \
"MIICqzCCAZMCAQAwZjELMAkGA1UEBhMCVVMxDjAMBgNVBAgMBVRleGFzMQ8wDQYD\n" \
"VQQHDAZEYWxsYXMxDDAKBgNVBAoMA0FXUzERMA8GA1UECwwIRGV2IFRlYW0xFTAT\n" \
"BgNVBAMMDDEyMy0xMjMtMTIzNDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\n" \
"ggEBAOpinr1O92o8tyvBQpVgUOKLF6RcCM5nD68ipWmS9RJCJFH3qognivS/iy6a\n" \
"zRcySrq95z1WHelk/gicKAUrZ8Q/DXd8J9DZzgzY+mVi1W63eOsJspWHpuAEeB7y\n" \
"EseO1n+eoUpjjpXm1jHKrGiSDgc5FM0H+GKcA5sj4LWV44Oam4KCtdIDfNP1Zrzw\n" \
"3Z55UT3p5AiGj/N6ZEGkvOGJFpkwtP4gnwlwYYYClpWFXTaK+y49gp5JgjEWkCvA\n" \
"HUaq+nMXboplKC4//rPXcMUiTkKEov6A8svbYhpztSvdH34p0/VJYTtI5M8KypGJ\n" \
"e09wPPrCYn9dKuHD1jCa94DtNqsCAwEAAaAAMA0GCSqGSIb3DQEBCwUAA4IBAQAr\n" \
"UFzTT9yMWxxuSW1l+8gtAQcAY+ZtxtQ3S0YL5+Tkxn3Fnx25A1oMcAYsp7Iy4p0P\n" \
"izePKxqRQSv6p2i69sASI1wAl3Lv+XKuw5LB0CmcsEuvkS10q/JDWakC8jGiy+Po\n" \
"wdtmWVcl08YhGxt9BA76diL8sGY7GL8rfHWynxxgNFL06OJy8f3GHJKZlD/Iusai\n" \
"56hkzOebrXtT7+jLdZpQvV2s6TfEP+PzuRp3iFOAJ/6YkqjZrVwP6Rh2v+MKtaRw\n" \
"/os1DCpxKbOs+tq2lDEXjDKvWn1HKRD3U86fiz1PZxPVtSF98zjkrcB+JNDK3315\n" \
"B9k09PUzNEE7r9Epfrex\n" \
"-----END CERTIFICATE REQUEST-----\n" 

#define SERIAL_NUMBER "asdf110ab22Q09iw8"

#else 
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
"MIIDWjCCAkKgAwIBAgIVAIrfmFfs6HKM3xB57ctZELPx3VnkMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTA1MTUwMzE3\n"\
"MTJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4V7Xeb4PxDxUvhOET\n"\
"BwBJ/RGRS/EAllSpDnbKDJMoBRAovkfr520XTVggO8lFF3AgZuIMsMDzUTPKzsPF\n"\
"zt1vEb5zW2yU+X6QIbHjWBsy0t2qKIxoPrMbA2P55fG5Vnhw6Jb2UvnPlxe0SjBM\n"\
"QPPGrBm7buAjypgWgoQdr4zi0p50lVuNvp4iJLAH9vab03IQN/YUPnLaahWQRQ+D\n"\
"FIVsmawocu2ODcQtFkCQh+C3CH69z+bNfylsT+Rx+oC0HmxHrnPW+sGPKbY/tjjz\n"\
"5IW2yR+7Ufwa2D7JihCPCLy9N6FJlOhkCmshfRPwqndEhsUyMDo3bt/M4FP1Oelx\n"\
"czCjAgMBAAGjYDBeMB8GA1UdIwQYMBaAFM41T3f90P1P+hTzz3laM9Su/6ZtMB0G\n"\
"A1UdDgQWBBQrxJLk8UNfJKUiHMSyaJkLQOROBDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYFacKK+3nDv7gPd1M1Tr4uHg\n"\
"bplgdAflkgrJ8oHGfzTKcmGVvBHe6UXrzG5yWCb/Z9VqWAuhTp1MzqOm0h9okDRJ\n"\
"SokaH5RNpq0wIgw4/MS4yq6Ck9jDOZG5ibWaedev1yg0KZLHAiQ37zZvcukviWOC\n"\
"FMru6LPceeOUOX7q5z/qEgeuKtIA0LA0jUxGy46vQhgL6SXwdaD5rfhWOvNBFA3i\n"\
"WkAn9fNHTkut+GA6/fBHdknGmled1FqDjXJ5zR6v0lWJSZOjpI+m5ToK/LclGMM7\n"\
"k+7dJmgzhfJSBATnrUN93UmTFVMRctvkJESxkmDSBsJnEEFYIRWivYKQVExlFg==\n"\
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
"MIIEowIBAAKCAQEAuFe13m+D8Q8VL4ThEwcASf0RkUvxAJZUqQ52ygyTKAUQKL5H\n"\
"6+dtF01YIDvJRRdwIGbiDLDA81Ezys7Dxc7dbxG+c1tslPl+kCGx41gbMtLdqiiM\n"\
"aD6zGwNj+eXxuVZ4cOiW9lL5z5cXtEowTEDzxqwZu27gI8qYFoKEHa+M4tKedJVb\n"\
"jb6eIiSwB/b2m9NyEDf2FD5y2moVkEUPgxSFbJmsKHLtjg3ELRZAkIfgtwh+vc/m\n"\
"zX8pbE/kcfqAtB5sR65z1vrBjym2P7Y48+SFtskfu1H8Gtg+yYoQjwi8vTehSZTo\n"\
"ZAprIX0T8Kp3RIbFMjA6N27fzOBT9TnpcXMwowIDAQABAoIBAAg4EOnL+wwCaiVm\n"\
"PUrF4yNpXyElS6eFDF1FQdKcYOtF3oSSh05jUR/a2PUG9WBZPSyUqbt7Hf87PZ3r\n"\
"PhtRr9nF5sHp75tszFHMzsueIAhSEoQFrszvDrlDm2+G6xIiYthV5nUxGeZBjFMD\n"\
"g8fClZvkDHmo5eFypPlL9GwGaberLO9WaESp5z5XP2TXGh6Y3yTqqnkMplvoYYsq\n"\
"DCmNv3QND8tU+Fo8LIipO6WtmKC84Muyouj1UiyH0Ob5spyFIqqSeKgokhem8tEW\n"\
"x+MyZRg6fPHGBFygD/biBm21bhGIO3uTkpSP/K7nCxRrfYcJgQ6mCNrbmUp+Q3c6\n"\
"yqTgg1ECgYEA6DLOegftn4woR8Bd9Ud5P3niyxF5bkab4Y2kKbZ0oLzdmgQwLUDK\n"\
"45xDWVF17XDuDwnW8ZBNR814yEpzMADb6PNFLvbsisTedUINm3nNhEC7mziKSZdH\n"\
"EfMeGX7bkJUeyl0MaL7sAqhjRd82wj0x6GqakuCx61YmuciH+xehLV8CgYEAyz0a\n"\
"fyEMZywby5+EEdOm97slYsGp6QTCVgsTM6INq2gGBz5NSswTf/Hq4bwR7Gkw59rr\n"\
"8DFvSQPE78D4i45PYCK5PO9eF+55S9ny0uv1sBpysYUmIV+b/L5qzIHogTr+pHoF\n"\
"PkZy7nC2zkpZbaq5QbHC55E4/9hc6cUdtDS/Pz0CgYEAiYsW/fhWTO00KxSLU7Dr\n"\
"5KrpqgqG2Mjgq6JAfSkEOvbFeedDNnsr89nrlywG5AjCK4xTk7I75O2Uv2hChUvs\n"\
"+DeqYqCIC8eEUwc2kkN7dvz1ZIQAfokq4zoVOVsI6sM6gvrNT/rQSN7AN3J6uGKR\n"\
"frAvMhQBsHrO47wiuJ0Nr5cCgYBOhhA7uCAbqK4gkUQswxLKulLqghrMvhr7tZG4\n"\
"rE8Nv8Y8fDTOxmRuVaDDkK94IPhVTH9GMUNm+X7Yhz1AZj6CzUe2pGE9a9UPmmi4\n"\
"V5R4cu+HaQNfd5pEH6oR08tqSsnh8IcgFYYIXCI1OAKvXXvwRucgIzrbltPnOlKM\n"\
"sqiFnQKBgAkEEdLjNw0CtOsoaoV8TLukgiwWanE9yRSZyvs8ROsad9OtcQq9WVdZ\n"\
"KzfLPBV+Zp8kUMtgQ1si1MGJzdEA3y/o5WNDKOz1NcXToGrhygiUxEfj7JJpub5j\n"\
"JCR5XFvR9qMaRM090hyfRGnfdBS17ZyUBTszdRI5VoK/v2F5F1mc\n"\
"-----END RSA PRIVATE KEY-----\n"

#endif

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
