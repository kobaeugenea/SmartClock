#ifndef KEA_SC_DATES_H
#define KEA_SC_DATES_H

#include <stdint.h>

typedef enum kea_sc_DateS_Weekday {
    kea_sc_DateS_Weekday_MON,
    kea_sc_DateS_Weekday_TUE,
    kea_sc_DateS_Weekday_WED,
    kea_sc_DateS_Weekday_THU,
    kea_sc_DateS_Weekday_FRI,
    kea_sc_DateS_Weekday_SAT,
    kea_sc_DateS_Weekday_SUN,
} kea_sc_DateS_Weekday;

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
    uint8_t day;
    kea_sc_DateS_Month month;
    uint16_t year;
    uint8_t hour;
    uint8_t sec;
    uint8_t min;
    kea_sc_DateS_Weekday weekday;
} kea_sc_DateS_Date;

#endif