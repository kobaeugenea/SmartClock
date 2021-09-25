#ifndef KEA_SC_ERROR_SERVICE_H
#define KEA_SC_ERROR_SERVICE_H

#define MAX_ERROR_LENGTH 128

typedef struct {
    void (* const init)(void);
    void (* const put)(char errorFormat[MAX_ERROR_LENGTH], ...);
} kea_sc_ErrorService_n;
extern kea_sc_ErrorService_n const kea_sc_ErrorService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define ErrorService kea_sc_ErrorService 
#endif

#endif