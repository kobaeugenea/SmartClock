#ifndef KEA_SC_COMPONENTSERVICE_H
#define KEA_SC_COMPONENTSERVICE_H

#include "com/github/kobaeugenea/smartclock/enum/ComponentStatus.h"
#include <stdint.h>

typedef struct  {
    uint8_t id;
    ComponentStatus status;
} kea_sc_ComponentId;

typedef struct
{
    kea_sc_ComponentId (* const init)(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset);
    void (* const putContext)(kea_sc_ComponentId componentSData, void* context);
    void* (* const getContext)(kea_sc_ComponentId componentSData);
} kea_sc_ComponentService_n;
extern kea_sc_ComponentService_n const kea_sc_ComponentService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define ComponentId kea_sc_ComponentId
#define ComponentService kea_sc_ComponentService
#endif

#endif