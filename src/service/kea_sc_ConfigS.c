#include "service/kea_sc_ConfigS.h"

void kea_sc_ConfigS_init() {

}

kea_sc_ConfigS_MainDisplaySettings kea_sc_ConfigS_getMainDisplaySettings() {
    //TODO read from persistent memory
    kea_sc_ConfigS_MainDisplaySettings mainDisplaySettings = {
        .pinsData = kea_sc_ComponentS_init(18, 23, 5, -1, -1, "mainScreen")
    };
    return mainDisplaySettings;
}
void kea_sc_ConfigS_putMainDisplaySettings(kea_sc_ConfigS_MainDisplaySettings mainDisplaySettings) {
    //TODO write to persistent memory
}

kea_sc_ConfigS_LanguageSettings kea_sc_ConfigS_getLanguageSettings() {
    //TODO read from persistent memory
    kea_sc_ConfigS_LanguageSettings languageSettings = {
        .language = kea_sc_MessageS_Language_ENGLISH
    };
    return languageSettings;
}
void kea_sc_ConfigS_putLanguageSettings(kea_sc_ConfigS_LanguageSettings mainDisplaySettings) {
    //TODO write to persistent memory
}