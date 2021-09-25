#ifndef KEA_SC_DATES_H
#define KEA_SC_DATES_H

#include "com/github/kobaeugenea/smartclock/enum/DayOfWeek.h"
#include "com/github/kobaeugenea/smartclock/enum/Month.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct  {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    Month month;
    uint16_t year;
    DayOfWeek dayOfWeek;
} kea_sc_Date;

extern const kea_sc_Date KEA_SC_UNIX_EPOCH;

typedef struct {
    void (* const init)(void);
    bool (* const isDateValid)(kea_sc_Date);
    kea_sc_Date (* const getCurrentDate)(void);
} kea_sc_DateService_n;
extern kea_sc_DateService_n const kea_sc_DateService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define DateSerivce kea_sc_DateService 
#define UNIX_EPOCH KEA_SC_UNIX_EPOCH 
#define Date kea_sc_Date 
#endif


#endif