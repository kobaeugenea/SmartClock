#include "com/github/kobaeugenea/smartclock/service/ComponentService.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"

#include <stdbool.h>
#include <string.h>
#include <esp_log.h>

#define MAX_COMPONENT_COUNT 16

typedef struct {
    int8_t clock;
    int8_t data;
    int8_t cs;
    int8_t dc;
    int8_t reset;
} kea_sc_ComponentPins;

typedef struct
{
    kea_sc_ComponentPins componentPins;
    void *context;
} kea_sc_ComponentData;

static uint8_t numberOfComponents = 0;
static kea_sc_ComponentData components[MAX_COMPONENT_COUNT];

static bool checkPinAlreadyUsed(int8_t pin)
{
    if (pin < 0)
    {
        return false;
    }

    for (uint8_t i = 0; i < numberOfComponents; i++)
    {
        kea_sc_ComponentPins componentPins = components[i].componentPins;
        if (componentPins.clock == pin ||
            componentPins.data == pin ||
            componentPins.cs == pin ||
            componentPins.dc == pin ||
            componentPins.reset == pin)
        {
            return true;
        }
    }

    return false;
}

/**
 * @return -1 if all pins used by component are free, otherwise return busy pin number
 */
static int8_t checkPinsAlreadyUsed(kea_sc_ComponentPins componentPins)
{
    if (checkPinAlreadyUsed(componentPins.clock))
    {
        return componentPins.clock;
    }
    if (checkPinAlreadyUsed(componentPins.data))
    {
        return componentPins.data;
    }
    if (checkPinAlreadyUsed(componentPins.cs))
    {
        return componentPins.cs;
    }
    if (checkPinAlreadyUsed(componentPins.dc))
    {
        return componentPins.dc;
    }
    if (checkPinAlreadyUsed(componentPins.reset))
    {
        return componentPins.reset;
    }

    return -1;
}

/**
 * Init component data
 * Pass -1 if pin isn't used by component
 */
static kea_sc_ComponentId init(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset)
{
    kea_sc_ComponentPins componentPins = {
        .clock = clock,
        .data = data,
        .cs = cs,
        .dc = dc,
        .reset = reset,
    };

    if (numberOfComponents >= MAX_COMPONENT_COUNT)
    {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_TOO_MANY_COMPONENTS_CODE), MAX_ERROR_LENGTH);
        kea_sc_ComponentId componentId = {
            .id = numberOfComponents,
            .status = ComponentStatus_NOT_CREATED
        };
        return componentId;
    }

    int8_t usedPin = checkPinsAlreadyUsed(componentPins);
    if (usedPin >= 0)
    {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_PIN_USED_CODE), usedPin);
        kea_sc_ComponentId componentId = {
            .id = numberOfComponents,
            .status = ComponentStatus_NOT_CREATED
        };
        return componentId;
    }

    kea_sc_ComponentData componentData = {
        .componentPins = componentPins,
        .context = NULL,
    };

    kea_sc_ComponentId componentId = {
        .id = numberOfComponents,
        .status = ComponentStatus_OK
    };

    components[numberOfComponents] = componentData;
    numberOfComponents++;

    return componentId;
}

static void putContext(kea_sc_ComponentId componentId, void *context)
{
    if(componentId.id > numberOfComponents) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_COMPONENT_NOT_EXISTS), componentId.id);
        return;
    }
    components[componentId.id].context = context;
}

static void *getContext(kea_sc_ComponentId componentId)
{
    if(componentId.id > numberOfComponents) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_COMPONENT_NOT_EXISTS), componentId.id);
        return NULL;
    }
    return components[componentId.id].context;
}

kea_sc_ComponentService_n const kea_sc_ComponentService = {
    .init = init,
    .getContext = getContext,
    .putContext = putContext
};