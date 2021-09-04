#include "service/kea_sc_ConfigS.h"
#include "service/kea_sc_MessageS.h"
#include "service/kea_sc_ErrorS.h"
#include "job/kea_sc_WebUIJ.h"
#include "util/kea_sc_StringU.h"

static const uint8_t TIME_ZOME_BUFFER_SIZE = 4; //sign + 2 digits + \0

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNTPServer(char *buf, uint8_t bufLength)
{
    if (bufLength >= 1)
    {
        buf[0] = '\0'; //clean buffer
    }
    kea_sc_WebUIJ_getParam(KEA_SC_WEBUIJ_PARAM_NTP_SERVER, buf, bufLength);

    if(bufLength < 1 || buf[0] == '\0') {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), KEA_SC_WEBUIJ_PARAM_NTP_SERVER);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    return kea_sc_ConfigS_ParamStatus_SUCCESS;
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getTimeZone(int8_t *out)
{
    char buf[TIME_ZOME_BUFFER_SIZE];
    kea_sc_WebUIJ_getParam(KEA_SC_WEBUIJ_PARAM_TIME_ZONE, buf, TIME_ZOME_BUFFER_SIZE);
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
    if (bufLength >= 1)
    {
        buf[0] = '\0'; //clean buffer
    }
    kea_sc_WebUIJ_getParam(KEA_SC_WEBUIJ_PARAM_NETWORK_SSID, buf, bufLength);

    if(bufLength < 1 || buf[0] == '\0') {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), KEA_SC_WEBUIJ_PARAM_NETWORK_SSID);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    return kea_sc_ConfigS_ParamStatus_SUCCESS;
}

kea_sc_ConfigS_ParamStatus kea_sc_ConfigS_getNetworkPassword(char *buf, uint8_t bufLength)
{
    if (bufLength >= 1)
    {
        buf[0] = '\0'; //clean buffer
    }
    kea_sc_WebUIJ_getParam(KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD, buf, bufLength);

    if(bufLength < 1 || buf[0] == '\0') {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_READ_PARAM), KEA_SC_WEBUIJ_PARAM_NETWORK_PASSWORD);
        return kea_sc_ConfigS_ParamStatus_ERROR;
    }
    return kea_sc_ConfigS_ParamStatus_SUCCESS;
}