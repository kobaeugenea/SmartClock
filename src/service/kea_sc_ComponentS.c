#include "service/kea_sc_ComponentS.h"
#include "service/kea_sc_ErrorS.h"
#include "service/kea_sc_MessageS.h"
#include <stdbool.h>
#include <string.h>

#define MAX_COMPONENT_COUNT 16

typedef struct kea_sc_ComponentContext
{
    kea_sc_ComponentS_Data componentSData;
    void *context;
} kea_sc_ComponentContext;

static uint8_t numberOfComponents = 0;
static kea_sc_ComponentContext components[MAX_COMPONENT_COUNT];

static bool checkPinAlreadyUsed(int8_t pin)
{
    if (pin < 0)
    {
        return false;
    }

    for (uint8_t i = 0; i < numberOfComponents; i++)
    {
        kea_sc_ComponentS_Data componentSData = components[i].componentSData;
        if (componentSData.clock == pin ||
            componentSData.data == pin ||
            componentSData.cs == pin ||
            componentSData.dc == pin ||
            componentSData.reset == pin)
        {
            return true;
        }
    }

    return false;
}

/**
 * @return -1 if all pins used by component are free, otherwise return busy pin number
 */
static int8_t checkPinsAlreadyUsed(kea_sc_ComponentS_Data componentSData)
{
    if (checkPinAlreadyUsed(componentSData.clock))
    {
        return componentSData.clock;
    }
    if (checkPinAlreadyUsed(componentSData.data))
    {
        return componentSData.data;
    }
    if (checkPinAlreadyUsed(componentSData.cs))
    {
        return componentSData.cs;
    }
    if (checkPinAlreadyUsed(componentSData.dc))
    {
        return componentSData.dc;
    }
    if (checkPinAlreadyUsed(componentSData.reset))
    {
        return componentSData.reset;
    }

    return -1;
}

/**
 * Init component data
 * Pass -1 if pin isn't used by component
 */
kea_sc_ComponentS_Id kea_sc_ComponentS_init(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset)
{
    kea_sc_ComponentS_Data componentSData = {
        .clock = clock,
        .data = data,
        .cs = cs,
        .dc = dc,
        .reset = reset,
    };

    if (numberOfComponents >= MAX_COMPONENT_COUNT)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_TOO_MANY_COMPONENTS_CODE), MAX_ERROR_LENGTH);
        kea_sc_ComponentS_Id componentId = {
            .id = numberOfComponents,
            .status = kea_sc_IdU_Status_NOT_CREATED
        };
        return componentId;
    }

    int8_t usedPin = checkPinsAlreadyUsed(componentSData);
    if (usedPin)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_PIN_USED_CODE), usedPin);
        kea_sc_ComponentS_Id componentId = {
            .id = numberOfComponents,
            .status = kea_sc_IdU_Status_NOT_CREATED
        };
        return componentId;
    }

    kea_sc_ComponentContext componentContext = {
        .componentSData = componentSData,
        .context = NULL,
    };

    kea_sc_ComponentS_Id componentId = {
        .id = numberOfComponents,
        .status = kea_sc_IdU_Status_OK
    };

    components[numberOfComponents] = componentContext;
    numberOfComponents++;

    return componentId;
}

void kea_sc_ComponentS_putContext(kea_sc_ComponentS_Id componentId, void *context)
{
    if(componentId.id > numberOfComponents) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_COMPONENT_NOT_EXISTS), componentId.id);
        return;
    }
    components[componentId.id].context = context;
}

void *kea_sc_ComponentS_getContext(kea_sc_ComponentS_Id componentId)
{
    if(componentId.id > numberOfComponents) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_COMPONENT_NOT_EXISTS), componentId.id);
        return NULL;
    }
    return components[componentId.id].context;
}