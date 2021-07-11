#ifndef KEA_SC_DATES_H
#define KEA_SC_DATES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum kea_sc_DateS_DayOfWeek {
    kea_sc_DateS_DayOfWeek_MON,
    kea_sc_DateS_DayOfWeek_TUE,
    kea_sc_DateS_DayOfWeek_WED,
    kea_sc_DateS_DayOfWeek_THU,
    kea_sc_DateS_DayOfWeek_FRI,
    kea_sc_DateS_DayOfWeek_SAT,
    kea_sc_DateS_DayOfWeek_SUN,
} kea_sc_DateS_DayOfWeek;

typedef enum kea_sc_DateS_Month {
    kea_sc_DateS_Month_JAN,
    kea_sc_DateS_Month_FEB,
    kea_sc_DateS_Month_MAR,
    kea_sc_DateS_Month_APR,
    kea_sc_DateS_Month_MAY,
    kea_sc_DateS_Month_JUN,
    kea_sc_DateS_Month_JUL,
    kea_sc_DateS_Month_AUG,
    kea_sc_DateS_Month_SEP,
    kea_sc_DateS_Month_OCT,
    kea_sc_DateS_Month_NOV,
    kea_sc_DateS_Month_DEC,
} kea_sc_DateS_Month;

typedef struct kea_sc_DateS_Date {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    kea_sc_DateS_Month month;
    uint16_t year;
    kea_sc_DateS_DayOfWeek dayOfWeek;
} kea_sc_DateS_Date;

extern kea_sc_DateS_Date kea_sc_DateS_Date_unixEpoch;

#ifdef __cplusplus
extern "C" {
#endif

void kea_sc_DateS_init();
bool kea_sc_DateS_isDateValid(kea_sc_DateS_Date date);
kea_sc_DateS_Date kea_sc_DateS_getCurrentDate();

#ifdef __cplusplus
}
#endif

#endif