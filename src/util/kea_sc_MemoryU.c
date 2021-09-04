#include "util/kea_sc_MemoryU.h"
#include "service/kea_sc_ErrorS.h"
#include "service/kea_sc_MessageS.h"

BaseType_t kea_sc_MemoryU_xTaskCreate(TaskFunction_t pvTaskCode,
                                      const char *const pcName,
                                      UBaseType_t usStackDepth,
                                      void *pvParameters,
                                      UBaseType_t uxPriority,
                                      TaskHandle_t *pxCreatedTask)
{
    BaseType_t task = xTaskCreate(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
    if(task != pdPASS)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_CREATE_TASK));
        vTaskSuspend(NULL);
    }
    return task;
}


SemaphoreHandle_t kea_sc_MemoryU_xSemaphoreCreateMutex() {
    SemaphoreHandle_t semaphore = xSemaphoreCreateMutex();
    if(semaphore == NULL)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_CREATE_SEMAPHORE));
        vTaskSuspend(NULL);
    }
    return semaphore;
}

void* kea_sc_MemoryU_malloc(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL)
    {
        kea_sc_ErrorS_put(kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_CANNOT_ALLOCATE_MEMORY));
        vTaskSuspend(NULL);
    }
    return ptr;
}