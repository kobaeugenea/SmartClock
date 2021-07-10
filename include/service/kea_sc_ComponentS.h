#ifndef KEA_SC_COMPONENTS_H
#define KEA_SC_COMPONENTS_H

#include <stdint.h>
#include "util/kea_sc_IdU.h"

typedef struct kea_sc_ComponentS_Data {
    int8_t clock;
    int8_t data;
    int8_t cs;
    int8_t dc;
    int8_t reset;
} kea_sc_ComponentS_Data;

typedef struct kea_sc_ComponentS_Id {
    uint8_t id;
    kea_sc_IdU_Status status;

} kea_sc_ComponentS_Id;

#ifdef __cplusplus
extern "C" {
#endif

kea_sc_ComponentS_Id kea_sc_ComponentS_init(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset);
void kea_sc_ComponentS_putContext(kea_sc_ComponentS_Id componentSData, void* context);
void* kea_sc_ComponentS_getContext(kea_sc_ComponentS_Id componentSData);

#ifdef __cplusplus
}
#endif

#endif