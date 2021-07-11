#include "service/kea_sc_DateS.h"

#include <esp_sntp.h>

#define KEA_SC_DATES_DAYS_IN_WEEK 7

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
    setenv("TZ", "VLAT-10", 1);
    tzset();

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
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
        .dayOfWeek = (localTime->tm_wday + 6) % KEA_SC_DATES_DAYS_IN_WEEK, //tm_wday is days since Sunday – [0, 6]
    };

    if(date.sec == 60) {
        date.sec = 59;
    }

    return date;
}