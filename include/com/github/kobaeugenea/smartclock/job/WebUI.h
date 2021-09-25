#ifndef KEA_SC_WEBUI_H
#define KEA_SC_WEBUI_H

#include <stdint.h>

typedef enum {
    kea_sc_WebUI_ParamStatus_SUCCESS,
    kea_sc_WebUI_ParamStatus_ERROR,
} kea_sc_WebUI_ParamStatus;

#define KEA_SC_WEBUI_PARAM_NTP_SERVER "ntpServer"
#define KEA_SC_WEBUI_PARAM_TIME_ZONE "timeZone"
#define KEA_SC_WEBUI_PARAM_NETWORK_SSID "networkSsid"
#define KEA_SC_WEBUI_PARAM_NETWORK_PASSWORD "networkPassword"

typedef struct {
    void (* const startJob)(void);
    kea_sc_WebUI_ParamStatus (*const getParam)(const char* paramName, char* buf, uint8_t bufLength);
} kea_sc_WebUI_n;
extern kea_sc_WebUI_n const kea_sc_WebUI;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define WebUI kea_sc_WebUI 
#define ParamStatus kea_sc_WebUI_ParamStatus 
#define ParamStatus_SUCCESS kea_sc_WebUI_ParamStatus_SUCCESS 
#define ParamStatus_ERROR kea_sc_WebUI_ParamStatus_ERROR 
#define WEBUI_PARAM_NTP_SERVER  KEA_SC_WEBUI_PARAM_NTP_SERVER 
#define WEBUI_PARAM_TIME_ZONE KEA_SC_WEBUI_PARAM_TIME_ZONE 
#define WEBUI_PARAM_NETWORK_SSID KEA_SC_WEBUI_PARAM_NETWORK_SSID 
#define WEBUI_PARAM_NETWORK_PASSWORD KEA_SC_WEBUI_PARAM_NETWORK_PASSWORD 
#endif

#endif