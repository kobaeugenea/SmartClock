#include "service/kea_sc_DateS.h"

kea_sc_DateS_Date kea_sc_DateS_Date_unixEpoch = {
    .sec = 0,
    .min = 0,
    .hour = 0,
    .day = 1,
    .month = kea_sc_DateS_Month_JAN,
    .year = 1970,
    .dayOfWeek = kea_sc_DateS_DayOfWeek_THU,
};

bool kea_sc_DateS_isDateValid(kea_sc_DateS_Date date) {
    return date.sec <= 60 &&
           date.min <= 60 && 
           date.hour <= 24 && 
           date.day <= 31 && 
           date.month <= kea_sc_DateS_Month_DEC &&
           date.dayOfWeek <= kea_sc_DateS_DayOfWeek_SUN;
}