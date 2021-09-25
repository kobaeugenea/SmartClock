#ifndef KEA_SC_STRINGUTILS_H
#define KEA_SC_SRTINGUTILS_H

#include <stdint.h>
 
typedef enum {
    kea_sc_StringUtils_ParseStatus_SUCCESS,
    kea_sc_StringUtils_ParseStatus_OVERFLOW,
    kea_sc_StringUtils_ParseStatus_UNDERFLOW,
    kea_sc_StringUtils_ParseStatus_INCONVERTIBLE
} kea_sc_StringUtils_ParseStatus;

typedef struct
{
    /* Convert string s to int out.
    *
    * @param[out] out The converted int. Cannot be NULL.
    *
    * @param[in] s Input string to be converted.
    *
    *     The format is the same as strtol,
    *     except that the following are inconvertible:
    *
    *     - empty string
    *     - leading whitespace
    *     - any trailing characters that are not part of the number
    *
    *     Cannot be NULL.
    *
    * @return Indicates if the operation succeeded, or why it failed.
    */
    kea_sc_StringUtils_ParseStatus (* const stringToInt8)(int8_t *out, char *s);
} kea_sc_StringUtils_n;
extern kea_sc_StringUtils_n const kea_sc_StringUtils;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define StringUtils kea_sc_StringUtils
#define ParseStatus kea_sc_StringUtils_ParseStatus
#define ParseStatus_SUCCESS kea_sc_StringUtils_ParseStatus_SUCCESS
#define ParseStatus_OVERFLOW kea_sc_StringUtils_ParseStatus_OVERFLOW
#define ParseStatus_UNDERFLOW kea_sc_StringUtils_ParseStatus_UNDERFLOW
#define ParseStatus_INCONVERTIBLE kea_sc_StringUtils_ParseStatus_INCONVERTIBLE
#endif


#endif