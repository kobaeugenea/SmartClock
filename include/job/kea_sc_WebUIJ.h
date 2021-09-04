#ifndef KEA_SC_WEBUIJ_H
#define KEA_SC_WEBUIJ_H

#include <stdint.h>

#define KEA_SC_WEBUIJ_PARAM_NTP_SERVER "ntpServer"
#define KEA_SC_WEBUIJ_PARAM_TIME_ZONE "timeZone"
#define KEA_SC_WEBUIJ_PARAM_NETWORK_SSID "networkSsid"
#define KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD "networkPassword"

#ifdef __cplusplus
extern "C" {
#endif
void kea_sc_WebUIJ_startJob();
void kea_sc_WebUIJ_getParam(const char* paramName, char* buf, uint8_t bufLength);
#ifdef __cplusplus
}
#endif

#endif