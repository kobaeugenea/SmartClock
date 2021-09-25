#include "com/github/kobaeugenea/smartclock/service/ConfigService.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"
#include "com/github/kobaeugenea/smartclock/job/WebUI.h"
#include "com/github/kobaeugenea/smartclock/util/StringUtils.h"

#define KEA_SC_TIME_ZOME_BUFFER_SIZE 4 //sign + 2 digits + \0

static kea_sc_ConfigService_ParamStatus getStringParam(const char* paramName, char *buf, uint8_t bufLength) {
    if(bufLength < 1) {
        return kea_sc_ConfigService_ParamStatus_WRONG_OUTPUT_BUF_LENGTH;
    }
    buf[0] = '\0'; //clean buffer

    ParamStatus paramStatus = WebUI.getParam(paramName, buf, bufLength);

    if(paramStatus == ParamStatus_ERROR) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_READ_PARAM), paramName);
        return kea_sc_ConfigService_ParamStatus_ERROR;
    }
    if(buf[0] == '\0') {
        return kea_sc_ConfigService_ParamStatus_EMPTY;
    }

    return kea_sc_ConfigService_ParamStatus_SUCCESS;
}

static kea_sc_ConfigService_ParamStatus getNTPServer(char *buf, uint8_t bufLength)
{
    return getStringParam(WEBUI_PARAM_NTP_SERVER, buf, bufLength);
}

static kea_sc_ConfigService_ParamStatus getTimeZone(int8_t *out)
{
    char buf[KEA_SC_TIME_ZOME_BUFFER_SIZE] = {'\0'};
    ParamStatus paramStatus = WebUI.getParam(WEBUI_PARAM_TIME_ZONE, buf, KEA_SC_TIME_ZOME_BUFFER_SIZE);
    if(paramStatus == ParamStatus_ERROR) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_READ_PARAM), WEBUI_PARAM_TIME_ZONE);
        return kea_sc_ConfigService_ParamStatus_ERROR;
    }
    if(buf[0] == '\0') {
        return kea_sc_ConfigService_ParamStatus_EMPTY;
    }

    ParamStatus parseStatus = StringUtils.stringToInt8(out, buf);

    if(parseStatus != ParamStatus_SUCCESS) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_READ_PARAM), WEBUI_PARAM_TIME_ZONE);
        return kea_sc_ConfigService_ParamStatus_ERROR;
    }
    return kea_sc_ConfigService_ParamStatus_SUCCESS;
}

static kea_sc_ConfigService_ParamStatus getNetworkSSID(char *buf, uint8_t bufLength)
{
    return getStringParam(WEBUI_PARAM_NETWORK_SSID, buf, bufLength);
}

static kea_sc_ConfigService_ParamStatus getNetworkPassword(char *buf, uint8_t bufLength)
{
    return getStringParam(WEBUI_PARAM_NETWORK_PASSWORD, buf, bufLength);
}

kea_sc_ConfigService_n const kea_sc_ConfigService = {
    .getNTPServer = getNTPServer,
    .getTimeZone = getTimeZone,
    .getNetworkSSID = getNetworkSSID,
    .getNetworkPassword = getNetworkPassword
};