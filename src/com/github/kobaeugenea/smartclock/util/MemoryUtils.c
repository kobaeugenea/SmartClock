#include "com/github/kobaeugenea/smartclock/util/MemoryUtils.h"
#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"
#include "com/github/kobaeugenea/smartclock/service/MessageService.h"

static BaseType_t xTaskCreateWrap(TaskFunction_t pvTaskCode,
                              const char *const pcName,
                              UBaseType_t usStackDepth,
                              void *pvParameters,
                              UBaseType_t uxPriority,
                              TaskHandle_t *pxCreatedTask)
{
    BaseType_t task = xTaskCreate(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
    if(task != pdPASS)
    {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_CREATE_TASK));
        vTaskSuspend(NULL);
    }
    return task;
}


static SemaphoreHandle_t xSemaphoreCreateMutexWrap() {
    SemaphoreHandle_t semaphore = xSemaphoreCreateMutex();
    if(semaphore == NULL)
    {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_CREATE_SEMAPHORE));
        vTaskSuspend(NULL);
    }
    return semaphore;
}

static void* mallocWrap(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL)
    {
        ErrorService.put(MessageService.getTranslatedMessage(MESSAGE_CANNOT_ALLOCATE_MEMORY));
        vTaskSuspend(NULL);
    }
    return ptr;
}

kea_sc_MemoryUtils_n const kea_sc_MemoryUtils = {
    .xTaskCreate = xTaskCreateWrap,
    .xSemaphoreCreateMutexWrap = xSemaphoreCreateMutexWrap,
    .malloc = mallocWrap
};