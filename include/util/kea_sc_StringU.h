#ifndef KEA_SC_STRINGU_H
#define KEA_SC_SRTINGU_H

#include <stdint.h>
 
typedef enum {
    kea_sc_StringU_ParseStatus_SUCCESS,
    kea_sc_StringU_ParseStatus_OVERFLOW,
    kea_sc_StringU_ParseStatus_UNDERFLOW,
    kea_sc_StringU_ParseStatus_INCONVERTIBLE
} kea_sc_StringU_ParseStatus;

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
kea_sc_StringU_ParseStatus kea_sc_StringU_stringToInt8(int8_t *out, char *s);


#endif