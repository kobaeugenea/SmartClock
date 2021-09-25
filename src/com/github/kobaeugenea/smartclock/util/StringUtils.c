#include "com/github/kobaeugenea/smartclock/util/StringUtils.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static kea_sc_StringUtils_ParseStatus stringToInt8(int8_t *out, char *s)
{
    char *end;
    if (s[0] == '\0' || isspace(s[0])){
        kea_sc_StringUtils_ParseStatus parseStatus = kea_sc_StringUtils_ParseStatus_INCONVERTIBLE;
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    errno = 0;
    long l = strtol(s, &end, 0);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT8_MAX || (errno == ERANGE && l == LONG_MAX))
    {
        kea_sc_StringUtils_ParseStatus parseStatus = kea_sc_StringUtils_ParseStatus_OVERFLOW;
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    if (l < INT8_MIN || (errno == ERANGE && l == LONG_MIN))
    {
        kea_sc_StringUtils_ParseStatus parseStatus = kea_sc_StringUtils_ParseStatus_UNDERFLOW;
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    if (*end != '\0')
    {
        kea_sc_StringUtils_ParseStatus parseStatus = kea_sc_StringUtils_ParseStatus_INCONVERTIBLE;
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_PARSE_STRING_TO_INT), s, parseStatus);
        return parseStatus;
    }
    *out = l;
    return kea_sc_StringUtils_ParseStatus_SUCCESS;
}

kea_sc_StringUtils_n const kea_sc_StringUtils = {
    .stringToInt8 = stringToInt8
};