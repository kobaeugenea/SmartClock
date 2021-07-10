#ifndef KEA_SC_MEMORYU_H
#define KEA_SC_MEMORYU_H
 
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

BaseType_t kea_sc_MemoryU_xTaskCreate(TaskFunction_t pvTaskCode,
                                      const char *const pcName,
                                      UBaseType_t usStackDepth,
                                      void *pvParameters,
                                      UBaseType_t uxPriority,
                                      TaskHandle_t *pxCreatedTask);
SemaphoreHandle_t kea_sc_MemoryU_xSemaphoreCreateMutex();
void* kea_sc_MemoryU_malloc(size_t size);


#endif