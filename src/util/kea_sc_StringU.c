#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/kea_sc_StringU.h"
#include "service/kea_sc_MessageS.h"
#include "service/kea_sc_ErrorS.h"

kea_sc_StringU_ParseStatus kea_sc_StringU_stringToInt8(int8_t *out, char *s)
{
    char *end;
    if (s[0] == '\0' || isspace(s[0])){
        kea_sc_StringU_ParseStatus parseStatus = kea_sc_StringU_ParseStatus_INCONVERTIBLE;
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    errno = 0;
    long l = strtol(s, &end, 0);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT8_MAX || (errno == ERANGE && l == LONG_MAX))
    {
        kea_sc_StringU_ParseStatus parseStatus = kea_sc_StringU_ParseStatus_OVERFLOW;
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    if (l < INT8_MIN || (errno == ERANGE && l == LONG_MIN))
    {
        kea_sc_StringU_ParseStatus parseStatus = kea_sc_StringU_ParseStatus_UNDERFLOW;
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    if (*end != '\0')
    {
        kea_sc_StringU_ParseStatus parseStatus = kea_sc_StringU_ParseStatus_INCONVERTIBLE;
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    *out = l;
    return kea_sc_StringU_ParseStatus_SUCCESS;
}