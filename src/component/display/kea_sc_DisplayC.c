#include <stdlib.h>
#include <stdio.h>
#include "component/display/kea_sc_DisplayC.h"
#include "component/display/kea_sc_Display2x4Max7219C.h"
#include "service/kea_sc_ErrorS.h"
#include "service/kea_sc_MessageS.h"
#include "service/kea_sc_ComponentS.h"

typedef struct kea_sc_DisplayC_Methods
{
    void (*init) (kea_sc_ComponentS_Id);
    void (*displayDate) (kea_sc_ComponentS_Id, kea_sc_DateS_Date);
} kea_sc_DisplayC_Methods;

static kea_sc_DisplayC_Methods displayMethods[] = {
    [0].displayDate = kea_sc_Display2x4Max7219C_displayDate,
    [0].init = kea_sc_Display2x4Max7219C_init
};

static uint8_t displaysCount;
static kea_sc_DisplayC_Id *displayIds;

//common displays methods
void kea_sc_DisplayC_init() {
    //TODO dummy method, implement reading from flash
    displaysCount = 1;
    displayIds = malloc(sizeof(kea_sc_DisplayC_Id) * displaysCount);
    kea_sc_ComponentS_Id componentId = kea_sc_ComponentS_init(18, 23, 5, -1, -1);
    displayIds[0].id = 0;
    displayIds[0].componentId = componentId;
    displayIds[0].type = kea_sc_DisplayC_Type_2X4MAX7219;
    displayIds[0].status = kea_sc_IdU_Status_OK;
    kea_sc_DisplayC_Id displayId = displayIds[0];
    displayMethods[displayId.type].init(displayId.componentId);
}
uint8_t kea_sc_DisplayC_getDisplaysCount() {
    return displaysCount;
}
kea_sc_DisplayC_Id kea_sc_DisplayC_getDisplayDisplayId(uint8_t n) {
    if(n >= displaysCount) {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_DISPLAY_NOT_EXISTS), n, displaysCount);
        kea_sc_DisplayC_Id displayId = {
            .status = kea_sc_IdU_Status_OK,
        };
        return displayId;
    }

    return displayIds[n];
}
//end common displays methods

//work with particualr display
void kea_sc_DisplayC_displayDate(kea_sc_DisplayC_Id displayId, kea_sc_DateS_Date date) {
    displayMethods[displayId.type].displayDate(displayId.componentId, date);
}
//end work with particualr display