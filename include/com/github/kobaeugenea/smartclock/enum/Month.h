#ifndef KEA_SC_ENUM_MONTH_H
#define KEA_SC_ENUM_MONTH_H

typedef enum {
    kea_sc_Month_JAN,
    kea_sc_Month_FEB,
    kea_sc_Month_MAR,
    kea_sc_Month_APR,
    kea_sc_Month_MAY,
    kea_sc_Month_JUN,
    kea_sc_Month_JUL,
    kea_sc_Month_AUG,
    kea_sc_Month_SEP,
    kea_sc_Month_OCT,
    kea_sc_Month_NOV,
    kea_sc_Month_DEC,
} kea_sc_Month;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define Month kea_sc_Month
#define Month_JAN kea_sc_Month_JAN
#define Month_FEB kea_sc_Month_FEB
#define Month_MAR kea_sc_Month_MAR
#define Month_APR kea_sc_Month_APR
#define Month_MAY kea_sc_Month_MAY
#define Month_JUN kea_sc_Month_JUN
#define Month_JUL kea_sc_Month_JUL
#define Month_AUG kea_sc_Month_AUG
#define Month_SEP kea_sc_Month_SEP
#define Month_OCT kea_sc_Month_OCT
#define Month_NOV kea_sc_Month_NOV
#define Month_DEC kea_sc_Month_DEC
#endif

#endif