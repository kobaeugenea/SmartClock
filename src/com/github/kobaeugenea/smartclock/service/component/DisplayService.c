#include "com/github/kobaeugenea/smartclock/component/display/Display2x4Max7219.h"
#include "com/github/kobaeugenea/smartclock/util/MemoryUtils.h"
#include "com/github/kobaeugenea/smartclock/service/ComponentService.h"
#include "com/github/kobaeugenea/smartclock/service/component/DisplayService.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"

#include <stdlib.h>
#include <stdio.h>
#include <esp_log.h>

typedef struct {
    Display_n* display;
    ComponentId disaplyId;
} kea_sc_DisaplayInstance;
static kea_sc_DisaplayInstance **displayInstances;

static uint8_t displaysCount;
static const char *TAG = "DisaplayService";

//common displays methods
static void init() {
    //TODO dummy method, implement reading from flash
    ESP_LOGI(TAG, "Initialization");
    displaysCount = 1;
    displayInstances = MemoryUtils.malloc(sizeof(kea_sc_DisaplayInstance*) * displaysCount);
    displayInstances[0] = MemoryUtils.malloc(sizeof(kea_sc_DisaplayInstance));
    kea_sc_DisaplayInstance *displayInstance = displayInstances[0];
    

    ComponentId componentId = ComponentService.init(18, 23, 5, -1, -1);
    displayInstance->display = &Disaplay2x4Max7219;
    displayInstance->disaplyId = componentId;

    displayInstance->display->init(displayInstance->disaplyId);
    ESP_LOGI(TAG, "Initialized");
}
static uint8_t getDisplaysCount() {
    return displaysCount;
}

//work with particualr display
static void showDate(uint8_t displayNum, Date date) {
    if(displayNum >= displaysCount) {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_DISPLAY_NOT_EXISTS), displayNum, displaysCount);
    }
    kea_sc_DisaplayInstance* displayInstance = displayInstances[displayNum];
    displayInstance->display->displayDate(displayInstance->disaplyId, date);

}
//end work with particualr display

kea_sc_DisaplyService_n const kea_sc_DisaplyService = {
    .init = init,
    .getDisplaysCount = getDisplaysCount,
    .showDate = showDate
};