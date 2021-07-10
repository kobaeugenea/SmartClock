#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <clib/u8g2.h>

#include "service/kea_sc_MessageS.h"
#include "component/display/kea_sc_DisplayC.h"
#include "util/kea_sc_MemoryU.h"

#define KEA_SC_2X4MAX7219DISAPLYC_TASK_PRIORITY 1
#define KEA_SC_2X4MAX7219DISAPLYC_TASK_STACK_DEPTH 2048

uint8_t u8x8_gpio_and_delay_arduino(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
static void redraw(void *pvParameter);

//digits
static unsigned char SMALL_DIGITS[][8] = {{0xde, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xde},
                                         {0xcc, 0xce, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xde},
                                         {0xde, 0xf3, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3, 0xff},
                                         {0xde, 0xf3, 0xf0, 0xdc, 0xf0, 0xf0, 0xf3, 0xde},
                                         {0xd8, 0xcc, 0xc6, 0xc3, 0xdb, 0xff, 0xd8, 0xd8},
                                         {0xff, 0xc3, 0xc3, 0xdf, 0xf0, 0xf0, 0xf3, 0xde},
                                         {0xde, 0xf3, 0xc3, 0xc3, 0xdf, 0xf3, 0xf3, 0xde},
                                         {0xff, 0xf0, 0xf0, 0xd8, 0xcc, 0xcc, 0xcc, 0xcc},
                                         {0xde, 0xf3, 0xf3, 0xde, 0xf3, 0xf3, 0xf3, 0xde},
                                         {0xde, 0xf3, 0xf3, 0xf3, 0xfe, 0xf0, 0xf3, 0xde}};
static unsigned char SMALL_DIGIT_COLON[] = {0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xfc};

typedef struct kea_sc_Display2x4Max7219C_Context {
    u8g2_t u8g2;
    kea_sc_DateS_Date date;
    SemaphoreHandle_t dateSemaphore;
} kea_sc_Display2x4Max7219C_Context;

void kea_sc_Display2x4Max7219C_init(kea_sc_ComponentS_Id componentsId) {
  u8g2_t u8g2;
  u8g2_Setup_max7219_64x8_f(&u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
  u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_SPI_CLOCK, 18);
  u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_SPI_DATA, 23);
  u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_CS, 5);
  u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_DC, U8X8_PIN_NONE);
  u8x8_SetPin(u8g2_GetU8x8(&u8g2), U8X8_PIN_RESET, U8X8_PIN_NONE);
  u8g2_InitDisplay(&u8g2);
  u8g2_ClearDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_SetContrast(&u8g2, 160);
  u8g2_SetFont(&u8g2, u8g2_font_victoriabold8_8r);

  kea_sc_Display2x4Max7219C_Context* context = kea_sc_MemoryU_malloc(sizeof(kea_sc_Display2x4Max7219C_Context));
  context -> u8g2 = u8g2;
  context -> dateSemaphore = kea_sc_MemoryU_xSemaphoreCreateMutex();

  kea_sc_ComponentS_putContext(componentsId, context);

  kea_sc_MemoryU_xTaskCreate(&redraw, "Display2x4Max7219C_redraw", KEA_SC_2X4MAX7219DISAPLYC_TASK_STACK_DEPTH, context, KEA_SC_2X4MAX7219DISAPLYC_TASK_PRIORITY, NULL);
}

static void printFirstFloor(u8g2_t* u8g2, kea_sc_DateS_Date date, bool showColon) {
  const uint8_t digitWidth = 6;
  const uint8_t colonWidth = 2;
  const uint8_t charHeight = 8;
  const uint8_t yPos = 0;
  const uint8_t fitstDigitHoursXPos = 1;
  const uint8_t secondDigitHoursXPos = 8;
  const uint8_t colonXPos = 15;
  const uint8_t fitstDigitMinutesXPos = 18;
  const uint8_t secondDigitMinutesXPos = 25;

  uint8_t fitstDigitHours = date.hour / 10;
  uint8_t secondDigitHours = date.hour % 10;
  uint8_t fitstDigitMinutes = date.min / 10;
  uint8_t secondDigitMinutes = date.min % 10;

  u8g2_DrawXBM(u8g2, fitstDigitHoursXPos, yPos, digitWidth, charHeight, SMALL_DIGITS[fitstDigitHours]);
  u8g2_DrawXBM(u8g2, secondDigitHoursXPos, yPos, digitWidth, charHeight, SMALL_DIGITS[secondDigitHours]);
  if(showColon) {
    u8g2_DrawXBM(u8g2, colonXPos, yPos, colonWidth, charHeight, SMALL_DIGIT_COLON);
  }
  u8g2_DrawXBM(u8g2, fitstDigitMinutesXPos, yPos, digitWidth, charHeight, SMALL_DIGITS[fitstDigitMinutes]);
  u8g2_DrawXBM(u8g2, secondDigitMinutesXPos, yPos, digitWidth, charHeight, SMALL_DIGITS[secondDigitMinutes]);
}

static u8g2_uint_t printSecondFloor(u8g2_t* u8g2, kea_sc_DateS_Date date, uint8_t offset) {
  const uint8_t maxDateStrLength = 255;

  char* template = kea_sc_MessageS_getTranslatedMessage(KEA_SC_MESSAGES_DATE_TEMPLATE);
  char* dayOfWeek = kea_sc_MessageS_getTranslatedCapitalDayOfWeek(date.dayOfWeek);
  char* month = kea_sc_MessageS_getTranslatedMonth(date.month);
  
  char dateStr[maxDateStrLength];
  snprintf(dateStr, maxDateStrLength, template, dayOfWeek, date.day, month, date.year);

  u8g2_SetClipWindow(u8g2, 32, 0, 64, 8);
  u8g2_DrawStr(u8g2, 64 - offset, 7, dateStr);
  u8g2_SetMaxClipWindow(u8g2);
  return u8g2_GetStrWidth(u8g2, dateStr) + 32;
}

void kea_sc_Display2x4Max7219C_setDate(kea_sc_ComponentS_Id componentsId, kea_sc_DateS_Date date) {
  kea_sc_Display2x4Max7219C_Context* context = kea_sc_ComponentS_getContext(componentsId);
  if(xSemaphoreTake(context->dateSemaphore, portMAX_DELAY) == pdTRUE)
  {
    context -> date = date;
    xSemaphoreGive(context->dateSemaphore);
  }
}

static bool showColon(uint64_t cycleNum, uint64_t delayMs, uint64_t updateColonAtMs) {
  uint64_t updateColonAtCycle = updateColonAtMs / delayMs;
  uint64_t updatesAmount = cycleNum / updateColonAtCycle;
  return updatesAmount % 2;
}


static void redraw(void *pvParameter) {
  static uint64_t drawCycleNum = 0;
  static uint8_t secondFloorTextOffset = 0;

  const uint64_t delayMs = 100;
  const uint64_t updateColonAtMs = 1000;

  kea_sc_Display2x4Max7219C_Context* context = pvParameter;

  while (true)
  {
    kea_sc_DateS_Date date;
    if (xSemaphoreTake(context->dateSemaphore, portMAX_DELAY) == pdTRUE)
    {
      date = context -> date;
      xSemaphoreGive(context->dateSemaphore);
    }

    u8g2_ClearBuffer(&(context->u8g2));
    printFirstFloor(&(context->u8g2), date, showColon(drawCycleNum, delayMs, updateColonAtMs));
    uint8_t maxOffset = printSecondFloor(&(context->u8g2), date, secondFloorTextOffset);
    u8g2_SendBuffer(&(context->u8g2));

    secondFloorTextOffset = (secondFloorTextOffset >= maxOffset - 1) ? 0 : secondFloorTextOffset + 1; 
    drawCycleNum++;
    vTaskDelay(delayMs / portTICK_PERIOD_MS);
  }
}
