#ifndef KEA_SC_ENUM_LANGUAGE_H
#define KEA_SC_ENUM_LANGUAGE_H

typedef enum {
    kea_sc_Language_RUSSIAN,
    kea_sc_Language_ENGLISH
} kea_sc_Language;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define Language kea_sc_Language
#define Language_RUSSIAN kea_sc_Language_RUSSIAN
#define Language_ENGLISH kea_sc_Language_ENGLISH
#endif

#endif