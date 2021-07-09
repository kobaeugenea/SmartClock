#ifndef KEA_SC_MESSAGES_H
#define KEA_SC_MESSAGES_H

#include <stdint.h>

typedef uint8_t kea_sc_MessageS_MessageCode;

#define KEA_SC_MESSAGES_TOO_MANY_COMPONENTS_CODE 0
#define KEA_SC_MESSAGES_PIN_USED_CODE 1
#define KEA_SC_MESSAGES_COMPONENT_NOT_EXISTS 2
#define KEA_SC_MESSAGES_DISPLAY_NOT_EXISTS 3

typedef enum kea_sc_MessageS_Language {
    kea_sc_MessageS_Language_RUSSIAN,
    kea_sc_MessageS_Language_ENGLISH
} kea_sc_MessageS_Language;

void kea_sc_MessageS_init();

char* kea_sc_MessageS_getTranslatedMessage(kea_sc_MessageS_MessageCode messageCode);

#endif