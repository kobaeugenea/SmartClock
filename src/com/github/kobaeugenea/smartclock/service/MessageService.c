#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/enum/Language.h"
#include <stdio.h>

static Language currentLanguage = Language_ENGLISH;

//NOTE: Please do not forget update array size when you add new values
                            //Russian                                               //Codes
static char *messages[][22] ={{"Количество компонентов должно быть меньше, чем %d", //0
                             "Пин %d уже используется",                             //1
                             "Компонент с %d id не существует",                     //2
                             "Запрошен %d дисплей, всего - %d",                     //3
                             "%s %d %s %d",                                         //4
                             "Невозможно создать задачу",                           //5
                             "Невозможно создать семафор",                          //6
                             "Невозможно выделить память",                          //7
                             "Неверный формат даты",                                //8
                             "Время",                                               //9
                             "NTP сервер",                                          //10
                             "Часовой пояс GMT",                                    //11
                             "Wi-Fi",                                               //12
                             "Сеть",                                                //13
                             "Пароль",                                              //14
                             "Сохранить",                                           //15
                             "Перезагрузить устройство",                            //16
                             "Информация",                                          //17
                             "Все параметры",                                       //18
                             "Длина значение параметра (%d) больше буффера (%d)",   //19
                             "Не могу получить параметр %s",                        //20
                             "Не могу получить число из строки '%s', код %d",       //21
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
                             "Wrong date format",                                   //8
                             "Time",                                                //9
                             "NTP server",                                          //10
                             "Time zone GMT",                                       //11
                             "Wi-Fi",                                               //12
                             "Network",                                             //13
                             "Password",                                            //14
                             "Save",                                                //15
                             "Reboot device",                                       //16
                             "Info",                                                //17
                             "All parameters",                                      //18
                             "Length of parameter value (%d) bigger than buffer (%d)",//19
                             "Cannot read parameter",                               //20
                             "Cannot parse '%s' to integer, code %d",               //21
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

static void init()
{
    
}

static char* getTranslatedMessage(kea_sc_MessageService_MessageCode messageCode) {
    return messages[currentLanguage][messageCode];
}

static char* getTranslatedCapitalDayOfWeek(DayOfWeek dayOfWeek) {
    return capitalDaysOfWeek[currentLanguage][dayOfWeek];
}

static char* getTranslatedMonth(Month month) {
    return months[currentLanguage][month];
}
kea_sc_MessageService_n const kea_sc_MessageService = {
    .init = init,
    .getTranslatedMessage = getTranslatedMessage,
    .getTranslatedCapitalDayOfWeek = getTranslatedCapitalDayOfWeek,
    .getTranslatedMonth = getTranslatedMonth
};