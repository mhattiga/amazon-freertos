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
"MIICujCCAaICCQDgoiQfzyGt0DANBgkqhkiG9w0BAQsFADAnMQswCQYDVQQGEwJV\n" \
"UzEYMBYGA1UECgwPQm9vayBNYWtlcnMgSW5jMB4XDTE5MDUxNzIwMDM1NVoXDTIw\n" \
"MDkyODIwMDM1NVowFzEVMBMGA1UEAwwMMTIzLTEyMy0xMjM0MIIBIjANBgkqhkiG\n" \
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtGKML2pkMSQLSmeg+lwrO9E7+BTRCGveK9iw\n" \
"/sRDCBcW0L+1tk0rdWvman36rbntyvs7qBpR1ADM+TWhH5JEHqUNB1A8QfjA7nry\n" \
"NSr/N91bUxyp2hvDWWv3ubIZbOB05zteliX7czavuBStOY97MjsnzOzmvtk95p4J\n" \
"zAmhKcuRgtwWYJWWQ1g0d7EVgJomqUXAHAVufw/SLwM63QnvyMRfAhy9asyzTGCJ\n" \
"kp9sEM1s+ImtKic4f28AKXdNSQndXLEhsY3/2N9PqbndYwtbuLEpsvgBTdxav1/U\n" \
"OD7+OWa6pDQ2YZEmRoSo0rQuiaUEjxr17LR4agw+SlRp4gm7FwIDAQABMA0GCSqG\n" \
"SIb3DQEBCwUAA4IBAQBCrWOxj9kWFEz/00KlsK0UYMN/E34yGS76fHyhh1EFxka2\n" \
"2yAKKe6JMJ/eutjWQEByHQ2Gk8l4BShW6Kk6RGBrjOX2FqAdZ/tPKynkHjk9hwtg\n" \
"PAYDJ2wEwy1bfQ8JwYC7bIC/ISUcAP0zp5vnPjAz0SriCayRwvjg8Cp2QlwODj97\n" \
"mWtZtuLz4xbLulqTRfH/jeEshYloDJA/CdLbAWo1Fh06HXiY/a+J6UwEGSh3rm5l\n" \
"rjNVhtAOCyZ90Z8OAWqh8R2NiBNvz6P95mlhS3gMhGe0DKiyBziqRxcE83VqJAEM\n" \
"MZCZ98lAIKjLRJeHJKvcpqbG+Y9l9C0k3Ifkl464\n" \
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
"MIIEowIBAAKCAQEAtGKML2pkMSQLSmeg+lwrO9E7+BTRCGveK9iw/sRDCBcW0L+1\n" \
"tk0rdWvman36rbntyvs7qBpR1ADM+TWhH5JEHqUNB1A8QfjA7nryNSr/N91bUxyp\n" \
"2hvDWWv3ubIZbOB05zteliX7czavuBStOY97MjsnzOzmvtk95p4JzAmhKcuRgtwW\n" \
"YJWWQ1g0d7EVgJomqUXAHAVufw/SLwM63QnvyMRfAhy9asyzTGCJkp9sEM1s+Imt\n" \
"Kic4f28AKXdNSQndXLEhsY3/2N9PqbndYwtbuLEpsvgBTdxav1/UOD7+OWa6pDQ2\n" \
"YZEmRoSo0rQuiaUEjxr17LR4agw+SlRp4gm7FwIDAQABAoIBAAG1kVh9rJdenRDG\n" \
"bJsStoIpmGTgZZ6rzv4hXoP7fhschOXTezhQAOJq9FL8AJ0Wzu8GdGlCXpYgr9CI\n" \
"to8jBqw3qijwlLGXVtSrq5HfZ22zFkNyWRWs/6vgPweubVk/wzvRrzLDB1/vG7kl\n" \
"0QJjnqo6L0Vc1U7nphOCWdtqF/HabN8aRWWQJIvZ8oPGCv5gokTOl6/+rYzk1iTr\n" \
"te4stx/KxYHJAnLc3WXFpAvT6/Q/OkcFrPcTWYQLRppLQUIOUCzNMT77B4W+QALa\n" \
"A6XZQjDBV0mS6x+ftNmoYCt7xUvaTG4W4kANK6I46dbZo167LVh//ZpXWNzl4Kgx\n" \
"9XoCFOkCgYEA6kVkyDDQJ+x1MTRRrUyE4ZQfwgc+Emring2aMDxZK/cgnMEPPpkr\n" \
"QYadvrKC2yS1oGlutRKyi227L1Xw+hdTLuDNcLc/vMwy8bQKj6swc8zxma5i3BLW\n" \
"aCjeGGu/9ykSDI4koYBah3DC7yvX5FA725vouLG7/moa9fDyvKS3sxUCgYEAxR2q\n" \
"N5T1nilWSd74B/qF9O037Vl4z0USzf7XlS/iHD2wajfFQdw4N2JlShBbUPSs0CqJ\n" \
"3c+YtZBYccbN068199CouL0uT+wzRS75tnu09sF7HQnbWcYEg/U6fMjPgT3YEUaT\n" \
"W5r1ndk9yJb/ptNcwtkWKiFutG/EHq7fi3MX8HsCgYBsXmVcZZgkn7EmbblKnRbq\n" \
"8oYuTwNbqa3ixxAIOCJXwB2J5ZSTtG7aBNd7m0AE91o9NghMIrYM4Vmxb+PlDF0i\n" \
"VkMyXNJTF3KJdGteQiZLqwYnvQ9mFiCwVhdG3LEUOB9tR2OSgble5b6GvJVFvAe0\n" \
"cs6YgT8hVRvboPXoZZnEcQKBgQCCkULWLGqCCJmqtvIOvuiKs7NvGewHR5bMMrl0\n" \
"jdI1qLs5sJWOKaRnM1sqsyj5uAjcnsDR15gs9F9RhkGCrbWO4H1SWaXatPfFJPet\n" \
"48WcCc9WDdhpX9xP2FmUnKOu1VtRHjGv5TY7B9KAE11mkO0J+ChRYfHlvX7oYCed\n" \
"RHCgDwKBgDjkxc3wpHWTOn+UYIM0Z+5eepuNah8NA6ey+biw+ZKXmX0LVnNBzpv9\n" \
"LgA+uZv88Et170baDL9RNg/kvX8aXCfzPfrSXqzRcy/ZgsdXbB7DgDDxVC9aJ7nY\n" \
"sZEDdRftzeUxlEmT4w4WpDQjr/IUYPWdzhSWxhFm57/M/UfyEtCM\n" \
"-----END RSA PRIVATE KEY-----\n"

#define key_FIRST_CSR_PEM \
"-----BEGIN CERTIFICATE REQUEST-----\n" \
"MIICrzCCAZcCAQAwajELMAkGA1UEBhMCVVMxDjAMBgNVBAgMBVRleGFzMQ8wDQYD\n" \
"VQQHDAZEYWxsYXMxDDAKBgNVBAoMA0FXUzERMA8GA1UECwwIRGV2IFRlYW0xGTAX\n" \
"BgNVBAMMEGlvdF9jZXJ0X2dlbl9kZXYwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw\n" \
"ggEKAoIBAQC0YowvamQxJAtKZ6D6XCs70Tv4FNEIa94r2LD+xEMIFxbQv7W2TSt1\n" \
"a+Zqffqtue3K+zuoGlHUAMz5NaEfkkQepQ0HUDxB+MDuevI1Kv833VtTHKnaG8NZ\n" \
"a/e5shls4HTnO16WJftzNq+4FK05j3syOyfM7Oa+2T3mngnMCaEpy5GC3BZglZZD\n" \
"WDR3sRWAmiapRcAcBW5/D9IvAzrdCe/IxF8CHL1qzLNMYImSn2wQzWz4ia0qJzh/\n" \
"bwApd01JCd1csSGxjf/Y30+pud1jC1u4sSmy+AFN3Fq/X9Q4Pv45ZrqkNDZhkSZG\n" \
"hKjStC6JpQSPGvXstHhqDD5KVGniCbsXAgMBAAGgADANBgkqhkiG9w0BAQsFAAOC\n" \
"AQEAREcubais4bE+AMUcSAr/tx6I28GSCPv+NJqqBAgm9ExnCxw32UGFONqppWgG\n" \
"u/MFsEGCVnxYbqRiqvgPXtCiXgVUJ7ffyIEEnx728qYHMSguSSJ9I4Yg0HzZkVMw\n" \
"nIkQBCcyKy2lkCGLvpU/Gd4PszRAUMM9py0r93eVgOq/0LBOmWaWtI/HE+CkDCNu\n" \
"U8VWwYBtmgMhfVQy+EgWpVACraYjjeSrKc0z/+oyzvbEPTKrGGszSr0w9ieUQPFQ\n" \
"ENF6aG7t7E7K592OtpHR/c43pf74U/HbgNGl1teT0OE+dq185vblZXXhzDc40p8G\n" \
"/kx1+tXJXTL5FvUK7X4bfe4WCw==\n" \
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
"MIICujCCAaICCQDgoiQfzyGt0DANBgkqhkiG9w0BAQsFADAnMQswCQYDVQQGEwJV\n" \
"UzEYMBYGA1UECgwPQm9vayBNYWtlcnMgSW5jMB4XDTE5MDUxNzIwMDM1NVoXDTIw\n" \
"MDkyODIwMDM1NVowFzEVMBMGA1UEAwwMMTIzLTEyMy0xMjM0MIIBIjANBgkqhkiG\n" \
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtGKML2pkMSQLSmeg+lwrO9E7+BTRCGveK9iw\n" \
"/sRDCBcW0L+1tk0rdWvman36rbntyvs7qBpR1ADM+TWhH5JEHqUNB1A8QfjA7nry\n" \
"NSr/N91bUxyp2hvDWWv3ubIZbOB05zteliX7czavuBStOY97MjsnzOzmvtk95p4J\n" \
"zAmhKcuRgtwWYJWWQ1g0d7EVgJomqUXAHAVufw/SLwM63QnvyMRfAhy9asyzTGCJ\n" \
"kp9sEM1s+ImtKic4f28AKXdNSQndXLEhsY3/2N9PqbndYwtbuLEpsvgBTdxav1/U\n" \
"OD7+OWa6pDQ2YZEmRoSo0rQuiaUEjxr17LR4agw+SlRp4gm7FwIDAQABMA0GCSqG\n" \
"SIb3DQEBCwUAA4IBAQBCrWOxj9kWFEz/00KlsK0UYMN/E34yGS76fHyhh1EFxka2\n" \
"2yAKKe6JMJ/eutjWQEByHQ2Gk8l4BShW6Kk6RGBrjOX2FqAdZ/tPKynkHjk9hwtg\n" \
"PAYDJ2wEwy1bfQ8JwYC7bIC/ISUcAP0zp5vnPjAz0SriCayRwvjg8Cp2QlwODj97\n" \
"mWtZtuLz4xbLulqTRfH/jeEshYloDJA/CdLbAWo1Fh06HXiY/a+J6UwEGSh3rm5l\n" \
"rjNVhtAOCyZ90Z8OAWqh8R2NiBNvz6P95mlhS3gMhGe0DKiyBziqRxcE83VqJAEM\n" \
"MZCZ98lAIKjLRJeHJKvcpqbG+Y9l9C0k3Ifkl464\n" \
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
