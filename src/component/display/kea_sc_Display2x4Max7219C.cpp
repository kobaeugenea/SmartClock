#ifndef KEA_SC_2X4MAX7219DISAPLYC_H
#define KEA_SC_2X4MAX7219DISAPLYC_H

#include <U8g2lib.h>

#include "component/display/kea_sc_DisplayC.h"

extern "C" void kea_sc_Display2x4Max7219C_init(kea_sc_ComponentS_Id componentsId) {
  printf("kea_sc_Display2x4Max7219C_init\n");
}
extern "C" void kea_sc_Display2x4Max7219C_displayDate(kea_sc_DateS_Date date) {
  u8g2_t u8g2;
  u8g2_Setup_max7219_64x8_1(&u8g2, U8G2_R0, u8x8_byte_arduino_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
  u8x8_SetPin_4Wire_SW_SPI(u8g2_GetU8x8(&u8g2), 18, 23, 5, U8X8_PIN_NONE, U8X8_PIN_NONE);
  u8g2_InitDisplay(&u8g2);
  u8g2_ClearDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_SetContrast(&u8g2, 160);
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_victoriabold8_8r);
  u8g2_DrawStr(&u8g2, 0, 7, "LOVE");
  u8g2_SetDisplayRotation(&u8g2, U8G2_R2);
  u8g2_DrawStr(&u8g2, 0, 7, "YOU!");
  u8g2_SendBuffer(&u8g2);
}

#endif