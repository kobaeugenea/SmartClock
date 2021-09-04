#include "job/kea_sc_WebUIJ.h"
#include "service/kea_sc_MessageS.h"
#include "service/kea_sc_ErrorS.h"
#include "service/kea_sc_ConfigS.h"
#include "util/kea_sc_MemoryU.h"
#include <CRMui3.h>
#include <string.h>
#include "esp_log.h"

#define KEA_SC_WEBUI_TASK_PRIORIY 1
#define KEA_SC_WEBUI_STACK_DEPTH 2048
#define KEA_SC_WEBUI_PARAM_SAVE_BUTTON "saveButton"
#define KEA_SC_WEBUI_PARAM_REBOOT_BUTTON "rebootButton"

static CRMui3 crm;

static void reboot() {
    crm.espReboot();
}

static void webUiRun(void *pvParameter)
{
    while (1)
    {
        crm.run();
        if (crm.btnSwStatus())
        {
            crm.btnCallback(KEA_SC_WEBUI_PARAM_REBOOT_BUTTON, reboot);  // Check "reboot" SW button
        }
    }
}

static void update() 
{

}

static void interface()
{
    char *rebootButtonMessage = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_REBOOT_BUTTON);

    //Date
    crm.page(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_DATE_TAB));
    char *dateTabNtpServerMessage = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_DATE_TAB_NTP_SERVER);
    char *dateTabTimeZoneMessage = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_DATE_TAB_TIME_ZONE);
    crm.input({INPUT_TEXT, KEA_SC_WEBUIJ_PARAM_NTP_SERVER, dateTabNtpServerMessage, KEA_SC_CONFIGS_DEFAULT_NTP_SERVER});
    crm.range({KEA_SC_WEBUIJ_PARAM_TIME_ZONE, dateTabTimeZoneMessage, KEA_SC_CONFIGS_DEFAULT_TIME_ZONE, KEA_SC_CONFIGS_MIN_TIME_ZONE, KEA_SC_CONFIGS_MAX_TIME_ZONE, 1});
    crm.input({INPUT_BUTTON, KEA_SC_WEBUI_PARAM_REBOOT_BUTTON, rebootButtonMessage});

    //Network
    crm.page(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_WIFI_TAB));
    char *wifiTabNetworkMessage = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_WIFI_TAB_NETWORK);
    char *wifiTabPasswordMessage = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_WEBUI_WIFI_TAB_PASSWORD);
    crm.input({INPUT_TEXT, KEA_SC_WEBUIJ_PARAM_NETWORK_SSID, wifiTabNetworkMessage});
    crm.input({INPUT_TEXT, KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD, wifiTabPasswordMessage});
    crm.input({INPUT_BUTTON, KEA_SC_WEBUI_PARAM_REBOOT_BUTTON, rebootButtonMessage});
}

void kea_sc_WebUIJ_startJob()
{
    crm.begin(KEA_SC_APP_NAME, interface, update);
    crm.version(KEA_SC_APP_VERSION);
    kea_sc_MemoryU_xTaskCreate(webUiRun, "web_ui_task", KEA_SC_WEBUI_STACK_DEPTH, NULL, KEA_SC_WEBUI_TASK_PRIORIY, NULL);
}

extern "C" kea_sc_WebUIJ_ParamStatus kea_sc_WebUIJ_getParam(const char* paramName, char* buf, uint8_t bufLength) {
    if(!crm.isVarExists(paramName)) {
        if(bufLength > 0) {
            buf[0] = '\0';
        }
        return kea_sc_WebUIJ_ParamStatus_SUCCESS;
    }
    String param = crm.var(paramName);
    if(param.length() > bufLength - 1) { // -1 for \0 char
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_PARAM_VALUE_BIGGER_BUFFER), param.length(), bufLength);
        return kea_sc_WebUIJ_ParamStatus_ERROR;
    }
    strncpy(buf, param.c_str(), bufLength - 1);
    return kea_sc_WebUIJ_ParamStatus_SUCCESS;
}

