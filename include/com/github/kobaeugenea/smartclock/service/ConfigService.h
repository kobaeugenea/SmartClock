#ifndef KEA_SC_CONFIGS_H
#define KEA_SC_CONFIGS_H

#include <stdint.h>

typedef enum {
    kea_sc_ConfigService_ParamStatus_SUCCESS,
    kea_sc_ConfigService_ParamStatus_ERROR,
    kea_sc_ConfigService_ParamStatus_EMPTY,
    kea_sc_ConfigService_ParamStatus_WRONG_OUTPUT_BUF_LENGTH,
} kea_sc_ConfigService_ParamStatus;

#define KEA_SC_CONFIG_DEFAULT_NTP_SERVER "pool.ntp.org"
#define KEA_SC_CONFIG_DEFAULT_TIME_ZONE 0
#define KEA_SC_CONFIG_MIN_TIME_ZONE -12
#define KEA_SC_CONFIG_MAX_TIME_ZONE 12

typedef struct {
    kea_sc_ConfigService_ParamStatus (*const getNTPServer)(char* buf, uint8_t bufLength);
    kea_sc_ConfigService_ParamStatus (*const getTimeZone)(int8_t *out);
    kea_sc_ConfigService_ParamStatus (*const getNetworkSSID)(char* buf, uint8_t bufLength);
    kea_sc_ConfigService_ParamStatus (*const getNetworkPassword)(char* buf, uint8_t bufLength);
} kea_sc_ConfigService_n;
extern kea_sc_ConfigService_n const kea_sc_ConfigService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define ConfigService kea_sc_ConfigService 
#define ParamStatus kea_sc_ConfigService_ParamStatus 
#define CONFIG_DEFAULT_NTP_SERVER KEA_SC_CONFIG_DEFAULT_NTP_SERVER 
#define CONFIG_DEFAULT_TIME_ZONE KEA_SC_CONFIG_DEFAULT_TIME_ZONE 
#define CONFIG_MIN_TIME_ZONE KEA_SC_CONFIG_MIN_TIME_ZONE 
#define CONFIG_MAX_TIME_ZONE KEA_SC_CONFIG_MAX_TIME_ZONE 
#define ParamStatus_SUCCESS kea_sc_ConfigService_ParamStatus_SUCCESS 
#define ParamStatus_ERROR kea_sc_ConfigService_ParamStatus_ERROR 
#define ParamStatus_EMPTY kea_sc_ConfigService_ParamStatus_EMPTY 
#define ParamStatus_WRONG_OUTPUT_BUF_LENGTH kea_sc_ConfigService_ParamStatus_WRONG_OUTPUT_BUF_LENGTH 
#endif


#endif