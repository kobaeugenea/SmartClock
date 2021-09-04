#ifndef KEA_SC_MESSAGES_H
#define KEA_SC_MESSAGES_H

#include <stdint.h>

#include "service/kea_sc_DateS.h"

typedef uint8_t kea_sc_MessageS_MessageCode;

#define KEA_SC_MESSAGES_TOO_MANY_COMPONENTS_CODE 0
#define KEA_SC_MESSAGES_PIN_USED_CODE 1
#define KEA_SC_MESSAGES_COMPONENT_NOT_EXISTS 2
#define KEA_SC_MESSAGES_DISPLAY_NOT_EXISTS 3
#define KEA_SC_MESSAGES_DATE_TEMPLATE 4
#define KEA_SC_MESSAGES_CANNOT_CREATE_TASK 5
#define KEA_SC_MESSAGES_CANNOT_CREATE_SEMAPHORE 6
#define KEA_SC_MESSAGES_CANNOT_ALLOCATE_MEMORY 7
#define KEA_SC_MESSAGES_CANNOT_ALLOCATE_MEMORY 7
#define KEA_SC_MESSAGES_WRONG_DATE_FORMAT 8
#define KEA_SC_MESSAGES_WEBUI_DATE_TAB 9
#define KEA_SC_MESSAGES_WEBUI_DATE_TAB_NTP_SERVER 10
#define KEA_SC_MESSAGES_WEBUI_DATE_TAB_TIME_ZONE 11
#define KEA_SC_MESSAGES_WEBUI_WIFI_TAB 12
#define KEA_SC_MESSAGES_WEBUI_WIFI_TAB_NETWORK 13
#define KEA_SC_MESSAGES_WEBUI_WIFI_TAB_PASSWORD 14
#define KEA_SC_MESSAGES_WEBUI_SAVE_BUTTON 15
#define KEA_SC_MESSAGES_WEBUI_REBOOT_BUTTON 16
#define KEA_SC_MESSAGES_WEBUI_INFO_TAB 17
#define KEA_SC_MESSAGES_WEBUI_INFO_TAB_ALL_PARAMETERS 18
#define KEA_SC_MESSAGES_PARAM_VALUE_BIGGER_BUFFER 19
#define KEA_SC_MESSAGES_CANNOT_READ_PARAM 20
#define KEA_SC_MESSAGES_CANNOT_PARSE_STRING_TO_INT 21

typedef enum kea_sc_MessageS_Language {
    kea_sc_MessageS_Language_RUSSIAN,
    kea_sc_MessageS_Language_ENGLISH
} kea_sc_MessageS_Language;

void kea_sc_MessageS_init();

#ifdef __cplusplus
extern "C" {
#endif

char* kea_sc_MessageS_getTranslatedMessage(kea_sc_MessageS_MessageCode messageCode);

#ifdef __cplusplus
}
#endif

char* kea_sc_MessageS_getTranslatedCapitalDayOfWeek(kea_sc_DateS_DayOfWeek dayOfWeek);
char* kea_sc_MessageS_getTranslatedMonth(kea_sc_DateS_Month month);

#endif