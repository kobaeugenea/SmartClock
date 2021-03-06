#include "com/github/kobaeugenea/smartclock/service/DateService.h"
#include "com/github/kobaeugenea/smartclock/service/ConfigService.h"

#include <esp_sntp.h>
#include <esp_log.h>

#define DAYS_IN_WEEK 7
#define NTP_SERVER_NAME_LENGTH_MAX 32
static const char* TAG = "DateService";

static int8_t timeZone = 0;
static char ntpServer[NTP_SERVER_NAME_LENGTH_MAX];

static void init() {
    ESP_LOGI(TAG, "Initialization");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);

    ParamStatus ntpServerParamStatus = ConfigService.getNTPServer(ntpServer, NTP_SERVER_NAME_LENGTH_MAX);
    if (ntpServerParamStatus == ParamStatus_SUCCESS) {
        sntp_setservername(0, ntpServer);
    }

    ParamStatus timeZoneParamStatus = ConfigService.getTimeZone(&timeZone);
    if (timeZoneParamStatus == ParamStatus_SUCCESS) {
        char timeZoneString[9];
        int8_t timeZoneOpposite = timeZone * -1; // Seems to be bug in setenv as opposite time zone should be passed for correct work
        sprintf(timeZoneString, "GMT%s%d", timeZoneOpposite > 0 ? "+" : "", timeZoneOpposite);
        setenv("TZ", timeZoneString, 1);
        tzset();
    }

    if (ntpServerParamStatus == ParamStatus_SUCCESS && timeZoneParamStatus == ParamStatus_SUCCESS) {
        sntp_init();
    }
    ESP_LOGI(TAG, "Initialized");
}

static bool isDateValid(kea_sc_Date date) {
    return date.sec < 60 &&
           date.min < 60 && 
           date.hour < 24 && 
           date.day <= 31 && 
           date.month <= Month_DEC &&
           date.dayOfWeek <= DayOfWeek_SUN;
}

static kea_sc_Date getCurrentDate() {
    time_t t = time(NULL);
    struct tm *localTime = localtime(&t);

    kea_sc_Date date = {
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

kea_sc_Date const KEA_SC_UNIX_EPOCH = {
    .sec = 0,
    .min = 0,
    .hour = 0,
    .day = 1,
    .month = Month_JAN,
    .year = 1970,
    .dayOfWeek = DayOfWeek_THU,
};

kea_sc_DateService_n const kea_sc_DateService = {
    .init = init,
    .getCurrentDate = getCurrentDate,
    .isDateValid = isDateValid
};

#undef DAYS_IN_WEEK
#undef NTP_SERVER_NAME_LENGTH_MAX