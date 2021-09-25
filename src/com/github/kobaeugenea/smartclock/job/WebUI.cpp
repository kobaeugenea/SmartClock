#include "com/github/kobaeugenea/smartclock/job/WebUI.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"
#include "com/github/kobaeugenea/smartclock/service/ConfigService.h"
#include "com/github/kobaeugenea/smartclock/util/MemoryUtils.h"

#include <CRMui3.h>
#include <string.h>
#include <esp_log.h>

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
    char *rebootButtonMessage = MessageService.getTranslatedMessage(MESSAGE_WEBUI_REBOOT_BUTTON);

    //Date
    crm.page(MessageService.getTranslatedMessage(MESSAGE_WEBUI_DATE_TAB));
    char *dateTabNtpServerMessage = MessageService.getTranslatedMessage(MESSAGE_WEBUI_DATE_TAB_NTP_SERVER);
    char *dateTabTimeZoneMessage = MessageService.getTranslatedMessage(MESSAGE_WEBUI_DATE_TAB_TIME_ZONE);
    crm.input({INPUT_TEXT, KEA_SC_WEBUI_PARAM_NTP_SERVER, dateTabNtpServerMessage, CONFIG_DEFAULT_NTP_SERVER});
    crm.range({KEA_SC_WEBUI_PARAM_TIME_ZONE, dateTabTimeZoneMessage, CONFIG_DEFAULT_TIME_ZONE, CONFIG_MIN_TIME_ZONE, CONFIG_MAX_TIME_ZONE, 1});
    crm.input({INPUT_BUTTON, KEA_SC_WEBUI_PARAM_REBOOT_BUTTON, rebootButtonMessage});

    //Network
    crm.page(MessageService.getTranslatedMessage(MESSAGE_WEBUI_WIFI_TAB));
    char *wifiTabNetworkMessage = MessageService.getTranslatedMessage(MESSAGE_WEBUI_WIFI_TAB_NETWORK);
    char *wifiTabPasswordMessage = MessageService.getTranslatedMessage(MESSAGE_WEBUI_WIFI_TAB_PASSWORD);
    crm.input({INPUT_TEXT, KEA_SC_WEBUI_PARAM_NETWORK_SSID, wifiTabNetworkMessage});
    crm.input({INPUT_TEXT, KEA_SC_WEBUI_PARAM_NETWORK_PASSWORD, wifiTabPasswordMessage});
    crm.input({INPUT_BUTTON, KEA_SC_WEBUI_PARAM_REBOOT_BUTTON, rebootButtonMessage});
}

static void startJob()
{
    crm.begin(KEA_SC_APP_NAME, interface, update);
    crm.version(KEA_SC_APP_VERSION);
    MemoryUtils.xTaskCreate(webUiRun, "web_ui_task", KEA_SC_WEBUI_STACK_DEPTH, NULL, KEA_SC_WEBUI_TASK_PRIORIY, NULL);
}

static kea_sc_WebUI_ParamStatus getParam(const char* paramName, char* buf, uint8_t bufLength) {
    if(!crm.isVarExists(paramName)) {
        if(bufLength > 0) {
            buf[0] = '\0';
        }
        return kea_sc_WebUI_ParamStatus_SUCCESS;
    }
    String param = crm.var(paramName);
    if(param.length() > bufLength - 1) { // -1 for \0 char
        ErrorService.put(MessageService.getTranslatedMessage(KEA_SC_MESSAGE_PARAM_VALUE_BIGGER_BUFFER), param.length(), bufLength);
        return kea_sc_WebUI_ParamStatus_ERROR;
    }
    strncpy(buf, param.c_str(), bufLength - 1);
    return kea_sc_WebUI_ParamStatus_SUCCESS;
}

kea_sc_WebUI_n const kea_sc_WebUI = {
    .startJob = startJob,
    .getParam = getParam
};

