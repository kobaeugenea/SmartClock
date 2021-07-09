#include "service/kea_sc_MessageS.h"

static kea_sc_MessageS_Language currentLanguage = kea_sc_MessageS_Language_ENGLISH;


                            //Russian                                               //Codes
static char *messages[][4] = {{"Количество компонентов должно быть меньше, чем %d", //0
                             "Пин %d уже используется",                             //1
                             "Компонент с %d id не существует",                     //2
                             "Запрошен %d дисплей, всего - %d",                           //3
                             },                    
                             //English
                            {"Amount of component should be less than %d",         //0
                             "%d pin already used by another component",           //1
                             "Component with %d id doesn't exist"                  //2
                             "Requested %d diplay, total - %d",                    //3
                             }};               

void kea_sc_MessageS_init()
{
    
}

char* kea_sc_MessageS_getTranslatedMessage(kea_sc_MessageS_MessageCode messageCode) {
    return messages[currentLanguage][messageCode];
}