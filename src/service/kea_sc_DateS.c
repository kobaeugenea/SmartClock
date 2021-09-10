#include "service/kea_sc_DateS.h"
#include "service/kea_sc_ConfigS.h"

#include <esp_sntp.h>
#include "esp_log.h"

#define DAYS_IN_WEEK 7
#define NTP_SERVER_NAME_LENGTH_MAX 32

static int8_t timeZone = 0;
static char ntpServer[NTP_SERVER_NAME_LENGTH_MAX];


kea_sc_DateS_Date kea_sc_DateS_Date_unixEpoch = {
    .sec = 0,
    .min = 0,
    .hour = 0,
    .day = 1,
    .month = kea_sc_DateS_Month_JAN,
    .year = 1970,
    .dayOfWeek = kea_sc_DateS_DayOfWeek_THU,
};



void kea_sc_DateS_init() {
    sntp_setoperatingmode(SNTP_OPMODE_POLL);

    kea_sc_ConfigS_ParamStatus ntpServerParamStatus = kea_sc_ConfigS_getNTPServer(ntpServer, NTP_SERVER_NAME_LENGTH_MAX);
    if (ntpServerParamStatus == kea_sc_ConfigS_ParamStatus_SUCCESS) {
        sntp_setservername(0, ntpServer);
    }

    kea_sc_ConfigS_ParamStatus timeZoneParamStatus = kea_sc_ConfigS_getTimeZone(&timeZone);
    if (timeZoneParamStatus == kea_sc_ConfigS_ParamStatus_SUCCESS) {
        char timeZoneString[9];
        int8_t timeZoneOpposite = timeZone * -1; // Seems to be bug in setenv as opposite time zone should be passed for correct work
        sprintf(timeZoneString, "GMT%s%d", timeZoneOpposite > 0 ? "+" : "", timeZoneOpposite);
        setenv("TZ", timeZoneString, 1);
        tzset();
    }

    if (ntpServerParamStatus == kea_sc_ConfigS_ParamStatus_SUCCESS && timeZoneParamStatus == kea_sc_ConfigS_ParamStatus_SUCCESS) {
        sntp_init();
    }
}

bool kea_sc_DateS_isDateValid(kea_sc_DateS_Date date) {
    return date.sec < 60 &&
           date.min < 60 && 
           date.hour < 24 && 
           date.day <= 31 && 
           date.month <= kea_sc_DateS_Month_DEC &&
           date.dayOfWeek <= kea_sc_DateS_DayOfWeek_SUN;
}

kea_sc_DateS_Date kea_sc_DateS_getCurrentDate() {
    time_t t = time(NULL);
    struct tm *localTime = localtime(&t);

    kea_sc_DateS_Date date = {
        .sec = localTime->tm_sec,
        .min = localTime->tm_min,
        .hour = localTime->tm_hour,
        .day = localTime->tm_mday,
        .month = localTime->tm_mon,
        .year = 1900 + localTime->tm_year,
        //tm_wday is days since Sunday – [0, 6], but dayOfWeek is days since Monday – [0, 6]
        .dayOfWeek = (localTime->tm_wday + 6) % DAYS_IN_WEEK, //tm_wday is days since Sunday – [0, 6]
    };

    if(date.sec == 60) {
        date.sec = 59;
    }

    return date;
}

#undef DAYS_IN_WEEK
#undef NTP_SERVER_NAME_LENGTH_MAX