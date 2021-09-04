#include "service/kea_sc_ConfigS.h"
#include "service/kea_sc_MessageS.h"
#include "service/kea_sc_ErrorS.h"
#include "job/kea_sc_WebUIJ.h"
#include "util/kea_sc_StringU.h"

#define KEA_SC_TIME_ZOME_BUFFER_SIZE 4 //sign + 2 digits + \0

static kea_sc_ConfigS_ParamStatus getStringParam(const char* paramName, char *buf, uint8_t bufLength) {
    if(bufLength < 1) {
        return kea_sc_ConfigS_ParamStatus_WRONG_OUTPUT_BUF_LENGTH;
    }
    buf[0] = '\0'; //clean buffer

    kea_sc_WebUIJ_ParamStatus paramStatus = kea_sc_WebUIJ_getParam(paramName, buf, bufLength);

    if(paramStatus == kea_sc_WebUIJ_ParamStatus_ERROR) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), paramName);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    if(buf[0] == '\0') {
        return kea_sc_ConfigS_ParamStatus_EMPTY;
    }

    return kea_sc_ConfigS_ParamStatus_SUCCESS;
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNTPServer(char *buf, uint8_t bufLength)
{
    return getStringParam(KEA_SC_WEBUIJ_PARAM_NTP_SERVER, buf, bufLength);
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getTimeZone(int8_t *out)
{
    char buf[KEA_SC_TIME_ZOME_BUFFER_SIZE] = {'\0'};
    kea_sc_WebUIJ_ParamStatus paramStatus = kea_sc_WebUIJ_getParam(KEA_SC_WEBUIJ_PARAM_TIME_ZONE, buf, KEA_SC_TIME_ZOME_BUFFER_SIZE);
    if(paramStatus == kea_sc_WebUIJ_ParamStatus_ERROR) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), KEA_SC_WEBUIJ_PARAM_TIME_ZONE);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    if(buf[0] == '\0') {
        return kea_sc_ConfigS_ParamStatus_EMPTY;
    }

    int8_t timeZone;
    kea_sc_StringU_ParseStatus parseStatus = kea_sc_StringU_stringToInt8(&timeZone, buf);

    if(parseStatus != kea_sc_StringU_ParseStatus_SUCCESS) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), KEA_SC_WEBUIJ_PARAM_TIME_ZONE);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    return kea_sc_ConfigS_ParamStatus_SUCCESS;
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNetworkSSID(char *buf, uint8_t bufLength)
{
    return getStringParam(KEA_SC_WEBUIJ_PARAM_NETWORK_SSID, buf, bufLength);
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNetworkPassword(char *buf, uint8_t bufLength)
{
    return getStringParam(KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD, buf, bufLength);
}