#include "service/kea_sc_ComponentS.h"
#include "service/kea_sc_ErrorS.h"
#include "service/kea_sc_MessageS.h"
#include <stdbool.h>
#include <string.h>

#define MAX_COMPONENT_COUNT 16

typedef struct kea_sc_ComponentContext
{
    kea_sc_ComponentSData componentSData;
    void *context;
} kea_sc_ComponentContext;

static uint8_t numberOfComponents = 0;
static kea_sc_ComponentContext components[MAX_COMPONENT_COUNT];

/**
 * Init component data
 * Pass -1 if pin isn't used by component
 */
kea_sc_ComponentSData kea_sc_ComponentS_init(int8_t clock, int8_t data, int8_t cs, int8_t dc, int8_t reset, char componentName[])
{
    kea_sc_ComponentSData componentSData = {
        .clock = clock,
        .data = data,
        .cs = cs,
        .dc = dc,
        .reset = reset,
        .componentName = componentName,
    };
    return componentSData;
}

static bool checkPinAlreadyUsed(uint8_t pin)
{
    if (pin < 0)
    {
        return false;
    }

    for (uint8_t i = 0; i < numberOfComponents; i++)
    {
        kea_sc_ComponentSData componentSData = components[i].componentSData;
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
static int8_t checkPinsAlreadyUsed(kea_sc_ComponentSData componentSData)
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

void kea_sc_ComponentS_putContext(kea_sc_ComponentSData componentSData, void *context)
{
    //TODO translation service
    if (numberOfComponents >= MAX_COMPONENT_COUNT)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_TOO_MANY_COMPONENTS_CODE), MAX_ERROR_LENGTH);
        return;
    }

    int8_t usedPin = checkPinsAlreadyUsed(componentSData);
    if (usedPin)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_PIN_USED_CODE), usedPin);
        return;
    }

    kea_sc_ComponentContext componentContext = {
        .componentSData = componentSData,
        .context = context,
    };
    components[numberOfComponents] = componentContext;
    numberOfComponents++;
}

static bool isComponentsEqual(kea_sc_ComponentSData cd1, kea_sc_ComponentSData cd2)
{
    return cd1.clock == cd2.clock &&
           cd1.data == cd2.data &&
           cd1.cs == cd2.cs &&
           cd1.dc == cd2.dc &&
           cd1.reset == cd2.reset &&
           strcmp(cd1.componentName, cd2.componentName) == 0;
}

void *kea_sc_ComponentSGetContext(kea_sc_ComponentSData componentSData)
{
    for (uint8_t i = 0; i < numberOfComponents; i++)
    {
        if (isComponentsEqual(componentSData, components[i].componentSData))
        {
            return components[i].context;
        }
    }

    return NULL;
}