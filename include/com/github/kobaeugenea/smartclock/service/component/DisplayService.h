#ifndef KEA_SC_DISAPLYSERVICE_H
#define KEA_SC_DISAPLYSERVICE_H

#include "com/github/kobaeugenea/smartclock/service/ComponentService.h"
#include "com/github/kobaeugenea/smartclock/service/DateService.h"
#include "com/github/kobaeugenea/smartclock/enum/ComponentStatus.h"

typedef struct
{
    void (* const init)(void);
    uint8_t (* const getDisplaysCount)(void);
    void (* const showDate)(uint8_t displayNum, Date date);
} kea_sc_DisaplyService_n;
extern kea_sc_DisaplyService_n const kea_sc_DisaplyService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define DisaplyService kea_sc_DisaplyService
#endif

#endif