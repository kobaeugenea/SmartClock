#ifndef KEA_SC_CONFIGS_H
#define KEA_SC_CONFIGS_H

#include <stdint.h>

typedef enum {
    kea_sc_ConfigS_ParamStatus_SUCCESS,
    kea_sc_ConfigS_ParamStatus_ERROR,
} kea_sc_ConfigS_ParamStatus;

#define KEA_SC_CONFIGS_DEFAULT_NTP_SERVER "pool.ntp.org"
#define KEA_SC_CONFIGS_DEFAULT_TIME_ZONE 0
#define KEA_SC_CONFIGS_MIN_TIME_ZONE -12
#define KEA_SC_CONFIGS_MAX_TIME_ZONE 12

//All settings changes handled by CRM framework for now
//void kea_sc_ConfigS_setNTPServer(char* ntpServer);
//void kea_sc_ConfigS_setTimeZone(int8_t timeZone);
//void kea_sc_ConfigS_setNetworkSSID(char* networkSSID);
//void kea_sc_ConfigS_setNetworkPassword(char* networkPassword);

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNTPServer(char* buf, uint8_t bufLength);
kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getTimeZone(int8_t *out);
kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNetworkSSID(char* buf, uint8_t bufLength);
kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNetworkPassword(char* buf, uint8_t bufLength);

#endif