//Utils that responsible for allocation and freeing memory
//Please use only this service for that purposes

#ifndef KEA_SC_MEMORYU_H
#define KEA_SC_MEMORYU_H
 
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

typedef struct {
  BaseType_t (*const xTaskCreate)(TaskFunction_t pvTaskCode,
                                  const char *const pcName,
                                  UBaseType_t usStackDepth,
                                  void *pvParameters,
                                  UBaseType_t uxPriority,
                                  TaskHandle_t *pxCreatedTask);
  SemaphoreHandle_t (* const xSemaphoreCreateMutexWrap)(void);
  void* (* const malloc)(size_t size);
} kea_sc_MemoryUtils_n;
extern kea_sc_MemoryUtils_n const kea_sc_MemoryUtils;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define MemoryUtils kea_sc_MemoryUtils
#endif


#endif