#ifndef KEA_SC_ERRORS_H
#define KEA_SC_ERRORS_H

#define MAX_ERROR_LENGTH 128

void kea_sc_ErrorS_put(char errorFormat[MAX_ERROR_LENGTH], ...);

#endif