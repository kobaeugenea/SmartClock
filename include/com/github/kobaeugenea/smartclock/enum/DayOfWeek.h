#ifndef KEA_SC_ENUM_DAYOFWEEK_H
#define KEA_SC_ENUM_DAYOFWEEK_H

typedef enum {
    kea_sc_DayOfWeek_MON,
    kea_sc_DayOfWeek_TUE,
    kea_sc_DayOfWeek_WED,
    kea_sc_DayOfWeek_THU,
    kea_sc_DayOfWeek_FRI,
    kea_sc_DayOfWeek_SAT,
    kea_sc_DayOfWeek_SUN,
} kea_sc_DayOfWeek;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define DayOfWeek kea_sc_DayOfWeek
#define DayOfWeek_MON kea_sc_DayOfWeek_MON
#define DayOfWeek_TUE kea_sc_DayOfWeek_TUE
#define DayOfWeek_WED kea_sc_DayOfWeek_WED
#define DayOfWeek_THU kea_sc_DayOfWeek_THU
#define DayOfWeek_FRI kea_sc_DayOfWeek_FRI
#define DayOfWeek_SAT kea_sc_DayOfWeek_SAT
#define DayOfWeek_SUN kea_sc_DayOfWeek_SUN
#endif

#endif