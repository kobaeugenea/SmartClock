#ifndef KEA_SC_COMPONENTS_H
#define KEA_SC_COMPONENTS_H

#include <stdint.h>

#define MAX_COMPONENT_NAME_LENGHT 24

typedef struct kea_sc_ComponentSData {
    int8_t clock;
    int8_t data;
    int8_t cs;
    int8_t dc;
    int8_t reset;
    char* componentName;
} kea_sc_ComponentSData;

kea_sc_ComponentSData kea_sc_ComponentS_init(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset, char componentName[MAX_COMPONENT_NAME_LENGHT]);
void kea_sc_ComponentS_putContext(kea_sc_ComponentSData componentSData, void* context);
void* kea_sc_ComponentS_getContext(kea_sc_ComponentSData componentSData);

#endif