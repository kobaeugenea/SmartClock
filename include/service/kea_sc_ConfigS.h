#ifndef KEA_SC_CONFIGS_H
#define KEA_SC_CONFIGS_H

#include "kea_sc_ComponentS.h"
#include "kea_sc_MessageS.h"

typedef struct kea_sc_ConfigS_MainDisplaySettings {
    kea_sc_ComponentSData pinsData;
} kea_sc_ConfigS_MainDisplaySettings;

typedef struct kea_sc_ConfigS_LanguageSettings {
    kea_sc_MessageS_Language language;
} kea_sc_ConfigS_LanguageSettings;

void kea_sc_ConfigS_init();

kea_sc_ConfigS_MainDisplaySettings kea_sc_ConfigS_getMainDisplaySettings();
void kea_sc_ConfigS_putMainDisplaySettings(kea_sc_ConfigS_MainDisplaySettings mainDisplaySettings);

kea_sc_ConfigS_LanguageSettings kea_sc_ConfigS_getLanguageSettings();
void kea_sc_ConfigS_putLanguageSettings(kea_sc_ConfigS_LanguageSettings mainDisplaySettings);

#endif