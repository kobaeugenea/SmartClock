#ifndef KEA_SC_WEBUIJ_H
#define KEA_SC_WEBUIJ_H

#include <stdint.h>

typedef enum {
    kea_sc_WebUIJ_ParamStatus_SUCCESS,
    kea_sc_WebUIJ_ParamStatus_ERROR,
} kea_sc_WebUIJ_ParamStatus;

#define KEA_SC_WEBUIJ_PARAM_NTP_SERVER "ntpServer"
#define KEA_SC_WEBUIJ_PARAM_TIME_ZONE "timeZone"
#define KEA_SC_WEBUIJ_PARAM_NETWORK_SSID "networkSsid"
#define KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD "networkPassword"

#ifdef __cplusplus
extern "C" {
#endif
void kea_sc_WebUIJ_startJob();
kea_sc_WebUIJ_ParamStatus kea_sc_WebUIJ_getParam(const char* paramName, char* buf, uint8_t bufLength);
#ifdef __cplusplus
}
#endif

#endif