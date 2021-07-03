#include "service/kea_sc_MessageS.h"

static kea_sc_MessageS_Language currentLanguage = kea_sc_MessageS_Language_ENGLISH;


                            //Russian                                              //Codes
static char *messages[][2] = {{"Количество компонентов должно быть меньше, чем %d", //0
                             "Пин %d уже используется"},                           //1
                             //English
                            {"Amount of component should be less than %d",         //0
                             "%d pin already used by another component"}};         //1

void kea_sc_MessageS_init(kea_sc_MessageS_Language language)
{
    currentLanguage = language;
}

char* kea_sc_MessageS_getTranslatedMessage(kea_sc_MessageS_MessageCode messageCode) {
    return messages[currentLanguage][messageCode];
}