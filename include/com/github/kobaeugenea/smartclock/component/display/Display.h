#ifndef KEA_SC_COMPONENT_DISPLAY_H
#define KEA_SC_COMPONENT_DISPLAY_H

#include "com/github/kobaeugenea/smartclock/service/ComponentService.h"
#include "com/github/kobaeugenea/smartclock/service/DateService.h"

typedef struct
{
    void (*init) (ComponentId);
    void (*displayDate) (ComponentId, Date);
} kea_sc_Display_n;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define Display_n kea_sc_Display_n
#endif

#endif