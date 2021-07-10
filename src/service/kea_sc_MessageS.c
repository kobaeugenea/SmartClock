#include "service/kea_sc_MessageS.h"
#include <stdio.h>

static kea_sc_MessageS_Language currentLanguage = kea_sc_MessageS_Language_ENGLISH;


                            //Russian                                               //Codes
static char *messages[][8] = {{"Количество компонентов должно быть меньше, чем %d", //0
                             "Пин %d уже используется",                             //1
                             "Компонент с %d id не существует",                     //2
                             "Запрошен %d дисплей, всего - %d",                     //3
                             "%s %d %s %d",                                         //4
                             "Невозможно создать задачу",                           //5
                             "Невозможно создать семафор",                          //6
                             "Невозможно выделить память",                          //7
                             },                    
                             //English
                            {"Amount of component should be less than %d",          //0
                             "%d pin already used by another component",            //1
                             "Component with %d id doesn't exist",                  //2
                             "Requested %d diplay, total - %d",                     //3
                             "%s %d of %s %d",                                      //4
                             "Cannot create task",                                  //5
                             "Cannot create semaphore",                             //6
                             "Cannot allocate memory",                              //7
                             }};

                                      //Russian
static char *capitalDaysOfWeek[][7] = {{
                                           "Понедельник",
                                           "Вторник",
                                           "Среда",
                                           "Четверг",
                                           "Пятница",
                                           "Суббота",
                                           "Воскресенье",
                                       },
                                       //English
                                       {
                                           "Monday",
                                           "Tuesday",
                                           "Wednesday",
                                           "Thursday",
                                           "Friday",
                                           "Saturday",
                                           "Sunday",
                                       }};

                           //Russian
static char *months[][12] = {{
                               "января",
                               "февраля",
                               "марта",
                               "апреля",
                               "мая",
                               "июня",
                               "июля",
                               "августа",
                               "сентября",
                               "октября",
                               "ноября",
                               "декабря",
                           },
                           //English
                           {
                               "January",
                               "February",
                               "March",
                               "April",
                               "May",
                               "June",
                               "July",
                               "August",
                               "September",
                               "October",
                               "November",
                               "December",
                           }};

void kea_sc_MessageS_init()
{
    
}

char* kea_sc_MessageS_getTranslatedMessage(kea_sc_MessageS_MessageCode messageCode) {
    return messages[currentLanguage][messageCode];
}

char* kea_sc_MessageS_getTranslatedCapitalDayOfWeek(kea_sc_DateS_DayOfWeek dayOfWeek) {
    return capitalDaysOfWeek[currentLanguage][dayOfWeek];
}

char* kea_sc_MessageS_getTranslatedMonth(kea_sc_DateS_Month month) {
    return months[currentLanguage][month];
}